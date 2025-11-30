#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#define CLEAR "cls"
static void sleep_ms(unsigned int ms) { Sleep(ms); }
#else
#include <unistd.h>
#define CLEAR "clear"
static void sleep_ms(unsigned int ms) { usleep((useconds_t)ms * 1000); } // ms -> µs
#endif

#define MAX 1000

typedef struct node
{
    int y;
    int x;
    struct node *next;
} node;

typedef struct Graph
{
    int sizeY;
    int sizeX;
    int hit;
    int visit[MAX][MAX];
    node *adjacents[MAX][MAX];
} Graph;

/* prototypes */
int mazeLoadFromFile(int **maze, int *sizeY, int *sizeX, int *startY, int *startX, int *finishY, int *finishX);

node *createNode(int y, int x);
void addEdge(Graph *graph, int srcY, int srcX, int destY, int destX);
Graph *createGraph(int **maze, int y, int x);

void render(int **maze, Graph *graph, int delay, int y, int x);
int countAdjacents(node *getNode);

int dfsPathFinder(int **maze, int sizeY, int sizeX, Graph *graph, int delay, int startY, int startX, int finishY, int finishX)
{
    node *adjacent = graph->adjacents[startY][startX];

    int stackInd = 0;
    node *stack[MAX];

    int result = 0;
    while (adjacent && result == 0)
    {
        int adjacentY = adjacent->y;
        int adjacentX = adjacent->x;

        if (adjacentY == finishY && adjacentX == finishX)
        {
            result = 1;
        }
        else
        {
            if (maze[adjacentY][adjacentX] != 5)
            {
                /* don't overwrite start(2) or finish(3) */
                if (maze[adjacentY][adjacentX] != 2 && maze[adjacentY][adjacentX] != 3)
                    maze[adjacentY][adjacentX] = 5;

                node *newItem = malloc(sizeof(node));
                if (!newItem) { perror("malloc"); exit(EXIT_FAILURE); }
                newItem->y = adjacentY;
                newItem->x = adjacentX;
                newItem->next = NULL;
                stack[stackInd] = newItem;
                stackInd++;

                render(maze, graph, delay, sizeY, sizeX);
            }

            /* mark visited */
            if (graph->visit[adjacentY][adjacentX] == 0)
            {
                graph->visit[startY][startX] = 1;
                result = dfsPathFinder(maze, sizeY, sizeX, graph, delay, adjacentY, adjacentX, finishY, finishX);
                if (result == 0)
                {
                    int chk = 0;
                    int index = 0;
                    for (index = stackInd; index > 0; index--)
                    {
                        node *getNode = stack[index - 1];

                        if (chk == 0)
                        {
                            node *selAdjacent = graph->adjacents[getNode->y][getNode->x];
                            int res = countAdjacents(selAdjacent);
                            if (res == 1)
                            {
                                graph->hit++;
                            }
                            chk++;
                        }

                        if (maze[getNode->y][getNode->x] != 1 &&
                            maze[getNode->y][getNode->x] != 2 &&
                            maze[getNode->y][getNode->x] != 3)
                        {
                            maze[getNode->y][getNode->x] = 1;
                            render(maze, graph, delay, sizeY, sizeX);
                        }
                    }
                }
            }

            adjacent = adjacent->next;
        }
    }

    return result;
}

int main(void)
{
    system(CLEAR);
    srand((unsigned)time(NULL));

    int delay; /* milliseconds */
    int mazeSizeY = 0, mazeSizeX = 0;
    int startY = -1, startX = -1, finishY = -1, finishX = -1;

    /* allocate a MAX x MAX maze (simple approach) */
    int **maze = malloc(MAX * sizeof(int *));
    if (!maze) { perror("malloc"); return 1; }
    for (int i = 0; i < MAX; i++) {
        maze[i] = malloc(MAX * sizeof(int));
        if (!maze[i]) { perror("malloc"); return 1; }
        for (int j = 0; j < MAX; j++) maze[i][j] = 0;
    }

    if (!mazeLoadFromFile(maze, &mazeSizeY, &mazeSizeX, &startY, &startX, &finishY, &finishX))
    {
        fprintf(stderr, "Failed to load maze file.\n");
        return 1;
    }

    if (startY < 0 || finishY < 0) {
        fprintf(stderr, "Start or finish not found in maze file.\n");
        return 1;
    }

    Graph *graph = createGraph(maze, mazeSizeY, mazeSizeX);
    if (!graph) { fprintf(stderr, "Graph creation failed.\n"); return 1; }

    printf("Please enter a run time delay (milliseconds):\n");
    if (scanf("%d", &delay) != 1) delay = 100; /* default 100 ms */

    dfsPathFinder(maze, mazeSizeY, mazeSizeX, graph, delay, startY, startX, finishY, finishX);

    return 0;
}

/* -- file loader -- */
int mazeLoadFromFile(int **maze, int *sizeY, int *sizeX, int *startY, int *startX, int *finishY, int *finishX)
{
    FILE *fp;
    char buffer[MAX];
    fp = fopen("sample.txt", "r");
    if (fp == NULL)
    {
        perror("fopen sample.txt");
        return 0;
    }

    int i = 0;
    int maxX = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && i < MAX)
    {
        size_t len = strlen(buffer);
        int k;
        for (k = 0; k < (int)len && buffer[k] != '\n' && buffer[k] != '\r' && k < MAX; k++)
        {
            char ch = buffer[k];
            if (ch == '+' || ch == '-' || ch == '|')
            {
                maze[i][k] = 0;
            }
            else if (ch == ' ')
            {
                maze[i][k] = 1;
            }
            else if (ch == 'b')
            {
                maze[i][k] = 2;
                *startY = i;
                *startX = k;
            }
            else if (ch == 'c')
            {
                maze[i][k] = 3;
                *finishY = i;
                *finishX = k;
            }
            else
            {
                maze[i][k] = 1;
            }
        }
        if (k > maxX) maxX = k;
        i++;
    }

    *sizeY = i;
    *sizeX = maxX;

    fclose(fp);
    return 1;
}

node *createNode(int y, int x)
{
    node *newn = malloc(sizeof(node));
    if (!newn) { perror("malloc"); exit(EXIT_FAILURE); }
    newn->y = y;
    newn->x = x;
    newn->next = NULL;
    return newn;
}

void addEdge(Graph *graph, int srcY, int srcX, int destY, int destX)
{
    if (srcY < 0 || srcY >= graph->sizeY || srcX < 0 || srcX >= graph->sizeX) return;
    if (destY < 0 || destY >= graph->sizeY || destX < 0 || destX >= graph->sizeX) return;

    int notFound = 1;
    node *ptr = graph->adjacents[srcY][srcX];
    while (ptr != NULL && notFound)
    {
        if (ptr->y == destY && ptr->x == destX)
        {
            notFound = 0;
        }
        ptr = ptr->next;
    }

    if (notFound)
    {
        node *newNode = createNode(destY, destX);
        newNode->next = graph->adjacents[srcY][srcX];
        graph->adjacents[srcY][srcX] = newNode;

        newNode = createNode(srcY, srcX);
        newNode->next = graph->adjacents[destY][destX];
        graph->adjacents[destY][destX] = newNode;
    }
}

Graph *createGraph(int **maze, int y, int x)
{
    Graph *graph = malloc(sizeof(Graph));
    if (!graph) { perror("malloc"); exit(EXIT_FAILURE); }
    graph->sizeY = y;
    graph->sizeX = x;
    graph->hit = 0;

    for (int i = 0; i < y && i < MAX; i++)
    {
        for (int k = 0; k < x && k < MAX; k++)
        {
            graph->visit[i][k] = 0;
            graph->adjacents[i][k] = NULL;
        }
    }

    for (int i = 1; i < y - 1; i += 2)
    {
        for (int k = 1; k < x - 1; k += 2)
        {
            if (maze[i][k] != 0)
            {
                if (i - 2 >= 0 && maze[i - 2][k] != 0 && maze[i - 1][k] != 0)
                {
                    addEdge(graph, i, k, i - 2, k);
                }
                if (i + 2 < y && maze[i + 2][k] != 0 && maze[i + 1][k] != 0)
                {
                    addEdge(graph, i, k, i + 2, k);
                }
                if (k - 2 >= 0 && maze[i][k - 2] != 0 && maze[i][k - 1] != 0)
                {
                    addEdge(graph, i, k, i, k - 2);
                }
                if (k + 2 < x && maze[i][k + 2] != 0 && maze[i][k + 1] != 0)
                {
                    addEdge(graph, i, k, i, k + 2);
                }
            }
        }
    }

    return graph;
}

void render(int **maze, Graph *graph, int delay, int y, int x)
{
    system(CLEAR);

    for (int i = 0; i < y; i++)
    {
        for (int k = 0; k < x; k++)
        {
            if (i % 2 == 0 && k % 2 == 0 && maze[i][k] == 0)
            {
                printf("+");
            }
            else if (i % 2 == 0 && maze[i][k] == 0)
            {
                printf("-");
            }
            else if (k % 2 == 0 && maze[i][k] == 0)
            {
                printf("|");
            }
            else if (maze[i][k] == 1)
            {
                printf(" ");
            }
            else if (maze[i][k] == 2)
            {
                printf("b");
            }
            else if (maze[i][k] == 3)
            {
                printf("c");
            }
            else if (maze[i][k] == 5)
            {
                printf("*");
            }
            else
            {
                printf("%i", maze[i][k]);
            }
        }
        printf("\n");
    }
    printf("\n5 x hit:%i \n", graph->hit);
    sleep_ms((unsigned)delay);
}

int countAdjacents(node *getNode)
{
    int cnt = 0;
    node *ptr = getNode;
    while (ptr)
    {
        cnt++;
        ptr = ptr->next;
    }
    return cnt;
}

import pygame
import time

# Colors definition
WHITE = (255, 255, 255)
GREY = (200, 200, 200)
BLACK = (0, 0, 0)
RED = (255, 50, 50)
GREEN = (0, 255, 0)
BLUE = (50, 50, 255)

UPDATE_TIME_MS = 100

maze_design = [
    "+-+-+-+-+-+-+-+-+",
    "|b  |     |   | |",
    "+ + + +-+ + +-+ |",
    "| | | |     | | |",
    "+ + + +-+-+ + + |",
    "| |     |       |",
    "+ +-+-+-+-+-+-  |",
    "|     | |     | |",
    "+ +-+ + + +-+ + |",
    "|   |     |c  | |",
    "+-+-+-+-+-+-+-+-+",
]

maze_height = len(maze_design)
maze_width = len(maze_design[0])
cell_size = 40

pygame.init()
screen = pygame.display.set_mode((cell_size * maze_width, cell_size * maze_height))
pygame.display.set_caption("DFS Maze Traversal Matching C++")

class Cell:
    def __init__(self, ch, x, y):
        self.ch = ch
        self.x = x
        self.y = y
        self.is_wall = ch in '+-|'
        self.is_start = ch == 'b'
        self.is_end = ch == 'c'
        self.visited = False
        self.on_path = False
        self.dead_end = False

maze = [[Cell(ch, x, y) for x, ch in enumerate(row)] for y, row in enumerate(maze_design)]

def neighbors(cell):
    
    directions = [(-1,0),(1,0),(0,-1),(0,1)]  # same order as C++
    result = []
    for dx, dy in directions:
        nx, ny = cell.x + dx, cell.y + dy
        if 0 <= nx < maze_width and 0 <= ny < maze_height:
            neighbor_cell = maze[ny][nx]
            if not neighbor_cell.is_wall:
                result.append(neighbor_cell)
    return result

def draw_maze(hit_count):
    screen.fill(WHITE)
    for row in maze:
        for cell in row:
            rect = pygame.Rect(cell.x*cell_size, cell.y*cell_size, cell_size, cell_size)
            if cell.is_wall:
                pygame.draw.rect(screen, BLACK, rect)
            elif cell.is_start:
                pygame.draw.rect(screen, GREEN, rect)
            elif cell.is_end:
                pygame.draw.rect(screen, RED, rect)
            elif cell.dead_end:
                pygame.draw.rect(screen, (255, 150, 150), rect)
            elif cell.on_path:
                pygame.draw.rect(screen, BLUE, rect)
            elif cell.visited:
                pygame.draw.rect(screen, GREY, rect)
            else:
                pygame.draw.rect(screen, WHITE, rect)
            pygame.draw.rect(screen, BLACK, rect, 1)
    font = pygame.font.SysFont(None, 24)
    text_surface = font.render(f"Hits (dead ends): {hit_count}", True, BLACK)
    screen.blit(text_surface, (10, 10))
    pygame.display.flip()

stack = []
hit_count = 0

def dfs(cell):
    global hit_count
    pygame.event.pump()
    cell.visited = True
    cell.on_path = True
    stack.append(cell)
    draw_maze(hit_count)
    time.sleep(UPDATE_TIME_MS / 1000.0)
    if cell.is_end:
        return True
    found_path = False
    for neighbor in neighbors(cell):
        if not neighbor.visited:
            if dfs(neighbor):
                found_path = True
                break
    if not found_path:
        # dead end: backtrack here
        hit_count += 1
        cell.dead_end = True
        draw_maze(hit_count)
        time.sleep(UPDATE_TIME_MS / 1000.0)
        cell.on_path = False
        stack.pop()
    return found_path

def find_start_end():
    start_cell = None
    end_cell = None
    for row in maze:
        for cell in row:
            if cell.is_start:
                start_cell = cell
            if cell.is_end:
                end_cell = cell
    return start_cell, end_cell

def main():
    start_cell, end_cell = find_start_end()
    if not start_cell or not end_cell:
        print("Maze must include 'b' (start) and 'c' (end)")
        return
    dfs(start_cell)
    print(f"Dead ends (Hits): {hit_count}")
    running = True
    while running:
        for evt in pygame.event.get():
            if evt.type == pygame.QUIT:
                running = False
    pygame.quit()

if __name__=="__main__":
    main()

// Maze definition constants
const CELL_TYPES = {
    WALL: '+-|',  // Wall characters
    PATH: ' ',    // Path character
    START: 'b',   // Start character
    END: 'c'      // End character
};

// Cell class to represent each cell in the maze
class Cell {
    constructor(ch, x, y) {
        this.ch = ch;
        this.x = x;
        this.y = y;
        this.isWall = CELL_TYPES.WALL.includes(ch);
        this.isStart = ch === CELL_TYPES.START;
        this.isEnd = ch === CELL_TYPES.END;
        this.visited = false;
        this.onPath = false;
        this.deadEnd = false;
    }
}

// Define different maze layouts
const mazes = {
    maze1: [
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
    ],
    maze3: [
        "+-+-+-+-+-+-+-+-+",
        "|b  |     |   | |",
        "+ + + +-+ + +-+ |",
        "| | | |     | | |",
        "+ + + + +-+ + + +",
        "| |     |     | |",
        "+ +-+ +-+-+-+ + |",
        "|     | |     | |",
        "+ +-+ + + +-+ + |",
        "|   |     |c  | |",
        "+-+-+-+-+-+-+-+-+",
    ]
};

// Global variables for the maze solving process
let maze = [];
let mazeHeight = 0;
let mazeWidth = 0;
let hitCount = 0;
let solving = false;
let solvePromise = null;

// DOM elements
const mazeContainer = document.getElementById('maze-container');
const mazeSelect = document.getElementById('maze-select');
const startBtn = document.getElementById('start-btn');
const resetBtn = document.getElementById('reset-btn');
const speedControl = document.getElementById('speed-control');
const speedValue = document.getElementById('speed-value');
const hitCountElement = document.getElementById('hit-count');

// Initialize the application
function init() {
    // Set up event listeners
    mazeSelect.addEventListener('change', loadMaze);
    startBtn.addEventListener('click', startSolving);
    resetBtn.addEventListener('click', resetMaze);
    speedControl.addEventListener('input', updateSpeed);
    
    // Load the default maze
    loadMaze();
}

// Load a maze based on the selected option
function loadMaze() {
    const selectedMaze = mazeSelect.value;
    const mazeLayout = mazes[selectedMaze];
    
    // Reset global variables
    hitCount = 0;
    hitCountElement.textContent = hitCount;
    solving = false;
    startBtn.disabled = false;
    
    // Parse the maze layout
    mazeHeight = mazeLayout.length;
    mazeWidth = mazeLayout[0].length;
    
    // Create the maze grid
    maze = [];
    for (let y = 0; y < mazeHeight; y++) {
        const row = [];
        for (let x = 0; x < mazeWidth; x++) {
            const ch = mazeLayout[y][x];
            row.push(new Cell(ch, x, y));
        }
        maze.push(row);
    }
    
    // Render the maze
    renderMaze();
}

// Render the maze in the DOM
function renderMaze() {
    // Clear the maze container
    mazeContainer.innerHTML = '';
    
    // Set the grid template for the container
    mazeContainer.style.gridTemplateColumns = `repeat(${mazeWidth}, 30px)`;
    
    // Create cells for the maze
    for (let y = 0; y < mazeHeight; y++) {
        for (let x = 0; x < mazeWidth; x++) {
            const cell = maze[y][x];
            const cellElement = document.createElement('div');
            cellElement.className = 'cell';
            cellElement.dataset.x = x;
            cellElement.dataset.y = y;
            
            // Add the appropriate class based on the cell type
            if (cell.isWall) {
                cellElement.classList.add('wall');
            } else if (cell.isStart) {
                cellElement.classList.add('start');
                cellElement.textContent = 'b';
            } else if (cell.isEnd) {
                cellElement.classList.add('end');
                cellElement.textContent = 'c';
            } else {
                cellElement.classList.add('path');
            }
            
            // Update visual state based on algorithm progress
            updateCellVisualState(cellElement, cell);
            
            mazeContainer.appendChild(cellElement);
        }
    }
    
    // Update hit count display
    hitCountElement.textContent = hitCount;
}

// Update the visual state of a cell based on its properties
function updateCellVisualState(cellElement, cell) {
    // Remove all state classes
    cellElement.classList.remove('visited', 'on-path', 'dead-end');
    
    // Add the appropriate class based on the cell's state
    if (cell.deadEnd) {
        cellElement.classList.add('dead-end');
    } else if (cell.onPath) {
        cellElement.classList.add('on-path');
    } else if (cell.visited) {
        cellElement.classList.add('visited');
    }
}

// Get neighbors of a cell
function getNeighbors(cell) {
    const directions = [[-1, 0], [1, 0], [0, -1], [0, 1]]; // Left, Right, Up, Down
    const result = [];
    
    for (const [dx, dy] of directions) {
        const nx = cell.x + dx;
        const ny = cell.y + dy;
        
        if (nx >= 0 && nx < mazeWidth && ny >= 0 && ny < mazeHeight) {
            const neighborCell = maze[ny][nx];
            if (!neighborCell.isWall) {
                result.push(neighborCell);
            }
        }
    }
    
    return result;
}

// Update the visual display of the maze
function updateDisplay() {
    const cells = document.querySelectorAll('.cell');
    
    cells.forEach(cellElement => {
        const x = parseInt(cellElement.dataset.x);
        const y = parseInt(cellElement.dataset.y);
        const cell = maze[y][x];
        
        if (!cell.isWall && !cell.isStart && !cell.isEnd) {
            updateCellVisualState(cellElement, cell);
        }
    });
    
    // Update hit count display
    hitCountElement.textContent = hitCount;
}

// Depth-First Search algorithm implementation
async function dfs(cell) {
    if (!solving) return false;
    
    // Mark cell as visited and on the current path
    cell.visited = true;
    cell.onPath = true;
    
    // Update the display
    updateDisplay();
    
    // Wait for the specified delay based on speed setting
    await sleep(getDelay());
    
    // Check if this is the end cell
    if (cell.isEnd) {
        return true;
    }
    
    // Recursive DFS on neighbors
    let foundPath = false;
    const neighbors = getNeighbors(cell);
    
    for (const neighbor of neighbors) {
        if (!neighbor.visited && solving) {
            if (await dfs(neighbor)) {
                foundPath = true;
                break;
            }
        }
    }
    
    if (!foundPath && solving) {
        // Mark as dead end and backtrack
        hitCount++;
        cell.deadEnd = true;
        cell.onPath = false;
        
        // Update display
        updateDisplay();
        
        // Wait for the delay
        await sleep(getDelay());
    }
    
    return foundPath;
}

// Find start and end cells in the maze
function findStartEnd() {
    let startCell = null;
    let endCell = null;
    
    for (let y = 0; y < mazeHeight; y++) {
        for (let x = 0; x < mazeWidth; x++) {
            if (maze[y][x].isStart) {
                startCell = maze[y][x];
            } else if (maze[y][x].isEnd) {
                endCell = maze[y][x];
            }
        }
    }
    
    return { startCell, endCell };
}

// Start the solving process
async function startSolving() {
    if (solving) return; // Don't start if already solving
    
    solving = true;
    startBtn.disabled = true;
    
    const { startCell, endCell } = findStartEnd();
    
    if (!startCell || !endCell) {
        console.error("Maze must include 'b' (start) and 'c' (end)");
        solving = false;
        startBtn.disabled = false;
        return;
    }
    
    // Reset cell states (but keep walls, start, and end as they are)
    for (let y = 0; y < mazeHeight; y++) {
        for (let x = 0; x < mazeWidth; x++) {
            const cell = maze[y][x];
            if (!cell.isWall && !cell.isStart && !cell.isEnd) {
                cell.visited = false;
                cell.onPath = false;
                cell.deadEnd = false;
            }
        }
    }
    
    // Reset hit count
    hitCount = 0;
    
    // Re-render the maze to reset visual state
    renderMaze();
    
    // Start DFS from the start cell
    await dfs(startCell);
    
    // Solving is complete
    solving = false;
    startBtn.disabled = false;
}

// Reset the maze to its initial state
function resetMaze() {
    solving = false;
    loadMaze(); // Reload the current maze to reset it
}

// Get the current delay based on speed control
function getDelay() {
    // Invert the value so higher numbers mean faster (lower delay)
    return 150 - (speedControl.value * 1.3); // Range: 20ms to 130ms
}

// Update the speed display
function updateSpeed() {
    speedValue.textContent = `${getDelay().toFixed(0)}ms`;
}

// Helper function to create a delay
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

// Initialize the application when the page loads
window.onload = init;
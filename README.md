# 🧩 Maze Solver - DFS Algorithm Visualization

A modern, interactive web application that visualizes the **Depth-First Search (DFS)** algorithm solving maze puzzles in real-time. Built for a college mini-project in Design and Analysis of Algorithms (DAA).

![Maze Solver Preview](https://img.shields.io/badge/Status-Active-success)
![HTML5](https://img.shields.io/badge/HTML5-E34F26?logo=html5&logoColor=white)
![CSS3](https://img.shields.io/badge/CSS3-1572B6?logo=css3&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?logo=javascript&logoColor=black)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Demo](#demo)
- [Technology Stack](#technology-stack)
- [Installation & Usage](#installation--usage)
- [How It Works](#how-it-works)
- [Project Structure](#project-structure)
- [Screenshots](#screenshots)
- [Presentation](#presentation)
- [Future Enhancements](#future-enhancements)
- [License](#license)

## 🔍 Overview

This project is a web-based implementation of a maze solver using the **Depth-First Search (DFS)** algorithm. Originally developed in Python with Pygame, it has been converted to a modern web application with stunning visual design and real-time algorithm visualization.

The application demonstrates how the DFS algorithm explores a maze, backtracks when hitting dead ends, and eventually finds a path from start to finish.

## ✨ Features

- **Real-time Visualization**: Watch the DFS algorithm solve mazes step-by-step
- **Multiple Mazes**: Choose from different maze layouts with varying complexity
- **Speed Control**: Adjust the visualization speed from slow motion to fast
- **Modern UI**: Beautiful dark theme with glassmorphism effects and gradient colors
- **Color-Coded Cells**:
  - 🟢 **Green**: Start position
  - 🔴 **Red**: End position
  - 🔵 **Blue**: Current path being explored
  - ⚫ **Gray**: Visited cells
  - 🔴 **Pink**: Dead ends (backtracked)
  - ⬛ **Black**: Walls
- **Dead End Counter**: Tracks the number of times the algorithm backtracks
- **Responsive Design**: Works on desktop, tablet, and mobile devices

## 🎮 Demo

Simply open `index.html` in any modern web browser to see the maze solver in action!

## 🛠️ Technology Stack

- **HTML5**: Structure and semantic markup
- **CSS3**: Modern styling with gradients, glassmorphism, and animations
- **JavaScript (ES6+)**: DFS algorithm implementation and DOM manipulation
- **Google Fonts**: Inter font family for premium typography

**No frameworks or libraries required** - Pure vanilla web technologies!

## 📥 Installation & Usage

### Method 1: Direct Download

1. Clone or download this repository
```bash
git clone https://github.com/yourusername/maze-solver-dfs.git
cd maze-solver-dfs
```

2. Open `index.html` in your web browser
   - Double-click the file, or
   - Right-click → Open with → Your browser

### Method 2: Local Server (Optional)

For a better development experience:

```bash
# Using Python
python -m http.server 8000

# Using Node.js
npx serve

# Then open http://localhost:8000 in your browser
```

### How to Use

1. **Select a Maze**: Choose from "Sample Maze 1" or "Sample Maze 3" in the dropdown
2. **Adjust Speed**: Use the speed slider to control visualization speed (1-100ms)
3. **Start Solving**: Click the "▶️ Start Solving" button to begin
4. **Watch the Algorithm**: Observe as the DFS algorithm explores the maze
5. **Reset**: Click "🔄 Reset" to reload the maze and try again

## 🧠 How It Works

### DFS Algorithm Overview

The Depth-First Search algorithm works by:

1. Starting at the initial position (marked 'b')
2. Marking the current cell as visited
3. Exploring neighbors (up, down, left, right) recursively
4. If the end is found, the path is complete
5. If a dead end is reached, backtrack and try a different path
6. Continue until the end position (marked 'c') is found

### Implementation Details

- **Cell Class**: Represents each cell in the maze with properties (position, type, visited status)
- **Async Visualization**: Uses JavaScript `async/await` and `setTimeout` for animated visualization
- **Grid Rendering**: Dynamic grid layout created with CSS Grid
- **State Management**: Tracks visited cells, current path, and dead ends

## 📁 Project Structure

```
maze-solver-dfs/
│
├── index.html          # Main HTML file
├── style.css           # CSS styling with modern design
├── script.js           # JavaScript DFS implementation
├── README.md           # Project documentation (this file)
│
├── assets/             # Additional files
│   ├── maze_with_dfs.c # Original C implementation
│   ├── new.py          # Original Python implementation
│   ├── sample.txt      # Sample maze layouts
│   ├── sample1.txt
│   └── sample2.txt
│
└── .gitignore          # Git ignore file
```

## 📸 Screenshots

### Modern UI Design
![Maze Solver Initial State](assets/screenshot-initial.png)
*Dark theme with glassmorphism and gradient effects*

### Algorithm in Action
![DFS Solving Process](assets/screenshot-solving.png)
*Real-time visualization of the DFS algorithm exploring the maze*

## 🎤 Presentation

View our detailed project presentation on Canva:

🔗 **[Maze Solver - Project Presentation](https://www.canva.com/design/DAG56xbwWRQ/PoA2l0wsSq-Njigr6PohHA/view?utm_content=DAG56xbwWRQ&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=h19b3088bc4)**

The presentation covers:
- Project overview and objectives
- Algorithm explanation
- Implementation details
- UI/UX design choices
- Results and demonstrations

## 🔮 Future Enhancements

Potential improvements for future versions:

- [ ] Additional algorithms (BFS, A*, Dijkstra)
- [ ] Custom maze generator
- [ ] Maze editor (draw your own mazes)
- [ ] Path comparison between algorithms
- [ ] Step-by-step mode with manual control
- [ ] Performance metrics (time complexity, space complexity)
- [ ] Save/load maze layouts
- [ ] Animation export (GIF/video)

## 📝 License

This project is open source and available for educational purposes. Feel free to use, modify, and distribute as needed for learning and academic projects.

---

## 👨‍💻 Author

**College Mini Project - Design and Analysis of Algorithms (DAA)**

If you found this project helpful, please ⭐ star this repository!

---

### 🙏 Acknowledgments

- Original Python/Pygame implementation converted to web
- Inspired by classic pathfinding algorithm visualizations
- UI design influenced by modern web design trends (glassmorphism, dark themes)

---

<div align="center">
  <sub>Built with ❤️ for learning and education</sub>
</div>
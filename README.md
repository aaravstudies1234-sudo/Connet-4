Connect 4 – C++ Terminal-Based Game
This repository contains a fully functional implementation of the classic Connect 4 game written in C++. The project focuses on clean code design, logical structuring, and the use of fundamental programming concepts such as arrays, functions, loops, and simple data structures. It is designed as a beginner-level project that demonstrates how simple turn-based games can be developed using only the C++ standard library.

Overview
Connect 4 is a two-player game played on a 6×7 grid. Players take turns dropping pieces into columns, attempting to form a line of four connected tokens either horizontally, vertically, or diagonally.
This implementation provides a human vs computer mode along with a robust board-rendering and win-detection system.

Key Features
Human vs Computer Gameplay
The player competes against a computer opponent that selects valid moves and follows the rules of Connect 4. The AI uses a simple selection mechanism designed for predictable and fair gameplay.
Dynamic Board Rendering
The game displays the board in a clear and readable format after every move. All updates occur in real time within the terminal.
Full Turn Undo System
The project includes an undo mechanism that reverts the last complete turn.

This means:
The last player move is undone
The last computer move is undone
The board returns to the exact previous state
This feature is implemented using a history log of moves stored in a vector.
Input Validation
The game ensures that user input is correctly handled. Invalid column numbers, full column selections, and incorrect data types are safely managed without crashing the program.
Modular Code Structure
All functional components are separated into individual functions for clarity and maintainability. These include board printing, player input handling, computer move generation, win checking, and undo handling.
Implementation Details
Board Representation
The game board is represented using a fixed-size 2D character array:
Move History
A structure storing row and column values is used to track each move.
A vector of such structures enables efficient reversal of moves during the undo process.
Win Detection

The code includes comprehensive checks for:
Horizontal alignment
Vertical alignment
Both diagonal directions
These checks ensure accurate detection of winning states.

Game Loop
The main loop manages the flow of turns, move validation, win checks, and optional undo requests. Execution continues until a win or draw condition is reached.

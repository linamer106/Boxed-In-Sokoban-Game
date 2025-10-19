# Boxed-In-Sokoban-Game

A console-based puzzle game in C, where you push boxes onto target squares in a 10x10 grid. This project demonstrates array manipulation, modular functions, and user input handling in C.

## 🎮 Gameplay

Move the player X and push boxes O onto targets *. Undo moves with z. The game ends when all boxes are on target squares.

Key	Action:
w:	Move Up
a:	Move Left
s: Move Down
d:	Move Right
z:	Undo Last Move

Example board:

##########
/#        #
/#  X O * #
/#        #
##########

## ⚡ Features

ASCII grid rendering of the game board.

Undo functionality with move tracking.

Dynamic handling of boxes and targets.

Clear modular C code with functions for each task.

## 💻 How to Run

**Compile the code:**

gcc -o boxedin boxed_in.c

**Run the game:**

./boxedin


Follow the on-screen instructions to play.

## 🏆 Learning Outcomes

Working with 2D arrays and grid-based logic.

Modular function design in C.

Handling user input safely.

Implementing game logic and undo mechanics.

# Sudoku
Recreating the famous logic-based, combinatorial number-placement puzzle.

## User's Guide

### Rules

The game contains the same standard rules:

* Each row must contain the numbers from 1 to 9, without repetition
* Each column must contain the numbers from 1 to 9, without repetition
* The digits can only occur once per block (nonet)

### Gameplay

Once the game started, the window displays the **Menu** where 
the user has an option to START or LOAD the game.

* **MENU**
    * START - moves the screen to **Complexity** screen
    * LOAD - loads the previously saved game
* **COMPLEXITY**
    * EASY - prepares an easy level puzzle
    * MEDIUM - prepares a medium level puzzle
    * DIFFICULT - prepares a difficult level puzzle
    
After the level is selected, the program displays the **game** screen with a grid 
and buttons

* Menu - to go back to menu
* Check - to check if the puzzle is solved correctly
* Hint - to reveal a solution of the selected cell
* Save - to save the game
* Next - to display the next grid (same complexity level)
* Solve - to display solved puzzle

**To write the numbers in the particular cell, select the cell you desire and 
write with a keyboard the numbers from 1-9.**

## How to Run

### Prerequisites:

1. [Visual Studio (2019+)](https://visualstudio.microsoft.com/)
2. [SDL (2.0.22+)](https://github.com/libsdl-org/SDL/releases/tag/release-2.24.0)
3. [SDL_ttf (2.20.1](https://github.com/libsdl-org/SDL_ttf)

### Setup

1. Clone the repository
2. Configure SDL and SDL_ttf libraries to your Visual Studio
3. Run the program

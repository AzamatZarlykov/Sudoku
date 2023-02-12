# Sudoku
Recreating the famous logic-based, combinatorial number-placement puzzle - Sudoku.

## Features

The following are the key features of the project:

* Multiple levels of difficulty: Users can choose from different levels: Easy, Middle, Difficult
* Timer: The game includes a timer to track the time taken to solve the puzzle, allowing users to keep track of their progress.
* Solution checker: Users can check their solution against the correct answer and receive feedback on their progress.
* Hints: The game provides the option to get a hint for the selected square if the user is stuck.
* Save and Load: Users can save their current puzzle and continue playing at a later time, or load a previously saved puzzle.
* Next puzzle: The game also provides the option to move to the next puzzle.
* Solve puzzle: If the user is struggling, they can opt to have the puzzle solved for them.

## Gameplay

Here are some screenshots of the Sudoku gameplay:

![Screenshot 1](/img/menu_levels.png)
This screenshot shows the main menu of the Sudoku game on the left. It includes the `'Start'` and `'Load'` buttons. On the right side, it is the window which appears after starting the game where the player can select the difficulty level.

![Screenshot 2](/img/gameplay_load.png)
This screenshot shows the gameplay once the difficulty is selected, left image, and the loaded game, right image. 

## Technologies

1. C++ programming language
2. [Visual Studio (2019+)](https://visualstudio.microsoft.com/)
3. [SDL (2.0.22+)](https://github.com/libsdl-org/SDL/releases/tag/release-2.24.0)
4. [SDL_ttf (2.20.1](https://github.com/libsdl-org/SDL_ttf)

## Setup

1. Clone the repository
```bash
git clone https://github.com/AzamatZarlykov/Sudoku.git
```
2. Configure SDL and SDL_ttf libraries to your Visual Studio:
* In Visual Studio, go to Project Properties > Linker > Input > Additional Dependencies and add the following:
    * SDL2.lib
    * SDL2main.lib
    * SDL2_ttf.lib
* In Project Properties > C/C++ > Additional Include Directories, add the include directories for SDL and SDL_ttf
3. Run the application in Visual Studio
    * Open the solution file sudoku.sln in Visual Studio
    * Select the build configuration (Debug or Release) and target architecture (x86 or x64)
    * Press the Start button to run the application

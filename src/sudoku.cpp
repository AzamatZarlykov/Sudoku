#include "../include/sudoku.hpp"

Sudoku::Sudoku() {
	// instantiating the grid of cells
	for (int i = 0; i < SIZE; i++)
	{
		// construct a vector of ints with the given default value
		vector<Cell> v;
		for (int j = 0; j < SIZE; j++) {
			v.push_back(Cell());
		}

		// push back above one-dimensional vector
		grid.push_back(v);
	}

	// parser = make_unique<Parser>();
	generator = make_unique<Generator>();
	view = make_unique<View>();
}

void Sudoku::print_grid() const {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
}


void Sudoku::Sudoku::create_interface_layout()
{

}


int Sudoku::play()
{
	generator->generate(level, grid);
	print_grid();


	create_interface_layout();

	SDL_Event event;
	bool game_running = true;
	while (game_running) {
		// register mouse press 
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_running = false;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
			}
			else if (event.type == SDL_KEYDOWN) {
			}
		}
	}
	return 0;
}

/*
	Sudoku functionalities
	1) GUI
	2) Generate Unsolved Sudoku puzzles (instead of reading from txt)
	3) Save/Load (professor)
	4) Select complexity (Easy/Middle/Hard)
	5) SOLVE btn - solves the puzzle
	6) Get Hint for particular square
	7) Next puzzle
*/


#include "../include/sudoku.hpp"

Sudoku::Sudoku() 
{
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

void Sudoku::print_grid() const 
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
}

void Sudoku::set_selected_cell()
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++) {
			if (grid[row][col].get_editable()) {
				selected.y = row;
				selected.x = col;
				grid[row][col].set_selected(true);
				return;
			}
		}
	}
}

int Sudoku::play()
{
	generator->generate(level, grid);
	print_grid();

	// create a game interface
	view->create_interface_layout(grid);

	// Set first current cell selected
	set_selected_cell();

	time_t start_timer = 0;
	time(&start_timer);
	// Enable text input
	SDL_StartTextInput();
	SDL_Event event;

	bool game_running = true;
	while (game_running) {
		// handle events that are in the queue
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_running = false;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
			}
			else if (event.type == SDL_KEYDOWN) {
			}
		}
		

		view->render(grid, start_timer);

		// Slow down program becuase it doesn't need to run very fast
		SDL_Delay(10);
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


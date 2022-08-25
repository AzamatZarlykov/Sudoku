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
	// initialize the buttons 
	for (int i = 0; i < 5; i++) {
		buttons.push_back(make_unique<Button>(button_names[i]));
	}
	load = make_unique<Button>("Load");

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

void Sudoku::check_buttons_selection(const SDL_Event* event,bool& load_b)
{
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->identify_mouse_event(event) == ButtonState::BUTTON_MOUSE_DOWN) {
			if (buttons[i]->get_name() == "Check") {
				bool_buttons[0] = true;
			}
			else if (buttons[i]->get_name() == "Hint") {
				bool_buttons[1] = true;
			}
			else if (buttons[i]->get_name() == "Save") {
				bool_buttons[2] = true;
			}
			else if (buttons[i]->get_name() == "Next") {
				bool_buttons[3] = true;
			}
			else if (buttons[i]->get_name() == "Solve") {
				bool_buttons[4] = true;
			}
		}
	}

	if (load->identify_mouse_event(event) == ButtonState::BUTTON_MOUSE_DOWN) {
		load_b = true;
	}
}

void Sudoku::check_cell_selection(const SDL_Event* event)
{
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			if (grid[row][col].get_editable()) {
				if (grid[row][col].identify_mouse_event(event) == ButtonState::BUTTON_MOUSE_DOWN) {
					// unselect the previous selected
					grid[selected.y][selected.x].set_selected(false);	
					// store selected positions
					selected.y = row;
					selected.x = col;
					grid[row][col].set_selected(true);
				}
			}
		}
	}
}

bool Sudoku::check_grid(bool& check_pressed) const 
{
	check_pressed = true;
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			if (!grid[row][col].is_correct()) {
				return false;
			}
		}
	}
	return true;
}

void Sudoku::handle_buttons_selection(bool& load_b, bool& check_pressed, time_t& check_time, 
	time_t& current_time, bool& solved)
{
	// Check
	if (bool_buttons[0]) {
		bool_buttons[0] = false;
		// check the grid
		bool correct = check_grid(check_pressed);
		// start the time after the check button pressed
		time(&check_time);
		if (check_pressed) {
			// display the outcome on the view for 2 seconds
			if (difftime(time(NULL), check_time) < DISPLAY_TIME) {

				if (correct) {
					view->display_success(buttons[0]);
					solved = true;
				}
				else {
					view->display_failure(buttons[0]);
				}
			}
			else {
				check_pressed = false;
			}
		}
		else {
			view->set_default_check_button(buttons[0]);
		}
	}
	// Hint
	else if (bool_buttons[1]) {

		bool_buttons[1] = false;
	}
	// Save
	else if (bool_buttons[2]) {

		bool_buttons[2] = false;
	}
	// Next
	else if (bool_buttons[3]) {
		// generate new puzzle
		generator->generate(level, grid);
		// remove previous selected 
		grid[selected.y][selected.x].set_selected(false);
		// find new selected cell
		set_selected_cell();
		// reset timer
		time(&current_time);

		bool_buttons[3] = false;
	}
	// Solve
	else if (bool_buttons[4]) {

		bool_buttons[4] = false;
	}
	// Load
	else if (load_b) {

		load_b = false;
	}
}

int Sudoku::play()
{
	generator->generate(level, grid);
	print_grid();
	// create a game interface
	view->create_interface_layout(grid, buttons);
	// Set first current cell selected
	set_selected_cell();

	time_t current_timer = 0;
	time_t check_time = 0;
	time(&current_timer);
	// Enable text input
	SDL_StartTextInput();
	SDL_Event event;

	bool load_b = false;
	bool solved = false;
	bool check_pressed = false;


	bool game_running = true;
	while (game_running) {
		// handle events that are in the queue
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_running = false;
			}
			else if (event.type == SDL_KEYDOWN) {
			}
			check_buttons_selection(&event, load_b);
			check_cell_selection(&event);
			grid[selected.y][selected.x].handle_keyboard_event(&event, view->get_number_textures());
		}
		// handle button presses
		handle_buttons_selection(load_b, check_pressed, check_time, current_timer, solved);
		view->render(grid, buttons, current_timer, solved);

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


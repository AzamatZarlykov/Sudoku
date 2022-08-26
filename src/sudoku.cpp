#include "../include/sudoku.hpp"

Sudoku::Sudoku() 
{
	initialize_grid(grid);
	// initialize the buttons
	initialize_buttons();

	// parser = make_unique<Parser>();
	generator = make_unique<Generator>();
	view = make_unique<View>();
	writer = make_unique<Writer>();
	reader = make_unique<Reader>();
}

void Sudoku::initialize_buttons()
{
	// game buttons
	for (int i = 0; i < 5; i++) {
		game_buttons.push_back(make_unique<Button>(game_button_names[i]));
	}
	// menu buttons
	for (int i = 0; i < 2; i++) {
		menu_buttons.push_back(make_unique<Button>(menu_button_names[i]));
	}
	// complexity buttons 
	for (int i = 0; i < 3; i++) {
		complexity_buttons.push_back(make_unique<Button>(complexity_names[i]));
	}
}

void Sudoku::initialize_grid(vector<vector<Cell>>& grid)
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
	if (gs == GameState::GAME) {
		for (int i = 0; i < game_buttons.size(); i++) {
			if (game_buttons[i]->identify_mouse_event(event) == ButtonState::BUTTON_MOUSE_DOWN) {
				if (game_buttons[i]->get_name() == "Check") {
					bool_game_buttons[0] = true;
				}
				else if (game_buttons[i]->get_name() == "Hint") {
					bool_game_buttons[1] = true;
				}
				else if (game_buttons[i]->get_name() == "Save") {
					bool_game_buttons[2] = true;
				}
				else if (game_buttons[i]->get_name() == "Next") {
					bool_game_buttons[3] = true;
				}
				else if (game_buttons[i]->get_name() == "Solve") {
					bool_game_buttons[4] = true;
				}
			}
		}
		for (int i = 0; i < game_buttons.size(); i++) {
			if (bool_game_buttons[i]) {
				any_button_pressed = true;
				return;
			}
		}
	}
	else if (gs == GameState::MENU) {
		for (int i = 0; i < menu_buttons.size(); i++) {
			if (menu_buttons[i]->identify_mouse_event(event) == ButtonState::BUTTON_MOUSE_DOWN) {
				if (menu_buttons[i]->get_name() == "Start") {
					bool_menu_buttons[0] = true;
				}
				else if (menu_buttons[i]->get_name() == "Load") {
					bool_menu_buttons[1] = true;
				}
			}
		}
	}
	else if (gs == GameState::COMPLEXITY) {
		for (int i = 0; i < complexity_buttons.size(); i++) {
			if (complexity_buttons[i]->identify_mouse_event(event) == ButtonState::BUTTON_MOUSE_DOWN) {
				if (complexity_buttons[i]->get_name() == "Easy") {
					bool_complexity_buttons[0] = true;
				}
				else if (complexity_buttons[i]->get_name() == "Medium") {
					bool_complexity_buttons[1] = true;
				}
				else {
					bool_complexity_buttons[2] = true;
				}
			}
		}
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

void Sudoku::handle_check_button(bool& check_pressed, time_t& check_time)
{
	// check the grid
	bool correct = check_grid(check_pressed);
	// start the time after the check button pressed
	time(&check_time);
	if (check_pressed) {
		// display the outcome on the view for 2 seconds
		if (difftime(time(NULL), check_time) < DISPLAY_TIME) {

			if (correct) {
				view->display_message(game_buttons[0], 0);
				if (view->get_finish_time() == 0) {
					view->set_finish_time(current_timer);
				}
			}
			else {
				view->display_message(game_buttons[0], 1);

			}
		}
		else {
			check_pressed = false;
		}
	}
	else {
		view->set_default_texture(game_buttons[0], 0);
	}
}

void Sudoku::repopulate_grid(vector<vector<Cell>>& new_grid)
{
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			int val = new_grid[row][col].get_number();
			grid[row][col].set_noneditable_square(val);
			// this cell is a non-editable cell
			if (val != 0) {
				grid[row][col].set_editable(false);
			}
			else {
				grid[row][col].unset();
				grid[row][col].set_solution(new_grid[row][col].get_solution());
			}
			view->load_cell_texture(grid[row][col], val);
		}
	}
}

void Sudoku::handle_next_button(bool& next_b)
{
	// reset the timer
	view->reset_finish_time();

	// new grid to store
	vector<vector<Cell>> new_grid;
	initialize_grid(new_grid);
	// generate new puzzle
	generator->generate(level, new_grid);

	// remove previous selected 
	grid[selected.y][selected.x].set_selected(false);
	// store the new grid to a grid
	repopulate_grid(new_grid);
	// find new selected cell
	set_selected_cell();

	cout << "New generated grid: " << endl;
	print_grid();

	// reset timer
	time(&current_timer);

	// reset the texture in the Check Button
	view->set_default_texture(game_buttons[0], 0);
}

void Sudoku::handle_solve_button()
{
	// set the solutions for editable squares
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			// reveal the solutions for the cells
			if (grid[row][col].get_number() == 0) {
				grid[row][col].set_number(grid[row][col].get_solution());
				view->load_cell_texture(grid[row][col], grid[row][col].get_number());
			}
		}
	}
}

void Sudoku::handle_hint_button()
{
	int x = selected.x;
	int y = selected.y;
	grid[y][x].set_number(grid[y][x].get_solution());
	view->load_cell_texture(grid[y][x], grid[y][x].get_number());
}

void Sudoku::handle_save_button(bool& saved_pressed, time_t& saved_time)
{
	saved_pressed = true;

	writer->write(grid, current_timer);
	
	time(&saved_time);
	if (saved_pressed) {
		if (difftime(time(NULL), saved_time) < DISPLAY_TIME) {
			view->display_message(game_buttons[2], 2);
		}
		else {
			saved_pressed = false;
		}
	}
	else {
		view->set_default_texture(game_buttons[2], 2);
	}
}

void Sudoku::handle_load_button()
{
	// reader->read(grid, current_timer);
}

void Sudoku::handle_buttons_selection(bool& load_b, bool& check_pressed, bool& saved_pressed,
	time_t& check_time, time_t& saved_time)
{
	// Check
	if (bool_game_buttons[0]) {
		handle_check_button(check_pressed, check_time);
		bool_game_buttons[0] = false;
	}
	// Hint
	else if (bool_game_buttons[1]) {
		handle_hint_button();
		bool_game_buttons[1] = false;
	}
	// Save
	else if (bool_game_buttons[2]) {
		handle_save_button(saved_pressed, saved_time);
		bool_game_buttons[2] = false;
	}
	// Next
	else if (bool_game_buttons[3]) {
		handle_next_button(bool_game_buttons[3]);
		bool_game_buttons[3] = false;
	}
	// Solve
	else if (bool_game_buttons[4]) {
		handle_solve_button();
		bool_game_buttons[4] = false;
	}
	// Load
	else if (load_b) {
		handle_load_button();
		load_b = false;
	}
}

int Sudoku::play()
{
	generator->generate(level, grid);
	print_grid();

	// create a game interface
	view->create_interface_layout(grid, game_buttons, menu_buttons, complexity_buttons);
	// Set first current cell selected
	set_selected_cell();

	time_t check_time = 0;
	time_t saved_time = 0;
	// Enable text input
	SDL_StartTextInput();
	SDL_Event event;

	bool load_b = false;
	bool check_pressed = false;
	bool saved_pressed = false;

	bool game_running = true;
	while (game_running) {
		if (gs == GameState::GAME) {
			time(&current_timer);
		}

		// handle events that are in the queue
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_running = false;
			}
			else if (event.type == SDL_TEXTINPUT) {
				if (atoi(event.text.text) && any_button_pressed) {
					view->reset_button_textures(game_buttons);
				}
			}

			check_buttons_selection(&event, load_b);
			if (gs == GameState::GAME) {	// only in the game
				check_cell_selection(&event);
				grid[selected.y][selected.x].handle_keyboard_event(&event, view->get_number_textures());
			}
		}
		// handle button presses
		handle_buttons_selection(load_b, check_pressed, saved_pressed, check_time, saved_time);
		if (gs == GameState::GAME) {
			view->render_game(grid, game_buttons, current_timer);
		}
		else if (gs == GameState::MENU) {
			view->render_menu(menu_buttons);
		}
		else {
			view->render_complexity(complexity_buttons);
		}

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


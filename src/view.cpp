#include "../include/view.hpp"

void View::CHECKFORERROR(bool error, string msg) 
{
	if (error) {
		cerr << ("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(1);
	}
}

View::View()
{
	/* initialize sdl */
	CHECKFORERROR(SDL_Init(SDL_INIT_VIDEO), SDL_GetError());

	/* initialize window and renderer */
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC, &_window, &_renderer);	
	CHECKFORERROR(_window == NULL, SDL_GetError());
	CHECKFORERROR(_renderer == NULL, SDL_GetError());

	/* initialize font */
	CHECKFORERROR(TTF_Init() == -1, TTF_GetError());
	_font = TTF_OpenFont("./font/font.ttf", FONT_SIZE);
	CHECKFORERROR(_font == NULL, TTF_GetError());

	SDL_SetWindowTitle(_window, "Sudoku");
}

View::~View()
{
	// clean
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);

	// free texture
	for (int i = 0; i < 10; i++) {
		if (i < 6) {
			if (buttons_texture[i] != nullptr) {
				SDL_DestroyTexture(buttons_texture[i]);
				buttons_texture[i] = nullptr;
			}
		}
		if (num_texture[i] != nullptr) {
			SDL_DestroyTexture(num_texture[i]);
			num_texture[i] = nullptr;
		}
	}

	// Free font
	TTF_CloseFont(_font);
	_font = nullptr;

	SDL_Quit();
	TTF_Quit();
}

SDL_Texture** View::get_number_textures()
{
	return num_texture;
}

void View::load_texture(SDL_Texture*& texture, const char* text, SDL_Color& font_color)
{
	SDL_Surface * text_surface = TTF_RenderText_Solid(_font, text, font_color);
	CHECKFORERROR(text_surface == NULL, SDL_GetError());

	texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
	CHECKFORERROR(texture == NULL, SDL_GetError());

	SDL_FreeSurface(text_surface);
}



void View::prepare_texture(vector<unique_ptr<Button>>& buttons)
{
	// Set background color 
	SDL_Color font_color = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // black

	// texture for space
	load_texture(num_texture[0], " ", font_color);
	// load possible textures: 1-9 and space
	for (int i = 1; i < 10; i++) {
		const char val[] = { '0' + i, '\0' };;
		load_texture(num_texture[i], val, font_color);
	}

	// load textures for buttons
	for (int i = 0; i < buttons.size(); i++) {
		load_texture(buttons_texture[i], buttons[i]->get_name(), font_color);
	}
	load_texture(buttons_texture[5], "Load", font_color);

	const char* outcomes[2] = {"Correct!", "Wrong!"};
	// load results texture
	for (int i = 0; i < 2; i++) {
		load_texture(result_texture[i], outcomes[i], font_color);
	}
}




void View::prepare_stopwatch(int& row, int& col, int& b_width,
	int& b_height)
{

	b_width = GRID_WIDTH - 2 * THICK_B;
	b_height = (HEIGHT - 6 * THIN_B - 5 * THICK_B) / 10;

	row += THICK_B;
	col += THICK_B;

	SDL_Rect button = { row, col, b_width, b_height };
	timer.set_button_rect(button);
}



void View::prepare_grid(vector<vector<Cell>>& grid, int& row, int& col, int& b_width,
	int& b_height)
{
	b_width = (GRID_WIDTH - 6 * THIN_B - 4 * THICK_B) / SIZE;

	// Carry on from previous starting row
	row += b_height;
	int c_row = row;

	// Set cell button position and dimensions
	for (int g_row = 0; g_row < SIZE; g_row++)
	{
		// Add to starting row
		if (g_row == 0) c_row += THICK_B;
		else if (g_row % 3 == 0) c_row += b_height + THICK_B;
		else c_row += b_height + THIN_B;

		// Reset starting column
		col = 0;

		for (int g_col = 0; g_col < SIZE; g_col++)
		{
			// Add to starting column
			if (g_col == 0) col += THICK_B;
			else if (g_col % 3 == 0) col += b_width + THICK_B;
			else col += b_width + THIN_B;

			// Set button position and dimensions
			SDL_Rect button = { col, c_row, b_width, b_height };
			grid[g_row][g_col].set_button_rect(button);
		}
	}

	col += b_width + THICK_B;
}

void View::prepare_buttons(int& row, int& col, int& b_width, int& b_height, 
	vector<unique_ptr<Button>>& buttons)
{
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->set_texture(buttons_texture[i]);
	}

	b_width = WIDTH - GRID_WIDTH - THICK_B;
	row += THICK_B + 235;

	for (int i = 0; i < buttons.size(); i++) {
		SDL_Rect rect = { col, row + i * 96, b_width, b_height };
		buttons[i]->set_button_rect(rect);
	}
}


void View::load_cell_texture(Cell& cell, int val)
{
	cell.set_texture(num_texture[val]);
	cell.center_val();
}


void View::create_interface_layout(vector<vector<Cell>>& grid, vector<unique_ptr<Button>>& buttons)
{
	// pre load the texture
	prepare_texture(buttons);

	int start_row = 0;
	int start_col = 0;
	int b_height = 0;
	int b_width = 0;

	// left side
	prepare_stopwatch(start_row, start_col, b_width, b_height);
	prepare_grid(grid, start_row, start_col, b_width, b_height);
	// right side
	prepare_buttons(start_row, start_col, b_width, b_height, buttons);

	// set grid texture
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			int val = grid[row][col].get_number();
			load_cell_texture(grid[row][col], val);
		}
	}
}


void View::render_grid(vector<vector<Cell>>& grid)
{
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			grid[row][col].render_button(_renderer);
			grid[row][col].center_val();
			grid[row][col].render_texture(_renderer);
		}
	}
}

void View::render_stopwatch(time_t& start_timer)
{
	time_t difference = 0;
	difference = time(NULL) - start_timer;
	
	tm formatted_time;
	if (finish_time != 0) {
		localtime_s(&formatted_time, &finish_time);
	}
	else {
		localtime_s(&formatted_time, &difference);
	}

	if (formatted_time.tm_hour != 0) {
		formatted_time.tm_hour = 0;
	}
	
	char t[80];
	strftime(t, sizeof(t), "%H:%M:%S", &formatted_time);

	SDL_Texture* timer_texture = nullptr;
	SDL_Color font_color = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // black
	load_texture(timer_texture, t, font_color);

	timer.set_texture(timer_texture);
	timer.render_button(_renderer);
	timer.center_val();
	timer.render_texture(_renderer);

	SDL_DestroyTexture(timer_texture);
	timer_texture = nullptr;
}

void View::render_buttons(vector<unique_ptr<Button>>& buttons)
{
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->render_button(_renderer);
		buttons[i]->center_val();
		buttons[i]->render_texture(_renderer);
	}
}

void View::render(vector<vector<Cell>>& grid, vector<unique_ptr<Button>>& buttons, time_t& start_timer)
{
	// Select the color for drawing. It is set to black here.
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	// Clear screen with rendered colour
	SDL_RenderClear(_renderer);

	render_grid(grid);
	
	render_stopwatch(start_timer);
	
	render_buttons(buttons);

	SDL_RenderPresent(_renderer);
}


void View::display_success(unique_ptr<Button>& button)
{
	// Set colour to green
	SDL_Color colour = { 91, 191, 116, SDL_ALPHA_OPAQUE };

	// Set render colour to green
	SDL_SetRenderDrawColor(_renderer, colour.r, colour.g, colour.b, SDL_ALPHA_OPAQUE);

	// Set texture to "Correct!"
	button->set_texture(result_texture[0]);

	// Set mouse down colour to green
	button->set_mousedown_color(colour);
}

void View::display_failure(unique_ptr<Button>& button)
{
	// Set colour to red
	SDL_Color colour = { 200, 73, 46, SDL_ALPHA_OPAQUE };

	// Set render colour to red
	SDL_SetRenderDrawColor(_renderer, colour.r, colour.g, colour.b, SDL_ALPHA_OPAQUE);

	// Set texture to "Wrong!"
	button->set_texture(result_texture[1]);

	// Set mouse down colour to red
	button->set_mousedown_color(colour);
}

void View::reset_check_button(unique_ptr<Button>& button)
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

	button->set_texture(buttons_texture[0]);

	SDL_Color color = { 255,255,255, SDL_ALPHA_OPAQUE };
	button->set_mousedown_color(color);
}

void View::set_default_check_button(unique_ptr<Button>& button)
{
	// Set texture to "Check"
	button->set_texture(buttons_texture[0]);

	// set color to black 
	SDL_Color colour = { 0, 0, 0, SDL_ALPHA_OPAQUE };

	// Set render colour to black
	SDL_SetRenderDrawColor(_renderer, colour.r, colour.g, colour.b, colour.a);
}

const time_t& View::get_finish_time() const
{
	return finish_time;
}

void View::reset_finish_time()
{
	finish_time = 0;
}

void View::set_finish_time(time_t& start_timer)
{
	finish_time = time(NULL) - start_timer;
}
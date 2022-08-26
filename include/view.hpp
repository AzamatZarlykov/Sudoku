#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"
#include "cell.hpp"

#undef main

using namespace std;

class View
{
public:
	View();
	~View();

	void render_game(vector<vector<Cell>>&, vector<unique_ptr<Button>>&, time_t&);
	void render_menu(vector<unique_ptr<Button>>&);
	void render_complexity(vector<unique_ptr<Button>>&);

	void create_interface_layout(vector<vector<Cell>>&, vector<unique_ptr<Button>>&,
		vector<unique_ptr<Button>>&, vector<unique_ptr<Button>>&);

	void load_texture(SDL_Texture*&, const char*, SDL_Color&);
	void load_cell_texture(Cell&, int);

	void display_message(unique_ptr<Button>&, int);
	void set_default_texture(unique_ptr<Button>&, int);

	void set_finish_time(time_t&);
	void reset_finish_time();

	void reset_button_textures(vector<unique_ptr<Button>>&);

	const time_t& get_finish_time() const;

	SDL_Texture** get_number_textures();
private:
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	TTF_Font* _font;

	SDL_Texture* num_texture[10];
	SDL_Texture* game_buttons_texture[6];
	SDL_Texture* menu_buttons_texture[6];
	SDL_Texture* complexity_buttons_texture[6];
	SDL_Texture* result_texture[3];

	// Stopwatch
	Button timer;

	time_t finish_time;


	void CHECKFORERROR(bool, string);

	void render_title();
	void render_grid(vector<vector<Cell>>&);
	void render_stopwatch(time_t&);
	void render_buttons(vector<unique_ptr<Button>>&);
	void render_button(unique_ptr<Button>&);

	void prepare_stopwatch(int&, int&, int&, int&);
	void prepare_grid(vector<vector<Cell>>&, int&, int&, int&, int&);
	void prepare_game_buttons(int&, int&, int&, int&, vector<unique_ptr<Button>>&);
	void prepare_menu_buttons(vector<unique_ptr<Button>>&);
	void prepare_texture(vector<unique_ptr<Button>>&, vector<unique_ptr<Button>>&, 
		vector<unique_ptr<Button>>&);
};


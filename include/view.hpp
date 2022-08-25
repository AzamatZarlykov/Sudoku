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

	void render(vector<vector<Cell>>&, vector<unique_ptr<Button>>&, time_t, bool&);
	void create_interface_layout(vector<vector<Cell>>&, vector<unique_ptr<Button>>&);
	void load_texture(SDL_Texture*&, const char*, SDL_Color&);

	void display_success(unique_ptr<Button>&);
	void display_failure(unique_ptr<Button>&);

	void set_default_check_button(unique_ptr<Button>&);

	SDL_Texture** get_number_textures();
private:
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	TTF_Font* _font;

	SDL_Texture* num_texture[10];
	SDL_Texture* buttons_texture[6];
	SDL_Texture* result_texture[2];

	// Stopwatch
	Button timer;

	time_t finish_time;


	void CHECKFORERROR(bool, string);

	void render_grid(vector<vector<Cell>>&);
	void render_stopwatch(time_t&, bool&);
	void render_buttons(vector<unique_ptr<Button>>&);

	void prepare_stopwatch(int&, int&, int&, int&);
	void prepare_grid(vector<vector<Cell>>&, int&, int&, int&, int&);
	void prepare_buttons(int&, int&, int&, int&, vector<unique_ptr<Button>>&);
	void prepare_texture(vector<unique_ptr<Button>>&);

	
};


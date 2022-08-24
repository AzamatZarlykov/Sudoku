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

	void render(vector<vector<Cell>>&, time_t);
	void create_interface_layout(vector<vector<Cell>>&);
	void prepare_texture();
	void load_texture(SDL_Texture*&, const char*, SDL_Color&);
private:
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	TTF_Font* _font;

	SDL_Texture* num_texture[10];
	SDL_Texture* buttons_texture[6];

	// buttons: Check, Hint, Save, Next, Solve
	vector<unique_ptr<Button>> buttons;
	
	// Stopwatch
	Button timer;
	// Load button separate(only menu)
	Button load;

	void CHECKFORERROR(bool, string);

	void render_grid(vector<vector<Cell>>&);
	void render_stopwatch(time_t&);
	void render_buttons();

	void prepare_stopwatch(int&, int&, int&, int&);
	void prepare_grid(vector<vector<Cell>>&, int&, int&, int&, int&);
	void prepare_buttons(int&, int&, int&, int&);
};


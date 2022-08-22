#pragma once

#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "constants.hpp"

#undef main

using namespace std;

class View {
public:
	View();
private:
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	TTF_Font* _font;

	void CHECKFORERROR(bool, string);
};


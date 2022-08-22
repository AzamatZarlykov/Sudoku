#include "../include/view.hpp"

void View::CHECKFORERROR(bool error, string msg) {
	if (error) {
		cerr << ("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(1);
	}
}

View::View() {
	cout << "view instantiated" << endl;

	/* initialize sdl */
	CHECKFORERROR(SDL_Init(SDL_INIT_VIDEO), SDL_GetError());

	/* initialize window and renderer */
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC, &_window, &_renderer);
	CHECKFORERROR(_window == NULL, SDL_GetError());
	CHECKFORERROR(_renderer == NULL, SDL_GetError());

	/* initialize font */
	CHECKFORERROR(TTF_Init() == -1, TTF_GetError());
	_font = TTF_OpenFont("../font/font.ttf", FONT_SIZE);
	CHECKFORERROR(_font == NULL, TTF_GetError());

	SDL_SetWindowTitle(_window, "Sudoku");
}
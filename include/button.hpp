#pragma once

#include <SDL.h>

class Button {
public:
	// setters
	void set_texture(SDL_Texture* texture);
	void set_button_rect(const SDL_Rect& rect);
	void set_texture_rect(const SDL_Rect& rect);
private:
	SDL_Texture* texture;

	SDL_Rect button_rect;
	SDL_Rect texture_rect;
};
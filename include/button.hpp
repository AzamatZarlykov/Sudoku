#pragma once

#include <iostream>

#include <SDL.h>
#include "constants.hpp"

enum class ButtonState
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER_MOTION = 1,
	BUTTON_MOUSE_DOWN = 2,
	BUTTON_MOUSE_UP = 3,
};


class Button {
public:
	Button();
	// setters
	void set_texture(SDL_Texture* texture);
	void set_button_rect(const SDL_Rect& rect);
	void set_texture_rect(const SDL_Rect& rect);
	void set_selected(const bool);

	void render_button(SDL_Renderer* _renderer);
	void render_texture(SDL_Renderer* _renderer);
	void center_val();

	bool get_selected() const;
private:
	bool selected;

	// Current button state
	ButtonState current_state;

	SDL_Texture* texture;
	SDL_Rect button_rect;
	SDL_Rect texture_rect;

	/* Colors */
	SDL_Color MOUSEOUTCOLOR = { 255, 255, 255, SDL_ALPHA_OPAQUE };
	SDL_Color MOUSEOVERMOTIONCOLOR = { 95, 89, 191, SDL_ALPHA_OPAQUE };
	SDL_Color MOUSEDOWNCOLOR = { 102, 178, 255, SDL_ALPHA_OPAQUE };
	SDL_Color MOUSEUPCOLOR = { 180, 214, 255, SDL_ALPHA_OPAQUE };
};
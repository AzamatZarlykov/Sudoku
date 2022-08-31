#pragma once

#include <iostream>
#include <string>

#include "SDL.h"
#include "constants.hpp"

using namespace std;

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
	Button(const char* name);

	void set_texture(SDL_Texture*);
	void set_button_rect(const SDL_Rect&);
	void set_texture_rect(const SDL_Rect&);
	void set_selected(const bool);
	void set_mousedown_color(const SDL_Color& colour);

	void render_button(SDL_Renderer*);
	void render_stopwatch(SDL_Renderer*);
	void render_texture(SDL_Renderer*);
	void center_val();

	ButtonState identify_mouse_event(const SDL_Event*);

	const char* get_name() const;
	bool get_selected() const;

	// default colors
	SDL_Color TITLE = { 0,0,0, SDL_ALPHA_OPAQUE };
	SDL_Color MOUSEOUTCOLOR = { 255, 255, 255, SDL_ALPHA_OPAQUE };
	SDL_Color MOUSEOVERMOTIONCOLOR = { 204, 229, 255, SDL_ALPHA_OPAQUE };
	SDL_Color MOUSEDOWNCOLOR = { 102, 178, 255, SDL_ALPHA_OPAQUE };
	SDL_Color MOUSEUPCOLOR = { 180, 214, 255, SDL_ALPHA_OPAQUE };
private:
	bool selected;
	const char* name;

	// Current button state
	ButtonState current_state;

	SDL_Texture* texture;
	SDL_Rect button_rect;
	SDL_Rect texture_rect;

	bool any_mouse_actions(const SDL_Event* event) const;
	bool inside_button(const int, const int) const;

};
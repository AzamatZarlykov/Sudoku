#include "../include/button.hpp"

Button::Button() : 
	current_state(ButtonState::BUTTON_MOUSE_OUT),
	selected(false),
	button_rect({0, 0, 0, 0}),
	texture(nullptr),
	texture_rect({0,0,0,0})
{}

void Button::set_texture(SDL_Texture* t)
{
	texture = t;
}

void Button::set_button_rect(const SDL_Rect& rect)
{
	button_rect = rect;
}

void Button::set_texture_rect(const SDL_Rect& rect)
{
	texture_rect = rect;
}

void Button::set_selected(const bool val)
{
	selected = val;
}

bool Button::get_selected() const
{
	return selected;
}

void Button::center_val()
{
	int textureWidth;
	int textureHeight;
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	const int textureStartRow = button_rect.y + 0.5 * (button_rect.h - textureHeight);
	const int textureStartCol = button_rect.x + 0.5 * (button_rect.w - textureWidth);

	texture_rect = { textureStartCol, textureStartRow, textureWidth, textureHeight };
}

void Button::render_button(SDL_Renderer* _renderer)
{
	if (selected) {
		SDL_SetRenderDrawColor(_renderer, MOUSEDOWNCOLOR.r, 
			MOUSEDOWNCOLOR.g, MOUSEDOWNCOLOR.b, MOUSEDOWNCOLOR.a
		);
	}
	else {
		// Show current button State
		switch (current_state)
		{
		case ButtonState::BUTTON_MOUSE_OUT:
			SDL_SetRenderDrawColor(_renderer, MOUSEOUTCOLOR.r, MOUSEOUTCOLOR.g, MOUSEOUTCOLOR.b, MOUSEOUTCOLOR.a);
			break;
		case ButtonState::BUTTON_MOUSE_OVER_MOTION:
			SDL_SetRenderDrawColor(_renderer, MOUSEOVERMOTIONCOLOR.r, MOUSEOVERMOTIONCOLOR.g, 
				MOUSEOVERMOTIONCOLOR.b, MOUSEOVERMOTIONCOLOR.a);
			break;
		case ButtonState::BUTTON_MOUSE_DOWN:
			SDL_SetRenderDrawColor(_renderer, MOUSEDOWNCOLOR.r, MOUSEDOWNCOLOR.g, MOUSEDOWNCOLOR.b, MOUSEDOWNCOLOR.a);
			break; 
		case ButtonState::BUTTON_MOUSE_UP:
			SDL_SetRenderDrawColor(_renderer, MOUSEUPCOLOR.r, MOUSEUPCOLOR.g, MOUSEUPCOLOR.b, MOUSEUPCOLOR.a);
			break;

		}
	}
	SDL_RenderFillRect(_renderer, &button_rect);
}

void Button::render_texture(SDL_Renderer* _renderer)
{
	// Set rendering space
	SDL_RenderCopy(_renderer, texture, nullptr, &texture_rect);
}
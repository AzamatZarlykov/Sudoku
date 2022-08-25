#include "../include/button.hpp"

Button::Button() :
	name(nullptr),
	current_state(ButtonState::BUTTON_MOUSE_OUT),
	selected(false),
	button_rect({ 0, 0, 0, 0 }),
	texture(nullptr),
	texture_rect({ 0,0,0,0 })
{

}

Button::Button(const char* name) :
	name(name),
	current_state(ButtonState::BUTTON_MOUSE_OUT),
	selected(false),
	button_rect({0, 0, 0, 0}),
	texture(nullptr),
	texture_rect({0,0,0,0})
{

}

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

void Button::set_mousedown_color(const SDL_Color& colour)
{
	MOUSEDOWNCOLOR = colour;
}

 
const char* Button::get_name() const
{
	return name;
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

bool Button::any_mouse_actions(const SDL_Event* event) const
{
	return event->type == SDL_MOUSEMOTION ||
		event->type == SDL_MOUSEBUTTONDOWN ||
		event->type == SDL_MOUSEBUTTONUP;
}

bool Button::inside_button(const int x, const int y) const
{
	return button_rect.x <= x && x <= button_rect.x + button_rect.w &&
		button_rect.y <= y && y <= button_rect.y + button_rect.h;
}

ButtonState Button::identify_mouse_event(const SDL_Event* event) 
{
	//If mouse event happened
	if (any_mouse_actions(event))
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Mouse is outside button
		if (!inside_button(x, y))
		{
			current_state = ButtonState::BUTTON_MOUSE_OUT;
		}
		// Mouse is inside button
		else
		{
			// Set mouse over State
			switch (event->type)
			{
			case SDL_MOUSEMOTION:
				current_state = ButtonState::BUTTON_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				current_state = ButtonState::BUTTON_MOUSE_DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				current_state = ButtonState::BUTTON_MOUSE_UP;
				break;

			}
		}
	}
	return current_state;
}

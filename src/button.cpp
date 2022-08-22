#include "../include/button.hpp"

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
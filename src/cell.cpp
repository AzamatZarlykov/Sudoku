#include "../include/cell.hpp"

Cell::Cell() :
	isEditable(false),
	number(0),
	solution(-1) { }

void Cell::set_number(const int n) 
{
	number = n;
}

void Cell::set_solution(const int s) 
{
	solution = s;
}

void Cell::set_editable(const bool e) 
{
	isEditable = e;
}

void Cell::set_noneditable_square(const int val) 
{
	number = val;
	solution = val;
	isEditable = false;

	// not editables have all grey
	MOUSEOUTCOLOR = { 160, 160, 160, SDL_ALPHA_OPAQUE };
	MOUSEOVERMOTIONCOLOR = { 160, 160, 160, SDL_ALPHA_OPAQUE };
	MOUSEDOWNCOLOR = { 160, 160, 160, SDL_ALPHA_OPAQUE };
	MOUSEUPCOLOR = { 160, 160, 160, SDL_ALPHA_OPAQUE };
}

void Cell::unset() 
{
	number = 0;	// change number displaying
	isEditable = true;	// can be edited

	// change colors
	MOUSEOUTCOLOR = { 255, 255, 255, SDL_ALPHA_OPAQUE };
	MOUSEOVERMOTIONCOLOR = { 204, 229, 255, SDL_ALPHA_OPAQUE };
	MOUSEDOWNCOLOR = { 102, 178, 255, SDL_ALPHA_OPAQUE };
	MOUSEUPCOLOR = { 180, 214, 255, SDL_ALPHA_OPAQUE };
}

int Cell::get_number() const {
	return number;
}

int Cell::get_solution() const {
	return solution;
}

bool Cell::get_editable() const {
	return isEditable;
}

bool Cell::is_correct() const {
	return number == solution;
}

ostream& operator<<(std::ostream& strm, const Cell& a) {
	return strm << int(a.solution);
}

void Cell::handle_keyboard_event(const SDL_Event* event, SDL_Texture* num_texture[])
{
	// Handle backspace
	if (event->key.keysym.sym == SDLK_BACKSPACE && number != ' ')
	{
		number = ' ';

		set_texture(num_texture[0]);
	}
	// Handle text input
	else if (event->type == SDL_TEXTINPUT)
	{
		// numbers only
		if (atoi(event->text.text))
		{
			number = * (event->text.text) - '0';

			set_texture(num_texture[atoi(event->text.text)]);
		}
	}
}
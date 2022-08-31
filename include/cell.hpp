#pragma once

#include <iostream>

#include "button.hpp"

using namespace std;

class Cell : public Button{
public:
	Cell();

	/* CELL RELATED */
	void set_number(const int);
	void set_solution(const int);
	void set_editable(const bool);

	void set_noneditable_square(const int);
	void unset();

	int get_number() const;
	int get_solution() const;
	bool get_editable() const;

	void handle_keyboard_event(const SDL_Event*, SDL_Texture*[]);

	bool is_correct() const;
private:
	bool isEditable;

	int number;
	int solution;

	friend ostream& operator<<(std::ostream& strm, const Cell& a);
};
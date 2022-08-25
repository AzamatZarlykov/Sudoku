#pragma once

#include "generator.hpp"
#include "view.hpp"

using namespace std;

struct Pos
{
	int x;
	int y;
};


class Sudoku {
public:
	Sudoku();

	int play();

private:
	Pos selected = { -1, -1 };

	// defaut level
	Level level = Level::EASY;
	// sudoku grid
	vector<vector<Cell>> grid;


	// unique_ptr<Parser> parser;
	unique_ptr<Generator> generator;
	unique_ptr<View> view;

	// buttons: Check, Hint, Save, Next, Solve
	const char* button_names[5] = { "Check", "Hint", "Save", "Next", "Solve" };
	bool bool_buttons[5] = { false, false, false, false, false };
	vector<unique_ptr<Button>> buttons;
	// Load button separate(only menu)
	unique_ptr<Button> load;

	bool check_grid(bool&) const;

	void handle_buttons_selection(bool&, bool&, time_t&, time_t&, bool&);
	void check_buttons_selection(const SDL_Event*, bool&);
	void check_cell_selection(const SDL_Event*);
	void set_selected_cell();

	void print_grid() const;
};

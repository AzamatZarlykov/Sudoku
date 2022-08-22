#pragma once

#include "generator.hpp"
#include "view.hpp"

using namespace std;

class Sudoku {
public:
	Sudoku();

	int play();

private:
	// defaut level
	Level level = Level::EASY;
	// sudoku grid
	vector<vector<Cell>> grid;
	// buttons: Check, Next, Hint
	Button check;
	Button next;
	Button hint;

	SDL_Texture* texture_cache[14];

	// unique_ptr<Parser> parser;
	unique_ptr<Generator> generator;
	unique_ptr<View> view;

	void print_grid() const;
	void create_interface_layout();
};

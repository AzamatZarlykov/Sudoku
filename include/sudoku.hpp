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
	// defaut level
	Level level = Level::EASY;
	// sudoku grid
	vector<vector<Cell>> grid;

	Pos selected = {-1, -1};

	// unique_ptr<Parser> parser;
	unique_ptr<Generator> generator;
	unique_ptr<View> view;

	void set_selected_cell();
	void print_grid() const;
};

#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "level.hpp"
#include "cell.hpp"

class Generator {
public:
	Generator();

	void generate(Level, vector<vector<Cell>>&);
private:
	void generate_puzzle(vector<vector<Cell>>&);
	void provide_hints(const int, vector<vector<Cell>>&);

	void fill_square(int, int, vector<vector<Cell>>&);
	bool fill_remaining(int, int, vector<vector<Cell>>&);

	bool safe(int, int, int, vector<vector<Cell>>&) const;
	bool safe_row(int, int, vector<vector<Cell>>&) const;
	bool safe_col(int, int, vector<vector<Cell>>&) const;
	bool safe_block(int, int, int, vector<vector<Cell>>&) const;

	int get_block_value(int, int, vector<vector<Cell>>&);

	int random_number(int);
};


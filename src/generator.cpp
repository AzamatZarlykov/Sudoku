#include "../include/generator.hpp"

Generator::Generator()
{
	srand((unsigned int)time(NULL));
}

int Generator::random_number(int n) {
	return rand() % n + 1;
}

// checks if the random number is inside the block
bool Generator::safe_block(int row, int col, int rnd_num, vector<vector<Cell>>& grid) const
{
	for (int i = 0; i < SQN; i++) {
		for (int j = 0; j < SQN; j++) {
			if (grid[row + i][col + j].get_number() == rnd_num) {
				return false;
			}
		}
	}

	return true;
}


int Generator::get_block_value(int row, int col, vector<vector<Cell>>& grid)
{
	int rnd_num = random_number(SIZE);

	while (!safe_block(row, col, rnd_num, grid)) {
		rnd_num = random_number(SIZE);
	}

	return rnd_num;
}


// fill diagonal square
void Generator::fill_square(int row, int col, vector<vector<Cell>>& grid)
{
	for (int i = 0; i < SQN; i++)
	{
		for (int j = 0; j < SQN; j++)
		{
			int value = get_block_value(row, col, grid);
			grid[row + i][col + j].set_noneditable_square(value);
		}
	}
}

bool Generator::safe_row(int i, int val, vector<vector<Cell>>& grid) const
{
	for (int j = 0; j < SIZE; j++) {
		if (grid[i][j].get_number() == val) {
			return false;
		}
	}
	return true;
}

bool Generator::safe_col(int j, int val, vector<vector<Cell>>& grid) const
{
	for (int i = 0; i < SIZE; i++) {
		if (grid[i][j].get_number() == val) {
			return false;
		}
	}
	return true;
}

bool Generator::safe(int row, int col, int val, vector<vector<Cell>>& grid) const
{
	return safe_row(row, val, grid) && safe_col(col, val, grid) &&
		safe_block(row - row % SQN, col - col % SQN, val, grid);
}

bool Generator::fill_remaining(int row, int col, vector<vector<Cell>>& grid)
{
	// if every col in the row is filled but row is not at the end
	// we want to move to the next row
	if (col >= SIZE && row < SIZE - 1) {
		col = 0;
		row += 1;
	}

	if (row >= SIZE && col >= SIZE) {
		return true;
	}

	if (row < SQN)
	{
		if (col < SQN) {
			col = SQN;
		}
	}
	else if (row < SIZE - SQN)
	{
		if (col == (row / SQN) * SQN)
			col += SQN;
	}
	else {
		if (col == SIZE - SQN)
		{
			row += 1;
			col = 0;
			if (row >= SIZE)
				return true;
		}
	}


	for (int val = 1; val <= 9; val++) {
		if (safe(row, col, val, grid)) {
			grid[row][col].set_noneditable_square(val);

			if (fill_remaining(row, col + 1, grid)) {
				return true;
			}
			grid[row][col].set_noneditable_square(0);
		}
	}
	return false;
}

void Generator::generate_puzzle(vector<vector<Cell>>& grid)
{
	// fill diagonal squares
	for (int i = 0; i < SIZE; i = i + SQN)
		// for diagonal box, start coordinates->i==j
		fill_square(i, i, grid);

	fill_remaining(0, SQN, grid);
}

void Generator::provide_hints(int n, vector<vector<Cell>>& grid)
{
	int hints = n;

	while (hints > 0) {
		int random_cell = random_number(SIZE * SIZE) - 1;

		int row = random_cell / SIZE; // floor
		int col = random_cell % SIZE;

		// not empty
		if (grid[row][col].get_number() != 0) {
			grid[row][col].unset();
			hints -= 1;
		}
	}
}

void Generator::generate(Level level, vector<vector<Cell>>& grid)
{
	generate_puzzle(grid);

	switch (level) {
	case (Level::EASY):
		provide_hints(FOR_EASY, grid);
		break;
	case (Level::MEDIUM):
		provide_hints(FOR_MEDIUM, grid);
		break;
	case (Level::HARD):
		provide_hints(FOR_HARD, grid);
		break;
	}
}

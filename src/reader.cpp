#include "../include/reader.hpp"

Reader::Reader()
{

}

string Reader::ltrim(const string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

string Reader::rtrim(const string& s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

string Reader::trim(const string& s) {
	return rtrim(ltrim(s));
}

bool Reader::is_white_space(const string& line) const {
	for (auto ch : line) {
		if (!isspace(ch)) {
			return false;
		}
	}
	return true;
}

bool Reader::is_editable(const string& word) const
{
	if (word.find('-') != std::string::npos)
		return true;
	else
		return false;
}

void Reader::store_line(vector<vector<Cell>>& grid, time_t& timer, string& line, int& row, int& col)
{
	string word;
	stringstream ss(line);

	while (ss >> word) {
		if (is_editable(word)) {
			grid[row][col].set_number(word[0] - '0');
			grid[row][col].set_solution(word[2] - '0');
			grid[row][col].set_editable(true);
		}
		else {
			if (stoi(word) > 9) {
				continue;
			}
			grid[row][col].set_noneditable_square(stoi(word));
		}

		col++;
	}
	col = 0;
}

bool Reader::read(vector<vector<Cell>>& grid, time_t& timer)
{
	int row = 0;
	int col = 0;

	string line;
	fstream file;

	file.open(path, fstream::in);

	if (!file.is_open()) {
		return false;
	}

	while (getline(file, line)) {
		if (is_white_space(line)) {
			continue;
		}

		line = trim(line);
		store_line(grid, timer, line, row, col);
		row++;
	}
	return true;
}
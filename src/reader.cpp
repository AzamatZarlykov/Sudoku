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

bool Reader::check_char(const string& word, char ch) const
{
	if (word.find(ch) != std::string::npos)
		return true;
	else
		return false;
}

void Reader::store_line(vector<vector<Cell>>& grid, string& line, int& row, int& col)
{
	string word;
	stringstream ss(line);

	while (ss >> word) {
		if (check_char(word, '-')) {
			grid[row][col].set_number(word[0] - '0');
			grid[row][col].set_solution(word[2] - '0');
			grid[row][col].set_editable(true);
		}
		else {
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

		// recognize time
		if (check_char(line, ':')) {

			timer = time(0);
			struct tm lt = {0};

			istringstream ss(line);
			ss >> get_time(&lt, "%H:%M:%S"); // or just %T in this case
			cout << "READ TIME: " << lt.tm_hour << ":" << lt.tm_min << ":" << lt.tm_sec << endl;
			timer = mktime(&lt);
		}
		// recognize grid
		else {
			store_line(grid, line, row, col);
		}
		row++;
	}
	return true;
}
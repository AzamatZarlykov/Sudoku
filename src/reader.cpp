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

void print_tm(tm& dt)
{
	cout << "#####" << endl;
	cout << "YDAY: " << dt.tm_yday << endl;
	cout << "WDAY: " << dt.tm_wday << endl;
	cout << "year: " << dt.tm_year << endl;
	cout << "MON: " << dt.tm_mon << endl;
	cout << "MDAY: " << dt.tm_mday << endl;
	cout << "HOUR: " << dt.tm_hour << endl;
	cout << "MIN: " << dt.tm_min << endl;
	cout << "SEC: " << dt.tm_sec << endl;
	cout << "ISDST: " << dt.tm_isdst << endl;
}


bool Reader::read(vector<vector<Cell>>& grid, time_t& timer)
{
	int row = 0;
	int col = 0;

	string line;
	fstream file;

	file.open(path, fstream::in);

	if (!file) {
		return false;
	}

	while (getline(file, line)) {
		if (is_white_space(line)) {
			continue;
		}

		line = trim(line);

		// recognize time
		if (check_char(line, ':')) {


			// store the saved time to tm struct
			tm tm_r = { 0 };
			time_t t;

			tm_r.tm_hour = 1;
			tm_r.tm_mon = 1;
			tm_r.tm_year = 2000 - 1970;
			tm_r.tm_mday = 1;
			tm_r.tm_sec = 1;
			tm_r.tm_yday = 1;
			tm_r.tm_isdst = 1;
			tm_r.tm_min = 1;
			tm_r.tm_wday = 1;

			t = time(nullptr);

			print_tm(tm_r);



			timer = mktime(&tm_r);
		}
		// recognize grid
		else {
			store_line(grid, line, row, col);
		}
		row++;
	}
	return true;
}
/*
tm tm_r = { 0 };
time_t t;
t = time(nullptr);
localtime_s(&tm_r, &t);

print_tm(tm_r);

istringstream ss(line);
tm holder = { 0 };
ss >> get_time(&holder, "%T");

tm_r.tm_isdst = 0;
tm_r.tm_sec = holder.tm_sec;
print_tm(tm_r);

timer = mktime(&tm_r);

*/

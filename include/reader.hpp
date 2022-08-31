#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>      // std::get_time
#include <chrono>
#include <ctime>
#include <locale.h>

#include "cell.hpp"

class Reader {
public:
	Reader();
	bool read(vector<vector<Cell>>& grid, time_t& timer);
private:
	const char* path = "saved/saved.txt";
	const string WHITESPACE = " \n\r\t\f\v";

	void store_line(vector<vector<Cell>>&, string&, int&, int&);
	bool is_white_space(const string&) const;
	bool check_char(const string&, char) const;
	string trim(const string&);
	string rtrim(const string&);
	string ltrim(const string&);
};
#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include "cell.hpp"

class Reader {
public:
	Reader();
	bool read(vector<vector<Cell>>& grid, time_t& timer);
private:
	const char* path = "saved/saved.txt";
	const string WHITESPACE = " \n\r\t\f\v";

	void store_line(vector<vector<Cell>>&, time_t&, string&, int&, int&);
	bool is_white_space(const string&) const;
	bool is_editable(const string&) const;
	string trim(const string&);
	string rtrim(const string&);
	string ltrim(const string&);
};
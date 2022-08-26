#pragma once

#include <fstream>
#include <vector>

#include "cell.hpp"

class Writer {
public:
	Writer();
	void write(vector<vector<Cell>>&, time_t&);
private:
	const char* path = "saved/saved.txt";
};
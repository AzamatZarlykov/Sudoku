#pragma once

#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>      // std::put_time

#include "cell.hpp"

class Writer {
public:
	Writer();
	void write(vector<vector<Cell>>&, time_t&);
private:
	const char* path = "saved/saved.txt";

	void record_time(time_t& time, fstream&);
};
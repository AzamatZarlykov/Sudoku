#include "../include/writer.hpp"

Writer::Writer()
{

}

void Writer::record_time(time_t& current_time, fstream& file)
{
	time_t difference = time(nullptr) - current_time;

	tm formatted_time;
	localtime_s(&formatted_time, &difference);

	if (formatted_time.tm_hour != 0) {
		formatted_time.tm_hour = 0;
	}

	file << put_time(&formatted_time, "%T") << endl;

	//file << formatted_time.tm_hour * 3600 + formatted_time.tm_min * 60 + formatted_time.tm_sec << endl;
}

void Writer::write(vector<vector<Cell>>& grid, time_t& time)
{
	fstream file;
	file.open(path, fstream::out);

	if (!file.is_open()) {
		cout << "Unable to open the file" << endl;
		exit(1);
	}
	// writing the grid to the file
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			if (!grid[row][col].get_editable()) {
				file << grid[row][col].get_number() << " ";
			}
			else {
				file << grid[row][col].get_number() << "-" << grid[row][col].get_solution() << " ";
			}
		}
		file << endl;
	}
	// write time to the file 
	record_time(time, file);

 	// close the opened file.
	file.close();
}
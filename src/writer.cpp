#include "../include/writer.hpp"

Writer::Writer()
{

}

void Writer::write(vector<vector<Cell>>& grid, time_t& time)
{
	fstream file;
	file.open(path, fstream::out);
	// writing the grid to the file
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			file << grid[row][col].get_number() << " ";
		}
		file << endl;
	}
	// write stopwatch timer
	file << time << endl;

	// close the opened file.
	file.close();
}
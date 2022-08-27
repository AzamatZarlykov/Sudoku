#include "../include/writer.hpp"

Writer::Writer()
{

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

	// close the opened file.
	file.close();
}
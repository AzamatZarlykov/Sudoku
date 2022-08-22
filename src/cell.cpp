#include "../include/cell.hpp"

Cell::Cell() :
	isEditable(false),
	number(0),
	solution(-1) { }

void Cell::set_number(const int n) {
	number = n;
}

void Cell::set_solution(const int s) {
	solution = s;
}

void Cell::set_editable(const bool e) {
	isEditable = e;
}

void Cell::set_noneditable_square(const int val) {
	number = val;
	solution = val;
	// isEditable is false by default
}

void Cell::unset() {
	number = 0;	// change number displaying
	solution = -1;	// change sol
	isEditable = true;	// can be edited
}

int Cell::get_number() const {
	return number;
}

int Cell::get_solution() const {
	return solution;
}

bool Cell::get_editable() const {
	return isEditable;
}

bool Cell::check() const {
	return number == solution;
}

ostream& operator<<(std::ostream& strm, const Cell& a) {
	return strm << a.number;
}
#pragma once

#include <filesystem>

#include "generator.hpp"
#include "view.hpp"
#include "writer.hpp"
#include "reader.hpp"

using namespace std;

enum class GameState {
	MENU, COMPLEXITY, GAME
};

struct Pos
{
	int x;
	int y;
};

class Sudoku {
public:
	Sudoku();
	int play();
private:
	Pos selected = { -1, -1 };

	GameState gs = GameState::MENU;
	// defaut level
	Level level = Level::EASY;
	// sudoku grid
	vector<vector<Cell>> grid;

	// stopwatch
	time_t current_timer;

	// unique_ptr<Parser> parser;
	unique_ptr<Generator> generator;
	unique_ptr<View> view;
	
	//writer and reader
	unique_ptr<Writer> writer;
	unique_ptr<Reader> reader;

	bool any_button_pressed = false;
	bool bool_game_buttons[6] = { false, false, false, false, false, false };
	bool bool_menu_buttons[2] = { false, false };
	bool bool_complexity_buttons[3] = { false, false, false };

	vector<unique_ptr<Button>> game_buttons;
	vector<unique_ptr<Button>> menu_buttons;
	vector<unique_ptr<Button>> complexity_buttons;
	const char* game_button_names[6] = { "Check", "Hint", "Save", "Next", "Solve", "Menu"};
	const char* menu_button_names[2] = { "Start", "Load" };
	const char* complexity_names[3] = { "Easy", "Medium","Difficult" };

	void initialize_buttons();

	bool check_grid(bool&) const;
	bool is_selected_set() const;
	void initialize_grid(vector<vector<Cell>>&);

	void handle_buttons_selection(bool&, time_t&, time_t&, time_t&);
	void check_buttons_selection(const SDL_Event*);
	void check_cell_selection(const SDL_Event*);
	void set_selected_cell();

	void handle_check_button(bool&, time_t&);
	void handle_next_button(bool next_grid);
	void handle_solve_button();
	void handle_hint_button();
	void handle_save_button(bool&, time_t&);
	void handle_menu_button();
	void handle_load_button(bool&, time_t&);
	void handle_start_button();

	void repopulate_grid(vector<vector<Cell>>&);

	void print_grid() const;
};

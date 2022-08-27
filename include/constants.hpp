#pragma once

#include "SDL.h"

/* puzzle grid dimensions */
const int SIZE = 9;

/* square root for diagonal block division */
const int SQN = 3;

/* domain of every cell */
const int FROM = 1;
const int TO = 9;

/* number of hints */
const int FOR_EASY = 17;
const int FOR_MEDIUM = 33;
const int FOR_HARD = 49;

/* window size */
const int WIDTH = 935;
const int HEIGHT = 795;

/* Define Sudoku grid dimensions */
const int mGridHeight = 680;
const int mGridWidth = 680;

/* font */
const int FONT_SIZE = 30;
const int TITLE_FONT_SIZE = 100;

const int GRID_WIDTH = 710;

// Define thick and thin borders
const int THIN_B = 2;
const int THICK_B = THIN_B + 6;

/* seconds to display a message */
const int DISPLAY_TIME = 2;
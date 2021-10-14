#ifndef SCREEN_H
#define SCREEN_H

#include "system.h"

#define SCREEN_WIDTH 5
#define SCREEN_HEIGHT 7

// Lits given column with given pattern
void show_column(uint8_t row_pattern, uint8_t current_column);
// Displays the screen
void screen_update(void);
// Returns true/false if given pixel is lit
bool screen_pixel_get(uint8_t col, uint8_t row);
// Moves screen up
void screen_up(void);
// Initialises screen/display
void screen_init(uint8_t rate);

#endif //SCREEN_H



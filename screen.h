#ifndef SCREEN_H
#define SCREEN_H

#include "system.h"

#define SCREEN_WIDTH 5
#define SCREEN_HEIGHT 7

// Number of seconds that the player can idle to not lose
#define SCREEN_TIME_OUT 12

typedef enum 
{
    /** Showing title of game */
    SCREEN_MODE_TITLE, 
    /** Showing instructions  */
    SCREEN_MODE_INSTRUCTIONS,
    /** Showing game */
    SCREEN_MODE_GAME,
    /** Showing game over */
    SCREEN_MODE_END,
} screen_mode_t;


// Lits given column with given pattern
void screen_show_column(uint8_t row_pattern, uint8_t current_column);
// Displays the screen
void screen_update(void);
// Returns true/false if given pixel is lit
bool screen_pixel_get(uint8_t col, uint8_t row);
// Moves screen up
void screen_up(void);
// Unpauses the screen
void screen_navswitch_pressed(void);
//Display game over message with player score
void screen_show_game_over(void);
// Initialises screen/display
void screen_init(uint16_t rate);

#endif //SCREEN_H



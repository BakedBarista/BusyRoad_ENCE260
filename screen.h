/** @file    screen.h
    @authors Carl Chen and Jeremy Gatdula
    @date    22 October 2021
    @brief   Screen graphics module.

    @defgroup screen Screen graphics module.
       
    This module provides a simple way to display
    obstacles onto the screen and count scores.

    Here is a example to display obstacles on screen

       @code
       #include "system.h
       #include "screen.h"
       #include "pacer.h"

       void main (void)
       {
           system_init();
           pacer_init (300);
           screen_init(300);
           while (1)
           {
               pacer_wait ();
               screen_update();

           }
        }
       @endcode

*/

#ifndef SCREEN_H
#define SCREEN_H

#include "system.h"

/** Define size of display.  */
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


/** Displays a given pattern on screen
    @param row_pattern pattern of leds, 1 turns led on, 0 turns led off.
    @param current_column coordinate of pattern on column.  */
void screen_show_column(uint8_t row_pattern, uint8_t current_column);


/** Update display, obstacles and text display.  */
void screen_update(void);


/** Get pixel.
    @param col column-coordinate on bitmap.
    @param row row-coordinate on bitmap.
    @return 1 if pixel is on; 0 if pixel is off.  */
bool screen_pixel_get(uint8_t col, uint8_t row);


/** Advance bitmap up and create new obstacle. */
void screen_up(void);


/** Display game over message with player score. */
void screen_show_game_over(void);


/** Advances the screen to the next mode. */
void screen_navswitch_pressed(void);


/** Initialises screen. */
void screen_init(uint16_t rate);


#endif //SCREEN_H



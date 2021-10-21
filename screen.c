/** @file    screen.c
    @authors Carl Chen and Jeremy Gatdula
    @date    22 October 2021
    @brief   Screen graphics module.
*/

#include "tinygl.h"
#include "screen.h"
#include "obstacles.h"
#include "pio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../fonts/font3x5_1.h"
#include "tinygl.h"

static uint8_t bitmap[SCREEN_WIDTH];
static screen_mode_t screen_mode;
static uint16_t screen_rate;
static uint16_t screen_timer = 0;
static uint16_t screen_score = 0;

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


/** Displays a given pattern on screen
    @param row_pattern pattern of leds, 1 turns led on, 0 turns led off.
    @param current_column coordinate of pattern on column  */
void screen_show_column(uint8_t row_pattern, uint8_t current_column)
{
    if (screen_mode == SCREEN_MODE_GAME){
        static uint8_t last_column = 0;
        pio_output_high(cols[last_column]);
        for (int i = 0; i < 7; i++) {
            if ((row_pattern>>i) & 1) {
                pio_output_low(rows[i]);
            }
            else {
                pio_output_high(rows[i]);
            }
        }
        pio_output_low(cols[current_column]);
        last_column = current_column;
    }
}


/** Update display, obstacles and text display.  */
void screen_update(void)
{
    if (screen_mode == SCREEN_MODE_GAME){
        static uint8_t col = 0;

        screen_show_column(bitmap[col], col);
        col++;
        screen_timer++;
        if (col >= SCREEN_WIDTH)
            col = 0;
        if (screen_timer/screen_rate >= SCREEN_TIME_OUT) {
            screen_show_game_over();
        }
        obstacle_update(bitmap);
    } else {
        tinygl_update();
        if (screen_timer/screen_rate <= 2) {
            screen_timer += 1;
        }
    }
}


/** Get pixel.
    @param col column-coordinate on bitmap.
    @param row row-coordinate on bitmap.
    @return 1 if pixel is on; 0 if pixel is off.  */
bool screen_pixel_get(uint8_t col, uint8_t row)
{
    uint8_t bitmask;

    if (col >= SCREEN_WIDTH || row >= SCREEN_HEIGHT)
        return 0;

    bitmask = BIT (row);

    return (bitmap[col] & bitmask) != 0;
}


/** Advance bitmap up and create new obstacle. */
void screen_up(void)
{
    if (screen_mode == SCREEN_MODE_GAME) {
        for (int i = 1; i < SCREEN_WIDTH; i++) {
            bitmap[SCREEN_WIDTH - i] = bitmap[SCREEN_WIDTH - i - 1];
        }
        screen_score++;
        screen_timer = 0;
        // Creates a new obstacle
        create_obstacle(bitmap);
    }
}


/** Display game over message with player score. */
void screen_show_game_over(void)
{
    if (screen_mode == SCREEN_MODE_GAME) {
        char str[6];
        itoa(screen_score, str, 10);
        char msg[24] = "GAME OVER SCORE:";
        strcat(msg, str);
        tinygl_text (msg);
        screen_timer = 0;
        screen_mode = SCREEN_MODE_END;
    }
}


/** Resets the bitmap, score and timer. */
static void screen_refresh(void)
{
    for (int i = 0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
    for (int i = 0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
    uint8_t init[] =
    {
        0x41, 0x55, 0x0, 0x0, 0x0
    };

    for (int col = 0; col < SCREEN_WIDTH; col++) {
        bitmap[col] = init[col];
    }

    obstacle_refresh();

    screen_score = 0;
    screen_timer = 0;
}


/** Advances the screen to the next mode. */
void screen_navswitch_pressed(void)
{
    if (screen_mode == SCREEN_MODE_TITLE) {
        tinygl_text ("USE NAVSTICK TO MOVE");
        screen_mode = SCREEN_MODE_INSTRUCTIONS;
    } else if (screen_mode == SCREEN_MODE_INSTRUCTIONS) {
        screen_refresh();
        screen_mode = SCREEN_MODE_GAME;
    }
    if (screen_mode == SCREEN_MODE_END && (screen_timer/screen_rate >= 2)) {
        screen_refresh();
        screen_mode = SCREEN_MODE_GAME;
    }
}


/** Initialises screen. */
void screen_init(uint16_t rate)
{
	tinygl_init(rate);
	tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (30);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text ("BUSY ROAD");
    screen_refresh();
    obstacle_init(rate);

    screen_rate = rate;
    screen_mode = SCREEN_MODE_TITLE;
}



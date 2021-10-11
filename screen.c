#include "tinygl.h"
#include "screen.h"
#include "pio.h"
#include <stdlib.h>

static uint8_t bitmap[SCREEN_WIDTH];
static uint8_t preload[SCREEN_MAX_PRELOAD] = {0};
static uint8_t preloaded_columns = 0;
static uint8_t screen_counter[6] = {0,1,2,3,2,1};

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

// Lits given column with given pattern
void show_column(uint8_t row_pattern, uint8_t current_column)
{
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

// Creates new obsticles
static void screen_preload(void)
{
    if (preloaded_columns <= 0) {
        for (int col = SCREEN_MAX_PRELOAD; col > 1; col--) {
            preload[col-1] = preload[col-2];
        }
        // Randomly generate obsticles and empty rows for traffic
        uint8_t empty_row = screen_counter[rand() % 5];
        if (empty_row == 0) {
        	for (int i = 0; i < SCREEN_MAX_PRELOAD; i++) {
        			preload[i] = (rand() % 0x7f);
        	}
        } else {
        	for (int j = 0; j < empty_row; j++) {
        		for (int i = 0; i < SCREEN_MAX_PRELOAD; i++) {
        			preload[i] = 0x00;
        		}
        	}
        }
        	
        preloaded_columns++;
    }
}

// Displays the screen
void screen_update(void)
{
    static uint8_t col = 0;

    show_column(bitmap[col], col);

    col++;
    if (col >= SCREEN_WIDTH)
        col = 0;
}

// Returns true/false if given pixel is lit
bool screen_pixel_get(uint8_t col, uint8_t row)
{
    uint8_t bitmask;

    if (col >= SCREEN_WIDTH || row >= SCREEN_HEIGHT)
        return 0;

    bitmask = BIT (row);

    return (bitmap[col] & bitmask) != 0;
}

// Moves screen up
void screen_up(void)
{
    screen_preload();
    for (int col = SCREEN_WIDTH; col > 1; col--) {
        bitmap[col-1] = bitmap[col-2];
    }
    bitmap[0] = preload[preloaded_columns-1];
    preloaded_columns--;

}

// Initialises screen/display
void screen_init(void)
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
    preloaded_columns = 0;
}



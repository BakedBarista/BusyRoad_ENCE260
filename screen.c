#include "tinygl.h"
#include "screen.h"
#include "obstacles.h"
#include "pio.h"
#include <stdlib.h>

static uint8_t bitmap[SCREEN_WIDTH];

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

// Displays the screen
void screen_update(void)
{
    static uint8_t col = 0;

    show_column(bitmap[col], col);
    col++;
    if (col >= SCREEN_WIDTH)
        col = 0;
        
    obstacle_update(bitmap);
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
    for (int i = 1; i < SCREEN_WIDTH; i++) {
        bitmap[SCREEN_WIDTH - i] = bitmap[SCREEN_WIDTH - i - 1];
    }
    // Creates a new obstacle
    create_obstacle(bitmap);
}

// Initialises screen/display
void screen_init(uint8_t rate)
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
    obstacle_init(rate);
}



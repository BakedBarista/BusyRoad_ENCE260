#include <stdlib.h>
#include <stdbool.h>
#include "system.h"
#include "screen.h"
#include "obstacles.h"

static uint8_t screen_counter[5] = {0, 0, 2, 3, 2, 1};
static uint8_t car_presets[] = {0x11, 0x54, 0x10, 0x14, 0x02, 0x08};
static uint8_t car_times[SCREEN_WIDTH] = {0};
static uint8_t car_placements;
static uint8_t screen_rate;

// returns true/false if path is blocked
static bool check_obstacle(uint8_t* bitmap, uint8_t check)
{
    for (uint8_t i = 1; i < SCREEN_WIDTH; i++) {
        if (check >= 0x7f) {
            return true;
        } else if (bitmap[i] == 0 || (car_placements & BIT(i)) != 0 || check == 0) {
            return false;
        }
        check |= bitmap[i];
    }
    return true;
}

// Generates new obstacles
void create_obstacle(uint8_t* bitmap)
{
    for (int i = 1; i < SCREEN_WIDTH; i++) {
        car_times[SCREEN_WIDTH - i] = car_times[SCREEN_WIDTH - i - 1];
    }
    car_placements = car_placements << 1;
    car_placements &= 0x7f;

    uint8_t empty_row = screen_counter[rand() % 5];
    if (empty_row == 0) {
        // Creates stationary points
        uint8_t obstacle;
        do {
            obstacle = (rand() % 0x7f);
        } while (check_obstacle(bitmap, obstacle));
        bitmap[0] = obstacle;

    } else if (rand() % 2 == 1) { // how often cars are made for every blank row
        // Creates moving cars
        bitmap[0] = car_presets[rand() % 6];
        car_placements |= 0x01;
        car_times[0] = (rand() % (CAR_SPEED*screen_rate));

    } else {
        // Creates empty row
        bitmap[0] = 0x00;
    }
}

// Updates moving obstacles
void obstacle_update(uint8_t* bitmap)
{
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        uint8_t time = car_times[i];
        if ((car_placements & BIT(i)) != 0 && time/screen_rate >= CAR_SPEED) {
            bitmap[i] = bitmap[i] << 1;
            bitmap[i] &= 0x7f;
            if ((bitmap[i] & 0x03) == 0 && (rand() % 3) == 1) {
                bitmap[i] |= 0x01;
            }
            car_times[i] = 0;
        }
        car_times[i] += 1;
    }
}

// Refreshes placements and sets screen rate
void obstacle_init(uint8_t rate)
{
    car_placements = 0x00;
    screen_rate = rate;
}

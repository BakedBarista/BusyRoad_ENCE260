#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "system.h"

#define CAR_SPEED 1
#define MAX_CAR_DISTANCE 3

// Generates new obstacles
void create_obstacle(uint8_t* bitmap);
// Updates moving obstacles
void obstacle_update(uint8_t* bitmap);
// Refreshes placements and sets screen rate
void obstacle_init(uint8_t rate);



#endif //OBSTACLES_H
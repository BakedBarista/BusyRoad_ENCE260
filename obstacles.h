/** @file    obstacles.h
    @authors Carl Chen and Jeremy Gatdula
    @date    22 October 2021
    @brief   Obstacle generator module

    @defgroup obstacles Obstacle generator module
       
    This module provides support for creating obstacles on bitmaps.

    Here is a example to generate a obstacle on a 5 display wide bitmap.

        @code
        #include "obstacles.h"
        #include "screen.h"

        void main (void)
        {
            uint8_t bitmap[5];
            create_obstacle(bitmap);
        }
        @endcode

*/

#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "system.h"

#define CAR_SPEED 1
#define MAX_CAR_DISTANCE 3


/** Generates new obstacles.
    @param bitmap pointer to add new obstacles on.  */
void create_obstacle(uint8_t* bitmap);


/** Update obstacles (Move cars).
    @param bitmap pointer used to move cars.  */
void obstacle_update(uint8_t* bitmap);


/** Clears all car placements  */
void obstacle_refresh(void);


/** Initialise obstacles.
    @param rate rate in Hz.  */
void obstacle_init(uint16_t rate);


#endif //OBSTACLES_H

/** @file    player.h
    @authors Carl Chen and Jeremy Gatdula
    @date    22 October 2021
    @brief   Player module.

    @defgroup player Player module.
       
    This module provides a simple way to record
	player location and move player on screen.

    Here is a example to display player on screen 
	with obstacles:

       @code
       #include "system.h"
       #include "player.h"
       #include "screen.h"
       #include "pacer.h"

       void main (void)
       {
           system_init();
           pacer_init (300);
           screen_init(300);
           player = player_init();
           while (1)
           {
               pacer_wait ();
               screen_update();
			   player_update(&player);

           }
        }
       @endcode

*/


#ifndef PLAYER_H
#define PLAYER_H

#include "system.h"

/** Object player containing player location on display. */
typedef struct
{
	uint8_t x;
	uint8_t y;
}player_t;


/** Create player object and set to start location
	@param player to move player location up.
    @return player object with new location.  */
player_t move_forward(player_t player);


/** Create player object and set to start location.
	@param player to move player location down.
    @return player object with new location.  */
player_t move_backward(player_t player);


/** Create player object and set to start location.
	@param player to move player location right.
    @return player object with new location.  */
player_t move_right(player_t player);


/** Create player object and set to start location.
	@param player to move player location left.
    @return player object with new location.  */
player_t move_left(player_t player);


/** Create player object and set to start location.
    @return new player object with start location.  */
player_t player_init(void);


/** Updates and displays player
	@param player to get location.  */
void player_update(player_t* player);


#endif //PLAYER_H



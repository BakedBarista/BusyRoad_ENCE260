#ifndef PLAYER_H
#define PLAYER_H
#include "tinygl.h"

//Object player containing score and player location on display
typedef struct
{
	uint8_t score;
	tinygl_point_t pos;
}player_t;


//Create new player object and set to start location
player_t player_init(void);
//Move left
player_t move_left(player_t player);
//Move right
player_t move_right(player_t player);
//Move forward
player_t move_forward(player_t player);
//Move backward
player_t move_backward(player_t player);

#endif //PLAYER_H


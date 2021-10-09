#ifndef P_MOVE_H
#define P_MOVE_H
#include "tinygl.h"


typedef struct
{
	tinygl_point_t pos;
}player_t;


player_t move_left(player_t player);
player_t move_right(player_t player);
player_t move_forward(player_t player);
player_t move_backward(player_t player);

#endif //P_MOVE_H



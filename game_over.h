#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "player.h"
#include "obstacles.h"
#include "systems.h"
#include "tinygl.h"

//Triggers game over when player collide with car
void game_over_trigger(player_t player, car);

//Display final meesage and score

void show_score(player_t player);

#endif // GAME_OVER_H



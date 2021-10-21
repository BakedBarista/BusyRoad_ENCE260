/** @file    player.c
    @authors Carl Chen and Jeremy Gatdula
    @date    22 October 2021
    @brief   Obstacle generator module
*/

#include "system.h"
#include "player.h"
#include "screen.h"
#include <stdlib.h>


/** Create player object and set to start location
	@param player to move player location up.
    @return player object with new location.  */
player_t move_forward(player_t player)
{
	if (player.y == 0 || screen_pixel_get(player.y - 1, player.x)) {
		return player;
	} else if (player.y <= 3) {
		screen_up();
	} else {
		player.y = player.y-1;
	}
	return player;
}


/** Create player object and set to start location.
	@param player to move player location down.
    @return player object with new location.  */
player_t move_backward(player_t player)
{
	if (player.y == 4 || screen_pixel_get(player.y + 1, player.x)) {
		return player;
	} else {
	player.y = player.y+1;
	return player;
	}
	
}


/** Create player object and set to start location.
	@param player to move player location right.
    @return player object with new location.  */
player_t move_right(player_t player)
{
	if (player.x == 0 || screen_pixel_get(player.y, player.x - 1)) {
		return player;
	} else {
	player.x = player.x - 1;
	return player;
	}
	
}


/** Create player object and set to start location.
	@param player to move player location left.
    @return player object with new location.  */
player_t move_left(player_t player)
{
	if (player.x == 6 || screen_pixel_get(player.y, player.x + 1)) {
		return player;
	} else {
	player.x = player.x + 1;
	return player;
	}
}


/** Create player object and set to start location.
    @return new player object with start location.  */
player_t player_init(void)
{
	player_t player = {4, 4};
	return player;
}


/** Updates and displays player
	@param player to get location.  */
void player_update(player_t* player) {
	if (!screen_pixel_get(player->y, player->x)) {
		screen_show_column(BIT(player->x), player->y);
	} else {
		screen_show_game_over();
		player->x = 4;
		player->y = 4;
	}
}

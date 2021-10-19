
#include "system.h"
#include "player.h"
#include "screen.h"
#include <stdlib.h>
#include <string.h>
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include "tinygl.h"



player_t move_forward(player_t player)
{
	if (player.y == 0 || screen_pixel_get(player.y - 1, player.x)) {
		return player;
	} else if (player.y <= 3) {
		screen_up();
		player.score += 1;
	} else {
		player.y= player.y-1;
	}
	return player;
}
player_t move_backward(player_t player)
{
	if (player.y == 4 || screen_pixel_get(player.y + 1, player.x)) {
		return player;
	} else {
	player.y= player.y+1;
	return player;
	}
	
}
player_t move_right(player_t player)
{
	if (player.x == 0 || screen_pixel_get(player.y, player.x - 1)) {
		return player;
	} else {
	player.x= player.x - 1;
	return player;
	}
	
}
player_t move_left(player_t player)
{
	if (player.x == 6 || screen_pixel_get(player.y, player.x + 1)) {
		return player;
	} else {
	player.x= player.x + 1;
	return player;
	}
}

//Display game over message with player score
static void game_over_show(player_t player)
{
	
	uint8_t num = player.score;
	char str[5];
	itoa(num, str, 10);
	char msg[] = "GAME OVER SCORE ";
	strcat(msg, str);
	tinygl_text(msg);
	while(1) {
		pacer_wait();
		tinygl_update();
	}
}

player_t player_init(void)
{
	player_t player = {0, 4, 4};
	return player;
}


//Displays player and check for collision
void player_update(player_t player) {
	if (!screen_pixel_get(player.y, player.x)) {
		show_column(BIT(player.x), player.y);
	} else {
		game_over_show(player);
	}
}

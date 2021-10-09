#include "tinygl.h"
#include "player.h"

player_t player_init(void)
{
	player_t player = {0, {TINYGL_WIDTH / 2, TINYGL_HEIGHT - 1}};
	return player;
}

player_t move_left(player_t player)
{
	if (player.pos.x == 0) {
		return player;
	} else {
	tinygl_draw_point(player.pos, 0);
	player.pos.x= player.pos.x-1;
	tinygl_draw_point(player.pos, 1);
	return player;
	}
}
player_t move_right(player_t player)
{
	if (player.pos.x == 4) {
		return player;
	} else {
	tinygl_draw_point(player.pos, 0);
	player.pos.x= player.pos.x+1;
	tinygl_draw_point(player.pos, 1);
	return player;
	}
	
}
player_t move_forward(player_t player)
{
	if (player.pos.y == 0) {
		return player;
	} else {
	tinygl_draw_point(player.pos, 0);
	player.pos.y= player.pos.y - 1;
	tinygl_draw_point(player.pos, 1);
	return player;
	}
	
}
player_t move_backward(player_t player)
{
	if (player.pos.y == 6) {
		return player;
	} else {
	tinygl_draw_point(player.pos, 0);
	player.pos.y= player.pos.y + 1;
	tinygl_draw_point(player.pos, 1);
	return player;
	}
}

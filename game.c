#include "system.h"
#include "navswitch.h"
#include "pacer.h"
#include "display.h"
#include "tinygl.h"
#include "p_move.h"

int main (void)
{
	system_init();
	navswitch_init();
	pacer_init(200);
	tinygl_init(200);
	player_t player;
	player.pos.x = TINYGL_WIDTH / 2;
	player.pos.y = TINYGL_HEIGHT - 1;
	tinygl_draw_point(player.pos, 1);
	
	while(1) {
	pacer_wait();
	navswitch_update();
	if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
		player = move_forward(player);
		}
	if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
		player = move_backward(player);
		}
	if (navswitch_push_event_p(NAVSWITCH_WEST)) {
		player = move_left(player);
		}
	if (navswitch_push_event_p(NAVSWITCH_EAST)) {
		player = move_right(player);
		}
	tinygl_update();
	}
	return 0;
}

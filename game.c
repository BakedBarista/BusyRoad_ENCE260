#include "system.h"
#include "navswitch.h"
#include "pacer.h"
#include "display.h"
#include "tinygl.h"
#include "task.h"
#include "player.h"
#include "screen.h"
#include <stdlib.h>
#include <string.h>
#include "../fonts/font5x7_1.h"

/* Define polling rates in Hz.  */
#define BUTTON_TASK_RATE 100
#define SCREEN_TASK_RATE 250
#define PLAYER_TASK_RATE 20

static player_t player;

static void navswitch_task (__unused__ void *data)
{
	navswitch_update();
	if (navswitch_push_event_p(NAVSWITCH_WEST)) {
		player = move_forward(player);
	}
	if (navswitch_push_event_p(NAVSWITCH_EAST)) {
		player = move_backward(player);
	}
	if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
		player = move_left(player);
	}
	if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
		player = move_right(player);
	}
}

static void player_task (__unused__ void *data)
{
	player_update(player);
}

static void screen_task (__unused__ void *data)
{
	screen_update();
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

int main (void)
{
	system_init();
	navswitch_init();
	pacer_init(200);
	tinygl_init(200);
	tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (10);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	screen_init(SCREEN_TASK_RATE);
	player = player_init();
	while (!screen_pixel_get(player.y, player.x)) {
	task_t tasks[] =
    {
        {.func = screen_task, .period = TASK_RATE / SCREEN_TASK_RATE}, 
        {.func = navswitch_task, .period = TASK_RATE / BUTTON_TASK_RATE},
        {.func = player_task, .period = TASK_RATE / PLAYER_TASK_RATE},
    };
    
	task_schedule (tasks, ARRAY_SIZE (tasks));
	}
	game_over_show(player);
		
	return 0;
}

/** @file    game.c
    @authors Carl Chen and Jeremy Gatdula
    @date    22 October 2021
*/

#include "system.h"
#include "navswitch.h"
#include "pacer.h"
#include "display.h"
#include "task.h"
#include "player.h"
#include "screen.h"
#include <stdlib.h>
#include <string.h>

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
		screen_navswitch_pressed();
	}
	if (navswitch_push_event_p(NAVSWITCH_EAST)) {
		player = move_backward(player);
		screen_navswitch_pressed();
	}
	if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
		player = move_left(player);
		screen_navswitch_pressed();
	}
	if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
		player = move_right(player);
		screen_navswitch_pressed();
	}
}


static void player_task (__unused__ void *data)
{
	player_update(&player);
}


static void screen_task (__unused__ void *data)
{
	screen_update();
}


int main (void)
{
	system_init();
	navswitch_init();
	screen_init(SCREEN_TASK_RATE);
	player = player_init();
	task_t tasks[] =
    {
        {.func = screen_task, .period = TASK_RATE / SCREEN_TASK_RATE}, 
        {.func = navswitch_task, .period = TASK_RATE / BUTTON_TASK_RATE},
        {.func = player_task, .period = TASK_RATE / PLAYER_TASK_RATE},
    };
    
	task_schedule (tasks, ARRAY_SIZE (tasks));
	return 0;
}

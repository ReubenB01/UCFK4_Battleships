#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "game.h"

/**
If all ship tiles have been hit display "WIN" message for winner.
End game.
*/
void win_screen(int* count);
void update_matrix(int x, int y, int* shot_matrix);
void player_movement(int* x, int* y);

/**
//send ready signal after ships have been placed
*/
void ready_signal(void);
int first_turn(void);
void send_point(int*, int*, char*);

#endif
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "game.h"
#include "ir_uart.h"
#include "../fonts/font3x5_1.h"

void update_matrix(int x, int y, int* shot_matrix);


/**
Player can use navswitch to select which tile to fire at.
*/
void player_movement(int* x, int* y);


/**
//send ready signal after ships have been placed
*/
void ready_signal(void);
int first_turn(void);
void send_point(int*, int*, char*);

#endif

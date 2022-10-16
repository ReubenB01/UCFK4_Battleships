#ifndef GAME_H
#define GAME_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "boat_setup.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define MAX_X 5
#define MAX_Y 7

void hit_message (int board[7][5], int x_cord, int y_cord);
void display_hits(int board[7][5]);
void win_screen(int count);
void update_matrix(int x, int y, int* their_matrix);
void player_movement(int* x, int* y);
void ready_signal(void);
int first_turn(void);

#endif

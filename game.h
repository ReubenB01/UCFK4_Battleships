#ifndef GAME_H
#define GAME_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "movement.h"
#include "boat_setup.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define MAX_X 4
#define MAX_Y 6

void hit_message (int board[7][5], int x_cord, int y_cord);
void display_hits(int board[7][5]);
void win_screen (int board[7][5]);

#endif

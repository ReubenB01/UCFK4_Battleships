/**
    @file gameplay.h
    @author T. Glubb & R. Brown
    @date 17 October 2022
    @brief Gameplay logic support
*/

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "game.h"
#include "ir_uart.h"
#include "../fonts/font3x5_1.h"

/*
Updates the matrix with a 1 if a hit occurs
*/
void update_matrix(int x, int y, int*);


/**
Player can use navswitch to select which tile to fire at.
*/
void player_movement(int* x, int* y);


/*
send ready signal after ships have been placed
*/
void ready_signal(void);


/*
The player who pushes the navswitch down first 
is player 1. The other board will recieve a signal
that the game has started. Player 1 will shoot 
first
*/
int first_turn(void);


/*
After the user has fired a shot they send the co-ordinates 
corresponding to a specific character on the character
matrix
*/
void send_point(int*, int*, char*);

/*
After recieving shot character from other player 
determines which co-ordinates it is throuhg the 
character matrix. If hit displays the number of boats
the player has left. Sends back message to other player 
if its a hit or miss
*/
void recieve_point(int*, int*, char*, int*, int*);

#endif

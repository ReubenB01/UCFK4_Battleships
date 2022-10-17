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
#include "ir_uart.h"
#include "../fonts/font5x5_1.h"
#include "boat_setup.h"

#define HIT 'h'
#define MISS 'm'
#define READY 'r'
#define FIRST_CHARACTER '6'
#define LAST_CHARACTER 'X'
#define WIDTH 5
#define MAX_X 5
#define MAX_Y 7

/*
Takes in the x and y co-ordinates and the shot matrix
Updates the matrix with a 1 if a hit occurs
*/
void update_matrix(int, int, int*);


/*
Takes in x and y co-ordinate pointers
player can use navswitch to move their shot around
this update the x and y co-ordinates
*/
void player_movement(int*, int*);


/*
send ready signal after ships have been placed
*/
void ready_signal(void);


/*
The player who pushes the navswitch down first 
is player 1 this returnsa 1. The other board will recieve a signal
that the game has started and returns 0. Player 1 will shoot 
first
*/
int first_turn(void);


/*
Takes x and y co-ordinate and character matrix
after the user has fired a shot they send the co-ordinates 
corresponding to a specific character on the character
matrix
*/
void send_point(int*, int*, char*);

/*
Takes x and y co-ordinate, character and boat matrix, and the current turn
after recieving shot character from other player 
determines which co-ordinates it is throuhg the 
character matrix. If hit displays the number of boats
the player has left. Sends back message to other player 
if its a hit or miss
*/
void recieve_point(int*, int*, char*, int*, int*);

#endif

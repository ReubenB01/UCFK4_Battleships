/**
    @file led_display.h
    @author T. Glubb & R. Brown
    @date 17 October 2022
    @brief LED display support
*/

#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include "system.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "pacer.h"
#include "game.h"

/**
initialise tinygl.
set text font size to 5x5.
set text to scroll.
set text scroll speed to the message rate.
*/
void inititalise_tinygl(void);


/**
Takes coordinate player has fired at, the hit count and the shot matrix 
displays "HIT" message if a ship was placed on chosen coordinate.
displays "MISS" message if no ship on chosen coordinate.
coordinate is set to 1 if there was a hit.
coordinate is set to 2 is there was a miss.
*/ 
void hit_message (int board[7][5], int x_cord, int y_cord, int* count);


/**
if matrix coordinate = 1, blink the led -- this means that 
the shot was a hit.
if matrix coordinate = 2, leave led on -- this means that
the shot was a miss.
*/
void display_hits(int board[7][5]);

/*
If player has sunk all the ships (7 HITS) a win screen
appears, a losing message sends to other player
*/
void win_screen(int*);

/*
Takes shot count
if the losing message is recieved it appears on
the user's screen
*/
void lose_screen(void);

#endif

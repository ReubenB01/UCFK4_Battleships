#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include "system.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "pacer.h"
#include "game.h"

/**
initialise tinygl.
set text font size to 3x5.
set text to scroll.
set text scroll speed to the message rate.
*/
void inititalise_tinygl(void);


/**
Takes coordinate player has fired at. 
displays "HIT" message if a ship was placed on chosen coordinate.
displays "MISS" message if no ship on chosen coordinate.
coordinate is set to 2 if there was a hit.
coordinate is set to 3 is there was a miss.
*/ 
void hit_message (int board[7][5], int x_cord, int y_cord, int* count);


/**
if matrix coordinate = 2, blink the led.
if matrix coordinate = 3, leave led on.
*/
void display_hits(int board[7][5]);


void lose_screen(void);

#endif

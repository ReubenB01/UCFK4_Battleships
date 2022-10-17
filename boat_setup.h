/**
    @file boat_setup.h
    @author T. Glubb & R. Brown
    @date 17 October 2022
    @brief Boat setup support
*/


#ifndef BOAT_SETUP_H
#define BOAT_SETUP_H

#include "tinygl.h"
#include "button.h"
#include "pacer.h"
#include "game.h"

/*
The struct keeps track of the coordinates of
the start and end point for each boat, this uses
the tinygl x and y struct
*/
typedef struct {
    tinygl_point_t start;
    tinygl_point_t end;
} Points_t;

/*
When button pressed in the set-up this
rotates the boat from either horizontal
or vertical to have variability in boat placements
*/
Points_t rotate(Points_t, uint8_t);


/*
Initialises boat sizes with the Points_t struct
*/
Points_t points_init(int8_t, int8_t, int8_t, int8_t);


/*
Moves the current boat around the board with the navswitch
this is achieved by updates the coordinates of the start
and end positon -- when navswitch is pushed this sets boat
*/
Points_t boat_movement(Points_t , int* , int*, uint8_t);


/*
Sets the length of the current boat
*/
Points_t boat_size(uint8_t i);


/*
Main set up function which loops through the array of boat 
sizes until all boats have been placed and the boat matrix
is updated
*/
void set_up(int*);


/*
Shows the boats the user has already placed so they can
know where they've gone
*/
void display_boats(int*);

#endif

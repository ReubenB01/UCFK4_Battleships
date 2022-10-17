#ifndef BOAT_SETUP_H
#define BOAT_SETUP_H

#include "tinygl.h"
#include "button.h"
#include "pacer.h"
#include "navswitch.h"
#include "game.h"

typedef struct {
    tinygl_point_t start;
    tinygl_point_t end;
} Points_t;

int button_pressed_p (void);

Points_t rotate(Points_t points, uint8_t);

Points_t points_init(int8_t start_x, int8_t end_x, int8_t start_y, int8_t end_y);

Points_t boat_movement(Points_t , int* , int*, uint8_t);

Points_t boat_size(uint8_t i);

void set_up(int* matrix);

void display_boats(int* matrix);

#endif



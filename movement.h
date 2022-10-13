#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"

typedef struct {
    tinygl_point_t start;
    tinygl_point_t end;
} Points_t;

Points_t points_init(int8_t start_x, int8_t end_x, int8_t start_y, int8_t end_y);

Points_t boat_movement(Points_t, int*);

#endif
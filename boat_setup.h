#ifndef BOAT_SETUP_H
#define BOAT_SETUP_H

#include "system.h"
#include "navswitch.h"
#include "display.h"
#include "movement.h"
#include "pacer.h"
#include "tinygl.h"

Points_t boat_size(uint8_t i);

void set_up(void);

void display_boats(int* matrix);

#endif
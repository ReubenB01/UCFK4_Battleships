/**
    @file game.h
    @author T. Glubb & R. Brown
    @date 17 October 2022
    @brief Gameplay logic support
*/

#ifndef GAME_H
#define GAME_H


#include "button.h"
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "boat_setup.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"
#include "gameplay.h"
#include "led_display.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define MAX_X 5
#define MAX_Y 7
#define BLINKING 100
#define HIT 'h'
#define MISS 'm'
#define LOSE 'l'
#define READY 'r'
#define NUM_BOATS 4
#define SMALL_BOAT 1
#define MEDIUM_BOAT 2
#define LARGE_BOAT 3
#define FIRST_CHARACTER '6'
#define LAST_CHARACTER 'X'
#define WIDTH 5


#endif


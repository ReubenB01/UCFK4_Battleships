#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
<<<<<<< HEAD
#include "movement.h"
#include "boat_setup.h"


int main(void)
{

    system_init();
    navswitch_init();
    display_init();
    pacer_init (500);
    tinygl_init(500);


    while (1)
    {
        set_up();
    }
    

    
=======
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"
#include <stdbool.h>

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define MAX_X 4
#define MAX_Y 6

//top of ucfk4 is where usb plugs in//

void hit_message (int board[7][5], int x_cord, int y_cord);
void display_hits(int board[7][5]);
void win_screen (int board[7][5]);

void hit_message (int board[7][5], int x_cord, int y_cord)
{
    int (*ptr)[5];
    ptr = board;
    
    if (board[y_cord][x_cord] == 1)
    {
        ptr[y_cord][x_cord] = 2; //set coordinate in matrix to 2 so it is lit up
        tinygl_draw_message (" HIT", tinygl_point(0,1), 1); //display hit if there is a 1 at chosen tile
    }
    else
    {
        tinygl_draw_message (" MISS", tinygl_point(0,1), 1); //display miss if there is a 0 at chosen tile
    }
}

void display_hits(int board[7][5])
{
    int x = 0;
    int y = 0;
    
    for(x = 0; x < MAX_X; x++) {      //iterate through board matrix, if index == 2 a ship has been hit at that tile
        for (y = 0; y < MAX_Y; y++) {
            if (board[y][x] == 2) {
                tinygl_draw_point(tinygl_point(x, y), 1);
            }
        }
    }
}

void win_screen (int board[7][5])
{
    int x = 0;
    int y = 0;
    int count = 0;
    
    for(x = 0; x < MAX_X; x++) {      //iterate through board matrix, if no ships left there is a winner
        for (y = 0; y < MAX_Y; y++) {
            if (board[y][x] == 1)
            {
                count++;
            }
        }
    }
    if (count == 0)
    {
        tinygl_clear();
        tinygl_text(" WIN");
        while(1)
        {
            pacer_wait();
            tinygl_update();
        }
    }
    
}


int main (void)
{
    int board[7][5] = {
                 {1, 1, 1, 1, 0},
                 {0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0}
                 };
    
    int x = 0;
    int y = 0;
    

    system_init ();

    tinygl_init(PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    navswitch_init();

    pacer_init (PACER_RATE);
    
    while(1)
    {
        pacer_wait ();

        tinygl_update();   
        navswitch_update();
        
        
        if (navswitch_push_event_p(NAVSWITCH_NORTH))
        {
            tinygl_draw_point (tinygl_point(x, y), 0);
            y --;    
        }
        
        if (navswitch_push_event_p(NAVSWITCH_SOUTH))
        {
            tinygl_draw_point (tinygl_point(x, y), 0);
            y ++;    
        }
        
        if (navswitch_push_event_p(NAVSWITCH_EAST))
        {
            tinygl_draw_point (tinygl_point(x, y), 0);
            x ++;    
        }
        
        if (navswitch_push_event_p(NAVSWITCH_WEST))
        {
            tinygl_draw_point (tinygl_point(x, y), 0);
            x --;    
        }
        
        if (navswitch_push_event_p(NAVSWITCH_PUSH))
        {
            hit_message(board, x, y);
        }
        
        tinygl_draw_point (tinygl_point(x, y), 1);
        display_hits(board);
        win_screen(board);
    }
    return 0;
>>>>>>> 2ad4912eac3b9d61ee0ec8487444d8ea8e33369c
}

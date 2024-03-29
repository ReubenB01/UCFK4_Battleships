/**
    @file led_display.c
    @author T. Glubb & R. Brown
    @date 17 October 2022
    @brief LED display module
*/

#include "led_display.h"


/**
initialise tinygl.
set text font size to 5x5.
set text to scroll.
set text scroll speed to the message rate.
*/
void inititalise_tinygl(void)
{
    tinygl_init(1750);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}


/**
Takes coordinate player has fired at, the hit count and the shot matrix 
displays "HIT" message if a ship was placed on chosen coordinate.
displays "MISS" message if no ship on chosen coordinate.
coordinate is set to 1 if there was a hit.
coordinate is set to 2 is there was a miss.
*/ 
void hit_message (int matrix[7][5], int x, int y, int* count)
{
    int (*ptr)[5];
    ptr = matrix;
    tinygl_clear();
    
    if (matrix[y][x] == 1) //if chosen coordinate is a ship
    {
        *count = *count + 1;
        tinygl_text("HIT"); //display hit message
    }
    else if (matrix[y][x] == 0)
    {
        tinygl_text("MISS"); //display miss message
        ptr[y][x] = 2; //set coordinate in matrix to 2
    }
    for (int i = 0; i < 2000; i++) { //
        pacer_wait();
        tinygl_update();
    }
    tinygl_clear();
}


/**
if matrix coordinate = 1, blink the led -- this means that 
the shot was a hit.
if matrix coordinate = 2, leave led on -- this means that
the shot was a miss.
*/
void display_hits(int shot_matrix[7][5])
{
    int x = 0;
    int y = 0;

    static int blink_timer = 0;
    static int led_state = 0;
    
    for(x = 0; x < MAX_X; x++) { //iterate through board matrix
        for (y = 0; y < MAX_Y; y++) {
            if (shot_matrix[y][x] == 1) { //if coordinate in matrix is a 2(hit), blink the led
                if (blink_timer == BLINKING) {
                    
                    tinygl_draw_point(tinygl_point(x, y), led_state);
                }
            } else if (shot_matrix[y][x] == 2) { // if coordinate in matrix is a 3(miss), turn led on
                
                tinygl_draw_point(tinygl_point(x, y), 1);
            }
        }
    }

    if (blink_timer == BLINKING) { // this changes the state of the LED when the LED counter is reached
        blink_timer = 0;
        if (led_state ==0) {
            led_state = 1; 
        } else {
            led_state = 0;
        }
    }

    tinygl_update();
    blink_timer++;
}


/*
Takes shot count
If player has sunk all the ships (7 HITS) a win screen
appears, a losing message sends to other player
*/
void win_screen(int* count)
{
    if (*count == 7) { // if count == 7, all ships are sunk
        tinygl_clear();
        tinygl_text("WIN"); //display win message on winner's board
        ir_uart_putc(LOSE);
        
        while(1) {
            pacer_wait();
            tinygl_update();
            
        }
    }   
}

/*
If the losing message is recieved it appears on
the user's screen
*/
void lose_screen(void) {
    tinygl_clear();
    tinygl_text("LOSE"); //display win message on winner's board
        while(1) {
            pacer_wait();
            tinygl_update();
        }
}

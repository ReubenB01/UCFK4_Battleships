#include "led_display.h"

void inititalise_tinygl(void)
{
    tinygl_init(1750);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}


void hit_message (int matrix[7][5], int x_cord, int y_cord, int* count)
{
    int (*ptr)[5];
    ptr = matrix;
    tinygl_clear();
    
    if (matrix[y_cord][x_cord] == 1) //if chosen coordinate is a ship
    {
        ptr[y_cord][x_cord] = 2; //set coordinate in matrix to 2
        *count = *count + 1;
        tinygl_draw_message("HIT", tinygl_point(0,1), 1); //display hit message
    }
    else if (matrix[y_cord][x_cord] == 0)
    {
        tinygl_draw_message("MISS", tinygl_point(0,1), 1); //display miss message
        ptr[y_cord][x_cord] = 3; //set coordinate in matrix to 3 
    }
    for (int i = 0; i < 2000; i++) { //
        pacer_wait();
        tinygl_update();
    }
    tinygl_clear();
}


void display_hits(int shot_matrix[7][5])
{
    int x = 0;
    int y = 0;

    static int blink_rate = 0;
    static int led_state = 0;
    
    for(x = 0; x < MAX_X; x++) { //iterate through board matrix
        for (y = 0; y < MAX_Y; y++) {
            if (shot_matrix[y][x] == 2) { //if coordinate in matrix is a 2(hit), blink the led
                if (blink_rate == BLINKING) {
                    tinygl_draw_point(tinygl_point(x, y), led_state);
                }
            } else if (shot_matrix[y][x] == 3) { // if coordinate in matrix is a 3(miss), turn led on
                tinygl_draw_point(tinygl_point(x, y), 1);
            }
        }
    }
    if (blink_rate == BLINKING) {
        blink_rate = 0;
        if (led_state ==0) {
            led_state =1; 
        } else {
            led_state = 0;
        }
    }
    tinygl_update();
    blink_rate++;
}

void lose_screen(void) {
    tinygl_clear();
    tinygl_text("LOSE"); //display win message on winner's board
        while(1)
        {
            pacer_wait();
            tinygl_update();
        }
}

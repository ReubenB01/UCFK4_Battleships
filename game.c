#include "game.h"

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


int main (void)
{    
    int x = 0;
    int y = 0;

    int boat_matrix[7][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
                 };

int shot_matrix[7][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
                };

char character_matrix[7][5] = {
    {'6', '7', '8', '9', ':'},
    {';', '<', '=', '>', '?'},
    {'@', 'A', 'B', 'C', 'D'},
    {'E', 'F', 'G', 'H', 'I'},
    {'J', 'K', 'L', 'M', 'N'}, 
    {'O', 'P', 'Q', 'R', 'S'},
    {'T', 'U', 'V', 'W', 'X'}
};

    
    system_init ();
    pacer_init (PACER_RATE);
    display_init();
    ir_uart_init();
    inititalise_tinygl(); // initialise tinygl
    navswitch_init();
    
    int count = 0; // counts how many hits player has
    int turn = first_turn();
    
    set_up((int*)boat_matrix);
    ready_signal();
    display_clear();
    display_update();
    
    while(1)
    {
        display_hits(shot_matrix);
        pacer_wait ();
        tinygl_update();   
        navswitch_update();
        if (turn == 1) {
            if (ir_uart_read_ready_p() && ir_uart_getc() == 'l') {
                lose_screen();
            }
            tinygl_draw_point (tinygl_point(x, y), 1);
            player_movement(&x, &y);
            
            if (navswitch_push_event_p(NAVSWITCH_PUSH))
            {
                send_point(&x, &y, (char*)character_matrix);
                                   
                tinygl_draw_point (tinygl_point(x, y), 0);
                
                turn = 2;
            } 
        }
    
        if (turn == 2 && ir_uart_read_ready_p()) {
            char shot = ir_uart_getc();
            if (shot == HIT) {
                update_matrix(x, y, (int*)shot_matrix);
                hit_message(shot_matrix, x, y, &count);
                turn = 0;
                
            } else if (shot == MISS) { 
                hit_message(shot_matrix, x, y, &count);
                turn = 0;
            }
        }
        
        if (turn == 0) {
            if (ir_uart_read_ready_p()) {    
                char r_character = ir_uart_getc();
                if (r_character >= '6' && r_character <= 'X') {
                    for (int i = 0; i < MAX_X; i++) {
                        for (int j = 0; j < MAX_Y; j++) {
                            char c = character_matrix[j][i];
                            if ( c == r_character) {
                                x = i;
                                y = j;
                            } 
                        }
                    }
        if (boat_matrix[y][x] == 1) {
            ir_uart_putc(HIT);
            boat_matrix[y][x] = 0;
            tinygl_clear();
            for (int i = 0; i < 1000; i++) { 
                pacer_wait();
                display_boats((int*)boat_matrix);
        }
            tinygl_clear();
        } else {
            ir_uart_putc(MISS);
        }
        turn = 1;
        }
    }    
} 
    
     
    win_screen(&count); // checks if a player has won
    }
}


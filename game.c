#include "game.h"
#include "button.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define BLINKING 100
//top of ucfk4 is where usb plugs in//

//void hit_message (int matrix[7][5], int x_cord, int y_cord);
//void display_hits(int matrix[7][5]);

void hit_message (int matrix[7][5], int x_cord, int y_cord)
{
    int (*ptr)[5];
    ptr = matrix;

    tinygl_clear();
    if (matrix[y_cord][x_cord] == 1)
    {
        ptr[y_cord][x_cord] = 2; //set coordinate in matrix to 2 so it is lit up
        tinygl_draw_message("HIT", tinygl_point(0,1), 1); //display hit if there is a 1 at chosen tile
    }
    else if (matrix[y_cord][x_cord] == 0)
    {
        tinygl_draw_message("MISS", tinygl_point(0,1), 1); //display miss if there is a 0 at chosen tile
        ptr[y_cord][x_cord] = 3;
    }
    for (int i = 0; i < 1000; i++) {
        pacer_wait();
        tinygl_update();
    }
    tinygl_clear();
}



void display_hits(int their_matrix[7][5])
{
    int x = 0;
    int y = 0;

    static int blink_rate = 0;
    static int led_state = 0;
    
    for(x = 0; x < MAX_X; x++) {      //iterate through board matrix, if index == 2 a ship has been hit at that tile
        for (y = 0; y < MAX_Y; y++) {
            if (their_matrix[y][x] == 2) {
                if (blink_rate == BLINKING) {
                    tinygl_draw_point(tinygl_point(x, y), led_state);
                }
            } else if (their_matrix[y][x] == 3) {
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



void win_screen(int count)
{
    if (count == 6)
    {
        tinygl_clear();
        tinygl_text("WIN");
        while(1)
        {
            pacer_wait();
            tinygl_update();
        }
    }
    
}

void player_movement(int* x, int* y) {
    if (navswitch_push_event_p(NAVSWITCH_NORTH))
        {
            tinygl_draw_point (tinygl_point(*x, *y), 0);
            *y = *y - 1;    
        }
        
    if (navswitch_push_event_p(NAVSWITCH_SOUTH))
        {
            tinygl_draw_point (tinygl_point(*x, *y), 0);
            *y = *y + 1;    
        }
        
    if (navswitch_push_event_p(NAVSWITCH_EAST))
        {
            tinygl_draw_point (tinygl_point(*x, *y), 0);
            *x =*x + 1;    
        }
        
    if (navswitch_push_event_p(NAVSWITCH_WEST))
        {
            tinygl_draw_point (tinygl_point(*x, *y), 0);
            *x= *x - 1;    
        }        
}

void update_matrix(int x, int y, int* their_matrix) {
    *(their_matrix + (5 * y) + x) = 1;
}

void ready_signal(void)
{
    //send ready signal after ships have been placed
    int ready = 0;
    int received = 0;
    while(ready == 0) {
        ir_uart_putc ('1');
        received = ir_uart_getc();
        if (received == '1') {
            pacer_wait();
            ready = 1;
        }
    }
}

int first_turn(void) {

    tinygl_text("?");

    while(1) {
        navswitch_update();
        tinygl_update();
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            display_clear();
            tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
            tinygl_update();
            ir_uart_putc_nocheck(50);
            return 1;
        } 
        if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == 50) {
                display_clear();
                tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
                tinygl_update();
                ir_uart_putc_nocheck(50);
                return 0;
            }
        }
    }
}


int my_matrix[7][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
                 };

int their_matrix[7][5] = {
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

void send_point(int* x, int* y ) 
{
    char character = character_matrix[*x][*y];
    ir_uart_putc(character);
}


int main (void)
{

    
    int x = 0;
    int y = 0;
    
    system_init ();
    pacer_init (PACER_RATE);
    display_init();
    ir_uart_init();

    tinygl_init(PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    navswitch_init();
    //int count = 0;
    int turn = first_turn();
    set_up((int*)my_matrix);
    //ready_signal();
    display_clear();
    display_update();
    
    while(1)
    {
        display_hits(their_matrix);
        pacer_wait ();
        tinygl_update();   
        navswitch_update();
        if (turn == 1) {
            tinygl_draw_point (tinygl_point(x, y), 1);
            player_movement(&x, &y);
            if (navswitch_push_event_p(NAVSWITCH_PUSH))
            {
                send_point(&x, &y);
                                   
                tinygl_draw_point (tinygl_point(x, y), 0);
                
                turn = 2;
                
            } 
        }
    
        if (turn == 2 && ir_uart_read_ready_p()) {
            char shot = ir_uart_getc();
            if (shot == 'h') {
                update_matrix(x, y, (int*)their_matrix);
                hit_message(their_matrix, x, y);
                turn = 0;
                
            } else if (shot == 'm') { 
                hit_message(their_matrix, x, y);
                turn = 0;
            }
    }
        
    if (turn == 0) {
        if (ir_uart_read_ready_p()) {    
        char r_character = ir_uart_getc();
        if (r_character >= '6' && r_character <= 'X') {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 7; j++) {
                    char c =character_matrix[j][i];
                    if ( c == r_character) {
                        x = i;
                        y = j;
                    }

                
            }
        }
        if (my_matrix[y][x] == 1) {
            ir_uart_putc('h');
        } else {
            ir_uart_putc('m');
        }
        turn = 1;
        }


    }

        
    }  
    //win_screen(count);
    
    
    }
}

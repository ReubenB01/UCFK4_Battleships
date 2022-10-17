#include "gameplay.h"


void update_matrix(int x, int y, int* shot_matrix)
{
    *(shot_matrix + (5 * y) + x) = 1;
}


void player_movement(int* x, int* y) 
{
    if (navswitch_push_event_p(NAVSWITCH_NORTH) && *y != 0) {
        tinygl_draw_point (tinygl_point(*x, *y), 0);
        *y = *y - 1;    
    }
        
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && *y != 6) {
        tinygl_draw_point (tinygl_point(*x, *y), 0);
        *y = *y + 1;    
    }
        
    if (navswitch_push_event_p(NAVSWITCH_EAST) && *x != 4) {
        tinygl_draw_point (tinygl_point(*x, *y), 0);
        *x =*x + 1;    
    }
        
    if (navswitch_push_event_p(NAVSWITCH_WEST) && *x != 0) {
        tinygl_draw_point (tinygl_point(*x, *y), 0);
        *x= *x - 1;    
    }        
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


int first_turn(void) 
{
    tinygl_text(" BATTLE SHIPS"); //start screen text

    while(1) {
        navswitch_update();
        tinygl_update();
        
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            display_clear();
            tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
            tinygl_update();
            ir_uart_putc_nocheck(50);
            return 1;
        }
         
        if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == 50) {
                display_clear();
                tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
                tinygl_update();
                ir_uart_putc_nocheck(50);
                return 0;
            }
        }
    }
}


void send_point(int* x, int* y, char* character_matrix) 
{
    char character = *(character_matrix + (5 * *y) + *x);
    ir_uart_putc(character);
}

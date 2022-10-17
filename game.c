/**
    @file game.c
    @author T. Glubb & R. Brown
    @date 17 October 2022
    @brief Main game modules
*/

#include "boat_setup.h"
#include "gameplay.h"
#include "led_display.h"


int main (void)
{    
    int x = 0;
    int y = 0;

    int boat_matrix[7][5] = { // The boats the user has placed
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
                };

    int shot_matrix[7][5] = {// Keeps track of the user's shots
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
                };

    char character_matrix[7][5] = { //Each co-ordinate corresponds to a special character so can use putc function
                {'6', '7', '8', '9', ':'},
                {';', '<', '=', '>', '?'},
                {'@', 'A', 'B', 'C', 'D'},
                {'E', 'F', 'G', 'H', 'I'},
                {'J', 'K', 'L', 'M', 'N'}, 
                {'O', 'P', 'Q', 'R', 'S'},
                {'T', 'U', 'V', 'W', 'X'}
                };

    
    system_init();
    pacer_init (PACER_RATE);
    display_init();
    ir_uart_init();
    inititalise_tinygl(); // initialise tinygl
    navswitch_init();
    
    int count = 0; // counts how many hits player has
    int turn = first_turn(); // determines who shoots first after set-up
    
    set_up((int*)boat_matrix); 
    ready_signal();
    display_clear();
    
    while(1) {
        display_hits(shot_matrix);
        pacer_wait ();
        tinygl_update();   
        navswitch_update();
        
        if (turn == 1) {
            if (ir_uart_read_ready_p() && ir_uart_getc() == 'l') { // checks if a loss message is recieved 
                lose_screen();
            }
            
            tinygl_draw_point (tinygl_point(x, y), 1);
            player_movement(&x, &y);
            
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                send_point(&x, &y, (char*)character_matrix);                  
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
                recieve_point(&x, &y, (char*)character_matrix, (int*)boat_matrix, &turn);                 
            }    
        }
        
    win_screen(&count); // checks if a player has won
    }
}

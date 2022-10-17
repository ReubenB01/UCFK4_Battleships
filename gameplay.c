/**
    @file gameplay.h
    @author T. Glubb & R. Brown
    @date 17 October 2022
    @brief Gameplay logic module
*/

#include "gameplay.h"

/*
Takes in the x and y co-ordinates and the shot matrix
Updates the matrix with a 1 if a hit occurs
*/
void update_matrix(int x, int y, int* shot_matrix)
{
    *(shot_matrix + (WIDTH * y) + x) = 1; //updates the matrix if hit
}

/*
Takes in x and y co-ordinate pointers
player can use navswitch to move their shot around
this update the x and y co-ordinates
*/
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

/*
send ready signal after ships have been placed
*/
void ready_signal(void) 
{
    
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

/*
The player who pushes the navswitch down first 
is player 1 this returnsa 1. The other board will recieve a signal
that the game has started and returns 0. Player 1 will shoot 
first
*/
int first_turn(void) 
{
    tinygl_text(" BATTLE SHIPS"); // Start screen text

    while(1) {
        navswitch_update();
        tinygl_update();
        
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) { // If navswitch push the user is player 1
            display_clear();
            tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            tinygl_update();
            ir_uart_putc(READY); // Sends ready message to other player
            return 1;
        }
         
        if (ir_uart_read_ready_p()) { 
            if (ir_uart_getc() == READY) { // If it recieves ready message
                display_clear();
                tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
                tinygl_update();
                return 0;
            }
        }
    }
}

/*
Takes x and y co-ordinate and character matrix
after the user has fired a shot they send the co-ordinates 
corresponding to a specific character on the character
matrix
*/
void send_point(int* x, int* y, char* character_matrix) 
{
    char character = *(character_matrix + (WIDTH * *y) + *x); // Changes co-ordinates of shot to character
    ir_uart_putc(character);
}


/*
Takes x and y co-ordinate, character and boat matrix, and the current turn
after recieving shot character from other player 
determines which co-ordinates it is throuhg the 
character matrix. If hit displays the number of boats
the player has left. Sends back message to other player 
if its a hit or miss
*/
void recieve_point(int* x, int* y, char* character_matrix, int* boat_matrix, int* turn)
{
    char r_character = ir_uart_getc();
    if (r_character >= FIRST_CHARACTER && r_character <= LAST_CHARACTER) { // If the message recieved is in the bounds of the character matrix
        for (int i = 0; i < MAX_X; i++) {
            for (int j = 0; j < MAX_Y; j++) {
                if (*(character_matrix + (WIDTH * j) + i) == r_character) {
                    *x = i;
                    *y = j;
                } 
            }
        }
                    
        if (*(boat_matrix + (WIDTH * *y) + *x) == 1) { 
            ir_uart_putc(HIT);
            *(boat_matrix + (WIDTH * *y) + *x) = 0; // Shows user their remaining boats
            tinygl_clear();
        
            for (int i = 0; i < 1000; i++) { 
                pacer_wait();
                display_boats((int*)boat_matrix);
            }
            tinygl_clear();
            
        } else {
            ir_uart_putc(MISS);
        }
        *turn = 1; 
    }
}

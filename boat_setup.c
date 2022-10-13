#include "system.h"
#include "navswitch.h"
#include "display.h"
#include "movement.h"
#include "pacer.h"
#include "tinygl.h"

Points_t boat_size(uint8_t i) {
    int8_t start_x, end_x, start_y, end_y; 
    int8_t boats[5] = {3, 1, 2, 2, 3};
    start_y = 0;
    end_y = 0;
    if (boats[i] == 1) {
        start_x = 0;
        end_x = 0;        
    } else if (boats[i] == 2) {
        start_x = 0;
        end_x = 1;
    } else {
        start_x = 0;
        end_x = 2;
    }
    Points_t points = points_init(start_x, end_x, start_y, end_y);
    return points;
}

void display_boats(int* matrix)
{
    for (uint8_t i=0; i < 5; i++) {
        for (uint8_t j=0; j<7; j++) {
            if (*(matrix + ((5 * i) + j)) == 1) {
                display_pixel_set(i, j, 1);
            }

        }
    }
}

void set_up(void) {
    int matrix[7][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    for (uint8_t i = 0; i < 5; i++) {
        Points_t points = boat_size(i);
        tinygl_draw_line(points.start, points.end, 1);
        int going = 0;
        while (going!= 1)
        {
            
            pacer_wait();
            points = boat_movement(points, (int*)matrix);
            tinygl_update();
            if (navswitch_push_event_p(NAVSWITCH_PUSH)){
                going =1;
            display_boats((int*)matrix);
            display_update();    
            }
        }
    }
}
#include "system.h"
#include "navswitch.h"
#include "display.h"
#include "tinygl.h"
#include "button.h"
#include "boat_setup.h"


Points_t points_init(int8_t startx, int8_t endx, int8_t starty, int8_t endy)
{
    Points_t points;
    points.start.x = startx;
    points.end.x = endx;
    points.start.y = starty;
    points.end.y = endy;
    return points;
}

Points_t boat_movement(Points_t points, int* matrix, int* placed)
{
    navswitch_update(); 
    button_init ();
    tinygl_draw_line(points.start, points.end, 1); 
    
        
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        tinygl_clear();
        if (points.end.y != 0) { 
            points.start.y = points.start.y - 1;
            points.end.y = points.end.y -1;
        }
        
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        tinygl_clear();
        if (points.start.y != 6) {
            points.start.y = points.start.y + 1;
            points.end.y = points.end.y + 1;
        }
        
        }

    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        tinygl_clear();
        if (points.end.x != 4) {
            points.start.x = points.start.x + 1;
            points.end.x = points.end.x + 1;
        }
        
        }

    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        tinygl_clear();
        if (points.start.x != 0) {
            points.start.x = points.start.x - 1;
            points.end.x = points.end.x - 1;
        }
        
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            for (int i=0; i < 5; i++) {
                for (int j=0 ; j< 7; j++) {
                    tinygl_point_t t_point = tinygl_point(i,j);
                    if (*(matrix + (5 * j) + i) != 1 && tinygl_pixel_get(t_point) == 1) {
                            *(matrix + (5 * j) + i) = 1;
                            *placed = 1;
                        }
                    }
                }
            }  
        button_update ();

        if (button_push_event_p(0)) {
            tinygl_clear();
            int save_start = points.start.x;
            int save_end = points.end.x;
            points.start.x = points.start.y;
            points.start.y = save_start;
            points.end.x = points.end.y;
            points.end.y = save_end;
            tinygl_draw_line(points.start, points.end, 1); 
        }



    return points;
}


Points_t boat_size(uint8_t i) {
    int8_t start_x, end_x, start_y, end_y; 
    int8_t boats[5] = {3, 2, 1, 1};
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
            if (*(matrix + (5 * j) + i) == 1) {
                display_pixel_set(i, j, 1);
            }

        }
    }
    display_update();
}

void set_up(int* matrix) {
    tinygl_init (1000);

    for (uint8_t i = 0; i < 4; i++) {
        Points_t points = boat_size(i);
        tinygl_draw_line(points.start, points.end, 1);
        int placed = 0;
        while (placed!= 1)
        {
            
            pacer_wait();
            points = boat_movement(points, (int*)matrix, &placed);
            display_boats((int*)matrix);
            tinygl_update();
            
            
        }
    }
}


#include "boat_setup.h"


Points_t points_init(int8_t start_x, int8_t end_x, int8_t start_y, int8_t end_y)
{
    Points_t points;
    points.start.x = start_x;
    points.end.x = end_x;
    points.start.y = start_y;
    points.end.y = end_y;
    return points;
}


Points_t rotate(Points_t points, uint8_t current_boat) {
    tinygl_clear();
    if (points.start.x == points.end.x && points.start.x) {
        points.start.y = points.end.y;
        points.start.x = points.start.x - (current_boat - 1);
        
    } else if (points.start.y == points.end.y) {
        points.start.x = points.end.x;
        points.start.y = points.start.y + (current_boat -1);
    }
    
    tinygl_draw_line(points.start, points.end, 1); 
    return points;
}


Points_t boat_movement(Points_t points, int* matrix, int* placed, uint8_t current_boat)
{
    navswitch_update(); 
    button_init ();
    tinygl_draw_line(points.start, points.end, 1); 
    
    if (navswitch_push_event_p (NAVSWITCH_NORTH) && points.start.y != 0 && points.end.y != 0) {
        tinygl_clear();
        points.start.y = points.start.y - 1;
        points.end.y = points.end.y -1; 
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH) && points.end.y != 6 && points.start.y != 6) {
        tinygl_clear();
        points.start.y = points.start.y + 1;
        points.end.y = points.end.y + 1;
    }

    if (navswitch_push_event_p (NAVSWITCH_EAST) && points.end.x != MAX_X -1) {
        tinygl_clear();
        points.start.x = points.start.x + 1;
        points.end.x = points.end.x + 1;
    }

    if (navswitch_push_event_p (NAVSWITCH_WEST) && points.start.x != 0) {
        tinygl_clear();
        points.start.x = points.start.x - 1;
        points.end.x = points.end.x - 1;
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
        points = rotate(points, current_boat);
    }

    return points;
}


Points_t boat_size(uint8_t current_boat) {
    int8_t start_x, end_x, start_y, end_y; 
    start_y = 0;
    end_y = 0;
    if (current_boat == 1) {
        start_x = 0;
        end_x = 0;        
    } else if (current_boat == 2) {
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
    for (uint8_t i=0; i < MAX_X; i++) {
        for (uint8_t j=0; j<MAX_Y; j++) {
            if (*(matrix + (5 * j) + i) == 1) {
                display_pixel_set(i, j, 1);
            }
        }
    }
    
    display_update();
}


void set_up(int* matrix) {
    tinygl_init (1000);
    int8_t boats[5] = {3, 2, 1, 1};

    for (uint8_t i = 0; i < NUM_BOATS; i++) {
        int placed = 0;
        uint8_t current_boat = boats[i];
        Points_t points = boat_size(current_boat);
        tinygl_draw_line(points.start, points.end, 1);
        
        while (placed!= 1)
        {
            pacer_wait();
            points = boat_movement(points, (int*)matrix, &placed, current_boat);
            display_boats((int*)matrix);
            tinygl_update();
        }
    }
}



#include "system.h"
#include "navswitch.h"
#include "display.h"
#include "movement.h"
#include "pacer.h"
#include "tinygl.h"

Points_t points_init(int8_t startx, int8_t endx, int8_t starty, int8_t endy)
{
    Points_t points;
    points.start.x = startx;
    points.end.x = endx;
    points.start.y = starty;
    points.end.y = endy;
    return points;
}

Points_t boat_movement(Points_t points, int* matrix)
{
     navswitch_update(); 
        
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        tinygl_clear();
        if (points.end.y != 0) { 
            points.start.y = points.start.y - 1;
            points.end.y = points.end.y -1;
        }
        tinygl_draw_line(points.start, points.end, 1);
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        tinygl_clear();
        if (points.start.y != 6) {
            points.start.y = points.start.y + 1;
            points.end.y = points.end.y + 1;
        }
        tinygl_draw_line(points.start, points.end, 1);
        }

    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        tinygl_clear();
        if (points.end.x != 4) {
            points.start.x = points.start.x + 1;
            points.end.x = points.end.x + 1;
        }
        tinygl_draw_line(points.start, points.end, 1); 
        }

    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        tinygl_clear();
        if (points.start.x != 0) {
            points.start.x = points.start.x - 1;
            points.end.x = points.end.x - 1;
        }
        tinygl_draw_line(points.start, points.end, 1); 
        }

    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        if (points.start.x == points.end.x) {
            uint8_t j = points.start.y;
            while (j < (points.end.y + 1)) {
                *(matrix + ((5 * points.start.x) + j)) = 1;
                j--;
            }
        }
    }
    return points;
}


#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "movement.h"
#include "boat_setup.h"


int main(void)
{

    system_init();
    navswitch_init();
    display_init();
    pacer_init (500);
    tinygl_init(500);


    while (1)
    {
        set_up();
    }
    

    
}

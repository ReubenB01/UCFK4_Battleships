#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pio.h"


/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

int main(void)
{

    system_init ();
    navswitch_init ();
    ir_uart_init ();

    for (uint8_t i = 0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
    for (uint8_t i = 0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }

    pio_output_high(cols[1]);

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        
        if (navswitch_push_event_p (NAVSWITCH_NORTH))
            character++;

        if (navswitch_push_event_p (NAVSWITCH_SOUTH))
            character--;

        if (navswitch_push_event_p (NAVSWITCH_EAST))
            character--;

        if (navswitch_push_event_p (NAVSWITCH_WEST))
            character--;

        display_character(character);
        
    }

    return 0;
}

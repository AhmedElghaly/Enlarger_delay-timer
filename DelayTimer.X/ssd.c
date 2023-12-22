#include "ssd.h"
#include "gpio.h"

#define NUMBER_OF_SSD (2)

tSSD_Value ssd_values[NUMBER_OF_SSD] = {SSD_NULL};

static unsigned char ssd_data[] =
{
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000, // 9
    0b00000000  // NULL
};

void SSD_Init(tSSD ssd, tSSD_State initial_state, tSSD_Value initial_value)
{
    /* Initialize SSD Hardware */
    /* Initialize SSD Data pins */

    GPIO_InitPort(PORT_C, GPIO_OUTPUT);
    GPIO_SetPortState(PORT_C, ssd_data[SSD_NULL]);

    /* Initialize SSD State pins */

    switch(ssd)
    {
        case SSD_L:
            GPIO_InitPortPin(PORT_A, 6, GPIO_OUTPUT); //connected with port A pin 6
            break;
        case SSD_R:
            GPIO_InitPortPin(PORT_A, 7, GPIO_OUTPUT); //connected with port A pin 7
            break;
        default:
            /* Should not be here */

            break;
    }

    /* Set initial State */

    SSD_SetState(ssd, initial_state);

    /* Set initial value */

    SSD_SetValue(ssd, initial_value);
}

void SSD_Update(void)
{
    static tSSD current_ssd = SSD_L;
    /* Turn off all ssd */

    SSD_SetState(SSD_L, SSD_OFF);
    SSD_SetState(SSD_R, SSD_OFF);

    /*Set current ssd output */

    GPIO_SetPortState(PORT_C, ssd_data[ssd_values[current_ssd]]);

    /* Turn on current ssd */

    SSD_SetState(current_ssd, SSD_ON);

    if(current_ssd == SSD_R)
    {
       current_ssd = SSD_L;
    }
    else
    {
        current_ssd++;
    }
}

void SSD_SetValue(tSSD ssd, tSSD_Value value)
{
    ssd_values[ssd] = value;
}
void SSD_SetState(tSSD ssd, tSSD_State state)
{
    switch(ssd)
    {
        case SSD_L:
            GPIO_SetPortPinState(PORT_A, 6, state); //connected with port A pin 6
            break;
        case SSD_R:
            GPIO_SetPortPinState(PORT_A, 7, state); //connected with port A pin 7
            break;
        default:
            /* Should not be here */

            break;
    }
}
tSSD_Value SSD_GetValue(tSSD ssd)
{
   tSSD_Value ret = SSD_NULL;

   ret = ssd_values[ssd];

   return ret;
}
tSSD_State SSD_GetState(tSSD ssd)
{
    tSSD_State ret = SSD_OFF;

    switch(ssd)
    {
        case SSD_L:
            ret = GPIO_GetPortPinState(PORT_A, 6); //connected with port A pin 6
            break;
        case SSD_R:
            ret = GPIO_GetPortPinState(PORT_A, 7); //connected with port A pin 7
            break;
        default:
            /* Should not be here */
            break;
    }
    return ret;
}

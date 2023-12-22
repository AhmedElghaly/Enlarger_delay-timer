#include "push_button.h"
#include "gpio.h"

#define NUMBER_OF_SAMPLE  (2)
#define NUMBER_OF_PUSH_BUTTONS  (8)

#define PB_PRESSED_VOLTAGE  (0)
#define PB_RELEASED_VOLTAGE  (1)


typedef struct
{
    unsigned char samples[NUMBER_OF_SAMPLE];
    tPB_State state;
}tPB_Info;

static tPB_Info pb_info[NUMBER_OF_PUSH_BUTTONS]; // because I need it for every button

void PB_Init(tPB pb, tPB_State initial_state)
{
    /* initialize hw pins */
    switch(pb)
    {
        case PB_UP:
            GPIO_InitPortPin(PORT_A, 0, GPIO_INPUT);
            break;
        case PB_DOWN:
            GPIO_InitPortPin(PORT_A, 1, GPIO_INPUT);
            break;
        case PB_FOCUS:
            GPIO_InitPortPin(PORT_A, 5, GPIO_INPUT);
            break;
        case PB_RESET:
            GPIO_InitPortPin(PORT_A, 4, GPIO_INPUT);
            break;
        case PB_PAUSE:
            GPIO_InitPortPin(PORT_B, 2, GPIO_INPUT);
            break;
        case PB_IR_ENABLE:
            GPIO_InitPortPin(PORT_B, 1, GPIO_INPUT);
            break;
        case PB_IP_ENABLE:
            GPIO_InitPortPin(PORT_A, 3, GPIO_INPUT);
            break;
        case PB_CAMERA_TRIGGER:
            GPIO_InitPortPin(PORT_B, 0, GPIO_INPUT);
            break;
        default:
            /* should not be here */
            break;
    }

    /* initialize state */
    pb_info[pb].state = initial_state;

    /* initialize samples */
    switch(initial_state)
    {
        case PB_RELEASED:
        case PB_PRE_RELEASED:
            pb_info[pb].samples[0] = PB_RELEASED_VOLTAGE;
            pb_info[pb].samples[1] = PB_RELEASED_VOLTAGE;
            break;

        case PB_PRESSED:
        case PB_PRE_PRESSED:
            pb_info[pb].samples[0] = PB_PRESSED_VOLTAGE;
            pb_info[pb].samples[1] = PB_PRESSED_VOLTAGE;
            break;
        default:
            /* should not be here */
            break;
    }
}
void PB_Update(void)
{
    tPB current_button = PB_UP;
    for(current_button = PB_UP; current_button <= PB_CAMERA_TRIGGER; current_button ++)
    {
        /* Update samples */
        pb_info[current_button].samples[0] = pb_info[current_button].samples[1];

        switch(current_button)
        {
            case PB_UP:
                pb_info[current_button].samples[1] = GPIO_GetPortPinState(PORT_A, 0);
                break;
            case PB_DOWN:
                pb_info[current_button].samples[1] = GPIO_GetPortPinState(PORT_A, 1);
                break;
            case PB_FOCUS:
                pb_info[current_button].samples[1] = GPIO_GetPortPinState(PORT_A, 5);
                break;
            case PB_RESET:
                pb_info[current_button].samples[1] = GPIO_GetPortPinState(PORT_A, 4);
                break;
            case PB_PAUSE:
                pb_info[current_button].samples[1] = GPIO_GetPortPinState(PORT_B, 2);
                break;
            case PB_IR_ENABLE:
                pb_info[current_button].samples[1] = GPIO_GetPortPinState(PORT_B, 1);
                break;
            case PB_IP_ENABLE:
                pb_info[current_button].samples[1] = GPIO_GetPortPinState(PORT_A, 3);
                break;
            case PB_CAMERA_TRIGGER:
                pb_info[current_button].samples[1] = GPIO_GetPortPinState(PORT_B, 0);
                break;
            default:
                /* should not be here */
                break;
        }

        /* Update state */
        switch(pb_info[current_button].state)
        {
            case PB_RELEASED:
                if((pb_info[current_button].samples[0] == PB_PRESSED_VOLTAGE) &&
                    (pb_info[current_button].samples[1] == PB_PRESSED_VOLTAGE))
                {
                    pb_info[current_button].state = PB_PRE_PRESSED;
                }
                break;
            case PB_PRE_PRESSED:
                if(pb_info[current_button].samples[1] == PB_PRESSED_VOLTAGE)
                {
                    pb_info[current_button].state = PB_PRESSED;
                }
                break;
            case PB_PRESSED:
                if((pb_info[current_button].samples[0] == PB_RELEASED_VOLTAGE) &&
                    (pb_info[current_button].samples[1] == PB_RELEASED_VOLTAGE))
                {
                    pb_info[current_button].state = PB_PRE_RELEASED;
                }
                break;
            case PB_PRE_RELEASED:
                if(pb_info[current_button].samples[1] == PB_RELEASED_VOLTAGE)
                {
                    pb_info[current_button].state = PB_RELEASED;
                }
                break;
            default:
                /* should not be here */
                break;
        }

    }
}

tPB_State PB_GetState(tPB pb)
{
    tPB_State ret = PB_RELEASED;

    ret = pb_info[pb].state;

    return ret;
}

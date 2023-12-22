# 1 "push_button.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.00/packs/Microchip/PIC18F-K_DFP/1.5.114/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "push_button.c" 2
# 1 "./push_button.h" 1
# 15 "./push_button.h"
typedef enum
{
    PB_UP,
    PB_DOWN,
    PB_FOCUS,
    PB_RESET,
    PB_PAUSE,
    PB_IR_ENABLE,
    PB_IP_ENABLE,
    PB_CAMERA_TRIGGER
}tPB;

typedef enum
{
    PB_RELEASED,
    PB_PRE_PRESSED,
    PB_PRESSED,
    PB_PRE_RELEASED
}tPB_State;

void PB_Init(tPB pb, tPB_State initial_state);
void PB_Update(void);
tPB_State PB_GetState(tPB pb);
# 1 "push_button.c" 2

# 1 "./gpio.h" 1
# 15 "./gpio.h"
typedef enum
{
   PORT_A,
   PORT_B,
   PORT_C
}tPort;

typedef enum
{
    GPIO_OUTPUT = 0,
    GPIO_INPUT = 1
}tPortDirection;

void GPIO_InitPortPin(tPort port, unsigned char pin, tPortDirection direction);
void GPIO_InitPort(tPort port, tPortDirection direction);
void GPIO_Update(void);
void GPIO_SetPortPinState(tPort port, unsigned char pin, unsigned char state);
void GPIO_SetPortState(tPort port, unsigned char state);
unsigned char GPIO_GetPortPinState(tPort port, unsigned char pin);
# 2 "push_button.c" 2
# 11 "push_button.c"
typedef struct
{
    unsigned char samples[(2)];
    tPB_State state;
}tPB_Info;

static tPB_Info pb_info[(8)];

void PB_Init(tPB pb, tPB_State initial_state)
{

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

            break;
    }


    pb_info[pb].state = initial_state;


    switch(initial_state)
    {
        case PB_RELEASED:
        case PB_PRE_RELEASED:
            pb_info[pb].samples[0] = (1);
            pb_info[pb].samples[1] = (1);
            break;

        case PB_PRESSED:
        case PB_PRE_PRESSED:
            pb_info[pb].samples[0] = (0);
            pb_info[pb].samples[1] = (0);
            break;
        default:

            break;
    }
}
void PB_Update(void)
{
    tPB current_button = PB_UP;
    for(current_button = PB_UP; current_button <= PB_CAMERA_TRIGGER; current_button ++)
    {

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

                break;
        }


        switch(pb_info[current_button].state)
        {
            case PB_RELEASED:
                if((pb_info[current_button].samples[0] == (0)) &&
                    (pb_info[current_button].samples[1] == (0)))
                {
                    pb_info[current_button].state = PB_PRE_PRESSED;
                }
                break;
            case PB_PRE_PRESSED:
                if(pb_info[current_button].samples[1] == (0))
                {
                    pb_info[current_button].state = PB_PRESSED;
                }
                break;
            case PB_PRESSED:
                if((pb_info[current_button].samples[0] == (1)) &&
                    (pb_info[current_button].samples[1] == (1)))
                {
                    pb_info[current_button].state = PB_PRE_RELEASED;
                }
                break;
            case PB_PRE_RELEASED:
                if(pb_info[current_button].samples[1] == (1))
                {
                    pb_info[current_button].state = PB_RELEASED;
                }
                break;
            default:

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

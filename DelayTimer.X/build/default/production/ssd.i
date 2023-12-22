# 1 "ssd.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.00/packs/Microchip/PIC18F-K_DFP/1.5.114/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "ssd.c" 2
# 1 "./ssd.h" 1
# 15 "./ssd.h"
typedef enum
{
    SSD_L,
    SSD_R
}tSSD;

typedef enum
{
    SSD_OFF = 0,
    SSD_ON
}tSSD_State;

typedef enum
{
    SSD_0,
    SSD_1,
    SSD_2,
    SSD_3,
    SSD_4,
    SSD_5,
    SSD_6,
    SSD_7,
    SSD_8,
    SSD_9,
    SSD_NULL
}tSSD_Value;

void SSD_Init(tSSD ssd, tSSD_State initial_state, tSSD_Value initial_value);
void SSD_Update(void);
void SSD_SetValue(tSSD ssd, tSSD_Value value);
void SSD_SetState(tSSD ssd, tSSD_State state);
tSSD_Value SSD_GetValue(tSSD ssd);
tSSD_State SSD_GetState(tSSD ssd);
# 1 "ssd.c" 2

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
# 2 "ssd.c" 2




tSSD_Value ssd_values[(2)] = {SSD_NULL};

static unsigned char ssd_data[] =
{
    0b11000000,
    0b11111001,
    0b10100100,
    0b10110000,
    0b10011001,
    0b10010010,
    0b10000010,
    0b11111000,
    0b10000000,
    0b10010000,
    0b00000000
};

void SSD_Init(tSSD ssd, tSSD_State initial_state, tSSD_Value initial_value)
{



    GPIO_InitPort(PORT_C, GPIO_OUTPUT);
    GPIO_SetPortState(PORT_C, ssd_data[SSD_NULL]);



    switch(ssd)
    {
        case SSD_L:
            GPIO_InitPortPin(PORT_A, 6, GPIO_OUTPUT);
            break;
        case SSD_R:
            GPIO_InitPortPin(PORT_A, 7, GPIO_OUTPUT);
            break;
        default:


            break;
    }



    SSD_SetState(ssd, initial_state);



    SSD_SetValue(ssd, initial_value);
}

void SSD_Update(void)
{
    static tSSD current_ssd = SSD_L;


    SSD_SetState(SSD_L, SSD_OFF);
    SSD_SetState(SSD_R, SSD_OFF);



    GPIO_SetPortState(PORT_C, ssd_data[ssd_values[current_ssd]]);



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
            GPIO_SetPortPinState(PORT_A, 6, state);
            break;
        case SSD_R:
            GPIO_SetPortPinState(PORT_A, 7, state);
            break;
        default:


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
            ret = GPIO_GetPortPinState(PORT_A, 6);
            break;
        case SSD_R:
            ret = GPIO_GetPortPinState(PORT_A, 7);
            break;
        default:

            break;
    }
    return ret;
}

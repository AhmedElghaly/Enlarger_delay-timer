#include "gpio.h"
#include <xc.h>

#define SET_REGISTER_PIN(REG, BIT, VAL) ((REG) = (((REG) & (~(1<<BIT))) | ((VAL) << (BIT))))
#define READ_REGISTER_PIN(REG, BIT) ((REG &(1<<BIT)) >> (BIT))


void GPIO_InitPortPin(tPort port, unsigned char pin, tPortDirection direction)
{
    switch(port)
    {
        case PORT_A:
            SET_REGISTER_PIN(TRISA, pin, direction);
            break;
        case PORT_B:
            SET_REGISTER_PIN(TRISB, pin, direction);
            break;
        case PORT_C:
            SET_REGISTER_PIN(TRISC, pin, direction);
            break;
        default:
            /* Should not be here */
            break;
    }
}

void GPIO_InitPort(tPort port, tPortDirection direction)
{
    unsigned char i = 0;

    for(i = 0; i < 8; i++)
    {
        GPIO_InitPortPin(port, i, direction);
    }
}


void GPIO_Update(void)
{
    /* Should do nothing */
}


void GPIO_SetPortPinState(tPort port, unsigned char pin, unsigned char state)
{
    switch(port)
    {
        case PORT_A:
            SET_REGISTER_PIN(PORTA, pin, state);
            break;
        case PORT_B:
            SET_REGISTER_PIN(PORTB, pin, state);
            break;
        case PORT_C:
            SET_REGISTER_PIN(PORTC, pin, state);
            break;
        default:
            /* Should not be here */
            break;
    }
}

void GPIO_SetPortState(tPort port, unsigned char state)
{
    unsigned char i = 0;

    for(i = 0; i < 8; i++)
    {
        GPIO_SetPortPinState(port, i, READ_REGISTER_PIN(state, i));
    }
}

unsigned char GPIO_GetPortPinState(tPort port, unsigned char pin)
{
    unsigned char ret = 0;

    switch(port)
    {
        case PORT_A:
            ret =  READ_REGISTER_PIN(PORTA, pin);
            break;
        case PORT_B:
            ret =  READ_REGISTER_PIN(PORTB, pin);
            break;
        case PORT_C:
            ret =  READ_REGISTER_PIN(PORTC, pin);
            break;
        default:
            /* Should not be here */
            break;
    }

    return ret;
}


/* 
 * File:   gpio.h
 * Author: Ahmed Saad
 *
 * Created on December 14, 2023, 1:09 PM
 */

#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif

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



#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */


/* 
 * File:   led.h
 * Author: Ahmed Saad
 *
 * Created on December 14, 2023, 4:52 PM
 */

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef __LED_H__
#define __LED_H__

typedef enum
{
    LED_ACTIVE
}tLED;

typedef enum
{
	LED_OFF = 0,
	LED_ON = 1
}tLED_State;

void LED_Init(tLED led, tLED_State initial_state);
void LED_Update(void);  //====> void - void to work as a task or ISR
void LED_SetState(tLED led, tLED_State state);
tLED_State LED_GetState(tLED led);

#ifdef	__cplusplus
}
#endif

#endif // __LED_H
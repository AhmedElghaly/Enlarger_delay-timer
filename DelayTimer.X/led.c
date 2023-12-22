#include "led.h"
#include "gpio.h"
#include <xc.h> 

#define LED_TOGGLE_MS (1000)

static void LED_Toggle(tLED led);

void LED_Init(tLED led,tLED_State initial_state)
{
    /* Initialize led pin as an output*/
    switch(led)
    {
    case LED_ACTIVE:
        //TRISA0 = 0;
        GPIO_InitPortPin(PORT_B, 5, GPIO_OUTPUT);
        break;
    default:
        /* Should not be here */
        break;
    }
    /* Set led state */
    LED_SetState(led, initial_state);
}

void LED_Update(void)
{
    /* Toggle initialized led with period*/
    //LED_Toggle(LED_1);  
}

void LED_SetState(tLED led, tLED_State state)
{
    switch(led)
    {
    case LED_ACTIVE:
        GPIO_SetPortPinState(PORT_B, 5, state);
        break;
    default:
        /* Should not be here */
        break;
    }
}

tLED_State LED_GetState(tLED led)
{
    tLED_State ret = LED_OFF;

    switch(led)
    {
    case LED_ACTIVE:
        ret = GPIO_GetPortPinState(PORT_B, 5);
        break;
    default:
        /* Should not be here */
        break;
    }

    return ret;
}

static void LED_Toggle(tLED led)
{
   if(LED_GetState(led) == LED_ON)
   {
       LED_SetState(led, LED_OFF);
   }else
   {
       LED_SetState(led, LED_ON);
   }
}


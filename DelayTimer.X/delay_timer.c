#include "delay_timer.h"
#include "ssd.h"
#include "push_button.h"
#include "gpio.h"
#include "led.h"
#include "mcc_generated_files/mcc.h"

unsigned char count_flag = 0;
static unsigned char counter;
static unsigned char counter_index;
static unsigned char pause;
static unsigned char focus;

void DELAY_TIMER_Init(unsigned int initial_count)
{
    // Initializing the min timer setter pin
    GPIO_InitPortPin(PORT_B, 7, GPIO_OUTPUT);
    counter = initial_count;
    counter_index = 0;
    pause = 1;
    focus = 1;
}

void DELAY_TIMER_Update(void)
{
    /* Get buttons state */
    // increment counter if UP is pre pressed
    if((PB_GetState(PB_UP) == PB_PRE_PRESSED) && (pause != 0) && (focus !=  0))
    {
        if(counter < 99)
        {
            counter++;
        }
    }
    // decrement counter if DOWN is pre pressed
    else if((PB_GetState(PB_DOWN) == PB_PRE_PRESSED) && (pause != 0) && (focus !=  0))
    {
        if(counter > 1)
        {
            counter--;
        }
    }
    // reset counter if Reset is pre pressed
    else if((PB_GetState(PB_RESET) == PB_PRE_PRESSED) && (focus !=  0))
    {
        counter = 0;
        pause = 1;
    }
    // pause/continue  counter if pause is pre pressed
    else if((PB_GetState(PB_PAUSE) == PB_PRE_PRESSED) && (focus !=  0))
    {
        if(pause == 1)
        {
            pause = 0;   
        }
        else 
        {
            pause = 1;
        }
    }
    // focus counter if focus is pre pressed
    else if(PB_GetState(PB_FOCUS) == PB_PRE_PRESSED)
    {
        counter = 0;
        if(focus == 1)
        {
            focus = 0;   
        }
        else 
        {
            focus = 1;
        }
    }
    if(((PB_GetState(PB_IR_ENABLE) == PB_PRE_PRESSED) || 
        (PB_GetState(PB_IP_ENABLE) == PB_PRE_PRESSED) || 
        (PB_GetState(PB_CAMERA_TRIGGER) == PB_PRE_PRESSED)) && (focus !=  0))
    {
        //counter_index = counter;
        count_flag = 1;
    }
    
    /*Set SSD values */
    SSD_SetValue(SSD_L, counter / 10);
    SSD_SetValue(SSD_R, counter % 10);

}

void DELAY_TIMER_Count(void)
{
    
    counter_index ++;
    if(counter_index == counter)
    {
        LED_SetState(LED_ACTIVE, LED_ON); // LED OFF
        count_flag = 0;
        counter_index = 0;
    }
    else
    {
        LED_SetState(LED_ACTIVE, LED_OFF); // LED ON
        count_flag = 1;  
    }
    /*Set SSD values */
    SSD_SetValue(SSD_L, counter_index / 10);
    SSD_SetValue(SSD_R, counter_index % 10);
}

void DELAY_TIMER_SetMainTimer(tMT_State state)
{
    GPIO_SetPortPinState(PORT_B, 7, state);
}


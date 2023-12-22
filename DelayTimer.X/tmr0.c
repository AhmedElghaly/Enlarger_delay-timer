#include <xc.h>
#include "ssd.h"
#include "tmr0.h"
#include "push_button.h"
#include "delay_timer.h"
#include "led.h"

#define TMR0_TICK_MS (5)

#define GLOBAL_INTERRUPT_ENABLE(x)  (GIE = x)


/* (PSA = 1 => assigned to WDT), (PSA = 0 => assigned to TMR) */
#define TMR0_SET_PRE_SCALER(x) PSA = 0;\
                                    T0PS0 = (x&0x1);\
                                    T0PS1 = (x&0x2)>>1;\
                                    T0PS2 = (x&0x4)>>2;

#define TMR0_CHECK_FLAG() (TMR0IF)
#define TMR0_CLEAR_FLAG() (TMR0IF = 0)

#define TMR0_SELECT_CLOCK_SOURCE(y) (T0CS = y)
#define TMR0_SELECT_EDGE(z) (T0SE = z)
#define TMR0_READ_COUNTER() (TMR0)
#define TMR0_SET_TIME_MS(t) (TMR0 = 256 - 8*t)
#define TMR0_SET_INT_STATE(x) (TMR0IE = x)
#define TMR0_SET_STATE(x) (T0CS = x)

extern unsigned char count_flag;

void TMR0_Init(void)
{
    TMR0_SET_STATE(1);             // TIMER0 IS OFF
    TMR0_SET_PRE_SCALER(7)         // 7 EQUAL 256
}

void TMR0_Start(void)
{
    TMR0_CLEAR_FLAG();
    TMR0_SET_TIME_MS(TMR0_TICK_MS);
    TMR0_SET_INT_STATE(1);
    GLOBAL_INTERRUPT_ENABLE(1); // Enabling global interrupt
    TMR0_SELECT_CLOCK_SOURCE(1); // INTERNAL OSCILLATOR
    TMR0_SET_STATE(0);             // TIMER0 IS ON
}

void __interrupt() TMR0_Update() 
{
    if (TMR0IF) {
    static unsigned char counter1 = 0;
    static unsigned int counter2 = 0;
    counter1 = counter1 + TMR0_TICK_MS;
    counter2 = counter2 + TMR0_TICK_MS;

    /* Tasks */
    if(counter1 == 20)
    {
        PB_Update();            // 20 ms
        DELAY_TIMER_Update();   // 20 ms
        
        if (count_flag == 0)
        {
            LED_SetState(LED_ACTIVE, LED_ON);
            SSD_Update();       // 20 ms
            DELAY_TIMER_SetMainTimer(MT_OFF);
        }
        counter1 = 0;
    }
    
    if(counter2 == 100)
    {
        if (count_flag == 1)
        {
            LED_SetState(LED_ACTIVE, LED_OFF);
            DELAY_TIMER_Count();
            SSD_Update();       // 20 ms
            DELAY_TIMER_SetMainTimer(MT_ON);
        }
        counter2 = 0;
    }

    TMR0_CLEAR_FLAG();
    TMR0_SET_TIME_MS(TMR0_TICK_MS);

    return;
    }
}



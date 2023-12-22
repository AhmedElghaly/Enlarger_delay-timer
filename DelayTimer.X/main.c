#include <xc.h>
#include "ssd.h"
#include "delay_timer.h"
#include "push_button.h"
#include "tmr0.h"
#include "led.h"
#include "mcc_generated_files/mcc.h"

void main() 
{
    //System_Initialize
    SYSTEM_Initialize();
    
    // Inputs initialize
    PB_Init(PB_UP, PB_RELEASED);
    PB_Init(PB_DOWN, PB_RELEASED);
    PB_Init(PB_FOCUS, PB_RELEASED);
    PB_Init(PB_RESET, PB_RELEASED);
    PB_Init(PB_PAUSE, PB_RELEASED);
    PB_Init(PB_IR_ENABLE, PB_RELEASED);
    PB_Init(PB_IP_ENABLE, PB_RELEASED);
    PB_Init(PB_CAMERA_TRIGGER, PB_RELEASED);
    
	//Main program initialize
    DELAY_TIMER_Init(1);
    
	// Outputs initialize 
    SSD_Init(SSD_L, SSD_OFF, SSD_NULL);
    SSD_Init(SSD_R, SSD_OFF, SSD_NULL);
    LED_Init(LED_ACTIVE, LED_OFF);
    
	//OS initialize
    TMR0_Init();
    TMR0_Start();
    
    while (1) 
    {
        
    }
}

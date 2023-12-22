/* 
 * File:   count.h
 * Author: Ahmed Saad
 *
 * Created on December 14, 2023, 4:51 PM
 */

#ifndef DELAY_TIMER_H
#define	DELAY_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
	MT_OFF = 0, //main timer off
	MT_ON = 1   //main timer on
}tMT_State;
    
void DELAY_TIMER_Init(unsigned int initial_count);
void DELAY_TIMER_Update(void);
void DELAY_TIMER_Count(void);
void DELAY_TIMER_SetMainTimer(tMT_State state);


#ifdef	__cplusplus
}
#endif

#endif	/* COUNT_H */


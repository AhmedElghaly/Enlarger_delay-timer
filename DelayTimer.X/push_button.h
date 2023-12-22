/* 
 * File:   push_button.h
 * Author: Ahmed Saad
 *
 * Created on December 14, 2023, 4:52 PM
 */

#ifndef PUSH_BUTTON_H
#define	PUSH_BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif

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


#ifdef	__cplusplus
}
#endif

#endif	/* PUSH_BUTTON_H */


/* 
 * File:   ssd.h
 * Author: Ahmed Saad
 *
 * Created on December 19, 2023, 12:31 AM
 */

#ifndef SSD_H
#define	SSD_H

#ifdef	__cplusplus
extern "C" {
#endif  
 
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
    SSD_NULL //will show nothing
}tSSD_Value;

void SSD_Init(tSSD ssd, tSSD_State initial_state, tSSD_Value initial_value);
void SSD_Update(void);
void SSD_SetValue(tSSD ssd, tSSD_Value value);
void SSD_SetState(tSSD ssd, tSSD_State state);
tSSD_Value SSD_GetValue(tSSD ssd);
tSSD_State SSD_GetState(tSSD ssd);

    
#ifdef	__cplusplus
}
#endif

#endif	/* SSD_H */


/* 
 * File:   tmr0.h
 * Author: Ahmed Saad
 *
 * Created on December 19, 2023, 2:19 PM
 */

#ifndef TMR0_H
#define	TMR0_H

#ifdef	__cplusplus
extern "C" {
#endif


void TMR0_Init(void);
void __interrupt() TMR0_Update();
void TMR0_Start(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TMR0_H */


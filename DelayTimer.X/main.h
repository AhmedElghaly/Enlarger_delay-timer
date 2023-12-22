/* 
 * File:   main.h
 * Author: Ahmed
 *
 * Created on December 19, 2023, 12:30 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

// Configuration settings
#pragma config FOSC = INTIO67   // Internal oscillator block
//#pragma config PWRT = OFF       // Power-up timer disabled
//#pragma config MCLRE = ON       // MCLR pin enabled; RE3 input pin disabled
#pragma config PBADEN = OFF     // PORTB<4:0> pins configured as digital I/O on reset
#pragma config LVP = OFF        // Single-Supply ICSP disabled
#define _XTAL_FREQ 8000000


    
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */


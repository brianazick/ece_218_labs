/*
 * File: main_t2_blink.c
 * Author: B. Zick
 * Date: 2019-01-28
 * Purpose: Blink an LED using on board timer
 * Modified:
 */
/*********** COMPILER DIRECTIVES *********/

// #include for textbook library header files
#include "pic24_all.h"

// #defines for handy constants
#define LED (_LATA0)  // LED on microstick, RA0 (pin 2)


/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/
void configTimer2(void) {
    T2CON = 0x0030; //TMR2 off, default idle mode, gate off, prescale 1:256, 32-bit mode off, internal clock
    PR2 = 39062;
    _T2IF = 0; //set the initial state to off
    T2CONbits.TON = 1; //Turn the timer on
}

/********** MAIN PROGRAM ********************************/
int main ( void )  //main function that....
{
/* Define local variables */


/* Call configuration routines */
	  configClock();  //Sets the clock to 40MHz using FRC and PLL
    configTimer2(); //Sets the timer to desired settings

/* Initialize ports and other one-time code */
    D1PCFGL = 0xFFFF; //config all ports to be digital
    TRISA = 0x0000; //config all ports to be outputs
    LATA = 0x0000; //config all ports to init to 0
    LED = 1; //turn the LED on by default
    
/* Main program loop */
	while (1) {
		while(!_T2IF){}; //wait for the timer to go off
      LED = !LED; //cycle the LED's power state when it gets to here
      _T2IF = 0; //reset the interrupt register
		}
}

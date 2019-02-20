/* 
 * File: main_dc_motor.c
 * Author: B. Zick
 * Date: 2019-02-06
 * Purpose: Run a DC Motor with a PIC24
 * Modified:
 */
/*********** COMPILER DIRECTIVES *********/

// #include for textbook library header files
#include "pic24_all.h"

// #defines for handy constants 
#define A1 (_RB1) // RB1 (pin 5) is connected to 1A on the motor driver
#define A2 (_RB2) // RB2 (pin 6) is connected to 2A on the motor driver
#define EN_12 (_RB12) // RB12 (pin 23) is connected to EN_12 on the motor driver


/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/


    
/********** MAIN PROGRAM ********************************/
int main ( void )  //main function that....
{ 
/* Define local variables */


/* Call configuration routines */
	configClock();  //Sets the clock to 40MHz using FRC and PLL


/* Initialize ports and other one-time code */
    CONFIG_RB1_AS_DIG_OUTPUT();
    CONFIG_RB2_AS_DIG_OUTPUT();
    CONFIG_RB12_AS_DIG_OUTPUT();
    
/* Main program loop */
	while (1) {	
		//run the motor in direction one for 5 seconds
        _LATB1 = 1;
        _LATB2 = 0;
        _LATB12 = 1;
        DELAY_MS(5000);
        
        //turn off the motor for 1 second
        _LATB12 = 0;
        DELAY_MS(1000);
        
        //run the motor in direction two for 5 seconds
        _LATB1 = 0;
        _LATB2 = 1;
        _LATB12 = 1;
        DELAY_MS(5000);
        
        //turn off the motor for 1 second
        _LATB12 = 0;
        DELAY_MS(1000);
		}
}
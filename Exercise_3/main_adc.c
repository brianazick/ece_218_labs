/*
 * File:
 * Author:
 * Date:
 * Purpose:
 * Modified:
 */
/*********** COMPILER DIRECTIVES *********/

// #include for textbook library header files
#include "pic24_all.h"

// #defines for handy constants
#define LED (_LATA0)  // LED on microstick, RA0 (pin 2)


/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/



/********** MAIN PROGRAM ********************************/
int main ( void )  //main function that....
{
/* Define local variables */
    uint16_t u16_var;
    float voltage;

/* Call configuration routines */
	configClock();  //Sets the clock to 40MHz using FRC and PLL
    CONFIG_RA1_AS_ANALOG(); //sets RA1 (pin 3) to be analog
    configADC1_ManualCH0(RA1_AN, 31, 0); //set up ADC

/* Initialize ports and other one-time code */



/* Main program loop */
	while (1) {
		u16_var = convertADC1();
        voltage = ((float)u16_var/(float)1023)*3.3;
        DELAY_MS(100);
		}
}

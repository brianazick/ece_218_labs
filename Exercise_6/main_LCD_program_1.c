/* 
 * File: main_LCD.c
 * Author: B. Zick
 * Date: 2019-01-30
 * Purpose: Work with the SparkFun LCD
 * Modified:
 */
/*********** COMPILER DIRECTIVES *********/

// #include for textbook library header files
#include "pic24_all.h"
#include "lcd4bit_lib.h"

// #defines for handy constants 


/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/


    
/********** MAIN PROGRAM ********************************/
int main ( void )  //main function that....
{ 
/* Define local variables */


/* Call configuration routines */
    configClock();  //Sets the clock to 40MHz using FRC and PLL
    configControlLCD(); //Configure the RS, RW, and E control lines and outputs and initialize them low

/* Initialize ports and other one-time code */
    initLCD(); //Execute the initialization sequence for the LCD display
    
    outStringLCD("Hello there!");
    writeLCD(0xC0, 0, 1, 1);
    outStringLCD("Enjoy LCD Demo!");
    
/* Main program loop */
	while (1) {	
		
		}
}
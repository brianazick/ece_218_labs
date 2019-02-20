
/* File: main_blink.c
 * Author: C. Traver
 * Date: Dec 7 2018
 * Purpose: Program to blink a LED with the Microstick II board
 * The LED will be attached to Pin 3
 */

/*********** COMPILER DIRECTIVES *********/
#include "pic24_all.h"  //Textbook library header file

#define LED1 (_LATA1)   // _LATA1 is the port write register bit for RA1 (pin 3).

/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/
// No variables or functions needed for blinking

/********** MAIN PROGRAM ********************************/
int main(void) {  //main function that blinks LED
  configClock();  //Sets the clock to 40MHz using FRC and PLL
  /* Initialize ports */
  AD1PCFGL = 0x0002; 	//set RA1 (pin3) to digital (others analog)
  _TRISA1 = 0;  //set RA1 (pin 3) as output
  LED1 = 0;   
  while (1) {  
    // Delay long enough to see LED blink.
    DELAY_MS(250);

    LED1 = !LED1;
  } // end while (1)
}

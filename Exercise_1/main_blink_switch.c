
/* File: main_blink_switch.c
 * Author: C. Traver and B. Zick
 * Date: 2019-01-09
 * Purpose: Program to blink a LED with the Microstick II board when a button is pressed
 * The LED will be attached to Pin 3
 * The button will be attached to Pin 6
 */

/*********** COMPILER DIRECTIVES *********/
#include "pic24_all.h"  //Textbook library header file

#define LED1 (_LATA1)   // _LATA1 is the port write register bit for RA1 (pin 3).
#define sw (_RB2)       // _RBS is the port write register bit for RB2 (pin 6).

/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/
// No variables or functions needed for blinking or using a switch

/********** MAIN PROGRAM ********************************/
int main(void) {  //main function that blinks LED
  configClock();  //Sets the clock to 40MHz using FRC and PLL
  /* Initialize ports */
  AD1PCFGL = 0x0012; 	//set RA1 (pin3) and AN4 (pin 6) to digital (others analog)
  _TRISA1 = 0;  //set RA1 (pin 3) as output
  _TRISB2 = 1; //set RB2 (pin 6) as input
  LED1 = 0;  //Turns the LED off
  while (1) {  //Loops indefinitely
    // Delay long enough to see LED blink.
    DELAY_MS(250);
    
    if (sw == 0){
        LED1 = !LED1; //Changes the state of the LED
    } else {
        LED1 = LED1; //Cause state to remain the same
    }
        
  } // end while (1)
}

/* 
 * File: main_serial.c
 * Author: B. Zick
 * Date: 2019-01-16
 * Purpose: Utilize serial communication for basic I/O
 * Modified:
 */
/*********** COMPILER DIRECTIVES *********/

// #include for textbook library header files
#include "pic24_all.h"


/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/


    
/********** MAIN PROGRAM ********************************/
int main ( void )  //main function that....
{ 
/* Define local variables */
    uint8_t key_char; //declare variable for reading user input

/* Call configuration routines */
	configClock();  //Sets the clock to 40MHz using FRC and PLL
    configUART1(230400); //parameter is the baudrate for serial communication

/* Initialize ports and other one-time code */
    uint8_t clear_terminal[] = "\e[1;1H\e[2J"; //String to clear terminal
    outString(clear_terminal); //Clear the terminal
    uint8_t u8_str[] = "Serial communication has been established.\r"; //Initialize welcome message
    outString(u8_str); //Print welcome message

    
/* Main program loop */
	while (1) {	
		key_char = inChar(); //Read in char from user
        outChar(key_char); //Print out char to user
		}
}
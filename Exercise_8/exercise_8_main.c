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
#define NUM_ROWS 4
#define NUM_COLS 3

/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/
volatile char keypad_table[NUM_ROWS][NUM_COLS] = {{'1','2','3'},
                                                  {'4','5','6'},
                                                  {'7','8','9'},
                                                  {'*','0','#'}};
uint16_t cur_column;

void _ISR _CNInterrupt(void){
    uint16_t pressed_column = cur_column;
    uint16_t pressed_row;
    
    DELAY_MS(25);
    
    if (_RB15 == 0) {
        pressed_row = 0;
        while(_RB15 == 0);
        outChar(keypad_table[pressed_row][pressed_column]);
    } else if (_RB12  == 0) {
        pressed_row = 1;
        while(_RB12  == 0);
        outChar(keypad_table[pressed_row][pressed_column]);
    } else if (_RB13  == 0) {
        pressed_row = 2;
        while(_RB13  == 0);
        outChar(keypad_table[pressed_row][pressed_column]);
    } else if (_RB14  == 0) {
        pressed_row = 3;
        while(_RB14  == 0);
        outChar(keypad_table[pressed_row][pressed_column]);
    }
      
    DELAY_MS(25);
    
    _CNIF = 0; //reset the interrupt register
}
    
/********** MAIN PROGRAM ********************************/
int main ( void )  //main function that....
{ 
/* Define local variables */


/* Call configuration routines */
	configClock();  //Sets the clock to 40MHz using FRC and PLL
    configUART1(230400); //Configure UART1 for 230400 baud


/* Initialize ports and other one-time code */
    CONFIG_RB3_AS_DIG_OUTPUT(); //orange wire
    CONFIG_RB4_AS_DIG_OUTPUT(); //brown wire
    CONFIG_RB5_AS_DIG_OUTPUT(); //white wire
    
    CONFIG_RB12_AS_DIG_INPUT(); //black wire
    CONFIG_RB13_AS_DIG_INPUT(); //red wire
    CONFIG_RB14_AS_DIG_INPUT(); //blue wire
    CONFIG_RB15_AS_DIG_INPUT(); //green wire
    
    ENABLE_RB12_PULLUP();
    ENABLE_RB13_PULLUP();
    ENABLE_RB14_PULLUP();
    ENABLE_RB15_PULLUP();
    
    ENABLE_RB12_CN_INTERRUPT();
    ENABLE_RB13_CN_INTERRUPT();
    ENABLE_RB14_CN_INTERRUPT();
    ENABLE_RB15_CN_INTERRUPT();    
    
    
    
    uint8_t clear_terminal[] = "\e[1;1H\e[2J"; //String to clear terminal
    outString(clear_terminal); //Clear the terminal
    uint8_t u8_str[] = "Serial communication has been established.\n\r"; //Initialize welcome message
    outString(u8_str); //Print welcome message
    
    _CNIE = 1; // enable the interrupt
    
/* Main program loop */
	while (1) {
        cur_column = 2;
		_LATB3 = 0;
        _LATB4 = 1;
        _LATB5 = 1;
        
        DELAY_MS(10);
        
        cur_column = 0;
        _LATB3 = 1;
        _LATB4 = 0;
        _LATB5 = 1;
        
        DELAY_MS(10);
        
        cur_column = 1;
        _LATB3 = 1;
        _LATB4 = 1;
        _LATB5 = 0;
	
        DELAY_MS(10);
    }
}
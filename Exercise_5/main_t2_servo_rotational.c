/*
 * File: main_t2_servo.c
 * Author: B. Zick
 * Date: 2019-01-28
 * Purpose: Move a servo motor using on board timer
 * Modified:
 */
/*********** COMPILER DIRECTIVES *********/

// #include for textbook library header files
#include "pic24_all.h"

// #defines for handy constants
#define LED (_LATA0)  // LED on microstick, RA0 (pin 2)
#define PWM_PERIOD 3125 //Define previously calculated period in ticks
#define p_min 117 //Define previous calculated minimum pulse width in ticks
#define p_max 351 //Define previous calculated maximum pulse width in ticks



/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/
volatile uint16_t pulse_width;

void configOC1(void) {
    T2CONbits.TON = 0; //Turn the timer off
    CONFIG_OC1_TO_RP(RB1_RP); //Map the OC1 output to the remappable pin RP1
    OC1RS = 0x0000; //clear the register
    OC1R = 0x0000; //clear the register
    OC1CONbits.OCM = 0x6; //PWM mode on OC1, fault pin disabled
    OC1CONbits.OCTSEL = 0; //use timer2 as the clock source
}

void configTimer2(void) {
    T2CON = 0x0030; //TMR2 off, default idle mode, gate off, prescale 1:256, 32-bit mode off, internal clock
    PR2 = PWM_PERIOD; //delay = PWM_PERIOD
    TMR2 = 0x0000;
    _T2IF = 0; //set the initial state to off
}

void _ISR _T2Interrupt(void){
    OC1RS = pulse_width; //update the OC1RS register
    _T2IF = 0; //set the flag bit to 0
}



/********** MAIN PROGRAM ********************************/
int main ( void )  //main function that....
{
/* Define local variables */


/* Call configuration routines */
	configClock();  //Sets the clock to 40MHz using FRC and PLL
    configTimer2(); //Sets the timer to desired settings
    configOC1(); //Config the output compare

/* Initialize ports and other one-time code */
    _T2IE = 1; //set timer interrupt enable
    _T2IF = 0; //clear the timer flag
    T2CONbits.TON = 1; //Turn the timer on
    pulse_width = 156;

/* Main program loop */
	while (1) {

	}
}

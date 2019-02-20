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
#define EN_12 (_RB12) // RB12 (pin 23) is connected to EN_12 on the motor driver
#define PWM_PERIOD 510 //Define previously calculated period in ticks
#define p_min 255 //Define previous calculated minimum pulse width in ticks
#define p_max 510 //Define previous calculated maximum pulse width in ticks

volatile uint16_t A1;
volatile uint16_t A2;

/*********** GLOBAL VARIABLE AND FUNCTION DEFINITIONS *******/
void configOC1(void) {
    T2CONbits.TON = 0; //Turn the timer off
    CONFIG_OC1_TO_RP(RB1_RP); //Map the OC1 output to the remappable pin RP1
    OC1RS = 0x0000; //clear the register
    OC1R = 0x0000; //clear the register
    OC1CONbits.OCM = 0x6; //PWM mode on OC1, fault pin disabled
    OC1CONbits.OCTSEL = 0; //use timer2 as the clock source
}

void configOC2(void) {
    T2CONbits.TON = 0; //Turn the timer off
    CONFIG_OC2_TO_RP(RB2_RP); //Map the OC2 output to the remappable pin RP2
    OC2RS = 0x0000; //clear the register
    OC2R = 0x0000; //clear the register
    OC2CONbits.OCM = 0x6; //PWM mode on OC2, fault pin disabled
    OC2CONbits.OCTSEL = 0; //use timer2 as the clock source
}

void configTimer2(void) {
    T2CON = 0x0010; //TMR2 off, default idle mode, gate off, prescale 1:8, 32-bit mode off, internal clock
    PR2 = PWM_PERIOD; //delay = PWM_PERIOD
    TMR2 = 0x0000; //clear the timer
    _T2IF = 0; //set the initial state to off
}

void _ISR _T2Interrupt(void){
    OC1RS = A1; //update the OC1RS register
        
    OC2RS = A2; //update the OC2RS register

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
    configOC2(); //Config the output compare

/* Initialize ports and other one-time code */
    CONFIG_RB12_AS_DIG_OUTPUT();
    
    A1 = 0;
    A2 = 0;
    
    _T2IE = 1; //set timer interrupt enable
    _T2IF = 0; //clear the timer flag
    T2CONbits.TON = 1; //Turn the timer on
    
    int i;
    
/* Main program loop */
	while (1) {	
		//initialize the motor to minimum speed in direction one
        A1 = p_min;
        A2 = 0;
        _LATB12 = 1;
        
        //ramp up the speed in direction one
        for(i = p_min; i < p_max; i += 10){
            A1 = i;
            DELAY_MS(60);
        }        
        
        //run the motor at top speed for one second
        DELAY_MS(1000);
        
        //ramp down the speed in direction one
        for(i = p_max; i < p_min; i -= 10){
            A1 = i;
            DELAY_MS(60);
        } 
        
        //run the motor at minimum speed for one second
        DELAY_MS(1000);
        
        //turn the motor off for one second
        _LATB12 = 0;
        DELAY_MS(1000);
        
        //initialize the motor to minimum speed in direction one
        A1 = 0;
        A2 = p_min;
        _LATB12 = 1;
        
        //ramp up the speed in direction one
        for(i = p_min; i < p_max; i += 10){
            A2 = i;
            DELAY_MS(60);
        }        
        
        //run the motor at top speed for one second
        DELAY_MS(1000);
        
        //ramp down the speed in direction one
        for(i = p_max; i < p_min; i -= 10){
            A2 = i;
            DELAY_MS(60);
        } 
        
        //run the motor at minimum speed for one second
        DELAY_MS(1000);
        
        //turn the motor off for one second
        _LATB12 = 0;
        DELAY_MS(1000);
	}
}
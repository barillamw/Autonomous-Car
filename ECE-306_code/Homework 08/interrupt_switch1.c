#include  "msp430.h"
#include  "macros.h"



extern unsigned volatile int debounce1;
extern unsigned volatile int debounce1_count;
extern unsigned int switchONE;
unsigned int oneTime1;
unsigned int loFreq;

//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function contains the Interupt Service Routines for the 
//      SW1.
//
//------------------------------------------------------------------------------
#pragma vector = PORT4_VECTOR
__interrupt void switch1_interrupt(void){

  //Switch 1
  if (P4IFG & SW1) {
    switchONE = HIGH;                   //Set a varibale to identify the switch has been pressed.
    loFreq = HIGH;
    debounce1 = HIGH;                   //Set a variable to identify the switch si being debounced.
    //debounce1_count = RESET_STATE;      //Reset the count required of the debounce
    P4IFG &= ~SW1;                    //Clear all Sw1 inerrupt flags
    P4IE &= ~SW1;                     //Sw1 interrupt disabled
    TB0CCTL1 |= CCIE;                   //CCR1 enable interrupt
    //P6OUT &= ~LCD_BACKLITE;           //LCD_BACKLITE off to indicate bootISR working
  }
  //use a Timer Value to control the debounce
}

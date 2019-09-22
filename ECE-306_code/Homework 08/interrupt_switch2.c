#include  "msp430.h"
#include  "macros.h"


extern unsigned volatile int debounce2;
extern unsigned volatile int debounce2_count;
extern unsigned int switchTWO;
unsigned int oneTime2;
unsigned int hiFreq;

//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initalizes the Interrupt Service Routines 
//      for SW2 
//
//------------------------------------------------------------------------------

#pragma vector = PORT2_VECTOR
__interrupt void switch2_interrupt(void){

  //Switch 2
  if (P2IFG & SW2) {
    switchTWO = HIGH;                   //Set a varibale to identify the switch has been pressed.
    hiFreq = HIGH;
    debounce2 = HIGH;                   //Set a variable to identify the switch si being debounced.
    //debounce1_count = RESET_STATE;      //Reset the count required of the debounce
    P2IFG &= ~SW2;                    //Clear all Sw1 inerrupt flags
    P2IE &= ~SW2;                     //Sw1 interrupt disabled
    TB0CCTL1 |= CCIE;                   //CCR1 enable interrupt
    //P6OUT |= LCD_BACKLITE;           //LCD_BACKLITE off to indicate bootISR working
  }
  //use a Timer Value to control the debounce
}
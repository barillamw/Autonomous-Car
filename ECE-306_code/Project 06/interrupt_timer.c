//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This file contains the interrupt functions for the B0-0  
//     and B0-1,2, overflow timers
//
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "macros.h"



volatile unsigned int Time_Sequence;
volatile char one_time;
unsigned int blink_count;

volatile unsigned int debounce1;
volatile unsigned int debounce1_count;
volatile unsigned int debounce2;
volatile unsigned int debounce2_count;

extern volatile unsigned char update_display;
unsigned int update_count;

volatile unsigned int newSecond;
unsigned int second_count;



#pragma vector = TIMER0_B0_VECTOR // Timer B0 – 0 Capture compare
__interrupt void Timer0_B0_ISR(void){
//--------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//--------------------------------------------------------------------
  /*// LCD Backlight
  if(blink_count++ > COUNT_TEN){
    blink_count = RESET_STATE; // Reset for next count
    P6OUT ^= LCD_BACKLITE; // Flip State of LCD_BACKLITE
  }*/
  
  
  if(update_count++ >COUNT_FOUR){
        update_count = LOW;
        update_display = HIGH;
  }
  
  if (second_count++ > 20){
    second_count = LOW;
    newSecond = HIGH;
  }
    
  // Time Sequence
  one_time = HIGH;
  if(Time_Sequence++ > 250){
    Time_Sequence = RESET_STATE;
  }

  
 
  
  //CHANGE_PROBE;
  TB0CCR0 += TB0CCR0_INTERVAL; // Add interval Offset to TBCCR0
//--------------------------------------------------------------------
}

#pragma vector = TIMER0_B1_VECTOR // Timer B0 – 1 Capture compare
__interrupt void Timer0_B1_ISR(void){
//--------------------------------------------------------------------
// TimerB0 1 Interrupt handler
//--------------------------------------------------------------------
  switch(__even_in_range(TB0IV,S14)){
  case S0: break;                //No Interrupt
  case S2:                       //CCR1 
    if (debounce1){
      if(debounce1_count++ > COUNT_TEN){
        debounce1 = LOW;
        debounce1_count = LOW;
        P4IFG &= ~SW1;                //Clear all Sw1 inerrupt flags
        P4IE |= SW1;                  //Sw1 interrupt enabled
        TB0CCTL1 &= ~CCIE;            // CCR1 disable interrupt
      }
    }
    if(debounce2){
      if(debounce2_count++ > COUNT_TEN){
        debounce2 = LOW;
        debounce2_count = LOW;
        P2IFG &= ~SW2;                //Clear all Sw1 inerrupt flags
        P2IE |= SW2;                  //Sw1 interrupt enabled
        TB0CCTL1 &= ~CCIE;            // CCR1 disable interrupt
      }
    }
    TB0CCTL1 &= ~CCIFG;               // CCR1 clear interrupt flag
    TB0CCR1 += TB0CCR1_INTERVAL;      // Add interval Offset to TBCCR1
    break;
  case S4: 
    TB0CCTL2 &= ~CCIFG; 
    TB0CCR2 += TB0CCR2_INTERVAL;
  case S14: break;
  default: break;
  }
//--------------------------------------------------------------------
}

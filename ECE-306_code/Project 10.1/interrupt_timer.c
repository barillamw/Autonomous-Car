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
#include  "functions.h"



volatile unsigned int Time_Sequence;
volatile char one_time;
unsigned int blink_count;

volatile unsigned int debounce1;
volatile unsigned int debounce1_count;
volatile unsigned int debounce2;
volatile unsigned int debounce2_count;

extern volatile unsigned char update_display;
unsigned int update_count;

volatile unsigned int newDrive;
unsigned int newDrive_count;
unsigned int newSecond;
unsigned int second_count;
unsigned int time_count;
unsigned int time_count_en;
unsigned int wait_count;
extern unsigned int endWait;
unsigned int sample;
unsigned int waitTime;
unsigned int scroll;
unsigned int send;
unsigned int reset;
extern unsigned int startTimer;
extern char driveState;
extern unsigned int distance;
unsigned int ping_count;
extern unsigned int sendPing;
extern unsigned int turnTimer;
unsigned int turn_count;
extern char stateBlackLine;
unsigned int doneTurn;
unsigned int doneDrive;




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
        if(time_count_en){
          if(time_count >= MAXTIME) time_count = RESET;
            else time_count += SECOND;
          time_display();
        }
  }
  if(turnTimer){
    if(turn_count++ > SECOND){
      if(!(distance--)){
        doneTurn = HIGH;
        //stateBlackLine = DRIVE;
        turnTimer = LOW;
      }
    }
  }
    
  
  if (second_count++ > COUNT_TWENTY){
    second_count = LOW;
    newSecond = HIGH;
    send = HIGH;
    sample = HIGH;
    scroll++;
    if(startTimer){
      if(!(distance--)){
         doneDrive = HIGH;
         startTimer = LOW;
      }
    }
   
  }
  
  if(ping_count++ > HUNDREDS){
    ping_count = LOW;
    sendPing = HIGH;
  }
    
  // Time Sequence
  one_time = HIGH;
  if(Time_Sequence++ > TIME_MAX_250){
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
   if (wait_count++ > waitTime){
    wait_count = LOW;
    endWait = HIGH;
   }
   if (newDrive_count++ > COUNT_FOUR){
    newDrive_count = LOW;
    newDrive = HIGH;
   }
   
   

   
    TB0CCTL2 &= ~CCIFG; 
    TB0CCR2 += TB0CCR2_INTERVAL;
  case S14: break;
  default: break;
  }
//--------------------------------------------------------------------
}

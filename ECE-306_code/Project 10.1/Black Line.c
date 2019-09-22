//------------------------------------------------------------------------------
//
//  Description: This file contains the function that utalizes the ADC to follow 
//               a black line that is on the ground and drive along the path.//  
//
//  Michael Barilla
//  Mar 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern char display_line[FOURTH][COUNT_ELEVEN];
extern volatile unsigned char display_changed;
unsigned int capture;
extern volatile unsigned int newSecond;
extern char state;
extern unsigned int time_count_en;
extern unsigned int runDrive;
unsigned int testSignal;

extern unsigned int waitTime;
extern unsigned int endWait;

void blackLine(void){
    switch(state){
    case CALIBRATE:
      strcpy(display_line[SECOND_LINE],"CALIBRATE ");
      display_changed = HIGH;
      calibrate();
      break;
    case INTERCEPT:
      strcpy(display_line[SECOND_LINE],"INTERCEPT ");
      display_changed = HIGH;
      intercept();
      break;
    case TURN: 
      strcpy(display_line[SECOND_LINE],"  TURNING ");
      if(drivePivot(FIRST))state = DRIVE;
      break;
    case DRIVE:
      strcpy(display_line[SECOND_LINE],"  CIRCLING ");
      display_changed = HIGH;
      time_count_en = HIGH;
      followCircle();
      break;
    case TURN2: 
      strcpy(display_line[SECOND_LINE],"  TURNING ");
      if(drivePivot(FIRST))state = STOP;
      break;
    case STOP:
      strcpy(display_line[SECOND_LINE],"  STOP   ");
      display_changed = HIGH;
      time_count_en = LOW;
      driveForward(CRUISE,CRUISE);
      waitTime = TWOSECS;
      TB0CCTL2 &=~ CCIFG;
      TB0CCTL2 |= CCIE;
      if(endWait){
          TB0CCTL2 &= ~CCIE;
          state = INTERCEPT;
          endWait = RESET;
          capture = LOW;
          All_Wheel_Off();
      }
      break;
    default: break;
    }
}
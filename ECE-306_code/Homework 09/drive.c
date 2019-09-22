//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This file contains the functions used to drive the car forward
//      (1 sec), backward (2 sec), forward (1 sec), Clockwise (3 sec), Counter
//      Clockwise (3 secs) with various pauses between
//
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "macros.h"
#include  "functions.h"
#include  <string.h>

extern volatile unsigned int newSecond;
unsigned int driveState = NOSTATE;
unsigned int count;
extern unsigned int runCar;
extern volatile unsigned char display_changed;
extern char display_line[FOURTH][COUNT_ELEVEN];


void drive(void){
  if(newSecond){
    newSecond = LOW;
    switch(driveState){
    case NOSTATE:
      driveState = WAIT1;
      break;
    case WAIT1:
      All_Wheel_Off();
      driveState = FORWARD1;
      break;
    case FORWARD1:
      strcpy(display_line[THIRD_LINE], " FORWARD  ");
      display_changed = HIGH;
      Forward();
      driveState = WAIT2;
      break;
    case WAIT2:
      All_Wheel_Off();
      driveState = BACKWARD;
      break;
    case BACKWARD:
      strcpy(display_line[THIRD_LINE], " REVERSE  ");
      display_changed = HIGH;
      Reverse();
      if(count++ >= 2){
        count = RESET_STATE;
        driveState = WAIT3;
      }
      break;
    case WAIT3:
      All_Wheel_Off();
      driveState = FORWARD2;
      break;
    case FORWARD2:
      strcpy(display_line[THIRD_LINE], " FORWARD  ");
      display_changed = HIGH;
      Forward();
      driveState = WAIT4;
      break;
    case WAIT4:
      All_Wheel_Off();
      driveState = CW;
      break;
    case CW:
      strcpy(display_line[THIRD_LINE], " CW TURN  ");
      display_changed = HIGH;
      CW_Turn();
      if(count++ >= 3){
        count = RESET_STATE;
        driveState = WAIT5;
      }
      break;
    case WAIT5:
      All_Wheel_Off();
      if(count++ >=2){
        count = RESET_STATE;
        driveState = CCW;
      }
      break;
    case CCW:
      strcpy(display_line[THIRD_LINE], " CCW TURN  ");
      display_changed = HIGH;
      CCW_Turn();
      if(count++ >= 3){
        count = RESET_STATE;
        driveState = WAIT6;
      }
      break;
    default:
      All_Wheel_Off();
      driveState = NOSTATE;
      runCar = LOW;
      strcpy(display_line[THIRD_LINE], "           ");
      break;
    }
  }      
}
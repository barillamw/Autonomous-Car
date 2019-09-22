//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

  // Global Variables
volatile char slow_input_down;
extern char display_line[FOURTH][COUNT_ELEVEN];
extern char *display[FOURTH];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int Last_Time_Sequence;
unsigned int cycle_time;
unsigned int time_change;
unsigned int time_change2;

unsigned int switchONE;
unsigned int switchTWO;

unsigned int capture;
extern volatile unsigned int newSecond;
extern char state;
extern unsigned int time_count_en;
extern unsigned int runDrive;
unsigned int testTurn;

extern unsigned int waitTime;
extern unsigned int endWait;



void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  
  PM5CTL0 &= ~LOCKLPM5;
  
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  strcpy(display_line[FIRST_LINE], "          ");
  //update_string(display_line[FIRST_LINE], FIRST_LINE);
  strcpy(display_line[SECOND_LINE], "          ");
  //update_string(display_line[SECOND_LINE], SECOND_LINE);
  strcpy(display_line[THIRD_LINE], "          ");
  strcpy(display_line[FOURTH_LINE], "          ");
  display_changed = HIGH;
  //update_string(display_line[FOURTH_LINE], FOURTH_LINE);
  
    Display_Update(FOURTH_LINE,SECOND_LINE,FIRST_LINE,FIRST_LINE);
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    
    if(switchONE){
        switchONE = LOW;
        //strcpy(display_line[THIRD_LINE], " SWITCH 1  ");
        display_changed = HIGH;
        capture = HIGH;
        
    }
    if(switchTWO){
        switchTWO = LOW;
        //strcpy(display_line[THIRD_LINE], " SWITCH 2  ");
        display_changed = HIGH;
        P5OUT &= ~IR_LED;
        Begin_ADC();
        testTurn = HIGH;
        


        
    }
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
      //time_count_en = HIGH;
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

    /*displayADC();
    followCircle();*/
    display_changed = HIGH;
    Display_Process();
  }
//------------------------------------------------------------------------------
}






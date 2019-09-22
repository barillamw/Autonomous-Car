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
unsigned char event;
unsigned char state;
unsigned char shape;

unsigned int switchONE;
unsigned int switchTWO;


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
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  strcpy(display_line[FIRST_LINE], "   NCSU   ");
  display_changed = HIGH;
  //update_string(display_line[FIRST_LINE], FIRST_LINE);
  strcpy(display_line[SECOND_LINE], " WOLFPACK ");
  display_changed = HIGH;
  //update_string(display_line[SECOND_LINE], SECOND_LINE);
  strcpy(display_line[THIRD_LINE], "  ECE306  ");
  display_changed = HIGH;
  //update_string(display_line[FOURTH_LINE], FOURTH_LINE);

  Display_Update(FOURTH_LINE,SECOND_LINE,FIRST_LINE,FIRST_LINE);

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    switch(Time_Sequence){
      case S1250:                        //
        if(one_time){
          Init_LEDs();
          lcd_BIG_mid();
          //strcpy(display_line[THIRD_LINE], " STRAIGHT  ");
          display_changed = HIGH;
          one_time = RESET_STATE;
        }
        Time_Sequence = RESET_STATE;             //
        break;
      case S1000:                        //
        if(one_time){
          GREEN_LED_ON;            // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;
      case S750:                         //
        if(one_time){
          RED_LED_ON;            // Change State of LED 4
          GREEN_LED_OFF;           // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;
      case S500:                         //
        if(one_time){
          lcd_4line();
          GREEN_LED_ON;            // Change State of LED 5
          display_changed = HIGH;
          one_time = LOW;
        }
        break;
      case  S250:                        //
        if(one_time){
          RED_LED_OFF;           // Change State of LED 4
          GREEN_LED_OFF;           // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;                         //
      default: break;
    }
    
    if (Last_Time_Sequence != Time_Sequence){
      Last_Time_Sequence = Time_Sequence;
      cycle_time++;
      time_change = HIGH;
      time_change2 = HIGH;
    } 
    
    if(switchONE){
        switchONE = LOW;
        strcpy(display_line[THIRD_LINE], " SWITCH 1  ");
    }
    if(switchTWO){
        switchTWO = LOW;
        strcpy(display_line[THIRD_LINE], " SWITCH 2  ");
    }
    
    Switches_Process();                // Check for switch state change
    Display_Process();
//  paths();
//  Wheels();

  }
//------------------------------------------------------------------------------
}






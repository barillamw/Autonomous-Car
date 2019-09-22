//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to initiate the MSP430.
//  
//
//  Michael Barilla
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

//Global Variables
extern char display_line[FOURTH][COUNT_ELEVEN];
extern char *display[FOURTH];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;



void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=LOW;i<COUNT_ELEVEN;i++){
    display_line[FIRST_LINE][i] = RESET_STATE;
    display_line[SECOND_LINE][i] = RESET_STATE;
    display_line[THIRD_LINE][i] = RESET_STATE;
    display_line[FOURTH_LINE][i] = RESET_STATE;
  }
  display_line[FIRST_LINE][COUNT_TEN] = RESET_STATE;
  display_line[SECOND_LINE][COUNT_TEN] = RESET_STATE;
  display_line[THIRD_LINE][COUNT_TEN] = RESET_STATE;
  display_line[FOURTH_LINE][COUNT_TEN] = RESET_STATE;

  display[FIRST_LINE] = &display_line[FIRST_LINE][LOW];
  display[SECOND_LINE] = &display_line[SECOND_LINE][LOW];
  display[THIRD_LINE] = &display_line[THIRD_LINE][LOW];
  display[FOURTH_LINE] = &display_line[FOURTH_LINE][LOW];
  update_display = LOW;
  update_display_count = LOW;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------

}

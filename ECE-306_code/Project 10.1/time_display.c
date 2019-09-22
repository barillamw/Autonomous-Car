//------------------------------------------------------------------------------
//
//  Description: This file contains the function to update a timer on the screen
//  
//
//  Michael Barilla
//  Mar 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern unsigned int time_count;
extern char bcd_char [COUNT_ELEVEN];
extern char display_line[FOURTH][COUNT_ELEVEN];
extern volatile unsigned char display_changed;

void time_display(void){
  display_line[FOURTH_LINE][CHAR0] = 'T';
  display_line[FOURTH_LINE][CHAR1] = 'I';
  display_line[FOURTH_LINE][CHAR2] = 'M';
  display_line[FOURTH_LINE][CHAR3] = 'E';
  display_line[FOURTH_LINE][CHAR4] = ' ';
  HEXtoBCD(time_count);
  display_line[FOURTH_LINE][CHAR5] = bcd_char[CHAR0];
  display_line[FOURTH_LINE][CHAR6] = bcd_char[CHAR1];
  display_line[FOURTH_LINE][CHAR7] = bcd_char[CHAR2];
  display_line[FOURTH_LINE][CHAR8] = '.';
  display_line[FOURTH_LINE][CHAR9] = bcd_char[CHAR3];
}  
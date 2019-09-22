//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to initiate the ADC Registers 
//  to set pins 2, 3, and 5 to measure the V_Detect_L, V_Detece_R, and V_Thumb 
//  respectively.
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

extern volatile unsigned char display_changed;
extern char display_line[FOURTH][COUNT_ELEVEN];
extern unsigned int V_Detect_R;
extern unsigned int V_Detect_L;
extern char adc_char [CHAR_LENGTH];
char display_number[SECOND][FOURTH];
char LeftVal[COUNT_ELEVEN];
char RightVal[COUNT_ELEVEN];

void Line_Detect(void){
  //char display_number[SECOND][FOURTH];
  HEXtoBCD(V_Detect_L);
  strcpy(LeftVal,"LFT:       ");
  LeftVal[CHAR6] = adc_char[CHAR0];
  LeftVal[CHAR7] = adc_char[CHAR1];
  LeftVal[CHAR8] = adc_char[CHAR2];
  LeftVal[CHAR9] = adc_char[CHAR3];
  strcpy(display_line[THIRD_LINE],LeftVal);
  
  HEXtoBCD(V_Detect_R);
  strcpy(RightVal,"RHT:       ");
  RightVal[CHAR6] = adc_char[CHAR0];
  RightVal[CHAR7] = adc_char[CHAR1];
  RightVal[CHAR8] = adc_char[CHAR2];
  RightVal[CHAR9] = adc_char[CHAR3];
  strcpy(display_line[FOURTH_LINE],RightVal);
  

  if(V_Detect_R > THOUSANDS && V_Detect_L > THOUSANDS)
    strcpy(display_line[SECOND_LINE]," ON BLACK ");
  else if((V_Detect_R < THOUSANDS) && (V_Detect_L < THOUSANDS))
    strcpy(display_line[SECOND_LINE],"OFF BLACK ");
  else if((V_Detect_R > THOUSANDS) && (V_Detect_L < THOUSANDS))
    strcpy(display_line[SECOND_LINE],"OFF 2 RHT ");
  else if((V_Detect_R < THOUSANDS) && (V_Detect_L > THOUSANDS))
    strcpy(display_line[SECOND_LINE],"OFF 2 LFT ");
  else
    strcpy(display_line[SECOND_LINE],"  ERROR  ");
  
  
  display_changed = HIGH;
  
}
  
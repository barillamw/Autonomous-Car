//------------------------------------------------------------------------------
//
//  Description: This file contains the functions execute a White/Black 
//     detection calibration
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

extern char display_line[FOURTH][COUNT_ELEVEN];
extern volatile unsigned char display_changed;
unsigned int calibrate_count = RESET;
unsigned int white = WHITE;
unsigned int black = BLACK;
unsigned int midpoint = RESET;
unsigned int R_average;
unsigned int L_average;
extern unsigned int R_count;
extern unsigned int L_count;
extern unsigned int V_Detect_R[MAX_ARRAY];
extern unsigned int V_Detect_L[MAX_ARRAY];
unsigned int sumR;
unsigned int sumL;
extern unsigned int capture;
extern char stateBlackLine;
extern char bcd_char [COUNT_ELEVEN];
extern unsigned int action;

void calibrate(void){
  displayADC(SECOND_LINE);
  if(!white){
    strcpy(display_line[FOURTH_LINE],"CALIB WHTE");
    display_changed = HIGH;
    if(capture){
      Read_ADC();
      if(calibrate_count++ == COUNT_FIFTY){
        white = (R_average+L_average)/SECOND;
        calibrate_count = RESET;
        capture = RESET;
      }
      //RED_LED_ON;
      //GREEN_LED_OFF;
    }
    else{
      //GREEN_LED_ON;
      //RED_LED_OFF;
    }
  }
  else if(!black) {
    strcpy(display_line[FOURTH_LINE],"CALIB BLCK");
    display_changed = HIGH;
    if(capture){
      if(calibrate_count++ == COUNT_FIFTY){
        Read_ADC();
        black = (R_average+L_average)/DIV_BY_TWO;
        calibrate_count = RESET;
        capture = RESET;
      }
      //RED_LED_ON;
      //GREEN_LED_OFF;
    }
    else{
      //GREEN_LED_ON;
      //RED_LED_OFF;
    }
  }
  else{
    midpoint = ((black-white)/COUNT_FIVE) + white;
    stateBlackLine = SEARCHING;
    strcpy(display_line[FOURTH_LINE],"          ");
    //GREEN_LED_ON;
    //RED_LED_OFF;
  }
}

void calibrateWhite(void){
  displayADC(SECOND_LINE);
  if(!white){
    strcpy(display_line[FOURTH_LINE],"CALIB WHTE");
    display_changed = HIGH;
    Begin_ADC();
    if(capture){
      Read_ADC();
      if(calibrate_count++ == COUNT_FIFTY){
        white = (R_average+L_average)/SECOND;
        midpoint = ((black-white)/COUNT_FIVE) + white;
        End_ADC();
        calibrate_count = RESET;
        capture = RESET;
        action = RESET;
      }
      //RED_LED_ON;
      //GREEN_LED_OFF;
    }
  }
}

void calibrateBlack(void){
  if(!black) {
    strcpy(display_line[FOURTH_LINE],"CALIB BLCK");
    display_changed = HIGH;
    if(capture){
      if(calibrate_count++ == COUNT_FIFTY){
        Read_ADC();
        black = (R_average+L_average)/DIV_BY_TWO;
        midpoint = ((black-white)/COUNT_FIVE) + white;
        calibrate_count = RESET;
        capture = RESET;
        action = RESET;
      }
      //RED_LED_ON;
      //GREEN_LED_OFF;
    }
    else{
      //GREEN_LED_ON;
      //RED_LED_OFF;
    }
  }
}
  

void Read_ADC(void){
  int i;
  sumR = RESET;
  sumL = RESET;
  for(i=BEGIN_ARRAY; i<MAX_ARRAY; i++) sumR = sumR + V_Detect_R[i];
  for(i=BEGIN_ARRAY; i<MAX_ARRAY; i++) sumL = sumL + V_Detect_L[i];
  R_average = (sumR>>SHIFT);
  L_average = sumL>>SHIFT;
  //R_count = RESET;
  //L_count = RESET;
  
}

void displayADC(int line){
  Read_ADC();
  HEXtoBCD(L_average);
  display_line[line][CHAR0] = bcd_char[CHAR0];
  display_line[line][CHAR1] = bcd_char[CHAR1];
  display_line[line][CHAR2] = bcd_char[CHAR2];
  display_line[line][CHAR3] = bcd_char[CHAR3];
  HEXtoBCD(R_average);
  display_line[line][CHAR5] = bcd_char[CHAR0];
  display_line[line][CHAR6] = bcd_char[CHAR1];
  display_line[line][CHAR7] = bcd_char[CHAR2];
  display_line[line][CHAR8] = bcd_char[CHAR3];
  display_line[line][CHAR4] = ' ';
}



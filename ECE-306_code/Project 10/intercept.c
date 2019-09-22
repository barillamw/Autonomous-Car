//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to execute black line 
//      detection and intercept.
//
//  Michael Barilla
//  Mar 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern unsigned int R_average;
extern unsigned int L_average;
extern unsigned int V_Detect_R[MAX_ARRAY];
extern unsigned int V_Detect_L[MAX_ARRAY];
extern unsigned int R_count;
extern unsigned int L_count;
extern unsigned int black;
extern unsigned int midpoint;
//extern char state;
extern char display_line[FOURTH][COUNT_ELEVEN];
extern volatile unsigned char display_changed;
extern unsigned int capture;
unsigned int searching = HIGH;
unsigned int endWait;
extern unsigned int newDrive;
extern unsigned int waitTime;

void whiteBoard(void){
  displayADC();
  Read_ADC();
  if(capture){
  if(searching){
      strcpy(display_line[SECOND_LINE],"  SEARCH  ");
      display_changed = HIGH;
      driveForward(SEARCH,SEARCH);
      if(R_average < midpoint || L_average < midpoint) searching = LOW;
  }
 else{
  strcpy(display_line[FOURTH_LINE],"  BOARD  ");
  display_changed = HIGH;
  All_Wheel_Off();
  /*waitTime = TWOSECS;
  TB0CCTL2 &=~ CCIFG;
  TB0CCTL2 |= CCIE;
  if(endWait){
    strcpy(display_line[SECOND_LINE],"  WAITING ");
    TB0CCTL2 &= ~CCIE;
    state = TURN;
    capture = RESET;
    endWait = RESET;
    searching = LOW;
    }*/
  }
  }
}

  

void intercept(void){
  displayADC();
  if(capture){
    Read_ADC();
    if(searching){
        strcpy(display_line[FOURTH_LINE],"  SEARCH  ");
        display_changed = HIGH;
        driveForward(SEARCH,SEARCH);
        if(R_average > midpoint || L_average > midpoint) searching = LOW;
    }
   else{
    strcpy(display_line[FOURTH_LINE],"  FOUND  ");
    display_changed = HIGH;
    All_Wheel_Off();
    waitTime = TWOSECS;
    TB0CCTL2 &=~ CCIFG;
    TB0CCTL2 |= CCIE;
    if(endWait){
      strcpy(display_line[SECOND_LINE],"  WAITING ");
      TB0CCTL2 &= ~CCIE;
      //state = TURN;
      capture = RESET;
      endWait = RESET;
      searching = LOW;
      }
    }
   }
  }



  
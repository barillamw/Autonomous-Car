//------------------------------------------------------------------------------
//
//  Description: This file contains the functions execute a PID and a wheel 
//      control based on a given value.
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

 int r_error;
 int l_error;
extern unsigned int black ; 
extern unsigned int midpoint;
extern unsigned int R_average;
extern unsigned int L_average;
extern unsigned int R_count;
extern unsigned int L_count;
extern unsigned int V_Detect_R[MAX_ARRAY];
extern unsigned int V_Detect_L[MAX_ARRAY];
extern unsigned int doneDrive;

 int current_error;
 int previous_error;
 int sum_error;
 int delta_error;
 int proportional;
 int integral;
 int derivative;
 
 extern unsigned int waitTime;
 extern unsigned int endWait;
 extern char stateBlackLine;
 
 //int sample_time=0.1; //1 second;
 extern char display_line[FOURTH][COUNT_ELEVEN];

unsigned int lspeed;
unsigned int rspeed;

unsigned int runDrive;
char current_state;
char previous_state;
extern unsigned int sample;
extern char driveCommand[SMALL_RING_SIZE];
extern unsigned int distance;
extern unsigned int startTimer;
unsigned int displayCircle = LOW;


char getCurrentState(void){
  Read_ADC();
  
  if(R_average > midpoint && L_average > midpoint) return BLACK_LINE;
  else if(R_average < midpoint && L_average > midpoint) return RIGHT_SIDE;
  else if(R_average > midpoint && L_average < midpoint) return LEFT_SIDE;
  else return WHITE_BOARD;
}

void followCircle(void){
  waitTime = TWOSECS;
  TB0CCTL2 &=~ CCIFG;
  TB0CCTL2 |= CCIE;
  
  if(endWait||displayCircle){
    endWait = LOW;
    displayCircle = HIGH;
    strcpy(display_line[FIRST_LINE],"BL  CIRCLE");
  }
  else{
    strcpy(display_line[FIRST_LINE],"BL  TRAVEL");
  }
  
  
  if(driveCommand[CHARC] == 'I'){
    TB0CCTL2 &= ~CCIE;
    All_Wheel_Off();
    stateBlackLine = EXIT;
    distance = COUNT_FOUR;
    doneDrive = LOW;
    startTimer = HIGH;
  }
  Read_ADC();
  Reverse_Off();
  //displayADC();
  Read_ADC();
  
  
   if(V_Detect_R[R_count%MAX_ARRAY] > V_Detect_L[L_count%MAX_ARRAY]  ){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = LCORRECT;
    }
   else if(V_Detect_R[R_count%MAX_ARRAY] < V_Detect_L[L_count%MAX_ARRAY]){
      RIGHT_FORWARD_SPEED = RCORRECT;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
    }
  }  
      
  
  
   
      

  
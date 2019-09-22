//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This file contains the functions used to run the wheels using 
//      pulse width modulation
//
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "macros.h"
#include  "functions.h"

void Forward(){
  Reverse_Off();
  RIGHT_FORWARD_SPEED = TOTAL;
  LEFT_FORWARD_SPEED = TOTAL;
}

void Forward_Off(){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}

void Reverse_Off(){
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Reverse(){
  Forward_Off();
  RIGHT_REVERSE_SPEED = TOTAL;
  LEFT_REVERSE_SPEED = TOTAL;
}

void All_Wheel_Off(){
  Forward_Off();
  Reverse_Off();
}

void CW_Turn(){
  All_Wheel_Off();
  RIGHT_REVERSE_SPEED = TOTAL;
  LEFT_FORWARD_SPEED = TOTAL;  
}

void CCW_Turn(){
  All_Wheel_Off();
  LEFT_REVERSE_SPEED = TOTAL;
  RIGHT_FORWARD_SPEED = TOTAL;
}
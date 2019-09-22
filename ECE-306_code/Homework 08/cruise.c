//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to drive the car along certain
//      paths like forward and a 90 degree turn in place. 
//  
//
//  Michael Barilla
//  Mar 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "macros.h"
#include  "functions.h"

extern volatile unsigned int newDrive;
unsigned int drive_count;
extern unsigned char state;


void driveForward(unsigned int speedL, unsigned int speedR){
  Reverse_Off();
  RIGHT_FORWARD_SPEED = speedR;
  LEFT_FORWARD_SPEED = speedL+SPEED_SHIFT;
}

void driveReverse(){
  Forward_Off();
  RIGHT_REVERSE_SPEED = CRUISE+SPEED_SHIFT;
  LEFT_REVERSE_SPEED = CRUISE;
}

void turnRight(){
  All_Wheel_Off();
  RIGHT_REVERSE_SPEED = CRUISE + SPEED_SHIFT;
  LEFT_FORWARD_SPEED = CRUISE;
}

void turnLeft(){
  All_Wheel_Off();
  RIGHT_FORWARD_SPEED = CRUISE + SPEED_SHIFT;
  LEFT_REVERSE_SPEED = CRUISE;
}

void Reverse_Off(){
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void All_Wheel_Off(){
  Forward_Off();
  Reverse_Off();
}

void Forward_Off(){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}

void rightTurn(){
  All_Wheel_Off();
  RIGHT_REVERSE_SPEED = HALF;
  LEFT_FORWARD_SPEED = HALF;  
}

int drivePivot(int length){
  TB0CCTL2 |= CCIE;
  if(newDrive){
      newDrive=RESET;
      if(drive_count++ < QUARTER_LOOP*length){
        rightTurn();
        return LOW;
      }
      else if(drive_count++ < CHAR7){
         driveForward(CRUISE,CRUISE);
      }
      else{
      //state = DRIVE;
      All_Wheel_Off();
      TB0CCTL2 &= ~CCIE;
      drive_count = RESET;
      return HIGH;
     }
  }
  return LOW;
}


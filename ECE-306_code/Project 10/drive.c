//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to drive the car from TCP
//
//  Michael Barilla
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>


char driveCommand[SMALL_RING_SIZE];
extern char display_line[FOURTH][COUNT_ELEVEN];
char firstDrive[FOURTH];
char secondDrive[FOURTH];
unsigned int readyDrive;

unsigned int distance;
char direction;

char driveState = LOAD;
unsigned int startTimer;
unsigned int turnTimer;
unsigned int stopCount;

unsigned int blackLineR;
unsigned int blackLineL;
char stateBlackLine = CALIBRATE;
unsigned int capture;

int pwmL;
int pwmR;


void drive(void){
  if(strstr(driveCommand,"0208") && readyDrive){
    readyDrive = LOW;
    switch(driveCommand[CHARC]){
      case 'N':
        pwmL = (driveCommand[CHAR5]-ASCII_SHIFT)*HUNDREDS;
        pwmL += (driveCommand[CHAR6] - ASCII_SHIFT) * TENS;
        pwmL += (driveCommand[CHAR7] - ASCII_SHIFT);
        if(driveCommand[CHAR4] == '-') pwmL *= -1;
        
        pwmR = (driveCommand[CHAR9] - ASCII_SHIFT) * HUNDREDS;
        pwmR += (driveCommand[CHARA] - ASCII_SHIFT) * TENS;
        pwmR += (driveCommand[CHARB] - ASCII_SHIFT);
        if(driveCommand[CHAR8] == '-') pwmR *= -1;
        
        wheels(pwmR, pwmL);
        break;
      case 'L':
        //Follow Line Left
        break;
      case 'R':
        //Follow Line Right
        break;
      case 'I':
        stopCount++;
        break;
      case 'D':
        stopCount--;
        break;
    }
  }
}

void blackLine(void){
  switch(stateBlackLine){
    case CALIBRATE:
      strcpy(display_line[SECOND_LINE],"CALIBRATE ");
      calibrate();
      break;
    case SEARCHING:  
      //find white board
      strcpy(display_line[SECOND_LINE]," SEARCHING ");
      whiteBoard();
      break;
    /*case INTERCEPT:
      strcpy(display_line[SECOND_LINE],"INTERCEPT ");
      //display_changed = HIGH;
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
    default: break;*/
    }
}
    
      
        
    
    
    /*for(int i=RESET; i< NINE; i++){
      if(i<FOURTH)
        firstDrive[i] = driveCommand[i+FOURTH];
      else
        secondDrive[i-COUNT_FOUR] = driveCommand[i+FOURTH];
    }
    for(int i=RESET; i<SMALL_RING_SIZE; i++)
      driveCommand[i] = '\0';
  }
  
  if(firstDrive[CHAR0]){
    switch(driveState){
      case LOAD:
        direction = firstDrive[CHAR0];
        distance =  (firstDrive[CHAR1]-ASCII_SHIFT) * HUNDREDS;
        distance += (firstDrive[CHAR2]-ASCII_SHIFT) * TENS;
        distance += (firstDrive[CHAR3]-ASCII_SHIFT+COUNT_ONE);
        driveState = DRIVE;
        lcd_BIG_mid();
        strcpy(display_line[FIRST_LINE], "          ");
        strcpy(display_line[SECOND_LINE], "          ");
        strcpy(display_line[THIRD_LINE], "          ");
        strcpy(display_line[FOURTH_LINE], "          ");
        display_line[SECOND_LINE][CHAR3] = firstDrive[CHAR0];
        display_line[SECOND_LINE][CHAR4] = firstDrive[CHAR1];
        display_line[SECOND_LINE][CHAR5] = firstDrive[CHAR2];
        display_line[SECOND_LINE][CHAR6] = firstDrive[CHAR3];
        driveState = DRIVE;
      case DRIVE:
        switch(direction){
          case FORWARD:
            startTimer = HIGH;
            driveForward(CRUISE, CRUISE);
            break;
          case BACKWARD:
            startTimer = HIGH;
            driveReverse();
            break;
          case RIGHT:
            turnTimer = HIGH;
            turnRight();
            break;
          case LEFT:
            turnTimer = HIGH;
            turnLeft();
            break;
          default:break;
        }
        break;
      case END:
        All_Wheel_Off();
        for(int i = RESET; i<COUNT_FOUR; i++)
          firstDrive[i] = '\0';
        driveState = LOAD;
        break;
      default: break;
      }   

  }
  else if(secondDrive[CHAR0]){
    switch(driveState){
      case LOAD:
        direction = secondDrive[CHAR0];
        distance =  (secondDrive[CHAR1]-ASCII_SHIFT) * HUNDREDS;
        distance += (secondDrive[CHAR2]-ASCII_SHIFT) * TENS;
        distance += (secondDrive[CHAR3]-ASCII_SHIFT+COUNT_ONE);
        strcpy(display_line[FIRST_LINE], "          ");
        strcpy(display_line[SECOND_LINE], "          ");
        strcpy(display_line[THIRD_LINE], "          ");
        strcpy(display_line[FOURTH_LINE], "          ");
        display_line[SECOND_LINE][CHAR3] = secondDrive[CHAR0];
        display_line[SECOND_LINE][CHAR4] = secondDrive[CHAR1];
        display_line[SECOND_LINE][CHAR5] = secondDrive[CHAR2];
        display_line[SECOND_LINE][CHAR6] = secondDrive[CHAR3];
        driveState = DRIVE;
      case DRIVE:
        switch(direction){
          case FORWARD:
            startTimer = HIGH;
            driveForward(CRUISE, CRUISE);
            break;
          case BACKWARD:
            startTimer = HIGH;
            driveReverse();
            break;
          case RIGHT:
            turnTimer = HIGH;
            turnRight();
            break;
          case LEFT:
            turnTimer = HIGH;
            turnLeft();
            break;
          default:break;
        }
        break;
      case END:
        All_Wheel_Off();
        for(int i = RESET; i<COUNT_FOUR; i++)
          secondDrive[i] = '\0';
        driveState = LOAD;
        break;
      default: break;
    }
  }
} */   
//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to update the network 
//   and maintain it during the code operation
//  
//
//  Michael Barilla
//  Apr 2019
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
char stateBlackLine = START;
unsigned int capture;
unsigned int follow;
unsigned int oneTime;

int pwmL;
int pwmR;

extern unsigned int time_count_en;
extern unsigned int waitTime;
extern unsigned int endWait;

unsigned int left = LOW;
unsigned int right = HIGH;
extern unsigned int distance;
extern unsigned int endWait;
unsigned int searchState = RESET;

extern unsigned int doneTurn;
extern unsigned int doneDrive;
extern unsigned int turn_count;
extern unsigned int menu_select;
unsigned int waiting = HIGH;
extern unsigned int time_count_en;

extern int secondDot;
extern int offset3;
extern int offset4;
extern char IP[SMALL_RING_SIZE];
extern unsigned int midpoint;
extern unsigned int white;
extern unsigned int black;

void program(void){
  lcd_4line();
  if(waiting) {
    strcpy(display_line[FIRST_LINE],"  Waiting ");
    strcpy(display_line[SECOND_LINE],"For  Input");
    strcpy(display_line[THIRD_LINE], "          ");
    time_display();
  }
  
  if(!follow)
    drive();
  else
    blackLine();
}

void drive(void){
  if(strstr(driveCommand,"0208") && readyDrive){
    waiting = LOW;
    readyDrive = LOW;
    switch(driveCommand[CHARC]){
      case 'N':
        pwmL = (driveCommand[CHAR5]-ASCII_SHIFT)*HUNDREDS;
        pwmL += (driveCommand[CHAR6] - ASCII_SHIFT) * TENS;
        pwmL += (driveCommand[CHAR7] - ASCII_SHIFT);
        if(driveCommand[CHAR4] == '-') pwmL *= NEG;
        
        pwmR = (driveCommand[CHAR9] - ASCII_SHIFT) * HUNDREDS;
        pwmR += (driveCommand[CHARA] - ASCII_SHIFT) * TENS;
        pwmR += (driveCommand[CHARB] - ASCII_SHIFT);
        if(driveCommand[CHAR8] == '-') pwmR *= NEG;
        
        wheels(pwmR, pwmL);
        if(pwmR && pwmL){
          time_count_en = HIGH;
          for(int i = RESET; i<COUNT_ELEVEN; i++){
            display_line[FIRST_LINE][i] = driveCommand[i+CHAR4];
          }
          display_line[FIRST_LINE][CHARA] = ' ';
          strcpy(display_line[SECOND_LINE],"          ");
          strcpy(display_line[THIRD_LINE],"          ");
          for(int i=RESET; i<SMALL_RING_SIZE; i++){
            if(i<secondDot) display_line[SECOND_LINE][i+offset3] = IP[i];
            if(i>secondDot) display_line[THIRD_LINE][i-offset4] = IP[i];
          }
          
        }
        
        oneTime = HIGH;
        break;
      case 'L':
        left = HIGH;
        right = LOW;
        follow = HIGH;
        menu_select = S2;
        endWait = LOW;
        //DisplayThing Here
        strcpy(display_line[FIRST_LINE]," BL START ");
        break;
      case 'R':
        left = LOW;
        right = HIGH;
        follow = HIGH;
        menu_select = S2;
        endWait = LOW;
        time_count_en = HIGH;
        //displayThing Here
        strcpy(display_line[FIRST_LINE]," BL START ");
        break;
      case 'I':
        if(oneTime){
          oneTime = LOW;
          strcpy(display_line[FIRST_LINE],"ARRIVED   ");
          display_line[FIRST_LINE][CHAR9] = (stopCount++%NINE)+ASCII_SHIFT;
        }
        break;
      case 'D':
        stopCount++;
        strcpy(display_line[FIRST_LINE],"ARRIVED   ");
        display_line[FIRST_LINE][CHAR9] = (stopCount%NINE)+ASCII_SHIFT;
        break;
    }
  }
}

void blackLine(void){
  TB0CCTL2 &= ~CCIFG; //CCR2 clear interrupt flag
  TB0CCTL2 |= CCIE;   // CCR2 enable interrupt
  strcpy(display_line[SECOND_LINE],"          ");
  strcpy(display_line[THIRD_LINE],"          ");
  switch(stateBlackLine){
    case START:
      waitTime = TWOSECS;
      TB0CCTL2 &=~ CCIFG;
      TB0CCTL2 |= CCIE;
      if(endWait){
        //strcpy(display_line[SECOND_LINE],"  WAITING ");
        TB0CCTL2 &= ~CCIE;
        stateBlackLine = TRAVEL;
        midpoint = ((black-white)/COUNT_FIVE) + white;
        endWait = RESET;
        waitTime = DISTANCE;
        TB0CCTL2 &=~ CCIFG;
        TB0CCTL2 |= CCIE;
        }
      break;
    case TRAVEL:
      driveForward(CRUISE,CRUISE);
      strcpy(display_line[FIRST_LINE],"INTERCEPT ");
      if(endWait){
        TB0CCTL2 &= ~CCIE;
        stateBlackLine = SEARCHING;
        Begin_ADC();
      }
      break;
    case SEARCHING:  
      //find white board
      //strcpy(display_line[FIRST_LINE]," SEARCHING ");
      whiteBoard();
      break;
    case INTERCEPT:
      //strcpy(display_line[FIRST_LINE],"INTERCEPT ");
      //display_changed = HIGH;
      intercept();
      break;
    case TURN: 
      //strcpy(display_line[FIRST_LINE],"  TURNING ");
      turnTimer = HIGH;
      if(right){
        turnRight();
      }
      else if(left){
        turnLeft();
      }
      if(doneTurn){
        doneTurn = LOW;
        turnTimer = LOW;
        stateBlackLine = DRIVE;
        endWait = LOW;
      }
      break;
    case DRIVE:
      //time_count_en = HIGH;
      followCircle();
      break;
    case EXIT: 
      strcpy(display_line[FIRST_LINE],"  BL EXIT ");
      driveForward(CRUISE,CRUISE);
      if(doneDrive) stateBlackLine = STOP;
      break;
    case STOP:
      strcpy(display_line[FIRST_LINE]," BL  STOP ");
      time_count_en = LOW;
      All_Wheel_Off();
      break;
    default: break;
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
  }*/  
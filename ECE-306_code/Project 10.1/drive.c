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



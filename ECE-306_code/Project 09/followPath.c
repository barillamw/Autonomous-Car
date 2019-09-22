//------------------------------------------------------------------------------
//
//  Description: This file contains the functions execute a calibration, line 
//    intercept, drive along path, and stop.
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

extern char state;

void followPath(void){
  switch(state){
  case START:
    start_intercept();
  case CALIBRATE:
    calibrate();
    break;
  case INTERCEPT;
    intercept();
    break;
  case DRIVE:
    pid();
    break;
  case STOP:
    stop_intercept();
    break;
  default:
    break;
  }
}



  
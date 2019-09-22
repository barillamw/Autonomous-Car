//------------------------------------------------------------------------------
//
//  Description: This file contains the implementation of sending and recieving
//               a UART serial communication message from one MSP430 to another
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

char serial_state = WAITING;
unsigned int once;
extern unsigned int freq;

extern unsigned int lineFinished;
extern unsigned int lineStart;

void serialProcess(void){
   switch(serial_state){
      case WAITING:
        strcpy(display_line[FIRST_LINE],"WAITING...");
        switch(freq){
        case K115:
          strcpy(display_line[THIRD_LINE],"BR: 115.2k");
          break;
        case K460:
          strcpy(display_line[THIRD_LINE],"BR: 460.8k");
          break;
        }
        if(lineStart) serial_state = RECIEVING;
        break;
      case RECIEVING:
        strcpy(display_line[FIRST_LINE]," RECIEVED ");
        if(lineFinished){
          lineFinished = LOW;
        }
        break;      
      case TRANSMITTING:
        strcpy(display_line[FIRST_LINE]," TRANSMIT ");
        if(once){
          once = LOW;
          display_Text_A0();
          Transmit_Text_A0();
        }
        switch(freq){
        case K115:
          strcpy(display_line[THIRD_LINE],"BR: 115.2k");
          break;
        case K460:
          strcpy(display_line[THIRD_LINE],"BR: 460.8k");
          break;
        }
        break;
      default: break;
    }
}
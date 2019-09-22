//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to run the utilities of the 
//      device.
//  
//
//  Michael Barilla
//  Apr 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

extern volatile unsigned char display_changed;
extern char display_line[FOURTH][COUNT_ELEVEN];

unsigned int switchONE;
unsigned int switchTWO;
extern unsigned int capture;
extern unsigned int menu_select;
extern unsigned int menu;
extern unsigned int setting;
extern unsigned int action;
extern unsigned int waiting;

extern unsigned int send;
extern unsigned int transmit;
extern unsigned int lineFinished;
char command;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern char Text[COUNT_ELEVEN];
extern volatile unsigned int usb_rx_ring_wr;

extern unsigned int follow;
extern char stateBlackLine;

extern unsigned int freq;

void utilities(void){
  Serial_PC();
  switches();
  Menu_Process();
  display_changed = HIGH;
  Display_Process();
}

void switches(void){
  if(switchONE){
        switchONE = LOW;
        //strcpy(display_line[THIRD_LINE], " SWITCH 1  ");
        //display_changed = HIGH;
        capture = HIGH;
        if(!menu_select)
          menu_select = menu;
        else if(menu_select == S1 && !action)
            action = setting;
        else if(menu_select == S2)
          follow = HIGH;
        
        
    }
    if(switchTWO){
        switchTWO = LOW;
        //strcpy(display_line[THIRD_LINE], " SWITCH 2  ");
        //display_changed = HIGH;
        //P5OUT &= ~IR_LED;
        //Begin_ADC();
        //testTurn = HIGH  
        if(action)
          action = RESET;
        else if (stateBlackLine == STOP){
          action = RESET;
          menu_select = RESET;
          follow = RESET;
          waiting = HIGH;
          stateBlackLine = START;
        }
        else if (menu_select)
          menu_select = RESET;

    }
}

void Serial_PC(void){
  if(transmit && send){

      send = LOW;
      transmit = LOW;
      Store_Text_A1();


      if(lineFinished){
        lineFinished = LOW;
        command = USB_Char_Rx[usb_rx_ring_wr-SECOND];
      }
        switch(command){
        case '^':
          strcpy(Text, "I'm Here");
          break;
        case 'F':
          freq = K115;
          Configure_Serial();
          strcpy(Text, "115,200");
          break;
        case 'S':
          freq = K96;
          Configure_Serial();
          strcpy(Text, "9,600");
          break;
        case 'T':
          transmit ^= transmit;
          break;
        default: break;
      }
    Transmit_Text_A1();
     }
}



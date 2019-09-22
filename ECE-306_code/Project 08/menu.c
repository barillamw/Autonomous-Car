
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern unsigned int freq;
extern char display_line[FOURTH][COUNT_ELEVEN];
extern volatile unsigned char display_changed;
extern unsigned int menu;
extern unsigned int capture;
extern char serial_state;


void menu_switch(void){
  Begin_ADC();
  if(!capture){
    switch(menu){
      case s0:
        strcpy(display_line[THIRD_LINE],"BR: 9.6k");
        display_changed = HIGH;
        freq = K96;
        break;
      case s1:
      case s2:
      case s3:
        strcpy(display_line[THIRD_LINE],"BR: 115.2k");
        display_changed = HIGH;
        freq = K115;
        break;
      case s4:
      case s5:
      case s6:
      case s7:
        strcpy(display_line[THIRD_LINE],"BR: 460.8k");
        display_changed = HIGH;
        freq = K460;
        break;
      default: break;
      }
  }
  else{
    capture = LOW;
   Configure_Serial();
   serial_state = WAITING;
   End_ADC();
   Begin_Serial();
  }
}



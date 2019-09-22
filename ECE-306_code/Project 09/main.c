//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

  // Global Variables
volatile char slow_input_down;
extern char display_line[FOURTH][COUNT_ELEVEN];
extern char *display[FOURTH];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int Last_Time_Sequence;
unsigned int cycle_time;
unsigned int time_change;
unsigned int time_change2;

unsigned int switchONE;
unsigned int switchTWO;


extern unsigned int menu;
extern unsigned int menu_select;

extern char Text[COUNT_ELEVEN];

extern unsigned int send;
extern unsigned int transmit;
extern unsigned int lineFinished;

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wr;
char command;
extern unsigned int freq;
extern unsigned int updateIP;














void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  
  PM5CTL0 &= ~LOCKLPM5;
  
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions 
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          // Initialize ADC
  Init_Serial();                       // Initialize Serial
  
  

// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  strcpy(display_line[FIRST_LINE], "          ");
  strcpy(display_line[SECOND_LINE], "          ");
  strcpy(display_line[THIRD_LINE], "          ");
  strcpy(display_line[FOURTH_LINE], "          ");
  display_changed = HIGH;
  
  Display_Update(FOURTH_LINE,SECOND_LINE,FIRST_LINE,FIRST_LINE);
  P5OUT |= IOT_RESET;
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    
    //IOT_Reset();
    updateNetwork();
    ping();
    drive();
    
 

      
    //Store_Text_A1();
    if(transmit && send){

      send = LOW;
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
        case 'I':
          updateIP = HIGH;
          command = 'T';
        default: break;
      }
    Transmit_Text_A1();
     }
    
    //IOT_Process();
    //Switch_Process();
    //Menu_Process();
    display_changed = HIGH;
    Display_Process();
  }
//------------------------------------------------------------------------------
}









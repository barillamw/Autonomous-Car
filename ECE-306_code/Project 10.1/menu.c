
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern unsigned int freq;
extern char display_line[FOURTH][COUNT_ELEVEN];
extern char bcd_char [COUNT_ELEVEN]; 
extern volatile unsigned char display_changed;
extern unsigned int ADC_Thumb;
extern unsigned int capture;
extern char serial_state;
unsigned int menu_select;
unsigned int menu;
unsigned int resistor;
unsigned int shapes;
unsigned int lyrics;
unsigned int counter;
unsigned int previous;
extern unsigned int scroll;
unsigned int action;
unsigned int setting;
extern unsigned int white;
extern unsigned int black;
extern char SSID[COUNT_ELEVEN];
extern char IP[SMALL_RING_SIZE];



void Menu_Process(void){
  Begin_ADC();
  menu = ADC_Thumb >> COUNT_TEN;
  
  if(menu_select){
    switch(menu_select){
    case S1:
      settings();
      break;
    case S2:
      program();
      break;
    case S3:
      //PowerSave();
      break;
    default: 
      break;
    }
  }
  else{
    lcd_BIG_mid();
    strcpy(display_line[FIRST_LINE],"---MAIN---");
    strcpy(display_line[THIRD_LINE],"---MENU---");
    strcpy(display_line[FOURTH_LINE],"          ");
    switch(menu){
      case S0:
        strcpy(display_line[SECOND_LINE],"<<---------");
        break;
      case S1:
        strcpy(display_line[SECOND_LINE]," SETTINGS ");
        break;
      case S2:
        strcpy(display_line[SECOND_LINE],"PROJECT 10");
        break;
      case S3:
        strcpy(display_line[SECOND_LINE], " PWR SAVE ");
        break;
     }
  }
  End_ADC();
}
     
void settings(void){
  lcd_4line();
  setting = ADC_Thumb >> COUNT_TEN;
  
  if(!action){
  
    strcpy(display_line[FIRST_LINE]," SETTINGS ");
   
    
    switch(setting){
    case S3:
      strcpy(display_line[SECOND_LINE], "White:    ");
      HEXtoBCD(white);
      strcpy(display_line[THIRD_LINE],"          ");
      strcpy(display_line[FOURTH_LINE],"          ");
      strcpy(display_line[THIRD_LINE], bcd_char);
      break;
    case S2:
      strcpy(display_line[SECOND_LINE], "Black:    ");
      HEXtoBCD(black);
      strcpy(display_line[THIRD_LINE],"          ");
      strcpy(display_line[FOURTH_LINE],"          ");
      strcpy(display_line[THIRD_LINE], bcd_char);
      break;    
    case S1:
      strcpy(display_line[SECOND_LINE], "Network: ");
      strcpy(display_line[THIRD_LINE], SSID);
      for(int i=RESET; i<COUNT_ELEVEN;i++){
        display_line[FOURTH_LINE][i] = IP[(i+scroll)%SMALL_RING_SIZE];
      }
      display_line[FOURTH_LINE][COUNT_TEN] = '\0';
      break;
    case S0:
      strcpy(display_line[SECOND_LINE], " Read ADC ");
      displayADC(THIRD_LINE);
      strcpy(display_line[FOURTH_LINE],"          ");
      break;
    default: break;
    }
  }
  else{
    End_ADC();
    switch(action){
    case S3:
      white = RESET;
      calibrateWhite();
      break;
    case S2:
      black = RESET;
      calibrateBlack();
      //Configure Black
      break;
    case S1:
      //Network State = New
      break;
    case S0:
      //Reset Module
      break;
    default: break;
    }
  }
}
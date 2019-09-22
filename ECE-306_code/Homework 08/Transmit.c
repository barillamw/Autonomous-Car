

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>
#include  <stdio.h>
#include  <stdlib.h>

#define NEW                           ('n')
#define UPDATE                        ('u')
#define DISPLAY                       ('d')
#define WAIT                          ('w')
#define TCP                           ('t')
#define MIDPOINT                        (4)

unsigned char ncsu[COUNT_ELEVEN] = " NCSU  #1 ";
extern char display_line[FOURTH][COUNT_ELEVEN];
char Text[COUNT_ELEVEN];
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern char IOTcommand[SMALL_RING_SIZE];





void out_character_A0(char character){
  while(!(UCA0IFG & UCTXIFG));
    if(character != '\0') UCA0TXBUF = character;
}

void out_character_A1 (char character){
  while(!(UCA1IFG & UCTXIFG));
    if(character != '\0') UCA1TXBUF = character;
}

void Transmit_Text_A1(void){
  int i;
  for(i=RESET; i<COUNT_ELEVEN; i++){
   //if(Text[i] != RESET)
    out_character_A1(Text[i]);
  }
}

void display_Text_A0(void){
  int i;
  for(i=RESET; i<=COUNT_ELEVEN; i++){
    Text[i] = IOT_Char_Rx[i];
    display_line[SECOND_LINE][i] = Text[i];
    Text[CHARA] = '\0';
  }

}

void display_Text_A1(void){
  int i;
  for(i=RESET; i<=COUNT_ELEVEN; i++){
    Text[i] = USB_Char_Rx[i];
    display_line[SECOND_LINE][i] = Text[i];
    Text[CHARA] = '\0';
  }

}

void clear(void){
  int i;
  for(i=RESET; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = RESET;
    IOT_Char_Rx[i] = RESET;
  }
}

void Store_Text_A1(void){
  int i;
  for(i=RESET; i<=COUNT_ELEVEN; i++){
    Text[i] = USB_Char_Rx[i];
  }
}

void Transmit_Test_A1(void){
  int i;
  for (i=RESET; i<=COUNT_ELEVEN; i++){
    out_character_A1(ncsu[i]);
  }
}

void Transmit_Command_A0(void){
  int i;
  for(i=RESET; i<SMALL_RING_SIZE; i++){
    out_character_A0(IOTcommand[i]);
  }
}
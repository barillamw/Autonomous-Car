

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

extern unsigned int UCA1_index;
unsigned char ncsu[COUNT_ELEVEN] = " NCSU  #1 ";
unsigned char test_Baud[SMALL_RING_SIZE] = "UUUUUUUUUUUUUUU";
unsigned char Send_Text[COUNT_ELEVEN] = "          ";
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern char display_line[FOURTH][COUNT_ELEVEN];
extern volatile unsigned char display_changed;

void out_character_A0(char character){
  while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = character;
}

void out_character_A1 (char character){
  while(!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = character;
}

void Transmit_NCSU_A1(void){
  int i;
  for(i=RESET; i<COUNT_ELEVEN; i++){
    out_character_A1(ncsu[i]);
  }
}
void Transmit_Test_A1(void){
  int i;
  for(i=RESET; i<COUNT_ELEVEN; i++){
    out_character_A1(test_Baud[i]);
  }
}

void Recieved_Text(void){
  int i;
  for(i=RESET; i<COUNT_ELEVEN; i++){
    Send_Text[i] = USB_Char_Rx[i];
    display_line[FIRST_LINE][i] = Send_Text[i];
    //USB_Char_Rx[i] = RESET;
  }
  display_changed = HIGH;
}

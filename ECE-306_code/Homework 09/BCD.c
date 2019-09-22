// ------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to BCD for display on an LCD or monitor
//
// ------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

char bcd_char [CHAR_LENGTH];

void HEXtoBCD (int hex_value){
  int value=RESET;
  bcd_char [CHAR0] = '0';
  bcd_char [CHAR1] = '0';
  bcd_char [CHAR2] = '0';  
  bcd_char [CHAR3] = '0';
  
  while ( hex_value > NINENINENINE){
    hex_value = hex_value - THOUSANDS ;
    value++;
    bcd_char [CHAR0] = ASCII_SHIFT + value;
  }
  value = RESET;
  while ( hex_value > NINENINE){
    hex_value = hex_value -HUNDREDS;
    value++;
    bcd_char [CHAR1] = ASCII_SHIFT + value;
  }
  value = RESET;
    while ( hex_value > NINE){
    hex_value = hex_value -TENS;
    value++;
    bcd_char [CHAR2] = ASCII_SHIFT + value;
  }
  bcd_char [CHAR3] = ASCII_SHIFT + hex_value ;
}
//******************************************************************************
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to BCD for display on an LCD or monitor
//
// ------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

char adc_char [CHAR_LENGTH];

void HEXtoBCD (int hex_value){
  int value=RESET;
  adc_char [FIRST_CHAR] = '0';
  
  while ( hex_value > NINENINENINE){
    hex_value = hex_value - THOUSANDS ;
    value++;
    adc_char [FIRST_CHAR] = ASCII_SHIFT + value;
  }
  value = RESET;
  while ( hex_value > NINENINE){
    hex_value = hex_value -HUNDREDS;
    value++;
    adc_char [SECOND_CHAR] = ASCII_SHIFT + value;
  }
  value = RESET;
    while ( hex_value > NINE){
    hex_value = hex_value -TENS;
    value++;
    adc_char [THIRD_CHAR] = ASCII_SHIFT + value;
  }
  adc_char [FOURTH_CHAR] = ASCII_SHIFT + hex_value ;
}
//******************************************************************************
// ------------------------------------------------------------------------------
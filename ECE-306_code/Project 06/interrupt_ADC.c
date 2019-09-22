//------------------------------------------------------------------------------
//
//  Description: This file contains the interrupt function for the ADC 
//  
//
//  Michael Barilla
//  Mar 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

unsigned int channel;
unsigned int V_Detect_R;
unsigned int V_Detect_L;
unsigned int ADC_Thumb;


#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
      break;
    case ADCIV_ADCOVIFG:        //When a conversion result is written to the ADCMEM0
                                // before its previosu conversion result was read.
      break;
    case ADCIV_ADCTOVIFG:       //ADC conversion-time overflow
      break;
    case ADCIV_ADCHIIFG:        //Window comparator interrupt flags
      break;
    case ADCIV_ADCLOIFG:        //Window comparator interrupt flag
      break;
    case ADCIV_ADCINIFG:        //Window comparator interrupt flag
      break;
    case ADCIV_ADCIFG:          //ADCMEM0 memory register with the convesion result
      ADCCTL0 &= ~ADCENC;
      switch(channel++){
        case THUMB:
          ADC_Thumb = ADCMEM0;          //Capture Thumb ADC Value
          ADCMCTL0 &= ~ADCINCH_5;        //Set In Channel from 5 to 2
          ADCMCTL0 |= ADCINCH_2;
          break;
        case LDET:
          V_Detect_L = ADCMEM0;         //Capture VDETL ADC Value
          ADCMCTL0 &= ~ADCINCH_2;        //Set In Channel from 2 to 3
          ADCMCTL0 |= ADCINCH_3;
          break;
        case RDET:
          V_Detect_R = ADCMEM0;         //Capture VDETR ADC Value
          ADCMCTL0 &= ~ADCINCH_3;        //Set In Channel from 3 to 5
          ADCMCTL0 |= ADCINCH_5;
          channel = THUMB;              //Reset Channel
          break;
        default:
          break; 
      }
      ADCCTL0 |= ADCENC;
      ADCCTL0 |= ADCSC;
      
      break;
    default:
      break;
  }
}

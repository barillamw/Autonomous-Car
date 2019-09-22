//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to initiate the ADC Registers 
//  to set pins 2, 3, and 5 to measure the V_Detect_L, V_Detece_R, and V_Thumb 
//  respectively.
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

extern volatile unsigned char display_changed;
extern char display_line[FOURTH][COUNT_ELEVEN];



void Init_ADC(void){
  //----------------------------------------------------------------------------
  //    V_DETECT_L       (0x04) // Pin 2 A2
  //    V_DETECT_R       (0x08) // Pin 3 A3
  //    V_THUMB          (0x20) // Pin 5 A5
  //----------------------------------------------------------------------------
  
  //ADCCTL0 Register
    ADCCTL0  = RESET;     //Reset
    ADCCTL0 |= ADCSHT_2;        //16 ADC clocks
    ADCCTL0 |= ADCMSC;          //MSC
    ADCCTL0 |= ADCON;           //ADC ON
    
  //ADCCTL1 Register
    ADCCTL1  = RESET;     //Reset
    ADCCTL1 |= ADCSHS_0;        //00b = ADCSC bit
    ADCCTL1 |= ADCSHP;          //ADC sample-and-hold SAMPCON signal from sampling timer.
    ADCCTL1 &= ~ADCISSH;        //ADC invert signal sample - and - hold.
    ADCCTL1 |= ADCDIV_0;        //ADC clock divider -000b = Divide by 1
    ADCCTL1 |= ADCSSEL_0;       //ADC clock MODCLK
    ADCCTL1 |= ADCCONSEQ_0;     //ADC conversion sequence 00b = Single -channel single channel single -conversionconversion conversion
  //ADCCTL1 & ADCBUSY identifies a conversion is in process 
  
  //ADCCTL2 Register 
    ADCCTL2 = RESET;      //Reset
    ADCCTL2 |= ADCPDIV0;        //00b = Pre -divide by 1divide by 1 divide by 1 divide by 1
    ADCCTL2 |= ADCRES_2;        //ADC resolution 10b = 12 bit (14 clock cycle conversion time)
    ADCCTL2 &= ~ADCDF;          //ADC data read-back format 0b = Binary unsigned. back format 0b = Binary unsigned.
    ADCCTL2 &= ~ADCSR;          //ADC sampling rate 0b = buffer supports up to 200 ksps
    
  //ADCMCTL0 Register           
    ADCMCTL0 |= ADCSREF_0;      //VREF - 000b = {VR+ = AVCC and VR- = AVSS}
    ADCMCTL0 |= ADCINCH_5;      //V_THUMB (0x20) Pin 5 A5
    
    ADCIE &= ~ADCIE0;            // disable ADC conv complete interrupt 
    ADCCTL0 &= ~ADCENC;          // ADC enable conversion. 
    ADCCTL0 &= ~ADCSC;           // ADC start conversion. 
}

void Begin_ADC(void){
  IR_LED_ON;                    //Turn on IR LED
  //strcpy(display_line[FIRST_LINE], " ADC ON  ");
  display_changed = HIGH;       //Change Display
  ADCIE |= ADCIE0;              //enable ADC conv complete interrupt
  ADCCTL0 |= ADCENC;            //ADC enable conversion
  ADCCTL0 |= ADCSC;             //ADC start conversion.
}

void End_ADC(void){
  IR_LED_OFF;                   //Turn Off IR LED
  //strcpy(display_line[FIRST_LINE], "  ADC OFF  ");
  display_changed = HIGH;       //Change Display
  ADCIE &= ~ADCIE0;             //disable ADC conv complete interrupt
  ADCCTL0 &= ~ADCENC;           //ADC enable conversion
  ADCCTL0 &= ~ADCSC;            //ADC Start conversion.
}



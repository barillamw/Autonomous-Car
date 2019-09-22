//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to initiate the Serial 
//      port for USB at various Baud Rates
//      A0 - 115,200
//      A1 - 460,800
//  
//
//  Michael Barilla
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

//Global Variables
volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE];

volatile unsigned int iot_rx_ring_wr;
volatile unsigned int iot_rx_ring_rd;
volatile char IOT_Char_Rx[SMALL_RING_SIZE];
volatile char IOT_Char_Tx[SMALL_RING_SIZE];

unsigned int freq = K115;

extern char display_line[FOURTH][COUNT_ELEVEN];
extern volatile unsigned char display_changed;

unsigned int transmit;

void Init_Serial(void){
  Init_Serial_UCA0();
  Init_Serial_UCA1();
}

void Init_Serial_UCA0(void){            //Serial Port for IOT
  int i;
  for(i=BEGINNING; i<SMALL_RING_SIZE; i++){
    IOT_Char_Rx[i] = RESET;
  }
  iot_rx_ring_wr = BEGINNING;
  iot_rx_ring_rd = BEGINNING;
  
  //for(i=BEGINNING; i<LARGE_RING_SIZE; i++){
    //IOT_Char_Tx[i] = RESET;
  
  //iot_tx_ring_wr = BEGINNING;
  //iot_tx_ring_rd = BEGINNING;
  
  //Configure UART 0
  UCA0CTLW0 = RESET;            //use word register
  UCA0CTLW0 |= UCSWRST;         //Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK;   //Set SMCLK as fBRCLK
  UCA0BRW = COUNT_FOUR;
  //UCA0MCTLW = 0x55 UCFX 5  UCOS16 1
  UCA0MCTLW = LO_FREQ;
  

  transmit = LOW;
  UCA0CTLW0 &= ~UCSWRST;
  UCA0IE |= UCRXIE;
}

void Init_Serial_UCA1(void){            //Serial Port for USB
  int i;
  for(i=BEGINNING; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = RESET;
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;
  
  for(i=BEGINNING; i<LARGE_RING_SIZE; i++){
    USB_Char_Tx[i] = RESET;
  }
  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;
  
  //Configure UART 1
  UCA1CTLW0 = RESET;            //use word register
  UCA1CTLW0 |= UCSWRST;         //Set Software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK;   //Set SMCLK as fBRCLK

  UCA1BRW = COUNT_FOUR;
  UCA1MCTLW = LO_FREQ;
  


  UCA1CTLW0 &= ~UCSWRST;
  UCA1IE |= UCRXIE;
}

void Begin_Serial(void){
    UCA1CTLW0 &= ~UCSWRST;
    UCA1IE |= UCRXIE;
    
    //strcpy(display_line[FOURTH_LINE],"SERIAL ON ");
    
    UCA0CTLW0 &= ~UCSWRST;
    UCA0IE |= UCRXIE;
}

void End_Serial(void){
  UCA1CTLW0 |= UCSWRST;
  UCA1IE &= ~UCRXIE;
  
  //strcpy(display_line[FOURTH_LINE],"SERIAL OFF");
    
  UCA0CTLW0 |= UCSWRST;
  UCA0IE &= ~UCRXIE;
}

void Configure_Serial(void){  
  switch(freq){
    case K115:                    //frequency 115.2K
      UCA0BRW = COUNT_FOUR;
      //UCA1MCTLW = 0x55 UCFX 5  UCOS16 1
      UCA0MCTLW = LO_FREQ;
      //UCA1BRW = COUNT_FOUR;
      //UCA1MCTLW = LO_FREQ;
      //strcpy(display_line[THIRD_LINE],"BR: 115.2k");
      break;
    case K460:                    //frequency 460.8K
      UCA0BRW = COUNT_ONE;
      //UCA1MCTLW = 0x4A  UCFX 0  UCOS16 1
      UCA0MCTLW = HI_FREQ;
      UCA1BRW = COUNT_ONE;
      UCA1MCTLW = HI_FREQ;
      //strcpy(display_line[THIRD_LINE],"BR: 460.8k");
      break;
  case K96:
      UCA0BRW = 52;
      //UCA1MCTLW = 0x49  UCFX 1  UCOS16 1
      UCA0MCTLW = COMPUTER;
      //UCA1BRW = 52;
      //UCA1MCTLW = COMPUTER;
      //strcpy(display_line[THIRD_LINE],"BR: 9600");
    default:
      break;
  }
}
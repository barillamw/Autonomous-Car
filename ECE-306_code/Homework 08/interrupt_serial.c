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

//Global Varibles
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];
extern volatile unsigned int iot_rx_ring_wr;
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Tx[SMALL_RING_SIZE];
unsigned int UCA1_index;
unsigned int UCA0_index;
unsigned int lineFinished;
unsigned int lineStart;

//------------------------------------------------------------------------------

/*#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA0IV,0x08)){
  case 0:                       //vector 0 - no interrupt
    break;
  case 2:                       //Vector 2 - RXIFG
    temp = iot_rx_ring_wr++;
    IOT_Char_Rx[temp] = UCA0RXBUF;      //RX -> IOT_Char_Rx character
    UCA0RXBUF = IOT_Char_Rx[temp];
    if (iot_rx_ring_wr >= (sizeof(USB_Char_Rx))){
      usb_rx_ring_wr = BEGINNING;
    }
    break;
  case 4:
    switch(UCA0_index++){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      UCA0TXBUF = IOT_Char_Tx[UCA0_index];
      break;
    case 9:
      UCA0TXBUF = 0x0D;
      break;
    case 10:
      UCA0TXBUF = 0x0A;
      break;
    default:
      UCA0IE &= ~UCTXIE;                //disable TX interrupt
      break;
    }
    break;
  }
}*/

#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
unsigned int temp;
  
  switch(__even_in_range(UCA1IV, 0x08)){
    case 0:
      break;
    case 2:
      temp = usb_rx_ring_wr++;
      USB_Char_Rx[temp] = UCA1RXBUF;        //RX -> USB_Char_Rx character
      if(USB_Char_Rx[temp] != '\0') lineStart = HIGH;
      if(USB_Char_Rx[temp] == '\0' && lineStart == HIGH){
        lineStart = LOW;
        lineFinished = HIGH;
        usb_rx_ring_wr = BEGINNING;
      }
      if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
        usb_rx_ring_wr = BEGINNING;

      }
      break;
    case 4:
      /*switch(UCA1_index++){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
          UCA1TXBUF = USB_Char_Tx[UCA1_index];
          break;
        case 9:
          //UCA1TXBUF = 0x0D;
          break;
        case 10:
          //UCA1TXBUF = 0x0A;
          break;
        default:
          //UCA1IE &= ~UCTXIE;
          UCA1IFG &= ~UCTXIFG;
          break;
      }
      break;*/
    default: break;
  }
}
  
      

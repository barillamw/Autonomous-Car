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
extern unsigned int transmit;
extern unsigned int send;
extern unsigned int startPos;
char character;
char IOTcharacter;

unsigned int ipSearch;
unsigned int updateStatus;
unsigned int collect;
char IOT_All_Char[SMALL_RING_SIZE];
unsigned int all_char;
extern unsigned int updateIP;
unsigned int location = RESET;
extern char SSID[COUNT_ELEVEN];
extern char IP[SMALL_RING_SIZE];
unsigned int findSSID;
unsigned int findIP;
unsigned int flagSSID;
unsigned int flagIP;

extern char statusNTWK;
extern char driveCommand[SMALL_RING_SIZE];
unsigned int driveCommandCount;
unsigned int newDriveCommand;
extern unsigned int readyDrive;





//------------------------------------------------------------------------------

#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  
  switch(__even_in_range(UCA0IV, UCA0TXD)){
    case S0:
      break;
    case S2:
      IOTcharacter = UCA0RXBUF;
      UCA1TXBUF = IOTcharacter; 
      IOT_All_Char[all_char++%SMALL_RING_SIZE] = IOTcharacter;
      /*if(lineStart){
         IOT_Char_Rx[iot_rx_ring_wr] = IOTcharacter;
          iot_rx_ring_wr++;
          if(IOTcharacter == '\r'){
            lineStart = LOW;
            lineFinished = HIGH;
          }
      }*/
      if(strstr(IOT_All_Char, "SS\r\n")&&(statusNTWK != NEW)) 
        statusNTWK = NEW;
      if(statusNTWK == UPDATE){
        if(findSSID){
          if(IOTcharacter == '"'){
            findSSID = LOW;
            location = RESET;
            flagSSID = HIGH;
          }
          else{
            SSID[location] = IOTcharacter;
            location++;
            if(location == sizeof(SSID)){
              findSSID = LOW;
              location = RESET;
              flagSSID = HIGH;
            }
          }
        }
        else if(IOTcharacter == '"' && !flagSSID) findSSID = HIGH;
        else if(findIP){
          if(IOTcharacter == ' '){
            findIP = LOW;
            location = RESET;
            statusNTWK = DISPLAY;
          }
          else if(IOTcharacter == '=');
          else{
            IP[location] = IOTcharacter;
            location++;
            if(location == sizeof(IP)){
              findIP = LOW;
              location = RESET;
              statusNTWK = DISPLAY;
            }
          }
        }
        else if(strstr(IOT_All_Char,"r=")) 
          findIP = HIGH;
      }
      
      if(newDriveCommand){
        if(IOTcharacter == ';') {
          readyDrive = HIGH;
          newDriveCommand = LOW;
        }
        else {
          driveCommand[driveCommandCount%SMALL_RING_SIZE] = IOTcharacter;
          driveCommandCount++;
        }
      }
      else if(IOTcharacter == '~'){
            newDriveCommand = HIGH;
            driveCommandCount = RESET;
      }

      if (iot_rx_ring_wr >= (sizeof(IOT_Char_Rx))){
        iot_rx_ring_wr = BEGINNING;
      }
      
      break;
    case S4:
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
          UCA1TXBUF = 0x0D;
          break;
        case 10:
          UCA1TXBUF = 0x0A;
          break;
        default:
          UCA1IE &= ~UCTXIE;
          break;
      }
      break;*/
    default: break;
  }
}

#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  transmit = HIGH;
  send = LOW;
  switch(__even_in_range(UCA1IV, UCA1TXD)){
    case S0:
      break;
    case S2:
      character = UCA1RXBUF;
      
      if(lineStart){
         USB_Char_Rx[usb_rx_ring_wr] = character;
          usb_rx_ring_wr++;
          if(character == '\r'){
            lineStart = LOW;
            lineFinished = HIGH;
          }
      }
      else if(character == '^'){
        lineStart = HIGH;
        usb_rx_ring_wr = RESET;
        USB_Char_Rx[usb_rx_ring_wr] = character;
        usb_rx_ring_wr++;
      }
      else UCA0TXBUF = character; 
      if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
        usb_rx_ring_wr = BEGINNING;
      }
      break;
    case S4:
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
          UCA1TXBUF = 0x0D;
          break;
        case 10:
          UCA1TXBUF = 0x0A;
          break;
        default:
          UCA1IE &= ~UCTXIE;
          break;
      }
      break;*/
    default: break;
  }
}
   

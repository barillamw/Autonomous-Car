//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to update the network 
//   and maintain it during the code operation
//  
//
//  Michael Barilla
//  Apr 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>
#include  <stdio.h>
#include  <stdlib.h>


char statusNTWK;
char IOTcommand[SMALL_RING_SIZE];
char IP[SMALL_RING_SIZE] = "                ";
char SSID[COUNT_ELEVEN] = "          ";

extern char display_line[FOURTH][COUNT_ELEVEN];

unsigned int sendPing = HIGH;
char PING[LARGE_RING_SIZE] = "AT+PING=www.pixar.com,3\r";

int dotCount = RESET;
int firstDot=RESET;
int secondDot=RESET;
int thirdDot=RESET;
int offset1 = RESET;
int offset3 = RESET;
int offset4 = RESET;

void network(void){
    //IOT_Reset();
    updateNetwork();
    ping();
}

void updateNetwork(void){
  int i = RESET;

  
  
  switch(statusNTWK){
  case NEW:
      statusNTWK = UPDATE;
      strcpy(IOTcommand,"AT+NSTAT=?\r");
      Transmit_Command_A0();
      break;    
  case DISPLAY:
    for(i=COUNT_ELEVEN; i > RESET; i--){
      if(SSID[i] == '\0') offset1++;
    }
    SSID[COUNT_TEN] = '\0';
    IP[COUNT_FIFTEEN] = '\0';
    
    dotCount = RESET;
    for(i=RESET; i<sizeof(IP); i++){
      if(IP[i] == '.') dotCount++;
      if(dotCount == FIRST && !firstDot) firstDot = i;
      else if(dotCount == SECOND && !secondDot) secondDot = i;
      else if(dotCount == THIRD && !thirdDot) thirdDot = i;
    }
    offset3 = MIDPOINT-firstDot;
    offset4 = thirdDot - MIDPOINT;
    
    /*strcpy(display_line[FIRST_LINE],"          ");
    strcpy(display_line[SECOND_LINE],"IP address");
    strcpy(display_line[THIRD_LINE],"          ");
    strcpy(display_line[FOURTH_LINE],"          ");
    
    for(i=RESET; i<COUNT_ELEVEN; i++){
      display_line[FIRST_LINE][i+(offset1>>FIRST)] = SSID[i];
    }
    for(i=RESET; i<SMALL_RING_SIZE; i++){
      if(i<secondDot) display_line[THIRD_LINE][i+offset3] = IP[i];
      if(i>secondDot) display_line[FOURTH_LINE][i-offset4] = IP[i];
    }*/
    statusNTWK = TCP;
  case TCP:
    strcpy(IOTcommand, "AT+NSTCP=7898,1\r");
    Transmit_Command_A0();
    statusNTWK=WAIT;
    GREEN_LED_ON;
    
    
  default: break;
  }
}

void ping(void){
  if(sendPing && (statusNTWK == WAIT)){
    sendPing = LOW;
      for(int i=RESET; i<LARGE_RING_SIZE; i++)
        out_character_A0(PING[i]);
  }
}
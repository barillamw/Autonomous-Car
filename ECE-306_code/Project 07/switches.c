#include  "functions.h"
#include  "msp430.h"
#include "macros.h"


extern unsigned int time_change2;
extern unsigned char event;
extern unsigned char shape;

void Switches_Process(void){
  //---------------------------------------------------------------------------
  if(time_change2){
    time_change2 = LOW;
    if (!(P4IN & SW1)){
      event = shape;
      switch(shape){
        case STRAIGHT:
          shape = CIRCLE;
          break;
        case CIRCLE:
          shape = FIG_EIGHT;
          break;
        case FIG_EIGHT:
          shape = TRIANGLE;
          break;
        case TRIANGLE:
          shape = STRAIGHT;
          break;
        default: break;

      /*display_line[1] = "NCSU";
      posL1 = 3;
      display_line [2] = "WOLFAPACK";
      posL2 = 1;
      display_3 = "ECE306";
      posL3 = 2;
      display_4 = "M Barilla";
      posL4 = 1;*/
    }
    if (!(P2IN & SW2)){
      
      /*display_1 = "Embedded";
      posL1 = 1;
      display_2 = "Systems";
      posL2 = 2;
      dislay_3 = "Rock!";
      posL3 = 3;
      display_4 = "Go Pack!";
      posL4 = 1;*/
    }
  //---------------------------------------------------------------------------
    }
  }
}
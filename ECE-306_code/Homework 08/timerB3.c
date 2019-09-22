//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initializes the Time B3 timer
//      TB3.1 P6.0 R_FORWARD
//      TB3.2 P6.1 L_FORWARD
//      TB3.3 P6.2 R_REVERSE
//      TB3.4 P6.3 L_REVERSE
//
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "macros.h"
#include  "functions.h"

void Init_Timer_B3(void){
  TB3CTL = TBSSEL__SMCLK;                 //Source = SMCLK
  TB3CTL |= MC__UP;                       //Up Mode
  TB3CTL |= TBCLR;                        //Clear TAR

  TB3CCR0 = WHEEL_PERIOD;                 //PWM Period

  TB3CCTL1 = OUTMOD_7;                    //CCR1 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF;        //P6.0 Right Forward PWM duty cycle

  TB3CCTL2 = OUTMOD_7;                    //CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF;         //P6.1 Right Forward PWM duty cycle

  TB3CCTL3 = OUTMOD_7;                     //CCR3 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF;       //P6.2 Right Reverse PWM duty cycle

  TB3CCTL4 = OUTMOD_7;                    //CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF;          //P6.3 Left Reverse PWM duty cycle
}
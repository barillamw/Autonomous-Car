//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to initiate each of the ports 
//  on the MSP430.
//
//  Michael Barilla
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

void Init_Ports(){      //Calls the rest of the initalization functions
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_Port5();
  Init_Port6();
}
  
//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initalizes all of the pins on port 1
//      Pin 0 - RED LED output
//      Pin 1 - Unused SEEED Function Pin
//      Pin 2 - Voltage Detect Left ADC
//      Pin 3 - Voltage Detect Right ADC
//      Pin 4 - Unused SEEED Function Pin
//      Pin 5 - Voltage Thumb Function
//      Pin 6 - UCA0TXD Function
//      Pin 7 - UCA0RXD Function
//
//------------------------------------------------------------------------------
void Init_Port1() {     
  P1SEL1 = RESET;               //Set P1 Select 1 to Low
  P1SEL0 = RESET;               //Set P1 Select 0 to Low
  P1OUT = RESET;                //Set P1 Intial Value to Low
  P1DIR = FULL;                 //Set P1 Direction to Output
  P1REN = RESET;                //Set P1 Resistor Enable to Low
  
  P1SEL0 &= ~RED_LED;           //RED_LED GPIO operation (00)
  P1SEL1 &= ~RED_LED;           
  P1OUT &= ~RED_LED;            //Initial Value = 0 [OFF]
  P1DIR |= RED_LED;             //Direction = Output

  P1SEL0 |= A1_SEEED;            //A1_SEEED Function Operation (11)
  P1SEL1 |= A1_SEEED;            
  
  P1SEL0 |= V_DETECT_L;         //V_DETECT_L Function Operation (11)
  P1SEL1 |= V_DETECT_L;         
  
  P1SEL0 |= V_DETECT_R;         //V_DETECT_R Function Operation (11)
  P1SEL1 |= V_DETECT_R;         
  
  P1SEL0 |= A4_SEEED;           //A4_SEEED Function Operation (11)
  P1SEL1 |= A4_SEEED;           
  
  P1SEL0 |= V_THUMB;            //V_THUMB Function Operation (11)
  P1SEL1 |= V_THUMB;            
  
  P1SEL0 |= UCA0TXD;            //UCA0TXD Function Operation (01)
  P1SEL1 &= ~UCA0TXD;           
  
  P1SEL0 |= UCA0RXD;            //UCA0RXD Function Operation (01)
  P1SEL1 &= ~UCA0RXD;           
}

//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initalizes all of the pins on port 2
//      Pin 0 - Unused GPIO
//      Pin 1 - Unused GPIO
//      Pin 2 - Unused GPIO
//      Pin 3 - Pull up Switch 2
//      Pin 4 - Unused GPIO
//      Pin 5 - Unused GPIO
//      Pin 6 - Low Frequency Clock Out
//      Pin 7 - Low Frequency Clock In
//
//------------------------------------------------------------------------------
void Init_Port2(){ 
  P2SEL1 = RESET;               //Set P2 Select 1 to Low
  P2SEL0 = RESET;               //Set P2 Select 0 to Low
  P2OUT = RESET;                //Set P2 inital value to Low
  P2DIR = FULL;                 //Set P2 direction to output
  P2REN = RESET;                //Set P2 Resistor Enable to Low
  
  P2SEL0 &= ~P2_0;              //P2_0 GPIO operation (00)
  P2SEL1 &= ~P2_0;              
  P2DIR &= ~P2_0;               //Direction = input
  
  P2SEL0 &= ~P2_1;              //P2_1 GPIO operation (00)
  P2SEL1 &= ~P2_1;              
  P2DIR &= ~P2_1;               //Direction = input 
  
  P2SEL0 &= ~P2_2;              //P2_2 GPIO operation (00)
  P2SEL1 &= ~P2_2;              
  P2DIR &= ~P2_2;               //Direction = input
  
  P2SEL0 &= ~SW2;               //SW2 operation
  P2SEL1 &= ~SW2;               //SW2 operation
  P2DIR &= ~SW2;                //Direction = input
  P2OUT |= SW2;                 //Configure pullup resistor
  P2REN |= SW2;                 //Enable pullup resistor
  P2IES |= SW2;                 //SW2 Hi/Lo edge interrupt
  P2IFG &= ~SW2;                //Clear all SW2 inerrupt flags
  P2IE |= SW2;                  //SW2 interrupt enabled
  
  P2SEL0 &= ~P2_4;              //P2_4 GPIO operation (00)
  P2SEL1 &= ~P2_4;              
  P2DIR &= ~P2_4;               //Direction = input
  
  P2SEL0 &= ~P2_5;              //P2_5 GPIO operation (00)
  P2SEL1 &= ~P2_5;              
  P2DIR &= ~P2_5;               //Diretion = input
  
  P2SEL0 &= ~LFXOUT;            //LFXOUT Clock operation (10)
  P2SEL1 |= LFXOUT;             
  
  P2SEL0 &= ~LFXIN;             //LFXIN Clock operation (10)
  P2SEL1 |= LFXIN;              
 //-----------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initalizes all of the pins on port 3
//      Pin 0 - Test Probe Input
//      Pin 1 - OA20 Function
//      Pin 2 - OA2 Neg Function
//      Pin 3 - OA2 Pos Function
//      Pin 4 - SM Clock Output
//      Pin 5 - Unused GPIO
//      Pin 6 - IOT Link
//      Pin 7 - Unused GPIO
//
//------------------------------------------------------------------------------
void Init_Port3(){             
  P3SEL1 = RESET;               //Set P3 Select 1 to Low
  P3SEL0 = RESET;               //Set P3 Select 0 to Low
  P3OUT = RESET;                //Set P3 Initial Value to Low
  P3DIR = FULL;                 //Set P3 Direction to Output
  P3REN = RESET;                //Set P3 Resistor Enable to Low
  
  P3SEL0 &= ~TEST_PROBE;        //TEST_PROBE GPIO Operation (00)
  P3SEL1 &= ~TEST_PROBE;
  P3DIR |= TEST_PROBE;          //Direction = Output
  
  P3SEL0 |= OA20;               //Function Operation (11)
  P3SEL1 |= OA20;       
  
  P3SEL0 |= OA2N;               //Function Operation (11)
  P3SEL1 |= OA2N;       
  
  P3SEL0 |= OA2P;               //Function Operation (11)
  P3SEL1 |= OA2P;       
  
  P3SEL0 |= SMCLK_OUT;          //Function Operation (01)
  P3SEL1 &= ~SMCLK_OUT; 
  
  P3SEL0 &= ~P3_5;              //GPIO Operation (00)
  P3SEL1 &= ~P3_5;
  P3DIR &= ~P3_5;               //Sets Direction to Input

  P3SEL0 &= ~IOT_LINK;          //GPIO Operation (00)
  P3SEL1 &= ~IOT_LINK;  
  P3DIR &= ~IOT_LINK;           //Sets Direction to Input
  
  P3SEL0 &= ~P3_7;              //GPIO Operation (00)
  P3SEL1 &= ~P3_7;      
  P3DIR &= ~IOT_LINK;           //Sets Direction to Input
}

//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initalizes all of the pins on port 4
//      Pin 0 - Reset the LCD 
//      Pin 1 - Pull up Switch 1
//      Pin 2 - UCA1RXD Function
//      Pin 3 - UCA1TXD Function
//      Pin 4 - UCB1_CS_LCD GPIO Pin
//      Pin 5 - UCB1CLK Function
//      Pin 6 - UCB1SIMO Function
//      Pin 7 - UCB1SOMI Function
//
//------------------------------------------------------------------------------
void Init_Port4(){             
  P4SEL0 = RESET;               //Set P4 Select 0 to Low
  P4SEL1 = RESET;               //Set P4 Select 1 to Low
  P4OUT = RESET;                //Set P4 Inital Value to Low
  P4DIR = FULL;                 //Set P4 Direction to Output
  P4REN = RESET;                //Set P Resistor Enable to Low
  
  P4SEL0 &= ~RESET_LCD;         //RESET_LCD GPIO Operation (00)
  P4SEL1 &= ~RESET_LCD;
  P4OUT &= ~RESET_LCD;          //Initial Value to 0
  P4DIR |= RESET_LCD;           //Direction = Input
  
  P4SEL0 &= ~SW1;               //SW1 operation (00)
  P4SEL1 &= ~SW1;      
  P4DIR &= ~SW1;                //Direction = input
  P4OUT |= SW1;                 //Configure pullup resistor
  P4REN |= SW1;                 //Enable pullup resistor
  P4IES |= SW1;                 //SW1 Hi/Lo edge interrupt
  P4IFG &= ~SW1;                //Clear all Sw1 inerrupt flags
  P4IE |= SW1;                  //Sw1 interrupt enabled
  
  P4SEL0 |= UCA1RXD;            //UCA1RXD Function Operation (01)
  P4SEL1 &= ~UCA1RXD;   
  
  P4SEL0 |= UCA1TXD;            //UCA1TXD Function Operation (01)
  P4SEL1 &= ~UCA1TXD;  
  
  P4SEL0 &= ~UCB1_CS_LCD;       //GPIO Operation (00)
  P4SEL1 &= ~UCB1_CS_LCD;
  P4OUT &= ~UCB1_CS_LCD;        //Initial Value = 0
  P4DIR |= UCB1_CS_LCD;         //Direction = Input
  
  P4SEL0 |= UCB1CLK;            //UCB1CLK Function Operation (01)
  P4SEL1 &= ~UCB1CLK;   
  
  P4SEL0 |= UCB1SIMO;            //UCB1SIMO Function Operation (01)
  P4SEL1 &= ~UCB1SIMO;           
  
  P4SEL0 |= UCB1SOMI;           //UCB1SOMI Function Operation (01)
  P4SEL1 &= ~UCB1SOMI;  
}

//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initalizes all of the pins on port 5
//      Pin 0 - Reset IOT
//      Pin 1 - Unused GPIO
//      Pin 2 - IOT Program Selector
//      Pin 3 - IOT Program Mode
//      Pin 4 - InfraRed LED
//
//------------------------------------------------------------------------------
void Init_Port5(){ 
  P5SEL0 = RESET;               //Set P5 Select 0 to Low
  P5SEL1 = RESET;               //Set P5 Select 1 to Low
  P5OUT = RESET;                //Set P5 Initial Value Low
  P5DIR = FULL;                 //Set P5 Direction to Output
  P5REN = RESET;                //SET P5 Resistor Enable to Low
  
  P5SEL0 &= ~IOT_RESET;         //IOT_RESET GPIO Operation (00)
  P5SEL1 &= ~IOT_RESET;         
  P5OUT &= ~IOT_RESET;          //Initial Value = 0
  P5DIR |= IOT_RESET;           //Direction = Output
  
  P5SEL0 &= ~P5_1;              //P5_1 GPIO Operation (00)
  P5SEL1 &= ~P5_1;              
  P5DIR &= ~P5_1;               //Direction = Input
  
  P5SEL0 &= ~IOT_PROG_SEL;      //IOT_PROG_SEL GPIO Operation (00)
  P5SEL1 &= ~IOT_PROG_SEL;      
  P5DIR &= ~IOT_PROG_SEL;       //Direction = Input
  
  P5SEL0 &= ~IOT_PROG_MODE;      //IOT_PROG_MODE GPIO Operation (00)
  P5SEL1 &= ~IOT_PROG_MODE;
  P5DIR &= ~IOT_PROG_MODE;      //Direction = Input
  
  P5SEL0 &= ~IR_LED;            //IR_LED mode GPIO operation (00)
  P5SEL1 &= ~IR_LED;
  P5OUT &= ~IR_LED;             //Initial value = LOW
  P5DIR |= IR_LED;              //Direction = Output
  
  
  
}

//------------------------------------------------------------------------------
//
//  Michael Barilla
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initalizes all of the pins on port 5
//      Pin 0 - Right Motor Forward Output
//      Pin 1 - Left Motor Forward Output
//      Pin 2 - Right Motor Reverse Output 
//      Pin 3 - Left Motor Reverse Output
//      Pin 4 - LCD Backlight
//      Pin 5 - Unsued GPIO
//      Pin 6 - Green LED output
//
//------------------------------------------------------------------------------
void Init_Port6(){ 
  P6SEL0 = RESET;               //Set P6 Select 0 to Low
  P6SEL1 = RESET;               //Set P6 Select 1 to Low
  P6OUT = RESET;                //Set P6 Initial Value Low
  P6DIR = FULL;                 //Set P6 Direction to Output
  P6REN = RESET;                //SET P6 Resistor Enable to Low
  
  P6SEL0 |= R_FORWARD;         //R_FORWARD Function Operation (01)
  P6SEL1 &=~ R_FORWARD;
  //P6OUT &= ~R_FORWARD;          //Initial Value = 0
  P6DIR |= R_FORWARD;           //Direction = Output
  
  P6SEL0 |= L_FORWARD;         //L_FORWARD Function Operation (01)
  P6SEL1 &= ~L_FORWARD;         
  //P6OUT &= ~L_FORWARD;          //Initial Value = 0
  P6DIR |= L_FORWARD;           //Direction = Output
  
  P6SEL0 |= R_REVERSE;         //R_REVERSE Function Operation (01)
  P6SEL1 &= ~R_REVERSE;
  //P6OUT &= ~R_REVERSE;          //Initial Value = 0
  P6DIR |= R_REVERSE;           //Direction 1
  
  P6SEL0 |= L_REVERSE;         //L_REVERSE Function Operation (01)
  P6SEL1 &= ~L_REVERSE;         
  //P6OUT &= ~L_REVERSE;          //Initial Value = 0
  P6DIR |= L_REVERSE;           //Direction 1
  
  P6SEL0 &= ~LCD_BACKLITE;      //LCD_BACKLITE GPIO Operation (00)
  P6SEL1 &= ~LCD_BACKLITE;
  P6OUT &= ~LCD_BACKLITE;       //Initial Value = 1
  P6DIR |= LCD_BACKLITE;        //Direction = Output
  
  P6SEL0 &= ~P6_5;              //P6_5 GPIO Operation (00)
  P6SEL1 &= ~P6_5;              
  P6DIR &= ~P6_5;               //Direction = Output
  
  P6SEL0 &= ~GRN_LED;           //GRN_LED GPIO Operation (00)
  P6SEL1 &= ~GRN_LED;
  P6OUT &= ~GRN_LED;            //Initial Value = 0
  P6DIR |= GRN_LED;             //Direction Output  
  
}


void wheelControl(int Direction){
  if (Direction){
    //GPIO
      P6SEL0 &= ~ R_FORWARD;         //R_FORWARD Function Operation (00)
      P6SEL1 &=~ R_FORWARD;
      P6OUT &= ~R_FORWARD;          //Initial Value = 0
      P6DIR |= R_FORWARD;           //Direction = Output
      
      P6SEL0 &= ~ L_FORWARD;         //L_FORWARD Function Operation (00)
      P6SEL1 &= ~L_FORWARD;         
      P6OUT &= ~L_FORWARD;          //Initial Value = 0
      P6DIR |= L_FORWARD;           //Direction = Output
      
      P6SEL0 &= ~ R_REVERSE;         //R_REVERSE Function Operation (00)
      P6SEL1 &= ~R_REVERSE;
      P6OUT &= ~R_REVERSE;          //Initial Value = 0
      P6DIR |= R_REVERSE;           //Direction 1
      
      P6SEL0 &= ~L_REVERSE;         //L_REVERSE Function Operation (00)
      P6SEL1 &= ~L_REVERSE;         
      P6OUT &= ~L_REVERSE;          //Initial Value = 0
      P6DIR |= L_REVERSE;           //Direction 1
  }
  else {
    //PWM
      P6SEL0 |= R_FORWARD;         //R_FORWARD Function Operation (01)
      P6SEL1 &=~ R_FORWARD;
      P6OUT &= ~R_FORWARD;          //Initial Value = 0
      P6DIR |= R_FORWARD;           //Direction = Output
      
      P6SEL0 |= L_FORWARD;         //L_FORWARD Function Operation (01)
      P6SEL1 &= ~L_FORWARD;         
      P6OUT &= ~L_FORWARD;          //Initial Value = 0
      P6DIR |= L_FORWARD;           //Direction = Output
      
      P6SEL0 |= R_REVERSE;         //R_REVERSE Function Operation (01)
      P6SEL1 &= ~R_REVERSE;
      P6OUT &= ~R_REVERSE;          //Initial Value = 0
      P6DIR |= R_REVERSE;           //Direction 1
      
      P6SEL0 |= L_REVERSE;         //L_REVERSE Function Operation (01)
      P6SEL1 &= ~L_REVERSE;         
      P6OUT &= ~L_REVERSE;          //Initial Value = 0
      P6DIR |= L_REVERSE;           //Direction 1
  }










      
}  
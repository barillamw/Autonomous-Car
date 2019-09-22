#ifndef MACROS_H
#define MACROS_H

#define RED_LED_ON       (P1OUT |= RED_LED)
#define RED_LED_OFF     (P1OUT &= ~RED_LED)
#define GREEN_LED_ON     (P6OUT |= GRN_LED)
#define GREEN_LED_OFF   (P6OUT &= ~GRN_LED)
#define IR_LED_ON         (P5OUT |= IR_LED)
#define IR_LED_OFF       (P5OUT &= ~IR_LED)
#define RESET_STATE                     (0)
#define ALWAYS                          (1)
#define RED_LED                      (0x01) // RED LED 0
#define GRN_LED                      (0x40) // GREEN LED 1
#define RESET                        (0x00) // Set 8 bits of zeros
#define FULL                         (0xFF) // Set 8 bits of ones
#define FIRST_LINE                      (0)
#define SECOND_LINE                     (1)
#define THIRD_LINE                      (2)
#define FOURTH_LINE                     (3)
#define HIGH                            (1)
#define LOW                             (0)

#define COUNT_ELEVEN                   (11)
#define COUNT_TEN                      (10)
#define COUNT_FOUR                      (4)
#define COUNT_FIFTY                    (50)
#define COUNT_TWENTY                   (20)
#define COUNT_ONE                       (1)
#define COUNT_NINE                      (9)

#define FIRST                           (1)
#define SECOND                          (2)
#define THIRD                           (3)
#define FOURTH                          (4)

#define DIV_BY_FIVE                     (5)
#define DIV_BY_TWO                      (2)

//Port 1 Pins==================================================================
#define RED_LED                      (0x01) // 0 RED LED 0
#define A1_SEEED                     (0x02) // 1 A1_SEEED
#define V_DETECT_L                   (0x04) // 2 Pin 2 A2
#define V_DETECT_R                   (0x08) // 3 Pin 3 A3
#define A4_SEEED                     (0x10) // 4 A4_SEEED
#define V_THUMB                      (0x20) // 5 Pin 5 A5
#define UCA0RXD                      (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD                      (0x80) // 7 Back Channel UCA0TXD

//Port 2 Pins===================================================================
#define P2_0                         (0x01) // 0 RED LED 0
#define P2_1                         (0x02) // 1 A1_SEEED
#define P2_2                         (0x04) // 2
#define SW2                          (0x08) // 3
#define P2_4                         (0x10) // 4 A4_SEEED
#define P2_5                         (0x20) // 5
#define LFXOUT                       (0x40) // 6 Back Channel UCA0RXD
#define LFXIN                        (0x80) // 7 Back Channel UCA0TXD

//Port 3 Pins==================================================================
#define TEST_PROBE                   (0x01) // 0 TEST PROBE
#define OA20                         (0x02) // 1 Photodiode Circuit
#define OA2N                         (0x04) // 2 Photodiode Circuit
#define OA2P                         (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT                    (0x10) // 4 SMCLK
#define P3_5                         (0x20) // 5
#define IOT_LINK                     (0x40) // 6 IOT_LINK
#define P3_7                         (0x80) // 7 

//Port 4 Pins==================================================================
#define RESET_LCD                    (0x01) // 0 LCD Reset
#define SW1                          (0x02) // 1 SW1
#define UCA1RXD                      (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD                      (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD                  (0x10) // 4 Chip Select
#define UCB1CLK                      (0x20) // 5 SPI mode - clock output-UCB1CLK
#define UCB1SIMO                     (0x40) // 6 UCB1SIMO
#define UCB1SOMI                     (0x80) // 7 UCB1SOMI

//Port 5 Pins=================================================================
#define IOT_RESET                    (0x01) // 0 
#define P5_1                         (0x02) // 1 
#define IOT_PROG_SEL                 (0x04) // 2
#define IOT_PROG_MODE                (0x08) // 3
#define IR_LED                       (0x10) // 4 

//Port 6 Pins==================================================================
#define R_FORWARD                    (0x01) // 0 
#define L_FORWARD                    (0x02) // 1 
#define R_REVERSE                    (0x04) // 2 
#define L_REVERSE                    (0x08) // 3 
#define LCD_BACKLITE                 (0x10) // 4 
#define P6_5                         (0x20) // 5 
#define GRN_LED                      (0x40) // 6 


//Interrupts====================================================================
#define TB0CCR0_INTERVAL            (25000)   //8,000,000/2/8/[1/50msec]
#define TB0CCR1_INTERVAL            (40000)   //8,000,000/2/8/[1/80msec]
#define TB0CCR2_INTERVAL            (25000)   //8,000,000/2/8/[1/20msec]


//Timers=======================================================================
#define Time_Sequence_Rate             (50)
#define S1250     (1250/Time_Sequence_Rate)
#define S1000     (1000/Time_Sequence_Rate)
#define S750       (750/Time_Sequence_Rate)
#define S500       (500/Time_Sequence_Rate)
#define S250       (250/Time_Sequence_Rate)
#define TIME_MAX_250                  (250)

#define CHANGE_PROBE   (P3OUT ^ TEST_PROBE)       //Change state of Probe

#define S0                              (0)
#define S2                              (2)
#define S4                              (4)
#define S14                            (14)

#define MAXTIME                      (9998)

#define TWOSECS                        (40)
#define TENSECS                       (400)


//Wheels=======================================================================
#define RIGHT_FORWARD_SPEED       (TB3CCR1)
#define LEFT_FORWARD_SPEED        (TB3CCR2)
#define RIGHT_REVERSE_SPEED       (TB3CCR3)
#define LEFT_REVERSE_SPEED        (TB3CCR4)

#define WHEEL_OFF                       (0)
#define WHEEL_PERIOD                (50000)

#define HALF            (WHEEL_PERIOD *0.5)
#define THREEFOURTHS    (WHEEL_PERIOD*0.75)
#define MINSPEED        (WHEEL_PERIOD*0.4)
#define MAXSPEED           (WHEEL_PERIOD-5)
#define CRUISE                      (30000)
#define SEARCH                      (25000)
#define RCORRECT                    (27000)
#define LCORRECT                    (24000)

#define NUDGE                        (5000)
#define PUSH                        (10000)

#define SPEED_SHIFT                   (1000)
#define QUARTER_LOOP                    (3)

//ADC =========================================================================
#define THUMB                           (0)
#define LDET                            (1)
#define RDET                            (2)
#define BEGIN_ARRAY                     (0)
#define MAX_ARRAY                       (8)
#define SHIFT                           (3)

//BCD ==========================================================================
#define CHAR_LENGTH                     (4)
#define ASCII_SHIFT                  (0x30)

#define TENS                           (10)
#define HUNDREDS                      (100)
#define THOUSANDS                    (1000)
#define NINE                            (9)
#define NINENINE                       (99)
#define NINENINENINE                  (999)

#define CHAR0                           (0)
#define CHAR1                           (1)
#define CHAR2                           (2)
#define CHAR3                           (3)
#define CHAR4                           (4)
#define CHAR5                           (5)
#define CHAR6                           (6)
#define CHAR7                           (7)
#define CHAR8                           (8)
#define CHAR9                           (9)
#define CHARA                          (10)
#define CHARB                          (11)

//Intercept ====================================================================
#define CALIBRATE                     ('c')
#define INTERCEPT                     ('i')
#define DRIVE                         ('d')
#define TURN                          ('t')
#define TURN2                         ('u')
#define STOP                          ('s')

#define WHITE_BOARD                   ('w')
#define BLACK_LINE                    ('b')
#define LEFT_SIDE                     ('l')
#define RIGHT_SIDE                    ('r')

#define BUFFER                         (50)

//PID ==========================================================================
#define K1                              (100)
#define K2                              (0)
#define K3                              (0)

//Serial ======================================================================
#define BEGINNING                       (0)
#define SMALL_RING_SIZE                (16)
#define SWITCH_VALUE                 (0x08)
#define LARGE_RING_SIZE                (16)
#define LO_FREQ                    (0x5551)
#define HI_FREQ                    (0x4A11)
#define COMPUTER                   (0x4911)
#define K115                            (0)
#define K460                            (1)
#define K96                             (2)

//Menu =========================================================================
#define s0                              (0)
#define s1                              (1)
#define s2                              (2)
#define s3                              (3)
#define s4                              (4)
#define s5                              (5)
#define s6                              (6)
#define s7                              (7)
#define s8                              (8)

//Serial State =================================================================
#define SET_RATE                      ('s')
#define WAITING                       ('w')
#define RECIEVING                     ('r')
#define TRANSMITTING                  ('t')







#endif //MACROS_H
#ifndef MACROS_H
#define MACROS_H

#define RED_LED_ON      (P1OUT |= RED_LED)
#define RED_LED_OFF    (P1OUT &= ~RED_LED)
#define GREEN_LED_ON    (P6OUT |= GRN_LED)
#define GREEN_LED_OFF  (P6OUT &= ~GRN_LED)
#define IR_LED_ON        (P5OUT |= IR_LED)
#define IR_LED_OFF      (P5OUT &= ~IR_LED)
#define ALWAYS                         (1)
#define RESET_STATE                    (0)
#define RED_LED                     (0x01) // RED LED 0
#define GRN_LED                     (0x40) // GREEN LED 1
#define RESET                       (0x00) // Set 8 bits of zeros
#define FULL                        (0xFF) // Set 8 bits of ones
#define FIRST_LINE                      (0)
#define SECOND_LINE                     (1)
#define THIRD_LINE                      (2)
#define FOURTH_LINE                     (3)
#define HIGH                            (1)
#define LOW                             (0)
#define COUNT_ELEVEN                   (11)

//Port 1 Pins==================================================================
#define RED_LED         (0x01) // 0 RED LED 0
#define A1_SEEED        (0x02) // 1 A1_SEEED
#define V_DETECT_L      (0x04) // 2 Pin 2 A2
#define V_DETECT_R      (0x08) // 3 Pin 3 A3
#define A4_SEEED        (0x10) // 4 A4_SEEED
#define V_THUMB         (0x20) // 5 Pin 5 A5
#define UCA0RXD         (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD         (0x80) // 7 Back Channel UCA0TXD

//Port 2 Pins===================================================================
#define P2_0            (0x01) // 0 RED LED 0
#define P2_1            (0x02) // 1 A1_SEEED
#define P2_2            (0x04) // 2
#define SW2             (0x08) // 3
#define P2_4            (0x10) // 4 A4_SEEED
#define P2_5            (0x20) // 5
#define LFXOUT          (0x40) // 6 Back Channel UCA0RXD
#define LFXIN           (0x80) // 7 Back Channel UCA0TXD

//Port 3 Pins==================================================================
#define TEST_PROBE      (0x01) // 0 TEST PROBE
#define OA20            (0x02) // 1 Photodiode Circuit
#define OA2N            (0x04) // 2 Photodiode Circuit
#define OA2P            (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT       (0x10) // 4 SMCLK
#define P3_5            (0x20) // 5
#define IOT_LINK        (0x40) // 6 IOT_LINK
#define P3_7            (0x80) // 7 

//Port 4 Pins==================================================================
#define RESET_LCD       (0x01) // 0 LCD Reset
#define SW1             (0x02) // 1 SW1
#define UCA1RXD         (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD         (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD     (0x10) // 4 Chip Select
#define UCB1CLK         (0x20) // 5 SPI mode - clock output-UCB1CLK
#define UCB1SIMO        (0x40) // 6 UCB1SIMO
#define UCB1SOMI        (0x80) // 7 UCB1SOMI

//Port 5 Pins=================================================================
#define IOT_RESET       (0x01) // 0 
#define P5_1            (0x02) // 1 
#define IOT_PROG_SEL    (0x04) // 2
#define IOT_PROG_MODE   (0x08) // 3
#define IR_LED          (0x10) // 4 

//Port 6 Pins==================================================================
#define R_FORWARD       (0x01) // 0 
#define L_FORWARD       (0x02) // 1 
#define R_REVERSE       (0x04) // 2 
#define L_REVERSE       (0x08) // 3 
#define LCD_BACKLITE    (0x10) // 4 
#define P6_5            (0x20) // 5 
#define GRN_LED         (0x40) // 6 

//States=======================================================================
#define NONE                    ('N')
#define STRAIGHT                ('L')
#define CIRCLE                  ('C')
#define TRIANGLE                ('T')
#define FIG_EIGHT               ('E')

#define WAIT                    ('W')
#define START                   ('S')
#define RUN                     ('R')
#define END                     ('E')

#define WHEEL_COUNT_TIME         (10)
#define RIGHT_COUNT_TIME          (8)
#define LEFT_COUNT_TIME           (8)
#define TRAVEL_DISTANCE         (300)
#define WAITING2START           (1500)

#define LEFT                    ('L')
#define RIGHT                   ('R')

#define LOOP                    (80)
#define TWOLOOP                 (160)
#define FOURLOOP                (320)
#define STAGEONE                (1)
#define STAGETWO                (20)
#define LOOPONE                 (0)
#define LOOPTWO                 (1)

#define TRI                     (6)
#define STAGEONETRI             (200)
#define STAGETWOTRI             (500)
#define STAGETHREETRI           (800)

#define FIRST                   (1)
#define SECOND                  (2)
#define THIRD                   (3)
#define FOURTH                  (4)

//Interrupts====================================================================
#define TB0CCR0_INTERVAL      (25000)   //8,000,000/2/8/[1/50msec]
#define TB0CCR1_INTERVAL      (40000)   //8,000,000/2/8/[1/80msec]
#define TB0CCR2_INTERVAL      (10000)

#define COUNT_TEN                (10)
#define COUNT_FOUR                (4)

//Timers=======================================================================
#define Time_Sequence_Rate           (50)
#define S1250   (1250/Time_Sequence_Rate)
#define S1000   (1000/Time_Sequence_Rate)
#define S750     (750/Time_Sequence_Rate)
#define S500     (500/Time_Sequence_Rate)
#define S250     (250/Time_Sequence_Rate)
#define TIME_MAX_250               (250)

#define CHANGE_PROBE (P3OUT ^ TEST_PROBE)       //Change state of Probe

#define S0                            (0)
#define S2                            (2)
#define S4                            (4)
#define S14                          (14)

//Wheels=======================================================================
#define RIGHT_FORWARD_SPEED      (TB3CCR1)
#define LEFT_FORWARD_SPEED       (TB3CCR2)
#define RIGHT_REVERSE_SPEED      (TB3CCR3)
#define LEFT_REVERSE_SPEED       (TB3CCR4)

#define WHEEL_OFF                      (0)
#define WHEEL_PERIOD               (40000)

#define HALF                       (20000)
#define THREEFOURTHS               (30000)
#define ONEFOURTH                  (10000)
#define TOTAL                      (39995)

//Drive =======================================================================
#define NOSTATE                      (0x0)
#define WAIT1                        (0x1)
#define FORWARD1                     (0x2)
#define WAIT2                        (0x3)
#define BACKWARD                     (0x4)
#define WAIT3                        (0x5)
#define FORWARD2                     (0x6)
#define WAIT4                        (0x7)
#define CW                           (0x8)
#define WAIT5                        (0x9)
#define CCW                          (0xA)
#define WAIT6                        (0xB)

//ADC =========================================================================
#define THUMB                          (0)
#define LDET                           (1)
#define RDET                           (2)

//BCD ==========================================================================
#define FIRST_CHAR                     (0)
#define SECOND_CHAR                    (1)
#define THIRD_CHAR                     (2)
#define FOURTH_CHAR                    (3)
#define CHAR_LENGTH                    (4)
#define ASCII_SHIFT                 (0x30)

#define TENS                          (10)
#define HUNDREDS                     (100)
#define THOUSANDS                   (1000)
#define NINE                           (9)
#define NINENINE                      (99)
#define NINENINENINE                 (999)

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






#endif //MACROS_H
#ifndef MACROS_H
#define MACROS_H

#define RED_LED_ON      (P1OUT |= RED_LED)
#define RED_LED_OFF    (P1OUT &= ~RED_LED)
#define GREEN_LED_ON    (P6OUT |= GRN_LED)
#define GREEN_LED_OFF  (P6OUT &= ~GRN_LED)
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


//Port 1 Pins==================================================================
#define RED_LED         (0x01) // 0 RED LED 0
#define A1_SEEED        (0x02) // 1 A1_SEEED
#define V_DETECT_L      (0x04) // 2
#define V_DETECT_R      (0x08) // 3
#define A4_SEEED        (0x10) // 4 A4_SEEED
#define V_THUMB         (0x20) // 5
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



#endif //MACROS_H
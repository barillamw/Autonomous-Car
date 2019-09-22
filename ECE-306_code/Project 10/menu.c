
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern unsigned int freq;
extern char display_line[FOURTH][COUNT_ELEVEN];
extern volatile unsigned char display_changed;
extern unsigned int ADC_Thumb;
extern unsigned int capture;
extern char serial_state;
char RedAndWhiteSong[233] = "We're the Red and White from State and we know we are the best. A hand behind our back, we can take on all the rest. Come o'er the hill, Caroline. Devils and Deacs stand in line. The Red and White from N.C. State. Go State!        ";
const char RedAndWhite[14] = "Red and White ";
const char WhiteAndRed[14] = "White and Red ";
unsigned int menu_select;
unsigned int menu;
unsigned int resistor;
unsigned int shapes;
unsigned int lyrics;
unsigned int counter;
unsigned int previous;
extern unsigned int scroll;




void Menu_Process(void){
  menu = ADC_Thumb >> COUNT_TEN;
  
  if(menu_select){
    switch(menu_select){
    case S1:
      Song_Menu();
      break;
    case S2:
      Shapes_Menu();
      break;
    case S3:
      Resistor_Menu();
      break;
    default: 
      break;
    }
  }
  else{
    lcd_BIG_mid();
    strcpy(display_line[FIRST_LINE],"---MAIN---");
    strcpy(display_line[THIRD_LINE],"---MENU---");
    strcpy(display_line[FOURTH_LINE],"          ");
    switch(menu){
      case S0:
        strcpy(display_line[SECOND_LINE],"<<---------");
        break;
      case S1:
        strcpy(display_line[SECOND_LINE],"   Song   ");
        break;
      case S2:
        strcpy(display_line[SECOND_LINE],"  Shapes  ");
        break;
      case S3:
        strcpy(display_line[SECOND_LINE], " Resistor ");
        break;
     }
  }
}
     
void Resistor_Menu(void){
  lcd_4line();
  resistor = ADC_Thumb / FOUR_TEN;
  
  strcpy(display_line[FIRST_LINE],"  COLOR:  ");
  strcpy(display_line[THIRD_LINE],"  VALUE:  ");
  strcpy(display_line[FOURTH_LINE],"    0#    ");
  
  switch(resistor){
  case S9:
    strcpy(display_line[SECOND_LINE], "  BLACK   ");
    display_line[FOURTH_LINE][CHAR5] = S0 + ASCII_SHIFT;
    break;
  case S8:
    strcpy(display_line[SECOND_LINE], "  BROWN   ");
    display_line[FOURTH_LINE][CHAR5] = S1 + ASCII_SHIFT;
    break;
  case S7:
    strcpy(display_line[SECOND_LINE], "   RED    ");
    display_line[FOURTH_LINE][CHAR5] = S2 + ASCII_SHIFT;
    break;    
  case S6:
    strcpy(display_line[SECOND_LINE], "  ORANGE  ");
    display_line[FOURTH_LINE][CHAR5] = S3 + ASCII_SHIFT;
    break;
  case S5:
    strcpy(display_line[SECOND_LINE], "  YELLOW  ");
    display_line[FOURTH_LINE][CHAR5] = S4 + ASCII_SHIFT;
    break;
  case S4:
    strcpy(display_line[SECOND_LINE], "  GREEN   ");
    display_line[FOURTH_LINE][CHAR5] = S5 + ASCII_SHIFT;
    break;
  case S3:
    strcpy(display_line[SECOND_LINE], "   BLUE   ");
    display_line[FOURTH_LINE][CHAR5] = S6 + ASCII_SHIFT;
    break;
  case S2:
    strcpy(display_line[SECOND_LINE], "  VIOLET  ");
    display_line[FOURTH_LINE][CHAR5] = S7 + ASCII_SHIFT;
    break;
  case S1:
    strcpy(display_line[SECOND_LINE], "   GRAY   ");
    display_line[FOURTH_LINE][CHAR5] = S8 + ASCII_SHIFT;
    break;
  case S0:
    strcpy(display_line[SECOND_LINE], "  WHITE   ");
    display_line[FOURTH_LINE][CHAR5] = S9 + ASCII_SHIFT;
    break;
  default: break;
  }
  

}

void Shapes_Menu(void){
  shapes = ADC_Thumb / FOUR_TEN;
  
  switch(shapes){
  case S9:
    strcpy(display_line[FIRST_LINE], " vSTART:v ");
    strcpy(display_line[SECOND_LINE], "  circle  ");
    strcpy(display_line[THIRD_LINE], "  square  ");
    break;
  case S8:
    strcpy(display_line[FIRST_LINE], "  circle  ");
    strcpy(display_line[SECOND_LINE], "  square  ");
    strcpy(display_line[THIRD_LINE], " triangle ");
    break;
  case S7:
    strcpy(display_line[FIRST_LINE], "  square  ");
    strcpy(display_line[SECOND_LINE], " triangle ");
    strcpy(display_line[THIRD_LINE], " octagon  ");
    break;
  case S6:
    strcpy(display_line[FIRST_LINE], " triangle ");
    strcpy(display_line[SECOND_LINE], " octagon  ");
    strcpy(display_line[THIRD_LINE], " pentagon ");
    break;
  case S5:
    strcpy(display_line[FIRST_LINE], " octagon  ");
    strcpy(display_line[SECOND_LINE], " pentagon ");
    strcpy(display_line[THIRD_LINE], "  hexagon ");
    break;
  case S4:
    strcpy(display_line[FIRST_LINE], " pentagon ");
    strcpy(display_line[SECOND_LINE], "  hexagon ");
    strcpy(display_line[THIRD_LINE], "   cube   ");
    break;
  case S3:
    strcpy(display_line[FIRST_LINE], "  hexagon ");
    strcpy(display_line[SECOND_LINE], "   cube   ");
    strcpy(display_line[THIRD_LINE], "   oval   ");
    break;
  case S2:
    strcpy(display_line[FIRST_LINE], "   cube   ");
    strcpy(display_line[SECOND_LINE], "   oval   ");
    strcpy(display_line[THIRD_LINE], "  sphere  ");
    break;
  case S1:
    strcpy(display_line[FIRST_LINE], "   oval   ");
    strcpy(display_line[SECOND_LINE], "  sphere  ");
    strcpy(display_line[THIRD_LINE], " cylinder ");
    break;
  case S0:
    strcpy(display_line[FIRST_LINE], "  sphere  ");
    strcpy(display_line[SECOND_LINE], " cylinder ");
    strcpy(display_line[THIRD_LINE], "  ^END.^  ");
    break;
  default: break;
  }
}

void Song_Menu(void){
  int i;

  lyrics = ADC_Thumb >> COUNT_SEVEN;
  if(lyrics > previous || lyrics == RESET){
    previous = lyrics;
   

    
    for(i=RESET; i<COUNT_ELEVEN; i++){
      display_line[SECOND_LINE][i] = RedAndWhiteSong[lyrics+i+(counter*THIRTY_TWO)];
    }
    
    if(lyrics == 31){
      counter++;
      if(counter == 7)
        counter = RESET;
    }
  }
  if(scroll){
    for(i=RESET; i<COUNT_ELEVEN; i++){
      display_line[FIRST_LINE][i] = RedAndWhite[(scroll%10+i)%14];
      display_line[THIRD_LINE][i] = WhiteAndRed[(scroll%10+i)%14];
    }
  }
    
}
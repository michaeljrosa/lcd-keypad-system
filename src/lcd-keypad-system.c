/**
 * Author: Michael Rosa
 * Date: June 2016
 */

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


int main(void)
{
  lcd_init(LCD_DISP_ON_CURSOR_BLINK);
  
  lcd_clrscr();
  lcd_gotoxy(0, 0);
  lcd_puts("first line");
  lcd_gotoxy(0, 1);
  lcd_puts("second line");
  
  while(1)
  {
  }
  
  return 0;
}
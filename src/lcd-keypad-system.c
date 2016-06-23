/**
 * Author: Michael Rosa
 * Date: June 2016
 */

#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define  LCD_BUFFER_SIZE    LCD_LINES * LCD_DISP_LENGTH

char *lcd_buffer;


inline void lcd_buffer_clr(void)
{
  memset(lcd_buffer, 254, LCD_BUFFER_SIZE);
}

inline void lcd_buffer_init(void)
{
  lcd_buffer = malloc(LCD_BUFFER_SIZE);
  lcd_buffer_clr();
}

uint8_t pos_from_xy(const uint8_t x, const uint8_t y)
{
  return y * LCD_DISP_LENGTH + x;
}

void lcd_buffer_writec(const uint8_t pos, const char c)
{
  if(pos < LCD_BUFFER_SIZE)
    *(lcd_buffer + pos) = c;
}

void lcd_buffer_writes(const uint8_t x, const uint8_t y, const char *s)
{
  strncpy(lcd_buffer + pos_from_xy(x, y), s, strlen(s));   // to remove the null byte
}

void lcd_update(void)
{
  for(uint8_t pos = 0; pos < LCD_BUFFER_SIZE; pos++)
  { 
    // need to account for how LCD memory is set up
    if(pos >= LCD_DISP_LENGTH && pos < 2 * LCD_DISP_LENGTH)            // in row 2
      lcd_putc(*(lcd_buffer + pos + LCD_DISP_LENGTH));       
    else if(pos >= 2 * LCD_DISP_LENGTH && pos < 3 * LCD_DISP_LENGTH)   // in row 3
      lcd_putc(*(lcd_buffer + pos - LCD_DISP_LENGTH));
    else
      lcd_putc(*(lcd_buffer + pos));
  }
}


int main(void)
{
  lcd_init(LCD_DISP_ON);
  lcd_buffer_init();
  
  
  while(1)
  {
  }
  
  return 0;
}
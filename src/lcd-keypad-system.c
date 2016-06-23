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

static char *lcd_buffer;
static uint8_t cursor;


static void lcd_update(void)
{
  char *line = malloc(LCD_DISP_LENGTH + 1);
  
  lcd_clrscr();
  for(uint8_t i = 0; i < LCD_LINES; i++)
  {
    // accounting for how LCD memory is set up
    if(i == 1)
      memcpy(line, &lcd_buffer[(i + 1) * LCD_DISP_LENGTH], LCD_DISP_LENGTH);
    else if(i == 2)
      memcpy(line, &lcd_buffer[(i - 1) * LCD_DISP_LENGTH], LCD_DISP_LENGTH);
    else
      memcpy(line, &lcd_buffer[i * LCD_DISP_LENGTH], LCD_DISP_LENGTH);
    
    line[LCD_DISP_LENGTH] = '\0';
    
    lcd_puts(line);
  }
}

void lcd_buffer_clrscr(void)
{
  memset(lcd_buffer, 254, LCD_BUFFER_SIZE);   // extended ASCII blank 
  cursor = 0;
}

void lcd_buffer_init(void)
{
  lcd_buffer = malloc(LCD_BUFFER_SIZE);
  lcd_buffer_clrscr();
}

void lcd_buffer_gotoxy(const uint8_t x, const uint8_t y)
{
  if(x < LCD_DISP_LENGTH && y < LCD_LINES)
    cursor = y * LCD_DISP_LENGTH + x;
}

void lcd_buffer_putc(const char c)
{
  *(lcd_buffer + cursor) = c;
  if(++cursor == LCD_BUFFER_SIZE) cursor = 0;
  
  lcd_update();
}

void lcd_buffer_puts(const char *s)
{
  if(cursor + strlen(s) < LCD_BUFFER_SIZE)        // if not on the last line
    strncpy(lcd_buffer + cursor, s, strlen(s));   // write as normal w/o null byte
  else
  {                                               // overflow from last line to first
    strncpy(lcd_buffer + cursor, s, LCD_BUFFER_SIZE - cursor);   
    strncpy(lcd_buffer, &s[LCD_BUFFER_SIZE - cursor], strlen(s) - LCD_BUFFER_SIZE + cursor);
  } 
  
  cursor += strlen(s);
  
  if(cursor >= LCD_BUFFER_SIZE)
    cursor %= LCD_BUFFER_SIZE;
  
  lcd_update();
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
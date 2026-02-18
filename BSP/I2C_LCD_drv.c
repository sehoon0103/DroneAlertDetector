//
//********************************************************************************************************
// 	Date: 	2024-02-01	                                              	
//********************************************************************************************************
//	FILE:	I2C_LCD_drv.c 
// 
//	TITLE:	CLCD Drive
//			
//********************************************************************************************************
//

#include "includes.h"     

uint8_t	lcd_data = 0x00, lcd_control = 0x08;

void LCD_command_8bit(uint8_t command)		/* write a command(instruction) to text LCD */
{
     lcd_control &= ~0x04;				// E = 0
	lcd_control &= ~0x01;				// RS = 0
	pcf8574Write((lcd_data<<4) | lcd_control);
     
	DelayUS(1);
	lcd_data = command & 0xf0;
	pcf8574Write(lcd_data | lcd_control);
     DelayUS(1);
	
	lcd_control |= 0x04;				// E = 1
	pcf8574Write(lcd_data | lcd_control);
	DelayUS(1);
	lcd_control &= ~0x04;				// E = 0
	pcf8574Write(lcd_data | lcd_control);
	
     DelayUS(100);
}

void LCD_command(uint8_t command)			/* write a command(instruction) to text LCD */
{
	lcd_control &= ~0x04;				// E = 0
	lcd_control &= ~0x01;				// RS = 0
	pcf8574Write((lcd_data<<4) | lcd_control);
	
	DelayUS(1);
	lcd_data = command & 0xf0;
	pcf8574Write(lcd_data | lcd_control);
     DelayUS(1);
	
	lcd_control |= 0x04;				// E = 1
	pcf8574Write(lcd_data | lcd_control);
	DelayUS(1);
	lcd_control &= ~0x04;				// E = 0
	pcf8574Write(lcd_data | lcd_control);
	
	DelayUS(1);
	lcd_data = (command<<4) & 0xf0;
	pcf8574Write(lcd_data | lcd_control);
	DelayUS(1);
	
	lcd_control |= 0x04;				// E = 1
	pcf8574Write(lcd_data | lcd_control);
	DelayUS(1);
	lcd_control &= ~0x04;				// E = 0
	pcf8574Write(lcd_data | lcd_control);
	
     DelayUS(100);
}

void LCD_data(uint8_t data)		/* display a character on text LCD */
{
	lcd_control &= ~0x04;				// E = 0
	lcd_control |= 0x01;				// RS = 1
	pcf8574Write((lcd_data<<4) | lcd_control);
	
	DelayUS(1);
	lcd_data = data & 0xf0;
	pcf8574Write(lcd_data | lcd_control);
     DelayUS(1);
	
	lcd_control |= 0x04;				// E = 1
	pcf8574Write(lcd_data | lcd_control);
	DelayUS(1);
	lcd_control &= ~0x04;				// E = 0
	pcf8574Write(lcd_data | lcd_control);
	
	DelayUS(1);
	lcd_data = (data<<4) & 0xf0;
	pcf8574Write(lcd_data | lcd_control);
	DelayUS(1);
	    
     lcd_control |= 0x04;				// E = 1
	pcf8574Write(lcd_data | lcd_control);
	DelayUS(1);
	lcd_control &= ~0x04;				// E = 0
	pcf8574Write(lcd_data | lcd_control);
	
	DelayUS(100);
}


void LCD_initialize(void)			// initialize text LCD module 
{
//	LCD_command(0x30);
//	DelayMS(10);
//	LCD_command(0x30);
//	DelayMS(1);
//	LCD_command(0x30);
//	DelayMS(1);

//	LCD_command(0x38);				// function set(4 bit, 2 line, 5x7 dot)
//     LCD_command(0x0C);				// display control(display ON, cursor OFF)
//     LCD_command(0x06);				// entry mode set(increment, not shift)
//     LCD_command(0x01);				// clear display
//     DelayMS(2);
	
	LCD_command_8bit(0x30);
	DelayMS(10);
	LCD_command_8bit(0x30);
	DelayMS(1);
	LCD_command_8bit(0x30);
	DelayMS(1);
	
	LCD_command_8bit(0x20);
	
	
	LCD_command(0x28);				// function set(4 bit, 2 line, 5x7 dot)
     LCD_command(0x0C);				// display control(display ON, cursor OFF)
     LCD_command(0x06);				// entry mode set(increment, not shift)
     LCD_command(0x01);				// clear display
     DelayMS(2);
}


void LCD_string(uint8_t command, uint8_t *string) /* display a string on LCD */
{
     LCD_command(command);			// start position of string
     while(*string != '\0') {			// display string
        LCD_data(*string);
        string++;
     }
}

/* -------------------------------------------------------------------------- */
/*		텍스트 LCD 모듈의 수치 데이터 출력 함수				*/
/* -------------------------------------------------------------------------- */

void LCD_binary(U16 number, U08 digit)		/* display 8 or 16 bit binary number */
{
     unsigned char i, shift;

     if((digit == 0) || (digit > 16)) return;

     shift = digit - 1;
     for(i = 0; i < digit; i++ )
     { 
          LCD_data(((number >> shift) & 0x01) + '0');
          shift--;
     }
}

void LCD_unsigned_decimal(U32 number, U08 zerofill, U08 digit) /* display unsigned decimal number */
{
     unsigned char zero_flag, character;
     unsigned long div;

     if((digit == 0) || (digit > 9)) return;

     div = 1;
     while(--digit) div *= 10;

     zero_flag = zerofill;
     while(div > 0)				// display number
     { 
          character = number / div;
          if((character == 0) && (zero_flag == 0) && (div != 1))
               LCD_data(character + ' ');
          else
          { 
               zero_flag = 1;
               LCD_data(character + '0');
          }
          number %= div;
          div /= 10;
     }
}

void LCD_signed_decimal(S32 number, U08 zerofill, U08 digit)	/* display signed decimal number */
{
     unsigned char zero_flag, character;
     unsigned long div;

     if((digit == 0) || (digit > 9)) return;

     if(number >= 0)				// display sign
          LCD_data('+');
     else
     { 
          LCD_data('-');
          number = -number;
     }

     div = 1;
     while(--digit) div *= 10;

     zero_flag = zerofill;
     while(div > 0)				// display number
     { 
          character = number / div;
          if((character == 0) && (zero_flag == 0) && (div != 1))
               LCD_data(character + ' ');
          else
          { 
               zero_flag = 1;
               LCD_data(character + '0');
          }
          number %= div;
          div /= 10;
     }
}

void LCD_hexadecimal(U32 number, U08 digit)	/* display hexadecimal number */
{
     unsigned char i, character;

     if((digit == 0) || (digit > 8)) return;

     for(i = digit; i > 0; i--)
     { 
          character = (number >> 4*(i-1)) & 0x0F;
          if(character < 10) LCD_data(character + '0');
          else               LCD_data(character - 10 + 'A');
     }
}

void LCD_0x_hexadecimal(U32 number, U08 digit)	/* display hexadecimal number with 0x */
{
     unsigned char i, character;

     if((digit == 0) || (digit > 8)) return;

     LCD_data('0');
     LCD_data('x');

     for(i = digit; i > 0; i--)
     { 
          character = (number >> 4*(i-1)) & 0x0F;
          if(character < 10) LCD_data(character + '0');
          else               LCD_data(character - 10 + 'A');
     }
}

void LCD_unsigned_float(float number, U08 integral, U08 fractional) /* display unsigned floating-point number */
{
     unsigned char zero_flag, digit, character;	// integral = digits of integral part
     unsigned long div, integer;			// fractional = digits of fractional part

     digit = integral + fractional;
     if((integral == 0) || (fractional == 0) || (digit > 9)) return;

     div = 1;
     while(--digit) div *= 10;

     while(fractional--) number *= 10.;
     integer = (U32)(number + 0.5);

     zero_flag = 0;
     digit = 1;
     while(div > 0)				// display number
     { 
          character = integer / div;
          if((character == 0) && (zero_flag == 0) && (digit != integral))
               LCD_data(character + ' ');
          else
          { 
               zero_flag = 1;
               LCD_data(character + '0');
          }
          integer %= div;
          div /= 10;

          if(digit == integral)
               LCD_data('.');
          digit++;
     }
}

void LCD_signed_float(float number, U08 integral, U08 fractional) /* display signed floating-point number */
{
     unsigned char zero_flag, digit, character;
     unsigned long div, integer;

     digit = integral + fractional;
     if((integral == 0) || (fractional == 0) || (digit > 9)) return;

     if(number >= 0)				// display sign
          LCD_data('+');
     else
     {      
          LCD_data('-');
          number = -number;
     }

     div = 1;
     while(--digit) div *= 10;

     while(fractional--) number *= 10.;
     integer = (U32)(number + 0.5);

     zero_flag = 0;
     digit = 1;
     while(div > 0)				// display number
     { 
          character = integer / div;
          if((character == 0) && (zero_flag == 0) && (digit != integral))
               LCD_data(character + ' ');
          else
          {  
               zero_flag = 1;
               LCD_data(character + '0');
          }
          integer %= div;
          div /= 10;

          if(digit == integral)
               LCD_data('.');
          digit++;
     }
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void LCD_xy(uint8_t x, uint8_t y)
{
     if(x > 3 || y > 39) return;
     
     if(x == 0)      LCD_command(0x80 + y);
	else if(x == 1) LCD_command(0xc0 + y);
     else if(x == 2) LCD_command(0x94 + y);
     else if(x == 3) LCD_command(0xd4 + y);
}

void clear_line(uint8_t x)
{
     uint8_t   cmd;
     
     if(x > 3) return;
     
  	if(x == 0)      cmd = 0x80;
     else if(x == 1) cmd = 0xc0;
     else if(x == 2) cmd = 0x94;
     else if(x == 3) cmd = 0xd4;
     
                          //01234567890123456789
	LCD_string(cmd | 0x80,"                    ");
}

void LCD_cursor_on(uint8_t x, uint8_t y)
{
  	if(x > 3 || y > 39) return;
     
     LCD_xy(x, y);
	LCD_command(0x0F);	     // cursor and blinking
}

void LCD_cursor_off(void)
{
	LCD_command(0x0C);	
}

void Set_font(void)
{
	uint8_t	i;
	uint8_t 	font[] = {		
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0x00,
//		0x00, 0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x00,
//		0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x0E, 0x00,
		0x00, 0x00, 0x00, 0x1F, 0x0E, 0x0E, 0x0E, 0x00,
		0x00, 0x1F, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00,
		
		0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	
	LCD_command(0x40);
	for(i=0;i<40;i++) LCD_data(font[i]);
	
}

void LCD_4d(unsigned int number , char position)
{
	 int a=0;
	 int b=0;
	 int c=0;
	 int d=0;
	 unsigned int i,flag;
     
	 flag = 0;
     i = number / 1000;
     if(i == 0) LCD_data(' ');
     else {   
	 		  if(i==3  || i==6 || i==9) a=1;
	 		  LCD_data(i + '0');
              flag = 1;
          }
      
     number = number % 1000;
     i = number / 100; 
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   
	          if(i==3  || i==6 || i==9) b=1;
			  LCD_data(i + '0');
              flag = 1;
          }
     
     number = number % 100;
     i = number / 10;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {
               if(i==3  || i==6 || i==9) c=1;
	 	       LCD_data(i + '0');
          }
     i = number % 10;
	 if(i==3  || i==6 || i==9) d=1;
     LCD_data(i + '0');

	 if(a==1 || b==1 || c==1 || d==1)
	 {
         LCD_string(position,"   *");
	 }
 
     if((a==1  && b==1) || (a==1  && c==1) || (a==1  && d==1) || (b==1  && c==1) || (b==1  && d==1) || (c==1  && d==1) )
	 {
         LCD_string(position,"  **");
	 }
	 if((a==1  && b==1 && c==1) || (a==1  && c==1 && d==1) || (b==1  && c==1 && d==1))
	 {
         LCD_string(position," ***");
	 }
 
     if((a==1)  && (b==1) && (c==1) && (d=1))
	 {
         LCD_string(position,"****");
	 }
	 a=b=c=d=0;
}    

void LCD_s4d(int number)
{
     unsigned int i, flag;
     flag = 0;      
     
     if(number < 0) {
     	number = number * (-1);
     	LCD_data('-');
     } else {
     	if(number == 0) LCD_data(' ');
     	else            LCD_data('+');
     }
     
     i = number / 1000;
     if(i == 0) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
      
     number = number % 1000;
     i = number / 100; 
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     number = number % 100;
     i = number / 10;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else LCD_data(i + '0');
     
     i = number % 10;
     LCD_data(i + '0');  
}  

//------------------------------------------------------------------------------

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
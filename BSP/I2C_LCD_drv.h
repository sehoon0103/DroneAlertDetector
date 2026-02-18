//
//********************************************************************************************************
// 	Date: 	2024-02-01	                                              	
//********************************************************************************************************
//	FILE:	CLCD_drv.h 
// 
//	TITLE:	CLCD Drive
//			
//********************************************************************************************************
//

#ifndef __CLCD_DRV_H
#define __CLCD_DRV_H

//#define   DDRAM_LINE1     0x40
//#define   DDRAM_LINE2     0x40
//#define   DDRAM_LINE3     0x14
//#define   DDRAM_LINE4     0x54

#define	L1		0x80
#define	L2		0xC0
#define	L3		0x84
#define	L4		0xD4

void LCD_command(uint8_t command);			// write a command(instruction) to text LCD
void LCD_data(uint8_t data);			// display a character on text LCD
void LCD_initialize(void);         // initialize text LCD module
void LCD_string(uint8_t command, uint8_t *string);	// display a string on LCD
//void LCD_string(uint8_t x, uint8_t y, uint8_t *string);

void LCD_binary(U16 number, U08 digit);		// display 8 or 16 bit binary number
void LCD_unsigned_decimal(U32 number, U08 zerofill, U08 digit); // display unsigned decimal number
void LCD_signed_decimal(S32 number, U08 zerofill, U08 digit);	// display signed decimal number
void LCD_hexadecimal(U32 number, U08 digit);	// display hexadecimal number
void LCD_0x_hexadecimal(U32 number, U08 digit);	// display hexadecimal number with 0x
void LCD_unsigned_float(float number, U08 integral, U08 fractional); // display unsigned floating-point number
void LCD_signed_float(float number, U08 integral, U08 fractional);   // display signed floating-point number

// -----------------------------------------------------------------------------
void LCD_xy(uint8_t x, uint8_t y);

void clear_line(uint8_t cmd);
void LCD_cursor_on(uint8_t x, uint8_t y);
void LCD_cursor_off(void);

void Set_font(void);
// Formatted LCD Display Routine

#endif


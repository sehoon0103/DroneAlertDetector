//
//********************************************************************************************************
// 	Date: 	10/28/2017	                                              	
//********************************************************************************************************
//	FILE:	BSP_GLCD_V30.C 
// 
//	TITLE:	ASCII(English)-Only Display on Graphic LCD Module 
//********************************************************************************************************
//

#include 	"..\includes.h"

uint8_t xcharacter, ycharacter;		// x character(0-7), y character(0-19)
uint8_t cursor_flag, xcursor, ycursor;	// x and y cursor position(0-7, 0-19)
//unsigned char inverse_flag = 0;   

unsigned char screen[8][128];		        // screen buffer

//extern	void Delay_us(unsigned char time_us);		/* time delay for us */
//extern	void Delay_ms(unsigned int time_ms);       	/* time delay for ms */


prog_uchar font[95][5] = {		/* 5x7 ASCII character font */
	{0x00, 0x00, 0x00, 0x00, 0x00},		/* 0x20 space */
	{0x00, 0x00, 0x4f, 0x00, 0x00},		/* 0x21 ! */
	{0x00, 0x07, 0x00, 0x07, 0x00},		/* 0x22 " */
	{0x14, 0x7f, 0x14, 0x7f, 0x14},		/* 0x23 # */
	{0x24, 0x2a, 0x7f, 0x2a, 0x12},		/* 0x24 $ */
	{0x23, 0x13, 0x08, 0x64, 0x62},		/* 0x25 % */
	{0x36, 0x49, 0x55, 0x22, 0x50},		/* 0x26 & */
	{0x00, 0x05, 0x03, 0x00, 0x00},		/* 0x27 ' */
	{0x00, 0x1c, 0x22, 0x41, 0x00},		/* 0x28 ( */
	{0x00, 0x41, 0x22, 0x1c, 0x00},		/* 0x29 ) */
	{0x14, 0x08, 0x3e, 0x08, 0x14},		/* 0x2a * */
	{0x08, 0x08, 0x3e, 0x08, 0x08},		/* 0x2b + */
	{0x00, 0x50, 0x30, 0x00, 0x00},		/* 0x2c , */
	{0x08, 0x08, 0x08, 0x08, 0x08},		/* 0x2d - */
	{0x00, 0x60, 0x60, 0x00, 0x00},		/* 0x2e . */
	{0x20, 0x10, 0x08, 0x04, 0x02},		/* 0x2f / */
	{0x3e, 0x51, 0x49, 0x45, 0x3e},		/* 0x30 0 */
	{0x00, 0x42, 0x7f, 0x40, 0x00},		/* 0x31 1 */
	{0x42, 0x61, 0x51, 0x49, 0x46},		/* 0x32 2 */
	{0x21, 0x41, 0x45, 0x4b, 0x31},		/* 0x33 3 */
	{0x18, 0x14, 0x12, 0x7f, 0x10},		/* 0x34 4 */
	{0x27, 0x45, 0x45, 0x45, 0x39},		/* 0x35 5 */
	{0x3c, 0x4a, 0x49, 0x49, 0x30},		/* 0x36 6 */
	{0x01, 0x71, 0x09, 0x05, 0x03},		/* 0x37 7 */
	{0x36, 0x49, 0x49, 0x49, 0x36},		/* 0x38 8 */
	{0x06, 0x49, 0x49, 0x29, 0x1e},		/* 0x39 9 */
	{0x00, 0x36, 0x36, 0x00, 0x00},		/* 0x3a : */
	{0x00, 0x56, 0x36, 0x00, 0x00},		/* 0x3b ; */
	{0x08, 0x14, 0x22, 0x41, 0x00},		/* 0x3c < */
	{0x14, 0x14, 0x14, 0x14, 0x14},		/* 0x3d = */
	{0x00, 0x41, 0x22, 0x14, 0x08},		/* 0x3e > */
	{0x02, 0x01, 0x51, 0x09, 0x06},		/* 0x3f ? */
	{0x32, 0x49, 0x79, 0x41, 0x3e},		/* 0x40 @ */
	{0x7e, 0x11, 0x11, 0x11, 0x7e},		/* 0x41 A */
	{0x7f, 0x49, 0x49, 0x49, 0x36},		/* 0x42 B */
	{0x3e, 0x41, 0x41, 0x41, 0x22},		/* 0x43 C */
	{0x7f, 0x41, 0x41, 0x22, 0x1c},		/* 0x44 D */
	{0x7f, 0x49, 0x49, 0x49, 0x41},		/* 0x45 E */
	{0x7f, 0x09, 0x09, 0x09, 0x01},		/* 0x46 F */
	{0x3e, 0x41, 0x49, 0x49, 0x7a},		/* 0x47 G */
	{0x7f, 0x08, 0x08, 0x08, 0x7f},		/* 0x48 H */
	{0x00, 0x41, 0x7f, 0x41, 0x00},		/* 0x49 I */
	{0x20, 0x40, 0x41, 0x3f, 0x01},		/* 0x4a J */
	{0x7f, 0x08, 0x14, 0x22, 0x41},		/* 0x4b K */
	{0x7f, 0x40, 0x40, 0x40, 0x40},		/* 0x4c L */
	{0x7f, 0x02, 0x0c, 0x02, 0x7f},		/* 0x4d M */
	{0x7f, 0x04, 0x08, 0x10, 0x7f},		/* 0x4e N */
	{0x3e, 0x41, 0x41, 0x41, 0x3e},		/* 0x4f O */
	{0x7f, 0x09, 0x09, 0x09, 0x06},		/* 0x50 P */
	{0x3e, 0x41, 0x51, 0x21, 0x5e},		/* 0x51 Q */
	{0x7f, 0x09, 0x19, 0x29, 0x46},		/* 0x52 R */
	{0x26, 0x49, 0x49, 0x49, 0x32},		/* 0x53 S */
	{0x01, 0x01, 0x7f, 0x01, 0x01},		/* 0x54 T */
	{0x3f, 0x40, 0x40, 0x40, 0x3f},		/* 0x55 U */
	{0x1f, 0x20, 0x40, 0x20, 0x1f},		/* 0x56 V */
	{0x3f, 0x40, 0x38, 0x40, 0x3f},		/* 0x57 W */
	{0x63, 0x14, 0x08, 0x14, 0x63},		/* 0x58 X */
	{0x07, 0x08, 0x70, 0x08, 0x07},		/* 0x59 Y */
	{0x61, 0x51, 0x49, 0x45, 0x43},		/* 0x5a Z */
	{0x00, 0x7f, 0x41, 0x41, 0x00},		/* 0x5b [ */
	{0x02, 0x04, 0x08, 0x10, 0x20},		/* 0x5c \ */
	{0x00, 0x41, 0x41, 0x7f, 0x00},		/* 0x5d ] */
	{0x04, 0x02, 0x01, 0x02, 0x04},		/* 0x5e ^ */
	{0x40, 0x40, 0x40, 0x40, 0x40},		/* 0x5f _ */
	{0x00, 0x01, 0x02, 0x04, 0x00},		/* 0x60 ` */
	{0x20, 0x54, 0x54, 0x54, 0x78},		/* 0x61 a */
	{0x7f, 0x48, 0x44, 0x44, 0x38},		/* 0x62 b */
	{0x38, 0x44, 0x44, 0x44, 0x20},		/* 0x63 c */
	{0x38, 0x44, 0x44, 0x48, 0x7f},		/* 0x64 d */
	{0x38, 0x54, 0x54, 0x54, 0x18},		/* 0x65 e */
	{0x08, 0x7e, 0x09, 0x01, 0x02},		/* 0x66 f */
	{0x0c, 0x52, 0x52, 0x52, 0x3e},		/* 0x67 g */
	{0x7f, 0x08, 0x04, 0x04, 0x78},		/* 0x68 h */
	{0x00, 0x04, 0x7d, 0x00, 0x00},		/* 0x69 i */
	{0x20, 0x40, 0x44, 0x3d, 0x00},		/* 0x6a j */
	{0x7f, 0x10, 0x28, 0x44, 0x00},		/* 0x6b k */
	{0x00, 0x41, 0x7f, 0x40, 0x00},		/* 0x6c l */
	{0x7c, 0x04, 0x18, 0x04, 0x7c},		/* 0x6d m */
	{0x7c, 0x08, 0x04, 0x04, 0x78},		/* 0x6e n */
	{0x38, 0x44, 0x44, 0x44, 0x38},		/* 0x6f o */
	{0x7c, 0x14, 0x14, 0x14, 0x08},		/* 0x70 p */
	{0x08, 0x14, 0x14, 0x18, 0x7c},		/* 0x71 q */
	{0x7c, 0x08, 0x04, 0x04, 0x08},		/* 0x72 r */
	{0x48, 0x54, 0x54, 0x54, 0x20},		/* 0x73 s */
	{0x04, 0x3f, 0x44, 0x40, 0x20},		/* 0x74 t */
	{0x3c, 0x40, 0x40, 0x20, 0x7c},		/* 0x75 u */
	{0x1c, 0x20, 0x40, 0x20, 0x1c},		/* 0x76 v */
	{0x3c, 0x40, 0x30, 0x40, 0x3c},		/* 0x77 w */
	{0x44, 0x28, 0x10, 0x28, 0x44},		/* 0x78 x */
	{0x0c, 0x50, 0x50, 0x50, 0x3c},		/* 0x79 y */
	{0x44, 0x64, 0x54, 0x4c, 0x44},		/* 0x7a z */
	{0x00, 0x08, 0x36, 0x41, 0x00},		/* 0x7b { */
	{0x00, 0x00, 0x77, 0x00, 0x00},		/* 0x7c | */
	{0x00, 0x41, 0x36, 0x08, 0x00},		/* 0x7d } */
	{0x08, 0x04, 0x08, 0x10, 0x08}};		/* 0x7e ~ */  

// 	LCD_DATABUS:		DB0-DB7 (7-14, data bus)				
//            	   		GND:	R/-W    (5, read/write)				
// 	LCD_CONTROL.4:	D/-I    (4, data/instruction)			
//         	  .5:	E       (6, enable)					
//         	  .6:	CS1     (15, chip select 1)				
//         	  .7:	CS2     (16, chip select 2)	


#define	LCD_CONTROL	PORTD
#define	LCD_DATABUS	PORTB

void GLCD_command(unsigned char signal,unsigned char command)       	//write a command 
{ 
	LCD_CONTROL = signal & 0xC0;					// D/-I = 0
	asm volatile(" PUSH  R0 ");                  // delay for 500 ns
	asm volatile(" POP   R0 ");
	asm volatile(" PUSH  R0 ");
	asm volatile(" POP   R0 ");
	LCD_DATABUS = command;                        	// write command
	LCD_CONTROL = (signal & 0xC0)|0x20;				// E = 1	
	asm volatile(" PUSH  R0 ");                  // delay for 500 ns
	asm volatile(" POP   R0 ");
	asm volatile(" PUSH  R0 ");
	asm volatile(" POP   R0 ");
	LCD_CONTROL = signal & 0xC0;                  	// E = 0
	asm volatile(" NOP      ");
	LCD_CONTROL = 0x00;							// clear all control signals
	Delay_us(10);                                // wait for GLCD busy
}

void GLCD_data(unsigned char signal,unsigned char character)   		// write a data 
{ 
	LCD_CONTROL = (signal & 0xC0)|0x10;				// D/-I = 1
	asm volatile(" PUSH  R0 ");                  // delay for 500 ns
	asm volatile(" POP   R0 ");
	asm volatile(" PUSH  R0 ");
	asm volatile(" POP   R0 ");
	LCD_DATABUS = character;                      	// write data
	LCD_CONTROL = (signal & 0xC0)|0x30;				// E = 1
	asm volatile(" PUSH  R0 ");                  // delay for 500 ns
	asm volatile(" POP   R0 ");
	asm volatile(" PUSH  R0 ");
	asm volatile(" POP   R0 ");
	LCD_CONTROL = (signal & 0xC0)|0x10;           	// E = 0
	asm volatile(" NOP      ");
	LCD_CONTROL = 0x00;							// clear all control signals
	Delay_us(10);                                // wait GLCD busy
}

void GLCD_clear(void)				/* clear GLCD screen */
{ unsigned char i, j, x;

  LCD_CONTROL = 0x00;				// clear all control signals
  GLCD_command(0xC0,0x3F);			// CS1,CS2 display ON
  GLCD_command(0xC0,0xC0);			// CS1,CS2 display position

  x = 0xB8;
  for(i = 0; i <= 7; i++)
    { GLCD_command(0xC0,x);                     // X start addtess
      GLCD_command(0xC0,0x40);                  // Y start address
      for(j = 0; j <= 63; j++)
        GLCD_data(0xC0,0x00);			// clear CS1 and CS2 screen
      x++;
    }
}

void GLCD_xy(uint8_t x,uint8_t y)		/* set character position */
{ xcharacter = x;
  ycharacter = y;

  GLCD_command(0xC0,0xB8+xcharacter);		// X address

  if(ycharacter <= 9)				// if y <= 9, CS1 Y address
    GLCD_command(0x40,0x40+ycharacter*6+4);
  else						// if y >= 10, CS2 Y address
    GLCD_command(0x80,0x40+(ycharacter-10)*6);
}

void GLCD_character(uint8_t character)		/* display a character */
{ unsigned char i, signal, font_data;

  GLCD_xy(xcharacter,ycharacter);
  if(ycharacter <= 9)				// if y <= 9, CS1
    signal = 0x40;
  else						// if y >= 10, CS2
    signal = 0x80;
  for(i = 0; i <= 4; i++)
    { font_data = pgm_read_byte(&font[character-0x20][i]);
    //font_data = (Font[character-0x20][i]);
      if((cursor_flag == 1) && (xcharacter == xcursor) && (ycharacter == ycursor))
          GLCD_data(signal,font_data | 0x80);
      else
          GLCD_data(signal,font_data);
    }
  GLCD_data(signal,0x00);			// last byte 0x00

  ycharacter++;                                 // go next character position
  if(ycharacter == 20)
    { ycharacter = 0;
      xcharacter++;
    }
}

void GLCD_string(uint8_t x,uint8_t y,uint8_t *string)	/* display a string */
{ xcharacter = x;
  ycharacter = y;

  while(*string != '\0')
     { GLCD_character(*string);			// display a charcater
       string++;
     }
}


void Axis_xy(uint8_t x,uint8_t y)		/* set x, y axis position */
{ 
	GLCD_command(0xC0,0xB8+x);			// X address(0 - 7)

  	if(y <= 63)					// if y <= 63, CS1 Y address
    		GLCD_command(0x40,0x40 + y);
  	else							// if y >= 64, CS2 Y address
    		GLCD_command(0x80,0x40 + y - 64);
}

void Draw(void)					/* draw screen with buffer data */
{ 
	unsigned char x, y;

  	for(x = 0; x <= 7; x++)
    	{ 
    		Axis_xy(x, 0);					// draw CS1 area
      	for(y = 0; y <= 63; y++)
        		GLCD_data(0x40, screen[x][y]);
      	
      	Axis_xy(x, 64);				// draw CS2 area
      	for(y = 64; y <= 127; y++)
        		GLCD_data(0x80, screen[x][y]);
    	}
}

void Clear_screen(void)				/* clear buffer and GLCD screen */
{ 
	unsigned char x, y;

  	LCD_CONTROL = 0x00;				// clear all control signals
  	GLCD_command(0xC0,0x3F);			// CS1,CS2 display ON
  	GLCD_command(0xC0,0xC0);			// CS1,CS2 display position

  	for(x = 0; x <= 7; x++)			// clear screen buffer
    		for(y = 0; y <= 127; y++)
      		screen[x][y] = 0;

  	Draw();					// clear screen
}

void Dot(uint8_t xx,uint8_t y)			/* draw a dot on GLCD */
{ 
	unsigned char x, i;

  	if((xx > 63) || (y > 127)) return;

  	x = xx / 8;					// calculate x address
  	i = xx % 8;
  	if(i == 0)      i = 0x01;
  	else if(i == 1) i = 0x02;
  	else if(i == 2) i = 0x04;
  	else if(i == 3) i = 0x08;
  	else if(i == 4) i = 0x10;
  	else if(i == 5) i = 0x20;
  	else if(i == 6) i = 0x40;
  	else            i = 0x80;
  	screen[x][y] |= i;				// OR old data with new data

  	Axis_xy(x, y);				// draw dot on GLCD screen
  	if(y <= 63)
    		GLCD_data(0x40, screen[x][y]);
  	else
    		GLCD_data(0x80, screen[x][y]);
}

void Line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)	/* draw a straight line */
{ int x, y;

  if(y1 != y2)					// if y1 != y2, y is variable
    { if(y1 < y2)				//              x is function
        for(y = y1; y <= y2; y++)
          { x = x1 + (y - y1)*(x2 - x1)/(y2 - y1);
            Dot(x,y);
          }
      else
        for(y = y1; y >= y2; y--)
          { x = x1 + (y - y1)*(x2 - x1)/(y2 - y1);
            Dot(x,y);
          }
    }
  else if(x1 != x2)				// if x1 != x2, x is variable
    { if(x1 < x2)				//              y is function
        for(x = x1; x <= x2; x++)
          { y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
            Dot(x,y);
          }
      else
        for(x = x1; x >= x2; x--)
          { y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
            Dot(x,y);
          }
    }
  else						// if x1 == x2 and y1 == y2,
    Dot(x1,y1);					//             it is a dot
}

void Rectangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2) /* draw a rectangle */
{ 
	Line(x1,y1,x1,y2);				// horizontal line
  	Line(x2,y1,x2,y2);
  	Line(x1,y1,x2,y1);				// vertical line
  	Line(x1,y2,x2,y2);
}

void Circle(uint8_t x1,uint8_t y1,uint8_t r)	/* draw a circle */
{ int x, y;
  float s;

  for(y = y1 - r*3/4; y <= y1 + r*3/4; y++)	// draw with y variable
    { s = sqrt(r*r - (y-y1)*(y-y1)) + 0.5;
      x = x1 + (uint8_t)s;
      Dot(x,y);
      x = x1 - (uint8_t)s;
      Dot(x,y);
    }

  for(x = x1 - r*3/4; x <= x1 + r*3/4; x++)	// draw with x variable
    { s = sqrt(r*r - (x-x1)*(x-x1)) + 0.5;
      y = y1 + (uint8_t)s;
      Dot(x,y);
      y = y1 - (uint8_t)s;
      Dot(x,y);
    }
}


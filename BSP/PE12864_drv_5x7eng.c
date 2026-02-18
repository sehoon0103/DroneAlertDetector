//
//********************************************************************************************************
// 	Date: 	2024-02-01	                                              	
//********************************************************************************************************
//	FILE:	PE12864_drv_5x7eng.c 
// 
//	TITLE:	GLCD Drive for PE12864LRU
//			English :  5x7 dot
//********************************************************************************************************
//

#include "includes.h"     

uint8_t xcharacter, ycharacter;		// x character(0-7), y character(0-19)
uint8_t cursor_flag, xcursor, ycursor;	// x and y cursor position(0-7, 0-19)

unsigned char screen[8][128];		        // screen buffer

// *********************************************************************************************
//  8x16 Dot English(ASCII) Character Font	
// *********************************************************************************************
const uint8_t font[95][5] = {		/* 5x7 ASCII character font */
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


void GLCD_command(uint8_t command)			// write a command
{ 
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);		// A0 = L  
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);		// CS1 = L
	GPIO_ResetBits(GPIOC, GPIO_Pin_14);		// WR = L 
  	Delay_us(1);
  	//GPIO_Write(GPIOD,command);				// write command
	GPIOD->ODR = ((GPIOD->ODR & 0xFF00) | (uint16_t)command);
  	Delay_us(1);
  	GPIO_SetBits(GPIOC, GPIO_Pin_14);			// WR = H
  	GPIO_SetBits(GPIOC, GPIO_Pin_11);			// CS1 = H
  	Delay_us(10);                               	// wait for GLCD busy
}

void GLCD_data(uint8_t character)        	// write a data 
{ 
	GPIO_SetBits(GPIOC, GPIO_Pin_13);			// A0 = H
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);		// CS1 = L
	GPIO_ResetBits(GPIOC, GPIO_Pin_14);		// WR = L
  	Delay_us(1);
  	//GPIO_Write(GPIOD,character);				// write character
	GPIOD->ODR = ((GPIOD->ODR & 0xFF00) | (uint16_t)character);
  	Delay_us(1);
  	GPIO_SetBits(GPIOC, GPIO_Pin_14);			// WR = H
  	GPIO_SetBits(GPIOC, GPIO_Pin_11);			// CS1 = H
  	Delay_us(10);                               	// wait for GLCD busy
}

void GLCD_clear(void)				/* clear GLCD screen */
{
     int16_t	i, j;
       
     for(i = 0 ; i < 8 ; i++)
	{
		for(j = 0 ; j < 132 ; j++)
		{
               //Page Address Set
			GLCD_command(0xB0 + i);
               //Column Address Set
			GLCD_command(0x10 + (j >> 4));
			GLCD_command(0x00 + (j & 0x0F));
               //write data for clearing screen
			GLCD_data(0x00);
		}
	}  
}

void GLCD_init(void)			// initialize GLCD
{
  	GPIOC->BSRR = GPIO_Pin_10;		// BackLight On    
     
     GPIO_SetBits(GPIOC, GPIO_Pin_15);			// RD = H
     GPIO_SetBits(GPIOC, GPIO_Pin_14);			// WR = H
  	GPIO_SetBits(GPIOC, GPIO_Pin_11);			// CS1 = H
	
  	// reset LCD
	GPIO_ResetBits(GPIOC, GPIO_Pin_12);
	Delay_ms(1);
	GPIO_SetBits(GPIOC, GPIO_Pin_12);
	Delay_ms(10);
	
	//LCD bias Set(11)
	GLCD_command(0xA2);//1/9bias
	
	//ADC selection(8)
	//GLCD_command(0xA0);//Normal
     GLCD_command(0xA0+1);//Reverse
	
	//Common output state selection(15)
	GLCD_command(0xC0);
     //GLCD_command(0xC8);
	
	//Setting the built-in resistance ratio for regulation of the V0 voltage(17)
	GLCD_command(0x23);//small
	
	//Electronic volume control(18): adjust the brightness of the liquid crystal display by controlling V0
	//The Electronic Volume Mode Set :enabled
	GLCD_command(0x81);
	//Electronic Volume Register Set
	GLCD_command(0x29);	// 0x20
	
	//Power Control Setting
	GLCD_command(0x2F);
	
	// Normal/Reverse Display(9)
	GLCD_command(0xA6);
	
	// Entire Display On(10) : 0XA5 -> DISPLAY ALL POINTS ON
	GLCD_command(0xA5); 
	
	//Display On(1)
   	GLCD_command(0xAF); 
	
	// Entire Display On(10) : 0XA4 -> DISPLAY ALL POINTS Off
	GLCD_command(0xA4); 
	
	//GLCD_command(0x40);
	
	Delay_ms(10);
     
     GLCD_clear();  
}

void GLCD_xy(uint8_t x,uint8_t y)       /* set character */
{ 
	// Page Address Set           // x = 0 - 7
	GLCD_command(0xB0 + x);       
  	
	// Column Address Set         // y = 0 - 21
	GLCD_command(0x10 + ((y*6 + 4) >> 4));       
	GLCD_command(0x00 + ((y*6 + 4) & 0x0F));
     
     xcharacter = x;
  	ycharacter = y;	
}

void GLCD_character(uint8_t character)		/* display a character */
{ 
     uint8_t i, font_data;

  	GLCD_xy(xcharacter,ycharacter);
     
  	for(i = 0; i <= 4; i++)
     {
          font_data = font[character-0x20][i];
    		if((cursor_flag == 1) && (xcharacter == xcursor) && (ycharacter == ycursor))
               GLCD_data(font_data | 0x80);
          else
               GLCD_data(font_data); 
     }
     
  	ycharacter++;                           // go next character position
  	if(ycharacter == 22)
    	{ 
    		ycharacter = 0;
      	xcharacter++;
    	}
} 

void GLCD_string(uint8_t x,uint8_t y,uint8_t *string)	/* display a string */
{ 
     xcharacter = x;
     ycharacter = y;

     while(*string != '\0')
     { 
          GLCD_character(*string);			// display a charcater
          string++;
     }
}

// *********************************************************************************************
//  Graphic Function	
// *********************************************************************************************

void Axis_xy(uint8_t x,uint8_t y)		/* set x, y axis position */
{     
     // Page Address Set           // x = 0 - 7
	GLCD_command(0xB0 + x);       
  	
	// Column Address Set         // y = 0 - 127
	GLCD_command(0x10 + ((y + 4) >> 4));       
	GLCD_command(0x00 + ((y + 4) & 0x0F));   
}

void Draw(void)					/* draw screen with buffer data */
{ 
	uint8_t x, y;

  	for(x = 0; x <= 7; x++)
    	{ 
    		Axis_xy(x, 0);					// draw area
      	for(y = 0; y <= 127; y++)
        		GLCD_data(screen[x][y]);
    	}
}

void Clear_screen(void)				/* clear buffer and GLCD screen */
{ 
	uint8_t x, y;

  	for(x = 0; x <= 7; x++)			// clear screen buffer
    		for(y = 0; y <= 127; y++)
      		screen[x][y] = 0;

  	Draw();					// clear screen
}

void Dot(uint8_t xx,uint8_t y)			/* draw a dot on GLCD */
{ 
	uint8_t x, i;

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
     GLCD_data(screen[x][y]);
}

void Line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)	/* draw a straight line */
{ 
     int x, y;

     if(y1 != y2)					// if y1 != y2, y is variable
     { 
          if(y1 < y2)				//              x is function
               for(y = y1; y <= y2; y++)
               { 
                    x = x1 + (y - y1)*(x2 - x1)/(y2 - y1);
                    Dot(x,y);
               }
          else
               for(y = y1; y >= y2; y--)
               { 
                    x = x1 + (y - y1)*(x2 - x1)/(y2 - y1);
                    Dot(x,y);
               }
     }
     else if(x1 != x2)				// if x1 != x2, x is variable
     { 
          if(x1 < x2)				//              y is function
               for(x = x1; x <= x2; x++)
               { 
                    y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
                    Dot(x,y);
               }
          else
               for(x = x1; x >= x2; x--)
               { 
                    y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
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
{ 
     int x, y;
     float s;

     for(y = y1 - r*3/4; y <= y1 + r*3/4; y++)	// draw with y variable
     { 
          s = sqrt(r*r - (y-y1)*(y-y1)) + 0.5;
          x = x1 + (uint8_t)s;
          Dot(x,y);
          x = x1 - (uint8_t)s;
          Dot(x,y);
     }

     for(x = x1 - r*3/4; x <= x1 + r*3/4; x++)	// draw with x variable
     { 
          s = sqrt(r*r - (x-x1)*(x-x1)) + 0.5;
          y = y1 + (uint8_t)s;
          Dot(x,y);
          y = y1 - (uint8_t)s;
          Dot(x,y);
     }
}


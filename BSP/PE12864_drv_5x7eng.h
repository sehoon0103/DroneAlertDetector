//
//********************************************************************************************************
// 	Date: 	2024-02-01	                                              	
//********************************************************************************************************
//	FILE:	PE12864_drv_5x7eng.h 
// 
//	TITLE:	GLCD Drive for PE12864LRU
//			English :  5x7 dot
//********************************************************************************************************
//

#ifndef __GLCD_DRV_H
#define __GLCD_DRV_H

void GLCD_command(uint8_t command);		// write a command
void GLCD_data(uint8_t character);        	// write a data 

void GLCD_clear(void);								/* clear GLCD screen */
void GLCD_init(void);								// initialize GLCD
void GLCD_xy(uint8_t x,uint8_t y);                          /* set character */
void GLCD_character(uint8_t character);		               /* display a character */
void GLCD_string(uint8_t x,uint8_t y,uint8_t *string);	     /* display a string */

void Draw(void);					                    /* draw screen with buffer data */
void Clear_screen(void);				                    /* clear buffer and GLCD screen */
void Dot(uint8_t xx,uint8_t y);			               /* draw a dot on GLCD */
void Line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);	/* draw a straight line */
void Rectangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);/* draw a rectangle */
void Circle(uint8_t x1,uint8_t y1,uint8_t r);	          /* draw a circle */
#endif


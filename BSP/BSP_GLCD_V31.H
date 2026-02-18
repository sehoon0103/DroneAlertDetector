//
//********************************************************************************************************
// 	Date: 	10/28/2017	                                              	
//********************************************************************************************************
//	FILE:	BSP_GLCD_V30.H 
// 
//	TITLE:	ASCII(English)-Only Display on Graphic LCD Module 
//********************************************************************************************************
//

#ifndef BSP_GLCD_H
#define BSP_GLCD_H

//uint8_t xcharacter, ycharacter;		// x character(0-7), y character(0-19)
//uint8_t cursor_flag, xcursor, ycursor;	// x and y cursor position(0-7, 0-19)
////unsigned char inverse_flag = 0;   

// 	GLCD_DATABUS:		DB0-DB7 (7-14, data bus)				
//            	   		GND:	R/-W    (5, read/write)				
// 	GLCD_CONTROL.4:	D/-I    (4, data/instruction)			
//         	  .5:	E       (6, enable)					
//         	  .6:	CS1     (15, chip select 1)				
//         	  .7:	CS2     (16, chip select 2)	

void GLCD_command(unsigned char signal,unsigned char command);       	// write a command 
void GLCD_data(unsigned char signal,unsigned char character);   		// write a data 
void GLCD_clear(void);										// clear GLCD screen 
void GLCD_xy(uint8_t x,uint8_t y);								/* set character position */
void GLCD_character(uint8_t character);							/* display a character */
void GLCD_string(uint8_t x,uint8_t y,uint8_t *string);				/* display a string */

#endif



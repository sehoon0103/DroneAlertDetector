/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   IAR STM32-SK Evaluation Board
*
* Filename      : includes.h
* Version       : V1.10
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#include 	<stm32f10x.h>
#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>

#include  <ucos_ii.h>

//#include  <cpu.h>
//#include  <lib_def.h>
//#include  <lib_mem.h>
//#include  <lib_str.h>
//
#include  <stm32f10x_conf.h>
//#include  <stm32f10x_lib.h>
//
#include	<os_cfg.h>
#include  <app_cfg.h>

typedef unsigned char	U08;			// data type definition
typedef   signed char	S08;
typedef unsigned short 	U16;
typedef   signed short	S16;
typedef unsigned int 	U32;
typedef   signed int	S32;

#include  <BSP_evm2.h>
#include  <PE12864_drv_5x7eng.h>
#include  <FRAM25LV_drv_rev2.h>
#include	<I2C_LCD_drv.h>

// ESBB
#include 	<COMMRTOS.H>
#include 	<TMR.H>
#include 	<KEY.H>

//#define OS_ENTER_CRITICAL()   __disable_irq() 
//#define OS_EXIT_CRITICAL()    __enable_irq()

#define TRUE	1
#define FALSE	0



//#if (APP_LCD_EN == DEF_ENABLED)
//#include    <lcd.h>
//#endif
//
//#if (APP_OS_PROBE_EN == DEF_ENABLED)
//#include  <os_probe.h>
//#endif
//
//#if (APP_PROBE_COM_EN == DEF_ENABLED)
//#include  <probe_com.h>
//
//#if (PROBE_COM_METHOD_RS232 == DEF_ENABLED)
//#include  <probe_rs232.h>
//#endif
//#endif




#endif

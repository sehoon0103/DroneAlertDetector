/**
  ******************************************************************************
  * @file    BSP/BSP_evm2.h 
  * @author  Joonik Son
  * @version V1.0.0
  * @date    2024-02-01
  * @brief   
  ******************************************************************************
  * @Note
  



  *
  * COPYRIGHT 2016 BIT Technology
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H
#define __BSP_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include	"includes.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#define	IMU_I2C		I2C1
#define	IMU_LSM6DS3	(0x6A<<1)
#define	IMU_LIS3MDL	(0x1C<<1)
    
#define 	sEE_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define 	sEE_LONG_TIMEOUT         ((uint32_t)(10 * sEE_FLAG_TIMEOUT))

#define   sEE_I2C     	I2C1
#define   sEEAddress     0xA0

#define 	sEE_OK                    0
#define 	sEE_FAIL                  1

#define	LED0		0
#define	LED1		1
#define	LED2		2
#define	LED3		3



#define	DAC0		0
#define	DAC1		1


int  putchar(int character);

void TX1_char(uint8_t data);
void DelayUS(uint16_t us);
void DelayMS(uint16_t ms);
void	Delay_us(uint32_t time_us);
void	Delay_ms(uint32_t time_ms);

void	BSP_Init(void);
void SysTick_Configuration(void);

INT32U  BSP_CPU_ClkFreq (void);
INT32U  OS_CPU_SysTickClkFreq (void);

void RCC_Configuration(void);
void GPIO_Configuration(void);
void CAN_Configuration(void);
void NVIC_Configuration(void);

uint32_t sEE_TIMEOUT_UserCallback(void);

void LED_ON(uint8_t	led);
void LED_OFF(uint8_t led);
void LED_TOGGLE(uint8_t led);

void IMU_I2C_ByteWrite(u8 slaveAddr, u8* pBuffer, u8 writeAddr);
void IMU_I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead);
void IMU_Init(void);

void AT24C16_write(uint16_t address, uint8_t byte);
uint8_t AT24C16_read(uint16_t address);


void wr_U16(uint16_t addr, uint16_t data);
uint16_t rd_U16(uint16_t addr);

uint32_t pcf8574Write(uint8_t data);

#define TC75_ADDRESS 0x90	// TC75	A5 address


int16_t TC75_Read_Temperature(uint8_t TC75address);
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);
void I2C_stop(I2C_TypeDef* I2Cx);
int8_t I2C_read_ack(I2C_TypeDef* I2Cx);
int8_t I2C_read_nack(I2C_TypeDef* I2Cx);

// -----------------------------------------------------------------------------

#define LIS3MDL_CS_ON()  GPIOA->BRR = GPIO_Pin_4
#define LIS3MDL_CS_OFF() GPIOA->BSRR = GPIO_Pin_4
//#define EEPROM_CS_ON()	GPIOB->BRR = GPIO_Pin_12	
//#define EEPROM_CS_OFF() 	GPIOB->BSRR = GPIO_Pin_12

#define DUMMY_LIS3MDL    0xFF

// LIS3MDL register address map
#define   WHO_AM_I       0x0F

#define   CTRL_REG1      0x20
#define   CTRL_REG2      0x21
#define   CTRL_REG3      0x22
#define   CTRL_REG4      0x23
#define   CTRL_REG5      0x24

#define   STATUS_REG     0x27
#define   OUT_X_L        0x28
#define   OUT_X_H        0x29
#define   OUT_Y_L        0x2A
#define   OUT_Y_H        0x2B
#define   OUT_Z_L        0x2C
#define   OUT_Z_H        0x2D
#define   TEMP_OUT_L     0x2E
#define   TEMP_OUT_H     0x2F
#define   INT_CFG        0x30
#define   INT_SRC        0x31
#define   INT_THS_L      0x32
#define   INT_THS_H      0x33
      
// Full-sacle selection
#define   LIS3MDL_RANGE_4_GAUSS    0x00      // +/- 4g (default value)
#define   LIS3MDL_RANGE_8_GAUSS    0x20      // +/- 8g
#define   LIS3MDL_RANGE_12_GAUSS   0x40      // +/- 12g
#define   LIS3MDL_RANGE_16_GAUSS   0x60      // +/- 16g

// X and Y axes operating mode 
#define   LIS3MDL_LOWPOWERMODE     0x00      // Low power mode
#define   LIS3MDL_MEDIUMMODE       0x20      // Medium performance mode
#define   LIS3MDL_HIGHMODE         0x40      // High performance mode
#define   LIS3MDL_ULTRAHIGHMODE    0x60      // Ultra-high performance mode
 
// Output data rate configuration 
#define   LIS3MDL_DATARATE_0_625_HZ     0x00      // 0.625 Hz
#define   LIS3MDL_DATARATE_1_25_HZ      0x04      // 1.25 Hz
#define   LIS3MDL_DATARATE_2_5_HZ       0x08      // 2.5 Hz
#define   LIS3MDL_DATARATE_5_HZ         0x0C      // 5 Hz
#define   LIS3MDL_DATARATE_10_HZ        0x10      // 10 Hz
#define   LIS3MDL_DATARATE_20_HZ        0x14      // 20 Hz
#define   LIS3MDL_DATARATE_40_HZ        0x18      // 40 Hz
#define   LIS3MDL_DATARATE_80_HZ        0x1C      // 80 Hz

//#define   LIS3MDL_DATARATE_155_HZ        = 0b0001,   ///<  155 Hz (FAST_ODR + UHP)
//#define   LIS3MDL_DATARATE_300_HZ = 0b0011,   ///<  300 Hz (FAST_ODR + HP)
//#define   LIS3MDL_DATARATE_560_HZ = 0b0101,   ///<  560 Hz (FAST_ODR + MP)
//#define   LIS3MDL_DATARATE_1000_HZ = 0b0111,  ///<  1000 Hz (FAST_ODR + LP)

// System operation mode  
#define   LIS3MDL_CONTINUOUSMODE        0x00      // Continuous conversion
#define   LIS3MDL_SINGLEMODE            0x01      // Single-shot conversion
#define   LIS3MDL_POWERDOWNMODE         0x10      // Powered-down mode


#endif /* __BSP_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

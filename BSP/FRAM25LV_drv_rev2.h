/**
  ******************************************************************************
  * @file    FRAM25LV_drv_rev2.h 
  * @author  
  * @version V1.0.0
  * @date    2019-09-25
  * @brief   
  ******************************************************************************
  */ 

#ifndef __FRMA25_H
#define __FRMA25_H

#include "stm32f10x.h"

//#define   FM25L04B  1         // 4KBit (512 byte)

#define FM25LV_API_VERSION	        1.10
#define FM25LV_API_VERSION_HEX        0x0110

#define WREN_EEPROM			0x06
#define WRDI_EEPROM			0x04
#define RDSR_EEPROM			0x05
#define WRSR_EEPROM			0x01
#define READ_EEPROM			0x03
#define WRITE_EEPROM	     0x02
#define DUMMY_EEPROM	     0xFF
#define STATUS_REG_EEPROM     0x00

#define ADDRESS_HIGH(w)	((w>>8) & 0x00ff)
#define ADDRESS_LOW(w)	((w) & 0x00ff)


//#define EEPROM_CS_ON()	GPIOA->BRR = GPIO_Pin_4;	
//#define EEPROM_CS_OFF() 	GPIOA->BSRR = GPIO_Pin_4;
#define EEPROM_CS_ON()	GPIOB->BRR = GPIO_Pin_12	
#define EEPROM_CS_OFF() 	GPIOB->BSRR = GPIO_Pin_12

uint8_t spiTransferByte(uint8_t data);
void InitEeprom(void);
void WriteStatusRegisterEeprom(uint8_t StatusRegister);
uint8_t ReadStatusRegisterEeprom(void);
void WriteDisableEeprom(void);
void WriteEnableEeprom(void);
void WriteEeprom(uint16_t Address, uint8_t Data);
void PWriteEeprom(uint8_t Page, uint8_t *StartAddr);
uint8_t ReadEeprom(uint16_t Address);
float ApiVersionEeprom(void);
uint16_t ApiVersionHexEeprom(void);

#endif






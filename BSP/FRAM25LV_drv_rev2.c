/**
  ******************************************************************************
  * @file    FRAM25LV_drv_rev2.c 
  * @author  
  * @version V1.0.0
  * @date    2019-09-25
  * @brief   
  ******************************************************************************
  */ 


#include	"includes.h"

///*---------------------------------------------------------------------------
//	SPI1 Driver by STM32F10x GPIO
//---------------------------------------------------------------------------*/
//uint8_t spiTransferByte(uint8_t data)
//{
//	uint8_t read;
//	
//	/* Wait for SPI1 Tx buffer empty */
//    	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//    	/* Send SPI1 data */
//    	SPI_I2S_SendData(SPI1, data);
//    	
//	/* Wait for SPI1 data reception */
//    	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//    
//	/* Read SPI1 received data */
//    	read = SPI_I2S_ReceiveData(SPI1);
//
//	return read;
//}

/*---------------------------------------------------------------------------
	SPI2 Driver by STM32F10x GPIO
---------------------------------------------------------------------------*/
uint8_t spiTransferByte(uint8_t data)
{
	uint8_t read;
	
	/* Wait for SPI2 Tx buffer empty */
    	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    	/* Send SPI2 data */
    	SPI_I2S_SendData(SPI2, data);
    	
	/* Wait for SPI2 data reception */
    	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    
	/* Read SPI2 received data */
    	read = SPI_I2S_ReceiveData(SPI2);

	return read;
}

/*---------------------------------------------------------------------------
    Read Data from Eeprom
---------------------------------------------------------------------------*/
uint8_t ReadEeprom(uint16_t Address)
{
	uint8_t Out;

	EEPROM_CS_ON();
#ifdef    FM25L04B	
	if(Address & 0x0100) spiTransferByte(READ_EEPROM | 0x08);
     else spiTransferByte(READ_EEPROM);
	//spiTransferByte(ADDRESS_HIGH(Address));
	spiTransferByte(ADDRESS_LOW(Address));
	Out = spiTransferByte(DUMMY_EEPROM);
#else
     spiTransferByte(READ_EEPROM);
	spiTransferByte(ADDRESS_HIGH(Address));
	spiTransferByte(ADDRESS_LOW(Address));
	Out = spiTransferByte(DUMMY_EEPROM);
#endif	
	EEPROM_CS_OFF();

	return Out;
}

/*---------------------------------------------------------------------------
    Address Write Data to Eeprom
---------------------------------------------------------------------------*/
void WriteEeprom(uint16_t Address, uint8_t Data)
{
	EEPROM_CS_ON();
#ifdef    FM25L04B
     if(Address & 0x0100) spiTransferByte(WRITE_EEPROM | 0x08);
     else spiTransferByte(WRITE_EEPROM);
	//spiTransferByte(ADDRESS_HIGH(Address));
	spiTransferByte(ADDRESS_LOW(Address));
	spiTransferByte(Data);
#else	
     spiTransferByte(WRITE_EEPROM);
	spiTransferByte(ADDRESS_HIGH(Address));
	spiTransferByte(ADDRESS_LOW(Address));
	spiTransferByte(Data);
#endif     
	EEPROM_CS_OFF();

	while(ReadStatusRegisterEeprom() & 0x01);
}

/*---------------------------------------------------------------------------
    Page Write Data to Eeprom
---------------------------------------------------------------------------*/
void PWriteEeprom(uint8_t Page, uint8_t *StartAddr)
{
	uint16_t Address,n;
	Address = Page * 64;

	EEPROM_CS_ON();

	spiTransferByte(WRITE_EEPROM);
	spiTransferByte(ADDRESS_HIGH(Address));
	spiTransferByte(ADDRESS_LOW(Address));
	for(n=0;n<64;n++){
		spiTransferByte(StartAddr[n]);
	}

	EEPROM_CS_OFF();

	while(ReadStatusRegisterEeprom() & 0x01);
}

/*---------------------------------------------------------------------------
    Write Enable
---------------------------------------------------------------------------*/
void WriteEnableEeprom(void)
{
	EEPROM_CS_ON();

	spiTransferByte(WREN_EEPROM);

	EEPROM_CS_OFF();
}

/*---------------------------------------------------------------------------
    Write Disable
---------------------------------------------------------------------------*/
void WriteDisableEeprom(void)
{
	EEPROM_CS_ON();

	spiTransferByte(WRDI_EEPROM);

	EEPROM_CS_OFF();
}

/*---------------------------------------------------------------------------
    Read Status Register from Eeprom
---------------------------------------------------------------------------*/
uint8_t ReadStatusRegisterEeprom(void)
{
	uint8_t Out;

	EEPROM_CS_ON();

	spiTransferByte(RDSR_EEPROM);
	Out = spiTransferByte(DUMMY_EEPROM);

	EEPROM_CS_OFF();

	return Out;
}

/*---------------------------------------------------------------------------
	Proto Type :	void WriteStatusRegisterEeprom(Uint state_register)
	Function   : 	Write Status Register
	Parameta   : 	state_register
					x--- ---- ; SRWD is don't care in our case
					-000 ---- ; Not Used
					---- 0--- ; Clear BP1
					---- -0-- ; Clear BP2
					---- --R- ; Write Enable Latch Bit,Read Only,Enable == 1
					---- ---R ; Write In Progress Bit,Read Only,Progress == 1
	Return     :	None
---------------------------------------------------------------------------*/
void WriteStatusRegisterEeprom(uint8_t StatusRegister)
{
	EEPROM_CS_ON();

	spiTransferByte(WRSR_EEPROM);
	spiTransferByte(StatusRegister);

	EEPROM_CS_OFF();

	while(ReadStatusRegisterEeprom() & 0x01);
}


void InitEeprom(void)
{

/*---------------------------------------------------------------------------
	1. WREN
---------------------------------------------------------------------------*/
	while(ReadStatusRegisterEeprom() & 0x01);
	
	WriteEnableEeprom();
	
/*---------------------------------------------------------------------------
	2. WRSR
	2.1 DISABLE PROTECT AREA BP0=0,BP1=0
---------------------------------------------------------------------------*/
	WriteStatusRegisterEeprom(STATUS_REG_EEPROM);
}

float ApiVersionEeprom(void)
{
	float VersionTemp = FM25LV_API_VERSION;
	return VersionTemp;
}

uint16_t ApiVersionHexEeprom(void)
{
	uint16_t VersionTemp = FM25LV_API_VERSION_HEX;
	return VersionTemp;
}



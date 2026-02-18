/**
  ******************************************************************************
  * @file    BSP/BSP_evm2.c 
  * @author  Joonik Son
  * @version V1.0.0
  * @date    2024-02-01
  * @brief            
  ******************************************************************************
  * @Note



  * COPYRIGHT 2016 BIT Technology
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "includes.h"  

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Printf
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
	  
#define 	ADC1_DR_Address    ((uint32_t)0x4001244C)	

__IO		uint16_t 	ADCConvertedValue[5];
		uint16_t 	PrescalerValue = 0;
__IO		uint32_t  sEETimeout = sEE_LONG_TIMEOUT;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
		
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */ 
		
/******************************************************************************/
/*            Cortex-M3 Processor                                             */
/******************************************************************************/
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  GLCD_character((uint8_t) ch);
  
//  /* e.g. write a character to the USART */
//  
//  USART_SendData(USART2, (uint8_t) ch);
//
//  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
//  {}

  return ch;
}

int  putchar(int character)
{
     //if((c >= 0x20) && (c <= 0x7e))
  	GLCD_character(character);
     
     return character;
}

void TX1_char(uint8_t data)
{
	USART_SendData(USART1, data);
	
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  	{}
}

/**
  * @brief  .
  * @param  None
  * @retval None
  */

void DelayUS(uint16_t us)		// TIM3 is used
{
	TIM_SetCounter(TIM3, 0);
	
  	while(TIM_GetCounter(TIM3) <= us);
}

void DelayMS(uint16_t ms)
{
	register int i;
	for(i=0; i<ms; i++) DelayUS(1000);
}

void	Delay_us(uint32_t time_us)
{
  	register uint16_t i;
	for(i=0; i<time_us; i++) 
	{
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 5
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 10
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 15
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 20
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 25
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 30
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 35
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 40
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 45
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 50
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 55
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 60
		asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");		// 65
		asm("NOP"); 
	}
}

void	Delay_ms(uint32_t time_ms)
{
  	register	uint16_t	i;
	for(i=0; i<time_ms; i++)
	  	Delay_us(1000);
}


void	BSP_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef		TIM_OCInitStructure;
//	TIM_ICInitTypeDef		TIM_ICInitStructure;
//	TIM_BDTRInitTypeDef		TIM_BDTRInitStructure;

	USART_InitTypeDef		USART_InitStructure;
	ADC_InitTypeDef		ADC_InitStructure;
	DMA_InitTypeDef		DMA_InitStructure;
	
	SPI_InitTypeDef  SPI_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;
	DAC_InitTypeDef     DAC_InitStructure;	
//	CAN_InitTypeDef        CAN_InitStructure;
//	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

//	NVIC_InitTypeDef	NVIC_InitStructure;
              
     uint16_t	TimerPeriod = 0;
	TimerPeriod = TimerPeriod;		// prevent warning

	/* System Clocks Configuration */
	RCC_Configuration();
	
	/* GPIO Configuration */
     GPIO_Configuration();
     
     
    
	RCC_Configuration();
     GPIO_Configuration();
     
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------     
//	DMA1 channel1 configuration
// -----------------------------------------------------------------------------	
     DMA_DeInit(DMA1_Channel1);
     DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
     DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
     DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
     DMA_InitStructure.DMA_BufferSize = 5;
     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
     DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
     DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
     DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
     DMA_InitStructure.DMA_Priority = DMA_Priority_High;
     DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
     DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
     /* Enable DMA1 channel1 */
     DMA_Cmd(DMA1_Channel1, ENABLE);
// -----------------------------------------------------------------------------	
	
// -----------------------------------------------------------------------------     
//	ADC1 configuration 
// -----------------------------------------------------------------------------	
     // A/D input port
     GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_Init(GPIOC, &GPIO_InitStructure);
		
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
     ADC_InitStructure.ADC_ScanConvMode = ENABLE;
     ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
     ADC_InitStructure.ADC_NbrOfChannel = 5;
     ADC_Init(ADC1, &ADC_InitStructure);

     /* ADC1 regular channel configuration */ 
     ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);
     ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_55Cycles5);
     ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_55Cycles5);
     ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 5, ADC_SampleTime_55Cycles5);

     /* Enable ADC1 DMA */
     ADC_DMACmd(ADC1, ENABLE);
	
//	/* Enable ADC1 external trigger */ 
//	ADC_ExternalTrigConvCmd(ADC1, ENABLE);
//
//	/* Enable JEOC interrupt */
//	ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);
  
     /* Enable ADC1 */
     ADC_Cmd(ADC1, ENABLE);

     /* Enable ADC1 reset calibration register */   
     ADC_ResetCalibration(ADC1);
     /* Check the end of ADC1 reset calibration register */
     while(ADC_GetResetCalibrationStatus(ADC1));

     /* Start ADC1 calibration */
     ADC_StartCalibration(ADC1);
     /* Check the end of ADC1 calibration */
     while(ADC_GetCalibrationStatus(ADC1));
     
//	/* TIM1 counter enable */
//	TIM_Cmd(TIM1, ENABLE);
//	/* TIM1 main Output Enable */
//	TIM_CtrlPWMOutputs(TIM1, ENABLE);  
  
     /* Start ADC1 Software Conversion */ 
     ADC_SoftwareStartConvCmd(ADC1, ENABLE);
// -----------------------------------------------------------------------------	
  
 
// ------------------------------------------------------------------------
	// SPI1 configuration for FRAM
	// ------------------------------------------------------------------------
	// Configure SPI1 pins: SCK, MISO and MOSI 
  	// Confugure SCK and MOSI pins as Alternate Function Push Pull
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure SPI1 pins: nCS */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIOA->BSRR = GPIO_Pin_4;		// /CS High
	
	// SPI1 configuration
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	//SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	//SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	/* Enable SPI1 */
	SPI_Cmd(SPI1, ENABLE);
	// ------------------------------------------------------------------------	
     
     
// ------------------------------------------------------------------------
	// SPI2 configuration for ADS7871
	// ------------------------------------------------------------------------
	/* Configure SPI2 pins: SCK, MISO and MOSI ------------------------------*/
  	/* Confugure SCK and MOSI pins as Alternate Function Push Pull */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure SPI2 pins: nCS */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	//SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	//SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
     //SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
     SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
     //SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	/* Enable SPI2 */
	SPI_Cmd(SPI2, ENABLE);
	
	GPIOB->BSRR = GPIO_Pin_12;		// /CS High
	// ------------------------------------------------------------------------
     
// -----------------------------------------------------------------------------	
	/*!< Configure sEE_I2C pins: SCL */
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
     GPIO_Init(GPIOB, &GPIO_InitStructure);

     /*!< Configure sEE_I2C pins: SDA */
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
     GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	
	/*!< I2C configuration */
     /* sEE_I2C configuration */
     I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
     I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
     I2C_InitStructure.I2C_OwnAddress1 = 0xA0;
     I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
     I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
     //I2C_InitStructure.I2C_ClockSpeed = 400000;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
  
     /* sEE_I2C Peripheral Enable */
     I2C_Cmd(I2C1, ENABLE);
     /* Apply sEE_I2C configuration after enabling it */
     I2C_Init(I2C1, &I2C_InitStructure);
     /* Enable GPIO clock */
// -----------------------------------------------------------------------------     
  	
  
     /* USARTy and USARTz configuration --------------------------------------*/
  	/* USARTy and USARTz configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
  	USART_InitStructure.USART_BaudRate = 9600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	/* Configure USARTy */
  	USART_Init(USART1, &USART_InitStructure);
	USART_Init(USART2, &USART_InitStructure);
     	
     /* Configure USART Tx as alternate function push-pull */
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_2;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
     
     /* Configure USART Rx as input floating */
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_3;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  	/* Enable USARTy Receive and Transmit interrupts */
  	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
  	/* Enable the USARTy */
  	USART_Cmd(USART1, ENABLE);
	USART_Cmd(USART2, ENABLE);
	
	
     
// -----------------------------------------------------------------------------          
     /* Compute the prescaler value */
     PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;

// -----------------------------------------------------------------------------
// TIM2 Configuration for 20ms Task
// -----------------------------------------------------------------------------	
     /* Time2 configuration */
     TIM_TimeBaseStructure.TIM_Period = 20000;
     TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
     TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
     /* TIM enable counter */
     TIM_Cmd(TIM2, ENABLE);
     
     TIM_ClearFlag(TIM2, TIM_FLAG_Update);

     /* TIM IT enable */
     TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
// -----------------------------------------------------------------------------
//	TIM3 Configuration for Delay
// -----------------------------------------------------------------------------	
	/* Time3 configuration */
     TIM_TimeBaseStructure.TIM_Period = 20000;
     TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
     TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
     /* TIM enable counter */
     TIM_Cmd(TIM3, ENABLE);
// -----------------------------------------------------------------------------
	
	/* DAC channel1 Configuration */
     DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
     DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
     DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
     DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
     DAC_Init(DAC_Channel_1, &DAC_InitStructure);
     
     /* DAC channel2 Configuration */
     DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
     DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
     DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
     DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
     DAC_Init(DAC_Channel_2, &DAC_InitStructure);
     
     /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is 
     automatically connected to the DAC converter. */
     DAC_Cmd(DAC_Channel_1, ENABLE);
     
     /* Enable DAC Channel2: Once the DAC channel2 is enabled, PA.05 is 
     automatically connected to the DAC converter. */
     DAC_Cmd(DAC_Channel_2, ENABLE);
     
     /* Set DAC dual channel DHR12RD register */
//     DAC_SetDualChannelData(DAC_Align_12b_R, 0x100, 0x100);
     DAC_SetChannel1Data(DAC_Align_12b_R, 0);
     DAC_SetChannel2Data(DAC_Align_12b_R, 0);
// -----------------------------------------------------------------------------     
     
     /* NVIC Configuration */	
	NVIC_Configuration();   
	
	/* SysTick Configuration */
//  	SysTick_Configuration();
}

/**
  * @brief  Configures the SysTick.
  * @param  None
  * @retval None
  */
void SysTick_Configuration(void)
{
  /* Setup SysTick Timer for 0.1 msec interrupts  */
  if (SysTick_Config((SystemCoreClock) / 1000))		// for 1ms tick
  { 
    /* Capture error */ 
    while (1);
  }

   NVIC_SetPriority(SysTick_IRQn, 0x0);
}



/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

INT32U  BSP_CPU_ClkFreq (void)
{
    RCC_ClocksTypeDef  rcc_clocks;


    RCC_GetClocksFreq(&rcc_clocks);

    return ((INT32U)rcc_clocks.HCLK_Frequency);
}

/*
*********************************************************************************************************
*********************************************************************************************************
*                                         OS CORTEX-M3 FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         OS_CPU_SysTickClkFreq()
*
* Description : Get system tick clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : Clock frequency (of system tick).
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

INT32U  OS_CPU_SysTickClkFreq (void)
{
    INT32U  freq;


    freq = BSP_CPU_ClkFreq();
    return (freq);
}





void RCC_Configuration(void)
{
	
	/* ADCCLK = PCLK2/4 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);

	/* Enable peripheral clocks ---------------------------------------------*/
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// Enable DMA1 clock 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
     
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		
	/* Enable TIMx */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
     
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	// Enable TIM2 clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	// Enable TIM3 clock
     //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	// Enable TIM4 clock
     //RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);	// Enable TIM8 clock
     
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
	/*!< GPIO configuration */  
 	/* Configure PORTA */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PORTB Configure
	GPIO_InitStructure.GPIO_Pin = 0x0000;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// PORTC Configure
	GPIO_InitStructure.GPIO_Pin = (uint16_t)0xFC00;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
     
     // PORTD Configure
	GPIO_InitStructure.GPIO_Pin = (uint16_t)0xE3FF;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

     // PORTE Configure
	GPIO_InitStructure.GPIO_Pin = (uint16_t)0x0FF0;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
     
}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
void CAN_Configuration(void)
{
	
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
     NVIC_InitTypeDef NVIC_InitStructure;

     /* Enable the USART1 Interrupt */
     NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART2 Interrupt */
     NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the TIM2 Interrupt */
     NVIC_InitStructure.NVIC_IRQChannel =  TIM2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
	
//	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
//	NVIC_Init(&NVIC_InitStructure);
}



uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
  while (1)
  {   
  }
}


// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
void LED_ON(uint8_t	led)
{
     if(led == 0) GPIO_SetBits(GPIOE, GPIO_Pin_8); 			// turn on LED0
	else if(led == 1) GPIO_SetBits(GPIOE, GPIO_Pin_9); 		// turn on LED1
	else if(led == 2) GPIO_SetBits(GPIOE, GPIO_Pin_10); 		// turn on LED2
	else if(led == 3) GPIO_SetBits(GPIOE, GPIO_Pin_11); 		// turn on LED3
}

void LED_OFF(uint8_t led)
{
	if(led == 0) GPIO_ResetBits(GPIOE, GPIO_Pin_8);		     // turn off LED0
     else if(led == 1) GPIO_ResetBits(GPIOE, GPIO_Pin_9);	     // turn off LED1
	else if(led == 2) GPIO_ResetBits(GPIOE, GPIO_Pin_10);	     // turn 0ff LED2
	else if(led == 3) GPIO_ResetBits(GPIOE, GPIO_Pin_11);	     // turn 0ff LED3
}

void LED_TOGGLE(uint8_t led)
{
     if(led == 0) {GPIO_WriteBit(GPIOE, GPIO_Pin_8, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_8)));}		// toggle LED0
     else if(led == 1) {GPIO_WriteBit(GPIOE, GPIO_Pin_9, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_9)));}	// toggle LED1
     else if(led == 2) {GPIO_WriteBit(GPIOE, GPIO_Pin_10, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_10)));}	// toggle LED2
	else if(led == 3) {GPIO_WriteBit(GPIOE, GPIO_Pin_11, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_11)));}	// toggle LED3
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/**
 * @brief  Writes one byte to the IMU.
 * @param  slaveAddr : slave address IMU_DEFAULT_ADDRESS
 * @param  pBuffer : pointer to the buffer  containing the data to be written to the MPU6050.
 * @param  writeAddr : address of the register in which the data will be written
 * @return None
 */
void IMU_I2C_ByteWrite(u8 slaveAddr, u8* pBuffer, u8 writeAddr)
{
    // ENTR_CRT_SECTION();

    /* Send START condition */
    I2C_GenerateSTART(IMU_I2C, ENABLE);

    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_MODE_SELECT));

    /* Send MPU6050 address for write */
    I2C_Send7bitAddress(IMU_I2C, slaveAddr, I2C_Direction_Transmitter);

    /* Test on EV6 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    /* Send the MPU6050's internal address to write to */
    I2C_SendData(IMU_I2C, writeAddr);

    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    /* Send the byte to be written */
    I2C_SendData(IMU_I2C, *pBuffer);

    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    /* Send STOP condition */
    I2C_GenerateSTOP(IMU_I2C, ENABLE);

    // EXT_CRT_SECTION();
}

/**
 * @brief  Reads a block of data from the IMU.
 * @param  slaveAddr  : slave address
 * @param  pBuffer : pointer to the buffer that receives the data read from the IMU.
 * @param  readAddr : IMU's internal address to read from.
 * @param  NumByteToRead : number of bytes to read from the IMU.
 * @return None
 */
void IMU_I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead)
{
    // ENTR_CRT_SECTION();

    /* While the bus is busy */
    while (I2C_GetFlagStatus(IMU_I2C, I2C_FLAG_BUSY));

    /* Send START condition */
    I2C_GenerateSTART(IMU_I2C, ENABLE);

    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_MODE_SELECT));

    /* Send MPU6050 address for write */
    I2C_Send7bitAddress(IMU_I2C, slaveAddr, I2C_Direction_Transmitter);

    /* Test on EV6 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    /* Clear EV6 by setting again the PE bit */
    I2C_Cmd(IMU_I2C, ENABLE);

    /* Send the MPU6050's internal address to write to */
    I2C_SendData(IMU_I2C, readAddr);

    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    /* Send STRAT condition a second time */
    I2C_GenerateSTART(IMU_I2C, ENABLE);

    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_MODE_SELECT));

    /* Send MPU6050 address for read */
    I2C_Send7bitAddress(IMU_I2C, slaveAddr, I2C_Direction_Receiver);

    /* Test on EV6 and clear it */
    while (!I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    /* While there is data to be read */
    while (NumByteToRead)
    {
        if (NumByteToRead == 1)
        {
            /* Disable Acknowledgement */
            I2C_AcknowledgeConfig(IMU_I2C, DISABLE);

            /* Send STOP Condition */
            I2C_GenerateSTOP(IMU_I2C, ENABLE);
        }

        /* Test on EV7 and clear it */
        if (I2C_CheckEvent(IMU_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED))
        {
            /* Read a byte from the MPU6050 */
            *pBuffer = I2C_ReceiveData(IMU_I2C);

            /* Point to the next location where the byte read will be saved */
            pBuffer++;

            /* Decrement the read bytes counter */
            NumByteToRead--;
        }
    }

    /* Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(IMU_I2C, ENABLE);
    
    // EXT_CRT_SECTION();
}

void IMU_Init(void) 
{
  	uint8_t   tmp;
	uint8_t   temp[16];
  
  	I2C_Cmd(I2C1, DISABLE);
     I2C_Cmd(I2C1, ENABLE);
	Delay_ms(1);
	
	IMU_I2C_BufferRead(IMU_LIS3MDL, &tmp, WHO_AM_I, 1);
     if(tmp == 0x3D) {
                              //012345678901234567890
          GLCD_xy(7,0); printf("detected.            ");
       
     }
     else {
                              //012345678901234567890
          GLCD_xy(7,0); printf("Not detected.      ");
     }
  
  	tmp = LIS3MDL_ULTRAHIGHMODE | LIS3MDL_DATARATE_80_HZ;
     IMU_I2C_ByteWrite(IMU_LIS3MDL, &tmp, CTRL_REG1); 		
     
     tmp = LIS3MDL_RANGE_4_GAUSS;
     IMU_I2C_ByteWrite(IMU_LIS3MDL, &tmp, CTRL_REG2);
     
     tmp = LIS3MDL_CONTINUOUSMODE;
     IMU_I2C_ByteWrite(IMU_LIS3MDL, &tmp, CTRL_REG3);
	
	IMU_I2C_BufferRead(IMU_LIS3MDL, temp, OUT_X_L, 6);
     
     // Linear acceleration sensor control register
     //tmp = 0x4C;         // 104Hz, 8g
     tmp = 0x44;         // 104Hz, 16g 
     IMU_I2C_ByteWrite(IMU_LSM6DS3, &tmp, 0x10);
	IMU_I2C_BufferRead(IMU_LSM6DS3, temp, 0x22, 12);
	
     
     // Angular rate sensor control register
     //tmp = 0x44;         // 104Hz, 500dps
     tmp = 0x4C;         // 104Hz, 2000dps
     IMU_I2C_ByteWrite(IMU_LSM6DS3, &tmp, 0x11);
	
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


void AT24C16_write(uint16_t address, uint8_t byte)	// write a byte to AT24C16 
{
	I2C1->CR1 |= 0x0100;				// START condition
  	while(!(I2C1->SR1 & 0x0001));			// SB = 1 ?

  	I2C1->DR = 0xA0 + ((address >> 7) & 0x000E);	// write address
  	while(!(I2C1->SR1 & 0x0002));			// ADDR = 1 ?
  	while((I2C1->SR2 & 0x0003) != 0x0003);	// BUSY = MSL = 1 ?

  	I2C1->DR = address & 0x00FF;			// write address
  	while(!(I2C1->SR1 & 0x0080));			// TxE = 1 ?

  	I2C1->DR = byte;				// write data
  	while((I2C1->SR1 & 0x0084) != 0x0084);	// TxE = BTF = 1 ?

  	I2C1->CR1 |= 0x0200;				// STOP condition
  	Delay_ms(5);                                  // delay 5 ms for twr time
}

uint8_t AT24C16_read(uint16_t address)		// read a byte from AT24C16 
{
  	uint8_t byte;

  	I2C1->CR1 |= 0x0100;				// START condition
  	while(!(I2C1->SR1 & 0x0001));			// SB = 1 ?

  	I2C1->DR = 0xA0 + ((address >> 7) & 0x000E);	// write address
  	while(!(I2C1->SR1 & 0x0002));			// ADDR = 1 ?
  	while((I2C1->SR2 & 0x0003) != 0x0003);	// BUSY = MSL = 1 ?

  	I2C1->DR = address & 0x00FF;			// write address
  	while(!(I2C1->SR1 & 0x0080));			// TxE = 1 ?

  	I2C1->CR1 |= 0x0100;				// START condition
  	while(!(I2C1->SR1 & 0x0001));			// SB = 1 ?

  	I2C1->DR = 0xA1 + ((address >> 7) & 0x000E);	// write address
  	while(!(I2C1->SR1 & 0x0002));			// ADDR = 1 ?
  	while((I2C1->SR2 & 0x0003) != 0x0003);	// BUSY = MSL = 1 ?

  	while(!(I2C1->SR1 & 0x0040));			// RxNE = 1 ?
  	byte = I2C1->DR & 0x00FF;			// read data

  	I2C1->CR1 |= 0x0200;				// STOP condition
  	Delay_us(10);

  	return byte;                                  // return data
}



void wr_U16(uint16_t addr, uint16_t data)
{
  	addr =  addr * 2;

	AT24C16_write(addr, data & 0x0ff);
	AT24C16_write(addr + 1, (data>>8) & 0x0ff);
}

uint16_t rd_U16(uint16_t addr)
{
	uint16_t temp;
	
	addr =  addr * 2;
	temp = (AT24C16_read(addr + 1)<<8) + AT24C16_read(addr);
	  
	return temp;
}

//void wr_U16(uint16_t addr, uint16_t data)
//{
//    	addr =  addr*2;
//
//	WriteEnableEeprom();
//	WriteEeprom(addr, data & 0x0ff);
//	WriteEnableEeprom();
//	WriteEeprom(addr + 1, ((data>>8) & 0x0ff));
//}
//
//uint16_t rd_U16(uint16_t addr)
//{
//	uint16_t temp;
//
//	addr =  (addr*2);
//	temp = ((uint16_t)(ReadEeprom(addr + 1)<<8)) + (uint16_t)ReadEeprom(addr);
//
//	return temp;
//}

#define PCF8574_ADDRESS 0x70

uint32_t pcf8574Write(uint8_t data)
{
  /*!< While the bus is busy */
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  /* Start the config sequence */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on EV5 and clear it */
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Transmit the slave address and enable writing operation */
  I2C_Send7bitAddress(I2C1, PCF8574_ADDRESS, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Write data */
  I2C_SendData(I2C1, data);

  /* Test on EV8 and clear it */
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));

  /* End the configuration sequence */
  I2C_GenerateSTOP(I2C1, ENABLE);  
  
  return 0;  
}

// -----------------------------------------------------------------------------

int16_t TC75_Read_Temperature(uint8_t TC75address)
{
	int8_t data1, data2;
	
	I2C_start(I2C1, TC75address, I2C_Direction_Transmitter);
	I2C_write(I2C1,0x00);
	I2C_stop(I2C1); 
	I2C_start(I2C1, TC75address, I2C_Direction_Receiver);
	data1 = I2C_read_ack(I2C1);
	data2 = I2C_read_nack(I2C1);
	return (((int16_t)data1<<8) + (int16_t)data2);
}

void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction)
{
 	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
 	I2C_GenerateSTART(I2Cx, ENABLE);
 	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)) ;
 	I2C_Send7bitAddress(I2Cx, address, direction);
 	if (direction == I2C_Direction_Transmitter) {
 		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
 	}
 	else if(direction == I2C_Direction_Receiver) {
 		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
 	}
}

void I2C_write(I2C_TypeDef* I2Cx, uint8_t data)
{
 	I2C_SendData(I2Cx, data);
 	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}
void I2C_stop(I2C_TypeDef* I2Cx)
{
 	I2C_GenerateSTOP(I2Cx, ENABLE);
}

int8_t I2C_read_ack(I2C_TypeDef* I2Cx)
{
 	int8_t data;
 
 	I2C_AcknowledgeConfig(I2Cx, ENABLE);
 	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
 	data = I2C_ReceiveData(I2Cx);
 
 	return data;
}

int8_t I2C_read_nack(I2C_TypeDef* I2Cx)
{
 	uint8_t data;
 
 	I2C_AcknowledgeConfig(I2Cx, DISABLE);
 	I2C_GenerateSTOP(I2Cx, ENABLE);
 	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
 	data = I2C_ReceiveData(I2Cx);
 
 	return data;
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    Exmaple/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x_it.h>
    
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


//------------------------------------------------------------------------------

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
    
extern    OS_EVENT	*Sync;
extern    OS_EVENT	*SyncBuzz;    
    
/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
  //OS_CPU_PendSVHandler();
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)                      // 1ms
{
     // 1ms system tick handler
  //OS_CPU_SysTickHandler();
  
  //GPIO_WriteBit(GPIOC, GPIO_Pin_12, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_12)));              // for led
	
  
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles USARTy global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
 	INT8U c, err;
  
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		c = USART_ReceiveData(USART1); 
		CommPutRxChar(COMM1,c); 
	}
  
	if(USART_GetITStatus(USART1, USART_IT_TXE) == SET)
	{   
		c = CommGetTxChar(COMM1,&err);		
		if(err == COMM_TX_EMPTY) {
			// disable TXEIE(Transmit Data Register Empty Interrupt) 
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		} else {
			// send a byte
			USART_SendData(USART1, c); 
		}      
	}
}

void USART2_IRQHandler(void)
{
	INT8U c, err;
  
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		c = USART_ReceiveData(USART2); 
		CommPutRxChar(COMM2,c); 
	}
  
	if(USART_GetITStatus(USART2, USART_IT_TXE) == SET)
	{   
		c = CommGetTxChar(COMM2,&err);		
		if(err == COMM_TX_EMPTY) {
			// disable TXEIE(Transmit Data Register Empty Interrupt) 
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		} else {
			// send a byte
			USART_SendData(USART2, c); 
		}      
	}
}

void USART3_IRQHandler(void)
{
	
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
  	//int i;
  	
//	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
//	
//	write_CanRxFIFO(&can_rxFIFO, &RxMessage);
	
	
//	if(RxMessage.IDE == CAN_ID_STD) {
//		write_canFIFO(&RxCanFIFO, &RxMessage);
//		
//	}

}

/**
  * @brief  This function handles TIM2 interrupts request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)         // every 20 ms
{
	static    int16_t   tick = 0;
     
     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	    
     tick++;
     if(tick > 49) {
//          OSSemPost(Sync); 
//          OSSemPost(SyncBuzz);
          tick = 0;
     }
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

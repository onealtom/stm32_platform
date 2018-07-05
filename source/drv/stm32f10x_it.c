/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : stm32f10x_it.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Main Interrupt Service Routines.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Header.h"
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"
#include "usb_lib.h"
#include "usb_istr.h"
//#include "hw_config.h"

static uint8_t tmp_tx_buf[200];
static int cur_cnt=0;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
	Timer100msHandle();
	AdcStartExConv();
	uwTick++;
}


void TIM2_IRQHandler(void)
{
	uint16_t capture = 0;
	//__IO uint16_t CCR1_Val = 40961;
	__IO uint16_t CCR1_Val = 60000;
	__IO uint16_t CCR2_Val = 27309;
	__IO uint16_t CCR3_Val = 13654;
	__IO uint16_t CCR4_Val = 6826;
	static unsigned int iCnt;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

		/* Pin PC.06 toggling with frequency = 73.24 Hz */
		//GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6)));
		capture = TIM_GetCapture1(TIM2);
		TIM_SetCompare1(TIM2, capture + CCR1_Val);
		/*flush output*/
		//if( cur_cnt >0 ){
		//	route_txframe(tmp_tx_buf, cur_cnt );
		//	cur_cnt=0;
		//}
		if(iCnt>500){
			iCnt=0;
			printf("5s \n");
		}else{
			iCnt++;
		}
	}

}

/**
  * @brief  This function handles ADC1 and ADC2 global interrupts requests.
  * @param  None
  * @retval : None
  */
void ADC1_2_IRQHandler(void)
{
	/* Clear ADC1 JEOC pending interrupt bit */
	ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
	SaveExAdcResult();
#if 0
	/* Get injected channel10 and channel11 converted value */
	ADC_InjectedConvertedValueTab[Index++] = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
	ADC_InjectedConvertedValueTab[Index++] = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);

	if (Index == 32)
	{
		Index = 0;
	}
#endif
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

#ifndef STM32F10X_CL
/*******************************************************************************
* Function Name  : USB_LP_CAN1_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  USB_Istr();
}
#endif /* STM32F10X_CL */

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
	UINT16 tmp;
}


/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{
	UINT16 tmp;
	
	if (USART_GetITStatus(COM_CONTROL, USART_IT_RXNE) != RESET)
	{
		/* Send the received data to the PC Host*/
		////UartReceInterrupt((UCHAR8)USART_ReceiveData(COM_CONTROL));
		USART_ClearITPendingBit(COM_CONTROL, USART_IT_RXNE);
	}

	/* If overrun condition occurs, clear the ORE flag and recover communication */  
	if (USART_GetITStatus(COM_CONTROL, USART_IT_TXE) != RESET)
	{
		////UartTransInterrupt();
		USART_ClearITPendingBit(COM_CONTROL, USART_IT_TXE);
	}

	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
	{
//printf("ov");
		tmp = USART2->SR;
		tmp = USART2->DR;
		uart_ctl_ore_count++;
	}
}


/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{

	while(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		//cur_cnt++;
		/* Read one byte from the receive data register */
		printf("%x ",  USART_ReceiveData(USART3) );
		//tmp_tx_buf[cur_cnt-1] = USART_ReceiveData(USART3);
		
		
		//if(cur_cnt>=192){
		//	route_txframe(tmp_tx_buf, cur_cnt );
		//	cur_cnt=0;
		//}
	}

}


/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{

TRACE_INFO_WP(" UART4\r\n");

#if 0
	UINT16 tmp;
	//TRACE_INFO_WP(" UART4\r\n");
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		/* Send the received data to the PC Host*/
		ThrUartIsrRxDat((UCHAR8)USART_ReceiveData(UART4));
		//UartReceInterrupt((UCHAR8)USART_ReceiveData(UART4));
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}

	/* If overrun condition occurs, clear the ORE flag and recover communication */  
	if (USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
	{
		//ThrUartTxInterrupt();
		//ThrUartTxInterrupt();
		ThrUartIsrTxReady();
		USART_ClearITPendingBit(UART4, USART_IT_TXE);
	}

	if (USART_GetITStatus(UART4, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_TC);
		ThrUartIsrTxComplete();
	}

	
	if (USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)
	{
		tmp = UART4->SR;
		tmp = UART4->DR;
	}
#endif
}


#ifdef STM32F10X_CL
/*******************************************************************************
* Function Name  : OTG_FS_IRQHandler
* Description    : This function handles USB-On-The-Go FS global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void OTG_FS_IRQHandler(void)
{
  STM32_PCD_OTG_ISR_Handler(); 
}
#endif /* STM32F10X_CL */

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/*******************************************************************************
* Function Name  : PPP_IRQHandler
* Description    : This function handles PPP interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*void PPP_IRQHandler(void)
{
}*/

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/



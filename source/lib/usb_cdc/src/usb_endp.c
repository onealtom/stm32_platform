/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_endp.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Endpoint routines
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
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
//#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if 0
uint8_t USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
extern  uint8_t USART_Rx_Buffer[];
extern uint32_t USART_Rx_ptr_out;
extern uint32_t USART_Rx_length;
#endif
extern uint8_t  USB_Tx_State;
extern uint8_t  USB_Rx_State;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback (void)
{
	static uint8_t last_trans_bytes=0;
	uint8_t * tx_ptr;
	uint16_t tx_length;
	Transfer * pTransfer = &TxTransfer;

	if (USB_Tx_State == 1)
	{
		if ( VIRTUAL_COM_PORT_DATA_SIZE!=last_trans_bytes)		// 若最后发的数据长度小于缓冲长度，则判断是否完成传输
		{
			if ( pTransfer->remaining==0 )
			{
				USB_Tx_State = 0;
				
				if (pTransfer->fCallback != 0) 
				{
					((TransferCallback) pTransfer->fCallback)
						(pTransfer->pArgument, 0, pTransfer->transferred, 0);
				}
				last_trans_bytes = 0;
				return;
			}
		}

		if (pTransfer->remaining > VIRTUAL_COM_PORT_DATA_SIZE)
		{
			tx_length = VIRTUAL_COM_PORT_DATA_SIZE;
		}
		else
		{
			tx_length = pTransfer->remaining;
		}
		last_trans_bytes = tx_length;	// 记录最后发送的包长度
		USB_Tx_State = 1; 

		tx_ptr = pTransfer->pData;
		pTransfer->pData += tx_length;
		pTransfer->remaining -= tx_length;

		UserToPMABufferCopy(tx_ptr, ENDP1_TXADDR, tx_length);
		SetEPTxCount(ENDP1, tx_length);
		SetEPTxValid(ENDP1); 
		//USB_SIL_Write(EP1_IN, tx_ptr, tx_length);  
	}

#if 0
  if (USB_Tx_State == 1)
  {
    if (USART_Rx_length == 0) 
    {
      USB_Tx_State = 0;
    }
    else 
    {
      if (USART_Rx_length > VIRTUAL_COM_PORT_DATA_SIZE){
        USB_Tx_ptr = USART_Rx_ptr_out;
        USB_Tx_length = VIRTUAL_COM_PORT_DATA_SIZE;
        
        USART_Rx_ptr_out += VIRTUAL_COM_PORT_DATA_SIZE;
        USART_Rx_length -= VIRTUAL_COM_PORT_DATA_SIZE;    
      }
      else 
      {
        USB_Tx_ptr = USART_Rx_ptr_out;
        USB_Tx_length = USART_Rx_length;
        
        USART_Rx_ptr_out += USART_Rx_length;
        USART_Rx_length = 0;
      }
      
#ifdef USE_STM3210C_EVAL
      USB_SIL_Write(EP1_IN, &USART_Rx_Buffer[USB_Tx_ptr], USB_Tx_length);  
#else
      UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
      SetEPTxCount(ENDP1, USB_Tx_length);
      SetEPTxValid(ENDP1); 
#endif  
    }
  }
 #endif
}

/*******************************************************************************
* Function Name  : EP3_OUT_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP3_OUT_Callback(void)
{
//	uint16_t USB_Rx_Cnt;
	Transfer * pTransfer = &RxTransfer;

	/* Get the received data buffer and update the counter */
	pTransfer->transferred = USB_SIL_Read(EP3_OUT, pTransfer->pData);

	USB_Rx_State = 0;

	if (pTransfer->fCallback != 0) 
	{
		((TransferCallback) pTransfer->fCallback)
			(pTransfer->pArgument, 0, pTransfer->transferred, 0);
	}

#if 0
	/* USB data will be immediately processed, this allow next USB traffic beeing 
	NAKed till the end of the USART Xfet */
	USB_To_USART_Send_Data(USB_Rx_Buffer, USB_Rx_Cnt);

#ifndef STM32F10X_CL
	/* Enable the receive of data on EP3 */
	SetEPRxValid(ENDP3);
#endif /* STM32F10X_CL */
#endif
}


/*******************************************************************************
* Function Name  : SOF_Callback / INTR_SOFINTR_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
#ifdef STM32F10X_CL
void INTR_SOFINTR_Callback(void)
#else
void SOF_Callback(void)
#endif /* STM32F10X_CL */
{
  static uint32_t FrameCount = 0;
  
  if(bDeviceState == CONFIGURED)
  {
    if (FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL)
    {
      /* Reset the frame counter */
      FrameCount = 0;
      
      /* Check the data to be sent through IN pipe */
      Handle_USBAsynchXfer();
    }
  }  
}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/


/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : hw_config.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_it.h"
//#include "usb_lib.h"
//#include "usb_prop.h"
//#include "usb_desc.h"
//#include "hw_config.h"
#include "platform_config.h"
//#include "usb_pwr.h"
//#include "stm32_eval.h"
#include "Header.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
USART_InitTypeDef USART_InitStructure;

uint8_t  USART_Rx_Buffer [USART_RX_DATA_SIZE]; 
uint32_t USART_Rx_ptr_in = 0;
uint32_t USART_Rx_ptr_out = 0;
uint32_t USART_Rx_length  = 0;

Transfer RxTransfer;
Transfer TxTransfer;

T_USB_RECE_DAT g_rx_dat = {{0X00}, NULL, NULL, NULL, 0X00, 0X00};
T_USB_RECE_DAT g_tx_dat = {{0x00}, NULL, NULL, NULL, 0X00, 0X00};

uint8_t  USB_Tx_State = 0;
uint8_t  USB_Rx_State = 0;
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
/* Extern variables ----------------------------------------------------------*/

extern LINE_CODING linecoding;
/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : 配置USB时钟为48MHz
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
	/* Select USBCLK source */
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
	//RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);

	/* Enable the USB clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
	/* Set the device state to suspend */
	bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
	DEVICE_INFO *pInfo = &Device_Info;

	/* Set the device state to the correct state */
	if (pInfo->Current_Configuration != 0)
	{
		/* Device configured */
		bDeviceState = CONFIGURED;
	}
	else
	{
		bDeviceState = ATTACHED;
	}
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

#ifdef STM32F10X_CL 
	/* Enable the USB Interrupts */
	NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#else
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif /* STM32F10X_CL */
}

/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable
* Input          : None.
* Return         : Status
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
    g_rx_dat.p_dat = g_rx_dat.dat;
    g_rx_dat.p_head = (T_USB_PACKET_HEAD*)g_rx_dat.dat;
    g_tx_dat.p_dat = g_tx_dat.dat;
    g_tx_dat.p_head = (T_USB_PACKET_HEAD*)g_tx_dat.dat;

	
#ifdef USE_STM3210C_EVAL  
  if (NewState != DISABLE)
  {
    USB_DevConnect();
  }
  else
  {
    USB_DevDisconnect();
  }
#else /* USE_STM3210B_EVAL or USE_STM3210E_EVAL */
  if (NewState != DISABLE)
  {
    GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
  }
  else
  {
    GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
  }
#endif /* USE_STM3210C_EVAL */
}

//#define EVAL_COM1 USART1
/*******************************************************************************
* Function Name  : USB_To_USART_Send_Data.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
* Return         : none.
*******************************************************************************/
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes)
{
	//TRACE_INFO("USB_To_USART\r\n")

  #if 0
  uint32_t i;
  return;
  for (i = 0; i < Nb_bytes; i++)
  {
    USART_SendData(EVAL_COM1, *(data_buffer + i));
    while(USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TXE) == RESET); 
  }  
  #endif
}

/*******************************************************************************
* Function Name  : Handle_USBAsynchXfer.
* Description    : send data to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
void Handle_USBAsynchXfer (void)
{
#if 0
	uint16_t USB_Tx_ptr;
	uint16_t USB_Tx_length;

	if(USB_Tx_State != 1)
	{
		if (USART_Rx_ptr_out == USART_RX_DATA_SIZE)
		{
			USART_Rx_ptr_out = 0;
		}

		if(USART_Rx_ptr_out == USART_Rx_ptr_in) 
		{
			USB_Tx_State = 0; 
			return;
		}

		if(USART_Rx_ptr_out > USART_Rx_ptr_in) /* rollback */
		{ 
			USART_Rx_length = USART_RX_DATA_SIZE - USART_Rx_ptr_out;
		}
		else 
		{
			USART_Rx_length = USART_Rx_ptr_in - USART_Rx_ptr_out;
		}

		if (USART_Rx_length > VIRTUAL_COM_PORT_DATA_SIZE)
		{
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
		USB_Tx_State = 1; 

#ifdef USE_STM3210C_EVAL
		USB_SIL_Write(EP1_IN, &USART_Rx_Buffer[USB_Tx_ptr], USB_Tx_length);  
#else
		UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
		SetEPTxCount(ENDP1, USB_Tx_length);
		SetEPTxValid(ENDP1); 
#endif
	}  
#endif
}
/*******************************************************************************
* Function Name  : UART_To_USB_Send_Data.
* Description    : send the received data from UART 0 to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
void USART_To_USB_Send_Data(void)
{
	//TRACE_INFO("USART_To_USB\r\n")
  #if 0
  if (linecoding.datatype == 7)
  {
    USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(EVAL_COM1) & 0x7F;
  }
  else if (linecoding.datatype == 8)
  {
    USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(EVAL_COM1);
  }
  
  USART_Rx_ptr_in++;
  
  /* To avoid buffer overflow */
  if(USART_Rx_ptr_in == USART_RX_DATA_SIZE)
  {
    USART_Rx_ptr_in = 0;
  }
  #endif
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

//  Device_Serial0 = *(__IO uint32_t*)(0x1FFFF7E8);
//  Device_Serial1 = *(__IO uint32_t*)(0x1FFFF7EC);
//  Device_Serial2 = *(__IO uint32_t*)(0x1FFFF7F0);

 // Device_Serial0 += Device_Serial2;
	Device_Serial0 = 0x20120101;
	Device_Serial1 = 0x0000F5A2;

  if (Device_Serial0 != 0)
  {
    IntToUnicode (Device_Serial0, &Virtual_Com_Port_StringSerial[2] , 8);
    IntToUnicode (Device_Serial1, &Virtual_Com_Port_StringSerial[18], 4);
  }
}

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;
  
  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2* idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2* idx] = (value >> 28) + 'A' - 10; 
    }
    
    value = value << 4;
    
    pbuf[ 2* idx + 1] = 0;
  }
}

/*******************************************************************************
* Function Name  : CDCDSerialDriver_Write.
* Description    : USB虚拟串口发送函数
* Input          : 	
* 				data-数据指针
*				size-数据字节长度
*				callback-回调函数
*				argument-自定义回调参数
* Output         : None.
* Return         : 0-成功,1-失败
*******************************************************************************/
unsigned char CDCDSerialDriver_Write(void * pData,
                                     unsigned int dLength,
                                     TransferCallback fCallback,
                                     void * argument)
{
	uint8_t * tx_ptr;
	uint16_t tx_length;
	Transfer * pTransfer = &TxTransfer;
	
	if(USB_Tx_State == 1)
	{
		return 1;
	}
	
	// Setup the transfer descriptor.
	pTransfer->pData = (void *) pData;
	pTransfer->remaining = dLength;
	pTransfer->buffered = 0;
	pTransfer->transferred = 0;
	pTransfer->fCallback = fCallback;
	pTransfer->pArgument = argument;

	if (pTransfer->remaining > VIRTUAL_COM_PORT_DATA_SIZE)
	{
		tx_length = VIRTUAL_COM_PORT_DATA_SIZE;
	}
	else
	{
		tx_length = pTransfer->remaining;
	}

	USB_Tx_State = 1; 

	tx_ptr = pTransfer->pData;
	pTransfer->pData += tx_length;
	pTransfer->remaining -= tx_length;
	
//	USB_SIL_Write(EP1_IN, tx_ptr, tx_length);  
	UserToPMABufferCopy(tx_ptr, ENDP1_TXADDR, tx_length);
	SetEPTxCount(ENDP1, tx_length);
	SetEPTxValid(ENDP1); 
	
 	return 0;
	
}

unsigned char CDCDSerialDriver_Read(void *pData,
                                    unsigned int dLength,
                                    TransferCallback fCallback,
                                    void *argument)
{

	Transfer * pTransfer = &RxTransfer;

	if(USB_Rx_State == 1)
	{
		return 1;
	}

	pTransfer->pData = pData;
	pTransfer->remaining = dLength;
	pTransfer->buffered = 0;
	pTransfer->transferred = 0;
	pTransfer->fCallback = fCallback;
	pTransfer->pArgument = argument;

	USB_Rx_State = 1;
	
	SetEPRxValid(ENDP3);

	return 0;
}

void InitUsb()
{
	USB_Rx_State = 0;
	USB_Tx_State = 0;
	//TRACE_INFO("Set_USBClock\r\n");
	Set_USBClock();
	
	//TRACE_INFO("USB_Interrupts_Config\r\n");
	USB_Interrupts_Config();
	
	//TRACE_INFO("USB_Init\r\n");
	USB_Init();

}

void UsbConnect()
{
	GPIO_InitTypeDef gpio_usb_dp = PINS_DP_CONNECT;
	
	GPIO_Init( GPIOA, &gpio_usb_dp ); 
}

void UsbDisConnect()
{
	GPIO_InitTypeDef gpio_usb_dp = PINS_DP;
	
	GPIO_Init( GPIOA, &gpio_usb_dp ); 
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, DISABLE);
}

// 检查USB是否连接
UCHAR8 IsUsbConnected()
{
	if ( 1==GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_13))
	{
		return 1;
	}
	else
	{
		return 0;  
	}
}

// 检查USB是否已枚举完成，可以开始使用
UCHAR8 IsUsbConfigured()
{
	if ( bDeviceState != CONFIGURED ) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/


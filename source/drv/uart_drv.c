#include "Header.h"

_T_THR_FUNC thr_func;
volatile UINT16 uart_ctl_ore_count = 0;
volatile UINT16 uart_thr_ore_count = 0;

void EnableCtrlUartInt(UINT16 int_en)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */  
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_CTL_INT_PRIORITY;

	if ( 0!=int_en)
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	}
	else
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	}
	NVIC_Init(&NVIC_InitStructure);
}

/*************************************************************
Name:InitControlUart (RS1)         
Description: 初始化控制串口(485-A)
Input:波特率          
Output:void         
Return:void         
**************************************************************/
void InitControlUart(UINT32 baudrate)
{

	UINT16 tmp;
	USART_InitTypeDef uart_cfg;
	// 使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART2, &uart_cfg );

	USART_Cmd(USART2, ENABLE);

	RS485A_RX_MODE;
	tmp = USART_ReceiveData(USART2);
	tmp = USART_ReceiveData(USART2);
	EnableCtrlUartInt(1); 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	// 使能接收中断



}

void InitDebugUart( UINT32 baudrate )
{
	USART_InitTypeDef uart_cfg; 

//	RS485B_TX_MODE;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	USART_StructInit( &uart_cfg );  

	uart_cfg.USART_BaudRate = baudrate; 
	
	USART_Init( USART1 , &uart_cfg );

	USART_Cmd(USART1 , ENABLE);  
	
}

void EnableCtrlUartTxIT()
{
	USART_ITConfig(COM_CONTROL, USART_IT_TXE, ENABLE);	// 使能发送中断
}

void DisableCtrlUartTxIT()
{
	USART_ITConfig(COM_CONTROL, USART_IT_TXE, DISABLE);	// 禁止发送中断
}

void CtrlUartSendDat( UCHAR8 dat )
{
	USART_SendData(COM_CONTROL, dat);
}

void ThrUartSendDat( UCHAR8 dat )
{
	USART_SendData(COM_THR, dat);
}

/*************************************************************
Name:EnableUartTx          
Description:UART TX使能    
Input:1:使能，0:禁能            
Output:void         
Return:void         
**************************************************************/
void EnableUartTx(UCHAR8 flag, UCHAR8 ch_head)
{
	UINT16 i=0;
	
	if (0!=flag)
	{	
		RS485A_TX_MODE;
		UsNopDelay(10);
		CtrlUartSendDat(ch_head);
		EnableCtrlUartTxIT();
	}
	else
	{
		#if 0
		while( USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET )		// 等待发送完成
		{
			UsNopDelay(1);
			if ( ++i>1500 )
			{
				break;
			}
		}
		#endif
		DisableCtrlUartTxIT();
//		UsNopDelay(10);
		RS485A_RX_MODE;
	}
}	
/*************************************************************
Name:EnableUartRx          
Description:UART RX使能    
Input:1:使能，0:禁能            
Output:void         
Return:void         
**************************************************************/
void EnableUartRx(UCHAR8 flag)
{
#if 0
	if (flag)
	{	
		USART_SetReceiverEnabled(AT91C_BASE_US1, 1);
		AT91C_BASE_US1->US_IER = AT91C_US_RXRDY;			
	}
	else
	{
		USART_SetReceiverEnabled(AT91C_BASE_US1, 0);
		AT91C_BASE_US1->US_IDR = AT91C_US_RXRDY;	
	}
#endif	
}




#if 1

UCHAR8 ThrUart_Init( UINT16 port_flag, UINT16 baud_set)
{
	UINT32 baudrate = 9600;
	
	switch( baud_set )
	{
	case 0:	baudrate = 9600;		break;
	case 1:	baudrate = 19200;		break;
	case 2:	baudrate = 38400;		break;
	case 3:	baudrate = 57600;		break;
	case 4:	baudrate = 115200;	break;
	default:break;
	//return 0;
	}
	
	if ( port_flag==0 )	// 485-B做透传
	{
		//thr_func.pf_init = Uart4_Init;
		//thr_func.pf_send_byte = Uart4_SendDat;
		//thr_func.pf_ie_tx_ready = Uart4_IE_TxReady;
		//thr_func.pf_ie_tx_complete = Uart4_IE_TxComplete;
		//thr_func.pf_ie_rx_dat = Uart4_IE_RxDat;
		//thr_func.pf_tx_start = Uart4_TxStart;
 		//thr_func.pf_tx_finish = Uart4_TxFinish;

		thr_func.pf_init = Uart3_Init;
		thr_func.pf_send_byte = Uart3_SendDat;
		thr_func.pf_ie_tx_ready = Uart3_IE_TxReady;
		thr_func.pf_ie_tx_complete = Uart3_IE_TxComplete;
		thr_func.pf_ie_rx_dat = Uart3_IE_RxDat;
		thr_func.pf_tx_start = Uart3_TxStart;
 		thr_func.pf_tx_finish = Uart3_TxFinish;
	}
	else 
	{  
	
	  #ifdef NOTRACE
		thr_func.pf_init = Uart1_Init;
		thr_func.pf_send_byte = Uart1_SendDat;
		thr_func.pf_ie_tx_ready = Uart1_IE_TxReady;
		thr_func.pf_ie_tx_complete = Uart1_IE_TxComplete;
		thr_func.pf_ie_rx_dat = Uart1_IE_RxDat;
		thr_func.pf_tx_start = Uart1_TxStart;
 		thr_func.pf_tx_finish = Uart1_TxFinish;
 	  #else
 	  {
 	  	thr_func.pf_init = Uart3_Init;
		thr_func.pf_send_byte = Uart3_SendDat;
		thr_func.pf_ie_tx_ready = Uart3_IE_TxReady;
		thr_func.pf_ie_tx_complete = Uart3_IE_TxComplete;
		thr_func.pf_ie_rx_dat = Uart3_IE_RxDat;
		thr_func.pf_tx_start = Uart3_TxStart;
 		thr_func.pf_tx_finish = Uart3_TxFinish;
 	  }
	  #endif
	}

	thr_func.pf_init(baudrate);
}

void ThrUartIntDisable()
{
#ifdef NOTRACE
	if(sys_param_1b[MADD_THR_PORT].val)
	{
		Uart1_EnableInterrupt(0);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);	// 禁能时钟
	}
	else
	{
		Uart3_EnableInterrupt(0);
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);	// 禁能时钟
	}
#else
	Uart3_EnableInterrupt(0);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);	// 禁能时钟
#endif
	


}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Uart1_EnableInterrupt(UINT16 int_en)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_THR_INT_PRIORITY;

	if ( 0!=int_en)
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	}
	else
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	}
	NVIC_Init(&NVIC_InitStructure);
}

/*************************************************************
Name:InitThrUart (RS0)          
Description: 初始化透传串口(Debug Uart)
Input:波特率          
Output:void         
Return:void         
**************************************************************/
void Uart1_Init(UINT32 baudrate)
{
	USART_InitTypeDef uart_cfg;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_DeInit(USART1);
	
	Uart1_EnableInterrupt(0);
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);	// 禁能接收中断

	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART1, &uart_cfg );

	USART_Cmd(USART1, ENABLE);

	USART_ReceiveData(USART1);
	
	Uart1_EnableInterrupt(1);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	// 使能接收中断
	
}


// 发送缓冲空中断使能
void Uart1_IE_TxReady( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig( USART1, USART_IT_TXE, DISABLE );	// 禁止发送缓冲空中断
	}
	else
	{
		USART_ITConfig( USART1, USART_IT_TXE, ENABLE );	// 使能发送缓冲空中断
	}
}

// 发送完成中断使能
void Uart1_IE_TxComplete( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig( USART1, USART_IT_TC, DISABLE );	// 禁止发送完成中断
	}
	else
	{
		USART_ITConfig( USART1, USART_IT_TC, ENABLE );	// 使能发送完成中断
	}
}

// 接收中断使能
void Uart1_IE_RxDat( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig( USART1, USART_IT_RXNE, DISABLE );	// 禁止发送中断
	}
	else
	{
		USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );	// 使能发送完成中断
	}
}

// 启动发送
void Uart1_TxStart( void )
{
	Uart1_IE_TxReady(1);	// 使能发送缓冲空中断
}

// 写入数据到发送缓冲
void Uart1_SendDat( UCHAR8 dat )
{
	USART_SendData( USART1, dat );		// 发送数数据
	Uart1_IE_TxReady(1);
}

// 发送结束
void Uart1_TxFinish( void )
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Uart3_EnableInterrupt(UINT16 int_en)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_THR_INT_PRIORITY;

	if ( 0!=int_en)
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	}
	else
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	}
	NVIC_Init(&NVIC_InitStructure);
}

/*************************************************************
Name:InitThrUart (RS0)          
Description: 初始化透传串口(485-B)
Input:波特率          
Output:void         
Return:void         
**************************************************************/
void Uart3_Init(UINT32 baudrate)
{

#if 0
	UINT16 tmp;
	USART_InitTypeDef uart_cfg;
	// 使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	USART_DeInit(USART3);
	
	Uart3_EnableInterrupt(0);
	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	// 禁能接收中断

	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART3, &uart_cfg );

	USART_Cmd(USART3, ENABLE);

	RS485B_RX_MODE;
	tmp = USART_ReceiveData(USART3);
	tmp = USART_ReceiveData(USART3);
	Uart3_EnableInterrupt(1);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// 使能接收中断
#endif

#if 0
	UINT16 tmp;
	USART_InitTypeDef uart_cfg;

	// 使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART3, &uart_cfg );

	USART_Cmd(USART3, ENABLE);

	//RS485B_RX_MODE;
	tmp = USART_ReceiveData(USART3);
	tmp = USART_ReceiveData(USART3);
	Uart3_EnableInterrupt(1); 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// 使能接收中断
#endif

	UINT16 tmp;
	USART_InitTypeDef uart_cfg;
	// 使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	USART_DeInit(USART3);
	
	Uart3_EnableInterrupt(0);
	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	// 禁能接收中断

	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART3, &uart_cfg );

	USART_Cmd(USART3, ENABLE);

	//RS485B_RX_MODE;
	tmp = USART_ReceiveData(USART3);
	tmp = USART_ReceiveData(USART3);
	Uart3_EnableInterrupt(1);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// 使能接收中断
	
}

// 发送缓冲空中断使能
void Uart3_IE_TxReady( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(USART3, USART_IT_TXE, DISABLE);	// 禁止发送缓冲空中断
	}
	else
	{
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE);	// 使能发送缓冲空中断
	}
}

// 发送完成中断使能
void Uart3_IE_TxComplete( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(USART3, USART_IT_TC, DISABLE);	// 禁止发送完成中断
	}
	else
	{
		USART_ITConfig(USART3, USART_IT_TC, ENABLE);	// 使能发送完成中断
	}
}

// 接收中断使能
void Uart3_IE_RxDat( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	// 禁止发送中断
	}
	else
	{
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// 使能发送完成中断
	}
}

// 启动发送
void Uart3_TxStart( void )
{
	//RS485B_TX_MODE;
	UsNopDelay(10);		// 延时
	Uart3_IE_TxReady(1);	// 使能发送缓冲空中断
}

// 写入数据到发送缓冲
void Uart3_SendDat( UCHAR8 dat )
{
//	USART_SendData(USART3, dat);		// 发送数数据
	//RS485B_TX_MODE;
	UsNopDelay(5);		// 延时
	USART_SendData(USART3, dat);		// 发送数数据
	Uart3_IE_TxReady(1);
}

// 发送结束
void Uart3_TxFinish( void )
{
	UsNopDelay(10);		// 延时
	//RS485B_RX_MODE;
}


/*************************************************************
Name:         Uart1_EnableInterrupt 
Description:  串口1的中断控制
Input:        int_en : 0 - 失能
                       1 - 使能
Output:       void           
Return:       void         
**************************************************************/
void Uart4_EnableInterrupt(UINT16 int_en)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_THR_INT_PRIORITY;

	if ( 0!=int_en)
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	}
	else
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	}
	NVIC_Init(&NVIC_InitStructure);
}

/*************************************************************
Name:InitThrUart (RS0)          
Description: 初始化透传串口(485-B)
Input:波特率          
Output:void         
Return:void         
**************************************************************/
void Uart4_Init(UINT32 baudrate)
{
	UINT16 tmp;
	USART_InitTypeDef uart_cfg;
	// 使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	USART_DeInit(UART4);
	
	Uart4_EnableInterrupt(0);
	USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);	// 禁能接收中断
//	USART_ITConfig(UART4, USART_IT_ORE, DISABLE);	// 禁能接收中断
	
	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( UART4, &uart_cfg );

	USART_Cmd(UART4, ENABLE);

	RS485B_RX_MODE;
	tmp = USART_ReceiveData(UART4);
	tmp = USART_ReceiveData(UART4);
	Uart4_EnableInterrupt(1);
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	// 使能接收中断
//	USART_ITConfig(UART4, USART_IT_ORE, ENABLE);		// 使能接收中断
	
}


/*************************************************************
Name:         Uar4_EnableTxIT 
Description:  串口4的发送中断控制
Input:        int_en : 0 - 失能
                       1 - 使能
Output:       void           
Return:       void         
**************************************************************/
void Uart4_EnableTxIT( UINT16 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(UART4, USART_IT_TC, DISABLE);	// 禁止发送中断
	}
	else
	{

		USART_ITConfig(UART4, USART_IT_TC, ENABLE);	// 使能发送完成中断
	}
}


/*************************************************************
Name:         Uart4_SendDat 
Description:  串口4发送数据
Input:        dat : 发送的数据 
Output:       void           
Return:       void         
**************************************************************/
void Uart4_SendDat( UCHAR8 dat )
{

	RS485B_TX_MODE;	//GPIO_SetBits(GPIOC, GPIO_Pin_12);		// 485发送模式
	UsNopDelay(5);	// 延时
	USART_SendData(UART4, dat);		// 发送数数据
	Uart4_EnableTxIT(1);
}


// 启动发送
void Uart4_TxStart( void )
{
	RS485B_TX_MODE;
	UsNopDelay(10);		// 延时
	Uart4_IE_TxReady(1);	// 使能发送缓冲空中断
}

// 发送缓冲空中断使能
void Uart4_IE_TxReady( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig( UART4, USART_IT_TXE, DISABLE );	// 禁止发送缓冲空中断
	}
	else
	{
		USART_ITConfig( UART4, USART_IT_TXE, ENABLE );	// 使能发送缓冲空中断
	}
}

// 接收中断使能
void Uart4_IE_RxDat( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);	// 禁止发送中断
	}
	else
	{
		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	// 使能发送完成中断
	}
}
// 发送完成中断使能
void Uart4_IE_TxComplete( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(UART4, USART_IT_TC, DISABLE);	// 禁止发送完成中断
	}
	else
	{
		USART_ITConfig(UART4, USART_IT_TC, ENABLE);	// 使能发送完成中断
	}
}

// 发送结束
void Uart4_TxFinish( void )
{
	UsNopDelay(10);		// 延时
	RS485B_RX_MODE;
}


#endif



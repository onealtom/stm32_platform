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
Description: ��ʼ�����ƴ���(485-A)
Input:������          
Output:void         
Return:void         
**************************************************************/
void InitControlUart(UINT32 baudrate)
{

	UINT16 tmp;
	USART_InitTypeDef uart_cfg;
	// ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART2, &uart_cfg );

	USART_Cmd(USART2, ENABLE);

	RS485A_RX_MODE;
	tmp = USART_ReceiveData(USART2);
	tmp = USART_ReceiveData(USART2);
	EnableCtrlUartInt(1); 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	// ʹ�ܽ����ж�



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
	USART_ITConfig(COM_CONTROL, USART_IT_TXE, ENABLE);	// ʹ�ܷ����ж�
}

void DisableCtrlUartTxIT()
{
	USART_ITConfig(COM_CONTROL, USART_IT_TXE, DISABLE);	// ��ֹ�����ж�
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
Description:UART TXʹ��    
Input:1:ʹ�ܣ�0:����            
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
		while( USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET )		// �ȴ��������
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
Description:UART RXʹ��    
Input:1:ʹ�ܣ�0:����            
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
	
	if ( port_flag==0 )	// 485-B��͸��
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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);	// ����ʱ��
	}
	else
	{
		Uart3_EnableInterrupt(0);
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);	// ����ʱ��
	}
#else
	Uart3_EnableInterrupt(0);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);	// ����ʱ��
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
Description: ��ʼ��͸������(Debug Uart)
Input:������          
Output:void         
Return:void         
**************************************************************/
void Uart1_Init(UINT32 baudrate)
{
	USART_InitTypeDef uart_cfg;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_DeInit(USART1);
	
	Uart1_EnableInterrupt(0);
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);	// ���ܽ����ж�

	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART1, &uart_cfg );

	USART_Cmd(USART1, ENABLE);

	USART_ReceiveData(USART1);
	
	Uart1_EnableInterrupt(1);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	// ʹ�ܽ����ж�
	
}


// ���ͻ�����ж�ʹ��
void Uart1_IE_TxReady( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig( USART1, USART_IT_TXE, DISABLE );	// ��ֹ���ͻ�����ж�
	}
	else
	{
		USART_ITConfig( USART1, USART_IT_TXE, ENABLE );	// ʹ�ܷ��ͻ�����ж�
	}
}

// ��������ж�ʹ��
void Uart1_IE_TxComplete( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig( USART1, USART_IT_TC, DISABLE );	// ��ֹ��������ж�
	}
	else
	{
		USART_ITConfig( USART1, USART_IT_TC, ENABLE );	// ʹ�ܷ�������ж�
	}
}

// �����ж�ʹ��
void Uart1_IE_RxDat( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig( USART1, USART_IT_RXNE, DISABLE );	// ��ֹ�����ж�
	}
	else
	{
		USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );	// ʹ�ܷ�������ж�
	}
}

// ��������
void Uart1_TxStart( void )
{
	Uart1_IE_TxReady(1);	// ʹ�ܷ��ͻ�����ж�
}

// д�����ݵ����ͻ���
void Uart1_SendDat( UCHAR8 dat )
{
	USART_SendData( USART1, dat );		// ����������
	Uart1_IE_TxReady(1);
}

// ���ͽ���
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
Description: ��ʼ��͸������(485-B)
Input:������          
Output:void         
Return:void         
**************************************************************/
void Uart3_Init(UINT32 baudrate)
{

#if 0
	UINT16 tmp;
	USART_InitTypeDef uart_cfg;
	// ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	USART_DeInit(USART3);
	
	Uart3_EnableInterrupt(0);
	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	// ���ܽ����ж�

	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART3, &uart_cfg );

	USART_Cmd(USART3, ENABLE);

	RS485B_RX_MODE;
	tmp = USART_ReceiveData(USART3);
	tmp = USART_ReceiveData(USART3);
	Uart3_EnableInterrupt(1);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ʹ�ܽ����ж�
#endif

#if 0
	UINT16 tmp;
	USART_InitTypeDef uart_cfg;

	// ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART3, &uart_cfg );

	USART_Cmd(USART3, ENABLE);

	//RS485B_RX_MODE;
	tmp = USART_ReceiveData(USART3);
	tmp = USART_ReceiveData(USART3);
	Uart3_EnableInterrupt(1); 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ʹ�ܽ����ж�
#endif

	UINT16 tmp;
	USART_InitTypeDef uart_cfg;
	// ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	USART_DeInit(USART3);
	
	Uart3_EnableInterrupt(0);
	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	// ���ܽ����ж�

	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( USART3, &uart_cfg );

	USART_Cmd(USART3, ENABLE);

	//RS485B_RX_MODE;
	tmp = USART_ReceiveData(USART3);
	tmp = USART_ReceiveData(USART3);
	Uart3_EnableInterrupt(1);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ʹ�ܽ����ж�
	
}

// ���ͻ�����ж�ʹ��
void Uart3_IE_TxReady( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(USART3, USART_IT_TXE, DISABLE);	// ��ֹ���ͻ�����ж�
	}
	else
	{
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE);	// ʹ�ܷ��ͻ�����ж�
	}
}

// ��������ж�ʹ��
void Uart3_IE_TxComplete( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(USART3, USART_IT_TC, DISABLE);	// ��ֹ��������ж�
	}
	else
	{
		USART_ITConfig(USART3, USART_IT_TC, ENABLE);	// ʹ�ܷ�������ж�
	}
}

// �����ж�ʹ��
void Uart3_IE_RxDat( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	// ��ֹ�����ж�
	}
	else
	{
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ʹ�ܷ�������ж�
	}
}

// ��������
void Uart3_TxStart( void )
{
	//RS485B_TX_MODE;
	UsNopDelay(10);		// ��ʱ
	Uart3_IE_TxReady(1);	// ʹ�ܷ��ͻ�����ж�
}

// д�����ݵ����ͻ���
void Uart3_SendDat( UCHAR8 dat )
{
//	USART_SendData(USART3, dat);		// ����������
	//RS485B_TX_MODE;
	UsNopDelay(5);		// ��ʱ
	USART_SendData(USART3, dat);		// ����������
	Uart3_IE_TxReady(1);
}

// ���ͽ���
void Uart3_TxFinish( void )
{
	UsNopDelay(10);		// ��ʱ
	//RS485B_RX_MODE;
}


/*************************************************************
Name:         Uart1_EnableInterrupt 
Description:  ����1���жϿ���
Input:        int_en : 0 - ʧ��
                       1 - ʹ��
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
Description: ��ʼ��͸������(485-B)
Input:������          
Output:void         
Return:void         
**************************************************************/
void Uart4_Init(UINT32 baudrate)
{
	UINT16 tmp;
	USART_InitTypeDef uart_cfg;
	// ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	USART_DeInit(UART4);
	
	Uart4_EnableInterrupt(0);
	USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);	// ���ܽ����ж�
//	USART_ITConfig(UART4, USART_IT_ORE, DISABLE);	// ���ܽ����ж�
	
	USART_StructInit( &uart_cfg );

	uart_cfg.USART_BaudRate = baudrate;
	
	USART_Init( UART4, &uart_cfg );

	USART_Cmd(UART4, ENABLE);

	RS485B_RX_MODE;
	tmp = USART_ReceiveData(UART4);
	tmp = USART_ReceiveData(UART4);
	Uart4_EnableInterrupt(1);
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	// ʹ�ܽ����ж�
//	USART_ITConfig(UART4, USART_IT_ORE, ENABLE);		// ʹ�ܽ����ж�
	
}


/*************************************************************
Name:         Uar4_EnableTxIT 
Description:  ����4�ķ����жϿ���
Input:        int_en : 0 - ʧ��
                       1 - ʹ��
Output:       void           
Return:       void         
**************************************************************/
void Uart4_EnableTxIT( UINT16 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(UART4, USART_IT_TC, DISABLE);	// ��ֹ�����ж�
	}
	else
	{

		USART_ITConfig(UART4, USART_IT_TC, ENABLE);	// ʹ�ܷ�������ж�
	}
}


/*************************************************************
Name:         Uart4_SendDat 
Description:  ����4��������
Input:        dat : ���͵����� 
Output:       void           
Return:       void         
**************************************************************/
void Uart4_SendDat( UCHAR8 dat )
{

	RS485B_TX_MODE;	//GPIO_SetBits(GPIOC, GPIO_Pin_12);		// 485����ģʽ
	UsNopDelay(5);	// ��ʱ
	USART_SendData(UART4, dat);		// ����������
	Uart4_EnableTxIT(1);
}


// ��������
void Uart4_TxStart( void )
{
	RS485B_TX_MODE;
	UsNopDelay(10);		// ��ʱ
	Uart4_IE_TxReady(1);	// ʹ�ܷ��ͻ�����ж�
}

// ���ͻ�����ж�ʹ��
void Uart4_IE_TxReady( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig( UART4, USART_IT_TXE, DISABLE );	// ��ֹ���ͻ�����ж�
	}
	else
	{
		USART_ITConfig( UART4, USART_IT_TXE, ENABLE );	// ʹ�ܷ��ͻ�����ж�
	}
}

// �����ж�ʹ��
void Uart4_IE_RxDat( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);	// ��ֹ�����ж�
	}
	else
	{
		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	// ʹ�ܷ�������ж�
	}
}
// ��������ж�ʹ��
void Uart4_IE_TxComplete( UCHAR8 enable )
{
	if ( enable==0 )
	{
		USART_ITConfig(UART4, USART_IT_TC, DISABLE);	// ��ֹ��������ж�
	}
	else
	{
		USART_ITConfig(UART4, USART_IT_TC, ENABLE);	// ʹ�ܷ�������ж�
	}
}

// ���ͽ���
void Uart4_TxFinish( void )
{
	UsNopDelay(10);		// ��ʱ
	RS485B_RX_MODE;
}


#endif



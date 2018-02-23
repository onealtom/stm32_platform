/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司

*************************************************************
文件名：   UART_DRV_H_
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： UART_DRV_H_的底层驱动头文件 
函数列表：  
修改日期： 
        1.日期:      2010年08月05日  
          作者：     韦瑞锦 
          修改内容： 原版
        2.日期:      2012年04月17日  
          作者：     邓子谦
          修改内容： 微型光钎V02   
**************************************************************/


#ifndef _UART_DRV_H_
#define _UART_DRV_H_

#include "ex_conf.h"

typedef void (*LP_THR_INIT)(UINT32); 
typedef void (*LP_THR_SENDBYTE)(UCHAR8); 
typedef void (*LP_THR_IE_TX_READY)(UCHAR8); 
typedef void (*LP_THR_IE_TX_COMPLETE)(UCHAR8); 
typedef void (*LP_THR_IE_RX_DAT)(UCHAR8); 
typedef void (*LP_THR_TX_START)(void); 
typedef void (*LP_THR_TX_FINISH)(void); 

typedef struct {
	LP_THR_INIT 			pf_init;			// 初始化
	LP_THR_SENDBYTE 		pf_send_byte;		// 发送1字节
	LP_THR_IE_TX_READY 		pf_ie_tx_ready;		// 发送中断使能
	LP_THR_IE_TX_COMPLETE 	pf_ie_tx_complete;	// 发送中断使能
	LP_THR_IE_RX_DAT		pf_ie_rx_dat;		// 接收中断使能
	LP_THR_TX_START			pf_tx_start;		// 开始发送
	LP_THR_TX_FINISH		pf_tx_finish;		// 发送完成
} _T_THR_FUNC;
 
#define COM_CONTROL	(USART2)

#ifdef THR_USE_DEBUG_UART
#define COM_DEBUG		(void)
#define COM_THR			(USART1)
#else
#define COM_DEBUG		(USART1)
#define COM_THR			(USART3)
#endif

#define RS485A_TX_MODE		GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define RS485A_RX_MODE		GPIO_ResetBits(GPIOA, GPIO_Pin_1)

#define RS485B_TX_MODE		GPIO_SetBits(GPIOC, GPIO_Pin_12)
#define RS485B_RX_MODE		GPIO_ResetBits(GPIOC, GPIO_Pin_12)

// Variable
extern _T_THR_FUNC thr_func; 
extern volatile UINT16 uart_ctl_ore_count;
extern volatile UINT16 uart_thr_ore_count;


//function
void InitDebugUart( UINT32 baudrate );
void InitControlUart(UINT32 baudrate);
void InitThrUart(UINT32 baudrate);
void EnableUartTx(UCHAR8 flag, UCHAR8 ch_head);
UCHAR8 ThrUart_Init( UINT16 port_flag, UINT16 baud_set);
void ThrUartIntDisable();
void Uart1_EnableInterrupt(UINT16 int_en);
void Uart1_Init(UINT32 baudrate);
void Uart1_IE_TxReady( UCHAR8 enable );
void Uart1_IE_TxComplete( UCHAR8 enable );
void Uart1_IE_RxDat( UCHAR8 enable );
void Uart1_TxStart( void );
void Uart1_SendDat( UCHAR8 dat );
void Uart1_TxFinish( void );


void Uart3_EnableInterrupt(UINT16 int_en);
void Uart3_Init(UINT32 baudrate);
void Uart3_IE_TxReady( UCHAR8 enable );
void Uart3_IE_TxComplete( UCHAR8 enable );
void Uart3_IE_RxDat( UCHAR8 enable );
void Uart3_TxStart( void );
void Uart3_SendDat( UCHAR8 dat );
void Uart3_TxFinish( void );

void Uart4_EnableInterrupt(UINT16 int_en);
void Uart4_Init(UINT32 baudrate);
void Uart4_EnableTxIT( UINT16 enable );
void Uart4_SendDat( UCHAR8 dat );
void Uart4_TxStart( void );
void Uart4_IE_TxReady( UCHAR8 enable);
void Uart4_IE_RxDat( UCHAR8 enable );
void Uart4_IE_TxComplete( UCHAR8 enable );
void Uart4_TxFinish( void );




#endif

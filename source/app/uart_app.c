/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : uart_app.c
* Description : RS485接口操作, 485-A主控通讯端口, 485-B透传端口
* Version     :v0.1
* Author      :RJ
* Date        :2008-08-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*	RJ		2010-06-11	v0.1			初始版本
**************************************************************/

#include "Header.h"

extern UCHAR8 para_bak[];
extern _T_PARAM_1B sys_param_1b[];
extern _T_PARAM_2B sys_param_2b[];
extern _T_PARAM_4B sys_param_4b[];

extern _T_FP_INFO fp_inf[];		            // 光口拓扑信息
extern _T_VALID_FP_TOPO valid_fp_topo[FP_MAX];
extern _T_FP_INFO fp_inf[FP_MAX];
extern _T_RE_INFO tmp_re_inf[FP_MAX][RE_MAX];		// RE信息的临时缓存

////UCHAR8 uart_rx_buff[ UART_BUFF_SIZE ]; 
////UCHAR8 uart_tx_buff[ UART_BUFF_SIZE ]; 
////volatile UCHAR8 pc_tx_buff[ PC_BUFF_SIZE ];
UCHAR8 uart_rx_buff[ 1 ]; 
UCHAR8 uart_tx_buff[ 1 ]; 
volatile UCHAR8 pc_tx_buff[ 1 ];

UCHAR8 uart_test_tx_buff[20 ]; 
UCHAR8 uart_index=0; 
UCHAR8 uart_flag=0;


UCHAR8 re_trans_head_bk[4];		// 远程查询设置RE命令的485数据包头备份:type, ver, device, address
UCHAR8 re_trans_cmd = 0;	// 远程查询设置RE命令的子命令字
UCHAR8 re_trans_fp = 0;		// 远程查询设置RE命令的目的光口
UCHAR8 re_trans_node = 0;	// 远程查询设置RE命令的目的节点
UCHAR8 re_trans_rf = 0;	// 远程查询设置RE命令的目的射频节点

_T_UART_RECE uart_rece_info={0,0,uart_rx_buff,0};
_T_UART_TRANS uart_trans_info = {0,0,uart_tx_buff,0};
volatile _T_UART_TRANS pc_trans_info = {0,0,pc_tx_buff,0};
UCHAR8 trans_4e_flag = 0;		//接收时0X4E转义标志

//UCHAR8 rs485_rx_pkt_flag = 0;	// 485接收中断标志

// 透传FIFO使用双缓冲机制，收和发各用一个，每次发送完成后切换
_T_THR_FIFO uart_thr_tx_fifo[2];	// 透传串口发送FPGA接收FIFO
_T_THR_FIFO uart_thr_rx_fifo[2];	// 透传串口接收FPGA发送FIFO
UCHAR8 thr_utx_fifo_use;		// 标识透传串口发送使用的FIFO，FPGA接收使用另一个FIFO
UCHAR8 thr_urx_fifo_use;		// 标识透传串口接收使用的FIFO，FPGA发送使用另一个FIFO
UCHAR8 uart_thr_tx_end;		// 串口透传数据发送完成标志
UCHAR8 fpga_thr_tx_end;		// FPGA透传数据发送完成标志

// 复位透传FIFO及状态
void ResetThrFifo()
{

}

// 透传串口中断函数: 接收中断
void ThrUartIsrRxDat( UCHAR8 thr_dat )
{

}

// 透传串口中断函数: 发送就绪
void ThrUartIsrTxReady( void )
{

}

// 透传串口中断函数: 发送完成
void ThrUartIsrTxComplete( void )
{

}

/*************************************************************
Name:UartBTransTSW0      
Description:发送透传数据
Input:tsw0_dat:透传数据内容         
Output:void         
Return:void         
**************************************************************/
void UartTransThrDat()
{

}


//#ifdef HXCT_VER

/*************************************************************
Name:UartStartTrans          
Description:开始发送
Input:void            
Output:void         
Return:void         
**************************************************************/
void PcStartTrans(void)
{

}
/*************************************************************
Name:PcPacketTransHead          
Description:打包包头
Input:模块地址，命令字，应答标志            
Output:void         
Return:void         
**************************************************************/
void PcPacketTransHead(UCHAR8 *tx_buffer)
{

}






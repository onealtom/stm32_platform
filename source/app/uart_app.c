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
extern _T_MODULE_CFG mod_cfg_a;
extern UINT32 module_param_chg_flag;		//系统工作参数修改标志
extern _T_FP_INFO fp_inf[];		            // 光口拓扑信息
extern _T_VALID_FP_TOPO valid_fp_topo[FP_MAX];
extern _T_FP_INFO fp_inf[FP_MAX];
extern _T_RE_INFO tmp_re_inf[FP_MAX][RE_MAX];		// RE信息的临时缓存

UCHAR8 uart_rx_buff[ UART_BUFF_SIZE ]; 
UCHAR8 uart_tx_buff[ UART_BUFF_SIZE ]; 
volatile UCHAR8 pc_tx_buff[ PC_BUFF_SIZE ];
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
	memset( (UCHAR8*)uart_thr_tx_fifo, 0, sizeof(uart_thr_tx_fifo)*2 );
	thr_utx_fifo_use = 0;	// 串口发送使用FIFO区0
	memset( (UCHAR8*)uart_thr_rx_fifo, 0, sizeof(uart_thr_rx_fifo)*2 );
	thr_urx_fifo_use = 0;	// 串口接收使用FIFO区0
	uart_thr_tx_end = 1;	// 串口透传数据发送完成
	fpga_thr_tx_end = 1;	// FPGA透传数据发送完成
}

// 透传串口中断函数: 接收中断
void ThrUartIsrRxDat( UCHAR8 thr_dat )
{
	_T_THR_FIFO * p_fifo = &uart_thr_rx_fifo[thr_urx_fifo_use];	// FIFO指针

	// FIFO未满, 保存数据到FIFO, 数据计数+1
	if ( p_fifo->count < THR_FIFO_SIZE )	
	{
		p_fifo->p_dat[ p_fifo->count++ ] = thr_dat;	
	}

	//printf("s");
}

// 透传串口中断函数: 发送就绪
void ThrUartIsrTxReady( void )
{
	_T_THR_FIFO * p_fifo = &uart_thr_tx_fifo[thr_utx_fifo_use];	// FIFO指针
	UCHAR8 tmp;

	// FIFO中有数据则继续发送
	if ( p_fifo->count > 0 )
	{
		// 从FIFO取数据,读指针后移
		tmp = p_fifo->p_dat[ p_fifo->index++ ];
				
		// FIFO数据计数-1
		p_fifo->count --;

		// 数据写入串口发送缓冲
		thr_func.pf_send_byte( tmp );
	}

	// 缓冲中已无数据
	if ( 0 == p_fifo->count )
	{
		// 关闭发送缓冲空中断
		thr_func.pf_ie_tx_ready(0);
		
		// 使能发送完成中断
		thr_func.pf_ie_tx_complete(1);
	}

}

// 透传串口中断函数: 发送完成
void ThrUartIsrTxComplete( void )
{
	_T_THR_FIFO * p_fifo = &uart_thr_tx_fifo[thr_utx_fifo_use];	// FIFO指针

	// 关闭发送完成中断
	thr_func.pf_ie_tx_complete(0);
	
	// 缓冲中已无数据
	if ( 0 == p_fifo->count )
	{
		p_fifo->index = 0;
		
		// 发送完成，进入接收模式
		thr_func.pf_tx_finish();
		
		// 置发送完成标志
		uart_thr_tx_end = 1;
	}
	else	// 缓冲还有数据(!!!正常情况下不可能出现此情况)
	{
		// 使能发送缓冲空中断，继续发送
		thr_func.pf_ie_tx_ready(1);
	}
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
	_T_THR_FIFO * p_fifo;	// FIFO指针
	UCHAR8 fifo_id;

	// 得到FPGA接收使用的FIFO ID
	fifo_id = (0==thr_utx_fifo_use) ? 1 : 0;

	// FPGA接收FIFO的指针
	p_fifo = &uart_thr_tx_fifo[fifo_id];
	//TRACE_INFO("p_fifo->count---------[%x],thr_utx_fifo_use=[%x]\r\n",p_fifo->count,thr_utx_fifo_use);
	// 若FIFO不为空则切换FIFO并启动发送
	if ( 0 != p_fifo->count )
	{
		// FIFO交换，将FPGA接收FIFO作为串口的发送FIFO
		thr_utx_fifo_use = fifo_id;

		// 将之前的串口的发送FIFO作为FPGA的接收FIFO
		fifo_id = 1 - thr_utx_fifo_use;

		// 清空FPGA接收FIFO
		memset( (UCHAR8*)&(uart_thr_tx_fifo[fifo_id]), 0, sizeof(_T_THR_FIFO) );
		
		// 启动发送
		p_fifo->index = 0;
		uart_thr_tx_end = 0;
		thr_func.pf_tx_start();
	}
}


//#ifdef HXCT_VER
#if  0

/*************************************************************
Name:UartReceInterrupt          
Description:中断调用接收处理程序
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartReceInterrupt( UCHAR8 rx_dat )
{
	uart_rece_info.rx_data = rx_dat;
	
	WTD_CLR;
	if (0 != (sys_work_info&SYSTEM_FLAG_232_RECE))	// 上一笔包还没处理完
	{
		return;
	}

	//监控接口
	switch(uart_rece_info.rx_count)
	{
		//包头
		case 0:
			if (uart_rece_info.rx_data != 0x7E)
				return;
		break;	
		//模块编号
		case 1:
			if ( (uart_rece_info.rx_data != HXCT_DDF_MODULE_NUM)
				&&( uart_rece_info.rx_data != HXCT_DET_MODULE_NUM )
				&&( uart_rece_info.rx_data != HXCT_LNA_MODULE_NUM ) )
			{
				uart_rece_info.rx_count = 0;	
				return;
			}
			uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = uart_rece_info.rx_data;
		break;
		//命令体长度
		case 4:
			//收取数据长度高4位
			uart_rece_info.rx_len = (uart_rece_info.rx_data&0xf0)>>4;
			uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = uart_rece_info.rx_data;	// 应答标志
		break;
		
		case 5:
			//收取数据长度低8位
			uart_rece_info.rx_len = (uart_rece_info.rx_len<<8)|uart_rece_info.rx_data;
			uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = uart_rece_info.rx_data;
			if (uart_rece_info.rx_len > (UART_BUFF_SIZE-10))
			{
				uart_rece_info.rx_count = 0;
				return;
			}
		break;
		
		default:
			if ((uart_rece_info.rx_count>5) && (uart_rece_info.rx_count>=(uart_rece_info.rx_len+8)) 
				&& ((uart_rece_info.rx_data==0x7F)))
			{
				//数据收取完毕				
				uart_rece_info.rx_count = 0;
				sys_work_info |= SYSTEM_FLAG_232_RECE;
				return;
			}	
			else if (uart_rece_info.rx_count > 0 )
			{
				uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = uart_rece_info.rx_data;		
			}
			else
			{
				uart_rece_info.rx_count = 0;
				return;
			}
		break;					
			
	}
	uart_rece_info.rx_count++;
	if (uart_rece_info.rx_count > (UART_BUFF_SIZE-2))	// 数据过长,判定为无效数据包
		uart_rece_info.rx_count = 0;

}


/*************************************************************
Name:UartTransInterrupt          
Description:中断调用发送处理函数
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartTransInterrupt(void)
{
	//中断发生时上一个数据已经发送出去了
	if (uart_trans_info.tx_count<= uart_trans_info.tx_len)
	{
		CtrlUartSendDat( uart_trans_info.tx_buffer[uart_trans_info.tx_count++] );
	}
	else if (uart_trans_info.tx_count == uart_trans_info.tx_len+1)	// 多发送一个字符
	{	
		CtrlUartSendDat(0x00);
		uart_trans_info.tx_count++;
	}
	else
	{
		//延时后将485发送使能关闭			
		EnableUartTx(0, 0);	
		return;
	}

}
//#if 0
/*************************************************************
Name:UartStartTrans          
Description:开始发送
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartStartTrans(void)
{
	
	uart_trans_info.tx_count = 0;
	EnableUartTx(1, 0x7E);	
}
//#endif 
/*************************************************************
Name:UartPacketHXTransHead          
Description:打包包头
Input:模块地址，命令字，应答标志            
Output:void         
Return:void         
**************************************************************/
void UartPacketHXTransHead(UCHAR8 type,UCHAR8 address,UCHAR8 command,UCHAR8 ack,UINT16 len)
{
	uart_trans_info.tx_buffer[0] = type;	
	uart_trans_info.tx_buffer[1] = address;
	uart_trans_info.tx_buffer[2] = command;	
	uart_trans_info.tx_buffer[3] = ack|((len>>4)&0x00f0);
	uart_trans_info.tx_buffer[4] = (UCHAR8)len;
	uart_trans_info.tx_len = 5;	
}

/*************************************************************
Name:MonHXGetStatusPara
Description:表12		扩展ICS模块查询命令回应数据
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:数据长度
**************************************************************/
#ifdef HX_PROTOCOL_1230		// 虹信20111230协议
UINT16 MonHXGetStatusPara(UCHAR8 * data ,UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 * bak_data = data;
	UINT16 i;
	UCHAR8 tmp;
	UINT16 val;
	
	//开关状态(1字节)
	tmp = 0;
	if ( 0 != sys_param_1b[MADD_FPS_BCCH_LK_ST].val ) { tmp |= (1<<7); }	// 锁定BCCH是否成功,1-成功
	if ( 0 != sys_param_1b[MADD_FPS_MOSVC_LK_ST].val ) { tmp |= (1<<6); }	// 锁定运营商是否成功,1-成功
	if ( 0 != sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val ) { tmp |= (1<<5); }	// 锁定频段是否成功,1-成功
	if ( 0 != sys_param_1b[MADD_LOW_POWER].val ) { tmp |= (1<<3); }	// 低功耗开关,1-ON
	if (( 0==up_down )&&( 0!=sys_param_1b[(0==ab_flag) ? MADD_A_LTHR_EN : MADD_B_LTHR_EN].val ))
	{ 
		tmp |= (1<<2); 		// 底噪抑制使能开关,1-ON
	}
	if ( 0!=sys_param_1b[(0==ab_flag) ? MADD_A_UL_WORK_EN : MADD_B_UL_WORK_EN].val )
	{
		tmp |= (1<<0);		// 处理模块总开关, 1-ON
	}
	*data++ = tmp;

	//信道开关(4字节)
	for ( i=0; i<32; i++ )
	{
		if ( 0==(i%8) )
		{
			if ( i>0 )
			{
				*data++ = tmp;
			}
			tmp = 0;
		}
		tmp <<= 1;
		if ( 0!= sys_param_1b[(0==ab_flag) ? (MADD_A_DCH_EN32-i) : (MADD_B_DCH_EN32-i)].val )
		{
			tmp |= 1;	// 通道开关, 1-ON
		}
	}
	*data++ = tmp;

	// 工作状态(4字节)
	*data++ = 0;
	*data++ = 0;
	tmp = 0;
	for ( i=0; i<8; i++ )
	{
		tmp <<= 1;
		if ( 0 != sys_param_1b[MADD_FP8_LOF-i].val ) { tmp |= 1; }	// 光收发状态告警, 1-ALARM, RE只有光口1和2
	}
	*data++ = tmp;
	tmp = 0;
	if ( 0 != sys_param_1b[MADD_TOPO_CHG_ALM].val ) { tmp |= (1<<7); }		// 环路状态告警,1-ALARM
	if ( 0 != sys_param_1b[MADD_BER_ALARM].val ) { tmp |= (1<<6); }		// 误码率偏高告警,1-ALARM
	if ( 0 != sys_param_1b[MADD_CLK_PLL_ST].val ) { tmp |= (1<<4); }		// 时钟失锁,1-UNLOCK
	if ( 0 != sys_param_1b[MADD_FPGA_CLK_ST].val ) { tmp |= (1<<3); }		// FPGA本振状态,1-UNLOCK
	tmp |= (0x03 & sys_param_1b[MADD_LOAD_FPGA_ST].val );		// 模块初始化FPGA状态
	*data++ = tmp;

	//选频频段(1字节), 0:GSM,1:WCDMA
	if ( 0==ab_flag )
	{
		tmp = fpga_cfg.a_net_type;
	}
	else
	{
		if ( fpga_cfg.b_net_type == NET_DIVE )
		{
			tmp = fpga_cfg.a_net_type;
		}
		else
		{
			tmp = fpga_cfg.b_net_type;
		}
		
	}
	if (( tmp==NET_TYPE_GSM900 )||( tmp==NET_TYPE_DCS1800 ))
	{
		*data++ = 0;
	}
	else
	{
		*data++ = 1;
	}
	
	// 上行输出功率门限(2字节)
	val = sys_param_2b[(0==ab_flag) ? MADD_A_UCH_MAX_POW1 : MADD_B_UCH_MAX_POW1].val;
	*data++ = (UCHAR8)(val);
	*data++ = (UCHAR8)(val>>8);

	//输入功率(2字节)
	val = sys_param_2b[(0==ab_flag) ? MADD_A_DL_TOTAL_POW : MADD_B_DL_TOTAL_POW].val;
	*data++ = (UCHAR8)(val);
	*data++ = (UCHAR8)(val>>8);
	
	//输出功率(2字节)
	val = sys_param_2b[(0==ab_flag) ? MADD_A_UL_TOTAL_POW : MADD_B_UL_TOTAL_POW].val;
	*data++ = (UCHAR8)(val);
	*data++ = (UCHAR8)(val>>8);

	//ATT(1字节)
	if ( 0==up_down )
	{// 上行
		*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_UCH_ATT1 : MADD_B_UCH_ATT1].val;
	}
	else
	{// 下行
		*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_DCH_ATT1 : MADD_B_DCH_ATT1].val;
	}

	//噪声电平门限(1字节)
	*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_LTHR_DN: MADD_B_LTHR_DN].val;		// 上行底噪抑制下门限

	//功放增益(1字节)
	*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_DL_PA_GAIN: MADD_B_DL_PA_GAIN].val;		// 下行功放增益

	//双工器衰减(1字节)
	val = sys_param_2b[(0==ab_flag) ? MADD_A_UDPX_IN_GAIN: MADD_B_UDPX_IN_GAIN].val;		// 输入双工器衰减
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);
	val = sys_param_2b[(0==ab_flag) ? MADD_A_UDPX_OUT_GAIN: MADD_B_UDPX_OUT_GAIN].val;		// 输出双工器衰减
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);

	// 远端机节点状态
	*data++ = sys_param_1b[MADD_RE_NODE_MODE].val;

//#ifdef FUNC_FREQ_POINT_SEARCH_EN	// 启用频点搜索功能
	// 频点搜索相关参数 BCCH
	*data++ = sys_param_1b[MADD_FPS_RFRANGE_SEL].val;		// 频段选择
	*data++ = sys_param_1b[MADD_FPS_MOSVC_SEL].val;		// 运营商选择
	val = sys_param_2b[MADD_FPS_BCCH_FC_M].val;			// 主小区BCCH信道号
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);
	*data++ = sys_param_1b[MADD_FPS_BCCH_POW_M].val;		// 主小区BCCH接收强度
	val = sys_param_2b[MADD_FPS_CID].val;					// 小区识别码实时值
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);
	val = sys_param_2b[MADD_FPS_AREA_ID].val;				// 位置区编码
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);
	*data++ = sys_param_1b[MADD_FPS_BS_ID].val;			// 基站识别码
	for ( i=0; i<6; i++ )										// 邻小区BCCH信道号
	{
		val = sys_param_2b[MADD_FPS_BCCH_FC_1+i].val;			
		*data++ = (UCHAR8)(val&0xFF);
		*data++ = (UCHAR8)(val>>8);
	}
	for ( i=0; i<6; i++ )										// 邻小区BCCH接收强度
	{
		*data++ = sys_param_1b[MADD_FPS_BCCH_POW_1+i].val;
	}
	for ( i=0; i<6; i++ )										// 邻小区CID识别码
	{
		val = sys_param_2b[MADD_FPS_CID_1+i].val;	
		*data++ = (UCHAR8)(val&0xFF);
		*data++ = (UCHAR8)(val>>8);
	}

	//通道数N(1字节)+工作信道号(N*2字节)
	if ( 0==ab_flag )
	{
		tmp = sys_param_1b[MADD_A_CHANNEL_COUNT].val;
		*data++ = tmp;
		for ( i=0; i<tmp; i++ )
		{
			*data++ = (UCHAR8)(sys_param_2b[MADD_A_DL_CHANNEL1+i].val);
			*data++ = (UCHAR8)(sys_param_2b[MADD_A_DL_CHANNEL1+i].val>>8);
		}
	}
	else
	{
		tmp = sys_param_1b[MADD_B_CHANNEL_COUNT].val;
		*data++ = tmp;
		for ( i=0; i<tmp; i++ )
		{
			*data++ = (UCHAR8)(sys_param_2b[MADD_B_DL_CHANNEL1+i].val);
			*data++ = (UCHAR8)(sys_param_2b[MADD_B_DL_CHANNEL1+i].val>>8);
		}
	}

	// 频点搜索相关参数 CA
	*data++ = sys_param_1b[MADD_FPS_CA_COUNT].val;		// 有效信道数
	for ( i=0; i<sys_param_1b[MADD_FPS_CA_COUNT].val; i++ )		// CA信道号
	{
		val = sys_param_2b[MADD_FPS_CA_FC_0+i].val;			
		*data++ = (UCHAR8)(val&0xFF);
		*data++ = (UCHAR8)(val>>8);
	}

	return (data-bak_data);	
	
}
#else	// 虹信20110629协议
UINT16 MonHXGetStatusPara(UCHAR8 * data ,UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 * bak_data = data;
	UINT16 i;
	UCHAR8 tmp;
	
	//开关状态(1字节)
	tmp = 0;
	if ( 0 != sys_param_1b[MADD_LOW_POWER].val ) { tmp |= (1<<3); }	// 低功耗开关,1-ON
	if (( 0==up_down )&&( 0!=sys_param_1b[(0==ab_flag) ? MADD_A_LTHR_EN : MADD_B_LTHR_EN].val ))
	{ 
		tmp |= (1<<2); 		// 底噪抑制使能开关,1-ON
	}
	if ( 0!=sys_param_1b[(0==ab_flag) ? MADD_A_UL_WORK_EN : MADD_B_UL_WORK_EN].val )
	{
		tmp |= (1<<0);		// 处理模块总开关, 1-ON
	}
	*data++ = tmp;

	//信道开关(4字节)
	for ( i=0; i<32; i++ )
	{
		if ( 0==(i%8) )
		{
			if ( i>0 )
			{
				*data++ = tmp;
			}
			tmp = 0;
		}

		tmp <<= 1;
		if ( 0!= sys_param_1b[(0==ab_flag) ? (MADD_A_DCH_EN32-i) : (MADD_B_DCH_EN32-i)].val )
		{
			tmp |= 1;	// 通道开关, 1-ON
		}
	}
	*data++ = tmp;

	// 工作状态(4字节)
	*data++ = 0;
	*data++ = 0;
	tmp = 0;
	for ( i=0; i<8; i++ )
	{
		tmp <<= 1;
		if ( 0 != sys_param_1b[MADD_FP8_LOF-i].val ) { tmp |= 1; }	// 光收发状态告警, 1-ALARM
	}
	*data++ = tmp;
	tmp = 0;
	if ( 0 != sys_param_1b[MADD_TOPO_CHG_ALM].val ) { tmp |= (1<<7); }		// 环路状态告警,1-ALARM
	if ( 0 != sys_param_1b[MADD_BER_ALARM].val ) { tmp |= (1<<6); }		// 误码率偏高告警,1-ALARM
	if ( 0 != sys_param_1b[MADD_CLK_PLL_ST].val ) { tmp |= (1<<4); }		// 时钟失锁,1-UNLOCK
	if ( 0 != sys_param_1b[MADD_FPGA_CLK_ST].val ) { tmp |= (1<<3); }		// FPGA本振状态,1-UNLOCK
	tmp |= (0x03 & sys_param_1b[MADD_LOAD_FPGA_ST].val );		// 模块初始化FPGA状态
	*data++ = tmp;

	//选频频段(1字节), 0:GSM,1:WCDMA
	if ( 0==ab_flag )
	{
		tmp = fpga_cfg.a_net_type;
	}
	else
	{
		if ( fpga_cfg.b_net_type == NET_DIVE )
		{
			tmp = fpga_cfg.a_net_type;
		}
		else
		{
			tmp = fpga_cfg.b_net_type;
		}
		
	}
	if (( tmp==NET_TYPE_GSM900 )||( tmp==NET_TYPE_DCS1800 ))
	{
		*data++ = 0;
	}
	else
	{
		*data++ = 1;
	}
	
	// 上行输出功率门限(2字节)
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_UCH_MAX_POW1 : MADD_B_UCH_MAX_POW1].val);
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_UCH_MAX_POW1 : MADD_B_UCH_MAX_POW1].val>>8);

	//输入功率(2字节)
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_DL_TOTAL_POW : MADD_B_DL_TOTAL_POW].val);
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_DL_TOTAL_POW : MADD_B_DL_TOTAL_POW].val>>8);
	
	//输出功率(2字节)
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_UL_TOTAL_POW : MADD_B_UL_TOTAL_POW].val);
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_UL_TOTAL_POW : MADD_B_UL_TOTAL_POW].val>>8);

	//ATT(1字节)
	if ( 0==up_down )
	{// 上行
		*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_UCH_ATT1 : MADD_B_UCH_ATT1].val;
	}
	else
	{// 下行
		*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_DCH_ATT1 : MADD_B_DCH_ATT1].val;
	}

	//噪声电平门限(1字节)
	*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_LTHR_DN: MADD_B_LTHR_DN].val;		// 上行底噪抑制下门限

	//通道数N(1字节)+工作信道号(N*2字节)
	if ( 0==ab_flag )
	{
		tmp = sys_param_1b[MADD_A_CHANNEL_COUNT].val;
		*data++ = tmp;
		for ( i=0; i<tmp; i++ )
		{
			*data++ = (UCHAR8)(sys_param_2b[MADD_A_DL_CHANNEL1+i].val);
			*data++ = (UCHAR8)(sys_param_2b[MADD_A_DL_CHANNEL1+i].val>>8);
		}
	}
	else
	{
		tmp = sys_param_1b[MADD_B_CHANNEL_COUNT].val;
		*data++ = tmp;
		for ( i=0; i<tmp; i++ )
		{
			*data++ = (UCHAR8)(sys_param_2b[MADD_B_DL_CHANNEL1+i].val);
			*data++ = (UCHAR8)(sys_param_2b[MADD_B_DL_CHANNEL1+i].val>>8);
		}
	}

	return (data-bak_data);	
	
}
#endif

/*************************************************************
Name:MonHXGetSubPara
Description:扩展设置查询项的查询命令回复
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:数据长度
**************************************************************/
UINT16 MonHXGetSubPara(UCHAR8 * data ,UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 * bak_data = data;
	UINT16 i;
	UCHAR8 tmp;

	//光模块开关(2字节)
	*data++ = 0;		// 高8位无光模块，为0
	tmp = 0;
	for ( i=0; i<8; i++ )
	{
		tmp <<= 1;
		if ( 0 != sys_param_1b[MADD_FP8_EN-i].val ) { tmp |= 1; }	// 光模块开关, 1-ON
	}
	*data++ = tmp;

	//光模块个数(1字节)
	*data++ = FP_MAX;

	//通道数N(1字节)+通道增益值(N*1字节)
	if ( 0==ab_flag )
	{
		tmp = sys_param_1b[MADD_A_CHANNEL_COUNT].val;
		*data++ = tmp;
		for ( i=0; i<tmp; i++ )
		{
			*data++ = 0;		// REC不支持设置和查询通道增益值
		}
	}
	else
	{
		tmp = sys_param_1b[MADD_B_CHANNEL_COUNT].val;
		*data++ = tmp;
		for ( i=0; i<tmp; i++ )
		{
			*data++ = 0;
		}
	}

	//延时补偿(2字节)
	*data++ = 0;			// REC不支持设置和查询延时补偿
	*data++ = 0;

	//自动时延开关(1字节)
	*data++ = sys_param_1b[MADD_DELAY_MODE].val;		// 自动时延开关, 1-ON

	//Mcu温度(1字节)
	*data++ = sys_param_1b[MADD_BOARD_TEMP].val;

	//低功耗开关(1字节)
	*data++ = sys_param_1b[MADD_LOW_POWER].val;		// 低功耗开关,1-ON

	//自动/手动选频(1字节)
	*data++ = 0;		// 1：自动选频, 0：手动选频

	//上行时隙占用率(1字节)
	*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_BUSY_TIME : MADD_B_BUSY_TIME].val;
	
	//上行时隙占用率统计状态(1字节)
	*data++ = sys_param_1b[MADD_TRAFFIC_END].val;

	//设备路由登记地址(4字节)
	*data++ = (UCHAR8)(sys_param_4b[MADD_DEV_ADDR].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_DEV_ADDR].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_DEV_ADDR].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_DEV_ADDR].val>>24);

	//环网对端光口号1(4字节)
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>24);

	//环网对端光口号1(4字节)
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>24);

	//远端机节点计数1(4字节), 光口1-4
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT1].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT1].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT1].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT1].val>>24);

	//远端机节点计数2(4字节), 光口5-8
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT2].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT2].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT2].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT2].val>>24);

	//远端机节点计数3,4(2*4字节), 光口9-16
	for ( i=0; i<8; i++ )
	{
		*data++ = 0;
	}

	//远端机节点状态(1字节)
	*data++ = 0;		// REC无效

	//链路最大延时(2字节)
	*data++ = (UCHAR8)(sys_param_2b[MADD_MAX_T14].val);
	*data++ = (UCHAR8)(sys_param_2b[MADD_MAX_T14].val>>8);

	//节点光路延时(2字节)
	*data++ = 0;		// REC无效
	*data++ = 0;		// REC无效

	//节点光路延时(2字节)
	*data++ = 0;		// REC无效
	*data++ = 0;		// REC无效

	//WLAN网口1-4状态(4*1字节)
	*data++ = sys_param_1b[MADD_WLAN_CONN_ST1].val;
	*data++ = sys_param_1b[MADD_WLAN_CONN_ST2].val;
	*data++ = sys_param_1b[MADD_WLAN_CONN_ST3].val;
	*data++ = sys_param_1b[MADD_WLAN_CONN_ST4].val;

	//WLAN网口速度流量1-4(4*1字节)
	*data++ = sys_param_1b[MADD_WLAN_SPEED1].val;
	*data++ = sys_param_1b[MADD_WLAN_SPEED2].val;
	*data++ = sys_param_1b[MADD_WLAN_SPEED3].val;
	*data++ = sys_param_1b[MADD_WLAN_SPEED4].val;

	return (data-bak_data);	

}

/*************************************************************
Name:MonHXSetNormalPara
Description:扩展设置查询项的查询命令回复
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 MonHXSetNormalPara(UCHAR8 cmd, UCHAR8 * data , UINT16 body_len, UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 tmp;
	UINT16 addr;

	switch(cmd)
	{
	case HXCT_CMD_SET_ATT:		// ATT
		if ( 0==ab_flag )
		{
			addr = (0==up_down)? MADD_A_UCH_ATT1 : MADD_A_DCH_ATT1;
		}
		else
		{
			addr = (0==up_down)? MADD_B_UCH_ATT1 : MADD_B_DCH_ATT1;
		}
		if ( data[0] == sys_param_1b[addr].val )
		{
			return 2;
		}
		if ( VAL_IN_RANGE( data[0], 0, 31 ) )
		{
			sys_param_1b[addr].val = data[0]&0x7F;
			if ( 0==ab_flag )
			{
				module_param_chg_flag |= PCHG_A_POW_GAIN;//((0==up_down) ? PCHG_A_UL_GAIN : PCHG_A_DL_GAIN);	// 置修改参数标志
			}
			else
			{
				module_param_chg_flag |= PCHG_B_POW_GAIN;//((0==up_down) ? PCHG_A_UL_GAIN : PCHG_A_DL_GAIN);	// 置修改参数标志
			}
		}
		else
		{
			return 0;
		}
		//是否保存ATT
		if ( 0 != (data[0]&0x80) )	// 最高位等于1，此次设置的ATT参数值不用保存
		{
			return 2;
		}
	break;
	
	case HXCT_CMD_SET_ONOFF:		// 工作使能
		if ( data[0]>1 ) return 0;
		
		if ( 0==ab_flag )
		{
			if (( sys_param_1b[MADD_A_UL_WORK_EN].val != data[0] )||( sys_param_1b[MADD_A_DL_WORK_EN].val != data[0] ))
			{
				sys_param_1b[MADD_A_UL_WORK_EN].val = data[0];
				sys_param_1b[MADD_A_DL_WORK_EN].val = data[0];
				module_param_chg_flag |= PCHG_A_WORK_EN;
			}
			else
			{
				return 2;
			}
		}
		else
		{
			if (( sys_param_1b[MADD_B_UL_WORK_EN].val != data[0] )||( sys_param_1b[MADD_B_DL_WORK_EN].val != data[0] ))
			{
				sys_param_1b[MADD_B_UL_WORK_EN].val = data[0];
				sys_param_1b[MADD_B_DL_WORK_EN].val = data[0];
				module_param_chg_flag |= PCHG_B_WORK_EN;
			}
			else
			{
				return 2;
			}
		}	
	break;

	case HXCT_CMD_SET_NOISE_ON:		// 底噪抑制使能
		if ( data[0]>1 ) return 0;

		addr = (0==ab_flag) ? MADD_A_LTHR_EN : MADD_B_LTHR_EN;
		if ( sys_param_1b[addr].val == data[0] )
		{
			return 2;
		}
		sys_param_1b[addr].val = data[0];
		module_param_chg_flag |= ((0==ab_flag) ? PCHG_A_LTHR: PCHG_B_LTHR);
	break;

	case HXCT_CMD_SET_NOISE_GATE:		// 躁声抑制电平下门限MADD_B_LTHR_DN
		addr = (0==ab_flag) ? MADD_A_LTHR_DN : MADD_B_LTHR_DN;
		if ( sys_param_1b[addr].val == data[0] )
		{
			return 2;
		}
		sys_param_1b[addr].val = data[0];
		module_param_chg_flag |= ((0==ab_flag) ? PCHG_A_LTHR: PCHG_B_LTHR);
	break;

	default:
		return 0xFF;
	}

	return 1;	// 设置成功，需要保存参数
}


#ifdef HX_PROTOCOL_1230		// 虹信20111230协议
/*************************************************************
Name: HxExtraSetLowPowerMode
Description: 扩展设置->低功耗模式开关
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetLowPowerMode( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	return 0;		// REC禁止低功耗
}


/*************************************************************
Name: HxExtraSetPaGain
Description: 扩展设置->功放增益
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetPaGain( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	return 0;	// REC不支持设置功放增益
}

/*************************************************************
Name: HxExtraSetDpxInAtt
Description: 扩展设置->输入双工器衰减
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetDpxInAtt( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	UCHAR8 tmp;
	UINT16 addr;
	UINT16 val16;

	if ( up_down==0 ) return 0;	// 不支持设置上行

	val16 = data[0]|(data[1]<<8);
	if ( val16>315 ) return 0;
	
	if ( 0==ab_flag )
	{
		if ( val16 !=sys_param_2b[MADD_A_UDPX_IN_GAIN].val )
		{
			sys_param_2b[MADD_A_UDPX_IN_GAIN].val = val16;
			module_param_chg_flag |= PCHG_A_POW_GAIN;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if ( val16 !=sys_param_2b[MADD_B_UDPX_IN_GAIN].val )
		{
			sys_param_2b[MADD_B_UDPX_IN_GAIN].val = val16;
			module_param_chg_flag |= PCHG_B_POW_GAIN;
		}
		else
		{
			return 2;
		}
	}

	return 1;
}

/*************************************************************
Name: HxExtraSetDpxOutAtt
Description: 扩展设置->输出双工器衰减
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetDpxOutAtt( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	UCHAR8 tmp;
	UINT16 addr;
	UINT16 val16;

	if ( up_down==1 ) return 0;	// 不支持设置下行

	val16 = data[0]|(data[1]<<8);
	if ( val16>315 ) return 0;

	if ( 0==ab_flag )
	{
		if ( val16 !=sys_param_2b[MADD_A_UDPX_OUT_GAIN].val )
		{
			sys_param_2b[MADD_A_UDPX_OUT_GAIN].val = val16;
			module_param_chg_flag |= PCHG_A_POW_GAIN;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if ( val16 !=sys_param_2b[MADD_B_UDPX_OUT_GAIN].val )
		{
			sys_param_2b[MADD_B_UDPX_OUT_GAIN].val = val16;
			module_param_chg_flag |= PCHG_B_POW_GAIN;
		}
		else
		{
			return 2;
		}
	}

	return 1;
}

/*************************************************************
Name: HxExtraSetFpsLockBcch
Description: 扩展设置->频点搜索:锁频信道号BCCH
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetFpsLockBcch( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN	// 启用频点搜索功能

	UINT16 val16;

	val16 = data[0]|(data[1]<<8);
	
	if ( val16 != sys_param_2b[MADD_FPS_BCCH_LK_SET].val )
	{
		sys_param_2b[MADD_FPS_BCCH_LK_SET].val = val16;
		if ( b_FALSE==FPS_CheckParam(SYS_A_FLAG) )
		{
			return 0;	// 出错
		}
		module_param_chg_flag |= PCHG_FPS_RANGE;
		return 1;
	}
	else
	{
		return 2;		// 设置值没改变
	}
	
#else
	return 0;
#endif
}

/*************************************************************
Name: HxExtraSetAutoDelayMode
Description: 扩展设置->自动延时调整开关
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetFpsParam( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN	// 启用频点搜索功能

	UCHAR8 chg_flag = 0;
	
	if ( data[0]!=sys_param_1b[MADD_FPS_RFRANGE_SEL].val )	// 频段选择
	{
		sys_param_1b[MADD_FPS_RFRANGE_SEL].val = data[0];
		chg_flag = 1;
	}

	if ( data[1]!=sys_param_1b[MADD_FPS_MOSVC_SEL].val )		// 运营商选择
	{
		sys_param_1b[MADD_FPS_MOSVC_SEL].val = data[1];
		chg_flag = 1;
	}

	if ( 0==chg_flag )
	{
		return 2;		// 设置值没改变
	}
	else
	{
		if ( b_FALSE==FPS_CheckParam(SYS_A_FLAG) )
		{
			return 0;	// 出错
		}
		module_param_chg_flag |= PCHG_FPS_RANGE;
		return 1;		
	}
	
#else
	return 0;
#endif
}

/*************************************************************
Name: HxExtraSetFpsLockCid
Description: 扩展设置->频点搜索:锁小区识别码CID
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetFpsLockCid( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN	// 启用频点搜索功能

	UINT16 val16;

	val16 = data[0]|(data[1]<<8);
	
	if ( val16 != sys_param_2b[MADD_FPS_CID_LK_SET].val )
	{
		sys_param_2b[MADD_FPS_CID_LK_SET].val = val16;
		if ( b_FALSE==FPS_CheckParam(SYS_A_FLAG ) )
		{
			return 0;	// 出错
		}
		module_param_chg_flag |= PCHG_FPS_RANGE;
		return 1;
	}
	else
	{
		return 2;		// 设置值没改变
	}

#else
	return 0;
#endif

}

/*************************************************************
Name: HxExtraSetAutoDelayMode
Description: 扩展设置->自动延时调整开关
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetAutoDelayMode( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{

	if ( data[0]>1 ) return 0;
	
	if ( data[0]!=sys_param_1b[MADD_DELAY_MODE].val )
	{
		sys_param_1b[MADD_DELAY_MODE].val = data[0];
		module_param_chg_flag |= PCHG_OPT_DELAY;
		return 1;
	}
	else
	{
		return 2;		// 设置值没改变
	}
}

/*************************************************************
Name: HxExtraSetDelayOffset
Description: 扩展设置->光路延时补偿
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: 处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 HxExtraSetDelayOffset( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	UINT16 val16;

	val16 = data[0]|(data[1]<<8);
	
	if ( val16 != sys_param_2b[MADD_DL_DELAY_OFFSET].val )
	{
		sys_param_2b[MADD_DL_DELAY_OFFSET].val = val16;
		module_param_chg_flag |= PCHG_OPT_DELAY;
		return 1;
	}
	else
	{
		return 2;		// 设置值没改变
	}

}
#endif

/*************************************************************
Name:MonHXSetExtraPara
Description:扩展设置查询项的查询命令回复
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 MonHXSetExtraPara(UCHAR8 sub_cmd, UCHAR8 * data , UINT16 body_len, UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 tmp;
	UINT16 addr;
	UINT16 val16;
	UINT32 i;

	switch(sub_cmd)
	{
	case HXCT_SUBCMD_SET_POWER:		// 设置通道整机最大输出功率
		if ( up_down==1 ) return 0;	// REC不支持设置下行最大输出功率
		val16 = data[0]|(data[1]<<8);
//		if ( (INT16)val16>5 )		// 最大5db
//		{
//			return 0;
//		}
		addr = (0==ab_flag) ? MADD_A_UCH_MAX_POW1: MADD_B_UCH_MAX_POW1;
		if ( sys_param_2b[addr].val == val16 )
		{
			return 2;
		}
		sys_param_2b[addr].val = val16;
		module_param_chg_flag |= ((0==ab_flag) ? PCHG_A_POW_GAIN : PCHG_B_POW_GAIN);
	break;
	
	case HXCT_SUBCMD_SET_GAIN:		// 设置整机通道最大增益
//		tmp = (0==ab_flag) ? sys_param_1b[MADD_A_CHANNEL_COUNT].val : sys_param_1b[MADD_B_CHANNEL_COUNT].val;
//		addr = (0==ab_flag) ? MADD_A_DCH_GAIN1 : MADD_B_DCH_GAIN1;
//		for ( i=0; i<tmp; i++ )
//		{
//			
//		}
		return 0;		// REC不支持设置通道增益

	break;

	case HXCT_SUBCMD_SET_FRE_NUM:		// 设置信道号
		tmp = 1;
		if (0==ab_flag )
		{
			for ( i=0; i<sys_param_1b[MADD_A_CHANNEL_COUNT].val; i++ )
			{
				val16 = 0;
				if ( body_len>=2 )
				{
					val16 = data[0]|(data[1]<<8);
					data+=2;
					body_len -= 2;
				}
				if (( tmp != 0 )&&( val16!=sys_param_2b[MADD_A_DL_CHANNEL1+i].val )&&( val16!=sys_param_2b[MADD_A_UL_CHANNEL1+i].val ))
				{
					tmp = 0;		// 修改参数标志
				}
				sys_param_2b[MADD_A_DL_CHANNEL1+i].val = val16;
				sys_param_2b[MADD_A_UL_CHANNEL1+i].val = val16;
			}
			//if ((i>0)&&( b_FALSE==CheckChannelSetA() ))
			//{
			//	return 0;	// 出错
			//}
		}
		else
		{
			for ( i=0; i<sys_param_1b[MADD_B_CHANNEL_COUNT].val; i++ )
			{
				val16 = 0;
				if ( body_len>=2 )
				{
					val16 = data[0]|(data[1]<<8);
					data+=2;
					body_len -= 2;
				}
				if (( tmp != 0 )&&( val16!=sys_param_2b[MADD_B_DL_CHANNEL1+i].val )&&( val16!=sys_param_2b[MADD_B_UL_CHANNEL1+i].val ))
				{
					tmp = 0;		// 修改参数标志
				}
				sys_param_2b[MADD_B_DL_CHANNEL1+i].val = val16;
				sys_param_2b[MADD_B_UL_CHANNEL1+i].val = val16;
			}
			//if ((i>0)&&( b_FALSE==CheckChannelSetB() ))
			//{
			//	return 0;	// 出错
			//}
		}
		if ( tmp!=0 ) return 2;		// 参数没变，不需要保存
		module_param_chg_flag |= ((0==ab_flag) ? PCHG_A_CHANNEL: PCHG_B_CHANNEL);
	break;

	case HXCT_SUBCMD_SET_CH_EN:		// 设置信道开关
		val16 = 1;
		if (0==ab_flag )
		{
			for ( i=0; i<sys_param_1b[MADD_A_CHANNEL_COUNT].val; i++ )
			{
				tmp = 0;
				if ( body_len>0 )
				{
					tmp = *data++;
					body_len--;
				}
				if ( tmp > 1 )	return 0;
				if (( val16 != 0 )&&( tmp!=sys_param_1b[MADD_A_DCH_EN1+i].val )&&( tmp!=sys_param_1b[MADD_A_UCH_EN1+i].val ))
				{
					val16 = 0;		// 修改参数标志
				}
				sys_param_1b[MADD_A_DCH_EN1+i].val = tmp;
				sys_param_1b[MADD_A_UCH_EN1+i].val = tmp;
			}
			//if ((i>0)&&( b_FALSE==CheckChannelSetA() ))
			//{
			//	return 0;	// 出错
			//}
		}
		else
		{
			for ( i=0; i<sys_param_1b[MADD_B_CHANNEL_COUNT].val; i++ )
			{
				tmp = 0;
				if ( body_len>0 )
				{
					tmp = *data++;
					body_len--;
				}
				if ( tmp > 1 )	return 0;
				if (( val16 != 0 )&&( tmp != sys_param_1b[MADD_B_DCH_EN1+i].val )&&( tmp != sys_param_1b[MADD_B_UCH_EN1+i].val ))
				{
					val16 = 0;		// 修改参数标志
				}
				sys_param_1b[MADD_B_DCH_EN1+i].val = tmp;
				sys_param_1b[MADD_B_UCH_EN1+i].val = tmp;
			}
			//if ((i>0)&&( b_FALSE==CheckChannelSetB() ))
			//{
			//	return 0;	// 出错
			//}
		}
		if ( val16!=0 ) return 2;		// 参数没变，不需要保存
		module_param_chg_flag |= ((0==ab_flag) ? PCHG_A_CHANNEL: PCHG_B_CHANNEL);
	break;

	case HXCT_SUBCMD_SET_OPT_EN:		// 光模块开关
		val16 = 1;
		for ( i=0; i<FP_MAX; i++ )
		{
			tmp = 0;
			if ( body_len>0 )
			{
				tmp = *data++;
				body_len--;
			}
			if ( tmp > 1 )	return 0;
			if (( val16 != 0 )&&( tmp != sys_param_1b[MADD_FP1_EN+i].val ))
			{
				val16 = 0;		// 修改参数标志
			}
			sys_param_1b[MADD_FP1_EN+i].val = tmp;
		}
		if ( val16!=0 ) return 2;		// 参数没变，不需要保存
		module_param_chg_flag |= PCHG_SYS_FP_EN;
	break;


#ifdef HX_PROTOCOL_1230		// 虹信20111230协议
	case HXCT_SUBCMD_SET_PD_MODE:		// 设置低功耗开关(1230协议)
		return HxExtraSetLowPowerMode( data, up_down, ab_flag );
		break;
	
	case HXCT_SUBCMD_SET_PA_GAIN:		// 设置下行功放增益(1230协议)
		return HxExtraSetPaGain( data, up_down, ab_flag );
		break;

	case HXCT_SUBCMD_SET_DPX_IA:		// 设置输入双工器衰减(1230协议)
		return HxExtraSetDpxInAtt( data, up_down, ab_flag );
		break;

	case HXCT_SUBCMD_SET_DPX_OA:		// 设置输出双工器衰减(1230协议)
		return HxExtraSetDpxOutAtt( data, up_down, ab_flag );
		break;

	case HXCT_SUBCMD_SET_FPS_BCCH:		// 设置锁频信道号(1230协议)
		return HxExtraSetFpsLockBcch( data, up_down, ab_flag );
		break;
		
	case HXCT_SUBCMD_SET_FPS_PARA:		// 设置运营商和频段选择(1230协议)
		return HxExtraSetFpsParam( data, up_down, ab_flag );
		break;
		
	case HXCT_SUBCMD_SET_FPS_CID:		// 设置锁定小区识别码实时值(1230协议)
		return HxExtraSetFpsLockCid( data, up_down, ab_flag );
		break;
				
	case HXCT_SUBCMD_SET_DELAY_M:		// 设置自动延时开关(1230协议)
		return HxExtraSetAutoDelayMode( data, up_down, ab_flag );
		break;

	case HXCT_SUBCMD_SET_RE_DELAY:		// 设置光路延时补偿(1230协议)
		return HxExtraSetDelayOffset( data, up_down, ab_flag );
		break;

#else	// 虹信20110629协议
	case HXCT_SUBCMD_SET_DELAY:		// 设置延时补偿值
		tmp = 1;
		// 自动时延开关
		if ( data[0]>1 ) return 0;
		if ( data[0]!=sys_param_1b[MADD_DELAY_MODE].val ) tmp = 0;
		sys_param_1b[MADD_DELAY_MODE].val = *data++;
		// 延时补偿
		val16 = data[0]|(data[1]<<8);
		data += 2;
		if ( val16 != sys_param_2b[MADD_DL_DELAY_OFFSET].val ) tmp = 0;
		sys_param_2b[MADD_DL_DELAY_OFFSET].val = val16;
		// 低功耗开关
		if ( data[0]>1 ) return 0;
		if ( data[0]!=sys_param_1b[MADD_LOW_POWER].val ) tmp = 0;
		sys_param_1b[MADD_LOW_POWER].val = *data++;
		if ( tmp!=0 ) return 2;
		module_param_chg_flag |= (PCHG_OPT_DELAY|PCHG_LOW_POWER);
	break;
#endif

	default:
		return 0xFF;
	}

	return 1;	// 设置成功，需要保存参数
}


/*************************************************************
Name:MonHXSetSubPara
Description:扩展设置查询项的查询命令回复
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:处理结果:0-失败，1-设置成功，2-无需改变，0xFF-未知命令
**************************************************************/
UCHAR8 MonHXSetPara(UCHAR8 cmd, UCHAR8 * data , UINT16 body_len, UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 set_result = 0xff;
	
	BackupSystemPara(para_bak);	// 备份参数
	
	if ( cmd==HXCT_CMD_SET_DDF )
	{
		set_result = MonHXSetExtraPara( data[0], data+1, body_len-1, up_down, ab_flag );
	}
	else 
	{
		set_result = MonHXSetNormalPara( cmd, data, body_len, up_down, ab_flag );
	}

	if ( 0 == set_result )	// 参数错误，恢复原值
	{
		RestoreSystemPara(para_bak);
	}

	return set_result;

}

/*************************************************************
Name:UartReceHandleHXSetAdd          
Description:虹信协议设置地址
Input:数据指针，数据长度    
Output:void         
Return:1:成功，0:失败        
**************************************************************/
CHAR8 UartReceHandleHXSetAdd(UCHAR8 *data,UINT16 data_len)
{
	UCHAR8 cur_addr;	// 当前地址
	UCHAR8 new_addr;
	UCHAR8 ab_flag = 0xff;
	UINT16 crc16,i;
	UCHAR8 save_flag = 0;

	new_addr = data[1]&0x07;
	cur_addr = uart_rece_info.rx_buffer[1]&0x07;

	//上下行
	if ( (0==(uart_rece_info.rx_buffer[1]&0x08)) )	// DL
	{
		if ( (0x0F&sys_param_1b[MADD_A_PRI_ADD].val) == cur_addr )	// 设置A段下行地址
		{
			if ( (0x0F&sys_param_1b[MADD_B_PRI_ADD].val)!=new_addr )
			{
				sys_param_1b[MADD_A_PRI_ADD].val = new_addr|(sys_param_1b[MADD_A_PRI_ADD].val&0x70);
				save_flag = 1;
			}
		}
		else if ( (0x0F&sys_param_1b[MADD_B_PRI_ADD].val) == cur_addr )	// 设置B段下行地址
		{
			if ( (0x0F&sys_param_1b[MADD_A_PRI_ADD].val) != new_addr )
			{
				sys_param_1b[MADD_B_PRI_ADD].val = new_addr|(sys_param_1b[MADD_B_PRI_ADD].val&0x70);
				save_flag = 1;
			}
		}
		else
		{
			return;
		}
	}
	else		// UL
	{
		if ( ((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4) == cur_addr )	// 设置A段上行地址
		{
			if ( ((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4) != new_addr )
			{
				sys_param_1b[MADD_A_PRI_ADD].val = (new_addr<<4)|(0x07&sys_param_1b[MADD_A_PRI_ADD].val);
				save_flag = 1;
			}
		}
		else if ( ((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4) == cur_addr )	// 设置B段上行地址
		{
			if ( ((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4) != new_addr )
			{
				sys_param_1b[MADD_B_PRI_ADD].val = (new_addr<<4)|(0x07&sys_param_1b[MADD_B_PRI_ADD].val);
				save_flag = 1;
			}
		}
		else
		{
			return;
		}
	}

	if ( 0!=save_flag )//( data[0]==HXCT_DDF_MODULE_NUM )
	{
		//设置地址
//		sys_param_1b[MADD_A_PRI_ADD].val = data[1]&0x07;	// 以参数的A段地址为模块地址
//		sys_param_1b[MADD_B_PRI_ADD].val = sys_param_1b[MADD_A_PRI_ADD].val + 1;
		//打包包头
		UartPacketHXTransHead(uart_rece_info.rx_buffer[0],(uart_rece_info.rx_buffer[1]&0xf8)|(data[1]&0x07),
			uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);
//		save_flag = 1;
	}
	else
	{
		//错误，不是设置光纤模块，打包包头
		UartPacketHXTransHead(uart_rece_info.rx_buffer[0],(uart_rece_info.rx_buffer[1]&0xf8)|(data[1]&0x07),
			uart_rece_info.rx_buffer[2],HXCT_ACK_SET_ERROR,data_len);
	}

	//COPY 数据
	for (i=0; i<data_len; i++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];	
	
	//计算CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//结束标志
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;

	UartStartTrans();
	
	if ( save_flag != 0 )
	{
		SaveSysParamToFlash();	// 保存参数
	}
	return 1;	
	
}

/*************************************************************
Name:UartReceHandleHXCmdError          
Description:虹信协议命令不支持
Input:数据指针，数据长度    
Output:void         
Return:1:成功，0:失败        
**************************************************************/
CHAR8 UartReceHandleHXCmdError(UCHAR8 *data,UINT16 data_len)
{

	UINT16 crc16,i;

	//打包包头
	UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
		uart_rece_info.rx_buffer[2],HXCT_ACK_CMD_ERROR,data_len);	

	//COPY 数据
	for (i=0; i<data_len; i++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];	
	
	//计算CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//结束标志
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;

	UartStartTrans();
	
	return 1;	

}

/*************************************************************
Name:UartReceHandleHXReset          
Description:虹信协议复位
Input:数据指针，数据长度    
Output:void         
Return:1:成功，0:失败        
**************************************************************/
CHAR8 UartReceHandleHXReset(UCHAR8 *data,UINT16 data_len)
{
	UINT16 crc16,i;
	UCHAR8 reset_flag = 0;

	if ((data_len>0)&&( data[0]==1))
	{
		reset_flag = 1;
	}

	//打包包头
	UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
		uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);	

	//COPY 数据
	for (i=0; i<data_len; i++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];	
	
	//计算CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//结束标志
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;

	UartStartTrans();

	if ( reset_flag != 0 )
	{
		//等待发送完成再复位
		while (uart_trans_info.tx_count!=uart_trans_info.tx_len+1);
		UsNopDelay(10000);

		sys_work_info |= SYSTEM_FLAG_SOFT_RESET;
	}
			
	return 1;	
	
}
/*************************************************************
Name:UartReceHandleHXGet          
Description:虹信协议获取参数
Input:数据指针，数据长度    
Output:void         
Return:1:成功，0:失败        
**************************************************************/
CHAR8 UartReceHandleHXGet(UCHAR8 *data,UINT16 data_len)
{
	UINT16 crc16;
	UCHAR8 up_down, ab_flag;
	
	//上下行标志
	if ( (0==(uart_rece_info.rx_buffer[1]&0x08)) )	// DL
	{
		up_down = 1;
		// AB段标志，A-0，B-1
		if ( (0x0F&sys_param_1b[MADD_A_PRI_ADD].val) == (uart_rece_info.rx_buffer[1]&0x07) )	// A段下行地址
		{
			ab_flag = 0;
		}
		else if ( (0x0F&sys_param_1b[MADD_B_PRI_ADD].val) == (uart_rece_info.rx_buffer[1]&0x07) )	// B段下行地址
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}
	else		// UL
	{
		up_down = 0;
		// AB段标志，A-0，B-1
		if ( ((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// A段上行地址
		{
			ab_flag = 0;
		}
		else if ( ((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B段上行地址
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}

	UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
		uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);		
	//读取相关参数
	uart_trans_info.tx_len += MonHXGetStatusPara(uart_trans_info.tx_buffer+5,up_down, ab_flag);		
	//命令单元长度有变化
	uart_trans_info.tx_buffer[3] = HXCT_ACK_OK|(((uart_trans_info.tx_len-5)>>4)&0x00f0);
	uart_trans_info.tx_buffer[4] = (UCHAR8)(uart_trans_info.tx_len-5);	

	//计算CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//结束标志
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;
	//发送应答
	UartStartTrans();	

	return 1;
		
}

/*************************************************************
Name:UartReceHandleHXSetAtt          
Description:虹信协议设置参数
Input:数据指针，数据长度    ，命令字
Output:void         
Return:1:成功，0:失败        
**************************************************************/
CHAR8 UartReceHandleHXSet(UCHAR8 *data,UINT16 data_len,UCHAR8 cmd)
{
	UINT16 crc16,i;
	UCHAR8 up_down, ab_flag;
	UCHAR8 save_flag= 0;
	UCHAR8 set_flag = 1;
	
	//上下行标志
	if ( (0==(uart_rece_info.rx_buffer[1]&0x08)) )	// DL
	{
		up_down = 1;
		// AB段标志，A-0，B-1
		if ( (0x0F&sys_param_1b[MADD_A_PRI_ADD].val) == (uart_rece_info.rx_buffer[1]&0x07) )	// A段下行地址
		{
			ab_flag = 0;
		}
		else if ( (0x0F&sys_param_1b[MADD_B_PRI_ADD].val) == (uart_rece_info.rx_buffer[1]&0x07) )	// B段下行地址
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}
	else		// UL
	{
		up_down = 0;
		// AB段标志，A-0，B-1
		if ( ((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// A段上行地址
		{
			ab_flag = 0;
		}
		else if ( ((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B段上行地址
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}
	
	switch ( MonHXSetPara(cmd, data, data_len, up_down, ab_flag) )
	{
	case 0:		// 设置错误
		save_flag = 0;
		UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
			uart_rece_info.rx_buffer[2],HXCT_ACK_SET_ERROR,data_len);	
	break;

	case 1:		// 设置成功，写入Flash
		save_flag = 1;
		
	case 2:		// 设置成功，不需要保存
		UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
			uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);
	break;

	default:		// 未知命令
		if ( cmd==HXCT_CMD_SET_DDF )
		{
			if (data[0] == HXCT_SUBCMD_GET_SETTING)		//表25	扩展设置查询项的查询命令
			{
				//打包包头
				UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
					uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);		
				//填充命令体
				uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[0];
				//读取相关参数
				uart_trans_info.tx_len += MonHXGetSubPara(uart_trans_info.tx_buffer+6,up_down, ab_flag);		

				//命令单元长度有变化
				uart_trans_info.tx_buffer[3] = HXCT_ACK_OK|(((uart_trans_info.tx_len-5)>>4)&0x00f0);
				uart_trans_info.tx_buffer[4] = (UCHAR8)(uart_trans_info.tx_len-5);

				set_flag = 0;
				break;
			}
			else if (data[0] == HXCT_SUBCMD_GET_BASE)		//表25	扩展设置查询项的查询命令
			{	
				UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
					uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);		
				//填充命令体
				uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[0];
				//读取相关参数
				//厂家生产序列号
				for (i=0; i<20;i++)
					uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = str_pri_gl_seq[i];
				//MCU程序日期
				for (i=0; i<20;i++)
					uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = str_pri_mcu_date[i];		
				//FPGA程序日期
				for (i=0; i<64;i++)
					uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = str_pri_fpga_date[i];		

				//命令单元长度有变化
				uart_trans_info.tx_buffer[3] = HXCT_ACK_OK|(((uart_trans_info.tx_len-5)>>4)&0x00f0);
				uart_trans_info.tx_buffer[4] = (UCHAR8)(uart_trans_info.tx_len-5);

				set_flag = 0;
				break;
			}
		}
		UartReceHandleHXCmdError(data,data_len);
		return 0;
	}

	if ( set_flag== 1 )	// 设置命令，应答时直接返回原来的命令体
	{
		//COPY 数据
		for (i=0; i<data_len; i++)
			uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];	
	}
		
	//计算CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//结束标志
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;
	//发送应答
	UartStartTrans();

	//如果收到了工作模式变调试模式命令
	if(1==save_flag)
	{
		SaveSysParamToFlash();	// 保存参数
	}
	return 1;	
	
}

/*************************************************************
Name:UartReceHXModuleDET          
Description:虹信协议DET模块处理
Input: [p_dat:命令体指针] [data_len:命令体和命令头的总数据长度]           
Output:void         
Return:void         
**************************************************************/
void UartReceHXModuleDET( UCHAR8 * p_dat, UINT16 data_len )
{
	UCHAR8 tmp;
	UCHAR8 up_down;
	UCHAR8 ab_flag = 0xff;
	UINT16 crc16;
	UCHAR8 body_len = 0;
	UCHAR8 * p_body = uart_trans_info.tx_buffer+5+data_len;	// 指针指向命令体起始位置
	UCHAR8 ack = HXCT_ACK_OK;
	UCHAR8 save_flag = 0;
	
	//上下行标志,0-UL, 1-DL
	if ( 0==(uart_rece_info.rx_buffer[1]&0x08) )	// DL
	{
		up_down = 1;
		// AB段标志，A-0，B-1
		if ( (sys_param_1b[MADD_HX_DET_DADDR].val&0x0F) == (uart_rece_info.rx_buffer[1]&0x07) )	// A段
		{
			ab_flag = 0;
		}
		else if ( (sys_param_1b[MADD_HX_DET_DADDR].val>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B段
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}
	else		// UL
	{
		up_down= 0;
		// AB段标志，A-0，B-1
		if ( (sys_param_1b[MADD_HX_DET_UADDR].val&0x0F) == (uart_rece_info.rx_buffer[1]&0x07) )	// A段
		{
			ab_flag = 0;
		}
		else if ( (sys_param_1b[MADD_HX_DET_UADDR].val>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B段
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}
	
	if ( HXCT_CMD_SET_ADD==uart_rece_info.rx_buffer[2] )	// 设置模块地址
	{
		tmp = p_dat[1]&0x07;		// 新地址

		if ( 1==up_down )		// DL
		{
			if ( 0==ab_flag )	// A段
			{
				if ( (sys_param_1b[MADD_HX_DET_DADDR].val>>4) != tmp )	// 新地址不等于B段地址
				{
					sys_param_1b[MADD_HX_DET_DADDR].val = (sys_param_1b[MADD_HX_DET_DADDR].val & 0xF0)|tmp;	// 设置新地址
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// 设置应答地址
					save_flag = 1;
				}
			}
			else if ( 1==ab_flag )	// B段
			{
				if ( (sys_param_1b[MADD_HX_DET_DADDR].val & 0x0F) != tmp )	// 新地址不等于A段地址
				{
					sys_param_1b[MADD_HX_DET_DADDR].val = (sys_param_1b[MADD_HX_DET_DADDR].val & 0x0F)|(tmp<<4);	// 设置新地址
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// 设置应答地址
					save_flag = 1;
				}
			}
			else
			{
				ack = HXCT_ACK_SET_ERROR;
			}
		}
		else		// UL
		{
			if ( 0==ab_flag )	// A段
			{
				if ( (sys_param_1b[MADD_HX_DET_UADDR].val>>4) != tmp )	// 新地址不等于B段地址
				{
					sys_param_1b[MADD_HX_DET_UADDR].val = (sys_param_1b[MADD_HX_DET_UADDR].val & 0xF0)|tmp;	// 设置新地址
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// 设置应答地址
					save_flag = 1;
				}
			}
			else if ( 1==ab_flag )	// B段
			{
				if ( (sys_param_1b[MADD_HX_DET_UADDR].val & 0x0F) != tmp )	// 新地址不等于A段地址
				{
					sys_param_1b[MADD_HX_DET_UADDR].val = (sys_param_1b[MADD_HX_DET_UADDR].val & 0x0F)|(tmp<<4);	// 设置新地址
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// 设置应答地址
					save_flag = 1;
				}
			}
			else
			{
				ack = HXCT_ACK_SET_ERROR;
			}
		}
	}
	else if ( (0==up_down) && ( ab_flag<2 ) )	// 处理其他命令,只响应上行地址的请求
	{
		if ( HXCT_CMD_GET_STA==uart_rece_info.rx_buffer[2] )	// 模块状态查询命令
		{
			p_body[0] = 0;
			p_body[1] = 0;	// 无低噪放，功率为0
			p_body[2] = 0;	// 无低噪放，功率为0
			p_body[3] = 0;	// 无低噪放，功率为0
			body_len = 4;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	UartPacketHXTransHead(
		uart_rece_info.rx_buffer[0], uart_rece_info.rx_buffer[1], uart_rece_info.rx_buffer[2], ack, data_len+body_len );	
	//COPY 数据
	for (tmp=0; tmp<data_len; tmp++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = p_dat[tmp];	

	uart_trans_info.tx_len += body_len;
	
	//计算CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//结束标志
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;
	//发送应答
	UartStartTrans();	

	if ( 0!= save_flag )
	{
		SaveSysParamToFlash();	// 保存参数
	}
}

/*************************************************************
Name:UartReceHXModuleDET          
Description:虹信协议LNA模块处理,【不】应响应下行LNA 模块命令
Input:[p_dat:命令体指针] [data_len:命令体和命令头的总数据长度]           
Output:void         
Return:void         
**************************************************************/
void UartReceHXModuleLNA( UCHAR8 * p_dat, UINT16 data_len )
{
	UCHAR8 tmp;
	UCHAR8 up_down;
	UCHAR8 ab_flag = 0xff;
	UINT16 crc16;
	UCHAR8 body_len = 0;
	UCHAR8 * p_body = uart_trans_info.tx_buffer+5+data_len;	// 指针指向命令体起始位置
	UCHAR8 ack = HXCT_ACK_OK;
	UCHAR8 save_flag = 0;

	//上下行标志,0-UL, 1-DL
	if ( 0==(uart_rece_info.rx_buffer[1]&0x08) )	// DL
	{
		return;	// 不响应下行LNA 模块命令
	#if 0
		up_down = 1;
		// AB段标志，A-0，B-1
		if ( (sys_param_1b[MADD_HX_LNA_DADDR].val&0x0F) == (uart_rece_info.rx_buffer[1]&0x07) )	// A段
		{
			ab_flag = 0;
		}
		else if ( (sys_param_1b[MADD_HX_LNA_DADDR].val>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B段
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	#endif;
	}
	else		// UL
	{
		up_down= 0;
		// AB段标志，A-0，B-1
		if ( (sys_param_1b[MADD_HX_LNA_UADDR].val&0x07) == (uart_rece_info.rx_buffer[1]&0x07) )	// A段
		{
			ab_flag = 0;
		}
		else if ( (sys_param_1b[MADD_HX_LNA_UADDR].val>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B段
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}
	
	if ( HXCT_CMD_SET_ADD==uart_rece_info.rx_buffer[2] )	// 设置模块地址
	{
		tmp = p_dat[1]&0x07;	// 新地址

		if ( 1==up_down )		// DL
		{
			if ( 0==ab_flag )	// A段
			{
				if ( (sys_param_1b[MADD_HX_LNA_DADDR].val>>4) != tmp )	// 新地址不等于B段地址
				{
					sys_param_1b[MADD_HX_LNA_DADDR].val = (sys_param_1b[MADD_HX_LNA_DADDR].val & 0x70)|tmp;	// 设置新地址
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// 设置应答地址
					save_flag = 1;
				}
			}
			else if ( 1==ab_flag )	// B段
			{
				if ( (sys_param_1b[MADD_HX_LNA_DADDR].val & 0x0F) != tmp )	// 新地址不等于A段地址
				{
					sys_param_1b[MADD_HX_LNA_DADDR].val = (sys_param_1b[MADD_HX_LNA_DADDR].val & 0x07)|(tmp<<4);	// 设置新地址
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// 设置应答地址
					save_flag = 1;
				}
			}
			else
			{
				ack = HXCT_ACK_SET_ERROR;
			}
		}
		else		// UL
		{
			if ( 0==ab_flag )	// A段
			{
				if ( (sys_param_1b[MADD_HX_LNA_UADDR].val>>4) != tmp )	// 新地址不等于B段地址
				{
					sys_param_1b[MADD_HX_LNA_UADDR].val = (sys_param_1b[MADD_HX_LNA_UADDR].val & 0x70)|tmp;	// 设置新地址
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// 设置应答地址
					save_flag = 1;
				}
			}
			else if ( 1==ab_flag )	// B段
			{
				if ( (sys_param_1b[MADD_HX_LNA_UADDR].val & 0x0F) != tmp )	// 新地址不等于A段地址
				{
					sys_param_1b[MADD_HX_LNA_UADDR].val = (sys_param_1b[MADD_HX_LNA_UADDR].val & 0x07)|(tmp<<4);	// 设置新地址
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// 设置应答地址
					save_flag = 1;
				}
			}
			else
			{
				ack = HXCT_ACK_SET_ERROR;
			}
		}

	}
	else if ( (0==up_down) && ( ab_flag<2 ) )	// 处理其他命令,只响应上行地址的请求
	{
		if ( HXCT_CMD_GET_STA==uart_rece_info.rx_buffer[2] )	// 模块状态查询命令
		{
			p_body[0] = 0;	// REC无LNA
			p_body[1] = 0;	// 不支持ATT值查询，返回0
			p_body[2] = 0;	// 不支持LNA最大增益值查询，返回0
			p_body[3] = 0;	// 不支持LNA的ALC数值查询，返回0
			body_len = 4;
		}
		else if ( HXCT_CMD_SET_ATT == uart_rece_info.rx_buffer[2] )
		{
			body_len = 0;
		}
		else if ( HXCT_CMD_SET_ALC == uart_rece_info.rx_buffer[2] )
		{
			body_len = 0;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
	
	UartPacketHXTransHead(
		uart_rece_info.rx_buffer[0], uart_rece_info.rx_buffer[1], uart_rece_info.rx_buffer[2], ack, data_len+body_len );	
	//COPY 数据
	for (tmp=0; tmp<data_len; tmp++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = p_dat[tmp];	

	uart_trans_info.tx_len += body_len;
	
	//计算CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//结束标志
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;
	//发送应答
	UartStartTrans();	

	if ( 0!= save_flag )
	{
		SaveSysParamToFlash();	// 保存参数
	}

}
#if 0
/*************************************************************
Name:UartReceHandle          
Description:接收数据包处理
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartReceHandle(void)
{
	UINT16 crc_val;
	//判断应答标志
	if ((uart_rece_info.rx_buffer[3]&0x0f) != 0x00)
		return;
	
	//判断CRC
	crc_val = CalCrc16(uart_rece_info.rx_buffer,uart_rece_info.rx_len+5,HXCT_CRC_SEED);
	if (crc_val != (uart_rece_info.rx_buffer[uart_rece_info.rx_len+5]|(uart_rece_info.rx_buffer[uart_rece_info.rx_len+6]<<8)))
	{
		return;		//crc错误		
	}

	if ( HXCT_DET_MODULE_NUM==uart_rece_info.rx_buffer[0] )	// DET模块处理
	{
		UartReceHXModuleDET( uart_rece_info.rx_buffer+5 , uart_rece_info.rx_len );
		return;
	}
	else if ( HXCT_LNA_MODULE_NUM==uart_rece_info.rx_buffer[0] )	// LNA模块处理
	{
		UartReceHXModuleLNA( uart_rece_info.rx_buffer+5 , uart_rece_info.rx_len );
		return;
	}
	else if ( HXCT_DDF_MODULE_NUM !=uart_rece_info.rx_buffer[0] )	// 非中频模块则不处理
	{
		return;
	}

	//判断地址
	if ((uart_rece_info.rx_buffer[2]!=HXCT_CMD_SET_ADD) 
		&& ((uart_rece_info.rx_buffer[1]&0x07)!=(0x0F&sys_param_1b[MADD_A_PRI_ADD].val))
		&& ((uart_rece_info.rx_buffer[1]&0x07)!=((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4))
		&& ((uart_rece_info.rx_buffer[1]&0x07)!=(0x0F&sys_param_1b[MADD_B_PRI_ADD].val))
		&& ((uart_rece_info.rx_buffer[1]&0x07)!=((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4)) )
	{
		//非设置地址命令，并且地址不相符则不处理数据包
		return;
	}

	WTD_CLR;
	switch(uart_rece_info.rx_buffer[2])
	{
		case HXCT_CMD_SET_ADD:
			UartReceHandleHXSetAdd(uart_rece_info.rx_buffer+5,uart_rece_info.rx_len);
		break;

		case HXCT_CMD_GET_STA:
			UartReceHandleHXGet(uart_rece_info.rx_buffer+5,uart_rece_info.rx_len);
		break;

		case HXCT_CMD_SET_ATT:				
		case HXCT_CMD_SET_ONOFF:
		case HXCT_CMD_SET_NOISE_ON:
		case HXCT_CMD_SET_NOISE_GATE:		
		case HXCT_CMD_SET_DDF:
			UartReceHandleHXSet(uart_rece_info.rx_buffer+5,uart_rece_info.rx_len,uart_rece_info.rx_buffer[2]);
		break;		

		case HXCT_CMD_SET_RESET:
			UartReceHandleHXReset(uart_rece_info.rx_buffer+5,uart_rece_info.rx_len);
		break;	
		
		default:
			UartReceHandleHXCmdError(uart_rece_info.rx_buffer+5,uart_rece_info.rx_len);
		break;	
		
	}
	
}
#endif 


#else

/*************************************************************
Name:UartReceInterrupt          
Description:中断调用接收处理程序
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartReceInterrupt( UCHAR8 rx_dat )
{

	uart_rece_info.rx_data = rx_dat;
	//printf("%02x\r\n",rx_dat);	
	WTD_CLR;
	if (0 != (sys_work_info&SYSTEM_FLAG_232_RECE))
	{
		// 上一笔包还没处理完
		return;
	}

	//监控接口
	if (uart_rece_info.rx_count==0 && uart_rece_info.rx_data!=0x4E)
	{
		//trans_4e_flag = 0;
		return;			//等待开始标志
	}
	
	if (uart_rece_info.rx_count!=0 && uart_rece_info.rx_data==0x4E)
	{
		if ( uart_rece_info.rx_count>=10 )
		{
			//收到结束标志
			uart_rece_info.rx_buffer[uart_rece_info.rx_count] = uart_rece_info.rx_data;
			uart_rece_info.rx_len = uart_rece_info.rx_count+1;
			uart_rece_info.rx_count = 0;
			sys_work_info |= SYSTEM_FLAG_232_RECE;
			//printf(" uart_rece_info.rx_count>=10");
			//trans_4e_flag = 0;
			return;
		}
		else
		{
			//printf(" uart_rece_info.rx_count:%d",uart_rece_info.rx_count);
			//纠错
			uart_rece_info.rx_count = 0;
		}
	}

	if ( trans_4e_flag == 0 )
	{
		if (uart_rece_info.rx_data==0x4D && uart_rece_info.rx_buffer[uart_rece_info.rx_count-1]==0x5E) 
		{
			//转义
			uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = 0x4E;
			trans_4e_flag = 1;		//置4E转义标志
			return;
		}
		
		if (uart_rece_info.rx_data==0x5D&& uart_rece_info.rx_buffer[uart_rece_info.rx_count-1]==0x5E) 
		{
			//转义
			uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = 0x5E;
			trans_4e_flag = 1;
			return;
		}
	}
	
	uart_rece_info.rx_buffer[uart_rece_info.rx_count] = uart_rece_info.rx_data;
	uart_rece_info.rx_count++;

	if ( uart_rece_info.rx_count>=UART_BUFF_SIZE ) 
	{
		// 数据过长,判定为无效数据包
		uart_rece_info.rx_count = 0;
	}
	
	trans_4e_flag = 0;

}

/*************************************************************
Name:UartTransInterrupt          
Description:中断调用发送处理函数
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartTransInterrupt(void)
{
	//中断发生时上一个数据已经发送出去了
	//uart_trans_info.tx_len为不包括前后0X4E的数据长度

	if (uart_trans_info.tx_count == uart_trans_info.tx_len)			// 结束标志
	{	
		CtrlUartSendDat(0x4E);
		uart_trans_info.tx_count++;
	}
	else if (uart_trans_info.tx_count == uart_trans_info.tx_len+1)	// 多发送一个字符
	{	
		CtrlUartSendDat(0xFF);
		uart_trans_info.tx_count++;
	}
	else if(uart_trans_info.tx_count == uart_trans_info.tx_len+2)		// 发送完成
	{
		//延时后将485发送使能关闭			
		EnableUartTx(0,0);	
		return;
	}
	else
	{
		if (uart_trans_info.tx_buffer[uart_trans_info.tx_count] == 0x4E)
		{
			//转义
			CtrlUartSendDat(0x5E);
			uart_trans_info.tx_buffer[uart_trans_info.tx_count] = 0x4D;
			return;
		}
		if (uart_trans_info.tx_buffer[uart_trans_info.tx_count] == 0x5E)
		{
			//转义
			CtrlUartSendDat(0x5E);
			uart_trans_info.tx_buffer[uart_trans_info.tx_count] = 0x5D;
			return;
		}
		CtrlUartSendDat( uart_trans_info.tx_buffer[uart_trans_info.tx_count] );
		uart_trans_info.tx_count++;
	}
}
//#if 0
/*************************************************************
Name:UartStartTrans          
Description:开始发送
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartStartTrans(void)
{
	TRACE_DEBUG("RS485A Start Trans.\r\n")
	
	uart_trans_info.tx_count = 0;
	EnableUartTx(1,0x4E);	
}
//#endif 
/*************************************************************
Name:UartPacketTransHead          
Description:打包包头
Input:模块地址，命令字，应答标志            
Output:void         
Return:void         
**************************************************************/
void UartPacketTransHead(UCHAR8 type,UCHAR8 ver,UCHAR8 device,UCHAR8 address,UCHAR8 command,UCHAR8 ack)
{
	uart_trans_info.tx_buffer[0] = type;
	uart_trans_info.tx_buffer[1] = ver;	
	uart_trans_info.tx_buffer[2] = device;		
	uart_trans_info.tx_buffer[3] = address;
	uart_trans_info.tx_buffer[4] = command;	
	uart_trans_info.tx_buffer[5] = ack;
	uart_trans_info.tx_len = 6;
}

/*************************************************************
Name:UartReceHandle          
Description:接收数据包处理
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartReceHandle(void)
{
	UCHAR8 *real_data;
	UINT16 read_data_len;
	UINT16 crc16;
	CHAR8 ret = 1;

	WTD_CLR;

	
	if (uart_rece_info.rx_len < 10)
	{
//		printf("uart_rece_info.rx_len_to_short:%02X\r\n", uart_rece_info.rx_len);	//长度有限制

		return;
	}
#if 0	
	TRACE_INFO("RS485A Handle\r\n");
	{
		UINT16 i;
		for ( i=0; i<uart_rece_info.rx_len;  i++)
		{
			TRACE_INFO_WP("%02X ", uart_rece_info.rx_buffer[i] );
		}
		TRACE_INFO_WP("\r\n");
	}
#endif
//test
//	UartReceHandleMoError(MONITOR_ERROR_CRC);	
//	return;

	if ((uart_rece_info.rx_buffer[4]!=0xff) 
		&& (uart_rece_info.rx_buffer[4]!=sys_param_1b[MADD_A_PRI_ADD].val)
		&& (uart_rece_info.rx_buffer[4]!=sys_param_1b[MADD_B_PRI_ADD].val)
		&& (uart_rece_info.rx_buffer[4]!=sys_param_1b[MADD_C_PRI_ADD].val)
		&& (uart_rece_info.rx_buffer[4]!=sys_param_1b[MADD_D_PRI_ADD].val))
	{
		//模块地址不为广播地址或者本机地址则不处理
		TRACE_ERROR("485A Mo Addr Err:%02X\r\n", uart_rece_info.rx_buffer[4]);
		return ;
	}
	
	//收到数据后延时20MS再处理
	UsNopDelay(25*1000);	
	WTD_CLR;
	//printf("485_ID_1:%02X\r\n", uart_rece_info.rx_buffer[5]);	//长度有限制
	
	//校验CRC
	crc16 = CalCrc16(uart_rece_info.rx_buffer+1,uart_rece_info.rx_len-4,0x0000);
	if (crc16 != (UINT16)(uart_rece_info.rx_buffer[uart_rece_info.rx_len-3]|(uart_rece_info.rx_buffer[uart_rece_info.rx_len-2]<<8)))
	{
		//crc错误
		UartReceHandleMoError(MONITOR_ERROR_CRC);			
		return;
	}
	
	//printf("485_ID_2:%02X\r\n", uart_rece_info.rx_buffer[6]);	
	
	if (uart_rece_info.rx_buffer[6] != 0xFF)
	{
		//主机发来的标志错
		printf("crc error\r\n");
		UartReceHandleMoError(MONITOR_ERROR_FLAG);
		return;
	}
	WTD_CLR;
	
	printf("485_cmd:%02X,485_len:%04X\r\n", uart_rece_info.rx_buffer[5],uart_rece_info.rx_len);	
	
	switch(uart_rece_info.rx_buffer[5])
	{
		case MONITOR_CMD_GET_PRI:
			ret = UartReceHandleMoGetPara(uart_rece_info.rx_buffer+7,uart_rece_info.rx_len-10);
			if (ret == 0)
				UartReceHandleMoError(MONITOR_ERROR_GET);
		break;
		
		case MONITOR_CMD_GET_ALL_PARA:
			ret = UartReceHandleMoGetAllPara(uart_rece_info.rx_buffer+7,uart_rece_info.rx_len-10);
			if (ret == 0)
				UartReceHandleMoError(MONITOR_ERROR_GET);				
		break;
		
		case MONITOR_CMD_SET_PRI:
			ret = UartReceHandleMoSetPara(uart_rece_info.rx_buffer+7,uart_rece_info.rx_len-10);
			if (ret == 0)
				UartReceHandleMoError(MONITOR_ERROR_SET);				
		break;
		
		case MONITOR_CMD_SET_PARA:
			ret = UartReceHandleMoSetPara(uart_rece_info.rx_buffer+7,uart_rece_info.rx_len-10);
			if (ret == 0)
				UartReceHandleMoError(MONITOR_ERROR_SET);				
		break;
		
		case MONITOR_CMD_GET_PARA:
			ret = UartReceHandleMoGetPara(uart_rece_info.rx_buffer+7,uart_rece_info.rx_len-10);
			if (ret == 0)
				UartReceHandleMoError(MONITOR_ERROR_GET);				
		break;

		case MONITOR_CMD_RE_TRANS:
			ret = UartReceHandleMoTransRe( uart_rece_info.rx_buffer+7,uart_rece_info.rx_len-10 );
			if (ret==0 )
			{
				// 有错误，复位RE远程访问指令的相关参数
				re_trans_cmd = 0;
				re_trans_fp = 0;
				re_trans_node = 0;
				UartReceHandleMoError(MONITOR_ERROR_OTHER);				
			}
		break;

		case MONITOR_CMD_GET_TOPO:
				UartReceHandleMoGetTopo( uart_rece_info.rx_buffer+7,uart_rece_info.rx_len-10 );
		break;
			
		default:
			//命令不支持
			UartReceHandleMoError(MONITOR_ERROR_COM);		
		break;			
	}
	WTD_CLR;
}



/*************************************************************
Name:UartReceHandleMonGetAllPara         
Description:监控命令中的获取所有参数信息
Input:数据指针，数据长度            
Output:void         
Return:1:成功，0:失败        
**************************************************************/
CHAR8 UartReceHandleMoGetAllPara(UCHAR8 *data,UINT16 data_len)
{
	UINT16 ret_len, crc16;
	UINT16 pkt_count;
	UINT16 i;
	UCHAR8 flag;

	TRACE_DEBUG("485A Handle HandShake\r\n")
	
	UartPacketTransHead(uart_rece_info.rx_buffer[1],uart_rece_info.rx_buffer[2],uart_rece_info.rx_buffer[3],
			uart_rece_info.rx_buffer[4],uart_rece_info.rx_buffer[5],MONITOR_SUCCESS);	

	if ( data_len>0 )
	{
		i = data[0];
	}
	else
	{
		i = 1;
	}

	ret_len = 0;
	if ( uart_rece_info.rx_buffer[4]==sys_param_1b[MADD_A_PRI_ADD].val )
	{
		flag=SYS_A_FLAG;
	}
	else if ( uart_rece_info.rx_buffer[4]==sys_param_1b[MADD_B_PRI_ADD].val )
	{
		flag=SYS_B_FLAG;
	}
	else if ( uart_rece_info.rx_buffer[4]==sys_param_1b[MADD_C_PRI_ADD].val )
	{
		flag=SYS_C_FLAG;
	}
	else if ( uart_rece_info.rx_buffer[4]==sys_param_1b[MADD_D_PRI_ADD].val )
	{
		flag=SYS_D_FLAG;
	}	
	
	ret_len = GetAllMoParam( i, flag, uart_trans_info.tx_buffer+uart_trans_info.tx_len );
	
	TRACE_DEBUG("485A Handle HandShake1\r\n")
	if ( ret_len == 0 )
	{
		return 0;
	}
	TRACE_DEBUG("485A Handle HandShake2\r\n")
	uart_trans_info.tx_len += ret_len;
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, 0x0000);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);
	UartStartTrans();

	return 1;
}

/*************************************************************
Name:UartReceHandleMonGetPrara        
Description:监控命令中的获取参数
Input:数据指针，数据长度            
Output:void         
Return:1:成功，0:失败   
**************************************************************/
CHAR8 UartReceHandleMoGetTopo(UCHAR8 *data,UINT16 data_len)
{
	UINT16 crc16;
	UINT16 i;
	UINT32 len;
	UCHAR8 tmp;
	UINT32 msg_tx_len;
	UCHAR8 fp_no, re_no,ree_no;  	

	UartPacketTransHead(uart_rece_info.rx_buffer[1],uart_rece_info.rx_buffer[2],uart_rece_info.rx_buffer[3],
			/*(UCHAR8)sys_param_1b[MADD_A_PRI_ADD].addr*/uart_rece_info.rx_buffer[4],uart_rece_info.rx_buffer[5],MONITOR_SUCCESS);	


	 
	TRACE_INFO("[M]Msg Handle Get Topo 1 \r\n"); 

	msg_tx_len =uart_trans_info.tx_len;


//	if ( 0x00 == p_args[0] )		// 查询类型:当前拓扑
//	{
//		TRACE_INFO("[M]Msg Handle Get Topo  2\r\n"); 
		for ( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			// 光口状态
			tmp = 0;
			
			if ( COMMA_LOCK==fp_inf[fp_no].comma_lock )	// 逗号锁定
			{
                  tmp |= (0x01<<7);
			}
			
			if ( FRAME_LOCK==fp_inf[fp_no].frm_lock )	// 接收帧锁定
			{
				 tmp |= (0x01<<6);
			}

			if ( 0 != ( OPS_RCV_FLAG & fp_inf[fp_no].ops_info ) )	// 收到对端光口数据，环网
			{
				tmp |= (0x01<<4);		// 环网
				tmp |= ( fp_inf[fp_no].ops_info & OPS_NO_MASK );		// 对端光口号
			}

			uart_trans_info.tx_buffer[msg_tx_len++] = tmp;  //bit7~逗号锁定，bit6~帧锁定，bit4~环网标志，bit3~bit0 对端光口号 
			uart_trans_info.tx_buffer[msg_tx_len++] = fp_inf[fp_no].re_cnt; //当前光口的RE个数 
//			p_tx_buff[msg_tx_len++] = fp_inf[fp_no].ree_cnt; //当前光口的REe个数  
//				TRACE_INFO("\r\n"); 
//				TRACE_INFO("fp_inf[fp_no].re_cnt(%0x)\r\n",fp_inf[fp_no].re_cnt); 	

			
			for ( re_no=0; re_no< fp_inf[fp_no].re_cnt; re_no++ )  
			{
				uart_trans_info.tx_buffer[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].re_status; //包含了光口0、1的锁定状态和上、下行光口的判断
//				uart_trans_info.tx_buffer[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].re_id;     //光口ID 
				
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_count;           //当前光口当前节点的REe个数 
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_sync_st_inf[0];     // 4个连接RF的光口状态和8个连接RF的网口状态
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_sync_st_inf[1];     // 	
				uart_trans_info.tx_buffer[msg_tx_len++] = tmp_re_inf[fp_no][re_no].ree_nt_stat;     // 4个连接RF的光口状态和8个连接RF的网口状态
				uart_trans_info.tx_buffer[msg_tx_len++] =tmp_re_inf[fp_no][re_no].ree_fp_stat;     // 
				uart_trans_info.tx_buffer[msg_tx_len++] =(0xff00&tmp_re_inf[fp_no][re_no].ree_work_status)>>8;     // 4个连接RF的光口状态和8个连接RF的网口状态
				uart_trans_info.tx_buffer[msg_tx_len++] =0xff&tmp_re_inf[fp_no][re_no].ree_work_status;     // 

//				TRACE_INFO("fp_inf[fp_no].re_info[re_no].re_status(%0x)\r\n",fp_inf[fp_no].re_info[re_no].re_status); 
//				TRACE_INFO("fp_inf[fp_no].re_info[re_no].re_id(%0x)\r\n",fp_inf[fp_no].re_info[re_no].re_id); 
//				TRACE_INFO("tmp_re_inf[fp_no][re_no].ree_nt_stat(%0x)\r\n",tmp_re_inf[fp_no][re_no].ree_nt_stat); 
//				TRACE_INFO("tmp_re_inf[fp_no][re_no].ree_fp_stat(%0x)\r\n",tmp_re_inf[fp_no][re_no].ree_fp_stat); 
//				TRACE_INFO("(0xff00&tmp_re_inf[fp_no][re_no].ree_work_status)>>8(%0x)\r\n",(0xff00&tmp_re_inf[fp_no][re_no].ree_work_status)>>8); 
//				TRACE_INFO("0xff&tmp_re_inf[fp_no][re_no].ree_work_status(%0x)\r\n",0xff&tmp_re_inf[fp_no][re_no].ree_work_status); 	
				//
//				TRACE_INFO("\r\n"); 
				
			} 
			
		}
//	}

	if (msg_tx_len == 0)
		return 0;
//	TRACE_INFO("uart_trans_info.tx_len(%0x)------------------\r\n",uart_trans_info.tx_len);
//	TRACE_INFO("1msg_tx_len(%0x)------------------\r\n",uart_trans_info.tx_len);	
	uart_trans_info.tx_len = msg_tx_len;
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len,0x0000);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len+1] = (UCHAR8)(crc16>>8);
	uart_trans_info.tx_len+=2;
//	TRACE_INFO("2msg_tx_len(%0x)------------------\r\n",uart_trans_info.tx_len);
	UartStartTrans();
//	TRACE_INFO("3msg_tx_len(%0x)------------------\r\n",uart_trans_info.tx_len);
	return 1;	
}


/*************************************************************
Name:UartReceHandleMonGetPrara        
Description:监控命令中的获取参数
Input:数据指针，数据长度            
Output:void         
Return:1:成功，0:失败   
**************************************************************/
CHAR8 UartReceHandleMoGetPara(UCHAR8 *data,UINT16 data_len)
{
	UINT16 ret_len,crc16;
	UCHAR8 mask;
	UINT16 i;
	
	TRACE_DEBUG("485A Handle Get Param\r\n");

	UartPacketTransHead(uart_rece_info.rx_buffer[1],uart_rece_info.rx_buffer[2],uart_rece_info.rx_buffer[3],
			/*(UCHAR8)sys_param_1b[MADD_A_PRI_ADD].addr*/uart_rece_info.rx_buffer[4],uart_rece_info.rx_buffer[5],MONITOR_SUCCESS);	

//	TRACE_INFO("p_msg:[%02X]------------\r\n", data[data_len-1]);
	TRACE_INFO("abcd=[%x]:------------\r\n", uart_rece_info.rx_buffer[4]);

	if ( uart_rece_info.rx_buffer[4] == sys_param_1b[MADD_A_PRI_ADD].val )
	{
		mask = PT_AP;
	}
	else if ( uart_rece_info.rx_buffer[4] == sys_param_1b[MADD_B_PRI_ADD].val )
	{
		mask = PT_BP;
	}
	else	if ( uart_rece_info.rx_buffer[4] == sys_param_1b[MADD_C_PRI_ADD].val )
	{
		mask = PT_CP;
	}
	else	if ( uart_rece_info.rx_buffer[4] == sys_param_1b[MADD_D_PRI_ADD].val )
	{
		mask = PT_DP;
	}
	else
	{
		return 0;
	}
	TRACE_INFO("p_msg:data_len=[%04X],mask=[%02X],data=[%04X],[%04X]------------\r\n",data_len,mask,data, uart_trans_info.tx_buffer+uart_trans_info.tx_len  );
	ret_len = GetSysParam( data_len, mask, data, uart_trans_info.tx_buffer+uart_trans_info.tx_len );

	if (ret_len == 0)
		return 0;

	uart_trans_info.tx_len += ret_len;
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len,0x0000);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len+1] = (UCHAR8)(crc16>>8);
	uart_trans_info.tx_len+=2;
	UartStartTrans();
	
	return 1;	
}


/*************************************************************
Name:UartReceHandleMonSetPrara        
Description:监控命令中的设置参数
Input:数据指针，数据长度            
Output:void         
Return:1:成功，0:失败      
**************************************************************/
CHAR8 UartReceHandleMoSetPara(UCHAR8 *data,UINT16 data_len)
{
	UINT16 ret_len,crc16;
	UCHAR8 dev_add;
	UINT16 err_add;
	UCHAR8 ex_flag;
	UINT16 i;
	
	TRACE_DEBUG("485A Handle Set Param\r\n");

	UartPacketTransHead(uart_rece_info.rx_buffer[1],uart_rece_info.rx_buffer[2],uart_rece_info.rx_buffer[3],
			/*(UCHAR8)sys_param_1b[MADD_A_PRI_ADD].addr*/uart_rece_info.rx_buffer[4],uart_rece_info.rx_buffer[5],MONITOR_SUCCESS);	

	dev_add = uart_rece_info.rx_buffer[4];

	if ( dev_add == sys_param_1b[MADD_A_PRI_ADD].val )
	{
		ex_flag = 1;
		dev_add = SYS_A_FLAG;
	}
	else if ( dev_add == sys_param_1b[MADD_B_PRI_ADD].val )
	{
		ex_flag = 2;
		dev_add = SYS_B_FLAG;
	}
	else if ( dev_add == sys_param_1b[MADD_C_PRI_ADD].val )
	{
		ex_flag = 3;
		dev_add = SYS_C_FLAG;
	}
	else if ( dev_add == sys_param_1b[MADD_D_PRI_ADD].val )
	{
		ex_flag = 4;
		dev_add = SYS_D_FLAG;
	}	
	else
	{
		return 0;
	}

	BackupSystemPara(para_bak);

	// 设置参数
	if ( 0 != SetSysParam( data_len, ex_flag, data, &err_add ) )
	{
		// 保存参数
		SaveSysParamToFlash();
	}
	else
	{
		RestoreSystemPara(para_bak);
		return 0;
	}

	for(i =0;i<data_len; i++)
	{
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];
	}
	

	//设置完成有可能改变了设备地址
	if ( SYS_A_FLAG==dev_add ) 
	{
		uart_trans_info.tx_buffer[3] = (UCHAR8)sys_param_1b[MADD_A_PRI_ADD].val;
	}
	else if (SYS_B_FLAG==dev_add )
	{
		uart_trans_info.tx_buffer[3] = (UCHAR8)sys_param_1b[MADD_B_PRI_ADD].val;
	}
	else if (SYS_C_FLAG==dev_add )
	{
	uart_trans_info.tx_buffer[3] = (UCHAR8)sys_param_1b[MADD_C_PRI_ADD].val;
	}

	else if (SYS_D_FLAG==dev_add )
	{
		uart_trans_info.tx_buffer[3] = (UCHAR8)sys_param_1b[MADD_D_PRI_ADD].val;
	}
	
	
	//uart_trans_info.tx_len += ret_len;
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len,0x0000);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len+1] = (UCHAR8)(crc16>>8);
	uart_trans_info.tx_len+=2;
	UartStartTrans();
	
	return 1;
}

/*************************************************************
Name:UartReceHandleMoTransRe        
Description: 远程查询设置RE命令
Input:数据指针，数据长度            
Output:void         
Return:1:成功，0:失败      
**************************************************************/
CHAR8 UartReceHandleMoTransRe(UCHAR8 *data,UINT16 data_len)
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT16 tx_len;
	UINT16 i;
	UINT16 param_add;
	UCHAR8 param_len;
//	UCHAR8 re_cmd;//, re_fp, re_node;
	
	TRACE_DEBUG("485A Handle Trans RE-----------------\r\n");
	// 保存数据包的头信息，供RE应答的时候生成485数据包
	re_trans_head_bk[0] = uart_rece_info.rx_buffer[1];
	re_trans_head_bk[1] = uart_rece_info.rx_buffer[2];	
	re_trans_head_bk[2] = uart_rece_info.rx_buffer[3];		
	re_trans_head_bk[3] = uart_rece_info.rx_buffer[4];
	
	for ( i=0; i<data_len; i++ )
	{
//		TRACE_INFO("p_msg:[%02X]------------\r\n", data[i]);

	}
//	TRACE_INFO("p_msg:[%02X]------------\r\n", data[data_len-1]);
//	TRACE_INFO("uart_rece_info.rx_buffer[4]:[%02X]------------\r\n", uart_rece_info.rx_buffer[4]);
//#if 0
//	if ( uart_rece_info.rx_buffer[4] == sys_param_1b[MADD_A_PRI_ADD].val )	// A段地址
	{
		TRACE_DEBUG("485A Handle Trans RE-----------------\r\n");
		i = 0;
		re_trans_cmd = data[i++];
		re_trans_fp = data[i++];
		re_trans_node = data[i++];
		re_trans_rf=0;
		if ( (0==re_trans_fp)||(re_trans_fp>FP_MAX) )
		{
			return 0;
		}	
		
		if ( ((0==re_trans_node)||(re_trans_node>fp_inf[re_trans_fp-1].re_cnt) ) )
		{
			return 0;
		}
//		if ( 0xC1==re_trans_cmd )		// 设置参数
//		{
//			re_trans_cmd = MSG_CMD_SET_PARAM;
//		}
//		else if ( 0xC2==re_trans_cmd )	// 查询参数
//		{
//			re_trans_cmd = MSG_CMD_GET_PARAM;
//		}
//		else
//		{
//			return 0;
//		}
		TRACE_INFO("data_len:[%02X],i:[%02X]------------\r\n", data_len,i);
		if ( (i+3)>=data_len )		// 数据部分最少有一个参数，即2字节地址，1字节长度，因此数据包中应该至少还剩下4个字节的数据
		{
			return 0;
		}
		WTD_CLR;
		p_msg[MSG_DES_FP] = re_trans_fp;
		p_msg[MSG_DES_RE] = re_trans_node;
		p_msg[MSG_DES_REE] =re_trans_rf;
		p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
		p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
		p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;
		p_msg[MSG_CMD_ID] = MSG_CMD_RE_REMOTE;
		p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
		p_msg[MSG_RESERVE1] = MSG_RE_TRANS_RECV_CODE1;
		p_msg[MSG_RESERVE2] = MSG_RE_TRANS_RECV_CODE2;
		tx_len = MSG_PKT_HEAD_SIZE;

		p_msg[tx_len++] = re_trans_cmd;	// 子命令
		p_msg[tx_len++] = uart_rece_info.rx_buffer[4];//1;	// AB段标志: A
		TRACE_INFO("ABCD_FLAG:[%02X]------------\r\n", uart_rece_info.rx_buffer[4]);
		for ( i; i<data_len; i++ )
		{
			p_msg[tx_len++] = data[i];	// AB段标志: A
//			TRACE_INFO("p_msg:[%02X]------------\r\n", data[i]);

		}

#if 0		
		while ( (i+3)<data_len )
		{
			// 485接口地址
			param_add = data[i]|( (UINT16)data[i+1]<<8);
			i+=2;
			// 参数长度
			param_len = data[i++];
			// 485接口地址转换为模块下标地址
			if ( b_FALSE==ParamAddTranslate( param_len, param_add, PT_AP, &param_add ) )	
			{
				return 0;
			}
			// 下标地址
			p_msg[tx_len++] = (UCHAR8)(param_add&0x00FF);	
			p_msg[tx_len++] = (UCHAR8)((param_add>>8)&0x00FF);
			// 长度
			p_msg[tx_len++] = param_len;
			// 数据
			while ( param_len-- )
			{
				p_msg[tx_len++] = data[i++];	
			}
		}
#endif
		p_msg[tx_len] = 0;
		p_msg[tx_len+1] = 0;
		// 发送数据包到RE

		
	TRACE_INFO("Got Msg[%02X:%02X:%02X]->[%02X:%02X:%02X],cmd=%02X.\r\n", 
		p_msg[MSG_SRC_FP], p_msg[MSG_SRC_RE],p_msg[MSG_SRC_REE], p_msg[MSG_DES_FP], p_msg[MSG_DES_RE], p_msg[MSG_DES_REE],p_msg[MSG_CMD_ID]);

		SendMsgPkt(tx_len, p_msg);
		return 1;

	}
//#endif 	
	return 0;

	
}

/*************************************************************
Name:UartReceHandleMonError        
Description:监控错误处理
Input:错误内型            
Output:void         
Return:void         
**************************************************************/
void UartReceHandleMoError(UCHAR8 error_type)
{
	UINT16 crc16,i;

	TRACE_ERROR("485A Error:%02X", error_type);

	UartPacketTransHead(uart_rece_info.rx_buffer[1],uart_rece_info.rx_buffer[2],uart_rece_info.rx_buffer[3],
						uart_rece_info.rx_buffer[4],uart_rece_info.rx_buffer[5],error_type);
	
	//从接收的包中将数据COPY到发送缓存
	for (i=6; i<uart_rece_info.rx_len-4; i++)
	{
		uart_trans_info.tx_buffer[i]  = uart_rece_info.rx_buffer[i+1];
		uart_trans_info.tx_len++;
	}
	//CRC		
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len,0x0000);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len+1] = (UCHAR8)(crc16>>8);
	uart_trans_info.tx_len+=2;
	UartStartTrans();	
	
}

/*************************************************************
Name:UartReTransHandleAckMsg        
Description: 处理收到的远程访问RE指令的应答
Input:数据指针，数据长度            
Output: void         
Return: void
**************************************************************/
void UartReTransHandleAckMsg(UCHAR8 result, UCHAR8 *data,UINT16 data_len)
{
	UINT16 i = 0;
	UINT16 param_add;
	UCHAR8 param_len;
	UCHAR8 tmp;
	UINT16 crc16;
	
	if ( (i+3)>=data_len )		// 无有效参数数据，一个有效参数数据至少占用4字节长度
	{
		return;
	}

	switch( result )	// 命令执行结果
	{
	case MSG_ACK_CMD_OK:
		tmp = MONITOR_SUCCESS;
		break;

	case MSG_ACK_ERR_CRC:
		tmp = MONITOR_ERROR_CRC;
		break;
		
	case MSG_ACK_ERR_ADDR:
	case MSG_ACK_ERR_VALUE:
		if ( re_trans_cmd==0xC1 )		// 设置参数
		{
			tmp = MONITOR_ERROR_SET;
			break;
		}
		else if ( re_trans_cmd==0xC2 )		// 查询参数
		{
			tmp = MONITOR_ERROR_GET;
			break;
		}
		
	default:
		tmp = MONITOR_ERROR_OTHER;

	}

	// 生成数据包头
	UartPacketTransHead( re_trans_head_bk[0], re_trans_head_bk[1], re_trans_head_bk[2],
						re_trans_head_bk[3], MONITOR_CMD_RE_TRANS, tmp );
	// 子命令字及RE位置信息
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = re_trans_cmd;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = re_trans_fp;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = re_trans_node;
//	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = re_trans_rf;
	// 复位RE远程访问命令的相关数据
	re_trans_cmd = 0;
	re_trans_fp = 0;
	re_trans_node = 0;
	re_trans_rf = 0;
	// 参数数据
	while ( data_len-- )
	{
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = *data++;
	}
#if 0
	while ( (i+3)<data_len )
	{
		// 下标地址
		param_add = data[i]|( (UINT16)data[i+1]<<8);
		i+=2;
		// 参数长度
		param_len = data[i++];
		// 下标地址转换成485地址
		if ( 1==param_len )
		{
			if ( param_add<SYS_PARAM_1B_COUNT )
			{
				param_add = sys_param_1b[param_add].addr;
			}
			else 
			{
				return;
			}
		}
		else if ( 2==param_len )
		{
			if ( param_add<SYS_PARAM_2B_COUNT )
			{
				param_add = sys_param_2b[param_add].addr;
			}
			else
			{
				return;
			}
		}
		else if ( 4==param_len )
		{
			if ( param_add<SYS_PARAM_4B_COUNT )
			{
				param_add = sys_param_4b[param_add].addr;
			}
			else
			{
				return;
			}
		}
		else if ( param_add<SYS_PARAM_ASC_COUNT )	// 字符串参数
		{
			if ( param_len < sys_param_asc[param_add].length )	// 检查长度
			{
				param_add = sys_param_asc[param_add].addr;	// 参数485地址
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}

		if ( param_add != 0 )		// 有效的485地址不能为0
		{
			// 拷贝地址
			uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(param_add&0xFF);
			uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(param_add>>8);
			// 拷贝长度
			uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = param_len;
			// 拷贝数据
			while ( param_len-- )
			{
				uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i++];
			}
		}
		
	}
#endif
	//CRC		
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len,0x0000);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len+1] = (UCHAR8)(crc16>>8);
	uart_trans_info.tx_len+=2;
	UartStartTrans();	

}
#endif	// endif HXCT_VER


/*************************************************************
Name:UartStartTrans          
Description:开始发送
Input:void            
Output:void         
Return:void         
**************************************************************/
void PcStartTrans(void)
{
	UsbSendMsgPkt(pc_trans_info.tx_len,pc_trans_info.tx_buffer);
}
#if 0
/*************************************************************
Name:PcPacketTransHead          
Description:打包包头
Input:模块地址，命令字，应答标志            
Output:void         
Return:void         
**************************************************************/
void PcPacketTransHead(UCHAR8 type,UCHAR8 ver,UCHAR8 device,UCHAR8 address,UCHAR8 command,UCHAR8 ack)
{
	pc_trans_info.tx_buffer[0] = type;
	pc_trans_info.tx_buffer[1] = ver;	
	pc_trans_info.tx_buffer[2] = device;		
	pc_trans_info.tx_buffer[3] = address;
	pc_trans_info.tx_buffer[4] = command;	
	pc_trans_info.tx_buffer[5] = ack;
	pc_trans_info.tx_len = 6;
}
#endif

/*************************************************************
Name:PcPacketTransHead          
Description:打包包头
Input:模块地址，命令字，应答标志            
Output:void         
Return:void         
**************************************************************/
void PcPacketTransHead(UCHAR8 *tx_buffer)
{
	pc_trans_info.tx_buffer[0] = tx_buffer[0] ;
	pc_trans_info.tx_buffer[1] = tx_buffer[1] ;	
	pc_trans_info.tx_buffer[2] = tx_buffer[2] ;		
	pc_trans_info.tx_buffer[3] = tx_buffer[3] ;
	pc_trans_info.tx_buffer[4] = tx_buffer[4] ;	
	pc_trans_info.tx_buffer[5] = tx_buffer[5] ;
	pc_trans_info.tx_buffer[6] = tx_buffer[6] ;
	pc_trans_info.tx_buffer[7] = tx_buffer[7] ;	
	pc_trans_info.tx_buffer[8] = tx_buffer[8] ;	
	pc_trans_info.tx_buffer[9] = tx_buffer[9] ;	
	
	pc_trans_info.tx_len = MSG_CMD_BODY;
}
//#if 0
/*************************************************************
Name:UartReceHandleSetFtPara          
Description:设置收发器初始化序列
Input:数据指针，数据长度            
Output:void         
Return:1:成功，0:失败        
**************************************************************/
CHAR8 UartReceHandleSetFtPara(UCHAR8 *data,UINT16 data_len)
{
	UCHAR8 ft_ab,current_p,total_p;
	UINT16 cmd_cnt,i,j,k,mcuFpgaSpiStaus;
	UINT16 PKTlen;
	UCHAR8 cmd,cmd_result,length;
	UCHAR8 * tx_p = pc_trans_info.tx_buffer+MSG_CMD_BODY;
	UINT16 result_len;
	UCHAR8 * p_packet_head;
	data+=MSG_CMD_BODY;
	ft_ab = data[3];				//A,B
	current_p = data[4];			//当前包数
	total_p = data[5];				//总包数
	cmd_cnt = (data[6]<<8)|data[7];	//包中包含的命令个数

	PKTlen =( data[4]<<8)|data[5];	//总包数
	TRACE_INFO("@@@@@PKTlen=[%d],cmd_cnt=%d\r\n",PKTlen,cmd_cnt);


	
	p_packet_head = data+6;

	if((0==current_p)&&(	(TF_C!=ft_ab)||(!AD9369)||(	0x00==(0x01&(FpgaReadRegister(0x7a)>>14)))	)	)
	{
		TFInitCs( ft_ab);	//201503171043
	}
	if((0==current_p)&&(TF_C==ft_ab)&&(AD9369))
	{
		i=0;
		while((i<10000))
		{
			
			if(0x01==(0x01&(FpgaReadRegister(0x7a)>>15))	)
			{
				UsNopDelay(1);
				if(0==i%1000)
					WTD_CLR;
				continue;
			}
			i=0x3fff&FpgaReadRegister(0x8000|0x7b);

			FPGA_ENABLE_WRITE;
			FpgaWriteRegister(0x8000|0x7b,i);//201503171043
			FPGA_DISABLE_WRITE;	
			TRACE_INFO("FpgaWriteRegister(0x8000|0x7b,i)=[%x]\r\n",i);

			break;
			
		}	
	}

	if((0==current_p)	)
	{
		TFInitCs( ft_ab);	//201503171043
	}


	
	//应答包
//	PcPacketTransHead(0xdf,0x01,0x01,0x01,0xab,0x00);
	* tx_p++ = data[0];		//表格类型 9363
	TRACE_INFO("9363_TYPE[%02X]\r\n",data[0]);
	tx_p+=2;			//保留空间存储返回包的数据长度
	* tx_p++ = data[3];	//A,B
	* tx_p++ = data[4];	//当前包数
	* tx_p++ = data[5];	//总包数
	* tx_p++ = data[6];	//包中包含的命令个数
	* tx_p++ = data[7];	//包中包含的命令个数


	
	data += 8;	
	pc_trans_info.tx_len += 8;//8个字节头:1个字节表格类型--9363， 2字节返回包数据长度，1字节A,B标志，1字节当前包数，1字节总包数，2字节包中包含的命令个数，

	TRACE_DEBUG("from_pc:cmd_cnt[%d]=[%04x],data[0]=[%02x],data[1]=[%02x],data[2]=[%02x]\r\n\r\n",current_p,cmd_cnt,data[0],data[1],data[2]);	
	//执行命令
	for (i=0; i<cmd_cnt; i++)
	{
		WTD_CLR;

		
		cmd = data[0];

		switch(cmd)
		{		
			case CMD_BLOCK_WRITE:
				* tx_p++ = CMD_RESULT_IGNORE;
				pc_trans_info.tx_len++;
				data += CMD_BLOCK_WRITE_LEN;				
			break;
			
			case CMD_SPI_WRITE:

				FPGA_ENABLE_WRITE;
				cmd_result = CmdHandleSpiWrite(ft_ab,(data[1]<<8)|data[2],data[3]);
				FPGA_DISABLE_WRITE;
				* tx_p++ = cmd_result;
		
				pc_trans_info.tx_len++;
	
				data += CMD_SPI_WRITE_LEN;
			break;
			
			case CMD_WAIT:
				cmd_result = CmdHandleWait((data[1]<<8)|data[2]);
				* tx_p++ = cmd_result;
				pc_trans_info.tx_len++;
				data += CMD_WAIT_LEN;				
			break;
			
			case CMD_REFCLK_SCALE:
				* tx_p++ = CMD_RESULT_IGNORE;
				pc_trans_info.tx_len++;
				data += CMD_REFCLK_SCALE_LEN;
			break;

			case CMD_WAIT_CALDONE:
				FPGA_ENABLE_WRITE;
				cmd_result = CmdHandleWaitCaldone(ft_ab,data[1],(data[2]<<8)|data[3]);
				FPGA_DISABLE_WRITE;
				if((1!=cmd_result)&&(TF_A==ft_ab))
				{
					TRACE_DEBUG("error__________9363_CmdHandleWaitCaldone--cmd_result[%02x],addr=[%x],data=[%x]\r\n",cmd_result,data[1],(data[2]<<8)|data[3]);
						
				}				
				* tx_p++ = cmd_result;
				pc_trans_info.tx_len++;
				data += CMD_WAIT_CALDONE_LEN;
			break;

			case CMD_SPI_READ:
				FPGA_ENABLE_WRITE;
				cmd_result = ReadWriteTF(ft_ab,0,(data[1]<<8)|data[2],0);
				FPGA_DISABLE_WRITE;
				* tx_p++ = cmd_result;
				pc_trans_info.tx_len++;
				data += CMD_SPI_READ_LEN;
			break;
			case CMD_FPGA_WRITE:  break;

			
			case CMD_UPDATA_DATA:
				length=0;

				TRACE_INFO("9363_GetUpdateData........\r\n");
				cmd_result = GetUpdateData(ft_ab, data,&length);
					
				data += length;
				pc_trans_info.tx_len++;
			break;			

			case CMD_WAIT_FPGA_CFG:
#if 1
				k=0;
				while((TF_C==ft_ab)&&(AD9369)&&(k<10000))
				{
					k++;
					UsNopDelay(1);
					if(0==k%1000)
						WTD_CLR;
					//等待MCU读写SPI指示信号闲
					if(0x01==(0x01&(FpgaReadRegister(0x7a)>>15))	)
					{
						continue;
					}
					
					TRACE_INFO("( 0x00==(0x01&(FpgaReadRegister(0x7a)>>14))):%x\r\n",(	0x00==(0x01&(FpgaReadRegister(0x7a)>>14))));

					if((k<10000)&&(TF_C==ft_ab)&&(AD9369)&&(	0x00==(0x01&(FpgaReadRegister(0x7a)>>14)))	)
					{
						//切换成FPGA ROM SPI模式
						mcuFpgaSpiStaus=FpgaReadRegister(0x8000|0x7b);
						mcuFpgaSpiStaus&=0x3fff;
						mcuFpgaSpiStaus|=(0x02<<14);
						TRACE_INFO("1FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus):%x\r\n",mcuFpgaSpiStaus);
						FPGA_ENABLE_WRITE;
						FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus);
						FPGA_DISABLE_WRITE;
						//FPGA SPI 数据使能
						mcuFpgaSpiStaus=FpgaReadRegister(0x8000|0x7b);
						mcuFpgaSpiStaus&=0xdfff;
						mcuFpgaSpiStaus|=(0x1<<13);
						TRACE_INFO("2FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus):%x\r\n",mcuFpgaSpiStaus);
						FPGA_ENABLE_WRITE;
						FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus);
						FPGA_DISABLE_WRITE; 
						//等待FPGA ROM 写SPI 数据完成
						j=0;
						while((j<5000)&&(0x00==(0x01&(FpgaReadRegister(0x7a)>>14))	))
						{
							j++;
							UsNopDelay(1*1000);
							WTD_CLR;
						}
						
						//等待MCU读写SPI指示信号闲
						j=0;
						while((j<5000)&&(0x01==(0x01&(FpgaReadRegister(0x7a)>>15))	))
						{
							j++;
							UsNopDelay(1*1000);
							WTD_CLR;
						}

						//切换成MCU模拟控SPI
						mcuFpgaSpiStaus=FpgaReadRegister(0x8000|0x7b);
						mcuFpgaSpiStaus &= (~((1<<14)|(1<<15)));
						TRACE_INFO("3FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus):%x\r\n",mcuFpgaSpiStaus);
						FPGA_ENABLE_WRITE;
						FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus);
						FPGA_DISABLE_WRITE;
					}	
					break;
				}
				break;
			#endif	
			default:
				//错误命令				
		//		PcPacketTransHead(0xdf,0x01,0x01,0x01,0xab,0x01);
				TRACE_INFO("9363_错误命令\r\n");
				* tx_p++ = 0;
				pc_trans_info.tx_len++;
		
				goto out;
			break;
		}
	}

	//保存数据PKTlen
	SaveInitData(ft_ab,current_p,total_p,p_packet_head,data_len-6-MSG_CMD_BODY);//data_len-6-MSG_CMD_BODY 为总包个数之后的数据 长度不超过1005-2字节
	//SaveInitData(ft_ab,PKTlen,total_p,p_packet_head,data_len-6-MSG_CMD_BODY);//data_len-6-MSG_CMD_BODY 为总包个数之后的数据 长度不超过1005-2字?
out:
	result_len = pc_trans_info.tx_len-MSG_CMD_BODY;
	pc_trans_info.tx_buffer[MSG_CMD_BODY+1] = result_len;
	pc_trans_info.tx_buffer[MSG_CMD_BODY+2] = result_len>>8;	
	
	pc_trans_info.tx_buffer[MSG_CMD_BODY+2+result_len] = 0x00;
	pc_trans_info.tx_buffer[MSG_CMD_BODY+2+result_len+1] = 0x00;	
	
//	pc_trans_info.tx_buffer[8+result_len+2] = 0x4E;	
//	pc_trans_info.tx_len = 8+result_len+3;

	//PcStartTrans();
	SendMsgPkt( pc_trans_info.tx_len,pc_trans_info.tx_buffer );
	//写入FLASH
	
	return 1;	
	
	
}
//#endif 





/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : uart_app.c
* Description : RS485�ӿڲ���, 485-A����ͨѶ�˿�, 485-B͸���˿�
* Version     :v0.1
* Author      :RJ
* Date        :2008-08-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*	RJ		2010-06-11	v0.1			��ʼ�汾
**************************************************************/

#include "Header.h"

extern UCHAR8 para_bak[];
extern _T_PARAM_1B sys_param_1b[];
extern _T_PARAM_2B sys_param_2b[];
extern _T_PARAM_4B sys_param_4b[];
extern _T_MODULE_CFG mod_cfg_a;
extern UINT32 module_param_chg_flag;		//ϵͳ���������޸ı�־
extern _T_FP_INFO fp_inf[];		            // ���������Ϣ
extern _T_VALID_FP_TOPO valid_fp_topo[FP_MAX];
extern _T_FP_INFO fp_inf[FP_MAX];
extern _T_RE_INFO tmp_re_inf[FP_MAX][RE_MAX];		// RE��Ϣ����ʱ����

UCHAR8 uart_rx_buff[ UART_BUFF_SIZE ]; 
UCHAR8 uart_tx_buff[ UART_BUFF_SIZE ]; 
volatile UCHAR8 pc_tx_buff[ PC_BUFF_SIZE ];
UCHAR8 uart_test_tx_buff[20 ]; 
UCHAR8 uart_index=0; 
UCHAR8 uart_flag=0;


UCHAR8 re_trans_head_bk[4];		// Զ�̲�ѯ����RE�����485���ݰ�ͷ����:type, ver, device, address
UCHAR8 re_trans_cmd = 0;	// Զ�̲�ѯ����RE�������������
UCHAR8 re_trans_fp = 0;		// Զ�̲�ѯ����RE�����Ŀ�Ĺ��
UCHAR8 re_trans_node = 0;	// Զ�̲�ѯ����RE�����Ŀ�Ľڵ�
UCHAR8 re_trans_rf = 0;	// Զ�̲�ѯ����RE�����Ŀ����Ƶ�ڵ�

_T_UART_RECE uart_rece_info={0,0,uart_rx_buff,0};
_T_UART_TRANS uart_trans_info = {0,0,uart_tx_buff,0};
volatile _T_UART_TRANS pc_trans_info = {0,0,pc_tx_buff,0};
UCHAR8 trans_4e_flag = 0;		//����ʱ0X4Eת���־

//UCHAR8 rs485_rx_pkt_flag = 0;	// 485�����жϱ�־

// ͸��FIFOʹ��˫������ƣ��պͷ�����һ����ÿ�η�����ɺ��л�
_T_THR_FIFO uart_thr_tx_fifo[2];	// ͸�����ڷ���FPGA����FIFO
_T_THR_FIFO uart_thr_rx_fifo[2];	// ͸�����ڽ���FPGA����FIFO
UCHAR8 thr_utx_fifo_use;		// ��ʶ͸�����ڷ���ʹ�õ�FIFO��FPGA����ʹ����һ��FIFO
UCHAR8 thr_urx_fifo_use;		// ��ʶ͸�����ڽ���ʹ�õ�FIFO��FPGA����ʹ����һ��FIFO
UCHAR8 uart_thr_tx_end;		// ����͸�����ݷ�����ɱ�־
UCHAR8 fpga_thr_tx_end;		// FPGA͸�����ݷ�����ɱ�־

// ��λ͸��FIFO��״̬
void ResetThrFifo()
{
	memset( (UCHAR8*)uart_thr_tx_fifo, 0, sizeof(uart_thr_tx_fifo)*2 );
	thr_utx_fifo_use = 0;	// ���ڷ���ʹ��FIFO��0
	memset( (UCHAR8*)uart_thr_rx_fifo, 0, sizeof(uart_thr_rx_fifo)*2 );
	thr_urx_fifo_use = 0;	// ���ڽ���ʹ��FIFO��0
	uart_thr_tx_end = 1;	// ����͸�����ݷ������
	fpga_thr_tx_end = 1;	// FPGA͸�����ݷ������
}

// ͸�������жϺ���: �����ж�
void ThrUartIsrRxDat( UCHAR8 thr_dat )
{
	_T_THR_FIFO * p_fifo = &uart_thr_rx_fifo[thr_urx_fifo_use];	// FIFOָ��

	// FIFOδ��, �������ݵ�FIFO, ���ݼ���+1
	if ( p_fifo->count < THR_FIFO_SIZE )	
	{
		p_fifo->p_dat[ p_fifo->count++ ] = thr_dat;	
	}

	//printf("s");
}

// ͸�������жϺ���: ���;���
void ThrUartIsrTxReady( void )
{
	_T_THR_FIFO * p_fifo = &uart_thr_tx_fifo[thr_utx_fifo_use];	// FIFOָ��
	UCHAR8 tmp;

	// FIFO�����������������
	if ( p_fifo->count > 0 )
	{
		// ��FIFOȡ����,��ָ�����
		tmp = p_fifo->p_dat[ p_fifo->index++ ];
				
		// FIFO���ݼ���-1
		p_fifo->count --;

		// ����д�봮�ڷ��ͻ���
		thr_func.pf_send_byte( tmp );
	}

	// ��������������
	if ( 0 == p_fifo->count )
	{
		// �رշ��ͻ�����ж�
		thr_func.pf_ie_tx_ready(0);
		
		// ʹ�ܷ�������ж�
		thr_func.pf_ie_tx_complete(1);
	}

}

// ͸�������жϺ���: �������
void ThrUartIsrTxComplete( void )
{
	_T_THR_FIFO * p_fifo = &uart_thr_tx_fifo[thr_utx_fifo_use];	// FIFOָ��

	// �رշ�������ж�
	thr_func.pf_ie_tx_complete(0);
	
	// ��������������
	if ( 0 == p_fifo->count )
	{
		p_fifo->index = 0;
		
		// ������ɣ��������ģʽ
		thr_func.pf_tx_finish();
		
		// �÷�����ɱ�־
		uart_thr_tx_end = 1;
	}
	else	// ���廹������(!!!��������²����ܳ��ִ����)
	{
		// ʹ�ܷ��ͻ�����жϣ���������
		thr_func.pf_ie_tx_ready(1);
	}
}

/*************************************************************
Name:UartBTransTSW0      
Description:����͸������
Input:tsw0_dat:͸����������         
Output:void         
Return:void         
**************************************************************/
void UartTransThrDat()
{
	_T_THR_FIFO * p_fifo;	// FIFOָ��
	UCHAR8 fifo_id;

	// �õ�FPGA����ʹ�õ�FIFO ID
	fifo_id = (0==thr_utx_fifo_use) ? 1 : 0;

	// FPGA����FIFO��ָ��
	p_fifo = &uart_thr_tx_fifo[fifo_id];
	//TRACE_INFO("p_fifo->count---------[%x],thr_utx_fifo_use=[%x]\r\n",p_fifo->count,thr_utx_fifo_use);
	// ��FIFO��Ϊ�����л�FIFO����������
	if ( 0 != p_fifo->count )
	{
		// FIFO��������FPGA����FIFO��Ϊ���ڵķ���FIFO
		thr_utx_fifo_use = fifo_id;

		// ��֮ǰ�Ĵ��ڵķ���FIFO��ΪFPGA�Ľ���FIFO
		fifo_id = 1 - thr_utx_fifo_use;

		// ���FPGA����FIFO
		memset( (UCHAR8*)&(uart_thr_tx_fifo[fifo_id]), 0, sizeof(_T_THR_FIFO) );
		
		// ��������
		p_fifo->index = 0;
		uart_thr_tx_end = 0;
		thr_func.pf_tx_start();
	}
}


//#ifdef HXCT_VER
#if  0

/*************************************************************
Name:UartReceInterrupt          
Description:�жϵ��ý��մ������
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartReceInterrupt( UCHAR8 rx_dat )
{
	uart_rece_info.rx_data = rx_dat;
	
	WTD_CLR;
	if (0 != (sys_work_info&SYSTEM_FLAG_232_RECE))	// ��һ�ʰ���û������
	{
		return;
	}

	//��ؽӿ�
	switch(uart_rece_info.rx_count)
	{
		//��ͷ
		case 0:
			if (uart_rece_info.rx_data != 0x7E)
				return;
		break;	
		//ģ����
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
		//�����峤��
		case 4:
			//��ȡ���ݳ��ȸ�4λ
			uart_rece_info.rx_len = (uart_rece_info.rx_data&0xf0)>>4;
			uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = uart_rece_info.rx_data;	// Ӧ���־
		break;
		
		case 5:
			//��ȡ���ݳ��ȵ�8λ
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
				//������ȡ���				
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
	if (uart_rece_info.rx_count > (UART_BUFF_SIZE-2))	// ���ݹ���,�ж�Ϊ��Ч���ݰ�
		uart_rece_info.rx_count = 0;

}


/*************************************************************
Name:UartTransInterrupt          
Description:�жϵ��÷��ʹ�����
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartTransInterrupt(void)
{
	//�жϷ���ʱ��һ�������Ѿ����ͳ�ȥ��
	if (uart_trans_info.tx_count<= uart_trans_info.tx_len)
	{
		CtrlUartSendDat( uart_trans_info.tx_buffer[uart_trans_info.tx_count++] );
	}
	else if (uart_trans_info.tx_count == uart_trans_info.tx_len+1)	// �෢��һ���ַ�
	{	
		CtrlUartSendDat(0x00);
		uart_trans_info.tx_count++;
	}
	else
	{
		//��ʱ��485����ʹ�ܹر�			
		EnableUartTx(0, 0);	
		return;
	}

}
//#if 0
/*************************************************************
Name:UartStartTrans          
Description:��ʼ����
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
Description:�����ͷ
Input:ģ���ַ�������֣�Ӧ���־            
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
Description:��12		��չICSģ���ѯ�����Ӧ����
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:���ݳ���
**************************************************************/
#ifdef HX_PROTOCOL_1230		// ����20111230Э��
UINT16 MonHXGetStatusPara(UCHAR8 * data ,UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 * bak_data = data;
	UINT16 i;
	UCHAR8 tmp;
	UINT16 val;
	
	//����״̬(1�ֽ�)
	tmp = 0;
	if ( 0 != sys_param_1b[MADD_FPS_BCCH_LK_ST].val ) { tmp |= (1<<7); }	// ����BCCH�Ƿ�ɹ�,1-�ɹ�
	if ( 0 != sys_param_1b[MADD_FPS_MOSVC_LK_ST].val ) { tmp |= (1<<6); }	// ������Ӫ���Ƿ�ɹ�,1-�ɹ�
	if ( 0 != sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val ) { tmp |= (1<<5); }	// ����Ƶ���Ƿ�ɹ�,1-�ɹ�
	if ( 0 != sys_param_1b[MADD_LOW_POWER].val ) { tmp |= (1<<3); }	// �͹��Ŀ���,1-ON
	if (( 0==up_down )&&( 0!=sys_param_1b[(0==ab_flag) ? MADD_A_LTHR_EN : MADD_B_LTHR_EN].val ))
	{ 
		tmp |= (1<<2); 		// ��������ʹ�ܿ���,1-ON
	}
	if ( 0!=sys_param_1b[(0==ab_flag) ? MADD_A_UL_WORK_EN : MADD_B_UL_WORK_EN].val )
	{
		tmp |= (1<<0);		// ����ģ���ܿ���, 1-ON
	}
	*data++ = tmp;

	//�ŵ�����(4�ֽ�)
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
			tmp |= 1;	// ͨ������, 1-ON
		}
	}
	*data++ = tmp;

	// ����״̬(4�ֽ�)
	*data++ = 0;
	*data++ = 0;
	tmp = 0;
	for ( i=0; i<8; i++ )
	{
		tmp <<= 1;
		if ( 0 != sys_param_1b[MADD_FP8_LOF-i].val ) { tmp |= 1; }	// ���շ�״̬�澯, 1-ALARM, REֻ�й��1��2
	}
	*data++ = tmp;
	tmp = 0;
	if ( 0 != sys_param_1b[MADD_TOPO_CHG_ALM].val ) { tmp |= (1<<7); }		// ��·״̬�澯,1-ALARM
	if ( 0 != sys_param_1b[MADD_BER_ALARM].val ) { tmp |= (1<<6); }		// ������ƫ�߸澯,1-ALARM
	if ( 0 != sys_param_1b[MADD_CLK_PLL_ST].val ) { tmp |= (1<<4); }		// ʱ��ʧ��,1-UNLOCK
	if ( 0 != sys_param_1b[MADD_FPGA_CLK_ST].val ) { tmp |= (1<<3); }		// FPGA����״̬,1-UNLOCK
	tmp |= (0x03 & sys_param_1b[MADD_LOAD_FPGA_ST].val );		// ģ���ʼ��FPGA״̬
	*data++ = tmp;

	//ѡƵƵ��(1�ֽ�), 0:GSM,1:WCDMA
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
	
	// ���������������(2�ֽ�)
	val = sys_param_2b[(0==ab_flag) ? MADD_A_UCH_MAX_POW1 : MADD_B_UCH_MAX_POW1].val;
	*data++ = (UCHAR8)(val);
	*data++ = (UCHAR8)(val>>8);

	//���빦��(2�ֽ�)
	val = sys_param_2b[(0==ab_flag) ? MADD_A_DL_TOTAL_POW : MADD_B_DL_TOTAL_POW].val;
	*data++ = (UCHAR8)(val);
	*data++ = (UCHAR8)(val>>8);
	
	//�������(2�ֽ�)
	val = sys_param_2b[(0==ab_flag) ? MADD_A_UL_TOTAL_POW : MADD_B_UL_TOTAL_POW].val;
	*data++ = (UCHAR8)(val);
	*data++ = (UCHAR8)(val>>8);

	//ATT(1�ֽ�)
	if ( 0==up_down )
	{// ����
		*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_UCH_ATT1 : MADD_B_UCH_ATT1].val;
	}
	else
	{// ����
		*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_DCH_ATT1 : MADD_B_DCH_ATT1].val;
	}

	//������ƽ����(1�ֽ�)
	*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_LTHR_DN: MADD_B_LTHR_DN].val;		// ���е�������������

	//��������(1�ֽ�)
	*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_DL_PA_GAIN: MADD_B_DL_PA_GAIN].val;		// ���й�������

	//˫����˥��(1�ֽ�)
	val = sys_param_2b[(0==ab_flag) ? MADD_A_UDPX_IN_GAIN: MADD_B_UDPX_IN_GAIN].val;		// ����˫����˥��
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);
	val = sys_param_2b[(0==ab_flag) ? MADD_A_UDPX_OUT_GAIN: MADD_B_UDPX_OUT_GAIN].val;		// ���˫����˥��
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);

	// Զ�˻��ڵ�״̬
	*data++ = sys_param_1b[MADD_RE_NODE_MODE].val;

//#ifdef FUNC_FREQ_POINT_SEARCH_EN	// ����Ƶ����������
	// Ƶ��������ز��� BCCH
	*data++ = sys_param_1b[MADD_FPS_RFRANGE_SEL].val;		// Ƶ��ѡ��
	*data++ = sys_param_1b[MADD_FPS_MOSVC_SEL].val;		// ��Ӫ��ѡ��
	val = sys_param_2b[MADD_FPS_BCCH_FC_M].val;			// ��С��BCCH�ŵ���
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);
	*data++ = sys_param_1b[MADD_FPS_BCCH_POW_M].val;		// ��С��BCCH����ǿ��
	val = sys_param_2b[MADD_FPS_CID].val;					// С��ʶ����ʵʱֵ
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);
	val = sys_param_2b[MADD_FPS_AREA_ID].val;				// λ��������
	*data++ = (UCHAR8)(val&0xFF);
	*data++ = (UCHAR8)(val>>8);
	*data++ = sys_param_1b[MADD_FPS_BS_ID].val;			// ��վʶ����
	for ( i=0; i<6; i++ )										// ��С��BCCH�ŵ���
	{
		val = sys_param_2b[MADD_FPS_BCCH_FC_1+i].val;			
		*data++ = (UCHAR8)(val&0xFF);
		*data++ = (UCHAR8)(val>>8);
	}
	for ( i=0; i<6; i++ )										// ��С��BCCH����ǿ��
	{
		*data++ = sys_param_1b[MADD_FPS_BCCH_POW_1+i].val;
	}
	for ( i=0; i<6; i++ )										// ��С��CIDʶ����
	{
		val = sys_param_2b[MADD_FPS_CID_1+i].val;	
		*data++ = (UCHAR8)(val&0xFF);
		*data++ = (UCHAR8)(val>>8);
	}

	//ͨ����N(1�ֽ�)+�����ŵ���(N*2�ֽ�)
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

	// Ƶ��������ز��� CA
	*data++ = sys_param_1b[MADD_FPS_CA_COUNT].val;		// ��Ч�ŵ���
	for ( i=0; i<sys_param_1b[MADD_FPS_CA_COUNT].val; i++ )		// CA�ŵ���
	{
		val = sys_param_2b[MADD_FPS_CA_FC_0+i].val;			
		*data++ = (UCHAR8)(val&0xFF);
		*data++ = (UCHAR8)(val>>8);
	}

	return (data-bak_data);	
	
}
#else	// ����20110629Э��
UINT16 MonHXGetStatusPara(UCHAR8 * data ,UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 * bak_data = data;
	UINT16 i;
	UCHAR8 tmp;
	
	//����״̬(1�ֽ�)
	tmp = 0;
	if ( 0 != sys_param_1b[MADD_LOW_POWER].val ) { tmp |= (1<<3); }	// �͹��Ŀ���,1-ON
	if (( 0==up_down )&&( 0!=sys_param_1b[(0==ab_flag) ? MADD_A_LTHR_EN : MADD_B_LTHR_EN].val ))
	{ 
		tmp |= (1<<2); 		// ��������ʹ�ܿ���,1-ON
	}
	if ( 0!=sys_param_1b[(0==ab_flag) ? MADD_A_UL_WORK_EN : MADD_B_UL_WORK_EN].val )
	{
		tmp |= (1<<0);		// ����ģ���ܿ���, 1-ON
	}
	*data++ = tmp;

	//�ŵ�����(4�ֽ�)
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
			tmp |= 1;	// ͨ������, 1-ON
		}
	}
	*data++ = tmp;

	// ����״̬(4�ֽ�)
	*data++ = 0;
	*data++ = 0;
	tmp = 0;
	for ( i=0; i<8; i++ )
	{
		tmp <<= 1;
		if ( 0 != sys_param_1b[MADD_FP8_LOF-i].val ) { tmp |= 1; }	// ���շ�״̬�澯, 1-ALARM
	}
	*data++ = tmp;
	tmp = 0;
	if ( 0 != sys_param_1b[MADD_TOPO_CHG_ALM].val ) { tmp |= (1<<7); }		// ��·״̬�澯,1-ALARM
	if ( 0 != sys_param_1b[MADD_BER_ALARM].val ) { tmp |= (1<<6); }		// ������ƫ�߸澯,1-ALARM
	if ( 0 != sys_param_1b[MADD_CLK_PLL_ST].val ) { tmp |= (1<<4); }		// ʱ��ʧ��,1-UNLOCK
	if ( 0 != sys_param_1b[MADD_FPGA_CLK_ST].val ) { tmp |= (1<<3); }		// FPGA����״̬,1-UNLOCK
	tmp |= (0x03 & sys_param_1b[MADD_LOAD_FPGA_ST].val );		// ģ���ʼ��FPGA״̬
	*data++ = tmp;

	//ѡƵƵ��(1�ֽ�), 0:GSM,1:WCDMA
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
	
	// ���������������(2�ֽ�)
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_UCH_MAX_POW1 : MADD_B_UCH_MAX_POW1].val);
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_UCH_MAX_POW1 : MADD_B_UCH_MAX_POW1].val>>8);

	//���빦��(2�ֽ�)
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_DL_TOTAL_POW : MADD_B_DL_TOTAL_POW].val);
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_DL_TOTAL_POW : MADD_B_DL_TOTAL_POW].val>>8);
	
	//�������(2�ֽ�)
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_UL_TOTAL_POW : MADD_B_UL_TOTAL_POW].val);
	*data++ = (UCHAR8)(sys_param_2b[(0==ab_flag) ? MADD_A_UL_TOTAL_POW : MADD_B_UL_TOTAL_POW].val>>8);

	//ATT(1�ֽ�)
	if ( 0==up_down )
	{// ����
		*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_UCH_ATT1 : MADD_B_UCH_ATT1].val;
	}
	else
	{// ����
		*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_DCH_ATT1 : MADD_B_DCH_ATT1].val;
	}

	//������ƽ����(1�ֽ�)
	*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_LTHR_DN: MADD_B_LTHR_DN].val;		// ���е�������������

	//ͨ����N(1�ֽ�)+�����ŵ���(N*2�ֽ�)
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
Description:��չ���ò�ѯ��Ĳ�ѯ����ظ�
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:���ݳ���
**************************************************************/
UINT16 MonHXGetSubPara(UCHAR8 * data ,UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 * bak_data = data;
	UINT16 i;
	UCHAR8 tmp;

	//��ģ�鿪��(2�ֽ�)
	*data++ = 0;		// ��8λ�޹�ģ�飬Ϊ0
	tmp = 0;
	for ( i=0; i<8; i++ )
	{
		tmp <<= 1;
		if ( 0 != sys_param_1b[MADD_FP8_EN-i].val ) { tmp |= 1; }	// ��ģ�鿪��, 1-ON
	}
	*data++ = tmp;

	//��ģ�����(1�ֽ�)
	*data++ = FP_MAX;

	//ͨ����N(1�ֽ�)+ͨ������ֵ(N*1�ֽ�)
	if ( 0==ab_flag )
	{
		tmp = sys_param_1b[MADD_A_CHANNEL_COUNT].val;
		*data++ = tmp;
		for ( i=0; i<tmp; i++ )
		{
			*data++ = 0;		// REC��֧�����úͲ�ѯͨ������ֵ
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

	//��ʱ����(2�ֽ�)
	*data++ = 0;			// REC��֧�����úͲ�ѯ��ʱ����
	*data++ = 0;

	//�Զ�ʱ�ӿ���(1�ֽ�)
	*data++ = sys_param_1b[MADD_DELAY_MODE].val;		// �Զ�ʱ�ӿ���, 1-ON

	//Mcu�¶�(1�ֽ�)
	*data++ = sys_param_1b[MADD_BOARD_TEMP].val;

	//�͹��Ŀ���(1�ֽ�)
	*data++ = sys_param_1b[MADD_LOW_POWER].val;		// �͹��Ŀ���,1-ON

	//�Զ�/�ֶ�ѡƵ(1�ֽ�)
	*data++ = 0;		// 1���Զ�ѡƵ, 0���ֶ�ѡƵ

	//����ʱ϶ռ����(1�ֽ�)
	*data++ = sys_param_1b[(0==ab_flag) ? MADD_A_BUSY_TIME : MADD_B_BUSY_TIME].val;
	
	//����ʱ϶ռ����ͳ��״̬(1�ֽ�)
	*data++ = sys_param_1b[MADD_TRAFFIC_END].val;

	//�豸·�ɵǼǵ�ַ(4�ֽ�)
	*data++ = (UCHAR8)(sys_param_4b[MADD_DEV_ADDR].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_DEV_ADDR].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_DEV_ADDR].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_DEV_ADDR].val>>24);

	//�����Զ˹�ں�1(4�ֽ�)
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>24);

	//�����Զ˹�ں�1(4�ֽ�)
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPS_PORT].val>>24);

	//Զ�˻��ڵ����1(4�ֽ�), ���1-4
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT1].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT1].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT1].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT1].val>>24);

	//Զ�˻��ڵ����2(4�ֽ�), ���5-8
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT2].val);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT2].val>>8);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT2].val>>16);
	*data++ = (UCHAR8)(sys_param_4b[MADD_OPT_RE_COUNT2].val>>24);

	//Զ�˻��ڵ����3,4(2*4�ֽ�), ���9-16
	for ( i=0; i<8; i++ )
	{
		*data++ = 0;
	}

	//Զ�˻��ڵ�״̬(1�ֽ�)
	*data++ = 0;		// REC��Ч

	//��·�����ʱ(2�ֽ�)
	*data++ = (UCHAR8)(sys_param_2b[MADD_MAX_T14].val);
	*data++ = (UCHAR8)(sys_param_2b[MADD_MAX_T14].val>>8);

	//�ڵ��·��ʱ(2�ֽ�)
	*data++ = 0;		// REC��Ч
	*data++ = 0;		// REC��Ч

	//�ڵ��·��ʱ(2�ֽ�)
	*data++ = 0;		// REC��Ч
	*data++ = 0;		// REC��Ч

	//WLAN����1-4״̬(4*1�ֽ�)
	*data++ = sys_param_1b[MADD_WLAN_CONN_ST1].val;
	*data++ = sys_param_1b[MADD_WLAN_CONN_ST2].val;
	*data++ = sys_param_1b[MADD_WLAN_CONN_ST3].val;
	*data++ = sys_param_1b[MADD_WLAN_CONN_ST4].val;

	//WLAN�����ٶ�����1-4(4*1�ֽ�)
	*data++ = sys_param_1b[MADD_WLAN_SPEED1].val;
	*data++ = sys_param_1b[MADD_WLAN_SPEED2].val;
	*data++ = sys_param_1b[MADD_WLAN_SPEED3].val;
	*data++ = sys_param_1b[MADD_WLAN_SPEED4].val;

	return (data-bak_data);	

}

/*************************************************************
Name:MonHXSetNormalPara
Description:��չ���ò�ѯ��Ĳ�ѯ����ظ�
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
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
				module_param_chg_flag |= PCHG_A_POW_GAIN;//((0==up_down) ? PCHG_A_UL_GAIN : PCHG_A_DL_GAIN);	// ���޸Ĳ�����־
			}
			else
			{
				module_param_chg_flag |= PCHG_B_POW_GAIN;//((0==up_down) ? PCHG_A_UL_GAIN : PCHG_A_DL_GAIN);	// ���޸Ĳ�����־
			}
		}
		else
		{
			return 0;
		}
		//�Ƿ񱣴�ATT
		if ( 0 != (data[0]&0x80) )	// ���λ����1���˴����õ�ATT����ֵ���ñ���
		{
			return 2;
		}
	break;
	
	case HXCT_CMD_SET_ONOFF:		// ����ʹ��
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

	case HXCT_CMD_SET_NOISE_ON:		// ��������ʹ��
		if ( data[0]>1 ) return 0;

		addr = (0==ab_flag) ? MADD_A_LTHR_EN : MADD_B_LTHR_EN;
		if ( sys_param_1b[addr].val == data[0] )
		{
			return 2;
		}
		sys_param_1b[addr].val = data[0];
		module_param_chg_flag |= ((0==ab_flag) ? PCHG_A_LTHR: PCHG_B_LTHR);
	break;

	case HXCT_CMD_SET_NOISE_GATE:		// �������Ƶ�ƽ������MADD_B_LTHR_DN
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

	return 1;	// ���óɹ�����Ҫ�������
}


#ifdef HX_PROTOCOL_1230		// ����20111230Э��
/*************************************************************
Name: HxExtraSetLowPowerMode
Description: ��չ����->�͹���ģʽ����
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 HxExtraSetLowPowerMode( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	return 0;		// REC��ֹ�͹���
}


/*************************************************************
Name: HxExtraSetPaGain
Description: ��չ����->��������
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 HxExtraSetPaGain( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	return 0;	// REC��֧�����ù�������
}

/*************************************************************
Name: HxExtraSetDpxInAtt
Description: ��չ����->����˫����˥��
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 HxExtraSetDpxInAtt( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	UCHAR8 tmp;
	UINT16 addr;
	UINT16 val16;

	if ( up_down==0 ) return 0;	// ��֧����������

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
Description: ��չ����->���˫����˥��
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 HxExtraSetDpxOutAtt( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
	UCHAR8 tmp;
	UINT16 addr;
	UINT16 val16;

	if ( up_down==1 ) return 0;	// ��֧����������

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
Description: ��չ����->Ƶ������:��Ƶ�ŵ���BCCH
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 HxExtraSetFpsLockBcch( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN	// ����Ƶ����������

	UINT16 val16;

	val16 = data[0]|(data[1]<<8);
	
	if ( val16 != sys_param_2b[MADD_FPS_BCCH_LK_SET].val )
	{
		sys_param_2b[MADD_FPS_BCCH_LK_SET].val = val16;
		if ( b_FALSE==FPS_CheckParam(SYS_A_FLAG) )
		{
			return 0;	// ����
		}
		module_param_chg_flag |= PCHG_FPS_RANGE;
		return 1;
	}
	else
	{
		return 2;		// ����ֵû�ı�
	}
	
#else
	return 0;
#endif
}

/*************************************************************
Name: HxExtraSetAutoDelayMode
Description: ��չ����->�Զ���ʱ��������
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 HxExtraSetFpsParam( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN	// ����Ƶ����������

	UCHAR8 chg_flag = 0;
	
	if ( data[0]!=sys_param_1b[MADD_FPS_RFRANGE_SEL].val )	// Ƶ��ѡ��
	{
		sys_param_1b[MADD_FPS_RFRANGE_SEL].val = data[0];
		chg_flag = 1;
	}

	if ( data[1]!=sys_param_1b[MADD_FPS_MOSVC_SEL].val )		// ��Ӫ��ѡ��
	{
		sys_param_1b[MADD_FPS_MOSVC_SEL].val = data[1];
		chg_flag = 1;
	}

	if ( 0==chg_flag )
	{
		return 2;		// ����ֵû�ı�
	}
	else
	{
		if ( b_FALSE==FPS_CheckParam(SYS_A_FLAG) )
		{
			return 0;	// ����
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
Description: ��չ����->Ƶ������:��С��ʶ����CID
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 HxExtraSetFpsLockCid( UCHAR8 * data, UCHAR8 up_down, UCHAR8 ab_flag )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN	// ����Ƶ����������

	UINT16 val16;

	val16 = data[0]|(data[1]<<8);
	
	if ( val16 != sys_param_2b[MADD_FPS_CID_LK_SET].val )
	{
		sys_param_2b[MADD_FPS_CID_LK_SET].val = val16;
		if ( b_FALSE==FPS_CheckParam(SYS_A_FLAG ) )
		{
			return 0;	// ����
		}
		module_param_chg_flag |= PCHG_FPS_RANGE;
		return 1;
	}
	else
	{
		return 2;		// ����ֵû�ı�
	}

#else
	return 0;
#endif

}

/*************************************************************
Name: HxExtraSetAutoDelayMode
Description: ��չ����->�Զ���ʱ��������
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
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
		return 2;		// ����ֵû�ı�
	}
}

/*************************************************************
Name: HxExtraSetDelayOffset
Description: ��չ����->��·��ʱ����
Input: up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output: void         
Return: ������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
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
		return 2;		// ����ֵû�ı�
	}

}
#endif

/*************************************************************
Name:MonHXSetExtraPara
Description:��չ���ò�ѯ��Ĳ�ѯ����ظ�
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 MonHXSetExtraPara(UCHAR8 sub_cmd, UCHAR8 * data , UINT16 body_len, UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 tmp;
	UINT16 addr;
	UINT16 val16;
	UINT32 i;

	switch(sub_cmd)
	{
	case HXCT_SUBCMD_SET_POWER:		// ����ͨ����������������
		if ( up_down==1 ) return 0;	// REC��֧��������������������
		val16 = data[0]|(data[1]<<8);
//		if ( (INT16)val16>5 )		// ���5db
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
	
	case HXCT_SUBCMD_SET_GAIN:		// ��������ͨ���������
//		tmp = (0==ab_flag) ? sys_param_1b[MADD_A_CHANNEL_COUNT].val : sys_param_1b[MADD_B_CHANNEL_COUNT].val;
//		addr = (0==ab_flag) ? MADD_A_DCH_GAIN1 : MADD_B_DCH_GAIN1;
//		for ( i=0; i<tmp; i++ )
//		{
//			
//		}
		return 0;		// REC��֧������ͨ������

	break;

	case HXCT_SUBCMD_SET_FRE_NUM:		// �����ŵ���
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
					tmp = 0;		// �޸Ĳ�����־
				}
				sys_param_2b[MADD_A_DL_CHANNEL1+i].val = val16;
				sys_param_2b[MADD_A_UL_CHANNEL1+i].val = val16;
			}
			//if ((i>0)&&( b_FALSE==CheckChannelSetA() ))
			//{
			//	return 0;	// ����
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
					tmp = 0;		// �޸Ĳ�����־
				}
				sys_param_2b[MADD_B_DL_CHANNEL1+i].val = val16;
				sys_param_2b[MADD_B_UL_CHANNEL1+i].val = val16;
			}
			//if ((i>0)&&( b_FALSE==CheckChannelSetB() ))
			//{
			//	return 0;	// ����
			//}
		}
		if ( tmp!=0 ) return 2;		// ����û�䣬����Ҫ����
		module_param_chg_flag |= ((0==ab_flag) ? PCHG_A_CHANNEL: PCHG_B_CHANNEL);
	break;

	case HXCT_SUBCMD_SET_CH_EN:		// �����ŵ�����
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
					val16 = 0;		// �޸Ĳ�����־
				}
				sys_param_1b[MADD_A_DCH_EN1+i].val = tmp;
				sys_param_1b[MADD_A_UCH_EN1+i].val = tmp;
			}
			//if ((i>0)&&( b_FALSE==CheckChannelSetA() ))
			//{
			//	return 0;	// ����
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
					val16 = 0;		// �޸Ĳ�����־
				}
				sys_param_1b[MADD_B_DCH_EN1+i].val = tmp;
				sys_param_1b[MADD_B_UCH_EN1+i].val = tmp;
			}
			//if ((i>0)&&( b_FALSE==CheckChannelSetB() ))
			//{
			//	return 0;	// ����
			//}
		}
		if ( val16!=0 ) return 2;		// ����û�䣬����Ҫ����
		module_param_chg_flag |= ((0==ab_flag) ? PCHG_A_CHANNEL: PCHG_B_CHANNEL);
	break;

	case HXCT_SUBCMD_SET_OPT_EN:		// ��ģ�鿪��
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
				val16 = 0;		// �޸Ĳ�����־
			}
			sys_param_1b[MADD_FP1_EN+i].val = tmp;
		}
		if ( val16!=0 ) return 2;		// ����û�䣬����Ҫ����
		module_param_chg_flag |= PCHG_SYS_FP_EN;
	break;


#ifdef HX_PROTOCOL_1230		// ����20111230Э��
	case HXCT_SUBCMD_SET_PD_MODE:		// ���õ͹��Ŀ���(1230Э��)
		return HxExtraSetLowPowerMode( data, up_down, ab_flag );
		break;
	
	case HXCT_SUBCMD_SET_PA_GAIN:		// �������й�������(1230Э��)
		return HxExtraSetPaGain( data, up_down, ab_flag );
		break;

	case HXCT_SUBCMD_SET_DPX_IA:		// ��������˫����˥��(1230Э��)
		return HxExtraSetDpxInAtt( data, up_down, ab_flag );
		break;

	case HXCT_SUBCMD_SET_DPX_OA:		// �������˫����˥��(1230Э��)
		return HxExtraSetDpxOutAtt( data, up_down, ab_flag );
		break;

	case HXCT_SUBCMD_SET_FPS_BCCH:		// ������Ƶ�ŵ���(1230Э��)
		return HxExtraSetFpsLockBcch( data, up_down, ab_flag );
		break;
		
	case HXCT_SUBCMD_SET_FPS_PARA:		// ������Ӫ�̺�Ƶ��ѡ��(1230Э��)
		return HxExtraSetFpsParam( data, up_down, ab_flag );
		break;
		
	case HXCT_SUBCMD_SET_FPS_CID:		// ��������С��ʶ����ʵʱֵ(1230Э��)
		return HxExtraSetFpsLockCid( data, up_down, ab_flag );
		break;
				
	case HXCT_SUBCMD_SET_DELAY_M:		// �����Զ���ʱ����(1230Э��)
		return HxExtraSetAutoDelayMode( data, up_down, ab_flag );
		break;

	case HXCT_SUBCMD_SET_RE_DELAY:		// ���ù�·��ʱ����(1230Э��)
		return HxExtraSetDelayOffset( data, up_down, ab_flag );
		break;

#else	// ����20110629Э��
	case HXCT_SUBCMD_SET_DELAY:		// ������ʱ����ֵ
		tmp = 1;
		// �Զ�ʱ�ӿ���
		if ( data[0]>1 ) return 0;
		if ( data[0]!=sys_param_1b[MADD_DELAY_MODE].val ) tmp = 0;
		sys_param_1b[MADD_DELAY_MODE].val = *data++;
		// ��ʱ����
		val16 = data[0]|(data[1]<<8);
		data += 2;
		if ( val16 != sys_param_2b[MADD_DL_DELAY_OFFSET].val ) tmp = 0;
		sys_param_2b[MADD_DL_DELAY_OFFSET].val = val16;
		// �͹��Ŀ���
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

	return 1;	// ���óɹ�����Ҫ�������
}


/*************************************************************
Name:MonHXSetSubPara
Description:��չ���ò�ѯ��Ĳ�ѯ����ظ�
Input:up_down:0-UL, 1-DL; ab_flag:0-A, 1-B
Output:void         
Return:������:0-ʧ�ܣ�1-���óɹ���2-����ı䣬0xFF-δ֪����
**************************************************************/
UCHAR8 MonHXSetPara(UCHAR8 cmd, UCHAR8 * data , UINT16 body_len, UCHAR8 up_down, UCHAR8 ab_flag)
{
	UCHAR8 set_result = 0xff;
	
	BackupSystemPara(para_bak);	// ���ݲ���
	
	if ( cmd==HXCT_CMD_SET_DDF )
	{
		set_result = MonHXSetExtraPara( data[0], data+1, body_len-1, up_down, ab_flag );
	}
	else 
	{
		set_result = MonHXSetNormalPara( cmd, data, body_len, up_down, ab_flag );
	}

	if ( 0 == set_result )	// �������󣬻ָ�ԭֵ
	{
		RestoreSystemPara(para_bak);
	}

	return set_result;

}

/*************************************************************
Name:UartReceHandleHXSetAdd          
Description:����Э�����õ�ַ
Input:����ָ�룬���ݳ���    
Output:void         
Return:1:�ɹ���0:ʧ��        
**************************************************************/
CHAR8 UartReceHandleHXSetAdd(UCHAR8 *data,UINT16 data_len)
{
	UCHAR8 cur_addr;	// ��ǰ��ַ
	UCHAR8 new_addr;
	UCHAR8 ab_flag = 0xff;
	UINT16 crc16,i;
	UCHAR8 save_flag = 0;

	new_addr = data[1]&0x07;
	cur_addr = uart_rece_info.rx_buffer[1]&0x07;

	//������
	if ( (0==(uart_rece_info.rx_buffer[1]&0x08)) )	// DL
	{
		if ( (0x0F&sys_param_1b[MADD_A_PRI_ADD].val) == cur_addr )	// ����A�����е�ַ
		{
			if ( (0x0F&sys_param_1b[MADD_B_PRI_ADD].val)!=new_addr )
			{
				sys_param_1b[MADD_A_PRI_ADD].val = new_addr|(sys_param_1b[MADD_A_PRI_ADD].val&0x70);
				save_flag = 1;
			}
		}
		else if ( (0x0F&sys_param_1b[MADD_B_PRI_ADD].val) == cur_addr )	// ����B�����е�ַ
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
		if ( ((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4) == cur_addr )	// ����A�����е�ַ
		{
			if ( ((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4) != new_addr )
			{
				sys_param_1b[MADD_A_PRI_ADD].val = (new_addr<<4)|(0x07&sys_param_1b[MADD_A_PRI_ADD].val);
				save_flag = 1;
			}
		}
		else if ( ((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4) == cur_addr )	// ����B�����е�ַ
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
		//���õ�ַ
//		sys_param_1b[MADD_A_PRI_ADD].val = data[1]&0x07;	// �Բ�����A�ε�ַΪģ���ַ
//		sys_param_1b[MADD_B_PRI_ADD].val = sys_param_1b[MADD_A_PRI_ADD].val + 1;
		//�����ͷ
		UartPacketHXTransHead(uart_rece_info.rx_buffer[0],(uart_rece_info.rx_buffer[1]&0xf8)|(data[1]&0x07),
			uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);
//		save_flag = 1;
	}
	else
	{
		//���󣬲������ù���ģ�飬�����ͷ
		UartPacketHXTransHead(uart_rece_info.rx_buffer[0],(uart_rece_info.rx_buffer[1]&0xf8)|(data[1]&0x07),
			uart_rece_info.rx_buffer[2],HXCT_ACK_SET_ERROR,data_len);
	}

	//COPY ����
	for (i=0; i<data_len; i++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];	
	
	//����CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//������־
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;

	UartStartTrans();
	
	if ( save_flag != 0 )
	{
		SaveSysParamToFlash();	// �������
	}
	return 1;	
	
}

/*************************************************************
Name:UartReceHandleHXCmdError          
Description:����Э�����֧��
Input:����ָ�룬���ݳ���    
Output:void         
Return:1:�ɹ���0:ʧ��        
**************************************************************/
CHAR8 UartReceHandleHXCmdError(UCHAR8 *data,UINT16 data_len)
{

	UINT16 crc16,i;

	//�����ͷ
	UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
		uart_rece_info.rx_buffer[2],HXCT_ACK_CMD_ERROR,data_len);	

	//COPY ����
	for (i=0; i<data_len; i++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];	
	
	//����CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//������־
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;

	UartStartTrans();
	
	return 1;	

}

/*************************************************************
Name:UartReceHandleHXReset          
Description:����Э�鸴λ
Input:����ָ�룬���ݳ���    
Output:void         
Return:1:�ɹ���0:ʧ��        
**************************************************************/
CHAR8 UartReceHandleHXReset(UCHAR8 *data,UINT16 data_len)
{
	UINT16 crc16,i;
	UCHAR8 reset_flag = 0;

	if ((data_len>0)&&( data[0]==1))
	{
		reset_flag = 1;
	}

	//�����ͷ
	UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
		uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);	

	//COPY ����
	for (i=0; i<data_len; i++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];	
	
	//����CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//������־
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;

	UartStartTrans();

	if ( reset_flag != 0 )
	{
		//�ȴ���������ٸ�λ
		while (uart_trans_info.tx_count!=uart_trans_info.tx_len+1);
		UsNopDelay(10000);

		sys_work_info |= SYSTEM_FLAG_SOFT_RESET;
	}
			
	return 1;	
	
}
/*************************************************************
Name:UartReceHandleHXGet          
Description:����Э���ȡ����
Input:����ָ�룬���ݳ���    
Output:void         
Return:1:�ɹ���0:ʧ��        
**************************************************************/
CHAR8 UartReceHandleHXGet(UCHAR8 *data,UINT16 data_len)
{
	UINT16 crc16;
	UCHAR8 up_down, ab_flag;
	
	//�����б�־
	if ( (0==(uart_rece_info.rx_buffer[1]&0x08)) )	// DL
	{
		up_down = 1;
		// AB�α�־��A-0��B-1
		if ( (0x0F&sys_param_1b[MADD_A_PRI_ADD].val) == (uart_rece_info.rx_buffer[1]&0x07) )	// A�����е�ַ
		{
			ab_flag = 0;
		}
		else if ( (0x0F&sys_param_1b[MADD_B_PRI_ADD].val) == (uart_rece_info.rx_buffer[1]&0x07) )	// B�����е�ַ
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
		// AB�α�־��A-0��B-1
		if ( ((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// A�����е�ַ
		{
			ab_flag = 0;
		}
		else if ( ((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B�����е�ַ
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
	//��ȡ��ز���
	uart_trans_info.tx_len += MonHXGetStatusPara(uart_trans_info.tx_buffer+5,up_down, ab_flag);		
	//���Ԫ�����б仯
	uart_trans_info.tx_buffer[3] = HXCT_ACK_OK|(((uart_trans_info.tx_len-5)>>4)&0x00f0);
	uart_trans_info.tx_buffer[4] = (UCHAR8)(uart_trans_info.tx_len-5);	

	//����CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//������־
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;
	//����Ӧ��
	UartStartTrans();	

	return 1;
		
}

/*************************************************************
Name:UartReceHandleHXSetAtt          
Description:����Э�����ò���
Input:����ָ�룬���ݳ���    ��������
Output:void         
Return:1:�ɹ���0:ʧ��        
**************************************************************/
CHAR8 UartReceHandleHXSet(UCHAR8 *data,UINT16 data_len,UCHAR8 cmd)
{
	UINT16 crc16,i;
	UCHAR8 up_down, ab_flag;
	UCHAR8 save_flag= 0;
	UCHAR8 set_flag = 1;
	
	//�����б�־
	if ( (0==(uart_rece_info.rx_buffer[1]&0x08)) )	// DL
	{
		up_down = 1;
		// AB�α�־��A-0��B-1
		if ( (0x0F&sys_param_1b[MADD_A_PRI_ADD].val) == (uart_rece_info.rx_buffer[1]&0x07) )	// A�����е�ַ
		{
			ab_flag = 0;
		}
		else if ( (0x0F&sys_param_1b[MADD_B_PRI_ADD].val) == (uart_rece_info.rx_buffer[1]&0x07) )	// B�����е�ַ
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
		// AB�α�־��A-0��B-1
		if ( ((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// A�����е�ַ
		{
			ab_flag = 0;
		}
		else if ( ((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B�����е�ַ
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
	case 0:		// ���ô���
		save_flag = 0;
		UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
			uart_rece_info.rx_buffer[2],HXCT_ACK_SET_ERROR,data_len);	
	break;

	case 1:		// ���óɹ���д��Flash
		save_flag = 1;
		
	case 2:		// ���óɹ�������Ҫ����
		UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
			uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);
	break;

	default:		// δ֪����
		if ( cmd==HXCT_CMD_SET_DDF )
		{
			if (data[0] == HXCT_SUBCMD_GET_SETTING)		//��25	��չ���ò�ѯ��Ĳ�ѯ����
			{
				//�����ͷ
				UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
					uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);		
				//���������
				uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[0];
				//��ȡ��ز���
				uart_trans_info.tx_len += MonHXGetSubPara(uart_trans_info.tx_buffer+6,up_down, ab_flag);		

				//���Ԫ�����б仯
				uart_trans_info.tx_buffer[3] = HXCT_ACK_OK|(((uart_trans_info.tx_len-5)>>4)&0x00f0);
				uart_trans_info.tx_buffer[4] = (UCHAR8)(uart_trans_info.tx_len-5);

				set_flag = 0;
				break;
			}
			else if (data[0] == HXCT_SUBCMD_GET_BASE)		//��25	��չ���ò�ѯ��Ĳ�ѯ����
			{	
				UartPacketHXTransHead(uart_rece_info.rx_buffer[0],uart_rece_info.rx_buffer[1],
					uart_rece_info.rx_buffer[2],HXCT_ACK_OK,data_len);		
				//���������
				uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[0];
				//��ȡ��ز���
				//�����������к�
				for (i=0; i<20;i++)
					uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = str_pri_gl_seq[i];
				//MCU��������
				for (i=0; i<20;i++)
					uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = str_pri_mcu_date[i];		
				//FPGA��������
				for (i=0; i<64;i++)
					uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = str_pri_fpga_date[i];		

				//���Ԫ�����б仯
				uart_trans_info.tx_buffer[3] = HXCT_ACK_OK|(((uart_trans_info.tx_len-5)>>4)&0x00f0);
				uart_trans_info.tx_buffer[4] = (UCHAR8)(uart_trans_info.tx_len-5);

				set_flag = 0;
				break;
			}
		}
		UartReceHandleHXCmdError(data,data_len);
		return 0;
	}

	if ( set_flag== 1 )	// �������Ӧ��ʱֱ�ӷ���ԭ����������
	{
		//COPY ����
		for (i=0; i<data_len; i++)
			uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = data[i];	
	}
		
	//����CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//������־
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;
	//����Ӧ��
	UartStartTrans();

	//����յ��˹���ģʽ�����ģʽ����
	if(1==save_flag)
	{
		SaveSysParamToFlash();	// �������
	}
	return 1;	
	
}

/*************************************************************
Name:UartReceHXModuleDET          
Description:����Э��DETģ�鴦��
Input: [p_dat:������ָ��] [data_len:�����������ͷ�������ݳ���]           
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
	UCHAR8 * p_body = uart_trans_info.tx_buffer+5+data_len;	// ָ��ָ����������ʼλ��
	UCHAR8 ack = HXCT_ACK_OK;
	UCHAR8 save_flag = 0;
	
	//�����б�־,0-UL, 1-DL
	if ( 0==(uart_rece_info.rx_buffer[1]&0x08) )	// DL
	{
		up_down = 1;
		// AB�α�־��A-0��B-1
		if ( (sys_param_1b[MADD_HX_DET_DADDR].val&0x0F) == (uart_rece_info.rx_buffer[1]&0x07) )	// A��
		{
			ab_flag = 0;
		}
		else if ( (sys_param_1b[MADD_HX_DET_DADDR].val>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B��
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
		// AB�α�־��A-0��B-1
		if ( (sys_param_1b[MADD_HX_DET_UADDR].val&0x0F) == (uart_rece_info.rx_buffer[1]&0x07) )	// A��
		{
			ab_flag = 0;
		}
		else if ( (sys_param_1b[MADD_HX_DET_UADDR].val>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B��
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}
	
	if ( HXCT_CMD_SET_ADD==uart_rece_info.rx_buffer[2] )	// ����ģ���ַ
	{
		tmp = p_dat[1]&0x07;		// �µ�ַ

		if ( 1==up_down )		// DL
		{
			if ( 0==ab_flag )	// A��
			{
				if ( (sys_param_1b[MADD_HX_DET_DADDR].val>>4) != tmp )	// �µ�ַ������B�ε�ַ
				{
					sys_param_1b[MADD_HX_DET_DADDR].val = (sys_param_1b[MADD_HX_DET_DADDR].val & 0xF0)|tmp;	// �����µ�ַ
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// ����Ӧ���ַ
					save_flag = 1;
				}
			}
			else if ( 1==ab_flag )	// B��
			{
				if ( (sys_param_1b[MADD_HX_DET_DADDR].val & 0x0F) != tmp )	// �µ�ַ������A�ε�ַ
				{
					sys_param_1b[MADD_HX_DET_DADDR].val = (sys_param_1b[MADD_HX_DET_DADDR].val & 0x0F)|(tmp<<4);	// �����µ�ַ
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// ����Ӧ���ַ
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
			if ( 0==ab_flag )	// A��
			{
				if ( (sys_param_1b[MADD_HX_DET_UADDR].val>>4) != tmp )	// �µ�ַ������B�ε�ַ
				{
					sys_param_1b[MADD_HX_DET_UADDR].val = (sys_param_1b[MADD_HX_DET_UADDR].val & 0xF0)|tmp;	// �����µ�ַ
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// ����Ӧ���ַ
					save_flag = 1;
				}
			}
			else if ( 1==ab_flag )	// B��
			{
				if ( (sys_param_1b[MADD_HX_DET_UADDR].val & 0x0F) != tmp )	// �µ�ַ������A�ε�ַ
				{
					sys_param_1b[MADD_HX_DET_UADDR].val = (sys_param_1b[MADD_HX_DET_UADDR].val & 0x0F)|(tmp<<4);	// �����µ�ַ
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// ����Ӧ���ַ
					save_flag = 1;
				}
			}
			else
			{
				ack = HXCT_ACK_SET_ERROR;
			}
		}
	}
	else if ( (0==up_down) && ( ab_flag<2 ) )	// ������������,ֻ��Ӧ���е�ַ������
	{
		if ( HXCT_CMD_GET_STA==uart_rece_info.rx_buffer[2] )	// ģ��״̬��ѯ����
		{
			p_body[0] = 0;
			p_body[1] = 0;	// �޵���ţ�����Ϊ0
			p_body[2] = 0;	// �޵���ţ�����Ϊ0
			p_body[3] = 0;	// �޵���ţ�����Ϊ0
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
	//COPY ����
	for (tmp=0; tmp<data_len; tmp++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = p_dat[tmp];	

	uart_trans_info.tx_len += body_len;
	
	//����CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//������־
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;
	//����Ӧ��
	UartStartTrans();	

	if ( 0!= save_flag )
	{
		SaveSysParamToFlash();	// �������
	}
}

/*************************************************************
Name:UartReceHXModuleDET          
Description:����Э��LNAģ�鴦��,������Ӧ��Ӧ����LNA ģ������
Input:[p_dat:������ָ��] [data_len:�����������ͷ�������ݳ���]           
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
	UCHAR8 * p_body = uart_trans_info.tx_buffer+5+data_len;	// ָ��ָ����������ʼλ��
	UCHAR8 ack = HXCT_ACK_OK;
	UCHAR8 save_flag = 0;

	//�����б�־,0-UL, 1-DL
	if ( 0==(uart_rece_info.rx_buffer[1]&0x08) )	// DL
	{
		return;	// ����Ӧ����LNA ģ������
	#if 0
		up_down = 1;
		// AB�α�־��A-0��B-1
		if ( (sys_param_1b[MADD_HX_LNA_DADDR].val&0x0F) == (uart_rece_info.rx_buffer[1]&0x07) )	// A��
		{
			ab_flag = 0;
		}
		else if ( (sys_param_1b[MADD_HX_LNA_DADDR].val>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B��
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
		// AB�α�־��A-0��B-1
		if ( (sys_param_1b[MADD_HX_LNA_UADDR].val&0x07) == (uart_rece_info.rx_buffer[1]&0x07) )	// A��
		{
			ab_flag = 0;
		}
		else if ( (sys_param_1b[MADD_HX_LNA_UADDR].val>>4) == (uart_rece_info.rx_buffer[1]&0x07) )	// B��
		{
			ab_flag = 1;
		}
		else
		{
			return;
		}
	}
	
	if ( HXCT_CMD_SET_ADD==uart_rece_info.rx_buffer[2] )	// ����ģ���ַ
	{
		tmp = p_dat[1]&0x07;	// �µ�ַ

		if ( 1==up_down )		// DL
		{
			if ( 0==ab_flag )	// A��
			{
				if ( (sys_param_1b[MADD_HX_LNA_DADDR].val>>4) != tmp )	// �µ�ַ������B�ε�ַ
				{
					sys_param_1b[MADD_HX_LNA_DADDR].val = (sys_param_1b[MADD_HX_LNA_DADDR].val & 0x70)|tmp;	// �����µ�ַ
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// ����Ӧ���ַ
					save_flag = 1;
				}
			}
			else if ( 1==ab_flag )	// B��
			{
				if ( (sys_param_1b[MADD_HX_LNA_DADDR].val & 0x0F) != tmp )	// �µ�ַ������A�ε�ַ
				{
					sys_param_1b[MADD_HX_LNA_DADDR].val = (sys_param_1b[MADD_HX_LNA_DADDR].val & 0x07)|(tmp<<4);	// �����µ�ַ
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// ����Ӧ���ַ
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
			if ( 0==ab_flag )	// A��
			{
				if ( (sys_param_1b[MADD_HX_LNA_UADDR].val>>4) != tmp )	// �µ�ַ������B�ε�ַ
				{
					sys_param_1b[MADD_HX_LNA_UADDR].val = (sys_param_1b[MADD_HX_LNA_UADDR].val & 0x70)|tmp;	// �����µ�ַ
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// ����Ӧ���ַ
					save_flag = 1;
				}
			}
			else if ( 1==ab_flag )	// B��
			{
				if ( (sys_param_1b[MADD_HX_LNA_UADDR].val & 0x0F) != tmp )	// �µ�ַ������A�ε�ַ
				{
					sys_param_1b[MADD_HX_LNA_UADDR].val = (sys_param_1b[MADD_HX_LNA_UADDR].val & 0x07)|(tmp<<4);	// �����µ�ַ
					uart_rece_info.rx_buffer[1] = (uart_rece_info.rx_buffer[1] & 0xf8)|tmp;								// ����Ӧ���ַ
					save_flag = 1;
				}
			}
			else
			{
				ack = HXCT_ACK_SET_ERROR;
			}
		}

	}
	else if ( (0==up_down) && ( ab_flag<2 ) )	// ������������,ֻ��Ӧ���е�ַ������
	{
		if ( HXCT_CMD_GET_STA==uart_rece_info.rx_buffer[2] )	// ģ��״̬��ѯ����
		{
			p_body[0] = 0;	// REC��LNA
			p_body[1] = 0;	// ��֧��ATTֵ��ѯ������0
			p_body[2] = 0;	// ��֧��LNA�������ֵ��ѯ������0
			p_body[3] = 0;	// ��֧��LNA��ALC��ֵ��ѯ������0
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
	//COPY ����
	for (tmp=0; tmp<data_len; tmp++)
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = p_dat[tmp];	

	uart_trans_info.tx_len += body_len;
	
	//����CRC
	crc16 = CalCrc16(uart_trans_info.tx_buffer,uart_trans_info.tx_len, HXCT_CRC_SEED);
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)crc16;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(crc16>>8);

	//������־
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = 0x7F;
	//����Ӧ��
	UartStartTrans();	

	if ( 0!= save_flag )
	{
		SaveSysParamToFlash();	// �������
	}

}
#if 0
/*************************************************************
Name:UartReceHandle          
Description:�������ݰ�����
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartReceHandle(void)
{
	UINT16 crc_val;
	//�ж�Ӧ���־
	if ((uart_rece_info.rx_buffer[3]&0x0f) != 0x00)
		return;
	
	//�ж�CRC
	crc_val = CalCrc16(uart_rece_info.rx_buffer,uart_rece_info.rx_len+5,HXCT_CRC_SEED);
	if (crc_val != (uart_rece_info.rx_buffer[uart_rece_info.rx_len+5]|(uart_rece_info.rx_buffer[uart_rece_info.rx_len+6]<<8)))
	{
		return;		//crc����		
	}

	if ( HXCT_DET_MODULE_NUM==uart_rece_info.rx_buffer[0] )	// DETģ�鴦��
	{
		UartReceHXModuleDET( uart_rece_info.rx_buffer+5 , uart_rece_info.rx_len );
		return;
	}
	else if ( HXCT_LNA_MODULE_NUM==uart_rece_info.rx_buffer[0] )	// LNAģ�鴦��
	{
		UartReceHXModuleLNA( uart_rece_info.rx_buffer+5 , uart_rece_info.rx_len );
		return;
	}
	else if ( HXCT_DDF_MODULE_NUM !=uart_rece_info.rx_buffer[0] )	// ����Ƶģ���򲻴���
	{
		return;
	}

	//�жϵ�ַ
	if ((uart_rece_info.rx_buffer[2]!=HXCT_CMD_SET_ADD) 
		&& ((uart_rece_info.rx_buffer[1]&0x07)!=(0x0F&sys_param_1b[MADD_A_PRI_ADD].val))
		&& ((uart_rece_info.rx_buffer[1]&0x07)!=((0xF0&sys_param_1b[MADD_A_PRI_ADD].val)>>4))
		&& ((uart_rece_info.rx_buffer[1]&0x07)!=(0x0F&sys_param_1b[MADD_B_PRI_ADD].val))
		&& ((uart_rece_info.rx_buffer[1]&0x07)!=((0xF0&sys_param_1b[MADD_B_PRI_ADD].val)>>4)) )
	{
		//�����õ�ַ������ҵ�ַ������򲻴������ݰ�
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
Description:�жϵ��ý��մ������
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
		// ��һ�ʰ���û������
		return;
	}

	//��ؽӿ�
	if (uart_rece_info.rx_count==0 && uart_rece_info.rx_data!=0x4E)
	{
		//trans_4e_flag = 0;
		return;			//�ȴ���ʼ��־
	}
	
	if (uart_rece_info.rx_count!=0 && uart_rece_info.rx_data==0x4E)
	{
		if ( uart_rece_info.rx_count>=10 )
		{
			//�յ�������־
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
			//����
			uart_rece_info.rx_count = 0;
		}
	}

	if ( trans_4e_flag == 0 )
	{
		if (uart_rece_info.rx_data==0x4D && uart_rece_info.rx_buffer[uart_rece_info.rx_count-1]==0x5E) 
		{
			//ת��
			uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = 0x4E;
			trans_4e_flag = 1;		//��4Eת���־
			return;
		}
		
		if (uart_rece_info.rx_data==0x5D&& uart_rece_info.rx_buffer[uart_rece_info.rx_count-1]==0x5E) 
		{
			//ת��
			uart_rece_info.rx_buffer[uart_rece_info.rx_count-1] = 0x5E;
			trans_4e_flag = 1;
			return;
		}
	}
	
	uart_rece_info.rx_buffer[uart_rece_info.rx_count] = uart_rece_info.rx_data;
	uart_rece_info.rx_count++;

	if ( uart_rece_info.rx_count>=UART_BUFF_SIZE ) 
	{
		// ���ݹ���,�ж�Ϊ��Ч���ݰ�
		uart_rece_info.rx_count = 0;
	}
	
	trans_4e_flag = 0;

}

/*************************************************************
Name:UartTransInterrupt          
Description:�жϵ��÷��ʹ�����
Input:void            
Output:void         
Return:void         
**************************************************************/
void UartTransInterrupt(void)
{
	//�жϷ���ʱ��һ�������Ѿ����ͳ�ȥ��
	//uart_trans_info.tx_lenΪ������ǰ��0X4E�����ݳ���

	if (uart_trans_info.tx_count == uart_trans_info.tx_len)			// ������־
	{	
		CtrlUartSendDat(0x4E);
		uart_trans_info.tx_count++;
	}
	else if (uart_trans_info.tx_count == uart_trans_info.tx_len+1)	// �෢��һ���ַ�
	{	
		CtrlUartSendDat(0xFF);
		uart_trans_info.tx_count++;
	}
	else if(uart_trans_info.tx_count == uart_trans_info.tx_len+2)		// �������
	{
		//��ʱ��485����ʹ�ܹر�			
		EnableUartTx(0,0);	
		return;
	}
	else
	{
		if (uart_trans_info.tx_buffer[uart_trans_info.tx_count] == 0x4E)
		{
			//ת��
			CtrlUartSendDat(0x5E);
			uart_trans_info.tx_buffer[uart_trans_info.tx_count] = 0x4D;
			return;
		}
		if (uart_trans_info.tx_buffer[uart_trans_info.tx_count] == 0x5E)
		{
			//ת��
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
Description:��ʼ����
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
Description:�����ͷ
Input:ģ���ַ�������֣�Ӧ���־            
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
Description:�������ݰ�����
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
//		printf("uart_rece_info.rx_len_to_short:%02X\r\n", uart_rece_info.rx_len);	//����������

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
		//ģ���ַ��Ϊ�㲥��ַ���߱�����ַ�򲻴���
		TRACE_ERROR("485A Mo Addr Err:%02X\r\n", uart_rece_info.rx_buffer[4]);
		return ;
	}
	
	//�յ����ݺ���ʱ20MS�ٴ���
	UsNopDelay(25*1000);	
	WTD_CLR;
	//printf("485_ID_1:%02X\r\n", uart_rece_info.rx_buffer[5]);	//����������
	
	//У��CRC
	crc16 = CalCrc16(uart_rece_info.rx_buffer+1,uart_rece_info.rx_len-4,0x0000);
	if (crc16 != (UINT16)(uart_rece_info.rx_buffer[uart_rece_info.rx_len-3]|(uart_rece_info.rx_buffer[uart_rece_info.rx_len-2]<<8)))
	{
		//crc����
		UartReceHandleMoError(MONITOR_ERROR_CRC);			
		return;
	}
	
	//printf("485_ID_2:%02X\r\n", uart_rece_info.rx_buffer[6]);	
	
	if (uart_rece_info.rx_buffer[6] != 0xFF)
	{
		//���������ı�־��
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
				// �д��󣬸�λREԶ�̷���ָ�����ز���
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
			//���֧��
			UartReceHandleMoError(MONITOR_ERROR_COM);		
		break;			
	}
	WTD_CLR;
}



/*************************************************************
Name:UartReceHandleMonGetAllPara         
Description:��������еĻ�ȡ���в�����Ϣ
Input:����ָ�룬���ݳ���            
Output:void         
Return:1:�ɹ���0:ʧ��        
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
Description:��������еĻ�ȡ����
Input:����ָ�룬���ݳ���            
Output:void         
Return:1:�ɹ���0:ʧ��   
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


//	if ( 0x00 == p_args[0] )		// ��ѯ����:��ǰ����
//	{
//		TRACE_INFO("[M]Msg Handle Get Topo  2\r\n"); 
		for ( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			// ���״̬
			tmp = 0;
			
			if ( COMMA_LOCK==fp_inf[fp_no].comma_lock )	// ��������
			{
                  tmp |= (0x01<<7);
			}
			
			if ( FRAME_LOCK==fp_inf[fp_no].frm_lock )	// ����֡����
			{
				 tmp |= (0x01<<6);
			}

			if ( 0 != ( OPS_RCV_FLAG & fp_inf[fp_no].ops_info ) )	// �յ��Զ˹�����ݣ�����
			{
				tmp |= (0x01<<4);		// ����
				tmp |= ( fp_inf[fp_no].ops_info & OPS_NO_MASK );		// �Զ˹�ں�
			}

			uart_trans_info.tx_buffer[msg_tx_len++] = tmp;  //bit7~����������bit6~֡������bit4~������־��bit3~bit0 �Զ˹�ں� 
			uart_trans_info.tx_buffer[msg_tx_len++] = fp_inf[fp_no].re_cnt; //��ǰ��ڵ�RE���� 
//			p_tx_buff[msg_tx_len++] = fp_inf[fp_no].ree_cnt; //��ǰ��ڵ�REe����  
//				TRACE_INFO("\r\n"); 
//				TRACE_INFO("fp_inf[fp_no].re_cnt(%0x)\r\n",fp_inf[fp_no].re_cnt); 	

			
			for ( re_no=0; re_no< fp_inf[fp_no].re_cnt; re_no++ )  
			{
				uart_trans_info.tx_buffer[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].re_status; //�����˹��0��1������״̬���ϡ����й�ڵ��ж�
//				uart_trans_info.tx_buffer[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].re_id;     //���ID 
				
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_count;           //��ǰ��ڵ�ǰ�ڵ��REe���� 
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_sync_st_inf[0];     // 4������RF�Ĺ��״̬��8������RF������״̬
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_sync_st_inf[1];     // 	
				uart_trans_info.tx_buffer[msg_tx_len++] = tmp_re_inf[fp_no][re_no].ree_nt_stat;     // 4������RF�Ĺ��״̬��8������RF������״̬
				uart_trans_info.tx_buffer[msg_tx_len++] =tmp_re_inf[fp_no][re_no].ree_fp_stat;     // 
				uart_trans_info.tx_buffer[msg_tx_len++] =(0xff00&tmp_re_inf[fp_no][re_no].ree_work_status)>>8;     // 4������RF�Ĺ��״̬��8������RF������״̬
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
Description:��������еĻ�ȡ����
Input:����ָ�룬���ݳ���            
Output:void         
Return:1:�ɹ���0:ʧ��   
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
Description:��������е����ò���
Input:����ָ�룬���ݳ���            
Output:void         
Return:1:�ɹ���0:ʧ��      
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

	// ���ò���
	if ( 0 != SetSysParam( data_len, ex_flag, data, &err_add ) )
	{
		// �������
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
	

	//��������п��ܸı����豸��ַ
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
Description: Զ�̲�ѯ����RE����
Input:����ָ�룬���ݳ���            
Output:void         
Return:1:�ɹ���0:ʧ��      
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
	// �������ݰ���ͷ��Ϣ����REӦ���ʱ������485���ݰ�
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
//	if ( uart_rece_info.rx_buffer[4] == sys_param_1b[MADD_A_PRI_ADD].val )	// A�ε�ַ
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
//		if ( 0xC1==re_trans_cmd )		// ���ò���
//		{
//			re_trans_cmd = MSG_CMD_SET_PARAM;
//		}
//		else if ( 0xC2==re_trans_cmd )	// ��ѯ����
//		{
//			re_trans_cmd = MSG_CMD_GET_PARAM;
//		}
//		else
//		{
//			return 0;
//		}
		TRACE_INFO("data_len:[%02X],i:[%02X]------------\r\n", data_len,i);
		if ( (i+3)>=data_len )		// ���ݲ���������һ����������2�ֽڵ�ַ��1�ֽڳ��ȣ�������ݰ���Ӧ�����ٻ�ʣ��4���ֽڵ�����
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

		p_msg[tx_len++] = re_trans_cmd;	// ������
		p_msg[tx_len++] = uart_rece_info.rx_buffer[4];//1;	// AB�α�־: A
		TRACE_INFO("ABCD_FLAG:[%02X]------------\r\n", uart_rece_info.rx_buffer[4]);
		for ( i; i<data_len; i++ )
		{
			p_msg[tx_len++] = data[i];	// AB�α�־: A
//			TRACE_INFO("p_msg:[%02X]------------\r\n", data[i]);

		}

#if 0		
		while ( (i+3)<data_len )
		{
			// 485�ӿڵ�ַ
			param_add = data[i]|( (UINT16)data[i+1]<<8);
			i+=2;
			// ��������
			param_len = data[i++];
			// 485�ӿڵ�ַת��Ϊģ���±��ַ
			if ( b_FALSE==ParamAddTranslate( param_len, param_add, PT_AP, &param_add ) )	
			{
				return 0;
			}
			// �±��ַ
			p_msg[tx_len++] = (UCHAR8)(param_add&0x00FF);	
			p_msg[tx_len++] = (UCHAR8)((param_add>>8)&0x00FF);
			// ����
			p_msg[tx_len++] = param_len;
			// ����
			while ( param_len-- )
			{
				p_msg[tx_len++] = data[i++];	
			}
		}
#endif
		p_msg[tx_len] = 0;
		p_msg[tx_len+1] = 0;
		// �������ݰ���RE

		
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
Description:��ش�����
Input:��������            
Output:void         
Return:void         
**************************************************************/
void UartReceHandleMoError(UCHAR8 error_type)
{
	UINT16 crc16,i;

	TRACE_ERROR("485A Error:%02X", error_type);

	UartPacketTransHead(uart_rece_info.rx_buffer[1],uart_rece_info.rx_buffer[2],uart_rece_info.rx_buffer[3],
						uart_rece_info.rx_buffer[4],uart_rece_info.rx_buffer[5],error_type);
	
	//�ӽ��յİ��н�����COPY�����ͻ���
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
Description: �����յ���Զ�̷���REָ���Ӧ��
Input:����ָ�룬���ݳ���            
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
	
	if ( (i+3)>=data_len )		// ����Ч�������ݣ�һ����Ч������������ռ��4�ֽڳ���
	{
		return;
	}

	switch( result )	// ����ִ�н��
	{
	case MSG_ACK_CMD_OK:
		tmp = MONITOR_SUCCESS;
		break;

	case MSG_ACK_ERR_CRC:
		tmp = MONITOR_ERROR_CRC;
		break;
		
	case MSG_ACK_ERR_ADDR:
	case MSG_ACK_ERR_VALUE:
		if ( re_trans_cmd==0xC1 )		// ���ò���
		{
			tmp = MONITOR_ERROR_SET;
			break;
		}
		else if ( re_trans_cmd==0xC2 )		// ��ѯ����
		{
			tmp = MONITOR_ERROR_GET;
			break;
		}
		
	default:
		tmp = MONITOR_ERROR_OTHER;

	}

	// �������ݰ�ͷ
	UartPacketTransHead( re_trans_head_bk[0], re_trans_head_bk[1], re_trans_head_bk[2],
						re_trans_head_bk[3], MONITOR_CMD_RE_TRANS, tmp );
	// �������ּ�REλ����Ϣ
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = re_trans_cmd;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = re_trans_fp;
	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = re_trans_node;
//	uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = re_trans_rf;
	// ��λREԶ�̷���������������
	re_trans_cmd = 0;
	re_trans_fp = 0;
	re_trans_node = 0;
	re_trans_rf = 0;
	// ��������
	while ( data_len-- )
	{
		uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = *data++;
	}
#if 0
	while ( (i+3)<data_len )
	{
		// �±��ַ
		param_add = data[i]|( (UINT16)data[i+1]<<8);
		i+=2;
		// ��������
		param_len = data[i++];
		// �±��ַת����485��ַ
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
		else if ( param_add<SYS_PARAM_ASC_COUNT )	// �ַ�������
		{
			if ( param_len < sys_param_asc[param_add].length )	// ��鳤��
			{
				param_add = sys_param_asc[param_add].addr;	// ����485��ַ
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

		if ( param_add != 0 )		// ��Ч��485��ַ����Ϊ0
		{
			// ������ַ
			uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(param_add&0xFF);
			uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = (UCHAR8)(param_add>>8);
			// ��������
			uart_trans_info.tx_buffer[uart_trans_info.tx_len++] = param_len;
			// ��������
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
Description:��ʼ����
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
Description:�����ͷ
Input:ģ���ַ�������֣�Ӧ���־            
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
Description:�����ͷ
Input:ģ���ַ�������֣�Ӧ���־            
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
Description:�����շ�����ʼ������
Input:����ָ�룬���ݳ���            
Output:void         
Return:1:�ɹ���0:ʧ��        
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
	current_p = data[4];			//��ǰ����
	total_p = data[5];				//�ܰ���
	cmd_cnt = (data[6]<<8)|data[7];	//���а������������

	PKTlen =( data[4]<<8)|data[5];	//�ܰ���
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


	
	//Ӧ���
//	PcPacketTransHead(0xdf,0x01,0x01,0x01,0xab,0x00);
	* tx_p++ = data[0];		//������� 9363
	TRACE_INFO("9363_TYPE[%02X]\r\n",data[0]);
	tx_p+=2;			//�����ռ�洢���ذ������ݳ���
	* tx_p++ = data[3];	//A,B
	* tx_p++ = data[4];	//��ǰ����
	* tx_p++ = data[5];	//�ܰ���
	* tx_p++ = data[6];	//���а������������
	* tx_p++ = data[7];	//���а������������


	
	data += 8;	
	pc_trans_info.tx_len += 8;//8���ֽ�ͷ:1���ֽڱ������--9363�� 2�ֽڷ��ذ����ݳ��ȣ�1�ֽ�A,B��־��1�ֽڵ�ǰ������1�ֽ��ܰ�����2�ֽڰ��а��������������

	TRACE_DEBUG("from_pc:cmd_cnt[%d]=[%04x],data[0]=[%02x],data[1]=[%02x],data[2]=[%02x]\r\n\r\n",current_p,cmd_cnt,data[0],data[1],data[2]);	
	//ִ������
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
					//�ȴ�MCU��дSPIָʾ�ź���
					if(0x01==(0x01&(FpgaReadRegister(0x7a)>>15))	)
					{
						continue;
					}
					
					TRACE_INFO("( 0x00==(0x01&(FpgaReadRegister(0x7a)>>14))):%x\r\n",(	0x00==(0x01&(FpgaReadRegister(0x7a)>>14))));

					if((k<10000)&&(TF_C==ft_ab)&&(AD9369)&&(	0x00==(0x01&(FpgaReadRegister(0x7a)>>14)))	)
					{
						//�л���FPGA ROM SPIģʽ
						mcuFpgaSpiStaus=FpgaReadRegister(0x8000|0x7b);
						mcuFpgaSpiStaus&=0x3fff;
						mcuFpgaSpiStaus|=(0x02<<14);
						TRACE_INFO("1FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus):%x\r\n",mcuFpgaSpiStaus);
						FPGA_ENABLE_WRITE;
						FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus);
						FPGA_DISABLE_WRITE;
						//FPGA SPI ����ʹ��
						mcuFpgaSpiStaus=FpgaReadRegister(0x8000|0x7b);
						mcuFpgaSpiStaus&=0xdfff;
						mcuFpgaSpiStaus|=(0x1<<13);
						TRACE_INFO("2FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus):%x\r\n",mcuFpgaSpiStaus);
						FPGA_ENABLE_WRITE;
						FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus);
						FPGA_DISABLE_WRITE; 
						//�ȴ�FPGA ROM дSPI �������
						j=0;
						while((j<5000)&&(0x00==(0x01&(FpgaReadRegister(0x7a)>>14))	))
						{
							j++;
							UsNopDelay(1*1000);
							WTD_CLR;
						}
						
						//�ȴ�MCU��дSPIָʾ�ź���
						j=0;
						while((j<5000)&&(0x01==(0x01&(FpgaReadRegister(0x7a)>>15))	))
						{
							j++;
							UsNopDelay(1*1000);
							WTD_CLR;
						}

						//�л���MCUģ���SPI
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
				//��������				
		//		PcPacketTransHead(0xdf,0x01,0x01,0x01,0xab,0x01);
				TRACE_INFO("9363_��������\r\n");
				* tx_p++ = 0;
				pc_trans_info.tx_len++;
		
				goto out;
			break;
		}
	}

	//��������PKTlen
	SaveInitData(ft_ab,current_p,total_p,p_packet_head,data_len-6-MSG_CMD_BODY);//data_len-6-MSG_CMD_BODY Ϊ�ܰ�����֮������� ���Ȳ�����1005-2�ֽ�
	//SaveInitData(ft_ab,PKTlen,total_p,p_packet_head,data_len-6-MSG_CMD_BODY);//data_len-6-MSG_CMD_BODY Ϊ�ܰ�����֮������� ���Ȳ�����1005-2�ֽ
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
	//д��FLASH
	
	return 1;	
	
	
}
//#endif 





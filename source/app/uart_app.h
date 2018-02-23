/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : uart_app.h
* Description : RS485�ӿڲ���
* Version     :v0.1
* Author      :RJ
* Date        :2010-06-11
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*	RJ		2010-06-11	v0.1			��ʼ�汾
**************************************************************/
#ifndef _UART_APP_H
#define _UART_APP_H

#include "ex_conf.h"

#define UART_BUFF_SIZE		(1024+512)//2048
#define THR_FIFO_SIZE		(1024+512)
#define PC_BUFF_SIZE		(1024+512)//2048
#define MO_MSG_BODY_SIZE	70

#define UART_PKT_MIN		9		// �������ݰ���С����

#define DEBUG_UART_BAUD				115200	// ���Դ��ڲ�����

#ifdef USER_CONTROL_BAUD
#define CONTROL_UART_BAUD				USER_CONTROL_BAUD		// �û����ƴ��ڲ�����
#else
#define CONTROL_UART_BAUD				9600	// Ĭ�Ͽ��ƴ��ڲ�����
#endif

#ifdef USER_THR_BAUD
#define THR_UART_BAUD					USER_THR_BAUD	// �û�͸�����ڲ�����
#else
#define THR_UART_BAUD					9600	// Ĭ��͸�����ڲ�����
#endif


typedef struct _S_UART_RECE
{
	UINT16 rx_count;
	UINT16 rx_len;
	UCHAR8 * rx_buffer;
	UCHAR8 rx_data;
} _T_UART_RECE;

typedef struct _SUART_TRANS
{
	UINT16 tx_count;
	UINT16 tx_len;
	UCHAR8 *tx_buffer;
	UCHAR8 tx_data;
} _T_UART_TRANS;

typedef struct _S_THR_FIFO
{
	volatile UINT16 index;
	volatile UINT16 count;
	UCHAR8 p_dat[THR_FIFO_SIZE];
}/* __attribute__((packed))*/ _T_THR_FIFO;

//����Э��
#define HXCT_CRC_SEED				0x0000		// CRC����
#define HXCT_DDF_MODULE_NUM		0x20		//��Ƶģ����
#define HXCT_DET_MODULE_NUM		0x01		// DETģ��
#define HXCT_LNA_MODULE_NUM		0x09		// LNAģ��

#define HXCT_CMD_SET_ADD			0x10
#define HXCT_CMD_GET_STA			0x11
#define HXCT_CMD_SET_ATT			0x20
#define HXCT_CMD_SET_ONOFF		0x22
#define HXCT_CMD_SET_ALC			0x23		// ALC��������
#define HXCT_CMD_SET_NOISE_ON		0x2b
#define HXCT_CMD_SET_NOISE_GATE	0x2c
#define HXCT_CMD_SET_RESET		0x88
#define HXCT_CMD_SET_DDF			0x93		// ���������

//������չ������
#define HXCT_SUBCMD_SET_POWER	0x20		// ����ͨ����������������
#define HXCT_SUBCMD_SET_GAIN		0x21		// ��������ͨ���������
#define HXCT_SUBCMD_SET_FRE_NUM	0x22		// �����ŵ���
#define HXCT_SUBCMD_SET_CH_EN		0x23		// �����ŵ�����
#define HXCT_SUBCMD_SET_OPT_EN	0x24		// ��ģ�鿪��
#define HXCT_SUBCMD_SET_DELAY		0x25		// ������ʱ����ֵ
#define HXCT_SUBCMD_SET_PD_MODE	0x25		// ���õ͹��Ŀ���(1230Э��)
#define HXCT_SUBCMD_SET_PA_GAIN	0x26		// �������й�������(1230Э��)
#define HXCT_SUBCMD_SET_DPX_IA	0x27		// ��������˫����˥��(1230Э��)
#define HXCT_SUBCMD_SET_DPX_OA	0x28		// �������˫����˥��(1230Э��)
#define HXCT_SUBCMD_SET_FPS_BCCH	0x29		// ������Ƶ�ŵ���(1230Э��)
#define HXCT_SUBCMD_SET_FPS_PARA	0x2A		// ������Ӫ�̺�Ƶ��ѡ��(1230Э��)
#define HXCT_SUBCMD_SET_FPS_CID	0x2B		// ��������С��ʶ����ʵʱֵ(1230Э��)
#define HXCT_SUBCMD_SET_DELAY_M	0x2C		// �����Զ���ʱ����(1230Э��)
#define HXCT_SUBCMD_SET_RE_DELAY	0x2D		// ���ù�·��ʱ����(1230Э��)
#define HXCT_SUBCMD_GET_SETTING	0x10
#define HXCT_SUBCMD_GET_BASE		0x11

#define HXCT_ACK_OK					0x00
#define HXCT_ACK_CMD_ERROR		0x02
#define HXCT_ACK_DATA_ERROR		0x03
#define HXCT_ACK_SET_ERROR			0x04


//��ͨЭ��

//�������
#define MONITOR_CMD_GET_PRI			0x40
#define MONITOR_CMD_GET_ALL_PARA		0x50
#define MONITOR_CMD_SET_PRI			0x60
#define MONITOR_CMD_SET_PARA			0xc1
#define MONITOR_CMD_GET_PARA			0xc2
#define MONITOR_CMD_RE_TRANS			0xCE
#define MONITOR_CMD_GET_TOPO			0xCF

//���ر�־
#define MONITOR_SUCCESS			0x00
#define MONITOR_ERROR_COM			0x01
#define MONITOR_ERROR_VER			0x02
#define MONITOR_ERROR_CRC			0x03
#define MONITOR_ERROR_HEAD		0x04
#define MONITOR_ERROR_FLAG		0x06
#define MONITOR_ERROR_SET			0x07
#define MONITOR_ERROR_GET			0x08
#define MONITOR_ERROR_TYPE		0x10
#define MONITOR_ERROR_NOT_HOST	0x11
#define MONITOR_ERROR_OTHER		0xa0

//�㷨
#define MONITOR_SIGNED				0x00
#define MONITOR_UNSIGNED			0x07
#define MONITOR_INT_10				0x08
#define MONITOR_UINT_10			0x09
#define MONITOR_CHAR_10			0x0B
#define MONITOR_UCHAR_10			0x0C
#define MONITOR_NONE				0xFF

#define PARAM_RO			0x00
#define PARAM_RW			0xFF

extern UCHAR8 thr_utx_fifo_use;		// ��ʶ͸�����ڷ���ʹ�õ�FIFO��FPGA����ʹ����һ��FIFO
extern UCHAR8 thr_urx_fifo_use;		// ��ʶ͸�����ڽ���ʹ�õ�FIFO��FPGA����ʹ����һ��FIFO
extern UCHAR8 uart_thr_tx_end;		// ����͸�����ݷ�����ɱ�־
extern UCHAR8 fpga_thr_tx_end;		// FPGA͸�����ݷ�����ɱ�־
extern _T_THR_FIFO uart_thr_tx_fifo[];	// ͸�����ڷ���FPGA����FIFO
extern _T_THR_FIFO uart_thr_rx_fifo[];	// ͸�����ڽ���FPGA����FIFO
extern UCHAR8 uart_test_tx_buff[ ]; 
extern UCHAR8 uart_index; 
extern UCHAR8 uart_flag;


void ResetThrFifo();
void DebugUartInterrupt(void);
void ControlUartInterrupt(void);
void ThrUartIsrRxDat( UCHAR8 thr_dat );
void ThrUartIsrTxReady( void );
void ThrUartIsrTxComplete( void );
void UartTransThrDat();
void UartBTestSend( UCHAR8 dat );
CHAR8 UartReceHandleMoGetAllPara(UCHAR8 *data,UINT16 data_len);
CHAR8 UartReceHandleMoGetPara(UCHAR8 *data,UINT16 data_len);
CHAR8 UartReceHandleMoSetPara(UCHAR8 *data,UINT16 data_len);
CHAR8 UartReceHandleMoTransRe(UCHAR8 *data,UINT16 data_len);
void UartReceHandleMoError(UCHAR8 error_type);
void UartReTransHandleAckMsg(UCHAR8 result, UCHAR8 *data,UINT16 data_len);
CHAR8 UartReceHandleMoGetTopo(UCHAR8 *data,UINT16 data_len);
void UartReceHandleMoError(UCHAR8 error_type);
CHAR8 UartReceHandleSetFtPara(UCHAR8 *data,UINT16 data_len);
//void PcPacketTransHead(UCHAR8 type,UCHAR8 ver,UCHAR8 device,UCHAR8 address,UCHAR8 command,UCHAR8 ack);
void PcPacketTransHead(UCHAR8 *tx_buffer);

#endif

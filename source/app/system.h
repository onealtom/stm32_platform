/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :system.h
* Description :
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			��ʼ�汾
**************************************************************/
#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "ex_conf.h"



// MCU����汾��
#define MCU_SOFT_VER 	0x20

#define ARRY_NUM(ARRAY, TYPE) (sizeof(ARRAY)/sizeof(TYPE)) 	// ������Ԫ�ظ�����ARRAY�����飬TYPE������Ԫ������
#define VAL_IN_RANGE( VALUE, RANGE_MIN, RANGE_MAX )	( ((VALUE)>=(RANGE_MIN)) && ((VALUE)<=(RANGE_MAX)) )
// ����10Ϊ�׵Ķ���
#define LOG_10( VAL )				( log(VAL)/log(10) )

typedef struct _S_ERROR
{
	UINT32 err_type;
	UCHAR8 err_info[64];
} _T_ERROR;

// ������ʽ
#define NET_TYPE_GSM900			0
#define NET_TYPE_WCDMA2100		1
#define NET_TYPE_TD				2
#define NET_TYPE_CDMA			3
#define NET_TYPE_DCS1800		4
#define NET_TYPE_CMMB			5
#define NET_TYPE_TETRA			6
#define NET_RESERVE3			7
#define NET_TYPE_LTE_TD			8
#define NET_TYPE_LTE_FDD		9
#define NET_TYPE_CDMA800		    10
#define NET_DIVE				0xF		// �ּ�
#define NET_NONE				0xEE	// �գ�����ӦӲ��

#define G2_TYPE_UNICOM		0		//�й���ͨ
#define G2_TYPE_CNMOBILE		1	//�й��ƶ�
#define G2_TYPE_TELECOM		2	//�й�����


#define FP_MAX	4			// ֧�ֵ����������
#define RE_MAX	12			// ÿ�����֧�ֵ����RE����
#define REE_MAX	12			// ÿ��RE֧�ֵ����REE����

//#define MAX_CHANNEL_COUNT		32	// ֧�ֵ�ͨ����

#define WLAN_PORT_COUNT		4	// WLAN�˿�����
#define WLAN_PORT_OFFSET		4	// WLAN�˿�ƫ��������WLAN0��Ӧ�Ĺ�ں�

// A��������ʽ
#ifdef USER_NET_TYPE_A
#define A_NETWORK_TYPE		USER_NET_TYPE_A		
#else
#define A_NETWORK_TYPE		NET_TYPE_GSM900	
#endif

// B��������ʽ
#ifdef USER_NET_TYPE_B

#if 	(( USER_NET_TYPE_B==NET_TYPE_DCS1800 ) && defined(FUNC_FREQ_POINT_SEARCH_EN) && defined(FUNC_FPS_AUTO_SET))
#define B_NETWORK_TYPE		NET_DIVE		
#else
#define B_NETWORK_TYPE		USER_NET_TYPE_B		
#endif

#else
#define B_NETWORK_TYPE		NET_TYPE_WCDMA2100	
#endif

// C��������ʽ
#ifdef USER_NET_TYPE_C
#define C_NETWORK_TYPE		USER_NET_TYPE_C		
#else
#define C_NETWORK_TYPE		NET_TYPE_LTE_FDD	
#endif

// D��������ʽ
#ifdef USER_NET_TYPE_D
#define D_NETWORK_TYPE		USER_NET_TYPE_D		
#else
#define D_NETWORK_TYPE		NET_TYPE_LTE_FDD	
#endif

// ��ʽ��飬A��Ϊ��ʱ��������B������Ϊ�ּ�ģʽ
#if (( A_NETWORK_TYPE==NET_NONE )&&( B_NETWORK_TYPE==NET_DIVE ))
#error "A&B NET TYPE ERROR!"
#endif

// ������ͳ��ʱ��(����)
#ifdef USER_TRAFFIC_TIME
#define TRAFFIC_TIME		USER_TRAFFIC_TIME	
#else
#define TRAFFIC_TIME		15
#endif

// ������ʼ��:���ƶ˿ڲ�����
#ifdef USER_INIT_PARAM_CTRL_BAUD
#define PARAM_INIT_CTRL_BAUD			USER_INIT_PARAM_CTRL_BAUD	
#else
#define PARAM_INIT_CTRL_BAUD			0	// 0-9600bps
#endif

// ������ʼ��:͸���˿�ѡ��
#ifdef USER_INIT_PARAM_THR_PORT
#define PARAM_INIT_THR_PORT			USER_INIT_PARAM_THR_PORT	
#else
#define PARAM_INIT_THR_PORT			0	// 0-485B
#endif

// ������ʼ��:͸���˿ڲ�����
#ifdef USER_INIT_PARAM_THR_BAUD
#define PARAM_INIT_THR_BAUD			USER_INIT_PARAM_THR_BAUD	
#else
#define PARAM_INIT_THR_BAUD			0	// 0-9600bps
#endif



// ����ŵ�ѹ��Χ
#define V_LNA_MIN		3.6
#define V_LNA_MAX		4.6
#if 0
//RE��Ϣ�ṹ��
typedef struct _S_RE_INFO
{
	UCHAR8 flag;	// ״̬������Ϣ
	UCHAR8 id;		// RE��ID��
	UINT16 status;	// RE�Ĺ���״̬
	UINT32 re_t12;	// RE��ǰ���Ĺ�����ʱ
} _T_RE_INFO;

//�����Ϣ�ṹ��
typedef struct _S_FP_INFO
{
	UCHAR8 sfp_attach:1;	// ��ģ�����Ӽ��: 1-������
	UCHAR8 comma_lock:1;	// ���˶��ż��: 1-������⵽����,0-�쳣
	UCHAR8 frm_lock:1;		// ����֡����״̬: 1-����, 0-�쳣
	UCHAR8 tx_err:1;		// ĩ�����з���״̬: 1-�Ͽ�
	UCHAR8 rcv_frm_mode;	// ����֡״̬:00---û���յ�֡���ݣ�01---�յ��Է�֡��10---�յ�����֡��11-�յ�����֡
	UCHAR8 re_cnt;			// ��ڵ�ǰ���ӵ�RE��
	UCHAR8 ops_info;		// �Զ˹�ں�,���λΪָʾλ
	struct 
	{
		UCHAR8 id;		// RE��ID��
		UCHAR8 status;	// RE�Ĺ���״̬
	} re_info[RE_MAX];	//RE_MAXÿ�����֧�ֵ�RE��
} _T_FP_INFO;
#endif

//RE��Ϣ�ṹ��
typedef struct _S_RE_INFO
{
	UCHAR8 flag;	    // ״̬������Ϣ 
	UCHAR8 id;		    // RE��ID�� 
	UINT16 status;	    // RE�Ĺ���״̬
	UINT32 re_t12;	    // RE��ǰ���Ĺ�����ʱ
    UCHAR8 ree_fp_stat;  // 4������Ree�Ĺ��״̬
    UCHAR8 ree_nt_stat;  // 8������Ree�����ڿ�״̬ 
    UCHAR8 pre_ree_fp_stat;  // 4������Ree�Ĺ��״̬
    UCHAR8 pre_ree_nt_stat;  // 8������Ree�����ڿ�״̬     
    UINT16  ree_work_status;	    // RE�Ĺ���״̬
	
} _T_RE_INFO;  

//�����Ϣ�ṹ��
typedef struct _S_FP_INFO
{
	UCHAR8 sfp_attach:1;	// ��ģ�����Ӽ��: 1-������
	UCHAR8 comma_lock:1;	// ���˶��ż��: 1-������⵽����,0-�쳣
	UCHAR8 frm_lock:1;		// ����֡����״̬: 1-����, 0-�쳣
	UCHAR8 tx_err:1;		// ĩ�����з���״̬: 1-�Ͽ�
	UCHAR8 rcv_frm_mode;	// ����֡״̬:00---û���յ�֡���ݣ�01---�յ��Է�֡��10---�յ�����֡��11-�յ�����֡
	UCHAR8 re_cnt;			// ��ڵ�ǰ���ӵ�RE��
	UCHAR8 ree_cnt;			// ��ڵ�ǰ���ӵ�REE��
	UCHAR8 ops_info;		// �Զ˹�ں�,���λΪָʾλ
	struct 
	{
		UCHAR8 re_id;		    // RE��ID�� :��չ��Ԫ
		UCHAR8 re_status;	    // RE�Ĺ���״̬
		UCHAR8 ree_sync_st_inf[2];  // 12����Զ�ڹ���״̬ 
		UCHAR8 pre_ree_sync_st_inf[2];  // 12����Զ�ڹ���״̬
		UCHAR8 rf_count;  //Re����Rf������  
		
	} re_info[RE_MAX];	//RE_MAXÿ�����֧�ֵ�RE��
	
} _T_FP_INFO;

typedef struct _S_VALID_FP_TOPO
{
	UCHAR8 fp_mode;
	UCHAR8 re_count;
	struct
	{
		UCHAR8 id;
		UCHAR8 mode;
	} re_inf[RE_MAX];
} _T_VALID_FP_TOPO;


typedef struct _S_TOPO_ALARM_INFO
{
	UCHAR8 mau_alarm;
	UCHAR8 meu_alarm;
	UINT16    ru_alarm;
	//struct
	//{
		//UCHAR8 id;
		//UCHAR8 mode;
	//} ru_inf[REE_MAX];
	
	
}_T_TOPO_ALARM_INFO;

// ��������״̬
#define COMMA_LOCK			1
#define COMMA_UNLOCK		0

// ֡����״̬
#define FRAME_LOCK			1
#define FRAME_UNLOCK		0

// ����֡״̬
#define RFM_NO_FRAME		0	// ������֡
#define RFM_AT_FRAME		1	// �Է�֡
#define RFM_DL_FRAME		2	// ����֡
#define FRM_UL_FRAME		3	// ����֡

// ��ڶԶ˽��ձ�־��������
#define OPS_RCV_FLAG		0x80	// ���յ��Զ˹������
#define OPS_NO_MASK		0x0F	// �Զ˹�ں�
#define OPS_NOT_FOUND		0x00	// û�жԶ˹��


// ϵͳ����״̬
#define SYS_ERR_FPGA_LOAD				2
#define SYS_ERR_PLL_UNLOCK				3

#define SYS_A_FLAG		0	// A��
#define SYS_B_FLAG		1	// B��
#define SYS_C_FLAG		2	// C��
#define SYS_D_FLAG		3	// D��

#define SYS_DL_FLAG		0	// ���б�־
#define SYS_UL_FLAG		1	// ���б�־


// DA��־
#define DA_A_FLAG		0	// A��
#define DA_B_FLAG		1	// B��
#define DA_C_FLAG		3	// C��
#define DA_D_FLAG		4	// D��

// ��Ƶ��ǰ��˱�־
#define MIXER_FRONT		0	// ǰ��
#define MIXER_BACK		1	// ���
#define MIXER_A_FLAG	0	// A��
#define MIXER_B_FLAG	1	// B��

#define FPGA_COMPRESS  


// λ���
#define SET_BIT_FLAG( VALUE, BIT_FLAG )		(VALUE) = (VALUE)|(BIT_FLAG)
#define CLR_BIT_FLAG( VALUE, BIT_FLAG )		(VALUE) = (VALUE)&(~(BIT_FLAG))
#define CHECK_BIT_FLAG( VALUE, BIT_FLAG )	( (VALUE)&(BIT_FLAG) )



// RE��id��Χ
#define ID_DEFAULT	0		// Ĭ�ϵ�IDֵ
#define ID_MAX		254		// ID�����ֵ
#define ID_START	64		// ID�ķ�����ʼֵ������Сֵ��1~63����



// function
#define WTD_CLR				{ClrWtd();}//
#define TURN_ON_LED		{LedOn();}//GP2CLR = GPIO_LED_O<<16;
#define TURN_OFF_LED		{LedOff();}//GP2SET = GPIO_LED_O<<16;
#define FLASH_LED			{LedFlash();}//if (GP2DAT&(GPIO_LED_O<<16)) GP2CLR = GPIO_LED_O<<16;else GP2SET = GPIO_LED_O<<16;
#define RS485_DRIVER		{}//GP1SET = GPIO_485_RE_O<<16;

#endif

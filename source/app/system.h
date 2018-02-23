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
*shiyang		2008-01-29	v0.1			初始版本
**************************************************************/
#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "ex_conf.h"



// MCU软件版本号
#define MCU_SOFT_VER 	0x20

#define ARRY_NUM(ARRAY, TYPE) (sizeof(ARRAY)/sizeof(TYPE)) 	// 求数组元素个数，ARRAY是数组，TYPE是数组元素类型
#define VAL_IN_RANGE( VALUE, RANGE_MIN, RANGE_MAX )	( ((VALUE)>=(RANGE_MIN)) && ((VALUE)<=(RANGE_MAX)) )
// 计算10为底的对数
#define LOG_10( VAL )				( log(VAL)/log(10) )

typedef struct _S_ERROR
{
	UINT32 err_type;
	UCHAR8 err_info[64];
} _T_ERROR;

// 网络制式
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
#define NET_DIVE				0xF		// 分集
#define NET_NONE				0xEE	// 空，无相应硬件

#define G2_TYPE_UNICOM		0		//中国联通
#define G2_TYPE_CNMOBILE		1	//中国移动
#define G2_TYPE_TELECOM		2	//中国电信


#define FP_MAX	4			// 支持的最大光口数量
#define RE_MAX	12			// 每个光口支持的最大RE数量
#define REE_MAX	12			// 每个RE支持的最大REE数量

//#define MAX_CHANNEL_COUNT		32	// 支持的通道数

#define WLAN_PORT_COUNT		4	// WLAN端口数量
#define WLAN_PORT_OFFSET		4	// WLAN端口偏移量，即WLAN0对应的光口号

// A段网络制式
#ifdef USER_NET_TYPE_A
#define A_NETWORK_TYPE		USER_NET_TYPE_A		
#else
#define A_NETWORK_TYPE		NET_TYPE_GSM900	
#endif

// B段网络制式
#ifdef USER_NET_TYPE_B

#if 	(( USER_NET_TYPE_B==NET_TYPE_DCS1800 ) && defined(FUNC_FREQ_POINT_SEARCH_EN) && defined(FUNC_FPS_AUTO_SET))
#define B_NETWORK_TYPE		NET_DIVE		
#else
#define B_NETWORK_TYPE		USER_NET_TYPE_B		
#endif

#else
#define B_NETWORK_TYPE		NET_TYPE_WCDMA2100	
#endif

// C段网络制式
#ifdef USER_NET_TYPE_C
#define C_NETWORK_TYPE		USER_NET_TYPE_C		
#else
#define C_NETWORK_TYPE		NET_TYPE_LTE_FDD	
#endif

// D段网络制式
#ifdef USER_NET_TYPE_D
#define D_NETWORK_TYPE		USER_NET_TYPE_D		
#else
#define D_NETWORK_TYPE		NET_TYPE_LTE_FDD	
#endif

// 制式检查，A段为空时，不允许B段设置为分集模式
#if (( A_NETWORK_TYPE==NET_NONE )&&( B_NETWORK_TYPE==NET_DIVE ))
#error "A&B NET TYPE ERROR!"
#endif

// 话务量统计时间(分钟)
#ifdef USER_TRAFFIC_TIME
#define TRAFFIC_TIME		USER_TRAFFIC_TIME	
#else
#define TRAFFIC_TIME		15
#endif

// 参数初始化:控制端口波特率
#ifdef USER_INIT_PARAM_CTRL_BAUD
#define PARAM_INIT_CTRL_BAUD			USER_INIT_PARAM_CTRL_BAUD	
#else
#define PARAM_INIT_CTRL_BAUD			0	// 0-9600bps
#endif

// 参数初始化:透传端口选择
#ifdef USER_INIT_PARAM_THR_PORT
#define PARAM_INIT_THR_PORT			USER_INIT_PARAM_THR_PORT	
#else
#define PARAM_INIT_THR_PORT			0	// 0-485B
#endif

// 参数初始化:透传端口波特率
#ifdef USER_INIT_PARAM_THR_BAUD
#define PARAM_INIT_THR_BAUD			USER_INIT_PARAM_THR_BAUD	
#else
#define PARAM_INIT_THR_BAUD			0	// 0-9600bps
#endif



// 低噪放电压范围
#define V_LNA_MIN		3.6
#define V_LNA_MAX		4.6
#if 0
//RE信息结构体
typedef struct _S_RE_INFO
{
	UCHAR8 flag;	// 状态更新信息
	UCHAR8 id;		// RE的ID号
	UINT16 status;	// RE的工作状态
	UINT32 re_t12;	// RE到前级的光纤延时
} _T_RE_INFO;

//光口信息结构体
typedef struct _S_FP_INFO
{
	UCHAR8 sfp_attach:1;	// 光模块连接检测: 1-已连接
	UCHAR8 comma_lock:1;	// 本端逗号检测: 1-正常检测到逗号,0-异常
	UCHAR8 frm_lock:1;		// 本端帧接收状态: 1-正常, 0-异常
	UCHAR8 tx_err:1;		// 末端下行发送状态: 1-断开
	UCHAR8 rcv_frm_mode;	// 接收帧状态:00---没有收到帧数据，01---收到自发帧，10---收到下行帧，11-收到上行帧
	UCHAR8 re_cnt;			// 光口当前连接的RE数
	UCHAR8 ops_info;		// 对端光口号,最高位为指示位
	struct 
	{
		UCHAR8 id;		// RE的ID号
		UCHAR8 status;	// RE的工作状态
	} re_info[RE_MAX];	//RE_MAX每个光口支持的RE数
} _T_FP_INFO;
#endif

//RE信息结构体
typedef struct _S_RE_INFO
{
	UCHAR8 flag;	    // 状态更新信息 
	UCHAR8 id;		    // RE的ID号 
	UINT16 status;	    // RE的工作状态
	UINT32 re_t12;	    // RE到前级的光纤延时
    UCHAR8 ree_fp_stat;  // 4个连到Ree的光口状态
    UCHAR8 ree_nt_stat;  // 8个连到Ree的网口口状态 
    UCHAR8 pre_ree_fp_stat;  // 4个连到Ree的光口状态
    UCHAR8 pre_ree_nt_stat;  // 8个连到Ree的网口口状态     
    UINT16  ree_work_status;	    // RE的工作状态
	
} _T_RE_INFO;  

//光口信息结构体
typedef struct _S_FP_INFO
{
	UCHAR8 sfp_attach:1;	// 光模块连接检测: 1-已连接
	UCHAR8 comma_lock:1;	// 本端逗号检测: 1-正常检测到逗号,0-异常
	UCHAR8 frm_lock:1;		// 本端帧接收状态: 1-正常, 0-异常
	UCHAR8 tx_err:1;		// 末端下行发送状态: 1-断开
	UCHAR8 rcv_frm_mode;	// 接收帧状态:00---没有收到帧数据，01---收到自发帧，10---收到下行帧，11-收到上行帧
	UCHAR8 re_cnt;			// 光口当前连接的RE数
	UCHAR8 ree_cnt;			// 光口当前连接的REE数
	UCHAR8 ops_info;		// 对端光口号,最高位为指示位
	struct 
	{
		UCHAR8 re_id;		    // RE的ID号 :扩展单元
		UCHAR8 re_status;	    // RE的工作状态
		UCHAR8 ree_sync_st_inf[2];  // 12个拉远口工作状态 
		UCHAR8 pre_ree_sync_st_inf[2];  // 12个拉远口工作状态
		UCHAR8 rf_count;  //Re连接Rf的数量  
		
	} re_info[RE_MAX];	//RE_MAX每个光口支持的RE数
	
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

// 逗号锁定状态
#define COMMA_LOCK			1
#define COMMA_UNLOCK		0

// 帧锁定状态
#define FRAME_LOCK			1
#define FRAME_UNLOCK		0

// 接收帧状态
#define RFM_NO_FRAME		0	// 无数据帧
#define RFM_AT_FRAME		1	// 自发帧
#define RFM_DL_FRAME		2	// 下行帧
#define FRM_UL_FRAME		3	// 上行帧

// 光口对端接收标志，即环网
#define OPS_RCV_FLAG		0x80	// 接收到对端光口数据
#define OPS_NO_MASK		0x0F	// 对端光口号
#define OPS_NOT_FOUND		0x00	// 没有对端光口


// 系统错误状态
#define SYS_ERR_FPGA_LOAD				2
#define SYS_ERR_PLL_UNLOCK				3

#define SYS_A_FLAG		0	// A段
#define SYS_B_FLAG		1	// B段
#define SYS_C_FLAG		2	// C段
#define SYS_D_FLAG		3	// D段

#define SYS_DL_FLAG		0	// 下行标志
#define SYS_UL_FLAG		1	// 上行标志


// DA标志
#define DA_A_FLAG		0	// A段
#define DA_B_FLAG		1	// B段
#define DA_C_FLAG		3	// C段
#define DA_D_FLAG		4	// D段

// 混频器前后端标志
#define MIXER_FRONT		0	// 前端
#define MIXER_BACK		1	// 后端
#define MIXER_A_FLAG	0	// A段
#define MIXER_B_FLAG	1	// B段

#define FPGA_COMPRESS  


// 位检测
#define SET_BIT_FLAG( VALUE, BIT_FLAG )		(VALUE) = (VALUE)|(BIT_FLAG)
#define CLR_BIT_FLAG( VALUE, BIT_FLAG )		(VALUE) = (VALUE)&(~(BIT_FLAG))
#define CHECK_BIT_FLAG( VALUE, BIT_FLAG )	( (VALUE)&(BIT_FLAG) )



// RE的id范围
#define ID_DEFAULT	0		// 默认的ID值
#define ID_MAX		254		// ID的最大值
#define ID_START	64		// ID的分配起始值，即最小值，1~63保留



// function
#define WTD_CLR				{ClrWtd();}//
#define TURN_ON_LED		{LedOn();}//GP2CLR = GPIO_LED_O<<16;
#define TURN_OFF_LED		{LedOff();}//GP2SET = GPIO_LED_O<<16;
#define FLASH_LED			{LedFlash();}//if (GP2DAT&(GPIO_LED_O<<16)) GP2CLR = GPIO_LED_O<<16;else GP2SET = GPIO_LED_O<<16;
#define RS485_DRIVER		{}//GP1SET = GPIO_485_RE_O<<16;

#endif

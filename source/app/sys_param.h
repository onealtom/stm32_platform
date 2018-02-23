/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :sys_param.c
* Description :系统参数处理相关函数
* Version     :v0.1
* Author      :RJ
* Date        :2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			初始版本
**************************************************************/
#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

// 校准REC时；使用保留字低8位；
// 校准RE 时，使用保留字高8位；
#define SEL_REC	(1<<3)	// 0x08
#define SEL_RE	(0<<3)	// 0x00
#define SEL_REE	(1<<4)	// 0x16
#define ADJ_REC	(1<<2)	// 0x04
#define ADJ_RE	(0<<2)
#define ADJ_REE	(1<<4)	// 0x04
#define SEL_DL	(0<<1)	// 0x02
#define SEL_UL	(1<<1)
#define SEL_A	(0<<0)	// 0x00
#define SEL_B	(1<<0)	// 0x01

//模块工作关键参数修改标志
#define PCHG_A_CHANNEL				(1<<0)	// 信道号和通道使能
#define PCHG_A_LTHR					(1<<1)	// 底噪抑制
#define PCHG_A_POW_MODE			(1<<2)	// A段功率控制模式
#define PCHG_A_WORK_EN			(1<<3)	// A段工作使能
#define PCHG_A_FL_CHG				(1<<4)	// A段本振更改
#define PCHG_A_POW_GAIN			(1<<5)	// 功率增益

#define PCHG_B_CHANNEL				(1<<6)	// 信道号和通道使能
#define PCHG_B_LTHR					(1<<7)	// 底噪抑制
#define PCHG_B_POW_MODE			(1<<8)	// B段功率控制模式
#define PCHG_B_WORK_EN			(1<<9)	// B段工作使能
#define PCHG_B_FL_CHG				(1<<10)	// B段本振更改
#define PCHG_B_POW_GAIN			(1<<11)	// 功率增益

#define PCHG_C_CHANNEL				(1<<12)	// 信道号和通道使能
#define PCHG_C_LTHR					(1<<13)	// 底噪抑制
#define PCHG_C_POW_MODE			(1<<14)	// C段功率控制模式
#define PCHG_C_WORK_EN			(1<<15)	// C段工作使能
#define PCHG_C_FL_CHG				(1<<16)	// C段本振更改
#define PCHG_C_POW_GAIN			(1<<17)	// 功率增益

#define PCHG_D_CHANNEL				(1<<18)	// 信道号和通道使能
#define PCHG_D_LTHR					(1<<19)	// 底噪抑制
#define PCHG_D_POW_MODE			(1<<20)	// D段功率控制模式
#define PCHG_D_WORK_EN			(1<<21)	// D段工作使能
#define PCHG_D_FL_CHG				(1<<22)	// D段本振更改
#define PCHG_D_POW_GAIN			(1<<23)	// 功率增益

//#define PCHG_A_GAIN				(1<<3)	// 增益
//#define PCHG_A_DL_POWER			(1<<2)	// 通道功率
//#define PCHG_A_UL_POWER			(1<<3)	// 通道功率
//#define PCHG_A_DL_GAIN				(1<<4)	// 整机增益
//#define PCHG_A_UL_GAIN				(1<<5)	// 整机增益
//#define PCHG_A_DL_ATT				(1<<6)	// 下行数控衰减器
//#define PCHG_A_UL_ATT				(1<<7)	// 上行数控衰减器
//#define PCHG_B_GAIN					(1<<19)	// 增益
//#define PCHG_B_DL_POWER			(1<<18)	// 通道功率
//#define PCHG_B_UL_POWER			(1<<19)	// 通道功率
//#define PCHG_B_DL_GAIN				(1<<20)	// 整机增益
//#define PCHG_B_UL_GAIN				(1<<21)	// 整机增益
//#define PCHG_B_DL_ATT				(1<<22)	// 下行数控衰减器
//#define PCHG_B_UL_ATT				(1<<23)	// 上行数控衰减器

//#define PCHG_SYS_CFG				(1<<24)	// 修改系统参数配置

#define PCHG_CENTER_FRE_FLAG		(1<<16)	// 设置中心频点

#define PCHG_BENZHEN_ADJ_FLAG		(1<<24)	// 设置本振校准参数
#define PCHG_CTRL_BAUD				(1<<25)	// 控制端口波特率设置
#define PCHG_THR_CONFIG			(1<<26)	// 透传端口设置

#define PCHG_FPS_RANGE				(1<<27)	// 频点搜素范围
#define PCHG_LOW_POWER			(1<<28)	// 低功耗模式
#define PCHG_TD_PARAM				(1<<29)	// TD参数
#define PCHG_OPT_DELAY				(1<<30)	// 光口的附加延时值
#define PCHG_SYS_FP_EN				(1<<31)	// 光口使能

extern UINT16 mo_param_count_a;
extern UINT16 mo_param_count_b;
extern UCHAR8 G2Tpye;

void GetValidTopo();
void SaveValidTopo();
void ParamResetDefault();
void ParamPreInit();
void InitUserInterface();
void GetSysParamFromFlash(void);
void SaveSysParamToFlash(void);
BOOL ParamAddTranslate( UCHAR8 len,  UINT16 param_addr, UCHAR8 ab_flag, UINT16* p_mo_addr );
UINT32 CheckParamValid( UINT32 param_add, UINT32 param_val );
UCHAR8 IsAscParam( UINT16 mo_add );
UINT32 ParamChangeVerify( UINT32 length, UCHAR8 * p_param, UCHAR8 ex_add, UINT32* p_err_info );
//BOOL SetSysParam( UINT32 length, UCHAR8 * p_param );
UCHAR8 SetSysParam( UINT16 length, UCHAR8 ex_add_flag, UCHAR8 * p_param, UINT16 * p_err_addr );
UINT16 GetSysParam( UINT32 length, UCHAR8 ex_add, UCHAR8 * p_cmd, UCHAR8 * p_ret );
void RestoreSystemPara( UCHAR8* p_param_buff );
void BackupSystemPara( UCHAR8* p_param_buff );
UINT16 GetMoParamCount( UCHAR8 ab_flag );

#endif

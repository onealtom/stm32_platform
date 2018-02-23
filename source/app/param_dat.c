/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : param_dat.c
* Description : 系统参数处理相关函数
* Version     : v0.1
* Author      : RJ
* Date        : 2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			初始版本
**************************************************************/
#include "Header.h"

const UCHAR8 calc_type[]=
{
	0xff,
	0x00,
	0x08,
	0x07,
	0x0A
};
_T_PARAM_1B sys_param_1b[]=
{
	
	{	PARA_A_CHANNEL_COUNT	,PT_AP_G_EX|PT_US,	0,},	//	A段支持的通道数
	{	PARA_A_DL_WORK_EN	,PT_AP_G_EX|PT_US,	0,},	//	A段下行工作使能
	{	PARA_A_UL_WORK_EN	,PT_AP_G_EX|PT_US,	0,},	//	A段上行工作使能
	{	PARA_A_DPOW_MODE	,PT_NC,	0,},	//	A段下行功率控制方式
	{	PARA_A_UPOW_MODE	,PT_NC,	0,},	//	A段上行功率控制方式
	{	PARA_A_LTHR_EN	,PT_AP_G_EX|PT_US,	1,},	//	A段上行底噪抑制使能
	{	PARA_A_LTHR_UP	,PT_AP_G_EX|PT_NC,	1,},	//	A段底噪抑制上门限
	{	PARA_A_LTHR_DN	,PT_AP_G_EX|PT_SI,	1,},	//	A段底噪抑制下门限
	{	PARA_A_DCH_EN1	,PT_AP|PT_US,	1,},	//	A段下行通道工作使能1
	{	PARA_A_DCH_EN2	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能2
	{	PARA_A_DCH_EN3	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能3
	{	PARA_A_DCH_EN4	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能4
	{	PARA_A_DCH_EN5	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能5
	{	PARA_A_DCH_EN6	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能6
	{	PARA_A_DCH_EN7	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能7
	{	PARA_A_DCH_EN8	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能8
	{	PARA_A_DCH_EN9	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能9
	{	PARA_A_DCH_EN10	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能10
	{	PARA_A_DCH_EN11	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能11
	{	PARA_A_DCH_EN12	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能12
	{	PARA_A_DCH_EN13	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能13
	{	PARA_A_DCH_EN14	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能14
	{	PARA_A_DCH_EN15	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能15
	{	PARA_A_DCH_EN16	,PT_AP|PT_US,	0,},	//	A段下行通道工作使能16
	{	PARA_A_UCH_EN1	,PT_NC,	1,},	//	A段上行通道工作使能1
	{	PARA_A_UCH_EN2	,PT_NC,	0,},	//	A段上行通道工作使能2
	{	PARA_A_UCH_EN3	,PT_NC,	0,},	//	A段上行通道工作使能3
	{	PARA_A_UCH_EN4	,PT_NC,	0,},	//	A段上行通道工作使能4
	{	PARA_A_UCH_EN5	,PT_NC,	0,},	//	A段上行通道工作使能5
	{	PARA_A_UCH_EN6	,PT_NC,	0,},	//	A段上行通道工作使能6
	{	PARA_A_UCH_EN7	,PT_NC,	0,},	//	A段上行通道工作使能7
	{	PARA_A_UCH_EN8	,PT_NC,	0,},	//	A段上行通道工作使能8
	{	PARA_A_UCH_EN9	,PT_NC,	0,},	//	A段上行通道工作使能9
	{	PARA_A_UCH_EN10	,PT_NC,	0,},	//	A段上行通道工作使能10
	{	PARA_A_UCH_EN11	,PT_NC,	0,},	//	A段上行通道工作使能11
	{	PARA_A_UCH_EN12	,PT_NC,	0,},	//	A段上行通道工作使能12
	{	PARA_A_UCH_EN13	,PT_NC,	0,},	//	A段上行通道工作使能13
	{	PARA_A_UCH_EN14	,PT_NC,	0,},	//	A段上行通道工作使能14
	{	PARA_A_UCH_EN15	,PT_NC,	0,},	//	A段上行通道工作使能15
	{	PARA_A_UCH_EN16	,PT_NC,	0,},	//	A段上行通道工作使能16
	{	PARA_A_DCH_GAIN1	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益1
	{	PARA_A_DCH_GAIN2	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益2
	{	PARA_A_DCH_GAIN3	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益3
	{	PARA_A_DCH_GAIN4	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益4
	{	PARA_A_DCH_GAIN5	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益5
	{	PARA_A_DCH_GAIN6	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益6
	{	PARA_A_DCH_GAIN7	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益7
	{	PARA_A_DCH_GAIN8	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益8
	{	PARA_A_DCH_GAIN9	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益9
	{	PARA_A_DCH_GAIN10	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益10
	{	PARA_A_DCH_GAIN11	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益11
	{	PARA_A_DCH_GAIN12	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益12
	{	PARA_A_DCH_GAIN13	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益13
	{	PARA_A_DCH_GAIN14	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益14
	{	PARA_A_DCH_GAIN15	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益15
	{	PARA_A_DCH_GAIN16	,PT_AP_G_EX|PT_US,	40,},	//	A段下行选频通道放大器增益16
	{	PARA_A_UCH_GAIN1	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益1
	{	PARA_A_UCH_GAIN2	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益2
	{	PARA_A_UCH_GAIN3	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益3
	{	PARA_A_UCH_GAIN4	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益4
	{	PARA_A_UCH_GAIN5	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益5
	{	PARA_A_UCH_GAIN6	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益6
	{	PARA_A_UCH_GAIN7	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益7
	{	PARA_A_UCH_GAIN8	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益8
	{	PARA_A_UCH_GAIN9	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益9
	{	PARA_A_UCH_GAIN10	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益10
	{	PARA_A_UCH_GAIN11	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益11
	{	PARA_A_UCH_GAIN12	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益12
	{	PARA_A_UCH_GAIN13	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益13
	{	PARA_A_UCH_GAIN14	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益14
	{	PARA_A_UCH_GAIN15	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益15
	{	PARA_A_UCH_GAIN16	,PT_AP_G_EX|PT_US,	40,},	//	A段上行选频通道放大器增益16
	{	PARA_A_DCH_ATT1	,PT_AP_G_EX|PT_US,	0,},	//	A段下行数控衰减量1
	{	PARA_A_DCH_ATT2	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量2
	{	PARA_A_DCH_ATT3	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量3
	{	PARA_A_DCH_ATT4	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量4
	{	PARA_A_DCH_ATT5	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量5
	{	PARA_A_DCH_ATT6	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量6
	{	PARA_A_DCH_ATT7	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量7
	{	PARA_A_DCH_ATT8	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量8
	{	PARA_A_DCH_ATT9	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量9
	{	PARA_A_DCH_ATT10	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量10
	{	PARA_A_DCH_ATT11	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量11
	{	PARA_A_DCH_ATT12	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量12
	{	PARA_A_DCH_ATT13	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量13
	{	PARA_A_DCH_ATT14	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量14
	{	PARA_A_DCH_ATT15	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量15
	{	PARA_A_DCH_ATT16	,PT_AP_G_EX|PT_NC,	0,},	//	A段下行数控衰减量16
	{	PARA_A_UCH_ATT1	,PT_AP|PT_US,	0,},	//	A段上行数控衰减量1
	{	PARA_A_UCH_ATT2	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量2
	{	PARA_A_UCH_ATT3	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量3
	{	PARA_A_UCH_ATT4	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量4
	{	PARA_A_UCH_ATT5	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量5
	{	PARA_A_UCH_ATT6	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量6
	{	PARA_A_UCH_ATT7	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量7
	{	PARA_A_UCH_ATT8	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量8
	{	PARA_A_UCH_ATT9	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量9
	{	PARA_A_UCH_ATT10	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量10
	{	PARA_A_UCH_ATT11	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量11
	{	PARA_A_UCH_ATT12	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量12
	{	PARA_A_UCH_ATT13	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量13
	{	PARA_A_UCH_ATT14	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量14
	{	PARA_A_UCH_ATT15	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量15
	{	PARA_A_UCH_ATT16	,PT_AP_G_EX|PT_NC,	0,},	//	A段上行数控衰减量16
	{	PARA_A_DL_PA_GAIN	,PT_NC,	0,},	//	A段下行功放增益
	{	PARA_A_UL_PA_GAIN	,PT_NC,	0,},	//	A段上行功放增益
	{	PARA_A_TX_PLL_ST	,PT_AP|PT_RO|PT_US,	0,},	//	A段下行PLL状态,287 2为TX_VCO锁定，其他失锁
	{	PARA_A_RX_PLL_ST	,PT_AP|PT_RO|PT_US,	0,},	//	A段上行PLL状态,247 2为RX_VCO锁定，其他失锁
	{	PARA_A_INIT_DA_ST	,PT_AP_G_EX|PT_NC,	0,},	//	初始化A段DA状态,17 1A为锁定+发送接收使能打开，其他异常
	{	PARA_A_BB_PLL_LOCK	,PT_AP_G_EX|PT_NC,	0,},	//	A段DA PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
	{	PARA_A_FSAT	,PT_NC,	0,},	//	A段前端AD输入状态
	{	PARA_A_DSAT	,PT_NC,	0,},	//	A段后端DA输出状态
	{	PARA_A_PA_VG_EN	,PT_NC,	0,},	//	A段功放栅压状态
	{	PARA_A_PA_VT	,PT_NC,	0,},	//	A段功放管电压显示
	{	PARA_A_Modulator_EN	,PT_NC,	0,},	//	A段调制器状态
	{	PARA_A_LNA_VT	,PT_NC,	0,},	//	A段下行低噪放LNA电压
	{	PARA_A_LNA1_ST	,PT_RO|PT_US,	0,},	//	上行LNA1状态
	{	PARA_A_LNA2_ST	,PT_RO|PT_US,	0,},	//	上行LNA2状态
	{	PARA_A_BUSY_TIME	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_SI,	0,},	//	A段上行时隙占用率
	{	PARA_A_PRI_ADD,		PT_AP_G_EX|PT_RO|PT_US,	1,},	//	A段模块地址
	{	PARA_A_UL_POW_1B, 	PT_AP_G|PT_SI, 	0,},	//	A段上行输入总功率
	{	PARA_A_DL_POW_1B, 	PT_AP_G_EX|PT_RO|PT_SI, 	0,},	//	A段下行输入总功率
	{	PARA_A_DCH_REC_RF_ATT1,		PT_AP_G_EX|PT_US, 	0},	 // REC端的上行数控衰减量。即RF端的链路上行衰减量 RF 
	{	PARA_A_UCH_REC_RF_ATT1,		PT_AP_G_EX|PT_US, 	0},	 // REC端的上行数控衰减量。即RF端的链路上行衰减量 RF 
	{	PARA_B_CHANNEL_COUNT	, PT_BP_G_EX|PT_US,	0,},	//	B段支持的通道数
	{	PARA_B_DL_WORK_EN	,PT_BP_G_EX|PT_US,	1,},	//	B段下行工作使能
	{	PARA_B_UL_WORK_EN	,PT_BP_G_EX|PT_US,	1,},	//	B段上行工作使能
	{	PARA_B_DPOW_MODE	,PT_NC,	0,},	//	B段下行功率控制方式
	{	PARA_B_UPOW_MODE	,PT_NC,	0,},	//	B段上行功率控制方式
	{	PARA_B_LTHR_EN	,PT_BP_G_EX|PT_US,	0,},	//	B段上行底噪抑制使能
	{	PARA_B_LTHR_UP	,PT_BP_G_EX|PT_NC,	0,},	//	B段底噪抑制上门限
	{	PARA_B_LTHR_DN	,PT_BP_G_EX|PT_SI,	0,},	//	B段底噪抑制下门限
	{	PARA_B_DCH_EN1		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能1
	{	PARA_B_DCH_EN2		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能2
	{	PARA_B_DCH_EN3		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能3
	{	PARA_B_DCH_EN4		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能4
	{	PARA_B_DCH_EN5		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能5
	{	PARA_B_DCH_EN6		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能6
	{	PARA_B_DCH_EN7		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能7
	{	PARA_B_DCH_EN8		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能8
	{	PARA_B_DCH_EN9		,PT_BP|PT_US,	1,},	//	B段下行通道工作使能9
	{	PARA_B_DCH_EN10	,PT_BP|PT_US,	1,},	//	B段下行通道工作使能10
	{	PARA_B_DCH_EN11	,PT_BP|PT_US,	1,},	//	B段下行通道工作使能11
	{	PARA_B_DCH_EN12	,PT_BP|PT_US,	1,},	//	B段下行通道工作使能12
	{	PARA_B_DCH_EN13	,PT_BP|PT_US,	1,},	//	B段下行通道工作使能13
	{	PARA_B_DCH_EN14	,PT_BP|PT_US,	1,},	//	B段下行通道工作使能14
	{	PARA_B_DCH_EN15	,PT_BP|PT_US,	1,},	//	B段下行通道工作使能15
	{	PARA_B_DCH_EN16	,PT_BP|PT_US,	1,},	//	B段下行通道工作使能16
	{	PARA_B_UCH_EN1		,PT_US,	1,},	//	B段上行通道工作使能1
	{	PARA_B_UCH_EN2		,PT_US,	1,},	//	B段上行通道工作使能2
	{	PARA_B_UCH_EN3		,PT_US,	1,},	//	B段上行通道工作使能3
	{	PARA_B_UCH_EN4		,PT_US,	1,},	//	B段上行通道工作使能4
	{	PARA_B_UCH_EN5		,PT_US,	1,},	//	B段上行通道工作使能5
	{	PARA_B_UCH_EN6		,PT_US,	1,},	//	B段上行通道工作使能6
	{	PARA_B_UCH_EN7		,PT_US,	1,},	//	B段上行通道工作使能7
	{	PARA_B_UCH_EN8		,PT_US,	1,},	//	B段上行通道工作使能8
	{	PARA_B_UCH_EN9		,PT_US,	1,},	//	B段上行通道工作使能9
	{	PARA_B_UCH_EN10	,PT_US,	1,},	//	B段上行通道工作使能10
	{	PARA_B_UCH_EN11	,PT_US,	1,},	//	B段上行通道工作使能11
	{	PARA_B_UCH_EN12	,PT_US,	1,},	//	B段上行通道工作使能12
	{	PARA_B_UCH_EN13	,PT_US,	1,},	//	B段上行通道工作使能13
	{	PARA_B_UCH_EN14	,PT_US,	1,},	//	B段上行通道工作使能14
	{	PARA_B_UCH_EN15	,PT_US,	1,},	//	B段上行通道工作使能15
	{	PARA_B_UCH_EN16	,PT_US,	1,},	//	B段上行通道工作使能16
	{	PARA_B_DCH_GAIN1	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益1
	{	PARA_B_DCH_GAIN2	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益2
	{	PARA_B_DCH_GAIN3	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益3
	{	PARA_B_DCH_GAIN4	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益4
	{	PARA_B_DCH_GAIN5	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益5
	{	PARA_B_DCH_GAIN6	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益6
	{	PARA_B_DCH_GAIN7	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益7
	{	PARA_B_DCH_GAIN8	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益8
	{	PARA_B_DCH_GAIN9	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益9
	{	PARA_B_DCH_GAIN10	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益10
	{	PARA_B_DCH_GAIN11	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益11
	{	PARA_B_DCH_GAIN12	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益12
	{	PARA_B_DCH_GAIN13	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益13
	{	PARA_B_DCH_GAIN14	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益14
	{	PARA_B_DCH_GAIN15	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益15
	{	PARA_B_DCH_GAIN16	,PT_BP_G_EX|PT_US,	40,},	//	B段下行选频通道放大器增益16
	{	PARA_B_UCH_GAIN1	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益1
	{	PARA_B_UCH_GAIN2	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益2
	{	PARA_B_UCH_GAIN3	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益3
	{	PARA_B_UCH_GAIN4	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益4
	{	PARA_B_UCH_GAIN5	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益5
	{	PARA_B_UCH_GAIN6	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益6
	{	PARA_B_UCH_GAIN7	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益7
	{	PARA_B_UCH_GAIN8	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益8
	{	PARA_B_UCH_GAIN9	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益9
	{	PARA_B_UCH_GAIN10	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益10
	{	PARA_B_UCH_GAIN11	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益11
	{	PARA_B_UCH_GAIN12	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益12
	{	PARA_B_UCH_GAIN13	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益13
	{	PARA_B_UCH_GAIN14	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益14
	{	PARA_B_UCH_GAIN15	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益15
	{	PARA_B_UCH_GAIN16	,PT_BP_G_EX|PT_US,	40,},	//	B段上行选频通道放大器增益16
	{	PARA_B_DCH_ATT1	,PT_BP_G_EX|PT_US,	0,},	//	B段下行输出数控衰减量1
	{	PARA_B_DCH_ATT2	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量2
	{	PARA_B_DCH_ATT3	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量3
	{	PARA_B_DCH_ATT4	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量4
	{	PARA_B_DCH_ATT5	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量5
	{	PARA_B_DCH_ATT6	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量6
	{	PARA_B_DCH_ATT7	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量7
	{	PARA_B_DCH_ATT8	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量8
	{	PARA_B_DCH_ATT9	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量9
	{	PARA_B_DCH_ATT10	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量10
	{	PARA_B_DCH_ATT11	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量11
	{	PARA_B_DCH_ATT12	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量12
	{	PARA_B_DCH_ATT13	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量13
	{	PARA_B_DCH_ATT14	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量14
	{	PARA_B_DCH_ATT15	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量15
	{	PARA_B_DCH_ATT16	,PT_BP_G_EX|PT_NC,	0,},	//	B段下行输出数控衰减量16
	{	PARA_B_UCH_ATT1	,PT_BP|PT_US,	0,},	//	B段上行输入数控衰减量1(上行数控总衰减量)
	{	PARA_B_UCH_ATT2	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量2
	{	PARA_B_UCH_ATT3	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量3
	{	PARA_B_UCH_ATT4	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量4
	{	PARA_B_UCH_ATT5	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量5
	{	PARA_B_UCH_ATT6	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量6
	{	PARA_B_UCH_ATT7	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量7
	{	PARA_B_UCH_ATT8	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量8
	{	PARA_B_UCH_ATT9	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量9
	{	PARA_B_UCH_ATT10	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量10
	{	PARA_B_UCH_ATT11	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量11
	{	PARA_B_UCH_ATT12	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量12
	{	PARA_B_UCH_ATT13	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量13
	{	PARA_B_UCH_ATT14	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量14
	{	PARA_B_UCH_ATT15	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量15
	{	PARA_B_UCH_ATT16	,PT_BP_G_EX|PT_NC,	0,},	//	B段上行输入数控衰减量16
	{	PARA_B_DL_PA_GAIN	,PT_NC,	0,},	//	B段下行功放增益
	{	PARA_B_UL_PA_GAIN	,PT_NC,	0,},	//	B段上行功放增益
	{	PARA_B_TX_PLL_ST	,PT_BP|PT_RO|PT_US,	0,},	//	B段下行PLL状态,287 2为TX_VCO锁定，其他失锁
	{	PARA_B_RX_PLL_ST	,PT_BP|PT_RO|PT_US,	0,},	//	B段上行PLL状态,247 2为RX_VCO锁定，其他失锁
	{	PARA_B_INIT_DA_ST	,PT_NC,	0,},	//	初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
	{	PARA_B_BB_PLL_LOCK	,PT_NC,	0,},	//	B段DA PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
	{	PARA_B_FSAT	,PT_NC,	0,},	//	B段前端AD输入状态
	{	PARA_B_DSAT	,PT_NC,	0,},	//	B段后端DA输出状态
	{	PARA_B_PA_VG_EN	,PT_NC,	0,},	//	B段功放栅压状态
	{	PARA_B_PA_VT	,PT_NC,	0,},	//	B段功放管电压显示
	{	PARA_B_Modulator_EN	,PT_NC,	0,},	//	B段调制器状态
	{	PARA_B_LNA_VT	,PT_NC,	0,},	//	B段下行低噪放LNA电压
	{	PARA_B_LNA1_ST	,PT_RO|PT_US,	0,},	//	上行LNA1状态
	{	PARA_B_LNA2_ST	,PT_RO|PT_US,	0,},	//	上行LNA2状态
	{	PARA_B_BUSY_TIME	,PT_RO|PT_SI,	0,},	//	B段上行时隙占用率
	{	PARA_B_PRI_ADD,		PT_BP_G_EX|PT_RO|PT_US,	2,},	//	B段模块地址
	{	PARA_B_UL_POW_1B, 	/*PT_BP_G|*/PT_SI, 	0,},	//	B段上行输入总功率
	{	PARA_B_DL_POW_1B, 	PT_BP_G_EX|PT_RO|PT_SI, 	0,},	//	B段下行输入总功率
	{	PARA_B_DCH_REC_RF_ATT1,		PT_BP_G_EX|PT_US, 	0},	 // REC端的上行数控衰减量。即RF端的链路上行衰减量 RF 
	{	PARA_B_UCH_REC_RF_ATT1,		PT_BP_G_EX|PT_US, 	0},	 // REC端的上行数控衰减量。即RF端的链路上行衰减量 RF 
	{	PARA_C_CHANNEL_COUNT	, PT_CP_G_EX|PT_US,	0,},	//	C段支持的通道数
	{	PARA_C_DL_WORK_EN	,PT_CP_G_EX|PT_US,	1,},	//	C段下行工作使能
	{	PARA_C_UL_WORK_EN	,PT_CP_G_EX|PT_US,	1,},	//	C段上行工作使能
	{	PARA_C_DPOW_MODE	,PT_NC,	0,},	//	C段下行功率控制方式
	{	PARA_C_UPOW_MODE	,PT_NC,	0,},	//	C段上行功率控制方式
	{	PARA_C_LTHR_EN	,PT_CP_G_EX|PT_US,	0,},	//	C段上行底噪抑制使能
	{	PARA_C_LTHR_UP	,PT_CP_G_EX|PT_NC,	0,},	//	C段底噪抑制上门限
	{	PARA_C_LTHR_DN	,PT_CP_G_EX|PT_SI,	0,},	//	C段底噪抑制下门限
	{	PARA_C_DCH_EN1  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能1
	{	PARA_C_DCH_EN2  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能2
	{	PARA_C_DCH_EN3  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能3
	{	PARA_C_DCH_EN4  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能4
	{	PARA_C_DCH_EN5  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能5
	{	PARA_C_DCH_EN6  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能6
	{	PARA_C_DCH_EN7  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能7
	{	PARA_C_DCH_EN8  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能8
	{	PARA_C_DCH_EN9  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能9
	{	PARA_C_DCH_EN10  ,PT_CP|PT_US, 1,}, // C段下行通道工作使能10
	{	PARA_C_UCH_EN1		,PT_US,	1,},	//	C段上行通道工作使能1
	{	PARA_C_UCH_EN2		,PT_US,	1,},	//	C段上行通道工作使能2
	{	PARA_C_UCH_EN3		,PT_US,	1,},	//	C段上行通道工作使能3
	{	PARA_C_UCH_EN4		,PT_US,	1,},	//	C段上行通道工作使能4
	{	PARA_C_UCH_EN5		,PT_US,	1,},	//	C段上行通道工作使能5
	{	PARA_C_UCH_EN6		,PT_US,	1,},	//	C段上行通道工作使能6
	{	PARA_C_UCH_EN7		,PT_US,	1,},	//	C段上行通道工作使能7
	{	PARA_C_UCH_EN8		,PT_US,	1,},	//	C段上行通道工作使能8
	{	PARA_C_UCH_EN9		,PT_US,	1,},	//	C段上行通道工作使能9
	{	PARA_C_UCH_EN10		,PT_US,	1,},	//	C段上行通道工作使能10
	{	PARA_C_DCH_GAIN1	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益1
	{	PARA_C_DCH_GAIN2	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益2
	{	PARA_C_DCH_GAIN3	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益3
	{	PARA_C_DCH_GAIN4	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益4
	{	PARA_C_DCH_GAIN5	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益5
	{	PARA_C_DCH_GAIN6	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益6
	{	PARA_C_DCH_GAIN7	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益7
	{	PARA_C_DCH_GAIN8	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益8
	{	PARA_C_DCH_GAIN9	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益9
	{	PARA_C_DCH_GAIN10	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益10
	{	PARA_C_DCH_GAIN11	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益11
	{	PARA_C_DCH_GAIN12	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益12
	{	PARA_C_DCH_GAIN13	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益13
	{	PARA_C_DCH_GAIN14	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益14
	{	PARA_C_DCH_GAIN15	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益15
	{	PARA_C_DCH_GAIN16	,PT_CP_G_EX|PT_US,	40,},	//	C段下行选频通道放大器增益16
	{	PARA_C_UCH_GAIN1	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益1
	{	PARA_C_UCH_GAIN2	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益2
	{	PARA_C_UCH_GAIN3	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益3
	{	PARA_C_UCH_GAIN4	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益4
	{	PARA_C_UCH_GAIN5	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益5
	{	PARA_C_UCH_GAIN6	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益6
	{	PARA_C_UCH_GAIN7	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益7
	{	PARA_C_UCH_GAIN8	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益8
	{	PARA_C_UCH_GAIN9	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益9
	{	PARA_C_UCH_GAIN10	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益10
	{	PARA_C_UCH_GAIN11	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益11
	{	PARA_C_UCH_GAIN12	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益12
	{	PARA_C_UCH_GAIN13	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益13
	{	PARA_C_UCH_GAIN14	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益14
	{	PARA_C_UCH_GAIN15	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益15
	{	PARA_C_UCH_GAIN16	,PT_CP_G_EX|PT_US,	40,},	//	C段上行选频通道放大器增益16
	{	PARA_C_DCH_ATT1	,PT_CP_G_EX|PT_US,	0,},	//	C段下行输出数控衰减量1
	{	PARA_C_DCH_ATT2	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量2
	{	PARA_C_DCH_ATT3	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量3
	{	PARA_C_DCH_ATT4	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量4
	{	PARA_C_DCH_ATT5	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量5
	{	PARA_C_DCH_ATT6	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量6
	{	PARA_C_DCH_ATT7	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量7
	{	PARA_C_DCH_ATT8	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量8
	{	PARA_C_DCH_ATT9	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量9
	{	PARA_C_DCH_ATT10	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量10
	{	PARA_C_DCH_ATT11	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量11
	{	PARA_C_DCH_ATT12	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量12
	{	PARA_C_DCH_ATT13	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量13
	{	PARA_C_DCH_ATT14	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量14
	{	PARA_C_DCH_ATT15	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量15
	{	PARA_C_DCH_ATT16	,PT_CP_G_EX|PT_NC,	0,},	//	C段下行输出数控衰减量16
	{	PARA_C_UCH_ATT1	,PT_CP|PT_US,	0,},	//	C段上行输入数控衰减量1
	{	PARA_C_UCH_ATT2	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量2
	{	PARA_C_UCH_ATT3	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量3
	{	PARA_C_UCH_ATT4	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量4
	{	PARA_C_UCH_ATT5	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量5
	{	PARA_C_UCH_ATT6	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量6
	{	PARA_C_UCH_ATT7	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量7
	{	PARA_C_UCH_ATT8	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量8
	{	PARA_C_UCH_ATT9	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量9
	{	PARA_C_UCH_ATT10	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量10
	{	PARA_C_UCH_ATT11	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量11
	{	PARA_C_UCH_ATT12	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量12
	{	PARA_C_UCH_ATT13	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量13
	{	PARA_C_UCH_ATT14	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量14
	{	PARA_C_UCH_ATT15	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量15
	{	PARA_C_UCH_ATT16	,PT_CP_G_EX|PT_NC,	0,},	//	C段上行输入数控衰减量16
	{	PARA_C_DL_PA_GAIN	,PT_NC,	0,},	//	C段下行功放增益
	{	PARA_C_UL_PA_GAIN	,PT_NC,	0,},	//	C段上行功放增益
	{	PARA_C_TX_PLL_ST	,PT_CP|PT_RO|PT_US,	0,},	//	C段下行PLL状态,287 2为TX_VCO锁定，其他失锁
	{	PARA_C_RX_PLL_ST	,PT_CP|PT_RO|PT_US,	0,},	//	C段上行PLL状态,247 2为RX_VCO锁定，其他失锁
	{	PARA_C_INIT_DA_ST	,PT_NC,	0,},	//	初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
	{	PARA_C_BB_PLL_LOCK	,PT_NC,	0,},	//	C段DA PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
	{	PARA_C_FSAT	,PT_NC,	0,},	//	C段前端AD输入状态
	{	PARA_C_DSAT	,PT_NC,	0,},	//	C段后端DA输出状态
	{	PARA_C_PA_VG_EN	,PT_NC,	0,},	//	C段功放栅压状态
	{	PARA_C_PA_VT	,PT_NC,	0,},	//	C段功放管电压显示
	{	PARA_C_Modulator_EN	,PT_NC,	0,},	//	C段调制器状态
	{	PARA_C_LNA_VT	,PT_NC,	0,},	//	C段下行低噪放LNA电压
	{	PARA_C_LNA1_ST	,PT_RO|PT_US,	0,},	//	上行LNA1状态
	{	PARA_C_LNA2_ST	,PT_RO|PT_US,	0,},	//	上行LNA2状态
	{	PARA_C_BUSY_TIME	,PT_RO|PT_SI,	0,},	//	C段上行时隙占用率
	{	PARA_C_PRI_ADD,  PT_CP_G_EX|PT_RO|PT_US, 3,}, // C段模块地址
	{	PARA_C_UL_POW_1B, 	/*PT_BP_G|*/PT_SI, 	0,},	//	C段上行输入总功率
	{	PARA_C_DL_POW_1B, 	PT_CP_G_EX|PT_RO|PT_SI, 	0,},	//	C段下行输入总功率
	{	PARA_C_DCH_REC_RF_ATT1,		PT_CP_G_EX|PT_US, 	0},	 // REC端的上行数控衰减量。即RF端的链路上行衰减量 RF 
	{	PARA_C_UCH_REC_RF_ATT1,		PT_CP_G_EX|PT_US, 	0},	 // REC端的上行数控衰减量。即RF端的链路上行衰减量 RF 
	{	PARA_D_CHANNEL_COUNT	, PT_DP_G_EX|PT_US,	0,},	//	D段支持的通道数
	{	PARA_D_DL_WORK_EN	,PT_DP_G_EX|PT_US,	1,},	//	D段下行工作使能
	{	PARA_D_UL_WORK_EN	,PT_DP_G_EX|PT_US,	1,},	//	D段上行工作使能
	{	PARA_D_DPOW_MODE	,PT_NC,	0,},	//	D段下行功率控制方式
	{	PARA_D_UPOW_MODE	,PT_NC,	0,},	//	D段上行功率控制方式
	{	PARA_D_LTHR_EN	,PT_DP_G_EX|PT_US,	0,},	//	D段上行底噪抑制使能
	{	PARA_D_LTHR_UP	,PT_DP_G_EX|PT_NC,	0,},	//	D段底噪抑制上门限
	{	PARA_D_LTHR_DN	,PT_DP_G_EX|PT_SI,	0,},	//	D段底噪抑制下门限
	{	PARA_D_DCH_EN1  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能1
	{	PARA_D_DCH_EN2  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能2
	{	PARA_D_DCH_EN3  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能3
	{	PARA_D_DCH_EN4  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能4
	{	PARA_D_DCH_EN5  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能5
	{	PARA_D_DCH_EN6  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能6
	{	PARA_D_DCH_EN7  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能7
	{	PARA_D_DCH_EN8  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能8
	{	PARA_D_DCH_EN9  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能9
	{	PARA_D_DCH_EN10  ,PT_DP|PT_US, 1,}, // D段下行通道工作使能10
	{	PARA_D_UCH_EN1		,PT_US, 1,},	//	D段上行通道工作使能1
	{	PARA_D_UCH_EN2		,PT_US, 1,},	//	D段上行通道工作使能2
	{	PARA_D_UCH_EN3		,PT_US, 1,},	//	D段上行通道工作使能3
	{	PARA_D_UCH_EN4		,PT_US, 1,},	//	D段上行通道工作使能4
	{	PARA_D_UCH_EN5		,PT_US, 1,},	//	D段上行通道工作使能5
	{	PARA_D_UCH_EN6		,PT_US, 1,},	//	D段上行通道工作使能6
	{	PARA_D_UCH_EN7		,PT_US, 1,},	//	D段上行通道工作使能7
	{	PARA_D_UCH_EN8		,PT_US, 1,},	//	D段上行通道工作使能8
	{	PARA_D_UCH_EN9		,PT_US, 1,},	//	D段上行通道工作使能9
	{	PARA_D_UCH_EN10 	,PT_US, 1,},	//	D段上行通道工作使能10
	{	PARA_D_DCH_GAIN1	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益1
	{	PARA_D_DCH_GAIN2	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益2
	{	PARA_D_DCH_GAIN3	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益3
	{	PARA_D_DCH_GAIN4	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益4
	{	PARA_D_DCH_GAIN5	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益5
	{	PARA_D_DCH_GAIN6	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益6
	{	PARA_D_DCH_GAIN7	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益7
	{	PARA_D_DCH_GAIN8	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益8
	{	PARA_D_DCH_GAIN9	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益9
	{	PARA_D_DCH_GAIN10	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益10
	{	PARA_D_DCH_GAIN11	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益11
	{	PARA_D_DCH_GAIN12	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益12
	{	PARA_D_DCH_GAIN13	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益13
	{	PARA_D_DCH_GAIN14	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益14
	{	PARA_D_DCH_GAIN15	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益15
	{	PARA_D_DCH_GAIN16	,PT_DP_G_EX|PT_US,	40,},	//	D段下行选频通道放大器增益16
	{	PARA_D_UCH_GAIN1	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益1
	{	PARA_D_UCH_GAIN2	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益2
	{	PARA_D_UCH_GAIN3	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益3
	{	PARA_D_UCH_GAIN4	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益4
	{	PARA_D_UCH_GAIN5	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益5
	{	PARA_D_UCH_GAIN6	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益6
	{	PARA_D_UCH_GAIN7	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益7
	{	PARA_D_UCH_GAIN8	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益8
	{	PARA_D_UCH_GAIN9	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益9
	{	PARA_D_UCH_GAIN10	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益10
	{	PARA_D_UCH_GAIN11	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益11
	{	PARA_D_UCH_GAIN12	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益12
	{	PARA_D_UCH_GAIN13	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益13
	{	PARA_D_UCH_GAIN14	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益14
	{	PARA_D_UCH_GAIN15	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益15
	{	PARA_D_UCH_GAIN16	,PT_DP_G_EX|PT_US,	40,},	//	D段上行选频通道放大器增益16
	{	PARA_D_DCH_ATT1	,PT_DP_G_EX|PT_US,	0,},	//	D段下行输出数控衰减量1
	{	PARA_D_DCH_ATT2	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量2
	{	PARA_D_DCH_ATT3	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量3
	{	PARA_D_DCH_ATT4	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量4
	{	PARA_D_DCH_ATT5	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量5
	{	PARA_D_DCH_ATT6	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量6
	{	PARA_D_DCH_ATT7	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量7
	{	PARA_D_DCH_ATT8	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量8
	{	PARA_D_DCH_ATT9	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量9
	{	PARA_D_DCH_ATT10	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量10
	{	PARA_D_DCH_ATT11	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量11
	{	PARA_D_DCH_ATT12	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量12
	{	PARA_D_DCH_ATT13	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量13
	{	PARA_D_DCH_ATT14	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量14
	{	PARA_D_DCH_ATT15	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量15
	{	PARA_D_DCH_ATT16	,PT_DP_G_EX|PT_NC,	0,},	//	D段下行输出数控衰减量16
	{	PARA_D_UCH_ATT1	,PT_DP|PT_US,	0,},	//	D段上行输入数控衰减量1
	{	PARA_D_UCH_ATT2	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量2
	{	PARA_D_UCH_ATT3	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量3
	{	PARA_D_UCH_ATT4	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量4
	{	PARA_D_UCH_ATT5	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量5
	{	PARA_D_UCH_ATT6	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量6
	{	PARA_D_UCH_ATT7	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量7
	{	PARA_D_UCH_ATT8	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量8
	{	PARA_D_UCH_ATT9	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量9
	{	PARA_D_UCH_ATT10	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量10
	{	PARA_D_UCH_ATT11	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量11
	{	PARA_D_UCH_ATT12	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量12
	{	PARA_D_UCH_ATT13	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量13
	{	PARA_D_UCH_ATT14	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量14
	{	PARA_D_UCH_ATT15	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量15
	{	PARA_D_UCH_ATT16	,PT_DP_G_EX|PT_NC,	0,},	//	D段上行输入数控衰减量16
	{	PARA_D_DL_PA_GAIN	,PT_NC,	0,},	//	D段下行功放增益
	{	PARA_D_UL_PA_GAIN	,PT_NC,	0,},	//	D段上行功放增益
	{	PARA_D_TX_PLL_ST	,PT_DP|PT_RO|PT_US,	0,},	//	D段下行PLL状态,287 2为TX_VCO锁定，其他失锁
	{	PARA_D_RX_PLL_ST	,PT_DP|PT_RO|PT_US,	0,},	//	D段上行PLL状态,247 2为RX_VCO锁定，其他失锁
	{	PARA_D_INIT_DA_ST	,PT_NC,	0,},	//	初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
	{	PARA_D_BB_PLL_LOCK	,PT_NC,	0,},	//	D段DA PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
	{	PARA_D_FSAT	,PT_NC,	0,},	//	D段前端AD输入状态
	{	PARA_D_DSAT	,PT_NC,	0,},	//	D段后端DA输出状态
	{	PARA_D_PA_VG_EN	,PT_NC,	0,},	//	D段功放栅压状态
	{	PARA_D_PA_VT	,PT_NC,	0,},	//	D段功放管电压显示
	{	PARA_D_Modulator_EN	,PT_NC,	0,},	//	D段调制器状态
	{	PARA_D_LNA_VT	,PT_NC,	0,},	//	D段下行低噪放LNA电压
	{	PARA_D_LNA1_ST	,PT_RO|PT_US,	0,},	//	上行LNA1状态
	{	PARA_D_LNA2_ST	,PT_RO|PT_US,	0,},	//	上行LNA2状态
	{	PARA_D_BUSY_TIME	,PT_RO|PT_SI,	0,},	//	D段上行时隙占用率
	{ 	PARA_D_PRI_ADD,  PT_DP_G_EX|PT_RO|PT_US, 4,}, // D段模块地址
	{	PARA_D_UL_POW_1B, 	/*PT_DP_G|*/PT_SI, 	0,},	//	D段上行输入总功率
	{	PARA_D_DL_POW_1B, 	PT_DP_G_EX|PT_RO|PT_SI, 	0,},	//	D段下行输入总功率
	{	PARA_D_DCH_REC_RF_ATT1,		PT_DP_G_EX|PT_US, 	0},	 // REC端的上行数控衰减量。即RF端的链路上行衰减量 RF 
	{	PARA_D_UCH_REC_RF_ATT1,		PT_DP_G_EX|PT_US, 	0},	 // REC端的上行数控衰减量。即RF端的链路上行衰减量 RF 
	{	PARA_FP1_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能1
	{	PARA_FP2_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能2
	{	PARA_FP3_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能3
	{	PARA_FP4_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能4
	{	PARA_FP5_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能5
	{	PARA_FP6_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能6
	{	PARA_FP7_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能7
	{	PARA_FP8_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能8
	{	PARA_FP9_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能9
	{	PARA_FP10_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能10
	{	PARA_FP11_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能11
	{	PARA_FP12_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能12
	{	PARA_FP13_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能13
	{	PARA_FP14_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能14
	{	PARA_FP15_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能15
	{	PARA_FP16_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	光口发送使能16
	{	PARA_FP1_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	光口在位状态1, 0-在位
	{	PARA_FP2_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	光口在位状态2, 0-在位
	{	PARA_FP3_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	光口在位状态3, 0-在位
	{	PARA_FP4_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	光口在位状态4, 0-在位
	{	PARA_FP5_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	光口在位状态5, 0-在位
	{	PARA_FP6_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	光口在位状态6, 0-在位
	{	PARA_FP7_ON_POS	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	0,},	//	光口在位状态7, 0-在位
	{	PARA_FP8_ON_POS	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	0,},	//	光口在位状态8, 0-在位
	{	PARA_FP9_ON_POS	,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	光口在位状态9, 0-在位
	{	PARA_FP10_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	光口在位状态10, 0-在位
	{	PARA_FP11_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	光口在位状态11, 0-在位
	{	PARA_FP12_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	光口在位状态12, 0-在位
	{	PARA_FP13_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	光口在位状态13, 0-在位
	{	PARA_FP14_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	光口在位状态14, 0-在位
	{	PARA_FP15_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	光口在位状态15, 0-在位
	{	PARA_FP16_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	光口在位状态16, 0-在位
	{	PARA_FP1_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口1信号丢失状态
	{	PARA_FP2_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口2信号丢失状态
	{	PARA_FP3_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口3信号丢失状态
	{	PARA_FP4_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口4信号丢失状态
	{	PARA_FP5_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口5信号丢失状态
	{	PARA_FP6_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口6信号丢失状态
	{	PARA_FP7_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口7信号丢失状态
	{	PARA_FP8_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口8信号丢失状态
	{	PARA_FP9_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口9信号丢失状态
	{	PARA_FP10_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口10信号丢失状态
	{	PARA_FP11_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口11信号丢失状态
	{	PARA_FP12_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口12信号丢失状态
	{	PARA_FP13_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口13信号丢失状态
	{	PARA_FP14_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口14信号丢失状态
	{	PARA_FP15_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口15信号丢失状态
	{	PARA_FP16_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口16信号丢失状态
	{	PARA_FP1_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口1帧丢失状态
	{	PARA_FP2_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口2帧丢失状态
	{	PARA_FP3_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口3帧丢失状态
	{	PARA_FP4_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口4帧丢失状态
	{	PARA_FP5_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口5帧丢失状态
	{	PARA_FP6_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口6帧丢失状态
	{	PARA_FP7_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口7帧丢失状态
	{	PARA_FP8_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口8帧丢失状态
	{	PARA_FP9_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口9帧丢失状态
	{	PARA_FP10_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口10帧丢失状态
	{	PARA_FP11_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口11帧丢失状态
	{	PARA_FP12_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口12帧丢失状态
	{	PARA_FP13_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口13帧丢失状态
	{	PARA_FP14_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口14帧丢失状态
	{	PARA_FP15_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口15帧丢失状态
	{	PARA_FP16_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	光口16帧丢失状态
	{	PARA_OPT_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	帧丢失状态
	{	PARA_SERDES1_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态1
	{	PARA_SERDES2_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态2
	{	PARA_SERDES3_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态3
	{	PARA_SERDES4_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态4
	{	PARA_SERDES5_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态5
	{	PARA_SERDES6_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态6
	{	PARA_SERDES7_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态7
	{	PARA_SERDES8_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态8
	{	PARA_SERDES9_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态9
	{	PARA_SERDES10_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态10
	{	PARA_SERDES11_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态11
	{	PARA_SERDES12_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态12
	{	PARA_SERDES13_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态13
	{	PARA_SERDES14_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态14
	{	PARA_SERDES15_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态15
	{	PARA_SERDES16_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDes芯片PLL状态16
	{	PARA_TOPO_CHG_ALM	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	环路状态告警
	{	PARA_BER_ALARM		,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	误码率偏高告警
	{	PARA_LOAD_FPGA_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	加载FPGA状态
	{	PARA_FPGA_CLK_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	FPGA本振状态
	{	PARA_INIT_CLK_ST	,PT_NC,	0,},	//	初始化时钟状态
	{	PARA_INIT_AD_ST		,PT_NC,	0,},	//	初始化AD状态
	{	PARA_INIT_FB_AD_ST	,PT_NC,	0,},	//	初始化反馈AD状态
	{	PARA_CLK_PLL_ST	,	PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	CLK PLL状态
	{	PARA_CLK_REF_ST	,	PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	CLK 参考状态
	{	PARA_RE_NODE_MODE,	PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	RE节点模式
	{	PARA_BOARD_TEMP,	PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	单板温度
	{	PARA_CLK_VCO_VT,	PT_NC,	0,},	//	时钟VCO电压
	{	PARA_PWR_9V0_VT,	PT_NC,	0,},	//	9V电源电压
	{	PARA_PWR_5V5_VT,	PT_NC,	0,},	//	5.5V电源电压
	{	PARA_PWR_3V6_VT,	PT_NC,	0,},	//	3.6V电源电压
	{	PARA_PWR_1V2_VT,	PT_NC,	0,},	//	1.2V电源电压
	{	PARA_PWR_2V5_VT,	PT_NC,	0,},	//	1.2V电源电压
	{	PARA_PRI_PROTOCAL_V	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	协议版本
	{	PARA_MODULE_HRI_ID,	PT_NC,	0,},	//	ID
	{	PARA_WORK_ERROR,	PT_NC,	0,},	// 系统工作状态，1-有故障
	{	PARA_TRAFFIC_END, 	PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	// 系统工作状态，1-有故障
	{	PARA_DELAY_MODE,	PT_AP_G|PT_BP_G|PT_US, 	1},		// 	延时模式: 0-手动, 1-自动
	{	PARA_TD_SYNC_ST,		PT_BP|PT_RO|PT_US, 		0},		// TD同步状态: 0-已同步，1-未同步
	{	PARA_TD_WORK_MODE, PT_BP|PT_US, 0 },		// [WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开, 每次上电后清零
	{	PARA_TD_T0_UD,		PT_BP_G_EX|PT_US, 	1},	// TD时隙0上下行标志:0-上行，1-下行
	{	PARA_TD_T1_UD,		PT_BP_G_EX|PT_US, 	1},	// TD时隙1上下行标志:0-上行，1-下行
	{	PARA_TD_T2_UD,		PT_BP_G_EX|PT_US, 	1},	// TD时隙2上下行标志:0-上行，1-下行
	{	PARA_TD_T3_UD,		PT_BP_G_EX|PT_US, 	1},	// TD时隙3上下行标志:0-上行，1-下行
	{	PARA_TD_T4_UD,		PT_BP_G_EX|PT_US, 	0},	// TD时隙4上下行标志:0-上行，1-下行
	{	PARA_TD_T5_UD,		PT_BP_G_EX|PT_US, 	0},	// TD时隙5上下行标志:0-上行，1-下行
	{	PARA_TD_T6_UD,		PT_BP_G_EX|PT_US, 	0},	// TD时隙6上下行标志:0-上行，1-下行
	{	PARA_POWERUP_ST,	PT_AP_G_EX|PT_SI},	// 	数字板上电状态,每次启动时置1
	{	PARA_LOW_POWER,	PT_AP|PT_BP|PT_CP|PT_DP|PT_SI,	0 },	//	低功耗模式:1-低功耗;	0-正常
	{	PARA_THR_PORT,		PT_NC,	PARAM_INIT_THR_PORT},	// 	透传端口选择0-485B, 1-RS232
	{	PARA_THR_BAUD,		PT_NC,	PARAM_INIT_THR_BAUD},	//	透传端口波特率 0-9600, 1-19200, 2-38400, 3-57600, 4-115200
	{	PARA_CTRL_BAUD,	PT_NC,	PARAM_INIT_CTRL_BAUD},	//	控制端口波特率 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
	{	PARA_WLAN_CONN_ST1,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN口状态1: 0-正常，1-异常
	{	PARA_WLAN_CONN_ST2,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN口状态2: 0-正常，1-异常
	{	PARA_WLAN_CONN_ST3,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN口状态3: 0-正常，1-异常
	{	PARA_WLAN_CONN_ST4,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN口状态4: 0-正常，1-异常
	{	PARA_WLAN_SPEED1,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN口速度1: 0：10M  1：100M  2：1000M
	{	PARA_WLAN_SPEED2,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},		// WLAN口速度1: 0：10M  1：100M  2：1000M
	{	PARA_WLAN_SPEED3,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},		// WLAN口速度1: 0：10M  1：100M  2：1000M
	{	PARA_WLAN_SPEED4,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},		// WLAN口速度1: 0：10M  1：100M  2：1000M
	{	PARA_GSM_BW_SEL,		PT_RO|PT_US,			0},		// 宽带版本GSM带宽选择: 0-6M, 1-20M, 2-24M, 3-25M, 其他无效
	{	PARA_HX_DET_UADDR,		PT_NC,		0x31 }, // 虹信DET模块上行地址, 高4位为B段, 低四位为A段
	{	PARA_HX_LNA_UADDR,		PT_NC,		0x31 }, // 虹信LNA模块上行地址, 高4位为B段, 低四位为A段
	{	PARA_HX_DET_DADDR,		PT_NC,		0x42 }, // 虹信DET模块下行地址, 高4位为B段, 低四位为A段
	{	PARA_HX_LNA_DADDR,		PT_NC,		0x42 }, // 虹信LNA模块下行地址, 高4位为B段, 低四位为A段
	{	PARA_FPS_AUTO_SCAN,	PT_AP_G|PT_US,		0 },			// 自动频点搜索功能使能:1-自动搜索和设置频点, 0-手动搜索
	{	PARA_FPS_SWITCH_THD,	PT_NC, 		0 },			// 自动频点搜索的BCCH功率切换门限
	{	PARA_FPS_MOSVC_SEL,	PT_AP_G|PT_US, 		0 },	// 频点搜索: 运营商选择: 0-中移动, 1-中联通, 2-中移动, 255-自动选择
	{	PARA_FPS_RFRANGE_SEL,	PT_AP_G|PT_US, 		0 },	// 频点搜索: 频宽选择(忽略,以模块制式为准): 0-全频段, 1-900MHz, 2-1800MHz
	{	PARA_FPS_BS_ID,		PT_AP_G|PT_RO|PT_US, 		0 },	// 频点搜索: 基站识别码
	{	PARA_FPS_CA_COUNT,		PT_AP_G|PT_RO|PT_US, 		0 },	// 频点搜索: 有效信道数
	{	PARA_FPS_BCCH_LK_ST,	PT_AP_G|PT_RO|PT_US, 		0 },	// 频点搜索: 锁定BCCH状态: 1-锁定, 0-失败
	{	PARA_FPS_MOSVC_LK_ST,	PT_AP_G|PT_RO|PT_US, 		0 },	// 频点搜索: 锁定运营商状态: 1-锁定, 0-失败
	{	PARA_FPS_RFRANGE_LK_ST,	PT_AP_G|PT_RO|PT_US, 		0 },	// 频点搜索: 锁定频带状态: 1-锁定, 0-失败
	{	PARA_FPS_BCCH_POW_M,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// 频点搜索: 主小区BCCH接收强度
	{	PARA_FPS_BCCH_POW_1,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// 频点搜索: 邻小区1BCCH接收强度
	{	PARA_FPS_BCCH_POW_2,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// 频点搜索: 邻小区2BCCH接收强度
	{	PARA_FPS_BCCH_POW_3,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// 频点搜索: 邻小区3BCCH接收强度
	{	PARA_FPS_BCCH_POW_4,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// 频点搜索: 邻小区4BCCH接收强度
	{	PARA_FPS_BCCH_POW_5,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// 频点搜索: 邻小区5BCCH接收强度
	{	PARA_FPS_BCCH_POW_6,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// 频点搜索: 邻小区6BCCH接收强度
	{	PARA_A_EXPA_WORK_EN,	PT_AP_G_EX|PT_US, 	0 },		// [WR]微功放: 射频信号开关
	{	PARA_A_EXPA_DL_ATT,		PT_AP_G_EX|PT_US, 	0 },		// [WR]微功放: 下行衰减值
	{	PARA_A_EXPA_TEMP,		PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 温度
	{	PARA_A_EXPA_DL_POW,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 下行输出功率电平
	{	PARA_A_EXPA_SWR,		PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 下行驻波比值
	{	PARA_A_EXPA_POWER_DN,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 电源掉电告警(3分钟概率判定)
	{	PARA_A_EXPA_POWER_ERR,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 电源故障告警(3分钟概率判定)
	{	PARA_A_EXPA_BATT_ERR,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 监控模块电池故障告警(3分钟概率判定)
	{	PARA_A_EXPA_POS_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 位置告警
	{	PARA_A_EXPA_DOOR_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 门禁告警
	{	PARA_A_EXPA_WROK_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 下行功放故障告警(3分钟概率判定)
	{	PARA_A_EXPA_EXT1_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 外部告警1
	{	PARA_A_EXPA_EXT2_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 外部告警2
	{	PARA_A_EXPA_EXT3_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]微功放: 外部告警3
	{	PARA_A_EXPA_MAX_GAIN,	PT_NC, 	0 },		// 微功放: 零衰减增益，即最大增益
	{	PARA_A_EXPA_GAIN_THD,	PT_NC, 	0 },		// 微功放: 增益门限，即允许工作的增益最大值
	{	PARA_A_EXPA_POW_THD,	PT_NC, 	0 },		// 微功放: 功放输出功率门限
	{	PARA_A_EXPA_POD_CMP,	PT_NC,	0 },		// 微功放: 检波管功率检测补偿值,1字节有符号数,最终功率为检波管功率加上补偿值
	{	PARA_MONITOR_VOL_OVER_THR, 				PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0},			 // 监控电压过门限
	{	PARA_MONITOR_VOL_OWE_THR,				PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0},			 // 监控电压欠门限
	{	PARA_DIGITAL_SINGNAL_ALARM,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // 数字信号异常告警
	{	PARA_HOST_DEVICE_LINK_SINGNAL_ALARM,    PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // 主从监控链路告警
	{	PARA_MONITOR_BATTERY_ALARM,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // 监控模块电池故障告警
	{	PARA_LOW_POWER_ALARM,    				PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 //// 电源掉电告警
	{	PARA_BATTERY_BREAKDOWN_ALARM,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 //// 电源故障告警
	{	PARA_POSITION_MOVE_ALARM,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0},			 // 位置告警
	{	PARA_A_INPUT_OVER_DPOW_THR_ALARM,    	PT_AP_G_EX|PT_US, 	0},			 // A下行输入过功率告警
	{	PARA_A_INPUT_OWE_DPOW_THR_ALARM,    	PT_AP_G_EX|PT_US, 	0},			 // A下行输入欠功率告警
	{	PARA_B_INPUT_OVER_DPOW_THR_ALARM,    	PT_BP_G_EX|PT_US, 	0},			 // B下行输入过功率告警
	{	PARA_B_INPUT_OWE_DPOW_THR_ALARM,    	PT_BP_G_EX|PT_US, 	0},			 // B下行输入欠功率告警
	{	PARA_C_INPUT_OVER_DPOW_THR_ALARM,    	PT_CP_G_EX|PT_US, 	0},			 // C下行输入过功率告警
	{	PARA_C_INPUT_OWE_DPOW_THR_ALARM,    	PT_CP_G_EX|PT_US, 	0},			 // C下行输入欠功率告警
	{	PARA_D_INPUT_OVER_DPOW_THR_ALARM,    	PT_DP_G_EX|PT_US, 	0},			 // D下行输入过功率告警
	{	PARA_D_INPUT_OWE_DPOW_THR_ALARM,    	PT_DP_G_EX|PT_US, 	0},			 // D下行输入欠功率告警
	{	PARA_TD_D_OVER_SLOT1_THR_ALARM,    		PT_BP_G_EX|PT_US, 	0}, 			 // TD下行输入导频过功率告警
	{	PARA_TD_D_OWE_SLOT1_THR_ALARM,    		PT_BP_G_EX|PT_US, 	0}, 			 // TD下行输入导频欠功率告警
	{	PARA_RE_DATA_LAN_ST1,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // TD下行输入导频欠功率告警
	{	PARA_RE_CASCADE_LAN_ST1,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // TD下行输入导频欠功率告警
	{	PARA_RE_DATA_LAN_SYS_ST1,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // TD下行输入导频欠功率告警
	{	PARA_RE_CASCADE_LAN_SYS_ST1,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // TD下行输入导频欠功率告警
	{	PARA_A_RF_POW_SWR,				PT_AP_G_EX|PT_US, 	0},	 //A段覆盖单元功放驻波比
	{	PARA_A_RF_OUT_POW_H_THR,		PT_AP_G_EX|PT_US, 	0},	 //A段覆盖单元输出过功率门限
	{	PARA_A_RF_OUT_POW_L_THR,		PT_AP_G_EX|PT_US, 	0},	 //A段覆盖单元输出欠功率门限
	{	PARA_B_RF_POW_SWR,				PT_BP_G_EX|PT_US, 	0},	 //B段覆盖单元功放驻波比
	{	PARA_B_RF_OUT_POW_H_THR,		PT_BP_G_EX|PT_US, 	0},	 //B段覆盖单元输出过功率门限 
	{	PARA_B_RF_OUT_POW_L_THR,		PT_BP_G_EX|PT_US, 	0},	 //B段覆盖单元输出欠功率门限
	{	PARA_C_RF_POW_SWR,				PT_CP_G_EX|PT_US, 	0},	 //C段覆盖单元功放驻波比
	{	PARA_C_RF_OUT_POW_H_THR,		PT_CP_G_EX|PT_US, 	0},	 //C段覆盖单元输出过功率门限 
	{	PARA_C_RF_OUT_POW_L_THR,		PT_CP_G_EX|PT_US, 	0},	 //C段覆盖单元输出欠功率门限
	{	PARA_D_RF_POW_SWR,				PT_DP_G_EX|PT_US, 	0},	 //D段覆盖单元功放驻波比
	{	PARA_D_RF_OUT_POW_H_THR,		PT_DP_G_EX|PT_US, 	0},	 //D段覆盖单元输出过功率门限 
	{	PARA_D_RF_OUT_POW_L_THR,		PT_DP_G_EX|PT_US, 	0},	 //D段覆盖单元输出欠功率门限
	{	PARA_PWR_3V3_1_VT  ,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 		// 3.3V电源电压
	{	PARA_PWR_3V3_2_VT  ,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 		//	3.3V电源电压
	{	PARA_PWR_1V8_VT  ,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			// 1.8V电源电压
	{	PARA_PWR_1V5_VT  ,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // 1.5V电源电压
	{	PARA_A_DL_RF_EN	,		PT_AP|PT_US,		1,},	// 	A段下行射频使能
	{	PARA_A_UL_RF_EN	,		PT_AP|PT_US,		1,},	// 	A段上行射频使能
	{	PARA_B_DL_RF_EN	,		PT_BP|PT_US,		1,},	// 	B段下行射频使能
	{	PARA_B_UL_RF_EN	,		PT_BP|PT_US,		1,},	// 	B段上行射频使能
	{	PARA_C_DL_RF_EN	,		PT_CP|PT_US,		1,},	// 	C段下行射频使能
	{	PARA_C_UL_RF_EN	,		PT_CP|PT_US,		1,},	// 	C段上行射频使能
	{	PARA_D_DL_RF_EN	,		PT_DP|PT_US,		1,},	// 	D段下行射频使能
	{	PARA_D_UL_RF_EN	,		PT_DP|PT_US,		1,},	// 	D段上行射频使能
	{	PARA_METER_OFFSET  ,    		PT_AP_G_EX|PT_US, 	0}, 			 //	仪器偏差值设置
	{	PARA_METER_OFFSET_B  ,    		PT_BP_G_EX|PT_US, 	0}, 			 //	仪器偏差值设置
	{	PARA_METER_OFFSET_C  ,    		PT_CP_G_EX|PT_US, 	0}, 			 //	仪器偏差值设置
	{	PARA_METER_OFFSET_D  ,    		PT_DP_G_EX|PT_US, 	0}, 			 //	仪器偏差值设置
	{	PARA_C_TD_TYPE_SELECT  ,    		PT_CP|PT_US, 	0},//686	// TD下行输入导频过功率告警					
	{	PARA_C_TD_NORMAL_CP	  ,    		PT_CP|PT_US, 	0},//716	//	TDD特殊时隙 NORMAL_CP
	{	PARA_C_TD_EXTENDED_CP	  ,    		PT_CP_G_EX|PT_US, 	0},//717	//	TDD特殊时隙 NORMAL_CP
	{	PARA_C_TD_SYNC_ST  ,    		PT_CP|PT_US, 	0},	//687  	//TD同步状态:	0-已同步，1-未同步			
	{	PARA_C_TD_WORK_MODE  ,    		PT_CP|PT_US, 	0},	//688  	//[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零			
	{	PARA_C_TD_DL_OVER_SLOT1_THR_ALARM  ,    		PT_CP_G_EX|PT_US, 	0},	//689  // TD下行输入导频过功率告警					
	{	PARA_C_TD_DL_OWE_SLOT1_THR_ALARM  ,    		PT_CP_G_EX|PT_US, 	0},	//690	 // TD下行输入导频欠功率告警					
	{	PARA_D_TD_TYPE_SELECT  ,    		PT_DP|PT_US, 	0},	//691  // TD下行输入导频过功率告警					
	{	PARA_D_TD_NORMAL_CP	  ,    		PT_DP|PT_US, 	0},//718	//	TDD特殊时隙 NORMAL_CP
	{	PARA_D_TD_EXTENDED_CP	  ,    		PT_DP_G_EX|PT_US, 	0},//719	//	TDD特殊时隙 NORMAL_CP
	{	PARA_D_TD_SYNC_ST  ,    		PT_DP|PT_US, 	0},	//692  	//TD同步状态:	0-已同步，1-未同步			
	{	PARA_D_TD_WORK_MODE  ,    		PT_DP|PT_US, 	0},	//693  	//[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零			
	{	PARA_D_TD_DL_OVER_SLOT1_THR_ALARM  ,    		PT_DP_G_EX|PT_US, 	0},	//694  	// TD下行输入导频过功率告警					
	{	PARA_D_TD_DL_OWE_SLOT1_THR_ALARM  ,    		PT_DP_G_EX|PT_US, 	0},	//695	 // TD下行输入导频欠功率告警					
	{	PARA_C_TD_T0_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//696  	//TD时隙0上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T1_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//697  	//TD时隙1上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T2_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//698  	//TD时隙2上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T3_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//699  	//TD时隙3上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T4_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//700  	//TD时隙4上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T5_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//701  	//TD时隙5上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T6_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//702  	//TD时隙6上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T7_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//703  	//TD时隙7上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T8_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//704  	//TD时隙8上下行标志:0-上行，1-下行			
	{	PARA_C_TD_T9_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//705  	//TD时隙9上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T0_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//706  	//TD时隙0上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T1_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//707  	//TD时隙1上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T2_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//708  	//TD时隙2上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T3_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//709  	//TD时隙3上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T4_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//710  	//TD时隙4上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T5_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//711  	//TD时隙5上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T6_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//712  	//TD时隙6上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T7_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//713  	//TD时隙7上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T8_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//714  	//TD时隙8上下行标志:0-上行，1-下行			
	{	PARA_D_TD_T9_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//715  	//TD时隙9上下行标志:0-上行，1-下行
	{	PARA_NOISE_TEST_EN	  ,    	PT_AP_G_EX|PT_US, 	0},	//	噪声测试开关	
	{	PARA_FREQ_MODIF_VAL_D	  ,    	PT_DP_G_EX|PT_US, 	0},	//	频点修正	
	{	PARA_FREQ_MODIF_VAL_B	  ,    	PT_BP_G_EX|PT_US, 	0},	//	频点修正	
	{	PARA_FREQ_MODIF_VAL_A	  ,    	PT_AP_G_EX|PT_US, 	0},	//	频点修正	
	{	PARA_B_TDS_2TH_BREAKING_POINT_SET	  ,    	PT_BP|PT_US, 	0},	//	TDS 第二转换点设置	
	{	PARA_DELAY_MODE_A	,PT_AP|PT_US, 	0},		//0x8660	// 	延时模式: 0-手动, 1-自动		
	{	PARA_DELAY_MODE_B	,PT_BP|PT_US, 	0},		//0x8660	// 	延时模式: 0-手动, 1-自动					
	{	PARA_DELAY_MODE_C	,PT_CP|PT_US, 	0},		//0x8660	// 	延时模式: 0-手动, 1-自动					
	{	PARA_DELAY_MODE_D	,PT_DP|PT_US, 	0},		//0x8660	// 	延时模式: 0-手动, 1-自动					
	{	PARA_REE_CIRCUIT_ALARM	,	   PT_AP|PT_US,  0},					//	0x803f		// 扩展单元电路故障告警16
	{	PARA_REE_WLAN_CONN_ST			,	   PT_AP|PT_US,  0},			//	0x87d0	//	316 //	WLAN口状态1:	0-正常，1-异常
	{	PARA_DL_POWER_MAX ,PT_NC, 0}, 	//求下行模块功率最大值			
	{	PARA_SLOT_TIME_EN_B	,PT_BP,	0}, 	//时隙配比自动检测开关				
	{	PARA_SLOT_TIME_DISTRI_B ,PT_BP, 0}, 	//时隙配比分布				
	{	PARA_VERSION_FLAG ,PT_NC, 0}, 	//版本识别		
	{	PARA_SLOT_TIME_EN_C ,PT_BP, 0}, 	//时隙配比自动检测开关				
	{	PARA_SLOT_TIME_DISTRI_C ,PT_BP, 0}, 	//时隙配比分布				
	{	PARA_A_1197_LOCK_ST ,PT_AP, 0}, //A段1197锁定状态		
	{	PARA_A_IF_ST ,PT_AP, 0},	//A段中频频率,0/1---300M/500M				
	{	PARA_ENCRYPTION_ST ,PT_AP, 0},	//加密状态,0/1---不加密/加密				
	{	PARA_PWR_1V6_VT ,PT_AP, 0},         //     //1.6v电源		
	{	PARA_A_90_VALUE ,PT_AP, 0xff}, //A段9363 90寄存器的值
	{	PARA_A_91_VALUE ,PT_AP, 0xff}, //A段9363 91寄存器的值
	{	PARA_A_94_VALUE ,PT_AP, 0xff}, //A段9363 94寄存器的值
	{	PARA_A_95_VALUE ,PT_AP, 0xff}, //A段9363 95寄存器的值
	{	PARA_B_90_VALUE ,PT_AP, 0xff}, //B段9363 90寄存器的值
	{	PARA_B_91_VALUE ,PT_AP, 0xff}, //B段9363 91寄存器的值
	{	PARA_B_94_VALUE ,PT_AP, 0xff}, //B段9363 94寄存器的值
	{	PARA_B_95_VALUE ,PT_AP, 0xff}, //B段9363 95寄存器的值
	{	PARA_C_90_VALUE ,PT_AP, 0xff}, //C段9363 90寄存器的值
	{	PARA_C_91_VALUE ,PT_AP, 0xff}, //C段9363 91寄存器的值
	{	PARA_C_94_VALUE ,PT_AP, 0xff}, //C段9363 94寄存器的值
	{	PARA_C_95_VALUE ,PT_AP, 0xff}, //C段9363 95寄存器的值
	{	PARA_D_90_VALUE ,PT_AP, 0xff}, //D段9363 90寄存器的值
	{	PARA_D_91_VALUE ,PT_AP, 0xff}, //D段9363 91寄存器的值
	{	PARA_D_94_VALUE ,PT_AP, 0xff}, //D段9363 94寄存器的值
	{	PARA_D_95_VALUE ,PT_AP, 0xff}, //D段9363 95寄存器的值
	{	PARA_PASSTHROUGH_EN ,PT_AP, 0x00}, //透传使能开关
	{	PARA_A_DL_POW_ADJ ,PT_AP, 0}, 
	{	PARA_B_DL_POW_ADJ ,PT_BP, 0}, 
	{	PARA_C_DL_POW_ADJ ,PT_CP, 0}, 
	{	PARA_D_DL_POW_ADJ ,PT_DP, 0}, 
	{	PARA_SoftwareLoadTimes ,PT_NC, 0}, 
	{	PARA_A_LNA_EN_ST	,PT_AP, 0}, 			//9363初始化配置，0为a1，01为a2
		

};


_T_PARAM_2B sys_param_2b[]={
	{	PARA_A_DL_CHANNEL1	, PT_AP|PT_US, 	45,}, 	//	A段下行信道号1
	{	PARA_A_DL_CHANNEL2	, PT_AP|PT_US, 	45,},	//	A段下行信道号2
	{	PARA_A_DL_CHANNEL3	, PT_AP|PT_US, 	45,},	//	A段下行信道号3
	{	PARA_A_DL_CHANNEL4	, PT_AP|PT_US, 	45,},	//	A段下行信道号4
	{	PARA_A_DL_CHANNEL5	, PT_AP|PT_US, 	45,},	//	A段下行信道号5
	{	PARA_A_DL_CHANNEL6	, PT_AP|PT_US, 	45,},	//	A段下行信道号6
	{	PARA_A_DL_CHANNEL7	, PT_AP|PT_US, 	45,},	//	A段下行信道号7
	{	PARA_A_DL_CHANNEL8	, PT_AP|PT_US, 	45,},	//	A段下行信道号8
	{	PARA_A_DL_CHANNEL9	, PT_AP|PT_US, 	45,},	//	A段下行信道号9
	{	PARA_A_DL_CHANNEL10	, PT_AP|PT_US, 	45,},	//	A段下行信道号10
	{	PARA_A_DL_CHANNEL11	, PT_AP|PT_US, 	45,},	//	A段下行信道号11
	{	PARA_A_DL_CHANNEL12	, PT_AP|PT_US, 	45,},	//	A段下行信道号12
	{	PARA_A_DL_CHANNEL13	, PT_AP|PT_US, 	45,},	//	A段下行信道号13
	{	PARA_A_DL_CHANNEL14	, PT_AP|PT_US, 	45,},	//	A段下行信道号14
	{	PARA_A_DL_CHANNEL15	, PT_AP|PT_US, 	45,},	//	A段下行信道号15
	{	PARA_A_DL_CHANNEL16	, PT_AP|PT_US, 	45,},	//	A段下行信道号16
	{	PARA_A_UL_CHANNEL1		, PT_US, 	45,}, 	//	A段上行信道号1
	{	PARA_A_UL_CHANNEL2		, PT_US, 	45,},	//	A段上行信道号2
	{	PARA_A_UL_CHANNEL3		, PT_US, 	45,},	//	A段上行信道号3
	{	PARA_A_UL_CHANNEL4		, PT_US, 	45,},	//	A段上行信道号4
	{	PARA_A_UL_CHANNEL5		, PT_US, 	45,},	//	A段上行信道号5
	{	PARA_A_UL_CHANNEL6		, PT_US, 	45,},	//	A段上行信道号6
	{	PARA_A_UL_CHANNEL7		, PT_US, 	45,},	//	A段上行信道号7
	{	PARA_A_UL_CHANNEL8		, PT_US, 	45,},	//	A段上行信道号8
	{	PARA_A_UL_CHANNEL9		, PT_US, 	45,},	//	A段上行信道号9
	{	PARA_A_UL_CHANNEL10	, PT_US, 	45,},	//	A段上行信道号10
	{	PARA_A_UL_CHANNEL11	, PT_US, 	45,},	//	A段上行信道号11
	{	PARA_A_UL_CHANNEL12	, PT_US, 	45,},	//	A段上行信道号12
	{	PARA_A_UL_CHANNEL13	, PT_US, 	45,},	//	A段上行信道号13
	{	PARA_A_UL_CHANNEL14	, PT_US, 	45,},	//	A段上行信道号14
	{	PARA_A_UL_CHANNEL15	, PT_US, 	45,},	//	A段上行信道号15
	{	PARA_A_UL_CHANNEL16	, PT_US, 	45,},	//	A段上行信道号16
	{	PARA_A_DCH_MAX_POW1	, PT_AP_G_EX|PT_SI, 	27,},	//	A段下行通道最大输出功率1
	{	PARA_A_DCH_MAX_POW2	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率2
	{	PARA_A_DCH_MAX_POW3	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率3
	{	PARA_A_DCH_MAX_POW4	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率4
	{	PARA_A_DCH_MAX_POW5	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率5
	{	PARA_A_DCH_MAX_POW6	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率6
	{	PARA_A_DCH_MAX_POW7	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率7
	{	PARA_A_DCH_MAX_POW8	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率8
	{	PARA_A_DCH_MAX_POW9	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率9
	{	PARA_A_DCH_MAX_POW10	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率10
	{	PARA_A_DCH_MAX_POW11	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率11
	{	PARA_A_DCH_MAX_POW12	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率12
	{	PARA_A_DCH_MAX_POW13	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率13
	{	PARA_A_DCH_MAX_POW14	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率14
	{	PARA_A_DCH_MAX_POW15	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率15
	{	PARA_A_DCH_MAX_POW16	, PT_AP_G_EX|PT_NC, 	27,},	//	A段下行通道最大输出功率16
	{	PARA_A_UCH_MAX_POW1	, PT_AP|PT_SI, 		-10,},	//	A段上行通道最大输入功率1
	{	PARA_A_UCH_MAX_POW2	, PT_AP|PT_SI, 	-10,},	//	A段上行通道最大输入功率2
	{	PARA_A_UCH_MAX_POW3	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率3
	{	PARA_A_UCH_MAX_POW4	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率4
	{	PARA_A_UCH_MAX_POW5	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率5
	{	PARA_A_UCH_MAX_POW6	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率6
	{	PARA_A_UCH_MAX_POW7	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率7
	{	PARA_A_UCH_MAX_POW8	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率8
	{	PARA_A_UCH_MAX_POW9	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率9
	{	PARA_A_UCH_MAX_POW10	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率10
	{	PARA_A_UCH_MAX_POW11	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率11
	{	PARA_A_UCH_MAX_POW12	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率12
	{	PARA_A_UCH_MAX_POW13	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率13
	{	PARA_A_UCH_MAX_POW14	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率14
	{	PARA_A_UCH_MAX_POW15	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率15
	{	PARA_A_UCH_MAX_POW16	, PT_AP_G_EX|PT_NC, 	-10,},	//	A段上行通道最大输入功率16
	{	PARA_A_DCH_POW1	, PT_NC, 	0,},	//	A段选频通道下行功率1
	{	PARA_A_DCH_POW2	, PT_NC, 	0,},	//	A段选频通道下行功率2
	{	PARA_A_DCH_POW3	, PT_NC, 	0,},	//	A段选频通道下行功率3
	{	PARA_A_DCH_POW4	, PT_NC, 	0,},	//	A段选频通道下行功率4
	{	PARA_A_DCH_POW5	, PT_NC, 	0,},	//	A段选频通道下行功率5
	{	PARA_A_DCH_POW6	, PT_NC, 	0,},	//	A段选频通道下行功率6
	{	PARA_A_DCH_POW7	, PT_NC, 	0,},	//	A段选频通道下行功率7
	{	PARA_A_DCH_POW8	, PT_NC, 	0,},	//	A段选频通道下行功率8
	{	PARA_A_DCH_POW9	, PT_NC, 	0,},	//	A段选频通道下行功率9
	{	PARA_A_DCH_POW10	, PT_NC, 	0,},	//	A段选频通道下行功率10
	{	PARA_A_DCH_POW11	, PT_NC, 	0,},	//	A段选频通道下行功率11
	{	PARA_A_DCH_POW12	, PT_NC, 	0,},	//	A段选频通道下行功率12
	{	PARA_A_DCH_POW13	, PT_NC, 	0,},	//	A段选频通道下行功率13
	{	PARA_A_DCH_POW14	, PT_NC, 	0,},	//	A段选频通道下行功率14
	{	PARA_A_DCH_POW15	, PT_NC, 	0,},	//	A段选频通道下行功率15
	{	PARA_A_DCH_POW16	, PT_NC, 	0,},	//	A段选频通道下行功率16
	{	PARA_A_UCH_POW1	, PT_NC, 	0,},	//	A段选频通道上行功率1
	{	PARA_A_UCH_POW2	, PT_NC, 	0,},	//	A段选频通道上行功率2
	{	PARA_A_UCH_POW3	, PT_NC, 	0,},	//	A段选频通道上行功率3
	{	PARA_A_UCH_POW4	, PT_NC, 	0,},	//	A段选频通道上行功率4
	{	PARA_A_UCH_POW5	, PT_NC, 	0,},	//	A段选频通道上行功率5
	{	PARA_A_UCH_POW6	, PT_NC, 	0,},	//	A段选频通道上行功率6
	{	PARA_A_UCH_POW7	, PT_NC, 	0,},	//	A段选频通道上行功率7
	{	PARA_A_UCH_POW8	, PT_NC, 	0,},	//	A段选频通道上行功率8
	{	PARA_A_UCH_POW9	, PT_NC, 	0,},	//	A段选频通道上行功率9
	{	PARA_A_UCH_POW10	, PT_NC, 	0,},	//	A段选频通道上行功率10
	{	PARA_A_UCH_POW11	, PT_NC, 	0,},	//	A段选频通道上行功率11
	{	PARA_A_UCH_POW12	, PT_NC, 	0,},	//	A段选频通道上行功率12
	{	PARA_A_UCH_POW13	, PT_NC, 	0,},	//	A段选频通道上行功率13
	{	PARA_A_UCH_POW14	, PT_NC, 	0,},	//	A段选频通道上行功率14
	{	PARA_A_UCH_POW15	, PT_NC, 	0,},	//	A段选频通道上行功率15
	{	PARA_A_UCH_POW16	, PT_NC, 	0,},	//	A段选频通道上行功率16
	{	PARA_A_UDPX_IN_GAIN	, PT_AP_G_EX|PT_NC, 	0,},	//	A段输入双工器增益
	{	PARA_A_UDPX_OUT_GAIN, PT_AP_G_EX|PT_NC, 	0,},	//	A段输出双工器增益
	{	PARA_A_DL_TOTAL_POW	, PT_AP|PT_RO|PT_SI, 	0,},	//	A段下行总功率
	{	PARA_A_UL_TOTAL_POW	, PT_AP|PT_RO|PT_SI, 	0,},	//	A段上行总功率
	{	PARA_A_REC_DPX_IG	, PT_NC, 	0,},	//	REC的A段输入双工器衰减，用来进行增益计算，只读,	
	{	PARA_A_REC_DPX_OG	, PT_NC, 	0,},	//	REC的A段输出双工器衰减，用来进行增益计算，只读,	
	{	PARA_B_DL_CHANNEL1		, PT_BP|PT_US,	10688,},	//	B段下行信道号1
	{	PARA_B_DL_CHANNEL2		, PT_BP|PT_US,	10688,},	//	B段下行信道号2
	{	PARA_B_DL_CHANNEL3		, PT_BP|PT_US,	10688,},	//	B段下行信道号3
	{	PARA_B_DL_CHANNEL4		, PT_BP|PT_US,	10688,},	//	B段下行信道号4
	{	PARA_B_DL_CHANNEL5		, PT_BP|PT_US,	10688,},	//	B段下行信道号5
	{	PARA_B_DL_CHANNEL6		, PT_BP|PT_US,	10688,},	//	B段下行信道号6
	{	PARA_B_DL_CHANNEL7		, PT_BP|PT_US,	10688,},	//	B段下行信道号7
	{	PARA_B_DL_CHANNEL8		, PT_BP|PT_US,	10688,},	//	B段下行信道号8
	{	PARA_B_DL_CHANNEL9		, PT_BP|PT_US,	10688,},	//	B段下行信道号9
	{	PARA_B_DL_CHANNEL10 , PT_BP|PT_US,	10688,},	//	B段下行信道号10
	{	PARA_B_DL_CHANNEL11 , PT_BP|PT_US,	10688,},	//	B段下行信道号11
	{	PARA_B_DL_CHANNEL12 , PT_BP|PT_US,	10688,},	//	B段下行信道号12
	{	PARA_B_DL_CHANNEL13 , PT_BP|PT_US,	10688,},	//	B段下行信道号13
	{	PARA_B_DL_CHANNEL14 , PT_BP|PT_US,	10688,},	//	B段下行信道号14
	{	PARA_B_DL_CHANNEL15 , PT_BP|PT_US,	10688,},	//	B段下行信道号15
	{	PARA_B_DL_CHANNEL16 , PT_BP|PT_US,	10688,},	//	B段下行信道号16
	{	PARA_B_UL_CHANNEL1	, PT_US,	10688,},	//	B段上行信道号1
	{	PARA_B_UL_CHANNEL2	, PT_US,	10688,},	//	B段上行信道号2
	{	PARA_B_UL_CHANNEL3	, PT_US,	10688,},	//	B段上行信道号3
	{	PARA_B_UL_CHANNEL4	, PT_US,	10688,},	//	B段上行信道号4
	{	PARA_B_UL_CHANNEL5	, PT_US,	10688,},	//	B段上行信道号5
	{	PARA_B_UL_CHANNEL6	, PT_US,	10688,},	//	B段上行信道号6
	{	PARA_B_UL_CHANNEL7	, PT_US,	10688,},	//	B段上行信道号7
	{	PARA_B_UL_CHANNEL8	, PT_US,	10688,},	//	B段上行信道号8
	{	PARA_B_UL_CHANNEL9	, PT_US,	10688,},	//	B段上行信道号9
	{	PARA_B_UL_CHANNEL10 , PT_US,	10688,},	//	B段上行信道号10
	{	PARA_B_UL_CHANNEL11 , PT_US,	10688,},	//	B段上行信道号11
	{	PARA_B_UL_CHANNEL12 , PT_US,	10688,},	//	B段上行信道号12
	{	PARA_B_UL_CHANNEL13 , PT_US,	10688,},	//	B段上行信道号13
	{	PARA_B_UL_CHANNEL14 , PT_US,	10688,},	//	B段上行信道号14
	{	PARA_B_UL_CHANNEL15 , PT_US,	10688,},	//	B段上行信道号15
	{	PARA_B_UL_CHANNEL16 , PT_US,	10688,},	//	B段上行信道号16
	{	PARA_B_DCH_MAX_POW1	, PT_BP_G_EX|PT_SI, 		27,},	//	B段下行通道最大输出功率1
	{	PARA_B_DCH_MAX_POW2	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率2
	{	PARA_B_DCH_MAX_POW3	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率3
	{	PARA_B_DCH_MAX_POW4	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率4
	{	PARA_B_DCH_MAX_POW5	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率5
	{	PARA_B_DCH_MAX_POW6	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率6
	{	PARA_B_DCH_MAX_POW7	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率7
	{	PARA_B_DCH_MAX_POW8	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率8
	{	PARA_B_DCH_MAX_POW9	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率9
	{	PARA_B_DCH_MAX_POW10	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率10
	{	PARA_B_DCH_MAX_POW11	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率11
	{	PARA_B_DCH_MAX_POW12	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率12
	{	PARA_B_DCH_MAX_POW13	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率13
	{	PARA_B_DCH_MAX_POW14	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率14
	{	PARA_B_DCH_MAX_POW15	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率15
	{	PARA_B_DCH_MAX_POW16	, PT_BP_G_EX|PT_NC, 	27,},	//	B段下行通道最大输出功率16
	{	PARA_B_UCH_MAX_POW1		, PT_BP|PT_SI, 	-10,},	//	B段上行通道最大输入功率1
	{	PARA_B_UCH_MAX_POW2		, PT_BP|PT_SI, 	-10,},	//	B段上行通道最大输入功率2
	{	PARA_B_UCH_MAX_POW3		, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率3
	{	PARA_B_UCH_MAX_POW4		, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率4
	{	PARA_B_UCH_MAX_POW5		, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率5
	{	PARA_B_UCH_MAX_POW6		, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率6
	{	PARA_B_UCH_MAX_POW7		, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率7
	{	PARA_B_UCH_MAX_POW8		, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率8
	{	PARA_B_UCH_MAX_POW9		, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率9
	{	PARA_B_UCH_MAX_POW10	, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率10
	{	PARA_B_UCH_MAX_POW11	, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率11
	{	PARA_B_UCH_MAX_POW12	, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率12
	{	PARA_B_UCH_MAX_POW13	, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率13
	{	PARA_B_UCH_MAX_POW14	, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率14
	{	PARA_B_UCH_MAX_POW15	, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率15
	{	PARA_B_UCH_MAX_POW16	, PT_BP_G_EX|PT_NC, 	27,},	//	B段上行通道最大输入功率16
	{	PARA_B_DCH_POW1	, PT_NC, 	0,},	//	B段选频通道下行功率1
	{	PARA_B_DCH_POW2	, PT_NC, 	0,},	//	B段选频通道下行功率2
	{	PARA_B_DCH_POW3	, PT_NC, 	0,},	//	B段选频通道下行功率3
	{	PARA_B_DCH_POW4	, PT_NC, 	0,},	//	B段选频通道下行功率4
	{	PARA_B_DCH_POW5	, PT_NC, 	0,},	//	B段选频通道下行功率5
	{	PARA_B_DCH_POW6	, PT_NC, 	0,},	//	B段选频通道下行功率6
	{	PARA_B_DCH_POW7	, PT_NC, 	0,},	//	B段选频通道下行功率7
	{	PARA_B_DCH_POW8	, PT_NC, 	0,},	//	B段选频通道下行功率8
	{	PARA_B_DCH_POW9	, PT_NC, 	0,},	//	B段选频通道下行功率9
	{	PARA_B_DCH_POW10	, PT_NC, 	0,},	//	B段选频通道下行功率10
	{	PARA_B_DCH_POW11	, PT_NC, 	0,},	//	B段选频通道下行功率11
	{	PARA_B_DCH_POW12	, PT_NC, 	0,},	//	B段选频通道下行功率12
	{	PARA_B_DCH_POW13	, PT_NC, 	0,},	//	B段选频通道下行功率13
	{	PARA_B_DCH_POW14	, PT_NC, 	0,},	//	B段选频通道下行功率14
	{	PARA_B_DCH_POW15	, PT_NC, 	0,},	//	B段选频通道下行功率15
	{	PARA_B_DCH_POW16	, PT_NC, 	0,},	//	B段选频通道下行功率16
	{	PARA_B_UCH_POW1	, PT_NC, 	0,},	//	B段选频通道上行功率1
	{	PARA_B_UCH_POW2	, PT_NC, 	0,},	//	B段选频通道上行功率2
	{	PARA_B_UCH_POW3	, PT_NC, 	0,},	//	B段选频通道上行功率3
	{	PARA_B_UCH_POW4	, PT_NC, 	0,},	//	B段选频通道上行功率4
	{	PARA_B_UCH_POW5	, PT_NC, 	0,},	//	B段选频通道上行功率5
	{	PARA_B_UCH_POW6	, PT_NC, 	0,},	//	B段选频通道上行功率6
	{	PARA_B_UCH_POW7	, PT_NC, 	0,},	//	B段选频通道上行功率7
	{	PARA_B_UCH_POW8	, PT_NC, 	0,},	//	B段选频通道上行功率8
	{	PARA_B_UCH_POW9	, PT_NC, 	0,},	//	B段选频通道上行功率9
	{	PARA_B_UCH_POW10	, PT_NC, 	0,},	//	B段选频通道上行功率10
	{	PARA_B_UCH_POW11	, PT_NC, 	0,},	//	B段选频通道上行功率11
	{	PARA_B_UCH_POW12	, PT_NC, 	0,},	//	B段选频通道上行功率12
	{	PARA_B_UCH_POW13	, PT_NC, 	0,},	//	B段选频通道上行功率13
	{	PARA_B_UCH_POW14	, PT_NC, 	0,},	//	B段选频通道上行功率14
	{	PARA_B_UCH_POW15	, PT_NC, 	0,},	//	B段选频通道上行功率15
	{	PARA_B_UCH_POW16	, PT_NC, 	0,},	//	B段选频通道上行功率16
	{	PARA_B_UDPX_IN_GAIN	, PT_BP_G_EX|PT_NC, 	0,},	//	B段输入双工器增益
	{	PARA_B_UDPX_OUT_GAIN, PT_BP_G_EX|PT_NC, 	0,},	//	B段输出双工器增益
	{	PARA_B_DL_TOTAL_POW	, PT_BP|PT_RO|PT_SI, 	0,},	//	B段下行输出总功率/*PT_BP_EX*/
	{	PARA_B_UL_TOTAL_POW	, PT_BP|PT_RO|PT_SI, 	0,},	//	B段上行输入总功率/*PT_BP_EX*/
	{	PARA_B_REC_DPX_IG	, PT_NC, 	0,},	//	REC的B段输入双工器衰减，用来进行增益计算，只读,	
	{	PARA_B_REC_DPX_OG	, PT_NC, 	0,},	//	REC的B段输出双工器衰减，用来进行增益计算，只读,	
	{ 	PARA_C_DL_CHANNEL1 , PT_CP|PT_US,  39100,},  // C段下行信道号1
	{ 	PARA_C_DL_CHANNEL2 , PT_CP|PT_US,  39100,},	// C段下行信道号2
	{ 	PARA_C_DL_CHANNEL3 , PT_CP|PT_US,  39210,},	// C段下行信道号3
	{ 	PARA_C_DL_CHANNEL4 , PT_CP|PT_US,  39210,},	// C段下行信道号4
	{ 	PARA_C_DL_CHANNEL5 , PT_CP|PT_US,  39210,},	// C段下行信道号5
	{ 	PARA_C_DL_CHANNEL6 , PT_CP|PT_US,  39210,},	// C段下行信道号6
	{ 	PARA_C_DL_CHANNEL7 , PT_CP|PT_US,  39210,},	// C段下行信道号7
	{ 	PARA_C_DL_CHANNEL8 , PT_CP|PT_US,  39210,},	// C段下行信道号8
	{ 	PARA_C_DL_CHANNEL9 , PT_CP|PT_US,  39210,},	// C段下行信道号9
	{ 	PARA_C_DL_CHANNEL10 , PT_CP|PT_US,  39210,},  // C段下行信道号10
	{	PARA_C_UL_CHANNEL1		, PT_US, 	39210,}, 	//	C段上行信道号1
	{	PARA_C_UL_CHANNEL2		, PT_US, 	39210,},	//	C段上行信道号2
	{	PARA_C_UL_CHANNEL3		, PT_US, 	39210,},	//	C段上行信道号3
	{	PARA_C_UL_CHANNEL4		, PT_US, 	39210,},	//	C段上行信道号4
	{	PARA_C_UL_CHANNEL5		, PT_US, 	39210,},	//	C段上行信道号5
	{	PARA_C_UL_CHANNEL6		, PT_US, 	39210,},	//	C段上行信道号6
	{	PARA_C_UL_CHANNEL7		, PT_US, 	39210,},	//	C段上行信道号7
	{	PARA_C_UL_CHANNEL8		, PT_US, 	39210,},	//	C段上行信道号8
	{	PARA_C_UL_CHANNEL9		, PT_US, 	39210,},	//	C段上行信道号9
	{	PARA_C_UL_CHANNEL10		, PT_US, 	39210,},	//	C段上行信道号10
	{	PARA_C_DCH_MAX_POW1	, PT_CP_G_EX|PT_SI, 		27,},	//	C段下行通道最大输出功率1
	{	PARA_C_DCH_MAX_POW2	, PT_CP_G_EX|PT_SI, 		27,},	//	C段下行通道最大输出功率2
	{	PARA_C_DCH_MAX_POW3	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率3
	{	PARA_C_DCH_MAX_POW4	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率4
	{	PARA_C_DCH_MAX_POW5	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率5
	{	PARA_C_DCH_MAX_POW6	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率6
	{	PARA_C_DCH_MAX_POW7	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率7
	{	PARA_C_DCH_MAX_POW8	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率8
	{	PARA_C_DCH_MAX_POW9	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率9
	{	PARA_C_DCH_MAX_POW10	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率10
	{	PARA_C_DCH_MAX_POW11	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率11
	{	PARA_C_DCH_MAX_POW12	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率12
	{	PARA_C_DCH_MAX_POW13	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率13
	{	PARA_C_DCH_MAX_POW14	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率14
	{	PARA_C_DCH_MAX_POW15	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率15
	{	PARA_C_DCH_MAX_POW16	, PT_CP_G_EX|PT_NC, 	27,},	//	C段下行通道最大输出功率16
	{	PARA_C_UCH_MAX_POW1	, PT_CP|PT_SI, 		-5,},	//	C段上行通道最大输入功率1
	{	PARA_C_UCH_MAX_POW2	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率2
	{	PARA_C_UCH_MAX_POW3	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率3
	{	PARA_C_UCH_MAX_POW4	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率4
	{	PARA_C_UCH_MAX_POW5	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率5
	{	PARA_C_UCH_MAX_POW6	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率6
	{	PARA_C_UCH_MAX_POW7	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率7
	{	PARA_C_UCH_MAX_POW8	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率8
	{	PARA_C_UCH_MAX_POW9	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率9
	{	PARA_C_UCH_MAX_POW10	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率10
	{	PARA_C_UCH_MAX_POW11	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率11
	{	PARA_C_UCH_MAX_POW12	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率12
	{	PARA_C_UCH_MAX_POW13	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率13
	{	PARA_C_UCH_MAX_POW14	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率14
	{	PARA_C_UCH_MAX_POW15	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率15
	{	PARA_C_UCH_MAX_POW16	, PT_CP_G_EX|PT_NC, 	-5,},	//	C段上行通道最大输入功率16
	{	PARA_C_DCH_POW1	, PT_NC, 	0,},	//	C段选频通道下行功率1
	{	PARA_C_DCH_POW2	, PT_NC, 	0,},	//	C段选频通道下行功率2
	{	PARA_C_DCH_POW3	, PT_NC, 	0,},	//	C段选频通道下行功率3
	{	PARA_C_DCH_POW4	, PT_NC, 	0,},	//	C段选频通道下行功率4
	{	PARA_C_DCH_POW5	, PT_NC, 	0,},	//	C段选频通道下行功率5
	{	PARA_C_DCH_POW6	, PT_NC, 	0,},	//	C段选频通道下行功率6
	{	PARA_C_DCH_POW7	, PT_NC, 	0,},	//	C段选频通道下行功率7
	{	PARA_C_DCH_POW8	, PT_NC, 	0,},	//	C段选频通道下行功率8
	{	PARA_C_DCH_POW9	, PT_NC, 	0,},	//	C段选频通道下行功率9
	{	PARA_C_DCH_POW10	, PT_NC, 	0,},	//	C段选频通道下行功率10
	{	PARA_C_DCH_POW11	, PT_NC, 	0,},	//	C段选频通道下行功率11
	{	PARA_C_DCH_POW12	, PT_NC, 	0,},	//	C段选频通道下行功率12
	{	PARA_C_DCH_POW13	, PT_NC, 	0,},	//	C段选频通道下行功率13
	{	PARA_C_DCH_POW14	, PT_NC, 	0,},	//	C段选频通道下行功率14
	{	PARA_C_DCH_POW15	, PT_NC, 	0,},	//	C段选频通道下行功率15
	{	PARA_C_DCH_POW16	, PT_NC, 	0,},	//	C段选频通道下行功率16
	{	PARA_C_UCH_POW1	, PT_NC, 	0,},	//	C段选频通道上行功率1
	{	PARA_C_UCH_POW2	, PT_NC, 	0,},	//	C段选频通道上行功率2
	{	PARA_C_UCH_POW3	, PT_NC, 	0,},	//	C段选频通道上行功率3
	{	PARA_C_UCH_POW4	, PT_NC, 	0,},	//	C段选频通道上行功率4
	{	PARA_C_UCH_POW5	, PT_NC, 	0,},	//	C段选频通道上行功率5
	{	PARA_C_UCH_POW6	, PT_NC, 	0,},	//	C段选频通道上行功率6
	{	PARA_C_UCH_POW7	, PT_NC, 	0,},	//	C段选频通道上行功率7
	{	PARA_C_UCH_POW8	, PT_NC, 	0,},	//	C段选频通道上行功率8
	{	PARA_C_UCH_POW9	, PT_NC, 	0,},	//	C段选频通道上行功率9
	{	PARA_C_UCH_POW10	, PT_NC, 	0,},	//	C段选频通道上行功率10
	{	PARA_C_UCH_POW11	, PT_NC, 	0,},	//	C段选频通道上行功率11
	{	PARA_C_UCH_POW12	, PT_NC, 	0,},	//	C段选频通道上行功率12
	{	PARA_C_UCH_POW13	, PT_NC, 	0,},	//	C段选频通道上行功率13
	{	PARA_C_UCH_POW14	, PT_NC, 	0,},	//	C段选频通道上行功率14
	{	PARA_C_UCH_POW15	, PT_NC, 	0,},	//	C段选频通道上行功率15
	{	PARA_C_UCH_POW16	, PT_NC, 	0,},	//	C段选频通道上行功率16
	{	PARA_C_UDPX_IN_GAIN	, PT_CP_G_EX|PT_NC, 	0,},	//	C段输入双工器增益
	{	PARA_C_UDPX_OUT_GAIN, PT_CP_G_EX|PT_NC, 	0,},	//	C段输出双工器增益
	{	PARA_C_DL_TOTAL_POW	, PT_CP|PT_RO|PT_SI, 	0,},	//	C段下行总功率
	{	PARA_C_UL_TOTAL_POW	, PT_CP_G_EX|PT_RO|PT_SI, 	0,},	//	C段上行总功率
	{	PARA_C_REC_DPX_IG	, PT_NC, 	0,},	//	REC的C段输入双工器衰减，用来进行增益计算，只读,	
	{	PARA_C_REC_DPX_OG	, PT_NC, 	0,},	//	REC的C段输出双工器衰减，用来进行增益计算，只读,	
	{ 	PARA_D_DL_CHANNEL1  , PT_DP|PT_US,  39100,},	// D段下行信道号1
	{ 	PARA_D_DL_CHANNEL2  , PT_DP|PT_US,  39100,},	// D段下行信道号2
	{ 	PARA_D_DL_CHANNEL3  , PT_DP|PT_US,  39210,},	// D段下行信道号3
	{ 	PARA_D_DL_CHANNEL4  , PT_DP|PT_US,  39210,},	// D段下行信道号4
	{ 	PARA_D_DL_CHANNEL5  , PT_DP|PT_US,  39210,},	// D段下行信道号5
	{	PARA_D_DL_CHANNEL6  , PT_DP|PT_US,  39210,},	// D段下行信道号6
	{ 	PARA_D_DL_CHANNEL7  , PT_DP|PT_US,  39210,},	// D段下行信道号7
	{ 	PARA_D_DL_CHANNEL8  , PT_DP|PT_US,  39210,},	// D段下行信道号8
	{ 	PARA_D_DL_CHANNEL9  , PT_DP|PT_US,  39210,},	// D段下行信道号9
	{ 	PARA_D_DL_CHANNEL10  , PT_DP|PT_US,  39210,},  // D段下行信道号10
	{	PARA_D_UL_CHANNEL1	, PT_US, 	39210,}, 	//	D段上行信道号1
	{	PARA_D_UL_CHANNEL2	, PT_US, 	39210,},	//	D段上行信道号2
	{	PARA_D_UL_CHANNEL3	, PT_US, 	39210,},	//	D段上行信道号3
	{	PARA_D_UL_CHANNEL4	, PT_US, 	39210,},	//	D段上行信道号4
	{	PARA_D_UL_CHANNEL5	, PT_US, 	39210,},	//	D段上行信道号5
	{	PARA_D_UL_CHANNEL6	, PT_US, 	39210,},	//	D段上行信道号6
	{	PARA_D_UL_CHANNEL7	, PT_US, 	39210,},	//	D段上行信道号7
	{	PARA_D_UL_CHANNEL8	, PT_US, 	39210,},	//	D段上行信道号8
	{	PARA_D_UL_CHANNEL9	, PT_US, 	39210,},	//	D段上行信道号9
	{	PARA_D_UL_CHANNEL10	, PT_US, 	39210,},	//	D段上行信道号10
	{	PARA_D_DCH_MAX_POW1	, PT_DP_G_EX|PT_SI, 		27,},	//	D段下行通道最大输出功率1
	{	PARA_D_DCH_MAX_POW2	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率2
	{	PARA_D_DCH_MAX_POW3	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率3
	{	PARA_D_DCH_MAX_POW4	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率4
	{	PARA_D_DCH_MAX_POW5	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率5
	{	PARA_D_DCH_MAX_POW6	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率6
	{	PARA_D_DCH_MAX_POW7	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率7
	{	PARA_D_DCH_MAX_POW8	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率8
	{	PARA_D_DCH_MAX_POW9	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率9
	{	PARA_D_DCH_MAX_POW10	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率10
	{	PARA_D_DCH_MAX_POW11	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率11
	{	PARA_D_DCH_MAX_POW12	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率12
	{	PARA_D_DCH_MAX_POW13	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率13
	{	PARA_D_DCH_MAX_POW14	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率14
	{	PARA_D_DCH_MAX_POW15	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率15
	{	PARA_D_DCH_MAX_POW16	, PT_DP_G_EX|PT_NC, 	27,},	//	D段下行通道最大输出功率16
	{	PARA_D_UCH_MAX_POW1	, PT_DP|PT_SI, 		-5,},	//	D段上行通道最大输入功率1
	{	PARA_D_UCH_MAX_POW2	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率2
	{	PARA_D_UCH_MAX_POW3	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率3
	{	PARA_D_UCH_MAX_POW4	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率4
	{	PARA_D_UCH_MAX_POW5	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率5
	{	PARA_D_UCH_MAX_POW6	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率6
	{	PARA_D_UCH_MAX_POW7	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率7
	{	PARA_D_UCH_MAX_POW8	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率8
	{	PARA_D_UCH_MAX_POW9	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率9
	{	PARA_D_UCH_MAX_POW10	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率10
	{	PARA_D_UCH_MAX_POW11	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率11
	{	PARA_D_UCH_MAX_POW12	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率12
	{	PARA_D_UCH_MAX_POW13	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率13
	{	PARA_D_UCH_MAX_POW14	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率14
	{	PARA_D_UCH_MAX_POW15	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率15
	{	PARA_D_UCH_MAX_POW16	, PT_DP_G_EX|PT_NC, 	-5,},	//	D段上行通道最大输入功率16
	{	PARA_D_DCH_POW1	, PT_NC, 	0,},	//	D段选频通道下行功率1
	{	PARA_D_DCH_POW2	, PT_NC, 	0,},	//	D段选频通道下行功率2
	{	PARA_D_DCH_POW3	, PT_NC, 	0,},	//	D段选频通道下行功率3
	{	PARA_D_DCH_POW4	, PT_NC, 	0,},	//	D段选频通道下行功率4
	{	PARA_D_DCH_POW5	, PT_NC, 	0,},	//	D段选频通道下行功率5
	{	PARA_D_DCH_POW6	, PT_NC, 	0,},	//	D段选频通道下行功率6
	{	PARA_D_DCH_POW7	, PT_NC, 	0,},	//	D段选频通道下行功率7
	{	PARA_D_DCH_POW8	, PT_NC, 	0,},	//	D段选频通道下行功率8
	{	PARA_D_DCH_POW9	, PT_NC, 	0,},	//	D段选频通道下行功率9
	{	PARA_D_DCH_POW10	, PT_NC, 	0,},	//	D段选频通道下行功率10
	{	PARA_D_DCH_POW11	, PT_NC, 	0,},	//	D段选频通道下行功率11
	{	PARA_D_DCH_POW12	, PT_NC, 	0,},	//	D段选频通道下行功率12
	{	PARA_D_DCH_POW13	, PT_NC, 	0,},	//	D段选频通道下行功率13
	{	PARA_D_DCH_POW14	, PT_NC, 	0,},	//	D段选频通道下行功率14
	{	PARA_D_DCH_POW15	, PT_NC, 	0,},	//	D段选频通道下行功率15
	{	PARA_D_DCH_POW16	, PT_NC, 	0,},	//	D段选频通道下行功率16
	{	PARA_D_UCH_POW1	, PT_NC, 	0,},	//	D段选频通道上行功率1
	{	PARA_D_UCH_POW2	, PT_NC, 	0,},	//	D段选频通道上行功率2
	{	PARA_D_UCH_POW3	, PT_NC, 	0,},	//	D段选频通道上行功率3
	{	PARA_D_UCH_POW4	, PT_NC, 	0,},	//	D段选频通道上行功率4
	{	PARA_D_UCH_POW5	, PT_NC, 	0,},	//	D段选频通道上行功率5
	{	PARA_D_UCH_POW6	, PT_NC, 	0,},	//	D段选频通道上行功率6
	{	PARA_D_UCH_POW7	, PT_NC, 	0,},	//	D段选频通道上行功率7
	{	PARA_D_UCH_POW8	, PT_NC, 	0,},	//	D段选频通道上行功率8
	{	PARA_D_UCH_POW9	, PT_NC, 	0,},	//	D段选频通道上行功率9
	{	PARA_D_UCH_POW10	, PT_NC, 	0,},	//	D段选频通道上行功率10
	{	PARA_D_UCH_POW11	, PT_NC, 	0,},	//	D段选频通道上行功率11
	{	PARA_D_UCH_POW12	, PT_NC, 	0,},	//	D段选频通道上行功率12
	{	PARA_D_UCH_POW13	, PT_NC, 	0,},	//	D段选频通道上行功率13
	{	PARA_D_UCH_POW14	, PT_NC, 	0,},	//	D段选频通道上行功率14
	{	PARA_D_UCH_POW15	, PT_NC, 	0,},	//	D段选频通道上行功率15
	{	PARA_D_UCH_POW16	, PT_NC, 	0,},	//	D段选频通道上行功率16
	{	PARA_D_UDPX_IN_GAIN	, PT_DP_G_EX|PT_NC, 	0,},	//	D段输入双工器增益
	{	PARA_D_UDPX_OUT_GAIN, PT_DP_G_EX|PT_NC, 	0,},	//	D段输出双工器增益
	{	PARA_D_DL_TOTAL_POW	, PT_DP|PT_RO|PT_SI, 	0,},	//	D段下行输出总功率/*PT_BP_EX*/
	{	PARA_D_UL_TOTAL_POW	, PT_DP_G_EX|PT_RO|PT_SI, 	0,},	//	D段上行输入总功率/*PT_BP_EX*/
	{	PARA_D_REC_DPX_IG	, PT_DP_G_EX|PT_NC, 	0,},	//	REC的D段输入双工器衰减，用来进行增益计算，只读,	
	{	PARA_D_REC_DPX_OG	, PT_DP_G_EX|PT_NC, 	0,},	//	REC的D段输出双工器衰减，用来进行增益计算，只读,	
	{	PARA_REC_TO_RE_DELAY,	PT_AP_G_EX|PT_BP_G_EX|PT_US,	0},	// REC到RE的光纤延时
	{	PARA_RE_RF_DELAY,		PT_AP_G_EX|PT_BP_G_EX|PT_US,	0},	// RE的射频延时
	{	PARA_MAX_T14	, PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0,},	//	光口最大延时
	{	PARA_DL_DELAY_OFFSET	, PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0,},	//	下行延时偏移量
	{	PARA_UL_DELAY_OFFSET	, PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0,},	//	上行延时偏移量
	{	PARA_PRI_SOFT_V	, PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0,},	//	程序版本号（用ASCII码）
	{	PARA_PRI_HARD_V	, PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0,},	//	PCB版本号(用ASCII码)
	{	PARA_TD_1ST_CP_TIME,	PT_BP_EX|PT_US,	0},	// TD第1转换点时间ns, 有符号数
	{	PARA_TD_2ND_CP_TIME,	PT_BP_EX|PT_US,	0},	// TD第2转换点时间ns, 有符号数
	{	PARA_TD_LNA_ON_TIME,	PT_BP_EX|PT_US,	0},	// LNA开启迟后DN_PA关闭的保护时间ns
	{	PARA_TD_LNA_OFF_TIME,	PT_BP_EX|PT_US,	0},	// LNA关闭超前DN_PA开启的保护时间ns
	{	PARA_TD_SLOT1_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙1上行检测功率
	{	PARA_TD_SLOT2_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙2上行检测功率
	{	PARA_TD_SLOT3_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙3上行检测功率
	{	PARA_TD_SLOT4_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙4上行检测功率
	{	PARA_TD_SLOT5_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙5上行检测功率
	{	PARA_TD_SLOT6_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙6上行检测功率
	{	PARA_TD_SLOT7_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙7上行检测功率
	{	PARA_TD_SLOT1_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙1下行检测功率
	{	PARA_TD_SLOT2_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙2下行检测功率
	{	PARA_TD_SLOT3_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙3下行检测功率
	{	PARA_TD_SLOT4_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙4下行检测功率
	{	PARA_TD_SLOT5_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙5下行检测功率
	{	PARA_TD_SLOT6_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙6下行检测功率
	{	PARA_TD_SLOT7_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TD时隙7下行检测功率
	{	PARA_FPS_S1,	PT_SI,	0},	// 频点搜素范围1起始频点
	{	PARA_FPS_E1,	PT_SI,	0},	// 频点搜素范围1结束频点
	{	PARA_FPS_S2,	PT_SI,	0},	// 频点搜素范围2起始频点
	{	PARA_FPS_E2,	PT_SI,	0},	// 频点搜素范围2结束频点
	{	PARA_FPS_BCCH_LK_SET,	PT_AP_G|PT_US,	65535},	// 频点搜索: 锁频信道号: 标准信道号, 65535-退出锁频
	{	PARA_FPS_CID_LK_SET	,	PT_AP_G|PT_US,	0},	// 频点搜索: 小区识别码参考值, 0-退出小区锁定功能
	{	PARA_FPS_BCCH_FC_M	,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: 主小区BCCH信道号, 标准信道号, 65535-无BCCH
	{	PARA_FPS_CA_FC_0,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波0信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_1,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波1信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_2,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波2信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_3,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波3信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_4,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波4信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_5,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波5信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_6,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波6信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_7,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波7信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_8,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波8信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_9,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波9信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_10,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波10信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_11,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波11信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_12,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波12信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_13,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波13信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_14,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波14信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_CA_FC_15,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: CA载波15信道号, 标准信道号, 65535-无CA
	{	PARA_FPS_BCCH_FC_1,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: 邻小区1 BCCH信道号, 标准信道号, 65535-无BCCH
	{	PARA_FPS_BCCH_FC_2,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: 邻小区2 BCCH信道号, 标准信道号, 65535-无BCCH
	{	PARA_FPS_BCCH_FC_3,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: 邻小区3 BCCH信道号, 标准信道号, 65535-无BCCH
	{	PARA_FPS_BCCH_FC_4,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: 邻小区4 BCCH信道号, 标准信道号, 65535-无BCCH
	{	PARA_FPS_BCCH_FC_5,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: 邻小区5 BCCH信道号, 标准信道号, 65535-无BCCH
	{	PARA_FPS_BCCH_FC_6,	PT_AP_G|PT_RO|PT_US,	65535},	// 频点搜索: 邻小区6 BCCH信道号, 标准信道号, 65535-无BCCH
	{	PARA_FPS_AREA_ID,	PT_AP_G_EX|PT_RO|PT_US,	0},	// 频点搜索: 位置区编码
	{	PARA_FPS_CID,	PT_AP_G_EX|PT_RO|PT_US,	0},	// 频点搜索: 小区识别码实时值
	{	PARA_FPS_CID_1,		PT_NC,	0}, // 频点搜索: 邻小区1 CID小区识别码
	{	PARA_FPS_CID_2,		PT_NC,	0}, // 频点搜索: 邻小区2 CID小区识别码
	{	PARA_FPS_CID_3,		PT_NC,	0}, // 频点搜索: 邻小区3 CID小区识别码
	{	PARA_FPS_CID_4,		PT_NC,	0}, // 频点搜索: 邻小区4 CID小区识别码
	{	PARA_FPS_CID_5,		PT_NC,	0}, // 频点搜索: 邻小区5 CID小区识别码
	{	PARA_FPS_CID_6,		PT_NC,	0}, // 频点搜索: 邻小区6 CID小区识别码
	{	PARA_A_EXPA_IDRAIN_SET,	PT_NC,	0},	// 微功放: 漏极电流设置,mA
	{	PARA_TD_SLOT1_DPOW_OVER_THR,    PT_BP_G_EX|PT_US, 	0},       //下行输入导频过功率门限
	{	PARA_TD_SLOT1_DPOW_OWE_THR,    	PT_BP_G_EX|PT_US, 	0},       //下行输入导频欠功率门限
	{	PARA_A_INPUT_TOTAL_DPOW_OVER_THR,				PT_AP_G_EX|PT_US,	0},//下行输入导频过功率门限
	{	PARA_A_INPUT_TOTAL_DPOW_OWE_THR,				PT_AP_G_EX|PT_US,	0},//下行输入导频欠功率门限
	{	PARA_B_INPUT_TOTAL_DPOW_OVER_THR,				PT_BP_G_EX|PT_US,	0},//下行输入导频过功率门限
	{	PARA_B_INPUT_TOTAL_DPOW_OWE_THR,				PT_BP_G_EX|PT_US,	0},//下行输入导频欠功率门限
	{	PARA_C_INPUT_TOTAL_DPOW_OVER_THR,				PT_CP_G_EX|PT_US,	0},//下行输入导频过功率门限
	{	PARA_C_INPUT_TOTAL_DPOW_OWE_THR,				PT_CP_G_EX|PT_US,	0},//下行输入导频欠功率门限
	{	PARA_D_INPUT_TOTAL_DPOW_OVER_THR,				PT_DP_G_EX|PT_US,	0},//下行输入导频过功率门限
	{	PARA_D_INPUT_TOTAL_DPOW_OWE_THR,				PT_DP_G_EX|PT_US,	0},//下行输入导频欠功率门限
	{	PARA_REE_A_DL_OUT_TOTAL_POW_DETECT,		PT_AP_G_EX|PT_US,	0},//A段REE下行输出总功率
	{	PARA_A_RE_LOCAL_ST_ALARM,					PT_AP_G_EX|PT_BP_G_EX|PT_US,	0},//覆盖单元本地告警状态
	{	PARA_REE_B_DL_OUT_TOTAL_POW_DETECT ,		PT_BP_G_EX|PT_US,	0}, //B段REE下行输出总功率
	{	PARA_B_RE_LOCAL_ST_ALARM,	PT_BP_G_EX|PT_US,	0},//覆盖单元本地告警状态
	{	PARA_REE_C_DL_OUT_TOTAL_POW_DETECT,		PT_CP_G_EX|PT_US,	0},//C段REE下行输出总功率
	{	PARA_C_RE_LOCAL_ST_ALARM,					PT_CP_G_EX|PT_US,	0},//覆盖单元本地告警状态
	{	PARA_REE_D_DL_OUT_TOTAL_POW_DETECT ,		PT_DP_G_EX|PT_US,	0}, //D段REE下行输出总功率
	{	PARA_D_RE_LOCAL_ST_ALARM,	PT_DP_G_EX|PT_US,	0},//覆盖单元本地告警状态
	{	PARA_C_TD_1ST_CP_TIME,	PT_CP_G_EX|PT_US,	0},		//465		//		TD第1转换点时间,ns,	
	{	PARA_C_TD_2ND_CP_TIME,	PT_CP_G_EX|PT_US,	0},		//466		//		TD第2转换点时间,ns,	
	{	PARA_C_TD_LNA_ON_TIME,	PT_CP_G_EX|PT_US,	0},		//467		//		LNA开启迟后DN_PA关闭的保护时间ns	
	{	PARA_C_TD_LNA_OFF_TIME,	PT_CP_G_EX|PT_US,	0},		//468		//		LNA关闭超前DN_PA开启的保护时间ns	
	{	PARA_C_TD_SLOT1_DPOW_OVER_THR,	PT_CP_G_EX|PT_US,	0},		//469		//625		//下行输入导频过功率门限	
	{	PARA_C_TD_SLOT1_DPOW_OWE_THR,	PT_CP_G_EX|PT_US,	0},		//470		//626		//下行输入导频欠功率门限	
	{	PARA_D_TD_1ST_CP_TIME,	PT_DP_G_EX|PT_US,	0},		//471		//		TD第1转换点时间,ns,	
	{	PARA_D_TD_2ND_CP_TIME,	PT_DP_G_EX|PT_US,	0},		//472		//		TD第2转换点时间,ns,	
	{	PARA_D_TD_LNA_ON_TIME,	PT_DP_G_EX|PT_US,	0},		//473		//		LNA开启迟后DN_PA关闭的保护时间ns	
	{	PARA_D_TD_LNA_OFF_TIME,	PT_DP_G_EX|PT_US,	0},		//474		//		LNA关闭超前DN_PA开启的保护时间ns	
	{	PARA_D_TD_SLOT1_DPOW_OVER_THR,	PT_DP_G_EX|PT_US,	0},		//475		//625		//下行输入导频过功率门限	
	{	PARA_D_TD_SLOT1_DPOW_OWE_THR,	PT_DP_G_EX|PT_US,	0},		//476		//626		//下行输入导频欠功率门限	
	{	PARA_C_TD_SLOT1_POW,	PT_CP_G_EX|PT_US,	0},		//477		//		TD时隙1输入检测功率	
	{	PARA_C_TD_SLOT2_POW,	PT_CP_G_EX|PT_US,	0},		//478		//		TD时隙2输入检测功率	
	{	PARA_C_TD_SLOT3_POW,	PT_CP_G_EX|PT_US,	0},		//479		//		TD时隙3输入检测功率	
	{	PARA_C_TD_SLOT4_POW,	PT_CP_G_EX|PT_US,	0},		//480		//		TD时隙4输入检测功率	
	{	PARA_C_TD_SLOT5_POW,	PT_CP_G_EX|PT_US,	0},		//481		//		TD时隙5输入检测功率	
	{	PARA_C_TD_SLOT6_POW,	PT_CP_G_EX|PT_US,	0},		//482		//		TD时隙6输入检测功率	
	{	PARA_C_TD_SLOT7_POW,	PT_CP_G_EX|PT_US,	0},		//483		//		TD时隙7输入检测功率	
	{	PARA_C_TD_SLOT8_POW,	PT_CP_G_EX|PT_US,	0},		//484		//		TD时隙8输入检测功率	
	{	PARA_C_TD_SLOT9_POW,	PT_CP_G_EX|PT_US,	0},		//485		//		TD时隙9输入检测功率	
	{	PARA_C_TD_SLOT10_POW,	PT_CP_G_EX|PT_US,	0},		//486		//		TD时隙10输入检测功率	
	{	PARA_C_TD_SLOT11_POW,	PT_CP_G_EX|PT_US,	0},		//487		//		TD时隙11输入检测功率	
	{	PARA_C_TD_SLOT12_POW,	PT_CP_G_EX|PT_US,	0},		//488		//		TD时隙12输入检测功率	
	{	PARA_C_TD_SLOT13_POW,	PT_CP_G_EX|PT_US,	0},		//489		//		TD时隙13输入检测功率	
	{	PARA_C_TD_SLOT14_POW,	PT_CP_G_EX|PT_US,	0},		//490		//		TD时隙14输入检测功率	
	{	PARA_C_TD_SLOT15_POW,	PT_CP_G_EX|PT_US,	0},		//491		//		TD时隙15输入检测功率	
	{	PARA_C_TD_SLOT16_POW,	PT_CP_G_EX|PT_US,	0},		//492		//		TD时隙16输入检测功率	
	{	PARA_C_TD_SLOT17_POW,	PT_CP_G_EX|PT_US,	0},		//493		//		TD时隙17输入检测功率	
	{	PARA_C_TD_SLOT18_POW,	PT_CP_G_EX|PT_US,	0},		//494		//		TD时隙18输入检测功率	
	{	PARA_C_TD_SLOT19_POW,	PT_CP_G_EX|PT_US,	0},		//495		//		TD时隙19输入检测功率	
	{	PARA_C_TD_SLOT20_POW,	PT_CP_G_EX|PT_US,	0},		//496		//		TD时隙20输入检测功率	
	{	PARA_D_TD_SLOT1_POW,	PT_DP_G_EX|PT_US,	0},		//497		//		TD时隙1输入检测功率	
	{	PARA_D_TD_SLOT2_POW,	PT_DP_G_EX|PT_US,	0},		//498		//		TD时隙2输入检测功率	
	{	PARA_D_TD_SLOT3_POW,	PT_DP_G_EX|PT_US,	0},		//499		//		TD时隙3输入检测功率	
	{	PARA_D_TD_SLOT4_POW,	PT_DP_G_EX|PT_US,	0},		//500		//		TD时隙4输入检测功率	
	{	PARA_D_TD_SLOT5_POW,	PT_DP_G_EX|PT_US,	0},		//501		//		TD时隙5输入检测功率	
	{	PARA_D_TD_SLOT6_POW,	PT_DP_G_EX|PT_US,	0},		//502		//		TD时隙6输入检测功率	
	{	PARA_D_TD_SLOT7_POW,	PT_DP_G_EX|PT_US,	0},		//503		//		TD时隙7输入检测功率	
	{	PARA_D_TD_SLOT8_POW,	PT_DP_G_EX|PT_US,	0},		//504		//		TD时隙8输入检测功率	
	{	PARA_D_TD_SLOT9_POW,	PT_DP_G_EX|PT_US,	0},		//505		//		TD时隙9输入检测功率	
	{	PARA_D_TD_SLOT10_POW,	PT_DP_G_EX|PT_US,	0},		//506		//		TD时隙10输入检测功率	
	{	PARA_D_TD_SLOT11_POW,	PT_DP_G_EX|PT_US,	0},		//507		//		TD时隙11输入检测功率	
	{	PARA_D_TD_SLOT12_POW,	PT_DP_G_EX|PT_US,	0},		//508		//		TD时隙12输入检测功率	
	{	PARA_D_TD_SLOT13_POW,	PT_DP_G_EX|PT_US,	0},		//509		//		TD时隙13输入检测功率	
	{	PARA_D_TD_SLOT14_POW,	PT_DP_G_EX|PT_US,	0},		//510		//		TD时隙14输入检测功率	
	{	PARA_D_TD_SLOT15_POW,	PT_DP_G_EX|PT_US,	0},		//511		//		TD时隙15输入检测功率	
	{	PARA_D_TD_SLOT16_POW,	PT_DP_G_EX|PT_US,	0},		//512		//		TD时隙16输入检测功率	
	{	PARA_D_TD_SLOT17_POW,	PT_DP_G_EX|PT_US,	0},		//513		//		TD时隙17输入检测功率	
	{	PARA_D_TD_SLOT18_POW,	PT_DP_G_EX|PT_US,	0},		//514		//		TD时隙18输入检测功率	
	{	PARA_D_TD_SLOT19_POW,	PT_DP_G_EX|PT_US,	0},		//515		//		TD时隙19输入检测功率	
	{	PARA_D_TD_SLOT20_POW,	PT_DP_G_EX|PT_US,	0},		//516		//		TD时隙20输入检测功率	
	{	PARA_DL_DELAY_OFFSET_B	,PT_BP|PT_US, 	0},		//0x8660	//		下行延时偏移量					
	{	PARA_DL_DELAY_OFFSET_C	,PT_CP|PT_US, 	0},		//0x8660	//		下行延时偏移量					
	{	PARA_DL_DELAY_OFFSET_D	,PT_DP|PT_US, 	0},		//0x8660	//		下行延时偏移量					
	{	PARA_VGS_A	,PT_AP|PT_US,	0}, 	//A段栅压
	{	PARA_VGS_B	,PT_BP|PT_US,	0}, 	//B段栅压
	{	PARA_VGS_C	,PT_CP|PT_US,	0}, 	//C段栅压
	{	PARA_VGS_D	,PT_DP|PT_US,	0}, 	//D段栅压
	{	PARA_VGS_COMP_A ,PT_AP|PT_US,	0}, 	//A段栅压
	{	PARA_VGS_COMP_B ,PT_BP|PT_US,	0}, 	//B段栅压
	{	PARA_VGS_COMP_C ,PT_CP|PT_US,	0}, 	//C段栅压
	{	PARA_VGS_COMP_D ,PT_DP|PT_US,	0}, 	//D段栅压
	{	PARA_ATT_DATA_COMP_A	,PT_AP|PT_US,	0}, //ATT补偿数据
	{	PARA_ATT_DATA_COMP_B	,PT_BP|PT_US,	0}, //ATT补偿数据
	{	PARA_ATT_DATA_COMP_C	,PT_CP|PT_US,	0}, //ATT补偿数据
	{	PARA_ATT_DATA_COMP_D	,PT_DP|PT_US,	0}, //ATT补偿数据//PARA_MAX_T14_A
	{	PARA_MAX_T14_A	,PT_AP|PT_US,	0}, //ATT补偿数据
	{	PARA_MAX_T14_B	,PT_BP|PT_US,	0}, //ATT补偿数据
	{	PARA_MAX_T14_C	,PT_CP|PT_US,	0}, //ATT补偿数据
	{	PARA_MAX_T14_D	,PT_DP|PT_US,	0}, //ATT补偿数
	{	PARA_ERL_JG_A,PT_AP|PT_US,	0}, 
	{	PARA_ERL_JG_C,PT_CP|PT_US,	0}, 
	{	PARA_ERL_JG_D,PT_DP|PT_US,	0}, 
	{	PARA_MOVE_CENTER_FRE_D,PT_NC,	0}, 										
	{	PARA_MOVE_CENTER_FRE_U,PT_NC, 0}, 										
};


_T_PARAM_4B sys_param_4b[]={
	{ 	PARA_DEV_ADDR , PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_US,	0	 },		//	设备路由登记地址
	{	PARA_BIT_ERR_COUNT, PT_NC, 0 },		// 数据包错误统计
	{	PARA_TOPO_CHG_COUNT, PT_NC, 0 },		// 数据包错误统计
	{	PARA_FPGA_PKT_COUNT, PT_NC, 0 },		// FPGA数据包个数统计
	{	PARA_OPT_RE_COUNT1, PT_AP_EX|PT_BP_EX|PT_CP|PT_DP|PT_US, 0 },		// 远端机节点计数1
	{	PARA_OPT_RE_COUNT2, PT_AP_EX|PT_BP_EX|PT_CP|PT_DP|PT_US, 0 },		// 远端机节点计数2
	{	PARA_OPS_PORT, PT_AP_EX|PT_BP_EX|PT_CP|PT_DP|PT_US, 0 },		// 光口的对端光口号
};

// 模块识别ID号(用ASCII码)			REC/RE
UCHAR8 str_pri_id[PRI_ID_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// 模块类型(用ASCII码)				REC/RE
UCHAR8 str_pri_type[PRI_TYPE_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', '\0'};
// 生产序列号(用ASCII码)			20101030001
UCHAR8 str_pri_seq[PRI_SEQ_LEN]={'2', '0', '1', '0', '1', '0', '3', '0', '0', '0', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// 厂家产品编号(用ASCII码)			DOF-FFFFFFFW21400302
UCHAR8 str_pri_gl_product[PRI_GL_PRODUCT_LEN]={'D', 'O', 'N', '-', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'W', '2', '1', '4', '0', '0', '3', '0', '2'};
// 厂家生产序列号(用ASCII码)		20101030001
UCHAR8 str_pri_gl_seq[PRI_GL_SEQ_LEN]={'2', '0', '1', '0', '1', '0', '3', '0', '0', '0', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// 唯一识别ID(用ASCII码)			REC/RE
UCHAR8 str_pri_gl_rom_id[PRI_GL_ROM_ID_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// MCU程序日期(用ASCII码)
UCHAR8 str_pri_mcu_date[PRI_MCU_DATE_LEN]={0};
// FPGA程序日期(用ASCII码)
UCHAR8 str_pri_fpga_date[PRI_FPGA_DATE_LEN]={0};
// FPGA2程序日期(用ASCII码)
UCHAR8 str_pri_fpga2_date[PRI_FPGA_DATE_LEN]={0};
// ID识别字符串(用ASCII码)			REC/RE
UCHAR8 str_module_hri_str[MODULE_HRI_STR_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
//	9363_A配置文件更新日期(用ASCII码)
UCHAR8 str_a_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	9363_B配置文件更新日期(用ASCII码)
UCHAR8 str_b_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	9363_C配置文件更新日期(用ASCII码)
UCHAR8 str_c_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	ree设备位置信息
UCHAR8 str_mau_position_inf[PRI_MAU_POSITION_INF_LEN]={0};
// MCU程序版本(用ASCII码)
UCHAR8 str_pri_mcu_version_new[MCU_VERSION_NEW_LEN]={'M', 'A', 'U', ' ', ' ', ' ', ' ', ' ', ' ',};



_T_PARAM_ASC sys_param_asc[]={
	{ 	PARA_PRI_TYPE, 			PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_TYPE_LEN, str_pri_type },
	{ 	PARA_PRI_ID, 			PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_ID_LEN, str_pri_id },
	{ 	PARA_PRI_MCU_DATE, 		PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_MCU_DATE_LEN, str_pri_mcu_date },
	{ 	PARA_PRI_GL_ROM_ID, 	PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_GL_ROM_ID_LEN, str_pri_gl_rom_id },
	{ 	PARA_PRI_GL_SEQ, 		PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_GL_SEQ_LEN, str_pri_gl_seq },
	{ 	PARA_PRI_GL_PRODUCT, 	PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_GL_PRODUCT_LEN, str_pri_gl_product },
	{ 	PARA_PRI_SEQ, 			PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_SEQ_LEN, str_pri_seq },
	{ 	PARA_MODULE_HRI_STR, 	PT_NC, MODULE_HRI_STR_LEN, str_module_hri_str },
	{ 	PARA_PRI_FPGA_DATE, 	PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_FPGA_DATE_LEN, str_pri_fpga_date },
	{ 	PARA_PRI_FPGA2_DATE, 	PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_FPGA_DATE_LEN, str_pri_fpga2_date },
	{ 	PARA_A_PRI_9363_UPDATA_DATE, 	PT_AP_G_EX|PT_RO|PT_NC, PRI_9363_UPDATA_DATE_LEN, str_a_pri_9363_date },
	{ 	PARA_B_PRI_9363_UPDATA_DATE, 	PT_BP_G_EX|PT_RO|PT_NC, PRI_9363_UPDATA_DATE_LEN, str_b_pri_9363_date },
	{ 	PARA_C_PRI_9363_UPDATA_DATE, 	PT_CP_G_EX|PT_RO|PT_NC, PRI_9363_UPDATA_DATE_LEN, str_c_pri_9363_date },
	{	PARA_REE_POSITION_INF	,		PT_AP|PT_RO|PT_NC, PRI_MAU_POSITION_INF_LEN, 		str_mau_position_inf },
	{ 	PARA_MCU_VERSION_NEW, 		PT_AP|PT_BP|PT_RO|PT_NC, MCU_VERSION_NEW_LEN, str_pri_mcu_version_new },

};



_T_PARAM_1B sys_param_eu_1b[]={
	{	PARA_EU_ALARM_FLAG1     			,PT_AP|PT_BP|PT_US, 	0},      	//EU1告警指示
	{	PARA_EU_ALARM_FLAG2     			,PT_AP|PT_BP|PT_US, 	0},      	//EU2告警指示
	{	PARA_EU_ALARM_FLAG3     			,PT_AP|PT_BP|PT_US, 	0},      	//EU3告警指示
	{	PARA_EU_ALARM_FLAG4     			,PT_AP|PT_BP|PT_US, 	0},     	//EU4告警指示
	{	PARA_EU_ALARM_FLAG5     			,PT_AP|PT_BP|PT_US, 	0},      	//EU5告警指示
	{	PARA_EU_ALARM_FLAG6     			,PT_AP|PT_BP|PT_US, 	0},     	//EU6告警指示
	{	PARA_EU_ALARM_FLAG7     			,PT_AP|PT_BP|PT_US, 	0},      	//EU7告警指示
	{	PARA_EU_ALARM_FLAG8     			,PT_AP|PT_BP|PT_US, 	0},      	//EU8告警指示
	
};

_T_PARAM_2B sys_param_eu_2b[]={

	{	PARA_EU_ALARM_CONTENT1 ,		PT_AP|PT_BP|PT_US,	0},//EU1告警内容
	{	PARA_EU_ALARM_CONTENT2,		PT_AP|PT_BP|PT_US,	0},//EU2告警内容
	{	PARA_EU_ALARM_CONTENT3 ,		PT_AP|PT_BP|PT_US, 	0},//EU3告警内容
	{	PARA_EU_ALARM_CONTENT4 ,		PT_AP|PT_BP|PT_US, 	0},//EU4告警内容	
	{	PARA_EU_ALARM_CONTENT5 ,		PT_AP|PT_BP|PT_US,	0},//EU5告警内容
	{	PARA_EU_ALARM_CONTENT6,		PT_AP|PT_BP|PT_US,	0},//EU6告警内容
	{	PARA_EU_ALARM_CONTENT7 ,		PT_AP|PT_BP|PT_US, 	0},//EU7告警内容
	{	PARA_EU_ALARM_CONTENT8 ,		PT_AP|PT_BP|PT_US, 	0},//EU8告警内容
	{	PARA_EU_RUALARM_FLAG1 ,		PT_AP|PT_BP|PT_US, 	0},//EU1下的16个RU告警指示
	{	PARA_EU_RUALARM_FLAG2 ,		PT_AP|PT_BP|PT_US, 	0},//EU2下的16个RU告警指示
	{	PARA_EU_RUALARM_FLAG3 ,		PT_AP|PT_BP|PT_US, 	0},//EU3下的16个RU告警指示
	{	PARA_EU_RUALARM_FLAG4 ,		PT_AP|PT_BP|PT_US, 	0},//EU4下的16个RU告警指示
	{	PARA_EU_RUALARM_FLAG5 ,		PT_AP|PT_BP|PT_US, 	0},//EU5下的16个RU告警指示
	{	PARA_EU_RUALARM_FLAG6 ,		PT_AP|PT_BP|PT_US, 	0},//EU6下的16个RU告警指示
	{	PARA_EU_RUALARM_FLAG7 ,		PT_AP|PT_BP|PT_US, 	0},//EU7下的16个RU告警指示
	{	PARA_EU_RUALARM_FLAG8 ,		PT_AP|PT_BP|PT_US, 	0},//EU8下的16个RU告警指示
};


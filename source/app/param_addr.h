/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : param_addr.h
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
#ifndef _PARAM_ADDR_H_
#define _PARAM_ADDR_H_



// 4字节参数结构体
typedef struct _S_PARAM_4B
{
	UINT16	addr;	// 地址
	UCHAR8	type;	// 性质和算法
	UINT32	val;		// 参数值
}_T_PARAM_4B;





#define PARAM_ASC_MAX_LEN		64		//字符串参数的长度最大值

#define PTM_MASK	(0x07<<0)	// 算法掩码
#define PT_NC		(0<<0) // 无算法
#define PT_SI		(1<<0) // 有符号数
#define PT_SW		(2<<0) // 有符号双字节数,需要将实际值x10
#define PT_US		(3<<0) // 无符号数
#define PT_RST		(4<<0) // 复位算法

#define PT_RO		(8<<0)	// 只读参数
#define PT_AP		(1<<4)	// 外部主控485参数
#define PT_BP		(1<<5)	// 外部主控485参数
#define PT_CP		(1<<6)	// 外部主控485参数
#define PT_DP		(1<<7)	// 外部主控485参数


#define PT_ARNC		(PT_AP|PT_NC)
#define PT_BRNC		(PT_BP|PT_NC)
#define PT_ABRNC	(PT_AP|PT_BP|PT_NC)

#if defined ( CLIENT_JIZHUN)
	// 国人参数
	#define PT_AP_G		(PT_AP)
	#define PT_BP_G		(PT_BP)
	#define PT_CP_G		(PT_CP)
	#define PT_DP_G		(PT_DP)		
	#define PT_AP_G_EX		(PT_AP)
	#define PT_BP_G_EX		(PT_BP)
	#define PT_CP_G_EX		(0)
	#define PT_DP_G_EX		(0)		
	// 对外参数
	#define PT_AP_EX	(PT_AP)
	#define PT_BP_EX	(PT_BP)	
	#define PT_CP_EX	(PT_CP)
	#define PT_DP_EX	(PT_DP)	

#else
	// 国人参数
	#define PT_AP_G		(0)
	#define PT_BP_G		(0)
	#define PT_CP_G		(0)
	#define PT_DP_G		(0)	
	// 对外参数
	#define PT_AP_EX	(PT_AP)
	#define PT_BP_EX	(PT_BP)	
	#define PT_CP_EX	(PT_CP)
	#define PT_DP_EX	(PT_DP)
	#define PT_AP_G_EX		(PT_AP)
	#define PT_BP_G_EX		(PT_BP)
	#define PT_CP_G_EX		(PT_CP)
	#define PT_DP_G_EX		(PT_DP)		
	
#endif

#if defined ( CLIENT_JIZHUN)
	// 国人参数
// 参数地址定义==================================================== 1b								
#define	PARA_A_CHANNEL_COUNT	0x8889	//	A段支持的通道数
#define	PARA_A_DL_WORK_EN	0x08a0	//	A段下行工作使能
#define	PARA_A_UL_WORK_EN	0x08a1	//	A段上行工作使能
#define	PARA_A_DPOW_MODE	0	//	A段下行功率控制方式
#define	PARA_A_UPOW_MODE	0	//	A段上行功率控制方式
#define	PARA_A_LTHR_EN	0x0770	//	A段上行底噪抑制使能
#define	PARA_A_LTHR_UP	0	//	A段底噪抑制上门限
#define	PARA_A_LTHR_DN	0x08b0	//	A段底噪抑制下门限
#define	PARA_A_DCH_EN1	0x08d0	//	A段下行通道工作使能1
#define	PARA_A_DCH_EN2	0x08d1	//	A段下行通道工作使能2
#define	PARA_A_DCH_EN3	0x08d2	//	A段下行通道工作使能3
#define	PARA_A_DCH_EN4	0x08d3	//	A段下行通道工作使能4
#define	PARA_A_DCH_EN5	0x08d4	//	A段下行通道工作使能5
#define	PARA_A_DCH_EN6	0x08d5	//	A段下行通道工作使能6
#define	PARA_A_DCH_EN7	0x08d6	//	A段下行通道工作使能7
#define	PARA_A_DCH_EN8	0x08d7	//	A段下行通道工作使能8
#define	PARA_A_DCH_EN9	0x08d8	//	A段下行通道工作使能9
#define	PARA_A_DCH_EN10	0x08d9	//	A段下行通道工作使能10
#define	PARA_A_DCH_EN11	0x08dA	//	A段下行通道工作使能11
#define	PARA_A_DCH_EN12	0x08dB	//	A段下行通道工作使能12
#define	PARA_A_DCH_EN13	0x08dC	//	A段下行通道工作使能13
#define	PARA_A_DCH_EN14	0x08dD	//	A段下行通道工作使能14
#define	PARA_A_DCH_EN15	0x08dE	//	A段下行通道工作使能15
#define	PARA_A_DCH_EN16	0x08dF	//	A段下行通道工作使能16
#define	PARA_A_UCH_EN1	0x08d0	//	A段上行通道工作使能1
#define	PARA_A_UCH_EN2	0x08d1	//	A段上行通道工作使能2
#define	PARA_A_UCH_EN3	0x08d2	//	A段上行通道工作使能3
#define	PARA_A_UCH_EN4	0x08d3	//	A段上行通道工作使能4
#define	PARA_A_UCH_EN5	0x08d4	//	A段上行通道工作使能5
#define	PARA_A_UCH_EN6	0x08d5	//	A段上行通道工作使能6
#define	PARA_A_UCH_EN7	0x08d6	//	A段上行通道工作使能7
#define	PARA_A_UCH_EN8	0x08d7	//	A段上行通道工作使能8
#define	PARA_A_UCH_EN9	0x08d8	//	A段上行通道工作使能9
#define	PARA_A_UCH_EN10	0x08d9	//	A段上行通道工作使能10
#define	PARA_A_UCH_EN11	0x08dA	//	A段上行通道工作使能11
#define	PARA_A_UCH_EN12	0x08dB	//	A段上行通道工作使能12
#define	PARA_A_UCH_EN13	0x08dC	//	A段上行通道工作使能13
#define	PARA_A_UCH_EN14	0x08dD	//	A段上行通道工作使能14
#define	PARA_A_UCH_EN15	0x08dE	//	A段上行通道工作使能15
#define	PARA_A_UCH_EN16	0x08dF	//	A段上行通道工作使能16
#define	PARA_A_DCH_GAIN1	0x0840	//	A段下行选频通道放大器增益1
#define	PARA_A_DCH_GAIN2	0x0841	//	A段下行选频通道放大器增益2
#define	PARA_A_DCH_GAIN3	0x0842	//	A段下行选频通道放大器增益3
#define	PARA_A_DCH_GAIN4	0x0843	//	A段下行选频通道放大器增益4
#define	PARA_A_DCH_GAIN5	0x0844	//	A段下行选频通道放大器增益5
#define	PARA_A_DCH_GAIN6	0x0845	//	A段下行选频通道放大器增益6
#define	PARA_A_DCH_GAIN7	0x0846	//	A段下行选频通道放大器增益7
#define	PARA_A_DCH_GAIN8	0x0847	//	A段下行选频通道放大器增益8
#define	PARA_A_DCH_GAIN9	0x0848	//	A段下行选频通道放大器增益9
#define	PARA_A_DCH_GAIN10	0x0849	//	A段下行选频通道放大器增益10
#define	PARA_A_DCH_GAIN11	0x084A	//	A段下行选频通道放大器增益11
#define	PARA_A_DCH_GAIN12	0x084B	//	A段下行选频通道放大器增益12
#define	PARA_A_DCH_GAIN13	0x084C	//	A段下行选频通道放大器增益13
#define	PARA_A_DCH_GAIN14	0x084D	//	A段下行选频通道放大器增益14
#define	PARA_A_DCH_GAIN15	0x084E	//	A段下行选频通道放大器增益15
#define	PARA_A_DCH_GAIN16	0x084F	//	A段下行选频通道放大器增益16
#define	PARA_A_UCH_GAIN1	0x0850	//	A段上行选频通道放大器增益1
#define	PARA_A_UCH_GAIN2	0x0851	//	A段上行选频通道放大器增益2
#define	PARA_A_UCH_GAIN3	0x0852	//	A段上行选频通道放大器增益3
#define	PARA_A_UCH_GAIN4	0x0853	//	A段上行选频通道放大器增益4
#define	PARA_A_UCH_GAIN5	0x0854	//	A段上行选频通道放大器增益5
#define	PARA_A_UCH_GAIN6	0x0855	//	A段上行选频通道放大器增益6
#define	PARA_A_UCH_GAIN7	0x0856	//	A段上行选频通道放大器增益7
#define	PARA_A_UCH_GAIN8	0x0857	//	A段上行选频通道放大器增益8
#define	PARA_A_UCH_GAIN9	0x0858	//	A段上行选频通道放大器增益9
#define	PARA_A_UCH_GAIN10	0x0859	//	A段上行选频通道放大器增益10
#define	PARA_A_UCH_GAIN11	0x085A	//	A段上行选频通道放大器增益11
#define	PARA_A_UCH_GAIN12	0x085B	//	A段上行选频通道放大器增益12
#define	PARA_A_UCH_GAIN13	0x085C	//	A段上行选频通道放大器增益13
#define	PARA_A_UCH_GAIN14	0x085D	//	A段上行选频通道放大器增益14
#define	PARA_A_UCH_GAIN15	0x085E	//	A段上行选频通道放大器增益15
#define	PARA_A_UCH_GAIN16	0x085F	//	A段上行选频通道放大器增益16
#define	PARA_A_DCH_ATT1	0x0324	//	A段下行数控衰减量1
#define	PARA_A_DCH_ATT2	0	//	A段下行数控衰减量2
#define	PARA_A_DCH_ATT3	0	//	A段下行数控衰减量3
#define	PARA_A_DCH_ATT4	0	//	A段下行数控衰减量4
#define	PARA_A_DCH_ATT5	0	//	A段下行数控衰减量5
#define	PARA_A_DCH_ATT6	0	//	A段下行数控衰减量6
#define	PARA_A_DCH_ATT7	0	//	A段下行数控衰减量7
#define	PARA_A_DCH_ATT8	0	//	A段下行数控衰减量8
#define	PARA_A_DCH_ATT9	0	//	A段下行数控衰减量9
#define	PARA_A_DCH_ATT10	0	//	A段下行数控衰减量10
#define	PARA_A_DCH_ATT11	0	//	A段下行数控衰减量11
#define	PARA_A_DCH_ATT12	0	//	A段下行数控衰减量12
#define	PARA_A_DCH_ATT13	0	//	A段下行数控衰减量13
#define	PARA_A_DCH_ATT14	0	//	A段下行数控衰减量14
#define	PARA_A_DCH_ATT15	0	//	A段下行数控衰减量15
#define	PARA_A_DCH_ATT16	0	//	A段下行数控衰减量16
#define	PARA_A_UCH_ATT1	0x0320	//	A段上行数控衰减量1
#define	PARA_A_UCH_ATT2	0	//	A段上行数控衰减量2
#define	PARA_A_UCH_ATT3	0	//	A段上行数控衰减量3
#define	PARA_A_UCH_ATT4	0	//	A段上行数控衰减量4
#define	PARA_A_UCH_ATT5	0	//	A段上行数控衰减量5
#define	PARA_A_UCH_ATT6	0	//	A段上行数控衰减量6
#define	PARA_A_UCH_ATT7	0	//	A段上行数控衰减量7
#define	PARA_A_UCH_ATT8	0	//	A段上行数控衰减量8
#define	PARA_A_UCH_ATT9	0	//	A段上行数控衰减量9
#define	PARA_A_UCH_ATT10	0	//	A段上行数控衰减量10
#define	PARA_A_UCH_ATT11	0	//	A段上行数控衰减量11
#define	PARA_A_UCH_ATT12	0	//	A段上行数控衰减量12
#define	PARA_A_UCH_ATT13	0	//	A段上行数控衰减量13
#define	PARA_A_UCH_ATT14	0	//	A段上行数控衰减量14
#define	PARA_A_UCH_ATT15	0	//	A段上行数控衰减量15
#define	PARA_A_UCH_ATT16	0	//	A段上行数控衰减量16
#define	PARA_A_DL_PA_GAIN	0	//	A段下行功放增益
#define	PARA_A_UL_PA_GAIN	0	//	A段上行功放增益
#define	PARA_A_TX_PLL_ST	0x8308	//	A段下行PLL状态,287 2为TX_VCO锁定，其他失锁
#define	PARA_A_RX_PLL_ST	0x8300	//	A段上行PLL状态,247 2为RX_VCO锁定，其他失锁
#define	PARA_A_INIT_DA_ST	0	//	初始化A段DA状态,17 1A为锁定+发送接收使能打开，其他异常
#define	PARA_A_BB_PLL_LOCK	0	//	A段BB PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define	PARA_A_FSAT		0	//	A段前端AD输入状态
#define	PARA_A_DSAT		0	//	A段后端DA输出状态
#define	PARA_A_PA_VG_EN	0	//	A段功放栅压状态
#define	PARA_A_PA_VT	0	//	A段功放管电压显示
#define	PARA_A_Modulator_EN	0	//	A段调制器状态
#define	PARA_A_LNA_VT	0	//	A段下行低噪放LNA电压
#define	PARA_A_LNA1_ST		0x8214	//	上行LNA1状态
#define	PARA_A_LNA2_ST		0x8215	//	上行LNA2状态
#define	PARA_A_BUSY_TIME	0x8892	//	A段上行时隙占用率
#define	PARA_A_PRI_ADD 	0xf002	//	A段模块地址(在虹信协议中，高四位为上行地址，低四位为下行地址)
#define	PARA_A_UL_POW_1B	0x831e	//	A段上行输入总功率
#define 	PARA_A_DL_POW_1B	0x8390	//	A段下行输入总功率
#define 	PARA_A_DCH_REC_RF_ATT1          0     //// REC端的下行数控衰减量。即RF端的链路下行衰减量 在rf
#define 	PARA_A_UCH_REC_RF_ATT1          0     //// REC端的上行数控衰减量。即RF端的链路上行衰减量 在rf
#define	PARA_B_CHANNEL_COUNT	0x8889	//	B段支持的通道数
#define	PARA_B_DL_WORK_EN	0x08a0	//	B段下行工作使能
#define	PARA_B_UL_WORK_EN	0x08a1	//	B段上行工作使能
#define	PARA_B_DPOW_MODE	0	//	B段下行功率控制方式
#define	PARA_B_UPOW_MODE	0	//	B段上行功率控制方式
#define	PARA_B_LTHR_EN		0x0770	//	B段上行底噪抑制使能
#define	PARA_B_LTHR_UP		0	//	B段底噪抑制上门限
#define	PARA_B_LTHR_DN		0x08b0	//	B段底噪抑制下门限
#define	PARA_B_DCH_EN1		0x08d0	//	B段下行通道工作使能1
#define	PARA_B_DCH_EN2		0x08d1	//	B段下行通道工作使能2
#define	PARA_B_DCH_EN3		0x08d2	//	B段下行通道工作使能3
#define	PARA_B_DCH_EN4		0x08d3	//	B段下行通道工作使能4
#define	PARA_B_DCH_EN5		0x08d4	//	B段下行通道工作使能5
#define	PARA_B_DCH_EN6		0x08d5	//	B段下行通道工作使能6
#define	PARA_B_DCH_EN7		0x08d6	//	B段下行通道工作使能7
#define	PARA_B_DCH_EN8		0x08d7	//	B段下行通道工作使能8
#define	PARA_B_DCH_EN9		0x08d8	//	B段下行通道工作使能9
#define	PARA_B_DCH_EN10		0x08d9	//	B段下行通道工作使能10
#define	PARA_B_DCH_EN11		0x08dA	//	B段下行通道工作使能11
#define	PARA_B_DCH_EN12		0x08dB	//	B段下行通道工作使能12
#define	PARA_B_DCH_EN13		0x08dC	//	B段下行通道工作使能13
#define	PARA_B_DCH_EN14		0x08dD	//	B段下行通道工作使能14
#define	PARA_B_DCH_EN15		0x08dE	//	B段下行通道工作使能15
#define	PARA_B_DCH_EN16		0x08dF	//	B段下行通道工作使能16
#define	PARA_B_UCH_EN1		0x08d0	//	B段上行通道工作使能1
#define	PARA_B_UCH_EN2		0x08d1	//	B段上行通道工作使能2
#define	PARA_B_UCH_EN3		0x08d2	//	B段上行通道工作使能3
#define	PARA_B_UCH_EN4		0x08d3	//	B段上行通道工作使能4
#define	PARA_B_UCH_EN5		0x08d4	//	B段上行通道工作使能5
#define	PARA_B_UCH_EN6		0x08d5	//	B段上行通道工作使能6
#define	PARA_B_UCH_EN7		0x08d6	//	B段上行通道工作使能7
#define	PARA_B_UCH_EN8		0x08d7	//	B段上行通道工作使能8
#define	PARA_B_UCH_EN9		0x08d8	//	B段上行通道工作使能9
#define	PARA_B_UCH_EN10		0x08d9	//	B段上行通道工作使能10
#define	PARA_B_UCH_EN11		0x08dA	//	B段上行通道工作使能11
#define	PARA_B_UCH_EN12		0x08dB	//	B段上行通道工作使能12
#define	PARA_B_UCH_EN13		0x08dC	//	B段上行通道工作使能13
#define	PARA_B_UCH_EN14		0x08dD	//	B段上行通道工作使能14
#define	PARA_B_UCH_EN15		0x08dE	//	B段上行通道工作使能15
#define	PARA_B_UCH_EN16		0x08dF	//	B段上行通道工作使能16
#define	PARA_B_DCH_GAIN1	0x0840	//	B段下行选频通道放大器增益1
#define	PARA_B_DCH_GAIN2	0x0841	//	B段下行选频通道放大器增益2
#define	PARA_B_DCH_GAIN3	0x0842	//	B段下行选频通道放大器增益3
#define	PARA_B_DCH_GAIN4	0x0843	//	B段下行选频通道放大器增益4
#define	PARA_B_DCH_GAIN5	0x0844	//	B段下行选频通道放大器增益5
#define	PARA_B_DCH_GAIN6	0x0845	//	B段下行选频通道放大器增益6
#define	PARA_B_DCH_GAIN7	0x0846	//	B段下行选频通道放大器增益7
#define	PARA_B_DCH_GAIN8	0x0847	//	B段下行选频通道放大器增益8
#define	PARA_B_DCH_GAIN9	0x0848	//	B段下行选频通道放大器增益9
#define	PARA_B_DCH_GAIN10	0x0849	//	B段下行选频通道放大器增益10
#define	PARA_B_DCH_GAIN11	0x084A	//	B段下行选频通道放大器增益11
#define	PARA_B_DCH_GAIN12	0x084B	//	B段下行选频通道放大器增益12
#define	PARA_B_DCH_GAIN13	0x084C	//	B段下行选频通道放大器增益13
#define	PARA_B_DCH_GAIN14	0x084D	//	B段下行选频通道放大器增益14
#define	PARA_B_DCH_GAIN15	0x084E	//	B段下行选频通道放大器增益15
#define	PARA_B_DCH_GAIN16	0x084F	//	B段下行选频通道放大器增益16
#define	PARA_B_UCH_GAIN1	0x0850	//	B段上行选频通道放大器增益1
#define	PARA_B_UCH_GAIN2	0x0851	//	B段上行选频通道放大器增益2
#define	PARA_B_UCH_GAIN3	0x0852	//	B段上行选频通道放大器增益3
#define	PARA_B_UCH_GAIN4	0x0853	//	B段上行选频通道放大器增益4
#define	PARA_B_UCH_GAIN5	0x0854	//	B段上行选频通道放大器增益5
#define	PARA_B_UCH_GAIN6	0x0855	//	B段上行选频通道放大器增益6
#define	PARA_B_UCH_GAIN7	0x0856	//	B段上行选频通道放大器增益7
#define	PARA_B_UCH_GAIN8	0x0857	//	B段上行选频通道放大器增益8
#define	PARA_B_UCH_GAIN9	0x0858	//	B段上行选频通道放大器增益9
#define	PARA_B_UCH_GAIN10	0x0859	//	B段上行选频通道放大器增益10
#define	PARA_B_UCH_GAIN11	0x085A	//	B段上行选频通道放大器增益11
#define	PARA_B_UCH_GAIN12	0x085B	//	B段上行选频通道放大器增益12
#define	PARA_B_UCH_GAIN13	0x085C	//	B段上行选频通道放大器增益13
#define	PARA_B_UCH_GAIN14	0x085D	//	B段上行选频通道放大器增益14
#define	PARA_B_UCH_GAIN15	0x085E	//	B段上行选频通道放大器增益15
#define	PARA_B_UCH_GAIN16	0x085F	//	B段上行选频通道放大器增益16
#define	PARA_B_DCH_ATT1		0x0324	//	B段下行输出数控衰减量1
#define	PARA_B_DCH_ATT2		0	//	B段下行输出数控衰减量2
#define	PARA_B_DCH_ATT3		0	//	B段下行输出数控衰减量3
#define	PARA_B_DCH_ATT4		0	//	B段下行输出数控衰减量4
#define	PARA_B_DCH_ATT5		0	//	B段下行输出数控衰减量5
#define	PARA_B_DCH_ATT6		0	//	B段下行输出数控衰减量6
#define	PARA_B_DCH_ATT7		0	//	B段下行输出数控衰减量7
#define	PARA_B_DCH_ATT8		0	//	B段下行输出数控衰减量8
#define	PARA_B_DCH_ATT9		0	//	B段下行输出数控衰减量9
#define	PARA_B_DCH_ATT10	0	//	B段下行输出数控衰减量10
#define	PARA_B_DCH_ATT11	0	//	B段下行输出数控衰减量11
#define	PARA_B_DCH_ATT12	0	//	B段下行输出数控衰减量12
#define	PARA_B_DCH_ATT13	0	//	B段下行输出数控衰减量13
#define	PARA_B_DCH_ATT14	0	//	B段下行输出数控衰减量14
#define	PARA_B_DCH_ATT15	0	//	B段下行输出数控衰减量15
#define	PARA_B_DCH_ATT16	0	//	B段下行输出数控衰减量16
#define	PARA_B_UCH_ATT1		0//0x0320	//	B段上行输入数控衰减量1
#define	PARA_B_UCH_ATT2		0	//	B段上行输入数控衰减量2
#define	PARA_B_UCH_ATT3		0	//	B段上行输入数控衰减量3
#define	PARA_B_UCH_ATT4		0	//	B段上行输入数控衰减量4
#define	PARA_B_UCH_ATT5		0	//	B段上行输入数控衰减量5
#define	PARA_B_UCH_ATT6		0	//	B段上行输入数控衰减量6
#define	PARA_B_UCH_ATT7		0	//	B段上行输入数控衰减量7
#define	PARA_B_UCH_ATT8		0	//	B段上行输入数控衰减量8
#define	PARA_B_UCH_ATT9		0	//	B段上行输入数控衰减量9
#define	PARA_B_UCH_ATT10	0	//	B段上行输入数控衰减量10
#define	PARA_B_UCH_ATT11	0	//	B段上行输入数控衰减量11
#define	PARA_B_UCH_ATT12	0	//	B段上行输入数控衰减量12
#define	PARA_B_UCH_ATT13	0	//	B段上行输入数控衰减量13
#define	PARA_B_UCH_ATT14	0	//	B段上行输入数控衰减量14
#define	PARA_B_UCH_ATT15	0	//	B段上行输入数控衰减量15
#define	PARA_B_UCH_ATT16	0	//	B段上行输入数控衰减量16
#define	PARA_B_DL_PA_GAIN	0	//	B段下行功放增益
#define	PARA_B_UL_PA_GAIN	0	//	B段上行功放增益
#define	PARA_B_TX_PLL_ST	0x8308	//	B段下行PLL状态,287 2为TX_VCO锁定，其他失锁
#define	PARA_B_RX_PLL_ST	0x8300	//	B段上行PLL状态,247 2为RX_VCO锁定，其他失锁
#define	PARA_B_INIT_DA_ST	0	//	初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
#define	PARA_B_BB_PLL_LOCK	0	//	B段BB PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define	PARA_B_FSAT		0	//	B段前端AD输入状态
#define	PARA_B_DSAT		0	//	B段后端DA输出状态
#define	PARA_B_PA_VG_EN	0	//	B段功放栅压状态
#define	PARA_B_PA_VT	0	//	B段功放管电压显示
#define	PARA_B_Modulator_EN	0	//	B段调制器状态
#define	PARA_B_LNA_VT	0	//	B段下行低噪放LNA电压
#define	PARA_B_LNA1_ST		0x8214	//	上行LNA1状态
#define	PARA_B_LNA2_ST		0x8215	//	上行LNA2状态
#define	PARA_B_BUSY_TIME	0x8892	//	B段上行时隙占用率
#define	PARA_B_PRI_ADD 		0xf002	//	B段模块地址(在虹信协议中，高四位为上行地址，低四位为下行地址)
#define	PARA_B_UL_POW_1B	0x831e	//	B段上行输入总功率
#define 	PARA_B_DL_POW_1B	0x8390	//	B段下行输入总功率
#define 	PARA_B_DCH_REC_RF_ATT1          0     //// REC端的下行数控衰减量。即RF端的链路下行衰减量 在rf
#define 	PARA_B_UCH_REC_RF_ATT1          0     //// REC端的上行数控衰减量。即RF端的链路上行衰减量  在rf
#define	PARA_C_CHANNEL_COUNT	0x8889	//	C段支持的通道数
#define	PARA_C_DL_WORK_EN	0x08a0	//	C段下行工作使能
#define	PARA_C_UL_WORK_EN	0x08a1	//	C段上行工作使能
#define	PARA_C_DPOW_MODE	0	//	C段下行功率控制方式
#define	PARA_C_UPOW_MODE	0	//	C段上行功率控制方式
#define	PARA_C_LTHR_EN		0x0770	//	C段上行底噪抑制使能
#define	PARA_C_LTHR_UP		0	//	C段底噪抑制上门限
#define	PARA_C_LTHR_DN		0x08b0	//	C段底噪抑制下门限
#define	PARA_C_DCH_EN1		0x08d0	//	C段下行通道工作使能1
#define	PARA_C_DCH_EN2		0x08d1	//	C段下行通道工作使能2
#define	PARA_C_DCH_EN3		0x08d2	//	C段下行通道工作使能3
#define	PARA_C_DCH_EN4		0x08d3	//	C段下行通道工作使能4
#define	PARA_C_DCH_EN5		0x08d4	//	C段下行通道工作使能5
#define	PARA_C_DCH_EN6		0x08d5	//	C段下行通道工作使能6
#define	PARA_C_DCH_EN7		0x08d6	//	C段下行通道工作使能7
#define	PARA_C_DCH_EN8		0x08d7	//	C段下行通道工作使能8
#define	PARA_C_DCH_EN9		0x08d8	//	C段下行通道工作使能9
#define	PARA_C_DCH_EN10		0x08d9	//	C段下行通道工作使能10
#define	PARA_C_UCH_EN1		0x08d0	//	C段上行通道工作使能1
#define	PARA_C_UCH_EN2		0x08d1	//	C段上行通道工作使能2
#define	PARA_C_UCH_EN3		0x08d2	//	C段上行通道工作使能3
#define	PARA_C_UCH_EN4		0x08d3	//	C段上行通道工作使能4
#define	PARA_C_UCH_EN5		0x08d4	//	C段上行通道工作使能5
#define	PARA_C_UCH_EN6		0x08d5	//	C段上行通道工作使能6
#define	PARA_C_UCH_EN7		0x08d6	//	C段上行通道工作使能7
#define	PARA_C_UCH_EN8		0x08d7	//	C段上行通道工作使能8
#define	PARA_C_UCH_EN9		0x08d8	//	C段上行通道工作使能9
#define	PARA_C_UCH_EN10		0x08d9	//	C段上行通道工作使能10
#define	PARA_C_DCH_GAIN1	0x0840	//	C段下行选频通道放大器增益1
#define	PARA_C_DCH_GAIN2	0x0841	//	C段下行选频通道放大器增益2
#define	PARA_C_DCH_GAIN3	0x0842	//	C段下行选频通道放大器增益3
#define	PARA_C_DCH_GAIN4	0x0843	//	C段下行选频通道放大器增益4
#define	PARA_C_DCH_GAIN5	0x0844	//	C段下行选频通道放大器增益5
#define	PARA_C_DCH_GAIN6	0x0845	//	C段下行选频通道放大器增益6
#define	PARA_C_DCH_GAIN7	0x0846	//	C段下行选频通道放大器增益7
#define	PARA_C_DCH_GAIN8	0x0847	//	C段下行选频通道放大器增益8
#define	PARA_C_DCH_GAIN9	0x0848	//	C段下行选频通道放大器增益9
#define	PARA_C_DCH_GAIN10	0x0849	//	C段下行选频通道放大器增益10
#define 	PARA_C_DCH_GAIN11 	0	// 	C段下行选频通道放大器增益11
#define 	PARA_C_DCH_GAIN12 	0	// 	C段下行选频通道放大器增益12
#define 	PARA_C_DCH_GAIN13 	0	// 	C段下行选频通道放大器增益13
#define 	PARA_C_DCH_GAIN14 	0	// 	C段下行选频通道放大器增益14
#define 	PARA_C_DCH_GAIN15 	0	// 	C段下行选频通道放大器增益15
#define 	PARA_C_DCH_GAIN16 	0	// 	C段下行选频通道放大器增益16
#define	PARA_C_UCH_GAIN1	0x0850	//	C段上行选频通道放大器增益1
#define	PARA_C_UCH_GAIN2	0x0851	//	C段上行选频通道放大器增益2
#define	PARA_C_UCH_GAIN3	0x0852	//	C段上行选频通道放大器增益3
#define	PARA_C_UCH_GAIN4	0x0853	//	C段上行选频通道放大器增益4
#define	PARA_C_UCH_GAIN5	0x0854	//	C段上行选频通道放大器增益5
#define	PARA_C_UCH_GAIN6	0x0855	//	C段上行选频通道放大器增益6
#define	PARA_C_UCH_GAIN7	0x0856	//	C段上行选频通道放大器增益7
#define	PARA_C_UCH_GAIN8	0x0857	//	C段上行选频通道放大器增益8
#define	PARA_C_UCH_GAIN9	0x0858	//	C段上行选频通道放大器增益9
#define	PARA_C_UCH_GAIN10	0x0859	//	C段上行选频通道放大器增益10
#define	PARA_C_UCH_GAIN11	0	//	C段上行选频通道放大器增益11
#define	PARA_C_UCH_GAIN12	0	//	C段上行选频通道放大器增益12
#define	PARA_C_UCH_GAIN13	0	//	C段上行选频通道放大器增益13
#define	PARA_C_UCH_GAIN14	0	//	C段上行选频通道放大器增益14
#define	PARA_C_UCH_GAIN15	0	//	C段上行选频通道放大器增益15
#define	PARA_C_UCH_GAIN16	0	//	C段上行选频通道放大器增益16
#define	PARA_C_DCH_ATT1		0x0324	//	C段下行输出数控衰减量1
#define	PARA_C_DCH_ATT2		0	//	C段下行输出数控衰减量2
#define	PARA_C_DCH_ATT3		0	//	C段下行输出数控衰减量3
#define	PARA_C_DCH_ATT4		0	//	C段下行输出数控衰减量4
#define	PARA_C_DCH_ATT5		0	//	C段下行输出数控衰减量5
#define	PARA_C_DCH_ATT6		0	//	C段下行输出数控衰减量6
#define	PARA_C_DCH_ATT7		0	//	C段下行输出数控衰减量7
#define	PARA_C_DCH_ATT8		0	//	C段下行输出数控衰减量8
#define	PARA_C_DCH_ATT9		0	//	C段下行输出数控衰减量9
#define	PARA_C_DCH_ATT10	0	//	C段下行输出数控衰减量10
#define	PARA_C_DCH_ATT11	0	//	C段下行输出数控衰减量11
#define	PARA_C_DCH_ATT12	0	//	C段下行输出数控衰减量12
#define	PARA_C_DCH_ATT13	0	//	C段下行输出数控衰减量13
#define	PARA_C_DCH_ATT14	0	//	C段下行输出数控衰减量14
#define	PARA_C_DCH_ATT15	0	//	C段下行输出数控衰减量15
#define	PARA_C_DCH_ATT16	0	//	C段下行输出数控衰减量16
#define	PARA_C_UCH_ATT1		0//0x0320	//	C段上行输入数控衰减量1
#define	PARA_C_UCH_ATT2		0	//	C段上行输入数控衰减量2
#define	PARA_C_UCH_ATT3		0	//	C段上行输入数控衰减量3
#define	PARA_C_UCH_ATT4		0	//	C段上行输入数控衰减量4
#define	PARA_C_UCH_ATT5		0	//	C段上行输入数控衰减量5
#define	PARA_C_UCH_ATT6		0	//	C段上行输入数控衰减量6
#define	PARA_C_UCH_ATT7		0	//	C段上行输入数控衰减量7
#define	PARA_C_UCH_ATT8		0	//	C段上行输入数控衰减量8
#define	PARA_C_UCH_ATT9		0	//	C段上行输入数控衰减量9
#define	PARA_C_UCH_ATT10	0	//	C段上行输入数控衰减量10
#define	PARA_C_UCH_ATT11	0	//	C段上行输入数控衰减量11
#define	PARA_C_UCH_ATT12	0	//	C段上行输入数控衰减量12
#define	PARA_C_UCH_ATT13	0	//	C段上行输入数控衰减量13
#define	PARA_C_UCH_ATT14	0	//	C段上行输入数控衰减量14
#define	PARA_C_UCH_ATT15	0	//	C段上行输入数控衰减量15
#define	PARA_C_UCH_ATT16	0	//	C段上行输入数控衰减量16
#define	PARA_C_DL_PA_GAIN	0	//	C段下行功放增益
#define	PARA_C_UL_PA_GAIN	0	//	C段上行功放增益
#define	PARA_C_TX_PLL_ST	0x8308	//	C段下行PLL状态,287 2为TX_VCO锁定，其他失锁
#define	PARA_C_RX_PLL_ST	0x8300	//	C段上行PLL状态,247 2为RX_VCO锁定，其他失锁
#define	PARA_C_INIT_DA_ST	0	//	C初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
#define	PARA_C_BB_PLL_LOCK	0	//	C段BB PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define	PARA_C_FSAT		0	//	C段前端AD输入状态
#define	PARA_C_DSAT		0	//	C段后端DA输出状态
#define	PARA_C_PA_VG_EN	0	//	C段功放栅压状态
#define	PARA_C_PA_VT	0	//	C段功放管电压显示
#define	PARA_C_Modulator_EN	0	//	C段调制器状态
#define	PARA_C_LNA_VT	0	//	C段下行低噪放LNA电压
#define	PARA_C_LNA1_ST		0x8214	//	C上行LNA1状态
#define	PARA_C_LNA2_ST		0x8215	//	C上行LNA2状态
#define	PARA_C_BUSY_TIME	0x8892	//	C段上行时隙占用率
#define	PARA_C_PRI_ADD 		0xf002	//	C段模块地址(在虹信协议中，高四位为上行地址，低四位为下行地址)
#define	PARA_C_UL_POW_1B	0x831e	//	C段上行输入总功率
#define 	PARA_C_DL_POW_1B	0x8390	//	C段下行输入总功率
#define 	PARA_C_DCH_REC_RF_ATT1          0     //// REC端的下行数控衰减量。即RF端的链路下行衰减量 在rf
#define 	PARA_C_UCH_REC_RF_ATT1          0     //// REC端的上行数控衰减量。即RF端的链路上行衰减量  在rf
#define	PARA_D_CHANNEL_COUNT	0x8889	//	D段支持的通道数
#define	PARA_D_DL_WORK_EN	0x08a0	//	D段下行工作使能
#define	PARA_D_UL_WORK_EN	0x08a1	//	D段上行工作使能
#define	PARA_D_DPOW_MODE	0	//	D段下行功率控制方式
#define	PARA_D_UPOW_MODE	0	//	D段上行功率控制方式
#define	PARA_D_LTHR_EN		0x0770	//	D段上行底噪抑制使能
#define	PARA_D_LTHR_UP		0	//	D段底噪抑制上门限
#define	PARA_D_LTHR_DN		0x08b0	//	D段底噪抑制下门限
#define	PARA_D_DCH_EN1		0x08d0	//	D段下行通道工作使能1
#define	PARA_D_DCH_EN2		0x08d1	//	D段下行通道工作使能2
#define	PARA_D_DCH_EN3		0x08d2	//	D段下行通道工作使能3
#define	PARA_D_DCH_EN4		0x08d3	//	D段下行通道工作使能4
#define	PARA_D_DCH_EN5		0x08d4	//	D段下行通道工作使能5
#define	PARA_D_DCH_EN6		0x08d5	//	D段下行通道工作使能6
#define	PARA_D_DCH_EN7		0x08d6	//	D段下行通道工作使能7
#define	PARA_D_DCH_EN8		0x08d7	//	D段下行通道工作使能8
#define	PARA_D_DCH_EN9		0x08d8	//	D段下行通道工作使能9
#define	PARA_D_DCH_EN10	0x08d9	//	D段下行通道工作使能10
#define	PARA_D_UCH_EN1		0x08d0	//	D段上行通道工作使能1
#define	PARA_D_UCH_EN2		0x08d1	//	D段上行通道工作使能2
#define	PARA_D_UCH_EN3		0x08d2	//	D段上行通道工作使能3
#define	PARA_D_UCH_EN4		0x08d3	//	D段上行通道工作使能4
#define	PARA_D_UCH_EN5		0x08d4	//	D段上行通道工作使能5
#define	PARA_D_UCH_EN6		0x08d5	//	D段上行通道工作使能6
#define	PARA_D_UCH_EN7		0x08d6	//	D段上行通道工作使能7
#define	PARA_D_UCH_EN8		0x08d7	//	D段上行通道工作使能8
#define	PARA_D_UCH_EN9		0x08d8	//	D段上行通道工作使能9
#define	PARA_D_UCH_EN10	0x08d9	//	D段上行通道工作使能10
#define	PARA_D_DCH_GAIN1	0x0840	//	D段下行选频通道放大器增益1
#define	PARA_D_DCH_GAIN2	0x0841	//	D段下行选频通道放大器增益2
#define	PARA_D_DCH_GAIN3	0x0842	//	D段下行选频通道放大器增益3
#define	PARA_D_DCH_GAIN4	0x0843	//	D段下行选频通道放大器增益4
#define	PARA_D_DCH_GAIN5	0x0844	//	D段下行选频通道放大器增益5
#define	PARA_D_DCH_GAIN6	0x0845	//	D段下行选频通道放大器增益6
#define	PARA_D_DCH_GAIN7	0x0846	//	D段下行选频通道放大器增益7
#define	PARA_D_DCH_GAIN8	0x0847	//	D段下行选频通道放大器增益8
#define	PARA_D_DCH_GAIN9	0x0848	//	D段下行选频通道放大器增益9
#define	PARA_D_DCH_GAIN10	0x0849	//	D段下行选频通道放大器增益10
#define	PARA_D_DCH_GAIN11	0	//	D段下行选频通道放大器增益11
#define	PARA_D_DCH_GAIN12	0	//	D段下行选频通道放大器增益12
#define	PARA_D_DCH_GAIN13	0	//	D段下行选频通道放大器增益13
#define	PARA_D_DCH_GAIN14	0	//	D段下行选频通道放大器增益14
#define	PARA_D_DCH_GAIN15	0	//	D段下行选频通道放大器增益15
#define	PARA_D_DCH_GAIN16	0	//	D段下行选频通道放大器增益16
#define	PARA_D_UCH_GAIN1	0x0850	//	D段上行选频通道放大器增益1
#define	PARA_D_UCH_GAIN2	0x0851	//	D段上行选频通道放大器增益2
#define	PARA_D_UCH_GAIN3	0x0852	//	D段上行选频通道放大器增益3
#define	PARA_D_UCH_GAIN4	0x0853	//	D段上行选频通道放大器增益4
#define	PARA_D_UCH_GAIN5	0x0854	//	D段上行选频通道放大器增益5
#define	PARA_D_UCH_GAIN6	0x0855	//	D段上行选频通道放大器增益6
#define	PARA_D_UCH_GAIN7	0x0856	//	D段上行选频通道放大器增益7
#define	PARA_D_UCH_GAIN8	0x0857	//	D段上行选频通道放大器增益8
#define	PARA_D_UCH_GAIN9	0x0858	//	D段上行选频通道放大器增益9
#define	PARA_D_UCH_GAIN10	0x0859	//	D段上行选频通道放大器增益10
#define	PARA_D_UCH_GAIN11	0	//	D段上行选频通道放大器增益11
#define	PARA_D_UCH_GAIN12	0	//	D段上行选频通道放大器增益12
#define	PARA_D_UCH_GAIN13	0	//	D段上行选频通道放大器增益13
#define	PARA_D_UCH_GAIN14	0	//	D段上行选频通道放大器增益14
#define	PARA_D_UCH_GAIN15	0	//	D段上行选频通道放大器增益15
#define	PARA_D_UCH_GAIN16	0	//	D段上行选频通道放大器增益16
#define	PARA_D_DCH_ATT1		0x0324	//	D段下行输出数控衰减量1
#define	PARA_D_DCH_ATT2		0	//	D段下行输出数控衰减量2
#define	PARA_D_DCH_ATT3		0	//	D段下行输出数控衰减量3
#define	PARA_D_DCH_ATT4		0	//	D段下行输出数控衰减量4
#define	PARA_D_DCH_ATT5		0	//	D段下行输出数控衰减量5
#define	PARA_D_DCH_ATT6		0	//	D段下行输出数控衰减量6
#define	PARA_D_DCH_ATT7		0	//	D段下行输出数控衰减量7
#define	PARA_D_DCH_ATT8		0	//	D段下行输出数控衰减量8
#define	PARA_D_DCH_ATT9		0	//	D段下行输出数控衰减量9
#define	PARA_D_DCH_ATT10	0	//	D段下行输出数控衰减量10
#define	PARA_D_DCH_ATT11	0	//	D段下行输出数控衰减量11
#define	PARA_D_DCH_ATT12	0	//	D段下行输出数控衰减量12
#define	PARA_D_DCH_ATT13	0	//	D段下行输出数控衰减量13
#define	PARA_D_DCH_ATT14	0	//	D段下行输出数控衰减量14
#define	PARA_D_DCH_ATT15	0	//	D段下行输出数控衰减量15
#define	PARA_D_DCH_ATT16	0	//	D段下行输出数控衰减量16
#define	PARA_D_UCH_ATT1		0//0x0320	//	D段上行输入数控衰减量1
#define	PARA_D_UCH_ATT2		0	//	D段上行输入数控衰减量2
#define	PARA_D_UCH_ATT3		0	//	D段上行输入数控衰减量3
#define	PARA_D_UCH_ATT4		0	//	D段上行输入数控衰减量4
#define	PARA_D_UCH_ATT5		0	//	D段上行输入数控衰减量5
#define	PARA_D_UCH_ATT6		0	//	D段上行输入数控衰减量6
#define	PARA_D_UCH_ATT7		0	//	D段上行输入数控衰减量7
#define	PARA_D_UCH_ATT8		0	//	D段上行输入数控衰减量8
#define	PARA_D_UCH_ATT9		0	//	D段上行输入数控衰减量9
#define	PARA_D_UCH_ATT10	0	//	D段上行输入数控衰减量10
#define	PARA_D_UCH_ATT11	0	//	D段上行输入数控衰减量11
#define	PARA_D_UCH_ATT12	0	//	D段上行输入数控衰减量12
#define	PARA_D_UCH_ATT13	0	//	D段上行输入数控衰减量13
#define	PARA_D_UCH_ATT14	0	//	D段上行输入数控衰减量14
#define	PARA_D_UCH_ATT15	0	//	D段上行输入数控衰减量15
#define	PARA_D_UCH_ATT16	0	//	D段上行输入数控衰减量16
#define	PARA_D_DL_PA_GAIN	0	//	D段下行功放增益
#define	PARA_D_UL_PA_GAIN	0	//	D段上行功放增益
#define	PARA_D_TX_PLL_ST	0x8308	//	D段下行PLL状态,287 2为TX_VCO锁定，其他失锁
#define	PARA_D_RX_PLL_ST	0x8300	//	D段上行PLL状态,247 2为RX_VCO锁定，其他失锁
#define	PARA_D_INIT_DA_ST	0	//	D初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
#define	PARA_D_BB_PLL_LOCK	0	//	D段BB PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define	PARA_D_FSAT		0	//	D段前端AD输入状态
#define	PARA_D_DSAT		0	//	D段后端DA输出状态
#define	PARA_D_PA_VG_EN	0	//	D段功放栅压状态
#define	PARA_D_PA_VT	0	//	D段功放管电压显示
#define	PARA_D_Modulator_EN	0	//	D段调制器状态
#define	PARA_D_LNA_VT	0	//	D段下行低噪放LNA电压
#define	PARA_D_LNA1_ST		0x8214	//	D上行LNA1状态
#define	PARA_D_LNA2_ST		0x8215	//	D上行LNA2状态
#define	PARA_D_BUSY_TIME	0x8892	//	D段上行时隙占用率
#define	PARA_D_PRI_ADD 		0xf002	//	D段模块地址(在虹信协议中，高四位为上行地址，低四位为下行地址)
#define	PARA_D_UL_POW_1B	0x831e	//	D段上行输入总功率
#define 	PARA_D_DL_POW_1B	0x8390	//	D段下行输入总功率
#define 	PARA_D_DCH_REC_RF_ATT1          0     //// REC端的下行数控衰减量。即RF端的链路下行衰减量 在rf
#define 	PARA_D_UCH_REC_RF_ATT1          0     //// REC端的上行数控衰减量。即RF端的链路上行衰减量  在rf
#define	PARA_FP1_EN	0x0927	//	光口发送使能1
#define	PARA_FP2_EN	0x0928	//	光口发送使能2
#define	PARA_FP3_EN	0x0929	//	光口发送使能3
#define	PARA_FP4_EN	0x092A	//	光口发送使能4
#define	PARA_FP5_EN	0x092B	//	光口发送使能5
#define	PARA_FP6_EN	0x092C	//	光口发送使能6
#define	PARA_FP7_EN	0x092D	//	光口发送使能7
#define	PARA_FP8_EN	0x092E	//	光口发送使能8
#define	PARA_FP9_EN	0x0	//	光口发送使能9
#define	PARA_FP10_EN	0x0	//	光口发送使能10
#define	PARA_FP11_EN	0x0	//	光口发送使能11
#define	PARA_FP12_EN	0x0	//	光口发送使能12
#define	PARA_FP13_EN	0x0	//	光口发送使能13
#define	PARA_FP14_EN	0x0	//	光口发送使能14
#define	PARA_FP15_EN	0x0	//	光口发送使能15
#define	PARA_FP16_EN	0x0	//	光口发送使能16
#define	PARA_FP1_ON_POS	0x8568	//	光口在位状态1, 0-在位	
#define	PARA_FP2_ON_POS	0x8569	//	光口在位状态2, 0-在位	
#define	PARA_FP3_ON_POS	0x856A	//	光口在位状态3, 0-在位	
#define	PARA_FP4_ON_POS	0x856B	//	光口在位状态4, 0-在位	
#define	PARA_FP5_ON_POS	0x856C	//	光口在位状态5, 0-在位	
#define	PARA_FP6_ON_POS	0x856D	//	光口在位状态6, 0-在位	
#define	PARA_FP7_ON_POS	0x856E	//	光口在位状态7, 0-在位	
#define	PARA_FP8_ON_POS	0x856F	//	光口在位状态8, 0-在位	
#define	PARA_FP9_ON_POS	0x8568	//	光口在位状态9, 0-在位	
#define	PARA_FP10_ON_POS	0x8569	//	光口在位状态10, 0-在位	
#define	PARA_FP11_ON_POS	0x856a	//	光口在位状态11, 0-在位	
#define	PARA_FP12_ON_POS	0x856b	//	光口在位状态12, 0-在位	
#define	PARA_FP13_ON_POS	0x856c	//	光口在位状态13, 0-在位	
#define	PARA_FP14_ON_POS	0x856d	//	光口在位状态14, 0-在位
#define	PARA_FP15_ON_POS	0x856e	//	光口在位状态15, 0-在位
#define	PARA_FP16_ON_POS	0x856f	//	光口在位状态16, 0-在位
#define	PARA_FP1_LOS	0x8738//0x8730	//	光口1信号丢失状态	
#define	PARA_FP2_LOS	0x8739//0x8731	//	光口2信号丢失状态	
#define	PARA_FP3_LOS	0x873a//0x8732	//	光口3信号丢失状态	
#define	PARA_FP4_LOS	0x873b//0x8733	//	光口4信号丢失状态	
#define	PARA_FP5_LOS	0x873c//0x8734	//	光口5信号丢失状态	
#define	PARA_FP6_LOS	0x873d//0x8735	//	光口6信号丢失状态	
#define	PARA_FP7_LOS	0x8598//0x8736	//	光口7信号丢失状态	
#define	PARA_FP8_LOS	0x8599//0x8737	//	光口8信号丢失状态	
#define	PARA_FP9_LOS	0//0x8738	//	光口9信号丢失状态
#define	PARA_FP10_LOS	0//0x8739	//	光口10信号丢失状态	
#define	PARA_FP11_LOS	0//0x873a	//	光口11信号丢失状态	
#define	PARA_FP12_LOS	0//0x873b	//	光口12信号丢失状态	
#define	PARA_FP13_LOS	0//0x873c	//	光口13信号丢失状态
#define	PARA_FP14_LOS	0//0x873d	//	光口14信号丢失状态
#define	PARA_FP15_LOS	0//0x873e	//	光口15信号丢失状态
#define	PARA_FP16_LOS	0//0x873f	//	光口16信号丢失状态
#define	PARA_FP1_LOF	0x878a//0x8780	//	光口1帧丢失状态	
#define	PARA_FP2_LOF	0x878b//0x8781	//	光口2帧丢失状态	
#define	PARA_FP3_LOF	0x878c//0x8782	//	光口3帧丢失状态	
#define	PARA_FP4_LOF	0x878d//0x8783	//	光口4帧丢失状态	
#define	PARA_FP5_LOF	0x87ab//0x8784	//	光口5帧丢失状态	
#define	PARA_FP6_LOF	0x87ac//0x8785	//	光口6帧丢失状态	
#define	PARA_FP7_LOF	0x87ad//0x8786	//	光口7帧丢失状态	
#define	PARA_FP8_LOF	0x87ae//0x8787	//	光口8帧丢失状态	
#define	PARA_FP9_LOF	0//0x8788	//	光口9帧丢失状态	
#define	PARA_FP10_LOF	0//0x8789	//	光口10帧丢失状态	
#define	PARA_FP11_LOF	0//0x878a	//	光口11帧丢失状态	
#define	PARA_FP12_LOF	0//0x878b	//	光口12帧丢失状态	
#define	PARA_FP13_LOF	0//0x878c	//	光口13帧丢失状态
#define	PARA_FP14_LOF	0//0x878d	//	光口14帧丢失状态
#define	PARA_FP15_LOF	0//0x878e	//	光口15帧丢失状态
#define	PARA_FP16_LOF	0//0x878f	//	光口16帧丢失状态
#define	PARA_OPT_LOF	0//0x87ad	//	帧丢失状态
#define	PARA_SERDES1_PLL_ST	0x878e	//	SerDes芯片PLL状态1	
#define	PARA_SERDES2_PLL_ST	0x878f	//	SerDes芯片PLL状态2	
#define	PARA_SERDES3_PLL_ST	0x8790	//	SerDes芯片PLL状态3	
#define	PARA_SERDES4_PLL_ST	0x8791	//	SerDes芯片PLL状态4	
#define	PARA_SERDES5_PLL_ST	0x8898	//	SerDes芯片PLL状态5	
#define	PARA_SERDES6_PLL_ST	0x8899	//	SerDes芯片PLL状态6	
#define	PARA_SERDES7_PLL_ST	0x889a	//	SerDes芯片PLL状态7	
#define	PARA_SERDES8_PLL_ST	0x889b	//	SerDes芯片PLL状态8	
#define	PARA_SERDES9_PLL_ST	0x85a8	//	SerDes芯片PLL状态9	
#define	PARA_SERDES10_PLL_ST	0x85a9	//	SerDes芯片PLL状态10	
#define	PARA_SERDES11_PLL_ST	0x85aa	//	SerDes芯片PLL状态11	
#define	PARA_SERDES12_PLL_ST	0x85ab	//	SerDes芯片PLL状态12	
#define	PARA_SERDES13_PLL_ST	0x85ac	//	SerDes芯片PLL状态13
#define	PARA_SERDES14_PLL_ST	0x85ad	//	SerDes芯片PLL状态14
#define	PARA_SERDES15_PLL_ST	0x85ae	//	SerDes芯片PLL状态15
#define	PARA_SERDES16_PLL_ST	0x85af	//	SerDes芯片PLL状态16
#define	PARA_TOPO_CHG_ALM	0x873F//0x87af	//	环路状态告警
#define	PARA_BER_ALARM	0//0x87ae	//	误码率偏高告警
#define	PARA_LOAD_FPGA_ST	0x8854	//	加载FPGA状态
#define	PARA_FPGA_CLK_ST	0x8851	//	FPGA本振状态
#define	PARA_INIT_CLK_ST	0	//	初始化时钟状态
#define	PARA_INIT_AD_ST	0	//	初始化AD状态
#define	PARA_INIT_FB_AD_ST	0	//	初始化反馈AD状态
#define	PARA_CLK_PLL_ST	0x884e	//	CLK PLL状态
#define	PARA_CLK_REF_ST	0x884f	//	CLK 参考状态
#define	PARA_RE_NODE_MODE	0x889d	//	RE节点模式
#define	PARA_BOARD_TEMP	0x8844	//	单板温度
#define	PARA_CLK_VCO_VT	0	//	时钟VCO电压
#define	PARA_PWR_9V0_VT	0	//	9V电源电压
#define	PARA_PWR_5V5_VT	0	//	5.5V电源电压
#define	PARA_PWR_3V6_VT	0	//	3.6V电源电压
#define	PARA_PWR_1V2_VT	0	//	1.2V电源电压
#define	PARA_PWR_2V5_VT	0	//	1.2V电源电压
#define	PARA_PRI_PROTOCAL_V	0xf003	//	协议版本
#define	PARA_MODULE_HRI_ID	0	//	ID
#define 	PARA_WORK_ERROR	0	// 系统工作状态，1-有故障
#define 	PARA_TRAFFIC_END	0x88ac	// 话务量统计结束标志
#define 	PARA_DELAY_MODE	0x098f	// 	延时模式: 0-手动, 1-自动
#define	PARA_TD_SYNC_ST			0x862a		// TD同步状态: 1-已同步，0-未同步
#define	PARA_TD_WORK_MODE 		0x060c	// [WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开, 每次上电后清零			
#define 	PARA_TD_T0_UD		0x08a0	// TD时隙0上下行标志:0-上行，1-下行			
#define 	PARA_TD_T1_UD		0x08a1	// TD时隙1上下行标志:0-上行，1-下行			
#define 	PARA_TD_T2_UD		0x08a2	// TD时隙2上下行标志:0-上行，1-下行			
#define 	PARA_TD_T3_UD		0x08a3	// TD时隙3上下行标志:0-上行，1-下行			
#define 	PARA_TD_T4_UD		0x08a4	// TD时隙4上下行标志:0-上行，1-下行			
#define 	PARA_TD_T5_UD		0x08a5	// TD时隙5上下行标志:0-上行，1-下行			
#define 	PARA_TD_T6_UD		0x08a6	// TD时隙6上下行标志:0-上行，1-下行			
#define	PARA_POWERUP_ST		0x8852	// 	数字板上电状态,每次启动时置1
#define	PARA_LOW_POWER			0x88ff//0x08ad	//	低功耗模式:1-低功耗;	0-正常		国人 x0778   由软件初始化，此宏只作为参考
#define 	PARA_THR_PORT		0		// 	透传端口选择0-485B, 1-RS232
#define	PARA_THR_BAUD		0		//	透传端口波特率 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define	PARA_CTRL_BAUD	0		//	控制端口波特率 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define	PARA_WLAN_CONN_ST1		0x87b2	// WLAN口状态1: 0-正常，1-异常
#define	PARA_WLAN_CONN_ST2		0x87b3	// WLAN口状态2: 0-正常，1-异常
#define	PARA_WLAN_CONN_ST3		0x87b4	// WLAN口状态3: 0-正常，1-异常
#define	PARA_WLAN_CONN_ST4		0x87b7	// WLAN口状态4: 0-正常，1-异常
#define	PARA_WLAN_SPEED1			0x87b8	// WLAN口速度1: 0：10M  1：100M  2：1000M
#define	PARA_WLAN_SPEED2			0x87b9		// WLAN口速度1: 0：10M  1：100M  2：1000M
#define	PARA_WLAN_SPEED3			0x87ba		// WLAN口速度1: 0：10M  1：100M  2：1000M
#define	PARA_WLAN_SPEED4			0x87bb		// WLAN口速度1: 0：10M  1：100M  2：1000M
#define	PARA_GSM_BW_SEL			0		// 宽带版本GSM带宽选择: 0-6M, 1-20M, 2-24M, 3-25M, 其他无效
#define	PARA_HX_DET_UADDR 0 // 虹信DET模块上行地址, 高4位为B段, 低四位为A段
#define	PARA_HX_LNA_UADDR 0 // 虹信LNA模块上行地址, 高4位为B段, 低四位为A段
#define	PARA_HX_DET_DADDR 0 // 虹信DET模块下行地址, 高4位为B段, 低四位为A段
#define	PARA_HX_LNA_DADDR 0 // 虹信LNA模块下行地址, 高4位为B段, 低四位为A段
#define 	PARA_FPS_AUTO_SCAN		0x0931		// 自动频点搜索功能使能:1-自动搜索和设置频点, 0-手动搜索
#define 	PARA_FPS_SWITCH_THD 		0 		// 自动频点搜索的BCCH功率切换门限
#define 	PARA_FPS_MOSVC_SEL		0x0925	// 频点搜索: 运营商选择: 0-中移动, 1-中联通, 2-中移动, 255-自动选择
#define	PARA_FPS_RFRANGE_SEL	0x0924	// 频点搜索: 频宽选择(忽略,以模块制式为准): 0-全频段, 1-900MHz, 2-1800MHz
#define 	PARA_FPS_BS_ID			0x8959	// 频点搜索: 基站识别码
#define	PARA_FPS_CA_COUNT		0x895b	// 频点搜索: 有效信道数
#define	PARA_FPS_BCCH_LK_ST		0x895c	// 频点搜索: 锁定BCCH状态: 1-锁定, 0-失败
#define	PARA_FPS_MOSVC_LK_ST		0x895d	// 频点搜索: 锁定运营商状态: 1-锁定, 0-失败
#define	PARA_FPS_RFRANGE_LK_ST	0x895e	// 频点搜索: 锁定频带状态: 1-锁定, 0-失败
#define	PARA_FPS_BCCH_POW_M		0x8960	// 频点搜索: 主小区BCCH接收强度
#define	PARA_FPS_BCCH_POW_1		0x8961	// 频点搜索: 邻小区1BCCH接收强度
#define	PARA_FPS_BCCH_POW_2		0x8962	// 频点搜索: 邻小区2BCCH接收强度
#define	PARA_FPS_BCCH_POW_3		0x8963	// 频点搜索: 邻小区3BCCH接收强度
#define	PARA_FPS_BCCH_POW_4		0x8964	// 频点搜索: 邻小区4BCCH接收强度
#define	PARA_FPS_BCCH_POW_5		0x8965	// 频点搜索: 邻小区5BCCH接收强度
#define	PARA_FPS_BCCH_POW_6		0x8966	// 频点搜索: 邻小区6BCCH接收强度
#define	PARA_A_EXPA_WORK_EN		0xC401	// [WR]微功放: 射频信号开关
#define	PARA_A_EXPA_DL_ATT		0xC441	// [WR]微功放: 下行衰减值
#define	PARA_A_EXPA_TEMP			0xC501	// [RO]微功放: 温度
#define	PARA_A_EXPA_DL_POW		0xC503	// [RO]微功放: 下行输出功率电平
#define	PARA_A_EXPA_SWR			0xC506	// [RO]微功放: 下行驻波比值
#define	PARA_A_EXPA_POWER_DN	0xC301	// [RO]微功放: 电源掉电告警(3分钟概率判定)
#define	PARA_A_EXPA_POWER_ERR	0xC302	// [RO]微功放: 电源故障告警(3分钟概率判定)
#define	PARA_A_EXPA_BATT_ERR		0xC304	// [RO]微功放: 监控模块电池故障告警(3分钟概率判定)
#define	PARA_A_EXPA_POS_ALM		0xC305	// [RO]微功放: 位置告警
#define	PARA_A_EXPA_DOOR_ALM	0xC328	// [RO]微功放: 门禁告警
#define	PARA_A_EXPA_WROK_ALM	0xC30D	// [RO]微功放: 下行功放故障告警(3分钟概率判定)
#define	PARA_A_EXPA_EXT1_ALM		0xC320	// [RO]微功放: 外部告警1
#define	PARA_A_EXPA_EXT2_ALM		0xC321	// [RO]微功放: 外部告警2
#define	PARA_A_EXPA_EXT3_ALM		0xC322	// [RO]微功放: 外部告警3
#define	PARA_A_EXPA_MAX_GAIN	0		// 微功放: 零衰减增益，即最大增益
#define	PARA_A_EXPA_GAIN_THD		0		// 微功放: 增益门限，即允许工作的增益最大值
#define	PARA_A_EXPA_POW_THD		0		// 微功放: 功放输出功率门限
#define	PARA_A_EXPA_POD_CMP 		0		// 微功放: 检波管功率检测补偿值,1字节有符号数,最终功率为检波管功率加上补偿值
#define	PARA_MONITOR_VOL_OVER_THR 				0x0a62 			 // 监控电压过门限
#define 	PARA_MONITOR_VOL_OWE_THR 				0x0a63 			 // 监控电压欠门限
#define 	PARA_DIGITAL_SINGNAL_ALARM 				0x8a68			 // 数字信号异常告警
#define 	PARA_HOST_DEVICE_LINK_SINGNAL_ALARM 	0x8a69			 // 主从监控链路告警
#define 	PARA_MONITOR_BATTERY_ALARM 				0x8a6a			 // 监控模块电池故障告警
#define 	PARA_LOW_POWER_ALARM 					0x8a6b			 // 电源掉电告警
#define 	PARA_BATTERY_BREAKDOWN_ALARM 			0x8a6c			 // 电源故障告警
#define 	PARA_POSITION_MOVE_ALARM					0x8a6f			 // 位置告警
#define 	PARA_A_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // A下行输入过功率告警
#define 	PARA_A_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // A下行输入欠功率告警
#define 	PARA_B_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // B下行输入过功率告警
#define 	PARA_B_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // B下行输入欠功率告警
#define 	PARA_C_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // C下行输入过功率告警
#define 	PARA_C_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // C下行输入欠功率告警
#define 	PARA_D_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // D下行输入过功率告警
#define 	PARA_D_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // D下行输入欠功率告警
#define 	PARA_TD_D_OVER_SLOT1_THR_ALARM 			0x8a66			 // TD下行输入导频过功率告警
#define 	PARA_TD_D_OWE_SLOT1_THR_ALARM 			0x8a67			 // TD下行输入导频欠功率告警
#define 	PARA_RE_DATA_LAN_ST1     0x8a40     //数据PHY芯片工作状态  0: 正常，1: 告警
#define 	PARA_RE_CASCADE_LAN_ST1   0x8a48     //级联网口的工作状态  0: 正常，1: 告警
#define 	PARA_RE_DATA_LAN_SYS_ST1  0x8a4a     //数据网口同步状态  0: 同步，1: 失步
#define 	PARA_RE_CASCADE_LAN_SYS_ST1  0x8a52     //级联网口同步状态  0: 同步，1: 失步
#define 	PARA_A_RF_POW_SWR           	0x8a32     //A段覆盖单元功放驻波比
#define 	PARA_A_RF_OUT_POW_H_THR   		0x0a50     //A段覆盖单元输出过功率门限
#define 	PARA_A_RF_OUT_POW_L_THR   		0x0a51     //A段覆盖单元输出欠功率门限
#define 	PARA_B_RF_POW_SWR            	0x8a32     //B段覆盖单元功放驻波比
#define 	PARA_B_RF_OUT_POW_H_THR   		0x0a50     //A段覆盖单元输出过功率门限
#define 	PARA_B_RF_OUT_POW_L_THR   		0x0a51     //A段覆盖单元输出欠功率门限
#define 	PARA_C_RF_POW_SWR           	0x8a32     //A段覆盖单元功放驻波比
#define 	PARA_C_RF_OUT_POW_H_THR   		0x0a50     //A段覆盖单元输出过功率门限
#define 	PARA_C_RF_OUT_POW_L_THR   		0x0a51     //A段覆盖单元输出欠功率门限
#define 	PARA_D_RF_POW_SWR            	0x8a32     //B段覆盖单元功放驻波比
#define 	PARA_D_RF_OUT_POW_H_THR   		0x0a50     //A段覆盖单元输出过功率门限
#define 	PARA_D_RF_OUT_POW_L_THR   		0x0a51     //A段覆盖单元输出欠功率门限
#define 	PARA_PWR_3V3_1_VT	0		// 3.3V电源电压
#define 	PARA_PWR_3V3_2_VT	0		//	3.3V电源电压
#define 	PARA_PWR_1V8_VT		0			// 1.8V电源电压
#define 	PARA_PWR_1V5_VT		0			 // 1.5V电源电压
#define 	PARA_A_DL_RF_EN 	0x08a0	// 	A段下行射频使能	
#define 	PARA_A_UL_RF_EN 	0x08a1	// 	A段上行射频使能	
#define 	PARA_B_DL_RF_EN 	0x08a0	// 	B段下行射频使能	
#define 	PARA_B_UL_RF_EN		0x08a1	// 	B段上行射频使能	
#define 	PARA_C_DL_RF_EN 	0x08a0	// 	C段下行射频使能	
#define 	PARA_C_UL_RF_EN 	0x08a1	// 	C段上行射频使能	
#define 	PARA_D_DL_RF_EN 	0x08a0	// 	D段下行射频使能	
#define 	PARA_D_UL_RF_EN 	0x08a1	// 	D段上行射频使能	
#define 	PARA_METER_OFFSET	0x0a66	//	仪器偏差值设置
#define 	PARA_METER_OFFSET_B	0x0a66	//	仪器偏差值设置
#define 	PARA_METER_OFFSET_C	0x0a66	//	仪器偏差值设置
#define 	PARA_METER_OFFSET_D	0x0a66	//	仪器偏差值设置
#define 	PARA_C_TD_TYPE_SELECT	0x0631	//686	// TD下行输入导频过功率告警					
#define 	PARA_C_TD_NORMAL_CP		0x0632	//716	//	TDD特殊时隙 NORMAL_CP
#define 	PARA_C_TD_EXTENDED_CP	0x0a6c	//717	//	TDD特殊时隙 NORMAL_CP
#define 	PARA_C_TD_SYNC_ST	0x862a	//687	//	TD同步状态:	0-已同步，1-未同步			
#define 	PARA_C_TD_WORK_MODE	0x060c	//688	//	[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零			
#define 	PARA_C_TD_DL_OVER_SLOT1_THR_ALARM	0x8a66	//689	// TD下行输入导频过功率告警					
#define 	PARA_C_TD_DL_OWE_SLOT1_THR_ALARM	0x8a67	//690	 // TD下行输入导频欠功率告警					
#define 	PARA_D_TD_TYPE_SELECT	0x0631	//691	// TD下行输入导频过功率告警					
#define 	PARA_D_TD_NORMAL_CP		0x0632	//718	//	TDD特殊时隙 NORMAL_CP
#define 	PARA_D_TD_EXTENDED_CP	0x0a6c	//719	//	TDD特殊时隙 NORMAL_CP
#define 	PARA_D_TD_SYNC_ST	0x862a	//692	//	TD同步状态:	0-已同步，1-未同步			
#define 	PARA_D_TD_WORK_MODE	0x060c	//693	//	[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零			
#define 	PARA_D_TD_DL_OVER_SLOT1_THR_ALARM	0x8a66	//694	// TD下行输入导频过功率告警					
#define 	PARA_D_TD_DL_OWE_SLOT1_THR_ALARM	0x8a67	//695	 // TD下行输入导频欠功率告警					
#define 	PARA_C_TD_T0_UD	0	//696	//	TD时隙0上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T1_UD	0	//697	//	TD时隙1上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T2_UD	0	//698	//	TD时隙2上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T3_UD	0	//699	//	TD时隙3上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T4_UD	0	//700	//	TD时隙4上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T5_UD	0	//701	//	TD时隙5上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T6_UD	0	//702	//	TD时隙6上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T7_UD	0	//703	//	TD时隙7上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T8_UD	0	//704	//	TD时隙8上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T9_UD	0	//705	//	TD时隙9上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T0_UD	0	//706	//	TD时隙0上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T1_UD	0	//707	//	TD时隙1上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T2_UD	0	//708	//	TD时隙2上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T3_UD	0	//709	//	TD时隙3上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T4_UD	0	//710	//	TD时隙4上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T5_UD	0	//711	//	TD时隙5上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T6_UD	0	//712	//	TD时隙6上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T7_UD	0	//713	//	TD时隙7上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T8_UD	0	//714	//	TD时隙8上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T9_UD	0	//715	//	TD时隙9上下行标志:0-上行，1-下行//#endif
#define	PARA_NOISE_TEST_EN	0	//	噪声测试开关		
#define	PARA_FREQ_MODIF_VAL_D	0x0a6d		//	本振修正值
#define	PARA_FREQ_MODIF_VAL_B	0x0a6e		//	本振修正值
#define	PARA_FREQ_MODIF_VAL_A	0x0a6f		//	本振修正值
#define	PARA_B_TDS_2TH_BREAKING_POINT_SET	0x0609		//	TDS 第二转换点设置
#define 	PARA_DELAY_MODE_A	0x8660	// 	延时模式: 0-手动, 1-自动
#define 	PARA_DELAY_MODE_B	0x8660	// 	延时模式: 0-手动, 1-自动
#define 	PARA_DELAY_MODE_C	0x8660	// 	延时模式: 0-手动, 1-自动
#define 	PARA_DELAY_MODE_D	0x8660	// 	延时模式: 0-手动, 1-自动
#define	PARA_REE_CIRCUIT_ALARM	 		0
#define	PARA_REE_WLAN_CONN_ST			0
#define	PARA_DL_POWER_MAX			0
#define 	PARA_SLOT_TIME_EN_B	0x0	// 时隙配比自动检测开关		
#define 	PARA_SLOT_TIME_DISTRI_B	0	// 时隙配比分布	BIT0：1代表15配比,BIT1：1代表24配比,	BIT2：1代表33配比			
#define 	PARA_VERSION_FLAG		0	// 版本标识		
#define 	PARA_SLOT_TIME_EN_C	0	// 时隙配比自动检测开关		
#define 	PARA_SLOT_TIME_DISTRI_C	0	
#define 	PARA_A_1197_LOCK_ST		0	// A段1197锁定状态	
#define 	PARA_A_IF_ST	0	// A段中频频率,0/1---300M/500M		
#define 	PARA_ENCRYPTION_ST	0	//加密状态,0/1---不加密/加密
#define 	PARA_PWR_1V6_VT	0	//加密状态,0/1---不加密/加密
#define		PARA_A_90_VALUE			0				//A段9363 90寄存器的值
#define		PARA_A_91_VALUE			0				//A段9363 91寄存器的值
#define		PARA_A_94_VALUE			0				//A段9363 94寄存器的值
#define		PARA_A_95_VALUE			0				//A段9363 95寄存器的值
#define		PARA_B_90_VALUE			0				//B段9363 90寄存器的值
#define		PARA_B_91_VALUE			0				//B段9363 91寄存器的值
#define		PARA_B_94_VALUE			0				//B段9363 94寄存器的值
#define		PARA_B_95_VALUE			0				//B段9363 95寄存器的值
#define		PARA_C_90_VALUE			0				//C段9363 90寄存器的值
#define		PARA_C_91_VALUE			0				//C段9363 91寄存器的值
#define		PARA_C_94_VALUE			0				//C段9363 94寄存器的值
#define		PARA_C_95_VALUE			0				//C段9363 95寄存器的值
#define		PARA_D_90_VALUE			0				//D段9363 90寄存器的值
#define		PARA_D_91_VALUE			0				//D段9363 91寄存器的值
#define		PARA_D_94_VALUE			0				//D段9363 94寄存器的值
#define		PARA_D_95_VALUE			0				//D段9363 95寄存器的值
#define		PARA_PASSTHROUGH_EN			0				//测试透传使能
#define		PARA_A_DL_POW_ADJ			0			
#define		PARA_B_DL_POW_ADJ			0			
#define		PARA_C_DL_POW_ADJ			0			
#define		PARA_D_DL_POW_ADJ			0		
#define		PARA_SoftwareLoadTimes			0		
#define     PARA_A_LNA_EN_ST 		   0	// 	A段下行低噪放LNA开关使能







#else

// 参数地址定义==================================================== 1b								
#define	PARA_A_CHANNEL_COUNT	0x8889	//	A段支持的通道数
#define	PARA_A_DL_WORK_EN	0x08b1	//	A段下行工作使能
#define	PARA_A_UL_WORK_EN	0x08b2	//	A段上行工作使能
#define	PARA_A_DPOW_MODE	0	//	A段下行功率控制方式
#define	PARA_A_UPOW_MODE	0	//	A段上行功率控制方式
#define	PARA_A_LTHR_EN	0x0770	//	A段上行底噪抑制使能
#define	PARA_A_LTHR_UP	0	//	A段底噪抑制上门限
#define	PARA_A_LTHR_DN	0x08b0	//	A段底噪抑制下门限
#define	PARA_A_DCH_EN1	0x08d0	//	A段下行通道工作使能1
#define	PARA_A_DCH_EN2	0x08d1	//	A段下行通道工作使能2
#define	PARA_A_DCH_EN3	0x08d2	//	A段下行通道工作使能3
#define	PARA_A_DCH_EN4	0x08d3	//	A段下行通道工作使能4
#define	PARA_A_DCH_EN5	0x08d4	//	A段下行通道工作使能5
#define	PARA_A_DCH_EN6	0x08d5	//	A段下行通道工作使能6
#define	PARA_A_DCH_EN7	0x08d6	//	A段下行通道工作使能7
#define	PARA_A_DCH_EN8	0x08d7	//	A段下行通道工作使能8
#define	PARA_A_DCH_EN9	0x08d8	//	A段下行通道工作使能9
#define	PARA_A_DCH_EN10	0x08d9	//	A段下行通道工作使能10
#define	PARA_A_DCH_EN11	0x08dA	//	A段下行通道工作使能11
#define	PARA_A_DCH_EN12	0x08dB	//	A段下行通道工作使能12
#define	PARA_A_DCH_EN13	0x08dC	//	A段下行通道工作使能13
#define	PARA_A_DCH_EN14	0x08dD	//	A段下行通道工作使能14
#define	PARA_A_DCH_EN15	0x08dE	//	A段下行通道工作使能15
#define	PARA_A_DCH_EN16	0x08dF	//	A段下行通道工作使能16
#define	PARA_A_UCH_EN1	0x08d0	//	A段上行通道工作使能1
#define	PARA_A_UCH_EN2	0x08d1	//	A段上行通道工作使能2
#define	PARA_A_UCH_EN3	0x08d2	//	A段上行通道工作使能3
#define	PARA_A_UCH_EN4	0x08d3	//	A段上行通道工作使能4
#define	PARA_A_UCH_EN5	0x08d4	//	A段上行通道工作使能5
#define	PARA_A_UCH_EN6	0x08d5	//	A段上行通道工作使能6
#define	PARA_A_UCH_EN7	0x08d6	//	A段上行通道工作使能7
#define	PARA_A_UCH_EN8	0x08d7	//	A段上行通道工作使能8
#define	PARA_A_UCH_EN9	0x08d8	//	A段上行通道工作使能9
#define	PARA_A_UCH_EN10	0x08d9	//	A段上行通道工作使能10
#define	PARA_A_UCH_EN11	0x08dA	//	A段上行通道工作使能11
#define	PARA_A_UCH_EN12	0x08dB	//	A段上行通道工作使能12
#define	PARA_A_UCH_EN13	0x08dC	//	A段上行通道工作使能13
#define	PARA_A_UCH_EN14	0x08dD	//	A段上行通道工作使能14
#define	PARA_A_UCH_EN15	0x08dE	//	A段上行通道工作使能15
#define	PARA_A_UCH_EN16	0x08dF	//	A段上行通道工作使能16
#define	PARA_A_DCH_GAIN1	0x0840	//	A段下行选频通道放大器增益1
#define	PARA_A_DCH_GAIN2	0x0841	//	A段下行选频通道放大器增益2
#define	PARA_A_DCH_GAIN3	0x0842	//	A段下行选频通道放大器增益3
#define	PARA_A_DCH_GAIN4	0x0843	//	A段下行选频通道放大器增益4
#define	PARA_A_DCH_GAIN5	0x0844	//	A段下行选频通道放大器增益5
#define	PARA_A_DCH_GAIN6	0x0845	//	A段下行选频通道放大器增益6
#define	PARA_A_DCH_GAIN7	0x0846	//	A段下行选频通道放大器增益7
#define	PARA_A_DCH_GAIN8	0x0847	//	A段下行选频通道放大器增益8
#define	PARA_A_DCH_GAIN9	0x0848	//	A段下行选频通道放大器增益9
#define	PARA_A_DCH_GAIN10	0x0849	//	A段下行选频通道放大器增益10
#define	PARA_A_DCH_GAIN11	0x084A	//	A段下行选频通道放大器增益11
#define	PARA_A_DCH_GAIN12	0x084B	//	A段下行选频通道放大器增益12
#define	PARA_A_DCH_GAIN13	0x084C	//	A段下行选频通道放大器增益13
#define	PARA_A_DCH_GAIN14	0x084D	//	A段下行选频通道放大器增益14
#define	PARA_A_DCH_GAIN15	0x084E	//	A段下行选频通道放大器增益15
#define	PARA_A_DCH_GAIN16	0x084F	//	A段下行选频通道放大器增益16
#define	PARA_A_UCH_GAIN1	0x0850	//	A段上行选频通道放大器增益1
#define	PARA_A_UCH_GAIN2	0x0851	//	A段上行选频通道放大器增益2
#define	PARA_A_UCH_GAIN3	0x0852	//	A段上行选频通道放大器增益3
#define	PARA_A_UCH_GAIN4	0x0853	//	A段上行选频通道放大器增益4
#define	PARA_A_UCH_GAIN5	0x0854	//	A段上行选频通道放大器增益5
#define	PARA_A_UCH_GAIN6	0x0855	//	A段上行选频通道放大器增益6
#define	PARA_A_UCH_GAIN7	0x0856	//	A段上行选频通道放大器增益7
#define	PARA_A_UCH_GAIN8	0x0857	//	A段上行选频通道放大器增益8
#define	PARA_A_UCH_GAIN9	0x0858	//	A段上行选频通道放大器增益9
#define	PARA_A_UCH_GAIN10	0x0859	//	A段上行选频通道放大器增益10
#define	PARA_A_UCH_GAIN11	0x085A	//	A段上行选频通道放大器增益11
#define	PARA_A_UCH_GAIN12	0x085B	//	A段上行选频通道放大器增益12
#define	PARA_A_UCH_GAIN13	0x085C	//	A段上行选频通道放大器增益13
#define	PARA_A_UCH_GAIN14	0x085D	//	A段上行选频通道放大器增益14
#define	PARA_A_UCH_GAIN15	0x085E	//	A段上行选频通道放大器增益15
#define	PARA_A_UCH_GAIN16	0x085F	//	A段上行选频通道放大器增益16
#define	PARA_A_DCH_ATT1	0x0324	//	A段下行数控衰减量1
#define	PARA_A_DCH_ATT2	0	//	A段下行数控衰减量2
#define	PARA_A_DCH_ATT3	0	//	A段下行数控衰减量3
#define	PARA_A_DCH_ATT4	0	//	A段下行数控衰减量4
#define	PARA_A_DCH_ATT5	0	//	A段下行数控衰减量5
#define	PARA_A_DCH_ATT6	0	//	A段下行数控衰减量6
#define	PARA_A_DCH_ATT7	0	//	A段下行数控衰减量7
#define	PARA_A_DCH_ATT8	0	//	A段下行数控衰减量8
#define	PARA_A_DCH_ATT9	0	//	A段下行数控衰减量9
#define	PARA_A_DCH_ATT10	0	//	A段下行数控衰减量10
#define	PARA_A_DCH_ATT11	0	//	A段下行数控衰减量11
#define	PARA_A_DCH_ATT12	0	//	A段下行数控衰减量12
#define	PARA_A_DCH_ATT13	0	//	A段下行数控衰减量13
#define	PARA_A_DCH_ATT14	0	//	A段下行数控衰减量14
#define	PARA_A_DCH_ATT15	0	//	A段下行数控衰减量15
#define	PARA_A_DCH_ATT16	0	//	A段下行数控衰减量16
#define	PARA_A_UCH_ATT1	0x0320	//	A段上行数控衰减量1
#define	PARA_A_UCH_ATT2	0	//	A段上行数控衰减量2
#define	PARA_A_UCH_ATT3	0	//	A段上行数控衰减量3
#define	PARA_A_UCH_ATT4	0	//	A段上行数控衰减量4
#define	PARA_A_UCH_ATT5	0	//	A段上行数控衰减量5
#define	PARA_A_UCH_ATT6	0	//	A段上行数控衰减量6
#define	PARA_A_UCH_ATT7	0	//	A段上行数控衰减量7
#define	PARA_A_UCH_ATT8	0	//	A段上行数控衰减量8
#define	PARA_A_UCH_ATT9	0	//	A段上行数控衰减量9
#define	PARA_A_UCH_ATT10	0	//	A段上行数控衰减量10
#define	PARA_A_UCH_ATT11	0	//	A段上行数控衰减量11
#define	PARA_A_UCH_ATT12	0	//	A段上行数控衰减量12
#define	PARA_A_UCH_ATT13	0	//	A段上行数控衰减量13
#define	PARA_A_UCH_ATT14	0	//	A段上行数控衰减量14
#define	PARA_A_UCH_ATT15	0	//	A段上行数控衰减量15
#define	PARA_A_UCH_ATT16	0	//	A段上行数控衰减量16
#define	PARA_A_DL_PA_GAIN	0	//	A段下行功放增益
#define	PARA_A_UL_PA_GAIN	0	//	A段上行功放增益
#define	PARA_A_TX_PLL_ST	0x8308	//	A段下行PLL状态,287 2为TX_VCO锁定，其他失锁
#define	PARA_A_RX_PLL_ST	0x8300	//	A段上行PLL状态,247 2为RX_VCO锁定，其他失锁
#define	PARA_A_INIT_DA_ST	0	//	初始化A段DA状态,17 1A为锁定+发送接收使能打开，其他异常
#define	PARA_A_BB_PLL_LOCK	0	//	A段BB PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define	PARA_A_FSAT		0	//	A段前端AD输入状态
#define	PARA_A_DSAT		0	//	A段后端DA输出状态
#define	PARA_A_PA_VG_EN	0	//	A段功放栅压状态
#define	PARA_A_PA_VT	0	//	A段功放管电压显示
#define	PARA_A_Modulator_EN	0	//	A段调制器状态
#define	PARA_A_LNA_VT	0	//	A段下行低噪放LNA电压
#define	PARA_A_LNA1_ST		0x8214	//	上行LNA1状态
#define	PARA_A_LNA2_ST		0x8215	//	上行LNA2状态
#define	PARA_A_BUSY_TIME	0x8892	//	A段上行时隙占用率
#define	PARA_A_PRI_ADD 	0xf002	//	A段模块地址(在虹信协议中，高四位为上行地址，低四位为下行地址)
#define	PARA_A_UL_POW_1B	0x831e	//	A段上行输入总功率
#define 	PARA_A_DL_POW_1B	0x8390	//	A段下行输入总功率
#define 	PARA_A_DCH_REC_RF_ATT1          0     //// REC端的下行数控衰减量。即RF端的链路下行衰减量 在rf
#define 	PARA_A_UCH_REC_RF_ATT1          0     //// REC端的上行数控衰减量。即RF端的链路上行衰减量 在rf
#define	PARA_B_CHANNEL_COUNT	0x8889	//	B段支持的通道数
#define	PARA_B_DL_WORK_EN	0x08b1	//	B段下行工作使能
#define	PARA_B_UL_WORK_EN	0x08b2	//	B段上行工作使能
#define	PARA_B_DPOW_MODE	0	//	B段下行功率控制方式
#define	PARA_B_UPOW_MODE	0	//	B段上行功率控制方式
#define	PARA_B_LTHR_EN		0x0770	//	B段上行底噪抑制使能
#define	PARA_B_LTHR_UP		0	//	B段底噪抑制上门限
#define	PARA_B_LTHR_DN		0x08b0	//	B段底噪抑制下门限
#define	PARA_B_DCH_EN1		0x08d0	//	B段下行通道工作使能1
#define	PARA_B_DCH_EN2		0x08d1	//	B段下行通道工作使能2
#define	PARA_B_DCH_EN3		0x08d2	//	B段下行通道工作使能3
#define	PARA_B_DCH_EN4		0x08d3	//	B段下行通道工作使能4
#define	PARA_B_DCH_EN5		0x08d4	//	B段下行通道工作使能5
#define	PARA_B_DCH_EN6		0x08d5	//	B段下行通道工作使能6
#define	PARA_B_DCH_EN7		0x08d6	//	B段下行通道工作使能7
#define	PARA_B_DCH_EN8		0x08d7	//	B段下行通道工作使能8
#define	PARA_B_DCH_EN9		0x08d8	//	B段下行通道工作使能9
#define	PARA_B_DCH_EN10		0x08d9	//	B段下行通道工作使能10
#define	PARA_B_DCH_EN11		0x08dA	//	B段下行通道工作使能11
#define	PARA_B_DCH_EN12		0x08dB	//	B段下行通道工作使能12
#define	PARA_B_DCH_EN13		0x08dC	//	B段下行通道工作使能13
#define	PARA_B_DCH_EN14		0x08dD	//	B段下行通道工作使能14
#define	PARA_B_DCH_EN15		0x08dE	//	B段下行通道工作使能15
#define	PARA_B_DCH_EN16		0x08dF	//	B段下行通道工作使能16
#define	PARA_B_UCH_EN1		0x08d0	//	B段上行通道工作使能1
#define	PARA_B_UCH_EN2		0x08d1	//	B段上行通道工作使能2
#define	PARA_B_UCH_EN3		0x08d2	//	B段上行通道工作使能3
#define	PARA_B_UCH_EN4		0x08d3	//	B段上行通道工作使能4
#define	PARA_B_UCH_EN5		0x08d4	//	B段上行通道工作使能5
#define	PARA_B_UCH_EN6		0x08d5	//	B段上行通道工作使能6
#define	PARA_B_UCH_EN7		0x08d6	//	B段上行通道工作使能7
#define	PARA_B_UCH_EN8		0x08d7	//	B段上行通道工作使能8
#define	PARA_B_UCH_EN9		0x08d8	//	B段上行通道工作使能9
#define	PARA_B_UCH_EN10		0x08d9	//	B段上行通道工作使能10
#define	PARA_B_UCH_EN11		0x08dA	//	B段上行通道工作使能11
#define	PARA_B_UCH_EN12		0x08dB	//	B段上行通道工作使能12
#define	PARA_B_UCH_EN13		0x08dC	//	B段上行通道工作使能13
#define	PARA_B_UCH_EN14		0x08dD	//	B段上行通道工作使能14
#define	PARA_B_UCH_EN15		0x08dE	//	B段上行通道工作使能15
#define	PARA_B_UCH_EN16		0x08dF	//	B段上行通道工作使能16
#define	PARA_B_DCH_GAIN1	0x0840	//	B段下行选频通道放大器增益1
#define	PARA_B_DCH_GAIN2	0x0841	//	B段下行选频通道放大器增益2
#define	PARA_B_DCH_GAIN3	0x0842	//	B段下行选频通道放大器增益3
#define	PARA_B_DCH_GAIN4	0x0843	//	B段下行选频通道放大器增益4
#define	PARA_B_DCH_GAIN5	0x0844	//	B段下行选频通道放大器增益5
#define	PARA_B_DCH_GAIN6	0x0845	//	B段下行选频通道放大器增益6
#define	PARA_B_DCH_GAIN7	0x0846	//	B段下行选频通道放大器增益7
#define	PARA_B_DCH_GAIN8	0x0847	//	B段下行选频通道放大器增益8
#define	PARA_B_DCH_GAIN9	0x0848	//	B段下行选频通道放大器增益9
#define	PARA_B_DCH_GAIN10	0x0849	//	B段下行选频通道放大器增益10
#define	PARA_B_DCH_GAIN11	0x084A	//	B段下行选频通道放大器增益11
#define	PARA_B_DCH_GAIN12	0x084B	//	B段下行选频通道放大器增益12
#define	PARA_B_DCH_GAIN13	0x084C	//	B段下行选频通道放大器增益13
#define	PARA_B_DCH_GAIN14	0x084D	//	B段下行选频通道放大器增益14
#define	PARA_B_DCH_GAIN15	0x084E	//	B段下行选频通道放大器增益15
#define	PARA_B_DCH_GAIN16	0x084F	//	B段下行选频通道放大器增益16
#define	PARA_B_UCH_GAIN1	0x0850	//	B段上行选频通道放大器增益1
#define	PARA_B_UCH_GAIN2	0x0851	//	B段上行选频通道放大器增益2
#define	PARA_B_UCH_GAIN3	0x0852	//	B段上行选频通道放大器增益3
#define	PARA_B_UCH_GAIN4	0x0853	//	B段上行选频通道放大器增益4
#define	PARA_B_UCH_GAIN5	0x0854	//	B段上行选频通道放大器增益5
#define	PARA_B_UCH_GAIN6	0x0855	//	B段上行选频通道放大器增益6
#define	PARA_B_UCH_GAIN7	0x0856	//	B段上行选频通道放大器增益7
#define	PARA_B_UCH_GAIN8	0x0857	//	B段上行选频通道放大器增益8
#define	PARA_B_UCH_GAIN9	0x0858	//	B段上行选频通道放大器增益9
#define	PARA_B_UCH_GAIN10	0x0859	//	B段上行选频通道放大器增益10
#define	PARA_B_UCH_GAIN11	0x085A	//	B段上行选频通道放大器增益11
#define	PARA_B_UCH_GAIN12	0x085B	//	B段上行选频通道放大器增益12
#define	PARA_B_UCH_GAIN13	0x085C	//	B段上行选频通道放大器增益13
#define	PARA_B_UCH_GAIN14	0x085D	//	B段上行选频通道放大器增益14
#define	PARA_B_UCH_GAIN15	0x085E	//	B段上行选频通道放大器增益15
#define	PARA_B_UCH_GAIN16	0x085F	//	B段上行选频通道放大器增益16
#define	PARA_B_DCH_ATT1		0x0324	//	B段下行输出数控衰减量1
#define	PARA_B_DCH_ATT2		0	//	B段下行输出数控衰减量2
#define	PARA_B_DCH_ATT3		0	//	B段下行输出数控衰减量3
#define	PARA_B_DCH_ATT4		0	//	B段下行输出数控衰减量4
#define	PARA_B_DCH_ATT5		0	//	B段下行输出数控衰减量5
#define	PARA_B_DCH_ATT6		0	//	B段下行输出数控衰减量6
#define	PARA_B_DCH_ATT7		0	//	B段下行输出数控衰减量7
#define	PARA_B_DCH_ATT8		0	//	B段下行输出数控衰减量8
#define	PARA_B_DCH_ATT9		0	//	B段下行输出数控衰减量9
#define	PARA_B_DCH_ATT10	0	//	B段下行输出数控衰减量10
#define	PARA_B_DCH_ATT11	0	//	B段下行输出数控衰减量11
#define	PARA_B_DCH_ATT12	0	//	B段下行输出数控衰减量12
#define	PARA_B_DCH_ATT13	0	//	B段下行输出数控衰减量13
#define	PARA_B_DCH_ATT14	0	//	B段下行输出数控衰减量14
#define	PARA_B_DCH_ATT15	0	//	B段下行输出数控衰减量15
#define	PARA_B_DCH_ATT16	0	//	B段下行输出数控衰减量16
#define	PARA_B_UCH_ATT1		0//0x0320	//	B段上行输入数控衰减量1
#define	PARA_B_UCH_ATT2		0	//	B段上行输入数控衰减量2
#define	PARA_B_UCH_ATT3		0	//	B段上行输入数控衰减量3
#define	PARA_B_UCH_ATT4		0	//	B段上行输入数控衰减量4
#define	PARA_B_UCH_ATT5		0	//	B段上行输入数控衰减量5
#define	PARA_B_UCH_ATT6		0	//	B段上行输入数控衰减量6
#define	PARA_B_UCH_ATT7		0	//	B段上行输入数控衰减量7
#define	PARA_B_UCH_ATT8		0	//	B段上行输入数控衰减量8
#define	PARA_B_UCH_ATT9		0	//	B段上行输入数控衰减量9
#define	PARA_B_UCH_ATT10	0	//	B段上行输入数控衰减量10
#define	PARA_B_UCH_ATT11	0	//	B段上行输入数控衰减量11
#define	PARA_B_UCH_ATT12	0	//	B段上行输入数控衰减量12
#define	PARA_B_UCH_ATT13	0	//	B段上行输入数控衰减量13
#define	PARA_B_UCH_ATT14	0	//	B段上行输入数控衰减量14
#define	PARA_B_UCH_ATT15	0	//	B段上行输入数控衰减量15
#define	PARA_B_UCH_ATT16	0	//	B段上行输入数控衰减量16
#define	PARA_B_DL_PA_GAIN	0	//	B段下行功放增益
#define	PARA_B_UL_PA_GAIN	0	//	B段上行功放增益
#define	PARA_B_TX_PLL_ST	0x8308	//	B段下行PLL状态,287 2为TX_VCO锁定，其他失锁
#define	PARA_B_RX_PLL_ST	0x8300	//	B段上行PLL状态,247 2为RX_VCO锁定，其他失锁
#define	PARA_B_INIT_DA_ST	0	//	初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
#define	PARA_B_BB_PLL_LOCK	0	//	B段BB PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define	PARA_B_FSAT		0	//	B段前端AD输入状态
#define	PARA_B_DSAT		0	//	B段后端DA输出状态
#define	PARA_B_PA_VG_EN	0	//	B段功放栅压状态
#define	PARA_B_PA_VT	0	//	B段功放管电压显示
#define	PARA_B_Modulator_EN	0	//	B段调制器状态
#define	PARA_B_LNA_VT	0	//	B段下行低噪放LNA电压
#define	PARA_B_LNA1_ST		0x8214	//	上行LNA1状态
#define	PARA_B_LNA2_ST		0x8215	//	上行LNA2状态
#define	PARA_B_BUSY_TIME	0x8892	//	B段上行时隙占用率
#define	PARA_B_PRI_ADD 		0xf002	//	B段模块地址(在虹信协议中，高四位为上行地址，低四位为下行地址)
#define	PARA_B_UL_POW_1B	0x831e	//	B段上行输入总功率
#define 	PARA_B_DL_POW_1B	0x8390	//	B段下行输入总功率
#define 	PARA_B_DCH_REC_RF_ATT1          0     //// REC端的下行数控衰减量。即RF端的链路下行衰减量 在rf
#define 	PARA_B_UCH_REC_RF_ATT1          0     //// REC端的上行数控衰减量。即RF端的链路上行衰减量  在rf
#define	PARA_C_CHANNEL_COUNT	0x8889	//	C段支持的通道数
#define	PARA_C_DL_WORK_EN	0x08b1	//	C段下行工作使能
#define	PARA_C_UL_WORK_EN	0x08b2	//	C段上行工作使能
#define	PARA_C_DPOW_MODE	0	//	C段下行功率控制方式
#define	PARA_C_UPOW_MODE	0	//	C段上行功率控制方式
#define	PARA_C_LTHR_EN		0x0770	//	C段上行底噪抑制使能
#define	PARA_C_LTHR_UP		0	//	C段底噪抑制上门限
#define	PARA_C_LTHR_DN		0x08b0	//	C段底噪抑制下门限
#define	PARA_C_DCH_EN1		0x08d0	//	C段下行通道工作使能1
#define	PARA_C_DCH_EN2		0x08d1	//	C段下行通道工作使能2
#define	PARA_C_DCH_EN3		0x08d2	//	C段下行通道工作使能3
#define	PARA_C_DCH_EN4		0x08d3	//	C段下行通道工作使能4
#define	PARA_C_DCH_EN5		0x08d4	//	C段下行通道工作使能5
#define	PARA_C_DCH_EN6		0x08d5	//	C段下行通道工作使能6
#define	PARA_C_DCH_EN7		0x08d6	//	C段下行通道工作使能7
#define	PARA_C_DCH_EN8		0x08d7	//	C段下行通道工作使能8
#define	PARA_C_DCH_EN9		0x08d8	//	C段下行通道工作使能9
#define	PARA_C_DCH_EN10		0x08d9	//	C段下行通道工作使能10
#define	PARA_C_UCH_EN1		0x08d0	//	C段上行通道工作使能1
#define	PARA_C_UCH_EN2		0x08d1	//	C段上行通道工作使能2
#define	PARA_C_UCH_EN3		0x08d2	//	C段上行通道工作使能3
#define	PARA_C_UCH_EN4		0x08d3	//	C段上行通道工作使能4
#define	PARA_C_UCH_EN5		0x08d4	//	C段上行通道工作使能5
#define	PARA_C_UCH_EN6		0x08d5	//	C段上行通道工作使能6
#define	PARA_C_UCH_EN7		0x08d6	//	C段上行通道工作使能7
#define	PARA_C_UCH_EN8		0x08d7	//	C段上行通道工作使能8
#define	PARA_C_UCH_EN9		0x08d8	//	C段上行通道工作使能9
#define	PARA_C_UCH_EN10		0x08d9	//	C段上行通道工作使能10
#define	PARA_C_DCH_GAIN1	0x0840	//	C段下行选频通道放大器增益1
#define	PARA_C_DCH_GAIN2	0x0841	//	C段下行选频通道放大器增益2
#define	PARA_C_DCH_GAIN3	0x0842	//	C段下行选频通道放大器增益3
#define	PARA_C_DCH_GAIN4	0x0843	//	C段下行选频通道放大器增益4
#define	PARA_C_DCH_GAIN5	0x0844	//	C段下行选频通道放大器增益5
#define	PARA_C_DCH_GAIN6	0x0845	//	C段下行选频通道放大器增益6
#define	PARA_C_DCH_GAIN7	0x0846	//	C段下行选频通道放大器增益7
#define	PARA_C_DCH_GAIN8	0x0847	//	C段下行选频通道放大器增益8
#define	PARA_C_DCH_GAIN9	0x0848	//	C段下行选频通道放大器增益9
#define	PARA_C_DCH_GAIN10	0x0849	//	C段下行选频通道放大器增益10
#define 	PARA_C_DCH_GAIN11 	0	// 	C段下行选频通道放大器增益11
#define 	PARA_C_DCH_GAIN12 	0	// 	C段下行选频通道放大器增益12
#define 	PARA_C_DCH_GAIN13 	0	// 	C段下行选频通道放大器增益13
#define 	PARA_C_DCH_GAIN14 	0	// 	C段下行选频通道放大器增益14
#define 	PARA_C_DCH_GAIN15 	0	// 	C段下行选频通道放大器增益15
#define 	PARA_C_DCH_GAIN16 	0	// 	C段下行选频通道放大器增益16
#define	PARA_C_UCH_GAIN1	0x0850	//	C段上行选频通道放大器增益1
#define	PARA_C_UCH_GAIN2	0x0851	//	C段上行选频通道放大器增益2
#define	PARA_C_UCH_GAIN3	0x0852	//	C段上行选频通道放大器增益3
#define	PARA_C_UCH_GAIN4	0x0853	//	C段上行选频通道放大器增益4
#define	PARA_C_UCH_GAIN5	0x0854	//	C段上行选频通道放大器增益5
#define	PARA_C_UCH_GAIN6	0x0855	//	C段上行选频通道放大器增益6
#define	PARA_C_UCH_GAIN7	0x0856	//	C段上行选频通道放大器增益7
#define	PARA_C_UCH_GAIN8	0x0857	//	C段上行选频通道放大器增益8
#define	PARA_C_UCH_GAIN9	0x0858	//	C段上行选频通道放大器增益9
#define	PARA_C_UCH_GAIN10	0x0859	//	C段上行选频通道放大器增益10
#define	PARA_C_UCH_GAIN11	0	//	C段上行选频通道放大器增益11
#define	PARA_C_UCH_GAIN12	0	//	C段上行选频通道放大器增益12
#define	PARA_C_UCH_GAIN13	0	//	C段上行选频通道放大器增益13
#define	PARA_C_UCH_GAIN14	0	//	C段上行选频通道放大器增益14
#define	PARA_C_UCH_GAIN15	0	//	C段上行选频通道放大器增益15
#define	PARA_C_UCH_GAIN16	0	//	C段上行选频通道放大器增益16
#define	PARA_C_DCH_ATT1		0x0324	//	C段下行输出数控衰减量1
#define	PARA_C_DCH_ATT2		0	//	C段下行输出数控衰减量2
#define	PARA_C_DCH_ATT3		0	//	C段下行输出数控衰减量3
#define	PARA_C_DCH_ATT4		0	//	C段下行输出数控衰减量4
#define	PARA_C_DCH_ATT5		0	//	C段下行输出数控衰减量5
#define	PARA_C_DCH_ATT6		0	//	C段下行输出数控衰减量6
#define	PARA_C_DCH_ATT7		0	//	C段下行输出数控衰减量7
#define	PARA_C_DCH_ATT8		0	//	C段下行输出数控衰减量8
#define	PARA_C_DCH_ATT9		0	//	C段下行输出数控衰减量9
#define	PARA_C_DCH_ATT10	0	//	C段下行输出数控衰减量10
#define	PARA_C_DCH_ATT11	0	//	C段下行输出数控衰减量11
#define	PARA_C_DCH_ATT12	0	//	C段下行输出数控衰减量12
#define	PARA_C_DCH_ATT13	0	//	C段下行输出数控衰减量13
#define	PARA_C_DCH_ATT14	0	//	C段下行输出数控衰减量14
#define	PARA_C_DCH_ATT15	0	//	C段下行输出数控衰减量15
#define	PARA_C_DCH_ATT16	0	//	C段下行输出数控衰减量16
#define	PARA_C_UCH_ATT1		0//0x0320	//	C段上行输入数控衰减量1
#define	PARA_C_UCH_ATT2		0	//	C段上行输入数控衰减量2
#define	PARA_C_UCH_ATT3		0	//	C段上行输入数控衰减量3
#define	PARA_C_UCH_ATT4		0	//	C段上行输入数控衰减量4
#define	PARA_C_UCH_ATT5		0	//	C段上行输入数控衰减量5
#define	PARA_C_UCH_ATT6		0	//	C段上行输入数控衰减量6
#define	PARA_C_UCH_ATT7		0	//	C段上行输入数控衰减量7
#define	PARA_C_UCH_ATT8		0	//	C段上行输入数控衰减量8
#define	PARA_C_UCH_ATT9		0	//	C段上行输入数控衰减量9
#define	PARA_C_UCH_ATT10	0	//	C段上行输入数控衰减量10
#define	PARA_C_UCH_ATT11	0	//	C段上行输入数控衰减量11
#define	PARA_C_UCH_ATT12	0	//	C段上行输入数控衰减量12
#define	PARA_C_UCH_ATT13	0	//	C段上行输入数控衰减量13
#define	PARA_C_UCH_ATT14	0	//	C段上行输入数控衰减量14
#define	PARA_C_UCH_ATT15	0	//	C段上行输入数控衰减量15
#define	PARA_C_UCH_ATT16	0	//	C段上行输入数控衰减量16
#define	PARA_C_DL_PA_GAIN	0	//	C段下行功放增益
#define	PARA_C_UL_PA_GAIN	0	//	C段上行功放增益
#define	PARA_C_TX_PLL_ST	0x8308	//	C段下行PLL状态,287 2为TX_VCO锁定，其他失锁
#define	PARA_C_RX_PLL_ST	0x8300	//	C段上行PLL状态,247 2为RX_VCO锁定，其他失锁
#define	PARA_C_INIT_DA_ST	0	//	C初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
#define	PARA_C_BB_PLL_LOCK	0	//	C段BB PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define	PARA_C_FSAT		0	//	C段前端AD输入状态
#define	PARA_C_DSAT		0	//	C段后端DA输出状态
#define	PARA_C_PA_VG_EN	0	//	C段功放栅压状态
#define	PARA_C_PA_VT	0	//	C段功放管电压显示
#define	PARA_C_Modulator_EN	0	//	C段调制器状态
#define	PARA_C_LNA_VT	0	//	C段下行低噪放LNA电压
#define	PARA_C_LNA1_ST		0x8214	//	C上行LNA1状态
#define	PARA_C_LNA2_ST		0x8215	//	C上行LNA2状态
#define	PARA_C_BUSY_TIME	0x8892	//	C段上行时隙占用率
#define	PARA_C_PRI_ADD 		0xf002	//	C段模块地址(在虹信协议中，高四位为上行地址，低四位为下行地址)
#define	PARA_C_UL_POW_1B	0x831e	//	C段上行输入总功率
#define 	PARA_C_DL_POW_1B	0x8390	//	C段下行输入总功率
#define 	PARA_C_DCH_REC_RF_ATT1          0     //// REC端的下行数控衰减量。即RF端的链路下行衰减量 在rf
#define 	PARA_C_UCH_REC_RF_ATT1          0     //// REC端的上行数控衰减量。即RF端的链路上行衰减量  在rf
#define	PARA_D_CHANNEL_COUNT	0x8889	//	D段支持的通道数
#define	PARA_D_DL_WORK_EN	0x08b1	//	D段下行工作使能
#define	PARA_D_UL_WORK_EN	0x08b2	//	D段上行工作使能
#define	PARA_D_DPOW_MODE	0	//	D段下行功率控制方式
#define	PARA_D_UPOW_MODE	0	//	D段上行功率控制方式
#define	PARA_D_LTHR_EN		0x0770	//	D段上行底噪抑制使能
#define	PARA_D_LTHR_UP		0	//	D段底噪抑制上门限
#define	PARA_D_LTHR_DN		0x08b0	//	D段底噪抑制下门限
#define	PARA_D_DCH_EN1		0x08d0	//	D段下行通道工作使能1
#define	PARA_D_DCH_EN2		0x08d1	//	D段下行通道工作使能2
#define	PARA_D_DCH_EN3		0x08d2	//	D段下行通道工作使能3
#define	PARA_D_DCH_EN4		0x08d3	//	D段下行通道工作使能4
#define	PARA_D_DCH_EN5		0x08d4	//	D段下行通道工作使能5
#define	PARA_D_DCH_EN6		0x08d5	//	D段下行通道工作使能6
#define	PARA_D_DCH_EN7		0x08d6	//	D段下行通道工作使能7
#define	PARA_D_DCH_EN8		0x08d7	//	D段下行通道工作使能8
#define	PARA_D_DCH_EN9		0x08d8	//	D段下行通道工作使能9
#define	PARA_D_DCH_EN10	0x08d9	//	D段下行通道工作使能10
#define	PARA_D_UCH_EN1		0x08d0	//	D段上行通道工作使能1
#define	PARA_D_UCH_EN2		0x08d1	//	D段上行通道工作使能2
#define	PARA_D_UCH_EN3		0x08d2	//	D段上行通道工作使能3
#define	PARA_D_UCH_EN4		0x08d3	//	D段上行通道工作使能4
#define	PARA_D_UCH_EN5		0x08d4	//	D段上行通道工作使能5
#define	PARA_D_UCH_EN6		0x08d5	//	D段上行通道工作使能6
#define	PARA_D_UCH_EN7		0x08d6	//	D段上行通道工作使能7
#define	PARA_D_UCH_EN8		0x08d7	//	D段上行通道工作使能8
#define	PARA_D_UCH_EN9		0x08d8	//	D段上行通道工作使能9
#define	PARA_D_UCH_EN10	0x08d9	//	D段上行通道工作使能10
#define	PARA_D_DCH_GAIN1	0x0840	//	D段下行选频通道放大器增益1
#define	PARA_D_DCH_GAIN2	0x0841	//	D段下行选频通道放大器增益2
#define	PARA_D_DCH_GAIN3	0x0842	//	D段下行选频通道放大器增益3
#define	PARA_D_DCH_GAIN4	0x0843	//	D段下行选频通道放大器增益4
#define	PARA_D_DCH_GAIN5	0x0844	//	D段下行选频通道放大器增益5
#define	PARA_D_DCH_GAIN6	0x0845	//	D段下行选频通道放大器增益6
#define	PARA_D_DCH_GAIN7	0x0846	//	D段下行选频通道放大器增益7
#define	PARA_D_DCH_GAIN8	0x0847	//	D段下行选频通道放大器增益8
#define	PARA_D_DCH_GAIN9	0x0848	//	D段下行选频通道放大器增益9
#define	PARA_D_DCH_GAIN10	0x0849	//	D段下行选频通道放大器增益10
#define	PARA_D_DCH_GAIN11	0	//	D段下行选频通道放大器增益11
#define	PARA_D_DCH_GAIN12	0	//	D段下行选频通道放大器增益12
#define	PARA_D_DCH_GAIN13	0	//	D段下行选频通道放大器增益13
#define	PARA_D_DCH_GAIN14	0	//	D段下行选频通道放大器增益14
#define	PARA_D_DCH_GAIN15	0	//	D段下行选频通道放大器增益15
#define	PARA_D_DCH_GAIN16	0	//	D段下行选频通道放大器增益16
#define	PARA_D_UCH_GAIN1	0x0850	//	D段上行选频通道放大器增益1
#define	PARA_D_UCH_GAIN2	0x0851	//	D段上行选频通道放大器增益2
#define	PARA_D_UCH_GAIN3	0x0852	//	D段上行选频通道放大器增益3
#define	PARA_D_UCH_GAIN4	0x0853	//	D段上行选频通道放大器增益4
#define	PARA_D_UCH_GAIN5	0x0854	//	D段上行选频通道放大器增益5
#define	PARA_D_UCH_GAIN6	0x0855	//	D段上行选频通道放大器增益6
#define	PARA_D_UCH_GAIN7	0x0856	//	D段上行选频通道放大器增益7
#define	PARA_D_UCH_GAIN8	0x0857	//	D段上行选频通道放大器增益8
#define	PARA_D_UCH_GAIN9	0x0858	//	D段上行选频通道放大器增益9
#define	PARA_D_UCH_GAIN10	0x0859	//	D段上行选频通道放大器增益10
#define	PARA_D_UCH_GAIN11	0	//	D段上行选频通道放大器增益11
#define	PARA_D_UCH_GAIN12	0	//	D段上行选频通道放大器增益12
#define	PARA_D_UCH_GAIN13	0	//	D段上行选频通道放大器增益13
#define	PARA_D_UCH_GAIN14	0	//	D段上行选频通道放大器增益14
#define	PARA_D_UCH_GAIN15	0	//	D段上行选频通道放大器增益15
#define	PARA_D_UCH_GAIN16	0	//	D段上行选频通道放大器增益16
#define	PARA_D_DCH_ATT1		0x0324	//	D段下行输出数控衰减量1
#define	PARA_D_DCH_ATT2		0	//	D段下行输出数控衰减量2
#define	PARA_D_DCH_ATT3		0	//	D段下行输出数控衰减量3
#define	PARA_D_DCH_ATT4		0	//	D段下行输出数控衰减量4
#define	PARA_D_DCH_ATT5		0	//	D段下行输出数控衰减量5
#define	PARA_D_DCH_ATT6		0	//	D段下行输出数控衰减量6
#define	PARA_D_DCH_ATT7		0	//	D段下行输出数控衰减量7
#define	PARA_D_DCH_ATT8		0	//	D段下行输出数控衰减量8
#define	PARA_D_DCH_ATT9		0	//	D段下行输出数控衰减量9
#define	PARA_D_DCH_ATT10	0	//	D段下行输出数控衰减量10
#define	PARA_D_DCH_ATT11	0	//	D段下行输出数控衰减量11
#define	PARA_D_DCH_ATT12	0	//	D段下行输出数控衰减量12
#define	PARA_D_DCH_ATT13	0	//	D段下行输出数控衰减量13
#define	PARA_D_DCH_ATT14	0	//	D段下行输出数控衰减量14
#define	PARA_D_DCH_ATT15	0	//	D段下行输出数控衰减量15
#define	PARA_D_DCH_ATT16	0	//	D段下行输出数控衰减量16
#define	PARA_D_UCH_ATT1		0//0x0320	//	D段上行输入数控衰减量1
#define	PARA_D_UCH_ATT2		0	//	D段上行输入数控衰减量2
#define	PARA_D_UCH_ATT3		0	//	D段上行输入数控衰减量3
#define	PARA_D_UCH_ATT4		0	//	D段上行输入数控衰减量4
#define	PARA_D_UCH_ATT5		0	//	D段上行输入数控衰减量5
#define	PARA_D_UCH_ATT6		0	//	D段上行输入数控衰减量6
#define	PARA_D_UCH_ATT7		0	//	D段上行输入数控衰减量7
#define	PARA_D_UCH_ATT8		0	//	D段上行输入数控衰减量8
#define	PARA_D_UCH_ATT9		0	//	D段上行输入数控衰减量9
#define	PARA_D_UCH_ATT10	0	//	D段上行输入数控衰减量10
#define	PARA_D_UCH_ATT11	0	//	D段上行输入数控衰减量11
#define	PARA_D_UCH_ATT12	0	//	D段上行输入数控衰减量12
#define	PARA_D_UCH_ATT13	0	//	D段上行输入数控衰减量13
#define	PARA_D_UCH_ATT14	0	//	D段上行输入数控衰减量14
#define	PARA_D_UCH_ATT15	0	//	D段上行输入数控衰减量15
#define	PARA_D_UCH_ATT16	0	//	D段上行输入数控衰减量16
#define	PARA_D_DL_PA_GAIN	0	//	D段下行功放增益
#define	PARA_D_UL_PA_GAIN	0	//	D段上行功放增益
#define	PARA_D_TX_PLL_ST	0x8308	//	D段下行PLL状态,287 2为TX_VCO锁定，其他失锁
#define	PARA_D_RX_PLL_ST	0x8300	//	D段上行PLL状态,247 2为RX_VCO锁定，其他失锁
#define	PARA_D_INIT_DA_ST	0	//	D初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常
#define	PARA_D_BB_PLL_LOCK	0	//	D段BB PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define	PARA_D_FSAT		0	//	D段前端AD输入状态
#define	PARA_D_DSAT		0	//	D段后端DA输出状态
#define	PARA_D_PA_VG_EN	0	//	D段功放栅压状态
#define	PARA_D_PA_VT	0	//	D段功放管电压显示
#define	PARA_D_Modulator_EN	0	//	D段调制器状态
#define	PARA_D_LNA_VT	0	//	D段下行低噪放LNA电压
#define	PARA_D_LNA1_ST		0x8214	//	D上行LNA1状态
#define	PARA_D_LNA2_ST		0x8215	//	D上行LNA2状态
#define	PARA_D_BUSY_TIME	0x8892	//	D段上行时隙占用率
#define	PARA_D_PRI_ADD 		0xf002	//	D段模块地址(在虹信协议中，高四位为上行地址，低四位为下行地址)
#define	PARA_D_UL_POW_1B	0x831e	//	D段上行输入总功率
#define 	PARA_D_DL_POW_1B	0x8390	//	D段下行输入总功率
#define 	PARA_D_DCH_REC_RF_ATT1          0     //// REC端的下行数控衰减量。即RF端的链路下行衰减量 在rf
#define 	PARA_D_UCH_REC_RF_ATT1          0     //// REC端的上行数控衰减量。即RF端的链路上行衰减量  在rf
#define	PARA_FP1_EN	0x0927	//	光口发送使能1
#define	PARA_FP2_EN	0x0928	//	光口发送使能2
#define	PARA_FP3_EN	0x0929	//	光口发送使能3
#define	PARA_FP4_EN	0x092A	//	光口发送使能4
#define	PARA_FP5_EN	0x092B	//	光口发送使能5
#define	PARA_FP6_EN	0x092C	//	光口发送使能6
#define	PARA_FP7_EN	0x092D	//	光口发送使能7
#define	PARA_FP8_EN	0x092E	//	光口发送使能8
#define	PARA_FP9_EN	0x0	//	光口发送使能9
#define	PARA_FP10_EN	0x0	//	光口发送使能10
#define	PARA_FP11_EN	0x0	//	光口发送使能11
#define	PARA_FP12_EN	0x0	//	光口发送使能12
#define	PARA_FP13_EN	0x0	//	光口发送使能13
#define	PARA_FP14_EN	0x0	//	光口发送使能14
#define	PARA_FP15_EN	0x0	//	光口发送使能15
#define	PARA_FP16_EN	0x0	//	光口发送使能16
#define	PARA_FP1_ON_POS	0x8560	//	光口在位状态1, 0-在位	
#define	PARA_FP2_ON_POS	0x8561	//	光口在位状态2, 0-在位	
#define	PARA_FP3_ON_POS	0x8562	//	光口在位状态3, 0-在位	
#define	PARA_FP4_ON_POS	0x8563	//	光口在位状态4, 0-在位	
#define	PARA_FP5_ON_POS	0x8564	//	光口在位状态5, 0-在位	
#define	PARA_FP6_ON_POS	0x8565	//	光口在位状态6, 0-在位	
#define	PARA_FP7_ON_POS	0x8566	//	光口在位状态7, 0-在位	
#define	PARA_FP8_ON_POS	0x8567	//	光口在位状态8, 0-在位	
#define	PARA_FP9_ON_POS	0x8568	//	光口在位状态9, 0-在位	
#define	PARA_FP10_ON_POS	0x8569	//	光口在位状态10, 0-在位	
#define	PARA_FP11_ON_POS	0x856a	//	光口在位状态11, 0-在位	
#define	PARA_FP12_ON_POS	0x856b	//	光口在位状态12, 0-在位	
#define	PARA_FP13_ON_POS	0x856c	//	光口在位状态13, 0-在位	
#define	PARA_FP14_ON_POS	0x856d	//	光口在位状态14, 0-在位
#define	PARA_FP15_ON_POS	0x856e	//	光口在位状态15, 0-在位
#define	PARA_FP16_ON_POS	0x856f	//	光口在位状态16, 0-在位
#define	PARA_FP1_LOS	0x8730	//	光口1信号丢失状态	
#define	PARA_FP2_LOS	0x8731	//	光口2信号丢失状态	
#define	PARA_FP3_LOS	0x8732	//	光口3信号丢失状态	
#define	PARA_FP4_LOS	0x8733	//	光口4信号丢失状态	
#define	PARA_FP5_LOS	0x8734	//	光口5信号丢失状态	
#define	PARA_FP6_LOS	0x8735	//	光口6信号丢失状态	
#define	PARA_FP7_LOS	0x8736	//	光口7信号丢失状态	
#define	PARA_FP8_LOS	0x8737	//	光口8信号丢失状态	
#define	PARA_FP9_LOS	0x8738	//	光口9信号丢失状态
#define	PARA_FP10_LOS	0x8739	//	光口10信号丢失状态	
#define	PARA_FP11_LOS	0x873a	//	光口11信号丢失状态	
#define	PARA_FP12_LOS	0x873b	//	光口12信号丢失状态	
#define	PARA_FP13_LOS	0x873c	//	光口13信号丢失状态
#define	PARA_FP14_LOS	0x873d	//	光口14信号丢失状态
#define	PARA_FP15_LOS	0x873e	//	光口15信号丢失状态
#define	PARA_FP16_LOS	0x873f	//	光口16信号丢失状态
#define	PARA_FP1_LOF	0x8780	//	光口1帧丢失状态	
#define	PARA_FP2_LOF	0x8781	//	光口2帧丢失状态	
#define	PARA_FP3_LOF	0x8782	//	光口3帧丢失状态	
#define	PARA_FP4_LOF	0x8783	//	光口4帧丢失状态	
#define	PARA_FP5_LOF	0x8784	//	光口5帧丢失状态	
#define	PARA_FP6_LOF	0x8785	//	光口6帧丢失状态	
#define	PARA_FP7_LOF	0x8786	//	光口7帧丢失状态	
#define	PARA_FP8_LOF	0x8787	//	光口8帧丢失状态	
#define	PARA_FP9_LOF	0x8788	//	光口9帧丢失状态	
#define	PARA_FP10_LOF	0x8789	//	光口10帧丢失状态	
#define	PARA_FP11_LOF	0x878a	//	光口11帧丢失状态	
#define	PARA_FP12_LOF	0x878b	//	光口12帧丢失状态	
#define	PARA_FP13_LOF	0x878c	//	光口13帧丢失状态
#define	PARA_FP14_LOF	0x878d	//	光口14帧丢失状态
#define	PARA_FP15_LOF	0x878e	//	光口15帧丢失状态
#define	PARA_FP16_LOF	0x878f	//	光口16帧丢失状态
#define	PARA_OPT_LOF	0x87ad	//	帧丢失状态
#define	PARA_SERDES1_PLL_ST	0x8790	//	SerDes芯片PLL状态1	
#define	PARA_SERDES2_PLL_ST	0x8791	//	SerDes芯片PLL状态2	
#define	PARA_SERDES3_PLL_ST	0x8792	//	SerDes芯片PLL状态3	
#define	PARA_SERDES4_PLL_ST	0x8793	//	SerDes芯片PLL状态4	
#define	PARA_SERDES5_PLL_ST	0x8794	//	SerDes芯片PLL状态5	
#define	PARA_SERDES6_PLL_ST	0x8795	//	SerDes芯片PLL状态6	
#define	PARA_SERDES7_PLL_ST	0x8796	//	SerDes芯片PLL状态7	
#define	PARA_SERDES8_PLL_ST	0x8797	//	SerDes芯片PLL状态8	
#define	PARA_SERDES9_PLL_ST	0x8798	//	SerDes芯片PLL状态9	
#define	PARA_SERDES10_PLL_ST	0x8799	//	SerDes芯片PLL状态10	
#define	PARA_SERDES11_PLL_ST	0x879a	//	SerDes芯片PLL状态11	
#define	PARA_SERDES12_PLL_ST	0x879b	//	SerDes芯片PLL状态12	
#define	PARA_SERDES13_PLL_ST	0x879c	//	SerDes芯片PLL状态13
#define	PARA_SERDES14_PLL_ST	0x879d	//	SerDes芯片PLL状态14
#define	PARA_SERDES15_PLL_ST	0x879e	//	SerDes芯片PLL状态15
#define	PARA_SERDES16_PLL_ST	0x879f	//	SerDes芯片PLL状态16
#define	PARA_TOPO_CHG_ALM	0x87af	//	环路状态告警
#define	PARA_BER_ALARM	0x87ae	//	误码率偏高告警
#define	PARA_LOAD_FPGA_ST	0x8854	//	加载FPGA状态
#define	PARA_FPGA_CLK_ST	0x8851	//	FPGA本振状态
#define	PARA_INIT_CLK_ST	0	//	初始化时钟状态
#define	PARA_INIT_AD_ST	0	//	初始化AD状态
#define	PARA_INIT_FB_AD_ST	0	//	初始化反馈AD状态
#define	PARA_CLK_PLL_ST	0x884e	//	CLK PLL状态
#define	PARA_CLK_REF_ST	0x884f	//	CLK 参考状态
#define	PARA_RE_NODE_MODE	0x889d	//	RE节点模式
#define	PARA_BOARD_TEMP	0x8844	//	单板温度
#define	PARA_CLK_VCO_VT	0	//	时钟VCO电压
#define	PARA_PWR_9V0_VT	0	//	9V电源电压
#define	PARA_PWR_5V5_VT	0	//	5.5V电源电压
#define	PARA_PWR_3V6_VT	0	//	3.6V电源电压
#define	PARA_PWR_1V2_VT	0	//	1.2V电源电压
#define	PARA_PWR_2V5_VT	0	//	1.2V电源电压
#define	PARA_PRI_PROTOCAL_V	0xf003	//	协议版本
#define	PARA_MODULE_HRI_ID	0	//	ID
#define 	PARA_WORK_ERROR	0	// 系统工作状态，1-有故障
#define 	PARA_TRAFFIC_END	0x88ac	// 话务量统计结束标志
#define 	PARA_DELAY_MODE	0x098e	// 	延时模式: 0-手动, 1-自动
#define	PARA_TD_SYNC_ST			0x7620		// TD同步状态: 1-已同步，0-未同步
#define	PARA_TD_WORK_MODE 		0x08ac	// [WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开, 每次上电后清零			
#define 	PARA_TD_T0_UD		0x08a0	// TD时隙0上下行标志:0-上行，1-下行			
#define 	PARA_TD_T1_UD		0x08a1	// TD时隙1上下行标志:0-上行，1-下行			
#define 	PARA_TD_T2_UD		0x08a2	// TD时隙2上下行标志:0-上行，1-下行			
#define 	PARA_TD_T3_UD		0x08a3	// TD时隙3上下行标志:0-上行，1-下行			
#define 	PARA_TD_T4_UD		0x08a4	// TD时隙4上下行标志:0-上行，1-下行			
#define 	PARA_TD_T5_UD		0x08a5	// TD时隙5上下行标志:0-上行，1-下行			
#define 	PARA_TD_T6_UD		0x08a6	// TD时隙6上下行标志:0-上行，1-下行			
#define	PARA_POWERUP_ST		0x8852	// 	数字板上电状态,每次启动时置1
#define	PARA_LOW_POWER			0x88ff//0x08ad	//	低功耗模式:1-低功耗;	0-正常		国人 x0778   由软件初始化，此宏只作为参考
#define 	PARA_THR_PORT		0		// 	透传端口选择0-485B, 1-RS232
#define	PARA_THR_BAUD		0		//	透传端口波特率 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define	PARA_CTRL_BAUD	0		//	控制端口波特率 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define	PARA_WLAN_CONN_ST1		0x87b2	// WLAN口状态1: 0-正常，1-异常
#define	PARA_WLAN_CONN_ST2		0x87b3	// WLAN口状态2: 0-正常，1-异常
#define	PARA_WLAN_CONN_ST3		0x87b4	// WLAN口状态3: 0-正常，1-异常
#define	PARA_WLAN_CONN_ST4		0x87b7	// WLAN口状态4: 0-正常，1-异常
#define	PARA_WLAN_SPEED1			0x87b8	// WLAN口速度1: 0：10M  1：100M  2：1000M
#define	PARA_WLAN_SPEED2			0x87b9		// WLAN口速度1: 0：10M  1：100M  2：1000M
#define	PARA_WLAN_SPEED3			0x87ba		// WLAN口速度1: 0：10M  1：100M  2：1000M
#define	PARA_WLAN_SPEED4			0x87bb		// WLAN口速度1: 0：10M  1：100M  2：1000M
#define	PARA_GSM_BW_SEL			0		// 宽带版本GSM带宽选择: 0-6M, 1-20M, 2-24M, 3-25M, 其他无效
#define	PARA_HX_DET_UADDR 0 // 虹信DET模块上行地址, 高4位为B段, 低四位为A段
#define	PARA_HX_LNA_UADDR 0 // 虹信LNA模块上行地址, 高4位为B段, 低四位为A段
#define	PARA_HX_DET_DADDR 0 // 虹信DET模块下行地址, 高4位为B段, 低四位为A段
#define	PARA_HX_LNA_DADDR 0 // 虹信LNA模块下行地址, 高4位为B段, 低四位为A段
#define 	PARA_FPS_AUTO_SCAN		0x0932		// 自动频点搜索功能使能:1-自动搜索和设置频点, 0-手动搜索
#define 	PARA_FPS_SWITCH_THD 		0 		// 自动频点搜索的BCCH功率切换门限
#define 	PARA_FPS_MOSVC_SEL		0x0925	// 频点搜索: 运营商选择: 0-中移动, 1-中联通, 2-中移动, 255-自动选择
#define	PARA_FPS_RFRANGE_SEL	0x0924	// 频点搜索: 频宽选择(忽略,以模块制式为准): 0-全频段, 1-900MHz, 2-1800MHz
#define 	PARA_FPS_BS_ID			0x8959	// 频点搜索: 基站识别码
#define	PARA_FPS_CA_COUNT		0x895b	// 频点搜索: 有效信道数
#define	PARA_FPS_BCCH_LK_ST		0x895c	// 频点搜索: 锁定BCCH状态: 1-锁定, 0-失败
#define	PARA_FPS_MOSVC_LK_ST		0x895d	// 频点搜索: 锁定运营商状态: 1-锁定, 0-失败
#define	PARA_FPS_RFRANGE_LK_ST	0x895e	// 频点搜索: 锁定频带状态: 1-锁定, 0-失败
#define	PARA_FPS_BCCH_POW_M		0x8960	// 频点搜索: 主小区BCCH接收强度
#define	PARA_FPS_BCCH_POW_1		0x8961	// 频点搜索: 邻小区1BCCH接收强度
#define	PARA_FPS_BCCH_POW_2		0x8962	// 频点搜索: 邻小区2BCCH接收强度
#define	PARA_FPS_BCCH_POW_3		0x8963	// 频点搜索: 邻小区3BCCH接收强度
#define	PARA_FPS_BCCH_POW_4		0x8964	// 频点搜索: 邻小区4BCCH接收强度
#define	PARA_FPS_BCCH_POW_5		0x8965	// 频点搜索: 邻小区5BCCH接收强度
#define	PARA_FPS_BCCH_POW_6		0x8966	// 频点搜索: 邻小区6BCCH接收强度
#define	PARA_A_EXPA_WORK_EN		0xC401	// [WR]微功放: 射频信号开关
#define	PARA_A_EXPA_DL_ATT		0xC441	// [WR]微功放: 下行衰减值
#define	PARA_A_EXPA_TEMP			0xC501	// [RO]微功放: 温度
#define	PARA_A_EXPA_DL_POW		0xC503	// [RO]微功放: 下行输出功率电平
#define	PARA_A_EXPA_SWR			0xC506	// [RO]微功放: 下行驻波比值
#define	PARA_A_EXPA_POWER_DN	0xC301	// [RO]微功放: 电源掉电告警(3分钟概率判定)
#define	PARA_A_EXPA_POWER_ERR	0xC302	// [RO]微功放: 电源故障告警(3分钟概率判定)
#define	PARA_A_EXPA_BATT_ERR		0xC304	// [RO]微功放: 监控模块电池故障告警(3分钟概率判定)
#define	PARA_A_EXPA_POS_ALM		0xC305	// [RO]微功放: 位置告警
#define	PARA_A_EXPA_DOOR_ALM	0xC328	// [RO]微功放: 门禁告警
#define	PARA_A_EXPA_WROK_ALM	0xC30D	// [RO]微功放: 下行功放故障告警(3分钟概率判定)
#define	PARA_A_EXPA_EXT1_ALM		0xC320	// [RO]微功放: 外部告警1
#define	PARA_A_EXPA_EXT2_ALM		0xC321	// [RO]微功放: 外部告警2
#define	PARA_A_EXPA_EXT3_ALM		0xC322	// [RO]微功放: 外部告警3
#define	PARA_A_EXPA_MAX_GAIN	0		// 微功放: 零衰减增益，即最大增益
#define	PARA_A_EXPA_GAIN_THD		0		// 微功放: 增益门限，即允许工作的增益最大值
#define	PARA_A_EXPA_POW_THD		0		// 微功放: 功放输出功率门限
#define	PARA_A_EXPA_POD_CMP 		0		// 微功放: 检波管功率检测补偿值,1字节有符号数,最终功率为检波管功率加上补偿值
#define	PARA_MONITOR_VOL_OVER_THR 				0x0a62 			 // 监控电压过门限
#define 	PARA_MONITOR_VOL_OWE_THR 				0x0a63 			 // 监控电压欠门限
#define 	PARA_DIGITAL_SINGNAL_ALARM 				0x8a68			 // 数字信号异常告警
#define 	PARA_HOST_DEVICE_LINK_SINGNAL_ALARM 	0x8a69			 // 主从监控链路告警
#define 	PARA_MONITOR_BATTERY_ALARM 				0x8a6a			 // 监控模块电池故障告警
#define 	PARA_LOW_POWER_ALARM 					0x8a6b			 // 电源掉电告警
#define 	PARA_BATTERY_BREAKDOWN_ALARM 			0x8a6c			 // 电源故障告警
#define 	PARA_POSITION_MOVE_ALARM					0x8a6f			 // 位置告警
#define 	PARA_A_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // A下行输入过功率告警
#define 	PARA_A_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // A下行输入欠功率告警
#define 	PARA_B_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // B下行输入过功率告警
#define 	PARA_B_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // B下行输入欠功率告警
#define 	PARA_C_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // C下行输入过功率告警
#define 	PARA_C_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // C下行输入欠功率告警
#define 	PARA_D_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // D下行输入过功率告警
#define 	PARA_D_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // D下行输入欠功率告警
#define 	PARA_TD_D_OVER_SLOT1_THR_ALARM 			0x8a66			 // TD下行输入导频过功率告警
#define 	PARA_TD_D_OWE_SLOT1_THR_ALARM 			0x8a67			 // TD下行输入导频欠功率告警
#define 	PARA_RE_DATA_LAN_ST1     0x8a40     //数据PHY芯片工作状态  0: 正常，1: 告警
#define 	PARA_RE_CASCADE_LAN_ST1   0x8a48     //级联网口的工作状态  0: 正常，1: 告警
#define 	PARA_RE_DATA_LAN_SYS_ST1  0x8a4a     //数据网口同步状态  0: 同步，1: 失步
#define 	PARA_RE_CASCADE_LAN_SYS_ST1  0x8a52     //级联网口同步状态  0: 同步，1: 失步
#define 	PARA_A_RF_POW_SWR           	0x8a32     //A段覆盖单元功放驻波比
#define 	PARA_A_RF_OUT_POW_H_THR   		0x0a50     //A段覆盖单元输出过功率门限
#define 	PARA_A_RF_OUT_POW_L_THR   		0x0a51     //A段覆盖单元输出欠功率门限
#define 	PARA_B_RF_POW_SWR            	0x8a32     //B段覆盖单元功放驻波比
#define 	PARA_B_RF_OUT_POW_H_THR   		0x0a50     //A段覆盖单元输出过功率门限
#define 	PARA_B_RF_OUT_POW_L_THR   		0x0a51     //A段覆盖单元输出欠功率门限
#define 	PARA_C_RF_POW_SWR           	0x8a32     //A段覆盖单元功放驻波比
#define 	PARA_C_RF_OUT_POW_H_THR   		0x0a50     //A段覆盖单元输出过功率门限
#define 	PARA_C_RF_OUT_POW_L_THR   		0x0a51     //A段覆盖单元输出欠功率门限
#define 	PARA_D_RF_POW_SWR            	0x8a32     //B段覆盖单元功放驻波比
#define 	PARA_D_RF_OUT_POW_H_THR   		0x0a50     //A段覆盖单元输出过功率门限
#define 	PARA_D_RF_OUT_POW_L_THR   		0x0a51     //A段覆盖单元输出欠功率门限
#define 	PARA_PWR_3V3_1_VT	0		// 3.3V电源电压
#define 	PARA_PWR_3V3_2_VT	0		//	3.3V电源电压
#define 	PARA_PWR_1V8_VT		0			// 1.8V电源电压
#define 	PARA_PWR_1V5_VT		0			 // 1.5V电源电压
#define 	PARA_A_DL_RF_EN 	0x0a67	// 	A段下行射频使能	
#define 	PARA_A_UL_RF_EN 	0x0a68	// 	A段上行射频使能	
#define 	PARA_B_DL_RF_EN 	0x0a67	// 	B段下行射频使能	
#define 	PARA_B_UL_RF_EN		0x0a68	// 	B段上行射频使能	
#define 	PARA_C_DL_RF_EN 	0x0a67	// 	C段下行射频使能	
#define 	PARA_C_UL_RF_EN 	0x0a68	// 	C段上行射频使能	
#define 	PARA_D_DL_RF_EN 	0x0a67	// 	D段下行射频使能	
#define 	PARA_D_UL_RF_EN 	0x0a68	// 	D段上行射频使能	
#define 	PARA_METER_OFFSET	0x0a66	//	仪器偏差值设置
#define 	PARA_METER_OFFSET_B	0x0a66	//	仪器偏差值设置
#define 	PARA_METER_OFFSET_C	0x0a66	//	仪器偏差值设置
#define 	PARA_METER_OFFSET_D	0x0a66	//	仪器偏差值设置
#define 	PARA_C_TD_TYPE_SELECT	0x0a6a	//686	// TD下行输入导频过功率告警					
#define 	PARA_C_TD_NORMAL_CP	0x0a6b	//716	//	TDD特殊时隙 NORMAL_CP
#define 	PARA_C_TD_EXTENDED_CP	0x0a6c	//717	//	TDD特殊时隙 NORMAL_CP
#define 	PARA_C_TD_SYNC_ST	0x7620	//687	//	TD同步状态:	0-已同步，1-未同步			
#define 	PARA_C_TD_WORK_MODE	0x08ac	//688	//	[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零			
#define 	PARA_C_TD_DL_OVER_SLOT1_THR_ALARM	0x8a66	//689	// TD下行输入导频过功率告警					
#define 	PARA_C_TD_DL_OWE_SLOT1_THR_ALARM	0x8a67	//690	 // TD下行输入导频欠功率告警					
#define 	PARA_D_TD_TYPE_SELECT	0x0a6a	//691	// TD下行输入导频过功率告警					
#define 	PARA_D_TD_NORMAL_CP	0x0a6b	//718	//	TDD特殊时隙 NORMAL_CP
#define 	PARA_D_TD_EXTENDED_CP	0x0a6c	//719	//	TDD特殊时隙 NORMAL_CP
#define 	PARA_D_TD_SYNC_ST	0x7620	//692	//	TD同步状态:	0-已同步，1-未同步			
#define 	PARA_D_TD_WORK_MODE	0x08ac	//693	//	[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零			
#define 	PARA_D_TD_DL_OVER_SLOT1_THR_ALARM	0x8a66	//694	// TD下行输入导频过功率告警					
#define 	PARA_D_TD_DL_OWE_SLOT1_THR_ALARM	0x8a67	//695	 // TD下行输入导频欠功率告警					
#define 	PARA_C_TD_T0_UD	0	//696	//	TD时隙0上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T1_UD	0	//697	//	TD时隙1上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T2_UD	0	//698	//	TD时隙2上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T3_UD	0	//699	//	TD时隙3上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T4_UD	0	//700	//	TD时隙4上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T5_UD	0	//701	//	TD时隙5上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T6_UD	0	//702	//	TD时隙6上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T7_UD	0	//703	//	TD时隙7上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T8_UD	0	//704	//	TD时隙8上下行标志:0-上行，1-下行			
#define 	PARA_C_TD_T9_UD	0	//705	//	TD时隙9上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T0_UD	0	//706	//	TD时隙0上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T1_UD	0	//707	//	TD时隙1上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T2_UD	0	//708	//	TD时隙2上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T3_UD	0	//709	//	TD时隙3上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T4_UD	0	//710	//	TD时隙4上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T5_UD	0	//711	//	TD时隙5上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T6_UD	0	//712	//	TD时隙6上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T7_UD	0	//713	//	TD时隙7上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T8_UD	0	//714	//	TD时隙8上下行标志:0-上行，1-下行			
#define 	PARA_D_TD_T9_UD	0	//715	//	TD时隙9上下行标志:0-上行，1-下行//#endif
#define	PARA_NOISE_TEST_EN	0	//	噪声测试开关		
#define	PARA_FREQ_MODIF_VAL_D	0x0a6d		//	本振修正值
#define	PARA_FREQ_MODIF_VAL_B	0x0a6e		//	本振修正值
#define	PARA_FREQ_MODIF_VAL_A	0x0a6f		//	本振修正值
#define	PARA_B_TDS_2TH_BREAKING_POINT_SET	0x0609		//	TDS 第二转换点设置
#define 	PARA_DELAY_MODE_A	0x098f	// 	延时模式: 0-手动, 1-自动
#define 	PARA_DELAY_MODE_B	0x098f	// 	延时模式: 0-手动, 1-自动
#define 	PARA_DELAY_MODE_C	0x098f	// 	延时模式: 0-手动, 1-自动
#define 	PARA_DELAY_MODE_D	0x098f	// 	延时模式: 0-手动, 1-自动
#define	PARA_REE_CIRCUIT_ALARM	 		0
#define	PARA_REE_WLAN_CONN_ST			0
#define	PARA_DL_POWER_MAX			0
#define 	PARA_SLOT_TIME_EN_B		0	// 时隙配比自动检测开关		
#define 	PARA_SLOT_TIME_DISTRI_B	0 // 时隙配比分布	BIT0：1代表15配比,BIT1：1代表24配比,	BIT2：1代表33配比			
#define 	PARA_VERSION_FLAG		0	// 版本标识		
#define 	PARA_SLOT_TIME_EN_C	0	// 时隙配比自动检测开关		
#define 	PARA_SLOT_TIME_DISTRI_C	0	// 时隙配比分布	BIT0：1代表15配比,BIT1：1代表24配比,	BIT2：1代表33配比			
#define 	PARA_A_1197_LOCK_ST		0	// A段1197锁定状态	
#define 	PARA_A_IF_ST	0	// A段中频频率,0/1---300M/500M		
#define 	PARA_ENCRYPTION_ST	0	//加密状态,0/1---不加密/加密
#define 	PARA_PWR_1V6_VT	0	//加密状态,0/1---不加密/加密
#define		PARA_A_90_VALUE			0				//A段9363 90寄存器的值
#define		PARA_A_91_VALUE			0				//A段9363 91寄存器的值
#define		PARA_A_94_VALUE			0				//A段9363 94寄存器的值
#define		PARA_A_95_VALUE			0				//A段9363 95寄存器的值
#define		PARA_B_90_VALUE			0				//B段9363 90寄存器的值
#define		PARA_B_91_VALUE			0				//B段9363 91寄存器的值
#define		PARA_B_94_VALUE			0				//B段9363 94寄存器的值
#define		PARA_B_95_VALUE			0				//B段9363 95寄存器的值
#define		PARA_C_90_VALUE			0				//C段9363 90寄存器的值
#define		PARA_C_91_VALUE			0				//C段9363 91寄存器的值
#define		PARA_C_94_VALUE			0				//C段9363 94寄存器的值
#define		PARA_C_95_VALUE			0				//C段9363 95寄存器的值
#define		PARA_D_90_VALUE			0				//D段9363 90寄存器的值
#define		PARA_D_91_VALUE			0				//D段9363 91寄存器的值
#define		PARA_D_94_VALUE			0				//D段9363 94寄存器的值
#define		PARA_D_95_VALUE			0				//D段9363 95寄存器的值
#define		PARA_PASSTHROUGH_EN			0				//测试透传使能
#define		PARA_A_DL_POW_ADJ			0			
#define		PARA_B_DL_POW_ADJ			0			
#define		PARA_C_DL_POW_ADJ			0			
#define		PARA_D_DL_POW_ADJ			0			
#define		PARA_SoftwareLoadTimes			0		
#define     PARA_A_LNA_EN_ST 		   0	// 	A段下行低噪放LNA开关使能

#endif

// 访问地址>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 1B
#define 	MADD_A_CHANNEL_COUNT 	0	// 	A段支持的通道数
#define 	MADD_A_DL_WORK_EN 	1	// 	A段下行工作使能
#define 	MADD_A_UL_WORK_EN 	2	// 	A段上行工作使能
#define 	MADD_A_DPOW_MODE 	3	// 	A段下行功率控制方式
#define 	MADD_A_UPOW_MODE 	4	// 	A段上行功率控制方式
#define 	MADD_A_LTHR_EN 	5	// 	A段上行底噪抑制使能
#define 	MADD_A_LTHR_UP 	6	// 	A段底噪抑制上门限
#define 	MADD_A_LTHR_DN 	7	// 	A段底噪抑制下门限
#define 	MADD_A_DCH_EN1 	8	// 	A段下行通道工作使能1
#define 	MADD_A_DCH_EN2 	9	// 	A段下行通道工作使能2
#define 	MADD_A_DCH_EN3 	10	// 	A段下行通道工作使能3
#define 	MADD_A_DCH_EN4 	11	// 	A段下行通道工作使能4
#define 	MADD_A_DCH_EN5 	12	// 	A段下行通道工作使能5
#define 	MADD_A_DCH_EN6 	13	// 	A段下行通道工作使能6
#define 	MADD_A_DCH_EN7 	14	// 	A段下行通道工作使能7
#define 	MADD_A_DCH_EN8 	15	// 	A段下行通道工作使能8
#define 	MADD_A_DCH_EN9 	16	// 	A段下行通道工作使能9
#define 	MADD_A_DCH_EN10 	17	// 	A段下行通道工作使能10
#define 	MADD_A_DCH_EN11 	18	// 	A段下行通道工作使能11
#define 	MADD_A_DCH_EN12 	19	// 	A段下行通道工作使能12
#define 	MADD_A_DCH_EN13 	20	// 	A段下行通道工作使能13
#define 	MADD_A_DCH_EN14 	21	// 	A段下行通道工作使能14
#define 	MADD_A_DCH_EN15 	22	// 	A段下行通道工作使能15
#define 	MADD_A_DCH_EN16 	23	// 	A段下行通道工作使能16
#define 	MADD_A_UCH_EN1 	24	// 	A段上行通道工作使能1
#define 	MADD_A_UCH_EN2 	25	// 	A段上行通道工作使能2
#define 	MADD_A_UCH_EN3 	26	// 	A段上行通道工作使能3
#define 	MADD_A_UCH_EN4 	27	// 	A段上行通道工作使能4
#define 	MADD_A_UCH_EN5 	28	// 	A段上行通道工作使能5
#define 	MADD_A_UCH_EN6 	29	// 	A段上行通道工作使能6
#define 	MADD_A_UCH_EN7 	30	// 	A段上行通道工作使能7
#define 	MADD_A_UCH_EN8 	31	// 	A段上行通道工作使能8
#define 	MADD_A_UCH_EN9 	32	// 	A段上行通道工作使能9
#define 	MADD_A_UCH_EN10 	33	// 	A段上行通道工作使能10
#define 	MADD_A_UCH_EN11 	34	// 	A段上行通道工作使能11
#define 	MADD_A_UCH_EN12 	35	// 	A段上行通道工作使能12
#define 	MADD_A_UCH_EN13 	36	// 	A段上行通道工作使能13
#define 	MADD_A_UCH_EN14 	37	// 	A段上行通道工作使能14
#define 	MADD_A_UCH_EN15 	38	// 	A段上行通道工作使能15
#define 	MADD_A_UCH_EN16 	39	// 	A段上行通道工作使能16
#define 	MADD_A_DCH_GAIN1 	40	// 	A段下行选频通道放大器增益1
#define 	MADD_A_DCH_GAIN2 	41	// 	A段下行选频通道放大器增益2
#define 	MADD_A_DCH_GAIN3 	42	// 	A段下行选频通道放大器增益3
#define 	MADD_A_DCH_GAIN4 	43	// 	A段下行选频通道放大器增益4
#define 	MADD_A_DCH_GAIN5 	44	// 	A段下行选频通道放大器增益5
#define 	MADD_A_DCH_GAIN6 	45	// 	A段下行选频通道放大器增益6
#define 	MADD_A_DCH_GAIN7 	46	// 	A段下行选频通道放大器增益7
#define 	MADD_A_DCH_GAIN8 	47	// 	A段下行选频通道放大器增益8
#define 	MADD_A_DCH_GAIN9 	48	// 	A段下行选频通道放大器增益9
#define 	MADD_A_DCH_GAIN10 	49	// 	A段下行选频通道放大器增益10
#define 	MADD_A_DCH_GAIN11 	50	// 	A段下行选频通道放大器增益11
#define 	MADD_A_DCH_GAIN12 	51	// 	A段下行选频通道放大器增益12
#define 	MADD_A_DCH_GAIN13 	52	// 	A段下行选频通道放大器增益13
#define 	MADD_A_DCH_GAIN14 	53	// 	A段下行选频通道放大器增益14
#define 	MADD_A_DCH_GAIN15 	54	// 	A段下行选频通道放大器增益15
#define 	MADD_A_DCH_GAIN16 	55	// 	A段下行选频通道放大器增益16
#define 	MADD_A_UCH_GAIN1 	56	// 	A段上行选频通道放大器增益1
#define 	MADD_A_UCH_GAIN2 	57	// 	A段上行选频通道放大器增益2
#define 	MADD_A_UCH_GAIN3 	58	// 	A段上行选频通道放大器增益3
#define 	MADD_A_UCH_GAIN4 	59	// 	A段上行选频通道放大器增益4
#define 	MADD_A_UCH_GAIN5 	60	// 	A段上行选频通道放大器增益5
#define 	MADD_A_UCH_GAIN6 	61	// 	A段上行选频通道放大器增益6
#define 	MADD_A_UCH_GAIN7 	62	// 	A段上行选频通道放大器增益7
#define 	MADD_A_UCH_GAIN8 	63	// 	A段上行选频通道放大器增益8
#define 	MADD_A_UCH_GAIN9 	64	// 	A段上行选频通道放大器增益9
#define 	MADD_A_UCH_GAIN10 	65	// 	A段上行选频通道放大器增益10
#define 	MADD_A_UCH_GAIN11 	66	// 	A段上行选频通道放大器增益11
#define 	MADD_A_UCH_GAIN12 	67	// 	A段上行选频通道放大器增益12
#define 	MADD_A_UCH_GAIN13 	68	// 	A段上行选频通道放大器增益13
#define 	MADD_A_UCH_GAIN14 	69	// 	A段上行选频通道放大器增益14
#define 	MADD_A_UCH_GAIN15 	70	// 	A段上行选频通道放大器增益15
#define 	MADD_A_UCH_GAIN16 	71	// 	A段上行选频通道放大器增益16
#define 	MADD_A_DCH_ATT1 	72	// 	A段下行数控衰减量1
#define 	MADD_A_DCH_ATT2 	73	// 	A段下行数控衰减量2
#define 	MADD_A_DCH_ATT3 	74	// 	A段下行数控衰减量3
#define 	MADD_A_DCH_ATT4 	75	// 	A段下行数控衰减量4
#define 	MADD_A_DCH_ATT5 	76	// 	A段下行数控衰减量5
#define 	MADD_A_DCH_ATT6 	77	// 	A段下行数控衰减量6
#define 	MADD_A_DCH_ATT7 	78	// 	A段下行数控衰减量7
#define 	MADD_A_DCH_ATT8 	79	// 	A段下行数控衰减量8
#define 	MADD_A_DCH_ATT9 	80	// 	A段下行数控衰减量9
#define 	MADD_A_DCH_ATT10 	81	// 	A段下行数控衰减量10
#define 	MADD_A_DCH_ATT11 	82	// 	A段下行数控衰减量11
#define 	MADD_A_DCH_ATT12 	83	// 	A段下行数控衰减量12
#define 	MADD_A_DCH_ATT13 	84	// 	A段下行数控衰减量13
#define 	MADD_A_DCH_ATT14 	85	// 	A段下行数控衰减量14
#define 	MADD_A_DCH_ATT15 	86	// 	A段下行数控衰减量15
#define 	MADD_A_DCH_ATT16 	87	// 	A段下行数控衰减量16
#define 	MADD_A_UCH_ATT1 	88	// 	A段上行数控衰减量1
#define 	MADD_A_UCH_ATT2 	89	// 	A段上行数控衰减量2
#define 	MADD_A_UCH_ATT3 	90	// 	A段上行数控衰减量3
#define 	MADD_A_UCH_ATT4 	91	// 	A段上行数控衰减量4
#define 	MADD_A_UCH_ATT5 	92	// 	A段上行数控衰减量5
#define 	MADD_A_UCH_ATT6 	93	// 	A段上行数控衰减量6
#define 	MADD_A_UCH_ATT7 	94	// 	A段上行数控衰减量7
#define 	MADD_A_UCH_ATT8 	95	// 	A段上行数控衰减量8
#define 	MADD_A_UCH_ATT9 	96	// 	A段上行数控衰减量9	
#define 	MADD_A_UCH_ATT10 	97	// 	A段上行数控衰减量10	
#define 	MADD_A_UCH_ATT11 	98	// 	A段上行数控衰减量11	
#define 	MADD_A_UCH_ATT12 	99	// 	A段上行数控衰减量12	
#define 	MADD_A_UCH_ATT13 	100	// 	A段上行数控衰减量13	
#define 	MADD_A_UCH_ATT14 	101	// 	A段上行数控衰减量14	
#define 	MADD_A_UCH_ATT15 	102	// 	A段上行数控衰减量15	
#define 	MADD_A_UCH_ATT16 	103	// 	A段上行数控衰减量16	
#define 	MADD_A_DL_PA_GAIN 	104	// 	A段下行功放增益	
#define 	MADD_A_UL_PA_GAIN 	105	// 	A段上行功放增益	
#define 	MADD_A_TX_PLL_ST 	106	// 	A段下行PLL状态,287 2为TX_VCO锁定，其他失锁	
#define 	MADD_A_RX_PLL_ST 	107	// 	A段上行PLL状态	,247 2为RX_VCO锁定，其他失锁
#define 	MADD_A_INIT_DA_ST 	108	// 	初始化A段DA状态	,17 1A为锁定+发送接收使能打开，其他异常
#define 	MADD_A_BB_PLL_LOCK 	109	// 	A段BB 	PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define 	MADD_A_FSAT 	110	// 	A段前端AD输入状态	
#define 	MADD_A_DSAT 	111	// 	A段后端DA输出状态	
#define 	MADD_A_PA_VG_EN 	112	// 	A段功放栅压状态
#define 	MADD_A_PA_VT 	113	// 	A段功放管电压显示
#define 	MADD_A_Modulator_EN 	114	// 	A段调制器状态
#define 	MADD_A_LNA_VT 	115	// 	A段下行低噪放LNA电压	
#define 	MADD_A_LNA1_ST 	116	// 	上行LNA1状态	
#define 	MADD_A_LNA2_ST 	117	// 	上行LNA2状态	
#define 	MADD_A_BUSY_TIME 	118	// 	A段上行时隙占用率	
#define 	MADD_A_PRI_ADD 	119	// 	A段模块地址	
#define 	MADD_A_UL_POW_1B 	120	// 	A段上行输入总功率	
#define 	MADD_A_DL_POW_1B 	121	// 	A段下行输入总功率	
#define 	MADD_A_DCH_REC_RF_ATT1	122	//// 	REC端的下行数控衰减量。即RF端的链路下行衰减量 	在rf
#define 	MADD_A_UCH_REC_RF_ATT1	123	//// 	REC端的上行数控衰减量。即RF端的链路上行衰减量 	在rf
#define 	MADD_B_CHANNEL_COUNT 	124	// 	B段支持的通道数	
#define 	MADD_B_DL_WORK_EN 	125	// 	B段下行工作使能	
#define 	MADD_B_UL_WORK_EN 	126	// 	B段上行工作使能	
#define 	MADD_B_DPOW_MODE 	127	// 	B段下行功率控制方式	
#define 	MADD_B_UPOW_MODE 	128	// 	B段上行功率控制方式
#define 	MADD_B_LTHR_EN 	129	// 	B段上行底噪抑制使能
#define 	MADD_B_LTHR_UP 	130	// 	B段底噪抑制上门限
#define 	MADD_B_LTHR_DN 	131	// 	B段底噪抑制下门限
#define 	MADD_B_DCH_EN1 	132	// 	B段下行通道工作使能1
#define 	MADD_B_DCH_EN2 	133	// 	B段下行通道工作使能2
#define 	MADD_B_DCH_EN3 	134	// 	B段下行通道工作使能3
#define 	MADD_B_DCH_EN4 	135	// 	B段下行通道工作使能4
#define 	MADD_B_DCH_EN5 	136	// 	B段下行通道工作使能5
#define 	MADD_B_DCH_EN6 	137	// 	B段下行通道工作使能6
#define 	MADD_B_DCH_EN7 	138	// 	B段下行通道工作使能7
#define 	MADD_B_DCH_EN8 	139	// 	B段下行通道工作使能8
#define 	MADD_B_DCH_EN9 	140	// 	B段下行通道工作使能9
#define 	MADD_B_DCH_EN10 	141	// 	B段下行通道工作使能10
#define 	MADD_B_DCH_EN11 	142	// 	B段下行通道工作使能11
#define 	MADD_B_DCH_EN12 	143	// 	B段下行通道工作使能12
#define 	MADD_B_DCH_EN13 	144	// 	B段下行通道工作使能13
#define 	MADD_B_DCH_EN14 	145	// 	B段下行通道工作使能14
#define 	MADD_B_DCH_EN15 	146	// 	B段下行通道工作使能15
#define 	MADD_B_DCH_EN16 	147	// 	B段下行通道工作使能16
#define 	MADD_B_UCH_EN1 	148	// 	B段上行通道工作使能1
#define 	MADD_B_UCH_EN2 	149	// 	B段上行通道工作使能2
#define 	MADD_B_UCH_EN3 	150	// 	B段上行通道工作使能3
#define 	MADD_B_UCH_EN4 	151	// 	B段上行通道工作使能4
#define 	MADD_B_UCH_EN5 	152	// 	B段上行通道工作使能5
#define 	MADD_B_UCH_EN6 	153	// 	B段上行通道工作使能6
#define 	MADD_B_UCH_EN7 	154	// 	B段上行通道工作使能7
#define 	MADD_B_UCH_EN8 	155	// 	B段上行通道工作使能8
#define 	MADD_B_UCH_EN9 	156	// 	B段上行通道工作使能9
#define 	MADD_B_UCH_EN10 	157	// 	B段上行通道工作使能10
#define 	MADD_B_UCH_EN11 	158	// 	B段上行通道工作使能11
#define 	MADD_B_UCH_EN12 	159	// 	B段上行通道工作使能12
#define 	MADD_B_UCH_EN13 	160	// 	B段上行通道工作使能13
#define 	MADD_B_UCH_EN14 	161	// 	B段上行通道工作使能14
#define 	MADD_B_UCH_EN15 	162	// 	B段上行通道工作使能15
#define 	MADD_B_UCH_EN16 	163	// 	B段上行通道工作使能16
#define 	MADD_B_DCH_GAIN1 	164	// 	B段下行选频通道放大器增益1
#define 	MADD_B_DCH_GAIN2 	165	// 	B段下行选频通道放大器增益2
#define 	MADD_B_DCH_GAIN3 	166	// 	B段下行选频通道放大器增益3
#define 	MADD_B_DCH_GAIN4 	167	// 	B段下行选频通道放大器增益4
#define 	MADD_B_DCH_GAIN5 	168	// 	B段下行选频通道放大器增益5
#define 	MADD_B_DCH_GAIN6 	169	// 	B段下行选频通道放大器增益6
#define 	MADD_B_DCH_GAIN7 	170	// 	B段下行选频通道放大器增益7
#define 	MADD_B_DCH_GAIN8 	171	// 	B段下行选频通道放大器增益8
#define 	MADD_B_DCH_GAIN9 	172	// 	B段下行选频通道放大器增益9
#define 	MADD_B_DCH_GAIN10 	173	// 	B段下行选频通道放大器增益10
#define 	MADD_B_DCH_GAIN11 	174	// 	B段下行选频通道放大器增益11
#define 	MADD_B_DCH_GAIN12 	175	// 	B段下行选频通道放大器增益12
#define 	MADD_B_DCH_GAIN13 	176	// 	B段下行选频通道放大器增益13
#define 	MADD_B_DCH_GAIN14 	177	// 	B段下行选频通道放大器增益14
#define 	MADD_B_DCH_GAIN15 	178	// 	B段下行选频通道放大器增益15
#define 	MADD_B_DCH_GAIN16 	179	// 	B段下行选频通道放大器增益16
#define 	MADD_B_UCH_GAIN1 	180	// 	B段上行选频通道放大器增益1
#define 	MADD_B_UCH_GAIN2 	181	// 	B段上行选频通道放大器增益2
#define 	MADD_B_UCH_GAIN3 	182	// 	B段上行选频通道放大器增益3
#define 	MADD_B_UCH_GAIN4 	183	// 	B段上行选频通道放大器增益4
#define 	MADD_B_UCH_GAIN5 	184	// 	B段上行选频通道放大器增益5
#define 	MADD_B_UCH_GAIN6 	185	// 	B段上行选频通道放大器增益6
#define 	MADD_B_UCH_GAIN7 	186	// 	B段上行选频通道放大器增益7
#define 	MADD_B_UCH_GAIN8 	187	// 	B段上行选频通道放大器增益8
#define 	MADD_B_UCH_GAIN9 	188	// 	B段上行选频通道放大器增益9
#define 	MADD_B_UCH_GAIN10 	189	// 	B段上行选频通道放大器增益10
#define 	MADD_B_UCH_GAIN11 	190	// 	B段上行选频通道放大器增益11
#define 	MADD_B_UCH_GAIN12 	191	// 	B段上行选频通道放大器增益12
#define 	MADD_B_UCH_GAIN13 	192	// 	B段上行选频通道放大器增益13
#define 	MADD_B_UCH_GAIN14 	193	// 	B段上行选频通道放大器增益14
#define 	MADD_B_UCH_GAIN15 	194	// 	B段上行选频通道放大器增益15
#define 	MADD_B_UCH_GAIN16 	195	// 	B段上行选频通道放大器增益16
#define 	MADD_B_DCH_ATT1 	196	// 	B段下行输出数控衰减量1
#define 	MADD_B_DCH_ATT2 	197	// 	B段下行输出数控衰减量2
#define 	MADD_B_DCH_ATT3 	198	// 	B段下行输出数控衰减量3
#define 	MADD_B_DCH_ATT4 	199	// 	B段下行输出数控衰减量4
#define 	MADD_B_DCH_ATT5 	200	// 	B段下行输出数控衰减量5
#define 	MADD_B_DCH_ATT6 	201	// 	B段下行输出数控衰减量6
#define 	MADD_B_DCH_ATT7 	202	// 	B段下行输出数控衰减量7
#define 	MADD_B_DCH_ATT8 	203	// 	B段下行输出数控衰减量8
#define 	MADD_B_DCH_ATT9 	204	// 	B段下行输出数控衰减量9
#define 	MADD_B_DCH_ATT10 	205	// 	B段下行输出数控衰减量10
#define 	MADD_B_DCH_ATT11 	206	// 	B段下行输出数控衰减量11
#define 	MADD_B_DCH_ATT12 	207	// 	B段下行输出数控衰减量12
#define 	MADD_B_DCH_ATT13 	208	// 	B段下行输出数控衰减量13
#define 	MADD_B_DCH_ATT14 	209	// 	B段下行输出数控衰减量14
#define 	MADD_B_DCH_ATT15 	210	// 	B段下行输出数控衰减量15
#define 	MADD_B_DCH_ATT16 	211	// 	B段下行输出数控衰减量16
#define 	MADD_B_UCH_ATT1 	212	// 	B段上行输入数控衰减量1
#define 	MADD_B_UCH_ATT2 	213	// 	B段上行输入数控衰减量2
#define 	MADD_B_UCH_ATT3 	214	// 	B段上行输入数控衰减量3
#define 	MADD_B_UCH_ATT4 	215	// 	B段上行输入数控衰减量4
#define 	MADD_B_UCH_ATT5 	216	// 	B段上行输入数控衰减量5
#define 	MADD_B_UCH_ATT6 	217	// 	B段上行输入数控衰减量6
#define 	MADD_B_UCH_ATT7 	218	// 	B段上行输入数控衰减量7
#define 	MADD_B_UCH_ATT8 	219	// 	B段上行输入数控衰减量8
#define 	MADD_B_UCH_ATT9 	220	// 	B段上行输入数控衰减量9
#define 	MADD_B_UCH_ATT10 	221	// 	B段上行输入数控衰减量10
#define 	MADD_B_UCH_ATT11 	222	// 	B段上行输入数控衰减量11
#define 	MADD_B_UCH_ATT12 	223	// 	B段上行输入数控衰减量12
#define 	MADD_B_UCH_ATT13 	224	// 	B段上行输入数控衰减量13	
#define 	MADD_B_UCH_ATT14 	225	// 	B段上行输入数控衰减量14	
#define 	MADD_B_UCH_ATT15 	226	// 	B段上行输入数控衰减量15	
#define 	MADD_B_UCH_ATT16 	227	// 	B段上行输入数控衰减量16	
#define 	MADD_B_DL_PA_GAIN 	228	// 	B段下行功放增益	
#define 	MADD_B_UL_PA_GAIN 	229	// 	B段上行功放增益	
#define 	MADD_B_TX_PLL_ST 	230	// 	B段下行PLL状态	,287 2为TX_VCO锁定，其他失锁
#define 	MADD_B_RX_PLL_ST 	231	// 	B段上行PLL状态,247 2为RX_VCO锁定，其他失锁	
#define 	MADD_B_INIT_DA_ST 	232	// 	初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常	
#define 	MADD_B_BB_PLL_LOCK 	233	// 	B段BB 	PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define 	MADD_B_FSAT 	234	// 	B段前端AD输入状态	
#define 	MADD_B_DSAT 	235	// 	B段后端DA输出状态	
#define 	MADD_B_PA_VG_EN 	236	// 	B段功放栅压状态
#define 	MADD_B_PA_VT 	237	// 	B段功放管电压显示
#define 	MADD_B_Modulator_EN 	238	// 	B段调制器状态
#define 	MADD_B_LNA_VT 	239	// 	B段下行低噪放LNA电压	
#define 	MADD_B_LNA1_ST 	240	// 	上行LNA1状态		
#define 	MADD_B_LNA2_ST 	241	// 	上行LNA2状态		
#define 	MADD_B_BUSY_TIME 	242	// 	B段上行时隙占用率		
#define 	MADD_B_PRI_ADD 	243	// 	B段模块地址		
#define 	MADD_B_UL_POW_1B 	244	// 	B段上行输入总功率		
#define 	MADD_B_DL_POW_1B 	245	// 	B段下行输入总功率		
#define 	MADD_B_DCH_REC_RF_ATT1	246	//// 	REC端的下行数控衰减量。即RF端的链路下行衰减量 	在rf
#define 	MADD_B_UCH_REC_RF_ATT1  	247	 //// 	REC端的上行数控衰减量。即RF端的链路上行衰减量 	 	在rf
#define 	MADD_C_CHANNEL_COUNT 	248	// 	C段支持的通道数		
#define 	MADD_C_DL_WORK_EN 	249	// 	C段下行工作使能		
#define 	MADD_C_UL_WORK_EN 	250	// 	C段上行工作使能		
#define 	MADD_C_DPOW_MODE 	251	// 	C段下行功率控制方式		
#define 	MADD_C_UPOW_MODE 	252	// 	C段上行功率控制方式		
#define 	MADD_C_LTHR_EN 	253	// 	C段上行底噪抑制使能		
#define 	MADD_C_LTHR_UP 	254	// 	C段底噪抑制上门限		
#define 	MADD_C_LTHR_DN 	255	// 	C段底噪抑制下门限		
#define 	MADD_C_DCH_EN1 	256	// 	C段下行通道工作使能1
#define 	MADD_C_DCH_EN2 	257	// 	C段下行通道工作使能2
#define 	MADD_C_DCH_EN3 	258	// 	C段下行通道工作使能3
#define 	MADD_C_DCH_EN4 	259	// 	C段下行通道工作使能4
#define 	MADD_C_DCH_EN5 	260	// 	C段下行通道工作使能5
#define 	MADD_C_DCH_EN6 	261	// 	C段下行通道工作使能6
#define 	MADD_C_DCH_EN7 	262	// 	C段下行通道工作使能7
#define 	MADD_C_DCH_EN8 	263	// 	C段下行通道工作使能8
#define 	MADD_C_DCH_EN9 	264	// 	C段下行通道工作使能9
#define 	MADD_C_DCH_EN10 	265	// 	C段下行通道工作使能10
#define 	MADD_C_UCH_EN1 	266	// 	C段上行通道工作使能1
#define 	MADD_C_UCH_EN2 	267	// 	C段上行通道工作使能2
#define 	MADD_C_UCH_EN3 	268	// 	C段上行通道工作使能3
#define 	MADD_C_UCH_EN4 	269	// 	C段上行通道工作使能4
#define 	MADD_C_UCH_EN5 	270	// 	C段上行通道工作使能5
#define 	MADD_C_UCH_EN6 	271	// 	C段上行通道工作使能6
#define 	MADD_C_UCH_EN7 	272	// 	C段上行通道工作使能7
#define 	MADD_C_UCH_EN8 	273	// 	C段上行通道工作使能8
#define 	MADD_C_UCH_EN9 	274	// 	C段上行通道工作使能9
#define 	MADD_C_UCH_EN10 	275	// 	C段上行通道工作使能10
#define 	MADD_C_DCH_GAIN1 	276	// 	C段下行选频通道放大器增益1
#define 	MADD_C_DCH_GAIN2 	277	// 	C段下行选频通道放大器增益2
#define 	MADD_C_DCH_GAIN3 	278	// 	C段下行选频通道放大器增益3
#define 	MADD_C_DCH_GAIN4 	279	// 	C段下行选频通道放大器增益4
#define 	MADD_C_DCH_GAIN5 	280	// 	C段下行选频通道放大器增益5
#define 	MADD_C_DCH_GAIN6 	281	// 	C段下行选频通道放大器增益6
#define 	MADD_C_DCH_GAIN7 	282	// 	C段下行选频通道放大器增益7
#define 	MADD_C_DCH_GAIN8 	283	// 	C段下行选频通道放大器增益8
#define 	MADD_C_DCH_GAIN9 	284	// 	C段下行选频通道放大器增益9
#define 	MADD_C_DCH_GAIN10 	285	// 	C段下行选频通道放大器增益10
#define 	MADD_C_DCH_GAIN11 	286	// 	C段下行选频通道放大器增益11
#define 	MADD_C_DCH_GAIN12 	287	// 	C段下行选频通道放大器增益12
#define 	MADD_C_DCH_GAIN13 	288	// 	C段下行选频通道放大器增益13
#define 	MADD_C_DCH_GAIN14 	289	// 	C段下行选频通道放大器增益14
#define 	MADD_C_DCH_GAIN15 	290	// 	C段下行选频通道放大器增益15
#define 	MADD_C_DCH_GAIN16 	291	// 	C段下行选频通道放大器增益16
#define 	MADD_C_UCH_GAIN1 	292	// 	C段上行选频通道放大器增益1
#define 	MADD_C_UCH_GAIN2 	293	// 	C段上行选频通道放大器增益2
#define 	MADD_C_UCH_GAIN3 	294	// 	C段上行选频通道放大器增益3
#define 	MADD_C_UCH_GAIN4 	295	// 	C段上行选频通道放大器增益4
#define 	MADD_C_UCH_GAIN5 	296	// 	C段上行选频通道放大器增益5
#define 	MADD_C_UCH_GAIN6 	297	// 	C段上行选频通道放大器增益6
#define 	MADD_C_UCH_GAIN7 	298	// 	C段上行选频通道放大器增益7
#define 	MADD_C_UCH_GAIN8 	299	// 	C段上行选频通道放大器增益8
#define 	MADD_C_UCH_GAIN9 	300	// 	C段上行选频通道放大器增益9
#define 	MADD_C_UCH_GAIN10 	301	// 	C段上行选频通道放大器增益10
#define 	MADD_C_UCH_GAIN11 	302	// 	C段上行选频通道放大器增益11
#define 	MADD_C_UCH_GAIN12 	303	// 	C段上行选频通道放大器增益12
#define 	MADD_C_UCH_GAIN13 	304	// 	C段上行选频通道放大器增益13
#define 	MADD_C_UCH_GAIN14 	305	// 	C段上行选频通道放大器增益14
#define 	MADD_C_UCH_GAIN15 	306	// 	C段上行选频通道放大器增益15
#define 	MADD_C_UCH_GAIN16 	307	// 	C段上行选频通道放大器增益16
#define 	MADD_C_DCH_ATT1 	308	// 	C段下行数控衰减量1
#define 	MADD_C_DCH_ATT2 	309	// 	C段下行数控衰减量2
#define 	MADD_C_DCH_ATT3 	310	// 	C段下行数控衰减量3
#define 	MADD_C_DCH_ATT4 	311	// 	C段下行数控衰减量4
#define 	MADD_C_DCH_ATT5 	312	// 	C段下行数控衰减量5
#define 	MADD_C_DCH_ATT6 	313	// 	C段下行数控衰减量6
#define 	MADD_C_DCH_ATT7 	314	// 	C段下行数控衰减量7
#define 	MADD_C_DCH_ATT8 	315	// 	C段下行数控衰减量8
#define 	MADD_C_DCH_ATT9 	316	// 	C段下行数控衰减量9
#define 	MADD_C_DCH_ATT10 	317	// 	C段下行数控衰减量10
#define 	MADD_C_DCH_ATT11 	318	// 	C段下行数控衰减量11
#define 	MADD_C_DCH_ATT12 	319	// 	C段下行数控衰减量12
#define 	MADD_C_DCH_ATT13 	320	// 	C段下行数控衰减量13
#define 	MADD_C_DCH_ATT14 	321	// 	C段下行数控衰减量14
#define 	MADD_C_DCH_ATT15 	322	// 	C段下行数控衰减量15
#define 	MADD_C_DCH_ATT16 	323	// 	C段下行数控衰减量16
#define 	MADD_C_UCH_ATT1 	324	// 	C段上行数控衰减量1
#define 	MADD_C_UCH_ATT2 	325	// 	C段上行数控衰减量2
#define 	MADD_C_UCH_ATT3 	326	// 	C段上行数控衰减量3
#define 	MADD_C_UCH_ATT4 	327	// 	C段上行数控衰减量4
#define 	MADD_C_UCH_ATT5 	328	// 	C段上行数控衰减量5
#define 	MADD_C_UCH_ATT6 	329	// 	C段上行数控衰减量6
#define 	MADD_C_UCH_ATT7 	330	// 	C段上行数控衰减量7
#define 	MADD_C_UCH_ATT8 	331	// 	C段上行数控衰减量8
#define 	MADD_C_UCH_ATT9 	332	// 	C段上行数控衰减量9
#define 	MADD_C_UCH_ATT10 	333	// 	C段上行数控衰减量10
#define 	MADD_C_UCH_ATT11 	334	// 	C段上行数控衰减量11
#define 	MADD_C_UCH_ATT12 	335	// 	C段上行数控衰减量12
#define 	MADD_C_UCH_ATT13 	336	// 	C段上行数控衰减量13	
#define 	MADD_C_UCH_ATT14 	337	// 	C段上行数控衰减量14	
#define 	MADD_C_UCH_ATT15 	338	// 	C段上行数控衰减量15	
#define 	MADD_C_UCH_ATT16 	339	// 	C段上行数控衰减量16	
#define 	MADD_C_DL_PA_GAIN 	340	// 	C段下行功放增益	
#define 	MADD_C_UL_PA_GAIN 	341	// 	C段上行功放增益	
#define 	MADD_C_TX_PLL_ST 	342	// 	C段下行PLL状态,287 2为TX_VCO锁定，其他失锁	
#define 	MADD_C_RX_PLL_ST 	343	// 	C段上行PLL状态,247 2为RX_VCO锁定，其他失锁	
#define 	MADD_C_INIT_DA_ST 	344	// 	初始化A段DA状态	,17 1A为锁定+发送接收使能打开，其他异常
#define 	MADD_C_BB_PLL_LOCK 	345	// 	C段BB 	PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define 	MADD_C_FSAT 	346	// 	C段前端AD输入状态	
#define 	MADD_C_DSAT 	347	// 	C段后端DA输出状态	
#define 	MADD_C_PA_VG_EN 	348	// 	C段功放栅压状态
#define 	MADD_C_PA_VT 	349	// 	C段功放管电压显示
#define 	MADD_C_Modulator_EN 	350	// 	C段调制器状态
#define 	MADD_C_LNA_VT 	351	// 	C段下行低噪放LNA电压	
#define 	MADD_C_LNA1_ST 	352	// 	上行LNA1状态	
#define 	MADD_C_LNA2_ST 	353	// 	上行LNA2状态	
#define 	MADD_C_BUSY_TIME 	354	// 	C段上行时隙占用率	
#define 	MADD_C_PRI_ADD 	355	// 	C段模块地址	
#define 	MADD_C_UL_POW_1B 	356	// 	C段上行输入总功率	
#define 	MADD_C_DL_POW_1B 	357	// 	C段下行输入总功率	
#define 	MADD_C_DCH_REC_RF_ATT1	358	//// 	REC端的下行数控衰减量。即RF端的链路下行衰减量 	在rf
#define 	MADD_C_UCH_REC_RF_ATT1	359	//// 	REC端的上行数控衰减量。即RF端的链路上行衰减量 	在rf
#define 	MADD_D_CHANNEL_COUNT 	360	// 	D段支持的通道数	
#define 	MADD_D_DL_WORK_EN 	361	// 	D段下行工作使能	
#define 	MADD_D_UL_WORK_EN 	362	// 	D段上行工作使能	
#define 	MADD_D_DPOW_MODE 	363	// 	D段下行功率控制方式	
#define 	MADD_D_UPOW_MODE 	364	// 	D段上行功率控制方式	
#define 	MADD_D_LTHR_EN 	365	// 	D段上行底噪抑制使能	
#define 	MADD_D_LTHR_UP 	366	// 	D段底噪抑制上门限	
#define 	MADD_D_LTHR_DN 	367	// 	D段底噪抑制下门限	
#define 	MADD_D_DCH_EN1 	368	// 	D段下行通道工作使能1
#define 	MADD_D_DCH_EN2 	369	// 	D段下行通道工作使能2
#define 	MADD_D_DCH_EN3 	370	// 	D段下行通道工作使能3
#define 	MADD_D_DCH_EN4 	371	// 	D段下行通道工作使能4
#define 	MADD_D_DCH_EN5 	372	// 	D段下行通道工作使能5
#define 	MADD_D_DCH_EN6 	373	// 	D段下行通道工作使能6
#define 	MADD_D_DCH_EN7 	374	// 	D段下行通道工作使能7
#define 	MADD_D_DCH_EN8 	375	// 	D段下行通道工作使能8
#define 	MADD_D_DCH_EN9 	376	// 	D段下行通道工作使能9
#define 	MADD_D_DCH_EN10 	377	// 	D段下行通道工作使能10
#define 	MADD_D_UCH_EN1 	378	// 	D段上行通道工作使能1
#define 	MADD_D_UCH_EN2 	379	// 	D段上行通道工作使能2
#define 	MADD_D_UCH_EN3 	380	// 	D段上行通道工作使能3
#define 	MADD_D_UCH_EN4 	381	// 	D段上行通道工作使能4
#define 	MADD_D_UCH_EN5 	382	// 	D段上行通道工作使能5
#define 	MADD_D_UCH_EN6 	383	// 	D段上行通道工作使能6
#define 	MADD_D_UCH_EN7 	384	// 	D段上行通道工作使能7
#define 	MADD_D_UCH_EN8 	385	// 	D段上行通道工作使能8
#define 	MADD_D_UCH_EN9 	386	// 	D段上行通道工作使能9
#define 	MADD_D_UCH_EN10 	387	// 	D段上行通道工作使能10
#define 	MADD_D_DCH_GAIN1 	388	// 	D段下行选频通道放大器增益1
#define 	MADD_D_DCH_GAIN2 	389	// 	D段下行选频通道放大器增益2
#define 	MADD_D_DCH_GAIN3 	390	// 	D段下行选频通道放大器增益3
#define 	MADD_D_DCH_GAIN4 	391	// 	D段下行选频通道放大器增益4
#define 	MADD_D_DCH_GAIN5 	392	// 	D段下行选频通道放大器增益5
#define 	MADD_D_DCH_GAIN6 	393	// 	D段下行选频通道放大器增益6
#define 	MADD_D_DCH_GAIN7 	394	// 	D段下行选频通道放大器增益7
#define 	MADD_D_DCH_GAIN8 	395	// 	D段下行选频通道放大器增益8
#define 	MADD_D_DCH_GAIN9 	396	// 	D段下行选频通道放大器增益9
#define 	MADD_D_DCH_GAIN10 	397	// 	D段下行选频通道放大器增益10
#define 	MADD_D_DCH_GAIN11 	398	// 	D段下行选频通道放大器增益11
#define 	MADD_D_DCH_GAIN12 	399	// 	D段下行选频通道放大器增益12
#define 	MADD_D_DCH_GAIN13 	400	// 	D段下行选频通道放大器增益13
#define 	MADD_D_DCH_GAIN14 	401	// 	D段下行选频通道放大器增益14
#define 	MADD_D_DCH_GAIN15 	402	// 	D段下行选频通道放大器增益15
#define 	MADD_D_DCH_GAIN16 	403	// 	D段下行选频通道放大器增益16
#define 	MADD_D_UCH_GAIN1 	404	// 	D段上行选频通道放大器增益1
#define 	MADD_D_UCH_GAIN2 	405	// 	D段上行选频通道放大器增益2
#define 	MADD_D_UCH_GAIN3 	406	// 	D段上行选频通道放大器增益3
#define 	MADD_D_UCH_GAIN4 	407	// 	D段上行选频通道放大器增益4
#define 	MADD_D_UCH_GAIN5 	408	// 	D段上行选频通道放大器增益5
#define 	MADD_D_UCH_GAIN6 	409	// 	D段上行选频通道放大器增益6
#define 	MADD_D_UCH_GAIN7 	410	// 	D段上行选频通道放大器增益7
#define 	MADD_D_UCH_GAIN8 	411	// 	D段上行选频通道放大器增益8
#define 	MADD_D_UCH_GAIN9 	412	// 	D段上行选频通道放大器增益9
#define 	MADD_D_UCH_GAIN10 	413	// 	D段上行选频通道放大器增益10
#define 	MADD_D_UCH_GAIN11 	414	// 	D段上行选频通道放大器增益11
#define 	MADD_D_UCH_GAIN12 	415	// 	D段上行选频通道放大器增益12
#define 	MADD_D_UCH_GAIN13 	416	// 	D段上行选频通道放大器增益13
#define 	MADD_D_UCH_GAIN14 	417	// 	D段上行选频通道放大器增益14
#define 	MADD_D_UCH_GAIN15 	418	// 	D段上行选频通道放大器增益15
#define 	MADD_D_UCH_GAIN16 	419	// 	D段上行选频通道放大器增益16
#define 	MADD_D_DCH_ATT1 	420	// 	D段下行输出数控衰减量1
#define 	MADD_D_DCH_ATT2 	421	// 	D段下行输出数控衰减量2
#define 	MADD_D_DCH_ATT3 	422	// 	D段下行输出数控衰减量3
#define 	MADD_D_DCH_ATT4 	423	// 	D段下行输出数控衰减量4
#define 	MADD_D_DCH_ATT5 	424	// 	D段下行输出数控衰减量5
#define 	MADD_D_DCH_ATT6 	425	// 	D段下行输出数控衰减量6
#define 	MADD_D_DCH_ATT7 	426	// 	D段下行输出数控衰减量7
#define 	MADD_D_DCH_ATT8 	427	// 	D段下行输出数控衰减量8
#define 	MADD_D_DCH_ATT9 	428	// 	D段下行输出数控衰减量9
#define 	MADD_D_DCH_ATT10 	429	// 	D段下行输出数控衰减量10
#define 	MADD_D_DCH_ATT11 	430	// 	D段下行输出数控衰减量11
#define 	MADD_D_DCH_ATT12 	431	// 	D段下行输出数控衰减量12
#define 	MADD_D_DCH_ATT13 	432	// 	D段下行输出数控衰减量13
#define 	MADD_D_DCH_ATT14	433	// 	D段下行输出数控衰减量14
#define 	MADD_D_DCH_ATT15 	434	// 	D段下行输出数控衰减量15
#define 	MADD_D_DCH_ATT16 	435	// 	D段下行输出数控衰减量16
#define 	MADD_D_UCH_ATT1 	436	// 	D段上行输入数控衰减量1
#define 	MADD_D_UCH_ATT2 	437	// 	D段上行输入数控衰减量2
#define 	MADD_D_UCH_ATT3 	438	// 	D段上行输入数控衰减量3
#define 	MADD_D_UCH_ATT4 	439	// 	D段上行输入数控衰减量4
#define 	MADD_D_UCH_ATT5 	440	// 	D段上行输入数控衰减量5
#define 	MADD_D_UCH_ATT6 	441	// 	D段上行输入数控衰减量6
#define 	MADD_D_UCH_ATT7 	442	// 	D段上行输入数控衰减量7
#define 	MADD_D_UCH_ATT8 	443	// 	D段上行输入数控衰减量8
#define 	MADD_D_UCH_ATT9 	444	// 	D段上行输入数控衰减量9
#define 	MADD_D_UCH_ATT10 	445	// 	D段上行输入数控衰减量10
#define 	MADD_D_UCH_ATT11 	446	// 	D段上行输入数控衰减量11
#define 	MADD_D_UCH_ATT12 	447	// 	D段上行输入数控衰减量12
#define 	MADD_D_UCH_ATT13 	448	// 	D段上行输入数控衰减量13	
#define 	MADD_D_UCH_ATT14 	449	// 	D段上行输入数控衰减量14	
#define 	MADD_D_UCH_ATT15	450	// 	D段上行输入数控衰减量15	
#define 	MADD_D_UCH_ATT16 	451	// 	D段上行输入数控衰减量16	
#define 	MADD_D_DL_PA_GAIN 	452	// 	D段下行功放增益	
#define 	MADD_D_UL_PA_GAIN 	453	// 	D段上行功放增益	
#define 	MADD_D_TX_PLL_ST 	454	// 	D段下行PLL状态	,287 2为TX_VCO锁定，其他失锁
#define 	MADD_D_RX_PLL_ST 	455	// 	D段上行PLL状态,247 2为RX_VCO锁定，其他失锁	
#define 	MADD_D_INIT_DA_ST 	456	// 	初始化B段DA状态,17 1A为锁定+发送接收使能打开，其他异常	
#define 	MADD_D_BB_PLL_LOCK 	457	// 	D段BB 	PLL锁定状态,5E 80为BBPLL数字锁相环锁定，其他失锁
#define 	MADD_D_FSAT 	458	// 	D段前端AD输入状态	
#define 	MADD_D_DSAT 	459	// 	D段后端DA输出状态	
#define 	MADD_D_PA_VG_EN 	460	// 	D段功放栅压状态
#define 	MADD_D_PA_VT 	461	// 	D段功放管电压显示	
#define 	MADD_D_Modulator_EN 	462	// 	D段调制器状态
#define 	MADD_D_LNA_VT 	463	// 	D段下行低噪放LNA电压	
#define 	MADD_D_LNA1_ST 	464	// 	上行LNA1状态		
#define 	MADD_D_LNA2_ST 	465	// 	上行LNA2状态		
#define 	MADD_D_BUSY_TIME 	466	// 	D段上行时隙占用率		
#define 	MADD_D_PRI_ADD 	467	// 	D段模块地址		
#define 	MADD_D_UL_POW_1B 	468	// 	D段上行输入总功率		
#define 	MADD_D_DL_POW_1B 	469	// 	D段下行输入总功率		
#define 	MADD_D_DCH_REC_RF_ATT1	470	//// 	REC端的下行数控衰减量。即RF端的链路下行衰减量 	在rf
#define 	MADD_D_UCH_REC_RF_ATT1  	471	 //// 	REC端的上行数控衰减量。即RF端的链路上行衰减量 	 	在rf
#define	MADD_FP1_EN	472	//	光口发送使能1		
#define	MADD_FP2_EN	473	//	光口发送使能2		
#define	MADD_FP3_EN	474	//	光口发送使能3		
#define	MADD_FP4_EN	475	//	光口发送使能4		
#define	MADD_FP5_EN	476	//	光口发送使能5		
#define	MADD_FP6_EN	477	//	光口发送使能6		
#define	MADD_FP7_EN	478	//	光口发送使能7		
#define	MADD_FP8_EN	479	//	光口发送使能8		
#define	MADD_FP9_EN	480	//	光口发送使能9	
#define	MADD_FP10_EN	481	//	光口发送使能10	
#define	MADD_FP11_EN	482	//	光口发送使能11	
#define	MADD_FP12_EN	483	//	光口发送使能12	
#define	MADD_FP13_EN	484	//	光口发送使能13	
#define	MADD_FP14_EN	485	//	光口发送使能14	
#define	MADD_FP15_EN	486	//	光口发送使能15	
#define	MADD_FP16_EN	487	//	光口发送使能16	
#define	MADD_FP1_ON_POS	488	//	光口在位状态1,	0-在位
#define	MADD_FP2_ON_POS	489	//	光口在位状态2,	0-在位
#define	MADD_FP3_ON_POS	490	//	光口在位状态3,	0-在位
#define	MADD_FP4_ON_POS	491	//	光口在位状态4,	0-在位
#define	MADD_FP5_ON_POS	492	//	光口在位状态5,	0-在位
#define	MADD_FP6_ON_POS	493	//	光口在位状态6,	0-在位
#define	MADD_FP7_ON_POS	494	//	光口在位状态7,	0-在位
#define	MADD_FP8_ON_POS	495	//	光口在位状态8,	0-在位
#define	MADD_FP9_ON_POS	496	//	光口在位状态9,	0-在位
#define	MADD_FP10_ON_POS	497	//	光口在位状态10,	0-在位
#define	MADD_FP11_ON_POS	498	//	光口在位状态11,	0-在位
#define	MADD_FP12_ON_POS	499	//	光口在位状态12,	0-在位
#define	MADD_FP13_ON_POS	500	//	光口在位状态13,	0-在位
#define	MADD_FP14_ON_POS	501	//	光口在位状态14,	0-在位
#define	MADD_FP15_ON_POS	502	//	光口在位状态15,	0-在位
#define	MADD_FP16_ON_POS	503	//	光口在位状态16,	0-在位
#define	MADD_FP1_LOS	504	//	光口1信号丢失状态	
#define	MADD_FP2_LOS	505	//	光口2信号丢失状态	
#define	MADD_FP3_LOS	506	//	光口3信号丢失状态	
#define	MADD_FP4_LOS	507	//	光口4信号丢失状态	
#define	MADD_FP5_LOS	508	//	光口5信号丢失状态	
#define	MADD_FP6_LOS	509	//	光口6信号丢失状态	
#define	MADD_FP7_LOS	510	//	光口7信号丢失状态	
#define	MADD_FP8_LOS	511	//	光口8信号丢失状态	
#define	MADD_FP9_LOS	512	//	光口9信号丢失状态
#define	MADD_FP10_LOS	513	//	光口10信号丢失状态
#define	MADD_FP11_LOS	514	//	光口11信号丢失状态
#define	MADD_FP12_LOS	515	//	光口12信号丢失状态
#define	MADD_FP13_LOS	516	//	光口13信号丢失状态
#define	MADD_FP14_LOS	517	//	光口14信号丢失状态
#define	MADD_FP15_LOS	518	//	光口15信号丢失状态
#define	MADD_FP16_LOS	519	//	光口16信号丢失状态
#define	MADD_FP1_LOF	520	//	光口1帧丢失状态
#define	MADD_FP2_LOF	521	//	光口2帧丢失状态
#define	MADD_FP3_LOF	522	//	光口3帧丢失状态
#define	MADD_FP4_LOF	523	//	光口4帧丢失状态
#define	MADD_FP5_LOF	524	//	光口5帧丢失状态
#define	MADD_FP6_LOF	525	//	光口6帧丢失状态
#define	MADD_FP7_LOF	526	//	光口7帧丢失状态
#define	MADD_FP8_LOF	527	//	光口8帧丢失状态
#define	MADD_FP9_LOF	528	//	光口9帧丢失状态
#define	MADD_FP10_LOF	529	//	光口10帧丢失状态
#define	MADD_FP11_LOF	530	//	光口11帧丢失状态
#define	MADD_FP12_LOF	531	//	光口12帧丢失状态
#define	MADD_FP13_LOF	532	//	光口13帧丢失状态
#define	MADD_FP14_LOF	533	//	光口14帧丢失状态
#define	MADD_FP15_LOF	534	//	光口15帧丢失状态
#define	MADD_FP16_LOF	535	//	光口16帧丢失状态
#define	MADD_OPT_LOF	536	//	帧丢失状态
#define	MADD_SERDES1_PLL_ST	537	//	SerDes芯片PLL状态1
#define	MADD_SERDES2_PLL_ST	538	//	SerDes芯片PLL状态2
#define	MADD_SERDES3_PLL_ST	539	//	SerDes芯片PLL状态3
#define	MADD_SERDES4_PLL_ST	540	//	SerDes芯片PLL状态4
#define	MADD_SERDES5_PLL_ST	541	//	SerDes芯片PLL状态5
#define	MADD_SERDES6_PLL_ST	542	//	SerDes芯片PLL状态6
#define	MADD_SERDES7_PLL_ST	543	//	SerDes芯片PLL状态7
#define	MADD_SERDES8_PLL_ST	544	//	SerDes芯片PLL状态8
#define	MADD_SERDES9_PLL_ST	545	//	SerDes芯片PLL状态9
#define	MADD_SERDES10_PLL_ST	546	//	SerDes芯片PLL状态10
#define	MADD_SERDES11_PLL_ST	547	//	SerDes芯片PLL状态11
#define	MADD_SERDES12_PLL_ST	548	//	SerDes芯片PLL状态12
#define	MADD_SERDES13_PLL_ST	549	//	SerDes芯片PLL状态13
#define	MADD_SERDES14_PLL_ST	550	//	SerDes芯片PLL状态14
#define	MADD_SERDES15_PLL_ST	551	//	SerDes芯片PLL状态15
#define	MADD_SERDES16_PLL_ST	552	//	SerDes芯片PLL状态16
#define	MADD_TOPO_CHG_ALM	553	//	环路状态告警
#define	MADD_BER_ALARM	554	//	误码率偏高告警
#define	MADD_LOAD_FPGA_ST	555	//	加载FPGA状态
#define	MADD_FPGA_CLK_ST	556	//	FPGA本振状态
#define	MADD_INIT_CLK_ST	557	//	初始化时钟状态
#define	MADD_INIT_AD_ST	558	//	初始化AD状态
#define	MADD_INIT_FB_AD_ST	559	//	初始化反馈AD状态
#define	MADD_CLK_PLL_ST	560	//	CLK	PLL状态		
#define	MADD_CLK_REF_ST	561	//	CLK	参考状态		
#define	MADD_RE_NODE_MODE	562	//	RE节点模式:0-未联网,1-链网末端,2-链网中间,3-环网末端,4-环网中间			
#define	MADD_BOARD_TEMP	563	//	单板温度			
#define	MADD_CLK_VCO_VT	564	//	时钟VCO电压			
#define	MADD_PWR_9V0_VT	565	//	9V电源电压			
#define	MADD_PWR_5V5_VT	566	//	5.5V电源电压			
#define	MADD_PWR_3V6_VT	567	//	3.6V电源电压			
#define	MADD_PWR_1V2_VT	568	//	1.2V电源电压			
#define	MADD_PWR_2V5_VT	569	//	1.2V电源电压			
#define	MADD_PRI_PROTOCAL_V	570	//	协议版本			
#define	MADD_MODULE_HRI_ID	571	//	ID			
#define	MADD_WORK_ERROR	572	//	系统工作状态，1-有故障			
#define	MADD_TRAFFIC_END	573	//	话务量统计结束标志,	国人版本每次统计完成则+1,其他客户统计完成置1		
#define	MADD_DELAY_MODE	574	//		延时模式:	0-手动,	1-自动
#define	MADD_TD_SYNC_ST	575	//	TD同步状态:	0-已同步，1-未同步		
#define	MADD_TD_WORK_MODE	576	//	[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零		
#define	MADD_TD_T0_UD	577	//	TD时隙0上下行标志:0-上行，1-下行			
#define	MADD_TD_T1_UD	578	//	TD时隙1上下行标志:0-上行，1-下行			
#define	MADD_TD_T2_UD	579	//	TD时隙2上下行标志:0-上行，1-下行			
#define	MADD_TD_T3_UD	580	//	TD时隙3上下行标志:0-上行，1-下行			
#define	MADD_TD_T4_UD	581	//	TD时隙4上下行标志:0-上行，1-下行			
#define	MADD_TD_T5_UD	582	//	TD时隙5上下行标志:0-上行，1-下行			
#define	MADD_TD_T6_UD	583	//	TD时隙6上下行标志:0-上行，1-下行			
#define	MADD_POWERUP_ST	584	//		数字板上电状态,每次启动时置一		
#define	MADD_LOW_POWER	585	//	低功耗模式:1-低功耗;	0-正常		
#define	MADD_THR_PORT	586	//		透传端口选择0-485B,	1-RS232	
#define	MADD_THR_BAUD	587	//	透传端口波特率	0-9600,	1-19200,	2-38400,
#define	MADD_CTRL_BAUD	588	//	控制端口波特率	0-9600,	1-19200,	2-38400,
#define	MADD_WLAN_CONN_ST1	589	//	WLAN口状态1:	0-正常，1-异常		
#define	MADD_WLAN_CONN_ST2	590	//	WLAN口状态2:	0-正常，1-异常		
#define	MADD_WLAN_CONN_ST3	591	//	WLAN口状态3:	0-正常，1-异常		
#define	MADD_WLAN_CONN_ST4	592	//	WLAN口状态4:	0-正常，1-异常		
#define	MADD_WLAN_SPEED1	593	//	WLAN口速度1:	0：10M		1：100M
#define	MADD_WLAN_SPEED2	594	//	WLAN口速度1:	0：10M		1：100M
#define	MADD_WLAN_SPEED3	595	//	WLAN口速度1:	0：10M		1：100M
#define	MADD_WLAN_SPEED4	596	//	WLAN口速度1:	0：10M		1：100M
#define	MADD_GSM_BW_SEL	597	//	宽带版本GSM带宽选择:	0-6M,	1-20M,	2-24M,
#define	MADD_HX_DET_UADDR	598	//	虹信DET模块上行地址,	高4位为B段,	低四位为A段	
#define	MADD_HX_LNA_UADDR	599	//	虹信LNA模块上行地址,	高4位为B段,	低四位为A段	
#define	MADD_HX_DET_DADDR	600	//	虹信DET模块下行地址,	高4位为B段,	低四位为A段	
#define	MADD_HX_LNA_DADDR	601	//	虹信LNA模块下行地址,	高4位为B段,	低四位为A段	
#define	MADD_FPS_AUTO_SCAN	602	//	自动频点搜索功能使能:1-自动搜索和设置频点,	0-手动搜索		
#define	MADD_FPS_SWITCH_THD	603	//	自动频点搜索的BCCH功率切换门限			
#define	MADD_FPS_MOSVC_SEL	604	//	频点搜索:	运营商选择:	0-中移动,	1-中联通,
#define	MADD_FPS_RFRANGE_SEL	605	//	频点搜索:	频宽选择(忽略,以模块制式为准):	0-全频段,	1-900MHz,
#define	MADD_FPS_BS_ID	606	//	频点搜索:	基站识别码		
#define	MADD_FPS_CA_COUNT	607	//	频点搜索:	有效信道数		
#define	MADD_FPS_BCCH_LK_ST	608	//	频点搜索:	锁定BCCH状态:	1-锁定,	0-失败
#define	MADD_FPS_MOSVC_LK_ST	609	//	频点搜索:	锁定运营商状态:	1-锁定,	0-失败
#define	MADD_FPS_RFRANGE_LK_ST	610	//	频点搜索:	锁定频带状态:	1-锁定,	0-失败
#define	MADD_FPS_BCCH_POW_M	611	//	频点搜索:	主小区BCCH接收强度		
#define	MADD_FPS_BCCH_POW_1	612	//	频点搜索:	邻小区1BCCH接收强度		
#define	MADD_FPS_BCCH_POW_2	613	//	频点搜索:	邻小区2BCCH接收强度		
#define	MADD_FPS_BCCH_POW_3	614	//	频点搜索:	邻小区3BCCH接收强度		
#define	MADD_FPS_BCCH_POW_4	615	//	频点搜索:	邻小区4BCCH接收强度		
#define	MADD_FPS_BCCH_POW_5	616	//	频点搜索:	邻小区5BCCH接收强度		
#define	MADD_FPS_BCCH_POW_6	617	//	频点搜索:	邻小区6BCCH接收强度		
#define	MADD_A_EXPA_WORK_EN	618	//	[WR]微功放:	射频信号开关		
#define	MADD_A_EXPA_DL_ATT	619	//	[WR]微功放:	下行衰减值		
#define	MADD_A_EXPA_TEMP	620	//	[RO]微功放:	温度		
#define	MADD_A_EXPA_DL_POW	621	//	[RO]微功放:	下行输出功率电平		
#define	MADD_A_EXPA_SWR	622	//	[RO]微功放:	下行驻波比值,x100保留2位小数，最大不超过1.5		
#define	MADD_A_EXPA_POWER_DN	623	//	[RO]微功放:	电源掉电告警(3分钟概率判定)		
#define	MADD_A_EXPA_POWER_ERR	624	//	[RO]微功放:	电源故障告警(3分钟概率判定)	
#define	MADD_A_EXPA_BATT_ERR	625	//	[RO]微功放:	监控模块电池故障告警(3分钟概率判定)	
#define	MADD_A_EXPA_POS_ALM	626	//	[RO]微功放:	位置告警	
#define	MADD_A_EXPA_DOOR_ALM	627	//	[RO]微功放:	门禁告警	
#define	MADD_A_EXPA_WROK_ALM	628	//	[RO]微功放:	下行功放故障告警(3分钟概率判定)	
#define	MADD_A_EXPA_EXT1_ALM	629	//	[RO]微功放:	外部告警1	
#define	MADD_A_EXPA_EXT2_ALM	630	//	[RO]微功放:	外部告警2	
#define	MADD_A_EXPA_EXT3_ALM	631	//	[RO]微功放:	外部告警3	
#define	MADD_A_EXPA_MAX_GAIN	632	//	微功放:	零衰减增益，即最大增益	
#define	MADD_A_EXPA_GAIN_THD	633	//	微功放:	增益门限，即允许工作的增益最大值	
#define	MADD_A_EXPA_POW_THD	634	//	微功放:	功放输出功率门限	
#define	MADD_A_EXPA_POD_CMP	635	//	微功放:	检波管功率检测补偿值,1字节有符号数,最终功率为检波管功率加上补偿值	
#define	MADD_MONITOR_VOL_OVER_THR 		636			 // 监控电压过门限
#define 	MADD_MONITOR_VOL_OWE_THR 		637			 // 监控电压欠门限
#define 	MADD_DIGITAL_SINGNAL_ALARM 		638			 // 数字信号异常告警
#define 	MADD_HOST_DEVICE_LINK_SINGNAL_ALARM 		639			 // 主从监控链路告警
#define 	MADD_MONITOR_BATTERY_ALARM 		640			 // 监控模块电池故障告警	
#define 	MADD_LOW_POWER_ALARM 		641			 // 电源掉电告警	
#define 	MADD_BATTERY_BREAKDOWN_ALARM 		642			 // 电源故障告警	
#define 	MADD_POSITION_MOVE_ALARM		643			 // 位置告警	
#define 	MADD_A_INPUT_OVER_DPOW_THR_ALARM 		644			 // A下行输入过功率告警	
#define 	MADD_A_INPUT_OWE_DPOW_THR_ALARM 		645			 // A下行输入欠功率告警	
#define 	MADD_B_INPUT_OVER_DPOW_THR_ALARM 		646	// A下行输入过功率告警			
#define 	MADD_B_INPUT_OWE_DPOW_THR_ALARM 		647	// A下行输入欠功率告警			
#define 	MADD_C_INPUT_OVER_DPOW_THR_ALARM 		648	//248			 // A下行输入过功率告警
#define 	MADD_C_INPUT_OWE_DPOW_THR_ALARM 		649	//249			 // A下行输入欠功率告警
#define 	MADD_D_INPUT_OVER_DPOW_THR_ALARM		650	//248			 // A下行输入过功率告警
#define 	MADD_D_INPUT_OWE_DPOW_THR_ALARM		651	//339	//249		
#define 	MADD_TD_D_OVER_SLOT1_THR_ALARM 		652			 // TD下行输入导频过功率告警	
#define 	MADD_TD_D_OWE_SLOT1_THR_ALARM 		653			 // TD下行输入导频欠功率告警	
#define	MADD_RE_DATA_LAN_ST1	654	//	PHY芯片工作状态		0:00	正常，1:
#define	MADD_RE_CASCADE_LAN_ST1	655	//	级联网口的工作状态		0:00	正常，1:
#define	MADD_RE_DATA_LAN_SYS_ST1	656	//	数据网口同步状态		0:00	同步，1:
#define	MADD_RE_CASCADE_LAN_SYS_ST1	657	//	级联网口同步状态		0:00	同步，1:
#define	MADD_A_RF_POW_SWR	658	//	A段覆盖单元功放驻波比			
#define	MADD_A_RF_OUT_POW_H_THR 	659	//	A段覆盖单元输出过功率门限			
#define	MADD_A_RF_OUT_POW_L_THR 	660	//	A段覆盖单元输出欠功率门限			
#define	MADD_B_RF_POW_SWR	661	 //	B段覆盖单元功放驻波比			
#define	MADD_B_RF_OUT_POW_H_THR 	662	 //	B段覆盖单元输出过功率门限			
#define	MADD_B_RF_OUT_POW_L_THR 	663	 //	B段覆盖单元输出欠功率门限			
#define	MADD_C_RF_POW_SWR	664	//	A段覆盖单元功放驻波比			
#define	MADD_C_RF_OUT_POW_H_THR 	665	//	A段覆盖单元输出过功率门限			
#define	MADD_C_RF_OUT_POW_L_THR 	666	//	A段覆盖单元输出欠功率门限			
#define	MADD_D_RF_POW_SWR	667	 // 	D段覆盖单元功放驻波比			
#define	MADD_D_RF_OUT_POW_H_THR 	668	 // 	D段覆盖单元输出过功率门限			
#define	MADD_D_RF_OUT_POW_L_THR 	669	 // 	D段覆盖单元输出欠功率门限			
#define	MADD_PWR_3V3_1_VT	670		//	3.3V电源电压		
#define	MADD_PWR_3V3_2_VT	671		//	3.3V电源电压		
#define	MADD_PWR_1V8_VT	672			//	1.8V电源电压	
#define	MADD_PWR_1V5_VT	673				//	1.5V电源电压
#define	MADD_A_DL_RF_EN 	674	// 	A段下行射频使能	
#define	MADD_A_UL_RF_EN 	675	// 	A段上行射频使能	
#define	MADD_B_DL_RF_EN 	676	// 	B段下行射频使能	
#define	MADD_B_UL_RF_EN 	677	// 	B段上行射频使能	
#define	MADD_C_DL_RF_EN 	678	// 	C段下行射频使能	
#define	MADD_C_UL_RF_EN 	679	// 	C段上行射频使能	
#define	MADD_D_DL_RF_EN 	680	// 	D段下行射频使能	
#define	MADD_D_UL_RF_EN 	681	// 	D段上行射频使能
#define	MADD_METER_OFFSET	682				//	仪器偏差值设置
#define	MADD_METER_OFFSET_B	683				//	仪器偏差值设置
#define	MADD_METER_OFFSET_C	684				//	仪器偏差值设置
#define	MADD_METER_OFFSET_D	685				//	仪器偏差值设置
#define	MADD_C_TD_TYPE_SELECT	686	// TD_TLE时隙配比				
#define	MADD_C_TD_NORMAL_CP	687		//	TDD特殊时隙 NORMAL_CP		
#define	MADD_C_TD_EXTENDED_CP	688		//	TDD特殊时隙 NORMAL_CP		
#define	MADD_C_TD_SYNC_ST	689	//	TD同步状态:	0-已同步，1-未同步		
#define	MADD_C_TD_WORK_MODE	690	//	[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零		
#define	MADD_C_TD_DL_OVER_SLOT1_THR_ALARM	691	// TD下行输入导频过功率告警				
#define	MADD_C_TD_DL_OWE_SLOT1_THR_ALARM	692	 // TD下行输入导频欠功率告警				
#define	MADD_D_TD_TYPE_SELECT	693	// TD_TLE时隙配比				
#define	MADD_D_TD_NORMAL_CP	694	//718	//	TDD特殊时隙 NORMAL_CP		
#define	MADD_D_TD_EXTENDED_CP	695	//719	//	TDD特殊时隙 NORMAL_CP		
#define	MADD_D_TD_SYNC_ST	696	//	TD同步状态:	0-已同步，1-未同步		
#define	MADD_D_TD_WORK_MODE	697	//	[WR]TD:TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开,	每次上电后清零		
#define	MADD_D_TD_DL_OVER_SLOT1_THR_ALARM	698	// TD下行输入导频过功率告警				
#define	MADD_D_TD_DL_OWE_SLOT1_THR_ALARM	699	 // TD下行输入导频欠功率告警				
#define	MADD_C_TD_T0_UD	700		//	TD时隙0上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T1_UD	701		//	TD时隙1上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T2_UD	702		//	TD时隙2上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T3_UD	703		//	TD时隙3上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T4_UD	704		//	TD时隙4上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T5_UD	705		//	TD时隙5上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T6_UD	706		//	TD时隙6上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T7_UD	707		//	TD时隙7上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T8_UD	708		//	TD时隙8上下行标志:0-上行，1-下行		
#define	MADD_C_TD_T9_UD	709		//	TD时隙9上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T0_UD	710		//	TD时隙0上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T1_UD	711		//	TD时隙1上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T2_UD	712		//	TD时隙2上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T3_UD	713		//	TD时隙3上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T4_UD	714		//	TD时隙4上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T5_UD	715		//	TD时隙5上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T6_UD	716		//	TD时隙6上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T7_UD	717		//	TD时隙7上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T8_UD	718		//	TD时隙8上下行标志:0-上行，1-下行		
#define	MADD_D_TD_T9_UD	719		//	TD时隙9上下行标志:0-上行，1-下行		
#define	MADD_NOISE_TEST_EN	720		//	噪声测试开关		
#define	MADD_FREQ_MODIF_VAL_D	721		//	本振修正
#define	MADD_FREQ_MODIF_VAL_B	722		//	本振修正
#define	MADD_FREQ_MODIF_VAL_A	723		//	本振修正
#define	MADD_B_TDS_2TH_BREAKING_POINT_SET	724		//	TDS 第二转换点设置取值[1，5]
#define	MADD_DELAY_MODE_A				725	// 	延时模式: 0-手动, 1-自动
#define	MADD_DELAY_MODE_B				726	// 	延时模式: 0-手动, 1-自动
#define	MADD_DELAY_MODE_C				727	// 	延时模式: 0-手动, 1-自动
#define	MADD_DELAY_MODE_D				728	// 	延时模式: 0-手动, 1-自动
#define	MADD_REE_CIRCUIT_ALARM	 		729
#define	MADD_REE_WLAN_CONN_ST			730
#define	MADD_DL_POWER_MAX				731//求下行模块功率最大值	
#define 	MADD_SLOT_TIME_EN_B				732	// 时隙配比自动检测开关		
#define 	MADD_SLOT_TIME_DISTRI_B			733	// 时隙配比分布			
#define 	MADD_VERSION_FLAG				734	// 版本标识识别
#define 	MADD_SLOT_TIME_EN_C				735	// 时隙配比自动检测开关		
#define 	MADD_SLOT_TIME_DISTRI_C			736	// TD-LTE时隙配比状态 D3-0:特殊子帧配比 TDL_SP_SubFrm_CFG_check  等于15时表示检测失败	D7-4:上下行时隙配比 TDL_TS_EN_check  等于15时表示检测失败			
#define 	MADD_A_1197_LOCK_ST 	737	// 	A段1197锁定状态,
#define 	MADD_A_IF_ST 	738	// 	A段中频频率,0/1---300M/500M
#define 	MADD_ENCRYPTION_ST 	739	// 	加密状态,0/1---不加密/加密
#define	MADD_PWR_1V6_VT			740				//	1.6V电源电压
#define	MADD_A_90_VALUE			741				//A段9363 90寄存器的值
#define	MADD_A_91_VALUE			742				//A段9363 91寄存器的值
#define	MADD_A_94_VALUE			743				//A段9363 94寄存器的值
#define	MADD_A_95_VALUE			744				//A段9363 95寄存器的值
#define	MADD_B_90_VALUE			745				//B段9363 90寄存器的值
#define	MADD_B_91_VALUE			746				//B段9363 91寄存器的值
#define	MADD_B_94_VALUE			747				//B段9363 94寄存器的值
#define	MADD_B_95_VALUE			748				//B段9363 95寄存器的值
#define	MADD_C_90_VALUE			749				//C段9363 90寄存器的值
#define	MADD_C_91_VALUE			750				//C段9363 91寄存器的值
#define	MADD_C_94_VALUE			751				//C段9363 94寄存器的值
#define	MADD_C_95_VALUE			752				//C段9363 95寄存器的值
#define	MADD_D_90_VALUE			753				//D段9363 90寄存器的值
#define	MADD_D_91_VALUE			754				//D段9363 91寄存器的值
#define	MADD_D_94_VALUE			755				//D段9363 94寄存器的值
#define	MADD_D_95_VALUE			756				//D段9363 95寄存器的值
#define	MADD_PASSTHROUGH_EN		757				//透传使能
#define	MADD_A_DL_POW_ADJ		758				//功率调节             
#define	MADD_B_DL_POW_ADJ		759				//功率调节             
#define	MADD_C_DL_POW_ADJ		760				//功率调节             
#define	MADD_D_DL_POW_ADJ		761				//功率调节             
#define	MADD_SoftwareLoadTimes	762				//软件重启次数，每次上电加一
#define	MADD_A_LNA_EN_ST 		763	           		 // 	A段下行低噪放LNA开关

#define SYS_PARAM_1B_COUNT		764


#if defined ( CLIENT_JIZHUN)
	// 国人参数
	// 参数地址定义==================================================== 2b
#define	PARA_A_DL_CHANNEL1	0x0900	//	A段下行信道号1
#define	PARA_A_DL_CHANNEL2	0x0901	//	A段下行信道号2
#define	PARA_A_DL_CHANNEL3	0x0902	//	A段下行信道号3
#define	PARA_A_DL_CHANNEL4	0x0903	//	A段下行信道号4
#define	PARA_A_DL_CHANNEL5	0x0904	//	A段下行信道号5
#define	PARA_A_DL_CHANNEL6	0x0905	//	A段下行信道号6
#define	PARA_A_DL_CHANNEL7	0x0906	//	A段下行信道号7
#define	PARA_A_DL_CHANNEL8	0x0907	//	A段下行信道号8
#define	PARA_A_DL_CHANNEL9	0x0908	//	A段下行信道号9
#define	PARA_A_DL_CHANNEL10	0x0909	//	A段下行信道号10
#define	PARA_A_DL_CHANNEL11	0x090A	//	A段下行信道号11
#define	PARA_A_DL_CHANNEL12	0x090B	//	A段下行信道号12
#define	PARA_A_DL_CHANNEL13	0x090C	//	A段下行信道号13
#define	PARA_A_DL_CHANNEL14	0x090D	//	A段下行信道号14
#define	PARA_A_DL_CHANNEL15	0x090E	//	A段下行信道号15
#define	PARA_A_DL_CHANNEL16	0x090F	//	A段下行信道号16
#define	PARA_A_UL_CHANNEL1	0x0900	//	A段上行信道号1
#define	PARA_A_UL_CHANNEL2	0x0901	//	A段上行信道号2
#define	PARA_A_UL_CHANNEL3	0x0902	//	A段上行信道号3
#define	PARA_A_UL_CHANNEL4	0x0903	//	A段上行信道号4
#define	PARA_A_UL_CHANNEL5	0x0904	//	A段上行信道号5
#define	PARA_A_UL_CHANNEL6	0x0905	//	A段上行信道号6
#define	PARA_A_UL_CHANNEL7	0x0906	//	A段上行信道号7
#define	PARA_A_UL_CHANNEL8	0x0907	//	A段上行信道号8
#define	PARA_A_UL_CHANNEL9	0x0908	//	A段上行信道号9
#define	PARA_A_UL_CHANNEL10	0x0909	//	A段上行信道号10
#define	PARA_A_UL_CHANNEL11	0x090A	//	A段上行信道号11
#define	PARA_A_UL_CHANNEL12	0x090B	//	A段上行信道号12
#define	PARA_A_UL_CHANNEL13	0x090C	//	A段上行信道号13
#define	PARA_A_UL_CHANNEL14	0x090D	//	A段上行信道号14
#define	PARA_A_UL_CHANNEL15	0x090E	//	A段上行信道号15
#define	PARA_A_UL_CHANNEL16	0x090F	//	A段上行信道号16
#define	PARA_A_DCH_MAX_POW1	0x0348	//	A段下行通道最大输出功率1
#define	PARA_A_DCH_MAX_POW2	0	//	A段下行通道最大输出功率2
#define	PARA_A_DCH_MAX_POW3	0	//	A段下行通道最大输出功率3
#define	PARA_A_DCH_MAX_POW4	0	//	A段下行通道最大输出功率4
#define	PARA_A_DCH_MAX_POW5	0	//	A段下行通道最大输出功率5
#define	PARA_A_DCH_MAX_POW6	0	//	A段下行通道最大输出功率6
#define	PARA_A_DCH_MAX_POW7	0	//	A段下行通道最大输出功率7
#define	PARA_A_DCH_MAX_POW8	0	//	A段下行通道最大输出功率8
#define	PARA_A_DCH_MAX_POW9	0	//	A段下行通道最大输出功率9
#define	PARA_A_DCH_MAX_POW10	0	//	A段下行通道最大输出功率10
#define	PARA_A_DCH_MAX_POW11	0	//	A段下行通道最大输出功率11
#define	PARA_A_DCH_MAX_POW12	0	//	A段下行通道最大输出功率12
#define	PARA_A_DCH_MAX_POW13	0	//	A段下行通道最大输出功率13
#define	PARA_A_DCH_MAX_POW14	0	//	A段下行通道最大输出功率14
#define	PARA_A_DCH_MAX_POW15	0	//	A段下行通道最大输出功率15
#define	PARA_A_DCH_MAX_POW16	0	//	A段下行通道最大输出功率16
#define	PARA_A_UCH_MAX_POW1		0x0340	//	A段上行通道最大输入功率1
#define	PARA_A_UCH_MAX_POW2		0x8269	//	A段上行通道最大输入功率2
#define	PARA_A_UCH_MAX_POW3	0	//	A段上行通道最大输入功率3
#define	PARA_A_UCH_MAX_POW4	0	//	A段上行通道最大输入功率4
#define	PARA_A_UCH_MAX_POW5	0	//	A段上行通道最大输入功率5
#define	PARA_A_UCH_MAX_POW6	0	//	A段上行通道最大输入功率6
#define	PARA_A_UCH_MAX_POW7	0	//	A段上行通道最大输入功率7
#define	PARA_A_UCH_MAX_POW8	0	//	A段上行通道最大输入功率8
#define	PARA_A_UCH_MAX_POW9	0	//	A段上行通道最大输入功率9
#define	PARA_A_UCH_MAX_POW10	0	//	A段上行通道最大输入功率10
#define	PARA_A_UCH_MAX_POW11	0	//	A段上行通道最大输入功率11
#define	PARA_A_UCH_MAX_POW12	0	//	A段上行通道最大输入功率12
#define	PARA_A_UCH_MAX_POW13	0	//	A段上行通道最大输入功率13
#define	PARA_A_UCH_MAX_POW14	0	//	A段上行通道最大输入功率14
#define	PARA_A_UCH_MAX_POW15	0	//	A段上行通道最大输入功率15
#define	PARA_A_UCH_MAX_POW16	0	//	A段上行通道最大输入功率16
#define	PARA_A_DCH_POW1	0	//	A段选频通道下行功率1
#define	PARA_A_DCH_POW2	0	//	A段选频通道下行功率2
#define	PARA_A_DCH_POW3	0	//	A段选频通道下行功率3
#define	PARA_A_DCH_POW4	0	//	A段选频通道下行功率4
#define	PARA_A_DCH_POW5	0	//	A段选频通道下行功率5
#define	PARA_A_DCH_POW6	0	//	A段选频通道下行功率6
#define	PARA_A_DCH_POW7	0	//	A段选频通道下行功率7
#define	PARA_A_DCH_POW8	0	//	A段选频通道下行功率8
#define	PARA_A_DCH_POW9	0	//	A段选频通道下行功率9
#define	PARA_A_DCH_POW10	0	//	A段选频通道下行功率10
#define	PARA_A_DCH_POW11	0	//	A段选频通道下行功率11
#define	PARA_A_DCH_POW12	0	//	A段选频通道下行功率12
#define	PARA_A_DCH_POW13	0	//	A段选频通道下行功率13
#define	PARA_A_DCH_POW14	0	//	A段选频通道下行功率14
#define	PARA_A_DCH_POW15	0	//	A段选频通道下行功率15
#define	PARA_A_DCH_POW16	0	//	A段选频通道下行功率16
#define	PARA_A_UCH_POW1	0	//	A段选频通道上行功率1
#define	PARA_A_UCH_POW2	0	//	A段选频通道上行功率2
#define	PARA_A_UCH_POW3	0	//	A段选频通道上行功率3
#define	PARA_A_UCH_POW4	0	//	A段选频通道上行功率4
#define	PARA_A_UCH_POW5	0	//	A段选频通道上行功率5
#define	PARA_A_UCH_POW6	0	//	A段选频通道上行功率6
#define	PARA_A_UCH_POW7	0	//	A段选频通道上行功率7
#define	PARA_A_UCH_POW8	0	//	A段选频通道上行功率8
#define	PARA_A_UCH_POW9	0	//	A段选频通道上行功率9
#define	PARA_A_UCH_POW10	0	//	A段选频通道上行功率10
#define	PARA_A_UCH_POW11	0	//	A段选频通道上行功率11
#define	PARA_A_UCH_POW12	0	//	A段选频通道上行功率12
#define	PARA_A_UCH_POW13	0	//	A段选频通道上行功率13
#define	PARA_A_UCH_POW14	0	//	A段选频通道上行功率14
#define	PARA_A_UCH_POW15	0	//	A段选频通道上行功率15
#define	PARA_A_UCH_POW16	0	//	A段选频通道上行功率16
#define	PARA_A_UDPX_IN_GAIN		0x08AB	//	A段下行输入双工器增益
#define	PARA_A_UDPX_OUT_GAIN	0x08AA	//	A段上行输出双工器增益
#define	PARA_A_DL_TOTAL_POW	0x8390	//	A段下行输入总功率
#define	PARA_A_UL_TOTAL_POW	0x831e	//	A段上行输出总功率
#define	PARA_A_REC_DPX_IG		0		//		REC的A段输入双工器增益，用来进行增益计算，只读							
#define	PARA_A_REC_DPX_OG		0		//		REC的A段输出双工器增益，用来进行增益计算，只读	
#define	PARA_B_DL_CHANNEL1	0x0900	//	B段下行信道号1
#define	PARA_B_DL_CHANNEL2	0x0901	//	B段下行信道号2
#define	PARA_B_DL_CHANNEL3	0x0902	//	B段下行信道号3
#define	PARA_B_DL_CHANNEL4	0x0903	//	B段下行信道号4
#define	PARA_B_DL_CHANNEL5	0x0904	//	B段下行信道号5
#define	PARA_B_DL_CHANNEL6	0x0905	//	B段下行信道号6
#define	PARA_B_DL_CHANNEL7	0x0906	//	B段下行信道号7
#define	PARA_B_DL_CHANNEL8	0x0907	//	B段下行信道号8
#define	PARA_B_DL_CHANNEL9	0x0908	//	B段下行信道号9
#define	PARA_B_DL_CHANNEL10	0x0909	//	B段下行信道号10
#define	PARA_B_DL_CHANNEL11	0x090A	//	B段下行信道号11
#define	PARA_B_DL_CHANNEL12	0x090B	//	B段下行信道号12
#define	PARA_B_DL_CHANNEL13	0x090C	//	B段下行信道号13
#define	PARA_B_DL_CHANNEL14	0x090D	//	B段下行信道号14
#define	PARA_B_DL_CHANNEL15	0x090E	//	B段下行信道号15
#define	PARA_B_DL_CHANNEL16	0x090F	//	B段下行信道号16
#define	PARA_B_UL_CHANNEL1	0x0900	//	B段上行信道号1
#define	PARA_B_UL_CHANNEL2	0x0901	//	B段上行信道号2
#define	PARA_B_UL_CHANNEL3	0x0902	//	B段上行信道号3
#define	PARA_B_UL_CHANNEL4	0x0903	//	B段上行信道号4
#define	PARA_B_UL_CHANNEL5	0x0904	//	B段上行信道号5
#define	PARA_B_UL_CHANNEL6	0x0905	//	B段上行信道号6
#define	PARA_B_UL_CHANNEL7	0x0906	//	B段上行信道号7
#define	PARA_B_UL_CHANNEL8	0x0907	//	B段上行信道号8
#define	PARA_B_UL_CHANNEL9	0x0908	//	B段上行信道号9
#define	PARA_B_UL_CHANNEL10	0x0909	//	B段上行信道号10
#define	PARA_B_UL_CHANNEL11	0x090A	//	B段上行信道号11
#define	PARA_B_UL_CHANNEL12	0x090B	//	B段上行信道号12
#define	PARA_B_UL_CHANNEL13	0x090C	//	B段上行信道号13
#define	PARA_B_UL_CHANNEL14	0x090D	//	B段上行信道号14
#define	PARA_B_UL_CHANNEL15	0x090E	//	B段上行信道号15
#define	PARA_B_UL_CHANNEL16	0x090F	//	B段上行信道号16
#define	PARA_B_DCH_MAX_POW1	0x0348	//	B段下行通道最大输出功率1
#define	PARA_B_DCH_MAX_POW2	0	//	B段下行通道最大输出功率2
#define	PARA_B_DCH_MAX_POW3	0	//	B段下行通道最大输出功率3
#define	PARA_B_DCH_MAX_POW4	0	//	B段下行通道最大输出功率4
#define	PARA_B_DCH_MAX_POW5	0	//	B段下行通道最大输出功率5
#define	PARA_B_DCH_MAX_POW6	0	//	B段下行通道最大输出功率6
#define	PARA_B_DCH_MAX_POW7	0	//	B段下行通道最大输出功率7
#define	PARA_B_DCH_MAX_POW8	0	//	B段下行通道最大输出功率8
#define	PARA_B_DCH_MAX_POW9	0	//	B段下行通道最大输出功率9
#define	PARA_B_DCH_MAX_POW10	0	//	B段下行通道最大输出功率10
#define	PARA_B_DCH_MAX_POW11	0	//	B段下行通道最大输出功率11
#define	PARA_B_DCH_MAX_POW12	0	//	B段下行通道最大输出功率12
#define	PARA_B_DCH_MAX_POW13	0	//	B段下行通道最大输出功率13
#define	PARA_B_DCH_MAX_POW14	0	//	B段下行通道最大输出功率14
#define	PARA_B_DCH_MAX_POW15	0	//	B段下行通道最大输出功率15
#define	PARA_B_DCH_MAX_POW16	0	//	B段下行通道最大输出功率16
#define	PARA_B_UCH_MAX_POW1		0x0340	//	B段上行通道最大输入功率1
#define	PARA_B_UCH_MAX_POW2		0x8269//	B段上行通道最大输入功率2
#define	PARA_B_UCH_MAX_POW3	0	//	B段上行通道最大输入功率3
#define	PARA_B_UCH_MAX_POW4	0	//	B段上行通道最大输入功率4
#define	PARA_B_UCH_MAX_POW5	0	//	B段上行通道最大输入功率5
#define	PARA_B_UCH_MAX_POW6	0	//	B段上行通道最大输入功率6
#define	PARA_B_UCH_MAX_POW7	0	//	B段上行通道最大输入功率7
#define	PARA_B_UCH_MAX_POW8	0	//	B段上行通道最大输入功率8
#define	PARA_B_UCH_MAX_POW9	0	//	B段上行通道最大输入功率9
#define	PARA_B_UCH_MAX_POW10	0	//	B段上行通道最大输入功率10
#define	PARA_B_UCH_MAX_POW11	0	//	B段上行通道最大输入功率11
#define	PARA_B_UCH_MAX_POW12	0	//	B段上行通道最大输入功率12
#define	PARA_B_UCH_MAX_POW13	0	//	B段上行通道最大输入功率13
#define	PARA_B_UCH_MAX_POW14	0	//	B段上行通道最大输入功率14
#define	PARA_B_UCH_MAX_POW15	0	//	B段上行通道最大输入功率15
#define	PARA_B_UCH_MAX_POW16	0	//	B段上行通道最大输入功率16
#define	PARA_B_DCH_POW1	0	//	B段选频通道下行功率1
#define	PARA_B_DCH_POW2	0	//	B段选频通道下行功率2
#define	PARA_B_DCH_POW3	0	//	B段选频通道下行功率3
#define	PARA_B_DCH_POW4	0	//	B段选频通道下行功率4
#define	PARA_B_DCH_POW5	0	//	B段选频通道下行功率5
#define	PARA_B_DCH_POW6	0	//	B段选频通道下行功率6
#define	PARA_B_DCH_POW7	0	//	B段选频通道下行功率7
#define	PARA_B_DCH_POW8	0	//	B段选频通道下行功率8
#define	PARA_B_DCH_POW9	0	//	B段选频通道下行功率9
#define	PARA_B_DCH_POW10	0	//	B段选频通道下行功率10
#define	PARA_B_DCH_POW11	0	//	B段选频通道下行功率11
#define	PARA_B_DCH_POW12	0	//	B段选频通道下行功率12
#define	PARA_B_DCH_POW13	0	//	B段选频通道下行功率13
#define	PARA_B_DCH_POW14	0	//	B段选频通道下行功率14
#define	PARA_B_DCH_POW15	0	//	B段选频通道下行功率15
#define	PARA_B_DCH_POW16	0	//	B段选频通道下行功率16
#define	PARA_B_UCH_POW1	0	//	B段选频通道上行功率1
#define	PARA_B_UCH_POW2	0	//	B段选频通道上行功率2
#define	PARA_B_UCH_POW3	0	//	B段选频通道上行功率3
#define	PARA_B_UCH_POW4	0	//	B段选频通道上行功率4
#define	PARA_B_UCH_POW5	0	//	B段选频通道上行功率5
#define	PARA_B_UCH_POW6	0	//	B段选频通道上行功率6
#define	PARA_B_UCH_POW7	0	//	B段选频通道上行功率7
#define	PARA_B_UCH_POW8	0	//	B段选频通道上行功率8
#define	PARA_B_UCH_POW9	0	//	B段选频通道上行功率9
#define	PARA_B_UCH_POW10	0	//	B段选频通道上行功率10
#define	PARA_B_UCH_POW11	0	//	B段选频通道上行功率11
#define	PARA_B_UCH_POW12	0	//	B段选频通道上行功率12
#define	PARA_B_UCH_POW13	0	//	B段选频通道上行功率13
#define	PARA_B_UCH_POW14	0	//	B段选频通道上行功率14
#define	PARA_B_UCH_POW15	0	//	B段选频通道上行功率15
#define	PARA_B_UCH_POW16	0	//	B段选频通道上行功率16
#define	PARA_B_UDPX_IN_GAIN	0x08AB	//	B段下行输入双工器增益
#define	PARA_B_UDPX_OUT_GAIN	0x08AA	//	B段上行输出双工器增益
#define	PARA_B_DL_TOTAL_POW	0x8390	//	B段下行输入总功率
#define	PARA_B_UL_TOTAL_POW	0x831e	//	B段上行输出总功率
#define	PARA_B_REC_DPX_IG		0		//		REC的A段输入双工器增益，用来进行增益计算，只读							
#define	PARA_B_REC_DPX_OG		0		//		REC的A段输出双工器增益，用来进行增益计算，只读	
#define	PARA_C_DL_CHANNEL1	0x0900	//	C段下行信道号1
#define	PARA_C_DL_CHANNEL2	0x0901	//	C段下行信道号2
#define	PARA_C_DL_CHANNEL3	0x0902	//	C段下行信道号3
#define	PARA_C_DL_CHANNEL4	0x0903	//	C段下行信道号4
#define	PARA_C_DL_CHANNEL5	0x0904	//	C段下行信道号5
#define	PARA_C_DL_CHANNEL6	0x0905	//	C段下行信道号6
#define	PARA_C_DL_CHANNEL7	0x0906	//	C段下行信道号7
#define	PARA_C_DL_CHANNEL8	0x0907	//	C段下行信道号8
#define	PARA_C_DL_CHANNEL9	0x0908	//	C段下行信道号9
#define	PARA_C_DL_CHANNEL10	0x0909	//	C段下行信道号10
#define	PARA_C_UL_CHANNEL1	0x0900	//	C段上行信道号1
#define	PARA_C_UL_CHANNEL2	0x0901	//	C段上行信道号2
#define	PARA_C_UL_CHANNEL3	0x0902	//	C段上行信道号3
#define	PARA_C_UL_CHANNEL4	0x0903	//	C段上行信道号4
#define	PARA_C_UL_CHANNEL5	0x0904	//	C段上行信道号5
#define	PARA_C_UL_CHANNEL6	0x0905	//	C段上行信道号6
#define	PARA_C_UL_CHANNEL7	0x0906	//	C段上行信道号7
#define	PARA_C_UL_CHANNEL8	0x0907	//	C段上行信道号8
#define	PARA_C_UL_CHANNEL9	0x0908	//	C段上行信道号9
#define	PARA_C_UL_CHANNEL10	0x0909	//	C段上行信道号10
#define	PARA_C_DCH_MAX_POW1	0x0348	//	C段下行通道最大输出功率1
#define	PARA_C_DCH_MAX_POW2	0	//	C段下行通道最大输出功率2
#define	PARA_C_DCH_MAX_POW3	0	//	C段下行通道最大输出功率3
#define	PARA_C_DCH_MAX_POW4	0	//	C段下行通道最大输出功率4
#define	PARA_C_DCH_MAX_POW5	0	//	C段下行通道最大输出功率5
#define	PARA_C_DCH_MAX_POW6	0	//	C段下行通道最大输出功率6
#define	PARA_C_DCH_MAX_POW7	0	//	C段下行通道最大输出功率7
#define	PARA_C_DCH_MAX_POW8	0	//	C段下行通道最大输出功率8
#define	PARA_C_DCH_MAX_POW9	0	//	C段下行通道最大输出功率9
#define	PARA_C_DCH_MAX_POW10	0	//	C段下行通道最大输出功率10
#define	PARA_C_DCH_MAX_POW11	0	//	C段下行通道最大输出功率11
#define	PARA_C_DCH_MAX_POW12	0	//	C段下行通道最大输出功率12
#define	PARA_C_DCH_MAX_POW13	0	//	C段下行通道最大输出功率13
#define	PARA_C_DCH_MAX_POW14	0	//	C段下行通道最大输出功率14
#define	PARA_C_DCH_MAX_POW15	0	//	C段下行通道最大输出功率15
#define	PARA_C_DCH_MAX_POW16	0	//	C段下行通道最大输出功率16
#define	PARA_C_UCH_MAX_POW1	0x0340	//	C段上行通道最大输入功率1
#define	PARA_C_UCH_MAX_POW2	0	//	C段上行通道最大输入功率2
#define	PARA_C_UCH_MAX_POW3	0	//	C段上行通道最大输入功率3
#define	PARA_C_UCH_MAX_POW4	0	//	C段上行通道最大输入功率4
#define	PARA_C_UCH_MAX_POW5	0	//	C段上行通道最大输入功率5
#define	PARA_C_UCH_MAX_POW6	0	//	C段上行通道最大输入功率6
#define	PARA_C_UCH_MAX_POW7	0	//	C段上行通道最大输入功率7
#define	PARA_C_UCH_MAX_POW8	0	//	C段上行通道最大输入功率8
#define	PARA_C_UCH_MAX_POW9	0	//	C段上行通道最大输入功率9
#define	PARA_C_UCH_MAX_POW10		0	//	C段上行通道最大输入功率10
#define	PARA_C_UCH_MAX_POW11		0	//	C段上行通道最大输入功率11
#define	PARA_C_UCH_MAX_POW12		0	//	C段上行通道最大输入功率12
#define	PARA_C_UCH_MAX_POW13		0	//	C段上行通道最大输入功率13
#define	PARA_C_UCH_MAX_POW14		0	//	C段上行通道最大输入功率14
#define	PARA_C_UCH_MAX_POW15		0	//	C段上行通道最大输入功率15
#define	PARA_C_UCH_MAX_POW16		0	//	C段上行通道最大输入功率16
#define	PARA_C_DCH_POW1	0	//	C段选频通道下行功率1
#define	PARA_C_DCH_POW2	0	//	C段选频通道下行功率2
#define	PARA_C_DCH_POW3	0	//	C段选频通道下行功率3
#define	PARA_C_DCH_POW4	0	//	C段选频通道下行功率4
#define	PARA_C_DCH_POW5	0	//	C段选频通道下行功率5
#define	PARA_C_DCH_POW6	0	//	C段选频通道下行功率6
#define	PARA_C_DCH_POW7	0	//	C段选频通道下行功率7
#define	PARA_C_DCH_POW8	0	//	C段选频通道下行功率8
#define	PARA_C_DCH_POW9	0	//	C段选频通道下行功率9
#define	PARA_C_DCH_POW10	0	//	C段选频通道下行功率10
#define	PARA_C_DCH_POW11	0	//	C段选频通道下行功率11
#define	PARA_C_DCH_POW12	0	//	C段选频通道下行功率12
#define	PARA_C_DCH_POW13	0	//	C段选频通道下行功率13
#define	PARA_C_DCH_POW14	0	//	C段选频通道下行功率14
#define	PARA_C_DCH_POW15	0	//	C段选频通道下行功率15
#define	PARA_C_DCH_POW16	0	//	C段选频通道下行功率16
#define	PARA_C_UCH_POW1	0	//	C段选频通道上行功率1
#define	PARA_C_UCH_POW2	0	//	C段选频通道上行功率2
#define	PARA_C_UCH_POW3	0	//	C段选频通道上行功率3
#define	PARA_C_UCH_POW4	0	//	C段选频通道上行功率4
#define	PARA_C_UCH_POW5	0	//	C段选频通道上行功率5
#define	PARA_C_UCH_POW6	0	//	C段选频通道上行功率6
#define	PARA_C_UCH_POW7	0	//	C段选频通道上行功率7
#define	PARA_C_UCH_POW8	0	//	C段选频通道上行功率8
#define	PARA_C_UCH_POW9	0	//	C段选频通道上行功率9
#define	PARA_C_UCH_POW10	0	//	C段选频通道上行功率10
#define	PARA_C_UCH_POW11	0	//	C段选频通道上行功率11
#define	PARA_C_UCH_POW12	0	//	C段选频通道上行功率12
#define	PARA_C_UCH_POW13	0	//	C段选频通道上行功率13
#define	PARA_C_UCH_POW14	0	//	C段选频通道上行功率14
#define	PARA_C_UCH_POW15	0	//	C段选频通道上行功率15
#define	PARA_C_UCH_POW16	0	//	C段选频通道上行功率16
#define	PARA_C_UDPX_IN_GAIN	0x08AB	//	C段下行输入双工器增益
#define	PARA_C_UDPX_OUT_GAIN	0x08AA	//	C段上行输出双工器增益
#define	PARA_C_DL_TOTAL_POW	0x8390	//	C段下行输入总功率
#define	PARA_C_UL_TOTAL_POW	0x831e	//	C段上行输出总功率
#define	PARA_C_REC_DPX_IG		0		//		REC的A段输入双工器增益，用来进行增益计算，只读							
#define	PARA_C_REC_DPX_OG		0		//		REC的A段输出双工器增益，用来进行增益计算，只读	
#define	PARA_D_DL_CHANNEL1	0x0900	//	D段下行信道号1
#define	PARA_D_DL_CHANNEL2	0x0901	//	D段下行信道号2
#define	PARA_D_DL_CHANNEL3	0x0902	//	D段下行信道号3
#define	PARA_D_DL_CHANNEL4	0x0903	//	D段下行信道号4
#define	PARA_D_DL_CHANNEL5	0x0904	//	D段下行信道号5
#define	PARA_D_DL_CHANNEL6	0x0905	//	D段下行信道号6
#define	PARA_D_DL_CHANNEL7	0x0906	//	D段下行信道号7
#define	PARA_D_DL_CHANNEL8	0x0907	//	D段下行信道号8
#define	PARA_D_DL_CHANNEL9	0x0908	//	D段下行信道号9
#define	PARA_D_DL_CHANNEL10	0x0909	//	D段下行信道号10
#define	PARA_D_UL_CHANNEL1	0x0900	//	D段上行信道号1
#define	PARA_D_UL_CHANNEL2	0x0901	//	D段上行信道号2
#define	PARA_D_UL_CHANNEL3	0x0902	//	D段上行信道号3
#define	PARA_D_UL_CHANNEL4	0x0903	//	D段上行信道号4
#define	PARA_D_UL_CHANNEL5	0x0904	//	D段上行信道号5
#define	PARA_D_UL_CHANNEL6	0x0905	//	D段上行信道号6
#define	PARA_D_UL_CHANNEL7	0x0906	//	D段上行信道号7
#define	PARA_D_UL_CHANNEL8	0x0907	//	D段上行信道号8
#define	PARA_D_UL_CHANNEL9	0x0908	//	D段上行信道号9
#define	PARA_D_UL_CHANNEL10	0x0909	//	D段上行信道号10
#define	PARA_D_DCH_MAX_POW1	0x0348	//	D段下行通道最大输出功率1
#define	PARA_D_DCH_MAX_POW2	0	//	D段下行通道最大输出功率2
#define	PARA_D_DCH_MAX_POW3	0	//	D段下行通道最大输出功率3
#define	PARA_D_DCH_MAX_POW4	0	//	D段下行通道最大输出功率4
#define	PARA_D_DCH_MAX_POW5	0	//	D段下行通道最大输出功率5
#define	PARA_D_DCH_MAX_POW6	0	//	D段下行通道最大输出功率6
#define	PARA_D_DCH_MAX_POW7	0	//	D段下行通道最大输出功率7
#define	PARA_D_DCH_MAX_POW8	0	//	D段下行通道最大输出功率8
#define	PARA_D_DCH_MAX_POW9	0	//	D段下行通道最大输出功率9
#define	PARA_D_DCH_MAX_POW10	0	//	D段下行通道最大输出功率10
#define	PARA_D_DCH_MAX_POW11	0	//	D段下行通道最大输出功率11
#define	PARA_D_DCH_MAX_POW12	0	//	D段下行通道最大输出功率12
#define	PARA_D_DCH_MAX_POW13	0	//	D段下行通道最大输出功率13
#define	PARA_D_DCH_MAX_POW14	0	//	D段下行通道最大输出功率14
#define	PARA_D_DCH_MAX_POW15	0	//	D段下行通道最大输出功率15
#define	PARA_D_DCH_MAX_POW16	0	//	D段下行通道最大输出功率16
#define	PARA_D_UCH_MAX_POW1	0x0340	//	D段上行通道最大输入功率1
#define	PARA_D_UCH_MAX_POW2	0	//	D段上行通道最大输入功率2
#define	PARA_D_UCH_MAX_POW3	0	//	D段上行通道最大输入功率3
#define	PARA_D_UCH_MAX_POW4	0	//	D段上行通道最大输入功率4
#define	PARA_D_UCH_MAX_POW5	0	//	D段上行通道最大输入功率5
#define	PARA_D_UCH_MAX_POW6	0	//	D段上行通道最大输入功率6
#define	PARA_D_UCH_MAX_POW7	0	//	D段上行通道最大输入功率7
#define	PARA_D_UCH_MAX_POW8	0	//	D段上行通道最大输入功率8
#define	PARA_D_UCH_MAX_POW9	0	//	D段上行通道最大输入功率9
#define	PARA_D_UCH_MAX_POW10	0	//	D段上行通道最大输入功率10
#define	PARA_D_UCH_MAX_POW11	0	//	D段上行通道最大输入功率11
#define	PARA_D_UCH_MAX_POW12	0	//	D段上行通道最大输入功率12
#define	PARA_D_UCH_MAX_POW13	0	//	D段上行通道最大输入功率13
#define	PARA_D_UCH_MAX_POW14	0	//	D段上行通道最大输入功率14
#define	PARA_D_UCH_MAX_POW15	0	//	D段上行通道最大输入功率15
#define	PARA_D_UCH_MAX_POW16	0	//	D段上行通道最大输入功率16
#define	PARA_D_DCH_POW1	0	//	D段选频通道下行功率1
#define	PARA_D_DCH_POW2	0	//	D段选频通道下行功率2
#define	PARA_D_DCH_POW3	0	//	D段选频通道下行功率3
#define	PARA_D_DCH_POW4	0	//	D段选频通道下行功率4
#define	PARA_D_DCH_POW5	0	//	D段选频通道下行功率5
#define	PARA_D_DCH_POW6	0	//	D段选频通道下行功率6
#define	PARA_D_DCH_POW7	0	//	D段选频通道下行功率7
#define	PARA_D_DCH_POW8	0	//	D段选频通道下行功率8
#define	PARA_D_DCH_POW9	0	//	D段选频通道下行功率9
#define	PARA_D_DCH_POW10	0	//	D段选频通道下行功率10
#define	PARA_D_DCH_POW11	0	//	D段选频通道下行功率11
#define	PARA_D_DCH_POW12	0	//	D段选频通道下行功率12
#define	PARA_D_DCH_POW13	0	//	D段选频通道下行功率13
#define	PARA_D_DCH_POW14	0	//	D段选频通道下行功率14
#define	PARA_D_DCH_POW15	0	//	D段选频通道下行功率15
#define	PARA_D_DCH_POW16	0	//	D段选频通道下行功率16
#define	PARA_D_UCH_POW1	0	//	D段选频通道上行功率1
#define	PARA_D_UCH_POW2	0	//	D段选频通道上行功率2
#define	PARA_D_UCH_POW3	0	//	D段选频通道上行功率3
#define	PARA_D_UCH_POW4	0	//	D段选频通道上行功率4
#define	PARA_D_UCH_POW5	0	//	D段选频通道上行功率5
#define	PARA_D_UCH_POW6	0	//	D段选频通道上行功率6
#define	PARA_D_UCH_POW7	0	//	D段选频通道上行功率7
#define	PARA_D_UCH_POW8	0	//	D段选频通道上行功率8
#define	PARA_D_UCH_POW9	0	//	D段选频通道上行功率9
#define	PARA_D_UCH_POW10	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW11	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW12	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW13	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW14	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW15	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW16	0	//	D段选频通道上行功率10
#define	PARA_D_UDPX_IN_GAIN	0x08AB	//	D段下行输入双工器增益
#define	PARA_D_UDPX_OUT_GAIN	0x08AA	//	D段上行输出双工器增益
#define	PARA_D_DL_TOTAL_POW	0x8390	//	D段下行输入总功率
#define	PARA_D_UL_TOTAL_POW	0x831e	//	D段上行输出总功率
#define	PARA_D_REC_DPX_IG		0		//		REC的D段输入双工器增益，用来进行增益计算，只读							
#define	PARA_D_REC_DPX_OG		0		//		REC的D段输出双工器增益，用来进行增益计算，只读	
#define	PARA_REC_TO_RE_DELAY		0x889e	// REC到RE的光纤延时
#define	PARA_RE_RF_DELAY			0x889f	// RE的射频延时
#define	PARA_MAX_T14	0x889c	//	光口最大延时
#define	PARA_DL_DELAY_OFFSET	0x0768	//	下行延时偏移量
#define	PARA_UL_DELAY_OFFSET	0x0769	//	上行延时偏移量
#define	PARA_PRI_SOFT_V	0xf018	//	程序版本号（用ASCII码）
#define	PARA_PRI_HARD_V	0xf026	//	PCB版本号(用ASCII码)
#define	PARA_TD_1ST_CP_TIME		0x08a7	// TD第1转换点时间ns, 有符号数
#define	PARA_TD_2ND_CP_TIME		0x08a8	// TD第2转换点时间ns, 有符号数
#define	PARA_TD_LNA_ON_TIME		0x08ae	// LNA开启迟后DN_PA关闭的保护时间ns
#define	PARA_TD_LNA_OFF_TIME		0x08af	// LNA关闭超前DN_PA开启的保护时间ns
#define	PARA_TD_SLOT1_UPOW	0x7501	// TD时隙1上行检测功率
#define	PARA_TD_SLOT2_UPOW	0x7502	// TD时隙2上行检测功率
#define	PARA_TD_SLOT3_UPOW	0x7503	// TD时隙3上行检测功率
#define	PARA_TD_SLOT4_UPOW	0x7504	// TD时隙4上行检测功率
#define	PARA_TD_SLOT5_UPOW	0x7505	// TD时隙5上行检测功率
#define	PARA_TD_SLOT6_UPOW	0x7506	// TD时隙6上行检测功率
#define	PARA_TD_SLOT7_UPOW	0x7507	// TD时隙7上行检测功率
#define	PARA_TD_SLOT1_DPOW	0x7511	// TD时隙1下行检测功率
#define	PARA_TD_SLOT2_DPOW	0x7512	// TD时隙2下行检测功率
#define	PARA_TD_SLOT3_DPOW	0x7513	// TD时隙3下行检测功率
#define	PARA_TD_SLOT4_DPOW	0x7514	// TD时隙4下行检测功率
#define	PARA_TD_SLOT5_DPOW	0x7515	// TD时隙5下行检测功率
#define	PARA_TD_SLOT6_DPOW	0x7516	// TD时隙6下行检测功率
#define	PARA_TD_SLOT7_DPOW	0x7517	// TD时隙7下行检测功率
#define	PARA_FPS_S1 0 // 频点搜素: 范围1起始频点
#define	PARA_FPS_E1 0 // 频点搜素: 范围1结束频点
#define	PARA_FPS_S2 0 // 频点搜素: 范围2起始频点
#define	PARA_FPS_E2 0 // 频点搜素: 范围2结束频点
#define	PARA_FPS_BCCH_LK_SET	0x0923	// 频点搜索: 锁频信道号: 标准信道号, 65535-退出锁频
#define	PARA_FPS_CID_LK_SET	0x0926	// 频点搜索: 小区识别码参考值, 0-退出小区锁定功能
#define	PARA_FPS_BCCH_FC_M	0x8940	// 频点搜索: 主小区BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_CA_FC_0	0x8941	// 频点搜索: CA载波0信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_1	0x8942	// 频点搜索: CA载波1信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_2	0x8943	// 频点搜索: CA载波2信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_3	0x8944	// 频点搜索: CA载波3信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_4	0x8945	// 频点搜索: CA载波4信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_5	0x8946	// 频点搜索: CA载波5信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_6	0x8947	// 频点搜索: CA载波6信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_7	0x8948	// 频点搜索: CA载波7信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_8	0x8949	// 频点搜索: CA载波8信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_9	0x894A	// 频点搜索: CA载波9信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_10	0x894B	// 频点搜索: CA载波10信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_11	0x894C	// 频点搜索: CA载波11信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_12	0x894D	// 频点搜索: CA载波12信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_13	0x894E	// 频点搜索: CA载波13信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_14	0x894F	// 频点搜索: CA载波14信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_15	0x8950	// 频点搜索: CA载波15信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_BCCH_FC_1	0x8951	// 频点搜索: 邻小区1 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_2	0x8952	// 频点搜索: 邻小区2 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_3	0x8953	// 频点搜索: 邻小区3 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_4	0x8954	// 频点搜索: 邻小区4 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_5	0x8955	// 频点搜索: 邻小区5 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_6	0x8956	// 频点搜索: 邻小区6 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_AREA_ID	0x8958	// 频点搜索: 位置区编码
#define	PARA_FPS_CID		0x895A	// 频点搜索: 小区识别码实时值
#define	PARA_FPS_CID_1 0 // 频点搜索: 邻小区1 CID小区识别码
#define	PARA_FPS_CID_2 0 // 频点搜索: 邻小区2 CID小区识别码
#define	PARA_FPS_CID_3 0 // 频点搜索: 邻小区3 CID小区识别码
#define	PARA_FPS_CID_4 0 // 频点搜索: 邻小区4 CID小区识别码
#define	PARA_FPS_CID_5 0 // 频点搜索: 邻小区5 CID小区识别码
#define	PARA_FPS_CID_6 0 // 频点搜索: 邻小区6 CID小区识别码
#define	PARA_A_EXPA_IDRAIN_SET	0	// 微功放: 漏极电流设置,mA
#define	PARA_TD_SLOT1_DPOW_OVER_THR				0x0a60       //td下行输入导频过功率门限
#define	PARA_TD_SLOT1_DPOW_OWE_THR				0x0a61      //td下行输入导频欠功率门限	
#define PARA_A_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //下行输入过功率门限
#define PARA_A_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //下行输入欠功率门限
#define PARA_B_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //下行输入过功率门限
#define PARA_B_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //下行输入欠功率门限
#define PARA_C_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //下行输入过功率门限
#define PARA_C_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //下行输入欠功率门限
#define PARA_D_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //下行输入过功率门限
#define PARA_D_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //下行输入欠功率门限
#define PARA_REE_A_DL_OUT_TOTAL_POW_DETECT     	0x8004      //A段RE下行输出总功率//注REC\RE使用 MADD_A_DL_TOTAL_POW
#define PARA_A_RE_LOCAL_ST_ALARM     			0x8a33      	//覆盖单元本地告警状态
#define PARA_REE_B_DL_OUT_TOTAL_POW_DETECT     	0x8004      //B段RE下行输出总功率 //注REC\RE使用 MADD_B_DL_TOTAL_POW
#define PARA_B_RE_LOCAL_ST_ALARM     			0x8a33      	//覆盖单元本地告警状态
#define PARA_REE_C_DL_OUT_TOTAL_POW_DETECT     	0x8004      //A段RE下行输出总功率//注REC\RE使用 MADD_C_DL_TOTAL_POW
#define PARA_C_RE_LOCAL_ST_ALARM     			0x8a33      	//覆盖单元本地告警状态
#define PARA_REE_D_DL_OUT_TOTAL_POW_DETECT     	0x8004      //	D段RE下行输出总功率 //注REC\RE使用 MADD_D_DL_TOTAL_POW
#define PARA_D_RE_LOCAL_ST_ALARM     			0x8a33      	//	D覆盖单元本地告警状态
#define PARA_C_TD_1ST_CP_TIME	0x08a7	//		//465		TD第1转换点时间,ns,		
#define PARA_C_TD_2ND_CP_TIME	0x08a8	//		//466		TD第2转换点时间,ns,		
#define PARA_C_TD_LNA_ON_TIME	0x08ae	//		//467		LNA开启迟后DN_PA关闭的保护时间ns		
#define PARA_C_TD_LNA_OFF_TIME	0x08af	//		//468		LNA关闭超前DN_PA开启的保护时间ns		
#define PARA_C_TD_SLOT1_DPOW_OVER_THR	0x0a60	//		//469	0	//		//5625
#define PARA_C_TD_SLOT1_DPOW_OWE_THR	0x0a61	//		//470	0	//		//5626
#define PARA_D_TD_1ST_CP_TIME	0x08a7	//		//471		TD第1转换点时间,ns,		
#define PARA_D_TD_2ND_CP_TIME	0x08a7	//		//472		TD第2转换点时间,ns,		
#define PARA_D_TD_LNA_ON_TIME	0x08ae	//		//473		LNA开启迟后DN_PA关闭的保护时间ns		
#define PARA_D_TD_LNA_OFF_TIME	0x08af	//		//474		LNA关闭超前DN_PA开启的保护时间ns		
#define PARA_D_TD_SLOT1_DPOW_OVER_THR	0x0a60	//		//475	0	//		//5625
#define PARA_D_TD_SLOT1_DPOW_OWE_THR	0x0a61	//		//476	0	//		//5626
#define PARA_C_TD_SLOT1_POW	0	//		//477		TD时隙1输入检测功率	
#define PARA_C_TD_SLOT2_POW	0	//		//478		TD时隙2输入检测功率	
#define PARA_C_TD_SLOT3_POW	0	//		//479		TD时隙3输入检测功率	
#define PARA_C_TD_SLOT4_POW	0	//		//480		TD时隙4输入检测功率	
#define PARA_C_TD_SLOT5_POW	0	//		//481		TD时隙5输入检测功率	
#define PARA_C_TD_SLOT6_POW	0	//		//482		TD时隙6输入检测功率	
#define PARA_C_TD_SLOT7_POW	0	//		//483		TD时隙7输入检测功率	
#define PARA_C_TD_SLOT8_POW	0	//		//484		TD时隙8输入检测功率	
#define PARA_C_TD_SLOT9_POW	0	//		//485		TD时隙9输入检测功率	
#define PARA_C_TD_SLOT10_POW	0	//		//486		TD时隙10输入检测功率	
#define PARA_C_TD_SLOT11_POW	0	//		//487		TD时隙11输入检测功率	
#define PARA_C_TD_SLOT12_POW	0	//		//488		TD时隙12输入检测功率	
#define PARA_C_TD_SLOT13_POW	0	//		//489		TD时隙13输入检测功率	
#define PARA_C_TD_SLOT14_POW	0	//		//490		TD时隙14输入检测功率	
#define PARA_C_TD_SLOT15_POW	0	//		//491		TD时隙15输入检测功率	
#define PARA_C_TD_SLOT16_POW	0	//		//492		TD时隙16输入检测功率	
#define PARA_C_TD_SLOT17_POW	0	//		//493		TD时隙17输入检测功率
#define PARA_C_TD_SLOT18_POW	0	//		//494		TD时隙18输入检测功率
#define PARA_C_TD_SLOT19_POW	0	//		//495		TD时隙19输入检测功率
#define PARA_C_TD_SLOT20_POW	0	//		//496		TD时隙20输入检测功率
#define PARA_D_TD_SLOT1_POW	0	//		//497		TD时隙1输入检测功率
#define PARA_D_TD_SLOT2_POW	0	//		//498		TD时隙2输入检测功率
#define PARA_D_TD_SLOT3_POW	0	//		//499		TD时隙3输入检测功率
#define PARA_D_TD_SLOT4_POW	0	//		//500		TD时隙4输入检测功率
#define PARA_D_TD_SLOT5_POW	0	//		//501		TD时隙5输入检测功率
#define PARA_D_TD_SLOT6_POW	0	//		//502		TD时隙6输入检测功率
#define PARA_D_TD_SLOT7_POW	0	//		//503		TD时隙7输入检测功率
#define PARA_D_TD_SLOT8_POW	0	//		//504		TD时隙8输入检测功率
#define PARA_D_TD_SLOT9_POW	0	//		//505		TD时隙9输入检测功率
#define PARA_D_TD_SLOT10_POW	0	//		//506		TD时隙10输入检测功率
#define PARA_D_TD_SLOT11_POW	0	//		//507		TD时隙11输入检测功率
#define PARA_D_TD_SLOT12_POW	0	//		//508		TD时隙12输入检测功率
#define PARA_D_TD_SLOT13_POW	0	//		//509		TD时隙13输入检测功率
#define PARA_D_TD_SLOT14_POW	0	//		//510		TD时隙14输入检测功率
#define PARA_D_TD_SLOT15_POW	0	//		//511		TD时隙15输入检测功率
#define PARA_D_TD_SLOT16_POW	0	//		//512		TD时隙16输入检测功率
#define PARA_D_TD_SLOT17_POW	0	//		//513		TD时隙17输入检测功率
#define PARA_D_TD_SLOT18_POW	0	//		//514		TD时隙18输入检测功率
#define PARA_D_TD_SLOT19_POW	0	//		//515		TD时隙19输入检测功率
#define PARA_D_TD_SLOT20_POW	0	//		//516		TD时隙20输入检测功率
#define	PARA_DL_DELAY_OFFSET_B		0//0x889c		//		下行延时偏移量		
#define	PARA_DL_DELAY_OFFSET_C		0//0x889c		//		下行延时偏移量		
#define	PARA_DL_DELAY_OFFSET_D		0//0x889c		//		下行延时偏移量		
#define	PARA_VGS_A		            0		//	         A段栅压		
#define	PARA_VGS_B          		0		//		 B段栅压		
#define	PARA_VGS_C          		0		//		 C段栅压
#define	PARA_VGS_D          		0		//		 D段栅压
#define	PARA_VGS_COMP_A		        0		//	     A段栅压补偿		
#define	PARA_VGS_COMP_B             0		//		 B段栅压补偿			
#define	PARA_VGS_COMP_C             0		//		 C段栅压补偿	
#define	PARA_VGS_COMP_D          	0		//		 C段栅压补偿	
#define	PARA_ATT_DATA_COMP_A		0				//ATT补偿数据
#define	PARA_ATT_DATA_COMP_B		0				//ATT补偿数据
#define	PARA_ATT_DATA_COMP_C		0				//ATT补偿数据
#define	PARA_ATT_DATA_COMP_D		0				//ATT补偿数据
#define	PARA_MAX_T14_A	0x889c	//	光口最大延时
#define	PARA_MAX_T14_B	0x889c	//	光口最大延时
#define	PARA_MAX_T14_C	0x889c	//	光口最大延时
#define	PARA_MAX_T14_D	0x889c	//	光口最大延时
#define PARA_ERL_JG_A		0// A段话务量统计结果
#define PARA_ERL_JG_B		0
#define PARA_ERL_JG_C		0
#define PARA_ERL_JG_D		0
#define	PARA_MOVE_CENTER_FRE_D		0//改变下行中频频率
#define	PARA_MOVE_CENTER_FRE_U		0//改变上行中频频率



#else
	// 普通参数
// 参数地址定义==================================================== 2b
#define	PARA_A_DL_CHANNEL1	0x0900	//	A段下行信道号1
#define	PARA_A_DL_CHANNEL2	0x0901	//	A段下行信道号2
#define	PARA_A_DL_CHANNEL3	0x0902	//	A段下行信道号3
#define	PARA_A_DL_CHANNEL4	0x0903	//	A段下行信道号4
#define	PARA_A_DL_CHANNEL5	0x0904	//	A段下行信道号5
#define	PARA_A_DL_CHANNEL6	0x0905	//	A段下行信道号6
#define	PARA_A_DL_CHANNEL7	0x0906	//	A段下行信道号7
#define	PARA_A_DL_CHANNEL8	0x0907	//	A段下行信道号8
#define	PARA_A_DL_CHANNEL9	0x0908	//	A段下行信道号9
#define	PARA_A_DL_CHANNEL10	0x0909	//	A段下行信道号10
#define	PARA_A_DL_CHANNEL11	0x090A	//	A段下行信道号11
#define	PARA_A_DL_CHANNEL12	0x090B	//	A段下行信道号12
#define	PARA_A_DL_CHANNEL13	0x090C	//	A段下行信道号13
#define	PARA_A_DL_CHANNEL14	0x090D	//	A段下行信道号14
#define	PARA_A_DL_CHANNEL15	0x090E	//	A段下行信道号15
#define	PARA_A_DL_CHANNEL16	0x090F	//	A段下行信道号16
#define	PARA_A_UL_CHANNEL1	0x0900	//	A段上行信道号1
#define	PARA_A_UL_CHANNEL2	0x0901	//	A段上行信道号2
#define	PARA_A_UL_CHANNEL3	0x0902	//	A段上行信道号3
#define	PARA_A_UL_CHANNEL4	0x0903	//	A段上行信道号4
#define	PARA_A_UL_CHANNEL5	0x0904	//	A段上行信道号5
#define	PARA_A_UL_CHANNEL6	0x0905	//	A段上行信道号6
#define	PARA_A_UL_CHANNEL7	0x0906	//	A段上行信道号7
#define	PARA_A_UL_CHANNEL8	0x0907	//	A段上行信道号8
#define	PARA_A_UL_CHANNEL9	0x0908	//	A段上行信道号9
#define	PARA_A_UL_CHANNEL10	0x0909	//	A段上行信道号10
#define	PARA_A_UL_CHANNEL11	0x090A	//	A段上行信道号11
#define	PARA_A_UL_CHANNEL12	0x090B	//	A段上行信道号12
#define	PARA_A_UL_CHANNEL13	0x090C	//	A段上行信道号13
#define	PARA_A_UL_CHANNEL14	0x090D	//	A段上行信道号14
#define	PARA_A_UL_CHANNEL15	0x090E	//	A段上行信道号15
#define	PARA_A_UL_CHANNEL16	0x090F	//	A段上行信道号16
#define	PARA_A_DCH_MAX_POW1	0x0348	//	A段下行通道最大输出功率1
#define	PARA_A_DCH_MAX_POW2	0	//	A段下行通道最大输出功率2
#define	PARA_A_DCH_MAX_POW3	0	//	A段下行通道最大输出功率3
#define	PARA_A_DCH_MAX_POW4	0	//	A段下行通道最大输出功率4
#define	PARA_A_DCH_MAX_POW5	0	//	A段下行通道最大输出功率5
#define	PARA_A_DCH_MAX_POW6	0	//	A段下行通道最大输出功率6
#define	PARA_A_DCH_MAX_POW7	0	//	A段下行通道最大输出功率7
#define	PARA_A_DCH_MAX_POW8	0	//	A段下行通道最大输出功率8
#define	PARA_A_DCH_MAX_POW9	0	//	A段下行通道最大输出功率9
#define	PARA_A_DCH_MAX_POW10	0	//	A段下行通道最大输出功率10
#define	PARA_A_DCH_MAX_POW11	0	//	A段下行通道最大输出功率11
#define	PARA_A_DCH_MAX_POW12	0	//	A段下行通道最大输出功率12
#define	PARA_A_DCH_MAX_POW13	0	//	A段下行通道最大输出功率13
#define	PARA_A_DCH_MAX_POW14	0	//	A段下行通道最大输出功率14
#define	PARA_A_DCH_MAX_POW15	0	//	A段下行通道最大输出功率15
#define	PARA_A_DCH_MAX_POW16	0	//	A段下行通道最大输出功率16
#define	PARA_A_UCH_MAX_POW1	0x0340	//	A段上行通道最大输入功率1
#define	PARA_A_UCH_MAX_POW2	0	//	A段上行通道最大输入功率2
#define	PARA_A_UCH_MAX_POW3	0	//	A段上行通道最大输入功率3
#define	PARA_A_UCH_MAX_POW4	0	//	A段上行通道最大输入功率4
#define	PARA_A_UCH_MAX_POW5	0	//	A段上行通道最大输入功率5
#define	PARA_A_UCH_MAX_POW6	0	//	A段上行通道最大输入功率6
#define	PARA_A_UCH_MAX_POW7	0	//	A段上行通道最大输入功率7
#define	PARA_A_UCH_MAX_POW8	0	//	A段上行通道最大输入功率8
#define	PARA_A_UCH_MAX_POW9	0	//	A段上行通道最大输入功率9
#define	PARA_A_UCH_MAX_POW10	0	//	A段上行通道最大输入功率10
#define	PARA_A_UCH_MAX_POW11	0	//	A段上行通道最大输入功率11
#define	PARA_A_UCH_MAX_POW12	0	//	A段上行通道最大输入功率12
#define	PARA_A_UCH_MAX_POW13	0	//	A段上行通道最大输入功率13
#define	PARA_A_UCH_MAX_POW14	0	//	A段上行通道最大输入功率14
#define	PARA_A_UCH_MAX_POW15	0	//	A段上行通道最大输入功率15
#define	PARA_A_UCH_MAX_POW16	0	//	A段上行通道最大输入功率16
#define	PARA_A_DCH_POW1	0	//	A段选频通道下行功率1
#define	PARA_A_DCH_POW2	0	//	A段选频通道下行功率2
#define	PARA_A_DCH_POW3	0	//	A段选频通道下行功率3
#define	PARA_A_DCH_POW4	0	//	A段选频通道下行功率4
#define	PARA_A_DCH_POW5	0	//	A段选频通道下行功率5
#define	PARA_A_DCH_POW6	0	//	A段选频通道下行功率6
#define	PARA_A_DCH_POW7	0	//	A段选频通道下行功率7
#define	PARA_A_DCH_POW8	0	//	A段选频通道下行功率8
#define	PARA_A_DCH_POW9	0	//	A段选频通道下行功率9
#define	PARA_A_DCH_POW10	0	//	A段选频通道下行功率10
#define	PARA_A_DCH_POW11	0	//	A段选频通道下行功率11
#define	PARA_A_DCH_POW12	0	//	A段选频通道下行功率12
#define	PARA_A_DCH_POW13	0	//	A段选频通道下行功率13
#define	PARA_A_DCH_POW14	0	//	A段选频通道下行功率14
#define	PARA_A_DCH_POW15	0	//	A段选频通道下行功率15
#define	PARA_A_DCH_POW16	0	//	A段选频通道下行功率16
#define	PARA_A_UCH_POW1	0	//	A段选频通道上行功率1
#define	PARA_A_UCH_POW2	0	//	A段选频通道上行功率2
#define	PARA_A_UCH_POW3	0	//	A段选频通道上行功率3
#define	PARA_A_UCH_POW4	0	//	A段选频通道上行功率4
#define	PARA_A_UCH_POW5	0	//	A段选频通道上行功率5
#define	PARA_A_UCH_POW6	0	//	A段选频通道上行功率6
#define	PARA_A_UCH_POW7	0	//	A段选频通道上行功率7
#define	PARA_A_UCH_POW8	0	//	A段选频通道上行功率8
#define	PARA_A_UCH_POW9	0	//	A段选频通道上行功率9
#define	PARA_A_UCH_POW10	0	//	A段选频通道上行功率10
#define	PARA_A_UCH_POW11	0	//	A段选频通道上行功率11
#define	PARA_A_UCH_POW12	0	//	A段选频通道上行功率12
#define	PARA_A_UCH_POW13	0	//	A段选频通道上行功率13
#define	PARA_A_UCH_POW14	0	//	A段选频通道上行功率14
#define	PARA_A_UCH_POW15	0	//	A段选频通道上行功率15
#define	PARA_A_UCH_POW16	0	//	A段选频通道上行功率16
#define	PARA_A_UDPX_IN_GAIN		0x08AB	//	A段下行输入双工器增益
#define	PARA_A_UDPX_OUT_GAIN	0x08AA	//	A段上行输出双工器增益
#define	PARA_A_DL_TOTAL_POW	0x8390	//	A段下行输入总功率
#define	PARA_A_UL_TOTAL_POW	0x831e	//	A段上行输出总功率
#define	PARA_A_REC_DPX_IG		0		//		REC的A段输入双工器增益，用来进行增益计算，只读							
#define	PARA_A_REC_DPX_OG		0		//		REC的A段输出双工器增益，用来进行增益计算，只读	
#define	PARA_B_DL_CHANNEL1	0x0900	//	B段下行信道号1
#define	PARA_B_DL_CHANNEL2	0x0901	//	B段下行信道号2
#define	PARA_B_DL_CHANNEL3	0x0902	//	B段下行信道号3
#define	PARA_B_DL_CHANNEL4	0x0903	//	B段下行信道号4
#define	PARA_B_DL_CHANNEL5	0x0904	//	B段下行信道号5
#define	PARA_B_DL_CHANNEL6	0x0905	//	B段下行信道号6
#define	PARA_B_DL_CHANNEL7	0x0906	//	B段下行信道号7
#define	PARA_B_DL_CHANNEL8	0x0907	//	B段下行信道号8
#define	PARA_B_DL_CHANNEL9	0x0908	//	B段下行信道号9
#define	PARA_B_DL_CHANNEL10	0x0909	//	B段下行信道号10
#define	PARA_B_DL_CHANNEL11	0x090A	//	B段下行信道号11
#define	PARA_B_DL_CHANNEL12	0x090B	//	B段下行信道号12
#define	PARA_B_DL_CHANNEL13	0x090C	//	B段下行信道号13
#define	PARA_B_DL_CHANNEL14	0x090D	//	B段下行信道号14
#define	PARA_B_DL_CHANNEL15	0x090E	//	B段下行信道号15
#define	PARA_B_DL_CHANNEL16	0x090F	//	B段下行信道号16
#define	PARA_B_UL_CHANNEL1	0x0900	//	B段上行信道号1
#define	PARA_B_UL_CHANNEL2	0x0901	//	B段上行信道号2
#define	PARA_B_UL_CHANNEL3	0x0902	//	B段上行信道号3
#define	PARA_B_UL_CHANNEL4	0x0903	//	B段上行信道号4
#define	PARA_B_UL_CHANNEL5	0x0904	//	B段上行信道号5
#define	PARA_B_UL_CHANNEL6	0x0905	//	B段上行信道号6
#define	PARA_B_UL_CHANNEL7	0x0906	//	B段上行信道号7
#define	PARA_B_UL_CHANNEL8	0x0907	//	B段上行信道号8
#define	PARA_B_UL_CHANNEL9	0x0908	//	B段上行信道号9
#define	PARA_B_UL_CHANNEL10	0x0909	//	B段上行信道号10
#define	PARA_B_UL_CHANNEL11	0x090A	//	B段上行信道号11
#define	PARA_B_UL_CHANNEL12	0x090B	//	B段上行信道号12
#define	PARA_B_UL_CHANNEL13	0x090C	//	B段上行信道号13
#define	PARA_B_UL_CHANNEL14	0x090D	//	B段上行信道号14
#define	PARA_B_UL_CHANNEL15	0x090E	//	B段上行信道号15
#define	PARA_B_UL_CHANNEL16	0x090F	//	B段上行信道号16
#define	PARA_B_DCH_MAX_POW1	0x0348	//	B段下行通道最大输出功率1
#define	PARA_B_DCH_MAX_POW2	0	//	B段下行通道最大输出功率2
#define	PARA_B_DCH_MAX_POW3	0	//	B段下行通道最大输出功率3
#define	PARA_B_DCH_MAX_POW4	0	//	B段下行通道最大输出功率4
#define	PARA_B_DCH_MAX_POW5	0	//	B段下行通道最大输出功率5
#define	PARA_B_DCH_MAX_POW6	0	//	B段下行通道最大输出功率6
#define	PARA_B_DCH_MAX_POW7	0	//	B段下行通道最大输出功率7
#define	PARA_B_DCH_MAX_POW8	0	//	B段下行通道最大输出功率8
#define	PARA_B_DCH_MAX_POW9	0	//	B段下行通道最大输出功率9
#define	PARA_B_DCH_MAX_POW10	0	//	B段下行通道最大输出功率10
#define	PARA_B_DCH_MAX_POW11	0	//	B段下行通道最大输出功率11
#define	PARA_B_DCH_MAX_POW12	0	//	B段下行通道最大输出功率12
#define	PARA_B_DCH_MAX_POW13	0	//	B段下行通道最大输出功率13
#define	PARA_B_DCH_MAX_POW14	0	//	B段下行通道最大输出功率14
#define	PARA_B_DCH_MAX_POW15	0	//	B段下行通道最大输出功率15
#define	PARA_B_DCH_MAX_POW16	0	//	B段下行通道最大输出功率16
#define	PARA_B_UCH_MAX_POW1	0x0340	//	B段上行通道最大输入功率1
#define	PARA_B_UCH_MAX_POW2	0	//	B段上行通道最大输入功率2
#define	PARA_B_UCH_MAX_POW3	0	//	B段上行通道最大输入功率3
#define	PARA_B_UCH_MAX_POW4	0	//	B段上行通道最大输入功率4
#define	PARA_B_UCH_MAX_POW5	0	//	B段上行通道最大输入功率5
#define	PARA_B_UCH_MAX_POW6	0	//	B段上行通道最大输入功率6
#define	PARA_B_UCH_MAX_POW7	0	//	B段上行通道最大输入功率7
#define	PARA_B_UCH_MAX_POW8	0	//	B段上行通道最大输入功率8
#define	PARA_B_UCH_MAX_POW9	0	//	B段上行通道最大输入功率9
#define	PARA_B_UCH_MAX_POW10	0	//	B段上行通道最大输入功率10
#define	PARA_B_UCH_MAX_POW11	0	//	B段上行通道最大输入功率11
#define	PARA_B_UCH_MAX_POW12	0	//	B段上行通道最大输入功率12
#define	PARA_B_UCH_MAX_POW13	0	//	B段上行通道最大输入功率13
#define	PARA_B_UCH_MAX_POW14	0	//	B段上行通道最大输入功率14
#define	PARA_B_UCH_MAX_POW15	0	//	B段上行通道最大输入功率15
#define	PARA_B_UCH_MAX_POW16	0	//	B段上行通道最大输入功率16
#define	PARA_B_DCH_POW1	0	//	B段选频通道下行功率1
#define	PARA_B_DCH_POW2	0	//	B段选频通道下行功率2
#define	PARA_B_DCH_POW3	0	//	B段选频通道下行功率3
#define	PARA_B_DCH_POW4	0	//	B段选频通道下行功率4
#define	PARA_B_DCH_POW5	0	//	B段选频通道下行功率5
#define	PARA_B_DCH_POW6	0	//	B段选频通道下行功率6
#define	PARA_B_DCH_POW7	0	//	B段选频通道下行功率7
#define	PARA_B_DCH_POW8	0	//	B段选频通道下行功率8
#define	PARA_B_DCH_POW9	0	//	B段选频通道下行功率9
#define	PARA_B_DCH_POW10	0	//	B段选频通道下行功率10
#define	PARA_B_DCH_POW11	0	//	B段选频通道下行功率11
#define	PARA_B_DCH_POW12	0	//	B段选频通道下行功率12
#define	PARA_B_DCH_POW13	0	//	B段选频通道下行功率13
#define	PARA_B_DCH_POW14	0	//	B段选频通道下行功率14
#define	PARA_B_DCH_POW15	0	//	B段选频通道下行功率15
#define	PARA_B_DCH_POW16	0	//	B段选频通道下行功率16
#define	PARA_B_UCH_POW1	0	//	B段选频通道上行功率1
#define	PARA_B_UCH_POW2	0	//	B段选频通道上行功率2
#define	PARA_B_UCH_POW3	0	//	B段选频通道上行功率3
#define	PARA_B_UCH_POW4	0	//	B段选频通道上行功率4
#define	PARA_B_UCH_POW5	0	//	B段选频通道上行功率5
#define	PARA_B_UCH_POW6	0	//	B段选频通道上行功率6
#define	PARA_B_UCH_POW7	0	//	B段选频通道上行功率7
#define	PARA_B_UCH_POW8	0	//	B段选频通道上行功率8
#define	PARA_B_UCH_POW9	0	//	B段选频通道上行功率9
#define	PARA_B_UCH_POW10	0	//	B段选频通道上行功率10
#define	PARA_B_UCH_POW11	0	//	B段选频通道上行功率11
#define	PARA_B_UCH_POW12	0	//	B段选频通道上行功率12
#define	PARA_B_UCH_POW13	0	//	B段选频通道上行功率13
#define	PARA_B_UCH_POW14	0	//	B段选频通道上行功率14
#define	PARA_B_UCH_POW15	0	//	B段选频通道上行功率15
#define	PARA_B_UCH_POW16	0	//	B段选频通道上行功率16
#define	PARA_B_UDPX_IN_GAIN	0x08AB	//	B段下行输入双工器增益
#define	PARA_B_UDPX_OUT_GAIN	0x08AA	//	B段上行输出双工器增益
#define	PARA_B_DL_TOTAL_POW	0x8390	//	B段下行输入总功率
#define	PARA_B_UL_TOTAL_POW	0x831e	//	B段上行输出总功率
#define	PARA_B_REC_DPX_IG		0		//		REC的A段输入双工器增益，用来进行增益计算，只读							
#define	PARA_B_REC_DPX_OG		0		//		REC的A段输出双工器增益，用来进行增益计算，只读	
#define	PARA_C_DL_CHANNEL1	0x0900	//	C段下行信道号1
#define	PARA_C_DL_CHANNEL2	0x0901	//	C段下行信道号2
#define	PARA_C_DL_CHANNEL3	0x0902	//	C段下行信道号3
#define	PARA_C_DL_CHANNEL4	0x0903	//	C段下行信道号4
#define	PARA_C_DL_CHANNEL5	0x0904	//	C段下行信道号5
#define	PARA_C_DL_CHANNEL6	0x0905	//	C段下行信道号6
#define	PARA_C_DL_CHANNEL7	0x0906	//	C段下行信道号7
#define	PARA_C_DL_CHANNEL8	0x0907	//	C段下行信道号8
#define	PARA_C_DL_CHANNEL9	0x0908	//	C段下行信道号9
#define	PARA_C_DL_CHANNEL10	0x0909	//	C段下行信道号10
#define	PARA_C_UL_CHANNEL1	0x0900	//	C段上行信道号1
#define	PARA_C_UL_CHANNEL2	0x0901	//	C段上行信道号2
#define	PARA_C_UL_CHANNEL3	0x0902	//	C段上行信道号3
#define	PARA_C_UL_CHANNEL4	0x0903	//	C段上行信道号4
#define	PARA_C_UL_CHANNEL5	0x0904	//	C段上行信道号5
#define	PARA_C_UL_CHANNEL6	0x0905	//	C段上行信道号6
#define	PARA_C_UL_CHANNEL7	0x0906	//	C段上行信道号7
#define	PARA_C_UL_CHANNEL8	0x0907	//	C段上行信道号8
#define	PARA_C_UL_CHANNEL9	0x0908	//	C段上行信道号9
#define	PARA_C_UL_CHANNEL10	0x0909	//	C段上行信道号10
#define	PARA_C_DCH_MAX_POW1	0x0348	//	C段下行通道最大输出功率1
#define	PARA_C_DCH_MAX_POW2	0	//	C段下行通道最大输出功率2
#define	PARA_C_DCH_MAX_POW3	0	//	C段下行通道最大输出功率3
#define	PARA_C_DCH_MAX_POW4	0	//	C段下行通道最大输出功率4
#define	PARA_C_DCH_MAX_POW5	0	//	C段下行通道最大输出功率5
#define	PARA_C_DCH_MAX_POW6	0	//	C段下行通道最大输出功率6
#define	PARA_C_DCH_MAX_POW7	0	//	C段下行通道最大输出功率7
#define	PARA_C_DCH_MAX_POW8	0	//	C段下行通道最大输出功率8
#define	PARA_C_DCH_MAX_POW9	0	//	C段下行通道最大输出功率9
#define	PARA_C_DCH_MAX_POW10	0	//	C段下行通道最大输出功率10
#define	PARA_C_DCH_MAX_POW11	0	//	C段下行通道最大输出功率11
#define	PARA_C_DCH_MAX_POW12	0	//	C段下行通道最大输出功率12
#define	PARA_C_DCH_MAX_POW13	0	//	C段下行通道最大输出功率13
#define	PARA_C_DCH_MAX_POW14	0	//	C段下行通道最大输出功率14
#define	PARA_C_DCH_MAX_POW15	0	//	C段下行通道最大输出功率15
#define	PARA_C_DCH_MAX_POW16	0	//	C段下行通道最大输出功率16
#define	PARA_C_UCH_MAX_POW1	0x0340	//	C段上行通道最大输入功率1
#define	PARA_C_UCH_MAX_POW2	0	//	C段上行通道最大输入功率2
#define	PARA_C_UCH_MAX_POW3	0	//	C段上行通道最大输入功率3
#define	PARA_C_UCH_MAX_POW4	0	//	C段上行通道最大输入功率4
#define	PARA_C_UCH_MAX_POW5	0	//	C段上行通道最大输入功率5
#define	PARA_C_UCH_MAX_POW6	0	//	C段上行通道最大输入功率6
#define	PARA_C_UCH_MAX_POW7	0	//	C段上行通道最大输入功率7
#define	PARA_C_UCH_MAX_POW8	0	//	C段上行通道最大输入功率8
#define	PARA_C_UCH_MAX_POW9	0	//	C段上行通道最大输入功率9
#define	PARA_C_UCH_MAX_POW10		0	//	C段上行通道最大输入功率10
#define	PARA_C_UCH_MAX_POW11		0	//	C段上行通道最大输入功率11
#define	PARA_C_UCH_MAX_POW12		0	//	C段上行通道最大输入功率12
#define	PARA_C_UCH_MAX_POW13		0	//	C段上行通道最大输入功率13
#define	PARA_C_UCH_MAX_POW14		0	//	C段上行通道最大输入功率14
#define	PARA_C_UCH_MAX_POW15		0	//	C段上行通道最大输入功率15
#define	PARA_C_UCH_MAX_POW16		0	//	C段上行通道最大输入功率16
#define	PARA_C_DCH_POW1	0	//	C段选频通道下行功率1
#define	PARA_C_DCH_POW2	0	//	C段选频通道下行功率2
#define	PARA_C_DCH_POW3	0	//	C段选频通道下行功率3
#define	PARA_C_DCH_POW4	0	//	C段选频通道下行功率4
#define	PARA_C_DCH_POW5	0	//	C段选频通道下行功率5
#define	PARA_C_DCH_POW6	0	//	C段选频通道下行功率6
#define	PARA_C_DCH_POW7	0	//	C段选频通道下行功率7
#define	PARA_C_DCH_POW8	0	//	C段选频通道下行功率8
#define	PARA_C_DCH_POW9	0	//	C段选频通道下行功率9
#define	PARA_C_DCH_POW10	0	//	C段选频通道下行功率10
#define	PARA_C_DCH_POW11	0	//	C段选频通道下行功率11
#define	PARA_C_DCH_POW12	0	//	C段选频通道下行功率12
#define	PARA_C_DCH_POW13	0	//	C段选频通道下行功率13
#define	PARA_C_DCH_POW14	0	//	C段选频通道下行功率14
#define	PARA_C_DCH_POW15	0	//	C段选频通道下行功率15
#define	PARA_C_DCH_POW16	0	//	C段选频通道下行功率16
#define	PARA_C_UCH_POW1	0	//	C段选频通道上行功率1
#define	PARA_C_UCH_POW2	0	//	C段选频通道上行功率2
#define	PARA_C_UCH_POW3	0	//	C段选频通道上行功率3
#define	PARA_C_UCH_POW4	0	//	C段选频通道上行功率4
#define	PARA_C_UCH_POW5	0	//	C段选频通道上行功率5
#define	PARA_C_UCH_POW6	0	//	C段选频通道上行功率6
#define	PARA_C_UCH_POW7	0	//	C段选频通道上行功率7
#define	PARA_C_UCH_POW8	0	//	C段选频通道上行功率8
#define	PARA_C_UCH_POW9	0	//	C段选频通道上行功率9
#define	PARA_C_UCH_POW10	0	//	C段选频通道上行功率10
#define	PARA_C_UCH_POW11	0	//	C段选频通道上行功率11
#define	PARA_C_UCH_POW12	0	//	C段选频通道上行功率12
#define	PARA_C_UCH_POW13	0	//	C段选频通道上行功率13
#define	PARA_C_UCH_POW14	0	//	C段选频通道上行功率14
#define	PARA_C_UCH_POW15	0	//	C段选频通道上行功率15
#define	PARA_C_UCH_POW16	0	//	C段选频通道上行功率16
#define	PARA_C_UDPX_IN_GAIN	0x08AB	//	C段下行输入双工器增益
#define	PARA_C_UDPX_OUT_GAIN	0x08AA	//	C段上行输出双工器增益
#define	PARA_C_DL_TOTAL_POW	0x8390	//	C段下行输入总功率
#define	PARA_C_UL_TOTAL_POW	0x831e	//	C段上行输出总功率
#define	PARA_C_REC_DPX_IG		0		//		REC的A段输入双工器增益，用来进行增益计算，只读							
#define	PARA_C_REC_DPX_OG		0		//		REC的A段输出双工器增益，用来进行增益计算，只读	
#define	PARA_D_DL_CHANNEL1	0x0900	//	D段下行信道号1
#define	PARA_D_DL_CHANNEL2	0x0901	//	D段下行信道号2
#define	PARA_D_DL_CHANNEL3	0x0902	//	D段下行信道号3
#define	PARA_D_DL_CHANNEL4	0x0903	//	D段下行信道号4
#define	PARA_D_DL_CHANNEL5	0x0904	//	D段下行信道号5
#define	PARA_D_DL_CHANNEL6	0x0905	//	D段下行信道号6
#define	PARA_D_DL_CHANNEL7	0x0906	//	D段下行信道号7
#define	PARA_D_DL_CHANNEL8	0x0907	//	D段下行信道号8
#define	PARA_D_DL_CHANNEL9	0x0908	//	D段下行信道号9
#define	PARA_D_DL_CHANNEL10	0x0909	//	D段下行信道号10
#define	PARA_D_UL_CHANNEL1	0x0900	//	D段上行信道号1
#define	PARA_D_UL_CHANNEL2	0x0901	//	D段上行信道号2
#define	PARA_D_UL_CHANNEL3	0x0902	//	D段上行信道号3
#define	PARA_D_UL_CHANNEL4	0x0903	//	D段上行信道号4
#define	PARA_D_UL_CHANNEL5	0x0904	//	D段上行信道号5
#define	PARA_D_UL_CHANNEL6	0x0905	//	D段上行信道号6
#define	PARA_D_UL_CHANNEL7	0x0906	//	D段上行信道号7
#define	PARA_D_UL_CHANNEL8	0x0907	//	D段上行信道号8
#define	PARA_D_UL_CHANNEL9	0x0908	//	D段上行信道号9
#define	PARA_D_UL_CHANNEL10	0x0909	//	D段上行信道号10
#define	PARA_D_DCH_MAX_POW1	0x0348	//	D段下行通道最大输出功率1
#define	PARA_D_DCH_MAX_POW2	0	//	D段下行通道最大输出功率2
#define	PARA_D_DCH_MAX_POW3	0	//	D段下行通道最大输出功率3
#define	PARA_D_DCH_MAX_POW4	0	//	D段下行通道最大输出功率4
#define	PARA_D_DCH_MAX_POW5	0	//	D段下行通道最大输出功率5
#define	PARA_D_DCH_MAX_POW6	0	//	D段下行通道最大输出功率6
#define	PARA_D_DCH_MAX_POW7	0	//	D段下行通道最大输出功率7
#define	PARA_D_DCH_MAX_POW8	0	//	D段下行通道最大输出功率8
#define	PARA_D_DCH_MAX_POW9	0	//	D段下行通道最大输出功率9
#define	PARA_D_DCH_MAX_POW10	0	//	D段下行通道最大输出功率10
#define	PARA_D_DCH_MAX_POW11	0	//	D段下行通道最大输出功率11
#define	PARA_D_DCH_MAX_POW12	0	//	D段下行通道最大输出功率12
#define	PARA_D_DCH_MAX_POW13	0	//	D段下行通道最大输出功率13
#define	PARA_D_DCH_MAX_POW14	0	//	D段下行通道最大输出功率14
#define	PARA_D_DCH_MAX_POW15	0	//	D段下行通道最大输出功率15
#define	PARA_D_DCH_MAX_POW16	0	//	D段下行通道最大输出功率16
#define	PARA_D_UCH_MAX_POW1	0x0340	//	D段上行通道最大输入功率1
#define	PARA_D_UCH_MAX_POW2	0	//	D段上行通道最大输入功率2
#define	PARA_D_UCH_MAX_POW3	0	//	D段上行通道最大输入功率3
#define	PARA_D_UCH_MAX_POW4	0	//	D段上行通道最大输入功率4
#define	PARA_D_UCH_MAX_POW5	0	//	D段上行通道最大输入功率5
#define	PARA_D_UCH_MAX_POW6	0	//	D段上行通道最大输入功率6
#define	PARA_D_UCH_MAX_POW7	0	//	D段上行通道最大输入功率7
#define	PARA_D_UCH_MAX_POW8	0	//	D段上行通道最大输入功率8
#define	PARA_D_UCH_MAX_POW9	0	//	D段上行通道最大输入功率9
#define	PARA_D_UCH_MAX_POW10	0	//	D段上行通道最大输入功率10
#define	PARA_D_UCH_MAX_POW11	0	//	D段上行通道最大输入功率11
#define	PARA_D_UCH_MAX_POW12	0	//	D段上行通道最大输入功率12
#define	PARA_D_UCH_MAX_POW13	0	//	D段上行通道最大输入功率13
#define	PARA_D_UCH_MAX_POW14	0	//	D段上行通道最大输入功率14
#define	PARA_D_UCH_MAX_POW15	0	//	D段上行通道最大输入功率15
#define	PARA_D_UCH_MAX_POW16	0	//	D段上行通道最大输入功率16
#define	PARA_D_DCH_POW1	0	//	D段选频通道下行功率1
#define	PARA_D_DCH_POW2	0	//	D段选频通道下行功率2
#define	PARA_D_DCH_POW3	0	//	D段选频通道下行功率3
#define	PARA_D_DCH_POW4	0	//	D段选频通道下行功率4
#define	PARA_D_DCH_POW5	0	//	D段选频通道下行功率5
#define	PARA_D_DCH_POW6	0	//	D段选频通道下行功率6
#define	PARA_D_DCH_POW7	0	//	D段选频通道下行功率7
#define	PARA_D_DCH_POW8	0	//	D段选频通道下行功率8
#define	PARA_D_DCH_POW9	0	//	D段选频通道下行功率9
#define	PARA_D_DCH_POW10	0	//	D段选频通道下行功率10
#define	PARA_D_DCH_POW11	0	//	D段选频通道下行功率11
#define	PARA_D_DCH_POW12	0	//	D段选频通道下行功率12
#define	PARA_D_DCH_POW13	0	//	D段选频通道下行功率13
#define	PARA_D_DCH_POW14	0	//	D段选频通道下行功率14
#define	PARA_D_DCH_POW15	0	//	D段选频通道下行功率15
#define	PARA_D_DCH_POW16	0	//	D段选频通道下行功率16
#define	PARA_D_UCH_POW1	0	//	D段选频通道上行功率1
#define	PARA_D_UCH_POW2	0	//	D段选频通道上行功率2
#define	PARA_D_UCH_POW3	0	//	D段选频通道上行功率3
#define	PARA_D_UCH_POW4	0	//	D段选频通道上行功率4
#define	PARA_D_UCH_POW5	0	//	D段选频通道上行功率5
#define	PARA_D_UCH_POW6	0	//	D段选频通道上行功率6
#define	PARA_D_UCH_POW7	0	//	D段选频通道上行功率7
#define	PARA_D_UCH_POW8	0	//	D段选频通道上行功率8
#define	PARA_D_UCH_POW9	0	//	D段选频通道上行功率9
#define	PARA_D_UCH_POW10	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW11	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW12	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW13	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW14	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW15	0	//	D段选频通道上行功率10
#define	PARA_D_UCH_POW16	0	//	D段选频通道上行功率10
#define	PARA_D_UDPX_IN_GAIN	0x08AB	//	D段下行输入双工器增益
#define	PARA_D_UDPX_OUT_GAIN	0x08AA	//	D段上行输出双工器增益
#define	PARA_D_DL_TOTAL_POW	0x8390	//	D段下行输入总功率
#define	PARA_D_UL_TOTAL_POW	0x831e	//	D段上行输出总功率
#define	PARA_D_REC_DPX_IG		0		//		REC的D段输入双工器增益，用来进行增益计算，只读							
#define	PARA_D_REC_DPX_OG		0		//		REC的D段输出双工器增益，用来进行增益计算，只读	
#define	PARA_REC_TO_RE_DELAY		0x889e	// REC到RE的光纤延时
#define	PARA_RE_RF_DELAY			0x889f	// RE的射频延时
#define	PARA_MAX_T14	0//0x889c	//	光口最大延时
#define	PARA_DL_DELAY_OFFSET	0//0x0768	//	下行延时偏移量
#define	PARA_UL_DELAY_OFFSET	0x0769	//	上行延时偏移量
#define	PARA_PRI_SOFT_V	0xf018	//	程序版本号（用ASCII码）
#define	PARA_PRI_HARD_V	0xf026	//	PCB版本号(用ASCII码)
#define	PARA_TD_1ST_CP_TIME		0x08a7	// TD第1转换点时间ns, 有符号数
#define	PARA_TD_2ND_CP_TIME		0x08a8	// TD第2转换点时间ns, 有符号数
#define	PARA_TD_LNA_ON_TIME		0x08ae	// LNA开启迟后DN_PA关闭的保护时间ns
#define	PARA_TD_LNA_OFF_TIME		0x08af	// LNA关闭超前DN_PA开启的保护时间ns
#define	PARA_TD_SLOT1_UPOW	0x7501	// TD时隙1上行检测功率
#define	PARA_TD_SLOT2_UPOW	0x7502	// TD时隙2上行检测功率
#define	PARA_TD_SLOT3_UPOW	0x7503	// TD时隙3上行检测功率
#define	PARA_TD_SLOT4_UPOW	0x7504	// TD时隙4上行检测功率
#define	PARA_TD_SLOT5_UPOW	0x7505	// TD时隙5上行检测功率
#define	PARA_TD_SLOT6_UPOW	0x7506	// TD时隙6上行检测功率
#define	PARA_TD_SLOT7_UPOW	0x7507	// TD时隙7上行检测功率
#define	PARA_TD_SLOT1_DPOW	0x7511	// TD时隙1下行检测功率
#define	PARA_TD_SLOT2_DPOW	0x7512	// TD时隙2下行检测功率
#define	PARA_TD_SLOT3_DPOW	0x7513	// TD时隙3下行检测功率
#define	PARA_TD_SLOT4_DPOW	0x7514	// TD时隙4下行检测功率
#define	PARA_TD_SLOT5_DPOW	0x7515	// TD时隙5下行检测功率
#define	PARA_TD_SLOT6_DPOW	0x7516	// TD时隙6下行检测功率
#define	PARA_TD_SLOT7_DPOW	0x7517	// TD时隙7下行检测功率
#define	PARA_FPS_S1 0 // 频点搜素: 范围1起始频点
#define	PARA_FPS_E1 0 // 频点搜素: 范围1结束频点
#define	PARA_FPS_S2 0 // 频点搜素: 范围2起始频点
#define	PARA_FPS_E2 0 // 频点搜素: 范围2结束频点
#define	PARA_FPS_BCCH_LK_SET	0x0923	// 频点搜索: 锁频信道号: 标准信道号, 65535-退出锁频
#define	PARA_FPS_CID_LK_SET	0x0926	// 频点搜索: 小区识别码参考值, 0-退出小区锁定功能
#define	PARA_FPS_BCCH_FC_M	0x8940	// 频点搜索: 主小区BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_CA_FC_0	0x8941	// 频点搜索: CA载波0信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_1	0x8942	// 频点搜索: CA载波1信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_2	0x8943	// 频点搜索: CA载波2信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_3	0x8944	// 频点搜索: CA载波3信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_4	0x8945	// 频点搜索: CA载波4信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_5	0x8946	// 频点搜索: CA载波5信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_6	0x8947	// 频点搜索: CA载波6信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_7	0x8948	// 频点搜索: CA载波7信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_8	0x8949	// 频点搜索: CA载波8信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_9	0x894A	// 频点搜索: CA载波9信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_10	0x894B	// 频点搜索: CA载波10信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_11	0x894C	// 频点搜索: CA载波11信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_12	0x894D	// 频点搜索: CA载波12信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_13	0x894E	// 频点搜索: CA载波13信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_14	0x894F	// 频点搜索: CA载波14信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_CA_FC_15	0x8950	// 频点搜索: CA载波15信道号, 标准信道号, 65535-无CA
#define	PARA_FPS_BCCH_FC_1	0x8951	// 频点搜索: 邻小区1 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_2	0x8952	// 频点搜索: 邻小区2 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_3	0x8953	// 频点搜索: 邻小区3 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_4	0x8954	// 频点搜索: 邻小区4 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_5	0x8955	// 频点搜索: 邻小区5 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_BCCH_FC_6	0x8956	// 频点搜索: 邻小区6 BCCH信道号, 标准信道号, 65535-无BCCH
#define	PARA_FPS_AREA_ID	0x8958	// 频点搜索: 位置区编码
#define	PARA_FPS_CID		0x895A	// 频点搜索: 小区识别码实时值
#define	PARA_FPS_CID_1 0 // 频点搜索: 邻小区1 CID小区识别码
#define	PARA_FPS_CID_2 0 // 频点搜索: 邻小区2 CID小区识别码
#define	PARA_FPS_CID_3 0 // 频点搜索: 邻小区3 CID小区识别码
#define	PARA_FPS_CID_4 0 // 频点搜索: 邻小区4 CID小区识别码
#define	PARA_FPS_CID_5 0 // 频点搜索: 邻小区5 CID小区识别码
#define	PARA_FPS_CID_6 0 // 频点搜索: 邻小区6 CID小区识别码
#define	PARA_A_EXPA_IDRAIN_SET	0	// 微功放: 漏极电流设置,mA
#define	PARA_TD_SLOT1_DPOW_OVER_THR				0x0a60       //td下行输入导频过功率门限
#define	PARA_TD_SLOT1_DPOW_OWE_THR				0x0a61      //td下行输入导频欠功率门限	
#define PARA_A_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //下行输入过功率门限
#define PARA_A_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //下行输入欠功率门限
#define PARA_B_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //下行输入过功率门限
#define PARA_B_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //下行输入欠功率门限
#define PARA_C_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //下行输入过功率门限
#define PARA_C_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //下行输入欠功率门限
#define PARA_D_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //下行输入过功率门限
#define PARA_D_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //下行输入欠功率门限
#define PARA_REE_A_DL_OUT_TOTAL_POW_DETECT     	0x8004      //A段RE下行输出总功率//注REC\RE使用 MADD_A_DL_TOTAL_POW
#define PARA_A_RE_LOCAL_ST_ALARM     			0x8a33      	//覆盖单元本地告警状态
#define PARA_REE_B_DL_OUT_TOTAL_POW_DETECT     	0x8004      //B段RE下行输出总功率 //注REC\RE使用 MADD_B_DL_TOTAL_POW
#define PARA_B_RE_LOCAL_ST_ALARM     			0x8a33      	//覆盖单元本地告警状态
#define PARA_REE_C_DL_OUT_TOTAL_POW_DETECT     	0x8004      //A段RE下行输出总功率//注REC\RE使用 MADD_C_DL_TOTAL_POW
#define PARA_C_RE_LOCAL_ST_ALARM     			0x8a33      	//覆盖单元本地告警状态
#define PARA_REE_D_DL_OUT_TOTAL_POW_DETECT     	0x8004      //	D段RE下行输出总功率 //注REC\RE使用 MADD_D_DL_TOTAL_POW
#define PARA_D_RE_LOCAL_ST_ALARM     			0x8a33      	//	D覆盖单元本地告警状态
#define PARA_C_TD_1ST_CP_TIME	0x08a7	//		//465		TD第1转换点时间,ns,		
#define PARA_C_TD_2ND_CP_TIME	0x08a8	//		//466		TD第2转换点时间,ns,		
#define PARA_C_TD_LNA_ON_TIME	0x08ae	//		//467		LNA开启迟后DN_PA关闭的保护时间ns		
#define PARA_C_TD_LNA_OFF_TIME	0x08af	//		//468		LNA关闭超前DN_PA开启的保护时间ns		
#define PARA_C_TD_SLOT1_DPOW_OVER_THR	0x0a60	//		//469	0	//		//5625
#define PARA_C_TD_SLOT1_DPOW_OWE_THR	0x0a61	//		//470	0	//		//5626
#define PARA_D_TD_1ST_CP_TIME	0x08a7	//		//471		TD第1转换点时间,ns,		
#define PARA_D_TD_2ND_CP_TIME	0x08a7	//		//472		TD第2转换点时间,ns,		
#define PARA_D_TD_LNA_ON_TIME	0x08ae	//		//473		LNA开启迟后DN_PA关闭的保护时间ns		
#define PARA_D_TD_LNA_OFF_TIME	0x08af	//		//474		LNA关闭超前DN_PA开启的保护时间ns		
#define PARA_D_TD_SLOT1_DPOW_OVER_THR	0x0a60	//		//475	0	//		//5625
#define PARA_D_TD_SLOT1_DPOW_OWE_THR	0x0a61	//		//476	0	//		//5626
#define PARA_C_TD_SLOT1_POW	0x7511	//		//477		TD时隙1输入检测功率	
#define PARA_C_TD_SLOT2_POW	0	//		//478		TD时隙2输入检测功率	
#define PARA_C_TD_SLOT3_POW	0	//		//479		TD时隙3输入检测功率	
#define PARA_C_TD_SLOT4_POW	0	//		//480		TD时隙4输入检测功率	
#define PARA_C_TD_SLOT5_POW	0	//		//481		TD时隙5输入检测功率	
#define PARA_C_TD_SLOT6_POW	0	//		//482		TD时隙6输入检测功率	
#define PARA_C_TD_SLOT7_POW	0	//		//483		TD时隙7输入检测功率	
#define PARA_C_TD_SLOT8_POW	0	//		//484		TD时隙8输入检测功率	
#define PARA_C_TD_SLOT9_POW	0	//		//485		TD时隙9输入检测功率	
#define PARA_C_TD_SLOT10_POW	0	//		//486		TD时隙10输入检测功率	
#define PARA_C_TD_SLOT11_POW	0	//		//487		TD时隙11输入检测功率	
#define PARA_C_TD_SLOT12_POW	0	//		//488		TD时隙12输入检测功率	
#define PARA_C_TD_SLOT13_POW	0	//		//489		TD时隙13输入检测功率	
#define PARA_C_TD_SLOT14_POW	0	//		//490		TD时隙14输入检测功率	
#define PARA_C_TD_SLOT15_POW	0	//		//491		TD时隙15输入检测功率	
#define PARA_C_TD_SLOT16_POW	0	//		//492		TD时隙16输入检测功率	
#define PARA_C_TD_SLOT17_POW	0	//		//493		TD时隙17输入检测功率
#define PARA_C_TD_SLOT18_POW	0	//		//494		TD时隙18输入检测功率
#define PARA_C_TD_SLOT19_POW	0	//		//495		TD时隙19输入检测功率
#define PARA_C_TD_SLOT20_POW	0	//		//496		TD时隙20输入检测功率
#define PARA_D_TD_SLOT1_POW	0x7511	//		//497		TD时隙1输入检测功率
#define PARA_D_TD_SLOT2_POW	0	//		//498		TD时隙2输入检测功率
#define PARA_D_TD_SLOT3_POW	0	//		//499		TD时隙3输入检测功率
#define PARA_D_TD_SLOT4_POW	0	//		//500		TD时隙4输入检测功率
#define PARA_D_TD_SLOT5_POW	0	//		//501		TD时隙5输入检测功率
#define PARA_D_TD_SLOT6_POW	0	//		//502		TD时隙6输入检测功率
#define PARA_D_TD_SLOT7_POW	0	//		//503		TD时隙7输入检测功率
#define PARA_D_TD_SLOT8_POW	0	//		//504		TD时隙8输入检测功率
#define PARA_D_TD_SLOT9_POW	0	//		//505		TD时隙9输入检测功率
#define PARA_D_TD_SLOT10_POW	0	//		//506		TD时隙10输入检测功率
#define PARA_D_TD_SLOT11_POW	0	//		//507		TD时隙11输入检测功率
#define PARA_D_TD_SLOT12_POW	0	//		//508		TD时隙12输入检测功率
#define PARA_D_TD_SLOT13_POW	0	//		//509		TD时隙13输入检测功率
#define PARA_D_TD_SLOT14_POW	0	//		//510		TD时隙14输入检测功率
#define PARA_D_TD_SLOT15_POW	0	//		//511		TD时隙15输入检测功率
#define PARA_D_TD_SLOT16_POW	0	//		//512		TD时隙16输入检测功率
#define PARA_D_TD_SLOT17_POW	0	//		//513		TD时隙17输入检测功率
#define PARA_D_TD_SLOT18_POW	0	//		//514		TD时隙18输入检测功率
#define PARA_D_TD_SLOT19_POW	0	//		//515		TD时隙19输入检测功率
#define PARA_D_TD_SLOT20_POW	0	//		//516		TD时隙20输入检测功率
#define	PARA_DL_DELAY_OFFSET_B		0//0x889c		//		下行延时偏移量		
#define	PARA_DL_DELAY_OFFSET_C		0//0x889c		//		下行延时偏移量		
#define	PARA_DL_DELAY_OFFSET_D		0//0x889c		//		下行延时偏移量		
#define	PARA_VGS_A		            0		//	         A段栅压		
#define	PARA_VGS_B          		0		//		 B段栅压		
#define	PARA_VGS_C          		0		//		 C段栅压
#define	PARA_VGS_D          		0		//		 D段栅压
#define	PARA_VGS_COMP_A		        0		//	     A段栅压补偿		
#define	PARA_VGS_COMP_B             0		//		 B段栅压补偿			
#define	PARA_VGS_COMP_C             0		//		 C段栅压补偿	
#define	PARA_VGS_COMP_D          	0		//		 C段栅压补偿	
#define	PARA_ATT_DATA_COMP_A		0				//ATT补偿数据
#define	PARA_ATT_DATA_COMP_B		0				//ATT补偿数据
#define	PARA_ATT_DATA_COMP_C		0				//ATT补偿数据
#define	PARA_ATT_DATA_COMP_D		0				//ATT补偿数据
#define	PARA_MAX_T14_A	0x889c	//	光口最大延时
#define	PARA_MAX_T14_B	0x889c	//	光口最大延时
#define	PARA_MAX_T14_C	0x889c	//	光口最大延时
#define	PARA_MAX_T14_D	0x889c	//	光口最大延时
#define PARA_ERL_JG_A		0// A段话务量统计结果
#define PARA_ERL_JG_B		0
#define PARA_ERL_JG_C		0
#define PARA_ERL_JG_D		0
#define	PARA_MOVE_CENTER_FRE_D		0//改变下行中心频率
#define	PARA_MOVE_CENTER_FRE_U		0//改变上行中心频率

#endif

// 访问地址>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 2B
#define	MADD_A_DL_CHANNEL1		0		//		A段下行信道号1		
#define	MADD_A_DL_CHANNEL2		1		//		A段下行信道号2		
#define	MADD_A_DL_CHANNEL3		2		//		A段下行信道号3		
#define	MADD_A_DL_CHANNEL4		3		//		A段下行信道号4		
#define	MADD_A_DL_CHANNEL5		4		//		A段下行信道号5		
#define	MADD_A_DL_CHANNEL6		5		//		A段下行信道号6		
#define	MADD_A_DL_CHANNEL7		6		//		A段下行信道号7		
#define	MADD_A_DL_CHANNEL8		7		//		A段下行信道号8		
#define	MADD_A_DL_CHANNEL9		8		//		A段下行信道号9		
#define	MADD_A_DL_CHANNEL10		9		//		A段下行信道号10		
#define	MADD_A_DL_CHANNEL11		10		//		A段下行信道号11		
#define	MADD_A_DL_CHANNEL12		11		//		A段下行信道号12		
#define	MADD_A_DL_CHANNEL13		12		//		A段下行信道号13		
#define	MADD_A_DL_CHANNEL14		13		//		A段下行信道号14		
#define	MADD_A_DL_CHANNEL15		14		//		A段下行信道号15		
#define	MADD_A_DL_CHANNEL16		15		//		A段下行信道号16		
#define	MADD_A_UL_CHANNEL1		16		//		A段上行信道号1		
#define	MADD_A_UL_CHANNEL2		17		//		A段上行信道号2		
#define	MADD_A_UL_CHANNEL3		18		//		A段上行信道号3		
#define	MADD_A_UL_CHANNEL4		19		//		A段上行信道号4		
#define	MADD_A_UL_CHANNEL5		20		//		A段上行信道号5		
#define	MADD_A_UL_CHANNEL6		21		//		A段上行信道号6		
#define	MADD_A_UL_CHANNEL7		22		//		A段上行信道号7		
#define	MADD_A_UL_CHANNEL8		23		//		A段上行信道号8		
#define	MADD_A_UL_CHANNEL9		24		//		A段上行信道号9		
#define	MADD_A_UL_CHANNEL10		25		//		A段上行信道号10		
#define	MADD_A_UL_CHANNEL11		26		//		A段上行信道号11		
#define	MADD_A_UL_CHANNEL12		27		//		A段上行信道号12		
#define	MADD_A_UL_CHANNEL13		28		//		A段上行信道号13		
#define	MADD_A_UL_CHANNEL14		29		//		A段上行信道号14		
#define	MADD_A_UL_CHANNEL15		30		//		A段上行信道号15		
#define	MADD_A_UL_CHANNEL16		31		//		A段上行信道号16		
#define	MADD_A_DCH_MAX_POW1		32		//		A段下行通道最大输出功率1		
#define	MADD_A_DCH_MAX_POW2		33		//		A段下行通道最大输出功率2		
#define	MADD_A_DCH_MAX_POW3		34		//		A段下行通道最大输出功率3		
#define	MADD_A_DCH_MAX_POW4		35		//		A段下行通道最大输出功率4		
#define	MADD_A_DCH_MAX_POW5		36		//		A段下行通道最大输出功率5		
#define	MADD_A_DCH_MAX_POW6		37		//		A段下行通道最大输出功率6		
#define	MADD_A_DCH_MAX_POW7		38		//		A段下行通道最大输出功率7		
#define	MADD_A_DCH_MAX_POW8		39		//		A段下行通道最大输出功率8		
#define	MADD_A_DCH_MAX_POW9		40		//		A段下行通道最大输出功率9		
#define	MADD_A_DCH_MAX_POW10		41		//		A段下行通道最大输出功率10		
#define	MADD_A_DCH_MAX_POW11		42		//		A段下行通道最大输出功率11		
#define	MADD_A_DCH_MAX_POW12		43		//		A段下行通道最大输出功率12		
#define	MADD_A_DCH_MAX_POW13		44		//		A段下行通道最大输出功率13		
#define	MADD_A_DCH_MAX_POW14		45		//		A段下行通道最大输出功率14		
#define	MADD_A_DCH_MAX_POW15		46		//		A段下行通道最大输出功率15		
#define	MADD_A_DCH_MAX_POW16		47		//		A段下行通道最大输出功率16		
#define	MADD_A_UCH_MAX_POW1		48		//		A段上行通道最大输入功率1		
#define	MADD_A_UCH_MAX_POW2		49		//		A段上行通道最大输入功率2		
#define	MADD_A_UCH_MAX_POW3		50		//		A段上行通道最大输入功率3		
#define	MADD_A_UCH_MAX_POW4		51		//		A段上行通道最大输入功率4		
#define	MADD_A_UCH_MAX_POW5		52		//		A段上行通道最大输入功率5		
#define	MADD_A_UCH_MAX_POW6		53		//		A段上行通道最大输入功率6		
#define	MADD_A_UCH_MAX_POW7		54		//		A段上行通道最大输入功率7		
#define	MADD_A_UCH_MAX_POW8		55		//		A段上行通道最大输入功率8		
#define	MADD_A_UCH_MAX_POW9		56		//		A段上行通道最大输入功率9		
#define	MADD_A_UCH_MAX_POW10		57		//		A段上行通道最大输入功率10		
#define	MADD_A_UCH_MAX_POW11		58		//		A段上行通道最大输入功率11		
#define	MADD_A_UCH_MAX_POW12		59		//		A段上行通道最大输入功率12		
#define	MADD_A_UCH_MAX_POW13		60		//		A段上行通道最大输入功率13		
#define	MADD_A_UCH_MAX_POW14		61		//		A段上行通道最大输入功率14		
#define	MADD_A_UCH_MAX_POW15		62		//		A段上行通道最大输入功率15		
#define	MADD_A_UCH_MAX_POW16		63		//		A段上行通道最大输入功率16		
#define	MADD_A_DCH_POW1		64		//		A段选频通道下行功率1		
#define	MADD_A_DCH_POW2		65		//		A段选频通道下行功率2		
#define	MADD_A_DCH_POW3		66		//		A段选频通道下行功率3		
#define	MADD_A_DCH_POW4		67		//		A段选频通道下行功率4		
#define	MADD_A_DCH_POW5		68		//		A段选频通道下行功率5		
#define	MADD_A_DCH_POW6		69		//		A段选频通道下行功率6		
#define	MADD_A_DCH_POW7		70		//		A段选频通道下行功率7		
#define	MADD_A_DCH_POW8		71		//		A段选频通道下行功率8		
#define	MADD_A_DCH_POW9		72		//		A段选频通道下行功率9		
#define	MADD_A_DCH_POW10		73		//		A段选频通道下行功率10		
#define	MADD_A_DCH_POW11		74		//		A段选频通道下行功率11		
#define	MADD_A_DCH_POW12		75		//		A段选频通道下行功率12		
#define	MADD_A_DCH_POW13		76		//		A段选频通道下行功率13		
#define	MADD_A_DCH_POW14		77		//		A段选频通道下行功率14		
#define	MADD_A_DCH_POW15		78		//		A段选频通道下行功率15		
#define	MADD_A_DCH_POW16		79		//		A段选频通道下行功率16		
#define	MADD_A_UCH_POW1		80		//		A段选频通道上行功率1		
#define	MADD_A_UCH_POW2		81		//		A段选频通道上行功率2		
#define	MADD_A_UCH_POW3		82		//		A段选频通道上行功率3		
#define	MADD_A_UCH_POW4		83		//		A段选频通道上行功率4		
#define	MADD_A_UCH_POW5		84		//		A段选频通道上行功率5		
#define	MADD_A_UCH_POW6		85		//		A段选频通道上行功率6		
#define	MADD_A_UCH_POW7		86		//		A段选频通道上行功率7		
#define	MADD_A_UCH_POW8		87		//		A段选频通道上行功率8		
#define	MADD_A_UCH_POW9		88		//		A段选频通道上行功率9		
#define	MADD_A_UCH_POW10		89		//		A段选频通道上行功率10		
#define	MADD_A_UCH_POW11		90		//		A段选频通道上行功率11		
#define	MADD_A_UCH_POW12		91		//		A段选频通道上行功率12		
#define	MADD_A_UCH_POW13		92		//		A段选频通道上行功率13		
#define	MADD_A_UCH_POW14		93		//		A段选频通道上行功率14		
#define	MADD_A_UCH_POW15		94		//		A段选频通道上行功率15		
#define	MADD_A_UCH_POW16		95		//		A段选频通道上行功率16		
#define	MADD_A_UDPX_IN_GAIN		96		//		A段输入双工器衰减,		
#define	MADD_A_UDPX_OUT_GAIN		97		//		A段输出双工器衰减,		
#define	MADD_A_DL_TOTAL_POW		98		//		A段下行输出总功率，x10算法保留一位小数		
#define	MADD_A_UL_TOTAL_POW		99		//		A段上行输入总功率，x10算法保留一位小数		
#define	MADD_A_REC_DPX_IG		100		//		REC的A段输入双工器衰减，用来进行增益计算，只读,		
#define	MADD_A_REC_DPX_OG		101		//		REC的A段输出双工器衰减，用来进行增益计算，只读,		
#define	MADD_B_DL_CHANNEL1		102		//		B段下行信道号1		
#define	MADD_B_DL_CHANNEL2		103		//		B段下行信道号2		
#define	MADD_B_DL_CHANNEL3		104		//		B段下行信道号3		
#define	MADD_B_DL_CHANNEL4		105		//		B段下行信道号4		
#define	MADD_B_DL_CHANNEL5		106		//		B段下行信道号5		
#define	MADD_B_DL_CHANNEL6		107		//		B段下行信道号6		
#define	MADD_B_DL_CHANNEL7		108		//		B段下行信道号7		
#define	MADD_B_DL_CHANNEL8		109		//		B段下行信道号8		
#define	MADD_B_DL_CHANNEL9		110		//		B段下行信道号9		
#define	MADD_B_DL_CHANNEL10		111		//		B段下行信道号10		
#define	MADD_B_DL_CHANNEL11		112		//		B段下行信道号11		
#define	MADD_B_DL_CHANNEL12		113		//		B段下行信道号12		
#define	MADD_B_DL_CHANNEL13		114		//		B段下行信道号13		
#define	MADD_B_DL_CHANNEL14		115		//		B段下行信道号14		
#define	MADD_B_DL_CHANNEL15		116		//		B段下行信道号15		
#define	MADD_B_DL_CHANNEL16		117		//		B段下行信道号16		
#define	MADD_B_UL_CHANNEL1		118		//		B段上行信道号1		
#define	MADD_B_UL_CHANNEL2		119		//		B段上行信道号2		
#define	MADD_B_UL_CHANNEL3		120		//		B段上行信道号3		
#define	MADD_B_UL_CHANNEL4		121		//		B段上行信道号4		
#define	MADD_B_UL_CHANNEL5		122		//		B段上行信道号5		
#define	MADD_B_UL_CHANNEL6		123		//		B段上行信道号6		
#define	MADD_B_UL_CHANNEL7		124		//		B段上行信道号7		
#define	MADD_B_UL_CHANNEL8		125		//		B段上行信道号8		
#define	MADD_B_UL_CHANNEL9		126		//		B段上行信道号9		
#define	MADD_B_UL_CHANNEL10		127		//		B段上行信道号10		
#define	MADD_B_UL_CHANNEL11		128		//		B段上行信道号11		
#define	MADD_B_UL_CHANNEL12		129		//		B段上行信道号12		
#define	MADD_B_UL_CHANNEL13		130		//		B段上行信道号13		
#define	MADD_B_UL_CHANNEL14		131		//		B段上行信道号14		
#define	MADD_B_UL_CHANNEL15		132		//		B段上行信道号15		
#define	MADD_B_UL_CHANNEL16		133		//		B段上行信道号16		
#define	MADD_B_DCH_MAX_POW1		134		//		B段下行通道最大输出功率1		
#define	MADD_B_DCH_MAX_POW2		135		//		B段下行通道最大输出功率2		
#define	MADD_B_DCH_MAX_POW3		136		//		B段下行通道最大输出功率3		
#define	MADD_B_DCH_MAX_POW4		137		//		B段下行通道最大输出功率4		
#define	MADD_B_DCH_MAX_POW5		138		//		B段下行通道最大输出功率5		
#define	MADD_B_DCH_MAX_POW6		139		//		B段下行通道最大输出功率6		
#define	MADD_B_DCH_MAX_POW7		140		//		B段下行通道最大输出功率7		
#define	MADD_B_DCH_MAX_POW8		141		//		B段下行通道最大输出功率8		
#define	MADD_B_DCH_MAX_POW9		142		//		B段下行通道最大输出功率9		
#define	MADD_B_DCH_MAX_POW10		143		//		B段下行通道最大输出功率10		
#define	MADD_B_DCH_MAX_POW11		144		//		B段下行通道最大输出功率11		
#define	MADD_B_DCH_MAX_POW12		145		//		B段下行通道最大输出功率12		
#define	MADD_B_DCH_MAX_POW13		146		//		B段下行通道最大输出功率13		
#define	MADD_B_DCH_MAX_POW14		147		//		B段下行通道最大输出功率14		
#define	MADD_B_DCH_MAX_POW15		148		//		B段下行通道最大输出功率15		
#define	MADD_B_DCH_MAX_POW16		149		//		B段下行通道最大输出功率16		
#define	MADD_B_UCH_MAX_POW1		150		//		B段上行通道最大输入功率1		
#define	MADD_B_UCH_MAX_POW2		151		//		B段上行通道最大输入功率2		
#define	MADD_B_UCH_MAX_POW3		152		//		B段上行通道最大输入功率3		
#define	MADD_B_UCH_MAX_POW4		153		//		B段上行通道最大输入功率4		
#define	MADD_B_UCH_MAX_POW5		154		//		B段上行通道最大输入功率5		
#define	MADD_B_UCH_MAX_POW6		155		//		B段上行通道最大输入功率6		
#define	MADD_B_UCH_MAX_POW7		156		//		B段上行通道最大输入功率7		
#define	MADD_B_UCH_MAX_POW8		157		//		B段上行通道最大输入功率8		
#define	MADD_B_UCH_MAX_POW9		158		//		B段上行通道最大输入功率9		
#define	MADD_B_UCH_MAX_POW10		159		//		B段上行通道最大输入功率10		
#define	MADD_B_UCH_MAX_POW11		160		//		B段上行通道最大输入功率11		
#define	MADD_B_UCH_MAX_POW12		161		//		B段上行通道最大输入功率12		
#define	MADD_B_UCH_MAX_POW13		162		//		B段上行通道最大输入功率13		
#define	MADD_B_UCH_MAX_POW14		163		//		B段上行通道最大输入功率14		
#define	MADD_B_UCH_MAX_POW15		164		//		B段上行通道最大输入功率15		
#define	MADD_B_UCH_MAX_POW16		165		//		B段上行通道最大输入功率16		
#define	MADD_B_DCH_POW1		166		//		B段选频通道下行功率1		
#define	MADD_B_DCH_POW2		167		//		B段选频通道下行功率2		
#define	MADD_B_DCH_POW3		168		//		B段选频通道下行功率3		
#define	MADD_B_DCH_POW4		169		//		B段选频通道下行功率4		
#define	MADD_B_DCH_POW5		170		//		B段选频通道下行功率5		
#define	MADD_B_DCH_POW6		171		//		B段选频通道下行功率6		
#define	MADD_B_DCH_POW7		172		//		B段选频通道下行功率7		
#define	MADD_B_DCH_POW8		173		//		B段选频通道下行功率8		
#define	MADD_B_DCH_POW9		174		//		B段选频通道下行功率9		
#define	MADD_B_DCH_POW10		175		//		B段选频通道下行功率10		
#define	MADD_B_DCH_POW11		176		//		B段选频通道下行功率11		
#define	MADD_B_DCH_POW12		177		//		B段选频通道下行功率12		
#define	MADD_B_DCH_POW13		178		//		B段选频通道下行功率13		
#define	MADD_B_DCH_POW14		179		//		B段选频通道下行功率14		
#define	MADD_B_DCH_POW15		180		//		B段选频通道下行功率15		
#define	MADD_B_DCH_POW16		181		//		B段选频通道下行功率16		
#define	MADD_B_UCH_POW1		182		//		B段选频通道上行功率1		
#define	MADD_B_UCH_POW2		183		//		B段选频通道上行功率2		
#define	MADD_B_UCH_POW3		184		//		B段选频通道上行功率3		
#define	MADD_B_UCH_POW4		185		//		B段选频通道上行功率4		
#define	MADD_B_UCH_POW5		186		//		B段选频通道上行功率5		
#define	MADD_B_UCH_POW6		187		//		B段选频通道上行功率6		
#define	MADD_B_UCH_POW7		188		//		B段选频通道上行功率7		
#define	MADD_B_UCH_POW8		189		//		B段选频通道上行功率8		
#define	MADD_B_UCH_POW9		190		//		B段选频通道上行功率9		
#define	MADD_B_UCH_POW10		191		//		B段选频通道上行功率10		
#define	MADD_B_UCH_POW11		192		//		B段选频通道上行功率11		
#define	MADD_B_UCH_POW12		193		//		B段选频通道上行功率12		
#define	MADD_B_UCH_POW13		194		//		B段选频通道上行功率13		
#define	MADD_B_UCH_POW14		195		//		B段选频通道上行功率14		
#define	MADD_B_UCH_POW15		196		//		B段选频通道上行功率15		
#define	MADD_B_UCH_POW16		197		//		B段选频通道上行功率16		
#define	MADD_B_UDPX_IN_GAIN		198		//		B段输入双工器衰减,		
#define	MADD_B_UDPX_OUT_GAIN		199		//		B段输出双工器衰减,		
#define	MADD_B_DL_TOTAL_POW		200		//		B段下行输出总功率		
#define	MADD_B_UL_TOTAL_POW		201		//		B段上行输入总功率，x10算法保留一位小数		
#define	MADD_B_REC_DPX_IG		202		//		REC的B段输入双工器衰减，用来进行增益计算，只读,		
#define	MADD_B_REC_DPX_OG		203		//		REC的B段输出双工器衰减，用来进行增益计算，只读,		
#define	MADD_C_DL_CHANNEL1		204		//		C段下行信道号1		
#define	MADD_C_DL_CHANNEL2		205		//		C段下行信道号2		
#define	MADD_C_DL_CHANNEL3		206		//		C段下行信道号3		
#define	MADD_C_DL_CHANNEL4		207		//		C段下行信道号4		
#define	MADD_C_DL_CHANNEL5		208		//		C段下行信道号5		
#define	MADD_C_DL_CHANNEL6		209		//		C段下行信道号6		
#define	MADD_C_DL_CHANNEL7		210		//		C段下行信道号7		
#define	MADD_C_DL_CHANNEL8		211		//		C段下行信道号8		
#define	MADD_C_DL_CHANNEL9		212		//		C段下行信道号9		
#define	MADD_C_DL_CHANNEL10		213		//		C段下行信道号10		
#define	MADD_C_UL_CHANNEL1		214		//		C段上行信道号1		
#define	MADD_C_UL_CHANNEL2		215		//		C段上行信道号2		
#define	MADD_C_UL_CHANNEL3		216		//		C段上行信道号3		
#define	MADD_C_UL_CHANNEL4		217		//		C段上行信道号4		
#define	MADD_C_UL_CHANNEL5		218		//		C段上行信道号5		
#define	MADD_C_UL_CHANNEL6		219		//		C段上行信道号6		
#define	MADD_C_UL_CHANNEL7		220		//		C段上行信道号7		
#define	MADD_C_UL_CHANNEL8		221		//		C段上行信道号8		
#define	MADD_C_UL_CHANNEL9		222		//		C段上行信道号9		
#define	MADD_C_UL_CHANNEL10		223		//		C段上行信道号10		
#define	MADD_C_DCH_MAX_POW1		224		//		C段下行通道最大输出功率1		
#define	MADD_C_DCH_MAX_POW2		225		//		C段下行通道最大输出功率2		
#define	MADD_C_DCH_MAX_POW3		226		//		C段下行通道最大输出功率3		
#define	MADD_C_DCH_MAX_POW4		227		//		C段下行通道最大输出功率4		
#define	MADD_C_DCH_MAX_POW5		228		//		C段下行通道最大输出功率5		
#define	MADD_C_DCH_MAX_POW6		229		//		C段下行通道最大输出功率6		
#define	MADD_C_DCH_MAX_POW7		230		//		C段下行通道最大输出功率7		
#define	MADD_C_DCH_MAX_POW8		231		//		C段下行通道最大输出功率8		
#define	MADD_C_DCH_MAX_POW9		232		//		C段下行通道最大输出功率9		
#define	MADD_C_DCH_MAX_POW10		233		//		C段下行通道最大输出功率10		
#define	MADD_C_DCH_MAX_POW11		234		//		C段下行通道最大输出功率11		
#define	MADD_C_DCH_MAX_POW12		235		//		C段下行通道最大输出功率12		
#define	MADD_C_DCH_MAX_POW13		236		//		C段下行通道最大输出功率13		
#define	MADD_C_DCH_MAX_POW14		237		//		C段下行通道最大输出功率14		
#define	MADD_C_DCH_MAX_POW15		238		//		C段下行通道最大输出功率15		
#define	MADD_C_DCH_MAX_POW16		239		//		C段下行通道最大输出功率16		
#define	MADD_C_UCH_MAX_POW1		240		//		C段上行通道最大输入功率1		
#define	MADD_C_UCH_MAX_POW2		241		//		C段上行通道最大输入功率2		
#define	MADD_C_UCH_MAX_POW3		242		//		C段上行通道最大输入功率3		
#define	MADD_C_UCH_MAX_POW4		243		//		C段上行通道最大输入功率4		
#define	MADD_C_UCH_MAX_POW5		244		//		C段上行通道最大输入功率5		
#define	MADD_C_UCH_MAX_POW6		245		//		C段上行通道最大输入功率6		
#define	MADD_C_UCH_MAX_POW7		246		//		C段上行通道最大输入功率7		
#define	MADD_C_UCH_MAX_POW8		247		//		C段上行通道最大输入功率8		
#define	MADD_C_UCH_MAX_POW9		248		//		C段上行通道最大输入功率9		
#define	MADD_C_UCH_MAX_POW10		249		//		C段上行通道最大输入功率10		
#define	MADD_C_UCH_MAX_POW11		250		//		C段上行通道最大输入功率11		
#define	MADD_C_UCH_MAX_POW12		251		//		C段上行通道最大输入功率12		
#define	MADD_C_UCH_MAX_POW13		252		//		C段上行通道最大输入功率13		
#define	MADD_C_UCH_MAX_POW14		253		//		C段上行通道最大输入功率14		
#define	MADD_C_UCH_MAX_POW15		254		//		C段上行通道最大输入功率15		
#define	MADD_C_UCH_MAX_POW16		255		//		C段上行通道最大输入功率16		
#define	MADD_C_DCH_POW1		256		//		C段选频通道下行功率1		
#define	MADD_C_DCH_POW2		257		//		C段选频通道下行功率2		
#define	MADD_C_DCH_POW3		258		//		C段选频通道下行功率3		
#define	MADD_C_DCH_POW4		259		//		C段选频通道下行功率4		
#define	MADD_C_DCH_POW5		260		//		C段选频通道下行功率5		
#define	MADD_C_DCH_POW6		261		//		C段选频通道下行功率6		
#define	MADD_C_DCH_POW7		262		//		C段选频通道下行功率7		
#define	MADD_C_DCH_POW8		263		//		C段选频通道下行功率8		
#define	MADD_C_DCH_POW9		264		//		C段选频通道下行功率9		
#define	MADD_C_DCH_POW10		265		//		C段选频通道下行功率10		
#define	MADD_C_DCH_POW11		266		//		C段选频通道下行功率11		
#define	MADD_C_DCH_POW12		267		//		C段选频通道下行功率12		
#define	MADD_C_DCH_POW13		268		//		C段选频通道下行功率13		
#define	MADD_C_DCH_POW14		269		//		C段选频通道下行功率14		
#define	MADD_C_DCH_POW15		270		//		C段选频通道下行功率15		
#define	MADD_C_DCH_POW16		271		//		C段选频通道下行功率16		
#define	MADD_C_UCH_POW1		272		//		C段选频通道上行功率1		
#define	MADD_C_UCH_POW2		273		//		C段选频通道上行功率2		
#define	MADD_C_UCH_POW3		274		//		C段选频通道上行功率3		
#define	MADD_C_UCH_POW4		275		//		C段选频通道上行功率4		
#define	MADD_C_UCH_POW5		276		//		C段选频通道上行功率5		
#define	MADD_C_UCH_POW6		277		//		C段选频通道上行功率6		
#define	MADD_C_UCH_POW7		278		//		C段选频通道上行功率7		
#define	MADD_C_UCH_POW8		279		//		C段选频通道上行功率8		
#define	MADD_C_UCH_POW9		280		//		C段选频通道上行功率9		
#define	MADD_C_UCH_POW10		281		//		C段选频通道上行功率10		
#define	MADD_C_UCH_POW11		282		//		C段选频通道上行功率11		
#define	MADD_C_UCH_POW12		283		//		C段选频通道上行功率12		
#define	MADD_C_UCH_POW13		284		//		C段选频通道上行功率13		
#define	MADD_C_UCH_POW14		285		//		C段选频通道上行功率14		
#define	MADD_C_UCH_POW15		286		//		C段选频通道上行功率15		
#define	MADD_C_UCH_POW16		287		//		C段选频通道上行功率16		
#define	MADD_C_UDPX_IN_GAIN		288		//		C段输入双工器衰减,		
#define	MADD_C_UDPX_OUT_GAIN		289		//		C段输出双工器衰减,		
#define	MADD_C_DL_TOTAL_POW		290		//		C段下行输出总功率，x10算法保留一位小数		
#define	MADD_C_UL_TOTAL_POW		291		//		C段上行输入总功率，x10算法保留一位小数		
#define	MADD_C_REC_DPX_IG		292		//		REC的C段输入双工器衰减，用来进行增益计算，只读,		
#define	MADD_C_REC_DPX_OG		293		//		REC的C段输出双工器衰减，用来进行增益计算，只读,		
#define	MADD_D_DL_CHANNEL1		294		//		D段下行信道号1		
#define	MADD_D_DL_CHANNEL2		295		//		D段下行信道号2		
#define	MADD_D_DL_CHANNEL3		296		//		D段下行信道号3		
#define	MADD_D_DL_CHANNEL4		297		//		D段下行信道号4		
#define	MADD_D_DL_CHANNEL5		298		//		D段下行信道号5		
#define	MADD_D_DL_CHANNEL6		299		//		D段下行信道号6		
#define	MADD_D_DL_CHANNEL7		300		//		D段下行信道号7		
#define	MADD_D_DL_CHANNEL8		301		//		D段下行信道号8		
#define	MADD_D_DL_CHANNEL9		302		//		D段下行信道号9		
#define	MADD_D_DL_CHANNEL10		303		//		D段下行信道号10		
#define	MADD_D_UL_CHANNEL1		304		//		D段上行信道号1		
#define	MADD_D_UL_CHANNEL2		305		//		D段上行信道号2		
#define	MADD_D_UL_CHANNEL3		306		//		D段上行信道号3		
#define	MADD_D_UL_CHANNEL4		307		//		D段上行信道号4		
#define	MADD_D_UL_CHANNEL5		308		//		D段上行信道号5		
#define	MADD_D_UL_CHANNEL6		309		//		D段上行信道号6		
#define	MADD_D_UL_CHANNEL7		310		//		D段上行信道号7		
#define	MADD_D_UL_CHANNEL8		311		//		D段上行信道号8		
#define	MADD_D_UL_CHANNEL9		312		//		D段上行信道号9		
#define	MADD_D_UL_CHANNEL10		313		//		D段上行信道号10		
#define	MADD_D_DCH_MAX_POW1		314		//		D段下行通道最大输出功率1		
#define	MADD_D_DCH_MAX_POW2		315		//		D段下行通道最大输出功率2		
#define	MADD_D_DCH_MAX_POW3		316		//		D段下行通道最大输出功率3		
#define	MADD_D_DCH_MAX_POW4		317		//		D段下行通道最大输出功率4		
#define	MADD_D_DCH_MAX_POW5		318		//		D段下行通道最大输出功率5		
#define	MADD_D_DCH_MAX_POW6		319		//		D段下行通道最大输出功率6		
#define	MADD_D_DCH_MAX_POW7		320		//		D段下行通道最大输出功率7		
#define	MADD_D_DCH_MAX_POW8		321		//		D段下行通道最大输出功率8		
#define	MADD_D_DCH_MAX_POW9		322		//		D段下行通道最大输出功率9		
#define	MADD_D_DCH_MAX_POW10		323		//		D段下行通道最大输出功率10		
#define	MADD_D_DCH_MAX_POW11		324		//		D段下行通道最大输出功率11		
#define	MADD_D_DCH_MAX_POW12		325		//		D段下行通道最大输出功率12		
#define	MADD_D_DCH_MAX_POW13		326		//		D段下行通道最大输出功率13		
#define	MADD_D_DCH_MAX_POW14		327		//		D段下行通道最大输出功率14		
#define	MADD_D_DCH_MAX_POW15		328		//		D段下行通道最大输出功率15		
#define	MADD_D_DCH_MAX_POW16		329		//		D段下行通道最大输出功率16		
#define	MADD_D_UCH_MAX_POW1		330		//		D段上行通道最大输入功率1		
#define	MADD_D_UCH_MAX_POW2		331		//		D段上行通道最大输入功率2		
#define	MADD_D_UCH_MAX_POW3		332		//		D段上行通道最大输入功率3		
#define	MADD_D_UCH_MAX_POW4		333		//		D段上行通道最大输入功率4		
#define	MADD_D_UCH_MAX_POW5		334		//		D段上行通道最大输入功率5		
#define	MADD_D_UCH_MAX_POW6		335		//		D段上行通道最大输入功率6		
#define	MADD_D_UCH_MAX_POW7		336		//		D段上行通道最大输入功率7		
#define	MADD_D_UCH_MAX_POW8		337		//		D段上行通道最大输入功率8		
#define	MADD_D_UCH_MAX_POW9		338		//		D段上行通道最大输入功率9		
#define	MADD_D_UCH_MAX_POW10		339		//		D段上行通道最大输入功率10		
#define	MADD_D_UCH_MAX_POW11		340		//		D段上行通道最大输入功率11		
#define	MADD_D_UCH_MAX_POW12		341		//		D段上行通道最大输入功率12		
#define	MADD_D_UCH_MAX_POW13		342		//		D段上行通道最大输入功率13		
#define	MADD_D_UCH_MAX_POW14		343		//		D段上行通道最大输入功率14		
#define	MADD_D_UCH_MAX_POW15		344		//		D段上行通道最大输入功率15		
#define	MADD_D_UCH_MAX_POW16		345		//		D段上行通道最大输入功率16		
#define	MADD_D_DCH_POW1		346		//		D段选频通道下行功率1		
#define	MADD_D_DCH_POW2		347		//		D段选频通道下行功率2		
#define	MADD_D_DCH_POW3		348		//		D段选频通道下行功率3		
#define	MADD_D_DCH_POW4		349		//		D段选频通道下行功率4		
#define	MADD_D_DCH_POW5		350		//		D段选频通道下行功率5		
#define	MADD_D_DCH_POW6		351		//		D段选频通道下行功率6		
#define	MADD_D_DCH_POW7		352		//		D段选频通道下行功率7		
#define	MADD_D_DCH_POW8		353		//		D段选频通道下行功率8		
#define	MADD_D_DCH_POW9		354		//		D段选频通道下行功率9		
#define	MADD_D_DCH_POW10		355		//		D段选频通道下行功率10		
#define	MADD_D_DCH_POW11		356		//		D段选频通道下行功率11		
#define	MADD_D_DCH_POW12		357		//		D段选频通道下行功率12		
#define	MADD_D_DCH_POW13		358		//		D段选频通道下行功率13		
#define	MADD_D_DCH_POW14		359		//		D段选频通道下行功率14		
#define	MADD_D_DCH_POW15		360		//		D段选频通道下行功率15		
#define	MADD_D_DCH_POW16		361		//		D段选频通道下行功率16		
#define	MADD_D_UCH_POW1		362		//		D段选频通道上行功率1		
#define	MADD_D_UCH_POW2		363		//		D段选频通道上行功率2		
#define	MADD_D_UCH_POW3		364		//		D段选频通道上行功率3		
#define	MADD_D_UCH_POW4		365		//		D段选频通道上行功率4		
#define	MADD_D_UCH_POW5		366		//		D段选频通道上行功率5		
#define	MADD_D_UCH_POW6		367		//		D段选频通道上行功率6		
#define	MADD_D_UCH_POW7		368		//		D段选频通道上行功率7		
#define	MADD_D_UCH_POW8		369		//		D段选频通道上行功率8		
#define	MADD_D_UCH_POW9		370		//		D段选频通道上行功率9		
#define	MADD_D_UCH_POW10		371		//		D段选频通道上行功率10		
#define	MADD_D_UCH_POW11		372		//		D段选频通道上行功率11		
#define	MADD_D_UCH_POW12		373		//		D段选频通道上行功率12		
#define	MADD_D_UCH_POW13		374		//		D段选频通道上行功率13		
#define	MADD_D_UCH_POW14		375		//		D段选频通道上行功率14		
#define	MADD_D_UCH_POW15		376		//		D段选频通道上行功率15		
#define	MADD_D_UCH_POW16		377		//		D段选频通道上行功率16		
#define	MADD_D_UDPX_IN_GAIN		378		//		D段输入双工器衰减,		
#define	MADD_D_UDPX_OUT_GAIN		379		//		D段输出双工器衰减,		
#define	MADD_D_DL_TOTAL_POW		380		//		D段下行输出总功率		
#define	MADD_D_UL_TOTAL_POW		381		//		D段上行输入总功率，x10算法保留一位小数		
#define	MADD_D_REC_DPX_IG		382		//		REC的D段输入双工器衰减，用来进行增益计算，只读,		
#define	MADD_D_REC_DPX_OG		383		//		REC的D段输出双工器衰减，用来进行增益计算，只读,		
#define	MADD_REC_TO_RE_DELAY		384		//		REC到RE的光纤延时		
#define	MADD_RE_RF_DELAY		385						
#define	MADD_MAX_T14		386		//		光口最大延时,单位10ns		
#define	MADD_DL_DELAY_OFFSET		387		//		下行延时偏移量		
#define	MADD_UL_DELAY_OFFSET		388		//		上行延时偏移量		
#define	MADD_PRI_SOFT_V		389		//		程序版本号（用ASCII码）		
#define	MADD_PRI_HARD_V		390		//		PCB版本号(用ASCII码)		
#define	MADD_TD_1ST_CP_TIME		391		//		TD第1转换点时间,ns,		
#define	MADD_TD_2ND_CP_TIME		392		//		TD第2转换点时间,ns,		
#define	MADD_TD_LNA_ON_TIME		393		//		LNA开启迟后DN_PA关闭的保护时间ns		
#define	MADD_TD_LNA_OFF_TIME		394		//		LNA关闭超前DN_PA开启的保护时间ns		
#define	MADD_TD_SLOT1_UPOW		395		//		TD时隙1上行输入检测功率		
#define	MADD_TD_SLOT2_UPOW		396		//		TD时隙2上行输入检测功率		
#define	MADD_TD_SLOT3_UPOW		397		//		TD时隙3上行输入检测功率		
#define	MADD_TD_SLOT4_UPOW		398		//		TD时隙4上行输入检测功率		
#define	MADD_TD_SLOT5_UPOW		399		//		TD时隙5上行输入检测功率		
#define	MADD_TD_SLOT6_UPOW		400		//		TD时隙6上行输入检测功率		
#define	MADD_TD_SLOT7_UPOW		401		//		TD时隙7上行输入检测功率		
#define	MADD_TD_SLOT1_DPOW		402		//		TD时隙1下行输入检测功率		
#define	MADD_TD_SLOT2_DPOW		403		//		TD时隙2下行输入检测功率		
#define	MADD_TD_SLOT3_DPOW		404		//		TD时隙3下行输入检测功率		
#define	MADD_TD_SLOT4_DPOW		405		//		TD时隙4下行输入检测功率		
#define	MADD_TD_SLOT5_DPOW		406		//		TD时隙5下行输入检测功率		
#define	MADD_TD_SLOT6_DPOW		407		//		TD时隙6下行输入检测功率		
#define	MADD_TD_SLOT7_DPOW		408		//		TD时隙7下行输入检测功率		
#define	MADD_FPS_S1		409		//		频点搜素范围1起始频点		
#define	MADD_FPS_E1		410		//		频点搜素范围1结束频点		
#define	MADD_FPS_S2		411		//		频点搜素范围2起始频点		
#define	MADD_FPS_E2		412		//		频点搜素范围2结束频点		
#define	MADD_FPS_BCCH_LK_SET		413		//		频点搜索:		
#define	MADD_FPS_CID_LK_SET		414		//		频点搜索:		
#define	MADD_FPS_BCCH_FC_M		415		//		频点搜索:		
#define	MADD_FPS_CA_FC_0		416		//		频点搜索:		
#define	MADD_FPS_CA_FC_1		417		//		频点搜索:		
#define	MADD_FPS_CA_FC_2		418		//		频点搜索:		
#define	MADD_FPS_CA_FC_3		419		//		频点搜索:		
#define	MADD_FPS_CA_FC_4		420		//		频点搜索:		
#define	MADD_FPS_CA_FC_5		421		//		频点搜索:		
#define	MADD_FPS_CA_FC_6		422		//		频点搜索:		
#define	MADD_FPS_CA_FC_7		423		//		频点搜索:		
#define	MADD_FPS_CA_FC_8		424		//		频点搜索:		
#define	MADD_FPS_CA_FC_9		425		//		频点搜索:		
#define	MADD_FPS_CA_FC_10		426		//		频点搜索:		
#define	MADD_FPS_CA_FC_11		427		//		频点搜索:		
#define	MADD_FPS_CA_FC_12		428		//		频点搜索:		
#define	MADD_FPS_CA_FC_13		429		//		频点搜索:		
#define	MADD_FPS_CA_FC_14		430		//		频点搜索:		
#define	MADD_FPS_CA_FC_15		431		//		频点搜索:		
#define	MADD_FPS_BCCH_FC_1		432		//		频点搜索:		
#define	MADD_FPS_BCCH_FC_2		433		//		频点搜索:		
#define	MADD_FPS_BCCH_FC_3		434		//		频点搜索:		
#define	MADD_FPS_BCCH_FC_4		435		//		频点搜索:		
#define	MADD_FPS_BCCH_FC_5		436		//		频点搜索:		
#define	MADD_FPS_BCCH_FC_6		437		//		频点搜索:		
#define	MADD_FPS_AREA_ID		438		//		频点搜索:		
#define	MADD_FPS_CID		439		//		频点搜索:		
#define	MADD_FPS_CID_1		440		//		频点搜索:		
#define	MADD_FPS_CID_2		441		//		频点搜索:		
#define	MADD_FPS_CID_3		442		//		频点搜索:		
#define	MADD_FPS_CID_4		443		//		频点搜索:		
#define	MADD_FPS_CID_5		444		//		频点搜索:		
#define	MADD_FPS_CID_6		445		//		频点搜索:		
#define	MADD_A_EXPA_IDRAIN_SET		446		//		微功放:		
#define	MADD_TD_SLOT1_DPOW_OVER_THR		447		//625		//下行输入导频过功率门限		
#define	MADD_TD_SLOT1_DPOW_OWE_THR		448		//626		//下行输入导频欠功率门限		
#define	MADD_A_INPUT_TOTAL_DPOW_OVER_THR		449		//				
#define	MADD_A_INPUT_TOTAL_DPOW_OWE_THR		450		//				
#define	MADD_B_INPUT_TOTAL_DPOW_OVER_THR		451		//				
#define	MADD_B_INPUT_TOTAL_DPOW_OWE_THR		452		//				
#define	MADD_C_INPUT_TOTAL_DPOW_OVER_THR		453		//				
#define	MADD_C_INPUT_TOTAL_DPOW_OWE_THR		454		//				
#define	MADD_D_INPUT_TOTAL_DPOW_OVER_THR		455		//				
#define	MADD_D_INPUT_TOTAL_DPOW_OWE_THR		456		//				
#define	MADD_REE_A_DL_OUT_TOTAL_POW_DETECT		457		//A段RE下行输出总功率				
#define	MADD_A_RE_LOCAL_ST_ALARM		458		//覆盖单元本地告警状态				
#define	MADD_REE_B_DL_OUT_TOTAL_POW_DETECT		459		//B段RE下行输出总功率				
#define	MADD_B_RE_LOCAL_ST_ALARM		460		//覆盖单元本地告警状态				
#define	MADD_REE_C_DL_OUT_TOTAL_POW_DETECT		461		//A段RE下行输出总功率				
#define	MADD_C_RE_LOCAL_ST_ALARM		462		//覆盖单元本地告警状态				
#define	MADD_REE_D_DL_OUT_TOTAL_POW_DETECT		463		//D段RE下行输出总功率				
#define	MADD_D_RE_LOCAL_ST_ALARM		464		//覆盖单元本地告警状态	
#define	MADD_C_TD_1ST_CP_TIME		465		//		TD第1转换点时间,ns,	
#define	MADD_C_TD_2ND_CP_TIME		466		//		TD第2转换点时间,ns,	
#define	MADD_C_TD_LNA_ON_TIME		467		//		LNA开启迟后DN_PA关闭的保护时间ns	
#define	MADD_C_TD_LNA_OFF_TIME		468		//		LNA关闭超前DN_PA开启的保护时间ns	
#define	MADD_C_TD_SLOT1_DPOW_OVER_THR		469		//625		//下行输入导频过功率门限	
#define	MADD_C_TD_SLOT1_DPOW_OWE_THR		470		//626		//下行输入导频欠功率门限	
#define	MADD_D_TD_1ST_CP_TIME		471		//		TD第1转换点时间,ns,	
#define	MADD_D_TD_2ND_CP_TIME		472		//		TD第2转换点时间,ns,	
#define	MADD_D_TD_LNA_ON_TIME		473		//		LNA开启迟后DN_PA关闭的保护时间ns	
#define	MADD_D_TD_LNA_OFF_TIME		474		//		LNA关闭超前DN_PA开启的保护时间ns	
#define	MADD_D_TD_SLOT1_DPOW_OVER_THR		475		//625		//下行输入导频过功率门限	
#define	MADD_D_TD_SLOT1_DPOW_OWE_THR		476		//626		//下行输入导频欠功率门限	
#define	MADD_C_TD_SLOT1_POW		477		//		TD时隙1输入检测功率	
#define	MADD_C_TD_SLOT2_POW		478		//		TD时隙2输入检测功率	
#define	MADD_C_TD_SLOT3_POW		479		//		TD时隙3输入检测功率	
#define	MADD_C_TD_SLOT4_POW		480		//		TD时隙4输入检测功率	
#define	MADD_C_TD_SLOT5_POW		481		//		TD时隙5输入检测功率	
#define	MADD_C_TD_SLOT6_POW		482		//		TD时隙6输入检测功率	
#define	MADD_C_TD_SLOT7_POW		483		//		TD时隙7输入检测功率	
#define	MADD_C_TD_SLOT8_POW		484		//		TD时隙8输入检测功率	
#define	MADD_C_TD_SLOT9_POW		485		//		TD时隙9输入检测功率	
#define	MADD_C_TD_SLOT10_POW		486		//		TD时隙10输入检测功率	
#define	MADD_C_TD_SLOT11_POW		487		//		TD时隙11输入检测功率	
#define	MADD_C_TD_SLOT12_POW		488		//		TD时隙12输入检测功率	
#define	MADD_C_TD_SLOT13_POW		489		//		TD时隙13输入检测功率	
#define	MADD_C_TD_SLOT14_POW		490		//		TD时隙14输入检测功率	
#define	MADD_C_TD_SLOT15_POW		491		//		TD时隙15输入检测功率	
#define	MADD_C_TD_SLOT16_POW		492		//		TD时隙16输入检测功率	
#define	MADD_C_TD_SLOT17_POW		493		//		TD时隙17输入检测功率	
#define	MADD_C_TD_SLOT18_POW		494		//		TD时隙18输入检测功率	
#define	MADD_C_TD_SLOT19_POW		495		//		TD时隙19输入检测功率	
#define	MADD_C_TD_SLOT20_POW		496		//		TD时隙20输入检测功率	
#define	MADD_D_TD_SLOT1_POW		497		//		TD时隙1输入检测功率	
#define	MADD_D_TD_SLOT2_POW		498		//		TD时隙2输入检测功率	
#define	MADD_D_TD_SLOT3_POW		499		//		TD时隙3输入检测功率	
#define	MADD_D_TD_SLOT4_POW		500		//		TD时隙4输入检测功率	
#define	MADD_D_TD_SLOT5_POW		501		//		TD时隙5输入检测功率	
#define	MADD_D_TD_SLOT6_POW		502		//		TD时隙6输入检测功率	
#define	MADD_D_TD_SLOT7_POW		503		//		TD时隙7输入检测功率	
#define	MADD_D_TD_SLOT8_POW		504		//		TD时隙8输入检测功率	
#define	MADD_D_TD_SLOT9_POW		505		//		TD时隙9输入检测功率	
#define	MADD_D_TD_SLOT10_POW		506		//		TD时隙10输入检测功率	
#define	MADD_D_TD_SLOT11_POW		507		//		TD时隙11输入检测功率	
#define	MADD_D_TD_SLOT12_POW		508		//		TD时隙12输入检测功率	
#define	MADD_D_TD_SLOT13_POW		509		//		TD时隙13输入检测功率	
#define	MADD_D_TD_SLOT14_POW		510		//		TD时隙14输入检测功率	
#define	MADD_D_TD_SLOT15_POW		511		//		TD时隙15输入检测功率	
#define	MADD_D_TD_SLOT16_POW		512		//		TD时隙16输入检测功率	
#define	MADD_D_TD_SLOT17_POW		513		//		TD时隙17输入检测功率	
#define	MADD_D_TD_SLOT18_POW		514		//		TD时隙18输入检测功率	
#define	MADD_D_TD_SLOT19_POW		515		//		TD时隙19输入检测功率	
#define	MADD_D_TD_SLOT20_POW		516		//		TD时隙20输入检测功率	
#define	MADD_DL_DELAY_OFFSET_B		517		//		下行延时偏移量		
#define	MADD_DL_DELAY_OFFSET_C		518		//		下行延时偏移量		
#define	MADD_DL_DELAY_OFFSET_D		519		//		下行延时偏移量		
#define	MADD_PARA_VGS_A		            520		//	         A段栅压		
#define	MADD_PARA_VGS_B          		521		//		 B段栅压		
#define	MADD_PARA_VGS_C          		522		//		 C段栅压
#define	MADD_PARA_VGS_D          		523		//		 D段栅压
#define	MADD_PARA_VGS_COMP_A		        524	//	     A段栅压		
#define	MADD_PARA_VGS_COMP_B          		525		//		 B段栅压		
#define	MADD_PARA_VGS_COMP_C          		526		//		 C段栅压
#define	MADD_PARA_VGS_COMP_D          		527		//		 C段栅压
#define	MADD_ATT_DATA_COMP_A		528				//ATT补偿数据
#define	MADD_ATT_DATA_COMP_B		529				//ATT补偿数据
#define	MADD_ATT_DATA_COMP_C		530				//ATT补偿数据
#define	MADD_ATT_DATA_COMP_D		531				//ATT补偿数据
#define	MADD_MAX_T14_A		532		//	光口最大延时
#define	MADD_MAX_T14_B		533		//	光口最大延时
#define	MADD_MAX_T14_C		534		//	光口最大延时
#define	MADD_MAX_T14_D		535		//	光口最大延时
#define	MADD_ERL_JG_A		536// A段话务量统计结果
#define	MADD_ERL_JG_C		537
#define	MADD_ERL_JG_D		538
#define	MADD_MOVE_CENTER_FRE_D		539//改变下行中心频率
#define	MADD_MOVE_CENTER_FRE_U		540//改变上行中心频率

#define	SYS_PARAM_2B_COUNT				541//					

				


// 参数地址定义==================================================== 4b
#define PARA_DEV_ADDR	0x8893	//	设备路由登记地址
#define PARA_BIT_ERR_COUNT	0	// 	数据包错误统计
#define PARA_TOPO_CHG_COUNT	0	// 拓扑变化计数
#define PARA_FPGA_PKT_COUNT	0	// FPGA数据包个数计数
#define PARA_OPT_RE_COUNT1	0x88ee	// 远端机节点计数1
#define PARA_OPT_RE_COUNT2	0x88ef	// 远端机节点计数2
#define PARA_OPS_PORT			0x88ec	// 光口的对端光口号


// 访问地址>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 4B
#define MADD_DEV_ADDR			0	// 设备路由登记地址
#define MADD_BIT_ERR_COUNT	1	// 数据包错误统计
#define MADD_TOPO_CHG_COUNT	2	// 拓扑变化计数
#define MADD_FPGA_PKT_COUNT	3	// FPGA数据包个数计数
#define MADD_OPT_RE_COUNT1	4	// 远端机节点计数1
#define MADD_OPT_RE_COUNT2	5	// 远端机节点计数2
#define MADD_OPS_PORT			6	// 光口的对端光口号

#define SYS_PARAM_4B_COUNT	7

// 参数地址定义==================================================== ASC
#define PARA_PRI_TYPE	0xf001	//	模块类型(用ASCII码)
#define PARA_PRI_ID	0xf000	//	模块识别ID号(用ASCII码)
#define PARA_PRI_MCU_DATE	0xf02a	//	MCU程序日期(用ASCII码)
#define PARA_PRI_GL_ROM_ID	0xf029	//	唯一识别ID(用ASCII码)
#define PARA_PRI_GL_SEQ	0xf028	//	厂家生产序列号(用ASCII码)
#define PARA_PRI_GL_PRODUCT	0xf027	//	厂家产品编号(用ASCII码)
#define PARA_PRI_SEQ	0xf019	//	生产序列号(用ASCII码)
#define PARA_MODULE_HRI_STR	0	//	ID识别字符串(用ASCII码)
#define PARA_PRI_FPGA_DATE	0xf02b	//	FPGA程序日期(用ASCII码)
#define PARA_PRI_FPGA2_DATE	0xf02c	//	FPGA2程序日期(用ASCII码)
#define PARA_A_PRI_9363_UPDATA_DATE	(0)	//	9363配置文件更新日期(用ASCII码)
#define PARA_B_PRI_9363_UPDATA_DATE	(0)	//	9363配置文件更新日期(用ASCII码)
#define PARA_C_PRI_9363_UPDATA_DATE	(0)	//	9363配置文件更新日期(用ASCII码)
#define PARA_REE_POSITION_INF		(0xF01E)	//	扩展单元位置信息（设备安放位置，即物理地址，
#define PARA_MCU_VERSION_NEW		(0) //  MCU新的版本信息

// 访问地址>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ASC
#define MADD_PRI_TYPE			(0)	//	模块类型(用ASCII码)
#define MADD_PRI_ID				(MADD_PRI_TYPE+1)	//	模块识别ID号(用ASCII码)
#define MADD_PRI_MCU_DATE		(MADD_PRI_ID+1)	//	MCU程序日期(用ASCII码)
#define MADD_PRI_GL_ROM_ID	(MADD_PRI_MCU_DATE+1)	//	唯一识别ID(用ASCII码)
#define MADD_PRI_GL_SEQ		(MADD_PRI_GL_ROM_ID+1)	//	厂家生产序列号(用ASCII码)
#define MADD_PRI_GL_PRODUCT	(MADD_PRI_GL_SEQ+1)	//	厂家产品编号(用ASCII码)
#define MADD_PRI_SEQ			(MADD_PRI_GL_PRODUCT+1)	//	生产序列号(用ASCII码)
#define MADD_MODULE_HRI_STR	(MADD_PRI_SEQ+1)	//	ID识别字符串(用ASCII码)
#define MADD_PRI_FPGA_DATE	(MADD_MODULE_HRI_STR+1)	//	FPGA程序日期(用ASCII码)
#define MADD_PRI_FPGA2_DATE	(MADD_PRI_FPGA_DATE+1)	//	FPGA2程序日期(用ASCII码)
#define MADD_A_PRI_9363_UPDATA_DATE	(MADD_PRI_FPGA2_DATE+1)	//	9363配置文件更新日期(用ASCII码)
#define MADD_B_PRI_9363_UPDATA_DATE	(MADD_A_PRI_9363_UPDATA_DATE+1)	//	9363配置文件更新日期(用ASCII码)
#define MADD_C_PRI_9363_UPDATA_DATE	(MADD_B_PRI_9363_UPDATA_DATE+1)	//	9363配置文件更新日期(用ASCII码)
#define MADD_REE_POSITION_INF		(MADD_C_PRI_9363_UPDATA_DATE+1)	//	扩展单元位置信息（设备安放位置，即物理地址，
#define MADD_MCU_VERSION_NEW		(MADD_REE_POSITION_INF+1) //  MCU新的版本信息

#define SYS_PARAM_ASC_COUNT	(MADD_MCU_VERSION_NEW+1)



//****************************EU参数1字节********************************
#define PARA_EU_ALARM_FLAG1     			0	//EU1告警指示		
#define PARA_EU_ALARM_FLAG2     			0	//EU2告警指示		
#define PARA_EU_ALARM_FLAG3     			0	//EU3告警指示		
#define PARA_EU_ALARM_FLAG4     			0	//EU4告警指示		
#define PARA_EU_ALARM_FLAG5     			0	//EU5告警指示		
#define PARA_EU_ALARM_FLAG6     			0	//EU6告警指示		
#define PARA_EU_ALARM_FLAG7     			0	//EU7告警指示		
#define PARA_EU_ALARM_FLAG8     			0	//EU8告警指示		


#define MADD_EU_ALARM_FLAG1     			0	//EU1告警指示		
#define MADD_EU_ALARM_FLAG2     			1	//EU2告警指示		
#define MADD_EU_ALARM_FLAG3     			2	//EU3告警指示		
#define MADD_EU_ALARM_FLAG4     			3	//EU4告警指示		
#define MADD_EU_ALARM_FLAG5     			4	//EU5告警指示		
#define MADD_EU_ALARM_FLAG6     			5	//EU6告警指示		
#define MADD_EU_ALARM_FLAG7     			6	//EU7告警指示		
#define MADD_EU_ALARM_FLAG8     			7	//EU8告警指示		



#define	SYS_PARAM_EU_1B_COUNT						8


//****************************EU参数2字节********************************
#define PARA_EU_ALARM_CONTENT1     			0	//EU1告警内容		
#define PARA_EU_ALARM_CONTENT2     			0	//EU2告警内容		
#define PARA_EU_ALARM_CONTENT3     			0	//EU3告警内容		
#define PARA_EU_ALARM_CONTENT4     			0	//EU4告警内容		
#define PARA_EU_ALARM_CONTENT5     			0	//EU5告警内容		
#define PARA_EU_ALARM_CONTENT6     			0	//EU6告警内容		
#define PARA_EU_ALARM_CONTENT7     			0	//EU7告警内容		
#define PARA_EU_ALARM_CONTENT8     			0	//EU8告警内容
#define PARA_EU_RUALARM_FLAG1     				8	//EU1下的16个RU告警指示		
#define PARA_EU_RUALARM_FLAG2     				9	//EU2下的16个RU告警指示		
#define PARA_EU_RUALARM_FLAG3     				10	//EU3下的16个RU告警指示		
#define PARA_EU_RUALARM_FLAG4     				11	//EU4下的16个RU告警指示		
#define PARA_EU_RUALARM_FLAG5     				12	//EU5下的16个RU告警指示		
#define PARA_EU_RUALARM_FLAG6     				13	//EU6下的16个RU告警指示		
#define PARA_EU_RUALARM_FLAG7     				14	//EU7下的16个RU告警指示		
#define PARA_EU_RUALARM_FLAG8     				15	//EU8下的16个RU告警指示	



#define MADD_EU_ALARM_CONTENT1     			0	//EU1告警内容		
#define MADD_EU_ALARM_CONTENT2     			1	//EU2告警内容		
#define MADD_EU_ALARM_CONTENT3     			2	//EU3告警内容		
#define MADD_EU_ALARM_CONTENT4     			3	//EU4告警内容		
#define MADD_EU_ALARM_CONTENT5     			4	//EU5告警内容		
#define MADD_EU_ALARM_CONTENT6     			5	//EU6告警内容		
#define MADD_EU_ALARM_CONTENT7     			6	//EU7告警内容		
#define MADD_EU_ALARM_CONTENT8     			7	//EU8告警内容

#define MADD_EU_RUALARM_FLAG1     				8	//EU1下的16个RU告警指示		
#define MADD_EU_RUALARM_FLAG2     				9	//EU2下的16个RU告警指示		
#define MADD_EU_RUALARM_FLAG3     				10	//EU3下的16个RU告警指示		
#define MADD_EU_RUALARM_FLAG4     				11	//EU4下的16个RU告警指示		
#define MADD_EU_RUALARM_FLAG5     				12	//EU5下的16个RU告警指示		
#define MADD_EU_RUALARM_FLAG6     				13	//EU6下的16个RU告警指示		
#define MADD_EU_RUALARM_FLAG7     				14	//EU7下的16个RU告警指示		
#define MADD_EU_RUALARM_FLAG8     				15	//EU8下的16个RU告警指示	


#define	SYS_PARAM_EU_2B_COUNT						16


#define	PRI_TYPE_LEN	8
#define	PRI_ID_LEN	10
#define	PRI_MCU_DATE_LEN	(20+3)
#define	PRI_GL_ROM_ID_LEN	20
#define	PRI_GL_SEQ_LEN	20
#define	PRI_GL_PRODUCT_LEN	20
#define	PRI_SEQ_LEN	20
#define	MODULE_HRI_STR_LEN	20
#define	PRI_FPGA_DATE_LEN	64
#define	PRI_9363_UPDATA_DATE_LEN	50
#define	PRI_MAU_POSITION_INF_LEN			(20)	
#define	MCU_VERSION_NEW_LEN				64



extern UCHAR8 str_pri_type[];
extern UCHAR8 str_pri_id[];
extern UCHAR8 str_pri_mcu_date[];
extern UCHAR8 str_pri_gl_rom_id[];
extern UCHAR8 str_pri_gl_seq[];
extern UCHAR8 str_pri_gl_product[];
extern UCHAR8 str_pri_seq[];
extern UCHAR8 str_module_hri_str[];
extern UCHAR8 str_pri_fpga_date[];
extern UCHAR8 str_pri_fpga2_date[];
//	9363_A配置文件更新日期(用ASCII码)
extern UCHAR8 str_a_pri_9363_date[];
//	9363_B配置文件更新日期(用ASCII码)
extern UCHAR8 str_b_pri_9363_date[];
//	9363_C配置文件更新日期(用ASCII码)
extern UCHAR8 str_c_pri_9363_date[];
//	ree设备位置信息
extern UCHAR8 str_mau_position_inf[];
// MCU程序版本(用ASCII码)
extern UCHAR8 str_pri_mcu_version_new[];



extern const UCHAR8 calc_type[];



#endif


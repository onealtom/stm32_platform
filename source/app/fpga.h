//20140209
/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :fpga.h
* Description :FPGA处理相关函数
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			初始版本
**************************************************************/
#ifndef _FPGA_H
#define _FPGA_H

#include "ex_conf.h"

typedef struct _S_FPGA_CONFIG
{
	UCHAR8 a_net_type;		// A段通讯制式
	UCHAR8 a_ultra_info;	// A段附加信息
	UCHAR8 b_net_type;		// B段通讯制式
	UCHAR8 b_ultra_info;	// B段附加信息
	UCHAR8 c_net_type;		// C段通讯制式
	UCHAR8 c_ultra_info;	// C段附加信息
	UCHAR8 d_net_type;		// D段通讯制式
	UCHAR8 d_ultra_info;	// D段附加信息	
	
	UCHAR8 wlan_en;			// 1-WLAN功能使能

	FLOAT32 a_fpga_data_clk; //A段FPGA数据时钟
	FLOAT32 b_fpga_data_clk; //B段FPGA数据时钟
	FLOAT32 c_fpga_data_clk; //C段FPGA数据时钟
	FLOAT32 d_fpga_data_clk; //D段FPGA数据时钟

	
	UCHAR8 a_9363; //A段9363选择
	UCHAR8 b_9363; //B段9363选择
	UCHAR8 c_9363; //C段9363选择
	UCHAR8 d_9363; //D段9363选择
	

#if	0
	FLOAT32 a_dch_avg_pow;	// 下行输出通道平均功率
	FLOAT32 a_uch_avg_pow;	// 上行输出通道平均功率
	
	FLOAT32 b_dch_avg_pow;	// 下行输出通道平均功率
	FLOAT32 b_uch_avg_pow;	// 上行输出通道平均功率

	FLOAT32 c_dch_avg_pow;	// 下行输出通道平均功率
	FLOAT32 c_uch_avg_pow;	// 上行输出通道平均功率
	
	FLOAT32 d_dch_avg_pow;	// 下行输出通道平均功率
	FLOAT32 d_uch_avg_pow;	// 上行输出通道平均功率	
#endif
	

}_T_FPGA_CFG;

typedef struct _S_ATT_ADJ_ST
{
	UCHAR8 adj_st;
	UCHAR8 ab_flag;
	UCHAR8 ud_flag;
	UCHAR8 att_no;
	UCHAR8 step;
	UCHAR8 is_wait;
	UINT16 dat_len;
	UINT16 fre_point;
	UINT16 time_out;
} _T_ATT_ADJ_ST;


extern UINT32 fpga_load_status;

//编绎ACDU版本以下宏要一起打开



#define ATT_ADJ_ST_IDLE				0  //空闲校正
#define ATT_ADJ_ST_MAX_ADJ			1  //开始最校正
#define ATT_ADJ_ST_WAIT_MAX_PSF		2  //等待返回最大校正的选频功率
#define ATT_ADJ_ST_STEP_ADJ			3  //开始步进校正 
#define ATT_ADJ_ST_WAIT_STEP_PSF	4  //等待返回步进校正的选频功率

#define ATT_UL_ADJ		0
#define ATT_DL_ADJ		1

#define FPGA_MSG_BUFF_SIZE	191		// FPGA消息缓冲大小
#define FPGA_MSG_FRAME_LEN	(FPGA_MSG_BUFF_SIZE-1)		// FPGA数据帧缓冲字节长度
#define FPGA_MSG_ADDR_LEN	(6)		//大数据包从第二个包开始，增加目的地址、源地址。长度为8

#define FPGA_FRAME_FIFO_SIZE	200		// FPGA传输帧FIFO字节长度，读取数据的时候一次要把整个帧FIFO全部读完

#define FPGA_LDST_OK			0x0000	// FPGA已加载并成功初始化
#define FPGA_LDST_NO_FILE		0x0001	// 找不到FPGA加载文件
#define FPGA_LDST_FAIL			0x0002	// FPGA加载失败
#define FPGA_LDST_INIT_ERR		0x0004	// FPGA初始化失败

#define FPGA_LOAD_BLOCK1		0x01	// 区块1
#define FPGA_LOAD_BLOCK2		0x02	// 区块2

#define FPGA_POWER_PDN		10		// 计算输入输出功率时的参数,单位dbm

#define FPGA_AF_ATT1			0	// 前端衰减器1
#define FPGA_AF_ATT2			1	// 前端衰减器2
#define FPGA_AB_ATT1			2	// 后端衰减器1

#define FPGA_BF_ATT1			0	// 前端衰减器1
#define FPGA_BF_ATT2			1	// 前端衰减器2
#define FPGA_BB_ATT1			2	// 后端衰减器1

// 链路计算相关参数
#define FPGA_PDN			(10)		// 归一化数字幅度(dbm)


#if defined CLIENT_JIZHUN
#if defined JIZHUN_V2
#define FPGA_REC_GFNOM	(50)	    // REC前端标称增益
#define FPGA_REC_GDNOM	(10)		// REC后端标称增益
#define FPGA_RE_GFNOM		(50)		// RE前端标称增益
#define FPGA_RE_GDNOM		(10)		// RE后端标称增益
#else
#define FPGA_REC_GFNOM	(0)	    // REC前端标称增益
#define FPGA_REC_GDNOM	(10)		// REC后端标称增益
#define FPGA_RE_GFNOM		(50)		// RE前端标称增益
#define FPGA_RE_GDNOM		(10)		// RE后端标称增益
#endif

#else
#define FPGA_REC_GFNOM	(30)	    // REC前端标称增益
#define FPGA_REC_GDNOM	(10)		// REC后端标称增益
#define FPGA_RE_GFNOM		(30)		// RE前端标称增益
#define FPGA_RE_GDNOM		(10)		// RE后端标称增益

#endif


#define FPGA_SERDES_T_S2P		300	// FPGA光纤串转并延迟(单位ns)
#define FPGA_SERDES_T_P2S		300	// FPGA光纤并转串延迟(单位ns)


//增益波动校准
#define GAIN_ADJ_ST_IDLE						0//空闲
#define GAIN_ADJ_ST_SET_AUEU_ADJ_MODE		1//AU EU进入校准模式
//#define GAIN_ADJ_ST_START_ADJ					2//开始校准
#define GAIN_ADJ_ST_SET_AUEU_FRE				2//设置AU EU频点
#define GAIN_ADJ_ST_GET_EU_SF_POW			3//获取选频功率
#define GAIN_ADJ_ST_DONE						4//完成


//告警相关处理
#define ALARM_CLAER	0//清除告警
#define ALARM_GET_STATUS1  1//获取告警状态
//计算GS写入寄存器的值
#define CALC_GS_REG( GS )	(UINT16)( pow(10, ((GS)/20))*256.0 )	// 10^(Gs/20)*256

// 计算选频级输出功率
//	PA: 设置的端口通道功率
//	GA: 功放增益
//	G_OUT_ATT: 输出双工器衰减量
//	GFCMPS: 后端频率补偿因子
//	GDNOM: 后端标称增益
#define CALC_OUTPUT_PSF( PA, GA, G_OUT_ATT, GFCMPS, GDNOM )	\
	(FLOAT32)( (PA)-(GA)+(G_OUT_ATT)+(GFCMPS)-GDNOM )

// 计算DA数字域输出最大平均功率
//	CH_NUM: 通道数
#define CALC_DA_MAX_POW( CH_NUM )		\
	(FLOAT32)(-6-10*LOG_10(3+(CH_NUM))+FPGA_PDN)

#define CALC_DA_MAX_POW_WCDMA( CH_NUM )		\
	(FLOAT32)(-18-10*LOG_10(1+(FLOAT32)((CH_NUM)/4.0))+FPGA_PDN)


// 计算Fpga的Gdcmps
//	PDA: DA数字域输出最大平均功率
//	PSF: 选频级输出功率
//	GINP: 输出滤波器增益
#define CALC_GDCMPS( PDA, PSF, GINP )	(FLOAT32)(PDA-PSF-GINP)

// 根据寄存器的值求增益
#define CALC_GAIN( REG_VAL )	( (REG_VAL==0) ? 0 : (FLOAT32)( 20*LOG_10( (REG_VAL)/256.0 ) ) )		// 20*lg( GAIN_REG/2^8 )

// 根据寄存器值求功率
#define CALC_POWER( REG_VAL )	( (REG_VAL==0) ? (FLOAT32)(-150) : ((FLOAT32)(FPGA_PDN+(FLOAT32)10.0*LOG_10( (FLOAT32)(REG_VAL)/4294967296L ))))	// 10*lg(POW_REG/2^32)+Pdn
// 根据寄存器值求功率
#define CALC_POWER_1( REG_VAL )	( (REG_VAL==0) ? (FLOAT32)(-100) : ((FLOAT32)(FPGA_PDN+(FLOAT32)10.0*LOG_10( (FLOAT32)(REG_VAL)/4294967296L ))))	// 10*lg(POW_REG/2^32)+Pdn

// 温度增益补偿 FTCOMP=int[10^(TCOFF/20)*4096]
#define CALC_FTCOMP( COMP_DB ) ( 4096*pow(10, (COMP_DB)/20) )

//==FPGA参数相关==
#define FPGA_WO_REG(ADR)		(0x8000|(ADR))	// 只写寄存器地址标志
#define FPGA_WO_REG_COUNT		320//252		//FPGA写入寄存器个数


//只写寄存器***********************************************************************************************
#define FPGA_REG_WRITE_PROTECT	FPGA_WO_REG(0x00)		//寄存器写保护
#define WP_CODE_NO_PROTECT	0x4747
#define WP_CODE_PROTECT_ALL	0x0000

#define FPGA_REG_SHOW_ERROR				FPGA_WO_REG(0X01)	//FPGA_WO_REG(15) FPGA错误指示灯控制
#define ERR_AU		(0x01<<15)
#define ERR_EU		(0x01<<14)
#define ERR_RU		(0x01<<13)

#define FPGA_REG_CH_SEL					FPGA_WO_REG(0X02)		// 要操作的高频通道号
#define FPGA_REG_TRAFFIC_CTL			FPGA_WO_REG(0X03)	// FPGA_WO_REG(7)话务统计控制
#define BM_TRAFFIC_PERIOD				(0xFF<<0)	// 占用时隙统计时间长度（分钟）
#define BM_TRAFFIC_STATISTIC			(1<<15)		// 话务统计功能不使能<0>/使能<1>

#define FPGA_REG_ATT_ADJ_TBL			FPGA_WO_REG(0X010)	//FPGA_WO_REG(5) 各衰减器校准修正表格地址
#define BM_ATT_ADDR		(0x3F<<0)			// 表格地址
#define ATT_SEL_A1		(0x00<<13)		// A段衰减器ATT1
#define ATT_SEL_A3		(0x01<<13)		// A段衰减器ATT3
#define ATT_SEL_B1		(0x02<<13)		// B段衰减器ATT1
#define ATT_SEL_B3		(0x03<<13)		// B段衰减器ATT3
#define ATT_SEL_C1		(0x04<<13)		// C段衰减器ATT1
#define ATT_SEL_C3		(0x05<<13)		// C段衰减器ATT3
#define ATT_SEL_D1		(0x06<<13)		// D段衰减器ATT1
#define ATT_SEL_D3		(0x07<<13)		// D段衰减器ATT3

#define FPGA_REG_ATT_ADJ_DAT			FPGA_WO_REG(0X11)	//FPGA_WO_REG(6) 衰减器修正表格写入数值

#define FPGA_REG_ATT_FULL_REDUCE		FPGA_WO_REG(0x12)	//FPGA_WO_REG(4) att1数控衰减0衰

// A段只写控制寄存器
#define FPGA_REG_A_ATT_CTL				FPGA_WO_REG(0X20)	//FPGA_WO_REG(16) A段衰减校准控制
#define ATT_MODE_MASK		0x0003		// 工作模式掩码
#define ATT_MODE_NORMAL		0x0000		// 正常工作
#define ATT_MODE_ADJUST		0x0002		// 衰减校准
#define ATT_MODE_VERIFY		0x0003		// 衰减校准验证
#define ATT_WORK_EN			(1<<2)		// A段工作使能,1-工作
#define ATT_MANUAL			(1<<3)		// 1-手动ATT ; 0-自动ATT衰减

#define FPGA_REG_A_ATT3_EN				FPGA_WO_REG(0X21)	//FPGA_WO_REG(17) A段ATT3控制输出使能脉冲
#define FPGA_REG_A_ATT1_CAL				FPGA_WO_REG(0X22)	//FPGA_WO_REG(18) A段前端衰减器校准时ATT1的衰减值
#define FPGA_REG_A_ATT3_CAL				FPGA_WO_REG(0X23)	//FPGA_WO_REG(19) A段前端衰减器校准时ATT3的衰减值
#define FPGA_REG_A_FT_CMPS				FPGA_WO_REG(0X24)	//FPGA_WO_REG(20) A段前端温度补偿系数,小数点在D12和D11之间
#define FPGA_REG_A_BT_CMPS				FPGA_WO_REG(0X25)	//FPGA_WO_REG(21) A段后端温度补偿系数,小数点在D12和D11之间
#define FPGA_REG_A_FREQ_CTL_L_12		FPGA_WO_REG(0X26)	//FPGA_WO_REG(22) A段数字本振频率字低12位
#define BM_FREQ		(0xFFF<<0)			// A段数字本振频率字
#define BM_CHN_EN	(1<<15)				// A段选频通道工作使能1-工作;0-不工作
#define FPGA_REG_A_FREQ_CTL_H_14		FPGA_WO_REG(0x27)	//FPGA_WO_REG(0X80) A段下行前端数字本振频率字高14位
#define FPGA_REG_A_D_FREQ_CTL_L_12		FPGA_WO_REG(0x28)	//FPGA_WO_REG(0x84) A段上行后端数字本振频率字低12位
#define FPGA_REG_A_D_FREQ_CTL_H_14		FPGA_WO_REG(0x29)	//FPGA_WO_REG(0x85) A段上行后端数字本振频率字高14位
#define FREQ_SIG	(1<<15)				// A段数字本振频率字正负 1/0----负/正
#define FPGA_REG_A_FOUT_CTL				FPGA_WO_REG(0X2A)	//FPGA_WO_REG(23) 输出补偿频率及频谱翻转控制
#define FPGA_REG_GSM_BW_SEL				FPGA_WO_REG(0X2E)	//FPGA_WO_REG(66) 宽带版本GSM带宽选择
#define GSM_BW_SEL_6M			0
#define GSM_BW_SEL_20M		1
#define GSM_BW_SEL_24M		2
#define GSM_BW_SEL_25M		3

// B段只写控制寄存器
#define FPGA_REG_B_ATT_CTL				FPGA_WO_REG(0X40)	//FPGA_WO_REG(32) B段衰减校准控制
#define FPGA_REG_B_ATT3_EN				FPGA_WO_REG(0X41)	//FPGA_WO_REG(33) B段ATT3控制输出使能脉冲
#define FPGA_REG_B_ATT1_CAL				FPGA_WO_REG(0X42)	//FPGA_WO_REG(34) B段前端衰减器校准时ATT1的衰减值
#define FPGA_REG_B_ATT3_CAL				FPGA_WO_REG(0X43)	//FPGA_WO_REG(35) B段前端衰减器校准时ATT3的衰减值
#define FPGA_REG_B_FT_CMPS				FPGA_WO_REG(0X44)	//FPGA_WO_REG(36) B段前端温度补偿系数,小数点在D12和D11之间
#define FPGA_REG_B_BT_CMPS				FPGA_WO_REG(0X45)	//FPGA_WO_REG(37) B段后端温度补偿系数,小数点在D12和D11之间
#define FPGA_REG_B_FREQ_CTL_L_12		FPGA_WO_REG(0X46)	//FPGA_WO_REG(38) B段下行前端数字本振频率字低12位
#define FPGA_REG_B_FREQ_CTL_H_14		FPGA_WO_REG(0x47)	//FPGA_WO_REG(0X81) B段下行前端数字本振频率字高14位
#define FPGA_REG_B_D_FREQ_CTL_L_12		FPGA_WO_REG(0x48)	//FPGA_WO_REG(0x86) B段上行后端数字本振频率字低12位
#define FPGA_REG_B_D_FREQ_CTL_H_14		FPGA_WO_REG(0x49)	//FPGA_WO_REG(0x87) B段上行后端数字本振频率字高14位
#define FPGA_REG_B_FOUT_CTL				FPGA_WO_REG(0X4A)	//FPGA_WO_REG(39) 输出补偿频率及频谱翻转控制

#define FPGA_REG_B_W_SPI_CONTROL			FPGA_WO_REG(0x5A)//(0X7A)	// D15-读写指示，1是写，0是读;D[14:10]-SPI指令信号，默认为全零;D[9:0]-读写地址信号
#define FPGA_REG_B_W_SPI_WRITE_DATA		FPGA_WO_REG(0x5B)//(0X7B)	// D15-MCU读写SPI指示信号，1：允许MCU读写SPI，0：禁止MCU读写SPI    D[7:0]-读出的SPI数据

// C段只写控制寄存器
#define FPGA_REG_C_ATT_CTL				FPGA_WO_REG(0X60)	//FPGA_WO_REG(70) C段衰减校准控制
#define FPGA_REG_C_ATT3_EN				FPGA_WO_REG(0X61)	//FPGA_WO_REG(71) C段ATT3控制输出使能脉冲
#define FPGA_REG_C_ATT1_CAL				FPGA_WO_REG(0X62)	//FPGA_WO_REG(72) C段前端衰减器校准时ATT1的衰减值
#define FPGA_REG_C_ATT3_CAL				FPGA_WO_REG(0X63)	//FPGA_WO_REG(73) C段前端衰减器校准时ATT3的衰减值
#define FPGA_REG_C_FT_CMPS				FPGA_WO_REG(0X64)	//FPGA_WO_REG(74) C段前端温度补偿系数,小数点在D12和D11之间
#define FPGA_REG_C_BT_CMPS				FPGA_WO_REG(0X65)	//FPGA_WO_REG(75) C段后端温度补偿系数,小数点在D12和D11之间
#define FPGA_REG_C_FREQ_CTL_L_12		FPGA_WO_REG(0X66)	//FPGA_WO_REG(76) C段数字本振频率控制
#define FPGA_REG_C_FREQ_CTL_H_14		FPGA_WO_REG(0x67)	//FPGA_WO_REG(0X82) C段下行前端数字本振频率字高14位
#define FPGA_REG_C_D_FREQ_CTL_L_12		FPGA_WO_REG(0X68)	//FPGA_WO_REG(76) C段上行前端数字本振频率控制低12位
#define FPGA_REG_C_D_FREQ_CTL_H_14		FPGA_WO_REG(0x69)	//FPGA_WO_REG(0X82) C段上行前端数字本振频率字高14位

#define FPGA_REG_C_W_SPI_CONTROL		FPGA_WO_REG(0x7A)//(0X7A)	// D15-读写指示，1是写，0是读;D[14:10]-SPI指令信号，默认为全零;D[9:0]-读写地址信号
#define FPGA_REG_C_W_SPI_WRITE_DATA	FPGA_WO_REG(0x7B)//(0X7B)	// D15-MCU读写SPI指示信号，1：允许MCU读写SPI，0：禁止MCU读写SPI    D[7:0]-读出的SPI数据

// D段只写控制寄存器
#define FPGA_REG_D_ATT_CTL				FPGA_WO_REG(0X80)	//FPGA_WO_REG(78) D段衰减校准控制
#define FPGA_REG_D_ATT3_EN				FPGA_WO_REG(0X81)	//FPGA_WO_REG(79) D段ATT3控制输出使能脉冲
#define FPGA_REG_D_ATT1_CAL				FPGA_WO_REG(0X82)	//FPGA_WO_REG(80) D段前端衰减器校准时ATT1的衰减值
#define FPGA_REG_D_ATT3_CAL				FPGA_WO_REG(0X83)	//FPGA_WO_REG(81) D段前端衰减器校准时ATT3的衰减值
#define FPGA_REG_D_FT_CMPS				FPGA_WO_REG(0X84)	//FPGA_WO_REG(82) D段前端温度补偿系数,小数点在D12和D11之间
#define FPGA_REG_D_BT_CMPS				FPGA_WO_REG(0X85)	//FPGA_WO_REG(83) D段后端温度补偿系数,小数点在D12和D11之间
#define FPGA_REG_D_FREQ_CTL_L_12		FPGA_WO_REG(0X86)	//FPGA_WO_REG(84) D段数字本振频率控制
#define FPGA_REG_D_FREQ_CTL_H_14		FPGA_WO_REG(0x87)	//FPGA_WO_REG(0X83) D段下行前端数字本振频率字高14位
#define FPGA_REG_D_D_FREQ_CTL_L_12		FPGA_WO_REG(0X88)	//FPGA_WO_REG(76) D段上行前端数字本振频率控制低12位
#define FPGA_REG_D_D_FREQ_CTL_H_14		FPGA_WO_REG(0x89)	//FPGA_WO_REG(0X82) D段上行前端数字本振频率字高14位

// 光端口只写控制寄存器
#define FPGA_REG_OPT_ON					FPGA_WO_REG(0XA0)	//FPGA_WO_REG(48) 1-对应光端口工作;0-对应光端口不工作
#define FPGA_REG_OPT_SEL				FPGA_WO_REG(0xA1)		// FPGA_WO_REG(0x01)要操作的光口号
#define FPGA_REG_W_THR_DAT				FPGA_WO_REG(0XA2)	//FPGA_WO_REG(51) D[7:0]透传字节写入
#define FPGA_REG_W_MSG_DES_ADD			FPGA_WO_REG(0XA3)	//FPGA_WO_REG(52) 接收数据包的模块的地址
#define FPGA_REG_W_MSG_SRC_ADD			FPGA_WO_REG(0XA4)	//FPGA_WO_REG(53) 发送数据包的模块的地址
#define BM_MSG_ADDR_RE	(0xFF<<0)		// D7-0：接收数据包的RE节点地址，全1表示所有节点
#define BM_MSG_ADDR_FP	(0xFF<<8)		// D15-8：接收数据包的RE所在链路的REC光端口，全1表示所有端口
#define FPGA_REG_W_MSG_LEN				FPGA_WO_REG(0XA5)	//FPGA_WO_REG(54) 数据包长度
//#define MSG_FLAME_MAX_LEN				191	//一次传输的最大字节数
#define FPGA_REG_W_MSG_DAT				FPGA_WO_REG(0XA6)	//FPGA_WO_REG(55) 数据包缓冲
#define FPGA_REG_MSG_START_SEND			FPGA_WO_REG(0XA7)	//FPGA_WO_REG(56) 写操作启动数据包传输
//#define FPGA_REG_A_FFCOMP				0x8017	// 前端频率补偿因子,小数点在D12和D11之间
//#define FPGA_REG_A_BFCOMP				0x8018	// 后端频率补偿因子,小数点在D12和D11之间

#define FPGA_REG_TD_MAIN_CH_L12			FPGA_WO_REG(0XD0)	//FPGA_WO_REG(25) D11-0:宽带TDSCDMA制式主用信道频率控制字
#define FPGA_REG_TD_MAIN_CH_H14			FPGA_WO_REG(0XD1)	//FPGA_WO_REG(26) D25-12:宽带TDSCDMA制式主用信道频率控制字
#define FPGA_REG_TD_MAIN_CH_CNT    		FPGA_WO_REG(0XD2) //FPGA_WO_REG(27) D7-0:宽带TDSCDMA制式频点个数
#define FPGA_REG_TD_MAIN_CH_END     	FPGA_WO_REG(0XD3) //FPGA_WO_REG(28) TDSCDMA制式写频率字完毕
#define FPGA_REG_TDSLOT_CTL				FPGA_WO_REG(0XD4)	//FPGA_WO_REG(41) TD时隙上下行控制
#define FPGA_REG_TD_1ST_TIME			FPGA_WO_REG(0XD5)	//FPGA_WO_REG(42) TD第一转换点时间
#define FPGA_REG_TD_2ND_TIME			FPGA_WO_REG(0XD6)	//FPGA_WO_REG(43) TD第一转换点时间
#define FPGA_REG_TD_LNA_ON_TIME			FPGA_WO_REG(0XD7)	//FPGA_WO_REG(44) TD第一转换点时间
#define FPGA_REG_TD_LNA_OFF_TIME		FPGA_WO_REG(0XD8)	//FPGA_WO_REG(45) TD第一转换点时间
#define FPGA_REG_TD_WORK_MODE			FPGA_WO_REG(0XD9)	//FPGA_WO_REG(68) TD_SCDMA控制模式，00正常模式，01上行常开，10是下行常开
#define TD_WM_NORMAL			0
#define TD_WM_UL_ALWAYS_ON	1
#define TD_WM_DL_ALWAYS_ON	2
#define FPGA_REG_TDSLOT_SEL					FPGA_WO_REG(0xDA)//(1)		// TD时隙号


#define FPGA_REC_C_TS_CONFIG			FPGA_WO_REG(0xE0)	//FPGA_WO_REG(0xDA) TD上下行时隙配比
#define FPGA_REC_C_TD_LTE_SLOT_SEL		FPGA_WO_REG(0xE1)		//FPGA_WO_REG(0xDB) 要操作的LTE时隙号
#define FPGA_REC_C_LTE_FREQ_CTL_L		FPGA_WO_REG(0xE2)	//FPGA_WO_REG(0xDC) TD_LTE信道频率控制字	13bit
#define FPGA_REC_C_LTE_FREQ_CTL_H		FPGA_WO_REG(0xE3)	//FPGA_WO_REG(0xDD) TD_LTE信道频率控制字	13bit
#define FPGA_REC_C_TD_1ST_TIME			FPGA_WO_REG(0xE4)	//FPGA_WO_REG(0xDE) TD第一转换点时间
#define FPGA_REC_C_TD_2ND_TIME			FPGA_WO_REG(0xE5)	//FPGA_WO_REG(0xDF) TD第一转换点时间
#define FPGA_REC_C_TD_LNA_ON_TIME		FPGA_WO_REG(0xE6)	//FPGA_WO_REG(0xE0) LNA开启迟后DN_PA关闭的保护时间ns
#define FPGA_REC_C_TD_LNA_OFF_TIME		FPGA_WO_REG(0xE7)	//FPGA_WO_REG(0xE1) LNA关闭超前DN_PA开启的保护时间ns
#define FPGA_REC_C_TD_WORK_MODE			FPGA_WO_REG(0XE8)	//FPGA_WO_REG(0xE2) TD_LTE控制模式，00正常模式，01上行常开，10是下行常开
#define FPGA_REG_LTE_MAIN_CH_CNT    	FPGA_WO_REG(0XE9)   //FPGA_WO_REG(27) D7-0:宽带 TD_LTE制式频点个数
#define FPGA_REG_LTE_MAIN_CH_END     	FPGA_WO_REG(0XEA)   //FPGA_WO_REG(28) TDSCDMA制式写频率字完毕
#define FPGA_REG_W_SLOT_TIME_B			FPGA_WO_REG(0xEB)	// BIT 15--只写1：打开TDS时隙配比自动检测功能
#define FPGA_REG_W_SLOT_TIME_C			FPGA_WO_REG(0xEC)	// BIT 15--只写1：打开TDS时隙配比自动检测功能
										


#define FPGA_REC_D_TS_CONFIG			FPGA_WO_REG(0xE0)	//FPGA_WO_REG(0xDA) TD上下行时隙配比
#define FPGA_REC_D_LTE_FREQ_CTL_L		FPGA_WO_REG(0xE2)	//FPGA_WO_REG(0xDC) TD_LTE信道频率控制字	13bit
#define FPGA_REC_D_LTE_FREQ_CTL_H		FPGA_WO_REG(0xE3)	//FPGA_WO_REG(0xDD) TD_LTE信道频率控制字	13bit
#define FPGA_REC_D_TD_1ST_TIME			FPGA_WO_REG(0xE4)	//FPGA_WO_REG(0xDE) TD第一转换点时间
#define FPGA_REC_D_TD_2ND_TIME			FPGA_WO_REG(0xE5)	//FPGA_WO_REG(0xDF) TD第一转换点时间
#define FPGA_REC_D_TD_LNA_ON_TIME		FPGA_WO_REG(0xE6)	//FPGA_WO_REG(0xE0) LNA开启迟后DN_PA关闭的保护时间ns
#define FPGA_REC_D_TD_LNA_OFF_TIME		FPGA_WO_REG(0xE7)	//FPGA_WO_REG(0xE1) LNA关闭超前DN_PA开启的保护时间ns
#define FPGA_REC_D_TD_WORK_MODE			FPGA_WO_REG(0XE8)	//FPGA_WO_REG(0xE2) TD_LTE控制模式，00正常模式，01上行常开，10是下行常开


// 频点扫描
#define FPGA_REG_RFC_SCAN_CNT			FPGA_WO_REG(0X100)	//FPGA_WO_REG(60) 扫描的频点数量
#define FPGA_REG_RFC_SCAN_DF_2      	FPGA_WO_REG(0X101) //FPGA_WO_REG(61) 扫描的频点数字频率字[11:0]位
#define FPGA_REG_RFC_SCAN_READY			FPGA_WO_REG(0X102)	//FPGA_WO_REG(62) 执行写操作，产生数字频率字写入完成信号
#define FPGA_REG_RFC_SCAN_START			FPGA_WO_REG(0X103)	//FPGA_WO_REG(63) 执行写操作，启动扫描
#define FPGA_REG_BCCH_DF_2				FPGA_WO_REG(0X104)	//FPGA_WO_REG(64) 要获取TCCH的BCCH频率字[11:0]位，写入频率字直接启动TCCH捕捉
#define FPGA_REG_RFC_SCAN_DF_1			FPGA_WO_REG(0x106)	//FPGA_WO_REG(57) 扫描的频点数字频率字[25:12]位
#define FPGA_REG_BCCH_DF_1				FPGA_WO_REG(0x107)	//FPGA_WO_REG(58) 要获取TCCH的BCCH频率字[25:12]位，写入频率字直接启动TCCH捕捉

#define FPGA_REG_RFC_SCAN_FRE_WORE_POINT_L12			FPGA_WO_REG(0x105)	//D15：1/0------手动/自动设置频点搜索的频率字FRE_WORE_POINT [15]D11-0：手动设置时频点的频率字 FRE_WORE_POINT[11:0] 
#define FPGA_REG_RFC_SCAN_FRE_WORE_POINT_H14			FPGA_WO_REG(0x108)	//D13-0：各频点对应的数字本振频率字FRE_WORE_POINT[25:12]（写操作时FPGA发出使能脉冲）；D15： FRE_WORE_POINT[26]。



// 默认温度补偿系数
#define DEFAULT_T_CMPS	4096
// A、B段数字本振频率控制寄存器控制位
#define CNL_FREQ_MASK		(0x0FFF)			// 数字本振频率字
#define SF_CHANNEL_EN		(1<<15)			// 选频通道工作使能1-工作;0-不工作
// A、B段频率输出频谱反转
#define FOUT_SPEC_INV		(1<<15)			// 1-翻转; 0-不翻转


#define FPGA_REG_EX_DEV_CTL		FPGA_WO_REG(0x11F)		// FPGA_WO_REG(3)外设器件控制线
#define BM_EX_PLL_DAT			(1<<0)	// 频率综合器设置数据线PLL_DAT
#define BM_EX_PLL_CLK			(1<<1)	// 频率综合器设置时钟线PLL_CLK
//#define BM_EX_A_DA9788_RST		// A段DA9778复位信号 A_DA_RST
//#define BM_EX_B_DA9788_RST		// B段DA9778复位信号 B_DA_RST
//#define BM_EX_AD6655_EN			// AD6655片选AD_EN
//#define BM_EX_AD6655_SYNC			// AD6655同步控制
#define BM_EX_FA_PLL_LE		(1<<8)	// A段前端综合器设置片选FA_PLL_LE
#define BM_EX_BA_PLL_LE		(1<<9)	// A段后端综合器设置片选BA_PLL_LE
#define BM_EX_FB_PLL_LE			(1<<10)	// B段前端综合器设置片选FB_PLL_LE
#define BM_EX_BB_PLL_LE			(1<<11)	// B段后端综合器设置片选BB_PLL_LE
#define BM_OUT_ATT_OFF			(1<<12)	// A段ATT1-ATT3和B段ATT1-ATT3强制全衰控制。1---强制全衰，0---正常控制

#define FPGA_REG_DELAY_SPEC_H		FPGA_WO_REG(0X11F)	//FPGA_WO_REG(49) D[15:0]信号发送延时要求[23:8]
#define FPGA_REG_DELAY_SPEC_L		FPGA_WO_REG(0X11F)	//FPGA_WO_REG(50) D[15:8]信号发送延时要求[7:0]
//#define FPGA_REG_RFC_SCAN_DF		FPGA_WO_REG(61)	// 扫描的频点数字频率字
//#define FPGA_REG_RFC_SCAN_DF_1		FPGA_WO_REG(0x11f)	//FPGA_WO_REG(57) 扫描的频点数字频率字[25:12]位
//#define FPGA_REG_BCCH_DF			FPGA_WO_REG(64)	// 要获取TCCH的BCCH频率字，写入频率字直接启动TCCH捕捉
//#define FPGA_REG_BCCH_DF_1			FPGA_WO_REG(0x11f)	//FPGA_WO_REG(58) 要获取TCCH的BCCH频率字[25:12]位，写入频率字直接启动TCCH捕捉

//#define FPGA_REG_C_D_FREQ_CTL_L_12		FPGA_WO_REG(0x11F)	//FPGA_WO_REG(0x88)C段上行后端数字本振频率字低12位
//#define FPGA_REG_C_D_FREQ_CTL_H_14	FPGA_WO_REG(0x11F)	//FPGA_WO_REG(0x89)C段上行后端数字本振频率字高14位
//#define FPGA_REG_D_D_FREQ_CTL_L_12		FPGA_WO_REG(0x11F)	//FPGA_WO_REG(0x8A) D段上行后端数字本振频率字低12位
//#define FPGA_REG_D_D_FREQ_CTL_H_14	FPGA_WO_REG(0x11F)	//FPGA_WO_REG(0x8B) D段上行后端数字本振频率字高14位
// 软错误检测(SED)只写控制寄存器
#define FPGA_REG_W_SED_CTL		FPGA_WO_REG(0x11f)	//FPGA_WO_REG(200) 软错误检测控制
#define BM_SED_ENABLE		(1<<0)	// 1-使能SED; 0-禁止SED
#define BM_SED_START		(1<<1)	// 1-启动SED; 0-停止SED
// 加密
#define FPGA_REG_W_ONE_WIRE		FPGA_WO_REG(0x11f)	//FPGA_WO_REG(251) 单总线写数据，加密用

#define FPGA_REG_A_ATT2_CAL		FPGA_WO_REG(0x11F)	// A段前端衰减器校准时ATT2的衰减值   //mdas v2 31寄存器暂时不用  暂时用于屏蔽功能用
#define FPGA_REG_B_ATT2_CAL		FPGA_WO_REG(0X11F)	// B段前端衰减器校准时ATT2的衰减值 //mdas v2 31寄存器暂时不用  暂时用于屏蔽功能用
#define FPGA_REG_C_ATT2_CAL		FPGA_WO_REG(0X11F)	// C段前端衰减器校准时ATT2的衰减值//mdas v2 31寄存器暂时不用  暂时用于屏蔽功能用
#define FPGA_REG_D_ATT2_CAL		FPGA_WO_REG(0X11F)	// D段前端衰减器校准时ATT2的衰减值//mdas v2 31寄存器暂时不用  暂时用于屏蔽功能用



//只读寄存器********************************************************************************************************
#define FPGA_REG_WRITE_CHECK		0x00	//0 将只写寄存器0的值取反读出，用于总线连接检查
#define FPGA_REG_EDITION_INFO		0x01    //	FPGA版本相关信息
#define BM_SECONDARY_VERSION	(0x0F<<0)	// FPGA次版本号
#define BM_PRIMARY_VERSION		(0x0F<<4)	// FPGA主版本号
#define BM_MODULE_FLAG			(0x01<<12)	// 模块标识0-REC, 1-RE
#define BM_PRODUCT_FLAG		(0x07<<13)	// 产品标示: 7-GSM光纤直放站

#define FPGA_REG_PCB_VERSION		0x02    //	2 PCB版本号
#define FPGA_REG_IRQ_CLEAN			0x03    //	3 读操作后清除由160单元D0为1引起的中断,水印读出初始化
#define FPGA_REG_WATER_PRINT		0x04    //	4 读操作后清除饱和状态内容,每读一次水印数据地址加1。
#define FPGA_REG_CH_COUNT			0x05	//5 FPGA支持的通道数
#define BM_A_CH_COUNT			(0x0F<<0)	// FPGA支持的段A的通道个数
#define BM_B_CH_COUNT			(0x0F<<8)	// FPGA支持的段B的通道个数
#define BM_C_CH_COUNT			(0x0F<<4)	// FPGA支持的段A的通道个数
#define BM_D_CH_COUNT			(0x0F<<12)	// FPGA支持的段B的通道个数

#define FPGA_REG_R_OPT_CH			0x06	//6 待操作的光口号、高频通道号读回
#define BM_OPT_READBACK		(0x07<<8)
#define BM_CH_READBACK			(0x1F<<0)
#define FPGA_GET_CH_SEL		( 0x1F & FpgaReadRegister(FPGA_REG_R_OPT_CH) )
#define FPGA_GET_OPT_SEL		( 0x0F & ( FpgaReadRegister(FPGA_REG_R_OPT_CH)>>8 ) )
#define FPGA_REG_RF_INFO			0x07	//7 FPGA的射频相关信息
//#define FPGA_REG_RF_INFO_C_D			45	// FPGA的射频相关信息
#define BM_A_NT_INFO		(0xF<<8)	// A段的射频制式信息
#define FPGA_A_NT_GSM		0		// GSM
#define FPGS_A_NT_WCDMA		1		// WCDMA
#define FPGA_A_NT_TD		2		// TD-SCDMA
#define FPGA_A_NT_CDMA_WB	3		// CDMA
#define FPGA_A_NT_GSM_WB	4		// 宽带GSM
#define FPGA_A_NT_CMMB		5		// CMMB
#define FPGA_A_NT_TETRA_WB	6		// 宽带集群

#define BM_B_NT_INFO		(0xF<<12)	// B段的射频制式信息
#define FPGA_B_NT_GSM		0		// GSM
#define FPGS_B_NT_WCDMA		1		// WCDMA
#define FPGA_B_NT_TD		2		// TD-SCDMA
#define FPGA_B_NT_CDMA_WB	3		// 宽带CDMA
#define FPGA_B_NT_GSM_D		4		// 分集GSM
#define FPGA_B_NT_WCDMA_D	5		// 分集WCDMA
#define FPGA_B_NT_TD_D		6		// 分集TD-SCDMA
#define FPGA_B_NT_CDMA_D_WB	7		// 宽带分集CDMA
#define FPGA_B_NT_TD_WB		8		// 宽带TD-SCDMA
#define FPGA_B_NT_GSM_D_WB	9		// 分集宽带GSM
#define FPGA_B_NT_GSM_WB	10		// 宽带GSM
#define FPGA_B_NT_WCDMA_WB	11		// 宽带WCDMA
#define FPGA_B_NT_CMMB		12		// CMMB
#define FPGA_B_NT_TETRA_D_WB	13		// 分集宽带集群

#define FPGA_C_NT_LTE_TD		0		// LTE_TD
#define FPGA_C_NT_LTE_FDD		1		// LTE_FDD
#define FPGA_D_NT_LTE_TD		0		// LTE_TD
#define FPGA_D_NT_LTE_FDD		1		// LTE_FDD

#define FPGA_REG_SOME_STATUS		0X08//64某些状态标志
#define FPGA_REG_CLEAR_TRA_FLAG		0X09	//65清除话务统计时间周期进行标志
#define FPGA_REG_AC_WARNING_FLAG		0X0A	//D1: 外部AC告警输入 AC_WARNING			

// A段只读控制寄存器
#define FPGA_REG_A_FAD_POW_H	0X0020	//32 前端A/D输入信号功率高16位
#define FPGA_REG_A_FAD_POW_L	0X0021	//33 前端A/D输入信号功率低16位
#define FPGA_REG_A_BDA_POW_H	0X0022	//34 后端D/A输出信号功率高16位
#define FPGA_REG_A_BDA_POW_L	0X0023	//35 后端D/A输出信号功率低16位
#define FPGA_REG_A_FG_CMPS		0x0024	//36 前端Gfcmps增益
#define FPGA_REG_A_BG_CMPS		0x0025	//37 后端GDcmps增益
#define FPGA_REG_A_ATT1_VAL		0x0026	//38 前端衰减器ATT1的衰减值
#define FPGA_REG_A_ATT2_VAL		    0X11F	//39 前端衰减器ATT2的衰减值
#define FPGA_REG_A_ATT3_VAL		0x0027	//40 前端衰减器ATT3的衰减值
//#define FPGA_REG_A_AD_DA_ST		0x0029	// AD、DA饱和状态,一旦发生饱和就一直保持下来。4单元读操作后清除各饱和状态
#define BM_AD_FSAT		0x0001		// 1-前端AD输入饱和
#define BM_DA_DSAT		0x0002		// 1-后端DA输出饱和

// B段只读控制寄存器
#define FPGA_REG_B_FAD_POW_H		0X40	//48 前端A/D输入信号功率高16位				
#define FPGA_REG_B_FAD_POW_L		0X41	//49 前端A/D输入信号功率低16位				
#define FPGA_REG_B_BDA_POW_H		0X42	//50 后端D/A输出信号功率高16位				
#define FPGA_REG_B_BDA_POW_L		0x43	//51 后端D/A输出信号功率低16位				
#define FPGA_REG_B_FG_CMPS		0x44	//52 前端Gfcmps增益				
#define FPGA_REG_B_BG_CMPS		0x45	//53 后端GDcmps增益				
#define FPGA_REG_B_ATT1_VAL		0x46	//54 前端衰减器ATT1的衰减值				
//#define FPGA_REG_B_ATT2_VAL		55	// 前端衰减器ATT2的衰减值				
#define FPGA_REG_B_ATT3_VAL		0x47	//56 前端衰减器ATT3的衰减值				
//#define FPGA_REG_B_AD_DA_ST		57	// AD、DA饱和状态,一旦发生饱和就一直保持下来。4单元读操作后清除各饱和状态				
#define FPGA_REG_B_R_SPI_DATA			0x5A	// SPI: D15-MCU读写SPI指示信号，1：允许MCU读写SPI，0：禁止MCU读写SPI    D[7:0]-读出的SPI数据

// C段只读控制寄存器				
#define FPGA_REG_C_FAD_POW_H		0x60	//148 前端A/D输入信号功率高16位	
#define FPGA_REG_C_FAD_POW_L		0x61	//149 前端A/D输入信号功率低16位	
#define FPGA_REG_C_BDA_POW_H		0x62	//150 后端D/A输出信号功率高16位	
#define FPGA_REG_C_BDA_POW_L		0x63	//151 后端D/A输出信号功率低16位	
#define FPGA_REG_C_FG_CMPS			0x64	//152 前端Gfcmps增益
#define FPGA_REG_C_BG_CMPS			0x65	//153 后端GDcmps增益	
#define FPGA_REG_C_ATT1_VAL			0x66	//154 前端衰减器ATT1的衰减值	
//#define FPGA_REG_C_ATT2_VAL			155	// 前端衰减器ATT2的衰减值	
#define FPGA_REG_C_ATT3_VAL			0x67	//156 前端衰减器ATT3的衰减值	
//#define FPGA_REG_C_AD_DA_ST			157	// AD、DA饱和状态,一旦发生饱和就一直保持下来。4单元读操作后清除各饱和状态	

#define FPGA_REG_C_R_SPI_DATA		0x7A	// SPI: D15-MCU读写SPI指示信号，1：允许MCU读写SPI，0：禁止MCU读写SPI    D[7:0]-读出的SPI数据

// D段只读控制寄存器
#define FPGA_REG_D_FAD_POW_H		0x80	//168 前端A/D输入信号功率高16位
#define FPGA_REG_D_FAD_POW_L		0x81	//169 前端A/D输入信号功率低16位
#define FPGA_REG_D_BDA_POW_H		0x82	//170 后端D/A输出信号功率高16位
#define FPGA_REG_D_BDA_POW_L		0x83	//171 后端D/A输出信号功率低16位
#define FPGA_REG_D_FG_CMPS			0x84	//172 前端Gfcmps增益
#define FPGA_REG_D_BG_CMPS			0x85	//173 后端GDcmps增益
#define FPGA_REG_D_ATT1_VAL			0x86	//174 前端衰减器ATT1的衰减值
//#define FPGA_REG_D_ATT2_VAL			175	// 前端衰减器ATT2的衰减值
#define FPGA_REG_D_ATT3_VAL			0x87	//176 前端衰减器ATT3的衰减值
//#define FPGA_REG_D_AD_DA_ST			177	// AD、DA饱和状态,一旦发生饱和就一直保持下来。4单元读操作后清除各饱和状态


// 光端口只读通讯寄存器
#define FPGA_REG_R_THR_IDLE_ST	0xA0	//8 光端口透传写入空闲标志,每个位对应一个光口,1-空闲
#define FPGA_REG_THR_FIFO_ST	0xA1	//9 光口透传接收FIFO状态,低8位1表示FIFO有数据,高8位1表示FIFO满
#define FPGA_REG_R_THR_DAT		0xA2	//10 光口透传FIFO读出地址
#define FPGA_REG_MSG_TX_READY	0xA3	//11 光口数据包发送FIFO就绪标志,位对应,1-FIFO就绪，可以写入新数据
#define FPGA_REG_MSG_FIFO_ST	0xA4	//12 光口数据包接收FIFO状态,位对应,低8位1表示FIFO有数据,高8位1表示FIFO满
#define FPGA_REG_PKT_ERR_COUNT	0xA5	//13 数据包错误计数
#define FPGA_REG_CLEAR_PKT_ERR	0xA6	//14 读操作清0数据包错误计数器
#define FPGA_REG_R_MSG_DAT		0xA7	//15 FIFO中读出的数据包字节，读操作读出地址计数器自动加1
#define FPGA_REG_R_NEXT_MSG		0xA8	//16 读操作将数据包FIFO读指针加1，读出地址计数器清0。
#define FPGA_REG_OPT_INFO		0xA9	// 光口状态
#define BM_OPT_RE_COUNT		(0xFF<<0)	// 节点下行计数，数据帧锁定时有效
#define BM_OPT_COMMA_LOCK		(1<<8)	// 1-本端口检测到逗号
#define BM_OPT_FRM_LOCK		(1<<9)	// 1-本端口接收帧锁定
#define BM_OPS_COMMA_LOCK		(1<<10)	// 1-对端接收检测到本端逗号
#define BM_UP_DN				(0x03<<11)	// 接收帧状态
#define UP_DN_BITS			11		// 接收帧状态位偏移量
#define UP_DN_MODE_NOF	(0<<11)	// 没有收到帧数据
#define UP_DN_MODE_ATF	(1<<11)	// 收到自发帧
#define UP_DN_MODE_DNF	(2<<11)	// 收到下行帧
#define UP_DN_MODE_UPF	(3<<11)	// 收到上行帧
#define BM_OPS_END_YES			(1<<13)	// 1-末端RE收到的另一光端口的信号

#define FPGA_REG_OPS_INFO			0xAA	//18 末端RE接收的另一光口状态
#define BM_OPS_NODE_COUNT	(0xFF<<0)	// 末端RE收到的另一光端口节点下行计数
#define BM_OPS_OPT_NUM	(0xFF<<8)	// 末端RE收到的另一光端口序号

#define FPGA_REG_OPT_MAX_DELAY_H	0xC0	//23 D[15:0]REC测量的光口信号延时D23-8
#define FPGA_REG_OPT_MAX_DELAY_L	0xC1	//24 D[15:8]REC测量的光口信号延时D7-0
#define FPGA_REG_OPT_DELAY_H		0xC2	//19 D[15:0]REC测量的光口信号延时D23-8
#define FPGA_REG_OPT_DELAY_L		0xC3	//20 D[15:8]REC测量的光口信号延时D7-0
#define FPGA_REG_DL_EXDELAY		    0xC4	//21 D[2:0]下行发送附加延时
#define FPGA_REG_UL_EXDELAY		    0xC5	//22 D[7:0]上行接收附加延迟


							
#define FPGA_REG_TD_SYNC_ST		0x00D0	//58 b[4:0]-TD同步码字, b[5]-TD同步状态				
#define BM_TD_SYNC_OK		(1<<5)	// 1-TD同步OK				
#define FPGA_REG_TD_MCH_POW_H	0x00D3	// TD主用信道的AD功率MPow高8位 | AD功率 = 10*log10(MPow /2^32)+Pdn(其中Pdn为10dbm)					
#define FPGA_REG_TD_MCH_POW_L	0x00D4	// TD主用信道的AD功率MPow低16位 | 端口功率 = AD功率 - 前端模拟增益		

#define FPGA_REG_C_TD_SYNC_ST		0x00E0	//0xDA b[4:0]-TD同步码字, b[5]-TD同步状态				
#define FPGA_REG_D_TD_SYNC_ST		0x00E0	//0xDA b[4:0]-TD同步码字, b[5]-TD同步状态				
#define FPGA_REG_C_TD_MCH_POW_H	0x00E2	//0xE2 TD主用信道的AD功率MPow高16位 | AD功率 = 10*log10(MPow /2^32)+Pdn(其中Pdn为10dbm)					
#define FPGA_REG_C_TD_MCH_POW_L	0x00E3	//0xE2 TD主用信道的AD功率MPow低16位 | 端口功率 = AD功率 - 前端模拟增益		
#define FPGA_REG_C_TD_SYSCH_POW_H	0x00E6	//0xE6 TD同步信道的AD功率MPow高16位 | AD功率 = 10*log10(MPow /2^32)+Pdn(其中Pdn为10dbm)					
#define FPGA_REG_C_TD_SYSCH_POW_L	0x00E7	//0xE7 TD同步信道的AD功率MPow低16位 | 端口功率 = AD功率 - 前端模拟增益		

#define FPGA_REG_C_LTE_CUR_POS	        0x00E1	//0xE1   TD_LTE当前正在扫描的频率字位置				
#define FPGA_REG_C_LTE_CUR_FREQ_H	    0x00E2	//0xE2    D13-D0 为TD_LTE当前正在扫描的频率字高14位 D15为正负
#define FPGA_REG_C_LTE_CUR_FREQ_L	    0x00E3	//0xE3     D11-D0 当前正在扫描的频率字低12位
#define FPGA_REG_R_SLOT_TIME_B			0xEB	//BIT0~2 只读BIT0：1代表15配比,BIT1：1代表24配比,	BIT2：1代表33配比
#define FPGA_REG_R_SLOT_TIME_C			0xEC	//D3-0:特殊子帧配比 TDL_SP_SubFrm_CFG_check  等于15时表示检测失败,D7-4:上下行时隙配比 TDL_TS_EN_check  等于15时表示检测失败


// 全局状态只读寄存器
#define FPGA_REG_GCLK_ST			0x011F	//0x40 全局时钟状态,20140210 delete
#define BM_INT_PULSE_EN	(1<<0)	// 1-产生中断定时脉冲
#define BM_CLK_125			(1<<2)	// 1-逻辑时钟为125M，0-逻辑时钟为122.88
//#define BM_CLK_LD			0x0008	// 1-AD9517锁定指示
//#define BM_CLK_REFMON		0x0010	// 1-AD9517参考正常指示
#define BM_FPGA_PLL_LOCK	(1<<5)	// 1-FPGA本振锁定指示
//#define BM_A_BB_PLL_LOCK	0x0040	// 1-A段AD9779 PLL锁定指示
//#define BM_B_BB_PLL_LOCK	0x0080	// 1-B段AD9779 PLL锁定指示
//#define BM_CLK_SATATUS		0x0100	// 时钟状态
//#define BM_FA_PLL_ALM		(1<<9)	// 1-A段前端频率综合器锁定指示
//#define BM_BA_PLL_ALM		(1<<10)	// 1-A段后端频率综合器锁定指示
//#define BM_FB_PLL_ALM		(1<<11)	// 1-B段前端频率综合器锁定指示
//#define BM_BB_PLL_ALM		(1<<12)	// 1-B段后端频率综合器锁定指示
#define BM_WLAN_EN			(1<<13)	// 1-带有WLAN功能


// SERDES状态
#define FPGA_SERDES_PLL_UNLOCK	0x011F	//0x48 光口发送锁相环锁定状态,1-失锁
#define BM_QUAD0_LOCK		0x0001	// QUAD0失锁
#define BM_QUAD1_LOCK		0x0002	// QUAD1失锁
#define FPGA_SERDES_FP_LOS			0x011F	//0x49 光端口信号丢失LOS状态,位对应,1-信号丢失
#define FPGA_SERDES_CDR_UNLOCK	0x011F	//0x4a 恢复出来的时钟信号和数据信号失锁状态,位对应,1-失锁
#define FPGA_SERDES_COMMA_LOS	0x011F	//0x4b 光口逗号丢失状态,位对应,1-逗号丢失
#define FPGA_REG_SFP_CONNECT		0x00AF	//0x4c 光口在位状态0-在位

// 网口状态信息
#define FPGA_WLAN_PORT_INFO		0X11F//95
#define BM_WLAN_LINK_ST	(1<<15)		// 1/0---链路有/没有LINK上
#define BM_WLAN_MODE		(1<<12)		// 1/0---全双工/半双工
#define BM_WLAN_SPEED		(0x03<<10)	// 网络速率指示
#define 	FLAG_WLAN_SPEED_10M		(0<<10)		// 10M
#define 	FLAG_WLAN_SPEED_100M	(1<<10)		// 100M
#define 	FLAG_WLAN_SPEED_1000M	(2<<10)		// 1000M

// 软错误检测SED状态
#define FPGA_REG_SED_ST			0x011F	//0x48
#define BM_SEDINPROG		0x0001
#define BM_SEDDONE			0x0002
#define BM_SEDERR			0x0004

// 频点扫描状态
#define FPGA_REG_RFC_SCAN_ST		0x0100	//0x050 频点扫描状态
#define BM_SCAN_BCCH_END	(1<<0)	// BCCH搜索完毕
#define BM_SCAN_TCH_END	(1<<1)	// TCH搜索完毕
#define BM_SCAN_PBCCH_END	(1<<2)	// PBCCH搜索完毕
#define BM_SCAN_EDGE_END	(1<<3)	// EDGE搜索完毕
#define BM_SCAN_AREA_END	(1<<4)	// 小区信息
#define FPGA_REG_BCCH_CNT			0x0101	//0x051 扫描到的频点BCCH个数
#define FPGA_REG_BCCH_INFO		0x0102	//0x052 频点BCCH信息, 频点1序号>功率>误码率>频点2序号>功率>误码率>......
#define FPGA_REG_TCH_INFO			0x0103	//0x053 频点TCH信息, 8个16位数据
#define FPGA_REG_EDGE_CNT			0x0105	//0x055 EDGE频点个数
#define FPGA_REG_EDGE_INFO		0x0106	//0x056 频点EDGE信息, 低10位为频点号
#define FPGA_REG_PBCCH_INFO		0x0107	//0x057 频点PBCCH信息, 10个16位数据
#define FPGA_REG_AREA_INFO		0x0108	//0x058 小区信息

// 注册数据只读寄存器
#define FPGA_REG_R_ONE_WIRE		0x011F	// DS28E01读回数据
#define FPGA_REG_REGISTER_ST		0x011F	// 注册验证信息
#define FPGA_REG_R_REG_NUM4		0x011F
#define FPGA_REG_R_REG_NUM3		0x011F
#define FPGA_REG_R_REG_NUM2		0x011F
#define FPGA_REG_R_REG_NUM1		0x011F

//=======================================================================

// RE寄存器
#define FPGA_REG_RE_A_DPSF_H	0x2D//47	// 下行选频通道输出功率值高16位,功率折算方式:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_A_DPSF_L	0x2E//48	// 下行选频通道输出功率值低16位
#define FPGA_REG_RE_A_UPSF_H	0x2F//49	// 上行选频通道输出功率值高16位,功率折算方式:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_A_UPSF_L	0x30//50	// 上行选频通道输出功率值低16位

#define FPGA_REG_RE_B_DPSF_H	0x4D//79	// 下行选频通道输出功率值高16位,功率折算方式:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_B_DPSF_L	0x4E//80	// 下行选频通道输出功率值低16位
#define FPGA_REG_RE_B_UPSF_H	0x4F//81	// 上行选频通道输出功率值高16位,功率折算方式:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_B_UPSF_L	0x50//82	// 上行选频通道输出功率值低16位

// RE寄存器
#define FPGA_REG_RE_C_DPSF_H	0x6D//163	// 下行选频通道输出功率值高16位,功率折算方式:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_C_DPSF_L	0x6E//164	// 下行选频通道输出功率值低16位
#define FPGA_REG_RE_C_UPSF_H	0x6F//165	// 上行选频通道输出功率值高16位,功率折算方式:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_C_UPSF_L	0x70//166	// 上行选频通道输出功率值低16位

#define FPGA_REG_RE_D_DPSF_H	0x8D//195	// 下行选频通道输出功率值高16位,功率折算方式:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_D_DPSF_L	0x8E//196	// 下行选频通道输出功率值低16位
#define FPGA_REG_RE_D_UPSF_H	0x8F//197	// 上行选频通道输出功率值高16位,功率折算方式:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_D_UPSF_L	0x90//198	// 上行选频通道输出功率值低16位


//=======================================================================

// 宏操作定义
#define FPGA_ENABLE_WRITE		FpgaWriteRegister( FPGA_REG_WRITE_PROTECT, WP_CODE_NO_PROTECT)
#define FPGA_DISABLE_WRITE		FpgaWriteRegister( FPGA_REG_WRITE_PROTECT, WP_CODE_PROTECT_ALL)

#define FPGA_SET_OPT( OPT_NO )	FpgaWriteRegister( FPGA_REG_OPT_SEL, (OPT_NO) )		// 设置要操作的光口号
#define FPGA_GET_OPT( OPT_NO )	FpgaReadRegister( FPGA_REG_OPT_SEL,(OPT_NO)  )				// 当前操作的光口号
#define FPGA_SET_LTE_SLOT( SLOT_NO )	FpgaWriteRegister( FPGA_REC_C_TD_LTE_SLOT_SEL, (SLOT_NO) )		// 设置要操作的光口号
#define FPGA_SET_TDS_SLOT( SLOT_NO )	FpgaWriteRegister( FPGA_REG_TDSLOT_CTL	, (SLOT_NO) )		// 设置要操作的光口号

#define FPGA_SET_CHANNEL(CHL)		FpgaWriteRegister( FPGA_REG_CH_SEL, (CHL) )

#define FPGA_ATT_SET_DELAY	10000		//10ms

//衰减器数量
#define DL_ATT_NUM	1	//下行
#define UL_ATT_NUM	1	//上行
//上下行标志
#define UL_ATT_FLAG_MAIN	0
#define UL_ATT_FLAG_DIVE	1
//上行校准标志位
#define UL_GAIN_ADJ_FLAG_STEP_MODE	0x80
#define UL_GAIN_ADJ_FLAG_READ_PSF	0x40
#define UL_GAIN_ADJ_STEP_CNT_MASK	0x3F

// FPGA 错误信息
#define FPGA_ERR_PROG		1
#define FPGA_ERR_CHECK		2


//////////////////////////////////////////////新加的配置，微型光纤V02//////////////////////////////////////////////////////

//PLL sdi BIT
#define PLL_B_R_PLL_SDI			2 
#define PLL_A_L_PLL_SDI			4

#define PLL_R					0
#define PLL_A					1 
#define PLL_L					2
#define PLL_B					3

#define A_MIXER					PLL_R
#define A_MODEN					PLL_A
#define B_MIXER					PLL_L
#define B_MODEN					PLL_B


#define BIT_MIXF_PLL_CLK		0x0004
#define BIT_R_L_PLL_EN			0x0008
#define BIT_A_B_PLL_CS			0x0010
#define BIT_A_B_PLL_EN			0x0020
#define BIT_PLL_CLK				0x0040
#define BIT_PLL_SDO				0x0080
#define BIT_R_L_PLL_CS			0x0100

#define FPGA_REG_W_A_PLL			FPGA_WO_REG(0x11f)//FPGA_WO_REG(13)  20130912 CHANGE 0x11f INVALID REG
#define FPGA_REG_W_B_PLL			FPGA_WO_REG(0X11F)

#define FPGA_REG_R_PLL_CLK             110            //PLL的读寄存器

#define CALC_FPGA_FW( DF )	(INT32)((FLOAT32)(DF)/0.0125 + ((DF<0) ? -0.5 : 0.5 ))	// DF/0.0203
#define ADJUST_FPGA_FW(DF)	{ if ( (DF)<0 ) {DF += 5000;} }

#define CALC_FPGA_FW_QW( FW )			((INT32)(FW)/625)	// 频率字的商(占3位)
#define CALC_FPGA_FW_RW( FW )			((INT32)(FW)%625)	// 频率字的余数(占10位)
#define CONN_FPGA_FW_Q_R( _QW, _RW )	(((_QW)&0x07)<<10)|((_RW)&0x03FF)	// 将商和余数按要求拼接成频率字 一共13位

// ------------------ Variable ------------------------
extern UCHAR8 fpga_load_block;
extern _T_FPGA_CFG fpga_cfg;

#define TF_A						0
#define TF_B						1
#define TF_C						2
#define TF_D					3
//AD80305 控制写寄存器位
#define BIT_TF_DI				0x0000
#define BIT_TF_CLK				0x0000
#define BIT_TF_EN				0x0000
#define BIT_TF_RESET			0x0000

//AD9363 控制写寄存器位
#define BIT_9363_A_RESET			(0x01<<0)
#define BIT_9363_SPI_A_AGC				(0x01<<1)
#define BIT_9363_SPI_A_DO				(0x01<<2)
#define BIT_9363_SPI_A_CLK				(0x01<<3)
#define BIT_9363_SPI_A_EN				(0x01<<4)

#define BIT_9363_B_RESET			(0x01<<8)
#define BIT_9363_SPI_B_AGC				(0x01<<9)
#define BIT_9363_SPI_B_DO				(0x01<<10)
#define BIT_9363_SPI_B_CLK				(0x01<<11)
#define BIT_9363_SPI_B_EN				(0x01<<12)

#define BIT_9363_C_RESET			(0x01<<0)
#define BIT_9363_SPI_C_AGC				(0x01<<1)
#define BIT_9363_SPI_C_DO				(0x01<<2)
#define BIT_9363_SPI_C_CLK				(0x01<<3)
#define BIT_9363_SPI_C_EN				(0x01<<4)

//AD80305读取寄存器位
#define BIT_TF_DO				0x0001

#define FPGA_REG_W_A_TF			0x11f
#define FPGA_REG_W_B_TF			0x11f
#define FPGA_REG_W_A_TF_RESET	0x11f
#define FPGA_REG_W_B_TF_RESET	0x11f

//AD9363写寄存器位
#define FPGA_REG_W_9363_SPI_DO_A_B		FPGA_WO_REG(0XF0)    //FPGA_WO_REG(11)
#define FPGA_REG_W_9363_SPI_DO_C		FPGA_WO_REG(0XF1)		//FPGA_WO_REG(12)

//SPI--AD9363/1197读取寄存器位
#define FPGA_REG_R_SPI_IN		0x00F0	// SPI   0X90
#define BIT_9363_SPI_A_DI		(0x01<<0)	//
#define BIT_9363_SPI_B_DI		(0x01<<1)	//
#define BIT_9363_SPI_C_DI		(0x01<<2)	//
#define BIT_HMC_SPI_DI		(0x01<<3)	// SPI

// HMC 1197
#define FPGA_REG_W_HMC_A_PLL			FPGA_WO_REG(0XF2)		//FPGA_WO_REG(13)
#define BIT_HMC_SPI_CLK			(0x01<<0)		//HMC1197---CLK
#define BIT_HMC_SPI_SDO			(0x01<<1)		//HMC1197---OUTPUT
#define BIT_HMC_SPI_CS			(0x01<<2)		//HMC1197---SPI SELECT
#define BIT_HMC_CS			(0x01<<15)		//HMC1197---CHIP SELECT

#define FPGA_REG_R_A_SPI_DO		7
#define FPGA_REG_R_B_SPI_DO		8

#define FPGA_W_REG_MAX	250 		//写寄存器的最大数

// ------------------ Function ------------------------
void FpgaSetErrInfo( UCHAR8 err_id );
void FpgaSendMsgPkt( UINT32 des_add, UINT32 src_add, UINT32 length, UCHAR8 * p_msg_dat );
INT16 FpgaSaveMsgDat( INT16 len, UCHAR8 *p_save_buff );
void FpgaGetMsgPkt( void );
//void FpgaReadThrDat(); 
BOOL FpgaGetTopoStaus( UCHAR8 opt, _T_FP_INFO* p_fp_info );
INT32 CalcGsmFreqWord( INT32 freq_code,  FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
INT32 CalcWcdmaFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
INT32 CalcWCDMAFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
INT32 CalcTetraFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
INT32 CalcDcsFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
INT32 CalcCdma800FreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
INT32 CalcLteTddFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
INT32 CalcLteFddFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
void CalcWcdmaPLLoutputFreq(FLOAT32 *up_fre,FLOAT32 *down_fre );
INT32 WcdmaFreqWordConfigureTxRxPll( FLOAT32 up_fre,  FLOAT32 down_fre);
void FpgaSetChannel( UCHAR8 channel, UCHAR8 enable, INT32 digit_fw, UINT16 reg_add );
UINT32 FpgaLoad(void);
void FpgaAttOutput( UCHAR8 mode );
void FpgaWriteRegister(UINT16 add, UINT16 data);
UINT16 FpgaReadRegister(UINT16 add);
void FpgaConfigPara(void);
void AfterFpgaLoad(void);
void FpgaGetChannelCount();
void FpgaEnableTrafficCtl( UCHAR8 time, UCHAR8 enable );
UCHAR8 FpgaTest();
BOOL InitFpga(void);
void FpgaMakeAttAdjMsgHead( UINT32 len, UCHAR8 * p_dat );
void FpgaGetAdDaPow( UCHAR8 ab_flag );
void FpgaHandlePsfAck( UCHAR8 * p_dat );
void FpgaAttStepAdj();
void FpgaAttAdjust();
void FpgaEnterAttAdjMode( UCHAR8 abcd_flag );
void FpgaExitAttAdjMode( UCHAR8 ab_flag );
void FpgaSetTempAdjustTable();
void FpgaSetGsmBW( UCHAR8 bw );
FLOAT32 CalcLteTdPLLoutputFreq(UCHAR8 flag);
FLOAT32 CalcLteFddPLLoutputFreq(UCHAR8 flag);
INT32 CalcLteFddFreqWord( INT32 freq_code, FLOAT32 fu_local );
INT32 LteFddFreqWordConfigureTxRxPll( FLOAT32 plloutputfreq ,UCHAR8 flag);
INT32 LteTdFreqWordConfigureTxRxPll( FLOAT32 plloutputfreq ,UCHAR8 flag);
void FpgaPowSelSlot(UINT32 reg_add);
UCHAR8 FpgaSaveAdjustTable(UCHAR8 *p_data, UCHAR8 att_count, UCHAR8 ab_flag, UCHAR8 ud_flag );
CHAR8 FpgaLoadA7(UINT32 len);
CHAR8 FpgaLoadA72(UINT32 len);
void FpgaGainAdjust();
UINT16 GianAdjustStartAdj(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
UINT16 GianAdjustGetAdjStatus(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
UINT16 GianAdjustGetAdjData(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
UINT16 GianAdjustEnterAdjMode(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
UINT32 MoveCenterFre(UCHAR8 ab_flag, UCHAR8 ud_flag);

//void FpgaSendThrDat();

#endif //_FPGA_H

/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :msg_app.h
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
#ifndef _MSG_APP_H
#define _MSG_APP_H

#define ADDR_FP_MASK			0x1F
#define ADDR_PC_MASK			0xC0

#define LOCAL_ADD_FP				0x00
#define LOCAL_ADD_RE				0x00
#define LOCAL_ADD_REE				0x00

#define PC_ADD_FP					0x40
#define PC_ADD_RE					0x00
#define PC_ADD_REE					0x00

// 广播地址
#define BROADCAST_ADD_FP			0x1F
#define BROADCAST_ADD_RE			0x3F
#define BROADCAST_ADD_REE			0x3F

// 主控地址标志
#define PC_ADD_FLAG			0x40

// 主控的绝对访问地址
#define PC_ABS_FP			0x80
#define PC_ABS_RE		    0xFF
#define PC_ABS_REE		    0xFF

// 模块的绝对访问地址
#define MODULE_ABS_FP		0x80
#define MODULE_ABS_RE	       0x00
#define MODULE_ABS_REE 	0x00

// 模块的类型
#define MODULE_TYPE_REC		0x00
#define MODULE_TYPE_REE	    0x01
#define MODULE_TYPE_RF	    0x02

// 错误光口地址
#define ERROR_FP_ADD		0xFF

//ATT校准地址
#ifdef MDAS
#define ADJ_ADDR_AU		0X1F
#define ADJ_ADDR_EU		0X01
#define ADJ_ADDR_RU		0X01
#elif defined CEDT
#define ADJ_ADDR_AU		0X1F
#define ADJ_ADDR_EU		0X01
#define ADJ_ADDR_RU		0X00
#else
#define ADJ_ADDR_AU		0X1F
#define ADJ_ADDR_EU		0X01
#define ADJ_ADDR_RU		0X01

#endif



// 消息包地址性质
#define MSG_TO_NONE	0
#define MSG_TO_PC		1
#define MSG_TO_ALL		2
#define MSG_TO_RE		3
#define MSG_TO_REE		4

// USB接口消息包
//#define MSG_PKT_START_FLAG		0x4E
//#define MSG_PKT_END_FLAG			0xE4
#define MSG_PKT_FLAG				0x4E
#define MSG_SHIFT_FLAG				0x5E

// 大数据消息缓冲
#define MSG_BIG_PKT_COUNT			2		// 支持的大消息包个数
#define MSG_BIG_PKT_SIZE			2048	// 消息包的最大长度
#define MSG_BIG_PKT_TIME_OUT		5		// 超时时间，大缓冲5秒

// 光纤消息包
#define MSG_FRAME_INDEX_MASK		0x7F	// 帧编号
#define MSG_FRAME_END_FLAG		0x80	// 最末帧标志

#define MSG_MAX_FRAME_INDEX		( MSG_BIG_PKT_SIZE/FPGA_MSG_FRAME_LEN )

// 485转光纤与RE远程通讯的数据包保留字
#define MSG_RE_TRANS_RECV_CODE1	0xD9
#define MSG_RE_TRANS_RECV_CODE2	0x9D

typedef struct _S_BIG_PKT_BUFF
{
	UINT32 owner;
	UINT16 time_out;
	UCHAR8 buff[MSG_BIG_PKT_SIZE];
} _T_BIG_PKT_BUFF;

// 消息包参数
#define MSG_PKT_HEAD_SIZE			10		// 消息包的头信息长度//20121130
#define MSG_PKT_SIZE_MIN			12		// 消息包最小长度: 目的地址[2]+源地址[2]+命令[1]+应答[1]+保留字节+CRC[2]//20121130

#define MSG_DES_FP			0
#define MSG_DES_RE			1
#define MSG_DES_REE		2//20121130
#define MSG_SRC_FP			3
#define MSG_SRC_RE			4
#define MSG_SRC_REE			5//20121130
#define MSG_CMD_ID			6
#define MSG_ACK_FLAG		7
#define MSG_RESERVE1		8		// 保留字节1
#define MSG_RESERVE2		9		// 保留字节2
#define MSG_CMD_BODY		10//20121130

// 数据包命令字
#define MSG_CMD_SET_PARAM			0x00D0	// 设置模块的相关参数
#define MSG_CMD_GET_PARAM			0x00D1	// 查询模块的相关参数
#define MSG_CMD_SET_DEV_REG		    0x00D2	// 设置外围芯片的寄存器的值
#define MSG_CMD_GET_DEV_REG		    0x00D3	// 查询外围芯片的寄存器的值
#define MSG_CMD_RESET_DEV			0x00D4	// 重新初始化外围芯片
#define MSG_CMD_GET_TABLE			0x00D6	// 查询温度补偿表,频率补偿表,衰减器补偿表内容
#define MSG_CMD_SET_TABLE			0x00D7	// 设置温度补偿表,频率补偿表,衰减器补偿表内容
#define MSG_CMD_GET_FPGA_REG		0x00D8	// 读取FPGA寄存器
#define MSG_CMD_GET_TOPO			0x00D9	// 查询当前的拓扑结构和设置的正确拓扑结构
#define MSG_CMD_SET_TOPO			0x00DA	// 设置正确的拓扑结构
#define MSG_CMD_GET_REE_INFO		0x00DB	// 获取RE信息
#define MSG_CMD_UPDATE_MCU		0x00DC	// MCU升级
#define MSG_CMD_UPDATE_FPGA		0x00DD	// FPGA升级

#define MSG_CMD_UPDATE_FPGA2		0x00E1	//发送文件到RU
#define MSG_CMD__UPDATE_CONF		0x00E2	//PC发送json到AU  FPGA3

#define MSG_CMD_GET_FLASH_PAGE	0x00DE	// 读取Flash页内容
#define MSG_CMD_ERR_ALARM			0x00EE	// 错误或故障报警
#define MSG_CMD_BLANK				0x00DF	// 空命令

#define MSG_CMD_PROMTP					0x00B6
#define MSG_CMD_RMTCMD					0x00B7

#define MSG_CMD_START_ATT_ADJ	    0x00A0	// 进入校准模式
#define MSG_CMD_ATT_STEP_ADJ		0x00A1	// 步进校准
#define MSG_CMD_END_ATT_ADJ		    0x00A2	// 退出校准
#define MSG_CMD_FC_SCAN			    0x00A6	// 频点扫描
#define MSG_CMD_RE_REMOTE			0x00CE	// RE远程访问指令
#define MSG_CMD_NOISE_TEST			0x00A7	// RE远程访问指令
#define MSG_CMD_AU		  			 0x00A4	// AU发到RU的数据
#define MSG_CMD_GAIN_ADJ  			 0x00A9	//波动校准

#define MSG_CMD_FLASH_OPERATION  	0x00EF	// 擦除Flash页内容

// 数据包应答标志
#define MSG_ACK_CMD_OK			0x00	// 正确处理
#define MSG_ACK_MASTER_SEND		0xFF	// 主动数据包
#define MSG_ACK_ERR_CMD			0xE1	// 错误命令，未知命令
#define MSG_ACK_ERR_BUSY			0xE2	// 接收端未准备好
#define MSG_ACK_ERR_CRC			0xE3	// CRC错误
#define MSG_ACK_ERR_VALUE			0xE5	// 数值错误
#define MSG_ACK_ERR_ADDR			0xE7	// 访问地址错误
#define MSG_ACK_ERR_RE_ADDR		0xE9	// 未知的RE
#define MSG_ACK_ERR_UPDATE_PKT	0xEA	// 错误的升级数据包
#define MSG_ACK_ERR_UPDATE_FAIL	0xEB	// 升级失败
#define MSG_ACK_ERR_UNDEF			0xEE	// 未知错误


// 器件标识
#define DEV_ID_CLK		    0		// 时钟
#define DEV_ID_FPGA			1		// FPGA
#define DEV_ID_AD		    2		// AD
#define DEV_ID_DA_A  	    3		// DA_0
#define DEV_ID_DA_B 	    4		// DA_1
#define DEV_ID_A_UP_LINK	    5		// A段上行链路
#define DEV_ID_A_DN_LINK	    6		// A段下行链路
#define DEV_ID_B_UP_LINK	    7		// B段前端混频器	
#define DEV_ID_B_DN_LINK	    8		// B段后端混频器
#define DEV_ID_MCU			9		// MCU寄存器 
#define DEV_ID_PHY1			10		// PHY1寄存器 
#define DEV_ID_PHY2			11		// PHY2寄存器 
#define DEV_ID_PHY3			12		// PHY3寄存器 
#define DEV_ID_PHY4			13		// PHY4寄存器
#define DEV_ID_A_AD9363			17		// AD9363寄存器 
#define DEV_ID_B_AD9363			18		// AD9363寄存器 
#define DEV_ID_C_AD9363			19		// AD9363寄存器 
#define DEV_ID_1197			20		// AD9363寄存器 
//   

#define REG_TYPE_MASK		(0x07<<5)	// 寄存器属性
#define REG_TYPE_NORMAL	(0x00<<5)	// NORMAL
#define REG_TYPE_OTHER	(0x01<<5)	// 其他类型
#define REG_TYPE_CHN		(0x02<<5)	// 通道寄存器
#define REG_TYPE_OPT		(0x04<<5)	// 光口寄存器
#define REG_TYPE_TDSLOT 	(0x06<<5)	// TD时隙
#define FPGA_TDS_LTE_REG	(0x07<<5)// TD时隙
#define REG_TYPE_ARGS		(0x1F<<0)	// 寄存器属性附带参数

#define REG_TYPE_OTHER_OTHER	(0x00)	// 
#define REG_TYPE_OTHER_TYPE1		(0x01)	// 光口数据
#define REG_TYPE_OTHER_TYPE2		(0x02)	// 

//参数类型标识
#define TYPE_REE_1B						0X81
#define TYPE_REE_2B						0X82

//增益校准子命令
#define GAIN_ADJ_CMD2_ENTER_ADJ_MODE	0x00//进入校准模式
#define GAIN_ADJ_CMD2_START_ADJ			0x01//开始增益校准
#define GAIN_ADJ_CMD2_GET_ADJ_STATUS		0x02//查询校准状态
#define GAIN_ADJ_CMD2_GET_ADJ_DATA		0x03//获取校准数据

//UINT32 CheckMsgAddr( UCHAR8 des_fp, UCHAR8 des_re );
UINT32 CheckMsgAddr( UCHAR8 des_fp, UCHAR8 des_re ,UCHAR8 des_ree);
UINT32 GetReBigMsgBuffIndex( UCHAR8 fp, UCHAR8 re,UCHAR8 rf );
//UINT32 GetReBigMsgBuffIndex( UCHAR8 fp, UCHAR8 re );
UINT32 GetFreeBigBuffIndex( void );
void CheckBigBuffTimeOut( void );
void SendMsgPkt( UINT32 tx_len, UCHAR8 * p_msg_dat );
void MsgPktTransmit( UINT32 tx_len, UCHAR8 * p_msg_dat );
//void MsgHandle_usb( UCHAR8 fp, UCHAR8 re, UINT32 msg_len, UCHAR8* p_msg_dat );
void MsgHandle( UCHAR8 fp, UCHAR8 re, UCHAR8 ree,UINT32 msg_len, UCHAR8* p_msg_dat );
//void MsgCrcError( UCHAR8 fp, UCHAR8 re, UCHAR8 cmd, UINT16 crc );//20121130
void MsgCrcError( UCHAR8 fp, UCHAR8 re, UCHAR8 ree,UCHAR8 cmd, UINT16 crc );//20121130
//void MsgReceiverBusy( UCHAR8 des_fp, UCHAR8 des_no );
void MsgReceiverBusy( UCHAR8 des_fp, UCHAR8 des_re,UCHAR8 des_rf );
void MsgHandleUnknowCmd( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleBlankCmd( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
int MsgHandlePromtp(UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff);
void MsgHandleSetParam( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetParam( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );


void MsgHandleSetDevReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetDevReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleResetDev( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetFpgaReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );

void MsgHandleUpdateMCU( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleUpdateFPGA( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleUpdateJSON( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetFlashPage( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleFlashOperatePage( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff ) ;

void MsgHandleAck( UINT16 msg_length, UCHAR8 * p_msg_dat );

#endif

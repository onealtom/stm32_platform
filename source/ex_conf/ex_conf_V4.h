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
#ifndef _EX_CONFIG_H_
#define _EX_CONFIG_H_

#define NOTRACE
 //FPGA TYPE
#define CYCLONE5	0
#define ARRIA2		1
//#define VERSION_20M_NOIN			0   //20M 非一体化
//#define VERSION_40M_NOIN			1   //40M 非一体化
//#define VERSION_20M_IN			    2   //20M 一体化
//#define VERSION_40M_IN			    3   //40M 一体化

#define VERSION_NUMBER	VERSION_50M_IN_V4				



#define FPGA_ACDU_16M_FLASH	//用在逻辑程序超过8M
#define FPGA_SOLO_LOAD	//逻辑加载和正常操作数据线分开
#define FPGA_TYPE		A7



//V3版本光纤通讯，采用新机制。从第二包开始，包头增加目的地址源地址。//20141212
#define FPGA_MSG_ADD_ADDRESS

// 客户标示 CLIENT
#define GUORENSOFT				// 国人
//#define CLIENT_NORMAL			// 其他客户
// #define CLIENT_XINMIN				// 欣民
//#define HXCT_VER					// 虹信

////#define DEBUG_UART_BAUD				115200	// 调试串口波特率
////#define USER_CONTROL_BAUD				9600	// 控制串口波特率
////#define USER_THR_BAUD					115200	// 透传串口波特率
////#define THR_USE_DEBUG_UART			// 使用Debug串口做透传端口


#define USER_INIT_PARAM_CTRL_BAUD	0	// 控制端口波特率 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define USER_INIT_PARAM_THR_PORT	0	// 透传端口选择0-485B, 1-RS232
#define USER_INIT_PARAM_THR_BAUD	0	// 透传端口波特率 0-9600, 1-19200, 2-38400, 3-57600, 4-115200

#define MAX_CHANNEL_COUNT		16//32	// 支持的通道数

#define USE_PLL9517_125MHZ		// 使用150M时钟，不定义则使用122.88M时钟
#define FUNC_FREQ_POINT_SEARCH_EN        // 启用频点搜索功能
#define	FUNC_FPS_AUTO_SET
//#define FUNC_RF_SCAN_EN				// 启用频点搜索功能
// #define USE_RS232_AS_CTRL_PORT		// 使用RS232串口做控制串口
// #define AUTO_SET_DIVE_ATT			// 自动设置分集的数控衰减器

// 网络类型
// NET_TYPE_GSM900				// GSM
// NET_TYPE_WCDMA2100				// WCDMA
// NET_TYPE_TD					// TD
// NET_TYPE_CDMA					// CDMA
// NET_TYPE_DCS1800				// DCS
// NET_TYPE_CMMB	
// NET_RESERVE3						
// NET_DIVE								分集
// NET_NONE								空，无相应硬件
#define USER_NET_TYPE_A				NET_TYPE_GSM900//NET_TYPE_GSM900//	NET_TYPE_DCS1800	// A段网络制式
//#define USER_NET_TYPE_A				NET_TYPE_DCS1800	// A段网络制式
#define USER_NET_TYPE_B				NET_TYPE_TD//	NET_TYPE_WCDMA2100		// B段网络制式
#define USER_NET_TYPE_C				NET_TYPE_LTE_TD// C段网络制式
#define USER_NET_TYPE_D				NET_TYPE_LTE_TD// D段网络制式
// TD模式
#define TD_TYPE_WB				// TD宽带版本
#define FUNC_TD_AUTO_SEARCH_FP   //td_scdma 自动搜频

//#define USER_NET_TYPE_A				NET_TYPE_DCS1800	// A段网络制式
//#define USER_NET_TYPE_B				NET_TYPE_WCDMA2100		// B段网络制式
//#define USER_NET_TYPE_C				NET_TYPE_LTE_FDD// C段网络制式
//#define USER_NET_TYPE_D				NET_TYPE_LTE_FDD// D段网络制式

#define DCS_MAX_FRE_CODE_UNICOM				736
#define DCS_MIN_FRE_CODE_UNICOM				637
#define DCS_MAX_FRE_CODE_CNMOBILE			DCS_MIN_FRE_CODE_UNICOM-1
#define DCS_MIN_FRE_CODE_CNMOBILE			512

// GSM网络模式
//#define GSM_TYPE_UNICOM			//中国联通
#define GSM_TYPE_CNMOBILE		//中国移动		

#define USER_TRAFFIC_TIME			15	// 话务量统计时间(分钟)



#endif


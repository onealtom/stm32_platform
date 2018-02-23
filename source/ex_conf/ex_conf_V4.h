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
#ifndef _EX_CONFIG_H_
#define _EX_CONFIG_H_

#define NOTRACE
 //FPGA TYPE
#define CYCLONE5	0
#define ARRIA2		1
//#define VERSION_20M_NOIN			0   //20M ��һ�廯
//#define VERSION_40M_NOIN			1   //40M ��һ�廯
//#define VERSION_20M_IN			    2   //20M һ�廯
//#define VERSION_40M_IN			    3   //40M һ�廯

#define VERSION_NUMBER	VERSION_50M_IN_V4				



#define FPGA_ACDU_16M_FLASH	//�����߼����򳬹�8M
#define FPGA_SOLO_LOAD	//�߼����غ��������������߷ֿ�
#define FPGA_TYPE		A7



//V3�汾����ͨѶ�������»��ơ��ӵڶ�����ʼ����ͷ����Ŀ�ĵ�ַԴ��ַ��//20141212
#define FPGA_MSG_ADD_ADDRESS

// �ͻ���ʾ CLIENT
#define GUORENSOFT				// ����
//#define CLIENT_NORMAL			// �����ͻ�
// #define CLIENT_XINMIN				// ����
//#define HXCT_VER					// ����

////#define DEBUG_UART_BAUD				115200	// ���Դ��ڲ�����
////#define USER_CONTROL_BAUD				9600	// ���ƴ��ڲ�����
////#define USER_THR_BAUD					115200	// ͸�����ڲ�����
////#define THR_USE_DEBUG_UART			// ʹ��Debug������͸���˿�


#define USER_INIT_PARAM_CTRL_BAUD	0	// ���ƶ˿ڲ����� 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define USER_INIT_PARAM_THR_PORT	0	// ͸���˿�ѡ��0-485B, 1-RS232
#define USER_INIT_PARAM_THR_BAUD	0	// ͸���˿ڲ����� 0-9600, 1-19200, 2-38400, 3-57600, 4-115200

#define MAX_CHANNEL_COUNT		16//32	// ֧�ֵ�ͨ����

#define USE_PLL9517_125MHZ		// ʹ��150Mʱ�ӣ���������ʹ��122.88Mʱ��
#define FUNC_FREQ_POINT_SEARCH_EN        // ����Ƶ����������
#define	FUNC_FPS_AUTO_SET
//#define FUNC_RF_SCAN_EN				// ����Ƶ����������
// #define USE_RS232_AS_CTRL_PORT		// ʹ��RS232���������ƴ���
// #define AUTO_SET_DIVE_ATT			// �Զ����÷ּ�������˥����

// ��������
// NET_TYPE_GSM900				// GSM
// NET_TYPE_WCDMA2100				// WCDMA
// NET_TYPE_TD					// TD
// NET_TYPE_CDMA					// CDMA
// NET_TYPE_DCS1800				// DCS
// NET_TYPE_CMMB	
// NET_RESERVE3						
// NET_DIVE								�ּ�
// NET_NONE								�գ�����ӦӲ��
#define USER_NET_TYPE_A				NET_TYPE_GSM900//NET_TYPE_GSM900//	NET_TYPE_DCS1800	// A��������ʽ
//#define USER_NET_TYPE_A				NET_TYPE_DCS1800	// A��������ʽ
#define USER_NET_TYPE_B				NET_TYPE_TD//	NET_TYPE_WCDMA2100		// B��������ʽ
#define USER_NET_TYPE_C				NET_TYPE_LTE_TD// C��������ʽ
#define USER_NET_TYPE_D				NET_TYPE_LTE_TD// D��������ʽ
// TDģʽ
#define TD_TYPE_WB				// TD����汾
#define FUNC_TD_AUTO_SEARCH_FP   //td_scdma �Զ���Ƶ

//#define USER_NET_TYPE_A				NET_TYPE_DCS1800	// A��������ʽ
//#define USER_NET_TYPE_B				NET_TYPE_WCDMA2100		// B��������ʽ
//#define USER_NET_TYPE_C				NET_TYPE_LTE_FDD// C��������ʽ
//#define USER_NET_TYPE_D				NET_TYPE_LTE_FDD// D��������ʽ

#define DCS_MAX_FRE_CODE_UNICOM				736
#define DCS_MIN_FRE_CODE_UNICOM				637
#define DCS_MAX_FRE_CODE_CNMOBILE			DCS_MIN_FRE_CODE_UNICOM-1
#define DCS_MIN_FRE_CODE_CNMOBILE			512

// GSM����ģʽ
//#define GSM_TYPE_UNICOM			//�й���ͨ
#define GSM_TYPE_CNMOBILE		//�й��ƶ�		

#define USER_TRAFFIC_TIME			15	// ������ͳ��ʱ��(����)



#endif


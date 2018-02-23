/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :msg_app.h
* Description :ϵͳ����������غ���
* Version     :v0.1
* Author      :RJ
* Date        :2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			��ʼ�汾
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

// �㲥��ַ
#define BROADCAST_ADD_FP			0x1F
#define BROADCAST_ADD_RE			0x3F
#define BROADCAST_ADD_REE			0x3F

// ���ص�ַ��־
#define PC_ADD_FLAG			0x40

// ���صľ��Է��ʵ�ַ
#define PC_ABS_FP			0x80
#define PC_ABS_RE		    0xFF
#define PC_ABS_REE		    0xFF

// ģ��ľ��Է��ʵ�ַ
#define MODULE_ABS_FP		0x80
#define MODULE_ABS_RE	       0x00
#define MODULE_ABS_REE 	0x00

// ģ�������
#define MODULE_TYPE_REC		0x00
#define MODULE_TYPE_REE	    0x01
#define MODULE_TYPE_RF	    0x02

// �����ڵ�ַ
#define ERROR_FP_ADD		0xFF

//ATTУ׼��ַ
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



// ��Ϣ����ַ����
#define MSG_TO_NONE	0
#define MSG_TO_PC		1
#define MSG_TO_ALL		2
#define MSG_TO_RE		3
#define MSG_TO_REE		4

// USB�ӿ���Ϣ��
//#define MSG_PKT_START_FLAG		0x4E
//#define MSG_PKT_END_FLAG			0xE4
#define MSG_PKT_FLAG				0x4E
#define MSG_SHIFT_FLAG				0x5E

// ��������Ϣ����
#define MSG_BIG_PKT_COUNT			2		// ֧�ֵĴ���Ϣ������
#define MSG_BIG_PKT_SIZE			2048	// ��Ϣ������󳤶�
#define MSG_BIG_PKT_TIME_OUT		5		// ��ʱʱ�䣬�󻺳�5��

// ������Ϣ��
#define MSG_FRAME_INDEX_MASK		0x7F	// ֡���
#define MSG_FRAME_END_FLAG		0x80	// ��ĩ֡��־

#define MSG_MAX_FRAME_INDEX		( MSG_BIG_PKT_SIZE/FPGA_MSG_FRAME_LEN )

// 485ת������REԶ��ͨѶ�����ݰ�������
#define MSG_RE_TRANS_RECV_CODE1	0xD9
#define MSG_RE_TRANS_RECV_CODE2	0x9D

typedef struct _S_BIG_PKT_BUFF
{
	UINT32 owner;
	UINT16 time_out;
	UCHAR8 buff[MSG_BIG_PKT_SIZE];
} _T_BIG_PKT_BUFF;

// ��Ϣ������
#define MSG_PKT_HEAD_SIZE			10		// ��Ϣ����ͷ��Ϣ����//20121130
#define MSG_PKT_SIZE_MIN			12		// ��Ϣ����С����: Ŀ�ĵ�ַ[2]+Դ��ַ[2]+����[1]+Ӧ��[1]+�����ֽ�+CRC[2]//20121130

#define MSG_DES_FP			0
#define MSG_DES_RE			1
#define MSG_DES_REE		2//20121130
#define MSG_SRC_FP			3
#define MSG_SRC_RE			4
#define MSG_SRC_REE			5//20121130
#define MSG_CMD_ID			6
#define MSG_ACK_FLAG		7
#define MSG_RESERVE1		8		// �����ֽ�1
#define MSG_RESERVE2		9		// �����ֽ�2
#define MSG_CMD_BODY		10//20121130

// ���ݰ�������
#define MSG_CMD_SET_PARAM			0x00D0	// ����ģ�����ز���
#define MSG_CMD_GET_PARAM			0x00D1	// ��ѯģ�����ز���
#define MSG_CMD_SET_DEV_REG		    0x00D2	// ������ΧоƬ�ļĴ�����ֵ
#define MSG_CMD_GET_DEV_REG		    0x00D3	// ��ѯ��ΧоƬ�ļĴ�����ֵ
#define MSG_CMD_RESET_DEV			0x00D4	// ���³�ʼ����ΧоƬ
#define MSG_CMD_GET_TABLE			0x00D6	// ��ѯ�¶Ȳ�����,Ƶ�ʲ�����,˥��������������
#define MSG_CMD_SET_TABLE			0x00D7	// �����¶Ȳ�����,Ƶ�ʲ�����,˥��������������
#define MSG_CMD_GET_FPGA_REG		0x00D8	// ��ȡFPGA�Ĵ���
#define MSG_CMD_GET_TOPO			0x00D9	// ��ѯ��ǰ�����˽ṹ�����õ���ȷ���˽ṹ
#define MSG_CMD_SET_TOPO			0x00DA	// ������ȷ�����˽ṹ
#define MSG_CMD_GET_REE_INFO		0x00DB	// ��ȡRE��Ϣ
#define MSG_CMD_UPDATE_MCU		0x00DC	// MCU����
#define MSG_CMD_UPDATE_FPGA		0x00DD	// FPGA����
#define MSG_CMD_GET_FLASH_PAGE	0x00DE	// ��ȡFlashҳ����
#define MSG_CMD_ERR_ALARM			0x00EE	// �������ϱ���
#define MSG_CMD_BLANK				0x00DF	// ������
#define MSG_CMD_START_ATT_ADJ	    0x00A0	// ����У׼ģʽ
#define MSG_CMD_ATT_STEP_ADJ		0x00A1	// ����У׼
#define MSG_CMD_END_ATT_ADJ		    0x00A2	// �˳�У׼
#define MSG_CMD_FC_SCAN			    0x00A6	// Ƶ��ɨ��
#define MSG_CMD_RE_REMOTE			0x00CE	// REԶ�̷���ָ��
#define MSG_CMD_NOISE_TEST			0x00A7	// REԶ�̷���ָ��
#define MSG_CMD_AU		  			 0x00A4	// AU����RU������
#define MSG_CMD_GAIN_ADJ  			 0x00A9	//����У׼

#define MSG_CMD_FLASH_OPERATION  	0x00EF	// ����Flashҳ����

// ���ݰ�Ӧ���־
#define MSG_ACK_CMD_OK			0x00	// ��ȷ����
#define MSG_ACK_MASTER_SEND		0xFF	// �������ݰ�
#define MSG_ACK_ERR_CMD			0xE1	// �������δ֪����
#define MSG_ACK_ERR_BUSY			0xE2	// ���ն�δ׼����
#define MSG_ACK_ERR_CRC			0xE3	// CRC����
#define MSG_ACK_ERR_VALUE			0xE5	// ��ֵ����
#define MSG_ACK_ERR_ADDR			0xE7	// ���ʵ�ַ����
#define MSG_ACK_ERR_RE_ADDR		0xE9	// δ֪��RE
#define MSG_ACK_ERR_UPDATE_PKT	0xEA	// ������������ݰ�
#define MSG_ACK_ERR_UPDATE_FAIL	0xEB	// ����ʧ��
#define MSG_ACK_ERR_UNDEF			0xEE	// δ֪����


// ������ʶ
#define DEV_ID_CLK		    0		// ʱ��
#define DEV_ID_FPGA			1		// FPGA
#define DEV_ID_AD		    2		// AD
#define DEV_ID_DA_A  	    3		// DA_0
#define DEV_ID_DA_B 	    4		// DA_1
#define DEV_ID_A_UP_LINK	    5		// A��������·
#define DEV_ID_A_DN_LINK	    6		// A��������·
#define DEV_ID_B_UP_LINK	    7		// B��ǰ�˻�Ƶ��	
#define DEV_ID_B_DN_LINK	    8		// B�κ�˻�Ƶ��
#define DEV_ID_MCU			9		// MCU�Ĵ��� 
#define DEV_ID_PHY1			10		// PHY1�Ĵ��� 
#define DEV_ID_PHY2			11		// PHY2�Ĵ��� 
#define DEV_ID_PHY3			12		// PHY3�Ĵ��� 
#define DEV_ID_PHY4			13		// PHY4�Ĵ���
#define DEV_ID_A_AD9363			17		// AD9363�Ĵ��� 
#define DEV_ID_B_AD9363			18		// AD9363�Ĵ��� 
#define DEV_ID_C_AD9363			19		// AD9363�Ĵ��� 
#define DEV_ID_1197			20		// AD9363�Ĵ��� 
//   

#define REG_TYPE_MASK		(0x07<<5)	// �Ĵ�������
#define REG_TYPE_NORMAL	(0x00<<5)	// NORMAL
#define REG_TYPE_OTHER	(0x01<<5)	// ��������
#define REG_TYPE_CHN		(0x02<<5)	// ͨ���Ĵ���
#define REG_TYPE_OPT		(0x04<<5)	// ��ڼĴ���
#define REG_TYPE_TDSLOT 	(0x06<<5)	// TDʱ϶
#define FPGA_TDS_LTE_REG	(0x07<<5)// TDʱ϶
#define REG_TYPE_ARGS		(0x1F<<0)	// �Ĵ������Ը�������

#define REG_TYPE_OTHER_OTHER	(0x00)	// 
#define REG_TYPE_OTHER_TYPE1		(0x01)	// �������
#define REG_TYPE_OTHER_TYPE2		(0x02)	// 

//�������ͱ�ʶ
#define TYPE_REE_1B						0X81
#define TYPE_REE_2B						0X82

//����У׼������
#define GAIN_ADJ_CMD2_ENTER_ADJ_MODE	0x00//����У׼ģʽ
#define GAIN_ADJ_CMD2_START_ADJ			0x01//��ʼ����У׼
#define GAIN_ADJ_CMD2_GET_ADJ_STATUS		0x02//��ѯУ׼״̬
#define GAIN_ADJ_CMD2_GET_ADJ_DATA		0x03//��ȡУ׼����

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
void MsgHandleSetParam( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetParam( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleSetTable( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetTable( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleSetDevReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetDevReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleResetDev( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetFpgaReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleSetTopo( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetTopo( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleUpdateMCU( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleUpdateFPGA( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGetFlashPage( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleFlashOperatePage( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff ) ;
void MsgHandleStartAttAdj( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleAttStepAdj( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleEndAttAdj( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleFcScan( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleAck( UINT16 msg_length, UCHAR8 * p_msg_dat );
void MsgHandleNoiseTest( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGainAdj( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff );
void MsgHandleGainAdjEUAck( UINT16 msg_length, UCHAR8 * p_msg_dat);
void MsgHandleErrAlarm( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff  );
void MsgHandleGetEUParam( UINT16 msg_length, UCHAR8 * p_msg_dat );

#endif

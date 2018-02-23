/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :rec_app.c
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
#ifndef _REC_APP_H_
#define _REC_APP_H_


#define A_UP_PLL_LCK   (0X01<<0)   
#define A_DN_PLL_LCK   (0X01<<1)
#define B_UP_PLL_LCK   (0X01<<2)
#define B_DN_PLL_LCK   (0X01<<3)


#define GSM_FDM		942		    // GSM��������Ƶ�� 
#define GSM_FUM		897		    // GSM��������Ƶ�� 
#define GSM_FDL_OFFSET	92.24	// ����,�߱���,��Ƶ��Ƶ�ʼ�GSMƵ�ʵĲ�ֵ
#define GSM_FUL_OFFSET	93.72	// ����,�߱���,��Ƶ��Ƶ�ʼ�GSMƵ�ʵĲ�ֵ

#define WCDMA_FDM	2140	// WCDMA��������Ƶ�� 
#define WCDMA_FUM	1950	// WCDMA��������Ƶ�� 
#define WCDMA_FDL_OFFSET	(-92)	    // ����,�ͱ���,��Ƶ��Ƶ�ʼ�WCDMAƵ�ʵĲ�ֵ
#define WCDMA_FUL_OFFSET	(-91.44)	// ����,�ͱ���,��Ƶ��Ƶ�ʼ�WCDMAƵ�ʵĲ�ֵ
 
#define DEFAULT_GSM_FDL		    (GSM_FDM + GSM_FDL_OFFSET)
#define DEFAULT_GSM_FUL		    (GSM_FUM + GSM_FUL_OFFSET)
#define DEFAULT_WCDMA_FDL		(WCDMA_FDM + WCDMA_FDL_OFFSET)
#define DEFAULT_WCDMA_FUL		(WCDMA_FUM + WCDMA_FUL_OFFSET)

#define RF_DELAY_TIME_A		(13.97)//US A��ʵ����Ƶ��·ʱ��
#define RF_DELAY_TIME_B		(4.27)//US  B��ʵ����Ƶ��·ʱ��
#define RF_DELAY_TIME_C		(5.35)//US  C��ʵ����Ƶ��·ʱ��
#define RF_DELAY_TIME_D		(5.35)//US  D��ʵ����Ƶ��·ʱ��

#define IS_OPT_ENABLE( OPT_PORT )	( 0 != ( (1<<OPT_PORT)&fp_enable ) )
#define OPT_ENABLE( OPT_PORT )	    { fp_enable |= ( 1<<OPT_PORT ); }
#define OPT_DISABLE( OPT_PORT )	    { fp_enable &= (~(1<<OPT_PORT)); }

typedef struct _S_TOPO_STATUS 
{
	UINT32 IsTopoUnsteady:1;  //���˽ṹ�Ƿ��ȶ�
	UINT32 IsSendReqPkt:1;  // �Ƿ���RE��Ϣ��
	UINT32 IsGetReInfOk:1;  //�Ƿ���Ӧ��
	UINT32 ReAckTimeOut:5;  //REӦ��ʱ��  
	UINT32 UpdateCycDelay:5; 
} _T_TOPO_STATUS; 

typedef struct _S_NOISE_TEST_STATUS
{
	UCHAR8 test_mode;
	UCHAR8 mcu_control;
	UCHAR8 mode_change;
	UCHAR8 type;
	UCHAR8 value;
} _T_NOISE_TEST_STATUS;

extern UINT16 fp_enable;			// ��ڵ�ʹ��״̬: 1-ʹ��
extern UINT32 topo_ok_count;
extern UINT32 topo_err_count;
extern _T_TOPO_ALARM_INFO topo_alarm[FP_MAX][RE_MAX];



void EnableOpt();
void UpdateTopo();
void ClearTmpReInfo( UCHAR8 fp );
void ClearReInfo( UINT32 fp );
BOOL CheckReInfoUpdate();
void GetReInfo();
void CheckReID();
void UpdateWorkParam(UINT32 mask);
void CheckErrStatus();
void AutoProtect();
void SetTDParam_B();
void SetTDParam_C();
void SetTDParam_D();
void SetReUlPowerGain();
void SetReSysConfig();
void SetReTDParam();
void SetChannelByParam( UCHAR8 abcd_flag );
void SetReID( UCHAR8 fp, UCHAR8 re, UCHAR8 rf,  UCHAR8 id );
void SysLowPowerMode();
void SysNormalWorkMode();

void TdAutoSearchFp( UCHAR8 );

UCHAR8 CheckChannelSetA( void );
UCHAR8 CheckChannelSetB( void );
UCHAR8 CheckChannelSetC( void );
UCHAR8 CheckChannelSetD( void );
void NoiseTest(void);
void MAUSetParamToMEU(void);
void MAUGetParamFromMEU(void);
void MauGetMeuAlarm();


void SetAdjBenZhenSignalPara( void);
void ZiDongShiXiPeiBi( void);
void MoveBenZhenTo2340( void);
void MAUSetParamToMRU(void);
void GainAdjSetEUFrePoint(UCHAR8 ab_flag,INT32 freq_point);
void GainAdjSetEUEnterAdjMode(UCHAR8 ab_flag);
void GainAdjGetEUPow(UCHAR8 ab_flag, UCHAR8 ud_flag);
void GetPsfFromRe( UCHAR8 ab_flag, UCHAR8 ud_flag );


#endif

/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :sys_param.c
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
#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

// У׼RECʱ��ʹ�ñ����ֵ�8λ��
// У׼RE ʱ��ʹ�ñ����ָ�8λ��
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

//ģ�鹤���ؼ������޸ı�־
#define PCHG_A_CHANNEL				(1<<0)	// �ŵ��ź�ͨ��ʹ��
#define PCHG_A_LTHR					(1<<1)	// ��������
#define PCHG_A_POW_MODE			(1<<2)	// A�ι��ʿ���ģʽ
#define PCHG_A_WORK_EN			(1<<3)	// A�ι���ʹ��
#define PCHG_A_FL_CHG				(1<<4)	// A�α������
#define PCHG_A_POW_GAIN			(1<<5)	// ��������

#define PCHG_B_CHANNEL				(1<<6)	// �ŵ��ź�ͨ��ʹ��
#define PCHG_B_LTHR					(1<<7)	// ��������
#define PCHG_B_POW_MODE			(1<<8)	// B�ι��ʿ���ģʽ
#define PCHG_B_WORK_EN			(1<<9)	// B�ι���ʹ��
#define PCHG_B_FL_CHG				(1<<10)	// B�α������
#define PCHG_B_POW_GAIN			(1<<11)	// ��������

#define PCHG_C_CHANNEL				(1<<12)	// �ŵ��ź�ͨ��ʹ��
#define PCHG_C_LTHR					(1<<13)	// ��������
#define PCHG_C_POW_MODE			(1<<14)	// C�ι��ʿ���ģʽ
#define PCHG_C_WORK_EN			(1<<15)	// C�ι���ʹ��
#define PCHG_C_FL_CHG				(1<<16)	// C�α������
#define PCHG_C_POW_GAIN			(1<<17)	// ��������

#define PCHG_D_CHANNEL				(1<<18)	// �ŵ��ź�ͨ��ʹ��
#define PCHG_D_LTHR					(1<<19)	// ��������
#define PCHG_D_POW_MODE			(1<<20)	// D�ι��ʿ���ģʽ
#define PCHG_D_WORK_EN			(1<<21)	// D�ι���ʹ��
#define PCHG_D_FL_CHG				(1<<22)	// D�α������
#define PCHG_D_POW_GAIN			(1<<23)	// ��������

//#define PCHG_A_GAIN				(1<<3)	// ����
//#define PCHG_A_DL_POWER			(1<<2)	// ͨ������
//#define PCHG_A_UL_POWER			(1<<3)	// ͨ������
//#define PCHG_A_DL_GAIN				(1<<4)	// ��������
//#define PCHG_A_UL_GAIN				(1<<5)	// ��������
//#define PCHG_A_DL_ATT				(1<<6)	// ��������˥����
//#define PCHG_A_UL_ATT				(1<<7)	// ��������˥����
//#define PCHG_B_GAIN					(1<<19)	// ����
//#define PCHG_B_DL_POWER			(1<<18)	// ͨ������
//#define PCHG_B_UL_POWER			(1<<19)	// ͨ������
//#define PCHG_B_DL_GAIN				(1<<20)	// ��������
//#define PCHG_B_UL_GAIN				(1<<21)	// ��������
//#define PCHG_B_DL_ATT				(1<<22)	// ��������˥����
//#define PCHG_B_UL_ATT				(1<<23)	// ��������˥����

//#define PCHG_SYS_CFG				(1<<24)	// �޸�ϵͳ��������

#define PCHG_CENTER_FRE_FLAG		(1<<16)	// ��������Ƶ��

#define PCHG_BENZHEN_ADJ_FLAG		(1<<24)	// ���ñ���У׼����
#define PCHG_CTRL_BAUD				(1<<25)	// ���ƶ˿ڲ���������
#define PCHG_THR_CONFIG			(1<<26)	// ͸���˿�����

#define PCHG_FPS_RANGE				(1<<27)	// Ƶ�����ط�Χ
#define PCHG_LOW_POWER			(1<<28)	// �͹���ģʽ
#define PCHG_TD_PARAM				(1<<29)	// TD����
#define PCHG_OPT_DELAY				(1<<30)	// ��ڵĸ�����ʱֵ
#define PCHG_SYS_FP_EN				(1<<31)	// ���ʹ��

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

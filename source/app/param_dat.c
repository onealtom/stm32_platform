/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : param_dat.c
* Description : ϵͳ����������غ���
* Version     : v0.1
* Author      : RJ
* Date        : 2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			��ʼ�汾
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
	
	{	PARA_A_CHANNEL_COUNT	,PT_AP_G_EX|PT_US,	0,},	//	A��֧�ֵ�ͨ����
	{	PARA_A_DL_WORK_EN	,PT_AP_G_EX|PT_US,	0,},	//	A�����й���ʹ��
	{	PARA_A_UL_WORK_EN	,PT_AP_G_EX|PT_US,	0,},	//	A�����й���ʹ��
	{	PARA_A_DPOW_MODE	,PT_NC,	0,},	//	A�����й��ʿ��Ʒ�ʽ
	{	PARA_A_UPOW_MODE	,PT_NC,	0,},	//	A�����й��ʿ��Ʒ�ʽ
	{	PARA_A_LTHR_EN	,PT_AP_G_EX|PT_US,	1,},	//	A�����е�������ʹ��
	{	PARA_A_LTHR_UP	,PT_AP_G_EX|PT_NC,	1,},	//	A�ε�������������
	{	PARA_A_LTHR_DN	,PT_AP_G_EX|PT_SI,	1,},	//	A�ε�������������
	{	PARA_A_DCH_EN1	,PT_AP|PT_US,	1,},	//	A������ͨ������ʹ��1
	{	PARA_A_DCH_EN2	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��2
	{	PARA_A_DCH_EN3	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��3
	{	PARA_A_DCH_EN4	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��4
	{	PARA_A_DCH_EN5	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��5
	{	PARA_A_DCH_EN6	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��6
	{	PARA_A_DCH_EN7	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��7
	{	PARA_A_DCH_EN8	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��8
	{	PARA_A_DCH_EN9	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��9
	{	PARA_A_DCH_EN10	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��10
	{	PARA_A_DCH_EN11	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��11
	{	PARA_A_DCH_EN12	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��12
	{	PARA_A_DCH_EN13	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��13
	{	PARA_A_DCH_EN14	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��14
	{	PARA_A_DCH_EN15	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��15
	{	PARA_A_DCH_EN16	,PT_AP|PT_US,	0,},	//	A������ͨ������ʹ��16
	{	PARA_A_UCH_EN1	,PT_NC,	1,},	//	A������ͨ������ʹ��1
	{	PARA_A_UCH_EN2	,PT_NC,	0,},	//	A������ͨ������ʹ��2
	{	PARA_A_UCH_EN3	,PT_NC,	0,},	//	A������ͨ������ʹ��3
	{	PARA_A_UCH_EN4	,PT_NC,	0,},	//	A������ͨ������ʹ��4
	{	PARA_A_UCH_EN5	,PT_NC,	0,},	//	A������ͨ������ʹ��5
	{	PARA_A_UCH_EN6	,PT_NC,	0,},	//	A������ͨ������ʹ��6
	{	PARA_A_UCH_EN7	,PT_NC,	0,},	//	A������ͨ������ʹ��7
	{	PARA_A_UCH_EN8	,PT_NC,	0,},	//	A������ͨ������ʹ��8
	{	PARA_A_UCH_EN9	,PT_NC,	0,},	//	A������ͨ������ʹ��9
	{	PARA_A_UCH_EN10	,PT_NC,	0,},	//	A������ͨ������ʹ��10
	{	PARA_A_UCH_EN11	,PT_NC,	0,},	//	A������ͨ������ʹ��11
	{	PARA_A_UCH_EN12	,PT_NC,	0,},	//	A������ͨ������ʹ��12
	{	PARA_A_UCH_EN13	,PT_NC,	0,},	//	A������ͨ������ʹ��13
	{	PARA_A_UCH_EN14	,PT_NC,	0,},	//	A������ͨ������ʹ��14
	{	PARA_A_UCH_EN15	,PT_NC,	0,},	//	A������ͨ������ʹ��15
	{	PARA_A_UCH_EN16	,PT_NC,	0,},	//	A������ͨ������ʹ��16
	{	PARA_A_DCH_GAIN1	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������1
	{	PARA_A_DCH_GAIN2	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������2
	{	PARA_A_DCH_GAIN3	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������3
	{	PARA_A_DCH_GAIN4	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������4
	{	PARA_A_DCH_GAIN5	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������5
	{	PARA_A_DCH_GAIN6	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������6
	{	PARA_A_DCH_GAIN7	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������7
	{	PARA_A_DCH_GAIN8	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������8
	{	PARA_A_DCH_GAIN9	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������9
	{	PARA_A_DCH_GAIN10	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������10
	{	PARA_A_DCH_GAIN11	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������11
	{	PARA_A_DCH_GAIN12	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������12
	{	PARA_A_DCH_GAIN13	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������13
	{	PARA_A_DCH_GAIN14	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������14
	{	PARA_A_DCH_GAIN15	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������15
	{	PARA_A_DCH_GAIN16	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������16
	{	PARA_A_UCH_GAIN1	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������1
	{	PARA_A_UCH_GAIN2	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������2
	{	PARA_A_UCH_GAIN3	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������3
	{	PARA_A_UCH_GAIN4	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������4
	{	PARA_A_UCH_GAIN5	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������5
	{	PARA_A_UCH_GAIN6	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������6
	{	PARA_A_UCH_GAIN7	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������7
	{	PARA_A_UCH_GAIN8	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������8
	{	PARA_A_UCH_GAIN9	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������9
	{	PARA_A_UCH_GAIN10	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������10
	{	PARA_A_UCH_GAIN11	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������11
	{	PARA_A_UCH_GAIN12	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������12
	{	PARA_A_UCH_GAIN13	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������13
	{	PARA_A_UCH_GAIN14	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������14
	{	PARA_A_UCH_GAIN15	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������15
	{	PARA_A_UCH_GAIN16	,PT_AP_G_EX|PT_US,	40,},	//	A������ѡƵͨ���Ŵ�������16
	{	PARA_A_DCH_ATT1	,PT_AP_G_EX|PT_US,	0,},	//	A����������˥����1
	{	PARA_A_DCH_ATT2	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����2
	{	PARA_A_DCH_ATT3	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����3
	{	PARA_A_DCH_ATT4	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����4
	{	PARA_A_DCH_ATT5	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����5
	{	PARA_A_DCH_ATT6	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����6
	{	PARA_A_DCH_ATT7	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����7
	{	PARA_A_DCH_ATT8	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����8
	{	PARA_A_DCH_ATT9	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����9
	{	PARA_A_DCH_ATT10	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����10
	{	PARA_A_DCH_ATT11	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����11
	{	PARA_A_DCH_ATT12	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����12
	{	PARA_A_DCH_ATT13	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����13
	{	PARA_A_DCH_ATT14	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����14
	{	PARA_A_DCH_ATT15	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����15
	{	PARA_A_DCH_ATT16	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����16
	{	PARA_A_UCH_ATT1	,PT_AP|PT_US,	0,},	//	A����������˥����1
	{	PARA_A_UCH_ATT2	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����2
	{	PARA_A_UCH_ATT3	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����3
	{	PARA_A_UCH_ATT4	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����4
	{	PARA_A_UCH_ATT5	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����5
	{	PARA_A_UCH_ATT6	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����6
	{	PARA_A_UCH_ATT7	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����7
	{	PARA_A_UCH_ATT8	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����8
	{	PARA_A_UCH_ATT9	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����9
	{	PARA_A_UCH_ATT10	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����10
	{	PARA_A_UCH_ATT11	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����11
	{	PARA_A_UCH_ATT12	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����12
	{	PARA_A_UCH_ATT13	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����13
	{	PARA_A_UCH_ATT14	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����14
	{	PARA_A_UCH_ATT15	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����15
	{	PARA_A_UCH_ATT16	,PT_AP_G_EX|PT_NC,	0,},	//	A����������˥����16
	{	PARA_A_DL_PA_GAIN	,PT_NC,	0,},	//	A�����й�������
	{	PARA_A_UL_PA_GAIN	,PT_NC,	0,},	//	A�����й�������
	{	PARA_A_TX_PLL_ST	,PT_AP|PT_RO|PT_US,	0,},	//	A������PLL״̬,287 2ΪTX_VCO����������ʧ��
	{	PARA_A_RX_PLL_ST	,PT_AP|PT_RO|PT_US,	0,},	//	A������PLL״̬,247 2ΪRX_VCO����������ʧ��
	{	PARA_A_INIT_DA_ST	,PT_AP_G_EX|PT_NC,	0,},	//	��ʼ��A��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
	{	PARA_A_BB_PLL_LOCK	,PT_AP_G_EX|PT_NC,	0,},	//	A��DA PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
	{	PARA_A_FSAT	,PT_NC,	0,},	//	A��ǰ��AD����״̬
	{	PARA_A_DSAT	,PT_NC,	0,},	//	A�κ��DA���״̬
	{	PARA_A_PA_VG_EN	,PT_NC,	0,},	//	A�ι���դѹ״̬
	{	PARA_A_PA_VT	,PT_NC,	0,},	//	A�ι��Źܵ�ѹ��ʾ
	{	PARA_A_Modulator_EN	,PT_NC,	0,},	//	A�ε�����״̬
	{	PARA_A_LNA_VT	,PT_NC,	0,},	//	A�����е����LNA��ѹ
	{	PARA_A_LNA1_ST	,PT_RO|PT_US,	0,},	//	����LNA1״̬
	{	PARA_A_LNA2_ST	,PT_RO|PT_US,	0,},	//	����LNA2״̬
	{	PARA_A_BUSY_TIME	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_SI,	0,},	//	A������ʱ϶ռ����
	{	PARA_A_PRI_ADD,		PT_AP_G_EX|PT_RO|PT_US,	1,},	//	A��ģ���ַ
	{	PARA_A_UL_POW_1B, 	PT_AP_G|PT_SI, 	0,},	//	A�����������ܹ���
	{	PARA_A_DL_POW_1B, 	PT_AP_G_EX|PT_RO|PT_SI, 	0,},	//	A�����������ܹ���
	{	PARA_A_DCH_REC_RF_ATT1,		PT_AP_G_EX|PT_US, 	0},	 // REC�˵���������˥��������RF�˵���·����˥���� RF 
	{	PARA_A_UCH_REC_RF_ATT1,		PT_AP_G_EX|PT_US, 	0},	 // REC�˵���������˥��������RF�˵���·����˥���� RF 
	{	PARA_B_CHANNEL_COUNT	, PT_BP_G_EX|PT_US,	0,},	//	B��֧�ֵ�ͨ����
	{	PARA_B_DL_WORK_EN	,PT_BP_G_EX|PT_US,	1,},	//	B�����й���ʹ��
	{	PARA_B_UL_WORK_EN	,PT_BP_G_EX|PT_US,	1,},	//	B�����й���ʹ��
	{	PARA_B_DPOW_MODE	,PT_NC,	0,},	//	B�����й��ʿ��Ʒ�ʽ
	{	PARA_B_UPOW_MODE	,PT_NC,	0,},	//	B�����й��ʿ��Ʒ�ʽ
	{	PARA_B_LTHR_EN	,PT_BP_G_EX|PT_US,	0,},	//	B�����е�������ʹ��
	{	PARA_B_LTHR_UP	,PT_BP_G_EX|PT_NC,	0,},	//	B�ε�������������
	{	PARA_B_LTHR_DN	,PT_BP_G_EX|PT_SI,	0,},	//	B�ε�������������
	{	PARA_B_DCH_EN1		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��1
	{	PARA_B_DCH_EN2		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��2
	{	PARA_B_DCH_EN3		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��3
	{	PARA_B_DCH_EN4		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��4
	{	PARA_B_DCH_EN5		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��5
	{	PARA_B_DCH_EN6		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��6
	{	PARA_B_DCH_EN7		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��7
	{	PARA_B_DCH_EN8		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��8
	{	PARA_B_DCH_EN9		,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��9
	{	PARA_B_DCH_EN10	,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��10
	{	PARA_B_DCH_EN11	,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��11
	{	PARA_B_DCH_EN12	,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��12
	{	PARA_B_DCH_EN13	,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��13
	{	PARA_B_DCH_EN14	,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��14
	{	PARA_B_DCH_EN15	,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��15
	{	PARA_B_DCH_EN16	,PT_BP|PT_US,	1,},	//	B������ͨ������ʹ��16
	{	PARA_B_UCH_EN1		,PT_US,	1,},	//	B������ͨ������ʹ��1
	{	PARA_B_UCH_EN2		,PT_US,	1,},	//	B������ͨ������ʹ��2
	{	PARA_B_UCH_EN3		,PT_US,	1,},	//	B������ͨ������ʹ��3
	{	PARA_B_UCH_EN4		,PT_US,	1,},	//	B������ͨ������ʹ��4
	{	PARA_B_UCH_EN5		,PT_US,	1,},	//	B������ͨ������ʹ��5
	{	PARA_B_UCH_EN6		,PT_US,	1,},	//	B������ͨ������ʹ��6
	{	PARA_B_UCH_EN7		,PT_US,	1,},	//	B������ͨ������ʹ��7
	{	PARA_B_UCH_EN8		,PT_US,	1,},	//	B������ͨ������ʹ��8
	{	PARA_B_UCH_EN9		,PT_US,	1,},	//	B������ͨ������ʹ��9
	{	PARA_B_UCH_EN10	,PT_US,	1,},	//	B������ͨ������ʹ��10
	{	PARA_B_UCH_EN11	,PT_US,	1,},	//	B������ͨ������ʹ��11
	{	PARA_B_UCH_EN12	,PT_US,	1,},	//	B������ͨ������ʹ��12
	{	PARA_B_UCH_EN13	,PT_US,	1,},	//	B������ͨ������ʹ��13
	{	PARA_B_UCH_EN14	,PT_US,	1,},	//	B������ͨ������ʹ��14
	{	PARA_B_UCH_EN15	,PT_US,	1,},	//	B������ͨ������ʹ��15
	{	PARA_B_UCH_EN16	,PT_US,	1,},	//	B������ͨ������ʹ��16
	{	PARA_B_DCH_GAIN1	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������1
	{	PARA_B_DCH_GAIN2	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������2
	{	PARA_B_DCH_GAIN3	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������3
	{	PARA_B_DCH_GAIN4	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������4
	{	PARA_B_DCH_GAIN5	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������5
	{	PARA_B_DCH_GAIN6	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������6
	{	PARA_B_DCH_GAIN7	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������7
	{	PARA_B_DCH_GAIN8	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������8
	{	PARA_B_DCH_GAIN9	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������9
	{	PARA_B_DCH_GAIN10	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������10
	{	PARA_B_DCH_GAIN11	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������11
	{	PARA_B_DCH_GAIN12	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������12
	{	PARA_B_DCH_GAIN13	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������13
	{	PARA_B_DCH_GAIN14	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������14
	{	PARA_B_DCH_GAIN15	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������15
	{	PARA_B_DCH_GAIN16	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������16
	{	PARA_B_UCH_GAIN1	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������1
	{	PARA_B_UCH_GAIN2	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������2
	{	PARA_B_UCH_GAIN3	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������3
	{	PARA_B_UCH_GAIN4	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������4
	{	PARA_B_UCH_GAIN5	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������5
	{	PARA_B_UCH_GAIN6	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������6
	{	PARA_B_UCH_GAIN7	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������7
	{	PARA_B_UCH_GAIN8	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������8
	{	PARA_B_UCH_GAIN9	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������9
	{	PARA_B_UCH_GAIN10	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������10
	{	PARA_B_UCH_GAIN11	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������11
	{	PARA_B_UCH_GAIN12	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������12
	{	PARA_B_UCH_GAIN13	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������13
	{	PARA_B_UCH_GAIN14	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������14
	{	PARA_B_UCH_GAIN15	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������15
	{	PARA_B_UCH_GAIN16	,PT_BP_G_EX|PT_US,	40,},	//	B������ѡƵͨ���Ŵ�������16
	{	PARA_B_DCH_ATT1	,PT_BP_G_EX|PT_US,	0,},	//	B�������������˥����1
	{	PARA_B_DCH_ATT2	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����2
	{	PARA_B_DCH_ATT3	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����3
	{	PARA_B_DCH_ATT4	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����4
	{	PARA_B_DCH_ATT5	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����5
	{	PARA_B_DCH_ATT6	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����6
	{	PARA_B_DCH_ATT7	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����7
	{	PARA_B_DCH_ATT8	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����8
	{	PARA_B_DCH_ATT9	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����9
	{	PARA_B_DCH_ATT10	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����10
	{	PARA_B_DCH_ATT11	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����11
	{	PARA_B_DCH_ATT12	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����12
	{	PARA_B_DCH_ATT13	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����13
	{	PARA_B_DCH_ATT14	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����14
	{	PARA_B_DCH_ATT15	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����15
	{	PARA_B_DCH_ATT16	,PT_BP_G_EX|PT_NC,	0,},	//	B�������������˥����16
	{	PARA_B_UCH_ATT1	,PT_BP|PT_US,	0,},	//	B��������������˥����1(����������˥����)
	{	PARA_B_UCH_ATT2	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����2
	{	PARA_B_UCH_ATT3	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����3
	{	PARA_B_UCH_ATT4	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����4
	{	PARA_B_UCH_ATT5	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����5
	{	PARA_B_UCH_ATT6	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����6
	{	PARA_B_UCH_ATT7	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����7
	{	PARA_B_UCH_ATT8	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����8
	{	PARA_B_UCH_ATT9	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����9
	{	PARA_B_UCH_ATT10	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����10
	{	PARA_B_UCH_ATT11	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����11
	{	PARA_B_UCH_ATT12	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����12
	{	PARA_B_UCH_ATT13	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����13
	{	PARA_B_UCH_ATT14	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����14
	{	PARA_B_UCH_ATT15	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����15
	{	PARA_B_UCH_ATT16	,PT_BP_G_EX|PT_NC,	0,},	//	B��������������˥����16
	{	PARA_B_DL_PA_GAIN	,PT_NC,	0,},	//	B�����й�������
	{	PARA_B_UL_PA_GAIN	,PT_NC,	0,},	//	B�����й�������
	{	PARA_B_TX_PLL_ST	,PT_BP|PT_RO|PT_US,	0,},	//	B������PLL״̬,287 2ΪTX_VCO����������ʧ��
	{	PARA_B_RX_PLL_ST	,PT_BP|PT_RO|PT_US,	0,},	//	B������PLL״̬,247 2ΪRX_VCO����������ʧ��
	{	PARA_B_INIT_DA_ST	,PT_NC,	0,},	//	��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
	{	PARA_B_BB_PLL_LOCK	,PT_NC,	0,},	//	B��DA PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
	{	PARA_B_FSAT	,PT_NC,	0,},	//	B��ǰ��AD����״̬
	{	PARA_B_DSAT	,PT_NC,	0,},	//	B�κ��DA���״̬
	{	PARA_B_PA_VG_EN	,PT_NC,	0,},	//	B�ι���դѹ״̬
	{	PARA_B_PA_VT	,PT_NC,	0,},	//	B�ι��Źܵ�ѹ��ʾ
	{	PARA_B_Modulator_EN	,PT_NC,	0,},	//	B�ε�����״̬
	{	PARA_B_LNA_VT	,PT_NC,	0,},	//	B�����е����LNA��ѹ
	{	PARA_B_LNA1_ST	,PT_RO|PT_US,	0,},	//	����LNA1״̬
	{	PARA_B_LNA2_ST	,PT_RO|PT_US,	0,},	//	����LNA2״̬
	{	PARA_B_BUSY_TIME	,PT_RO|PT_SI,	0,},	//	B������ʱ϶ռ����
	{	PARA_B_PRI_ADD,		PT_BP_G_EX|PT_RO|PT_US,	2,},	//	B��ģ���ַ
	{	PARA_B_UL_POW_1B, 	/*PT_BP_G|*/PT_SI, 	0,},	//	B�����������ܹ���
	{	PARA_B_DL_POW_1B, 	PT_BP_G_EX|PT_RO|PT_SI, 	0,},	//	B�����������ܹ���
	{	PARA_B_DCH_REC_RF_ATT1,		PT_BP_G_EX|PT_US, 	0},	 // REC�˵���������˥��������RF�˵���·����˥���� RF 
	{	PARA_B_UCH_REC_RF_ATT1,		PT_BP_G_EX|PT_US, 	0},	 // REC�˵���������˥��������RF�˵���·����˥���� RF 
	{	PARA_C_CHANNEL_COUNT	, PT_CP_G_EX|PT_US,	0,},	//	C��֧�ֵ�ͨ����
	{	PARA_C_DL_WORK_EN	,PT_CP_G_EX|PT_US,	1,},	//	C�����й���ʹ��
	{	PARA_C_UL_WORK_EN	,PT_CP_G_EX|PT_US,	1,},	//	C�����й���ʹ��
	{	PARA_C_DPOW_MODE	,PT_NC,	0,},	//	C�����й��ʿ��Ʒ�ʽ
	{	PARA_C_UPOW_MODE	,PT_NC,	0,},	//	C�����й��ʿ��Ʒ�ʽ
	{	PARA_C_LTHR_EN	,PT_CP_G_EX|PT_US,	0,},	//	C�����е�������ʹ��
	{	PARA_C_LTHR_UP	,PT_CP_G_EX|PT_NC,	0,},	//	C�ε�������������
	{	PARA_C_LTHR_DN	,PT_CP_G_EX|PT_SI,	0,},	//	C�ε�������������
	{	PARA_C_DCH_EN1  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��1
	{	PARA_C_DCH_EN2  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��2
	{	PARA_C_DCH_EN3  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��3
	{	PARA_C_DCH_EN4  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��4
	{	PARA_C_DCH_EN5  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��5
	{	PARA_C_DCH_EN6  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��6
	{	PARA_C_DCH_EN7  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��7
	{	PARA_C_DCH_EN8  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��8
	{	PARA_C_DCH_EN9  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��9
	{	PARA_C_DCH_EN10  ,PT_CP|PT_US, 1,}, // C������ͨ������ʹ��10
	{	PARA_C_UCH_EN1		,PT_US,	1,},	//	C������ͨ������ʹ��1
	{	PARA_C_UCH_EN2		,PT_US,	1,},	//	C������ͨ������ʹ��2
	{	PARA_C_UCH_EN3		,PT_US,	1,},	//	C������ͨ������ʹ��3
	{	PARA_C_UCH_EN4		,PT_US,	1,},	//	C������ͨ������ʹ��4
	{	PARA_C_UCH_EN5		,PT_US,	1,},	//	C������ͨ������ʹ��5
	{	PARA_C_UCH_EN6		,PT_US,	1,},	//	C������ͨ������ʹ��6
	{	PARA_C_UCH_EN7		,PT_US,	1,},	//	C������ͨ������ʹ��7
	{	PARA_C_UCH_EN8		,PT_US,	1,},	//	C������ͨ������ʹ��8
	{	PARA_C_UCH_EN9		,PT_US,	1,},	//	C������ͨ������ʹ��9
	{	PARA_C_UCH_EN10		,PT_US,	1,},	//	C������ͨ������ʹ��10
	{	PARA_C_DCH_GAIN1	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������1
	{	PARA_C_DCH_GAIN2	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������2
	{	PARA_C_DCH_GAIN3	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������3
	{	PARA_C_DCH_GAIN4	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������4
	{	PARA_C_DCH_GAIN5	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������5
	{	PARA_C_DCH_GAIN6	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������6
	{	PARA_C_DCH_GAIN7	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������7
	{	PARA_C_DCH_GAIN8	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������8
	{	PARA_C_DCH_GAIN9	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������9
	{	PARA_C_DCH_GAIN10	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������10
	{	PARA_C_DCH_GAIN11	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������11
	{	PARA_C_DCH_GAIN12	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������12
	{	PARA_C_DCH_GAIN13	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������13
	{	PARA_C_DCH_GAIN14	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������14
	{	PARA_C_DCH_GAIN15	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������15
	{	PARA_C_DCH_GAIN16	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������16
	{	PARA_C_UCH_GAIN1	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������1
	{	PARA_C_UCH_GAIN2	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������2
	{	PARA_C_UCH_GAIN3	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������3
	{	PARA_C_UCH_GAIN4	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������4
	{	PARA_C_UCH_GAIN5	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������5
	{	PARA_C_UCH_GAIN6	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������6
	{	PARA_C_UCH_GAIN7	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������7
	{	PARA_C_UCH_GAIN8	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������8
	{	PARA_C_UCH_GAIN9	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������9
	{	PARA_C_UCH_GAIN10	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������10
	{	PARA_C_UCH_GAIN11	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������11
	{	PARA_C_UCH_GAIN12	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������12
	{	PARA_C_UCH_GAIN13	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������13
	{	PARA_C_UCH_GAIN14	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������14
	{	PARA_C_UCH_GAIN15	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������15
	{	PARA_C_UCH_GAIN16	,PT_CP_G_EX|PT_US,	40,},	//	C������ѡƵͨ���Ŵ�������16
	{	PARA_C_DCH_ATT1	,PT_CP_G_EX|PT_US,	0,},	//	C�������������˥����1
	{	PARA_C_DCH_ATT2	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����2
	{	PARA_C_DCH_ATT3	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����3
	{	PARA_C_DCH_ATT4	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����4
	{	PARA_C_DCH_ATT5	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����5
	{	PARA_C_DCH_ATT6	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����6
	{	PARA_C_DCH_ATT7	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����7
	{	PARA_C_DCH_ATT8	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����8
	{	PARA_C_DCH_ATT9	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����9
	{	PARA_C_DCH_ATT10	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����10
	{	PARA_C_DCH_ATT11	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����11
	{	PARA_C_DCH_ATT12	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����12
	{	PARA_C_DCH_ATT13	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����13
	{	PARA_C_DCH_ATT14	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����14
	{	PARA_C_DCH_ATT15	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����15
	{	PARA_C_DCH_ATT16	,PT_CP_G_EX|PT_NC,	0,},	//	C�������������˥����16
	{	PARA_C_UCH_ATT1	,PT_CP|PT_US,	0,},	//	C��������������˥����1
	{	PARA_C_UCH_ATT2	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����2
	{	PARA_C_UCH_ATT3	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����3
	{	PARA_C_UCH_ATT4	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����4
	{	PARA_C_UCH_ATT5	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����5
	{	PARA_C_UCH_ATT6	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����6
	{	PARA_C_UCH_ATT7	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����7
	{	PARA_C_UCH_ATT8	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����8
	{	PARA_C_UCH_ATT9	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����9
	{	PARA_C_UCH_ATT10	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����10
	{	PARA_C_UCH_ATT11	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����11
	{	PARA_C_UCH_ATT12	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����12
	{	PARA_C_UCH_ATT13	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����13
	{	PARA_C_UCH_ATT14	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����14
	{	PARA_C_UCH_ATT15	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����15
	{	PARA_C_UCH_ATT16	,PT_CP_G_EX|PT_NC,	0,},	//	C��������������˥����16
	{	PARA_C_DL_PA_GAIN	,PT_NC,	0,},	//	C�����й�������
	{	PARA_C_UL_PA_GAIN	,PT_NC,	0,},	//	C�����й�������
	{	PARA_C_TX_PLL_ST	,PT_CP|PT_RO|PT_US,	0,},	//	C������PLL״̬,287 2ΪTX_VCO����������ʧ��
	{	PARA_C_RX_PLL_ST	,PT_CP|PT_RO|PT_US,	0,},	//	C������PLL״̬,247 2ΪRX_VCO����������ʧ��
	{	PARA_C_INIT_DA_ST	,PT_NC,	0,},	//	��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
	{	PARA_C_BB_PLL_LOCK	,PT_NC,	0,},	//	C��DA PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
	{	PARA_C_FSAT	,PT_NC,	0,},	//	C��ǰ��AD����״̬
	{	PARA_C_DSAT	,PT_NC,	0,},	//	C�κ��DA���״̬
	{	PARA_C_PA_VG_EN	,PT_NC,	0,},	//	C�ι���դѹ״̬
	{	PARA_C_PA_VT	,PT_NC,	0,},	//	C�ι��Źܵ�ѹ��ʾ
	{	PARA_C_Modulator_EN	,PT_NC,	0,},	//	C�ε�����״̬
	{	PARA_C_LNA_VT	,PT_NC,	0,},	//	C�����е����LNA��ѹ
	{	PARA_C_LNA1_ST	,PT_RO|PT_US,	0,},	//	����LNA1״̬
	{	PARA_C_LNA2_ST	,PT_RO|PT_US,	0,},	//	����LNA2״̬
	{	PARA_C_BUSY_TIME	,PT_RO|PT_SI,	0,},	//	C������ʱ϶ռ����
	{	PARA_C_PRI_ADD,  PT_CP_G_EX|PT_RO|PT_US, 3,}, // C��ģ���ַ
	{	PARA_C_UL_POW_1B, 	/*PT_BP_G|*/PT_SI, 	0,},	//	C�����������ܹ���
	{	PARA_C_DL_POW_1B, 	PT_CP_G_EX|PT_RO|PT_SI, 	0,},	//	C�����������ܹ���
	{	PARA_C_DCH_REC_RF_ATT1,		PT_CP_G_EX|PT_US, 	0},	 // REC�˵���������˥��������RF�˵���·����˥���� RF 
	{	PARA_C_UCH_REC_RF_ATT1,		PT_CP_G_EX|PT_US, 	0},	 // REC�˵���������˥��������RF�˵���·����˥���� RF 
	{	PARA_D_CHANNEL_COUNT	, PT_DP_G_EX|PT_US,	0,},	//	D��֧�ֵ�ͨ����
	{	PARA_D_DL_WORK_EN	,PT_DP_G_EX|PT_US,	1,},	//	D�����й���ʹ��
	{	PARA_D_UL_WORK_EN	,PT_DP_G_EX|PT_US,	1,},	//	D�����й���ʹ��
	{	PARA_D_DPOW_MODE	,PT_NC,	0,},	//	D�����й��ʿ��Ʒ�ʽ
	{	PARA_D_UPOW_MODE	,PT_NC,	0,},	//	D�����й��ʿ��Ʒ�ʽ
	{	PARA_D_LTHR_EN	,PT_DP_G_EX|PT_US,	0,},	//	D�����е�������ʹ��
	{	PARA_D_LTHR_UP	,PT_DP_G_EX|PT_NC,	0,},	//	D�ε�������������
	{	PARA_D_LTHR_DN	,PT_DP_G_EX|PT_SI,	0,},	//	D�ε�������������
	{	PARA_D_DCH_EN1  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��1
	{	PARA_D_DCH_EN2  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��2
	{	PARA_D_DCH_EN3  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��3
	{	PARA_D_DCH_EN4  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��4
	{	PARA_D_DCH_EN5  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��5
	{	PARA_D_DCH_EN6  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��6
	{	PARA_D_DCH_EN7  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��7
	{	PARA_D_DCH_EN8  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��8
	{	PARA_D_DCH_EN9  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��9
	{	PARA_D_DCH_EN10  ,PT_DP|PT_US, 1,}, // D������ͨ������ʹ��10
	{	PARA_D_UCH_EN1		,PT_US, 1,},	//	D������ͨ������ʹ��1
	{	PARA_D_UCH_EN2		,PT_US, 1,},	//	D������ͨ������ʹ��2
	{	PARA_D_UCH_EN3		,PT_US, 1,},	//	D������ͨ������ʹ��3
	{	PARA_D_UCH_EN4		,PT_US, 1,},	//	D������ͨ������ʹ��4
	{	PARA_D_UCH_EN5		,PT_US, 1,},	//	D������ͨ������ʹ��5
	{	PARA_D_UCH_EN6		,PT_US, 1,},	//	D������ͨ������ʹ��6
	{	PARA_D_UCH_EN7		,PT_US, 1,},	//	D������ͨ������ʹ��7
	{	PARA_D_UCH_EN8		,PT_US, 1,},	//	D������ͨ������ʹ��8
	{	PARA_D_UCH_EN9		,PT_US, 1,},	//	D������ͨ������ʹ��9
	{	PARA_D_UCH_EN10 	,PT_US, 1,},	//	D������ͨ������ʹ��10
	{	PARA_D_DCH_GAIN1	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������1
	{	PARA_D_DCH_GAIN2	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������2
	{	PARA_D_DCH_GAIN3	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������3
	{	PARA_D_DCH_GAIN4	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������4
	{	PARA_D_DCH_GAIN5	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������5
	{	PARA_D_DCH_GAIN6	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������6
	{	PARA_D_DCH_GAIN7	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������7
	{	PARA_D_DCH_GAIN8	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������8
	{	PARA_D_DCH_GAIN9	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������9
	{	PARA_D_DCH_GAIN10	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������10
	{	PARA_D_DCH_GAIN11	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������11
	{	PARA_D_DCH_GAIN12	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������12
	{	PARA_D_DCH_GAIN13	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������13
	{	PARA_D_DCH_GAIN14	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������14
	{	PARA_D_DCH_GAIN15	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������15
	{	PARA_D_DCH_GAIN16	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������16
	{	PARA_D_UCH_GAIN1	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������1
	{	PARA_D_UCH_GAIN2	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������2
	{	PARA_D_UCH_GAIN3	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������3
	{	PARA_D_UCH_GAIN4	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������4
	{	PARA_D_UCH_GAIN5	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������5
	{	PARA_D_UCH_GAIN6	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������6
	{	PARA_D_UCH_GAIN7	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������7
	{	PARA_D_UCH_GAIN8	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������8
	{	PARA_D_UCH_GAIN9	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������9
	{	PARA_D_UCH_GAIN10	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������10
	{	PARA_D_UCH_GAIN11	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������11
	{	PARA_D_UCH_GAIN12	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������12
	{	PARA_D_UCH_GAIN13	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������13
	{	PARA_D_UCH_GAIN14	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������14
	{	PARA_D_UCH_GAIN15	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������15
	{	PARA_D_UCH_GAIN16	,PT_DP_G_EX|PT_US,	40,},	//	D������ѡƵͨ���Ŵ�������16
	{	PARA_D_DCH_ATT1	,PT_DP_G_EX|PT_US,	0,},	//	D�������������˥����1
	{	PARA_D_DCH_ATT2	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����2
	{	PARA_D_DCH_ATT3	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����3
	{	PARA_D_DCH_ATT4	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����4
	{	PARA_D_DCH_ATT5	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����5
	{	PARA_D_DCH_ATT6	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����6
	{	PARA_D_DCH_ATT7	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����7
	{	PARA_D_DCH_ATT8	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����8
	{	PARA_D_DCH_ATT9	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����9
	{	PARA_D_DCH_ATT10	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����10
	{	PARA_D_DCH_ATT11	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����11
	{	PARA_D_DCH_ATT12	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����12
	{	PARA_D_DCH_ATT13	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����13
	{	PARA_D_DCH_ATT14	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����14
	{	PARA_D_DCH_ATT15	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����15
	{	PARA_D_DCH_ATT16	,PT_DP_G_EX|PT_NC,	0,},	//	D�������������˥����16
	{	PARA_D_UCH_ATT1	,PT_DP|PT_US,	0,},	//	D��������������˥����1
	{	PARA_D_UCH_ATT2	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����2
	{	PARA_D_UCH_ATT3	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����3
	{	PARA_D_UCH_ATT4	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����4
	{	PARA_D_UCH_ATT5	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����5
	{	PARA_D_UCH_ATT6	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����6
	{	PARA_D_UCH_ATT7	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����7
	{	PARA_D_UCH_ATT8	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����8
	{	PARA_D_UCH_ATT9	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����9
	{	PARA_D_UCH_ATT10	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����10
	{	PARA_D_UCH_ATT11	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����11
	{	PARA_D_UCH_ATT12	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����12
	{	PARA_D_UCH_ATT13	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����13
	{	PARA_D_UCH_ATT14	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����14
	{	PARA_D_UCH_ATT15	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����15
	{	PARA_D_UCH_ATT16	,PT_DP_G_EX|PT_NC,	0,},	//	D��������������˥����16
	{	PARA_D_DL_PA_GAIN	,PT_NC,	0,},	//	D�����й�������
	{	PARA_D_UL_PA_GAIN	,PT_NC,	0,},	//	D�����й�������
	{	PARA_D_TX_PLL_ST	,PT_DP|PT_RO|PT_US,	0,},	//	D������PLL״̬,287 2ΪTX_VCO����������ʧ��
	{	PARA_D_RX_PLL_ST	,PT_DP|PT_RO|PT_US,	0,},	//	D������PLL״̬,247 2ΪRX_VCO����������ʧ��
	{	PARA_D_INIT_DA_ST	,PT_NC,	0,},	//	��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
	{	PARA_D_BB_PLL_LOCK	,PT_NC,	0,},	//	D��DA PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
	{	PARA_D_FSAT	,PT_NC,	0,},	//	D��ǰ��AD����״̬
	{	PARA_D_DSAT	,PT_NC,	0,},	//	D�κ��DA���״̬
	{	PARA_D_PA_VG_EN	,PT_NC,	0,},	//	D�ι���դѹ״̬
	{	PARA_D_PA_VT	,PT_NC,	0,},	//	D�ι��Źܵ�ѹ��ʾ
	{	PARA_D_Modulator_EN	,PT_NC,	0,},	//	D�ε�����״̬
	{	PARA_D_LNA_VT	,PT_NC,	0,},	//	D�����е����LNA��ѹ
	{	PARA_D_LNA1_ST	,PT_RO|PT_US,	0,},	//	����LNA1״̬
	{	PARA_D_LNA2_ST	,PT_RO|PT_US,	0,},	//	����LNA2״̬
	{	PARA_D_BUSY_TIME	,PT_RO|PT_SI,	0,},	//	D������ʱ϶ռ����
	{ 	PARA_D_PRI_ADD,  PT_DP_G_EX|PT_RO|PT_US, 4,}, // D��ģ���ַ
	{	PARA_D_UL_POW_1B, 	/*PT_DP_G|*/PT_SI, 	0,},	//	D�����������ܹ���
	{	PARA_D_DL_POW_1B, 	PT_DP_G_EX|PT_RO|PT_SI, 	0,},	//	D�����������ܹ���
	{	PARA_D_DCH_REC_RF_ATT1,		PT_DP_G_EX|PT_US, 	0},	 // REC�˵���������˥��������RF�˵���·����˥���� RF 
	{	PARA_D_UCH_REC_RF_ATT1,		PT_DP_G_EX|PT_US, 	0},	 // REC�˵���������˥��������RF�˵���·����˥���� RF 
	{	PARA_FP1_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��1
	{	PARA_FP2_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��2
	{	PARA_FP3_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��3
	{	PARA_FP4_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��4
	{	PARA_FP5_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��5
	{	PARA_FP6_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��6
	{	PARA_FP7_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��7
	{	PARA_FP8_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��8
	{	PARA_FP9_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��9
	{	PARA_FP10_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��10
	{	PARA_FP11_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��11
	{	PARA_FP12_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��12
	{	PARA_FP13_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��13
	{	PARA_FP14_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��14
	{	PARA_FP15_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��15
	{	PARA_FP16_EN	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	1,},	//	��ڷ���ʹ��16
	{	PARA_FP1_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	�����λ״̬1, 0-��λ
	{	PARA_FP2_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	�����λ״̬2, 0-��λ
	{	PARA_FP3_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	�����λ״̬3, 0-��λ
	{	PARA_FP4_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	�����λ״̬4, 0-��λ
	{	PARA_FP5_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	�����λ״̬5, 0-��λ
	{	PARA_FP6_ON_POS	,PT_AP|PT_BP_G_EX|PT_US,	0,},	//	�����λ״̬6, 0-��λ
	{	PARA_FP7_ON_POS	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	0,},	//	�����λ״̬7, 0-��λ
	{	PARA_FP8_ON_POS	,PT_AP_G_EX|PT_BP_G_EX|PT_US,	0,},	//	�����λ״̬8, 0-��λ
	{	PARA_FP9_ON_POS	,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	�����λ״̬9, 0-��λ
	{	PARA_FP10_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	�����λ״̬10, 0-��λ
	{	PARA_FP11_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	�����λ״̬11, 0-��λ
	{	PARA_FP12_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	�����λ״̬12, 0-��λ
	{	PARA_FP13_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	�����λ״̬13, 0-��λ
	{	PARA_FP14_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	�����λ״̬14, 0-��λ
	{	PARA_FP15_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	�����λ״̬15, 0-��λ
	{	PARA_FP16_ON_POS,PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	//	�����λ״̬16, 0-��λ
	{	PARA_FP1_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���1�źŶ�ʧ״̬
	{	PARA_FP2_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���2�źŶ�ʧ״̬
	{	PARA_FP3_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���3�źŶ�ʧ״̬
	{	PARA_FP4_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���4�źŶ�ʧ״̬
	{	PARA_FP5_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���5�źŶ�ʧ״̬
	{	PARA_FP6_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���6�źŶ�ʧ״̬
	{	PARA_FP7_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���7�źŶ�ʧ״̬
	{	PARA_FP8_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���8�źŶ�ʧ״̬
	{	PARA_FP9_LOS	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���9�źŶ�ʧ״̬
	{	PARA_FP10_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���10�źŶ�ʧ״̬
	{	PARA_FP11_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���11�źŶ�ʧ״̬
	{	PARA_FP12_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���12�źŶ�ʧ״̬
	{	PARA_FP13_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���13�źŶ�ʧ״̬
	{	PARA_FP14_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���14�źŶ�ʧ״̬
	{	PARA_FP15_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���15�źŶ�ʧ״̬
	{	PARA_FP16_LOS,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���16�źŶ�ʧ״̬
	{	PARA_FP1_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���1֡��ʧ״̬
	{	PARA_FP2_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���2֡��ʧ״̬
	{	PARA_FP3_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���3֡��ʧ״̬
	{	PARA_FP4_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���4֡��ʧ״̬
	{	PARA_FP5_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���5֡��ʧ״̬
	{	PARA_FP6_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���6֡��ʧ״̬
	{	PARA_FP7_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���7֡��ʧ״̬
	{	PARA_FP8_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���8֡��ʧ״̬
	{	PARA_FP9_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���9֡��ʧ״̬
	{	PARA_FP10_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���10֡��ʧ״̬
	{	PARA_FP11_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���11֡��ʧ״̬
	{	PARA_FP12_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���12֡��ʧ״̬
	{	PARA_FP13_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���13֡��ʧ״̬
	{	PARA_FP14_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���14֡��ʧ״̬
	{	PARA_FP15_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���15֡��ʧ״̬
	{	PARA_FP16_LOF,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	���16֡��ʧ״̬
	{	PARA_OPT_LOF	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	֡��ʧ״̬
	{	PARA_SERDES1_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬1
	{	PARA_SERDES2_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬2
	{	PARA_SERDES3_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬3
	{	PARA_SERDES4_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬4
	{	PARA_SERDES5_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬5
	{	PARA_SERDES6_PLL_ST	,PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬6
	{	PARA_SERDES7_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬7
	{	PARA_SERDES8_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬8
	{	PARA_SERDES9_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬9
	{	PARA_SERDES10_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬10
	{	PARA_SERDES11_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬11
	{	PARA_SERDES12_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬12
	{	PARA_SERDES13_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬13
	{	PARA_SERDES14_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬14
	{	PARA_SERDES15_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬15
	{	PARA_SERDES16_PLL_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	SerDesоƬPLL״̬16
	{	PARA_TOPO_CHG_ALM	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	��·״̬�澯
	{	PARA_BER_ALARM		,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	������ƫ�߸澯
	{	PARA_LOAD_FPGA_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	����FPGA״̬
	{	PARA_FPGA_CLK_ST	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	FPGA����״̬
	{	PARA_INIT_CLK_ST	,PT_NC,	0,},	//	��ʼ��ʱ��״̬
	{	PARA_INIT_AD_ST		,PT_NC,	0,},	//	��ʼ��AD״̬
	{	PARA_INIT_FB_AD_ST	,PT_NC,	0,},	//	��ʼ������AD״̬
	{	PARA_CLK_PLL_ST	,	PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	CLK PLL״̬
	{	PARA_CLK_REF_ST	,	PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	CLK �ο�״̬
	{	PARA_RE_NODE_MODE,	PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	RE�ڵ�ģʽ
	{	PARA_BOARD_TEMP,	PT_AP_G|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	�����¶�
	{	PARA_CLK_VCO_VT,	PT_NC,	0,},	//	ʱ��VCO��ѹ
	{	PARA_PWR_9V0_VT,	PT_NC,	0,},	//	9V��Դ��ѹ
	{	PARA_PWR_5V5_VT,	PT_NC,	0,},	//	5.5V��Դ��ѹ
	{	PARA_PWR_3V6_VT,	PT_NC,	0,},	//	3.6V��Դ��ѹ
	{	PARA_PWR_1V2_VT,	PT_NC,	0,},	//	1.2V��Դ��ѹ
	{	PARA_PWR_2V5_VT,	PT_NC,	0,},	//	1.2V��Դ��ѹ
	{	PARA_PRI_PROTOCAL_V	,PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US,	0,},	//	Э��汾
	{	PARA_MODULE_HRI_ID,	PT_NC,	0,},	//	ID
	{	PARA_WORK_ERROR,	PT_NC,	0,},	// ϵͳ����״̬��1-�й���
	{	PARA_TRAFFIC_END, 	PT_AP_G_EX|PT_BP_G_EX|PT_NC,	0,},	// ϵͳ����״̬��1-�й���
	{	PARA_DELAY_MODE,	PT_AP_G|PT_BP_G|PT_US, 	1},		// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
	{	PARA_TD_SYNC_ST,		PT_BP|PT_RO|PT_US, 		0},		// TDͬ��״̬: 0-��ͬ����1-δͬ��
	{	PARA_TD_WORK_MODE, PT_BP|PT_US, 0 },		// [WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���, ÿ���ϵ������
	{	PARA_TD_T0_UD,		PT_BP_G_EX|PT_US, 	1},	// TDʱ϶0�����б�־:0-���У�1-����
	{	PARA_TD_T1_UD,		PT_BP_G_EX|PT_US, 	1},	// TDʱ϶1�����б�־:0-���У�1-����
	{	PARA_TD_T2_UD,		PT_BP_G_EX|PT_US, 	1},	// TDʱ϶2�����б�־:0-���У�1-����
	{	PARA_TD_T3_UD,		PT_BP_G_EX|PT_US, 	1},	// TDʱ϶3�����б�־:0-���У�1-����
	{	PARA_TD_T4_UD,		PT_BP_G_EX|PT_US, 	0},	// TDʱ϶4�����б�־:0-���У�1-����
	{	PARA_TD_T5_UD,		PT_BP_G_EX|PT_US, 	0},	// TDʱ϶5�����б�־:0-���У�1-����
	{	PARA_TD_T6_UD,		PT_BP_G_EX|PT_US, 	0},	// TDʱ϶6�����б�־:0-���У�1-����
	{	PARA_POWERUP_ST,	PT_AP_G_EX|PT_SI},	// 	���ְ��ϵ�״̬,ÿ������ʱ��1
	{	PARA_LOW_POWER,	PT_AP|PT_BP|PT_CP|PT_DP|PT_SI,	0 },	//	�͹���ģʽ:1-�͹���;	0-����
	{	PARA_THR_PORT,		PT_NC,	PARAM_INIT_THR_PORT},	// 	͸���˿�ѡ��0-485B, 1-RS232
	{	PARA_THR_BAUD,		PT_NC,	PARAM_INIT_THR_BAUD},	//	͸���˿ڲ����� 0-9600, 1-19200, 2-38400, 3-57600, 4-115200
	{	PARA_CTRL_BAUD,	PT_NC,	PARAM_INIT_CTRL_BAUD},	//	���ƶ˿ڲ����� 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
	{	PARA_WLAN_CONN_ST1,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN��״̬1: 0-������1-�쳣
	{	PARA_WLAN_CONN_ST2,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN��״̬2: 0-������1-�쳣
	{	PARA_WLAN_CONN_ST3,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN��״̬3: 0-������1-�쳣
	{	PARA_WLAN_CONN_ST4,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN��״̬4: 0-������1-�쳣
	{	PARA_WLAN_SPEED1,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},	// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
	{	PARA_WLAN_SPEED2,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
	{	PARA_WLAN_SPEED3,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
	{	PARA_WLAN_SPEED4,		PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0},		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
	{	PARA_GSM_BW_SEL,		PT_RO|PT_US,			0},		// ����汾GSM����ѡ��: 0-6M, 1-20M, 2-24M, 3-25M, ������Ч
	{	PARA_HX_DET_UADDR,		PT_NC,		0x31 }, // ����DETģ�����е�ַ, ��4λΪB��, ����λΪA��
	{	PARA_HX_LNA_UADDR,		PT_NC,		0x31 }, // ����LNAģ�����е�ַ, ��4λΪB��, ����λΪA��
	{	PARA_HX_DET_DADDR,		PT_NC,		0x42 }, // ����DETģ�����е�ַ, ��4λΪB��, ����λΪA��
	{	PARA_HX_LNA_DADDR,		PT_NC,		0x42 }, // ����LNAģ�����е�ַ, ��4λΪB��, ����λΪA��
	{	PARA_FPS_AUTO_SCAN,	PT_AP_G|PT_US,		0 },			// �Զ�Ƶ����������ʹ��:1-�Զ�����������Ƶ��, 0-�ֶ�����
	{	PARA_FPS_SWITCH_THD,	PT_NC, 		0 },			// �Զ�Ƶ��������BCCH�����л�����
	{	PARA_FPS_MOSVC_SEL,	PT_AP_G|PT_US, 		0 },	// Ƶ������: ��Ӫ��ѡ��: 0-���ƶ�, 1-����ͨ, 2-���ƶ�, 255-�Զ�ѡ��
	{	PARA_FPS_RFRANGE_SEL,	PT_AP_G|PT_US, 		0 },	// Ƶ������: Ƶ��ѡ��(����,��ģ����ʽΪ׼): 0-ȫƵ��, 1-900MHz, 2-1800MHz
	{	PARA_FPS_BS_ID,		PT_AP_G|PT_RO|PT_US, 		0 },	// Ƶ������: ��վʶ����
	{	PARA_FPS_CA_COUNT,		PT_AP_G|PT_RO|PT_US, 		0 },	// Ƶ������: ��Ч�ŵ���
	{	PARA_FPS_BCCH_LK_ST,	PT_AP_G|PT_RO|PT_US, 		0 },	// Ƶ������: ����BCCH״̬: 1-����, 0-ʧ��
	{	PARA_FPS_MOSVC_LK_ST,	PT_AP_G|PT_RO|PT_US, 		0 },	// Ƶ������: ������Ӫ��״̬: 1-����, 0-ʧ��
	{	PARA_FPS_RFRANGE_LK_ST,	PT_AP_G|PT_RO|PT_US, 		0 },	// Ƶ������: ����Ƶ��״̬: 1-����, 0-ʧ��
	{	PARA_FPS_BCCH_POW_M,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// Ƶ������: ��С��BCCH����ǿ��
	{	PARA_FPS_BCCH_POW_1,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// Ƶ������: ��С��1BCCH����ǿ��
	{	PARA_FPS_BCCH_POW_2,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// Ƶ������: ��С��2BCCH����ǿ��
	{	PARA_FPS_BCCH_POW_3,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// Ƶ������: ��С��3BCCH����ǿ��
	{	PARA_FPS_BCCH_POW_4,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// Ƶ������: ��С��4BCCH����ǿ��
	{	PARA_FPS_BCCH_POW_5,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// Ƶ������: ��С��5BCCH����ǿ��
	{	PARA_FPS_BCCH_POW_6,	PT_AP_G_EX|PT_RO|PT_US, 	(UCHAR8)(-120) },	// Ƶ������: ��С��6BCCH����ǿ��
	{	PARA_A_EXPA_WORK_EN,	PT_AP_G_EX|PT_US, 	0 },		// [WR]΢����: ��Ƶ�źſ���
	{	PARA_A_EXPA_DL_ATT,		PT_AP_G_EX|PT_US, 	0 },		// [WR]΢����: ����˥��ֵ
	{	PARA_A_EXPA_TEMP,		PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: �¶�
	{	PARA_A_EXPA_DL_POW,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: ����������ʵ�ƽ
	{	PARA_A_EXPA_SWR,		PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: ����פ����ֵ
	{	PARA_A_EXPA_POWER_DN,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: ��Դ����澯(3���Ӹ����ж�)
	{	PARA_A_EXPA_POWER_ERR,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: ��Դ���ϸ澯(3���Ӹ����ж�)
	{	PARA_A_EXPA_BATT_ERR,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: ���ģ���ع��ϸ澯(3���Ӹ����ж�)
	{	PARA_A_EXPA_POS_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: λ�ø澯
	{	PARA_A_EXPA_DOOR_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: �Ž��澯
	{	PARA_A_EXPA_WROK_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: ���й��Ź��ϸ澯(3���Ӹ����ж�)
	{	PARA_A_EXPA_EXT1_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: �ⲿ�澯1
	{	PARA_A_EXPA_EXT2_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: �ⲿ�澯2
	{	PARA_A_EXPA_EXT3_ALM,	PT_AP_G_EX|PT_RO|PT_US, 	0 },		// [RO]΢����: �ⲿ�澯3
	{	PARA_A_EXPA_MAX_GAIN,	PT_NC, 	0 },		// ΢����: ��˥�����棬���������
	{	PARA_A_EXPA_GAIN_THD,	PT_NC, 	0 },		// ΢����: �������ޣ������������������ֵ
	{	PARA_A_EXPA_POW_THD,	PT_NC, 	0 },		// ΢����: ���������������
	{	PARA_A_EXPA_POD_CMP,	PT_NC,	0 },		// ΢����: �첨�ܹ��ʼ�ⲹ��ֵ,1�ֽ��з�����,���չ���Ϊ�첨�ܹ��ʼ��ϲ���ֵ
	{	PARA_MONITOR_VOL_OVER_THR, 				PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0},			 // ��ص�ѹ������
	{	PARA_MONITOR_VOL_OWE_THR,				PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0},			 // ��ص�ѹǷ����
	{	PARA_DIGITAL_SINGNAL_ALARM,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // �����ź��쳣�澯
	{	PARA_HOST_DEVICE_LINK_SINGNAL_ALARM,    PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // ���Ӽ����·�澯
	{	PARA_MONITOR_BATTERY_ALARM,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // ���ģ���ع��ϸ澯
	{	PARA_LOW_POWER_ALARM,    				PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 //// ��Դ����澯
	{	PARA_BATTERY_BREAKDOWN_ALARM,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 //// ��Դ���ϸ澯
	{	PARA_POSITION_MOVE_ALARM,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0},			 // λ�ø澯
	{	PARA_A_INPUT_OVER_DPOW_THR_ALARM,    	PT_AP_G_EX|PT_US, 	0},			 // A������������ʸ澯
	{	PARA_A_INPUT_OWE_DPOW_THR_ALARM,    	PT_AP_G_EX|PT_US, 	0},			 // A��������Ƿ���ʸ澯
	{	PARA_B_INPUT_OVER_DPOW_THR_ALARM,    	PT_BP_G_EX|PT_US, 	0},			 // B������������ʸ澯
	{	PARA_B_INPUT_OWE_DPOW_THR_ALARM,    	PT_BP_G_EX|PT_US, 	0},			 // B��������Ƿ���ʸ澯
	{	PARA_C_INPUT_OVER_DPOW_THR_ALARM,    	PT_CP_G_EX|PT_US, 	0},			 // C������������ʸ澯
	{	PARA_C_INPUT_OWE_DPOW_THR_ALARM,    	PT_CP_G_EX|PT_US, 	0},			 // C��������Ƿ���ʸ澯
	{	PARA_D_INPUT_OVER_DPOW_THR_ALARM,    	PT_DP_G_EX|PT_US, 	0},			 // D������������ʸ澯
	{	PARA_D_INPUT_OWE_DPOW_THR_ALARM,    	PT_DP_G_EX|PT_US, 	0},			 // D��������Ƿ���ʸ澯
	{	PARA_TD_D_OVER_SLOT1_THR_ALARM,    		PT_BP_G_EX|PT_US, 	0}, 			 // TD�������뵼Ƶ�����ʸ澯
	{	PARA_TD_D_OWE_SLOT1_THR_ALARM,    		PT_BP_G_EX|PT_US, 	0}, 			 // TD�������뵼ƵǷ���ʸ澯
	{	PARA_RE_DATA_LAN_ST1,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // TD�������뵼ƵǷ���ʸ澯
	{	PARA_RE_CASCADE_LAN_ST1,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // TD�������뵼ƵǷ���ʸ澯
	{	PARA_RE_DATA_LAN_SYS_ST1,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // TD�������뵼ƵǷ���ʸ澯
	{	PARA_RE_CASCADE_LAN_SYS_ST1,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // TD�������뵼ƵǷ���ʸ澯
	{	PARA_A_RF_POW_SWR,				PT_AP_G_EX|PT_US, 	0},	 //A�θ��ǵ�Ԫ����פ����
	{	PARA_A_RF_OUT_POW_H_THR,		PT_AP_G_EX|PT_US, 	0},	 //A�θ��ǵ�Ԫ�������������
	{	PARA_A_RF_OUT_POW_L_THR,		PT_AP_G_EX|PT_US, 	0},	 //A�θ��ǵ�Ԫ���Ƿ��������
	{	PARA_B_RF_POW_SWR,				PT_BP_G_EX|PT_US, 	0},	 //B�θ��ǵ�Ԫ����פ����
	{	PARA_B_RF_OUT_POW_H_THR,		PT_BP_G_EX|PT_US, 	0},	 //B�θ��ǵ�Ԫ������������� 
	{	PARA_B_RF_OUT_POW_L_THR,		PT_BP_G_EX|PT_US, 	0},	 //B�θ��ǵ�Ԫ���Ƿ��������
	{	PARA_C_RF_POW_SWR,				PT_CP_G_EX|PT_US, 	0},	 //C�θ��ǵ�Ԫ����פ����
	{	PARA_C_RF_OUT_POW_H_THR,		PT_CP_G_EX|PT_US, 	0},	 //C�θ��ǵ�Ԫ������������� 
	{	PARA_C_RF_OUT_POW_L_THR,		PT_CP_G_EX|PT_US, 	0},	 //C�θ��ǵ�Ԫ���Ƿ��������
	{	PARA_D_RF_POW_SWR,				PT_DP_G_EX|PT_US, 	0},	 //D�θ��ǵ�Ԫ����פ����
	{	PARA_D_RF_OUT_POW_H_THR,		PT_DP_G_EX|PT_US, 	0},	 //D�θ��ǵ�Ԫ������������� 
	{	PARA_D_RF_OUT_POW_L_THR,		PT_DP_G_EX|PT_US, 	0},	 //D�θ��ǵ�Ԫ���Ƿ��������
	{	PARA_PWR_3V3_1_VT  ,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 		// 3.3V��Դ��ѹ
	{	PARA_PWR_3V3_2_VT  ,    		PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 		//	3.3V��Դ��ѹ
	{	PARA_PWR_1V8_VT  ,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			// 1.8V��Դ��ѹ
	{	PARA_PWR_1V5_VT  ,    			PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0}, 			 // 1.5V��Դ��ѹ
	{	PARA_A_DL_RF_EN	,		PT_AP|PT_US,		1,},	// 	A��������Ƶʹ��
	{	PARA_A_UL_RF_EN	,		PT_AP|PT_US,		1,},	// 	A��������Ƶʹ��
	{	PARA_B_DL_RF_EN	,		PT_BP|PT_US,		1,},	// 	B��������Ƶʹ��
	{	PARA_B_UL_RF_EN	,		PT_BP|PT_US,		1,},	// 	B��������Ƶʹ��
	{	PARA_C_DL_RF_EN	,		PT_CP|PT_US,		1,},	// 	C��������Ƶʹ��
	{	PARA_C_UL_RF_EN	,		PT_CP|PT_US,		1,},	// 	C��������Ƶʹ��
	{	PARA_D_DL_RF_EN	,		PT_DP|PT_US,		1,},	// 	D��������Ƶʹ��
	{	PARA_D_UL_RF_EN	,		PT_DP|PT_US,		1,},	// 	D��������Ƶʹ��
	{	PARA_METER_OFFSET  ,    		PT_AP_G_EX|PT_US, 	0}, 			 //	����ƫ��ֵ����
	{	PARA_METER_OFFSET_B  ,    		PT_BP_G_EX|PT_US, 	0}, 			 //	����ƫ��ֵ����
	{	PARA_METER_OFFSET_C  ,    		PT_CP_G_EX|PT_US, 	0}, 			 //	����ƫ��ֵ����
	{	PARA_METER_OFFSET_D  ,    		PT_DP_G_EX|PT_US, 	0}, 			 //	����ƫ��ֵ����
	{	PARA_C_TD_TYPE_SELECT  ,    		PT_CP|PT_US, 	0},//686	// TD�������뵼Ƶ�����ʸ澯					
	{	PARA_C_TD_NORMAL_CP	  ,    		PT_CP|PT_US, 	0},//716	//	TDD����ʱ϶ NORMAL_CP
	{	PARA_C_TD_EXTENDED_CP	  ,    		PT_CP_G_EX|PT_US, 	0},//717	//	TDD����ʱ϶ NORMAL_CP
	{	PARA_C_TD_SYNC_ST  ,    		PT_CP|PT_US, 	0},	//687  	//TDͬ��״̬:	0-��ͬ����1-δͬ��			
	{	PARA_C_TD_WORK_MODE  ,    		PT_CP|PT_US, 	0},	//688  	//[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������			
	{	PARA_C_TD_DL_OVER_SLOT1_THR_ALARM  ,    		PT_CP_G_EX|PT_US, 	0},	//689  // TD�������뵼Ƶ�����ʸ澯					
	{	PARA_C_TD_DL_OWE_SLOT1_THR_ALARM  ,    		PT_CP_G_EX|PT_US, 	0},	//690	 // TD�������뵼ƵǷ���ʸ澯					
	{	PARA_D_TD_TYPE_SELECT  ,    		PT_DP|PT_US, 	0},	//691  // TD�������뵼Ƶ�����ʸ澯					
	{	PARA_D_TD_NORMAL_CP	  ,    		PT_DP|PT_US, 	0},//718	//	TDD����ʱ϶ NORMAL_CP
	{	PARA_D_TD_EXTENDED_CP	  ,    		PT_DP_G_EX|PT_US, 	0},//719	//	TDD����ʱ϶ NORMAL_CP
	{	PARA_D_TD_SYNC_ST  ,    		PT_DP|PT_US, 	0},	//692  	//TDͬ��״̬:	0-��ͬ����1-δͬ��			
	{	PARA_D_TD_WORK_MODE  ,    		PT_DP|PT_US, 	0},	//693  	//[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������			
	{	PARA_D_TD_DL_OVER_SLOT1_THR_ALARM  ,    		PT_DP_G_EX|PT_US, 	0},	//694  	// TD�������뵼Ƶ�����ʸ澯					
	{	PARA_D_TD_DL_OWE_SLOT1_THR_ALARM  ,    		PT_DP_G_EX|PT_US, 	0},	//695	 // TD�������뵼ƵǷ���ʸ澯					
	{	PARA_C_TD_T0_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//696  	//TDʱ϶0�����б�־:0-���У�1-����			
	{	PARA_C_TD_T1_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//697  	//TDʱ϶1�����б�־:0-���У�1-����			
	{	PARA_C_TD_T2_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//698  	//TDʱ϶2�����б�־:0-���У�1-����			
	{	PARA_C_TD_T3_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//699  	//TDʱ϶3�����б�־:0-���У�1-����			
	{	PARA_C_TD_T4_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//700  	//TDʱ϶4�����б�־:0-���У�1-����			
	{	PARA_C_TD_T5_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//701  	//TDʱ϶5�����б�־:0-���У�1-����			
	{	PARA_C_TD_T6_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//702  	//TDʱ϶6�����б�־:0-���У�1-����			
	{	PARA_C_TD_T7_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//703  	//TDʱ϶7�����б�־:0-���У�1-����			
	{	PARA_C_TD_T8_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//704  	//TDʱ϶8�����б�־:0-���У�1-����			
	{	PARA_C_TD_T9_UD	  ,    		PT_CP_G_EX|PT_US, 	0},	//705  	//TDʱ϶9�����б�־:0-���У�1-����			
	{	PARA_D_TD_T0_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//706  	//TDʱ϶0�����б�־:0-���У�1-����			
	{	PARA_D_TD_T1_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//707  	//TDʱ϶1�����б�־:0-���У�1-����			
	{	PARA_D_TD_T2_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//708  	//TDʱ϶2�����б�־:0-���У�1-����			
	{	PARA_D_TD_T3_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//709  	//TDʱ϶3�����б�־:0-���У�1-����			
	{	PARA_D_TD_T4_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//710  	//TDʱ϶4�����б�־:0-���У�1-����			
	{	PARA_D_TD_T5_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//711  	//TDʱ϶5�����б�־:0-���У�1-����			
	{	PARA_D_TD_T6_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//712  	//TDʱ϶6�����б�־:0-���У�1-����			
	{	PARA_D_TD_T7_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//713  	//TDʱ϶7�����б�־:0-���У�1-����			
	{	PARA_D_TD_T8_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//714  	//TDʱ϶8�����б�־:0-���У�1-����			
	{	PARA_D_TD_T9_UD	  ,    		PT_DP_G_EX|PT_US, 	0},	//715  	//TDʱ϶9�����б�־:0-���У�1-����
	{	PARA_NOISE_TEST_EN	  ,    	PT_AP_G_EX|PT_US, 	0},	//	�������Կ���	
	{	PARA_FREQ_MODIF_VAL_D	  ,    	PT_DP_G_EX|PT_US, 	0},	//	Ƶ������	
	{	PARA_FREQ_MODIF_VAL_B	  ,    	PT_BP_G_EX|PT_US, 	0},	//	Ƶ������	
	{	PARA_FREQ_MODIF_VAL_A	  ,    	PT_AP_G_EX|PT_US, 	0},	//	Ƶ������	
	{	PARA_B_TDS_2TH_BREAKING_POINT_SET	  ,    	PT_BP|PT_US, 	0},	//	TDS �ڶ�ת��������	
	{	PARA_DELAY_MODE_A	,PT_AP|PT_US, 	0},		//0x8660	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�		
	{	PARA_DELAY_MODE_B	,PT_BP|PT_US, 	0},		//0x8660	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�					
	{	PARA_DELAY_MODE_C	,PT_CP|PT_US, 	0},		//0x8660	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�					
	{	PARA_DELAY_MODE_D	,PT_DP|PT_US, 	0},		//0x8660	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�					
	{	PARA_REE_CIRCUIT_ALARM	,	   PT_AP|PT_US,  0},					//	0x803f		// ��չ��Ԫ��·���ϸ澯16
	{	PARA_REE_WLAN_CONN_ST			,	   PT_AP|PT_US,  0},			//	0x87d0	//	316 //	WLAN��״̬1:	0-������1-�쳣
	{	PARA_DL_POWER_MAX ,PT_NC, 0}, 	//������ģ�鹦�����ֵ			
	{	PARA_SLOT_TIME_EN_B	,PT_BP,	0}, 	//ʱ϶����Զ���⿪��				
	{	PARA_SLOT_TIME_DISTRI_B ,PT_BP, 0}, 	//ʱ϶��ȷֲ�				
	{	PARA_VERSION_FLAG ,PT_NC, 0}, 	//�汾ʶ��		
	{	PARA_SLOT_TIME_EN_C ,PT_BP, 0}, 	//ʱ϶����Զ���⿪��				
	{	PARA_SLOT_TIME_DISTRI_C ,PT_BP, 0}, 	//ʱ϶��ȷֲ�				
	{	PARA_A_1197_LOCK_ST ,PT_AP, 0}, //A��1197����״̬		
	{	PARA_A_IF_ST ,PT_AP, 0},	//A����ƵƵ��,0/1---300M/500M				
	{	PARA_ENCRYPTION_ST ,PT_AP, 0},	//����״̬,0/1---������/����				
	{	PARA_PWR_1V6_VT ,PT_AP, 0},         //     //1.6v��Դ		
	{	PARA_A_90_VALUE ,PT_AP, 0xff}, //A��9363 90�Ĵ�����ֵ
	{	PARA_A_91_VALUE ,PT_AP, 0xff}, //A��9363 91�Ĵ�����ֵ
	{	PARA_A_94_VALUE ,PT_AP, 0xff}, //A��9363 94�Ĵ�����ֵ
	{	PARA_A_95_VALUE ,PT_AP, 0xff}, //A��9363 95�Ĵ�����ֵ
	{	PARA_B_90_VALUE ,PT_AP, 0xff}, //B��9363 90�Ĵ�����ֵ
	{	PARA_B_91_VALUE ,PT_AP, 0xff}, //B��9363 91�Ĵ�����ֵ
	{	PARA_B_94_VALUE ,PT_AP, 0xff}, //B��9363 94�Ĵ�����ֵ
	{	PARA_B_95_VALUE ,PT_AP, 0xff}, //B��9363 95�Ĵ�����ֵ
	{	PARA_C_90_VALUE ,PT_AP, 0xff}, //C��9363 90�Ĵ�����ֵ
	{	PARA_C_91_VALUE ,PT_AP, 0xff}, //C��9363 91�Ĵ�����ֵ
	{	PARA_C_94_VALUE ,PT_AP, 0xff}, //C��9363 94�Ĵ�����ֵ
	{	PARA_C_95_VALUE ,PT_AP, 0xff}, //C��9363 95�Ĵ�����ֵ
	{	PARA_D_90_VALUE ,PT_AP, 0xff}, //D��9363 90�Ĵ�����ֵ
	{	PARA_D_91_VALUE ,PT_AP, 0xff}, //D��9363 91�Ĵ�����ֵ
	{	PARA_D_94_VALUE ,PT_AP, 0xff}, //D��9363 94�Ĵ�����ֵ
	{	PARA_D_95_VALUE ,PT_AP, 0xff}, //D��9363 95�Ĵ�����ֵ
	{	PARA_PASSTHROUGH_EN ,PT_AP, 0x00}, //͸��ʹ�ܿ���
	{	PARA_A_DL_POW_ADJ ,PT_AP, 0}, 
	{	PARA_B_DL_POW_ADJ ,PT_BP, 0}, 
	{	PARA_C_DL_POW_ADJ ,PT_CP, 0}, 
	{	PARA_D_DL_POW_ADJ ,PT_DP, 0}, 
	{	PARA_SoftwareLoadTimes ,PT_NC, 0}, 
	{	PARA_A_LNA_EN_ST	,PT_AP, 0}, 			//9363��ʼ�����ã�0Ϊa1��01Ϊa2
		

};


_T_PARAM_2B sys_param_2b[]={
	{	PARA_A_DL_CHANNEL1	, PT_AP|PT_US, 	45,}, 	//	A�������ŵ���1
	{	PARA_A_DL_CHANNEL2	, PT_AP|PT_US, 	45,},	//	A�������ŵ���2
	{	PARA_A_DL_CHANNEL3	, PT_AP|PT_US, 	45,},	//	A�������ŵ���3
	{	PARA_A_DL_CHANNEL4	, PT_AP|PT_US, 	45,},	//	A�������ŵ���4
	{	PARA_A_DL_CHANNEL5	, PT_AP|PT_US, 	45,},	//	A�������ŵ���5
	{	PARA_A_DL_CHANNEL6	, PT_AP|PT_US, 	45,},	//	A�������ŵ���6
	{	PARA_A_DL_CHANNEL7	, PT_AP|PT_US, 	45,},	//	A�������ŵ���7
	{	PARA_A_DL_CHANNEL8	, PT_AP|PT_US, 	45,},	//	A�������ŵ���8
	{	PARA_A_DL_CHANNEL9	, PT_AP|PT_US, 	45,},	//	A�������ŵ���9
	{	PARA_A_DL_CHANNEL10	, PT_AP|PT_US, 	45,},	//	A�������ŵ���10
	{	PARA_A_DL_CHANNEL11	, PT_AP|PT_US, 	45,},	//	A�������ŵ���11
	{	PARA_A_DL_CHANNEL12	, PT_AP|PT_US, 	45,},	//	A�������ŵ���12
	{	PARA_A_DL_CHANNEL13	, PT_AP|PT_US, 	45,},	//	A�������ŵ���13
	{	PARA_A_DL_CHANNEL14	, PT_AP|PT_US, 	45,},	//	A�������ŵ���14
	{	PARA_A_DL_CHANNEL15	, PT_AP|PT_US, 	45,},	//	A�������ŵ���15
	{	PARA_A_DL_CHANNEL16	, PT_AP|PT_US, 	45,},	//	A�������ŵ���16
	{	PARA_A_UL_CHANNEL1		, PT_US, 	45,}, 	//	A�������ŵ���1
	{	PARA_A_UL_CHANNEL2		, PT_US, 	45,},	//	A�������ŵ���2
	{	PARA_A_UL_CHANNEL3		, PT_US, 	45,},	//	A�������ŵ���3
	{	PARA_A_UL_CHANNEL4		, PT_US, 	45,},	//	A�������ŵ���4
	{	PARA_A_UL_CHANNEL5		, PT_US, 	45,},	//	A�������ŵ���5
	{	PARA_A_UL_CHANNEL6		, PT_US, 	45,},	//	A�������ŵ���6
	{	PARA_A_UL_CHANNEL7		, PT_US, 	45,},	//	A�������ŵ���7
	{	PARA_A_UL_CHANNEL8		, PT_US, 	45,},	//	A�������ŵ���8
	{	PARA_A_UL_CHANNEL9		, PT_US, 	45,},	//	A�������ŵ���9
	{	PARA_A_UL_CHANNEL10	, PT_US, 	45,},	//	A�������ŵ���10
	{	PARA_A_UL_CHANNEL11	, PT_US, 	45,},	//	A�������ŵ���11
	{	PARA_A_UL_CHANNEL12	, PT_US, 	45,},	//	A�������ŵ���12
	{	PARA_A_UL_CHANNEL13	, PT_US, 	45,},	//	A�������ŵ���13
	{	PARA_A_UL_CHANNEL14	, PT_US, 	45,},	//	A�������ŵ���14
	{	PARA_A_UL_CHANNEL15	, PT_US, 	45,},	//	A�������ŵ���15
	{	PARA_A_UL_CHANNEL16	, PT_US, 	45,},	//	A�������ŵ���16
	{	PARA_A_DCH_MAX_POW1	, PT_AP_G_EX|PT_SI, 	27,},	//	A������ͨ������������1
	{	PARA_A_DCH_MAX_POW2	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������2
	{	PARA_A_DCH_MAX_POW3	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������3
	{	PARA_A_DCH_MAX_POW4	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������4
	{	PARA_A_DCH_MAX_POW5	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������5
	{	PARA_A_DCH_MAX_POW6	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������6
	{	PARA_A_DCH_MAX_POW7	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������7
	{	PARA_A_DCH_MAX_POW8	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������8
	{	PARA_A_DCH_MAX_POW9	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������9
	{	PARA_A_DCH_MAX_POW10	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������10
	{	PARA_A_DCH_MAX_POW11	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������11
	{	PARA_A_DCH_MAX_POW12	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������12
	{	PARA_A_DCH_MAX_POW13	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������13
	{	PARA_A_DCH_MAX_POW14	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������14
	{	PARA_A_DCH_MAX_POW15	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������15
	{	PARA_A_DCH_MAX_POW16	, PT_AP_G_EX|PT_NC, 	27,},	//	A������ͨ������������16
	{	PARA_A_UCH_MAX_POW1	, PT_AP|PT_SI, 		-10,},	//	A������ͨ��������빦��1
	{	PARA_A_UCH_MAX_POW2	, PT_AP|PT_SI, 	-10,},	//	A������ͨ��������빦��2
	{	PARA_A_UCH_MAX_POW3	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��3
	{	PARA_A_UCH_MAX_POW4	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��4
	{	PARA_A_UCH_MAX_POW5	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��5
	{	PARA_A_UCH_MAX_POW6	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��6
	{	PARA_A_UCH_MAX_POW7	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��7
	{	PARA_A_UCH_MAX_POW8	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��8
	{	PARA_A_UCH_MAX_POW9	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��9
	{	PARA_A_UCH_MAX_POW10	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��10
	{	PARA_A_UCH_MAX_POW11	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��11
	{	PARA_A_UCH_MAX_POW12	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��12
	{	PARA_A_UCH_MAX_POW13	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��13
	{	PARA_A_UCH_MAX_POW14	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��14
	{	PARA_A_UCH_MAX_POW15	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��15
	{	PARA_A_UCH_MAX_POW16	, PT_AP_G_EX|PT_NC, 	-10,},	//	A������ͨ��������빦��16
	{	PARA_A_DCH_POW1	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���1
	{	PARA_A_DCH_POW2	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���2
	{	PARA_A_DCH_POW3	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���3
	{	PARA_A_DCH_POW4	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���4
	{	PARA_A_DCH_POW5	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���5
	{	PARA_A_DCH_POW6	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���6
	{	PARA_A_DCH_POW7	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���7
	{	PARA_A_DCH_POW8	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���8
	{	PARA_A_DCH_POW9	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���9
	{	PARA_A_DCH_POW10	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���10
	{	PARA_A_DCH_POW11	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���11
	{	PARA_A_DCH_POW12	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���12
	{	PARA_A_DCH_POW13	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���13
	{	PARA_A_DCH_POW14	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���14
	{	PARA_A_DCH_POW15	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���15
	{	PARA_A_DCH_POW16	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���16
	{	PARA_A_UCH_POW1	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���1
	{	PARA_A_UCH_POW2	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���2
	{	PARA_A_UCH_POW3	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���3
	{	PARA_A_UCH_POW4	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���4
	{	PARA_A_UCH_POW5	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���5
	{	PARA_A_UCH_POW6	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���6
	{	PARA_A_UCH_POW7	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���7
	{	PARA_A_UCH_POW8	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���8
	{	PARA_A_UCH_POW9	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���9
	{	PARA_A_UCH_POW10	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���10
	{	PARA_A_UCH_POW11	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���11
	{	PARA_A_UCH_POW12	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���12
	{	PARA_A_UCH_POW13	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���13
	{	PARA_A_UCH_POW14	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���14
	{	PARA_A_UCH_POW15	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���15
	{	PARA_A_UCH_POW16	, PT_NC, 	0,},	//	A��ѡƵͨ�����й���16
	{	PARA_A_UDPX_IN_GAIN	, PT_AP_G_EX|PT_NC, 	0,},	//	A������˫��������
	{	PARA_A_UDPX_OUT_GAIN, PT_AP_G_EX|PT_NC, 	0,},	//	A�����˫��������
	{	PARA_A_DL_TOTAL_POW	, PT_AP|PT_RO|PT_SI, 	0,},	//	A�������ܹ���
	{	PARA_A_UL_TOTAL_POW	, PT_AP|PT_RO|PT_SI, 	0,},	//	A�������ܹ���
	{	PARA_A_REC_DPX_IG	, PT_NC, 	0,},	//	REC��A������˫����˥������������������㣬ֻ��,	
	{	PARA_A_REC_DPX_OG	, PT_NC, 	0,},	//	REC��A�����˫����˥������������������㣬ֻ��,	
	{	PARA_B_DL_CHANNEL1		, PT_BP|PT_US,	10688,},	//	B�������ŵ���1
	{	PARA_B_DL_CHANNEL2		, PT_BP|PT_US,	10688,},	//	B�������ŵ���2
	{	PARA_B_DL_CHANNEL3		, PT_BP|PT_US,	10688,},	//	B�������ŵ���3
	{	PARA_B_DL_CHANNEL4		, PT_BP|PT_US,	10688,},	//	B�������ŵ���4
	{	PARA_B_DL_CHANNEL5		, PT_BP|PT_US,	10688,},	//	B�������ŵ���5
	{	PARA_B_DL_CHANNEL6		, PT_BP|PT_US,	10688,},	//	B�������ŵ���6
	{	PARA_B_DL_CHANNEL7		, PT_BP|PT_US,	10688,},	//	B�������ŵ���7
	{	PARA_B_DL_CHANNEL8		, PT_BP|PT_US,	10688,},	//	B�������ŵ���8
	{	PARA_B_DL_CHANNEL9		, PT_BP|PT_US,	10688,},	//	B�������ŵ���9
	{	PARA_B_DL_CHANNEL10 , PT_BP|PT_US,	10688,},	//	B�������ŵ���10
	{	PARA_B_DL_CHANNEL11 , PT_BP|PT_US,	10688,},	//	B�������ŵ���11
	{	PARA_B_DL_CHANNEL12 , PT_BP|PT_US,	10688,},	//	B�������ŵ���12
	{	PARA_B_DL_CHANNEL13 , PT_BP|PT_US,	10688,},	//	B�������ŵ���13
	{	PARA_B_DL_CHANNEL14 , PT_BP|PT_US,	10688,},	//	B�������ŵ���14
	{	PARA_B_DL_CHANNEL15 , PT_BP|PT_US,	10688,},	//	B�������ŵ���15
	{	PARA_B_DL_CHANNEL16 , PT_BP|PT_US,	10688,},	//	B�������ŵ���16
	{	PARA_B_UL_CHANNEL1	, PT_US,	10688,},	//	B�������ŵ���1
	{	PARA_B_UL_CHANNEL2	, PT_US,	10688,},	//	B�������ŵ���2
	{	PARA_B_UL_CHANNEL3	, PT_US,	10688,},	//	B�������ŵ���3
	{	PARA_B_UL_CHANNEL4	, PT_US,	10688,},	//	B�������ŵ���4
	{	PARA_B_UL_CHANNEL5	, PT_US,	10688,},	//	B�������ŵ���5
	{	PARA_B_UL_CHANNEL6	, PT_US,	10688,},	//	B�������ŵ���6
	{	PARA_B_UL_CHANNEL7	, PT_US,	10688,},	//	B�������ŵ���7
	{	PARA_B_UL_CHANNEL8	, PT_US,	10688,},	//	B�������ŵ���8
	{	PARA_B_UL_CHANNEL9	, PT_US,	10688,},	//	B�������ŵ���9
	{	PARA_B_UL_CHANNEL10 , PT_US,	10688,},	//	B�������ŵ���10
	{	PARA_B_UL_CHANNEL11 , PT_US,	10688,},	//	B�������ŵ���11
	{	PARA_B_UL_CHANNEL12 , PT_US,	10688,},	//	B�������ŵ���12
	{	PARA_B_UL_CHANNEL13 , PT_US,	10688,},	//	B�������ŵ���13
	{	PARA_B_UL_CHANNEL14 , PT_US,	10688,},	//	B�������ŵ���14
	{	PARA_B_UL_CHANNEL15 , PT_US,	10688,},	//	B�������ŵ���15
	{	PARA_B_UL_CHANNEL16 , PT_US,	10688,},	//	B�������ŵ���16
	{	PARA_B_DCH_MAX_POW1	, PT_BP_G_EX|PT_SI, 		27,},	//	B������ͨ������������1
	{	PARA_B_DCH_MAX_POW2	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������2
	{	PARA_B_DCH_MAX_POW3	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������3
	{	PARA_B_DCH_MAX_POW4	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������4
	{	PARA_B_DCH_MAX_POW5	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������5
	{	PARA_B_DCH_MAX_POW6	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������6
	{	PARA_B_DCH_MAX_POW7	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������7
	{	PARA_B_DCH_MAX_POW8	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������8
	{	PARA_B_DCH_MAX_POW9	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������9
	{	PARA_B_DCH_MAX_POW10	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������10
	{	PARA_B_DCH_MAX_POW11	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������11
	{	PARA_B_DCH_MAX_POW12	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������12
	{	PARA_B_DCH_MAX_POW13	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������13
	{	PARA_B_DCH_MAX_POW14	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������14
	{	PARA_B_DCH_MAX_POW15	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������15
	{	PARA_B_DCH_MAX_POW16	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ������������16
	{	PARA_B_UCH_MAX_POW1		, PT_BP|PT_SI, 	-10,},	//	B������ͨ��������빦��1
	{	PARA_B_UCH_MAX_POW2		, PT_BP|PT_SI, 	-10,},	//	B������ͨ��������빦��2
	{	PARA_B_UCH_MAX_POW3		, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��3
	{	PARA_B_UCH_MAX_POW4		, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��4
	{	PARA_B_UCH_MAX_POW5		, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��5
	{	PARA_B_UCH_MAX_POW6		, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��6
	{	PARA_B_UCH_MAX_POW7		, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��7
	{	PARA_B_UCH_MAX_POW8		, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��8
	{	PARA_B_UCH_MAX_POW9		, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��9
	{	PARA_B_UCH_MAX_POW10	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��10
	{	PARA_B_UCH_MAX_POW11	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��11
	{	PARA_B_UCH_MAX_POW12	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��12
	{	PARA_B_UCH_MAX_POW13	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��13
	{	PARA_B_UCH_MAX_POW14	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��14
	{	PARA_B_UCH_MAX_POW15	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��15
	{	PARA_B_UCH_MAX_POW16	, PT_BP_G_EX|PT_NC, 	27,},	//	B������ͨ��������빦��16
	{	PARA_B_DCH_POW1	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���1
	{	PARA_B_DCH_POW2	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���2
	{	PARA_B_DCH_POW3	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���3
	{	PARA_B_DCH_POW4	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���4
	{	PARA_B_DCH_POW5	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���5
	{	PARA_B_DCH_POW6	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���6
	{	PARA_B_DCH_POW7	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���7
	{	PARA_B_DCH_POW8	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���8
	{	PARA_B_DCH_POW9	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���9
	{	PARA_B_DCH_POW10	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���10
	{	PARA_B_DCH_POW11	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���11
	{	PARA_B_DCH_POW12	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���12
	{	PARA_B_DCH_POW13	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���13
	{	PARA_B_DCH_POW14	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���14
	{	PARA_B_DCH_POW15	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���15
	{	PARA_B_DCH_POW16	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���16
	{	PARA_B_UCH_POW1	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���1
	{	PARA_B_UCH_POW2	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���2
	{	PARA_B_UCH_POW3	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���3
	{	PARA_B_UCH_POW4	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���4
	{	PARA_B_UCH_POW5	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���5
	{	PARA_B_UCH_POW6	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���6
	{	PARA_B_UCH_POW7	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���7
	{	PARA_B_UCH_POW8	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���8
	{	PARA_B_UCH_POW9	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���9
	{	PARA_B_UCH_POW10	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���10
	{	PARA_B_UCH_POW11	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���11
	{	PARA_B_UCH_POW12	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���12
	{	PARA_B_UCH_POW13	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���13
	{	PARA_B_UCH_POW14	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���14
	{	PARA_B_UCH_POW15	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���15
	{	PARA_B_UCH_POW16	, PT_NC, 	0,},	//	B��ѡƵͨ�����й���16
	{	PARA_B_UDPX_IN_GAIN	, PT_BP_G_EX|PT_NC, 	0,},	//	B������˫��������
	{	PARA_B_UDPX_OUT_GAIN, PT_BP_G_EX|PT_NC, 	0,},	//	B�����˫��������
	{	PARA_B_DL_TOTAL_POW	, PT_BP|PT_RO|PT_SI, 	0,},	//	B����������ܹ���/*PT_BP_EX*/
	{	PARA_B_UL_TOTAL_POW	, PT_BP|PT_RO|PT_SI, 	0,},	//	B�����������ܹ���/*PT_BP_EX*/
	{	PARA_B_REC_DPX_IG	, PT_NC, 	0,},	//	REC��B������˫����˥������������������㣬ֻ��,	
	{	PARA_B_REC_DPX_OG	, PT_NC, 	0,},	//	REC��B�����˫����˥������������������㣬ֻ��,	
	{ 	PARA_C_DL_CHANNEL1 , PT_CP|PT_US,  39100,},  // C�������ŵ���1
	{ 	PARA_C_DL_CHANNEL2 , PT_CP|PT_US,  39100,},	// C�������ŵ���2
	{ 	PARA_C_DL_CHANNEL3 , PT_CP|PT_US,  39210,},	// C�������ŵ���3
	{ 	PARA_C_DL_CHANNEL4 , PT_CP|PT_US,  39210,},	// C�������ŵ���4
	{ 	PARA_C_DL_CHANNEL5 , PT_CP|PT_US,  39210,},	// C�������ŵ���5
	{ 	PARA_C_DL_CHANNEL6 , PT_CP|PT_US,  39210,},	// C�������ŵ���6
	{ 	PARA_C_DL_CHANNEL7 , PT_CP|PT_US,  39210,},	// C�������ŵ���7
	{ 	PARA_C_DL_CHANNEL8 , PT_CP|PT_US,  39210,},	// C�������ŵ���8
	{ 	PARA_C_DL_CHANNEL9 , PT_CP|PT_US,  39210,},	// C�������ŵ���9
	{ 	PARA_C_DL_CHANNEL10 , PT_CP|PT_US,  39210,},  // C�������ŵ���10
	{	PARA_C_UL_CHANNEL1		, PT_US, 	39210,}, 	//	C�������ŵ���1
	{	PARA_C_UL_CHANNEL2		, PT_US, 	39210,},	//	C�������ŵ���2
	{	PARA_C_UL_CHANNEL3		, PT_US, 	39210,},	//	C�������ŵ���3
	{	PARA_C_UL_CHANNEL4		, PT_US, 	39210,},	//	C�������ŵ���4
	{	PARA_C_UL_CHANNEL5		, PT_US, 	39210,},	//	C�������ŵ���5
	{	PARA_C_UL_CHANNEL6		, PT_US, 	39210,},	//	C�������ŵ���6
	{	PARA_C_UL_CHANNEL7		, PT_US, 	39210,},	//	C�������ŵ���7
	{	PARA_C_UL_CHANNEL8		, PT_US, 	39210,},	//	C�������ŵ���8
	{	PARA_C_UL_CHANNEL9		, PT_US, 	39210,},	//	C�������ŵ���9
	{	PARA_C_UL_CHANNEL10		, PT_US, 	39210,},	//	C�������ŵ���10
	{	PARA_C_DCH_MAX_POW1	, PT_CP_G_EX|PT_SI, 		27,},	//	C������ͨ������������1
	{	PARA_C_DCH_MAX_POW2	, PT_CP_G_EX|PT_SI, 		27,},	//	C������ͨ������������2
	{	PARA_C_DCH_MAX_POW3	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������3
	{	PARA_C_DCH_MAX_POW4	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������4
	{	PARA_C_DCH_MAX_POW5	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������5
	{	PARA_C_DCH_MAX_POW6	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������6
	{	PARA_C_DCH_MAX_POW7	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������7
	{	PARA_C_DCH_MAX_POW8	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������8
	{	PARA_C_DCH_MAX_POW9	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������9
	{	PARA_C_DCH_MAX_POW10	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������10
	{	PARA_C_DCH_MAX_POW11	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������11
	{	PARA_C_DCH_MAX_POW12	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������12
	{	PARA_C_DCH_MAX_POW13	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������13
	{	PARA_C_DCH_MAX_POW14	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������14
	{	PARA_C_DCH_MAX_POW15	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������15
	{	PARA_C_DCH_MAX_POW16	, PT_CP_G_EX|PT_NC, 	27,},	//	C������ͨ������������16
	{	PARA_C_UCH_MAX_POW1	, PT_CP|PT_SI, 		-5,},	//	C������ͨ��������빦��1
	{	PARA_C_UCH_MAX_POW2	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��2
	{	PARA_C_UCH_MAX_POW3	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��3
	{	PARA_C_UCH_MAX_POW4	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��4
	{	PARA_C_UCH_MAX_POW5	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��5
	{	PARA_C_UCH_MAX_POW6	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��6
	{	PARA_C_UCH_MAX_POW7	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��7
	{	PARA_C_UCH_MAX_POW8	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��8
	{	PARA_C_UCH_MAX_POW9	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��9
	{	PARA_C_UCH_MAX_POW10	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��10
	{	PARA_C_UCH_MAX_POW11	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��11
	{	PARA_C_UCH_MAX_POW12	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��12
	{	PARA_C_UCH_MAX_POW13	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��13
	{	PARA_C_UCH_MAX_POW14	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��14
	{	PARA_C_UCH_MAX_POW15	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��15
	{	PARA_C_UCH_MAX_POW16	, PT_CP_G_EX|PT_NC, 	-5,},	//	C������ͨ��������빦��16
	{	PARA_C_DCH_POW1	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���1
	{	PARA_C_DCH_POW2	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���2
	{	PARA_C_DCH_POW3	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���3
	{	PARA_C_DCH_POW4	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���4
	{	PARA_C_DCH_POW5	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���5
	{	PARA_C_DCH_POW6	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���6
	{	PARA_C_DCH_POW7	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���7
	{	PARA_C_DCH_POW8	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���8
	{	PARA_C_DCH_POW9	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���9
	{	PARA_C_DCH_POW10	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���10
	{	PARA_C_DCH_POW11	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���11
	{	PARA_C_DCH_POW12	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���12
	{	PARA_C_DCH_POW13	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���13
	{	PARA_C_DCH_POW14	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���14
	{	PARA_C_DCH_POW15	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���15
	{	PARA_C_DCH_POW16	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���16
	{	PARA_C_UCH_POW1	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���1
	{	PARA_C_UCH_POW2	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���2
	{	PARA_C_UCH_POW3	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���3
	{	PARA_C_UCH_POW4	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���4
	{	PARA_C_UCH_POW5	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���5
	{	PARA_C_UCH_POW6	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���6
	{	PARA_C_UCH_POW7	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���7
	{	PARA_C_UCH_POW8	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���8
	{	PARA_C_UCH_POW9	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���9
	{	PARA_C_UCH_POW10	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���10
	{	PARA_C_UCH_POW11	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���11
	{	PARA_C_UCH_POW12	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���12
	{	PARA_C_UCH_POW13	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���13
	{	PARA_C_UCH_POW14	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���14
	{	PARA_C_UCH_POW15	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���15
	{	PARA_C_UCH_POW16	, PT_NC, 	0,},	//	C��ѡƵͨ�����й���16
	{	PARA_C_UDPX_IN_GAIN	, PT_CP_G_EX|PT_NC, 	0,},	//	C������˫��������
	{	PARA_C_UDPX_OUT_GAIN, PT_CP_G_EX|PT_NC, 	0,},	//	C�����˫��������
	{	PARA_C_DL_TOTAL_POW	, PT_CP|PT_RO|PT_SI, 	0,},	//	C�������ܹ���
	{	PARA_C_UL_TOTAL_POW	, PT_CP_G_EX|PT_RO|PT_SI, 	0,},	//	C�������ܹ���
	{	PARA_C_REC_DPX_IG	, PT_NC, 	0,},	//	REC��C������˫����˥������������������㣬ֻ��,	
	{	PARA_C_REC_DPX_OG	, PT_NC, 	0,},	//	REC��C�����˫����˥������������������㣬ֻ��,	
	{ 	PARA_D_DL_CHANNEL1  , PT_DP|PT_US,  39100,},	// D�������ŵ���1
	{ 	PARA_D_DL_CHANNEL2  , PT_DP|PT_US,  39100,},	// D�������ŵ���2
	{ 	PARA_D_DL_CHANNEL3  , PT_DP|PT_US,  39210,},	// D�������ŵ���3
	{ 	PARA_D_DL_CHANNEL4  , PT_DP|PT_US,  39210,},	// D�������ŵ���4
	{ 	PARA_D_DL_CHANNEL5  , PT_DP|PT_US,  39210,},	// D�������ŵ���5
	{	PARA_D_DL_CHANNEL6  , PT_DP|PT_US,  39210,},	// D�������ŵ���6
	{ 	PARA_D_DL_CHANNEL7  , PT_DP|PT_US,  39210,},	// D�������ŵ���7
	{ 	PARA_D_DL_CHANNEL8  , PT_DP|PT_US,  39210,},	// D�������ŵ���8
	{ 	PARA_D_DL_CHANNEL9  , PT_DP|PT_US,  39210,},	// D�������ŵ���9
	{ 	PARA_D_DL_CHANNEL10  , PT_DP|PT_US,  39210,},  // D�������ŵ���10
	{	PARA_D_UL_CHANNEL1	, PT_US, 	39210,}, 	//	D�������ŵ���1
	{	PARA_D_UL_CHANNEL2	, PT_US, 	39210,},	//	D�������ŵ���2
	{	PARA_D_UL_CHANNEL3	, PT_US, 	39210,},	//	D�������ŵ���3
	{	PARA_D_UL_CHANNEL4	, PT_US, 	39210,},	//	D�������ŵ���4
	{	PARA_D_UL_CHANNEL5	, PT_US, 	39210,},	//	D�������ŵ���5
	{	PARA_D_UL_CHANNEL6	, PT_US, 	39210,},	//	D�������ŵ���6
	{	PARA_D_UL_CHANNEL7	, PT_US, 	39210,},	//	D�������ŵ���7
	{	PARA_D_UL_CHANNEL8	, PT_US, 	39210,},	//	D�������ŵ���8
	{	PARA_D_UL_CHANNEL9	, PT_US, 	39210,},	//	D�������ŵ���9
	{	PARA_D_UL_CHANNEL10	, PT_US, 	39210,},	//	D�������ŵ���10
	{	PARA_D_DCH_MAX_POW1	, PT_DP_G_EX|PT_SI, 		27,},	//	D������ͨ������������1
	{	PARA_D_DCH_MAX_POW2	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������2
	{	PARA_D_DCH_MAX_POW3	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������3
	{	PARA_D_DCH_MAX_POW4	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������4
	{	PARA_D_DCH_MAX_POW5	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������5
	{	PARA_D_DCH_MAX_POW6	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������6
	{	PARA_D_DCH_MAX_POW7	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������7
	{	PARA_D_DCH_MAX_POW8	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������8
	{	PARA_D_DCH_MAX_POW9	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������9
	{	PARA_D_DCH_MAX_POW10	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������10
	{	PARA_D_DCH_MAX_POW11	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������11
	{	PARA_D_DCH_MAX_POW12	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������12
	{	PARA_D_DCH_MAX_POW13	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������13
	{	PARA_D_DCH_MAX_POW14	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������14
	{	PARA_D_DCH_MAX_POW15	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������15
	{	PARA_D_DCH_MAX_POW16	, PT_DP_G_EX|PT_NC, 	27,},	//	D������ͨ������������16
	{	PARA_D_UCH_MAX_POW1	, PT_DP|PT_SI, 		-5,},	//	D������ͨ��������빦��1
	{	PARA_D_UCH_MAX_POW2	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��2
	{	PARA_D_UCH_MAX_POW3	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��3
	{	PARA_D_UCH_MAX_POW4	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��4
	{	PARA_D_UCH_MAX_POW5	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��5
	{	PARA_D_UCH_MAX_POW6	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��6
	{	PARA_D_UCH_MAX_POW7	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��7
	{	PARA_D_UCH_MAX_POW8	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��8
	{	PARA_D_UCH_MAX_POW9	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��9
	{	PARA_D_UCH_MAX_POW10	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��10
	{	PARA_D_UCH_MAX_POW11	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��11
	{	PARA_D_UCH_MAX_POW12	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��12
	{	PARA_D_UCH_MAX_POW13	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��13
	{	PARA_D_UCH_MAX_POW14	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��14
	{	PARA_D_UCH_MAX_POW15	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��15
	{	PARA_D_UCH_MAX_POW16	, PT_DP_G_EX|PT_NC, 	-5,},	//	D������ͨ��������빦��16
	{	PARA_D_DCH_POW1	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���1
	{	PARA_D_DCH_POW2	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���2
	{	PARA_D_DCH_POW3	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���3
	{	PARA_D_DCH_POW4	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���4
	{	PARA_D_DCH_POW5	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���5
	{	PARA_D_DCH_POW6	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���6
	{	PARA_D_DCH_POW7	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���7
	{	PARA_D_DCH_POW8	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���8
	{	PARA_D_DCH_POW9	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���9
	{	PARA_D_DCH_POW10	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���10
	{	PARA_D_DCH_POW11	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���11
	{	PARA_D_DCH_POW12	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���12
	{	PARA_D_DCH_POW13	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���13
	{	PARA_D_DCH_POW14	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���14
	{	PARA_D_DCH_POW15	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���15
	{	PARA_D_DCH_POW16	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���16
	{	PARA_D_UCH_POW1	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���1
	{	PARA_D_UCH_POW2	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���2
	{	PARA_D_UCH_POW3	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���3
	{	PARA_D_UCH_POW4	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���4
	{	PARA_D_UCH_POW5	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���5
	{	PARA_D_UCH_POW6	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���6
	{	PARA_D_UCH_POW7	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���7
	{	PARA_D_UCH_POW8	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���8
	{	PARA_D_UCH_POW9	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���9
	{	PARA_D_UCH_POW10	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���10
	{	PARA_D_UCH_POW11	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���11
	{	PARA_D_UCH_POW12	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���12
	{	PARA_D_UCH_POW13	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���13
	{	PARA_D_UCH_POW14	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���14
	{	PARA_D_UCH_POW15	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���15
	{	PARA_D_UCH_POW16	, PT_NC, 	0,},	//	D��ѡƵͨ�����й���16
	{	PARA_D_UDPX_IN_GAIN	, PT_DP_G_EX|PT_NC, 	0,},	//	D������˫��������
	{	PARA_D_UDPX_OUT_GAIN, PT_DP_G_EX|PT_NC, 	0,},	//	D�����˫��������
	{	PARA_D_DL_TOTAL_POW	, PT_DP|PT_RO|PT_SI, 	0,},	//	D����������ܹ���/*PT_BP_EX*/
	{	PARA_D_UL_TOTAL_POW	, PT_DP_G_EX|PT_RO|PT_SI, 	0,},	//	D�����������ܹ���/*PT_BP_EX*/
	{	PARA_D_REC_DPX_IG	, PT_DP_G_EX|PT_NC, 	0,},	//	REC��D������˫����˥������������������㣬ֻ��,	
	{	PARA_D_REC_DPX_OG	, PT_DP_G_EX|PT_NC, 	0,},	//	REC��D�����˫����˥������������������㣬ֻ��,	
	{	PARA_REC_TO_RE_DELAY,	PT_AP_G_EX|PT_BP_G_EX|PT_US,	0},	// REC��RE�Ĺ�����ʱ
	{	PARA_RE_RF_DELAY,		PT_AP_G_EX|PT_BP_G_EX|PT_US,	0},	// RE����Ƶ��ʱ
	{	PARA_MAX_T14	, PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0,},	//	��������ʱ
	{	PARA_DL_DELAY_OFFSET	, PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0,},	//	������ʱƫ����
	{	PARA_UL_DELAY_OFFSET	, PT_AP_G_EX|PT_BP_G_EX|PT_US, 	0,},	//	������ʱƫ����
	{	PARA_PRI_SOFT_V	, PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0,},	//	����汾�ţ���ASCII�룩
	{	PARA_PRI_HARD_V	, PT_AP_G_EX|PT_BP_G_EX|PT_RO|PT_US, 	0,},	//	PCB�汾��(��ASCII��)
	{	PARA_TD_1ST_CP_TIME,	PT_BP_EX|PT_US,	0},	// TD��1ת����ʱ��ns, �з�����
	{	PARA_TD_2ND_CP_TIME,	PT_BP_EX|PT_US,	0},	// TD��2ת����ʱ��ns, �з�����
	{	PARA_TD_LNA_ON_TIME,	PT_BP_EX|PT_US,	0},	// LNA�����ٺ�DN_PA�رյı���ʱ��ns
	{	PARA_TD_LNA_OFF_TIME,	PT_BP_EX|PT_US,	0},	// LNA�رճ�ǰDN_PA�����ı���ʱ��ns
	{	PARA_TD_SLOT1_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶1���м�⹦��
	{	PARA_TD_SLOT2_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶2���м�⹦��
	{	PARA_TD_SLOT3_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶3���м�⹦��
	{	PARA_TD_SLOT4_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶4���м�⹦��
	{	PARA_TD_SLOT5_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶5���м�⹦��
	{	PARA_TD_SLOT6_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶6���м�⹦��
	{	PARA_TD_SLOT7_UPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶7���м�⹦��
	{	PARA_TD_SLOT1_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶1���м�⹦��
	{	PARA_TD_SLOT2_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶2���м�⹦��
	{	PARA_TD_SLOT3_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶3���м�⹦��
	{	PARA_TD_SLOT4_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶4���м�⹦��
	{	PARA_TD_SLOT5_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶5���м�⹦��
	{	PARA_TD_SLOT6_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶6���м�⹦��
	{	PARA_TD_SLOT7_DPOW,	PT_BP_G_EX|PT_SI,	0},	// TDʱ϶7���м�⹦��
	{	PARA_FPS_S1,	PT_SI,	0},	// Ƶ�����ط�Χ1��ʼƵ��
	{	PARA_FPS_E1,	PT_SI,	0},	// Ƶ�����ط�Χ1����Ƶ��
	{	PARA_FPS_S2,	PT_SI,	0},	// Ƶ�����ط�Χ2��ʼƵ��
	{	PARA_FPS_E2,	PT_SI,	0},	// Ƶ�����ط�Χ2����Ƶ��
	{	PARA_FPS_BCCH_LK_SET,	PT_AP_G|PT_US,	65535},	// Ƶ������: ��Ƶ�ŵ���: ��׼�ŵ���, 65535-�˳���Ƶ
	{	PARA_FPS_CID_LK_SET	,	PT_AP_G|PT_US,	0},	// Ƶ������: С��ʶ����ο�ֵ, 0-�˳�С����������
	{	PARA_FPS_BCCH_FC_M	,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: ��С��BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
	{	PARA_FPS_CA_FC_0,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�0�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_1,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�1�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_2,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�2�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_3,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�3�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_4,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�4�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_5,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�5�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_6,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�6�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_7,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�7�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_8,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�8�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_9,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�9�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_10,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�10�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_11,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�11�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_12,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�12�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_13,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�13�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_14,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�14�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_CA_FC_15,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: CA�ز�15�ŵ���, ��׼�ŵ���, 65535-��CA
	{	PARA_FPS_BCCH_FC_1,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: ��С��1 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
	{	PARA_FPS_BCCH_FC_2,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: ��С��2 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
	{	PARA_FPS_BCCH_FC_3,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: ��С��3 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
	{	PARA_FPS_BCCH_FC_4,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: ��С��4 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
	{	PARA_FPS_BCCH_FC_5,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: ��С��5 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
	{	PARA_FPS_BCCH_FC_6,	PT_AP_G|PT_RO|PT_US,	65535},	// Ƶ������: ��С��6 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
	{	PARA_FPS_AREA_ID,	PT_AP_G_EX|PT_RO|PT_US,	0},	// Ƶ������: λ��������
	{	PARA_FPS_CID,	PT_AP_G_EX|PT_RO|PT_US,	0},	// Ƶ������: С��ʶ����ʵʱֵ
	{	PARA_FPS_CID_1,		PT_NC,	0}, // Ƶ������: ��С��1 CIDС��ʶ����
	{	PARA_FPS_CID_2,		PT_NC,	0}, // Ƶ������: ��С��2 CIDС��ʶ����
	{	PARA_FPS_CID_3,		PT_NC,	0}, // Ƶ������: ��С��3 CIDС��ʶ����
	{	PARA_FPS_CID_4,		PT_NC,	0}, // Ƶ������: ��С��4 CIDС��ʶ����
	{	PARA_FPS_CID_5,		PT_NC,	0}, // Ƶ������: ��С��5 CIDС��ʶ����
	{	PARA_FPS_CID_6,		PT_NC,	0}, // Ƶ������: ��С��6 CIDС��ʶ����
	{	PARA_A_EXPA_IDRAIN_SET,	PT_NC,	0},	// ΢����: ©����������,mA
	{	PARA_TD_SLOT1_DPOW_OVER_THR,    PT_BP_G_EX|PT_US, 	0},       //�������뵼Ƶ����������
	{	PARA_TD_SLOT1_DPOW_OWE_THR,    	PT_BP_G_EX|PT_US, 	0},       //�������뵼ƵǷ��������
	{	PARA_A_INPUT_TOTAL_DPOW_OVER_THR,				PT_AP_G_EX|PT_US,	0},//�������뵼Ƶ����������
	{	PARA_A_INPUT_TOTAL_DPOW_OWE_THR,				PT_AP_G_EX|PT_US,	0},//�������뵼ƵǷ��������
	{	PARA_B_INPUT_TOTAL_DPOW_OVER_THR,				PT_BP_G_EX|PT_US,	0},//�������뵼Ƶ����������
	{	PARA_B_INPUT_TOTAL_DPOW_OWE_THR,				PT_BP_G_EX|PT_US,	0},//�������뵼ƵǷ��������
	{	PARA_C_INPUT_TOTAL_DPOW_OVER_THR,				PT_CP_G_EX|PT_US,	0},//�������뵼Ƶ����������
	{	PARA_C_INPUT_TOTAL_DPOW_OWE_THR,				PT_CP_G_EX|PT_US,	0},//�������뵼ƵǷ��������
	{	PARA_D_INPUT_TOTAL_DPOW_OVER_THR,				PT_DP_G_EX|PT_US,	0},//�������뵼Ƶ����������
	{	PARA_D_INPUT_TOTAL_DPOW_OWE_THR,				PT_DP_G_EX|PT_US,	0},//�������뵼ƵǷ��������
	{	PARA_REE_A_DL_OUT_TOTAL_POW_DETECT,		PT_AP_G_EX|PT_US,	0},//A��REE��������ܹ���
	{	PARA_A_RE_LOCAL_ST_ALARM,					PT_AP_G_EX|PT_BP_G_EX|PT_US,	0},//���ǵ�Ԫ���ظ澯״̬
	{	PARA_REE_B_DL_OUT_TOTAL_POW_DETECT ,		PT_BP_G_EX|PT_US,	0}, //B��REE��������ܹ���
	{	PARA_B_RE_LOCAL_ST_ALARM,	PT_BP_G_EX|PT_US,	0},//���ǵ�Ԫ���ظ澯״̬
	{	PARA_REE_C_DL_OUT_TOTAL_POW_DETECT,		PT_CP_G_EX|PT_US,	0},//C��REE��������ܹ���
	{	PARA_C_RE_LOCAL_ST_ALARM,					PT_CP_G_EX|PT_US,	0},//���ǵ�Ԫ���ظ澯״̬
	{	PARA_REE_D_DL_OUT_TOTAL_POW_DETECT ,		PT_DP_G_EX|PT_US,	0}, //D��REE��������ܹ���
	{	PARA_D_RE_LOCAL_ST_ALARM,	PT_DP_G_EX|PT_US,	0},//���ǵ�Ԫ���ظ澯״̬
	{	PARA_C_TD_1ST_CP_TIME,	PT_CP_G_EX|PT_US,	0},		//465		//		TD��1ת����ʱ��,ns,	
	{	PARA_C_TD_2ND_CP_TIME,	PT_CP_G_EX|PT_US,	0},		//466		//		TD��2ת����ʱ��,ns,	
	{	PARA_C_TD_LNA_ON_TIME,	PT_CP_G_EX|PT_US,	0},		//467		//		LNA�����ٺ�DN_PA�رյı���ʱ��ns	
	{	PARA_C_TD_LNA_OFF_TIME,	PT_CP_G_EX|PT_US,	0},		//468		//		LNA�رճ�ǰDN_PA�����ı���ʱ��ns	
	{	PARA_C_TD_SLOT1_DPOW_OVER_THR,	PT_CP_G_EX|PT_US,	0},		//469		//625		//�������뵼Ƶ����������	
	{	PARA_C_TD_SLOT1_DPOW_OWE_THR,	PT_CP_G_EX|PT_US,	0},		//470		//626		//�������뵼ƵǷ��������	
	{	PARA_D_TD_1ST_CP_TIME,	PT_DP_G_EX|PT_US,	0},		//471		//		TD��1ת����ʱ��,ns,	
	{	PARA_D_TD_2ND_CP_TIME,	PT_DP_G_EX|PT_US,	0},		//472		//		TD��2ת����ʱ��,ns,	
	{	PARA_D_TD_LNA_ON_TIME,	PT_DP_G_EX|PT_US,	0},		//473		//		LNA�����ٺ�DN_PA�رյı���ʱ��ns	
	{	PARA_D_TD_LNA_OFF_TIME,	PT_DP_G_EX|PT_US,	0},		//474		//		LNA�رճ�ǰDN_PA�����ı���ʱ��ns	
	{	PARA_D_TD_SLOT1_DPOW_OVER_THR,	PT_DP_G_EX|PT_US,	0},		//475		//625		//�������뵼Ƶ����������	
	{	PARA_D_TD_SLOT1_DPOW_OWE_THR,	PT_DP_G_EX|PT_US,	0},		//476		//626		//�������뵼ƵǷ��������	
	{	PARA_C_TD_SLOT1_POW,	PT_CP_G_EX|PT_US,	0},		//477		//		TDʱ϶1�����⹦��	
	{	PARA_C_TD_SLOT2_POW,	PT_CP_G_EX|PT_US,	0},		//478		//		TDʱ϶2�����⹦��	
	{	PARA_C_TD_SLOT3_POW,	PT_CP_G_EX|PT_US,	0},		//479		//		TDʱ϶3�����⹦��	
	{	PARA_C_TD_SLOT4_POW,	PT_CP_G_EX|PT_US,	0},		//480		//		TDʱ϶4�����⹦��	
	{	PARA_C_TD_SLOT5_POW,	PT_CP_G_EX|PT_US,	0},		//481		//		TDʱ϶5�����⹦��	
	{	PARA_C_TD_SLOT6_POW,	PT_CP_G_EX|PT_US,	0},		//482		//		TDʱ϶6�����⹦��	
	{	PARA_C_TD_SLOT7_POW,	PT_CP_G_EX|PT_US,	0},		//483		//		TDʱ϶7�����⹦��	
	{	PARA_C_TD_SLOT8_POW,	PT_CP_G_EX|PT_US,	0},		//484		//		TDʱ϶8�����⹦��	
	{	PARA_C_TD_SLOT9_POW,	PT_CP_G_EX|PT_US,	0},		//485		//		TDʱ϶9�����⹦��	
	{	PARA_C_TD_SLOT10_POW,	PT_CP_G_EX|PT_US,	0},		//486		//		TDʱ϶10�����⹦��	
	{	PARA_C_TD_SLOT11_POW,	PT_CP_G_EX|PT_US,	0},		//487		//		TDʱ϶11�����⹦��	
	{	PARA_C_TD_SLOT12_POW,	PT_CP_G_EX|PT_US,	0},		//488		//		TDʱ϶12�����⹦��	
	{	PARA_C_TD_SLOT13_POW,	PT_CP_G_EX|PT_US,	0},		//489		//		TDʱ϶13�����⹦��	
	{	PARA_C_TD_SLOT14_POW,	PT_CP_G_EX|PT_US,	0},		//490		//		TDʱ϶14�����⹦��	
	{	PARA_C_TD_SLOT15_POW,	PT_CP_G_EX|PT_US,	0},		//491		//		TDʱ϶15�����⹦��	
	{	PARA_C_TD_SLOT16_POW,	PT_CP_G_EX|PT_US,	0},		//492		//		TDʱ϶16�����⹦��	
	{	PARA_C_TD_SLOT17_POW,	PT_CP_G_EX|PT_US,	0},		//493		//		TDʱ϶17�����⹦��	
	{	PARA_C_TD_SLOT18_POW,	PT_CP_G_EX|PT_US,	0},		//494		//		TDʱ϶18�����⹦��	
	{	PARA_C_TD_SLOT19_POW,	PT_CP_G_EX|PT_US,	0},		//495		//		TDʱ϶19�����⹦��	
	{	PARA_C_TD_SLOT20_POW,	PT_CP_G_EX|PT_US,	0},		//496		//		TDʱ϶20�����⹦��	
	{	PARA_D_TD_SLOT1_POW,	PT_DP_G_EX|PT_US,	0},		//497		//		TDʱ϶1�����⹦��	
	{	PARA_D_TD_SLOT2_POW,	PT_DP_G_EX|PT_US,	0},		//498		//		TDʱ϶2�����⹦��	
	{	PARA_D_TD_SLOT3_POW,	PT_DP_G_EX|PT_US,	0},		//499		//		TDʱ϶3�����⹦��	
	{	PARA_D_TD_SLOT4_POW,	PT_DP_G_EX|PT_US,	0},		//500		//		TDʱ϶4�����⹦��	
	{	PARA_D_TD_SLOT5_POW,	PT_DP_G_EX|PT_US,	0},		//501		//		TDʱ϶5�����⹦��	
	{	PARA_D_TD_SLOT6_POW,	PT_DP_G_EX|PT_US,	0},		//502		//		TDʱ϶6�����⹦��	
	{	PARA_D_TD_SLOT7_POW,	PT_DP_G_EX|PT_US,	0},		//503		//		TDʱ϶7�����⹦��	
	{	PARA_D_TD_SLOT8_POW,	PT_DP_G_EX|PT_US,	0},		//504		//		TDʱ϶8�����⹦��	
	{	PARA_D_TD_SLOT9_POW,	PT_DP_G_EX|PT_US,	0},		//505		//		TDʱ϶9�����⹦��	
	{	PARA_D_TD_SLOT10_POW,	PT_DP_G_EX|PT_US,	0},		//506		//		TDʱ϶10�����⹦��	
	{	PARA_D_TD_SLOT11_POW,	PT_DP_G_EX|PT_US,	0},		//507		//		TDʱ϶11�����⹦��	
	{	PARA_D_TD_SLOT12_POW,	PT_DP_G_EX|PT_US,	0},		//508		//		TDʱ϶12�����⹦��	
	{	PARA_D_TD_SLOT13_POW,	PT_DP_G_EX|PT_US,	0},		//509		//		TDʱ϶13�����⹦��	
	{	PARA_D_TD_SLOT14_POW,	PT_DP_G_EX|PT_US,	0},		//510		//		TDʱ϶14�����⹦��	
	{	PARA_D_TD_SLOT15_POW,	PT_DP_G_EX|PT_US,	0},		//511		//		TDʱ϶15�����⹦��	
	{	PARA_D_TD_SLOT16_POW,	PT_DP_G_EX|PT_US,	0},		//512		//		TDʱ϶16�����⹦��	
	{	PARA_D_TD_SLOT17_POW,	PT_DP_G_EX|PT_US,	0},		//513		//		TDʱ϶17�����⹦��	
	{	PARA_D_TD_SLOT18_POW,	PT_DP_G_EX|PT_US,	0},		//514		//		TDʱ϶18�����⹦��	
	{	PARA_D_TD_SLOT19_POW,	PT_DP_G_EX|PT_US,	0},		//515		//		TDʱ϶19�����⹦��	
	{	PARA_D_TD_SLOT20_POW,	PT_DP_G_EX|PT_US,	0},		//516		//		TDʱ϶20�����⹦��	
	{	PARA_DL_DELAY_OFFSET_B	,PT_BP|PT_US, 	0},		//0x8660	//		������ʱƫ����					
	{	PARA_DL_DELAY_OFFSET_C	,PT_CP|PT_US, 	0},		//0x8660	//		������ʱƫ����					
	{	PARA_DL_DELAY_OFFSET_D	,PT_DP|PT_US, 	0},		//0x8660	//		������ʱƫ����					
	{	PARA_VGS_A	,PT_AP|PT_US,	0}, 	//A��դѹ
	{	PARA_VGS_B	,PT_BP|PT_US,	0}, 	//B��դѹ
	{	PARA_VGS_C	,PT_CP|PT_US,	0}, 	//C��դѹ
	{	PARA_VGS_D	,PT_DP|PT_US,	0}, 	//D��դѹ
	{	PARA_VGS_COMP_A ,PT_AP|PT_US,	0}, 	//A��դѹ
	{	PARA_VGS_COMP_B ,PT_BP|PT_US,	0}, 	//B��դѹ
	{	PARA_VGS_COMP_C ,PT_CP|PT_US,	0}, 	//C��դѹ
	{	PARA_VGS_COMP_D ,PT_DP|PT_US,	0}, 	//D��դѹ
	{	PARA_ATT_DATA_COMP_A	,PT_AP|PT_US,	0}, //ATT��������
	{	PARA_ATT_DATA_COMP_B	,PT_BP|PT_US,	0}, //ATT��������
	{	PARA_ATT_DATA_COMP_C	,PT_CP|PT_US,	0}, //ATT��������
	{	PARA_ATT_DATA_COMP_D	,PT_DP|PT_US,	0}, //ATT��������//PARA_MAX_T14_A
	{	PARA_MAX_T14_A	,PT_AP|PT_US,	0}, //ATT��������
	{	PARA_MAX_T14_B	,PT_BP|PT_US,	0}, //ATT��������
	{	PARA_MAX_T14_C	,PT_CP|PT_US,	0}, //ATT��������
	{	PARA_MAX_T14_D	,PT_DP|PT_US,	0}, //ATT������
	{	PARA_ERL_JG_A,PT_AP|PT_US,	0}, 
	{	PARA_ERL_JG_C,PT_CP|PT_US,	0}, 
	{	PARA_ERL_JG_D,PT_DP|PT_US,	0}, 
	{	PARA_MOVE_CENTER_FRE_D,PT_NC,	0}, 										
	{	PARA_MOVE_CENTER_FRE_U,PT_NC, 0}, 										
};


_T_PARAM_4B sys_param_4b[]={
	{ 	PARA_DEV_ADDR , PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_US,	0	 },		//	�豸·�ɵǼǵ�ַ
	{	PARA_BIT_ERR_COUNT, PT_NC, 0 },		// ���ݰ�����ͳ��
	{	PARA_TOPO_CHG_COUNT, PT_NC, 0 },		// ���ݰ�����ͳ��
	{	PARA_FPGA_PKT_COUNT, PT_NC, 0 },		// FPGA���ݰ�����ͳ��
	{	PARA_OPT_RE_COUNT1, PT_AP_EX|PT_BP_EX|PT_CP|PT_DP|PT_US, 0 },		// Զ�˻��ڵ����1
	{	PARA_OPT_RE_COUNT2, PT_AP_EX|PT_BP_EX|PT_CP|PT_DP|PT_US, 0 },		// Զ�˻��ڵ����2
	{	PARA_OPS_PORT, PT_AP_EX|PT_BP_EX|PT_CP|PT_DP|PT_US, 0 },		// ��ڵĶԶ˹�ں�
};

// ģ��ʶ��ID��(��ASCII��)			REC/RE
UCHAR8 str_pri_id[PRI_ID_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// ģ������(��ASCII��)				REC/RE
UCHAR8 str_pri_type[PRI_TYPE_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', '\0'};
// �������к�(��ASCII��)			20101030001
UCHAR8 str_pri_seq[PRI_SEQ_LEN]={'2', '0', '1', '0', '1', '0', '3', '0', '0', '0', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// ���Ҳ�Ʒ���(��ASCII��)			DOF-FFFFFFFW21400302
UCHAR8 str_pri_gl_product[PRI_GL_PRODUCT_LEN]={'D', 'O', 'N', '-', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'W', '2', '1', '4', '0', '0', '3', '0', '2'};
// �����������к�(��ASCII��)		20101030001
UCHAR8 str_pri_gl_seq[PRI_GL_SEQ_LEN]={'2', '0', '1', '0', '1', '0', '3', '0', '0', '0', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// Ψһʶ��ID(��ASCII��)			REC/RE
UCHAR8 str_pri_gl_rom_id[PRI_GL_ROM_ID_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// MCU��������(��ASCII��)
UCHAR8 str_pri_mcu_date[PRI_MCU_DATE_LEN]={0};
// FPGA��������(��ASCII��)
UCHAR8 str_pri_fpga_date[PRI_FPGA_DATE_LEN]={0};
// FPGA2��������(��ASCII��)
UCHAR8 str_pri_fpga2_date[PRI_FPGA_DATE_LEN]={0};
// IDʶ���ַ���(��ASCII��)			REC/RE
UCHAR8 str_module_hri_str[MODULE_HRI_STR_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
//	9363_A�����ļ���������(��ASCII��)
UCHAR8 str_a_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	9363_B�����ļ���������(��ASCII��)
UCHAR8 str_b_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	9363_C�����ļ���������(��ASCII��)
UCHAR8 str_c_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	ree�豸λ����Ϣ
UCHAR8 str_mau_position_inf[PRI_MAU_POSITION_INF_LEN]={0};
// MCU����汾(��ASCII��)
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
	{	PARA_EU_ALARM_FLAG1     			,PT_AP|PT_BP|PT_US, 	0},      	//EU1�澯ָʾ
	{	PARA_EU_ALARM_FLAG2     			,PT_AP|PT_BP|PT_US, 	0},      	//EU2�澯ָʾ
	{	PARA_EU_ALARM_FLAG3     			,PT_AP|PT_BP|PT_US, 	0},      	//EU3�澯ָʾ
	{	PARA_EU_ALARM_FLAG4     			,PT_AP|PT_BP|PT_US, 	0},     	//EU4�澯ָʾ
	{	PARA_EU_ALARM_FLAG5     			,PT_AP|PT_BP|PT_US, 	0},      	//EU5�澯ָʾ
	{	PARA_EU_ALARM_FLAG6     			,PT_AP|PT_BP|PT_US, 	0},     	//EU6�澯ָʾ
	{	PARA_EU_ALARM_FLAG7     			,PT_AP|PT_BP|PT_US, 	0},      	//EU7�澯ָʾ
	{	PARA_EU_ALARM_FLAG8     			,PT_AP|PT_BP|PT_US, 	0},      	//EU8�澯ָʾ
	
};

_T_PARAM_2B sys_param_eu_2b[]={

	{	PARA_EU_ALARM_CONTENT1 ,		PT_AP|PT_BP|PT_US,	0},//EU1�澯����
	{	PARA_EU_ALARM_CONTENT2,		PT_AP|PT_BP|PT_US,	0},//EU2�澯����
	{	PARA_EU_ALARM_CONTENT3 ,		PT_AP|PT_BP|PT_US, 	0},//EU3�澯����
	{	PARA_EU_ALARM_CONTENT4 ,		PT_AP|PT_BP|PT_US, 	0},//EU4�澯����	
	{	PARA_EU_ALARM_CONTENT5 ,		PT_AP|PT_BP|PT_US,	0},//EU5�澯����
	{	PARA_EU_ALARM_CONTENT6,		PT_AP|PT_BP|PT_US,	0},//EU6�澯����
	{	PARA_EU_ALARM_CONTENT7 ,		PT_AP|PT_BP|PT_US, 	0},//EU7�澯����
	{	PARA_EU_ALARM_CONTENT8 ,		PT_AP|PT_BP|PT_US, 	0},//EU8�澯����
	{	PARA_EU_RUALARM_FLAG1 ,		PT_AP|PT_BP|PT_US, 	0},//EU1�µ�16��RU�澯ָʾ
	{	PARA_EU_RUALARM_FLAG2 ,		PT_AP|PT_BP|PT_US, 	0},//EU2�µ�16��RU�澯ָʾ
	{	PARA_EU_RUALARM_FLAG3 ,		PT_AP|PT_BP|PT_US, 	0},//EU3�µ�16��RU�澯ָʾ
	{	PARA_EU_RUALARM_FLAG4 ,		PT_AP|PT_BP|PT_US, 	0},//EU4�µ�16��RU�澯ָʾ
	{	PARA_EU_RUALARM_FLAG5 ,		PT_AP|PT_BP|PT_US, 	0},//EU5�µ�16��RU�澯ָʾ
	{	PARA_EU_RUALARM_FLAG6 ,		PT_AP|PT_BP|PT_US, 	0},//EU6�µ�16��RU�澯ָʾ
	{	PARA_EU_RUALARM_FLAG7 ,		PT_AP|PT_BP|PT_US, 	0},//EU7�µ�16��RU�澯ָʾ
	{	PARA_EU_RUALARM_FLAG8 ,		PT_AP|PT_BP|PT_US, 	0},//EU8�µ�16��RU�澯ָʾ
};


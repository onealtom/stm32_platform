/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : param_addr.h
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
#ifndef _PARAM_ADDR_H_
#define _PARAM_ADDR_H_

// 1�ֽڲ����ṹ��
typedef struct _S_PARAM_1B
{
	UINT16	addr;	// ��ַ
	UCHAR8	type;	// ���ʺ��㷨
	UCHAR8	val;		// ����ֵ
}_T_PARAM_1B;

// 2�ֽڲ����ṹ��
typedef struct _S_PARAM_2B
{
	UINT16	addr;	// ��ַ
	UCHAR8	type;	// ���ʺ��㷨
	UINT16	val;		// ����ֵ
}_T_PARAM_2B;

// 4�ֽڲ����ṹ��
typedef struct _S_PARAM_4B
{
	UINT16	addr;	// ��ַ
	UCHAR8	type;	// ���ʺ��㷨
	UINT32	val;		// ����ֵ
}_T_PARAM_4B;

// �ַ��������ṹ��
typedef struct _S_PARAM_ASC
{
	UINT16	addr;	// ��ַ
	UCHAR8	type;	// ���ʺ��㷨
	UCHAR8	length;	// �ַ�������
	UCHAR8 * p_asc;	// ָ���ַ����׵�ַָ��
}_T_PARAM_ASC;



#define PARAM_ASC_MAX_LEN		64		//�ַ��������ĳ������ֵ

#define PTM_MASK	(0x07<<0)	// �㷨����
#define PT_NC		(0<<0) // ���㷨
#define PT_SI		(1<<0) // �з�����
#define PT_SW		(2<<0) // �з���˫�ֽ���,��Ҫ��ʵ��ֵx10
#define PT_US		(3<<0) // �޷�����
#define PT_RST		(4<<0) // ��λ�㷨

#define PT_RO		(8<<0)	// ֻ������
#define PT_AP		(1<<4)	// �ⲿ����485����
#define PT_BP		(1<<5)	// �ⲿ����485����
#define PT_CP		(1<<6)	// �ⲿ����485����
#define PT_DP		(1<<7)	// �ⲿ����485����


#define PT_ARNC		(PT_AP|PT_NC)
#define PT_BRNC		(PT_BP|PT_NC)
#define PT_ABRNC	(PT_AP|PT_BP|PT_NC)

#if defined ( CLIENT_JIZHUN)
	// ���˲���
	#define PT_AP_G		(PT_AP)
	#define PT_BP_G		(PT_BP)
	#define PT_CP_G		(PT_CP)
	#define PT_DP_G		(PT_DP)		
	#define PT_AP_G_EX		(PT_AP)
	#define PT_BP_G_EX		(PT_BP)
	#define PT_CP_G_EX		(0)
	#define PT_DP_G_EX		(0)		
	// �������
	#define PT_AP_EX	(PT_AP)
	#define PT_BP_EX	(PT_BP)	
	#define PT_CP_EX	(PT_CP)
	#define PT_DP_EX	(PT_DP)	

#else
	// ���˲���
	#define PT_AP_G		(0)
	#define PT_BP_G		(0)
	#define PT_CP_G		(0)
	#define PT_DP_G		(0)	
	// �������
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
	// ���˲���
// ������ַ����==================================================== 1b								
#define	PARA_A_CHANNEL_COUNT	0x8889	//	A��֧�ֵ�ͨ����
#define	PARA_A_DL_WORK_EN	0x08a0	//	A�����й���ʹ��
#define	PARA_A_UL_WORK_EN	0x08a1	//	A�����й���ʹ��
#define	PARA_A_DPOW_MODE	0	//	A�����й��ʿ��Ʒ�ʽ
#define	PARA_A_UPOW_MODE	0	//	A�����й��ʿ��Ʒ�ʽ
#define	PARA_A_LTHR_EN	0x0770	//	A�����е�������ʹ��
#define	PARA_A_LTHR_UP	0	//	A�ε�������������
#define	PARA_A_LTHR_DN	0x08b0	//	A�ε�������������
#define	PARA_A_DCH_EN1	0x08d0	//	A������ͨ������ʹ��1
#define	PARA_A_DCH_EN2	0x08d1	//	A������ͨ������ʹ��2
#define	PARA_A_DCH_EN3	0x08d2	//	A������ͨ������ʹ��3
#define	PARA_A_DCH_EN4	0x08d3	//	A������ͨ������ʹ��4
#define	PARA_A_DCH_EN5	0x08d4	//	A������ͨ������ʹ��5
#define	PARA_A_DCH_EN6	0x08d5	//	A������ͨ������ʹ��6
#define	PARA_A_DCH_EN7	0x08d6	//	A������ͨ������ʹ��7
#define	PARA_A_DCH_EN8	0x08d7	//	A������ͨ������ʹ��8
#define	PARA_A_DCH_EN9	0x08d8	//	A������ͨ������ʹ��9
#define	PARA_A_DCH_EN10	0x08d9	//	A������ͨ������ʹ��10
#define	PARA_A_DCH_EN11	0x08dA	//	A������ͨ������ʹ��11
#define	PARA_A_DCH_EN12	0x08dB	//	A������ͨ������ʹ��12
#define	PARA_A_DCH_EN13	0x08dC	//	A������ͨ������ʹ��13
#define	PARA_A_DCH_EN14	0x08dD	//	A������ͨ������ʹ��14
#define	PARA_A_DCH_EN15	0x08dE	//	A������ͨ������ʹ��15
#define	PARA_A_DCH_EN16	0x08dF	//	A������ͨ������ʹ��16
#define	PARA_A_UCH_EN1	0x08d0	//	A������ͨ������ʹ��1
#define	PARA_A_UCH_EN2	0x08d1	//	A������ͨ������ʹ��2
#define	PARA_A_UCH_EN3	0x08d2	//	A������ͨ������ʹ��3
#define	PARA_A_UCH_EN4	0x08d3	//	A������ͨ������ʹ��4
#define	PARA_A_UCH_EN5	0x08d4	//	A������ͨ������ʹ��5
#define	PARA_A_UCH_EN6	0x08d5	//	A������ͨ������ʹ��6
#define	PARA_A_UCH_EN7	0x08d6	//	A������ͨ������ʹ��7
#define	PARA_A_UCH_EN8	0x08d7	//	A������ͨ������ʹ��8
#define	PARA_A_UCH_EN9	0x08d8	//	A������ͨ������ʹ��9
#define	PARA_A_UCH_EN10	0x08d9	//	A������ͨ������ʹ��10
#define	PARA_A_UCH_EN11	0x08dA	//	A������ͨ������ʹ��11
#define	PARA_A_UCH_EN12	0x08dB	//	A������ͨ������ʹ��12
#define	PARA_A_UCH_EN13	0x08dC	//	A������ͨ������ʹ��13
#define	PARA_A_UCH_EN14	0x08dD	//	A������ͨ������ʹ��14
#define	PARA_A_UCH_EN15	0x08dE	//	A������ͨ������ʹ��15
#define	PARA_A_UCH_EN16	0x08dF	//	A������ͨ������ʹ��16
#define	PARA_A_DCH_GAIN1	0x0840	//	A������ѡƵͨ���Ŵ�������1
#define	PARA_A_DCH_GAIN2	0x0841	//	A������ѡƵͨ���Ŵ�������2
#define	PARA_A_DCH_GAIN3	0x0842	//	A������ѡƵͨ���Ŵ�������3
#define	PARA_A_DCH_GAIN4	0x0843	//	A������ѡƵͨ���Ŵ�������4
#define	PARA_A_DCH_GAIN5	0x0844	//	A������ѡƵͨ���Ŵ�������5
#define	PARA_A_DCH_GAIN6	0x0845	//	A������ѡƵͨ���Ŵ�������6
#define	PARA_A_DCH_GAIN7	0x0846	//	A������ѡƵͨ���Ŵ�������7
#define	PARA_A_DCH_GAIN8	0x0847	//	A������ѡƵͨ���Ŵ�������8
#define	PARA_A_DCH_GAIN9	0x0848	//	A������ѡƵͨ���Ŵ�������9
#define	PARA_A_DCH_GAIN10	0x0849	//	A������ѡƵͨ���Ŵ�������10
#define	PARA_A_DCH_GAIN11	0x084A	//	A������ѡƵͨ���Ŵ�������11
#define	PARA_A_DCH_GAIN12	0x084B	//	A������ѡƵͨ���Ŵ�������12
#define	PARA_A_DCH_GAIN13	0x084C	//	A������ѡƵͨ���Ŵ�������13
#define	PARA_A_DCH_GAIN14	0x084D	//	A������ѡƵͨ���Ŵ�������14
#define	PARA_A_DCH_GAIN15	0x084E	//	A������ѡƵͨ���Ŵ�������15
#define	PARA_A_DCH_GAIN16	0x084F	//	A������ѡƵͨ���Ŵ�������16
#define	PARA_A_UCH_GAIN1	0x0850	//	A������ѡƵͨ���Ŵ�������1
#define	PARA_A_UCH_GAIN2	0x0851	//	A������ѡƵͨ���Ŵ�������2
#define	PARA_A_UCH_GAIN3	0x0852	//	A������ѡƵͨ���Ŵ�������3
#define	PARA_A_UCH_GAIN4	0x0853	//	A������ѡƵͨ���Ŵ�������4
#define	PARA_A_UCH_GAIN5	0x0854	//	A������ѡƵͨ���Ŵ�������5
#define	PARA_A_UCH_GAIN6	0x0855	//	A������ѡƵͨ���Ŵ�������6
#define	PARA_A_UCH_GAIN7	0x0856	//	A������ѡƵͨ���Ŵ�������7
#define	PARA_A_UCH_GAIN8	0x0857	//	A������ѡƵͨ���Ŵ�������8
#define	PARA_A_UCH_GAIN9	0x0858	//	A������ѡƵͨ���Ŵ�������9
#define	PARA_A_UCH_GAIN10	0x0859	//	A������ѡƵͨ���Ŵ�������10
#define	PARA_A_UCH_GAIN11	0x085A	//	A������ѡƵͨ���Ŵ�������11
#define	PARA_A_UCH_GAIN12	0x085B	//	A������ѡƵͨ���Ŵ�������12
#define	PARA_A_UCH_GAIN13	0x085C	//	A������ѡƵͨ���Ŵ�������13
#define	PARA_A_UCH_GAIN14	0x085D	//	A������ѡƵͨ���Ŵ�������14
#define	PARA_A_UCH_GAIN15	0x085E	//	A������ѡƵͨ���Ŵ�������15
#define	PARA_A_UCH_GAIN16	0x085F	//	A������ѡƵͨ���Ŵ�������16
#define	PARA_A_DCH_ATT1	0x0324	//	A����������˥����1
#define	PARA_A_DCH_ATT2	0	//	A����������˥����2
#define	PARA_A_DCH_ATT3	0	//	A����������˥����3
#define	PARA_A_DCH_ATT4	0	//	A����������˥����4
#define	PARA_A_DCH_ATT5	0	//	A����������˥����5
#define	PARA_A_DCH_ATT6	0	//	A����������˥����6
#define	PARA_A_DCH_ATT7	0	//	A����������˥����7
#define	PARA_A_DCH_ATT8	0	//	A����������˥����8
#define	PARA_A_DCH_ATT9	0	//	A����������˥����9
#define	PARA_A_DCH_ATT10	0	//	A����������˥����10
#define	PARA_A_DCH_ATT11	0	//	A����������˥����11
#define	PARA_A_DCH_ATT12	0	//	A����������˥����12
#define	PARA_A_DCH_ATT13	0	//	A����������˥����13
#define	PARA_A_DCH_ATT14	0	//	A����������˥����14
#define	PARA_A_DCH_ATT15	0	//	A����������˥����15
#define	PARA_A_DCH_ATT16	0	//	A����������˥����16
#define	PARA_A_UCH_ATT1	0x0320	//	A����������˥����1
#define	PARA_A_UCH_ATT2	0	//	A����������˥����2
#define	PARA_A_UCH_ATT3	0	//	A����������˥����3
#define	PARA_A_UCH_ATT4	0	//	A����������˥����4
#define	PARA_A_UCH_ATT5	0	//	A����������˥����5
#define	PARA_A_UCH_ATT6	0	//	A����������˥����6
#define	PARA_A_UCH_ATT7	0	//	A����������˥����7
#define	PARA_A_UCH_ATT8	0	//	A����������˥����8
#define	PARA_A_UCH_ATT9	0	//	A����������˥����9
#define	PARA_A_UCH_ATT10	0	//	A����������˥����10
#define	PARA_A_UCH_ATT11	0	//	A����������˥����11
#define	PARA_A_UCH_ATT12	0	//	A����������˥����12
#define	PARA_A_UCH_ATT13	0	//	A����������˥����13
#define	PARA_A_UCH_ATT14	0	//	A����������˥����14
#define	PARA_A_UCH_ATT15	0	//	A����������˥����15
#define	PARA_A_UCH_ATT16	0	//	A����������˥����16
#define	PARA_A_DL_PA_GAIN	0	//	A�����й�������
#define	PARA_A_UL_PA_GAIN	0	//	A�����й�������
#define	PARA_A_TX_PLL_ST	0x8308	//	A������PLL״̬,287 2ΪTX_VCO����������ʧ��
#define	PARA_A_RX_PLL_ST	0x8300	//	A������PLL״̬,247 2ΪRX_VCO����������ʧ��
#define	PARA_A_INIT_DA_ST	0	//	��ʼ��A��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define	PARA_A_BB_PLL_LOCK	0	//	A��BB PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define	PARA_A_FSAT		0	//	A��ǰ��AD����״̬
#define	PARA_A_DSAT		0	//	A�κ��DA���״̬
#define	PARA_A_PA_VG_EN	0	//	A�ι���դѹ״̬
#define	PARA_A_PA_VT	0	//	A�ι��Źܵ�ѹ��ʾ
#define	PARA_A_Modulator_EN	0	//	A�ε�����״̬
#define	PARA_A_LNA_VT	0	//	A�����е����LNA��ѹ
#define	PARA_A_LNA1_ST		0x8214	//	����LNA1״̬
#define	PARA_A_LNA2_ST		0x8215	//	����LNA2״̬
#define	PARA_A_BUSY_TIME	0x8892	//	A������ʱ϶ռ����
#define	PARA_A_PRI_ADD 	0xf002	//	A��ģ���ַ(�ں���Э���У�����λΪ���е�ַ������λΪ���е�ַ)
#define	PARA_A_UL_POW_1B	0x831e	//	A�����������ܹ���
#define 	PARA_A_DL_POW_1B	0x8390	//	A�����������ܹ���
#define 	PARA_A_DCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define 	PARA_A_UCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define	PARA_B_CHANNEL_COUNT	0x8889	//	B��֧�ֵ�ͨ����
#define	PARA_B_DL_WORK_EN	0x08a0	//	B�����й���ʹ��
#define	PARA_B_UL_WORK_EN	0x08a1	//	B�����й���ʹ��
#define	PARA_B_DPOW_MODE	0	//	B�����й��ʿ��Ʒ�ʽ
#define	PARA_B_UPOW_MODE	0	//	B�����й��ʿ��Ʒ�ʽ
#define	PARA_B_LTHR_EN		0x0770	//	B�����е�������ʹ��
#define	PARA_B_LTHR_UP		0	//	B�ε�������������
#define	PARA_B_LTHR_DN		0x08b0	//	B�ε�������������
#define	PARA_B_DCH_EN1		0x08d0	//	B������ͨ������ʹ��1
#define	PARA_B_DCH_EN2		0x08d1	//	B������ͨ������ʹ��2
#define	PARA_B_DCH_EN3		0x08d2	//	B������ͨ������ʹ��3
#define	PARA_B_DCH_EN4		0x08d3	//	B������ͨ������ʹ��4
#define	PARA_B_DCH_EN5		0x08d4	//	B������ͨ������ʹ��5
#define	PARA_B_DCH_EN6		0x08d5	//	B������ͨ������ʹ��6
#define	PARA_B_DCH_EN7		0x08d6	//	B������ͨ������ʹ��7
#define	PARA_B_DCH_EN8		0x08d7	//	B������ͨ������ʹ��8
#define	PARA_B_DCH_EN9		0x08d8	//	B������ͨ������ʹ��9
#define	PARA_B_DCH_EN10		0x08d9	//	B������ͨ������ʹ��10
#define	PARA_B_DCH_EN11		0x08dA	//	B������ͨ������ʹ��11
#define	PARA_B_DCH_EN12		0x08dB	//	B������ͨ������ʹ��12
#define	PARA_B_DCH_EN13		0x08dC	//	B������ͨ������ʹ��13
#define	PARA_B_DCH_EN14		0x08dD	//	B������ͨ������ʹ��14
#define	PARA_B_DCH_EN15		0x08dE	//	B������ͨ������ʹ��15
#define	PARA_B_DCH_EN16		0x08dF	//	B������ͨ������ʹ��16
#define	PARA_B_UCH_EN1		0x08d0	//	B������ͨ������ʹ��1
#define	PARA_B_UCH_EN2		0x08d1	//	B������ͨ������ʹ��2
#define	PARA_B_UCH_EN3		0x08d2	//	B������ͨ������ʹ��3
#define	PARA_B_UCH_EN4		0x08d3	//	B������ͨ������ʹ��4
#define	PARA_B_UCH_EN5		0x08d4	//	B������ͨ������ʹ��5
#define	PARA_B_UCH_EN6		0x08d5	//	B������ͨ������ʹ��6
#define	PARA_B_UCH_EN7		0x08d6	//	B������ͨ������ʹ��7
#define	PARA_B_UCH_EN8		0x08d7	//	B������ͨ������ʹ��8
#define	PARA_B_UCH_EN9		0x08d8	//	B������ͨ������ʹ��9
#define	PARA_B_UCH_EN10		0x08d9	//	B������ͨ������ʹ��10
#define	PARA_B_UCH_EN11		0x08dA	//	B������ͨ������ʹ��11
#define	PARA_B_UCH_EN12		0x08dB	//	B������ͨ������ʹ��12
#define	PARA_B_UCH_EN13		0x08dC	//	B������ͨ������ʹ��13
#define	PARA_B_UCH_EN14		0x08dD	//	B������ͨ������ʹ��14
#define	PARA_B_UCH_EN15		0x08dE	//	B������ͨ������ʹ��15
#define	PARA_B_UCH_EN16		0x08dF	//	B������ͨ������ʹ��16
#define	PARA_B_DCH_GAIN1	0x0840	//	B������ѡƵͨ���Ŵ�������1
#define	PARA_B_DCH_GAIN2	0x0841	//	B������ѡƵͨ���Ŵ�������2
#define	PARA_B_DCH_GAIN3	0x0842	//	B������ѡƵͨ���Ŵ�������3
#define	PARA_B_DCH_GAIN4	0x0843	//	B������ѡƵͨ���Ŵ�������4
#define	PARA_B_DCH_GAIN5	0x0844	//	B������ѡƵͨ���Ŵ�������5
#define	PARA_B_DCH_GAIN6	0x0845	//	B������ѡƵͨ���Ŵ�������6
#define	PARA_B_DCH_GAIN7	0x0846	//	B������ѡƵͨ���Ŵ�������7
#define	PARA_B_DCH_GAIN8	0x0847	//	B������ѡƵͨ���Ŵ�������8
#define	PARA_B_DCH_GAIN9	0x0848	//	B������ѡƵͨ���Ŵ�������9
#define	PARA_B_DCH_GAIN10	0x0849	//	B������ѡƵͨ���Ŵ�������10
#define	PARA_B_DCH_GAIN11	0x084A	//	B������ѡƵͨ���Ŵ�������11
#define	PARA_B_DCH_GAIN12	0x084B	//	B������ѡƵͨ���Ŵ�������12
#define	PARA_B_DCH_GAIN13	0x084C	//	B������ѡƵͨ���Ŵ�������13
#define	PARA_B_DCH_GAIN14	0x084D	//	B������ѡƵͨ���Ŵ�������14
#define	PARA_B_DCH_GAIN15	0x084E	//	B������ѡƵͨ���Ŵ�������15
#define	PARA_B_DCH_GAIN16	0x084F	//	B������ѡƵͨ���Ŵ�������16
#define	PARA_B_UCH_GAIN1	0x0850	//	B������ѡƵͨ���Ŵ�������1
#define	PARA_B_UCH_GAIN2	0x0851	//	B������ѡƵͨ���Ŵ�������2
#define	PARA_B_UCH_GAIN3	0x0852	//	B������ѡƵͨ���Ŵ�������3
#define	PARA_B_UCH_GAIN4	0x0853	//	B������ѡƵͨ���Ŵ�������4
#define	PARA_B_UCH_GAIN5	0x0854	//	B������ѡƵͨ���Ŵ�������5
#define	PARA_B_UCH_GAIN6	0x0855	//	B������ѡƵͨ���Ŵ�������6
#define	PARA_B_UCH_GAIN7	0x0856	//	B������ѡƵͨ���Ŵ�������7
#define	PARA_B_UCH_GAIN8	0x0857	//	B������ѡƵͨ���Ŵ�������8
#define	PARA_B_UCH_GAIN9	0x0858	//	B������ѡƵͨ���Ŵ�������9
#define	PARA_B_UCH_GAIN10	0x0859	//	B������ѡƵͨ���Ŵ�������10
#define	PARA_B_UCH_GAIN11	0x085A	//	B������ѡƵͨ���Ŵ�������11
#define	PARA_B_UCH_GAIN12	0x085B	//	B������ѡƵͨ���Ŵ�������12
#define	PARA_B_UCH_GAIN13	0x085C	//	B������ѡƵͨ���Ŵ�������13
#define	PARA_B_UCH_GAIN14	0x085D	//	B������ѡƵͨ���Ŵ�������14
#define	PARA_B_UCH_GAIN15	0x085E	//	B������ѡƵͨ���Ŵ�������15
#define	PARA_B_UCH_GAIN16	0x085F	//	B������ѡƵͨ���Ŵ�������16
#define	PARA_B_DCH_ATT1		0x0324	//	B�������������˥����1
#define	PARA_B_DCH_ATT2		0	//	B�������������˥����2
#define	PARA_B_DCH_ATT3		0	//	B�������������˥����3
#define	PARA_B_DCH_ATT4		0	//	B�������������˥����4
#define	PARA_B_DCH_ATT5		0	//	B�������������˥����5
#define	PARA_B_DCH_ATT6		0	//	B�������������˥����6
#define	PARA_B_DCH_ATT7		0	//	B�������������˥����7
#define	PARA_B_DCH_ATT8		0	//	B�������������˥����8
#define	PARA_B_DCH_ATT9		0	//	B�������������˥����9
#define	PARA_B_DCH_ATT10	0	//	B�������������˥����10
#define	PARA_B_DCH_ATT11	0	//	B�������������˥����11
#define	PARA_B_DCH_ATT12	0	//	B�������������˥����12
#define	PARA_B_DCH_ATT13	0	//	B�������������˥����13
#define	PARA_B_DCH_ATT14	0	//	B�������������˥����14
#define	PARA_B_DCH_ATT15	0	//	B�������������˥����15
#define	PARA_B_DCH_ATT16	0	//	B�������������˥����16
#define	PARA_B_UCH_ATT1		0//0x0320	//	B��������������˥����1
#define	PARA_B_UCH_ATT2		0	//	B��������������˥����2
#define	PARA_B_UCH_ATT3		0	//	B��������������˥����3
#define	PARA_B_UCH_ATT4		0	//	B��������������˥����4
#define	PARA_B_UCH_ATT5		0	//	B��������������˥����5
#define	PARA_B_UCH_ATT6		0	//	B��������������˥����6
#define	PARA_B_UCH_ATT7		0	//	B��������������˥����7
#define	PARA_B_UCH_ATT8		0	//	B��������������˥����8
#define	PARA_B_UCH_ATT9		0	//	B��������������˥����9
#define	PARA_B_UCH_ATT10	0	//	B��������������˥����10
#define	PARA_B_UCH_ATT11	0	//	B��������������˥����11
#define	PARA_B_UCH_ATT12	0	//	B��������������˥����12
#define	PARA_B_UCH_ATT13	0	//	B��������������˥����13
#define	PARA_B_UCH_ATT14	0	//	B��������������˥����14
#define	PARA_B_UCH_ATT15	0	//	B��������������˥����15
#define	PARA_B_UCH_ATT16	0	//	B��������������˥����16
#define	PARA_B_DL_PA_GAIN	0	//	B�����й�������
#define	PARA_B_UL_PA_GAIN	0	//	B�����й�������
#define	PARA_B_TX_PLL_ST	0x8308	//	B������PLL״̬,287 2ΪTX_VCO����������ʧ��
#define	PARA_B_RX_PLL_ST	0x8300	//	B������PLL״̬,247 2ΪRX_VCO����������ʧ��
#define	PARA_B_INIT_DA_ST	0	//	��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define	PARA_B_BB_PLL_LOCK	0	//	B��BB PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define	PARA_B_FSAT		0	//	B��ǰ��AD����״̬
#define	PARA_B_DSAT		0	//	B�κ��DA���״̬
#define	PARA_B_PA_VG_EN	0	//	B�ι���դѹ״̬
#define	PARA_B_PA_VT	0	//	B�ι��Źܵ�ѹ��ʾ
#define	PARA_B_Modulator_EN	0	//	B�ε�����״̬
#define	PARA_B_LNA_VT	0	//	B�����е����LNA��ѹ
#define	PARA_B_LNA1_ST		0x8214	//	����LNA1״̬
#define	PARA_B_LNA2_ST		0x8215	//	����LNA2״̬
#define	PARA_B_BUSY_TIME	0x8892	//	B������ʱ϶ռ����
#define	PARA_B_PRI_ADD 		0xf002	//	B��ģ���ַ(�ں���Э���У�����λΪ���е�ַ������λΪ���е�ַ)
#define	PARA_B_UL_POW_1B	0x831e	//	B�����������ܹ���
#define 	PARA_B_DL_POW_1B	0x8390	//	B�����������ܹ���
#define 	PARA_B_DCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define 	PARA_B_UCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥����  ��rf
#define	PARA_C_CHANNEL_COUNT	0x8889	//	C��֧�ֵ�ͨ����
#define	PARA_C_DL_WORK_EN	0x08a0	//	C�����й���ʹ��
#define	PARA_C_UL_WORK_EN	0x08a1	//	C�����й���ʹ��
#define	PARA_C_DPOW_MODE	0	//	C�����й��ʿ��Ʒ�ʽ
#define	PARA_C_UPOW_MODE	0	//	C�����й��ʿ��Ʒ�ʽ
#define	PARA_C_LTHR_EN		0x0770	//	C�����е�������ʹ��
#define	PARA_C_LTHR_UP		0	//	C�ε�������������
#define	PARA_C_LTHR_DN		0x08b0	//	C�ε�������������
#define	PARA_C_DCH_EN1		0x08d0	//	C������ͨ������ʹ��1
#define	PARA_C_DCH_EN2		0x08d1	//	C������ͨ������ʹ��2
#define	PARA_C_DCH_EN3		0x08d2	//	C������ͨ������ʹ��3
#define	PARA_C_DCH_EN4		0x08d3	//	C������ͨ������ʹ��4
#define	PARA_C_DCH_EN5		0x08d4	//	C������ͨ������ʹ��5
#define	PARA_C_DCH_EN6		0x08d5	//	C������ͨ������ʹ��6
#define	PARA_C_DCH_EN7		0x08d6	//	C������ͨ������ʹ��7
#define	PARA_C_DCH_EN8		0x08d7	//	C������ͨ������ʹ��8
#define	PARA_C_DCH_EN9		0x08d8	//	C������ͨ������ʹ��9
#define	PARA_C_DCH_EN10		0x08d9	//	C������ͨ������ʹ��10
#define	PARA_C_UCH_EN1		0x08d0	//	C������ͨ������ʹ��1
#define	PARA_C_UCH_EN2		0x08d1	//	C������ͨ������ʹ��2
#define	PARA_C_UCH_EN3		0x08d2	//	C������ͨ������ʹ��3
#define	PARA_C_UCH_EN4		0x08d3	//	C������ͨ������ʹ��4
#define	PARA_C_UCH_EN5		0x08d4	//	C������ͨ������ʹ��5
#define	PARA_C_UCH_EN6		0x08d5	//	C������ͨ������ʹ��6
#define	PARA_C_UCH_EN7		0x08d6	//	C������ͨ������ʹ��7
#define	PARA_C_UCH_EN8		0x08d7	//	C������ͨ������ʹ��8
#define	PARA_C_UCH_EN9		0x08d8	//	C������ͨ������ʹ��9
#define	PARA_C_UCH_EN10		0x08d9	//	C������ͨ������ʹ��10
#define	PARA_C_DCH_GAIN1	0x0840	//	C������ѡƵͨ���Ŵ�������1
#define	PARA_C_DCH_GAIN2	0x0841	//	C������ѡƵͨ���Ŵ�������2
#define	PARA_C_DCH_GAIN3	0x0842	//	C������ѡƵͨ���Ŵ�������3
#define	PARA_C_DCH_GAIN4	0x0843	//	C������ѡƵͨ���Ŵ�������4
#define	PARA_C_DCH_GAIN5	0x0844	//	C������ѡƵͨ���Ŵ�������5
#define	PARA_C_DCH_GAIN6	0x0845	//	C������ѡƵͨ���Ŵ�������6
#define	PARA_C_DCH_GAIN7	0x0846	//	C������ѡƵͨ���Ŵ�������7
#define	PARA_C_DCH_GAIN8	0x0847	//	C������ѡƵͨ���Ŵ�������8
#define	PARA_C_DCH_GAIN9	0x0848	//	C������ѡƵͨ���Ŵ�������9
#define	PARA_C_DCH_GAIN10	0x0849	//	C������ѡƵͨ���Ŵ�������10
#define 	PARA_C_DCH_GAIN11 	0	// 	C������ѡƵͨ���Ŵ�������11
#define 	PARA_C_DCH_GAIN12 	0	// 	C������ѡƵͨ���Ŵ�������12
#define 	PARA_C_DCH_GAIN13 	0	// 	C������ѡƵͨ���Ŵ�������13
#define 	PARA_C_DCH_GAIN14 	0	// 	C������ѡƵͨ���Ŵ�������14
#define 	PARA_C_DCH_GAIN15 	0	// 	C������ѡƵͨ���Ŵ�������15
#define 	PARA_C_DCH_GAIN16 	0	// 	C������ѡƵͨ���Ŵ�������16
#define	PARA_C_UCH_GAIN1	0x0850	//	C������ѡƵͨ���Ŵ�������1
#define	PARA_C_UCH_GAIN2	0x0851	//	C������ѡƵͨ���Ŵ�������2
#define	PARA_C_UCH_GAIN3	0x0852	//	C������ѡƵͨ���Ŵ�������3
#define	PARA_C_UCH_GAIN4	0x0853	//	C������ѡƵͨ���Ŵ�������4
#define	PARA_C_UCH_GAIN5	0x0854	//	C������ѡƵͨ���Ŵ�������5
#define	PARA_C_UCH_GAIN6	0x0855	//	C������ѡƵͨ���Ŵ�������6
#define	PARA_C_UCH_GAIN7	0x0856	//	C������ѡƵͨ���Ŵ�������7
#define	PARA_C_UCH_GAIN8	0x0857	//	C������ѡƵͨ���Ŵ�������8
#define	PARA_C_UCH_GAIN9	0x0858	//	C������ѡƵͨ���Ŵ�������9
#define	PARA_C_UCH_GAIN10	0x0859	//	C������ѡƵͨ���Ŵ�������10
#define	PARA_C_UCH_GAIN11	0	//	C������ѡƵͨ���Ŵ�������11
#define	PARA_C_UCH_GAIN12	0	//	C������ѡƵͨ���Ŵ�������12
#define	PARA_C_UCH_GAIN13	0	//	C������ѡƵͨ���Ŵ�������13
#define	PARA_C_UCH_GAIN14	0	//	C������ѡƵͨ���Ŵ�������14
#define	PARA_C_UCH_GAIN15	0	//	C������ѡƵͨ���Ŵ�������15
#define	PARA_C_UCH_GAIN16	0	//	C������ѡƵͨ���Ŵ�������16
#define	PARA_C_DCH_ATT1		0x0324	//	C�������������˥����1
#define	PARA_C_DCH_ATT2		0	//	C�������������˥����2
#define	PARA_C_DCH_ATT3		0	//	C�������������˥����3
#define	PARA_C_DCH_ATT4		0	//	C�������������˥����4
#define	PARA_C_DCH_ATT5		0	//	C�������������˥����5
#define	PARA_C_DCH_ATT6		0	//	C�������������˥����6
#define	PARA_C_DCH_ATT7		0	//	C�������������˥����7
#define	PARA_C_DCH_ATT8		0	//	C�������������˥����8
#define	PARA_C_DCH_ATT9		0	//	C�������������˥����9
#define	PARA_C_DCH_ATT10	0	//	C�������������˥����10
#define	PARA_C_DCH_ATT11	0	//	C�������������˥����11
#define	PARA_C_DCH_ATT12	0	//	C�������������˥����12
#define	PARA_C_DCH_ATT13	0	//	C�������������˥����13
#define	PARA_C_DCH_ATT14	0	//	C�������������˥����14
#define	PARA_C_DCH_ATT15	0	//	C�������������˥����15
#define	PARA_C_DCH_ATT16	0	//	C�������������˥����16
#define	PARA_C_UCH_ATT1		0//0x0320	//	C��������������˥����1
#define	PARA_C_UCH_ATT2		0	//	C��������������˥����2
#define	PARA_C_UCH_ATT3		0	//	C��������������˥����3
#define	PARA_C_UCH_ATT4		0	//	C��������������˥����4
#define	PARA_C_UCH_ATT5		0	//	C��������������˥����5
#define	PARA_C_UCH_ATT6		0	//	C��������������˥����6
#define	PARA_C_UCH_ATT7		0	//	C��������������˥����7
#define	PARA_C_UCH_ATT8		0	//	C��������������˥����8
#define	PARA_C_UCH_ATT9		0	//	C��������������˥����9
#define	PARA_C_UCH_ATT10	0	//	C��������������˥����10
#define	PARA_C_UCH_ATT11	0	//	C��������������˥����11
#define	PARA_C_UCH_ATT12	0	//	C��������������˥����12
#define	PARA_C_UCH_ATT13	0	//	C��������������˥����13
#define	PARA_C_UCH_ATT14	0	//	C��������������˥����14
#define	PARA_C_UCH_ATT15	0	//	C��������������˥����15
#define	PARA_C_UCH_ATT16	0	//	C��������������˥����16
#define	PARA_C_DL_PA_GAIN	0	//	C�����й�������
#define	PARA_C_UL_PA_GAIN	0	//	C�����й�������
#define	PARA_C_TX_PLL_ST	0x8308	//	C������PLL״̬,287 2ΪTX_VCO����������ʧ��
#define	PARA_C_RX_PLL_ST	0x8300	//	C������PLL״̬,247 2ΪRX_VCO����������ʧ��
#define	PARA_C_INIT_DA_ST	0	//	C��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define	PARA_C_BB_PLL_LOCK	0	//	C��BB PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define	PARA_C_FSAT		0	//	C��ǰ��AD����״̬
#define	PARA_C_DSAT		0	//	C�κ��DA���״̬
#define	PARA_C_PA_VG_EN	0	//	C�ι���դѹ״̬
#define	PARA_C_PA_VT	0	//	C�ι��Źܵ�ѹ��ʾ
#define	PARA_C_Modulator_EN	0	//	C�ε�����״̬
#define	PARA_C_LNA_VT	0	//	C�����е����LNA��ѹ
#define	PARA_C_LNA1_ST		0x8214	//	C����LNA1״̬
#define	PARA_C_LNA2_ST		0x8215	//	C����LNA2״̬
#define	PARA_C_BUSY_TIME	0x8892	//	C������ʱ϶ռ����
#define	PARA_C_PRI_ADD 		0xf002	//	C��ģ���ַ(�ں���Э���У�����λΪ���е�ַ������λΪ���е�ַ)
#define	PARA_C_UL_POW_1B	0x831e	//	C�����������ܹ���
#define 	PARA_C_DL_POW_1B	0x8390	//	C�����������ܹ���
#define 	PARA_C_DCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define 	PARA_C_UCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥����  ��rf
#define	PARA_D_CHANNEL_COUNT	0x8889	//	D��֧�ֵ�ͨ����
#define	PARA_D_DL_WORK_EN	0x08a0	//	D�����й���ʹ��
#define	PARA_D_UL_WORK_EN	0x08a1	//	D�����й���ʹ��
#define	PARA_D_DPOW_MODE	0	//	D�����й��ʿ��Ʒ�ʽ
#define	PARA_D_UPOW_MODE	0	//	D�����й��ʿ��Ʒ�ʽ
#define	PARA_D_LTHR_EN		0x0770	//	D�����е�������ʹ��
#define	PARA_D_LTHR_UP		0	//	D�ε�������������
#define	PARA_D_LTHR_DN		0x08b0	//	D�ε�������������
#define	PARA_D_DCH_EN1		0x08d0	//	D������ͨ������ʹ��1
#define	PARA_D_DCH_EN2		0x08d1	//	D������ͨ������ʹ��2
#define	PARA_D_DCH_EN3		0x08d2	//	D������ͨ������ʹ��3
#define	PARA_D_DCH_EN4		0x08d3	//	D������ͨ������ʹ��4
#define	PARA_D_DCH_EN5		0x08d4	//	D������ͨ������ʹ��5
#define	PARA_D_DCH_EN6		0x08d5	//	D������ͨ������ʹ��6
#define	PARA_D_DCH_EN7		0x08d6	//	D������ͨ������ʹ��7
#define	PARA_D_DCH_EN8		0x08d7	//	D������ͨ������ʹ��8
#define	PARA_D_DCH_EN9		0x08d8	//	D������ͨ������ʹ��9
#define	PARA_D_DCH_EN10	0x08d9	//	D������ͨ������ʹ��10
#define	PARA_D_UCH_EN1		0x08d0	//	D������ͨ������ʹ��1
#define	PARA_D_UCH_EN2		0x08d1	//	D������ͨ������ʹ��2
#define	PARA_D_UCH_EN3		0x08d2	//	D������ͨ������ʹ��3
#define	PARA_D_UCH_EN4		0x08d3	//	D������ͨ������ʹ��4
#define	PARA_D_UCH_EN5		0x08d4	//	D������ͨ������ʹ��5
#define	PARA_D_UCH_EN6		0x08d5	//	D������ͨ������ʹ��6
#define	PARA_D_UCH_EN7		0x08d6	//	D������ͨ������ʹ��7
#define	PARA_D_UCH_EN8		0x08d7	//	D������ͨ������ʹ��8
#define	PARA_D_UCH_EN9		0x08d8	//	D������ͨ������ʹ��9
#define	PARA_D_UCH_EN10	0x08d9	//	D������ͨ������ʹ��10
#define	PARA_D_DCH_GAIN1	0x0840	//	D������ѡƵͨ���Ŵ�������1
#define	PARA_D_DCH_GAIN2	0x0841	//	D������ѡƵͨ���Ŵ�������2
#define	PARA_D_DCH_GAIN3	0x0842	//	D������ѡƵͨ���Ŵ�������3
#define	PARA_D_DCH_GAIN4	0x0843	//	D������ѡƵͨ���Ŵ�������4
#define	PARA_D_DCH_GAIN5	0x0844	//	D������ѡƵͨ���Ŵ�������5
#define	PARA_D_DCH_GAIN6	0x0845	//	D������ѡƵͨ���Ŵ�������6
#define	PARA_D_DCH_GAIN7	0x0846	//	D������ѡƵͨ���Ŵ�������7
#define	PARA_D_DCH_GAIN8	0x0847	//	D������ѡƵͨ���Ŵ�������8
#define	PARA_D_DCH_GAIN9	0x0848	//	D������ѡƵͨ���Ŵ�������9
#define	PARA_D_DCH_GAIN10	0x0849	//	D������ѡƵͨ���Ŵ�������10
#define	PARA_D_DCH_GAIN11	0	//	D������ѡƵͨ���Ŵ�������11
#define	PARA_D_DCH_GAIN12	0	//	D������ѡƵͨ���Ŵ�������12
#define	PARA_D_DCH_GAIN13	0	//	D������ѡƵͨ���Ŵ�������13
#define	PARA_D_DCH_GAIN14	0	//	D������ѡƵͨ���Ŵ�������14
#define	PARA_D_DCH_GAIN15	0	//	D������ѡƵͨ���Ŵ�������15
#define	PARA_D_DCH_GAIN16	0	//	D������ѡƵͨ���Ŵ�������16
#define	PARA_D_UCH_GAIN1	0x0850	//	D������ѡƵͨ���Ŵ�������1
#define	PARA_D_UCH_GAIN2	0x0851	//	D������ѡƵͨ���Ŵ�������2
#define	PARA_D_UCH_GAIN3	0x0852	//	D������ѡƵͨ���Ŵ�������3
#define	PARA_D_UCH_GAIN4	0x0853	//	D������ѡƵͨ���Ŵ�������4
#define	PARA_D_UCH_GAIN5	0x0854	//	D������ѡƵͨ���Ŵ�������5
#define	PARA_D_UCH_GAIN6	0x0855	//	D������ѡƵͨ���Ŵ�������6
#define	PARA_D_UCH_GAIN7	0x0856	//	D������ѡƵͨ���Ŵ�������7
#define	PARA_D_UCH_GAIN8	0x0857	//	D������ѡƵͨ���Ŵ�������8
#define	PARA_D_UCH_GAIN9	0x0858	//	D������ѡƵͨ���Ŵ�������9
#define	PARA_D_UCH_GAIN10	0x0859	//	D������ѡƵͨ���Ŵ�������10
#define	PARA_D_UCH_GAIN11	0	//	D������ѡƵͨ���Ŵ�������11
#define	PARA_D_UCH_GAIN12	0	//	D������ѡƵͨ���Ŵ�������12
#define	PARA_D_UCH_GAIN13	0	//	D������ѡƵͨ���Ŵ�������13
#define	PARA_D_UCH_GAIN14	0	//	D������ѡƵͨ���Ŵ�������14
#define	PARA_D_UCH_GAIN15	0	//	D������ѡƵͨ���Ŵ�������15
#define	PARA_D_UCH_GAIN16	0	//	D������ѡƵͨ���Ŵ�������16
#define	PARA_D_DCH_ATT1		0x0324	//	D�������������˥����1
#define	PARA_D_DCH_ATT2		0	//	D�������������˥����2
#define	PARA_D_DCH_ATT3		0	//	D�������������˥����3
#define	PARA_D_DCH_ATT4		0	//	D�������������˥����4
#define	PARA_D_DCH_ATT5		0	//	D�������������˥����5
#define	PARA_D_DCH_ATT6		0	//	D�������������˥����6
#define	PARA_D_DCH_ATT7		0	//	D�������������˥����7
#define	PARA_D_DCH_ATT8		0	//	D�������������˥����8
#define	PARA_D_DCH_ATT9		0	//	D�������������˥����9
#define	PARA_D_DCH_ATT10	0	//	D�������������˥����10
#define	PARA_D_DCH_ATT11	0	//	D�������������˥����11
#define	PARA_D_DCH_ATT12	0	//	D�������������˥����12
#define	PARA_D_DCH_ATT13	0	//	D�������������˥����13
#define	PARA_D_DCH_ATT14	0	//	D�������������˥����14
#define	PARA_D_DCH_ATT15	0	//	D�������������˥����15
#define	PARA_D_DCH_ATT16	0	//	D�������������˥����16
#define	PARA_D_UCH_ATT1		0//0x0320	//	D��������������˥����1
#define	PARA_D_UCH_ATT2		0	//	D��������������˥����2
#define	PARA_D_UCH_ATT3		0	//	D��������������˥����3
#define	PARA_D_UCH_ATT4		0	//	D��������������˥����4
#define	PARA_D_UCH_ATT5		0	//	D��������������˥����5
#define	PARA_D_UCH_ATT6		0	//	D��������������˥����6
#define	PARA_D_UCH_ATT7		0	//	D��������������˥����7
#define	PARA_D_UCH_ATT8		0	//	D��������������˥����8
#define	PARA_D_UCH_ATT9		0	//	D��������������˥����9
#define	PARA_D_UCH_ATT10	0	//	D��������������˥����10
#define	PARA_D_UCH_ATT11	0	//	D��������������˥����11
#define	PARA_D_UCH_ATT12	0	//	D��������������˥����12
#define	PARA_D_UCH_ATT13	0	//	D��������������˥����13
#define	PARA_D_UCH_ATT14	0	//	D��������������˥����14
#define	PARA_D_UCH_ATT15	0	//	D��������������˥����15
#define	PARA_D_UCH_ATT16	0	//	D��������������˥����16
#define	PARA_D_DL_PA_GAIN	0	//	D�����й�������
#define	PARA_D_UL_PA_GAIN	0	//	D�����й�������
#define	PARA_D_TX_PLL_ST	0x8308	//	D������PLL״̬,287 2ΪTX_VCO����������ʧ��
#define	PARA_D_RX_PLL_ST	0x8300	//	D������PLL״̬,247 2ΪRX_VCO����������ʧ��
#define	PARA_D_INIT_DA_ST	0	//	D��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define	PARA_D_BB_PLL_LOCK	0	//	D��BB PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define	PARA_D_FSAT		0	//	D��ǰ��AD����״̬
#define	PARA_D_DSAT		0	//	D�κ��DA���״̬
#define	PARA_D_PA_VG_EN	0	//	D�ι���դѹ״̬
#define	PARA_D_PA_VT	0	//	D�ι��Źܵ�ѹ��ʾ
#define	PARA_D_Modulator_EN	0	//	D�ε�����״̬
#define	PARA_D_LNA_VT	0	//	D�����е����LNA��ѹ
#define	PARA_D_LNA1_ST		0x8214	//	D����LNA1״̬
#define	PARA_D_LNA2_ST		0x8215	//	D����LNA2״̬
#define	PARA_D_BUSY_TIME	0x8892	//	D������ʱ϶ռ����
#define	PARA_D_PRI_ADD 		0xf002	//	D��ģ���ַ(�ں���Э���У�����λΪ���е�ַ������λΪ���е�ַ)
#define	PARA_D_UL_POW_1B	0x831e	//	D�����������ܹ���
#define 	PARA_D_DL_POW_1B	0x8390	//	D�����������ܹ���
#define 	PARA_D_DCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define 	PARA_D_UCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥����  ��rf
#define	PARA_FP1_EN	0x0927	//	��ڷ���ʹ��1
#define	PARA_FP2_EN	0x0928	//	��ڷ���ʹ��2
#define	PARA_FP3_EN	0x0929	//	��ڷ���ʹ��3
#define	PARA_FP4_EN	0x092A	//	��ڷ���ʹ��4
#define	PARA_FP5_EN	0x092B	//	��ڷ���ʹ��5
#define	PARA_FP6_EN	0x092C	//	��ڷ���ʹ��6
#define	PARA_FP7_EN	0x092D	//	��ڷ���ʹ��7
#define	PARA_FP8_EN	0x092E	//	��ڷ���ʹ��8
#define	PARA_FP9_EN	0x0	//	��ڷ���ʹ��9
#define	PARA_FP10_EN	0x0	//	��ڷ���ʹ��10
#define	PARA_FP11_EN	0x0	//	��ڷ���ʹ��11
#define	PARA_FP12_EN	0x0	//	��ڷ���ʹ��12
#define	PARA_FP13_EN	0x0	//	��ڷ���ʹ��13
#define	PARA_FP14_EN	0x0	//	��ڷ���ʹ��14
#define	PARA_FP15_EN	0x0	//	��ڷ���ʹ��15
#define	PARA_FP16_EN	0x0	//	��ڷ���ʹ��16
#define	PARA_FP1_ON_POS	0x8568	//	�����λ״̬1, 0-��λ	
#define	PARA_FP2_ON_POS	0x8569	//	�����λ״̬2, 0-��λ	
#define	PARA_FP3_ON_POS	0x856A	//	�����λ״̬3, 0-��λ	
#define	PARA_FP4_ON_POS	0x856B	//	�����λ״̬4, 0-��λ	
#define	PARA_FP5_ON_POS	0x856C	//	�����λ״̬5, 0-��λ	
#define	PARA_FP6_ON_POS	0x856D	//	�����λ״̬6, 0-��λ	
#define	PARA_FP7_ON_POS	0x856E	//	�����λ״̬7, 0-��λ	
#define	PARA_FP8_ON_POS	0x856F	//	�����λ״̬8, 0-��λ	
#define	PARA_FP9_ON_POS	0x8568	//	�����λ״̬9, 0-��λ	
#define	PARA_FP10_ON_POS	0x8569	//	�����λ״̬10, 0-��λ	
#define	PARA_FP11_ON_POS	0x856a	//	�����λ״̬11, 0-��λ	
#define	PARA_FP12_ON_POS	0x856b	//	�����λ״̬12, 0-��λ	
#define	PARA_FP13_ON_POS	0x856c	//	�����λ״̬13, 0-��λ	
#define	PARA_FP14_ON_POS	0x856d	//	�����λ״̬14, 0-��λ
#define	PARA_FP15_ON_POS	0x856e	//	�����λ״̬15, 0-��λ
#define	PARA_FP16_ON_POS	0x856f	//	�����λ״̬16, 0-��λ
#define	PARA_FP1_LOS	0x8738//0x8730	//	���1�źŶ�ʧ״̬	
#define	PARA_FP2_LOS	0x8739//0x8731	//	���2�źŶ�ʧ״̬	
#define	PARA_FP3_LOS	0x873a//0x8732	//	���3�źŶ�ʧ״̬	
#define	PARA_FP4_LOS	0x873b//0x8733	//	���4�źŶ�ʧ״̬	
#define	PARA_FP5_LOS	0x873c//0x8734	//	���5�źŶ�ʧ״̬	
#define	PARA_FP6_LOS	0x873d//0x8735	//	���6�źŶ�ʧ״̬	
#define	PARA_FP7_LOS	0x8598//0x8736	//	���7�źŶ�ʧ״̬	
#define	PARA_FP8_LOS	0x8599//0x8737	//	���8�źŶ�ʧ״̬	
#define	PARA_FP9_LOS	0//0x8738	//	���9�źŶ�ʧ״̬
#define	PARA_FP10_LOS	0//0x8739	//	���10�źŶ�ʧ״̬	
#define	PARA_FP11_LOS	0//0x873a	//	���11�źŶ�ʧ״̬	
#define	PARA_FP12_LOS	0//0x873b	//	���12�źŶ�ʧ״̬	
#define	PARA_FP13_LOS	0//0x873c	//	���13�źŶ�ʧ״̬
#define	PARA_FP14_LOS	0//0x873d	//	���14�źŶ�ʧ״̬
#define	PARA_FP15_LOS	0//0x873e	//	���15�źŶ�ʧ״̬
#define	PARA_FP16_LOS	0//0x873f	//	���16�źŶ�ʧ״̬
#define	PARA_FP1_LOF	0x878a//0x8780	//	���1֡��ʧ״̬	
#define	PARA_FP2_LOF	0x878b//0x8781	//	���2֡��ʧ״̬	
#define	PARA_FP3_LOF	0x878c//0x8782	//	���3֡��ʧ״̬	
#define	PARA_FP4_LOF	0x878d//0x8783	//	���4֡��ʧ״̬	
#define	PARA_FP5_LOF	0x87ab//0x8784	//	���5֡��ʧ״̬	
#define	PARA_FP6_LOF	0x87ac//0x8785	//	���6֡��ʧ״̬	
#define	PARA_FP7_LOF	0x87ad//0x8786	//	���7֡��ʧ״̬	
#define	PARA_FP8_LOF	0x87ae//0x8787	//	���8֡��ʧ״̬	
#define	PARA_FP9_LOF	0//0x8788	//	���9֡��ʧ״̬	
#define	PARA_FP10_LOF	0//0x8789	//	���10֡��ʧ״̬	
#define	PARA_FP11_LOF	0//0x878a	//	���11֡��ʧ״̬	
#define	PARA_FP12_LOF	0//0x878b	//	���12֡��ʧ״̬	
#define	PARA_FP13_LOF	0//0x878c	//	���13֡��ʧ״̬
#define	PARA_FP14_LOF	0//0x878d	//	���14֡��ʧ״̬
#define	PARA_FP15_LOF	0//0x878e	//	���15֡��ʧ״̬
#define	PARA_FP16_LOF	0//0x878f	//	���16֡��ʧ״̬
#define	PARA_OPT_LOF	0//0x87ad	//	֡��ʧ״̬
#define	PARA_SERDES1_PLL_ST	0x878e	//	SerDesоƬPLL״̬1	
#define	PARA_SERDES2_PLL_ST	0x878f	//	SerDesоƬPLL״̬2	
#define	PARA_SERDES3_PLL_ST	0x8790	//	SerDesоƬPLL״̬3	
#define	PARA_SERDES4_PLL_ST	0x8791	//	SerDesоƬPLL״̬4	
#define	PARA_SERDES5_PLL_ST	0x8898	//	SerDesоƬPLL״̬5	
#define	PARA_SERDES6_PLL_ST	0x8899	//	SerDesоƬPLL״̬6	
#define	PARA_SERDES7_PLL_ST	0x889a	//	SerDesоƬPLL״̬7	
#define	PARA_SERDES8_PLL_ST	0x889b	//	SerDesоƬPLL״̬8	
#define	PARA_SERDES9_PLL_ST	0x85a8	//	SerDesоƬPLL״̬9	
#define	PARA_SERDES10_PLL_ST	0x85a9	//	SerDesоƬPLL״̬10	
#define	PARA_SERDES11_PLL_ST	0x85aa	//	SerDesоƬPLL״̬11	
#define	PARA_SERDES12_PLL_ST	0x85ab	//	SerDesоƬPLL״̬12	
#define	PARA_SERDES13_PLL_ST	0x85ac	//	SerDesоƬPLL״̬13
#define	PARA_SERDES14_PLL_ST	0x85ad	//	SerDesоƬPLL״̬14
#define	PARA_SERDES15_PLL_ST	0x85ae	//	SerDesоƬPLL״̬15
#define	PARA_SERDES16_PLL_ST	0x85af	//	SerDesоƬPLL״̬16
#define	PARA_TOPO_CHG_ALM	0x873F//0x87af	//	��·״̬�澯
#define	PARA_BER_ALARM	0//0x87ae	//	������ƫ�߸澯
#define	PARA_LOAD_FPGA_ST	0x8854	//	����FPGA״̬
#define	PARA_FPGA_CLK_ST	0x8851	//	FPGA����״̬
#define	PARA_INIT_CLK_ST	0	//	��ʼ��ʱ��״̬
#define	PARA_INIT_AD_ST	0	//	��ʼ��AD״̬
#define	PARA_INIT_FB_AD_ST	0	//	��ʼ������AD״̬
#define	PARA_CLK_PLL_ST	0x884e	//	CLK PLL״̬
#define	PARA_CLK_REF_ST	0x884f	//	CLK �ο�״̬
#define	PARA_RE_NODE_MODE	0x889d	//	RE�ڵ�ģʽ
#define	PARA_BOARD_TEMP	0x8844	//	�����¶�
#define	PARA_CLK_VCO_VT	0	//	ʱ��VCO��ѹ
#define	PARA_PWR_9V0_VT	0	//	9V��Դ��ѹ
#define	PARA_PWR_5V5_VT	0	//	5.5V��Դ��ѹ
#define	PARA_PWR_3V6_VT	0	//	3.6V��Դ��ѹ
#define	PARA_PWR_1V2_VT	0	//	1.2V��Դ��ѹ
#define	PARA_PWR_2V5_VT	0	//	1.2V��Դ��ѹ
#define	PARA_PRI_PROTOCAL_V	0xf003	//	Э��汾
#define	PARA_MODULE_HRI_ID	0	//	ID
#define 	PARA_WORK_ERROR	0	// ϵͳ����״̬��1-�й���
#define 	PARA_TRAFFIC_END	0x88ac	// ������ͳ�ƽ�����־
#define 	PARA_DELAY_MODE	0x098f	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define	PARA_TD_SYNC_ST			0x862a		// TDͬ��״̬: 1-��ͬ����0-δͬ��
#define	PARA_TD_WORK_MODE 		0x060c	// [WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���, ÿ���ϵ������			
#define 	PARA_TD_T0_UD		0x08a0	// TDʱ϶0�����б�־:0-���У�1-����			
#define 	PARA_TD_T1_UD		0x08a1	// TDʱ϶1�����б�־:0-���У�1-����			
#define 	PARA_TD_T2_UD		0x08a2	// TDʱ϶2�����б�־:0-���У�1-����			
#define 	PARA_TD_T3_UD		0x08a3	// TDʱ϶3�����б�־:0-���У�1-����			
#define 	PARA_TD_T4_UD		0x08a4	// TDʱ϶4�����б�־:0-���У�1-����			
#define 	PARA_TD_T5_UD		0x08a5	// TDʱ϶5�����б�־:0-���У�1-����			
#define 	PARA_TD_T6_UD		0x08a6	// TDʱ϶6�����б�־:0-���У�1-����			
#define	PARA_POWERUP_ST		0x8852	// 	���ְ��ϵ�״̬,ÿ������ʱ��1
#define	PARA_LOW_POWER			0x88ff//0x08ad	//	�͹���ģʽ:1-�͹���;	0-����		���� x0778   �������ʼ�����˺�ֻ��Ϊ�ο�
#define 	PARA_THR_PORT		0		// 	͸���˿�ѡ��0-485B, 1-RS232
#define	PARA_THR_BAUD		0		//	͸���˿ڲ����� 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define	PARA_CTRL_BAUD	0		//	���ƶ˿ڲ����� 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define	PARA_WLAN_CONN_ST1		0x87b2	// WLAN��״̬1: 0-������1-�쳣
#define	PARA_WLAN_CONN_ST2		0x87b3	// WLAN��״̬2: 0-������1-�쳣
#define	PARA_WLAN_CONN_ST3		0x87b4	// WLAN��״̬3: 0-������1-�쳣
#define	PARA_WLAN_CONN_ST4		0x87b7	// WLAN��״̬4: 0-������1-�쳣
#define	PARA_WLAN_SPEED1			0x87b8	// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
#define	PARA_WLAN_SPEED2			0x87b9		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
#define	PARA_WLAN_SPEED3			0x87ba		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
#define	PARA_WLAN_SPEED4			0x87bb		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
#define	PARA_GSM_BW_SEL			0		// ����汾GSM����ѡ��: 0-6M, 1-20M, 2-24M, 3-25M, ������Ч
#define	PARA_HX_DET_UADDR 0 // ����DETģ�����е�ַ, ��4λΪB��, ����λΪA��
#define	PARA_HX_LNA_UADDR 0 // ����LNAģ�����е�ַ, ��4λΪB��, ����λΪA��
#define	PARA_HX_DET_DADDR 0 // ����DETģ�����е�ַ, ��4λΪB��, ����λΪA��
#define	PARA_HX_LNA_DADDR 0 // ����LNAģ�����е�ַ, ��4λΪB��, ����λΪA��
#define 	PARA_FPS_AUTO_SCAN		0x0931		// �Զ�Ƶ����������ʹ��:1-�Զ�����������Ƶ��, 0-�ֶ�����
#define 	PARA_FPS_SWITCH_THD 		0 		// �Զ�Ƶ��������BCCH�����л�����
#define 	PARA_FPS_MOSVC_SEL		0x0925	// Ƶ������: ��Ӫ��ѡ��: 0-���ƶ�, 1-����ͨ, 2-���ƶ�, 255-�Զ�ѡ��
#define	PARA_FPS_RFRANGE_SEL	0x0924	// Ƶ������: Ƶ��ѡ��(����,��ģ����ʽΪ׼): 0-ȫƵ��, 1-900MHz, 2-1800MHz
#define 	PARA_FPS_BS_ID			0x8959	// Ƶ������: ��վʶ����
#define	PARA_FPS_CA_COUNT		0x895b	// Ƶ������: ��Ч�ŵ���
#define	PARA_FPS_BCCH_LK_ST		0x895c	// Ƶ������: ����BCCH״̬: 1-����, 0-ʧ��
#define	PARA_FPS_MOSVC_LK_ST		0x895d	// Ƶ������: ������Ӫ��״̬: 1-����, 0-ʧ��
#define	PARA_FPS_RFRANGE_LK_ST	0x895e	// Ƶ������: ����Ƶ��״̬: 1-����, 0-ʧ��
#define	PARA_FPS_BCCH_POW_M		0x8960	// Ƶ������: ��С��BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_1		0x8961	// Ƶ������: ��С��1BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_2		0x8962	// Ƶ������: ��С��2BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_3		0x8963	// Ƶ������: ��С��3BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_4		0x8964	// Ƶ������: ��С��4BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_5		0x8965	// Ƶ������: ��С��5BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_6		0x8966	// Ƶ������: ��С��6BCCH����ǿ��
#define	PARA_A_EXPA_WORK_EN		0xC401	// [WR]΢����: ��Ƶ�źſ���
#define	PARA_A_EXPA_DL_ATT		0xC441	// [WR]΢����: ����˥��ֵ
#define	PARA_A_EXPA_TEMP			0xC501	// [RO]΢����: �¶�
#define	PARA_A_EXPA_DL_POW		0xC503	// [RO]΢����: ����������ʵ�ƽ
#define	PARA_A_EXPA_SWR			0xC506	// [RO]΢����: ����פ����ֵ
#define	PARA_A_EXPA_POWER_DN	0xC301	// [RO]΢����: ��Դ����澯(3���Ӹ����ж�)
#define	PARA_A_EXPA_POWER_ERR	0xC302	// [RO]΢����: ��Դ���ϸ澯(3���Ӹ����ж�)
#define	PARA_A_EXPA_BATT_ERR		0xC304	// [RO]΢����: ���ģ���ع��ϸ澯(3���Ӹ����ж�)
#define	PARA_A_EXPA_POS_ALM		0xC305	// [RO]΢����: λ�ø澯
#define	PARA_A_EXPA_DOOR_ALM	0xC328	// [RO]΢����: �Ž��澯
#define	PARA_A_EXPA_WROK_ALM	0xC30D	// [RO]΢����: ���й��Ź��ϸ澯(3���Ӹ����ж�)
#define	PARA_A_EXPA_EXT1_ALM		0xC320	// [RO]΢����: �ⲿ�澯1
#define	PARA_A_EXPA_EXT2_ALM		0xC321	// [RO]΢����: �ⲿ�澯2
#define	PARA_A_EXPA_EXT3_ALM		0xC322	// [RO]΢����: �ⲿ�澯3
#define	PARA_A_EXPA_MAX_GAIN	0		// ΢����: ��˥�����棬���������
#define	PARA_A_EXPA_GAIN_THD		0		// ΢����: �������ޣ������������������ֵ
#define	PARA_A_EXPA_POW_THD		0		// ΢����: ���������������
#define	PARA_A_EXPA_POD_CMP 		0		// ΢����: �첨�ܹ��ʼ�ⲹ��ֵ,1�ֽ��з�����,���չ���Ϊ�첨�ܹ��ʼ��ϲ���ֵ
#define	PARA_MONITOR_VOL_OVER_THR 				0x0a62 			 // ��ص�ѹ������
#define 	PARA_MONITOR_VOL_OWE_THR 				0x0a63 			 // ��ص�ѹǷ����
#define 	PARA_DIGITAL_SINGNAL_ALARM 				0x8a68			 // �����ź��쳣�澯
#define 	PARA_HOST_DEVICE_LINK_SINGNAL_ALARM 	0x8a69			 // ���Ӽ����·�澯
#define 	PARA_MONITOR_BATTERY_ALARM 				0x8a6a			 // ���ģ���ع��ϸ澯
#define 	PARA_LOW_POWER_ALARM 					0x8a6b			 // ��Դ����澯
#define 	PARA_BATTERY_BREAKDOWN_ALARM 			0x8a6c			 // ��Դ���ϸ澯
#define 	PARA_POSITION_MOVE_ALARM					0x8a6f			 // λ�ø澯
#define 	PARA_A_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // A������������ʸ澯
#define 	PARA_A_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // A��������Ƿ���ʸ澯
#define 	PARA_B_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // B������������ʸ澯
#define 	PARA_B_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // B��������Ƿ���ʸ澯
#define 	PARA_C_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // C������������ʸ澯
#define 	PARA_C_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // C��������Ƿ���ʸ澯
#define 	PARA_D_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // D������������ʸ澯
#define 	PARA_D_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // D��������Ƿ���ʸ澯
#define 	PARA_TD_D_OVER_SLOT1_THR_ALARM 			0x8a66			 // TD�������뵼Ƶ�����ʸ澯
#define 	PARA_TD_D_OWE_SLOT1_THR_ALARM 			0x8a67			 // TD�������뵼ƵǷ���ʸ澯
#define 	PARA_RE_DATA_LAN_ST1     0x8a40     //����PHYоƬ����״̬  0: ������1: �澯
#define 	PARA_RE_CASCADE_LAN_ST1   0x8a48     //�������ڵĹ���״̬  0: ������1: �澯
#define 	PARA_RE_DATA_LAN_SYS_ST1  0x8a4a     //��������ͬ��״̬  0: ͬ����1: ʧ��
#define 	PARA_RE_CASCADE_LAN_SYS_ST1  0x8a52     //��������ͬ��״̬  0: ͬ����1: ʧ��
#define 	PARA_A_RF_POW_SWR           	0x8a32     //A�θ��ǵ�Ԫ����פ����
#define 	PARA_A_RF_OUT_POW_H_THR   		0x0a50     //A�θ��ǵ�Ԫ�������������
#define 	PARA_A_RF_OUT_POW_L_THR   		0x0a51     //A�θ��ǵ�Ԫ���Ƿ��������
#define 	PARA_B_RF_POW_SWR            	0x8a32     //B�θ��ǵ�Ԫ����פ����
#define 	PARA_B_RF_OUT_POW_H_THR   		0x0a50     //A�θ��ǵ�Ԫ�������������
#define 	PARA_B_RF_OUT_POW_L_THR   		0x0a51     //A�θ��ǵ�Ԫ���Ƿ��������
#define 	PARA_C_RF_POW_SWR           	0x8a32     //A�θ��ǵ�Ԫ����פ����
#define 	PARA_C_RF_OUT_POW_H_THR   		0x0a50     //A�θ��ǵ�Ԫ�������������
#define 	PARA_C_RF_OUT_POW_L_THR   		0x0a51     //A�θ��ǵ�Ԫ���Ƿ��������
#define 	PARA_D_RF_POW_SWR            	0x8a32     //B�θ��ǵ�Ԫ����פ����
#define 	PARA_D_RF_OUT_POW_H_THR   		0x0a50     //A�θ��ǵ�Ԫ�������������
#define 	PARA_D_RF_OUT_POW_L_THR   		0x0a51     //A�θ��ǵ�Ԫ���Ƿ��������
#define 	PARA_PWR_3V3_1_VT	0		// 3.3V��Դ��ѹ
#define 	PARA_PWR_3V3_2_VT	0		//	3.3V��Դ��ѹ
#define 	PARA_PWR_1V8_VT		0			// 1.8V��Դ��ѹ
#define 	PARA_PWR_1V5_VT		0			 // 1.5V��Դ��ѹ
#define 	PARA_A_DL_RF_EN 	0x08a0	// 	A��������Ƶʹ��	
#define 	PARA_A_UL_RF_EN 	0x08a1	// 	A��������Ƶʹ��	
#define 	PARA_B_DL_RF_EN 	0x08a0	// 	B��������Ƶʹ��	
#define 	PARA_B_UL_RF_EN		0x08a1	// 	B��������Ƶʹ��	
#define 	PARA_C_DL_RF_EN 	0x08a0	// 	C��������Ƶʹ��	
#define 	PARA_C_UL_RF_EN 	0x08a1	// 	C��������Ƶʹ��	
#define 	PARA_D_DL_RF_EN 	0x08a0	// 	D��������Ƶʹ��	
#define 	PARA_D_UL_RF_EN 	0x08a1	// 	D��������Ƶʹ��	
#define 	PARA_METER_OFFSET	0x0a66	//	����ƫ��ֵ����
#define 	PARA_METER_OFFSET_B	0x0a66	//	����ƫ��ֵ����
#define 	PARA_METER_OFFSET_C	0x0a66	//	����ƫ��ֵ����
#define 	PARA_METER_OFFSET_D	0x0a66	//	����ƫ��ֵ����
#define 	PARA_C_TD_TYPE_SELECT	0x0631	//686	// TD�������뵼Ƶ�����ʸ澯					
#define 	PARA_C_TD_NORMAL_CP		0x0632	//716	//	TDD����ʱ϶ NORMAL_CP
#define 	PARA_C_TD_EXTENDED_CP	0x0a6c	//717	//	TDD����ʱ϶ NORMAL_CP
#define 	PARA_C_TD_SYNC_ST	0x862a	//687	//	TDͬ��״̬:	0-��ͬ����1-δͬ��			
#define 	PARA_C_TD_WORK_MODE	0x060c	//688	//	[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������			
#define 	PARA_C_TD_DL_OVER_SLOT1_THR_ALARM	0x8a66	//689	// TD�������뵼Ƶ�����ʸ澯					
#define 	PARA_C_TD_DL_OWE_SLOT1_THR_ALARM	0x8a67	//690	 // TD�������뵼ƵǷ���ʸ澯					
#define 	PARA_D_TD_TYPE_SELECT	0x0631	//691	// TD�������뵼Ƶ�����ʸ澯					
#define 	PARA_D_TD_NORMAL_CP		0x0632	//718	//	TDD����ʱ϶ NORMAL_CP
#define 	PARA_D_TD_EXTENDED_CP	0x0a6c	//719	//	TDD����ʱ϶ NORMAL_CP
#define 	PARA_D_TD_SYNC_ST	0x862a	//692	//	TDͬ��״̬:	0-��ͬ����1-δͬ��			
#define 	PARA_D_TD_WORK_MODE	0x060c	//693	//	[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������			
#define 	PARA_D_TD_DL_OVER_SLOT1_THR_ALARM	0x8a66	//694	// TD�������뵼Ƶ�����ʸ澯					
#define 	PARA_D_TD_DL_OWE_SLOT1_THR_ALARM	0x8a67	//695	 // TD�������뵼ƵǷ���ʸ澯					
#define 	PARA_C_TD_T0_UD	0	//696	//	TDʱ϶0�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T1_UD	0	//697	//	TDʱ϶1�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T2_UD	0	//698	//	TDʱ϶2�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T3_UD	0	//699	//	TDʱ϶3�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T4_UD	0	//700	//	TDʱ϶4�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T5_UD	0	//701	//	TDʱ϶5�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T6_UD	0	//702	//	TDʱ϶6�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T7_UD	0	//703	//	TDʱ϶7�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T8_UD	0	//704	//	TDʱ϶8�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T9_UD	0	//705	//	TDʱ϶9�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T0_UD	0	//706	//	TDʱ϶0�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T1_UD	0	//707	//	TDʱ϶1�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T2_UD	0	//708	//	TDʱ϶2�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T3_UD	0	//709	//	TDʱ϶3�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T4_UD	0	//710	//	TDʱ϶4�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T5_UD	0	//711	//	TDʱ϶5�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T6_UD	0	//712	//	TDʱ϶6�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T7_UD	0	//713	//	TDʱ϶7�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T8_UD	0	//714	//	TDʱ϶8�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T9_UD	0	//715	//	TDʱ϶9�����б�־:0-���У�1-����//#endif
#define	PARA_NOISE_TEST_EN	0	//	�������Կ���		
#define	PARA_FREQ_MODIF_VAL_D	0x0a6d		//	��������ֵ
#define	PARA_FREQ_MODIF_VAL_B	0x0a6e		//	��������ֵ
#define	PARA_FREQ_MODIF_VAL_A	0x0a6f		//	��������ֵ
#define	PARA_B_TDS_2TH_BREAKING_POINT_SET	0x0609		//	TDS �ڶ�ת��������
#define 	PARA_DELAY_MODE_A	0x8660	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define 	PARA_DELAY_MODE_B	0x8660	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define 	PARA_DELAY_MODE_C	0x8660	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define 	PARA_DELAY_MODE_D	0x8660	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define	PARA_REE_CIRCUIT_ALARM	 		0
#define	PARA_REE_WLAN_CONN_ST			0
#define	PARA_DL_POWER_MAX			0
#define 	PARA_SLOT_TIME_EN_B	0x0	// ʱ϶����Զ���⿪��		
#define 	PARA_SLOT_TIME_DISTRI_B	0	// ʱ϶��ȷֲ�	BIT0��1����15���,BIT1��1����24���,	BIT2��1����33���			
#define 	PARA_VERSION_FLAG		0	// �汾��ʶ		
#define 	PARA_SLOT_TIME_EN_C	0	// ʱ϶����Զ���⿪��		
#define 	PARA_SLOT_TIME_DISTRI_C	0	
#define 	PARA_A_1197_LOCK_ST		0	// A��1197����״̬	
#define 	PARA_A_IF_ST	0	// A����ƵƵ��,0/1---300M/500M		
#define 	PARA_ENCRYPTION_ST	0	//����״̬,0/1---������/����
#define 	PARA_PWR_1V6_VT	0	//����״̬,0/1---������/����
#define		PARA_A_90_VALUE			0				//A��9363 90�Ĵ�����ֵ
#define		PARA_A_91_VALUE			0				//A��9363 91�Ĵ�����ֵ
#define		PARA_A_94_VALUE			0				//A��9363 94�Ĵ�����ֵ
#define		PARA_A_95_VALUE			0				//A��9363 95�Ĵ�����ֵ
#define		PARA_B_90_VALUE			0				//B��9363 90�Ĵ�����ֵ
#define		PARA_B_91_VALUE			0				//B��9363 91�Ĵ�����ֵ
#define		PARA_B_94_VALUE			0				//B��9363 94�Ĵ�����ֵ
#define		PARA_B_95_VALUE			0				//B��9363 95�Ĵ�����ֵ
#define		PARA_C_90_VALUE			0				//C��9363 90�Ĵ�����ֵ
#define		PARA_C_91_VALUE			0				//C��9363 91�Ĵ�����ֵ
#define		PARA_C_94_VALUE			0				//C��9363 94�Ĵ�����ֵ
#define		PARA_C_95_VALUE			0				//C��9363 95�Ĵ�����ֵ
#define		PARA_D_90_VALUE			0				//D��9363 90�Ĵ�����ֵ
#define		PARA_D_91_VALUE			0				//D��9363 91�Ĵ�����ֵ
#define		PARA_D_94_VALUE			0				//D��9363 94�Ĵ�����ֵ
#define		PARA_D_95_VALUE			0				//D��9363 95�Ĵ�����ֵ
#define		PARA_PASSTHROUGH_EN			0				//����͸��ʹ��
#define		PARA_A_DL_POW_ADJ			0			
#define		PARA_B_DL_POW_ADJ			0			
#define		PARA_C_DL_POW_ADJ			0			
#define		PARA_D_DL_POW_ADJ			0		
#define		PARA_SoftwareLoadTimes			0		
#define     PARA_A_LNA_EN_ST 		   0	// 	A�����е����LNA����ʹ��







#else

// ������ַ����==================================================== 1b								
#define	PARA_A_CHANNEL_COUNT	0x8889	//	A��֧�ֵ�ͨ����
#define	PARA_A_DL_WORK_EN	0x08b1	//	A�����й���ʹ��
#define	PARA_A_UL_WORK_EN	0x08b2	//	A�����й���ʹ��
#define	PARA_A_DPOW_MODE	0	//	A�����й��ʿ��Ʒ�ʽ
#define	PARA_A_UPOW_MODE	0	//	A�����й��ʿ��Ʒ�ʽ
#define	PARA_A_LTHR_EN	0x0770	//	A�����е�������ʹ��
#define	PARA_A_LTHR_UP	0	//	A�ε�������������
#define	PARA_A_LTHR_DN	0x08b0	//	A�ε�������������
#define	PARA_A_DCH_EN1	0x08d0	//	A������ͨ������ʹ��1
#define	PARA_A_DCH_EN2	0x08d1	//	A������ͨ������ʹ��2
#define	PARA_A_DCH_EN3	0x08d2	//	A������ͨ������ʹ��3
#define	PARA_A_DCH_EN4	0x08d3	//	A������ͨ������ʹ��4
#define	PARA_A_DCH_EN5	0x08d4	//	A������ͨ������ʹ��5
#define	PARA_A_DCH_EN6	0x08d5	//	A������ͨ������ʹ��6
#define	PARA_A_DCH_EN7	0x08d6	//	A������ͨ������ʹ��7
#define	PARA_A_DCH_EN8	0x08d7	//	A������ͨ������ʹ��8
#define	PARA_A_DCH_EN9	0x08d8	//	A������ͨ������ʹ��9
#define	PARA_A_DCH_EN10	0x08d9	//	A������ͨ������ʹ��10
#define	PARA_A_DCH_EN11	0x08dA	//	A������ͨ������ʹ��11
#define	PARA_A_DCH_EN12	0x08dB	//	A������ͨ������ʹ��12
#define	PARA_A_DCH_EN13	0x08dC	//	A������ͨ������ʹ��13
#define	PARA_A_DCH_EN14	0x08dD	//	A������ͨ������ʹ��14
#define	PARA_A_DCH_EN15	0x08dE	//	A������ͨ������ʹ��15
#define	PARA_A_DCH_EN16	0x08dF	//	A������ͨ������ʹ��16
#define	PARA_A_UCH_EN1	0x08d0	//	A������ͨ������ʹ��1
#define	PARA_A_UCH_EN2	0x08d1	//	A������ͨ������ʹ��2
#define	PARA_A_UCH_EN3	0x08d2	//	A������ͨ������ʹ��3
#define	PARA_A_UCH_EN4	0x08d3	//	A������ͨ������ʹ��4
#define	PARA_A_UCH_EN5	0x08d4	//	A������ͨ������ʹ��5
#define	PARA_A_UCH_EN6	0x08d5	//	A������ͨ������ʹ��6
#define	PARA_A_UCH_EN7	0x08d6	//	A������ͨ������ʹ��7
#define	PARA_A_UCH_EN8	0x08d7	//	A������ͨ������ʹ��8
#define	PARA_A_UCH_EN9	0x08d8	//	A������ͨ������ʹ��9
#define	PARA_A_UCH_EN10	0x08d9	//	A������ͨ������ʹ��10
#define	PARA_A_UCH_EN11	0x08dA	//	A������ͨ������ʹ��11
#define	PARA_A_UCH_EN12	0x08dB	//	A������ͨ������ʹ��12
#define	PARA_A_UCH_EN13	0x08dC	//	A������ͨ������ʹ��13
#define	PARA_A_UCH_EN14	0x08dD	//	A������ͨ������ʹ��14
#define	PARA_A_UCH_EN15	0x08dE	//	A������ͨ������ʹ��15
#define	PARA_A_UCH_EN16	0x08dF	//	A������ͨ������ʹ��16
#define	PARA_A_DCH_GAIN1	0x0840	//	A������ѡƵͨ���Ŵ�������1
#define	PARA_A_DCH_GAIN2	0x0841	//	A������ѡƵͨ���Ŵ�������2
#define	PARA_A_DCH_GAIN3	0x0842	//	A������ѡƵͨ���Ŵ�������3
#define	PARA_A_DCH_GAIN4	0x0843	//	A������ѡƵͨ���Ŵ�������4
#define	PARA_A_DCH_GAIN5	0x0844	//	A������ѡƵͨ���Ŵ�������5
#define	PARA_A_DCH_GAIN6	0x0845	//	A������ѡƵͨ���Ŵ�������6
#define	PARA_A_DCH_GAIN7	0x0846	//	A������ѡƵͨ���Ŵ�������7
#define	PARA_A_DCH_GAIN8	0x0847	//	A������ѡƵͨ���Ŵ�������8
#define	PARA_A_DCH_GAIN9	0x0848	//	A������ѡƵͨ���Ŵ�������9
#define	PARA_A_DCH_GAIN10	0x0849	//	A������ѡƵͨ���Ŵ�������10
#define	PARA_A_DCH_GAIN11	0x084A	//	A������ѡƵͨ���Ŵ�������11
#define	PARA_A_DCH_GAIN12	0x084B	//	A������ѡƵͨ���Ŵ�������12
#define	PARA_A_DCH_GAIN13	0x084C	//	A������ѡƵͨ���Ŵ�������13
#define	PARA_A_DCH_GAIN14	0x084D	//	A������ѡƵͨ���Ŵ�������14
#define	PARA_A_DCH_GAIN15	0x084E	//	A������ѡƵͨ���Ŵ�������15
#define	PARA_A_DCH_GAIN16	0x084F	//	A������ѡƵͨ���Ŵ�������16
#define	PARA_A_UCH_GAIN1	0x0850	//	A������ѡƵͨ���Ŵ�������1
#define	PARA_A_UCH_GAIN2	0x0851	//	A������ѡƵͨ���Ŵ�������2
#define	PARA_A_UCH_GAIN3	0x0852	//	A������ѡƵͨ���Ŵ�������3
#define	PARA_A_UCH_GAIN4	0x0853	//	A������ѡƵͨ���Ŵ�������4
#define	PARA_A_UCH_GAIN5	0x0854	//	A������ѡƵͨ���Ŵ�������5
#define	PARA_A_UCH_GAIN6	0x0855	//	A������ѡƵͨ���Ŵ�������6
#define	PARA_A_UCH_GAIN7	0x0856	//	A������ѡƵͨ���Ŵ�������7
#define	PARA_A_UCH_GAIN8	0x0857	//	A������ѡƵͨ���Ŵ�������8
#define	PARA_A_UCH_GAIN9	0x0858	//	A������ѡƵͨ���Ŵ�������9
#define	PARA_A_UCH_GAIN10	0x0859	//	A������ѡƵͨ���Ŵ�������10
#define	PARA_A_UCH_GAIN11	0x085A	//	A������ѡƵͨ���Ŵ�������11
#define	PARA_A_UCH_GAIN12	0x085B	//	A������ѡƵͨ���Ŵ�������12
#define	PARA_A_UCH_GAIN13	0x085C	//	A������ѡƵͨ���Ŵ�������13
#define	PARA_A_UCH_GAIN14	0x085D	//	A������ѡƵͨ���Ŵ�������14
#define	PARA_A_UCH_GAIN15	0x085E	//	A������ѡƵͨ���Ŵ�������15
#define	PARA_A_UCH_GAIN16	0x085F	//	A������ѡƵͨ���Ŵ�������16
#define	PARA_A_DCH_ATT1	0x0324	//	A����������˥����1
#define	PARA_A_DCH_ATT2	0	//	A����������˥����2
#define	PARA_A_DCH_ATT3	0	//	A����������˥����3
#define	PARA_A_DCH_ATT4	0	//	A����������˥����4
#define	PARA_A_DCH_ATT5	0	//	A����������˥����5
#define	PARA_A_DCH_ATT6	0	//	A����������˥����6
#define	PARA_A_DCH_ATT7	0	//	A����������˥����7
#define	PARA_A_DCH_ATT8	0	//	A����������˥����8
#define	PARA_A_DCH_ATT9	0	//	A����������˥����9
#define	PARA_A_DCH_ATT10	0	//	A����������˥����10
#define	PARA_A_DCH_ATT11	0	//	A����������˥����11
#define	PARA_A_DCH_ATT12	0	//	A����������˥����12
#define	PARA_A_DCH_ATT13	0	//	A����������˥����13
#define	PARA_A_DCH_ATT14	0	//	A����������˥����14
#define	PARA_A_DCH_ATT15	0	//	A����������˥����15
#define	PARA_A_DCH_ATT16	0	//	A����������˥����16
#define	PARA_A_UCH_ATT1	0x0320	//	A����������˥����1
#define	PARA_A_UCH_ATT2	0	//	A����������˥����2
#define	PARA_A_UCH_ATT3	0	//	A����������˥����3
#define	PARA_A_UCH_ATT4	0	//	A����������˥����4
#define	PARA_A_UCH_ATT5	0	//	A����������˥����5
#define	PARA_A_UCH_ATT6	0	//	A����������˥����6
#define	PARA_A_UCH_ATT7	0	//	A����������˥����7
#define	PARA_A_UCH_ATT8	0	//	A����������˥����8
#define	PARA_A_UCH_ATT9	0	//	A����������˥����9
#define	PARA_A_UCH_ATT10	0	//	A����������˥����10
#define	PARA_A_UCH_ATT11	0	//	A����������˥����11
#define	PARA_A_UCH_ATT12	0	//	A����������˥����12
#define	PARA_A_UCH_ATT13	0	//	A����������˥����13
#define	PARA_A_UCH_ATT14	0	//	A����������˥����14
#define	PARA_A_UCH_ATT15	0	//	A����������˥����15
#define	PARA_A_UCH_ATT16	0	//	A����������˥����16
#define	PARA_A_DL_PA_GAIN	0	//	A�����й�������
#define	PARA_A_UL_PA_GAIN	0	//	A�����й�������
#define	PARA_A_TX_PLL_ST	0x8308	//	A������PLL״̬,287 2ΪTX_VCO����������ʧ��
#define	PARA_A_RX_PLL_ST	0x8300	//	A������PLL״̬,247 2ΪRX_VCO����������ʧ��
#define	PARA_A_INIT_DA_ST	0	//	��ʼ��A��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define	PARA_A_BB_PLL_LOCK	0	//	A��BB PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define	PARA_A_FSAT		0	//	A��ǰ��AD����״̬
#define	PARA_A_DSAT		0	//	A�κ��DA���״̬
#define	PARA_A_PA_VG_EN	0	//	A�ι���դѹ״̬
#define	PARA_A_PA_VT	0	//	A�ι��Źܵ�ѹ��ʾ
#define	PARA_A_Modulator_EN	0	//	A�ε�����״̬
#define	PARA_A_LNA_VT	0	//	A�����е����LNA��ѹ
#define	PARA_A_LNA1_ST		0x8214	//	����LNA1״̬
#define	PARA_A_LNA2_ST		0x8215	//	����LNA2״̬
#define	PARA_A_BUSY_TIME	0x8892	//	A������ʱ϶ռ����
#define	PARA_A_PRI_ADD 	0xf002	//	A��ģ���ַ(�ں���Э���У�����λΪ���е�ַ������λΪ���е�ַ)
#define	PARA_A_UL_POW_1B	0x831e	//	A�����������ܹ���
#define 	PARA_A_DL_POW_1B	0x8390	//	A�����������ܹ���
#define 	PARA_A_DCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define 	PARA_A_UCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define	PARA_B_CHANNEL_COUNT	0x8889	//	B��֧�ֵ�ͨ����
#define	PARA_B_DL_WORK_EN	0x08b1	//	B�����й���ʹ��
#define	PARA_B_UL_WORK_EN	0x08b2	//	B�����й���ʹ��
#define	PARA_B_DPOW_MODE	0	//	B�����й��ʿ��Ʒ�ʽ
#define	PARA_B_UPOW_MODE	0	//	B�����й��ʿ��Ʒ�ʽ
#define	PARA_B_LTHR_EN		0x0770	//	B�����е�������ʹ��
#define	PARA_B_LTHR_UP		0	//	B�ε�������������
#define	PARA_B_LTHR_DN		0x08b0	//	B�ε�������������
#define	PARA_B_DCH_EN1		0x08d0	//	B������ͨ������ʹ��1
#define	PARA_B_DCH_EN2		0x08d1	//	B������ͨ������ʹ��2
#define	PARA_B_DCH_EN3		0x08d2	//	B������ͨ������ʹ��3
#define	PARA_B_DCH_EN4		0x08d3	//	B������ͨ������ʹ��4
#define	PARA_B_DCH_EN5		0x08d4	//	B������ͨ������ʹ��5
#define	PARA_B_DCH_EN6		0x08d5	//	B������ͨ������ʹ��6
#define	PARA_B_DCH_EN7		0x08d6	//	B������ͨ������ʹ��7
#define	PARA_B_DCH_EN8		0x08d7	//	B������ͨ������ʹ��8
#define	PARA_B_DCH_EN9		0x08d8	//	B������ͨ������ʹ��9
#define	PARA_B_DCH_EN10		0x08d9	//	B������ͨ������ʹ��10
#define	PARA_B_DCH_EN11		0x08dA	//	B������ͨ������ʹ��11
#define	PARA_B_DCH_EN12		0x08dB	//	B������ͨ������ʹ��12
#define	PARA_B_DCH_EN13		0x08dC	//	B������ͨ������ʹ��13
#define	PARA_B_DCH_EN14		0x08dD	//	B������ͨ������ʹ��14
#define	PARA_B_DCH_EN15		0x08dE	//	B������ͨ������ʹ��15
#define	PARA_B_DCH_EN16		0x08dF	//	B������ͨ������ʹ��16
#define	PARA_B_UCH_EN1		0x08d0	//	B������ͨ������ʹ��1
#define	PARA_B_UCH_EN2		0x08d1	//	B������ͨ������ʹ��2
#define	PARA_B_UCH_EN3		0x08d2	//	B������ͨ������ʹ��3
#define	PARA_B_UCH_EN4		0x08d3	//	B������ͨ������ʹ��4
#define	PARA_B_UCH_EN5		0x08d4	//	B������ͨ������ʹ��5
#define	PARA_B_UCH_EN6		0x08d5	//	B������ͨ������ʹ��6
#define	PARA_B_UCH_EN7		0x08d6	//	B������ͨ������ʹ��7
#define	PARA_B_UCH_EN8		0x08d7	//	B������ͨ������ʹ��8
#define	PARA_B_UCH_EN9		0x08d8	//	B������ͨ������ʹ��9
#define	PARA_B_UCH_EN10		0x08d9	//	B������ͨ������ʹ��10
#define	PARA_B_UCH_EN11		0x08dA	//	B������ͨ������ʹ��11
#define	PARA_B_UCH_EN12		0x08dB	//	B������ͨ������ʹ��12
#define	PARA_B_UCH_EN13		0x08dC	//	B������ͨ������ʹ��13
#define	PARA_B_UCH_EN14		0x08dD	//	B������ͨ������ʹ��14
#define	PARA_B_UCH_EN15		0x08dE	//	B������ͨ������ʹ��15
#define	PARA_B_UCH_EN16		0x08dF	//	B������ͨ������ʹ��16
#define	PARA_B_DCH_GAIN1	0x0840	//	B������ѡƵͨ���Ŵ�������1
#define	PARA_B_DCH_GAIN2	0x0841	//	B������ѡƵͨ���Ŵ�������2
#define	PARA_B_DCH_GAIN3	0x0842	//	B������ѡƵͨ���Ŵ�������3
#define	PARA_B_DCH_GAIN4	0x0843	//	B������ѡƵͨ���Ŵ�������4
#define	PARA_B_DCH_GAIN5	0x0844	//	B������ѡƵͨ���Ŵ�������5
#define	PARA_B_DCH_GAIN6	0x0845	//	B������ѡƵͨ���Ŵ�������6
#define	PARA_B_DCH_GAIN7	0x0846	//	B������ѡƵͨ���Ŵ�������7
#define	PARA_B_DCH_GAIN8	0x0847	//	B������ѡƵͨ���Ŵ�������8
#define	PARA_B_DCH_GAIN9	0x0848	//	B������ѡƵͨ���Ŵ�������9
#define	PARA_B_DCH_GAIN10	0x0849	//	B������ѡƵͨ���Ŵ�������10
#define	PARA_B_DCH_GAIN11	0x084A	//	B������ѡƵͨ���Ŵ�������11
#define	PARA_B_DCH_GAIN12	0x084B	//	B������ѡƵͨ���Ŵ�������12
#define	PARA_B_DCH_GAIN13	0x084C	//	B������ѡƵͨ���Ŵ�������13
#define	PARA_B_DCH_GAIN14	0x084D	//	B������ѡƵͨ���Ŵ�������14
#define	PARA_B_DCH_GAIN15	0x084E	//	B������ѡƵͨ���Ŵ�������15
#define	PARA_B_DCH_GAIN16	0x084F	//	B������ѡƵͨ���Ŵ�������16
#define	PARA_B_UCH_GAIN1	0x0850	//	B������ѡƵͨ���Ŵ�������1
#define	PARA_B_UCH_GAIN2	0x0851	//	B������ѡƵͨ���Ŵ�������2
#define	PARA_B_UCH_GAIN3	0x0852	//	B������ѡƵͨ���Ŵ�������3
#define	PARA_B_UCH_GAIN4	0x0853	//	B������ѡƵͨ���Ŵ�������4
#define	PARA_B_UCH_GAIN5	0x0854	//	B������ѡƵͨ���Ŵ�������5
#define	PARA_B_UCH_GAIN6	0x0855	//	B������ѡƵͨ���Ŵ�������6
#define	PARA_B_UCH_GAIN7	0x0856	//	B������ѡƵͨ���Ŵ�������7
#define	PARA_B_UCH_GAIN8	0x0857	//	B������ѡƵͨ���Ŵ�������8
#define	PARA_B_UCH_GAIN9	0x0858	//	B������ѡƵͨ���Ŵ�������9
#define	PARA_B_UCH_GAIN10	0x0859	//	B������ѡƵͨ���Ŵ�������10
#define	PARA_B_UCH_GAIN11	0x085A	//	B������ѡƵͨ���Ŵ�������11
#define	PARA_B_UCH_GAIN12	0x085B	//	B������ѡƵͨ���Ŵ�������12
#define	PARA_B_UCH_GAIN13	0x085C	//	B������ѡƵͨ���Ŵ�������13
#define	PARA_B_UCH_GAIN14	0x085D	//	B������ѡƵͨ���Ŵ�������14
#define	PARA_B_UCH_GAIN15	0x085E	//	B������ѡƵͨ���Ŵ�������15
#define	PARA_B_UCH_GAIN16	0x085F	//	B������ѡƵͨ���Ŵ�������16
#define	PARA_B_DCH_ATT1		0x0324	//	B�������������˥����1
#define	PARA_B_DCH_ATT2		0	//	B�������������˥����2
#define	PARA_B_DCH_ATT3		0	//	B�������������˥����3
#define	PARA_B_DCH_ATT4		0	//	B�������������˥����4
#define	PARA_B_DCH_ATT5		0	//	B�������������˥����5
#define	PARA_B_DCH_ATT6		0	//	B�������������˥����6
#define	PARA_B_DCH_ATT7		0	//	B�������������˥����7
#define	PARA_B_DCH_ATT8		0	//	B�������������˥����8
#define	PARA_B_DCH_ATT9		0	//	B�������������˥����9
#define	PARA_B_DCH_ATT10	0	//	B�������������˥����10
#define	PARA_B_DCH_ATT11	0	//	B�������������˥����11
#define	PARA_B_DCH_ATT12	0	//	B�������������˥����12
#define	PARA_B_DCH_ATT13	0	//	B�������������˥����13
#define	PARA_B_DCH_ATT14	0	//	B�������������˥����14
#define	PARA_B_DCH_ATT15	0	//	B�������������˥����15
#define	PARA_B_DCH_ATT16	0	//	B�������������˥����16
#define	PARA_B_UCH_ATT1		0//0x0320	//	B��������������˥����1
#define	PARA_B_UCH_ATT2		0	//	B��������������˥����2
#define	PARA_B_UCH_ATT3		0	//	B��������������˥����3
#define	PARA_B_UCH_ATT4		0	//	B��������������˥����4
#define	PARA_B_UCH_ATT5		0	//	B��������������˥����5
#define	PARA_B_UCH_ATT6		0	//	B��������������˥����6
#define	PARA_B_UCH_ATT7		0	//	B��������������˥����7
#define	PARA_B_UCH_ATT8		0	//	B��������������˥����8
#define	PARA_B_UCH_ATT9		0	//	B��������������˥����9
#define	PARA_B_UCH_ATT10	0	//	B��������������˥����10
#define	PARA_B_UCH_ATT11	0	//	B��������������˥����11
#define	PARA_B_UCH_ATT12	0	//	B��������������˥����12
#define	PARA_B_UCH_ATT13	0	//	B��������������˥����13
#define	PARA_B_UCH_ATT14	0	//	B��������������˥����14
#define	PARA_B_UCH_ATT15	0	//	B��������������˥����15
#define	PARA_B_UCH_ATT16	0	//	B��������������˥����16
#define	PARA_B_DL_PA_GAIN	0	//	B�����й�������
#define	PARA_B_UL_PA_GAIN	0	//	B�����й�������
#define	PARA_B_TX_PLL_ST	0x8308	//	B������PLL״̬,287 2ΪTX_VCO����������ʧ��
#define	PARA_B_RX_PLL_ST	0x8300	//	B������PLL״̬,247 2ΪRX_VCO����������ʧ��
#define	PARA_B_INIT_DA_ST	0	//	��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define	PARA_B_BB_PLL_LOCK	0	//	B��BB PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define	PARA_B_FSAT		0	//	B��ǰ��AD����״̬
#define	PARA_B_DSAT		0	//	B�κ��DA���״̬
#define	PARA_B_PA_VG_EN	0	//	B�ι���դѹ״̬
#define	PARA_B_PA_VT	0	//	B�ι��Źܵ�ѹ��ʾ
#define	PARA_B_Modulator_EN	0	//	B�ε�����״̬
#define	PARA_B_LNA_VT	0	//	B�����е����LNA��ѹ
#define	PARA_B_LNA1_ST		0x8214	//	����LNA1״̬
#define	PARA_B_LNA2_ST		0x8215	//	����LNA2״̬
#define	PARA_B_BUSY_TIME	0x8892	//	B������ʱ϶ռ����
#define	PARA_B_PRI_ADD 		0xf002	//	B��ģ���ַ(�ں���Э���У�����λΪ���е�ַ������λΪ���е�ַ)
#define	PARA_B_UL_POW_1B	0x831e	//	B�����������ܹ���
#define 	PARA_B_DL_POW_1B	0x8390	//	B�����������ܹ���
#define 	PARA_B_DCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define 	PARA_B_UCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥����  ��rf
#define	PARA_C_CHANNEL_COUNT	0x8889	//	C��֧�ֵ�ͨ����
#define	PARA_C_DL_WORK_EN	0x08b1	//	C�����й���ʹ��
#define	PARA_C_UL_WORK_EN	0x08b2	//	C�����й���ʹ��
#define	PARA_C_DPOW_MODE	0	//	C�����й��ʿ��Ʒ�ʽ
#define	PARA_C_UPOW_MODE	0	//	C�����й��ʿ��Ʒ�ʽ
#define	PARA_C_LTHR_EN		0x0770	//	C�����е�������ʹ��
#define	PARA_C_LTHR_UP		0	//	C�ε�������������
#define	PARA_C_LTHR_DN		0x08b0	//	C�ε�������������
#define	PARA_C_DCH_EN1		0x08d0	//	C������ͨ������ʹ��1
#define	PARA_C_DCH_EN2		0x08d1	//	C������ͨ������ʹ��2
#define	PARA_C_DCH_EN3		0x08d2	//	C������ͨ������ʹ��3
#define	PARA_C_DCH_EN4		0x08d3	//	C������ͨ������ʹ��4
#define	PARA_C_DCH_EN5		0x08d4	//	C������ͨ������ʹ��5
#define	PARA_C_DCH_EN6		0x08d5	//	C������ͨ������ʹ��6
#define	PARA_C_DCH_EN7		0x08d6	//	C������ͨ������ʹ��7
#define	PARA_C_DCH_EN8		0x08d7	//	C������ͨ������ʹ��8
#define	PARA_C_DCH_EN9		0x08d8	//	C������ͨ������ʹ��9
#define	PARA_C_DCH_EN10		0x08d9	//	C������ͨ������ʹ��10
#define	PARA_C_UCH_EN1		0x08d0	//	C������ͨ������ʹ��1
#define	PARA_C_UCH_EN2		0x08d1	//	C������ͨ������ʹ��2
#define	PARA_C_UCH_EN3		0x08d2	//	C������ͨ������ʹ��3
#define	PARA_C_UCH_EN4		0x08d3	//	C������ͨ������ʹ��4
#define	PARA_C_UCH_EN5		0x08d4	//	C������ͨ������ʹ��5
#define	PARA_C_UCH_EN6		0x08d5	//	C������ͨ������ʹ��6
#define	PARA_C_UCH_EN7		0x08d6	//	C������ͨ������ʹ��7
#define	PARA_C_UCH_EN8		0x08d7	//	C������ͨ������ʹ��8
#define	PARA_C_UCH_EN9		0x08d8	//	C������ͨ������ʹ��9
#define	PARA_C_UCH_EN10		0x08d9	//	C������ͨ������ʹ��10
#define	PARA_C_DCH_GAIN1	0x0840	//	C������ѡƵͨ���Ŵ�������1
#define	PARA_C_DCH_GAIN2	0x0841	//	C������ѡƵͨ���Ŵ�������2
#define	PARA_C_DCH_GAIN3	0x0842	//	C������ѡƵͨ���Ŵ�������3
#define	PARA_C_DCH_GAIN4	0x0843	//	C������ѡƵͨ���Ŵ�������4
#define	PARA_C_DCH_GAIN5	0x0844	//	C������ѡƵͨ���Ŵ�������5
#define	PARA_C_DCH_GAIN6	0x0845	//	C������ѡƵͨ���Ŵ�������6
#define	PARA_C_DCH_GAIN7	0x0846	//	C������ѡƵͨ���Ŵ�������7
#define	PARA_C_DCH_GAIN8	0x0847	//	C������ѡƵͨ���Ŵ�������8
#define	PARA_C_DCH_GAIN9	0x0848	//	C������ѡƵͨ���Ŵ�������9
#define	PARA_C_DCH_GAIN10	0x0849	//	C������ѡƵͨ���Ŵ�������10
#define 	PARA_C_DCH_GAIN11 	0	// 	C������ѡƵͨ���Ŵ�������11
#define 	PARA_C_DCH_GAIN12 	0	// 	C������ѡƵͨ���Ŵ�������12
#define 	PARA_C_DCH_GAIN13 	0	// 	C������ѡƵͨ���Ŵ�������13
#define 	PARA_C_DCH_GAIN14 	0	// 	C������ѡƵͨ���Ŵ�������14
#define 	PARA_C_DCH_GAIN15 	0	// 	C������ѡƵͨ���Ŵ�������15
#define 	PARA_C_DCH_GAIN16 	0	// 	C������ѡƵͨ���Ŵ�������16
#define	PARA_C_UCH_GAIN1	0x0850	//	C������ѡƵͨ���Ŵ�������1
#define	PARA_C_UCH_GAIN2	0x0851	//	C������ѡƵͨ���Ŵ�������2
#define	PARA_C_UCH_GAIN3	0x0852	//	C������ѡƵͨ���Ŵ�������3
#define	PARA_C_UCH_GAIN4	0x0853	//	C������ѡƵͨ���Ŵ�������4
#define	PARA_C_UCH_GAIN5	0x0854	//	C������ѡƵͨ���Ŵ�������5
#define	PARA_C_UCH_GAIN6	0x0855	//	C������ѡƵͨ���Ŵ�������6
#define	PARA_C_UCH_GAIN7	0x0856	//	C������ѡƵͨ���Ŵ�������7
#define	PARA_C_UCH_GAIN8	0x0857	//	C������ѡƵͨ���Ŵ�������8
#define	PARA_C_UCH_GAIN9	0x0858	//	C������ѡƵͨ���Ŵ�������9
#define	PARA_C_UCH_GAIN10	0x0859	//	C������ѡƵͨ���Ŵ�������10
#define	PARA_C_UCH_GAIN11	0	//	C������ѡƵͨ���Ŵ�������11
#define	PARA_C_UCH_GAIN12	0	//	C������ѡƵͨ���Ŵ�������12
#define	PARA_C_UCH_GAIN13	0	//	C������ѡƵͨ���Ŵ�������13
#define	PARA_C_UCH_GAIN14	0	//	C������ѡƵͨ���Ŵ�������14
#define	PARA_C_UCH_GAIN15	0	//	C������ѡƵͨ���Ŵ�������15
#define	PARA_C_UCH_GAIN16	0	//	C������ѡƵͨ���Ŵ�������16
#define	PARA_C_DCH_ATT1		0x0324	//	C�������������˥����1
#define	PARA_C_DCH_ATT2		0	//	C�������������˥����2
#define	PARA_C_DCH_ATT3		0	//	C�������������˥����3
#define	PARA_C_DCH_ATT4		0	//	C�������������˥����4
#define	PARA_C_DCH_ATT5		0	//	C�������������˥����5
#define	PARA_C_DCH_ATT6		0	//	C�������������˥����6
#define	PARA_C_DCH_ATT7		0	//	C�������������˥����7
#define	PARA_C_DCH_ATT8		0	//	C�������������˥����8
#define	PARA_C_DCH_ATT9		0	//	C�������������˥����9
#define	PARA_C_DCH_ATT10	0	//	C�������������˥����10
#define	PARA_C_DCH_ATT11	0	//	C�������������˥����11
#define	PARA_C_DCH_ATT12	0	//	C�������������˥����12
#define	PARA_C_DCH_ATT13	0	//	C�������������˥����13
#define	PARA_C_DCH_ATT14	0	//	C�������������˥����14
#define	PARA_C_DCH_ATT15	0	//	C�������������˥����15
#define	PARA_C_DCH_ATT16	0	//	C�������������˥����16
#define	PARA_C_UCH_ATT1		0//0x0320	//	C��������������˥����1
#define	PARA_C_UCH_ATT2		0	//	C��������������˥����2
#define	PARA_C_UCH_ATT3		0	//	C��������������˥����3
#define	PARA_C_UCH_ATT4		0	//	C��������������˥����4
#define	PARA_C_UCH_ATT5		0	//	C��������������˥����5
#define	PARA_C_UCH_ATT6		0	//	C��������������˥����6
#define	PARA_C_UCH_ATT7		0	//	C��������������˥����7
#define	PARA_C_UCH_ATT8		0	//	C��������������˥����8
#define	PARA_C_UCH_ATT9		0	//	C��������������˥����9
#define	PARA_C_UCH_ATT10	0	//	C��������������˥����10
#define	PARA_C_UCH_ATT11	0	//	C��������������˥����11
#define	PARA_C_UCH_ATT12	0	//	C��������������˥����12
#define	PARA_C_UCH_ATT13	0	//	C��������������˥����13
#define	PARA_C_UCH_ATT14	0	//	C��������������˥����14
#define	PARA_C_UCH_ATT15	0	//	C��������������˥����15
#define	PARA_C_UCH_ATT16	0	//	C��������������˥����16
#define	PARA_C_DL_PA_GAIN	0	//	C�����й�������
#define	PARA_C_UL_PA_GAIN	0	//	C�����й�������
#define	PARA_C_TX_PLL_ST	0x8308	//	C������PLL״̬,287 2ΪTX_VCO����������ʧ��
#define	PARA_C_RX_PLL_ST	0x8300	//	C������PLL״̬,247 2ΪRX_VCO����������ʧ��
#define	PARA_C_INIT_DA_ST	0	//	C��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define	PARA_C_BB_PLL_LOCK	0	//	C��BB PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define	PARA_C_FSAT		0	//	C��ǰ��AD����״̬
#define	PARA_C_DSAT		0	//	C�κ��DA���״̬
#define	PARA_C_PA_VG_EN	0	//	C�ι���դѹ״̬
#define	PARA_C_PA_VT	0	//	C�ι��Źܵ�ѹ��ʾ
#define	PARA_C_Modulator_EN	0	//	C�ε�����״̬
#define	PARA_C_LNA_VT	0	//	C�����е����LNA��ѹ
#define	PARA_C_LNA1_ST		0x8214	//	C����LNA1״̬
#define	PARA_C_LNA2_ST		0x8215	//	C����LNA2״̬
#define	PARA_C_BUSY_TIME	0x8892	//	C������ʱ϶ռ����
#define	PARA_C_PRI_ADD 		0xf002	//	C��ģ���ַ(�ں���Э���У�����λΪ���е�ַ������λΪ���е�ַ)
#define	PARA_C_UL_POW_1B	0x831e	//	C�����������ܹ���
#define 	PARA_C_DL_POW_1B	0x8390	//	C�����������ܹ���
#define 	PARA_C_DCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define 	PARA_C_UCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥����  ��rf
#define	PARA_D_CHANNEL_COUNT	0x8889	//	D��֧�ֵ�ͨ����
#define	PARA_D_DL_WORK_EN	0x08b1	//	D�����й���ʹ��
#define	PARA_D_UL_WORK_EN	0x08b2	//	D�����й���ʹ��
#define	PARA_D_DPOW_MODE	0	//	D�����й��ʿ��Ʒ�ʽ
#define	PARA_D_UPOW_MODE	0	//	D�����й��ʿ��Ʒ�ʽ
#define	PARA_D_LTHR_EN		0x0770	//	D�����е�������ʹ��
#define	PARA_D_LTHR_UP		0	//	D�ε�������������
#define	PARA_D_LTHR_DN		0x08b0	//	D�ε�������������
#define	PARA_D_DCH_EN1		0x08d0	//	D������ͨ������ʹ��1
#define	PARA_D_DCH_EN2		0x08d1	//	D������ͨ������ʹ��2
#define	PARA_D_DCH_EN3		0x08d2	//	D������ͨ������ʹ��3
#define	PARA_D_DCH_EN4		0x08d3	//	D������ͨ������ʹ��4
#define	PARA_D_DCH_EN5		0x08d4	//	D������ͨ������ʹ��5
#define	PARA_D_DCH_EN6		0x08d5	//	D������ͨ������ʹ��6
#define	PARA_D_DCH_EN7		0x08d6	//	D������ͨ������ʹ��7
#define	PARA_D_DCH_EN8		0x08d7	//	D������ͨ������ʹ��8
#define	PARA_D_DCH_EN9		0x08d8	//	D������ͨ������ʹ��9
#define	PARA_D_DCH_EN10	0x08d9	//	D������ͨ������ʹ��10
#define	PARA_D_UCH_EN1		0x08d0	//	D������ͨ������ʹ��1
#define	PARA_D_UCH_EN2		0x08d1	//	D������ͨ������ʹ��2
#define	PARA_D_UCH_EN3		0x08d2	//	D������ͨ������ʹ��3
#define	PARA_D_UCH_EN4		0x08d3	//	D������ͨ������ʹ��4
#define	PARA_D_UCH_EN5		0x08d4	//	D������ͨ������ʹ��5
#define	PARA_D_UCH_EN6		0x08d5	//	D������ͨ������ʹ��6
#define	PARA_D_UCH_EN7		0x08d6	//	D������ͨ������ʹ��7
#define	PARA_D_UCH_EN8		0x08d7	//	D������ͨ������ʹ��8
#define	PARA_D_UCH_EN9		0x08d8	//	D������ͨ������ʹ��9
#define	PARA_D_UCH_EN10	0x08d9	//	D������ͨ������ʹ��10
#define	PARA_D_DCH_GAIN1	0x0840	//	D������ѡƵͨ���Ŵ�������1
#define	PARA_D_DCH_GAIN2	0x0841	//	D������ѡƵͨ���Ŵ�������2
#define	PARA_D_DCH_GAIN3	0x0842	//	D������ѡƵͨ���Ŵ�������3
#define	PARA_D_DCH_GAIN4	0x0843	//	D������ѡƵͨ���Ŵ�������4
#define	PARA_D_DCH_GAIN5	0x0844	//	D������ѡƵͨ���Ŵ�������5
#define	PARA_D_DCH_GAIN6	0x0845	//	D������ѡƵͨ���Ŵ�������6
#define	PARA_D_DCH_GAIN7	0x0846	//	D������ѡƵͨ���Ŵ�������7
#define	PARA_D_DCH_GAIN8	0x0847	//	D������ѡƵͨ���Ŵ�������8
#define	PARA_D_DCH_GAIN9	0x0848	//	D������ѡƵͨ���Ŵ�������9
#define	PARA_D_DCH_GAIN10	0x0849	//	D������ѡƵͨ���Ŵ�������10
#define	PARA_D_DCH_GAIN11	0	//	D������ѡƵͨ���Ŵ�������11
#define	PARA_D_DCH_GAIN12	0	//	D������ѡƵͨ���Ŵ�������12
#define	PARA_D_DCH_GAIN13	0	//	D������ѡƵͨ���Ŵ�������13
#define	PARA_D_DCH_GAIN14	0	//	D������ѡƵͨ���Ŵ�������14
#define	PARA_D_DCH_GAIN15	0	//	D������ѡƵͨ���Ŵ�������15
#define	PARA_D_DCH_GAIN16	0	//	D������ѡƵͨ���Ŵ�������16
#define	PARA_D_UCH_GAIN1	0x0850	//	D������ѡƵͨ���Ŵ�������1
#define	PARA_D_UCH_GAIN2	0x0851	//	D������ѡƵͨ���Ŵ�������2
#define	PARA_D_UCH_GAIN3	0x0852	//	D������ѡƵͨ���Ŵ�������3
#define	PARA_D_UCH_GAIN4	0x0853	//	D������ѡƵͨ���Ŵ�������4
#define	PARA_D_UCH_GAIN5	0x0854	//	D������ѡƵͨ���Ŵ�������5
#define	PARA_D_UCH_GAIN6	0x0855	//	D������ѡƵͨ���Ŵ�������6
#define	PARA_D_UCH_GAIN7	0x0856	//	D������ѡƵͨ���Ŵ�������7
#define	PARA_D_UCH_GAIN8	0x0857	//	D������ѡƵͨ���Ŵ�������8
#define	PARA_D_UCH_GAIN9	0x0858	//	D������ѡƵͨ���Ŵ�������9
#define	PARA_D_UCH_GAIN10	0x0859	//	D������ѡƵͨ���Ŵ�������10
#define	PARA_D_UCH_GAIN11	0	//	D������ѡƵͨ���Ŵ�������11
#define	PARA_D_UCH_GAIN12	0	//	D������ѡƵͨ���Ŵ�������12
#define	PARA_D_UCH_GAIN13	0	//	D������ѡƵͨ���Ŵ�������13
#define	PARA_D_UCH_GAIN14	0	//	D������ѡƵͨ���Ŵ�������14
#define	PARA_D_UCH_GAIN15	0	//	D������ѡƵͨ���Ŵ�������15
#define	PARA_D_UCH_GAIN16	0	//	D������ѡƵͨ���Ŵ�������16
#define	PARA_D_DCH_ATT1		0x0324	//	D�������������˥����1
#define	PARA_D_DCH_ATT2		0	//	D�������������˥����2
#define	PARA_D_DCH_ATT3		0	//	D�������������˥����3
#define	PARA_D_DCH_ATT4		0	//	D�������������˥����4
#define	PARA_D_DCH_ATT5		0	//	D�������������˥����5
#define	PARA_D_DCH_ATT6		0	//	D�������������˥����6
#define	PARA_D_DCH_ATT7		0	//	D�������������˥����7
#define	PARA_D_DCH_ATT8		0	//	D�������������˥����8
#define	PARA_D_DCH_ATT9		0	//	D�������������˥����9
#define	PARA_D_DCH_ATT10	0	//	D�������������˥����10
#define	PARA_D_DCH_ATT11	0	//	D�������������˥����11
#define	PARA_D_DCH_ATT12	0	//	D�������������˥����12
#define	PARA_D_DCH_ATT13	0	//	D�������������˥����13
#define	PARA_D_DCH_ATT14	0	//	D�������������˥����14
#define	PARA_D_DCH_ATT15	0	//	D�������������˥����15
#define	PARA_D_DCH_ATT16	0	//	D�������������˥����16
#define	PARA_D_UCH_ATT1		0//0x0320	//	D��������������˥����1
#define	PARA_D_UCH_ATT2		0	//	D��������������˥����2
#define	PARA_D_UCH_ATT3		0	//	D��������������˥����3
#define	PARA_D_UCH_ATT4		0	//	D��������������˥����4
#define	PARA_D_UCH_ATT5		0	//	D��������������˥����5
#define	PARA_D_UCH_ATT6		0	//	D��������������˥����6
#define	PARA_D_UCH_ATT7		0	//	D��������������˥����7
#define	PARA_D_UCH_ATT8		0	//	D��������������˥����8
#define	PARA_D_UCH_ATT9		0	//	D��������������˥����9
#define	PARA_D_UCH_ATT10	0	//	D��������������˥����10
#define	PARA_D_UCH_ATT11	0	//	D��������������˥����11
#define	PARA_D_UCH_ATT12	0	//	D��������������˥����12
#define	PARA_D_UCH_ATT13	0	//	D��������������˥����13
#define	PARA_D_UCH_ATT14	0	//	D��������������˥����14
#define	PARA_D_UCH_ATT15	0	//	D��������������˥����15
#define	PARA_D_UCH_ATT16	0	//	D��������������˥����16
#define	PARA_D_DL_PA_GAIN	0	//	D�����й�������
#define	PARA_D_UL_PA_GAIN	0	//	D�����й�������
#define	PARA_D_TX_PLL_ST	0x8308	//	D������PLL״̬,287 2ΪTX_VCO����������ʧ��
#define	PARA_D_RX_PLL_ST	0x8300	//	D������PLL״̬,247 2ΪRX_VCO����������ʧ��
#define	PARA_D_INIT_DA_ST	0	//	D��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define	PARA_D_BB_PLL_LOCK	0	//	D��BB PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define	PARA_D_FSAT		0	//	D��ǰ��AD����״̬
#define	PARA_D_DSAT		0	//	D�κ��DA���״̬
#define	PARA_D_PA_VG_EN	0	//	D�ι���դѹ״̬
#define	PARA_D_PA_VT	0	//	D�ι��Źܵ�ѹ��ʾ
#define	PARA_D_Modulator_EN	0	//	D�ε�����״̬
#define	PARA_D_LNA_VT	0	//	D�����е����LNA��ѹ
#define	PARA_D_LNA1_ST		0x8214	//	D����LNA1״̬
#define	PARA_D_LNA2_ST		0x8215	//	D����LNA2״̬
#define	PARA_D_BUSY_TIME	0x8892	//	D������ʱ϶ռ����
#define	PARA_D_PRI_ADD 		0xf002	//	D��ģ���ַ(�ں���Э���У�����λΪ���е�ַ������λΪ���е�ַ)
#define	PARA_D_UL_POW_1B	0x831e	//	D�����������ܹ���
#define 	PARA_D_DL_POW_1B	0x8390	//	D�����������ܹ���
#define 	PARA_D_DCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥���� ��rf
#define 	PARA_D_UCH_REC_RF_ATT1          0     //// REC�˵���������˥��������RF�˵���·����˥����  ��rf
#define	PARA_FP1_EN	0x0927	//	��ڷ���ʹ��1
#define	PARA_FP2_EN	0x0928	//	��ڷ���ʹ��2
#define	PARA_FP3_EN	0x0929	//	��ڷ���ʹ��3
#define	PARA_FP4_EN	0x092A	//	��ڷ���ʹ��4
#define	PARA_FP5_EN	0x092B	//	��ڷ���ʹ��5
#define	PARA_FP6_EN	0x092C	//	��ڷ���ʹ��6
#define	PARA_FP7_EN	0x092D	//	��ڷ���ʹ��7
#define	PARA_FP8_EN	0x092E	//	��ڷ���ʹ��8
#define	PARA_FP9_EN	0x0	//	��ڷ���ʹ��9
#define	PARA_FP10_EN	0x0	//	��ڷ���ʹ��10
#define	PARA_FP11_EN	0x0	//	��ڷ���ʹ��11
#define	PARA_FP12_EN	0x0	//	��ڷ���ʹ��12
#define	PARA_FP13_EN	0x0	//	��ڷ���ʹ��13
#define	PARA_FP14_EN	0x0	//	��ڷ���ʹ��14
#define	PARA_FP15_EN	0x0	//	��ڷ���ʹ��15
#define	PARA_FP16_EN	0x0	//	��ڷ���ʹ��16
#define	PARA_FP1_ON_POS	0x8560	//	�����λ״̬1, 0-��λ	
#define	PARA_FP2_ON_POS	0x8561	//	�����λ״̬2, 0-��λ	
#define	PARA_FP3_ON_POS	0x8562	//	�����λ״̬3, 0-��λ	
#define	PARA_FP4_ON_POS	0x8563	//	�����λ״̬4, 0-��λ	
#define	PARA_FP5_ON_POS	0x8564	//	�����λ״̬5, 0-��λ	
#define	PARA_FP6_ON_POS	0x8565	//	�����λ״̬6, 0-��λ	
#define	PARA_FP7_ON_POS	0x8566	//	�����λ״̬7, 0-��λ	
#define	PARA_FP8_ON_POS	0x8567	//	�����λ״̬8, 0-��λ	
#define	PARA_FP9_ON_POS	0x8568	//	�����λ״̬9, 0-��λ	
#define	PARA_FP10_ON_POS	0x8569	//	�����λ״̬10, 0-��λ	
#define	PARA_FP11_ON_POS	0x856a	//	�����λ״̬11, 0-��λ	
#define	PARA_FP12_ON_POS	0x856b	//	�����λ״̬12, 0-��λ	
#define	PARA_FP13_ON_POS	0x856c	//	�����λ״̬13, 0-��λ	
#define	PARA_FP14_ON_POS	0x856d	//	�����λ״̬14, 0-��λ
#define	PARA_FP15_ON_POS	0x856e	//	�����λ״̬15, 0-��λ
#define	PARA_FP16_ON_POS	0x856f	//	�����λ״̬16, 0-��λ
#define	PARA_FP1_LOS	0x8730	//	���1�źŶ�ʧ״̬	
#define	PARA_FP2_LOS	0x8731	//	���2�źŶ�ʧ״̬	
#define	PARA_FP3_LOS	0x8732	//	���3�źŶ�ʧ״̬	
#define	PARA_FP4_LOS	0x8733	//	���4�źŶ�ʧ״̬	
#define	PARA_FP5_LOS	0x8734	//	���5�źŶ�ʧ״̬	
#define	PARA_FP6_LOS	0x8735	//	���6�źŶ�ʧ״̬	
#define	PARA_FP7_LOS	0x8736	//	���7�źŶ�ʧ״̬	
#define	PARA_FP8_LOS	0x8737	//	���8�źŶ�ʧ״̬	
#define	PARA_FP9_LOS	0x8738	//	���9�źŶ�ʧ״̬
#define	PARA_FP10_LOS	0x8739	//	���10�źŶ�ʧ״̬	
#define	PARA_FP11_LOS	0x873a	//	���11�źŶ�ʧ״̬	
#define	PARA_FP12_LOS	0x873b	//	���12�źŶ�ʧ״̬	
#define	PARA_FP13_LOS	0x873c	//	���13�źŶ�ʧ״̬
#define	PARA_FP14_LOS	0x873d	//	���14�źŶ�ʧ״̬
#define	PARA_FP15_LOS	0x873e	//	���15�źŶ�ʧ״̬
#define	PARA_FP16_LOS	0x873f	//	���16�źŶ�ʧ״̬
#define	PARA_FP1_LOF	0x8780	//	���1֡��ʧ״̬	
#define	PARA_FP2_LOF	0x8781	//	���2֡��ʧ״̬	
#define	PARA_FP3_LOF	0x8782	//	���3֡��ʧ״̬	
#define	PARA_FP4_LOF	0x8783	//	���4֡��ʧ״̬	
#define	PARA_FP5_LOF	0x8784	//	���5֡��ʧ״̬	
#define	PARA_FP6_LOF	0x8785	//	���6֡��ʧ״̬	
#define	PARA_FP7_LOF	0x8786	//	���7֡��ʧ״̬	
#define	PARA_FP8_LOF	0x8787	//	���8֡��ʧ״̬	
#define	PARA_FP9_LOF	0x8788	//	���9֡��ʧ״̬	
#define	PARA_FP10_LOF	0x8789	//	���10֡��ʧ״̬	
#define	PARA_FP11_LOF	0x878a	//	���11֡��ʧ״̬	
#define	PARA_FP12_LOF	0x878b	//	���12֡��ʧ״̬	
#define	PARA_FP13_LOF	0x878c	//	���13֡��ʧ״̬
#define	PARA_FP14_LOF	0x878d	//	���14֡��ʧ״̬
#define	PARA_FP15_LOF	0x878e	//	���15֡��ʧ״̬
#define	PARA_FP16_LOF	0x878f	//	���16֡��ʧ״̬
#define	PARA_OPT_LOF	0x87ad	//	֡��ʧ״̬
#define	PARA_SERDES1_PLL_ST	0x8790	//	SerDesоƬPLL״̬1	
#define	PARA_SERDES2_PLL_ST	0x8791	//	SerDesоƬPLL״̬2	
#define	PARA_SERDES3_PLL_ST	0x8792	//	SerDesоƬPLL״̬3	
#define	PARA_SERDES4_PLL_ST	0x8793	//	SerDesоƬPLL״̬4	
#define	PARA_SERDES5_PLL_ST	0x8794	//	SerDesоƬPLL״̬5	
#define	PARA_SERDES6_PLL_ST	0x8795	//	SerDesоƬPLL״̬6	
#define	PARA_SERDES7_PLL_ST	0x8796	//	SerDesоƬPLL״̬7	
#define	PARA_SERDES8_PLL_ST	0x8797	//	SerDesоƬPLL״̬8	
#define	PARA_SERDES9_PLL_ST	0x8798	//	SerDesоƬPLL״̬9	
#define	PARA_SERDES10_PLL_ST	0x8799	//	SerDesоƬPLL״̬10	
#define	PARA_SERDES11_PLL_ST	0x879a	//	SerDesоƬPLL״̬11	
#define	PARA_SERDES12_PLL_ST	0x879b	//	SerDesоƬPLL״̬12	
#define	PARA_SERDES13_PLL_ST	0x879c	//	SerDesоƬPLL״̬13
#define	PARA_SERDES14_PLL_ST	0x879d	//	SerDesоƬPLL״̬14
#define	PARA_SERDES15_PLL_ST	0x879e	//	SerDesоƬPLL״̬15
#define	PARA_SERDES16_PLL_ST	0x879f	//	SerDesоƬPLL״̬16
#define	PARA_TOPO_CHG_ALM	0x87af	//	��·״̬�澯
#define	PARA_BER_ALARM	0x87ae	//	������ƫ�߸澯
#define	PARA_LOAD_FPGA_ST	0x8854	//	����FPGA״̬
#define	PARA_FPGA_CLK_ST	0x8851	//	FPGA����״̬
#define	PARA_INIT_CLK_ST	0	//	��ʼ��ʱ��״̬
#define	PARA_INIT_AD_ST	0	//	��ʼ��AD״̬
#define	PARA_INIT_FB_AD_ST	0	//	��ʼ������AD״̬
#define	PARA_CLK_PLL_ST	0x884e	//	CLK PLL״̬
#define	PARA_CLK_REF_ST	0x884f	//	CLK �ο�״̬
#define	PARA_RE_NODE_MODE	0x889d	//	RE�ڵ�ģʽ
#define	PARA_BOARD_TEMP	0x8844	//	�����¶�
#define	PARA_CLK_VCO_VT	0	//	ʱ��VCO��ѹ
#define	PARA_PWR_9V0_VT	0	//	9V��Դ��ѹ
#define	PARA_PWR_5V5_VT	0	//	5.5V��Դ��ѹ
#define	PARA_PWR_3V6_VT	0	//	3.6V��Դ��ѹ
#define	PARA_PWR_1V2_VT	0	//	1.2V��Դ��ѹ
#define	PARA_PWR_2V5_VT	0	//	1.2V��Դ��ѹ
#define	PARA_PRI_PROTOCAL_V	0xf003	//	Э��汾
#define	PARA_MODULE_HRI_ID	0	//	ID
#define 	PARA_WORK_ERROR	0	// ϵͳ����״̬��1-�й���
#define 	PARA_TRAFFIC_END	0x88ac	// ������ͳ�ƽ�����־
#define 	PARA_DELAY_MODE	0x098e	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define	PARA_TD_SYNC_ST			0x7620		// TDͬ��״̬: 1-��ͬ����0-δͬ��
#define	PARA_TD_WORK_MODE 		0x08ac	// [WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���, ÿ���ϵ������			
#define 	PARA_TD_T0_UD		0x08a0	// TDʱ϶0�����б�־:0-���У�1-����			
#define 	PARA_TD_T1_UD		0x08a1	// TDʱ϶1�����б�־:0-���У�1-����			
#define 	PARA_TD_T2_UD		0x08a2	// TDʱ϶2�����б�־:0-���У�1-����			
#define 	PARA_TD_T3_UD		0x08a3	// TDʱ϶3�����б�־:0-���У�1-����			
#define 	PARA_TD_T4_UD		0x08a4	// TDʱ϶4�����б�־:0-���У�1-����			
#define 	PARA_TD_T5_UD		0x08a5	// TDʱ϶5�����б�־:0-���У�1-����			
#define 	PARA_TD_T6_UD		0x08a6	// TDʱ϶6�����б�־:0-���У�1-����			
#define	PARA_POWERUP_ST		0x8852	// 	���ְ��ϵ�״̬,ÿ������ʱ��1
#define	PARA_LOW_POWER			0x88ff//0x08ad	//	�͹���ģʽ:1-�͹���;	0-����		���� x0778   �������ʼ�����˺�ֻ��Ϊ�ο�
#define 	PARA_THR_PORT		0		// 	͸���˿�ѡ��0-485B, 1-RS232
#define	PARA_THR_BAUD		0		//	͸���˿ڲ����� 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define	PARA_CTRL_BAUD	0		//	���ƶ˿ڲ����� 0-9600, 1-19200, 2-38400, 4-57600, 5-115200
#define	PARA_WLAN_CONN_ST1		0x87b2	// WLAN��״̬1: 0-������1-�쳣
#define	PARA_WLAN_CONN_ST2		0x87b3	// WLAN��״̬2: 0-������1-�쳣
#define	PARA_WLAN_CONN_ST3		0x87b4	// WLAN��״̬3: 0-������1-�쳣
#define	PARA_WLAN_CONN_ST4		0x87b7	// WLAN��״̬4: 0-������1-�쳣
#define	PARA_WLAN_SPEED1			0x87b8	// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
#define	PARA_WLAN_SPEED2			0x87b9		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
#define	PARA_WLAN_SPEED3			0x87ba		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
#define	PARA_WLAN_SPEED4			0x87bb		// WLAN���ٶ�1: 0��10M  1��100M  2��1000M
#define	PARA_GSM_BW_SEL			0		// ����汾GSM����ѡ��: 0-6M, 1-20M, 2-24M, 3-25M, ������Ч
#define	PARA_HX_DET_UADDR 0 // ����DETģ�����е�ַ, ��4λΪB��, ����λΪA��
#define	PARA_HX_LNA_UADDR 0 // ����LNAģ�����е�ַ, ��4λΪB��, ����λΪA��
#define	PARA_HX_DET_DADDR 0 // ����DETģ�����е�ַ, ��4λΪB��, ����λΪA��
#define	PARA_HX_LNA_DADDR 0 // ����LNAģ�����е�ַ, ��4λΪB��, ����λΪA��
#define 	PARA_FPS_AUTO_SCAN		0x0932		// �Զ�Ƶ����������ʹ��:1-�Զ�����������Ƶ��, 0-�ֶ�����
#define 	PARA_FPS_SWITCH_THD 		0 		// �Զ�Ƶ��������BCCH�����л�����
#define 	PARA_FPS_MOSVC_SEL		0x0925	// Ƶ������: ��Ӫ��ѡ��: 0-���ƶ�, 1-����ͨ, 2-���ƶ�, 255-�Զ�ѡ��
#define	PARA_FPS_RFRANGE_SEL	0x0924	// Ƶ������: Ƶ��ѡ��(����,��ģ����ʽΪ׼): 0-ȫƵ��, 1-900MHz, 2-1800MHz
#define 	PARA_FPS_BS_ID			0x8959	// Ƶ������: ��վʶ����
#define	PARA_FPS_CA_COUNT		0x895b	// Ƶ������: ��Ч�ŵ���
#define	PARA_FPS_BCCH_LK_ST		0x895c	// Ƶ������: ����BCCH״̬: 1-����, 0-ʧ��
#define	PARA_FPS_MOSVC_LK_ST		0x895d	// Ƶ������: ������Ӫ��״̬: 1-����, 0-ʧ��
#define	PARA_FPS_RFRANGE_LK_ST	0x895e	// Ƶ������: ����Ƶ��״̬: 1-����, 0-ʧ��
#define	PARA_FPS_BCCH_POW_M		0x8960	// Ƶ������: ��С��BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_1		0x8961	// Ƶ������: ��С��1BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_2		0x8962	// Ƶ������: ��С��2BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_3		0x8963	// Ƶ������: ��С��3BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_4		0x8964	// Ƶ������: ��С��4BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_5		0x8965	// Ƶ������: ��С��5BCCH����ǿ��
#define	PARA_FPS_BCCH_POW_6		0x8966	// Ƶ������: ��С��6BCCH����ǿ��
#define	PARA_A_EXPA_WORK_EN		0xC401	// [WR]΢����: ��Ƶ�źſ���
#define	PARA_A_EXPA_DL_ATT		0xC441	// [WR]΢����: ����˥��ֵ
#define	PARA_A_EXPA_TEMP			0xC501	// [RO]΢����: �¶�
#define	PARA_A_EXPA_DL_POW		0xC503	// [RO]΢����: ����������ʵ�ƽ
#define	PARA_A_EXPA_SWR			0xC506	// [RO]΢����: ����פ����ֵ
#define	PARA_A_EXPA_POWER_DN	0xC301	// [RO]΢����: ��Դ����澯(3���Ӹ����ж�)
#define	PARA_A_EXPA_POWER_ERR	0xC302	// [RO]΢����: ��Դ���ϸ澯(3���Ӹ����ж�)
#define	PARA_A_EXPA_BATT_ERR		0xC304	// [RO]΢����: ���ģ���ع��ϸ澯(3���Ӹ����ж�)
#define	PARA_A_EXPA_POS_ALM		0xC305	// [RO]΢����: λ�ø澯
#define	PARA_A_EXPA_DOOR_ALM	0xC328	// [RO]΢����: �Ž��澯
#define	PARA_A_EXPA_WROK_ALM	0xC30D	// [RO]΢����: ���й��Ź��ϸ澯(3���Ӹ����ж�)
#define	PARA_A_EXPA_EXT1_ALM		0xC320	// [RO]΢����: �ⲿ�澯1
#define	PARA_A_EXPA_EXT2_ALM		0xC321	// [RO]΢����: �ⲿ�澯2
#define	PARA_A_EXPA_EXT3_ALM		0xC322	// [RO]΢����: �ⲿ�澯3
#define	PARA_A_EXPA_MAX_GAIN	0		// ΢����: ��˥�����棬���������
#define	PARA_A_EXPA_GAIN_THD		0		// ΢����: �������ޣ������������������ֵ
#define	PARA_A_EXPA_POW_THD		0		// ΢����: ���������������
#define	PARA_A_EXPA_POD_CMP 		0		// ΢����: �첨�ܹ��ʼ�ⲹ��ֵ,1�ֽ��з�����,���չ���Ϊ�첨�ܹ��ʼ��ϲ���ֵ
#define	PARA_MONITOR_VOL_OVER_THR 				0x0a62 			 // ��ص�ѹ������
#define 	PARA_MONITOR_VOL_OWE_THR 				0x0a63 			 // ��ص�ѹǷ����
#define 	PARA_DIGITAL_SINGNAL_ALARM 				0x8a68			 // �����ź��쳣�澯
#define 	PARA_HOST_DEVICE_LINK_SINGNAL_ALARM 	0x8a69			 // ���Ӽ����·�澯
#define 	PARA_MONITOR_BATTERY_ALARM 				0x8a6a			 // ���ģ���ع��ϸ澯
#define 	PARA_LOW_POWER_ALARM 					0x8a6b			 // ��Դ����澯
#define 	PARA_BATTERY_BREAKDOWN_ALARM 			0x8a6c			 // ��Դ���ϸ澯
#define 	PARA_POSITION_MOVE_ALARM					0x8a6f			 // λ�ø澯
#define 	PARA_A_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // A������������ʸ澯
#define 	PARA_A_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // A��������Ƿ���ʸ澯
#define 	PARA_B_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // B������������ʸ澯
#define 	PARA_B_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // B��������Ƿ���ʸ澯
#define 	PARA_C_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // C������������ʸ澯
#define 	PARA_C_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // C��������Ƿ���ʸ澯
#define 	PARA_D_INPUT_OVER_DPOW_THR_ALARM 		0x8a6d			 // D������������ʸ澯
#define 	PARA_D_INPUT_OWE_DPOW_THR_ALARM 		0x8a6e			 // D��������Ƿ���ʸ澯
#define 	PARA_TD_D_OVER_SLOT1_THR_ALARM 			0x8a66			 // TD�������뵼Ƶ�����ʸ澯
#define 	PARA_TD_D_OWE_SLOT1_THR_ALARM 			0x8a67			 // TD�������뵼ƵǷ���ʸ澯
#define 	PARA_RE_DATA_LAN_ST1     0x8a40     //����PHYоƬ����״̬  0: ������1: �澯
#define 	PARA_RE_CASCADE_LAN_ST1   0x8a48     //�������ڵĹ���״̬  0: ������1: �澯
#define 	PARA_RE_DATA_LAN_SYS_ST1  0x8a4a     //��������ͬ��״̬  0: ͬ����1: ʧ��
#define 	PARA_RE_CASCADE_LAN_SYS_ST1  0x8a52     //��������ͬ��״̬  0: ͬ����1: ʧ��
#define 	PARA_A_RF_POW_SWR           	0x8a32     //A�θ��ǵ�Ԫ����פ����
#define 	PARA_A_RF_OUT_POW_H_THR   		0x0a50     //A�θ��ǵ�Ԫ�������������
#define 	PARA_A_RF_OUT_POW_L_THR   		0x0a51     //A�θ��ǵ�Ԫ���Ƿ��������
#define 	PARA_B_RF_POW_SWR            	0x8a32     //B�θ��ǵ�Ԫ����פ����
#define 	PARA_B_RF_OUT_POW_H_THR   		0x0a50     //A�θ��ǵ�Ԫ�������������
#define 	PARA_B_RF_OUT_POW_L_THR   		0x0a51     //A�θ��ǵ�Ԫ���Ƿ��������
#define 	PARA_C_RF_POW_SWR           	0x8a32     //A�θ��ǵ�Ԫ����פ����
#define 	PARA_C_RF_OUT_POW_H_THR   		0x0a50     //A�θ��ǵ�Ԫ�������������
#define 	PARA_C_RF_OUT_POW_L_THR   		0x0a51     //A�θ��ǵ�Ԫ���Ƿ��������
#define 	PARA_D_RF_POW_SWR            	0x8a32     //B�θ��ǵ�Ԫ����פ����
#define 	PARA_D_RF_OUT_POW_H_THR   		0x0a50     //A�θ��ǵ�Ԫ�������������
#define 	PARA_D_RF_OUT_POW_L_THR   		0x0a51     //A�θ��ǵ�Ԫ���Ƿ��������
#define 	PARA_PWR_3V3_1_VT	0		// 3.3V��Դ��ѹ
#define 	PARA_PWR_3V3_2_VT	0		//	3.3V��Դ��ѹ
#define 	PARA_PWR_1V8_VT		0			// 1.8V��Դ��ѹ
#define 	PARA_PWR_1V5_VT		0			 // 1.5V��Դ��ѹ
#define 	PARA_A_DL_RF_EN 	0x0a67	// 	A��������Ƶʹ��	
#define 	PARA_A_UL_RF_EN 	0x0a68	// 	A��������Ƶʹ��	
#define 	PARA_B_DL_RF_EN 	0x0a67	// 	B��������Ƶʹ��	
#define 	PARA_B_UL_RF_EN		0x0a68	// 	B��������Ƶʹ��	
#define 	PARA_C_DL_RF_EN 	0x0a67	// 	C��������Ƶʹ��	
#define 	PARA_C_UL_RF_EN 	0x0a68	// 	C��������Ƶʹ��	
#define 	PARA_D_DL_RF_EN 	0x0a67	// 	D��������Ƶʹ��	
#define 	PARA_D_UL_RF_EN 	0x0a68	// 	D��������Ƶʹ��	
#define 	PARA_METER_OFFSET	0x0a66	//	����ƫ��ֵ����
#define 	PARA_METER_OFFSET_B	0x0a66	//	����ƫ��ֵ����
#define 	PARA_METER_OFFSET_C	0x0a66	//	����ƫ��ֵ����
#define 	PARA_METER_OFFSET_D	0x0a66	//	����ƫ��ֵ����
#define 	PARA_C_TD_TYPE_SELECT	0x0a6a	//686	// TD�������뵼Ƶ�����ʸ澯					
#define 	PARA_C_TD_NORMAL_CP	0x0a6b	//716	//	TDD����ʱ϶ NORMAL_CP
#define 	PARA_C_TD_EXTENDED_CP	0x0a6c	//717	//	TDD����ʱ϶ NORMAL_CP
#define 	PARA_C_TD_SYNC_ST	0x7620	//687	//	TDͬ��״̬:	0-��ͬ����1-δͬ��			
#define 	PARA_C_TD_WORK_MODE	0x08ac	//688	//	[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������			
#define 	PARA_C_TD_DL_OVER_SLOT1_THR_ALARM	0x8a66	//689	// TD�������뵼Ƶ�����ʸ澯					
#define 	PARA_C_TD_DL_OWE_SLOT1_THR_ALARM	0x8a67	//690	 // TD�������뵼ƵǷ���ʸ澯					
#define 	PARA_D_TD_TYPE_SELECT	0x0a6a	//691	// TD�������뵼Ƶ�����ʸ澯					
#define 	PARA_D_TD_NORMAL_CP	0x0a6b	//718	//	TDD����ʱ϶ NORMAL_CP
#define 	PARA_D_TD_EXTENDED_CP	0x0a6c	//719	//	TDD����ʱ϶ NORMAL_CP
#define 	PARA_D_TD_SYNC_ST	0x7620	//692	//	TDͬ��״̬:	0-��ͬ����1-δͬ��			
#define 	PARA_D_TD_WORK_MODE	0x08ac	//693	//	[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������			
#define 	PARA_D_TD_DL_OVER_SLOT1_THR_ALARM	0x8a66	//694	// TD�������뵼Ƶ�����ʸ澯					
#define 	PARA_D_TD_DL_OWE_SLOT1_THR_ALARM	0x8a67	//695	 // TD�������뵼ƵǷ���ʸ澯					
#define 	PARA_C_TD_T0_UD	0	//696	//	TDʱ϶0�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T1_UD	0	//697	//	TDʱ϶1�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T2_UD	0	//698	//	TDʱ϶2�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T3_UD	0	//699	//	TDʱ϶3�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T4_UD	0	//700	//	TDʱ϶4�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T5_UD	0	//701	//	TDʱ϶5�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T6_UD	0	//702	//	TDʱ϶6�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T7_UD	0	//703	//	TDʱ϶7�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T8_UD	0	//704	//	TDʱ϶8�����б�־:0-���У�1-����			
#define 	PARA_C_TD_T9_UD	0	//705	//	TDʱ϶9�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T0_UD	0	//706	//	TDʱ϶0�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T1_UD	0	//707	//	TDʱ϶1�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T2_UD	0	//708	//	TDʱ϶2�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T3_UD	0	//709	//	TDʱ϶3�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T4_UD	0	//710	//	TDʱ϶4�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T5_UD	0	//711	//	TDʱ϶5�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T6_UD	0	//712	//	TDʱ϶6�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T7_UD	0	//713	//	TDʱ϶7�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T8_UD	0	//714	//	TDʱ϶8�����б�־:0-���У�1-����			
#define 	PARA_D_TD_T9_UD	0	//715	//	TDʱ϶9�����б�־:0-���У�1-����//#endif
#define	PARA_NOISE_TEST_EN	0	//	�������Կ���		
#define	PARA_FREQ_MODIF_VAL_D	0x0a6d		//	��������ֵ
#define	PARA_FREQ_MODIF_VAL_B	0x0a6e		//	��������ֵ
#define	PARA_FREQ_MODIF_VAL_A	0x0a6f		//	��������ֵ
#define	PARA_B_TDS_2TH_BREAKING_POINT_SET	0x0609		//	TDS �ڶ�ת��������
#define 	PARA_DELAY_MODE_A	0x098f	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define 	PARA_DELAY_MODE_B	0x098f	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define 	PARA_DELAY_MODE_C	0x098f	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define 	PARA_DELAY_MODE_D	0x098f	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define	PARA_REE_CIRCUIT_ALARM	 		0
#define	PARA_REE_WLAN_CONN_ST			0
#define	PARA_DL_POWER_MAX			0
#define 	PARA_SLOT_TIME_EN_B		0	// ʱ϶����Զ���⿪��		
#define 	PARA_SLOT_TIME_DISTRI_B	0 // ʱ϶��ȷֲ�	BIT0��1����15���,BIT1��1����24���,	BIT2��1����33���			
#define 	PARA_VERSION_FLAG		0	// �汾��ʶ		
#define 	PARA_SLOT_TIME_EN_C	0	// ʱ϶����Զ���⿪��		
#define 	PARA_SLOT_TIME_DISTRI_C	0	// ʱ϶��ȷֲ�	BIT0��1����15���,BIT1��1����24���,	BIT2��1����33���			
#define 	PARA_A_1197_LOCK_ST		0	// A��1197����״̬	
#define 	PARA_A_IF_ST	0	// A����ƵƵ��,0/1---300M/500M		
#define 	PARA_ENCRYPTION_ST	0	//����״̬,0/1---������/����
#define 	PARA_PWR_1V6_VT	0	//����״̬,0/1---������/����
#define		PARA_A_90_VALUE			0				//A��9363 90�Ĵ�����ֵ
#define		PARA_A_91_VALUE			0				//A��9363 91�Ĵ�����ֵ
#define		PARA_A_94_VALUE			0				//A��9363 94�Ĵ�����ֵ
#define		PARA_A_95_VALUE			0				//A��9363 95�Ĵ�����ֵ
#define		PARA_B_90_VALUE			0				//B��9363 90�Ĵ�����ֵ
#define		PARA_B_91_VALUE			0				//B��9363 91�Ĵ�����ֵ
#define		PARA_B_94_VALUE			0				//B��9363 94�Ĵ�����ֵ
#define		PARA_B_95_VALUE			0				//B��9363 95�Ĵ�����ֵ
#define		PARA_C_90_VALUE			0				//C��9363 90�Ĵ�����ֵ
#define		PARA_C_91_VALUE			0				//C��9363 91�Ĵ�����ֵ
#define		PARA_C_94_VALUE			0				//C��9363 94�Ĵ�����ֵ
#define		PARA_C_95_VALUE			0				//C��9363 95�Ĵ�����ֵ
#define		PARA_D_90_VALUE			0				//D��9363 90�Ĵ�����ֵ
#define		PARA_D_91_VALUE			0				//D��9363 91�Ĵ�����ֵ
#define		PARA_D_94_VALUE			0				//D��9363 94�Ĵ�����ֵ
#define		PARA_D_95_VALUE			0				//D��9363 95�Ĵ�����ֵ
#define		PARA_PASSTHROUGH_EN			0				//����͸��ʹ��
#define		PARA_A_DL_POW_ADJ			0			
#define		PARA_B_DL_POW_ADJ			0			
#define		PARA_C_DL_POW_ADJ			0			
#define		PARA_D_DL_POW_ADJ			0			
#define		PARA_SoftwareLoadTimes			0		
#define     PARA_A_LNA_EN_ST 		   0	// 	A�����е����LNA����ʹ��

#endif

// ���ʵ�ַ>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 1B
#define 	MADD_A_CHANNEL_COUNT 	0	// 	A��֧�ֵ�ͨ����
#define 	MADD_A_DL_WORK_EN 	1	// 	A�����й���ʹ��
#define 	MADD_A_UL_WORK_EN 	2	// 	A�����й���ʹ��
#define 	MADD_A_DPOW_MODE 	3	// 	A�����й��ʿ��Ʒ�ʽ
#define 	MADD_A_UPOW_MODE 	4	// 	A�����й��ʿ��Ʒ�ʽ
#define 	MADD_A_LTHR_EN 	5	// 	A�����е�������ʹ��
#define 	MADD_A_LTHR_UP 	6	// 	A�ε�������������
#define 	MADD_A_LTHR_DN 	7	// 	A�ε�������������
#define 	MADD_A_DCH_EN1 	8	// 	A������ͨ������ʹ��1
#define 	MADD_A_DCH_EN2 	9	// 	A������ͨ������ʹ��2
#define 	MADD_A_DCH_EN3 	10	// 	A������ͨ������ʹ��3
#define 	MADD_A_DCH_EN4 	11	// 	A������ͨ������ʹ��4
#define 	MADD_A_DCH_EN5 	12	// 	A������ͨ������ʹ��5
#define 	MADD_A_DCH_EN6 	13	// 	A������ͨ������ʹ��6
#define 	MADD_A_DCH_EN7 	14	// 	A������ͨ������ʹ��7
#define 	MADD_A_DCH_EN8 	15	// 	A������ͨ������ʹ��8
#define 	MADD_A_DCH_EN9 	16	// 	A������ͨ������ʹ��9
#define 	MADD_A_DCH_EN10 	17	// 	A������ͨ������ʹ��10
#define 	MADD_A_DCH_EN11 	18	// 	A������ͨ������ʹ��11
#define 	MADD_A_DCH_EN12 	19	// 	A������ͨ������ʹ��12
#define 	MADD_A_DCH_EN13 	20	// 	A������ͨ������ʹ��13
#define 	MADD_A_DCH_EN14 	21	// 	A������ͨ������ʹ��14
#define 	MADD_A_DCH_EN15 	22	// 	A������ͨ������ʹ��15
#define 	MADD_A_DCH_EN16 	23	// 	A������ͨ������ʹ��16
#define 	MADD_A_UCH_EN1 	24	// 	A������ͨ������ʹ��1
#define 	MADD_A_UCH_EN2 	25	// 	A������ͨ������ʹ��2
#define 	MADD_A_UCH_EN3 	26	// 	A������ͨ������ʹ��3
#define 	MADD_A_UCH_EN4 	27	// 	A������ͨ������ʹ��4
#define 	MADD_A_UCH_EN5 	28	// 	A������ͨ������ʹ��5
#define 	MADD_A_UCH_EN6 	29	// 	A������ͨ������ʹ��6
#define 	MADD_A_UCH_EN7 	30	// 	A������ͨ������ʹ��7
#define 	MADD_A_UCH_EN8 	31	// 	A������ͨ������ʹ��8
#define 	MADD_A_UCH_EN9 	32	// 	A������ͨ������ʹ��9
#define 	MADD_A_UCH_EN10 	33	// 	A������ͨ������ʹ��10
#define 	MADD_A_UCH_EN11 	34	// 	A������ͨ������ʹ��11
#define 	MADD_A_UCH_EN12 	35	// 	A������ͨ������ʹ��12
#define 	MADD_A_UCH_EN13 	36	// 	A������ͨ������ʹ��13
#define 	MADD_A_UCH_EN14 	37	// 	A������ͨ������ʹ��14
#define 	MADD_A_UCH_EN15 	38	// 	A������ͨ������ʹ��15
#define 	MADD_A_UCH_EN16 	39	// 	A������ͨ������ʹ��16
#define 	MADD_A_DCH_GAIN1 	40	// 	A������ѡƵͨ���Ŵ�������1
#define 	MADD_A_DCH_GAIN2 	41	// 	A������ѡƵͨ���Ŵ�������2
#define 	MADD_A_DCH_GAIN3 	42	// 	A������ѡƵͨ���Ŵ�������3
#define 	MADD_A_DCH_GAIN4 	43	// 	A������ѡƵͨ���Ŵ�������4
#define 	MADD_A_DCH_GAIN5 	44	// 	A������ѡƵͨ���Ŵ�������5
#define 	MADD_A_DCH_GAIN6 	45	// 	A������ѡƵͨ���Ŵ�������6
#define 	MADD_A_DCH_GAIN7 	46	// 	A������ѡƵͨ���Ŵ�������7
#define 	MADD_A_DCH_GAIN8 	47	// 	A������ѡƵͨ���Ŵ�������8
#define 	MADD_A_DCH_GAIN9 	48	// 	A������ѡƵͨ���Ŵ�������9
#define 	MADD_A_DCH_GAIN10 	49	// 	A������ѡƵͨ���Ŵ�������10
#define 	MADD_A_DCH_GAIN11 	50	// 	A������ѡƵͨ���Ŵ�������11
#define 	MADD_A_DCH_GAIN12 	51	// 	A������ѡƵͨ���Ŵ�������12
#define 	MADD_A_DCH_GAIN13 	52	// 	A������ѡƵͨ���Ŵ�������13
#define 	MADD_A_DCH_GAIN14 	53	// 	A������ѡƵͨ���Ŵ�������14
#define 	MADD_A_DCH_GAIN15 	54	// 	A������ѡƵͨ���Ŵ�������15
#define 	MADD_A_DCH_GAIN16 	55	// 	A������ѡƵͨ���Ŵ�������16
#define 	MADD_A_UCH_GAIN1 	56	// 	A������ѡƵͨ���Ŵ�������1
#define 	MADD_A_UCH_GAIN2 	57	// 	A������ѡƵͨ���Ŵ�������2
#define 	MADD_A_UCH_GAIN3 	58	// 	A������ѡƵͨ���Ŵ�������3
#define 	MADD_A_UCH_GAIN4 	59	// 	A������ѡƵͨ���Ŵ�������4
#define 	MADD_A_UCH_GAIN5 	60	// 	A������ѡƵͨ���Ŵ�������5
#define 	MADD_A_UCH_GAIN6 	61	// 	A������ѡƵͨ���Ŵ�������6
#define 	MADD_A_UCH_GAIN7 	62	// 	A������ѡƵͨ���Ŵ�������7
#define 	MADD_A_UCH_GAIN8 	63	// 	A������ѡƵͨ���Ŵ�������8
#define 	MADD_A_UCH_GAIN9 	64	// 	A������ѡƵͨ���Ŵ�������9
#define 	MADD_A_UCH_GAIN10 	65	// 	A������ѡƵͨ���Ŵ�������10
#define 	MADD_A_UCH_GAIN11 	66	// 	A������ѡƵͨ���Ŵ�������11
#define 	MADD_A_UCH_GAIN12 	67	// 	A������ѡƵͨ���Ŵ�������12
#define 	MADD_A_UCH_GAIN13 	68	// 	A������ѡƵͨ���Ŵ�������13
#define 	MADD_A_UCH_GAIN14 	69	// 	A������ѡƵͨ���Ŵ�������14
#define 	MADD_A_UCH_GAIN15 	70	// 	A������ѡƵͨ���Ŵ�������15
#define 	MADD_A_UCH_GAIN16 	71	// 	A������ѡƵͨ���Ŵ�������16
#define 	MADD_A_DCH_ATT1 	72	// 	A����������˥����1
#define 	MADD_A_DCH_ATT2 	73	// 	A����������˥����2
#define 	MADD_A_DCH_ATT3 	74	// 	A����������˥����3
#define 	MADD_A_DCH_ATT4 	75	// 	A����������˥����4
#define 	MADD_A_DCH_ATT5 	76	// 	A����������˥����5
#define 	MADD_A_DCH_ATT6 	77	// 	A����������˥����6
#define 	MADD_A_DCH_ATT7 	78	// 	A����������˥����7
#define 	MADD_A_DCH_ATT8 	79	// 	A����������˥����8
#define 	MADD_A_DCH_ATT9 	80	// 	A����������˥����9
#define 	MADD_A_DCH_ATT10 	81	// 	A����������˥����10
#define 	MADD_A_DCH_ATT11 	82	// 	A����������˥����11
#define 	MADD_A_DCH_ATT12 	83	// 	A����������˥����12
#define 	MADD_A_DCH_ATT13 	84	// 	A����������˥����13
#define 	MADD_A_DCH_ATT14 	85	// 	A����������˥����14
#define 	MADD_A_DCH_ATT15 	86	// 	A����������˥����15
#define 	MADD_A_DCH_ATT16 	87	// 	A����������˥����16
#define 	MADD_A_UCH_ATT1 	88	// 	A����������˥����1
#define 	MADD_A_UCH_ATT2 	89	// 	A����������˥����2
#define 	MADD_A_UCH_ATT3 	90	// 	A����������˥����3
#define 	MADD_A_UCH_ATT4 	91	// 	A����������˥����4
#define 	MADD_A_UCH_ATT5 	92	// 	A����������˥����5
#define 	MADD_A_UCH_ATT6 	93	// 	A����������˥����6
#define 	MADD_A_UCH_ATT7 	94	// 	A����������˥����7
#define 	MADD_A_UCH_ATT8 	95	// 	A����������˥����8
#define 	MADD_A_UCH_ATT9 	96	// 	A����������˥����9	
#define 	MADD_A_UCH_ATT10 	97	// 	A����������˥����10	
#define 	MADD_A_UCH_ATT11 	98	// 	A����������˥����11	
#define 	MADD_A_UCH_ATT12 	99	// 	A����������˥����12	
#define 	MADD_A_UCH_ATT13 	100	// 	A����������˥����13	
#define 	MADD_A_UCH_ATT14 	101	// 	A����������˥����14	
#define 	MADD_A_UCH_ATT15 	102	// 	A����������˥����15	
#define 	MADD_A_UCH_ATT16 	103	// 	A����������˥����16	
#define 	MADD_A_DL_PA_GAIN 	104	// 	A�����й�������	
#define 	MADD_A_UL_PA_GAIN 	105	// 	A�����й�������	
#define 	MADD_A_TX_PLL_ST 	106	// 	A������PLL״̬,287 2ΪTX_VCO����������ʧ��	
#define 	MADD_A_RX_PLL_ST 	107	// 	A������PLL״̬	,247 2ΪRX_VCO����������ʧ��
#define 	MADD_A_INIT_DA_ST 	108	// 	��ʼ��A��DA״̬	,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define 	MADD_A_BB_PLL_LOCK 	109	// 	A��BB 	PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define 	MADD_A_FSAT 	110	// 	A��ǰ��AD����״̬	
#define 	MADD_A_DSAT 	111	// 	A�κ��DA���״̬	
#define 	MADD_A_PA_VG_EN 	112	// 	A�ι���դѹ״̬
#define 	MADD_A_PA_VT 	113	// 	A�ι��Źܵ�ѹ��ʾ
#define 	MADD_A_Modulator_EN 	114	// 	A�ε�����״̬
#define 	MADD_A_LNA_VT 	115	// 	A�����е����LNA��ѹ	
#define 	MADD_A_LNA1_ST 	116	// 	����LNA1״̬	
#define 	MADD_A_LNA2_ST 	117	// 	����LNA2״̬	
#define 	MADD_A_BUSY_TIME 	118	// 	A������ʱ϶ռ����	
#define 	MADD_A_PRI_ADD 	119	// 	A��ģ���ַ	
#define 	MADD_A_UL_POW_1B 	120	// 	A�����������ܹ���	
#define 	MADD_A_DL_POW_1B 	121	// 	A�����������ܹ���	
#define 	MADD_A_DCH_REC_RF_ATT1	122	//// 	REC�˵���������˥��������RF�˵���·����˥���� 	��rf
#define 	MADD_A_UCH_REC_RF_ATT1	123	//// 	REC�˵���������˥��������RF�˵���·����˥���� 	��rf
#define 	MADD_B_CHANNEL_COUNT 	124	// 	B��֧�ֵ�ͨ����	
#define 	MADD_B_DL_WORK_EN 	125	// 	B�����й���ʹ��	
#define 	MADD_B_UL_WORK_EN 	126	// 	B�����й���ʹ��	
#define 	MADD_B_DPOW_MODE 	127	// 	B�����й��ʿ��Ʒ�ʽ	
#define 	MADD_B_UPOW_MODE 	128	// 	B�����й��ʿ��Ʒ�ʽ
#define 	MADD_B_LTHR_EN 	129	// 	B�����е�������ʹ��
#define 	MADD_B_LTHR_UP 	130	// 	B�ε�������������
#define 	MADD_B_LTHR_DN 	131	// 	B�ε�������������
#define 	MADD_B_DCH_EN1 	132	// 	B������ͨ������ʹ��1
#define 	MADD_B_DCH_EN2 	133	// 	B������ͨ������ʹ��2
#define 	MADD_B_DCH_EN3 	134	// 	B������ͨ������ʹ��3
#define 	MADD_B_DCH_EN4 	135	// 	B������ͨ������ʹ��4
#define 	MADD_B_DCH_EN5 	136	// 	B������ͨ������ʹ��5
#define 	MADD_B_DCH_EN6 	137	// 	B������ͨ������ʹ��6
#define 	MADD_B_DCH_EN7 	138	// 	B������ͨ������ʹ��7
#define 	MADD_B_DCH_EN8 	139	// 	B������ͨ������ʹ��8
#define 	MADD_B_DCH_EN9 	140	// 	B������ͨ������ʹ��9
#define 	MADD_B_DCH_EN10 	141	// 	B������ͨ������ʹ��10
#define 	MADD_B_DCH_EN11 	142	// 	B������ͨ������ʹ��11
#define 	MADD_B_DCH_EN12 	143	// 	B������ͨ������ʹ��12
#define 	MADD_B_DCH_EN13 	144	// 	B������ͨ������ʹ��13
#define 	MADD_B_DCH_EN14 	145	// 	B������ͨ������ʹ��14
#define 	MADD_B_DCH_EN15 	146	// 	B������ͨ������ʹ��15
#define 	MADD_B_DCH_EN16 	147	// 	B������ͨ������ʹ��16
#define 	MADD_B_UCH_EN1 	148	// 	B������ͨ������ʹ��1
#define 	MADD_B_UCH_EN2 	149	// 	B������ͨ������ʹ��2
#define 	MADD_B_UCH_EN3 	150	// 	B������ͨ������ʹ��3
#define 	MADD_B_UCH_EN4 	151	// 	B������ͨ������ʹ��4
#define 	MADD_B_UCH_EN5 	152	// 	B������ͨ������ʹ��5
#define 	MADD_B_UCH_EN6 	153	// 	B������ͨ������ʹ��6
#define 	MADD_B_UCH_EN7 	154	// 	B������ͨ������ʹ��7
#define 	MADD_B_UCH_EN8 	155	// 	B������ͨ������ʹ��8
#define 	MADD_B_UCH_EN9 	156	// 	B������ͨ������ʹ��9
#define 	MADD_B_UCH_EN10 	157	// 	B������ͨ������ʹ��10
#define 	MADD_B_UCH_EN11 	158	// 	B������ͨ������ʹ��11
#define 	MADD_B_UCH_EN12 	159	// 	B������ͨ������ʹ��12
#define 	MADD_B_UCH_EN13 	160	// 	B������ͨ������ʹ��13
#define 	MADD_B_UCH_EN14 	161	// 	B������ͨ������ʹ��14
#define 	MADD_B_UCH_EN15 	162	// 	B������ͨ������ʹ��15
#define 	MADD_B_UCH_EN16 	163	// 	B������ͨ������ʹ��16
#define 	MADD_B_DCH_GAIN1 	164	// 	B������ѡƵͨ���Ŵ�������1
#define 	MADD_B_DCH_GAIN2 	165	// 	B������ѡƵͨ���Ŵ�������2
#define 	MADD_B_DCH_GAIN3 	166	// 	B������ѡƵͨ���Ŵ�������3
#define 	MADD_B_DCH_GAIN4 	167	// 	B������ѡƵͨ���Ŵ�������4
#define 	MADD_B_DCH_GAIN5 	168	// 	B������ѡƵͨ���Ŵ�������5
#define 	MADD_B_DCH_GAIN6 	169	// 	B������ѡƵͨ���Ŵ�������6
#define 	MADD_B_DCH_GAIN7 	170	// 	B������ѡƵͨ���Ŵ�������7
#define 	MADD_B_DCH_GAIN8 	171	// 	B������ѡƵͨ���Ŵ�������8
#define 	MADD_B_DCH_GAIN9 	172	// 	B������ѡƵͨ���Ŵ�������9
#define 	MADD_B_DCH_GAIN10 	173	// 	B������ѡƵͨ���Ŵ�������10
#define 	MADD_B_DCH_GAIN11 	174	// 	B������ѡƵͨ���Ŵ�������11
#define 	MADD_B_DCH_GAIN12 	175	// 	B������ѡƵͨ���Ŵ�������12
#define 	MADD_B_DCH_GAIN13 	176	// 	B������ѡƵͨ���Ŵ�������13
#define 	MADD_B_DCH_GAIN14 	177	// 	B������ѡƵͨ���Ŵ�������14
#define 	MADD_B_DCH_GAIN15 	178	// 	B������ѡƵͨ���Ŵ�������15
#define 	MADD_B_DCH_GAIN16 	179	// 	B������ѡƵͨ���Ŵ�������16
#define 	MADD_B_UCH_GAIN1 	180	// 	B������ѡƵͨ���Ŵ�������1
#define 	MADD_B_UCH_GAIN2 	181	// 	B������ѡƵͨ���Ŵ�������2
#define 	MADD_B_UCH_GAIN3 	182	// 	B������ѡƵͨ���Ŵ�������3
#define 	MADD_B_UCH_GAIN4 	183	// 	B������ѡƵͨ���Ŵ�������4
#define 	MADD_B_UCH_GAIN5 	184	// 	B������ѡƵͨ���Ŵ�������5
#define 	MADD_B_UCH_GAIN6 	185	// 	B������ѡƵͨ���Ŵ�������6
#define 	MADD_B_UCH_GAIN7 	186	// 	B������ѡƵͨ���Ŵ�������7
#define 	MADD_B_UCH_GAIN8 	187	// 	B������ѡƵͨ���Ŵ�������8
#define 	MADD_B_UCH_GAIN9 	188	// 	B������ѡƵͨ���Ŵ�������9
#define 	MADD_B_UCH_GAIN10 	189	// 	B������ѡƵͨ���Ŵ�������10
#define 	MADD_B_UCH_GAIN11 	190	// 	B������ѡƵͨ���Ŵ�������11
#define 	MADD_B_UCH_GAIN12 	191	// 	B������ѡƵͨ���Ŵ�������12
#define 	MADD_B_UCH_GAIN13 	192	// 	B������ѡƵͨ���Ŵ�������13
#define 	MADD_B_UCH_GAIN14 	193	// 	B������ѡƵͨ���Ŵ�������14
#define 	MADD_B_UCH_GAIN15 	194	// 	B������ѡƵͨ���Ŵ�������15
#define 	MADD_B_UCH_GAIN16 	195	// 	B������ѡƵͨ���Ŵ�������16
#define 	MADD_B_DCH_ATT1 	196	// 	B�������������˥����1
#define 	MADD_B_DCH_ATT2 	197	// 	B�������������˥����2
#define 	MADD_B_DCH_ATT3 	198	// 	B�������������˥����3
#define 	MADD_B_DCH_ATT4 	199	// 	B�������������˥����4
#define 	MADD_B_DCH_ATT5 	200	// 	B�������������˥����5
#define 	MADD_B_DCH_ATT6 	201	// 	B�������������˥����6
#define 	MADD_B_DCH_ATT7 	202	// 	B�������������˥����7
#define 	MADD_B_DCH_ATT8 	203	// 	B�������������˥����8
#define 	MADD_B_DCH_ATT9 	204	// 	B�������������˥����9
#define 	MADD_B_DCH_ATT10 	205	// 	B�������������˥����10
#define 	MADD_B_DCH_ATT11 	206	// 	B�������������˥����11
#define 	MADD_B_DCH_ATT12 	207	// 	B�������������˥����12
#define 	MADD_B_DCH_ATT13 	208	// 	B�������������˥����13
#define 	MADD_B_DCH_ATT14 	209	// 	B�������������˥����14
#define 	MADD_B_DCH_ATT15 	210	// 	B�������������˥����15
#define 	MADD_B_DCH_ATT16 	211	// 	B�������������˥����16
#define 	MADD_B_UCH_ATT1 	212	// 	B��������������˥����1
#define 	MADD_B_UCH_ATT2 	213	// 	B��������������˥����2
#define 	MADD_B_UCH_ATT3 	214	// 	B��������������˥����3
#define 	MADD_B_UCH_ATT4 	215	// 	B��������������˥����4
#define 	MADD_B_UCH_ATT5 	216	// 	B��������������˥����5
#define 	MADD_B_UCH_ATT6 	217	// 	B��������������˥����6
#define 	MADD_B_UCH_ATT7 	218	// 	B��������������˥����7
#define 	MADD_B_UCH_ATT8 	219	// 	B��������������˥����8
#define 	MADD_B_UCH_ATT9 	220	// 	B��������������˥����9
#define 	MADD_B_UCH_ATT10 	221	// 	B��������������˥����10
#define 	MADD_B_UCH_ATT11 	222	// 	B��������������˥����11
#define 	MADD_B_UCH_ATT12 	223	// 	B��������������˥����12
#define 	MADD_B_UCH_ATT13 	224	// 	B��������������˥����13	
#define 	MADD_B_UCH_ATT14 	225	// 	B��������������˥����14	
#define 	MADD_B_UCH_ATT15 	226	// 	B��������������˥����15	
#define 	MADD_B_UCH_ATT16 	227	// 	B��������������˥����16	
#define 	MADD_B_DL_PA_GAIN 	228	// 	B�����й�������	
#define 	MADD_B_UL_PA_GAIN 	229	// 	B�����й�������	
#define 	MADD_B_TX_PLL_ST 	230	// 	B������PLL״̬	,287 2ΪTX_VCO����������ʧ��
#define 	MADD_B_RX_PLL_ST 	231	// 	B������PLL״̬,247 2ΪRX_VCO����������ʧ��	
#define 	MADD_B_INIT_DA_ST 	232	// 	��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣	
#define 	MADD_B_BB_PLL_LOCK 	233	// 	B��BB 	PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define 	MADD_B_FSAT 	234	// 	B��ǰ��AD����״̬	
#define 	MADD_B_DSAT 	235	// 	B�κ��DA���״̬	
#define 	MADD_B_PA_VG_EN 	236	// 	B�ι���դѹ״̬
#define 	MADD_B_PA_VT 	237	// 	B�ι��Źܵ�ѹ��ʾ
#define 	MADD_B_Modulator_EN 	238	// 	B�ε�����״̬
#define 	MADD_B_LNA_VT 	239	// 	B�����е����LNA��ѹ	
#define 	MADD_B_LNA1_ST 	240	// 	����LNA1״̬		
#define 	MADD_B_LNA2_ST 	241	// 	����LNA2״̬		
#define 	MADD_B_BUSY_TIME 	242	// 	B������ʱ϶ռ����		
#define 	MADD_B_PRI_ADD 	243	// 	B��ģ���ַ		
#define 	MADD_B_UL_POW_1B 	244	// 	B�����������ܹ���		
#define 	MADD_B_DL_POW_1B 	245	// 	B�����������ܹ���		
#define 	MADD_B_DCH_REC_RF_ATT1	246	//// 	REC�˵���������˥��������RF�˵���·����˥���� 	��rf
#define 	MADD_B_UCH_REC_RF_ATT1  	247	 //// 	REC�˵���������˥��������RF�˵���·����˥���� 	 	��rf
#define 	MADD_C_CHANNEL_COUNT 	248	// 	C��֧�ֵ�ͨ����		
#define 	MADD_C_DL_WORK_EN 	249	// 	C�����й���ʹ��		
#define 	MADD_C_UL_WORK_EN 	250	// 	C�����й���ʹ��		
#define 	MADD_C_DPOW_MODE 	251	// 	C�����й��ʿ��Ʒ�ʽ		
#define 	MADD_C_UPOW_MODE 	252	// 	C�����й��ʿ��Ʒ�ʽ		
#define 	MADD_C_LTHR_EN 	253	// 	C�����е�������ʹ��		
#define 	MADD_C_LTHR_UP 	254	// 	C�ε�������������		
#define 	MADD_C_LTHR_DN 	255	// 	C�ε�������������		
#define 	MADD_C_DCH_EN1 	256	// 	C������ͨ������ʹ��1
#define 	MADD_C_DCH_EN2 	257	// 	C������ͨ������ʹ��2
#define 	MADD_C_DCH_EN3 	258	// 	C������ͨ������ʹ��3
#define 	MADD_C_DCH_EN4 	259	// 	C������ͨ������ʹ��4
#define 	MADD_C_DCH_EN5 	260	// 	C������ͨ������ʹ��5
#define 	MADD_C_DCH_EN6 	261	// 	C������ͨ������ʹ��6
#define 	MADD_C_DCH_EN7 	262	// 	C������ͨ������ʹ��7
#define 	MADD_C_DCH_EN8 	263	// 	C������ͨ������ʹ��8
#define 	MADD_C_DCH_EN9 	264	// 	C������ͨ������ʹ��9
#define 	MADD_C_DCH_EN10 	265	// 	C������ͨ������ʹ��10
#define 	MADD_C_UCH_EN1 	266	// 	C������ͨ������ʹ��1
#define 	MADD_C_UCH_EN2 	267	// 	C������ͨ������ʹ��2
#define 	MADD_C_UCH_EN3 	268	// 	C������ͨ������ʹ��3
#define 	MADD_C_UCH_EN4 	269	// 	C������ͨ������ʹ��4
#define 	MADD_C_UCH_EN5 	270	// 	C������ͨ������ʹ��5
#define 	MADD_C_UCH_EN6 	271	// 	C������ͨ������ʹ��6
#define 	MADD_C_UCH_EN7 	272	// 	C������ͨ������ʹ��7
#define 	MADD_C_UCH_EN8 	273	// 	C������ͨ������ʹ��8
#define 	MADD_C_UCH_EN9 	274	// 	C������ͨ������ʹ��9
#define 	MADD_C_UCH_EN10 	275	// 	C������ͨ������ʹ��10
#define 	MADD_C_DCH_GAIN1 	276	// 	C������ѡƵͨ���Ŵ�������1
#define 	MADD_C_DCH_GAIN2 	277	// 	C������ѡƵͨ���Ŵ�������2
#define 	MADD_C_DCH_GAIN3 	278	// 	C������ѡƵͨ���Ŵ�������3
#define 	MADD_C_DCH_GAIN4 	279	// 	C������ѡƵͨ���Ŵ�������4
#define 	MADD_C_DCH_GAIN5 	280	// 	C������ѡƵͨ���Ŵ�������5
#define 	MADD_C_DCH_GAIN6 	281	// 	C������ѡƵͨ���Ŵ�������6
#define 	MADD_C_DCH_GAIN7 	282	// 	C������ѡƵͨ���Ŵ�������7
#define 	MADD_C_DCH_GAIN8 	283	// 	C������ѡƵͨ���Ŵ�������8
#define 	MADD_C_DCH_GAIN9 	284	// 	C������ѡƵͨ���Ŵ�������9
#define 	MADD_C_DCH_GAIN10 	285	// 	C������ѡƵͨ���Ŵ�������10
#define 	MADD_C_DCH_GAIN11 	286	// 	C������ѡƵͨ���Ŵ�������11
#define 	MADD_C_DCH_GAIN12 	287	// 	C������ѡƵͨ���Ŵ�������12
#define 	MADD_C_DCH_GAIN13 	288	// 	C������ѡƵͨ���Ŵ�������13
#define 	MADD_C_DCH_GAIN14 	289	// 	C������ѡƵͨ���Ŵ�������14
#define 	MADD_C_DCH_GAIN15 	290	// 	C������ѡƵͨ���Ŵ�������15
#define 	MADD_C_DCH_GAIN16 	291	// 	C������ѡƵͨ���Ŵ�������16
#define 	MADD_C_UCH_GAIN1 	292	// 	C������ѡƵͨ���Ŵ�������1
#define 	MADD_C_UCH_GAIN2 	293	// 	C������ѡƵͨ���Ŵ�������2
#define 	MADD_C_UCH_GAIN3 	294	// 	C������ѡƵͨ���Ŵ�������3
#define 	MADD_C_UCH_GAIN4 	295	// 	C������ѡƵͨ���Ŵ�������4
#define 	MADD_C_UCH_GAIN5 	296	// 	C������ѡƵͨ���Ŵ�������5
#define 	MADD_C_UCH_GAIN6 	297	// 	C������ѡƵͨ���Ŵ�������6
#define 	MADD_C_UCH_GAIN7 	298	// 	C������ѡƵͨ���Ŵ�������7
#define 	MADD_C_UCH_GAIN8 	299	// 	C������ѡƵͨ���Ŵ�������8
#define 	MADD_C_UCH_GAIN9 	300	// 	C������ѡƵͨ���Ŵ�������9
#define 	MADD_C_UCH_GAIN10 	301	// 	C������ѡƵͨ���Ŵ�������10
#define 	MADD_C_UCH_GAIN11 	302	// 	C������ѡƵͨ���Ŵ�������11
#define 	MADD_C_UCH_GAIN12 	303	// 	C������ѡƵͨ���Ŵ�������12
#define 	MADD_C_UCH_GAIN13 	304	// 	C������ѡƵͨ���Ŵ�������13
#define 	MADD_C_UCH_GAIN14 	305	// 	C������ѡƵͨ���Ŵ�������14
#define 	MADD_C_UCH_GAIN15 	306	// 	C������ѡƵͨ���Ŵ�������15
#define 	MADD_C_UCH_GAIN16 	307	// 	C������ѡƵͨ���Ŵ�������16
#define 	MADD_C_DCH_ATT1 	308	// 	C����������˥����1
#define 	MADD_C_DCH_ATT2 	309	// 	C����������˥����2
#define 	MADD_C_DCH_ATT3 	310	// 	C����������˥����3
#define 	MADD_C_DCH_ATT4 	311	// 	C����������˥����4
#define 	MADD_C_DCH_ATT5 	312	// 	C����������˥����5
#define 	MADD_C_DCH_ATT6 	313	// 	C����������˥����6
#define 	MADD_C_DCH_ATT7 	314	// 	C����������˥����7
#define 	MADD_C_DCH_ATT8 	315	// 	C����������˥����8
#define 	MADD_C_DCH_ATT9 	316	// 	C����������˥����9
#define 	MADD_C_DCH_ATT10 	317	// 	C����������˥����10
#define 	MADD_C_DCH_ATT11 	318	// 	C����������˥����11
#define 	MADD_C_DCH_ATT12 	319	// 	C����������˥����12
#define 	MADD_C_DCH_ATT13 	320	// 	C����������˥����13
#define 	MADD_C_DCH_ATT14 	321	// 	C����������˥����14
#define 	MADD_C_DCH_ATT15 	322	// 	C����������˥����15
#define 	MADD_C_DCH_ATT16 	323	// 	C����������˥����16
#define 	MADD_C_UCH_ATT1 	324	// 	C����������˥����1
#define 	MADD_C_UCH_ATT2 	325	// 	C����������˥����2
#define 	MADD_C_UCH_ATT3 	326	// 	C����������˥����3
#define 	MADD_C_UCH_ATT4 	327	// 	C����������˥����4
#define 	MADD_C_UCH_ATT5 	328	// 	C����������˥����5
#define 	MADD_C_UCH_ATT6 	329	// 	C����������˥����6
#define 	MADD_C_UCH_ATT7 	330	// 	C����������˥����7
#define 	MADD_C_UCH_ATT8 	331	// 	C����������˥����8
#define 	MADD_C_UCH_ATT9 	332	// 	C����������˥����9
#define 	MADD_C_UCH_ATT10 	333	// 	C����������˥����10
#define 	MADD_C_UCH_ATT11 	334	// 	C����������˥����11
#define 	MADD_C_UCH_ATT12 	335	// 	C����������˥����12
#define 	MADD_C_UCH_ATT13 	336	// 	C����������˥����13	
#define 	MADD_C_UCH_ATT14 	337	// 	C����������˥����14	
#define 	MADD_C_UCH_ATT15 	338	// 	C����������˥����15	
#define 	MADD_C_UCH_ATT16 	339	// 	C����������˥����16	
#define 	MADD_C_DL_PA_GAIN 	340	// 	C�����й�������	
#define 	MADD_C_UL_PA_GAIN 	341	// 	C�����й�������	
#define 	MADD_C_TX_PLL_ST 	342	// 	C������PLL״̬,287 2ΪTX_VCO����������ʧ��	
#define 	MADD_C_RX_PLL_ST 	343	// 	C������PLL״̬,247 2ΪRX_VCO����������ʧ��	
#define 	MADD_C_INIT_DA_ST 	344	// 	��ʼ��A��DA״̬	,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣
#define 	MADD_C_BB_PLL_LOCK 	345	// 	C��BB 	PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define 	MADD_C_FSAT 	346	// 	C��ǰ��AD����״̬	
#define 	MADD_C_DSAT 	347	// 	C�κ��DA���״̬	
#define 	MADD_C_PA_VG_EN 	348	// 	C�ι���դѹ״̬
#define 	MADD_C_PA_VT 	349	// 	C�ι��Źܵ�ѹ��ʾ
#define 	MADD_C_Modulator_EN 	350	// 	C�ε�����״̬
#define 	MADD_C_LNA_VT 	351	// 	C�����е����LNA��ѹ	
#define 	MADD_C_LNA1_ST 	352	// 	����LNA1״̬	
#define 	MADD_C_LNA2_ST 	353	// 	����LNA2״̬	
#define 	MADD_C_BUSY_TIME 	354	// 	C������ʱ϶ռ����	
#define 	MADD_C_PRI_ADD 	355	// 	C��ģ���ַ	
#define 	MADD_C_UL_POW_1B 	356	// 	C�����������ܹ���	
#define 	MADD_C_DL_POW_1B 	357	// 	C�����������ܹ���	
#define 	MADD_C_DCH_REC_RF_ATT1	358	//// 	REC�˵���������˥��������RF�˵���·����˥���� 	��rf
#define 	MADD_C_UCH_REC_RF_ATT1	359	//// 	REC�˵���������˥��������RF�˵���·����˥���� 	��rf
#define 	MADD_D_CHANNEL_COUNT 	360	// 	D��֧�ֵ�ͨ����	
#define 	MADD_D_DL_WORK_EN 	361	// 	D�����й���ʹ��	
#define 	MADD_D_UL_WORK_EN 	362	// 	D�����й���ʹ��	
#define 	MADD_D_DPOW_MODE 	363	// 	D�����й��ʿ��Ʒ�ʽ	
#define 	MADD_D_UPOW_MODE 	364	// 	D�����й��ʿ��Ʒ�ʽ	
#define 	MADD_D_LTHR_EN 	365	// 	D�����е�������ʹ��	
#define 	MADD_D_LTHR_UP 	366	// 	D�ε�������������	
#define 	MADD_D_LTHR_DN 	367	// 	D�ε�������������	
#define 	MADD_D_DCH_EN1 	368	// 	D������ͨ������ʹ��1
#define 	MADD_D_DCH_EN2 	369	// 	D������ͨ������ʹ��2
#define 	MADD_D_DCH_EN3 	370	// 	D������ͨ������ʹ��3
#define 	MADD_D_DCH_EN4 	371	// 	D������ͨ������ʹ��4
#define 	MADD_D_DCH_EN5 	372	// 	D������ͨ������ʹ��5
#define 	MADD_D_DCH_EN6 	373	// 	D������ͨ������ʹ��6
#define 	MADD_D_DCH_EN7 	374	// 	D������ͨ������ʹ��7
#define 	MADD_D_DCH_EN8 	375	// 	D������ͨ������ʹ��8
#define 	MADD_D_DCH_EN9 	376	// 	D������ͨ������ʹ��9
#define 	MADD_D_DCH_EN10 	377	// 	D������ͨ������ʹ��10
#define 	MADD_D_UCH_EN1 	378	// 	D������ͨ������ʹ��1
#define 	MADD_D_UCH_EN2 	379	// 	D������ͨ������ʹ��2
#define 	MADD_D_UCH_EN3 	380	// 	D������ͨ������ʹ��3
#define 	MADD_D_UCH_EN4 	381	// 	D������ͨ������ʹ��4
#define 	MADD_D_UCH_EN5 	382	// 	D������ͨ������ʹ��5
#define 	MADD_D_UCH_EN6 	383	// 	D������ͨ������ʹ��6
#define 	MADD_D_UCH_EN7 	384	// 	D������ͨ������ʹ��7
#define 	MADD_D_UCH_EN8 	385	// 	D������ͨ������ʹ��8
#define 	MADD_D_UCH_EN9 	386	// 	D������ͨ������ʹ��9
#define 	MADD_D_UCH_EN10 	387	// 	D������ͨ������ʹ��10
#define 	MADD_D_DCH_GAIN1 	388	// 	D������ѡƵͨ���Ŵ�������1
#define 	MADD_D_DCH_GAIN2 	389	// 	D������ѡƵͨ���Ŵ�������2
#define 	MADD_D_DCH_GAIN3 	390	// 	D������ѡƵͨ���Ŵ�������3
#define 	MADD_D_DCH_GAIN4 	391	// 	D������ѡƵͨ���Ŵ�������4
#define 	MADD_D_DCH_GAIN5 	392	// 	D������ѡƵͨ���Ŵ�������5
#define 	MADD_D_DCH_GAIN6 	393	// 	D������ѡƵͨ���Ŵ�������6
#define 	MADD_D_DCH_GAIN7 	394	// 	D������ѡƵͨ���Ŵ�������7
#define 	MADD_D_DCH_GAIN8 	395	// 	D������ѡƵͨ���Ŵ�������8
#define 	MADD_D_DCH_GAIN9 	396	// 	D������ѡƵͨ���Ŵ�������9
#define 	MADD_D_DCH_GAIN10 	397	// 	D������ѡƵͨ���Ŵ�������10
#define 	MADD_D_DCH_GAIN11 	398	// 	D������ѡƵͨ���Ŵ�������11
#define 	MADD_D_DCH_GAIN12 	399	// 	D������ѡƵͨ���Ŵ�������12
#define 	MADD_D_DCH_GAIN13 	400	// 	D������ѡƵͨ���Ŵ�������13
#define 	MADD_D_DCH_GAIN14 	401	// 	D������ѡƵͨ���Ŵ�������14
#define 	MADD_D_DCH_GAIN15 	402	// 	D������ѡƵͨ���Ŵ�������15
#define 	MADD_D_DCH_GAIN16 	403	// 	D������ѡƵͨ���Ŵ�������16
#define 	MADD_D_UCH_GAIN1 	404	// 	D������ѡƵͨ���Ŵ�������1
#define 	MADD_D_UCH_GAIN2 	405	// 	D������ѡƵͨ���Ŵ�������2
#define 	MADD_D_UCH_GAIN3 	406	// 	D������ѡƵͨ���Ŵ�������3
#define 	MADD_D_UCH_GAIN4 	407	// 	D������ѡƵͨ���Ŵ�������4
#define 	MADD_D_UCH_GAIN5 	408	// 	D������ѡƵͨ���Ŵ�������5
#define 	MADD_D_UCH_GAIN6 	409	// 	D������ѡƵͨ���Ŵ�������6
#define 	MADD_D_UCH_GAIN7 	410	// 	D������ѡƵͨ���Ŵ�������7
#define 	MADD_D_UCH_GAIN8 	411	// 	D������ѡƵͨ���Ŵ�������8
#define 	MADD_D_UCH_GAIN9 	412	// 	D������ѡƵͨ���Ŵ�������9
#define 	MADD_D_UCH_GAIN10 	413	// 	D������ѡƵͨ���Ŵ�������10
#define 	MADD_D_UCH_GAIN11 	414	// 	D������ѡƵͨ���Ŵ�������11
#define 	MADD_D_UCH_GAIN12 	415	// 	D������ѡƵͨ���Ŵ�������12
#define 	MADD_D_UCH_GAIN13 	416	// 	D������ѡƵͨ���Ŵ�������13
#define 	MADD_D_UCH_GAIN14 	417	// 	D������ѡƵͨ���Ŵ�������14
#define 	MADD_D_UCH_GAIN15 	418	// 	D������ѡƵͨ���Ŵ�������15
#define 	MADD_D_UCH_GAIN16 	419	// 	D������ѡƵͨ���Ŵ�������16
#define 	MADD_D_DCH_ATT1 	420	// 	D�������������˥����1
#define 	MADD_D_DCH_ATT2 	421	// 	D�������������˥����2
#define 	MADD_D_DCH_ATT3 	422	// 	D�������������˥����3
#define 	MADD_D_DCH_ATT4 	423	// 	D�������������˥����4
#define 	MADD_D_DCH_ATT5 	424	// 	D�������������˥����5
#define 	MADD_D_DCH_ATT6 	425	// 	D�������������˥����6
#define 	MADD_D_DCH_ATT7 	426	// 	D�������������˥����7
#define 	MADD_D_DCH_ATT8 	427	// 	D�������������˥����8
#define 	MADD_D_DCH_ATT9 	428	// 	D�������������˥����9
#define 	MADD_D_DCH_ATT10 	429	// 	D�������������˥����10
#define 	MADD_D_DCH_ATT11 	430	// 	D�������������˥����11
#define 	MADD_D_DCH_ATT12 	431	// 	D�������������˥����12
#define 	MADD_D_DCH_ATT13 	432	// 	D�������������˥����13
#define 	MADD_D_DCH_ATT14	433	// 	D�������������˥����14
#define 	MADD_D_DCH_ATT15 	434	// 	D�������������˥����15
#define 	MADD_D_DCH_ATT16 	435	// 	D�������������˥����16
#define 	MADD_D_UCH_ATT1 	436	// 	D��������������˥����1
#define 	MADD_D_UCH_ATT2 	437	// 	D��������������˥����2
#define 	MADD_D_UCH_ATT3 	438	// 	D��������������˥����3
#define 	MADD_D_UCH_ATT4 	439	// 	D��������������˥����4
#define 	MADD_D_UCH_ATT5 	440	// 	D��������������˥����5
#define 	MADD_D_UCH_ATT6 	441	// 	D��������������˥����6
#define 	MADD_D_UCH_ATT7 	442	// 	D��������������˥����7
#define 	MADD_D_UCH_ATT8 	443	// 	D��������������˥����8
#define 	MADD_D_UCH_ATT9 	444	// 	D��������������˥����9
#define 	MADD_D_UCH_ATT10 	445	// 	D��������������˥����10
#define 	MADD_D_UCH_ATT11 	446	// 	D��������������˥����11
#define 	MADD_D_UCH_ATT12 	447	// 	D��������������˥����12
#define 	MADD_D_UCH_ATT13 	448	// 	D��������������˥����13	
#define 	MADD_D_UCH_ATT14 	449	// 	D��������������˥����14	
#define 	MADD_D_UCH_ATT15	450	// 	D��������������˥����15	
#define 	MADD_D_UCH_ATT16 	451	// 	D��������������˥����16	
#define 	MADD_D_DL_PA_GAIN 	452	// 	D�����й�������	
#define 	MADD_D_UL_PA_GAIN 	453	// 	D�����й�������	
#define 	MADD_D_TX_PLL_ST 	454	// 	D������PLL״̬	,287 2ΪTX_VCO����������ʧ��
#define 	MADD_D_RX_PLL_ST 	455	// 	D������PLL״̬,247 2ΪRX_VCO����������ʧ��	
#define 	MADD_D_INIT_DA_ST 	456	// 	��ʼ��B��DA״̬,17 1AΪ����+���ͽ���ʹ�ܴ򿪣������쳣	
#define 	MADD_D_BB_PLL_LOCK 	457	// 	D��BB 	PLL����״̬,5E 80ΪBBPLL�������໷����������ʧ��
#define 	MADD_D_FSAT 	458	// 	D��ǰ��AD����״̬	
#define 	MADD_D_DSAT 	459	// 	D�κ��DA���״̬	
#define 	MADD_D_PA_VG_EN 	460	// 	D�ι���դѹ״̬
#define 	MADD_D_PA_VT 	461	// 	D�ι��Źܵ�ѹ��ʾ	
#define 	MADD_D_Modulator_EN 	462	// 	D�ε�����״̬
#define 	MADD_D_LNA_VT 	463	// 	D�����е����LNA��ѹ	
#define 	MADD_D_LNA1_ST 	464	// 	����LNA1״̬		
#define 	MADD_D_LNA2_ST 	465	// 	����LNA2״̬		
#define 	MADD_D_BUSY_TIME 	466	// 	D������ʱ϶ռ����		
#define 	MADD_D_PRI_ADD 	467	// 	D��ģ���ַ		
#define 	MADD_D_UL_POW_1B 	468	// 	D�����������ܹ���		
#define 	MADD_D_DL_POW_1B 	469	// 	D�����������ܹ���		
#define 	MADD_D_DCH_REC_RF_ATT1	470	//// 	REC�˵���������˥��������RF�˵���·����˥���� 	��rf
#define 	MADD_D_UCH_REC_RF_ATT1  	471	 //// 	REC�˵���������˥��������RF�˵���·����˥���� 	 	��rf
#define	MADD_FP1_EN	472	//	��ڷ���ʹ��1		
#define	MADD_FP2_EN	473	//	��ڷ���ʹ��2		
#define	MADD_FP3_EN	474	//	��ڷ���ʹ��3		
#define	MADD_FP4_EN	475	//	��ڷ���ʹ��4		
#define	MADD_FP5_EN	476	//	��ڷ���ʹ��5		
#define	MADD_FP6_EN	477	//	��ڷ���ʹ��6		
#define	MADD_FP7_EN	478	//	��ڷ���ʹ��7		
#define	MADD_FP8_EN	479	//	��ڷ���ʹ��8		
#define	MADD_FP9_EN	480	//	��ڷ���ʹ��9	
#define	MADD_FP10_EN	481	//	��ڷ���ʹ��10	
#define	MADD_FP11_EN	482	//	��ڷ���ʹ��11	
#define	MADD_FP12_EN	483	//	��ڷ���ʹ��12	
#define	MADD_FP13_EN	484	//	��ڷ���ʹ��13	
#define	MADD_FP14_EN	485	//	��ڷ���ʹ��14	
#define	MADD_FP15_EN	486	//	��ڷ���ʹ��15	
#define	MADD_FP16_EN	487	//	��ڷ���ʹ��16	
#define	MADD_FP1_ON_POS	488	//	�����λ״̬1,	0-��λ
#define	MADD_FP2_ON_POS	489	//	�����λ״̬2,	0-��λ
#define	MADD_FP3_ON_POS	490	//	�����λ״̬3,	0-��λ
#define	MADD_FP4_ON_POS	491	//	�����λ״̬4,	0-��λ
#define	MADD_FP5_ON_POS	492	//	�����λ״̬5,	0-��λ
#define	MADD_FP6_ON_POS	493	//	�����λ״̬6,	0-��λ
#define	MADD_FP7_ON_POS	494	//	�����λ״̬7,	0-��λ
#define	MADD_FP8_ON_POS	495	//	�����λ״̬8,	0-��λ
#define	MADD_FP9_ON_POS	496	//	�����λ״̬9,	0-��λ
#define	MADD_FP10_ON_POS	497	//	�����λ״̬10,	0-��λ
#define	MADD_FP11_ON_POS	498	//	�����λ״̬11,	0-��λ
#define	MADD_FP12_ON_POS	499	//	�����λ״̬12,	0-��λ
#define	MADD_FP13_ON_POS	500	//	�����λ״̬13,	0-��λ
#define	MADD_FP14_ON_POS	501	//	�����λ״̬14,	0-��λ
#define	MADD_FP15_ON_POS	502	//	�����λ״̬15,	0-��λ
#define	MADD_FP16_ON_POS	503	//	�����λ״̬16,	0-��λ
#define	MADD_FP1_LOS	504	//	���1�źŶ�ʧ״̬	
#define	MADD_FP2_LOS	505	//	���2�źŶ�ʧ״̬	
#define	MADD_FP3_LOS	506	//	���3�źŶ�ʧ״̬	
#define	MADD_FP4_LOS	507	//	���4�źŶ�ʧ״̬	
#define	MADD_FP5_LOS	508	//	���5�źŶ�ʧ״̬	
#define	MADD_FP6_LOS	509	//	���6�źŶ�ʧ״̬	
#define	MADD_FP7_LOS	510	//	���7�źŶ�ʧ״̬	
#define	MADD_FP8_LOS	511	//	���8�źŶ�ʧ״̬	
#define	MADD_FP9_LOS	512	//	���9�źŶ�ʧ״̬
#define	MADD_FP10_LOS	513	//	���10�źŶ�ʧ״̬
#define	MADD_FP11_LOS	514	//	���11�źŶ�ʧ״̬
#define	MADD_FP12_LOS	515	//	���12�źŶ�ʧ״̬
#define	MADD_FP13_LOS	516	//	���13�źŶ�ʧ״̬
#define	MADD_FP14_LOS	517	//	���14�źŶ�ʧ״̬
#define	MADD_FP15_LOS	518	//	���15�źŶ�ʧ״̬
#define	MADD_FP16_LOS	519	//	���16�źŶ�ʧ״̬
#define	MADD_FP1_LOF	520	//	���1֡��ʧ״̬
#define	MADD_FP2_LOF	521	//	���2֡��ʧ״̬
#define	MADD_FP3_LOF	522	//	���3֡��ʧ״̬
#define	MADD_FP4_LOF	523	//	���4֡��ʧ״̬
#define	MADD_FP5_LOF	524	//	���5֡��ʧ״̬
#define	MADD_FP6_LOF	525	//	���6֡��ʧ״̬
#define	MADD_FP7_LOF	526	//	���7֡��ʧ״̬
#define	MADD_FP8_LOF	527	//	���8֡��ʧ״̬
#define	MADD_FP9_LOF	528	//	���9֡��ʧ״̬
#define	MADD_FP10_LOF	529	//	���10֡��ʧ״̬
#define	MADD_FP11_LOF	530	//	���11֡��ʧ״̬
#define	MADD_FP12_LOF	531	//	���12֡��ʧ״̬
#define	MADD_FP13_LOF	532	//	���13֡��ʧ״̬
#define	MADD_FP14_LOF	533	//	���14֡��ʧ״̬
#define	MADD_FP15_LOF	534	//	���15֡��ʧ״̬
#define	MADD_FP16_LOF	535	//	���16֡��ʧ״̬
#define	MADD_OPT_LOF	536	//	֡��ʧ״̬
#define	MADD_SERDES1_PLL_ST	537	//	SerDesоƬPLL״̬1
#define	MADD_SERDES2_PLL_ST	538	//	SerDesоƬPLL״̬2
#define	MADD_SERDES3_PLL_ST	539	//	SerDesоƬPLL״̬3
#define	MADD_SERDES4_PLL_ST	540	//	SerDesоƬPLL״̬4
#define	MADD_SERDES5_PLL_ST	541	//	SerDesоƬPLL״̬5
#define	MADD_SERDES6_PLL_ST	542	//	SerDesоƬPLL״̬6
#define	MADD_SERDES7_PLL_ST	543	//	SerDesоƬPLL״̬7
#define	MADD_SERDES8_PLL_ST	544	//	SerDesоƬPLL״̬8
#define	MADD_SERDES9_PLL_ST	545	//	SerDesоƬPLL״̬9
#define	MADD_SERDES10_PLL_ST	546	//	SerDesоƬPLL״̬10
#define	MADD_SERDES11_PLL_ST	547	//	SerDesоƬPLL״̬11
#define	MADD_SERDES12_PLL_ST	548	//	SerDesоƬPLL״̬12
#define	MADD_SERDES13_PLL_ST	549	//	SerDesоƬPLL״̬13
#define	MADD_SERDES14_PLL_ST	550	//	SerDesоƬPLL״̬14
#define	MADD_SERDES15_PLL_ST	551	//	SerDesоƬPLL״̬15
#define	MADD_SERDES16_PLL_ST	552	//	SerDesоƬPLL״̬16
#define	MADD_TOPO_CHG_ALM	553	//	��·״̬�澯
#define	MADD_BER_ALARM	554	//	������ƫ�߸澯
#define	MADD_LOAD_FPGA_ST	555	//	����FPGA״̬
#define	MADD_FPGA_CLK_ST	556	//	FPGA����״̬
#define	MADD_INIT_CLK_ST	557	//	��ʼ��ʱ��״̬
#define	MADD_INIT_AD_ST	558	//	��ʼ��AD״̬
#define	MADD_INIT_FB_AD_ST	559	//	��ʼ������AD״̬
#define	MADD_CLK_PLL_ST	560	//	CLK	PLL״̬		
#define	MADD_CLK_REF_ST	561	//	CLK	�ο�״̬		
#define	MADD_RE_NODE_MODE	562	//	RE�ڵ�ģʽ:0-δ����,1-����ĩ��,2-�����м�,3-����ĩ��,4-�����м�			
#define	MADD_BOARD_TEMP	563	//	�����¶�			
#define	MADD_CLK_VCO_VT	564	//	ʱ��VCO��ѹ			
#define	MADD_PWR_9V0_VT	565	//	9V��Դ��ѹ			
#define	MADD_PWR_5V5_VT	566	//	5.5V��Դ��ѹ			
#define	MADD_PWR_3V6_VT	567	//	3.6V��Դ��ѹ			
#define	MADD_PWR_1V2_VT	568	//	1.2V��Դ��ѹ			
#define	MADD_PWR_2V5_VT	569	//	1.2V��Դ��ѹ			
#define	MADD_PRI_PROTOCAL_V	570	//	Э��汾			
#define	MADD_MODULE_HRI_ID	571	//	ID			
#define	MADD_WORK_ERROR	572	//	ϵͳ����״̬��1-�й���			
#define	MADD_TRAFFIC_END	573	//	������ͳ�ƽ�����־,	���˰汾ÿ��ͳ�������+1,�����ͻ�ͳ�������1		
#define	MADD_DELAY_MODE	574	//		��ʱģʽ:	0-�ֶ�,	1-�Զ�
#define	MADD_TD_SYNC_ST	575	//	TDͬ��״̬:	0-��ͬ����1-δͬ��		
#define	MADD_TD_WORK_MODE	576	//	[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������		
#define	MADD_TD_T0_UD	577	//	TDʱ϶0�����б�־:0-���У�1-����			
#define	MADD_TD_T1_UD	578	//	TDʱ϶1�����б�־:0-���У�1-����			
#define	MADD_TD_T2_UD	579	//	TDʱ϶2�����б�־:0-���У�1-����			
#define	MADD_TD_T3_UD	580	//	TDʱ϶3�����б�־:0-���У�1-����			
#define	MADD_TD_T4_UD	581	//	TDʱ϶4�����б�־:0-���У�1-����			
#define	MADD_TD_T5_UD	582	//	TDʱ϶5�����б�־:0-���У�1-����			
#define	MADD_TD_T6_UD	583	//	TDʱ϶6�����б�־:0-���У�1-����			
#define	MADD_POWERUP_ST	584	//		���ְ��ϵ�״̬,ÿ������ʱ��һ		
#define	MADD_LOW_POWER	585	//	�͹���ģʽ:1-�͹���;	0-����		
#define	MADD_THR_PORT	586	//		͸���˿�ѡ��0-485B,	1-RS232	
#define	MADD_THR_BAUD	587	//	͸���˿ڲ�����	0-9600,	1-19200,	2-38400,
#define	MADD_CTRL_BAUD	588	//	���ƶ˿ڲ�����	0-9600,	1-19200,	2-38400,
#define	MADD_WLAN_CONN_ST1	589	//	WLAN��״̬1:	0-������1-�쳣		
#define	MADD_WLAN_CONN_ST2	590	//	WLAN��״̬2:	0-������1-�쳣		
#define	MADD_WLAN_CONN_ST3	591	//	WLAN��״̬3:	0-������1-�쳣		
#define	MADD_WLAN_CONN_ST4	592	//	WLAN��״̬4:	0-������1-�쳣		
#define	MADD_WLAN_SPEED1	593	//	WLAN���ٶ�1:	0��10M		1��100M
#define	MADD_WLAN_SPEED2	594	//	WLAN���ٶ�1:	0��10M		1��100M
#define	MADD_WLAN_SPEED3	595	//	WLAN���ٶ�1:	0��10M		1��100M
#define	MADD_WLAN_SPEED4	596	//	WLAN���ٶ�1:	0��10M		1��100M
#define	MADD_GSM_BW_SEL	597	//	����汾GSM����ѡ��:	0-6M,	1-20M,	2-24M,
#define	MADD_HX_DET_UADDR	598	//	����DETģ�����е�ַ,	��4λΪB��,	����λΪA��	
#define	MADD_HX_LNA_UADDR	599	//	����LNAģ�����е�ַ,	��4λΪB��,	����λΪA��	
#define	MADD_HX_DET_DADDR	600	//	����DETģ�����е�ַ,	��4λΪB��,	����λΪA��	
#define	MADD_HX_LNA_DADDR	601	//	����LNAģ�����е�ַ,	��4λΪB��,	����λΪA��	
#define	MADD_FPS_AUTO_SCAN	602	//	�Զ�Ƶ����������ʹ��:1-�Զ�����������Ƶ��,	0-�ֶ�����		
#define	MADD_FPS_SWITCH_THD	603	//	�Զ�Ƶ��������BCCH�����л�����			
#define	MADD_FPS_MOSVC_SEL	604	//	Ƶ������:	��Ӫ��ѡ��:	0-���ƶ�,	1-����ͨ,
#define	MADD_FPS_RFRANGE_SEL	605	//	Ƶ������:	Ƶ��ѡ��(����,��ģ����ʽΪ׼):	0-ȫƵ��,	1-900MHz,
#define	MADD_FPS_BS_ID	606	//	Ƶ������:	��վʶ����		
#define	MADD_FPS_CA_COUNT	607	//	Ƶ������:	��Ч�ŵ���		
#define	MADD_FPS_BCCH_LK_ST	608	//	Ƶ������:	����BCCH״̬:	1-����,	0-ʧ��
#define	MADD_FPS_MOSVC_LK_ST	609	//	Ƶ������:	������Ӫ��״̬:	1-����,	0-ʧ��
#define	MADD_FPS_RFRANGE_LK_ST	610	//	Ƶ������:	����Ƶ��״̬:	1-����,	0-ʧ��
#define	MADD_FPS_BCCH_POW_M	611	//	Ƶ������:	��С��BCCH����ǿ��		
#define	MADD_FPS_BCCH_POW_1	612	//	Ƶ������:	��С��1BCCH����ǿ��		
#define	MADD_FPS_BCCH_POW_2	613	//	Ƶ������:	��С��2BCCH����ǿ��		
#define	MADD_FPS_BCCH_POW_3	614	//	Ƶ������:	��С��3BCCH����ǿ��		
#define	MADD_FPS_BCCH_POW_4	615	//	Ƶ������:	��С��4BCCH����ǿ��		
#define	MADD_FPS_BCCH_POW_5	616	//	Ƶ������:	��С��5BCCH����ǿ��		
#define	MADD_FPS_BCCH_POW_6	617	//	Ƶ������:	��С��6BCCH����ǿ��		
#define	MADD_A_EXPA_WORK_EN	618	//	[WR]΢����:	��Ƶ�źſ���		
#define	MADD_A_EXPA_DL_ATT	619	//	[WR]΢����:	����˥��ֵ		
#define	MADD_A_EXPA_TEMP	620	//	[RO]΢����:	�¶�		
#define	MADD_A_EXPA_DL_POW	621	//	[RO]΢����:	����������ʵ�ƽ		
#define	MADD_A_EXPA_SWR	622	//	[RO]΢����:	����פ����ֵ,x100����2λС������󲻳���1.5		
#define	MADD_A_EXPA_POWER_DN	623	//	[RO]΢����:	��Դ����澯(3���Ӹ����ж�)		
#define	MADD_A_EXPA_POWER_ERR	624	//	[RO]΢����:	��Դ���ϸ澯(3���Ӹ����ж�)	
#define	MADD_A_EXPA_BATT_ERR	625	//	[RO]΢����:	���ģ���ع��ϸ澯(3���Ӹ����ж�)	
#define	MADD_A_EXPA_POS_ALM	626	//	[RO]΢����:	λ�ø澯	
#define	MADD_A_EXPA_DOOR_ALM	627	//	[RO]΢����:	�Ž��澯	
#define	MADD_A_EXPA_WROK_ALM	628	//	[RO]΢����:	���й��Ź��ϸ澯(3���Ӹ����ж�)	
#define	MADD_A_EXPA_EXT1_ALM	629	//	[RO]΢����:	�ⲿ�澯1	
#define	MADD_A_EXPA_EXT2_ALM	630	//	[RO]΢����:	�ⲿ�澯2	
#define	MADD_A_EXPA_EXT3_ALM	631	//	[RO]΢����:	�ⲿ�澯3	
#define	MADD_A_EXPA_MAX_GAIN	632	//	΢����:	��˥�����棬���������	
#define	MADD_A_EXPA_GAIN_THD	633	//	΢����:	�������ޣ������������������ֵ	
#define	MADD_A_EXPA_POW_THD	634	//	΢����:	���������������	
#define	MADD_A_EXPA_POD_CMP	635	//	΢����:	�첨�ܹ��ʼ�ⲹ��ֵ,1�ֽ��з�����,���չ���Ϊ�첨�ܹ��ʼ��ϲ���ֵ	
#define	MADD_MONITOR_VOL_OVER_THR 		636			 // ��ص�ѹ������
#define 	MADD_MONITOR_VOL_OWE_THR 		637			 // ��ص�ѹǷ����
#define 	MADD_DIGITAL_SINGNAL_ALARM 		638			 // �����ź��쳣�澯
#define 	MADD_HOST_DEVICE_LINK_SINGNAL_ALARM 		639			 // ���Ӽ����·�澯
#define 	MADD_MONITOR_BATTERY_ALARM 		640			 // ���ģ���ع��ϸ澯	
#define 	MADD_LOW_POWER_ALARM 		641			 // ��Դ����澯	
#define 	MADD_BATTERY_BREAKDOWN_ALARM 		642			 // ��Դ���ϸ澯	
#define 	MADD_POSITION_MOVE_ALARM		643			 // λ�ø澯	
#define 	MADD_A_INPUT_OVER_DPOW_THR_ALARM 		644			 // A������������ʸ澯	
#define 	MADD_A_INPUT_OWE_DPOW_THR_ALARM 		645			 // A��������Ƿ���ʸ澯	
#define 	MADD_B_INPUT_OVER_DPOW_THR_ALARM 		646	// A������������ʸ澯			
#define 	MADD_B_INPUT_OWE_DPOW_THR_ALARM 		647	// A��������Ƿ���ʸ澯			
#define 	MADD_C_INPUT_OVER_DPOW_THR_ALARM 		648	//248			 // A������������ʸ澯
#define 	MADD_C_INPUT_OWE_DPOW_THR_ALARM 		649	//249			 // A��������Ƿ���ʸ澯
#define 	MADD_D_INPUT_OVER_DPOW_THR_ALARM		650	//248			 // A������������ʸ澯
#define 	MADD_D_INPUT_OWE_DPOW_THR_ALARM		651	//339	//249		
#define 	MADD_TD_D_OVER_SLOT1_THR_ALARM 		652			 // TD�������뵼Ƶ�����ʸ澯	
#define 	MADD_TD_D_OWE_SLOT1_THR_ALARM 		653			 // TD�������뵼ƵǷ���ʸ澯	
#define	MADD_RE_DATA_LAN_ST1	654	//	PHYоƬ����״̬		0:00	������1:
#define	MADD_RE_CASCADE_LAN_ST1	655	//	�������ڵĹ���״̬		0:00	������1:
#define	MADD_RE_DATA_LAN_SYS_ST1	656	//	��������ͬ��״̬		0:00	ͬ����1:
#define	MADD_RE_CASCADE_LAN_SYS_ST1	657	//	��������ͬ��״̬		0:00	ͬ����1:
#define	MADD_A_RF_POW_SWR	658	//	A�θ��ǵ�Ԫ����פ����			
#define	MADD_A_RF_OUT_POW_H_THR 	659	//	A�θ��ǵ�Ԫ�������������			
#define	MADD_A_RF_OUT_POW_L_THR 	660	//	A�θ��ǵ�Ԫ���Ƿ��������			
#define	MADD_B_RF_POW_SWR	661	 //	B�θ��ǵ�Ԫ����פ����			
#define	MADD_B_RF_OUT_POW_H_THR 	662	 //	B�θ��ǵ�Ԫ�������������			
#define	MADD_B_RF_OUT_POW_L_THR 	663	 //	B�θ��ǵ�Ԫ���Ƿ��������			
#define	MADD_C_RF_POW_SWR	664	//	A�θ��ǵ�Ԫ����פ����			
#define	MADD_C_RF_OUT_POW_H_THR 	665	//	A�θ��ǵ�Ԫ�������������			
#define	MADD_C_RF_OUT_POW_L_THR 	666	//	A�θ��ǵ�Ԫ���Ƿ��������			
#define	MADD_D_RF_POW_SWR	667	 // 	D�θ��ǵ�Ԫ����פ����			
#define	MADD_D_RF_OUT_POW_H_THR 	668	 // 	D�θ��ǵ�Ԫ�������������			
#define	MADD_D_RF_OUT_POW_L_THR 	669	 // 	D�θ��ǵ�Ԫ���Ƿ��������			
#define	MADD_PWR_3V3_1_VT	670		//	3.3V��Դ��ѹ		
#define	MADD_PWR_3V3_2_VT	671		//	3.3V��Դ��ѹ		
#define	MADD_PWR_1V8_VT	672			//	1.8V��Դ��ѹ	
#define	MADD_PWR_1V5_VT	673				//	1.5V��Դ��ѹ
#define	MADD_A_DL_RF_EN 	674	// 	A��������Ƶʹ��	
#define	MADD_A_UL_RF_EN 	675	// 	A��������Ƶʹ��	
#define	MADD_B_DL_RF_EN 	676	// 	B��������Ƶʹ��	
#define	MADD_B_UL_RF_EN 	677	// 	B��������Ƶʹ��	
#define	MADD_C_DL_RF_EN 	678	// 	C��������Ƶʹ��	
#define	MADD_C_UL_RF_EN 	679	// 	C��������Ƶʹ��	
#define	MADD_D_DL_RF_EN 	680	// 	D��������Ƶʹ��	
#define	MADD_D_UL_RF_EN 	681	// 	D��������Ƶʹ��
#define	MADD_METER_OFFSET	682				//	����ƫ��ֵ����
#define	MADD_METER_OFFSET_B	683				//	����ƫ��ֵ����
#define	MADD_METER_OFFSET_C	684				//	����ƫ��ֵ����
#define	MADD_METER_OFFSET_D	685				//	����ƫ��ֵ����
#define	MADD_C_TD_TYPE_SELECT	686	// TD_TLEʱ϶���				
#define	MADD_C_TD_NORMAL_CP	687		//	TDD����ʱ϶ NORMAL_CP		
#define	MADD_C_TD_EXTENDED_CP	688		//	TDD����ʱ϶ NORMAL_CP		
#define	MADD_C_TD_SYNC_ST	689	//	TDͬ��״̬:	0-��ͬ����1-δͬ��		
#define	MADD_C_TD_WORK_MODE	690	//	[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������		
#define	MADD_C_TD_DL_OVER_SLOT1_THR_ALARM	691	// TD�������뵼Ƶ�����ʸ澯				
#define	MADD_C_TD_DL_OWE_SLOT1_THR_ALARM	692	 // TD�������뵼ƵǷ���ʸ澯				
#define	MADD_D_TD_TYPE_SELECT	693	// TD_TLEʱ϶���				
#define	MADD_D_TD_NORMAL_CP	694	//718	//	TDD����ʱ϶ NORMAL_CP		
#define	MADD_D_TD_EXTENDED_CP	695	//719	//	TDD����ʱ϶ NORMAL_CP		
#define	MADD_D_TD_SYNC_ST	696	//	TDͬ��״̬:	0-��ͬ����1-δͬ��		
#define	MADD_D_TD_WORK_MODE	697	//	[WR]TD:TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���,	ÿ���ϵ������		
#define	MADD_D_TD_DL_OVER_SLOT1_THR_ALARM	698	// TD�������뵼Ƶ�����ʸ澯				
#define	MADD_D_TD_DL_OWE_SLOT1_THR_ALARM	699	 // TD�������뵼ƵǷ���ʸ澯				
#define	MADD_C_TD_T0_UD	700		//	TDʱ϶0�����б�־:0-���У�1-����		
#define	MADD_C_TD_T1_UD	701		//	TDʱ϶1�����б�־:0-���У�1-����		
#define	MADD_C_TD_T2_UD	702		//	TDʱ϶2�����б�־:0-���У�1-����		
#define	MADD_C_TD_T3_UD	703		//	TDʱ϶3�����б�־:0-���У�1-����		
#define	MADD_C_TD_T4_UD	704		//	TDʱ϶4�����б�־:0-���У�1-����		
#define	MADD_C_TD_T5_UD	705		//	TDʱ϶5�����б�־:0-���У�1-����		
#define	MADD_C_TD_T6_UD	706		//	TDʱ϶6�����б�־:0-���У�1-����		
#define	MADD_C_TD_T7_UD	707		//	TDʱ϶7�����б�־:0-���У�1-����		
#define	MADD_C_TD_T8_UD	708		//	TDʱ϶8�����б�־:0-���У�1-����		
#define	MADD_C_TD_T9_UD	709		//	TDʱ϶9�����б�־:0-���У�1-����		
#define	MADD_D_TD_T0_UD	710		//	TDʱ϶0�����б�־:0-���У�1-����		
#define	MADD_D_TD_T1_UD	711		//	TDʱ϶1�����б�־:0-���У�1-����		
#define	MADD_D_TD_T2_UD	712		//	TDʱ϶2�����б�־:0-���У�1-����		
#define	MADD_D_TD_T3_UD	713		//	TDʱ϶3�����б�־:0-���У�1-����		
#define	MADD_D_TD_T4_UD	714		//	TDʱ϶4�����б�־:0-���У�1-����		
#define	MADD_D_TD_T5_UD	715		//	TDʱ϶5�����б�־:0-���У�1-����		
#define	MADD_D_TD_T6_UD	716		//	TDʱ϶6�����б�־:0-���У�1-����		
#define	MADD_D_TD_T7_UD	717		//	TDʱ϶7�����б�־:0-���У�1-����		
#define	MADD_D_TD_T8_UD	718		//	TDʱ϶8�����б�־:0-���У�1-����		
#define	MADD_D_TD_T9_UD	719		//	TDʱ϶9�����б�־:0-���У�1-����		
#define	MADD_NOISE_TEST_EN	720		//	�������Կ���		
#define	MADD_FREQ_MODIF_VAL_D	721		//	��������
#define	MADD_FREQ_MODIF_VAL_B	722		//	��������
#define	MADD_FREQ_MODIF_VAL_A	723		//	��������
#define	MADD_B_TDS_2TH_BREAKING_POINT_SET	724		//	TDS �ڶ�ת��������ȡֵ[1��5]
#define	MADD_DELAY_MODE_A				725	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define	MADD_DELAY_MODE_B				726	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define	MADD_DELAY_MODE_C				727	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define	MADD_DELAY_MODE_D				728	// 	��ʱģʽ: 0-�ֶ�, 1-�Զ�
#define	MADD_REE_CIRCUIT_ALARM	 		729
#define	MADD_REE_WLAN_CONN_ST			730
#define	MADD_DL_POWER_MAX				731//������ģ�鹦�����ֵ	
#define 	MADD_SLOT_TIME_EN_B				732	// ʱ϶����Զ���⿪��		
#define 	MADD_SLOT_TIME_DISTRI_B			733	// ʱ϶��ȷֲ�			
#define 	MADD_VERSION_FLAG				734	// �汾��ʶʶ��
#define 	MADD_SLOT_TIME_EN_C				735	// ʱ϶����Զ���⿪��		
#define 	MADD_SLOT_TIME_DISTRI_C			736	// TD-LTEʱ϶���״̬ D3-0:������֡��� TDL_SP_SubFrm_CFG_check  ����15ʱ��ʾ���ʧ��	D7-4:������ʱ϶��� TDL_TS_EN_check  ����15ʱ��ʾ���ʧ��			
#define 	MADD_A_1197_LOCK_ST 	737	// 	A��1197����״̬,
#define 	MADD_A_IF_ST 	738	// 	A����ƵƵ��,0/1---300M/500M
#define 	MADD_ENCRYPTION_ST 	739	// 	����״̬,0/1---������/����
#define	MADD_PWR_1V6_VT			740				//	1.6V��Դ��ѹ
#define	MADD_A_90_VALUE			741				//A��9363 90�Ĵ�����ֵ
#define	MADD_A_91_VALUE			742				//A��9363 91�Ĵ�����ֵ
#define	MADD_A_94_VALUE			743				//A��9363 94�Ĵ�����ֵ
#define	MADD_A_95_VALUE			744				//A��9363 95�Ĵ�����ֵ
#define	MADD_B_90_VALUE			745				//B��9363 90�Ĵ�����ֵ
#define	MADD_B_91_VALUE			746				//B��9363 91�Ĵ�����ֵ
#define	MADD_B_94_VALUE			747				//B��9363 94�Ĵ�����ֵ
#define	MADD_B_95_VALUE			748				//B��9363 95�Ĵ�����ֵ
#define	MADD_C_90_VALUE			749				//C��9363 90�Ĵ�����ֵ
#define	MADD_C_91_VALUE			750				//C��9363 91�Ĵ�����ֵ
#define	MADD_C_94_VALUE			751				//C��9363 94�Ĵ�����ֵ
#define	MADD_C_95_VALUE			752				//C��9363 95�Ĵ�����ֵ
#define	MADD_D_90_VALUE			753				//D��9363 90�Ĵ�����ֵ
#define	MADD_D_91_VALUE			754				//D��9363 91�Ĵ�����ֵ
#define	MADD_D_94_VALUE			755				//D��9363 94�Ĵ�����ֵ
#define	MADD_D_95_VALUE			756				//D��9363 95�Ĵ�����ֵ
#define	MADD_PASSTHROUGH_EN		757				//͸��ʹ��
#define	MADD_A_DL_POW_ADJ		758				//���ʵ���             
#define	MADD_B_DL_POW_ADJ		759				//���ʵ���             
#define	MADD_C_DL_POW_ADJ		760				//���ʵ���             
#define	MADD_D_DL_POW_ADJ		761				//���ʵ���             
#define	MADD_SoftwareLoadTimes	762				//�������������ÿ���ϵ��һ
#define	MADD_A_LNA_EN_ST 		763	           		 // 	A�����е����LNA����

#define SYS_PARAM_1B_COUNT		764


#if defined ( CLIENT_JIZHUN)
	// ���˲���
	// ������ַ����==================================================== 2b
#define	PARA_A_DL_CHANNEL1	0x0900	//	A�������ŵ���1
#define	PARA_A_DL_CHANNEL2	0x0901	//	A�������ŵ���2
#define	PARA_A_DL_CHANNEL3	0x0902	//	A�������ŵ���3
#define	PARA_A_DL_CHANNEL4	0x0903	//	A�������ŵ���4
#define	PARA_A_DL_CHANNEL5	0x0904	//	A�������ŵ���5
#define	PARA_A_DL_CHANNEL6	0x0905	//	A�������ŵ���6
#define	PARA_A_DL_CHANNEL7	0x0906	//	A�������ŵ���7
#define	PARA_A_DL_CHANNEL8	0x0907	//	A�������ŵ���8
#define	PARA_A_DL_CHANNEL9	0x0908	//	A�������ŵ���9
#define	PARA_A_DL_CHANNEL10	0x0909	//	A�������ŵ���10
#define	PARA_A_DL_CHANNEL11	0x090A	//	A�������ŵ���11
#define	PARA_A_DL_CHANNEL12	0x090B	//	A�������ŵ���12
#define	PARA_A_DL_CHANNEL13	0x090C	//	A�������ŵ���13
#define	PARA_A_DL_CHANNEL14	0x090D	//	A�������ŵ���14
#define	PARA_A_DL_CHANNEL15	0x090E	//	A�������ŵ���15
#define	PARA_A_DL_CHANNEL16	0x090F	//	A�������ŵ���16
#define	PARA_A_UL_CHANNEL1	0x0900	//	A�������ŵ���1
#define	PARA_A_UL_CHANNEL2	0x0901	//	A�������ŵ���2
#define	PARA_A_UL_CHANNEL3	0x0902	//	A�������ŵ���3
#define	PARA_A_UL_CHANNEL4	0x0903	//	A�������ŵ���4
#define	PARA_A_UL_CHANNEL5	0x0904	//	A�������ŵ���5
#define	PARA_A_UL_CHANNEL6	0x0905	//	A�������ŵ���6
#define	PARA_A_UL_CHANNEL7	0x0906	//	A�������ŵ���7
#define	PARA_A_UL_CHANNEL8	0x0907	//	A�������ŵ���8
#define	PARA_A_UL_CHANNEL9	0x0908	//	A�������ŵ���9
#define	PARA_A_UL_CHANNEL10	0x0909	//	A�������ŵ���10
#define	PARA_A_UL_CHANNEL11	0x090A	//	A�������ŵ���11
#define	PARA_A_UL_CHANNEL12	0x090B	//	A�������ŵ���12
#define	PARA_A_UL_CHANNEL13	0x090C	//	A�������ŵ���13
#define	PARA_A_UL_CHANNEL14	0x090D	//	A�������ŵ���14
#define	PARA_A_UL_CHANNEL15	0x090E	//	A�������ŵ���15
#define	PARA_A_UL_CHANNEL16	0x090F	//	A�������ŵ���16
#define	PARA_A_DCH_MAX_POW1	0x0348	//	A������ͨ������������1
#define	PARA_A_DCH_MAX_POW2	0	//	A������ͨ������������2
#define	PARA_A_DCH_MAX_POW3	0	//	A������ͨ������������3
#define	PARA_A_DCH_MAX_POW4	0	//	A������ͨ������������4
#define	PARA_A_DCH_MAX_POW5	0	//	A������ͨ������������5
#define	PARA_A_DCH_MAX_POW6	0	//	A������ͨ������������6
#define	PARA_A_DCH_MAX_POW7	0	//	A������ͨ������������7
#define	PARA_A_DCH_MAX_POW8	0	//	A������ͨ������������8
#define	PARA_A_DCH_MAX_POW9	0	//	A������ͨ������������9
#define	PARA_A_DCH_MAX_POW10	0	//	A������ͨ������������10
#define	PARA_A_DCH_MAX_POW11	0	//	A������ͨ������������11
#define	PARA_A_DCH_MAX_POW12	0	//	A������ͨ������������12
#define	PARA_A_DCH_MAX_POW13	0	//	A������ͨ������������13
#define	PARA_A_DCH_MAX_POW14	0	//	A������ͨ������������14
#define	PARA_A_DCH_MAX_POW15	0	//	A������ͨ������������15
#define	PARA_A_DCH_MAX_POW16	0	//	A������ͨ������������16
#define	PARA_A_UCH_MAX_POW1		0x0340	//	A������ͨ��������빦��1
#define	PARA_A_UCH_MAX_POW2		0x8269	//	A������ͨ��������빦��2
#define	PARA_A_UCH_MAX_POW3	0	//	A������ͨ��������빦��3
#define	PARA_A_UCH_MAX_POW4	0	//	A������ͨ��������빦��4
#define	PARA_A_UCH_MAX_POW5	0	//	A������ͨ��������빦��5
#define	PARA_A_UCH_MAX_POW6	0	//	A������ͨ��������빦��6
#define	PARA_A_UCH_MAX_POW7	0	//	A������ͨ��������빦��7
#define	PARA_A_UCH_MAX_POW8	0	//	A������ͨ��������빦��8
#define	PARA_A_UCH_MAX_POW9	0	//	A������ͨ��������빦��9
#define	PARA_A_UCH_MAX_POW10	0	//	A������ͨ��������빦��10
#define	PARA_A_UCH_MAX_POW11	0	//	A������ͨ��������빦��11
#define	PARA_A_UCH_MAX_POW12	0	//	A������ͨ��������빦��12
#define	PARA_A_UCH_MAX_POW13	0	//	A������ͨ��������빦��13
#define	PARA_A_UCH_MAX_POW14	0	//	A������ͨ��������빦��14
#define	PARA_A_UCH_MAX_POW15	0	//	A������ͨ��������빦��15
#define	PARA_A_UCH_MAX_POW16	0	//	A������ͨ��������빦��16
#define	PARA_A_DCH_POW1	0	//	A��ѡƵͨ�����й���1
#define	PARA_A_DCH_POW2	0	//	A��ѡƵͨ�����й���2
#define	PARA_A_DCH_POW3	0	//	A��ѡƵͨ�����й���3
#define	PARA_A_DCH_POW4	0	//	A��ѡƵͨ�����й���4
#define	PARA_A_DCH_POW5	0	//	A��ѡƵͨ�����й���5
#define	PARA_A_DCH_POW6	0	//	A��ѡƵͨ�����й���6
#define	PARA_A_DCH_POW7	0	//	A��ѡƵͨ�����й���7
#define	PARA_A_DCH_POW8	0	//	A��ѡƵͨ�����й���8
#define	PARA_A_DCH_POW9	0	//	A��ѡƵͨ�����й���9
#define	PARA_A_DCH_POW10	0	//	A��ѡƵͨ�����й���10
#define	PARA_A_DCH_POW11	0	//	A��ѡƵͨ�����й���11
#define	PARA_A_DCH_POW12	0	//	A��ѡƵͨ�����й���12
#define	PARA_A_DCH_POW13	0	//	A��ѡƵͨ�����й���13
#define	PARA_A_DCH_POW14	0	//	A��ѡƵͨ�����й���14
#define	PARA_A_DCH_POW15	0	//	A��ѡƵͨ�����й���15
#define	PARA_A_DCH_POW16	0	//	A��ѡƵͨ�����й���16
#define	PARA_A_UCH_POW1	0	//	A��ѡƵͨ�����й���1
#define	PARA_A_UCH_POW2	0	//	A��ѡƵͨ�����й���2
#define	PARA_A_UCH_POW3	0	//	A��ѡƵͨ�����й���3
#define	PARA_A_UCH_POW4	0	//	A��ѡƵͨ�����й���4
#define	PARA_A_UCH_POW5	0	//	A��ѡƵͨ�����й���5
#define	PARA_A_UCH_POW6	0	//	A��ѡƵͨ�����й���6
#define	PARA_A_UCH_POW7	0	//	A��ѡƵͨ�����й���7
#define	PARA_A_UCH_POW8	0	//	A��ѡƵͨ�����й���8
#define	PARA_A_UCH_POW9	0	//	A��ѡƵͨ�����й���9
#define	PARA_A_UCH_POW10	0	//	A��ѡƵͨ�����й���10
#define	PARA_A_UCH_POW11	0	//	A��ѡƵͨ�����й���11
#define	PARA_A_UCH_POW12	0	//	A��ѡƵͨ�����й���12
#define	PARA_A_UCH_POW13	0	//	A��ѡƵͨ�����й���13
#define	PARA_A_UCH_POW14	0	//	A��ѡƵͨ�����й���14
#define	PARA_A_UCH_POW15	0	//	A��ѡƵͨ�����й���15
#define	PARA_A_UCH_POW16	0	//	A��ѡƵͨ�����й���16
#define	PARA_A_UDPX_IN_GAIN		0x08AB	//	A����������˫��������
#define	PARA_A_UDPX_OUT_GAIN	0x08AA	//	A���������˫��������
#define	PARA_A_DL_TOTAL_POW	0x8390	//	A�����������ܹ���
#define	PARA_A_UL_TOTAL_POW	0x831e	//	A����������ܹ���
#define	PARA_A_REC_DPX_IG		0		//		REC��A������˫�������棬��������������㣬ֻ��							
#define	PARA_A_REC_DPX_OG		0		//		REC��A�����˫�������棬��������������㣬ֻ��	
#define	PARA_B_DL_CHANNEL1	0x0900	//	B�������ŵ���1
#define	PARA_B_DL_CHANNEL2	0x0901	//	B�������ŵ���2
#define	PARA_B_DL_CHANNEL3	0x0902	//	B�������ŵ���3
#define	PARA_B_DL_CHANNEL4	0x0903	//	B�������ŵ���4
#define	PARA_B_DL_CHANNEL5	0x0904	//	B�������ŵ���5
#define	PARA_B_DL_CHANNEL6	0x0905	//	B�������ŵ���6
#define	PARA_B_DL_CHANNEL7	0x0906	//	B�������ŵ���7
#define	PARA_B_DL_CHANNEL8	0x0907	//	B�������ŵ���8
#define	PARA_B_DL_CHANNEL9	0x0908	//	B�������ŵ���9
#define	PARA_B_DL_CHANNEL10	0x0909	//	B�������ŵ���10
#define	PARA_B_DL_CHANNEL11	0x090A	//	B�������ŵ���11
#define	PARA_B_DL_CHANNEL12	0x090B	//	B�������ŵ���12
#define	PARA_B_DL_CHANNEL13	0x090C	//	B�������ŵ���13
#define	PARA_B_DL_CHANNEL14	0x090D	//	B�������ŵ���14
#define	PARA_B_DL_CHANNEL15	0x090E	//	B�������ŵ���15
#define	PARA_B_DL_CHANNEL16	0x090F	//	B�������ŵ���16
#define	PARA_B_UL_CHANNEL1	0x0900	//	B�������ŵ���1
#define	PARA_B_UL_CHANNEL2	0x0901	//	B�������ŵ���2
#define	PARA_B_UL_CHANNEL3	0x0902	//	B�������ŵ���3
#define	PARA_B_UL_CHANNEL4	0x0903	//	B�������ŵ���4
#define	PARA_B_UL_CHANNEL5	0x0904	//	B�������ŵ���5
#define	PARA_B_UL_CHANNEL6	0x0905	//	B�������ŵ���6
#define	PARA_B_UL_CHANNEL7	0x0906	//	B�������ŵ���7
#define	PARA_B_UL_CHANNEL8	0x0907	//	B�������ŵ���8
#define	PARA_B_UL_CHANNEL9	0x0908	//	B�������ŵ���9
#define	PARA_B_UL_CHANNEL10	0x0909	//	B�������ŵ���10
#define	PARA_B_UL_CHANNEL11	0x090A	//	B�������ŵ���11
#define	PARA_B_UL_CHANNEL12	0x090B	//	B�������ŵ���12
#define	PARA_B_UL_CHANNEL13	0x090C	//	B�������ŵ���13
#define	PARA_B_UL_CHANNEL14	0x090D	//	B�������ŵ���14
#define	PARA_B_UL_CHANNEL15	0x090E	//	B�������ŵ���15
#define	PARA_B_UL_CHANNEL16	0x090F	//	B�������ŵ���16
#define	PARA_B_DCH_MAX_POW1	0x0348	//	B������ͨ������������1
#define	PARA_B_DCH_MAX_POW2	0	//	B������ͨ������������2
#define	PARA_B_DCH_MAX_POW3	0	//	B������ͨ������������3
#define	PARA_B_DCH_MAX_POW4	0	//	B������ͨ������������4
#define	PARA_B_DCH_MAX_POW5	0	//	B������ͨ������������5
#define	PARA_B_DCH_MAX_POW6	0	//	B������ͨ������������6
#define	PARA_B_DCH_MAX_POW7	0	//	B������ͨ������������7
#define	PARA_B_DCH_MAX_POW8	0	//	B������ͨ������������8
#define	PARA_B_DCH_MAX_POW9	0	//	B������ͨ������������9
#define	PARA_B_DCH_MAX_POW10	0	//	B������ͨ������������10
#define	PARA_B_DCH_MAX_POW11	0	//	B������ͨ������������11
#define	PARA_B_DCH_MAX_POW12	0	//	B������ͨ������������12
#define	PARA_B_DCH_MAX_POW13	0	//	B������ͨ������������13
#define	PARA_B_DCH_MAX_POW14	0	//	B������ͨ������������14
#define	PARA_B_DCH_MAX_POW15	0	//	B������ͨ������������15
#define	PARA_B_DCH_MAX_POW16	0	//	B������ͨ������������16
#define	PARA_B_UCH_MAX_POW1		0x0340	//	B������ͨ��������빦��1
#define	PARA_B_UCH_MAX_POW2		0x8269//	B������ͨ��������빦��2
#define	PARA_B_UCH_MAX_POW3	0	//	B������ͨ��������빦��3
#define	PARA_B_UCH_MAX_POW4	0	//	B������ͨ��������빦��4
#define	PARA_B_UCH_MAX_POW5	0	//	B������ͨ��������빦��5
#define	PARA_B_UCH_MAX_POW6	0	//	B������ͨ��������빦��6
#define	PARA_B_UCH_MAX_POW7	0	//	B������ͨ��������빦��7
#define	PARA_B_UCH_MAX_POW8	0	//	B������ͨ��������빦��8
#define	PARA_B_UCH_MAX_POW9	0	//	B������ͨ��������빦��9
#define	PARA_B_UCH_MAX_POW10	0	//	B������ͨ��������빦��10
#define	PARA_B_UCH_MAX_POW11	0	//	B������ͨ��������빦��11
#define	PARA_B_UCH_MAX_POW12	0	//	B������ͨ��������빦��12
#define	PARA_B_UCH_MAX_POW13	0	//	B������ͨ��������빦��13
#define	PARA_B_UCH_MAX_POW14	0	//	B������ͨ��������빦��14
#define	PARA_B_UCH_MAX_POW15	0	//	B������ͨ��������빦��15
#define	PARA_B_UCH_MAX_POW16	0	//	B������ͨ��������빦��16
#define	PARA_B_DCH_POW1	0	//	B��ѡƵͨ�����й���1
#define	PARA_B_DCH_POW2	0	//	B��ѡƵͨ�����й���2
#define	PARA_B_DCH_POW3	0	//	B��ѡƵͨ�����й���3
#define	PARA_B_DCH_POW4	0	//	B��ѡƵͨ�����й���4
#define	PARA_B_DCH_POW5	0	//	B��ѡƵͨ�����й���5
#define	PARA_B_DCH_POW6	0	//	B��ѡƵͨ�����й���6
#define	PARA_B_DCH_POW7	0	//	B��ѡƵͨ�����й���7
#define	PARA_B_DCH_POW8	0	//	B��ѡƵͨ�����й���8
#define	PARA_B_DCH_POW9	0	//	B��ѡƵͨ�����й���9
#define	PARA_B_DCH_POW10	0	//	B��ѡƵͨ�����й���10
#define	PARA_B_DCH_POW11	0	//	B��ѡƵͨ�����й���11
#define	PARA_B_DCH_POW12	0	//	B��ѡƵͨ�����й���12
#define	PARA_B_DCH_POW13	0	//	B��ѡƵͨ�����й���13
#define	PARA_B_DCH_POW14	0	//	B��ѡƵͨ�����й���14
#define	PARA_B_DCH_POW15	0	//	B��ѡƵͨ�����й���15
#define	PARA_B_DCH_POW16	0	//	B��ѡƵͨ�����й���16
#define	PARA_B_UCH_POW1	0	//	B��ѡƵͨ�����й���1
#define	PARA_B_UCH_POW2	0	//	B��ѡƵͨ�����й���2
#define	PARA_B_UCH_POW3	0	//	B��ѡƵͨ�����й���3
#define	PARA_B_UCH_POW4	0	//	B��ѡƵͨ�����й���4
#define	PARA_B_UCH_POW5	0	//	B��ѡƵͨ�����й���5
#define	PARA_B_UCH_POW6	0	//	B��ѡƵͨ�����й���6
#define	PARA_B_UCH_POW7	0	//	B��ѡƵͨ�����й���7
#define	PARA_B_UCH_POW8	0	//	B��ѡƵͨ�����й���8
#define	PARA_B_UCH_POW9	0	//	B��ѡƵͨ�����й���9
#define	PARA_B_UCH_POW10	0	//	B��ѡƵͨ�����й���10
#define	PARA_B_UCH_POW11	0	//	B��ѡƵͨ�����й���11
#define	PARA_B_UCH_POW12	0	//	B��ѡƵͨ�����й���12
#define	PARA_B_UCH_POW13	0	//	B��ѡƵͨ�����й���13
#define	PARA_B_UCH_POW14	0	//	B��ѡƵͨ�����й���14
#define	PARA_B_UCH_POW15	0	//	B��ѡƵͨ�����й���15
#define	PARA_B_UCH_POW16	0	//	B��ѡƵͨ�����й���16
#define	PARA_B_UDPX_IN_GAIN	0x08AB	//	B����������˫��������
#define	PARA_B_UDPX_OUT_GAIN	0x08AA	//	B���������˫��������
#define	PARA_B_DL_TOTAL_POW	0x8390	//	B�����������ܹ���
#define	PARA_B_UL_TOTAL_POW	0x831e	//	B����������ܹ���
#define	PARA_B_REC_DPX_IG		0		//		REC��A������˫�������棬��������������㣬ֻ��							
#define	PARA_B_REC_DPX_OG		0		//		REC��A�����˫�������棬��������������㣬ֻ��	
#define	PARA_C_DL_CHANNEL1	0x0900	//	C�������ŵ���1
#define	PARA_C_DL_CHANNEL2	0x0901	//	C�������ŵ���2
#define	PARA_C_DL_CHANNEL3	0x0902	//	C�������ŵ���3
#define	PARA_C_DL_CHANNEL4	0x0903	//	C�������ŵ���4
#define	PARA_C_DL_CHANNEL5	0x0904	//	C�������ŵ���5
#define	PARA_C_DL_CHANNEL6	0x0905	//	C�������ŵ���6
#define	PARA_C_DL_CHANNEL7	0x0906	//	C�������ŵ���7
#define	PARA_C_DL_CHANNEL8	0x0907	//	C�������ŵ���8
#define	PARA_C_DL_CHANNEL9	0x0908	//	C�������ŵ���9
#define	PARA_C_DL_CHANNEL10	0x0909	//	C�������ŵ���10
#define	PARA_C_UL_CHANNEL1	0x0900	//	C�������ŵ���1
#define	PARA_C_UL_CHANNEL2	0x0901	//	C�������ŵ���2
#define	PARA_C_UL_CHANNEL3	0x0902	//	C�������ŵ���3
#define	PARA_C_UL_CHANNEL4	0x0903	//	C�������ŵ���4
#define	PARA_C_UL_CHANNEL5	0x0904	//	C�������ŵ���5
#define	PARA_C_UL_CHANNEL6	0x0905	//	C�������ŵ���6
#define	PARA_C_UL_CHANNEL7	0x0906	//	C�������ŵ���7
#define	PARA_C_UL_CHANNEL8	0x0907	//	C�������ŵ���8
#define	PARA_C_UL_CHANNEL9	0x0908	//	C�������ŵ���9
#define	PARA_C_UL_CHANNEL10	0x0909	//	C�������ŵ���10
#define	PARA_C_DCH_MAX_POW1	0x0348	//	C������ͨ������������1
#define	PARA_C_DCH_MAX_POW2	0	//	C������ͨ������������2
#define	PARA_C_DCH_MAX_POW3	0	//	C������ͨ������������3
#define	PARA_C_DCH_MAX_POW4	0	//	C������ͨ������������4
#define	PARA_C_DCH_MAX_POW5	0	//	C������ͨ������������5
#define	PARA_C_DCH_MAX_POW6	0	//	C������ͨ������������6
#define	PARA_C_DCH_MAX_POW7	0	//	C������ͨ������������7
#define	PARA_C_DCH_MAX_POW8	0	//	C������ͨ������������8
#define	PARA_C_DCH_MAX_POW9	0	//	C������ͨ������������9
#define	PARA_C_DCH_MAX_POW10	0	//	C������ͨ������������10
#define	PARA_C_DCH_MAX_POW11	0	//	C������ͨ������������11
#define	PARA_C_DCH_MAX_POW12	0	//	C������ͨ������������12
#define	PARA_C_DCH_MAX_POW13	0	//	C������ͨ������������13
#define	PARA_C_DCH_MAX_POW14	0	//	C������ͨ������������14
#define	PARA_C_DCH_MAX_POW15	0	//	C������ͨ������������15
#define	PARA_C_DCH_MAX_POW16	0	//	C������ͨ������������16
#define	PARA_C_UCH_MAX_POW1	0x0340	//	C������ͨ��������빦��1
#define	PARA_C_UCH_MAX_POW2	0	//	C������ͨ��������빦��2
#define	PARA_C_UCH_MAX_POW3	0	//	C������ͨ��������빦��3
#define	PARA_C_UCH_MAX_POW4	0	//	C������ͨ��������빦��4
#define	PARA_C_UCH_MAX_POW5	0	//	C������ͨ��������빦��5
#define	PARA_C_UCH_MAX_POW6	0	//	C������ͨ��������빦��6
#define	PARA_C_UCH_MAX_POW7	0	//	C������ͨ��������빦��7
#define	PARA_C_UCH_MAX_POW8	0	//	C������ͨ��������빦��8
#define	PARA_C_UCH_MAX_POW9	0	//	C������ͨ��������빦��9
#define	PARA_C_UCH_MAX_POW10		0	//	C������ͨ��������빦��10
#define	PARA_C_UCH_MAX_POW11		0	//	C������ͨ��������빦��11
#define	PARA_C_UCH_MAX_POW12		0	//	C������ͨ��������빦��12
#define	PARA_C_UCH_MAX_POW13		0	//	C������ͨ��������빦��13
#define	PARA_C_UCH_MAX_POW14		0	//	C������ͨ��������빦��14
#define	PARA_C_UCH_MAX_POW15		0	//	C������ͨ��������빦��15
#define	PARA_C_UCH_MAX_POW16		0	//	C������ͨ��������빦��16
#define	PARA_C_DCH_POW1	0	//	C��ѡƵͨ�����й���1
#define	PARA_C_DCH_POW2	0	//	C��ѡƵͨ�����й���2
#define	PARA_C_DCH_POW3	0	//	C��ѡƵͨ�����й���3
#define	PARA_C_DCH_POW4	0	//	C��ѡƵͨ�����й���4
#define	PARA_C_DCH_POW5	0	//	C��ѡƵͨ�����й���5
#define	PARA_C_DCH_POW6	0	//	C��ѡƵͨ�����й���6
#define	PARA_C_DCH_POW7	0	//	C��ѡƵͨ�����й���7
#define	PARA_C_DCH_POW8	0	//	C��ѡƵͨ�����й���8
#define	PARA_C_DCH_POW9	0	//	C��ѡƵͨ�����й���9
#define	PARA_C_DCH_POW10	0	//	C��ѡƵͨ�����й���10
#define	PARA_C_DCH_POW11	0	//	C��ѡƵͨ�����й���11
#define	PARA_C_DCH_POW12	0	//	C��ѡƵͨ�����й���12
#define	PARA_C_DCH_POW13	0	//	C��ѡƵͨ�����й���13
#define	PARA_C_DCH_POW14	0	//	C��ѡƵͨ�����й���14
#define	PARA_C_DCH_POW15	0	//	C��ѡƵͨ�����й���15
#define	PARA_C_DCH_POW16	0	//	C��ѡƵͨ�����й���16
#define	PARA_C_UCH_POW1	0	//	C��ѡƵͨ�����й���1
#define	PARA_C_UCH_POW2	0	//	C��ѡƵͨ�����й���2
#define	PARA_C_UCH_POW3	0	//	C��ѡƵͨ�����й���3
#define	PARA_C_UCH_POW4	0	//	C��ѡƵͨ�����й���4
#define	PARA_C_UCH_POW5	0	//	C��ѡƵͨ�����й���5
#define	PARA_C_UCH_POW6	0	//	C��ѡƵͨ�����й���6
#define	PARA_C_UCH_POW7	0	//	C��ѡƵͨ�����й���7
#define	PARA_C_UCH_POW8	0	//	C��ѡƵͨ�����й���8
#define	PARA_C_UCH_POW9	0	//	C��ѡƵͨ�����й���9
#define	PARA_C_UCH_POW10	0	//	C��ѡƵͨ�����й���10
#define	PARA_C_UCH_POW11	0	//	C��ѡƵͨ�����й���11
#define	PARA_C_UCH_POW12	0	//	C��ѡƵͨ�����й���12
#define	PARA_C_UCH_POW13	0	//	C��ѡƵͨ�����й���13
#define	PARA_C_UCH_POW14	0	//	C��ѡƵͨ�����й���14
#define	PARA_C_UCH_POW15	0	//	C��ѡƵͨ�����й���15
#define	PARA_C_UCH_POW16	0	//	C��ѡƵͨ�����й���16
#define	PARA_C_UDPX_IN_GAIN	0x08AB	//	C����������˫��������
#define	PARA_C_UDPX_OUT_GAIN	0x08AA	//	C���������˫��������
#define	PARA_C_DL_TOTAL_POW	0x8390	//	C�����������ܹ���
#define	PARA_C_UL_TOTAL_POW	0x831e	//	C����������ܹ���
#define	PARA_C_REC_DPX_IG		0		//		REC��A������˫�������棬��������������㣬ֻ��							
#define	PARA_C_REC_DPX_OG		0		//		REC��A�����˫�������棬��������������㣬ֻ��	
#define	PARA_D_DL_CHANNEL1	0x0900	//	D�������ŵ���1
#define	PARA_D_DL_CHANNEL2	0x0901	//	D�������ŵ���2
#define	PARA_D_DL_CHANNEL3	0x0902	//	D�������ŵ���3
#define	PARA_D_DL_CHANNEL4	0x0903	//	D�������ŵ���4
#define	PARA_D_DL_CHANNEL5	0x0904	//	D�������ŵ���5
#define	PARA_D_DL_CHANNEL6	0x0905	//	D�������ŵ���6
#define	PARA_D_DL_CHANNEL7	0x0906	//	D�������ŵ���7
#define	PARA_D_DL_CHANNEL8	0x0907	//	D�������ŵ���8
#define	PARA_D_DL_CHANNEL9	0x0908	//	D�������ŵ���9
#define	PARA_D_DL_CHANNEL10	0x0909	//	D�������ŵ���10
#define	PARA_D_UL_CHANNEL1	0x0900	//	D�������ŵ���1
#define	PARA_D_UL_CHANNEL2	0x0901	//	D�������ŵ���2
#define	PARA_D_UL_CHANNEL3	0x0902	//	D�������ŵ���3
#define	PARA_D_UL_CHANNEL4	0x0903	//	D�������ŵ���4
#define	PARA_D_UL_CHANNEL5	0x0904	//	D�������ŵ���5
#define	PARA_D_UL_CHANNEL6	0x0905	//	D�������ŵ���6
#define	PARA_D_UL_CHANNEL7	0x0906	//	D�������ŵ���7
#define	PARA_D_UL_CHANNEL8	0x0907	//	D�������ŵ���8
#define	PARA_D_UL_CHANNEL9	0x0908	//	D�������ŵ���9
#define	PARA_D_UL_CHANNEL10	0x0909	//	D�������ŵ���10
#define	PARA_D_DCH_MAX_POW1	0x0348	//	D������ͨ������������1
#define	PARA_D_DCH_MAX_POW2	0	//	D������ͨ������������2
#define	PARA_D_DCH_MAX_POW3	0	//	D������ͨ������������3
#define	PARA_D_DCH_MAX_POW4	0	//	D������ͨ������������4
#define	PARA_D_DCH_MAX_POW5	0	//	D������ͨ������������5
#define	PARA_D_DCH_MAX_POW6	0	//	D������ͨ������������6
#define	PARA_D_DCH_MAX_POW7	0	//	D������ͨ������������7
#define	PARA_D_DCH_MAX_POW8	0	//	D������ͨ������������8
#define	PARA_D_DCH_MAX_POW9	0	//	D������ͨ������������9
#define	PARA_D_DCH_MAX_POW10	0	//	D������ͨ������������10
#define	PARA_D_DCH_MAX_POW11	0	//	D������ͨ������������11
#define	PARA_D_DCH_MAX_POW12	0	//	D������ͨ������������12
#define	PARA_D_DCH_MAX_POW13	0	//	D������ͨ������������13
#define	PARA_D_DCH_MAX_POW14	0	//	D������ͨ������������14
#define	PARA_D_DCH_MAX_POW15	0	//	D������ͨ������������15
#define	PARA_D_DCH_MAX_POW16	0	//	D������ͨ������������16
#define	PARA_D_UCH_MAX_POW1	0x0340	//	D������ͨ��������빦��1
#define	PARA_D_UCH_MAX_POW2	0	//	D������ͨ��������빦��2
#define	PARA_D_UCH_MAX_POW3	0	//	D������ͨ��������빦��3
#define	PARA_D_UCH_MAX_POW4	0	//	D������ͨ��������빦��4
#define	PARA_D_UCH_MAX_POW5	0	//	D������ͨ��������빦��5
#define	PARA_D_UCH_MAX_POW6	0	//	D������ͨ��������빦��6
#define	PARA_D_UCH_MAX_POW7	0	//	D������ͨ��������빦��7
#define	PARA_D_UCH_MAX_POW8	0	//	D������ͨ��������빦��8
#define	PARA_D_UCH_MAX_POW9	0	//	D������ͨ��������빦��9
#define	PARA_D_UCH_MAX_POW10	0	//	D������ͨ��������빦��10
#define	PARA_D_UCH_MAX_POW11	0	//	D������ͨ��������빦��11
#define	PARA_D_UCH_MAX_POW12	0	//	D������ͨ��������빦��12
#define	PARA_D_UCH_MAX_POW13	0	//	D������ͨ��������빦��13
#define	PARA_D_UCH_MAX_POW14	0	//	D������ͨ��������빦��14
#define	PARA_D_UCH_MAX_POW15	0	//	D������ͨ��������빦��15
#define	PARA_D_UCH_MAX_POW16	0	//	D������ͨ��������빦��16
#define	PARA_D_DCH_POW1	0	//	D��ѡƵͨ�����й���1
#define	PARA_D_DCH_POW2	0	//	D��ѡƵͨ�����й���2
#define	PARA_D_DCH_POW3	0	//	D��ѡƵͨ�����й���3
#define	PARA_D_DCH_POW4	0	//	D��ѡƵͨ�����й���4
#define	PARA_D_DCH_POW5	0	//	D��ѡƵͨ�����й���5
#define	PARA_D_DCH_POW6	0	//	D��ѡƵͨ�����й���6
#define	PARA_D_DCH_POW7	0	//	D��ѡƵͨ�����й���7
#define	PARA_D_DCH_POW8	0	//	D��ѡƵͨ�����й���8
#define	PARA_D_DCH_POW9	0	//	D��ѡƵͨ�����й���9
#define	PARA_D_DCH_POW10	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_DCH_POW11	0	//	D��ѡƵͨ�����й���11
#define	PARA_D_DCH_POW12	0	//	D��ѡƵͨ�����й���12
#define	PARA_D_DCH_POW13	0	//	D��ѡƵͨ�����й���13
#define	PARA_D_DCH_POW14	0	//	D��ѡƵͨ�����й���14
#define	PARA_D_DCH_POW15	0	//	D��ѡƵͨ�����й���15
#define	PARA_D_DCH_POW16	0	//	D��ѡƵͨ�����й���16
#define	PARA_D_UCH_POW1	0	//	D��ѡƵͨ�����й���1
#define	PARA_D_UCH_POW2	0	//	D��ѡƵͨ�����й���2
#define	PARA_D_UCH_POW3	0	//	D��ѡƵͨ�����й���3
#define	PARA_D_UCH_POW4	0	//	D��ѡƵͨ�����й���4
#define	PARA_D_UCH_POW5	0	//	D��ѡƵͨ�����й���5
#define	PARA_D_UCH_POW6	0	//	D��ѡƵͨ�����й���6
#define	PARA_D_UCH_POW7	0	//	D��ѡƵͨ�����й���7
#define	PARA_D_UCH_POW8	0	//	D��ѡƵͨ�����й���8
#define	PARA_D_UCH_POW9	0	//	D��ѡƵͨ�����й���9
#define	PARA_D_UCH_POW10	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW11	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW12	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW13	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW14	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW15	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW16	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UDPX_IN_GAIN	0x08AB	//	D����������˫��������
#define	PARA_D_UDPX_OUT_GAIN	0x08AA	//	D���������˫��������
#define	PARA_D_DL_TOTAL_POW	0x8390	//	D�����������ܹ���
#define	PARA_D_UL_TOTAL_POW	0x831e	//	D����������ܹ���
#define	PARA_D_REC_DPX_IG		0		//		REC��D������˫�������棬��������������㣬ֻ��							
#define	PARA_D_REC_DPX_OG		0		//		REC��D�����˫�������棬��������������㣬ֻ��	
#define	PARA_REC_TO_RE_DELAY		0x889e	// REC��RE�Ĺ�����ʱ
#define	PARA_RE_RF_DELAY			0x889f	// RE����Ƶ��ʱ
#define	PARA_MAX_T14	0x889c	//	��������ʱ
#define	PARA_DL_DELAY_OFFSET	0x0768	//	������ʱƫ����
#define	PARA_UL_DELAY_OFFSET	0x0769	//	������ʱƫ����
#define	PARA_PRI_SOFT_V	0xf018	//	����汾�ţ���ASCII�룩
#define	PARA_PRI_HARD_V	0xf026	//	PCB�汾��(��ASCII��)
#define	PARA_TD_1ST_CP_TIME		0x08a7	// TD��1ת����ʱ��ns, �з�����
#define	PARA_TD_2ND_CP_TIME		0x08a8	// TD��2ת����ʱ��ns, �з�����
#define	PARA_TD_LNA_ON_TIME		0x08ae	// LNA�����ٺ�DN_PA�رյı���ʱ��ns
#define	PARA_TD_LNA_OFF_TIME		0x08af	// LNA�رճ�ǰDN_PA�����ı���ʱ��ns
#define	PARA_TD_SLOT1_UPOW	0x7501	// TDʱ϶1���м�⹦��
#define	PARA_TD_SLOT2_UPOW	0x7502	// TDʱ϶2���м�⹦��
#define	PARA_TD_SLOT3_UPOW	0x7503	// TDʱ϶3���м�⹦��
#define	PARA_TD_SLOT4_UPOW	0x7504	// TDʱ϶4���м�⹦��
#define	PARA_TD_SLOT5_UPOW	0x7505	// TDʱ϶5���м�⹦��
#define	PARA_TD_SLOT6_UPOW	0x7506	// TDʱ϶6���м�⹦��
#define	PARA_TD_SLOT7_UPOW	0x7507	// TDʱ϶7���м�⹦��
#define	PARA_TD_SLOT1_DPOW	0x7511	// TDʱ϶1���м�⹦��
#define	PARA_TD_SLOT2_DPOW	0x7512	// TDʱ϶2���м�⹦��
#define	PARA_TD_SLOT3_DPOW	0x7513	// TDʱ϶3���м�⹦��
#define	PARA_TD_SLOT4_DPOW	0x7514	// TDʱ϶4���м�⹦��
#define	PARA_TD_SLOT5_DPOW	0x7515	// TDʱ϶5���м�⹦��
#define	PARA_TD_SLOT6_DPOW	0x7516	// TDʱ϶6���м�⹦��
#define	PARA_TD_SLOT7_DPOW	0x7517	// TDʱ϶7���м�⹦��
#define	PARA_FPS_S1 0 // Ƶ������: ��Χ1��ʼƵ��
#define	PARA_FPS_E1 0 // Ƶ������: ��Χ1����Ƶ��
#define	PARA_FPS_S2 0 // Ƶ������: ��Χ2��ʼƵ��
#define	PARA_FPS_E2 0 // Ƶ������: ��Χ2����Ƶ��
#define	PARA_FPS_BCCH_LK_SET	0x0923	// Ƶ������: ��Ƶ�ŵ���: ��׼�ŵ���, 65535-�˳���Ƶ
#define	PARA_FPS_CID_LK_SET	0x0926	// Ƶ������: С��ʶ����ο�ֵ, 0-�˳�С����������
#define	PARA_FPS_BCCH_FC_M	0x8940	// Ƶ������: ��С��BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_CA_FC_0	0x8941	// Ƶ������: CA�ز�0�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_1	0x8942	// Ƶ������: CA�ز�1�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_2	0x8943	// Ƶ������: CA�ز�2�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_3	0x8944	// Ƶ������: CA�ز�3�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_4	0x8945	// Ƶ������: CA�ز�4�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_5	0x8946	// Ƶ������: CA�ز�5�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_6	0x8947	// Ƶ������: CA�ز�6�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_7	0x8948	// Ƶ������: CA�ز�7�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_8	0x8949	// Ƶ������: CA�ز�8�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_9	0x894A	// Ƶ������: CA�ز�9�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_10	0x894B	// Ƶ������: CA�ز�10�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_11	0x894C	// Ƶ������: CA�ز�11�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_12	0x894D	// Ƶ������: CA�ز�12�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_13	0x894E	// Ƶ������: CA�ز�13�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_14	0x894F	// Ƶ������: CA�ز�14�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_15	0x8950	// Ƶ������: CA�ز�15�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_BCCH_FC_1	0x8951	// Ƶ������: ��С��1 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_2	0x8952	// Ƶ������: ��С��2 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_3	0x8953	// Ƶ������: ��С��3 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_4	0x8954	// Ƶ������: ��С��4 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_5	0x8955	// Ƶ������: ��С��5 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_6	0x8956	// Ƶ������: ��С��6 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_AREA_ID	0x8958	// Ƶ������: λ��������
#define	PARA_FPS_CID		0x895A	// Ƶ������: С��ʶ����ʵʱֵ
#define	PARA_FPS_CID_1 0 // Ƶ������: ��С��1 CIDС��ʶ����
#define	PARA_FPS_CID_2 0 // Ƶ������: ��С��2 CIDС��ʶ����
#define	PARA_FPS_CID_3 0 // Ƶ������: ��С��3 CIDС��ʶ����
#define	PARA_FPS_CID_4 0 // Ƶ������: ��С��4 CIDС��ʶ����
#define	PARA_FPS_CID_5 0 // Ƶ������: ��С��5 CIDС��ʶ����
#define	PARA_FPS_CID_6 0 // Ƶ������: ��С��6 CIDС��ʶ����
#define	PARA_A_EXPA_IDRAIN_SET	0	// ΢����: ©����������,mA
#define	PARA_TD_SLOT1_DPOW_OVER_THR				0x0a60       //td�������뵼Ƶ����������
#define	PARA_TD_SLOT1_DPOW_OWE_THR				0x0a61      //td�������뵼ƵǷ��������	
#define PARA_A_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //�����������������
#define PARA_A_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //��������Ƿ��������
#define PARA_B_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //�����������������
#define PARA_B_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //��������Ƿ��������
#define PARA_C_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //�����������������
#define PARA_C_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //��������Ƿ��������
#define PARA_D_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //�����������������
#define PARA_D_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //��������Ƿ��������
#define PARA_REE_A_DL_OUT_TOTAL_POW_DETECT     	0x8004      //A��RE��������ܹ���//עREC\REʹ�� MADD_A_DL_TOTAL_POW
#define PARA_A_RE_LOCAL_ST_ALARM     			0x8a33      	//���ǵ�Ԫ���ظ澯״̬
#define PARA_REE_B_DL_OUT_TOTAL_POW_DETECT     	0x8004      //B��RE��������ܹ��� //עREC\REʹ�� MADD_B_DL_TOTAL_POW
#define PARA_B_RE_LOCAL_ST_ALARM     			0x8a33      	//���ǵ�Ԫ���ظ澯״̬
#define PARA_REE_C_DL_OUT_TOTAL_POW_DETECT     	0x8004      //A��RE��������ܹ���//עREC\REʹ�� MADD_C_DL_TOTAL_POW
#define PARA_C_RE_LOCAL_ST_ALARM     			0x8a33      	//���ǵ�Ԫ���ظ澯״̬
#define PARA_REE_D_DL_OUT_TOTAL_POW_DETECT     	0x8004      //	D��RE��������ܹ��� //עREC\REʹ�� MADD_D_DL_TOTAL_POW
#define PARA_D_RE_LOCAL_ST_ALARM     			0x8a33      	//	D���ǵ�Ԫ���ظ澯״̬
#define PARA_C_TD_1ST_CP_TIME	0x08a7	//		//465		TD��1ת����ʱ��,ns,		
#define PARA_C_TD_2ND_CP_TIME	0x08a8	//		//466		TD��2ת����ʱ��,ns,		
#define PARA_C_TD_LNA_ON_TIME	0x08ae	//		//467		LNA�����ٺ�DN_PA�رյı���ʱ��ns		
#define PARA_C_TD_LNA_OFF_TIME	0x08af	//		//468		LNA�رճ�ǰDN_PA�����ı���ʱ��ns		
#define PARA_C_TD_SLOT1_DPOW_OVER_THR	0x0a60	//		//469	0	//		//5625
#define PARA_C_TD_SLOT1_DPOW_OWE_THR	0x0a61	//		//470	0	//		//5626
#define PARA_D_TD_1ST_CP_TIME	0x08a7	//		//471		TD��1ת����ʱ��,ns,		
#define PARA_D_TD_2ND_CP_TIME	0x08a7	//		//472		TD��2ת����ʱ��,ns,		
#define PARA_D_TD_LNA_ON_TIME	0x08ae	//		//473		LNA�����ٺ�DN_PA�رյı���ʱ��ns		
#define PARA_D_TD_LNA_OFF_TIME	0x08af	//		//474		LNA�رճ�ǰDN_PA�����ı���ʱ��ns		
#define PARA_D_TD_SLOT1_DPOW_OVER_THR	0x0a60	//		//475	0	//		//5625
#define PARA_D_TD_SLOT1_DPOW_OWE_THR	0x0a61	//		//476	0	//		//5626
#define PARA_C_TD_SLOT1_POW	0	//		//477		TDʱ϶1�����⹦��	
#define PARA_C_TD_SLOT2_POW	0	//		//478		TDʱ϶2�����⹦��	
#define PARA_C_TD_SLOT3_POW	0	//		//479		TDʱ϶3�����⹦��	
#define PARA_C_TD_SLOT4_POW	0	//		//480		TDʱ϶4�����⹦��	
#define PARA_C_TD_SLOT5_POW	0	//		//481		TDʱ϶5�����⹦��	
#define PARA_C_TD_SLOT6_POW	0	//		//482		TDʱ϶6�����⹦��	
#define PARA_C_TD_SLOT7_POW	0	//		//483		TDʱ϶7�����⹦��	
#define PARA_C_TD_SLOT8_POW	0	//		//484		TDʱ϶8�����⹦��	
#define PARA_C_TD_SLOT9_POW	0	//		//485		TDʱ϶9�����⹦��	
#define PARA_C_TD_SLOT10_POW	0	//		//486		TDʱ϶10�����⹦��	
#define PARA_C_TD_SLOT11_POW	0	//		//487		TDʱ϶11�����⹦��	
#define PARA_C_TD_SLOT12_POW	0	//		//488		TDʱ϶12�����⹦��	
#define PARA_C_TD_SLOT13_POW	0	//		//489		TDʱ϶13�����⹦��	
#define PARA_C_TD_SLOT14_POW	0	//		//490		TDʱ϶14�����⹦��	
#define PARA_C_TD_SLOT15_POW	0	//		//491		TDʱ϶15�����⹦��	
#define PARA_C_TD_SLOT16_POW	0	//		//492		TDʱ϶16�����⹦��	
#define PARA_C_TD_SLOT17_POW	0	//		//493		TDʱ϶17�����⹦��
#define PARA_C_TD_SLOT18_POW	0	//		//494		TDʱ϶18�����⹦��
#define PARA_C_TD_SLOT19_POW	0	//		//495		TDʱ϶19�����⹦��
#define PARA_C_TD_SLOT20_POW	0	//		//496		TDʱ϶20�����⹦��
#define PARA_D_TD_SLOT1_POW	0	//		//497		TDʱ϶1�����⹦��
#define PARA_D_TD_SLOT2_POW	0	//		//498		TDʱ϶2�����⹦��
#define PARA_D_TD_SLOT3_POW	0	//		//499		TDʱ϶3�����⹦��
#define PARA_D_TD_SLOT4_POW	0	//		//500		TDʱ϶4�����⹦��
#define PARA_D_TD_SLOT5_POW	0	//		//501		TDʱ϶5�����⹦��
#define PARA_D_TD_SLOT6_POW	0	//		//502		TDʱ϶6�����⹦��
#define PARA_D_TD_SLOT7_POW	0	//		//503		TDʱ϶7�����⹦��
#define PARA_D_TD_SLOT8_POW	0	//		//504		TDʱ϶8�����⹦��
#define PARA_D_TD_SLOT9_POW	0	//		//505		TDʱ϶9�����⹦��
#define PARA_D_TD_SLOT10_POW	0	//		//506		TDʱ϶10�����⹦��
#define PARA_D_TD_SLOT11_POW	0	//		//507		TDʱ϶11�����⹦��
#define PARA_D_TD_SLOT12_POW	0	//		//508		TDʱ϶12�����⹦��
#define PARA_D_TD_SLOT13_POW	0	//		//509		TDʱ϶13�����⹦��
#define PARA_D_TD_SLOT14_POW	0	//		//510		TDʱ϶14�����⹦��
#define PARA_D_TD_SLOT15_POW	0	//		//511		TDʱ϶15�����⹦��
#define PARA_D_TD_SLOT16_POW	0	//		//512		TDʱ϶16�����⹦��
#define PARA_D_TD_SLOT17_POW	0	//		//513		TDʱ϶17�����⹦��
#define PARA_D_TD_SLOT18_POW	0	//		//514		TDʱ϶18�����⹦��
#define PARA_D_TD_SLOT19_POW	0	//		//515		TDʱ϶19�����⹦��
#define PARA_D_TD_SLOT20_POW	0	//		//516		TDʱ϶20�����⹦��
#define	PARA_DL_DELAY_OFFSET_B		0//0x889c		//		������ʱƫ����		
#define	PARA_DL_DELAY_OFFSET_C		0//0x889c		//		������ʱƫ����		
#define	PARA_DL_DELAY_OFFSET_D		0//0x889c		//		������ʱƫ����		
#define	PARA_VGS_A		            0		//	         A��դѹ		
#define	PARA_VGS_B          		0		//		 B��դѹ		
#define	PARA_VGS_C          		0		//		 C��դѹ
#define	PARA_VGS_D          		0		//		 D��դѹ
#define	PARA_VGS_COMP_A		        0		//	     A��դѹ����		
#define	PARA_VGS_COMP_B             0		//		 B��դѹ����			
#define	PARA_VGS_COMP_C             0		//		 C��դѹ����	
#define	PARA_VGS_COMP_D          	0		//		 C��դѹ����	
#define	PARA_ATT_DATA_COMP_A		0				//ATT��������
#define	PARA_ATT_DATA_COMP_B		0				//ATT��������
#define	PARA_ATT_DATA_COMP_C		0				//ATT��������
#define	PARA_ATT_DATA_COMP_D		0				//ATT��������
#define	PARA_MAX_T14_A	0x889c	//	��������ʱ
#define	PARA_MAX_T14_B	0x889c	//	��������ʱ
#define	PARA_MAX_T14_C	0x889c	//	��������ʱ
#define	PARA_MAX_T14_D	0x889c	//	��������ʱ
#define PARA_ERL_JG_A		0// A�λ�����ͳ�ƽ��
#define PARA_ERL_JG_B		0
#define PARA_ERL_JG_C		0
#define PARA_ERL_JG_D		0
#define	PARA_MOVE_CENTER_FRE_D		0//�ı�������ƵƵ��
#define	PARA_MOVE_CENTER_FRE_U		0//�ı�������ƵƵ��



#else
	// ��ͨ����
// ������ַ����==================================================== 2b
#define	PARA_A_DL_CHANNEL1	0x0900	//	A�������ŵ���1
#define	PARA_A_DL_CHANNEL2	0x0901	//	A�������ŵ���2
#define	PARA_A_DL_CHANNEL3	0x0902	//	A�������ŵ���3
#define	PARA_A_DL_CHANNEL4	0x0903	//	A�������ŵ���4
#define	PARA_A_DL_CHANNEL5	0x0904	//	A�������ŵ���5
#define	PARA_A_DL_CHANNEL6	0x0905	//	A�������ŵ���6
#define	PARA_A_DL_CHANNEL7	0x0906	//	A�������ŵ���7
#define	PARA_A_DL_CHANNEL8	0x0907	//	A�������ŵ���8
#define	PARA_A_DL_CHANNEL9	0x0908	//	A�������ŵ���9
#define	PARA_A_DL_CHANNEL10	0x0909	//	A�������ŵ���10
#define	PARA_A_DL_CHANNEL11	0x090A	//	A�������ŵ���11
#define	PARA_A_DL_CHANNEL12	0x090B	//	A�������ŵ���12
#define	PARA_A_DL_CHANNEL13	0x090C	//	A�������ŵ���13
#define	PARA_A_DL_CHANNEL14	0x090D	//	A�������ŵ���14
#define	PARA_A_DL_CHANNEL15	0x090E	//	A�������ŵ���15
#define	PARA_A_DL_CHANNEL16	0x090F	//	A�������ŵ���16
#define	PARA_A_UL_CHANNEL1	0x0900	//	A�������ŵ���1
#define	PARA_A_UL_CHANNEL2	0x0901	//	A�������ŵ���2
#define	PARA_A_UL_CHANNEL3	0x0902	//	A�������ŵ���3
#define	PARA_A_UL_CHANNEL4	0x0903	//	A�������ŵ���4
#define	PARA_A_UL_CHANNEL5	0x0904	//	A�������ŵ���5
#define	PARA_A_UL_CHANNEL6	0x0905	//	A�������ŵ���6
#define	PARA_A_UL_CHANNEL7	0x0906	//	A�������ŵ���7
#define	PARA_A_UL_CHANNEL8	0x0907	//	A�������ŵ���8
#define	PARA_A_UL_CHANNEL9	0x0908	//	A�������ŵ���9
#define	PARA_A_UL_CHANNEL10	0x0909	//	A�������ŵ���10
#define	PARA_A_UL_CHANNEL11	0x090A	//	A�������ŵ���11
#define	PARA_A_UL_CHANNEL12	0x090B	//	A�������ŵ���12
#define	PARA_A_UL_CHANNEL13	0x090C	//	A�������ŵ���13
#define	PARA_A_UL_CHANNEL14	0x090D	//	A�������ŵ���14
#define	PARA_A_UL_CHANNEL15	0x090E	//	A�������ŵ���15
#define	PARA_A_UL_CHANNEL16	0x090F	//	A�������ŵ���16
#define	PARA_A_DCH_MAX_POW1	0x0348	//	A������ͨ������������1
#define	PARA_A_DCH_MAX_POW2	0	//	A������ͨ������������2
#define	PARA_A_DCH_MAX_POW3	0	//	A������ͨ������������3
#define	PARA_A_DCH_MAX_POW4	0	//	A������ͨ������������4
#define	PARA_A_DCH_MAX_POW5	0	//	A������ͨ������������5
#define	PARA_A_DCH_MAX_POW6	0	//	A������ͨ������������6
#define	PARA_A_DCH_MAX_POW7	0	//	A������ͨ������������7
#define	PARA_A_DCH_MAX_POW8	0	//	A������ͨ������������8
#define	PARA_A_DCH_MAX_POW9	0	//	A������ͨ������������9
#define	PARA_A_DCH_MAX_POW10	0	//	A������ͨ������������10
#define	PARA_A_DCH_MAX_POW11	0	//	A������ͨ������������11
#define	PARA_A_DCH_MAX_POW12	0	//	A������ͨ������������12
#define	PARA_A_DCH_MAX_POW13	0	//	A������ͨ������������13
#define	PARA_A_DCH_MAX_POW14	0	//	A������ͨ������������14
#define	PARA_A_DCH_MAX_POW15	0	//	A������ͨ������������15
#define	PARA_A_DCH_MAX_POW16	0	//	A������ͨ������������16
#define	PARA_A_UCH_MAX_POW1	0x0340	//	A������ͨ��������빦��1
#define	PARA_A_UCH_MAX_POW2	0	//	A������ͨ��������빦��2
#define	PARA_A_UCH_MAX_POW3	0	//	A������ͨ��������빦��3
#define	PARA_A_UCH_MAX_POW4	0	//	A������ͨ��������빦��4
#define	PARA_A_UCH_MAX_POW5	0	//	A������ͨ��������빦��5
#define	PARA_A_UCH_MAX_POW6	0	//	A������ͨ��������빦��6
#define	PARA_A_UCH_MAX_POW7	0	//	A������ͨ��������빦��7
#define	PARA_A_UCH_MAX_POW8	0	//	A������ͨ��������빦��8
#define	PARA_A_UCH_MAX_POW9	0	//	A������ͨ��������빦��9
#define	PARA_A_UCH_MAX_POW10	0	//	A������ͨ��������빦��10
#define	PARA_A_UCH_MAX_POW11	0	//	A������ͨ��������빦��11
#define	PARA_A_UCH_MAX_POW12	0	//	A������ͨ��������빦��12
#define	PARA_A_UCH_MAX_POW13	0	//	A������ͨ��������빦��13
#define	PARA_A_UCH_MAX_POW14	0	//	A������ͨ��������빦��14
#define	PARA_A_UCH_MAX_POW15	0	//	A������ͨ��������빦��15
#define	PARA_A_UCH_MAX_POW16	0	//	A������ͨ��������빦��16
#define	PARA_A_DCH_POW1	0	//	A��ѡƵͨ�����й���1
#define	PARA_A_DCH_POW2	0	//	A��ѡƵͨ�����й���2
#define	PARA_A_DCH_POW3	0	//	A��ѡƵͨ�����й���3
#define	PARA_A_DCH_POW4	0	//	A��ѡƵͨ�����й���4
#define	PARA_A_DCH_POW5	0	//	A��ѡƵͨ�����й���5
#define	PARA_A_DCH_POW6	0	//	A��ѡƵͨ�����й���6
#define	PARA_A_DCH_POW7	0	//	A��ѡƵͨ�����й���7
#define	PARA_A_DCH_POW8	0	//	A��ѡƵͨ�����й���8
#define	PARA_A_DCH_POW9	0	//	A��ѡƵͨ�����й���9
#define	PARA_A_DCH_POW10	0	//	A��ѡƵͨ�����й���10
#define	PARA_A_DCH_POW11	0	//	A��ѡƵͨ�����й���11
#define	PARA_A_DCH_POW12	0	//	A��ѡƵͨ�����й���12
#define	PARA_A_DCH_POW13	0	//	A��ѡƵͨ�����й���13
#define	PARA_A_DCH_POW14	0	//	A��ѡƵͨ�����й���14
#define	PARA_A_DCH_POW15	0	//	A��ѡƵͨ�����й���15
#define	PARA_A_DCH_POW16	0	//	A��ѡƵͨ�����й���16
#define	PARA_A_UCH_POW1	0	//	A��ѡƵͨ�����й���1
#define	PARA_A_UCH_POW2	0	//	A��ѡƵͨ�����й���2
#define	PARA_A_UCH_POW3	0	//	A��ѡƵͨ�����й���3
#define	PARA_A_UCH_POW4	0	//	A��ѡƵͨ�����й���4
#define	PARA_A_UCH_POW5	0	//	A��ѡƵͨ�����й���5
#define	PARA_A_UCH_POW6	0	//	A��ѡƵͨ�����й���6
#define	PARA_A_UCH_POW7	0	//	A��ѡƵͨ�����й���7
#define	PARA_A_UCH_POW8	0	//	A��ѡƵͨ�����й���8
#define	PARA_A_UCH_POW9	0	//	A��ѡƵͨ�����й���9
#define	PARA_A_UCH_POW10	0	//	A��ѡƵͨ�����й���10
#define	PARA_A_UCH_POW11	0	//	A��ѡƵͨ�����й���11
#define	PARA_A_UCH_POW12	0	//	A��ѡƵͨ�����й���12
#define	PARA_A_UCH_POW13	0	//	A��ѡƵͨ�����й���13
#define	PARA_A_UCH_POW14	0	//	A��ѡƵͨ�����й���14
#define	PARA_A_UCH_POW15	0	//	A��ѡƵͨ�����й���15
#define	PARA_A_UCH_POW16	0	//	A��ѡƵͨ�����й���16
#define	PARA_A_UDPX_IN_GAIN		0x08AB	//	A����������˫��������
#define	PARA_A_UDPX_OUT_GAIN	0x08AA	//	A���������˫��������
#define	PARA_A_DL_TOTAL_POW	0x8390	//	A�����������ܹ���
#define	PARA_A_UL_TOTAL_POW	0x831e	//	A����������ܹ���
#define	PARA_A_REC_DPX_IG		0		//		REC��A������˫�������棬��������������㣬ֻ��							
#define	PARA_A_REC_DPX_OG		0		//		REC��A�����˫�������棬��������������㣬ֻ��	
#define	PARA_B_DL_CHANNEL1	0x0900	//	B�������ŵ���1
#define	PARA_B_DL_CHANNEL2	0x0901	//	B�������ŵ���2
#define	PARA_B_DL_CHANNEL3	0x0902	//	B�������ŵ���3
#define	PARA_B_DL_CHANNEL4	0x0903	//	B�������ŵ���4
#define	PARA_B_DL_CHANNEL5	0x0904	//	B�������ŵ���5
#define	PARA_B_DL_CHANNEL6	0x0905	//	B�������ŵ���6
#define	PARA_B_DL_CHANNEL7	0x0906	//	B�������ŵ���7
#define	PARA_B_DL_CHANNEL8	0x0907	//	B�������ŵ���8
#define	PARA_B_DL_CHANNEL9	0x0908	//	B�������ŵ���9
#define	PARA_B_DL_CHANNEL10	0x0909	//	B�������ŵ���10
#define	PARA_B_DL_CHANNEL11	0x090A	//	B�������ŵ���11
#define	PARA_B_DL_CHANNEL12	0x090B	//	B�������ŵ���12
#define	PARA_B_DL_CHANNEL13	0x090C	//	B�������ŵ���13
#define	PARA_B_DL_CHANNEL14	0x090D	//	B�������ŵ���14
#define	PARA_B_DL_CHANNEL15	0x090E	//	B�������ŵ���15
#define	PARA_B_DL_CHANNEL16	0x090F	//	B�������ŵ���16
#define	PARA_B_UL_CHANNEL1	0x0900	//	B�������ŵ���1
#define	PARA_B_UL_CHANNEL2	0x0901	//	B�������ŵ���2
#define	PARA_B_UL_CHANNEL3	0x0902	//	B�������ŵ���3
#define	PARA_B_UL_CHANNEL4	0x0903	//	B�������ŵ���4
#define	PARA_B_UL_CHANNEL5	0x0904	//	B�������ŵ���5
#define	PARA_B_UL_CHANNEL6	0x0905	//	B�������ŵ���6
#define	PARA_B_UL_CHANNEL7	0x0906	//	B�������ŵ���7
#define	PARA_B_UL_CHANNEL8	0x0907	//	B�������ŵ���8
#define	PARA_B_UL_CHANNEL9	0x0908	//	B�������ŵ���9
#define	PARA_B_UL_CHANNEL10	0x0909	//	B�������ŵ���10
#define	PARA_B_UL_CHANNEL11	0x090A	//	B�������ŵ���11
#define	PARA_B_UL_CHANNEL12	0x090B	//	B�������ŵ���12
#define	PARA_B_UL_CHANNEL13	0x090C	//	B�������ŵ���13
#define	PARA_B_UL_CHANNEL14	0x090D	//	B�������ŵ���14
#define	PARA_B_UL_CHANNEL15	0x090E	//	B�������ŵ���15
#define	PARA_B_UL_CHANNEL16	0x090F	//	B�������ŵ���16
#define	PARA_B_DCH_MAX_POW1	0x0348	//	B������ͨ������������1
#define	PARA_B_DCH_MAX_POW2	0	//	B������ͨ������������2
#define	PARA_B_DCH_MAX_POW3	0	//	B������ͨ������������3
#define	PARA_B_DCH_MAX_POW4	0	//	B������ͨ������������4
#define	PARA_B_DCH_MAX_POW5	0	//	B������ͨ������������5
#define	PARA_B_DCH_MAX_POW6	0	//	B������ͨ������������6
#define	PARA_B_DCH_MAX_POW7	0	//	B������ͨ������������7
#define	PARA_B_DCH_MAX_POW8	0	//	B������ͨ������������8
#define	PARA_B_DCH_MAX_POW9	0	//	B������ͨ������������9
#define	PARA_B_DCH_MAX_POW10	0	//	B������ͨ������������10
#define	PARA_B_DCH_MAX_POW11	0	//	B������ͨ������������11
#define	PARA_B_DCH_MAX_POW12	0	//	B������ͨ������������12
#define	PARA_B_DCH_MAX_POW13	0	//	B������ͨ������������13
#define	PARA_B_DCH_MAX_POW14	0	//	B������ͨ������������14
#define	PARA_B_DCH_MAX_POW15	0	//	B������ͨ������������15
#define	PARA_B_DCH_MAX_POW16	0	//	B������ͨ������������16
#define	PARA_B_UCH_MAX_POW1	0x0340	//	B������ͨ��������빦��1
#define	PARA_B_UCH_MAX_POW2	0	//	B������ͨ��������빦��2
#define	PARA_B_UCH_MAX_POW3	0	//	B������ͨ��������빦��3
#define	PARA_B_UCH_MAX_POW4	0	//	B������ͨ��������빦��4
#define	PARA_B_UCH_MAX_POW5	0	//	B������ͨ��������빦��5
#define	PARA_B_UCH_MAX_POW6	0	//	B������ͨ��������빦��6
#define	PARA_B_UCH_MAX_POW7	0	//	B������ͨ��������빦��7
#define	PARA_B_UCH_MAX_POW8	0	//	B������ͨ��������빦��8
#define	PARA_B_UCH_MAX_POW9	0	//	B������ͨ��������빦��9
#define	PARA_B_UCH_MAX_POW10	0	//	B������ͨ��������빦��10
#define	PARA_B_UCH_MAX_POW11	0	//	B������ͨ��������빦��11
#define	PARA_B_UCH_MAX_POW12	0	//	B������ͨ��������빦��12
#define	PARA_B_UCH_MAX_POW13	0	//	B������ͨ��������빦��13
#define	PARA_B_UCH_MAX_POW14	0	//	B������ͨ��������빦��14
#define	PARA_B_UCH_MAX_POW15	0	//	B������ͨ��������빦��15
#define	PARA_B_UCH_MAX_POW16	0	//	B������ͨ��������빦��16
#define	PARA_B_DCH_POW1	0	//	B��ѡƵͨ�����й���1
#define	PARA_B_DCH_POW2	0	//	B��ѡƵͨ�����й���2
#define	PARA_B_DCH_POW3	0	//	B��ѡƵͨ�����й���3
#define	PARA_B_DCH_POW4	0	//	B��ѡƵͨ�����й���4
#define	PARA_B_DCH_POW5	0	//	B��ѡƵͨ�����й���5
#define	PARA_B_DCH_POW6	0	//	B��ѡƵͨ�����й���6
#define	PARA_B_DCH_POW7	0	//	B��ѡƵͨ�����й���7
#define	PARA_B_DCH_POW8	0	//	B��ѡƵͨ�����й���8
#define	PARA_B_DCH_POW9	0	//	B��ѡƵͨ�����й���9
#define	PARA_B_DCH_POW10	0	//	B��ѡƵͨ�����й���10
#define	PARA_B_DCH_POW11	0	//	B��ѡƵͨ�����й���11
#define	PARA_B_DCH_POW12	0	//	B��ѡƵͨ�����й���12
#define	PARA_B_DCH_POW13	0	//	B��ѡƵͨ�����й���13
#define	PARA_B_DCH_POW14	0	//	B��ѡƵͨ�����й���14
#define	PARA_B_DCH_POW15	0	//	B��ѡƵͨ�����й���15
#define	PARA_B_DCH_POW16	0	//	B��ѡƵͨ�����й���16
#define	PARA_B_UCH_POW1	0	//	B��ѡƵͨ�����й���1
#define	PARA_B_UCH_POW2	0	//	B��ѡƵͨ�����й���2
#define	PARA_B_UCH_POW3	0	//	B��ѡƵͨ�����й���3
#define	PARA_B_UCH_POW4	0	//	B��ѡƵͨ�����й���4
#define	PARA_B_UCH_POW5	0	//	B��ѡƵͨ�����й���5
#define	PARA_B_UCH_POW6	0	//	B��ѡƵͨ�����й���6
#define	PARA_B_UCH_POW7	0	//	B��ѡƵͨ�����й���7
#define	PARA_B_UCH_POW8	0	//	B��ѡƵͨ�����й���8
#define	PARA_B_UCH_POW9	0	//	B��ѡƵͨ�����й���9
#define	PARA_B_UCH_POW10	0	//	B��ѡƵͨ�����й���10
#define	PARA_B_UCH_POW11	0	//	B��ѡƵͨ�����й���11
#define	PARA_B_UCH_POW12	0	//	B��ѡƵͨ�����й���12
#define	PARA_B_UCH_POW13	0	//	B��ѡƵͨ�����й���13
#define	PARA_B_UCH_POW14	0	//	B��ѡƵͨ�����й���14
#define	PARA_B_UCH_POW15	0	//	B��ѡƵͨ�����й���15
#define	PARA_B_UCH_POW16	0	//	B��ѡƵͨ�����й���16
#define	PARA_B_UDPX_IN_GAIN	0x08AB	//	B����������˫��������
#define	PARA_B_UDPX_OUT_GAIN	0x08AA	//	B���������˫��������
#define	PARA_B_DL_TOTAL_POW	0x8390	//	B�����������ܹ���
#define	PARA_B_UL_TOTAL_POW	0x831e	//	B����������ܹ���
#define	PARA_B_REC_DPX_IG		0		//		REC��A������˫�������棬��������������㣬ֻ��							
#define	PARA_B_REC_DPX_OG		0		//		REC��A�����˫�������棬��������������㣬ֻ��	
#define	PARA_C_DL_CHANNEL1	0x0900	//	C�������ŵ���1
#define	PARA_C_DL_CHANNEL2	0x0901	//	C�������ŵ���2
#define	PARA_C_DL_CHANNEL3	0x0902	//	C�������ŵ���3
#define	PARA_C_DL_CHANNEL4	0x0903	//	C�������ŵ���4
#define	PARA_C_DL_CHANNEL5	0x0904	//	C�������ŵ���5
#define	PARA_C_DL_CHANNEL6	0x0905	//	C�������ŵ���6
#define	PARA_C_DL_CHANNEL7	0x0906	//	C�������ŵ���7
#define	PARA_C_DL_CHANNEL8	0x0907	//	C�������ŵ���8
#define	PARA_C_DL_CHANNEL9	0x0908	//	C�������ŵ���9
#define	PARA_C_DL_CHANNEL10	0x0909	//	C�������ŵ���10
#define	PARA_C_UL_CHANNEL1	0x0900	//	C�������ŵ���1
#define	PARA_C_UL_CHANNEL2	0x0901	//	C�������ŵ���2
#define	PARA_C_UL_CHANNEL3	0x0902	//	C�������ŵ���3
#define	PARA_C_UL_CHANNEL4	0x0903	//	C�������ŵ���4
#define	PARA_C_UL_CHANNEL5	0x0904	//	C�������ŵ���5
#define	PARA_C_UL_CHANNEL6	0x0905	//	C�������ŵ���6
#define	PARA_C_UL_CHANNEL7	0x0906	//	C�������ŵ���7
#define	PARA_C_UL_CHANNEL8	0x0907	//	C�������ŵ���8
#define	PARA_C_UL_CHANNEL9	0x0908	//	C�������ŵ���9
#define	PARA_C_UL_CHANNEL10	0x0909	//	C�������ŵ���10
#define	PARA_C_DCH_MAX_POW1	0x0348	//	C������ͨ������������1
#define	PARA_C_DCH_MAX_POW2	0	//	C������ͨ������������2
#define	PARA_C_DCH_MAX_POW3	0	//	C������ͨ������������3
#define	PARA_C_DCH_MAX_POW4	0	//	C������ͨ������������4
#define	PARA_C_DCH_MAX_POW5	0	//	C������ͨ������������5
#define	PARA_C_DCH_MAX_POW6	0	//	C������ͨ������������6
#define	PARA_C_DCH_MAX_POW7	0	//	C������ͨ������������7
#define	PARA_C_DCH_MAX_POW8	0	//	C������ͨ������������8
#define	PARA_C_DCH_MAX_POW9	0	//	C������ͨ������������9
#define	PARA_C_DCH_MAX_POW10	0	//	C������ͨ������������10
#define	PARA_C_DCH_MAX_POW11	0	//	C������ͨ������������11
#define	PARA_C_DCH_MAX_POW12	0	//	C������ͨ������������12
#define	PARA_C_DCH_MAX_POW13	0	//	C������ͨ������������13
#define	PARA_C_DCH_MAX_POW14	0	//	C������ͨ������������14
#define	PARA_C_DCH_MAX_POW15	0	//	C������ͨ������������15
#define	PARA_C_DCH_MAX_POW16	0	//	C������ͨ������������16
#define	PARA_C_UCH_MAX_POW1	0x0340	//	C������ͨ��������빦��1
#define	PARA_C_UCH_MAX_POW2	0	//	C������ͨ��������빦��2
#define	PARA_C_UCH_MAX_POW3	0	//	C������ͨ��������빦��3
#define	PARA_C_UCH_MAX_POW4	0	//	C������ͨ��������빦��4
#define	PARA_C_UCH_MAX_POW5	0	//	C������ͨ��������빦��5
#define	PARA_C_UCH_MAX_POW6	0	//	C������ͨ��������빦��6
#define	PARA_C_UCH_MAX_POW7	0	//	C������ͨ��������빦��7
#define	PARA_C_UCH_MAX_POW8	0	//	C������ͨ��������빦��8
#define	PARA_C_UCH_MAX_POW9	0	//	C������ͨ��������빦��9
#define	PARA_C_UCH_MAX_POW10		0	//	C������ͨ��������빦��10
#define	PARA_C_UCH_MAX_POW11		0	//	C������ͨ��������빦��11
#define	PARA_C_UCH_MAX_POW12		0	//	C������ͨ��������빦��12
#define	PARA_C_UCH_MAX_POW13		0	//	C������ͨ��������빦��13
#define	PARA_C_UCH_MAX_POW14		0	//	C������ͨ��������빦��14
#define	PARA_C_UCH_MAX_POW15		0	//	C������ͨ��������빦��15
#define	PARA_C_UCH_MAX_POW16		0	//	C������ͨ��������빦��16
#define	PARA_C_DCH_POW1	0	//	C��ѡƵͨ�����й���1
#define	PARA_C_DCH_POW2	0	//	C��ѡƵͨ�����й���2
#define	PARA_C_DCH_POW3	0	//	C��ѡƵͨ�����й���3
#define	PARA_C_DCH_POW4	0	//	C��ѡƵͨ�����й���4
#define	PARA_C_DCH_POW5	0	//	C��ѡƵͨ�����й���5
#define	PARA_C_DCH_POW6	0	//	C��ѡƵͨ�����й���6
#define	PARA_C_DCH_POW7	0	//	C��ѡƵͨ�����й���7
#define	PARA_C_DCH_POW8	0	//	C��ѡƵͨ�����й���8
#define	PARA_C_DCH_POW9	0	//	C��ѡƵͨ�����й���9
#define	PARA_C_DCH_POW10	0	//	C��ѡƵͨ�����й���10
#define	PARA_C_DCH_POW11	0	//	C��ѡƵͨ�����й���11
#define	PARA_C_DCH_POW12	0	//	C��ѡƵͨ�����й���12
#define	PARA_C_DCH_POW13	0	//	C��ѡƵͨ�����й���13
#define	PARA_C_DCH_POW14	0	//	C��ѡƵͨ�����й���14
#define	PARA_C_DCH_POW15	0	//	C��ѡƵͨ�����й���15
#define	PARA_C_DCH_POW16	0	//	C��ѡƵͨ�����й���16
#define	PARA_C_UCH_POW1	0	//	C��ѡƵͨ�����й���1
#define	PARA_C_UCH_POW2	0	//	C��ѡƵͨ�����й���2
#define	PARA_C_UCH_POW3	0	//	C��ѡƵͨ�����й���3
#define	PARA_C_UCH_POW4	0	//	C��ѡƵͨ�����й���4
#define	PARA_C_UCH_POW5	0	//	C��ѡƵͨ�����й���5
#define	PARA_C_UCH_POW6	0	//	C��ѡƵͨ�����й���6
#define	PARA_C_UCH_POW7	0	//	C��ѡƵͨ�����й���7
#define	PARA_C_UCH_POW8	0	//	C��ѡƵͨ�����й���8
#define	PARA_C_UCH_POW9	0	//	C��ѡƵͨ�����й���9
#define	PARA_C_UCH_POW10	0	//	C��ѡƵͨ�����й���10
#define	PARA_C_UCH_POW11	0	//	C��ѡƵͨ�����й���11
#define	PARA_C_UCH_POW12	0	//	C��ѡƵͨ�����й���12
#define	PARA_C_UCH_POW13	0	//	C��ѡƵͨ�����й���13
#define	PARA_C_UCH_POW14	0	//	C��ѡƵͨ�����й���14
#define	PARA_C_UCH_POW15	0	//	C��ѡƵͨ�����й���15
#define	PARA_C_UCH_POW16	0	//	C��ѡƵͨ�����й���16
#define	PARA_C_UDPX_IN_GAIN	0x08AB	//	C����������˫��������
#define	PARA_C_UDPX_OUT_GAIN	0x08AA	//	C���������˫��������
#define	PARA_C_DL_TOTAL_POW	0x8390	//	C�����������ܹ���
#define	PARA_C_UL_TOTAL_POW	0x831e	//	C����������ܹ���
#define	PARA_C_REC_DPX_IG		0		//		REC��A������˫�������棬��������������㣬ֻ��							
#define	PARA_C_REC_DPX_OG		0		//		REC��A�����˫�������棬��������������㣬ֻ��	
#define	PARA_D_DL_CHANNEL1	0x0900	//	D�������ŵ���1
#define	PARA_D_DL_CHANNEL2	0x0901	//	D�������ŵ���2
#define	PARA_D_DL_CHANNEL3	0x0902	//	D�������ŵ���3
#define	PARA_D_DL_CHANNEL4	0x0903	//	D�������ŵ���4
#define	PARA_D_DL_CHANNEL5	0x0904	//	D�������ŵ���5
#define	PARA_D_DL_CHANNEL6	0x0905	//	D�������ŵ���6
#define	PARA_D_DL_CHANNEL7	0x0906	//	D�������ŵ���7
#define	PARA_D_DL_CHANNEL8	0x0907	//	D�������ŵ���8
#define	PARA_D_DL_CHANNEL9	0x0908	//	D�������ŵ���9
#define	PARA_D_DL_CHANNEL10	0x0909	//	D�������ŵ���10
#define	PARA_D_UL_CHANNEL1	0x0900	//	D�������ŵ���1
#define	PARA_D_UL_CHANNEL2	0x0901	//	D�������ŵ���2
#define	PARA_D_UL_CHANNEL3	0x0902	//	D�������ŵ���3
#define	PARA_D_UL_CHANNEL4	0x0903	//	D�������ŵ���4
#define	PARA_D_UL_CHANNEL5	0x0904	//	D�������ŵ���5
#define	PARA_D_UL_CHANNEL6	0x0905	//	D�������ŵ���6
#define	PARA_D_UL_CHANNEL7	0x0906	//	D�������ŵ���7
#define	PARA_D_UL_CHANNEL8	0x0907	//	D�������ŵ���8
#define	PARA_D_UL_CHANNEL9	0x0908	//	D�������ŵ���9
#define	PARA_D_UL_CHANNEL10	0x0909	//	D�������ŵ���10
#define	PARA_D_DCH_MAX_POW1	0x0348	//	D������ͨ������������1
#define	PARA_D_DCH_MAX_POW2	0	//	D������ͨ������������2
#define	PARA_D_DCH_MAX_POW3	0	//	D������ͨ������������3
#define	PARA_D_DCH_MAX_POW4	0	//	D������ͨ������������4
#define	PARA_D_DCH_MAX_POW5	0	//	D������ͨ������������5
#define	PARA_D_DCH_MAX_POW6	0	//	D������ͨ������������6
#define	PARA_D_DCH_MAX_POW7	0	//	D������ͨ������������7
#define	PARA_D_DCH_MAX_POW8	0	//	D������ͨ������������8
#define	PARA_D_DCH_MAX_POW9	0	//	D������ͨ������������9
#define	PARA_D_DCH_MAX_POW10	0	//	D������ͨ������������10
#define	PARA_D_DCH_MAX_POW11	0	//	D������ͨ������������11
#define	PARA_D_DCH_MAX_POW12	0	//	D������ͨ������������12
#define	PARA_D_DCH_MAX_POW13	0	//	D������ͨ������������13
#define	PARA_D_DCH_MAX_POW14	0	//	D������ͨ������������14
#define	PARA_D_DCH_MAX_POW15	0	//	D������ͨ������������15
#define	PARA_D_DCH_MAX_POW16	0	//	D������ͨ������������16
#define	PARA_D_UCH_MAX_POW1	0x0340	//	D������ͨ��������빦��1
#define	PARA_D_UCH_MAX_POW2	0	//	D������ͨ��������빦��2
#define	PARA_D_UCH_MAX_POW3	0	//	D������ͨ��������빦��3
#define	PARA_D_UCH_MAX_POW4	0	//	D������ͨ��������빦��4
#define	PARA_D_UCH_MAX_POW5	0	//	D������ͨ��������빦��5
#define	PARA_D_UCH_MAX_POW6	0	//	D������ͨ��������빦��6
#define	PARA_D_UCH_MAX_POW7	0	//	D������ͨ��������빦��7
#define	PARA_D_UCH_MAX_POW8	0	//	D������ͨ��������빦��8
#define	PARA_D_UCH_MAX_POW9	0	//	D������ͨ��������빦��9
#define	PARA_D_UCH_MAX_POW10	0	//	D������ͨ��������빦��10
#define	PARA_D_UCH_MAX_POW11	0	//	D������ͨ��������빦��11
#define	PARA_D_UCH_MAX_POW12	0	//	D������ͨ��������빦��12
#define	PARA_D_UCH_MAX_POW13	0	//	D������ͨ��������빦��13
#define	PARA_D_UCH_MAX_POW14	0	//	D������ͨ��������빦��14
#define	PARA_D_UCH_MAX_POW15	0	//	D������ͨ��������빦��15
#define	PARA_D_UCH_MAX_POW16	0	//	D������ͨ��������빦��16
#define	PARA_D_DCH_POW1	0	//	D��ѡƵͨ�����й���1
#define	PARA_D_DCH_POW2	0	//	D��ѡƵͨ�����й���2
#define	PARA_D_DCH_POW3	0	//	D��ѡƵͨ�����й���3
#define	PARA_D_DCH_POW4	0	//	D��ѡƵͨ�����й���4
#define	PARA_D_DCH_POW5	0	//	D��ѡƵͨ�����й���5
#define	PARA_D_DCH_POW6	0	//	D��ѡƵͨ�����й���6
#define	PARA_D_DCH_POW7	0	//	D��ѡƵͨ�����й���7
#define	PARA_D_DCH_POW8	0	//	D��ѡƵͨ�����й���8
#define	PARA_D_DCH_POW9	0	//	D��ѡƵͨ�����й���9
#define	PARA_D_DCH_POW10	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_DCH_POW11	0	//	D��ѡƵͨ�����й���11
#define	PARA_D_DCH_POW12	0	//	D��ѡƵͨ�����й���12
#define	PARA_D_DCH_POW13	0	//	D��ѡƵͨ�����й���13
#define	PARA_D_DCH_POW14	0	//	D��ѡƵͨ�����й���14
#define	PARA_D_DCH_POW15	0	//	D��ѡƵͨ�����й���15
#define	PARA_D_DCH_POW16	0	//	D��ѡƵͨ�����й���16
#define	PARA_D_UCH_POW1	0	//	D��ѡƵͨ�����й���1
#define	PARA_D_UCH_POW2	0	//	D��ѡƵͨ�����й���2
#define	PARA_D_UCH_POW3	0	//	D��ѡƵͨ�����й���3
#define	PARA_D_UCH_POW4	0	//	D��ѡƵͨ�����й���4
#define	PARA_D_UCH_POW5	0	//	D��ѡƵͨ�����й���5
#define	PARA_D_UCH_POW6	0	//	D��ѡƵͨ�����й���6
#define	PARA_D_UCH_POW7	0	//	D��ѡƵͨ�����й���7
#define	PARA_D_UCH_POW8	0	//	D��ѡƵͨ�����й���8
#define	PARA_D_UCH_POW9	0	//	D��ѡƵͨ�����й���9
#define	PARA_D_UCH_POW10	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW11	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW12	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW13	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW14	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW15	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UCH_POW16	0	//	D��ѡƵͨ�����й���10
#define	PARA_D_UDPX_IN_GAIN	0x08AB	//	D����������˫��������
#define	PARA_D_UDPX_OUT_GAIN	0x08AA	//	D���������˫��������
#define	PARA_D_DL_TOTAL_POW	0x8390	//	D�����������ܹ���
#define	PARA_D_UL_TOTAL_POW	0x831e	//	D����������ܹ���
#define	PARA_D_REC_DPX_IG		0		//		REC��D������˫�������棬��������������㣬ֻ��							
#define	PARA_D_REC_DPX_OG		0		//		REC��D�����˫�������棬��������������㣬ֻ��	
#define	PARA_REC_TO_RE_DELAY		0x889e	// REC��RE�Ĺ�����ʱ
#define	PARA_RE_RF_DELAY			0x889f	// RE����Ƶ��ʱ
#define	PARA_MAX_T14	0//0x889c	//	��������ʱ
#define	PARA_DL_DELAY_OFFSET	0//0x0768	//	������ʱƫ����
#define	PARA_UL_DELAY_OFFSET	0x0769	//	������ʱƫ����
#define	PARA_PRI_SOFT_V	0xf018	//	����汾�ţ���ASCII�룩
#define	PARA_PRI_HARD_V	0xf026	//	PCB�汾��(��ASCII��)
#define	PARA_TD_1ST_CP_TIME		0x08a7	// TD��1ת����ʱ��ns, �з�����
#define	PARA_TD_2ND_CP_TIME		0x08a8	// TD��2ת����ʱ��ns, �з�����
#define	PARA_TD_LNA_ON_TIME		0x08ae	// LNA�����ٺ�DN_PA�رյı���ʱ��ns
#define	PARA_TD_LNA_OFF_TIME		0x08af	// LNA�رճ�ǰDN_PA�����ı���ʱ��ns
#define	PARA_TD_SLOT1_UPOW	0x7501	// TDʱ϶1���м�⹦��
#define	PARA_TD_SLOT2_UPOW	0x7502	// TDʱ϶2���м�⹦��
#define	PARA_TD_SLOT3_UPOW	0x7503	// TDʱ϶3���м�⹦��
#define	PARA_TD_SLOT4_UPOW	0x7504	// TDʱ϶4���м�⹦��
#define	PARA_TD_SLOT5_UPOW	0x7505	// TDʱ϶5���м�⹦��
#define	PARA_TD_SLOT6_UPOW	0x7506	// TDʱ϶6���м�⹦��
#define	PARA_TD_SLOT7_UPOW	0x7507	// TDʱ϶7���м�⹦��
#define	PARA_TD_SLOT1_DPOW	0x7511	// TDʱ϶1���м�⹦��
#define	PARA_TD_SLOT2_DPOW	0x7512	// TDʱ϶2���м�⹦��
#define	PARA_TD_SLOT3_DPOW	0x7513	// TDʱ϶3���м�⹦��
#define	PARA_TD_SLOT4_DPOW	0x7514	// TDʱ϶4���м�⹦��
#define	PARA_TD_SLOT5_DPOW	0x7515	// TDʱ϶5���м�⹦��
#define	PARA_TD_SLOT6_DPOW	0x7516	// TDʱ϶6���м�⹦��
#define	PARA_TD_SLOT7_DPOW	0x7517	// TDʱ϶7���м�⹦��
#define	PARA_FPS_S1 0 // Ƶ������: ��Χ1��ʼƵ��
#define	PARA_FPS_E1 0 // Ƶ������: ��Χ1����Ƶ��
#define	PARA_FPS_S2 0 // Ƶ������: ��Χ2��ʼƵ��
#define	PARA_FPS_E2 0 // Ƶ������: ��Χ2����Ƶ��
#define	PARA_FPS_BCCH_LK_SET	0x0923	// Ƶ������: ��Ƶ�ŵ���: ��׼�ŵ���, 65535-�˳���Ƶ
#define	PARA_FPS_CID_LK_SET	0x0926	// Ƶ������: С��ʶ����ο�ֵ, 0-�˳�С����������
#define	PARA_FPS_BCCH_FC_M	0x8940	// Ƶ������: ��С��BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_CA_FC_0	0x8941	// Ƶ������: CA�ز�0�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_1	0x8942	// Ƶ������: CA�ز�1�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_2	0x8943	// Ƶ������: CA�ز�2�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_3	0x8944	// Ƶ������: CA�ز�3�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_4	0x8945	// Ƶ������: CA�ز�4�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_5	0x8946	// Ƶ������: CA�ز�5�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_6	0x8947	// Ƶ������: CA�ز�6�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_7	0x8948	// Ƶ������: CA�ز�7�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_8	0x8949	// Ƶ������: CA�ز�8�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_9	0x894A	// Ƶ������: CA�ز�9�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_10	0x894B	// Ƶ������: CA�ز�10�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_11	0x894C	// Ƶ������: CA�ز�11�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_12	0x894D	// Ƶ������: CA�ز�12�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_13	0x894E	// Ƶ������: CA�ز�13�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_14	0x894F	// Ƶ������: CA�ز�14�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_CA_FC_15	0x8950	// Ƶ������: CA�ز�15�ŵ���, ��׼�ŵ���, 65535-��CA
#define	PARA_FPS_BCCH_FC_1	0x8951	// Ƶ������: ��С��1 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_2	0x8952	// Ƶ������: ��С��2 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_3	0x8953	// Ƶ������: ��С��3 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_4	0x8954	// Ƶ������: ��С��4 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_5	0x8955	// Ƶ������: ��С��5 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_BCCH_FC_6	0x8956	// Ƶ������: ��С��6 BCCH�ŵ���, ��׼�ŵ���, 65535-��BCCH
#define	PARA_FPS_AREA_ID	0x8958	// Ƶ������: λ��������
#define	PARA_FPS_CID		0x895A	// Ƶ������: С��ʶ����ʵʱֵ
#define	PARA_FPS_CID_1 0 // Ƶ������: ��С��1 CIDС��ʶ����
#define	PARA_FPS_CID_2 0 // Ƶ������: ��С��2 CIDС��ʶ����
#define	PARA_FPS_CID_3 0 // Ƶ������: ��С��3 CIDС��ʶ����
#define	PARA_FPS_CID_4 0 // Ƶ������: ��С��4 CIDС��ʶ����
#define	PARA_FPS_CID_5 0 // Ƶ������: ��С��5 CIDС��ʶ����
#define	PARA_FPS_CID_6 0 // Ƶ������: ��С��6 CIDС��ʶ����
#define	PARA_A_EXPA_IDRAIN_SET	0	// ΢����: ©����������,mA
#define	PARA_TD_SLOT1_DPOW_OVER_THR				0x0a60       //td�������뵼Ƶ����������
#define	PARA_TD_SLOT1_DPOW_OWE_THR				0x0a61      //td�������뵼ƵǷ��������	
#define PARA_A_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //�����������������
#define PARA_A_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //��������Ƿ��������
#define PARA_B_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //�����������������
#define PARA_B_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //��������Ƿ��������
#define PARA_C_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //�����������������
#define PARA_C_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //��������Ƿ��������
#define PARA_D_INPUT_TOTAL_DPOW_OVER_THR     	0x0a64      //�����������������
#define PARA_D_INPUT_TOTAL_DPOW_OWE_THR			0x0a65      //��������Ƿ��������
#define PARA_REE_A_DL_OUT_TOTAL_POW_DETECT     	0x8004      //A��RE��������ܹ���//עREC\REʹ�� MADD_A_DL_TOTAL_POW
#define PARA_A_RE_LOCAL_ST_ALARM     			0x8a33      	//���ǵ�Ԫ���ظ澯״̬
#define PARA_REE_B_DL_OUT_TOTAL_POW_DETECT     	0x8004      //B��RE��������ܹ��� //עREC\REʹ�� MADD_B_DL_TOTAL_POW
#define PARA_B_RE_LOCAL_ST_ALARM     			0x8a33      	//���ǵ�Ԫ���ظ澯״̬
#define PARA_REE_C_DL_OUT_TOTAL_POW_DETECT     	0x8004      //A��RE��������ܹ���//עREC\REʹ�� MADD_C_DL_TOTAL_POW
#define PARA_C_RE_LOCAL_ST_ALARM     			0x8a33      	//���ǵ�Ԫ���ظ澯״̬
#define PARA_REE_D_DL_OUT_TOTAL_POW_DETECT     	0x8004      //	D��RE��������ܹ��� //עREC\REʹ�� MADD_D_DL_TOTAL_POW
#define PARA_D_RE_LOCAL_ST_ALARM     			0x8a33      	//	D���ǵ�Ԫ���ظ澯״̬
#define PARA_C_TD_1ST_CP_TIME	0x08a7	//		//465		TD��1ת����ʱ��,ns,		
#define PARA_C_TD_2ND_CP_TIME	0x08a8	//		//466		TD��2ת����ʱ��,ns,		
#define PARA_C_TD_LNA_ON_TIME	0x08ae	//		//467		LNA�����ٺ�DN_PA�رյı���ʱ��ns		
#define PARA_C_TD_LNA_OFF_TIME	0x08af	//		//468		LNA�رճ�ǰDN_PA�����ı���ʱ��ns		
#define PARA_C_TD_SLOT1_DPOW_OVER_THR	0x0a60	//		//469	0	//		//5625
#define PARA_C_TD_SLOT1_DPOW_OWE_THR	0x0a61	//		//470	0	//		//5626
#define PARA_D_TD_1ST_CP_TIME	0x08a7	//		//471		TD��1ת����ʱ��,ns,		
#define PARA_D_TD_2ND_CP_TIME	0x08a7	//		//472		TD��2ת����ʱ��,ns,		
#define PARA_D_TD_LNA_ON_TIME	0x08ae	//		//473		LNA�����ٺ�DN_PA�رյı���ʱ��ns		
#define PARA_D_TD_LNA_OFF_TIME	0x08af	//		//474		LNA�رճ�ǰDN_PA�����ı���ʱ��ns		
#define PARA_D_TD_SLOT1_DPOW_OVER_THR	0x0a60	//		//475	0	//		//5625
#define PARA_D_TD_SLOT1_DPOW_OWE_THR	0x0a61	//		//476	0	//		//5626
#define PARA_C_TD_SLOT1_POW	0x7511	//		//477		TDʱ϶1�����⹦��	
#define PARA_C_TD_SLOT2_POW	0	//		//478		TDʱ϶2�����⹦��	
#define PARA_C_TD_SLOT3_POW	0	//		//479		TDʱ϶3�����⹦��	
#define PARA_C_TD_SLOT4_POW	0	//		//480		TDʱ϶4�����⹦��	
#define PARA_C_TD_SLOT5_POW	0	//		//481		TDʱ϶5�����⹦��	
#define PARA_C_TD_SLOT6_POW	0	//		//482		TDʱ϶6�����⹦��	
#define PARA_C_TD_SLOT7_POW	0	//		//483		TDʱ϶7�����⹦��	
#define PARA_C_TD_SLOT8_POW	0	//		//484		TDʱ϶8�����⹦��	
#define PARA_C_TD_SLOT9_POW	0	//		//485		TDʱ϶9�����⹦��	
#define PARA_C_TD_SLOT10_POW	0	//		//486		TDʱ϶10�����⹦��	
#define PARA_C_TD_SLOT11_POW	0	//		//487		TDʱ϶11�����⹦��	
#define PARA_C_TD_SLOT12_POW	0	//		//488		TDʱ϶12�����⹦��	
#define PARA_C_TD_SLOT13_POW	0	//		//489		TDʱ϶13�����⹦��	
#define PARA_C_TD_SLOT14_POW	0	//		//490		TDʱ϶14�����⹦��	
#define PARA_C_TD_SLOT15_POW	0	//		//491		TDʱ϶15�����⹦��	
#define PARA_C_TD_SLOT16_POW	0	//		//492		TDʱ϶16�����⹦��	
#define PARA_C_TD_SLOT17_POW	0	//		//493		TDʱ϶17�����⹦��
#define PARA_C_TD_SLOT18_POW	0	//		//494		TDʱ϶18�����⹦��
#define PARA_C_TD_SLOT19_POW	0	//		//495		TDʱ϶19�����⹦��
#define PARA_C_TD_SLOT20_POW	0	//		//496		TDʱ϶20�����⹦��
#define PARA_D_TD_SLOT1_POW	0x7511	//		//497		TDʱ϶1�����⹦��
#define PARA_D_TD_SLOT2_POW	0	//		//498		TDʱ϶2�����⹦��
#define PARA_D_TD_SLOT3_POW	0	//		//499		TDʱ϶3�����⹦��
#define PARA_D_TD_SLOT4_POW	0	//		//500		TDʱ϶4�����⹦��
#define PARA_D_TD_SLOT5_POW	0	//		//501		TDʱ϶5�����⹦��
#define PARA_D_TD_SLOT6_POW	0	//		//502		TDʱ϶6�����⹦��
#define PARA_D_TD_SLOT7_POW	0	//		//503		TDʱ϶7�����⹦��
#define PARA_D_TD_SLOT8_POW	0	//		//504		TDʱ϶8�����⹦��
#define PARA_D_TD_SLOT9_POW	0	//		//505		TDʱ϶9�����⹦��
#define PARA_D_TD_SLOT10_POW	0	//		//506		TDʱ϶10�����⹦��
#define PARA_D_TD_SLOT11_POW	0	//		//507		TDʱ϶11�����⹦��
#define PARA_D_TD_SLOT12_POW	0	//		//508		TDʱ϶12�����⹦��
#define PARA_D_TD_SLOT13_POW	0	//		//509		TDʱ϶13�����⹦��
#define PARA_D_TD_SLOT14_POW	0	//		//510		TDʱ϶14�����⹦��
#define PARA_D_TD_SLOT15_POW	0	//		//511		TDʱ϶15�����⹦��
#define PARA_D_TD_SLOT16_POW	0	//		//512		TDʱ϶16�����⹦��
#define PARA_D_TD_SLOT17_POW	0	//		//513		TDʱ϶17�����⹦��
#define PARA_D_TD_SLOT18_POW	0	//		//514		TDʱ϶18�����⹦��
#define PARA_D_TD_SLOT19_POW	0	//		//515		TDʱ϶19�����⹦��
#define PARA_D_TD_SLOT20_POW	0	//		//516		TDʱ϶20�����⹦��
#define	PARA_DL_DELAY_OFFSET_B		0//0x889c		//		������ʱƫ����		
#define	PARA_DL_DELAY_OFFSET_C		0//0x889c		//		������ʱƫ����		
#define	PARA_DL_DELAY_OFFSET_D		0//0x889c		//		������ʱƫ����		
#define	PARA_VGS_A		            0		//	         A��դѹ		
#define	PARA_VGS_B          		0		//		 B��դѹ		
#define	PARA_VGS_C          		0		//		 C��դѹ
#define	PARA_VGS_D          		0		//		 D��դѹ
#define	PARA_VGS_COMP_A		        0		//	     A��դѹ����		
#define	PARA_VGS_COMP_B             0		//		 B��դѹ����			
#define	PARA_VGS_COMP_C             0		//		 C��դѹ����	
#define	PARA_VGS_COMP_D          	0		//		 C��դѹ����	
#define	PARA_ATT_DATA_COMP_A		0				//ATT��������
#define	PARA_ATT_DATA_COMP_B		0				//ATT��������
#define	PARA_ATT_DATA_COMP_C		0				//ATT��������
#define	PARA_ATT_DATA_COMP_D		0				//ATT��������
#define	PARA_MAX_T14_A	0x889c	//	��������ʱ
#define	PARA_MAX_T14_B	0x889c	//	��������ʱ
#define	PARA_MAX_T14_C	0x889c	//	��������ʱ
#define	PARA_MAX_T14_D	0x889c	//	��������ʱ
#define PARA_ERL_JG_A		0// A�λ�����ͳ�ƽ��
#define PARA_ERL_JG_B		0
#define PARA_ERL_JG_C		0
#define PARA_ERL_JG_D		0
#define	PARA_MOVE_CENTER_FRE_D		0//�ı���������Ƶ��
#define	PARA_MOVE_CENTER_FRE_U		0//�ı���������Ƶ��

#endif

// ���ʵ�ַ>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 2B
#define	MADD_A_DL_CHANNEL1		0		//		A�������ŵ���1		
#define	MADD_A_DL_CHANNEL2		1		//		A�������ŵ���2		
#define	MADD_A_DL_CHANNEL3		2		//		A�������ŵ���3		
#define	MADD_A_DL_CHANNEL4		3		//		A�������ŵ���4		
#define	MADD_A_DL_CHANNEL5		4		//		A�������ŵ���5		
#define	MADD_A_DL_CHANNEL6		5		//		A�������ŵ���6		
#define	MADD_A_DL_CHANNEL7		6		//		A�������ŵ���7		
#define	MADD_A_DL_CHANNEL8		7		//		A�������ŵ���8		
#define	MADD_A_DL_CHANNEL9		8		//		A�������ŵ���9		
#define	MADD_A_DL_CHANNEL10		9		//		A�������ŵ���10		
#define	MADD_A_DL_CHANNEL11		10		//		A�������ŵ���11		
#define	MADD_A_DL_CHANNEL12		11		//		A�������ŵ���12		
#define	MADD_A_DL_CHANNEL13		12		//		A�������ŵ���13		
#define	MADD_A_DL_CHANNEL14		13		//		A�������ŵ���14		
#define	MADD_A_DL_CHANNEL15		14		//		A�������ŵ���15		
#define	MADD_A_DL_CHANNEL16		15		//		A�������ŵ���16		
#define	MADD_A_UL_CHANNEL1		16		//		A�������ŵ���1		
#define	MADD_A_UL_CHANNEL2		17		//		A�������ŵ���2		
#define	MADD_A_UL_CHANNEL3		18		//		A�������ŵ���3		
#define	MADD_A_UL_CHANNEL4		19		//		A�������ŵ���4		
#define	MADD_A_UL_CHANNEL5		20		//		A�������ŵ���5		
#define	MADD_A_UL_CHANNEL6		21		//		A�������ŵ���6		
#define	MADD_A_UL_CHANNEL7		22		//		A�������ŵ���7		
#define	MADD_A_UL_CHANNEL8		23		//		A�������ŵ���8		
#define	MADD_A_UL_CHANNEL9		24		//		A�������ŵ���9		
#define	MADD_A_UL_CHANNEL10		25		//		A�������ŵ���10		
#define	MADD_A_UL_CHANNEL11		26		//		A�������ŵ���11		
#define	MADD_A_UL_CHANNEL12		27		//		A�������ŵ���12		
#define	MADD_A_UL_CHANNEL13		28		//		A�������ŵ���13		
#define	MADD_A_UL_CHANNEL14		29		//		A�������ŵ���14		
#define	MADD_A_UL_CHANNEL15		30		//		A�������ŵ���15		
#define	MADD_A_UL_CHANNEL16		31		//		A�������ŵ���16		
#define	MADD_A_DCH_MAX_POW1		32		//		A������ͨ������������1		
#define	MADD_A_DCH_MAX_POW2		33		//		A������ͨ������������2		
#define	MADD_A_DCH_MAX_POW3		34		//		A������ͨ������������3		
#define	MADD_A_DCH_MAX_POW4		35		//		A������ͨ������������4		
#define	MADD_A_DCH_MAX_POW5		36		//		A������ͨ������������5		
#define	MADD_A_DCH_MAX_POW6		37		//		A������ͨ������������6		
#define	MADD_A_DCH_MAX_POW7		38		//		A������ͨ������������7		
#define	MADD_A_DCH_MAX_POW8		39		//		A������ͨ������������8		
#define	MADD_A_DCH_MAX_POW9		40		//		A������ͨ������������9		
#define	MADD_A_DCH_MAX_POW10		41		//		A������ͨ������������10		
#define	MADD_A_DCH_MAX_POW11		42		//		A������ͨ������������11		
#define	MADD_A_DCH_MAX_POW12		43		//		A������ͨ������������12		
#define	MADD_A_DCH_MAX_POW13		44		//		A������ͨ������������13		
#define	MADD_A_DCH_MAX_POW14		45		//		A������ͨ������������14		
#define	MADD_A_DCH_MAX_POW15		46		//		A������ͨ������������15		
#define	MADD_A_DCH_MAX_POW16		47		//		A������ͨ������������16		
#define	MADD_A_UCH_MAX_POW1		48		//		A������ͨ��������빦��1		
#define	MADD_A_UCH_MAX_POW2		49		//		A������ͨ��������빦��2		
#define	MADD_A_UCH_MAX_POW3		50		//		A������ͨ��������빦��3		
#define	MADD_A_UCH_MAX_POW4		51		//		A������ͨ��������빦��4		
#define	MADD_A_UCH_MAX_POW5		52		//		A������ͨ��������빦��5		
#define	MADD_A_UCH_MAX_POW6		53		//		A������ͨ��������빦��6		
#define	MADD_A_UCH_MAX_POW7		54		//		A������ͨ��������빦��7		
#define	MADD_A_UCH_MAX_POW8		55		//		A������ͨ��������빦��8		
#define	MADD_A_UCH_MAX_POW9		56		//		A������ͨ��������빦��9		
#define	MADD_A_UCH_MAX_POW10		57		//		A������ͨ��������빦��10		
#define	MADD_A_UCH_MAX_POW11		58		//		A������ͨ��������빦��11		
#define	MADD_A_UCH_MAX_POW12		59		//		A������ͨ��������빦��12		
#define	MADD_A_UCH_MAX_POW13		60		//		A������ͨ��������빦��13		
#define	MADD_A_UCH_MAX_POW14		61		//		A������ͨ��������빦��14		
#define	MADD_A_UCH_MAX_POW15		62		//		A������ͨ��������빦��15		
#define	MADD_A_UCH_MAX_POW16		63		//		A������ͨ��������빦��16		
#define	MADD_A_DCH_POW1		64		//		A��ѡƵͨ�����й���1		
#define	MADD_A_DCH_POW2		65		//		A��ѡƵͨ�����й���2		
#define	MADD_A_DCH_POW3		66		//		A��ѡƵͨ�����й���3		
#define	MADD_A_DCH_POW4		67		//		A��ѡƵͨ�����й���4		
#define	MADD_A_DCH_POW5		68		//		A��ѡƵͨ�����й���5		
#define	MADD_A_DCH_POW6		69		//		A��ѡƵͨ�����й���6		
#define	MADD_A_DCH_POW7		70		//		A��ѡƵͨ�����й���7		
#define	MADD_A_DCH_POW8		71		//		A��ѡƵͨ�����й���8		
#define	MADD_A_DCH_POW9		72		//		A��ѡƵͨ�����й���9		
#define	MADD_A_DCH_POW10		73		//		A��ѡƵͨ�����й���10		
#define	MADD_A_DCH_POW11		74		//		A��ѡƵͨ�����й���11		
#define	MADD_A_DCH_POW12		75		//		A��ѡƵͨ�����й���12		
#define	MADD_A_DCH_POW13		76		//		A��ѡƵͨ�����й���13		
#define	MADD_A_DCH_POW14		77		//		A��ѡƵͨ�����й���14		
#define	MADD_A_DCH_POW15		78		//		A��ѡƵͨ�����й���15		
#define	MADD_A_DCH_POW16		79		//		A��ѡƵͨ�����й���16		
#define	MADD_A_UCH_POW1		80		//		A��ѡƵͨ�����й���1		
#define	MADD_A_UCH_POW2		81		//		A��ѡƵͨ�����й���2		
#define	MADD_A_UCH_POW3		82		//		A��ѡƵͨ�����й���3		
#define	MADD_A_UCH_POW4		83		//		A��ѡƵͨ�����й���4		
#define	MADD_A_UCH_POW5		84		//		A��ѡƵͨ�����й���5		
#define	MADD_A_UCH_POW6		85		//		A��ѡƵͨ�����й���6		
#define	MADD_A_UCH_POW7		86		//		A��ѡƵͨ�����й���7		
#define	MADD_A_UCH_POW8		87		//		A��ѡƵͨ�����й���8		
#define	MADD_A_UCH_POW9		88		//		A��ѡƵͨ�����й���9		
#define	MADD_A_UCH_POW10		89		//		A��ѡƵͨ�����й���10		
#define	MADD_A_UCH_POW11		90		//		A��ѡƵͨ�����й���11		
#define	MADD_A_UCH_POW12		91		//		A��ѡƵͨ�����й���12		
#define	MADD_A_UCH_POW13		92		//		A��ѡƵͨ�����й���13		
#define	MADD_A_UCH_POW14		93		//		A��ѡƵͨ�����й���14		
#define	MADD_A_UCH_POW15		94		//		A��ѡƵͨ�����й���15		
#define	MADD_A_UCH_POW16		95		//		A��ѡƵͨ�����й���16		
#define	MADD_A_UDPX_IN_GAIN		96		//		A������˫����˥��,		
#define	MADD_A_UDPX_OUT_GAIN		97		//		A�����˫����˥��,		
#define	MADD_A_DL_TOTAL_POW		98		//		A����������ܹ��ʣ�x10�㷨����һλС��		
#define	MADD_A_UL_TOTAL_POW		99		//		A�����������ܹ��ʣ�x10�㷨����һλС��		
#define	MADD_A_REC_DPX_IG		100		//		REC��A������˫����˥������������������㣬ֻ��,		
#define	MADD_A_REC_DPX_OG		101		//		REC��A�����˫����˥������������������㣬ֻ��,		
#define	MADD_B_DL_CHANNEL1		102		//		B�������ŵ���1		
#define	MADD_B_DL_CHANNEL2		103		//		B�������ŵ���2		
#define	MADD_B_DL_CHANNEL3		104		//		B�������ŵ���3		
#define	MADD_B_DL_CHANNEL4		105		//		B�������ŵ���4		
#define	MADD_B_DL_CHANNEL5		106		//		B�������ŵ���5		
#define	MADD_B_DL_CHANNEL6		107		//		B�������ŵ���6		
#define	MADD_B_DL_CHANNEL7		108		//		B�������ŵ���7		
#define	MADD_B_DL_CHANNEL8		109		//		B�������ŵ���8		
#define	MADD_B_DL_CHANNEL9		110		//		B�������ŵ���9		
#define	MADD_B_DL_CHANNEL10		111		//		B�������ŵ���10		
#define	MADD_B_DL_CHANNEL11		112		//		B�������ŵ���11		
#define	MADD_B_DL_CHANNEL12		113		//		B�������ŵ���12		
#define	MADD_B_DL_CHANNEL13		114		//		B�������ŵ���13		
#define	MADD_B_DL_CHANNEL14		115		//		B�������ŵ���14		
#define	MADD_B_DL_CHANNEL15		116		//		B�������ŵ���15		
#define	MADD_B_DL_CHANNEL16		117		//		B�������ŵ���16		
#define	MADD_B_UL_CHANNEL1		118		//		B�������ŵ���1		
#define	MADD_B_UL_CHANNEL2		119		//		B�������ŵ���2		
#define	MADD_B_UL_CHANNEL3		120		//		B�������ŵ���3		
#define	MADD_B_UL_CHANNEL4		121		//		B�������ŵ���4		
#define	MADD_B_UL_CHANNEL5		122		//		B�������ŵ���5		
#define	MADD_B_UL_CHANNEL6		123		//		B�������ŵ���6		
#define	MADD_B_UL_CHANNEL7		124		//		B�������ŵ���7		
#define	MADD_B_UL_CHANNEL8		125		//		B�������ŵ���8		
#define	MADD_B_UL_CHANNEL9		126		//		B�������ŵ���9		
#define	MADD_B_UL_CHANNEL10		127		//		B�������ŵ���10		
#define	MADD_B_UL_CHANNEL11		128		//		B�������ŵ���11		
#define	MADD_B_UL_CHANNEL12		129		//		B�������ŵ���12		
#define	MADD_B_UL_CHANNEL13		130		//		B�������ŵ���13		
#define	MADD_B_UL_CHANNEL14		131		//		B�������ŵ���14		
#define	MADD_B_UL_CHANNEL15		132		//		B�������ŵ���15		
#define	MADD_B_UL_CHANNEL16		133		//		B�������ŵ���16		
#define	MADD_B_DCH_MAX_POW1		134		//		B������ͨ������������1		
#define	MADD_B_DCH_MAX_POW2		135		//		B������ͨ������������2		
#define	MADD_B_DCH_MAX_POW3		136		//		B������ͨ������������3		
#define	MADD_B_DCH_MAX_POW4		137		//		B������ͨ������������4		
#define	MADD_B_DCH_MAX_POW5		138		//		B������ͨ������������5		
#define	MADD_B_DCH_MAX_POW6		139		//		B������ͨ������������6		
#define	MADD_B_DCH_MAX_POW7		140		//		B������ͨ������������7		
#define	MADD_B_DCH_MAX_POW8		141		//		B������ͨ������������8		
#define	MADD_B_DCH_MAX_POW9		142		//		B������ͨ������������9		
#define	MADD_B_DCH_MAX_POW10		143		//		B������ͨ������������10		
#define	MADD_B_DCH_MAX_POW11		144		//		B������ͨ������������11		
#define	MADD_B_DCH_MAX_POW12		145		//		B������ͨ������������12		
#define	MADD_B_DCH_MAX_POW13		146		//		B������ͨ������������13		
#define	MADD_B_DCH_MAX_POW14		147		//		B������ͨ������������14		
#define	MADD_B_DCH_MAX_POW15		148		//		B������ͨ������������15		
#define	MADD_B_DCH_MAX_POW16		149		//		B������ͨ������������16		
#define	MADD_B_UCH_MAX_POW1		150		//		B������ͨ��������빦��1		
#define	MADD_B_UCH_MAX_POW2		151		//		B������ͨ��������빦��2		
#define	MADD_B_UCH_MAX_POW3		152		//		B������ͨ��������빦��3		
#define	MADD_B_UCH_MAX_POW4		153		//		B������ͨ��������빦��4		
#define	MADD_B_UCH_MAX_POW5		154		//		B������ͨ��������빦��5		
#define	MADD_B_UCH_MAX_POW6		155		//		B������ͨ��������빦��6		
#define	MADD_B_UCH_MAX_POW7		156		//		B������ͨ��������빦��7		
#define	MADD_B_UCH_MAX_POW8		157		//		B������ͨ��������빦��8		
#define	MADD_B_UCH_MAX_POW9		158		//		B������ͨ��������빦��9		
#define	MADD_B_UCH_MAX_POW10		159		//		B������ͨ��������빦��10		
#define	MADD_B_UCH_MAX_POW11		160		//		B������ͨ��������빦��11		
#define	MADD_B_UCH_MAX_POW12		161		//		B������ͨ��������빦��12		
#define	MADD_B_UCH_MAX_POW13		162		//		B������ͨ��������빦��13		
#define	MADD_B_UCH_MAX_POW14		163		//		B������ͨ��������빦��14		
#define	MADD_B_UCH_MAX_POW15		164		//		B������ͨ��������빦��15		
#define	MADD_B_UCH_MAX_POW16		165		//		B������ͨ��������빦��16		
#define	MADD_B_DCH_POW1		166		//		B��ѡƵͨ�����й���1		
#define	MADD_B_DCH_POW2		167		//		B��ѡƵͨ�����й���2		
#define	MADD_B_DCH_POW3		168		//		B��ѡƵͨ�����й���3		
#define	MADD_B_DCH_POW4		169		//		B��ѡƵͨ�����й���4		
#define	MADD_B_DCH_POW5		170		//		B��ѡƵͨ�����й���5		
#define	MADD_B_DCH_POW6		171		//		B��ѡƵͨ�����й���6		
#define	MADD_B_DCH_POW7		172		//		B��ѡƵͨ�����й���7		
#define	MADD_B_DCH_POW8		173		//		B��ѡƵͨ�����й���8		
#define	MADD_B_DCH_POW9		174		//		B��ѡƵͨ�����й���9		
#define	MADD_B_DCH_POW10		175		//		B��ѡƵͨ�����й���10		
#define	MADD_B_DCH_POW11		176		//		B��ѡƵͨ�����й���11		
#define	MADD_B_DCH_POW12		177		//		B��ѡƵͨ�����й���12		
#define	MADD_B_DCH_POW13		178		//		B��ѡƵͨ�����й���13		
#define	MADD_B_DCH_POW14		179		//		B��ѡƵͨ�����й���14		
#define	MADD_B_DCH_POW15		180		//		B��ѡƵͨ�����й���15		
#define	MADD_B_DCH_POW16		181		//		B��ѡƵͨ�����й���16		
#define	MADD_B_UCH_POW1		182		//		B��ѡƵͨ�����й���1		
#define	MADD_B_UCH_POW2		183		//		B��ѡƵͨ�����й���2		
#define	MADD_B_UCH_POW3		184		//		B��ѡƵͨ�����й���3		
#define	MADD_B_UCH_POW4		185		//		B��ѡƵͨ�����й���4		
#define	MADD_B_UCH_POW5		186		//		B��ѡƵͨ�����й���5		
#define	MADD_B_UCH_POW6		187		//		B��ѡƵͨ�����й���6		
#define	MADD_B_UCH_POW7		188		//		B��ѡƵͨ�����й���7		
#define	MADD_B_UCH_POW8		189		//		B��ѡƵͨ�����й���8		
#define	MADD_B_UCH_POW9		190		//		B��ѡƵͨ�����й���9		
#define	MADD_B_UCH_POW10		191		//		B��ѡƵͨ�����й���10		
#define	MADD_B_UCH_POW11		192		//		B��ѡƵͨ�����й���11		
#define	MADD_B_UCH_POW12		193		//		B��ѡƵͨ�����й���12		
#define	MADD_B_UCH_POW13		194		//		B��ѡƵͨ�����й���13		
#define	MADD_B_UCH_POW14		195		//		B��ѡƵͨ�����й���14		
#define	MADD_B_UCH_POW15		196		//		B��ѡƵͨ�����й���15		
#define	MADD_B_UCH_POW16		197		//		B��ѡƵͨ�����й���16		
#define	MADD_B_UDPX_IN_GAIN		198		//		B������˫����˥��,		
#define	MADD_B_UDPX_OUT_GAIN		199		//		B�����˫����˥��,		
#define	MADD_B_DL_TOTAL_POW		200		//		B����������ܹ���		
#define	MADD_B_UL_TOTAL_POW		201		//		B�����������ܹ��ʣ�x10�㷨����һλС��		
#define	MADD_B_REC_DPX_IG		202		//		REC��B������˫����˥������������������㣬ֻ��,		
#define	MADD_B_REC_DPX_OG		203		//		REC��B�����˫����˥������������������㣬ֻ��,		
#define	MADD_C_DL_CHANNEL1		204		//		C�������ŵ���1		
#define	MADD_C_DL_CHANNEL2		205		//		C�������ŵ���2		
#define	MADD_C_DL_CHANNEL3		206		//		C�������ŵ���3		
#define	MADD_C_DL_CHANNEL4		207		//		C�������ŵ���4		
#define	MADD_C_DL_CHANNEL5		208		//		C�������ŵ���5		
#define	MADD_C_DL_CHANNEL6		209		//		C�������ŵ���6		
#define	MADD_C_DL_CHANNEL7		210		//		C�������ŵ���7		
#define	MADD_C_DL_CHANNEL8		211		//		C�������ŵ���8		
#define	MADD_C_DL_CHANNEL9		212		//		C�������ŵ���9		
#define	MADD_C_DL_CHANNEL10		213		//		C�������ŵ���10		
#define	MADD_C_UL_CHANNEL1		214		//		C�������ŵ���1		
#define	MADD_C_UL_CHANNEL2		215		//		C�������ŵ���2		
#define	MADD_C_UL_CHANNEL3		216		//		C�������ŵ���3		
#define	MADD_C_UL_CHANNEL4		217		//		C�������ŵ���4		
#define	MADD_C_UL_CHANNEL5		218		//		C�������ŵ���5		
#define	MADD_C_UL_CHANNEL6		219		//		C�������ŵ���6		
#define	MADD_C_UL_CHANNEL7		220		//		C�������ŵ���7		
#define	MADD_C_UL_CHANNEL8		221		//		C�������ŵ���8		
#define	MADD_C_UL_CHANNEL9		222		//		C�������ŵ���9		
#define	MADD_C_UL_CHANNEL10		223		//		C�������ŵ���10		
#define	MADD_C_DCH_MAX_POW1		224		//		C������ͨ������������1		
#define	MADD_C_DCH_MAX_POW2		225		//		C������ͨ������������2		
#define	MADD_C_DCH_MAX_POW3		226		//		C������ͨ������������3		
#define	MADD_C_DCH_MAX_POW4		227		//		C������ͨ������������4		
#define	MADD_C_DCH_MAX_POW5		228		//		C������ͨ������������5		
#define	MADD_C_DCH_MAX_POW6		229		//		C������ͨ������������6		
#define	MADD_C_DCH_MAX_POW7		230		//		C������ͨ������������7		
#define	MADD_C_DCH_MAX_POW8		231		//		C������ͨ������������8		
#define	MADD_C_DCH_MAX_POW9		232		//		C������ͨ������������9		
#define	MADD_C_DCH_MAX_POW10		233		//		C������ͨ������������10		
#define	MADD_C_DCH_MAX_POW11		234		//		C������ͨ������������11		
#define	MADD_C_DCH_MAX_POW12		235		//		C������ͨ������������12		
#define	MADD_C_DCH_MAX_POW13		236		//		C������ͨ������������13		
#define	MADD_C_DCH_MAX_POW14		237		//		C������ͨ������������14		
#define	MADD_C_DCH_MAX_POW15		238		//		C������ͨ������������15		
#define	MADD_C_DCH_MAX_POW16		239		//		C������ͨ������������16		
#define	MADD_C_UCH_MAX_POW1		240		//		C������ͨ��������빦��1		
#define	MADD_C_UCH_MAX_POW2		241		//		C������ͨ��������빦��2		
#define	MADD_C_UCH_MAX_POW3		242		//		C������ͨ��������빦��3		
#define	MADD_C_UCH_MAX_POW4		243		//		C������ͨ��������빦��4		
#define	MADD_C_UCH_MAX_POW5		244		//		C������ͨ��������빦��5		
#define	MADD_C_UCH_MAX_POW6		245		//		C������ͨ��������빦��6		
#define	MADD_C_UCH_MAX_POW7		246		//		C������ͨ��������빦��7		
#define	MADD_C_UCH_MAX_POW8		247		//		C������ͨ��������빦��8		
#define	MADD_C_UCH_MAX_POW9		248		//		C������ͨ��������빦��9		
#define	MADD_C_UCH_MAX_POW10		249		//		C������ͨ��������빦��10		
#define	MADD_C_UCH_MAX_POW11		250		//		C������ͨ��������빦��11		
#define	MADD_C_UCH_MAX_POW12		251		//		C������ͨ��������빦��12		
#define	MADD_C_UCH_MAX_POW13		252		//		C������ͨ��������빦��13		
#define	MADD_C_UCH_MAX_POW14		253		//		C������ͨ��������빦��14		
#define	MADD_C_UCH_MAX_POW15		254		//		C������ͨ��������빦��15		
#define	MADD_C_UCH_MAX_POW16		255		//		C������ͨ��������빦��16		
#define	MADD_C_DCH_POW1		256		//		C��ѡƵͨ�����й���1		
#define	MADD_C_DCH_POW2		257		//		C��ѡƵͨ�����й���2		
#define	MADD_C_DCH_POW3		258		//		C��ѡƵͨ�����й���3		
#define	MADD_C_DCH_POW4		259		//		C��ѡƵͨ�����й���4		
#define	MADD_C_DCH_POW5		260		//		C��ѡƵͨ�����й���5		
#define	MADD_C_DCH_POW6		261		//		C��ѡƵͨ�����й���6		
#define	MADD_C_DCH_POW7		262		//		C��ѡƵͨ�����й���7		
#define	MADD_C_DCH_POW8		263		//		C��ѡƵͨ�����й���8		
#define	MADD_C_DCH_POW9		264		//		C��ѡƵͨ�����й���9		
#define	MADD_C_DCH_POW10		265		//		C��ѡƵͨ�����й���10		
#define	MADD_C_DCH_POW11		266		//		C��ѡƵͨ�����й���11		
#define	MADD_C_DCH_POW12		267		//		C��ѡƵͨ�����й���12		
#define	MADD_C_DCH_POW13		268		//		C��ѡƵͨ�����й���13		
#define	MADD_C_DCH_POW14		269		//		C��ѡƵͨ�����й���14		
#define	MADD_C_DCH_POW15		270		//		C��ѡƵͨ�����й���15		
#define	MADD_C_DCH_POW16		271		//		C��ѡƵͨ�����й���16		
#define	MADD_C_UCH_POW1		272		//		C��ѡƵͨ�����й���1		
#define	MADD_C_UCH_POW2		273		//		C��ѡƵͨ�����й���2		
#define	MADD_C_UCH_POW3		274		//		C��ѡƵͨ�����й���3		
#define	MADD_C_UCH_POW4		275		//		C��ѡƵͨ�����й���4		
#define	MADD_C_UCH_POW5		276		//		C��ѡƵͨ�����й���5		
#define	MADD_C_UCH_POW6		277		//		C��ѡƵͨ�����й���6		
#define	MADD_C_UCH_POW7		278		//		C��ѡƵͨ�����й���7		
#define	MADD_C_UCH_POW8		279		//		C��ѡƵͨ�����й���8		
#define	MADD_C_UCH_POW9		280		//		C��ѡƵͨ�����й���9		
#define	MADD_C_UCH_POW10		281		//		C��ѡƵͨ�����й���10		
#define	MADD_C_UCH_POW11		282		//		C��ѡƵͨ�����й���11		
#define	MADD_C_UCH_POW12		283		//		C��ѡƵͨ�����й���12		
#define	MADD_C_UCH_POW13		284		//		C��ѡƵͨ�����й���13		
#define	MADD_C_UCH_POW14		285		//		C��ѡƵͨ�����й���14		
#define	MADD_C_UCH_POW15		286		//		C��ѡƵͨ�����й���15		
#define	MADD_C_UCH_POW16		287		//		C��ѡƵͨ�����й���16		
#define	MADD_C_UDPX_IN_GAIN		288		//		C������˫����˥��,		
#define	MADD_C_UDPX_OUT_GAIN		289		//		C�����˫����˥��,		
#define	MADD_C_DL_TOTAL_POW		290		//		C����������ܹ��ʣ�x10�㷨����һλС��		
#define	MADD_C_UL_TOTAL_POW		291		//		C�����������ܹ��ʣ�x10�㷨����һλС��		
#define	MADD_C_REC_DPX_IG		292		//		REC��C������˫����˥������������������㣬ֻ��,		
#define	MADD_C_REC_DPX_OG		293		//		REC��C�����˫����˥������������������㣬ֻ��,		
#define	MADD_D_DL_CHANNEL1		294		//		D�������ŵ���1		
#define	MADD_D_DL_CHANNEL2		295		//		D�������ŵ���2		
#define	MADD_D_DL_CHANNEL3		296		//		D�������ŵ���3		
#define	MADD_D_DL_CHANNEL4		297		//		D�������ŵ���4		
#define	MADD_D_DL_CHANNEL5		298		//		D�������ŵ���5		
#define	MADD_D_DL_CHANNEL6		299		//		D�������ŵ���6		
#define	MADD_D_DL_CHANNEL7		300		//		D�������ŵ���7		
#define	MADD_D_DL_CHANNEL8		301		//		D�������ŵ���8		
#define	MADD_D_DL_CHANNEL9		302		//		D�������ŵ���9		
#define	MADD_D_DL_CHANNEL10		303		//		D�������ŵ���10		
#define	MADD_D_UL_CHANNEL1		304		//		D�������ŵ���1		
#define	MADD_D_UL_CHANNEL2		305		//		D�������ŵ���2		
#define	MADD_D_UL_CHANNEL3		306		//		D�������ŵ���3		
#define	MADD_D_UL_CHANNEL4		307		//		D�������ŵ���4		
#define	MADD_D_UL_CHANNEL5		308		//		D�������ŵ���5		
#define	MADD_D_UL_CHANNEL6		309		//		D�������ŵ���6		
#define	MADD_D_UL_CHANNEL7		310		//		D�������ŵ���7		
#define	MADD_D_UL_CHANNEL8		311		//		D�������ŵ���8		
#define	MADD_D_UL_CHANNEL9		312		//		D�������ŵ���9		
#define	MADD_D_UL_CHANNEL10		313		//		D�������ŵ���10		
#define	MADD_D_DCH_MAX_POW1		314		//		D������ͨ������������1		
#define	MADD_D_DCH_MAX_POW2		315		//		D������ͨ������������2		
#define	MADD_D_DCH_MAX_POW3		316		//		D������ͨ������������3		
#define	MADD_D_DCH_MAX_POW4		317		//		D������ͨ������������4		
#define	MADD_D_DCH_MAX_POW5		318		//		D������ͨ������������5		
#define	MADD_D_DCH_MAX_POW6		319		//		D������ͨ������������6		
#define	MADD_D_DCH_MAX_POW7		320		//		D������ͨ������������7		
#define	MADD_D_DCH_MAX_POW8		321		//		D������ͨ������������8		
#define	MADD_D_DCH_MAX_POW9		322		//		D������ͨ������������9		
#define	MADD_D_DCH_MAX_POW10		323		//		D������ͨ������������10		
#define	MADD_D_DCH_MAX_POW11		324		//		D������ͨ������������11		
#define	MADD_D_DCH_MAX_POW12		325		//		D������ͨ������������12		
#define	MADD_D_DCH_MAX_POW13		326		//		D������ͨ������������13		
#define	MADD_D_DCH_MAX_POW14		327		//		D������ͨ������������14		
#define	MADD_D_DCH_MAX_POW15		328		//		D������ͨ������������15		
#define	MADD_D_DCH_MAX_POW16		329		//		D������ͨ������������16		
#define	MADD_D_UCH_MAX_POW1		330		//		D������ͨ��������빦��1		
#define	MADD_D_UCH_MAX_POW2		331		//		D������ͨ��������빦��2		
#define	MADD_D_UCH_MAX_POW3		332		//		D������ͨ��������빦��3		
#define	MADD_D_UCH_MAX_POW4		333		//		D������ͨ��������빦��4		
#define	MADD_D_UCH_MAX_POW5		334		//		D������ͨ��������빦��5		
#define	MADD_D_UCH_MAX_POW6		335		//		D������ͨ��������빦��6		
#define	MADD_D_UCH_MAX_POW7		336		//		D������ͨ��������빦��7		
#define	MADD_D_UCH_MAX_POW8		337		//		D������ͨ��������빦��8		
#define	MADD_D_UCH_MAX_POW9		338		//		D������ͨ��������빦��9		
#define	MADD_D_UCH_MAX_POW10		339		//		D������ͨ��������빦��10		
#define	MADD_D_UCH_MAX_POW11		340		//		D������ͨ��������빦��11		
#define	MADD_D_UCH_MAX_POW12		341		//		D������ͨ��������빦��12		
#define	MADD_D_UCH_MAX_POW13		342		//		D������ͨ��������빦��13		
#define	MADD_D_UCH_MAX_POW14		343		//		D������ͨ��������빦��14		
#define	MADD_D_UCH_MAX_POW15		344		//		D������ͨ��������빦��15		
#define	MADD_D_UCH_MAX_POW16		345		//		D������ͨ��������빦��16		
#define	MADD_D_DCH_POW1		346		//		D��ѡƵͨ�����й���1		
#define	MADD_D_DCH_POW2		347		//		D��ѡƵͨ�����й���2		
#define	MADD_D_DCH_POW3		348		//		D��ѡƵͨ�����й���3		
#define	MADD_D_DCH_POW4		349		//		D��ѡƵͨ�����й���4		
#define	MADD_D_DCH_POW5		350		//		D��ѡƵͨ�����й���5		
#define	MADD_D_DCH_POW6		351		//		D��ѡƵͨ�����й���6		
#define	MADD_D_DCH_POW7		352		//		D��ѡƵͨ�����й���7		
#define	MADD_D_DCH_POW8		353		//		D��ѡƵͨ�����й���8		
#define	MADD_D_DCH_POW9		354		//		D��ѡƵͨ�����й���9		
#define	MADD_D_DCH_POW10		355		//		D��ѡƵͨ�����й���10		
#define	MADD_D_DCH_POW11		356		//		D��ѡƵͨ�����й���11		
#define	MADD_D_DCH_POW12		357		//		D��ѡƵͨ�����й���12		
#define	MADD_D_DCH_POW13		358		//		D��ѡƵͨ�����й���13		
#define	MADD_D_DCH_POW14		359		//		D��ѡƵͨ�����й���14		
#define	MADD_D_DCH_POW15		360		//		D��ѡƵͨ�����й���15		
#define	MADD_D_DCH_POW16		361		//		D��ѡƵͨ�����й���16		
#define	MADD_D_UCH_POW1		362		//		D��ѡƵͨ�����й���1		
#define	MADD_D_UCH_POW2		363		//		D��ѡƵͨ�����й���2		
#define	MADD_D_UCH_POW3		364		//		D��ѡƵͨ�����й���3		
#define	MADD_D_UCH_POW4		365		//		D��ѡƵͨ�����й���4		
#define	MADD_D_UCH_POW5		366		//		D��ѡƵͨ�����й���5		
#define	MADD_D_UCH_POW6		367		//		D��ѡƵͨ�����й���6		
#define	MADD_D_UCH_POW7		368		//		D��ѡƵͨ�����й���7		
#define	MADD_D_UCH_POW8		369		//		D��ѡƵͨ�����й���8		
#define	MADD_D_UCH_POW9		370		//		D��ѡƵͨ�����й���9		
#define	MADD_D_UCH_POW10		371		//		D��ѡƵͨ�����й���10		
#define	MADD_D_UCH_POW11		372		//		D��ѡƵͨ�����й���11		
#define	MADD_D_UCH_POW12		373		//		D��ѡƵͨ�����й���12		
#define	MADD_D_UCH_POW13		374		//		D��ѡƵͨ�����й���13		
#define	MADD_D_UCH_POW14		375		//		D��ѡƵͨ�����й���14		
#define	MADD_D_UCH_POW15		376		//		D��ѡƵͨ�����й���15		
#define	MADD_D_UCH_POW16		377		//		D��ѡƵͨ�����й���16		
#define	MADD_D_UDPX_IN_GAIN		378		//		D������˫����˥��,		
#define	MADD_D_UDPX_OUT_GAIN		379		//		D�����˫����˥��,		
#define	MADD_D_DL_TOTAL_POW		380		//		D����������ܹ���		
#define	MADD_D_UL_TOTAL_POW		381		//		D�����������ܹ��ʣ�x10�㷨����һλС��		
#define	MADD_D_REC_DPX_IG		382		//		REC��D������˫����˥������������������㣬ֻ��,		
#define	MADD_D_REC_DPX_OG		383		//		REC��D�����˫����˥������������������㣬ֻ��,		
#define	MADD_REC_TO_RE_DELAY		384		//		REC��RE�Ĺ�����ʱ		
#define	MADD_RE_RF_DELAY		385						
#define	MADD_MAX_T14		386		//		��������ʱ,��λ10ns		
#define	MADD_DL_DELAY_OFFSET		387		//		������ʱƫ����		
#define	MADD_UL_DELAY_OFFSET		388		//		������ʱƫ����		
#define	MADD_PRI_SOFT_V		389		//		����汾�ţ���ASCII�룩		
#define	MADD_PRI_HARD_V		390		//		PCB�汾��(��ASCII��)		
#define	MADD_TD_1ST_CP_TIME		391		//		TD��1ת����ʱ��,ns,		
#define	MADD_TD_2ND_CP_TIME		392		//		TD��2ת����ʱ��,ns,		
#define	MADD_TD_LNA_ON_TIME		393		//		LNA�����ٺ�DN_PA�رյı���ʱ��ns		
#define	MADD_TD_LNA_OFF_TIME		394		//		LNA�رճ�ǰDN_PA�����ı���ʱ��ns		
#define	MADD_TD_SLOT1_UPOW		395		//		TDʱ϶1���������⹦��		
#define	MADD_TD_SLOT2_UPOW		396		//		TDʱ϶2���������⹦��		
#define	MADD_TD_SLOT3_UPOW		397		//		TDʱ϶3���������⹦��		
#define	MADD_TD_SLOT4_UPOW		398		//		TDʱ϶4���������⹦��		
#define	MADD_TD_SLOT5_UPOW		399		//		TDʱ϶5���������⹦��		
#define	MADD_TD_SLOT6_UPOW		400		//		TDʱ϶6���������⹦��		
#define	MADD_TD_SLOT7_UPOW		401		//		TDʱ϶7���������⹦��		
#define	MADD_TD_SLOT1_DPOW		402		//		TDʱ϶1���������⹦��		
#define	MADD_TD_SLOT2_DPOW		403		//		TDʱ϶2���������⹦��		
#define	MADD_TD_SLOT3_DPOW		404		//		TDʱ϶3���������⹦��		
#define	MADD_TD_SLOT4_DPOW		405		//		TDʱ϶4���������⹦��		
#define	MADD_TD_SLOT5_DPOW		406		//		TDʱ϶5���������⹦��		
#define	MADD_TD_SLOT6_DPOW		407		//		TDʱ϶6���������⹦��		
#define	MADD_TD_SLOT7_DPOW		408		//		TDʱ϶7���������⹦��		
#define	MADD_FPS_S1		409		//		Ƶ�����ط�Χ1��ʼƵ��		
#define	MADD_FPS_E1		410		//		Ƶ�����ط�Χ1����Ƶ��		
#define	MADD_FPS_S2		411		//		Ƶ�����ط�Χ2��ʼƵ��		
#define	MADD_FPS_E2		412		//		Ƶ�����ط�Χ2����Ƶ��		
#define	MADD_FPS_BCCH_LK_SET		413		//		Ƶ������:		
#define	MADD_FPS_CID_LK_SET		414		//		Ƶ������:		
#define	MADD_FPS_BCCH_FC_M		415		//		Ƶ������:		
#define	MADD_FPS_CA_FC_0		416		//		Ƶ������:		
#define	MADD_FPS_CA_FC_1		417		//		Ƶ������:		
#define	MADD_FPS_CA_FC_2		418		//		Ƶ������:		
#define	MADD_FPS_CA_FC_3		419		//		Ƶ������:		
#define	MADD_FPS_CA_FC_4		420		//		Ƶ������:		
#define	MADD_FPS_CA_FC_5		421		//		Ƶ������:		
#define	MADD_FPS_CA_FC_6		422		//		Ƶ������:		
#define	MADD_FPS_CA_FC_7		423		//		Ƶ������:		
#define	MADD_FPS_CA_FC_8		424		//		Ƶ������:		
#define	MADD_FPS_CA_FC_9		425		//		Ƶ������:		
#define	MADD_FPS_CA_FC_10		426		//		Ƶ������:		
#define	MADD_FPS_CA_FC_11		427		//		Ƶ������:		
#define	MADD_FPS_CA_FC_12		428		//		Ƶ������:		
#define	MADD_FPS_CA_FC_13		429		//		Ƶ������:		
#define	MADD_FPS_CA_FC_14		430		//		Ƶ������:		
#define	MADD_FPS_CA_FC_15		431		//		Ƶ������:		
#define	MADD_FPS_BCCH_FC_1		432		//		Ƶ������:		
#define	MADD_FPS_BCCH_FC_2		433		//		Ƶ������:		
#define	MADD_FPS_BCCH_FC_3		434		//		Ƶ������:		
#define	MADD_FPS_BCCH_FC_4		435		//		Ƶ������:		
#define	MADD_FPS_BCCH_FC_5		436		//		Ƶ������:		
#define	MADD_FPS_BCCH_FC_6		437		//		Ƶ������:		
#define	MADD_FPS_AREA_ID		438		//		Ƶ������:		
#define	MADD_FPS_CID		439		//		Ƶ������:		
#define	MADD_FPS_CID_1		440		//		Ƶ������:		
#define	MADD_FPS_CID_2		441		//		Ƶ������:		
#define	MADD_FPS_CID_3		442		//		Ƶ������:		
#define	MADD_FPS_CID_4		443		//		Ƶ������:		
#define	MADD_FPS_CID_5		444		//		Ƶ������:		
#define	MADD_FPS_CID_6		445		//		Ƶ������:		
#define	MADD_A_EXPA_IDRAIN_SET		446		//		΢����:		
#define	MADD_TD_SLOT1_DPOW_OVER_THR		447		//625		//�������뵼Ƶ����������		
#define	MADD_TD_SLOT1_DPOW_OWE_THR		448		//626		//�������뵼ƵǷ��������		
#define	MADD_A_INPUT_TOTAL_DPOW_OVER_THR		449		//				
#define	MADD_A_INPUT_TOTAL_DPOW_OWE_THR		450		//				
#define	MADD_B_INPUT_TOTAL_DPOW_OVER_THR		451		//				
#define	MADD_B_INPUT_TOTAL_DPOW_OWE_THR		452		//				
#define	MADD_C_INPUT_TOTAL_DPOW_OVER_THR		453		//				
#define	MADD_C_INPUT_TOTAL_DPOW_OWE_THR		454		//				
#define	MADD_D_INPUT_TOTAL_DPOW_OVER_THR		455		//				
#define	MADD_D_INPUT_TOTAL_DPOW_OWE_THR		456		//				
#define	MADD_REE_A_DL_OUT_TOTAL_POW_DETECT		457		//A��RE��������ܹ���				
#define	MADD_A_RE_LOCAL_ST_ALARM		458		//���ǵ�Ԫ���ظ澯״̬				
#define	MADD_REE_B_DL_OUT_TOTAL_POW_DETECT		459		//B��RE��������ܹ���				
#define	MADD_B_RE_LOCAL_ST_ALARM		460		//���ǵ�Ԫ���ظ澯״̬				
#define	MADD_REE_C_DL_OUT_TOTAL_POW_DETECT		461		//A��RE��������ܹ���				
#define	MADD_C_RE_LOCAL_ST_ALARM		462		//���ǵ�Ԫ���ظ澯״̬				
#define	MADD_REE_D_DL_OUT_TOTAL_POW_DETECT		463		//D��RE��������ܹ���				
#define	MADD_D_RE_LOCAL_ST_ALARM		464		//���ǵ�Ԫ���ظ澯״̬	
#define	MADD_C_TD_1ST_CP_TIME		465		//		TD��1ת����ʱ��,ns,	
#define	MADD_C_TD_2ND_CP_TIME		466		//		TD��2ת����ʱ��,ns,	
#define	MADD_C_TD_LNA_ON_TIME		467		//		LNA�����ٺ�DN_PA�رյı���ʱ��ns	
#define	MADD_C_TD_LNA_OFF_TIME		468		//		LNA�رճ�ǰDN_PA�����ı���ʱ��ns	
#define	MADD_C_TD_SLOT1_DPOW_OVER_THR		469		//625		//�������뵼Ƶ����������	
#define	MADD_C_TD_SLOT1_DPOW_OWE_THR		470		//626		//�������뵼ƵǷ��������	
#define	MADD_D_TD_1ST_CP_TIME		471		//		TD��1ת����ʱ��,ns,	
#define	MADD_D_TD_2ND_CP_TIME		472		//		TD��2ת����ʱ��,ns,	
#define	MADD_D_TD_LNA_ON_TIME		473		//		LNA�����ٺ�DN_PA�رյı���ʱ��ns	
#define	MADD_D_TD_LNA_OFF_TIME		474		//		LNA�رճ�ǰDN_PA�����ı���ʱ��ns	
#define	MADD_D_TD_SLOT1_DPOW_OVER_THR		475		//625		//�������뵼Ƶ����������	
#define	MADD_D_TD_SLOT1_DPOW_OWE_THR		476		//626		//�������뵼ƵǷ��������	
#define	MADD_C_TD_SLOT1_POW		477		//		TDʱ϶1�����⹦��	
#define	MADD_C_TD_SLOT2_POW		478		//		TDʱ϶2�����⹦��	
#define	MADD_C_TD_SLOT3_POW		479		//		TDʱ϶3�����⹦��	
#define	MADD_C_TD_SLOT4_POW		480		//		TDʱ϶4�����⹦��	
#define	MADD_C_TD_SLOT5_POW		481		//		TDʱ϶5�����⹦��	
#define	MADD_C_TD_SLOT6_POW		482		//		TDʱ϶6�����⹦��	
#define	MADD_C_TD_SLOT7_POW		483		//		TDʱ϶7�����⹦��	
#define	MADD_C_TD_SLOT8_POW		484		//		TDʱ϶8�����⹦��	
#define	MADD_C_TD_SLOT9_POW		485		//		TDʱ϶9�����⹦��	
#define	MADD_C_TD_SLOT10_POW		486		//		TDʱ϶10�����⹦��	
#define	MADD_C_TD_SLOT11_POW		487		//		TDʱ϶11�����⹦��	
#define	MADD_C_TD_SLOT12_POW		488		//		TDʱ϶12�����⹦��	
#define	MADD_C_TD_SLOT13_POW		489		//		TDʱ϶13�����⹦��	
#define	MADD_C_TD_SLOT14_POW		490		//		TDʱ϶14�����⹦��	
#define	MADD_C_TD_SLOT15_POW		491		//		TDʱ϶15�����⹦��	
#define	MADD_C_TD_SLOT16_POW		492		//		TDʱ϶16�����⹦��	
#define	MADD_C_TD_SLOT17_POW		493		//		TDʱ϶17�����⹦��	
#define	MADD_C_TD_SLOT18_POW		494		//		TDʱ϶18�����⹦��	
#define	MADD_C_TD_SLOT19_POW		495		//		TDʱ϶19�����⹦��	
#define	MADD_C_TD_SLOT20_POW		496		//		TDʱ϶20�����⹦��	
#define	MADD_D_TD_SLOT1_POW		497		//		TDʱ϶1�����⹦��	
#define	MADD_D_TD_SLOT2_POW		498		//		TDʱ϶2�����⹦��	
#define	MADD_D_TD_SLOT3_POW		499		//		TDʱ϶3�����⹦��	
#define	MADD_D_TD_SLOT4_POW		500		//		TDʱ϶4�����⹦��	
#define	MADD_D_TD_SLOT5_POW		501		//		TDʱ϶5�����⹦��	
#define	MADD_D_TD_SLOT6_POW		502		//		TDʱ϶6�����⹦��	
#define	MADD_D_TD_SLOT7_POW		503		//		TDʱ϶7�����⹦��	
#define	MADD_D_TD_SLOT8_POW		504		//		TDʱ϶8�����⹦��	
#define	MADD_D_TD_SLOT9_POW		505		//		TDʱ϶9�����⹦��	
#define	MADD_D_TD_SLOT10_POW		506		//		TDʱ϶10�����⹦��	
#define	MADD_D_TD_SLOT11_POW		507		//		TDʱ϶11�����⹦��	
#define	MADD_D_TD_SLOT12_POW		508		//		TDʱ϶12�����⹦��	
#define	MADD_D_TD_SLOT13_POW		509		//		TDʱ϶13�����⹦��	
#define	MADD_D_TD_SLOT14_POW		510		//		TDʱ϶14�����⹦��	
#define	MADD_D_TD_SLOT15_POW		511		//		TDʱ϶15�����⹦��	
#define	MADD_D_TD_SLOT16_POW		512		//		TDʱ϶16�����⹦��	
#define	MADD_D_TD_SLOT17_POW		513		//		TDʱ϶17�����⹦��	
#define	MADD_D_TD_SLOT18_POW		514		//		TDʱ϶18�����⹦��	
#define	MADD_D_TD_SLOT19_POW		515		//		TDʱ϶19�����⹦��	
#define	MADD_D_TD_SLOT20_POW		516		//		TDʱ϶20�����⹦��	
#define	MADD_DL_DELAY_OFFSET_B		517		//		������ʱƫ����		
#define	MADD_DL_DELAY_OFFSET_C		518		//		������ʱƫ����		
#define	MADD_DL_DELAY_OFFSET_D		519		//		������ʱƫ����		
#define	MADD_PARA_VGS_A		            520		//	         A��դѹ		
#define	MADD_PARA_VGS_B          		521		//		 B��դѹ		
#define	MADD_PARA_VGS_C          		522		//		 C��դѹ
#define	MADD_PARA_VGS_D          		523		//		 D��դѹ
#define	MADD_PARA_VGS_COMP_A		        524	//	     A��դѹ		
#define	MADD_PARA_VGS_COMP_B          		525		//		 B��դѹ		
#define	MADD_PARA_VGS_COMP_C          		526		//		 C��դѹ
#define	MADD_PARA_VGS_COMP_D          		527		//		 C��դѹ
#define	MADD_ATT_DATA_COMP_A		528				//ATT��������
#define	MADD_ATT_DATA_COMP_B		529				//ATT��������
#define	MADD_ATT_DATA_COMP_C		530				//ATT��������
#define	MADD_ATT_DATA_COMP_D		531				//ATT��������
#define	MADD_MAX_T14_A		532		//	��������ʱ
#define	MADD_MAX_T14_B		533		//	��������ʱ
#define	MADD_MAX_T14_C		534		//	��������ʱ
#define	MADD_MAX_T14_D		535		//	��������ʱ
#define	MADD_ERL_JG_A		536// A�λ�����ͳ�ƽ��
#define	MADD_ERL_JG_C		537
#define	MADD_ERL_JG_D		538
#define	MADD_MOVE_CENTER_FRE_D		539//�ı���������Ƶ��
#define	MADD_MOVE_CENTER_FRE_U		540//�ı���������Ƶ��

#define	SYS_PARAM_2B_COUNT				541//					

				


// ������ַ����==================================================== 4b
#define PARA_DEV_ADDR	0x8893	//	�豸·�ɵǼǵ�ַ
#define PARA_BIT_ERR_COUNT	0	// 	���ݰ�����ͳ��
#define PARA_TOPO_CHG_COUNT	0	// ���˱仯����
#define PARA_FPGA_PKT_COUNT	0	// FPGA���ݰ���������
#define PARA_OPT_RE_COUNT1	0x88ee	// Զ�˻��ڵ����1
#define PARA_OPT_RE_COUNT2	0x88ef	// Զ�˻��ڵ����2
#define PARA_OPS_PORT			0x88ec	// ��ڵĶԶ˹�ں�


// ���ʵ�ַ>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 4B
#define MADD_DEV_ADDR			0	// �豸·�ɵǼǵ�ַ
#define MADD_BIT_ERR_COUNT	1	// ���ݰ�����ͳ��
#define MADD_TOPO_CHG_COUNT	2	// ���˱仯����
#define MADD_FPGA_PKT_COUNT	3	// FPGA���ݰ���������
#define MADD_OPT_RE_COUNT1	4	// Զ�˻��ڵ����1
#define MADD_OPT_RE_COUNT2	5	// Զ�˻��ڵ����2
#define MADD_OPS_PORT			6	// ��ڵĶԶ˹�ں�

#define SYS_PARAM_4B_COUNT	7

// ������ַ����==================================================== ASC
#define PARA_PRI_TYPE	0xf001	//	ģ������(��ASCII��)
#define PARA_PRI_ID	0xf000	//	ģ��ʶ��ID��(��ASCII��)
#define PARA_PRI_MCU_DATE	0xf02a	//	MCU��������(��ASCII��)
#define PARA_PRI_GL_ROM_ID	0xf029	//	Ψһʶ��ID(��ASCII��)
#define PARA_PRI_GL_SEQ	0xf028	//	�����������к�(��ASCII��)
#define PARA_PRI_GL_PRODUCT	0xf027	//	���Ҳ�Ʒ���(��ASCII��)
#define PARA_PRI_SEQ	0xf019	//	�������к�(��ASCII��)
#define PARA_MODULE_HRI_STR	0	//	IDʶ���ַ���(��ASCII��)
#define PARA_PRI_FPGA_DATE	0xf02b	//	FPGA��������(��ASCII��)
#define PARA_PRI_FPGA2_DATE	0xf02c	//	FPGA2��������(��ASCII��)
#define PARA_A_PRI_9363_UPDATA_DATE	(0)	//	9363�����ļ���������(��ASCII��)
#define PARA_B_PRI_9363_UPDATA_DATE	(0)	//	9363�����ļ���������(��ASCII��)
#define PARA_C_PRI_9363_UPDATA_DATE	(0)	//	9363�����ļ���������(��ASCII��)
#define PARA_REE_POSITION_INF		(0xF01E)	//	��չ��Ԫλ����Ϣ���豸����λ�ã��������ַ��
#define PARA_MCU_VERSION_NEW		(0) //  MCU�µİ汾��Ϣ

// ���ʵ�ַ>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ASC
#define MADD_PRI_TYPE			(0)	//	ģ������(��ASCII��)
#define MADD_PRI_ID				(MADD_PRI_TYPE+1)	//	ģ��ʶ��ID��(��ASCII��)
#define MADD_PRI_MCU_DATE		(MADD_PRI_ID+1)	//	MCU��������(��ASCII��)
#define MADD_PRI_GL_ROM_ID	(MADD_PRI_MCU_DATE+1)	//	Ψһʶ��ID(��ASCII��)
#define MADD_PRI_GL_SEQ		(MADD_PRI_GL_ROM_ID+1)	//	�����������к�(��ASCII��)
#define MADD_PRI_GL_PRODUCT	(MADD_PRI_GL_SEQ+1)	//	���Ҳ�Ʒ���(��ASCII��)
#define MADD_PRI_SEQ			(MADD_PRI_GL_PRODUCT+1)	//	�������к�(��ASCII��)
#define MADD_MODULE_HRI_STR	(MADD_PRI_SEQ+1)	//	IDʶ���ַ���(��ASCII��)
#define MADD_PRI_FPGA_DATE	(MADD_MODULE_HRI_STR+1)	//	FPGA��������(��ASCII��)
#define MADD_PRI_FPGA2_DATE	(MADD_PRI_FPGA_DATE+1)	//	FPGA2��������(��ASCII��)
#define MADD_A_PRI_9363_UPDATA_DATE	(MADD_PRI_FPGA2_DATE+1)	//	9363�����ļ���������(��ASCII��)
#define MADD_B_PRI_9363_UPDATA_DATE	(MADD_A_PRI_9363_UPDATA_DATE+1)	//	9363�����ļ���������(��ASCII��)
#define MADD_C_PRI_9363_UPDATA_DATE	(MADD_B_PRI_9363_UPDATA_DATE+1)	//	9363�����ļ���������(��ASCII��)
#define MADD_REE_POSITION_INF		(MADD_C_PRI_9363_UPDATA_DATE+1)	//	��չ��Ԫλ����Ϣ���豸����λ�ã��������ַ��
#define MADD_MCU_VERSION_NEW		(MADD_REE_POSITION_INF+1) //  MCU�µİ汾��Ϣ

#define SYS_PARAM_ASC_COUNT	(MADD_MCU_VERSION_NEW+1)



//****************************EU����1�ֽ�********************************
#define PARA_EU_ALARM_FLAG1     			0	//EU1�澯ָʾ		
#define PARA_EU_ALARM_FLAG2     			0	//EU2�澯ָʾ		
#define PARA_EU_ALARM_FLAG3     			0	//EU3�澯ָʾ		
#define PARA_EU_ALARM_FLAG4     			0	//EU4�澯ָʾ		
#define PARA_EU_ALARM_FLAG5     			0	//EU5�澯ָʾ		
#define PARA_EU_ALARM_FLAG6     			0	//EU6�澯ָʾ		
#define PARA_EU_ALARM_FLAG7     			0	//EU7�澯ָʾ		
#define PARA_EU_ALARM_FLAG8     			0	//EU8�澯ָʾ		


#define MADD_EU_ALARM_FLAG1     			0	//EU1�澯ָʾ		
#define MADD_EU_ALARM_FLAG2     			1	//EU2�澯ָʾ		
#define MADD_EU_ALARM_FLAG3     			2	//EU3�澯ָʾ		
#define MADD_EU_ALARM_FLAG4     			3	//EU4�澯ָʾ		
#define MADD_EU_ALARM_FLAG5     			4	//EU5�澯ָʾ		
#define MADD_EU_ALARM_FLAG6     			5	//EU6�澯ָʾ		
#define MADD_EU_ALARM_FLAG7     			6	//EU7�澯ָʾ		
#define MADD_EU_ALARM_FLAG8     			7	//EU8�澯ָʾ		



#define	SYS_PARAM_EU_1B_COUNT						8


//****************************EU����2�ֽ�********************************
#define PARA_EU_ALARM_CONTENT1     			0	//EU1�澯����		
#define PARA_EU_ALARM_CONTENT2     			0	//EU2�澯����		
#define PARA_EU_ALARM_CONTENT3     			0	//EU3�澯����		
#define PARA_EU_ALARM_CONTENT4     			0	//EU4�澯����		
#define PARA_EU_ALARM_CONTENT5     			0	//EU5�澯����		
#define PARA_EU_ALARM_CONTENT6     			0	//EU6�澯����		
#define PARA_EU_ALARM_CONTENT7     			0	//EU7�澯����		
#define PARA_EU_ALARM_CONTENT8     			0	//EU8�澯����
#define PARA_EU_RUALARM_FLAG1     				8	//EU1�µ�16��RU�澯ָʾ		
#define PARA_EU_RUALARM_FLAG2     				9	//EU2�µ�16��RU�澯ָʾ		
#define PARA_EU_RUALARM_FLAG3     				10	//EU3�µ�16��RU�澯ָʾ		
#define PARA_EU_RUALARM_FLAG4     				11	//EU4�µ�16��RU�澯ָʾ		
#define PARA_EU_RUALARM_FLAG5     				12	//EU5�µ�16��RU�澯ָʾ		
#define PARA_EU_RUALARM_FLAG6     				13	//EU6�µ�16��RU�澯ָʾ		
#define PARA_EU_RUALARM_FLAG7     				14	//EU7�µ�16��RU�澯ָʾ		
#define PARA_EU_RUALARM_FLAG8     				15	//EU8�µ�16��RU�澯ָʾ	



#define MADD_EU_ALARM_CONTENT1     			0	//EU1�澯����		
#define MADD_EU_ALARM_CONTENT2     			1	//EU2�澯����		
#define MADD_EU_ALARM_CONTENT3     			2	//EU3�澯����		
#define MADD_EU_ALARM_CONTENT4     			3	//EU4�澯����		
#define MADD_EU_ALARM_CONTENT5     			4	//EU5�澯����		
#define MADD_EU_ALARM_CONTENT6     			5	//EU6�澯����		
#define MADD_EU_ALARM_CONTENT7     			6	//EU7�澯����		
#define MADD_EU_ALARM_CONTENT8     			7	//EU8�澯����

#define MADD_EU_RUALARM_FLAG1     				8	//EU1�µ�16��RU�澯ָʾ		
#define MADD_EU_RUALARM_FLAG2     				9	//EU2�µ�16��RU�澯ָʾ		
#define MADD_EU_RUALARM_FLAG3     				10	//EU3�µ�16��RU�澯ָʾ		
#define MADD_EU_RUALARM_FLAG4     				11	//EU4�µ�16��RU�澯ָʾ		
#define MADD_EU_RUALARM_FLAG5     				12	//EU5�µ�16��RU�澯ָʾ		
#define MADD_EU_RUALARM_FLAG6     				13	//EU6�µ�16��RU�澯ָʾ		
#define MADD_EU_RUALARM_FLAG7     				14	//EU7�µ�16��RU�澯ָʾ		
#define MADD_EU_RUALARM_FLAG8     				15	//EU8�µ�16��RU�澯ָʾ	


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
//	9363_A�����ļ���������(��ASCII��)
extern UCHAR8 str_a_pri_9363_date[];
//	9363_B�����ļ���������(��ASCII��)
extern UCHAR8 str_b_pri_9363_date[];
//	9363_C�����ļ���������(��ASCII��)
extern UCHAR8 str_c_pri_9363_date[];
//	ree�豸λ����Ϣ
extern UCHAR8 str_mau_position_inf[];
// MCU����汾(��ASCII��)
extern UCHAR8 str_pri_mcu_version_new[];



extern const UCHAR8 calc_type[];
extern _T_PARAM_1B sys_param_1b[];
extern _T_PARAM_2B sys_param_2b[];
extern _T_PARAM_4B sys_param_4b[];
extern _T_PARAM_ASC sys_param_asc[];

extern _T_PARAM_1B sys_param_eu_1b[];
extern _T_PARAM_2B sys_param_eu_2b[];


#endif


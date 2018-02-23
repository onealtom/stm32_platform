//20140209
/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :fpga.h
* Description :FPGA������غ���
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			��ʼ�汾
**************************************************************/
#ifndef _FPGA_H
#define _FPGA_H

#include "ex_conf.h"

typedef struct _S_FPGA_CONFIG
{
	UCHAR8 a_net_type;		// A��ͨѶ��ʽ
	UCHAR8 a_ultra_info;	// A�θ�����Ϣ
	UCHAR8 b_net_type;		// B��ͨѶ��ʽ
	UCHAR8 b_ultra_info;	// B�θ�����Ϣ
	UCHAR8 c_net_type;		// C��ͨѶ��ʽ
	UCHAR8 c_ultra_info;	// C�θ�����Ϣ
	UCHAR8 d_net_type;		// D��ͨѶ��ʽ
	UCHAR8 d_ultra_info;	// D�θ�����Ϣ	
	
	UCHAR8 wlan_en;			// 1-WLAN����ʹ��

	FLOAT32 a_fpga_data_clk; //A��FPGA����ʱ��
	FLOAT32 b_fpga_data_clk; //B��FPGA����ʱ��
	FLOAT32 c_fpga_data_clk; //C��FPGA����ʱ��
	FLOAT32 d_fpga_data_clk; //D��FPGA����ʱ��

	
	UCHAR8 a_9363; //A��9363ѡ��
	UCHAR8 b_9363; //B��9363ѡ��
	UCHAR8 c_9363; //C��9363ѡ��
	UCHAR8 d_9363; //D��9363ѡ��
	

#if	0
	FLOAT32 a_dch_avg_pow;	// �������ͨ��ƽ������
	FLOAT32 a_uch_avg_pow;	// �������ͨ��ƽ������
	
	FLOAT32 b_dch_avg_pow;	// �������ͨ��ƽ������
	FLOAT32 b_uch_avg_pow;	// �������ͨ��ƽ������

	FLOAT32 c_dch_avg_pow;	// �������ͨ��ƽ������
	FLOAT32 c_uch_avg_pow;	// �������ͨ��ƽ������
	
	FLOAT32 d_dch_avg_pow;	// �������ͨ��ƽ������
	FLOAT32 d_uch_avg_pow;	// �������ͨ��ƽ������	
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

//����ACDU�汾���º�Ҫһ���



#define ATT_ADJ_ST_IDLE				0  //����У��
#define ATT_ADJ_ST_MAX_ADJ			1  //��ʼ��У��
#define ATT_ADJ_ST_WAIT_MAX_PSF		2  //�ȴ��������У����ѡƵ����
#define ATT_ADJ_ST_STEP_ADJ			3  //��ʼ����У�� 
#define ATT_ADJ_ST_WAIT_STEP_PSF	4  //�ȴ����ز���У����ѡƵ����

#define ATT_UL_ADJ		0
#define ATT_DL_ADJ		1

#define FPGA_MSG_BUFF_SIZE	191		// FPGA��Ϣ�����С
#define FPGA_MSG_FRAME_LEN	(FPGA_MSG_BUFF_SIZE-1)		// FPGA����֡�����ֽڳ���
#define FPGA_MSG_ADDR_LEN	(6)		//�����ݰ��ӵڶ�������ʼ������Ŀ�ĵ�ַ��Դ��ַ������Ϊ8

#define FPGA_FRAME_FIFO_SIZE	200		// FPGA����֡FIFO�ֽڳ��ȣ���ȡ���ݵ�ʱ��һ��Ҫ������֡FIFOȫ������

#define FPGA_LDST_OK			0x0000	// FPGA�Ѽ��ز��ɹ���ʼ��
#define FPGA_LDST_NO_FILE		0x0001	// �Ҳ���FPGA�����ļ�
#define FPGA_LDST_FAIL			0x0002	// FPGA����ʧ��
#define FPGA_LDST_INIT_ERR		0x0004	// FPGA��ʼ��ʧ��

#define FPGA_LOAD_BLOCK1		0x01	// ����1
#define FPGA_LOAD_BLOCK2		0x02	// ����2

#define FPGA_POWER_PDN		10		// ���������������ʱ�Ĳ���,��λdbm

#define FPGA_AF_ATT1			0	// ǰ��˥����1
#define FPGA_AF_ATT2			1	// ǰ��˥����2
#define FPGA_AB_ATT1			2	// ���˥����1

#define FPGA_BF_ATT1			0	// ǰ��˥����1
#define FPGA_BF_ATT2			1	// ǰ��˥����2
#define FPGA_BB_ATT1			2	// ���˥����1

// ��·������ز���
#define FPGA_PDN			(10)		// ��һ�����ַ���(dbm)


#if defined CLIENT_JIZHUN
#if defined JIZHUN_V2
#define FPGA_REC_GFNOM	(50)	    // RECǰ�˱������
#define FPGA_REC_GDNOM	(10)		// REC��˱������
#define FPGA_RE_GFNOM		(50)		// REǰ�˱������
#define FPGA_RE_GDNOM		(10)		// RE��˱������
#else
#define FPGA_REC_GFNOM	(0)	    // RECǰ�˱������
#define FPGA_REC_GDNOM	(10)		// REC��˱������
#define FPGA_RE_GFNOM		(50)		// REǰ�˱������
#define FPGA_RE_GDNOM		(10)		// RE��˱������
#endif

#else
#define FPGA_REC_GFNOM	(30)	    // RECǰ�˱������
#define FPGA_REC_GDNOM	(10)		// REC��˱������
#define FPGA_RE_GFNOM		(30)		// REǰ�˱������
#define FPGA_RE_GDNOM		(10)		// RE��˱������

#endif


#define FPGA_SERDES_T_S2P		300	// FPGA���˴�ת���ӳ�(��λns)
#define FPGA_SERDES_T_P2S		300	// FPGA���˲�ת���ӳ�(��λns)


//���沨��У׼
#define GAIN_ADJ_ST_IDLE						0//����
#define GAIN_ADJ_ST_SET_AUEU_ADJ_MODE		1//AU EU����У׼ģʽ
//#define GAIN_ADJ_ST_START_ADJ					2//��ʼУ׼
#define GAIN_ADJ_ST_SET_AUEU_FRE				2//����AU EUƵ��
#define GAIN_ADJ_ST_GET_EU_SF_POW			3//��ȡѡƵ����
#define GAIN_ADJ_ST_DONE						4//���


//�澯��ش���
#define ALARM_CLAER	0//����澯
#define ALARM_GET_STATUS1  1//��ȡ�澯״̬
//����GSд��Ĵ�����ֵ
#define CALC_GS_REG( GS )	(UINT16)( pow(10, ((GS)/20))*256.0 )	// 10^(Gs/20)*256

// ����ѡƵ���������
//	PA: ���õĶ˿�ͨ������
//	GA: ��������
//	G_OUT_ATT: ���˫����˥����
//	GFCMPS: ���Ƶ�ʲ�������
//	GDNOM: ��˱������
#define CALC_OUTPUT_PSF( PA, GA, G_OUT_ATT, GFCMPS, GDNOM )	\
	(FLOAT32)( (PA)-(GA)+(G_OUT_ATT)+(GFCMPS)-GDNOM )

// ����DA������������ƽ������
//	CH_NUM: ͨ����
#define CALC_DA_MAX_POW( CH_NUM )		\
	(FLOAT32)(-6-10*LOG_10(3+(CH_NUM))+FPGA_PDN)

#define CALC_DA_MAX_POW_WCDMA( CH_NUM )		\
	(FLOAT32)(-18-10*LOG_10(1+(FLOAT32)((CH_NUM)/4.0))+FPGA_PDN)


// ����Fpga��Gdcmps
//	PDA: DA������������ƽ������
//	PSF: ѡƵ���������
//	GINP: ����˲�������
#define CALC_GDCMPS( PDA, PSF, GINP )	(FLOAT32)(PDA-PSF-GINP)

// ���ݼĴ�����ֵ������
#define CALC_GAIN( REG_VAL )	( (REG_VAL==0) ? 0 : (FLOAT32)( 20*LOG_10( (REG_VAL)/256.0 ) ) )		// 20*lg( GAIN_REG/2^8 )

// ���ݼĴ���ֵ����
#define CALC_POWER( REG_VAL )	( (REG_VAL==0) ? (FLOAT32)(-150) : ((FLOAT32)(FPGA_PDN+(FLOAT32)10.0*LOG_10( (FLOAT32)(REG_VAL)/4294967296L ))))	// 10*lg(POW_REG/2^32)+Pdn
// ���ݼĴ���ֵ����
#define CALC_POWER_1( REG_VAL )	( (REG_VAL==0) ? (FLOAT32)(-100) : ((FLOAT32)(FPGA_PDN+(FLOAT32)10.0*LOG_10( (FLOAT32)(REG_VAL)/4294967296L ))))	// 10*lg(POW_REG/2^32)+Pdn

// �¶����油�� FTCOMP=int[10^(TCOFF/20)*4096]
#define CALC_FTCOMP( COMP_DB ) ( 4096*pow(10, (COMP_DB)/20) )

//==FPGA�������==
#define FPGA_WO_REG(ADR)		(0x8000|(ADR))	// ֻд�Ĵ�����ַ��־
#define FPGA_WO_REG_COUNT		320//252		//FPGAд��Ĵ�������


//ֻд�Ĵ���***********************************************************************************************
#define FPGA_REG_WRITE_PROTECT	FPGA_WO_REG(0x00)		//�Ĵ���д����
#define WP_CODE_NO_PROTECT	0x4747
#define WP_CODE_PROTECT_ALL	0x0000

#define FPGA_REG_SHOW_ERROR				FPGA_WO_REG(0X01)	//FPGA_WO_REG(15) FPGA����ָʾ�ƿ���
#define ERR_AU		(0x01<<15)
#define ERR_EU		(0x01<<14)
#define ERR_RU		(0x01<<13)

#define FPGA_REG_CH_SEL					FPGA_WO_REG(0X02)		// Ҫ�����ĸ�Ƶͨ����
#define FPGA_REG_TRAFFIC_CTL			FPGA_WO_REG(0X03)	// FPGA_WO_REG(7)����ͳ�ƿ���
#define BM_TRAFFIC_PERIOD				(0xFF<<0)	// ռ��ʱ϶ͳ��ʱ�䳤�ȣ����ӣ�
#define BM_TRAFFIC_STATISTIC			(1<<15)		// ����ͳ�ƹ��ܲ�ʹ��<0>/ʹ��<1>

#define FPGA_REG_ATT_ADJ_TBL			FPGA_WO_REG(0X010)	//FPGA_WO_REG(5) ��˥����У׼��������ַ
#define BM_ATT_ADDR		(0x3F<<0)			// ����ַ
#define ATT_SEL_A1		(0x00<<13)		// A��˥����ATT1
#define ATT_SEL_A3		(0x01<<13)		// A��˥����ATT3
#define ATT_SEL_B1		(0x02<<13)		// B��˥����ATT1
#define ATT_SEL_B3		(0x03<<13)		// B��˥����ATT3
#define ATT_SEL_C1		(0x04<<13)		// C��˥����ATT1
#define ATT_SEL_C3		(0x05<<13)		// C��˥����ATT3
#define ATT_SEL_D1		(0x06<<13)		// D��˥����ATT1
#define ATT_SEL_D3		(0x07<<13)		// D��˥����ATT3

#define FPGA_REG_ATT_ADJ_DAT			FPGA_WO_REG(0X11)	//FPGA_WO_REG(6) ˥�����������д����ֵ

#define FPGA_REG_ATT_FULL_REDUCE		FPGA_WO_REG(0x12)	//FPGA_WO_REG(4) att1����˥��0˥

// A��ֻд���ƼĴ���
#define FPGA_REG_A_ATT_CTL				FPGA_WO_REG(0X20)	//FPGA_WO_REG(16) A��˥��У׼����
#define ATT_MODE_MASK		0x0003		// ����ģʽ����
#define ATT_MODE_NORMAL		0x0000		// ��������
#define ATT_MODE_ADJUST		0x0002		// ˥��У׼
#define ATT_MODE_VERIFY		0x0003		// ˥��У׼��֤
#define ATT_WORK_EN			(1<<2)		// A�ι���ʹ��,1-����
#define ATT_MANUAL			(1<<3)		// 1-�ֶ�ATT ; 0-�Զ�ATT˥��

#define FPGA_REG_A_ATT3_EN				FPGA_WO_REG(0X21)	//FPGA_WO_REG(17) A��ATT3�������ʹ������
#define FPGA_REG_A_ATT1_CAL				FPGA_WO_REG(0X22)	//FPGA_WO_REG(18) A��ǰ��˥����У׼ʱATT1��˥��ֵ
#define FPGA_REG_A_ATT3_CAL				FPGA_WO_REG(0X23)	//FPGA_WO_REG(19) A��ǰ��˥����У׼ʱATT3��˥��ֵ
#define FPGA_REG_A_FT_CMPS				FPGA_WO_REG(0X24)	//FPGA_WO_REG(20) A��ǰ���¶Ȳ���ϵ��,С������D12��D11֮��
#define FPGA_REG_A_BT_CMPS				FPGA_WO_REG(0X25)	//FPGA_WO_REG(21) A�κ���¶Ȳ���ϵ��,С������D12��D11֮��
#define FPGA_REG_A_FREQ_CTL_L_12		FPGA_WO_REG(0X26)	//FPGA_WO_REG(22) A�����ֱ���Ƶ���ֵ�12λ
#define BM_FREQ		(0xFFF<<0)			// A�����ֱ���Ƶ����
#define BM_CHN_EN	(1<<15)				// A��ѡƵͨ������ʹ��1-����;0-������
#define FPGA_REG_A_FREQ_CTL_H_14		FPGA_WO_REG(0x27)	//FPGA_WO_REG(0X80) A������ǰ�����ֱ���Ƶ���ָ�14λ
#define FPGA_REG_A_D_FREQ_CTL_L_12		FPGA_WO_REG(0x28)	//FPGA_WO_REG(0x84) A�����к�����ֱ���Ƶ���ֵ�12λ
#define FPGA_REG_A_D_FREQ_CTL_H_14		FPGA_WO_REG(0x29)	//FPGA_WO_REG(0x85) A�����к�����ֱ���Ƶ���ָ�14λ
#define FREQ_SIG	(1<<15)				// A�����ֱ���Ƶ�������� 1/0----��/��
#define FPGA_REG_A_FOUT_CTL				FPGA_WO_REG(0X2A)	//FPGA_WO_REG(23) �������Ƶ�ʼ�Ƶ�׷�ת����
#define FPGA_REG_GSM_BW_SEL				FPGA_WO_REG(0X2E)	//FPGA_WO_REG(66) ����汾GSM����ѡ��
#define GSM_BW_SEL_6M			0
#define GSM_BW_SEL_20M		1
#define GSM_BW_SEL_24M		2
#define GSM_BW_SEL_25M		3

// B��ֻд���ƼĴ���
#define FPGA_REG_B_ATT_CTL				FPGA_WO_REG(0X40)	//FPGA_WO_REG(32) B��˥��У׼����
#define FPGA_REG_B_ATT3_EN				FPGA_WO_REG(0X41)	//FPGA_WO_REG(33) B��ATT3�������ʹ������
#define FPGA_REG_B_ATT1_CAL				FPGA_WO_REG(0X42)	//FPGA_WO_REG(34) B��ǰ��˥����У׼ʱATT1��˥��ֵ
#define FPGA_REG_B_ATT3_CAL				FPGA_WO_REG(0X43)	//FPGA_WO_REG(35) B��ǰ��˥����У׼ʱATT3��˥��ֵ
#define FPGA_REG_B_FT_CMPS				FPGA_WO_REG(0X44)	//FPGA_WO_REG(36) B��ǰ���¶Ȳ���ϵ��,С������D12��D11֮��
#define FPGA_REG_B_BT_CMPS				FPGA_WO_REG(0X45)	//FPGA_WO_REG(37) B�κ���¶Ȳ���ϵ��,С������D12��D11֮��
#define FPGA_REG_B_FREQ_CTL_L_12		FPGA_WO_REG(0X46)	//FPGA_WO_REG(38) B������ǰ�����ֱ���Ƶ���ֵ�12λ
#define FPGA_REG_B_FREQ_CTL_H_14		FPGA_WO_REG(0x47)	//FPGA_WO_REG(0X81) B������ǰ�����ֱ���Ƶ���ָ�14λ
#define FPGA_REG_B_D_FREQ_CTL_L_12		FPGA_WO_REG(0x48)	//FPGA_WO_REG(0x86) B�����к�����ֱ���Ƶ���ֵ�12λ
#define FPGA_REG_B_D_FREQ_CTL_H_14		FPGA_WO_REG(0x49)	//FPGA_WO_REG(0x87) B�����к�����ֱ���Ƶ���ָ�14λ
#define FPGA_REG_B_FOUT_CTL				FPGA_WO_REG(0X4A)	//FPGA_WO_REG(39) �������Ƶ�ʼ�Ƶ�׷�ת����

#define FPGA_REG_B_W_SPI_CONTROL			FPGA_WO_REG(0x5A)//(0X7A)	// D15-��дָʾ��1��д��0�Ƕ�;D[14:10]-SPIָ���źţ�Ĭ��Ϊȫ��;D[9:0]-��д��ַ�ź�
#define FPGA_REG_B_W_SPI_WRITE_DATA		FPGA_WO_REG(0x5B)//(0X7B)	// D15-MCU��дSPIָʾ�źţ�1������MCU��дSPI��0����ֹMCU��дSPI    D[7:0]-������SPI����

// C��ֻд���ƼĴ���
#define FPGA_REG_C_ATT_CTL				FPGA_WO_REG(0X60)	//FPGA_WO_REG(70) C��˥��У׼����
#define FPGA_REG_C_ATT3_EN				FPGA_WO_REG(0X61)	//FPGA_WO_REG(71) C��ATT3�������ʹ������
#define FPGA_REG_C_ATT1_CAL				FPGA_WO_REG(0X62)	//FPGA_WO_REG(72) C��ǰ��˥����У׼ʱATT1��˥��ֵ
#define FPGA_REG_C_ATT3_CAL				FPGA_WO_REG(0X63)	//FPGA_WO_REG(73) C��ǰ��˥����У׼ʱATT3��˥��ֵ
#define FPGA_REG_C_FT_CMPS				FPGA_WO_REG(0X64)	//FPGA_WO_REG(74) C��ǰ���¶Ȳ���ϵ��,С������D12��D11֮��
#define FPGA_REG_C_BT_CMPS				FPGA_WO_REG(0X65)	//FPGA_WO_REG(75) C�κ���¶Ȳ���ϵ��,С������D12��D11֮��
#define FPGA_REG_C_FREQ_CTL_L_12		FPGA_WO_REG(0X66)	//FPGA_WO_REG(76) C�����ֱ���Ƶ�ʿ���
#define FPGA_REG_C_FREQ_CTL_H_14		FPGA_WO_REG(0x67)	//FPGA_WO_REG(0X82) C������ǰ�����ֱ���Ƶ���ָ�14λ
#define FPGA_REG_C_D_FREQ_CTL_L_12		FPGA_WO_REG(0X68)	//FPGA_WO_REG(76) C������ǰ�����ֱ���Ƶ�ʿ��Ƶ�12λ
#define FPGA_REG_C_D_FREQ_CTL_H_14		FPGA_WO_REG(0x69)	//FPGA_WO_REG(0X82) C������ǰ�����ֱ���Ƶ���ָ�14λ

#define FPGA_REG_C_W_SPI_CONTROL		FPGA_WO_REG(0x7A)//(0X7A)	// D15-��дָʾ��1��д��0�Ƕ�;D[14:10]-SPIָ���źţ�Ĭ��Ϊȫ��;D[9:0]-��д��ַ�ź�
#define FPGA_REG_C_W_SPI_WRITE_DATA	FPGA_WO_REG(0x7B)//(0X7B)	// D15-MCU��дSPIָʾ�źţ�1������MCU��дSPI��0����ֹMCU��дSPI    D[7:0]-������SPI����

// D��ֻд���ƼĴ���
#define FPGA_REG_D_ATT_CTL				FPGA_WO_REG(0X80)	//FPGA_WO_REG(78) D��˥��У׼����
#define FPGA_REG_D_ATT3_EN				FPGA_WO_REG(0X81)	//FPGA_WO_REG(79) D��ATT3�������ʹ������
#define FPGA_REG_D_ATT1_CAL				FPGA_WO_REG(0X82)	//FPGA_WO_REG(80) D��ǰ��˥����У׼ʱATT1��˥��ֵ
#define FPGA_REG_D_ATT3_CAL				FPGA_WO_REG(0X83)	//FPGA_WO_REG(81) D��ǰ��˥����У׼ʱATT3��˥��ֵ
#define FPGA_REG_D_FT_CMPS				FPGA_WO_REG(0X84)	//FPGA_WO_REG(82) D��ǰ���¶Ȳ���ϵ��,С������D12��D11֮��
#define FPGA_REG_D_BT_CMPS				FPGA_WO_REG(0X85)	//FPGA_WO_REG(83) D�κ���¶Ȳ���ϵ��,С������D12��D11֮��
#define FPGA_REG_D_FREQ_CTL_L_12		FPGA_WO_REG(0X86)	//FPGA_WO_REG(84) D�����ֱ���Ƶ�ʿ���
#define FPGA_REG_D_FREQ_CTL_H_14		FPGA_WO_REG(0x87)	//FPGA_WO_REG(0X83) D������ǰ�����ֱ���Ƶ���ָ�14λ
#define FPGA_REG_D_D_FREQ_CTL_L_12		FPGA_WO_REG(0X88)	//FPGA_WO_REG(76) D������ǰ�����ֱ���Ƶ�ʿ��Ƶ�12λ
#define FPGA_REG_D_D_FREQ_CTL_H_14		FPGA_WO_REG(0x89)	//FPGA_WO_REG(0X82) D������ǰ�����ֱ���Ƶ���ָ�14λ

// ��˿�ֻд���ƼĴ���
#define FPGA_REG_OPT_ON					FPGA_WO_REG(0XA0)	//FPGA_WO_REG(48) 1-��Ӧ��˿ڹ���;0-��Ӧ��˿ڲ�����
#define FPGA_REG_OPT_SEL				FPGA_WO_REG(0xA1)		// FPGA_WO_REG(0x01)Ҫ�����Ĺ�ں�
#define FPGA_REG_W_THR_DAT				FPGA_WO_REG(0XA2)	//FPGA_WO_REG(51) D[7:0]͸���ֽ�д��
#define FPGA_REG_W_MSG_DES_ADD			FPGA_WO_REG(0XA3)	//FPGA_WO_REG(52) �������ݰ���ģ��ĵ�ַ
#define FPGA_REG_W_MSG_SRC_ADD			FPGA_WO_REG(0XA4)	//FPGA_WO_REG(53) �������ݰ���ģ��ĵ�ַ
#define BM_MSG_ADDR_RE	(0xFF<<0)		// D7-0���������ݰ���RE�ڵ��ַ��ȫ1��ʾ���нڵ�
#define BM_MSG_ADDR_FP	(0xFF<<8)		// D15-8���������ݰ���RE������·��REC��˿ڣ�ȫ1��ʾ���ж˿�
#define FPGA_REG_W_MSG_LEN				FPGA_WO_REG(0XA5)	//FPGA_WO_REG(54) ���ݰ�����
//#define MSG_FLAME_MAX_LEN				191	//һ�δ��������ֽ���
#define FPGA_REG_W_MSG_DAT				FPGA_WO_REG(0XA6)	//FPGA_WO_REG(55) ���ݰ�����
#define FPGA_REG_MSG_START_SEND			FPGA_WO_REG(0XA7)	//FPGA_WO_REG(56) д�����������ݰ�����
//#define FPGA_REG_A_FFCOMP				0x8017	// ǰ��Ƶ�ʲ�������,С������D12��D11֮��
//#define FPGA_REG_A_BFCOMP				0x8018	// ���Ƶ�ʲ�������,С������D12��D11֮��

#define FPGA_REG_TD_MAIN_CH_L12			FPGA_WO_REG(0XD0)	//FPGA_WO_REG(25) D11-0:���TDSCDMA��ʽ�����ŵ�Ƶ�ʿ�����
#define FPGA_REG_TD_MAIN_CH_H14			FPGA_WO_REG(0XD1)	//FPGA_WO_REG(26) D25-12:���TDSCDMA��ʽ�����ŵ�Ƶ�ʿ�����
#define FPGA_REG_TD_MAIN_CH_CNT    		FPGA_WO_REG(0XD2) //FPGA_WO_REG(27) D7-0:���TDSCDMA��ʽƵ�����
#define FPGA_REG_TD_MAIN_CH_END     	FPGA_WO_REG(0XD3) //FPGA_WO_REG(28) TDSCDMA��ʽдƵ�������
#define FPGA_REG_TDSLOT_CTL				FPGA_WO_REG(0XD4)	//FPGA_WO_REG(41) TDʱ϶�����п���
#define FPGA_REG_TD_1ST_TIME			FPGA_WO_REG(0XD5)	//FPGA_WO_REG(42) TD��һת����ʱ��
#define FPGA_REG_TD_2ND_TIME			FPGA_WO_REG(0XD6)	//FPGA_WO_REG(43) TD��һת����ʱ��
#define FPGA_REG_TD_LNA_ON_TIME			FPGA_WO_REG(0XD7)	//FPGA_WO_REG(44) TD��һת����ʱ��
#define FPGA_REG_TD_LNA_OFF_TIME		FPGA_WO_REG(0XD8)	//FPGA_WO_REG(45) TD��һת����ʱ��
#define FPGA_REG_TD_WORK_MODE			FPGA_WO_REG(0XD9)	//FPGA_WO_REG(68) TD_SCDMA����ģʽ��00����ģʽ��01���г�����10�����г���
#define TD_WM_NORMAL			0
#define TD_WM_UL_ALWAYS_ON	1
#define TD_WM_DL_ALWAYS_ON	2
#define FPGA_REG_TDSLOT_SEL					FPGA_WO_REG(0xDA)//(1)		// TDʱ϶��


#define FPGA_REC_C_TS_CONFIG			FPGA_WO_REG(0xE0)	//FPGA_WO_REG(0xDA) TD������ʱ϶���
#define FPGA_REC_C_TD_LTE_SLOT_SEL		FPGA_WO_REG(0xE1)		//FPGA_WO_REG(0xDB) Ҫ������LTEʱ϶��
#define FPGA_REC_C_LTE_FREQ_CTL_L		FPGA_WO_REG(0xE2)	//FPGA_WO_REG(0xDC) TD_LTE�ŵ�Ƶ�ʿ�����	13bit
#define FPGA_REC_C_LTE_FREQ_CTL_H		FPGA_WO_REG(0xE3)	//FPGA_WO_REG(0xDD) TD_LTE�ŵ�Ƶ�ʿ�����	13bit
#define FPGA_REC_C_TD_1ST_TIME			FPGA_WO_REG(0xE4)	//FPGA_WO_REG(0xDE) TD��һת����ʱ��
#define FPGA_REC_C_TD_2ND_TIME			FPGA_WO_REG(0xE5)	//FPGA_WO_REG(0xDF) TD��һת����ʱ��
#define FPGA_REC_C_TD_LNA_ON_TIME		FPGA_WO_REG(0xE6)	//FPGA_WO_REG(0xE0) LNA�����ٺ�DN_PA�رյı���ʱ��ns
#define FPGA_REC_C_TD_LNA_OFF_TIME		FPGA_WO_REG(0xE7)	//FPGA_WO_REG(0xE1) LNA�رճ�ǰDN_PA�����ı���ʱ��ns
#define FPGA_REC_C_TD_WORK_MODE			FPGA_WO_REG(0XE8)	//FPGA_WO_REG(0xE2) TD_LTE����ģʽ��00����ģʽ��01���г�����10�����г���
#define FPGA_REG_LTE_MAIN_CH_CNT    	FPGA_WO_REG(0XE9)   //FPGA_WO_REG(27) D7-0:��� TD_LTE��ʽƵ�����
#define FPGA_REG_LTE_MAIN_CH_END     	FPGA_WO_REG(0XEA)   //FPGA_WO_REG(28) TDSCDMA��ʽдƵ�������
#define FPGA_REG_W_SLOT_TIME_B			FPGA_WO_REG(0xEB)	// BIT 15--ֻд1����TDSʱ϶����Զ���⹦��
#define FPGA_REG_W_SLOT_TIME_C			FPGA_WO_REG(0xEC)	// BIT 15--ֻд1����TDSʱ϶����Զ���⹦��
										


#define FPGA_REC_D_TS_CONFIG			FPGA_WO_REG(0xE0)	//FPGA_WO_REG(0xDA) TD������ʱ϶���
#define FPGA_REC_D_LTE_FREQ_CTL_L		FPGA_WO_REG(0xE2)	//FPGA_WO_REG(0xDC) TD_LTE�ŵ�Ƶ�ʿ�����	13bit
#define FPGA_REC_D_LTE_FREQ_CTL_H		FPGA_WO_REG(0xE3)	//FPGA_WO_REG(0xDD) TD_LTE�ŵ�Ƶ�ʿ�����	13bit
#define FPGA_REC_D_TD_1ST_TIME			FPGA_WO_REG(0xE4)	//FPGA_WO_REG(0xDE) TD��һת����ʱ��
#define FPGA_REC_D_TD_2ND_TIME			FPGA_WO_REG(0xE5)	//FPGA_WO_REG(0xDF) TD��һת����ʱ��
#define FPGA_REC_D_TD_LNA_ON_TIME		FPGA_WO_REG(0xE6)	//FPGA_WO_REG(0xE0) LNA�����ٺ�DN_PA�رյı���ʱ��ns
#define FPGA_REC_D_TD_LNA_OFF_TIME		FPGA_WO_REG(0xE7)	//FPGA_WO_REG(0xE1) LNA�رճ�ǰDN_PA�����ı���ʱ��ns
#define FPGA_REC_D_TD_WORK_MODE			FPGA_WO_REG(0XE8)	//FPGA_WO_REG(0xE2) TD_LTE����ģʽ��00����ģʽ��01���г�����10�����г���


// Ƶ��ɨ��
#define FPGA_REG_RFC_SCAN_CNT			FPGA_WO_REG(0X100)	//FPGA_WO_REG(60) ɨ���Ƶ������
#define FPGA_REG_RFC_SCAN_DF_2      	FPGA_WO_REG(0X101) //FPGA_WO_REG(61) ɨ���Ƶ������Ƶ����[11:0]λ
#define FPGA_REG_RFC_SCAN_READY			FPGA_WO_REG(0X102)	//FPGA_WO_REG(62) ִ��д��������������Ƶ����д������ź�
#define FPGA_REG_RFC_SCAN_START			FPGA_WO_REG(0X103)	//FPGA_WO_REG(63) ִ��д����������ɨ��
#define FPGA_REG_BCCH_DF_2				FPGA_WO_REG(0X104)	//FPGA_WO_REG(64) Ҫ��ȡTCCH��BCCHƵ����[11:0]λ��д��Ƶ����ֱ������TCCH��׽
#define FPGA_REG_RFC_SCAN_DF_1			FPGA_WO_REG(0x106)	//FPGA_WO_REG(57) ɨ���Ƶ������Ƶ����[25:12]λ
#define FPGA_REG_BCCH_DF_1				FPGA_WO_REG(0x107)	//FPGA_WO_REG(58) Ҫ��ȡTCCH��BCCHƵ����[25:12]λ��д��Ƶ����ֱ������TCCH��׽

#define FPGA_REG_RFC_SCAN_FRE_WORE_POINT_L12			FPGA_WO_REG(0x105)	//D15��1/0------�ֶ�/�Զ�����Ƶ��������Ƶ����FRE_WORE_POINT [15]D11-0���ֶ�����ʱƵ���Ƶ���� FRE_WORE_POINT[11:0] 
#define FPGA_REG_RFC_SCAN_FRE_WORE_POINT_H14			FPGA_WO_REG(0x108)	//D13-0����Ƶ���Ӧ�����ֱ���Ƶ����FRE_WORE_POINT[25:12]��д����ʱFPGA����ʹ�����壩��D15�� FRE_WORE_POINT[26]��



// Ĭ���¶Ȳ���ϵ��
#define DEFAULT_T_CMPS	4096
// A��B�����ֱ���Ƶ�ʿ��ƼĴ�������λ
#define CNL_FREQ_MASK		(0x0FFF)			// ���ֱ���Ƶ����
#define SF_CHANNEL_EN		(1<<15)			// ѡƵͨ������ʹ��1-����;0-������
// A��B��Ƶ�����Ƶ�׷�ת
#define FOUT_SPEC_INV		(1<<15)			// 1-��ת; 0-����ת


#define FPGA_REG_EX_DEV_CTL		FPGA_WO_REG(0x11F)		// FPGA_WO_REG(3)��������������
#define BM_EX_PLL_DAT			(1<<0)	// Ƶ���ۺ�������������PLL_DAT
#define BM_EX_PLL_CLK			(1<<1)	// Ƶ���ۺ�������ʱ����PLL_CLK
//#define BM_EX_A_DA9788_RST		// A��DA9778��λ�ź� A_DA_RST
//#define BM_EX_B_DA9788_RST		// B��DA9778��λ�ź� B_DA_RST
//#define BM_EX_AD6655_EN			// AD6655ƬѡAD_EN
//#define BM_EX_AD6655_SYNC			// AD6655ͬ������
#define BM_EX_FA_PLL_LE		(1<<8)	// A��ǰ���ۺ�������ƬѡFA_PLL_LE
#define BM_EX_BA_PLL_LE		(1<<9)	// A�κ���ۺ�������ƬѡBA_PLL_LE
#define BM_EX_FB_PLL_LE			(1<<10)	// B��ǰ���ۺ�������ƬѡFB_PLL_LE
#define BM_EX_BB_PLL_LE			(1<<11)	// B�κ���ۺ�������ƬѡBB_PLL_LE
#define BM_OUT_ATT_OFF			(1<<12)	// A��ATT1-ATT3��B��ATT1-ATT3ǿ��ȫ˥���ơ�1---ǿ��ȫ˥��0---��������

#define FPGA_REG_DELAY_SPEC_H		FPGA_WO_REG(0X11F)	//FPGA_WO_REG(49) D[15:0]�źŷ�����ʱҪ��[23:8]
#define FPGA_REG_DELAY_SPEC_L		FPGA_WO_REG(0X11F)	//FPGA_WO_REG(50) D[15:8]�źŷ�����ʱҪ��[7:0]
//#define FPGA_REG_RFC_SCAN_DF		FPGA_WO_REG(61)	// ɨ���Ƶ������Ƶ����
//#define FPGA_REG_RFC_SCAN_DF_1		FPGA_WO_REG(0x11f)	//FPGA_WO_REG(57) ɨ���Ƶ������Ƶ����[25:12]λ
//#define FPGA_REG_BCCH_DF			FPGA_WO_REG(64)	// Ҫ��ȡTCCH��BCCHƵ���֣�д��Ƶ����ֱ������TCCH��׽
//#define FPGA_REG_BCCH_DF_1			FPGA_WO_REG(0x11f)	//FPGA_WO_REG(58) Ҫ��ȡTCCH��BCCHƵ����[25:12]λ��д��Ƶ����ֱ������TCCH��׽

//#define FPGA_REG_C_D_FREQ_CTL_L_12		FPGA_WO_REG(0x11F)	//FPGA_WO_REG(0x88)C�����к�����ֱ���Ƶ���ֵ�12λ
//#define FPGA_REG_C_D_FREQ_CTL_H_14	FPGA_WO_REG(0x11F)	//FPGA_WO_REG(0x89)C�����к�����ֱ���Ƶ���ָ�14λ
//#define FPGA_REG_D_D_FREQ_CTL_L_12		FPGA_WO_REG(0x11F)	//FPGA_WO_REG(0x8A) D�����к�����ֱ���Ƶ���ֵ�12λ
//#define FPGA_REG_D_D_FREQ_CTL_H_14	FPGA_WO_REG(0x11F)	//FPGA_WO_REG(0x8B) D�����к�����ֱ���Ƶ���ָ�14λ
// �������(SED)ֻд���ƼĴ���
#define FPGA_REG_W_SED_CTL		FPGA_WO_REG(0x11f)	//FPGA_WO_REG(200) ����������
#define BM_SED_ENABLE		(1<<0)	// 1-ʹ��SED; 0-��ֹSED
#define BM_SED_START		(1<<1)	// 1-����SED; 0-ֹͣSED
// ����
#define FPGA_REG_W_ONE_WIRE		FPGA_WO_REG(0x11f)	//FPGA_WO_REG(251) ������д���ݣ�������

#define FPGA_REG_A_ATT2_CAL		FPGA_WO_REG(0x11F)	// A��ǰ��˥����У׼ʱATT2��˥��ֵ   //mdas v2 31�Ĵ�����ʱ����  ��ʱ�������ι�����
#define FPGA_REG_B_ATT2_CAL		FPGA_WO_REG(0X11F)	// B��ǰ��˥����У׼ʱATT2��˥��ֵ //mdas v2 31�Ĵ�����ʱ����  ��ʱ�������ι�����
#define FPGA_REG_C_ATT2_CAL		FPGA_WO_REG(0X11F)	// C��ǰ��˥����У׼ʱATT2��˥��ֵ//mdas v2 31�Ĵ�����ʱ����  ��ʱ�������ι�����
#define FPGA_REG_D_ATT2_CAL		FPGA_WO_REG(0X11F)	// D��ǰ��˥����У׼ʱATT2��˥��ֵ//mdas v2 31�Ĵ�����ʱ����  ��ʱ�������ι�����



//ֻ���Ĵ���********************************************************************************************************
#define FPGA_REG_WRITE_CHECK		0x00	//0 ��ֻд�Ĵ���0��ֵȡ�������������������Ӽ��
#define FPGA_REG_EDITION_INFO		0x01    //	FPGA�汾�����Ϣ
#define BM_SECONDARY_VERSION	(0x0F<<0)	// FPGA�ΰ汾��
#define BM_PRIMARY_VERSION		(0x0F<<4)	// FPGA���汾��
#define BM_MODULE_FLAG			(0x01<<12)	// ģ���ʶ0-REC, 1-RE
#define BM_PRODUCT_FLAG		(0x07<<13)	// ��Ʒ��ʾ: 7-GSM����ֱ��վ

#define FPGA_REG_PCB_VERSION		0x02    //	2 PCB�汾��
#define FPGA_REG_IRQ_CLEAN			0x03    //	3 �������������160��ԪD0Ϊ1������ж�,ˮӡ������ʼ��
#define FPGA_REG_WATER_PRINT		0x04    //	4 ���������������״̬����,ÿ��һ��ˮӡ���ݵ�ַ��1��
#define FPGA_REG_CH_COUNT			0x05	//5 FPGA֧�ֵ�ͨ����
#define BM_A_CH_COUNT			(0x0F<<0)	// FPGA֧�ֵĶ�A��ͨ������
#define BM_B_CH_COUNT			(0x0F<<8)	// FPGA֧�ֵĶ�B��ͨ������
#define BM_C_CH_COUNT			(0x0F<<4)	// FPGA֧�ֵĶ�A��ͨ������
#define BM_D_CH_COUNT			(0x0F<<12)	// FPGA֧�ֵĶ�B��ͨ������

#define FPGA_REG_R_OPT_CH			0x06	//6 �������Ĺ�ںš���Ƶͨ���Ŷ���
#define BM_OPT_READBACK		(0x07<<8)
#define BM_CH_READBACK			(0x1F<<0)
#define FPGA_GET_CH_SEL		( 0x1F & FpgaReadRegister(FPGA_REG_R_OPT_CH) )
#define FPGA_GET_OPT_SEL		( 0x0F & ( FpgaReadRegister(FPGA_REG_R_OPT_CH)>>8 ) )
#define FPGA_REG_RF_INFO			0x07	//7 FPGA����Ƶ�����Ϣ
//#define FPGA_REG_RF_INFO_C_D			45	// FPGA����Ƶ�����Ϣ
#define BM_A_NT_INFO		(0xF<<8)	// A�ε���Ƶ��ʽ��Ϣ
#define FPGA_A_NT_GSM		0		// GSM
#define FPGS_A_NT_WCDMA		1		// WCDMA
#define FPGA_A_NT_TD		2		// TD-SCDMA
#define FPGA_A_NT_CDMA_WB	3		// CDMA
#define FPGA_A_NT_GSM_WB	4		// ���GSM
#define FPGA_A_NT_CMMB		5		// CMMB
#define FPGA_A_NT_TETRA_WB	6		// �����Ⱥ

#define BM_B_NT_INFO		(0xF<<12)	// B�ε���Ƶ��ʽ��Ϣ
#define FPGA_B_NT_GSM		0		// GSM
#define FPGS_B_NT_WCDMA		1		// WCDMA
#define FPGA_B_NT_TD		2		// TD-SCDMA
#define FPGA_B_NT_CDMA_WB	3		// ���CDMA
#define FPGA_B_NT_GSM_D		4		// �ּ�GSM
#define FPGA_B_NT_WCDMA_D	5		// �ּ�WCDMA
#define FPGA_B_NT_TD_D		6		// �ּ�TD-SCDMA
#define FPGA_B_NT_CDMA_D_WB	7		// ����ּ�CDMA
#define FPGA_B_NT_TD_WB		8		// ���TD-SCDMA
#define FPGA_B_NT_GSM_D_WB	9		// �ּ����GSM
#define FPGA_B_NT_GSM_WB	10		// ���GSM
#define FPGA_B_NT_WCDMA_WB	11		// ���WCDMA
#define FPGA_B_NT_CMMB		12		// CMMB
#define FPGA_B_NT_TETRA_D_WB	13		// �ּ������Ⱥ

#define FPGA_C_NT_LTE_TD		0		// LTE_TD
#define FPGA_C_NT_LTE_FDD		1		// LTE_FDD
#define FPGA_D_NT_LTE_TD		0		// LTE_TD
#define FPGA_D_NT_LTE_FDD		1		// LTE_FDD

#define FPGA_REG_SOME_STATUS		0X08//64ĳЩ״̬��־
#define FPGA_REG_CLEAR_TRA_FLAG		0X09	//65�������ͳ��ʱ�����ڽ��б�־
#define FPGA_REG_AC_WARNING_FLAG		0X0A	//D1: �ⲿAC�澯���� AC_WARNING			

// A��ֻ�����ƼĴ���
#define FPGA_REG_A_FAD_POW_H	0X0020	//32 ǰ��A/D�����źŹ��ʸ�16λ
#define FPGA_REG_A_FAD_POW_L	0X0021	//33 ǰ��A/D�����źŹ��ʵ�16λ
#define FPGA_REG_A_BDA_POW_H	0X0022	//34 ���D/A����źŹ��ʸ�16λ
#define FPGA_REG_A_BDA_POW_L	0X0023	//35 ���D/A����źŹ��ʵ�16λ
#define FPGA_REG_A_FG_CMPS		0x0024	//36 ǰ��Gfcmps����
#define FPGA_REG_A_BG_CMPS		0x0025	//37 ���GDcmps����
#define FPGA_REG_A_ATT1_VAL		0x0026	//38 ǰ��˥����ATT1��˥��ֵ
#define FPGA_REG_A_ATT2_VAL		    0X11F	//39 ǰ��˥����ATT2��˥��ֵ
#define FPGA_REG_A_ATT3_VAL		0x0027	//40 ǰ��˥����ATT3��˥��ֵ
//#define FPGA_REG_A_AD_DA_ST		0x0029	// AD��DA����״̬,һ���������;�һֱ����������4��Ԫ�����������������״̬
#define BM_AD_FSAT		0x0001		// 1-ǰ��AD���뱥��
#define BM_DA_DSAT		0x0002		// 1-���DA�������

// B��ֻ�����ƼĴ���
#define FPGA_REG_B_FAD_POW_H		0X40	//48 ǰ��A/D�����źŹ��ʸ�16λ				
#define FPGA_REG_B_FAD_POW_L		0X41	//49 ǰ��A/D�����źŹ��ʵ�16λ				
#define FPGA_REG_B_BDA_POW_H		0X42	//50 ���D/A����źŹ��ʸ�16λ				
#define FPGA_REG_B_BDA_POW_L		0x43	//51 ���D/A����źŹ��ʵ�16λ				
#define FPGA_REG_B_FG_CMPS		0x44	//52 ǰ��Gfcmps����				
#define FPGA_REG_B_BG_CMPS		0x45	//53 ���GDcmps����				
#define FPGA_REG_B_ATT1_VAL		0x46	//54 ǰ��˥����ATT1��˥��ֵ				
//#define FPGA_REG_B_ATT2_VAL		55	// ǰ��˥����ATT2��˥��ֵ				
#define FPGA_REG_B_ATT3_VAL		0x47	//56 ǰ��˥����ATT3��˥��ֵ				
//#define FPGA_REG_B_AD_DA_ST		57	// AD��DA����״̬,һ���������;�һֱ����������4��Ԫ�����������������״̬				
#define FPGA_REG_B_R_SPI_DATA			0x5A	// SPI: D15-MCU��дSPIָʾ�źţ�1������MCU��дSPI��0����ֹMCU��дSPI    D[7:0]-������SPI����

// C��ֻ�����ƼĴ���				
#define FPGA_REG_C_FAD_POW_H		0x60	//148 ǰ��A/D�����źŹ��ʸ�16λ	
#define FPGA_REG_C_FAD_POW_L		0x61	//149 ǰ��A/D�����źŹ��ʵ�16λ	
#define FPGA_REG_C_BDA_POW_H		0x62	//150 ���D/A����źŹ��ʸ�16λ	
#define FPGA_REG_C_BDA_POW_L		0x63	//151 ���D/A����źŹ��ʵ�16λ	
#define FPGA_REG_C_FG_CMPS			0x64	//152 ǰ��Gfcmps����
#define FPGA_REG_C_BG_CMPS			0x65	//153 ���GDcmps����	
#define FPGA_REG_C_ATT1_VAL			0x66	//154 ǰ��˥����ATT1��˥��ֵ	
//#define FPGA_REG_C_ATT2_VAL			155	// ǰ��˥����ATT2��˥��ֵ	
#define FPGA_REG_C_ATT3_VAL			0x67	//156 ǰ��˥����ATT3��˥��ֵ	
//#define FPGA_REG_C_AD_DA_ST			157	// AD��DA����״̬,һ���������;�һֱ����������4��Ԫ�����������������״̬	

#define FPGA_REG_C_R_SPI_DATA		0x7A	// SPI: D15-MCU��дSPIָʾ�źţ�1������MCU��дSPI��0����ֹMCU��дSPI    D[7:0]-������SPI����

// D��ֻ�����ƼĴ���
#define FPGA_REG_D_FAD_POW_H		0x80	//168 ǰ��A/D�����źŹ��ʸ�16λ
#define FPGA_REG_D_FAD_POW_L		0x81	//169 ǰ��A/D�����źŹ��ʵ�16λ
#define FPGA_REG_D_BDA_POW_H		0x82	//170 ���D/A����źŹ��ʸ�16λ
#define FPGA_REG_D_BDA_POW_L		0x83	//171 ���D/A����źŹ��ʵ�16λ
#define FPGA_REG_D_FG_CMPS			0x84	//172 ǰ��Gfcmps����
#define FPGA_REG_D_BG_CMPS			0x85	//173 ���GDcmps����
#define FPGA_REG_D_ATT1_VAL			0x86	//174 ǰ��˥����ATT1��˥��ֵ
//#define FPGA_REG_D_ATT2_VAL			175	// ǰ��˥����ATT2��˥��ֵ
#define FPGA_REG_D_ATT3_VAL			0x87	//176 ǰ��˥����ATT3��˥��ֵ
//#define FPGA_REG_D_AD_DA_ST			177	// AD��DA����״̬,һ���������;�һֱ����������4��Ԫ�����������������״̬


// ��˿�ֻ��ͨѶ�Ĵ���
#define FPGA_REG_R_THR_IDLE_ST	0xA0	//8 ��˿�͸��д����б�־,ÿ��λ��Ӧһ�����,1-����
#define FPGA_REG_THR_FIFO_ST	0xA1	//9 ���͸������FIFO״̬,��8λ1��ʾFIFO������,��8λ1��ʾFIFO��
#define FPGA_REG_R_THR_DAT		0xA2	//10 ���͸��FIFO������ַ
#define FPGA_REG_MSG_TX_READY	0xA3	//11 ������ݰ�����FIFO������־,λ��Ӧ,1-FIFO����������д��������
#define FPGA_REG_MSG_FIFO_ST	0xA4	//12 ������ݰ�����FIFO״̬,λ��Ӧ,��8λ1��ʾFIFO������,��8λ1��ʾFIFO��
#define FPGA_REG_PKT_ERR_COUNT	0xA5	//13 ���ݰ��������
#define FPGA_REG_CLEAR_PKT_ERR	0xA6	//14 ��������0���ݰ����������
#define FPGA_REG_R_MSG_DAT		0xA7	//15 FIFO�ж��������ݰ��ֽڣ�������������ַ�������Զ���1
#define FPGA_REG_R_NEXT_MSG		0xA8	//16 �����������ݰ�FIFO��ָ���1��������ַ��������0��
#define FPGA_REG_OPT_INFO		0xA9	// ���״̬
#define BM_OPT_RE_COUNT		(0xFF<<0)	// �ڵ����м���������֡����ʱ��Ч
#define BM_OPT_COMMA_LOCK		(1<<8)	// 1-���˿ڼ�⵽����
#define BM_OPT_FRM_LOCK		(1<<9)	// 1-���˿ڽ���֡����
#define BM_OPS_COMMA_LOCK		(1<<10)	// 1-�Զ˽��ռ�⵽���˶���
#define BM_UP_DN				(0x03<<11)	// ����֡״̬
#define UP_DN_BITS			11		// ����֡״̬λƫ����
#define UP_DN_MODE_NOF	(0<<11)	// û���յ�֡����
#define UP_DN_MODE_ATF	(1<<11)	// �յ��Է�֡
#define UP_DN_MODE_DNF	(2<<11)	// �յ�����֡
#define UP_DN_MODE_UPF	(3<<11)	// �յ�����֡
#define BM_OPS_END_YES			(1<<13)	// 1-ĩ��RE�յ�����һ��˿ڵ��ź�

#define FPGA_REG_OPS_INFO			0xAA	//18 ĩ��RE���յ���һ���״̬
#define BM_OPS_NODE_COUNT	(0xFF<<0)	// ĩ��RE�յ�����һ��˿ڽڵ����м���
#define BM_OPS_OPT_NUM	(0xFF<<8)	// ĩ��RE�յ�����һ��˿����

#define FPGA_REG_OPT_MAX_DELAY_H	0xC0	//23 D[15:0]REC�����Ĺ���ź���ʱD23-8
#define FPGA_REG_OPT_MAX_DELAY_L	0xC1	//24 D[15:8]REC�����Ĺ���ź���ʱD7-0
#define FPGA_REG_OPT_DELAY_H		0xC2	//19 D[15:0]REC�����Ĺ���ź���ʱD23-8
#define FPGA_REG_OPT_DELAY_L		0xC3	//20 D[15:8]REC�����Ĺ���ź���ʱD7-0
#define FPGA_REG_DL_EXDELAY		    0xC4	//21 D[2:0]���з��͸�����ʱ
#define FPGA_REG_UL_EXDELAY		    0xC5	//22 D[7:0]���н��ո����ӳ�


							
#define FPGA_REG_TD_SYNC_ST		0x00D0	//58 b[4:0]-TDͬ������, b[5]-TDͬ��״̬				
#define BM_TD_SYNC_OK		(1<<5)	// 1-TDͬ��OK				
#define FPGA_REG_TD_MCH_POW_H	0x00D3	// TD�����ŵ���AD����MPow��8λ | AD���� = 10*log10(MPow /2^32)+Pdn(����PdnΪ10dbm)					
#define FPGA_REG_TD_MCH_POW_L	0x00D4	// TD�����ŵ���AD����MPow��16λ | �˿ڹ��� = AD���� - ǰ��ģ������		

#define FPGA_REG_C_TD_SYNC_ST		0x00E0	//0xDA b[4:0]-TDͬ������, b[5]-TDͬ��״̬				
#define FPGA_REG_D_TD_SYNC_ST		0x00E0	//0xDA b[4:0]-TDͬ������, b[5]-TDͬ��״̬				
#define FPGA_REG_C_TD_MCH_POW_H	0x00E2	//0xE2 TD�����ŵ���AD����MPow��16λ | AD���� = 10*log10(MPow /2^32)+Pdn(����PdnΪ10dbm)					
#define FPGA_REG_C_TD_MCH_POW_L	0x00E3	//0xE2 TD�����ŵ���AD����MPow��16λ | �˿ڹ��� = AD���� - ǰ��ģ������		
#define FPGA_REG_C_TD_SYSCH_POW_H	0x00E6	//0xE6 TDͬ���ŵ���AD����MPow��16λ | AD���� = 10*log10(MPow /2^32)+Pdn(����PdnΪ10dbm)					
#define FPGA_REG_C_TD_SYSCH_POW_L	0x00E7	//0xE7 TDͬ���ŵ���AD����MPow��16λ | �˿ڹ��� = AD���� - ǰ��ģ������		

#define FPGA_REG_C_LTE_CUR_POS	        0x00E1	//0xE1   TD_LTE��ǰ����ɨ���Ƶ����λ��				
#define FPGA_REG_C_LTE_CUR_FREQ_H	    0x00E2	//0xE2    D13-D0 ΪTD_LTE��ǰ����ɨ���Ƶ���ָ�14λ D15Ϊ����
#define FPGA_REG_C_LTE_CUR_FREQ_L	    0x00E3	//0xE3     D11-D0 ��ǰ����ɨ���Ƶ���ֵ�12λ
#define FPGA_REG_R_SLOT_TIME_B			0xEB	//BIT0~2 ֻ��BIT0��1����15���,BIT1��1����24���,	BIT2��1����33���
#define FPGA_REG_R_SLOT_TIME_C			0xEC	//D3-0:������֡��� TDL_SP_SubFrm_CFG_check  ����15ʱ��ʾ���ʧ��,D7-4:������ʱ϶��� TDL_TS_EN_check  ����15ʱ��ʾ���ʧ��


// ȫ��״ֻ̬���Ĵ���
#define FPGA_REG_GCLK_ST			0x011F	//0x40 ȫ��ʱ��״̬,20140210 delete
#define BM_INT_PULSE_EN	(1<<0)	// 1-�����ж϶�ʱ����
#define BM_CLK_125			(1<<2)	// 1-�߼�ʱ��Ϊ125M��0-�߼�ʱ��Ϊ122.88
//#define BM_CLK_LD			0x0008	// 1-AD9517����ָʾ
//#define BM_CLK_REFMON		0x0010	// 1-AD9517�ο�����ָʾ
#define BM_FPGA_PLL_LOCK	(1<<5)	// 1-FPGA��������ָʾ
//#define BM_A_BB_PLL_LOCK	0x0040	// 1-A��AD9779 PLL����ָʾ
//#define BM_B_BB_PLL_LOCK	0x0080	// 1-B��AD9779 PLL����ָʾ
//#define BM_CLK_SATATUS		0x0100	// ʱ��״̬
//#define BM_FA_PLL_ALM		(1<<9)	// 1-A��ǰ��Ƶ���ۺ�������ָʾ
//#define BM_BA_PLL_ALM		(1<<10)	// 1-A�κ��Ƶ���ۺ�������ָʾ
//#define BM_FB_PLL_ALM		(1<<11)	// 1-B��ǰ��Ƶ���ۺ�������ָʾ
//#define BM_BB_PLL_ALM		(1<<12)	// 1-B�κ��Ƶ���ۺ�������ָʾ
#define BM_WLAN_EN			(1<<13)	// 1-����WLAN����


// SERDES״̬
#define FPGA_SERDES_PLL_UNLOCK	0x011F	//0x48 ��ڷ������໷����״̬,1-ʧ��
#define BM_QUAD0_LOCK		0x0001	// QUAD0ʧ��
#define BM_QUAD1_LOCK		0x0002	// QUAD1ʧ��
#define FPGA_SERDES_FP_LOS			0x011F	//0x49 ��˿��źŶ�ʧLOS״̬,λ��Ӧ,1-�źŶ�ʧ
#define FPGA_SERDES_CDR_UNLOCK	0x011F	//0x4a �ָ�������ʱ���źź������ź�ʧ��״̬,λ��Ӧ,1-ʧ��
#define FPGA_SERDES_COMMA_LOS	0x011F	//0x4b ��ڶ��Ŷ�ʧ״̬,λ��Ӧ,1-���Ŷ�ʧ
#define FPGA_REG_SFP_CONNECT		0x00AF	//0x4c �����λ״̬0-��λ

// ����״̬��Ϣ
#define FPGA_WLAN_PORT_INFO		0X11F//95
#define BM_WLAN_LINK_ST	(1<<15)		// 1/0---��·��/û��LINK��
#define BM_WLAN_MODE		(1<<12)		// 1/0---ȫ˫��/��˫��
#define BM_WLAN_SPEED		(0x03<<10)	// ��������ָʾ
#define 	FLAG_WLAN_SPEED_10M		(0<<10)		// 10M
#define 	FLAG_WLAN_SPEED_100M	(1<<10)		// 100M
#define 	FLAG_WLAN_SPEED_1000M	(2<<10)		// 1000M

// �������SED״̬
#define FPGA_REG_SED_ST			0x011F	//0x48
#define BM_SEDINPROG		0x0001
#define BM_SEDDONE			0x0002
#define BM_SEDERR			0x0004

// Ƶ��ɨ��״̬
#define FPGA_REG_RFC_SCAN_ST		0x0100	//0x050 Ƶ��ɨ��״̬
#define BM_SCAN_BCCH_END	(1<<0)	// BCCH�������
#define BM_SCAN_TCH_END	(1<<1)	// TCH�������
#define BM_SCAN_PBCCH_END	(1<<2)	// PBCCH�������
#define BM_SCAN_EDGE_END	(1<<3)	// EDGE�������
#define BM_SCAN_AREA_END	(1<<4)	// С����Ϣ
#define FPGA_REG_BCCH_CNT			0x0101	//0x051 ɨ�赽��Ƶ��BCCH����
#define FPGA_REG_BCCH_INFO		0x0102	//0x052 Ƶ��BCCH��Ϣ, Ƶ��1���>����>������>Ƶ��2���>����>������>......
#define FPGA_REG_TCH_INFO			0x0103	//0x053 Ƶ��TCH��Ϣ, 8��16λ����
#define FPGA_REG_EDGE_CNT			0x0105	//0x055 EDGEƵ�����
#define FPGA_REG_EDGE_INFO		0x0106	//0x056 Ƶ��EDGE��Ϣ, ��10λΪƵ���
#define FPGA_REG_PBCCH_INFO		0x0107	//0x057 Ƶ��PBCCH��Ϣ, 10��16λ����
#define FPGA_REG_AREA_INFO		0x0108	//0x058 С����Ϣ

// ע������ֻ���Ĵ���
#define FPGA_REG_R_ONE_WIRE		0x011F	// DS28E01��������
#define FPGA_REG_REGISTER_ST		0x011F	// ע����֤��Ϣ
#define FPGA_REG_R_REG_NUM4		0x011F
#define FPGA_REG_R_REG_NUM3		0x011F
#define FPGA_REG_R_REG_NUM2		0x011F
#define FPGA_REG_R_REG_NUM1		0x011F

//=======================================================================

// RE�Ĵ���
#define FPGA_REG_RE_A_DPSF_H	0x2D//47	// ����ѡƵͨ���������ֵ��16λ,�������㷽ʽ:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_A_DPSF_L	0x2E//48	// ����ѡƵͨ���������ֵ��16λ
#define FPGA_REG_RE_A_UPSF_H	0x2F//49	// ����ѡƵͨ���������ֵ��16λ,�������㷽ʽ:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_A_UPSF_L	0x30//50	// ����ѡƵͨ���������ֵ��16λ

#define FPGA_REG_RE_B_DPSF_H	0x4D//79	// ����ѡƵͨ���������ֵ��16λ,�������㷽ʽ:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_B_DPSF_L	0x4E//80	// ����ѡƵͨ���������ֵ��16λ
#define FPGA_REG_RE_B_UPSF_H	0x4F//81	// ����ѡƵͨ���������ֵ��16λ,�������㷽ʽ:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_B_UPSF_L	0x50//82	// ����ѡƵͨ���������ֵ��16λ

// RE�Ĵ���
#define FPGA_REG_RE_C_DPSF_H	0x6D//163	// ����ѡƵͨ���������ֵ��16λ,�������㷽ʽ:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_C_DPSF_L	0x6E//164	// ����ѡƵͨ���������ֵ��16λ
#define FPGA_REG_RE_C_UPSF_H	0x6F//165	// ����ѡƵͨ���������ֵ��16λ,�������㷽ʽ:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_C_UPSF_L	0x70//166	// ����ѡƵͨ���������ֵ��16λ

#define FPGA_REG_RE_D_DPSF_H	0x8D//195	// ����ѡƵͨ���������ֵ��16λ,�������㷽ʽ:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_D_DPSF_L	0x8E//196	// ����ѡƵͨ���������ֵ��16λ
#define FPGA_REG_RE_D_UPSF_H	0x8F//197	// ����ѡƵͨ���������ֵ��16λ,�������㷽ʽ:10*log10(CH_SPOW /2^32)+Pdn
#define FPGA_REG_RE_D_UPSF_L	0x90//198	// ����ѡƵͨ���������ֵ��16λ


//=======================================================================

// ���������
#define FPGA_ENABLE_WRITE		FpgaWriteRegister( FPGA_REG_WRITE_PROTECT, WP_CODE_NO_PROTECT)
#define FPGA_DISABLE_WRITE		FpgaWriteRegister( FPGA_REG_WRITE_PROTECT, WP_CODE_PROTECT_ALL)

#define FPGA_SET_OPT( OPT_NO )	FpgaWriteRegister( FPGA_REG_OPT_SEL, (OPT_NO) )		// ����Ҫ�����Ĺ�ں�
#define FPGA_GET_OPT( OPT_NO )	FpgaReadRegister( FPGA_REG_OPT_SEL,(OPT_NO)  )				// ��ǰ�����Ĺ�ں�
#define FPGA_SET_LTE_SLOT( SLOT_NO )	FpgaWriteRegister( FPGA_REC_C_TD_LTE_SLOT_SEL, (SLOT_NO) )		// ����Ҫ�����Ĺ�ں�
#define FPGA_SET_TDS_SLOT( SLOT_NO )	FpgaWriteRegister( FPGA_REG_TDSLOT_CTL	, (SLOT_NO) )		// ����Ҫ�����Ĺ�ں�

#define FPGA_SET_CHANNEL(CHL)		FpgaWriteRegister( FPGA_REG_CH_SEL, (CHL) )

#define FPGA_ATT_SET_DELAY	10000		//10ms

//˥��������
#define DL_ATT_NUM	1	//����
#define UL_ATT_NUM	1	//����
//�����б�־
#define UL_ATT_FLAG_MAIN	0
#define UL_ATT_FLAG_DIVE	1
//����У׼��־λ
#define UL_GAIN_ADJ_FLAG_STEP_MODE	0x80
#define UL_GAIN_ADJ_FLAG_READ_PSF	0x40
#define UL_GAIN_ADJ_STEP_CNT_MASK	0x3F

// FPGA ������Ϣ
#define FPGA_ERR_PROG		1
#define FPGA_ERR_CHECK		2


//////////////////////////////////////////////�¼ӵ����ã�΢�͹���V02//////////////////////////////////////////////////////

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

#define FPGA_REG_R_PLL_CLK             110            //PLL�Ķ��Ĵ���

#define CALC_FPGA_FW( DF )	(INT32)((FLOAT32)(DF)/0.0125 + ((DF<0) ? -0.5 : 0.5 ))	// DF/0.0203
#define ADJUST_FPGA_FW(DF)	{ if ( (DF)<0 ) {DF += 5000;} }

#define CALC_FPGA_FW_QW( FW )			((INT32)(FW)/625)	// Ƶ���ֵ���(ռ3λ)
#define CALC_FPGA_FW_RW( FW )			((INT32)(FW)%625)	// Ƶ���ֵ�����(ռ10λ)
#define CONN_FPGA_FW_Q_R( _QW, _RW )	(((_QW)&0x07)<<10)|((_RW)&0x03FF)	// ���̺�������Ҫ��ƴ�ӳ�Ƶ���� һ��13λ

// ------------------ Variable ------------------------
extern UCHAR8 fpga_load_block;
extern _T_FPGA_CFG fpga_cfg;

#define TF_A						0
#define TF_B						1
#define TF_C						2
#define TF_D					3
//AD80305 ����д�Ĵ���λ
#define BIT_TF_DI				0x0000
#define BIT_TF_CLK				0x0000
#define BIT_TF_EN				0x0000
#define BIT_TF_RESET			0x0000

//AD9363 ����д�Ĵ���λ
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

//AD80305��ȡ�Ĵ���λ
#define BIT_TF_DO				0x0001

#define FPGA_REG_W_A_TF			0x11f
#define FPGA_REG_W_B_TF			0x11f
#define FPGA_REG_W_A_TF_RESET	0x11f
#define FPGA_REG_W_B_TF_RESET	0x11f

//AD9363д�Ĵ���λ
#define FPGA_REG_W_9363_SPI_DO_A_B		FPGA_WO_REG(0XF0)    //FPGA_WO_REG(11)
#define FPGA_REG_W_9363_SPI_DO_C		FPGA_WO_REG(0XF1)		//FPGA_WO_REG(12)

//SPI--AD9363/1197��ȡ�Ĵ���λ
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

#define FPGA_W_REG_MAX	250 		//д�Ĵ����������

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

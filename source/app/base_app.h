#ifndef _BASE_APP_H_
#define _BASE_APP_H_



#define TYPE_MIXER 0
#define TYPE_MODEN 1



#define  OFFSET_122M		     3072
#define  OFFSET_125M		     5000 
#define  DIV_122M		         0.02
#define  DIV_125M		         0.0125	         
#define  AD_FS_122M		         122.88
#define  AD_FS_125M		         125	          // ��������ʱ��


//����Ƶ����
#define CALC_FPGA_FRE_WORD(fre,fpga_clk_data)	(INT32)( (FLOAT32)pow(2,13)*1024*8*(fre)*1/(fpga_clk_data))


/******************************************GSM����Ƶ����ز���***************************************************/
#define  GSM_PLL_DL_OUT_122M_CNMOBILE         1095.6         //GSM΢�͹�ǥ�����б�������Ƶ��  ��1098.6 ��Ϊ 1098.75  9.27 PM 
#define  GSM_PLL_DL_OUT_125M_CNMOBILE         1098.25           //GSM΢�͹�ǥ�����б�������Ƶ�� 
#define  GSM_PLL_DL_OUT_150M_CNMOBILE         929           //GSM΢�͹�ǥ�����б�������Ƶ�� 
#define  GSM_PLL_UL_OUT_150M_CNMOBILE         909.3           //GSM΢�͹�ǥ�����б�������Ƶ�� 


#define  GSM_PLL_DL_OUT_122M_UNICOM           1110.6         //GSM΢�͹�ǥ�����б�������Ƶ��  ��1098.6 ��Ϊ 1098.75  9.27 PM 
#define  GSM_PLL_DL_OUT_125M_UNICOM           1113.25           //GSM΢�͹�ǥ�����б�������Ƶ�� 

/******************************************WCDMA2100����Ƶ����ز���*************************************************/
#define  WCDMA_PLL_DL_OUT_122M       2298.6          //WCDMA΢�͹�ǥ��rec���б�������Ƶ�� 
#define  WCDMA_PLL_DL_OUT_125M       2301.25            //WCDMA΢�͹�ǥ��rec���б�������Ƶ��
#define  WCDMA_PLL_DL_OUT_150M       2301.25            //WCDMA΢�͹�ǥ��rec���б�������Ƶ��


/******************************************TD����Ƶ����ز���*********************************************************/

#define  TD_SCDMA_PLL_DL_OUT_122M       2298.6          //TD_SCDMA΢�͹�ǥ��rec���б�������Ƶ�� 
#define  TD_SCDMA_PLL_DL_OUT_125M       2173.65            //TD_SCDMA΢�͹�ǥ��rec���б�������Ƶ��
#define  TD_SCDMA_PLL_DL_OUT_150M       2028           //TD_SCDMA΢�͹�ǥ��rec���б�������Ƶ��
#define  TD_SCDMA_PLL_UL_OUT_150M       2030           //TD_SCDMA΢�͹�ǥ��rec���б�������Ƶ��




/******************************************CDMA����Ƶ����ز���******************************************************/

#define  CDMA_PLL_DL_OUT_122M_CNMOBILE         1971             
#define  CDMA_PLL_DL_OUT_125M_CNMOBILE         1973.65           

#define  CDMA_PLL_DL_OUT						1971             
#define  CDMA_PLL_UL_OUT						1973.65           


/******************************************DCS1800����Ƶ����ز���****************************************************/
#define  DCS_PLL_DL_OUT_122M_CNMOBILE         1971             //DCS΢�͹�ǥ��rec���б�������Ƶ�� 
#define  DCS_PLL_DL_OUT_125M_CNMOBILE         1973.65           //DCS΢�͹�ǥ��rec���б�������Ƶ��

#define  DCS_PLL_DL_OUT_122M_UNICOM         1993.6             //DCS΢�͹�ǥ��rec���б�������Ƶ�� 
#define  DCS_PLL_DL_OUT_125M_UNICOM         1996.25            //DCS΢�͹�ǥ��rec���б�������Ƶ��

//#if defined (GUORENSOFT)
#define  DCS_PLL_DL_OUT_150M_CNMOBILE         1817.5//1802//1804.5//1840.7//1851            //DCS΢�͹�ǥ��rec���б�������Ƶ��
#define  DCS_PLL_UL_OUT_150M_CNMOBILE         1722.5//1738//1735.5//(1396+342)//(1394+344)//1762			
//#else
#define  DCS_PLL_DL_OUT_150M_UNICOM         1857//1851            //DCS΢�͹�ǥ��rec���б�������Ƶ��
#define  DCS_PLL_UL_OUT_150M_UNICOM         (1416+346)//1762

//#endif

/******************************************CMMB����Ƶ����ز���********************************************************/

                 
#define  TETRA_PLL_DL_OUT_122M       532.46            //WCDMA΢�͹�ǥ��rec���б�������Ƶ�� 
#define  TETRA_PLL_DL_OUT_125M       348            //WCDMA΢�͹�ǥ��rec���б�������Ƶ��


#define  TETRA_PLL_DL_FRQ       		363.5    
#define  TETRA_PLL_UL_FRQ       		353.5            

/******************************************LTE_TD����Ƶ����ز���********************************************************/
                 
#define  LTE_TDD_PLL_DL_OUT_122M       532.46            //WCDMA΢�͹�ǥ��rec���б�������Ƶ�� 
#define  LTE_TDD_PLL_DL_OUT_125M       532.46            //WCDMA΢�͹�ǥ��rec���б�������Ƶ��

#define  LTE_TDD_PLL_DL_OUT      		 857.5            //���б�������Ƶ�� 
#define  LTE_TDD_PLL_UL_OUT			845//828   //���б�������Ƶ��


/******************************************LTE_FDD����Ƶ����ز���********************************************************/
                 
#define  LTE_FDD_PLL_DL_OUT_122M       532.46            //WCDMA΢�͹�ǥ��rec���б�������Ƶ�� 
#define  LTE_FDD_PLL_DL_OUT_125M       532.46            //WCDMA΢�͹�ǥ��rec���б�������Ƶ��

#define  LTE_FDD_PLL_DL_OUT      		 	857.5            //���б�������Ƶ�� 
#define  LTE_FDD_PLL_UL_OUT			845//828   //���б�������Ƶ��



typedef struct _S_DYNAMIC_PLL_CFG 
{
	INT32 fnco;		// AD��NCO��������Ƶ��(KHz)
	INT32 adfs;		// ��������ʱ��(KHz)
	INT32 adfout;		// AD�����FPGA������Ƶ��(KHz), ����ADƵ��/8����AD_FS/AD_DIV

	INT32 f_mid;	// ��ƵƵ��(KHz)
	INT32 fref;		// �ο�ʱ��Ƶ��(KHz)
	INT32 fstep;	// ���񲽽�Ƶ��(KHz)
	INT32 fpfd;		// ������Ƶ��(KHz)

	UINT32 reg_n;	// 4153��N�Ĵ���
	UINT32 reg_r;	// 4153��R�Ĵ���
	INT32 ftoset;	// Ҫ���õ���Ƶ��(KHz)
	INT32 fout;	// ʵ�����Ƶ��(KHz)
} _T_DYNAMIC_PLL_CFG, *_T_PDYNAMIC_PLL_CFG;

typedef void (*LPF_RESET_DPC)(_T_PDYNAMIC_PLL_CFG); 
typedef INT32 (*LPF_CONV_FC_TO_FREQ)(INT32); 
typedef BOOL (*LPF_CHECK_LOCAL_PLL_CFG)( INT32 , INT32 , _T_PDYNAMIC_PLL_CFG , _T_PDYNAMIC_PLL_CFG  ); 
typedef INT32 (*LPF_CALC_DF)( INT32, _T_PDYNAMIC_PLL_CFG ); 
typedef INT32 (*LPF_CALC_FOUT_ADJ)(_T_PDYNAMIC_PLL_CFG , _T_PDYNAMIC_PLL_CFG ); 

typedef struct _S_MODULE_CFG	// �����ýṹ
{
	_T_DYNAMIC_PLL_CFG ul_pcf;
	_T_DYNAMIC_PLL_CFG dl_pcf;
	LPF_RESET_DPC lpf_ResetDpcUl;
	LPF_RESET_DPC lpf_ResetDpcDl;
	LPF_CONV_FC_TO_FREQ lpf_ConvFcToFreq;
	LPF_CHECK_LOCAL_PLL_CFG lpf_CheckLocalPll;
	LPF_CALC_DF lpf_CalcDf;
	LPF_CALC_FOUT_ADJ lpf_CalcFoutAdj;
} _T_MODULE_CFG, * _T_PMODULE_CFG;

#define DCS_PLL_RANGE 		20000	//26000	// ��̬��Χ(KHz)
#define PLL_RANGE 		25000	//26000	// ��̬��Χ(KHz)
#define FREQ_MARGIN	12000	//11500	// Ƶ�ʾ�߽�ļ��(KHz)
#define FBW_SUPPORT	24000	// ����֧�ֵ�Ƶ�ʴ���

// GSM ����38.8M
#define GSM_SF_STEP				0.2		// Ƶ�㲽��Ƶ��(MHz)
#define GSM_FUL_MIN			(890000L+(955-1024)*GSM_SF_STEP+FREQ_MARGIN)
#define GSM_FUL_MAX			(890000L+124*GSM_SF_STEP-FREQ_MARGIN)
#define GSM_FDL_MIN			(935000L+(955-1024)*GSM_SF_STEP+FREQ_MARGIN)
#define GSM_FDL_MAX			(935000L+124*GSM_SF_STEP-FREQ_MARGIN)
#define IS_GSM_FC( _FC )			(( ((_FC)>=0)&&((_FC)<=124) )||( ((_FC)>=955)&&((_FC)<=1023) ))
//#define IS_DCS_FC( _FC )			(( ((_FC)>=512)&&((_FC)<=636) )||( ((_FC)>=637)&&((_FC)<=736) ))


// DCS ����75M
#define DCS_SF_STEP				200		// Ƶ�㲽��Ƶ��(KHz)
#define DCS_FUL_MIN				(1710000L+(DCS_MIN_FRE_CODE_CNMOBILE-511)*DCS_SF_STEP+FREQ_MARGIN)
#define DCS_FUL_MAX			(1710000L+(885-511)*DCS_SF_STEP-FREQ_MARGIN)
#define DCS_FDL_MIN				(1805000L+(DCS_MIN_FRE_CODE_CNMOBILE-511)*DCS_SF_STEP+FREQ_MARGIN)
#define DCS_FDL_MAX			(1805000L+(885-511)*DCS_SF_STEP-FREQ_MARGIN)
#define IS_DCS_FC( _FC )			( ((_FC)>=DCS_MIN_FRE_CODE_CNMOBILE)&&((_FC)<=885) )

// WCDMA ����60M
#define WCDMA_PLL_RANGE 		20000	// W��̬��Χ(KHz)
#define WCDMA_FREQ_MARGIN	12000	// WƵ�ʾ�߽�ļ��(KHz)
#define WCDMA_FBW_SUPPORT	20000	// W����֧�ֵ�Ƶ�ʴ���Ƶ������5M����		
#define WCDMA_SF_STEP			(200)		// Ƶ�㲽��Ƶ��(KHz)
#define WCDMA_FUL_MIN			(10550*WCDMA_SF_STEP-190000+WCDMA_FREQ_MARGIN)
#define WCDMA_FUL_MAX			(10850*WCDMA_SF_STEP-190000-WCDMA_FREQ_MARGIN)
#define WCDMA_FDL_MIN			(10550*WCDMA_SF_STEP+WCDMA_FREQ_MARGIN)
#define WCDMA_FDL_MAX			(10850*WCDMA_SF_STEP-WCDMA_FREQ_MARGIN)
#define IS_WCDMA_FC( _FC )		( ((_FC)>=10550)&&((_FC)<=10850) )

// TD ����15M
//#define IS_TD_FC( _FC )			( ((_FC)>=10050)&&((_FC)<=10125) )
#define IS_TD_FC( _FC )			( ((_FC)>=10055)&&((_FC)<=10120) )
// CMMB 470~566MHz, 606~798MHz
#define CMMB_SF_STEP			(8000)		// Ƶ�㲽��Ƶ��(KHz)
#define CMMB_FDL_MIN1			( 370000+13*CMMB_SF_STEP+FREQ_MARGIN )
#define CMMB_FDL_MAX1			( 370000+24*CMMB_SF_STEP-FREQ_MARGIN )
#define IS_CMMB_FC1( _FC )		( ((_FC)>=13)&&((_FC)<=24) )
#define CMMB_FDL_MIN2			( 410000+25*CMMB_SF_STEP+FREQ_MARGIN )
#define CMMB_FDL_MAX2			( 410000+48*CMMB_SF_STEP-FREQ_MARGIN )
#define IS_CMMB_FC2( _FC )		( ((_FC)>=25)&&((_FC)<=48) )
#define IS_CMMB_FC( _FC )		( ((_FC)>=13)&&((_FC)<=48) )

#define CLK_FLAG_122_88M		0
#define CLK_FLAG_125M			1
extern UCHAR8 clk_flag;	//ʱ�ӱ�ʾ�� 0-122.88��1-125

//�汾����
#define VERSION_FLAG	            0xAA
#define VERSION_GEDT_ERRICSON_C	0
#define VERSION_GEDT_ERRICSON_G	1
#define VERSION_GEDT_JIZHUN		2  
#define VERSION_GEDT_DATANG		3  
#define VERSION_GEDT_ERRICSON_W	4  



#define VERSION_20M_NOIN			0   //20M ��һ�廯
#define VERSION_40M_NOIN			1   //40M ��һ�廯
#define VERSION_20M_IN			    2  //20M һ�廯
#define VERSION_40M_IN_A			    3   //40M һ�廯
#define VERSION_40M_IN_B			    4   //40M һ�廯
#define VERSION_40M_IN_C			    5   //40M һ�廯
#define VERSION_40M_IN_D			    6   //40M һ�廯
#define VERSION_40M_IN_E			    7   
#define VERSION_50M_IN_F			    8

#define VERSION_50M_IN_V4		    	10 
#define VERSION_50M_IN_V5		    	11 



extern UCHAR8 version_number ;

//�����汾����
#define MCU_PARAM_FLAG	            0xAB	//2014.08.29
#define MCU_PARAM_VER_0			     0      //2014.08.29
#define MCU_PARAM_VER_1			     1      //2014.08.29
#define MCU_PARAM_VER_2			     2      //2014.08.29
#define MCU_PARAM_VER_3			     3     //2014.08.29
#define MCU_PARAM_VER_4			     4    
#define MCU_PARAM_VER_5			     5    



// ����


// ����
BOOL Init_Local_Pll(UCHAR8 ucPll);
//UINT16 CalcFreqWord( INT32 freq_code, UCHAR8 Flag);
INT32 CalcFreqWord( INT32 freq_code, UCHAR8 Flag,INT32 *up_fre_word,INT32 *down_fre_word );
INT32 SearchFpCalcFreqWord( INT32 freq_code, UCHAR8 Flag,INT32 *up_fre_word,INT32 *down_fre_word );
void SetClkFlag( UCHAR8 val );
UINT32 _CalcDelayReg( UINT32 ns );
UINT32 _CalcBusyTime( UINT32 reg_val, UINT32 ch_count );
INT32 _CalcFpgaFw( INT32 df );
UINT32 _AdjustFpgaFw(INT32 df);
UINT16 _CalcFpgaFwReg( UINT32 fw );
UINT16 _CalcTdTimeParam( UINT32 tm );
FLOAT32 CalcGsmdfu( FLOAT32 freq_point, FLOAT32 fd_local );
FLOAT32 CalcDcsfu( FLOAT32 freq_point, FLOAT32 fd_local );
FLOAT32 CalcWcdmafu( FLOAT32 freq_point, FLOAT32 fu_local );
//FLOAT32 CalcTetrafu( FLOAT32 freq_point, FLOAT32 fu_local );
FLOAT32 CalcTdLtefu( FLOAT32 freq_point, FLOAT32 fd_local );
INT32 CalcFpgaFw_AB( FLOAT32 fDf )	;
INT32 CalcFpgaFw_A( FLOAT32 fDf )	;
INT32 CalcFpgaFw_B( FLOAT32 fDf )	;
INT32 CalcFpgaFw_CD( FLOAT32 fDf )	;
INT32 CalcTypeFddFpgaFw_CD( FLOAT32 fDf );
INT32  AdjustFpgaFw(INT32 iDf)	; 
UINT16 CalcFpgaFwReg( UINT32 fw );  
FLOAT32 ConvGsmFcToFreqDL( INT32 freq_code );
FLOAT32 ConvGsmFcToFreqUL( INT32 freq_code );
FLOAT32 ConvDcsFcToFreqDL( INT32 freq_code );
INT32 CalcFreqPointToFreq(UCHAR8 ucNetTye,INT32 freq_code);
//INT32 CalcGsmFreqWord( INT32 freq_code, FLOAT32 fd_local );
INT32 SearchFpCalcGsmFreqWord( INT32 freq_code, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
//INT32 CalcDcsFreqWord( INT32 freq_code, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );
//INT32 CalcDcsFreqWord( INT32 freq_code, FLOAT32 fd_local );
//INT32 CalcWcdmaFreqWord( INT32 freq_code, FLOAT32 fd_local );
INT32 SearchFpCalcTDFreqWord( INT32 freq_code, FLOAT32 fu_local );

void MenCpy(void *pvDst,const void * pvSrc, UINT usLen);
//INT32 CalcCdma800FreqWord( INT32 freq_code, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word );

#endif




















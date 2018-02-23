/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : PartA_app.c
* Description : A����غ���
* Version     : v0.1
* Author      : RJ
* Date        : 2010-08-17
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-08-17		v0.1			��ʼ�汾
**************************************************************/
#include "Header.h"

extern UCHAR8 sys_temp_buff[];
extern UCHAR8 gsm_type_a;	// gsmģʽ
extern UCHAR8 gsm_type_b;	// gsmģʽ
extern FLOAT32 fpga_dginp_d;		// B����������˲�������
extern FLOAT32 fpga_dgcic_d;		// B�����������˲�������(0)
extern FLOAT32 fpga_uginp_d;		// B����������˲�������(0)
extern FLOAT32 fpga_ugcic_d;		// B�����������˲�������
// extern _T_FPGA_CFG fpga_cfg;
extern UINT16 fpga_d_regbk[];		// ����д��Ĵ���ginp+gcic+{��������,��������}x ch_count+busy_time+traffic_end
extern UINT32 module_param_chg_flag;		//ϵͳ���������޸ı�־
extern UINT32 fpga_load_status;
extern _T_MODULE_CFG mod_cfg_a;

//UINT32 adf4153bf_n_reg = ADF4153_WCDMA_FN;
//UINT32 adf4153bf_r_reg = ADF4153_WCDMA_FR;
//UINT32 adf4153bb_n_reg = ADF4153_WCDMA_BN;
//UINT32 adf4153bb_r_reg = ADF4153_WCDMA_BR;
//FLOAT32 b_fdl;
//FLOAT32 b_ful;

_T_MODULE_CFG mod_cfg_d;
//extern UCHAR8 ucAd9122RegVal[7][41][2][2];


/*************************************************************
Name:	InitPart         
Description:��ʼ��A��
Input:void
Output:void      
Return:-1:ʧ�ܣ�1: �ɹ�            
**************************************************************/
void InitPartD(void)
{
	UCHAR8 net_type;
	
	if ( fpga_cfg.d_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

	//TRACE_INFO("Init Part-B.\r\n");

	if ( fpga_cfg.b_net_type==NET_DIVE )
	{
		// B��Ϊ�ּ�����A�β���������
		net_type = fpga_cfg.a_net_type;
	}
	else
	{
		net_type = fpga_cfg.b_net_type;
	}
	ReadWriteTF(TF_D,1,0X56,0X00);//�����У����ͨ����
	
	CheckChannelSetD();
	
	Init_Local_Pll(B_MIXER); //822 U PLL  A�����б��� ,REΪ��Ƶ
	Init_Local_Pll(B_MODEN);//839 D PLL  A�����б���  REΪ����	


	//д��У׼����ϵͳ�¶�
	if ( b_FALSE==FpgaSetUlAttAdjTableD() )
	{
		//TRACE_ERROR("No B UL ATT Adjust Table\r\n");
	}

	if ( b_FALSE==FpgaSetDlAttAdjTableD() )
	{
		//TRACE_ERROR("No B DL ATT Adjust Table\r\n");
	}
	WTD_CLR;

}

#if 0
/*************************************************************
Name:InitDA_A         
Description:��ʼ��AD9779
Input:main_dive_flag:1���ã�0:�ּ�
Output:void      
Return:-1:ʧ�ܣ�0: �ɹ�            
**************************************************************/
BOOL InitDA_B()
{
   UCHAR8 i; 
   //TRACE_INFO("Init 9122-B."); 
   HardReset9122B(); 

	for (i=0; i<41; i++)
	{  
      Ad9122Write(ucAd9122RegVal[fpga_cfg.b_net_type][i][clk_flag][0],ucAd9122RegVal[fpga_cfg.b_net_type][i][clk_flag][1],DA_B_FLAG);
      UsNopDelay(10);
	}

     return b_TRUE;

}

/*************************************************************
Name:CloseDA_B         
Description:��ʼ��AD9779
Input:main_dive_flag:1���ã�0:�ּ�
Output:void      
Return:-1:ʧ�ܣ�0: �ɹ�            
**************************************************************/
void CloseDA_B()
{	
	UCHAR8 val; 
	
	WTD_CLR; 
    Ad9122Write(0x01,0xf0,DA_B_FLAG);
    UsNopDelay(10);

}

/*************************************************************
Name:OpenDA_B         
Description:��ʼ��AD9779
Input:main_dive_flag:1���ã�0:�ּ�
Output:void      
Return:-1:ʧ�ܣ�0: �ɹ�            
**************************************************************/
void OpenDA_B()
{	
	UCHAR8 ret,i; 
	
	WTD_CLR; 
    Ad9122Write(0x01,0x10,DA_B_FLAG);
    UsNopDelay(10);

}
#endif 

/*************************************************************
Name: FpgaGetDlUlPowerB
Description: ��ȡAD��DA���ʣ��Ƴ��˿ڹ���
Input:void
Output:void         
Return:void
**************************************************************/
void FpgaGetDlUlPowerD()
{
	UINT16 power;
	FLOAT32 tmp;  
	FLOAT32 f_pow, f_gcmps;
	INT32 reg_val;

	if ( fpga_cfg.d_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

// D��
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(1);
	FPGA_DISABLE_WRITE;

	
	// AD����
	FpgaPowSelSlot(FPGA_REG_D_FAD_POW_H);
	reg_val= (FpgaReadRegister(FPGA_REG_D_FAD_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_D_FAD_POW_L));
	//TRACE_INFO("D---reg_val[%04x]\r\n",reg_val);

	f_pow = CALC_POWER( reg_val );
	// ǰ�˲���Gfcmps
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_D_FG_CMPS));
	// �˿����빦��Pin = Pad + Gfcmps + Gcic - Gfnom
	if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
	|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
	|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
	|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
	|| (version_number == VERSION_50M_IN_V5)
	)
		tmp = f_pow+fpga_dgcic_d+f_gcmps - FPGA_REC_GFNOM+(CHAR8)sys_param_1b[MADD_D_DL_POW_ADJ].val/10.0;
	else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
		tmp = f_pow+fpga_dgcic_d+f_gcmps - FPGA_REC_GFNOM+ (INT16)sys_param_2b[MADD_D_UDPX_IN_GAIN].val/10.0+(CHAR8)sys_param_1b[MADD_D_DL_POW_ADJ].val/10.0;
	if ( tmp<-123 )
	{
		tmp = -123;
	}
//	TRACE_INFO("pow_d=[%f]\n",tmp);

	sys_param_2b[MADD_D_DL_TOTAL_POW].val = (INT16)tmp;

	sys_param_1b[MADD_D_DL_POW_1B].val = (UCHAR8)tmp;
	//TRACE_INFO("D---sys_param_2b[MADD_D_DL_TOTAL_POW].val[%04x]\r\n",sys_param_2b[MADD_D_DL_TOTAL_POW].val);

	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(2);
	FPGA_DISABLE_WRITE;

	// DA����
	FpgaPowSelSlot(FPGA_REG_D_BDA_POW_H);
	reg_val= (FpgaReadRegister(FPGA_REG_D_BDA_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_D_BDA_POW_L));
	f_pow = CALC_POWER_1( reg_val );
	// ǰ�˲���Gfcmps
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_D_BG_CMPS));
	// �˿��������Pout = Pda - Gfcmps - Gcic + Gfnom
	tmp = f_pow-fpga_dginp_d-f_gcmps + FPGA_REC_GDNOM;
	if ( tmp<-123 )
	{
		tmp = -123;
	}

	sys_param_2b[MADD_D_UL_TOTAL_POW].val = (INT16)tmp;

	sys_param_1b[MADD_D_UL_POW_1B].val = (UCHAR8)tmp;

}


/*************************************************************
Name:FpgaSetGsmChannel
Description:FPGA����ͨ��Ƶ��
Input:
	channel: ͨ����
	enable: ͨ��ʹ��
	freq_point: Ƶ���
Output:void         
Return:void        
**************************************************************/
void PD_SetChannel( UCHAR8 channel, UCHAR8 enable, INT32 freq_code )
{
	UINT32 reg_val;
	UINT16 reg_val_16;
	INT32 up_fre_word=0;
	INT32 down_fre_word=0;

	if ( fpga_cfg.d_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

	if ( channel>=MAX_CHANNEL_COUNT )
	{
		return;
	}
	WTD_CLR;

	CalcFreqWord( freq_code,SYS_D_FLAG,&up_fre_word, &down_fre_word );
	reg_val=down_fre_word;
	reg_val_16 =(UINT16)reg_val&0x0fff;
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(channel);		// ����ͨ����
	if ( 1 == sys_param_1b[MADD_D_DCH_EN1+channel].val )		// ����Ƶ���ּĴ���
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
 	FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_L_12 , reg_val_16);
	
	reg_val_16=(UINT16)(reg_val>>12)&0x3fff;
	
	if(reg_val&0x80000000) 
	{
		reg_val_16 |=FREQ_SIG;
	}
	
	FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_H_14, reg_val_16);
	FPGA_DISABLE_WRITE;

	////reg_val=up_fre_word;
	reg_val=0;
	reg_val_16 =(UINT16)reg_val&0xfff;
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(channel);		// ����ͨ����
	if ( 1 ==  sys_param_1b[MADD_D_UCH_EN1+channel].val )		// ����Ƶ���ּĴ���
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
 	FpgaWriteRegister(FPGA_REG_D_D_FREQ_CTL_L_12, reg_val_16);
	
	reg_val_16 =(UINT16)((reg_val>>12)&0x3fff); ;
	if(reg_val&0x80000000) 
	{
		reg_val_16 |=FREQ_SIG;
	}
	FpgaWriteRegister(FPGA_REG_D_D_FREQ_CTL_H_14, reg_val_16);
	
	FPGA_DISABLE_WRITE;	

	WTD_CLR;
}
#if 0
/*************************************************************
Name:FpgaSetGsmChannel
Description:FPGA����ͨ��Ƶ��
Input:
	channel: ͨ����
	enable: ͨ��ʹ��
	freq_point: Ƶ���
Output:void         
Return:void        
**************************************************************/
void PB_SetTdMainChannel( UCHAR8 enable, INT32 freq_code )
{
	UINT16 reg_val;

	if ( fpga_cfg.b_net_type==NET_NONE )
	{
		return;
	}

	reg_val = CalcFreqWord( freq_code,SYS_B_FLAG );
    reg_val = CalcFpgaFwReg(reg_val); 
	
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(0);		// ����ͨ����
	if ( 1 == enable )		// ����Ƶ���ּĴ���
	{
		reg_val |= SF_CHANNEL_EN;
	}
 	FpgaWriteRegister(FPGA_REG_TD_MAIN_CH, reg_val);
	FPGA_DISABLE_WRITE;
	
	WTD_CLR;
}

#endif 

/*************************************************************
Name: FpgaSetOutAttValueB
Description: ����B�����ATT˥����
Input:
Output:void         
Return:void
**************************************************************/
void FpgaSetOutAttValueD()
{
	FLOAT32 g_odpx;
	FLOAT32 gfcmp;
	FLOAT32 pda;
	FLOAT32 psf;
	FLOAT32 g_dcmps;
	UINT16 tmp;
	INT16 i;
	UINT16 gcmp;
	UCHAR8 * p_dat = sys_temp_buff;

	tmp = 0;
	for ( i=0; i<sys_param_1b[MADD_D_CHANNEL_COUNT].val; i++ )
	{
		if ( 0!=sys_param_1b[MADD_D_UCH_EN1+i].val )
		{
			tmp++;
		}
	}
	if ( 0==tmp )
	{
		return;
	}
	
	//pda = CALC_DA_MAX_POW(tmp);

	if ( fpga_cfg.d_net_type==NET_DIVE )
	{
		// B��Ϊ�ּ�����A�β���������
		i = fpga_cfg.d_net_type;
	}
	else
	{
		i = fpga_cfg.d_net_type;
	}

	switch ( i )
	{
#if 0
	case NET_TYPE_GSM900:
	case NET_TYPE_DCS1800:
		if ( fpga_cfg.d_ultra_info == FPGA_B_NT_GSM_D_WB )	// �ּ����GSM
		{
			pda = -21+FPGA_PDN;
		}
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;

	case NET_TYPE_WCDMA2100:
		if ( fpga_cfg.d_ultra_info == FPGA_B_NT_WCDMA_WB )	// ���WCDMA
		{
			pda = -21+FPGA_PDN;
		}
		else
		{
			pda = CALC_DA_MAX_POW_WCDMA(tmp);
		}
		break;

	case NET_TYPE_TD:
		if ( fpga_cfg.d_ultra_info == FPGA_B_NT_TD_WB )	// ���TD
		{
			pda = -21+FPGA_PDN;//
		}
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
//	#ifdef TD_TYPE_WB
//		pda = -21+FPGA_PDN;
//	#else
//		pda = CALC_DA_MAX_POW(tmp);
//	#endif
		break;

	case NET_TYPE_CDMA:
		if (( fpga_cfg.d_ultra_info == FPGA_B_NT_CDMA_WB)	// ���CDMA
			||( fpga_cfg.d_ultra_info == FPGA_B_NT_CDMA_D_WB))	// ����ּ�CDMA
		{
			pda = -21+FPGA_PDN;
		}	
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;

	case NET_TYPE_TETRA:
		if ( fpga_cfg.d_ultra_info == FPGA_B_NT_TETRA_D_WB )	// �ּ������Ⱥ
		{
			pda = -21+FPGA_PDN;
		}	
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;
#endif
		case NET_TYPE_LTE_TD:
			if( version_number==VERSION_40M_NOIN )	
				pda = -21+FPGA_PDN;
			if( ( version_number==VERSION_40M_IN_A ) || (version_number==VERSION_40M_IN_B)  
			|| (version_number==VERSION_40M_IN_C) || (version_number==VERSION_40M_IN_D)
			|| (version_number == VERSION_40M_IN_E) || (version_number == VERSION_50M_IN_F)
			|| (version_number == VERSION_50M_IN_V4)
			|| (version_number == VERSION_50M_IN_V5)
			)	
				pda = -21+FPGA_PDN+3;
			else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN) )
				pda = -21+FPGA_PDN+6;
		break;
		
		case NET_TYPE_LTE_FDD:
			pda = -21+FPGA_PDN;
		break;		

	default:
		pda = CALC_DA_MAX_POW(tmp);
	}
	
	
	g_odpx = ((INT16)sys_param_2b[MADD_D_UDPX_OUT_GAIN].val)/10.0;

	gfcmp = 0; //CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));

	psf = CALC_OUTPUT_PSF( (FLOAT32)((INT16)sys_param_2b[MADD_D_UCH_MAX_POW1+0].val/10.0), 
			sys_param_1b[MADD_D_UL_PA_GAIN].val, 
			g_odpx, gfcmp, FPGA_REC_GDNOM);

	g_dcmps = CALC_GDCMPS(pda, psf, fpga_uginp_d);//2012.6.20

	gcmp = CALC_GS_REG( g_dcmps );
	
	//TRACE_DEBUG("Pda=%f, Psf=%f, Ginp=%f, GDCMPS=%f, gcmp=%04X, ", pda, psf, fpga_uginp_d, g_dcmps, gcmp);
		
//	FlashReadOnePage(FLASH_D_UL_ATT_ADJ_TBL_PAGE, 0, p_dat);
	FlashRead(FLASH_D_UL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE);
	
	if ( ( p_dat[0] != 0xEC )||( p_dat[1] != 0x69 ) )
	{
		// ��˥�����
		i = (INT16)(g_dcmps*2);
		if ( i<0 )
		{
			i=0;
		}
		else if ( i>63 )
		{
			i=63;
		}
	}
	else
	{
		for ( i=0; i<64; i++ )
		{
			tmp = p_dat[3+i*2]|(p_dat[3+i*2+1]<<8);

			if ( tmp>gcmp )
			{
				break;
			}
		}
		if ( i>0 )
		{
			i--;
		}
	}
	
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_D_ATT3_CAL, i&0x3F);
	FpgaWriteRegister(FPGA_REG_D_ATT3_EN,0x01);	
	FPGA_DISABLE_WRITE;
	//TRACE_DEBUG_WP("Att=%d\r\n", i);
	WTD_CLR;
		
}

/*************************************************************
Name:FpgaWorkEnableD
Description: FPGA��Ƶ����ʹ��
Input:
	ab_flag: AB��ѡ��
	enable: 1-ʹ��
Output:void         
Return:void
**************************************************************/
void FpgaWorkEnableD( UCHAR8 enable )
{
	UINT16 tmp; 

	
	if ( fpga_cfg.d_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

	tmp = FpgaReadRegister(FPGA_REG_D_ATT_CTL);
//	tmp &= (~(ATT_MODE_MASK));
	
	if ( 1==enable )
	{
		tmp |= ATT_WORK_EN;			// ʹ�ܹ���
	}
	else
	{
		EnableModulatorD(0);				// �ضϵ��������
		tmp &= (~ATT_WORK_EN);		// ֹͣ����
	}

	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_D_ATT_CTL, tmp );	
	FPGA_DISABLE_WRITE;
	
	if ( 1==enable )
	{
		UsNopDelay( 500000 );			// ��ʱ500ms
		EnableModulatorD(1);			// ʹ�ܵ��������
		WTD_CLR;
	}
}

/*************************************************************
Name:FpgaIsEnableD
Description: ����FPGAʹ��״̬
Input:void
Output:void         
Return:
	b_TRUE-��ʹ��
	b_FALSE-δʹ��
**************************************************************/
BOOL FpgaIsEnableD()
{
	UINT16 tmp; 
	tmp = FpgaReadRegister(FPGA_REG_D_ATT_CTL);

	return ( 0==(tmp & ATT_WORK_EN) ) ? b_FALSE : b_TRUE;
}
#if 0
/*************************************************************
Name: SetFpgaFreqAdj         
Description: ����FPGA AD����,DA���Ƶ�ʲ���
Input:void
Output:void      
Return:-1:ʧ�ܣ�1: �ɹ�            
**************************************************************/
void FpgaSetFreqAdjB(void)
{

	
} 

#endif 
/*************************************************************
Name:	FpgaSetUlAttAdjTable
Description:	��FPGAд������У׼���
Input: 
	ab_flag: AB��ѡ��
Output:void
Return:0:û�з���У׼���1:�ɹ�
**************************************************************/
BOOL FpgaSetUlAttAdjTableD()
{
	UINT16 att_val_reg;
	UCHAR8 att_no;
	UINT16 i;
	UCHAR8 *p_dat = sys_temp_buff;
	INT32 ginp, gcic;

	TRACE_INFO("FpgaSetUlAttAdjTableD......\r\n");

//	FlashReadOnePage( FLASH_D_UL_ATT_ADJ_TBL_PAGE, 0, p_dat );
	FlashRead( FLASH_D_UL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE );
	
	att_no = p_dat[2];
	if (( p_dat[0] != 0xEC )||( p_dat[1] != 0x69 ) )		//||( att_no > DL_ATT_NUM))
	{
		//TRACE_INFO_WP(". No Tbl!\r\n");
		return b_FALSE;
	}
	p_dat+=3;
	//TRACE_INFO_WP("(%d)", att_no);

	FPGA_ENABLE_WRITE;
	for ( i=0; i<64; i++ )
	{
		att_val_reg = (UINT16)(((UINT16)p_dat[0]|( p_dat[1]<<8 ))*pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_D].val/10.0/20)));
		p_dat += 2;

		WTD_CLR;						
		TRACE_INFO_WP("FpgaSetUlAttAdjTableD================= att_val_reg=%x,i=%d,(UINT16)p_dat[0]|( p_dat[1]<<8 )=[%x],pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_D].val/10.0/20))=[%f]\r\n", att_val_reg,i,(UINT16)p_dat[0]|( p_dat[1]<<8 ),pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_D].val/10.0/20)));

		FpgaWriteRegister( FPGA_REG_ATT_ADJ_TBL, (ATT_SEL_D3|i) );
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_DAT, att_val_reg );
	}
	FPGA_DISABLE_WRITE;

	ginp = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_uginp_d = ginp/10000.0;
	
	gcic = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_ugcic_d = gcic/10000.0;
	
	fpga_d_regbk[0] = (UINT16)((INT32)(ginp/100)&0xFFFF);
	//TRACE_INFO_WP(". ginp=%f. gcic=%f\r\n", fpga_uginp_b, fpga_ugcic_b);
//#endif 	
	WTD_CLR;
	return b_TRUE;

}

/*************************************************************
Name:	FpgaSetDlAttAdjTable
Description:	��FPGAд������У׼���
Input: 
	ab_flag: AB��ѡ��
Output:void
Return:0:û�з���У׼���1:�ɹ�
**************************************************************/
BOOL FpgaSetDlAttAdjTableD()
{
	UINT16 att_val_reg;
	UCHAR8 att_no;
	UINT16 i;
	UCHAR8 *p_dat = sys_temp_buff;
	INT32 ginp, gcic;
//#if 0
	if ( fpga_cfg.b_net_type==NET_DIVE )
	{
		// B��Ϊ�ּ�������������
		return;
	}

	//TRACE_INFO("Load Dl Att Tbl_B");

//	FlashReadOnePage( FLASH_D_DL_ATT_ADJ_TBL_PAGE, 0, p_dat );
	FlashRead( FLASH_D_DL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE );
	
	att_no = p_dat[2];
	if (( p_dat[0] != 0xEC )||( p_dat[1] != 0x69 ) )		//||( att_no > DL_ATT_NUM))
	{
		//TRACE_INFO_WP(". No Tbl!\r\n");
		return b_FALSE;
	}
	p_dat+=3;
	//TRACE_INFO_WP("(%d)", att_no);

	FPGA_ENABLE_WRITE;
	for ( i=0; i<64; i++ )
	{
		WTD_CLR;
		att_val_reg = (UINT16)(((UINT16)p_dat[0]|( p_dat[1]<<8 ))/pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_D].val/10.0/20)));
		TRACE_INFO_WP("FpgaSetDlAttAdjTableD================= att_val_reg=%x,i=%d,(UINT16)p_dat[0]|( p_dat[1]<<8 )=[%x],pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_D].val/10.0/20))=[%f]\r\n", att_val_reg,i,(UINT16)p_dat[0]|( p_dat[1]<<8 ),pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_D].val/10.0/20)));

		p_dat += 2;
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_TBL, (ATT_SEL_D1|i) );
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_DAT, att_val_reg );
	}
	FPGA_DISABLE_WRITE;

	ginp = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_dginp_d = ginp/10000.0;

	gcic = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_dgcic_d = gcic/10000.0;
	
	fpga_d_regbk[1] = (UINT16)((INT32)(gcic/100)&0xFFFF);

	//TRACE_INFO_WP(". ginp=%f. gcic=%f\r\n", fpga_dginp_b, fpga_dgcic_b);
//#endif 
	WTD_CLR;
	return b_TRUE;

}

/*************************************************************
Name:	CheckChannelSetD
Description:	���Ƶ�������Ƿ�Ϸ������ж��Ƿ���Ҫ�л�����
Input: void
Output:void
Return: 0:�����д�  	1:����OK
**************************************************************/
UCHAR8 CheckChannelSetD( void )
{
#if ( D_NETWORK_TYPE == NET_DIVE )
#define PART_D_TYPE C_NETWORK_TYPE
#else
#define PART_D_TYPE D_NETWORK_TYPE
#endif

#if 0//( PART_B_TYPE != NET_NONE )
	UCHAR8 ch;
	UCHAR8 flag = 0;

	for ( ch=0; ch<sys_param_1b[MADD_B_CHANNEL_COUNT].val; ch++ )	// ��������ͨ��
	{
		if ( sys_param_1b[MADD_B_DCH_EN1+ch].val==1 )	// ֻ��ͨ��ʹ�ܲż��
		{
			// ���жϱ�ԵƵ��,��Ϊ���һ������֧��
		#if (PART_B_TYPE == NET_TYPE_GSM900)	// GSM900
			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, 96, 124) )
			{
				flag |= 0x01;	// ��ͨ
				continue;
			}

			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, 0, 94) )
			{
				flag |= 0x02;	// �ƶ�
				continue;
			}
			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, 975, 1023) )
			{
				flag |= 0x02;	// �ƶ�
				continue;
			}
		#elif (PART_B_TYPE == NET_TYPE_DCS1800)	// DCS1800
			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, 637, 736) )
			{
				flag |= 0x01;	// ��ͨ
				continue;
			}

			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, 512, 636) )
			{
				flag |= 0x02;	// �ƶ�
				continue;
			}
		#endif
		}
	}

	if ( 0x03 == flag )		// ͬʱ�������ƶ�����ͨƵ�㣬����
	{
		return 0;
	}
	
#ifdef GSM_TYPE_UNICOM
		G2Tpye = G2_TYPE_UNICOM;
#elif defined(GSM_TYPE_CNMOBILE)
		G2Tpye = G2_TYPE_CNMOBILE;
#endif

	// �л�����ͨ����
	if ( (flag==0x01)&&(G2Tpye!=G2_TYPE_UNICOM) )
	{
		module_param_chg_flag|=PCHG_B_FL_CHG;
	}
	else if ( (flag==0x02)&&(G2Tpye!=G2_TYPE_CNMOBILE) )
	{
		module_param_chg_flag|=PCHG_B_FL_CHG;
	}


#endif

#undef PART_D_TYPE

	return 1;
}
//#endif 
/*************************************************************
Name:RFWorkEnableD
Description: ��Ƶ����ʹ��
Input:
	ab_flag: AB��ѡ��
	enable: 1-ʹ��
Output:void         
Return:void
**************************************************************/
void RFWorkEnableD( void )
{
	UINT16 tmp; 
	UINT16 reg;
	UCHAR8 npcs;
	WTD_CLR;
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return; 	
	}
	
	if ( fpga_cfg.d_net_type==NET_NONE )
	{
		return;
	}
	npcs = fpga_cfg.d_9363;

	//����
	tmp = ReadWriteTF(npcs,0,0x57,0);
	if(sys_param_1b[MADD_D_DL_RF_EN].val == 0)
	{
		tmp = tmp&0XFE;//д0��
	}
	else
	{
		tmp = tmp|0X01;//д1�ر�
	}
	ReadWriteTF(npcs,1,0x57,tmp);
#if 0
	//����
	tmp = ReadWriteTF(TF_C,0,0x53,0);
	if(sys_param_1b[MADD_D_DL_RF_EN].val == 0)
	{
		tmp = tmp&0XEB;//д0��
	}
	else
	{
		tmp = tmp|0X14;//д1�ر�
	}
	ReadWriteTF(TF_C,1,0x53, tmp);
#endif	
} 





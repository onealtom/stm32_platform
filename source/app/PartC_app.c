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
extern FLOAT32 fpga_dginp_c;		// A����������˲�������
extern FLOAT32 fpga_dgcic_c;		// A�����������˲�������(0)
extern FLOAT32 fpga_uginp_c;		// A����������˲�������(0)
extern FLOAT32 fpga_ugcic_c;		// A�����������˲�������
// extern _T_FPGA_CFG fpga_cfg;
extern UINT16 fpga_c_regbk[];		// ����д��Ĵ���ginp+gcic+{��������,��������}x ch_count+busy_time+traffic_end
extern UINT32 module_param_chg_flag;		//ϵͳ���������޸ı�־
extern UINT32 fpga_load_status;
_T_MODULE_CFG mod_cfg_c;
//extern UCHAR8 ucAd9122RegVal[7][41][2][2];



/*************************************************************
Name:	InitPartA         
Description:��ʼ��A��
Input:void
Output:void      
Return:-1:ʧ�ܣ�1: �ɹ�            
**************************************************************/
void InitPartC(void) 
{
	// ��ʼ��4153��Ƶ��
	//TRACE_INFO("Init Part-A.\r\n");

	if ( fpga_cfg.c_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}
	ReadWriteTF(TF_C,1,0X56,0X00);//�����У����ͨ����
	CheckChannelSetC();

    TRACE_ERROR("eda4\r\n");
	Init_Local_Pll(A_MIXER); //822 U PLL  A�����б��� ,REΪ��Ƶ
	Init_Local_Pll(A_MODEN);//839 D PLL  A�����б���  REΪ����
 
	//д��У׼����ϵͳ�¶�   
	if ( b_FALSE==FpgaSetUlAttAdjTableC() )
	{
		//TRACE_ERROR("No A UL ATT Adjust Table\r\n");
	}

	if ( b_FALSE==FpgaSetDlAttAdjTableC() )
	{
		//TRACE_ERROR("No A DL ATT Adjust Table\r\n");
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
BOOL InitDA_A()
{
	
	UCHAR8 ret,i; 
	
	WTD_CLR; 
	//Reset DA 
	HardReset9122A(); 

	for (i=0; i<41; i++)
	{  
      Ad9122Write(ucAd9122RegVal[fpga_cfg.a_net_type][i][clk_flag][0],ucAd9122RegVal[fpga_cfg.a_net_type][i][clk_flag][1],DA_A_FLAG);
      UsNopDelay(10);
	}
	
    WTD_CLR;   
	  
	if (Ad9122Read(AD9122_CHIP_ID_1F,DA_A_FLAG) != 0x08)
	{
		//TRACE_INFO_WP("init AD9122 fail\r\n");
		return b_FALSE; 
	}    
	
	//TRACE_INFO_WP("init AD9122 Sueess\r\n");
	return b_TRUE;
}
#endif


/*************************************************************
Name: FpgaGetDlUlPowerC
Description: ���������������
Input:void
Output:void         
Return:void
**************************************************************/
void FpgaGetDlUlPowerC()
{
	UINT16 power; 
	FLOAT32 tmp;
	FLOAT32 f_pow, f_gcmps;
	INT32 reg_val;

	if ( fpga_cfg.c_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(1);
	FPGA_DISABLE_WRITE;

	// AD����,���빦��
	FpgaPowSelSlot(FPGA_REG_C_FAD_POW_H);
	reg_val= (FpgaReadRegister(FPGA_REG_C_FAD_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_C_FAD_POW_L));
	//TRACE_INFO("C---reg_val[%04x]\r\n",reg_val);
	f_pow = CALC_POWER( reg_val );
	// ǰ�˲���Gfcmps 
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_C_FG_CMPS));
	// �˿����빦��Pin = Pad + Gfcmps + Gcic - Gfnom
	if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
	|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
	|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
	|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
	|| (version_number == VERSION_50M_IN_V5)
	)
		tmp = f_pow+fpga_dgcic_c+f_gcmps - FPGA_REC_GFNOM+(CHAR8)sys_param_1b[MADD_C_DL_POW_ADJ].val/10.0;
	else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
		tmp = f_pow+fpga_dgcic_c+f_gcmps - FPGA_REC_GFNOM+ (INT16)sys_param_2b[MADD_C_UDPX_IN_GAIN	].val/10.0+(CHAR8)sys_param_1b[MADD_C_DL_POW_ADJ].val/10.0;
	if ( tmp<-123 )
	{
		tmp = -123;
	} 
//	TRACE_INFO("pow_c=[%f]\n",tmp);

	sys_param_2b[MADD_C_DL_TOTAL_POW].val = (INT16)tmp;

	sys_param_1b[MADD_C_DL_POW_1B].val = (UCHAR8)tmp;
	//TRACE_INFO("C---sys_param_2b[MADD_C_DL_TOTAL_POW].val[%04x]\r\n",sys_param_2b[MADD_C_DL_TOTAL_POW].val);

	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(2);
	FPGA_DISABLE_WRITE;

	// DA���� �������
	FpgaPowSelSlot(FPGA_REG_C_BDA_POW_H);
	reg_val= (FpgaReadRegister(FPGA_REG_C_BDA_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_C_BDA_POW_L));
//	TRACE_INFO("reg_val[%04x]\n",reg_val);

	f_pow = CALC_POWER_1( reg_val );
//		TRACE_INFO("f_pow[%f]\n",f_pow);

	// ��˲���Gfcmps
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_C_BG_CMPS));
//		TRACE_INFO("f_gcmps[%f]\n",f_gcmps);
//		TRACE_INFO("fpga_uginp_c[%f]\n",fpga_uginp_c);

	// �˿��������Pout = Pda - Gfcmps - Gcic + Gfnom
	tmp = f_pow-fpga_uginp_c-f_gcmps + FPGA_REC_GDNOM;
	if ( tmp<-123 )
	{
		tmp = -123;
	}
//	TRACE_INFO("tmp[%d]\n",(INT16)tmp);
//	TRACE_INFO("(INT16)tmp[%d],reg_val[%04x],f_pow[%f],fpga_uginp_c[%f],f_gcmps[%f]\n",(INT16)tmp,reg_val,f_pow,fpga_uginp_c,f_gcmps);

	sys_param_2b[MADD_C_UL_TOTAL_POW].val = (INT16)tmp;

	sys_param_1b[MADD_C_UL_POW_1B].val = (UCHAR8)tmp;

}


/*************************************************************
Name:PC_SetChannel
Description:FPGA����ͨ��Ƶ��
Input:
	channel: ͨ����
	enable: ͨ��ʹ��
	freq_point: Ƶ���
Output:void         
Return:void        
**************************************************************/
void PC_SetChannel( UCHAR8 channel, UCHAR8 enable, INT32 freq_code )
{
	UINT32 reg_val;
	UINT16 reg_val_16;

	INT32 up_fre_word=0;
	INT32 down_fre_word=0;

	if ( fpga_cfg.c_net_type==NET_NONE )
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

	CalcFreqWord( freq_code ,SYS_C_FLAG,&up_fre_word,&down_fre_word);

	reg_val = down_fre_word;
	//reg_val=0;
	reg_val_16 =(UINT16)reg_val&0x0fff;
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(channel);		// ����ͨ����
	if ( 1 ==  sys_param_1b[MADD_C_DCH_EN1+channel].val  )		// ����Ƶ���ּĴ���
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
 	FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_L_12, reg_val_16);
	
	reg_val_16=(UINT16)(reg_val>>12)&0x3fff;
	if(reg_val&0x80000000)
	{
		reg_val_16 |=FREQ_SIG;
	}
	FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_H_14, reg_val_16);
	FPGA_DISABLE_WRITE;

	
	reg_val=up_fre_word;
	//reg_val=0;
	reg_val_16 =(UINT16)reg_val&0xfff;
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(channel);		// ����ͨ����
	if ( 1 ==  sys_param_1b[MADD_C_UCH_EN1+channel].val )		// ����Ƶ���ּĴ���
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
 	FpgaWriteRegister(FPGA_REG_C_D_FREQ_CTL_L_12, reg_val_16);

	reg_val_16=(UINT16)(reg_val>>12)&0x3fff;
	if(reg_val&0x80000000)
	{
		reg_val_16 |=FREQ_SIG;
	}	
	FpgaWriteRegister(FPGA_REG_C_D_FREQ_CTL_H_14, reg_val_16);
	
	FPGA_DISABLE_WRITE;	

	WTD_CLR;
		
}

void PC_SetTdMainChannel( UCHAR8 enable, INT32 freq_code )
{
	UINT16 reg_val_16;
	INT32 up_fre_word, down_fre_word;

	up_fre_word = 0;
	down_fre_word = 0;
	
	if ( fpga_cfg.c_net_type==NET_NONE )
	{
		return;
	}
	TRACE_DEBUG("PB_SetTdMainChannelccccccccccccccccccccccfreq_code[%04x]\r\n",freq_code);
	//reg_val = CalcFreqWord( freq_code,SYS_B_FLAG,&up_fre_word,&down_fre_word);
	//reg_val = CalcFpgaFwReg(reg_val); 
	SearchFpCalcFreqWord( freq_code,SYS_C_FLAG,&up_fre_word,&down_fre_word);
	//TRACE_DEBUG("PB_SetTdMainChannel_up_fre_word=[%08x],down_fre_word=[%08x]\r\n",up_fre_word,down_fre_word);
	reg_val_16=down_fre_word&0X0FFF;
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(0);		// ����ͨ����
	if ( 1 == enable )		// ����Ƶ���ּĴ���
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
	//TRACE_DEBUG("0reg_val_16=[%08x]\r\n",reg_val_16);
 	FpgaWriteRegister(FPGA_REC_C_LTE_FREQ_CTL_L, reg_val_16);
	FPGA_DISABLE_WRITE;
	
	reg_val_16=(down_fre_word>>12)&0X3FFF;
	if(down_fre_word&0x80000000)
	{
		reg_val_16 = reg_val_16|FOUT_SPEC_INV;
	}
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(0);		// ����ͨ����
	//TRACE_DEBUG("1reg_val_16=[%08x]\r\n",reg_val_16);
 	FpgaWriteRegister(FPGA_REC_C_LTE_FREQ_CTL_H, reg_val_16);
	FPGA_DISABLE_WRITE;	
	
	WTD_CLR;
}


//#if 0
/*************************************************************
Name: FpgaSetOutAttValueA
Description: ����A�����ATT˥����
Input:
Output:void         
Return:void
**************************************************************/
void FpgaSetOutAttValueC()
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
	for ( i=0; i<sys_param_1b[MADD_C_CHANNEL_COUNT].val; i++ )
	{
		if ( 0!=sys_param_1b[MADD_C_UCH_EN1+i].val )
		{
			tmp++;
		}
	}
	if ( 0==tmp )
	{
		return;
	}

	switch ( fpga_cfg.c_net_type )
	{
#if 0
	case NET_TYPE_GSM900:
	case NET_TYPE_DCS1800:
		if ( fpga_cfg.c_ultra_info == FPGA_A_NT_GSM_WB )	// ���GSM
		{
			pda = -21+FPGA_PDN;
		}
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;

	case NET_TYPE_WCDMA2100:
		pda = CALC_DA_MAX_POW_WCDMA(tmp);
		break;

	case NET_TYPE_TD:
		pda = CALC_DA_MAX_POW(tmp);		// A��û�п��TD�汾
//	#ifdef TD_TYPE_WB
//		pda = -21+FPGA_PDN;
//	#else
//		pda = CALC_DA_MAX_POW(tmp);
//	#endif
		break;

	case NET_TYPE_CDMA:
		if ( fpga_cfg.c_ultra_info == FPGA_A_NT_CDMA_WB)	// ���CDMA
		{
			pda = -21+FPGA_PDN;
		}	
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;

	case NET_TYPE_TETRA:
		if ( fpga_cfg.c_ultra_info == FPGA_A_NT_TETRA_WB)	// �����Ⱥ
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
			|| (version_number == VERSION_40M_IN_E)|| (version_number == VERSION_50M_IN_F)
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
	
	
	g_odpx = ((INT16)sys_param_2b[MADD_C_UDPX_OUT_GAIN].val)/10.0;

	gfcmp = 0; //CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));

	psf = CALC_OUTPUT_PSF( (FLOAT32)((INT16)sys_param_2b[MADD_C_UCH_MAX_POW1+0].val/10.0), 
			sys_param_1b[MADD_C_UL_PA_GAIN].val, 
			g_odpx, gfcmp, FPGA_REC_GDNOM);

	g_dcmps = CALC_GDCMPS(pda, psf, fpga_uginp_c); //2012.6.20 

	gcmp = CALC_GS_REG( g_dcmps );
	
	//TRACE_DEBUG("Pda=%f, Psf=%f, Ginp=%f, GDCMPS=%f, gcmp=%04X,sys_param_2b[MADD_A_UCH_MAX_POW1].val=%04X, \r\n", pda, psf, fpga_uginp_c, g_dcmps, gcmp,sys_param_2b[MADD_A_UCH_MAX_POW1].val);
		
//	FlashReadOnePage(FLASH_C_UL_ATT_ADJ_TBL_PAGE, 0, p_dat);
	FlashRead(FLASH_C_UL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE);
	
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
			//TRACE_DEBUG("FpgaSetOutAttValueA tmp =%04X\r\n", tmp );

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
	FpgaWriteRegister(FPGA_REG_C_ATT3_CAL, i&0x3F);
	FpgaWriteRegister(FPGA_REG_C_ATT3_EN, 0x01);
	
	FPGA_DISABLE_WRITE;
	//TRACE_DEBUG_WP("Att=%d\r\n", i);
	WTD_CLR;
//#endif		
}

/*************************************************************
Name:FpgaWorkEnableC
Description: FPGA��Ƶ����ʹ��
Input:
	ab_flag: AB��ѡ��
	enable: 1-ʹ��
Output:void         
Return:void
**************************************************************/
void FpgaWorkEnableC( UCHAR8 enable )
{
	UINT16 tmp; 

	
	if ( fpga_cfg.c_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

	tmp = FpgaReadRegister(FPGA_REG_C_ATT_CTL);
//	tmp &= (~(ATT_MODE_MASK));

	if ( 1==enable )
	{
		tmp |= ATT_WORK_EN;			// ʹ�ܹ���
	}
	else
	{
		EnableModulatorC(0);			// �ضϵ��������
		tmp &= (~ATT_WORK_EN);		// ֹͣ����
	}
	
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_C_ATT_CTL, tmp );	
	FPGA_DISABLE_WRITE;

	if ( 1==enable )
	{
		UsNopDelay( 500000 );		// ��ʱ500ms
		EnableModulatorC(1);		// ʹ�ܵ��������
		WTD_CLR;
	}

}

/*************************************************************
Name:FpgaIsEnableA
Description: ����FPGAʹ��״̬
Input:void
Output:void         
Return:
	b_TRUE-��ʹ��
	b_FALSE-δʹ��
**************************************************************/
BOOL FpgaIsEnableC()
{
	UINT16 tmp; 
	tmp = FpgaReadRegister(FPGA_REG_C_ATT_CTL);

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
void FpgaSetFreqAdjA(void)
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
BOOL FpgaSetUlAttAdjTableC()
{
	UINT16 att_val_reg;
	UCHAR8 att_no;
	UINT16 i;
	UCHAR8 *p_dat = sys_temp_buff;
	INT32 ginp, gcic;

	//TRACE_INFO("Load Ul Att Tbl_A");
#if 1
//	FlashReadOnePage( FLASH_C_UL_ATT_ADJ_TBL_PAGE, 0, p_dat );
	FlashRead( FLASH_C_UL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE );
	
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
		att_val_reg = (UINT16)(((UINT16)p_dat[0]|( p_dat[1]<<8 ))*pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20)));
		p_dat += 2;
							
		//TRACE_INFO_WP("FpgaSetUlAttAdjTableC================= att_val_reg=%x,i=%d,(UINT16)p_dat[0]|( p_dat[1]<<8 )=[%x],pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20))=[%f]\r\n", att_val_reg,i,(UINT16)p_dat[0]|( p_dat[1]<<8 ),pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20)));
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_TBL, (ATT_SEL_C3|i) );
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_DAT, att_val_reg );
	}
	FPGA_DISABLE_WRITE;

	ginp = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_uginp_c = ginp/10000.0;
	
	gcic = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;	
	fpga_ugcic_c = gcic/10000.0;
	
	fpga_c_regbk[0] = (UINT16)((INT32)(ginp/100)&0xFFFF);
	TRACE_INFO_WP("FpgaSetUlAttAdjTableC(.........ginp.......... pga_c_regbk[0]=%X\r\n",  fpga_c_regbk[0]);
	
#endif 	
	//TRACE_INFO_WP(". ginp=%f. gcic=%f\r\n", fpga_uginp_c, fpga_ugcic_c);
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
BOOL FpgaSetDlAttAdjTableC()
{
	UINT16 att_val_reg;
	UCHAR8 att_no;
	UINT16 i;
	UCHAR8 *p_dat = sys_temp_buff;
	INT32 ginp, gcic;

	//TRACE_INFO("Load Dl Att Tbl_A");
#if 1
//	FlashReadOnePage( FLASH_C_DL_ATT_ADJ_TBL_PAGE, 0, p_dat );
	FlashRead( FLASH_C_DL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE );
	
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
		att_val_reg = (UINT16)(((UINT16)p_dat[0]|( p_dat[1]<<8 ))/pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20)));
		p_dat += 2;
		//TRACE_INFO_WP("FpgaSetDlAttAdjTableC================= att_val_reg=%x,i=%d,(UINT16)p_dat[0]|( p_dat[1]<<8 )=[%x],pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20))=[%f]\r\n", att_val_reg,i,(UINT16)p_dat[0]|( p_dat[1]<<8 ),pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20)));

		FpgaWriteRegister( FPGA_REG_ATT_ADJ_TBL, (ATT_SEL_C1|i) );
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_DAT, att_val_reg );
	}
	FPGA_DISABLE_WRITE;

	ginp = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_dginp_c = ginp/10000.0;

	gcic = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_dgcic_c = gcic/10000.0;
	
	fpga_c_regbk[1] = (UINT16)((INT32)(gcic/100)&0xFFFF);
	TRACE_INFO_WP("FpgaSetDlAttAdjTableC............gcic................... pga_c_regbk[1]=%X\r\n",  fpga_c_regbk[1]);

	//TRACE_INFO_WP(". ginp=%f. gcic=%f\r\n", fpga_dginp_c, fpga_dgcic_c);
#endif 
	WTD_CLR;
	return b_TRUE;

}

/*************************************************************
Name:	CheckChannelSetC
Description:	���Ƶ�������Ƿ�Ϸ������ж��Ƿ���Ҫ�л�����
Input: void
Output:void
Return: 0:�����д�  	1:����OK
**************************************************************/
UCHAR8 CheckChannelSetC( void )
{
#if 0//( A_NETWORK_TYPE != NET_NONE )
	UCHAR8 ch;
	UCHAR8 flag = 0;

	for ( ch=0; ch<sys_param_1b[MADD_A_CHANNEL_COUNT].val; ch++ )	// ��������ͨ��
	{
		if ( sys_param_1b[MADD_A_DCH_EN1+ch].val==1 )	// ֻ��ͨ��ʹ�ܲż��
		{
			// ���жϱ�ԵƵ��,��Ϊ���һ������֧��
		#if (A_NETWORK_TYPE == NET_TYPE_GSM900)		// GSM900
			if ( VAL_IN_RANGE(sys_param_2b[MADD_A_DL_CHANNEL1+ch].val, 96, 124) )
			{
				flag |= 0x01;	// ��ͨ
				continue;
			}

			if ( VAL_IN_RANGE(sys_param_2b[MADD_A_DL_CHANNEL1+ch].val, 0, 94) )
			{
				flag |= 0x02;	// �ƶ�
				continue;
			}
			if ( VAL_IN_RANGE(sys_param_2b[MADD_A_DL_CHANNEL1+ch].val, 975, 1023) )
			{
				flag |= 0x02;	// �ƶ�
				continue;
			}
		#elif (A_NETWORK_TYPE == NET_TYPE_DCS1800)	// DCS1800
			if ( VAL_IN_RANGE(sys_param_2b[MADD_A_DL_CHANNEL1+ch].val, 637, 736) )
			{
				flag |= 0x01;	// ��ͨ
				continue;
			}

			if ( VAL_IN_RANGE(sys_param_2b[MADD_A_DL_CHANNEL1+ch].val, 512, 636) )
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
		module_param_chg_flag|=PCHG_A_FL_CHG;
	}
	else if ( (flag==0x02)&&(G2Tpye!=G2_TYPE_CNMOBILE) )
	{
		module_param_chg_flag|=PCHG_A_FL_CHG;
	}
	
#endif

	return 1;
}
/*************************************************************
Name:RFWorkEnableC
Description: ��Ƶ����ʹ��
Input:

Output:void         
Return:void
**************************************************************/
void RFWorkEnableC( void)
{
	UINT16 tmp; 
	UINT16 reg;
	UCHAR8 npcs;
	
	WTD_CLR;
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return; 	
	}
	
	if ( fpga_cfg.c_net_type==NET_NONE )
	{
		return;
	}
	npcs = fpga_cfg.c_9363;
	//����
	tmp = ReadWriteTF(npcs,0,0x57,0);

	if(sys_param_1b[MADD_C_UL_RF_EN].val == 0)
	{
		tmp = tmp&0XFD;//д0��
	}
	else
	{
		tmp = tmp|0X02;//д1�ر�
	}


	ReadWriteTF(npcs,1,0x57,tmp);
#if 0
	//����
	tmp = ReadWriteTF(TF_C,0,0x53,0);
	if(sys_param_1b[MADD_C_DL_RF_EN].val == 0)
	{
		tmp = tmp&0XD7;//д0��
	}
	else
	{
		tmp = tmp|0X28;//д1�ر�
	}
	ReadWriteTF(TF_C,1,0x53, tmp);
#endif	
} 


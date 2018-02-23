#include "Header.h"

extern UCHAR8 sys_temp_buff[];
extern UCHAR8 gsm_type_a;	// gsmģʽ
extern FLOAT32 fpga_dginp_a;		// A����������˲�������
extern FLOAT32 fpga_dgcic_a;		// A�����������˲�������(0)
extern FLOAT32 fpga_uginp_a;		// A����������˲�������(0)
extern FLOAT32 fpga_ugcic_a;		// A�����������˲�������
extern FLOAT32 fpga_dginp_c;		// A����������˲�������
extern FLOAT32 fpga_dgcic_c;		// A�����������˲�������(0)
extern FLOAT32 fpga_uginp_c;		// A����������˲�������(0)
extern FLOAT32 fpga_ugcic_c;		// A�����������˲�������

// extern _T_FPGA_CFG fpga_cfg;
extern UINT16 fpga_a_regbk[];		// ����д��Ĵ���ginp+gcic+{��������,��������}x ch_count+busy_time+traffic_end
extern UINT32 module_param_chg_flag;		//ϵͳ���������޸ı�־
extern UINT32 fpga_load_status;


_T_MODULE_CFG mod_cfg_a;
//extern UCHAR8 ucAd9122RegVal[7][41][2][2];

 

/*************************************************************
Name:	InitPartA         
Description:��ʼ��A��
Input:void
Output:void      
Return:-1:ʧ�ܣ�1: �ɹ�            
**************************************************************/
void InitPartA(void) 
{
	// ��ʼ��4153��Ƶ��
	//TRACE_INFO("Init Part-A.\r\n");

	if ( fpga_cfg.a_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}
	ReadWriteTF(TF_A,1,0X56,0X00);//�����У����ͨ����
	CheckChannelSetA();

	Init_Local_Pll(A_MIXER); //822 U PLL  A�����б��� ,REΪ��Ƶ
	Init_Local_Pll(A_MODEN);//839 D PLL  A�����б���  REΪ����
 
	//д��У׼����ϵͳ�¶�   
	if ( b_FALSE==FpgaSetUlAttAdjTableA() )
	{
		//TRACE_ERROR("No A UL ATT Adjust Table\r\n");
	}

	if ( b_FALSE==FpgaSetDlAttAdjTableA() )
	{
		//TRACE_ERROR("No A DL ATT Adjust Table\r\n");
	}
	
	WTD_CLR;

}


/*************************************************************
Name:InitDA_A         
Description:��ʼ��AD9779
Input:main_dive_flag:1���ã�0:�ּ�
Output:void      
Return:-1:ʧ�ܣ�0: �ɹ�            
**************************************************************/
BOOL InitDA_A()
{
	
	return b_TRUE;
}


/*************************************************************
Name: FpgaGetDlUlPowerA
Description: ���������������
Input:void
Output:void         
Return:void
**************************************************************/
void FpgaGetDlUlPowerA()
{
	UINT16 power; 
	FLOAT32 tmp;
	FLOAT32 f_pow, f_gcmps;
	INT32 reg_val;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

#if ((defined CLIENT_JIZHUN) ||(defined CLIENT_ERRICSON))
	// AD����,���빦��
	//FpgaPowSelSlot(FPGA_REG_A_FAD_POW_H);
	reg_val= (FpgaReadRegister(FPGA_REG_A_FAD_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_A_FAD_POW_L));
	f_pow = CALC_POWER( reg_val );
	// ǰ�˲���Gfcmps 
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));
	// �˿����빦��Pin = Pad + Gfcmps + Gcic - Gfnom
	fpga_dgcic_a = 0;
	tmp = f_pow+fpga_dgcic_a+f_gcmps - FPGA_REC_GFNOM+(CHAR8)sys_param_1b[MADD_A_DL_POW_ADJ].val/10.0+ (INT16)sys_param_2b[MADD_A_UDPX_IN_GAIN	].val/10.0;
	if ( tmp<-123 )
	{
		tmp = -123;
	} 
//	TRACE_INFO("pow_aaaaaa=[%f]\r\n",(CHAR8)sys_param_1b[MADD_A_DL_POW_ADJ].val/10.0);

	sys_param_2b[MADD_A_DL_TOTAL_POW].val = (INT16)tmp;

	sys_param_1b[MADD_A_DL_POW_1B].val = (UCHAR8)tmp;



	// DA���� �������
	//FpgaPowSelSlot(FPGA_REG_A_BDA_POW_H);
	reg_val= (FpgaReadRegister(FPGA_REG_A_BDA_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_A_BDA_POW_L));
//	TRACE_INFO("reg_val[%04x]\n",reg_val);

	f_pow = CALC_POWER_1( reg_val );
//		TRACE_INFO("f_pow[%f]\n",f_pow);

	// ��˲���Gfcmps
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_A_BG_CMPS));
//		TRACE_INFO("f_gcmps[%f]\n",f_gcmps);
//		TRACE_INFO("fpga_uginp_a[%f]\n",fpga_uginp_a);

	// �˿��������Pout = Pda - Gfcmps - Gcic + Gfnom
	fpga_uginp_a = 0;
	tmp = f_pow-fpga_uginp_a-f_gcmps + FPGA_REC_GDNOM+ (INT16)sys_param_2b[MADD_A_UDPX_OUT_GAIN	].val/10.0;
	if ( tmp<-123 )
	{
		tmp = -123;
	}
//	TRACE_INFO("tmp[%d]\n",(INT16)tmp);
//	TRACE_INFO("(INT16)tmp[%d],reg_val[%04x],f_pow[%f],fpga_uginp_a[%f],f_gcmps[%f]\n",(INT16)tmp,reg_val,f_pow,fpga_uginp_a,f_gcmps);

	sys_param_2b[MADD_A_UL_TOTAL_POW].val = (INT16)tmp;
	sys_param_1b[MADD_A_UL_POW_1B].val = tmp;
#elif ((defined  CLIENT_ERRICSON2) ||(defined CLIENT_ERRICSON_W))

// AD����,���빦��
	//FpgaPowSelSlot(FPGA_REG_A_FAD_POW_H);
	reg_val= (FpgaReadRegister(FPGA_REG_C_FAD_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_C_FAD_POW_L));
	f_pow = CALC_POWER( reg_val );
	// ǰ�˲���Gfcmps 
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_C_FG_CMPS));
	// �˿����빦��Pin = Pad + Gfcmps + Gcic - Gfnom
	fpga_dgcic_c= 0;
	tmp = f_pow+fpga_dgcic_c+f_gcmps - FPGA_REC_GFNOM+(CHAR8)sys_param_1b[MADD_C_DL_POW_ADJ].val/10.0+ (INT16)sys_param_2b[MADD_C_UDPX_IN_GAIN	].val/10.0;
	if ( tmp<-123 )
	{
		tmp = -123;
	} 
//	TRACE_INFO("pow_aaaaaa=[%f]\r\n",(CHAR8)sys_param_1b[MADD_A_DL_POW_ADJ].val/10.0);

	sys_param_2b[MADD_C_DL_TOTAL_POW].val = (INT16)tmp;
	sys_param_1b[MADD_C_DL_POW_1B].val = (UCHAR8)tmp;



	// DA���� �������
	//FpgaPowSelSlot(FPGA_REG_A_BDA_POW_H);
	reg_val= (FpgaReadRegister(FPGA_REG_C_BDA_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_C_BDA_POW_L));
//	TRACE_INFO("reg_val[%04x]\n",reg_val);

	f_pow = CALC_POWER_1( reg_val );
//		TRACE_INFO("f_pow[%f]\n",f_pow);

	// ��˲���Gfcmps
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_C_BG_CMPS));
//		TRACE_INFO("f_gcmps[%f]\n",f_gcmps);
//		TRACE_INFO("fpga_uginp_a[%f]\n",fpga_uginp_a);

	// �˿��������Pout = Pda - Gfcmps - Gcic + Gfnom
	fpga_uginp_c = 0;
	tmp = f_pow-fpga_uginp_c-f_gcmps + FPGA_REC_GDNOM+ (INT16)sys_param_2b[MADD_C_UDPX_OUT_GAIN	].val/10.0;
	if ( tmp<-123 )
	{
		tmp = -123;
	}
//	TRACE_INFO("tmp[%d]\n",(INT16)tmp);
//	TRACE_INFO("(INT16)tmp[%d],reg_val[%04x],f_pow[%f],fpga_uginp_a[%f],f_gcmps[%f]\n",(INT16)tmp,reg_val,f_pow,fpga_uginp_a,f_gcmps);

	sys_param_2b[MADD_C_UL_TOTAL_POW].val = (INT16)tmp;
	sys_param_1b[MADD_C_UL_POW_1B].val = tmp;


#endif



}


/*************************************************************
Name:PA_SetChannel
Description:FPGA����ͨ��Ƶ��
Input:
	channel: ͨ����
	enable: ͨ��ʹ��
	freq_point: Ƶ���
Output:void         
Return:void        
**************************************************************/
void PA_SetChannel( UCHAR8 channel, UCHAR8 enable, INT32 freq_code )
{
	UINT32 reg_val=0;
	UINT16 reg_val_16=0;
	INT32 up_fre_word;
	INT32 down_fre_word;
	FLOAT32 freq_point;
	up_fre_word = 0;
	down_fre_word = 0;
	if ( fpga_cfg.a_net_type==NET_NONE )
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

	
	printf("channel = %02x  ",channel);
	CalcFreqWord( freq_code ,SYS_A_FLAG,&up_fre_word,&down_fre_word);
	reg_val=down_fre_word;
	reg_val_16 =(UINT16)reg_val&0xfff;
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(channel);		// ����ͨ����
	if ( 1 == enable )		// ����Ƶ���ּĴ���
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
 	FpgaWriteRegister(FPGA_REG_A_FREQ_CTL_L_12, reg_val_16);
	
	printf("re1_l = %02x  ",reg_val_16);
	
	reg_val_16=(UINT16)(reg_val>>12)&0x3fff;
	if(reg_val&0x80000000)
	{
		reg_val_16 |=FREQ_SIG;
	}

	if ( (fpga_cfg.a_net_type==NET_TYPE_GSM900) || (fpga_cfg.a_net_type==NET_TYPE_DCS1800 ))
	{
		if ( G2Tpye== G2_TYPE_UNICOM)
		{
			if (((FLOAT32)(freq_code-511) * 0.2 + 1805)<DCS_PLL_DL_OUT_150M_UNICOM)
			{
				reg_val_16 |=FREQ_SIG;
			}else
			{
				reg_val_16 &=~FREQ_SIG;
			}
		}else if ( G2Tpye== G2_TYPE_CNMOBILE)
		{
			if ( IS_GSM_FC(freq_code) )
			{
				if ( freq_code <= 124 )
				{
					freq_point = 10*935 + 10*GSM_SF_STEP * freq_code;
				}
				else 
				{ 
					freq_point = 10*935 + 10*GSM_SF_STEP * (freq_code-1024);
				}
			}//else if
			{
				if(NET_TYPE_GSM900==fpga_cfg.a_net_type)
				{
					if ( IS_GSM_FC(freq_code) )
					{
						if ( freq_code <= 124 )
						{
							freq_point = 10*935 + 10*GSM_SF_STEP * freq_code;
						}
						else 
						{ 
							freq_point = 10*935 + 10*GSM_SF_STEP * (freq_code-1024);
						}
					}
					if ((freq_point<GSM_PLL_DL_OUT_150M_CNMOBILE*10)||(down_fre_word<0))
					{
						reg_val_16 |=FREQ_SIG;
					}else
					{
						reg_val_16 &=~FREQ_SIG;
					}
				}
				else if (NET_TYPE_DCS1800==fpga_cfg.a_net_type)
				{
					freq_point = (FLOAT32)(freq_code-511) * 10*0.2 + 1805* 10;

					if ((freq_point<DCS_PLL_DL_OUT_150M_CNMOBILE*10)||(down_fre_word<0))
					{
						reg_val_16 |=FREQ_SIG;
					}else
					{
						reg_val_16 &=~FREQ_SIG;
					}				
				}
			}
		}
	}
	

	FpgaWriteRegister(FPGA_REG_A_FREQ_CTL_H_14, reg_val_16);
	
	printf("re1_h = %02x  ",reg_val_16);
	
	FPGA_DISABLE_WRITE;

	
	
	TRACE_INFO("0UP_PA_SetChannel---------------------reg_val= %04X\r\n",up_fre_word);
	
	reg_val=up_fre_word;
	reg_val_16 =(UINT16)reg_val&0xfff;
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(channel);		// ����ͨ����
	if ( 1 == enable )		// ����Ƶ���ּĴ���
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
 	FpgaWriteRegister(FPGA_REG_A_D_FREQ_CTL_L_12, reg_val_16);
	
	printf("re2_l = %02x  ",reg_val_16);
	
	reg_val_16=(UINT16)(reg_val>>12)&0x3fff;
	if(reg_val&0x80000000)
	{
		reg_val_16 |=FREQ_SIG;
	}


	if ( (fpga_cfg.a_net_type==NET_TYPE_GSM900) || (fpga_cfg.a_net_type==NET_TYPE_DCS1800 ))
	{
		if ( G2Tpye== G2_TYPE_UNICOM)
		{
			if (((FLOAT32)(freq_code-511) * 0.2 + 1710)<DCS_PLL_UL_OUT_150M_UNICOM)
			{
				reg_val_16 |=FREQ_SIG;
			}else
			{
				reg_val_16 &=~FREQ_SIG;
			}
		}else if ( G2Tpye== G2_TYPE_CNMOBILE)
		{
			
			if(NET_TYPE_GSM900==fpga_cfg.a_net_type)
			{
				
				if ( IS_GSM_FC(freq_code) )
				{
					if ( freq_code <= 124 )
					{
						freq_point = 10*890 + 10*GSM_SF_STEP * freq_code;
					}
					else 
					{ 
						freq_point = 10*890+ 10*GSM_SF_STEP * (freq_code-1024);
					}
				}		
				if ((freq_point<GSM_PLL_UL_OUT_150M_CNMOBILE*10)||(up_fre_word<0))
				{
					reg_val_16 |=FREQ_SIG;
				}else
				{
					reg_val_16 &=~FREQ_SIG;
				}
			}
			else if (NET_TYPE_DCS1800==fpga_cfg.a_net_type)
			{
				freq_point = (FLOAT32)(freq_code-511)* 10* 0.2 + 1710* 10;			
				if ((freq_point<DCS_PLL_UL_OUT_150M_CNMOBILE*10)||(up_fre_word<0))
				{
					reg_val_16 |=FREQ_SIG;
				}else
				{
					reg_val_16 &=~FREQ_SIG;
				}
			}

		}
	}

	
	FpgaWriteRegister(FPGA_REG_A_D_FREQ_CTL_H_14, reg_val_16);
	
	printf("re2_h = %02x\r\n",reg_val_16);
	
	FPGA_DISABLE_WRITE;	
	
	WTD_CLR;
		
}


/*************************************************************
Name: FpgaSetOutAttValueA
Description: ����A�����ATT˥����
Input:
Output:void         
Return:void
**************************************************************/
void FpgaSetOutAttValueA()
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
	for ( i=0; i<sys_param_1b[MADD_A_CHANNEL_COUNT].val; i++ )
	{
		if ( 0!=sys_param_1b[MADD_A_UCH_EN1+i].val )
		{
			tmp++;
		}
	}
	if ( 0==tmp )
	{
		return;
	}

	switch ( fpga_cfg.a_net_type )
	{
	case NET_TYPE_GSM900:
	case NET_TYPE_DCS1800:
		if ( fpga_cfg.a_ultra_info == FPGA_A_NT_GSM_WB )	// ���GSM
		{
			pda = -21+FPGA_PDN;
		}
		else
		{
			pda = -21+FPGA_PDN;
			//pda = CALC_DA_MAX_POW(tmp);
		}
		break;

	case NET_TYPE_WCDMA2100:
		pda = -21+FPGA_PDN;
		//pda = CALC_DA_MAX_POW_WCDMA(tmp);
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
		if ( fpga_cfg.a_ultra_info == FPGA_A_NT_CDMA_WB)	// ���CDMA
		{
			pda = -21+FPGA_PDN;
		}	
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;

	case NET_TYPE_TETRA:
		if ( fpga_cfg.a_ultra_info == FPGA_A_NT_TETRA_WB)	// �����Ⱥ
		{
			pda = -21+FPGA_PDN;
		}	
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;

	case NET_TYPE_LTE_FDD:
			pda = -21+FPGA_PDN;
		break;		

	case NET_TYPE_LTE_TD:
			pda = -21+FPGA_PDN;
		break;
		
	case NET_TYPE_CDMA800:
			pda = -21+FPGA_PDN;
		break;

	default:
		pda = CALC_DA_MAX_POW(tmp);
	}
	
	
	g_odpx = ((INT16)sys_param_2b[MADD_A_UDPX_OUT_GAIN].val)/10.0;

	gfcmp = 0; //CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));

	psf = CALC_OUTPUT_PSF( (FLOAT32)((INT16)sys_param_2b[MADD_A_UCH_MAX_POW1+0].val/10.0), 
			sys_param_1b[MADD_A_UL_PA_GAIN].val, 
			g_odpx, gfcmp, FPGA_REC_GDNOM);

	g_dcmps = CALC_GDCMPS(pda, psf, fpga_uginp_a); //2012.6.20 

	gcmp = CALC_GS_REG( g_dcmps );
	
	//TRACE_DEBUG("Pda=%f, Psf=%f, Ginp=%f, GDCMPS=%f, gcmp=%04X,sys_param_2b[MADD_A_UCH_MAX_POW1].val=%04X, \r\n", pda, psf, fpga_uginp_a, g_dcmps, gcmp,sys_param_2b[MADD_A_UCH_MAX_POW1].val);
		
	FlashRead(FLASH_A_UL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE);
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
	FpgaWriteRegister(FPGA_REG_A_ATT3_CAL, i&0x3F);
	FpgaWriteRegister(FPGA_REG_A_ATT3_EN, 0x01);	
	FPGA_DISABLE_WRITE;
	//TRACE_DEBUG_WP("Att=%d\r\n", i);
	WTD_CLR;
//#endif		
}

/*************************************************************
Name:FpgaWorkEnable
Description: FPGA��Ƶ����ʹ��
Input:
	ab_flag: AB��ѡ��
	enable: 1-ʹ��
Output:void         
Return:void
**************************************************************/
void FpgaWorkEnableA( UCHAR8 enable )
{
	UINT16 tmp; 

	
	if ( fpga_cfg.a_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

	tmp = FpgaReadRegister(FPGA_REG_A_ATT_CTL);
//	tmp &= (~(ATT_MODE_MASK));

	if ( 1==enable )
	{
		tmp |= ATT_WORK_EN;			// ʹ�ܹ���
	}
	else
	{
		EnableModulatorA(0);			// �ضϵ��������
		tmp &= (~ATT_WORK_EN);		// ֹͣ����
	}
	
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_A_ATT_CTL, tmp );	
	FPGA_DISABLE_WRITE;

	if ( 1==enable )
	{
		UsNopDelay( 500000 );		// ��ʱ500ms
		EnableModulatorA(1);		// ʹ�ܵ��������
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
BOOL FpgaIsEnableA()
{
	UINT16 tmp; 
	tmp = FpgaReadRegister(FPGA_REG_A_ATT_CTL);

	return ( 0==(tmp & ATT_WORK_EN) ) ? b_FALSE : b_TRUE;
}

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

/*************************************************************
Name:	FpgaSetUlAttAdjTable
Description:	��FPGAд������У׼���
Input: 
	ab_flag: AB��ѡ��
Output:void
Return:0:û�з���У׼���1:�ɹ�
**************************************************************/
BOOL FpgaSetUlAttAdjTableA()
{
	UINT16 att_val_reg;
	UCHAR8 att_no;
	UINT16 i;
	UCHAR8 *p_dat = sys_temp_buff;
	INT32 ginp, gcic;

	//TRACE_INFO("Load Ul Att Tbl_A");

//	FlashReadOnePage( FLASH_A_UL_ATT_ADJ_TBL_PAGE, 0, p_dat );
	FlashRead( FLASH_A_UL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE);
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
		//printf("FpgaSetUlAttAdjTableA %d: %d\r\n",p_dat[0],p_dat[1]);
		att_val_reg = (UINT16)(((UINT16)p_dat[0]|( p_dat[1]<<8 ))*pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET].val/10.0/20)));
		p_dat += 2;
		//TRACE_INFO_WP("FpgaSetUlAttAdjTableA================= att_val_reg=%x,i=%d,(UINT16)p_dat[0]|( p_dat[1]<<8 )=[%x],pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20))=[%f]\r\n", att_val_reg,i,(UINT16)p_dat[0]|( p_dat[1]<<8 ),pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET].val/10.0/20)));
		
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_TBL, (ATT_SEL_A3|i) );
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_DAT, att_val_reg );
	}
	FPGA_DISABLE_WRITE;

	ginp = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_uginp_a = ginp/10000.0;
	
	gcic = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;	
	fpga_ugcic_a = gcic/10000.0;
	
	fpga_a_regbk[0] = (UINT16)((INT32)(ginp/100)&0xFFFF);
	
	//TRACE_INFO_WP(". ginp=%f. gcic=%f\r\n", fpga_uginp_a, fpga_ugcic_a);
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
BOOL FpgaSetDlAttAdjTableA()
{
	UINT16 att_val_reg;
	UCHAR8 att_no;
	UINT16 i;
	UCHAR8 *p_dat = sys_temp_buff;
	INT32 ginp, gcic;

	//TRACE_INFO("Load Dl Att Tbl_A");

//	FlashReadOnePage( FLASH_A_DL_ATT_ADJ_TBL_PAGE, 0, p_dat );
	FlashRead( FLASH_A_DL_ATT_ADJ_TBL_PAGE, 0, p_dat, FLASH_PAGE_SIZE);
	att_no = p_dat[2];
	if (( p_dat[0] != 0xEC )||( p_dat[1] != 0x69 ) )		//||( att_no > DL_ATT_NUM))
	{
		//TRACE_INFO_WP(". No Tbl!\r\n");
		return b_FALSE;
	}
	p_dat+=3;
	//TRACE_INFO_WP("(%d)", att_no);

	FPGA_ENABLE_WRITE;
	for ( i=0; i<64; i++ )	{
		
		//printf("FpgaSetDlAttAdjTableA %d:%d\r\n",p_dat[0],p_dat[1]);
		att_val_reg = (UINT16)(((UINT16)p_dat[0]|( p_dat[1]<<8 ))/pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET].val/10.0/20)));
		p_dat += 2;
		//TRACE_INFO_WP("FpgaSetUlAttAdjTableA================= att_val_reg=%x,i=%d,(UINT16)p_dat[0]|( p_dat[1]<<8 )=[%x],pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20))=[%f]\r\n", att_val_reg,i,(UINT16)p_dat[0]|( p_dat[1]<<8 ),pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET].val/10.0/20)));
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_TBL, (ATT_SEL_A1|i) );
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_DAT, att_val_reg );

	}
	FPGA_DISABLE_WRITE;

	ginp = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_dginp_a = ginp/10000.0;

	gcic = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_dgcic_a = gcic/10000.0;
	
	fpga_a_regbk[1] = (UINT16)((INT32)(gcic/100)&0xFFFF);

//	TRACE_INFO_WP(". ginp=%f. gcic=%f\r\n", fpga_dginp_a, fpga_dgcic_a);

	WTD_CLR;
	return b_TRUE;

}

/*************************************************************
Name:	CheckChannelSetA
Description:	���Ƶ�������Ƿ�Ϸ������ж��Ƿ���Ҫ�л�����
Input: void
Output:void
Return: 0:�����д�  	1:����OK
**************************************************************/
UCHAR8 CheckChannelSetA( void )
{
#if ( A_NETWORK_TYPE != NET_NONE )
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
			if ( VAL_IN_RANGE(sys_param_2b[MADD_A_DL_CHANNEL1+ch].val, DCS_MIN_FRE_CODE_UNICOM, DCS_MAX_FRE_CODE_UNICOM) )
			{
				flag |= 0x01;	// ��ͨ
				continue;
			}

			if ( VAL_IN_RANGE(sys_param_2b[MADD_A_DL_CHANNEL1+ch].val, DCS_MIN_FRE_CODE_CNMOBILE,DCS_MAX_FRE_CODE_CNMOBILE) )
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
Name:RFWorkEnableA
Description: ��Ƶ����ʹ��
Input:
	ab_flag: AB��ѡ��
	enable: 1-ʹ��
Output:void         
Return:void
**************************************************************/
void RFWorkEnableA( UCHAR8 enable )
{
	UINT16 tmp; 
	UINT16 reg;
	UCHAR8 npcs;
	WTD_CLR;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}
	
	if ( fpga_cfg.a_net_type==NET_NONE )
	{
		return;
	}
	npcs = fpga_cfg.a_9363;
	//printf("sys_param_1b[MADD_A_DL_RF_EN].val=[%x],sys_param_1b[MADD_A_UL_RF_EN].val=[%x]\r\n",sys_param_1b[MADD_A_DL_RF_EN].val,sys_param_1b[MADD_A_UL_RF_EN].val);
	//����
	tmp = ReadWriteTF(npcs,0,0x57,0);
	if(sys_param_1b[MADD_A_UL_RF_EN].val == 0)
	{
		tmp = tmp&0XFD;//д0��
	}
	else
	{
		tmp = tmp|0X3f;//д1�ر�
	}
	ReadWriteTF(npcs,1,0x57,tmp);
#if 0
	//����
	tmp = ReadWriteTF(TF_A,0,0x53,0);
	if(sys_param_1b[MADD_A_DL_RF_EN].val == 0)
	{
		tmp = tmp&0XD7;//д0��
	}
	else
	{
		tmp = tmp|0X28;//д1�ر�
	}
	ReadWriteTF(TF_A,1,0x53, tmp);
#endif	
} 


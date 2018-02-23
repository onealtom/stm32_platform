/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : PartA_app.c
* Description : A段相关函数
* Version     : v0.1
* Author      : RJ
* Date        : 2010-08-17
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-08-17		v0.1			初始版本
**************************************************************/
#include "Header.h"

extern UCHAR8 sys_temp_buff[];
extern UCHAR8 gsm_type_a;	// gsm模式
extern UCHAR8 gsm_type_b;	// gsm模式
extern FLOAT32 fpga_dginp_b;		// B段下行输出滤波器增益
extern FLOAT32 fpga_dgcic_b;		// B段下行输入滤波器增益(0)
extern FLOAT32 fpga_uginp_b;		// B段上行输出滤波器增益(0)
extern FLOAT32 fpga_ugcic_b;		// B段上行输入滤波器增益
// extern _T_FPGA_CFG fpga_cfg;
extern UINT16 fpga_b_regbk[];		// 备份写入寄存器ginp+gcic+{下行增益,上行增益}x ch_count+busy_time+traffic_end
extern UINT32 module_param_chg_flag;		//系统工作参数修改标志
extern UINT32 fpga_load_status;
extern _T_MODULE_CFG mod_cfg_a;

//UINT32 adf4153bf_n_reg = ADF4153_WCDMA_FN;
//UINT32 adf4153bf_r_reg = ADF4153_WCDMA_FR;
//UINT32 adf4153bb_n_reg = ADF4153_WCDMA_BN;
//UINT32 adf4153bb_r_reg = ADF4153_WCDMA_BR;
//FLOAT32 b_fdl;
//FLOAT32 b_ful;

_T_MODULE_CFG mod_cfg_b;
//extern UCHAR8 ucAd9122RegVal[7][41][2][2];


/*************************************************************
Name:	InitPart         
Description:初始化A段
Input:void
Output:void      
Return:-1:失败，1: 成功            
**************************************************************/
void InitPartB(void)
{
	UCHAR8 net_type;
	
	if ( fpga_cfg.b_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}
	//TRACE_INFO("Init Part-B.\r\n");
	ReadWriteTF(TF_B,1,0X56,0X00);//打开上行，输出通道、
	if ( fpga_cfg.b_net_type==NET_DIVE )
	{
		// B段为分集，按A段参数来配置
		net_type = fpga_cfg.a_net_type;
	}
	else
	{
		net_type = fpga_cfg.b_net_type;
	}

	CheckChannelSetB();
	
	Init_Local_Pll(B_MIXER); //822 U PLL  A段上行本震 ,RE为混频
	Init_Local_Pll(B_MODEN);//839 D PLL  A段下行本震  RE为调制	


	//写入校准表格和系统温度
	if ( b_FALSE==FpgaSetUlAttAdjTableB() )
	{
		//TRACE_ERROR("No B UL ATT Adjust Table\r\n");
	}

	if ( b_FALSE==FpgaSetDlAttAdjTableB() )
	{
		//TRACE_ERROR("No B DL ATT Adjust Table\r\n");
	}
	WTD_CLR;

}




/*************************************************************
Name: FpgaGetDlUlPowerB
Description: 读取AD、DA功率，推出端口功率
Input:void
Output:void         
Return:void
**************************************************************/
void FpgaGetDlUlPowerB()
{
	UINT16 power;
	FLOAT32 tmp;  
	FLOAT32 f_pow, f_gcmps;
	INT32 reg_val;
	
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

// B段
	FpgaPowSelSlot(FPGA_REG_B_FAD_POW_H);
	// AD功率
	reg_val= (FpgaReadRegister(FPGA_REG_B_FAD_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_B_FAD_POW_L));
	f_pow = CALC_POWER( reg_val );
	// 前端补偿Gfcmps
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_B_FG_CMPS));
	// 端口输入功率Pin = Pad + Gfcmps + Gcic - Gfnom
	if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
	|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
	|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
	|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
	|| (version_number == VERSION_50M_IN_V5)
	)
		tmp = f_pow+fpga_dgcic_b+f_gcmps - FPGA_REC_GFNOM+(CHAR8)sys_param_1b[MADD_B_DL_POW_ADJ].val/10.0;
	else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
		tmp = f_pow+fpga_dgcic_b+f_gcmps - FPGA_REC_GFNOM+ (INT16)sys_param_2b[MADD_B_UDPX_IN_GAIN	].val/10.0+(CHAR8)sys_param_1b[MADD_B_DL_POW_ADJ].val/10.0;
	if ( tmp<-123 )
	{
		tmp = -123;
	}
//	TRACE_INFO("pow_b=[%f]\n",tmp);

	sys_param_2b[MADD_B_DL_TOTAL_POW].val = (INT16)tmp;

	sys_param_1b[MADD_B_DL_POW_1B].val = (UCHAR8)tmp;
	//TRACE_INFO("B---sys_param_2b[MADD_B_DL_TOTAL_POW].val[%04x]\r\n",sys_param_2b[MADD_B_DL_TOTAL_POW].val);

	FpgaPowSelSlot(FPGA_REG_B_BDA_POW_H);
	// DA功率
	reg_val= (FpgaReadRegister(FPGA_REG_B_BDA_POW_H)<<16)|(FpgaReadRegister(FPGA_REG_B_BDA_POW_L));
	f_pow = CALC_POWER_1( reg_val );
	// 前端补偿Gfcmps
	f_gcmps = CALC_GAIN(FpgaReadRegister(FPGA_REG_B_BG_CMPS));
	// 端口输出功率Pout = Pda - Gfcmps - Gcic + Gfnom
	tmp = f_pow-fpga_dginp_b-f_gcmps + FPGA_REC_GDNOM;
	if ( tmp<-123 )
	{
		tmp = -123;
	}

	sys_param_2b[MADD_B_UL_TOTAL_POW].val = (INT16)tmp;

	sys_param_1b[MADD_B_UL_POW_1B].val = (UCHAR8)tmp;

}


/*************************************************************
Name:FpgaSetGsmChannel
Description:FPGA设置通道频点
Input:
	channel: 通道号
	enable: 通道使能
	freq_point: 频点号
Output:void         
Return:void        
**************************************************************/
void PB_SetChannel( UCHAR8 channel, UCHAR8 enable, INT32 freq_code )
{
	UINT32 reg_val;
	UINT16 reg_val_16;
	INT32 up_fre_word=0;
	INT32 down_fre_word=0;


	if ( fpga_cfg.b_net_type==NET_NONE )
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
//	TRACE_INFO("PB_SetChannel[%x]-freq_code= %d\r\n",channel,freq_code);

	//if(NET_TYPE_TD==fpga_cfg.b_net_type)
	//{
		CalcFreqWord( freq_code,SYS_B_FLAG ,&up_fre_word, &down_fre_word);
	//}else
	//{
	//	CalcFreqWord( freq_code,SYS_B_FLAG ,&up_fre_word, &down_fre_word);
	//}

//	TRACE_INFO("reg_val=[%08x]\r\n",reg_val);	


	FPGA_ENABLE_WRITE;

	reg_val=down_fre_word;
	reg_val_16 =(UINT16)reg_val&0xfff;	
	FPGA_SET_CHANNEL(channel);		// 设置通道号
	if ( 1 == enable )		// 设置频率字寄存器
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
	 FpgaWriteRegister(FPGA_REG_B_FREQ_CTL_L_12, reg_val_16);
	reg_val_16=(UINT16)(reg_val>>12)&0x3fff;
	if(reg_val&0x80000000)
	{
		reg_val_16 |=FREQ_SIG;
	}
	FpgaWriteRegister(FPGA_REG_B_FREQ_CTL_H_14, reg_val_16);
	
	FPGA_DISABLE_WRITE;


	FPGA_ENABLE_WRITE;
	
	//上行
	reg_val=up_fre_word;
	reg_val_16 =(UINT16)reg_val&0xfff;		

	FPGA_SET_CHANNEL(channel);		// 设置通道号
	if ( 1 == enable )		// 设置频率字寄存器
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
	FpgaWriteRegister(FPGA_REG_B_D_FREQ_CTL_L_12, reg_val_16);
	
	reg_val_16=(UINT16)(reg_val>>12)&0x3fff;
	if(reg_val&0x80000000)
	{
		reg_val_16 |=FREQ_SIG;
	}
	FpgaWriteRegister(FPGA_REG_B_D_FREQ_CTL_H_14, reg_val_16);

	FPGA_DISABLE_WRITE;
	WTD_CLR;
}

/*************************************************************
Name:FpgaSetGsmChannel
Description:FPGA设置通道频点
Input:
	channel: 通道号
	enable: 通道使能
	freq_point: 频点号
Output:void         
Return:void        
**************************************************************/
void PB_SetTdMainChannel( UCHAR8 enable, INT32 freq_code )
{
	UINT16 reg_val_16;
	INT32 up_fre_word, down_fre_word;

	up_fre_word = 0;
	down_fre_word = 0;
	
	if ( fpga_cfg.b_net_type==NET_NONE )
	{
		return;
	}
//	TRACE_DEBUG("PB_SetTdMainChannelbbbbbbbbbbbbbbbbbfreq_code[%04x]\r\n",freq_code);
	//reg_val = CalcFreqWord( freq_code,SYS_B_FLAG,&up_fre_word,&down_fre_word);
	//reg_val = CalcFpgaFwReg(reg_val); 
	SearchFpCalcFreqWord( freq_code,SYS_B_FLAG,&up_fre_word,&down_fre_word);
	TRACE_DEBUG("PB_SetTdMainChannel_up_fre_word=[%08x],down_fre_word=[%08x]\r\n",up_fre_word,down_fre_word);
	reg_val_16=down_fre_word&0X0FFF;
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(0);		// 设置通道号
	if ( 1 == enable )		// 设置频率字寄存器
	{
		reg_val_16 |= SF_CHANNEL_EN;
	}
//	TRACE_DEBUG("0reg_val_16=[%08x]\r\n",reg_val_16);
 	FpgaWriteRegister(FPGA_REG_TD_MAIN_CH_L12, reg_val_16);
	FPGA_DISABLE_WRITE;
	
	reg_val_16=(down_fre_word>>12)&0X3FFF;
	if(down_fre_word&0x80000000)
	{
		reg_val_16 = reg_val_16|FOUT_SPEC_INV;
	}
	FPGA_ENABLE_WRITE;
	FPGA_SET_CHANNEL(0);		// 设置通道号
//	TRACE_DEBUG("1reg_val_16=[%08x]\r\n",reg_val_16);
 	FpgaWriteRegister(FPGA_REG_TD_MAIN_CH_H14, reg_val_16);
	FPGA_DISABLE_WRITE;	
	
	WTD_CLR;
}


/*************************************************************
Name: FpgaSetOutAttValueB
Description: 设置B段输出ATT衰减量
Input:
Output:void         
Return:void
**************************************************************/
void FpgaSetOutAttValueB()
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
	for ( i=0; i<sys_param_1b[MADD_B_CHANNEL_COUNT].val; i++ )
	{
		if ( 0!=sys_param_1b[MADD_B_UCH_EN1+i].val )
		{
			tmp++;
		}
	}
	if ( 0==tmp )
	{
		return;
	}
	
	//pda = CALC_DA_MAX_POW(tmp);

	if ( fpga_cfg.b_net_type==NET_DIVE )
	{
		// B段为分集，按A段参数来配置
		i = fpga_cfg.a_net_type;
	}
	else
	{
		i = fpga_cfg.b_net_type;
	}

	switch ( i )
	{
	case NET_TYPE_GSM900:
	case NET_TYPE_DCS1800:
		pda = -21+FPGA_PDN;
		break;

	case NET_TYPE_WCDMA2100:
		pda = -21+FPGA_PDN;
		break;

	case NET_TYPE_TD:
		if ( fpga_cfg.b_ultra_info == FPGA_B_NT_TD_WB )	// 宽带TD
		{
			if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
			|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
			|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
			|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
			|| (version_number == VERSION_50M_IN_V5)
			)
				pda = -21+FPGA_PDN+3;
			else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
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
		if (( fpga_cfg.b_ultra_info == FPGA_B_NT_CDMA_WB)	// 宽带CDMA
			||( fpga_cfg.b_ultra_info == FPGA_B_NT_CDMA_D_WB))	// 宽带分集CDMA
		{
			pda = -21+FPGA_PDN;
		}	
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;

	case NET_TYPE_TETRA:
		if ( fpga_cfg.b_ultra_info == FPGA_B_NT_TETRA_D_WB )	// 分集宽带集群
		{
			pda = -21+FPGA_PDN;
		}	
		else
		{
			pda = CALC_DA_MAX_POW(tmp);
		}
		break;
	case NET_TYPE_LTE_TD:
			pda = -21+FPGA_PDN;
		break;
		
	case NET_TYPE_LTE_FDD:
			pda = -21+FPGA_PDN;
		break;	

	default:
		pda = CALC_DA_MAX_POW(tmp);
	}
	
	
	g_odpx = ((INT16)sys_param_2b[MADD_B_UDPX_OUT_GAIN].val)/10.0;

	gfcmp = 0; //CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));

	psf = CALC_OUTPUT_PSF( (FLOAT32)((INT16)sys_param_2b[MADD_B_UCH_MAX_POW1+0].val/10.0), 
			sys_param_1b[MADD_B_UL_PA_GAIN].val, 
			g_odpx, gfcmp, FPGA_REC_GDNOM);

	g_dcmps = CALC_GDCMPS(pda, psf, fpga_uginp_b);//2012.6.20

	gcmp = CALC_GS_REG( g_dcmps );
	
	//TRACE_DEBUG("Pda=%f, Psf=%f, Ginp=%f, GDCMPS=%f, gcmp=%04X, ", pda, psf, fpga_uginp_b, g_dcmps, gcmp);
		
//	FlashReadOnePage(FLASH_B_UL_ATT_ADJ_TBL_PAGE, 0, p_dat);
	FlashRead(FLASH_B_UL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE);
	
	if ( ( p_dat[0] != 0xEC )||( p_dat[1] != 0x69 ) )
	{
		// 无衰减表格
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
	FpgaWriteRegister(FPGA_REG_B_ATT3_CAL, i&0x3F);
	FpgaWriteRegister(FPGA_REG_B_ATT3_EN, 0x01);	
	FPGA_DISABLE_WRITE;
	//TRACE_DEBUG_WP("Att=%d\r\n", i);
	WTD_CLR;
		
}

/*************************************************************
Name:FpgaWorkEnable
Description: FPGA射频部分使能
Input:
	ab_flag: AB段选择
	enable: 1-使能
Output:void         
Return:void
**************************************************************/
void FpgaWorkEnableB( UCHAR8 enable )
{
	UINT16 tmp; 
	
	if ( fpga_cfg.b_net_type==NET_NONE )
	{
		return;
	}
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

	tmp = FpgaReadRegister(FPGA_REG_B_ATT_CTL);
//	tmp &= (~(ATT_MODE_MASK));
	
	if ( 1==enable )
	{
		tmp |= ATT_WORK_EN;			// 使能工作
	}
	else
	{
		EnableModulatorB(0);				// 关断调制器输出
		tmp &= (~ATT_WORK_EN);		// 停止工作
	}

	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_B_ATT_CTL, tmp );	
	FPGA_DISABLE_WRITE;
	
	if ( 1==enable )
	{
		UsNopDelay( 500000 );			// 延时500ms
		EnableModulatorB(1);			// 使能调制器输出
		WTD_CLR;
	}
}

/*************************************************************
Name:FpgaIsEnableB
Description: 返回FPGA使能状态
Input:void
Output:void         
Return:
	b_TRUE-已使能
	b_FALSE-未使能
**************************************************************/
BOOL FpgaIsEnableB()
{
	UINT16 tmp; 
	tmp = FpgaReadRegister(FPGA_REG_B_ATT_CTL);

	return ( 0==(tmp & ATT_WORK_EN) ) ? b_FALSE : b_TRUE;
}

/*************************************************************
Name: SetFpgaFreqAdj         
Description: 设置FPGA AD输入,DA输出频率补偿
Input:void
Output:void      
Return:-1:失败，1: 成功            
**************************************************************/
void FpgaSetFreqAdjB(void)
{

	
} 


/*************************************************************
Name:	FpgaSetUlAttAdjTable
Description:	向FPGA写入上行校准表格
Input: 
	ab_flag: AB段选择
Output:void
Return:0:没有发现校准表格，1:成功
**************************************************************/
BOOL FpgaSetUlAttAdjTableB()
{
	UINT16 att_val_reg;
	UCHAR8 att_no;
	UINT16 i;
	UCHAR8 *p_dat = sys_temp_buff;
	INT32 ginp, gcic;

	//TRACE_INFO("Load Ul Att Tbl_B");

//	FlashReadOnePage( FLASH_B_UL_ATT_ADJ_TBL_PAGE, 0, p_dat );
	FlashRead( FLASH_B_UL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE );
	
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
		att_val_reg = (UINT16)(((UINT16)p_dat[0]|( p_dat[1]<<8 ))*pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_B].val/10.0/20)));
		p_dat += 2;								
		//TRACE_INFO_WP("FpgaSetUlAttAdjTableB================= att_val_reg=%x,i=%d,(UINT16)p_dat[0]|( p_dat[1]<<8 )=[%x],pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_B].val/10.0/20))=[%f]\r\n", att_val_reg,i,(UINT16)p_dat[0]|( p_dat[1]<<8 ),pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_B].val/10.0/20)));
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_TBL, (ATT_SEL_B3|i) );
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_DAT, att_val_reg );
	}
	FPGA_DISABLE_WRITE;

	ginp = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_uginp_b = ginp/10000.0;
	
	gcic = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_ugcic_b = gcic/10000.0;
	
	fpga_b_regbk[0] = (UINT16)((INT32)(ginp/100)&0xFFFF);
	//TRACE_INFO_WP(". ginp=%f. gcic=%f\r\n", fpga_uginp_b, fpga_ugcic_b);
	
	WTD_CLR;
	return b_TRUE;

}

/*************************************************************
Name:	FpgaSetDlAttAdjTable
Description:	向FPGA写入上行校准表格
Input: 
	ab_flag: AB段选择
Output:void
Return:0:没有发现校准表格，1:成功
**************************************************************/
BOOL FpgaSetDlAttAdjTableB()
{
	UINT16 att_val_reg;
	UCHAR8 att_no;
	UINT16 i;
	UCHAR8 *p_dat = sys_temp_buff;
	INT32 ginp, gcic;

	if ( fpga_cfg.b_net_type==NET_DIVE )
	{
		// B段为分集，无下行输入
		return;
	}

	//TRACE_INFO("Load Dl Att Tbl_B");

//	FlashReadOnePage( FLASH_B_DL_ATT_ADJ_TBL_PAGE, 0, p_dat );
	FlashRead( FLASH_B_DL_ATT_ADJ_TBL_PAGE, 0, p_dat,FLASH_PAGE_SIZE );
	
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
		att_val_reg = (UINT16)(((UINT16)p_dat[0]|( p_dat[1]<<8 ))/pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_B].val/10.0/20)));
		p_dat += 2;
		//TRACE_INFO_WP("FpgaSetDlAttAdjTableB================= att_val_reg=%x,i=%d,(UINT16)p_dat[0]|( p_dat[1]<<8 )=[%x],pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_C].val/10.0/20))=[%f]\r\n", att_val_reg,i,(UINT16)p_dat[0]|( p_dat[1]<<8 ),pow(10,((CHAR8)sys_param_1b[MADD_METER_OFFSET_B].val/10.0/20)));
		
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_TBL, (ATT_SEL_B1|i) );
		FpgaWriteRegister( FPGA_REG_ATT_ADJ_DAT, att_val_reg );
	}
	FPGA_DISABLE_WRITE;

	ginp = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_dginp_b = ginp/10000.0;

	gcic = (UINT32)( p_dat[0]|( p_dat[1]<<8 )|( p_dat[2]<<16 )|( p_dat[3]<<24 ) );
	p_dat += 4;
	fpga_dgcic_b = gcic/10000.0;
	
	fpga_b_regbk[1] = (UINT16)((INT32)(gcic/100)&0xFFFF);

	//TRACE_INFO_WP(". ginp=%f. gcic=%f\r\n", fpga_dginp_b, fpga_dgcic_b);

	WTD_CLR;
	return b_TRUE;

}

/*************************************************************
Name:	CheckChannelSetB
Description:	检测频点设置是否合法，并判断是否需要切换本振
Input: void
Output:void
Return: 0:参数有错  	1:参数OK
**************************************************************/
UCHAR8 CheckChannelSetB( void )
{
#if ( B_NETWORK_TYPE == NET_DIVE )
#define PART_B_TYPE A_NETWORK_TYPE
#else
#define PART_B_TYPE B_NETWORK_TYPE
#endif

#if ( PART_B_TYPE != NET_NONE )
	UCHAR8 ch;
	UCHAR8 flag = 0;

	for ( ch=0; ch<sys_param_1b[MADD_B_CHANNEL_COUNT].val; ch++ )	// 遍历所有通道
	{
		if ( sys_param_1b[MADD_B_DCH_EN1+ch].val==1 )	// 只有通道使能才检测
		{
			// 不判断边缘频点,因为随便一个本振都支持
		#if (PART_B_TYPE == NET_TYPE_GSM900)	// GSM900
			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, 96, 124) )
			{
				flag |= 0x01;	// 联通
				continue;
			}

			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, 0, 94) )
			{
				flag |= 0x02;	// 移动
				continue;
			}
			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, 975, 1023) )
			{
				flag |= 0x02;	// 移动
				continue;
			}
		#elif (PART_B_TYPE == NET_TYPE_DCS1800)	// DCS1800
			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, DCS_MIN_FRE_CODE_UNICOM, DCS_MAX_FRE_CODE_UNICOM) )
			{
				flag |= 0x01;	// 联通
				continue;
			}

			if ( VAL_IN_RANGE(sys_param_2b[MADD_B_DL_CHANNEL1+ch].val, DCS_MIN_FRE_CODE_CNMOBILE,DCS_MAX_FRE_CODE_CNMOBILE) )
			{
				flag |= 0x02;	// 移动
				continue;
			}
		#endif
		}
	}

	if ( 0x03 == flag )		// 同时设置了移动和联通频点，出错
	{
		return 0;
	}
	
#ifdef GSM_TYPE_UNICOM
		G2Tpye = G2_TYPE_UNICOM;
#elif defined(GSM_TYPE_CNMOBILE)
		G2Tpye = G2_TYPE_CNMOBILE;
#endif

	// 切换到联通本振
	if ( (flag==0x01)&&(G2Tpye!=G2_TYPE_UNICOM) )
	{
		module_param_chg_flag|=PCHG_B_FL_CHG;
	}
	else if ( (flag==0x02)&&(G2Tpye!=G2_TYPE_CNMOBILE) )
	{
		module_param_chg_flag|=PCHG_B_FL_CHG;
	}


#endif

#undef PART_B_TYPE

	return 1;
}
/*************************************************************
Name:RFWorkEnableB
Description: 射频部分使能
Input:
	ab_flag: AB段选择
	enable: 1-使能
Output:void         
Return:void
**************************************************************/
void RFWorkEnableB( void )
{
	UINT16 tmp; 
	UINT16 reg;
	UCHAR8 npcs;
	WTD_CLR;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}
	
	if ( fpga_cfg.b_net_type==NET_NONE )
	{
		return;
	}

	npcs = fpga_cfg.b_9363;
	//上行
	tmp = ReadWriteTF(npcs,0,0x57,0);
	if(sys_param_1b[MADD_B_UL_RF_EN].val == 0)
	{
		tmp = tmp&0XFE;//写0打开
	}
	else
	{
		tmp = tmp|0X3f;//写1关闭
	}
	ReadWriteTF(npcs,1,0x57,tmp);
#if 0
	//下行
	tmp = ReadWriteTF(TF_B,0,0x53,0);
	if(sys_param_1b[MADD_B_DL_RF_EN].val == 0)
	{
		tmp = tmp&0XD7;//写0打开
	}
	else
	{
		tmp = tmp|0X28;//写1关闭
	}
	ReadWriteTF(TF_B,1,0x53, tmp);
#endif	
} 





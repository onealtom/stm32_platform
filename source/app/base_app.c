#include "Header.h"


UCHAR8 clk_flag = CLK_FLAG_122_88M;	//时钟标示： 0-122.88，1-125
UCHAR8 version_number = VERSION_40M_NOIN;	//版本提示： 0-20M分体，1-20M一体， 2-40M分体， 3-40M一体；



UCHAR8 aPllRegTbl[]={
	HMC830_REFDIV_02,
	HMC830_SD_CFG_06,
	HMC830_CHARGE_PUMP_09,
    HMC830_VCO_AUTO_0A,
	HMC830_PD_0B,	
	HMC830_VCO_SPI_05, 
	HMC830_VCO_SPI_05,
	HMC830_VCO_SPI_05,
	HMC830_VCO_SPI_05,
	HMC830_FRE_INT_03,
	HMC830_FRE_FRA_04, 
}; 

/*************************************************************
Name:LoadGsmPllRegTbl           
Description:初始化PLL
Input:
	fb_flag: 前后端标志
	ab_flag: AB段标志
Output:void       
Return:
	b_FALSE: 失败
	b_TRUE:  成功             
**************************************************************/
 void LoadGsmPllRegTbl(u8 G2Tpye)
 {
    if ( G2_TYPE_CNMOBILE == G2Tpye)
    {
     //  MenCpy(auiPllRegVlaue[0], GsmCnmobilePll, 44*4);
    } 
    else  
    {
      // MenCpy(auiPllRegVlaue[0], GsmUnicomPll, 44*4);
    } 
 } 
 
/*************************************************************
Name:Init_Local_Pll           
Description:初始化PLL
Input:
	fb_flag: 前后端标志
	ab_flag: AB段标志
Output:void       
Return:
	b_FALSE: 失败
	b_TRUE:  成功             
**************************************************************/
 void LoadDcsPllRegTbl(u8 G2Tpye)
 {
   #if 1
    if ( G2_TYPE_CNMOBILE == G2Tpye)
    {
    //  MenCpy((u8*)auiPllRegVlaue[4], (u8*)DcsCnmobilePll, 44*4);

    }
    else 
    {
     // MenCpy((u8*)auiPllRegVlaue[4], (u8*)DcsUnicomPll, 44*4);
    }
   #endif
 }


/*************************************************************
Name:Init_Local_Pll           
Description:初始化PLL
Input:
	fb_flag: 前后端标志
	ab_flag: AB段标志
Output:void       
Return:
	b_FALSE: 失败
	b_TRUE:  成功             
**************************************************************/
BOOL Init_Local_Pll(UCHAR8 ucPll)//822 U PLL
{
	return b_TRUE; 
}

void SetClkFlag( UCHAR8 val )
{
	clk_flag = val;
}

// 根据ns置计算延时时间寄存器值，ns：纳秒值
UINT32 _CalcDelayReg( UINT32 ns )
{
	if(0==clk_flag)
	{	// 122.88M时钟
		return (ns*122.88+500)/1000;
	}
	else
	{	// 125M时钟
		return (ns*125+500)/1000;
	}
}



// 根据寄存器计算话务量占用时间us
UINT32 _CalcBusyTime( UINT32 reg_val, UINT32 ch_count )
{
	if(0==clk_flag)
	{	// 122.88M时钟 
		return (UINT32)( (reg_val)*((FLOAT32)((ch_count+1)*4*64/122.88))+0.5 );
	}
	else
	{	// 125M时钟
		return (UINT32)( (reg_val)*((FLOAT32)((ch_count+1)*4*64/125))+0.5 );
	}
}

// 计算频率字，df：数字频率(KHz)
INT32 _CalcFpgaFw( INT32 df )
{
	INT32 sign = 1;	// 符号
	
	df *= 10;	// 变换成10Hz单位
	if ( df<0 )
	{
		sign = -1;	// 四舍五入
	}

	if(0==clk_flag)
	{	// 122.88M时钟
		df = (df + ( sign*100 ))/200;	// 20K
	}
	else
	{	// 125M时钟
		df = (df+(sign*62))/125;	// 12.5K
	}

	return df; 

}

// 频率字数值调整
UINT32 _AdjustFpgaFw(INT32 df)
{
	if ( df<0 ) 
	{
		if(0==clk_flag)
		{	// 122.88M时钟
			df+= 3072;
		}
		else
		{	// 125M时钟
			df+= 5000;
		}
	}
	return (UINT32)df;
}



////////////////////////////// TD函数 ////////////////////////////////
// TD时间计算
UINT16 _CalcTdTimeParam( UINT32 tm )
{
	CHAR8 flag=0;
	if(0!=(tm&0x8000))
	{
		//flag=1;
		TRACE_INFO("tm=[%X]\r\n",tm);
		tm=0xffff-(0x0ffff&tm);
		TRACE_INFO("tm=[%X]\r\n",tm);
		if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A)
		|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
		|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
		
		 )
			return (0xffff-(UINT16)(tm*78.125/1000));// 	
		else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
			return (0xffff-(UINT16)(tm*75.0/1000));// 
		else if(version_number == VERSION_50M_IN_F ||version_number == VERSION_50M_IN_V4)
			return (0xffff-(UINT16)(tm*62.5/1000));// 
		else if(version_number == VERSION_50M_IN_V5)
		{
			return (0xffff-(UINT16)(tm*62.5/1000));// 
		}
			
	}else
	{
		if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A)
		|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
		|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
		)
			return (UINT16)(tm*78.125/1000);// 	
		else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
			return (UINT16)(tm*75.0/1000);// 
		else if(version_number == VERSION_50M_IN_F ||version_number == VERSION_50M_IN_V4)
			return (UINT16)(tm*62.5/1000);// 
	}

	
}

/*************************************************************
Name:         CalcGsmdfu
Description:  计算GSM输入逻辑的频率
Input:        freq_point -  输入的RF频率
              fu_local   -  本振的输出频率
Output:       void         
Return:	 GSM输入逻辑的频率
**************************************************************/
FLOAT32 CalcGsmdfu( FLOAT32 freq_point, FLOAT32 fd_local )
{
//    FLOAT32 fClkFreq;
    
//    fClkFreq = clk_flag ? AD_FS_125M : AD_FS_122M;
//    return ( freq_point-fu_local+(2.0*fClkFreq)-(5.0*fClkFreq/8.0));
	if(freq_point>fd_local)
	{
		return ( freq_point-fd_local); 
	}
	else  
	{
		return ( fd_local-freq_point); 
	}

} 


/*************************************************************
Name:         CalcGsmdfu
Description:  计算GSM输入逻辑的频率
Input:        freq_point -  输入的RF频率
              fu_local   -  本振的输出频率
Output:       void         
Return:	 GSM输入逻辑的频率
**************************************************************/
FLOAT32 CalcDcsfu( FLOAT32 freq_point, FLOAT32 fd_local )
{
	if(freq_point>fd_local)
	{
		return ( freq_point-fd_local); 
	}
	else  
	{
		return ( fd_local-freq_point); 
	}
 	  

} 

/*************************************************************
Name:         CalcGsmdfu
Description:  计算GSM输入逻辑的频率
Input:        freq_point -  输入的RF频率
              fu_local   -  本振的输出频率
Output:       void         
Return:	 GSM输入逻辑的频率
**************************************************************/
FLOAT32 CalcWcdmafu( FLOAT32 freq_point, FLOAT32 fd_local )
{
	if(freq_point>fd_local)
	{
		// TRACE_INFO("CalcWcdmafu--freq_point>fd_local\r\n"); 
		return ( freq_point-fd_local); 
	}
	else
	{
		//TRACE_INFO("CalcWcdmafu--freq_point<fd_local\r\n"); 
		return ( fd_local-freq_point); 
	}
 	  
} 

/*************************************************************
Name:         CalcTdLtefu
Description:  计算GSM输入逻辑的频率
Input:        freq_point -  输入的RF频率
              fu_local   -  本振的输出频率
Output:       void         
Return:	 GSM输入逻辑的频率
**************************************************************/
FLOAT32 CalcTdLtefu( FLOAT32 freq_point, FLOAT32 fd_local )
{
    FLOAT32 fClkFreq; 
 	if(freq_point>fd_local)
	{
		 TRACE_INFO("CalcWcdmafu--freq_point>fd_local\r\n"); 
		return ( freq_point-fd_local); 
	}
	else
	{
		TRACE_INFO("CalcWcdmafu--freq_point<fd_local\r\n"); 
		return ( fd_local-freq_point); 
	}
} 

/*************************************************************
Name:         CalcFpgaFw
Description:  计算GSM输入逻辑的数字频率字
Input:        fDf -  输入的逻辑频率
Output:       void         
Return:	 逻辑的数字频率字
**************************************************************/
INT32 CalcFpgaFw_AB( FLOAT32 fDf )	
{  

#if defined CLIENT_JIZHUN
	return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/12.288);

#elif defined CLIENT_DATANG
	return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/61.44);

#else
	 //if(version_number == VERSION_50M_IN_V4)
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/61.44);//
#endif
	
}

/*************************************************************
Name:         CalcFpgaFw_A
Description:  计算GSM输入逻辑的数字频率字
Input:        fDf -  输入的逻辑频率
Output:       void         
Return:	 逻辑的数字频率字
**************************************************************/
INT32 CalcFpgaFw_A( FLOAT32 fDf )	
{  
	return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/61.44);
}

/*************************************************************
Name:         CalcFpgaFw
Description:  计算GSM输入逻辑的数字频率字
Input:        fDf -  输入的逻辑频率
Output:       void         
Return:	 逻辑的数字频率字
**************************************************************/
INT32 CalcFpgaFw_B( FLOAT32 fDf )	
{  
	if((version_number == VERSION_40M_NOIN) 	|| (version_number == VERSION_40M_IN_B)
		|| (version_number == VERSION_40M_IN_D)
	)
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*(7/156.25/4));
	else if((version_number == VERSION_40M_IN_E) || (version_number == VERSION_40M_IN_C))// 2015-2-6 v3c由75改为62.5
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*62.5);
	else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/75);
	else if(version_number == VERSION_40M_IN_A)
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/78.125);
	else if(version_number == VERSION_50M_IN_F )
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/62.5);
	else if(version_number == VERSION_50M_IN_V4)
		return (INT32)((FLOAT32)pow(2,13)*1024*8*fDf*1/50.0);

	else if(version_number == VERSION_50M_IN_V5)
		return (INT32)((FLOAT32)pow(2,13)*1024*8*fDf*1/50.0);

}

/*************************************************************
Name:         CalcFpgaFw
Description:  计算GSM输入逻辑的数字频率字
Input:        fDf -  输入的逻辑频率
Output:       void         
Return:	 逻辑的数字频率字
**************************************************************/
INT32 CalcFpgaFw_CD( FLOAT32 fDf )	
{
	if(version_number == VERSION_40M_IN_C)
	{
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/62.5);// 2015-2-6 v3c由50改为62.5
	}
	else if( version_number==VERSION_40M_IN_D)
	{
		return (INT32)((FLOAT32)pow(2,13)*1024*8*fDf*1/(156.25/7*2)  );
	}
	else if( version_number==VERSION_40M_IN_E)
	{
		return (INT32)((FLOAT32)pow(2,13)*1024*8*fDf*1/62.5 );
	}
	else if( (version_number==VERSION_20M_NOIN) || (version_number==VERSION_20M_IN) )
	{
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/25);
	}
	else if(version_number == VERSION_50M_IN_F ||version_number == VERSION_50M_IN_V4)
	{
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/62.5);// 2015-2-6 v3c由50改为62.5
	}
	else if(version_number == VERSION_50M_IN_V5)
	{
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/37.5);
	}
	else
	{
		if(0x02==sys_param_1b[MADD_C_CHANNEL_COUNT].val)
		{
			//return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/50);
			return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/(156.25/7*3));//201405221849
		}else 
		{
			return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/25);
		}
	}	

	
}
INT32 CalcTypeFddFpgaFw_CD( FLOAT32 fDf )
{

	return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/37.5);
}


/*************************************************************
Name:         AdjustFpgaFw
Description:  调整GSM输入逻辑的数字频率字
Input:        fDf -  GSM输入逻辑的数字频率字
Output:       void         
Return:	调制后的GSM数字频率字
**************************************************************/
INT32  AdjustFpgaFw(INT32 iDf)	
{ 
    INT32 iOffSet;

    iOffSet =  clk_flag ? OFFSET_125M : OFFSET_122M;
    
	if( iDf<0 ) 
	{
		iDf += iOffSet;
	}
	
    return iDf;
}



/*************************************************************
Name: ConvGsmFcToFreqDL
Description: 根据GSM频点号计算下行信号频率
Input:
	freq_code: 频点号
Output:void         
Return:	频率(KHz)
**************************************************************/
FLOAT32 ConvDcsFcToFreqDL( INT32 freq_code )
{
	FLOAT32 freq_point = 0.0;

	if ( IS_DCS_FC(freq_code) )
	{
		if ( freq_code <= DCS_MAX_FRE_CODE_CNMOBILE )
		{
			freq_point = 1805 + GSM_SF_STEP * (freq_code-511);
		}
		else 
		{ 
			freq_point = 1830 + GSM_SF_STEP * (freq_code-511);
		}
	}

	return freq_point;
}


/*************************************************************
Name: ConvGsmFcToFreqDL
Description: 根据GSM频点号计算下行信号频率
Input:
	freq_code: 频点号
Output:void         
Return:	频率(KHz)
**************************************************************/
FLOAT32 ConvGsmFcToFreqDL( INT32 freq_code )
{
	FLOAT32 freq_point = 0.0;

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
	TRACE_INFO("<freq_point=%f, freq_code=%f>\r\n", freq_point, freq_code);
	return freq_point;
}

/*************************************************************
Name: ConvGsmFcToFreqDL
Description: 根据GSM频点号计算下行信号频率
Input:
	freq_code: 频点号
Output:void         
Return:	频率(KHz)
**************************************************************/
FLOAT32 ConvGsmFcToFreqUL( INT32 freq_code )
{
	FLOAT32 freq_point = 0.0;

	if ( IS_GSM_FC(freq_code) )
	{
		if ( freq_code <= 124 )
		{
			freq_point = 10*890 + 10*GSM_SF_STEP * freq_code;
		}
		else 
		{ 
			freq_point = 10*890 + 10*GSM_SF_STEP * (freq_code-1024);
		}
	}
	TRACE_INFO("<freq_point=%f, freq_code=%f>\r\n", freq_point, freq_code);
	return freq_point;
}
 
/*************************************************************
Name: ConvGsmFcToFreqDL
Description: 根据GSM频点号计算下行信号频率
Input:
	freq_code: 频点号
Output:void         
Return:	频率(KHz)
**************************************************************/
INT32 CalcFreqPointToFreq(UCHAR8 ucNetTye,INT32 freq_code) 
{
   INT32 freq = 0;
   
   switch ( ucNetTye )
   {
	    case NET_TYPE_GSM900: 
        	freq= ConvGsmFcToFreqDL(freq_code); 
		break;      
				 
	    case NET_TYPE_DCS1800: 
			freq= ConvDcsFcToFreqDL(freq_code); 

		break; 
				
	    case NET_TYPE_WCDMA2100:
		  	
		break; 
		
	    case NET_TYPE_TD:
		  	
		break; 
		
	    case NET_TYPE_CDMA:
		  	
		break; 	 
		
	    case NET_TYPE_CMMB: 
		  	
		break; 
		
	    default:
			TRACE_ERROR("Err net type.");
	    break; 

   }

   return freq;
}


/*************************************************************
函数名:	    MenCpy   
功能描述:   内存拷贝
输入参数:	void
输出参数：  无 
返回值: 	void   
调用函数：  
被调函数：  
**************************************************************/
void MenCpy(void *pvDst,const void * pvSrc, UINT usLen)
{
    UCHAR8 * pucDst;
	UCHAR8 * pucSrc;
	UINT  usMenLen;
	  
	pucDst   = (UCHAR8 * )pvDst;
	pucSrc   = (UCHAR8 * )pvSrc;
	usMenLen = usLen; 
	  
    if (pucDst == 0 || pucSrc == 0 )
	{
	    return;	
	}  
	  
	while (usMenLen--)
	{
	    *pucDst++ = *pucSrc++;
    }
}






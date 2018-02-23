/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :init.c
* Description :���ļ�����ܱ߳�ʼ������
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			��ʼ�汾
**************************************************************/
#include "Header.h"

extern UINT32 ex_adc_cs;		// �ⲿ����Դѡ��
extern UINT32 fpga_load_status;
extern _T_BIG_PKT_BUFF msg_big_buff[MSG_BIG_PKT_COUNT];
extern FLOAT32 freq_ul_a_mixer;			// A�κ�����л�Ƶ��Ƶ��
extern FLOAT32 freq_dl_b_mixer;		// B��ǰ�����л�Ƶ��Ƶ��
extern FLOAT32 freq_ul_b_mixer;		// B�κ�����л�Ƶ��Ƶ��
extern _T_FPGA_CFG fpga_cfg;
extern UCHAR8 gsm_type_a;	// gsmģʽ
extern UCHAR8 gsm_type_b;	// gsmģʽ
extern _T_MODULE_CFG mod_cfg_a, mod_cfg_b;
extern UINT32 module_param_chg_flag;		//ϵͳ���������޸ı�־


#if(FPGA_TYPE == CYCLONE5)

#elif (FPGA_TYPE == ARRIA2)

#elif (FPGA_TYPE == A7)


#if defined CLIENT_DATANG

const UINT16 ucClkRegVal[][2]={
	
	{0x0000, 0x0081}, 
	{0x0010, 0x0064}, 
	{0x0011, 0x0000},
	{0x0012, 0x0000},
	{0x0016, 0x0028},
	{0x0017, 0x0000},
	{0x0018, 0x000c}, 
	{0x0019, 0x0003}, 
	{0x001a, 0x0028},
	{0x001b, 0x0010},
	{0x001c, 0x0008}, 
	{0x001d, 0x0002}, 
	{0x00f0, 0x00FE},
	{0x00f1, 0x001E}, 
	{0x00f2, 0x0003}, 
	{0x00f3, 0x0008}, 
	{0x00f4, 0x0002}, 
	{0x00f5, 0x00c0}, 
	{0x00f6, 0x0000},
	{0x00f9, 0x0000}, 
	{0x0196, 0x0020},
	{0x0197, 0x0000},
	{0x0198, 0x0000}, 
	{0x0199, 0x0020},
	{0x019a, 0x0000},
	{0x019b, 0x0000}, 
	{0x019c, 0x0007},
	{0x019d, 0x0009},
	{0x019e, 0x0000}, 
	{0x019f, 0x0003},
	{0x01a0, 0x0004},
	{0x01a1, 0x0000}, 
	{0x01ae, 0x0003},
	{0x01af, 0x0004},
	{0x01b0, 0x0000}, 
	{0x01b1, 0x0003},
	{0x01b2, 0x0004}, 
	{0x01b3, 0x0000}, 
	{0x01ba, 0x0000}, 
	{0x01bb, 0x0000}, 
	{0x0230, 0x000a}, 
	{0x0231, 0x0003}, 
	{0x0234, 0x0001},
	{0x00f3, 0x000a},
	{0x0234, 0x0001},
	{0x00f3, 0x0008},
	{0x0234, 0x0001}, 
	{0x0233, 0x0001}, 
	{0x0234, 0x0001}, 
	{0x0233, 0x0000}, 
	{0x0234, 0x0001},
	{0x0000, 0x0000}, 
	{0x0234, 0x0001}, 

}; 




#elif ((defined CLIENT_ERRICSON2) ||(defined CLIENT_ERRICSON_W))

const UINT16 ucClkRegVal[][2]={

{0x0000, 0x0081}, 
{0x0010, 0x0064}, 
{0x0011, 0x0000},
{0x0012, 0x0000},
{0x0016, 0x0028},
{0x0017, 0x0000},
{0x0018, 0x000c}, 
{0x0019, 0x0003}, 
{0x001a, 0x0028},
{0x001b, 0x0010},
{0x001c, 0x0008}, 
{0x001d, 0x0002}, 
{0x00f0, 0x00FE},
{0x00f1, 0x001E}, 
{0x00f2, 0x0003}, 
{0x00f3, 0x0008}, 
{0x00f4, 0x0002}, 
{0x00f5, 0x00c0}, 
{0x00f6, 0x0000},
{0x00f9, 0x0000}, 
{0x0196, 0x0020},
{0x0197, 0x0000},
{0x0198, 0x0000}, 
{0x0199, 0x0020},
{0x019a, 0x0000},
{0x019b, 0x0000}, 
{0x019c, 0x0007},
{0x019d, 0x0009},
{0x019e, 0x0000}, 
{0x019f, 0x0003},
{0x01a0, 0x0004},
{0x01a1, 0x0000}, 
{0x01ae, 0x0003},
{0x01af, 0x0004},
{0x01b0, 0x0000}, 
{0x01b1, 0x0003},
{0x01b2, 0x0004}, 
{0x01b3, 0x0000}, 
{0x01ba, 0x0000}, 
{0x01bb, 0x0000}, 
{0x0230, 0x000a}, 
{0x0231, 0x0003}, 
{0x0234, 0x0001},
{0x00f3, 0x000a},
{0x0234, 0x0001},
{0x00f3, 0x0008},
{0x0234, 0x0001}, 
{0x0233, 0x0001}, 
{0x0234, 0x0001}, 
{0x0233, 0x0000}, 
{0x0234, 0x0001},
{0x0000, 0x0000}, 
{0x0234, 0x0001}, 

};

#else
const UINT16 ucClkRegVal[][2]={
	
	{0x0000, 0x0081}, 
	{0x0010, 0x0064}, 
	{0x0011, 0x0000},
	{0x0012, 0x0000},
	{0x0016, 0x0028},
	{0x0017, 0x0000},
	{0x0018, 0x000c}, 
	{0x0019, 0x0003}, 
	{0x001a, 0x0028},
	{0x001b, 0x0010},
	{0x001c, 0x0008}, 
	{0x001d, 0x0002}, 
	{0x00f0, 0x00FE},
	{0x00f1, 0x001E}, 
	{0x00f2, 0x0003}, 
	{0x00f3, 0x0008}, 
	{0x00f4, 0x0002}, 
	{0x00f5, 0x00c0}, 
	{0x00f6, 0x0000},
	{0x00f9, 0x0000}, 
	{0x0196, 0x0020},
	{0x0197, 0x0000},
	{0x0198, 0x0000}, 
	{0x0199, 0x0020},
	{0x019a, 0x0000},
	{0x019b, 0x0000}, 
	{0x019c, 0x0007},
	{0x019d, 0x0009},
	{0x019e, 0x0000}, 
	{0x019f, 0x0003},
	{0x01a0, 0x0004},
	{0x01a1, 0x0000}, 
	{0x01ae, 0x0003},
	{0x01af, 0x0004},
	{0x01b0, 0x0000}, 
	{0x01b1, 0x0003},
	{0x01b2, 0x0004}, 
	{0x01b3, 0x0000}, 
	{0x01ba, 0x0000}, 
	{0x01bb, 0x0000}, 
	{0x0230, 0x000a}, 
	{0x0231, 0x0003}, 
	{0x0234, 0x0001},
	{0x00f3, 0x000a},
	{0x0234, 0x0001},
	{0x00f3, 0x0008},
	{0x0234, 0x0001}, 
	{0x0233, 0x0001}, 
	{0x0234, 0x0001}, 
	{0x0233, 0x0000}, 
	{0x0234, 0x0001},
	{0x0000, 0x0000}, 
	{0x0234, 0x0001}, 

}; 
#endif

#endif




/*************************************************************
Name:InitSystemTimer          
Description:��ʼ��ϵͳ��ʱ��    
Input:void          
Output:void         
Return:void         
**************************************************************/
void InitSystemTimer(void)
{
	InitTimeTick();
}


/*************************************************************
Name       :InitClkChip         
Description:��ʼ��ʱ�� 
Input:void
Output:void      
Return:-1:ʧ�ܣ�0: �ɹ�             
**************************************************************/
BOOL InitClkChip(void)
{
    UCHAR8 i;

#if 0
const UINT16 ucClkRegVal_50M_V4B[][2][2]={
     //reg   //val    //reg     //val 
{{0x0000, 0x0081},{0x0000, 0x0081}},
{{0x0010, 0x00FA},{0x0010, 0x00FA}},
{{0x0011, 0x0000},{0x0011, 0x0000}},
{{0x0012, 0x0000},{0x0012, 0x0000}}, 
{{0x0016, 0x0028},{0x0016, 0x0028}},
{{0x0017, 0x0000},{0x0017, 0x0000}},
{{0x0018, 0x000c},{0x0018, 0x000c}}, 
{{0x0019, 0x0003},{0x0019, 0x0003}}, 
{{0x001a, 0x0028},{0x001a, 0x0028}},
{{0x001b, 0x0010},{0x001b, 0x0010}},
{{0x001c, 0x0008},{0x001c, 0x0008}},  
{{0x001d, 0x0002},{0x001d, 0x0002}}, 
{{0x00f0, 0x00FE},{0x00f0, 0x00FE}},
{{0x00f1, 0x00A5},{0x00f1, 0x00A5}},
{{0x00f2, 0x0003},{0x00f2, 0x0003}},  
{{0x00f3, 0x0008},{0x00f3, 0x0008}}, 
{{0x00f4, 0x0002},{0x00f4, 0x0002}},
{{0x00f5, 0x00c0},{0x00f5, 0x00c0}},  
{{0x00f6, 0x0000},{0x00f6, 0x0000}},
{{0x00f9, 0x0000},{0x00f9, 0x0000}},  
{{0x0196, 0x0020},{0x0196, 0x0020}},
{{0x0197, 0x0000},{0x0197, 0x0000}},
{{0x0198, 0x0000},{0x0198, 0x0000}}, 
{{0x0199, 0x0020},{0x0199, 0x0020}},
{{0x019a, 0x0000},{0x019a, 0x0000}},
{{0x019b, 0x0000},{0x019b, 0x0000}}, 
{{0x019c, 0x0007},{0x019c, 0x0007}},
{{0x019d, 0x0008},{0x019d, 0x0008}},
{{0x019e, 0x0000},{0x019e, 0x0000}},
{{0x019f, 0x0003},{0x019f, 0x0003}},
{{0x01a0, 0x0003},{0x01a0, 0x0003}},
{{0x01a1, 0x0000},{0x01a1, 0x0000}},  
{{0x01ae, 0x0003},{0x01ae, 0x0003}},
{{0x01af, 0x0003},{0x01af, 0x0003}},
{{0x01b0, 0x0000},{0x01b0, 0x0000}},  
{{0x01b1, 0x0003},{0x01b1, 0x0003}},
{{0x01b2, 0x0003},{0x01b2, 0x0003}}, 
{{0x01b3, 0x0000},{0x01b3, 0x0000}}, 
{{0x01ba, 0x0000},{0x01ba, 0x0000}}, 
{{0x01bb, 0x0000},{0x01bb, 0x0000}}, 
{{0x0230, 0x000a},{0x0230, 0x000a}},  
{{0x0231, 0x0003},{0x0231, 0x0003}},  
{{0x0234, 0x0001},{0x0234, 0x0001}}, 
{{0x00f3, 0x000a},{0x00f3, 0x000a}},
{{0x0234, 0x0001},{0x0234, 0x0001}},
{{0x00f3, 0x0008},{0x00f3, 0x0008}},
{{0x0234, 0x0001},{0x0234, 0x0001}},  
{{0x0233, 0x0001},{0x0233, 0x0001}},  
{{0x0234, 0x0001},{0x0234, 0x0001}}, 
{{0x0233, 0x0000},{0x0233, 0x0000}}, 
{{0x0234, 0x0001},{0x0234, 0x0001}},
{{0x0000, 0x0000},{0x0000, 0x0000}}, 
{{0x0234, 0x0001},{0x0234, 0x0001}}, 

}; 

#endif


	WTD_CLR;
	
	clk_flag=1;
	
	HardResetClkChip(); 


#if 0
	if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A)
	|| (version_number == VERSION_40M_IN_B)
	)
	{
		for (i=0; i<(sizeof(ucClkRegVal_40M)/(4*2));i++)
		{ 
			Ad9524Write(ucClkRegVal_40M[i][clk_flag][0],ucClkRegVal_40M[i][clk_flag][1]);
		} 
	}
	else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN)
	|| (version_number == VERSION_40M_IN_C) || (version_number == VERSION_40M_IN_E)
	)
	{
		for (i=0; i<(sizeof(ucClkRegVal_20M)/(4*2));i++)
		{ 
			Ad9524Write(ucClkRegVal_20M[i][clk_flag][0],ucClkRegVal_20M[i][clk_flag][1]);
		} 
	}
	else if(version_number == VERSION_40M_IN_D)
	{
		for (i=0; i<(sizeof(ucClkRegVal_40M)/(4*2));i++)
		{ 
			Ad9524Write(ucClkRegVal_40M[i][clk_flag][0],ucClkRegVal_40M[i][clk_flag][1]);
		} 
	}
	else if((version_number == VERSION_50M_IN_F)||(version_number == VERSION_50M_IN_V4))
	{
		
		for (i=0; i<(sizeof(ucClkRegVal_50M)/(4*2));i++)
		{ 
			Ad9524Write(ucClkRegVal_50M[i][clk_flag][0],ucClkRegVal_50M[i][clk_flag][1]);
		} 
		
	}
	else if(version_number == VERSION_50M_IN_V5)
	{

		for (i=0; i<(sizeof(ucClkRegVal_50M_WCDMA2100)/(4*2));i++)
		{ 
			Ad9524Write(ucClkRegVal_50M_WCDMA2100[i][clk_flag][0],ucClkRegVal_50M_WCDMA2100[i][clk_flag][1]);
			
		} 

	}
#endif


	#if 0
	for (i=0; i<(sizeof(ucClkRegVal_50M)/(4*2));i++)
	{ 
		//printf("%02x,%02x\r\n",ucClkRegVal_50M[i][clk_flag][0],ucClkRegVal_50M[i][clk_flag][1]);
		Ad9524Write(ucClkRegVal_50M[i][clk_flag][0],ucClkRegVal_50M[i][clk_flag][1]);
		UsNopDelay(10);
	} 
	#endif


	for (i=0; i<(sizeof(ucClkRegVal)/4);i++)
	{
		Ad9524Write(ucClkRegVal[i][0],ucClkRegVal[i][1]);
		UsNopDelay(10);
	} 
	
    return b_TRUE;
}

/*************************************************************
Name:InitAD9627         
Description:��ʼ��AD9627 
Input:void
Output:void      
Return:-1:ʧ�ܣ�0: �ɹ�            
**************************************************************/
BOOL InitAD(void)
{

#if 0
    u8 ret,i;
		
	WTD_CLR;  

    for (i=0;i<(sizeof(ucAd6649RegVal)/2);i++)
    {
       Ad6649Write(ucAd6649RegVal[i][0],ucAd6649RegVal[i][1]);
    } 
	
	return b_TRUE;	 	
#endif	
}


void InitKeyDev(void)
{
	// ��ʼ��9524 
	sys_param_1b[MADD_INIT_CLK_ST].val = (b_FALSE==InitClkChip()) ? 1 : 0 ;
	// ��ʼ��6643  
	//sys_param_1b[MADD_INIT_AD_ST].val = (b_FALSE==InitAD() ? 1 : 0);
	//InitDA_A();  
	//InitDA_B();
}

#if 0
BOOL InitAllKeyDev(void)
{
	InitKeyDev(); 
	Init_Local_Pll(A_MIXER); //822 U PLL  A�����б��� ,REΪ��Ƶ
    Init_Local_Pll(A_MODEN); //839 D PLL  A�����б���  REΪ����
	Init_Local_Pll(B_MIXER); //822 U PLL  A�����б��� ,REΪ��Ƶ
    Init_Local_Pll(B_MODEN); //839 D PLL  A�����б���  REΪ����   
    return b_TRUE;
}
#endif

#if 0
UINT16 GetStrMonth( UCHAR8 * str_month )
{
	UINT32 tmp = 0;
	UINT16 i;

	for (i=0; i<3; i++)
	{
		tmp<<=8;
		
		if ( VAL_IN_RANGE(str_month[i], 'a', 'z') )
		{
			tmp |= str_month[i];
			continue;
		}
		
		if ( VAL_IN_RANGE(str_month[i], 'A', 'Z') )
		{ 
			tmp |= (str_month[i]+0x20);
			continue;
		}  

		return 0;
	}
	
	if ( tmp == MONTH_CODE_JAN )	return 1;
	if ( tmp == MONTH_CODE_FEB)	return 2;
	if ( tmp == MONTH_CODE_MAR)	return 3;
	if ( tmp == MONTH_CODE_APR)	return 4;
	if ( tmp == MONTH_CODE_MAY)	return 5;
	if ( tmp == MONTH_CODE_JUN)	return 6;
	if ( tmp == MONTH_CODE_JUL)	return 7;
	if ( tmp == MONTH_CODE_AUG)	return 8;
	if ( tmp == MONTH_CODE_SEP)	return 9;
	if ( tmp == MONTH_CODE_OCT)	return 10;
	if ( tmp == MONTH_CODE_NOV)	return 11;
	if ( tmp == MONTH_CODE_DEC)	return 12;

	return 0;
}

UINT16 GetStrIntVal( UCHAR8 * str_int, INT16 str_len )
{
	UINT16 tmp = 0;
	UCHAR8 ch;
	
	if (str_len>4) str_len=4;

	while( str_len>0 )
	{
		if ( *str_int != ' ' )
		{
			break;
		}
		str_len--;
		str_int++;
	}
	
	while ( str_len--)
	{
		ch = *str_int++;
		
		if ( VAL_IN_RANGE( ch, '0', '9') )
		{
			tmp = (tmp*10)+( ch-'0' );
		}
		else
		{
			break;
		}
	}
	return tmp;
}

/*************************************************************
Name:ConvStrToDate         
Description: ����ַ����е�������������ڵ�ǰ���ϵ
Input:
	p_str: �������ڵ��ַ�������ʽ[M D Y],Mռ3�ֽ�[Jan.Feb.Mar.Apr.May Jun.Jul.Aug.Sep.Oct.Nov.Dec.]֮һ��Dռ2�ֽ�1~31��Yռ4�ֽڣ����
	day: 	��������-��
	month: 	��������-��
	year:	��������-��
Output:void      
Return:
	0:ͬһ��
	1:�ַ�����ʾ�������ڸ�������֮��
	-1:�ַ�����ʾ�������ڸ�������֮ǰ
	-2:����������ַ���
**************************************************************/
CHAR8 CheckStrDate( UCHAR8* p_str, UINT16 day, UINT16 month, UINT16 year )
{
	UINT16 tmp;
	//[MMM_DD_YYYY]
	tmp = GetStrIntVal(p_str+7, 4);		// ��
	if (0==tmp) return -2;
	if ( tmp<year )
	{
		return -1;
	}
	else if ( tmp>year )
	{
		return 1;
	}
	else
	{
		tmp = GetStrMonth(p_str+0);
		if (0==tmp) return -2;
		if ( tmp<month )
		{
			return -1;
		}
		else if ( tmp>month )
		{
			return 1;
		}
		else
		{
			tmp = GetStrIntVal(p_str+4, 2);
			if (0==tmp) return -2;
			if ( tmp<day )
			{
				return -1;
			}
			else if ( tmp>day )
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	return -2;
}
#endif

//#if 0//20130621
/*************************************************************
Name:ThrUartConfig         
Description: ����͸���˿�
Input:void
Output:void      
Return:void
**************************************************************/
void ThrUartConfig()
{
	sys_param_1b[MADD_THR_PORT].val = 0;
	sys_param_1b[MADD_THR_BAUD].val = 0;
	//ThrUartIntDisable();   
	ResetThrFifo();
	ThrUart_Init(sys_param_1b[MADD_THR_PORT].val, sys_param_1b[MADD_THR_BAUD].val);
} 
//#endif 

/*************************************************************
Name:CtrlUartConfig         
Description: ���ÿ��ƶ˿�
Input:void
Output:void      
Return:void
**************************************************************/
void CtrlUartConfig()
{
	UINT32 baudrate = 9600;
	sys_param_1b[MADD_CTRL_BAUD].val = 0;
	switch( sys_param_1b[MADD_CTRL_BAUD].val )
	{
		case 0:	baudrate = 9600;		break;
		case 1:	baudrate = 19200;		break;
		case 2:	baudrate = 38400;		break;
		case 3:	baudrate = 57600;		break;
		case 4:	baudrate = 115200;	break;
	    default: //return 0;
	} 
	
	InitControlUart(baudrate);
}


/*************************************************************
Name:InitSystem         
Description: ϵͳ��ʼ��
Input:void
Output:void      
Return:void
**************************************************************/
void InitSystem()
{
	UINT32 i;

	// AB��ͨ����ʽ
	fpga_cfg.a_net_type = A_NETWORK_TYPE;
	fpga_cfg.b_net_type = B_NETWORK_TYPE;
	fpga_cfg.c_net_type = C_NETWORK_TYPE;
	fpga_cfg.d_net_type = D_NETWORK_TYPE;

	fpga_cfg.a_fpga_data_clk = FPGA_DATA_CLK_A;
	fpga_cfg.b_fpga_data_clk = FPGA_DATA_CLK_B;
	fpga_cfg.c_fpga_data_clk = FPGA_DATA_CLK_C;
	fpga_cfg.d_fpga_data_clk = FPGA_DATA_CLK_D;

	fpga_cfg.a_9363 = TF_A;
	fpga_cfg.b_9363 = TF_B;
	fpga_cfg.c_9363 = TF_C;
	fpga_cfg.d_9363 = TF_D;

	#if ((defined CLIENT_ERRICSON2) ||(defined CLIENT_ERRICSON_W))//C��ʹ��9363A;
	fpga_cfg.c_9363 = TF_A;
	#endif
	
	// ��ʼ��ϵͳ��ʱ��
	SystemInit();  

	// �����ж������� /* Set the Vector Table base location at 0x08008000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x8000);

	InitGpio();	// ����IO��
	WTD_CLR;
	UsbDisConnect();  

	// �ضϵ��������
//	EnableModulatorA(0);
//	EnableModulatorB(0);
//	EnableModulatorC(0);
//	EnableModulatorD(0);


#ifndef NOTRACE	
	//InitDebugUart( DEBUG_UART_BAUD  );		// ���õ��Դ���
#endif 
	InitDebugUart( DEBUG_UART_BAUD	);		// ���õ��Դ���

	//Uart1_Init(DEBUG_UART_BAUD);
	TRACE_INFO("Init APP SPI\r\n");
	InitSpi();	// ��ʼ��SPI���� 
	
//	TRACE_INFO("Init Sys Time Tick\r\n");
	InitSystemTimer();		// ��ʼ��ϵͳ���Ķ�ʱ��

//	TRACE_INFO("Get Flash Page Size\r\n");
	GetFlashPageSize();		// ��ȡFlashҳ��С

	InitUsb();


	WTD_CLR;
	//�ϵ���ʼ��Ĭ�ϲ���
	ParamResetDefault();

	//���ⲿFLASH�ж�ȡϵͳ���� 
	GetSysParamFromFlash();  

	// ��ȡ���������³�ʼ�����ֲ���
	ParamPreInit();  

	InitKeyDev(); 
	TRACE_INFO("InitKeyDev OK\r\n");

	WTD_CLR;  
	//InitExtentBus_8();	// ��ʼ��8λ����
	FpgaLoad();			// ����FPGA 
	InitExtentBus_16();	// ��ʼ��16λ���� 

	if ( FPGA_LDST_OK== fpga_load_status )
	{
		if ( 0!=FpgaTest() )	// �Ĵ�����д���Գɹ�
		{
			
			// ȷ��ϵͳʱ��ģʽ������ʱ��оƬ
			//CheckClkMode();     
			// ����FPGA�Ĵ���
			AfterFpgaLoad();
			
			sys_param_1b[MADD_LOAD_FPGA_ST].val = 0;	// ���سɹ�
			printf("FPGA test �ɹ�\r\n");
		}
		else
		{
			sys_param_1b[MADD_LOAD_FPGA_ST].val = 1;	// ����ʧ��
			printf("FPGA test ����ʧ��\r\n");
			fpga_load_status = FPGA_LDST_INIT_ERR;
			FpgaSetErrInfo(FPGA_ERR_PROG);
		}
	}
	else
	{
		TRACE_ERROR("Fpga load Fail\r\n");
		sys_param_1b[MADD_LOAD_FPGA_ST].val = 2;	// ����ʧ��
		FpgaSetErrInfo(FPGA_ERR_PROG);
		printf("FPGA����ʧ��2\r\n");
	}
	WTD_CLR; 
	//InitKeyDev();
	

	WTD_CLR; 
	InitFpga();
	WTD_CLR; 
	InitTransceiver(SYS_A_FLAG);
	InitTransceiver(SYS_B_FLAG);
	InitTransceiver(SYS_C_FLAG);
	InitTransceiver(SYS_D_FLAG);

	#if 0
	if(FPGA_LDST_OK== fpga_load_status )
	{
		
		TFInit();
		TFInitCs(TF_A);
		WTD_CLR; 
		if(0!=InitTransceiver(TF_A))
		{
			TRACE_INFO("InitTransceiver_A fail\r\n");
		}
		//TFInit();	
		TFInitCs(TF_A);
		WTD_CLR; 
		if(0!=InitTransceiver(TF_A))
		{
			TRACE_INFO("InitTransceiver_A fail\r\n");
		}
	}
	#endif
	
	
	//InitHmc1197();	
	
	
	
	// ����͸���˿�
	ThrUartConfig(); 

	//���ÿ��ƶ˿� 
	CtrlUartConfig();

	// ��ʼ���ڲ�AD����ʼ��ص�ѹ
	InitAdc();
	AdcStartConv();
	
#if 0	
	WTD_CLR; 
	//��ʼ��ָ���û���һЩ�������� 
	InitUserInterface(); 
   
	// ����͸���˿�
	ThrUartConfig(); 
	//���ÿ��ƶ˿� 
	CtrlUartConfig();
#ifndef NOTRACE	
	//InitDebugUart( DEBUG_UART_BAUD  );		// ���õ��Դ���
#endif 	
	//	InitPhyIo();
	//	HardResetPhy(PHY5_KSZ9031);

	// ����USB
	InitUsb();
	
	WTD_CLR;
	// ��ʼ����������
	InitRec();

	// ��ʼ���ڲ�AD����ʼ��ص�ѹ
	InitAdc();
	AdcStartConv();

	//ʹ�ܶ�Ӧ�Ĺ��
	EnableOpt();		// ���ʹ��

	WTD_CLR;
	//Ƶ��������ʼ��
	FPS_Init(); 
	// �ϵ�󣬽����ְ��ϵ�״̬��1
	sys_param_1b[MADD_POWERUP_ST].val = 1;
	WTD_CLR;
	
	InitPhyReg( PHY5_KSZ9031);

	SetAdjBenZhenSignalPara();
	GetPllStatus(); 
#endif

#if defined CLIENT_ERRICSON
	//Ƶ��������ʼ��
	FPS_Init();
#endif
	// ���¸��ݲ�������FPGA�Ĵ���
	module_param_chg_flag = 0xFFFFFFFF;
	
	
}




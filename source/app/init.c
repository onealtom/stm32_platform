/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :init.c
* Description :该文件存放周边初始化函数
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			初始版本
**************************************************************/
#include "Header.h"
#include "stm32f10x_tim.h"
extern UINT32 ex_adc_cs;		// 外部采样源选择
extern UINT32 fpga_load_status;
extern _T_BIG_PKT_BUFF msg_big_buff[MSG_BIG_PKT_COUNT];
extern FLOAT32 freq_ul_a_mixer;			// A段后端上行混频器频率
extern FLOAT32 freq_dl_b_mixer;		// B段前端下行混频器频率
extern FLOAT32 freq_ul_b_mixer;		// B段后端上行混频器频率
extern _T_FPGA_CFG fpga_cfg;
extern UCHAR8 gsm_type_a;	// gsm模式
extern UCHAR8 gsm_type_b;	// gsm模式

//extern UINT32 module_param_chg_flag;		//系统工作参数修改标志


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
Description:初始化系统定时器    
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
Description:初始化时钟 
Input:void
Output:void      
Return:-1:失败，0: 成功             
**************************************************************/
BOOL InitClkChip(void)
{
    UCHAR8 i;

	WTD_CLR;
	
	HardResetClkChip(); 

	for (i=0; i<(sizeof(ucClkRegVal)/4);i++)
	{
		Ad9524Write(ucClkRegVal[i][0],ucClkRegVal[i][1]);
		UsNopDelay(10);
	} 
	
    return b_TRUE;
}

/*************************************************************
Name:InitAD9627         
Description:初始化AD9627 
Input:void
Output:void      
Return:-1:失败，0: 成功            
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
	// 初始化9524 
	////sys_param_1b[MADD_INIT_CLK_ST].val = (b_FALSE==InitClkChip()) ? 1 : 0 ;
	InitClkChip();
	// 初始化6643  
	//sys_param_1b[MADD_INIT_AD_ST].val = (b_FALSE==InitAD() ? 1 : 0);
	//InitDA_A();  
	//InitDA_B();
}

#if 0
BOOL InitAllKeyDev(void)
{
	InitKeyDev(); 
	Init_Local_Pll(A_MIXER); //822 U PLL  A段上行本震 ,RE为混频
    Init_Local_Pll(A_MODEN); //839 D PLL  A段下行本震  RE为调制
	Init_Local_Pll(B_MIXER); //822 U PLL  A段上行本震 ,RE为混频
    Init_Local_Pll(B_MODEN); //839 D PLL  A段下行本震  RE为调制   
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
Description: 检查字符串中的日期与给定日期的前后关系
Input:
	p_str: 包含日期的字符串，格式[M D Y],M占3字节[Jan.Feb.Mar.Apr.May Jun.Jul.Aug.Sep.Oct.Nov.Dec.]之一，D占2字节1~31，Y占4字节，年份
	day: 	给定日期-号
	month: 	给定日期-月
	year:	给定日期-年
Output:void      
Return:
	0:同一天
	1:字符串表示的日期在给定日期之后
	-1:字符串表示的日期在给定日期之前
	-2:错误的日期字符串
**************************************************************/
CHAR8 CheckStrDate( UCHAR8* p_str, UINT16 day, UINT16 month, UINT16 year )
{
	UINT16 tmp;
	//[MMM_DD_YYYY]
	tmp = GetStrIntVal(p_str+7, 4);		// 年
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
Description: 配置透传端口
Input:void
Output:void      
Return:void
**************************************************************/
void ThrUartConfig()
{
	////sys_param_1b[MADD_THR_PORT].val = 0;
	////sys_param_1b[MADD_THR_BAUD].val = 0;
	//ThrUartIntDisable();   
	ResetThrFifo();
	////ThrUart_Init(sys_param_1b[MADD_THR_PORT].val, sys_param_1b[MADD_THR_BAUD].val);
} 
//#endif 

/*************************************************************
Name:CtrlUartConfig         
Description: 配置控制端口
Input:void
Output:void      
Return:void
**************************************************************/
void CtrlUartConfig()
{

}


/**
	* @brief  Configures the different system clocks.
	* @param  None
	* @retval None
	*/
void RCC_Configuration(void)
{
	/* PCLK1 = HCLK/4 */
	RCC_PCLK1Config(RCC_HCLK_Div4);

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

/**
	* @brief  Configure the GPIO Pins.
	* @param  None
	* @retval None
	*/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOC Configuration:Pin6, 7, 8 and 9 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
	* @brief  Configure the nested vectored interrupt controller.
	* @param  None
	* @retval None
	*/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

void InitTimer2(void) 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//__IO uint16_t CCR1_Val = 40961;
	__IO uint16_t CCR1_Val = 60000;
	__IO uint16_t CCR2_Val = 27309;
	__IO uint16_t CCR3_Val = 13654;
	__IO uint16_t CCR4_Val = 6826;
	uint16_t PrescalerValue = 0;
	uint32_t SystemCoreClock = 72000000;
	
	/* System Clocks Configuration */
	RCC_Configuration();

	/* NVIC Configuration */
	NVIC_Configuration();

	/* ---------------------------------------------------------------
		TIM2 Configuration: Output Compare Timing Mode:
		TIM2 counter clock at 6 MHz
		//CC1 update rate = TIM2 counter clock / CCR1_Val = 146.48 Hz , 6.82ms
		CC1 update rate = TIM2 counter clock / CCR1_Val = 100 Hz , 10ms
		CC2 update rate = TIM2 counter clock / CCR2_Val = 219.7 Hz , 4.55ms
		CC3 update rate = TIM2 counter clock / CCR3_Val = 439.4 Hz , 2.27ms
		CC4 update rate = TIM2 counter clock / CCR4_Val = 878.9 Hz , 1.13ms
	--------------------------------------------------------------- */

	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock / 12000000) - 1;

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Prescaler configuration */
	TIM_PrescalerConfig(TIM2, PrescalerValue, TIM_PSCReloadMode_Immediate);

	/* Output Compare Timing Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

	/* TIM IT enable */
	TIM_ITConfig(TIM2, TIM_IT_CC1 , ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
} 

/*************************************************************
Name:InitSystem         
Description: 系统初始化
Input:void
Output:void      
Return:void
**************************************************************/
void InitSystem()
{
	UINT32 i;

	// AB段通信制式
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

	#if ((defined CLIENT_ERRICSON2) ||(defined CLIENT_ERRICSON_W))//C段使用9363A;
	fpga_cfg.c_9363 = TF_A;
	#endif
	
	// 初始化系统和时钟
	SystemInit();  

	// 重置中断向量表 /* Set the Vector Table base location at 0x08008000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x8000);

	InitGpio();	// 配置IO口
	WTD_CLR;
	UsbDisConnect();  

	// 关断调制器输出
//	EnableModulatorA(0);
//	EnableModulatorB(0);
//	EnableModulatorC(0);
//	EnableModulatorD(0);


	InitDebugUart( DEBUG_UART_BAUD	);		// 配置调试串口
	Uart3_Init(115200);
	
	//Uart1_Init(DEBUG_UART_BAUD);
	TRACE_INFO("Init APP SPI\r\n");
	InitSpi();	// 初始化SPI总线 
	
//	TRACE_INFO("Init Sys Time Tick\r\n");
	InitSystemTimer();		// 初始化系统节拍定时器
	InitTimer2();
//	TRACE_INFO("Get Flash Page Size\r\n");
	GetFlashPageSize();		// 读取Flash页大小

	InitUsb();

	spiffs_init();
	WTD_CLR;
	//上电后初始化默认参数
	////ParamResetDefault();

	//从外部FLASH中读取系统参数 
	////GetSysParamFromFlash();  

	// 读取参数后重新初始化部分参数
	////ParamPreInit();  

	InitKeyDev(); 
	TRACE_INFO("InitKeyDev OK\r\n");

	WTD_CLR;  
	//InitExtentBus_8();	// 初始化8位总线
	//FpgaLoad();			// 加载FPGA 
	InitExtentBus_16();	// 初始化16位总线 

	if ( FPGA_LDST_OK== fpga_load_status )
	{
		if ( 0!=FpgaTest() )	// 寄存器读写测试成功
		{
			// 确定系统时钟模式并配置时钟芯片
			//CheckClkMode();     
			// 配置FPGA寄存器
			AfterFpgaLoad();
////			sys_param_1b[MADD_LOAD_FPGA_ST].val = 0;	// 加载成功
			printf("FPGA test success\r\n");
		}
		else
		{
////			sys_param_1b[MADD_LOAD_FPGA_ST].val = 1;	// 加载失败
			printf("FPGA test Fail\r\n");
			fpga_load_status = FPGA_LDST_INIT_ERR;
			FpgaSetErrInfo(FPGA_ERR_PROG);
		}
	}
	else
	{
		TRACE_ERROR("Fpga load Fail\r\n");
////		sys_param_1b[MADD_LOAD_FPGA_ST].val = 2;	// 加载失败
		FpgaSetErrInfo(FPGA_ERR_PROG);
		printf("FPGA Fail 2\r\n");
	}
	WTD_CLR;
	//InitKeyDev();

	WTD_CLR; 

	//ad936x_init_main();
	InitFpga();

	WTD_CLR;
	//InitTransceiver(SYS_A_FLAG);
	///InitTransceiver(SYS_B_FLAG);
	///InitTransceiver(SYS_C_FLAG);
	///InitTransceiver(SYS_D_FLAG);

	//InitHmc1197();	
	
	
	
	// 配置透传端口
	ThrUartConfig(); 

	//配置控制端口 
	CtrlUartConfig();

	// 初始化内部AD，开始监控电压
	InitAdc();
	AdcStartConv();
	
#if defined CLIENT_ERRICSON
	//频点搜索初始化
	FPS_Init();
#endif
	// 重新根据参数配置FPGA寄存器
	//module_param_chg_flag = 0xFFFFFFFF;
	

	
}




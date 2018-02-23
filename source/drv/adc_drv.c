/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司

*************************************************************
文件名：   ADC_DRV_C_
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： ADC_DRV_C_的底层驱动文件 
函数列表： 
修改日期： 
        1.日期:      2010年08月05日  
          作者：     韦瑞锦 
          修改内容： 原版
        2.日期:      2012年04月17日  
          作者：     邓子谦
          修改内容： 微型光钎V02 
**************************************************************/
#include "Header.h"

volatile UINT16 adc_result[9];

volatile UINT16 ex_adc_result[8];

volatile UINT16 ex_channel=0;


/*************************************************************
Name:          InitAdcInterrupt        
Description:   ADC的中断配置
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void InitAdcInterrupt(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable ADC1_2 IRQChannel */
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = ADC_INT_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/*************************************************************
Name:          AdcDmaConfig        
Description:   ADC的DMA配置
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcDmaConfig()
{
	DMA_InitTypeDef DMA_InitStructure;

	//启动DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_result;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 9;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		    //循环模式开启，Buffer写满后，自动回到初始地址开始传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);

}



/*************************************************************
Name:          AdcConfig        
Description:   ADC的规则组配置
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcConfig()
{
	ADC_InitTypeDef ADC_InitStructure;

	//启动ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;				// 扫描模式开启
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;			// 连续转换开启
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		// 右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 9;						// 通道数9
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 4, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 5, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 6, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 7, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9,  8, ADC_SampleTime_55Cycles5);


	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 9, ADC_SampleTime_239Cycles5);	// 内部温度传感器,通道16,放在转换结果最后
	
}


/*************************************************************
Name:          AdcConfig        
Description:   ADC的注入组配置
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcExConfig()
{
	ADC_InjectedSequencerLengthConfig(ADC1, 1);			// 注入转换通道数
	/* ADC1 injected channel Configuration */ 
	ADC_InjectedChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_71Cycles5);		
	/* ADC1 injected external trigger configuration */
	ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_None);

	ex_channel = 1;
	//SwitchExChannel();
	InitAdcInterrupt();
}


/*************************************************************
Name:          AdcConfig        
Description:   ADC的校准
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcAdj()
{
	// 下面是ADC自动校准，开机后需执行一次，保证精度
	// Enable ADC1 reset calibaration register
	ADC_ResetCalibration(ADC1);
	// Check the end of ADC1 reset calibration register
	while(ADC_GetResetCalibrationStatus(ADC1));

	// Start ADC1 calibaration
	ADC_StartCalibration(ADC1);
	// Check the end of ADC1 calibration
	while(ADC_GetCalibrationStatus(ADC1));
	// ADC自动校准结束---------------

}


/*************************************************************
Name:          InitAdc        
Description:   初始化ADC
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void InitAdc()
{
	AdcDmaConfig();
	AdcConfig();

	AdcExConfig();

	ADC_Cmd(ADC1, ENABLE);
	
	ADC_DMACmd(ADC1, ENABLE);

	AdcAdj();

}


/*************************************************************
Name:          AdcStartConv        
Description:   启动ADC规则组的转化
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcStartConv()
{
	//启动第一次AD转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



/*************************************************************
Name:          AdcStartExConv        
Description:   启动ADC注入组的转化
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcStartExConv()
{
	ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);
	ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);		// 使能转换完成中断
}


/*************************************************************
Name:          SwitchExChannel        
Description:   切换8选1开关
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void SwitchExChannel()
{
	ex_channel++;
	
	if ( ex_channel >= ADC_EX_CH_COUNT )
	{
		ex_channel = 0;
	}
//	TRACE_INFO("SwCh%d\r\n", ex_channel);

#if 0
	
	CLR_AD_EX_CSA_PIN;
	CLR_AD_EX_CSB_PIN;
	CLR_AD_EX_CSC_PIN;
	
	switch( ex_channel )
	{
	case 0:				// 000
		break;

	case 1:				// 001
		SET_AD_EX_CSA_PIN;
		break;

	case 2:				// 010
		SET_AD_EX_CSB_PIN;
		break;

	case 3:				// 011
		SET_AD_EX_CSA_PIN;
		SET_AD_EX_CSB_PIN;
		break;

	case 4:				// 100
		SET_AD_EX_CSC_PIN;
		break;

	case 5:				// 101
		SET_AD_EX_CSA_PIN;
		SET_AD_EX_CSC_PIN;
		break;

	case 6:				// 110
		SET_AD_EX_CSB_PIN;
		SET_AD_EX_CSC_PIN;
		break;

	case 7:				// 111
		SET_AD_EX_CSA_PIN;
		SET_AD_EX_CSB_PIN;
		SET_AD_EX_CSC_PIN;
		break;
	
	}
#endif	
}


/*************************************************************
Name:          SaveExAdcResult        
Description:   保存中断完成的ADC转换结果并切换8选1开关
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void SaveExAdcResult()
{
	ex_adc_result[ex_channel] = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
	ADC_ITConfig(ADC1, ADC_IT_JEOC, DISABLE);		// 关闭转换完成中断
	SwitchExChannel();
}




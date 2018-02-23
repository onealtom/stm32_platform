/************************************************************

     Copyright (C), 2011-2111, ����̩�˿Ƽ����޹�˾

*************************************************************
�ļ�����   ADC_DRV_C_
�汾�ţ�   V03
���ߣ�     Τ��� 
�������ڣ� 2010��08��05��
����޸ģ� 
���������� ADC_DRV_C_�ĵײ������ļ� 
�����б� 
�޸����ڣ� 
        1.����:      2010��08��05��  
          ���ߣ�     Τ��� 
          �޸����ݣ� ԭ��
        2.����:      2012��04��17��  
          ���ߣ�     ����ǫ
          �޸����ݣ� ΢�͹�ǥV02 
**************************************************************/
#include "Header.h"

volatile UINT16 adc_result[9];

volatile UINT16 ex_adc_result[8];

volatile UINT16 ex_channel=0;


/*************************************************************
Name:          InitAdcInterrupt        
Description:   ADC���ж�����
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
Description:   ADC��DMA����
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcDmaConfig()
{
	DMA_InitTypeDef DMA_InitStructure;

	//����DMAʱ��
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
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		    //ѭ��ģʽ������Bufferд�����Զ��ص���ʼ��ַ��ʼ����
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);

}



/*************************************************************
Name:          AdcConfig        
Description:   ADC�Ĺ���������
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcConfig()
{
	ADC_InitTypeDef ADC_InitStructure;

	//����ADC1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;				// ɨ��ģʽ����
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;			// ����ת������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		// �Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 9;						// ͨ����9
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
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 9, ADC_SampleTime_239Cycles5);	// �ڲ��¶ȴ�����,ͨ��16,����ת��������
	
}


/*************************************************************
Name:          AdcConfig        
Description:   ADC��ע��������
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcExConfig()
{
	ADC_InjectedSequencerLengthConfig(ADC1, 1);			// ע��ת��ͨ����
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
Description:   ADC��У׼
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcAdj()
{
	// ������ADC�Զ�У׼����������ִ��һ�Σ���֤����
	// Enable ADC1 reset calibaration register
	ADC_ResetCalibration(ADC1);
	// Check the end of ADC1 reset calibration register
	while(ADC_GetResetCalibrationStatus(ADC1));

	// Start ADC1 calibaration
	ADC_StartCalibration(ADC1);
	// Check the end of ADC1 calibration
	while(ADC_GetCalibrationStatus(ADC1));
	// ADC�Զ�У׼����---------------

}


/*************************************************************
Name:          InitAdc        
Description:   ��ʼ��ADC
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
Description:   ����ADC�������ת��
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcStartConv()
{
	//������һ��ADת��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



/*************************************************************
Name:          AdcStartExConv        
Description:   ����ADCע�����ת��
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void AdcStartExConv()
{
	ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);
	ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);		// ʹ��ת������ж�
}


/*************************************************************
Name:          SwitchExChannel        
Description:   �л�8ѡ1����
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
Description:   �����ж���ɵ�ADCת��������л�8ѡ1����
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void SaveExAdcResult()
{
	ex_adc_result[ex_channel] = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
	ADC_ITConfig(ADC1, ADC_IT_JEOC, DISABLE);		// �ر�ת������ж�
	SwitchExChannel();
}




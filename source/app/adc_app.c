/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :adc.c
* Description :ADת������
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


extern _T_PARAM_1B sys_param_1b[];

UINT32 ex_adc_cs  = 0;		    // �ⲿ����Դѡ��  

UINT16 pd_counter = 0;			// ���ʼ��ѡ��      
 
UINT16 adc_sample[ADC_DERICT_CH_COUNT+ADC_EX_CH_COUNT+1];

 
/*************************************************************
Name:AdcVoltage          
Description:��ѹ���͵�ADC����
Input:R1�ϵ���ֵK,R2:�µ���ֵ��fs:ADC����ֵ          
Output:void        
Return:�����õ���ʵ�ʵ�ѹֵ
**************************************************************/
FLOAT32 AdcVoltage(FLOAT32 r1,FLOAT32 r2,UINT16 fs)
{
	return ((r1+r2)*ADC_VREF*fs/(r2*ADC_FULL));
}    

/*************************************************************
Name:AdcHandle 
Description:�жϻ�ȡ���в���ֵ��Ĵ���
Input :void           
Output:void         
Return:void 
**************************************************************/
void AdcHandle(void)
{
	CHAR8 i,j;
	UINT32 result;
	FLOAT32 temp;
	
	WTD_CLR;	

//	TRACE_INFO("Adc: ");
	for ( i=0; i<ADC_DERICT_CH_COUNT; i++ )
	{
//		TRACE_INFO_WP("%d %d; ", i, adc_result[i]);
		adc_sample[i] = adc_result[i];
	}     

	for ( i=0; i<ADC_EX_CH_COUNT; i++ )
	{
//		TRACE_INFO_WP("%d %d; ", (ADC_DERICT_CH_COUNT+i), ex_adc_result[i]);
		adc_sample[ADC_DERICT_CH_COUNT+i] = ex_adc_result[i];
	}
//	TRACE_INFO_WP("\r\n"); 

	//����ADC����ֵ����ϵͳ��Ϣ
	// A������VCO��ѹ
	temp = AdcVoltage(200,200,adc_sample[VAD_A_DL_VCO]);
	i = temp * 10;
//	sys_param_1b[MADD_A_DL_VCO_VT].val= i;

	// A������VCO��ѹ 
	temp = AdcVoltage(200,200,adc_sample[VAD_A_UL_VCO]);
	i = temp * 10;   
//	sys_param_1b[MADD_A_UL_VCO_VT].val = i;    

	// ʱ��VCO��ѹ
	temp = AdcVoltage(200,200,adc_sample[VAD_CLK_VCO]);
	i = temp * 10;
	sys_param_1b[MADD_CLK_VCO_VT].val = i;

	// B������VCO��ѹ
	temp = AdcVoltage(200,200,adc_sample[VAD_B_DL_VCO]);
	i = temp * 10;
//	sys_param_1b[MADD_B_DL_VCO_VT].val= i;

	// B������VCO��ѹ
	temp = AdcVoltage(200,200,adc_sample[VAD_B_UL_VCO]);
	i = temp * 10;
//	sys_param_1b[MADD_B_UL_VCO_VT].val = i;

	// A������LNA1��ѹ
	temp = AdcVoltage(10,10,adc_sample[VAD_A_UL_LNA1]);
	i = temp * 10;
//	sys_param_1b[MADD_A_UL_LNA_VT].val = 0;//i;
	sys_param_1b[MADD_A_LNA1_ST].val = 0;// (VAL_IN_RANGE( temp, V_LNA_MIN, V_LNA_MAX ) ) ? 0 : 1;

	// A������LNA2��ѹ
	temp = AdcVoltage(10,10,adc_sample[VAD_A_UL_LNA2]);
	i = temp * 10;
//	sys_param_1b[MADD_A_UL_LNA_VT2].val = 0;//i;
	sys_param_1b[MADD_A_LNA2_ST].val = 0;// (VAL_IN_RANGE( temp, V_LNA_MIN, V_LNA_MAX ) ) ? 0 : 1;

	// B������LNA1��ѹ
	temp = AdcVoltage(10,10,adc_sample[VAD_B_UL_LNA1]);
	i = temp * 10;
//	sys_param_1b[MADD_B_UL_LNA_VT].val= 0;//i;
	sys_param_1b[MADD_B_LNA1_ST].val = 0;// (VAL_IN_RANGE( temp, V_LNA_MIN, V_LNA_MAX ) ) ? 0 : 1;

	// B������LNA2��ѹ
	temp = AdcVoltage(10,10,adc_sample[VAD_B_UL_LNA2]);
	i = temp * 10;
//	sys_param_1b[MADD_B_UL_LNA_VT2].val= 0;//i;
	sys_param_1b[MADD_B_LNA2_ST].val = 0;// (VAL_IN_RANGE( temp, V_LNA_MIN, V_LNA_MAX ) ) ? 0 : 1;

	// ��Դ9V��ѹ
	temp = AdcVoltage( 28.7, 10, adc_sample[VAD_POWER_9V]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_9V0_VT].val = i;

	// ��Դ5.5V��ѹ
	temp = AdcVoltage( 12.7, 10, adc_sample[VAD_POWER_5V5]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_5V5_VT].val = i;

	// ��Դ3.6V��ѹ
	temp = AdcVoltage( 2.49, 10, adc_sample[VAD_POWER_3V6]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_3V6_VT].val = i;

	// ��Դ1.2V��ѹ
	temp = AdcVoltage( 0, 10, adc_sample[VAD_POWER_1V2]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_1V2_VT].val = i;

	// ��Դ2.5V��ѹ
	temp = AdcVoltage( 0, 10, adc_sample[VAD_POWER_2V5]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_2V5_VT].val = i;
	
	WTD_CLR;	
}


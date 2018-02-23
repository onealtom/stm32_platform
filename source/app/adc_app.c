/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :adc.c
* Description :AD转换处理
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


extern _T_PARAM_1B sys_param_1b[];

UINT32 ex_adc_cs  = 0;		    // 外部采样源选择  

UINT16 pd_counter = 0;			// 功率检测选择      
 
UINT16 adc_sample[ADC_DERICT_CH_COUNT+ADC_EX_CH_COUNT+1];

 
/*************************************************************
Name:AdcVoltage          
Description:电压类型的ADC处理
Input:R1上电阻值K,R2:下电阻值，fs:ADC采样值          
Output:void        
Return:测量得到的实际电压值
**************************************************************/
FLOAT32 AdcVoltage(FLOAT32 r1,FLOAT32 r2,UINT16 fs)
{
	return ((r1+r2)*ADC_VREF*fs/(r2*ADC_FULL));
}    

/*************************************************************
Name:AdcHandle 
Description:中断获取所有采样值后的处理
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

	//根据ADC采样值设置系统信息
	// A段下行VCO电压
	temp = AdcVoltage(200,200,adc_sample[VAD_A_DL_VCO]);
	i = temp * 10;
//	sys_param_1b[MADD_A_DL_VCO_VT].val= i;

	// A段上行VCO电压 
	temp = AdcVoltage(200,200,adc_sample[VAD_A_UL_VCO]);
	i = temp * 10;   
//	sys_param_1b[MADD_A_UL_VCO_VT].val = i;    

	// 时钟VCO电压
	temp = AdcVoltage(200,200,adc_sample[VAD_CLK_VCO]);
	i = temp * 10;
	sys_param_1b[MADD_CLK_VCO_VT].val = i;

	// B段下行VCO电压
	temp = AdcVoltage(200,200,adc_sample[VAD_B_DL_VCO]);
	i = temp * 10;
//	sys_param_1b[MADD_B_DL_VCO_VT].val= i;

	// B段上行VCO电压
	temp = AdcVoltage(200,200,adc_sample[VAD_B_UL_VCO]);
	i = temp * 10;
//	sys_param_1b[MADD_B_UL_VCO_VT].val = i;

	// A段上行LNA1电压
	temp = AdcVoltage(10,10,adc_sample[VAD_A_UL_LNA1]);
	i = temp * 10;
//	sys_param_1b[MADD_A_UL_LNA_VT].val = 0;//i;
	sys_param_1b[MADD_A_LNA1_ST].val = 0;// (VAL_IN_RANGE( temp, V_LNA_MIN, V_LNA_MAX ) ) ? 0 : 1;

	// A段上行LNA2电压
	temp = AdcVoltage(10,10,adc_sample[VAD_A_UL_LNA2]);
	i = temp * 10;
//	sys_param_1b[MADD_A_UL_LNA_VT2].val = 0;//i;
	sys_param_1b[MADD_A_LNA2_ST].val = 0;// (VAL_IN_RANGE( temp, V_LNA_MIN, V_LNA_MAX ) ) ? 0 : 1;

	// B段上行LNA1电压
	temp = AdcVoltage(10,10,adc_sample[VAD_B_UL_LNA1]);
	i = temp * 10;
//	sys_param_1b[MADD_B_UL_LNA_VT].val= 0;//i;
	sys_param_1b[MADD_B_LNA1_ST].val = 0;// (VAL_IN_RANGE( temp, V_LNA_MIN, V_LNA_MAX ) ) ? 0 : 1;

	// B段上行LNA2电压
	temp = AdcVoltage(10,10,adc_sample[VAD_B_UL_LNA2]);
	i = temp * 10;
//	sys_param_1b[MADD_B_UL_LNA_VT2].val= 0;//i;
	sys_param_1b[MADD_B_LNA2_ST].val = 0;// (VAL_IN_RANGE( temp, V_LNA_MIN, V_LNA_MAX ) ) ? 0 : 1;

	// 电源9V电压
	temp = AdcVoltage( 28.7, 10, adc_sample[VAD_POWER_9V]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_9V0_VT].val = i;

	// 电源5.5V电压
	temp = AdcVoltage( 12.7, 10, adc_sample[VAD_POWER_5V5]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_5V5_VT].val = i;

	// 电源3.6V电压
	temp = AdcVoltage( 2.49, 10, adc_sample[VAD_POWER_3V6]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_3V6_VT].val = i;

	// 电源1.2V电压
	temp = AdcVoltage( 0, 10, adc_sample[VAD_POWER_1V2]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_1V2_VT].val = i;

	// 电源2.5V电压
	temp = AdcVoltage( 0, 10, adc_sample[VAD_POWER_2V5]);
	i = temp * 10;
	sys_param_1b[MADD_PWR_2V5_VT].val = i;
	
	WTD_CLR;	
}


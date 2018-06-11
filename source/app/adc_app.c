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


//extern _T_PARAM_1B sys_param_1b[];

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


}


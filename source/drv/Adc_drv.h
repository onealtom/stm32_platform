/************************************************************

     Copyright (C), 2011-2111, ����̩�˿Ƽ����޹�˾
     
*************************************************************
�ļ�����   ADC_DRV_H_
�汾�ţ�   V03
���ߣ�     Τ��� 
�������ڣ� 2010��08��05��
����޸ģ� 
���������� ADC_DRV_H_�ĵײ�����ͷ�ļ� 
�����б� 
�޸����ڣ� 
        1.����:      2010��08��05��  
          ���ߣ�     Τ��� 
          �޸����ݣ� ԭ��
        2.����:      2012��04��17��  
          ���ߣ�     ����ǫ
          �޸����ݣ� ΢�͹�ǥV02 
**************************************************************/

#ifndef _ADC_DRV_H_
#define _ADC_DRV_H_

// 8in1 a 
#define SET_AD_EX_CSA_PIN		GPIO_SetBits(GPIOE, GPIO_Pin_5)
#define CLR_AD_EX_CSA_PIN		GPIO_ResetBits(GPIOE, GPIO_Pin_5) 
// 8in1 b 
#define SET_AD_EX_CSB_PIN		GPIO_SetBits(GPIOE, GPIO_Pin_4)
#define CLR_AD_EX_CSB_PIN		GPIO_ResetBits(GPIOE, GPIO_Pin_4)
// 8in1 c 
#define SET_AD_EX_CSC_PIN		GPIO_SetBits(GPIOE, GPIO_Pin_3)
#define CLR_AD_EX_CSC_PIN		GPIO_ResetBits(GPIOE, GPIO_Pin_3)

 
#define ADC1_DR_Address   			 ((u32)0x4001244C)
#define ADC_DERICT_CH_COUNT		8	// ֱ�Ӳ���ͨ����
#define ADC_EX_CH_COUNT			7	// ���ò���ͨ����

// ֱ��ͨ�� 
#define ADC_A_D_VCO_VT				0
#define ADC_B_D_VCO_VT				1
#define ADC_CLK_VCO_VT				2
#define ADC_A_LNA1_VD				3
#define ADC_A_LNA2_VD				4
#define ADC_B_LNA1_VD				5
#define ADC_BATT_VT				    6
#define ADC_1V2_VT                  7

// ����ͨ��
#define ADC_3V6_VT					9
#define ADC_9V0_VT					10
#define ADC_5V5_VT					11
#define ADC_A_U_VCO_VT				12
#define ADC_B_U_VCO_VT				13
#define ADC_2V5_VT					14
#define ADC_B_LNA2_VD				15
 

// ADC��������������
#define VAD_CLK_VCO				    ADC_CLK_VCO_VT
#define VAD_A_DL_VCO				ADC_A_U_VCO_VT
#define VAD_A_UL_VCO				ADC_A_D_VCO_VT
#define VAD_B_DL_VCO				ADC_B_D_VCO_VT
#define VAD_B_UL_VCO				ADC_B_U_VCO_VT
#define VAD_POWER_9V				ADC_9V0_VT 
#define VAD_POWER_5V5				ADC_5V5_VT
#define VAD_POWER_3V6				ADC_3V6_VT
#define VAD_POWER_2V5				ADC_2V5_VT
#define VAD_POWER_1V2				ADC_1V2_VT
#define VAD_A_UL_LNA1				ADC_A_LNA1_VD
#define VAD_A_UL_LNA2				ADC_A_LNA2_VD
#define VAD_B_UL_LNA1				ADC_B_LNA1_VD
#define VAD_B_UL_LNA2				ADC_B_LNA2_VD



extern volatile UINT16 adc_result[];
extern volatile UINT16 ex_adc_result[8];

void InitAdc();
void AdcExConfig();
void AdcStartConv();
void AdcStartExConv();
void SwitchExChannel();
void SaveExAdcResult();

#endif


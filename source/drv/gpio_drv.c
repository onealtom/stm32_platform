/************************************************************

     Copyright (C), 2011-2111, ����̩�˿Ƽ����޹�˾

*************************************************************
�ļ�����   GPIO_DRV_H_
�汾�ţ�   V03
���ߣ�     Τ��� 
�������ڣ� 2010��08��05��
����޸ģ� 
���������� GPIO��ͷ�ļ�
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


/*************************************************************
Name:            InitGpio          
Description:     ��ʼ��MCU�ܽ�
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void InitGpio()
{
	unsigned int i; 

	 GPIO_InitTypeDef gpio_cfg_a[] = { GPIO_CFG_A };
	 GPIO_InitTypeDef gpio_cfg_b[] = { GPIO_CFG_B };
	 GPIO_InitTypeDef gpio_cfg_c[] = { GPIO_CFG_C };
	 GPIO_InitTypeDef gpio_cfg_d[] = { GPIO_CFG_D };
	 GPIO_InitTypeDef gpio_cfg_e[] = { GPIO_CFG_E };

	//GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO|
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
	GPIO_DeInit(GPIOE);

	// ��ӳ��IO����ֹ����JTAG����
	GPIO_PinRemapConfig( GPIO_Remap_SWJ_Disable, ENABLE );

	//GPIO_PinRemapConfig( GPIO_PartialRemap_USART3, ENABLE );
	
	for ( i=0; i<(sizeof(gpio_cfg_a)/sizeof(GPIO_InitTypeDef)); i++)
	{
		GPIO_Init( GPIOA, &gpio_cfg_a[i] );
	}

	for ( i=0; i<(sizeof(gpio_cfg_b)/sizeof(GPIO_InitTypeDef)); i++)
	{
		GPIO_Init( GPIOB, &gpio_cfg_b[i] );
	}

	for ( i=0; i<(sizeof(gpio_cfg_c)/sizeof(GPIO_InitTypeDef)); i++)
	{
		GPIO_Init( GPIOC, &gpio_cfg_c[i] );
	}

	for ( i=0; i<(sizeof(gpio_cfg_d)/sizeof(GPIO_InitTypeDef)); i++)
	{
		GPIO_Init( GPIOD, &gpio_cfg_d[i] );
	}
	
	for ( i=0; i<(sizeof(gpio_cfg_e)/sizeof(GPIO_InitTypeDef)); i++)
	{
		GPIO_Init( GPIOE, &gpio_cfg_e[i] );
	}

//	InitPhyIo();	
//	HardResetPhy(PHY4_VCS8662);
//	HardResetPhy(PHY5_KSZ9031);
	LedOn();
	EnablePower5V5;        //��5V��Դ
	SET_FPGA_NCS1_PIN;  //���ƻ��ţ�ʹ����ʱ�����nWEΪ��
	CLR_FPGA_NCONFIG;
	//ENABLE_AD9524_SYNC;
	CLK_PD_HIGH;  

}


/*************************************************************
Name:            LedFlash          
Description:     LEDָʾ����˸
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void LedFlash()
{
	if ( 0==GPIO_ReadOutputDataBit( GPIOC, IO_LED ) )
	{
		GPIO_SetBits( GPIOC, IO_LED );
	}
	else
	{
		GPIO_ResetBits( GPIOC, IO_LED );
	}
}


/*************************************************************
Name:            LedOn         
Description:     LEDָʾ�Ƴ���
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void LedOn()
{
	GPIO_ResetBits( GPIOC, IO_LED );
}


/*************************************************************
Name:            LedOff         
Description:     LEDָʾ��Ϩ��
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void LedOff()
{
	GPIO_SetBits( GPIOC, IO_LED );
}

/*************************************************************
Name:ClrWtd          
Description:ι��
Input:void          
Output:void         
Return:void         
**************************************************************/
void ClrWtd(void) 
{
	if ( 0==GPIO_ReadOutputDataBit( GPIOB, GPIO_Pin_9 ) )
	{
		GPIO_SetBits( GPIOB, GPIO_Pin_9 );
	}
	else
	{  
		GPIO_ResetBits( GPIOB, GPIO_Pin_9 );
	} 
}


/*************************************************************
Name:HardResetClkChip          
Description:��λʱ��оƬ 
Input:          
Output:void         
Return:void         
**************************************************************/
void HardResetClkChip(void)
{
#if 1
	GPIO_InitTypeDef gpio_ad9524_sp = 
		{GPIO_Pin_14|GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_Out_PP};
		
	// SP0��SP1����Ϊ���ģʽ
	GPIO_Init( GPIOA, &gpio_ad9524_sp );	
	// SP0��SP1����Ϊ�͵�ƽ������SPIģʽ
	GPIO_ResetBits( GPIOA, GPIO_Pin_14);
	GPIO_ResetBits( GPIOA, GPIO_Pin_15);
	// ���͸�λ��
	GPIO_ResetBits( GPIOB, GPIO_Pin_5);
	UsNopDelay(1000);
	// ���߸�λ��
	GPIO_SetBits( GPIOB, GPIO_Pin_5); 
	UsNopDelay(10); 
	// SP0��SP1�ָ�Ϊ��������ģʽ�������������
	gpio_ad9524_sp.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init( GPIOA, &gpio_ad9524_sp );
#endif
#if 0
	GPIO_SetBits( GPIOB, GPIO_Pin_5); 
	UsNopDelay(50*1000);
	GPIO_ResetBits( GPIOB, GPIO_Pin_5);
	UsNopDelay(50*1000);
	GPIO_SetBits( GPIOB, GPIO_Pin_5); 
	UsNopDelay(50*1000); 
#endif
}  


/*************************************************************
Name:            HardReset9122A         
Description:     A��9122Ӳ����λ
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void HardReset9122A()
{
	GPIO_SetBits( GPIOE, GPIO_Pin_1);
	UsNopDelay(50*1000);
	GPIO_ResetBits( GPIOE, GPIO_Pin_1);
	UsNopDelay(50*1000);
	GPIO_SetBits( GPIOE, GPIO_Pin_1);
	UsNopDelay(50*1000);
}


/*************************************************************
Name:            HardReset9122B       
Description:     B��9122Ӳ����λ
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void HardReset9122B()
{
	GPIO_SetBits( GPIOE, GPIO_Pin_0);
	UsNopDelay(50*1000); 
	GPIO_ResetBits( GPIOE, GPIO_Pin_0 );
	UsNopDelay(50*1000);
	GPIO_SetBits( GPIOE, GPIO_Pin_0 );
	UsNopDelay(50*1000);
} 

/*************************************************************
Name:EnableModulatorA          
Description:����A�ε�����ʹ��
Input:enable: 1-on, 0-off          
Output:void         
Return:void         
**************************************************************/
void EnableModulatorA(UCHAR8 enable)
{
#if 0
	if ( 0 != enable )
	{
		CLR_DSOP_A_PIN;
	}
	else
	{
		SET_DSOP_A_PIN;
	}
#endif
}

/*************************************************************
Name:EnableModulatorB          
Description:����B�ε�����ʹ��
Input:enable: 1-on, 0-off          
Output:void         
Return:void         
**************************************************************/
void EnableModulatorB(UCHAR8 enable)
{
	if ( 0 != enable )
	{
		CLR_DSOP_B_PIN;
	}
	else
	{
		SET_DSOP_B_PIN;
	}
}

/*************************************************************
Name:EnableModulatorC         
Description:����A�ε�����ʹ��
Input:enable: 1-on, 0-off          
Output:void         
Return:void         
**************************************************************/
void EnableModulatorC(UCHAR8 enable)
{
#if 0
	if ( 0 != enable )
	{
		CLR_DSOP_A_PIN;
	}
	else
	{
		SET_DSOP_A_PIN;
	}
#endif
}

/*************************************************************
Name:EnableModulatorD          
Description:����B�ε�����ʹ��
Input:enable: 1-on, 0-off          
Output:void         
Return:void         
**************************************************************/
void EnableModulatorD(UCHAR8 enable)
{
#if 0
	if ( 0 != enable )
	{
		CLR_DSOP_B_PIN;
	}
	else
	{
		SET_DSOP_B_PIN;
	}
#endif
}

/*************************************************************
Name:Hmc1197CsEnalbe
Description:HMC1197Ƭѡʹ��   enable 0:���ܣ�1:ʹ��
Input:Ƭѡ
Output:void         
Return:void   
**************************************************************/
void Hmc1197CsEnalbe(UCHAR8 enable)
{
	UINT16 fpga_data;
	
//	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	
	if(1==enable)
	{
//		fpga_data &= ~BIT_HMC_CS;
		GPIO_SetBits( GPIOE, GPIO_Pin_6);
	}else{
//		fpga_data |= BIT_HMC_CS;
		GPIO_ResetBits( GPIOE, GPIO_Pin_6);
	}
//	FPGA_ENABLE_WRITE;
//	FpgaWriteRegister(FPGA_REG_W_HMC_A_PLL,fpga_data);	
//	FPGA_DISABLE_WRITE;
	UsNopDelay(10);
	
}





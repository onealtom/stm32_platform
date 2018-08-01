/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司

*************************************************************
文件名：   GPIO_DRV_H_
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： GPIO的头文件
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


/*************************************************************
Name:            InitGpio          
Description:     初始化MCU管脚
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void InitGpio(void)
{
	unsigned int i; 

	 GPIO_InitTypeDef gpio_cfg_a[] = { GPIO_CFG_A };
	 GPIO_InitTypeDef gpio_cfg_b[] = { GPIO_CFG_B };
	 GPIO_InitTypeDef gpio_cfg_c[] = { GPIO_CFG_C };
	 GPIO_InitTypeDef gpio_cfg_d[] = { GPIO_CFG_D };
	 GPIO_InitTypeDef gpio_cfg_e[] = { GPIO_CFG_E };

	//GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO|
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
	GPIO_DeInit(GPIOE);

	// 重映射IO，禁止用做JTAG调试
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
	EnablePower5V5;        //打开5V电源
	SET_FPGA_NCS1_PIN;  //控制或门，使加载时输出的nWE为高
	CLR_FPGA_NCONFIG;
	//ENABLE_AD9524_SYNC;
	CLK_PD_HIGH;  

}


/*************************************************************
Name:            LedFlash          
Description:     LED指示灯闪烁
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void LedFlash(void)
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
Description:     LED指示灯常亮
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void LedOn(void)
{
	GPIO_ResetBits( GPIOC, IO_LED );
}


/*************************************************************
Name:            LedOff         
Description:     LED指示灯熄灭
Input:           void          
Output:          void         
Return:          void         
**************************************************************/
void LedOff(void)
{
	GPIO_SetBits( GPIOC, IO_LED );
}

/*************************************************************
Name:ClrWtd          
Description:喂狗
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
Description:复位时钟芯片 
Input:          
Output:void         
Return:void         
**************************************************************/
void HardResetClkChip(void)
{
#if 1
	GPIO_InitTypeDef gpio_ad9524_sp = 
		{GPIO_Pin_14|GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_Out_PP};
		
	// SP0和SP1配置为输出模式
	GPIO_Init( GPIOA, &gpio_ad9524_sp );	
	// SP0和SP1配置为低电平，进入SPI模式
	GPIO_ResetBits( GPIOA, GPIO_Pin_14);
	GPIO_ResetBits( GPIOA, GPIO_Pin_15);
	// 拉低复位脚
	GPIO_ResetBits( GPIOB, GPIO_Pin_5);
	UsNopDelay(1000);
	// 拉高复位脚
	GPIO_SetBits( GPIOB, GPIO_Pin_5); 
	UsNopDelay(10); 
	// SP0和SP1恢复为上拉输入模式，用于锁定检测
	gpio_ad9524_sp.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init( GPIOA, &gpio_ad9524_sp );
#endif

}  






/*************************************************************
Name:EnableModulatorB          
Description:控制B段调制器使能
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
Name:Hmc1197CsEnalbe
Description:HMC1197片选使能   enable 0:禁能，1:使能
Input:片选
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





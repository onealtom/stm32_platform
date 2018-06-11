/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司

*************************************************************
文件名：   SPI_DRV_C_
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： SPI_DRV_C_的底层驱动文件 
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

SPI_InitTypeDef  SPI_InitStructure;
extern UINT16 fpga_wo_reg[];

//extern UINT16 fpga_write_bak[FPGA_W_REG_MAX];

/*************************************************************
Name:	      SpiCsEnable          
Description: 使能SPI片选
Input:	      chip_sel: 
	             SPI_CS_AT45,
	             SPI_CS_AD9524,
	             SPI_CS_6643, 
	             SPI_CS_AD9122_A, 
	             SPI_CS_AD9122_B
Return: 	void
**************************************************************/
void SpiCsEnable( UINT16 chip_sel )
{  
	switch( chip_sel ) 
	{ 
		case SPI_CS_AT45:
			GPIO_ResetBits( GPIOB, GPIO_Pin_12 );
			break; 
			
		case SPI_CS_AD9524:
			GPIO_ResetBits( GPIOB, GPIO_Pin_6 );
			break;
			
		case SPI_CS_AD6643:
//			GPIO_ResetBits( GPIOB, GPIO_Pin_6 );
			
			break; 
			
		case SPI_CS_AD9122_A:
			GPIO_ResetBits( GPIOC, GPIO_Pin_14 );
			break;
			
		case SPI_CS_AD9122_B:
			GPIO_ResetBits( GPIOC, GPIO_Pin_15 ); 
		break;
	}

}


/*************************************************************
Name:	      SpiCsEnable          
Description: 失能SPI片选
Input:	      chip_sel: 
	             SPI_CS_AT45,
	             SPI_CS_AD9524,
	             SPI_CS_6643, 
	             SPI_CS_AD9122_A, 
	             SPI_CS_AD9122_B
Return: 	void
**************************************************************/
void SpiCsDisable( UINT16 chip_sel )
{
	switch( chip_sel )
	{
		case SPI_CS_AT45:
			GPIO_SetBits( GPIOB, GPIO_Pin_12 );
		break;
			
		case SPI_CS_AD9524: 
			GPIO_SetBits( GPIOB, GPIO_Pin_6 );
		break;
			
		case SPI_CS_AD6643:
//			GPIO_SetBits( GPIOB, GPIO_Pin_6 );
			
		break;
			
		case SPI_CS_AD9122_A:
			GPIO_SetBits( GPIOC, GPIO_Pin_14 ); 
		break;
			 
		case SPI_CS_AD9122_B:
			GPIO_SetBits( GPIOC, GPIO_Pin_15 );
		break;

		case SPI_CS_ALL:
			GPIO_SetBits( GPIOB, GPIO_Pin_12 );
			GPIO_SetBits( GPIOB, GPIO_Pin_6 );
//			GPIO_SetBits( GPIOB, GPIO_Pin_6);
			GPIO_SetBits( GPIOC, GPIO_Pin_14 );
			GPIO_SetBits( GPIOC, GPIO_Pin_15 ); 
		break;
	}
}

/*************************************************************
Name:	      InitSpi          
Description: 初始化SPI2
Input:	void
Return: 	void
**************************************************************/
void InitSpi()
{
	
	SpiCsDisable(SPI_CS_ALL);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		// 2线全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;					// 主机模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					// 8位模式
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;						// 时钟空闲时为低电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;					// 时钟第1个边沿时采样数据
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;						// 软件控制片选信号
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;	// 时钟分频2M
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					// 高位在前
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	//SPI1时钟
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE );
//	SPI_Init(SPI1, &SPI_InitStructure);								// 初始化SPI1

	//SPI2时钟
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );
	SPI_Init(SPI2, &SPI_InitStructure);								// 初始化SPI2
	/* Enable SPI1 */
//	SPI_Cmd(SPI1, ENABLE);

	//DMA1时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

}

/*************************************************************
Name:	           SpiDmaTrans          
Description:      通过DMA传输SPI数据
Input:	dat_size:  数据字节长度		p_buff: 数据指针
Return: 	    void
**************************************************************/
void SpiDmaTrans( UINT16 dat_size, UCHAR8 * p_buff )
{
	UINT16 tx_cnt=0;
	UINT16 wt_us=0;
	DMA_InitTypeDef  DMA_InitStructure;

	/* DMA1 channel4 configuration ---------------------------------------------*/
	DMA_DeInit(DMA1_Channel4);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI2_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)p_buff;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = dat_size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);

	/* SPI1 configuration ------------------------------------------------------*/
//	SPI_Init(SPI1, &SPI_InitStructure);								// 初始化SPI1

//	TRACE_INFO("dat-:%02X %02X %02X\r\n", p_buff[0], p_buff[1], p_buff[2]);

	/* Enable SPI2 Rx request */
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);

	/* Enable SPI1 */
//	SPI_Cmd(SPI1, ENABLE);

//	TRACE_INFO("dat0:%02X %02X %02X\r\n", p_buff[0], p_buff[1], p_buff[2]);

	/* Enable DMA1 Channel4 */
	SPI_I2S_ReceiveData(SPI2);
	DMA_Cmd(DMA1_Channel4, ENABLE);
	
//	TRACE_INFO("dat1:%02X %02X %02X\r\n", p_buff[0], p_buff[1], p_buff[2]);

	/* Transfer procedure */
//	TRACE_INFO("tx:");
	while (tx_cnt < dat_size)
	{
		/* Wait for SPI1 Tx buffer empty */
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		while ( wt_us<100 )
		{
			if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != RESET)
			{
				wt_us = 0;
				break;
			}
			UsNopDelay(1);
			wt_us++;
		}

		/* Send SPI1 data */
		SPI_I2S_SendData(SPI2, p_buff[tx_cnt++]);
	}

	/* Wait for DMA1 channel4 transfer complete */
	//while (RESET==DMA_GetFlagStatus(DMA1_FLAG_TC2));
	wt_us = 0;
	while ( wt_us<100 )
	{
		if (DMA_GetFlagStatus(DMA1_FLAG_TC4) != RESET)
		{
			break;
		}
		UsNopDelay(1);
		wt_us++;
	}
}

/*************************************************************
Name:	       SpiTransDat          
Description: 传输SPI数据,不使用DMA
Input:	      dat_size: 数据字节长度	
             p_buff: 数据指针
Return: 	void
**************************************************************/
void SpiTransDat( UINT16 dat_size, UCHAR8 * p_buff )
{
	UINT16 tx_cnt=0;
	UINT16 wt_us=0;

	SPI_I2S_ReceiveData(SPI2);

	while( tx_cnt<dat_size)
	{
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		while ( wt_us<100 )
		{
			if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != RESET)
			{
				wt_us = 0;
				break;
			}
			UsNopDelay(1);
			wt_us++;
		}

		SPI_I2S_SendData(SPI2, p_buff[tx_cnt]);
		
             //TRACE_INFO_WP("write to  is %02x\r\n",p_buff[tx_cnt]);  
		
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		while ( wt_us<100 )  
		{
			if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) != RESET)
			{
				break;
			}
			UsNopDelay(1); 
			wt_us++;
		}
		
		p_buff[tx_cnt] = SPI_I2S_ReceiveData(SPI2);  
		//TRACE_INFO_WP("read from is %02x\r\n",p_buff[tx_cnt]);  
//		TRACE_INFO_WP(" r%02X", p_buff[tx_cnt]); 
		
		tx_cnt++;
	}

//	TRACE_INFO_WP("\r\n");
	//SPI_Cmd(SPI1, DISABLE);

}
/*************************************************************
Name:	            spi_dma_rw_buffer          
Description:      SPI读写数据
Input:	           
                 p_cmd_buf: 命令数据指针		
                 cmd_len: 命令数据长度		
                 p_data_buf: 可选附加参数指针
                 data_len: 可选附加参数长度
Return: 	   void
**************************************************************/
void spi_dma_rw_buffer(UCHAR8 *p_cmd_buf, UINT16 cmd_len,UCHAR8 *p_data_buf, UINT16 data_len)
{

	//SpiDmaTrans( cmd_len, p_cmd_buf );
	SpiTransDat( cmd_len, p_cmd_buf );
	if ( p_data_buf!=NULL )
	{
		if ( data_len>20 )
		{
			SpiDmaTrans( data_len, p_data_buf );
			return; 
		}

		if ( data_len>0 )
		{
			SpiTransDat( data_len, p_data_buf );
			return;
		}
	}
	
}

/*************************************************************
Name:SpiWriteBuf          
Description:SPI写buffer
Input:片选,buffer,len
Output:void         
Return:void         
**************************************************************/
UCHAR8 SpiWriteBuf(UINT16 npcs, UCHAR8 * p_cmd_buf,UINT16 cmd_len,UCHAR8 * p_data_buf,UINT16 data_len)
{
//	printf(" spiw");
	SPI_Cmd(SPI2, ENABLE);
	SpiCsEnable(npcs);
	spi_dma_rw_buffer(p_cmd_buf,cmd_len,p_data_buf,data_len);
	SpiCsDisable(npcs);
	SPI_Cmd(SPI2, DISABLE);
	return 1;
}

/*************************************************************
Name:SpiReadBuf
Description:SPI读buffer
Input:片选,buffer,len
Output:void         
Return:void         
**************************************************************/
UCHAR8 SpiReadBuf(UINT16 npcs, UCHAR8 * p_cmd_buf,UINT16 cmd_len,UCHAR8 * p_data_buf,UINT16 data_len)
{	
//	printf(" spir");
	SPI_Cmd(SPI2, ENABLE);
	SpiCsEnable(npcs);
	spi_dma_rw_buffer(p_cmd_buf,cmd_len,p_data_buf,data_len);
	SpiCsDisable(npcs);
	SPI_Cmd(SPI2, DISABLE);
	return 1;
}
/*************************************************************
Name  :        SpiDatOutputMode
Description:   设置为输出模式
Input:         void 
Output:        void         
Return:        void         
**************************************************************/
void SpiDatOutputMode()
{
//	GPIO_InitTypeDef gpio_spi_dat = PINS_AD6643_SPI_DO;
	
	//GPIO_Init( GPIOB, &gpio_spi_dat ); 
}


/*************************************************************
Name  :        SpiDatInputMode
Description:   设置为输入模式
Input:         void 
Output:        void         
Return:        void         
**************************************************************/
void SpiDatInputMode()
{
//	GPIO_InitTypeDef gpio_spi_dat = PINS_AD6643_SPI_DI;
	
	//GPIO_Init( GPIOB, &gpio_spi_dat );  
}

/*************************************************************
Name:SdioSpiWriteByte          
Description:GPIO模拟的SPI写字节
Input:地址数据data            
Output:void         
Return:void
**************************************************************/
void SdioSpiWriteByte(UINT16 add,UCHAR8  data)
{
	UINT16 tmp;
	UCHAR8 i;

	add &= 0x1fff; 								//write one byte
}

/*************************************************************
Name:SdioSpiReadByte          
Description:GPIO模拟的SPI读字节
Input:add            
Output:void         
Return:读到的数据
**************************************************************/
UCHAR8 SdioSpiReadByte(UINT16 add)
{
	UINT16 tmp;
	UCHAR8 reg_dat;
	UCHAR8 i; 


	add = (add&0x1fff)|0x8000; 				//read one byte

	return reg_dat;	 

}



/*************************************************************
Name:Hmc830CsEnalbe
Description:HMC830片选使能
Input:片选
Output:void         
Return:void   
**************************************************************/
void Hmc830CsEnalbe(UCHAR8 npcs)
{
 	
	
}

/*************************************************************
Name:Hmc830CsDisable
Description:HMC830片选禁能
Input:片选
Output:void         
Return:void   
**************************************************************/
void Hmc830CsDisable(UCHAR8 npcs)
{
	
}


/*************************************************************
Name:Hmc830OutputEnalbe
Description:HMC830工作使能
Input:片选
Output:void         
Return:void   
**************************************************************/
void Hmc830OutputEnalbe(UCHAR8 npcs)
{

	
	
}

/*************************************************************
Name:Hmc830OutputDisable
Description:HMC830工作禁能
Input:片选
Output:void         
Return:void   
**************************************************************/
void Hmc830OutputDisable(UCHAR8 npcs)
{
	
	
}


/*************************************************************
Name: SetHmc830Mode
Description: 配置830的SPI模式
Input:void
Output:void         
Return:void   
**************************************************************/
void SetHmc830Mode(void)
{

}


/*************************************************************
Name:ReadWriteHmc830
Description:HMC830读写函数
Input:片选，读写标志:1读，0写，地址，数据
Output:void         
Return:void   
**************************************************************/
UINT32 ReadWriteHmc830(UCHAR8 npcs, UCHAR8 read_wirte_flag,UCHAR8 add, UINT32 data) 
{

}


/*************************************************************
Name:WriteHmc1197
Description:HMC1197写函数
Input:地址，数据
Output:void         
Return:void   
**************************************************************/
UINT32 WriteHmc1197(UCHAR8 add, UINT32 data) 
{

}

/*************************************************************
Name:ReadHmc1197
Description:HMC1197读函数
Input:地址，数据
Output:void         
Return:读回的32位数据   
**************************************************************/
UINT32 ReadHmc1197(UCHAR8 add) 
{

}




/*************************************************************
Name           :IsPllLocked
Description    判断指定的830是否锁定
Input:         ucDev-指定的器件
Output:        void         
Return:        1 - 锁定 
               0-  失锁 
**************************************************************/
BOOL IsPllLocked(UCHAR8 ucDev)
{
	UINT32 LockReg; 
	UINT32 IdReg;
	
    BOOL flag = 0; 
	
	FPGA_ENABLE_WRITE;
	LockReg = ReadWriteHmc830(ucDev,1,HMC830_GPO2_12,0x0000);
	//TRACE_INFO("LockReg = %d\r\n",LockReg);
	IdReg =   ReadWriteHmc830(ucDev,1,HMC830_ID_00,0x0000);  
	//TRACE_INFO("IdReg = %d\r\n",IdReg); 
	FPGA_DISABLE_WRITE;  
  
    if ( (HMC830_ID == IdReg)&&(HMC830_LCKED == (LockReg&HMC830_LCKED)) )
    {    
       flag = 1;  
    } 
    else
    {
       flag = 0; 
    }
	
	return flag;   
}

void GetPllStatus(void)
{

}
/*************************************************************
Name:TFInit
Description:初始化IO
Input:片选
Output:void         
Return:void   
**************************************************************/
void TFInit(void)
{
	UINT16 reg_add,fpga_data;

	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,BIT_9363_SPI_A_EN|BIT_9363_SPI_B_EN);
	FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_C,BIT_9363_SPI_C_EN);
	UsNopDelay(10);

	//RESET
	fpga_data=fpga_wo_reg[FPGA_REG_W_9363_SPI_DO_A_B&0XFF];
	fpga_data&=~(BIT_9363_A_RESET|BIT_9363_B_RESET);
	FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,fpga_data);
	
	fpga_data=fpga_wo_reg[FPGA_REG_W_9363_SPI_DO_C&0XFF];
	fpga_data&=~(BIT_9363_C_RESET);
	FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_C,fpga_data);	
	UsNopDelay(20);
	
	fpga_data=fpga_wo_reg[FPGA_REG_W_9363_SPI_DO_A_B&0XFF];
	fpga_data|=(BIT_9363_A_RESET|BIT_9363_B_RESET);
	FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,fpga_data);
	
	fpga_data=fpga_wo_reg[FPGA_REG_W_9363_SPI_DO_C&0XFF];
	fpga_data|=(BIT_9363_C_RESET);
	FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_C,fpga_data);
	FPGA_DISABLE_WRITE;

	if(AD9369)
	{
		ReadWriteTF(TF_C,1,0x00,0x18);
	}	
		
	UsNopDelay(20);
}
/*************************************************************
Name:TFInit
Description:初始化IO
Input:片选
Output:void         
Return:void   
**************************************************************/
void TFInitCs(UCHAR8 npcs)
{
	UINT16 reg_add,fpga_data;

	FPGA_ENABLE_WRITE;
	if (npcs == TF_A)
	{
		fpga_data=fpga_wo_reg[FPGA_REG_W_9363_SPI_DO_A_B&0XFF];
		fpga_data|=(BIT_9363_SPI_A_EN);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,fpga_data);
		UsNopDelay(10);
		//RESET
		fpga_data&=~(BIT_9363_A_RESET);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,fpga_data);
		UsNopDelay(20);
		fpga_data|=(BIT_9363_A_RESET);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,fpga_data);
	
		UsNopDelay(20);
	}
	else if(npcs == TF_B)
	{
		fpga_data=fpga_wo_reg[FPGA_REG_W_9363_SPI_DO_A_B&0XFF];
		fpga_data|=(BIT_9363_SPI_B_EN);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,fpga_data);
		UsNopDelay(10);
		//RESET
		fpga_data&=~(BIT_9363_B_RESET);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,fpga_data);
		UsNopDelay(20);
		fpga_data|=(BIT_9363_B_RESET);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_A_B,fpga_data);
	}
	else if(npcs == TF_C)
	{
		fpga_data=fpga_wo_reg[FPGA_REG_W_9363_SPI_DO_C&0XFF];
		fpga_data|=(BIT_9363_SPI_C_EN);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_C,fpga_data);
		UsNopDelay(10);
		//RESET
		fpga_data&=~(BIT_9363_C_RESET);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_C,fpga_data);
		UsNopDelay(20);
		fpga_data|=(BIT_9363_C_RESET);
		FpgaWriteRegister(FPGA_REG_W_9363_SPI_DO_C,fpga_data);

		if(AD9369)
		{
			ReadWriteTF(TF_C,1,0x00,0x18);
		}
	
	}	
	FPGA_DISABLE_WRITE;
}
/*************************************************************
Name:TFCsEnalbe
Description:收发器芯片选使能
Input:片选
Output:void         
Return:void   
**************************************************************/
void TFCsEnable(UCHAR8 npcs)
{
	UINT16 reg_add,fpga_data;
		
	if (npcs == TF_A)
	{
		reg_add = FPGA_REG_W_9363_SPI_DO_A_B;
		fpga_data = fpga_wo_reg[reg_add&0XFF];
		fpga_data &= ~(BIT_9363_SPI_A_DO|BIT_9363_SPI_A_CLK|BIT_9363_SPI_A_EN);	//ENB,CLK,DI LOW
	}
	else if (npcs == TF_B)
	{
		reg_add = FPGA_REG_W_9363_SPI_DO_A_B;
		fpga_data = fpga_wo_reg[reg_add&0XFF];
		fpga_data &= ~(BIT_9363_SPI_B_DO|BIT_9363_SPI_B_CLK|BIT_9363_SPI_B_EN);	//ENB,CLK,DI LOW
	}
	else if (npcs == TF_C)
	{
		reg_add = FPGA_REG_W_9363_SPI_DO_C;
		fpga_data = fpga_wo_reg[reg_add&0XFF];
		fpga_data &= ~(BIT_9363_SPI_C_DO|BIT_9363_SPI_C_CLK|BIT_9363_SPI_C_EN);	//ENB,CLK,DI LOW
	}
	else if (npcs == TF_D)
	{
		reg_add = FPGA_REG_W_9363_SPI_DO_C;
		fpga_data = fpga_wo_reg[reg_add&0XFF];
		fpga_data &= ~(BIT_9363_SPI_C_DO|BIT_9363_SPI_C_CLK|BIT_9363_SPI_C_EN);	//ENB,CLK,DI LOW
	}
	else 
		return ;
	
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(reg_add,fpga_data);
	FPGA_ENABLE_WRITE;
	UsNopDelay(20);
	
}
/*************************************************************
Name:TFCsDiable
Description:收发器芯片选禁能
Input:片选
Output:void         
Return:void   
**************************************************************/
void TFCsDiable(UCHAR8 npcs)
{
	UINT16 reg_add,fpga_data;
	
	
	if (npcs == TF_A)
	{
		reg_add = FPGA_REG_W_9363_SPI_DO_A_B;
		fpga_data = fpga_wo_reg[reg_add&0XFF];	
		fpga_data &= (~(BIT_9363_SPI_A_DO|BIT_9363_SPI_A_CLK));
		fpga_data |= (BIT_9363_SPI_A_EN);				//ENB HIGH,CLK,DI LOW
	}
	else if (npcs == TF_B)
	{
		reg_add = FPGA_REG_W_9363_SPI_DO_A_B;
		fpga_data = fpga_wo_reg[reg_add&0XFF];
		fpga_data &= (~(BIT_9363_SPI_B_DO|BIT_9363_SPI_B_CLK));
		fpga_data |= (BIT_9363_SPI_B_EN);				//ENB HIGH,CLK,DI LOW
	}
	else if (npcs == TF_C)
	{
		reg_add = FPGA_REG_W_9363_SPI_DO_C;
		fpga_data = fpga_wo_reg[reg_add&0XFF];
		fpga_data &= (~(BIT_9363_SPI_C_DO|BIT_9363_SPI_C_CLK));
		fpga_data |= (BIT_9363_SPI_C_EN);				//ENB HIGH,CLK,DI LOW	
	}
	else if (npcs == TF_D)
	{
		reg_add = FPGA_REG_W_9363_SPI_DO_C;
		fpga_data = fpga_wo_reg[reg_add&0XFF];
		fpga_data &= (~(BIT_9363_SPI_C_DO|BIT_9363_SPI_C_CLK));
		fpga_data |= (BIT_9363_SPI_C_EN);				//ENB HIGH,CLK,DI LOW	
	}
	else 
		return ;
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(reg_add,fpga_data);
	FPGA_DISABLE_WRITE;
	UsNopDelay(20);
}


/*************************************************************
Name:ReadWriteTF
Description:收发器芯片读写函数
Input:片选，读写标志:0读，1写，地址，数据
Output:void         
Return:void   
**************************************************************/
UCHAR8 ReadWriteTF(UCHAR8 npcs, UCHAR8 read_wirte_flag,UINT16  add, UCHAR8 data) 
{
	
	return 0;
}


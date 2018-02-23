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
extern UCHAR8 ucPllStatus;
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
#if 0
	/* DMA1 channel4 configuration ---------------------------------------------*/
	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI1_DR_Address;
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
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);

	/* SPI1 configuration ------------------------------------------------------*/
//	SPI_Init(SPI1, &SPI_InitStructure);								// 初始化SPI1

//	TRACE_INFO("dat-:%02X %02X %02X\r\n", p_buff[0], p_buff[1], p_buff[2]);

	/* Enable SPI2 Rx request */
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);

	/* Enable SPI1 */
//	SPI_Cmd(SPI1, ENABLE);

//	TRACE_INFO("dat0:%02X %02X %02X\r\n", p_buff[0], p_buff[1], p_buff[2]);

	/* Enable DMA1 Channel4 */
	SPI_I2S_ReceiveData(SPI1);
	DMA_Cmd(DMA1_Channel2, ENABLE);
	
//	TRACE_INFO("dat1:%02X %02X %02X\r\n", p_buff[0], p_buff[1], p_buff[2]);

	/* Transfer procedure */
//	TRACE_INFO("tx:");
	while (tx_cnt < dat_size)
	{
		/* Wait for SPI1 Tx buffer empty */
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		while ( wt_us<100 )
		{
			if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != RESET)
			{
				wt_us = 0;
				break;
			}
			UsNopDelay(1);
			wt_us++;
		}

		/* Send SPI1 data */
		SPI_I2S_SendData(SPI1, p_buff[tx_cnt++]);
	}

	/* Wait for DMA1 channel4 transfer complete */
	//while (RESET==DMA_GetFlagStatus(DMA1_FLAG_TC2));
	wt_us = 0;
	while ( wt_us<100 )
	{
		if (DMA_GetFlagStatus(DMA1_FLAG_TC2) != RESET)
		{
			break;
		}
		UsNopDelay(1);
		wt_us++;
	}
#endif 	
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
#if 0
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

	SPI_I2S_ReceiveData(SPI1);

	while( tx_cnt<dat_size)
	{
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		while ( wt_us<100 )
		{
			if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != RESET)
			{
				wt_us = 0;
				break;
			}
			UsNopDelay(1);
			wt_us++;
		}

		SPI_I2S_SendData(SPI1, p_buff[tx_cnt]);
		
             //TRACE_INFO_WP("write to  is %02x\r\n",p_buff[tx_cnt]);  
		
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		while ( wt_us<100 )  
		{
			if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != RESET)
			{
				break;
			}
			UsNopDelay(1); 
			wt_us++;
		}
		
		p_buff[tx_cnt] = SPI_I2S_ReceiveData(SPI1);  
		//TRACE_INFO_WP("read from is %02x\r\n",p_buff[tx_cnt]);  
//		TRACE_INFO_WP(" r%02X", p_buff[tx_cnt]); 
		
		tx_cnt++;
	}

//	TRACE_INFO_WP("\r\n");
	//SPI_Cmd(SPI1, DISABLE);

}
#endif 
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

#if 0
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
	SPI_Cmd(SPI1, ENABLE);
	SpiCsEnable(npcs);
	spi_dma_rw_buffer(p_cmd_buf,cmd_len,p_data_buf,data_len);
	SpiCsDisable(npcs);
	SPI_Cmd(SPI1, DISABLE);
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
	SPI_Cmd(SPI1, ENABLE);
	SpiCsEnable(npcs);
	spi_dma_rw_buffer(p_cmd_buf,cmd_len,p_data_buf,data_len);
	SpiCsDisable(npcs);
	SPI_Cmd(SPI1, DISABLE);
	return 1;
}
#endif 
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

#if 0
	SpiDatOutputMode();				                   //set sdio output
	
	CLR_SDIO_CLK_PIN;						    //set sdio,clk low	

	tmp = add;
	
	for (i=0; i<16; i++)
	{
		if ( 0x8000 == (tmp&0x8000) )
		{

			//201311111223 SET_SDIO_DAT_PIN;
		} 
		else 
		{

			CLR_SDIO_DAT_PIN;
		}
		UsNopDelay(10);

		SET_SDIO_CLK_PIN;				//clk high
		UsNopDelay(10);
		
		CLR_SDIO_CLK_PIN;				//clk low
		tmp <<= 1;
	}


	tmp = data;
	for (i=0; i<8; i++)
	{
		if ( 0x80 == (tmp&0x80) )
		{
			//201311111223 SET_SDIO_DAT_PIN;

		}
		else
		{
			CLR_SDIO_DAT_PIN;

		}
		UsNopDelay(10);
		
		SET_SDIO_CLK_PIN;				//clk high
		UsNopDelay(10);
		
		CLR_SDIO_CLK_PIN;				//clk low
		tmp <<= 1;
	}
#endif 
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

#if 0	
	SpiDatOutputMode();						//set sdio output
	CLR_SDIO_CLK_PIN;						//set sdio,clk low	
	UsNopDelay(5);
	
	tmp = add;
	for (i=0; i<16; i++)
	{
		if ( 0x8000 == (tmp&0x8000) )
		{
		//201311111223	SET_SDIO_DAT_PIN;

		}
		else
		{
			//CLR_SDIO_DAT_PIN;

		}
		tmp <<= 1;
		UsNopDelay(5);
		SET_SDIO_CLK_PIN;							//clk high上沿送数据				
		UsNopDelay(5);
		CLR_SDIO_CLK_PIN;						//clk low		
	}
	
	SpiDatInputMode();					//set sdio input		
	UsNopDelay(5);
	reg_dat = 0;
	for (i=0; i<8; i++)
	{
		reg_dat <<= 1;
		if (1==GET_SDIO_DAT_PIN)						//read bit
		{
			reg_dat |= 0x01;
		}
		else
		{

		}
		SET_SDIO_CLK_PIN;							//clk high	
		UsNopDelay(5);
		CLR_SDIO_CLK_PIN;						//clk low			
		UsNopDelay(5);
	}	
#endif 
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
	UINT16 reg_add,fpga_data,cs_bit;

	if (npcs == PLL_R)
	{
		reg_add = FPGA_REG_W_A_PLL;
		cs_bit = BIT_R_L_PLL_CS;

	}
	else if (npcs == PLL_A)
	{
		reg_add = FPGA_REG_W_A_PLL;
		cs_bit = BIT_A_B_PLL_CS;
	}
	else if (npcs == PLL_B)
	{
		reg_add = FPGA_REG_W_B_PLL;
		cs_bit = BIT_A_B_PLL_CS;
	}
	else if (npcs == PLL_L)
	{
		reg_add = FPGA_REG_W_B_PLL;
		cs_bit = BIT_R_L_PLL_CS;

	}
	else 
		return ;

	fpga_data = FpgaReadRegister(reg_add);
	fpga_data |= cs_bit;	
	FpgaWriteRegister(reg_add,fpga_data);	 	
	
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
	UINT16 reg_add,fpga_data,cs_bit;

	if (npcs == PLL_R)
	{
		reg_add = FPGA_REG_W_A_PLL;
		cs_bit = BIT_R_L_PLL_CS;
	}
	else if (npcs == PLL_A)
	{
		reg_add = FPGA_REG_W_A_PLL;
		cs_bit = BIT_A_B_PLL_CS;
	}
	else if (npcs == PLL_B)
	{
		reg_add = FPGA_REG_W_B_PLL;
		cs_bit = BIT_A_B_PLL_CS;
	}
	else if (npcs == PLL_L)
	{
		reg_add = FPGA_REG_W_B_PLL;
		cs_bit = BIT_R_L_PLL_CS;
	}
	else 
		return ;

	fpga_data = FpgaReadRegister(reg_add);
	fpga_data &= ~cs_bit;
	FpgaWriteRegister(reg_add,fpga_data);		
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
	UINT16 reg_add,fpga_data,en_bit;

	if (npcs == PLL_R)
	{
		reg_add = FPGA_REG_W_B_PLL;
		en_bit = BIT_R_L_PLL_EN;
	}
	else if (npcs == PLL_A)
	{
		reg_add = FPGA_REG_W_A_PLL;
		en_bit = BIT_A_B_PLL_EN;
	}
	else if (npcs == PLL_B)
	{
		reg_add = FPGA_REG_W_B_PLL;
		en_bit = BIT_A_B_PLL_EN;
	}
	else if (npcs == PLL_L)
	{
		reg_add = FPGA_REG_W_A_PLL;
		en_bit = BIT_R_L_PLL_EN;
	}
	else 
		return ;


	fpga_data = FpgaReadRegister(reg_add);
	fpga_data |= en_bit;	
	FpgaWriteRegister(reg_add,fpga_data);	
	
	
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
	UINT16 reg_add,fpga_data,en_bit;

	if (npcs == PLL_R)
	{
		reg_add = FPGA_REG_W_B_PLL;
		en_bit = BIT_R_L_PLL_EN;
	}
	else if (npcs == PLL_A)
	{
		reg_add = FPGA_REG_W_A_PLL;
		en_bit = BIT_A_B_PLL_EN;
	}
	else if (npcs == PLL_B)
	{
		reg_add = FPGA_REG_W_B_PLL;
		en_bit = BIT_A_B_PLL_EN;
	}
	else if (npcs == PLL_L)
	{
		reg_add = FPGA_REG_W_A_PLL;
		en_bit = BIT_R_L_PLL_EN;
	}
	else 
		return ;

	fpga_data = FpgaReadRegister(reg_add);
	fpga_data &= ~en_bit;
	FpgaWriteRegister(reg_add,fpga_data);		
	
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
	UINT16 fpga_data;

	FPGA_ENABLE_WRITE;
	
	// 先拉高CS, 其他线保持低
	fpga_data = BIT_R_L_PLL_CS|BIT_A_B_PLL_CS;
	FpgaWriteRegister( FPGA_REG_W_A_PLL, fpga_data );
	FpgaWriteRegister( FPGA_REG_W_B_PLL, fpga_data );
	UsNopDelay( 100 );
	// 后拉高CLK, 确定SPI的模式
	fpga_data |= BIT_PLL_CLK;
	FpgaWriteRegister( FPGA_REG_W_A_PLL, fpga_data );
	FpgaWriteRegister( FPGA_REG_W_B_PLL, fpga_data );
	UsNopDelay( 100 );
	// 全部数据线拉低，还原
	FpgaWriteRegister( FPGA_REG_W_A_PLL, 0 );
	FpgaWriteRegister( FPGA_REG_W_B_PLL, 0 );
	
	FPGA_DISABLE_WRITE;  
	
	UsNopDelay(10000);
	
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
	UINT16 clk_bit,sdo_bit,sdi_bit;
	UINT16 reg_add;
	CHAR8 i;
	UINT16 fpga_data;
	UINT32 read_data = 0;
	
#if 1	// >>RJ 2012-10-29 若寄存器值为0xFAAAFFFF则忽略设置，表示使用默认值
	if ( 0xFAAAFFFF==data ) return data;
#endif

	if (npcs == PLL_R)
	{
		reg_add = FPGA_REG_W_A_PLL;
		clk_bit = BIT_PLL_CLK;
		sdo_bit = BIT_PLL_SDO;
		sdi_bit = PLL_B_R_PLL_SDI;

	}
	else if (npcs == PLL_A)
	{
		reg_add = FPGA_REG_W_B_PLL;
		clk_bit = BIT_PLL_CLK;
		sdo_bit = BIT_PLL_SDO;
		sdi_bit = PLL_A_L_PLL_SDI;
	}
	else if (npcs == PLL_B)
	{
		reg_add = FPGA_REG_W_A_PLL;
		clk_bit = BIT_PLL_CLK;
		sdo_bit = BIT_PLL_SDO;
		sdi_bit = PLL_B_R_PLL_SDI;
	}
	else if (npcs == PLL_L)
	{
		reg_add = FPGA_REG_W_B_PLL;
		clk_bit = BIT_PLL_CLK;
		sdo_bit = BIT_PLL_SDO;
		sdi_bit = PLL_A_L_PLL_SDI;
	}		
	else 
		return 0;

	
	//组合数据
	data = ((((add&0x3f)|(read_wirte_flag<<6))<<24)&0xff000000)|(data&0x00ffffff);


	//cs high	
	Hmc830CsEnalbe(npcs);
	UsNopDelay(10);

	// clk low

	fpga_data = FpgaReadRegister(reg_add);
	fpga_data &= ~clk_bit;
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(reg_add,fpga_data);
	FPGA_DISABLE_WRITE;
	for (i=30; i>=0; i--)
	{
		//下延写数据
		if ((data>>i)&0x00000001)
			fpga_data |= sdo_bit;
		else
			fpga_data &= ~sdo_bit;
		fpga_data &= ~clk_bit;
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(reg_add,fpga_data);
		FPGA_DISABLE_WRITE;
		UsNopDelay(10);	

		//CLK拉高锁存数据
		fpga_data |= clk_bit;
		FpgaWriteRegister(reg_add,fpga_data);		
		UsNopDelay(10);
		
		fpga_data &= ~clk_bit;
		FpgaWriteRegister(reg_add,fpga_data);

		//读操作时下延读取数据
		if (read_wirte_flag && (i<=23))
		{
			if (FpgaReadRegister(FPGA_REG_R_PLL_CLK)&(0x01<<sdi_bit))
				read_data |= (0x01<<i);
		}
	}

	UsNopDelay(10);
	//clk high
	fpga_data = FpgaReadRegister(reg_add);
	fpga_data |= clk_bit;
	FpgaWriteRegister(reg_add,fpga_data);	
	UsNopDelay(10);
	
	//cs low
	Hmc830CsDisable(npcs);
	UsNopDelay(10);
	
	//clk low
	fpga_data = FpgaReadRegister(reg_add);
	fpga_data &= ~clk_bit;
	FpgaWriteRegister(reg_add,fpga_data);		
	UsNopDelay(10);
	
	//cs high
	Hmc830CsEnalbe(npcs);
	UsNopDelay(10);

	//cs low
	Hmc830CsDisable(npcs);
	UsNopDelay(10);

	return read_data;
}
#if 0
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
//		fpga_data |= BIT_HMC_CS;
		
	}else{
//		fpga_data &= ~BIT_HMC_CS;

	}
//	FPGA_ENABLE_WRITE;
//	FpgaWriteRegister(FPGA_REG_W_HMC_A_PLL,fpga_data);	
//	FPGA_DISABLE_WRITE;
	UsNopDelay(10);	
}
#endif

/*************************************************************
Name:WriteHmc1197
Description:HMC1197写函数
Input:地址，数据
Output:void         
Return:void   
**************************************************************/
UINT32 WriteHmc1197(UCHAR8 add, UINT32 data) 
{
	UINT16 clk_bit,sdo_bit,sdi_bit,cs_bit;
	UINT16 reg_add;
	CHAR8 i;
	UINT16 fpga_data;
	UINT32 read_data = 0;
	
	reg_add = FPGA_REG_W_HMC_A_PLL;
	clk_bit = BIT_HMC_SPI_CLK;
	sdo_bit = BIT_HMC_SPI_SDO;
	cs_bit  = BIT_HMC_SPI_CS;

	add&=0X1F;
	
	data=((data<<8)|(add<<3)|(0x00));
#if 0	
	Hmc1197CsEnalbe(0);
	UsNopDelay(1);
	FPGA_ENABLE_WRITE;	
	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	fpga_data &= ~clk_bit;
	FpgaWriteRegister(reg_add,fpga_data);
	UsNopDelay(1);

	fpga_data |= clk_bit;
	FpgaWriteRegister(reg_add,fpga_data);
	UsNopDelay(1);
	FPGA_DISABLE_WRITE;
#endif	
//	Hmc1197CsEnalbe(1);
	UsNopDelay(1);
	
	FPGA_ENABLE_WRITE;
	//spi_cs 	
	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	fpga_data &= ~cs_bit;
	FpgaWriteRegister(reg_add,fpga_data);
	UsNopDelay(1);
	

	for (i=31; i>=0; i--)
	{
		//CLK拉低
		fpga_data &= ~clk_bit;
		FpgaWriteRegister(reg_add,fpga_data);
		UsNopDelay(1);	
		
		fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
		//下延写数据
		if ((data>>i)&0x00000001)
			fpga_data |= sdo_bit;
		else
			fpga_data &= ~sdo_bit;
		FpgaWriteRegister(reg_add,fpga_data);
		UsNopDelay(1);

		//CLK拉高
		fpga_data |= clk_bit;
		FpgaWriteRegister(reg_add,fpga_data);		
		UsNopDelay(1);
		
	}
		//spi_cs 	
	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	fpga_data |= cs_bit;
	FpgaWriteRegister(reg_add,fpga_data);
	UsNopDelay(1);
	FPGA_DISABLE_WRITE;
	
//	Hmc1197CsEnalbe(0);
	UsNopDelay(1);


#if 0
	//组合数据
	data = ((((add&0x3f)|(read_wirte_flag<<6))<<24)&0xff000000)|(data&0x00ffffff);


	//cs high	
	Hmc830CsEnalbe(npcs);
	UsNopDelay(10);

	// clk low
	
	fpga_data = FpgaReadRegister(reg_add);
	fpga_data &= ~clk_bit;
	FpgaWriteRegister(reg_add,fpga_data);

	for (i=30; i>=0; i--)
	{
		//下延写数据
		if ((data>>i)&0x00000001)
			fpga_data |= sdo_bit;
		else
			fpga_data &= ~sdo_bit;
		fpga_data &= ~clk_bit;
		FpgaWriteRegister(reg_add,fpga_data);
		UsNopDelay(10);	

		//CLK拉高锁存数据
		fpga_data |= clk_bit;
		FpgaWriteRegister(reg_add,fpga_data);		
		UsNopDelay(10);
		
		fpga_data &= ~clk_bit;
		FpgaWriteRegister(reg_add,fpga_data);

		//读操作时下延读取数据
		if (read_wirte_flag && (i<=23))
		{
			if (FpgaReadRegister(FPGA_REG_R_PLL_CLK)&(0x01<<sdi_bit))
				read_data |= (0x01<<i);
		}
	}

	UsNopDelay(10);
	//clk high
	fpga_data = FpgaReadRegister(reg_add);
	fpga_data |= clk_bit;
	FpgaWriteRegister(reg_add,fpga_data);	
	UsNopDelay(10);
	
	//cs low
	Hmc830CsDisable(npcs);
	UsNopDelay(10);
	
	//clk low
	fpga_data = FpgaReadRegister(reg_add);
	fpga_data &= ~clk_bit;
	FpgaWriteRegister(reg_add,fpga_data);		
	UsNopDelay(10);
	
	//cs high
	Hmc830CsEnalbe(npcs);
	UsNopDelay(10);

	//cs low
	Hmc830CsDisable(npcs);
	UsNopDelay(10);
#endif 
	return read_data;
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
	UINT32 write_data=0x000000,write_data2=0x000000;
	UINT16 clk_bit,sdo_bit,sdi_bit,cs_bit;
	UINT16 write_reg_add,read_reg_add;
	CHAR8 i;
	UINT16 fpga_data;
	UINT32 read_data = 0;
	
	write_reg_add = FPGA_REG_W_HMC_A_PLL;
	clk_bit = BIT_HMC_SPI_CLK;
	sdo_bit = BIT_HMC_SPI_SDO;
	read_reg_add = FPGA_REG_R_SPI_IN;
	sdi_bit=BIT_HMC_SPI_DI;
	cs_bit  = BIT_HMC_SPI_CS;
	
	//reg_add = FPGA_REG_R_SPI_IN;
	
	add&=0X1F;
	write_data=add;
	write_data=((write_data<<8)|(0x00<<3)|(0x00));
	write_data2=write_data;
//	Hmc1197CsEnalbe(1);
	UsNopDelay(1);
	
	FPGA_ENABLE_WRITE;	
	
	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	fpga_data &= ~cs_bit;
	FpgaWriteRegister(write_reg_add,fpga_data);
	UsNopDelay(1);
	
	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	//CLK拉低
	fpga_data &= ~clk_bit;
	FpgaWriteRegister(write_reg_add,fpga_data);
	UsNopDelay(1);

	for (i=31; i>=0; i--)//first circle
	{
		//CLK拉低
		fpga_data &= ~clk_bit;
		FpgaWriteRegister(write_reg_add,fpga_data);
		UsNopDelay(1);
		
		fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
		//下延写数据
		if ((write_data>>i)&0x00000001)
			fpga_data |= sdo_bit;
		else
			fpga_data &= ~sdo_bit;
		FpgaWriteRegister(write_reg_add,fpga_data);
		UsNopDelay(1);

		//CLK拉高
		fpga_data |= clk_bit;
		//TRACE_INFO("ReadHmc1197---w---high---.i=[%02x],write_reg_add=[%x],fpga_data =[%x]\r\n",i,write_reg_add,fpga_data );		
		FpgaWriteRegister(write_reg_add,fpga_data);		
		UsNopDelay(1);
		
	}	
		//spi_cs 	
	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	fpga_data |= cs_bit;
	FpgaWriteRegister(write_reg_add,fpga_data);
	UsNopDelay(1);
	
	FPGA_DISABLE_WRITE;
		
	FPGA_ENABLE_WRITE;
	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	fpga_data &= ~cs_bit;
	FpgaWriteRegister(write_reg_add,fpga_data);
	UsNopDelay(1);
	
	UsNopDelay(10);
	//CLK拉低
	fpga_data &= ~clk_bit;
	FpgaWriteRegister(write_reg_add,fpga_data);
	UsNopDelay(1);
	
	for (i=31; i>=0; i--)//first circle
	{
		
		fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
		//下延写数据
		if ((write_data2>>i)&0x00000001)
			fpga_data |= sdo_bit;
		else
			fpga_data &= ~sdo_bit;
		FpgaWriteRegister(write_reg_add,fpga_data);
		UsNopDelay(1);
		
		//CLK拉高
		fpga_data |= clk_bit;
		
	//TRACE_INFO("ReadHmc1197---r---high---.i=[%02x],write_reg_add=[%x],fpga_data =[%x]\r\n",i,write_reg_add,fpga_data );		
		
		FpgaWriteRegister(write_reg_add,fpga_data);		
		UsNopDelay(50);

		//CLK拉低
		fpga_data &= ~clk_bit;
		//TRACE_INFO("ReadHmc1197---r---high---.i=[%02x],write_reg_add=[%x],fpga_data =[%x]\r\n",i,write_reg_add,fpga_data );		
		
		FpgaWriteRegister(write_reg_add,fpga_data);
		UsNopDelay(1);

		fpga_data = FpgaReadRegister(FPGA_REG_R_SPI_IN);
		fpga_data &=sdi_bit;
		read_data |= (fpga_data>>3)<<i;
				
	}
		//spi_cs 	
	fpga_data = FpgaReadRegister(FPGA_REG_W_HMC_A_PLL);
	fpga_data |= cs_bit;
	FpgaWriteRegister(write_reg_add,fpga_data);
	UsNopDelay(1);

	fpga_data |= clk_bit;
	//TRACE_INFO("ReadHmc1197---r---high---.i=[%02x],write_reg_add=[%x],fpga_data =[%x]\r\n",i,write_reg_add,fpga_data );		
	FpgaWriteRegister(write_reg_add,fpga_data);		
	UsNopDelay(1);	
	FPGA_DISABLE_WRITE;

	
//	Hmc1197CsEnalbe(0);
	UsNopDelay(1);

	return (read_data>>8);
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

	if (    sys_work_info&SYSTEM_FLAG_MCU_UPDATE
	     || sys_work_info &SYSTEM_FLAG_FPGA_UPDATE
	     || sys_work_info &SYSTEM_FLAG_REMOTE_UPDATE)
	{
	      
		 return;  
	}   
	
	if (IsPllLocked(A_MIXER))
	{
    	ucPllStatus |=  A_DN_PLL_LCK;
    }
    else
    {
       ucPllStatus &=  ~A_DN_PLL_LCK;
    }
    
	if (IsPllLocked(A_MODEN))
	{
    	ucPllStatus |=  A_UP_PLL_LCK;
    }
    else
    {
		ucPllStatus &=  ~A_UP_PLL_LCK;
    }
    
	if (IsPllLocked(B_MIXER)) 
	{
    	ucPllStatus |=  B_DN_PLL_LCK;
    }
    else
    {
		ucPllStatus &=  ~B_DN_PLL_LCK;
    }
    
	if (IsPllLocked(B_MODEN))
	{
    	ucPllStatus |=  B_UP_PLL_LCK;
    }  
    else
    {
		ucPllStatus &=  ~B_UP_PLL_LCK;
    }
    
}
#if 0
/*************************************************************
Name:TFInit
Description:初始化IO
Input:片选
Output:void         
Return:void   
**************************************************************/
void TFInit(void)
{
	FpgaWriteRegister(FPGA_REG_W_A_TF,BIT_TF_EN);
	FpgaWriteRegister(FPGA_REG_W_B_TF,BIT_TF_EN);
	UsNopDelay(10);

	//RESET
	FpgaWriteRegister(FPGA_REG_W_A_TF_RESET,0x00);
	FpgaWriteRegister(FPGA_REG_W_B_TF_RESET,0x00);
	UsNopDelay(20);
	FpgaWriteRegister(FPGA_REG_W_A_TF_RESET,BIT_TF_RESET);
	FpgaWriteRegister(FPGA_REG_W_B_TF_RESET,BIT_TF_RESET);		
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
	if (npcs == TF_A)
	{
		FpgaWriteRegister(FPGA_REG_W_A_TF,BIT_TF_EN);
		UsNopDelay(10);
		//RESET
		FpgaWriteRegister(FPGA_REG_W_A_TF_RESET,0x00);
		UsNopDelay(20);
		FpgaWriteRegister(FPGA_REG_W_A_TF_RESET,BIT_TF_RESET);
	
		UsNopDelay(20);
	}
	else
	{
		FpgaWriteRegister(FPGA_REG_W_B_TF,BIT_TF_EN);
		UsNopDelay(10);

		//RESET
		FpgaWriteRegister(FPGA_REG_W_B_TF_RESET,0x00);
		UsNopDelay(20);

		FpgaWriteRegister(FPGA_REG_W_B_TF_RESET,BIT_TF_RESET);		
		UsNopDelay(20);
	}

}
#endif 

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
	UINT16 cmd_addr;
	UCHAR8 i,read_data=0;	
	UINT16 write_reg_add,fpga_data,read_reg_add,bit_tf_clk,bit_tf_do,bit_tf_di;
	UINT16 spi_control,spi_w_data,spi_r_data,spi_flag;
	UINT16 spi_control_add,spi_w_data_add,spi_r_data_add;

	if((AD9369)&&(TF_C==npcs)	)
	{
		read_wirte_flag=1-read_wirte_flag;
		cmd_addr = ((read_wirte_flag==1)<<15)|(add&0x07ff);
	

		write_reg_add 	= FPGA_REG_W_9363_SPI_DO_C;
		read_reg_add 	= FPGA_REG_R_SPI_IN;
		bit_tf_clk	 	= BIT_9363_SPI_C_CLK;
		bit_tf_do   	= BIT_9363_SPI_C_DO;
		bit_tf_di   	= BIT_9363_SPI_C_DI;

		//FPGA控制9363
		spi_control_add = FPGA_REG_C_W_SPI_CONTROL;
		spi_w_data_add = FPGA_REG_C_W_SPI_WRITE_DATA;
		spi_r_data_add = FPGA_REG_C_R_SPI_DATA;

		TFCsEnable(npcs);
	//	fpga_data = fpga_write_bak[write_reg_add];
		fpga_data = fpga_wo_reg[write_reg_add&0XFF];

		FPGA_ENABLE_WRITE;
		//写地址
		//FpgaWriteRegister(FPGA_RE_W_C_9363_CONTROL,0X00);//MCU从FPGA获取9363_C的控制权
		UsNopDelay(15);
		for (i=0; i<16; i++)
		{
			//clk low,锁存数据
			fpga_data &= ~bit_tf_clk;
			FpgaWriteRegister(write_reg_add, fpga_data);	
			UsNopDelay(1);	

			//DO 
			if (cmd_addr&(0x0001<<(15-i)))
				fpga_data |= bit_tf_do;
			else
				fpga_data &= ~bit_tf_do;
			FpgaWriteRegister(write_reg_add, fpga_data);
			UsNopDelay(1);

			//clk high	
			fpga_data |= bit_tf_clk;
			FpgaWriteRegister(write_reg_add, fpga_data);
			UsNopDelay(1);
		}
		FPGA_DISABLE_WRITE;

		//读写数据
		read_data = 0;
		FPGA_ENABLE_WRITE;
		for (i=0; i<8; i++)
		{

			//clk low,锁存数据
			fpga_data &= ~bit_tf_clk;
			FpgaWriteRegister(write_reg_add, fpga_data);
			if(0==read_wirte_flag)
			{
				//DO 
				if (data&(0x0001<<(7-i)))
					fpga_data |= bit_tf_do;
				else
					fpga_data &= ~bit_tf_do;
				FpgaWriteRegister(write_reg_add, fpga_data);
				UsNopDelay(1);
			}
			//clk high	
			fpga_data |= bit_tf_clk;
			FpgaWriteRegister(write_reg_add, fpga_data);
			UsNopDelay(1);		

			if(1==read_wirte_flag)
			{
				UsNopDelay(1);
				if (FpgaReadRegister(read_reg_add)&bit_tf_di)
				read_data |= (1<<(7-i));			
			}
			UsNopDelay(1);
			
		}
		//FpgaWriteRegister(FPGA_RE_W_C_9363_CONTROL,0X01);//MCU释放9363_C的控制权给FPGA
		
		FPGA_DISABLE_WRITE;
	}	
	else
	{
		cmd_addr = ((read_wirte_flag==1)<<15)|(add&0x03ff);
		
		if ((npcs == TF_A))
		{
			write_reg_add	= FPGA_REG_W_9363_SPI_DO_A_B;
			read_reg_add 	= FPGA_REG_R_SPI_IN;
			bit_tf_clk		= BIT_9363_SPI_A_CLK;
			bit_tf_do   	= BIT_9363_SPI_A_DO;
			bit_tf_di   	= BIT_9363_SPI_A_DI;
		}	
		else if (npcs == TF_B)
		{
			write_reg_add 	= FPGA_REG_W_9363_SPI_DO_A_B;
			read_reg_add	= FPGA_REG_R_SPI_IN;
			bit_tf_clk	 	= BIT_9363_SPI_B_CLK;
			bit_tf_do   	= BIT_9363_SPI_B_DO;
			bit_tf_di   	= BIT_9363_SPI_B_DI;

			//FPGA控制9363
			spi_control_add = FPGA_REG_B_W_SPI_CONTROL;
			spi_w_data_add = FPGA_REG_B_W_SPI_WRITE_DATA;
			spi_r_data_add = FPGA_REG_B_R_SPI_DATA;
		}
		else if (npcs == TF_C)
		{
			write_reg_add 	= FPGA_REG_W_9363_SPI_DO_C;
			read_reg_add 	= FPGA_REG_R_SPI_IN;
			bit_tf_clk	 	= BIT_9363_SPI_C_CLK;
			bit_tf_do   	= BIT_9363_SPI_C_DO;
			bit_tf_di   	= BIT_9363_SPI_C_DI;

			//FPGA控制9363
			spi_control_add = FPGA_REG_C_W_SPI_CONTROL;
			spi_w_data_add = FPGA_REG_C_W_SPI_WRITE_DATA;
			spi_r_data_add = FPGA_REG_C_R_SPI_DATA;
		}
		else if (npcs == TF_D)
		{
			write_reg_add 	= FPGA_REG_W_9363_SPI_DO_C;
			read_reg_add 	= FPGA_REG_R_SPI_IN;
			bit_tf_clk	 	= BIT_9363_SPI_C_CLK;
			bit_tf_do   	= BIT_9363_SPI_C_DO;
			bit_tf_di   	= BIT_9363_SPI_C_DI;

			//FPGA控制9363
			spi_control_add = FPGA_REG_C_W_SPI_CONTROL;
			spi_w_data_add = FPGA_REG_C_W_SPI_WRITE_DATA;
			spi_r_data_add = FPGA_REG_C_R_SPI_DATA;
		}	
		else 
			return 0;
			
		TFCsEnable(npcs);
	//	fpga_data = fpga_write_bak[write_reg_add];
		fpga_data = fpga_wo_reg[write_reg_add&0XFF];

		FPGA_ENABLE_WRITE;
		//写地址
		//FpgaWriteRegister(FPGA_RE_W_C_9363_CONTROL,0X00);//MCU从FPGA获取9363_C的控制权
		UsNopDelay(15);
		for (i=0; i<16; i++)
		{
			//clk high	
			fpga_data |= bit_tf_clk;
			FpgaWriteRegister(write_reg_add, fpga_data);
			UsNopDelay(1);

			//DO 
			if (cmd_addr&(0x0001<<(15-i)))
				fpga_data |= bit_tf_do;
			else
				fpga_data &= ~bit_tf_do;
			FpgaWriteRegister(write_reg_add, fpga_data);
			UsNopDelay(1);

			//clk low,锁存数据
			fpga_data &= ~bit_tf_clk;
			FpgaWriteRegister(write_reg_add, fpga_data);	
			UsNopDelay(1);
		}
		FPGA_DISABLE_WRITE;

		//读写数据
		read_data = 0;
		FPGA_ENABLE_WRITE;
		for (i=0; i<8; i++)
		{
			//clk high	
			fpga_data |= bit_tf_clk;
			FpgaWriteRegister(write_reg_add, fpga_data);
			UsNopDelay(1);

			if(1==read_wirte_flag)
			{
				//DO 
				if (data&(0x0001<<(7-i)))
					fpga_data |= bit_tf_do;
				else
					fpga_data &= ~bit_tf_do;
				FpgaWriteRegister(write_reg_add, fpga_data);
				UsNopDelay(1);
			}
			//clk low,锁存数据
			fpga_data &= ~bit_tf_clk;
			FpgaWriteRegister(write_reg_add, fpga_data);
			if(0==read_wirte_flag)
			{
				UsNopDelay(1);
				if (FpgaReadRegister(read_reg_add)&bit_tf_di)
				read_data |= (1<<(7-i));			
			}
			UsNopDelay(1);
			
		}
		//FpgaWriteRegister(FPGA_RE_W_C_9363_CONTROL,0X01);//MCU释放9363_C的控制权给FPGA
		
		FPGA_DISABLE_WRITE;
	}


	UsNopDelay(15);
	TFCsDiable(npcs);	

	return read_data;
}

#if 0
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
		reg_add = FPGA_REG_W_A_TF;
	else if (npcs == TF_B)
		reg_add = FPGA_REG_W_B_TF;
	else 
		return;

	fpga_data = (BIT_TF_EN);				//ENB HIGH,CLK,DI LOW
	FpgaWriteRegister(reg_add,fpga_data);
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
	UINT16 cmd_addr;
	UCHAR8 i,read_data=0;	
	UINT16 write_reg_add,fpga_data,read_reg_add;
	
	cmd_addr = ((read_wirte_flag==1)<<15)|(add&0x03ff);
	
	if ((npcs == TF_A)||(npcs == TF_B))
	{
		write_reg_add = FPGA_REG_W_9363_SPI_A_B;
		read_reg_add = FPGA_REG_R_SPI_IN;
	}	
	else if (npcs == TF_B)
	{
		write_reg_add = FPGA_REG_W_9363_SPI_A_B;
		read_reg_add = FPGA_REG_R_SPI_IN;
	}
	else if (npcs == TF_C)
	{
		write_reg_add = FPGA_REG_W_9363_SPI_C;
		read_reg_add = FPGA_REG_R_SPI_IN;
	}
	else 
		return 0;
	
	TFCsEnable(npcs);
	fpga_data = fpga_write_bak[write_reg_add];
	//写地址
	for (i=0; i<16; i++)
	{
		//clk high	
		fpga_data |= BIT_TF_CLK;
		FpgaWriteRegister(write_reg_add, fpga_data);
		UsNopDelay(1);

		//DI 
		if (cmd_addr&(0x0001<<(15-i)))
			fpga_data |= BIT_TF_DI;
		else
			fpga_data &= ~BIT_TF_DI;
		FpgaWriteRegister(write_reg_add, fpga_data);
		UsNopDelay(10);

		//clk low,锁存数据
		fpga_data &= ~BIT_TF_CLK;
		FpgaWriteRegister(write_reg_add, fpga_data);	
		UsNopDelay(10);
	}

	//读写数据
	read_data = 0;
	for (i=0; i<8; i++)
	{
		//clk high	
		fpga_data |= BIT_TF_CLK;
		FpgaWriteRegister(write_reg_add, fpga_data);
		UsNopDelay(1);

		//DI 
		if (data&(0x0001<<(7-i)))
			fpga_data |= BIT_TF_DI;
		else
			fpga_data &= ~BIT_TF_DI;
		FpgaWriteRegister(write_reg_add, fpga_data);
		UsNopDelay(10);

		//clk low,锁存数据
		fpga_data &= ~BIT_TF_CLK;
		FpgaWriteRegister(write_reg_add, fpga_data);
		if (FpgaReadRegister(read_reg_add)&BIT_TF_DO)
			read_data |= (1<<(7-i));
		UsNopDelay(10);
		
	}	
	UsNopDelay(10);
	TFCsDiable(npcs);	
	
	return read_data;
}
#endif



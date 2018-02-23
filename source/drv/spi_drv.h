/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司

*************************************************************
文件名：   SPI_DRV_H_
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： SPI_DRV_H_的底层驱动头文件 
函数列表： 
修改日期： 
        1.日期:      2010年08月05日  
          作者：     韦瑞锦 
          修改内容： 原版
        2.日期:      2012年04月17日  
          作者：     邓子谦
          修改内容： 微型光钎V02 
**************************************************************/
#ifndef _SPI_DRV_H_
#define _SPI_DRV_H_

#define SPI1_DR_Address  0x4001300C		// SPI1的数据寄存器地址

#define SPI2_DR_Address  0x4000380C		// SPI2的数据寄存器地址

//AD6643
#define SET_SDIO_CLK_PIN		  //201310171807 GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define CLR_SDIO_CLK_PIN		  //201310171807 GPIO_ResetBits(GPIOB, GPIO_Pin_11)

#define SET_SDIO_DAT_PIN	     //201311111223 GPIO_SetBits(GPIOB, GPIO_Pin_10)
#define CLR_SDIO_DAT_PIN	    //201311111223 GPIO_ResetBits(GPIOB, GPIO_Pin_10)
#define GET_SDIO_DAT_PIN	     //201311111223 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)
  


#define SPI_CS_AT45			0
#define SPI_CS_AD9122_A		1
#define SPI_CS_AD9122_B		2
#define SPI_CS_AD9524		3
#define SPI_CS_AD6643		4
#define SPI_CS_ALL			99

#define HMC830_ID           0x95198
#define HMC830_LCKED        2

// function 
void   InitSpi();
void   SpiCsEnable( UINT16 chip_sel );
void   SpiCsDisable( UINT16 chip_sel );
void   SpiDmaTrans( UINT16 dat_size, UCHAR8 * p_buff );
void   SpiTransDat( UINT16 dat_size, UCHAR8 * p_buff );
void   spi_dma_rw_buffer(UCHAR8 *p_cmd_buf, UINT16 cmd_len,UCHAR8 *p_data_buf, UINT16 data_len);
UCHAR8 SpiWriteBuf(UINT16 npcs, UCHAR8 * p_cmd_buf,UINT16 cmd_len,UCHAR8 * p_data_buf,UINT16 data_len);
UCHAR8 SpiReadBuf(UINT16 npcs, UCHAR8 * p_cmd_buf,UINT16 cmd_len,UCHAR8 * p_data_buf,UINT16 data_len);
void   SpiDatOutputMode();
void   SpiDatInputMode();
void   SpiDatBusMode();
void   SdioSpiWriteByte(UINT16 add,UCHAR8  data);
UCHAR8 SdioSpiReadByte(UINT16 add);
BOOL   IsPllLocked(UCHAR8 ucDev);
void   GetPllStatus(void);
void TFInit(void);
void TFInitCs(UCHAR8 npcs);
UCHAR8 ReadWriteTF(UCHAR8 npcs, UCHAR8 read_wirte_flag,UINT16  add, UCHAR8 data);
UINT32 WriteHmc1197(UCHAR8 add, UINT32 data);
UINT32 ReadHmc1197(UCHAR8 add);
#endif

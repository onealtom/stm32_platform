/************************************************************

     Copyright (C), 2011-2111, ����̩�˿Ƽ����޹�˾

*************************************************************
�ļ�����   SPI_DRV_H_
�汾�ţ�   V03
���ߣ�     Τ��� 
�������ڣ� 2010��08��05��
����޸ģ� 
���������� SPI_DRV_H_�ĵײ�����ͷ�ļ� 
�����б� 
�޸����ڣ� 
        1.����:      2010��08��05��  
          ���ߣ�     Τ��� 
          �޸����ݣ� ԭ��
        2.����:      2012��04��17��  
          ���ߣ�     ����ǫ
          �޸����ݣ� ΢�͹�ǥV02 
**************************************************************/
#ifndef _SPI_DRV_H_
#define _SPI_DRV_H_

#define SPI1_DR_Address  0x4001300C		// SPI1�����ݼĴ�����ַ

#define SPI2_DR_Address  0x4000380C		// SPI2�����ݼĴ�����ַ

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

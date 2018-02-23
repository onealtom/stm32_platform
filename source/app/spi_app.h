/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :spi.h
* Description :SPI处理函数
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			初始版本
**************************************************************/
#ifndef _SPI_H
#define _SPI_H

#define FLASH_FLAG 0xBB //
/* flash */

#define FLASH_PAGE_NUM_PER_SECTOR		16	// 256 BYTE PER PAGE   4KB PER SECTOR
#define FLASH_BYTES_PER_SECTOR			4096	// 256 BYTE PER PAGE   4KB PER SECTOR


#define FLASH_PAGE_SIZE		flash_page_size		// Flash页大小
#define FLASH_TYPE			flash_type			// Flash类型
#define FLASH_PARR1			flash_parr1			// Flash类型
#define FLASH_PAGE_SIZE_528		528		// Flash页大小
#define FLASH_PAGE_SIZE_1056		1056		// Flash页大小

#define FLASH_PAGE_SIZE_264		264		// Flash页大小

#ifdef FPGA_ACDU_16M_FLASH
#define FLASH_PAGE_SIZE_256		256		// Flash页大小
#else
#define FLASH_PAGE_SIZE_256		256		// Flash页大小
#endif

#define FLASH_TYPE0		0		// Flash类型0 atmel 528 byte per page
#define FLASH_TYPE1		1		// Flash类型1 atmel 1056 byte per page
#define FLASH_TYPE2		2		// Flash类型2 atmel 264 byte per page
#define FLASH_TYPE3		3		// Flash类型3 winbond 256 byte per page
#define FLASH_ID0		0x1f270100		// Flash类型0 atmel 528 byte per page
#define FLASH_ID1		0x1f280000		// Flash类型0 atmel 1056 byte per page
#define FLASH_ID2		0x1f280001		// Flash类型0 atmel 264 byte per page
#define FLASH_ID3		0xEF401800		// Flash类型0 winbond 256 byte per page


#define FLASH_PAGE_COUNT	65536// Flash总页数
#define FLASH_PAGE_NUM_PER_SECTOR		16	// 256 BYTE PER PAGE   4KB PER SECTOR
#define FLASH_SECTOR_SIZE		4096	// 256 BYTE PER PAGE   4KB PER SECTOR

#define FLASH_PAGE_NUM_PER_BLOCK1		128	// 1 BLOCK1 = 32768 byte=32k,256 BYTE PER PAGE 
#define FLASH_BLOCK1_SIZE		32768	// 1 BLOCK1 = 32768 byte=32k,256 BYTE PER PAGE 
#define FLASH_PAGE_NUM_PER_BLOCK2		256	//  1 BLOCK2 = 65536 byte=64k ,256 BYTE PER PAGE
#define FLASH_BLOCK2_SIZE		65536	// 1 BLOCK2 = 65536 byte=64k ,256 BYTE PER PAGE



/*************************华邦*/


#if 0
//fpga 4M
#define FLASH_FPGA_PAGE_START1		(0+15)		// 4M,16384Page
#define FLASH_FPGA_END1			(16384-1)

#define FLASH_FPGA_PAGE_START2		(16384+15)	// 4M,16384Page
#define FLASH_FPGA_END2			(32768-1)

#define FLASH_FPGA_BLOCK_COUNT	16384		// 4M,16384Page

//mcu
#define FLASH_MCU_SW_START_PAGE	(34608+15)	//200K,800Page
#define FLASH_MCU_END			(35408-1)	
#endif

#if 1
//fpga 3.7M
#define FLASH_FPGA_PAGE_START1		(0+15)		// 3.7M,16384Page
#define FLASH_FPGA_END1			(14800-1)

#define FLASH_FPGA_PAGE_START2		(14800+15)	// 3.7M,16384Page
#define FLASH_FPGA_END2			(30000-1)

#define FLASH_FPGA_BLOCK_COUNT	14800		// 4M,16384Page

//mcu
#define FLASH_MCU_SW_START_PAGE	(30000+15)	//200K,800Page ,START page:30000
#define FLASH_MCU_END			(30800-1)	
#endif

// 系统参数存储区1
#define FLASH_PARAM_1B_PAGE		35408		// 4k,16Page
#define FLASH_PARAM_2B_PAGE		35424		// 4k,16Page
#define FLASH_PARAM_4B_PAGE		35440		// 4k,16Page
#define FLASH_PARAM_ASC_PAGE		35456		// 4k,16Page

// 系统参数存储区2
#define FLASH_PARAM_1B_PAGE_EX		35472	// 4k,16Page
#define FLASH_PARAM_2B_PAGE_EX		35488	// 4k,16Page
#define FLASH_PARAM_4B_PAGE_EX		35504	// 4k,16Page
#define FLASH_PARAM_ASC_PAGE_EX		35520	// 4k,16Page

#define FLASH_A_DL_ATT_ADJ_TBL_PAGE		35536	// 4k,16Page //下行衰减器校准表格 
#define FLASH_A_UL_ATT_ADJ_TBL_PAGE		35552	// 4k,16Page //上行衰减器校准表格
#define FLASH_B_DL_ATT_ADJ_TBL_PAGE		35568	// 4k,16Page //下行衰减器校准表格
#define FLASH_B_UL_ATT_ADJ_TBL_PAGE		35584	// 4k,16Page //上行衰减器校准表格
#define FLASH_C_DL_ATT_ADJ_TBL_PAGE		35600	// 4k,16Page //下行衰减器校准表格 
#define FLASH_C_UL_ATT_ADJ_TBL_PAGE		35616	// 4k,16Page //上行衰减器校准表格
#define FLASH_D_DL_ATT_ADJ_TBL_PAGE		35632	// 4k,16Page //下行衰减器校准表格
#define FLASH_D_UL_ATT_ADJ_TBL_PAGE		35648	// 4k,16Page //上行衰减器校准表格


#define FLASH_A_TS_PAGE_START		(35664+15)	// 40K,160page
#define FLASH_B_TS_PAGE_START		(35824+15)	// 40K,160page
#define FLASH_C_TS_PAGE_START		(35984+15)	// 40K,160page
#define FLASH_D_TS_PAGE_START		(35984+15)	// 40K,160page




#define FLASH_TOPO_PAGE			65535



/***********************end************/


/**********************old***************/
#if 0
#define FLASH_FPGA_SECTOR_START1		0				//BLOCK
#define FLASH_FPGA_SECTOR_START2		((3700+flash_parr2*(8192-3700))/4 	)		//BLOCK
#define FLASH_FPGA_PAGE_START1		(0*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE	))
#define FLASH_FPGA_PAGE_START2 		((3700+flash_parr2*(8192-3700))*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE	))

#define FLASH_FPGA_PAGE_COUNT		((3700+flash_parr2*(8192-3700))*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE	)	)	// FPGA程序块数量
//#define FLASH_FPGA_SECTOR_COUNT		(3700+flash_parr2*(8192-3700))/4		// FPGA程序块数量

#define FLASH_MCU_SW_INFO_PAGE		7548
#define FLASH_MCU_SW_START_PAGE		(7549*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))
#define FLASH_MCU_SW_START_SECTOR		1875	// 7500/4

//#define FIRMWARE_START_ADDR			(32*1024+0x100000)	//16K

#define FLASH_A_DL_ATT_ADJ_TBL_PAGE		((8042+2*flash_parr1)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//下行衰减器校准表格
#define FLASH_A_UL_ATT_ADJ_TBL_PAGE		((8044+4*flash_parr1)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//上行衰减器校准表格
#define FLASH_B_DL_ATT_ADJ_TBL_PAGE		((8046+6*flash_parr1)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//下行衰减器校准表格
#define FLASH_B_UL_ATT_ADJ_TBL_PAGE		((8048+8*flash_parr1)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//上行衰减器校准表格
#define FLASH_C_DL_ATT_ADJ_TBL_PAGE		((8050+10*flash_parr1)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//下行衰减器校准表格
#define FLASH_C_UL_ATT_ADJ_TBL_PAGE		((8052+12*flash_parr1)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//上行衰减器校准表格
#define FLASH_D_DL_ATT_ADJ_TBL_PAGE		((8054+14*flash_parr1)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//下行衰减器校准表格
#define FLASH_D_UL_ATT_ADJ_TBL_PAGE		((8056+16*flash_parr1)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//上行衰减器校准表格
#define FLASH_A_TS_BLOCK		8104/8	////1013 BLOCK(8104--8111 8 pages)
#define FLASH_B_TS_BLOCK		8120/8	////1014 BLOCK(8120--8119 8 pages)
#ifdef     AD9369	
#define FLASH_C_TS_BLOCK		8136/8	////1015 BLOCK(8136--8127 8 pages)
#else
#define FLASH_C_TS_BLOCK		(16384-1024)/8	//(16384-3072)/8	////1920 BLOCK(61440--65536 4096 pages)
#endif

#define FLASH_D_TS_BLOCK		8152/8	////1016 BLOCK(8152--8168 8 pages)

#define FLASH_A_TS_PAGE_START		((FLASH_A_TS_BLOCK*8+1*FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//
#define FLASH_B_TS_PAGE_START		((FLASH_B_TS_BLOCK*8+1*FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//
#define FLASH_C_TS_PAGE_START		((FLASH_C_TS_BLOCK*8+1*FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//
#define FLASH_D_TS_PAGE_START		((FLASH_D_TS_BLOCK*8+1*FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE)*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))	//

#define FLASH_A_TS_FLAG			((FLASH_A_TS_PAGE_START-1*FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE)))	//
#define FLASH_B_TS_FLAG			((FLASH_B_TS_PAGE_START-1*FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE)))	//
#define FLASH_C_TS_FLAG			((FLASH_C_TS_PAGE_START-1*FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE)))	//
#define FLASH_D_TS_FLAG			((FLASH_D_TS_PAGE_START-1*FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE)))	//

#define FLASH_TS_INIT_MAX_STEP		1	//

// 系统参数存储区1
#define FLASH_PARAM_1B_PAGE		(8000*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))
#define FLASH_PARAM_2B_PAGE		(8004*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))
#define FLASH_PARAM_4B_PAGE		(8008*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))
#define FLASH_PARAM_ASC_PAGE	(8012*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))			//基本参数中的ASCII

// 系统参数存储区2
#define FLASH_PARAM_1B_PAGE_EX		(8020*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))
#define FLASH_PARAM_2B_PAGE_EX		(8024*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))
#define FLASH_PARAM_4B_PAGE_EX		(8028*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))
#define FLASH_PARAM_ASC_PAGE_EX		(8032*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))			//基本参数中的ASCII

#define FLASH_TOPO_PAGE			(8016*(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE))

#endif
/*********************end*****************************/


#define FLASH_PAGE_INFO_OK			    0x00	// flash 信息正确
#define FLASH_PAGE_INFO_ERROR			0xFF	// flash 信息错误

/***********************************AD9524寄存器地址**************************************/
#define AD9524_ADD_PORT_CONF			0x00

#define AD9524_ADD_READ_CON			    0x04
//PLL1
#define AD9524_ADD_REFA_LOW			    0x010
#define AD9524_ADD_REFA_HIGH			0x011
#define AD9524_ADD_REFB_LOW			    0x012
#define AD9524_ADD_REFB_HIGH			0x013
#define AD9524_ADD_REF_TEST			    0x014
#define AD9524_ADD_PLL1_FEEDBACK_L	    0x016
#define AD9524_ADD_PLL1_FEEDBACK_H	    0x017
#define AD9524_ADD_PLL1_CHARGE_L		0x018
#define AD9524_ADD_PLL1_CHARGE_H		0x019
#define AD9524_ADD_PLL1_INPUT			0x01A
#define AD9524_ADD_REF_TEST			    0x01B
#define AD9524_ADD_PLL1_MISC			0x01C
#define AD9524_ADD_PLL1_LOOP			0x01D
//PLL2
#define AD9524_ADD_PLL2_CHARGE		    0x0F0
#define AD9524_ADD_PLL2_FEEDBACK		0x0F1
#define AD9524_ADD_PLL2_CONTROL		    0x0F2
#define AD9524_ADD_VCO_CONTROL		    0x0F3
#define AD9524_ADD_VCO_DIVIDER		    0x0F4
#define AD9524_ADD_PLL2_LOOP1			0x0F5
#define AD9524_ADD_PLL2_LOOP2			0x0F6
#define AD9524_ADD_NEW0_F9                   0x0F9

//CLOCK
#define AD9524_ADD_CH0_CONTROL1		0x196
#define AD9524_ADD_CH0_CONTROL2		0x197
#define AD9524_ADD_CH0_CONTROL3		0x198
#define AD9524_ADD_CH1_CONTROL1		0x199
#define AD9524_ADD_CH1_CONTROL2		0x19A
#define AD9524_ADD_CH1_CONTROL3		0x19B
#define AD9524_ADD_CH2_CONTROL1		0x19C
#define AD9524_ADD_CH2_CONTROL2		0x19D
#define AD9524_ADD_CH2_CONTROL3		0x19E
#define AD9524_ADD_CH3_CONTROL1		0x19F
#define AD9524_ADD_CH3_CONTROL2		0x1A0
#define AD9524_ADD_CH3_CONTROL3		0x1A1
#define AD9524_ADD_CH4_CONTROL1		0x1AE
#define AD9524_ADD_CH4_CONTROL2		0x1AF
#define AD9524_ADD_CH4_CONTROL3		0x1B0
#define AD9524_ADD_CH5_CONTROL1		0x1B1
#define AD9524_ADD_CH5_CONTROL2		0x1B2
#define AD9524_ADD_CH5_CONTROL3		0x1B3
#define AD9524_ADD_PLL1_OUTPUT		0x1BA
#define AD9524_ADD_PLL1_CH_OUTPUT	0x1BB
//READBACK
#define AD9524_ADD_READBACK0			0x22C
#define AD9524_ADD_READBACK1			0x22D
//OTHER
#define AD9524_ADD_STATUS1			0x230
#define AD9524_ADD_STATUS2			0x231
#define AD9524_ADD_STATUS3			0x232
#define AD9524_ADD_POWER_DOWN		0x233
//UPDATE
#define AD9524_ADD_UPDATE_ALL			0x234

//UPDATE
#define AD9528_ADD_UPDATE_ALL			0x0F




/***************************************** HMC830寄存器**********************************************************/
#define HMC830_ID_00								0x00
#define HMC830_RST_01								0x01
#define HMC830_REFDIV_02							0x02
#define HMC830_FRE_INT_03							0x03
#define HMC830_FRE_FRA_04							0x04
#define HMC830_VCO_SPI_05							0x05
#define HMC830_SD_CFG_06							0x06
#define HMC830_LOCK_DET_07						0x07
#define HMC830_ANALOG_EN_08						0x08
#define HMC830_CHARGE_PUMP_09					0x09
#define HMC830_VCO_AUTO_0A						0x0A
#define HMC830_PD_0B								0x0B
#define HMC830_FINE_FRE_0C							0x0C
#define HMC830_GPO_SPI_0F							0x0F
#define HMC830_VCO_TUNE_10						0x10
#define HMC830_SAR_11								0x11
#define HMC830_GPO2_12								0x12
#define HMC830_BIST_13								0x13



#define  ENABLE_AD9524_READ          Ad9524Write(AD9524_ADD_PORT_CONF,0x81)
#define  DISABLE_AD9524_READ         Ad9524Write(AD9524_ADD_PORT_CONF,0x00) 

#define  ENABLE_AD9528_READ          Ad9524Write(AD9524_ADD_PORT_CONF,0x18)
#define  DISABLE_AD9528_READ         Ad9524Write(AD9524_ADD_PORT_CONF,0x00) 

#define ENABLE_AD9122_READ          DISABLE_AD9524_READ
#define DISABLE_AD9122_READ         ENABLE_AD9524_READ


/* Variable */
extern UINT16 flash_page_size; 
extern UINT16 flash_type;
extern UCHAR8 flash_parr1;
extern UCHAR8 flash_parr2;

/* function */
void FlashWrite(UINT32 page,INT16 offset,UCHAR8 *data,UINT16 len,UINT16 option);
void  FlashRead(INT32 page,INT16 offset,UCHAR8 *data,INT32 len);
CHAR8 FlashEraseSectors(UINT32 from,UINT32 to);
void GetFlashPageInfo( UINT16 length, UCHAR8 * p_dat, UCHAR8 * p_tx_buff );
UINT32 FlashPageChang ( UINT32 page );
void Ad9122Write(UCHAR8 addr, UCHAR8 val,UCHAR8 ab_flag);
UCHAR8 Ad9122Read(UCHAR8 addr,UCHAR8 ab_flag);
void Ad9524Write(UINT16 add, UCHAR8 data);
UCHAR8 Ad9524Read(UINT16 add);
void Ad6643mspi(UINT16 add,UCHAR8  data);
void Ad6649Write(UINT16 add,UCHAR8  data);
UCHAR8 Ad6643Read(UINT16 add);
#endif //_SPI_H

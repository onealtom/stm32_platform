/***************************************************************
*Shenzhen Grandtelco Technology Co.,Ltd All rights reserved
*
* FileName    :Transceiver_app.h
* Description :收发器芯片处理函数
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2012-06-01	v0.1			初始版本
**************************************************************/
#ifndef _TRANSCEIVER_H
#define _TRANSCEIVER_H

//9369
#ifdef AD9369
	#define AD9369	1
#else
	#define AD9369	0
#endif

//9363锁相环
#define AD9363_INIT_DA_ST		0x1A	// 1A为锁定+发送接收使能打开，其他异常
#define AD9363_BB_PLL_LOCK		0x80	// 80为BBPLL数字锁相环锁定，其他失锁
#define AD9363_RX_PLL_ST		2	
#define AD9363_TX_PLL_ST		2	
#define AD9363_A_Modulator_EN		0X3C	
#define AD9363_B_Modulator_EN		0X3C	


// 9363锁相环
#define AD9363_REG_R_INIT_DA_ST	0x17		
#define AD9363_REG_R_BB_PLL_LOCK	0x5E		
#define AD9363_REG_R_RX_PLL_ST	0x247		
#define AD9363_REG_R_TX_PLL_ST	0x287		
#define AD9363_REG_R_Modulator_EN	0x57	

//INIT CMD
#define CMD_BLOCK_WRITE		0x02
#define CMD_SPI_WRITE			0x03
#define CMD_WAIT				0x06
#define CMD_REFCLK_SCALE		0x05
#define CMD_WAIT_CALDONE		0x07
#define CMD_SPI_READ			0x08
#define CMD_UPDATA_DATA			0x09

#define CMD_FPGA_WRITE			0x0A

#define CMD_WAIT_FPGA_CFG			0x0E


#define CMD_BLOCK_WRITE_LEN		0x04
#define CMD_SPI_WRITE_LEN			0x04
#define CMD_WAIT_LEN				0x03
#define CMD_REFCLK_SCALE_LEN		0x05
#define CMD_WAIT_CALDONE_LEN		0x04
#define CMD_SPI_READ_LEN			0x03
#define CMD_UPDATA_DATA_LEN			0x32

#define CMD_RESULT_FAIL		0
#define CMD_RESULT_OK			1
#define CMD_RESULT_TIMEOUT	2
#define CMD_RESULT_IGNORE		3


//WAIT_CALDONE 子命令
//9363
#define BBPLL		0X00   
#define RXCP			0X01 
#define TXCP			0X02 
#define RXFILTER		0X03
#define TXFILTER		0X04 
#define BBDC			0X05  
#define RFDC			0X06  
#define TXQUAD		0X07
#define RXQUAD		0X08
#define TXMON		0X09
#define RXMON		0X0A
//9369
#define RXTIA         0x0B
#define MailboxBusy   0x0C
#define ADCPROFILE    0x0D
#define ADCTuner      0x0E
#define RFPLLLOCK     0x0F
#define RFPLLCP       0x10
#define RCAL      	  0x11
#define CLKPLLLOCK      0x12



#define BBPLL_REG		0x05E   
#define RXCP_REG		0x244
#define TXCP_REG		0x284
#define RXFILTER_REG	0x016
#define TXFILTER_REG	0x016
#define BBDC_REG		0x016  
#define RFDC_REG		0x016  
#define TXQUAD_REG		0x016
#define RXQUAD_REG		0X08
#define TXMON_REG		0X09
#define RXMON_REG		0X0A


#define RXTIA_REG			0X016
#define MailboxBusy_REG     0x414//ADCPROFILE
#define ADCPROFILE_REG      0x24B
#define ADCTuner_REG		0x016
#define RFPLLLOCK_REG		0x190
#define RFPLLCP_REG			0x18D
#define RCAL_REG			0X016
#define CLKPLLLOCK_REG		0X125

#define BBPLL_BIT		7   
#define RXCP_BIT			7
#define TXCP_BIT			7
#define RXFILTER_BIT		7
#define TXFILTER_BIT		6 

#define BBDC_BIT			0  
#define RFDC_BIT			1  
#define TXQUAD_BIT		4
#define RXQUAD_BIT		0X08
#define TXMON_BIT		0X09
#define RXMON_BIT		0X0A
#define RXTIA_BIT		  5
#define MailboxBusy_BIT   7
#define ADCPROFILE_BIT		  5
#define ADCTuner_BIT		  7
#define RFPLLLOCK_BIT		  0
#define RFPLLCP_BIT		  	  7
#define RCAL_BIT		  	  6

#define TXFILTER_9369_BIT	  0	
#define CLKPLLLOCK_BIT	  0	 



#define BBPLL_DONE		1   
#define RXCP_DONE		1
#define TXCP_DONE		1
#define RXFILTER_DONE	0
#define TXFILTER_DONE	0 
#define BBDC_DONE		0  
#define RFDC_DONE		0  
#define TXQUAD_DONE	    0
#define RXTIA_DONE	    0
#define MailboxBusy_DONE   0
#define ADCPROFILE_DONE   0
#define ADCTuner_DONE    0
#define RFPLLLOCK_DONE   1
#define RFPLLCP_DONE   1
#define RCAL_DONE       0
#define CLKPLLLOCK_DONE       1

#define RXQUAD_DONE	0X08
#define TXMON_DONE		0X09
#define RXMON_DONE		0X0A
#define MAX_ARRAY_LINE_LENGTH       50
#define RECE_MAX	1320
#define PKG_MAX_9363	1024


typedef struct SYSTEM_INIT_DATA_S{
	UINT16 init_flag;
	UINT16 a_packet;
	UINT16 packet_len[MAX_ARRAY_LINE_LENGTH];
}SYSTEM_INIT_DATA_T;


UCHAR8 CmdHandleSpiWrite(UCHAR8 npcs,UINT16 addr,UCHAR8 data);
UCHAR8 CmdHandleWait(UINT16 time_ms);
UCHAR8 CmdHandleWaitCaldone(UCHAR8 npcs,UCHAR8 cld_id,UINT16 time_out);
UCHAR8 SaveInitData(UCHAR8 npcs,UINT16 current_p, UCHAR8  total_p,UCHAR8 * p_data,UINT16 len);
CHAR8 InitTransceiver(UCHAR8 abcd);

void SetAtt3(UCHAR8 abcd,UCHAR8 att);
void SetAtt1(UCHAR8 abcd,UCHAR8 att);
UCHAR8 SetAtt3Tx(UCHAR8 npcs,UCHAR8 att);
void TransSetPll(UCHAR8 up_down_flag, FLOAT32 pll);
UCHAR8 TransGetRxPllStatus(UCHAR8 up_down_flag);
UCHAR8 TransGetTxPllStatus(UCHAR8 up_down_flag);
UCHAR8 TransGetClkStatus(void);
UCHAR8 GetUpdateData(UCHAR8 npcs,UCHAR8 * p_data,UCHAR8 *len);
#endif //_TRANSCEIVER_H

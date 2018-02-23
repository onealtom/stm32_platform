/**
 * \file common.c
 * \brief Contains Mykonos API common wrapper functions for user hardware platform drivers
 */

/**
* \page Disclaimer Legal Disclaimer
* Copyright 2015-2017 Analog Devices Inc.
* Released under the AD9371 API license, for more information see the "LICENSE.txt" file in this zip file.
*
*/

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include "pl_spi_drv.h" 
#include "Header.h"
#include "fpga.h"

ADI_LOGLEVEL CMB_LOGLEVEL = ADIHAL_LOG_NONE;

uint32_t timo_ms_iCnt =0 ;
uint32_t timo_us_iCnt =0 ;



#define FPGA_REG_W_ADCSPI_BUSCTL				0x80F0
#define FPGA_REG_W_ADCSPI_ADDR					0x80FA
#define FPGA_REG_W_ADCSPI_TX					0x80FB
#define FPGA_REG_R_ADCSPI_RX					0x00F4



/* hardware reset function */
commonErr_t CMB_hardReset(uint8_t spiChipSelectIndex)
{
	FPGA_ENABLE_WRITE;
	/*disable the SPI chip CS pin*/
	FpgaWriteRegister(FPGA_REG_W_ADCSPI_BUSCTL, 0x00 );
		CMB_wait_ms(100);
	FpgaWriteRegister(FPGA_REG_W_ADCSPI_BUSCTL, 0x01 );
		CMB_wait_ms(100);
}


commonErr_t CMB_wait_ms(uint32_t time_ms)
{
   uint32_t i=0;  
   while(time_ms--)
   {
      i=12000;
      while(i--); 
   }
   WTD_CLR;
    return(COMMONERR_OK);
}

commonErr_t CMB_wait_us(uint32_t time_us)
{    
   uint32_t i=0;
   while(time_us--)
   {
      i=10;
      while(i--) ;    
   }
    return(COMMONERR_OK);
}

commonErr_t CMB_setTimeout_ms(uint32_t timeOut_ms)
{
	timo_ms_iCnt = timeOut_ms ;
	timo_us_iCnt = 0 ;
}


commonErr_t CMB_setTimeout_us(uint32_t timeOut_us)
{
	timo_ms_iCnt = 0;
	timo_us_iCnt = timeOut_us ;
}


commonErr_t CMB_hasTimeoutExpired()
{
	uint8_t retval = 0;
	
	if(timo_ms_iCnt!=0){
		timo_ms_iCnt--;
		CMB_wait_ms(1);
		retval=timo_ms_iCnt;
	}
	else if(timo_us_iCnt!=0){
		timo_us_iCnt--;
		CMB_wait_us(1);
		retval=timo_us_iCnt;
	}
	else{
		retval = 0;
	}

    if (retval > 0){
        return (COMMONERR_OK);
    }
    else {
        return(COMMONERR_FAILED);
    }
}

commonErr_t CMB_writeToLog(ADI_LOGLEVEL level, uint8_t deviceIndex, uint32_t errorCode, const char *comment)
{
    return(COMMONERR_OK);
}




/* single SPI byte write function */
commonErr_t CMB_SPIWriteByte(spiSettings_t *spiSettings, uint16_t addr, uint8_t data)
{
	if((addr == 0x03)||(addr == 0x02))
		printf("if 03 02 data=%02X\n\r",data);
	/*Set data to TX REG which i want to sent */
	FpgaWriteRegister(0x80FB, (uint16_t)data );//FPGA_REG_W_ADCSPI_TX=80FB
	UsNopDelay(10);
	/*Set  FPGA_REG_W_ADCSPI_ADDR with (bit15:WR flag; bit7~0: SPI addr ), 
	then fpga will do the TX work */
	//FpgaWriteRegister(0x80FA, ( 0x7FFF & addr ) );//FPGA_REG_W_ADCSPI_ADDR=80FA //AD9373
	FpgaWriteRegister(0x80FA, ( 0x8000 |( 0x7FFF & addr )) );//FPGA_REG_W_ADCSPI_ADDR=80FA //AD9363
	
	return COMMONERR_OK;

}

commonErr_t CMB_SPIWriteBytes(spiSettings_t *spiSettings, uint16_t *addr, uint8_t *data, uint32_t count)
{
	int i;
	for(i=0; i<count ; i++ ){
		CMB_SPIWriteByte(NULL, addr[i], data[i] );
	}

}

/* single SPI byte read function */
commonErr_t CMB_SPIReadByte (spiSettings_t *spiSettings, uint16_t addr, uint8_t *readdata)
{

	/*Set  FPGA_REG_W_ADCSPI_ADDR with (bit15:WR flag; bit7~0: SPI addr ), 
	then fpga will do the trans work */
       //FpgaWriteRegister(FPGA_REG_W_ADCSPI_ADDR, ( 0x8000 | (addr&0x7FFF) ) );//ADDR=80FA  //ad9373
	FpgaWriteRegister(FPGA_REG_W_ADCSPI_ADDR, (addr&0x7FFF) ) ;//ADDR=80FA  //ad9363
	
	UsNopDelay(10);
	
	/*after send addr read back form SPI of ADC chip*/

	*readdata = FpgaReadRegister(FPGA_REG_R_ADCSPI_RX);

}
 
/* write a field in a single register */
commonErr_t CMB_SPIWriteField(spiSettings_t *spiSettings, uint16_t addr, uint8_t  field_val, uint8_t mask, uint8_t start_bit)
{
    uint8_t Val=0;

    if(CMB_SPIReadByte(spiSettings, addr, &Val))
    {
        return(COMMONERR_FAILED);
    }
    Val = (Val & ~mask) | ((field_val << start_bit) & mask);
    if(CMB_SPIWriteByte(spiSettings, addr, Val))
    {
        return(COMMONERR_FAILED);
    }

    return(COMMONERR_OK);
}


/* read a field in a single register */
commonErr_t CMB_SPIReadField (spiSettings_t *spiSettings, uint16_t addr, uint8_t *field_val, uint8_t mask, uint8_t start_bit)	
{
    uint8_t data;

    if(CMB_SPIReadByte(spiSettings, addr, &data))
    {
        return(COMMONERR_FAILED);
    }
    *field_val =(uint8_t)((data & mask) >> start_bit);

    return(COMMONERR_OK);
}

/***************************************************************************//**
 *   @file   main.c
 *   @brief  Implementation of Main Function.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2013(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include "Header.h"
#include "config.h"
#include "ad9361_api.h"
#include "parameters.h"
#include "platform.h"


/******************************************************************************/
/************************ Variables Definitions *******************************/
/******************************************************************************/

/**
 * @brief ad936x_init_main
 *
 * @return 0表示初始化成功，-1表示初始化失败
 */
int ad936x_init_main(void)
{
#include "def_init_param.h"
	// NOTE: The user has to choose the GPIO numbers according to desired
	// carrier board.
	//.gpio_resetb = GPIO_RESET_PIN;
	int ret;
	
	printf("def param ad = 0x%08X\r\n",&default_init_param);
	
	CMB_hardReset();
	CMB_wait_ms(10);
#ifdef LINUX_PLATFORM
	gpio_init(default_init_param.gpio_resetb);
#else
	gpio_init(GPIO_DEVICE_ID);
#endif
	gpio_direction(default_init_param.gpio_resetb, 1);

	spi_init(SPI_DEVICE_ID, 1, 0);

	//if (AD9364_DEVICE){
		//printf("ID_AD9364\r\n");
		//default_init_param.dev_sel = ID_AD9364;
	//}
	//if (AD9363A_DEVICE){
	//	printf("ID_AD9363A\r\n");
	//	default_init_param.dev_sel = ID_AD9363A;
	//}

	ret = ad9361_init(&ad9361_phy, &default_init_param);
	if(ret == 0){
		ad9361_set_tx_fir_config(ad9361_phy, tx_fir_config);
		ad9361_set_rx_fir_config(ad9361_phy, rx_fir_config);
		printf("Done.\n");
	}

	printf("############a=%ld\n\r",ad9361_phy->clk_refin->rate);

	free(ad9361_phy->spi);
	free(ad9361_phy->clk_refin);
	free(ad9361_phy->pdata);
	free(ad9361_phy);
	printf("############a=%ld\n\r",ad9361_phy->clk_refin->rate);
	if (FpgaReadRegister(FPGA_REG_A_FAD_POW_H) >0x4000 ){ 
		return -1;
	}else{
		return 0;
	}

}

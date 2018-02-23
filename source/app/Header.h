#ifndef _HEADER_H_
#define _HEADER_H_

#include <string.h>
#include <math.h>

#include "stdio.h"
#include "trace.h" 

#include "type_def.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"

#include "Global_drv.h"
#include "spi_drv.h"
#include "gpio_drv.h"
#include "timer_drv.h"
#include "uart_drv.h"
#include "usb_drv.h"
#include "Adc_drv.h"
#include "I2c_drv.h"

#include "ex_conf.h"
#include "system.h"
#include "sys_param.h"
#include "param_addr.h"
#include "adc_app.h"
#include "fpga.h"
#include "crc8.h"
#include "spi_app.h"
#include "timer_app.h"
#include "uart_app.h"
#include "init.h"
#include "usbTxRx.h"
//#include "Main_others.h"
#include "Update_app.h"
#include "Twi_app.h"
#include "msg_app.h" 
#include "rec_app.h"
//#include "wcdma_app.h"
#include "base_app.h"
#include "fps_app.h"
#include "Transceiver_app.h"
#include "hmc1197_app.h"
#include "phy_drv.h"

extern void *memset(void *s,int ch,size_t n); 

/// Use for power management
#define STATE_IDLE    0
/// The USB device is in suspend state
#define STATE_SUSPEND 4
/// The USB device is in resume state
#define STATE_RESUME  5

#define flash
#define BOARD_FLASH_EEFC

// 选择串口0作为调试串口;
//#define DEBUG_USART0

void LowPowerMode(void);
void NormalPowerMode(void);

#endif

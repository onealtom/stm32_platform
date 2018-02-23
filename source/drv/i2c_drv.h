
#ifndef _I2C_DRV_H_
#define _I2C_DRV_H_

#define I2C_ADD_AD7415		0x49	//7415-0
//#define I2C_TIME_OUT		100000

void InitI2c();
UCHAR8 I2cAD7415Read( UCHAR8 rd_addr, UINT16 *p_dat );

#endif


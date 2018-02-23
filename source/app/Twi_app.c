/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :twi_app.c
* Description :TWI(IIC)接口操作
* Version     :v0.1
* Author      :RJ
* Date        :2008-08-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*	RJ		2008-08-29	v0.1			初始版本
**************************************************************/

#include "Header.h"
	
#if 0
CHAR8 GetTemperature()
{
	UINT16 tmp;
	CHAR8 temperature;

	if ( 0==I2cAD7415Read( 0, &tmp ) )
	{
		return 10;
	}
	
	if ( tmp & 0x0200 )
	{
		//0度以下，温度值是补码形式的
		tmp = ((~tmp)+1)/4;
		temperature = tmp*(-1);
	}
	else
	{
		 temperature = tmp/4;
	}
	//TRACE_INFO( "Board Temperature:%d 'C\r\n", temperature );
	return temperature;
	
}
#endif
#if 0
{
	UCHAR8 dat1,dat2;
	UINT16 tmp;
	CHAR8 temperature;
	UINT16 time_out=0;

//	TRACE_INFO( "TWI_Read>>Addr:%02X .. ", TWI_ADD_AD7415 );
	TWI_StartRead(AT91C_BASE_TWI, TWI_ADD_AD7415, 0, 1);
	
	time_out=0;
	while( 0 == TWI_ByteReceived(AT91C_BASE_TWI) )
	{
		if ( time_out++>5000 )
		{
			return 0;
		}
	}
	dat1 = TWI_ReadByte(AT91C_BASE_TWI);
//	TRACE_INFO_WP( "dat1:%02X .. ", dat1 );
	
	TWI_SendSTOPCondition(AT91C_BASE_TWI);
//	TRACE_INFO( "STOP..");
	time_out=0;
	while( 0 == TWI_ByteReceived(AT91C_BASE_TWI) )
	{
		if ( time_out++>5000 )
		{
			return 0;
		}
	}
	dat2 = TWI_ReadByte(AT91C_BASE_TWI);
//	TRACE_INFO_WP( "dat2:%02X .. ", dat2 );

	time_out=0;
	while( 0 == TWI_TransferComplete(AT91C_BASE_TWI) )
	{
		if ( time_out++>5000 )
		{
			return 0;
		}
	}
//	TRACE_INFO_WP( "End\r\n" );

	tmp = (dat1<<2) | (dat2>>6);
	if ( tmp & 0x0200 )
	{
		//0度以下，温度值是补码形式的
		tmp = ((~tmp)+1)/4;
		temperature = tmp*(-1);
	}
	else
	{
		 temperature = tmp/4;
	}
	//TRACE_INFO( "Board Temperature:%d 'C\r\n", temperature );
	return temperature;
}
#endif



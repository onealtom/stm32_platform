#include "Header.h"

void InitI2c()
{

	I2C_InitTypeDef  I2C_InitStructure; 

	/* I2C1 Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	I2C_DeInit(I2C2);
	/* I2C configuration */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0xA0;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 10000;		// 100k

	/* I2C Peripheral Enable */
//	I2C_Cmd(I2C1, ENABLE);
	/* Apply I2C configuration after enabling it */
	I2C_Init(I2C2, &I2C_InitStructure);

	I2C_Cmd(I2C2, ENABLE);

	
}

UCHAR8 I2cAD7415Read( UCHAR8 rd_addr, UINT16 *p_dat )
{
	UINT16 dt=0;
	UCHAR8 dat1, dat2;

	*p_dat = 0;
	
	/* While the bus is busy */
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY))
	{
		dt++;
		if ( dt>10000 )
		{
			I2C_SoftwareResetCmd(I2C2, ENABLE);
			//TRACE_INFO("I2c Err 0\r\n");
			return 0;
		}
		UsNopDelay(2);
	}

//	I2C_AcknowledgeConfig(I2C2, ENABLE);


	/* Send START condition */
	I2C_GenerateSTART(I2C2, ENABLE);	

	dt = 0;
	/* Test on EV5 and clear it */
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
	{
		dt++;
		if ( dt>50000 )
		{
			//I2C_SoftwareResetCmd(I2C2, ENABLE);
			InitI2c();
			//TRACE_INFO("I2c Err 1\r\n");
			return 0;
		}
		WTD_CLR;
		UsNopDelay(2);
	}
#if 0
	/* Send EEPROM address for write */
	I2C_Send7bitAddress(I2C2, I2C_ADD_AD7415, I2C_Direction_Receiver);

	dt = 0;
	/* Test on EV6 and clear it */
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		dt++;
		if ( dt>10000 )
		{
			I2C_SoftwareResetCmd(I2C2, ENABLE);
			//TRACE_INFO("I2c Err 2\r\n");
			return 0;
		}
		UsNopDelay(2);
	}
#endif
	/* Send the EEPROM's internal address to write to */
	I2C_SendData(I2C2, (I2C_ADD_AD7415<<1)|0x01 );		// addr0

	dt = 0;
	/* Test on EV8 and clear it */
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		dt++;
		if ( dt>10000 )
		{
			I2C_SoftwareResetCmd(I2C2, ENABLE);
			//TRACE_INFO("I2c Err 2\r\n");
			return 0;
		}
		UsNopDelay(2);
	}


	/* Send the EEPROM's internal address to write to */
	I2C_SendData(I2C2, 0x00);		// addr0

	dt = 0;
	/* Test on EV8 and clear it */
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		dt++;
		if ( dt>10000 )
		{
			I2C_SoftwareResetCmd(I2C2, ENABLE);
			//TRACE_INFO("I2c Err 3\r\n");
			return 0;
		}
		UsNopDelay(2);
	}

	/* Send EEPROM address for write */
	I2C_Send7bitAddress(I2C2, I2C_ADD_AD7415, I2C_Direction_Receiver);

	dt = 0;
	/* Test on EV6 and clear it */
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		dt++;
		if ( dt>10000 )
		{
			I2C_SoftwareResetCmd(I2C2, ENABLE);
			//TRACE_INFO("I2c Err 4\r\n");
			return 0;
		}
		UsNopDelay(2);
	}

	dt = 0;
	while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) )
	{
		dt++;
		if ( dt>10000 )
		{
			I2C_SoftwareResetCmd(I2C2, ENABLE);
			//TRACE_INFO("I2c Err 5\r\n");
			return 0;
		}
		UsNopDelay(2);
	}

	dat1 = I2C_ReceiveData(I2C2);

	/* Disable Acknowledgement */
	I2C_AcknowledgeConfig(I2C2, DISABLE);

	/* Send STOP Condition */
	I2C_GenerateSTOP(I2C2, ENABLE);

	dt = 0;
	while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) )
	{
		dt++;
		if ( dt>10000 )
		{
			I2C_SoftwareResetCmd(I2C2, ENABLE);
			//TRACE_INFO("I2c Err 6\r\n");
			return 0;
		}
		UsNopDelay(2);
	}

	dat2 = I2C_ReceiveData(I2C2);

	/* Enable Acknowledgement to be ready for another reception */
	I2C_AcknowledgeConfig(I2C2, ENABLE);

	*p_dat = (dat1<<2) | (dat2>>6);
	return 1;

}


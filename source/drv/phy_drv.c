#include "Header.h"
UINT16 Phy4_Serdes_St=-1;
#if 0
//8662
const UINT16 phy4RegVal[][2]={   
       //122.88M                       //125M 
   //reg           //val          //reg         //val 
   /*
{ {0x0000, 0x0081}, {0x0000, 0x0081} },
*/
{0x001f,0x0010},
{0x0017,0x8131},
{0x001f,0x0000},
{0x001d,0x0e0a}, 		
{0x0017,0x100c},// you 3004改为1004  20130325  
{0x0000,0x9140},
{0x0000,0x1140},

{0x011f,0x0010},
{0x0117,0x8131},
{0x011f,0x0000},
{0x011d,0x0a0e}, 		
{0x0117,0x2004},// you 3004改为1004  20130325   20130405 0X1004-->100C  20130703 0X100c-->2004
{0x0100,0x8100},//20130703 0X9140-->8100
{0x0100,0x2100},//20130703 0X1140-->2100
	   
};
#endif 
//9031
const UINT16 phy5RegVal[][2]={   
       //122.88M                       //125M 
   //reg           //val          //reg         //val 
   /*
{ {0x0000, 0x0081}, {0x0000, 0x0081} },
*/
{0x000d,0x0002},
{0x000e,0x0004},
{0x000d,0x4002},
{0x000e,0x00f7},

{0x000d,0x0002},
{0x000e,0x0005},
{0x000d,0x4002},
{0x000e,0xffff},

{0x000d,0x0002},
{0x000e,0x0006},
{0x000d,0x4002},
{0x000e,0x7777},

{0x000d,0x0002},
{0x000e,0x0008},
{0x000d,0x4002},
{0x000e,0x01e0},
	   
};


/*************************************************************
Name:	      SmdioOutputMode          
Description: 设置SMDIO为输出口
Input:	      port,pin
Return: 	void
**************************************************************/
void SmdioOutputMode(GPIO_TypeDef* smdio_GPIOx, uint16_t smdio_GPIO_Pin)
{
	GPIO_InitTypeDef gpio_dat;
	gpio_dat.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_dat.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_dat.GPIO_Pin = smdio_GPIO_Pin;	
	
	GPIO_Init( smdio_GPIOx, &gpio_dat ); 
}
/*************************************************************
Name:	      SmdioInputMode          
Description: 设置SMDIO为输入口
Input:	      port,pin
Return: 	void
**************************************************************/
void SmdioInputMode(GPIO_TypeDef* smdio_GPIOx, uint16_t smdio_GPIO_Pin)
{	
	GPIO_InitTypeDef gpio_dat;
	gpio_dat.GPIO_Mode = GPIO_Mode_IPU;
	gpio_dat.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_dat.GPIO_Pin = smdio_GPIO_Pin;
	
	GPIO_Init( smdio_GPIOx, &gpio_dat ); 

}

/*************************************************************
Name:	      InitPhyIo          
Description: 初始化PHY IO
Input:	      void
Return: 	void
**************************************************************/
void InitPhyIo(void)
{
//	EnablePower1V2;
	UsNopDelay(100);
#if 0	
	//PHY1
	SmdioInputMode(PHY1_MDIO_GPIO,PHY1_MDIO_PIN);	//MDIO Z
	GPIO_ResetBits(PHY1_MDC_GPIO,PHY1_MDC_PIN);		//MDC	low
	GPIO_SetBits(PHY1_RESET_GPIO,PHY1_RESET_PIN);  //20121217
	GPIO_SetBits(PHY1_SRESET_GPIO,PHY1_SRESET_PIN);  //20121217
	
	//PHY2
	SmdioInputMode(PHY2_MDIO_GPIO,PHY2_MDIO_PIN);	//MDIO Z
	GPIO_ResetBits(PHY2_MDC_GPIO,PHY2_MDC_PIN);		//MDC	low
	GPIO_SetBits(PHY2_RESET_GPIO,PHY2_RESET_PIN);
	GPIO_SetBits(PHY2_SRESET_GPIO,PHY2_SRESET_PIN);
	
	//PHY3
	SmdioInputMode(PHY3_MDIO_GPIO,PHY3_MDIO_PIN);	//MDIO Z
	GPIO_ResetBits(PHY3_MDC_GPIO,PHY3_MDC_PIN);		//MDC	low	
	GPIO_SetBits(PHY3_RESET_GPIO,PHY3_RESET_PIN);
	GPIO_SetBits(PHY3_SRESET_GPIO,PHY3_SRESET_PIN);
	
	//PHY4
	SmdioInputMode(PHY4_MDIO_GPIO,PHY4_MDIO_PIN);	//MDIO Z
	GPIO_ResetBits(PHY4_MDC_GPIO,PHY4_MDC_PIN);		//MDC	low	
	GPIO_SetBits(PHY4_RESET_GPIO,PHY4_RESET_PIN);
	GPIO_SetBits(PHY4_SRESET_GPIO,PHY4_SRESET_PIN);	
#endif
	//printf("0debug_phy_201311111636");
	//PHY5
	SmdioInputMode(PHY5_MDIO_GPIO,PHY5_MDIO_PIN);	//MDIO Z
	SmdioOutputMode(PHY5_MDC_GPIO,PHY5_MDC_PIN);
	GPIO_ResetBits(PHY5_MDC_GPIO,PHY5_MDC_PIN);		//MDC	low	
	GPIO_SetBits(PHY5_RESET_GPIO,PHY5_RESET_PIN);
//	GPIO_SetBits(PHY5_INT_GPIO,PHY5_INT_PIN);
	UsNopDelay(100);
	
}


/*************************************************************
Name:	      PhySmiReadIo          
Description: SMI READ
Input:	      port,pin,phy address,reg address
Return:      reg value
**************************************************************/
UINT16 PhySmiReadIo(GPIO_TypeDef* smc_GPIOx, uint16_t smc_GPIO_Pin,
						GPIO_TypeDef* smdio_GPIOx, uint16_t smdio_GPIO_Pin,
						UCHAR8 phy_addr,UCHAR8 reg_addr)
{
	UINT16 reg_value = 0,smi_addr;
	UCHAR8 i;

	smi_addr = (0x16<<10)|((phy_addr&0x1f)<<5)|(reg_addr&0x1f);	
	//
	//TRACE_INFO ("test201311121106_5_MDC_HIGH\r\n");
	SmdioOutputMode(PHY5_MDC_GPIO,PHY5_MDC_PIN);
#if 0	
	GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);		//MDC	HIGH	
	UsNopDelay(20);
	//Pull mdc LOW
	TRACE_INFO ("test201311121106_5_MDC_LOW\r\n");
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
	UsNopDelay(10);
	SmdioOutputMode(smdio_GPIOx,smdio_GPIO_Pin);
	TRACE_INFO ("test201311121106_5_MDIO_LOW\r\n");
	GPIO_ResetBits(smdio_GPIOx,smdio_GPIO_Pin);
#endif
	//Idie
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);		//MDC	low	
	UsNopDelay(20);
	//Pull mdc high
	GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);
	UsNopDelay(10);
	SmdioOutputMode(smdio_GPIOx,smdio_GPIO_Pin);
	
	//Write sfd,phy address,reg address
	for (i=0; i<15; i++)
	{
		GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);			//MCD low
		//set or reset smdio
		if (smi_addr&(0x0001<<(14-i)))
			GPIO_SetBits(smdio_GPIOx,smdio_GPIO_Pin);
		else
		 	GPIO_ResetBits(smdio_GPIOx,smdio_GPIO_Pin);
		UsNopDelay(10);

		//Pull mdc high
		GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);
		UsNopDelay(10);		
	}
	
	//TA
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);			//MCD low
	SmdioInputMode(smdio_GPIOx,smdio_GPIO_Pin);		//MDIO Z 
	UsNopDelay(10);	
	//Pull mdc high
	GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);	
	UsNopDelay(10);

	//Pull mdc low
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
	UsNopDelay(10);
	//must read 0
	GPIO_ReadInputDataBit(smdio_GPIOx,smdio_GPIO_Pin);
	//Pull mdc high
	GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);	
	UsNopDelay(10);

	// Read reg value
	reg_value = 0x0000;
	for (i=0; i<16; i++)
	{
		//Pull mdc low
		GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
		UsNopDelay(10);

		//read bit
		if (GPIO_ReadInputDataBit(smdio_GPIOx,smdio_GPIO_Pin) == Bit_SET)
			reg_value |= (0x0001<<(15-i));

		//Pull mdc high
		GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);	
		UsNopDelay(10);
	}
	//Idie
	for (i=0; i<2; i++)
	{	
		//Pull mdc low
		GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
		UsNopDelay(10);
		//Pull mdc high
		GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);	
		UsNopDelay(10);		
	}

	//end
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
 	
	return reg_value;
	
}


/*************************************************************
Name:	      PhySmiWriteIo          
Description: SMI READ
Input:	      port,pin,phy address,reg address,reg_value
Return:     void
**************************************************************/
void PhySmiWriteIo(GPIO_TypeDef* smc_GPIOx, uint16_t smc_GPIO_Pin,
						GPIO_TypeDef* smdio_GPIOx, uint16_t smdio_GPIO_Pin,
						UCHAR8 phy_addr,UCHAR8 reg_addr,UINT16 reg_value)
{
	UINT16 smi_addr;
	UCHAR8 i;

	smi_addr = (0x15<<10)|((phy_addr&0x1f)<<5)|(reg_addr&0x1f);

	//TRACE_INFO ("test201311121106_5_MDC_LOW\r\n");
	SmdioOutputMode(PHY5_MDC_GPIO,PHY5_MDC_PIN);
#if 0
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);		//MDC	HIGH	
	UsNopDelay(20);
	//Pull mdc LOW
	TRACE_INFO ("test201311121106_5_MDC_HIGH\r\n");
	GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);
	UsNopDelay(10);
	SmdioOutputMode(smdio_GPIOx,smdio_GPIO_Pin);
	TRACE_INFO ("test201311121106_5_MDIO_HIGH\r\n");
	GPIO_SetBits(smdio_GPIOx,smdio_GPIO_Pin);
#endif
	//Idie
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);		//MDC	low	
	UsNopDelay(20);
	//Pull mdc high
	GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);
	UsNopDelay(10);
	SmdioOutputMode(smdio_GPIOx,smdio_GPIO_Pin);
	
	//Write sfd,phy address,reg address
	for (i=0; i<15; i++)
	{
		GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);			//MCD low
		//set or reset smdio
		if (smi_addr&(0x0001<<(14-i)))
			GPIO_SetBits(smdio_GPIOx,smdio_GPIO_Pin);
		else
			GPIO_ResetBits(smdio_GPIOx,smdio_GPIO_Pin);
		UsNopDelay(10);

		//Pull mdc high
		GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);
		UsNopDelay(10);		
	}
	//TA,Send 1,0
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);			//MCD low
	GPIO_SetBits(smdio_GPIOx,smdio_GPIO_Pin);
	UsNopDelay(10);	
	//Pull mdc high
	GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);	
	UsNopDelay(10);

	//Pull mdc low
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
	UsNopDelay(10);
	GPIO_ResetBits(smdio_GPIOx,smdio_GPIO_Pin);
	//Pull mdc high
	GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);	
	UsNopDelay(10);

	// Write reg value
	for (i=0; i<16; i++)
	{
		//Pull mdc low
		GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
		UsNopDelay(10);

		if (reg_value&(0x0001<<(15-i)))
			GPIO_SetBits(smdio_GPIOx,smdio_GPIO_Pin);
		else
			GPIO_ResetBits(smdio_GPIOx,smdio_GPIO_Pin);
		//Pull mdc high
		GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);	
		UsNopDelay(10);
	}
	SmdioInputMode(smdio_GPIOx,smdio_GPIO_Pin);		//MDIO Z 
	//Idie
	for (i=0; i<2; i++)
	{	
		//Pull mdc low
		GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
		UsNopDelay(10);
		//Pull mdc high
		GPIO_SetBits(smc_GPIOx,smc_GPIO_Pin);	
		UsNopDelay(10);		
	}

	//end
	GPIO_ResetBits(smc_GPIOx,smc_GPIO_Pin);
	
}
/*************************************************************
Name:	      PhyRead          
Description: 从PHY芯片读取寄存器
Input:	      PHY芯片,PHY地址(针对多个PHY),寄存器地址
Return:     寄存器数据
**************************************************************/
UINT16 PhyRead(UCHAR8 phy_id,UCHAR8 phy_addr,UCHAR8 reg_addr)
{
	switch(phy_id)
	{
		#if 0
		case PHY1_VCS8224_1:
			return PhySmiReadIo(PHY1_MDC_GPIO,PHY1_MDC_PIN,PHY1_MDIO_GPIO,PHY1_MDIO_PIN,
								phy_addr,reg_addr);
		break;

		case PHY2_VCS8224_2:
			return PhySmiReadIo(PHY2_MDC_GPIO,PHY2_MDC_PIN,PHY2_MDIO_GPIO,PHY2_MDIO_PIN,
								phy_addr,reg_addr);			
		break;

		case PHY3_VCS8601:
			return PhySmiReadIo(PHY3_MDC_GPIO,PHY3_MDC_PIN,PHY3_MDIO_GPIO,PHY3_MDIO_PIN,
								phy_addr,reg_addr);			
		break;
		#endif

		case PHY4_VCS8662:
			return PhySmiReadIo(PHY4_MDC_GPIO,PHY4_MDC_PIN,PHY4_MDIO_GPIO,PHY4_MDIO_PIN,
								phy_addr,reg_addr);	
		case PHY5_KSZ9031:
			return PhySmiReadIo(PHY5_MDC_GPIO,PHY5_MDC_PIN,PHY5_MDIO_GPIO,PHY5_MDIO_PIN,
								phy_addr,reg_addr);	
		
		break;	
		
	}
}

/*************************************************************
Name:	      PhyWrite          
Description: 向PHY芯片写寄存器
Input:	      PHY芯片,PHY地址(针对多个PHY),寄存器地址，寄存器数据
Return:     void
**************************************************************/
void PhyWrite(UCHAR8 phy_id,UCHAR8 phy_addr,UCHAR8 reg_addr,UINT16 reg_value)
{
	
	switch(phy_id)
	{
		#if 0
		case PHY1_VCS8224_1:
			PhySmiWriteIo(PHY1_MDC_GPIO,PHY1_MDC_PIN,PHY1_MDIO_GPIO,PHY1_MDIO_PIN,
								phy_addr,reg_addr,reg_value);
			
		break;

		case PHY2_VCS8224_2:
			PhySmiWriteIo(PHY2_MDC_GPIO,PHY2_MDC_PIN,PHY2_MDIO_GPIO,PHY2_MDIO_PIN,
								phy_addr,reg_addr,reg_value);			
		break;

		case PHY3_VCS8601:
			PhySmiWriteIo(PHY3_MDC_GPIO,PHY3_MDC_PIN,PHY3_MDIO_GPIO,PHY3_MDIO_PIN,
								phy_addr,reg_addr,reg_value);			
		break;
		#endif
		
		case PHY4_VCS8662:
			PhySmiWriteIo(PHY4_MDC_GPIO,PHY4_MDC_PIN,PHY4_MDIO_GPIO,PHY4_MDIO_PIN,
								phy_addr,reg_addr,reg_value);		
		break;	
		
		case PHY5_KSZ9031:
			PhySmiWriteIo(PHY5_MDC_GPIO,PHY5_MDC_PIN,PHY5_MDIO_GPIO,PHY5_MDIO_PIN,
								phy_addr,reg_addr,reg_value);		
		break;	
		
	}	
}

void HardResetPhy(UCHAR8 phy_id)
{
	UsNopDelay(100);
	switch(phy_id)
	{
		#if 0
		case PHY1_VCS8224_1:
			GPIO_ResetBits(PHY1_RESET_GPIO,PHY1_RESET_PIN);
			UsNopDelay(100);
			GPIO_SetBits(PHY1_RESET_GPIO,PHY1_RESET_PIN);
			UsNopDelay(100);
		break;

		case PHY2_VCS8224_2:
			GPIO_ResetBits(PHY2_RESET_GPIO,PHY2_RESET_PIN);
			UsNopDelay(100);
			GPIO_SetBits(PHY2_RESET_GPIO,PHY2_RESET_PIN);
			UsNopDelay(100);		
			break;

		case PHY3_VCS8601:
			GPIO_ResetBits(PHY3_RESET_GPIO,PHY3_RESET_PIN);
			UsNopDelay(100);
			GPIO_SetBits(PHY3_RESET_GPIO,PHY3_RESET_PIN);
			UsNopDelay(100);		
			break;
		#endif

		case PHY4_VCS8662:
			GPIO_ResetBits(PHY4_RESET_GPIO,PHY4_RESET_PIN);
			UsNopDelay(100);
			GPIO_SetBits(PHY4_RESET_GPIO,PHY4_RESET_PIN);
			UsNopDelay(100);
			break;	
		case PHY5_KSZ9031:
			//printf("1debug_phy_201311111636");
			GPIO_ResetBits(PHY5_RESET_GPIO,PHY5_RESET_PIN);
			UsNopDelay(100);
			GPIO_SetBits(PHY5_RESET_GPIO,PHY5_RESET_PIN);
			UsNopDelay(100);
			break;	
		
	}		
}

/*************************************************************
Name:	      InitPhy          
Description: 初始化PHY IO
Input:	      
Return: 	void
**************************************************************/
UCHAR8 InitPhyReg( UCHAR8 phy_id  )
{
	UINT16 i;
	CHAR8 j,k; //test
	UsNopDelay(100);
	switch(phy_id)
	{
		#if 0
		case PHY1_VCS8224_1:
			for (i=0; i<(sizeof(phyRegVal)/(2*sizeof(phyRegVal[0][0])));i++)
			{ 
				PhyWrite(PHY1_VCS8224_1,(phyRegVal[i][0]&0xff00)>>8,(phyRegVal[i][0]&0xff),phyRegVal[i][1]);
				UsNopDelay(10);
			} 

		case PHY2_VCS8224_2:
			for (i=0; i<(sizeof(phyRegVal)/(2*sizeof(phyRegVal[0][0])));i++)
			{ 
				PhyWrite(PHY2_VCS8224_2,(phyRegVal[i][0]&0xff00)>>8,(phyRegVal[i][0]&0xff),phyRegVal[i][1]);
				UsNopDelay(10);
			} 		
		break;

		case PHY3_VCS8601:
			for (i=0; i<(sizeof(phyRegVal)/(2*sizeof(phyRegVal[0][0])));i++)
			{ 
				PhyWrite(PHY3_VCS8601,(phyRegVal[i][0]&0xff00)>>8,(phyRegVal[i][0]&0xff),phyRegVal[i][1]);
				UsNopDelay(10);
			} 		
		break;
		#endif
#if 0
		case PHY4_VCS8662:
			for (i=0; i<(sizeof(phy4RegVal)/(2*sizeof(phy4RegVal[0][0])));i++)
			{ 
//				j=((phy4RegVal[i][0]&0xff00)>>8);
//				k=(phy4RegVal[i][0]&0xff);
//				TRACE_INFO("j=(%02x),k=(%02x),val=(%04x)\r\n",j,k,phy4RegVal[i][1]);
				
				PhyWrite(PHY4_VCS8662,((phy4RegVal[i][0]&0xff00)>>8),(phy4RegVal[i][0]&0xff),phy4RegVal[i][1]);
				UsNopDelay(10);
			} 
			
			TRACE_INFO("0x0017=(%02x),0x0117=(%02x)\r\n",PhyRead(PHY4_VCS8662,0,0x17),PhyRead(PHY4_VCS8662,1,0x17));

				PhyWrite(PHY4_VCS8662,0,0x17,0x100c);
				UsNopDelay(10);

//				PhyWrite(PHY4_VCS8662,0,0x0,0x9140);
				UsNopDelay(10);
				
//				PhyWrite(PHY4_VCS8662,0,0x0,0x1140);
				UsNopDelay(10);
				
			TRACE_INFO("-----0x0017=(%02x),0x0117=(%02x)\r\n",PhyRead(PHY4_VCS8662,0,0x17),PhyRead(PHY4_VCS8662,1,0x17));
#endif 

		break;	

		case PHY5_KSZ9031:
			for (i=0; i<(sizeof(phy5RegVal)/(2*sizeof(phy5RegVal[0][0])));i++)
			{ 
//				j=((phy4RegVal[i][0]&0xff00)>>8);
//				k=(phy4RegVal[i][0]&0xff);
//				TRACE_INFO("j=(%02x),k=(%02x),val=(%04x)\r\n",j,k,phy4RegVal[i][1]);
				
				PhyWrite(PHY5_KSZ9031,((phy5RegVal[i][0]&0xff00)>>8),(phy5RegVal[i][0]&0xff),phy5RegVal[i][1]);
				UsNopDelay(10);
			} 
#if 0			
			TRACE_INFO("0x0017=(%02x),0x0117=(%02x)\r\n",PhyRead(PHY4_VCS8662,0,0x17),PhyRead(PHY4_VCS8662,1,0x17));

				PhyWrite(PHY4_VCS8662,0,0x17,0x100c);
				UsNopDelay(10);

//				PhyWrite(PHY4_VCS8662,0,0x0,0x9140);
				UsNopDelay(10);
				
//				PhyWrite(PHY4_VCS8662,0,0x0,0x1140);
				UsNopDelay(10);
				
			TRACE_INFO("-----0x0017=(%02x),0x0117=(%02x)\r\n",PhyRead(PHY4_VCS8662,0,0x17),PhyRead(PHY4_VCS8662,1,0x17));
#endif 

		break;	
		
	}
return 0;
	
}
#if 0
//configuration 9524 and phy
//void Config_Phy4_Serdes(UCHAR8 phy_id)
void Config_Phy4_Serdes()
{
	UINT16 temp;
	temp=FpgaReadRegister(0x077);
	
	TRACE_INFO("temp(%04x)\r\n",temp);
	if((Phy4_Serdes_St&0x01)!=(temp&0x01))
	{
		TRACE_INFO("test1\r\n");		
		if((temp&0x01)!=0x00)
		{
			TRACE_INFO("test2\r\n");
//			if((Phy4_Serdes_St&0x01)!=(temp&0x01))
			{
				Ad9524Write(0x001c,0x08);
				UsNopDelay(10);
				
				Ad9524Write(0x001a,0x0c);
				UsNopDelay(10);
				
				Ad9524Write(0x0234,0x01);
				UsNopDelay(10);
			}
			Phy4_Serdes_St=Phy4_Serdes_St|0x01;
		}
		else 
		{	
			TRACE_INFO("test3\r\n");
	
//			if(((Phy4_Serdes_St&0x01)!=(temp&0x01))&&((Phy4_Serdes_St&0x01)==0))
			{
				Ad9524Write(0x001c,0x0C);
				UsNopDelay(10);
				
				Ad9524Write(0x001a,0x14);
				UsNopDelay(10);
				
				Ad9524Write(0x0234,0x01);
				UsNopDelay(10);
			}
			Phy4_Serdes_St=Phy4_Serdes_St&(0xfffe);
		}


	}
	PhyWrite(PHY4_VCS8662,0,0x1f,0x10);
	UsNopDelay(10);	
//	if((Phy4_Serdes_St&0x02)!=(temp&0x02))
	if(((Phy4_Serdes_St&0x02)!=(temp&0x02))||((0X9131!=PhyRead(PHY4_VCS8662,0x00,0x17))&&(0X8131!=PhyRead(PHY4_VCS8662,0x00,0x17))))
	{
				TRACE_INFO("test4\r\n");
				PhyWrite(PHY4_VCS8662,0,0X1F,0X0010);
//				UsNopDelay(30);
//				PhySmiWriteIo(PHY4_MDC_GPIO,PHY4_MDC_PIN,PHY4_MDIO_GPIO,PHY4_MDIO_PIN,
//								0X00,0X1F,0X0010);
				UsNopDelay(10);
				if((temp&0x02)!=0x00)
				{
					TRACE_INFO("test5\r\n");
//					PhySmiWriteIo(PHY4_MDC_GPIO,PHY4_MDC_PIN,PHY4_MDIO_GPIO,PHY4_MDIO_PIN,
//								0X00,0X17,0X9131);
					PhyWrite(PHY4_VCS8662,0,0X17,0X9131);
					UsNopDelay(10);
					Phy4_Serdes_St=Phy4_Serdes_St|0x02;
				}
				else
				{
					TRACE_INFO("test6\r\n");
//					PhySmiWriteIo(PHY4_MDC_GPIO,PHY4_MDC_PIN,PHY4_MDIO_GPIO,PHY4_MDIO_PIN,
//								0X00,0X17,0X8131);
					PhyWrite(PHY4_VCS8662,0,0X17,0X8131);
					UsNopDelay(10);
					Phy4_Serdes_St=Phy4_Serdes_St&(0xfffd);
				}

//		Phy4_Serdes_St=temp;

	}
	PhyWrite(PHY4_VCS8662,0,0x1f,0x00);
	UsNopDelay(10);	
	Phy4_Serdes_St=temp;
	
}

void UplinkHandle()
{
	UINT16 temp;
	temp=FpgaReadRegister(0x78);
	if ((0==(temp&(0x01<<6)))&&(0==(temp&(0x01<<7))))
	{
		PhyWrite(PHY4_VCS8662,0,0x1f,0x00);
		UsNopDelay(10);	

		PhyWrite(PHY4_VCS8662,0,0x00,0x9140);
		UsNopDelay(10);	
		PhyWrite(PHY4_VCS8662,0,0x00,0x1140);
		UsNopDelay(10);	
	}

}
#endif 






  
#include "spiflash_drv.h"


/***********************************************************************************
       W25Xϵ��SPI FLASH�洢���洢�ṹ����
- ÿ256bytesΪһ��Page��ÿ4KbytesΪһ��Sector��ÿ16������Ϊ1��Block
- W25X16����Ϊ2M�ֽ�,����32��Block, 512��Sector  , 8192��Page
- W25X32����Ϊ4M�ֽ�,����64��Block, 1024��Sector ,16384��Page
- W25X64����Ϊ8M�ֽ�,����128��Block,2048��Sector ,32768��Page
**********************************************************************************************/

static u8_t SPIx_ReadWriteByte(u8_t TxData);

/***************************************************************************************
*  STM32 SPI ��ʼ��
*/
void SPI_FLASH_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  //SPI CS
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�����������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ8
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
	
	SPIx_ReadWriteByte(0xff);//��������		 
}   



/**************************************************************************************************************
*  SPIx ��дһ���ֽ�        TxData:Ҫд����ֽ�
*  ����ֵ:��ȡ�����ֽ�
*/
static u8_t SPIx_ReadWriteByte(u8_t TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����					    
}


/*****************************************************
* ��ȡSPI_FLASH��״̬�Ĵ���
* BIT7  6   5   4   3   2   1   0
* SPR   RV  TB BP2 BP1 BP0 WEL BUSY
* SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
* TB,BP2,BP1,BP0:FLASH����д��������
* WEL:дʹ������
* BUSY:æ���λ(1,æ;0,����)
* Ĭ��:0x00
*/
static u8_t SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	SPI_FLASH_CS_LOW();                            //ʹ������   
	SPIx_ReadWriteByte(W25X_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPIx_ReadWriteByte(0Xff);             //��ȡһ���ֽ�  
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     
	return byte;   
} 

/*********************************************************************
* SPI_FLASHдʹ��	, ��WEL��λ 
*/  
static void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS_LOW();                            //ʹ������   
	SPIx_ReadWriteByte(W25X_WriteEnable);      //����дʹ��  
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     	      
} 

/*********************************************************************
*  �ȴ�SPI FLASH ����
*/  
static void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  



/**********************************************************************
*  ��ȡоƬID W25X16��ID:0XEF14
*/
u16_t SPI_Flash_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_FLASH_CS_LOW();				    
	SPIx_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	 			   
	Temp|=SPIx_ReadWriteByte(0xFF)<<8;  
	Temp|=SPIx_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS_HIGH();				    
	return Temp;
}   		    


/********************************************************
* ��������оƬ  W25X16:25s  W25X32:40s  W25X64:40s
*/
void SPI_Flash_Erase_Chip(void)   
{                                             
	SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_LOW();                            //ʹ������   
	SPIx_ReadWriteByte(W25X_ChipErase);        //����Ƭ��������  
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     	      
	SPI_Flash_Wait_Busy();   				   //�ȴ�оƬ��������
}   



/****************************************************************************
*  ��ָ������ʼ��ַ����ȡָ�����ȵ����� (�ļ�ϵͳ�ӿں���)
*  pBuffer:���ݴ洢��   ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
*  NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
*/
s32_t SPI_Flash_Read(u32_t ReadAddr,u32_t NumByteToRead,u8_t * pBuffer)   
{ 
 	u16 i;    												    
	SPI_FLASH_CS_LOW();                            //ʹ������   
	SPIx_ReadWriteByte(W25X_ReadData);         //���Ͷ�ȡ����   
	SPIx_ReadWriteByte((u8_t)((ReadAddr)>>16));  //����24bit��ַ    
	SPIx_ReadWriteByte((u8_t)((ReadAddr)>>8));   
	SPIx_ReadWriteByte((u8_t)ReadAddr);   
	for(i=0;i<NumByteToRead;i++){ 
		pBuffer[i]=SPIx_ReadWriteByte(0XFF);   //ѭ������  
	}
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     

	return 0;		
} 


/**************************************************************************************
*  ��ָ������ʼ��ַ����ʼд�����256�ֽڵ����� (�ļ�ϵͳ�ӿں���)
*  pBuffer:���ݴ洢��  WriteAddr:��ʼд��ĵ�ַ(24bit)
*  NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
*/
s32_t SPI_Flash_Write(u32_t WriteAddr,u32_t NumByteToWrite,u8_t * pBuffer)
{
 	u16 i;  
	SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_FLASH_CS_LOW();                            //ʹ������   
	SPIx_ReadWriteByte(W25X_PageProgram);      //����дҳ����   
	SPIx_ReadWriteByte((u8)((WriteAddr)>>16)); //����24bit��ַ    
	SPIx_ReadWriteByte((u8)((WriteAddr)>>8));   
	SPIx_ReadWriteByte((u8)WriteAddr);
	
	for(i=0;i<NumByteToWrite;i++)
		SPIx_ReadWriteByte(pBuffer[i]);//ѭ��д��  
	
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ 
	SPI_Flash_Wait_Busy();					       //�ȴ�д�����
	
	return 0;
} 

/*************************************************************************************
*   ����������� (�ļ�ϵͳ�ӿں���)
*   Addr ��������ʼ��ַ  
*   Num �� Ҫ������������
*/
s32_t SPI_Flash_Erase(u32_t Addr,u32_t Num)   
{   
	  
	u32_t secpos;
	u32_t Address;
	u32_t i;
	secpos = Addr/4096; //������ַ (��������ĵ�ַ���ڵڼ�������)
	
	for(i=0;i<Num;i++) {
		Address = secpos * 4096;        //��������������������ʼ��ַ
		SPI_FLASH_Write_Enable();                  //SET WEL 	 
		SPI_Flash_Wait_Busy();   
		SPI_FLASH_CS_LOW();                        //ʹ������   
		SPIx_ReadWriteByte(W25X_SectorErase);      //������������ָ�� 
		SPIx_ReadWriteByte((u8_t)((Address)>>16));  //����24bit��ַ    
		SPIx_ReadWriteByte((u8_t)((Address)>>8));   
		SPIx_ReadWriteByte((u8_t)Address);  
		SPI_FLASH_CS_HIGH();                        //ȡ��Ƭѡ     	      
		SPI_Flash_Wait_Busy();   				            //�ȴ��������
		secpos++;	
	}
	  
	return 0;
}  




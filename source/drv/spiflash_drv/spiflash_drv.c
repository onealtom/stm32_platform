  
#include "spiflash_drv.h"


/***********************************************************************************
       W25X系列SPI FLASH存储器存储结构介绍
- 每256bytes为一个Page，每4Kbytes为一个Sector，每16个扇区为1个Block
- W25X16容量为2M字节,共有32个Block, 512个Sector  , 8192个Page
- W25X32容量为4M字节,共有64个Block, 1024个Sector ,16384个Page
- W25X64容量为8M字节,共有128个Block,2048个Sector ,32768个Page
**********************************************************************************************/

static u8_t SPIx_ReadWriteByte(u8_t TxData);

/***************************************************************************************
*  STM32 SPI 初始化
*/
void SPI_FLASH_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  //SPI CS
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;		//定义波特率预分频的值:波特率预分频值为8
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
	
	SPIx_ReadWriteByte(0xff);//启动传输		 
}   



/**************************************************************************************************************
*  SPIx 读写一个字节        TxData:要写入的字节
*  返回值:读取到的字节
*/
static u8_t SPIx_ReadWriteByte(u8_t TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据					    
}


/*****************************************************
* 读取SPI_FLASH的状态寄存器
* BIT7  6   5   4   3   2   1   0
* SPR   RV  TB BP2 BP1 BP0 WEL BUSY
* SPR:默认0,状态寄存器保护位,配合WP使用
* TB,BP2,BP1,BP0:FLASH区域写保护设置
* WEL:写使能锁定
* BUSY:忙标记位(1,忙;0,空闲)
* 默认:0x00
*/
static u8_t SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	SPI_FLASH_CS_LOW();                            //使能器件   
	SPIx_ReadWriteByte(W25X_ReadStatusReg);    //发送读取状态寄存器命令    
	byte=SPIx_ReadWriteByte(0Xff);             //读取一个字节  
	SPI_FLASH_CS_HIGH();                            //取消片选     
	return byte;   
} 

/*********************************************************************
* SPI_FLASH写使能	, 将WEL置位 
*/  
static void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS_LOW();                            //使能器件   
	SPIx_ReadWriteByte(W25X_WriteEnable);      //发送写使能  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
} 

/*********************************************************************
*  等待SPI FLASH 空闲
*/  
static void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}  



/**********************************************************************
*  读取芯片ID W25X16的ID:0XEF14
*/
u16_t SPI_Flash_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_FLASH_CS_LOW();				    
	SPIx_ReadWriteByte(0x90);//发送读取ID命令	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	 			   
	Temp|=SPIx_ReadWriteByte(0xFF)<<8;  
	Temp|=SPIx_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS_HIGH();				    
	return Temp;
}   		    


/********************************************************
* 擦除整个芯片  W25X16:25s  W25X32:40s  W25X64:40s
*/
void SPI_Flash_Erase_Chip(void)   
{                                             
	SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_LOW();                            //使能器件   
	SPIx_ReadWriteByte(W25X_ChipErase);        //发送片擦除命令  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
	SPI_Flash_Wait_Busy();   				   //等待芯片擦除结束
}   



/****************************************************************************
*  在指定的起始地址处读取指定长度的数据 (文件系统接口函数)
*  pBuffer:数据存储区   ReadAddr:开始读取的地址(24bit)
*  NumByteToRead:要读取的字节数(最大65535)
*/
s32_t SPI_Flash_Read(u32_t ReadAddr,u32_t NumByteToRead,u8_t * pBuffer)   
{ 
 	u16 i;    												    
	SPI_FLASH_CS_LOW();                            //使能器件   
	SPIx_ReadWriteByte(W25X_ReadData);         //发送读取命令   
	SPIx_ReadWriteByte((u8_t)((ReadAddr)>>16));  //发送24bit地址    
	SPIx_ReadWriteByte((u8_t)((ReadAddr)>>8));   
	SPIx_ReadWriteByte((u8_t)ReadAddr);   
	for(i=0;i<NumByteToRead;i++){ 
		pBuffer[i]=SPIx_ReadWriteByte(0XFF);   //循环读数  
	}
	SPI_FLASH_CS_HIGH();                            //取消片选     

	return 0;		
} 


/**************************************************************************************
*  在指定的起始地址处开始写入最大256字节的数据 (文件系统接口函数)
*  pBuffer:数据存储区  WriteAddr:开始写入的地址(24bit)
*  NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
*/
s32_t SPI_Flash_Write(u32_t WriteAddr,u32_t NumByteToWrite,u8_t * pBuffer)
{
 	u16 i;  
	SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_FLASH_CS_LOW();                            //使能器件   
	SPIx_ReadWriteByte(W25X_PageProgram);      //发送写页命令   
	SPIx_ReadWriteByte((u8)((WriteAddr)>>16)); //发送24bit地址    
	SPIx_ReadWriteByte((u8)((WriteAddr)>>8));   
	SPIx_ReadWriteByte((u8)WriteAddr);
	
	for(i=0;i<NumByteToWrite;i++)
		SPIx_ReadWriteByte(pBuffer[i]);//循环写数  
	
	SPI_FLASH_CS_HIGH();                            //取消片选 
	SPI_Flash_Wait_Busy();					       //等待写入结束
	
	return 0;
} 

/*************************************************************************************
*   擦除多个扇区 (文件系统接口函数)
*   Addr ：擦除起始地址  
*   Num ： 要擦除扇区个数
*/
s32_t SPI_Flash_Erase(u32_t Addr,u32_t Num)   
{   
	  
	u32_t secpos;
	u32_t Address;
	u32_t i;
	secpos = Addr/4096; //扇区地址 (计算给定的地址处于第几个扇区)
	
	for(i=0;i<Num;i++) {
		Address = secpos * 4096;        //根据扇区计算扇区的起始地址
		SPI_FLASH_Write_Enable();                  //SET WEL 	 
		SPI_Flash_Wait_Busy();   
		SPI_FLASH_CS_LOW();                        //使能器件   
		SPIx_ReadWriteByte(W25X_SectorErase);      //发送扇区擦除指令 
		SPIx_ReadWriteByte((u8_t)((Address)>>16));  //发送24bit地址    
		SPIx_ReadWriteByte((u8_t)((Address)>>8));   
		SPIx_ReadWriteByte((u8_t)Address);  
		SPI_FLASH_CS_HIGH();                        //取消片选     	      
		SPI_Flash_Wait_Busy();   				            //等待擦除完成
		secpos++;	
	}
	  
	return 0;
}  




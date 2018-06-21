#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f10x.h"
#include "spiffs.h"

//#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
//#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)


//指令表
#define W25X_WriteEnable		  0x06 
#define W25X_WriteDisable		  0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			    0x03 
#define W25X_FastReadData		  0x0B 
#define W25X_FastReadDual		  0x3B 
#define W25X_PageProgram		  0x02 
#define W25X_BlockErase			  0xD8 
#define W25X_SectorErase		  0x20 
#define W25X_ChipErase			  0xC7 
#define W25X_PowerDown			  0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			    0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

u16_t  SPI_Flash_ReadID(void);  	    //读取FLASH ID
void SPI_Flash_Erase_Chip(void);    	  //整片擦除

//文件系统接口函数
s32_t SPI_Flash_Read(u32_t ReadAddr,u32_t NumByteToRead,u8_t * pBuffer);   //读取flash
s32_t SPI_Flash_Write(u32_t WriteAddr,u32_t NumByteToWrite,u8_t * pBuffer);//写入flash
s32_t SPI_Flash_Erase(u32_t Addr,u32_t Num) ;

#endif /* __SPI_FLASH_H */


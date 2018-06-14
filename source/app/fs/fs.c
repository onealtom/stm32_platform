
#include "stm32f10x.h"		
#include "stdio.h"
#include "spiflash_drv.h"


 spiffs SPIFlashFS;
 static u8_t FS_Work_Buf[SPIFLASH_CFG_LOG_PAGE_SZ*2];
 static u8_t FS_FDS[32*4];
 static u8_t FS_Cache_Buf[(SPIFLASH_CFG_LOG_PAGE_SZ+32)*4];
 
 
 /***********************************************
 *   加载SPI FLASH文件系统
#define  SPIFLASH_CFG_PHYS_SZ               (1024*1024*8)    //FLASH总容量 应该是分区的容量
#define  SPIFLASH_CFG_PHYS_ERASE_SZ         (65536)          //FLASH擦除的最大容量(W25X系列可以按块擦除，一块的容量是65535字节)
#define  SPIFLASH_CFG_PHYS_ADDR             (8388608)           //起始地址 分区的其实地址，从16M的后半开始用，size8M，32768page*256byte/page=8MByte 
#define  SPIFLASH_CFG_LOG_PAGE_SZ           (256)            //FLASH页容量(W25X系列一页的容量是256字节)
#define  SPIFLASH_CFG_LOG_BLOCK_SZ          (65536)          //FLASH块容量(W25X系列一块的容量是65535字节)
 */
void Mount_SPI_Flash_File_System(void) 
{
	spiffs_config SPIFlashCfg;
	
	SPIFlashCfg.phys_size        = (1024*1024*8);        		// SPI Flash的总容量
	SPIFlashCfg.phys_addr        = 8388608;       			// 起始地址
	SPIFlashCfg.phys_erase_block = 65536;   			// FLASH最大可擦除的块大小(W25X64可以按扇区擦除(4K)或者按块擦除(64K))
	SPIFlashCfg.log_block_size   = 65536;   				// 块的大小(W25X64每块包含16个扇区，每个扇区4K字节，每块的总容量为：16X4=64K=65535字节)
	SPIFlashCfg.log_page_size    = 256;    				//  (W25X64每页包含256个字节，16个页构成一个扇区)
    
	SPIFlashCfg.hal_read_f =  SPI_Flash_Read;    //读
	SPIFlashCfg.hal_write_f = SPI_Flash_Write;   //写
	SPIFlashCfg.hal_erase_f = SPI_Flash_Erase;   //擦除

	//挂载SPIFS
	int res = SPIFFS_mount(&SPIFlashFS,
                           &SPIFlashCfg,
                           FS_Work_Buf,
                           FS_FDS,
                           sizeof(FS_FDS),
                           FS_Cache_Buf,
                           sizeof(FS_Cache_Buf),
                           0);
 
}

//char WriteBuf[]={"Hi,Budy! if you get this Message......Congratulations!You have succeeded!!"};
  char WriteBuf2[]={"                                                                          "};
char ReadBuf[80];	

int fs_test(void)
{
	//SPI_FLASH_Init();   //FLASH存储器初始化 设备已经初始化过了
	Mount_SPI_Flash_File_System( );//spi flash文件系统初始化

	//打开文件，如果文件不存在，自动创建
	printf("fs1\r\n");
	spiffs_file fd = SPIFFS_open(&SPIFlashFS, "my_file", SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR, 0);

	printf("fs2\r\n");
	//写文件
	//if (SPIFFS_write(&SPIFlashFS, fd, WriteBuf, sizeof(WriteBuf)) < 0)
	//	printf("errno %i\n", SPIFFS_errno(&SPIFlashFS));
//SPIFFS_close(&SPIFlashFS, fd);
  
	printf("fs3\r\n");
	//读文件
	fd = SPIFFS_open(&SPIFlashFS, "my_file", SPIFFS_RDWR, 0);
	if (SPIFFS_read(&SPIFlashFS, fd, ReadBuf, sizeof(WriteBuf2)) < 0)
		printf("errno %i\n", SPIFFS_errno(&SPIFlashFS));
	SPIFFS_close(&SPIFlashFS, fd);
  
	printf("fs4\r\n");
	//打印输出文件内容
	printf("%s\n", ReadBuf);

}


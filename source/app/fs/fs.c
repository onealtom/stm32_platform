
#include "stm32f10x.h"		
#include "stdio.h"
#include "spiflash_drv.h"


 spiffs SPIFlashFS;
 static u8_t FS_Work_Buf[SPIFLASH_CFG_LOG_PAGE_SZ*2];
 static u8_t FS_FDS[32*4];
 static u8_t FS_Cache_Buf[(SPIFLASH_CFG_LOG_PAGE_SZ+32)*4];
 
 
 /***********************************************
 *   ����SPI FLASH�ļ�ϵͳ
 */
  void Mount_SPI_Flash_File_System(void) 
{
	spiffs_config SPIFlashCfg;
	SPIFlashCfg.phys_size        = SPIFLASH_CFG_PHYS_SZ;         // SPI Flash��������
	SPIFlashCfg.phys_addr        = SPIFLASH_CFG_PHYS_ADDR;       // ��ʼ��ַ
	SPIFlashCfg.phys_erase_block = SPIFLASH_CFG_PHYS_ERASE_SZ;   // FLASH���ɲ����Ŀ��С(W25X64���԰���������(4K)���߰������(64K))
	SPIFlashCfg.log_block_size   = SPIFLASH_CFG_LOG_BLOCK_SZ;   // ��Ĵ�С(W25X64ÿ�����16��������ÿ������4K�ֽڣ�ÿ���������Ϊ��16X4=64K=65535�ֽ�)
	SPIFlashCfg.log_page_size    = SPIFLASH_CFG_LOG_PAGE_SZ;    //  (W25X64ÿҳ����256���ֽڣ�16��ҳ����һ������)
    
	SPIFlashCfg.hal_read_f =  SPI_Flash_Read;    //��
	SPIFlashCfg.hal_write_f = SPI_Flash_Write;   //д
	SPIFlashCfg.hal_erase_f = SPI_Flash_Erase;   //����
printf("%s(%d) %s\n",__FILE__,__LINE__,__FUNCTION__);
	//����SPIFS	
	int res = SPIFFS_mount(&SPIFlashFS,
                           &SPIFlashCfg,
                           FS_Work_Buf,
                           FS_FDS,
                           sizeof(FS_FDS),
                           FS_Cache_Buf,
                           sizeof(FS_Cache_Buf),
                           0);
 
  }


	
char WriteBuf[]={"Hi,Budy! if you get this Message......Congratulations!You have succeeded!!"};
char ReadBuf[80];	

int fs_test(void)
{
	//SPI_FLASH_Init();   //FLASH�洢����ʼ�� �豸�Ѿ���ʼ������
	Mount_SPI_Flash_File_System( );//spi flash�ļ�ϵͳ��ʼ��

	//���ļ�������ļ������ڣ��Զ�����
	printf("fs1\r\n");
	spiffs_file fd = SPIFFS_open(&SPIFlashFS, "my_file", SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR, 0);
	
	printf("fs2\r\n");
	//д�ļ�
	if (SPIFFS_write(&SPIFlashFS, fd, WriteBuf, sizeof(WriteBuf)) < 0)
		printf("errno %i\n", SPIFFS_errno(&SPIFlashFS));
	SPIFFS_close(&SPIFlashFS, fd);
  
	printf("fs3\r\n");
	//���ļ�
	fd = SPIFFS_open(&SPIFlashFS, "my_file", SPIFFS_RDWR, 0);
	if (SPIFFS_read(&SPIFlashFS, fd, ReadBuf, sizeof(WriteBuf)) < 0)
		printf("errno %i\n", SPIFFS_errno(&SPIFlashFS));
	SPIFFS_close(&SPIFlashFS, fd);
  
	printf("fs4\r\n");
	//��ӡ����ļ�����
	printf("%s\n", ReadBuf);
	
	while(1){
		//Nothing to do..........
	}
	
}



#include "stm32f10x.h"		
#include "stdio.h"
#include "spiflash_drv.h"


spiffs SPIFlashFS;
spiffs sfblk0p1;  //����1

static u8_t FS_Work_Buf[SPIFLASH_CFG_LOG_PAGE_SZ*2];
static u8_t FS_FDS[32*4];
static u8_t FS_Cache_Buf[(SPIFLASH_CFG_LOG_PAGE_SZ+32)*4];
 
char * r_fstring( char *filename);
 
 /***********************************************
 *   ����SPI FLASH�ļ�ϵͳ
#define  SPIFLASH_CFG_PHYS_SZ               (1024*1024*8)    //FLASH������ Ӧ���Ƿ���������
#define  SPIFLASH_CFG_PHYS_ERASE_SZ         (65536)          //FLASH�������������(W25Xϵ�п��԰��������һ���������65535�ֽ�)
#define  SPIFLASH_CFG_PHYS_ADDR             (8388608)           //��ʼ��ַ ��������ʵ��ַ����16M�ĺ�뿪ʼ�ã�size8M��32768page*256byte/page=8MByte 
#define  SPIFLASH_CFG_LOG_PAGE_SZ           (256)            //FLASHҳ����(W25Xϵ��һҳ��������256�ֽ�)
#define  SPIFLASH_CFG_LOG_BLOCK_SZ          (65536)          //FLASH������(W25Xϵ��һ���������65535�ֽ�)
 */
void Mount_SPI_Flash_File_System(void) 
{
	spiffs_config SPIFlashCfg;
	
	SPIFlashCfg.phys_size        = (1024*1024*8);        		// SPI Flash��������
	SPIFlashCfg.phys_addr        = 8388608;       			// ��ʼ��ַ
	SPIFlashCfg.phys_erase_block = 65536;   			// FLASH���ɲ����Ŀ��С(W25X64���԰���������(4K)���߰������(64K))
	SPIFlashCfg.log_block_size   = 65536;   				// ��Ĵ�С(W25X64ÿ�����16��������ÿ������4K�ֽڣ�ÿ���������Ϊ��16X4=64K=65535�ֽ�)
	SPIFlashCfg.log_page_size    = 256;    				//  (W25X64ÿҳ����256���ֽڣ�16��ҳ����һ������)
    
	SPIFlashCfg.hal_read_f =  SPI_Flash_Read;    //��
	SPIFlashCfg.hal_write_f = SPI_Flash_Write;   //д
	SPIFlashCfg.hal_erase_f = SPI_Flash_Erase;   //����

	//����SPIFS
	int res = SPIFFS_mount(&sfblk0p1,
                           &SPIFlashCfg,
                           FS_Work_Buf,
                           FS_FDS,
                           sizeof(FS_FDS),
                           FS_Cache_Buf,
                           sizeof(FS_Cache_Buf),
                           0);
 
}

//

char ReadBuf[80];

int spiffs_init(void)
{
	Mount_SPI_Flash_File_System( );//spi flash�ļ�ϵͳ��ʼ��

}


int spiffs_test(void)
{
	char WriteBuf[]={"Hi,Budy! if you get this Message......Congratulations!You have succeeded!!"};
	char *ReadBuf;
	//���ļ�������ļ������ڣ��Զ�����
	spiffs_file fd = SPIFFS_open(&sfblk0p1, "my_file", SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR, 0);

	//д�ļ�
	if (SPIFFS_write(&sfblk0p1, fd, WriteBuf, sizeof(WriteBuf)) < 0)
		printf("errno %i\n", SPIFFS_errno(&sfblk0p1));
	SPIFFS_close(&sfblk0p1, fd);

	//���ļ�
	fd = SPIFFS_open(&sfblk0p1, "my_file", SPIFFS_RDWR, 0);
	ReadBuf = malloc(sizeof(WriteBuf));
	if (SPIFFS_read(&sfblk0p1, fd, ReadBuf, sizeof(WriteBuf)) < 0)
		printf("errno %i\n", SPIFFS_errno(&sfblk0p1));
	SPIFFS_close(&sfblk0p1, fd);
  
	//��ӡ����ļ�����
	printf("%s\n", ReadBuf);

}
char *readf_to_string( char *filename)
{
	spiffs_file fd;
	extern spiffs sfblk0p1;
	char *ReadBuf;
	spiffs_stat s;
	int res;
	int i;
	
	fd = SPIFFS_open(&sfblk0p1, filename, SPIFFS_RDWR, 0);
	if (fd < 0) {
		printf("Can not open file %i\n", SPIFFS_errno(&sfblk0p1));
		return NULL;
	}
	res = SPIFFS_fstat(&sfblk0p1, fd, &s);
	if (res < 0) {
		printf("stat errno: %i\n", SPIFFS_errno(&sfblk0p1));
		return NULL;
	}
	printf("cat size=%d\n",s.size);
	ReadBuf = malloc(s.size+1);
	
	if (ReadBuf!=NULL){
		if (SPIFFS_read(&sfblk0p1, fd, ReadBuf, s.size ) < 0){
			printf("errno: %i\n", SPIFFS_errno(&sfblk0p1));
		}
		ReadBuf[s.size]=0x00;
		

	}else{
		printf("File too big\n");
	}

	SPIFFS_close(&sfblk0p1, fd);
	
	return ReadBuf;
}




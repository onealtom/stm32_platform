#include "getopt.h"
#include "Header.h"
#include <spiffs.h>

#define MAX_CLI_CAHR	53
#define MAX_CLI_ARGS	10

enum  cmd_num{ hello ,sendpkt ,fs ,memm };
const char *cmd_num[]={ "hello" ,"sendpkt", "fs" ,"memm"};
#define NUM_OF_CMD 4

int prompt_hello(int argc, char * argv[])
{
	int c;
	char* devstr;

	char* pipe;
	char* chnnum;
	char* chndir;
	int memsiz;
	char * p;

	unsigned int band_channel;

	printf("hello prompt cli \r\n");
	
	while ((c = getopt(argc, argv, "ih")) != EOF){

		switch ( c )
		{
		case 'i':
			json_main();
			break;

		case '?':
			printf("Unknown option %c\n\r",optopt);
			break;
		case ':':
			printf("-%c needs value\n\r",optopt);
			break;
		case 'h':
		default:	
			printf("\r+------------------+\n");
			printf("\r| help:            |\n");
			printf("\r|                  |\n");
			printf("\r|                  |\n");
			printf("\r|                  |\n");
			printf("\r|                  |\n");
			printf("\r+------------------+\n\r");

			return 0;
		}
	}

}




int prompt_sendpkt(int argc, char * argv[])
{
	int i;
	uint16_t des_add=0x1;
	uint16_t src_add=0xFF;

	FPGA_ENABLE_WRITE;

	FPGA_SET_OPT(0);
	
	while ( 0 == ( FpgaReadRegister(FPGA_REG_MSG_TX_READY) ) ){

		UsNopDelay(50);
		if ( ++i > 10 ){
			TRACE_INFO_WP("time out!");
			FPGA_DISABLE_WRITE;
			return NULL;
		}
	}
	
	//1 写目的地址源地址
	//FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, (des_add>>8)&0xffff );
	//FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, (src_add>>8)&0xffff );	
	FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, 1 );
	FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, 0 );
	
	//2 启动计数
	FpgaWriteRegister( FPGA_REG_W_MSG_LEN, 195 );//最大195
	
	//3 写发送数据寄存器
	for ( i=0; i<200; i++ )
	{
		FpgaWriteRegister( FPGA_REG_W_MSG_DAT, i );
	}
	
	//4 启动发送
	FpgaWriteRegister( FPGA_REG_MSG_START_SEND, 0x00 );
	
	printf("\rTX OK\r\n");
	
	i =0;
	while ( 0 == ( FpgaReadRegister(FPGA_REG_MSG_TX_READY) ) ){
		printf("tx ready reg =0\r\n");
		if ( ++i > 250 ){
			TRACE_INFO_WP("tx ready reg time out!");
			FPGA_DISABLE_WRITE;
			return NULL;
		}
	}
	printf("tx ready reg =1\r\n");
	
}


int prompt_fs(int argc, char * argv[])
{
	uint8_t tmp[256];
	int i;
	int c;

	spiffs_DIR d;
	extern spiffs SPIFlashFS;
	struct spiffs_dirent e;
	struct spiffs_dirent *pe = &e;
	
	char *ReadBuf;
	spiffs_file fd;
	spiffs_stat s;
	int file_size;
	int res;
	
	while ((c = getopt(argc, argv, "ltc:wedh")) != EOF){

		switch ( c ){
		case 'l':
			SPIFFS_opendir(&SPIFlashFS, "/", &d);
			while ((pe = SPIFFS_readdir(&d, pe))) {
				printf("%s [%04x] size:%i\n", pe->name, pe->obj_id, pe->size);
			}
			SPIFFS_closedir(&d);
			break;
		case 't':
			break;
		case 'c':
			fd = SPIFFS_open(&SPIFlashFS, optarg, SPIFFS_RDWR, 0);
			if (fd < 0) {
				printf("errno %i\n", SPIFFS_errno(&SPIFlashFS));
				break;
			}
			res = SPIFFS_fstat(&SPIFlashFS, fd, &s);
			if (res < 0) {
				printf("SPIFFS_ERR_NOT_FOUND errno: %i\n", SPIFFS_errno(&SPIFlashFS));
				break;
			}
			ReadBuf = malloc(s.size);

			if (SPIFFS_read(&SPIFlashFS, fd, ReadBuf, s.size ) < 0)
				printf("errno: %i\n", SPIFFS_errno(&SPIFlashFS));
			SPIFFS_close(&SPIFlashFS, fd);

			printf("%s\n", ReadBuf);
			break;
		case 'w':
			
			break;
		case 'e':
			SPI_Flash_Erase();
			break;
		case 'd':
			break;
		case '?':
			printf("Unknown option %c\n\r",optopt);
			break;
		case ':':
			printf("-%c needs value\n\r",optopt);
			break;
		case 'h':
		default:	
			printf("\r+--------------------+\n");
			printf("\r| help:              |\n");
			printf("\r| l: list /          |\n");
			printf("\r| c: cat filename    |\n");
			printf("\r| w: write filename  |\n");
			printf("\r| c: create filename |\n");
			printf("\r| d: delect filename |\n");		
			printf("\r+--------------------+\n\r");

			return 0;
		}
	}
}

int prompt_memm(int argc, char * argv[])
{
	int c;
	int memsiz;
	char * p;
	
	while ((c = getopt(argc, argv, "im:sh")) != EOF){

		switch ( c ){
		case 'i':
			mem_init();
			break;
		case 'm':
			memsiz = strtol( optarg, NULL, 0 );
			printf("memsiz=%d\r\n",memsiz);
			p=(char *)mymalloc(memsiz);
			if(p==NULL){
				printf("Malloc ERROR\r\n");
			}
			break;
		case 's':
			printf("mem used %d\n",mem_perused());
			break;
		case 'h':
		default:
			printf("\r+------------------+\n");
			printf("\r| help:            |\n");		
			printf("\r+------------------+\n\r");

			return 0;
		}
	}
}
	
int command_process(char * str )
{
	int i;
	char str1[MAX_CLI_CAHR] = "mset -i -p 0 -b 3 -a 0x8008 -v 0x1000";

	//char s[2] = " ";
	char *token;

	char * argv[MAX_CLI_ARGS];
	int argc = 0;

	
	for(i=0;i<MAX_CLI_ARGS;i++){
		argv[i] = NULL ;
	}
	
	WTD_CLR;
	optind=1; // repoint optge gal point to start head
	
	printf("strlen=%d\n",strlen(str));
	/* 获取第一个子字符串 */
	token = strtok(str, " ");
	argv[argc++] = token;

	/* 继续获取其他的子字符串 */
	while( token != NULL ) {
		token = strtok(NULL, " ");
		argv[argc++] = token;
	}

	argc-=1;//去掉末尾有问题项

	for(i=0;i<argc;i++){
		printf("argv[%d]=%s\n",i, argv[i] );
	}
	
	for(i=0; i<NUM_OF_CMD; i++){
		if( strcmp( argv[0] ,cmd_num[i])==0){
			break;
		}
	}

WTD_CLR; 

	switch(i)
	{
	case hello:
		prompt_hello(argc,argv );
		break;
	case sendpkt:
		prompt_sendpkt(argc,argv );
		break;
	case fs:
		prompt_fs(argc,argv );
		break;
	case memm:
		prompt_memm(argc,argv );
		break;
	default:
		printf("unknow command\n\r");
		break;
	}

WTD_CLR;  

}


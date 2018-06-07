#include "getopt.h"
#include "Header.h"


#define MAX_CLI_CAHR	53
#define MAX_CLI_ARGS	10

enum  cmd_num{ hello ,sendpkt };
const char *cmd_num[]={ "hello" ,"sendpkt" };
#define NUM_OF_CMD 2

int prompt_hello(int argc, char * argv[])
{
	int c;
	char* devstr;

	char* pipe;
	char* chnnum;
	char* chndir;

	unsigned int band_channel;

	printf("hello prompt cli \r\n");
	
	ad936x_init_main();
	while ((c = getopt(argc, argv, "d:c:h")) != EOF){

		switch ( c )
		{
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


int command_process(char * str )
{
	int i;
	char str1[MAX_CLI_CAHR] = "mset -i -p 0 -b 3 -a 0x8008 -v 0x1000";

	char s[2] = " ";
	char *token;
	
	char * argv[MAX_CLI_ARGS];
	int argc = 0;
	
	WTD_CLR;  	
	optind=1; // repoint optge gal point to start head

	/* 获取第一个子字符串 */
	token = strtok(str, s);
	argv[argc++] = token;

	/* 继续获取其他的子字符串 */
	while( token != NULL ) {

		token = strtok(NULL, s);
		argv[argc++] = token;
	}


	for(i=0;i<argc;i++){
		printf("argv[%d]=%s\r\n",i, argv[i] );
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
	default:
		printf("unknow command\n\r");
		break;
	}

WTD_CLR;  

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



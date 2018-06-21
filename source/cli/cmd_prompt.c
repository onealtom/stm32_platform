#include "getopt.h"
#include "Header.h"
#include <spiffs.h>

#include <fs.h>

#define MAX_CLI_CAHR	53
#define MAX_CLI_ARGS	10

enum  cmd_num{ hello ,sendpkt ,fs ,memm ,ls, touch, cat, writef ,rm , parse_then_set };
const char *cmd_num[]={ "hello" ,"sendpkt", "fs" ,"memm", "ls", "touch", "cat", "writef" , "rm" ,"parse_then_set" };
#define NUM_OF_CMD 10

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
int prompt_ls(void)
{
	spiffs_DIR d;
	extern spiffs sfblk0p1;
	struct spiffs_dirent e;
	struct spiffs_dirent *pe = &e;
	
	SPIFFS_opendir(&sfblk0p1, "/", &d);
	while ((pe = SPIFFS_readdir(&d, pe))) {
		printf("%s [id: %d] [size: %i]\n", pe->name, pe->obj_id, pe->size);
	}
	SPIFFS_closedir(&d);
}

int prompt_touch(int argc, char * argv[])
{
	spiffs_file fd;
	extern spiffs sfblk0p1;

	fd = SPIFFS_open(&sfblk0p1, argv[1], SPIFFS_CREAT | SPIFFS_RDWR, 0);
	if (fd < 0) {
		printf("Can not open file %i\n", SPIFFS_errno(&sfblk0p1));
	}

	SPIFFS_close(&sfblk0p1, fd);
	
	return 0;
}

int prompt_rm(int argc, char * argv[])
{
	int c;
	char *filename;
	uint16_t id;
	
	spiffs_file fd;
	extern spiffs sfblk0p1;
	int res;
	
	spiffs_DIR d;
	extern spiffs sfblk0p1;
	struct spiffs_dirent e;
	struct spiffs_dirent *pe = &e;

	while ((c = getopt(argc, argv, "f:i:h")) != EOF){
		
		switch ( c ){
		case 'f':
			filename = optarg;
			//fd = SPIFFS_open(&sfblk0p1, argv[1], SPIFFS_RDWR, 0);
			fd = SPIFFS_open(&sfblk0p1, filename, SPIFFS_RDWR, 0);
			if (fd < 0) {
				printf("Can not open file %i\n", SPIFFS_errno(&sfblk0p1));
				return -1;
			}
	
			res = SPIFFS_fremove(&sfblk0p1, fd);
			if (res < 0) {
				printf("errno %i\n", SPIFFS_errno(&sfblk0p1));
				return -1;
			}
				break;
		case 'i':
			id = (uint16_t)strtol( optarg, NULL, 0 );
			SPIFFS_opendir(&sfblk0p1, "/", &d);

			while ((pe = SPIFFS_readdir(&d, pe))) {
				if( ((uint16_t)(pe->obj_id)) == id) {
					SPIFFS_remove(&sfblk0p1, pe->name);
				}
			}
			SPIFFS_closedir(&d);
			
			id = (int)strtol( optarg, NULL, 0 );
		
			break;
			break;
		case 'h':
			default:
			printf("\r+------------------------------------------------------+\n");
			printf("\r| Usage   : remove file                                |\n");
			printf("\r| formart : rm -f file_name                            |\n");
			printf("\r| formart : rm -i file_id                              |\n");
			printf("\r+------------------------------------------------------+\n\r");
			return 0;
		}	
	}
	
	return 0;
}

int prompt_cat(int argc, char * argv[])
{
	char * fstring;
	fstring = readf_to_string(argv[1]);
	printf("%s\n",fstring);

	return 0;
}
int prompt_writef(int argc, char * argv[])
{
	int c;
	char *filename;
	char *msg;
	spiffs_file fd;
	extern spiffs sfblk0p1;
	int res;

	while ((c = getopt(argc, argv, "f:m:h")) != EOF){
		
		switch ( c )
		{
			case 'f':
				filename = optarg;
				break;
			case 'm':
				msg = optarg;
				break;
			case 'h':
			default:
			printf("\r+------------------------------------------------------+\n");
			printf("\r| Usage   : writef text to file                        |\n");
			printf("\r| formart : writef -f <filename> -m <text>             |\n");
			printf("\r+------------------------------------------------------+\n\r");
			return 0;
		}	
	}

	//printf("filename=%s\n",filename);
	//printf("msg=%s\n",msg);

	fd = SPIFFS_open(&sfblk0p1, filename , SPIFFS_CREAT | SPIFFS_RDWR, 0);

	if (fd < 0) {
		printf("Can not open file %i\n", SPIFFS_errno(&sfblk0p1));
		return -1;
	}
	
	res = SPIFFS_lseek(&sfblk0p1, fd, 0, SPIFFS_SEEK_END);
	if (res < 0) {
		printf("lseek errno: %i\n", SPIFFS_errno(&sfblk0p1));
		return -1;
	}
	if (SPIFFS_write(&sfblk0p1, fd, msg, strlen(msg) ) < 0) {
		printf("write errno %i\n", SPIFFS_errno(&sfblk0p1));
		return -1;
	}
	SPIFFS_close(&sfblk0p1, fd);
	return 0;

}
int prompt_fs(int argc, char * argv[])
{
	uint8_t tmp[256];
	int i;
	int c;

	spiffs_DIR d;
	extern spiffs sfblk0p1;
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
			SPIFFS_opendir(&sfblk0p1, "/", &d);
			while ((pe = SPIFFS_readdir(&d, pe))) {
				printf("%s [%04x] size:%i\n", pe->name, pe->obj_id, pe->size);
			}
			SPIFFS_closedir(&d);
			break;
		case 't':
			break;
		case 'c':
			fd = SPIFFS_open(&sfblk0p1, optarg, SPIFFS_RDWR, 0);
			if (fd < 0) {
				printf("Can not open file %i\n", SPIFFS_errno(&sfblk0p1));
				break;
			}
			res = SPIFFS_fstat(&sfblk0p1, fd, &s);
			if (res < 0) {
				printf("stat errno: %i\n", SPIFFS_errno(&sfblk0p1));
				break;
			}
			printf("cat size=%d\n",s.size);
			ReadBuf = malloc(s.size+1);
			if (ReadBuf!=NULL){
				if (SPIFFS_read(&sfblk0p1, fd, ReadBuf, s.size ) < 0){
					printf("errno: %i\n", SPIFFS_errno(&sfblk0p1));
				}
				ReadBuf[s.size]=0x00;
				printf("%s\n", ReadBuf);
				
				//for(i=0;i<s.size;i++)
				//	printf("0x%02X",ReadBuf[i]);
				//printf("\n");
				free(ReadBuf);
			}
			SPIFFS_close(&sfblk0p1, fd);
			break;
		case 'w':
			fd = SPIFFS_open(&sfblk0p1, "my_file", SPIFFS_CREAT | SPIFFS_RDWR, 0);
		
			if (fd < 0) {
				printf("Can not open file %i\n", SPIFFS_errno(&sfblk0p1));
				break;
			}

			res = SPIFFS_lseek(&sfblk0p1, fd, -1, SPIFFS_SEEK_END);
			if (res < 0) {
				printf("lseek errno: %i\n", SPIFFS_errno(&sfblk0p1));
				break;
			}

			if (SPIFFS_write(&sfblk0p1, fd, (u8_t *)"Hello world", 12) < 0) {
				printf("write errno %i\n", SPIFFS_errno(&sfblk0p1));
				break;
			}
			SPIFFS_close(&sfblk0p1, fd);
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

int prompt_parse_then_set(int argc, char * argv[])
{
	int c;
	int lo_flag=0, sgmt_flag=0, gainctl_flag=0  ;
	static char *json_file = NULL;

	while ((c = getopt(argc, argv, "c:lsgh")) != EOF){
		
		switch ( c ){
		case 'c':
			json_file = optarg;
			
			break;
		case 'l':
			lo_flag =1;
			break;
		case 's':
			sgmt_flag = 1;
			break;
		case 'g':
			gainctl_flag = 1;
			break;
		case 'h':
			default:
			printf("\r+------------------------------------------------------+\n");
			printf("\r+------------------------------------------------------+\n\r");
			return 0;
		}	
	}

	char * content=NULL;

	content = readf_to_string( json_file );
	
	if(content!=NULL)
		printf("not null\n");
	else
		printf("is null\n");

	if(lo_flag){
		//content = read_file(json_file);
	}

	if(sgmt_flag){
		sgmt_parse_then_set(content);
	}

	if (gainctl_flag){
		gainctl_parse_then_set(content);
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
	/*--------file option--------*/
	case ls:
		prompt_ls();
		break;
	case touch:
		prompt_touch(argc,argv );
		break;
	case cat:
		prompt_cat(argc,argv );
		break;
	case writef:
		prompt_writef(argc,argv );
		break;
	case rm:
		prompt_rm(argc,argv );
		break;
	case parse_then_set:
		prompt_parse_then_set(argc,argv );
		break;
	/*--------file option end----*/
	default:
		printf("unknow command\n\r");
		break;
	}

WTD_CLR;  

}


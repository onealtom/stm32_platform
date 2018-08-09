#include "getopt.h"
#include "Header.h"
#include <spiffs.h>

#include <fs.h>
#include "pkt_drv.h"
#include "tran_file.h"

#define MAX_CLI_CAHR	53
#define MAX_CLI_ARGS	10

enum  cmd_num{ hello ,sendpkt ,memm ,ls, touch, cat, writef ,rm , parse_then_set, devmem, fpga, fwinfo, fpgaload, txfile, md5sum, help };
const char *cmd_num[]={ "hello" ,"sendpkt", "memm", "ls", "touch", "cat", "writef" , "rm" ,"parse_then_set" , "devmem", "fpga", "fwinfo", "fpgaload","txfile", "md5sum", "help" };
#define NUM_OF_CMD 16


int prompt_hello(int argc, char * argv[])
{
	int c;
	char* devstr;
	int ret;
	
	char* pipe;
	char* chnnum;
	char* chndir;
	int memsiz;
	char * p;
	char * text = "Hello World";
	char ch;
	int len=0;
	
	uint8_t tmp;

	printf("hello prompt cli \r\n");
	
	while ((c = getopt(argc, argv, "igsdrth")) != EOF){

		switch ( c )
		{
		case 'i':
			//json_main();
			//send_string(text);
			//len = tran_txmid_frame(3, 9, text, 1024);
			//printf("len = %d\n", len);

			//port_chain_del();
			ret = port_chain_init();
			if(ret){
				printf("init ret %d\n",port_chain_init() );
				chain_display();
				set_node_data(0,0, 0x11);
				set_node_data(1,0, 0x22);
				set_node_data(2,0, 0x33);
				set_node_data(3,0, 0x44);
				chain_display();
				port_chain_del();
			}
			break;
		case 's':
			set_node_data(2,1, 0x81);
			break;
		case 'g':
			get_node_data(2,1, &tmp);
			printf("2.1=%x\n", tmp );
			break;
		case 'd':
			chain_display();
			break;
		case 'r':
			port_chain_del();
			break;
		case 't':
			//ret = wait_ack_until_timout(2,1,3000);
			printf("ret=%x \n",ret);
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
	int c;
	pPKT_DEV_T pkt_dev;
	uint8_t* data;
	uint8_t len;
	uint8_t i;
	int mode;
	
	pkt_dev=(pPKT_DEV_T)malloc(sizeof(PKT_DEV_T));
	data =(uint8_t*)malloc(256);

	while ((c = getopt(argc, argv, "p:a:b:c:d:l:m:h")) != EOF){

		switch ( c )
		{
			case 'p':
				pkt_dev->fiber_port = (uint8_t)strtol( optarg, NULL, 0 );
				break;
			case 'a':
				pkt_dev->des.bs.port = (uint8_t)strtol( optarg, NULL, 0 );
				break;
			case 'b':
				pkt_dev->des.bs.node = (uint8_t)strtol( optarg, NULL, 0 );
				break;
			case 'c':
				pkt_dev->src.bs.port = (uint8_t)strtol( optarg, NULL, 0 );
				break;
			case 'd':
				pkt_dev->src.bs.node = (uint8_t)strtol( optarg, NULL, 0 );
				break;
			case 'l':
				len = (uint8_t)strtol( optarg, NULL, 0 );
				break;
			case 'm':
				mode = (uint8_t)strtol( optarg, NULL, 0 );
				break;			
			case 'h':
			default:
			printf("\r#########################################################\n");
			printf("\r# Usage   : MDIO Bus Read                               #\n");
			printf("\r# formart : mset <-i> -p <phy num> -i <port num> -s     #\n");
			printf("\r# -i      : if <-i> mdio set ip , else set phy          #\n");
			printf("\r# -p      : port 0~6                                    #\n");
			printf("\r# -d      : dev addr , only for phy                     #\n");
			printf("\r# -a      : reg addr                                    #\n");
			printf("\r# example : mset -p 0 -d 3 -a 0x3008                    #\n");
			printf("\r# example : mset -i -p 0 -a 0x00                        #\n");
			printf("\r#########################################################\n\r");
			return 0;
		}

	}
	printf("port=0x%02X\n",pkt_dev->fiber_port);
	printf("des_port_ad=0x%02X\n",pkt_dev->des.bs.port);
	printf("des_node_ad=0x%02X\n",pkt_dev->des.bs.node);
	printf("src_port_ad=0x%02X\n",pkt_dev->src.bs.port);
	printf("src_node_ad=0x%02X\n",pkt_dev->src.bs.node);
	
	printf("des=0x%04X\n",pkt_dev->des.ws);
	printf("src=0x%04X\n",pkt_dev->src.ws);	
	
	printf("len=0x%02X\n",len );
	
	if(mode == 1){
		printf("test base pkt mode\n");
		for(i=0;i<0xFF;i++){
			data[i]=0xFF;
		}
		for(i=0;i<len;i++){
			data[i]=i;
		}
		pkt_tx_base_frame( pkt_dev,  data , len);	
	}else if(mode == 2){

		printf("tx start pkt mode\n");

		uint32_t fsize = 64*1024*1024;
		char *fname = "test.txt";

		tran_txstart_frame( pkt_dev->des.bs.port, pkt_dev->des.bs.node,  fsize, fname );

	}else if(mode == 3){
		printf("tx end pkt mode\n");
		
	}


	free(data);
	
/*	int i;
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
	FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, 0xFFFF );
	FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, 0 );
	
	//2 启动计数/pid
	FpgaWriteRegister( FPGA_REG_W_MSG_LEN, 5 );//最大195

	FpgaWriteRegister( FPGA_REG_W_MSG_DAT, 192 );
	//3 写发送数据寄存器
	for ( i=0; i<210; i++ )
	{
		FpgaWriteRegister( FPGA_REG_W_MSG_DAT, 32+i );
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
*/

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
	
	if(fstring!=NULL)
		free(fstring);
	
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
	
	if(content!=NULL)
		free(content);

}

int prompt_devmem(int argc, char * argv[])
{
	uint32_t addr;
	uint16_t value;
	uint32_t readtmp;
	int width ;
	int c;
	
	addr = (uint32_t)strtol( argv[1], NULL, 0 );
	
	if(argv[3]){
		width  = (uint32_t)strtol( argv[2], NULL, 0 );
	}else{
		width = 16;
	}

	if(argc ==4 ){/*write*/
		addr = (uint32_t)strtol( argv[1], NULL, 0 );
		value = (uint16_t)strtol( argv[3], NULL, 0 );
		printf("addr=0x%08X\n",addr);
		printf("ModAddr: 0x%04X\n", (addr-0x60000000)/4 );
		PLWriteRegister(addr, width, value);
		
	}else if ( (argc ==2) || (argc ==3) ) {/*read*/
		readtmp= PLReadRegister(addr, width);
		printf("0x%08X\n",readtmp);
	}else{
		goto usage_text;
	}

	return 0;

usage_text:
	printf("\r+---------------------------------------+\n");
	printf("\r| Usage: devmem ADDRESS [WIDTH [VALUE]] |\n");
	printf("\r| Read/write from physical address      |\n");
	printf("\r| ADDRESS Address to act upon           |\n");
	printf("\r| WIDTH   Width only16                  |\n");
	printf("\r| VALUE   Data to be written            |\n");
	printf("\r+---------------------------------------+\n\r");

}


/*
fpga 0xa4
fpga 0xa8
*/
int prompt_fpga(int argc, char * argv[])
{
	uint16_t addr;
	uint16_t value;
	int c;
	volatile uint16_t * p = (volatile uint16_t*)0x60000000;
	
	if(argv[2] ){/*write*/
		FPGA_ENABLE_WRITE;

		addr = (uint16_t)strtol( argv[1], NULL, 0 );
		value = (uint16_t)strtol( argv[2], NULL, 0 );
		printf("MapAddr: 0x%08X\n",p+(addr<<1));
		FpgaWriteRegister(FPGA_WO_REG(addr), value);

	}else if(argc ==2){/*read*/
		addr = (uint16_t)strtol( argv[1], NULL, 0 );
		printf("MapAddr: 0x%08X\n",p+(addr<<1));
		printf("0x%04X\n",FpgaReadRegister(addr) );

	}else{
		printf("\r+---------------------------------------+\n");
		printf("\r| Usage: fpga ADDRESS [VALUE]           |\n");
		printf("\r+---------------------------------------+\n\r");
	}

	return 0;

}

void prompt_fwinfo(void)
{
	uint8_t *buf;
	uint8_t *p;
	int i;
	
	printf("[MCU fw info]\n");
	printf("Build time: %s %s \n", __DATE__, __TIME__);
	
	printf("[FPGA fw info]\n");
	printf("Ver Code: 0x%02X\n", (uint8_t)PLReadRegister(0x60000004,16));
	printf(" hw Code: 0x%02X\n", (uint8_t)PLReadRegister(0x60000008,16));
	printf(" SN Code: 0x%02X\n", (uint8_t)PLReadRegister(0x6000000C,16));
	
	buf = malloc(65);
	p = buf;
	for( i=0; i<64; i++){
		*buf = (uint8_t)PLReadRegister(0x60000010,8);
		buf++;
	}
	*buf = 0x00;


	printf("Watermark: %s\n", p );

	free(p);
}

int prompt_txfile(int argc, char * argv[])
{
	int c;
	char *filename;
	uint8_t port=0, node=0; 

	while ((c = getopt(argc, argv, "p:n:f:h")) != EOF){
		
		switch ( c )
		{
			case 'p':
				port = (uint8_t)strtol( optarg, NULL, 0 );
				printf("port=%d\n",port);
				break;
			case 'n':
				node = (uint8_t)strtol( optarg, NULL, 0 );
				printf("node=%d\n",node);
				break;
			case 'f':
				filename = optarg;
				printf("filename: %s\n",filename);
				break;
			case 'h':
			default:
			printf("\r+------------------------------------------------------+\n");
			printf("\r| Usage   : txfile -p 2 -n 1 -f testfile.json \n");
			printf("\r+------------------------------------------------------+\n\r");
			return 0;
		}
	}

	if(port==0 && node==0)
		return -1;

	tran_local_file(port, node, filename );
	return 0;
}

int prompt_md5sum(int argc, char * argv[])
{
	int c;
	char *filename;
	uint8_t port=0, node=0; 

	while ((c = getopt(argc, argv, "f:h")) != EOF){
		
		switch ( c )
		{

			case 'f':
				filename = optarg;
				printf("filename: %s\n",filename);
				break;
			case 'h':
			default:
			printf("\r+------------------------------------------------------+\n");
			printf("\r| Usage   : md5sum -f tx.txt \n");
			printf("\r+------------------------------------------------------+\n\r");
			return 0;
		}
	}



	md5sum_file(filename );
	return 0;
}

void prompt_help(void)
{
	printf("fwinfo   - print mcu and fpga watermark info\n");
	printf("ls       - list files in flash filesystem\n");
	printf("touch    - create a blank file\n");
	printf("cat      - read document content\n");
	printf("writef   - write a string into end of the file\n");
	printf("rm       - delete file of flash with filename or id \n");
	printf("parse_then_set - parse the json config file and set regs\n");
	printf("devmem   - read/write reg (mem map addr)\n");
	printf("fpga     - read/write reg (phy addr)\n");
	printf("fpgaload - init or reconfigure fpga \n");
}
int command_process(char * str )
{
	int i;
	char str1[MAX_CLI_CAHR] = "mset -i -p 0 -b 3 -a 0x8008 -v 0x1000";

	//char s[2] = " ";
	char *token;

	char * argv[MAX_CLI_ARGS];
	int argc = 0;

	printf("\r\n");

	for(i=0;i<MAX_CLI_ARGS;i++){
		argv[i] = NULL ;
	}
	
	WTD_CLR;
	optind=1; // repoint optge gal point to start head
	
	//printf("strlen=%d\n",strlen(str));
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
		//printf("argv[%d]=%s\n",i, argv[i] );
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
	/*--------file option end----*/
	
	case parse_then_set:
		prompt_parse_then_set(argc,argv );
		break;
	
	case devmem:
		prompt_devmem(argc,argv );
		break;

	case fpga:
		prompt_fpga(argc,argv );
		break;
	case fpgaload:
		FpgaLoad();
		if ( 0!=FpgaTest() )
		{
			printf("FPGA test success\r\n");
		}else{
			printf("FPGA test Fail\r\n");

		}
		break;
	case fwinfo:
		prompt_fwinfo();
		break;
	case txfile:
		prompt_txfile(argc,argv );
		break;
	case md5sum:
		prompt_md5sum(argc,argv );
		break;
	case help:
		prompt_help();
		break;	
	default:
		printf("unknow command\n\r");
		break;
	}

WTD_CLR;  

}


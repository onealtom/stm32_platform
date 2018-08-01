#include "tran_file.h"
#include "pkt_drv.h"
#include "md5.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "spiffs.h"
#include "tools.h"

#define CMD_TXSTA_SRCPORT  254
#define CMD_TXMID_SRCPORT  253
#define CMD_TXEND_SRCPORT  252

/*
CMD_TXSTA
+------+-------------------+
| PID  |      PAYLOAD      |
+------+-----+------+------+
|      | LEN | SIZE | NAME |
| 254  +-----+------+------+
|      |  1  |  4   |  32  |
+------+-----+------+------+
CMD_TXMID
+------+-------------+
| PID  |   PAYLOAD   |
+------+-----+-------+
|      | LEN | DATA  |
| 253  +-----+-------+
|      |  1  | 0~195 |
+------+-----+-------+
CMD_TXEND
+------+-----------+
| PID  |  PAYLOAD  |
+------+-----+-----+
|      | LEN | MD5 |
| 252  +-----+-----+
|      |  1  |  32 |
+------+-----+-----+
*/

#define CMD_TXSTA_FRAME_LEN (4+32)
#define CMD_TXMID_FRAME_MAXPAYLOADLEN 195
#define CMD_TXEND_FRAME_LEN (32)

extern int tran_txstart_frame(int port, int node, uint32_t fsize, char* fname )
{
	PKT_DEV_T dev; 
	uint8_t data[CMD_TXSTA_FRAME_LEN];
	
	dev.des.bs.port=port;
	dev.des.bs.node=node;
	dev.src.bs.port=CMD_TXSTA_SRCPORT;
	dev.src.bs.node=0x00;

	memcpy(data, &fsize, 4);
	strncpy( (char*)(data+4), fname, 32);

	return pkt_tx_base_frame(&dev ,  data , CMD_TXSTA_FRAME_LEN);
}

extern int tran_txmid_frame(int port, int node, uint8_t* data, int len )
{
	PKT_DEV_T dev; 
	int txlen=0;
	int remainder;
	int num;
	int i;
	uint8_t * p;

	if(len>1024)
		return 0;

	num = len / CMD_TXMID_FRAME_MAXPAYLOADLEN;
	remainder = len % CMD_TXMID_FRAME_MAXPAYLOADLEN;
	printf("num=%d remainder=%d\n " ,num ,  remainder);

	dev.des.bs.port=port;
	dev.des.bs.node=node;
	dev.src.bs.port=CMD_TXMID_SRCPORT;
	dev.src.bs.node=0x00;

	p = data;
	for(i=0 ; i<num ; i++){
		txlen += pkt_tx_base_frame(&dev ,  p , CMD_TXMID_FRAME_MAXPAYLOADLEN);
		p+=CMD_TXSTA_FRAME_LEN;
	}
	txlen += pkt_tx_base_frame(&dev ,  p , remainder);
	
	return txlen;
}

extern int tran_txend_frame(int port, int node, char* md5 )
{
	PKT_DEV_T dev; 
	uint8_t data[CMD_TXEND_FRAME_LEN];
	
	dev.des.bs.port=port;
	dev.des.bs.node=node;
	dev.src.bs.port=CMD_TXEND_SRCPORT;
	dev.src.bs.node=0x00;

	memcpy(data, md5, 32);
	return pkt_tx_base_frame(&dev ,  data , CMD_TXEND_FRAME_LEN);
}

pRU_TX_FILE_T create_ru_file(int port, int node, uint32_t fsize, char* fname )
{	
	pRU_TX_FILE_T fd;
	int namelen;
	
	fd = (pRU_TX_FILE_T)malloc(sizeof(RU_TX_FILE_T));
	if(fd == NULL)
		return NULL;
	
	fd->md5 = (char *)malloc(32);

	namelen = strlen(fname); 
	namelen = ( namelen < 32) ? namelen : 32;
	fd->fname = (char*)malloc(namelen);

	fd->des.bs.node = node;
	fd->des.bs.port = port;
	fd->fsize = fsize;

	tran_txstart_frame(fd->des.bs.port, fd->des.bs.node, fsize,  fname );

	return fd;
}

int write_ru_file(pRU_TX_FILE_T fd, uint8_t* data, int len )
{
	return tran_txmid_frame( fd->des.bs.port, fd->des.bs.node , data,  len);
}

int close_ru_file(pRU_TX_FILE_T fd )
{
	int ret = tran_txend_frame( fd->des.bs.port, fd->des.bs.node, fd->md5 );
	free(fd->md5);
	free(fd->fname);
	free(fd);
	return ret;
}

extern int tran_local_file(int port, int node, char* localfname )
{
	spiffs_file fd;
	pRU_TX_FILE_T ru_fd;
	extern spiffs sfblk0p1;
	uint8_t *ReadBuf;
#define READBUFFLEN 512
	int num, remainder;
	spiffs_stat s;
	int res;
	int i;
	int rd_num;
	MD5_CTX c;
	unsigned char out[16];

	fd = SPIFFS_open(&sfblk0p1, localfname, SPIFFS_RDWR, 0);

	if (fd < 0) {
		printf("Can not open file %i\n", SPIFFS_errno(&sfblk0p1));
		goto err;
	}
	res = SPIFFS_fstat(&sfblk0p1, fd, &s);
	if (res < 0) {
		printf("stat errno: %i\n", SPIFFS_errno(&sfblk0p1));
		goto err;
	}
	//printf("cat size=%d\n",s.size);
	
	//ru_fd = create_ru_file(port, node, s.size , localfname);
	MD5_Init(&c);

	ReadBuf = (uint8_t*)malloc(READBUFFLEN);
	if(ReadBuf == NULL)
		goto err;
	
	num = s.size / READBUFFLEN;
	remainder = s.size % READBUFFLEN;
	printf("num=%d remainder=%d\n " ,num ,  remainder);

	for(i=0 ; i<num ; i++){
		rd_num = SPIFFS_read(&sfblk0p1, fd, ReadBuf, READBUFFLEN );
		printf("time=%d\n",i);
		if (rd_num < 0){
			printf("errno: %i\n", SPIFFS_errno(&sfblk0p1));
			goto err;
		}
		//write_ru_file(ru_fd , ReadBuf , rd_num );
		MD5_Update(&c, ReadBuf, rd_num);
	}
	rd_num = SPIFFS_read(&sfblk0p1, fd, ReadBuf, remainder );
	if (rd_num < 0){
		printf("errno: %i\n", SPIFFS_errno(&sfblk0p1));
		goto err;
	}
	//write_ru_file(ru_fd , ReadBuf , rd_num );
	MD5_Update(&c, ReadBuf, rd_num);

	SPIFFS_close(&sfblk0p1, fd);

	MD5_Final(out, &c);
	hexdump(out, 16);

	//close_ru_file(ru_fd  );
/*	if( check_node_alive(port, node) ){

		fd = create_ru_file( port,  node, all_len, fname );
		memcpy(fd->md5 , (char*)(p_args+8+32), 32 );
		goto ack_ok;
	}else{
		printf("node not alive\n");
		goto ack_err;
	}
	*/
err:
	return -1;
}

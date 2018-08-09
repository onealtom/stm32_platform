#ifndef _TRAN_FILE_H
#define _TRAN_FILE_H

#include <stdint.h>
#include "pkt_drv.h"


typedef struct ru_tx_file
{
	OPT_ADDR_T des;
	uint32_t fsize;
	char* fname;
	char * md5;
}RU_TX_FILE_T;
typedef RU_TX_FILE_T* pRU_TX_FILE_T;

//extern int tran_txstart_frame(int port, int node, uint32_t fsize, char* fname );
//extern int tran_txend_frame(int port, int node, char* md5 );

extern pRU_TX_FILE_T create_ru_file(uint8_t port, uint8_t node, uint32_t fsize, char* fname );
extern int write_ru_file(pRU_TX_FILE_T fd, uint8_t* data, int len );
extern int close_ru_file(pRU_TX_FILE_T fd );

extern int tran_local_file(uint8_t port, uint8_t node, char* localfname );
extern int md5sum_file( char* localfname );
#endif/*_TRAN_FILE_H*/

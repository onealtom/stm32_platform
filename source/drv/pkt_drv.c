#include "Header.h"

typedef struct pkt_dev {
	uint8_t fiber_port;
	uint16_t des_addr;
	uint16_t src_addr;
#define CMD_MODE 0
#define TTY_MODE 1
	int pid;
	uint8_t* data;
}PKT_DEV_T;

typedef PKT_DEV_T* pPKT_DEV_T;



extern int pkt_tx_bytes(pPKT_DEV_T pkt_dev, uint8_t* data , int len)
{
	int i;

	uint8_t * p;
	
	p = data;

	FPGA_ENABLE_WRITE;

	FPGA_SET_OPT(pkt_dev->fiber_port);
	
	while ( 0 == ( FpgaReadRegister(FPGA_REG_MSG_TX_READY) ) ){
		UsNopDelay(50);
		if ( ++i > 10 ){
			printf("time out!");
			FPGA_DISABLE_WRITE;
			return -1;
		}
		WTD_CLR;
	}

	//1 写目的地址源地址
	//FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, (des_add>>8)&0xffff );
	//FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, (src_add>>8)&0xffff );
	//FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, 1 );
	//FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, 0 );
	FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, pkt_dev->des_addr );
	FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, pkt_dev->src_addr );

	//写 pid
	//该寄存器同时相当于是将源地址目的地址pid写入frame序列的启动开关
	FpgaWriteRegister( FPGA_REG_W_MSG_LEN, pkt_dev->pid );

	//长度写在payload的第一个
	FpgaWriteRegister( FPGA_REG_W_MSG_DAT, (uint8_t)len );

	//3 写发送数据寄存器
	for ( i=0; i<len; i++ )
	{
		FpgaWriteRegister( FPGA_REG_W_MSG_DAT, *p );
		p++;
	}

	//4 启动发送
	FpgaWriteRegister( FPGA_REG_MSG_START_SEND, 0x00 );

}

#define RX_GET_STATUS 	FpgaReadRegister( FPGA_REG_MSG_FIFO_ST )
#define RX_DATA       	FpgaReadRegister( FPGA_REG_MSG_FIFO_ST )
#define RX_CLR		FpgaReadRegister( FPGA_REG_R_NEXT_MSG )
extern int pkt_rx_bytes(pPKT_DEV_T pkt_dev, uint8_t* rxbuff)
{
	uint16_t msg_fifo_st;
	uint8_t* p;
	int i;
	
	p = rxbuff;
	
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );

	FPGA_ENABLE_WRITE;
	FPGA_SET_OPT(pkt_dev->fiber_port);
	FPGA_DISABLE_WRITE;


	if( (0xFF & RX_GET_STATUS)==0 ){
		return -1;
	}

	for ( i=0; i<FPGA_FRAME_FIFO_SIZE; i++ ){
		*p = (UCHAR8)( 0x00FF & RX_DATA );
		p++;
	}

	RX_CLR;

	
	return 0;

}

extern int rx_task(uint8_t rx_sta)
{
	int i;
	uint8_t* rxbuff;
	pPKT_DEV_T pkt_dev;

	for ( i=0; (i<FP_MAX) && ((rx_sta&(0x01<<i))!=0) ; i++ ){

		rxbuff = (uint8_t*)malloc(256);
		pkt_dev = (pPKT_DEV_T)malloc(sizeof(PKT_DEV_T));

		pkt_dev->fiber_port = i;
		
		if(rxbuff!=NULL)
			pkt_rx_bytes(pkt_dev, rxbuff);
		else
			printf("not enough RAM to rec\n");

		hexdump(rxbuff ,256);
	}
	
}

int route_txframe(uint8_t* data , int len)
{
	pPKT_DEV_T pkt_dev;
	int ret;
	
	pkt_dev=(pPKT_DEV_T)malloc(sizeof(PKT_DEV_T));
	
	if(len<=0)
		return 0;
	
	pkt_dev->des_addr = 1;
	pkt_dev->src_addr = 0;
	pkt_dev->pid = 0;
	pkt_dev->fiber_port = 0;
	
	ret = pkt_tx_bytes( pkt_dev,  data , len);
	
	if(ret<0)
		printf("send timeout");

	
	hexdump(data , len);
	
	free(pkt_dev);
}

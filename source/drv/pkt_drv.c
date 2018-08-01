#include "Header.h"
#include "pkt_drv.h"

#define PKT_PAYLOAD_LEN 195
//struct 
extern int listen_rx(int port, int waitime)
{

}

extern int check_node_alive(int port, int node)
{
	uint16_t tmp;
	
	FPGA_SET_OPT(port);
	tmp = FpgaReadRegister( FPGA_REG_OPT_INFO );
	if (node > (0x00FF&tmp) )
		return 0;
	else
		return 1;
}

extern int pkt_tx_base_frame(pPKT_DEV_T pkt_dev, uint8_t* data , int len)
{
	int i;

	uint8_t * p;
	uint16_t des_addr,src_addr;
	uint8_t des_port_mask;
	uint16_t a,b,c,d ;
	p = data;

	FPGA_ENABLE_WRITE;
	
	if( pkt_dev->des.bs.port == 0xFF)
	{
		des_port_mask = (0x01<<FP_MAX ) -1 ;
	}else{
		des_port_mask = 0x01 << pkt_dev->des.bs.port;
	}

	while ( 0 == \
		     ( des_port_mask & \
		      FpgaReadRegister(FPGA_REG_MSG_TX_READY) ) 
	      ){
		UsNopDelay(50);
		if ( ++i > 10 ){
			printf("time out!");
			//FPGA_DISABLE_WRITE;
			return -1;
		}
		WTD_CLR;
	}

	//1 写目的地址源地址
	//printf("%x %x \n",des_addr,src_addr );
	FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, pkt_dev->des.ws );
	FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, pkt_dev->src.ws );

	len = (len <PKT_PAYLOAD_LEN)? len : PKT_PAYLOAD_LEN; 

	//写 pid
	//该寄存器同时相当于是将源地址目的地址pid写入frame序列的启动开关
	FpgaWriteRegister( FPGA_REG_W_MSG_LEN, len );

	//3 写发送数据寄存器
	for ( i=0; i<len; i++ )
	{
		FpgaWriteRegister( FPGA_REG_W_MSG_DAT, *p );
		p++;
	}

	//4 启动发送
	FpgaWriteRegister( FPGA_REG_MSG_START_SEND, 0x00 );

	return len;

}

#define RX_GET_STATUS 	FpgaReadRegister( FPGA_REG_MSG_FIFO_ST )
#define RX_DATA       	FpgaReadRegister( FPGA_REG_R_MSG_DAT )
#define RX_CLR		FpgaReadRegister( FPGA_REG_R_NEXT_MSG )

extern int pkt_rx_frame(int port, pPKT_RXHEAD_INFO_T rx_head, uint8_t* rxbuff)
{
	uint16_t msg_fifo_st;
	uint8_t* p;
	int i;
	
	uint8_t des_ad[2];
	uint8_t src_ad[2];
	uint8_t len;
	uint8_t rx_buf[PKT_PAYLOAD_LEN];
	uint8_t check[4];

	p = rxbuff;

	//msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );

	FPGA_SET_OPT(port);

	if( (0xFF & RX_GET_STATUS)==0 ){
		return -1;
	}

	rx_head->a = RX_DATA ;
	rx_head->b = RX_DATA ;
	rx_head->c = RX_DATA ;
	rx_head->d = RX_DATA ;

	len = RX_DATA ;

	for ( i=0; i<len; i++ ){
		rxbuff[i] = RX_DATA ;
	}

	RX_CLR;

	return len;

}

extern int pkt_check_incoming(void)
{
	uint16_t msg_fifo_st;
	int i;
	uint8_t* payload;
	PKT_RXHEAD_INFO_T rx_head;

	int len=0;

	
	//printf("rx_sta=0x%x\n",rx_sta);

	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );

	for ( i=0; i<FP_MAX ; i++ ){
	if( (msg_fifo_st&(0x01<<i))!=0 ){

		len = pkt_rx_frame(i, &rx_head , payload);
		hexdump(payload ,len);

	}}

}

extern int pkt_rx_bytes(int port, uint8_t* rxbuff)
{
	uint16_t msg_fifo_st;
	uint8_t* p;
	int i;
	
	uint8_t des_ad[2];
	uint8_t src_ad[2];
	uint8_t pid;
	uint8_t len;
	uint8_t rx_buf[PKT_PAYLOAD_LEN];
	uint8_t check[4];

	p = rxbuff;

	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );

	if( (0xFF & RX_GET_STATUS)==0 ){
		return -1;
	}

	FPGA_SET_OPT(port);
	
	//pkt_dev->des_port_ad = (uint8_t)( 0x00FF & RX_DATA );
	//pkt_dev->des_node_ad = (uint8_t)( 0x00FF & RX_DATA );
	//pkt_dev->src_port_ad = (uint8_t)( 0x00FF & RX_DATA );
	//pkt_dev->src_node_ad = (uint8_t)( 0x00FF & RX_DATA );

	len = (uint8_t)( 0x00FF & RX_DATA );

	for ( i=0; i<204; i++ ){
		*p = (UCHAR8)( 0x00FF & RX_DATA );
		p++;
	}

	RX_CLR;

	
	return len;

}

extern int rx_task(uint8_t rx_sta)
{
	int i;
	uint8_t* rxbuff;
	pPKT_DEV_T pkt_dev;
	int len=0;
	int ret;
	uint8_t tmp;
	uint8_t tmp8;
	
	//printf("rx_sta=0x%x\n",rx_sta);
	
	//for ( i=0; ( (i<FP_MAX) && ((rx_sta&(0x01<<i))!=0) ); i++ ){
	for ( i=0; i<FP_MAX ; i++ ){
		
		tmp=0x01<<i;
		tmp8 = rx_sta & tmp ;
		if( tmp8 !=0  ){

			rxbuff = (uint8_t*)malloc(256);
			pkt_dev = (pPKT_DEV_T)malloc(sizeof(PKT_DEV_T));

			pkt_dev->fiber_port = i;
			
			if(rxbuff!=NULL){
				//len = pkt_rx_bytes(pkt_dev, rxbuff);
			}
			else{
				len = 0;
				printf("not enough RAM to rec\n");
				return -1;
			}

			hexdump(rxbuff ,256);
			printf("len=%d\n",len);
			free(pkt_dev);
			free(rxbuff);
			
			//ret = USART3_tx_buf(rxbuff ,len);
			//printf("ret=%d\n",ret);
		}
	}

}

int route_txframe(uint8_t* data , int len)
{
	pPKT_DEV_T pkt_dev;
	int ret;

	pkt_dev=(pPKT_DEV_T)malloc(sizeof(PKT_DEV_T));

	if(len<=0)
		return 0;

	//pkt_dev->des_addr = 1;
	//pkt_dev->src_addr = 0;
	

	//pkt_dev->des_port_ad=0x00;
	//pkt_dev->des_node_ad=0x01;
	//pkt_dev->src_port_ad=0x00;
	//pkt_dev->src_node_ad=0x00;



	ret = pkt_tx_base_frame( pkt_dev,  data , len);

	if(ret<0)
		printf("send timeout");
	
	hexdump(data , len);
	
	free(pkt_dev);
}

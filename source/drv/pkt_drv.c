#include "Header.h"
#include "pkt_drv.h"
#include "kfifo.h"
#include "list.h"
#include "mymalloc.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PKT_MAX_PAYLOAD_LEN 195
uint8_t share_frame_buf[PKT_MAX_PAYLOAD_LEN];

static inline int check_rx_status(uint8_t port)
{
	uint16_t msg_fifo_st;
	uint16_t mask;
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	mask = 1U<<port;
	return ( mask & msg_fifo_st ) ;

}



static inline void switch_rx_port(uint8_t port)
{
	FPGA_SET_OPT(port);
}

static inline uint8_t get_rx_data(void)
{
	return FpgaReadRegister( FPGA_REG_W_MSG_DAT );
}

int get_node_num(uint8_t port)
{
	uint16_t node_num;
	FPGA_SET_OPT(port);
	node_num = FpgaReadRegister( FPGA_REG_OPT_INFO );
	return (0x00FF&node_num);

}

extern int check_node_alive(uint8_t port, uint8_t node)
{
	int node_num;

	node_num = get_node_num( port );

	if (node > node_num )
		return 0;
	else
		return 1;
}


typedef struct port_chain
{
	uint8_t rulist[64];
	int node_num;

}PORT_CHAIN_T;

PORT_CHAIN_T * chain[FP_MAX];

int port_chain_init(void)
{
	int port;
	PORT_CHAIN_T * p;

	for(port=0; port<FP_MAX ; port++){
		p = chain[port];
		myfree(p);
	}

	for(port=0; port<FP_MAX ; port++){
		chain[port] = NULL;
	}
	for(port=0; port<FP_MAX ; port++){
		chain[port] = (PORT_CHAIN_T *)mymalloc(sizeof(PORT_CHAIN_T));
		if(chain[port] == NULL)
			return 0;
		chain[port]->node_num = get_node_num(port);
		mymemset(chain[port]->rulist , 0, chain[port]->node_num+1);
	}
	return 1;
	
}
void port_chain_del(void)
{
	PORT_CHAIN_T * p;
	int port;

	for(port=0; port<FP_MAX ; port++){
		p = chain[port];
		myfree(p);
	}
}
void chain_display(void)
{
	int port;
	int n;
	PORT_CHAIN_T * p;
	uint8_t * data;

	for(port=0; port<FP_MAX ; port++){
		p = chain[port];
		if( p == NULL )
			continue;
		printf("port %d: --->", port);
		for(n=0; n < (p->node_num)+1 ; n++ ) {
			data = (p->rulist)+n ;
			printf("0x%02X->", *data );
		}
		printf("\n");
	}
}



int check_node_data_active(uint8_t port, uint8_t node)
{
	PORT_CHAIN_T * p;
	if( port > FP_MAX )
		return 0;

	if ( node > chain[port]->node_num )
		return 0;
	
	return 1;

}

int get_node_data(uint8_t port, uint8_t node, uint8_t *data)
{
	uint8_t * p;
	
	if( !check_node_data_active(port , node) )
		return 0 ;
		
	p = (uint8_t *)chain[port];
	*data = *(p+node);

	return 1;
}

int set_node_data(uint8_t port, uint8_t node, uint8_t data)
{
	uint8_t * p;
	
	if( !check_node_data_active(port , node) )
		return 0 ;
		
	p = (uint8_t *)chain[port];
	*(p+node) = data;

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

	len = (len <PKT_MAX_PAYLOAD_LEN)? len : PKT_MAX_PAYLOAD_LEN; 

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

extern int pkt_rx_frame(uint8_t port, pPKT_RXHEAD_INFO_T rx_head, uint8_t* rxbuff)
{
	uint16_t msg_fifo_st;
	uint8_t* p;
	int i;
	
	uint8_t des_ad[2];
	uint8_t src_ad[2];
	uint8_t len;
	uint8_t rx_buf[PKT_MAX_PAYLOAD_LEN];
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

static inline int pkt_read_bytes(uint8_t* data, int len)
{
	int i;

	for(i=0 ; i< len ; i++){
		data[i] = RX_DATA;
	}
}

struct rxhead{
	uint8_t vport;
	uint8_t vnode;
	uint8_t sport;
	uint8_t snode;
	uint8_t len;
};

static inline void pkt_rx_frame_head(struct rxhead * head)
{
	head->vport = RX_DATA;
	head->vnode = RX_DATA;
	head->sport = RX_DATA;
	head->snode = RX_DATA;
	head->len = RX_DATA;
}

static int pkt_rx_frame_payload(uint8_t* data, int len)
{
	return pkt_read_bytes(data, len);
}
static void pkt_rx_frame_clear(void)
{
	RX_CLR;
}

extern int pkt_check_incoming_old(void)
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

extern int pkt_rx_bytes(uint8_t port, uint8_t* rxbuff)
{
	uint16_t msg_fifo_st;
	uint8_t* p;
	int i;
	
	uint8_t des_ad[2];
	uint8_t src_ad[2];
	uint8_t pid;
	uint8_t len;
	uint8_t rx_buf[PKT_MAX_PAYLOAD_LEN];
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

	//len = (uint8_t)( 0x00FF & RX_DATA );

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
				len = pkt_rx_bytes(i, rxbuff);
			}else{
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
#define MULTIFRAME_VPORT 200//除了200端口以外的都是原帧
#define ACKFRAME_VPORT  201

#define MULTIFRAME_MAXLEN 1024 //不取最大值
uint8_t mf_buf[MULTIFRAME_MAXLEN];

int pkt_check_incoming(uint8_t port, int timeout )
{
	while( !check_rx_status(port)){
		timeout++;
	}
	return 1;
}



int pkt_incoming(uint8_t port)
{
	struct rxhead head;
	uint8_t rxbuf[PKT_MAX_PAYLOAD_LEN];
	uint8_t vport, vnode, sport, snode, len;
	uint8_t tmp;
	struct KFIFO * fifo;
	
	if ( !check_rx_status(port) ) 
		return 0;

	switch_rx_port(port);
	
	pkt_rx_frame_head(&head);

	if(head.vport == RPC_FRAME_T_REQUEST ){
		get_node_data(head.sport, head.snode, &tmp);
		//is locked?
		if(tmp == 0x00){
			tmp = head.vnode;
			set_node_data(head.sport, head.snode, tmp);
		}
	}else if (head.vport == RPC_FRAME_T_REPLY ){

	}
	
	RX_CLR;
	return 1;
}

/** 
* 从整个光口缓冲中翻阅指定节点的回复信息，slave过来的帧分两种，请求帧和回复帧，回复帧在master发出操作后，slave才会回，请求帧像中断，有事件发生slave才会发，请求master相应事件
 * @param[in]    port        监听光口
 * @param[in]    node        监听节点
 * @param[out]   data        输出数据
 * @return        0，执行成功，非0，失败，详见
 * @ref            RetCode.h
 * @see
 * @note
 */ 
int pkt_lookover_slave_reply(uint8_t port, uint8_t node, uint8_t * data )
{
	struct rxhead head;
	uint8_t rxbuf[PKT_MAX_PAYLOAD_LEN];
	uint8_t vport, vnode, sport, snode, len=0;
	uint8_t tmp;

	struct KFIFO * fifo;
	
	if ( !check_rx_status(port) ) {
		return 0;
	}

	switch_rx_port(port);

	pkt_rx_frame_head(&head);

	if(head.vport == RPC_FRAME_T_REQUEST ){
		get_node_data(head.sport, head.snode, &tmp);
		//is locked?
		if(tmp == 0x00){
			tmp = head.vnode;
			set_node_data(head.sport, head.snode, tmp);
		}
	}else if (head.vport == RPC_FRAME_T_REPLY ){
		if( head.snode == node )
			len = pkt_rx_frame_payload( data, head.len );
	}

	RX_CLR;
	return len;
}

int pkt_lookover_slave_reply_timeout(uint8_t port, uint8_t node, uint8_t * data, int framelen, int timeout )
{
	int checked = 0;
	uint32_t sta_tim =0;
	uint32_t cur_tim =0;	
	int ret , len;

	sta_tim = get_ms_clk();
	printf("sta_tim=%d\n",sta_tim);

	while ( checked<framelen ) {
		ret = pkt_lookover_slave_reply(port, node, data);
		if (ret >0 ){
			checked ++;
			len +=ret;
		}
		cur_tim = get_ms_clk();
		printf(".");

		if ( ( cur_tim - sta_tim ) > timeout ){
			goto timeout;
		}
		
		ClrWtd();
	}
	
	printf("len = %d\n",len );
	return len;
timeout:
	printf("time out\n" );
	return 0;
}

int pkt_check_ack_until_timeout(uint8_t port, uint8_t node, int timeout )
{
	int ret = 0;
	memset(share_frame_buf, 0 , 8);
	ret = pkt_lookover_slave_reply_timeout(port , node, share_frame_buf, 1, timeout);
	if (ret >0){
		if( REPLY_OK == share_frame_buf[0] )
			return 1;
		else
			return 0;
	}
	return ret;
}


int pkt_polling(void)
{
	int i;
	int ret = 0;
	for(i=0 ; i < FP_MAX ; i++){
		ret += pkt_incoming(i);
	}

	return ret;
}

/*
int wait_ack_until_timout(uint8_t port, uint8_t node, int ms )
{
	uint8_t tmp=0;
	int t = 0;

	//if have old event
	if (get_node_data(port, node, &tmp) ){
		process_ru_event(port, node, &tmp );
		set_node_data(port, node, 0);
	}

	while(ms--){
		if (pkt_polling() && get_node_data(port, node, &tmp)){
			if( tmp !=0){
				printf("acked use %dms\n",ms);
				printf("tmp=%x\n",tmp);
				return tmp;
			}
		}
		t++;
		CMB_wait_ms(1);
	}

	printf("wait ack time out \n");
	return 0;

}
*/

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

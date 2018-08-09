#ifndef __PKT_DRV_H
#define __PKT_DRV_H

#include <stdint.h>

#define RPC_FRAME_T_REQUEST   224U    /*RPC请求MASTER帧类型*/
#define RPC_FRAME_T_REPLY     225U    /*RPC回复MASTER帧类型*/
//#define STREAMFRAME_TYPE   226

#define REPLY_OK     1U
#define REPLY_FAIL   2U

typedef union {
	struct{uint8_t node, port ; } bs; //little-endian
	uint16_t ws;
} OPT_ADDR_T;

typedef struct pkt_dev {
	uint8_t fiber_port;
	OPT_ADDR_T des;
	OPT_ADDR_T src;
}PKT_DEV_T;


typedef OPT_ADDR_T* pOPT_ADDR_T;
typedef PKT_DEV_T* pPKT_DEV_T;

typedef struct pkt_rxhead_info {
	uint8_t port;
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t len;
}PKT_RXHEAD_INFO_T;

typedef PKT_RXHEAD_INFO_T* pPKT_RXHEAD_INFO_T;

static inline void switch_rx_port(uint8_t port);
static inline uint8_t get_rx_data(void);
inline int get_node_num(uint8_t port);

extern int check_node_alive(uint8_t port, uint8_t node);
extern int pkt_tx_base_frame(pPKT_DEV_T pkt_dev, uint8_t* data , int len);

int pkt_check_ack_until_timeout(uint8_t port, uint8_t node, int timeout );
#endif /*__PKT_DRV_H*/

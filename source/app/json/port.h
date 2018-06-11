#ifndef _PORT_H
#define _PORT_H

#include <stdint.h>
//#include "config.h"


// #define HARDWARE_AU	1
// #define HARDWARE_RU	0

// #define HARDWARE_ID  HARDWARE_RU

//#if defined(linux)
#define port_pr_err(format, ...)		do {fprintf(stderr, format, ## __VA_ARGS__);}while(0)
#define port_pr_info(format, ...)		do {fprintf(stdout, format, ## __VA_ARGS__);}while(0)




uint32_t port_get_pl_mclk(void);

uint64_t port_get_tx_lo_clk(int port);
uint64_t port_get_rx_lo_clk(int port);
int port_set_tx_lo_clk(int port, uint64_t clk);
int port_set_rx_lo_clk(int port, uint64_t clk);

int port_read(uint32_t addr, uint32_t *read_result);

int port_write(uint32_t addr, uint32_t write_data);

#endif /*_PORT_H*/
#include <errno.h>
#include "port.h"


#ifdef LINUX_PLATFORM
#include <fcntl.h>
#include <sys/mman.h>
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#include "pl_config.h"

#define DEVMEM_MAP_SIZE 4096
#define DEVMEM_MAP_MASK (off_t)(DEVMEM_MAP_SIZE - 1)

#define DEFULT_MCLK 61440000
#define DEFULT_TXLO 874500000
#define DEFULT_RXLO 829500000

enum iodev { RX, TX };


int pl_raw_write_bytes( uint32_t ad , uint8_t *data , int len)
{
	uint8_t reg[4];
	
	if(1==len){
		goto not_support;
	}else if(2==len){
		goto not_support;
	}else if(3==len){
		goto not_support;
	}else if(4==len){
		
		uint8_t reg[4];
		uint16_t lsb;
		uint16_t msb;
		
		reg[0] = *data;
		reg[1] = *(data+1);
		reg[2] = *(data+2);
		reg[3] = *(data+3);
		
		lsb =  (reg[1]<<8) + reg[0] ;
		msb =  (reg[3]<<8) + reg[2] ;
		
		PLWriteRegister(ad , lsb);
		
		PLWriteRegister(ad+4, msb);
	
	}else{
		goto not_support;
	}
	
	return 0;
not_support:
	return -1;
}

int port_is_au(void)
{
	return PRODUCT_MODE;
}

#ifdef LINUX_PLATFORM
/*
int iio_node_read_lo_example(void)
{
	uint64_t  rx_lo_buf[1];
	uint64_t  tx_lo_buf[1];

	iio_node_read_lo(RX , rx_lo_buf);
	iio_node_read_lo(TX , tx_lo_buf);

	printf("rx_lo_buf=%lld\n", rx_lo_buf[0]); 
	printf("tx_lo_buf=%lld\n", tx_lo_buf[0]); 
}
*/
int iio_node_read_lo(enum iodev type, uint64_t * lo_clk )
{
	//char * max_64_t = "18446744073709551615";
	//int max_read_len = strlen(max_64_t);
	#define MAX_READ_LEN 20

	FILE *f;
	char *dst;

	dst = (char*)malloc(20);

	char lo_node[128];

	if (type == RX)
		snprintf(lo_node, sizeof(lo_node), "/sys/bus/iio/devices/%s/%s", "iio:device2", "out_altvoltage0_RX_LO_frequency");
	else
		snprintf(lo_node, sizeof(lo_node), "/sys/bus/iio/devices/%s/%s", "iio:device2", "out_altvoltage1_TX_LO_frequency");

	ssize_t ret;

	f = fopen(lo_node, "re");
	if (!f)
		return -errno;

	ret = fread(dst, sizeof(char), MAX_READ_LEN, f);
	if (ret > 0)
		dst[ret - 1] = '\0';

	*lo_clk=(uint64_t)strtoll(dst, NULL, 10);

	pr_dbg("lo_clk=%lld\n",(long long int)*lo_clk); 

	fflush(f);

	if (ferror(f))
		ret = -errno;
	fclose(f);

	return ret ? ret : -EIO;
}


uint32_t port_get_pl_mclk(void)
{
	return DEFULT_MCLK;
}

uint64_t port_get_tx_lo_clk(int port)
{
	int ret;
	uint64_t  lo_buf[1];
	ret = iio_node_read_lo(TX , lo_buf);

	if(ret>0)
		return lo_buf[0];
	else
		return DEFULT_TXLO;
}

uint64_t port_get_rx_lo_clk(int port)
{
	int ret;
	uint64_t  lo_buf[1];
	ret = iio_node_read_lo(RX , lo_buf);
	
	if(ret>0)
		return lo_buf[0];
	else
		return DEFULT_RXLO;
}

int port_set_tx_lo_clk(int port, uint64_t clk)
{
	return IS_OK;
}

int port_set_rx_lo_clk(int port, uint64_t clk)
{
	return IS_OK;
}

int port_read(uint32_t addr, uint32_t *read_result)
{
	return devmem_read(addr, read_result);
}

int port_write(uint32_t addr, uint32_t write_data)
{
	return devmem_write(addr, write_data);
}


int devmem_read(uint32_t addr, uint32_t *read_result)
{
	void *map_base, *virt_addr;
	//uint64_t read_result;

	off_t target;
	int fd;
	int width = 8 * sizeof(int);

	errno = 0;
	target = addr;
		
	fd = open("/dev/mem",  (O_RDONLY | O_SYNC));

	map_base = mmap(NULL,
			DEVMEM_MAP_SIZE * 2 /* in case value spans page */,
			PROT_READ,
			MAP_SHARED,
			fd,
			target & ~DEVMEM_MAP_MASK);

	if (map_base == MAP_FAILED)
		printf("MAP_FAILED\n");

//	printf("Memory mapped at address %p.\n", map_base);

	virt_addr = (char*)map_base + (target & DEVMEM_MAP_MASK);

	read_result = *(volatile uint32_t*)virt_addr;

	if (munmap(map_base, DEVMEM_MAP_SIZE) == -1)
		printf("DEVMEM_MAP_SIZE\n");
	close(fd);

	return EXIT_SUCCESS;
}

int devmem_write(uint32_t addr, uint32_t write_data )
{
	void *map_base, *virt_addr;
	uint64_t writeval = write_data; /* for compiler */
	off_t target;
	int fd;
	int width = 8 * sizeof(int);

	target = addr;
	width = 32;

	fd = open("/dev/mem", (O_RDWR | O_SYNC) );

	map_base = mmap(NULL,
			DEVMEM_MAP_SIZE * 2 /* in case value spans page */,
			(PROT_READ | PROT_WRITE) ,
			MAP_SHARED,
			fd,
			target & ~DEVMEM_MAP_MASK);
	if (map_base == MAP_FAILED)
		printf("MAP_FAILED\n");

//	printf("Memory mapped at address %p.\n", map_base);

	virt_addr = (char*)map_base + (target & DEVMEM_MAP_MASK);

	*(volatile uint32_t*)virt_addr = writeval;

	if (munmap(map_base, DEVMEM_MAP_SIZE) == -1)
		printf("DEVMEM_MAP_SIZE\n");
	close(fd);

	return EXIT_SUCCESS;
}

#endif/*LINUX_PLATFORM*/

#ifdef BARE_PLATFORM


uint32_t port_get_pl_mclk(void)
{
	return DEFULT_MCLK;
}

uint64_t port_get_tx_lo_clk(int port)
{
	return DEFULT_TXLO;
}

uint64_t port_get_rx_lo_clk(int port)
{

	return DEFULT_RXLO;
}

int port_set_tx_lo_clk(int port, uint64_t clk)
{
	return IS_OK;
}

int port_set_rx_lo_clk(int port, uint64_t clk)
{
	return IS_OK;
}

int port_read(uint32_t addr, uint32_t *read_result)
{

}

int port_write(uint32_t addr, uint32_t write_data)
{

}

#endif/*BARE_PLATFORM*/
#include <stdio.h>
#include <stdint.h>

#include "common_hw.h"
#include "pl_config.h"

#include "port.h"
#include "regmap.h"



int is_au(void)
{
	return port_is_au();
}


/**
 * @brief 获取FPGA主时钟频率
 * @details [long description]
 * @return 主时钟频率单位Hz
 */
uint32_t get_pl_mclk(void)
{
	return port_get_pl_mclk();
}

uint32_t get_tx_lo_clk(int port)
{
	return port_get_tx_lo_clk(port);
}

uint32_t get_rx_lo_clk(int port)
{
	return port_get_rx_lo_clk(port);
}

uint32_t set_tx_lo_clk(int port, uint64_t clk)
{
	return port_set_tx_lo_clk(port, clk);
}

uint32_t set_rx_lo_clk(int port, uint64_t clk)
{
	return port_set_rx_lo_clk(port, clk);
}

static uint32_t pl_raw_write(uint32_t addr , uint32_t value)
{
	pr_dbg("\t[w]%04X %04X\n",addr , value);
	//pr_dbg("\n");
#ifndef PC_TEST
	port_write(addr, value);
#endif

}

static uint32_t pl_raw_read(uint32_t addr )
{
	pr_dbg("[r]%04X \n",addr );
#ifndef PC_TEST
	uint32_t *tmp;
	port_read(addr, tmp);
	return *tmp;
#else
	return 0;
#endif

}

extern uint32_t sgmtreg_write(char sgmt , uint32_t reg , uint32_t value)
{
	uint8_t port_num;
	uint32_t basead;

	//pr_dbg("[sg_w]sgmt%c reg%X\n",sgmt,reg);
	port_num = (uint8_t)(sgmt - 'A');

	basead = SGMTA_CTLREGS_BASEAD + (port_num * SGMTREGS_LEN);

	pl_raw_write( basead+(reg*0x04) , value );
}

static uint32_t sgmtreg_read(char sgmt , uint32_t reg )
{
	uint8_t port_num;
	uint32_t basead;

	port_num = (uint8_t)(sgmt - 'A');

	basead = SGMTA_CTLREGS_BASEAD + (port_num * SGMTREGS_LEN);

	return pl_raw_read( basead+(reg*0x04) );
}


static void pipe_select(uint32_t pipe_sel_num){

	static uint32_t sel_sav;

	if (sel_sav != pipe_sel_num){
		sel_sav = pipe_sel_num;
		pl_raw_write( PHYINFO_PIPESEL_REG, pipe_sel_num);
	}

}

extern uint32_t pipereg_write(char sgmt, uint32_t pipe_sel_num, uint32_t reg, uint32_t value)
{
	pipe_select(pipe_sel_num);

	pr_dbg("[pi_w]sgmt%c ch%d reg%X ",sgmt, pipe_sel_num,reg);
	sgmtreg_write( sgmt, reg, value );

}

static uint32_t pipereg_read(char sgmt, uint32_t pipe_sel_num, uint32_t reg )
{
	pipe_select(pipe_sel_num);

	//pr_dbg("[pi_w]sgmt%c ch%d reg%X ",sgmt, pipe_sel_num,reg);
	sgmtreg_read( sgmt, reg );

}

uint32_t sgmt_ad_tran( char sgmt, uint32_t offset_ad )
{
	uint8_t port_num;
	uint32_t basead;
	
	port_num = (uint8_t)(sgmt - 'A');

	basead = SGMTA_CTLREGS_BASEAD + (port_num * SGMTREGS_LEN);
	
	return (basead+(offset_ad*REG_LEN));

}



uint32_t sgmtreg_write_bytes(char sgmt , uint32_t reg , uint8_t *value, int len)
{
	uint8_t port_num;
	uint32_t basead;
	uint32_t actual_ad;


	actual_ad = sgmt_ad_tran(sgmt ,reg );

	pl_raw_write_bytes( actual_ad , value , len);
}
/*
extern uint32_t pipereg_write_bytes(char sgmt, uint32_t pipe_sel_num, uint32_t reg, uint8_t *value, int len)
{
	pipe_select(pipe_sel_num);

	pr_dbg("[pi_w]sgmt%c ch%d reg%X ",sgmt, pipe_sel_num,reg);
	sgmtreg_write_bytes( sgmt, reg, value , len);

}

*/
extern int get_max_pnr(char sgmt_chr)
{
	// int sgmt_no;
	// uint8_t w_h , w_l;
	// uint32_t nr_regad , buf;

	// sgmt_no = sgmt_chr - 'A';

	// w_h = (sgmt_no & 0xF0) >> 2;
	// w_l = sgmt_no & 0x0F;

	// nr_regad = PHYINFO_PIPENR1_REG+(4*w_h);

	// buf = pl_raw_read(nr_regad );

	//return ( 0x1F & ( buf>>(8*w_l) ) );
	return 4;

}

extern	int test_addr(char sgmt)
{
	pr_info("SGMTX_ADHTHR        reg%02X: ",SGMTX_ADHTHR);
	sgmtreg_read(sgmt, SGMTX_ADHTHR);
	pr_info("SGMTX_ADLTHR        reg%02X: ",SGMTX_ADLTHR);
	sgmtreg_read(sgmt, SGMTX_ADLTHR);
	pr_info("SGMTX_DAHTHR        reg%02X: ",SGMTX_DAHTHR);
	sgmtreg_read(sgmt, SGMTX_DAHTHR);
	pr_info("SGMTX_DALTHR        reg%02X: ",SGMTX_DALTHR);
	sgmtreg_read(sgmt, SGMTX_DALTHR);

	pr_info("SGMTX_PIPEX_RXPHASE reg%02X: ",SGMTX_PIPEX_RXPHASE);
	pipereg_read(sgmt, 0, SGMTX_PIPEX_RXPHASE);
	pr_info("SGMTX_PIPEX_TXPHASE reg%02X: ",SGMTX_PIPEX_TXPHASE);
	pipereg_read(sgmt, 0, SGMTX_PIPEX_TXPHASE);
	pr_info("SGMTX_PIPEX_TXGAIN  reg%02X: ",SGMTX_PIPEX_TXGAIN);
	pipereg_read(sgmt, 0, SGMTX_PIPEX_TXGAIN);
	pr_info("SGMTX_PIPEX_RXGAIN  reg%02X: ",SGMTX_PIPEX_RXGAIN);
	pipereg_read(sgmt, 0, SGMTX_PIPEX_RXGAIN);
	pr_info("SGMTX_PIPEX_TXALC   reg%02X: ",SGMTX_PIPEX_TXALC);
	pipereg_read(sgmt, 0, SGMTX_PIPEX_TXALC);
	pr_info("SGMTX_PIPEX_RXALC   reg%02X: ",SGMTX_PIPEX_RXALC);
	pipereg_read(sgmt, 0, SGMTX_PIPEX_RXALC);


}

//--------------------------read-------------------------
//------------------读状态模块使用以下接口-------------------

//字节地址8位读取
uint8_t raw_inle8(uint32_t addr )
{
	uint32_t tmp;

	tmp = pl_raw_read(addr - (addr%4));

	tmp = (tmp >> ((addr%4)*8)) & 0x000000FF;

	//pr_dbg("[raw_r]ad=0x%04X \n",addr );

	return (uint8_t)tmp;
}

//字节地址8位读len次，len最大等于4
uint32_t get_field(uint32_t addr, uint32_t len)
{
	uint8_t buf[4]={0,0,0,0};
	int i;

	if (len>4)
		len = 4;

	for ( i = 0; i < len; i++){
		buf[i] = raw_inle8(addr);
		addr++;
	}

	return ( (buf[3]<<24) | (buf[2]<<16) | (buf[1]<<8) | buf[0] );
}

//根据段号，将sgmt寄存器的偏移地址转为物理地址
static uint32_t smgtaddr(uint8_t sgmt, uint8_t ad)
{
	return SGMTA_CTLREGS_BASEAD + ( (sgmt - 'A') * SGMTREGS_LEN ) + ad;
}

//根据段号，通道号，将pipe寄存器的偏移地址转为物理地址
uint32_t pipeaddr(uint8_t sgmt , uint8_t pipe, uint8_t ad)
{
	pl_raw_write( PHYINFO_PIPESEL_REG, pipe);
	return smgtaddr( sgmt, ad );
}

//根据输入的sgmt号，sgmt reg offset，按字节读len个
extern uint32_t read_sgmt_val(uint8_t sgmt, uint8_t ad, uint8_t len)
{
	return get_field(smgtaddr(sgmt,ad), len);
}

//根据输入的sgmt号，pipe号，pipe reg offset，按字节读len个
extern uint32_t read_pipe_val(uint8_t sgmt, uint8_t pipe, uint8_t ad, uint8_t len)
{
	pipe_select(pipe);
	return get_field(pipeaddr(sgmt,pipe,ad), len);
}

static uint32_t readnet_raw( uint32_t addr, uint8_t len)
{
	return 0;
}

static uint32_t readnet_sgmt_val(uint8_t sgmt, uint8_t ad, uint8_t len)
{
	return readnet_raw(smgtaddr(sgmt,ad), len);
}
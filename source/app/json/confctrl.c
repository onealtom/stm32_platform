#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include <libconfig.h>

#include "pl_config.h"
#include "chn2freq.h"
#include "common_hw.h"
#include "formula.h"
#include "confctrl.h"


/*
  批量设置寄存器接口
  */
int set_thr_regs(pSGMT_SET_T p_sg)
{
	int adh_thr,adl_thr,dah_thr,dal_thr;
	uint32_t port;

	if( is_au() ){
		dah_thr = p_sg->ul_dah_thr;
		dal_thr = p_sg->ul_dal_thr;
		adh_thr = p_sg->dl_adh_thr;
		adl_thr = p_sg->dl_adl_thr;
	/*RU*/
	}else{
		adh_thr = p_sg->ul_adh_thr;
		adl_thr = p_sg->ul_adl_thr;
		dah_thr = p_sg->dl_dah_thr;
		dal_thr = p_sg->dl_dal_thr;
	}

	sgmtreg_write( p_sg->name , SGMTX_ADHTHR , thr2reg(adh_thr) );
	sgmtreg_write( p_sg->name , SGMTX_ADLTHR , thr2reg(adl_thr) );
	sgmtreg_write( p_sg->name , SGMTX_DAHTHR , thr2reg(dah_thr) );
	sgmtreg_write( p_sg->name , SGMTX_DALTHR , thr2reg(dal_thr) );
}




int set_chn_regs(pSGMT_SET_T p_sg )
{
	int i;
	uint8_t net;
	uint64_t ul_losc ,dl_losc ;
	uint32_t f;
	int phase;
	uint32_t reg;
	uint8_t regs[4];
	uint32_t ulphase_regad, dlphase_regad;

	int is_au_flag;
	//pnr = get_max_pnr(p_sg->name);
	/* 获取主时钟频率，并统一单位为KHz */

	is_au_flag = is_au();

	if( is_au_flag ){
		/*AU*/
		ul_losc = p_sg->ul_tx_losc;
		dl_losc = p_sg->dl_rx_losc;
		ulphase_regad = SGMTX_PIPEX_TXPHASE;
		dlphase_regad = SGMTX_PIPEX_RXPHASE;
	
	}else{
		/*RU*/
		ul_losc = p_sg->ul_rx_losc;
		dl_losc = p_sg->dl_tx_losc;
		ulphase_regad = SGMTX_PIPEX_RXPHASE;
		dlphase_regad = SGMTX_PIPEX_TXPHASE;
	}

	for(i=0;(i<16)&&(i<p_sg->pipe_nr);i++){

		if( (p_sg->ul_pipe_mask) & (0x0001<<i) ) {
			f = chn2freq(p_sg->net_std, p_sg->pipe_tab[i].ul_chn, UP_LINK);
			pr_dbg("f=%d\n",f);
			/* 传入频率统一单位为KHz get_pl_mclk 返回单位Hz，
			配置文件传入的本振单位MHz，
			chn2freq 返回单位0.1MHz */
			//reg = freq2reg((uint32_t)(get_pl_mclk()/1000), (uint32_t)(ul_losc/1000), (uint32_t)(f*100) );
			phase = freq2phase((uint32_t)(get_pl_mclk()/1000), (uint32_t)(ul_losc/1000), (uint32_t)(f*100) );
			pr_dbg("phase=%d\n",phase);

			if( is_au_flag ){
				reg = phase2aureg(phase);
				regs[3]= reg & BIT_MASK(7,0);
				regs[2]= (reg & BIT_MASK(15,8))>>8;
				regs[1]= (reg & BIT_MASK(23,16))>>16;
				regs[0]= (reg & BIT_MASK(31,24))>>24;
				//pipereg_write_bytes(p_sg->name, i, ulphase_regad, regs , 4 );
			}else{
				reg = phase2rureg(phase);
				pipereg_write(p_sg->name, i, ulphase_regad, reg );
			}
		}
		if( (p_sg->dl_pipe_mask) & (0x0001<<i) ) {
			f = chn2freq(p_sg->net_std, p_sg->pipe_tab[i].dl_chn, DW_LINK);
			pr_dbg("f=%d\n",f);
			/* 传入频率统一单位为KHz get_pl_mclk 返回单位Hz，
			配置文件传入的本振单位MHz，
			chn2freq 返回单位0.1MHz */
			//reg = freq2reg((uint32_t)(get_pl_mclk()/1000), (uint32_t)(dl_losc/1000), (uint32_t)(f*100) );
			phase = freq2phase((uint32_t)(get_pl_mclk()/1000), (uint32_t)(dl_losc/1000), (uint32_t)(f*100) );
			pr_dbg("phase=%d\n",phase);

			if( is_au_flag ){
				reg = phase2aureg(phase);
			}else{
				reg = phase2rureg(phase);
				pipereg_write(p_sg->name, i, dlphase_regad, reg );
			}
		}
	}

}

int set_gainalc_regs(pSGMT_GAINCTL_SET_T p_gc )
{
	int i ;
	uint32_t reg;

	if( is_au() ){
		return IS_OK;
	}

	for(i=0;(i<16)&&(i<p_gc->pipe_nr);i++){

		pipereg_write(p_gc->name, i, SGMTX_PIPEX_RXGAIN, gain2reg( p_gc->gainctl[i].ul_gain ) );
		pipereg_write(p_gc->name, i, SGMTX_PIPEX_RXALC , alc2reg(  p_gc->gainctl[i].ul_alc  ) );

		pipereg_write(p_gc->name, i, SGMTX_PIPEX_TXGAIN, gain2reg( p_gc->gainctl[i].dl_gain ) );
		pipereg_write(p_gc->name, i, SGMTX_PIPEX_TXALC , alc2reg(  p_gc->gainctl[i].dl_alc  ) );

	}
	return IS_OK;
}




typedef struct {
	uint32_t (*us_tfpow)(int sgmt);
	uint32_t (*us_comp1)(int sgmt);
	uint32_t (*us_comp2)(int sgmt);
	uint32_t (*us_comp3)(int sgmt);
	uint32_t (*pi_chpow)(int sgmt,int ch);
	uint32_t (*pi_rgain)(int sgmt,int ch);
	uint32_t (*ds_comp1)(int sgmt);
	uint32_t (*ds_comp2)(int sgmt);
	uint32_t (*ds_comp3)(int sgmt);
	uint32_t (*ds_tfpow)(int sgmt);
}LINK_REGS;


uint32_t two_arg_fun(int sgmt){
	return 0xFF;
}
uint32_t one_art_fun(int sgmt){
	return 0xFF;
}
//------------
uint32_t ul_adpow_reg(int sgmt){
	printf("11\n");
	return 0x11;
}
uint32_t ul_dapow_reg(int sgmt){
	printf("22\n");
	return 0x22;
}

uint32_t dl_adpow_reg(int sgmt){
	printf("33\n");
	return 0x33;
}
uint32_t dl_dapow_reg(int sgmt){
	printf("44\n");
	return 0x44;
}


uint16_t get_sgmt_mask(int sgmt, linkdir ul)
{
	return 0xFFFF;
}

int get_pipenr(int sgmt)
{
	return 16;
}


//linkstream * ls;

int get_sgmt_raw_val(int sgmt, lnstream_raw * lsraw)
{
	// printf("test_confctrl\n");
	// pi_chpow(au, net , ul, sgmt ,pipe, ad, mask)
	// pi_chpow(au, net , ul, sgmt ,pipe, ad, mask)

	// ru_ulink.dapow_reg(0);
	// ru_dlink.dapow_reg(0);
	uint16_t ul_mask, dl_mask;
	int pipe_nr;
	int i;

	//lsraw->dl->us_tfpow = readnet_sgmt_val(0,0);
	//lsraw->dl->us_comp1 = readnet_sgmt_val(0,0);
	//lsraw->dl->us_comp2 = readnet_sgmt_val(0,0);
	lsraw->dl->us_comp3 = read_sgmt_val(sgmt, 0x50 , 2);
	lsraw->dl->ds_comp1 = read_sgmt_val(sgmt, 0x10 , 2);
	lsraw->dl->ds_comp2 = read_sgmt_val(sgmt, 0x3C , 1);
	lsraw->dl->ds_comp3 = read_sgmt_val(sgmt, 0x3A , 2);
	lsraw->dl->ds_tfpow = read_sgmt_val(sgmt, 0x34 , 4);

	//lsraw->ul->us_tfpow = readnet_sgmt_val(0,0);
	//lsraw->ul->us_comp1 = readnet_sgmt_val(0,0);
	//lsraw->ul->us_comp2 = readnet_sgmt_val(0,0);
	lsraw->ul->us_comp3 = read_sgmt_val(sgmt, 0x50 , 2);
	lsraw->ul->ds_comp1 = read_sgmt_val(sgmt, 0x10 , 2);
	lsraw->ul->ds_comp2 = read_sgmt_val(sgmt, 0x3C , 1);
	lsraw->ul->ds_comp3 = read_sgmt_val(sgmt, 0x3A , 2);
	lsraw->ul->ds_tfpow = read_sgmt_val(sgmt, 0x34 , 4);

	pipe_nr = get_pipenr(sgmt);

	ul_mask = get_sgmt_mask(sgmt, UPLINK );
	dl_mask = get_sgmt_mask(sgmt, DWLINK );

	for(i=0;(i<MAX_NR_PIPES)&&(i<(pipe_nr));i++){

		if( (ul_mask) & (0x01<<i) ){
			lsraw->ul->pi[i].pi_chpow = read_pipe_val(sgmt, 0x50 , i, 2);
			lsraw->ul->pi[i].pi_rgain = read_pipe_val(sgmt, 0x50 , i, 2);
		}
		if( (dl_mask) & (0x01<<i) ){
			lsraw->dl->pi[i].pi_chpow = read_pipe_val(sgmt, 0x50 , i, 2);
			lsraw->dl->pi[i].pi_rgain = read_pipe_val(sgmt, 0x50 , i, 2);
		}
	}

}


int get_sgmt_print_val(lnstream_raw * lsraw, lnstream_pr * lspr)
{

	lspr->ul_us_tfpow=lnksta_formula1__(lsraw->ul->us_tfpow);
	lspr->ul_us_comp1=lnksta_formula2_1(lsraw->ul->us_comp1);
	lspr->ul_us_comp2=lnksta_formula2_2(lsraw->ul->us_comp2);
	lspr->ul_us_comp3=lnksta_formula2_3(lsraw->ul->us_comp3);
	lspr->ul_ds_comp1=lnksta_formula2_1(lsraw->ul->ds_comp1);
	lspr->ul_ds_comp2=lnksta_formula2_2(lsraw->ul->ds_comp2);
	lspr->ul_ds_comp3=lnksta_formula2_3(lsraw->ul->ds_comp3);
	lspr->ul_ds_tfpow=lnksta_formula1__(lsraw->ul->ds_tfpow);

	lspr->dl_us_tfpow=lnksta_formula1__(lsraw->dl->us_tfpow);
	lspr->dl_us_comp1=lnksta_formula2_1(lsraw->dl->us_comp1);
	lspr->dl_us_comp2=lnksta_formula2_2(lsraw->dl->us_comp2);
	lspr->dl_us_comp3=lnksta_formula2_3(lsraw->dl->us_comp3);
	lspr->dl_ds_comp1=lnksta_formula2_1(lsraw->dl->ds_comp1);
	lspr->dl_ds_comp2=lnksta_formula2_2(lsraw->dl->ds_comp2);
	lspr->dl_ds_comp3=lnksta_formula2_3(lsraw->dl->ds_comp3);
	lspr->dl_ds_tfpow=lnksta_formula1__(lsraw->dl->ds_tfpow);


}
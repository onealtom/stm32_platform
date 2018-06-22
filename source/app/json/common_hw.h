#ifndef _COMMON_HW_H
#define _COMMON_HW_H

#include <stdint.h>
#include "port.h"




extern uint32_t sgmtreg_write(char sgmt , uint32_t reg , uint32_t value);
extern uint32_t pipereg_write(char sgmt, uint32_t pipe_sel, uint32_t reg, uint32_t value);
extern uint32_t read_sgmt_val(uint8_t sgmt, uint8_t ad, uint8_t len);
extern uint32_t read_pipe_val(uint8_t sgmt, uint8_t pipe, uint8_t ad, uint8_t len);
extern int get_max_pnr(char sgmt_chr);
//inline int get_pipenr(char sgmt_no);

#define BIT_POS(X)             ( 1U<<(X) )
#define BIT_MASK(H,L)          ( (BIT_POS((H)-(L)+1)-1)<<(L) )
#define VAL_MASKED2(V, H, L)    (((V)&BIT_MASK((H),(L)))>>((H)-(L)+1))
#define VAL_MASKED(V, H, L)    (((V)<<(L))&(BIT_POS((H)-(L)+1)-1))

//----------------BYTE ADDR--------------------
#define PIPE_EN_BIT	 23
#define PIPE_EN_BIT_MASK 0x80

/*
enum valtwenty_index{
	dl_us_comp3,
	dl_pi_chpow,
	dl_pi_rgain,
	dl_ds_comp1,
	dl_ds_comp2,
	dl_ds_comp3,
	dl_ds_tfpow,
	ul_us_comp3,
	ul_pi_rgain,
	ul_pi_chpow,
	ul_ds_comp1,
	ul_ds_comp2,
	ul_ds_comp3,
	ul_ds_tfpow
};

VarField valtwenty[] = {
	[dl_us_comp3] = {  .ad=0x50, .ln=2},
	[dl_ds_comp1] = {  .ad=0x10, .ln=2},
	[dl_ds_comp2] = {  .ad=0x3C, .ln=1},
	[dl_ds_comp3] = {  .ad=0x3A, .ln=2},
	[dl_ds_tfpow] = {  .ad=0x34, .ln=4},

	[dl_pi_chpow] = {  .ad=0x4C, .ln=2},
	[dl_pi_rgain] = {  .ad=0x44, .ln=4},

	[ul_us_comp3] = {  .ad=0x52, .ln=2},
	[ul_ds_comp1] = {  .ad=0x0C, .ln=2},
	[ul_ds_comp2] = {  .ad=0x3D, .ln=1},
	[ul_ds_comp3] = {  .ad=0x38, .ln=2},
	[ul_ds_tfpow] = {  .ad=0x30, .ln=4},

	[ul_pi_rgain] = {  .ad=0x4E, .ln=2},
	[ul_pi_chpow] = {  .ad=0x48, .ln=4},

}
*/


#endif /*_COMMON_HW_H*/
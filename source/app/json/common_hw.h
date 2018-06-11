#ifndef _COMMON_HW_H
#define _COMMON_HW_H

#include <stdint.h>

#define REG_LEN2		8
#define REG_LEN		4
#define SGMTREGS_LEN	(REG_LEN*32)

#define PHYINFO_REGS_BASEAD  0x40000180
#define PHYINFO_PIPENR1_REG  PHYINFO_REGS_BASEAD+(REG_LEN*0x04)
#define PHYINFO_PIPENR2_REG  PHYINFO_REGS_BASEAD+(REG_LEN*0x05)
#define PHYINFO_PIPENR3_REG  PHYINFO_REGS_BASEAD+(REG_LEN*0x06)
#define PHYINFO_PIPENR4_REG  PHYINFO_REGS_BASEAD+(REG_LEN*0x07)
#define PHYINFO_PIPESEL_REG  PHYINFO_REGS_BASEAD+(REG_LEN*0x08)

#define SGMTA_CTLREGS_BASEAD  0x40000200
#define SGMTB_CTLREGS_BASEAD  SGMTA_CTLREGS_BASEAD + (SGMTREGS_LEN*0x01 )
#define SGMTC_CTLREGS_BASEAD  SGMTA_CTLREGS_BASEAD + (SGMTREGS_LEN*0x02 )
#define SGMTD_CTLREGS_BASEAD  SGMTA_CTLREGS_BASEAD + (SGMTREGS_LEN*0x03 )

//Setting Reg Group Addr
#define SGMTX_PIPEX_RXPHASE  0x05 //set
#define SGMTX_PIPEX_TXPHASE  0x06 //set
#define SGMTX_PIPEX_TXGAIN   0x08 //set
#define SGMTX_PIPEX_RXGAIN   0x09 //set
#define SGMTX_PIPEX_TXALC    0x0A //set
#define SGMTX_PIPEX_RXALC    0x0B //set

#define SGMTX_ADHTHR         0x17 //set
#define SGMTX_ADLTHR         0x18 //set
#define SGMTX_DAHTHR         0x19 //set
#define SGMTX_DALTHR         0x1A //set
//---------------------------------------
//Get Status Regs Group Addr
#define SGMTX_PIPEX_DLPOW    0x11 //get
#define SGMTX_PIPEX_ULPOW    0x12 //get
#define SGMTX_PIPEX_RECTGAIN 0x13 //get

#define SGMTX_RXTEMPCOMP     0x03 //get@@
#define SGMTX_TXTEMPCOMP     0x04 //get
#define SGMTX_ADPOW          0x0C //get@@
#define SGMTX_DAPOW          0x0D //get
#define SGMTX_COMP           0x0F //get
#define SGMTX_ATTCOMP        0x0E //get@

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
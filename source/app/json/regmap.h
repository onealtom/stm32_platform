#include "port.h"


#ifdef ZYNQ_PLATFORM
	#define REG_LEN 4
	#define SGMTREGS_LEN	(REG_LEN*32)
	#define SGMTA_CTLREGS_BASEAD  0x40000200
	
	/*用于获取每个sgmt有多少个pipe*/
	#define PHYINFO_PIPESEL_REG  0x400001A0

#endif

#ifdef STM32_PLATFORM
	#define REG_LEN 2
	#define SGMTREGS_LEN	(REG_LEN*0x32)
	#define SGMTA_CTLREGS_BASEAD  (0x60000000+(0x8020*2))

	/*PHYINFO寄存器组 pipesel pipenum*/
	#define PHYINFO_PIPESEL_REG  (0x60000000+(0x8002*2))
#endif



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
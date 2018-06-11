#ifndef _PL_CONFIG_H
#define _PL_CONFIG_H

#include "port.h"

#define pr_err(format, ...)		port_pr_info(format, ## __VA_ARGS__)
#define pr_info(format, ...)		port_pr_info(format, ## __VA_ARGS__)

#define PR_DEBUG
#ifdef PR_DEBUG
   #define LOG() do{printf("%s (%d) %s \n ",__FILE__,__LINE__,__FUNCTION__);}while(0)
   //#define LOG() do{printf("%s %s\n",__DATE__,__TIME__);}while(0)
   #define pr_dbg(fmt,arg...) do{pr_info(fmt,##arg); }while(0)
#else
   #define LOG()
   #define pr_dbg(...) do{ }while(0);
#endif/*PR_DEBUG*/


#define IS_OK		1
#define IS_ERROR	0

#define MAX_NR_PIPES 16





#define THR_DEFAULTS    -18
#define CHN_DEFAULTS    0
#define EXTRA_NUMOF_SGMTS  16  //A~P 最多16个段
#define EXTRA_NUMOF_PIPES  16


typedef enum{DWLINK=0, UPLINK=1} linkdir;

#pragma pack(1)
typedef struct pipe_set_t{
	uint32_t ul_chn;
	uint32_t dl_chn;
	//uint32_t ul_freq;
	//uint32_t dl_freq;
}PIPE_SET_T;
#pragma pack()



#pragma pack(1)
typedef struct segment_set_t {

	char name;
	char net_std;
	uint16_t pipe_nr;      //该段IP物理最大的pipe数，从寄存器获取

	/*本振频率 单位KHz*/
	/*uint32_t精度只能存到KHz,uint64_t可以精确到Hz*/
	uint32_t ul_tx_losc  ; //AU
	uint32_t dl_rx_losc  ; //AU
	uint32_t ul_rx_losc  ; //RU
	uint32_t dl_tx_losc  ; //RU
	/*AU*/
	int8_t dl_adh_thr  ;
	int8_t dl_adl_thr  ;
	int8_t ul_dah_thr  ;
	int8_t ul_dal_thr  ;
	/*RU*/
	int8_t ul_adh_thr  ;
	int8_t ul_adl_thr  ;
	int8_t dl_dah_thr  ;
	int8_t dl_dal_thr  ;

	uint16_t ul_pipe_mask  ;
	uint16_t dl_pipe_mask  ;

	PIPE_SET_T pipe_tab[EXTRA_NUMOF_PIPES];

}SGMT_SET_T;
#pragma pack()

#pragma pack(1)
typedef struct pipe_gainctl_set_t{
	int32_t ul_alc;
	int32_t dl_alc;
	float	ul_gain;
	float	dl_gain;
}PIPE_GAINCTL_SET_T;
#pragma pack()

#pragma pack(1)
typedef struct segment_gainctl_set_t {

	char name;
	char net_std;
	uint16_t pipe_nr;

	PIPE_GAINCTL_SET_T gainctl[EXTRA_NUMOF_PIPES];

}SGMT_GAINCTL_SET_T;
#pragma pack()

typedef  SGMT_SET_T * pSGMT_SET_T;
typedef  PIPE_SET_T * pPIPE_SET_T;

typedef  SGMT_GAINCTL_SET_T * pSGMT_GAINCTL_SET_T;
typedef  PIPE_GAINCTL_SET_T * pPIPE_GAINCTL_SET_T;


//typedef struct segment_dev {
//	pSGMT_SET_T       p_sg;
//	pSGMT_GAINCTL_SET_T  p_gainctl;
//}SGMT_DEV;
//typedef  SGMT_DEV * pSGMT_DEV;


// typedef struct pipe_cat_dat{
// 	int ch_pow;
// 	int rect_gain;
// 	int ch_gain;//calc
// 	int pin;
// 	int pout;
// }PIPE_CAT_DAT;

// typedef struct sgmt_cat_dat{
// 	int ad_pow;
// 	int da_pow;
// 	int ch_gain;//calc
// 	int pin;
// 	int pout;
// }SGMT_CAT_DAT;










#endif

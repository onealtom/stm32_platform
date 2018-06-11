#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chn2freq.h"

struct band_info{
	uint32_t chn_begin;  /*begin channel num of band*/
	uint32_t chn_end;    /*end channel num of band*/
	uint32_t step;     /*Freq step forward per channel num+1, Unit is 0.1MHz */
	uint32_t ul_begin; /*up link begin Freq*/
	uint32_t ul_end ;  /*up link end Freq*/
	uint32_t dl_begin; /*down link begin Freq*/
	uint32_t dl_end;   /*down link end Freq*/

};

const struct band_info gsm_tab[] = {
	/*按照chn大小排列*/
	{  0  ,  124 , 2 ,  8900 ,  9148 ,  9350 ,  9598 },  /*ER-GSM900-H */
	{ 128 ,  251 , 2 ,  8242 ,  8488 ,  8692 ,  8938 },  /*GSM850*/
	{ 259 ,  293 , 2 ,  4506 ,  4574 ,  4606 ,  4674 },  /*GSM450*/
	{ 306 ,  340 , 2 ,  4790 ,  4858 ,  4890 ,  4958 },  /*GSM480*/
	{ 438 ,  516 , 2 ,  7472 ,  7628 ,  7772 ,  7928 },  /*GSM750*/
	{ 940 , 1023 , 2 ,  8732 ,  8898 ,  9182 ,  9348 },  /*ER-GSM900-L*/
	//{ 512 ,  885 , 2 , 17102 , 17848 , 18052 , 18798 },  /*DCS1800*/
	//{ 512 ,  810 , 2 , 18502 , 19098 , 19302 , 19898 },  /*PCS1900*/
};

const struct band_info dcs1800_tab[] = {
	{ 512 ,  885 , 2 , 17102 , 17848 , 18052 , 18798 },  /*DCS1800*/
};

const struct band_info pcs1900_tab[] = {
	{ 512 ,  810 , 2 , 18502 , 19098 , 19302 , 19898 },  /*PCS1900*/
};

const struct band_info cdma_tab[] = {
	 {NULL, 0},
};

const struct band_info umts_tab[] = {
	 {NULL, 0},
};

const struct band_info tdscdma_tab[] = {
	{   9404 ,  9596 , 2 ,  18808 ,  19192 ,  18808 ,  19192 },
	{  10054 , 10121 , 2 ,  20108 ,  20242 ,  20108 ,  20242 },
	{  11504 , 11996 , 2 ,  23008 ,  23992 ,  23008 ,  23992 },
};

const struct band_info lte_tab[] = {
	/*下行表，的通道号对应的频率是6,7两列，4,5两列为配对的上行频率*/
	{  2400 ,  2649 , 1 ,  8240 ,  8489 ,  8690 ,  8939 },  /*FDD BAND5 DL*/
	{  2650 ,  2749 , 1 ,  8300 ,  8399 ,  8750 ,  8849 },	/*FDD BAND6 DL*/
	{  2750 ,  3449 , 1 , 25000 , 25699 , 26200 , 26899 },	/*FDD BAND7 DL*/
	{  3450 ,  3799 , 1 ,  8800 ,  9149 ,  9250 ,  9599 },	/*FDD BAND8 DL*/

	/*上行表，的通道号对应的频率是4,5两列，6,7两列为配对的上行频率*/
	{ 20400 , 20649 , 1 ,  8240 ,  8489 ,  8690 ,  8939 },  /*FDD BAND5 UL*/
	{ 20650 , 20749 , 1 ,  8300 ,  8399 ,  8750 ,  8849 },  /*FDD BAND6 UL*/
	{ 20750 , 21449 , 1 , 25000 , 25699 , 26200 , 26899 },  /*FDD BAND7 UL*/
	{ 21450 , 21799 , 1 ,  8800 ,  9149 ,  9250 ,  9599 },  /*FDD BAND8 UL*/

	/*TD的上行下行频率一样，4，5列与6,7列相同*/
	{ 37750 , 38249 , 1 , 25700 , 26199 , 25700 , 26199},  /*TD BAND38*/
	{ 38250 , 38649 , 1 , 18800 , 19199 , 18800 , 19199},  /*TD BAND39*/
	{ 38650 , 39649 , 1 , 23000 , 23999 , 23000 , 23999},  /*TD BAND40*/
	{ 39650 , 41589 , 1 , 24960 , 26899 , 24960 , 26899},  /*TD BAND41*/
};

/**
 * @brief 计算频点号对应的频率
 * @details 根据主时钟，本振，信号频率，计算相位字寄存器，统一单位为KHz
 *
 * @param net_std 网络制式
 * @param chn 频点号
 * @param dir 上行或下行标志位，UP_LINK=0 , DW_LINK=1
 * @return 返回频率值，单位0.1MHz，如果不在支持范围，返回0
 */
extern uint32_t chn2freq( char net_std, uint32_t chn, enum lnkdir dir)
{
	int i;
	uint32_t ul_freq=0,dl_freq=0, freq=0;
	int mode;

#define MY_ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]) )

#define	TRAV_TAB(x) do { \
	for (i = 0; i < MY_ARRAY_SIZE((x ## _tab)); i++){                                                            \
		if( (chn >= (x ## _tab)[i].chn_begin) && (chn <= (x ## _tab)[i].chn_end)  ){                         \
			ul_freq = (x ## _tab)[i].ul_begin + (chn - (x ## _tab)[i].chn_begin) * (x ## _tab)[i].step ; \
			dl_freq = (x ## _tab)[i].dl_begin + (chn - (x ## _tab)[i].chn_begin) * (x ## _tab)[i].step ; \
			break;                                                                                       \
		}                                                                                                    \
	}                                                                                                            \
}while(0)

//#define NUM_OF_MODE 7
//enum  mode_num{  GSM=0 , DCS1800 , PCS1900, CDMA, UMTS, TDSCDMA, LTE  };
//const char *mode_num[]={ "GSM" , "DCS1800" , "PCS1900", "CDMA", "UMTS", "TDSCDMA", "LTE"  };

	//for(i=0; i<NUM_OF_MODE; i++){
	//	if( strcmp(net_std ,mode_num[i])==0){
	//		//printf("mode_num: %s\n", mode_num);
	//		break;
	//	}
	//}

	switch(net_std){
	case 'G'://GSM
		c2fdbg("GSM format:\n");
		TRAV_TAB(gsm);
		freq = ( dir==UP_LINK )? ul_freq : dl_freq ;
		break;
	case 'D'://DCS1800
		c2fdbg("DCS1800 format:\n");
		TRAV_TAB(dcs1800);
		freq = ( dir==UP_LINK )? ul_freq : dl_freq ;
		break;
	case 'P'://PCS1900
		c2fdbg("PCS1900 format:\n");
		TRAV_TAB(pcs1900);
		freq = ( dir==UP_LINK )? ul_freq : dl_freq ;
		break;
	case 'C'://CDMA
		c2fdbg("CDMA not support\n");
		return 0;
		break;
	case 'U'://UMTS
		c2fdbg("UMTS not support\n");
		return 0;
		break;
	case 'T'://TDSCDMA
		c2fdbg("TDSCDMA format:\n");
		return 0;
		break;
	case 'L'://LTE
		c2fdbg("LTE format:\n");
		TRAV_TAB(lte);
		freq = ( dir==UP_LINK )? ul_freq : dl_freq ;
		break;
	default:
		return 0;
		break;
	}

	c2fdbg("ul=%d,dl=%d\n",ul_freq, dl_freq);
	c2fdbg("freq=%d\n",freq);
	return freq;

}


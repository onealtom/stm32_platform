#ifndef _FREQ2FIELD_H
#define _FREQ2FIELD_H

#include<stdint.h>
//#include"chn2freq.h"

#define SEGMENT_A		'A'
#define SEGMENT_B		'B'
#define SEGMENT_C		'C'
#define SEGMENT_D		'D'

struct channel_device{
	uint8_t pipe;		//save
	uint8_t sys_chn_num;		/*系统处理段中当前的通道号*///save
	uint8_t dir;			//save dev_s.c.d
	uint32_t band_channel;		/*频道号，频点号*/	//save
};

struct segment_info{
	uint8_t segment_num;		//save
	uint32_t lo_osc_downlink;	//save
	uint32_t lo_osc_uplink;		//save
	char format[4];			//save
	char band[8];			//save
	uint8_t range_uplink;
	uint8_t range_downuplink;
	uint16_t max_sys_chn_num;		/*该断内支持的最大通道数*/
	uint8_t fixsubf;
};

struct channel_info{
	struct segment_info *pipe;
	uint8_t sav_sgmt_num;		//save
	uint8_t sys_chn_num;		/*系统处理段中当前的通道号*///save
	uint8_t dir;			//save dev_s.c.d
#define UL_RX_RU		0x00  //00b
#define UL_TX_AU		0x01  //01b
#define DL_RX_AU		0x02  //10b
#define DL_TX_RU		0x03  //11b
	uint32_t band_channel;		/*频道号，频点号*/	//save
	uint32_t freq;
	uint32_t field;
};

int freq2field(struct channel_info *chn_dev  );

#endif

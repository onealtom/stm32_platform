#ifndef _CHN2FREQ_H
#define _CHN2FREQ_H

#include<stdint.h>

//#define  FREQ_DEBUG

#ifdef FREQ_DEBUG
   //#define LOG() do{printf("%s(%d) %s\n",__FILE__,__LINE__,__FUNCTION__);}while(0)
   #define c2fdbg(fmt,arg...) do{printf(fmt,##arg); }while(0)
#else
   #define c2fdbg(...) do{ }while(0);
#endif

enum lnkdir{ UP_LINK=0 , DW_LINK };




/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param mode 网络制式
 * @param chn 频点号
 * @param dir 方向，上行或下行，net_std为LTE时无效
 * @return channel 对应的频率值，单位0.1MHz，返回0表示制式或band不支持
 */
extern uint32_t chn2freq( char net_std, uint32_t chn, enum lnkdir dir);

#endif

/*
Example：
chn2freq(GSM, 225, UP_LINK);     //GSM  return 8436
chn2freq(DCS1800, 885, UP_LINK); //DCS1800  return 17848
chn2freq(LTE, 38423, 0);         //FDD-LTE  return 18973, not case 3rd arg
chn2freq(LTE, 2559, DW_LINK);    //TD-LTE return 8399(up link), not case 3rd arg
chn2freq(LTE, 2559, UP_LINK);    //TD-LTE return 8399(up link), not case 3rd arg
*/
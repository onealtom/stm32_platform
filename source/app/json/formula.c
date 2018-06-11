#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "pl_config.h"
#include "common_hw.h"
#include "chn2freq.h"

#ifndef __GNUC__
static inline double pow10(double x)
{
	return pow(10, x);
}
#endif


/***********************
AD功率调节门限、DA功率调节门限
公式：
thr = 10*log10(reg/2^24)
=>
reg[23:0] = 10^(thr/10) * 2^24
舍弃小数部分

寄存器范围[0x1,0xFFFFFF]
寄存器代表变量的数学范围: (0,2^24-1]
thr参数可取范围[-75,0]
***********************/
uint32_t thr2reg(int thr)
{
	//return (uint32_t)(( ((2<<(24-1))-1) * pow10((double)thr/10)) + 0.5 );
	//return (uint32_t)(( 16777216 * pow10((float)thr/10)) + 0.5 );
	double tmp;

	tmp = 16777216 * pow10((float)thr/10) + 0.5;
	tmp = (uint32_t)tmp;
	if (0xFFFFFF<=tmp)
		tmp = 0xFFFFFF;

	return tmp;
}

/***********************
通道增益（db）公式：
gain = 20*log10(reg/(2^8))
reg[15:0] = 2^8 * 10^(gain/20)
***********************/
extern uint32_t gain2reg(float gain)
{
	return (uint32_t)( 256 * pow10((float)gain/20) +0.5 );
}

/***********************
ALC 公式：
alc=10*log10(reg[26:0]/2^27)
reg[26:0]=2^27*10^(alc/10)
***********************/
uint32_t alc2reg(int alc)
{
	//return (uint32_t)( ((2<<(27-1))-1) * pow10((float)alc/10) + 0.5 );
	//return (uint32_t)(( 134217728 * pow10((float)alc/10)) + 0.5 );

	double tmp;

	tmp = 134217728 * pow10((float)alc/10) + 0.5;
	tmp = (uint32_t)tmp;
	if (0x7FFFFFF<=tmp)
		tmp = 0x7FFFFFF;

	return tmp;

}

/**
 * @brief 计算频率寄存器值
 * @details 根据主时钟，本振，信号频率，计算相位字寄存器，统一单位为KHz
 *
 * @param mclk 主时钟
 * @param losc 本振频率
 * @param freq 信号频率
 * @return [description]
 f_REQ=abs(信号输入频率-AD本振)
FREQ[CH_SEL][25:0]=2^13*1024*8*(1/Fs)*f_REQ
 */
uint32_t freq2reg(uint32_t  mclk, uint32_t losc , uint32_t freq)
{
	uint32_t sft ;
	float tmp;
	uint32_t reg;


pr_dbg("mclk=%d, losc=%d, freq=%d\n",mclk , losc , freq);

	sft = abs(freq - losc);

	tmp = (float)sft/mclk;

	reg = (uint32_t)(67108864 * tmp);

	/*符号位*/
	if( (freq-losc)<0 )
		reg= reg | (1U<<28);

	/*使能位*/
	reg = reg | (1U<<31);

	return reg;
}

int freq2phase(uint32_t  mclk, uint32_t losc , uint32_t freq)
{
	uint32_t sft ;
	double tmp;
	int phase;
	//614400,874500,829500
mclk=614400;
losc=874500;
freq=829500;
pr_dbg("mclk=%d, losc=%d, freq=%d\n",mclk , losc , freq);


	tmp = ((double)freq - (double)losc)/(double)mclk;
printf("%f\n",tmp);
	phase = (int)(67108864 * tmp);

	return phase;
}

uint32_t phase2rureg(int phase)
{
	uint32_t reg=0;

	reg = abs(phase);
pr_dbg("reg=%x\n",reg);
	/*符号位*/
	if ( phase<0 )
		reg = reg | (1U<<28);

	/*使能位*/
	reg = reg | (1U<<31);
	return reg;
}

uint32_t phase2aureg(int phase)
{
	uint32_t tmp;
	uint32_t reg;

	tmp = 0x7FFFFFFF&phase;

	/*lsb*/
	reg = (tmp & BIT_MASK(11,0));
	/*msb*/
	reg |= (tmp & BIT_MASK(25,12))<<12;

	/*符号位*/
	if ( phase<0 )
		reg |= (1U<<31);

	/*使能位*/
	reg |= (1U<<15);

	return reg;
}



uint32_t field2reg(uint32_t field)
{
	
struct reg_freq_input_lsb{
	uint16_t lsb	 : 12;
	uint8_t reserved : 3;
	_Bool chn_en	 : 1;
}freq_input_lsb;

struct reg_freq_input_msb{
	uint16_t msb	 : 14;
	uint8_t reserved : 1;
	_Bool sign	 : 1;
}freq_input_msb;

	uint16_t *p_lsb;
	uint16_t *p_msb;

	freq_input_lsb.reserved = 0;
	freq_input_lsb.lsb = field;
	freq_input_lsb.chn_en = 1;

	freq_input_msb.reserved = 0;
	freq_input_msb.msb = field>>12;
	freq_input_msb.sign = 1;

	p_lsb = (uint16_t*)&freq_input_lsb;
	p_msb = (uint16_t*)&freq_input_msb;

	return (0xFFFF0000&((*p_msb)<<16))|(0x0000FFFF&(*p_lsb));

}

// 链路状态公式

/**
 * @brief 公式1, 适用于AD/DA功率
 * @details 10*log10(D_CH_SPOW[31:0]/2^32)+Pdn
 *寄存器范围: [0x1,0xFFFFFFFF]
寄存器代表变量的数学范围: [1,2^32-1]
参数可取范围: [-86.3296,10]
 * @param reg 传入32bit max=4294967295
 * @return [description]
 */
float lnksta_formula1__(uint32_t reg)
{
	reg =(0==reg)?1:reg;
	return 10*log10(reg/4294967296.0)+10;
}

/**
 * @brief 公式2-1, 适用于温度补偿
 * @details reg=int[10^(TCOFF/20)*4096]
 *          TCOFF = 20*log(reg/4096)
寄存器范围: [0x1,0x0000FFFF]
寄存器代表变量的数学范围: [1,2^16-1]
参数可取范围: [-72.2472,24.0823]
 * @param reg 传入16bit max=65536
 * @return [description]
 */
float lnksta_formula2_1(uint16_t reg)
{
	reg =(0==reg)?1:reg;
	return 20*log10(reg/4096.0);
}

/**
 * @brief 公式2-2, 适用于ATT补偿
 * @details 2^8*10^(index/20)
二进制部分：index=[0,30] 时,value=2^8*10^(index/20)，value取整后转为二进制即可
二进制部分：index=[31,63] 时，value=2^8*10^(30/20)，value取整后转为二进制即可
十进制部分，带小数：20*log10(取整(value)/2^8)

 * @param index 传入6bit max=64
 * @return 最大值405733,最小值0
 */
float lnksta_formula2_2(uint8_t index)
{
	//return 256*pow10(index/20);
	return (float)index;
}

/**
 * @brief 公式2-3, 适用于总补偿
 * @details 20*log(REC_FG_CMPS[15:0]/(2^8))
 *寄存器范围: [0x1,0x0000FFFF]
寄存器代表变量的数学范围: [1,2^16-1]
参数可取范围: [-48.1648,48.1647]
 * @param reg 传入16bit max=65536
 * @return [description]
 */
float lnksta_formula2_3(uint16_t reg)
{
	reg =(0==reg)?1:reg;
	//return 20*log10(reg/(0x01<<8));
	return 20*log10(reg/256);
}

/**
 * @brief 公式3, 使用于修正增益
 * @details 20*log(D_SDLT_GAIN[15:0]/(2^16))
寄存器范围: [0x1,0x0000FFFF]
寄存器代表变量的数学范围: [1,2^16-1]
参数可取范围: [-96.3296,-0.00013254]
 * @param reg 传入32bit max=4294967295
 * @return [description]
 */
float lnksta_formula3__(uint32_t reg)
{
	reg =(0==reg)?1:reg;
	return 20*log10(reg/65536);
}
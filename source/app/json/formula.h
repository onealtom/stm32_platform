#ifndef _FORMAULA_H
#define _FORMAULA_H


uint32_t thr2reg(int thr);

extern uint32_t gain2reg(float gain);

uint32_t alc2reg(int alc);

//uint32_t freq2reg(float mclk, uint losc , uint freq);
uint32_t freq2reg(uint32_t  mclk, uint32_t losc , uint32_t freq);
#endif

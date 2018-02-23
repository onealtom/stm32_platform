/************************************************************

     Copyright (C), 2011-2111, ����̩�˿Ƽ����޹�˾

*************************************************************
�ļ�����   TIMER_DRV_H_
�汾�ţ�   V03
���ߣ�     Τ��� 
�������ڣ� 2010��08��05��
����޸ģ� 
���������� TIMER_DRV_H_�ĵײ�����ͷ�ļ� 
�����б�  
�޸����ڣ� 
        1.����:      2010��08��05��  
          ���ߣ�     Τ��� 
          �޸����ݣ� ԭ��
        2.����:      2012��04��17��  
          ���ߣ�     ����ǫ
          �޸����ݣ� ΢�͹�ǥV02   
**************************************************************/
#ifndef _TIMER_DRV_H_
#define _TIMER_DRV_H_

#define ONE_S_COUNT			10
#define TWO_S_COUNT			20
#define THREE_S_COUNT		30
#define FIVE_S_COUNT		50
#define TEN_S_COUNT			100

void UsNopDelay(UINT32 ustime);
void UsNopDelay_1(UINT32 ustime);

void InitTimeTick(void);
void Timer100msHandle(void);

#endif 



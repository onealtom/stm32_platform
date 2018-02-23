/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司

*************************************************************
文件名：   TIMER_DRV_H_
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： TIMER_DRV_H_的底层驱动头文件 
函数列表：  
修改日期： 
        1.日期:      2010年08月05日  
          作者：     韦瑞锦 
          修改内容： 原版
        2.日期:      2012年04月17日  
          作者：     邓子谦
          修改内容： 微型光钎V02   
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



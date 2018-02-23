/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司

*************************************************************
文件名：   TIMER_DRV_C_
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： TIMER_DRV_C_的底层驱动文件 
函数列表：  
修改日期： 
        1.日期:      2010年08月05日  
          作者：     韦瑞锦 
          修改内容： 原版
        2.日期:      2012年04月17日  
          作者：     邓子谦
          修改内容： 微型光钎V02 
**************************************************************/
#include "Header.h"


__ASM void __nop__delay(void)
{
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	bx lr
}

__ASM void __nop_5__delay(void)
{
	nop
	nop
	nop
	nop
	nop
	bx lr
}

void _UsDelay_1()
{
	__nop_5__delay();

}

/*************************************************************
Name:UsNopDelay          
Description:用nop作为延时
Input:us级别的时间            
Output:void         
Return:void         
**************************************************************/
void UsNopDelay_1(UINT32 ustime)
{
	UINT32 i;
	for (i=0; i<ustime; i++)
	{
		_UsDelay_1();
	}
}

void _UsDelay()
{
	__nop__delay();
	__nop__delay();
}

/*************************************************************
Name:UsNopDelay          
Description:用nop作为延时
Input:us级别的时间            
Output:void         
Return:void         
**************************************************************/
void UsNopDelay(UINT32 ustime)
{
	UINT32 i;
	for (i=0; i<ustime; i++)
	{
		_UsDelay();
	}
}

/*************************************************************
Name:InitTimeTick          
Description: 初始化系统时钟节拍
Input:void     
Output:void         
Return:void         
**************************************************************/
void InitTimeTick()
{
	// 初始化系统时钟节拍为100ms
	//TRACE_INFO("Init Sys Time Tick\r\n");
	if (SysTick_Config(SystemFrequency / (1000/100)))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/*************************************************************
Name:Timer100msHandle          
Description:100ms的系统定时器处理函数
Input:void            
Output:void         
Return:void         
**************************************************************/
void Timer100msHandle(void)
{
	static UCHAR8 one_second=0,fpga_read_second=0,read_coff_second=0;//,repeate_init_second=0;

	if (one_second++ == ONE_S_COUNT)
	{
		one_second = 0;
		sys_work_info |= SYSTEM_FLAG_1S_EVENT;
	}

	if (fpga_read_second++==THREE_S_COUNT)
	{
		fpga_read_second = 0;		
		sys_work_info |= SYSTEM_FLAG_3S_EVENT;		//置填充监控度参数标志
	}
	
	if (read_coff_second++==FIVE_S_COUNT)
	{
		read_coff_second = 0;		
		sys_work_info |= SYSTEM_FLAG_5S_EVENT;		//读取滤波系数，计算隔离度
	}

}



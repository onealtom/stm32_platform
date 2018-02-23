/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :timer.c
* Description :时间处理相关函数
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			初始版本
**************************************************************/
#include "Header.h"
//#include "driver.h"

extern volatile UINT32 sys_work_info;

#if 0
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
	__asm{
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
		nop
		
	};
	}
}

/*************************************************************
Name:UsDelay          
Description:
Input:us级别的时间            
Output:void         
Return:void         
**************************************************************/
void UsDelay(UINT32 ustime)
{
	UsNopDelay(ustime);	
}
/*************************************************************
Name:RS485Delay          
Description:485发送完最后一个字节后延时后
			将发使能关闭
Input:void      
Output:void         
Return:void         
**************************************************************/
void Rs485Delay(void)
{
#if 0
	T2CON = (0x01<<6)|(0x01<<10);			//32.768,periodic mode,disable timer
	T2LD = (15*32768)/RS485_BAUD;				//延时15个bits
	T2CLRI  = 1;					//Clear
	T2CON |= (0x01<<7);			//Timer start
	IRQEN |= (0x01<<INT_TIMER2);
#endif
			
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
	UINT32 status = AT91C_BASE_TC0->TC_SR;


	if ((status & AT91C_TC_CPCS) != 0) 
	{	
		if (one_second++ == ONE_S_COUNT)
		{
			one_second = 0;
			sys_work_info |= SYSTEM_FLAG_1S_EVENT;
			//TRACE_INFO( "1s\r\n" );
//			FLASH_LED;
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
		//TRACE_INFO( "Tisr_%d_%d\r\n",one_second, fpga_read_second );
	}
	AT91C_BASE_TC0->TC_CCR = AT91C_TC_CLKEN | AT91C_TC_SWTRG;
}
#endif


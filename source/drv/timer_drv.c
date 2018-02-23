/************************************************************

     Copyright (C), 2011-2111, ����̩�˿Ƽ����޹�˾

*************************************************************
�ļ�����   TIMER_DRV_C_
�汾�ţ�   V03
���ߣ�     Τ��� 
�������ڣ� 2010��08��05��
����޸ģ� 
���������� TIMER_DRV_C_�ĵײ������ļ� 
�����б�  
�޸����ڣ� 
        1.����:      2010��08��05��  
          ���ߣ�     Τ��� 
          �޸����ݣ� ԭ��
        2.����:      2012��04��17��  
          ���ߣ�     ����ǫ
          �޸����ݣ� ΢�͹�ǥV02 
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
Description:��nop��Ϊ��ʱ
Input:us�����ʱ��            
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
Description:��nop��Ϊ��ʱ
Input:us�����ʱ��            
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
Description: ��ʼ��ϵͳʱ�ӽ���
Input:void     
Output:void         
Return:void         
**************************************************************/
void InitTimeTick()
{
	// ��ʼ��ϵͳʱ�ӽ���Ϊ100ms
	//TRACE_INFO("Init Sys Time Tick\r\n");
	if (SysTick_Config(SystemFrequency / (1000/100)))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/*************************************************************
Name:Timer100msHandle          
Description:100ms��ϵͳ��ʱ��������
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
		sys_work_info |= SYSTEM_FLAG_3S_EVENT;		//������ضȲ�����־
	}
	
	if (read_coff_second++==FIVE_S_COUNT)
	{
		read_coff_second = 0;		
		sys_work_info |= SYSTEM_FLAG_5S_EVENT;		//��ȡ�˲�ϵ������������
	}

}



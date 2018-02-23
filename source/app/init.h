/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :init.h
* Description :
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			初始版本
**************************************************************/
#ifndef _INIT_H
#define _INIT_H
 
#include "ex_conf.h"

/*****************************1~12月份********************************************************/
#define MONTH_CODE_JAN			(('j')<<16|('a'<<8)|('n')) 
#define MONTH_CODE_FEB			(('f')<<16|('e'<<8)|('b')) 
#define MONTH_CODE_MAR		    (('m')<<16|('a'<<8)|('r')) 
#define MONTH_CODE_APR		    (('a')<<16|('p'<<8)|('r')) 
#define MONTH_CODE_MAY		    (('m')<<16|('a'<<8)|('y')) 
#define MONTH_CODE_JUN			(('j')<<16|('u'<<8)|('n')) 
#define MONTH_CODE_JUL			(('j')<<16|('u'<<8)|('l')) 
#define MONTH_CODE_AUG		    (('a')<<16|('u'<<8)|('g')) 
#define MONTH_CODE_SEP			(('s')<<16|('e'<<8)|('p')) 
#define MONTH_CODE_OCT		    (('o')<<16|('c'<<8)|('t')) 
#define MONTH_CODE_NOV		    (('n')<<16|('o'<<8)|('v')) 
#define MONTH_CODE_DEC		    (('d')<<16|('e'<<8)|('c')) 



void InitSystemTimer(void);
BOOL InitAD(void);
//void ThrUartConfig();
void CtrlUartConfig(); 
void InitSystem();
CHAR8 CheckStrDate( UCHAR8* p_str, UINT16 day, UINT16 month, UINT16 year );
BOOL InitAD9779(UCHAR8 ab_flag);
BOOL InitAD9524(void);
BOOL InitClkChip(void);
void InitKeyDev(void);
BOOL InitAllKeyDev(void);
#endif 



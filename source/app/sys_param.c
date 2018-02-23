/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :sys_param.c
* Description :系统参数处理相关函数
* Version     :v0.1
* Author      :RJ
* Date        :2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			初始版本
**************************************************************/
#include "Header.h"

//外部变量声明
extern UCHAR8 sys_temp_buff[SYS_TMP_BUFF_SIZE];
extern _T_PARAM_1B sys_param_1b[];
extern _T_PARAM_2B sys_param_2b[];
extern _T_PARAM_4B sys_param_4b[];
extern _T_PARAM_ASC sys_param_asc[];
extern _T_VALID_FP_TOPO valid_fp_topo[];
extern _T_MODULE_CFG mod_cfg_a;
extern UINT16 tds_dl_channel[19];

//本文件内变量声明
UCHAR8 para_bak[2+SYS_PARAM_1B_COUNT+(SYS_PARAM_2B_COUNT*2)+(SYS_PARAM_4B_COUNT*4)+(SYS_PARAM_ASC_COUNT*64)];//含两个字节的前缀-0XE7,0X5C
UINT32 module_param_chg_flag = 0xFFFFFFFF;		//系统工作参数修改标志

UINT16 mo_param_count_a = 0;
UINT16 mo_param_count_b = 0;
UINT16 mo_param_count_c = 0;
UINT16 mo_param_count_d = 0;
UCHAR8 G2Tpye = G2_TYPE_CNMOBILE;

/*************************************************************
Name:GetValidTopo          
Description:保存系统参数到外部FLASH中
Input:base_flag:0:不改变基本信息，1:改变了基本信息
Output:void         
Return:void
**************************************************************/
void GetValidTopo()
{
	UINT32 i,j;
	UINT32 length = 0;
	UCHAR8 tmp, re_cnt;
	UCHAR8 * p_dat = sys_temp_buff;

	//FlashReadOnePage(FLASH_TOPO_PAGE, 0, p_dat);

	if ( (0xEB!=p_dat[0])&&(0x90!=p_dat[1]) )
	{
		return;
	}

	p_dat += 2;
	
	for ( i=0; i<FP_MAX; i++ )
	{
		tmp = *p_dat++;
		re_cnt = *p_dat++;

		if ( re_cnt>RE_MAX )
		{
			return;
		}
		
		valid_fp_topo[i].fp_mode = tmp;
		valid_fp_topo[i].re_count = re_cnt;
		
		for ( j=0; j<valid_fp_topo[i].re_count; j++ )
		{
			valid_fp_topo[i].re_inf[j].id = *p_dat++;
			valid_fp_topo[i].re_inf[j].mode = *p_dat++;
		}
	}
}


/*************************************************************
Name:SaveSystemPara          
Description:保存系统参数到外部FLASH中
Input:base_flag:0:不改变基本信息，1:改变了基本信息
Output:void         
Return:void
**************************************************************/
void SaveValidTopo()
{
	UINT32 i,j;
	UINT32 length = 0;
	UCHAR8 * p_dat = sys_temp_buff;

	p_dat[length++] = 0xEB;
	p_dat[length++] = 0x90;
	
	for ( i=0; i<FP_MAX; i++ )
	{
		p_dat[length++] = valid_fp_topo[i].fp_mode;
		p_dat[length++] = valid_fp_topo[i].re_count;
		for ( j=0; j<valid_fp_topo[i].re_count; j++ )
		{
			p_dat[length++] = valid_fp_topo[i].re_inf[j].id;
			p_dat[length++] = valid_fp_topo[i].re_inf[j].mode;
		}
	}

	//FlashWriteOnepage(FLASH_TOPO_PAGE, p_dat, length, 1);

}

/*************************************************************
Name:GetSystemPara          
Description:从外部FLASH中读取系统参数
Input:void      
Output:void         
Return:void
**************************************************************/
void GetSysParamFromFlash(void)
{

	UINT32 i,j; 
	UINT32 length;
	UCHAR8 val_8;
	UINT16 val_16;
	UINT32 val_32;
	UINT16 count;
	UINT16 page;
	UCHAR8 * p_dat;
//TRACE_INFO("0GetSysParamFromFlash\r\n");
	p_dat = sys_temp_buff;
	
	//取1字节参数  
	page = FLASH_PARAM_1B_PAGE; 
//	FlashReadOnePage(page, 0, sys_temp_buff);
	FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
//TRACE_INFO("1GetSysParamFromFlash\r\n");	
	if (( 0xEB==sys_temp_buff[0] )&&( 0x90==sys_temp_buff[1] ))
	{
		count = 2;
		
		for ( i=0; i<SYS_PARAM_1B_COUNT; i++ )
		{
			sys_param_1b[i].val = p_dat[count++];
			// 若此页读取完毕则读取下一页
			if ( count>FLASH_PAGE_SIZE-1 )
			{
				count = 0; 
				page++; 
//				FlashReadOnePage(page, 0, sys_temp_buff);
				FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
			}      
		}
	}
	else
	{
		TRACE_ERROR("No Data in Flash 1B Param Page!\r\n");
	}
//TRACE_INFO("2GetSysParamFromFlash\r\n");
	//取2字节参数
	page = FLASH_PARAM_2B_PAGE;
//	FlashReadOnePage(page, 0, sys_temp_buff);
	FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
	if (( 0xEB==sys_temp_buff[0] )&&( 0x90==sys_temp_buff[1] ))
	{
		count = 2;
		for ( i=0; i<SYS_PARAM_2B_COUNT; i++ )
		{
			val_16 = (p_dat[count])|(p_dat[count+1]<<8);		//低位在前
			sys_param_2b[i].val = val_16;
			count += 2;
			// 若此页读取完毕则读取下一页
			if ( count>FLASH_PAGE_SIZE-2 )
			{
				count = 0;
				page++;
//				FlashReadOnePage(page, 0, sys_temp_buff);
				FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
			}
		}
	}
	else
	{
		TRACE_ERROR("No Data in Flash 2B Param Page!\r\n");
	}
	//取4字节参数
	page = FLASH_PARAM_4B_PAGE;
//	FlashReadOnePage(page, 0, sys_temp_buff);
	FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
	//TRACE_INFO("5GetSysParamFromFlash\r\n");
	if (( 0xEB==sys_temp_buff[0] )&&( 0x90==sys_temp_buff[1] ))
	{
		count = 2;
		for ( i=0; i<SYS_PARAM_4B_COUNT; i++ )
		{
			val_32 = (p_dat[count])|(p_dat[count+1]<<8)|(p_dat[count+2]<<16)|(p_dat[count+3]<<24);	//低位在前
			sys_param_4b[i].val = val_32;
			count += 4;
			// 若此页读取完毕则读取下一页
			if ( count>FLASH_PAGE_SIZE-4 )
			{
				count = 0;
				page++;
//				FlashReadOnePage(page, 0, sys_temp_buff);
				FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
			}
		}
	}
	else
	{
		//TRACE_ERROR("No Data in Flash 4B Param Page!\r\n");
	}

	//取字符串参数
	page = FLASH_PARAM_ASC_PAGE;
//	FlashReadOnePage(FLASH_PARAM_ASC_PAGE, 0, sys_temp_buff);
	FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
	
	if (( 0xEB==sys_temp_buff[0] )&&( 0x90==sys_temp_buff[1] ))
	{
		count = 2;
		for ( i=0; i<SYS_PARAM_ASC_COUNT; i++ )
		{
			
			//length = p_dat[count++];
			length= sys_param_asc[i].length;
			// 若此页读取完毕则读取下一页
			if ( count>FLASH_PAGE_SIZE-1 )
			{
				count = 0;
				page++;
//				FlashReadOnePage(page, 0, sys_temp_buff);
				FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
			}
			
			for ( j=0; j<length; j++ )
			{
				val_8 = p_dat[count++];
				sys_param_asc[i].p_asc[j] = val_8;
				// 若此页读取完毕则读取下一页
				if ( count>FLASH_PAGE_SIZE-1 )
				{
					count = 0;
					page++;
//					FlashReadOnePage(page, 0, sys_temp_buff);
					FlashRead(page, 0, sys_temp_buff,FLASH_PAGE_SIZE);
				}
			}
			// sys_param_asc[i].length = j;
		}
	}
	else
	{
		TRACE_ERROR("No Data in Flash Asc Param Page!\r\n");
	}
	
	WTD_CLR;
	
 }


/*************************************************************
Name:SaveSysParamToFlash          
Description:保存系统参数到外部FLASH中
Input:base_flag:0:不改变基本信息，1:改变了基本信息
Output:void         
Return:void
**************************************************************/
void SaveSysParamToFlash(void)
{
	UINT32 i,j;
	UINT32 length;
	UCHAR8 val_8;
	UINT16 val_16;
	UINT32 val_32;
	UINT16 page;
	UCHAR8 * p_dat;

	//TRACE_INFO("Save Param To Flash ");


	//保存1字节参数
	p_dat = sys_temp_buff;
	page = FLASH_PARAM_1B_PAGE;
	length = 0;
	p_dat[length++] = 0xEB;
	p_dat[length++] = 0x90;
	for ( i=0; i<SYS_PARAM_1B_COUNT; i++ )
	{
		p_dat[length++] = sys_param_1b[i].val;
		// 若数据满1页则先存储
		if ( length > FLASH_PAGE_SIZE-1 )
		{
//			FlashWriteOnepage( page, p_dat, length, 1 );	
			FlashWrite( page,0, p_dat, length,1);	// 写入数据
			page++;
			length = 0;
		}
	}
//	FlashWriteOnepage( page, p_dat, length, 1 );	
	FlashWrite( page,0, p_dat, length,1);	// 写入数据

	//保存2字节参数
	p_dat = sys_temp_buff;
	page = FLASH_PARAM_2B_PAGE;
	length = 0;
	p_dat[length++] = 0xEB;
	p_dat[length++] = 0x90;
	for ( i=0; i<SYS_PARAM_2B_COUNT; i++ )
	{
		val_16 = sys_param_2b[i].val;
		//低位在前
		p_dat[length++] = (UCHAR8)(val_16&0x00FF);
		p_dat[length++] = (UCHAR8)((val_16>>8)&0x00FF);
		// 若数据满1页则先存储
		if ( length > FLASH_PAGE_SIZE-2 )
		{
//			FlashWriteOnepage( page, p_dat, length, 1 );	
			FlashWrite( page,0, p_dat, length,1);	// 写入数据
			page++;
			length = 0;
		}
	}
//	FlashWriteOnepage( page, p_dat, length, 1 );	
	FlashWrite( page,0, p_dat, length,1);	// 写入数据

	//保存4字节参数
	p_dat = sys_temp_buff;
	page = FLASH_PARAM_4B_PAGE;
	length = 0;
	p_dat[length++] = 0xEB;
	p_dat[length++] = 0x90;
	for ( i=0; i<SYS_PARAM_4B_COUNT; i++ )
	{
		val_32 = sys_param_4b[i].val;
		//低位在前
		p_dat[length++] = (UCHAR8)(val_32&0x000000FF);
		p_dat[length++] = (UCHAR8)((val_32>>8)&0x000000FF);
		p_dat[length++] = (UCHAR8)((val_32>>16)&0x000000FF);
		p_dat[length++] = (UCHAR8)((val_32>>24)&0x000000FF);
		// 若数据满1页则先存储
		if ( length > FLASH_PAGE_SIZE-4 )
		{
//			FlashWriteOnepage( page, p_dat, length, 1 );
			FlashWrite( page,0, p_dat, length,1);	// 写入数据
			page++;
			length = 0;
		}
	}
//	FlashWriteOnepage( page, p_dat, length, 1 );
	FlashWrite( page,0, p_dat, length,1);	// 写入数据

	//保存字符串参数
	//TRACE_INFO_WP(".");
	p_dat = sys_temp_buff;
	page = FLASH_PARAM_ASC_PAGE;
	length = 0;
	p_dat[length++] = 0xEB;
	p_dat[length++] = 0x90;
	for ( i=0; i<SYS_PARAM_ASC_COUNT; i++ )
	{
		p_dat[length++] = sys_param_asc[i].length;
		// 若数据满1页则先存储
		if ( length > FLASH_PAGE_SIZE-1 )
		{
//			FlashWriteOnepage( page, p_dat, length, 1 );	
			FlashWrite( page,0, p_dat, length,1);	// 写入数据
			page++;
			length = 0;
		}
		
		for ( j=0; j<sys_param_asc[i].length; j++ )
		{
			p_dat[length++] = sys_param_asc[i].p_asc[j];
			// 若数据满1页则先存储
			if ( length > FLASH_PAGE_SIZE-1 )
			{
//				FlashWriteOnepage( page, p_dat, length, 1 );	
				FlashWrite( page,0, p_dat, length,1);	// 写入数据
				page++;
				length = 0;
			}
		}
	}
//	FlashWriteOnepage( page, p_dat, length, 1 );
	FlashWrite( page,0, p_dat, length,1);	// 写入数据

	//TRACE_INFO_WP("!\r\n");
	WTD_CLR;
 
}

/*************************************************************
Name:ParamResetDefault
Description: 上电后读取参数前初始化默认参数
Input:void      
Output:void         
Return:void
**************************************************************/
void ParamResetDefault()
{
	version_number = VERSION_NUMBER;
#ifdef GSM_TYPE_UNICOM
	G2Tpye = G2_TYPE_UNICOM;
#elif defined(GSM_TYPE_CNMOBILE)
	G2Tpye = G2_TYPE_CNMOBILE;
#elif defined(GSM_TYPE_TELECOM) 
	G2Tpye = G2_TYPE_TELECOM;
#endif

#if defined CLIENT_JIZHUN
		sys_param_2b[MADD_MOVE_CENTER_FRE_D].val = 36350;
		sys_param_2b[MADD_MOVE_CENTER_FRE_U].val = 35350;
	
#endif

	//A段上，行 使能开关打开
	sys_param_1b[MADD_A_DL_WORK_EN].val = 1;
	sys_param_1b[MADD_A_UL_WORK_EN].val = 1; 
	
    //根据不同制式设置默认频点	
#if (A_NETWORK_TYPE==NET_TYPE_GSM900)			// GSM
	#if (B_NETWORK_TYPE==NET_TYPE_WCDMA2100)
	sys_param_2b[MADD_A_DL_CHANNEL1].val = 110;
	#else
	sys_param_2b[MADD_A_DL_CHANNEL1].val = 45;
	#endif
#elif (A_NETWORK_TYPE==NET_TYPE_WCDMA2100)	// WCDMA
	sys_param_2b[MADD_A_DL_CHANNEL1].val = 10688;
#elif (A_NETWORK_TYPE==NET_TYPE_DCS1800)		// DCS1800
	sys_param_2b[MADD_A_DL_CHANNEL1].val = 699;
#elif (A_NETWORK_TYPE==NET_TYPE_TD)				// TD
	sys_param_2b[MADD_A_DL_CHANNEL1].val = 10096;
#endif

     //上 、下行的频点 配成一致
	sys_param_2b[MADD_A_UL_CHANNEL1].val = sys_param_2b[MADD_A_DL_CHANNEL1].val;



////////////////////////////////////////////////////////B段//////////////////////////////////////////////////////////////////////////
    //B段上，行 使能开关打开
	sys_param_1b[MADD_B_DL_WORK_EN].val = 1;
	sys_param_1b[MADD_B_UL_WORK_EN].val = 1;
	
	//根据不同制式设置默认频点
#if (B_NETWORK_TYPE==NET_TYPE_GSM900)			// GSM
	sys_param_2b[MADD_B_DL_CHANNEL1].val = 35;
#elif (B_NETWORK_TYPE==NET_TYPE_WCDMA2100)	// WCDMA
	sys_param_2b[MADD_B_DL_CHANNEL1].val = 10688;
#elif (B_NETWORK_TYPE==NET_TYPE_DCS1800)		// DCS1800
	sys_param_2b[MADD_B_DL_CHANNEL1].val = 699;
#elif (B_NETWORK_TYPE==NET_TYPE_TD)				// TD
	sys_param_2b[MADD_B_DL_CHANNEL1].val = 10090;
#elif (B_NETWORK_TYPE==NET_DIVE)				// 分集,设置和A段一样 
	sys_param_2b[MADD_B_DL_CHANNEL1].val = sys_param_2b[MADD_A_DL_CHANNEL1].val;
#endif

     //上 、下行的频点 配成一致
	sys_param_2b[MADD_B_UL_CHANNEL1].val = sys_param_2b[MADD_B_DL_CHANNEL1].val;

    //频点搜索功能设置
#if ( A_NETWORK_TYPE==NET_TYPE_GSM900 ) 
	sys_param_1b[MADD_FPS_RFRANGE_SEL].val= 1;	// 频点搜索: 频宽选择(忽略,以模块制式为准): 0-全频段, 1-900MHz, 2-1800MHz
#elif ( A_NETWORK_TYPE==NET_TYPE_DCS1800 )
	sys_param_1b[MADD_FPS_RFRANGE_SEL].val= 2;	// 频点搜索: 频宽选择(忽略,以模块制式为准): 0-全频段, 1-900MHz, 2-1800MHz
#endif

////////////////////////////////////////////////////////C段//////////////////////////////////////////////////////////////////////////
    //C段上，行 使能开关打开
	sys_param_1b[MADD_C_DL_WORK_EN].val = 1;
	sys_param_1b[MADD_C_UL_WORK_EN].val = 1;

////////////////////////////////////////////////////////D段//////////////////////////////////////////////////////////////////////////
    //D段上，行 使能开关打开
	sys_param_1b[MADD_D_DL_WORK_EN].val = 1;
	sys_param_1b[MADD_D_UL_WORK_EN].val = 1;
#ifdef FPGA_ACDU_16M_FLASH	
	flash_parr2=1;
#else
	flash_parr2=0;
#endif

}



/*************************************************************
Name:ParamPreInit          
Description: 读取参数后重新初始化部分参数
Input:void      
Output:void         
Return:void
**************************************************************/
void ParamPreInit()
{
	UINT16 i;
	CHAR8 tmp;
	UCHAR8 mcu_ver_c[40] ="CEDTMAU_MCU_V001F001R_201709011455";
	UCHAR8 mcu_ver_g[40] ="GEDTMAU_MCU_V001F001R_201709081511";
	UCHAR8 mcu_ver_w[40] ="WEDTMAU_MCU_V001F001R_201709222019";

	//程序版本
	#if defined CLIENT_ERRICSON
	memcpy(str_pri_mcu_version_new,mcu_ver_g,sizeof(mcu_ver_g));
	#elif defined CLIENT_ERRICSON2
	memcpy(str_pri_mcu_version_new,mcu_ver_c,sizeof(mcu_ver_c));
	#elif defined CLIENT_ERRICSON_W
	memcpy(str_pri_mcu_version_new,mcu_ver_w,sizeof(mcu_ver_w));
	#endif

	//告警清零
	sys_param_1b[MADD_WORK_ERROR].val = 0;
	sys_param_1b[MADD_BATTERY_BREAKDOWN_ALARM].val = 0;
	sys_param_1b[MADD_LOW_POWER_ALARM].val = 0;
	sys_param_1b[MADD_HOST_DEVICE_LINK_SINGNAL_ALARM].val = 0;
	sys_param_eu_1b[MADD_EU_ALARM_FLAG1].val = 0;
	sys_param_eu_1b[MADD_EU_ALARM_FLAG2].val = 0;
	sys_param_eu_1b[MADD_EU_ALARM_FLAG3].val = 0;
	sys_param_eu_1b[MADD_EU_ALARM_FLAG4].val = 0;
	sys_param_eu_1b[MADD_EU_ALARM_FLAG5].val = 0;
	sys_param_eu_1b[MADD_EU_ALARM_FLAG6].val = 0;
	sys_param_eu_1b[MADD_EU_ALARM_FLAG7].val = 0;
	sys_param_eu_1b[MADD_EU_ALARM_FLAG8].val = 0;
	
	sys_param_eu_2b[MADD_EU_RUALARM_FLAG1].val = 0;
	sys_param_eu_2b[MADD_EU_RUALARM_FLAG2].val = 0;
	sys_param_eu_2b[MADD_EU_RUALARM_FLAG3].val = 0;
	sys_param_eu_2b[MADD_EU_RUALARM_FLAG4].val = 0;
	sys_param_eu_2b[MADD_EU_RUALARM_FLAG5].val = 0;
	sys_param_eu_2b[MADD_EU_RUALARM_FLAG6].val = 0;
	sys_param_eu_2b[MADD_EU_RUALARM_FLAG7].val = 0;
	sys_param_eu_2b[MADD_EU_RUALARM_FLAG8].val = 0;

	memset( (UCHAR8*)topo_alarm, 0, sizeof(topo_alarm) );
	//topo_alarm[src_fp-1][src_re-1].meu_alarm
	// 正常模式工作
	sys_param_1b[MADD_LOW_POWER].val = 0;	
	// 上电后，将数字版上电状态置1
	sys_param_1b[MADD_POWERUP_ST].val = 1;

	// TD工作模式 为正常模式
	sys_param_1b[MADD_TD_WORK_MODE].val = 0;
	sys_param_1b[MADD_C_TD_WORK_MODE].val = 0;
	sys_param_1b[MADD_D_TD_WORK_MODE].val = 0;


#if (A_NETWORK_TYPE==NET_NONE)
	// 该段不存在，关闭工作使能
	sys_param_1b[MADD_A_DL_WORK_EN].val = 0;
	sys_param_1b[MADD_A_UL_WORK_EN].val = 0;
#endif

#if (B_NETWORK_TYPE==NET_NONE)
	// 该段不存在，关闭工作使能
	sys_param_1b[MADD_B_DL_WORK_EN].val = 0;
	sys_param_1b[MADD_B_UL_WORK_EN].val = 0;
#endif

#if (C_NETWORK_TYPE==NET_NONE)
	// 该段不存在，关闭工作使能
	sys_param_1b[MADD_C_DL_WORK_EN].val = 0;
	sys_param_1b[MADD_C_UL_WORK_EN].val = 0;
#endif

#if (D_NETWORK_TYPE==NET_NONE)
	// 该段不存在，关闭工作使能
	sys_param_1b[MADD_D_DL_WORK_EN].val = 0;
	sys_param_1b[MADD_D_UL_WORK_EN].val = 0;
#endif

	if ( sys_param_2b[MADD_A_UDPX_IN_GAIN].val == 0xFFFF )
	{
		sys_param_2b[MADD_A_UDPX_IN_GAIN].val = 0;
	}

	if ( sys_param_2b[MADD_A_UDPX_OUT_GAIN].val == 0xFFFF )
	{
		sys_param_2b[MADD_A_UDPX_OUT_GAIN].val = 0;
	}

	if ( sys_param_2b[MADD_B_UDPX_IN_GAIN].val == 0xFFFF )
	{
		sys_param_2b[MADD_B_UDPX_IN_GAIN].val = 0;
	}

	if ( sys_param_2b[MADD_B_UDPX_OUT_GAIN].val == 0xFFFF )
	{
		sys_param_2b[MADD_B_UDPX_OUT_GAIN].val = 0;
	}
	if ( sys_param_2b[MADD_C_UDPX_IN_GAIN].val == 0xFFFF )
	{
		sys_param_2b[MADD_C_UDPX_IN_GAIN].val = 0;
	}

	if ( sys_param_2b[MADD_C_UDPX_OUT_GAIN].val == 0xFFFF )
	{
		sys_param_2b[MADD_C_UDPX_OUT_GAIN].val = 0;
	}

	if ( sys_param_2b[MADD_D_UDPX_IN_GAIN].val == 0xFFFF )
	{
		sys_param_2b[MADD_D_UDPX_IN_GAIN].val = 0;
	}

	if ( sys_param_2b[MADD_D_UDPX_OUT_GAIN].val == 0xFFFF )
	{
		sys_param_2b[MADD_D_UDPX_OUT_GAIN].val = 0;
	}
	

#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能

	if ( (sys_param_1b[MADD_FPS_MOSVC_SEL].val>2)&&(128!=sys_param_1b[MADD_FPS_MOSVC_SEL].val ))	// 搜索范围不是移动联通也不是手动搜索
	{
		sys_param_1b[MADD_FPS_MOSVC_SEL].val = 0;		// 设置默认搜索范围为移动
	}

#else	// 不启用频点搜索功能，屏蔽相关参数

	sys_param_1b[MADD_FPS_MOSVC_SEL].type = PT_NC;	// 频点搜索: 运营商选择: 0-中移动, 1-中联通, 2-中移动, 128-直接手动指定, 255-自动选择
	sys_param_1b[MADD_FPS_MOSVC_SEL].val = 0;
	
	sys_param_1b[MADD_FPS_RFRANGE_SEL].type = PT_NC;	// 频点搜索: 频宽选择(忽略,以模块制式为准): 0-全频段, 1-900MHz, 2-1800MHz
	sys_param_1b[MADD_FPS_RFRANGE_SEL].val = 0;

	sys_param_1b[MADD_FPS_BS_ID].type = PT_NC;	// 频点搜索: 基站识别码
	sys_param_1b[MADD_FPS_BS_ID].val = 0;

	sys_param_1b[MADD_FPS_CA_COUNT].type = PT_NC;	// 频点搜索: 有效信道数
	sys_param_1b[MADD_FPS_CA_COUNT].val = 0;

	sys_param_1b[MADD_FPS_BCCH_LK_ST].type = PT_NC;	// 频点搜索: 锁定BCCH状态: 1-锁定, 0-失败
	sys_param_1b[MADD_FPS_BCCH_LK_ST].val = 0;

	sys_param_1b[MADD_FPS_MOSVC_LK_ST].type = PT_NC;	// 频点搜索: 锁定运营商状态: 1-锁定, 0-失败
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 0;

	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].type = PT_NC;	// 频点搜索: 锁定频带状态: 1-锁定, 0-失败
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 0;

	sys_param_1b[MADD_FPS_BCCH_POW_M].type = PT_NC;	// 频点搜索: 主小区BCCH接收强度
	sys_param_1b[MADD_FPS_BCCH_POW_M].val = 0;
	
	for ( i=MADD_FPS_BCCH_POW_1; i<=MADD_FPS_BCCH_POW_6; i++ )
	{
		sys_param_1b[i].type = PT_NC;	// 频点搜索: 邻小区BCCH接收强度
		sys_param_1b[i].val = 0;
	}
	
	sys_param_2b[MADD_FPS_BCCH_LK_SET].type = PT_NC;	// 频点搜索: 锁频信道号: 标准信道号, 65535-退出锁频
	sys_param_2b[MADD_FPS_BCCH_LK_SET].val = 65535;

	sys_param_2b[MADD_FPS_CID_LK_SET].type = PT_NC;	// 频点搜索: 小区识别码参考值, 0-退出小区锁定功能
	sys_param_2b[MADD_FPS_CID_LK_SET].val = 0;

	sys_param_2b[MADD_FPS_BCCH_FC_M].type = PT_NC;	// 频点搜索: 主小区BCCH信道号, 标准信道号, 65535-无BCCH
	sys_param_2b[MADD_FPS_BCCH_FC_M].val = 65535;

	for ( i=MADD_FPS_CA_FC_0; i<=MADD_FPS_CA_FC_15; i++ )
	{
		sys_param_2b[i].type = PT_NC;	// 频点搜索: CA载波信道号, 标准信道号, 65535-无CA
		sys_param_2b[i].val = 65535;
	}

	for ( i=MADD_FPS_BCCH_FC_1; i<=MADD_FPS_BCCH_FC_6; i++ )
	{
		sys_param_2b[i].type = PT_NC;	// 频点搜索: 邻小区BCCH信道号, 标准信道号, 65535-无BCCH
		sys_param_2b[i].val = 65535;
	}

	for ( i=MADD_FPS_CID_1; i<=MADD_FPS_CID_6; i++ )
	{
		sys_param_2b[i].type = PT_NC;	// 频点搜索: 邻小区BCCH 的CID, 0-无CID
		sys_param_2b[i].val = 0;
	}
	
	sys_param_2b[MADD_FPS_AREA_ID].type = PT_NC;	// 频点搜索: 位置区编码
	sys_param_2b[MADD_FPS_AREA_ID].val = 0;

	sys_param_2b[MADD_FPS_CID].type = PT_NC;	// 频点搜索: 小区识别码实时值
	sys_param_2b[MADD_FPS_CID].val = 0;
	
#endif

#if 0
	// 检查前一版本MCU水印是否是2010年11月2日前的
	tmp = CheckStrDate( str_pri_mcu_date+9, 2, 11, 2010 );		// 水印格式[rec_XX_x_MMM_DD_YYYY]
	if ( tmp<0 )		// 是则根据用户默认参数设置串口
	{
		sys_param_1b[MADD_CTRL_BAUD].val = PARAM_INIT_CTRL_BAUD;
		sys_param_1b[MADD_THR_BAUD].val  = PARAM_INIT_THR_BAUD;
		sys_param_1b[MADD_THR_PORT].val  = PARAM_INIT_THR_PORT;
	}  
#endif

   //根据第一个通道的频点来判断是联通还是移动 
   #if ((A_NETWORK_TYPE == NET_TYPE_GSM900)||(B_NETWORK_TYPE == NET_TYPE_GSM900))
   {
           if ((sys_param_2b[MADD_A_DL_CHANNEL1].val>=96)&&(sys_param_2b[MADD_A_DL_CHANNEL1].val<=124))
           {
              // G2Tpye = G2_TYPE_UNICOM; 
               
           }
           else
           if (  (sys_param_2b[MADD_A_DL_CHANNEL1].val>=1)&&(sys_param_2b[MADD_A_DL_CHANNEL1].val<=95)
               ||(sys_param_2b[MADD_A_DL_CHANNEL1].val>=999)&&(sys_param_2b[MADD_A_DL_CHANNEL1].val<=1023)
               )
           {
               // G2Tpye = G2_TYPE_CNMOBILE;   
           } 
           
           //module_param_chg_flag|=PCHG_A_FL_CHG;
          // module_param_chg_flag|=PCHG_B_FL_CHG;
           //module_param_chg_flag|=PCHG_C_FL_CHG;
          // module_param_chg_flag|=PCHG_D_FL_CHG;		   
           
   }
   #elif ((A_NETWORK_TYPE == NET_TYPE_DCS1800)||(B_NETWORK_TYPE == NET_TYPE_DCS1800))
   {
           if ((sys_param_2b[MADD_A_DL_CHANNEL1].val>=DCS_MIN_FRE_CODE_UNICOM)&&(sys_param_2b[MADD_A_DL_CHANNEL1].val<=DCS_MAX_FRE_CODE_UNICOM))
           {
              // G2Tpye = G2_TYPE_UNICOM; 
           }
           else
           if ((sys_param_2b[MADD_A_DL_CHANNEL1].val>=DCS_MIN_FRE_CODE_CNMOBILE)&&(sys_param_2b[MADD_A_DL_CHANNEL1].val<=DCS_MAX_FRE_CODE_CNMOBILE))
           { 
             //  G2Tpye = G2_TYPE_CNMOBILE; 
           }  
          // module_param_chg_flag|=PCHG_A_FL_CHG;
           //module_param_chg_flag|=PCHG_B_FL_CHG; 
           //module_param_chg_flag|=PCHG_C_FL_CHG;
          //module_param_chg_flag|=PCHG_D_FL_CHG;  		   
   }
   #endif

	sys_param_1b[MADD_METER_OFFSET].val=0;
	sys_param_1b[MADD_METER_OFFSET_B].val=0;
	sys_param_1b[MADD_METER_OFFSET_C].val=0;
	sys_param_1b[MADD_METER_OFFSET_D].val=0;  
	sys_param_1b[MADD_A_DL_RF_EN].val = 0;
	sys_param_1b[MADD_A_UL_RF_EN].val = 0;
	sys_param_1b[MADD_B_DL_RF_EN].val = 0;
	sys_param_1b[MADD_B_UL_RF_EN].val = 0;	
	sys_param_1b[MADD_C_DL_RF_EN].val = 0;
	sys_param_1b[MADD_C_UL_RF_EN].val = 0;
	sys_param_1b[MADD_D_DL_RF_EN].val = 0;
	sys_param_1b[MADD_D_UL_RF_EN].val = 0;	
	sys_param_1b[MADD_PASSTHROUGH_EN].val = 0;

}

void InitUserInterface()
{
	UINT16 i;
	UCHAR8 tmp;
	
// 根据客户标识重新配置特殊的参数地址 
#ifdef GUORENSOFT 
	sys_param_1b[MADD_TRAFFIC_END].addr = 0x08c6;	// 话务量统计状态参数地址(国人)
	sys_param_1b[MADD_LOW_POWER].addr   = 0x0778;	// 低功耗模式参数地址(国人)
	
	// A段
#if ( A_NETWORK_TYPE==NET_NONE )	// 无
	sys_param_1b[MADD_A_DL_POW_1B].type    = PT_RO|PT_SI;
	sys_param_1b[MADD_A_UL_POW_1B].type    = PT_RO|PT_SI;
	sys_param_2b[MADD_A_DL_TOTAL_POW].type = PT_RO|PT_SI;	
	sys_param_2b[MADD_A_UL_TOTAL_POW].type = PT_RO|PT_SI;	
#elif (( A_NETWORK_TYPE==NET_TYPE_GSM900)||( A_NETWORK_TYPE==NET_TYPE_DCS1800))	// A段为GSM, 2G版本功率采用1字节
	sys_param_1b[MADD_A_DL_POW_1B].type = PT_AP|PT_RO|PT_SI;
	sys_param_1b[MADD_A_UL_POW_1B].type = PT_AP|PT_RO|PT_SI;
	sys_param_2b[MADD_A_DL_TOTAL_POW].type = PT_RO|PT_SI;
	sys_param_2b[MADD_A_UL_TOTAL_POW].type = PT_RO|PT_SI;	
#else	// 其他, 3G版本功率采用2字节，x10算法保留一位小数
	sys_param_1b[MADD_A_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_A_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_A_DL_TOTAL_POW].type = PT_AP|PT_RO|PT_SI;	
	sys_param_2b[MADD_A_UL_TOTAL_POW].type = PT_AP|PT_RO|PT_SI;	
#endif

	// B段
#if ( B_NETWORK_TYPE==NET_NONE )	// 无
	sys_param_1b[MADD_B_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_B_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_B_DL_TOTAL_POW].type = PT_RO|PT_SI;	
	sys_param_2b[MADD_B_UL_TOTAL_POW].type = PT_RO|PT_SI;	
#elif ( B_NETWORK_TYPE==NET_TYPE_WCDMA2100 )	// B段为WCDMA, 3G版本功率采用2字节，x10算法保留一位小数
	sys_param_1b[MADD_B_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_B_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_B_DL_TOTAL_POW].type = PT_BP|PT_RO|PT_SI;	
	sys_param_2b[MADD_B_UL_TOTAL_POW].type = PT_BP|PT_RO|PT_SI;	
#elif ( B_NETWORK_TYPE==NET_TYPE_TD )	// B段为TD, 3G版本功率采用2字节，x10算法保留一位小数
	sys_param_1b[MADD_B_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_B_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_B_DL_TOTAL_POW].type = PT_BP|PT_RO|PT_SI;	
	sys_param_2b[MADD_B_UL_TOTAL_POW].type = PT_BP|PT_RO|PT_SI;	
#elif ( B_NETWORK_TYPE==NET_DIVE )		// B段为分集
	#if (( A_NETWORK_TYPE==NET_TYPE_GSM900)||( A_NETWORK_TYPE==NET_TYPE_DCS1800))	// A段为GSM, 2G版本功率采用1字节
	sys_param_1b[MADD_B_DL_POW_1B].type = PT_BP|PT_RO|PT_SI;
	sys_param_1b[MADD_B_UL_POW_1B].type = PT_BP|PT_RO|PT_SI;
	sys_param_2b[MADD_B_DL_TOTAL_POW].type = PT_RO|PT_SI;	
	sys_param_2b[MADD_B_UL_TOTAL_POW].type = PT_RO|PT_SI;	
	#else	// 其他, 3G版本, 功率采用2字节，x10算法保留一位小数
	sys_param_1b[MADD_B_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_B_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_B_DL_TOTAL_POW].type = PT_BP|PT_RO|PT_SI;	
	sys_param_2b[MADD_B_UL_TOTAL_POW].type = PT_BP|PT_RO|PT_SI;	
	#endif
#else	// 其他, 3G版本, 功率采用2字节，x10算法保留一位小数
	sys_param_1b[MADD_B_DL_POW_1B].type    = PT_RO|PT_SI;
	sys_param_1b[MADD_B_UL_POW_1B].type    = PT_RO|PT_SI;
	sys_param_2b[MADD_B_DL_TOTAL_POW].type = PT_BP|PT_RO|PT_SI;	
	sys_param_2b[MADD_B_UL_TOTAL_POW].type = PT_BP|PT_RO|PT_SI;	
#endif
// C段
#if (C_NETWORK_TYPE==NET_NONE )	// 无
	sys_param_1b[MADD_C_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_C_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_C_DL_TOTAL_POW].type = PT_RO|PT_SI;	
	sys_param_2b[MADD_C_UL_TOTAL_POW].type = PT_RO|PT_SI;	
#elif( ( C_NETWORK_TYPE==NET_TYPE_LTE_TD)	|| ( C_NETWORK_TYPE==NET_TYPE_LTE_FDD))// D段为WCDMA, 3G版本功率采用2字节，x10算法保留一位小数
	sys_param_1b[MADD_C_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_C_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_C_DL_TOTAL_POW].type = PT_CP|PT_RO|PT_SI;	
	sys_param_2b[MADD_C_UL_TOTAL_POW].type = PT_CP|PT_RO|PT_SI;	
#endif
	// D段
#if (D_NETWORK_TYPE==NET_NONE )	// 无
	sys_param_1b[MADD_D_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_D_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_D_DL_TOTAL_POW].type = PT_RO|PT_SI;	
	sys_param_2b[MADD_D_UL_TOTAL_POW].type = PT_RO|PT_SI;	
#elif (( D_NETWORK_TYPE==NET_TYPE_LTE_TD )|| ( D_NETWORK_TYPE==NET_TYPE_LTE_FDD))	// D段为WCDMA, 3G版本功率采用2字节，x10算法保留一位小数
	sys_param_1b[MADD_D_DL_POW_1B].type = PT_RO|PT_SI;
	sys_param_1b[MADD_D_UL_POW_1B].type = PT_RO|PT_SI;
	sys_param_2b[MADD_D_DL_TOTAL_POW].type = PT_DP|PT_RO|PT_SI;	
	sys_param_2b[MADD_D_UL_TOTAL_POW].type = PT_DP|PT_RO|PT_SI;	
#endif

	if ( 0==fpga_cfg.wlan_en )			// 122.88M时钟,非WLAN模式，不读取WLAN口信息
	{
		sys_param_1b[MADD_WLAN_CONN_ST1].type = PT_RO|PT_US;
		sys_param_1b[MADD_WLAN_CONN_ST2].type = PT_RO|PT_US;
		sys_param_1b[MADD_WLAN_CONN_ST3].type = PT_RO|PT_US;
		sys_param_1b[MADD_WLAN_CONN_ST4].type = PT_RO|PT_US;
		sys_param_1b[MADD_WLAN_SPEED1].type = PT_RO|PT_US;
		sys_param_1b[MADD_WLAN_SPEED2].type = PT_RO|PT_US;
		sys_param_1b[MADD_WLAN_SPEED3].type = PT_RO|PT_US;
		sys_param_1b[MADD_WLAN_SPEED4].type = PT_RO|PT_US;
	}
	
#else
	sys_param_1b[MADD_TRAFFIC_END].addr = 0x88ac;	// 话务量统计状态参数地址(其他客户)
	sys_param_1b[MADD_LOW_POWER].addr   = 0x08ad;	// 低功耗模式参数地址(其他客户)
#endif



	// A段通道
	tmp = sys_param_1b[MADD_A_CHANNEL_COUNT].val;

#if 1
	for ( i=tmp; i<MAX_CHANNEL_COUNT; i++ )
	{
		sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
		sys_param_1b[MADD_A_DCH_EN1+i].type = PT_NC;
		sys_param_1b[MADD_A_UCH_EN1+i].type = PT_NC;
		sys_param_1b[MADD_A_DCH_GAIN1+i].type = PT_NC;
		sys_param_1b[MADD_A_UCH_GAIN1+i].type = PT_NC;
		sys_param_2b[MADD_A_DL_CHANNEL1+i].type = PT_NC;
		sys_param_2b[MADD_A_UL_CHANNEL1+i].type = PT_NC;
	}
#endif 
	// B段通道
	tmp = sys_param_1b[MADD_B_CHANNEL_COUNT].val;

#if 1
	for ( i=tmp; i<MAX_CHANNEL_COUNT; i++ )
	{
		sys_param_1b[MADD_B_DCH_EN1+i].val = 0;
		sys_param_1b[MADD_B_DCH_EN1+i].type = PT_NC;
		sys_param_1b[MADD_B_UCH_EN1+i].type = PT_NC;
		sys_param_1b[MADD_B_DCH_GAIN1+i].type = PT_NC;
		sys_param_1b[MADD_B_UCH_GAIN1+i].type = PT_NC;
		sys_param_2b[MADD_B_DL_CHANNEL1+i].type = PT_NC;
		sys_param_2b[MADD_B_UL_CHANNEL1+i].type = PT_NC;
	}
#endif

	// C段通道
	tmp = sys_param_1b[MADD_C_CHANNEL_COUNT].val;

	for ( i=tmp; i<MAX_CHANNEL_COUNT-6; i++ )
	{
#if 1	
        sys_param_1b[MADD_C_DCH_EN1+i].val = 0;
		sys_param_1b[MADD_C_DCH_EN1+i].type = PT_NC;
		sys_param_1b[MADD_C_UCH_EN1+i].type = PT_NC;		
		//sys_param_1b[MADD_C_DCH_GAIN1+i].type = PT_NC;
		//sys_param_1b[MADD_C_UCH_GAIN1+i].type = PT_NC;
		sys_param_2b[MADD_C_DL_CHANNEL1+i].type = PT_NC;
		sys_param_2b[MADD_C_UL_CHANNEL1+i].type = PT_NC;
		sys_param_1b[MADD_C_DCH_EN1+i].val= 0;
		sys_param_1b[MADD_C_UCH_EN1+i].val= 0;			
#endif 
	}

	// D段通道
	tmp = sys_param_1b[MADD_D_CHANNEL_COUNT].val;

	for ( i=tmp; i<MAX_CHANNEL_COUNT-6; i++ )
	{
#if 1
		sys_param_1b[MADD_D_DCH_EN1+i].val = 0;
		sys_param_1b[MADD_D_DCH_EN1+i].type = PT_NC;
		sys_param_1b[MADD_D_UCH_EN1+i].type = PT_NC;

		//sys_param_1b[MADD_D_DCH_GAIN1+i].type = PT_NC;
		//sys_param_1b[MADD_D_UCH_GAIN1+i].type = PT_NC;
		sys_param_2b[MADD_D_DL_CHANNEL1+i].type = PT_NC;
		sys_param_2b[MADD_D_UL_CHANNEL1+i].type = PT_NC;
		sys_param_1b[MADD_D_DCH_EN1+i].val= 0;
		sys_param_1b[MADD_D_UCH_EN1+i].val= 0;			
#endif 
	}

	sys_param_1b[MADD_C_PRI_ADD].val &= 0x77;
	sys_param_1b[MADD_D_PRI_ADD].val &= 0x77;// 地址A段和B段不能相等，也不能超过8


	sys_param_1b[MADD_MONITOR_VOL_OVER_THR].val=140;
	sys_param_1b[MADD_MONITOR_VOL_OWE_THR].val=80;
	mo_param_count_a = GetMoParamCount(SYS_A_FLAG);
    //TRACE_INFO("mo_param_count_a = %d\r\n",mo_param_count_a);
	
	mo_param_count_b = GetMoParamCount(SYS_B_FLAG);
	//TRACE_INFO("mo_param_count_b = %d\r\n",mo_param_count_b);

	mo_param_count_c = GetMoParamCount(SYS_C_FLAG);
	//TRACE_INFO("mo_param_count_b = %d\r\n",mo_param_count_b);

	mo_param_count_d = GetMoParamCount(SYS_D_FLAG);
	//TRACE_INFO("mo_param_count_b = %d\r\n",mo_param_count_b);	
	if (0)//(B_NETWORK_TYPE==NET_TYPE_TD)
	{// td_scdma搜索通道号，第1通道为界面设置的频点，接下来九个频点为固定为；10055、10063、10071、10080、10088、10096、10104、10112、10120
		sys_param_2b[MADD_B_DL_CHANNEL2].val=10055;
		sys_param_2b[MADD_B_DL_CHANNEL3].val=10063;
		sys_param_2b[MADD_B_DL_CHANNEL4].val=10071;
		sys_param_2b[MADD_B_DL_CHANNEL5].val=10080;
		sys_param_2b[MADD_B_DL_CHANNEL6].val=10088;
		sys_param_2b[MADD_B_DL_CHANNEL7].val=10096;
		sys_param_2b[MADD_B_DL_CHANNEL8].val=10104;
		sys_param_2b[MADD_B_DL_CHANNEL9].val=10112;
		sys_param_2b[MADD_B_DL_CHANNEL10].val=10120;				
	}
	sys_param_1b[MADD_A_PRI_ADD].val = 0x01;
	sys_param_1b[MADD_B_PRI_ADD].val = 0x02;// 地址A段和B段不能相等，也不能超过8
	sys_param_1b[MADD_C_PRI_ADD].val = 0x03;
	sys_param_1b[MADD_D_PRI_ADD].val = 0x04;// 地址A段和B段不能相等，也不能超过8


	
	sys_param_1b[MADD_SoftwareLoadTimes ].val += 1 ;   //软件上电加载 ，每次上电加一

	SaveSysParamToFlash(); 
	
	
} 

/*************************************************************
Name:ParamAddTranslate          
Description: 将参数的访问地址转换成内部存储地址
Input:
	len: 参数长度
	param_add: 参数地址
	p_mo_addr: 指向保存内部存储地址的变量的指针
Output:
	*p_mo_addr: 参数的内部存储地址
Return: 
	1 - 地址正确
	0 - 地址错误
**************************************************************/
BOOL ParamAddTranslate( UCHAR8 len,  UINT16 param_addr, UCHAR8 ex_mask, UINT16* p_mo_addr )
{
	UINT32 i;
	UCHAR8 mask;

	TRACE_INFO("len=%d, padd=%04X, mask=%02X, \r\n", len, param_addr, ex_mask);
	if ( 1==len )
	{
		for ( i=0; i<SYS_PARAM_1B_COUNT; i++ )
		{
			if (( sys_param_1b[i].addr == param_addr )&&( ex_mask ==(sys_param_1b[i].type&ex_mask) ))
			{
				*p_mo_addr = i;

				TRACE_INFO(" sys_param_1b_i[%d]\r\n",i)
				
				return b_TRUE;
			}
		}

	}

	if ( 2==len )
	{
		for ( i=0; i<SYS_PARAM_2B_COUNT; i++ )
		{
			if ((sys_param_2b[i].addr == param_addr )&&( ex_mask ==(sys_param_2b[i].type&ex_mask) ))
			{
				*p_mo_addr = i;
				TRACE_INFO(" sys_param_2b_i[%d]\r\n",i)				
				return b_TRUE;
			}
		
		}
		
	}

	if ( 4==len )
	{
		for ( i=0; i<SYS_PARAM_4B_COUNT; i++ )
		{
			if ((sys_param_4b[i].addr == param_addr )&&( ex_mask ==(sys_param_4b[i].type&ex_mask) ))
			{
				*p_mo_addr = i;
				TRACE_INFO(" sys_param_4b_i[%d]\r\n",i)				
				return b_TRUE;
			}
		}
	}

	for ( i=0; i<SYS_PARAM_ASC_COUNT; i++ )
	{
		if ((sys_param_asc[i].addr == param_addr )&&( ex_mask ==(sys_param_asc[i].type&ex_mask) ))
		{
			*p_mo_addr = i;
			TRACE_INFO(" sys_param_asc_i[%d]\r\n",i)		
			return b_TRUE;
		}
	}

	return b_FALSE;
}

/*************************************************************
Name:AutoSetParam1b         
Description: 当改变参数时，自动设置相关参数
Input: 
	mo_addr: 参数的数组地址
Return: void
**************************************************************/
void AutoSetParam1b( UINT16 mo_addr )
{
	UINT16 addr;

	if (mo_addr<SYS_PARAM_1B_COUNT)
	{
		// 修改下行使能，自动同步到上行
		if ( VAL_IN_RANGE(mo_addr, MADD_A_DCH_EN1, MADD_A_DCH_EN16) )		
		{
			addr = mo_addr - MADD_A_DCH_EN1 + MADD_A_UCH_EN1;
			sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			return;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_B_DCH_EN1, MADD_B_DCH_EN16) )		
		{
			addr = mo_addr - MADD_B_DCH_EN1 + MADD_B_UCH_EN1;
			sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			return;
		}

		// 修改上行使能，自动同步到下行
		if ( VAL_IN_RANGE(mo_addr, MADD_A_UCH_EN1, MADD_A_UCH_EN16) )		
		{
			addr = mo_addr - MADD_A_UCH_EN1 + MADD_A_DCH_EN1;
			sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			return;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_B_UCH_EN1, MADD_B_UCH_EN16) )		
		{
			addr = mo_addr - MADD_B_UCH_EN1 + MADD_B_DCH_EN1;
			sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			return;
		}

		// 设置下行通道1数控衰减量，自动设置全部通道的值
		if ( MADD_A_DCH_ATT1==mo_addr )
		{
			for ( addr=MADD_A_DCH_ATT2; addr<=MADD_A_DCH_ATT16; addr++ )
			{
				sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			}
			return;
		}

		// 设置上行通道1数控衰减量，自动设置全部通道的值
		if ( MADD_A_UCH_ATT1==mo_addr )
		{
			for ( addr=MADD_A_UCH_ATT2; addr<=MADD_A_UCH_ATT16; addr++ )
			{
				sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			}
			return;
		}
// 修改下行使能，自动同步到上行
		if ( VAL_IN_RANGE(mo_addr, MADD_C_DCH_EN1, MADD_C_DCH_EN10) )		
		{
			addr = mo_addr - MADD_C_DCH_EN1 + MADD_C_UCH_EN1;
			sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			return;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_D_DCH_EN1, MADD_D_DCH_EN10) )		
		{
			addr = mo_addr - MADD_D_DCH_EN1 + MADD_D_UCH_EN1;
			sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			return;
		}

		// 修改上行使能，自动同步到下行
		if ( VAL_IN_RANGE(mo_addr, MADD_C_UCH_EN1, MADD_C_UCH_EN10) )		
		{
			addr = mo_addr - MADD_C_UCH_EN1 + MADD_C_DCH_EN1;
			sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			return;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_D_UCH_EN1, MADD_D_UCH_EN10) )		
		{
			addr = mo_addr - MADD_D_UCH_EN1 + MADD_D_DCH_EN1;
			sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			return;
		}

		// 设置下行通道1数控衰减量，自动设置全部通道的值
		if ( MADD_C_DCH_ATT1==mo_addr )
		{
			for ( addr=MADD_C_DCH_ATT1; addr<=MADD_C_DCH_ATT16; addr++ )
			{
				sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			}
			return;
		}

		// 设置上行通道1数控衰减量，自动设置全部通道的值
		if ( MADD_C_UCH_ATT1==mo_addr )
		{
			for ( addr=MADD_C_UCH_ATT1; addr<=MADD_C_UCH_ATT16; addr++ )
			{
				sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			}
			return;
		}

		// 设置下行通道1数控衰减量，自动设置全部通道的值
		if ( MADD_D_DCH_ATT1==mo_addr )
		{
			for ( addr=MADD_D_DCH_ATT1; addr<=MADD_D_DCH_ATT16; addr++ )
			{
				sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			}
			return;
		}

		// 设置上行通道1数控衰减量，自动设置全部通道的值
		if ( MADD_D_UCH_ATT1==mo_addr )
		{
			for ( addr=MADD_D_UCH_ATT1; addr<=MADD_D_UCH_ATT16; addr++ )
			{
				sys_param_1b[addr].val = sys_param_1b[mo_addr].val;
			}
			return;
		}
		
		
	}
}

/*************************************************************
Name:AutoSetParam2b         
Description: 当改变参数时，自动设置相关参数
Input: 
	mo_addr: 参数的数组地址
Return: void
**************************************************************/
void AutoSetParam2b( UINT16 mo_addr )
{	
	UINT16 addr;

	if (mo_addr<SYS_PARAM_2B_COUNT)
	{
		// 修改下行频点，自动同步到上行
		if ( VAL_IN_RANGE(mo_addr, MADD_A_DL_CHANNEL1, MADD_A_DL_CHANNEL16) )		
		{
			addr = mo_addr - MADD_A_DL_CHANNEL1 + MADD_A_UL_CHANNEL1;
			sys_param_2b[addr].val = sys_param_2b[mo_addr].val;
			return;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_B_DL_CHANNEL1, MADD_B_DL_CHANNEL16) )		
		{
			addr = mo_addr - MADD_B_DL_CHANNEL1 + MADD_B_UL_CHANNEL1;
			sys_param_2b[addr].val = sys_param_2b[mo_addr].val;
			return;
		}

		// 修改上行频点，自动同步到下行
		if ( VAL_IN_RANGE(mo_addr, MADD_A_UL_CHANNEL1, MADD_A_UL_CHANNEL16) )		
		{
			addr = mo_addr - MADD_A_UL_CHANNEL1 + MADD_A_DL_CHANNEL1;
			sys_param_2b[addr].val = sys_param_2b[mo_addr].val;
			return;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_B_UL_CHANNEL1, MADD_B_UL_CHANNEL16) )		
		{
			addr = mo_addr - MADD_B_UL_CHANNEL1 + MADD_B_DL_CHANNEL1;
			sys_param_2b[addr].val = sys_param_2b[mo_addr].val;
			return;
		}
// 修改下行频点，自动同步到上行
		if ( VAL_IN_RANGE(mo_addr, MADD_C_DL_CHANNEL1, MADD_C_DL_CHANNEL10) )		
		{
			addr = mo_addr - MADD_C_DL_CHANNEL1 + MADD_C_UL_CHANNEL1;
			sys_param_2b[addr].val = sys_param_2b[mo_addr].val;
			return;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_D_DL_CHANNEL1, MADD_D_DL_CHANNEL10) )		
		{
			addr = mo_addr - MADD_D_DL_CHANNEL1 + MADD_D_UL_CHANNEL1;
			sys_param_2b[addr].val = sys_param_2b[mo_addr].val;
			return;
		}

		// 修改上行频点，自动同步到下行
		if ( VAL_IN_RANGE(mo_addr, MADD_C_UL_CHANNEL1, MADD_C_UL_CHANNEL10) )		
		{
			addr = mo_addr - MADD_C_UL_CHANNEL1 + MADD_C_DL_CHANNEL1;
			sys_param_2b[addr].val = sys_param_2b[mo_addr].val;
			return;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_D_UL_CHANNEL1, MADD_D_UL_CHANNEL10) )		
		{
			addr = mo_addr - MADD_D_UL_CHANNEL1 + MADD_D_DL_CHANNEL1;
			sys_param_2b[addr].val = sys_param_2b[mo_addr].val;
			return;
		}

		
	}
}

/*************************************************************
Name:AutoSetParam4b         
Description: 当改变参数时，自动设置相关参数
Input: 
	mo_addr: 参数的数组地址
Return: void
**************************************************************/
void AutoSetParam4b( UINT16 mo_addr )
{
	return;
}

/*************************************************************
Name:AutoSetDiveParam         
Description: 根据A段自动设置B段分集参数，B段不为分集，则此函数不执行任何操作
Input: void
Return: void
**************************************************************/
void AutoSetDiveParam()
{
#if ( B_NETWORK_TYPE==NET_DIVE )	// B段不为分集，则此函数不执行任何操作
	UINT16 ch;

	for ( ch=0; ch<MAX_CHANNEL_COUNT; ch++ )
	{
		// 通道使能
		sys_param_1b[MADD_B_DCH_EN1+ch].val = sys_param_1b[MADD_A_DCH_EN1+ch].val;
		sys_param_1b[MADD_B_UCH_EN1+ch].val = sys_param_1b[MADD_A_UCH_EN1+ch].val;
		// 增益
		sys_param_1b[MADD_B_DCH_GAIN1+ch].val = sys_param_1b[MADD_A_DCH_GAIN1+ch].val;
		sys_param_1b[MADD_B_UCH_GAIN1+ch].val = sys_param_1b[MADD_A_UCH_GAIN1+ch].val;

		// 频点
		sys_param_2b[MADD_B_DL_CHANNEL1+ch].val = sys_param_2b[MADD_A_DL_CHANNEL1+ch].val;
		sys_param_2b[MADD_B_UL_CHANNEL1+ch].val = sys_param_2b[MADD_A_UL_CHANNEL1+ch].val;
		// 通道功率门限
		sys_param_2b[MADD_B_DCH_MAX_POW1+ch].val = sys_param_2b[MADD_A_DCH_MAX_POW1+ch].val;
		sys_param_2b[MADD_B_UCH_MAX_POW1+ch].val = sys_param_2b[MADD_A_UCH_MAX_POW1+ch].val;
	}
	// 工作使能
	sys_param_1b[MADD_B_DL_WORK_EN].val = sys_param_1b[MADD_A_DL_WORK_EN].val;
	sys_param_1b[MADD_B_UL_WORK_EN].val = sys_param_1b[MADD_A_UL_WORK_EN].val;
	// 功率控制方式
	sys_param_1b[MADD_B_DPOW_MODE].val = sys_param_1b[MADD_A_DPOW_MODE].val;
	sys_param_1b[MADD_B_UPOW_MODE].val = sys_param_1b[MADD_A_UPOW_MODE].val;
	// 底噪抑制
	sys_param_1b[MADD_B_LTHR_EN].val = sys_param_1b[MADD_A_LTHR_EN].val;
	sys_param_1b[MADD_B_LTHR_DN].val = sys_param_1b[MADD_A_LTHR_DN].val;
	sys_param_1b[MADD_B_LTHR_UP].val = sys_param_1b[MADD_A_LTHR_UP].val;
	// 功放增益
	sys_param_1b[MADD_B_DL_PA_GAIN].val = sys_param_1b[MADD_A_DL_PA_GAIN].val;
	sys_param_1b[MADD_B_UL_PA_GAIN].val = sys_param_1b[MADD_A_UL_PA_GAIN].val;
	// 双工器增益
	sys_param_2b[MADD_B_UDPX_IN_GAIN].val=sys_param_2b[MADD_A_UDPX_IN_GAIN].val;
	sys_param_2b[MADD_B_UDPX_OUT_GAIN].val=sys_param_2b[MADD_A_UDPX_OUT_GAIN].val;

#endif
}


/*************************************************************
Name:CheckParamValid1b         
Description: 检查参数是否正确
Input: 
	param_add: 参数地址
	param_val: 参数值
Return:
	1 - 参数正确
	0 - 参数错误
**************************************************************/
UCHAR8 CheckParamValid1b( UINT16 mo_addr, UCHAR8 val )
{
	UCHAR8 i,tmp;
	if (mo_addr<SYS_PARAM_1B_COUNT)
	{
		// 信道使能
		if ( VAL_IN_RANGE( mo_addr, MADD_A_DCH_EN1, MADD_A_DCH_EN16)
			|| VAL_IN_RANGE( mo_addr, MADD_A_UCH_EN1, MADD_A_UCH_EN16) )
		{
			if ( val >1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_A_CHANNEL;
				return 1;
			}
		}

		if ( VAL_IN_RANGE( mo_addr, MADD_B_DCH_EN1, MADD_B_DCH_EN16)
			|| VAL_IN_RANGE( mo_addr, MADD_B_UCH_EN1, MADD_B_UCH_EN16) )
		{
			if ( val >1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_B_CHANNEL;
				if(FPGA_B_NT_TD==fpga_cfg.b_net_type)
				{
					tds_dl_channel[0]=sys_param_2b[MADD_B_DL_CHANNEL1].val;
				}
				return 1;
			}
		}

		if ( VAL_IN_RANGE( mo_addr, MADD_C_DCH_EN1, MADD_C_DCH_EN10)
			|| VAL_IN_RANGE( mo_addr, MADD_C_UCH_EN1, MADD_C_UCH_EN10) )
		{
			if ( val >1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_C_CHANNEL;
				return 1;
			}
		}

		if ( VAL_IN_RANGE( mo_addr, MADD_D_DCH_EN1, MADD_D_DCH_EN10)
			|| VAL_IN_RANGE( mo_addr, MADD_D_UCH_EN1, MADD_D_UCH_EN10) )
		{
			if ( val >1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_D_CHANNEL;
				return 1;
			}
		}		
		
		// 底噪抑制
		if ((mo_addr==MADD_A_LTHR_EN)||(mo_addr==MADD_A_LTHR_UP)||(mo_addr==MADD_A_LTHR_DN))
		{
			module_param_chg_flag |= PCHG_A_LTHR;
			return 1;
		}

		if ((mo_addr==MADD_B_LTHR_EN)||(mo_addr==MADD_B_LTHR_UP)||(mo_addr==MADD_B_LTHR_DN))
		{
			module_param_chg_flag |= PCHG_B_LTHR;
			return 1;
		}

		// 下行整机增益
		if ( VAL_IN_RANGE(mo_addr, MADD_A_DCH_GAIN1, MADD_A_DCH_GAIN16) )
		{
			if ( VAL_IN_RANGE(val, 0, 60 ) )	// 下行增益0~40db
			{
				module_param_chg_flag |= PCHG_A_POW_GAIN;
				return 1;
			}
			else
			{
				return 0;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_B_DCH_GAIN1, MADD_B_DCH_GAIN16) )
		{
			if ( VAL_IN_RANGE(val, 0, 60 ) )	// 下行增益0~40db
			{
				module_param_chg_flag |= PCHG_B_POW_GAIN;
				return 1;
			}
			else
			{
				return 0;
			}
		}
		// 下行整机增益
		if ( VAL_IN_RANGE(mo_addr, MADD_C_DCH_GAIN1, MADD_C_DCH_GAIN10) )
		{
			if ( VAL_IN_RANGE(val, 0, 60 ) )	// 下行增益0~40db
			{
				module_param_chg_flag |= PCHG_C_POW_GAIN;
				return 1;
			}
			else
			{
				return 0;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_D_DCH_GAIN1, MADD_D_DCH_GAIN10) )
		{
			if ( VAL_IN_RANGE(val, 0, 60 ) )	// 下行增益0~40db
			{
				module_param_chg_flag |= PCHG_D_POW_GAIN;
				return 1;
			}
			else
			{
				return 0;
			}
		}

		// 上行整机增益
		if ( VAL_IN_RANGE(mo_addr, MADD_A_UCH_GAIN1, MADD_A_UCH_GAIN16) )
		{
			if ( VAL_IN_RANGE(val, 0, 65 ) )	// 上行增益0~65db
			{
				module_param_chg_flag |= PCHG_A_POW_GAIN;
				return 1;
			}
			else
			{
				return 0;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_B_UCH_GAIN1, MADD_B_UCH_GAIN16) )
		{
			if ( VAL_IN_RANGE(val, 0, 65 ) )	// 上行增益0~65db
			{
				module_param_chg_flag |= PCHG_B_POW_GAIN;
				return 1;
			}
			else
			{
				return 0;
			}
		}
		// 上行整机增益
		if ( VAL_IN_RANGE(mo_addr, MADD_C_UCH_GAIN1, MADD_C_UCH_GAIN10) )
		{
			if ( VAL_IN_RANGE(val, 0, 65 ) )	// 上行增益0~65db
			{
				module_param_chg_flag |= PCHG_C_POW_GAIN;
				return 1;
			}
			else
			{
				return 0;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_D_UCH_GAIN1, MADD_D_UCH_GAIN10) )
		{
			if ( VAL_IN_RANGE(val, 0, 65 ) )	// 上行增益0~65db
			{
				module_param_chg_flag |= PCHG_D_POW_GAIN;
				return 1;
			}
			else
			{
				return 0;
			}
		}

		// 下行数控衰减器，设置数控衰减量相当于修改整机增益
		if ( VAL_IN_RANGE(mo_addr, MADD_A_DCH_ATT1, MADD_A_DCH_ATT16) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
				//module_param_chg_flag |= PCHG_A_DL_ATT;
				return 1;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_B_DCH_ATT1, MADD_B_DCH_ATT16) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
				//module_param_chg_flag |= PCHG_B_DL_ATT;
				return 1;
			}
		}

		// 下行数控衰减器，设置数控衰减量相当于修改整机增益
		if ( VAL_IN_RANGE(mo_addr, MADD_C_DCH_ATT1, MADD_C_DCH_ATT10) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |=SYSTEM_FLAG_SET_RE_UPOW;
				//module_param_chg_flag |= PCHG_C_DL_ATT;
				return 1;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_D_DCH_ATT1, MADD_D_DCH_ATT10) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				//module_param_chg_flag |= PCHG_D_DL_ATT;
				return 1;
			}
		}

		// 上行数控衰减器，设置数控衰减量相当于修改整机增益
		if ( VAL_IN_RANGE(mo_addr, MADD_A_UCH_ATT1, MADD_A_UCH_ATT16) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				TRACE_INFO("MADD_A_UCH_ATT1\r\n");
				sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_B_UCH_ATT1, MADD_B_UCH_ATT16) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}

		// 上行数控衰减器，设置数控衰减量相当于修改整机增益
		if ( VAL_IN_RANGE(mo_addr, MADD_C_UCH_ATT1, MADD_C_UCH_ATT10) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
		if ( VAL_IN_RANGE(mo_addr, MADD_D_UCH_ATT1, MADD_D_UCH_ATT10) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
#if 1				
		// A段 REC端的上行数控衰减量。即RF端的链路上行衰减量
		if ( VAL_IN_RANGE(mo_addr, MADD_A_UCH_REC_RF_ATT1 ,MADD_A_UCH_REC_RF_ATT1 ) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
	
		// B段 REC端的上行数控衰减量。即RF端的链路上行衰减量
		if ( VAL_IN_RANGE(mo_addr, MADD_B_UCH_REC_RF_ATT1 ,MADD_B_UCH_REC_RF_ATT1 ) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
		// C段 REC端的上行数控衰减量。即RF端的链路上行衰减量
		if ( VAL_IN_RANGE(mo_addr, MADD_C_UCH_REC_RF_ATT1 ,MADD_C_UCH_REC_RF_ATT1 ) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
		// D段 REC端的上行数控衰减量。即RF端的链路上行衰减量
		if ( VAL_IN_RANGE(mo_addr, MADD_D_UCH_REC_RF_ATT1 ,MADD_D_UCH_REC_RF_ATT1 ) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
#endif 	
#if 1				
		// A段 REC端的上行数控衰减量。即RF端的链路上行衰减量
		if ( VAL_IN_RANGE(mo_addr, MADD_A_DCH_REC_RF_ATT1 ,MADD_A_DCH_REC_RF_ATT1 ) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
	
		// B段 REC端的上行数控衰减量。即RF端的链路上行衰减量
		if ( VAL_IN_RANGE(mo_addr, MADD_B_DCH_REC_RF_ATT1 ,MADD_B_DCH_REC_RF_ATT1 ) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
		// C段 REC端的上行数控衰减量。即RF端的链路上行衰减量
		if ( VAL_IN_RANGE(mo_addr, MADD_C_DCH_REC_RF_ATT1 ,MADD_C_DCH_REC_RF_ATT1 ) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
		// D段 REC端的上行数控衰减量。即RF端的链路上行衰减量
		if ( VAL_IN_RANGE(mo_addr, MADD_D_DCH_REC_RF_ATT1 ,MADD_D_DCH_REC_RF_ATT1 ) )
		{
			if ( val>31 )
			{
				return 0;
			}
			else
			{
				sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
				return 1;
			}
		}
#endif 
		// 光口使能
		if ( VAL_IN_RANGE(mo_addr, MADD_FP1_EN, MADD_FP8_EN) )
		{
			if ( val>1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_SYS_FP_EN;
				return 1;
			}
		}

		// 延时模式
		if (MADD_DELAY_MODE==mo_addr)
		{
			if ( val>1 )
			{
				return 0;
			}
			else
			{
				TRACE_INFO( "MADD_DELAY_MODE\r\n" );
				module_param_chg_flag |= PCHG_OPT_DELAY;
				return 1;
			}
		}

		// 低功耗模式设置
		if ( MADD_LOW_POWER==mo_addr )
		{
			module_param_chg_flag |= PCHG_LOW_POWER;
			return 1;
		}
		
		// 透传端口设置
		if (MADD_THR_PORT==mo_addr)
		{
			if ( val>1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_THR_CONFIG;
				return 1;
			}
		}

		if (MADD_THR_BAUD==mo_addr)
		{
			if ( val>4 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_THR_CONFIG;
				return 1;
			}
		}

		// 控制端口波特率
		if (MADD_CTRL_BAUD==mo_addr)
		{
			if ( val>4 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_CTRL_BAUD;
				return 1;
			}
		}
		
		// 宽带版本的GSM带宽设置
		if ( MADD_GSM_BW_SEL==mo_addr )
		{
			//module_param_chg_flag |= PCHG_SYS_CFG;
			return 1;
		}

		// 工作使能
		if ((MADD_A_DL_WORK_EN==mo_addr)||(MADD_A_UL_WORK_EN==mo_addr))
		{
			if ( val>1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_A_WORK_EN;
				return 1;
			}
		}

		if ((MADD_B_DL_WORK_EN==mo_addr)||(MADD_B_UL_WORK_EN==mo_addr))
		{
			if ( val>1 )
			{
				return 0;
			}
			module_param_chg_flag |= PCHG_B_WORK_EN;
			return 1;
		}
		if ((MADD_C_DL_WORK_EN==mo_addr)||(MADD_C_UL_WORK_EN==mo_addr))
		{
			if ( val>1 )
			{
				return 0;
			}			
			module_param_chg_flag |= PCHG_C_WORK_EN;
			return 1;
		}

		if ((MADD_D_DL_WORK_EN==mo_addr)||(MADD_D_UL_WORK_EN==mo_addr))
		{
			if ( val>1 )
			{
				return 0;
			}			
			module_param_chg_flag |= PCHG_D_WORK_EN;
			
			return 1;
		}		
		// 射频开关使能
		if ((MADD_A_DL_RF_EN==mo_addr)||(MADD_A_UL_RF_EN==mo_addr))
		{
			if ( val>1 )
			{				
				return 0;
			}			
			module_param_chg_flag |= PCHG_A_WORK_EN;
			sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}

		if ((MADD_B_DL_RF_EN==mo_addr)||(MADD_B_UL_RF_EN==mo_addr))
		{
			if ( val>1 )
			{
				return 0;
			}			
			module_param_chg_flag |= PCHG_B_WORK_EN;
			sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}
		if ((MADD_C_DL_RF_EN==mo_addr)||(MADD_C_UL_RF_EN==mo_addr))
		{
			if ( val>1 )
			{
				return 0;
			}			
			module_param_chg_flag |= PCHG_C_WORK_EN;
			sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}

		if ((MADD_D_DL_RF_EN==mo_addr)||(MADD_D_UL_RF_EN==mo_addr))
		{
			if ( val>1 )
			{
				return 0;
			}			
			module_param_chg_flag |= PCHG_D_WORK_EN;
			sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}		
		
		if ( VAL_IN_RANGE(mo_addr, MADD_TD_T0_UD, MADD_TD_T6_UD) )
		{
			if ( val>1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_C_TD_TYPE_SELECT, MADD_C_TD_EXTENDED_CP)  )
		{

			module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;

		}
		if ( VAL_IN_RANGE(mo_addr, MADD_D_TD_TYPE_SELECT, MADD_D_TD_EXTENDED_CP) )
		{
				module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;

		}

		
		// TD工作模式
		if ( MADD_TD_WORK_MODE==mo_addr )
		{
			module_param_chg_flag |= PCHG_TD_PARAM;
			return 1;
		}
		
		// TD工作模式
		if ( MADD_C_TD_WORK_MODE==mo_addr )
		{
			module_param_chg_flag |= PCHG_TD_PARAM;
			return 1;
		}		
		// TD工作模式
		if ( MADD_D_TD_WORK_MODE==mo_addr )
		{
			module_param_chg_flag |= PCHG_TD_PARAM;
			return 1;
		}	

		// 自动频点搜索使能
		if ( MADD_FPS_AUTO_SCAN==mo_addr )
		{
			module_param_chg_flag |= PCHG_FPS_RANGE;
			return 1;
		}
		// 频点切换功率门限
		if ( MADD_FPS_SWITCH_THD==mo_addr )
		{
			if ( val>50 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_FPS_RANGE;
				return 1;
			}
		}
		// 频点搜索参数
		if ( VAL_IN_RANGE( mo_addr, MADD_FPS_MOSVC_SEL, MADD_FPS_RFRANGE_SEL) )
		{
			module_param_chg_flag |= PCHG_FPS_RANGE;
			return 1;
		}
		if ( VAL_IN_RANGE(mo_addr, MADD_METER_OFFSET,MADD_METER_OFFSET) )
		{
			sys_param_1b[mo_addr].val=val;
			
			//InitPartA();   
			//InitPartB(); 
			//InitPartC();   
			//InitPartD(); 
			sys_work_info|= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_METER_OFFSET_B,MADD_METER_OFFSET_B) )
		{  
			sys_param_1b[mo_addr].val=val;
			//InitPartB(); 
			sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}
		if ( VAL_IN_RANGE(mo_addr, MADD_METER_OFFSET_C,MADD_METER_OFFSET_C) )
		{  
			sys_param_1b[mo_addr].val=val;
			//InitPartC(); 
			sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}
		if ( VAL_IN_RANGE(mo_addr, MADD_METER_OFFSET_D,MADD_METER_OFFSET_D) )
		{  
			sys_param_1b[mo_addr].val=val;
			//InitPartD(); 

			return 1;
		}

		if(VAL_IN_RANGE(mo_addr, MADD_FREQ_MODIF_VAL_D,MADD_FREQ_MODIF_VAL_D))
		{
			module_param_chg_flag |= PCHG_D_CHANNEL;
			module_param_chg_flag |= PCHG_A_CHANNEL;
			module_param_chg_flag |= PCHG_B_CHANNEL;
			sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}

		if(VAL_IN_RANGE(mo_addr, MADD_B_TDS_2TH_BREAKING_POINT_SET,MADD_B_TDS_2TH_BREAKING_POINT_SET))
		{
			if((val>5)||(val<1))
			{
				return 0;
			}
			tmp=0x7e&((0x1f>>(5-val))<<1);
			for(i=0;i<7;i++)
			{
				if( (0x1<<i)==((0x1<<i)&tmp) )
				{
					sys_param_1b[MADD_TD_T0_UD+i].val=0;
				}else 
				{
					sys_param_1b[MADD_TD_T0_UD+i].val=1;
				}
			}

			module_param_chg_flag |= PCHG_TD_PARAM;
			return 1;
		}	

		if(VAL_IN_RANGE(mo_addr, MADD_DELAY_MODE_A,MADD_DELAY_MODE_D))
		{
			TRACE_INFO("MADD_DELAY_MODE_A\r\n");			
			sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
			return 1;
		}		


		if(VAL_IN_RANGE(mo_addr, MADD_A_90_VALUE,MADD_D_95_VALUE))
		{

			module_param_chg_flag |= PCHG_BENZHEN_ADJ_FLAG ;
			return 1;
				
		}	
		if(VAL_IN_RANGE(mo_addr, MADD_SLOT_TIME_EN_B,MADD_SLOT_TIME_EN_B))
		{
			TRACE_INFO("MADD_SLOT_TIME_EN_B\r\n");			
			if ( val >1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_TD_PARAM ;
				return 1;
			}
		}		

		if(VAL_IN_RANGE(mo_addr, MADD_SLOT_TIME_EN_C,MADD_SLOT_TIME_EN_C))
		{
			TRACE_INFO("MADD_SLOT_TIME_EN_B\r\n");			
			if ( val >1 )
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_TD_PARAM ;
				return 1;
			}
		}		

		return 1;

	}

	return 0;
	
}

/*************************************************************
Name:CheckParamValid2b         
Description: 检查参数是否正确
Input: 
	param_add: 参数地址
	param_val: 参数值
Return:
	1 - 参数正确
	0 - 参数错误
**************************************************************/
UCHAR8 CheckParamValid2b( UINT16 mo_addr, UINT16 val )
{
	if (mo_addr<SYS_PARAM_2B_COUNT)
	{
//		TRACE_INFO( "c2\r\n" );
		// 信道号
		if ( VAL_IN_RANGE( mo_addr, MADD_A_DL_CHANNEL1, MADD_A_DL_CHANNEL16)
			|| VAL_IN_RANGE( mo_addr, MADD_A_UL_CHANNEL1, MADD_A_UL_CHANNEL16))
		{
			module_param_chg_flag |= PCHG_A_CHANNEL;
			TRACE_INFO("MADD_A_DL_CHANNEL1--------------------------------------Madd:%04X,val:%04X. \r\n", mo_addr,val);	
			return 1;
		}

		if ( VAL_IN_RANGE( mo_addr, MADD_B_DL_CHANNEL1, MADD_B_DL_CHANNEL16)
			|| VAL_IN_RANGE( mo_addr, MADD_B_UL_CHANNEL1, MADD_B_UL_CHANNEL16))
		{
			module_param_chg_flag |= PCHG_B_CHANNEL;
			return 1;
		}
		if ( VAL_IN_RANGE( mo_addr, MADD_C_DL_CHANNEL1, MADD_C_DL_CHANNEL10)
			|| VAL_IN_RANGE( mo_addr, MADD_C_UL_CHANNEL1, MADD_C_UL_CHANNEL10))
		{
			module_param_chg_flag |= PCHG_C_CHANNEL;
			return 1;
		}

		if ( VAL_IN_RANGE( mo_addr, MADD_D_DL_CHANNEL1, MADD_D_DL_CHANNEL10)
			|| VAL_IN_RANGE( mo_addr, MADD_D_UL_CHANNEL1, MADD_D_UL_CHANNEL10))
		{
			module_param_chg_flag |= PCHG_D_CHANNEL;
			return 1;
		}

		// 下行通道功率
		if ( VAL_IN_RANGE(mo_addr, MADD_A_DCH_MAX_POW1, MADD_A_DCH_MAX_POW16) )
		{
			if ( (INT16)val>5 )		// 最大5db
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_A_POW_GAIN;
				return 1;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_B_DCH_MAX_POW1, MADD_B_DCH_MAX_POW16) )
		{
			if ( (INT16)val>5 )		// 最大5db
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_B_POW_GAIN;
				return 1;
			}
		}
		if ( VAL_IN_RANGE(mo_addr, MADD_C_DCH_MAX_POW1, MADD_C_DCH_MAX_POW10) )
		{
			if ( (INT16)val>5 )		// 最大5db
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_C_POW_GAIN;
				return 1;
			}
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_D_DCH_MAX_POW1, MADD_D_DCH_MAX_POW10) )
		{
			if ( (INT16)val>5 )		// 最大5db
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_D_POW_GAIN;
				return 1;
			}
		}
				
		// 上行通道功率
		if ( VAL_IN_RANGE(mo_addr, MADD_A_UCH_MAX_POW1, MADD_A_UCH_MAX_POW16) )
		{
				module_param_chg_flag |= PCHG_A_POW_GAIN;
				
				TRACE_INFO("PCHG_A_POW_GAIN---Madd:%04X,val:%04X. ", mo_addr,val);				
				return 1;
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_B_UCH_MAX_POW1, MADD_B_UCH_MAX_POW16) )
		{
				module_param_chg_flag |= PCHG_B_POW_GAIN;
				return 1;
		}
		if ( VAL_IN_RANGE(mo_addr, MADD_C_UCH_MAX_POW1, MADD_C_UCH_MAX_POW10) )
		{
				module_param_chg_flag |= PCHG_C_POW_GAIN;
				
				TRACE_INFO("PCHG_C_POW_GAIN---Madd:%04X,val:%04X. ", mo_addr,val);				
				return 1;
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_D_UCH_MAX_POW1, MADD_D_UCH_MAX_POW10) )
		{
				module_param_chg_flag |= PCHG_D_POW_GAIN;
				return 1;
		}
	 	

		// 输入输出双工器衰减A
		if ( (mo_addr==MADD_A_UDPX_IN_GAIN) || (mo_addr==MADD_A_UDPX_OUT_GAIN) )
		{
			if ( (INT16)val>315 )		// 最大31.5db
			{
				return 0;
			}
			else
			{
				TRACE_INFO("MADD_A_UDPX_IN_GAIN mo_addr:%04X,val:%04X. ", mo_addr,val);	
				module_param_chg_flag |= PCHG_A_POW_GAIN;
				return 1;
			}
		}

		// 输入输出双工器衰减B
		if ( (mo_addr==MADD_B_UDPX_IN_GAIN) || (mo_addr==MADD_B_UDPX_OUT_GAIN) )
		{
			if ( (INT16)val>315 )		// 最大31.5db
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_B_POW_GAIN;
				return 1;
			}
		}
		
		// 输入输出双工器衰减C
		if ( (mo_addr==MADD_C_UDPX_IN_GAIN) || (mo_addr==MADD_C_UDPX_OUT_GAIN) )
		{
			if ( (INT16)val>315 )		// 最大31.5db
			{
				return 0;
			}
			else
			{
				TRACE_INFO("MADD_A_UDPX_IN_GAIN mo_addr:%04X,val:%04X. ", mo_addr,val);	
				module_param_chg_flag |= PCHG_C_POW_GAIN;
				return 1;
			}
		}

		// 输入输出双工器衰减B
		if ( (mo_addr==MADD_D_UDPX_IN_GAIN) || (mo_addr==MADD_D_UDPX_OUT_GAIN) )
		{
			if ( (INT16)val>315 )		// 最大31.5db
			{
				return 0;
			}
			else
			{
				module_param_chg_flag |= PCHG_D_POW_GAIN;
				return 1;
			}
		}		
		

		if ( VAL_IN_RANGE(mo_addr, MADD_TD_1ST_CP_TIME, MADD_TD_2ND_CP_TIME) )
		{
				module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_TD_LNA_ON_TIME, MADD_TD_LNA_OFF_TIME) )
		{
				module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;
		}
		
		if ( VAL_IN_RANGE(mo_addr, MADD_C_TD_1ST_CP_TIME, MADD_C_TD_2ND_CP_TIME) )
		{
				module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_C_TD_LNA_ON_TIME, MADD_C_TD_LNA_OFF_TIME) )
		{
				module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;
		}
		if ( VAL_IN_RANGE(mo_addr, MADD_D_TD_1ST_CP_TIME, MADD_D_TD_2ND_CP_TIME) )
		{
				module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;
		}

		if ( VAL_IN_RANGE(mo_addr, MADD_D_TD_LNA_ON_TIME, MADD_D_TD_LNA_OFF_TIME) )
		{
				module_param_chg_flag |= PCHG_TD_PARAM;
				return 1;
		}

		if ( VAL_IN_RANGE( mo_addr, MADD_FPS_S1, MADD_FPS_CID_LK_SET ) )		// 频点搜索范围
		{
			module_param_chg_flag |= PCHG_FPS_RANGE;
			return 1;
		}

		
		if( VAL_IN_RANGE(mo_addr, MADD_MOVE_CENTER_FRE_D, MADD_MOVE_CENTER_FRE_U) )
		{
			
			module_param_chg_flag |= PCHG_CENTER_FRE_FLAG;
			return 1;
		}
		return 1;
		
	}
	return 0;
	
}

/*************************************************************
Name:CheckParamValid4b         
Description: 检查参数是否正确
Input: 
	param_add: 参数地址
	param_val: 参数值
Return:
	1 - 参数正确
	0 - 参数错误
**************************************************************/
UCHAR8 CheckParamValid4b( UINT16 mo_addr, UINT32 val )
{
	return 1;
}

/*************************************************************
Name:IsAscParam          
Description: 检查参数地址对应的是否是字符串参数
Input: 
	param_add: 参数地址
Return:
	1 - 是字符串
	0 - 不是字符串参数
**************************************************************/
UCHAR8 IsAscParam( UINT16 mo_add )
{
	if ( mo_add<SYS_PARAM_ASC_COUNT )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************************
Name:SetSysParam          
Description: 设置系统参数
Input:
	length: 数据长度
	p_param: 指向参数设置信息的缓冲
Return: 
	1-设置成功
	0-设置失败
**************************************************************/
UCHAR8 SetSysParam( UINT16 length, UCHAR8 ex_add_flag, UCHAR8 * p_param, UINT16 * p_err_addr )
{
	UCHAR8 pt_mask;	// 参数类型标志位
	UINT16 i,j;
	UINT16 len;
	UINT16 param_addr, addr;
	UINT32 val;

	if (( length>MSG_BIG_PKT_SIZE )||( p_param==NULL ))
	{
		*p_err_addr = 0xfccf;
		return 0;
	}

	switch( ex_add_flag )
	{
	case 0:
		pt_mask = 0;
		break;

	case 1:
		pt_mask = PT_AP;
		break;

	case 2:
		pt_mask = PT_BP;
		break;

	case 3:
		pt_mask = PT_CP;
		break;

	case 4:
		pt_mask = PT_DP;
		break;
	default:
		*p_err_addr = 0xfeef;
		return 0;
	}
	
	for ( i=0; i+3<length; )
	{
		addr = param_addr = p_param[0]|(p_param[1]<<8);
		len = p_param[2];
		p_param += 3;
		i += 3;
		
		if ( 0!=pt_mask )	// 外部参数
		{
			// 将参数地址转化为内部存储地址
			if ( b_FALSE== ParamAddTranslate( len, param_addr, pt_mask, &addr ) )
			{
				*p_err_addr = param_addr;
				TRACE_INFO("addr_err\r\n");
				return 0;	// 无效地址
			}
		}

		TRACE_INFO("Madd:%04X.\r\n ", addr);
		TRACE_INFO("len:%04X.\r\n ", len);		
		if ( 1 == len )			// 设置1字节参数
		{
			if (addr>=SYS_PARAM_1B_COUNT)
			{			
				return 0;				
			}			
			val = *p_param;
			if ( sys_param_1b[addr].val != (UCHAR8)val )
			{
				TRACE_INFO("val2_1:0x%X==%d\r\n ", val,val);
				if ( 0==CheckParamValid1b( addr, (UCHAR8)(0xff&val) ) )
				{
					*p_err_addr = param_addr;
					TRACE_INFO("addr err 11\r\n ");
					return 0;
				}
				TRACE_INFO("val1_1:%04X.==%d\r\n ",sys_param_1b[addr].val,sys_param_1b[addr].val);
				sys_param_1b[addr].val = val;
				AutoSetParam1b(addr);
				//TRACE_INFO("val2_1:0x%X==%d\r\n ", val,val);
			}
		}
		else if ( 2 == len )	// 设置2字节参数
		{
			if (addr>=SYS_PARAM_2B_COUNT)
			{			
				return 0;				
			}			
			val = p_param[0]|(p_param[1]<<8);
			if ( sys_param_2b[addr].val != (UINT16)val )
			{
				if ( 0==CheckParamValid2b( addr, (UINT16)(0xffff&val) ) )
				{
					*p_err_addr = param_addr;
					TRACE_INFO("addr err 22\r\n ");
					return 0;
				}
				TRACE_INFO("val1_2:0x%X==%d\r\n ", sys_param_2b[addr].val,sys_param_2b[addr].val);
				sys_param_2b[addr].val = val;
				TRACE_INFO("val2_2:%04X==%d\r\n ", val,val);				
				AutoSetParam2b(addr);
			}
		}
		else if ( 4 == len )	// 设置4字节参数
		{
			if (addr>=SYS_PARAM_4B_COUNT)
			{			
				return 0;				
			}			
			val = p_param[0]|(p_param[1]<<8)|(p_param[2]<<16)|(p_param[3]<<24);
			if ( sys_param_4b[addr].val != val )
			{
				if ( 0==CheckParamValid4b( addr, val ) )
				{
					*p_err_addr = param_addr;
					TRACE_INFO("addr err 44\r\n ");
					return 0;
				}
				TRACE_INFO("val1_4:%X==%d\r\n ", sys_param_4b[addr].val,sys_param_4b[addr].val);
				sys_param_4b[addr].val = val;
				TRACE_INFO("val2_4:%X==%d\r\n ", val,val);				
				AutoSetParam4b(addr);
			}
		}
		else if ( len <= PARAM_ASC_MAX_LEN )	// 设置字符串参数
		{
			if (addr>=SYS_PARAM_ASC_COUNT)
			{			
				return 0;				
			}			
			// 检查是否是字符串参数
			if ( 0==IsAscParam( addr ) )
			{
				*p_err_addr = param_addr;
				return 0;
			}
			val = ( len<=sys_param_asc[addr].length) ? len : sys_param_asc[addr].length;

			for ( j=0; j<val; j++ )
			{
				sys_param_asc[addr].p_asc[j] = p_param[j];
			}
			
			for ( ; j<sys_param_asc[addr].length; j++ )
			{
				sys_param_asc[addr].p_asc[j] = 0;
			}
			TRACE_INFO("sys_param_asc\r\n ");
		}
		else		//参数长度不对
		{
			*p_err_addr = param_addr;
			return 0;
		}
		i+= len;
		p_param+=len;
	}

#if ( B_NETWORK_TYPE==NET_DIVE )	// B段为分集时自动设置参数
	AutoSetDiveParam();		
	if ( 0 != ( module_param_chg_flag&PCHG_A_CHANNEL) )	// 根据A段频点变更标志设置B段标志
	{
		module_param_chg_flag |= PCHG_B_CHANNEL;
	}
#endif

#if 1
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
//	if ( b_TRUE==FPS_GetAutoScanEn() )
	{
		if ( 0 != ( module_param_chg_flag&PCHG_FPS_RANGE) )
		{
			if ( b_FALSE==FPS_CheckParam(SYS_A_FLAG) )
			{
			TRACE_INFO("FPS_CheckParam err\r\n ");				
				return 0;	// 出错
			}
		#if 0
		#endif
		}
	}
//	else
#endif
#endif 
	{
		if ( 0 != ( module_param_chg_flag&PCHG_A_CHANNEL) )
		{
			if ( 0==CheckChannelSetA() )
			{
				TRACE_INFO("CheckChannelSetA err\r\n ");
				return 0;	// 出错
			}
		}
	}

	if ( 0 != ( module_param_chg_flag&PCHG_B_CHANNEL) )
	{
		if ( 0==CheckChannelSetB() )
		{
			TRACE_INFO("CheckChannelSetB err\r\n ");
			return 0;	// 出错
		}
	}

	if ( 0 != ( module_param_chg_flag&PCHG_C_CHANNEL) )
	{
		if ( 0==CheckChannelSetC() )
		{
			TRACE_INFO("CheckChannelSetB err\r\n ");
			return 0;	// 出错
		}
	}

	if ( 0 != ( module_param_chg_flag&PCHG_D_CHANNEL) )
	{
		if ( 0==CheckChannelSetD() )
		{
			TRACE_INFO("CheckChannelSetB err\r\n ");
			return 0;	// 出错
		}
	}	
	return 1;	

}




/*************************************************************
Name:SetSysParam          
Description: 设置系统参数
Input:
	length: 数据长度
	ex_add: 1-外部参数，地址需转换
	p_cmd: 命令数据指针
	p_ret: 返回数据指针
Return: 
	返回数据字节长度
**************************************************************/
UINT16 GetSysParam( UINT32 length, UCHAR8 ex_mask, UCHAR8 * p_cmd, UCHAR8 * p_ret )
{
	UINT16 i,j;
	UINT16 addr, mo_addr;
	UINT16 ret_len = 0;
	UINT32 tmp;
	UCHAR8 len;
	
	if (( length>MSG_BIG_PKT_SIZE )||( p_cmd==NULL )||( p_ret==NULL))
	{
		return 0;
	}

	for ( i=0; i+3<length; )
	{
		// 读取参数地址
		addr = p_cmd[i+0]|(p_cmd[i+1]<<8);

		// 读取参数长度
		len = p_cmd[i+2];

		// 地址和长度写入应答包
		p_ret[ret_len++] = p_cmd[i+0];
		p_ret[ret_len++] = p_cmd[i+1];
		p_ret[ret_len++] = p_cmd[i+2];
			
		//p_msg_body += 3;
		i+=3;
		
		if ( 0!=ex_mask )
		{
			if ( b_FALSE== ParamAddTranslate( len, addr, ex_mask, &mo_addr ) )
			{
				TRACE_INFO(" ParamErr\r\n");
				return 0;
			}
		}
		else
		{
			mo_addr = addr;
		}
		
		TRACE_INFO_WP("Madd:%d. \r\n", mo_addr);
		WTD_CLR;
		if ( 1 == len )
		{
			if (mo_addr>=SYS_PARAM_1B_COUNT)
			{
				ret_len+=len;
				continue;				
			}		
			if(MADD_B_TDS_2TH_BREAKING_POINT_SET==mo_addr)
			{
				tmp=0;
				for ( j=0; j<7; j++)
				{	
					//TRACE_INFO_WP("J:%X\r\n",j);

					if ( sys_param_1b[MADD_TD_T0_UD+j].val == 0 )
					{
						tmp++;
					}
				}
				//TRACE_INFO_WP("02th_point_val:%X\r\n",sys_param_1b[MADD_B_TDS_2TH_BREAKING_POINT_SET].val);
				sys_param_1b[MADD_B_TDS_2TH_BREAKING_POINT_SET].val=(UCHAR8)tmp;
				//TRACE_INFO_WP("2th_point_val:%X\r\n",sys_param_1b[MADD_B_TDS_2TH_BREAKING_POINT_SET].val);
			}
			// 获取1字节参数
			p_ret[ret_len++] = sys_param_1b[mo_addr].val;
			TRACE_INFO("val_1:0x%X==%d\r\n", sys_param_1b[mo_addr].val,sys_param_1b[mo_addr].val);
		}
		else if ( 2 == len )
		{
			if (mo_addr>=SYS_PARAM_2B_COUNT)
			{
				ret_len+=len;
				continue;				
			}			
			// 获取2字节参数
			tmp = sys_param_2b[mo_addr].val;
			p_ret[ret_len++] = (UCHAR8)(tmp&0x00ff);
			p_ret[ret_len++] = (UCHAR8)((tmp>>8)&0x00ff);
			TRACE_INFO_WP("val_2:0x%X==%d\r\n", tmp,tmp);
		}
		else if ( 4 == len )
		{
			if (mo_addr>=SYS_PARAM_4B_COUNT)
			{
				ret_len+=len;
				continue;				
			}			
			// 获取4字节参数
			tmp = sys_param_4b[mo_addr].val;
			p_ret[ret_len++] = (UCHAR8)(tmp&0x00ff);
			p_ret[ret_len++] = (UCHAR8)((tmp>>8)&0x00ff);
			p_ret[ret_len++] = (UCHAR8)((tmp>>16)&0x00ff);
			p_ret[ret_len++] = (UCHAR8)((tmp>>24)&0x00ff);
			TRACE_INFO_WP("val_4:0x%X==%d\r\n", tmp,tmp);
		}
		else if ( len <= PARAM_ASC_MAX_LEN )
		{
			if (mo_addr>=SYS_PARAM_ASC_COUNT)
			{
				ret_len+=len;
				continue;				
			}			
			// 获取字符串参数
			for ( j=0; j<len; j++ )
			{
				if ( j > sys_param_asc[mo_addr].length )
				{
					p_ret[ret_len++] = 0;
				}
				else
				{
					p_ret[ret_len++] = sys_param_asc[mo_addr].p_asc[j];
				}
			}
		}
		else
		{
			return ret_len;
		}

		i+=len;
		
	}

	return ret_len;

}

/*************************************************************
Name:RestoreSystemPara          
Description:恢复系统参数到外部FLASH中
Input:p_param_buff:指向存有备份数据的缓冲
Output:void         
Return:void
**************************************************************/
void RestoreSystemPara( UCHAR8* p_param_buff )
{

	UINT32 i,j;
	UINT32 length;
//	UCHAR8 val_8;
	UINT16 val_16;
	UINT32 val_32;

	if ( 0 == p_param_buff )
	{
		//无效指针
		return;
	}

	if (( 0xE7 != p_param_buff[0] )||( 0x5C != p_param_buff[1] ))
	{
		//缓冲中没有保存有效地备份数据
		return;
	}

	p_param_buff += 2;

	//取1字节参数
	for ( i=0; i<SYS_PARAM_1B_COUNT; i++ )
	{
		sys_param_1b[i].val = *p_param_buff++;
	}

	//取2字节参数
	for ( i=0; i<SYS_PARAM_2B_COUNT; i++ )
	{
		val_16 = (p_param_buff[0])|(p_param_buff[1]<<8);		//低位在前
		sys_param_2b[i].val = val_16;
		p_param_buff += 2;
	}

	//取4字节参数
	for ( i=0; i<SYS_PARAM_4B_COUNT; i++ )
	{
		val_32 = (p_param_buff[0])|(p_param_buff[1]<<8)|(p_param_buff[2]<<16)|(p_param_buff[3]<<24);	//低位在前
		sys_param_4b[i].val = val_32;
		p_param_buff += 4;
	}

	//取字符串参数
	for ( i=0; i<SYS_PARAM_ASC_COUNT; i++ )
	{
		length = sys_param_asc[i].length;
		for ( j=0; j<length; j++ )
		{
			sys_param_asc[i].p_asc[j] = *p_param_buff++;
		}
	}

	WTD_CLR;
	
}


/*************************************************************
Name:BackupSystemPara          
Description:备份系统参数
Input:p_param_buff:指向存有备份数据的缓冲
Output:void         
Return:void
**************************************************************/
void BackupSystemPara( UCHAR8* p_param_buff )
{
	UINT32 i,j;
	UINT32 length;
//	UCHAR8 val_8;
	UINT16 val_16;
	UINT32 val_32;

	if ( 0 == p_param_buff )
	{
		//无效指针
		return;
	}

	*p_param_buff++ = 0xE7;
	*p_param_buff++ = 0x5C;

	//保存1字节参数
	for ( i=0; i<SYS_PARAM_1B_COUNT; i++ )
	{
		*p_param_buff++ = sys_param_1b[i].val;
	}

	//保存2字节参数
	for ( i=0; i<SYS_PARAM_2B_COUNT; i++ )
	{
		val_16 = sys_param_2b[i].val;
		//低位在前
		*p_param_buff++ = (UCHAR8)(val_16&0x00FF);
		*p_param_buff++ = (UCHAR8)((val_16>>8)&0x00FF);
	}

	//保存4字节参数
	for ( i=0; i<SYS_PARAM_4B_COUNT; i++ )
	{
		val_32 = sys_param_4b[i].val;
		//低位在前
		*p_param_buff++ = (UCHAR8)(val_32&0x000000FF);
		*p_param_buff++ = (UCHAR8)((val_32>>8)&0x000000FF);
		*p_param_buff++ = (UCHAR8)((val_32>>16)&0x000000FF);
		*p_param_buff++ = (UCHAR8)((val_32>>24)&0x000000FF);
	}

	//保存字符串参数
	for ( i=0; i<SYS_PARAM_ASC_COUNT; i++ )
	{
		length = sys_param_asc[i].length;
		for ( j=0; j<length; j++ )
		{
			*p_param_buff++ = sys_param_asc[i].p_asc[j];
		}
	}

	WTD_CLR;
 
}

UINT16 GetMoParamCount( UCHAR8 ab_flag )
{
	UINT16 i;
	UINT16 count;
	UCHAR8 mask;
	
	// 外部参数个数

	if ( SYS_A_FLAG==ab_flag )
	{
		mask = PT_AP;
	}
	else if ( SYS_B_FLAG==ab_flag )
	{
		mask = PT_BP;
	}	
	else if ( SYS_C_FLAG==ab_flag )
	{
		mask = PT_CP;
	}
	else if ( SYS_D_FLAG==ab_flag )
	{
		mask = PT_DP;
	}
	else
	{
		return 0;
	}

	count = 0;
	
	for ( i=0; i<SYS_PARAM_1B_COUNT; i++ )
	{
		if ( 0!=(sys_param_1b[i].type & mask) )
		{
			count++;
		}
	}

	for ( i=0; i<SYS_PARAM_2B_COUNT; i++ )
	{
		if ( 0!=(sys_param_2b[i].type & mask) )
		{
			count++;
		}
	}

	for ( i=0; i<SYS_PARAM_4B_COUNT; i++ )
	{
		if ( 0!=(sys_param_4b[i].type & mask) )
		{
			count++;
		}
	}

	for ( i=0; i<SYS_PARAM_ASC_COUNT; i++ )
	{
		if ( 0!=(sys_param_asc[i].type & mask) )
		{
			count++;
		}
	}

	return count;
	
}

UINT16 GetAllMoParam( UCHAR8 pkt_index, UCHAR8 ab_flag, UCHAR8 * p_dat )
{
	UINT16 count;
	UINT16 param_offset, param_index;
	UINT16 tmp, i;
	UCHAR8 mask;

	if ( 0==pkt_index )
	{
		return 0;
	}

	tmp = (MO_MSG_BODY_SIZE-2)/4;		// 一次传输能发送的参数个数

	if ( SYS_A_FLAG==ab_flag )
	{
		count = (mo_param_count_a+(tmp-1))/tmp;	// 总包数
		mask = PT_AP;
	}
	else if ( SYS_B_FLAG==ab_flag )
	{
		count = (mo_param_count_b+(tmp-1))/tmp;	// 总包数
		mask = PT_BP;
	}
	else if ( SYS_C_FLAG==ab_flag )
	{
		count = (mo_param_count_c+(tmp-1))/tmp;	// 总包数
		mask = PT_CP;
	}
	else if ( SYS_D_FLAG==ab_flag )
	{
		count = (mo_param_count_d+(tmp-1))/tmp;	// 总包数
		mask = PT_DP;
	}
	else
	{
		return 0;
	}

	*p_dat++ = (UCHAR8)(count&0xff);
	*p_dat++ = pkt_index;

	param_offset = (pkt_index-1)*tmp;

	count = 0;
	param_index = 0;

	//TRACE_INFO_WP("\r\n%d: ", pkt_index);
	TRACE_INFO("ab_flag:%02X,\r\n",ab_flag);	
	
	//TRACE_INFO_WP("<1B>");
	for ( i=0; (i<SYS_PARAM_1B_COUNT)&&(count<tmp); i++ )
	{
		if ( 0 != (sys_param_1b[i].type&mask) )
		{
			param_index++;
			if ( param_index>param_offset )
			{
				if(0x0000==sys_param_1b[i].addr)
				TRACE_INFO_WP("\r\n----sys_param_1b[%d].type:%02X.mask=[%x]",i, sys_param_1b[i].type,mask);
				
				TRACE_INFO_WP("Prm_1=[%d]:%04X.",i, sys_param_1b[i].addr);
				*p_dat++ = (UCHAR8)(sys_param_1b[i].addr&0xff);
				*p_dat++ = (UCHAR8)((sys_param_1b[i].addr>>8)&0xff);
				*p_dat++ = 1;
				*p_dat++ = calc_type[ sys_param_1b[i].type&PTM_MASK ];
				param_offset++;
				count++;
			}
		}
	}

	//TRACE_INFO_WP("<2B>");
	for ( i=0; (i<SYS_PARAM_2B_COUNT)&&(count<tmp); i++ )
	{
		if ( 0 != (sys_param_2b[i].type&mask) )
		{
			param_index++;
			if ( param_index>param_offset )
			{
				if(0x0000==sys_param_2b[i].addr)
				TRACE_INFO_WP("\r\n----sys_param_2b[%d].type:%02X.mask=[%x]",i, sys_param_2b[i].type,mask);
				
				TRACE_INFO_WP("Prm_2=[%d]:%04X.",i, sys_param_2b[i].addr);
				*p_dat++ = (UCHAR8)(sys_param_2b[i].addr&0xff);
				*p_dat++ = (UCHAR8)((sys_param_2b[i].addr>>8)&0xff);
				*p_dat++ = 2;
				*p_dat++ = calc_type[ sys_param_2b[i].type&PTM_MASK ];
				param_offset++;
				count++;
			}
		}
	}

	//TRACE_INFO_WP("<4B>");
	for ( i=0; (i<SYS_PARAM_4B_COUNT)&&(count<tmp); i++ )
	{
		if ( 0 != (sys_param_4b[i].type&mask) )
		{
			param_index++;
			if ( param_index>param_offset )
			{
				if(0x0000==sys_param_4b[i].addr)
				TRACE_INFO_WP("\r\n----sys_param_4b[%d].type:%02X.mask=[%x]",i, sys_param_4b[i].type,mask);
				
				TRACE_INFO_WP("Prm_4=[%d]:%04X.",i, sys_param_4b[i].addr);
				*p_dat++ = (UCHAR8)(sys_param_4b[i].addr&0xff);
				*p_dat++ = (UCHAR8)((sys_param_4b[i].addr>>8)&0xff);
				*p_dat++ = 4;
				*p_dat++ = calc_type[ sys_param_4b[i].type&PTM_MASK ];
				param_offset++;
				count++;
			}
		}
	}
	
	//TRACE_INFO_WP("<ASC>");
	for ( i=0; (i<SYS_PARAM_ASC_COUNT)&&(count<tmp); i++ )
	{
		if ( 0 != (sys_param_asc[i].type&mask) )
		{
			param_index++;
			if ( param_index>param_offset )
			{
				if(0x0000==sys_param_asc[i].addr)
				TRACE_INFO_WP("\r\n----sys_param_asc[%d].type:%02X.mask=[%x]",i, sys_param_asc[i].type,mask);
				
				TRACE_INFO_WP("Prm_ASC=[%d]:%04X.",i, sys_param_asc[i].addr);
				*p_dat++ = (UCHAR8)(sys_param_asc[i].addr&0xff);
				*p_dat++ = (UCHAR8)((sys_param_asc[i].addr>>8)&0xff);
				*p_dat++ = sys_param_asc[i].length;
				*p_dat++ = calc_type[ sys_param_asc[i].type&PTM_MASK ];
				param_offset++;
				count++;
			}
		}
	}

// _EndOfGetAllParam:

	//TRACE_INFO_WP(".END(%d)\r\n", count);
	return (count*4+2);
		
}



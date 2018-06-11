/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : param_dat.c
* Description : 系统参数处理相关函数
* Version     : v0.1
* Author      : RJ
* Date        : 2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			初始版本
**************************************************************/
#include "Header.h"

const UCHAR8 calc_type[]=
{
	0xff,
	0x00,
	0x08,
	0x07,
	0x0A
};


// 模块识别ID号(用ASCII码)			REC/RE
UCHAR8 str_pri_id[PRI_ID_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// 模块类型(用ASCII码)				REC/RE
UCHAR8 str_pri_type[PRI_TYPE_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', '\0'};
// 生产序列号(用ASCII码)			20101030001
UCHAR8 str_pri_seq[PRI_SEQ_LEN]={'2', '0', '1', '0', '1', '0', '3', '0', '0', '0', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// 厂家产品编号(用ASCII码)			DOF-FFFFFFFW21400302
UCHAR8 str_pri_gl_product[PRI_GL_PRODUCT_LEN]={'D', 'O', 'N', '-', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'W', '2', '1', '4', '0', '0', '3', '0', '2'};
// 厂家生产序列号(用ASCII码)		20101030001
UCHAR8 str_pri_gl_seq[PRI_GL_SEQ_LEN]={'2', '0', '1', '0', '1', '0', '3', '0', '0', '0', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// 唯一识别ID(用ASCII码)			REC/RE
UCHAR8 str_pri_gl_rom_id[PRI_GL_ROM_ID_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
// MCU程序日期(用ASCII码)
UCHAR8 str_pri_mcu_date[PRI_MCU_DATE_LEN]={0};
// FPGA程序日期(用ASCII码)
UCHAR8 str_pri_fpga_date[PRI_FPGA_DATE_LEN]={0};
// FPGA2程序日期(用ASCII码)
UCHAR8 str_pri_fpga2_date[PRI_FPGA_DATE_LEN]={0};
// ID识别字符串(用ASCII码)			REC/RE
UCHAR8 str_module_hri_str[MODULE_HRI_STR_LEN]={'R', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
//	9363_A配置文件更新日期(用ASCII码)
UCHAR8 str_a_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	9363_B配置文件更新日期(用ASCII码)
UCHAR8 str_b_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	9363_C配置文件更新日期(用ASCII码)
UCHAR8 str_c_pri_9363_date[PRI_9363_UPDATA_DATE_LEN]={0};
//	ree设备位置信息
UCHAR8 str_mau_position_inf[PRI_MAU_POSITION_INF_LEN]={0};
// MCU程序版本(用ASCII码)
UCHAR8 str_pri_mcu_version_new[MCU_VERSION_NEW_LEN]={'M', 'A', 'U', ' ', ' ', ' ', ' ', ' ', ' ',};


/*
// 字符串参数结构体
typedef struct _S_PARAM_ASC
{
	UINT16	addr;	// 地址
	UCHAR8	type;	// 性质和算法
	UCHAR8	length;	// 字符串长度
	UCHAR8 * p_asc;	// 指向字符串首地址指针
}_T_PARAM_ASC;

_T_PARAM_ASC sys_param_asc[]={
	{ 	PARA_PRI_TYPE, 			PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_TYPE_LEN, str_pri_type },
	{ 	PARA_PRI_ID, 			PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_ID_LEN, str_pri_id },
	{ 	PARA_PRI_MCU_DATE, 		PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_MCU_DATE_LEN, str_pri_mcu_date },
	{ 	PARA_PRI_GL_ROM_ID, 	PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_GL_ROM_ID_LEN, str_pri_gl_rom_id },
	{ 	PARA_PRI_GL_SEQ, 		PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_GL_SEQ_LEN, str_pri_gl_seq },
	{ 	PARA_PRI_GL_PRODUCT, 	PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_GL_PRODUCT_LEN, str_pri_gl_product },
	{ 	PARA_PRI_SEQ, 			PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_SEQ_LEN, str_pri_seq },
	{ 	PARA_MODULE_HRI_STR, 	PT_NC, MODULE_HRI_STR_LEN, str_module_hri_str },
	{ 	PARA_PRI_FPGA_DATE, 	PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_FPGA_DATE_LEN, str_pri_fpga_date },
	{ 	PARA_PRI_FPGA2_DATE, 	PT_AP|PT_BP|PT_CP|PT_DP|PT_RO|PT_NC, PRI_FPGA_DATE_LEN, str_pri_fpga2_date },
	{ 	PARA_A_PRI_9363_UPDATA_DATE, 	PT_AP_G_EX|PT_RO|PT_NC, PRI_9363_UPDATA_DATE_LEN, str_a_pri_9363_date },
	{ 	PARA_B_PRI_9363_UPDATA_DATE, 	PT_BP_G_EX|PT_RO|PT_NC, PRI_9363_UPDATA_DATE_LEN, str_b_pri_9363_date },
	{ 	PARA_C_PRI_9363_UPDATA_DATE, 	PT_CP_G_EX|PT_RO|PT_NC, PRI_9363_UPDATA_DATE_LEN, str_c_pri_9363_date },
	{	PARA_REE_POSITION_INF	,		PT_AP|PT_RO|PT_NC, PRI_MAU_POSITION_INF_LEN, 		str_mau_position_inf },
	{ 	PARA_MCU_VERSION_NEW, 		PT_AP|PT_BP|PT_RO|PT_NC, MCU_VERSION_NEW_LEN, str_pri_mcu_version_new },

};
*/



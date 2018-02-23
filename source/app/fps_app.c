/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : Rfc_scan.c
* Description : GSM频点搜索
* Version     : v1.0
* Author      : RJ
* Date        : 2011-08-31
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2011-08-31		v0.1			初始版本
**************************************************************/
#include "Header.h"

#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
// 外部变量
extern volatile UINT32 sys_work_info;
extern FLOAT32 fpga_dgcic_a;
extern UINT32 module_param_chg_flag;		//系统工作参数修改标志
extern _T_MODULE_CFG mod_cfg_a;
extern _T_MODULE_CFG mod_cfg_b;

// 文件内变量
static UCHAR8 fps_report_head[MSG_PKT_HEAD_SIZE];	// 消息头, 若起始2字节为0xEE, 0xEE表示消息头无效

_T_FPS_REPORT fps_report = { 0, 0, fps_report_head };
_T_FPS_STATUS fps_st;
_T_PBCCH_INFO pbcch_inf;
#endif

/*************************************************************
// 整数求模，va为被除数，vb为除数，返回值为va除以vb的余数
// va可为任意整数，vb只能为正数
*************************************************************/
int FPS_CalcMod( int va, int vb )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能

	if ( va<0 )
	{
		do
		{
			va += vb;
		}while ( va<0 );
	}
	else
	{
		va = va % vb;
	}
	return va;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_GetBitStream          
Description: 从位流提取一段数据, 位流数据格式:起始位-> B0[7:0]-B1[7:0]-B2[7:0]...Bn[7:0] <-结束位
Input: [bit_start: 数据位的起始位置,0开始] [bit_len:截取位长度,最长32位] [p_bitstream:位流数据指针]
Return: [提取的数据值]
**************************************************************/
UINT32 FPS_GetBitStream( UINT16 bit_start, UCHAR8 bit_len, UCHAR8 * p_bitstream )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 bit_offset;
	UCHAR8 tmp;
	UINT32 ret_val = 0;

	p_bitstream += (bit_start/8);	// 取得位起始所在的字节位置
	tmp = *p_bitstream++;
	
	bit_offset = bit_start%8;		// 定位到位起始位置
	tmp <<= bit_offset;
	while ( bit_len-- )
	{
		// 读取位值
		ret_val <<= 1;
		if ( 0!=(tmp&0x80) )
		{
			ret_val++;
		}
		// 下一位
		bit_offset++;
		if ( bit_offset>= 8 )
		{
			bit_offset = 0;
			tmp = *p_bitstream++;
		}
		else
		{
			tmp <<= 1;
		}
	}
	return ret_val;
	
#else
	return 0;
#endif
}


/*************************************************************
Name:DecodeFn          
Description: TCH Bitmap N 格式解码
Input: 
	num:要求的频点序号(0~15)
	format: 编码格式
	w_list: TCH携带的W1到W16共16个计算参数
Return:
	该序号对应的FN
**************************************************************/
UINT16 FPS_DecodeFn( UCHAR8 num, UINT16 format, UINT16 * w_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 index = num+1;
	INT16 j=1;		// 不大于index的2的整次幂的最大值
	INT32 tmp = w_list[index-1];
	INT32 v_parent;

	// 计算J的值
	while ( j*2 <= index )
	{
		j *= 2;
	}
		
	while ( index > 1 )
	{
		if ( 2*index < 3*j )
		{
			index = index - j/2;
			v_parent = w_list[index-1];
			tmp = ( tmp + v_parent - format/j -1 );
			tmp = FPS_CalcMod( tmp, ((format<<1)/j-1) ) +1;
		}
		else
		{
			index = index - j;
			v_parent = w_list[index-1];
			tmp = tmp + v_parent - 1;
			tmp = FPS_CalcMod( tmp, ((format<<1)/j-1) ) +1;
		}
		j = j/2;
	}
		
	return tmp;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_TchDecFmt0          
Description: TCH Bitmap 0格式解码
	16字节的TCH数据，从tch_buff[0]字节的bit3开始到tch_buff[15]的bit0，依次表示频点的开关状态，置位表示频点使能
Input: 
	tch_buff: TCH的16字节数据，顺序存放
	fc_list: 频点数据，存放使能的频点号
Return:
	使能频点个数
**************************************************************/
UCHAR8 FPS_TchDecFmt0( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 fc_mask;
	UCHAR8 offset;
	UINT16 fc;
	UCHAR8 index;

	//TRACE_INFO("TCH Decode Format0:\r\n");
	index = 0;
	for ( fc=124; fc>0; fc-- )
	{
		fc_mask = 1<<((fc-1)%8);
		offset = 15 - (UCHAR8)((fc-1)/8);		// 
		if ( 0 != (fc_mask & tch_buff[offset]) )
		{
			fc_list[index++] = fc;
			//TRACE_INFO("fp%d:%d\r\n", index, fc);
		}
	}

	return index;
	
#else
	return 0;
#endif
}

/*************************************************************
Name: FPS_TchDecFmtVariable          
Description: TCH Bitmap Variable格式解码
	16字节的TCH数据，从tch_buff[2].0到tch_buff[2].7为10位的频点计算偏移基址
	从tch_buff[2]字节的bit6开始到tch_buff[15]的bit0，依次表示频点的开关状态，置位表示频点使能
Input: 
	tch_buff: TCH的16字节数据，顺序存放
	fc_list: 频点数据，存放使能的频点号
Return:
	使能频点个数
**************************************************************/
UCHAR8 FPS_TchDecFmtVariable( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 fc_mask;
	UCHAR8 offset;
	UINT16 fc;
	UCHAR8 index;
	UINT16 orig_arfcn;

	//TRACE_INFO("TCH Decode Format Variable:\r\n");
	orig_arfcn = ( ((UINT16)tch_buff[0]<<8)|tch_buff[1])&0x1FF;		// W0
	orig_arfcn = ( ((orig_arfcn<<8)|tch_buff[2])>>7)&0x3FF;		// W0

	index = 0;
	fc_list[index++] = orig_arfcn;
	
	for ( fc=111; fc>0; fc-- )
	{
		fc_mask = 1<<((fc-1)%8);
		offset = 15 - (UCHAR8)((fc-1)/8);		// 
		if ( 0 != (fc_mask & tch_buff[offset]) )
		{
			fc_list[index++] = (orig_arfcn+112-fc)%1024;
			//TRACE_INFO("fp%d:%d\r\n", index, fc);
		}
	}

	return index;
	
#else
	return 0;
#endif
}


/*************************************************************
Name:FPS_TchDecFmt1024          
Description: TCH Bitmap 1024 格式解码
Input: 
	tch_buff: TCH的16字节数据，顺序存放
	fc_list: 频点数据，存放使能的频点号
Return:
	使能频点个数
**************************************************************/
UCHAR8 FPS_TchDecFmt1024( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 w[17];
	UINT16 i;
	UCHAR8 count = 0;
	UCHAR8 offset;

	//TRACE_INFO("TCH Decode Format 1024:\r\n");
	offset = 5;
	w[0] = FPS_GetBitStream( offset, 1, tch_buff );	offset+=1; 		// 1
	w[1] = FPS_GetBitStream( offset, 10, tch_buff );	offset+=10; 		// 10
	w[2] = FPS_GetBitStream( offset, 9, tch_buff );	offset+=9; 		// 9
	w[3] = FPS_GetBitStream( offset, 9, tch_buff );	offset+=9; 		// 9
	w[4] = FPS_GetBitStream( offset, 8, tch_buff );	offset+=8; 		// 8
	w[5] = FPS_GetBitStream( offset, 8, tch_buff );	offset+=8; 		// 8
	w[6] = FPS_GetBitStream( offset, 8, tch_buff );	offset+=8; 		// 8
	w[7] = FPS_GetBitStream( offset, 8, tch_buff );	offset+=8; 		// 8
	w[8] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[9] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[10] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[11] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[12] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[13] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[14] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[15] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[16] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6

	if ( w[0] == 1 )	// F0=1, 0号频点是TCH频点范围中的一个
	{
		fc_list[count++] = 0;
	}
	for ( i=1; i<16; i++ )
	{
		if ( w[i]==0 ) break;					// 遇到W为0，表示余下频点都无效
		fc_list[count++] = FPS_DecodeFn( (i-1), 1024, &w[1] );
	}
	return count;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_TchDecFmt512          
Description: TCH Bitmap 512 格式解码
Input: 
	tch_buff: TCH的16字节数据，顺序存放
	fc_list: 频点数据，存放使能的频点号
Return:
	使能频点个数
**************************************************************/
UCHAR8 FPS_TchDecFmt512( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 w[18];
	UINT16 i;
	UCHAR8 offset;

	//TRACE_INFO("TCH Decode Format 512:\r\n");
	offset = 7;
	w[0] = FPS_GetBitStream( offset, 10, tch_buff );	offset+=10; 		// 10
	if ( w[0]==0 ) 	// W0为0，无频点数据
	{
		return 0;
	}
	w[1] = FPS_GetBitStream( offset, 9, tch_buff );	offset+=9; 		// 9
	w[2] = FPS_GetBitStream( offset, 8, tch_buff );	offset+=8; 		// 8
	w[3] = FPS_GetBitStream( offset, 8, tch_buff );	offset+=8; 		// 8
	w[4] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[5] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[6] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[7] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[8] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[9] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[10] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[11] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[12] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[13] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[14] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[15] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[16] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[17] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5

	fc_list[0] = w[0];
	for ( i=1; i<17; i++ )
	{
		if ( w[i]==0 ) break;					// 遇到W为0，表示余下频点都无效
		fc_list[i] = (w[0] + FPS_DecodeFn( (i-1), DCS_MIN_FRE_CODE_CNMOBILE, &w[1] )) % 1024;
		//TRACE_INFO("fp%d:%d\r\n", i, fc_list[i]);
	}
	return i;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_TchDecFmt256          
Description: TCH Bitmap 256 格式解码
Input: 
	tch_buff: TCH的16字节数据，顺序存放
	fc_list: 频点数据，存放使能的频点号
Return:
	使能频点个数
**************************************************************/
UCHAR8 FPS_TchDecFmt256( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 w[22];
	UINT16 i;
	UCHAR8 offset;

	//TRACE_INFO("TCH Decode Format 256:\r\n");

	offset = 7;
	w[0] = FPS_GetBitStream( offset, 10, tch_buff );	offset+=10; 		// 10
	if ( w[0]==0 ) 	// W0为0，无频点数据
	{
		return 0;
	}
	w[1] = FPS_GetBitStream( offset, 8, tch_buff );	offset+=8; 		// 8
	w[2] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[3] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[4] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[5] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[6] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[7] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[8] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[9] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[10] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[11] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[12] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[13] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[14] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[15] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[16] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[17] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[18] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[19] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[20] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[21] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	
	fc_list[0] = w[0];
// printf("Decode 256:\r\nW0=%d, Fc0=%d\r\n", w[0], fc_list[0]);
	for ( i=1; i<21; i++ )
	{
// printf("W%d=%d", i, w[i]);
		if ( w[i]==0 ) break;					// 遇到W为0，表示余下频点都无效
		fc_list[i] = ( w[0] + FPS_DecodeFn( (i-1), 256, &w[1] ) ) % 1024;
		//TRACE_INFO("fp%d:%d\r\n", i, fc_list[i]);
// printf(", Fc%d=%d\r\n", i, fc_list[i]);
	}
// printf(". End\r\n", i, w[i]);
	return i;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_TchDecFmt128          
Description: TCH Bitmap 128 格式解码
Input: 
	tch_buff: TCH的16字节数据，顺序存放
	fc_list: 频点数据，存放使能的频点号
Return:
	使能频点个数
**************************************************************/
UCHAR8 FPS_TchDecFmt128( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 w[29];
	UINT16 i;
	UCHAR8 offset;

	//TRACE_INFO("TCH Decode Format 128:\r\n");
	
	offset = 7;
	w[0] = FPS_GetBitStream( offset, 10, tch_buff );	offset+=10; 		// 10
	if ( w[0]==0 ) 	// W0为0，无频点数据
	{
		return 0;
	}
	w[1] = FPS_GetBitStream( offset, 7, tch_buff );	offset+=7; 		// 7
	w[2] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[3] = FPS_GetBitStream( offset, 6, tch_buff );	offset+=6; 		// 6
	w[4] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[5] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[6] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[7] = FPS_GetBitStream( offset, 5, tch_buff );	offset+=5; 		// 5
	w[8] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[9] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[10] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[11] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[12] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[13] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[14] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[15] = FPS_GetBitStream( offset, 4, tch_buff );	offset+=4; 		// 4
	w[16] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[17] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[18] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[19] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[20] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[21] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[22] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[23] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[24] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[25] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[26] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[27] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3
	w[28] = FPS_GetBitStream( offset, 3, tch_buff );	offset+=3; 		// 3

	fc_list[0] = w[0];
	for ( i=1; i<28; i++ )
	{
		if ( w[i]==0 ) break;					// 遇到W为0，表示余下频点都无效
		fc_list[i] = ( w[0] + FPS_DecodeFn( (i-1), 128, &w[1] ) ) % 1024;
		//TRACE_INFO("fp%d:%d\r\n", i, fc_list[i]);
	}
	return i;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_TchDecode          
Description: 解析TCH数据,获取频点号
Input: [tch_buff: 16字节TCH数据指针]
Return: void
**************************************************************/
void FPS_TchDecode(UCHAR8 * tch_buff)
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 tch_type;
	UCHAR8 rfc_cnt = 0;
	
	tch_type = tch_buff[0] & TCH_TYPE_MASK;

	switch( tch_type )
	{
	case TCH_TYPE_BITMAP_0:
		fps_st.tch_count = FPS_TchDecFmt0( tch_buff, fps_st.tch_lst );
		break;
		
	case TCH_TYPE_RANGE_1024:
		fps_st.tch_count = FPS_TchDecFmt1024( tch_buff, fps_st.tch_lst );
		break;
		
	case TCH_TYPE_RANGE_512:
		fps_st.tch_count = FPS_TchDecFmt512( tch_buff, fps_st.tch_lst );
		break;
		
	case TCH_TYPE_RANGE_256:
		fps_st.tch_count = FPS_TchDecFmt256( tch_buff, fps_st.tch_lst );
		break;
		
	case TCH_TYPE_RANGE_128:
		fps_st.tch_count = FPS_TchDecFmt128( tch_buff, fps_st.tch_lst );
		break;
		
	case TCH_TYPE_BM_VARIABLE:
		fps_st.tch_count = FPS_TchDecFmtVariable( tch_buff, fps_st.tch_lst );
		break;
	
	}

#endif
}

/*************************************************************
Name:FPS_PbcchDecode          
Description: 解析TCH数据,获取频点号
Input: [tch_buff: 16字节TCH数据指针]
Return: void
**************************************************************/
void FPS_PbcchDecode(UCHAR8 * pbcch_buff)
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 bit_offset; 
	UCHAR8 val;
	UCHAR8 tmp;

	// 初始化PBCCH状态
	pbcch_inf.valid = 0;
	pbcch_inf.gprs_support = 0;
	pbcch_inf.pbcch_support = 0;
	pbcch_inf.rfl_lst_support = 0;
	pbcch_inf.pbcch_fc_valid = 0;
	pbcch_inf.edge_support = 0;

	// 开始解析数据流
	bit_offset = 0; 
	val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 读取第1位数据
	bit_offset ++;
	if ( 0==val )
	{
		return;		// 第1位为0,无效信息,返回
	}
	pbcch_inf.valid = 1;	// 信息有效

	bit_offset+=7;		// 跳过 3位的BCCH_CHANGE_MARK + 4位的SI_CHANGE_FILED

	val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
	bit_offset++;
	if ( 1==val )		// =1,有GPRS频点信息
	{
		pbcch_inf.gprs_support = 1;	// 置标志位
		bit_offset += 2;		// 跳过2位的SI13_CHANGE_MARK
		// ---- GPRS Mobile Allocation IE ----
		bit_offset += 6;		// 跳过6位的HSN
		val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
		bit_offset++;
		if ( 1==val ) // =1,有RFL number list频点信息
		{
			pbcch_inf.rfl_lst_support = 1;
			pbcch_inf.rfl_count = 0;
			do
			{
				val = FPS_GetBitStream( bit_offset, 4, pbcch_buff );	// 读取4位RFL_NUMBER
				bit_offset += 4;
				pbcch_inf.rfl_lst[pbcch_inf.rfl_count++] = val;
				val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
				bit_offset++;
			}while ( 1==val );		// =0结束循环
		}

		val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
		bit_offset++;
		if ( 0==val )	// =0, 位映射TCH频点信息
		{
			pbcch_inf.arfcn_lst_mode = 0;	// 位映射模式
			val = pbcch_inf.ma_len = FPS_GetBitStream( bit_offset, 6, pbcch_buff )+1;		// 读取6位MA_LENGTH
			bit_offset += 6;
			tmp = 0;
			while ( val>0 )	// 读取BITMAP信息
			{
				if ( val>8 )
				{
					pbcch_inf.ma_bm[tmp++]= FPS_GetBitStream( bit_offset, 8, pbcch_buff );		// 读取8位BITMAP信息
					bit_offset += 8;
					val -= 8;
				}
				else
				{
					pbcch_inf.ma_bm[tmp] = FPS_GetBitStream( bit_offset, val, pbcch_buff );	// 读取n位BITMAP信息
					pbcch_inf.ma_bm[tmp] <<= (8-val);		// MSB对齐
					bit_offset += val;
					val = 0;
				}
			}
		}
		else		// =1, 列表模式TCH频点信息
		{
			pbcch_inf.arfcn_lst_mode = 1;	// 列表索引模式
			pbcch_inf.arfcn_count = 0;		// 索引个数清零
			val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
			bit_offset++;
			while ( 1==val )	// =0结束循环
			{
				val = FPS_GetBitStream( bit_offset, 6, pbcch_buff );	// 读取6位ARFCN_INDEX
				bit_offset += 6;
				pbcch_inf.arfcn_lst[pbcch_inf.arfcn_count++] = val;
				val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
				bit_offset++;
			}
		}
		// ---- End: GPRS Mobile Allocation IE ----
	}// 处理GPRS频点信息结束

	val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
	bit_offset++;
	if ( 1==val )	// =1, 包含PBCCH频点
	{
		pbcch_inf.pbcch_support = 1;	// 支持PBCCH频点
		bit_offset += 4;	// 跳过4位PS11_REPEAT_PERIOD
		bit_offset += 4;	// 跳过4位Pb
		bit_offset += 5;	// 跳过4位TSC
		bit_offset += 6;	// 跳过4位TN
		val = FPS_GetBitStream( bit_offset, 2, pbcch_buff );	// 2位分支
		bit_offset += 2;
		if ( 1==val )	// =01, 表示有PBCCH频点ARFCN
		{
			pbcch_inf.pbcch_fc_valid = 1;	// PBCCH的频点有效
			pbcch_inf.pbcch_arfcn = FPS_GetBitStream( bit_offset, 10, pbcch_buff );	// 读取10位ARFCN
			bit_offset += 10;
		}
	}
	else		// =0, 不包含PBCCH频点, 解读EDGE信息
	{
		bit_offset += 8;	// 跳过4位RAC
		bit_offset += 1;	// 跳过1位SPGC_CCCH_SUP
		bit_offset += 3;	// 跳过3位PRIORITY_ACCESS_THR
		bit_offset += 2;	// 跳过2位NETWORK_CONTROL_ORDER
		// ---- GPRS Cell Options IE ----
		bit_offset += 2;	// 跳过2位NMO
		bit_offset += 3;	// 跳过3位T3168
		bit_offset += 3;	// 跳过3位T3192
		bit_offset += 3;	// 跳过3位DRX_TIMER_MAX
		bit_offset += 1;	// 跳过1位ACCESS_BURST_TYPE
		bit_offset += 1;	// 跳过1位CONTROL_ACK_TYPE
		bit_offset += 4;	// 跳过4位BS_CV_MAX
		val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
		bit_offset ++;
		if ( 1==val )	// =1, PAN信息, 跳过
		{
			bit_offset += 9;	// 跳过3位PAN_DEC + 3位PAN_INC + 3位PAN_MAX
		}
		val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
		bit_offset ++;
		if ( 1==val )	// =1, 包含EDGE信息
		{
			bit_offset += 6;	// 跳过6位Extension Length
			val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1位分支
			bit_offset ++;
			if ( 1==val )	// =1, 包含EDGE信息
			{
				pbcch_inf.edge_support = 1;	// 支持EDGE频点
			}
		}
	}
#endif
}

/*************************************************************
Name:FPS_CheckParam          
Description: 检查扫描范围, 并计算搜索的频点个数
Input: [p_mo_cfg:模块配置指针,供计算频率用]
Return: TRUE-参数有效, FALSE-参数无效
**************************************************************/
#if 1 
BOOL FPS_CheckParam( UCHAR8 ab_flag )  //edasion
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 fc_start, fc_end; 
	UINT16 tmp;
	INT32  freq;
	INT32  freq_min = 0;
	INT32  freq_max = 0;
	UINT16 fc_min   = 0;
	UINT16 fc_max   = 0; 
	UCHAR8 fc_count = 0;
	UCHAR8 ucNetTpy = 0;


    ucNetTpy = ((SYS_A_FLAG == ab_flag)? fpga_cfg.a_net_type : fpga_cfg.b_net_type);

	
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 0;	    // 锁定运营商失败
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 0;	// 锁定频段失败

#ifdef FPS_LOCK_RANGE	// 锁定搜索范围
	sys_param_2b[MADD_FPS_S1].val = FPS_RANGE_S1; 
	sys_param_2b[MADD_FPS_E1].val = FPS_RANGE_E1; 
	sys_param_2b[MADD_FPS_S2].val = FPS_RANGE_S2; 
	sys_param_2b[MADD_FPS_E2].val = FPS_RANGE_E2;  
#else   
	if ( 128==sys_param_1b[MADD_FPS_MOSVC_SEL].val )	// 手动指定搜索频点号
	{
		;
	}
	else if ( 1==sys_param_1b[MADD_FPS_MOSVC_SEL].val )	// 联通频段
	{
	#if ( A_NETWORK_TYPE==NET_TYPE_GSM900 )		// GSM900
		if ( 1==sys_param_1b[MADD_FPS_RFRANGE_SEL].val )
		{
			sys_param_2b[MADD_FPS_S1].val = 96;
			sys_param_2b[MADD_FPS_E1].val = 124;
			sys_param_2b[MADD_FPS_S2].val = 0;
			sys_param_2b[MADD_FPS_E2].val = 0;
		}
	#else	// DCS1800
		if ( 2==sys_param_1b[MADD_FPS_RFRANGE_SEL].val )
		{
			TRACE_INFO("FPS_CheckParam dcs 636-736\r\n ");	
			sys_param_2b[MADD_FPS_S1].val = DCS_MIN_FRE_CODE_UNICOM;
			sys_param_2b[MADD_FPS_E1].val = DCS_MAX_FRE_CODE_UNICOM	;
			sys_param_2b[MADD_FPS_S2].val = 0;
			sys_param_2b[MADD_FPS_E2].val = 0;
		}
	#endif
		else
		{
			TRACE_INFO("FPS_CheckParam err1\r\n ");	
			return b_FALSE;
		}
	}
	else // 移动频段
	{
	#if ( A_NETWORK_TYPE==NET_TYPE_GSM900 )		// GSM900
		if ( 1==sys_param_1b[MADD_FPS_RFRANGE_SEL].val )
		{
			sys_param_2b[MADD_FPS_S1].val = 0;
			sys_param_2b[MADD_FPS_E1].val = 95;
			sys_param_2b[MADD_FPS_S2].val = 1000;
			sys_param_2b[MADD_FPS_E2].val = 1023;
		}
	#else	// DCS1800
		if ( 2==sys_param_1b[MADD_FPS_RFRANGE_SEL].val )
		{
			sys_param_2b[MADD_FPS_S1].val = DCS_MIN_FRE_CODE_CNMOBILE;
			sys_param_2b[MADD_FPS_E1].val = DCS_MAX_FRE_CODE_CNMOBILE;
			sys_param_2b[MADD_FPS_S2].val = 0;
			sys_param_2b[MADD_FPS_E2].val = 0;
		}
	#endif
		else
		{
			TRACE_INFO("FPS_CheckParam err2\r\n ");	
			return b_FALSE;
		}
	}
#endif

	fps_st.fc_count = 0;		// 清零频点计数

	// 读取扫描段1频点范围,在参数设置时,保证fc_start<fc_end
	fc_start = sys_param_2b[MADD_FPS_S1].val;
	fc_end = sys_param_2b[MADD_FPS_E1].val;
	
	TRACE_INFO("fc_start=[%d],fc_end=[%d].FPS_CheckParam\r\n ",fc_start,fc_end);	

	// 逐个检查频点号是否有效,并取得最大频率和最小频率
	for ( ; fc_start<=fc_end; fc_start++ )
	{
         
		freq = CalcFreqPointToFreq( ucNetTpy,fc_start );  // edasion
		//freq = p_mo_cfg->lpf_ConvFcToFreq( fc_start );  // edasion
		
		if ( freq<0 )
		{
			TRACE_INFO("FPS_CheckParam err3\r\n ");	
			return b_FALSE;	// 无效频点号
		}
		if (( 0==freq_min )||( freq<freq_min ))
		{
			freq_min = freq;
			fc_min = fc_start;
		}
		if (( 0==freq_max )||( freq>freq_max ))
		{
			freq_max = freq;
			fc_max = fc_start;
		}    
		
		fc_count++;
		
	}
		TRACE_INFO("1freq_max=[%d],freq_min=[%d].FPS_CheckParam err6\r\n ",freq_max,freq_min);	
	// 第二扫描段起始频点号不为0,表示使用第二扫描段
	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		// 读取扫描段2频点范围,在参数设置时,保证fc_start<fc_end
		fc_start = sys_param_2b[MADD_FPS_S2].val;
		fc_end = sys_param_2b[MADD_FPS_E2].val;
		// 逐个检查频点号是否有效,并取得最大频率和最小频率
		for ( ; fc_start<=fc_end; fc_start++ )
		{
			freq = CalcFreqPointToFreq( ucNetTpy,fc_start );  // edasion
			//freq = p_mo_cfg->lpf_ConvFcToFreq( fc_start );  edasion
			
			if ( freq<0 )
			{
							TRACE_INFO("FPS_CheckParam err4\r\n ");	
				return b_FALSE;	// 无效频点号
			} 
			if (( 0==freq_min )||( freq<freq_min ))
			{
				freq_min = freq;
				fc_min = fc_start;
			}
			if (( 0==freq_max )||( freq>freq_max ))
			{
				freq_max = freq;
				fc_max = fc_start;
			}
			
			fc_count++;
		}
	}
	TRACE_INFO("freq_max=[%d],freq_min=[%d].FPS_CheckParam err6\r\n ",freq_max,freq_min);
if(NET_TYPE_GSM900==ucNetTpy)
{
	// 若最大频率为0,或最小频率为0,或频率跨度超过允许的带宽,返回FALSE
	if ( (0==freq_max) || (0==freq_min) || ((freq_max-freq_min)>PLL_RANGE) )
	{
					TRACE_INFO("FPS_CheckParam err6\r\n ");	
		return b_FALSE;
	}
}
else if(NET_TYPE_DCS1800==ucNetTpy)
{
	// 若最大频率为0,或最小频率为0,或频率跨度超过允许的带宽,返回FALSE
	if ( (0==freq_max) || (0==freq_min) || ((freq_max-freq_min)>DCS_PLL_RANGE) )
	{
					TRACE_INFO("FPS_CheckParam err6\r\n ");	
		return b_FALSE;
	}
}	
	// 计算对应的本振频率
	#if 0   //edasion
	if ( b_FALSE == p_mo_cfg->lpf_CheckLocalPll( fc_max, fc_min, &(p_mo_cfg->dl_pcf), &(p_mo_cfg->ul_pcf) ) )
	{
		p_mo_cfg->dl_pcf.ftoset = -1;
		p_mo_cfg->ul_pcf.ftoset = -1;
		return b_FALSE;
	}
	#endif
	
	// 设置4153更新标志,切换到新的本振     
	SET_BIT_FLAG(module_param_chg_flag, PCHG_A_FL_CHG);

#if ( B_NETWORK_TYPE==NET_DIVE )
	//mod_cfg_b.dl_pcf.ftoset = mod_cfg_a.dl_pcf.ftoset;
	//mod_cfg_b.ul_pcf.ftoset = mod_cfg_a.ul_pcf.ftoset;
	// 设置4153更新标志,切换到新的本振 
	SET_BIT_FLAG(module_param_chg_flag, PCHG_B_FL_CHG);
#endif

	fps_st.fc_count = fc_count;		// 保存频点个数
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 1;	// 锁定运营商成功
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 1;	// 锁定频段成功
				TRACE_INFO("FPS_CheckParam 0K1\r\n ");	
	return b_TRUE;
	
#else
			TRACE_INFO("FPS_CheckParam OK2\r\n ");	
	return b_TRUE;
#endif	
}
#else
BOOL FPS_CheckParam( _T_PMODULE_CFG p_mo_cfg )  //edasion
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 fc_start, fc_end;
	UINT16 tmp;
	INT32 freq;
	INT32 freq_min=0;
	INT32 freq_max=0;
	UINT16 fc_min=0;
	UINT16 fc_max = 0;
	UCHAR8 fc_count = 0;
	
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 0;	// 锁定运营商失败
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 0;	// 锁定频段失败

#ifdef FPS_LOCK_RANGE	// 锁定搜索范围
	sys_param_2b[MADD_FPS_S1].val = FPS_RANGE_S1;
	sys_param_2b[MADD_FPS_E1].val = FPS_RANGE_E1;
	sys_param_2b[MADD_FPS_S2].val = FPS_RANGE_S2;
	sys_param_2b[MADD_FPS_E2].val = FPS_RANGE_E2;
#else
	if ( 128==sys_param_1b[MADD_FPS_MOSVC_SEL].val )	// 手动指定搜索频点号
	{
		;
	}
	else if ( 1==sys_param_1b[MADD_FPS_MOSVC_SEL].val )	// 联通频段
	{
	#if ( A_NETWORK_TYPE==NET_TYPE_GSM900 )		// GSM900
		if ( 1==sys_param_1b[MADD_FPS_RFRANGE_SEL].val )
		{
			sys_param_2b[MADD_FPS_S1].val = 96;
			sys_param_2b[MADD_FPS_E1].val = 124;
			sys_param_2b[MADD_FPS_S2].val = 0;
			sys_param_2b[MADD_FPS_E2].val = 0;
		}
	#else	// DCS1800
		if ( 2==sys_param_1b[MADD_FPS_RFRANGE_SEL].val )
		{
			sys_param_2b[MADD_FPS_S1].val = 637;
			sys_param_2b[MADD_FPS_E1].val = 736;
			sys_param_2b[MADD_FPS_S2].val = 0;
			sys_param_2b[MADD_FPS_E2].val = 0;
		}
	#endif
		else
		{
			return b_FALSE;
		}
	}
	else // 移动频段
	{
	#if ( A_NETWORK_TYPE==NET_TYPE_GSM900 )		// GSM900
		if ( 1==sys_param_1b[MADD_FPS_RFRANGE_SEL].val )
		{
			sys_param_2b[MADD_FPS_S1].val = 0;
			sys_param_2b[MADD_FPS_E1].val = 95;
			sys_param_2b[MADD_FPS_S2].val = 1000;
			sys_param_2b[MADD_FPS_E2].val = 1023;
		}
	#else	// DCS1800
		if ( 2==sys_param_1b[MADD_FPS_RFRANGE_SEL].val )
		{
			sys_param_2b[MADD_FPS_S1].val = 512;
			sys_param_2b[MADD_FPS_E1].val = 636;
			sys_param_2b[MADD_FPS_S2].val = 0;
			sys_param_2b[MADD_FPS_E2].val = 0;
		}
	#endif
		else
		{
			return b_FALSE;
		}
	}
#endif

	fps_st.fc_count = 0;		// 清零频点计数

	// 读取扫描段1频点范围,在参数设置时,保证fc_start<fc_end
	fc_start = sys_param_2b[MADD_FPS_S1].val;
	fc_end = sys_param_2b[MADD_FPS_E1].val;
	// 逐个检查频点号是否有效,并取得最大频率和最小频率
	for ( ; fc_start<=fc_end; fc_start++ )
	{
		//freq = p_mo_cfg->lpf_ConvFcToFreq( fc_start );  // edasion
		
		if ( freq<0 )
		{
			return b_FALSE;	// 无效频点号
		}
		if (( 0==freq_min )||( freq<freq_min ))
		{
			freq_min = freq;
			fc_min = fc_start;
		}
		if (( 0==freq_max )||( freq>freq_max ))
		{
			freq_max = freq;
			fc_max = fc_start;
		}
		fc_count++;
	}
	// 第二扫描段起始频点号不为0,表示使用第二扫描段
	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		// 读取扫描段2频点范围,在参数设置时,保证fc_start<fc_end
		fc_start = sys_param_2b[MADD_FPS_S2].val;
		fc_end = sys_param_2b[MADD_FPS_E2].val;
		// 逐个检查频点号是否有效,并取得最大频率和最小频率
		for ( ; fc_start<=fc_end; fc_start++ )
		{
			//freq = p_mo_cfg->lpf_ConvFcToFreq( fc_start );  edasion
			
			if ( freq<0 )
			{
				return b_FALSE;	// 无效频点号
			}
			if (( 0==freq_min )||( freq<freq_min ))
			{
				freq_min = freq;
				fc_min = fc_start;
			}
			if (( 0==freq_max )||( freq>freq_max ))
			{
				freq_max = freq;
				fc_max = fc_start;
			}
			
			fc_count++;
		}
	}
	// 若最大频率为0,或最小频率为0,或频率跨度超过允许的带宽,返回FALSE
	if ( (0==freq_max) || (0==freq_min) || ((freq_max-freq_min)>PLL_RANGE) )
	{
		return b_FALSE;
	}
	// 计算对应的本振频率
	#if 0   //edasion
	if ( b_FALSE == p_mo_cfg->lpf_CheckLocalPll( fc_max, fc_min, &(p_mo_cfg->dl_pcf), &(p_mo_cfg->ul_pcf) ) )
	{
		p_mo_cfg->dl_pcf.ftoset = -1;
		p_mo_cfg->ul_pcf.ftoset = -1;
		return b_FALSE;
	}
	#endif
	
	// 设置4153更新标志,切换到新的本振
	SET_BIT_FLAG(module_param_chg_flag, PCHG_A_FL_CHG);

#if ( B_NETWORK_TYPE==NET_DIVE )
	mod_cfg_b.dl_pcf.ftoset = mod_cfg_a.dl_pcf.ftoset;
	mod_cfg_b.ul_pcf.ftoset = mod_cfg_a.ul_pcf.ftoset;
	// 设置4153更新标志,切换到新的本振
	SET_BIT_FLAG(module_param_chg_flag, PCHG_B_FL_CHG);
#endif

	fps_st.fc_count = fc_count;		// 保存频点个数
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 1;	// 锁定运营商成功
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 1;	// 锁定频段成功
	return b_TRUE;
	
#else
	return b_TRUE;
#endif	
}
#endif
/*************************************************************
Name: _CalcFpgaFreqWord
Description:  根据频点号计算扫描频点的FPGA频率字寄存器值
Input: [p_mo_cfg:模块配置指针,供计算频率用] [freq_code: 频点号]
Return: 频率字寄存器的值
**************************************************************/
#if 1
UINT32 FPS_CalcFpgaFreqWord( UCHAR8 ab_flag, UINT16 freq_code )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能

	UINT32 reg_val;
	INT32 up_fre_word, down_fre_word;

	up_fre_word = 0;
	down_fre_word = 0;

    #if 0
		INT32  freq_point = -1;	// 频率
		INT32  digit_freq;	    // 数字频率 
		INT32  freq_word;
		UINT32 fw; 
	 
		//if (( NULL != p_mo_cfg->lpf_ConvFcToFreq )&&( NULL != p_mo_cfg->lpf_CalcDf ))
		{
			 freq_point = CalcFreqPointToFreq(ucNetTye, freq_code) 
			//freq_point = p_mo_cfg->lpf_ConvFcToFreq( freq_code );  edasion
		} 
		if (freq_point<0)
		{
			return 0;
		}
		//digit_freq = p_mo_cfg->lpf_CalcDf( freq_point, &(p_mo_cfg->dl_pcf) );		// 计算数字频率
		freq_word = _CalcFpgaFw( digit_freq );	// 计算频率字
		fw = _AdjustFpgaFw(freq_word);		// 频率字调整

		return _CalcFpgaFwReg(fw);			// 转换成频率字寄存器的值	
    #endif
//	TRACE_INFO("FPS_CalcFpgaFreqWord---------FPS_CalcFpgaFreqWord---------reg_val= %04X,freq_code= %04X\r\n",reg_val,freq_code);
	
	reg_val = SearchFpCalcFreqWord( freq_code ,ab_flag,&up_fre_word,&down_fre_word);  
	if(ab_flag == SYS_B_FLAG)
	{
		reg_val = down_fre_word;
	}
	//reg_val = CalcFpgaFwReg(reg_val); 
	reg_val = down_fre_word; 

	return reg_val;
#else
	return 0; 
#endif
}

#else 

UINT16 FPS_CalcFpgaFreqWord( _T_PMODULE_CFG p_mo_cfg, UINT16 freq_code )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	INT32  freq_point = -1;	// 频率
	INT32  digit_freq;	    // 数字频率 
	INT32  freq_word;
	UINT32 fw; 
 
	if (( NULL != p_mo_cfg->lpf_ConvFcToFreq )&&( NULL != p_mo_cfg->lpf_CalcDf ))
	{
		//freq_point = p_mo_cfg->lpf_ConvFcToFreq( freq_code );  edasion
	} 
	if (freq_point<0)
	{
		return 0;
	}
	//digit_freq = p_mo_cfg->lpf_CalcDf( freq_point, &(p_mo_cfg->dl_pcf) );		// 计算数字频率
	freq_word = _CalcFpgaFw( digit_freq );	// 计算频率字
	fw = _AdjustFpgaFw(freq_word);		// 频率字调整

	return _CalcFpgaFwReg(fw);			// 转换成频率字寄存器的值	
	
#else
	return 0;
#endif
}
#endif
/*************************************************************
Name:FPS_SetScanFc          
Description: 写入扫描频点号到FPGA中
Input: [p_mo_cfg:模块配置指针,供计算频率用] 
Return: void  
**************************************************************/
#if 1
void FPS_SetScanFc( UCHAR8 ab_flag )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 fc;
	UINT32 reg;

	FPGA_ENABLE_WRITE;
	
	// 向Fpga写入要扫描的频点个数
	FpgaWriteRegister( FPGA_REG_RFC_SCAN_CNT, fps_st.fc_count );

	for ( fc=sys_param_2b[MADD_FPS_S1].val; fc<=sys_param_2b[MADD_FPS_E1].val; fc++ )
	{
		reg = FPS_CalcFpgaFreqWord(ab_flag, fc);
//		printf("1频点搜索频率字%x\r\n",reg);
		FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF_1, (UINT16)(((reg>>12)&0x3FFF)|((reg&0x80000000)>>16)));//写频率字的[25:12]位
		FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF_2, (UINT16)(reg&0xFFF));//写频率字的[11:0]位
		//FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF, reg );
	}

	// 第二扫描段起始频点号不为0,表示使用第二扫描段
	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		for ( fc=sys_param_2b[MADD_FPS_S2].val; fc<=sys_param_2b[MADD_FPS_E2].val; fc++ )
		{
			reg = FPS_CalcFpgaFreqWord(ab_flag, fc);
//			printf("2频点搜索频率字%x\r\n",reg);
			//FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF, reg );
			FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF_1, (UINT16)(((reg>>12)&0x3FFF)|((reg&0x80000000)>>16)));//写频率字的[25:12]位
			FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF_2, (UINT16)(reg&0xFFF));//写频率字的[11:0]位

		}
	}

	if ( 1==fps_st.auto_scan_en )	// 自动搜索状态下,更新了搜索范围,重置搜索状态
	{
		fps_st.fps_run = 0;		// 停止当前搜索
		fps_st.scan_st = FPS_SCAN_ST_DONE;	// 修改状态标志为完成
		fps_st.err_st  = FPS_ERR_NONE;		// 清除错误标志
		fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 复位自动搜索状态机
	}

	FPGA_DISABLE_WRITE;
#endif
}

#else

void FPS_SetScanFc( _T_PMODULE_CFG p_mo_cfg )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 fc;
	UINT16 reg;

	FPGA_ENABLE_WRITE;
	
	// 向Fpga写入要扫描的频点个数
	FpgaWriteRegister( FPGA_REG_RFC_SCAN_CNT, fps_st.fc_count );

	for ( fc=sys_param_2b[MADD_FPS_S1].val; fc<=sys_param_2b[MADD_FPS_E1].val; fc++ )
	{
		reg = FPS_CalcFpgaFreqWord(p_mo_cfg, fc);
		FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF, reg );
	}

	// 第二扫描段起始频点号不为0,表示使用第二扫描段
	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		for ( fc=sys_param_2b[MADD_FPS_S2].val; fc<=sys_param_2b[MADD_FPS_E2].val; fc++ )
		{
			reg = FPS_CalcFpgaFreqWord(p_mo_cfg, fc);
			FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF, reg );
		}
	}

	if ( 1==fps_st.auto_scan_en )	// 自动搜索状态下,更新了搜索范围,重置搜索状态
	{
		fps_st.fps_run = 0;		// 停止当前搜索
		fps_st.scan_st = FPS_SCAN_ST_DONE;	// 修改状态标志为完成
		fps_st.err_st = FPS_ERR_NONE;		// 清除错误标志
		fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 复位自动搜索状态机
	}

	FPGA_DISABLE_WRITE;
#endif
}
#endif
/*************************************************************
Name:        FPS_BcchScanRun          
Description: 启动BCCH搜索
Input:       void
Return:      void
**************************************************************/
void FPS_BcchScanRun( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	fps_st.cur_mode = FPS_MODE_BCCH;	// 模式:BCCH
	fps_st.fps_run = 1;					// 启动搜索
   //fps_st.bcch_count = 0;					     // 结果清零
	if ( fps_st.fc_count > 0 )
	{
		fps_st.scan_st = FPS_SCAN_ST_BCCH;	    // 状态:搜索BCCH
		fps_st.err_st  = FPS_ERR_NONE;			// 错误状态复位
		FPGA_ENABLE_WRITE; 
		FpgaWriteRegister( FPGA_REG_RFC_SCAN_START, 1 );	// 启动BCCH扫描
		FPGA_DISABLE_WRITE;
	}
	else
	{ 
		fps_st.scan_st = FPS_SCAN_ST_DONE;	// 状态:搜索完成
		fps_st.err_st  = FPS_ERR_BCCH_RANGE;	// 错误:搜索范围不对
	}
#endif
}

/*************************************************************
Name:FPS_SetScanFc          
Description: 写入扫描频点号到FPGA中
Input: [p_mo_cfg:模块配置指针,供计算频率用]
Return: void
**************************************************************/
void FPS_TchScanRun( UINT16 bcch_fc, UINT16 time_out )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
    UINT32 reg;
	fps_st.cur_mode = FPS_MODE_TCH;	// 模式:TCH
	fps_st.tch_count = 0;		// 复位:TCH频点个数
	fps_st.edge_count = 0;		// 复位:EDGE频点个数
	pbcch_inf.valid = 0;		// 复位:PBCCH信息有效标志
	fps_st.err_st = FPS_ERR_NONE;			// 复位:错误状态
	fps_st.bcch_fc_sel = bcch_fc;			// 记录BCCH频点号
	fps_st.scan_st = FPS_SCAN_ST_TCH;		// 状态:搜索TCH
	if ( 0==time_out )
	{
		fps_st.time_out = 90;				// 超时:90秒调试时默认不可修改)
	}
	else
	{
		fps_st.time_out = time_out;		// 超时
	}
	fps_st.fps_run = 1;					// 启动搜索
		
	FPGA_ENABLE_WRITE;
	//FpgaWriteRegister(FPGA_REG_BCCH_DF, FPS_CalcFpgaFreqWord( SYS_A_FLAG, bcch_fc));	// 写TCH频点,启动搜索
	reg = FPS_CalcFpgaFreqWord( SYS_A_FLAG, bcch_fc);
	FpgaWriteRegister(FPGA_REG_BCCH_DF_1, (UINT16)(((reg>>12)&0x3FFF)|((reg&0x80000000)>>16)));	// 写TCH频点[25:12]位,启动搜索
	FpgaWriteRegister(FPGA_REG_BCCH_DF_2, (UINT16)(reg&0xFFF));	// 写TCH频点[11:0]位,启动搜索	

	FPGA_DISABLE_WRITE;
#endif
}

/*************************************************************
Name:FPS_CidScanRun          
Description: 写入扫描频点号到FPGA中
Input: [p_mo_cfg:模块配置指针,供计算频率用]
Return: void
**************************************************************/
void FPS_CidScanRun( UINT16 bcch_fc )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
    UINT32 reg;
	fps_st.cur_mode = FPS_MODE_CID;	// 模式:CID
	fps_st.bcch_fc_sel = bcch_fc;			// 记录BCCH频点号
	fps_st.scan_st = FPS_SCAN_ST_CID;		// 状态:搜索CID
	fps_st.time_out = 30;				// 超时:30秒(调试时默认不可修改)
		
	FPGA_ENABLE_WRITE;
	//FpgaWriteRegister(FPGA_REG_BCCH_DF, FPS_CalcFpgaFreqWord( SYS_A_FLAG, bcch_fc));	// 写TCH频点,启动搜索
	reg = FPS_CalcFpgaFreqWord( SYS_A_FLAG, bcch_fc);
	FpgaWriteRegister(FPGA_REG_BCCH_DF_1, (UINT16)(((reg>>12)&0x3FFF)|((reg&0x80000000)>>16)));	// 写TCH频点[25:12]位,启动搜索
	FpgaWriteRegister(FPGA_REG_BCCH_DF_2, (UINT16)(reg&0xFFF));	// 写TCH频点[11:0]位,启动搜索	

	FPGA_DISABLE_WRITE;
#endif
}


/*************************************************************
Name:FPS_ConvBcchIndex2Fc          
Description: 将BCCH搜索结果中的BCCH频点序号转换为频点号
Input: [bcch_id:BCCH频点序号]
Return: 频点号, 0xFFFF表示无效序号
**************************************************************/
UINT16 FPS_ConvBcchIndex2Fc( UINT16 bcch_id )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 count;

	count = sys_param_2b[MADD_FPS_E1].val - sys_param_2b[MADD_FPS_S1].val + 1;

	if ( bcch_id < count )
	{
		return (sys_param_2b[MADD_FPS_S1].val+bcch_id);
	}

	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		bcch_id-=count;

		count = sys_param_2b[MADD_FPS_E2].val - sys_param_2b[MADD_FPS_S2].val + 1;

		if ( bcch_id < count )
		{
			return (sys_param_2b[MADD_FPS_S2].val+bcch_id);
		}
	}

	return 0xFFFF;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FcScanStartBCCH          
Description: 启动BCCH扫描
Input: 
	force_run: 1-强制执行
	wait_time: 超时设置
Return: 结果:0-启动成功，1-正在执行BCCH扫描，2-正在执行TCH扫描，3-有错误
**************************************************************/
void FPS_AutoStartBcch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	fps_st.time_out = (fps_st.fc_count+1)*5;
	FPS_BcchScanRun();
#endif
}

/*************************************************************
Name:FPS_CompositorBcchLst          
Description: 对BCCH列表按功率值从大到小进行排序
Input: void
Return: void
**************************************************************/
void FPS_CompositorBcchLst( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	_T_FPS_BCCH_INFO bcch_tmp;
	UCHAR8 i, k;

	if ( fps_st.bcch_count < 1 )	// 只有BCCH个数超过1个才需要排序
	{
		return;
	}

	for ( i=0; i<fps_st.bcch_count-1; i++ )
	{
		for ( k=i+1; k<fps_st.bcch_count; k++ )
		{
			if ( fps_st.bcch_lst[k].power < fps_st.bcch_lst[i].power )	// 功率小的直接跳过
			{
				continue;
			}
			else if ( fps_st.bcch_lst[k].power == fps_st.bcch_lst[i].power )	// 若功率值相等
			{
				if ( fps_st.bcch_lst[k].precision <= fps_st.bcch_lst[i].precision )	// 正确率小的直接跳过
				{
					continue;
				}
			}
			// 交换两个BCCH
			bcch_tmp.fc = fps_st.bcch_lst[i].fc;
			bcch_tmp.power = fps_st.bcch_lst[i].power;
			bcch_tmp.precision = fps_st.bcch_lst[i].precision; 

			fps_st.bcch_lst[i].fc = fps_st.bcch_lst[k].fc;
			fps_st.bcch_lst[i].power = fps_st.bcch_lst[k].power;
			fps_st.bcch_lst[i].precision = fps_st.bcch_lst[k].precision; 

			fps_st.bcch_lst[k].fc = bcch_tmp.fc;
			fps_st.bcch_lst[k].power = bcch_tmp.power;
			fps_st.bcch_lst[k].precision = bcch_tmp.precision; 
			
		}
	}

#endif
}

/*************************************************************
Name:FPS_HandleBcchScan          
Description: 处理BCCH搜索结果
Input: void
Return: void
**************************************************************/
void FPS_HandleBcch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 count;	// BCCH个数
	UCHAR8 i, j;
	UINT16 tmp;
	UINT32 pow_min= 0xFFFFFFFF;
	_T_FPS_BCCH_INFO bcch_inf;

	// 初始化状态
	fps_st.err_st = FPS_ERR_BCCH_RESULT;
		
	count = FpgaReadRegister(FPGA_REG_BCCH_CNT);	// 读BCCH个数
	if ( count>fps_st.fc_count )	// BCCH个数超过总的搜索个数
	{
		return;
	}

	// 读取BCCH信息
	i = 0;
	while( count-- )
	{
		tmp = FpgaReadRegister(FPGA_REG_BCCH_INFO);	// 高8位频点序号, 低8位正确率
		bcch_inf.precision = tmp&0xFF;
		tmp>>=8;
		bcch_inf.fc = FPS_ConvBcchIndex2Fc( tmp );
		if ( bcch_inf.fc == 0xFFFF )
		{
			return;	// 无效频点序号,返回
		}
		// 48位功率,低16为舍弃,保留高32位
		bcch_inf.power = (UINT32)FpgaReadRegister(FPGA_REG_BCCH_INFO)<<16;
		bcch_inf.power |= FpgaReadRegister(FPGA_REG_BCCH_INFO);
		tmp = FpgaReadRegister(FPGA_REG_BCCH_INFO);

		if ( bcch_inf.fc == fps_st.bcch_use.fc )	// 更新当前在用的BCCH状态
		{
			fps_st.bcch_use.power = bcch_inf.power;
			fps_st.bcch_use.precision = bcch_inf.precision;
		}
		
		// 功率过小则直接丢弃
		if ( bcch_inf.power > 0 )
		{
			fps_st.bcch_lst[i].fc = bcch_inf.fc;
			fps_st.bcch_lst[i].power = bcch_inf.power;
			fps_st.bcch_lst[i].precision = bcch_inf.precision;
			if ( i<FPS_BCCH_MAX )		// 前FPS_BCCH_MAX个BCCH直接保存
			{
				if ( bcch_inf.power<pow_min ) 	// 在前几个中记录功率最小值
				{
					pow_min = bcch_inf.power;
				}
				i++;
			}
			else		// 开始比较
			{
				if ( bcch_inf.power>=pow_min ) 	// 读出的BCCH功率比已保存的BCCH列表中的某个BCCH功率强
				{
					// 查找列表中功率值最小的BCCH
					for ( j=0; j<FPS_BCCH_MAX; j++ )
					{
						if ( pow_min == fps_st.bcch_lst[j].power )		// 定位到BCCH
						{
							if ( fps_st.bcch_lst[j].power == bcch_inf.power )	// 若功率值相等
							{
								// 比较正确率
								if ( fps_st.bcch_lst[j].precision >= bcch_inf.precision )
								{
									continue;		// 读出的BCCH正确率小于列表中BCCH的正确率,不替换
								}
							}	
							// 读出的BCCH功率大于列表中BCCH的功率直接替换
							fps_st.bcch_lst[j].fc = bcch_inf.fc;
							fps_st.bcch_lst[j].power = bcch_inf.power;
							fps_st.bcch_lst[j].precision = bcch_inf.precision;
							break;
						}
					}
					if ( j<FPS_BCCH_MAX )		// 列表被更新
					{
						// 重新求列表中功率最小值
						pow_min = bcch_inf.power;
						for ( j=0; j<FPS_BCCH_MAX; j++ )
						{
							if ( fps_st.bcch_lst[j].power < pow_min )
							{
								pow_min = fps_st.bcch_lst[j].power;
							}
						}
					}
				}
			}
		}
	}

	fps_st.bcch_count = i;		// 更新BCCH个数
	fps_st.err_st = FPS_ERR_NONE;	// 设置状态
	
	// 将BCCH按功率大小排序
	FPS_CompositorBcchLst();
	
#endif	
}

/*************************************************************
Name:FPS_HandleTch          
Description: 处理TCH搜索结果
Input: void
Return: void
**************************************************************/
void FPS_HandleTch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 tmp = 0;
	UINT16 i;
	UCHAR8 tch_buf[16];
	
	for (i=0; i<16; )
	{
		tmp  = FpgaReadRegister(FPGA_REG_TCH_INFO);
		tch_buf[i++] = (UCHAR8)(tmp&0xff);
		tch_buf[i++] = (UCHAR8)(tmp>>8);
	}

	// 解码TCH
	FPS_TchDecode( tch_buf );
	fps_st.err_st = FPS_ERR_NONE;	// 设置状态
#endif	
}

/*************************************************************
Name:FPS_HandlePbcch          
Description: 处理TCH搜索结果
Input: void
Return: void
**************************************************************/
void FPS_HandlePbcch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 tmp = 0;
	UINT16 i;
	UCHAR8 pbcch_buf[20];
	
	for (i=0; i<20; )
	{
		tmp  = FpgaReadRegister(FPGA_REG_PBCCH_INFO);
		pbcch_buf[i++] = (UCHAR8)(tmp&0xff);
		pbcch_buf[i++] = (UCHAR8)(tmp>>8);
	}
	
	// 解码PBCH
	FPS_PbcchDecode( pbcch_buf );
	fps_st.err_st = FPS_ERR_NONE;	// 设置状态
#endif	
}

/*************************************************************
Name:FPS_HandleEdge          
Description: 处理TCH搜索结果
Input: void
Return: void
**************************************************************/
void FPS_HandleEdge( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 count = 0;
	UINT16 i;

	count = FpgaReadRegister( FPGA_REG_EDGE_CNT );
	for ( ; fps_st.edge_count<count; fps_st.edge_count++)
	{
		fps_st.edge_lst[fps_st.edge_count]= FpgaReadRegister(FPGA_REG_EDGE_INFO);
	}	
#endif
}

/*************************************************************
Name:FPS_GetBcchResult          
Description: 上位机获取BCCH搜索结果
Input: void
Return: void
**************************************************************/
UINT16 FPS_GetBcchResult( UCHAR8 * p_ret )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 len = 0;
	UINT16 i;
	FLOAT32 gain_in;		// 前端模拟增益 = 前端标称增益-输入滤波器增益Gcic-前端补偿增益Gcmps
	INT32 fc_power;
	UINT32 tmp;

	gain_in = CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));	// 前端补偿增益Gcmps
	gain_in = FPGA_REC_GFNOM - fpga_dgcic_a - gain_in;	// 前端模拟增益

	p_ret[len++] = fps_st.bcch_count;
	for ( i=0; i<fps_st.bcch_count; i++ )
	{
		// 频点号
		p_ret[len++] = (UCHAR8)(fps_st.bcch_lst[i].fc&0xff);
		p_ret[len++] = (UCHAR8)((fps_st.bcch_lst[i].fc>>8)&0xff);
		
		// 功率
		fc_power = (INT32)( 1000 * (CALC_POWER( fps_st.bcch_lst[i].power ) - gain_in) );	// 求输入功率dbm = AD功率-前端模拟增益G_in, x1000保留3位小数
		tmp = (UINT32)fc_power;
		p_ret[len++] = (UCHAR8)(tmp&0xff);
		p_ret[len++] = (UCHAR8)((tmp>>8)&0xff);
		p_ret[len++] = (UCHAR8)((tmp>>16)&0xff);
		p_ret[len++] = (UCHAR8)((tmp>>24)&0xff);
		
		// 误码率
		p_ret[len++] = fps_st.bcch_lst[i].precision;

		// CID小区识别码
		p_ret[len++] = (UCHAR8)(fps_st.bcch_lst[i].cid&0xff);
		p_ret[len++] = (UCHAR8)((fps_st.bcch_lst[i].cid>>8)&0xff);
	}
	
	return len;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_GetTchResult          
Description: 上位机获取TCH搜索结果
Input: void
Return: void
**************************************************************/
UINT16 FPS_GetTchResult( UCHAR8 * p_ret )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 len = 0;
	UINT16 tmp;
	UINT16 i;

	// 用来解析TCH的BCCH频点号
	tmp = fps_st.bcch_fc_sel;
	p_ret[len++] = (UCHAR8)(fps_st.bcch_fc_sel&0xff);
	p_ret[len++] = (UCHAR8)((fps_st.bcch_fc_sel>>8)&0xff);
	
	// TCH频点数量
	p_ret[len++] = fps_st.tch_count;
	// TCH频点列表
	for ( i=0; i<fps_st.tch_count; i++ )
	{
		p_ret[len++] = (UCHAR8)(fps_st.tch_lst[i]&0xff);
		p_ret[len++] = (UCHAR8)((fps_st.tch_lst[i]>>8)&0xff);
	}
	
	// EDGE频点数量
	p_ret[len++] = fps_st.edge_count;
	// EDGE频点列表
	for ( i=0; i<fps_st.edge_count; i++ )
	{
		p_ret[len++] = (UCHAR8)(fps_st.edge_lst[i]&0xff);
		p_ret[len++] = (UCHAR8)((fps_st.edge_lst[i]>>8)&0xff);
	}

	// PCCH
	p_ret[len++] = (1==pbcch_inf.valid) ? 1 : 0;
	p_ret[len++] = (1==pbcch_inf.gprs_support) ? 1 : 0;
	p_ret[len++] = (1==pbcch_inf.edge_support) ? 1 : 0;
	p_ret[len++] = (1==pbcch_inf.rfl_lst_support) ? 1 : 0;
	// RFL Count
	p_ret[len++] = pbcch_inf.rfl_count;
	// RFL List
	for ( i=0; i<pbcch_inf.rfl_count; i++ )
	{
		p_ret[len++] = pbcch_inf.rfl_lst[i];
	}
	// ARFCN mode
	p_ret[len++] = (1==pbcch_inf.arfcn_lst_mode) ? 1 : 0;
	// MA Length
	p_ret[len++] = pbcch_inf.ma_len;
	// BITMAP buf
	for ( i=0; i<(pbcch_inf.ma_len+7)/8; i++ )
	{
		p_ret[len++] = pbcch_inf.ma_bm[i];
	}
	// Gprs Arfcn Count
	p_ret[len++] = pbcch_inf.arfcn_count;
	// Gprs Arfcn List
	for ( i=0; i<(pbcch_inf.ma_len+7)/8; i++ )
	{
		p_ret[len++] = pbcch_inf.arfcn_lst[i];
	}
	// PBCCH FC
	p_ret[len++] = (1==pbcch_inf.pbcch_fc_valid) ? 1 : 0;
	p_ret[len++] = (UCHAR8)(pbcch_inf.pbcch_arfcn&0xff);
	p_ret[len++] = (UCHAR8)((pbcch_inf.pbcch_arfcn>>8)&0xff);

	return len;
	
#else
	return 0;
#endif	
}

/*************************************************************
Name:FPS_GetAutoScanStaus          
Description: 上位机获取自动扫描状态
Input: void
Return: void
**************************************************************/
UINT16 FPS_GetAutoScanStaus( UCHAR8 * p_ret )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 len = 0;
	UINT16 i;
	FLOAT32 gain_in;		// 前端模拟增益 = 前端标称增益-输入滤波器增益Gcic-前端补偿增益Gcmps
	INT32 fc_power;
	UINT32 tmp;

	if ( 0==fps_st.auto_scan_en )	// 当前处于手动搜索模式
	{
		p_ret[len++] = 3;		// 出错
		p_ret[len++] = FPS_ERR_MANUAL_MODE;	// 错误代码:模式错误
		return len;
	}
	p_ret[len++] = 0;		// 无错误

	gain_in = CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));	// 前端补偿增益Gcmps
	gain_in = FPGA_REC_GFNOM - fpga_dgcic_a - gain_in;	// 前端模拟增益

	// 自动搜索状态
	p_ret[len++] = fps_st.auto_state;
	// BCCH切换次数
	p_ret[len++] = fps_st.switch_count;
	// 自动搜索选定的BCCH频点号
	p_ret[len++] = (UCHAR8)(fps_st.bcch_use.fc&0xff);
	p_ret[len++] = (UCHAR8)((fps_st.bcch_use.fc>>8)&0xff);
	// 自动搜索选定的BCCH功率
	fc_power = (INT32)( 1000 * (CALC_POWER(fps_st.bcch_use.power) - gain_in) );	// 求输入功率dbm = AD功率-前端模拟增益G_in, x1000保留3位小数
	tmp = (UINT32)fc_power;
	p_ret[len++] = (UCHAR8)(tmp&0xff);
	p_ret[len++] = (UCHAR8)((tmp>>8)&0xff);
	p_ret[len++] = (UCHAR8)((tmp>>16)&0xff);
	p_ret[len++] = (UCHAR8)((tmp>>24)&0xff);
	// 自动搜索选定的BCCH正确率
	p_ret[len++] = fps_st.bcch_use.precision;
	// 当前搜索模式
	p_ret[len++] = ( 1==fps_st.cur_mode ) ? 1 : 0;
	// 当前搜索状态
	p_ret[len++] = fps_st.scan_st;
	// 当前搜索错误信息
	p_ret[len++] = fps_st.err_st;	

	len += FPS_GetBcchResult( p_ret+len );
	len += FPS_GetTchResult( p_ret+len );

	return len;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_SendReport          
Description: 手动扫描结束，发送扫描结果
Input: void
Return: void
**************************************************************/
void FPS_SendReport( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 * p_txbuff = sys_temp_buff;
	UINT16 tx_len=0;
	UINT16 i;
	UINT32 tmp;

	if ( (0xEE==fps_report_head[0]) && (0xEE==	fps_report_head[1]) )	// 无效消息头
	{
		return;
	}

	// 消息头
	for ( i=0; i<MSG_PKT_HEAD_SIZE; i++ )
	{
		p_txbuff[tx_len++] = fps_report_head[i];
	}
	
	// 模式
	p_txbuff[tx_len++] = fps_report.cmd_mode;
	
	// 附加模式
	p_txbuff[tx_len++] = fps_report.ext_mode;

	// 状态
	if ( FPS_ERR_NONE != fps_st.err_st )	
	{
		p_txbuff[tx_len++] = FPS_RESULT_ERROR;			// 有错误
		p_txbuff[tx_len++] = fps_st.err_st;
	}
	else
	{
		if ( FPS_SCAN_ST_DONE==fps_st.scan_st )
		{
			p_txbuff[tx_len++] = FPS_RESULT_OK;			// 无错误，扫描完成
		}
		else
		{
			p_txbuff[tx_len++] = FPS_RESULT_WORK;			// 正在扫描中
		}
		//if ( FPS_MODE_BCCH==fps_st.cur_mode )
		if ( 1==fps_report.cmd_mode )
		{
			tx_len += FPS_GetBcchResult(p_txbuff+tx_len);
		}
		else
		{
			tx_len += FPS_GetTchResult(p_txbuff+tx_len);
		}
	}
	SendMsgPkt( tx_len, p_txbuff);
#endif	
}

/*************************************************************
Name: FPS_MakeAckMsgHead          
Description: 生成应答数据包的信息头
Input: void
Return: void
**************************************************************/
void FPS_MakeAckMsgHead( UCHAR8 cmd_mode, UCHAR8 ext_mode, UCHAR8 head_len, UCHAR8 * p_head)
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 i;
	
	for ( i=0; i<head_len; i++ )
	{
		fps_report.p_ack_head[i] = *p_head++;
	}
	fps_report.cmd_mode = cmd_mode;
	fps_report.ext_mode = ext_mode;
#endif
}

/*************************************************************
Name: FPS_ResetResultParam          
Description: 复位搜索结果
Input: void
Return: void
**************************************************************/
void FPS_ResetResultParam( void )
{
	UCHAR8 i;
	CHAR8 tmp = -120;

	// 锁定的BCCH信息
	sys_param_2b[MADD_FPS_BCCH_FC_M].val = 65535;	// 锁定的BCCH, 无效
	sys_param_1b[MADD_FPS_BCCH_POW_M].val = (UCHAR8)tmp;		// 锁定的BCCH功率， -120
	// 邻区BCCH信息
	for ( i=0; i<6; i++ )
	{
		sys_param_2b[MADD_FPS_BCCH_FC_1+i].val = 65535;	// 无效BCCH
		sys_param_1b[MADD_FPS_BCCH_POW_1+i].val = (UCHAR8)tmp;		// 邻区BCCH功率
		sys_param_2b[MADD_FPS_CID_1+i].val = 0;	// 无效CID
	}
	// CA信息
	sys_param_1b[MADD_FPS_CA_COUNT].val = 0;		// 有效信道数:0
	
	for ( i=0; i<16; i++ )
	{
		sys_param_2b[MADD_FPS_CA_FC_0+i].val = 65535;		// 无效CA
	}
	// 基站信息
	sys_param_2b[MADD_FPS_CID].val = 0;
	sys_param_2b[MADD_FPS_AREA_ID].val = 0;
	sys_param_1b[MADD_FPS_BS_ID].val = 0;
	// 搜索结果状态
	sys_param_1b[MADD_FPS_BCCH_LK_ST].val = 0;		// 锁定BCCH失败
	
}

/*************************************************************
Name: FPS_SetResultToSysFc          
Description: 将结果应用到系统工作频点
Input: void
Return: void
**************************************************************/
void FPS_SetResultToSysFc( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN

#ifdef FUNC_FPS_AUTO_SET	// 定义宏则自动将搜索结果设置为工作频点号

	UINT16 fc_count;
	UINT16 i, tmp;
	UINT16 fc;
	UCHAR8 fpssaveflashflag;
	fc_count = sys_param_1b[MADD_FPS_CA_COUNT].val;		// 频点数
	
	if ( fc_count > 16 ) fc_count = 16;

	for ( i=sys_param_1b[MADD_A_CHANNEL_COUNT].val; i<MAX_CHANNEL_COUNT; i++ )
	{
		sys_param_2b[MADD_A_DL_CHANNEL1+i].val = 65535;
		sys_param_2b[MADD_A_UL_CHANNEL1+i].val = 65535;
		sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
		sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
	}

#ifdef FUNC_FPS_AVG_FP		// 定义宏则将频点按通道数对半分

	tmp = (fc_count+1)/2;

	for ( i=0; i<sys_param_1b[MADD_A_CHANNEL_COUNT].val/2; i++ )
	{
		if ( i >= tmp )		// 搜索结果最多支持16通道，若超出则关闭通道使能
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
			continue;
		}
		
		// 取得搜索结果的CA频点号
		fc = sys_param_2b[MADD_FPS_CA_FC_0+i].val;
		// A段频点号，与当前工作信道号不一致则重新设置
		if ( (fc != sys_param_2b[MADD_A_DL_CHANNEL1+i].val) || (fc != sys_param_2b[MADD_A_UL_CHANNEL1+i].val) )
		{
			sys_param_2b[MADD_A_DL_CHANNEL1+i].val = fc;
			sys_param_2b[MADD_A_UL_CHANNEL1+i].val = fc;
			module_param_chg_flag |= PCHG_A_CHANNEL;
			fpssaveflashflag=1;
		}
		// 频点使能
		if ( 65535!=fc )
		{
			if ( (0==sys_param_1b[MADD_A_DCH_EN1+i].val) || (0==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 1;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 1;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
		else
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
	}

	for ( i=sys_param_1b[MADD_A_CHANNEL_COUNT].val/2; i<sys_param_1b[MADD_A_CHANNEL_COUNT].val; i++, tmp++ )
	{
		if ( tmp >= fc_count )		// 搜索结果最多支持16通道，若超出则关闭通道使能
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
			continue;
		}
		
		// 取得搜索结果的CA频点号
		fc = sys_param_2b[MADD_FPS_CA_FC_0+tmp].val;
		// A段频点号，与当前工作信道号不一致则重新设置
		if ( (fc != sys_param_2b[MADD_A_DL_CHANNEL1+i].val) || (fc != sys_param_2b[MADD_A_UL_CHANNEL1+i].val) )
		{
			sys_param_2b[MADD_A_DL_CHANNEL1+i].val = fc;
			sys_param_2b[MADD_A_UL_CHANNEL1+i].val = fc;
			module_param_chg_flag |= PCHG_A_CHANNEL;
			fpssaveflashflag=1;
		}
		// 频点使能
		if ( 65535!=fc )
		{
			if ( (0==sys_param_1b[MADD_A_DCH_EN1+i].val) || (0==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 1;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 1;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
		else
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
	}

	if ( 0 != (module_param_chg_flag&PCHG_A_CHANNEL) )	// A段频点设置有改变,更改B段频点
	{
		for ( i=0; i<MAX_CHANNEL_COUNT; i++ )
		{
			sys_param_2b[MADD_B_DL_CHANNEL1+i].val = sys_param_2b[MADD_A_DL_CHANNEL1+i].val;
			sys_param_2b[MADD_B_UL_CHANNEL1+i].val = sys_param_2b[MADD_A_UL_CHANNEL1+i].val;
			sys_param_1b[MADD_B_DCH_EN1+i].val = sys_param_1b[MADD_A_DCH_EN1+i].val;
			sys_param_1b[MADD_B_UCH_EN1+i].val = sys_param_1b[MADD_A_UCH_EN1+i].val;
		}
		//CheckChannelSetB();  edasion
		module_param_chg_flag |= PCHG_B_CHANNEL;
		fpssaveflashflag=1;
	}

#else //11

	for ( i=0; i<sys_param_1b[MADD_A_CHANNEL_COUNT].val; i++ )
	{
		if ( i>= fc_count )		// 搜索结果最多支持16通道，若超出则关闭通道使能
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
			continue;
		}
		
		// 取得搜索结果的CA频点号
		fc = sys_param_2b[MADD_FPS_CA_FC_0+i].val;
		// A段频点号，与当前工作信道号不一致则重新设置
		if ( (fc != sys_param_2b[MADD_A_DL_CHANNEL1+i].val) || (fc != sys_param_2b[MADD_A_UL_CHANNEL1+i].val) )
		{
			sys_param_2b[MADD_A_DL_CHANNEL1+i].val = fc;
			sys_param_2b[MADD_A_UL_CHANNEL1+i].val = fc;
			module_param_chg_flag |= PCHG_A_CHANNEL;
			fpssaveflashflag=1;
		}
		// 频点使能
		if ( 65535!=fc )
		{
			if ( (0==sys_param_1b[MADD_A_DCH_EN1+i].val) || (0==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 1;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 1;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
		else
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// 使能状态改变
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
	}

#if ( B_NETWORK_TYPE==NET_DIVE )	// B段分集，采用同样设置
	if ( 0 != (module_param_chg_flag&PCHG_A_CHANNEL) )	// A段频点设置有改变
	{
		for ( i=0; i<MAX_CHANNEL_COUNT; i++ )
		{
			sys_param_2b[MADD_B_DL_CHANNEL1+i].val = sys_param_2b[MADD_A_DL_CHANNEL1+i].val;
			sys_param_2b[MADD_B_UL_CHANNEL1+i].val = sys_param_2b[MADD_A_UL_CHANNEL1+i].val;
			sys_param_1b[MADD_B_DCH_EN1+i].val = sys_param_1b[MADD_A_DCH_EN1+i].val;
			sys_param_1b[MADD_B_UCH_EN1+i].val = sys_param_1b[MADD_A_UCH_EN1+i].val;
		}
		//CheckChannelSetB();  edasion
		module_param_chg_flag |= PCHG_B_CHANNEL;
		fpssaveflashflag=1;
	}
#endif	// #( B_NETWORK_TYPE==NET_DIVE )

#endif	// #FUNC_FPS_AVG_FP
	if(0x01==fpssaveflashflag)
	{
		sys_work_info |= SYSTEM_FLAG_SET_RE_SFC;	// 置标志位,广播设置RE的频点		
		SaveSysParamToFlash();
	}

//	sys_work_info |= SYSTEM_FLAG_SET_RE_SFC;	// 置标志位,广播设置RE的频点

#endif	// #FUNC_FPS_AUTO_SET

#endif	// #FUNC_FREQ_POINT_SEARCH_EN
}

/*************************************************************
Name: FPS_SaveResultToSysParam          
Description: 保存搜索结果到参数表中
Input: void
Return: void
**************************************************************/
void FPS_SaveResultToSysParam( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UINT16 fc_set[16];
	UCHAR8 fc_id=0;
	UCHAR8 i, j;
	FLOAT32 gain_in;		// 前端模拟增益 = 前端标称增益-输入滤波器增益Gcic-前端补偿增益Gcmps
	INT32 fc_power;
	CHAR8 tmp;
	
	gain_in = CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));	// 前端补偿增益Gcmps
	gain_in = FPGA_REC_GFNOM - fpga_dgcic_a - gain_in;	// 前端模拟增益

	TRACE_INFO("fps_st.tch_count=%d\r\n",fps_st.tch_count );
	
	for ( i=0; (i<fps_st.tch_count)&&(fc_id<sys_param_1b[MADD_A_CHANNEL_COUNT].val); i++ )
	{
		fc_set[fc_id++] = fps_st.tch_lst[i];
		TRACE_INFO("fc_id0 = %d\r\n",fc_id);  
		TRACE_INFO("fps_st.tch_lst[%d]= %d\r\n",i,fps_st.tch_lst[i] );
	}

	if (1==pbcch_inf.valid)	// PBCCH信息有效
	{
		if ( (1==pbcch_inf.pbcch_support)&&(1==pbcch_inf.pbcch_fc_valid) )		// 有PBCCH频点
		{
			for ( i=0; i<fc_id; i++ )		// 查找有无重复
			{
				if ( fc_set[i] == pbcch_inf.pbcch_arfcn )
				{
					break;
				}
			}
			if ( i>=fc_id )		// 无重复则加入到频点列表中
			{
				fc_set[fc_id++] = pbcch_inf.pbcch_arfcn;
				TRACE_INFO("fc_id1 = %d\r\n",fc_id);  
			}
		}

		if ( 1==pbcch_inf.edge_support )	// PBCCH表示当前支持EDGE频点
		{
			for ( i=0; (i<fps_st.edge_count)&&(fc_id<sys_param_1b[MADD_A_CHANNEL_COUNT].val); i++ )	// 处理EDGE频点
			{
				for ( j=0; j<fc_id; j++ )	// 查找有无重复
				{
					if ( fc_set[j] == fps_st.edge_lst[i] )
					{
						break;
					}
				}
				if ( j>=fc_id )		// 无重复则加入到频点列表中
				{
					fc_set[fc_id++] = fps_st.edge_lst[i];
					TRACE_INFO("fc_id2 = %d\r\n",fc_id);  
				}
			}
		}
	}

	// 将频点信息更新到搜索结果参数中
	sys_param_2b[MADD_FPS_BCCH_FC_M].val = fps_st.bcch_use.fc;	// 锁定的BCCH
	fc_power = (INT32)(CALC_POWER( fps_st.bcch_use.power ) - gain_in);	// 求输入功率dbm = AD功率-前端模拟增益G_in
	if ( fc_power < -120)
	{
		tmp = -120;
	}
	else
	{
		tmp = fc_power;
	}
	sys_param_1b[MADD_FPS_BCCH_POW_M].val = (UCHAR8)tmp;		// 锁定的BCCH功率
	// 邻区BCCH信息
	for ( i=0, j=0; (i<FPS_BCCH_MAX)&&(j<6); i++ )
	{
		tmp = -120;		// 初始化功率值为-120dbm
		if ( i<fps_st.bcch_count)
		{
			if ( fps_st.bcch_lst[i].fc == fps_st.bcch_use.fc )	continue;	// 列表BCCH与当前在用的BCCH一致，不是邻区BCCH
			
			sys_param_2b[MADD_FPS_BCCH_FC_1+j].val = fps_st.bcch_lst[i].fc;	// 搜索到的邻区BCCH
			sys_param_2b[MADD_FPS_CID_1+j].val = fps_st.bcch_lst[i].cid;	// 邻区BCCH对应的CID
			fc_power = (INT32)(CALC_POWER( fps_st.bcch_lst[i].power ) - gain_in);	// 求输入功率dbm = AD功率-前端模拟增益G_in
			if ( fc_power >= -120)
			{
				tmp = fc_power;	// 功率值高于-120dbm才保存，防止数据溢出
			}
			sys_param_1b[MADD_FPS_BCCH_POW_1+j].val = (UCHAR8)tmp;		// 邻区BCCH功率
		}
		else
		{
			sys_param_2b[MADD_FPS_BCCH_FC_1+j].val = 65535;	// 无效BCCH
			sys_param_2b[MADD_FPS_CID_1+j].val = 0;				// 邻区BCCH对应的CID无效
			sys_param_1b[MADD_FPS_BCCH_POW_1+j].val = (UCHAR8)tmp;		// 邻区BCCH功率
		}
		j++;		// 邻小区BCCH个数+1
	}
	// CA信息
	sys_param_1b[MADD_FPS_CA_COUNT].val = fc_id;		// 有效信道数
	
	TRACE_INFO("fc_id3s = %d\r\n",fc_id);  
	
	  
	for ( i=0; i<16; i++ )  
	{
		if ( i<fc_id)
		{
			sys_param_2b[MADD_FPS_CA_FC_0+i].val = fc_set[i];
		}
		else
		{
			sys_param_2b[MADD_FPS_CA_FC_0+i].val = 65535;		// 无效CA
		}
	}
	sys_param_1b[MADD_FPS_BCCH_LK_ST].val = 1;		// 锁定BCCH成功

	FPS_SetResultToSysFc();
#endif
}

/*************************************************************
Name: FPS_AutoChkChangeBcch          
Description: 自动搜索时,检查是否需要更换当前在用的BCCH,根据功率门限判断
Input: void
Return: FALSE-不需要更换BCCH, TRUE-需要更换BCCH
**************************************************************/
BOOL FPS_AutoChkChangeBcch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 i;
	CHAR8 switch_thd;
	FLOAT32 fc_power_use, fc_power_scan;
	
	for ( i=0; i<fps_st.bcch_count; i++ )
	{
		if ( fps_st.bcch_use.fc == fps_st.bcch_lst[i].fc )
		{
			break;
		}
	}
	if ( i>=fps_st.bcch_count )	// 遍历完整个新的BCCH列表,都没有当前在用的BCCH频点,需要更换BCCH
	{
		return b_TRUE;		// 返回TRUE, 更换BCCH
	}

	if ( 0==i )	// 当前在用的BCCH频点是功率最强的, 不需要更换
	{
		return b_FALSE;		// 返回FALSE, 不需更换BCCH
	}

	// 当前BCCH功率不是最强的, 比较功率差值
	fc_power_use = CALC_POWER( fps_st.bcch_use.power );
	fc_power_scan = CALC_POWER( fps_st.bcch_lst[0].power );
	
	if ( fc_power_use>fc_power_scan )	// 在用BCCH功率比搜到的大,不需切换
	{
		return b_FALSE;
	}
	
//	switch_thd = (CHAR8)sys_param_1b[MADD_FPS_SWITCH_THD].val;		// 读取切换门限
	switch_thd = 3;		// 固定切换门限为3db
	if ( (fc_power_scan-fc_power_use)>switch_thd )	// 相差超过门限值则切换
	{
		return b_TRUE;		// 返回TRUE, 更换BCCH
	}
	else
	{
		return b_FALSE;		// 返回FALSE, 不需更换BCCH
	}
	
#else
	return b_FALSE;
#endif	
}

/*************************************************************
Name: FPS_HandleAutoScan          
Description: 频点搜索主程序
Input: void
Return: void
**************************************************************/
void FPS_HandleAutoScan( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	static UCHAR8 fail_count = 0;
	static UCHAR8 switch_chk = 0;
	static UCHAR8 bcch_index = 0;			// 搜索的BCCH序号
	UCHAR8 i;
	UINT16 tmp;
	
	if ( 0==fps_st.auto_scan_en )
	{
		return;
	}
	WTD_CLR;
	switch ( fps_st.auto_state )
	{
	case FPS_AUTO_ST_NEW_SCAN:
		FPS_ResetResultParam();	// 复位搜索结果
		FPS_AutoStartBcch();
		fail_count = 0;
		fps_st.auto_state = FPS_AUTO_ST_BCCH;
		break;

	case FPS_AUTO_ST_BCCH:
		if ( (0==fps_st.bcch_count)||(FPS_ERR_NONE!=fps_st.err_st) )	// 有错误或找不到BCCH频点
		{
			FPS_AutoStartBcch();		// 重新搜索
		}
		else		// BCCH搜索完成
		{
			fail_count = 0;
			bcch_index = 0;		// 复位BCCH序号,从功率最大的第一个BCCH开始
			
			if ( 65535!=sys_param_2b[MADD_FPS_BCCH_LK_SET].val )		// 使用BCCH锁频功能
			{
				for ( bcch_index=0; bcch_index<fps_st.bcch_count; bcch_index++ )	// 在结果列表中查找目标BCCH
				{
					if ( sys_param_2b[MADD_FPS_BCCH_LK_SET].val == fps_st.bcch_lst[bcch_index].fc )
					{
						break;	// 找到则跳出循环
					}
				}
				
				if ( bcch_index >= fps_st.bcch_count )	// 在BCCH结果列表中找不到指定锁频的BCCH
				{
					fps_st.auto_state = FPS_AUTO_ST_BCCH;
					FPS_AutoStartBcch();		// 重新搜索BCCH
					break;
				}
			}

			if ( 0!=sys_param_2b[MADD_FPS_CID_LK_SET].val )		// 使用CID锁频功能
			{
				if ( 65535!=sys_param_2b[MADD_FPS_BCCH_LK_SET].val )		// 使用BCCH锁频功能
				{
					if ( fps_st.bcch_lst[bcch_index].cid != sys_param_2b[MADD_FPS_CID_LK_SET].val )	// 锁定的BCCH对应的CID值与目标CID值不匹配
					{
						fps_st.auto_state = FPS_AUTO_ST_BCCH;
						FPS_AutoStartBcch();		// 重新搜索BCCH
						break;
					}
				}
				else
				{
					for ( bcch_index=0; bcch_index<fps_st.bcch_count; bcch_index++ )	// 在结果列表中查找目标CID
					{
						if ( sys_param_2b[MADD_FPS_CID_LK_SET].val == fps_st.bcch_lst[bcch_index].cid )
						{
							break;	// 找到则跳出循环
						}
					}

					if ( bcch_index >= fps_st.bcch_count )	// 在结果列表中找不到指定锁频的CID
					{
						fps_st.auto_state = FPS_AUTO_ST_BCCH;
						FPS_AutoStartBcch();		// 重新搜索BCCH
						break;
					}
				}
			}

			FPS_TchScanRun(fps_st.bcch_lst[bcch_index].fc, 60);		// 采用选中频点启动TCH搜索
			fps_st.auto_state = FPS_AUTO_ST_TCH;	// 状态转变: 搜索TCH
		}
		break;

#if 0
	case FPS_AUTO_ST_BCCH:
		if ( (0==fps_st.bcch_count)||(FPS_ERR_NONE!=fps_st.err_st) )	// 有错误或找不到BCCH频点
		{
			FPS_AutoStartBcch();		// 重新搜索
		}
		else		// BCCH搜索完成
		{
			fail_count = 0;
			bcch_index = 0;		// 复位BCCH序号,从功率最大的第一个BCCH开始
			
			FPS_CidScanRun(fps_st.bcch_lst[bcch_index].fc);	// 采用选中频点启动TCH_CID搜索
			fps_st.auto_state = FPS_AUTO_ST_SCAN_CID;		// 状态转变: 搜索CID
		}
		break;

	case FPS_AUTO_ST_SCAN_CID:		// 解析CID
		fps_st.time_out--;
		if ( 0==(BM_SCAN_AREA_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// 搜索未完成
		{
			if ( fps_st.time_out>0 )	// 等待超时结束
			{
				break;
			}
			else		// 超时
			{
				fps_st.bcch_lst[bcch_index].cid = 0;		// CID无效
			}
		}
		else		// CID解析完成
		{
			fps_st.bcch_lst[bcch_index].cid = FpgaReadRegister( FPGA_REG_AREA_INFO );	// 读取小区CID信息
		}
		
		bcch_index++;	// 切换下一个BCCH
		if ( bcch_index < fps_st.bcch_count )	
		{
			FPS_CidScanRun(fps_st.bcch_lst[bcch_index].fc);		// 搜索下一个BCCH的CID信息
			break;
		}

		// BCCH列表中的CID全部遍历完成
		bcch_index = 0;	// 默认采用功率最大的BCCH
		
		if ( 65535!=sys_param_2b[MADD_FPS_BCCH_LK_SET].val )		// 使用BCCH锁频功能
		{
			for ( bcch_index=0; bcch_index<fps_st.bcch_count; bcch_index++ )	// 在结果列表中查找目标BCCH
			{
				if ( sys_param_2b[MADD_FPS_BCCH_LK_SET].val == fps_st.bcch_lst[bcch_index].fc )
				{
					break;	// 找到则跳出循环
				}
			}
			
			if ( bcch_index >= fps_st.bcch_count )	// 在BCCH结果列表中找不到指定锁频的BCCH
			{
				fps_st.auto_state = FPS_AUTO_ST_BCCH;
				FPS_AutoStartBcch();		// 重新搜索BCCH
				break;
			}
		}

		if ( 0!=sys_param_2b[MADD_FPS_CID_LK_SET].val )		// 使用CID锁频功能
		{
			if ( 65535!=sys_param_2b[MADD_FPS_BCCH_LK_SET].val )		// 使用BCCH锁频功能
			{
				if ( fps_st.bcch_lst[bcch_index].cid != sys_param_2b[MADD_FPS_CID_LK_SET].val )	// 锁定的BCCH对应的CID值与目标CID值不匹配
				{
					fps_st.auto_state = FPS_AUTO_ST_BCCH;
					FPS_AutoStartBcch();		// 重新搜索BCCH
					break;
				}
			}
			else
			{
				for ( bcch_index=0; bcch_index<fps_st.bcch_count; bcch_index++ )	// 在结果列表中查找目标CID
				{
					if ( sys_param_2b[MADD_FPS_CID_LK_SET].val == fps_st.bcch_lst[bcch_index].cid )
					{
						break;	// 找到则跳出循环
					}
				}

				if ( bcch_index >= fps_st.bcch_count )	// 在结果列表中找不到指定锁频的CID
				{
					fps_st.auto_state = FPS_AUTO_ST_BCCH;
					FPS_AutoStartBcch();		// 重新搜索BCCH
					break;
				}
			}
		}

		FPS_TchScanRun(fps_st.bcch_lst[bcch_index].fc, 0);		// 采用选中频点启动TCH搜索
		fps_st.auto_state = FPS_AUTO_ST_TCH;	// 状态转变: 搜索TCH
		break;
#endif

	case FPS_AUTO_ST_TCH:
		if ( (FPS_ERR_NONE==fps_st.err_st)&&(fps_st.tch_count>0) )	// TCH搜索成功完成
		{
			fail_count = 0;
			fps_st.switch_count++;	// BCCH切换计数累加
			// 记录当前锁定的BCCH信息
			fps_st.bcch_use.fc = fps_st.bcch_lst[bcch_index].fc;
			fps_st.bcch_use.power = fps_st.bcch_lst[bcch_index].power;
			fps_st.bcch_use.precision = fps_st.bcch_lst[bcch_index].precision;
			// 设置频点
			FPS_SaveResultToSysParam();	
			// 重新启动BCCH搜索,反复检测
			fps_st.auto_state = FPS_AUTO_ST_CHK_BCCH;
			switch_chk = 0;
			FPS_AutoStartBcch();	
		}
		else		// TCH搜索失败
		{
			fail_count++;
			if ( fail_count<3 )		// 重试3次,不成功则跳过此BCCH
			{
				FPS_TchScanRun(fps_st.bcch_lst[bcch_index].fc, 0);	// 重新搜索
			}
			else
			{
				if ( sys_param_2b[MADD_FPS_CID_LK_SET].val != 0 )		// 已启用CID锁定功能,解析TCH失败则重新搜索BCCH
				{
					fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 清除状态,重新搜索
					break;
				}

				if ( sys_param_2b[MADD_FPS_BCCH_LK_SET].val != 65535 )	// 已启用锁频功能,解析TCH失败则重新搜索BCCH
				{
					fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 清除状态,重新搜索
					break;
				}
				
				bcch_index++;	// 切换到下一个BCCH进行解析
				if ( bcch_index >= fps_st.bcch_count )	// 列表中的BCCH都遍历一次,没有一个可以解析TCH的,重新搜索BCCH
				{
					fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 清除状态,重新搜索
				}
				else		
				{
					FPS_TchScanRun( fps_st.bcch_lst[bcch_index].fc, 60 );	// 重新搜索
				}
			}
		}
		break;

	case FPS_AUTO_ST_CHK_BCCH:
		if (FPS_ERR_NONE==fps_st.err_st)	// BCCH搜索无错误完成
		{
			fail_count = 0;	// 清零错误计数
			
			for ( i=0; i<fps_st.bcch_count; i++ )		// 在当前BCCH搜索结果列表中查找正在使用的BCCH
			{
				if ( fps_st.bcch_lst[i].fc == fps_st.bcch_use.fc )	// 在当前BCCH列表中找到正在用的BCCH
				{
					break;	// 跳出循环，解析BCCH
				}
			}

			if ( i<fps_st.bcch_count )	// 找到正在使用的BCCH，启动解析TCH
			{
				fps_st.auto_state = FPS_AUTO_ST_CHK_TCH;	// 状态机->重新解析业务信道
				FPS_TchScanRun( fps_st.bcch_use.fc, 60 );	// 解析业务信道
				break;			// 跳出
			}
		}
		// BCCH搜索出错处理
		fail_count++;		// 错误计数累加
		if ( fail_count > 3 )		// 连续3次搜索BCCH失败
		{
			fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 清除状态,重新搜索
		}
		else
		{
			FPS_AutoStartBcch();		// 有错误或找不到BCCH频点,重新搜索
		}
		break;

	case FPS_AUTO_ST_CHK_TCH:
		if ( (FPS_ERR_NONE==fps_st.err_st)&&(fps_st.tch_count>0) )	// TCH搜索成功完成
		{
			fail_count = 0;	// 清零错误计数
			
			FPS_SaveResultToSysParam();		// 更新业务频点信息

			tmp = 0;
			if ( 0!=sys_param_2b[MADD_FPS_CID_LK_SET].val )	// 启用CID锁定功能
			{
				if ( sys_param_2b[MADD_FPS_CID].val != sys_param_2b[MADD_FPS_CID_LK_SET].val )	// 当前BCCH的CID与目标CID不一致
				{
					tmp = 1;			// 设置需要切换标志
				}
			}
			else		// 没有启用CID锁定功能
			{
				if (65535==sys_param_2b[MADD_FPS_BCCH_LK_SET].val)		// 没启用BCCH锁频功能, 根据功率判断是否需要切换BCCH
				{
					if ( b_TRUE == FPS_AutoChkChangeBcch() )		// 需要切换到功率更大的BCCH
					{
						tmp = 1;		// 设置需要切换标志
					}
				}
			}

			if ( 0==tmp )		// 搜索结果判断不需要切换BCCH
			{
				switch_chk = 0;	// 清除BCCH切换需求计数值
			}
			else		// 搜索结果判断需要切换BCCH
			{
				switch_chk++;	// 需要切换计数+1
			}
			
			if ( switch_chk > 3 )	// 连续3次检测结果都是需要切换, 则复位状态机, 准备切换
			{
				fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 清除状态,重新搜索
			}
			else		// 不切换BCCH, 重新启动BCCH搜索,反复检测
			{
				fps_st.auto_state = FPS_AUTO_ST_CHK_BCCH;
				FPS_AutoStartBcch();	
			}
		}
		else		// TCH搜索失败
		{
			fail_count++;
			if ( fail_count<3 )		// 重试3次,不成功则重新开始BCCH搜索
			{
				FPS_TchScanRun( fps_st.bcch_use.fc, 0 );	// 重新搜索
			}
			else
			{
				fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 清除状态,重新搜索
			}
		}
		break;

	case FPS_AUTO_ERR_RANGE:
		break;

	default:
		fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 未知状态,重新搜索
	}

#endif	
}

/*************************************************************
Name:FPS_BcchFunc          
Description: BCCH搜索主程序
Input: void
Return: void
**************************************************************/
void FPS_BcchFunc( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	static UCHAR8 bcch_index;
	UINT32 fpga_fw;
	WTD_CLR;
	switch( fps_st.scan_st )
	{
	case FPS_SCAN_ST_BCCH:
		if ( 0!=(BM_SCAN_BCCH_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )		// 判断BCCH搜索是否完成
		{
			FPS_HandleBcch();
			if ( fps_st.bcch_count>0 )
			{
				fps_st.scan_st = FPS_SCAN_ST_CID;
				bcch_index = 0;
				// 写频点,启动CID搜索
				fpga_fw = FPS_CalcFpgaFreqWord(SYS_A_FLAG, fps_st.bcch_lst[bcch_index].fc);
				FPGA_ENABLE_WRITE;
				//FpgaWriteRegister(FPGA_REG_BCCH_DF, fpga_fw );	
	            FpgaWriteRegister(FPGA_REG_BCCH_DF_1, (UINT16)(((fpga_fw>>12)&0x3FFF)|((fpga_fw&0x80000000)>>16)));// 写频点[25:12]位,启动搜索
	            FpgaWriteRegister(FPGA_REG_BCCH_DF_2, (UINT16)(fpga_fw&0xFFF));	// 写频点[11:0]位,启动搜索				
				FPGA_DISABLE_WRITE;
				fps_st.time_out = 30;				// 超时:30秒(调试时默认不可修改)
			}
			else
			{
				fps_st.scan_st = FPS_SCAN_ST_DONE;
			}
		}
		else
		{
			if ( fps_st.time_out>0 )
			{
				fps_st.time_out--;
				return;
			}
			else
			{
				fps_st.bcch_count = 0;
				fps_st.err_st = FPS_ERR_BCCH_TIMEOUT;
				fps_st.scan_st = FPS_SCAN_ST_DONE;
			}
		}
		break;

	case FPS_SCAN_ST_CID:
		if ( 0==(BM_SCAN_AREA_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// 搜索未完成
		{
			if ( fps_st.time_out>0 )	// 等待超时结束
			{
				fps_st.time_out--;
				break;
			}
			else		// 超时
			{
				fps_st.bcch_lst[bcch_index].cid = 0;		// CID无效
			}
		}
		else		// CID解析完成
		{
			fps_st.bcch_lst[bcch_index].cid = FpgaReadRegister( FPGA_REG_AREA_INFO );	// 读取小区CID信息
			FpgaReadRegister(FPGA_REG_AREA_INFO);		// 空读2次
			FpgaReadRegister(FPGA_REG_AREA_INFO);
		}
		
		bcch_index++;	// 切换下一个BCCH
		if ( bcch_index < fps_st.bcch_count )	
		{
			// 搜索下一个BCCH的CID信息
			fpga_fw = FPS_CalcFpgaFreqWord(SYS_A_FLAG, fps_st.bcch_lst[bcch_index].fc);
			FPGA_ENABLE_WRITE;
			//FpgaWriteRegister( FPGA_REG_BCCH_DF, fpga_fw );// 写频点,启动搜索
			FpgaWriteRegister(FPGA_REG_BCCH_DF_1, (UINT16)(((fpga_fw>>12)&0x3FFF)|((fpga_fw&0x80000000)>>16)));// 写频点[25:12]位,启动搜索
	        FpgaWriteRegister(FPGA_REG_BCCH_DF_2, (UINT16)(fpga_fw&0xFFF));	// 写频点[11:0]位,启动搜索
			FPGA_DISABLE_WRITE;
			fps_st.time_out = 30;				// 超时:30秒(调试时默认不可修改)
		}
		else		// BCCH列表的CID全部搜索完成，清除无效的bcch信息
		{	
			for ( ; bcch_index<FPS_BCCH_MAX; bcch_index++ )
			{
				fps_st.bcch_lst[bcch_index].fc = 65535;
				fps_st.bcch_lst[bcch_index].cid = 0;
			}
			fps_st.scan_st = FPS_SCAN_ST_DONE;
		}
		break;
		
	case FPS_SCAN_ST_DONE:
		if ( 0==fps_st.auto_scan_en )	// 非自动模式, 上报搜索结果
		{
			FPS_SendReport();
			fps_report_head[0] = 0xEE;
			fps_report_head[1] = 0xEE;
		}
		fps_st.fps_run = 0;
		break;

	default:
		fps_st.scan_st = FPS_SCAN_ST_DONE;
		fps_st.fps_run = 0;
	}
#endif
}

/*************************************************************
Name:FPS_TchFunc          
Description: TCH搜索主程序
Input: void
Return: void
**************************************************************/
void FPS_TchFunc( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	UCHAR8 tmp;
	UCHAR8 report_flag = 0;

	if ( fps_st.time_out>0 )	// 倒计时
	{
		fps_st.time_out--;
	}

	switch( fps_st.scan_st )
	{
	case FPS_SCAN_ST_TCH:
		if ( 0!=(BM_SCAN_TCH_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )		// 判断TCH搜索是否完成
		{
			FPS_HandleTch();
			fps_st.scan_st = FPS_SCAN_ST_PBCCH;
			if ( 0==fps_st.auto_scan_en )	// 非自动模式, 上报搜索结果
			{
				FPS_SendReport();
			}
		}
		else
		{
			if ( 0==fps_st.time_out )		// 超时, 解析TCH出错
			{
				fps_st.err_st = FPS_ERR_TCH_TIMEOUT;
			}
		}
		break;

	case FPS_SCAN_ST_PBCCH:
		if ( 0!=(BM_SCAN_PBCCH_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )		// 判断PBCCH搜索是否完成
		{
			FPS_HandlePbcch();
			fps_st.scan_st = FPS_SCAN_ST_EDGE;	// PBCCH解码完成,转到EDGE查询状态
			if ( 0==fps_st.auto_scan_en )	// 非自动模式, 上报搜索结果
			{
				FPS_SendReport();
			}
			break;
		}

	case FPS_SCAN_ST_EDGE:
		if ( 0!=(BM_SCAN_EDGE_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// 查看是否有搜索到EDGE频点
		{
			tmp = fps_st.edge_count;
			FPS_HandleEdge();
			if ( 0==fps_st.auto_scan_en )	// 非自动模式, 上报搜索结果
			{
				if ( tmp != fps_st.edge_count )	// 有新的EDGE频点
				{
					FPS_SendReport();
				}
			}
		}
		break;
		
	default:
		fps_st.scan_st = FPS_SCAN_ST_DONE;
	}

	if ( 0==fps_st.time_out )	// 载波业务信道搜索时间结束
	{
		// 读取EDGE频点信息
		if ( 0!=(BM_SCAN_EDGE_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// 查看是否有搜索到EDGE频点
		{
			FPS_HandleEdge();
		}
		
		if ( 0!=(BM_SCAN_AREA_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// 读取到小区信息,更新参数
		{
			sys_param_2b[MADD_FPS_CID].val = FpgaReadRegister( FPGA_REG_AREA_INFO );
			sys_param_2b[MADD_FPS_AREA_ID].val = FpgaReadRegister(FPGA_REG_AREA_INFO);
			sys_param_1b[MADD_FPS_BS_ID].val = (UCHAR8)(0xFF & FpgaReadRegister(FPGA_REG_AREA_INFO));
		}
		else
		{
			sys_param_2b[MADD_FPS_CID].val = 0;
			sys_param_2b[MADD_FPS_AREA_ID].val = 0;
			sys_param_1b[MADD_FPS_BS_ID].val = 0;
		}
		fps_st.scan_st = FPS_SCAN_ST_DONE;
	}

	if ( FPS_SCAN_ST_DONE==fps_st.scan_st )
	{
		if ( 0==fps_st.auto_scan_en )	// 非自动模式, 上报搜索结果
		{
			FPS_SendReport();
			fps_report_head[0] = 0xEE;
			fps_report_head[1] = 0xEE;
		}
		fps_st.fps_run = 0;
	}
#endif		
}

/*************************************************************
Name:FcScanStartBCCH          
Description: 启动BCCH扫描
Input: [force_run: 1-强制执行] [wait_time: 超时设置] [wait_time:超时时间]
Return: 结果:0-启动成功，1-正在执行BCCH扫描，2-正在执行TCH扫描，3-有错误
**************************************************************/
UCHAR8 FPS_ManualStartBcch( UCHAR8 force_run, UINT16 wait_time )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	if ( 1==fps_st.auto_scan_en )
	{
		fps_st.err_st = FPS_ERR_IN_AUTO_MODE;
		FPS_SendReport();
		return 0;
	}
	
	if ( (0!=fps_st.fps_run)&&(0==force_run) )	// 当前正在扫描,非强制执行
	{
		if ( FPS_MODE_BCCH == fps_st.cur_mode )
		{
			fps_st.err_st = FPS_ERR_BUSY_IN_BCCH;
		}
		else if ( FPS_MODE_TCH == fps_st.cur_mode )
		{
			fps_st.err_st = FPS_ERR_BUSY_IN_TCH;
		}
		FPS_SendReport();
		return 0;
	}

	fps_st.time_out = ( 0==wait_time ) ? (fps_st.fc_count+1)*5 : wait_time;

	FPS_BcchScanRun();

	return FPS_ERR_NONE;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_ManualStartTch          
Description: 启动TCH扫描
Input: [force_run: 1-强制执行] [bcch_fc: 频点号] [wait_time:超时时间]
Return: 结果:0-启动成功，1-正在执行BCCH扫描，2-正在执行TCH扫描，3-有错误
**************************************************************/
UCHAR8 FPS_ManualStartTch(UINT16 bcch_fc, UCHAR8 force_run, UINT16 wait_time )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	if ( 1==fps_st.auto_scan_en )
	{
		fps_st.err_st = FPS_ERR_IN_AUTO_MODE;
		FPS_SendReport();
		return 0;
	}

	if ( (0!=fps_st.fps_run)&&(0==force_run) )	// 当前正在扫描,非强制执行
	{
		if ( FPS_MODE_BCCH == fps_st.cur_mode )
		{
			fps_st.err_st = FPS_ERR_BUSY_IN_BCCH;
		}
		else if ( FPS_MODE_TCH == fps_st.cur_mode )
		{
			fps_st.err_st = FPS_ERR_BUSY_IN_TCH;
		}
		FPS_SendReport();
		return 0;
	}

	if ( ( (bcch_fc<sys_param_2b[MADD_FPS_S1].val) || (bcch_fc>sys_param_2b[MADD_FPS_E1].val) )
		&& ( (bcch_fc<sys_param_2b[MADD_FPS_S2].val) || (bcch_fc>sys_param_2b[MADD_FPS_E2].val) ) )
	{
		fps_st.err_st = FPS_ERR_TCH_FC;
		fps_st.fps_run = 0;
		FPS_SendReport();
		return 0;
	}

	//fps_st.time_out = ;
	FPS_TchScanRun( bcch_fc, wait_time );
	return FPS_ERR_NONE;
	
#else
	return 0;
#endif	
}

/*************************************************************
Name:FPS_GetAutoScanEn          
Description: 读取自动搜索使能状态
Input: void
Return: TRUE-使能, FALSE-禁能
**************************************************************/
BOOL FPS_GetAutoScanEn( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	if ( 1==fps_st.auto_scan_en )
	{
		return b_TRUE;
	}
	else
	{
		return b_FALSE;
	}
#else
	return b_FALSE;	// 不使用频点搜索功能返回禁能状态
#endif
}

/*************************************************************
Name:FPS_EnableAutoScan          
Description: 设置自动搜索使能
Input: void
Return: void
**************************************************************/
void FPS_EnableAutoScan( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能

	if (1==sys_param_1b[MADD_FPS_AUTO_SCAN].val)
	{
		if ( 0==fps_st.auto_scan_en )	// 由手动变成自动
		{
			fps_st.auto_scan_en = 1;	// 设置自动搜索使能
			fps_st.fps_run = 0;		    // 停止当前搜索   
			fps_st.scan_st = FPS_SCAN_ST_DONE;	// 修改状态标志为完成
			fps_st.err_st  = FPS_ERR_NONE;		// 清除错误标志
			fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 复位自动搜索状态机
            //fps_st.fc_count = 0;
			fps_st.tch_count    = 0;		// 清零TCH频点计数
			fps_st.edge_count   = 0;		// 清零EDGE计数
			fps_st.switch_count = 0;	    // 清零频点切换计数
		}
	}
	else  // 由自动变手动 
	{
		if ( 1==fps_st.auto_scan_en )	
		{
			fps_st.auto_scan_en = 0;	// 取消自动搜索使能
			fps_st.fps_run = 0;		// 停止当前搜索
			fps_st.scan_st = FPS_SCAN_ST_DONE;	// 修改状态标志为完成
			fps_st.err_st = FPS_ERR_NONE;		// 清除错误标志
			fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 复位自动搜索状态机
		}
	}
	// 使能状态不变则保持原样
#endif
}

/*************************************************************
Name:FPS_SetParam          
Description: 频点搜索初始化
             设置频点搜索的相关参数到FPGA中

Input: void
Return: void
**************************************************************/
void FPS_SetParam( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
//	if ( fps_st.range_sel != sys_param_1b[MADD_FPS_RFRANGE_SEL].val )	// 修改了频段范围
//	{
		fps_st.range_sel = sys_param_1b[MADD_FPS_RFRANGE_SEL].val;	// 更新频段选择范围值
		
		if ( b_TRUE==FPS_CheckParam(SYS_A_FLAG) )
		{
			FPS_SetScanFc(SYS_A_FLAG); 
		}
//	}
	if ( fps_st.bcch_lock!= sys_param_2b[MADD_FPS_BCCH_LK_SET].val )	// 修改了锁频目标BCCH频点
	{
		fps_st.bcch_lock = sys_param_2b[MADD_FPS_BCCH_LK_SET].val;	// 更新锁频目标BCCH频点
		
		if ( 1==fps_st.auto_scan_en )
		{
			// 重新搜索BCCH
			fps_st.fps_run = 0;		// 停止当前搜索
			fps_st.scan_st = FPS_SCAN_ST_DONE;	// 修改状态标志为完成
			fps_st.err_st  = FPS_ERR_NONE;		// 清除错误标志
			fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// 复位自动搜索状态机
		}
	}

	FPS_EnableAutoScan();
	
#endif
}


/*************************************************************
Name:FPS_Init          
Description: 频点搜索初始化
Input: void
Return: void
**************************************************************/
void FPS_Init( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	FPS_ResetResultParam();		// 复位搜索状态
	fps_st.auto_scan_en = (1==sys_param_1b[MADD_FPS_AUTO_SCAN].val) ? 1 : 0;
	fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;
	fps_st.fps_run = 0;
	fps_st.bcch_use.fc = 0;
	fps_st.bcch_use.power = 0;
	fps_st.bcch_use.precision = 0;
	fps_st.range_sel = sys_param_1b[MADD_FPS_RFRANGE_SEL].val;	// 频段范围选择
	FPS_CheckParam(SYS_A_FLAG);
#endif
}

/*************************************************************
Name:FPS_MainFunc          
Description: 频点搜索主程序，1秒执行一次
Input: void
Return: void
**************************************************************/
void FPS_MainFunc( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能

	if ( 0==fps_st.fps_run )	// 当前已停止搜索
	{
		FPS_HandleAutoScan();	// 自动变更自动搜索状态
		return;
	}

	// 处理搜索结果
	if ( FPS_MODE_TCH==fps_st.cur_mode )
	{
		FPS_TchFunc();
	}
	else
	{
		FPS_BcchFunc();
	} 
	
#endif
}



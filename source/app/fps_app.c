/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    : Rfc_scan.c
* Description : GSMƵ������
* Version     : v1.0
* Author      : RJ
* Date        : 2011-08-31
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2011-08-31		v0.1			��ʼ�汾
**************************************************************/
#include "Header.h"

#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
// �ⲿ����
extern volatile UINT32 sys_work_info;
extern FLOAT32 fpga_dgcic_a;
extern UINT32 module_param_chg_flag;		//ϵͳ���������޸ı�־
extern _T_MODULE_CFG mod_cfg_a;
extern _T_MODULE_CFG mod_cfg_b;

// �ļ��ڱ���
static UCHAR8 fps_report_head[MSG_PKT_HEAD_SIZE];	// ��Ϣͷ, ����ʼ2�ֽ�Ϊ0xEE, 0xEE��ʾ��Ϣͷ��Ч

_T_FPS_REPORT fps_report = { 0, 0, fps_report_head };
_T_FPS_STATUS fps_st;
_T_PBCCH_INFO pbcch_inf;
#endif

/*************************************************************
// ������ģ��vaΪ��������vbΪ����������ֵΪva����vb������
// va��Ϊ����������vbֻ��Ϊ����
*************************************************************/
int FPS_CalcMod( int va, int vb )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������

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
Description: ��λ����ȡһ������, λ�����ݸ�ʽ:��ʼλ-> B0[7:0]-B1[7:0]-B2[7:0]...Bn[7:0] <-����λ
Input: [bit_start: ����λ����ʼλ��,0��ʼ] [bit_len:��ȡλ����,�32λ] [p_bitstream:λ������ָ��]
Return: [��ȡ������ֵ]
**************************************************************/
UINT32 FPS_GetBitStream( UINT16 bit_start, UCHAR8 bit_len, UCHAR8 * p_bitstream )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UCHAR8 bit_offset;
	UCHAR8 tmp;
	UINT32 ret_val = 0;

	p_bitstream += (bit_start/8);	// ȡ��λ��ʼ���ڵ��ֽ�λ��
	tmp = *p_bitstream++;
	
	bit_offset = bit_start%8;		// ��λ��λ��ʼλ��
	tmp <<= bit_offset;
	while ( bit_len-- )
	{
		// ��ȡλֵ
		ret_val <<= 1;
		if ( 0!=(tmp&0x80) )
		{
			ret_val++;
		}
		// ��һλ
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
Description: TCH Bitmap N ��ʽ����
Input: 
	num:Ҫ���Ƶ�����(0~15)
	format: �����ʽ
	w_list: TCHЯ����W1��W16��16���������
Return:
	����Ŷ�Ӧ��FN
**************************************************************/
UINT16 FPS_DecodeFn( UCHAR8 num, UINT16 format, UINT16 * w_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UCHAR8 index = num+1;
	INT16 j=1;		// ������index��2�������ݵ����ֵ
	INT32 tmp = w_list[index-1];
	INT32 v_parent;

	// ����J��ֵ
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
Description: TCH Bitmap 0��ʽ����
	16�ֽڵ�TCH���ݣ���tch_buff[0]�ֽڵ�bit3��ʼ��tch_buff[15]��bit0�����α�ʾƵ��Ŀ���״̬����λ��ʾƵ��ʹ��
Input: 
	tch_buff: TCH��16�ֽ����ݣ�˳����
	fc_list: Ƶ�����ݣ����ʹ�ܵ�Ƶ���
Return:
	ʹ��Ƶ�����
**************************************************************/
UCHAR8 FPS_TchDecFmt0( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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
Description: TCH Bitmap Variable��ʽ����
	16�ֽڵ�TCH���ݣ���tch_buff[2].0��tch_buff[2].7Ϊ10λ��Ƶ�����ƫ�ƻ�ַ
	��tch_buff[2]�ֽڵ�bit6��ʼ��tch_buff[15]��bit0�����α�ʾƵ��Ŀ���״̬����λ��ʾƵ��ʹ��
Input: 
	tch_buff: TCH��16�ֽ����ݣ�˳����
	fc_list: Ƶ�����ݣ����ʹ�ܵ�Ƶ���
Return:
	ʹ��Ƶ�����
**************************************************************/
UCHAR8 FPS_TchDecFmtVariable( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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
Description: TCH Bitmap 1024 ��ʽ����
Input: 
	tch_buff: TCH��16�ֽ����ݣ�˳����
	fc_list: Ƶ�����ݣ����ʹ�ܵ�Ƶ���
Return:
	ʹ��Ƶ�����
**************************************************************/
UCHAR8 FPS_TchDecFmt1024( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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

	if ( w[0] == 1 )	// F0=1, 0��Ƶ����TCHƵ�㷶Χ�е�һ��
	{
		fc_list[count++] = 0;
	}
	for ( i=1; i<16; i++ )
	{
		if ( w[i]==0 ) break;					// ����WΪ0����ʾ����Ƶ�㶼��Ч
		fc_list[count++] = FPS_DecodeFn( (i-1), 1024, &w[1] );
	}
	return count;
	
#else
	return 0;
#endif
}

/*************************************************************
Name:FPS_TchDecFmt512          
Description: TCH Bitmap 512 ��ʽ����
Input: 
	tch_buff: TCH��16�ֽ����ݣ�˳����
	fc_list: Ƶ�����ݣ����ʹ�ܵ�Ƶ���
Return:
	ʹ��Ƶ�����
**************************************************************/
UCHAR8 FPS_TchDecFmt512( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 w[18];
	UINT16 i;
	UCHAR8 offset;

	//TRACE_INFO("TCH Decode Format 512:\r\n");
	offset = 7;
	w[0] = FPS_GetBitStream( offset, 10, tch_buff );	offset+=10; 		// 10
	if ( w[0]==0 ) 	// W0Ϊ0����Ƶ������
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
		if ( w[i]==0 ) break;					// ����WΪ0����ʾ����Ƶ�㶼��Ч
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
Description: TCH Bitmap 256 ��ʽ����
Input: 
	tch_buff: TCH��16�ֽ����ݣ�˳����
	fc_list: Ƶ�����ݣ����ʹ�ܵ�Ƶ���
Return:
	ʹ��Ƶ�����
**************************************************************/
UCHAR8 FPS_TchDecFmt256( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 w[22];
	UINT16 i;
	UCHAR8 offset;

	//TRACE_INFO("TCH Decode Format 256:\r\n");

	offset = 7;
	w[0] = FPS_GetBitStream( offset, 10, tch_buff );	offset+=10; 		// 10
	if ( w[0]==0 ) 	// W0Ϊ0����Ƶ������
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
		if ( w[i]==0 ) break;					// ����WΪ0����ʾ����Ƶ�㶼��Ч
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
Description: TCH Bitmap 128 ��ʽ����
Input: 
	tch_buff: TCH��16�ֽ����ݣ�˳����
	fc_list: Ƶ�����ݣ����ʹ�ܵ�Ƶ���
Return:
	ʹ��Ƶ�����
**************************************************************/
UCHAR8 FPS_TchDecFmt128( UCHAR8 * tch_buff, UINT16 * fc_list )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 w[29];
	UINT16 i;
	UCHAR8 offset;

	//TRACE_INFO("TCH Decode Format 128:\r\n");
	
	offset = 7;
	w[0] = FPS_GetBitStream( offset, 10, tch_buff );	offset+=10; 		// 10
	if ( w[0]==0 ) 	// W0Ϊ0����Ƶ������
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
		if ( w[i]==0 ) break;					// ����WΪ0����ʾ����Ƶ�㶼��Ч
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
Description: ����TCH����,��ȡƵ���
Input: [tch_buff: 16�ֽ�TCH����ָ��]
Return: void
**************************************************************/
void FPS_TchDecode(UCHAR8 * tch_buff)
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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
Description: ����TCH����,��ȡƵ���
Input: [tch_buff: 16�ֽ�TCH����ָ��]
Return: void
**************************************************************/
void FPS_PbcchDecode(UCHAR8 * pbcch_buff)
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UCHAR8 bit_offset; 
	UCHAR8 val;
	UCHAR8 tmp;

	// ��ʼ��PBCCH״̬
	pbcch_inf.valid = 0;
	pbcch_inf.gprs_support = 0;
	pbcch_inf.pbcch_support = 0;
	pbcch_inf.rfl_lst_support = 0;
	pbcch_inf.pbcch_fc_valid = 0;
	pbcch_inf.edge_support = 0;

	// ��ʼ����������
	bit_offset = 0; 
	val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// ��ȡ��1λ����
	bit_offset ++;
	if ( 0==val )
	{
		return;		// ��1λΪ0,��Ч��Ϣ,����
	}
	pbcch_inf.valid = 1;	// ��Ϣ��Ч

	bit_offset+=7;		// ���� 3λ��BCCH_CHANGE_MARK + 4λ��SI_CHANGE_FILED

	val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
	bit_offset++;
	if ( 1==val )		// =1,��GPRSƵ����Ϣ
	{
		pbcch_inf.gprs_support = 1;	// �ñ�־λ
		bit_offset += 2;		// ����2λ��SI13_CHANGE_MARK
		// ---- GPRS Mobile Allocation IE ----
		bit_offset += 6;		// ����6λ��HSN
		val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
		bit_offset++;
		if ( 1==val ) // =1,��RFL number listƵ����Ϣ
		{
			pbcch_inf.rfl_lst_support = 1;
			pbcch_inf.rfl_count = 0;
			do
			{
				val = FPS_GetBitStream( bit_offset, 4, pbcch_buff );	// ��ȡ4λRFL_NUMBER
				bit_offset += 4;
				pbcch_inf.rfl_lst[pbcch_inf.rfl_count++] = val;
				val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
				bit_offset++;
			}while ( 1==val );		// =0����ѭ��
		}

		val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
		bit_offset++;
		if ( 0==val )	// =0, λӳ��TCHƵ����Ϣ
		{
			pbcch_inf.arfcn_lst_mode = 0;	// λӳ��ģʽ
			val = pbcch_inf.ma_len = FPS_GetBitStream( bit_offset, 6, pbcch_buff )+1;		// ��ȡ6λMA_LENGTH
			bit_offset += 6;
			tmp = 0;
			while ( val>0 )	// ��ȡBITMAP��Ϣ
			{
				if ( val>8 )
				{
					pbcch_inf.ma_bm[tmp++]= FPS_GetBitStream( bit_offset, 8, pbcch_buff );		// ��ȡ8λBITMAP��Ϣ
					bit_offset += 8;
					val -= 8;
				}
				else
				{
					pbcch_inf.ma_bm[tmp] = FPS_GetBitStream( bit_offset, val, pbcch_buff );	// ��ȡnλBITMAP��Ϣ
					pbcch_inf.ma_bm[tmp] <<= (8-val);		// MSB����
					bit_offset += val;
					val = 0;
				}
			}
		}
		else		// =1, �б�ģʽTCHƵ����Ϣ
		{
			pbcch_inf.arfcn_lst_mode = 1;	// �б�����ģʽ
			pbcch_inf.arfcn_count = 0;		// ������������
			val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
			bit_offset++;
			while ( 1==val )	// =0����ѭ��
			{
				val = FPS_GetBitStream( bit_offset, 6, pbcch_buff );	// ��ȡ6λARFCN_INDEX
				bit_offset += 6;
				pbcch_inf.arfcn_lst[pbcch_inf.arfcn_count++] = val;
				val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
				bit_offset++;
			}
		}
		// ---- End: GPRS Mobile Allocation IE ----
	}// ����GPRSƵ����Ϣ����

	val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
	bit_offset++;
	if ( 1==val )	// =1, ����PBCCHƵ��
	{
		pbcch_inf.pbcch_support = 1;	// ֧��PBCCHƵ��
		bit_offset += 4;	// ����4λPS11_REPEAT_PERIOD
		bit_offset += 4;	// ����4λPb
		bit_offset += 5;	// ����4λTSC
		bit_offset += 6;	// ����4λTN
		val = FPS_GetBitStream( bit_offset, 2, pbcch_buff );	// 2λ��֧
		bit_offset += 2;
		if ( 1==val )	// =01, ��ʾ��PBCCHƵ��ARFCN
		{
			pbcch_inf.pbcch_fc_valid = 1;	// PBCCH��Ƶ����Ч
			pbcch_inf.pbcch_arfcn = FPS_GetBitStream( bit_offset, 10, pbcch_buff );	// ��ȡ10λARFCN
			bit_offset += 10;
		}
	}
	else		// =0, ������PBCCHƵ��, ���EDGE��Ϣ
	{
		bit_offset += 8;	// ����4λRAC
		bit_offset += 1;	// ����1λSPGC_CCCH_SUP
		bit_offset += 3;	// ����3λPRIORITY_ACCESS_THR
		bit_offset += 2;	// ����2λNETWORK_CONTROL_ORDER
		// ---- GPRS Cell Options IE ----
		bit_offset += 2;	// ����2λNMO
		bit_offset += 3;	// ����3λT3168
		bit_offset += 3;	// ����3λT3192
		bit_offset += 3;	// ����3λDRX_TIMER_MAX
		bit_offset += 1;	// ����1λACCESS_BURST_TYPE
		bit_offset += 1;	// ����1λCONTROL_ACK_TYPE
		bit_offset += 4;	// ����4λBS_CV_MAX
		val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
		bit_offset ++;
		if ( 1==val )	// =1, PAN��Ϣ, ����
		{
			bit_offset += 9;	// ����3λPAN_DEC + 3λPAN_INC + 3λPAN_MAX
		}
		val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
		bit_offset ++;
		if ( 1==val )	// =1, ����EDGE��Ϣ
		{
			bit_offset += 6;	// ����6λExtension Length
			val = FPS_GetBitStream( bit_offset, 1, pbcch_buff );	// 1λ��֧
			bit_offset ++;
			if ( 1==val )	// =1, ����EDGE��Ϣ
			{
				pbcch_inf.edge_support = 1;	// ֧��EDGEƵ��
			}
		}
	}
#endif
}

/*************************************************************
Name:FPS_CheckParam          
Description: ���ɨ�跶Χ, ������������Ƶ�����
Input: [p_mo_cfg:ģ������ָ��,������Ƶ����]
Return: TRUE-������Ч, FALSE-������Ч
**************************************************************/
#if 1 
BOOL FPS_CheckParam( UCHAR8 ab_flag )  //edasion
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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

	
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 0;	    // ������Ӫ��ʧ��
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 0;	// ����Ƶ��ʧ��

#ifdef FPS_LOCK_RANGE	// ����������Χ
	sys_param_2b[MADD_FPS_S1].val = FPS_RANGE_S1; 
	sys_param_2b[MADD_FPS_E1].val = FPS_RANGE_E1; 
	sys_param_2b[MADD_FPS_S2].val = FPS_RANGE_S2; 
	sys_param_2b[MADD_FPS_E2].val = FPS_RANGE_E2;  
#else   
	if ( 128==sys_param_1b[MADD_FPS_MOSVC_SEL].val )	// �ֶ�ָ������Ƶ���
	{
		;
	}
	else if ( 1==sys_param_1b[MADD_FPS_MOSVC_SEL].val )	// ��ͨƵ��
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
	else // �ƶ�Ƶ��
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

	fps_st.fc_count = 0;		// ����Ƶ�����

	// ��ȡɨ���1Ƶ�㷶Χ,�ڲ�������ʱ,��֤fc_start<fc_end
	fc_start = sys_param_2b[MADD_FPS_S1].val;
	fc_end = sys_param_2b[MADD_FPS_E1].val;
	
	TRACE_INFO("fc_start=[%d],fc_end=[%d].FPS_CheckParam\r\n ",fc_start,fc_end);	

	// ������Ƶ����Ƿ���Ч,��ȡ�����Ƶ�ʺ���СƵ��
	for ( ; fc_start<=fc_end; fc_start++ )
	{
         
		freq = CalcFreqPointToFreq( ucNetTpy,fc_start );  // edasion
		//freq = p_mo_cfg->lpf_ConvFcToFreq( fc_start );  // edasion
		
		if ( freq<0 )
		{
			TRACE_INFO("FPS_CheckParam err3\r\n ");	
			return b_FALSE;	// ��ЧƵ���
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
	// �ڶ�ɨ�����ʼƵ��Ų�Ϊ0,��ʾʹ�õڶ�ɨ���
	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		// ��ȡɨ���2Ƶ�㷶Χ,�ڲ�������ʱ,��֤fc_start<fc_end
		fc_start = sys_param_2b[MADD_FPS_S2].val;
		fc_end = sys_param_2b[MADD_FPS_E2].val;
		// ������Ƶ����Ƿ���Ч,��ȡ�����Ƶ�ʺ���СƵ��
		for ( ; fc_start<=fc_end; fc_start++ )
		{
			freq = CalcFreqPointToFreq( ucNetTpy,fc_start );  // edasion
			//freq = p_mo_cfg->lpf_ConvFcToFreq( fc_start );  edasion
			
			if ( freq<0 )
			{
							TRACE_INFO("FPS_CheckParam err4\r\n ");	
				return b_FALSE;	// ��ЧƵ���
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
	// �����Ƶ��Ϊ0,����СƵ��Ϊ0,��Ƶ�ʿ�ȳ�������Ĵ���,����FALSE
	if ( (0==freq_max) || (0==freq_min) || ((freq_max-freq_min)>PLL_RANGE) )
	{
					TRACE_INFO("FPS_CheckParam err6\r\n ");	
		return b_FALSE;
	}
}
else if(NET_TYPE_DCS1800==ucNetTpy)
{
	// �����Ƶ��Ϊ0,����СƵ��Ϊ0,��Ƶ�ʿ�ȳ�������Ĵ���,����FALSE
	if ( (0==freq_max) || (0==freq_min) || ((freq_max-freq_min)>DCS_PLL_RANGE) )
	{
					TRACE_INFO("FPS_CheckParam err6\r\n ");	
		return b_FALSE;
	}
}	
	// �����Ӧ�ı���Ƶ��
	#if 0   //edasion
	if ( b_FALSE == p_mo_cfg->lpf_CheckLocalPll( fc_max, fc_min, &(p_mo_cfg->dl_pcf), &(p_mo_cfg->ul_pcf) ) )
	{
		p_mo_cfg->dl_pcf.ftoset = -1;
		p_mo_cfg->ul_pcf.ftoset = -1;
		return b_FALSE;
	}
	#endif
	
	// ����4153���±�־,�л����µı���     
	SET_BIT_FLAG(module_param_chg_flag, PCHG_A_FL_CHG);

#if ( B_NETWORK_TYPE==NET_DIVE )
	//mod_cfg_b.dl_pcf.ftoset = mod_cfg_a.dl_pcf.ftoset;
	//mod_cfg_b.ul_pcf.ftoset = mod_cfg_a.ul_pcf.ftoset;
	// ����4153���±�־,�л����µı��� 
	SET_BIT_FLAG(module_param_chg_flag, PCHG_B_FL_CHG);
#endif

	fps_st.fc_count = fc_count;		// ����Ƶ�����
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 1;	// ������Ӫ�̳ɹ�
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 1;	// ����Ƶ�γɹ�
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
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 fc_start, fc_end;
	UINT16 tmp;
	INT32 freq;
	INT32 freq_min=0;
	INT32 freq_max=0;
	UINT16 fc_min=0;
	UINT16 fc_max = 0;
	UCHAR8 fc_count = 0;
	
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 0;	// ������Ӫ��ʧ��
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 0;	// ����Ƶ��ʧ��

#ifdef FPS_LOCK_RANGE	// ����������Χ
	sys_param_2b[MADD_FPS_S1].val = FPS_RANGE_S1;
	sys_param_2b[MADD_FPS_E1].val = FPS_RANGE_E1;
	sys_param_2b[MADD_FPS_S2].val = FPS_RANGE_S2;
	sys_param_2b[MADD_FPS_E2].val = FPS_RANGE_E2;
#else
	if ( 128==sys_param_1b[MADD_FPS_MOSVC_SEL].val )	// �ֶ�ָ������Ƶ���
	{
		;
	}
	else if ( 1==sys_param_1b[MADD_FPS_MOSVC_SEL].val )	// ��ͨƵ��
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
	else // �ƶ�Ƶ��
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

	fps_st.fc_count = 0;		// ����Ƶ�����

	// ��ȡɨ���1Ƶ�㷶Χ,�ڲ�������ʱ,��֤fc_start<fc_end
	fc_start = sys_param_2b[MADD_FPS_S1].val;
	fc_end = sys_param_2b[MADD_FPS_E1].val;
	// ������Ƶ����Ƿ���Ч,��ȡ�����Ƶ�ʺ���СƵ��
	for ( ; fc_start<=fc_end; fc_start++ )
	{
		//freq = p_mo_cfg->lpf_ConvFcToFreq( fc_start );  // edasion
		
		if ( freq<0 )
		{
			return b_FALSE;	// ��ЧƵ���
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
	// �ڶ�ɨ�����ʼƵ��Ų�Ϊ0,��ʾʹ�õڶ�ɨ���
	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		// ��ȡɨ���2Ƶ�㷶Χ,�ڲ�������ʱ,��֤fc_start<fc_end
		fc_start = sys_param_2b[MADD_FPS_S2].val;
		fc_end = sys_param_2b[MADD_FPS_E2].val;
		// ������Ƶ����Ƿ���Ч,��ȡ�����Ƶ�ʺ���СƵ��
		for ( ; fc_start<=fc_end; fc_start++ )
		{
			//freq = p_mo_cfg->lpf_ConvFcToFreq( fc_start );  edasion
			
			if ( freq<0 )
			{
				return b_FALSE;	// ��ЧƵ���
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
	// �����Ƶ��Ϊ0,����СƵ��Ϊ0,��Ƶ�ʿ�ȳ�������Ĵ���,����FALSE
	if ( (0==freq_max) || (0==freq_min) || ((freq_max-freq_min)>PLL_RANGE) )
	{
		return b_FALSE;
	}
	// �����Ӧ�ı���Ƶ��
	#if 0   //edasion
	if ( b_FALSE == p_mo_cfg->lpf_CheckLocalPll( fc_max, fc_min, &(p_mo_cfg->dl_pcf), &(p_mo_cfg->ul_pcf) ) )
	{
		p_mo_cfg->dl_pcf.ftoset = -1;
		p_mo_cfg->ul_pcf.ftoset = -1;
		return b_FALSE;
	}
	#endif
	
	// ����4153���±�־,�л����µı���
	SET_BIT_FLAG(module_param_chg_flag, PCHG_A_FL_CHG);

#if ( B_NETWORK_TYPE==NET_DIVE )
	mod_cfg_b.dl_pcf.ftoset = mod_cfg_a.dl_pcf.ftoset;
	mod_cfg_b.ul_pcf.ftoset = mod_cfg_a.ul_pcf.ftoset;
	// ����4153���±�־,�л����µı���
	SET_BIT_FLAG(module_param_chg_flag, PCHG_B_FL_CHG);
#endif

	fps_st.fc_count = fc_count;		// ����Ƶ�����
	sys_param_1b[MADD_FPS_MOSVC_LK_ST].val = 1;	// ������Ӫ�̳ɹ�
	sys_param_1b[MADD_FPS_RFRANGE_LK_ST].val = 1;	// ����Ƶ�γɹ�
	return b_TRUE;
	
#else
	return b_TRUE;
#endif	
}
#endif
/*************************************************************
Name: _CalcFpgaFreqWord
Description:  ����Ƶ��ż���ɨ��Ƶ���FPGAƵ���ּĴ���ֵ
Input: [p_mo_cfg:ģ������ָ��,������Ƶ����] [freq_code: Ƶ���]
Return: Ƶ���ּĴ�����ֵ
**************************************************************/
#if 1
UINT32 FPS_CalcFpgaFreqWord( UCHAR8 ab_flag, UINT16 freq_code )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������

	UINT32 reg_val;
	INT32 up_fre_word, down_fre_word;

	up_fre_word = 0;
	down_fre_word = 0;

    #if 0
		INT32  freq_point = -1;	// Ƶ��
		INT32  digit_freq;	    // ����Ƶ�� 
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
		//digit_freq = p_mo_cfg->lpf_CalcDf( freq_point, &(p_mo_cfg->dl_pcf) );		// ��������Ƶ��
		freq_word = _CalcFpgaFw( digit_freq );	// ����Ƶ����
		fw = _AdjustFpgaFw(freq_word);		// Ƶ���ֵ���

		return _CalcFpgaFwReg(fw);			// ת����Ƶ���ּĴ�����ֵ	
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
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	INT32  freq_point = -1;	// Ƶ��
	INT32  digit_freq;	    // ����Ƶ�� 
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
	//digit_freq = p_mo_cfg->lpf_CalcDf( freq_point, &(p_mo_cfg->dl_pcf) );		// ��������Ƶ��
	freq_word = _CalcFpgaFw( digit_freq );	// ����Ƶ����
	fw = _AdjustFpgaFw(freq_word);		// Ƶ���ֵ���

	return _CalcFpgaFwReg(fw);			// ת����Ƶ���ּĴ�����ֵ	
	
#else
	return 0;
#endif
}
#endif
/*************************************************************
Name:FPS_SetScanFc          
Description: д��ɨ��Ƶ��ŵ�FPGA��
Input: [p_mo_cfg:ģ������ָ��,������Ƶ����] 
Return: void  
**************************************************************/
#if 1
void FPS_SetScanFc( UCHAR8 ab_flag )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 fc;
	UINT32 reg;

	FPGA_ENABLE_WRITE;
	
	// ��Fpgaд��Ҫɨ���Ƶ�����
	FpgaWriteRegister( FPGA_REG_RFC_SCAN_CNT, fps_st.fc_count );

	for ( fc=sys_param_2b[MADD_FPS_S1].val; fc<=sys_param_2b[MADD_FPS_E1].val; fc++ )
	{
		reg = FPS_CalcFpgaFreqWord(ab_flag, fc);
//		printf("1Ƶ������Ƶ����%x\r\n",reg);
		FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF_1, (UINT16)(((reg>>12)&0x3FFF)|((reg&0x80000000)>>16)));//дƵ���ֵ�[25:12]λ
		FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF_2, (UINT16)(reg&0xFFF));//дƵ���ֵ�[11:0]λ
		//FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF, reg );
	}

	// �ڶ�ɨ�����ʼƵ��Ų�Ϊ0,��ʾʹ�õڶ�ɨ���
	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		for ( fc=sys_param_2b[MADD_FPS_S2].val; fc<=sys_param_2b[MADD_FPS_E2].val; fc++ )
		{
			reg = FPS_CalcFpgaFreqWord(ab_flag, fc);
//			printf("2Ƶ������Ƶ����%x\r\n",reg);
			//FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF, reg );
			FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF_1, (UINT16)(((reg>>12)&0x3FFF)|((reg&0x80000000)>>16)));//дƵ���ֵ�[25:12]λ
			FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF_2, (UINT16)(reg&0xFFF));//дƵ���ֵ�[11:0]λ

		}
	}

	if ( 1==fps_st.auto_scan_en )	// �Զ�����״̬��,������������Χ,��������״̬
	{
		fps_st.fps_run = 0;		// ֹͣ��ǰ����
		fps_st.scan_st = FPS_SCAN_ST_DONE;	// �޸�״̬��־Ϊ���
		fps_st.err_st  = FPS_ERR_NONE;		// ��������־
		fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ��λ�Զ�����״̬��
	}

	FPGA_DISABLE_WRITE;
#endif
}

#else

void FPS_SetScanFc( _T_PMODULE_CFG p_mo_cfg )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 fc;
	UINT16 reg;

	FPGA_ENABLE_WRITE;
	
	// ��Fpgaд��Ҫɨ���Ƶ�����
	FpgaWriteRegister( FPGA_REG_RFC_SCAN_CNT, fps_st.fc_count );

	for ( fc=sys_param_2b[MADD_FPS_S1].val; fc<=sys_param_2b[MADD_FPS_E1].val; fc++ )
	{
		reg = FPS_CalcFpgaFreqWord(p_mo_cfg, fc);
		FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF, reg );
	}

	// �ڶ�ɨ�����ʼƵ��Ų�Ϊ0,��ʾʹ�õڶ�ɨ���
	if ( sys_param_2b[MADD_FPS_S2].val>0 )
	{
		for ( fc=sys_param_2b[MADD_FPS_S2].val; fc<=sys_param_2b[MADD_FPS_E2].val; fc++ )
		{
			reg = FPS_CalcFpgaFreqWord(p_mo_cfg, fc);
			FpgaWriteRegister( FPGA_REG_RFC_SCAN_DF, reg );
		}
	}

	if ( 1==fps_st.auto_scan_en )	// �Զ�����״̬��,������������Χ,��������״̬
	{
		fps_st.fps_run = 0;		// ֹͣ��ǰ����
		fps_st.scan_st = FPS_SCAN_ST_DONE;	// �޸�״̬��־Ϊ���
		fps_st.err_st = FPS_ERR_NONE;		// ��������־
		fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ��λ�Զ�����״̬��
	}

	FPGA_DISABLE_WRITE;
#endif
}
#endif
/*************************************************************
Name:        FPS_BcchScanRun          
Description: ����BCCH����
Input:       void
Return:      void
**************************************************************/
void FPS_BcchScanRun( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	fps_st.cur_mode = FPS_MODE_BCCH;	// ģʽ:BCCH
	fps_st.fps_run = 1;					// ��������
   //fps_st.bcch_count = 0;					     // �������
	if ( fps_st.fc_count > 0 )
	{
		fps_st.scan_st = FPS_SCAN_ST_BCCH;	    // ״̬:����BCCH
		fps_st.err_st  = FPS_ERR_NONE;			// ����״̬��λ
		FPGA_ENABLE_WRITE; 
		FpgaWriteRegister( FPGA_REG_RFC_SCAN_START, 1 );	// ����BCCHɨ��
		FPGA_DISABLE_WRITE;
	}
	else
	{ 
		fps_st.scan_st = FPS_SCAN_ST_DONE;	// ״̬:�������
		fps_st.err_st  = FPS_ERR_BCCH_RANGE;	// ����:������Χ����
	}
#endif
}

/*************************************************************
Name:FPS_SetScanFc          
Description: д��ɨ��Ƶ��ŵ�FPGA��
Input: [p_mo_cfg:ģ������ָ��,������Ƶ����]
Return: void
**************************************************************/
void FPS_TchScanRun( UINT16 bcch_fc, UINT16 time_out )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
    UINT32 reg;
	fps_st.cur_mode = FPS_MODE_TCH;	// ģʽ:TCH
	fps_st.tch_count = 0;		// ��λ:TCHƵ�����
	fps_st.edge_count = 0;		// ��λ:EDGEƵ�����
	pbcch_inf.valid = 0;		// ��λ:PBCCH��Ϣ��Ч��־
	fps_st.err_st = FPS_ERR_NONE;			// ��λ:����״̬
	fps_st.bcch_fc_sel = bcch_fc;			// ��¼BCCHƵ���
	fps_st.scan_st = FPS_SCAN_ST_TCH;		// ״̬:����TCH
	if ( 0==time_out )
	{
		fps_st.time_out = 90;				// ��ʱ:90�����ʱĬ�ϲ����޸�)
	}
	else
	{
		fps_st.time_out = time_out;		// ��ʱ
	}
	fps_st.fps_run = 1;					// ��������
		
	FPGA_ENABLE_WRITE;
	//FpgaWriteRegister(FPGA_REG_BCCH_DF, FPS_CalcFpgaFreqWord( SYS_A_FLAG, bcch_fc));	// дTCHƵ��,��������
	reg = FPS_CalcFpgaFreqWord( SYS_A_FLAG, bcch_fc);
	FpgaWriteRegister(FPGA_REG_BCCH_DF_1, (UINT16)(((reg>>12)&0x3FFF)|((reg&0x80000000)>>16)));	// дTCHƵ��[25:12]λ,��������
	FpgaWriteRegister(FPGA_REG_BCCH_DF_2, (UINT16)(reg&0xFFF));	// дTCHƵ��[11:0]λ,��������	

	FPGA_DISABLE_WRITE;
#endif
}

/*************************************************************
Name:FPS_CidScanRun          
Description: д��ɨ��Ƶ��ŵ�FPGA��
Input: [p_mo_cfg:ģ������ָ��,������Ƶ����]
Return: void
**************************************************************/
void FPS_CidScanRun( UINT16 bcch_fc )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
    UINT32 reg;
	fps_st.cur_mode = FPS_MODE_CID;	// ģʽ:CID
	fps_st.bcch_fc_sel = bcch_fc;			// ��¼BCCHƵ���
	fps_st.scan_st = FPS_SCAN_ST_CID;		// ״̬:����CID
	fps_st.time_out = 30;				// ��ʱ:30��(����ʱĬ�ϲ����޸�)
		
	FPGA_ENABLE_WRITE;
	//FpgaWriteRegister(FPGA_REG_BCCH_DF, FPS_CalcFpgaFreqWord( SYS_A_FLAG, bcch_fc));	// дTCHƵ��,��������
	reg = FPS_CalcFpgaFreqWord( SYS_A_FLAG, bcch_fc);
	FpgaWriteRegister(FPGA_REG_BCCH_DF_1, (UINT16)(((reg>>12)&0x3FFF)|((reg&0x80000000)>>16)));	// дTCHƵ��[25:12]λ,��������
	FpgaWriteRegister(FPGA_REG_BCCH_DF_2, (UINT16)(reg&0xFFF));	// дTCHƵ��[11:0]λ,��������	

	FPGA_DISABLE_WRITE;
#endif
}


/*************************************************************
Name:FPS_ConvBcchIndex2Fc          
Description: ��BCCH��������е�BCCHƵ�����ת��ΪƵ���
Input: [bcch_id:BCCHƵ�����]
Return: Ƶ���, 0xFFFF��ʾ��Ч���
**************************************************************/
UINT16 FPS_ConvBcchIndex2Fc( UINT16 bcch_id )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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
Description: ����BCCHɨ��
Input: 
	force_run: 1-ǿ��ִ��
	wait_time: ��ʱ����
Return: ���:0-�����ɹ���1-����ִ��BCCHɨ�裬2-����ִ��TCHɨ�裬3-�д���
**************************************************************/
void FPS_AutoStartBcch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	fps_st.time_out = (fps_st.fc_count+1)*5;
	FPS_BcchScanRun();
#endif
}

/*************************************************************
Name:FPS_CompositorBcchLst          
Description: ��BCCH�б�����ֵ�Ӵ�С��������
Input: void
Return: void
**************************************************************/
void FPS_CompositorBcchLst( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	_T_FPS_BCCH_INFO bcch_tmp;
	UCHAR8 i, k;

	if ( fps_st.bcch_count < 1 )	// ֻ��BCCH��������1������Ҫ����
	{
		return;
	}

	for ( i=0; i<fps_st.bcch_count-1; i++ )
	{
		for ( k=i+1; k<fps_st.bcch_count; k++ )
		{
			if ( fps_st.bcch_lst[k].power < fps_st.bcch_lst[i].power )	// ����С��ֱ������
			{
				continue;
			}
			else if ( fps_st.bcch_lst[k].power == fps_st.bcch_lst[i].power )	// ������ֵ���
			{
				if ( fps_st.bcch_lst[k].precision <= fps_st.bcch_lst[i].precision )	// ��ȷ��С��ֱ������
				{
					continue;
				}
			}
			// ��������BCCH
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
Description: ����BCCH�������
Input: void
Return: void
**************************************************************/
void FPS_HandleBcch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UCHAR8 count;	// BCCH����
	UCHAR8 i, j;
	UINT16 tmp;
	UINT32 pow_min= 0xFFFFFFFF;
	_T_FPS_BCCH_INFO bcch_inf;

	// ��ʼ��״̬
	fps_st.err_st = FPS_ERR_BCCH_RESULT;
		
	count = FpgaReadRegister(FPGA_REG_BCCH_CNT);	// ��BCCH����
	if ( count>fps_st.fc_count )	// BCCH���������ܵ���������
	{
		return;
	}

	// ��ȡBCCH��Ϣ
	i = 0;
	while( count-- )
	{
		tmp = FpgaReadRegister(FPGA_REG_BCCH_INFO);	// ��8λƵ�����, ��8λ��ȷ��
		bcch_inf.precision = tmp&0xFF;
		tmp>>=8;
		bcch_inf.fc = FPS_ConvBcchIndex2Fc( tmp );
		if ( bcch_inf.fc == 0xFFFF )
		{
			return;	// ��ЧƵ�����,����
		}
		// 48λ����,��16Ϊ����,������32λ
		bcch_inf.power = (UINT32)FpgaReadRegister(FPGA_REG_BCCH_INFO)<<16;
		bcch_inf.power |= FpgaReadRegister(FPGA_REG_BCCH_INFO);
		tmp = FpgaReadRegister(FPGA_REG_BCCH_INFO);

		if ( bcch_inf.fc == fps_st.bcch_use.fc )	// ���µ�ǰ���õ�BCCH״̬
		{
			fps_st.bcch_use.power = bcch_inf.power;
			fps_st.bcch_use.precision = bcch_inf.precision;
		}
		
		// ���ʹ�С��ֱ�Ӷ���
		if ( bcch_inf.power > 0 )
		{
			fps_st.bcch_lst[i].fc = bcch_inf.fc;
			fps_st.bcch_lst[i].power = bcch_inf.power;
			fps_st.bcch_lst[i].precision = bcch_inf.precision;
			if ( i<FPS_BCCH_MAX )		// ǰFPS_BCCH_MAX��BCCHֱ�ӱ���
			{
				if ( bcch_inf.power<pow_min ) 	// ��ǰ�����м�¼������Сֵ
				{
					pow_min = bcch_inf.power;
				}
				i++;
			}
			else		// ��ʼ�Ƚ�
			{
				if ( bcch_inf.power>=pow_min ) 	// ������BCCH���ʱ��ѱ����BCCH�б��е�ĳ��BCCH����ǿ
				{
					// �����б��й���ֵ��С��BCCH
					for ( j=0; j<FPS_BCCH_MAX; j++ )
					{
						if ( pow_min == fps_st.bcch_lst[j].power )		// ��λ��BCCH
						{
							if ( fps_st.bcch_lst[j].power == bcch_inf.power )	// ������ֵ���
							{
								// �Ƚ���ȷ��
								if ( fps_st.bcch_lst[j].precision >= bcch_inf.precision )
								{
									continue;		// ������BCCH��ȷ��С���б���BCCH����ȷ��,���滻
								}
							}	
							// ������BCCH���ʴ����б���BCCH�Ĺ���ֱ���滻
							fps_st.bcch_lst[j].fc = bcch_inf.fc;
							fps_st.bcch_lst[j].power = bcch_inf.power;
							fps_st.bcch_lst[j].precision = bcch_inf.precision;
							break;
						}
					}
					if ( j<FPS_BCCH_MAX )		// �б�����
					{
						// �������б��й�����Сֵ
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

	fps_st.bcch_count = i;		// ����BCCH����
	fps_st.err_st = FPS_ERR_NONE;	// ����״̬
	
	// ��BCCH�����ʴ�С����
	FPS_CompositorBcchLst();
	
#endif	
}

/*************************************************************
Name:FPS_HandleTch          
Description: ����TCH�������
Input: void
Return: void
**************************************************************/
void FPS_HandleTch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 tmp = 0;
	UINT16 i;
	UCHAR8 tch_buf[16];
	
	for (i=0; i<16; )
	{
		tmp  = FpgaReadRegister(FPGA_REG_TCH_INFO);
		tch_buf[i++] = (UCHAR8)(tmp&0xff);
		tch_buf[i++] = (UCHAR8)(tmp>>8);
	}

	// ����TCH
	FPS_TchDecode( tch_buf );
	fps_st.err_st = FPS_ERR_NONE;	// ����״̬
#endif	
}

/*************************************************************
Name:FPS_HandlePbcch          
Description: ����TCH�������
Input: void
Return: void
**************************************************************/
void FPS_HandlePbcch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 tmp = 0;
	UINT16 i;
	UCHAR8 pbcch_buf[20];
	
	for (i=0; i<20; )
	{
		tmp  = FpgaReadRegister(FPGA_REG_PBCCH_INFO);
		pbcch_buf[i++] = (UCHAR8)(tmp&0xff);
		pbcch_buf[i++] = (UCHAR8)(tmp>>8);
	}
	
	// ����PBCH
	FPS_PbcchDecode( pbcch_buf );
	fps_st.err_st = FPS_ERR_NONE;	// ����״̬
#endif	
}

/*************************************************************
Name:FPS_HandleEdge          
Description: ����TCH�������
Input: void
Return: void
**************************************************************/
void FPS_HandleEdge( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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
Description: ��λ����ȡBCCH�������
Input: void
Return: void
**************************************************************/
UINT16 FPS_GetBcchResult( UCHAR8 * p_ret )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 len = 0;
	UINT16 i;
	FLOAT32 gain_in;		// ǰ��ģ������ = ǰ�˱������-�����˲�������Gcic-ǰ�˲�������Gcmps
	INT32 fc_power;
	UINT32 tmp;

	gain_in = CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));	// ǰ�˲�������Gcmps
	gain_in = FPGA_REC_GFNOM - fpga_dgcic_a - gain_in;	// ǰ��ģ������

	p_ret[len++] = fps_st.bcch_count;
	for ( i=0; i<fps_st.bcch_count; i++ )
	{
		// Ƶ���
		p_ret[len++] = (UCHAR8)(fps_st.bcch_lst[i].fc&0xff);
		p_ret[len++] = (UCHAR8)((fps_st.bcch_lst[i].fc>>8)&0xff);
		
		// ����
		fc_power = (INT32)( 1000 * (CALC_POWER( fps_st.bcch_lst[i].power ) - gain_in) );	// �����빦��dbm = AD����-ǰ��ģ������G_in, x1000����3λС��
		tmp = (UINT32)fc_power;
		p_ret[len++] = (UCHAR8)(tmp&0xff);
		p_ret[len++] = (UCHAR8)((tmp>>8)&0xff);
		p_ret[len++] = (UCHAR8)((tmp>>16)&0xff);
		p_ret[len++] = (UCHAR8)((tmp>>24)&0xff);
		
		// ������
		p_ret[len++] = fps_st.bcch_lst[i].precision;

		// CIDС��ʶ����
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
Description: ��λ����ȡTCH�������
Input: void
Return: void
**************************************************************/
UINT16 FPS_GetTchResult( UCHAR8 * p_ret )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 len = 0;
	UINT16 tmp;
	UINT16 i;

	// ��������TCH��BCCHƵ���
	tmp = fps_st.bcch_fc_sel;
	p_ret[len++] = (UCHAR8)(fps_st.bcch_fc_sel&0xff);
	p_ret[len++] = (UCHAR8)((fps_st.bcch_fc_sel>>8)&0xff);
	
	// TCHƵ������
	p_ret[len++] = fps_st.tch_count;
	// TCHƵ���б�
	for ( i=0; i<fps_st.tch_count; i++ )
	{
		p_ret[len++] = (UCHAR8)(fps_st.tch_lst[i]&0xff);
		p_ret[len++] = (UCHAR8)((fps_st.tch_lst[i]>>8)&0xff);
	}
	
	// EDGEƵ������
	p_ret[len++] = fps_st.edge_count;
	// EDGEƵ���б�
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
Description: ��λ����ȡ�Զ�ɨ��״̬
Input: void
Return: void
**************************************************************/
UINT16 FPS_GetAutoScanStaus( UCHAR8 * p_ret )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 len = 0;
	UINT16 i;
	FLOAT32 gain_in;		// ǰ��ģ������ = ǰ�˱������-�����˲�������Gcic-ǰ�˲�������Gcmps
	INT32 fc_power;
	UINT32 tmp;

	if ( 0==fps_st.auto_scan_en )	// ��ǰ�����ֶ�����ģʽ
	{
		p_ret[len++] = 3;		// ����
		p_ret[len++] = FPS_ERR_MANUAL_MODE;	// �������:ģʽ����
		return len;
	}
	p_ret[len++] = 0;		// �޴���

	gain_in = CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));	// ǰ�˲�������Gcmps
	gain_in = FPGA_REC_GFNOM - fpga_dgcic_a - gain_in;	// ǰ��ģ������

	// �Զ�����״̬
	p_ret[len++] = fps_st.auto_state;
	// BCCH�л�����
	p_ret[len++] = fps_st.switch_count;
	// �Զ�����ѡ����BCCHƵ���
	p_ret[len++] = (UCHAR8)(fps_st.bcch_use.fc&0xff);
	p_ret[len++] = (UCHAR8)((fps_st.bcch_use.fc>>8)&0xff);
	// �Զ�����ѡ����BCCH����
	fc_power = (INT32)( 1000 * (CALC_POWER(fps_st.bcch_use.power) - gain_in) );	// �����빦��dbm = AD����-ǰ��ģ������G_in, x1000����3λС��
	tmp = (UINT32)fc_power;
	p_ret[len++] = (UCHAR8)(tmp&0xff);
	p_ret[len++] = (UCHAR8)((tmp>>8)&0xff);
	p_ret[len++] = (UCHAR8)((tmp>>16)&0xff);
	p_ret[len++] = (UCHAR8)((tmp>>24)&0xff);
	// �Զ�����ѡ����BCCH��ȷ��
	p_ret[len++] = fps_st.bcch_use.precision;
	// ��ǰ����ģʽ
	p_ret[len++] = ( 1==fps_st.cur_mode ) ? 1 : 0;
	// ��ǰ����״̬
	p_ret[len++] = fps_st.scan_st;
	// ��ǰ����������Ϣ
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
Description: �ֶ�ɨ�����������ɨ����
Input: void
Return: void
**************************************************************/
void FPS_SendReport( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UCHAR8 * p_txbuff = sys_temp_buff;
	UINT16 tx_len=0;
	UINT16 i;
	UINT32 tmp;

	if ( (0xEE==fps_report_head[0]) && (0xEE==	fps_report_head[1]) )	// ��Ч��Ϣͷ
	{
		return;
	}

	// ��Ϣͷ
	for ( i=0; i<MSG_PKT_HEAD_SIZE; i++ )
	{
		p_txbuff[tx_len++] = fps_report_head[i];
	}
	
	// ģʽ
	p_txbuff[tx_len++] = fps_report.cmd_mode;
	
	// ����ģʽ
	p_txbuff[tx_len++] = fps_report.ext_mode;

	// ״̬
	if ( FPS_ERR_NONE != fps_st.err_st )	
	{
		p_txbuff[tx_len++] = FPS_RESULT_ERROR;			// �д���
		p_txbuff[tx_len++] = fps_st.err_st;
	}
	else
	{
		if ( FPS_SCAN_ST_DONE==fps_st.scan_st )
		{
			p_txbuff[tx_len++] = FPS_RESULT_OK;			// �޴���ɨ�����
		}
		else
		{
			p_txbuff[tx_len++] = FPS_RESULT_WORK;			// ����ɨ����
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
Description: ����Ӧ�����ݰ�����Ϣͷ
Input: void
Return: void
**************************************************************/
void FPS_MakeAckMsgHead( UCHAR8 cmd_mode, UCHAR8 ext_mode, UCHAR8 head_len, UCHAR8 * p_head)
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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
Description: ��λ�������
Input: void
Return: void
**************************************************************/
void FPS_ResetResultParam( void )
{
	UCHAR8 i;
	CHAR8 tmp = -120;

	// ������BCCH��Ϣ
	sys_param_2b[MADD_FPS_BCCH_FC_M].val = 65535;	// ������BCCH, ��Ч
	sys_param_1b[MADD_FPS_BCCH_POW_M].val = (UCHAR8)tmp;		// ������BCCH���ʣ� -120
	// ����BCCH��Ϣ
	for ( i=0; i<6; i++ )
	{
		sys_param_2b[MADD_FPS_BCCH_FC_1+i].val = 65535;	// ��ЧBCCH
		sys_param_1b[MADD_FPS_BCCH_POW_1+i].val = (UCHAR8)tmp;		// ����BCCH����
		sys_param_2b[MADD_FPS_CID_1+i].val = 0;	// ��ЧCID
	}
	// CA��Ϣ
	sys_param_1b[MADD_FPS_CA_COUNT].val = 0;		// ��Ч�ŵ���:0
	
	for ( i=0; i<16; i++ )
	{
		sys_param_2b[MADD_FPS_CA_FC_0+i].val = 65535;		// ��ЧCA
	}
	// ��վ��Ϣ
	sys_param_2b[MADD_FPS_CID].val = 0;
	sys_param_2b[MADD_FPS_AREA_ID].val = 0;
	sys_param_1b[MADD_FPS_BS_ID].val = 0;
	// �������״̬
	sys_param_1b[MADD_FPS_BCCH_LK_ST].val = 0;		// ����BCCHʧ��
	
}

/*************************************************************
Name: FPS_SetResultToSysFc          
Description: �����Ӧ�õ�ϵͳ����Ƶ��
Input: void
Return: void
**************************************************************/
void FPS_SetResultToSysFc( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN

#ifdef FUNC_FPS_AUTO_SET	// ��������Զ��������������Ϊ����Ƶ���

	UINT16 fc_count;
	UINT16 i, tmp;
	UINT16 fc;
	UCHAR8 fpssaveflashflag;
	fc_count = sys_param_1b[MADD_FPS_CA_COUNT].val;		// Ƶ����
	
	if ( fc_count > 16 ) fc_count = 16;

	for ( i=sys_param_1b[MADD_A_CHANNEL_COUNT].val; i<MAX_CHANNEL_COUNT; i++ )
	{
		sys_param_2b[MADD_A_DL_CHANNEL1+i].val = 65535;
		sys_param_2b[MADD_A_UL_CHANNEL1+i].val = 65535;
		sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
		sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
	}

#ifdef FUNC_FPS_AVG_FP		// �������Ƶ�㰴ͨ�����԰��

	tmp = (fc_count+1)/2;

	for ( i=0; i<sys_param_1b[MADD_A_CHANNEL_COUNT].val/2; i++ )
	{
		if ( i >= tmp )		// ����������֧��16ͨ������������ر�ͨ��ʹ��
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
			continue;
		}
		
		// ȡ�����������CAƵ���
		fc = sys_param_2b[MADD_FPS_CA_FC_0+i].val;
		// A��Ƶ��ţ��뵱ǰ�����ŵ��Ų�һ������������
		if ( (fc != sys_param_2b[MADD_A_DL_CHANNEL1+i].val) || (fc != sys_param_2b[MADD_A_UL_CHANNEL1+i].val) )
		{
			sys_param_2b[MADD_A_DL_CHANNEL1+i].val = fc;
			sys_param_2b[MADD_A_UL_CHANNEL1+i].val = fc;
			module_param_chg_flag |= PCHG_A_CHANNEL;
			fpssaveflashflag=1;
		}
		// Ƶ��ʹ��
		if ( 65535!=fc )
		{
			if ( (0==sys_param_1b[MADD_A_DCH_EN1+i].val) || (0==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 1;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 1;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
		else
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
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
		if ( tmp >= fc_count )		// ����������֧��16ͨ������������ر�ͨ��ʹ��
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
			continue;
		}
		
		// ȡ�����������CAƵ���
		fc = sys_param_2b[MADD_FPS_CA_FC_0+tmp].val;
		// A��Ƶ��ţ��뵱ǰ�����ŵ��Ų�һ������������
		if ( (fc != sys_param_2b[MADD_A_DL_CHANNEL1+i].val) || (fc != sys_param_2b[MADD_A_UL_CHANNEL1+i].val) )
		{
			sys_param_2b[MADD_A_DL_CHANNEL1+i].val = fc;
			sys_param_2b[MADD_A_UL_CHANNEL1+i].val = fc;
			module_param_chg_flag |= PCHG_A_CHANNEL;
			fpssaveflashflag=1;
		}
		// Ƶ��ʹ��
		if ( 65535!=fc )
		{
			if ( (0==sys_param_1b[MADD_A_DCH_EN1+i].val) || (0==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 1;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 1;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
		else
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
	}

	if ( 0 != (module_param_chg_flag&PCHG_A_CHANNEL) )	// A��Ƶ�������иı�,����B��Ƶ��
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
		if ( i>= fc_count )		// ����������֧��16ͨ������������ر�ͨ��ʹ��
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
			continue;
		}
		
		// ȡ�����������CAƵ���
		fc = sys_param_2b[MADD_FPS_CA_FC_0+i].val;
		// A��Ƶ��ţ��뵱ǰ�����ŵ��Ų�һ������������
		if ( (fc != sys_param_2b[MADD_A_DL_CHANNEL1+i].val) || (fc != sys_param_2b[MADD_A_UL_CHANNEL1+i].val) )
		{
			sys_param_2b[MADD_A_DL_CHANNEL1+i].val = fc;
			sys_param_2b[MADD_A_UL_CHANNEL1+i].val = fc;
			module_param_chg_flag |= PCHG_A_CHANNEL;
			fpssaveflashflag=1;
		}
		// Ƶ��ʹ��
		if ( 65535!=fc )
		{
			if ( (0==sys_param_1b[MADD_A_DCH_EN1+i].val) || (0==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 1;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 1;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
		else
		{
			if ( (1==sys_param_1b[MADD_A_DCH_EN1+i].val) || (1==sys_param_1b[MADD_A_UCH_EN1+i].val) )	// ʹ��״̬�ı�
			{
				sys_param_1b[MADD_A_DCH_EN1+i].val = 0;
				sys_param_1b[MADD_A_UCH_EN1+i].val = 0;
				module_param_chg_flag |= PCHG_A_CHANNEL;
				fpssaveflashflag=1;
			}
		}
	}

#if ( B_NETWORK_TYPE==NET_DIVE )	// B�ηּ�������ͬ������
	if ( 0 != (module_param_chg_flag&PCHG_A_CHANNEL) )	// A��Ƶ�������иı�
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
		sys_work_info |= SYSTEM_FLAG_SET_RE_SFC;	// �ñ�־λ,�㲥����RE��Ƶ��		
		SaveSysParamToFlash();
	}

//	sys_work_info |= SYSTEM_FLAG_SET_RE_SFC;	// �ñ�־λ,�㲥����RE��Ƶ��

#endif	// #FUNC_FPS_AUTO_SET

#endif	// #FUNC_FREQ_POINT_SEARCH_EN
}

/*************************************************************
Name: FPS_SaveResultToSysParam          
Description: ���������������������
Input: void
Return: void
**************************************************************/
void FPS_SaveResultToSysParam( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UINT16 fc_set[16];
	UCHAR8 fc_id=0;
	UCHAR8 i, j;
	FLOAT32 gain_in;		// ǰ��ģ������ = ǰ�˱������-�����˲�������Gcic-ǰ�˲�������Gcmps
	INT32 fc_power;
	CHAR8 tmp;
	
	gain_in = CALC_GAIN(FpgaReadRegister(FPGA_REG_A_FG_CMPS));	// ǰ�˲�������Gcmps
	gain_in = FPGA_REC_GFNOM - fpga_dgcic_a - gain_in;	// ǰ��ģ������

	TRACE_INFO("fps_st.tch_count=%d\r\n",fps_st.tch_count );
	
	for ( i=0; (i<fps_st.tch_count)&&(fc_id<sys_param_1b[MADD_A_CHANNEL_COUNT].val); i++ )
	{
		fc_set[fc_id++] = fps_st.tch_lst[i];
		TRACE_INFO("fc_id0 = %d\r\n",fc_id);  
		TRACE_INFO("fps_st.tch_lst[%d]= %d\r\n",i,fps_st.tch_lst[i] );
	}

	if (1==pbcch_inf.valid)	// PBCCH��Ϣ��Ч
	{
		if ( (1==pbcch_inf.pbcch_support)&&(1==pbcch_inf.pbcch_fc_valid) )		// ��PBCCHƵ��
		{
			for ( i=0; i<fc_id; i++ )		// ���������ظ�
			{
				if ( fc_set[i] == pbcch_inf.pbcch_arfcn )
				{
					break;
				}
			}
			if ( i>=fc_id )		// ���ظ�����뵽Ƶ���б���
			{
				fc_set[fc_id++] = pbcch_inf.pbcch_arfcn;
				TRACE_INFO("fc_id1 = %d\r\n",fc_id);  
			}
		}

		if ( 1==pbcch_inf.edge_support )	// PBCCH��ʾ��ǰ֧��EDGEƵ��
		{
			for ( i=0; (i<fps_st.edge_count)&&(fc_id<sys_param_1b[MADD_A_CHANNEL_COUNT].val); i++ )	// ����EDGEƵ��
			{
				for ( j=0; j<fc_id; j++ )	// ���������ظ�
				{
					if ( fc_set[j] == fps_st.edge_lst[i] )
					{
						break;
					}
				}
				if ( j>=fc_id )		// ���ظ�����뵽Ƶ���б���
				{
					fc_set[fc_id++] = fps_st.edge_lst[i];
					TRACE_INFO("fc_id2 = %d\r\n",fc_id);  
				}
			}
		}
	}

	// ��Ƶ����Ϣ���µ��������������
	sys_param_2b[MADD_FPS_BCCH_FC_M].val = fps_st.bcch_use.fc;	// ������BCCH
	fc_power = (INT32)(CALC_POWER( fps_st.bcch_use.power ) - gain_in);	// �����빦��dbm = AD����-ǰ��ģ������G_in
	if ( fc_power < -120)
	{
		tmp = -120;
	}
	else
	{
		tmp = fc_power;
	}
	sys_param_1b[MADD_FPS_BCCH_POW_M].val = (UCHAR8)tmp;		// ������BCCH����
	// ����BCCH��Ϣ
	for ( i=0, j=0; (i<FPS_BCCH_MAX)&&(j<6); i++ )
	{
		tmp = -120;		// ��ʼ������ֵΪ-120dbm
		if ( i<fps_st.bcch_count)
		{
			if ( fps_st.bcch_lst[i].fc == fps_st.bcch_use.fc )	continue;	// �б�BCCH�뵱ǰ���õ�BCCHһ�£���������BCCH
			
			sys_param_2b[MADD_FPS_BCCH_FC_1+j].val = fps_st.bcch_lst[i].fc;	// ������������BCCH
			sys_param_2b[MADD_FPS_CID_1+j].val = fps_st.bcch_lst[i].cid;	// ����BCCH��Ӧ��CID
			fc_power = (INT32)(CALC_POWER( fps_st.bcch_lst[i].power ) - gain_in);	// �����빦��dbm = AD����-ǰ��ģ������G_in
			if ( fc_power >= -120)
			{
				tmp = fc_power;	// ����ֵ����-120dbm�ű��棬��ֹ�������
			}
			sys_param_1b[MADD_FPS_BCCH_POW_1+j].val = (UCHAR8)tmp;		// ����BCCH����
		}
		else
		{
			sys_param_2b[MADD_FPS_BCCH_FC_1+j].val = 65535;	// ��ЧBCCH
			sys_param_2b[MADD_FPS_CID_1+j].val = 0;				// ����BCCH��Ӧ��CID��Ч
			sys_param_1b[MADD_FPS_BCCH_POW_1+j].val = (UCHAR8)tmp;		// ����BCCH����
		}
		j++;		// ��С��BCCH����+1
	}
	// CA��Ϣ
	sys_param_1b[MADD_FPS_CA_COUNT].val = fc_id;		// ��Ч�ŵ���
	
	TRACE_INFO("fc_id3s = %d\r\n",fc_id);  
	
	  
	for ( i=0; i<16; i++ )  
	{
		if ( i<fc_id)
		{
			sys_param_2b[MADD_FPS_CA_FC_0+i].val = fc_set[i];
		}
		else
		{
			sys_param_2b[MADD_FPS_CA_FC_0+i].val = 65535;		// ��ЧCA
		}
	}
	sys_param_1b[MADD_FPS_BCCH_LK_ST].val = 1;		// ����BCCH�ɹ�

	FPS_SetResultToSysFc();
#endif
}

/*************************************************************
Name: FPS_AutoChkChangeBcch          
Description: �Զ�����ʱ,����Ƿ���Ҫ������ǰ���õ�BCCH,���ݹ��������ж�
Input: void
Return: FALSE-����Ҫ����BCCH, TRUE-��Ҫ����BCCH
**************************************************************/
BOOL FPS_AutoChkChangeBcch( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
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
	if ( i>=fps_st.bcch_count )	// �����������µ�BCCH�б�,��û�е�ǰ���õ�BCCHƵ��,��Ҫ����BCCH
	{
		return b_TRUE;		// ����TRUE, ����BCCH
	}

	if ( 0==i )	// ��ǰ���õ�BCCHƵ���ǹ�����ǿ��, ����Ҫ����
	{
		return b_FALSE;		// ����FALSE, �������BCCH
	}

	// ��ǰBCCH���ʲ�����ǿ��, �ȽϹ��ʲ�ֵ
	fc_power_use = CALC_POWER( fps_st.bcch_use.power );
	fc_power_scan = CALC_POWER( fps_st.bcch_lst[0].power );
	
	if ( fc_power_use>fc_power_scan )	// ����BCCH���ʱ��ѵ��Ĵ�,�����л�
	{
		return b_FALSE;
	}
	
//	switch_thd = (CHAR8)sys_param_1b[MADD_FPS_SWITCH_THD].val;		// ��ȡ�л�����
	switch_thd = 3;		// �̶��л�����Ϊ3db
	if ( (fc_power_scan-fc_power_use)>switch_thd )	// ��������ֵ���л�
	{
		return b_TRUE;		// ����TRUE, ����BCCH
	}
	else
	{
		return b_FALSE;		// ����FALSE, �������BCCH
	}
	
#else
	return b_FALSE;
#endif	
}

/*************************************************************
Name: FPS_HandleAutoScan          
Description: Ƶ������������
Input: void
Return: void
**************************************************************/
void FPS_HandleAutoScan( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	static UCHAR8 fail_count = 0;
	static UCHAR8 switch_chk = 0;
	static UCHAR8 bcch_index = 0;			// ������BCCH���
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
		FPS_ResetResultParam();	// ��λ�������
		FPS_AutoStartBcch();
		fail_count = 0;
		fps_st.auto_state = FPS_AUTO_ST_BCCH;
		break;

	case FPS_AUTO_ST_BCCH:
		if ( (0==fps_st.bcch_count)||(FPS_ERR_NONE!=fps_st.err_st) )	// �д�����Ҳ���BCCHƵ��
		{
			FPS_AutoStartBcch();		// ��������
		}
		else		// BCCH�������
		{
			fail_count = 0;
			bcch_index = 0;		// ��λBCCH���,�ӹ������ĵ�һ��BCCH��ʼ
			
			if ( 65535!=sys_param_2b[MADD_FPS_BCCH_LK_SET].val )		// ʹ��BCCH��Ƶ����
			{
				for ( bcch_index=0; bcch_index<fps_st.bcch_count; bcch_index++ )	// �ڽ���б��в���Ŀ��BCCH
				{
					if ( sys_param_2b[MADD_FPS_BCCH_LK_SET].val == fps_st.bcch_lst[bcch_index].fc )
					{
						break;	// �ҵ�������ѭ��
					}
				}
				
				if ( bcch_index >= fps_st.bcch_count )	// ��BCCH����б����Ҳ���ָ����Ƶ��BCCH
				{
					fps_st.auto_state = FPS_AUTO_ST_BCCH;
					FPS_AutoStartBcch();		// ��������BCCH
					break;
				}
			}

			if ( 0!=sys_param_2b[MADD_FPS_CID_LK_SET].val )		// ʹ��CID��Ƶ����
			{
				if ( 65535!=sys_param_2b[MADD_FPS_BCCH_LK_SET].val )		// ʹ��BCCH��Ƶ����
				{
					if ( fps_st.bcch_lst[bcch_index].cid != sys_param_2b[MADD_FPS_CID_LK_SET].val )	// ������BCCH��Ӧ��CIDֵ��Ŀ��CIDֵ��ƥ��
					{
						fps_st.auto_state = FPS_AUTO_ST_BCCH;
						FPS_AutoStartBcch();		// ��������BCCH
						break;
					}
				}
				else
				{
					for ( bcch_index=0; bcch_index<fps_st.bcch_count; bcch_index++ )	// �ڽ���б��в���Ŀ��CID
					{
						if ( sys_param_2b[MADD_FPS_CID_LK_SET].val == fps_st.bcch_lst[bcch_index].cid )
						{
							break;	// �ҵ�������ѭ��
						}
					}

					if ( bcch_index >= fps_st.bcch_count )	// �ڽ���б����Ҳ���ָ����Ƶ��CID
					{
						fps_st.auto_state = FPS_AUTO_ST_BCCH;
						FPS_AutoStartBcch();		// ��������BCCH
						break;
					}
				}
			}

			FPS_TchScanRun(fps_st.bcch_lst[bcch_index].fc, 60);		// ����ѡ��Ƶ������TCH����
			fps_st.auto_state = FPS_AUTO_ST_TCH;	// ״̬ת��: ����TCH
		}
		break;

#if 0
	case FPS_AUTO_ST_BCCH:
		if ( (0==fps_st.bcch_count)||(FPS_ERR_NONE!=fps_st.err_st) )	// �д�����Ҳ���BCCHƵ��
		{
			FPS_AutoStartBcch();		// ��������
		}
		else		// BCCH�������
		{
			fail_count = 0;
			bcch_index = 0;		// ��λBCCH���,�ӹ������ĵ�һ��BCCH��ʼ
			
			FPS_CidScanRun(fps_st.bcch_lst[bcch_index].fc);	// ����ѡ��Ƶ������TCH_CID����
			fps_st.auto_state = FPS_AUTO_ST_SCAN_CID;		// ״̬ת��: ����CID
		}
		break;

	case FPS_AUTO_ST_SCAN_CID:		// ����CID
		fps_st.time_out--;
		if ( 0==(BM_SCAN_AREA_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// ����δ���
		{
			if ( fps_st.time_out>0 )	// �ȴ���ʱ����
			{
				break;
			}
			else		// ��ʱ
			{
				fps_st.bcch_lst[bcch_index].cid = 0;		// CID��Ч
			}
		}
		else		// CID�������
		{
			fps_st.bcch_lst[bcch_index].cid = FpgaReadRegister( FPGA_REG_AREA_INFO );	// ��ȡС��CID��Ϣ
		}
		
		bcch_index++;	// �л���һ��BCCH
		if ( bcch_index < fps_st.bcch_count )	
		{
			FPS_CidScanRun(fps_st.bcch_lst[bcch_index].fc);		// ������һ��BCCH��CID��Ϣ
			break;
		}

		// BCCH�б��е�CIDȫ���������
		bcch_index = 0;	// Ĭ�ϲ��ù�������BCCH
		
		if ( 65535!=sys_param_2b[MADD_FPS_BCCH_LK_SET].val )		// ʹ��BCCH��Ƶ����
		{
			for ( bcch_index=0; bcch_index<fps_st.bcch_count; bcch_index++ )	// �ڽ���б��в���Ŀ��BCCH
			{
				if ( sys_param_2b[MADD_FPS_BCCH_LK_SET].val == fps_st.bcch_lst[bcch_index].fc )
				{
					break;	// �ҵ�������ѭ��
				}
			}
			
			if ( bcch_index >= fps_st.bcch_count )	// ��BCCH����б����Ҳ���ָ����Ƶ��BCCH
			{
				fps_st.auto_state = FPS_AUTO_ST_BCCH;
				FPS_AutoStartBcch();		// ��������BCCH
				break;
			}
		}

		if ( 0!=sys_param_2b[MADD_FPS_CID_LK_SET].val )		// ʹ��CID��Ƶ����
		{
			if ( 65535!=sys_param_2b[MADD_FPS_BCCH_LK_SET].val )		// ʹ��BCCH��Ƶ����
			{
				if ( fps_st.bcch_lst[bcch_index].cid != sys_param_2b[MADD_FPS_CID_LK_SET].val )	// ������BCCH��Ӧ��CIDֵ��Ŀ��CIDֵ��ƥ��
				{
					fps_st.auto_state = FPS_AUTO_ST_BCCH;
					FPS_AutoStartBcch();		// ��������BCCH
					break;
				}
			}
			else
			{
				for ( bcch_index=0; bcch_index<fps_st.bcch_count; bcch_index++ )	// �ڽ���б��в���Ŀ��CID
				{
					if ( sys_param_2b[MADD_FPS_CID_LK_SET].val == fps_st.bcch_lst[bcch_index].cid )
					{
						break;	// �ҵ�������ѭ��
					}
				}

				if ( bcch_index >= fps_st.bcch_count )	// �ڽ���б����Ҳ���ָ����Ƶ��CID
				{
					fps_st.auto_state = FPS_AUTO_ST_BCCH;
					FPS_AutoStartBcch();		// ��������BCCH
					break;
				}
			}
		}

		FPS_TchScanRun(fps_st.bcch_lst[bcch_index].fc, 0);		// ����ѡ��Ƶ������TCH����
		fps_st.auto_state = FPS_AUTO_ST_TCH;	// ״̬ת��: ����TCH
		break;
#endif

	case FPS_AUTO_ST_TCH:
		if ( (FPS_ERR_NONE==fps_st.err_st)&&(fps_st.tch_count>0) )	// TCH�����ɹ����
		{
			fail_count = 0;
			fps_st.switch_count++;	// BCCH�л������ۼ�
			// ��¼��ǰ������BCCH��Ϣ
			fps_st.bcch_use.fc = fps_st.bcch_lst[bcch_index].fc;
			fps_st.bcch_use.power = fps_st.bcch_lst[bcch_index].power;
			fps_st.bcch_use.precision = fps_st.bcch_lst[bcch_index].precision;
			// ����Ƶ��
			FPS_SaveResultToSysParam();	
			// ��������BCCH����,�������
			fps_st.auto_state = FPS_AUTO_ST_CHK_BCCH;
			switch_chk = 0;
			FPS_AutoStartBcch();	
		}
		else		// TCH����ʧ��
		{
			fail_count++;
			if ( fail_count<3 )		// ����3��,���ɹ���������BCCH
			{
				FPS_TchScanRun(fps_st.bcch_lst[bcch_index].fc, 0);	// ��������
			}
			else
			{
				if ( sys_param_2b[MADD_FPS_CID_LK_SET].val != 0 )		// ������CID��������,����TCHʧ������������BCCH
				{
					fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ���״̬,��������
					break;
				}

				if ( sys_param_2b[MADD_FPS_BCCH_LK_SET].val != 65535 )	// ��������Ƶ����,����TCHʧ������������BCCH
				{
					fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ���״̬,��������
					break;
				}
				
				bcch_index++;	// �л�����һ��BCCH���н���
				if ( bcch_index >= fps_st.bcch_count )	// �б��е�BCCH������һ��,û��һ�����Խ���TCH��,��������BCCH
				{
					fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ���״̬,��������
				}
				else		
				{
					FPS_TchScanRun( fps_st.bcch_lst[bcch_index].fc, 60 );	// ��������
				}
			}
		}
		break;

	case FPS_AUTO_ST_CHK_BCCH:
		if (FPS_ERR_NONE==fps_st.err_st)	// BCCH�����޴������
		{
			fail_count = 0;	// ����������
			
			for ( i=0; i<fps_st.bcch_count; i++ )		// �ڵ�ǰBCCH��������б��в�������ʹ�õ�BCCH
			{
				if ( fps_st.bcch_lst[i].fc == fps_st.bcch_use.fc )	// �ڵ�ǰBCCH�б����ҵ������õ�BCCH
				{
					break;	// ����ѭ��������BCCH
				}
			}

			if ( i<fps_st.bcch_count )	// �ҵ�����ʹ�õ�BCCH����������TCH
			{
				fps_st.auto_state = FPS_AUTO_ST_CHK_TCH;	// ״̬��->���½���ҵ���ŵ�
				FPS_TchScanRun( fps_st.bcch_use.fc, 60 );	// ����ҵ���ŵ�
				break;			// ����
			}
		}
		// BCCH����������
		fail_count++;		// ��������ۼ�
		if ( fail_count > 3 )		// ����3������BCCHʧ��
		{
			fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ���״̬,��������
		}
		else
		{
			FPS_AutoStartBcch();		// �д�����Ҳ���BCCHƵ��,��������
		}
		break;

	case FPS_AUTO_ST_CHK_TCH:
		if ( (FPS_ERR_NONE==fps_st.err_st)&&(fps_st.tch_count>0) )	// TCH�����ɹ����
		{
			fail_count = 0;	// ����������
			
			FPS_SaveResultToSysParam();		// ����ҵ��Ƶ����Ϣ

			tmp = 0;
			if ( 0!=sys_param_2b[MADD_FPS_CID_LK_SET].val )	// ����CID��������
			{
				if ( sys_param_2b[MADD_FPS_CID].val != sys_param_2b[MADD_FPS_CID_LK_SET].val )	// ��ǰBCCH��CID��Ŀ��CID��һ��
				{
					tmp = 1;			// ������Ҫ�л���־
				}
			}
			else		// û������CID��������
			{
				if (65535==sys_param_2b[MADD_FPS_BCCH_LK_SET].val)		// û����BCCH��Ƶ����, ���ݹ����ж��Ƿ���Ҫ�л�BCCH
				{
					if ( b_TRUE == FPS_AutoChkChangeBcch() )		// ��Ҫ�л������ʸ����BCCH
					{
						tmp = 1;		// ������Ҫ�л���־
					}
				}
			}

			if ( 0==tmp )		// ��������жϲ���Ҫ�л�BCCH
			{
				switch_chk = 0;	// ���BCCH�л��������ֵ
			}
			else		// ��������ж���Ҫ�л�BCCH
			{
				switch_chk++;	// ��Ҫ�л�����+1
			}
			
			if ( switch_chk > 3 )	// ����3�μ����������Ҫ�л�, ��λ״̬��, ׼���л�
			{
				fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ���״̬,��������
			}
			else		// ���л�BCCH, ��������BCCH����,�������
			{
				fps_st.auto_state = FPS_AUTO_ST_CHK_BCCH;
				FPS_AutoStartBcch();	
			}
		}
		else		// TCH����ʧ��
		{
			fail_count++;
			if ( fail_count<3 )		// ����3��,���ɹ������¿�ʼBCCH����
			{
				FPS_TchScanRun( fps_st.bcch_use.fc, 0 );	// ��������
			}
			else
			{
				fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ���״̬,��������
			}
		}
		break;

	case FPS_AUTO_ERR_RANGE:
		break;

	default:
		fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// δ֪״̬,��������
	}

#endif	
}

/*************************************************************
Name:FPS_BcchFunc          
Description: BCCH����������
Input: void
Return: void
**************************************************************/
void FPS_BcchFunc( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	static UCHAR8 bcch_index;
	UINT32 fpga_fw;
	WTD_CLR;
	switch( fps_st.scan_st )
	{
	case FPS_SCAN_ST_BCCH:
		if ( 0!=(BM_SCAN_BCCH_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )		// �ж�BCCH�����Ƿ����
		{
			FPS_HandleBcch();
			if ( fps_st.bcch_count>0 )
			{
				fps_st.scan_st = FPS_SCAN_ST_CID;
				bcch_index = 0;
				// дƵ��,����CID����
				fpga_fw = FPS_CalcFpgaFreqWord(SYS_A_FLAG, fps_st.bcch_lst[bcch_index].fc);
				FPGA_ENABLE_WRITE;
				//FpgaWriteRegister(FPGA_REG_BCCH_DF, fpga_fw );	
	            FpgaWriteRegister(FPGA_REG_BCCH_DF_1, (UINT16)(((fpga_fw>>12)&0x3FFF)|((fpga_fw&0x80000000)>>16)));// дƵ��[25:12]λ,��������
	            FpgaWriteRegister(FPGA_REG_BCCH_DF_2, (UINT16)(fpga_fw&0xFFF));	// дƵ��[11:0]λ,��������				
				FPGA_DISABLE_WRITE;
				fps_st.time_out = 30;				// ��ʱ:30��(����ʱĬ�ϲ����޸�)
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
		if ( 0==(BM_SCAN_AREA_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// ����δ���
		{
			if ( fps_st.time_out>0 )	// �ȴ���ʱ����
			{
				fps_st.time_out--;
				break;
			}
			else		// ��ʱ
			{
				fps_st.bcch_lst[bcch_index].cid = 0;		// CID��Ч
			}
		}
		else		// CID�������
		{
			fps_st.bcch_lst[bcch_index].cid = FpgaReadRegister( FPGA_REG_AREA_INFO );	// ��ȡС��CID��Ϣ
			FpgaReadRegister(FPGA_REG_AREA_INFO);		// �ն�2��
			FpgaReadRegister(FPGA_REG_AREA_INFO);
		}
		
		bcch_index++;	// �л���һ��BCCH
		if ( bcch_index < fps_st.bcch_count )	
		{
			// ������һ��BCCH��CID��Ϣ
			fpga_fw = FPS_CalcFpgaFreqWord(SYS_A_FLAG, fps_st.bcch_lst[bcch_index].fc);
			FPGA_ENABLE_WRITE;
			//FpgaWriteRegister( FPGA_REG_BCCH_DF, fpga_fw );// дƵ��,��������
			FpgaWriteRegister(FPGA_REG_BCCH_DF_1, (UINT16)(((fpga_fw>>12)&0x3FFF)|((fpga_fw&0x80000000)>>16)));// дƵ��[25:12]λ,��������
	        FpgaWriteRegister(FPGA_REG_BCCH_DF_2, (UINT16)(fpga_fw&0xFFF));	// дƵ��[11:0]λ,��������
			FPGA_DISABLE_WRITE;
			fps_st.time_out = 30;				// ��ʱ:30��(����ʱĬ�ϲ����޸�)
		}
		else		// BCCH�б��CIDȫ��������ɣ������Ч��bcch��Ϣ
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
		if ( 0==fps_st.auto_scan_en )	// ���Զ�ģʽ, �ϱ��������
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
Description: TCH����������
Input: void
Return: void
**************************************************************/
void FPS_TchFunc( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	UCHAR8 tmp;
	UCHAR8 report_flag = 0;

	if ( fps_st.time_out>0 )	// ����ʱ
	{
		fps_st.time_out--;
	}

	switch( fps_st.scan_st )
	{
	case FPS_SCAN_ST_TCH:
		if ( 0!=(BM_SCAN_TCH_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )		// �ж�TCH�����Ƿ����
		{
			FPS_HandleTch();
			fps_st.scan_st = FPS_SCAN_ST_PBCCH;
			if ( 0==fps_st.auto_scan_en )	// ���Զ�ģʽ, �ϱ��������
			{
				FPS_SendReport();
			}
		}
		else
		{
			if ( 0==fps_st.time_out )		// ��ʱ, ����TCH����
			{
				fps_st.err_st = FPS_ERR_TCH_TIMEOUT;
			}
		}
		break;

	case FPS_SCAN_ST_PBCCH:
		if ( 0!=(BM_SCAN_PBCCH_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )		// �ж�PBCCH�����Ƿ����
		{
			FPS_HandlePbcch();
			fps_st.scan_st = FPS_SCAN_ST_EDGE;	// PBCCH�������,ת��EDGE��ѯ״̬
			if ( 0==fps_st.auto_scan_en )	// ���Զ�ģʽ, �ϱ��������
			{
				FPS_SendReport();
			}
			break;
		}

	case FPS_SCAN_ST_EDGE:
		if ( 0!=(BM_SCAN_EDGE_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// �鿴�Ƿ���������EDGEƵ��
		{
			tmp = fps_st.edge_count;
			FPS_HandleEdge();
			if ( 0==fps_st.auto_scan_en )	// ���Զ�ģʽ, �ϱ��������
			{
				if ( tmp != fps_st.edge_count )	// ���µ�EDGEƵ��
				{
					FPS_SendReport();
				}
			}
		}
		break;
		
	default:
		fps_st.scan_st = FPS_SCAN_ST_DONE;
	}

	if ( 0==fps_st.time_out )	// �ز�ҵ���ŵ�����ʱ�����
	{
		// ��ȡEDGEƵ����Ϣ
		if ( 0!=(BM_SCAN_EDGE_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// �鿴�Ƿ���������EDGEƵ��
		{
			FPS_HandleEdge();
		}
		
		if ( 0!=(BM_SCAN_AREA_END&FpgaReadRegister(FPGA_REG_RFC_SCAN_ST)) )	// ��ȡ��С����Ϣ,���²���
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
		if ( 0==fps_st.auto_scan_en )	// ���Զ�ģʽ, �ϱ��������
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
Description: ����BCCHɨ��
Input: [force_run: 1-ǿ��ִ��] [wait_time: ��ʱ����] [wait_time:��ʱʱ��]
Return: ���:0-�����ɹ���1-����ִ��BCCHɨ�裬2-����ִ��TCHɨ�裬3-�д���
**************************************************************/
UCHAR8 FPS_ManualStartBcch( UCHAR8 force_run, UINT16 wait_time )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	if ( 1==fps_st.auto_scan_en )
	{
		fps_st.err_st = FPS_ERR_IN_AUTO_MODE;
		FPS_SendReport();
		return 0;
	}
	
	if ( (0!=fps_st.fps_run)&&(0==force_run) )	// ��ǰ����ɨ��,��ǿ��ִ��
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
Description: ����TCHɨ��
Input: [force_run: 1-ǿ��ִ��] [bcch_fc: Ƶ���] [wait_time:��ʱʱ��]
Return: ���:0-�����ɹ���1-����ִ��BCCHɨ�裬2-����ִ��TCHɨ�裬3-�д���
**************************************************************/
UCHAR8 FPS_ManualStartTch(UINT16 bcch_fc, UCHAR8 force_run, UINT16 wait_time )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	if ( 1==fps_st.auto_scan_en )
	{
		fps_st.err_st = FPS_ERR_IN_AUTO_MODE;
		FPS_SendReport();
		return 0;
	}

	if ( (0!=fps_st.fps_run)&&(0==force_run) )	// ��ǰ����ɨ��,��ǿ��ִ��
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
Description: ��ȡ�Զ�����ʹ��״̬
Input: void
Return: TRUE-ʹ��, FALSE-����
**************************************************************/
BOOL FPS_GetAutoScanEn( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	if ( 1==fps_st.auto_scan_en )
	{
		return b_TRUE;
	}
	else
	{
		return b_FALSE;
	}
#else
	return b_FALSE;	// ��ʹ��Ƶ���������ܷ��ؽ���״̬
#endif
}

/*************************************************************
Name:FPS_EnableAutoScan          
Description: �����Զ�����ʹ��
Input: void
Return: void
**************************************************************/
void FPS_EnableAutoScan( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������

	if (1==sys_param_1b[MADD_FPS_AUTO_SCAN].val)
	{
		if ( 0==fps_st.auto_scan_en )	// ���ֶ�����Զ�
		{
			fps_st.auto_scan_en = 1;	// �����Զ�����ʹ��
			fps_st.fps_run = 0;		    // ֹͣ��ǰ����   
			fps_st.scan_st = FPS_SCAN_ST_DONE;	// �޸�״̬��־Ϊ���
			fps_st.err_st  = FPS_ERR_NONE;		// ��������־
			fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ��λ�Զ�����״̬��
            //fps_st.fc_count = 0;
			fps_st.tch_count    = 0;		// ����TCHƵ�����
			fps_st.edge_count   = 0;		// ����EDGE����
			fps_st.switch_count = 0;	    // ����Ƶ���л�����
		}
	}
	else  // ���Զ����ֶ� 
	{
		if ( 1==fps_st.auto_scan_en )	
		{
			fps_st.auto_scan_en = 0;	// ȡ���Զ�����ʹ��
			fps_st.fps_run = 0;		// ֹͣ��ǰ����
			fps_st.scan_st = FPS_SCAN_ST_DONE;	// �޸�״̬��־Ϊ���
			fps_st.err_st = FPS_ERR_NONE;		// ��������־
			fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ��λ�Զ�����״̬��
		}
	}
	// ʹ��״̬�����򱣳�ԭ��
#endif
}

/*************************************************************
Name:FPS_SetParam          
Description: Ƶ��������ʼ��
             ����Ƶ����������ز�����FPGA��

Input: void
Return: void
**************************************************************/
void FPS_SetParam( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
//	if ( fps_st.range_sel != sys_param_1b[MADD_FPS_RFRANGE_SEL].val )	// �޸���Ƶ�η�Χ
//	{
		fps_st.range_sel = sys_param_1b[MADD_FPS_RFRANGE_SEL].val;	// ����Ƶ��ѡ��Χֵ
		
		if ( b_TRUE==FPS_CheckParam(SYS_A_FLAG) )
		{
			FPS_SetScanFc(SYS_A_FLAG); 
		}
//	}
	if ( fps_st.bcch_lock!= sys_param_2b[MADD_FPS_BCCH_LK_SET].val )	// �޸�����ƵĿ��BCCHƵ��
	{
		fps_st.bcch_lock = sys_param_2b[MADD_FPS_BCCH_LK_SET].val;	// ������ƵĿ��BCCHƵ��
		
		if ( 1==fps_st.auto_scan_en )
		{
			// ��������BCCH
			fps_st.fps_run = 0;		// ֹͣ��ǰ����
			fps_st.scan_st = FPS_SCAN_ST_DONE;	// �޸�״̬��־Ϊ���
			fps_st.err_st  = FPS_ERR_NONE;		// ��������־
			fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;	// ��λ�Զ�����״̬��
		}
	}

	FPS_EnableAutoScan();
	
#endif
}


/*************************************************************
Name:FPS_Init          
Description: Ƶ��������ʼ��
Input: void
Return: void
**************************************************************/
void FPS_Init( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������
	FPS_ResetResultParam();		// ��λ����״̬
	fps_st.auto_scan_en = (1==sys_param_1b[MADD_FPS_AUTO_SCAN].val) ? 1 : 0;
	fps_st.auto_state = FPS_AUTO_ST_NEW_SCAN;
	fps_st.fps_run = 0;
	fps_st.bcch_use.fc = 0;
	fps_st.bcch_use.power = 0;
	fps_st.bcch_use.precision = 0;
	fps_st.range_sel = sys_param_1b[MADD_FPS_RFRANGE_SEL].val;	// Ƶ�η�Χѡ��
	FPS_CheckParam(SYS_A_FLAG);
#endif
}

/*************************************************************
Name:FPS_MainFunc          
Description: Ƶ������������1��ִ��һ��
Input: void
Return: void
**************************************************************/
void FPS_MainFunc( void )
{
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// ����Ƶ����������

	if ( 0==fps_st.fps_run )	// ��ǰ��ֹͣ����
	{
		FPS_HandleAutoScan();	// �Զ�����Զ�����״̬
		return;
	}

	// �����������
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



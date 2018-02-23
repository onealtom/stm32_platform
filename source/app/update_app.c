/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :update_app.c
* Description :�������������غ���
* Version     :v0.1
* Author      :RJ
* Date        :2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			��ʼ�汾
**************************************************************/
#include "Header.h"

extern _T_ERROR last_err;
extern UCHAR8 sys_temp_buff[SYS_TMP_BUFF_SIZE];
//extern UINT32 sys_work_info;

UINT32 next_pkt_no;
UINT32 update_fw_len;
UINT32 update_pkt_count;
UINT16 update_pak_max_len=0;
UINT32 erase_start_page=0;

/*************************************************************
Name:CheckIsMcuFw
Description: ����Ƿ���MCU����
Input:
	len: ���ݳ���
Output:void
Return:���ط��͵����ݸ���
**************************************************************/
UCHAR8 CheckIsMcuFw( UINT32 * pEntry) 
{
	if ( (pEntry[0] & 0x2FFE0000 ) != 0x20000000) return 0;
	if ( pEntry[7]!=0xAA55AA55 ) return 0;
	if ( pEntry[8]!=0x33CC33CC ) return 0;
	if ( pEntry[9]!=0xA5C35A3C ) return 0;
	if ( pEntry[10]!=0xFF00FF00 ) return 0;
	
	if ( pEntry[13]!=0xEC61EC00 ) return 0;			// REC������ر��־

	return 1;
}


/*************************************************************
Name:FpgaChecksum
Description:FPGA����У���
Input:�����ļ����ܳ���          
Output:void         
Return:У��ֵ  
**************************************************************/
UINT32 FpgaChecksum(UINT32 len)
{
	UCHAR8 *p_flash_page = sys_temp_buff;
	UINT16 page_index;
	UINT32 sum=0;
	UINT16 i;

	if ( update_fw_len>=(FLASH_PAGE_SIZE*FLASH_FPGA_BLOCK_COUNT) )		
	{
		// FPGA���򳬹�һ�����Ŀռ䣬��ʹ��˫���ݹ��ܣ�Ĭ�ϴ��ڵ�һ��
		page_index = FLASH_FPGA_PAGE_START1+1;
	}
	else
	{
		// ˫���ݹ��ܣ�����洢�ڷǵ�ǰ���
		if ( FPGA_LOAD_BLOCK2 == fpga_load_block )
		{
			page_index = FLASH_FPGA_PAGE_START1+1;
		}
		else
		{
			page_index = FLASH_FPGA_PAGE_START2+1;
		}
	}
	
	while( len>0 )
	{
		i = len>FLASH_PAGE_SIZE ? FLASH_PAGE_SIZE : len;
		len -= i;
		FlashRead( page_index, 0, p_flash_page,FLASH_PAGE_SIZE );
		for ( ; i>0; i-- )
		{
			sum += p_flash_page[i-1];
		}
		page_index ++;
	}

	return (sum&0xffff);
}

/*************************************************************
Name:UpdateStart          
Description: ������ʼ��׼������������
Input:
	type: ��������
	len: ���������ܳ���
	pkt_count: �������ݰ����ܸ���
Output: void
Return: 
	1 - ׼������
	0 - ����
**************************************************************/
UINT32 UpdateStart( UINT32 type, UINT32 len, UINT32 pkt_count )
{
	if (( len < 528 )||(pkt_count<=1))
	{
		return 0;
	}
#if 0	
	if ( UPDATE_TYPE_FPGA == type )
	{
		if ( (pkt_count * UPDATE_PKT_MAX_LEN) >= (FLASH_PAGE_SIZE * FLASH_FPGA_BLOCK_COUNT * 2) )
		{
			return 0;	// �������ݳ��ȳ����洢��Χ
		}
	}
	else
	{
		if ( (pkt_count * UPDATE_PKT_MAX_LEN) > MCU_FW_MAX_LEN )
		{
			return 0;	// �������ݳ��ȳ����洢��Χ
		}
	}
#else
	if ( UPDATE_TYPE_FPGA == type )
	{
		if ( (pkt_count * UPDATE_PKT_MAX_LEN) >= (FLASH_PAGE_SIZE * FLASH_FPGA_BLOCK_COUNT *2) )
		{
			return 0;	// �������ݳ��ȳ����洢��Χ
		}
	}
	else
	{
		if ( (pkt_count * UPDATE_PKT_MAX_LEN) > MCU_FW_MAX_LEN )
		{
			return 0;	// �������ݳ��ȳ����洢��Χ
		}
	}
#endif	
	// �������б�־
	if ( UPDATE_TYPE_FPGA == type )
	{
		sys_work_info |= SYSTEM_FLAG_FPGA_UPDATE;	//����FPGA����������־
	}
	else
	{
		sys_work_info |= SYSTEM_FLAG_MCU_UPDATE;	//����FPGA����������־
	}
	
	// ������Ϣ
	next_pkt_no = 1;
	update_fw_len = len;
	update_pkt_count = pkt_count;

	return 1;
}

/*************************************************************
Name:FpgaUpdateEnd          
Description: FPGA������ʼ��׼������������
Input:
	len: ���������ܳ���
	pkt_count: �������ݰ����ܸ���
Output: void
Return: 
	1 - ׼������
	0 - ����
**************************************************************/
UINT32 FpgaUpdateEnd( UINT32 checksum, UINT32 * p_err )
{
	UINT32 checksum_val;
		UCHAR8 fpga_load_info[8];
		UCHAR8 blank_buff[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff,0xff, 0xff };
		
		if (0==(sys_work_info & SYSTEM_FLAG_FPGA_UPDATE))
		{
			return 0;
		}
	
		checksum_val = FpgaChecksum(update_fw_len);
		if ( ( (next_pkt_no-1)==update_pkt_count )&&(checksum_val==checksum) )
		{
			//����дFPGA������±�־
			fpga_load_info[0] = 0xEB;
			fpga_load_info[1] = 0x90;
			fpga_load_info[2] = update_fw_len&0xff;
			fpga_load_info[3] = (update_fw_len>>8)&0xff;
			fpga_load_info[4] = (update_fw_len>>16)&0xff;
			fpga_load_info[5] = (update_fw_len>>24)&0xff;
			// д�������Ϣ
			if ( update_fw_len>=(FLASH_PAGE_SIZE*FLASH_FPGA_BLOCK_COUNT) )		
			{
				// FPGA���򳬹�һ�����Ŀռ䣬��ʹ��˫���ݹ��ܣ�Ĭ�ϴ��ڵ�һ��
				FlashEraseSectors(FLASH_FPGA_PAGE_START1/16,FLASH_FPGA_PAGE_START1/16);
	
				FlashWrite( FLASH_FPGA_PAGE_START1, 0,fpga_load_info, 8, 1);
	
				TRACE_INFO("end pake 0 !\r\n");
	
			}
			else
			{
				// ˫���ݹ��ܣ�����洢�ڷǵ�ǰ���
				if ( FPGA_LOAD_BLOCK2 == fpga_load_block )
				{
					printf("block2\r\n");
					//FlashWriteOnepage( FLASH_FPGA_START1, blank_buff, 8, 1);
					FlashEraseSectors(FLASH_FPGA_PAGE_START1/16,FLASH_FPGA_PAGE_START1/16);
					FlashWrite( FLASH_FPGA_PAGE_START1,0, fpga_load_info, 8, 1);
					// �����ɵ�FPGA������Ϣ
					FlashEraseSectors(FLASH_FPGA_PAGE_START2/16,FLASH_FPGA_PAGE_START2/16);
					FlashWrite( FLASH_FPGA_PAGE_START2, 0,blank_buff, 8, 0);
	
					TRACE_INFO("end pake 1 !\r\n");
	
				}
				else
				{
					printf("block1\r\n");
					FlashEraseSectors(FLASH_FPGA_PAGE_START2/16,FLASH_FPGA_PAGE_START2/16);
					//FlashWriteOnepage( FLASH_FPGA_START2, blank_buff, 8, 1);
					FlashWrite( FLASH_FPGA_PAGE_START2,0, fpga_load_info, 8, 1);
					// �����ɵ�FPGA������Ϣ
					FlashEraseSectors(FLASH_FPGA_PAGE_START1/16,FLASH_FPGA_PAGE_START1/16);
					FlashWrite( FLASH_FPGA_PAGE_START1, 0,blank_buff, 8, 0);
	
					TRACE_INFO("end pake 2 !\r\n");
	
				}
			}
	
			return 1;
		}
		else
		{
			*p_err++ = checksum_val;
			return 0;
		}

}

/*************************************************************
Name:FpgaUpdateStart          
Description: FPGA������ʼ��׼������������
Input:
	len: ���������ܳ���
	pkt_count: �������ݰ����ܸ���
Output: void
Return: 
	1 - ׼������
	0 - ����
**************************************************************/
UINT32 SaveFpgaUpdatePkt( UINT32 pkt_no, UINT32 len, UCHAR8* p_dat, UINT32* p_err )
{
	UINT16 page;
	UINT32 wr_len;

	if ( (0==(sys_work_info & SYSTEM_FLAG_FPGA_UPDATE))||(0==pkt_no)||(len>UPDATE_PKT_MAX_LEN) )
	{
		return 0;
	}

	if ( pkt_no == next_pkt_no )
	{
		if ( update_fw_len>=(FLASH_PAGE_SIZE*FLASH_FPGA_BLOCK_COUNT) )		
		{
			// FPGA���򳬹�һ�����Ŀռ䣬��ʹ��˫���ݹ��ܣ�Ĭ�ϴ��ڵ�һ��
			page = FLASH_FPGA_PAGE_START1+1;
		}
		else
		{
			// ˫���ݹ��ܣ�����洢�ڷǵ�ǰ���
			if ( FPGA_LOAD_BLOCK2 == fpga_load_block )
			{
				page = FLASH_FPGA_PAGE_START1+1;
			}
			else
			{
				page = FLASH_FPGA_PAGE_START2+1;
			}
		}
		page += ( (pkt_no-1)*( (UPDATE_PKT_MAX_LEN+FLASH_PAGE_SIZE-1)/FLASH_PAGE_SIZE ) );
		
		while ( len>0 )
		{
			wr_len = (len>FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : len;
			FlashWrite( page, 0,p_dat, wr_len, 1);	// д������
			page++;
			p_dat += wr_len;		// ָ�����
			len -= wr_len;			// ����ʣ�೤��
		}
		next_pkt_no++;
		return 1;
	}
	else
	{
		*p_err = next_pkt_no;
		return 0;
	}
}

/*************************************************************
Name:FpgaChecksum
Description:FPGA����У���
Input:�����ļ����ܳ���          
Output:void         
Return:У��ֵ  
**************************************************************/
UINT32 McuChecksum(UINT32 len)
{
	UCHAR8 *p_flash_page = sys_temp_buff;
	UINT16 page_index;
	UINT32 sum=0;
	UINT16 i;

	page_index = FLASH_MCU_SW_START_PAGE+1;
	while( len>0 )
	{
		i = (len>FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : len;
		len -= i;
		FlashRead( page_index, 0, p_flash_page ,FLASH_PAGE_SIZE);
		for ( i; i>0; i-- )
		{
			sum += p_flash_page[i-1];
		}
		page_index ++;
	}

	return (sum&0xffff);
}


/*************************************************************
Name:McuUpdateEnd          
Description: FPGA������ʼ��׼������������
Input:
	len: ���������ܳ���
	pkt_count: �������ݰ����ܸ���
Output: void
Return: 
	1 - ׼������
	0 - ����
**************************************************************/
UINT32 McuUpdateEnd( UINT32 checksum, UINT32 * p_err )
{
	UINT32 checksum_val;
	UCHAR8 mcu_load_info[8];
	UCHAR8 blank_buff[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	
	if (0==(sys_work_info & SYSTEM_FLAG_MCU_UPDATE))
	{
		return 0;
	}

	checksum_val = McuChecksum(update_fw_len);
	if ( ( next_pkt_no==(update_pkt_count+1) )&&(checksum_val==checksum) )
	{
		//����дFPGA������±�־
		mcu_load_info[0] = 0xEB;
		mcu_load_info[1] = 0x90;
		mcu_load_info[2] = update_fw_len&0xff;
		mcu_load_info[3] = (update_fw_len>>8)&0xff;
		mcu_load_info[4] = (update_fw_len>>16)&0xff;
		mcu_load_info[5] = (update_fw_len>>24)&0xff;
		// д�������Ϣ
		// �����ɵ�FPGA������Ϣ
		FlashEraseSectors(FLASH_MCU_SW_START_PAGE/16,FLASH_MCU_SW_START_PAGE/16);
		//FlashWriteOnepage( FLASH_MCU_SW_START_PAGE, blank_buff, 8, 1 );
		FlashWrite( FLASH_MCU_SW_START_PAGE,0, mcu_load_info, 8, 1 );

		return 1;
	}
	else
	{
		*p_err++ = checksum_val;
		return 0;
	}
}

/*************************************************************
Name:SaveMcuUpdatePkt          
Description: FPGA������ʼ��׼������������
Input:
	len: ���������ܳ���
	pkt_count: �������ݰ����ܸ���
Output: void
Return: 
	1 - ׼������
	0 - ����
**************************************************************/
UINT32 SaveMcuUpdatePkt( UINT32 pkt_no, UINT32 len, UCHAR8* p_dat, UCHAR8* p_err )
{
	UINT32 page =( FLASH_MCU_SW_START_PAGE+1);
	UINT32 wr_len,i,j;
	UCHAR8 *p_flash_page = sys_temp_buff;

	TRACE_INFO("SaveMcuUpdatePkt\r\n");


	if ((0==(sys_work_info & SYSTEM_FLAG_MCU_UPDATE))|| (0==pkt_no)||(len>UPDATE_PKT_MAX_LEN) )
	{
		return 0;
	}


	TRACE_INFO("SaveMcuUpdatePkt_pkt_no=[%d]\r\n",pkt_no);
	if ( pkt_no == next_pkt_no )
	{
		page += (pkt_no-1)*( (UPDATE_PKT_MAX_LEN+FLASH_PAGE_SIZE-1)/FLASH_PAGE_SIZE );
		while ( len>0 )
		{
			TRACE_INFO("SaveMcuUpdatePkt_page=[%d],len=[%d]\r\n",page,len);
			WTD_CLR;
			
			wr_len = (len>FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : len;
			FlashWrite( page,0, p_dat, (UINT16)wr_len,2);	// д������
			page++;
			p_dat += wr_len;		// ָ�����
			len -= wr_len;		// ����ʣ�೤��
		}
		next_pkt_no++;
		return 1;
	}
	else
	{
		*p_err = next_pkt_no;
		return 0;
	}
}


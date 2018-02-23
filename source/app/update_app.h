/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :update_app.h
* Description :�������������غ���ͷ�ļ�
* Version     :v0.1
* Author      :RJ
* Date        :2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			��ʼ�汾
**************************************************************/
#ifndef _UPDATE_APP_H_
#define _UPDATE_APP_H_

#define UPDATE_TYPE_FPGA		0
#define FPGA_FW_MAX_LEN		4*1024*1024		// FPGA������󳤶�:4MB
#define FPGA_FW_MAX_PKT		7400			// FPGA�������ݰ�������: 4096 = FPGA_FW_MAX_LEN / FLASH_PAGE_SIZE

#define UPDATE_TYPE_MCU		1
#define MCU_FW_MAX_LEN		(256-32)*1024	// ������256KB, bootռ��32k
#define MCU_FW_MAX_PKT		512				// MCU�������ݰ�������: 4096 = FPGA_FW_MAX_LEN / FLASH_PAGE_SIZE

#define UPDATE_PKT_MAX_LEN	update_pak_max_len//1056			// һ�����������������ֽ���
extern UINT16 update_pak_max_len;
extern UINT32 erase_start_page;

UCHAR8 CheckIsMcuFw( UINT32 * pEntry) ;
UINT32 FpgaChecksum(UINT32 len);
UINT32 UpdateStart( UINT32 type, UINT32 len, UINT32 pkt_count );
UINT32 FpgaUpdateEnd( UINT32 checksum, UINT32 * p_err );
UINT32 SaveFpgaUpdatePkt( UINT32 pkt_no, UINT32 len, UCHAR8* p_dat, UINT32* p_err );
UINT32 McuChecksum(UINT32 len);
UINT32 McuUpdateEnd( UINT32 checksum, UINT32 * p_err );
UINT32 SaveMcuUpdatePkt( UINT32 pkt_no, UINT32 len, UCHAR8* p_dat, UCHAR8* p_err );

#endif

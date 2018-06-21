/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :update_app.h
* Description :软件升级处理相关函数头文件
* Version     :v0.1
* Author      :RJ
* Date        :2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			初始版本
**************************************************************/
#ifndef _UPDATE_APP_H_
#define _UPDATE_APP_H_

#define UPDATE_TYPE_FPGA		0
#define FPGA_FW_MAX_LEN		4*1024*1024		// FPGA程序最大长度:4MB
#define FPGA_FW_MAX_PKT		7400			// FPGA升级数据包最大个数: 4096 = FPGA_FW_MAX_LEN / FLASH_PAGE_SIZE

#define UPDATE_TYPE_MCU		1
#define MCU_FW_MAX_LEN		(256-32)*1024	// 总容量256KB, boot占用32k
#define MCU_FW_MAX_PKT		512				// MCU升级数据包最大个数: 4096 = FPGA_FW_MAX_LEN / FLASH_PAGE_SIZE

#define UPDATE_PKT_MAX_LEN	update_pak_max_len//1056			// 一个升级包传输的最大字节数
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

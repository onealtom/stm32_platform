/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :crc8.c
* Description :CRC8
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			≥ı º∞Ê±æ
**************************************************************/
#ifndef _CRC_H
#define _CRC_H

#define POLYNOMIAL	0x1021			//X^15+X^12+X^5+1

UINT16 CalCrc16(UCHAR8 * buff,UINT16 len,UINT16 crc);

#endif

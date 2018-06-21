#include <stdint.h>
#include <string.h>
#include "Header.h"

void hexdump(const void *_data, size_t size) {
	char lt = 0x2E;
	char text[17] ;
	/*我们要hexdump的内容的起始地址由*_data指定，大小为size*/ 
	const uint8_t *data = (const uint8_t *)_data;
	/*获取起始地址位置*/
	size_t offset = 0;
	/*偏移量初始化为0，也就是第一行最左边将显示0x0000*/
	while (offset < size) {
		printf("\r0x%04X  ", offset);
		/*0xx  以四位十六进制的方式显示偏移量，如果不足四位的在左边补零，如0x0000--0x0010*/  
		  size_t n = size - offset;
		if (n > 16) {
			n = 16;
		}

		for (size_t i = 0; i < 16; ++i) {
			if (i == 8) {
			printf(" ");
			}

			if (offset + i < size) {
				printf("%02X ", data[offset + i]);  /*x以两位十六进制的方式输出内容*/
			} else {
				printf("   "); /*如果数据已经不足16个，则以空格表示，以便对齐*/
			}
		}
		/*for循环又来输出中间部分十六进制显示的内容，不多于16个一行，8个和8个之间空两格*/
		printf(" ");

		for (size_t i = 0; i < n; ++i) {
			if ( (data[offset + i]>=32) && (data[offset + i]<=126) ) {//ASCII范围
				printf("%c", data[offset + i]);
			} else {
				printf("%c",lt);
			}
		}

		/*%c以字符的形式输出内容，如果是能够显示的字符，则显示，否则以 . 代替*/
		/*每行只显示十六个字节*/
		offset += 16;
		WTD_CLR;
		printf("\n");
	}
	printf("\n");
}

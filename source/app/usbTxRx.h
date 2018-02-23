/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :usbTxRx.h
* Description :USB 收发数据相关函数及结构;
* Version     :v0.1
* Author      :gaochanggang
* Date        :2009-07-15
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*gaochanggang		2009-07-15	v0.1			初始版本
**************************************************************/
#ifndef _USBTXRX_H
#define _USBTXRX_H
//#include "system.h"

// usb max buffer.
//#define USB_RX_BUFFER_LEN   2048
#define DATABUFFERSIZE		64

#if 0
// packet head define.
struct S_USB_PACKET_HEAD
{
	UINT16 s_syn;				// 2 byte 同步标志
	UCHAR8 c_protocol_ver;		// 1 byte 协议版本号
	UCHAR8 c_machine_no;			// 1 byte 整机编号
	UCHAR8 c_module_addr;		// 1 byte 模块地址
	UCHAR8 c_cmd_id;				// 1 byte 命令字
	UCHAR8 c_ack;				// 1 byte 校验标志 [7 Byte]

	CHAR8 data;						// 命令数据指针；[FPGA 1056+8]
	UINT16 s_crc;				// 2 byte; 校验码
	UCHAR8 c_end_sign;			// 1 byte; 结束标志
}__attribute__((packed));
typedef struct S_USB_PACKET_HEAD T_USB_PACKET_HEAD;

// 
typedef CHAR8 (*P_USB_CMD_HANDLE_FUNC)(UCHAR8 *, INT32, void *p_arg);
// USBCmdIdHandle struct.
struct S_USB_CMD_HANDLE
{
    UCHAR8 cmd_id;
    P_USB_CMD_HANDLE_FUNC p_func;
    void *p_arg;
}__attribute__((packed));
typedef struct S_USB_CMD_HANDLE T_USB_CMD_HANDLE;


// structuce for usb rece data.
struct S_USB_RECE_DAT
{
    UCHAR8 dat[USB_RX_BUFFER_LEN];   // data buffer.
    UCHAR8 * p_dat;                  // point to data buffer.
    T_USB_PACKET_HEAD *p_head;       // packet header.
    void *p_void;                   // cmd header.
    INT32 lenth;             // have received data size.
    INT32 count;              // current packet no.
}__attribute__((packed));
typedef struct S_USB_RECE_DAT T_USB_RECE_DAT;
#endif

extern volatile UCHAR8 usb_rx_end;
extern volatile UCHAR8 usb_tx_end;

// functions declaration.
void USBChgStatus();
void USBStartTrans(void);
void UsbSendMsgPkt( UINT32 msg_length, UCHAR8 * p_msg_dat  );
UCHAR8 SaveUsbMsgData(UCHAR8 * p_rx_dat, UINT16 data_len);
void UsbDataReceived(unsigned int unused,
                            unsigned char status,
                            unsigned int received,
                            unsigned int remaining);

void UsbTransFinished(unsigned int p_argument,
                            unsigned char status,
                            unsigned int transferred,
                            unsigned int remaining);

//UCHAR8 UsbReadRemainData();


void TestUsbWr();

#if 0
CHAR8 USBReceHandleSetAdReg(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleGetAdReg(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleReadWFpgaReg(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleSetFpgaReg(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleStepGain(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleFpgaUpdata(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleSetPriPara(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleGetPriPara(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleMaxGain(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleStepGain(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleWriteTable(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleSetPara(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleGetPara(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleWriteFreTable(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleGetFpgaPara(UCHAR8 *data,UINT16 data_len, void *p_arg);

CHAR8 USBReceHandleReadFpgaReg(UCHAR8 *data,UINT16 data_len, void *p_arg);


// dpd relate
CHAR8 USBReceHandleSbramRead(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleSbramWrite(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleDpdCommand(UCHAR8 *data,UINT16 data_len, void *p_arg);
CHAR8 USBReceHandleReadPower(UCHAR8 *data,UINT16 data_len, void *p_arg);

#endif

#endif //:~_USBTXRX_H



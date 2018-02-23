/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :usbTxRx.c
* Description :USB 收发数据相关处理函数;
* Version     :v0.1
* Author      :gaochanggang
* Date        :2009-07-15
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*gaochanggang		2009-07-15	v0.1			初始版本
**************************************************************/
#include "Header.h"

//#include "usbTxRx.h"
//#include "app.h"
//#include <stdio.h>
//#include <usb/device/core/usbd.h>

#define MIN(a, b)       (((a) < (b)) ? (a) : (b))

//int flag_err = 0;

// global dat buffer. [in-USBD_UDP.C]
extern T_USB_RECE_DAT g_rx_dat;
extern T_USB_RECE_DAT g_tx_dat;
extern UCHAR8 usb_time_out;
extern volatile UINT32 sys_work_info;
//extern UCHAR8 usbBuffer[DATABUFFERSIZE];

//extern UCHAR8 sys_rece_buf[RECE_MAX];
//extern UCHAR8 sys_trans_buf[TRAN_MAX];
//extern UINT16 fpga_write_bak[FPGA_W_REG_MAX];
//extern UCHAR8 powe_cn_flag;
extern UCHAR8 fre_bound;
extern UCHAR8 hard_ware_v;



#define USB_PACKET_HEAD_SYNC 0Xdf4e

/// State of USB, for suspend and resume
UCHAR8 USBState = STATE_IDLE;

/// Buffer for storing incoming USB data.
UCHAR8 usbBuffer[DATABUFFERSIZE+DATABUFFERSIZE];
//UCHAR8 usbExBuff[DATABUFFERSIZE];

UINT16 usb_remain_len;
UINT16 usb_remain_start;

volatile UINT16 usb_rx_len;
volatile UCHAR8 usb_rx_end=1;		// USB接收到数据标志
volatile UCHAR8 usb_tx_end=1;		// USB数据已发送标志

UCHAR8 port_open=0;

/*************************************************************
Name:    USBChgStatus       
Description: USB状态转换；
Input:void          
Output:void
Return:void         
**************************************************************/
void USBChgStatus()
{
	UCHAR8 i;
	static UCHAR8 usb_state=0;

//	if ( bDeviceState != CONFIGURED ) return;
	if ( 0==IsUsbConfigured() )
	{
		sys_work_info |= SYSTEM_FLAG_USB_RX_END;
		usb_rx_end = 0;
		sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);
		usb_tx_end = 0;
		return;
	}

	if ( 0==IsUsbConnected() )
	{
		//TRACE_INFO("USB DISCONNECT!!!!\r\n");
		USB_Init();
		sys_work_info |= SYSTEM_FLAG_USB_RX_END;
		usb_rx_end = 0;
		sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);
		usb_tx_end = 0;
		usb_state = 1;
		return;
	}
		
	if ( usb_rx_end==1 )
	{
		sys_work_info |= SYSTEM_FLAG_USB_RX_END;
		usb_rx_end = 0;
	}

	if ( usb_tx_end==1 )
	{
		sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);
		usb_tx_end = 0;
	}

#if 0

	if (USBD_GetState() < USBD_STATE_CONFIGURED) 
	{
		if ( 0 == usb_state )
		{
			sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);	//清除数据待发送标志
			//CDCDSerialDriver_Initialize();
			usb_state = 1;
			//port_open = 0;
			//USBD_Connect();
		}
		return;
	}
	
	if ( 1 == usb_state ) 
	{
	       TRACE_DEBUG("usb connected\r\n");			
	       //CDCDSerialDriver_Read(usbBuffer,DATABUFFERSIZE,	(TransferCallback) UsbDataReceived,0);
		//使能接收新的数据
		if ( USBD_STATUS_SUCCESS == CDCDSerialDriver_Read(usbBuffer, DATABUFFERSIZE, (TransferCallback)UsbDataReceived, 0) )
		{
			sys_work_info |= SYSTEM_FLAG_USB_WAIT_RX;
		}
//		sys_work_info &= (~SYSTEM_FLAG_USB_ONCE_RX);		
		usb_state = 0;
		return;
	}
#if 0
	if ( 0 != CDCDSerialDriver_GetCarrierActivated() )		// USB串口设备已打开
	{
		port_open = 1;
	}
	else
	{
		if ( 0!=port_open )
		{
			port_open = 0;
			//CDCDSerial_Init();
		}
	}
#endif
	if (USBD_GetState() < USBD_STATE_CONFIGURED) return;
		
	if ( usb_rx_end==1 )
	{
		sys_work_info |= SYSTEM_FLAG_USB_RX_END;
		usb_rx_end = 0;
	}

	if ( usb_tx_end==1 )
	{
		sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);
		usb_tx_end = 0;
	}

	if( USBState == STATE_SUSPEND ) 
	{
		//LowPowerMode();
		USBState = STATE_IDLE;
		TRACE_DEBUG("suspend!\r\n");
	}

	if( USBState == STATE_RESUME )
	{
	        // Return in normal MODE
	        // NormalPowerMode();
	        USBState = STATE_IDLE;
	        TRACE_DEBUG("resume !\r\n");
	}
#endif
}


/*************************************************************
Name:USBRxHandle          
Description:接收数据包处理
Input:void            
Output:void         
Return:void         
**************************************************************/
void USBRxHandle()
{
	UINT16 i;
//	UCHAR8 tmp;
//	TRACE_INFO("Reacive Packet!\r\n");

	if ( 0 != (sys_work_info & SYSTEM_FLAG_USB_PKT_UNSEND) )
	{ 
		return;   
	} 

	//TRACE_INFO("USBRxHandle\r\n");
	//if ( 0 != CDCDSerialDriver_GetCarrierActivated() )
	{
		MsgHandle( PC_ABS_FP, PC_ABS_RE, PC_ABS_REE,g_rx_dat.lenth, g_rx_dat.dat );
//		MsgHandle_usb( PC_ABS_FP, PC_ABS_RE, g_rx_dat.lenth, g_rx_dat.dat );
	}

	sys_work_info &= (~SYSTEM_FLAG_USB_RECE);
	g_rx_dat.lenth = 0;

}

#if 0
/*************************************************************
Name:SaveUsbMsgData          
Description: 转义保存USB收到的数据
Input:
	p_rx_dat: USB接收缓冲区指针
	data_len: 数据长度
Output:void         
Return:void         
**************************************************************/
UCHAR8 SaveUsbMsgData(UCHAR8 * p_rx_dat, UINT16 data_len)
{
	static UCHAR8 usb_pkt_flag = 0x00;
	UINT16 i;
	UINT16 msg_len;
	UCHAR8 tmp;
	UCHAR8 * p_msg_dat = g_rx_dat.dat;

	msg_len = g_rx_dat.lenth;
	usb_remain_len = data_len;
	for ( i=0; i<data_len; i++)
	{
		tmp = *p_rx_dat++;
		usb_remain_len--;

		if ( 0 == usb_pkt_flag)
		{
			//等待包分隔标志
			if ( MSG_PKT_FLAG == tmp )
			{
				usb_pkt_flag = 1;
				msg_len = 0;
			}
		}
		else
		{
			if ( 2 == usb_pkt_flag )
			{
				//前一个收到的字符是转义字符
				if ( 0x4D == tmp )
				{
					p_msg_dat[msg_len] = 0x4E;
					msg_len++;
				}
				else if ( 0x5D == tmp )
				{
					p_msg_dat[msg_len] = 0x5E;
					msg_len++;
				}
				usb_pkt_flag = 1;
			}
			else if ( MSG_PKT_FLAG == tmp )
			{
				//收到了分隔标志
				if ( msg_len >= MSG_PKT_SIZE_MIN )
				{
					//收到完整数据包
					usb_pkt_flag = 0;
					//更新长度
					g_rx_dat.lenth = msg_len;
					//设置需要处理标志位
					sys_work_info |= SYSTEM_FLAG_USB_RECE;
					//保存下一个读出数据的位置
					usb_remain_start = i+1;
					return 1;
				}
				else
				{
					//以新收到这个作为包头，前面收到的数据都去掉
					msg_len = 0;
				}
			}
			else
			{
				if ( MSG_SHIFT_FLAG == tmp )
				{
					usb_pkt_flag = 2;	
				}
				else
				{
					usb_pkt_flag = 1;
					p_msg_dat[msg_len] = tmp;
					msg_len++;
					//长度检查
					if ( msg_len > USB_RX_BUFFER_LEN )
					{
						//数据包长度超过了允许长度，丢弃
						usb_pkt_flag = 0;
						msg_len = 0; 
					}
				}
			}
		}
	}
	g_rx_dat.lenth = msg_len;
	usb_remain_len = 0;
	return 0;
}
#endif

/*************************************************************
Name:GetUsbMsgPkt          
Description: 转义保存USB收到的数据
Input:
	p_rx_dat: USB接收缓冲区指针
	data_len: 数据长度
Output:void         
Return:void         
**************************************************************/
UINT16 GetUsbMsgPkt(UCHAR8 * p_rx_dat, UINT16 data_len)
{
	static UCHAR8 usb_pkt_flag = 0x00;
//	UINT16 i;
	UINT16 msg_len;
	UCHAR8 tmp;
	UCHAR8 * p_msg_dat = g_rx_dat.dat;

	WTD_CLR;
	if ( 0 != (sys_work_info & SYSTEM_FLAG_USB_RECE ) )
	{
		return data_len;
	}

	msg_len = g_rx_dat.lenth;

	while( data_len>0 )
	{
		tmp = *p_rx_dat++;
		data_len--;

		if ( 0 == usb_pkt_flag)
		{
			//等待包分隔标志
			if ( MSG_PKT_FLAG == tmp )
			{
				usb_pkt_flag = 1;
				msg_len = 0;
			}
		}
		else
		{
			if ( 2 == usb_pkt_flag )
			{
				//前一个收到的字符是转义字符
				if ( 0x4D == tmp )
				{
					p_msg_dat[msg_len] = 0x4E;
					msg_len++;
				}
				else if ( 0x5D == tmp )
				{
					p_msg_dat[msg_len] = 0x5E;
					msg_len++;
				}
				usb_pkt_flag = 1;
			}
			else if ( MSG_PKT_FLAG == tmp )
			{
				//收到了分隔标志
				if ( msg_len >= MSG_PKT_SIZE_MIN )
				{
					//收到完整数据包
					//设置需要处理标志位
					//MsgHandle( PC_ABS_FP, PC_ABS_NODE, msg_len, p_msg_dat );
					//msg_len = 0;
					usb_pkt_flag = 0;
					sys_work_info |= SYSTEM_FLAG_USB_RECE;
					break;
				}
				else
				{
					//以新收到这个作为包头，前面收到的数据都去掉
					msg_len = 0;
				}
			}
			else
			{
				if ( MSG_SHIFT_FLAG == tmp )
				{
					usb_pkt_flag = 2;	
				}
				else
				{
					usb_pkt_flag = 1;
					p_msg_dat[msg_len] = tmp;
					msg_len++;
					//长度检查
					if ( msg_len >= USB_RX_BUFFER_LEN )
					{
						//数据包长度超过了允许长度，丢弃
						usb_pkt_flag = 0;
						msg_len = 0; 
					}
				}
			}
		}
	}
	g_rx_dat.lenth = msg_len;
	WTD_CLR;

	return data_len;
}




//------------------------------------------------------------------------------
/// Callback invoked when data has been received on the USB.
//------------------------------------------------------------------------------
void UsbDataReceived(unsigned int unused,
                            unsigned char status,
                            unsigned int received,
                            unsigned int remaining)
{
//	UINT16 data_len = 0;
//	TRACE_INFO_WP("U > Usb Read CallBack!\r\n");
		
    // Check that data has been received successfully
    	if (status == USBD_STATUS_SUCCESS)
	{		
		usb_rx_len = MIN(received, DATABUFFERSIZE);
#if 0
		while ( remaining>0 )
		{
			usbBuffer[usb_rx_len++] = (UCHAR8)AT91C_BASE_UDP->UDP_FDR[CDCDSerialDriverDescriptors_DATAOUT];
			remaining--;
		}
#endif
    	}
	else
	{
		usb_rx_len = 0;
	}
	//sys_work_info |= SYSTEM_FLAG_USB_RX_END;
	usb_rx_end = 1;
	
	WTD_CLR;

}
		
void UsbGetReceivedData()
{
	UINT16 data_len;

	if ( usb_rx_len >0 )
	{
		usb_rx_len=GetUsbMsgPkt(usbBuffer, usb_rx_len);
		// usb_rx_len = 0;
		//if ( 0 != (sys_work_info & SYSTEM_FLAG_USB_RECE ) )
		//{
		//	return;
		//}
	}

	if ( 0 != (sys_work_info & SYSTEM_FLAG_USB_RECE ) )
	{
		return;
	}

	// 清除等待接收数据标志
	sys_work_info &= (~SYSTEM_FLAG_USB_WAIT_RX);

	// 清除标志，重新使能接收
	sys_work_info &= (~SYSTEM_FLAG_USB_RX_END);
	
	// CDCDSerialDriver_Read(usbBuffer, DATABUFFERSIZE, (TransferCallback)UsbDataReceived, 0);

}

void UsbStartReceive()
{
	sys_work_info |= SYSTEM_FLAG_USB_WAIT_RX;
	
	//使能接收新的数据
	if ( USBD_STATUS_SUCCESS != CDCDSerialDriver_Read(usbBuffer, DATABUFFERSIZE, (TransferCallback)UsbDataReceived, 0) )
	{
		sys_work_info &= (~SYSTEM_FLAG_USB_WAIT_RX);
	}
	
}


/*************************************************************
Name:UsbSendMsgPkt
Description:从USB口发送一个消息包
Input:
	msg_length: 数据包长度
	p_msg_dat: 数据指针
Output:void         
Return:void         
**************************************************************/
void UsbSendMsgPkt( UINT32 msg_length, UCHAR8 * p_msg_dat  )
{
	UINT32 i,len;
	UCHAR8 tmp;

	WTD_CLR;
	//写入消息包起始标志
	len = 0;
	g_tx_dat.dat[len++] = MSG_PKT_FLAG;
	g_tx_dat.dat[len++] = MSG_PKT_FLAG;
	//写入消息包数据(包括CRC)，对转义字符进行转换
	for ( i=0; i<msg_length; i++ )
	{
		tmp = * p_msg_dat++;
		if ( 0x4E == tmp )
		{
			//转义0x4E
			g_tx_dat.dat[len++] = MSG_SHIFT_FLAG;
			g_tx_dat.dat[len++] = 0x4D;
		}
		else if ( 0x5E == tmp )
		{
			//转义0x5D
			g_tx_dat.dat[len++] = MSG_SHIFT_FLAG;
			g_tx_dat.dat[len++] = 0x5D;
		}
		else
		{
			//普通数据
			g_tx_dat.dat[len++] = tmp;
		}
	}
	
	//写入消息包结束标志
	g_tx_dat.dat[len++] = MSG_PKT_FLAG;
	
	if ( len>0 )
	{
		//写入转义后的消息包长度(包括起始和结束字符)
		g_tx_dat.lenth = len;

		//设置USB发送等待标志
		sys_work_info |= SYSTEM_FLAG_USB_PKT_UNSEND;
		
		//发送消息包
		USBStartTrans();
	}

}

void CheckUsbConnect()
{
#if 0
	if ((USBD_GetState() < USBD_STATE_CONFIGURED)||
		( 0 == CDCDSerialDriver_GetCarrierActivated() ))
	{
		//sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);
		usb_tx_end = 1;
		TRACE_INFO("CDC Device Is Unactive!\r\n");
		return;
	}
#endif
}

/*************************************************************
Name:USBStartTrans          
Description:开始发送
Input:void            
Output:void         
Return:void         
**************************************************************/
void USBStartTrans(void)
{
#if 1
	int i = 0;

	WTD_CLR;

//	if ( bDeviceState != CONFIGURED )
	if ( 0==IsUsbConfigured() )
	{
		//sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);
		usb_tx_end = 1;
		//TRACE_INFO("CDC Device Is Unactive!\r\n");
		return;
	}
	
	//设置USB发送等待标志
	//sys_work_info |= SYSTEM_FLAG_USB_PKT_UNSEND;
	
	// 启动发送
	//TRACE_INFO("USB Start Trans.");
	if (USBD_STATUS_SUCCESS == CDCDSerialDriver_Write(g_tx_dat.dat, g_tx_dat.lenth, (TransferCallback)UsbTransFinished, 0) )
	{
		// 开始发送
		//TRACE_INFO_WP(".");
	}
	else
	{
		// 发送失败
		//sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);
		usb_tx_end = 1;
		TRACE_INFO_WP("Fail.");
	}

	WTD_CLR;

#endif
}

/*************************************************************
Name:UsbTransFinished       
Description:USB数据发送完成回调函数
Input:
	p_argument: 送入的参数指针
	status: 状态
	transferred: 发送的数据长度
	remaining: 仍未发送的数据长度
Output:void         
Return:void         
**************************************************************/
void UsbTransFinished(unsigned int p_argument,
                            unsigned char status,
                            unsigned int transferred,
                            unsigned int remaining)
{
	//sys_work_info &= (~SYSTEM_FLAG_USB_PKT_UNSEND);
		usb_tx_end = 1;

	//TRACE_INFO_WP( "USBD Trans End" );
	if ( USBD_STATUS_SUCCESS == status )
	{
		//TRACE_INFO_WP("-OK")
	}
	else
	{
		//TRACE_INFO_WP("-Fail:%d", status );
	}
	//TRACE_INFO_WP( ", %d Sended %d Left\r\n", transferred, remaining );
}



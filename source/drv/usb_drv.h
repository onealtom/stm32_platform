/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : hw_config.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USB_DRV_H_
#define _USB_DRV_H_

/* Includes ------------------------------------------------------------------*/
//#include "usb_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define MASS_MEMORY_START     0x04002000
#define BULK_MAX_PACKET_SIZE  0x00000040

#define USART_RX_DATA_SIZE   2048

/// Indicates the operation was successful.
#define USBD_STATUS_SUCCESS             0
/// Endpoint/device is already busy.
#define USBD_STATUS_LOCKED              1
/// Operation has been aborted.
#define USBD_STATUS_ABORTED             2
/// Operation has been aborted because the device has been reset.
#define USBD_STATUS_RESET               3

typedef void (*TransferCallback)(void *pArg,
                                 unsigned char status,
                                 unsigned int transferred,
                                 unsigned int remaining);

/// Describes an ongoing transfer on a UDP endpoint.
typedef struct 
{
    /// Pointer to a data buffer used for emission/reception.
    char             *pData;
    /// Number of bytes which have been written into the UDP internal FIFO buffers.
    volatile int     buffered;
    /// Number of bytes which have been sent/received.
    volatile int     transferred;
    /// Number of bytes which have not been buffered/transferred yet.
    volatile int     remaining;
    /// Optional callback to invoke when the transfer completes.
    volatile TransferCallback fCallback;
    /// Optional argument to the callback function.
    void             *pArgument;
} Transfer;

// usb max buffer.
#define USB_RX_BUFFER_LEN   2048

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

extern Transfer RxTransfer;
extern Transfer TxTransfer;

extern uint8_t  USB_Tx_State;
extern uint8_t  USB_Rx_State;


/* Exported functions ------------------------------------------------------- */
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void USART_Config_Default(void);
bool USART_Config(void);
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes);
void USART_To_USB_Send_Data(void);
void Handle_USBAsynchXfer (void);
void Get_SerialNum(void);

unsigned char CDCDSerialDriver_Write(void * pData,
                                     unsigned int dLength,
                                     TransferCallback fCallback,
                                     void * argument);
unsigned char CDCDSerialDriver_Read(void *pData,
                                    unsigned int dLength,
                                    TransferCallback fCallback,
                                    void *argument);
void InitUsb();
void UsbConnect();
void UsbDisConnect();
UCHAR8 IsUsbConnected();
UCHAR8 IsUsbConfigured();


/* External variables --------------------------------------------------------*/

#endif  /*__HW_CONFIG_H*/
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

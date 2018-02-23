/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司
     
*************************************************************
文件名：   ADC_DRV_H_
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： ADC_DRV_H_的底层驱动头文件 
函数列表： 
修改日期： 
        1.日期:      2010年08月05日  
          作者：     韦瑞锦 
          修改内容： 原版
        2.日期:      2012年04月17日   
          作者：     邓子谦
          修改内容： 微型光钎V02 
**************************************************************/
#ifndef _GLOBAL_DRV_H_
#define _GLOBAL_DRV_H_

#define Bank1_SRAM1_ADDR    ((uint32_t)0x60000000)
#define Bank1_SRAM2_ADDR    ((uint32_t)0x64000000)
//20151126逻辑加载直接操作寄存器地址
#define GPIOD_SFR_BASE_SET           ((unsigned long *)0x40011410)
#define GPIOD_SFR_BASE_RESET         ((unsigned long *)0x40011414)

#define GPIOB_SFR_BASE_SET           ((unsigned long *)0x40010C10)
#define GPIOB_SFR_BASE_RESET           ((unsigned long *)0x40010C14)

#define SYS_TMP_BUFF_SIZE		(1056+512)

// variable
extern volatile unsigned char * p_ext_8;
extern volatile unsigned short * p_ext_16;
extern volatile UINT32 sys_work_info;
extern UCHAR8 sys_temp_buff[SYS_TMP_BUFF_SIZE];
extern volatile UINT32 au_send_msg;




// 系统工作状态
#define SYSTEM_FLAG_1S_EVENT			(0x01<<0)	// 定时器1秒到时事件
#define SYSTEM_FLAG_3S_EVENT			(0x01<<1)	// 定时器3秒到时事件
#define SYSTEM_FLAG_5S_EVENT			(0x01<<2)	// 定时器5秒到时事件
#define SYSTEM_FLAG_USB_WAIT_RX		(0x01<<3)	// USB等待接收数据
#define SYSTEM_FLAG_USB_PKT_UNSEND	(0x01<<4)	// USB数据等待发送标志,发送前置位，发送完成后清零
#define SYSTEM_FLAG_USB_RECE    		(0x01<<5)  	// usb 一次数据传输结束，等待处理；
#define SYSTEM_FLAG_USB_ONCE_RX 		(0x01<<6)  	// 一次数据包中断后立即读取数据；
#define SYSTEM_FLAG_USB_RX_END		(0x01<<7)	// 从USB总线接收到一个数据帧
#define SYSTEM_FLAG_SET_RE_SFC		(1<<6)		// 广播设置RE的频点
#define SYSTEM_FLAG_MCU_UPDATE		(0x01<<9)	// MCU升级中
#define SYSTEM_FLAG_MCU_RELOAD		(0x01<<10) 	// MCU程序下载完成，重启升级
#define SYSTEM_FLAG_FPGA_UPDATE		(0x01<<11)	// FPGA升级中
#define SYSTEM_FLAG_FPGA_RELOAD		(0x01<<12)	// FPGA程序下载完成，重新加载
#define SYSTEM_FLAG_232_RECE			(0x01<<13)
#define SYSTEM_FLAG_UART_DEBUG		(0x01<<14)
//#define SYSTEM_FLAG_UART_TX_THR		(1<<15)		// 正在从串口发送透传数据
#define SYSTEM_FLAG_CHECK_ID			(0x01<<16)	// 需要检查RE的ID
#define SYSTEM_FLAG_LOW_POWER		(1<<17)	// 低功耗模式
#define SYSTEM_FLAG_ATT_ADJ			(1<<18)		// 校准状态
#define SYSTEM_FLAG_SET_RE_UPOW		(1<<19)		// 需要重新设置RE的上行功率
#define SYSTEM_FLAG_SET_RE_SYS_CFG		(1<<20)		// 需要重新设置RE的系统配置:延时、滤波器带宽等
#define SYSTEM_FLAG_SET_RE_TDSLOT	(1<<21)		// 需要重新设置RE的TD时隙模式
#define SYSTEM_INIT_END				(1<<22)		// 系统初始化结束
#define SYSTEM_FLAG_FPGA_SAVE_THR	(1<<24)		// 正在从Fpga读取透传数据
#define SYSTEM_FLAG_SOFT_RESET		(1<<25)		// 执行软件复位

#define SYSTEM_FLAG_REMOTE_UPDATE	(0x01<<26)	// FPGA升级中
#define SYSTEM_FLAG_GAIN_ADJ			(1<<27)		// 增益校准


//AU发送的消息类型
//串口工作信息
#define AU_MSG_FLAG_GET_EU_PARA			(0x01<<0)	// 获取EU参数
#define AU_MSG_FLAG_SET_IF_PARA			(0x01<<1)	// 设置参数
#define AU_MSG_FLAG_GET_IF_TOPO			(0x01<<2)	// 获取RU的TOPO
#define AU_MSG_FLAG_SET_REF_CLK_POW		(0x01<<3)	// 下发9524的参考时钟功率


void   InitExtentBus_16(void);
void   InitExtentBus_8(void);
CHAR8  FpgaLoadAll(UINT32 len);
UCHAR8 GetAD9524LD();
UCHAR8 GetAD9524Refmon();
UCHAR8 GetAD9524Status();
UCHAR8 GetDA9122LockA();
UCHAR8 GetDA9122LockB();
void   SysSoftReset();
CHAR8  GetTemperature(); 
void SentLoadDat(UCHAR8 Dat);

#endif

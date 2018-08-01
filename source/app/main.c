/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
* 
* FileName    :main.c
* Description :系统主函数
* Version     :v0.1
* Author      :RJ
* Date        :2010-03-10
* 
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			初始版本
**************************************************************/
#include "Header.h"
#include "tools.h"
#ifndef USART3_RXBUF_SIZE
	#define USART3_RXBUF_SIZE  256
#endif


extern UCHAR8 usbBuffer[DATABUFFERSIZE];
extern UCHAR8 str_pri_mcu_date[];
//extern UINT32 module_param_chg_flag;		//系统工作参数修改标志
extern UINT32 fpga_load_status;

UCHAR8 * p_mcu_date; 
UCHAR8  p_mcu_date_GUOREN[11]={'S','e','p',' ','2','9',' ','2','0','1','4'};

UCHAR8 usb_time_out;  
UCHAR8 traffic_start = 0;//开始话务量统计
// AD6649版本
 

unsigned int traceLevel = TRACE_LEVEL_DEBUG;


rxbuffer *rx_buf1;
rxbuffer *rx_buf2;
rxbuffer *capt_guy;
rxbuffer *proc_guy;
int Uart3_Sta;

void main()
{
	UINT32 tmp=0;
	uint16_t tmp16;
	UCHAR8 reset_time=0;
	int i;

	//UCHAR8 p_msg_dat[]={0x01,0x01,0x00,0x00,0x00,0x00,0xdf,0xff,0x00,0x00,'t','e','s','k','o','k','.','f','r','o','m','.','r','e','c','.','.','.','.','.','.','.','.','.'};
	//UCHAR8 p_msg_dat1[]={0xC2,0x01,0x01,0x69,0x82,0x02,0x00,0x00};
	
	// 系统初始化
	InitSystem();
	
	WTD_CLR;

	TRACE_INFO("Sys Start Run\r\n");

	UsbConnect(); 

	
	rx_buf1 = (rxbuffer*)malloc( sizeof(rxbuffer) );
	rx_buf1->p = (uint8_t*)malloc(256);
	if(rx_buf1->p==NULL)
		printf("NULL\n");
	else{
		rx_buf1->cnt=0;
	}
	rx_buf2 = (rxbuffer*)malloc(sizeof(rxbuffer));
	rx_buf2->p = (uint8_t*)malloc(256);
	if(rx_buf2->p==NULL)
		printf("NULL\n");
	else{
		rx_buf2->cnt=0;	
	}
	capt_guy = rx_buf1;
	proc_guy = rx_buf2;

	while(1)
	{ 

		if(Uart3_Sta)
		{
			if(proc_guy->cnt > 0){
				printf("\n\rcnt: %d, proc: %d \n\r",proc_guy->cnt, (proc_guy == rx_buf1)? 1: 2 );
				//hexdump(proc_guy->p, proc_guy->cnt);
				route_txframe(proc_guy->p, proc_guy->cnt);
			}
			//for(i=0; i < proc_guy->cnt ; i++ )
				//printf("%c ", proc_guy->p[i] );


			Uart3_Sta = 0;
			proc_guy->cnt=0;
		}
		
		WTD_CLR;

		// USB状态转换 
		USBChgStatus();

		if ( 1 == IsUsbConfigured() )
		{
			// 有USB数据包未发出
			if ( SYSTEM_FLAG_USB_PKT_UNSEND != (sys_work_info & SYSTEM_FLAG_USB_PKT_UNSEND) )
			{
				// 数据发出后才处理新的数据
				if ( 0!=(sys_work_info & SYSTEM_FLAG_USB_RX_END) )
				{
					UsbGetReceivedData();
				}   

				if ( 0 != (sys_work_info & SYSTEM_FLAG_USB_RECE) )
				{
					USBRxHandle();
				}  
			}

			// 接收完成，使能新的数据接收
			if ( 0 == (sys_work_info & SYSTEM_FLAG_USB_WAIT_RX) )
			{
				UsbStartReceive();
			}
		}

		if (0 != (sys_work_info & SYSTEM_FLAG_232_RECE) )
		{
			// 处理485数据包
			//TRACE_INFO("Handle 485\r\n");	
			printf("Handle 485\r\n");	
			////UartReceHandle();
			sys_work_info &= (~SYSTEM_FLAG_232_RECE);
			WTD_CLR;	
		}         

		

		// 1秒事件
		if ( SYSTEM_FLAG_1S_EVENT == (sys_work_info & SYSTEM_FLAG_1S_EVENT ))
		{
			TRACE_INFO("Handle 1S\r\n");
////			TaskManageTopo(); 
			//FpgaGetMsgPkt(); 
			sys_work_info &= (~SYSTEM_FLAG_1S_EVENT);
   
			//if ( FPGA_LDST_OK==fpga_load_status )
			//{
				FLASH_LED; 
			//}

			if ( 0!= (sys_work_info & (SYSTEM_FLAG_SOFT_RESET|SYSTEM_FLAG_MCU_RELOAD|SYSTEM_FLAG_FPGA_RELOAD)) )
			{
				reset_time++;
				if ( reset_time== 2)
				{
					__disable_irq();
					SysSoftReset();
					while(1);
				}
			}
 
			// 更新RE信息
////			UpdateReInfo(); 


			

#if 1		
			// 获取输入和输出功率
			////FpgaGetDlUlPowerA();
			//FpgaGetDlUlPowerB();
			//FpgaGetDlUlPowerC();
			//FpgaGetDlUlPowerD();			
			
			// 频点搜索
			#if defined  CLIENT_ERRICSON
			FPS_MainFunc();
			#endif
#endif	
			
			// 释放大数据缓冲 
			CheckBigBuffTimeOut();
 
		    WTD_CLR;  
			
		
		}


 
#if 1
		// 3秒事件
		if ( SYSTEM_FLAG_3S_EVENT == (sys_work_info & SYSTEM_FLAG_3S_EVENT))
		{
			
			tmp16=FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
			//printf("FPGA_REG_MSG_FIFO_ST=0x%04X\n",tmp16);
			rx_task( (uint8_t)(0x0F & tmp16 ) );
			
			TRACE_INFO("Handle 3S\r\n");
			sys_work_info &= (~SYSTEM_FLAG_3S_EVENT);
			//TRACE_INFO("fpga_load_status:%d\r\n",fpga_load_status);
			if ( FPGA_LDST_OK!=fpga_load_status )
			{
				FLASH_LED;
			}

			/*ADC处理*/
			AdcHandle();	
			//温度
////			sys_param_1b[MADD_BOARD_TEMP].val =  GetTemperature();
		}
		
		// 5秒事件
		if (SYSTEM_FLAG_5S_EVENT==(sys_work_info & SYSTEM_FLAG_5S_EVENT))
		{
			sys_work_info &= (~SYSTEM_FLAG_5S_EVENT);
//			UartReceHandleMoGetTopo(p_msg_dat,0);
//			UartReceHandleMoTransRe(p_msg_dat1,8);
			TRACE_INFO("Handle 5S\r\n");
			//FpgaSendMsgPkt( 0x00000100, 0x00000000, 28, p_msg_dat );
			//FpgaSendThrDat(); 
			//1197 不能频繁读取

		}
 		WTD_CLR;
#endif

		if ( 0!=(sys_work_info&SYSTEM_FLAG_ATT_ADJ) )
		{
			FpgaAttAdjust(); 
		}
		if(sys_work_info&SYSTEM_FLAG_GAIN_ADJ)
		{
			////FpgaGainAdjust();
		}
		//if(sys_work_info&SYSTEM_FLAG_GAIN_ADJ)
		//{
		//	FpgaGainAdjust();
		//}

		WTD_CLR;	        
		// 检查拓扑状态
		//TaskManageTopo();

		// 处理光纤数据通讯
		WTD_CLR;
		////FpgaGetMsgPkt();
		
		

 

	}
}



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

UCHAR8 GetMcuNetType( UCHAR8 net_type )
{
	switch ( net_type )
	{
		case NET_TYPE_GSM900:
			return 'G';

		case NET_TYPE_WCDMA2100:
			return 'W';

		case NET_TYPE_TD:
			return 'T';

		case NET_TYPE_DCS1800:
			return 'D';

		case NET_DIVE:
			return 'd';

		case NET_TYPE_CMMB:
			return 'B';
			
		case NET_TYPE_CDMA:
		case NET_TYPE_CDMA800:
			return 'C';
			
		case NET_TYPE_TETRA:   //集群Tetra
			return 'T'; 
			
		case NET_TYPE_LTE_TD:
			return 'T';
		case NET_TYPE_LTE_FDD:
			return 'F';
			

		case NET_NONE:
			return '_';
			
		default:
			return '?';
	}
	
}

//SYSTEM_INIT_DATA_T c_init_data;

void GetMcuWaterPrint()
{
	UINT32 i;
	UINT32 tmp=0;
	
	//MCU编译日期和水印
	str_pri_mcu_date[tmp++] = 'A';
	str_pri_mcu_date[tmp++] = 'U';
	str_pri_mcu_date[tmp++] = '1';
	str_pri_mcu_date[tmp++] = ' ';
	
#if ((defined CLIENT_ERRICSON2) ||(defined CLIENT_ERRICSON_W))				
		str_pri_mcu_date[tmp++] = 'E';
		str_pri_mcu_date[tmp++] = 'R';
#elif defined( CLIENT_ERRICSON )			
		str_pri_mcu_date[tmp++] = 'E';
		str_pri_mcu_date[tmp++] = 'R';
#elif defined( CLIENT_JIZHUN )				
		str_pri_mcu_date[tmp++] = 'J';
		str_pri_mcu_date[tmp++] = 'Z';
#elif defined( CLIENT_DATANG )		
		str_pri_mcu_date[tmp++] = 'D';
		str_pri_mcu_date[tmp++] = 'T';
#else								   
		str_pri_mcu_date[tmp++] = 'E';
		str_pri_mcu_date[tmp++] = 'R';
#endif
	str_pri_mcu_date[tmp++] = ' ';

	str_pri_mcu_date[tmp++] = GetMcuNetType(fpga_cfg.a_net_type);
	str_pri_mcu_date[tmp++] = GetMcuNetType(fpga_cfg.b_net_type);;
	str_pri_mcu_date[tmp++] = GetMcuNetType(fpga_cfg.c_net_type);
	str_pri_mcu_date[tmp++] = GetMcuNetType(fpga_cfg.d_net_type);	

	//str_pri_mcu_date[tmp++] = ' ';





#ifdef USE_RS232_AS_CTRL_PORT
	str_pri_mcu_date[tmp++] = ',';
#elif defined ( FUNC_FREQ_POINT_SEARCH_EN )	// SFP
	str_pri_mcu_date[tmp++] = '#';
#else
	if ( fpga_cfg.wlan_en==1 )
	{
		str_pri_mcu_date[tmp++] = '|';
	}
	else  
	{
		str_pri_mcu_date[tmp++] = ' ';
	}  

#endif
	//str_pri_mcu_date[tmp++] = ' ';

	p_mcu_date = __DATE__; 	

	memcpy(str_pri_mcu_date+tmp,p_mcu_date,PRI_MCU_DATE_LEN-tmp);
	
}

void main()
{
	UINT32 tmp=0;
	UCHAR8 reset_time=0;

	//UCHAR8 p_msg_dat[]={0x01,0x01,0x00,0x00,0x00,0x00,0xdf,0xff,0x00,0x00,'t','e','s','k','o','k','.','f','r','o','m','.','r','e','c','.','.','.','.','.','.','.','.','.'};
	//UCHAR8 p_msg_dat1[]={0xC2,0x01,0x01,0x69,0x82,0x02,0x00,0x00};
	
	// 系统初始化
	InitSystem();

	// 读MCU水印
	GetMcuWaterPrint();	
	WTD_CLR;

	TRACE_INFO("Sys Start Run\r\n");

	UsbConnect(); 
   
	 
	while(1)
	{ 
	
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

		//rx_task( (uint8_t)(0x00FF & FpgaReadRegister( FPGA_REG_MSG_FIFO_ST )) );

 

	}
}



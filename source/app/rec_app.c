/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :rec_app.c
* Description :系统参数处理相关函数
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

extern _T_PARAM_1B sys_param_1b[];
extern _T_PARAM_2B sys_param_2b[];
extern _T_PARAM_4B sys_param_4b[];


extern UINT32 fpga_load_status;
extern _T_BIG_PKT_BUFF msg_big_buff[MSG_BIG_PKT_COUNT];
//extern UINT32 module_param_chg_flag;		//系统工作参数修改标志
extern FLOAT32 fpga_dgcic_b;
extern UCHAR8 traffic_start ;//开始话务量统计

_T_VALID_FP_TOPO valid_fp_topo[FP_MAX];
_T_RE_INFO tmp_re_inf[FP_MAX][RE_MAX];		// RE信息的临时缓存
_T_FP_INFO fp_inf[FP_MAX];		// 光口拓扑信息
_T_TOPO_ALARM_INFO topo_alarm[FP_MAX][RE_MAX] = {0};

UINT16 fp_enable = 0;			// 光口的使能状态: 1-使能
UINT16 total_re_count = 0;		// 拓扑中总的RE数量
UCHAR8 pre_re_count[FP_MAX];	// 前一次的光口RE数量
UINT16 total_ree_count = 0;		// 拓扑中总的RE数量
UCHAR8 pre_ree_count[FP_MAX];	// 前一次的光口RE数量
_T_TOPO_STATUS topo_st;			// 拓扑管理状态

UCHAR8 gsm_type_a = G2_TYPE_UNICOM;	// A段gsm模式,默认为联通频段
UCHAR8 gsm_type_b = G2_TYPE_UNICOM;	// B段gsm模式,默认为联通频段

UINT32 bit_err_cnt=0;
UINT32 topo_chg_cnt = 0;
UINT32 fpga_rx_pkt_cnt = 0;
UINT32 topo_ok_count = 0;
UINT32 topo_err_count = 0;

UCHAR8 ucPllStatus =0;
UCHAR8 benzhen2340 = 0;

_T_NOISE_TEST_STATUS noise_test_st = 0;
//计算RE平均功率用的数据,=10log(1~64)
const FLOAT32 pow_div_tbl[64]={
	0.000000,   3.010300,  4.771213,  6.020600,  6.989700,  7.781513,  8.450980,  9.030900, 
	9.542425,  10.000000, 10.413927, 10.791812, 11.139434, 11.461280, 11.760913, 12.041200, 
	12.304489, 12.552725, 12.787536, 13.010300, 13.222193, 13.424227, 13.617278, 13.802112, 
	13.979400, 14.149733, 14.313638, 14.471580, 14.623980, 14.771213, 14.913617, 15.051500, 
	15.185139, 15.314789, 15.440680, 15.563025, 15.682017, 15.797836, 15.910646, 16.020600, 
	16.127839, 16.232493, 16.334685, 16.434527, 16.532125, 16.627578, 16.720979, 16.812412, 
	16.901961, 16.989700, 17.075702, 17.160033, 17.242759, 17.323938, 17.403627, 17.481880, 
	17.558749, 17.634280, 17.708520, 17.781513, 17.853298, 17.923917, 17.993405, 18.061800, 
};

// td_scdma搜索通道号，第1通道为界面设置的频点，初始值为10087，接下来前9个为大唐的固定频点，后9个为华为的固定频点:10054,10062,10070,10079,10087,10095,10104,10112,10120，10055,10063,10071,10080,10088,10096,10104,10112,10120,
UINT16 tds_dl_channel[19] = {10087,10054,10062,10070,10079,10087,10095,10104,10112,10120,10055,10063,10071,10080,10088,10096};
// 温度增益补偿表
// A段下行温度增益补偿表        //                  -20                         -10                     0
const UINT16 temp_cmp_tbl_adl[13] = {(UINT16)((INT16)(2.2*1000)),(UINT16)((INT16)(1.6*1000)),(UINT16)((INT16)(1.2*1000)),
								//					10,						    20,  					30 ,				   					
								(UINT16)((INT16)(0.9*1000)),(UINT16)((INT16)(0.6*1000)),(UINT16)((INT16)(0.2*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.4*1000)),(UINT16)((INT16)(-0.8*1000)),
								//                  70, 				        80, 			
								(UINT16)((INT16)(-0.8*1000)),(UINT16)((INT16)(-1.5*1000)), 0, 0};	
// A段上行温度增益补偿表        //                   -20                     1-0                          0
const UINT16 temp_cmp_tbl_aul[13] = {(UINT16)((INT16)(1.6*1000)),(UINT16)((INT16)(1.2*1000)),(UINT16)((INT16)(0.87*1000)),
								//					10,						    20,  						      30 ,				   					
								(UINT16)((INT16)(0.9*1000)),(UINT16)((INT16)(0.2*1000)),(UINT16)((INT16)(0*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(0.2*1000)),(UINT16)((INT16)(0.1*1000)),
								//                  70, 				        80, 			
								(UINT16)((INT16)(-0.2*1000)),(UINT16)((INT16)(-0.9*1000)), 0, 0};		

// B段下行温度增益补偿表        //                  -20                          -10                   0
const UINT16 temp_cmp_tbl_bdl[13] = {(UINT16)((INT16)(2.2*1000)),(UINT16)((INT16)(1.9*1000)),(UINT16)((INT16)(1.5*1000)),
								//					10,						      20,  						      30 ,				   					
								(UINT16)((INT16)(1.1*1000)),(UINT16)((INT16)(0.7*1000)),(UINT16)((INT16)(0.4*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.5*1000)),(UINT16)((INT16)(-0.8*1000)),
								//                70, 				            80, 			
								(UINT16)((INT16)(-1.2*1000)),(UINT16)((INT16)(-1.7*1000)), 0, 0};	
// B段上行温度增益补偿表       //                   -20                         -10                        0
const UINT16 temp_cmp_tbl_bul[13] = {(UINT16)((INT16)(1.81*1000)),(UINT16)((INT16)(1.31*1000)),(UINT16)((INT16)(1.17*1000)),
								//					10,						     20,  						      30 ,				   					
								(UINT16)((INT16)(0.61*1000)),(UINT16)((INT16)(0.71*1000)),(UINT16)((INT16)(0.11*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.29*1000)),(UINT16)((INT16)(-0.63*1000)),
								//                  70, 				        80, 			
								(UINT16)((INT16)(-0.9*1000)),(UINT16)((INT16)(-1.69*1000)), 0, 0};		

// C段下行温度增益补偿表      //                   -20                        -10                        0
const UINT16 temp_cmp_tbl_cdl[13] = {(UINT16)((INT16)(2.3*1000)),(UINT16)((INT16)(2.2*1000)),(UINT16)((INT16)(1.7*1000)),
								//					10,						   20,  						      30 ,				   					
								(UINT16)((INT16)(0.6*1000)),(UINT16)((INT16)(0.8*1000)),(UINT16)((INT16)(0.32*1000)),
								//					40,						50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.8*1000)),(UINT16)((INT16)(-1.3*1000)),
								//                  70, 				      80, 			
								(UINT16)((INT16)(-1.4*1000)),(UINT16)((INT16)(-2.2*1000)), 0, 0};	
// C段上行温度增益补偿表      //                   -20                         -10                     0
const UINT16 temp_cmp_tbl_cul[13] = {(UINT16)((INT16)(1.9*1000)),(UINT16)((INT16)(1.8*1000)),(UINT16)((INT16)(1.44*1000)),
								//					10,						      20,  						      30 ,				   					
								(UINT16)((INT16)(1.09*1000)),(UINT16)((INT16)(0.3*1000)),(UINT16)((INT16)(0*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(0.1*1000)),(UINT16)((INT16)(-0.4*1000)),
								//                  70, 				        80, 			
								(UINT16)((INT16)(-0.6*1000)),(UINT16)((INT16)(-1.4*1000)), 0, 0};		
// D段下行温度增益补偿表         //                  -20                        -10                       0
UINT16 temp_cmp_tbl_ddl[13] = {(UINT16)((INT16)(2.5*1000)),(UINT16)((INT16)(2.3*1000)),(UINT16)((INT16)(1.9*1000)),
								//					10,						      20,  						      30 ,				   					
								(UINT16)((INT16)(1.29*1000)),(UINT16)((INT16)(0.9*1000)),(UINT16)((INT16)(0.2*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-1.2*1000)),(UINT16)((INT16)(-1.1*1000)),
								//        			70, 				         80, 			
								(UINT16)((INT16)(-1.5*1000)),(UINT16)((INT16)(-2*1000)), 0, 0};	
// D段上行温度增益补偿表       //                  -20                          -10                      0
const UINT16 temp_cmp_tbl_dul[13] = {(UINT16)((INT16)(1.8*1000)),(UINT16)((INT16)(1.6*1000)),(UINT16)((INT16)(1.3*1000)),
								//					10,						      20,  						      30 ,				   					
								(UINT16)((INT16)(0.75*1000)),(UINT16)((INT16)(0.6*1000)),(UINT16)((INT16)(0.2*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.4*1000)),(UINT16)((INT16)(-0.9*1000)),
								//                 70, 				             80, 			
								(UINT16)((INT16)(-1.1*1000)),(UINT16)((INT16)(-1.93*1000)), 0, 0};	

void InitRec()
{
	UINT32 i,j;
	UINT16 tmp;
	
	WTD_CLR;
	
	topo_st.IsTopoUnsteady = 1;
	topo_st.IsSendReqPkt = 0;
	topo_st.IsGetReInfOk = 0;   
	
	fp_enable = 0xFF;		// 使能所有光口 1使能，0失能

	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_OPT_ON, fp_enable);
	FPGA_DISABLE_WRITE;
	
	for ( i=0; i<FP_MAX; i++ )
	{
		fp_inf[i].re_cnt = 0; 
		pre_re_count[i]  = 0;  
		 
		for ( j=0; j<RE_MAX; j++ )
		{
			fp_inf[i].re_info[j].re_id = 0;
			fp_inf[i].re_info[j].re_status = 0;
		}
		
		//清空缓冲区 
		ClearTmpReInfo(i);
	}

	sys_param_1b[MADD_DELAY_MODE].val=1;
	sys_param_1b[MADD_DELAY_MODE_A].val=1;
	sys_param_1b[MADD_DELAY_MODE_B].val=1;
	sys_param_1b[MADD_DELAY_MODE_C].val=1;	
	sys_param_1b[MADD_DELAY_MODE_D].val=1;
	
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA故障，返回
		return;
	}

	sys_work_info = 0;

#ifdef FUNC_TD_AUTO_SEARCH_FP	// TD自动频点搜索
	// 初始化搜索超时时间，MCU的逻辑写缓存地址211，不用开写保护
	//FpgaWriteRegister( FPGA_WO_REG(211), 90 );
#endif
}

/*************************************************************
Name:SetValidTopo          
Description: 更新拓扑信息
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
BOOL SetValidTopo( UCHAR8 * p_dat )
{
	return b_TRUE;
}

/*************************************************************
Name:             GetNewTopo          
Description:      检查8个光口的状态:是否有光模块插入
                                    是否该光口锁定
                                    统计该光口下的RE数目
                                    是否有对端口，以及对端口的ID
               
                  在TaskManageTopo中调用 
Input: void
Return: void
**************************************************************/
void GetNewTopo()
{
}

/*************************************************************
Name:         CheckTopoChange          
Description:  判断拓扑有没有变化，统计总的RE数

              只要统计到任何一个光口的RE和上一次的RE个数步相等，就认为 拓扑已经改变
              最后统计所有的光口的RE总数

Input:        void
Return:       b_TRUE-拓扑改变； 
              FALSE-拓扑未改变 
**************************************************************/
BOOL CheckTopoChange()
{

}

/*************************************************************
Name:CheckRingNetErr          
Description: 检测是否环网断开 
Input: void
Return: void
**************************************************************/
void CheckRingNetErr()
{
	static UCHAR8 pre_ring_net_st=0;			// 环网状态，初始为非环网
	UINT32 i;
	UINT32 flag = 0;
	UCHAR8 alarm = 0;
	UINT32 ops_no;

	for ( i=0; i<FP_MAX; i++ )
	{
		// 初始化环网状态为非环网 
		flag = 1;

		// 重置本端下行发送状态为正常
		fp_inf[i].tx_err = 0;
				
		// 检测是否是环网连接
		if ( OPS_RCV_FLAG==(fp_inf[i].ops_info & OPS_RCV_FLAG) )
		{	
			// 取得环网对端光口号(0开始)
			ops_no = fp_inf[i].ops_info & OPS_NO_MASK;

			if ( ops_no!=i )	// 对端光口号与当前光口号不可能相同
			{
				// 对端光口也收到本端下行帧，则确定是环网
				if (( ops_no<FP_MAX )&&( OPS_RCV_FLAG==(fp_inf[ops_no].ops_info & OPS_RCV_FLAG) ))
				{		
					// 环网
					flag = 0;
				}
				else
				{	 
					// 末端RE没有收到本端的下行数据，判断本端下行发送故障
					fp_inf[i].tx_err = 1;
				}  
			}
		}

		// 如果光模块未连接，则清除前一次的环网标志
		if ( fp_inf[i].sfp_attach==0 )
		{
			pre_ring_net_st &= (~(1<<i));
			continue;
		}

        /*上次为非环网*/
		if ( 0==(pre_ring_net_st & (1<<i)) )
		{
			// 检测到当前为环网
			if ( flag==0 )
			{ 
				
				pre_ring_net_st |= (1<<i);	// 置环网标志
			}
		}
		else /*上次为环网*/
		{
			// 检测到当前不为环网
			if( flag == 1 )
			{
				alarm = 1;	// 环网状态告警
				break;
			}
			else
			{
				// 检测到当前为环网
			}
		}
	}

	sys_param_1b[MADD_TOPO_CHG_ALM].val = alarm;	// 环网状态告警
	
}

void RefreshParam()
{
	UINT32 tmp = 0;
	INT32 i;
	
	if ( 0 == topo_st.IsTopoUnsteady )
	{
		// 更新节点数量到参数中
		sys_param_4b[MADD_OPT_RE_COUNT1].val = (fp_inf[3].re_cnt<<24)|(fp_inf[2].re_cnt<<16)|(fp_inf[1].re_cnt<<8)|(fp_inf[0].re_cnt);
		sys_param_4b[MADD_OPT_RE_COUNT2].val = (fp_inf[7].re_cnt<<24)|(fp_inf[6].re_cnt<<16)|(fp_inf[5].re_cnt<<8)|(fp_inf[4].re_cnt);
		
		for (i=FP_MAX-1; i>=0; i--)
		{
			tmp <<= 4;
			
			if ( 0 !=(fp_inf[i].ops_info & OPS_RCV_FLAG) )
			{
				if ( (fp_inf[i].ops_info & OPS_NO_MASK)<FP_MAX )
				{
					tmp |= ( (fp_inf[i].ops_info & OPS_NO_MASK)+1 );
				}
			}
		}
	}
	else
	{
		sys_param_4b[MADD_OPT_RE_COUNT1].val = 0;
		sys_param_4b[MADD_OPT_RE_COUNT2].val = 0;
	}
	sys_param_4b[MADD_OPS_PORT].val = tmp;
}

/*************************************************************
Name:         UpdateReInfo          
Description:  更新RE信息
              在主循环中调用，1秒钟就处理一次  



              
Input:        void
Return:       void
**************************************************************/
void UpdateReInfo()
{  
	UCHAR8 fp_no, re_no; 

	WTD_CLR;
	
    //TRACE_INFO("UpdateReInfo\r\n");
	
	// 拓扑不稳定 
	if ( 1 == topo_st.IsTopoUnsteady )
	{
		topo_st.IsGetReInfOk = 0;
		topo_st.IsSendReqPkt = 0;
		topo_st.ReAckTimeOut = 0;
		//TRACE_INFO("back 6\r\n");
		return; 
	}          

    //没有RE数目 
	if ( 0 == total_re_count )
	{
		//TRACE_INFO("back 5\r\n");
		return; 
	}

	// 表示还没发送RE信息请求
	if ( 0 == topo_st.IsSendReqPkt )   //每5秒钟发送一次查RE状态的广播信息
	{
		
		GetReInfo();                    // 广播获取RE信息请求 ,返回每个RE的ID +状态(锁定  + 帧模式)
		topo_st.IsSendReqPkt = 1;		// 表示已经发送RE信息请求
		topo_st.IsGetReInfOk = 0;		// 清除RE信息更新完成标志
		topo_st.ReAckTimeOut = 0;		// 复位应答超时计时器
		//TRACE_INFO("back 4\r\n");
		return; 
	}  

	// RE没有返回最新状态
	if ( 0 == topo_st.IsGetReInfOk )
	{
		topo_st.ReAckTimeOut++;
		
		if ( topo_st.ReAckTimeOut > 5 )		// 获取RE信息超时(5s)
		{
			topo_st.IsSendReqPkt = 0;		//5秒之内还没收到所有RE的信息包，重新广播
			//TRACE_INFO("back 3\r\n");
			return;
		}

		// 遍历检查是否所有的RE都返回了最新状态
		for( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			if ( fp_inf[fp_no].re_cnt > RE_MAX )
			{
				//TRACE_INFO("back 2\r\n");
				return;
			} 
			
			for ( re_no=0; re_no<fp_inf[fp_no].re_cnt; re_no++ )
			{
				if ( 0 == tmp_re_inf[fp_no][re_no].flag )	// 有RE没有返回信息
				{
					//TRACE_INFO("back 1\r\n");  
					//TRACE_INFO("%d,%d\r\n",fp_no,re_no);
					return;
				} 
			}
		}

		topo_st.IsGetReInfOk = 1;		// 所有的RE信息更新完成标志
		topo_st.UpdateCycDelay = 0;  	// 清除等待计时器
		
		// 保存RE信息到拓扑结构中，并清空缓存
		for( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			for ( re_no=0; re_no<fp_inf[fp_no].re_cnt; re_no++ )
			{
				fp_inf[fp_no].re_info[re_no].re_status = tmp_re_inf[fp_no][re_no].status;
				fp_inf[fp_no].re_info[re_no].re_id = tmp_re_inf[fp_no][re_no].id;
			}
			
			ClearTmpReInfo( fp_no );
		}

		//检查RE的id
		//CheckReID();
		
	}
	else  //已经返回了所有RE的信息
	{
		topo_st.UpdateCycDelay++;
//		TRACE_INFO_WP("Wait..%d\r\n", topo_st.UpdateCycDelay);
		if ( topo_st.UpdateCycDelay>5 )		// 隔一定周期检查一次(5s)
		{
			topo_st.IsSendReqPkt = 0;	// 清零【已发送RE状态请求包】状态，即需要重发请求包
			topo_st.IsGetReInfOk = 0;	// 清除RE信息更新完成标志
		}
	}
	
}
/*************************************************************
Name:RecBoadcastGetTopo         
Description: 广播获取RE的拓扑信息,更新标志信息
Input: void
Return: void
**************************************************************/
void  RecBoadcastGetTopo()
{
	UCHAR8 topo_buff[25];
	UCHAR8  i=0;
		topo_buff[i++]=BROADCAST_ADD_FP;
		topo_buff[i++]=BROADCAST_ADD_RE;
		topo_buff[i++]=0x00;
		topo_buff[i++]=LOCAL_ADD_FP;
		topo_buff[i++]= LOCAL_ADD_RE;
		topo_buff[i++]= LOCAL_ADD_REE;
		topo_buff[i++]=MSG_CMD_GET_TOPO;
		topo_buff[i++]=MSG_ACK_MASTER_SEND;
		
		i = MSG_PKT_HEAD_SIZE;
		
		topo_buff[i++]=0x00;
		topo_buff[i++]=0x00;
		topo_buff[i++]=0x00;
		topo_buff[i++]=0x00;
		
		TRACE_INFO("RecBoadcastGetTopo.");
		SendMsgPkt(i+1, topo_buff);
		
}
	
/*************************************************************
Name:TaskManageTopo          
Description: 检查拓扑,更新标志信息
             此函数在主循环中实时调用
Input:  void
Return: void
**************************************************************/
void TaskManageTopo()
{
	UCHAR8 i,j;
	static UCHAR8 topo_stable_count = 0;
 
	WTD_CLR; 
	
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA故障，返回
		topo_st.IsTopoUnsteady = 1;
		return; 
	} 


    /*更新8个光口的最新状态*/
	GetNewTopo();

    /*检测是否环网断开 */
	//CheckRingNetErr();

    /*检测拓扑有无变化，并统计总RE数目*/
	if ( b_TRUE == CheckTopoChange() )		// 拓扑变化
	{
		TRACE_INFO("2013-----------CheckTopoChange\r\n");
		topo_stable_count = 0;
		sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
		sys_work_info |= SYSTEM_FLAG_SET_RE_SYS_CFG;
		sys_work_info |= SYSTEM_FLAG_SET_RE_TDSLOT;
		sys_work_info |= SYSTEM_FLAG_SET_RE_SFC;

		//if(topo_ok_count > 86400)//如果稳定了24小时候，发生不稳定 记为TOPO告警
		//if(topo_ok_count > 300)//5分钟告警测试版本
		if(topo_ok_count > 7200)  //2小时版本
			topo_err_count ++;
	} 
	else
	{  
		/*拓扑稳定计数加1*/
		topo_stable_count++;
		topo_ok_count++;
	}
	
	// 检查到8次以上，才证明拓扑稳定，无改变
	if ( topo_stable_count < 8 )		
	{ 
		if ( topo_st.IsTopoUnsteady==0 )
		{   
			/*拓扑变化计数器*/
			topo_chg_cnt++;
		}		
		topo_st.IsTopoUnsteady = 1;	
	}
	else
	{
		topo_st.IsTopoUnsteady = 0;
		topo_stable_count = 10;
	} 
	

}

/*************************************************************
Name:ClearTmpReInfo          
Description: 清除RE信息的临时缓存
Input: fp:光口号
Return: void
**************************************************************/
void ClearTmpReInfo( UCHAR8 fp )
{
	UCHAR8 i;
	for ( i=0; i<RE_MAX; i++ )
	{
		tmp_re_inf[fp][i].flag = 0;
		tmp_re_inf[fp][i].id = 0;
		tmp_re_inf[fp][i].status = 0;
	}
}

/*************************************************************
Name:GetReInfo          
Description: 广播发送获取RE状态的数据包
Input: void
Return: void
**************************************************************/
void GetReInfo()
{

	UCHAR8 msg[FPGA_MSG_FRAME_LEN];
	UINT32 tx_len;
	UINT32 tmp;
	static UCHAR8 i=0;
//	TRACE_INFO("201310090921-----------GetReInfo,i=%02x\r\n",i);	
	msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	msg[MSG_DES_REE] = 0;
	msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	msg[MSG_SRC_REE] = LOCAL_ADD_REE;
	msg[MSG_CMD_ID] = MSG_CMD_GET_REE_INFO;
	msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	if(255==i)
	{
		i=0;
	}
	
	msg[MSG_RESERVE1] = i++;
	
	tx_len = MSG_PKT_HEAD_SIZE;

	msg[tx_len++] = 0xA7;		// 扩展标识1
	msg[tx_len++] = 0xE5;		// 扩展标识2
	msg[tx_len++] = 0x0;		// 模式版本0

	SendMsgPkt(tx_len, msg);
	
}

/*************************************************************
Name:AssignID          
Description: 分配ID
Input:
	fp: 光口号
	re: RE位置序号
	p_id: 保存ID值的缓冲指针
Return: 
	b_TRUE: 成功分配ID值
	b_FALSE: 分配ID失败
**************************************************************/
BOOL AssignID( UINT32 fp, UINT32 re, UINT32 * p_id )
{
	UINT32 ok_flag = 0;
	UINT32 id = ID_DEFAULT+1;  //  1
	UINT32 i;

	WTD_CLR;
	
	if ((fp>FP_MAX)||(re>RE_MAX)||(NULL==p_id))
	{
		return b_FALSE;
	}

	while ( 0 == ok_flag )
	{
		if ( id>ID_MAX )
		{
			ok_flag = 0;
			break;
		} 
		
		ok_flag = 1;
		
		for ( i=0; i<fp_inf[fp].re_cnt; i++ )
		{
			if ( i == re ) 
			{
				continue;
			} 
			
			if ( id == fp_inf[fp].re_info[i].re_id )
			{
				id++;
				ok_flag = 0;
				break;
			}
		}
	}

	if ( ok_flag )
	{
		*p_id = id;
		return b_TRUE;
	}
	else
	{
		return b_FALSE;
	}

}

/*************************************************************
Name:CheckReID          
Description: 检查RE的ID是否有重复
Input: void
Return: 
	b_TRUE:  成功分配ID值
	b_FALSE: 分配ID失败
**************************************************************/
void CheckReID()
{
	UINT32 fp, re;
	UINT32 tmp_id;
	UINT32 re_id;
	UINT32 i;
	
	WTD_CLR;
	TRACE_INFO("Check Re id\r\n");

	for (fp=0; fp<FP_MAX; fp++)
	{
		// 检查光口是否使能
		if ( 0 == (fp_enable&(0x01<<fp)) )
		{
			continue;
		}
		
		for ( re=0; re<fp_inf[fp].re_cnt; re++ )
		{
			re_id = fp_inf[fp].re_info[re].re_id;
			if ( re_id == ID_DEFAULT )
			{
				if ( b_TRUE == AssignID( fp, re, &tmp_id ) )
				{
					fp_inf[fp].re_info[re].re_id = tmp_id;
					// 发送数据包设置RE的ID
					SetReID( fp, re, 0, tmp_id );
				} 
				else
				{
					TRACE_ERROR("Assign FP%d RE%d Id Fail.\r\n", fp, i);
				}
			}
			else
			{
				for ( i=re+1; i<fp_inf[fp].re_cnt; i++ )
				{
					if ( re_id == fp_inf[fp].re_info[i].re_id )
					{
						if ( b_TRUE == AssignID( fp, i, &tmp_id ) )
						{
							fp_inf[fp].re_info[i].re_id = tmp_id;
							// 发送数据包设置RE的ID
							SetReID( fp, re, 0, tmp_id );
						}
						else
						{
							TRACE_ERROR("Assign FP%d RE%d Id Fail.\r\n", fp, i);
						}
					}
				}
			}
		}
	}

	// 清除标志
	sys_work_info &= (~SYSTEM_FLAG_CHECK_ID);

}

// 读取WLAN口的状态，更新到接口参数表中
void GetWlanPortStatus()
{
	UINT16 port;
	UINT16 reg;
	
	for ( port=0; port<WLAN_PORT_COUNT; port++)
	{
		sys_param_1b[MADD_WLAN_CONN_ST1+port].val = 0;		// 重置状态为正常
		sys_param_1b[MADD_WLAN_SPEED1+port].val = 0;		// 重置速度为10M

		if ( 0==fpga_cfg.wlan_en )		// 122.88M时钟,非WLAN模式，不读取WLAN口信息
		{
			continue;
		}

		if ( 0==fp_inf[port+WLAN_PORT_OFFSET].sfp_attach)		// 网口模块未连接
		{
			continue;	// 不更新状态信息
		}
		

		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(port+WLAN_PORT_OFFSET);		// 设置光口
		FPGA_DISABLE_WRITE;

		reg = FpgaReadRegister(FPGA_WLAN_PORT_INFO);	// 读取参数
		if ( 0 == (reg&BM_WLAN_LINK_ST) )	// 连接断开
		{
			sys_param_1b[MADD_WLAN_CONN_ST1+port].val = 1;
		}
		switch (reg&BM_WLAN_SPEED)		// 速度流量
		{
		case FLAG_WLAN_SPEED_10M:
			sys_param_1b[MADD_WLAN_SPEED1+port].val = 0;
			break;
			
		case FLAG_WLAN_SPEED_100M:
			sys_param_1b[MADD_WLAN_SPEED1+port].val = 1;
			break;

		case FLAG_WLAN_SPEED_1000M:
			sys_param_1b[MADD_WLAN_SPEED1+port].val = 2;
			break;

		default:
			sys_param_1b[MADD_WLAN_SPEED1+port].val = 0;
			break;
		}

	}
}


/*************************************************************
Name: GetNetworkDelay          
Description: 获取最大的光口延时时间，并写入最大延时寄存器
Input: void 
Return: void
**************************************************************/
void GetNetworkDelay()
{
	INT32 i;
	UINT16 tmp;
	UINT32 opt_t14;
	UINT32 max_t14 = 0;
	if ( FPGA_LDST_OK == fpga_load_status )
	{
		tmp = ((UINT32)FpgaReadRegister(FPGA_REG_OPT_MAX_DELAY_H)<<8)| ((FpgaReadRegister(FPGA_REG_OPT_MAX_DELAY_L)>>8)&0xff);
		sys_param_2b[MADD_MAX_T14].val = (UINT16)(tmp/75.0); //光口最大延时
		//TRACE_INFO("sys_param_2b[MADD_MAX_T14].val=[%x],tmp=[%x]\r\n",sys_param_2b[MADD_MAX_T14].val,tmp);
		tmp = ((UINT32)FpgaReadRegister(FPGA_REG_OPT_MAX_DELAY_H)<<8)| ((FpgaReadRegister(FPGA_REG_OPT_MAX_DELAY_L)>>8)&0xff);
		sys_param_2b[MADD_MAX_T14_A].val = (UINT16)(tmp/75.0/2)+RF_DELAY_TIME_A*100; //光口最大延时
		sys_param_2b[MADD_MAX_T14_B].val = (UINT16)(tmp/75.0/2)+RF_DELAY_TIME_B*100; //光口最大延时
		sys_param_2b[MADD_MAX_T14_C].val = (UINT16)(tmp/75.0/2)+RF_DELAY_TIME_C*100; //光口最大延时
		sys_param_2b[MADD_MAX_T14_D].val = (UINT16)(tmp/75.0/2)+RF_DELAY_TIME_D*100; //光口最大延时

	}
}

/*************************************************************
Name:GetPeripheralStatus          
Description: 更新单板状态
Input: void
Return: void
**************************************************************/
void GetPeripheralStatus()
{
	UINT16 tmp;
	UINT16 i;	
	
	WTD_CLR;
	
	if (    sys_work_info&SYSTEM_FLAG_MCU_UPDATE
	     || sys_work_info &SYSTEM_FLAG_FPGA_UPDATE
	     || sys_work_info &SYSTEM_FLAG_REMOTE_UPDATE)
	{
	      
		 return;  
	}   
 
	/*获取最大的光口延时时间，并写入最大延时寄存器*/
	//GetNetworkDelay();

	// PLL状态 
	// 检查9517时钟状态 
	sys_param_1b[MADD_CLK_PLL_ST].val = ( 0==GetAD9524LD()? 1 : 0 );
	//sys_param_1b[MADD_CLK_REF_ST].val = ( 0==GetAD9524Refmon() ? 1 : 0 );
//	sys_param_1b[MADD_CLK_].val = ( 0==GetAD9524Status() ? 0 : 1 );

	// DA锁相环
	//sys_param_1b[MADD_A_BB_PLL_LOCK].val = (0==GetDA9122LockA()) ? 1 : 0;
	//sys_param_1b[MADD_B_BB_PLL_LOCK].val = (0==GetDA9122LockB()) ? 1 : 0;
	
	// 误码率偏高报警
	//sys_param_1b[MADD_BER_ALARM].val = 0;

	if ( FPGA_LDST_OK == fpga_load_status )
	{
		// 读取时钟状态
		tmp = FpgaReadRegister(FPGA_REG_GCLK_ST);
		// FPGA锁相环
		sys_param_1b[MADD_FPGA_CLK_ST].val = ( 0==(tmp&BM_FPGA_PLL_LOCK) ? 1 : 0 );

		// SERDES状态
		for ( i=0; i<FP_MAX; i++ )
		{
			// 重置状态为正常
			sys_param_1b[MADD_FP1_LOS+i].val = 0;//0: 正常，1: 告警
			sys_param_1b[MADD_FP1_LOF+i].val = 0;
			sys_param_1b[MADD_SERDES1_PLL_ST+i].val = 0;

			// 光模块在位状态
			sys_param_1b[MADD_FP1_ON_POS+i].val = ( fp_inf[i].sfp_attach==1 ) ? 0 : 1;

			if ( 1==fpga_cfg.wlan_en )		// WLAN模式，不读取WLAN口所在光口的锁定状态信息,只读取普通光口信息
			{
				if ( i>=WLAN_PORT_OFFSET )
				{
					continue;
				}
			}

			if ( fp_inf[i].sfp_attach == 1 )	// 光模块已连接
			{
//				TRACE_INFO("i[%02x]20130509++++++++r\n",i);
				// 光模块状态
				sys_param_1b[MADD_FP1_LOS+i].val = (( FRAME_LOCK==fp_inf[i].frm_lock ) ? 0 : 1);//(( b_TRUE==FpgaGetSfpStatus(i) ) ? 0 : 1);	//(( FRAME_LOCK==fp_inf[i].frm_lock ) ? 0 : 1);
				// 链路同步状态
				sys_param_1b[MADD_FP1_LOF+i].val = ((FRAME_LOCK==fp_inf[i].frm_lock)&&(0==fp_inf[i].tx_err) ? 0 : 1);
				// 锁定状态
				sys_param_1b[MADD_SERDES1_PLL_ST+i].val = ((FRAME_LOCK==fp_inf[i].frm_lock)&&(0==fp_inf[i].tx_err) ? 0 : 1);
			}

		}

#if	1
		//GetWlanPortStatus();

		CheckErrStatus();

		//RefreshParam();
		
		// 设置FPGA错误指示灯
		//FPGA_ENABLE_WRITE;
		//FpgaWriteRegister(FPGA_REG_SHOW_ERROR, sys_param_1b[MADD_WORK_ERROR].val);
		//FPGA_DISABLE_WRITE;

		
#endif	
	}

}

/*************************************************************
Name: CheckErrStatus_Erricson          
Description: 检查系统工作是否有异常
Input: void
Return: void
**************************************************************/
void CheckErrStatus_Erricson()
{
	UCHAR8 i=0,j=0,err=0,tmp = 0;
	UCHAR8 au_err = 0,eu_err = 0,ru_err = 0;
	static UINT16 workerror_last = 0;//上一次告警的值
	static UINT16 workerror_current = 0;//本次的告警的值
	static UCHAR8 fp_eu_cnt_old[FP_MAX] = {0};

	WTD_CLR;	
	//光口下的级联EU减少时，清除被拔掉的EU的告警状态

	for(i=0; i<FP_MAX; i++)
	{
		
			if(fp_inf[i].re_cnt < fp_eu_cnt_old[i])
			{
				for(j= fp_inf[i].re_cnt; j<RE_MAX; j++)
		 		{
		 		 	topo_alarm[i][j].meu_alarm = 0;
				 	topo_alarm[i][j].ru_alarm = 0;
		 		}
			}
			fp_eu_cnt_old[i] = fp_inf[i].re_cnt;
	}

	//for(i=FP_MAX; i<8; i++)//清除其他光口的告警
	//{
	//	sys_param_eu_1b[MADD_EU_ALARM_FLAG1+i].val = 0;
	//	sys_param_eu_2b[MADD_EU_RUALARM_FLAG1+i].val = 0;
	//}

	

	au_err = 0;
	//温度告警
	//workerror_current |= sys_param_1b[MADD_BOARD_TEMP].val>80? (0x01):0x00;
	au_err |= sys_param_1b[MADD_BOARD_TEMP].val>80? (0x01):0x00;

	//时钟失锁
	au_err |=sys_param_1b[MADD_CLK_PLL_ST].val? 0x02:0x00;

	//光纤链路异常告警

	//if(sys_param_1b[MADD_FP1_LOS+0].val |sys_param_1b[MADD_FP1_LOS+1].val |sys_param_1b[MADD_FP1_LOS+2].val |sys_param_1b[MADD_FP1_LOS+3].val )
	//	workerror_current = 0x04;

	for(i=0; i<FP_MAX; i++)
	{
		err += sys_param_1b[MADD_FP1_LOS+i].val;
	}
	if(err >0)
		au_err |= 0x04;

	//拓扑告警
	if(topo_err_count >=1)
	{
	
		//au_err |= 0x08;//暂时关闭该告警
	}

	sys_param_1b[MADD_WORK_ERROR].val = au_err;//AU对应的告警项
	//sys_param_1b[MADD_WORK_ERROR].val = 3;//AU对应的告警项

	sys_param_1b[MADD_BATTERY_BREAKDOWN_ALARM].val = au_err?1:0;
	//topo_alarm[0][0].mau_alarm = sys_param_1b[MADD_BATTERY_BREAKDOWN_ALARM].val;

	//topo_alarm.mau_alarm
	
	
	eu_err = 0;
	ru_err = 0;
	for(i=0;i<FP_MAX; i++)
	{
		for(j=0; j<RE_MAX; j++)
		{
			eu_err += topo_alarm[i][j].meu_alarm?1:0;
			 ru_err += topo_alarm[i][j].ru_alarm?1:0;
		}
	}

	
	//汇总告警项	
	workerror_current = 0;
	workerror_current |=  au_err? 0x8000:0x0000;//AU告警
	workerror_current |=  eu_err?0x4000:0x0000;
	workerror_current |=  ru_err?0x2000:0x0000;
	//workerror_current |= (sys_param_eu_1b[MADD_EU_ALARM_FLAG1].val ||sys_param_eu_1b[MADD_EU_ALARM_FLAG2].val ||sys_param_eu_1b[MADD_EU_ALARM_FLAG3].val ||sys_param_eu_1b[MADD_EU_ALARM_FLAG4].val)? 0x4000:0x0000;//低4位为EU告警
	//workerror_current |= (sys_param_eu_2b[MADD_EU_RUALARM_FLAG1].val ||sys_param_eu_2b[MADD_EU_RUALARM_FLAG2].val ||sys_param_eu_2b[MADD_EU_RUALARM_FLAG3].val ||sys_param_eu_2b[MADD_EU_RUALARM_FLAG4].val)? 0x2000:0x0000;//高4位为RU告警
	
	//sys_param_1b[MADD_WORK_ERROR].val = 0x3;
	
	//workerror_current = ((UINT16)sys_param_1b[MADD_WORK_ERROR].val<<15)|((UINT16)sys_param_1b[MADD_WORK_ERROR].val<<14)|((UINT16)sys_param_1b[MADD_WORK_ERROR].val<<13);//AU EU RU 
	//workerror_current = 0x6000;
	if(workerror_last != workerror_current)
	{
		printf("Alarm Occurred\r\n");
		workerror_last = workerror_current;
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_SHOW_ERROR,( ~workerror_current)&0xF000);//低电平告警
		FPGA_DISABLE_WRITE;
		sys_param_1b[MADD_HOST_DEVICE_LINK_SINGNAL_ALARM].val  = (UCHAR8) (workerror_last>>8);
	}
	
}

/*************************************************************
Name: CheckErrStatus          
Description: 检查系统工作是否有异常
Input: void
Return: void
**************************************************************/
void CheckErrStatus()
{
#if ((defined CLIENT_ERRICSON)||(defined CLIENT_ERRICSON2)||(defined CLIENT_ERRICSON_W))

CheckErrStatus_Erricson();


#endif

	
}

/*************************************************************
Name:UpdateWorkParam          
Description: 设置工作参数
Input: void
Return: void
**************************************************************/
void UpdateWorkParam(UINT32 mask)
{
	UINT32 i;
	UINT32 tmp;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}
	if ( 0 == mask )
	{
		return;
	} 
	
	WTD_CLR;

//	FpgaAttOutput(1);		// 控制衰减器全衰，防止逻辑开始工作时出现的杂散

	//更改本振或者中心频率
	if( 0 != ( mask&PCHG_CENTER_FRE_FLAG) )
	{
		//printf("设置中心频点\r\n");
		#if defined CLIENT_JIZHUN
		//TRACE_INFO("低操门限A = %d\r\n",(CHAR8)sys_param_1b[MADD_A_LTHR_DN].val) ;  
		MoveCenterFre(SYS_A_FLAG, SYS_DL_FLAG);
		#endif
	}


	#if defined CLIENT_ERRICSON
	// 修改频点搜索范围
	if ( 0!= (mask&PCHG_FPS_RANGE) )
	{

		//FPS_Init();
		//FPS_SetScanFc( &mod_cfg_a );
		//FPS_EnableAutoScan();
		WTD_CLR;
		FPS_SetParam(); 
	}
	#endif



	// 设置光口使能
	if ( 0 != ( mask&PCHG_SYS_FP_EN) )
	{
		 WTD_CLR;
		 EnableOpt();
	}

	// 恢复衰减器功能
	UsNopDelay(100*1000);			// 延时5ms
	//FpgaAttOutput(0);
	WTD_CLR;

	//printf("UpdateWorkParam end\r\n");
}

void EnableOpt()
{
	UINT16 tmp;
	UINT16 i;
	
	tmp = 0;
	
	for ( i=0; i<FP_MAX; i++ )
	{
		if ( 0!=sys_param_1b[MADD_FP1_EN+i].val )
		{
			#ifdef CLIENT_XINMIN
			tmp |= (0x01<<(7-i));
			#else
			tmp |= (0x01<<i);
			#endif
		}
	} 
	
	fp_enable = (UINT16)tmp;
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_OPT_ON, fp_enable );
	FPGA_DISABLE_WRITE;

}

/*************************************************************
Name: SetRecFcmps          
Description: 设置REC的频率补偿因子
Input: void
Return: void
**************************************************************/
void SetRecFcmps()
{
	UCHAR8 msg[FPGA_MSG_FRAME_LEN];
	UINT32 tx_len;
	
	msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	msg[MSG_CMD_ID] = MSG_CMD_SET_DEV_REG;
	msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;

	tx_len = MSG_PKT_HEAD_SIZE;
	msg[tx_len++] = DEV_ID_FPGA;

//	SendMsgPkt(tx_len, msg);
}

/*************************************************************
Name: SysBroadcastReFcA          
Description: 广播设置RE的频点
Input: void
Return: void
**************************************************************/
void SysBroadcastReFcA( void )
{
}

/*************************************************************
Name: SetReDpxInfo          
Description: 设置RE的上行输出功率门限
Input: void
Return: void
**************************************************************/
void SetReDpxInfo()
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;

	p_msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	p_msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	p_msg[MSG_DES_REE] = 0;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;	
	p_msg[MSG_CMD_ID] = MSG_CMD_SET_PARAM;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

	// REC的A段输入双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_A_REC_DPX_IG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_A_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_A_UDPX_IN_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC的A段输出双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_A_REC_DPX_OG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_A_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_A_UDPX_OUT_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	// REC的B段输入双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_B_REC_DPX_IG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_B_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_B_UDPX_IN_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC的B段输出双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_B_REC_DPX_OG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_B_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_B_UDPX_OUT_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	
	// REC的C段输入双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_C_REC_DPX_IG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_C_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_C_UDPX_IN_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC的C段输出双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_C_REC_DPX_OG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_C_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_C_UDPX_OUT_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	// REC的D段输入双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_D_REC_DPX_IG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_D_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_D_UDPX_IN_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC的D段输出双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_D_REC_DPX_OG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_D_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_D_UDPX_OUT_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	TRACE_INFO("-------SetReDpxInfo---------MADD_A_REC_DPX_IG:%04X\r\n",sys_param_2b[MADD_A_UDPX_IN_GAIN].val);		
	SendMsgPkt(tx_len, p_msg);
	
}

/*************************************************************
Name: SetReUlPowerGain          
Description: 设置RE的上行输出功率门限
Input: void
Return: void
**************************************************************/
void SetReUlPowerGain()
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	INT16 total_pow;
	INT16 pow_set;
	UINT16 tmp;

	if ( 0!=(sys_work_info&SYSTEM_FLAG_ATT_ADJ) )		// 处于校准状态，不设置RE参数
	{
		return;
	}

	if ((total_re_count == 0 )||( total_re_count>(FP_MAX*RE_MAX)))
	{
		return;
	}
	
	TRACE_INFO("Set Re PowGain\r\n");
	
	//total_re_count--;
	
	p_msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	p_msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	p_msg[MSG_DES_REE] = 0;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;
	p_msg[MSG_CMD_ID] = MSG_CMD_SET_PARAM;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

	// A段上行功率---------- 界面设置的上行输出功率
	total_pow = (INT16)sys_param_2b[MADD_A_UCH_MAX_POW1].val;
	//pow_set = total_pow-(INT16)(pow_div_tbl[total_re_count]+0.5);
	pow_set = total_pow;		// 功率不平分
	// 地址
	p_msg[tx_len++] = (UCHAR8)(MADD_A_UCH_MAX_POW1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_A_UCH_MAX_POW1>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 2;
	// 数据
	p_msg[tx_len++] = (UCHAR8)(pow_set&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((pow_set>>8)&0x00FF);

	//A段下行总衰减---------
	// 地址，REC的下行总衰减对应RE的上行数控衰减地址2
	p_msg[tx_len++] = (UCHAR8)(MADD_A_DCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_A_DCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_A_DCH_ATT11:%04X\r\n",sys_param_1b[MADD_A_DCH_ATT1].val);	
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_A_DCH_ATT1].val;	

	// A段上行总衰减---------
	// 地址，REC的上行总衰减对应RE的上行数控衰减地址2
	p_msg[tx_len++] = (UCHAR8)(MADD_A_UCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_A_UCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_A_UCH_ATT11:%04X\r\n",sys_param_1b[MADD_A_UCH_ATT1].val);	
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_A_UCH_ATT1].val;	
	
	// B段上行功率----------
	total_pow = (INT16)sys_param_2b[MADD_B_UCH_MAX_POW1].val;
	//pow_set = total_pow-pow_div_tbl[total_re_count];
	pow_set = total_pow;		// 功率不平分
	// 地址
	p_msg[tx_len++] = (UCHAR8)(MADD_B_UCH_MAX_POW1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_B_UCH_MAX_POW1>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 2;
	// 数据
	p_msg[tx_len++] = (UCHAR8)(pow_set&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((pow_set>>8)&0x00FF);

	//B段下行总衰减---------
	// 地址，REC的下行总衰减对应RE的上行数控衰减地址2
	p_msg[tx_len++] = (UCHAR8)(MADD_B_DCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_B_DCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_B_DCH_ATT11:%04X\r\n",sys_param_1b[MADD_B_DCH_ATT1].val);	
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_B_DCH_ATT1].val;	

	// B段上行总衰减----------
	// 地址，REC的上行总衰减对应RE的上行数控衰减地址2
	p_msg[tx_len++] = (UCHAR8)(MADD_B_UCH_REC_RF_ATT1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_B_UCH_REC_RF_ATT1>>8)&0x00FF);//20130302 modifi 
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_B_UCH_ATT1].val;


	// C段上行功率---------- 界面设置的上行输出功率
	total_pow = (INT16)sys_param_2b[MADD_C_UCH_MAX_POW1].val;
	//pow_set = total_pow-(INT16)(pow_div_tbl[total_re_count]+0.5);
	pow_set = total_pow;		// 功率不平分
	// 地址
	p_msg[tx_len++] = (UCHAR8)(MADD_C_UCH_MAX_POW1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_C_UCH_MAX_POW1>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 2;
	// 数据
	p_msg[tx_len++] = (UCHAR8)(pow_set&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((pow_set>>8)&0x00FF);

	//C段下行总衰减---------
	// 地址，REC的下行总衰减对应RE的上行数控衰减地址2
	p_msg[tx_len++] = (UCHAR8)(MADD_C_DCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_C_DCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_C_DCH_ATT11:%04X\r\n",sys_param_1b[MADD_C_DCH_ATT1].val);	
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_C_DCH_ATT1].val;	

	//C段上行总衰减---------
	// 地址，REC的上行总衰减对应RE的上行数控衰减地址2
	p_msg[tx_len++] = (UCHAR8)(MADD_C_UCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_C_UCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_C_UCH_ATT11:%04X\r\n",sys_param_1b[MADD_C_UCH_ATT1].val);	
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_C_UCH_ATT1].val;	
	
	// D段上行功率----------
	total_pow = (INT16)sys_param_2b[MADD_D_UCH_MAX_POW1].val;
	//pow_set = total_pow-pow_div_tbl[total_re_count];
	pow_set = total_pow;		// 功率不平分
	// 地址
	p_msg[tx_len++] = (UCHAR8)(MADD_D_UCH_MAX_POW1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_D_UCH_MAX_POW1>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 2;
	// 数据
	p_msg[tx_len++] = (UCHAR8)(pow_set&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((pow_set>>8)&0x00FF);

	//D段下行总衰减---------
	// 地址，REC的下行总衰减对应RE的上行数控衰减地址2
	p_msg[tx_len++] = (UCHAR8)(MADD_D_DCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_D_DCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_D_DCH_ATT11:%04X\r\n",sys_param_1b[MADD_D_DCH_ATT1].val);	
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_D_DCH_ATT1].val;	

	// D段上行总衰减----------
	// 地址，REC的上行总衰减对应RE的上行数控衰减地址2
	p_msg[tx_len++] = (UCHAR8)(MADD_D_UCH_REC_RF_ATT1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_D_UCH_REC_RF_ATT1>>8)&0x00FF);//20130302 modifi 
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_D_UCH_ATT1].val;
	
	p_msg[tx_len++] = (UCHAR8)(MADD_A_DL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_A_DL_RF_EN>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_A_DL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_A_UL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_A_UL_RF_EN>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_A_UL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_B_DL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_B_DL_RF_EN>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_B_DL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_B_UL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_B_UL_RF_EN>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_B_UL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_C_DL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_C_DL_RF_EN>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_C_DL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_C_UL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_C_UL_RF_EN>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_C_UL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_D_DL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_D_DL_RF_EN>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_D_DL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_D_UL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_D_UL_RF_EN>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_D_UL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_FREQ_MODIF_VAL_D&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_FREQ_MODIF_VAL_D>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val;	

	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_A&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_A>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_DELAY_MODE_A].val;	

	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_B&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_B>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_DELAY_MODE_B].val;	

	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_C&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_C>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_DELAY_MODE_C].val;	
	
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_D&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_D>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_DELAY_MODE_D].val;	

	// REC的A段输入双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_A_REC_DPX_IG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_A_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_A_UDPX_IN_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC的A段输出双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_A_REC_DPX_OG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_A_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_A_UDPX_OUT_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	// REC的B段输入双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_B_REC_DPX_IG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_B_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_B_UDPX_IN_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC的B段输出双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_B_REC_DPX_OG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_B_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_B_UDPX_OUT_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	
	// REC的C段输入双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_C_REC_DPX_IG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_C_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_C_UDPX_IN_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC的C段输出双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_C_REC_DPX_OG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_C_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_C_UDPX_OUT_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	// REC的D段输入双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_D_REC_DPX_IG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_D_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_D_UDPX_IN_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC的D段输出双工器增益
	p_msg[tx_len++] = (UCHAR8)(MADD_D_REC_DPX_OG&0x00FF);			// RE中的REC双工器参数地址
	p_msg[tx_len++] = (UCHAR8)((MADD_D_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// 长度
	tmp = sys_param_2b[MADD_D_UDPX_OUT_GAIN].val;		// 数据
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	TRACE_INFO("-------SetReDpxInfo---------MADD_A_REC_DPX_IG:%04X\r\n",sys_param_2b[MADD_A_UDPX_IN_GAIN].val);		
	
	// 宽带滤波器带宽
	p_msg[tx_len++] = (UCHAR8)(MADD_GSM_BW_SEL&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_GSM_BW_SEL>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = sys_param_1b[MADD_GSM_BW_SEL].val;	
	
	
	//TRACE_INFO("MADD_B_UCH_ATT11:%04X\r\n",sys_param_1b[MADD_D_UCH_ATT1].val);	

	TRACE_INFO("Set Re PowGain_p_msg[MSG_DES_REE]:%02x\r\n",p_msg[MSG_DES_REE]);
	SendMsgPkt(tx_len, p_msg);


}

/*************************************************************
Name: SetReSysConfig          
Description: 设置RE的上行输出功率门限
Input: void
Return: void
**************************************************************/
void SetReBwConfig()
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;

	p_msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	p_msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	p_msg[MSG_DES_REE] = BROADCAST_ADD_REE;	
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;	
	p_msg[MSG_CMD_ID] = MSG_CMD_SET_PARAM;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE; 

	// 宽带滤波器带宽
	p_msg[tx_len++] = (UCHAR8)(MADD_GSM_BW_SEL&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_GSM_BW_SEL>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = sys_param_1b[MADD_GSM_BW_SEL].val;	

	SendMsgPkt(tx_len, p_msg);
	
}

/*************************************************************
Name: SetReSysConfig          
Description: 设置RE的延时模式 
Input: void 
Return: void 
**************************************************************/
void SetReSysConfig()
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;

	if ( 0!=(sys_work_info&SYSTEM_FLAG_ATT_ADJ) )		// 处于校准状态，不设置RE参数
	{
		return;
	}
	if ((total_re_count == 0 )||( total_re_count>(FP_MAX*RE_MAX)))
	{  
		return;    
	}
	
	TRACE_INFO("Set Re Delay\r\n");

	p_msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	p_msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	p_msg[MSG_DES_REE] = 0;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;
	p_msg[MSG_CMD_ID] = MSG_CMD_SET_PARAM;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

//	tmp = sys_param_2b[MADD_A_UCH_POW1].addr;
	// 延时模式地址
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE].val;	

	sys_param_1b[MADD_DELAY_MODE_A].val=sys_param_1b[MADD_DELAY_MODE].val;
	sys_param_1b[MADD_DELAY_MODE_B].val=sys_param_1b[MADD_DELAY_MODE].val;
	sys_param_1b[MADD_DELAY_MODE_C].val=sys_param_1b[MADD_DELAY_MODE].val;
	sys_param_1b[MADD_DELAY_MODE_D].val=sys_param_1b[MADD_DELAY_MODE].val;
	
	// 延时模式地址
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_A&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_A>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE_A].val;	

	// 延时模式地址
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_B&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_B>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE_B].val;	

	// 延时模式地址
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_C&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_C>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE_C].val;		

	// 延时模式地址
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_D&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_D>>8)&0x00FF);
	// 长度
	p_msg[tx_len++] = 1;
	// 数据
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE_D].val;		

	//crc
	p_msg[tx_len++] =0;	
	p_msg[tx_len++] = 0;
	
	SendMsgPkt(tx_len, p_msg);
	
}

/*************************************************************
Name: SetReDelayMode          
Description: 设置RE的TD参数
Input: void 
Return: void
**************************************************************/
void SetReTDParam()
{
	const UINT16 mo_param_add_list1[]={		// 一字节参数，TD通道上下行设置
		MADD_TD_T0_UD, 
		MADD_TD_T1_UD, 	
		MADD_TD_T2_UD, 
		MADD_TD_T3_UD, 
		MADD_TD_T4_UD, 
		MADD_TD_T5_UD,	
		MADD_TD_T6_UD,
	};
	const UINT16 mo_param_add_list2[]={		 // 二字节参数，TD转换点时间
		MADD_TD_1ST_CP_TIME,
		MADD_TD_2ND_CP_TIME, 
		MADD_TD_LNA_ON_TIME, 
		MADD_TD_LNA_OFF_TIME, 
	};
	
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;
	UINT32 i;

	if ( 0!=(sys_work_info&SYSTEM_FLAG_ATT_ADJ) )		// 处于校准状态，不设置RE参数
	{
		return;
	}
		
	if ((total_re_count == 0 )||( total_re_count>(FP_MAX*RE_MAX)))
	{
		//return;
	}
	
	TRACE_INFO("---------------Set Re TD Param------------\r\n");

	p_msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	p_msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	p_msg[MSG_DES_REE] = 0;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;	
	p_msg[MSG_CMD_ID] = MSG_CMD_SET_PARAM;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

//-------------------------------B----------------------//
	for ( i=0; i<ARRY_NUM(mo_param_add_list1, UINT16); i++)
	{
		tmp = mo_param_add_list1[i];	// MADD_TD_T0_UD+i;
		// TD时隙上下行模式地址
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		// 长度
		p_msg[tx_len++] = 1;
		// 数据
		p_msg[tx_len++] = sys_param_1b[tmp].val;	
	}
	
	for ( i=0; i<ARRY_NUM(mo_param_add_list2, UINT16); i++)
	{
		tmp = mo_param_add_list2[i];	// MADD_TD_T0_UD+i;
		// TD时隙上下行模式地址
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		// 长度
		p_msg[tx_len++] = 2;
		// 数据
		tmp = sys_param_2b[tmp].val;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	}

		p_msg[tx_len++] = (UCHAR8)(MADD_TD_WORK_MODE&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_TD_WORK_MODE>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_TD_WORK_MODE].val;	


//--------------------------------C-----------------------------//

		p_msg[tx_len++] = (UCHAR8)(MADD_C_TD_WORK_MODE&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_C_TD_WORK_MODE>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_C_TD_WORK_MODE].val;	

		p_msg[tx_len++] = (UCHAR8)(MADD_C_TD_1ST_CP_TIME&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_C_TD_1ST_CP_TIME>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[MADD_C_TD_1ST_CP_TIME].val&0Xff);	
		p_msg[tx_len++] = (UCHAR8)((sys_param_2b[MADD_C_TD_1ST_CP_TIME].val>>8)&0Xff);	

		p_msg[tx_len++] = (UCHAR8)(MADD_C_TD_2ND_CP_TIME&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_C_TD_2ND_CP_TIME>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[MADD_C_TD_2ND_CP_TIME].val&0Xff);	
		p_msg[tx_len++] = (UCHAR8)((sys_param_2b[MADD_C_TD_2ND_CP_TIME].val>>8)&0Xff);	


		p_msg[tx_len++] = (UCHAR8)(MADD_C_TD_LNA_ON_TIME&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_C_TD_LNA_ON_TIME>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[MADD_C_TD_LNA_ON_TIME].val&0Xff);	
		p_msg[tx_len++] = (UCHAR8)((sys_param_2b[MADD_C_TD_LNA_ON_TIME].val>>8)&0Xff);	

		p_msg[tx_len++] = (UCHAR8)(MADD_C_TD_LNA_OFF_TIME&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_C_TD_LNA_OFF_TIME>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[MADD_C_TD_LNA_OFF_TIME].val&0Xff);	
		p_msg[tx_len++] = (UCHAR8)((sys_param_2b[MADD_C_TD_LNA_OFF_TIME].val>>8)&0Xff);	

		p_msg[tx_len++] = (UCHAR8)(MADD_C_TD_TYPE_SELECT&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_C_TD_TYPE_SELECT>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_C_TD_TYPE_SELECT].val;	

		p_msg[tx_len++] = (UCHAR8)(MADD_C_TD_NORMAL_CP&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_C_TD_NORMAL_CP>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_C_TD_NORMAL_CP].val;	

		p_msg[tx_len++] = (UCHAR8)(MADD_C_TD_EXTENDED_CP&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_C_TD_EXTENDED_CP>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_C_TD_EXTENDED_CP].val;

//----------------------------D-----------------------------------//
	TRACE_INFO("---------------Set Re TD Param_end------------\r\n");


		SendMsgPkt(tx_len, p_msg);

	
}

/*************************************************************
Name:SetAttByParam
Description: 将参数表中的衰减器值写入FPGA中
Input: void
Output:void         
Return:void
**************************************************************/
void SetAttByParam( UCHAR8 ab_flag )	
{
}



/*************************************************************
Name: GetPsfFromRe
Description: 从RE读取选频功率值，校准时用
Input: void
Output:void         
Return:void
**************************************************************/
void GetPsfFromRe( UCHAR8 ab_flag, UCHAR8 ud_flag )
{
	UCHAR8 msg[64];
	UCHAR8 ch = 0,attr = 0,attr2 =0;
	UINT16 reg_psf_l, reg_psf_h; 
	UINT32 tx_len;

	if ( SYS_A_FLAG == ab_flag )
	{
		if ( ATT_UL_ADJ==ud_flag )
		{
			reg_psf_l = FPGA_REG_RE_A_UPSF_L;		// 上行选频通道功率低16位
			reg_psf_h = FPGA_REG_RE_A_UPSF_H;		// 上行选频通道功率高16位
		}
		else
		{
			reg_psf_l = FPGA_REG_RE_A_DPSF_L;		// 下行选频通道功率低16位
			reg_psf_h = FPGA_REG_RE_A_DPSF_H;		// 下行选频通道功率高16位
		}
		switch(fpga_cfg.a_net_type)
		{
			case NET_TYPE_LTE_TD :
				attr = FPGA_TDS_LTE_REG;
				break;
			default:
				attr = REG_TYPE_NORMAL;
				break;
		}
	}
	else if ( SYS_B_FLAG == ab_flag )
	{
		if ( ATT_UL_ADJ==ud_flag )
		{
			reg_psf_l = FPGA_REG_RE_B_UPSF_L;		// 上行选频通道功率低16位
			reg_psf_h = FPGA_REG_RE_B_UPSF_H;		// 上行选频通道功率高16位
		}
		else
		{
			reg_psf_l = FPGA_REG_RE_B_DPSF_L;		// 下行选频通道功率低16位
			reg_psf_h = FPGA_REG_RE_B_DPSF_H;		// 下行选频通道功率高16位
		}


		switch(fpga_cfg.b_net_type)
		{
			case NET_TYPE_LTE_TD :
				attr = FPGA_TDS_LTE_REG;
				break;
			default:
				attr = REG_TYPE_NORMAL;
				break;
		}
	}
	else if ( SYS_C_FLAG == ab_flag )
	{
		if ( ATT_UL_ADJ==ud_flag )
		{
			reg_psf_l = FPGA_REG_RE_C_UPSF_L;		// 上行选频通道功率低16位
			reg_psf_h = FPGA_REG_RE_C_UPSF_H;		// 上行选频通道功率高16位
		}
		else
		{
			reg_psf_l = FPGA_REG_RE_C_DPSF_L;		// 下行选频通道功率低16位
			reg_psf_h = FPGA_REG_RE_C_DPSF_H;		// 下行选频通道功率高16位
		}

		switch(fpga_cfg.c_net_type)
		{
			case NET_TYPE_LTE_TD :
				attr = FPGA_TDS_LTE_REG;
				break;
			default:
				attr = REG_TYPE_NORMAL;
				break;
		}
	}
	else if ( SYS_D_FLAG == ab_flag )
	{
		if ( ATT_UL_ADJ==ud_flag )
		{
			reg_psf_l = FPGA_REG_RE_D_UPSF_L;		// 上行选频通道功率低16位
			reg_psf_h = FPGA_REG_RE_D_UPSF_H;		// 上行选频通道功率高16位
		}
		else
		{
			reg_psf_l = FPGA_REG_RE_D_DPSF_L;		// 下行选频通道功率低16位
			reg_psf_h = FPGA_REG_RE_D_DPSF_H;		// 下行选频通道功率高16位
		}

		switch(fpga_cfg.d_net_type)
		{
			case NET_TYPE_LTE_TD :
				attr = FPGA_TDS_LTE_REG;
				break;
			default:
				attr = REG_TYPE_NORMAL;
				break;
		}
	}

	// 包头
	msg[MSG_DES_FP] = ADJ_ADDR_AU;	    // 所有光口
	msg[MSG_DES_RE] = ADJ_ADDR_EU;					// 第一个MEU	
	msg[MSG_DES_REE] = ADJ_ADDR_RU;					// 第一个MRU
	msg[MSG_SRC_FP] = LOCAL_ADD_FP;         //00
	msg[MSG_SRC_RE] = LOCAL_ADD_RE;         //00
	msg[MSG_SRC_REE] = LOCAL_ADD_REE;         //00
	msg[MSG_CMD_ID] = MSG_CMD_GET_FPGA_REG;
	msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	msg[MSG_RESERVE1] = 0xE7;
	msg[MSG_RESERVE2] = 0x11;

	tx_len = MSG_PKT_HEAD_SIZE;
	// 低地址
	msg[tx_len++] = attr|ch;		// 通道0
	msg[tx_len++] = attr2;		
	msg[tx_len++] = (UCHAR8)(reg_psf_l&0x0ff);
	msg[tx_len++] = (UCHAR8)((reg_psf_l>>8)&0x0ff);
	msg[tx_len++] = 0;
	msg[tx_len++] = 0;
	// 高16位地址
	msg[tx_len++] = attr|ch;		// 通道0
	msg[tx_len++] = attr2;		
	msg[tx_len++] = (UCHAR8)(reg_psf_h&0x0ff);
	msg[tx_len++] = (UCHAR8)((reg_psf_h>>8)&0x0ff);
	msg[tx_len++] = 0;
	msg[tx_len++] = 0;

	// CRC
	msg[tx_len+0] = 0;
	msg[tx_len+1] = 0;

	SendMsgPkt(tx_len, msg);
	
}

/*************************************************************
Name: SetReID         
Description: 设置RE的ID号
Input: 
	fp: 光口号(0开始)
	re: 节点号(0开始)
	id: ID号
Return: void
**************************************************************/
void SetReID( UCHAR8 fp, UCHAR8 re, UCHAR8 rf,  UCHAR8 id )
{
	UCHAR8 msg[FPGA_MSG_FRAME_LEN];
	UINT32 tx_len;
	INT16 total_pow;
	INT16 pow_set;
	UINT16 tmp;
	
	msg[MSG_DES_FP] = fp+1;
	msg[MSG_DES_RE] = re+1;
	msg[MSG_DES_REE] = 0;
	msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	msg[MSG_SRC_REE] = LOCAL_ADD_REE;
	msg[MSG_CMD_ID] = MSG_CMD_SET_PARAM;
	msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

	// ID号地址
	msg[tx_len++] = (UCHAR8)(MADD_MODULE_HRI_ID&0x00FF);	
	msg[tx_len++] = (UCHAR8)((MADD_MODULE_HRI_ID>>8)&0x00FF);
	// 长度
	msg[tx_len++] = 1;
	// 数据
	msg[tx_len++] = id;	
	
	msg[tx_len] = 0;	
	msg[tx_len+1] = 0;	

	SendMsgPkt(tx_len, msg);
	
}

void SysLowPowerMode()
{
#ifndef AD9528
	// 9517除了给FPGA的时钟外,全部PowerDown
	Ad9524Write( 0xF0, 0x01|Ad9524Read(0xF0) );		// OUT0
	Ad9524Write( 0xF1, 0x01|Ad9524Read(0xF1) );		// OUT1
	Ad9524Write( 0xF4, 0x01|Ad9524Read(0xF4) );		// OUT2
	Ad9524Write( 0xF5, 0x01|Ad9524Read(0xF5) );		// OUT3
	// OUT4, OUT5作为Serdes的时钟给FPGA提供工作时钟,不关断
	Ad9524Write( 0x142, 0x01|Ad9524Read(0x142) );		// OUT6
	Ad9524Write( 0x143, 0x01|Ad9524Read(0x143) );		// OUT7
#endif
	// AD-PowerDown, 08寄存器写01-内部完全掉电
	//Ad6649Write(AD6655_ADD_CHANNEL, 0x03);			// 0x05
	Ad6649Write(0x08, 0x01);  

	// DA-PowerDown, 0地址的bit4置1
	Ad9122Write( 0, (1<<4)|Ad9122Read(0, DA_A_FLAG), DA_A_FLAG );		
	Ad9122Write( 0, (1<<4)|Ad9122Read(0, DA_B_FLAG), DA_B_FLAG );		
	
	// 4153-PowerDown, 2地址的bit4置1
	//SetADF4153Reg( (1<<4)|GetADF4153Reg(2, MIXER_FRONT, MIXER_A_FLAG), MIXER_FRONT, MIXER_A_FLAG);
	//SetADF4153Reg( (1<<4)|GetADF4153Reg(2, MIXER_BACK, MIXER_A_FLAG), MIXER_BACK, MIXER_A_FLAG);
	//SetADF4153Reg( (1<<4)|GetADF4153Reg(2, MIXER_FRONT, MIXER_B_FLAG), MIXER_FRONT, MIXER_B_FLAG);
	//SetADF4153Reg( (1<<4)|GetADF4153Reg(2, MIXER_BACK, MIXER_B_FLAG), MIXER_BACK, MIXER_B_FLAG);

	// 关闭5.5V模拟电源
	DisablePower5V5;

	// 设置低功耗模式标志
	sys_work_info |= SYSTEM_FLAG_LOW_POWER;

}

void SysNormalWorkMode()
{
	sys_work_info &= (~SYSTEM_FLAG_LOW_POWER);
#ifndef AD9528
	// 初始化9517
	Ad9524Write( 0xF0, (~0x01)&Ad9524Read(0xF0) );		// OUT0
	Ad9524Write( 0xF1, (~0x01)&Ad9524Read(0xF1) );		// OUT1
	Ad9524Write( 0xF4, (~0x01)&Ad9524Read(0xF4) );		// OUT2
	Ad9524Write( 0xF5, (~0x01)&Ad9524Read(0xF5) );		// OUT3
	// OUT4, OUT5作为Serdes的时钟给FPGA提供工作时钟,不关断
	Ad9524Write( 0x142, (~0x01)&Ad9524Read(0x142) );		// OUT6
	Ad9524Write( 0x143, (~0x01)&Ad9524Read(0x143) );		// OUT7
#endif
	// 初始化4153
	//InitADF4153AF();
	//InitADF4153AB();
	//InitADF4153BF();
	//InitADF4153BB();
		
	// 初始化AD
	Ad6649Write(0x08, 0x00);

	// 初始化DA
	Ad9122Write( 0, (~0x10)&Ad9122Read(0, DA_A_FLAG), DA_A_FLAG );		
	Ad9122Write( 0, (~0x10)&Ad9122Read(0, DA_B_FLAG), DA_B_FLAG );		

	// 打开5.5V模拟电源
	EnablePower5V5;

}

/*************************************************************
Name:CheckReID          
Params: [reset_fp: 0-继续之前的搜索，非0-重置搜索起始频点，并重新开始搜索]
Return: void
Description: TD自动频点搜索功能，当发现TD无法同步之后，自动切换频点，知道TD重新同步，函数要求每秒调用1次
**************************************************************/
void TdAutoSearchFp( UCHAR8 reset_fp )
{
}
/*************************************************************
Name: TempGainCompensate
Params: [force_set: 强制根据当前温度更新补偿值, 1有效]
Return: void
Description: 执行温度补偿功能(由于温度变化较慢，应3秒钟调用一次)
**************************************************************/
void TempGainCompensate( UCHAR8 force_set )
{
	static CHAR8 temp_old = 25;	// 前一次的温度值
	static CHAR8 comp_id = -1;	// 补偿表下标
	CHAR8 temp_now;
	CHAR8 seg, index;

	// 读取当前温度
	temp_now = (CHAR8)sys_param_1b[MADD_BOARD_TEMP].val;
	//temp_now=-11;
	// 前后两次温度一样
	if (( temp_old==temp_now )||( 1==force_set ))
	{
		index = 0;
		for ( seg=-15; seg<90; seg+=10 )
		{
//			TRACE_INFO("temp_cmp_tbl_aul[index]=[%d],index=[%d]\r\n", temp_cmp_tbl_aul[index],index );		

			if ( temp_now<seg )
			{
				break;
			}
			index++;			
		}
//		TRACE_INFO("(CHAR8)sys_param_1b[MADD_BOARD_TEMP].val(%d),temp_cmp_tbl_aul[index]=[%d],index=[%d]\r\n", (CHAR8)sys_param_1b[MADD_BOARD_TEMP].val,temp_cmp_tbl_aul[index],index );		
//		TRACE_INFO("(CHAR8)sys_param_1b[MADD_BOARD_TEMP].val(%d),temp_cmp_tbl_adl[index]=[%d],index=[%d]\r\n", (CHAR8)sys_param_1b[MADD_BOARD_TEMP].val,temp_cmp_tbl_adl[index],index );
//		TRACE_INFO("(CHAR8)sys_param_1b[MADD_BOARD_TEMP].val(%d),temp_cmp_tbl_bul[index]=[%d],index=[%d]\r\n", (CHAR8)sys_param_1b[MADD_BOARD_TEMP].val,temp_cmp_tbl_bul[index],index );
//		TRACE_INFO("(CHAR8)sys_param_1b[MADD_BOARD_TEMP].val(%d),temp_cmp_tbl_bdl[index]=[%d],index=[%d]\r\n", (CHAR8)sys_param_1b[MADD_BOARD_TEMP].val,temp_cmp_tbl_bdl[index],index );
//		printf("index=[%d],temp_now=[%d]",index,temp_now);
		if (( index != comp_id )||( 1==force_set ))
		{
			
			comp_id = index;
			// 设置A段温度补偿
			////FpgaSetTempComp( 0, 0, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_aul[index]/1000.0) );
			////FpgaSetTempComp( 0, 1, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_adl[index]/1000.0) );

			// 设置B段温度补偿
			////FpgaSetTempComp( 1, 0, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_bul[index]/1000.0) );
			////FpgaSetTempComp( 1, 1, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_bdl[index]/1000.0) );

			// 设置C段温度补偿
			////FpgaSetTempComp( 2, 0, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_cul[index]/1000.0) );
			////FpgaSetTempComp( 2, 1, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_cdl[index]/1000.0) );

			// 设置D段温度补偿
			////FpgaSetTempComp( 3, 0, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_dul[index]/1000.0) );
			////FpgaSetTempComp( 3, 1, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_ddl[index]/1000.0) );		
		}
	}

	// 保存本次温度
	temp_old = temp_now;

}
/*************************************************************
Name: NoiseTest          
Description: 底噪测试功能用
Input: void
Return: void
**************************************************************/

void NoiseTest(void)

{
	UCHAR8 	tmp1 ,tmp2;

	//tmp1 =	ReadWriteTF(noise_test_st.type,0,0x077,0);
	//tmp2 =	ReadWriteTF(noise_test_st.type,0,0x07C,0);
	ReadWriteTF(noise_test_st.type,1,0x077,0X40);
	ReadWriteTF(noise_test_st.type,1,0x07c,0X40);
	//printf("noise_test_st.test_mode = %02x,noise_test_st.mcu_control = %02x,noise_test_st.type = %02x,noise_test_st.value = %02x\r\n",noise_test_st.test_mode ,noise_test_st.mcu_control ,noise_test_st.type ,noise_test_st.value );
	//printf("9363_0x17_0 = %02x,\r\n",ReadWriteTF(TF_B,0,0x0017,0) );

	if(noise_test_st.test_mode == 0x01)
	{	
		if(noise_test_st.mcu_control == 0x01)
		{
			//进入MCU控制模式
			//ReadWriteTF(noise_test_st.type,1,0x077,tmp1|0X40);
			//ReadWriteTF(noise_test_st.type,1,0x07c,tmp2|0X40);
			//0x73 0x75写1
			if(noise_test_st.type == SYS_C_FLAG)
			{
				//printf("C data = %d\r\n",noise_test_st.value);
				ReadWriteTF(TF_D,1,0x0073,0);
				ReadWriteTF(TF_C,1,0x0075,(UCHAR8)(noise_test_st.value*4));
				ReadWriteTF(TF_B,1,0x0073,0);				
				
				//printf("c--设置0x75\r\n");
			}
			else if(noise_test_st.type == SYS_D_FLAG)
			{
				ReadWriteTF(TF_C,1,0x0075,0);
				//printf("D data = %d\r\n",noise_test_st.value);
				ReadWriteTF(TF_D,1,0x0073,(UCHAR8)(noise_test_st.value*4));
				ReadWriteTF(TF_B,1,0x0073,0);				
				//printf("d--设置0x73\r\n");
			}
			else if(noise_test_st.type == SYS_B_FLAG)
			{
				//printf("B data = %d\r\n",noise_test_st.value);
				ReadWriteTF(TF_C,1,0x0075,0);
				ReadWriteTF(TF_D,1,0x0073,0);
				ReadWriteTF(TF_B,1,0x0073,(UCHAR8)(noise_test_st.value*4));
				//printf("设置B--0x73\r\n");
				//printf("设置B--0x73--9363_0x17_0 = %02x,\r\n",ReadWriteTF(TF_B,0,0x0017,0) );
				
			}
			//执行本振泄露校准过程
			ReadWriteTF(noise_test_st.type,1,0x0169,0xcc);
			WTD_CLR;
			UsNopDelay(1000);
			ReadWriteTF(noise_test_st.type,1,0x018B,0x8d);
			WTD_CLR;
			UsNopDelay(1000);
			ReadWriteTF(noise_test_st.type,1,0x0014,0x03);
			WTD_CLR;
			UsNopDelay(1000);
			ReadWriteTF(noise_test_st.type,1,0x00ac,(UCHAR8)(noise_test_st.value*4));
			WTD_CLR;
			UsNopDelay(1000);
			ReadWriteTF(noise_test_st.type,1,0x0016,0x10);
			WTD_CLR;
			UsNopDelay(50000);
			ReadWriteTF(noise_test_st.type,1,0x0169,0xce);
			WTD_CLR;
			UsNopDelay(1000);
			ReadWriteTF(noise_test_st.type,1,0x018b,0xad);
			WTD_CLR;
			UsNopDelay(1000);
			ReadWriteTF(noise_test_st.type,1,0x0014,0x23);
			WTD_CLR;
			UsNopDelay(1000);
		}
		else
		{
			if(noise_test_st.type == SYS_B_FLAG)
			{		

				//退出MCU控制模式
				//ReadWriteTF(TF_C,1,0x077,tmp1|0X40);
				//ReadWriteTF(TF_C,1,0x07c,tmp2|0X40);
				//0x73 0x75写0
				//if(noise_test_st.type == SYS_C_FLAG)
				ReadWriteTF(TF_B,1,0x0073,0);
				WTD_CLR;
				UsNopDelay(1000);				
				//else if(noise_test_st.type == SYS_D_FLAG)
				ReadWriteTF(TF_B,1,0x0075,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//执行本振泄露校准过程			
				ReadWriteTF(TF_B,1,0x0169,0xcc);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x018B,0x8d);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x0014,0x03);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x00ac,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x0016,0x10);
				WTD_CLR;
				UsNopDelay(50000);				
				
				ReadWriteTF(TF_B,1,0x0169,0xce);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x018b,0xad);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x0014,0x23);
				//SetAtt3Tx(TF_C,0x14);

			}else 
			{
				//退出MCU控制模式
				//ReadWriteTF(TF_C,1,0x077,tmp1|0X40);
				//ReadWriteTF(TF_C,1,0x07c,tmp2|0X40);
				//0x73 0x75写0
				//if(noise_test_st.type == SYS_C_FLAG)
				ReadWriteTF(TF_C,1,0x0073,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//else if(noise_test_st.type == SYS_D_FLAG)
				ReadWriteTF(TF_C,1,0x0075,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//执行本振泄露校准过程
				ReadWriteTF(TF_C,1,0x0169,0xcc);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_C,1,0x018B,0x8d);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_C,1,0x0014,0x03);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_C,1,0x00ac,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_C,1,0x0016,0x10);
				WTD_CLR;
				UsNopDelay(50000);			
				
				ReadWriteTF(TF_C,1,0x0169,0xce);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_C,1,0x018b,0xad);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_C,1,0x0014,0x23);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//SetAtt3Tx(TF_C,0x14);
			}
		}
	}
	else
	{
		if(noise_test_st.type == SYS_B_FLAG)
		{		
			if(noise_test_st.mcu_control  == 0x01)
			{
				//退出MCU控制模式
				//ReadWriteTF(TF_C,1,0x077,tmp1|0X40);
				//ReadWriteTF(TF_C,1,0x07c,tmp2|0X40);
				//0x73 0x75写0
				//if(noise_test_st.type == SYS_C_FLAG)
				ReadWriteTF(TF_B,1,0x0073,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//else if(noise_test_st.type == SYS_D_FLAG)
				ReadWriteTF(TF_B,1,0x0075,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//执行本振泄露校准过程
				ReadWriteTF(TF_B,1,0x0169,0xcc);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x018B,0x8d);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x0014,0x03);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x00ac,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x0016,0x10);
				WTD_CLR;
				UsNopDelay(50000);				
				
				ReadWriteTF(TF_B,1,0x0169,0xce);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x018b,0xad);
				WTD_CLR;
				UsNopDelay(1000);				
				
				ReadWriteTF(TF_B,1,0x0014,0x23);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//SetAtt3Tx(TF_C,0x14);
			}
		}
		else 
		{		
			if(noise_test_st.mcu_control  == 0x01)
			{
				//退出MCU控制模式
				//ReadWriteTF(TF_C,1,0x077,tmp1|0X40);
				//ReadWriteTF(TF_C,1,0x07c,tmp2|0X40);
				//0x73 0x75写0
				//if(noise_test_st.type == SYS_C_FLAG)
				ReadWriteTF(TF_C,1,0x0073,0);
				WTD_CLR;
				UsNopDelay(1000);
				//else if(noise_test_st.type == SYS_D_FLAG)
				ReadWriteTF(TF_C,1,0x0075,0);
				WTD_CLR;
				UsNopDelay(1000);
				//执行本振泄露校准过程
				ReadWriteTF(TF_C,1,0x0169,0xcc);
				WTD_CLR;
				UsNopDelay(1000);
				ReadWriteTF(TF_C,1,0x018B,0x8d);
				WTD_CLR;
				UsNopDelay(1000);
				ReadWriteTF(TF_C,1,0x0014,0x03);
				WTD_CLR;
				UsNopDelay(1000);
				ReadWriteTF(TF_C,1,0x00ac,0);
				WTD_CLR;
				UsNopDelay(1000);
				ReadWriteTF(TF_C,1,0x0016,0x10);
				WTD_CLR;
				UsNopDelay(50000);
				ReadWriteTF(TF_C,1,0x0169,0xce);
				WTD_CLR;
				UsNopDelay(1000);
				ReadWriteTF(TF_C,1,0x018b,0xad);
				WTD_CLR;
				UsNopDelay(1000);
				ReadWriteTF(TF_C,1,0x0014,0x23);
				WTD_CLR;
				UsNopDelay(1000);
				//SetAtt3Tx(TF_C,0x14);
			}
		}
		
	}
//	printf("9363_0x17_1 = %02x,\r\n",ReadWriteTF(TF_B,0,0x0017,0) );
	
}

/*************************************************************
Name: MAUSetParamToMEU          
Description: 下发参数到拓展板
Input: void
Return: void
**************************************************************/
void MAUSetParamToMEU(void)
{
	if ( (0 !=	( sys_work_info & SYSTEM_FLAG_SET_RE_UPOW))
		||( 0 !=	(sys_work_info & SYSTEM_FLAG_SET_RE_SYS_CFG) ) )
	{
		// 设置RE的上行输出总功率(其值由界面设)
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_UPOW);
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_SYS_CFG);
		WTD_CLR; 
		//SetReUlPowerGain();
		// REC的双工器参数用单独的数据包发送，避免旧版RE程序不识别，导致其他参数也设置失败
		//SetReDpxInfo();

	}
	
	if ( 0 !=	(sys_work_info & SYSTEM_FLAG_SET_RE_SYS_CFG) )
	{
		WTD_CLR; 
		// 需要刷新RE的延时模式
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_SYS_CFG);
		//SetReSysConfig();
		//SetReBwConfig();

	}

	if ( 0!= (sys_work_info & SYSTEM_FLAG_SET_RE_TDSLOT ) )
	{
		WTD_CLR; 
		// 设置RE的TD时隙
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_TDSLOT);
		//SetReTDParam();
	}

	if ( 0!= (sys_work_info & SYSTEM_FLAG_SET_RE_SFC ) )
	{
		WTD_CLR; 
		// 设置RE的频点配置
		sys_work_info &= ( ~SYSTEM_FLAG_SET_RE_SFC );
		SysBroadcastReFcA();   
	}

}
/*************************************************************
Name: SetAdjBenZhenSignalPara
Params: 
Return: void
Description: 设置本振校准参数
**************************************************************/
void SetAdjBenZhenSignalPara( void)
{
	
	if((sys_param_1b[MADD_A_94_VALUE].val == 0xff)&&(sys_param_1b[MADD_A_95_VALUE].val == 0xff)
		&&(sys_param_1b[MADD_A_90_VALUE].val == 0xff)&&(sys_param_1b[MADD_A_91_VALUE].val == 0xff))
	{
		
		
	}
	else
	{
		ReadWriteTF(TF_A,1,0x9F,0x0A);
		ReadWriteTF(TF_A,1,0x90,sys_param_1b[MADD_A_90_VALUE].val);
		ReadWriteTF(TF_A,1,0x91,sys_param_1b[MADD_A_91_VALUE].val);
		ReadWriteTF(TF_A,1,0x94,sys_param_1b[MADD_A_94_VALUE].val);
		ReadWriteTF(TF_A,1,0x95,sys_param_1b[MADD_A_95_VALUE].val);
	}


	if((sys_param_1b[MADD_B_90_VALUE].val == 0xff)&&(sys_param_1b[MADD_B_91_VALUE].val == 0xff)
		&&(sys_param_1b[MADD_B_90_VALUE].val == 0xff)&&(sys_param_1b[MADD_B_91_VALUE].val == 0xff))
	{
		
	}
	else
	{
		ReadWriteTF(TF_B,1,0x9F,0x0A);
		ReadWriteTF(TF_B,1,0x90,sys_param_1b[MADD_B_90_VALUE].val);
		ReadWriteTF(TF_B,1,0x91,sys_param_1b[MADD_B_91_VALUE].val);
		ReadWriteTF(TF_B,1,0x94,sys_param_1b[MADD_B_94_VALUE].val);
		ReadWriteTF(TF_B,1,0x95,sys_param_1b[MADD_B_95_VALUE].val);
	}
	if((sys_param_1b[MADD_C_94_VALUE].val == 0xff)&&(sys_param_1b[MADD_C_95_VALUE].val == 0xff)
		&&(sys_param_1b[MADD_C_90_VALUE].val == 0xff)&&(sys_param_1b[MADD_C_91_VALUE].val == 0xff))
	{
		
		
	}
	else
	{
		ReadWriteTF(TF_C,1,0x9F,0x0f);
		ReadWriteTF(TF_C,1,0x90,sys_param_1b[MADD_C_90_VALUE].val);
		ReadWriteTF(TF_C,1,0x91,sys_param_1b[MADD_C_91_VALUE].val);
		ReadWriteTF(TF_C,1,0x94,sys_param_1b[MADD_C_94_VALUE].val);
		ReadWriteTF(TF_C,1,0x95,sys_param_1b[MADD_C_95_VALUE].val);
	}
	if((sys_param_1b[MADD_D_94_VALUE].val == 0xff)&&(sys_param_1b[MADD_D_95_VALUE].val == 0xff)
		&&(sys_param_1b[MADD_D_90_VALUE].val == 0xff)&&(sys_param_1b[MADD_D_91_VALUE].val == 0xff))
	{
		
		
	}
	else
	{
		ReadWriteTF(TF_D,1,0x9F,0x0f);
		ReadWriteTF(TF_D,1,0x8E,sys_param_1b[MADD_D_90_VALUE].val);
		ReadWriteTF(TF_D,1,0x8F,sys_param_1b[MADD_D_91_VALUE].val);
		ReadWriteTF(TF_D,1,0x92,sys_param_1b[MADD_D_94_VALUE].val);
		ReadWriteTF(TF_D,1,0x93,sys_param_1b[MADD_D_95_VALUE].val);
	}
		
}

/*************************************************************
Name: ZiDongShiXiPeiBi
Params: 
Return: void
Description: 自动时隙配比
**************************************************************/
void ZiDongShiXiPeiBi( void)
{	
	UINT16 tmp=0,tmp2=0,tmp3=0;
//获取自动时隙配比

}
/*************************************************************
Name: MoveBenZhenTo2345
Params: 
Return: void
Description: 根据条件移动本振(用于测试)
**************************************************************/
void MoveBenZhenTo2340( void)
{
	UINT32 fre = 0;
	FLOAT32 fre_f = 0;
	static UCHAR8 time_tick = 0,time_start =0 ;
	static UCHAR8 state = 0,change2340 = 0;
	if(time_start == 1)
	{
		time_tick++;
//		printf("计时器%d\r\n",time_tick);
		if(time_tick >= 10)
		{
			time_tick = 0;
			time_start = 0;
		}
		else
			return;
	}
		
	
	//同步
	 if(FpgaReadRegister(FPGA_REG_C_TD_SYNC_ST)&0x04) 
	 {
	 	//频偏5M
	 	fre = FpgaReadRegister(FPGA_REG_C_LTE_CUR_FREQ_L)|(FpgaReadRegister(FPGA_REG_C_LTE_CUR_FREQ_H)<<12);
//		printf("频偏%X\r\n",fre);
		fre_f = (FLOAT32)(fre/( 8192*1024*8*1/62.5));
//		printf("频偏F%f\r\n",fre_f);

		if((fre_f > 4)&&(fre_f < 6 ))
		{
			//移动本振至2340 (默认为2345)
			benzhen2340 = 1;
			if(state == 0)
				state= 1;
			//启动计时 10秒
			time_start = 1;
//			printf("同步小于5M\r\n");
			change2340 = 1;
		}
		else if((fre_f > 9)&&(fre_f < 11 ))
		{
			if(change2340 == 1)
			{
//				printf("不动r\n");
			}
			else
			{
//				printf("同步>于5M\r\n");
				benzhen2340 = 0;
				if(state == 2)
					state = 3;
				change2340 = 0;
			}
				
		}
		else 
		{
//			printf("同步>于5M\r\n");
			benzhen2340 = 0;
			if(state == 2)
				state = 3;
			change2340 = 0;
		}
	 }
	 else
	 {
//	 		printf("失步\r\n");
	 		benzhen2340 = 0;
			if(state == 2)
				state = 3;
			change2340 = 0;
	 }

	 if((state == 1)||(state == 3))
	 {		if(state == 1)
	 			state = 2;
	 		if(state == 3)
				state = 0;
//	 		printf("满足条件执行\r\n");
//	 		module_param_chg_flag |= PCHG_C_CHANNEL;
//			module_param_chg_flag |= PCHG_D_CHANNEL;
			MAUSetParamToMRU();
	 }
}

/*************************************************************
Name: MAUSetParamToMEU          
Description: 下发参数到拓展板
Input: void
Return: void
**************************************************************/
void MAUSetParamToMRU(void)
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;
	UINT32 i;
		
	p_msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	p_msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	p_msg[MSG_DES_REE] = BROADCAST_ADD_REE;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;	
	p_msg[MSG_CMD_ID] = MSG_CMD_AU;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

	
	p_msg[tx_len++] = 0;
	p_msg[tx_len++] = benzhen2340;

	SendMsgPkt(tx_len, p_msg);

}
/*************************************************************
Name: MAUSetParamToMEU          
Description: 下发参数到拓展板
Input: void
Return: void
**************************************************************/
void GainAdjSetEUFrePoint(UCHAR8 ab_flag,INT32 freq_point)
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;
	UINT32 i;
		
	p_msg[MSG_DES_FP] = 1;
	p_msg[MSG_DES_RE] = 1;
	p_msg[MSG_DES_REE] = 0;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;	
	p_msg[MSG_CMD_ID] = MSG_CMD_GAIN_ADJ;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

	p_msg[tx_len++] = GAIN_ADJ_ST_SET_AUEU_FRE;
	p_msg[tx_len++] = ab_flag;
	p_msg[tx_len++] = (UCHAR8)((freq_point>>0)&0xff);
	p_msg[tx_len++] = (UCHAR8)((freq_point>>8)&0xff);

	SendMsgPkt(tx_len, p_msg);
	
}
/*************************************************************
Name: MAUSetParamToMEU          
Description: 下发参数到拓展板
Input: void
Return: void
**************************************************************/
void GainAdjSetEUEnterAdjMode(UCHAR8 ab_flag)
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;
	UINT32 i;
		
	p_msg[MSG_DES_FP] = 1;
	p_msg[MSG_DES_RE] = 1;
	p_msg[MSG_DES_REE] = 0;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;	
	p_msg[MSG_CMD_ID] = MSG_CMD_GAIN_ADJ;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

	p_msg[tx_len++] = GAIN_ADJ_ST_SET_AUEU_ADJ_MODE;
	p_msg[tx_len++] = ab_flag;

	SendMsgPkt(tx_len, p_msg);
	
}
/*************************************************************
Name: GainAdjGetEUSfPow          
Description: 读取EU功率
Input: void
Return: void
**************************************************************/
void GainAdjGetEUPow(UCHAR8 ab_flag, UCHAR8 ud_flag)
{

	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;
	UINT32 i;
		
	p_msg[MSG_DES_FP] = 1;//第一个光口下的EU
	p_msg[MSG_DES_RE] = 1;
	p_msg[MSG_DES_REE] = 0;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] = LOCAL_ADD_REE;	
	p_msg[MSG_CMD_ID] = MSG_CMD_GAIN_ADJ;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

	p_msg[tx_len++] = GAIN_ADJ_ST_GET_EU_SF_POW;
	p_msg[tx_len++] = ab_flag;
	p_msg[tx_len++] = ud_flag;

	SendMsgPkt(tx_len, p_msg);

}

/*************************************************************
Name: ReeBordcastToSetRe          
Description:扩展单元广播设置射频参数
Input:base_flag:
Output:void         
Return:void
**************************************************************/
//void ReeBroadcastToSetRe(UCHAR8 485_usb_flag, UCHAR8 rf,UCHAR8 *P_tx_buff )
void MAUBroadcastToMEU(UCHAR8 uart_usb_flag,UCHAR8 des_eu,UCHAR8 *p_tx_buff ,UINT msg_tx_length,UCHAR8 msg_cmd_id)
{
	//目的地址
	p_tx_buff[MSG_DES_FP] = des_eu;  
	p_tx_buff[MSG_DES_RE] = BROADCAST_ADD_RE;   
	p_tx_buff[MSG_DES_REE] = 0; 
	
	// 源地址  
	p_tx_buff[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_tx_buff[MSG_SRC_RE] = LOCAL_ADD_RE; 
	p_tx_buff[MSG_SRC_REE] = LOCAL_ADD_REE;

	// 应答包的保留字段
	p_tx_buff[MSG_RESERVE1] = 0;
	p_tx_buff[MSG_RESERVE2] = uart_usb_flag;
	// 应答包的命令字
	p_tx_buff[MSG_CMD_ID] = msg_cmd_id ;
	p_tx_buff[MSG_ACK_FLAG]=MSG_ACK_MASTER_SEND;

	SendMsgPkt( msg_tx_length, p_tx_buff );
	
}


/*************************************************************
Name: MAUSetParamToMEU          
Description: 下发参数到拓展板
Input: void
Return: void
**************************************************************/
void MAUGetParamFromMEU(void)
{
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

	if (   (sys_work_info&SYSTEM_FLAG_MCU_UPDATE) || (sys_work_info &SYSTEM_FLAG_FPGA_UPDATE) 
	    || (sys_work_info &SYSTEM_FLAG_REMOTE_UPDATE))
	{
		 return;
	}

	if ( 0 !=	(sys_work_info & SYSTEM_FLAG_SET_RE_SYS_CFG) )
	{
		WTD_CLR; 
		// 需要刷新RE的延时模式
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_SYS_CFG);
		//SetReSysConfig();
		//SetReBwConfig();

	}

	
	
	au_send_msg |= AU_MSG_FLAG_GET_EU_PARA;

	if ( 0 !=	(au_send_msg & AU_MSG_FLAG_GET_EU_PARA) )
	{
		au_send_msg &= (~AU_MSG_FLAG_GET_EU_PARA);
		//printf("au_send_msg TO EU:%x\r\n",au_send_msg);
		MauGetMeuAlarm();
	}

}


/*************************************************************
Name:ReeDetectReST          
Description: ree获取re状态
Input:

Return: void
**************************************************************/
void MauGetMeuAlarm()
{


	UINT msg_tx_len,i=0;
	static UCHAR8 eu_port = 1;
	
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}

	if (   (sys_work_info&SYSTEM_FLAG_MCU_UPDATE) || (sys_work_info &SYSTEM_FLAG_FPGA_UPDATE) 
	    || (sys_work_info &SYSTEM_FLAG_REMOTE_UPDATE))
	{
		 return;
	}

		msg_tx_len = MSG_CMD_BODY;

		sys_temp_buff[msg_tx_len++]= (UCHAR8)MADD_WORK_ERROR;
		sys_temp_buff[msg_tx_len++]= (UCHAR8) (MADD_WORK_ERROR>>8);
		sys_temp_buff[msg_tx_len++]= 1;			
		msg_tx_len+=1;
		
		sys_temp_buff[msg_tx_len++]= (UCHAR8)MADD_A_RE_LOCAL_ST_ALARM;
		sys_temp_buff[msg_tx_len++]= (UCHAR8) (MADD_A_RE_LOCAL_ST_ALARM>>8);
		sys_temp_buff[msg_tx_len++]= 2;			
		msg_tx_len+=2;



	//TRACE_INFO("DETECT -------------------\r\n");
	//printf("发送");
//	TRACE_INFO(" ReeBroadcastToSetRe---2 \r\n"); 		
	//for(i=0;i<msg_tx_len;i++)
	//{

	//	TRACE_INFO_WP("%x ",sys_temp_buff[i]); 	
	//printf("%x ",sys_temp_buff[i]); 
	//}
	//TRACE_INFO(" \r\n"); 		

		if(eu_port>FP_MAX)
			eu_port = 1;

		//printf("eu_port:%d\r\n",eu_port);
		MAUBroadcastToMEU( 0,eu_port++,sys_temp_buff ,msg_tx_len,MSG_CMD_GET_PARAM);	

		
		
}


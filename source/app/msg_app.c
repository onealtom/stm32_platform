/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :sys_param.c
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
extern _T_PARAM_ASC sys_param_asc[];
extern _T_VALID_FP_TOPO valid_fp_topo[FP_MAX];
extern _T_FP_INFO fp_inf[FP_MAX];
extern _T_RE_INFO tmp_re_inf[FP_MAX][RE_MAX];		// RE信息的临时缓存
//extern UINT32 sys_work_info;
extern unsigned int traceLevel;
extern _T_ATT_ADJ_ST fpga_att_adj_st;
extern _T_ATT_ADJ_ST gain_adj_st;
extern UCHAR8 para_bak[];
extern UCHAR8 re_trans_fp;
extern UCHAR8 re_trans_node;
extern UCHAR8  re_trans_rf ;
extern UCHAR8 att_adj_buff[];


//UCHAR8 msg_big_buff[FP_MAX][MSG_BIG_PKT_SIZE];		// 大消息包缓冲
_T_BIG_PKT_BUFF msg_big_buff[MSG_BIG_PKT_COUNT];
UCHAR8 msg_buff[FP_MAX][FPGA_MSG_BUFF_SIZE];		// 小消息包缓冲
UINT32 re_msg_buff_st[FP_MAX];

UCHAR8 msg_tx_buff[MSG_BIG_PKT_SIZE];		// 发送缓冲
extern _T_NOISE_TEST_STATUS noise_test_st ;
/*************************************************************
Name:CheckMsgAddr          
Description: 检查地址是否合法
Input:
	des_fp: 目标光口(0-REC, 1~n-某光口, BROADCAST_ADD_FP-全光口广播)
	des_re: 目标RE (0-REC, 1~RE_MAX-某RE, BROADCAST_ADD_RE-光口全RE广播 )
Return: 
	0-非法地址
	1-主控地址
	2-光口广播
	3-针对RE发送
**************************************************************/
UINT32 CheckMsgAddr( UCHAR8 des_fp, UCHAR8 des_re ,UCHAR8 des_ree)
{
	if ((( PC_ADD_FP==des_fp )&&( PC_ADD_RE==des_re )&&( PC_ADD_REE==des_ree ))||(  PC_ABS_FP==des_fp )&&( PC_ABS_RE==des_re )&&( PC_ABS_REE==des_ree ))

	{
		// 本地主控地址
		return MSG_TO_PC;
	}
	else
	{

		if ( ADDR_PC_MASK!=(des_fp&ADDR_PC_MASK) )		// PC拓扑地址和相对地址标志不能同时有效
		{
			des_fp &= ADDR_FP_MASK; 
            //RE为广播地址 并且 光口地址存在
			if (( BROADCAST_ADD_RE==des_re )&&( LOCAL_ADD_FP!=des_fp))
			{
				//RF为广播地址 或则 光口为 1到8中的一个
				if (( BROADCAST_ADD_FP==des_fp )||( des_fp<=FP_MAX ))
				{
					return MSG_TO_ALL;
				}
			}

           		 //光口 为广播地址 并且 RE地址存在
			if (( BROADCAST_ADD_FP==des_fp )&&( LOCAL_ADD_RE!=des_re ))
			{
			    //RE为广播地址 或则 为1~32中的一个
				if (( BROADCAST_ADD_RE==des_re )||( des_re<=RE_MAX ))
				{
					return MSG_TO_ALL;
				} 
			}  
				
			if (( des_re<=RE_MAX )&&( des_fp<=FP_MAX )&&( des_ree<=REE_MAX ))	// 针对某光口的某个RE
			{
				if (( LOCAL_ADD_RE!=des_re ))
				{
					des_fp -= 1;
					des_re -= 1;
					if(0!=des_ree )
						des_ree -= 1;
					return MSG_TO_RE; 
					
					// 查看此位置是否有RE
					if (   (des_re<fp_inf[des_fp].re_cnt )&&(des_ree<REE_MAX  ))
					{
						return MSG_TO_RE; 
					}
				}
				else
				if( (0 != des_re)&&( 0!=des_fp ) ) 
				{
                   			return MSG_TO_RE; 
				}
			}
			
		}
		
	}
	// 错误地址
	return MSG_TO_NONE;
}
#if 0
//UINT32 CheckMsgAddr( UCHAR8 des_fp, UCHAR8 des_re)
{
//	if ((( PC_ADD_FP==des_fp )&&( PC_ADD_RE==des_re )&&( PC_ADD_REE==des_ree )))
	if ((( PC_ADD_FP==des_fp )&&( PC_ADD_RE==des_re )))
	{
		// 本地主控地址
		return MSG_TO_PC;
	}
	else
	{
		if ( ADDR_PC_MASK!=(des_fp&ADDR_PC_MASK) )		// PC拓扑地址和相对地址标志不能同时有效
		{
			des_fp &= ADDR_FP_MASK;

			if (( BROADCAST_ADD_RE==des_re )&&( LOCAL_ADD_FP!=des_fp))
			{
				// 广播
				if (( BROADCAST_ADD_FP==des_fp )||( des_fp<=FP_MAX ))
				{
					return MSG_TO_ALL;
				}
			}

			if (( BROADCAST_ADD_FP==des_fp )&&( LOCAL_ADD_RE!=des_re ))
			{
				// 广播
				if (( BROADCAST_ADD_RE==des_re )||( des_re<=RE_MAX ))
				{
					return MSG_TO_ALL;
				}
			}
			
			if (( des_re<=RE_MAX )&&( des_fp<=FP_MAX ))	// 针对某光口的某个RE
			{
				if (( LOCAL_ADD_FP!=des_fp )&&( LOCAL_ADD_RE!=des_re ))
				{
					return MSG_TO_RE;
					#if 0
					des_fp -= 1;
					des_re -= 1;
					// 查看此位置是否有RE
					#ifdef CLIENT_XINMIN
						if ( des_re<fp_inf[7-des_fp].re_cnt )
						{
							return MSG_TO_RE;
						}
					#else
						if ( des_re<fp_inf[des_fp].re_cnt )
						{
							return MSG_TO_RE;
						}
					#endif
					#endif
				}
			}
		}
	}
	// 错误地址
	return MSG_TO_NONE;
}

/*************************************************************
Name:GetReBigMsgBuffIndex          
Description: 查找指定RE的消息保存的大缓冲地址
Input:
	fp: 光口号
	re: re序号
Return: 
	0-没找到
	1~MSG_BIG_PKT_COUNT: 大缓冲区
**************************************************************/
UINT32 GetReBigMsgBuffIndex( UCHAR8 fp, UCHAR8 re )
{
	UINT32 i;
	UINT16 tmp;

	if ((fp>FP_MAX)||(re>RE_MAX))
	{
		return 0;
	}

	tmp = (fp<<8)|re;
	for (i=0; i<MSG_BIG_PKT_COUNT; i++)
	{
		if ( msg_big_buff[i].owner == tmp )
		{
			return (i+1);
		}
	}
	return 0;
}
#endif
/*************************************************************
Name:GetReBigMsgBuffIndex          
Description: 查找指定RE的消息保存的大缓冲地址
Input:
	fp: 光口号
	re: re序号
Return: 
	0-没找到
	1~MSG_BIG_PKT_COUNT: 大缓冲区
**************************************************************/
UINT32 GetReBigMsgBuffIndex( UCHAR8 fp, UCHAR8 re,UCHAR8 rf )
{
	UINT32 i;
	UINT32 tmp;

	if (((fp&0x1f)>FP_MAX)||(re>RE_MAX)||(rf>REE_MAX))
	{
		return 0;
	}

	tmp = (fp<<16)|(re<<8)|rf; 
	
	for (i=0; i<MSG_BIG_PKT_COUNT; i++)
	{
		if ( msg_big_buff[i].owner == tmp )
		{
			return (i+1); 
		}
	}
	return 0;
}
/*************************************************************
Name:GetFreeBigBuffIndex          
Description: 查找空闲的大数据缓冲区
Input: void
Return: 
	0-没找到
	1~MSG_BIG_PKT_COUNT: 大缓冲区
**************************************************************/
UINT32 GetFreeBigBuffIndex( void )
{
	UINT32 i;
	for (i=0; i<MSG_BIG_PKT_COUNT; i++)
	{
		if ( 0 == msg_big_buff[i].owner )
		{
			return (i+1);
		}
	}
	return 0;
}

/*************************************************************
Name:GetReBigMsgBuffIndex          
Description: 查找指定RE的消息保存的大缓冲地址
Input:
	fp: 光口号
	re: re序号
Return: 
	0-没找到
	1~MSG_BIG_PKT_COUNT: 大缓冲区
**************************************************************/
BOOL SetReBigMsgBuff( UCHAR8 index,  UCHAR8 fp, UCHAR8 re )
{
	UINT16 tmp;

	if ((fp>FP_MAX)||(re>RE_MAX))
	{
		return b_FALSE;
	}

	if ( msg_big_buff[index].owner != 0 )
	{
		return b_FALSE;
	}
	
	tmp = (fp<<8)|re;
	msg_big_buff[index].owner = tmp; 

	return b_TRUE;
}

/*************************************************************
Name:CheckBigBuffTimeOut          
Description: 检查是否有RE长时间占用大缓冲区
Input: void
Return: void
**************************************************************/
void CheckBigBuffTimeOut( void )
{
	UINT32 i;

	for (i=0; i<MSG_BIG_PKT_COUNT; i++)
	{
		if ( msg_big_buff[i].time_out>0 )
		{
			msg_big_buff[i].time_out--;
		}
		else
		{
			msg_big_buff[i].owner = 0;
		}
	}
}

/*************************************************************
Name:SendMsgPkt          
Description: 发送消息包给RE或主控
Input:
	msg_len: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
Return: void
**************************************************************/
void SendMsgPkt( UINT32 tx_len, UCHAR8 * p_msg_dat )
{
	UINT16 i;
	UCHAR8 des_fp, des_re,des_ree;
//	UCHAR8 src_fp, src_re;
	UINT32 des_add, src_add;
	UINT16 crc_val;
	UINT32 tmp;

	WTD_CLR;
	//TRACE_INFO("Send MsgPkt(%d).", tx_len);

	if ( tx_len >= MSG_BIG_PKT_SIZE )
	{
		// 长度溢出
		TRACE_INFO_WP("over flow\r\n");
		return;
	}
//	if(p_msg_dat[MSG_CMD_ID] == MSG_CMD_GET_REE_INFO)
//	{
//		TRACE_INFO("0SendMsgPkt id =DB,201310090921##############################################\r\n");
//	}
	des_fp = p_msg_dat[MSG_DES_FP];
	des_re = p_msg_dat[MSG_DES_RE];
	des_ree = p_msg_dat[MSG_DES_REE];
	//TRACE_INFO("SendMsgPkt to [%02X:%02X:%02X],cmd=%02X\r\n",des_fp,des_re,des_ree,p_msg_dat[MSG_CMD_ID] );
	tmp = CheckMsgAddr( des_fp, des_re,des_ree );
	TRACE_INFO("tmp(%d).\r\n",tmp);
	if ( MSG_TO_NONE == tmp )
	{
		// 无效地址
		TRACE_INFO_WP("Unknow Addr[%02X:%02X]\r\n", des_fp, des_re );
		return;
	}
	
	des_fp &= ADDR_FP_MASK;		// 取得光口号

	// 计算CRC值
	crc_val = CalCrc16(p_msg_dat, tx_len, POLYNOMIAL );
	p_msg_dat[tx_len++] = (UCHAR8)(crc_val&0x00ff);
	p_msg_dat[tx_len++] = (UCHAR8)((crc_val>>8)&0x00ff);

	switch( tmp )
	{
	case MSG_TO_PC:		// 发送给本地主控
		TRACE_INFO_WP("To PC\r\n");
		UsbSendMsgPkt( tx_len, p_msg_dat );
		break;

	case MSG_TO_ALL:	// 广播
		TRACE_INFO_WP("MSG_TO_ALL\r\n");
		if ( BROADCAST_ADD_FP==des_fp )
		{
			//TRACE_INFO_WP("Broadcast1\r\n");
			// 全光口广播
			for (i=0;i<FP_MAX;i++)
			{
				//TRACE_INFO_WP("Broadcast2\r\n");
				des_add = (i<<8);
				if ( BROADCAST_ADD_RE == des_re )
				{
					des_add |= 0xFF;
				}
				else
				{
					des_add |= des_re;
				}
				des_add = (des_add<<8)|des_ree;
				FpgaSendMsgPkt( des_add, 0, tx_len, p_msg_dat);
			}
		}
		else if ( BROADCAST_ADD_RE==des_re )
		{
			// 单光口所有RE广播
			TRACE_INFO_WP("Broadcast\r\n");
			if ( des_fp > 0 )
			{
				des_fp--;
				des_add = (des_fp<<8)|0xFF;
				des_add = (des_add<<8)|des_ree;
				FpgaSendMsgPkt( des_add, 0, tx_len, p_msg_dat);
			}
		}
		break;

	case MSG_TO_RE:		// 针对某个RE
		TRACE_INFO_WP("MSG_TO_EU\r\n");
		//if (des_fp==0)
		//{
			des_fp--;
			TRACE_INFO_WP("To RE\r\n");
			des_add = (des_fp<<16)|(des_re<<8)|(des_ree);
			TRACE_INFO("des_add(%02x).\r\n",des_add);
			FpgaSendMsgPkt( des_add, 0, tx_len, p_msg_dat);
		//}
		break;
	case MSG_TO_REE:
		TRACE_INFO_WP("MSG_TO_RU\r\n");
		if (des_fp>0)
		{
			des_fp --;
			des_add = (des_fp<<16)|(des_re<<8)|(des_ree);
			TRACE_INFO("des_add(%02x).\r\n",des_add);
			FpgaSendMsgPkt( des_add, 0, tx_len, p_msg_dat);
		}
		break;
	}

}

/*************************************************************
Name:MsgPktTransmit          
Description: 转发消息包给RE或主控
Input:
	tx_len: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
Return: void
**************************************************************/
void MsgPktTransmit( UINT32 tx_len, UCHAR8 * p_msg_dat )
{
	UINT16 i;
	UCHAR8 des_fp, des_re,des_ree;
	UCHAR8 src_fp, src_re,src_ree;
	UINT32 des_add, src_add;
	UINT32 tmp;
	UCHAR8 * p_args;
	WTD_CLR;
	
	TRACE_INFO("Transmit MsgPkt.\r\n"); 

	if ( tx_len >= MSG_BIG_PKT_SIZE )
	{
		// 长度溢出
		//TRACE_INFO_WP("over flow\r\n");
		return;
	}

    if (   MSG_CMD_UPDATE_MCU  == p_msg_dat[MSG_CMD_ID]
		 ||MSG_CMD_UPDATE_FPGA == p_msg_dat[MSG_CMD_ID])
    {

		p_args = p_msg_dat+MSG_PKT_HEAD_SIZE; 
       
	    if (( 0xFA == p_args[0] )&&( 0x5A == p_args[1] ))
	    {
           sys_work_info |= SYSTEM_FLAG_REMOTE_UPDATE;	//设置FPGA正在升级标志
 
		}
		else
		if (( 0xA5 == p_args[0] )&&( 0xAF == p_args[1] ))
		{

            sys_work_info &= ~SYSTEM_FLAG_REMOTE_UPDATE;
		}

	}

	des_fp = p_msg_dat[MSG_DES_FP];
	des_re = p_msg_dat[MSG_DES_RE];
	des_ree = p_msg_dat[MSG_DES_REE];
	
	TRACE_INFO_WP("des to Addr[%02X:%02X:%02X]\r\n", des_fp, des_re,des_ree );  
	
	src_fp = p_msg_dat[MSG_SRC_FP]&0x3F;
	src_re = p_msg_dat[MSG_SRC_RE];
	src_ree = p_msg_dat[MSG_SRC_REE];

	TRACE_INFO_WP("src to Addr[%02X:%02X:%02X]\r\n", src_fp, src_re,src_ree );
	if (( (src_fp&0x1f)>FP_MAX )||( src_re>RE_MAX )||( src_ree>REE_MAX ))
	{
		//TRACE_ERROR("Err SrcAdd\r\n");
		return;
	}

	if (( (src_fp&0x1f)>0 ))
	{
		src_fp--;  //变为逻辑光口地址
	} 
	
	src_add = (src_fp<<16)|(src_re<<8)|src_ree;

	tmp = CheckMsgAddr( des_fp, des_re, des_ree);
	TRACE_INFO_WP("CheckMsgAddr(%d)\r\n",tmp);	
	if ( MSG_TO_NONE == tmp )
	{
		// 无效地址
		TRACE_INFO_WP("Unknow Addr[%02X:%02X]\r\n", des_fp, des_re );
		return; 
	}

	des_fp &= ADDR_FP_MASK;		// 取得光口号

	switch( tmp )    
	{
	case MSG_TO_PC:		// 发送给本地主控
		TRACE_INFO_WP("To PC\r\n");
		UsbSendMsgPkt( tx_len, p_msg_dat );
		break;

	case MSG_TO_ALL:	// 广播
		TRACE_INFO_WP("To Broadcast\r\n");
		if ( BROADCAST_ADD_FP==des_fp )
		{
				// 全光口广播
				for (i=0;i<8;i++)
				{
					des_add = i<<16;
					
					if ( BROADCAST_ADD_RE == des_re )
					{
						des_add =des_add | 0xFF00|des_ree;
					}
					else
					{
						des_add=des_add|des_re|des_ree;
					}
					FpgaSendMsgPkt( des_add, src_add, tx_len, p_msg_dat);
				}
			}
			else if ( BROADCAST_ADD_RE==des_re )
			{
				// 单光口所有RE广播
				if ( des_fp > 0 )
				{
					des_fp--;
					des_add = (des_fp<<16)|0xFF00|des_ree;     
					FpgaSendMsgPkt( des_add, src_add, tx_len, p_msg_dat);
				}
			}
		
		break;

		case MSG_TO_RE:		// 针对某个RE
			if (des_fp>0) 
			{
				TRACE_INFO_WP("To RE\r\n");  
				des_fp--;    
				des_add = (des_fp<<16)|(des_re<<8)|des_ree ;
				FpgaSendMsgPkt( des_add, src_add, tx_len, p_msg_dat);
			}
		break;
		
	}
	
}


#if 0
/*************************************************************
Name:MsgHandle          
Description: 处理收到的消息包
Input:
	msg_len: 消息包的长度，包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
Return: void
**************************************************************/
void MsgHandle( UINT32 msg_len, UCHAR8* p_msg_dat )
{

	UINT16 tmp,i;
	UINT16 crc_val;
	UCHAR8 des_fp, des_re;
    UCHAR8 src_fp, src_re;

	WTD_CLR;
	
	// 判断是否是有效数据包 
	des_fp = p_msg_dat[MSG_DES_FP]; 
	des_re = p_msg_dat[MSG_DES_RE];
	src_fp = p_msg_dat[MSG_SRC_FP];
	src_re = p_msg_dat[MSG_SRC_RE];	
 
	if (( msg_len<MSG_PKT_SIZE_MIN )||( msg_len>MSG_BIG_PKT_SIZE )||( NULL == p_msg_dat ))
	{
		TRACE_DEBUG("This Is Not a MsgPkt!\r\n");
		return;
	}
	
	crc_val = CalCrc16( p_msg_dat, msg_len-2, POLYNOMIAL );
	tmp = (UINT16)((p_msg_dat[msg_len-1]<<8)|(p_msg_dat[msg_len-2]));
	
	if ( crc_val != tmp )  
	{
		TRACE_INFO("CRC Error!Calc CRC=%08X, Receive CRC=%08X\r\n", crc_val, tmp);
		MsgCrcError( des_fp, des_re, p_msg_dat[MSG_CMD_ID], crc_val );
		return; 
	} 

	#ifdef CLIENT_XINMIN   
     if ( des_fp >0 && des_fp < 9 ) 
     {
       p_msg_dat[MSG_DES_FP] = 9 - p_msg_dat[MSG_DES_FP];
       crc_val = CalCrc16( p_msg_dat, msg_len-2, POLYNOMIAL );
       p_msg_dat[msg_len-1] = (UCHAR8)(crc_val>>8);
	   p_msg_dat[msg_len-2] = (UCHAR8)(crc_val);
	   
     }   
	#endif   
    //TRACE_INFO("src fp =%d,src re =%d\r\n",p_msg_dat[2],p_msg_dat[3]); 
    TRACE_INFO("Got Msg[%02X:%02X]->[%02X:%02X],cmd=%02X.\r\n", 
	p_msg_dat[MSG_SRC_FP], p_msg_dat[MSG_SRC_RE], p_msg_dat[MSG_DES_FP], p_msg_dat[MSG_DES_RE], p_msg_dat[MSG_CMD_ID]);
    WTD_CLR;
	 
	// 根据目的地址处理  绝对地址或者拓扑地址                                           
	if  ( ((LOCAL_ADD_FP==des_fp)&&(LOCAL_ADD_RE==des_re))||(0x80==des_fp) ) 
	{
		// 发给REC的，或是主控给本地模块的

		// 计算实际数据长度，不包括CRC
		msg_len-=2;
		
		if ( MSG_ACK_MASTER_SEND == p_msg_dat[MSG_ACK_FLAG] )
		{
			// 确定应答包的目的地址

			// 数据包应答给发送方
			msg_tx_buff[MSG_DES_FP] = p_msg_dat[MSG_SRC_FP];
			msg_tx_buff[MSG_DES_RE] = p_msg_dat[MSG_SRC_RE];
			
			if ((PC_ABS_FP==msg_tx_buff[MSG_DES_FP])&&(PC_ABS_NODE==msg_tx_buff[MSG_DES_RE]))
			{
				// 若应答地址为主控的相对地址，则改为主控的拓扑地址
				msg_tx_buff[MSG_DES_FP] = PC_ADD_FP;
				msg_tx_buff[MSG_DES_RE] = PC_ADD_RE;
			}
			// 源地址REC [0x00,0x00]
			msg_tx_buff[MSG_SRC_FP] = LOCAL_ADD_FP;
			msg_tx_buff[MSG_SRC_RE] = LOCAL_ADD_RE;

			// 应答包的保留字段
			msg_tx_buff[MSG_RESERVE1] = p_msg_dat[MSG_RESERVE1];
			msg_tx_buff[MSG_RESERVE2] = p_msg_dat[MSG_RESERVE2];

			// 应答包的命令字
			msg_tx_buff[MSG_CMD_ID] = p_msg_dat[MSG_CMD_ID];

			// 处理应答包命令
			switch ( p_msg_dat[MSG_CMD_ID] )
			{
				case MSG_CMD_SET_PARAM:		// 设置参数
					MsgHandleSetParam( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_GET_PARAM:		// 查询参数
					MsgHandleGetParam( msg_len, p_msg_dat, msg_tx_buff );
				break;
					
				case MSG_CMD_SET_DEV_REG:		// 设置器件寄存器
					MsgHandleSetDevReg( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_GET_DEV_REG:		// 查询器件寄存器
					MsgHandleGetDevReg( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_RESET_DEV:		// 重新初始化器件
					MsgHandleResetDev( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_GET_FPGA_REG:
					MsgHandleGetFpgaReg( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_GET_TABLE:		// 查询表格
					MsgHandleGetTable( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_SET_TABLE:		// 设置表格
					MsgHandleSetTable( msg_len, p_msg_dat, msg_tx_buff );
				break;
					
				case MSG_CMD_GET_TOPO:		// 查询拓扑
					MsgHandleGetTopo( msg_len, p_msg_dat, msg_tx_buff );
				break;
					
				case MSG_CMD_SET_TOPO:			// 设置拓扑
					MsgHandleSetTopo( msg_len, p_msg_dat, msg_tx_buff );
				break;
					
				case MSG_CMD_UPDATE_MCU:		// 升级MCU
					MsgHandleUpdateMCU( msg_len, p_msg_dat, msg_tx_buff );
				break;
					
				case MSG_CMD_UPDATE_FPGA:		// 升级FPGA
					MsgHandleUpdateFPGA( msg_len, p_msg_dat, msg_tx_buff );
				break;
					
				case MSG_CMD_GET_FLASH_PAGE:	// 读取FLASH页内容
					MsgHandleGetFlashPage( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_START_ATT_ADJ:  //0XA0
					MsgHandleStartAttAdj( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_ATT_STEP_ADJ:
					MsgHandleAttStepAdj( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_END_ATT_ADJ:
					MsgHandleEndAttAdj( msg_len, p_msg_dat, msg_tx_buff );
				break;

				case MSG_CMD_FC_SCAN:
					MsgHandleFcScan( msg_len, p_msg_dat, msg_tx_buff );
				break;
					
				case MSG_CMD_ERR_ALARM:		// 错误报警
					//MsgHandleDlGainStepAdjust( msg_length, p_msg_dat );
				break;

				case MSG_CMD_BLANK:
					MsgHandleBlankCmd( msg_len, p_msg_dat, msg_tx_buff );
				break;

				default:		// 未知命令
					MsgHandleUnknowCmd( msg_len, p_msg_dat, msg_tx_buff );

			}
		}
		else
		{
			// 应答包
			MsgHandleAck( msg_len, p_msg_dat );
		}
	}
	else
	{
		// 需要转发的
		MsgPktTransmit( msg_len, p_msg_dat );
	}
	
	WTD_CLR;

		
}
#endif
/*************************************************************
Name:MsgHandle          
Description: 处理收到的消息包
Input:
	msg_len: 消息包的长度，包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
Return: void
**************************************************************/
//void MsgHandle( UCHAR8 fp, UCHAR8 re,UINT32 msg_len, UCHAR8* p_msg_dat )//20121130
void MsgHandle( UCHAR8 fp, UCHAR8 re, UCHAR8 ree,UINT32 msg_len, UCHAR8* p_msg_dat )
{
	UINT16 tmp;
	UINT16 crc_val;
	UCHAR8 des_fp, des_re,des_ree;
	//UCHAR8 src_fp, src_re;
	
	WTD_CLR;
	// 判断是否是有效数据包
	if (( msg_len<MSG_PKT_SIZE_MIN )||( msg_len>MSG_BIG_PKT_SIZE )||( NULL == p_msg_dat ))
	{
		TRACE_DEBUG("This Is Not a MsgPkt!\r\n");
		return;
	}

#if 0
	// CRC校验
	crc_val = CalCrc16( p_msg_dat, msg_len-2, POLYNOMIAL );
	tmp = (UINT16)((p_msg_dat[msg_len-1]<<8)|(p_msg_dat[msg_len-2]));
	if ( crc_val != tmp )
	{
		TRACE_INFO("CRC Error!Calc CRC=%08X, Receive CRC=%08X\r\n", crc_val, tmp);
//		MsgCrcError( fp, re, p_msg_dat[MSG_CMD_ID], crc_val );//20121130
	 	MsgCrcError( fp,  re,  ree, p_msg_dat[MSG_CMD_ID],  crc_val );

		return;
	}


	if ( MSG_CMD_UPDATE_FPGA == p_msg_dat[MSG_CMD_ID] )
	{
//		printf("Ack:%02X, pkt:%02X, %02X\r\n", p_msg_dat[MSG_ACK_FLAG], p_msg_dat[MSG_CMD_BODY], p_msg_dat[MSG_CMD_BODY+1]);
	}
#endif

//	TRACE_INFO("Rcv MsgPkt(%d).\r\n", msg_len);
#if 0
{
	UINT32 i;
	for ( i=0; i<msg_len; i++ )
	{
		TRACE_INFO_WP("%02X ", p_msg_dat[i]);
	}
	TRACE_INFO_WP("\r\n");
}
#endif

	des_fp = p_msg_dat[MSG_DES_FP];
	des_re = p_msg_dat[MSG_DES_RE];
	des_ree = p_msg_dat[MSG_DES_REE];
	TRACE_INFO("des_fp(%02x).\r\n", des_fp);
	TRACE_INFO("des_re (%02x).\r\n", des_re );
	TRACE_INFO("des_ree(%02x).\r\n", des_ree);
	TRACE_INFO("src_fp(%02x).\r\n", p_msg_dat[MSG_SRC_FP]);
	TRACE_INFO("src_re (%02x).\r\n", p_msg_dat[MSG_SRC_RE] );
	TRACE_INFO("src_ree(%02x).\r\n", p_msg_dat[MSG_SRC_REE]);
	// 根据目的地址处理
	if  ( ((LOCAL_ADD_FP==(des_fp))&&(LOCAL_ADD_RE==des_re)&&(LOCAL_ADD_REE==des_ree))||(0x80==des_fp) ) 
//	if  ( (((des_fp<=FP_MAX)||(LOCAL_ADD_FP==(des_fp))&&(LOCAL_ADD_RE==des_re))||(0x80==des_fp) ) 
	{
		// 发给REC的，或是主控给本地模块的

		// 计算实际数据长度，不包括CRC
		msg_len-=2;

		TRACE_INFO("p_msg_dat[MSG_ACK_FLAG](%d).\r\n", p_msg_dat[MSG_ACK_FLAG] );
		if ( MSG_ACK_MASTER_SEND == p_msg_dat[MSG_ACK_FLAG] )
		{
			// 确定应答包的目的地址

			// 数据包应答给发送方
			msg_tx_buff[MSG_DES_FP] = p_msg_dat[MSG_SRC_FP];
			msg_tx_buff[MSG_DES_RE] = p_msg_dat[MSG_SRC_RE];
			msg_tx_buff[MSG_DES_REE] = p_msg_dat[MSG_SRC_REE];
			
			if ((PC_ABS_FP==msg_tx_buff[MSG_DES_FP])&&(PC_ABS_RE==msg_tx_buff[MSG_DES_RE])&&(PC_ABS_REE==msg_tx_buff[MSG_DES_REE]))
			{
				// 若应答地址为主控的相对地址，则改为主控的拓扑地址
				msg_tx_buff[MSG_DES_FP] = PC_ADD_FP;
				msg_tx_buff[MSG_DES_RE] = PC_ADD_RE;
				msg_tx_buff[MSG_DES_REE] = PC_ADD_REE;
			}
#if 0
			if ((MODULE_ABS_FP==des_fp )&&(MODULE_ABS_RE==des_re))
			{
				// 主控的相对地址访问，返回地址要用主控的绝对地址
				msg_tx_buff[MSG_DES_FP] = PC_ADD_FP;
				msg_tx_buff[MSG_DES_RE] = PC_ADD_RE;
			}
			else if ((PC_ABS_FP==p_msg_dat[MSG_SRC_FP])&&(PC_ABS_NODE==p_msg_dat[MSG_SRC_RE]))
			{
				// 源地址为主控的地址，返回地址要用主控的拓扑地址
				msg_tx_buff[MSG_DES_FP] = PC_ADD_FP;
				msg_tx_buff[MSG_DES_RE] = PC_ADD_RE;
			}
			else
			{
				// 数据包应答给发送方
				msg_tx_buff[MSG_DES_FP] = p_msg_dat[MSG_SRC_FP];
				msg_tx_buff[MSG_DES_RE] = p_msg_dat[MSG_SRC_RE];
			}
#endif 			
			// 源地址REC [0x00,0x00]
			msg_tx_buff[MSG_SRC_FP] = LOCAL_ADD_FP;
			msg_tx_buff[MSG_SRC_RE] = LOCAL_ADD_RE;
			msg_tx_buff[MSG_SRC_REE] = LOCAL_ADD_REE;

			// 应答包的保留字段
			msg_tx_buff[MSG_RESERVE1] = p_msg_dat[MSG_RESERVE1];
			msg_tx_buff[MSG_RESERVE2] = p_msg_dat[MSG_RESERVE2];

			// 应答包的命令字
			msg_tx_buff[MSG_CMD_ID] = p_msg_dat[MSG_CMD_ID];

			TRACE_INFO(" MSG_CMD_ID =%d\r\n", p_msg_dat[MSG_CMD_ID]); 

			// 处理应答包命令
			switch ( p_msg_dat[MSG_CMD_ID] )
			{
			case MSG_CMD_SET_PARAM:		// 设置参数
				MsgHandleSetParam( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_GET_PARAM:		// 查询参数
				MsgHandleGetParam( msg_len, p_msg_dat, msg_tx_buff );
				break;
				
			case MSG_CMD_SET_DEV_REG:		// 设置器件寄存器
				MsgHandleSetDevReg( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_GET_DEV_REG:		// 查询器件寄存器
				MsgHandleGetDevReg( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_RESET_DEV:		// 重新初始化器件
				MsgHandleResetDev( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_GET_FPGA_REG:
				MsgHandleGetFpgaReg( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_GET_TABLE:		// 查询表格
				MsgHandleGetTable( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_SET_TABLE:		// 设置表格
				MsgHandleSetTable( msg_len, p_msg_dat, msg_tx_buff );
				break;
				
			case MSG_CMD_GET_TOPO:		// 查询拓扑
				MsgHandleGetTopo( msg_len, p_msg_dat, msg_tx_buff );
				break;
				
			case MSG_CMD_SET_TOPO:			// 设置拓扑
				MsgHandleSetTopo( msg_len, p_msg_dat, msg_tx_buff );
				break;
				
			case MSG_CMD_UPDATE_MCU:		// 升级MCU
				MsgHandleUpdateMCU( msg_len, p_msg_dat, msg_tx_buff );
				break;
				
			case MSG_CMD_UPDATE_FPGA:		// 升级FPGA
				MsgHandleUpdateFPGA( msg_len, p_msg_dat, msg_tx_buff );
				break;
				
			case MSG_CMD_GET_FLASH_PAGE:	// 读取FLASH页内容
				MsgHandleGetFlashPage( msg_len, p_msg_dat, msg_tx_buff );
				break;
			case MSG_CMD_FLASH_OPERATION: //Flash页操作
				MsgHandleFlashOperatePage( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_START_ATT_ADJ:
				MsgHandleStartAttAdj( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_ATT_STEP_ADJ:
				MsgHandleAttStepAdj( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_END_ATT_ADJ:
				MsgHandleEndAttAdj( msg_len, p_msg_dat, msg_tx_buff );
				break;

			case MSG_CMD_FC_SCAN:
				MsgHandleFcScan( msg_len, p_msg_dat, msg_tx_buff );
				break;
				
			case MSG_CMD_ERR_ALARM:		
				MsgHandleErrAlarm( msg_len, p_msg_dat, msg_tx_buff );
				break;
			case MSG_CMD_NOISE_TEST:
				MsgHandleNoiseTest( msg_len, p_msg_dat, msg_tx_buff );
				break;
			case MSG_CMD_GAIN_ADJ:
				MsgHandleGainAdj( msg_len, p_msg_dat, msg_tx_buff);
				break;
			case MSG_CMD_BLANK:
				MsgHandleBlankCmd( msg_len, p_msg_dat, msg_tx_buff );
				break;

			default:		// 未知命令
				MsgHandleUnknowCmd( msg_len, p_msg_dat, msg_tx_buff );

			}
		}
		else
		{
			TRACE_INFO(" MSG_CMD_ID =%d\r\n", p_msg_dat[MSG_CMD_ID]); 	
	//		TRACE_INFO("MsgHandleAck \r\n"); 		
			// 应答包
			MsgHandleAck( msg_len, p_msg_dat );
		}

		
	}
	else
	{

		TRACE_INFO("MsgPktTransmit \r\n"); 		
		// 需要转发的
		MsgPktTransmit( msg_len, p_msg_dat );
	}
	
	WTD_CLR;
		
}

/*************************************************************
Name:MsgCrcError          
Description: 消息包命令:未知命令
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
#if 0
void MsgCrcError( UCHAR8 fp, UCHAR8 re, UCHAR8 cmd, UINT16 crc )
{
	UINT32 msg_tx_len;
	// 目的地址
	msg_tx_buff[MSG_DES_FP] = fp;
	msg_tx_buff[MSG_DES_RE] = re;
	
	
	// 源地址REC [0x00,0x00]
	msg_tx_buff[MSG_SRC_FP] = 0;
	msg_tx_buff[MSG_SRC_RE] = 0;

	// 应答包的命令字
	msg_tx_buff[MSG_CMD_ID] = cmd;		// MSG_CMD_BLANK;

	// 应答信息
	msg_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_CRC;

	msg_tx_len = MSG_PKT_HEAD_SIZE;

	msg_tx_buff[msg_tx_len++] = (UCHAR8)(crc&0x00ff);
	msg_tx_buff[msg_tx_len++] = (UCHAR8)((crc>>8)&0x00ff);
	
	// 发送应答包
	SendMsgPkt( msg_tx_len, msg_tx_buff );
	
}
#endif

void MsgCrcError( UCHAR8 fp, UCHAR8 re, UCHAR8 ree,UCHAR8 cmd, UINT16 crc )
{
	UINT32 msg_tx_len;
	// 目的地址 
	msg_tx_buff[MSG_DES_FP] = fp;  
	msg_tx_buff[MSG_DES_RE] = re;  
	msg_tx_buff[MSG_DES_RE] = ree; 
	
	// 源地址REC [0x00,0x00] 
	msg_tx_buff[MSG_SRC_FP] = 0; 
	msg_tx_buff[MSG_SRC_RE] = 0;
	msg_tx_buff[MSG_SRC_REE] = 0;

	// 应答包的命令字
	msg_tx_buff[MSG_CMD_ID] = cmd;		// MSG_CMD_BLANK;

	// 应答信息
	msg_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_CRC;

	msg_tx_len = MSG_PKT_HEAD_SIZE;

	msg_tx_buff[msg_tx_len++] = (UCHAR8)(crc&0x00ff);
	msg_tx_buff[msg_tx_len++] = (UCHAR8)((crc>>8)&0x00ff);
	
	// 发送应答包
	SendMsgPkt( msg_tx_len, msg_tx_buff );
	
}



#if 0
/*************************************************************
Name:MsgHandleUnknowCmd
Description: 消息包命令:未知命令
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgReceiverBusy( UCHAR8 des_fp, UCHAR8 des_no )
{
	UINT32 msg_tx_len;

	// 目的地址
	msg_tx_buff[MSG_DES_FP] = des_fp;
	msg_tx_buff[MSG_DES_RE] = des_no;
	
	// 源地址REC [0x00,0x00]
	msg_tx_buff[MSG_SRC_FP] = 0;
	msg_tx_buff[MSG_SRC_RE] = 0;

	// 应答包的命令字
	msg_tx_buff[MSG_CMD_ID] = MSG_CMD_BLANK;

	// 应答信息
	msg_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_BUSY;

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	
	// 发送应答包
	SendMsgPkt( msg_tx_len, msg_tx_buff );
	
}
#endif
/*************************************************************
Name:MsgHandleUnknowCmd
Description: 消息包命令:未知命令
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgReceiverBusy( UCHAR8 des_fp, UCHAR8 des_re,UCHAR8 des_rf )
{
	UINT32 msg_tx_len;

	// 目的地址
	msg_tx_buff[MSG_DES_FP] = des_fp;
	msg_tx_buff[MSG_DES_RE] = des_re;
	msg_tx_buff[MSG_DES_REE] = des_rf;
	
	// 源地址REC [0x00,0x00]
	msg_tx_buff[MSG_SRC_FP] = 0;
	msg_tx_buff[MSG_SRC_RE] = 0;
	msg_tx_buff[MSG_SRC_REE] = 0;

	// 应答包的命令字
	msg_tx_buff[MSG_CMD_ID] = MSG_CMD_BLANK;

	// 应答信息
	msg_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_BUSY;

	msg_tx_len = MSG_PKT_HEAD_SIZE; 
	
	// 发送应答包
	SendMsgPkt( msg_tx_len, msg_tx_buff );
	
}
/*************************************************************
Name:MsgHandleUnknowCmd          
Description: 消息包命令:未知命令
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleUnknowCmd( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{


    //TRACE_INFO("MsgHandleUnknowCmd\r\n"); 
	
	UINT32 msg_tx_len;

	msg_tx_len = MSG_PKT_HEAD_SIZE;
		if ( MSG_CMD_BLANK==p_msg_dat[MSG_CMD_ID] )
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	}
	else
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_CMD;
	}

	//	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_CMD;
	

	// 发送应答包
	SendMsgPkt( msg_tx_len, p_tx_buff );
}

/*************************************************************
Name:MsgHandleBlankCmd          
Description: 消息包命令:空命令
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleBlankCmd( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
#if 1
	UINT16 tmp;
	UINT32 msg_tx_len;

	TRACE_INFO(" MsgHandleBlankCmd_hande\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;

	// A B C D段通道数
	tmp = FpgaReadRegister(FPGA_REG_CH_COUNT);

	#if defined CLIENT_JIZHUN
	p_tx_buff[msg_tx_len++] = tmp&0x1F>>0;
	p_tx_buff[msg_tx_len++] = 0;
	p_tx_buff[msg_tx_len++] = 0;
	p_tx_buff[msg_tx_len++] = 0;
	#else 
	p_tx_buff[msg_tx_len++] = tmp&BM_A_CH_COUNT>>0;
	p_tx_buff[msg_tx_len++] = (tmp&BM_B_CH_COUNT)>>8;
	p_tx_buff[msg_tx_len++] = (tmp&BM_C_CH_COUNT)>>4;
	p_tx_buff[msg_tx_len++] = (tmp&BM_D_CH_COUNT)>>12;
	#endif
	// A B C D段通信制式
	tmp = FpgaReadRegister(FPGA_REG_RF_INFO);
	p_tx_buff[msg_tx_len++] =(tmp>>8); //0x20|(tmp&0x0f);////20130318 test 
//	TRACE_INFO("[M]Msg Handle Blank A B C D段通信制式:[%04X]\r\n",(tmp&0XFF00)>>8);		
//	#if 0
	// 附加模块

	tmp = 0;

#ifdef USE_EXPA_MODULE
	tmp |= 0x01;
#endif

#ifdef EXPA_USE_I2C_PORT
	tmp |= 0x02;
#endif

	p_tx_buff[msg_tx_len++] = (UCHAR8)tmp&0xFF;
//#endif
	
	p_tx_buff[msg_tx_len++] = fpga_cfg.a_net_type;
	p_tx_buff[msg_tx_len++] = fpga_cfg.b_net_type;
	p_tx_buff[msg_tx_len++] = fpga_cfg.c_net_type;
	p_tx_buff[msg_tx_len++] = fpga_cfg.d_net_type;	
	p_tx_buff[msg_tx_len++] = MODULE_TYPE_REC;
	
	p_tx_buff[msg_tx_len++] = VERSION_FLAG; //2014.08.16
	p_tx_buff[msg_tx_len++] = version_number; //2014.08.16

	
	p_tx_buff[msg_tx_len++] = MCU_PARAM_FLAG; //2014.08.29
	p_tx_buff[msg_tx_len++] = MCU_PARAM_VER_5;  //2014.08.29

#ifdef FPGA_ACDU_16M_FLASH
	p_tx_buff[msg_tx_len++] = FLASH_FLAG; //2014.08.16
	p_tx_buff[msg_tx_len++] = (UCHAR8)flash_type;  //2014.08.29
#else
	p_tx_buff[msg_tx_len++] = 0; //2014.08.16
	p_tx_buff[msg_tx_len++] = (UCHAR8)0;  //2014.08.29
#endif

	//增加符
	p_tx_buff[msg_tx_len++] = '+';
	//版本名称			
	p_tx_buff[msg_tx_len++] = MAJOR_VERSION;
	//标称增益
	p_tx_buff[msg_tx_len++] = FPGA_REC_GFNOM;//AU 前端
	p_tx_buff[msg_tx_len++] = FPGA_REC_GDNOM;//AU 后端
	p_tx_buff[msg_tx_len++] = FPGA_RE_GFNOM;//RU 前端
	p_tx_buff[msg_tx_len++] = FPGA_RE_GDNOM;//RU 后端

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;

#endif
	
	// 发送应答包
	SendMsgPkt( msg_tx_len, p_tx_buff );
}

/*************************************************************
Name: MsgHandleSetParam          
Description: 消息包命令:设置参数
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleSetParam( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
//	UCHAR8 para_bak[SYS_PARAM_1B_COUNT+(SYS_PARAM_2B_COUNT*2)+(SYS_PARAM_4B_COUNT*4)+(SYS_PARAM_ASC_COUNT*64)];
	//UCHAR8 para_1b_bak[PARA_1B_MAX];
	//UINT16 para_2b_bak[PARA_2B_MAX];
	//UINT32 para_4b_bak[PARA_4B_MAX];

	UINT16 param_set_len;		// 参数设置串的长度
	UINT16 err_add;				// 错误参数的地址
	UCHAR8 * p_param_set_dat;
	UINT32 msg_tx_len;

	TRACE_INFO("[M]Msg Handle Set Param\r\n");

	param_set_len = msg_length - MSG_PKT_HEAD_SIZE;
	p_param_set_dat = p_msg_dat+MSG_PKT_HEAD_SIZE;

	msg_tx_len = MSG_CMD_BODY;
		
	// 检查参数设置串是否正确
#if 0
	if ( 0 != ParamChangeVerify( param_set_len, p_param_set_dat, 0, &err_add ) )
	{
		BackupSystemPara(para_bak);

		// 设置参数
		if ( b_TRUE == SetSysParam( param_set_len, p_param_set_dat ) )
		{
			// 保存参数
			SaveSysParamToFlash();
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
			goto _set_param_end;
		}
		
		RestoreSystemPara(para_bak);
		
	}
#endif
	BackupSystemPara(para_bak);

	// 设置参数
	if ( 0 != SetSysParam( param_set_len, 0, p_param_set_dat, &err_add ) )
	{
		// 保存参数
		SaveSysParamToFlash();
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	} 
	else
	{
		RestoreSystemPara(para_bak);

		TRACE_INFO("Err Param\r\n");
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_VALUE;
		p_tx_buff[msg_tx_len++] = (UCHAR8)(err_add & 0x000000FF);
		p_tx_buff[msg_tx_len++] = (UCHAR8)((err_add>>8) & 0x000000FF);
	}

	// 发送应答包
	SendMsgPkt( msg_tx_len, p_tx_buff );
	
}

/*************************************************************
Name: MsgHandleGetParam          
Description: 消息包命令:查询参数
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleGetParam( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
//	UCHAR8 * p_msg_body;
	UINT32 msg_tx_len;

	
	UINT32 i,j;
	UINT32 len;
	UINT32 addr, mo_addr;
	UINT32 val;
	UINT32 status = 1;

	TRACE_INFO("[M]Msg Handle Get Param\r\n");

//	p_msg_body = p_msg_dat + MSG_PKT_HEAD_SIZE;

	msg_tx_len = MSG_CMD_BODY;

	for ( i=MSG_CMD_BODY; (i+3)<msg_length; )
	{
		// 读取参数地址
		addr = p_msg_dat[i+0]|(p_msg_dat[i+1]<<8);

		// 读取参数长度
		len = p_msg_dat[i+2];

		// 地址和长度写入应答包
		p_tx_buff[msg_tx_len++] = p_msg_dat[i+0];
		p_tx_buff[msg_tx_len++] = p_msg_dat[i+1];
		p_tx_buff[msg_tx_len++] = p_msg_dat[i+2];
			
		//p_msg_body += 3;
		i+=3;
		
#if 0		
		if ( 0 == ParamAddTranslate( len, addr, &mo_addr ) )
		{
			TRACE_INFO_WP("Err Addr:%08X\r\n", addr);
			goto get_param_err_return;
		}
#endif		
		mo_addr = addr;
		
		TRACE_INFO("Madd:%04X. ", mo_addr);

		if ( 1 == len )
		{
			if (mo_addr>=SYS_PARAM_1B_COUNT)
			{
				msg_tx_len+=len;
				continue;				
			}			
			// 获取1字节参数
			val = sys_param_1b[mo_addr].val;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(val&0x00ff);
			TRACE_INFO_WP("val:%02X\r\n", val);
		}
		else if ( 2 == len )
		{
			if (mo_addr>=SYS_PARAM_2B_COUNT)
			{
				msg_tx_len+=len;
				continue;				
			}			
			// 获取2字节参数
			val = sys_param_2b[mo_addr].val;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(val&0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((val>>8)&0x00ff);
			TRACE_INFO_WP("val:%04X\r\n", val);
		}
		else if ( 4 == len )
		{
			if (mo_addr>=SYS_PARAM_4B_COUNT)
			{
				msg_tx_len+=len;
				continue;				
			}			
			// 获取4字节参数
			val = sys_param_4b[mo_addr].val;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(val&0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((val>>8)&0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((val>>16)&0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((val>>24)&0x00ff);
			TRACE_INFO_WP("val:%08X\r\n", val);
		}
		else if((TYPE_REE_1B == len)||(0xfc== len))
		{
			if (mo_addr>=SYS_PARAM_EU_1B_COUNT)
			{
				msg_tx_len+=1;
				continue;
				
			}		
			// 获取1字节参数
			val = sys_param_eu_1b[mo_addr].val;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(val&0x00ff);
//			TRACE_INFO("TYPE_REE_1B_val1:%02X\r\n", val);

		}else if((TYPE_REE_2B == len)||(0xfd== len))
		{
			if (mo_addr>=SYS_PARAM_EU_2B_COUNT)
			{
				msg_tx_len+=2;
				continue;
				
			}
							
			// 获取2字节参数
			val = sys_param_eu_2b[mo_addr].val;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(val&0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((val>>8)&0x00ff);
			TRACE_INFO_WP("TYPE_REE_2B_val2:%04X\r\n", val);
		}
		else if ( len <= PARAM_ASC_MAX_LEN )
		{
			if (mo_addr>=SYS_PARAM_ASC_COUNT)
			{
				msg_tx_len+=len;
				continue;				
			}			
			// 获取字符串参数
			for ( j=0; j<len; j++ )
			{
				if ( j > sys_param_asc[mo_addr].length )
				{
					p_tx_buff[msg_tx_len++] = 0;
				}
				else
				{
					p_tx_buff[msg_tx_len++] = sys_param_asc[mo_addr].p_asc[j];
				}
			}
		}
		else
		{
			goto get_param_err_return;
		}

		i+=len;
		
	}

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;

	// 发送应答包
	SendMsgPkt( msg_tx_len, p_tx_buff );
	return;

// 错误处理
get_param_err_return:

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_ADDR;

	msg_tx_len = MSG_CMD_BODY;
	p_tx_buff[msg_tx_len++] = (UCHAR8)(addr&0x00ff);
	p_tx_buff[msg_tx_len++] = (UCHAR8)((addr>>8)&0x00ff);
	
	// 发送错误应答
	SendMsgPkt( msg_tx_len, p_tx_buff );
	
}

void MsgHandleSetTable( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 tmp;
	UCHAR8 att_num;
	UCHAR8 ud_flag;
	UCHAR8 abcd_flag;


	TRACE_INFO("[M]Msg Handle Set Tbl\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_CMD_BODY;

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
		
#if 0
{
	UINT32 i;
	TRACE_INFO_WP("\r\n");
	for ( i=0; i<msg_length; i++ )
	{
		TRACE_INFO_WP("%02X ", p_msg_dat[i]);
	}
	TRACE_INFO_WP("\r\n");
}
#endif
	TRACE_INFO("Msg Handle_Set_Tbl_type=[%02X],ATT_NUMS=[%02X],ABCD_FLAGS=[%02X]\r\n",p_args[0],p_args[1],p_args[2]);
	if ( 0==p_args[0] )
	{

		att_num = p_args[1];

		//ab_flag=( 0==(p_args[2]&0x01) ) ? SYS_A_FLAG : SYS_B_FLAG;
		abcd_flag=( (p_args[2]&0x03) );//p_args[2]低四位含义，更改为0:为A段，1:为B段，2:为C段，3:为D段，
		switch(abcd_flag)
		{
			case 0x00:
				abcd_flag = SYS_A_FLAG;
			break;
			case 0x01:
				abcd_flag = SYS_B_FLAG;
			break;
			case 0x02:
				abcd_flag = SYS_C_FLAG;
			break;
			case 0x03:
				abcd_flag = SYS_D_FLAG;
			break;
			default:
				abcd_flag = SYS_A_FLAG;
			break;
		}
		ud_flag=( 0==(p_args[2]&0x08) ) ? 0 : 1;

		TRACE_INFO("Msg Handle_Set_Tbl_type[%02X]\r\n",p_args[0]);
		
		if ( 0==FpgaSaveAdjustTable( p_args+3, att_num, abcd_flag, ud_flag ) )
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_VALUE;
		}
		switch(abcd_flag)
		{
			case SYS_A_FLAG:
				InitPartA();   
			break;
		
			case SYS_B_FLAG:
				InitPartB();   
			break;
		
			case SYS_C_FLAG:
				InitPartC();   
			break;
	
			case SYS_D_FLAG:
				InitPartD();   
			break;
		}
	#if 0
		if ( 0==ud_flag )
		{
			FpgaSetDlAttAdjTable(ab_flag);
		}
		else
		{
			FpgaSetUlAttAdjTable(ab_flag);
		}

		// 退出校准模式
		FpgaExitAttAdjMode( ab_flag );
	#endif
	
		TRACE_INFO("Msg Handle_Set_Tbl_type_RETURN\r\n");
	
		// 发送错误应答
		SendMsgPkt( msg_tx_len, p_tx_buff );
	
	}else if ( 1==p_args[0] )	// 温度表格
	{
#if 0	
		p_args++;
		
		// 数据个数
		tmp = *p_args++;
		// 表格选择
		ab_flag=( 0==(p_args[0]&0x01) ) ? 0 : 1;
		ud_flag=( 0==(p_args[0]&0x02) ) ? 0 : 1;
		p_args++;
		// 保存到Flash
		if ( 0==SaveTempCmpTable( ab_flag, ud_flag, p_args ) )
		{
			// 写入表格错误
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_VALUE;
		}
		else
		{
			// 重新从Flash载入表格
			InitTempCmpTable( ab_fl ag, ud_flag );
			// 重置补偿
			TempGainCompensate( 1 );
		}
		
		// 发送错误应答
		SendMsgPkt( msg_tx_len, p_tx_buff );
#endif		
	}else if ( 2==p_args[0] )	// AD9363
	{
		TRACE_INFO("SET_AD9363\r\n");	
		PcPacketTransHead(p_tx_buff);	
		UartReceHandleSetFtPara(p_msg_dat,msg_length);
		
		
	}else if ( 3==p_args[0] )	// 频率校准
	{
		
		switch(p_args[2]&0x03)
		{
			case 0x00:
				abcd_flag = SYS_A_FLAG;
			break;
			case 0x01:
				abcd_flag = SYS_B_FLAG;
			break;
			case 0x02:
				abcd_flag = SYS_C_FLAG;
			break;
			case 0x03:
				abcd_flag = SYS_D_FLAG;
			break;
			default:
				abcd_flag = SYS_A_FLAG;
			break;
		}
		ud_flag=( 0==(p_args[2]&0x08) ) ? 0 : 1;
#if 0	
		// 保存到Flash
		if ( 0==SaveTempCmpTable( ab_flag, ud_flag, p_args ) )
		{
			// 写入表格错误
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_VALUE;
		}
		else
		{
			// 重新从Flash载入表格
			//InitTempCmpTable( ab_fl ag, ud_flag );
			// 重置补偿
			TempGainCompensate( 1 );
		}
		
		// 发送错误应答
		SendMsgPkt( msg_tx_len, p_tx_buff );
	
#endif 		
	}



}

void MsgHandleGetTable( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	
}

/*************************************************************
Name: MsgHandleSetDevReg          
Description: 消息包命令:设置器件寄存器
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleSetDevReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UCHAR8 dev_id = 0xff;
	UCHAR8 ret_val = 0;
	UINT32 i=0;
	UINT32 reg_len;
	UINT32 reg_add;
	UINT32 tmp;
	UINT32 msg_tx_len;

	TRACE_INFO("[M]Msg Handle Set Device\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;

	i = MSG_CMD_BODY;

	dev_id = p_msg_dat[i++];

	ret_val = MSG_ACK_CMD_OK;

	for ( ;(i+3)<msg_length; )
	{
		reg_add = p_msg_dat[i]|(p_msg_dat[i+1]<<8);
		i+=2;
		reg_len = p_msg_dat[i++];

		if ( 1 == reg_len )
		{
			tmp = p_msg_dat[i];
		}
		else if ( 2 == reg_len )
		{
			tmp = p_msg_dat[i]|(p_msg_dat[i+1]<<8);
		}
		else if ( 4 == reg_len )
		{
			tmp = p_msg_dat[i]|(p_msg_dat[i+1]<<8)|(p_msg_dat[i+2]<<16)|(p_msg_dat[i+3]<<24);
		}
		else
		{
			ret_val = MSG_ACK_ERR_VALUE;
			break;
		}
		i += reg_len;
		
		TRACE_INFO("[M]Msg Handle Set Device_dev_id[%d]\r\n",dev_id);
		switch( dev_id )
		{
		case DEV_ID_CLK:			// AD9517时钟
			Ad9524Write(reg_add, tmp);
			//TRACE_INFO_WP("<W IC>AD9517.");	
			break;

		case DEV_ID_FPGA:			// 逻辑FPGA
			if ( reg_add == 0xFA01 )
			{
				uart_ctl_ore_count = (UINT16)tmp;
			}
			else if ( reg_add == 0xFA02 )
			{
				uart_thr_ore_count = (UINT16)tmp;
			}
			else
			{
				FPGA_ENABLE_WRITE;
				FpgaWriteRegister( FPGA_WO_REG(reg_add), tmp);
				FPGA_DISABLE_WRITE;
			}
			//TRACE_INFO_WP("<W IC>FPGA.");	
			break;

		case DEV_ID_AD:			// ADC AD6655
			Ad6649Write(reg_add, tmp);
			//TRACE_INFO_WP("<W IC>AD6655.");	
			break;

		case DEV_ID_DA_A:		// A段DA AD9779
			Ad9122Write(reg_add, tmp, DA_A_FLAG);
			//TRACE_INFO_WP("<W IC>DA9779_A.");	
			break;

		case DEV_ID_DA_B:		// B段DA AD9779
			Ad9122Write(reg_add, tmp, DA_B_FLAG);
			//TRACE_INFO_WP("<W IC>DA9779_B.");	
			break;		

		case DEV_ID_A_UP_LINK:		// A段前端混频器
			    FPGA_ENABLE_WRITE;
				ReadWriteHmc830(A_MODEN,0,reg_add,tmp);
				FPGA_DISABLE_WRITE; 	
			break;

		case DEV_ID_A_DN_LINK:		// A段后端混频器	 
			    FPGA_ENABLE_WRITE;
				ReadWriteHmc830(A_MIXER,0,reg_add,tmp);
				FPGA_DISABLE_WRITE; 
			break;

		case DEV_ID_B_UP_LINK:		// B段前端混频器	
			    FPGA_ENABLE_WRITE;
				ReadWriteHmc830(B_MODEN,0,reg_add,tmp);
				FPGA_DISABLE_WRITE;	
			break;

		case DEV_ID_B_DN_LINK:		// B段后端混频器
			    FPGA_ENABLE_WRITE;
				ReadWriteHmc830(B_MIXER,0,reg_add,tmp);
				FPGA_DISABLE_WRITE; 	 
			break;  

		case DEV_ID_MCU:
			reg_add = (reg_add|0xFFFF0000)&0xFFFFFFFC;
			*((UINT32 *)reg_add) = tmp;
			//TRACE_INFO_WP("<W IC>MCU.");	
			break;
			
		case DEV_ID_A_AD9363:
			TRACE_INFO_WP("<W IC>9363.(CHAR8)reg_add=[%02x], tmp=[%08x]\r\n",(CHAR8)reg_add, tmp);
			CmdHandleSpiWrite(TF_A,reg_add,tmp);
			
			break;

		case DEV_ID_B_AD9363:
			TRACE_INFO_WP("<W IC>9363_B.(CHAR8)reg_add=[%02x], tmp=[%08x]\r\n",(CHAR8)reg_add, tmp);
			CmdHandleSpiWrite(TF_B,reg_add,tmp);
			
			break;
			
		case DEV_ID_C_AD9363:
			TRACE_INFO_WP("<W IC>9363_C.(CHAR8)reg_add=[%02x], tmp=[%08x]\r\n",(CHAR8)reg_add, tmp);
			CmdHandleSpiWrite(TF_C,reg_add,tmp);
			
			break;
			
		case DEV_ID_1197:
			TRACE_INFO_WP("<W IC>1197.(CHAR8)reg_add=[%02x], tmp=[%08x]\r\n",(CHAR8)reg_add, tmp);	
			WriteHmc1197((CHAR8)reg_add, tmp);			
			break;
			
		case DEV_ID_PHY4:
			TRACE_INFO("<W IC>PHY5_KSZ9031.data(%04x)\r\n",tmp);
			//PhyWrite(PHY5_KSZ9031,(0xFF00&reg_add)>>8,0xFF&reg_add,(UINT16 )(0xFFFF&tmp));
//			TRACE_INFO("<W IC>PHY4_VCS8662.data(%04x)\r\n",tmp);				
//			PhyWrite(PHY4_VCS8662,(0xFF00&reg_add)>>8,0xFF&reg_add,(UINT16 )(0xFFFF&tmp));
//			TRACE_INFO_WP("<W IC>PHY4_VCS8662.\r\n");	
			break;
			
			

		default:
			ret_val = MSG_ACK_ERR_VALUE;
		}

		if ( MSG_ACK_CMD_OK != ret_val )
		{
			break;
		}

		//TRACE_INFO_WP("%08X=%08X\r\n", reg_add, tmp );	

	}

	if ( DEV_ID_CLK==dev_id )
	{
#ifdef AD9528	
		Ad9524Write(AD9528_ADD_UPDATE_ALL,0x01);	// 需要写入01，写入的值才能生效
		//Ad9524Write(AD9524_ADD_UPDATE_ALL,0x01);	// 需要写入01，写入的值才能生效
#else
		Ad9524Write(AD9524_ADD_UPDATE_ALL,0x01);	// 需要写入01，写入的值才能生效
#endif
		
	} 

	p_tx_buff[MSG_ACK_FLAG] = ret_val; 
	SendMsgPkt(msg_tx_len, p_tx_buff);
	
}

/*************************************************************
Name: MsgHandleGetDevReg          
Description: 消息包命令:读取器件寄存器
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleGetDevReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UCHAR8 dev_id = 0xff;
	UCHAR8 ret_val = 0;
	UINT32 i=0;
	UINT32 reg_len;
	UINT32 reg_add;
	UINT32 tmp;
	UINT32 msg_tx_len;

	TRACE_INFO("[M]Msg Handle Get Device\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;

	i = MSG_CMD_BODY;
	dev_id = p_msg_dat[i++];
	
	p_tx_buff[msg_tx_len++] = dev_id;

	ret_val = MSG_ACK_CMD_OK;

	for ( ;(i+3)<msg_length; )
	{
		reg_add = p_msg_dat[i]|(p_msg_dat[i+1]<<8);
		reg_len = p_msg_dat[i+2];

		p_tx_buff[msg_tx_len++] = p_msg_dat[i];
		p_tx_buff[msg_tx_len++] = p_msg_dat[i+1];
		p_tx_buff[msg_tx_len++] = p_msg_dat[i+2];
		i+=3;
		TRACE_INFO_WP("%d\r\n",dev_id );
		switch( dev_id )
		{
			case DEV_ID_CLK:			// AD9517时钟
				tmp = Ad9524Read(reg_add);
				//TRACE_INFO_WP("%08X=%08X\r\n", reg_add, tmp );	
			break;

			case DEV_ID_FPGA:			// 逻辑FPGA
				if ( reg_add == 0xFA01 ) 
				{
					tmp = uart_ctl_ore_count;
				}
				else if ( reg_add == 0xFA02 )
				{
					tmp = uart_thr_ore_count;
				}
				else
				{
					//FpgaPowSelSlot(reg_add);
					tmp = FpgaReadRegister(reg_add);
				}
				//TRACE_INFO_WP("%08X=%08X\r\n", reg_add, tmp );	
				//TRACE_INFO_WP("<R IC>FPGA.");	
			break;

			case DEV_ID_AD:			// ADC AD6655
				tmp = Ad6643Read(reg_add);
				//TRACE_INFO_WP("<R IC>AD6655.");	
			break;

			case DEV_ID_DA_A:		// A段DA AD9779
				tmp = Ad9122Read(reg_add, DA_A_FLAG);
				//TRACE_INFO_WP("<R IC>DA9779_A.");	
			break;

			case DEV_ID_DA_B:		// B段DA AD9779
				tmp = Ad9122Read(reg_add, DA_B_FLAG);
				//TRACE_INFO_WP("<R IC>DA9779_B.");	
			break;

			case DEV_ID_A_UP_LINK:		// A段上行链路
			
			    FPGA_ENABLE_WRITE;
				tmp = ReadWriteHmc830(A_MODEN,1,reg_add,00);
				FPGA_DISABLE_WRITE;
					
				//TRACE_INFO_WP("<R IC> A_MODEN.");		
			break; 

			case DEV_ID_A_DN_LINK:		// A段下行链路	

			    FPGA_ENABLE_WRITE;
				tmp = ReadWriteHmc830(A_MIXER,1,reg_add,00);
                FPGA_DISABLE_WRITE;
				
				//TRACE_INFO_WP("<R IC> A_MIXER.");	
				
			break;

			case DEV_ID_B_UP_LINK:		// B段上行链路
			
			    FPGA_ENABLE_WRITE;
				tmp = ReadWriteHmc830(B_MODEN,1,reg_add,00);
				FPGA_DISABLE_WRITE;
				
				//TRACE_INFO_WP("<R IC> B_MODEN.");	
				
			break;

			case DEV_ID_B_DN_LINK:		// B段下行链路 

			    FPGA_ENABLE_WRITE;
 				tmp = ReadWriteHmc830(B_MIXER,1,reg_add,00);
				FPGA_DISABLE_WRITE;
				
				//TRACE_INFO_WP("<R IC> B_MIXER.");	 
				
			break;

			case DEV_ID_MCU:
				reg_add = (reg_add|0xFFFF0000)&0xFFFFFFFC;
				tmp = *((UINT32 *)reg_add);
				//TRACE_INFO_WP("<R IC>MCU.");	
			break;
			case DEV_ID_A_AD9363:	
				tmp=ReadWriteTF(TF_A,0,reg_add,0);	
				TRACE_INFO_WP("%08X=%08X\r\n", reg_add, tmp );
			break;
			
			case DEV_ID_B_AD9363:	
				tmp=ReadWriteTF(TF_B,0,reg_add,0);	
				TRACE_INFO_WP("%08X=%08X\r\n", reg_add, tmp );
			break;

			case DEV_ID_C_AD9363:	
				tmp=ReadWriteTF(TF_C,0,reg_add,0);	
				TRACE_INFO_WP("%08X=%08X\r\n", reg_add, tmp );
			break;			

			case DEV_ID_1197:	
				tmp=ReadHmc1197((CHAR8)reg_add);
				TRACE_INFO_WP("<R IC>1197.(CHAR8)reg_add=[%02x], tmp=[%08x]\r\n",(CHAR8)reg_add, tmp);					
			break;	
			
			case DEV_ID_PHY4:
			//tmp =(UINT32)PhyRead(PHY5_KSZ9031,(0xFF00&reg_add)>>8,0xFF&reg_add);
			TRACE_INFO_WP("<R IC>PHY5_KSZ9031.\r\n");				
//			tmp =(UINT32)PhyRead(PHY4_VCS8662,(0xFF00&reg_add)>>8,0xFF&reg_add);
//			TRACE_INFO_WP("<R IC>PHY4_VCS8662.\r\n");	
			break;
			
			
			default:
				
				ret_val = MSG_ACK_ERR_ADDR;
				msg_tx_len = MSG_PKT_HEAD_SIZE;
		}
		
		if ( MSG_ACK_CMD_OK != ret_val )
		{
			break;
		}

		if ( 1 == reg_len )
		{
			p_tx_buff[msg_tx_len++] = tmp;
		}
		else if ( 2 == reg_len )
		{
			p_tx_buff[msg_tx_len++] = (UCHAR8)(tmp&0xff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>8)&0xff);
		}
		else if ( 4 == reg_len )
		{
			p_tx_buff[msg_tx_len++] = (UCHAR8)(tmp&0xff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>8)&0xff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>16)&0xff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>24)&0xff);
		}
		else
		{
			ret_val = MSG_ACK_ERR_VALUE;
			msg_tx_len = MSG_PKT_HEAD_SIZE;
			break;
		}
		i += reg_len;

		TRACE_INFO_WP("%08X=%08X\r\n", reg_add, tmp );	
	}

	p_tx_buff[MSG_ACK_FLAG] = ret_val;
	SendMsgPkt(msg_tx_len, p_tx_buff);
	
}

/*************************************************************
Name: MsgHandleResetDev          
Description: 消息包命令: 初始化器件
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleResetDev( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UCHAR8 dev_id = 0xff;
	BOOL ret_val = 0;
	UCHAR8 output_st = 0;	// 当前输出状态: b0表示A段,b1表示B段; 0-输出关闭,1-输出打开
//	UINT32 len;
//	UINT32 tmp;
	UINT32 msg_tx_len;
	UCHAR8 * p_args; 

	//TRACE_INFO("[M]Msg Handle Reset Device\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_PKT_HEAD_SIZE;

	dev_id = p_args[0];
	
	// 保存输出状态
	if ( b_TRUE==FpgaIsEnableA() )	output_st |= 0x01;
	if ( b_TRUE==FpgaIsEnableB() )	output_st |= 0x02;
	// 关闭调制器输出
	EnableModulatorA( 0 );
	EnableModulatorB( 0 );

	switch( dev_id )
	{
	case DEV_ID_CLK:
//			    ret_val = InitAllKeyDev(); 
//				ret_val = InitAllKeyDev();
		InitClkChip();
		ret_val = (0==GetAD9524LD()) ? b_FALSE : b_TRUE;
		break;   

	case DEV_ID_FPGA:			// 逻辑FPGA
		ret_val = InitFpga();
		break;

	case DEV_ID_AD:			   // ADC AD6655
	    ret_val = InitAD();
		break;

	case DEV_ID_DA_A:		    // A段DA AD9779
		//ret_val = InitDA_A();
		break; 

	case DEV_ID_DA_B:		// B段DA AD9779
		//ret_val = InitDA_B();
		break;

	case DEV_ID_A_UP_LINK:		// A段前端混频器	
		//ret_val = Init_Local_Pll(A_MODEN);
		break;

	case DEV_ID_A_DN_LINK:		// A段后端混频器	
		//ret_val = Init_Local_Pll(A_MIXER);
		break;

	case DEV_ID_B_UP_LINK:		// B段前端混频器	
		//ret_val = Init_Local_Pll(B_MODEN);
		break;

	case DEV_ID_B_DN_LINK:		// B段后端混频器
		//ret_val = Init_Local_Pll(B_MIXER);
		break;

	default:
		ret_val = b_FALSE;
	}

	if ( b_TRUE == ret_val )
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	}
	else
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_ADDR;
	}
	
	SendMsgPkt(msg_tx_len, p_tx_buff);

	if ( 0!=output_st )	// 输出状态有效, 延时打开输出
	{
		WTD_CLR;
		UsNopDelay( 500000 );
		WTD_CLR;
		UsNopDelay( 500000 );
		if ( 0!=(output_st&0x01) ) EnableModulatorA( 1 );
		if ( 0!=(output_st&0x02) ) EnableModulatorB( 1 );
		WTD_CLR;
	}
}

/*************************************************************
Name: MsgHandleGetFpgaReg          
Description: 消息包命令:读取器件寄存器
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleGetFpgaReg( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UCHAR8 reg_type,reg_type2,guangkou,channel;
	UINT32 i=0;
	UINT32 reg_add;
	UINT32 tmp;
	UINT32 msg_tx_len;

	//TRACE_INFO("[M]Msg Handle Get Fpga Reg\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;

	i = MSG_CMD_BODY;
			
	for ( ;(i+3)<msg_length; )
	{
		reg_type = p_msg_dat[i];
		p_tx_buff[msg_tx_len++] = p_msg_dat[i++];
		
		//TRACE_INFO( "Reg_%04XH, ", reg_add );
		
		FPGA_ENABLE_WRITE;
		if ( REG_TYPE_CHN==(reg_type&REG_TYPE_MASK) )
		{
					

			FPGA_SET_CHANNEL( reg_type&REG_TYPE_ARGS );
			//TRACE_INFO_WP( "Ch%d", reg_type&REG_TYPE_ARGS );
		}
		else if ( REG_TYPE_OPT==(reg_type&REG_TYPE_MASK) )
		{
					

			FPGA_SET_OPT(reg_type&REG_TYPE_ARGS);
			//TRACE_INFO_WP( "Fp%d", reg_type&REG_TYPE_ARGS );
		}
		else if ( REG_TYPE_TDSLOT == (reg_type&REG_TYPE_MASK) )
		{			

			FPGA_SET_CHANNEL( reg_type&REG_TYPE_ARGS );
			FpgaWriteRegister( FPGA_REG_TDSLOT_SEL, p_msg_dat[i] );
			p_tx_buff[msg_tx_len++] = p_msg_dat[i++];
		}
		else if ( FPGA_TDS_LTE_REG == (reg_type&FPGA_TDS_LTE_REG) )
		{
			FPGA_SET_CHANNEL( reg_type&REG_TYPE_ARGS );
			FpgaWriteRegister( FPGA_REC_C_TD_LTE_SLOT_SEL, p_msg_dat[i] );
			p_tx_buff[msg_tx_len++] = p_msg_dat[i++];
			
		}
		else if( REG_TYPE_NORMAL == (reg_type&REG_TYPE_MASK))
		{
			FPGA_SET_CHANNEL( reg_type&REG_TYPE_ARGS );
			p_tx_buff[msg_tx_len++] = p_msg_dat[i++];		
		}
		else if ( REG_TYPE_OTHER == (reg_type&REG_TYPE_MASK) )
		{
			reg_type2 = p_msg_dat[i];
			p_tx_buff[msg_tx_len++] = p_msg_dat[i++];

			printf("type2 = %02x \r\n",reg_type2);

			if ( REG_TYPE_OTHER_TYPE1 == reg_type2 )
			{
				guangkou =  p_msg_dat[i];
				FPGA_SET_OPT(guangkou);
				p_tx_buff[msg_tx_len++] = p_msg_dat[i++];	

				printf("guangkou = %02x \r\n",guangkou);

				channel =  p_msg_dat[i];
				FPGA_SET_CHANNEL( channel );
				p_tx_buff[msg_tx_len++] = p_msg_dat[i++];

				printf("channel = %02x \r\n",channel);
			}
			
		}
		FPGA_DISABLE_WRITE;
		
		reg_add = p_msg_dat[i]|(p_msg_dat[i+1]<<8);
		p_tx_buff[msg_tx_len++] = p_msg_dat[i++];
		p_tx_buff[msg_tx_len++] = p_msg_dat[i++];

		//FpgaPowSelSlot(reg_add);
		tmp = FpgaReadRegister(reg_add);

		//TRACE_INFO_WP( ", Val=%04XH\r\n", tmp );
		
		p_tx_buff[msg_tx_len++] = (UCHAR8)(tmp&0xff);
		p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>8)&0xff);
		i += 2;

	}

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	SendMsgPkt(msg_tx_len, p_tx_buff);
	
}

/*************************************************************
Name: MsgHandleSetTopo          
Description: 消息包命令:设置正确拓扑
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleSetTopo( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 len;
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	
	TRACE_INFO("[M]Msg Handle Set Valid Topo\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE; 
	p_args = p_msg_dat+MSG_PKT_HEAD_SIZE; 
	
	SetValidTopo( p_args );

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;

	SendMsgPkt(msg_tx_len, p_tx_buff);
}

/*************************************************************
Name: MsgHandleSetTopo          
Description: 消息包命令:设置正确拓扑
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleGetTopo( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 len;
	UCHAR8 tmp;
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 fp_no, re_no,ree_no;  
	 
	TRACE_INFO("[M]Msg Handle Get Topo 1 \r\n"); 

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_PKT_HEAD_SIZE;
	
	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	p_tx_buff[msg_tx_len++] = p_args[0];

	if ( 0x00 == p_args[0] )		// 查询类型:当前拓扑
	{
		TRACE_INFO("[M]Msg Handle Get Topo  2\r\n"); 
		for ( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			// 光口状态
			tmp = 0;
			
			if ( COMMA_LOCK==fp_inf[fp_no].comma_lock )	// 逗号锁定
			{
                  		tmp |= (0x01<<7);
			}
			
			if ( FRAME_LOCK==fp_inf[fp_no].frm_lock )	// 接收帧锁定
			{
				 tmp |= (0x01<<6);
			}

			if ( 0 != ( OPS_RCV_FLAG & fp_inf[fp_no].ops_info ) )	// 收到对端光口数据，环网
			{
				tmp |= (0x01<<4);		// 环网
				tmp |= ( fp_inf[fp_no].ops_info & OPS_NO_MASK );		// 对端光口号
			}


			p_tx_buff[msg_tx_len++] = tmp;  //bit7~逗号锁定，bit6~帧锁定，bit4~环网标志，bit3~bit0 对端光口号 
			p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_cnt; //当前光口的EU个数 
//			p_tx_buff[msg_tx_len++] = fp_inf[fp_no].ree_cnt; //当前光口的REe个数  
			TRACE_INFO("\r\n"); 
			TRACE_INFO("fp_inf[fp_no].re_cnt(%0x)\r\n",fp_inf[fp_no].re_cnt); 	

			
			for ( re_no=0; re_no< fp_inf[fp_no].re_cnt; re_no++ )  
			{
				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].re_status; //包含了光口0、1的锁定状态和上、下行光口的判断
				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].re_id;     //光口ID 
				
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_count;           //当前光口当前节点的REe个数 
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_sync_st_inf[0];     // 4个连接RF的光口状态和8个连接RF的网口状态
//				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_sync_st_inf[1];     // 	
				p_tx_buff[msg_tx_len++] = tmp_re_inf[fp_no][re_no].ree_nt_stat;     // EU下面8个网口RU的连接状态
				p_tx_buff[msg_tx_len++] =tmp_re_inf[fp_no][re_no].ree_fp_stat;     // EU下面8个光口RU的连接状态
				p_tx_buff[msg_tx_len++] =(UCHAR8)(tmp_re_inf[fp_no][re_no].ree_work_status>>8);     // 4个连接RF的光口状态和8个连接RF的网口状态
				p_tx_buff[msg_tx_len++] =(UCHAR8)tmp_re_inf[fp_no][re_no].ree_work_status;     // 

				TRACE_INFO("fp_inf[fp_no].re_info[re_no].re_status(%0x)\r\n",fp_inf[fp_no].re_info[re_no].re_status); 
				TRACE_INFO("fp_inf[fp_no].re_info[re_no].re_id(%0x)\r\n",fp_inf[fp_no].re_info[re_no].re_id); 
				TRACE_INFO("tmp_re_inf[fp_no][re_no].ree_nt_stat(%0x)\r\n",tmp_re_inf[fp_no][re_no].ree_nt_stat); 
				TRACE_INFO("tmp_re_inf[fp_no][re_no].ree_fp_stat(%0x)\r\n",tmp_re_inf[fp_no][re_no].ree_fp_stat); 
				TRACE_INFO("(0xff00&tmp_re_inf[fp_no][re_no].ree_work_status)>>8(%0x)\r\n",(0xff00&tmp_re_inf[fp_no][re_no].ree_work_status)>>8); 
				TRACE_INFO("0xff&tmp_re_inf[fp_no][re_no].ree_work_status(%0x)\r\n",0xff&tmp_re_inf[fp_no][re_no].ree_work_status); 	
				TRACE_INFO("\r\n"); 
				
			} 
			
		}

		#if 0
		//顺便查询告警参数，解决AU EU告警参量不同的问题		
		{
			p_tx_buff[msg_tx_len++] = '+';
			p_tx_buff[msg_tx_len++] = sys_param_1b[MADD_WORK_ERROR].val?1:0;//AU告警项
			p_tx_buff[msg_tx_len++] = sys_param_eu_1b[MADD_EU_ALARM_FLAG1].val?1:0;//EU告警项
			p_tx_buff[msg_tx_len++] = sys_param_eu_1b[MADD_EU_ALARM_FLAG2].val?1:0;//EU告警项
			p_tx_buff[msg_tx_len++] = sys_param_eu_1b[MADD_EU_ALARM_FLAG3].val?1:0;//EU告警项
			p_tx_buff[msg_tx_len++] = sys_param_eu_1b[MADD_EU_ALARM_FLAG4].val?1:0;//EU告警项
			p_tx_buff[msg_tx_len++] = sys_param_eu_1b[MADD_EU_ALARM_FLAG5].val?1:0;//EU告警项
			p_tx_buff[msg_tx_len++] = sys_param_eu_1b[MADD_EU_ALARM_FLAG6].val?1:0;//EU告警项
			p_tx_buff[msg_tx_len++] = sys_param_eu_1b[MADD_EU_ALARM_FLAG7].val?1:0;//EU告警项
			p_tx_buff[msg_tx_len++] = sys_param_eu_1b[MADD_EU_ALARM_FLAG8].val?1:0;//EU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG1].val);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG1].val>>8);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG2].val);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG2].val>>8);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG3].val);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG3].val>>8);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG4].val);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG4].val>>8);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG5].val);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG5].val>>8);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG6].val);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG6].val>>8);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG7].val);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG7].val>>8);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG8].val);//EU对应的RU告警项
			p_tx_buff[msg_tx_len++] = (UCHAR8)(sys_param_eu_2b[MADD_EU_RUALARM_FLAG8].val>>8);//EU对应的RU告警项
		}
		#endif
		{
			p_tx_buff[msg_tx_len++] = '+';
			p_tx_buff[msg_tx_len++] = sys_param_1b[MADD_WORK_ERROR].val?1:0;//AU告警项
			for ( fp_no=0; fp_no<FP_MAX; fp_no++ )
			{
				//p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_cnt;
				for ( re_no=0; re_no< fp_inf[fp_no].re_cnt; re_no++ )  
				{
					p_tx_buff[msg_tx_len++] = topo_alarm[fp_no][re_no].meu_alarm?1:0; //EU告警项
					
					p_tx_buff[msg_tx_len++] = (UCHAR8)(topo_alarm[fp_no][re_no].ru_alarm);//EU对应的RU告警项
					p_tx_buff[msg_tx_len++] = (UCHAR8)(topo_alarm[fp_no][re_no].ru_alarm>>8);//EU对应的RU告警项			
				} 
			
			}
		}
	}
	else if ( 0x01==p_args[0] )		// 查询类型:已设置的正确拓扑
	{
		for ( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			p_tx_buff[msg_tx_len++] = valid_fp_topo[fp_no].fp_mode;
			p_tx_buff[msg_tx_len++] = valid_fp_topo[fp_no].re_count;
			
			for ( re_no=0; re_no<valid_fp_topo[fp_no].re_count; re_no++ )
			{
				p_tx_buff[msg_tx_len++] = valid_fp_topo[fp_no].re_inf[re_no].mode;
				p_tx_buff[msg_tx_len++] = valid_fp_topo[fp_no].re_inf[re_no].id;
				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_sync_st_inf[0];     // 4个连接RF的光口状态和8个连接RF的网口状态
                		p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].ree_sync_st_inf[1];     // 
			}
		}
	}
	else		// 错误的拓扑类型
	{ 
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_ADDR; 
	}
	
	SendMsgPkt(msg_tx_len, p_tx_buff);
	
}

#if 0
void MsgHandleGetTopo( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 len;
	UCHAR8 tmp;
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 fp_no, re_no;
	 
	TRACE_INFO("[M]Msg Handle Get Topo\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_PKT_HEAD_SIZE;
	
	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	
	p_tx_buff[msg_tx_len++] = p_args[0];

	if ( 0x00 == p_args[0] )		// 查询类型:当前拓扑
	{
		for ( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			// 光口状态
			tmp = 0;
			
			if ( COMMA_LOCK==fp_inf[fp_no].comma_lock )	// 逗号锁定
			{
				//#ifdef CLIENT_XINMIN
                  tmp |= (0x01<<7);
			}
			
			if ( FRAME_LOCK==fp_inf[fp_no].frm_lock )	// 接收帧锁定
			{
				tmp |= (0x01<<6);
			}

			if ( 0 != ( OPS_RCV_FLAG & fp_inf[fp_no].ops_info ) )	// 收到对端光口数据，环网
			{
				tmp |= (0x01<<4);		// 环网
				tmp |= ( fp_inf[fp_no].ops_info & OPS_NO_MASK );		// 对端光口号
			}

			p_tx_buff[msg_tx_len++] = tmp; //光口状态
			p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_cnt; //此光口包含多是个RE
			
			for ( re_no=0; re_no<fp_inf[fp_no].re_cnt; re_no++ )
			{
				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].status;
				p_tx_buff[msg_tx_len++] = fp_inf[fp_no].re_info[re_no].id;
                
			}
			
		}
	}
	else if ( 0x01==p_args[0] )		// 查询类型:已设置的正确拓扑
	{
		for ( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			p_tx_buff[msg_tx_len++] = valid_fp_topo[fp_no].fp_mode;
			p_tx_buff[msg_tx_len++] = valid_fp_topo[fp_no].re_count;
			for ( re_no=0; re_no<valid_fp_topo[fp_no].re_count; re_no++ )
			{
				p_tx_buff[msg_tx_len++] = valid_fp_topo[fp_no].re_inf[re_no].mode;
				p_tx_buff[msg_tx_len++] = valid_fp_topo[fp_no].re_inf[re_no].id;
			}
		}
	}
	else		// 错误的拓扑类型
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_ADDR;
	}
	
	SendMsgPkt(msg_tx_len, p_tx_buff);
	
}
#endif

/*************************************************************
Name: MsgHandleUpdateMCU          
Description: 消息包命令:MCU升级
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleUpdateMCU( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 pkt_count;
	UINT16 pkt_no;
	UINT32 len;
	UINT32 tmp;
	UINT32 msg_tx_len;
	UCHAR8 * p_args;

	TRACE_INFO("Message Handle Update MCU!\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_PKT_HEAD_SIZE;

	//TRACE_INFO("mcu Update Packet Param:[%02X][%02X][%02X][%02X]\r\n",p_args[0],p_args[1],p_args[2],p_args[3]);

	if (( 0xFA == p_args[0] )&&( 0x5A == p_args[1] ))
	{
		//起始包
		pkt_count = p_args[2]|(p_args[3]<<8);
		len = p_args[4]|(p_args[5]<<8)|(p_args[6]<<16)|(p_args[7]<<24);
		if ( 0 == UpdateStart( UPDATE_TYPE_MCU, len, pkt_count) )
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_UPDATE_FAIL;
		}
		else
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
		}
	}
	else if (( 0xA5 == p_args[0] )&&( 0xAF == p_args[1] ))
	{
		//结束包
		tmp = p_args[2]|(p_args[3]<<8);
		if ( 0 == McuUpdateEnd( tmp, &tmp) )
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_UPDATE_FAIL;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(tmp & 0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>8) & 0x00ff);
		}
		else
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
			sys_work_info |= SYSTEM_FLAG_MCU_RELOAD;
			sys_work_info &= (~SYSTEM_FLAG_MCU_UPDATE);
		}
	}
	else
	{
		pkt_no = p_args[0]|(p_args[1]<<8);
		len = p_args[2]|(p_args[3]<<8);

		if ( pkt_no == 1 )
		{
			if ( 0==CheckIsMcuFw( (UINT32*)(p_args+4) ) )	// 检查数据头，判断是否是合法的MCU程序
			{
				p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_UPDATE_FAIL;
				goto __re_ack;
			}
		}

		if ( 0 == SaveMcuUpdatePkt( pkt_no, len, p_args+4, (UCHAR8*)(&tmp) ) )
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_UPDATE_PKT;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(tmp & 0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>8) & 0x00ff);
		}
		else
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
		}
	}

__re_ack:
	SendMsgPkt(msg_tx_len, p_tx_buff);
}

/*************************************************************
Name: MsgHandleUpdateFPGA          
Description: 消息包命令:FPGA升级
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleUpdateFPGA( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 len;
	UINT32 tmp;
	UINT32 msg_tx_len;
	UCHAR8 * p_args;

	TRACE_INFO("Message Handle Update FPGA!\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_PKT_HEAD_SIZE;

	//printf("FPGA Update Packet Param:[%02X][%02X][%02X][%02X]\r\n",p_args[0],p_args[1],p_args[2],p_args[3]);

	if (( 0xFA == p_args[0] )&&( 0x5A == p_args[1] ))
	{
		UINT32 pkt_count;
		
		//起始包
		pkt_count = p_args[2]|(p_args[3]<<8);
		len = p_args[4]|(p_args[5]<<8)|(p_args[6]<<16)|(p_args[7]<<24);
		if ( 0 == UpdateStart( UPDATE_TYPE_FPGA, len, pkt_count) )
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_UPDATE_FAIL;
		}
		else
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
		}
	}
	else if (( 0xA5 == p_args[0] )&&( 0xAF == p_args[1] ))
	{
		TRACE_INFO("Message Handle Update FPGA_________FpgaUpdateEnd!\r\n");
		//结束包
		tmp = p_args[2]|(p_args[3]<<8);
		if ( 0 == FpgaUpdateEnd( tmp, &tmp) )
		{
			TRACE_INFO("Message Handle Update FPGA____FpgaUpdate_UPDATE_FAIL!\r\n");
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_UPDATE_FAIL;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(tmp & 0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>8) & 0x00ff);
		}
		else
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
			sys_work_info |= SYSTEM_FLAG_FPGA_RELOAD;
			sys_work_info &= (~SYSTEM_FLAG_FPGA_UPDATE);
		}
	}
	else
	{
		UINT16 pkt_no;

		pkt_no = p_args[0]|(p_args[1]<<8);
		len = p_args[2]|(p_args[3]<<8);
//		printf("Rx Pkt:%d",pkt_no);
		if ( 0 == SaveFpgaUpdatePkt( pkt_no, len, p_args+4, &tmp) )
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_UPDATE_PKT;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(tmp & 0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((tmp>>8) & 0x00ff);
//			printf("-Err Need:%d", (UINT16)tmp);
		}
		else
		{
			p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
			p_tx_buff[msg_tx_len++] = (UCHAR8)(pkt_no & 0x00ff);
			p_tx_buff[msg_tx_len++] = (UCHAR8)((pkt_no>>8) & 0x00ff);
		}
	}
	SendMsgPkt(msg_tx_len, p_tx_buff);
}

/*************************************************************
Name: MsgHandleGetFlashPage          
Description: 消息包命令:读取外部FLASH一个page的内容
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleGetFlashPage( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 page;
	UINT32 msg_tx_len;
	UCHAR8 * p_args;

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_CMD_BODY;

	page = (UINT32)( p_args[0]|(p_args[1]<<8)|(p_args[2]<<16)|(p_args[3]<<24) );



	
	if ( page >= FLASH_PAGE_COUNT )
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_ADDR;
	}
	else
	{
		TRACE_INFO("[[[[[[MsgHandleGetFlashPage;page:%d\r\n",page);
//		FlashReadOnePage(page, 0, p_tx_buff+MSG_CMD_BODY);
		FlashRead(page, 0, p_tx_buff+MSG_CMD_BODY,FLASH_PAGE_SIZE);

		msg_tx_len += FLASH_PAGE_SIZE;
		
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	}
	SendMsgPkt(msg_tx_len, p_tx_buff);
}
/*************************************************************
Name: MsgHandleFlashOperatePage        
Description: 消息包命令:擦除外部FLASH一个page的内容
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleFlashOperatePage( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{


	UINT32 length;
	UINT32 page_len;
	UINT32 msg_tx_len;
	UINT32 page ;

	UCHAR8 *p_args ;
    p_args = p_msg_dat+MSG_CMD_BODY;
	
	length = msg_length-MSG_PKT_HEAD_SIZE;

    msg_tx_len =  msg_length ;
	
	if(p_msg_dat[MSG_RESERVE1]==0) //擦除Flash 操作
	{
	    TRACE_INFO("FlashErase!\r\n");
	    page = (UINT32)( p_args[0]|(p_args[1]<<8)|(p_args[2]<<16)|(p_args[3]<<24) )*((UINT32)(FLASH_PAGE_SIZE_1056/FLASH_PAGE_SIZE));
        TRACE_INFO("page=%d,page=%x\r\n",page,page);
	   	if ( page >= FLASH_PAGE_COUNT )
		{
		   p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_ADDR;
		}
		else
		{
		  // FlashErasePage ( page ) ;
		   p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
		}
	
	   
	}else if(p_msg_dat[MSG_RESERVE1]==1) //得到Flash页信息
	{ 
	   GetFlashPageInfo(length ,p_args ,p_tx_buff+MSG_PKT_HEAD_SIZE );
	   p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	}
	
	SendMsgPkt(msg_tx_len, p_tx_buff);
}

/*************************************************************
Name: MsgHandleStartAttAdj          
Description: 消息包命令:进入校准模式
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleStartAttAdj( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 tmp;

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_CMD_BODY;

	p_tx_buff[msg_tx_len++] = p_args[0]; //A OR B SECTION
	p_tx_buff[msg_tx_len++] = p_args[1]; //in or out
if(NET_TYPE_TD == fpga_cfg.b_net_type )
{
	if((SEL_RE|ADJ_REC|SEL_DL|SEL_B)==p_msg_dat[MSG_RESERVE1])
	{
		//CloseDA_B();
		return;
	}
	if((SEL_REC|SEL_B|SEL_DL|ADJ_RE)==p_msg_dat[MSG_RESERVE1])
	{
		//CloseDA_B();
	}
}
	TRACE_INFO ("MsgHandleStartAttAdj++++++++++++++++test20131016_10fpga_att_adj_st.ab_flag=%x\r\n",fpga_att_adj_st.ab_flag);
	if ( 0x00 == p_args[0] )    // A   
	{
		fpga_att_adj_st.adj_st  = ATT_ADJ_ST_MAX_ADJ; //开始最大校正
		fpga_att_adj_st.is_wait = 0;
		fpga_att_adj_st.ab_flag = SYS_A_FLAG;

	}    
	else if ( 0x01 == p_args[0] )// B    
	{ 
		fpga_att_adj_st.adj_st = ATT_ADJ_ST_MAX_ADJ;  //开始最大校正
		fpga_att_adj_st.is_wait = 0;
		fpga_att_adj_st.ab_flag = SYS_B_FLAG;
		TRACE_INFO ("MsgHandleStartAttAdj++++++++++++++++test20131016_fpga_cfg.b_ultra_info=[%x]\r\n",fpga_cfg.b_ultra_info); 
		if(fpga_cfg.b_ultra_info==FPGA_B_NT_TD_WB)
		{
			TRACE_INFO ("MsgHandleStartAttAdj++++++++++++++++test201312061434_p_args[1]=[%x]\r\n",p_args[1]); 
			FPGA_ENABLE_WRITE;
			if ( 0==p_args[1] )  
			{					// 上行输出
				//fpga_att_adj_st.ud_flag=ATT_UL_ADJ;
				FpgaWriteRegister(FPGA_REG_TD_WORK_MODE, TD_WM_UL_ALWAYS_ON);
				sys_param_1b[MADD_TD_WORK_MODE].val = 1;
				ReadWriteTF(TF_B,1,0X56,0X00);//打开上行，输出通道、
				tmp=ReadWriteTF(TF_B,0,0x057,0x01);
				tmp&=(~0x01);
				ReadWriteTF(TF_B,1,0x057,tmp);	
			}    
			else 
			{					// 下行输入
				//fpga_att_adj_st.ud_flag=ATT_DL_ADJ;
				FpgaWriteRegister(FPGA_REG_TD_WORK_MODE, TD_WM_DL_ALWAYS_ON);
				sys_param_1b[MADD_TD_WORK_MODE].val = 2;
				ReadWriteTF(TF_B,1,0X56,0XF0);//打开上行，输出通道、
				tmp=ReadWriteTF(TF_B,0,0x057,0x01);
				tmp|=0x01;
				ReadWriteTF(TF_B,1,0x057,tmp);
 
				tmp=ReadWriteTF(TF_B,0,0x053,0x01);
				tmp&=~((0x01<<3)|(0x01<<5));
				ReadWriteTF(TF_B,1,0x053,tmp);				
			}
			FPGA_DISABLE_WRITE;

		}
	} 
	else if ( 0x02 == p_args[0] )// C    
	{ 
		fpga_att_adj_st.adj_st = ATT_ADJ_ST_MAX_ADJ;  //开始最大校正
		fpga_att_adj_st.is_wait = 0;
		fpga_att_adj_st.ab_flag = SYS_C_FLAG;

			TRACE_INFO ("MsgHandleStartAttAdj++++++++++++++++test201312061434C_p_args[1]=[%x]\r\n",p_args[1]); 
			FPGA_ENABLE_WRITE;
			if ( 0==p_args[1] )  
			{		// 上行输出
				FpgaWriteRegister(FPGA_REC_C_TD_WORK_MODE, TD_WM_UL_ALWAYS_ON);
				sys_param_1b[MADD_C_TD_WORK_MODE].val = TD_WM_UL_ALWAYS_ON;
				ReadWriteTF(TF_C,1,0X56,0X00);//打开上行，输出通道、
				//校准上行时，打开上行射频开关
				tmp=ReadWriteTF(TF_C,0,0x057,0x01);
				tmp&=(~0x01<<1);
				ReadWriteTF(TF_C,1,0x057,tmp);	
			}    
			else 
			{		// 下行输入
				FpgaWriteRegister(FPGA_REC_C_TD_WORK_MODE, TD_WM_DL_ALWAYS_ON);
				sys_param_1b[MADD_C_TD_WORK_MODE].val = TD_WM_DL_ALWAYS_ON;
				ReadWriteTF(TF_C,1,0X56,0XF0);//关闭上行，输出通道
			
				//校准下行时关上行射频开关，打开下行射频开关
				tmp=ReadWriteTF(TF_C,0,0x057,0x01);
				tmp|=(0x01<<1);
				ReadWriteTF(TF_C,1,0x057,tmp);
 
				tmp=ReadWriteTF(TF_C,0,0x053,0x01);
				tmp&=~((0x01<<3)|(0x01<<5));
				
				ReadWriteTF(TF_C,1,0x053,tmp);				
			}
			FPGA_DISABLE_WRITE;
		
	}
	else if ( 0x03 == p_args[0] )// D    
	{ 
		fpga_att_adj_st.adj_st = ATT_ADJ_ST_MAX_ADJ;  //开始最大校正
		fpga_att_adj_st.is_wait = 0;
		fpga_att_adj_st.ab_flag = SYS_D_FLAG;

			TRACE_INFO ("MsgHandleStartAttAdj++++++++++++++++test201312061434D_p_args[1]=[%x]\r\n",p_args[1]); 
			FPGA_ENABLE_WRITE;
			if ( 0==p_args[1] )  
			{		// 上行输出
				FpgaWriteRegister(FPGA_REC_D_TD_WORK_MODE, TD_WM_UL_ALWAYS_ON);
				sys_param_1b[MADD_D_TD_WORK_MODE].val = TD_WM_UL_ALWAYS_ON;
				ReadWriteTF(TF_D,1,0X56,0X00);//打开上行，输出通道、				

				//校准上行时，打开上行射频开关
				tmp=ReadWriteTF(TF_C,0,0x057,0x01);
				tmp&=(~0x01<<0);
				ReadWriteTF(TF_C,1,0x057,tmp);	
			}    
			else 
			{		// 下行输入
				FpgaWriteRegister(FPGA_REC_D_TD_WORK_MODE, TD_WM_DL_ALWAYS_ON);
				sys_param_1b[MADD_D_TD_WORK_MODE].val = TD_WM_DL_ALWAYS_ON;
				ReadWriteTF(TF_D,1,0X56,0XF0);//打开上行，输出通道、

				//校准下行时关上行射频开关，打开下行射频开关
				tmp=ReadWriteTF(TF_C,0,0x057,0x01);
				tmp|=(0x01<<0);
				ReadWriteTF(TF_C,1,0x057,tmp);
 
				tmp=ReadWriteTF(TF_C,0,0x053,0x01);
				tmp&=~((0x01<<2)|(0x01<<4));
				
				ReadWriteTF(TF_C,1,0x053,tmp);				
			}
			FPGA_DISABLE_WRITE;
		
	}	
	else 
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_VALUE;
		SendMsgPkt(msg_tx_len, p_tx_buff);
		return;
	}

	if ( 0==p_args[1] )  
	{
		// 上行输出
		fpga_att_adj_st.ud_flag=ATT_UL_ADJ;
		
	}    
	else 
	{
		// 下行输入
		fpga_att_adj_st.ud_flag=ATT_DL_ADJ;
	}

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;

	FpgaMakeAttAdjMsgHead( msg_tx_len, p_tx_buff );

	sys_work_info |= SYSTEM_FLAG_ATT_ADJ;
	
}

/*************************************************************
Name: MsgHandleAttStepAdj          
Description: 消息包命令:步进校准
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleAttStepAdj( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 ab_flag;
	UINT32 tmp;

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_CMD_BODY;

	p_tx_buff[msg_tx_len++] = p_args[0];
	p_tx_buff[msg_tx_len++] = p_args[1];

	tmp = 0;
	TRACE_INFO("MsgHandleAttStepAdj_SYS_A_FLAG(%d).\r\n", p_args[0] );
	if ( 0x00 == p_args[0] )
	{
		fpga_att_adj_st.ab_flag = SYS_A_FLAG;
	}
	else if ( 0x01==p_args[0] )
	{
		fpga_att_adj_st.ab_flag = SYS_B_FLAG;
	}
	else if ( 0x02==p_args[0] )
	{
		fpga_att_adj_st.ab_flag = SYS_C_FLAG;
	}
	else if ( 0x03==p_args[0] )
	{
		fpga_att_adj_st.ab_flag = SYS_D_FLAG;
	}
	else 
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_VALUE;
		SendMsgPkt(msg_tx_len, p_tx_buff);
		return;
	}

	fpga_att_adj_st.adj_st = ATT_ADJ_ST_STEP_ADJ;
	fpga_att_adj_st.is_wait = 0;
	fpga_att_adj_st.att_no = 0;
	fpga_att_adj_st.step = 0;
	
	if ( 0==p_args[1] )
	{
		// 上行输出
		fpga_att_adj_st.ud_flag=ATT_UL_ADJ;
		p_tx_buff[msg_tx_len++] = 1;		// 输出只有1个衰减器
	}
	else
	{
		// 下行输入
		fpga_att_adj_st.ud_flag=ATT_DL_ADJ;
		p_tx_buff[msg_tx_len++] = 1;		// 输入有1个衰减器
	}
	
	FpgaMakeAttAdjMsgHead( msg_tx_len, p_tx_buff );

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	
//	TRACE_INFO("MsgHandleAttStepAdj1.\r\n" );
	sys_work_info |= SYSTEM_FLAG_ATT_ADJ;
	
}

/*************************************************************
Name: MsgHandleAttStepAdj          
Description: 消息包命令:步进校准
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleEndAttAdj( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 ab_flag;
	UINT32 tmp;
	TRACE_INFO("MsgHandleEndAttAdj!\r\n");
	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_CMD_BODY;
	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;

	//OpenDA_B();

	if ( 0x00 == p_args[0] )
	{
		FpgaExitAttAdjMode( SYS_A_FLAG );
	}
	else if ( 0x01 == p_args[0] )
	{
		FpgaExitAttAdjMode( SYS_B_FLAG );
	}
	else if ( 0x02 == p_args[0] )
	{
		FpgaExitAttAdjMode( SYS_C_FLAG );
	}
	else if ( 0x03 == p_args[0] )
	{
		FpgaExitAttAdjMode( SYS_D_FLAG );
	}	
	else 
	{
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_VALUE;
		
	}


	

	SendMsgPkt(msg_tx_len, p_tx_buff);

}
/*************************************************************
Name: MsgHandleNoiseTest          
Description: 消息包命令:底噪测试
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleNoiseTest( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 ab_flag;
	UINT32 tmp;
	TRACE_INFO("MsgHandleNoiseTest!\r\n");
	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_CMD_BODY;
	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;

	noise_test_st.test_mode = p_args[0];
	noise_test_st.mcu_control = p_args[1];
	noise_test_st.type = p_args[2];
	noise_test_st.value= p_args[3];
	//printf("9363_0x17_01 = %02x,\r\n",ReadWriteTF(TF_B,0,0x0017,0) );

	WTD_CLR;	
	//噪声测试
	NoiseTest();
	//printf("9363_0x17_02 = %02x,\r\n",ReadWriteTF(TF_B,0,0x0017,0) );

	//SendMsgPkt(msg_tx_len, p_tx_buff);

}

/*************************************************************
Name: MsgHandleFcScan          
Description: 消息包命令:步进校准
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleFcScan( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT32 msg_tx_len;
	UCHAR8 * p_args;
	UINT16 fc;
	UCHAR8 cmd_mode;
	UCHAR8 rcv_code;
	UINT16 time_out;
	UCHAR8 force_run = 0;

	TRACE_INFO("Message Handle Scan Fc!\r\n");

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_CMD_BODY;
	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
#ifdef FUNC_FREQ_POINT_SEARCH_EN		// 启用频点搜索功能
	cmd_mode = p_args[0]&0x7F;

	if ( 3==cmd_mode )	// 查询自动搜索状态
	{
		p_tx_buff[msg_tx_len++] = p_args[0];
		p_tx_buff[msg_tx_len++] = p_args[1];
		msg_tx_len += FPS_GetAutoScanStaus(p_tx_buff+msg_tx_len);
	}
	else
	{
		force_run = (0==(p_args[0]&0x80)) ? 0 : 1;
		rcv_code = p_args[1];
		p_args += 2;
		FPS_MakeAckMsgHead( cmd_mode, rcv_code, msg_tx_len, p_tx_buff );		// 保存应答消息的包头数据
		p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_ERR_VALUE;

		if ( 1==cmd_mode )	// 手动BCCH搜索
		{
			time_out = p_args[0]|((UINT16)p_args[1]<<8);
			FPS_ManualStartBcch( force_run, time_out );
			return;
		}
		else if ( 2==cmd_mode )	// 手动TCH搜索
		{
			fc = p_args[0]|((UINT16)p_args[1]<<8);
			p_args+=2;
			time_out = p_args[0]|((UINT16)p_args[1]<<8);
			FPS_ManualStartTch( fc, force_run, time_out );
			return;
		}
	}
	
#endif
	SendMsgPkt(msg_tx_len, p_tx_buff);
	
}


/*************************************************************
Name: MsgHandleGainAdj          
Description: 消息包命令:增益校准
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleGainAdj( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT16 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 cmd2;

	msg_tx_len = MSG_PKT_HEAD_SIZE;
	p_args = p_msg_dat+MSG_CMD_BODY;

	cmd2 = p_args[0];//子命令	
	p_tx_buff[msg_tx_len++] = p_args[0];
	switch(cmd2)
	{
		case GAIN_ADJ_CMD2_ENTER_ADJ_MODE:
			msg_tx_len +=GianAdjustEnterAdjMode(msg_length-11,p_args+1,p_tx_buff+11);
			break;
		case GAIN_ADJ_CMD2_START_ADJ:
			msg_tx_len +=GianAdjustStartAdj(msg_length-11,p_args+1,p_tx_buff+11);
			break;
		case GAIN_ADJ_CMD2_GET_ADJ_STATUS:
			msg_tx_len +=GianAdjustGetAdjStatus(msg_length-11,p_args+1,p_tx_buff+11);
			break;
		case GAIN_ADJ_CMD2_GET_ADJ_DATA:
			msg_tx_len +=GianAdjustGetAdjData(msg_length-11,p_args+1,p_tx_buff+11);
			break;
	}

	p_tx_buff[MSG_ACK_FLAG] = MSG_ACK_CMD_OK;
	SendMsgPkt(msg_tx_len, p_tx_buff);
	
}


/*************************************************************
Name: MsgHandleGainAdjEUAck          
Description: 消息包命令:增益校准
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleGainAdjEUAck( UINT16 msg_length, UCHAR8 * p_msg_dat )
{
	UINT16 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 status;
	UCHAR8 abcd,ud,channel;
	UINT16 fre_point;
	UINT32 pow = 0;
	

	p_args = p_msg_dat+MSG_CMD_BODY;

	status = p_args[0];//AU传递状态给EU  EU进行同步操作
	switch(status)
	{
		case GAIN_ADJ_ST_SET_AUEU_ADJ_MODE:	
			abcd = p_args[1];
			//GainAdjSetEUEnterAdjMode(abcd);
			gain_adj_st.is_wait = 0;
			
			break;
		case GAIN_ADJ_ST_SET_AUEU_FRE:
			abcd = p_args[1];
			fre_point = p_args[2]|(p_args[3]<<8);			
			//GainAdjSetEUFrePoint(p_args[1],fre_point);
			gain_adj_st.is_wait = 0;

			break;
		case GAIN_ADJ_ST_GET_EU_SF_POW:
			abcd = p_args[1];
			ud = p_args[2];
			//pow = GainAdjGetEUPow(abcd,ud);
			gain_adj_st.is_wait = 0;
			att_adj_buff[ gain_adj_st.dat_len++] = p_args[3];
			att_adj_buff[ gain_adj_st.dat_len++] = p_args[4];
			att_adj_buff[ gain_adj_st.dat_len++] = p_args[5];
			att_adj_buff[ gain_adj_st.dat_len++] = p_args[6];
		
			break;
		
	}

	
}




/*************************************************************
Name: MsgHandleErrAlarm          
Description: 消息包命令:处理错误告警相关命令
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleErrAlarm( UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT16 msg_tx_len;
	UCHAR8 * p_args;
	UCHAR8 status;
	UCHAR8 abcd,ud,channel;
	UINT16 fre_point;
	UINT32 pow = 0;
	UCHAR8 cmd1 = 0,cmd2 = 0, cmd3 = 0;
	

	p_args = p_msg_dat+MSG_CMD_BODY;

	cmd1 = p_args[0];//AU传递状态给EU  EU进行同步操作
	switch(cmd1)
	{
		case ALARM_CLAER:
			//printf("清除告警\r\n");
			sys_param_1b[MADD_WORK_ERROR].val = 0;
			sys_param_1b[MADD_HOST_DEVICE_LINK_SINGNAL_ALARM].val  = 0;
			sys_param_1b[MADD_BATTERY_BREAKDOWN_ALARM].val = 0;
			sys_param_eu_1b[MADD_EU_ALARM_FLAG1].val = 0;
			sys_param_eu_1b[MADD_EU_ALARM_FLAG2].val = 0;
			sys_param_eu_1b[MADD_EU_ALARM_FLAG3].val = 0;
			sys_param_eu_1b[MADD_EU_ALARM_FLAG4].val = 0;
			sys_param_eu_1b[MADD_EU_ALARM_FLAG5].val = 0;
			sys_param_eu_1b[MADD_EU_ALARM_FLAG6].val = 0;
			sys_param_eu_1b[MADD_EU_ALARM_FLAG7].val = 0;
			sys_param_eu_1b[MADD_EU_ALARM_FLAG8].val = 0;
			
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG1].val = 0;
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG2].val = 0;
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG3].val = 0;
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG4].val = 0;
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG5].val = 0;
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG6].val = 0;
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG7].val = 0;
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG8].val = 0;
			 topo_err_count = 0;
			 topo_ok_count = 0;
			memset( (UCHAR8*)topo_alarm, 0, sizeof(topo_alarm) );
			
			break;
		case ALARM_GET_STATUS1:
			break;
		
	}

	
}

/*************************************************************
Name: MsgHandleAck          
Description: 处理应答包
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleAck( UINT16 msg_length, UCHAR8 * p_msg_dat )
{
	UCHAR8 src_fp, src_re,src_ree,i;
	UCHAR8 * p_args;
	UINT32 tmp,len = 0;
//	TRACE_INFO("p_args:[%02X]------------\r\n", p_args[i]);	
	TRACE_INFO("Msg Handle Ack-------------------1");



	if ( MSG_ACK_CMD_OK != p_msg_dat[MSG_ACK_FLAG] )
	{ 
		// 命令执行错误
		TRACE_INFO_WP("Err.");
		return; 
	} 

	TRACE_INFO("Msg Handle Ack[%02X:%02X:%02X]->[%02X:%02X:%02X],cmd=%02X,p_msg_dat[MSG_RESERVE1]=%02X,p_msg_dat[MSG_RESERVE2]=%02X.\r\n", 
	p_msg_dat[MSG_SRC_FP], p_msg_dat[MSG_SRC_RE],p_msg_dat[MSG_SRC_REE], p_msg_dat[MSG_DES_FP], p_msg_dat[MSG_DES_RE],  p_msg_dat[MSG_DES_REE],p_msg_dat[MSG_CMD_ID],p_msg_dat[MSG_RESERVE1],p_msg_dat[MSG_RESERVE2]);

	// 判断是否是485转发数据包
	if ( MSG_CMD_RE_REMOTE == p_msg_dat[MSG_CMD_ID] )
	{
		if ( (MSG_RE_TRANS_RECV_CODE1==p_msg_dat[MSG_RESERVE1]) && (MSG_RE_TRANS_RECV_CODE2==p_msg_dat[MSG_RESERVE2]) )
		{
			// 检查地址
			if ( (p_msg_dat[MSG_SRC_FP]==re_trans_fp) && (p_msg_dat[MSG_SRC_RE]==re_trans_node)&& (p_msg_dat[MSG_SRC_REE]==re_trans_rf)  )
			{
				// 发送485数据包，跳过前两个字节的子命令字和AB段标志
				UartReTransHandleAckMsg( p_msg_dat[MSG_ACK_FLAG], (p_msg_dat+MSG_CMD_BODY+2), (msg_length-MSG_PKT_HEAD_SIZE-2) );
				return;
			} 
		}
	}


	if (MSG_CMD_BLANK== p_msg_dat[MSG_CMD_ID] )
	{ 
		// 命令执行错误
			TRACE_INFO("return_of_MSG_CMD_BLANK_from_re.");
		return; 
	} 
	

	
	p_args = p_msg_dat+MSG_PKT_HEAD_SIZE;
	
	if ( MSG_CMD_GET_TOPO == p_msg_dat[MSG_CMD_ID] )
	{
		src_fp = p_msg_dat[MSG_SRC_FP]-1;
		src_re = p_msg_dat[MSG_SRC_RE]-1;
		src_ree = p_msg_dat[MSG_SRC_REE]-1;
		
		if (( src_fp<FP_MAX )&&( src_re<RE_MAX )) 
		{   
			len++;
			fp_inf[src_fp].re_info[src_re].rf_count=p_args[len++];
			fp_inf[src_fp].re_info[src_re].ree_sync_st_inf[0]=p_args[len++];
			fp_inf[src_fp].re_info[src_re].ree_sync_st_inf[1]=p_args[len++];
			fp_inf[src_fp].re_info[src_re].re_id=src_re+1;
//			TRACE_INFO("fp_inf[src_fp].re_info[src_re].ree_count(%d).",fp_inf[src_fp].re_info[src_re].rf_count);
//			TRACE_INFO("fp_inf[src_fp].re_info[src_re].ree_sync_st_inf[0](%d).",fp_inf[src_fp].re_info[src_re].ree_sync_st_inf[0]);
//			TRACE_INFO("fp_inf[src_fp].re_info[src_re].ree_sync_st_inf[1](%d).",fp_inf[src_fp].re_info[src_re].ree_sync_st_inf[1]);
//			TRACE_INFO("fp_inf[src_fp].re_info[src_re].re_id(%d).",fp_inf[src_fp].re_info[src_re].re_id);

#if 0			
		   	 tmp_re_inf[src_fp][src_re].flag = 1; 
			tmp_re_inf[src_fp][src_re].id = p_args[len++]; 
			tmp_re_inf[src_fp][src_re].status = p_args[len++];  
			tmp_re_inf[src_fp][src_re].re_t12 = p_args[len++]|(p_args[len++]<<8)|(p_args[len++]<<16)|(p_args[len++]<<24);
			tmp_re_inf[src_fp][src_re].ree_fp_stat =  p_args[len++]; // 4个连到RF的光口状态
			tmp_re_inf[src_fp][src_re].ree_nt_stat =  p_args[len++]; // 8个连到RF的网口口状态 
#endif
		}                     
	} 

	if ( MSG_CMD_GET_REE_INFO == p_msg_dat[MSG_CMD_ID] )
	{
		//TRACE_INFO("$$$$$$$$$$$$$$$$$$MSG_CMD_GET_REE_INFO.ACK\r\n");
		src_fp = p_msg_dat[MSG_SRC_FP]-1;
		src_re = p_msg_dat[MSG_SRC_RE]-1;
		src_ree = p_msg_dat[MSG_SRC_REE]-1;
		
		if (( src_fp<FP_MAX )&&( src_re<RE_MAX )) 
		{   
		    	tmp_re_inf[src_fp][src_re].flag = 1; 
			tmp_re_inf[src_fp][src_re].id = p_args[len++]; 
			tmp_re_inf[src_fp][src_re].status = p_args[len++];  
			tmp_re_inf[src_fp][src_re].re_t12 = p_args[len++]|(p_args[len++]<<8)|(p_args[len++]<<16)|(p_args[len++]<<24);
			tmp_re_inf[src_fp][src_re].ree_nt_stat =  p_args[len++]; // 8个连到RF的网口口状态 
			tmp_re_inf[src_fp][src_re].ree_fp_stat =  p_args[len++]; // 8个连到RF的光口状态
			tmp_re_inf[src_fp][src_re].ree_work_status=p_args[len++]|(p_args[len++]<<8);

			TRACE_INFO("[src_fp (%d).src_re (%d)\r\n",src_fp ,src_re);
			TRACE_INFO("RE.id (%d)\r\n",tmp_re_inf[src_fp][src_re].id);
			TRACE_INFO("tmp_re_inf[src_fp][src_re].status(%d).\r\n",tmp_re_inf[src_fp][src_re].status);
			TRACE_INFO("tmp_re_inf[src_fp][src_re].ree_nt_stat(%d).\r\n",tmp_re_inf[src_fp][src_re].ree_nt_stat);
			TRACE_INFO("tmp_re_inf[src_fp][src_re].ree_fp_stat(%d)\r\n.",tmp_re_inf[src_fp][src_re].ree_fp_stat);
			TRACE_INFO("tmp_re_inf[src_fp][src_re].ree_work_status(%d)\r\n.",tmp_re_inf[src_fp][src_re].ree_work_status);

//			TRACE_INFO("\r\n.");
		}  
		

	}
	
	if ( MSG_CMD_GET_FPGA_REG == p_msg_dat[MSG_CMD_ID] )
	{
		if (( 0xE7==p_msg_dat[MSG_RESERVE1] )&&( 0x11==p_msg_dat[MSG_RESERVE2] ))
		{
			FpgaHandlePsfAck( p_msg_dat+MSG_CMD_BODY );
		}
	}
	
	switch(p_msg_dat[MSG_CMD_ID])
	{
		case MSG_CMD_GAIN_ADJ:
			MsgHandleGainAdjEUAck(msg_length,p_msg_dat);
			break;
		case MSG_CMD_GET_PARAM:
			MsgHandleGetEUParam(msg_length,p_msg_dat);
			
		break;
	}
}

/*************************************************************
Name: MsgHandleGetReParam          
Description: 处理re应答包
Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void MsgHandleGetEUParam( UINT16 msg_length, UCHAR8 * p_msg_dat )
{
	UINT32 i,j,k;
	UINT32 len;
	UINT16 addr, mo_addr;
	UINT32 val;
	static unsigned char b_busy_time_count;		// 上行时隙
	static unsigned char a_busy_time_count;		// 上行时隙	
	UCHAR8 src_fp, src_re,src_ree;
	UCHAR8 des_fp, des_re,des_ree;

	src_fp = p_msg_dat[MSG_SRC_FP];
	src_re = p_msg_dat[MSG_SRC_RE];
	src_ree= p_msg_dat[MSG_SRC_REE];
	des_fp = p_msg_dat[MSG_DES_FP];
	des_re = p_msg_dat[MSG_DES_RE];
	des_ree= p_msg_dat[MSG_DES_REE];
	
	TRACE_INFO(" MSG_CMD_GET_PARAM Ack---2 \r\n"); 	
//	printf("接收");
//	for(i=0;i<msg_length;i++)
//	{
//		TRACE_INFO_WP("%d,%x --",i,p_msg_dat[i]); 	
//		printf("%x ",p_msg_dat[i]); 	
//	}
//	printf(" \r\n");
	TRACE_INFO(" \r\n"); 		
	for ( i=MSG_CMD_BODY; (i+3)<msg_length; )
	{
		// 读取参数地址   
		addr = p_msg_dat[i+0]|(p_msg_dat[i+1]<<8);
		// 读取参数长度    
		len = p_msg_dat[i+2];
		mo_addr = addr;
		
		WTD_CLR;
//		TRACE_INFO(" MsgHandleAck---i=[%d],len=[%x],mo_addr=[%x] \r\n",i,len,mo_addr); 			
		i+=3;	
		
		if ( 1 == len )
		{

			if((MADD_WORK_ERROR==mo_addr))
			{
				mo_addr= MADD_EU_ALARM_FLAG1;
				
			}
				
			else
			{
				//if(mo_addr>=SYS_PARAM_1B_COUNT)
				//{
				//	return;
				//}
				// 获取1字节参数
				//sys_param_1b[mo_addr+src_ree-1].val = p_msg_dat[i++];

				goto AddLen;			
			}	

			if(mo_addr+src_fp-1>=SYS_PARAM_EU_1B_COUNT)
			{
				return;
			}
			sys_param_eu_1b[mo_addr+src_fp-1].val=  p_msg_dat[i++];

		}
		else if ( 2 == len )
		{
			
			if( MADD_A_RE_LOCAL_ST_ALARM == mo_addr)
			{
				TRACE_INFO("MADD_A_RE_LOCAL_ST_ALARM\r\n");
				mo_addr= MADD_EU_RUALARM_FLAG1;
			}
				
			else
			{
				
				//if(mo_addr>=SYS_PARAM_2B_COUNT)
				//{
				//	return;
				//}
				//sys_param_2b[mo_addr+src_fp-1].val=(p_msg_dat[i++]|( (p_msg_dat[i++]<<8)&0xff00 ));
				goto AddLen;
			}
			if(mo_addr+src_ree-1>=SYS_PARAM_EU_2B_COUNT)
			{
				return;
			}
			sys_param_eu_2b[mo_addr+src_fp-1].val=(p_msg_dat[i++]|( (p_msg_dat[i++]<<8)&0xff00 ));
		}
		else if (len<PARAM_ASC_MAX_LEN )
		{
			return;
	
		}
		else
		{
			return;
		}

AddLen:

		//i+=len;

	}

	topo_alarm[src_fp-1][src_re-1].meu_alarm = sys_param_eu_1b[MADD_EU_ALARM_FLAG1+src_fp-1].val;
	topo_alarm[src_fp-1][src_re-1].ru_alarm = sys_param_eu_2b[MADD_EU_RUALARM_FLAG1+src_fp-1].val;
	//topo_alarm[src_fp-1][src_re-1].ru_alarm[1] = sys_param_eu_1b[MADD_EU_RUALARM_FLAG2+src_fp-1];
	//topo_alarm[src_fp-1][src_re-1].ru_alarm[2] = sys_param_eu_1b[MADD_EU_RUALARM_FLAG3+src_fp-1];
	//topo_alarm[src_fp-1][src_re-1].ru_alarm[3] = sys_param_eu_1b[MADD_EU_RUALARM_FLAG4+src_fp-1];
	//topo_alarm[src_fp-1][src_re-1].ru_alarm[4] = sys_param_eu_1b[MADD_EU_RUALARM_FLAG5+src_fp-1];
	//topo_alarm[src_fp-1][src_re-1].ru_alarm[5] = sys_param_eu_1b[MADD_EU_RUALARM_FLAG6+src_fp-1];
	//topo_alarm[src_fp-1][src_re-1].ru_alarm[6] = sys_param_eu_1b[MADD_EU_RUALARM_FLAG7+src_fp-1];
	//topo_alarm[src_fp-1][src_re-1].ru_alarm[7] = sys_param_eu_1b[MADD_EU_RUALARM_FLAG8+src_fp-1];
	//RefleshReParam();
}

#if 0
void MsgHandleAck( UINT16 msg_length, UCHAR8 * p_msg_dat )
{
	UCHAR8 src_fp, src_re;
	UCHAR8 * p_args;
	UINT32 tmp;
	
	TRACE_INFO("Msg Handle Ack!");

#if (!(defined(HXCT_VER) || defined( GUORENSOFT)))	// 非虹信特殊485协议或国人特殊485协议
	// 判断是否是485转发数据包
	if ( MSG_CMD_RE_REMOTE == p_msg_dat[MSG_CMD_ID] )
	{
		if ( (MSG_RE_TRANS_RECV_CODE1==p_msg_dat[MSG_RESERVE1]) && (MSG_RE_TRANS_RECV_CODE2==p_msg_dat[MSG_RESERVE2]) )
		{
			// 检查地址
			if ( (p_msg_dat[MSG_SRC_FP]==re_trans_fp) && (p_msg_dat[MSG_SRC_RE]==re_trans_node) )
			{
				// 发送485数据包，跳过前两个字节的子命令字和AB段标志
				UartReTransHandleAckMsg( p_msg_dat[MSG_ACK_FLAG], (p_msg_dat+MSG_CMD_BODY+2), (msg_length-MSG_PKT_HEAD_SIZE-2) );
				return;
			}
		}
	}
#endif

	if ( MSG_ACK_CMD_OK != p_msg_dat[MSG_ACK_FLAG] )
	{
		// 命令执行错误
		TRACE_INFO_WP("Err.");
		return;
	}
	
	p_args = p_msg_dat+MSG_PKT_HEAD_SIZE;

	if ( MSG_CMD_GET_REE_INFO == p_msg_dat[MSG_CMD_ID] )
	{
		src_fp = p_msg_dat[MSG_SRC_FP]-1;
		src_re = p_msg_dat[MSG_SRC_RE]-1;
		if (( src_fp<FP_MAX )&&( src_re<RE_MAX ))
		{
			tmp_re_inf[src_fp][src_re].id = p_args[0];
			tmp_re_inf[src_fp][src_re].status = p_args[1];
			tmp_re_inf[src_fp][src_re].flag = 1;
			tmp_re_inf[src_fp][src_re].re_t12 = p_args[2]|(p_args[3]<<8)|(p_args[4]<<16)|(p_args[5]<<24);
		}
	}

	if ( MSG_CMD_GET_FPGA_REG == p_msg_dat[MSG_CMD_ID] )
	{
		if (( 0xE7==p_msg_dat[MSG_RESERVE1] )&&( 0x11==p_msg_dat[MSG_RESERVE2] ))
		{
			FpgaHandlePsfAck( p_msg_dat+MSG_CMD_BODY );
		}
	}
	TRACE_INFO_WP("\r\n");

}
#endif

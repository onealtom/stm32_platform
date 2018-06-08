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
#include <stdio.h>


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
			
			case MSG_CMD_BLANK:
				MsgHandleBlankCmd( msg_len, p_msg_dat, msg_tx_buff );
				break;
			case MSG_CMD_PROMTP:
				printf("MSG_CMD_PROMTP\r\n");
				MsgHandlePromtp( msg_len, p_msg_dat, msg_tx_buff );
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

	msg_tx_len = MSG_CMD_BODY;

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
			//CmdHandleSpiWrite(TF_A,reg_add,tmp);
			break;

		case DEV_ID_B_AD9363:
			FPGA_ENABLE_WRITE;
			printf("<W IC>9363_B.(CHAR8)reg_add=[%02x], tmp=[%08x]\r\n",(CHAR8)reg_add, tmp);
			CMB_SPIWriteByte(NULL, reg_add, (uint8_t )tmp );
			FPGA_DISABLE_WRITE;
			break;
			
		case DEV_ID_C_AD9363:
			TRACE_INFO_WP("<W IC>9363_C.(CHAR8)reg_add=[%02x], tmp=[%08x]\r\n",(CHAR8)reg_add, tmp);
			//CmdHandleSpiWrite(TF_C,reg_add,tmp);
			
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
				FPGA_ENABLE_WRITE;
				CMB_SPIReadByte(NULL , reg_add , &tmp);
				printf("%08X=%08X\r\n", reg_add, tmp );
				FPGA_DISABLE_WRITE;
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
	////if ( b_TRUE==FpgaIsEnableA() )	output_st |= 0x01;
	////if ( b_TRUE==FpgaIsEnableB() )	output_st |= 0x02;
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
				////UartReTransHandleAckMsg( p_msg_dat[MSG_ACK_FLAG], (p_msg_dat+MSG_CMD_BODY+2), (msg_length-MSG_PKT_HEAD_SIZE-2) );
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

}

int MsgHandlePromtp(UINT16 msg_length, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff)
{
	UINT32 i=0;
	UCHAR8 ret_val = 0;
	UINT32 msg_tx_len;
	char * p;
	int len ;
	
	len = p_msg_dat[10];
	
	//printf("\rlen=%d\r\n",len);
	
	p=(char *)malloc(p_msg_dat[10]+1);
	//p=(char *)malloc(512);
	if(p==NULL){
		printf("malloc error\r\n");
		return -1;
	}
	
	for(i=0;i<p_msg_dat[10];i++){
		p[i]=(char)p_msg_dat[i+11];
		printf("%c",p[i]);
	}
	p[p_msg_dat[10]+1-1]='\0';
	
	command_process(p);
	
	ret_val = MSG_ACK_CMD_OK;
	p_tx_buff[MSG_ACK_FLAG] = ret_val;
	SendMsgPkt(msg_tx_len, p_tx_buff);
	
	free(p);
	
WTD_CLR;

}
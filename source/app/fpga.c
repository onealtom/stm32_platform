/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :fpga.c
* Description :FPGA处理相关函数
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			初始版本
**************************************************************/
#include "Header.h"

extern _T_PARAM_2B sys_param_2b[];
extern UCHAR8      sys_temp_buff[SYS_TMP_BUFF_SIZE];
extern _T_FP_INFO  fp_inf[FP_MAX];
extern _T_BIG_PKT_BUFF msg_big_buff[MSG_BIG_PKT_COUNT];
extern UCHAR8 msg_buff[FP_MAX][FPGA_MSG_BUFF_SIZE];		// 小消息包缓冲
extern UINT32 re_msg_buff_st[FP_MAX];
extern UINT32 module_param_chg_flag;		//系统工作参数修改标志
extern UINT32 bit_err_cnt; 
extern UINT32 fpga_rx_pkt_cnt;   
extern UCHAR8 benzhen2340;

UCHAR8 str_fpga_check_err[]="Fpga Data Bus Check Error!";
UCHAR8 str_fpga_prog_err[] ="Fpga Program Error!";

UCHAR8 fpga_load_block;		// Fpga加载区块
UINT32 fpga_load_status; 
UINT16 fpga_wo_reg[FPGA_WO_REG_COUNT]={0};
UCHAR8 att_adj_buff[20+2*64*4];
_T_ATT_ADJ_ST fpga_att_adj_st;
_T_ATT_ADJ_ST gain_adj_st;

_T_FPGA_CFG fpga_cfg;

FLOAT32 fpga_dginp_a=0;
FLOAT32 fpga_dgcic_a=0;
FLOAT32 fpga_uginp_a=0;
FLOAT32 fpga_ugcic_a=0;

FLOAT32 fpga_dginp_b=0;
FLOAT32 fpga_dgcic_b=0;
FLOAT32 fpga_uginp_b=0;
FLOAT32 fpga_ugcic_b=0; 

FLOAT32 fpga_dginp_c=0;
FLOAT32 fpga_dgcic_c=0;
FLOAT32 fpga_uginp_c=0;
FLOAT32 fpga_ugcic_c=0;

FLOAT32 fpga_dginp_d=0;
FLOAT32 fpga_dgcic_d=0;
FLOAT32 fpga_uginp_d=0;
FLOAT32 fpga_ugcic_d=0;

UINT16 fpga_a_regbk[MAX_CHANNEL_COUNT*2+2];	// 备份写入寄存器ginp+gcic+{下行增益,上行增益}x ch_count 
UINT16 fpga_b_regbk[MAX_CHANNEL_COUNT*2+2];	// 备份写入寄存器ginp+gcic+{下行增益,上行增益}x ch_count

UINT16 fpga_c_regbk[MAX_CHANNEL_COUNT*2+2];	// 备份写入寄存器ginp+gcic+{下行增益,上行增益}x ch_count 
UINT16 fpga_d_regbk[MAX_CHANNEL_COUNT*2+2];	// 备份写入寄存器ginp+gcic+{下行增益,上行增益}x ch_count

//UINT16 fpga_write_bak[FPGA_W_REG_MAX];


/*************************************************************
Name:        FpgaSetErrInfo
Description: 在Fpga水印信息中填充错误信息
Input:
	      err_id: 错误id 
Output:void          
Return:void
**************************************************************/
void FpgaSetErrInfo( UCHAR8 err_id )
{
	switch(err_id)
	{
		case FPGA_ERR_PROG:			// 加载错误
			sys_param_asc[MADD_PRI_FPGA_DATE].length = sizeof(str_fpga_prog_err);
			sys_param_asc[MADD_PRI_FPGA_DATE].p_asc = str_fpga_prog_err;
		break;
			
		case FPGA_ERR_CHECK:		// 校验错误
			sys_param_asc[MADD_PRI_FPGA_DATE].length = sizeof(str_fpga_check_err);
			sys_param_asc[MADD_PRI_FPGA_DATE].p_asc = str_fpga_check_err;
		break;
		
	}
}
#ifdef FPGA_MSG_ADD_ADDRESS
/*************************************************************
Name:           FpgaSendMsgPkt
Description:    通过FPGA向光口的RE发送数据
Input:
		  des_add: 接收数据包的地址，高8位表示光口号，低8位表示RE序号
  		  src_add: 发送数据包的地址，高8位表示光口号，低8位表示RE序号
  		  length:  数据包字节长度
  		  p_msg_dat: 只是数据缓冲的指针
  		  
Output:        void          
Return:        void
**************************************************************/
void FpgaSendMsgPkt( UINT32 des_add, UINT32 src_add, UINT32 length, UCHAR8 * p_msg_dat )
{
	UCHAR8 des_fp, des_re, des_ree;	
	UCHAR8 src_fp, src_re,src_ree;
//	UCHAR8 src_fp, src_re;
//	UINT16 fp_mask;
	UINT16 i, len;
	UCHAR8 frame_no = 0;
	UCHAR8 des_fp_tx, des_re_tx, des_ree_tx;
	UCHAR8 src_fp_tx, src_re_tx,src_ree_tx;

	UINT32 tx_count = 0;

	WTD_CLR;

	if (( FPGA_LDST_OK != fpga_load_status )||( length>MSG_BIG_PKT_SIZE ))
	{
		return;
	}

	des_fp_tx = p_msg_dat[MSG_DES_FP];
	des_re_tx = p_msg_dat[MSG_DES_RE];
	des_ree_tx = p_msg_dat[MSG_DES_REE];

	src_fp_tx = p_msg_dat[MSG_SRC_FP];
	src_re_tx = p_msg_dat[MSG_SRC_RE];
	src_ree_tx = p_msg_dat[MSG_SRC_REE];

	des_fp = (UCHAR8)((des_add>>16)&0xff);	// 高位表示光口号
	des_re = (UCHAR8)((des_add>>8)&0xff);		// 低位表示RE号
	des_ree = (UCHAR8)(des_add&0xff);		// 低位表示REe号

	
	src_fp = (UCHAR8)((src_add>>16)&0x00ff);	   // 高位表示光口号
	src_re = (UCHAR8)((src_add>>8)&0x00ff);		   // 低位表示RE号 
	src_ree = (UCHAR8)((src_add>>0)&0x00ff);		   // 低位表示Ree号

	TRACE_INFO("FpgaSendMsgPkt(%02x:%02x:%02x)-->des(%02x:%02x:%02x)\r\n" , src_fp,src_re,src_ree, des_fp,des_re,des_ree);
#if 0	
	if (    (  (des_fp>FP_MAX)&&(  (BROADCAST_ADD_FP!=des_fp)  || (BROADCAST_ADD_FP!=des_fp)  )   )
		||( (des_re>RE_MAX)&&(  (BROADCAST_ADD_RE!=des_re)  || (BROADCAST_ADD_FP!=des_fp)   )   )
		||(  (des_ree>REE_MAX)&& (  (BROADCAST_ADD_REE!=des_ree)  || (BROADCAST_ADD_FP!=des_fp)   )  )
		)
	{
		return;
	}
#endif

	FPGA_ENABLE_WRITE;

	// 写入要操作的光口号
	FPGA_SET_OPT(des_fp);
//	TRACE_INFO_WP("fp%d.", des_fp);

	while ( tx_count<=MSG_BIG_PKT_SIZE )
	{
//		TRACE_INFO_WP("fpga tx2.");
		// 等待发送缓冲空闲
		i = 0;
		while ( 0 == ( (1<<des_fp)&FpgaReadRegister(FPGA_REG_MSG_TX_READY) ) )
		{
			//TRACE_INFO_WP(".");
			UsNopDelay(50);
			if ( ++i > 10 )
			{
				TRACE_INFO_WP("time out!");
				FPGA_DISABLE_WRITE;
				return; 
			}
		}
		
		// 分包，判断是否是最后一个数据帧
		if(frame_no==0)
		{
			if ( length <= FPGA_MSG_FRAME_LEN )
			{
				frame_no |= MSG_FRAME_END_FLAG;
				len = length;
			}
			else
			{
				len = FPGA_MSG_FRAME_LEN;
			}
		}
		else
		{
			if ( length <= (FPGA_MSG_FRAME_LEN-FPGA_MSG_ADDR_LEN) )
			{
				frame_no |= MSG_FRAME_END_FLAG;
				len = length;
			}
			else
			{
				len = (FPGA_MSG_FRAME_LEN-FPGA_MSG_ADDR_LEN);
			}
		}
		
		// 计算剩余数据长度
		length -= len;
		tx_count += len;
		
		// 写入消息包的地址信息
		FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, (des_add>>8)&0xffff );
		FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, (src_add>>8)&0xffff );
//		TRACE_INFO_WP( "\r\nDesAdd:%06X, SrcAdd:%06X, ", des_add, src_add );
		
		// 写入数据长度,包括1字节的帧序号 
		if((frame_no & MSG_FRAME_INDEX_MASK) == 0)
		{
			FpgaWriteRegister( FPGA_REG_W_MSG_LEN, len+1 );
		}
		else
		{
			FpgaWriteRegister( FPGA_REG_W_MSG_LEN, len+1+FPGA_MSG_ADDR_LEN );
		}
		TRACE_INFO_WP( "MsgLen:%d,\r\n ", len+1 );

		// 写入帧编号
		FpgaWriteRegister( FPGA_REG_W_MSG_DAT, frame_no );
//		TRACE_INFO_WP( "FrmIndex:%02X\r\n ", frame_no );

		//光纤发送从第二包数据开始添加目的地址、源地址。20141205 
		//第一包数据原来已添加。
		if ( (frame_no & MSG_FRAME_INDEX_MASK) != 0 )
		{//不是第一个包
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, des_fp_tx );
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, des_re_tx );
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, des_ree_tx );
			
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, src_fp_tx );
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, src_re_tx );
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, src_ree_tx );
		}

		// 写入消息数据
		for ( i=0; i<len; i++ )
		{
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, *p_msg_dat++ );
		}
		
		// 启动发送
		FpgaWriteRegister( FPGA_REG_MSG_START_SEND, 0x00 );
		TRACE_INFO_WP( "End.\r\n" );
		
		WTD_CLR;
		//数据帧序号累加
		if ( 0 == (frame_no & MSG_FRAME_END_FLAG) )
		{
			frame_no++;
		}
		else
		{
			break;
		}
	}

	TRACE_INFO_WP("ok.\r\n");
	FPGA_DISABLE_WRITE;

}
#else
/*************************************************************
Name:           FpgaSendMsgPkt
Description:    通过FPGA向光口的RE发送数据
Input:
		  des_add: 接收数据包的地址，高8位表示光口号，低8位表示RE序号
  		  src_add: 发送数据包的地址，高8位表示光口号，低8位表示RE序号
  		  length:  数据包字节长度
  		  p_msg_dat: 只是数据缓冲的指针
  		  
Output:        void          
Return:        void
**************************************************************/
void FpgaSendMsgPkt( UINT32 des_add, UINT32 src_add, UINT32 length, UCHAR8 * p_msg_dat )
{
	UCHAR8 des_fp, des_re, des_ree;
//	UCHAR8 src_fp, src_re;
//	UINT16 fp_mask;
	UINT16 i, len;
	UCHAR8 frame_no = 0;

	UINT32 tx_count = 0;

	WTD_CLR;

	if (( FPGA_LDST_OK != fpga_load_status )||( length>MSG_BIG_PKT_SIZE ))
	{
		return;
	}
//	TRACE_INFO_WP("des_add%d.", des_add);
	TRACE_INFO_WP("fpga tx1---------------------\r\n.");
//	if(p_msg_dat[MSG_CMD_ID] == MSG_CMD_GET_REE_INFO)
//	{
//		TRACE_INFO("1SendMsgPkt id =DB,p_msg_dat[ MSG_RESERVE1]=%02x.201310090921##############################################\r\n",p_msg_dat[ MSG_RESERVE1]);
//	}
//	fp_mask = 1<<( ((des_add>>8)&0x00ff) );
	des_fp = (UCHAR8)((des_add>>16)&0xff);	// 高位表示光口号
	des_re = (UCHAR8)((des_add>>8)&0xff);		// 低位表示RE号
	des_ree = (UCHAR8)(des_add&0xff);		// 低位表示REe号
//	TRACE_INFO("FpgaSendMsgPkt [%02X:%02X:%02X]->[%02X:%02X:%02X],cmd=%02X\r\n",*( p_msg_dat+3),*( p_msg_dat+4),*( p_msg_dat+5),des_fp,des_re,des_ree,p_msg_dat[MSG_CMD_ID] );
#if 0	
	if (    (  (des_fp>FP_MAX)&&(  (BROADCAST_ADD_FP!=des_fp)  || (BROADCAST_ADD_FP!=des_fp)  )   )
		||( (des_re>RE_MAX)&&(  (BROADCAST_ADD_RE!=des_re)  || (BROADCAST_ADD_FP!=des_fp)   )   )
		||(  (des_ree>REE_MAX)&& (  (BROADCAST_ADD_REE!=des_ree)  || (BROADCAST_ADD_FP!=des_fp)   )  )
		)
	{
		return;
	}
#endif

	FPGA_ENABLE_WRITE;

	// 写入要操作的光口号
	FPGA_SET_OPT(des_fp);
//	TRACE_INFO_WP("fp%d.", des_fp);

	while ( tx_count<=MSG_BIG_PKT_SIZE )
	{
//		TRACE_INFO_WP("fpga tx2.");
		// 等待发送缓冲空闲
		i = 0;
		while ( 0 == ( (1<<des_fp)&FpgaReadRegister(FPGA_REG_MSG_TX_READY) ) )
		{
			//TRACE_INFO_WP(".");
			UsNopDelay(50);
			if ( ++i > 10 )
			{
				TRACE_INFO_WP("time out!");
				FPGA_DISABLE_WRITE;
				return; 
			}
		}
		
		// 分包，判断是否是最后一个数据帧
		if ( length <= FPGA_MSG_FRAME_LEN )
		{
			frame_no |= MSG_FRAME_END_FLAG;
			len = length;
		}
		else
		{
			len = FPGA_MSG_FRAME_LEN;
		}
		
		// 计算剩余数据长度
		length -= len;
		tx_count += len;
		
		// 写入消息包的地址信息
		FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, (des_add>>8)&0xffff );
		FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, (src_add>>8)&0xffff );
//		TRACE_INFO_WP( "\r\nDesAdd:%06X, SrcAdd:%06X, ", des_add, src_add );
		
		// 写入数据长度
		FpgaWriteRegister( FPGA_REG_W_MSG_LEN, len+1 );
//		TRACE_INFO_WP( "MsgLen:%d, ", len+1 );

		// 写入帧编号
		FpgaWriteRegister( FPGA_REG_W_MSG_DAT, frame_no );
//		TRACE_INFO_WP( "FrmIndex:%02X\r\n ", frame_no );

		// 写入消息数据
		for ( i=0; i<len; i++ )
		{
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, *p_msg_dat++ );
		}
		
		// 启动发送
		FpgaWriteRegister( FPGA_REG_MSG_START_SEND, 0x00 );
		TRACE_INFO_WP( "End.\r\n" );
		
		WTD_CLR;
		//数据帧序号累加
		if ( 0 == (frame_no & MSG_FRAME_END_FLAG) )
		{
			frame_no++;
		}
		else
		{
			break;
		}
	}

	TRACE_INFO_WP("ok.\r\n");
	FPGA_DISABLE_WRITE;

}
#endif

#if 0
/*************************************************************
Name:FpgaSaveMsgDat
Description: 从光口数据FIFO读取数据，存入指定缓冲区
Input:
	len: 要读取的数据长度
	p_save_buff: 缓冲区地址
Output:void         
Return: 已保存的数据长度
**************************************************************/
INT16 FpgaSaveMsgDat( INT16 len, UCHAR8 *p_save_buff )
{
	INT16 i = 0;
	UCHAR8 tmp;

	if (( 0 != p_save_buff )&&( len <= FPGA_MSG_BUFF_SIZE ))
	{
		for ( i=0; i<len; i++ )
		{
			tmp = FpgaReadRegister( FPGA_REG_R_MSG_DAT );
			*p_save_buff++ = tmp;
		} 
	} 
	
	//TRACE_INFO_WP("save fpga rx_dat(%d).", len);
	
	return i;
}

/*************************************************************
Name:FpgaGetMsgPkt
Description: 通过FPGA向光口的RE发送数据
Input:
	des_add: 接收数据包的地址，高8位表示光口号，低8位表示RE序号
	src_add: 发送数据包的地址，高8位表示光口号，低8位表示RE序号
	length: 数据包字节长度
	p_msg_dat: 只是数据缓冲的指针
Output:void         
Return:void
**************************************************************/
void FpgaGetMsgPkt( void )
{
	UINT32 i,j,k;
	UINT32 tmp;
	UINT16 msg_fifo_st;
	static UCHAR8 des_fp, des_re;
	static UCHAR8 src_fp, src_re;
	INT16  frame_len;
	UCHAR8 frame_no;
	BOOL   msg_end_flag = b_FALSE;
	UINT32 msg_len;
	UCHAR8 *p_msg_dat = 0;

	WTD_CLR;
	
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA故障，返回
		return;    
	} 
 
	// 光口数据包接收FIFO状态,位对应,低8位1表示FIFO有数据,高8位1表示FIFO满 
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	// 按光口顺序处理数据包 
	for ( i=0; i<FP_MAX; i++ )
	{
		// 写入要操作的光口号
		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(i);
		FPGA_DISABLE_WRITE; 

		// 累计数据包错误计数 ，并清空对应寄存器
		bit_err_cnt += FpgaReadRegister(FPGA_REG_PKT_ERR_COUNT);
		FpgaReadRegister(FPGA_REG_CLEAR_PKT_ERR);
		
		// 判断光口是否有收到数据包
		if ( 0 != (msg_fifo_st & (0x0001<<i)) ) 
		{
			p_msg_dat = sys_temp_buff;
			
			for ( j=0; j<FPGA_FRAME_FIFO_SIZE; j++ )
			{
				*p_msg_dat++ = (UCHAR8)( 0x00FF & FpgaReadRegister( FPGA_REG_R_MSG_DAT ) );
			} 	   
	   		
	   		// 读取数据长度
	   		frame_len = sys_temp_buff[4];	 //TRACE_INFO("frame_len = %d\r\n",frame_len);  
	   		
	   		// 读取数据帧编号  
	   		frame_no = sys_temp_buff[5];	 // TRACE_INFO("frame_no = %02x\r\n",frame_no);

			if (( src_fp>FP_MAX )||( src_re>RE_MAX )||(0==frame_len)||(frame_len>FPGA_MSG_BUFF_SIZE)||
				((frame_no&MSG_FRAME_INDEX_MASK)>=MSG_MAX_FRAME_INDEX) )
			{
				// 切换FIFO页
				FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
				continue;
			}  
			
			frame_len--;	  // 长度减1,即为有效数据长度

			if ( 0 ==(frame_no & MSG_FRAME_INDEX_MASK) ) 
			{ 
				des_fp   = sys_temp_buff[6];
				des_re   = sys_temp_buff[7];
				src_fp   = sys_temp_buff[8];
				src_re   = sys_temp_buff[9];
			}       

			if ( 0 != (frame_no & MSG_FRAME_END_FLAG) )	// 最末帧
			{
				msg_end_flag = b_TRUE;
				
				frame_no &= MSG_FRAME_INDEX_MASK;	// 取得帧编号
				
				// 判断是否是大数据包
				if ( frame_no > 0 )
				{	
					// 大数据包，判断RE是否有大缓冲使用权
					tmp = GetReBigMsgBuffIndex( src_fp, src_re );
					
					if ( 0 == tmp ) 	// 该RE没有大缓冲的使用权
					{
						// 返回接收端未就绪的应答
						p_msg_dat = 0;
						MsgReceiverBusy( src_fp, src_re );
						continue;
					} 
					else
					{
						// 存入大数据缓冲
						tmp--;
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
						msg_len = frame_no * FPGA_MSG_FRAME_LEN + frame_len;
 					}
				}
				else
				{
					// 普通数据包，直接保存并处理
					p_msg_dat = msg_buff[i];
					msg_len = frame_len;
				}
			}
			else
			{
				// 不是最后的数据帧
				msg_end_flag = b_FALSE; 
				
				// 数据需要保存到大缓冲中，先判断RE有没有大缓冲的使用权
				tmp = GetReBigMsgBuffIndex( src_fp, src_re );
				
				if ( 0 == tmp )	 // RE没有大数据缓冲的使用权
				{  
					tmp = GetFreeBigBuffIndex();

					if ( 0 != tmp )	// 大数据缓冲空闲,将其分配给当前RE
					{
						tmp--;    
						
						msg_big_buff[tmp].owner = ((src_fp<<8)|src_re); 
						msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;

						 // 数据指针指向大数据缓冲    
						p_msg_dat = msg_big_buff[tmp].buff; 
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
					}
					else // 大数据缓冲被占用
					{
						// 返回接收端未就绪的应答
						p_msg_dat = 0;
						MsgReceiverBusy( src_fp, src_re );
						continue;
					} 
				}
				else
				{
					tmp--;
					msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;
					p_msg_dat = msg_big_buff[tmp].buff;
					p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
				} 
			}

			WTD_CLR; 

			for ( k=0; k<frame_len; k++ )
		    {
				*p_msg_dat++ = sys_temp_buff[k+6];  
 	
		    }
           
			// 切换FIFO页
			FpgaReadRegister( FPGA_REG_R_NEXT_MSG );

			if ( b_TRUE == msg_end_flag )
			{
				
				if ( frame_no>0 )
				{  
					 //TRACE_INFO_WP("handle big pkt\r\n");
					tmp = GetReBigMsgBuffIndex( src_fp, src_re );
					
					if ( tmp>0 )
					{
						tmp--;
						MsgHandle(msg_len, msg_big_buff[tmp].buff );
						msg_big_buff[tmp].owner = 0;		// 释放大数据缓冲资源
					}
				}
				else
				{ 
					//TRACE_INFO_WP("handle small pkt\r\n");
					MsgHandle( msg_len, msg_buff[i] );
				}  
				 
				fpga_rx_pkt_cnt++;
			}
			
		}
	}
	
}
#endif

/*************************************************************
Name:FpgaSaveMsgDat
Description: 从光口数据FIFO读取数据，存入指定缓冲区
Input:
	len: 要读取的数据长度
	p_save_buff: 缓冲区地址
Output:void         
Return: 已保存的数据长度
**************************************************************/
INT16 FpgaSaveMsgDat( INT16 len, UCHAR8 *p_save_buff )
{
	INT16 i = 0;
	UCHAR8 tmp;

	TRACE_INFO_WP("\r\n");
	if (( 0 != p_save_buff )&&( len <= FPGA_MSG_BUFF_SIZE ))
	{
		for ( i=0; i<len; i++ )
		{
			tmp = FpgaReadRegister( FPGA_REG_R_MSG_DAT );
			*p_save_buff++ = tmp;
			TRACE_INFO_WP("%02X ", tmp);
		}
	}
	
	TRACE_INFO_WP("save fpga rx_dat(%d).", len);
	
	return i;
}

#ifdef FPGA_MSG_ADD_ADDRESS
/*************************************************************
Name:FpgaGetMsgPkt
Description: 通过FPGA从光口的读取RE数据
Input:
	des_add: 接收数据包的地址，高8位表示光口号，低8位表示RE序号
	src_add: 发送数据包的地址，高8位表示光口号，低8位表示RE序号
	length: 数据包字节长度
	p_msg_dat: 只是数据缓冲的指针
Output:void         
Return:void
**************************************************************/
void FpgaGetMsgPkt( void )
{
	UINT32 i,j,k;
	UINT32 tmp;
	UINT16 msg_fifo_st;
	static UCHAR8 des_fp, des_re,des_ree;
	static UCHAR8 src_fp, src_re,src_ree;
	INT16  frame_len;
	UCHAR8 frame_no,frame_no1;
	BOOL   msg_end_flag = b_FALSE;
	UINT32 msg_len;
	UCHAR8 *p_msg_dat = 0;

	WTD_CLR;
	
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA故障，返回
		return;    
	} 
 
	// 光口数据包接收FIFO状态,位对应,低8位1表示FIFO有数据,高8位1表示FIFO满 
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	//TRACE_INFO_WP("fpga msg_fifo_st = %02x \r\n",msg_fifo_st); 
	
	// 按光口顺序处理数据包 
	for ( i=0; i<FP_MAX; i++ )
	{
		// 写入要操作的光口号
		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(i);
		FPGA_DISABLE_WRITE; 

		// 累计数据包错误计数 ，并清空对应寄存器
		bit_err_cnt += FpgaReadRegister(FPGA_REG_PKT_ERR_COUNT);
		FpgaReadRegister(FPGA_REG_CLEAR_PKT_ERR);
//		TRACE_INFO_WP("fpga rx1\n"); 
		// 判断光口是否有收到数据包
		if ( 0 != (msg_fifo_st & (0x0001<<i)) )
		{
			TRACE_INFO_WP("fpga rx2\n"); 
			p_msg_dat = sys_temp_buff;
			
			for ( j=0; j<FPGA_FRAME_FIFO_SIZE; j++ )
			{
				*p_msg_dat++ = (UCHAR8)( 0x00FF & FpgaReadRegister( FPGA_REG_R_MSG_DAT ) );
			} 

	   		// 读取数据长度
	   		frame_len = sys_temp_buff[4];	
	   		
	   		// 读取数据帧编号 
			frame_no = sys_temp_buff[5]; 
			frame_no1 = sys_temp_buff[5]; 

			des_fp   = sys_temp_buff[6];
			des_re   = sys_temp_buff[7];
			des_ree   = sys_temp_buff[8];

			src_fp   = sys_temp_buff[9];
			src_re   = sys_temp_buff[10];
			src_ree   = sys_temp_buff[11];

			TRACE_INFO("FpgaGetMsgPkt--(%02X:%02X:%02X->%02X:%02X:%02X-len=%d).", src_fp, src_re, src_ree, des_fp, des_re,des_ree, frame_len);
			
			if ((0==frame_len)||(frame_len>FPGA_MSG_BUFF_SIZE)||
				((frame_no&MSG_FRAME_INDEX_MASK)>=MSG_MAX_FRAME_INDEX) )
			{
				TRACE_INFO_WP("FpgaGetMsgPkt--Err(%02X:%02X->%02X:%02X-%d).", src_fp, src_re, des_fp, des_re, frame_len);
				// 切换FIFO页
				FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
				continue;
			} 
			
			//TRACE_INFO_WP( "(%d) fi(0x%02X).", frame_len, frame_no );

			frame_len--;	// 长度减1,即为有效数据长度   
			  			 
			if ( 0 != (frame_no & MSG_FRAME_END_FLAG) )	// 最末帧
			{
				msg_end_flag = b_TRUE;
				
				frame_no &= MSG_FRAME_INDEX_MASK;	// 取得帧编号
				
				// 判断是否是大数据包
				if ( frame_no > 0 )
				{	
					// 大数据包，判断RE是否有大缓冲使用权
					tmp = GetReBigMsgBuffIndex( src_fp, src_re,src_ree);
					
					if ( 0 == tmp ) 	// 该RE没有大缓冲的使用权
					{
						// 返回接收端未就绪的应答
						p_msg_dat = 0;
						//MsgReceiverBusy( src_fp, src_re,src_ree);
						continue;
					} 
					else
					{
						// 存入大数据缓冲
						tmp--;
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += (FPGA_MSG_FRAME_LEN+ (frame_no-1) * (FPGA_MSG_FRAME_LEN-FPGA_MSG_ADDR_LEN) );
						msg_len = FPGA_MSG_FRAME_LEN+((frame_no-1) * (FPGA_MSG_FRAME_LEN-FPGA_MSG_ADDR_LEN)) + (frame_len-FPGA_MSG_ADDR_LEN);
 					}
				}
				else
				{
					// 普通数据包，直接保存并处理
					p_msg_dat = msg_buff[i];
					msg_len   = frame_len;
				}
			}
			else
			{
				// 不是最后的数据帧
				msg_end_flag = b_FALSE; 
				
				// 数据需要保存到大缓冲中，先判断RE有没有大缓冲的使用权
				tmp = GetReBigMsgBuffIndex( src_fp, src_re,src_ree);
				
				if ( 0 == tmp )	 // RE没有大数据缓冲的使用权
				{  
					tmp = GetFreeBigBuffIndex();

					if ( 0 != tmp )	// 大数据缓冲空闲,将其分配给当前RE
					{
						tmp--;    
						
						msg_big_buff[tmp].owner = ((src_fp<<16)|(src_re<<8)|src_ree); 
						msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;

						 // 数据指针指向大数据缓冲    
						p_msg_dat = msg_big_buff[tmp].buff; 
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
					}
					else // 大数据缓冲被占用
					{
						// 返回接收端未就绪的应答
						p_msg_dat = 0;
						//MsgReceiverBusy( src_fp, src_re,src_ree);
						continue;
					} 
				}
				else
				{
					tmp--;
					msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;
					p_msg_dat = msg_big_buff[tmp].buff;
					if(frame_no>0)
						p_msg_dat += (FPGA_MSG_FRAME_LEN+ (frame_no-1) * (FPGA_MSG_FRAME_LEN-FPGA_MSG_ADDR_LEN) );
				} 
			} 

			WTD_CLR;
			
			//光纤发送每包数据都添加目的地址、源地址。20141205 
			//存储时只存储第一个包的源地址和目的地址
			if ( (frame_no1 & MSG_FRAME_END_FLAG) == 0 )
			{
				if ( (frame_no1 & MSG_FRAME_INDEX_MASK) == 0 )//第一个包
				{
					for ( k=0; k<frame_len; k++ )
					{
						//TRACE_INFO_WP("%d ",*p_msg_dat);
						*p_msg_dat++ = sys_temp_buff[k+6];//去掉包头
					}
				}
				else
				{
					for ( k=0; k<(frame_len-FPGA_MSG_ADDR_LEN); k++ )
					{
						//TRACE_INFO_WP("%d ",*p_msg_dat);
						*p_msg_dat++ = sys_temp_buff[k+6+FPGA_MSG_ADDR_LEN];//去掉包头
					}
				}
			}
			else
			{//最后一个包
					if ( (frame_no1 & MSG_FRAME_INDEX_MASK) == 0 )//第一个包
					{
						for ( k=0; k<frame_len; k++ )
						{
							//TRACE_INFO_WP("%d ",*p_msg_dat);
							*p_msg_dat++ = sys_temp_buff[k+6];//去掉包头
						}
					}
					else
					{
						for ( k=0; k<(frame_len-FPGA_MSG_ADDR_LEN); k++ )
						{
							//TRACE_INFO_WP("%d ",*p_msg_dat);
							*p_msg_dat++ = sys_temp_buff[k+6+FPGA_MSG_ADDR_LEN];//去掉包头
						}
				
					}
			}
			
			// 切换FIFO页 
			FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
			TRACE_INFO_WP("fpga rx3\n"); 
		//	TRACE_INFO_WP("msg_end_flag(%d)\n",msg_end_flag); 
			if ( b_TRUE == msg_end_flag )
			{
				//TRACE_INFO_WP("handle.");
				if ( frame_no>0 )
				{
					
					tmp = GetReBigMsgBuffIndex( src_fp, src_re,src_ree);
		//		TRACE_INFO_WP("GetReBigMsgBuffIndex(%d)\n",tmp); 				
					if ( tmp>0 )
					{
//						TRACE_INFO_WP("msg_big_buff(%d)\n",tmp); 
						tmp--;
						MsgHandle(src_fp, src_re, src_ree,msg_len, msg_big_buff[tmp].buff);
						msg_big_buff[tmp].owner = 0;		// 释放大数据缓冲资源
#if 0  				
							for(j=0;j<msg_len;j++)
							{
					
              						TRACE_INFO("msg_big_buff[i].buff[%d]=%d\r\n",j,msg_big_buff[i].buff[j]); 

							}
#endif							
							/****test*********///20121127

						
					}
				}
				else
				{
					MsgHandle(src_fp, src_re, src_ree,msg_len, msg_buff[i]);
//					MsgHandle( msg_len, msg_buff[i] );

							/****test*********///20121127
			//				TRACE_INFO_WP("msg_buff3\r\n");
#if 0  				
							for(j=0;j<msg_len;j++)
							{
					
              						TRACE_INFO("msg_buff2[%d]=%d\r\n",j,msg_buff[i][j]); 

							}
#endif							
							/****test*********///20121127
				}  
				
				fpga_rx_pkt_cnt++;
			}         
			
			
		}
	}
	
}

#else
/*************************************************************
Name:FpgaGetMsgPkt
Description: 通过FPGA从光口的读取RE数据
Input:
	des_add: 接收数据包的地址，高8位表示光口号，低8位表示RE序号
	src_add: 发送数据包的地址，高8位表示光口号，低8位表示RE序号
	length: 数据包字节长度
	p_msg_dat: 只是数据缓冲的指针
Output:void         
Return:void
**************************************************************/
void FpgaGetMsgPkt( void )
{
	UINT32 i,j,k;
	UINT32 tmp;
	UINT16 msg_fifo_st;
	static UCHAR8 des_fp, des_re,des_ree;
	static UCHAR8 src_fp[FP_MAX], src_re[FP_MAX],src_ree[FP_MAX];
	INT16  frame_len;
	UCHAR8 frame_no;
	BOOL   msg_end_flag = b_FALSE;
	UINT32 msg_len;
	UCHAR8 *p_msg_dat = 0;

	WTD_CLR;
	
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA故障，返回
		return;    
	} 
 
	// 光口数据包接收FIFO状态,位对应,低8位1表示FIFO有数据,高8位1表示FIFO满 
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	// 按光口顺序处理数据包 
	for ( i=0; i<FP_MAX; i++ )
	{
		// 写入要操作的光口号
		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(i);
		FPGA_DISABLE_WRITE; 

		// 累计数据包错误计数 ，并清空对应寄存器
		bit_err_cnt += FpgaReadRegister(FPGA_REG_PKT_ERR_COUNT);
		FpgaReadRegister(FPGA_REG_CLEAR_PKT_ERR);
//		TRACE_INFO_WP("fpga rx1\n"); 
		// 判断光口是否有收到数据包
		if ( 0 != (msg_fifo_st & (0x0001<<i)) )
		{
			TRACE_INFO_WP("fpga rx2\n"); 
			p_msg_dat = sys_temp_buff;
			
			for ( j=0; j<FPGA_FRAME_FIFO_SIZE; j++ )
			{
				*p_msg_dat++ = (UCHAR8)( 0x00FF & FpgaReadRegister( FPGA_REG_R_MSG_DAT ) );
			} 

	   		// 读取数据长度
	   		frame_len = sys_temp_buff[4];	
	   		
	   		// 读取数据帧编号 
	   		frame_no = sys_temp_buff[5]; 
			 
			if ( 0 ==(frame_no & MSG_FRAME_INDEX_MASK) )
			{
			//	TRACE_INFO("the fisrt data packet\r\n");
				
				des_fp   = sys_temp_buff[6];
				des_re   = sys_temp_buff[7];
	            des_ree   = sys_temp_buff[8];
				
				src_fp[i]   = sys_temp_buff[9];
				src_re[i]   = sys_temp_buff[10];
	           		 src_ree[i]   = sys_temp_buff[11];

				TRACE_INFO("FpgaGetMsgPkt--(%02X:%02X:%02X->%02X:%02X:%02X-len=%d).", src_fp[i], src_re[i], src_ree[i], des_fp, des_re,des_ree, frame_len);

			}  	
			
			if ((0==frame_len)||(frame_len>FPGA_MSG_BUFF_SIZE)||
				((frame_no&MSG_FRAME_INDEX_MASK)>=MSG_MAX_FRAME_INDEX) )
			{
				TRACE_INFO_WP("FpgaGetMsgPkt--Err(%02X:%02X->%02X:%02X-%d).", src_fp[i], src_re[i], des_fp, des_re, frame_len);
				// 切换FIFO页
				FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
				continue;
			} 
			
			//TRACE_INFO_WP( "(%d) fi(0x%02X).", frame_len, frame_no );

			frame_len--;	// 长度减1,即为有效数据长度   
			  			 
			if ( 0 != (frame_no & MSG_FRAME_END_FLAG) )	// 最末帧
			{
				msg_end_flag = b_TRUE;
				
				frame_no &= MSG_FRAME_INDEX_MASK;	// 取得帧编号
				
				// 判断是否是大数据包
				if ( frame_no > 0 )
				{	
					// 大数据包，判断RE是否有大缓冲使用权
					tmp = GetReBigMsgBuffIndex( src_fp[i], src_re[i],src_ree[i]);
					
					if ( 0 == tmp ) 	// 该RE没有大缓冲的使用权
					{
						// 返回接收端未就绪的应答
						p_msg_dat = 0;
						MsgReceiverBusy( src_fp[i], src_re[i],src_ree[i]);
						continue;
					} 
					else
					{
						// 存入大数据缓冲
						tmp--;
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
						msg_len = frame_no * FPGA_MSG_FRAME_LEN + frame_len;
 					}
				}
				else
				{
					// 普通数据包，直接保存并处理
					p_msg_dat = msg_buff[i];
					msg_len   = frame_len;
				}
			}
			else
			{
				// 不是最后的数据帧
				msg_end_flag = b_FALSE; 
				
				// 数据需要保存到大缓冲中，先判断RE有没有大缓冲的使用权
				tmp = GetReBigMsgBuffIndex( src_fp[i], src_re[i],src_ree[i]);
				
				if ( 0 == tmp )	 // RE没有大数据缓冲的使用权
				{  
					tmp = GetFreeBigBuffIndex();

					if ( 0 != tmp )	// 大数据缓冲空闲,将其分配给当前RE
					{
						tmp--;    
						
						msg_big_buff[tmp].owner = ((src_fp[i]<<16)|(src_re[i]<<8)|src_ree[i]); 
						msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;

						 // 数据指针指向大数据缓冲    
						p_msg_dat = msg_big_buff[tmp].buff; 
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
					}
					else // 大数据缓冲被占用
					{
						// 返回接收端未就绪的应答
						p_msg_dat = 0;
						MsgReceiverBusy( src_fp[i], src_re[i],src_ree[i]);
						continue;
					} 
				}
				else
				{
					tmp--;
					msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;
					p_msg_dat = msg_big_buff[tmp].buff;
					p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
				} 
			} 

			WTD_CLR;
			
			for ( k=0; k<frame_len; k++ )
			{
				*p_msg_dat++ = sys_temp_buff[k+6];
			}  
			
			// 切换FIFO页 
			FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
			TRACE_INFO_WP("fpga rx3\n"); 
		//	TRACE_INFO_WP("msg_end_flag(%d)\n",msg_end_flag); 
			if ( b_TRUE == msg_end_flag )
			{
				//TRACE_INFO_WP("handle.");
				if ( frame_no>0 )
				{
					
					tmp = GetReBigMsgBuffIndex( src_fp[i], src_re[i],src_ree[i]);
		//		TRACE_INFO_WP("GetReBigMsgBuffIndex(%d)\n",tmp); 				
					if ( tmp>0 )
					{
//						TRACE_INFO_WP("msg_big_buff(%d)\n",tmp); 
						tmp--;
						MsgHandle(src_fp[i], src_re[i], src_ree[i],msg_len, msg_big_buff[tmp].buff);
						msg_big_buff[tmp].owner = 0;		// 释放大数据缓冲资源
#if 0  				
							for(j=0;j<msg_len;j++)
							{
					
              						TRACE_INFO("msg_big_buff[i].buff[%d]=%d\r\n",j,msg_big_buff[i].buff[j]); 

							}
#endif							
							/****test*********///20121127

						
					}
				}
				else
				{
					MsgHandle(src_fp[i], src_re[i], src_ree[i],msg_len, msg_buff[i]);
//					MsgHandle( msg_len, msg_buff[i] );

							/****test*********///20121127
			//				TRACE_INFO_WP("msg_buff3\r\n");
#if 0  				
							for(j=0;j<msg_len;j++)
							{
					
              						TRACE_INFO("msg_buff2[%d]=%d\r\n",j,msg_buff[i][j]); 

							}
#endif							
							/****test*********///20121127
				}  
				
				fpga_rx_pkt_cnt++;
			}         
			
			
		}
	}
	
}
#endif

#if 0
/*************************************************************
Name:FpgaGetMsgPkt
Description: 通过FPGA向光口的RE发送数据
Input:
	des_add: 接收数据包的地址，高8位表示光口号，低8位表示RE序号
	src_add: 发送数据包的地址，高8位表示光口号，低8位表示RE序号
	length: 数据包字节长度
	p_msg_dat: 只是数据缓冲的指针
Output:void         
Return:void
**************************************************************/
void FpgaGetMsgPkt( void )
{
	UINT32 i,j;
	UINT32 tmp;
	UINT16 msg_fifo_st;
	UCHAR8 des_fp, des_re, des_ree;
	UCHAR8 src_fp, src_re, src_ree;
	INT16 frame_len;
	UCHAR8 frame_no;
	BOOL msg_end_flag = b_FALSE;
	UINT32 msg_len;
	UCHAR8 *p_msg_dat = 0;

	WTD_CLR;
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA故障，返回
		return;
	}

	// 读取数据包FIFO状态
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	// 按光口顺序处理数据包
	for ( i=0; i<FP_MAX; i++ )
	{
		// 写入要操作的光口号
		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(i);
		FPGA_DISABLE_WRITE;

		// 累计数据包错误计数
		bit_err_cnt += FpgaReadRegister(FPGA_REG_PKT_ERR_COUNT);
		FpgaReadRegister(FPGA_REG_CLEAR_PKT_ERR);

		TRACE_INFO_WP( "test1");
		TRACE_INFO_WP( "msg_fifo_st=%d",msg_fifo_st);
		// 判断光口是否有收到数据包
		if ( 0 != (msg_fifo_st & (0x0001<<i)) )
		{
			TRACE_INFO_WP("fpga rx");
	
			// 读取目的地址
			des_fp = FpgaReadRegister( FPGA_REG_R_MSG_DAT )+2;
			des_re = FpgaReadRegister( FPGA_REG_R_MSG_DAT )+1;
			des_ree = FpgaReadRegister( FPGA_REG_R_MSG_DAT );
			// 读取源地址
			src_fp = FpgaReadRegister( FPGA_REG_R_MSG_DAT )+2;
			src_re = FpgaReadRegister( FPGA_REG_R_MSG_DAT )+1;
			src_ree = FpgaReadRegister( FPGA_REG_R_MSG_DAT );
			
			// 读取数据长度
			frame_len = FpgaReadRegister( FPGA_REG_R_MSG_DAT );
			
			// 读取数据帧编号
			frame_no = FpgaReadRegister( FPGA_REG_R_MSG_DAT );

			TRACE_INFO_WP(" test(%02X:%02X->%02X:%02X-%d).", src_fp, src_re, des_fp, des_re, frame_len);//add20121127
			
			if (( src_fp>FP_MAX )||( src_re>RE_MAX )||(0==frame_len)||(frame_len>FPGA_MSG_BUFF_SIZE)||
				((frame_no&MSG_FRAME_INDEX_MASK)>=MSG_MAX_FRAME_INDEX) )
			{
				TRACE_INFO_WP(" Err(%02X:%02X->%02X:%02X-%d).", src_fp, src_re, des_fp, des_re, frame_len);
				// 切换FIFO页
				FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
				continue;
			}
			
			TRACE_INFO_WP( "(%d) fi(0x%02X).", frame_len, frame_no );

			frame_len--;	// 长度减1,即为有效数据长度

			// 释放缓冲区指针
			p_msg_dat = 0;
			
			if ( 0 != (frame_no & MSG_FRAME_END_FLAG) )	// 最末帧
			{
				msg_end_flag = b_TRUE;
				
				frame_no &= MSG_FRAME_INDEX_MASK;	// 取得帧编号
				
				// 判断是否是大数据包
				if ( frame_no > 0 )
				{	
					// 大数据包，判断RE是否有大缓冲使用权
					tmp = GetReBigMsgBuffIndex( src_fp, src_re );
					
					if ( 0 == tmp ) 	// 该RE没有大缓冲的使用权
					{
						// 返回接收端未就绪的应答
						MsgReceiverBusy( src_fp, src_re );
					}
					else
					{
						// 存入大数据缓冲
						tmp--;
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
						msg_len = frame_no * FPGA_MSG_FRAME_LEN + frame_len;
 					}
				}
				else
				{
					// 普通数据包，直接保存并处理
					p_msg_dat = msg_buff[i];
					msg_len = frame_len;
				}
			}
			else
			{
				// 不是最后的数据帧
				msg_end_flag = b_FALSE;
				
				// 数据需要保存到大缓冲中，先判断RE有没有大缓冲的使用权
				//if ( 0 == (re_msg_buff_st[src_fp] & (0x00000001<<src_re)) )
				tmp = GetReBigMsgBuffIndex( src_fp, src_re );
				if ( 0 == tmp )	 // RE没有大数据缓冲的使用权
				{
					tmp = GetFreeBigBuffIndex();

					if ( 0 != tmp )	// 大数据缓冲空闲,将其分配给当前RE
					{
						tmp--;
						
						msg_big_buff[tmp].owner = ((src_fp<<8)|src_re);
						msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;

						// 数据指针指向大数据缓冲
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
					}
					else		// 大数据缓冲被占用
					{
						// 返回接收端未就绪的应答
						MsgReceiverBusy( src_fp, src_re );
					}
				}
				else
				{
					tmp--;
					msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;
					p_msg_dat = msg_big_buff[tmp].buff;
					p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
				}
			}

			FPGA_ENABLE_WRITE;
			FPGA_SET_OPT(i);
			FPGA_DISABLE_WRITE;

			WTD_CLR;
			tmp = 0;
			if ( 0!=p_msg_dat )
			{
				// 读取数据
				tmp = FpgaSaveMsgDat( frame_len, p_msg_dat );
			}

			// 切换FIFO页
			FpgaReadRegister( FPGA_REG_R_NEXT_MSG );

			if (( tmp>0 )&&( tmp<=FPGA_MSG_BUFF_SIZE))
			{
				WTD_CLR;
				if ( 0!=p_msg_dat )
				{
					// 处理消息包
					if ( b_TRUE == msg_end_flag )
					{
						TRACE_INFO_WP("handle(%d).", msg_len);
						if ( frame_no>0 )
						{
							tmp = GetReBigMsgBuffIndex( src_fp, src_re );
							if ( tmp>0 )
							{
								tmp--;
								MsgHandle( src_fp, src_re, src_ree,msg_len, msg_big_buff[tmp].buff );
								msg_big_buff[tmp].owner = 0;		// 释放大数据缓冲资源
							}
						}
						else
						{
							MsgHandle( src_fp, src_re, msg_len, msg_buff[i] );
							
							/****test*********///20121127
							TRACE_INFO_WP("msg_buff\r\n");
				
							for(j=0;j<msg_len;j++)
							{
//#if 0  					
              						TRACE_INFO("msg_buff2[%d]=%d\n",j,msg_buff[i][j]); 
//#endif
							}
							/****test*********///20121127

							
						}
					}
					
					fpga_rx_pkt_cnt++;
					
				}
			}
		}
	}
	
	
}
#endif



//#if 0//20130621
/*************************************************************
Name:         FpgaReadThrDat
Description:  从指定的光口中读取透传数据
Input:         void
Output:        void          
Return:        void
**************************************************************/
void FpgaReadThrDat()
{
	_T_THR_FIFO * p_fifo;	// FIFO指针
	UINT16 fp; 
	UCHAR8 dat; 

	WTD_CLR;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA故障，返回
		return; 
	}

	// FPGA透传接收FIFO指针
	p_fifo = (0==thr_utx_fifo_use) ? (&uart_thr_tx_fifo[1]) : (&uart_thr_tx_fifo[0]);	
	//TRACE_INFO("FpgaReadThrDat---thr_utx_fifo_use=[%x]\r\n",thr_utx_fifo_use);

	// 循环读取8个光口的透传数据
	for ( fp=0; fp<FP_MAX; fp++ )	
	{
		FPGA_ENABLE_WRITE;	// 打开FPGA写使能 
		FPGA_SET_OPT(fp);	// 切换光口号 
		FPGA_DISABLE_WRITE;	// 关闭FPGA写使能 

		//thr_func.pf_en_tx_it(0);	// 关闭透传串口发送中断，防止此时串口中断改变队列结构

		if ( IS_OPT_ENABLE(fp) )	// 光口已使能
		{
			while ( p_fifo->count < THR_FIFO_SIZE )
			{
				//TRACE_INFO("mau_rev_thr_dat_from_meu---dat_flag=[%x],fp=[%d]\r\n",FpgaReadRegister(FPGA_REG_THR_FIFO_ST) & (1<<fp),fp);
				
				// FPGA透传缓冲有数据
				if ( 0 != (FpgaReadRegister(FPGA_REG_THR_FIFO_ST) & (1<<fp)) )	
				{
					// 从FPGA透传缓冲读取数据
					dat = (UCHAR8)(0xff&FpgaReadRegister(FPGA_REG_R_THR_DAT));	

					// 保存数据到FIFO中, 数据个数+1
					p_fifo->p_dat[p_fifo->count++] = dat;
					TRACE_INFO("dat=%02x,p_fifo->count=%dr\n",dat,p_fifo->count);
				}
				else
				{
					
				// 跳出读下一光口数据
					break;	
				}
				WTD_CLR;
			}
		}
		//if ( 0==thr_tx_end )			// 前一次传输未完成
		//{
			//thr_func.pf_en_tx_it(1);	// 恢复透传串口发送中断
		//}
	}

}



/*************************************************************
Name:        FpgaSendThrDat
Description: FPGA发送透传数据，不需要指定光口的操作
Input:       void     
Output:      void         
Return:      void
**************************************************************/
void FpgaSendThrDat()
{
	_T_THR_FIFO * p_fifo;	// FIFO指针
	UCHAR8 wait_time = 0; 
	UCHAR8 dat;
	UINT16 count = 0;
	UINT16 i=0;

	// FPGA透传发送FIFO指针
	p_fifo = (0==thr_urx_fifo_use) ? (&uart_thr_rx_fifo[1]) : (&uart_thr_rx_fifo[0]);

	// 复位数据索引值
	p_fifo->index = 0;
#if 0
/*--------------------------以下为测试透传数据--------------------------*/	
	p_fifo->p_dat[ p_fifo->index++ ]='T';
	p_fifo->p_dat[ p_fifo->index++ ]='h';
	p_fifo->p_dat[ p_fifo->index++ ]='r';
	p_fifo->p_dat[ p_fifo->index++ ]='D';
	p_fifo->p_dat[ p_fifo->index++ ]='a';
	p_fifo->p_dat[ p_fifo->index++ ]='t';	
	p_fifo->p_dat[ p_fifo->index++ ]='f';
	p_fifo->p_dat[ p_fifo->index++ ]='a';
	for(;p_fifo->index<97;)
	{
		p_fifo->p_dat[ p_fifo->index++ ]='m';
	}
	p_fifo->p_dat[ p_fifo->index++ ]='a';
	p_fifo->p_dat[ p_fifo->index++ ]='u';
	p_fifo->p_dat[ p_fifo->index++ ]='u';		
	p_fifo->count=p_fifo->index;
	p_fifo->index = 0;
/*--------------------------以上为测试透传数据--------------------------*/	
#endif
	//TRACE_INFO("-------------------1ThrUart_send_dat_to_meu---p_fifo->count=[%d]\r\n",p_fifo->count);	
	
	if(p_fifo->count > 0)
	{
		TRACE_INFO("-------------------1ThrUart_send_dat_to_meu---p_fifo->count=%d:  ",p_fifo->count);	
		TRACE_INFO("data: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\r\n", p_fifo->p_dat[0], p_fifo->p_dat[1],p_fifo->p_dat[2], p_fifo->p_dat[3],p_fifo->p_dat[4], p_fifo->p_dat[5],p_fifo->p_dat[6], p_fifo->p_dat[7],p_fifo->p_dat[8], p_fifo->p_dat[9],p_fifo->p_dat[10], p_fifo->p_dat[11],p_fifo->p_dat[12], p_fifo->p_dat[13],p_fifo->p_dat[14], p_fifo->p_dat[15],p_fifo->p_dat[16], p_fifo->p_dat[17],p_fifo->p_dat[18]);	
	}
	// 循环发送数据
	while ( p_fifo->count > 0 ) 
	{
		//printf("aa");
		//TRACE_INFO("2ThrUart_send_dat_to_meu---FpgaReadRegister(FPGA_REG_R_THR_IDLE_ST)=[%x]\r\n",FpgaReadRegister(FPGA_REG_R_THR_IDLE_ST));	
		
		// 等待FPGA透传缓冲空闲
		if ( 0==(0x01&FpgaReadRegister(FPGA_REG_R_THR_IDLE_ST)) )
		{
			UsNopDelay(1);	// 延时1us
			wait_time++;		// 等待时间+1
			if ( wait_time>150 )	// 最多延时100us，缓冲仍繁忙则退出
			{
				break;
			}
			else
			{
				continue;
			}
		}
		
		// 等待时间清零
		wait_time = 0;
		
		// 从FIFO取出数据,FIFO读指针后移
		dat = p_fifo->p_dat[ p_fifo->index++ ];	
		
		//TRACE_INFO("dat=%02x,count=[%d] ",dat,p_fifo->count);	
		//UsNopDelay(5000);
		// 光纤发送透传数据
		FPGA_ENABLE_WRITE;		// 打开FPGA写使能
		FpgaWriteRegister( FPGA_REG_W_THR_DAT, dat );	// 写入数据到FPGA透传缓冲
		FPGA_DISABLE_WRITE;		// 关闭FPGA写使能

		
		if(sys_param_1b[MADD_PASSTHROUGH_EN].val)
		{
			TRACE_INFO("正在测试透传485......uart_index=%d\r\n",uart_index);
	
			uart_test_tx_buff[uart_index++]=dat; 
	
			if((dat==0x4E)&&(uart_flag==0x7E))
			{
				
				for(i=0;i<uart_index;i++)
				{
					thr_func.pf_send_byte(uart_test_tx_buff[i]);
					TRACE_INFO("正在发送测试透传485数据[%d]:[%x]......\r\n",i,uart_test_tx_buff[i]);
				}
				uart_index=0;
				uart_flag=0;
	
			}
			else if(dat==0x7E)
			{
				uart_flag =dat;
			}
		}

		
		// FIFO数据个数-1
		p_fifo->count--;	

		// 喂狗
		if ( ++count > 1000 )
		{
			WTD_CLR;
			count = 0;
		}
	}

	// 数据发送完成，若透传串口接收FIFO中有数据则切换FIFO
	if ( 0 != uart_thr_rx_fifo[thr_urx_fifo_use].count )
	{
		// 复位当前FIFO
		p_fifo->index = 0;
		p_fifo->count = 0;
		// 关闭接收中断
		thr_func.pf_ie_rx_dat(0);
		// 切换FIFO
		thr_urx_fifo_use = 1-thr_urx_fifo_use;
		// 恢复接收中断
		thr_func.pf_ie_rx_dat(1);
	}

}
//#endif 

/*************************************************************
Name:        FpgaGetTopoStaus
Description: 获取拓扑结构的基本信息
Input:
	      opt: 光口号，从0起
	      p_fp_info: 指向存放光口信息的结构体指针
	      
Output:      void         
Return:
		1-读取成功
		0-读取失败
**************************************************************/
BOOL FpgaGetTopoStaus( UCHAR8 opt, _T_FP_INFO* p_fp_info )
{
	UINT16 tmp;
	
	WTD_CLR;
	
	if (( FPGA_LDST_OK!=fpga_load_status )||( opt>= FP_MAX ))
	{
		return b_FALSE;
	} 
    
	// 写入要操作的光口号   
	FPGA_ENABLE_WRITE;
	FPGA_SET_OPT(opt);
	FPGA_DISABLE_WRITE;   
	//printf("opt = %d ",opt);

	// 读取光口状态   
	tmp = FpgaReadRegister( FPGA_REG_OPT_INFO );
	//printf("tmp = %02x\r\n ",tmp);

	// 逗号锁定状态  COMMA_LOCK:1锁定 
	p_fp_info->comma_lock = (BM_OPT_COMMA_LOCK==(tmp&BM_OPT_COMMA_LOCK)) ? COMMA_LOCK : COMMA_UNLOCK;

	// 收到的帧属性 
	p_fp_info->rcv_frm_mode = (tmp&BM_UP_DN)>>UP_DN_BITS;

    /*光口帧的判断条件是:本端口接收帧锁定 +本端逗号锁定 +对端逗号锁定 */
	if (  ( 0!=(tmp&BM_OPT_FRM_LOCK) )		// 帧锁定
		&&( 0!=(tmp&BM_OPS_COMMA_LOCK) )	// 本端逗号锁定
		&&( 0!=(tmp&BM_OPT_COMMA_LOCK) )	// 对端逗号锁定
		)
	{
		p_fp_info->frm_lock = FRAME_LOCK;
	}
	else
	{
		p_fp_info->frm_lock = FRAME_UNLOCK;
	}

	//节点下行计数，数据帧锁定时有效        
	p_fp_info->re_cnt = (UCHAR8)(tmp&0x00ff);

    /*0/1------末端RE没有收到/收到的另一光端口*/
	if ( BM_OPS_END_YES == (tmp&BM_OPS_END_YES) )
	{
		//D7-0：末端RE收到的另一光端口节点下行计数 ,D15-8：末端RE收到的另一光端口序号
		tmp = FpgaReadRegister( FPGA_REG_OPS_INFO );  
		//D7位置 1表示 对端口存在，D0~D6表示对端机的光口号 为 1~8
		#ifdef  CLIENT_XINMIN	// 欣民要求光口逆序排列
			p_fp_info->ops_info = OPS_RCV_FLAG|(7-(tmp>>8));
		#else  
		   p_fp_info->ops_info = OPS_RCV_FLAG|(tmp>>8);
		#endif 
	} 
	else
	{
		p_fp_info->ops_info = OPS_NOT_FOUND;
	}

	return b_TRUE;
	
}

/*************************************************************
Name: FpgaGetSfpStatus
Description: 检测光模块状态
Input:
	fp_no: 光口号
Output:void         
Return:
	b_TRUE - 正常
	b_FALSE - 异常
**************************************************************/
BOOL FpgaGetSfpStatus( UINT32 fp_no )
{
	if ( fp_no>=FP_MAX )
	{
		return b_TRUE;
	}

	return b_TRUE;		// 暂时不支持读取光模块状态，全部返回正常
}



/*************************************************************
Name:FpgaTest         
Description:测试FPGA总线读写是否正常
Input:void
Output:void      
Return:	0:失败，1: 成功            
**************************************************************/
UCHAR8 FpgaTest()
{
	UINT32 i;
	UINT16 dw, dr;
	UCHAR8 wr_ok_flag=1;

	dw = 0x01;

	//TRACE_INFO("fpga test \r\n");
	FPGA_ENABLE_WRITE;
	for ( i=0; i<16; i++)
	{
		
		//FpgaWriteRegister(0x8000, dw);
		FpgaWriteRegister(FPGA_REG_WRITE_PROTECT, dw);
		dr = 0xffff&( ~ FpgaReadRegister(FPGA_REG_WRITE_CHECK) );
		//TRACE_INFO("fpga test  w:%04X r:%04X\r\n", dw, ~dr);
		if ( dw !=dr )
		{
			wr_ok_flag = 0;
		}
		dw <<=1;
	}
	FPGA_DISABLE_WRITE;
	//TRACE_INFO("fpga test End\r\n");
	return wr_ok_flag;
}



/*************************************************************
Name:FpgaLoad
Description:FPGA加载
Input:void          
Output:void         
Return:
	0：加载成功
	1：加载失败
	2：未发现加载文件  
**************************************************************/
UINT32 FpgaLoad(void)
{
	UCHAR8 retry = 2,i;
	UCHAR8 *p_flash_page = sys_temp_buff;
	UINT32 len,page;
	BOOL result;

	//TRACE_INFO("FpgaLoad running.\r\n");

	fpga_load_block = 0;
	
	page=( FLASH_FPGA_PAGE_START1);

	FlashRead(page, 0, p_flash_page,FLASH_PAGE_SIZE);
	if (( 0xEB==p_flash_page[0] )&&( 0x90==p_flash_page[1] ))
	{
		fpga_load_block = FPGA_LOAD_BLOCK1;
	}
	else
	{
		page=( FLASH_FPGA_PAGE_START2);
		
		FlashRead(page, 0, p_flash_page,FLASH_PAGE_SIZE);
		if (( 0xEB==p_flash_page[0] )&&( 0x90==p_flash_page[1] ))
		{
			fpga_load_block = FPGA_LOAD_BLOCK2;
		}
		else
		{
			fpga_load_status = FPGA_LDST_NO_FILE;
			return 2;
		}
	}

	len = p_flash_page[2]|(p_flash_page[3]<<8)|(p_flash_page[4]<<16)|(p_flash_page[5]<<24);

	while (retry--)
	{

		//TRACE_INFO("Fpga file in block[%d], length [%d]\r\n", fpga_load_block, len);

		if(FPGA_TYPE == A7)
			//result = FpgaLoadA7(len);
			result = FpgaLoadA7(len);
		else
			result = FpgaLoadAll(len);
		TRACE_INFO("FpgaLoadAll returned [%d]\r\n", result);
		
		WTD_CLR;
		
		if ( 1==result)			//加载成功
		{

			for(i=0;i<200;i++)
			{
				//向写地址0写入0xA5A5,从读地址0读出判断
				FpgaWriteRegister(FPGA_REG_WRITE_PROTECT, 0xA5A5);
				if ( (UINT16)FpgaReadRegister(FPGA_REG_WRITE_CHECK) == 0x5A5A)
				{
					// FPGA功能正常
					fpga_load_status = FPGA_LDST_OK;
					return 0;
				}
				WTD_CLR;
				//TRACE_INFO("FpgaLoadAll---0寄存器验证失败return 0\r\n");			
			}
			return 0;
		}
		
	}
	fpga_load_status = FPGA_LDST_FAIL;
	return 1;
}

/*************************************************************
Name: FpgaAttOutput
Description: ATT衰减器输出控制
Input: 1-全衰，0-正常
Output:void         
Return:void   
**************************************************************/
void FpgaAttOutput( UCHAR8 mode )
{
	UINT16 val;

	val = FpgaReadRegister(FPGA_REG_EX_DEV_CTL);
	
	if ( 0==mode )
	{
		val &= (~BM_OUT_ATT_OFF);
	}
	else
	{
		val |= BM_OUT_ATT_OFF;
	}
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_EX_DEV_CTL, val );	
	FPGA_DISABLE_WRITE;
}
/*************************************************************
Name: FpgaPowSelSlot 
Description:  选择功率时隙
Input: reg_add 地址
Output:void         
Return:void   
**************************************************************/
void FpgaPowSelSlot(UINT32 reg_add)
{
	if((FPGA_REG_A_FAD_POW_H==reg_add)||(FPGA_REG_A_FAD_POW_L==reg_add)||(FPGA_REG_A_BDA_POW_H==reg_add)||(FPGA_REG_A_BDA_POW_L==reg_add))
	{
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0);
		FPGA_DISABLE_WRITE;
	}
	else if((FPGA_REG_B_FAD_POW_H==reg_add)||(FPGA_REG_B_FAD_POW_L==reg_add)||(FPGA_REG_B_BDA_POW_H==reg_add)||(FPGA_REG_B_BDA_POW_L==reg_add))
	{
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0);
		//FPGA_SET_TDS_SLOT(0);	
		FPGA_DISABLE_WRITE;
	}
	else if((FPGA_REG_C_FAD_POW_H==reg_add)||(FPGA_REG_C_FAD_POW_L==reg_add)||(FPGA_REG_C_BDA_POW_H==reg_add)||(FPGA_REG_C_BDA_POW_L==reg_add))
	{
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0);
		FPGA_SET_LTE_SLOT(1);
		FPGA_DISABLE_WRITE;
	}
	else if((FPGA_REG_D_FAD_POW_H==reg_add)||(FPGA_REG_D_FAD_POW_L==reg_add)||(FPGA_REG_D_BDA_POW_H==reg_add)||(FPGA_REG_D_BDA_POW_L==reg_add))
	{
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0);
		FPGA_SET_LTE_SLOT(1);
		FPGA_DISABLE_WRITE;
	}
}

/*************************************************************
Name:FpgaWriteRegister
Description:向FPGA写寄存器写数据
Input:地址，数据
Output:void         
Return:void   
**************************************************************/
void FpgaWriteRegister(UINT16 add, UINT16 dat)
{
	UINT16 ch = 0;


	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;		
	}	
	if (0==(add & 0x8000))
	{
		return;
	}

	
	add &= 0x7FFF;

	if ( add<FPGA_WO_REG_COUNT )
	{
		//地址范围溢出
		fpga_wo_reg[add] = dat;

	}
	if(0x00==add)
	{
		//TRACE_INFO("\r\n\r\n201404211100FpgaWriteRegister................... [%x]=%X\r\n", add, fpga_wo_reg[add]);
		;
	}	
	*(p_ext_16+(add<<1)) = dat;

}

/*************************************************************
Name:FpgaReadRegister
Description:从FPGA读寄存器读数据
Input:地址
Output:void         
Return:数据   
**************************************************************/
UINT16 FpgaReadRegister(UINT16 add)
{
	UCHAR8 reg_type;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return NULL;
	}

	reg_type = (add>>12)&0x0F;

	add &= 0x0FFF;
	
	switch( reg_type )
	{
		case 0x00:
			//只读寄存器地址
			return *(p_ext_16+(add<<1));	
		break;
			
		case 0x08:
			//只写寄存器地址，从缓冲读取
			if ( add>FPGA_WO_REG_COUNT )
			{
				return 0;
			}
			return fpga_wo_reg[add];
		break;

		case 0x0A:
			if ( add>(MAX_CHANNEL_COUNT*2+2) )
			{
				return 0;
			}
			return fpga_a_regbk[add];
		break;

		case 0x0B:
			if ( add>(MAX_CHANNEL_COUNT*2+2) )
			{
				return 0;
			}
			return fpga_b_regbk[add];
		break;

		case 0x0C:
			if ( add>(MAX_CHANNEL_COUNT*2+2) )
			{
				return 0;
			}
			TRACE_INFO_WP("FpgaReadRegister................... pga_c_regbk[%d]=%X\r\n", add, fpga_c_regbk[add]);
			
			return fpga_c_regbk[add];
		break;

		case 0x0D:
			if ( add>(MAX_CHANNEL_COUNT*2+2) )
			{
				return 0;
			}
			TRACE_INFO_WP("FpgaReadRegister................... pga_d_regbk[%d]=%X\r\n", add, fpga_d_regbk[add]);
		
			return fpga_d_regbk[add];
		break;
		
		case 0x1://1字节通过读逻辑读A段参数
			//if (0X00==add  )
			{
				return sys_param_1b[add].val;
			}
			return 0;
		break;

		case 0x2://2字节通过读逻辑读B段参数
		//	if ( 0X00==add )
			{
				return sys_param_2b[add].val;
			}
			return 0;		
		break;	

			return 0;				

	}


}
 

/*************************************************************
Name:FpgaConfigPara
Description:配置FPGA参数
Input:void
Output:void         
Return:void
**************************************************************/
void FpgaConfigPara(void)
{
	WTD_CLR;

	FPGA_ENABLE_WRITE;

	// 初始化光口，全部关闭
	FpgaWriteRegister(FPGA_REG_OPT_ON, 0);
		
	// 复位外设控制IO
	FpgaWriteRegister( FPGA_REG_EX_DEV_CTL, 
		BM_EX_PLL_CLK|BM_EX_PLL_DAT|BM_EX_BA_PLL_LE|BM_EX_BB_PLL_LE|BM_EX_FA_PLL_LE|BM_EX_FB_PLL_LE );

	// 设置工作模式
	FpgaWriteRegister( FPGA_REG_A_ATT_CTL, ATT_MODE_NORMAL );		// A段ATT正常工作模式
	FpgaWriteRegister( FPGA_REG_B_ATT_CTL, ATT_MODE_NORMAL );		// B段ATT正常工作模式
	FpgaWriteRegister( FPGA_REG_C_ATT_CTL, ATT_MODE_NORMAL );		// A段ATT正常工作模式
	FpgaWriteRegister( FPGA_REG_D_ATT_CTL, ATT_MODE_NORMAL );		// B段ATT正常工作模式
		
	UsNopDelay(200000);
	
	FPGA_DISABLE_WRITE;
	
	

	ReadWriteTF(0,1,0x0FB,0X0A);
	ReadWriteTF(1,1,0x0FB,0X0B);
	ReadWriteTF(2,1,0x0FB,0X0B);
	//ReadWriteTF(3,1,0x0FB,0X0B);	
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_ATT_FULL_REDUCE, 0 );		// att1零衰	
	FPGA_DISABLE_WRITE;
	
	
	WTD_CLR;
	
}


/*************************************************************
Name:		CheckClkMode
Description: 检查FPGA时钟
Input:void
Output:void         
Return:void
**************************************************************/
void CheckClkMode()
{
	UINT16 tmp;
	tmp = FpgaReadRegister(FPGA_REG_GCLK_ST);
	
	if ( 0==( tmp&BM_CLK_125) )
	{
		SetClkFlag(CLK_FLAG_122_88M);
		
	}
	else
	{
		SetClkFlag(CLK_FLAG_125M);
	}
 
	if ( 0==( tmp&BM_WLAN_EN) )
	{
		fpga_cfg.wlan_en = 0;
	}
	else
	{
		fpga_cfg.wlan_en = 1;
	}
}

/*************************************************************
Name:AfterFpgaLoad         
Description:FPGA加载完后初始化
Input:void
Output:void      
Return:void        
**************************************************************/
void AfterFpgaLoad(void) 
{
	CHAR8 ret_val;
	UINT16 reg_val;

	//TRACE_INFO("Reset FPGA.\r\n");

	// 读取AB段通讯制式
	reg_val = FpgaReadRegister(FPGA_REG_RF_INFO);
	fpga_cfg.a_ultra_info = (UCHAR8)(reg_val>>8)&0x07;
	fpga_cfg.b_ultra_info = (UCHAR8)(reg_val>>12)&0x0F;
	fpga_cfg.c_ultra_info = (UCHAR8)(reg_val>>9)&0x01;
	fpga_cfg.d_ultra_info = (UCHAR8)(reg_val>>9)&0x01;	
	
//	reg_val = FpgaReadRegister(FPGA_REG_RF_INFO_C_D);	
//	fpga_cfg.c_ultra_info = (UCHAR8)(reg_val)&0x0F;
//	fpga_cfg.d_ultra_info = (UCHAR8)(reg_val>>4)&0x0F;	
#ifdef TD_TYPE_WB
	fpga_cfg.b_ultra_info = FPGA_B_NT_TD_WB;
#endif
	
	//InitFpga();	

	//软件版本	
	reg_val = FpgaReadRegister(FPGA_REG_EDITION_INFO); 
	sys_param_2b[MADD_PRI_SOFT_V].val = MCU_SOFT_VER|((reg_val<<8)&0xFF00);
	
	//PCB版本号    
	reg_val = FpgaReadRegister(FPGA_REG_PCB_VERSION); 
	sys_param_2b[MADD_PRI_HARD_V].val = reg_val;	//hard_ware_v;
	
	//读取水印文件 
	FpgaReadRegister(FPGA_REG_IRQ_CLEAN);	//水印读出初始化
	
	for (ret_val=0; ret_val<sys_param_asc[MADD_PRI_FPGA_DATE].length; ret_val++)
	{
		str_pri_fpga_date[ret_val] = (CHAR8)FpgaReadRegister(FPGA_REG_WATER_PRINT);
	}      
	for (ret_val=0; ret_val<sys_param_asc[MADD_PRI_FPGA2_DATE].length; ret_val++)
	{
		str_pri_fpga2_date[ret_val] = ' ';
	}	
	//初始化当前拓扑结构体和RE延时测量值
	//InitTopoInfo();
}		

/*************************************************************
Name:FpgaGetChannelCount         
Description: 从FPGA读取通道数
Input:void
Output:void      
Return:-1:失败，1: 成功            
**************************************************************/
void FpgaGetChannelCount()
{
	UINT16 tmp;
	UINT16 i;
	
	tmp = FpgaReadRegister(FPGA_REG_CH_COUNT);		// 从FPGA读取通道数
	#if defined CLIENT_JIZHUN
	sys_param_1b[MADD_A_CHANNEL_COUNT].val = tmp&0x1F>>0;		// A段支持的通道数
	sys_param_1b[MADD_B_CHANNEL_COUNT].val = 0;		// B段支持的通道数
	sys_param_1b[MADD_C_CHANNEL_COUNT].val = 0;			// C段支持的通道数
	sys_param_1b[MADD_D_CHANNEL_COUNT].val = 0;		// D段支持的通道数
	#else 
	sys_param_1b[MADD_A_CHANNEL_COUNT].val = tmp&BM_A_CH_COUNT;			// A段支持的通道数
	sys_param_1b[MADD_B_CHANNEL_COUNT].val = (tmp&BM_B_CH_COUNT)>>8;		// B段支持的通道数
	sys_param_1b[MADD_C_CHANNEL_COUNT].val = (tmp&BM_C_CH_COUNT)>>4;			// C段支持的通道数
	sys_param_1b[MADD_D_CHANNEL_COUNT].val = (tmp&BM_D_CH_COUNT)>>12;		// D段支持的通道数
	#endif

	if ( sys_param_1b[MADD_A_CHANNEL_COUNT].val > MAX_CHANNEL_COUNT )
	{
		//TRACE_ERROR("A Channel Count Err(%d)\r\n", sys_param_1b[MADD_A_CHANNEL_COUNT].val );
		sys_param_1b[MADD_A_CHANNEL_COUNT].val = 0;
	}

	if ( sys_param_1b[MADD_B_CHANNEL_COUNT].val > MAX_CHANNEL_COUNT )
	{
		//TRACE_ERROR("B Channel Count Err(%d)\r\n", sys_param_1b[MADD_B_CHANNEL_COUNT].val );
		sys_param_1b[MADD_B_CHANNEL_COUNT].val = 0;
	}
	
	if ( sys_param_1b[MADD_C_CHANNEL_COUNT].val > 4 )
	{
		//TRACE_ERROR("A Channel Count Err(%d)\r\n", sys_param_1b[MADD_A_CHANNEL_COUNT].val );
		sys_param_1b[MADD_C_CHANNEL_COUNT].val = 0;
	}

	if ( sys_param_1b[MADD_D_CHANNEL_COUNT].val > 4 )
	{
		//TRACE_ERROR("B Channel Count Err(%d)\r\n", sys_param_1b[MADD_B_CHANNEL_COUNT].val );
		sys_param_1b[MADD_D_CHANNEL_COUNT].val = 0;
	}	

	
}


/*************************************************************
Name:         FpgaEnableTrafficCtl         
Description:  控制话务统计
Input:        time   -  多长时间统计一次
              enable -  使能控制
Output:       void      
Return:       void          
**************************************************************/
void FpgaEnableTrafficCtl( UCHAR8 time, UCHAR8 enable )
{
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_TRAFFIC_CTL, ((time&BM_TRAFFIC_PERIOD)|( 1==enable ? (1<<15) : 0 )) );
	FPGA_DISABLE_WRITE;
}

		
/*************************************************************
Name:InitFpga         
Description:初始化FPGA
Input:void
Output:void      
Return:-1:失败，1: 成功            
**************************************************************/
BOOL InitFpga(void)
{
	UCHAR8 tmp;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA故障，返回
		return b_FALSE; 
	}

	
	WTD_CLR;
	//TRACE_INFO("Init FPGA.\r\n");
	CLR_FPGA_RST_PIN;	//PIO_Clear(fpga_reset);
	UsNopDelay(10); 
	SET_FPGA_RST_PIN;	//PIO_Set(fpga_reset);
	
	// 读取AB段支持的通道数 
	FpgaGetChannelCount();

	//配置写寄存器
	FpgaConfigPara();

	
	InitPartA();
	InitPartB();
	InitPartC();
	InitPartD();
	//FPGA频率输出补偿
	// SetFpgaFreqAdj();

	// FPGA温度补偿系数
	FpgaSetTempAdjustTable();

	// 使能话务量统计,15分钟
	FpgaEnableTrafficCtl( TRAFFIC_TIME, 1 );


	
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_SHOW_ERROR, 0xF000);//清除告警项
	FPGA_DISABLE_WRITE;
	
	return b_TRUE;
	
}


/*************************************************************
Name:    	  FpgaMakeAttAdjMsgHead         
Description:   打包数据到att_adj_buff数组中

Input:         len   - 打包的数据长度
               p_dat - 数据指针
Output:  
Return:        void            
**************************************************************/
void FpgaMakeAttAdjMsgHead( UINT32 len, UCHAR8 * p_dat )
{
	UINT32 i;
 
	if ( len>512 ) return;

	// 复位数据长度
	fpga_att_adj_st.dat_len = 0;

	// 拷贝数据
	for ( i=0; i<len; i++ )
	{
		att_adj_buff[fpga_att_adj_st.dat_len++] = *p_dat++;
	}
}


/*************************************************************
Name:         FpgaGetAdDaPow         
Description:  获得REC的AD和DA功率
Input:        ab_flag   -  A段,B段选择
Output:       void      
Return:       void          
**************************************************************/  
void FpgaGetAdDaPow( UCHAR8 ab_flag )
{
	UINT16 pad_reg_l, pad_reg_h, pda_reg_l, pda_reg_h;
	UINT16 tmp;

	if ( SYS_A_FLAG==ab_flag )
	{
		pad_reg_l = FPGA_REG_A_FAD_POW_L;
		pad_reg_h = FPGA_REG_A_FAD_POW_H;
		pda_reg_l = FPGA_REG_A_BDA_POW_L;
		pda_reg_h = FPGA_REG_A_BDA_POW_H;
	}
	else if ( SYS_B_FLAG == ab_flag )
	{
		pad_reg_l = FPGA_REG_B_FAD_POW_L;
		pad_reg_h = FPGA_REG_B_FAD_POW_H;
		pda_reg_l = FPGA_REG_B_BDA_POW_L;
		pda_reg_h = FPGA_REG_B_BDA_POW_H;
	}
	else if ( SYS_C_FLAG == ab_flag )
	{
		pad_reg_l = FPGA_REG_C_FAD_POW_L;
		pad_reg_h = FPGA_REG_C_FAD_POW_H;
		pda_reg_l = FPGA_REG_C_BDA_POW_L;
		pda_reg_h = FPGA_REG_C_BDA_POW_H;
	}
	else if ( SYS_D_FLAG == ab_flag )
	{
		pad_reg_l = FPGA_REG_D_FAD_POW_L;
		pad_reg_h = FPGA_REG_D_FAD_POW_H;
		pda_reg_l = FPGA_REG_D_BDA_POW_L;
		pda_reg_h = FPGA_REG_D_BDA_POW_H;
	}	
	else
	{
		return;
	} 

	FpgaPowSelSlot(pad_reg_l);
//	TRACE_INFO("AD:");
	// Pad
	tmp = FpgaReadRegister(pad_reg_l);
//	TRACE_INFO_WP("L:%04X", tmp);
	att_adj_buff[ fpga_att_adj_st.dat_len++] = (UCHAR8)(tmp&0xff);
	att_adj_buff[ fpga_att_adj_st.dat_len++]= (UCHAR8)((tmp>>8)&0xff);

	tmp = FpgaReadRegister(pad_reg_h);
//	TRACE_INFO_WP("H:%04X", tmp);
	att_adj_buff[ fpga_att_adj_st.dat_len++] = (UCHAR8)(tmp&0xff);
	att_adj_buff[ fpga_att_adj_st.dat_len++] = (UCHAR8)((tmp>>8)&0xff);
	
//	TRACE_INFO("     DA:");
	// Pda
	tmp = FpgaReadRegister(pda_reg_l);
	//TRACE_INFO_WP("99999999999999999999999999999L=%04X,pda_reg_l=%04X,", tmp,pda_reg_l);
	att_adj_buff[ fpga_att_adj_st.dat_len++] = (UCHAR8)(tmp&0xff);
	att_adj_buff[ fpga_att_adj_st.dat_len++] = (UCHAR8)((tmp>>8)&0xff);

	tmp = FpgaReadRegister(pda_reg_h);
	//TRACE_INFO_WP("H=%04X,pda_reg_h=%04X\r\n", tmp,pda_reg_h);
	att_adj_buff[ fpga_att_adj_st.dat_len++] = (UCHAR8)(tmp&0xff);
	att_adj_buff[ fpga_att_adj_st.dat_len++] = (UCHAR8)((tmp>>8)&0xff);

	#if 0
			TRACE_INFO("att_adj_buff10[%X]\r\n",att_adj_buff[10]);
			TRACE_INFO("att_adj_buff11[%X]\r\n",att_adj_buff[11]);
			TRACE_INFO("att_adj_buff12[%X]\r\n",att_adj_buff[12]);
			TRACE_INFO("att_adj_buff13[%X]\r\n",att_adj_buff[13]);

			TRACE_INFO("att_adj_buff14[%X]\r\n",att_adj_buff[14]);
			TRACE_INFO("att_adj_buff15[%X]\r\n",att_adj_buff[15]);
			TRACE_INFO("att_adj_buff16[%X]\r\n",att_adj_buff[16]);
			TRACE_INFO("att_adj_buff17[%X]\r\n",att_adj_buff[17]);
	#endif 
}


/*************************************************************
Name:         FpgaHandlePsfAck         
Description:  把从RE读取回来的选频功率保存到数组中
Input:        p_dat -指选频功率数据的 指针头
Output:       void      
Return:       void          
**************************************************************/ 
void FpgaHandlePsfAck( UCHAR8 * p_dat )
{
	if ( 1==fpga_att_adj_st.is_wait )
	{

		// 跳过1字节寄存器属性，2字节地址
		p_dat += 4; 

		TRACE_INFO_WP("-------------------fpga_att_adj_st.dat_len=%d,H=%04X,L=%04X\r\n",fpga_att_adj_st.dat_len,*(p_dat+3)<<8|*(p_dat+2),*(p_dat+1)<<8|*(p_dat));		
		// 保存Psf数据低16位
		att_adj_buff[ fpga_att_adj_st.dat_len++] = *p_dat++;
		att_adj_buff[ fpga_att_adj_st.dat_len++] = *p_dat++;
		
		// 跳过1字节寄存器属性，2字节地址
		p_dat += 4;  
		// 保存Psf数据高16位
		att_adj_buff[ fpga_att_adj_st.dat_len++] = *p_dat++;
		att_adj_buff[ fpga_att_adj_st.dat_len++] = *p_dat++;
		// 清除等待标志   
		fpga_att_adj_st.is_wait = 0;
		TRACE_INFO_WP("-------------------0=%X,1=%X,2=%X,3=%X\\r\n",att_adj_buff[ fpga_att_adj_st.dat_len-4],att_adj_buff[ fpga_att_adj_st.dat_len-3],att_adj_buff[ fpga_att_adj_st.dat_len-2],att_adj_buff[ fpga_att_adj_st.dat_len-1]);		
		
	}
}


/*************************************************************
Name:         FpgaAttStepAdj        
Description:  选择要校正的ATT，并写入步进值
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
void FpgaAttStepAdj()  
{
	UINT16 att_reg; 
	UINT16 att_ctl_reg;
	
	if ( ATT_UL_ADJ==fpga_att_adj_st.ud_flag )
	{
		// 上行输出校准,3att 
		if ( 0==fpga_att_adj_st.att_no )
		{
			if ( SYS_A_FLAG==fpga_att_adj_st.ab_flag )
			{
				att_reg = FPGA_REG_A_ATT3_CAL;
				att_ctl_reg = FPGA_REG_A_ATT3_EN;
			}
			else if( SYS_B_FLAG==fpga_att_adj_st.ab_flag )
			{ 
				att_reg = FPGA_REG_B_ATT3_CAL;
				att_ctl_reg = FPGA_REG_B_ATT3_EN;
			}  
			else if( SYS_C_FLAG==fpga_att_adj_st.ab_flag )
			{ 
				att_reg = FPGA_REG_C_ATT3_CAL;
				att_ctl_reg = FPGA_REG_C_ATT3_EN;
			}  
			else if( SYS_D_FLAG==fpga_att_adj_st.ab_flag )
			{ 
				att_reg = FPGA_REG_D_ATT3_CAL;
				att_ctl_reg = FPGA_REG_D_ATT3_EN;
			}  
		} 
	}
	else 
	{
		// 下行输入校准 1att 
		if ( 0==fpga_att_adj_st.att_no )
		{
			if ( SYS_A_FLAG==fpga_att_adj_st.ab_flag )
			{
				att_reg = FPGA_REG_A_ATT1_CAL;
			} 
			else if ( SYS_B_FLAG==fpga_att_adj_st.ab_flag )
			{  
				att_reg = FPGA_REG_B_ATT1_CAL;
			}
			else if ( SYS_C_FLAG==fpga_att_adj_st.ab_flag )
			{  
				att_reg = FPGA_REG_C_ATT1_CAL;
			}
			else if ( SYS_D_FLAG==fpga_att_adj_st.ab_flag )
			{  
				att_reg = FPGA_REG_D_ATT1_CAL;
			}
		}
		else // att2 
		{
		#if 0
			if ( SYS_A_FLAG==fpga_att_adj_st.ab_flag )
			{
				att_reg = FPGA_REG_A_ATT2_CAL;
			}
			else if( SYS_B_FLAG==fpga_att_adj_st.ab_flag )
			{
				att_reg = FPGA_REG_B_ATT2_CAL;
			}
			else if( SYS_C_FLAG==fpga_att_adj_st.ab_flag )
			{
				att_reg = FPGA_REG_C_ATT2_CAL;
			}
			else if( SYS_D_FLAG==fpga_att_adj_st.ab_flag )
			{
				att_reg = FPGA_REG_D_ATT2_CAL;
			}
		#endif
		}
	}

	if ( fpga_att_adj_st.step >= 64 )
	{
		fpga_att_adj_st.step = 0;
	}


	if(ATT_UL_ADJ==fpga_att_adj_st.ud_flag )
	{
		FPGA_ENABLE_WRITE;
		//SetAtt1(fpga_att_adj_st.ab_flag ,(0x3F - fpga_att_adj_st.step));
		FpgaWriteRegister(att_reg,fpga_att_adj_st.step);
		FpgaWriteRegister(att_ctl_reg,0x01);
		FPGA_DISABLE_WRITE;
	}
	else
	{
		if(fpga_att_adj_st.step <= 0x1F)
			SetAtt1(fpga_att_adj_st.ab_flag ,(0x1F - fpga_att_adj_st.step));

	}

	
}


/*************************************************************
Name:         FpgaAttAdjust        
Description:  校正ATT表格函数
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
void FpgaAttAdjust()
{
//	TRACE_INFO("20FpgaAttAdjust\r\n");
	if ( ATT_ADJ_ST_MAX_ADJ==fpga_att_adj_st.adj_st)
	{
//		TRACE_INFO("FpgaAttAdjust_ ATT_ADJ_ST_MAX_ADJ\r\n");
		// 开始校准
		if ( 0 == fpga_att_adj_st.is_wait )
		{
			//REC本身进入 校准模式并且3个ATT都设置为0 
			FpgaEnterAttAdjMode( fpga_att_adj_st.ab_flag );
			WTD_CLR;
			UsNopDelay(1000*1000);
			WTD_CLR;
			UsNopDelay(1000*1000);
			//WTD_CLR;
			//UsNopDelay(1000*1000);	
			WTD_CLR;
			// 从RE读取选频功率寄存器   32位 
			GetPsfFromRe( fpga_att_adj_st.ab_flag, fpga_att_adj_st.ud_flag );
			// 读取REC 自身的 AD、DA功率      
			FpgaGetAdDaPow( fpga_att_adj_st.ab_flag );
			
			fpga_att_adj_st.adj_st= ATT_ADJ_ST_WAIT_MAX_PSF;
			// 置等待标志
			fpga_att_adj_st.is_wait = 1;
		} 		
		return;
	}

	if ( ATT_ADJ_ST_WAIT_MAX_PSF==fpga_att_adj_st.adj_st)
	{
	//	TRACE_INFO("FpgaAttAdjust_ ATT_ADJ_ST_WAIT_MAX_PSF\r\n");		
		if ( 0==fpga_att_adj_st.is_wait )
		{ 
			#if 0
			TRACE_INFO("att_adj_buff10[%X]\r\n",att_adj_buff[10]);
			TRACE_INFO("att_adj_buff11[%X]\r\n",att_adj_buff[11]);
			TRACE_INFO("att_adj_buff12[%X]\r\n",att_adj_buff[12]);
			TRACE_INFO("att_adj_buff13[%X]\r\n",att_adj_buff[13]);
			#endif 
			//TRACE_INFO("ATT_ADJ_ST_WAIT_MAX_PSF-------------fpga_att_adj_st.dat_len=%X\r\n",fpga_att_adj_st.dat_len);
			//TRACE_INFO_WP("1=%X,2=%X,3=%X,4=%X\r\n",att_adj_buff[17],att_adj_buff[18],att_adj_buff[19],att_adj_buff[21]);		

			// 将数据返回给主控
			SendMsgPkt( fpga_att_adj_st.dat_len, att_adj_buff );
			// 状态机复位
			fpga_att_adj_st.adj_st  = ATT_ADJ_ST_IDLE; 
			fpga_att_adj_st.is_wait = 0;  
			// 清除校准标志位
			sys_work_info &= (~SYSTEM_FLAG_ATT_ADJ);
		} 
		
		return;
	}

	if ( ATT_ADJ_ST_STEP_ADJ== fpga_att_adj_st.adj_st )
	{
//		TRACE_INFO("FpgaAttAdjust_ATT_ADJ_ST_STEP_ADJ(%d)\r\n",fpga_att_adj_st.step);			
		// 步进校准 
		if ( fpga_att_adj_st.step>=64 )
		{
			// 步进完成，将数据返回给主控
			SendMsgPkt( fpga_att_adj_st.dat_len, att_adj_buff );

			// 状态机复位  
			fpga_att_adj_st.adj_st  = ATT_ADJ_ST_IDLE; 
			fpga_att_adj_st.is_wait = 0; 
			
			// 清除校准标志位
			sys_work_info &= (~SYSTEM_FLAG_ATT_ADJ);
			
		}
		else
		{
			FpgaAttStepAdj();
			WTD_CLR;
			UsNopDelay(50000);
			//TRACE_INFO("FpgaAttAdjust_ATT_ADJ_ST_STEP_ADJ(%d)\r\n",fpga_att_adj_st.step);
			// 从RE读取选频功率寄存器
			GetPsfFromRe( fpga_att_adj_st.ab_flag, fpga_att_adj_st.ud_flag );
			fpga_att_adj_st.adj_st= ATT_ADJ_ST_WAIT_STEP_PSF;
			// 置等待标志
			fpga_att_adj_st.is_wait = 1;
		}
		return;
	}

	if ( ATT_ADJ_ST_WAIT_STEP_PSF==fpga_att_adj_st.adj_st)
	{
	//	TRACE_INFO("FpgaAttAdjust_ATT_ADJ_ST_WAIT_STEP_PSF\r\n");			
		if ( 0==fpga_att_adj_st.is_wait )
		{
			fpga_att_adj_st.step++;
			fpga_att_adj_st.adj_st= ATT_ADJ_ST_STEP_ADJ;
		}
		return;
	}

}

/*************************************************************
Name:        FpgaEnterAttAdjMode
Description: FPGA进入校准模式
Input: 
	      ab_flag: AB段标志
Output:      void 
Return:      void 
**************************************************************/
void FpgaEnterAttAdjMode( UCHAR8 abcd_flag )
{ 
	UINT16 tmp; 
	UINT16 i = 0;

	FPGA_ENABLE_WRITE;
	
	if ( SYS_A_FLAG == abcd_flag )
	{  
		tmp = FpgaReadRegister(FPGA_REG_A_ATT_CTL);
		tmp &= 0xFFFC;
		tmp |= (ATT_MODE_ADJUST|ATT_WORK_EN);//|ATT_MANUAL);  // 衰减校准模式  
		FpgaWriteRegister(FPGA_REG_A_ATT_CTL, tmp);//衰减校准模式  
		//FpgaWriteRegister(FPGA_REG_ATT_FULL_REDUCE, tmp);//数控衰减器全衰
		SetAtt1(TF_A,0X1F);
		
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_A_ATT3_CAL, 0X00 ); // 所有衰减器不衰
		FpgaWriteRegister(FPGA_REG_A_ATT3_EN,0x01);
		FPGA_DISABLE_WRITE;

		if(version_number == VERSION_50M_IN_V5)
		{
			FPGA_ENABLE_WRITE;
			FpgaWriteRegister(FPGA_REG_A_D_FREQ_CTL_L_12, 0x8893);
	 		FpgaWriteRegister(FPGA_REG_A_D_FREQ_CTL_H_14, 0x0041);
			FPGA_DISABLE_WRITE;
 		}
		

	}
	else if ( SYS_B_FLAG == abcd_flag )
	{
		tmp = FpgaReadRegister(FPGA_REG_B_ATT_CTL);
		tmp &= 0xFFFC;
		tmp |= (ATT_MODE_ADJUST|ATT_WORK_EN);//|ATT_MANUAL);
		FpgaWriteRegister(FPGA_REG_B_ATT_CTL, tmp);
		//FpgaWriteRegister(FPGA_REG_ATT_FULL_REDUCE, tmp);//数控衰减器全衰

		// 所有衰减器不衰
		SetAtt1(TF_B,0X1F);
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_B_ATT3_CAL, 0X00 ); // 所有衰减器不衰
		FpgaWriteRegister(FPGA_REG_B_ATT3_EN,0x01);
		UsNopDelay(20);

		if ( FPGA_B_NT_TD_WB !=fpga_cfg.b_ultra_info)	// TD宽带版
		{
			FPGA_SET_CHANNEL(0);		// 设置通道号
			FpgaWriteRegister(FPGA_REG_B_FREQ_CTL_L_12, 0x8D86);
 			FpgaWriteRegister(FPGA_REG_B_FREQ_CTL_H_14, 0x0015);
			TRACE_INFO("----------FPGA_B_NT_TD_WB !=fpga_cfg.b_ultra_info\r\n");
		}
		else
		{
			TRACE_INFO("----------FPGA_B_NT_TD_WB ==fpga_cfg.b_ultra_info\r\n");
		}
		FPGA_DISABLE_WRITE;


	}
	else if ( SYS_C_FLAG == abcd_flag )
	{
		tmp = FpgaReadRegister(FPGA_REG_C_ATT_CTL);
		tmp &= 0xFFFC;
		tmp |= (ATT_MODE_ADJUST|ATT_WORK_EN);//|ATT_MANUAL);
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_C_ATT_CTL, tmp);
		FPGA_DISABLE_WRITE;
		//FpgaWriteRegister(FPGA_REG_ATT_FULL_REDUCE, tmp);//数控衰减器全衰
		SetAtt1(TF_C,0X1F);
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0); //打开0通道
		FpgaWriteRegister(FPGA_REG_C_ATT3_CAL, 0X00 ); // 所有衰减器不衰
		FpgaWriteRegister(FPGA_REG_C_ATT3_EN,0x01);
		UsNopDelay(20);
		TRACE_INFO("\r\n");
		TRACE_INFO("FpgaAttAdjust_ 66666666666666666666666666666-----------\r\n");
		TRACE_INFO("\r\n");
		TRACE_INFO("\r\n");
		FPGA_SET_CHANNEL(0);		// 设置通道号
		//FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_L_12, 0x8893);
 		//FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_H_14, 0x0041);
 		//if(version_number == VERSION_40M_IN_E)
 		#if defined CLIENT_ERRICSON2
		{
			FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_L_12, 0x8566);
	 		FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_H_14, 0x11B5);
 		}
 		#elif defined CLIENT_ERRICSON
 		{
 			FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_L_12, 0x8893);
	 		FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_H_14, 0x0041);
 		}
		#elif defined CLIENT_ERRICSON_W
		{
			
			FpgaWriteRegister(FPGA_REG_C_D_FREQ_CTL_L_12, 0x8000);
	 		FpgaWriteRegister(FPGA_REG_C_D_FREQ_CTL_H_14, 0x100);
		}
		#else
		{
			FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_L_12, 0x8893);
	 		FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_H_14, 0x0041);
		}
		#endif
		FPGA_DISABLE_WRITE;
		
		TRACE_INFO("FpgaReadRegister( FPGA_REG_CH_SEL):%x\r\n",FpgaReadRegister( FPGA_REG_CH_SEL));
 		TRACE_INFO("FpgaReadRegister( FPGA_REG_C_FREQ_CTL_L_12)11111:%x\r\n",FpgaReadRegister( FPGA_REG_C_FREQ_CTL_L_12));
		// 所有衰减器不衰
	


	}
	else if ( SYS_D_FLAG == abcd_flag )
	{
		float FREQ_CTL_Val=0;
		
		tmp = FpgaReadRegister(FPGA_REG_D_ATT_CTL);
		tmp &= 0xFFFC;
		tmp |= (ATT_MODE_ADJUST|ATT_WORK_EN);//|ATT_MANUAL);
		FpgaWriteRegister(FPGA_REG_D_ATT_CTL, tmp);
		//FpgaWriteRegister(FPGA_REG_ATT_FULL_REDUCE, tmp);//数控衰减器全衰

		// 所有衰减器不衰
		SetAtt1(TF_D,0X1F);
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0); //打开0通道
		FpgaWriteRegister(FPGA_REG_D_ATT3_CAL, 0X00 ); // 所有衰减器不衰
		FpgaWriteRegister(FPGA_REG_D_ATT3_EN,0x01);
		UsNopDelay(20);
		FPGA_SET_CHANNEL(0);		// 设置通道号
		//FREQ_CTL_Val=0x8893*50/62.5;
		if((version_number == VERSION_40M_IN_E))
		{
			FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_L_12, 0x870A);
	 		FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_H_14, 0x8A3D);
 		}
 		else
 		{
 			FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_L_12, 0x8893);
	 		FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_H_14, 0x0041);
 		}
 		TRACE_INFO("FpgaReadRegister( FPGA_REG_CH_SEL):%x\r\n",FpgaReadRegister( FPGA_REG_CH_SEL));
 		TRACE_INFO("FpgaReadRegister( FPGA_REG_D_FREQ_CTL_L_12):%x\r\n",FpgaReadRegister( FPGA_REG_D_FREQ_CTL_L_12));
 		
		FPGA_DISABLE_WRITE;
		/*for(i=0; i<63; i++ )
		{
			tmp = 0;
			FpgaWriteRegister(FPGA_REG_D_ATT1_CAL, tmp ); // 所有衰减器不衰
			UsNopDelay(20);
			//FpgaWriteRegister(FPGA_REG_C_ATT2_CAL, 0 ); // 所有衰减器不衰
			FpgaWriteRegister(FPGA_REG_D_ATT3_CAL, tmp ); // 所有衰减器不衰
			UsNopDelay(20);
		}*/


	}	
	FPGA_DISABLE_WRITE;
}

/*************************************************************
Name:FpgaExitAttAdjMode
Description: FPGA退出校准模式
Input: 
	ab_flag: AB段标志
Output: void
Return: void
**************************************************************/
void FpgaExitAttAdjMode( UCHAR8 ab_flag )
{
	UINT16 tmp; 
	UINT16 reg;
	UCHAR8 data;	

	if ( SYS_A_FLAG == ab_flag )
	{
		reg= FPGA_REG_A_ATT_CTL;
		data=0x0a;
		ReadWriteTF(TF_A,1,0X56,0X00);//打开上行，输出通道、	

		if(version_number == VERSION_50M_IN_V5)
		{
			FPGA_ENABLE_WRITE;
			FPGA_SET_CHANNEL(0);		// 设置通道号
			FpgaWriteRegister(FPGA_REG_A_D_FREQ_CTL_L_12, 0x8000);
	 		FpgaWriteRegister(FPGA_REG_A_D_FREQ_CTL_H_14, 0x0000);
			
			//FpgaWriteRegister(FPGA_REC_D_TD_WORK_MODE, TD_WM_NORMAL);
			//sys_param_1b[MADD_D_TD_WORK_MODE].val = TD_WM_NORMAL;
			FPGA_DISABLE_WRITE;
			//退出校准上行时，打开上行射频开关
			tmp=ReadWriteTF(TF_A,0,0x057,0x01);
			tmp&=(~0x01<<0);
			ReadWriteTF(TF_A,1,0x057,tmp);		
			// 下行输入			
			//退出校准，打开下行射频开关
			tmp=ReadWriteTF(TF_D,0,0x053,0x01);
			tmp&=~((0x01<<2)|(0x01<<4));			
			ReadWriteTF(TF_A,1,0x053,tmp);		

			ReadWriteTF(TF_A,1,0X56,0X00);//打开上行，输出通道、
		}
	}
	else if ( SYS_B_FLAG == ab_flag )
	{
		data=0x0b;
		reg= FPGA_REG_B_ATT_CTL;
		FPGA_ENABLE_WRITE;
		if(NET_TYPE_TD!=fpga_cfg.b_net_type)
		{
			FPGA_SET_CHANNEL(0);		// 设置通道号
			FpgaWriteRegister(FPGA_REG_B_FREQ_CTL_L_12, 0x8000);
	 		FpgaWriteRegister(FPGA_REG_B_FREQ_CTL_H_14, 0x0000);			
		}
		FpgaWriteRegister(FPGA_REG_TD_WORK_MODE, TD_WM_NORMAL);
		sys_param_1b[MADD_TD_WORK_MODE].val = 0;
		FPGA_DISABLE_WRITE;		
		//退出校准上行时，打开上行射频开关
		tmp=ReadWriteTF(TF_B,0,0x057,0x01);
		tmp&=(~0x01<<0);
		ReadWriteTF(TF_B,1,0x057,tmp);		
	// 下行输入			
		//退出校准，打开下行射频开关
		tmp=ReadWriteTF(TF_B,0,0x053,0x01);
		tmp&=~((0x01<<3)|(0x01<<5));			
		ReadWriteTF(TF_B,1,0x053,tmp);		
		
		ReadWriteTF(TF_B,1,0X56,0X00);//打开上行，输出通道、
		
	} 
	else if ( SYS_C_FLAG == ab_flag )
	{
		data=0x0b;
		reg= FPGA_REG_C_ATT_CTL;
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0);		// 设置通道号
		FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_L_12, 0x8000);
 		FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_H_14, 0x0000);
		
		FpgaWriteRegister(FPGA_REC_C_TD_WORK_MODE, TD_WM_NORMAL);
		sys_param_1b[MADD_C_TD_WORK_MODE].val = TD_WM_NORMAL;
		FPGA_DISABLE_WRITE;		
		
		//退出校准上行时，打开上行射频开关
		tmp=ReadWriteTF(TF_C,0,0x057,0x01);
		tmp&=(~0x01<<1);
		ReadWriteTF(TF_C,1,0x057,tmp);		
	// 下行输入			
		//退出校准，打开下行射频开关
		tmp=ReadWriteTF(TF_C,0,0x053,0x01);
		tmp&=~((0x01<<3)|(0x01<<5));			
		ReadWriteTF(TF_C,1,0x053,tmp);	
		ReadWriteTF(TF_C,1,0X56,0X00);//打开上行，输出通道、
				
	} 
	else if ( SYS_D_FLAG == ab_flag )
	{
		data=0x0b;
		reg= FPGA_REG_D_ATT_CTL;

		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0);		// 设置通道号
		FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_L_12, 0x8000);
 		FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_H_14, 0x0000);
		
		FpgaWriteRegister(FPGA_REC_D_TD_WORK_MODE, TD_WM_NORMAL);
		sys_param_1b[MADD_D_TD_WORK_MODE].val = TD_WM_NORMAL;
		FPGA_DISABLE_WRITE;
		//退出校准上行时，打开上行射频开关
		tmp=ReadWriteTF(TF_D,0,0x057,0x01);
		tmp&=(~0x01<<0);
		ReadWriteTF(TF_D,1,0x057,tmp);		
	// 下行输入			
		//退出校准，打开下行射频开关
		tmp=ReadWriteTF(TF_D,0,0x053,0x01);
		tmp&=~((0x01<<2)|(0x01<<4));			
		ReadWriteTF(TF_D,1,0x053,tmp);		

		ReadWriteTF(TF_D,1,0X56,0X00);//打开上行，输出通道、

	} 
	// 退出校准模式
	tmp = FpgaReadRegister(reg);
	
	tmp &= (~(ATT_MODE_MASK|ATT_MANUAL)); //自动ATT衰减  
	tmp |= ATT_MODE_NORMAL;  //ATT正常工作模式   
	
	FPGA_ENABLE_WRITE;  
	FpgaWriteRegister(reg, tmp);
	 
	if(SYS_D_FLAG == ab_flag)
	{
		ab_flag=SYS_C_FLAG ;
	}
	FPGA_DISABLE_WRITE;
	ReadWriteTF(ab_flag,1,0x0FB,data);

#if 0
	FPGA_ENABLE_WRITE;
//	if ( 0==p_args[1] )  
//	{	// 上行输出
		//校准上行时，打开上行射频开关
		tmp=ReadWriteTF(TF_C,0,0x057,0x01);
		tmp&=(~0x01<<1);
		ReadWriteTF(TF_C,1,0x057,tmp);	
//	}    
//	else 
//	{	// 下行输入
				
		//校准下行时关上行射频开关，打开下行射频开关
		tmp=ReadWriteTF(TF_C,0,0x057,0x01);
		tmp|=(0x01<<1);
		ReadWriteTF(TF_C,1,0x057,tmp);
 
		tmp=ReadWriteTF(TF_C,0,0x053,0x01);
		tmp&=~((0x01<<3)|(0x01<<5));
			
		ReadWriteTF(TF_C,1,0x053,tmp);				
//	}
	FPGA_DISABLE_WRITE;
#endif 	
	// 重新根据参数配置FPGA寄存器
	module_param_chg_flag = 0xFFFFFFFF;

}

/*************************************************************
Name:         FpgaSetTempAdjustTable
Description:  向FPGA写入温度补偿表格
Input:        void 
Output:       void
Return:       void 
**************************************************************/
void FpgaSetTempAdjustTable()
{
	UINT16 w_len, tmp;
	UCHAR8 i;
	UCHAR8 *p_flash_page = sys_temp_buff;

	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_A_FT_CMPS, DEFAULT_T_CMPS);
	FpgaWriteRegister(FPGA_REG_A_BT_CMPS, DEFAULT_T_CMPS);
	 	
	FpgaWriteRegister(FPGA_REG_B_FT_CMPS, DEFAULT_T_CMPS);
	FpgaWriteRegister(FPGA_REG_B_BT_CMPS, DEFAULT_T_CMPS);

	FpgaWriteRegister(FPGA_REG_C_FT_CMPS, DEFAULT_T_CMPS);
	FpgaWriteRegister(FPGA_REG_C_BT_CMPS, DEFAULT_T_CMPS);
	 	
	FpgaWriteRegister(FPGA_REG_D_FT_CMPS, DEFAULT_T_CMPS);
	FpgaWriteRegister(FPGA_REG_D_BT_CMPS, DEFAULT_T_CMPS);	
	FPGA_DISABLE_WRITE;
	 
	WTD_CLR;  
}
 
/*************************************************************
Name:       FpgaSaveAdjustTable
Description:将表格保存到FLASH中
Input:
	p_data:数据指针
	att_count: 衰减器个数
	ab_flag: AB段选择
	ud_flag: 1-上行，0-下行
Output:void
Return:0:失败1:成功
**************************************************************/
UCHAR8 FpgaSaveAdjustTable(UCHAR8 *p_data, UCHAR8 att_count, UCHAR8 ab_flag, UCHAR8 ud_flag )
{
	UINT32 page,page1,write_byte;
	UINT16 w_len;
	UCHAR8 att_no,i;
	UCHAR8 * buff = sys_temp_buff;
//	UCHAR8 p_dat_buff[1056];
//	UCHAR8 p_dat_buffssss[256];
//	UCHAR8 p_dat_buff11[10]={0,1,2,4,5,6,7,8,9};

	if ( ud_flag>1 )
	{
		return 0;
	}  

	if ( SYS_A_FLAG==ab_flag )
	{
		if ( 0==ud_flag )
		{
			page = FLASH_A_DL_ATT_ADJ_TBL_PAGE;
		}
		else
		{
			page = FLASH_A_UL_ATT_ADJ_TBL_PAGE;
		}
	}
	else if ( SYS_B_FLAG==ab_flag )
	{
		if ( 0==ud_flag )
		{
			page = FLASH_B_DL_ATT_ADJ_TBL_PAGE;
		}
		else
		{
			page = FLASH_B_UL_ATT_ADJ_TBL_PAGE;
		}
	}
	else if ( SYS_C_FLAG==ab_flag )
	{
		if ( 0==ud_flag )
		{
			page = FLASH_C_DL_ATT_ADJ_TBL_PAGE;
		}
		else
		{
			page = FLASH_C_UL_ATT_ADJ_TBL_PAGE;
		}
	}
	else if ( SYS_D_FLAG==ab_flag )
	{
		if ( 0==ud_flag )
		{
			page = FLASH_D_DL_ATT_ADJ_TBL_PAGE;
		}
		else
		{
			page = FLASH_D_UL_ATT_ADJ_TBL_PAGE;
		}
	}
	else
	{
		return 0;
	}
	page1=page;
	TRACE_INFO("Msg FpgaSaveAdjustTable,page=0x%02X=[%d],\r\n",page,page);

	buff[0] = 0xEC;
	buff[1] = 0x69;
	
	w_len = 2;

	buff[w_len++] = att_count;
	
	for ( att_no=0; att_no<att_count; att_no++ )
	{
		for ( i=0; i<64; i++ )
		{
			buff[w_len++] = *p_data++;
			buff[w_len++] = *p_data++;
		}  
	}

	// Ginp, 4字节, 浮点数
	for ( i=0; i<4; i++ )
	{
		buff[w_len++] = *p_data++;
	}

	// Gcic, 4字节, 浮点数
	for ( i=0; i<4; i++ )
	{
		buff[w_len++] = *p_data++;
	}

    TRACE_INFO("Msg Handle_Set_Tbl_type111:w_len:%d\r\n",w_len);

	for(i=0;i<20;i++)
	{		
		if(0==(i%100))
		WTD_CLR;
		TRACE_INFO("%02X ",buff[i]);
	}
	TRACE_INFO("\r\n");
	
	while(w_len)
	{		
		write_byte=w_len>FLASH_PAGE_SIZE?FLASH_PAGE_SIZE:w_len;
		FlashWrite( page,0, buff, write_byte, 1);
		buff+=write_byte;
		w_len-=write_byte;
		page++;
	}


#if 0
	FlashRead(page1, 0, p_dat_buff ,FLASH_PAGE_SIZE);
	TRACE_INFO("Msg Handle_Set_Tbl_type222:FLASH_PAGE_SIZE;%d\r\n",FLASH_PAGE_SIZE);
	for(i=0;i<20;i++)
	{
		
		if(0==(i%10))
		WTD_CLR;
	    TRACE_INFO("%02X ",p_dat_buff[i]);
	}
	TRACE_INFO("\r\n");
#endif

#if 0
	//p_dat_buff
	page=FLASH_C_DL_ATT_ADJ_TBL_PAGE;
	FlashDisableWriteProtect(); 
	FlashWriteWithinpage( page,0, p_dat_buff11, 10, 1);
	FlashEnableWriteProtect(); 

	TRACE_INFO("test-----\r\n");
	FlashRead(page, 0, p_dat_buffssss ,10);
	for(i=0;i<10;i++)
	{
		
		if(0==(i%100))
		WTD_CLR;
	    TRACE_INFO("%02X ",p_dat_buffssss[i]);
	}
	TRACE_INFO("\r\n");
#endif	
	
	WTD_CLR;       
 
TRACE_INFO("return1");
	return 1;
	
}

/*************************************************************
Name:        FpgaSetGsmBW
Description: 设置GSM的带宽
Input:       BW - 带宽标志
Output:      void         
Return:      void
**************************************************************/
void FpgaSetGsmBW( UCHAR8 bw )
{
	if ( bw > 3 ) return;

	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_GSM_BW_SEL, bw );
	FPGA_DISABLE_WRITE; 
}    

/*************************************************************
Name: CalcGsmFreqWord
Description: 根据GSM频点号计算频率字，REC按下行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
//NT32 CalcGsmFreqWord( INT32 freq_code, FLOAT32 fd_local )
INT32 SearchFpCalcGsmFreqWord( INT32 freq_code, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   
/*------------下行----------------*/	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
    freq_point = ConvGsmFcToFreqDL(freq_code);
	TRACE_INFO("<fp=%f, ful=%f>\r\n", freq_point, down_fre);

	TRACE_INFO("GSM_(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val[d=%d][f/1000=%f],fu_local=%f\r\n",(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val,(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/1000.0,down_fre);	
	
	//down_fre +=(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/10000.0;

	TRACE_INFO("freq_point = %f,fu_local=[%f]\r\n",freq_point,down_fre);
	

	// 计算数字本震频率    
	digit_freq = CalcGsmdfu( freq_point, 10*down_fre); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	freq_word = CalcFpgaFw_AB( digit_freq )/10.0;  
	*down_fre_word=freq_word;
	if(freq_point<10*down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	
/*------------上行----------------*/	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
    freq_point = ConvGsmFcToFreqUL(freq_code);
	TRACE_INFO("<fp=%f, ful=%f>\r\n", freq_point, up_fre);

	TRACE_INFO("GSM_(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val[d=%d][f/1000=%f],fu_local=%f\r\n",(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val,(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/1000.0,up_fre);	
	
	up_fre +=(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/10000.0;

	TRACE_INFO("freq_point = %f,fu_local=[%f]\r\n",freq_point,up_fre);
	
	// 计算数字本震频率    
	digit_freq = CalcGsmdfu( freq_point, 10*up_fre); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	*up_fre_word = CalcFpgaFw_AB( digit_freq )/10.0;
	if(freq_point<10*up_fre)
	{
		*up_fre_word |=0x80000000;
	}
		
	TRACE_INFO("*down_fre_word = %08x\r\n",*up_fre_word);  
   
	
	return freq_word;//AdjustFpgaFw(freq_word); 
	
}


/*************************************************************
Name: CalcGsmFreqWord
Description: 根据GSM频点号计算频率字，REC按下行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
//NT32 CalcGsmFreqWord( INT32 freq_code, FLOAT32 fd_local )
INT32 CalcGsmFreqWord( INT32 freq_code,  FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   

	
	printf("freq_code = %d,up_fre=[%f],down_fre = %f\r\n",freq_code,up_fre,down_fre);
/*------------下行----------------*/	
	
	freq_point = ConvGsmFcToFreqDL(freq_code);
	printf("freq_point = %f\r\n",freq_point);	

	// 计算数字本震频率    
	digit_freq = CalcGsmdfu( freq_point, 10*down_fre); 
	printf("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//freq_word = CalcFpgaFw_AB( digit_freq )/10.0; 
	freq_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10.0;
	printf("freq_word = %02x\r\n",freq_word);  
	
	*down_fre_word=freq_word;
	if(freq_point<10*down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	
	printf("down_fre_word = %02x\r\n",*down_fre_word);  
	
/*------------上行----------------*/	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	freq_point = ConvGsmFcToFreqUL(freq_code);
	printf("freq_point = %f\r\n",freq_point);
	
	// 计算数字本震频率    
	digit_freq = CalcGsmdfu( freq_point, 10*up_fre); 
	
	printf("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*up_fre_word = CalcFpgaFw_AB( digit_freq )/10.0;
	
	freq_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10.0;

	*up_fre_word=freq_word;
		
	printf("*up_fre_word = %08x\r\n",*up_fre_word);  
	
	if(freq_point<10*up_fre)
	{
		*up_fre_word |=0x80000000;
	}
		
	printf("*up_fre_word = %08x\r\n",*up_fre_word);  
   
	
	return freq_word;//AdjustFpgaFw(freq_word); 
	
}
#if 0
/*************************************************************
Name: CalcGsmFreqWord
Description: 根据GSM频点号计算频率字，RE按上行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcDcsFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   
	
	if (!VAL_IN_RANGE( freq_code, 512, 885 ))
	{
		return 0;
	} 

	freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1805;
   TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, fu_local); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, fu_local); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	freq_word = CalcFpgaFw_AB( digit_freq );   
	TRACE_INFO("freq_word = %08x\r\n",freq_word);  
	return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}
#endif 
/*************************************************************
Name: CalcGsmFreqWord
Description: 根据GSM频点号计算频率字，RE按上行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcDcsFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   
	
	if (!VAL_IN_RANGE( freq_code, DCS_MIN_FRE_CODE_CNMOBILE, 885 ))
	{
		return 0;
	} 
/*--------------下行------------------------*/
	freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;
   TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, down_fre*10); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*down_fre_word = CalcFpgaFw_A( digit_freq )/10; 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10;
    TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<10*down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------上行------------------------*/
	freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1710*10;
   TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, up_fre*10); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*up_fre_word = CalcFpgaFw_A( digit_freq )/10; 
	*up_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10;
	if(freq_point<10*up_fre)
	{
		*up_fre_word |=0x80000000;
	}
	TRACE_INFO("up_freq_word = %08x\r\n",*up_fre_word); 	
	//return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}
/*************************************************************
Name: WcdmaFreqWordConfigureadTxRxPll
Description: 根据WCDMAplloutputfreq配置9363
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 WcdmaFreqWordConfigureTxRxPll( FLOAT32 up_fre,  FLOAT32 down_fre)
{
	FLOAT32 tmp,tmp1;
	UINT32 data;
	

	ReadWriteTF(TF_A,1,0X014,0X03);		 //芯片进入等待模式（此时芯片无输出）
	
	ReadWriteTF(TF_A,1,0X5,0X11);
	tmp=down_fre*100*pow(2,2);
	TRACE_INFO("tmp=%f,down_fre=%f\r\n",tmp,down_fre);
	
	//tmp/=62.5;
	//tmp/=50;
	if(version_number == VERSION_40M_IN_D)
		tmp/=(156.25/7*2);
	else  if(version_number == VERSION_50M_IN_V5)
	{
		tmp/=62.5;
	}
	TRACE_INFO("tmp=%f\r\n",tmp);

//	tmp=(plloutputfreq*1000000*pow(2,2)/62.5);
//	tmp/=1000000.000000;
	TRACE_INFO("tmp=%f\r\n",tmp);

//	tmp=(plloutputfreq*pow(2,2)/62.5);
	//rx
	tmp1=(FLOAT32)((tmp-((INT32)tmp)/10000*10000)*8388593);	
	//TRACE_INFO("0data = %08x,tmp1=%f,((INT32)tmp)/10000*10000= %d,plloutputfreq=%f,(tmp-((INT32)tmp)/10000*10000)=%f\r\n",data,tmp1,((INT32)tmp)/10000*10000,down_fre,(tmp-((INT32)tmp)/10000*10000));
	data=(UINT32)((INT32)(tmp1/10000));
	TRACE_INFO("data=%X\r\n",data);

	ReadWriteTF(TF_A,1,0X233,(data&0X0FF) );
	ReadWriteTF(TF_A,1,0X234,(UCHAR8)((data&0X0ff00)>>8) );
	ReadWriteTF(TF_A,1,0X235,(UCHAR8)((data&0X07F0000)>>16) );	
	data=(UINT32)((INT32)tmp/10000);
	//TRACE_INFO("1data = %08x,tmp=%f,(INT32)tmp= %08x,\r\n",data,tmp,(INT32)tmp);
	ReadWriteTF(TF_A,1,0X232,(data&0X0700)>>8 );
	ReadWriteTF(TF_A,1,0X231,(data&0X0FF) );
	UsNopDelay(500);
	//plloutputfreq*=100;
	//plloutputfreq=(FLOAT32)((INT32)plloutputfreq-19000);	
	//TRACE_INFO("plloutputfreq=%f\r\n",plloutputfreq);	
	//tmp=(plloutputfreq*1000*pow(2,2)/62.5);
	if(version_number == VERSION_40M_IN_D)
	{
		tmp=(up_fre*100*pow(2,2)/(156.25/7*2));
	}
	else  if(version_number == VERSION_50M_IN_V5)
	{
		tmp=(up_fre*100*pow(2,2)/62.5);
	}
	tmp1=(FLOAT32)((tmp-((INT32)tmp/10000*10000))*8388593);
	data=(UINT32)((INT32)(tmp1/10000));
	//data=((tmp-((INT32)tmp/10000*10000))*8388593);
	TRACE_INFO("2data = %08x,tmp=%f,tmp1= %08x,\r\n",data,tmp,tmp1);
	ReadWriteTF(TF_A,1,0X273,(data&0X0FF) );
	ReadWriteTF(TF_A,1,0X274,(UCHAR8)((data&0Xff00)>>8) );
	ReadWriteTF(TF_A,1,0X275,(UCHAR8)((data&0X007F0000)>>16) );	

	data=(UINT32)((INT32)tmp/10000);
	//TRACE_INFO("1WcdmaFreqWordConfigureTxRxPll---------tmp=%f,up_fre=%f,data = %08x\r\n",tmp,up_fre,data); 	
	//tx
	ReadWriteTF(TF_A,1,0X272,(data&0X0700)>>8 );
	ReadWriteTF(TF_A,1,0X271,(data&0X0FF) );
	UsNopDelay(500);
	ReadWriteTF(TF_A,1,0X014,0X23);		 //配置完成后芯片进入正常工作状态。	

	return 0;
}

/*************************************************************
Name: LteFddFreqWordConfigureTxRxPllFreqWordConfigureadTxRxPll
Description: 根据LTEFDDplloutputfreq配置9363
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 LteTdFreqWordConfigureTxRxPll( FLOAT32 plloutputfreq ,UCHAR8 flag)
{
	FLOAT32 tmp,tmp1;
	UINT32 data;
	CHAR8 abcd_flag;
	UCHAR8 data1;	
	abcd_flag=flag;	
	if(TF_D ==abcd_flag)
	{
		abcd_flag=TF_C ;
		TRACE_INFO("abcd_flag=%d\r\n",abcd_flag);
	}
	
	TRACE_INFO("TDD_(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val[d=%d][f=%f],plloutputfreq=%f\r\n",(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val,(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/100.0,plloutputfreq);	
	plloutputfreq +=(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/100.0;


	ReadWriteTF(abcd_flag,1,0X014,0X03);		 //芯片进入等待模式（此时芯片无输出）
	
	ReadWriteTF(abcd_flag,1,0X5,0X11);
	tmp=plloutputfreq*100*pow(2,2);
	TRACE_INFO("tmp=%f,plloutputfreq=%f,abcd_flag=%d\r\n",tmp,plloutputfreq,abcd_flag);
	
	//tmp/=62.5;
	//if(version_number == VERSION_50M_IN_F ||version_number == VERSION_50M_IN_V4)
	//{
		tmp/=62.5;
	//}

	TRACE_INFO("tmp=%f\r\n",tmp);

//	tmp=(plloutputfreq*1000000*pow(2,2)/62.5);
//	tmp/=1000000.000000;
	TRACE_INFO("tmp=%f\r\n",tmp);

//	tmp=(plloutputfreq*pow(2,2)/62.5);
	//rx
	tmp1=(FLOAT32)((tmp-((INT32)tmp)/10000*10000)*8388593);	
	TRACE_INFO("0data = %08x,tmp1=%f,((INT32)tmp)/10000*10000= %d,plloutputfreq=%f,(tmp-((INT32)tmp)/10000*10000)=%f\r\n",data,tmp1,((INT32)tmp)/10000*10000,plloutputfreq,(tmp-((INT32)tmp)/10000*10000));
	data=(UINT32)((INT32)(tmp1/10000));
	TRACE_INFO("data=%X,H7data=%X,M8data=%X,L8data=%X\r\n",data,(UCHAR8)((data&0X07F0000)>>16),(UCHAR8)((data&0X0ff00)>>8),(data&0X0FF));

	data1=(UCHAR8)(data&0X0FF);
	TRACE_INFO("0x233data1=%X\r\n",data1);
	ReadWriteTF(abcd_flag,1,0X233,data1 );
	//UsNopDelay(1000);
	TRACE_INFO("1x233data1=%X\r\n",ReadWriteTF(abcd_flag,0,0X233,data1 ));
	data1=(UCHAR8)((data&0X0ff00)>>8);
	TRACE_INFO("0x234data1=%X\r\n",data1);	
	ReadWriteTF(abcd_flag,1,0X234,data1 );

	data1=(UCHAR8)((data&0X07F0000)>>16);
	TRACE_INFO("0x235data1=%X\r\n",data1);	
	ReadWriteTF(abcd_flag,1,0X235,data1 );	

	data=(UINT32)((INT32)tmp/10000);
	TRACE_INFO("1data = %08x,H3data = %08x,L8data = %08x,tmp=%f,(INT32)tmp= %08x,\r\n",data,(data&0X0700)>>8,(data&0X0FF),tmp,(INT32)tmp);
	ReadWriteTF(abcd_flag,1,0X232,(data&0X0700)>>8 );
	//ReadWriteTF(abcd_flag,1,0X232,(data&0Xff00)>>8 );	
	ReadWriteTF(abcd_flag,1,0X231,(data&0X0FF) );

	UsNopDelay(10*1000);
	
	//plloutputfreq*=100;
	//plloutputfreq=(FLOAT32)((INT32)plloutputfreq-9500);	
	TRACE_INFO("plloutputfreq=%f\r\n",plloutputfreq);	
	//tmp=(plloutputfreq*1000*pow(2,2)/62.5);
	//if(version_number == VERSION_50M_IN_F ||version_number == VERSION_50M_IN_V4)
	tmp=(plloutputfreq*100*pow(2,2)/62.5);
	
	tmp1=(FLOAT32)((tmp-((INT32)tmp/10000*10000))*8388593);
	data=(UINT32)((INT32)(tmp1/10000));
	//data=((tmp-((INT32)tmp/10000*10000))*8388593);
	TRACE_INFO("2data = %08x,tmp=%f,tmp1= %08x,\r\n",data,tmp,tmp1);
	ReadWriteTF(abcd_flag,1,0X273,(data&0X0FF) );
	ReadWriteTF(abcd_flag,1,0X274,(UCHAR8)((data&0Xff00)>>8) );
	ReadWriteTF(abcd_flag,1,0X275,(UCHAR8)((data&0X007F0000)>>16) );	

	data=(UINT32)((INT32)tmp/10000);
	TRACE_INFO("LteFddFreqWordConfigureTxRxPll---------tmp=%f,plloutputfreq=%f,data = %08x\r\n",tmp,plloutputfreq,data); 	
	//tx
	ReadWriteTF(abcd_flag,1,0X272,(data&0X0700)>>8 );
	ReadWriteTF(abcd_flag,1,0X271,(data&0X0FF) );
	UsNopDelay(10*1000);

	ReadWriteTF(abcd_flag,1,0X014,0X23);		 //配置完成后芯片进入正常工作状态。	

	ReadWriteTF(abcd_flag,1,0X53,0Xff);		 //	
	UsNopDelay(1*1000);
	ReadWriteTF(abcd_flag,1,0X53,0X00);		 //	

//	TRACE_INFO("1x233data1=%X\r\n",ReadWriteTF(abcd_flag,0,0X233,data1 ));

	return 0;
}

/*************************************************************
Name: LteFddFreqWordConfigureTxRxPllFreqWordConfigureadTxRxPll
Description: 根据LTEFDDplloutputfreq配置9363
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 LteFddFreqWordConfigureTxRxPll( FLOAT32 plloutputfreq ,UCHAR8 flag)
{
	FLOAT32 tmp,tmp1;
	UINT32 data;
	CHAR8 abcd_flag;
	abcd_flag=flag;	

	if(TF_D ==abcd_flag)
	{
		abcd_flag=TF_C ;
		TRACE_INFO("abcd_flag=%d\r\n",abcd_flag);
	}	

	TRACE_INFO("FDD_(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val[d=%d][f=%f],plloutputfreq=%f\r\n",(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val,(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/100.0,plloutputfreq);	
	plloutputfreq +=(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/100.0;
	
	ReadWriteTF(abcd_flag,1,0X014,0X03);		 //芯片进入等待模式（此时芯片无输出）
	
	ReadWriteTF(abcd_flag,1,0X5,0X11);
	tmp=plloutputfreq*100*pow(2,2);
	TRACE_INFO("tmp=%f,plloutputfreq=%f,abcd_flag=%d\r\n",tmp,plloutputfreq,abcd_flag);
	
	//tmp/=62.5;
	if( version_number==VERSION_40M_IN_D)
	{
		tmp/= (156.25/7*2);
	}
	else if( version_number==VERSION_40M_IN_D)
	{
		tmp/=50;
	}
	else if( version_number==VERSION_50M_IN_V5)
	{
		tmp/=62.5;
	}
	TRACE_INFO("tmp=%f\r\n",tmp);

//	tmp=(plloutputfreq*1000000*pow(2,2)/62.5);
//	tmp/=1000000.000000;
	TRACE_INFO("tmp=%f\r\n",tmp);

//	tmp=(plloutputfreq*pow(2,2)/62.5);
	//rx
	tmp1=(FLOAT32)((tmp-((INT32)tmp)/10000*10000)*8388593);	
	TRACE_INFO("0data = %08x,tmp1=%f,((INT32)tmp)/10000*10000= %d,plloutputfreq=%f,(tmp-((INT32)tmp)/10000*10000)=%f\r\n",data,tmp1,((INT32)tmp)/10000*10000,plloutputfreq,(tmp-((INT32)tmp)/10000*10000));
	data=(UINT32)((INT32)(tmp1/10000));
	TRACE_INFO("data=%X\r\n",data);

	ReadWriteTF(abcd_flag,1,0X233,(data&0X0FF) );
	ReadWriteTF(abcd_flag,1,0X234,(UCHAR8)((data&0X0ff00)>>8) );
	ReadWriteTF(abcd_flag,1,0X235,(UCHAR8)((data&0X07F0000)>>16) );	
	data=(UINT32)((INT32)tmp/10000);
	TRACE_INFO("1data = %08x,tmp=%f,(INT32)tmp= %08x,\r\n",data,tmp,(INT32)tmp);
	ReadWriteTF(abcd_flag,1,0X232,(data&0X0700)>>8 );
	ReadWriteTF(abcd_flag,1,0X231,(data&0X0FF) );

	UsNopDelay(10*1000);
	
	ReadWriteTF(abcd_flag,1,0X53,0Xff);		 //配置完成后芯片进入正常工作状态。	
	UsNopDelay(1*1000);
	ReadWriteTF(abcd_flag,1,0X53,0X00);		 //配置完成后芯片进入正常工作状态。	

	//plloutputfreq*=100;
	if ( VAL_IN_RANGE(plloutputfreq, 2110*100, 2170*100) )//CMDA2100
	{

		plloutputfreq=(FLOAT32)(plloutputfreq-19000);
	}
	else								//CMDA1800
	{
		plloutputfreq=(FLOAT32)(plloutputfreq-9500);
	}
	TRACE_INFO_WP("FddFreqWordConfigure_plloutputfreq=%f\r\n",plloutputfreq);	
	//tmp=(plloutputfreq*1000*pow(2,2)/62.5);
	if( version_number==VERSION_40M_IN_D)
	{
		tmp=(plloutputfreq*100*pow(2,2)/(156.25/7*2));
	}
	else if( version_number==VERSION_50M_IN_V5)
	{
		tmp=(plloutputfreq*100*pow(2,2)/62.5);
	}
	tmp1=(FLOAT32)((tmp-((INT32)tmp/10000*10000))*8388593);
	data=(UINT32)((INT32)(tmp1/10000));
	//data=((tmp-((INT32)tmp/10000*10000))*8388593);
	TRACE_INFO("2data = %08x,tmp=%f,tmp1= %08x,\r\n",data,tmp,tmp1);
	ReadWriteTF(abcd_flag,1,0X273,(data&0X0FF) );
	ReadWriteTF(abcd_flag,1,0X274,(UCHAR8)((data&0Xff00)>>8) );
	ReadWriteTF(abcd_flag,1,0X275,(UCHAR8)((data&0X007F0000)>>16) );	

	data=(UINT32)((INT32)tmp/10000);
	TRACE_INFO("LteFddFreqWordConfigureTxRxPll---------tmp=%f,plloutputfreq=%f,data = %08x\r\n",tmp,plloutputfreq,data); 	
	//tx
	ReadWriteTF(abcd_flag,1,0X272,(data&0X0700)>>8 );
	ReadWriteTF(abcd_flag,1,0X271,(data&0X0FF) );
	UsNopDelay(10*1000);

	ReadWriteTF(abcd_flag,1,0X014,0X23);		 //配置完成后芯片进入正常工作状态。	

	return 0;
}

/*************************************************************
Name: CalcGsmFreqWord
Description: 根据wcdma频点号计算频率字,
Input:
	void 
Output:        
Return:
	频率字
**************************************************************/
void CalcWcdmaPLLoutputFreq(FLOAT32 *up_fre,FLOAT32 *down_fre )
{
	FLOAT32 plloput_freq;	// 频率 
	UCHAR8 i=0,j=0;
	INT16 freq_code_min,freq_code_max;     

	for(i=0;i<sys_param_1b[MADD_A_CHANNEL_COUNT].val;i++)
	{
		if(1==sys_param_1b[MADD_A_DCH_EN1+i].val)
		{
			if(0==j)
			{
				freq_code_min=sys_param_2b[MADD_A_DL_CHANNEL1+i].val;
				freq_code_max=sys_param_2b[MADD_A_DL_CHANNEL1+i].val;
				j++;
			}
			if(sys_param_2b[MADD_A_DL_CHANNEL1+i].val<freq_code_min)
				freq_code_min=sys_param_2b[MADD_A_DL_CHANNEL1+i].val;
			if(sys_param_2b[MADD_A_DL_CHANNEL1+i].val>freq_code_max)
				freq_code_max=sys_param_2b[MADD_A_DL_CHANNEL1+i].val;			
		}
	}
	if(0==j)
	{
		freq_code_min=sys_param_2b[MADD_A_DL_CHANNEL1+0].val;
		freq_code_max=sys_param_2b[MADD_A_DL_CHANNEL1+0].val;
		
	}
	//上行频率
	if (((freq_code_max-freq_code_min)<15*5+25)&&((freq_code_max-freq_code_min)>15*5-1))
	{
		*up_fre = (FLOAT32)(freq_code_min+freq_code_max)*0.2*100/2 -190*100;
 		TRACE_INFO("CalcWcdmaPLLoutputFreq---(freq_code_max-freq_code_min)==15*5\r\n");		
	}
	else 
	{
		//*up_fre = (FLOAT32)(freq_code_min*0.2*100+244-190*100);
		*up_fre = (FLOAT32)(freq_code_min*0.2*100-190*100);
 		TRACE_INFO("CalcWcdmaPLLoutputFreq---(freq_code_max-freq_code_min)<15*5\r\n");
		
	}

	//下行频率
	//正常模式
	*down_fre = (FLOAT32)(freq_code_min+freq_code_max)*0.2*100/2;
	TRACE_INFO("up_fre = %f,down_fre = %f\r\n",*up_fre,*down_fre);
#if 0
	if(FpgaReadRegister(FPGA_REG_B_ATT_CTL)&0X03 == 0)
	{
		*down_fre = (FLOAT32)(freq_code_min+freq_code_max)*0.2*100/2;
	}
	//校准模式
	else
	{
		if (((freq_code_max-freq_code_min)<15*5+25)&&((freq_code_max-freq_code_min)>15*5-1))
		{
			*down_fre = (FLOAT32)(freq_code_min+freq_code_max)*0.2*100/2;
	 		TRACE_INFO("CalcWcdmaPLLoutputFreq---(freq_code_max-freq_code_min)==15*5\r\n");		
		}
		else 
		{
			*down_fre = (FLOAT32)(freq_code_min*0.2*100+244);
	 		TRACE_INFO("CalcWcdmaPLLoutputFreq---(freq_code_max-freq_code_min)<15*5\r\n");
		}

	}
#endif
//	plloput_freq=(FLOAT32)(freq_code_min+freq_code_max)*0.2/2;
 	TRACE_INFO("CalcWcdmaPLLoutputFreq---plloput_freq=[%0.4f],freq_code_min=[%X],freq_code_max=[%X]\r\n",plloput_freq,freq_code_min,freq_code_max);
 	
	//return ((FLOAT32)plloput_freq); 
	
}


/*************************************************************
Name: CalcGsmFreqWord
Description: 根据wcdma频点号计算频率字,
Input:
	void 
Output:        
Return:
	频率字
**************************************************************/
FLOAT32 CalcLteTdPLLoutputFreq(UCHAR8 flag)
{
	FLOAT32 plloput_freq;	// 频率 
	UCHAR8 i=0,j=0;
	INT32 freq_code_min,freq_code_max;     

	if(SYS_C_FLAG==flag )
	{
		for(i=0;i<sys_param_1b[MADD_C_CHANNEL_COUNT].val;i++)
		{
			if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
			|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C) 
			|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
			|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
			)
			{
				if(0==j)
				{
					freq_code_min=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
					freq_code_max=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
					j++;
				}
				if(sys_param_2b[MADD_C_DL_CHANNEL1+i].val<freq_code_min)
					freq_code_min=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
				if(sys_param_2b[MADD_C_DL_CHANNEL1+i].val>freq_code_max)
					freq_code_max=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;			
			}
			else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
			{
				if(1==sys_param_1b[MADD_C_DCH_EN1+i].val)
				{
					if(0==j)
					{
						freq_code_min=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
						freq_code_max=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
						j++;
					}
					if(sys_param_2b[MADD_C_DL_CHANNEL1+i].val<freq_code_min)
						freq_code_min=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
					if(sys_param_2b[MADD_C_DL_CHANNEL1+i].val>freq_code_max)
						freq_code_max=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;			
				}
			}
		}
		if(0==j)
		{
			freq_code_min=sys_param_2b[MADD_C_DL_CHANNEL1+0].val;
			freq_code_max=sys_param_2b[MADD_C_DL_CHANNEL1+0].val;
			j++;
			TRACE_INFO("C0freq_code_min=[%X],freq_code_max=[%X]\r\n",freq_code_min,freq_code_max);	
		}


		
	}else if(SYS_D_FLAG==flag  )
	{
		for(i=0;i<sys_param_1b[MADD_D_CHANNEL_COUNT].val;i++)
		{
			if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
			|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C) 
			|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
			|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
			)
			{
					if(0==j)
					{
						freq_code_min=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
						freq_code_max=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
						j++;
					}
					if(sys_param_2b[MADD_D_DL_CHANNEL1+i].val<freq_code_min)
						freq_code_min=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
					if(sys_param_2b[MADD_D_DL_CHANNEL1+i].val>freq_code_max)
						freq_code_max=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;		
			}	
			else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
			{
				if(1==sys_param_1b[MADD_D_DCH_EN1+i].val)
				{
					if(0==j)
					{
						freq_code_min=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
						freq_code_max=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
						j++;
					}
					if(sys_param_2b[MADD_D_DL_CHANNEL1+i].val<freq_code_min)
						freq_code_min=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
					if(sys_param_2b[MADD_D_DL_CHANNEL1+i].val>freq_code_max)
						freq_code_max=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;			
				}
			}
		}
		if(0==j)
		{
			freq_code_min=sys_param_2b[MADD_D_DL_CHANNEL1+0].val;
			freq_code_max=sys_param_2b[MADD_D_DL_CHANNEL1+0].val;
			j++;
			TRACE_INFO("d0freq_code_min=[%X],freq_code_max=[%X]\r\n",freq_code_min,freq_code_max);	
		}		
	}
	
	if(	(38650<=freq_code_min)&&(39649>=freq_code_min)&&(38650<=freq_code_max)&&(39649>=freq_code_max)	)//
	{
		//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	    //freq_point = 361+freq_code*0.025;
	   plloput_freq=(FLOAT32)((freq_code_min+freq_code_max)/2-38650)*100*0.1+2300*100;
		//TRACE_INFO("freq_point = %0.2f\r\n",freq_point);
	}else if(	(38250<=freq_code_min)&&(38649>=freq_code_min)&&(38250<=freq_code_max)&&(38649>=freq_code_max)	)//
	{
		//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	    //freq_point = 361+freq_code*0.025;
	   plloput_freq=(FLOAT32)((freq_code_min+freq_code_max)/2-38250)*100*0.1+1880*100;
		//TRACE_INFO("freq_point = %0.2f\r\n",freq_point);
	}
	else if(	(39650<=freq_code_min)&&(41589>=freq_code_min)&&(39650<=freq_code_max)&&(41589>=freq_code_max)	)//
	{
		//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
		//freq_point = 361+freq_code*0.025;
	   	plloput_freq=(FLOAT32)((freq_code_min+freq_code_max)/2-39650)*100*0.1+2496*100;
		//TRACE_INFO("freq_point = %0.2f\r\n",freq_point);
	}


	//固定本振
	if(version_number == VERSION_50M_IN_V4) //由固定本振变为动态本振 201601070950
	{
		//plloput_freq=2345*100;
		
	}
		
	//plloput_freq=(FLOAT32)((freq_code_min+freq_code_max)/2-38650)*100*0.1+100*2300;
 	TRACE_INFO("1freq_code_min=[%X],freq_code_max=[%X],plloput_freq=[%f]\r\n",freq_code_min,freq_code_max,plloput_freq);
	return ((INT32)plloput_freq); 
	
}


/*************************************************************
Name: CalcGsmFreqWord
Description: 根据wcdma频点号计算频率字,
Input:
	void 
Output:        
Return:
	频率字
**************************************************************/
FLOAT32 CalcLteFddPLLoutputFreq(UCHAR8 flag)
{
	FLOAT32 plloput_freq;	// 频率 
	UCHAR8 i=0,j=0;
	INT32 freq_code_min,freq_code_max;   
	INT32 freq_code; 

	if(SYS_C_FLAG==flag )
	{
		for(i=0;i<sys_param_1b[MADD_C_CHANNEL_COUNT].val;i++)
		{
			if(1==sys_param_1b[MADD_C_DCH_EN1+i].val)
			{
				if(0==j)
				{
					freq_code_min=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
					freq_code_max=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
					j++;
				}
				if(sys_param_2b[MADD_C_DL_CHANNEL1+i].val<freq_code_min)
					freq_code_min=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;
				if(sys_param_2b[MADD_C_DL_CHANNEL1+i].val>freq_code_max)
					freq_code_max=sys_param_2b[MADD_C_DL_CHANNEL1+i].val;			
			}
		}
		if(0==j)
		{
			freq_code_min=sys_param_2b[MADD_C_DL_CHANNEL1+0].val;
			freq_code_max=sys_param_2b[MADD_C_DL_CHANNEL1+0].val;
			j++;
		}
					//TRACE_INFO("C---freq_code_min=[%X],freq_code_max=[%X]\r\n",freq_code_min,freq_code_max);	
		
	}else if(SYS_D_FLAG==flag )
	{
		for(i=0;i<sys_param_1b[MADD_D_CHANNEL_COUNT].val;i++)
		{
			if(1==sys_param_1b[MADD_D_DCH_EN1+i].val)
			{
				if(0==j)
				{
					freq_code_min=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
					freq_code_max=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
					j++;
				}
				if(sys_param_2b[MADD_D_DL_CHANNEL1+i].val<freq_code_min)
					freq_code_min=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;
				if(sys_param_2b[MADD_D_DL_CHANNEL1+i].val>freq_code_max)
					freq_code_max=sys_param_2b[MADD_D_DL_CHANNEL1+i].val;			
			}
		}
		if(0==j)
		{
			freq_code_min=sys_param_2b[MADD_D_DL_CHANNEL1+0].val;
			freq_code_max=sys_param_2b[MADD_D_DL_CHANNEL1+0].val;
			j++;
		}		
				//	TRACE_INFO("D--freq_code_min=[%X],freq_code_max=[%X]\r\n",freq_code_min,freq_code_max);	
	}
	
	plloput_freq=(FLOAT32)((freq_code_min+freq_code_max)/2-1200)*100*0.1+100*1805;

	freq_code= (freq_code_min+freq_code_max)/2 ;
	if ( VAL_IN_RANGE(freq_code, 0, 599) )//CMDA800  fdd2100
	{
		plloput_freq = (FLOAT32)(freq_code-0)*0.1*100+2110*100;
	}
	else	 //CMDA800  fdd1800
	{
		plloput_freq = (FLOAT32)(freq_code-1200)*0.1*100+1805*100;
	}

	return ((FLOAT32)plloput_freq); 
	
}


/*************************************************************
Name: CalcGsmFreqWord
Description: 根据GSM频点号计算频率字，RE按上行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcWcdmaFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率 
	FLOAT32 digit_freq;	// 数字频率 
	INT32   freq_word;     

	//下行
	freq_point = freq_code*0.2*100;
	TRACE_INFO("freq_point = %f,fu_local= %f,freq_code=[%X]\r\n",freq_point,down_fre,freq_code);

	// 计算数字本震频率    
	if(freq_point>down_fre)
	{
			digit_freq = freq_point - down_fre;
			digit_freq = digit_freq/100; 
			//*down_fre_word = CalcFpgaFw_B( digit_freq );
			*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
			
	}
	else
	{
			digit_freq = down_fre - freq_point;
			digit_freq = digit_freq/100; 
			//*down_fre_word = CalcFpgaFw_B( digit_freq ); 
			*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
			*down_fre_word = *down_fre_word|0x80000000;
	}
	

	// 计算频率字    
	TRACE_INFO("freq_word = %08x\r\n",*down_fre_word);  
	//------------------------------------------------------//
	//上行
	freq_point = freq_code*0.2*100 -190*100;
	TRACE_INFO("freq_point = %f,fu_local= %f\r\n",freq_point,up_fre);

	// 计算数字本震频率    
	if(freq_point>up_fre)
	{
			digit_freq = freq_point - up_fre;
			digit_freq = digit_freq/100; 
			//*up_fre_word = CalcFpgaFw_B( digit_freq ); 
			*up_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);

	}
	else
	{
			digit_freq = up_fre - freq_point;
			digit_freq = digit_freq/100; 
			//*up_fre_word = CalcFpgaFw_B( digit_freq );  
			*up_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
			*up_fre_word = *up_fre_word|0x80000000;
	}
	TRACE_INFO("freq_word = %08x\r\n",*up_fre_word);  

	
}
/*************************************************************
Name: CalcGsmFreqWord
Description: 根据LteFdd频点号计算频率字,新的计算公式
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcWCDMAFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   

/*--------------下行------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;
	//freq_point = (FLOAT32)(freq_code-0) * 0.01 + 866;
	freq_point = freq_code*0.2;
	down_fre = down_fre/100.0;
	up_fre = up_fre/100.0;


	TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, down_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*down_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------上行------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1710;
	//freq_point = (FLOAT32)(freq_code-0) * 0.01 + 821;
	freq_point = freq_code*0.2 -190;
	TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, up_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*up_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*up_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	
	if(freq_point<up_fre)
	{
		*up_fre_word |=0x80000000;
	}
	TRACE_INFO("up_freq_word = %08x\r\n",*up_fre_word); 	
	//return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}

#if 0
/*************************************************************
Name: TdSysCalcGsmFreqWord
Description: 根据GSM频点号计算频率字，RE按上行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcTDFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// 频率 
	FLOAT32 digit_freq;	// 数字频率 
	INT32   freq_word;     
	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	freq_point = freq_code*0.2;
	if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN) 
	|| (version_number == VERSION_40M_IN_A) || (version_number == VERSION_40M_IN_E)
	|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
	)
		freq_point = 2017.5;
	//freq_point = 2010+(freq_code-36200)*0.1; 
	TRACE_INFO("CalcTDfreq_point = %.2f,ful=%f\r\n",freq_point, fu_local);

	// 计算数字本震频率    
	digit_freq = CalcWcdmafu( freq_point*10, fu_local*10); 
	TRACE_INFO("CalcTDdigit_freq = %.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	if(version_number == VERSION_40M_IN_A)
		freq_word = ((INT32)( (FLOAT32)pow(2,13)*1024*8*digit_freq*(7/156.25/4)))/10;  
	else
		freq_word = CalcFpgaFw_B( digit_freq )/10;	 
	TRACE_INFO("CalcTDfreq_word = %08x\r\n",freq_word);  
   
	if(freq_point< fu_local)
	{
		return (freq_word|0X80000000); //AdjustFpgaFw(freq_word); 
	}	
	else
	{
		return (freq_word);
	}
	
}
#endif
/*************************************************************
Name: CalcGsmFreqWord
Description: 根据LteFdd频点号计算频率字,新的计算公式
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcTDSCDMAFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   

/*--------------下行------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;
	//freq_point = (FLOAT32)(freq_code-0) * 0.01 + 866;
	freq_point = 2017.5;

	TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, down_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*down_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------上行------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1710;
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 821;
	TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, up_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*up_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*up_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	
	if(freq_point<up_fre)
	{
		*up_fre_word |=0x80000000;
	}
	TRACE_INFO("up_freq_word = %08x\r\n",*up_fre_word); 	
	//return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}


/*************************************************************
Name: CalcGsmFreqWord
Description: 根据GSM频点号计算频率字，RE按上行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 SearchFpCalcTDFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// 频率 
	FLOAT32 digit_freq;	// 数字频率 
	INT32   freq_word;     
	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
    freq_point = freq_code*0.2;
	//freq_point = 2010+(freq_code-36200)*0.1; 
	//TRACE_INFO("freq_point = %0.2f,fu_local=[%0.2f]\r\n",freq_point,fu_local);

	TRACE_INFO("TDS_(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val[d=%d][f/1000=%f],fu_local=%f\r\n",(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val,(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/100.0,fu_local);	
	
	fu_local +=(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/1000/10.0*2000/2300;

	TRACE_INFO("freq_point = %f,fu_local=[%f]\r\n",freq_point,fu_local);
	
	// 计算数字本震频率    
	digit_freq = CalcWcdmafu( freq_point*10, fu_local*10); 
    TRACE_INFO("digit_freq = %f\r\n",digit_freq);  
	  
	// 计算频率字    
	
	if(version_number == VERSION_40M_IN_A)
		freq_word = ((INT32)( (FLOAT32)pow(2,13)*1024*8*digit_freq*(7/156.25/4)))/10;  
	else
		freq_word = CalcFpgaFw_B( digit_freq )/10;	
		
    TRACE_INFO("digit_freq = %f\r\n",digit_freq); 	
 
   	if(freq_point< fu_local)
	{
		//TRACE_INFO("freq_word = %08x\r\n",freq_word); 
		return (freq_word|0X80000000); //AdjustFpgaFw(freq_word); 
	}	
	else
	{
		//TRACE_INFO("freq_word = %08x\r\n",freq_word); 
		return (freq_word);
	}
	
}

#if 0
/*************************************************************
Name: CalcGsmFreqWord
Description: 根据GSM频点号计算频率字，RE按上行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcTetraFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// 频率 
	FLOAT32 digit_freq;	// 数字频率 
	INT32   freq_word;     
	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	freq_point = 361+freq_code*0.0125;
	//TRACE_INFO("freq_point = %0.2f\r\n",freq_point);

	// 计算数字本震频率    
	digit_freq = CalcTdLtefu( freq_point, fu_local); 
	
	if(freq_point>fu_local)
	{
		digit_freq =   freq_point-fu_local; 
	}
	else  
	{
		digit_freq = fu_local-freq_point; 
	}
	 

	// 计算频率字    
	//freq_word = CalcFpgaFw_B( digit_freq );   

	freq_word = CalcFpgaFw_AB( digit_freq )/10.0;  	
	//TRACE_INFO("freq_word = %08x\r\n",freq_word);  


	return freq_word//AdjustFpgaFw(freq_word); 
	
}
#endif
INT32 CalcTetraFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   

	
	//printf("freq_code = %d,up_fre=[%f],down_fre = %f\r\n",freq_code,up_fre,down_fre);
	/*------------下行----------------*/	
	
	freq_point = 361+(freq_code-1)*0.0125;

	//printf("freq_point = %f\r\n",freq_point);

	

	// 计算数字本震频率    
	//digit_freq = CalcGsmdfu( freq_point, 10*down_fre); 
	//printf("digit_freq = %0.2f\r\n",digit_freq);
	if(freq_point>down_fre)
	{
		digit_freq =  freq_point-down_fre; 
	}
	else  
	{
		digit_freq =   down_fre-freq_point; 
	}
	  
	// 计算频率字    
	//*down_fre_word = CalcFpgaFw_AB( digit_freq );  
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	//printf("freq_word = %02x\r\n",freq_word);  
	
	//*down_fre_word=freq_word;
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	
	//printf("down_fre_word = %02x\r\n",*down_fre_word);  
	
	/*------------上行----------------*/	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	freq_point = 351+(freq_code-1)*0.0125;
	//printf("freq_point = %f\r\n",freq_point);
	
	// 计算数字本震频率    
	//digit_freq = CalcGsmdfu( freq_point, 10*up_fre); 
	if(freq_point>up_fre)
	{
		digit_freq =  freq_point-up_fre; 
	}
	else  
	{
		digit_freq =   up_fre-freq_point; 
	}
	//printf("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*up_fre_word = CalcFpgaFw_AB( digit_freq );
	*up_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	
	if(freq_point<up_fre)
	{
		*up_fre_word |=0x80000000;
	}
	//printf("*up_fre_word = %08x\r\n",*up_fre_word);  
	
	return 0;//AdjustFpgaFw(freq_word); 
	
}

#if 0
/*************************************************************
Name: 
Description: 
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcLteTdFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// 频率 
	FLOAT32 digit_freq;	// 数字频率 
	INT32   freq_word;     
	
	//TRACE_INFO("<freq_code=%f, ful=%f> ", freq_code, fu_local);
 //   freq_point = (freq_code-38650)*100*0.1+100*2300;
	//TRACE_INFO("freq_point = %0.2f\r\n",freq_point);
	if(	(38650<=freq_code)&&(39649>=freq_code) )//
	{
		freq_point = 100*2300+100*(freq_code-38650)*0.1;
		//TRACE_INFO("freq_point = %0.2f\r\n",freq_point);
	}else if (	(38250<=freq_code)&&(38649>=freq_code)	)
	{
	    freq_point = 100*1880+100*(freq_code-38250)*0.1;
		TRACE_INFO("38250_freq_point = %0.2f\r\n",freq_point);
	}
	else if (	(39650<=freq_code)&&(41589>=freq_code)	)
	{
		freq_point = 100*2496+100*(freq_code-39650)*0.1;
		TRACE_INFO("38250_freq_point = %0.2f\r\n",freq_point);
	}
	// 计算数字本震频率    
	digit_freq = CalcTdLtefu( freq_point, fu_local); 
    //TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	freq_word = CalcFpgaFw_CD( digit_freq )/100;   
	//TRACE_INFO("freq_word = %08x\r\n",freq_word);  
   
	if (freq_point<fu_local)
	{
		freq_word |=0x80000000;
	}
	
	return freq_word;// AdjustFpgaFw(freq_word); 
	
}
#endif
/*************************************************************
Name: CalcGsmFreqWord
Description: 根据LteFdd频点号计算频率字,新的计算公式
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcLteTddFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   

/*--------------下行------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 866;

	TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, down_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*down_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------上行------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1710;
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 821;
	TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, up_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*up_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*up_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	
	if(freq_point<up_fre)
	{
		*up_fre_word |=0x80000000;
	}
	TRACE_INFO("up_freq_word = %08x\r\n",*up_fre_word); 	
	//return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}

/*************************************************************
Name: 
Description: 
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcLteFddFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// 频率 
	FLOAT32 digit_freq;	// 数字频率 
	INT32   freq_word;     
	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
//    freq_point = (FLOAT32)(freq_code-1200)*0.1+1805;
    freq_point = (FLOAT32)(freq_code-1200)*100*0.1+100*1805;
	if ( VAL_IN_RANGE(freq_code, 0, 599) )//CMDA2100
	{
		freq_point = (FLOAT32)((freq_code-0)*100*0.1+100*2110);
	}
	else								//CMDA1800
	{
		freq_point = (FLOAT32)(freq_code-1200)*100*0.1+100*1805;
	}

	TRACE_INFO("111freq_point = %d,freq_code:%d\r\n",(INT32)freq_point,freq_code);

	// 计算数字本震频率    
	digit_freq = CalcWcdmafu( freq_point, fu_local); 
	//digit_freq =0.1;
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	freq_word = CalcFpgaFw_CD( digit_freq )/100;   
	TRACE_INFO("!!1freq_word = %d\r\n",freq_word);  
   
	if (freq_point<fu_local) freq_word |=0x80000000;	
	return freq_word;//AdjustFpgaFw(freq_word); 
	
}
/*************************************************************
Name: CalcGsmFreqWord
Description: 根据LteFdd频点号计算频率字,新的计算公式
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcLteFddFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   
	//if (!VAL_IN_RANGE(freq_code, 0, 1400))
	//{
	//	return 0;
	//} 
/*--------------下行------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;

	#if (defined CLIENT_ERRICSON2)
		
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 866;

	#elif defined CLIENT_ERRICSON_W

		freq_point = 2140;
	#else
	if(	(38650<=freq_code)&&(39649>=freq_code) )//
	{
		freq_point = 100*2300+100*(freq_code-38650)*0.1;
		//TRACE_INFO("freq_point = %0.2f\r\n",freq_point);
	}else if (	(38250<=freq_code)&&(38649>=freq_code)	)
	{
	    freq_point = 100*1880+100*(freq_code-38250)*0.1;
		TRACE_INFO("38250_freq_point = %0.2f\r\n",freq_point);
	}
	else if (	(39650<=freq_code)&&(41589>=freq_code)	)
	{
		freq_point = 100*2496+100*(freq_code-39650)*0.1;
		TRACE_INFO("38250_freq_point = %0.2f\r\n",freq_point);
	}
	#endif

	TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, down_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*down_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------上行------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1710;
	#if (defined CLIENT_ERRICSON2)
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 821;
	#elif defined CLIENT_ERRICSON_W

		freq_point = 1950;
	#endif
	TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// 计算数字本震频率     
	digit_freq = CalcDcsfu( freq_point, up_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*up_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*up_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	
	if(freq_point<up_fre)
	{
		*up_fre_word |=0x80000000;
	}
	TRACE_INFO("up_freq_word = %08x\r\n",*up_fre_word); 	
	//return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}

/*************************************************************
Name: CalcCdma800FreqWord
Description: 根据GSM频点号计算频率字，RE按上行的公式计算
Input:
	freq_code: 频点号
Output:void         
Return:
	频率字
**************************************************************/
INT32 CalcCdma800FreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// 频率
	FLOAT32 digit_freq;	// 数字频率
	INT32   freq_word;   
	
	if (!VAL_IN_RANGE( freq_code, 1, 333 ))
	{
		return 0;
	} 
/*--------------下行------------------------*/
	freq_point = (FLOAT32)(freq_code *10* 0.03 + 870*10);
//   TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// 计算数字本震频率     
	//digit_freq = CalcDcsdfu ( freq_point, down_fre*10); 
	digit_freq = 0*10; 
	*down_fre_word = 0;

	if(digit_freq<0)
	{
		digit_freq=(0-digit_freq);
		*down_fre_word |=( 0x1<<31);
	}
	
//    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*down_fre_word |= CalcFpgaFw_AB( digit_freq )/10;   
	*down_fre_word |= CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10;

	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------上行------------------------*/
	freq_point = (FLOAT32)(freq_code *10* 0.03 + 825*10);
//   TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// 计算数字本震频率     
	//digit_freq = CalcDcsfu( freq_point, up_fre*10); 
	digit_freq = 0*10; 

	*up_fre_word = 0;
	if(digit_freq<0)
	{
		digit_freq=(0-digit_freq);
		*up_fre_word |=( 0x1<<31);
	}


//    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// 计算频率字    
	//*up_fre_word |= CalcFpgaFw_AB( digit_freq )/10;   
	*up_fre_word |= CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10;

	TRACE_INFO("up_freq_word = %08x\r\n",*up_fre_word); 	
	//return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}

/*************************************************************
Name: FpgaSetTempComp
Params: [seg_sel: 0-A段, 1-B段] [udl_sel: 0-UL上行, 1-DL下行] [comp: 补偿寄存器的值]
Return: void
Description: 设置补偿寄存器的值
**************************************************************/
void FpgaSetTempComp( UCHAR8 seg_sel, UCHAR8 udl_sel, UINT16 comp )
{
	UINT16 reg_addr = 0xFFFF;

	// 根据选择确定寄存器地址
	if ( 0==seg_sel )	// A段
	{
		if ( 0==udl_sel )	// 上行
		{
			reg_addr = FPGA_REG_A_BT_CMPS;	// 后端
		}
		else if ( 1==udl_sel )	// 下行
		{
			reg_addr = FPGA_REG_A_FT_CMPS;	// 前端
		}
	}
	else if ( 1==seg_sel )	// B段
	{
		if ( 0==udl_sel )	// 上行
		{
			reg_addr = FPGA_REG_B_BT_CMPS;	// 后端
		}
		else if ( 1==udl_sel )	// 下行
		{
			reg_addr = FPGA_REG_B_FT_CMPS;	// 前端
		}
	}
	else if ( 2==seg_sel )	// C段
	{
		if ( 0==udl_sel )	// 上行
		{
			reg_addr = FPGA_REG_C_BT_CMPS;	// 后端
		}
		else if ( 1==udl_sel )	// 下行
		{
			reg_addr = FPGA_REG_C_FT_CMPS;	// 前端
		}
	}
	else if ( 3==seg_sel )	// D段
	{
		if ( 0==udl_sel )	// 上行
		{
			reg_addr = FPGA_REG_D_BT_CMPS;	// 后端
		}
		else if ( 1==udl_sel )	// 下行
		{
			reg_addr = FPGA_REG_D_FT_CMPS;	// 前端
		}
	}
	// 无效的地址选择
	if ( 0xFFFF==reg_addr ) return;

	// 写入寄存器
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( reg_addr, comp );
	FPGA_DISABLE_WRITE;
	
}


/*************************************************************
Name:          SentLoadDat      
Description:   串行发送加载数据
Input:         Dat - 发送的字节          
Output:        void           
Return:        void       
**************************************************************/
void SentLoadDatA7(UCHAR8 Dat)
{

#if 1
	UCHAR8 i; 
	//为加快逻辑加载
	//20151120逻辑加载直接操作寄存器地址
	//volatile unsigned long *DBSRR_SFR=GPIOD_SFR_BASE_SET; 
	//volatile unsigned long *DBRR_SFR=GPIOD_SFR_BASE_RESET; 
	volatile unsigned long *datBSRR_SFR=(unsigned long *)(GPIOD_BASE+0X10); 
	volatile unsigned long *datRR_SFR=(unsigned long *)(GPIOD_BASE+0X14); 
	volatile unsigned long *clkBSRR_SFR=(unsigned long *)(GPIOB_BASE+0X10); 
	volatile unsigned long *clkBRR_SFR=(unsigned long *)(GPIOB_BASE+0X14); 
	for (i = 0;i<8; i++ )
	{ 
		//20151120加载逻辑直接操作寄存器
		if ( (Dat>>(7-i))&0x01 )
		{
			*datBSRR_SFR = GPIO_Pin_13;
		}
		else  
		{ 
			*datRR_SFR = GPIO_Pin_13;
		} 
		*clkBRR_SFR = GPIO_Pin_3;	
		*clkBSRR_SFR = GPIO_Pin_3;
	}
#endif


#if 0
	char i; 
	for (i = 8;i>0; i-- )
	{
	    //UsNopDelay(20);			
		if ( (Dat>>(i-1))&0x01 )//高位在前
		{
		      SET_FPGA_DATA1_PIN;
		}
		else  
	    { 
	      CLR_FPGA_DATA1_PIN;
	    } 
		CLR_FPGA_CCLK_PIN; //201411061713 	
		//UsNopDelay(20);	
		SET_FPGA_CCLK_PIN; //201411061713 
	}

#endif
}

/*************************************************************
Name:FpgaLoadA7
Description:FPGA加载
Input:加载文件的总长度          
Output:void         
Return:-1:失败，1: 成功         
**************************************************************/
CHAR8 FpgaLoadA7(UINT32 len)
{
#if 1
 
	UINT32 page_index,ReadByteOneLoop;
	UINT32 i ,ReadNums; 
	UCHAR8 *p_flash_page = sys_temp_buff;
//	UCHAR8 retry = 100;
//	CHAR8 result;
	UCHAR8 serial_retry = 4; 
	UCHAR8 ucTmpDat= 0;
	
	CLR_FPGA_CS_PIN;      // FPGA片选脚   
	TRACE_DEBUG_WP("FpgaLoadAll enter\r\n");
	printf("\r\nCLR_FPGA_CS_PIN\r\n");

  
	//第一步
	SET_FPGA_PROGRAM_B_PIN;	
	printf("SET_FPGA_PROGRAM_B_PIN\r\n");
	i =0;
	//while(1);
	while(0==GET_FPGA_INIT_B_ST)
	{	
		i++;
		UsNopDelay(1000);
		//printf("FPGA_INIT_B_ST %x\r\n",GET_FPGA_INIT_B_ST);
		//printf("GET_FPGA_DONE_ST %x\r\n",GET_FPGA_DONE_ST);
		if(i>20)
		{
			TRACE_DEBUG_WP("FpgaLoad INIT_B_error1\r\n");
			printf("FpgaLoad INIT_B_error1\r\n");
			return -1;
		}
	}
	if(1==GET_FPGA_DONE_ST)
	{
		TRACE_DEBUG_WP("done_error1\r\n");
		printf("done_error1\r\n");
		return -1;
	}
	
	
	//第二步
	CLR_FPGA_PROGRAM_B_PIN;
	printf("CLR_FPGA_PROGRAM_B_PIN\r\n");
	WTD_CLR;
	UsNopDelay(2000);				//延时 20us   等待 FPGA_INIT_B_ST 拉低
	i =0;
	while(1==GET_FPGA_INIT_B_ST)
	{	
		i++;
		UsNopDelay(50);
		if(i>20)
		{
			TRACE_DEBUG_WP("FpgaLoad INIT_B_error2\r\n");
			return -1;
		}
	}
	if(1==GET_FPGA_DONE_ST)
	{
		TRACE_DEBUG_WP("done_error2\r\n");
		return -1;
	}
	
	//第三步
	SET_FPGA_PROGRAM_B_PIN;
	printf("SET_FPGA_PROGRAM_B_PIN\r\n");
	i =0;
	while(0==GET_FPGA_INIT_B_ST)
	{	
		i++;
		UsNopDelay(1000);
		if(i>20)
		{
			TRACE_DEBUG_WP("FpgaLoad INIT_B_error3\r\n");
			return -1;
		}
	}
	if(1==GET_FPGA_DONE_ST)
	{
		TRACE_DEBUG_WP("done_error3\r\n");
		return -1;
	}
	
	
	//第四步
	TRACE_INFO("FpgaLoad Start\r\n"); // ?????

	page_index = ( FPGA_LOAD_BLOCK1==fpga_load_block ) ? (FLASH_FPGA_PAGE_START1+1) : (FLASH_FPGA_PAGE_START2+1) ;

	TRACE_INFO("Start Page:%04X.\r\n", page_index);
	WTD_CLR;
	printf("Start Page:%04X.\r\n", page_index);	
	while( len )
	{


			
		//ReadByteOneLoop = len>(1056) ?(1056) : len;

		ReadByteOneLoop = len>(FLASH_PAGE_SIZE*4) ?(FLASH_PAGE_SIZE*4) : len;

		
		for(ReadNums=0;ReadNums<ReadByteOneLoop/FLASH_PAGE_SIZE;ReadNums++)
		{
			//FlashRead(SPI_CS_W25Q64_1, page_index+ReadNums, 0, p_flash_page+ReadNums*FLASH_PAGE_SIZE ,FLASH_PAGE_SIZE);
			FlashRead(page_index+ReadNums,0,p_flash_page+ReadNums*FLASH_PAGE_SIZE,FLASH_PAGE_SIZE);
	
		}
		if(ReadByteOneLoop%FLASH_PAGE_SIZE)
		{	
			//FlashRead(SPI_CS_W25Q64_1, page_index+ReadNums, 0, p_flash_page+ReadNums*FLASH_PAGE_SIZE ,ReadByteOneLoop%FLASH_PAGE_SIZE);
			FlashRead(page_index+ReadNums,0,p_flash_page+ReadNums*FLASH_PAGE_SIZE,FLASH_PAGE_SIZE);
			ReadNums++;
		}

	

		WTD_CLR;
		for (i=0; i<ReadByteOneLoop; i++)
		{ 
			ucTmpDat = *(p_flash_page+i);  
			SentLoadDatA7(ucTmpDat); 				  
		}
		len -= ReadByteOneLoop;				
		page_index +=ReadNums;


		if((page_index%20)== 0)
			FLASH_LED;
	}
	TRACE_INFO("load all\r\n");
	WTD_CLR;
   //加载完毕
	UsNopDelay(1000); 			//Delay 1ms 
	if (GET_FPGA_DONE_ST)  
	{     
		TRACE_INFO_WP("LOAD SUCCESS-0\r\n");
		printf("LOAD SUCCESS-0\r\n");
		
		SentLoadDatA7(0X00);		//dummy write
		SentLoadDatA7(0X00);		//dummy write
		CLR_FPGA_CCLK_PIN;
		UsNopDelay(1000);  
		return 1; 
	} 
	else
	{
		TRACE_INFO_WP("LOAD FAIL-1\r\n");
		printf("LOAD FAIL-1\r\n");
		UsNopDelay(5000);  
		while (serial_retry--)			  //?????CLK
		{	
			if (GET_FPGA_DONE_ST)
			{
				TRACE_INFO_WP("LOAD SUCCESS-0\r\n");
				printf("LOAD SUCCESS-0\r\n");
				SentLoadDatA7(0X00);		//dummy write
				SentLoadDatA7(0X00);		//dummy write


				CLR_FPGA_CCLK_PIN;

		        //????,??1ms??user mode 
				UsNopDelay(1000);  
				
				return 1; 		
			} 
			else
			{ 
				 printf("LOAD FAIL-2\r\n");
			}  
			 
		}  
	}	
	
	return -1;
#endif	
}
/*************************************************************
Name:FpgaLoadA7
Description:FPGA加载
Input:加载文件的总长度          
Output:void         
Return:-1:失败，1: 成功         
**************************************************************/
CHAR8 FpgaLoadA72(UINT32 len)
{
 
	UINT32 page_index,ReadByteOneLoop;
	UINT32 i ,ReadNums; 
	UCHAR8 *p_flash_page = sys_temp_buff;
	UCHAR8 retry = 100;
	CHAR8 result;
	UCHAR8 serial_retry = 4; 
    UCHAR8 ucTmpDat= 0;
    
	//TRACE_DEBUG_WP("FpgaLoadAll enter\r\n");
	WTD_CLR;

	CLR_FPGA_CS_PIN;      // FPGA的片选有效

	//UsNopDelay(1000);

	// Fpga进入加载状态 

		

	//第一步
	CLR_FPGA_NCS1_PIN ;		//拉低时钟
	SET_FPGA_NCONFIG	;	//拉高 nCONFIG 
	i =0;
	UsNopDelay(100);
	while(0==FPGA_INIT_B)  //等待GET_FPGA_INIT_B_ST 拉高
	{	
		i++;
		UsNopDelay(1000);
		if(i>20)
		{
			TRACE_DEBUG_WP("FpgaLoad INIT_B_error1\r\n");
			return -1;
		}
	}
	if(1==GET_FPGA_CONF_DONE)
	{
		TRACE_DEBUG_WP("done_error1\r\n");
		//return 1;
	}

	UsNopDelay(350);			        //延时350us  

	//第二步
	CLR_FPGA_NCONFIG ; //拉低config 脚

	UsNopDelay(100);			        //延时350us  
	i=0;
	while(1==FPGA_INIT_B)  //等待GET_FPGA_INIT_B_ST 拉低
	{	
		i++;
		UsNopDelay(1000);
		if(i>20)
		{
			TRACE_DEBUG_WP("FpgaLoad INIT_B_error2\r\n");
			return -1;
		}
	}
	if(1==GET_FPGA_CONF_DONE)
	{
		TRACE_DEBUG_WP("done_error2\r\n");
		//return 1;
	}

	//第三步
	SET_FPGA_NCONFIG ; //拉高config 脚
	i= 0 ;
	while(0==FPGA_INIT_B)  //等待GET_FPGA_INIT_B_ST 拉低
	{	
		i++;
		UsNopDelay(1000);
		if(i>20)
		{
			TRACE_DEBUG_WP("FpgaLoad INIT_B_error33333\r\n");
			return -1;
		}
	}
	if(1==GET_FPGA_CONF_DONE)
	{
		TRACE_DEBUG_WP("done_error2\r\n");
		//return 1;
	}

			




	WTD_CLR;
	UsNopDelay(1000);	
	WTD_CLR;
	
	TRACE_DEBUG_WP("FpgaLoad Start\r\n"); // 定位页地址
	page_index = ( FPGA_LOAD_BLOCK1==fpga_load_block ) ? (FLASH_FPGA_PAGE_START1+1) : (FLASH_FPGA_PAGE_START2+1) ;
	TRACE_INFO_WP("Start Page:%04X.\r\n", page_index);


	while( len )
	{
		ReadByteOneLoop = len>UPDATE_PKT_MAX_LEN ?UPDATE_PKT_MAX_LEN : len;
		WTD_CLR;
		for(ReadNums=0;ReadNums<ReadByteOneLoop/FLASH_PAGE_SIZE;ReadNums++)
		{
			FlashRead( page_index+ReadNums, 0, p_flash_page+ReadNums*FLASH_PAGE_SIZE ,FLASH_PAGE_SIZE);
		}
		if(ReadByteOneLoop%FLASH_PAGE_SIZE)
		{			
			FlashRead( page_index+ReadNums, 0, p_flash_page+ReadNums*FLASH_PAGE_SIZE ,ReadByteOneLoop%FLASH_PAGE_SIZE);
			ReadNums++;
		}
		
		for (i=0; i<ReadByteOneLoop; i++)
		{ 
              	SentLoadDatA7(*(p_flash_page+i)); 
		}
		
		len -= ReadByteOneLoop;				
		page_index +=ReadNums;

		if((page_index%20)== 0)
			FLASH_LED;
//		TRACE_INFO(" page_index=[%d],ReadNums=[%d]\r\n",page_index,ReadNums);
	}
	TRACE_INFO("load all\r\n");
	WTD_CLR;
    //加载完毕
	UsNopDelay(1000); 			//Delay 1ms 
	
	if (GET_FPGA_CONF_DONE)  
	{     
		TRACE_INFO_WP("LOAD SUCCESS-0\r\n");

		SentLoadDatA7(0X00);		//dummy write
		SentLoadDatA7(0X00);		//dummy write

		


		SET_FPGA_NCS1_PIN;


        //加载成功,延迟1ms进入user mode 
		UsNopDelay(1000);  
		
		
		return 1; 

	} 
	else
	{
		TRACE_INFO_WP("LOAD FAIL-1\r\n");
		
		while (serial_retry--)			  //尝试多发点CLK
		{	
			if (GET_FPGA_CONF_DONE)
			{
				TRACE_INFO_WP("LOAD SUCCESS-0\r\n");

				SentLoadDatA7(0X00);		//dummy write
				SentLoadDatA7(0X00);		//dummy write


				SET_FPGA_NCS1_PIN;

		        	//加载成功,延迟1ms进入user mode 
				UsNopDelay(1000);  
				
				return 1; 		
			} 
			else
			{ 
               		TRACE_INFO_WP("LOAD FAIL-2222\r\n");
			}  
			 
		}  
		TRACE_INFO_WP("FPGA CANNT LOAD\r\n");
		SET_FPGA_NCS1_PIN;
		return  1;
	}	
	
}


/*************************************************************
Name:        GainAdjSetAUEnterAdjMode
Description: 增益校准设置AU进入校准模式
Input: 
	      ab_flag: AB段标志
Output:      void 
Return:      void 
**************************************************************/
void GainAdjSetAUEnterAdjMode( UCHAR8 abcd_flag )
{ 
	UINT16 tmp; 
	UINT16 i = 0;

	
	if ( SYS_A_FLAG == abcd_flag )
	{  
		
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_A_ATT_CTL, 0x06);//衰减校准模式 	
		FPGA_SET_CHANNEL(0); //打开0通道
		FPGA_DISABLE_WRITE;
		
		SetAtt1(TF_A,0X1F);
		
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_A_ATT3_CAL, 0X00 ); // 所有衰减器不衰
		FpgaWriteRegister(FPGA_REG_A_ATT3_EN,0x01);
		FPGA_DISABLE_WRITE;

	}
	else if ( SYS_B_FLAG == abcd_flag )
	{

	}
	else if ( SYS_C_FLAG == abcd_flag )
	{

	}
	else if ( SYS_D_FLAG == abcd_flag )
	{

	}	
}

/*************************************************************
Name:         GainAdjSetAUFrePoint        
Description:  增益波动校准设置AU频点
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
void GainAdjSetAUFrePoint(UCHAR8 abcd_flag,INT32 freq_point)
{

	switch (abcd_flag)
	{
		 case SYS_A_FLAG:
		 	PA_SetChannel( 0, 1, freq_point );
			break;
		default :
			break;
	}
		
}


/*************************************************************
Name:         FpgaAttAdjust        
Description:  增益波动校准
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
void FpgaGainAdjust()
{
	UINT16 fre_point = 512;

	//printf("adj_st:%d  is_wait:%d\r\n",gain_adj_st.adj_st,gain_adj_st.is_wait);
	if(gain_adj_st.is_wait)//等待命令执行
		return;

	switch(gain_adj_st.adj_st)
	{
		case GAIN_ADJ_ST_IDLE:
			gain_adj_st.is_wait = 0;
			break;
		case GAIN_ADJ_ST_SET_AUEU_ADJ_MODE://进入校准模式
			//printf("abcd:%d  ud:%d\r\n",gain_adj_st.ab_flag,gain_adj_st.ud_flag);
			
			
			// 置等待标志
			gain_adj_st.is_wait = 1;			
			gain_adj_st.adj_st= GAIN_ADJ_ST_IDLE;
			gain_adj_st.fre_point = 512;//起始频点
			gain_adj_st.step = 0;//清零计数

			if(gain_adj_st.ud_flag == SYS_DL_FLAG)
			{
				//printf("EU adj\r\n");
				//EU进入校准模式				
				GainAdjSetEUEnterAdjMode( gain_adj_st.ab_flag );
				
			}
			else
			{
				//printf("AU adj\r\n");
				//AU进入校准模式
				GainAdjSetAUEnterAdjMode( gain_adj_st.ab_flag );
				gain_adj_st.is_wait = 0;//进入下一个命令
			}
			WTD_CLR;
			UsNopDelay(1000*1000);
			
			break;
		case GAIN_ADJ_ST_SET_AUEU_FRE://设置AU EU第一个通道的频点
			fre_point = gain_adj_st.fre_point+gain_adj_st.step;//频点步进
			
			//printf("fre_point%d\r\n",fre_point);
			//设置AU的频点
			GainAdjSetAUFrePoint(gain_adj_st.ab_flag,fre_point);
			//设置EU的频点			
			GainAdjSetEUFrePoint(gain_adj_st.ab_flag,fre_point);
			gain_adj_st.is_wait = 1;
			gain_adj_st.adj_st= GAIN_ADJ_ST_GET_EU_SF_POW;
			//gain_adj_st.is_wait = 0;//进入下一个命令
			break;
		case GAIN_ADJ_ST_GET_EU_SF_POW://读取EU第一个通道的选频功率
		
			//GetPsfFromRe( gain_adj_st.ab_flag, gain_adj_st.ud_flag );
			GainAdjGetEUPow(gain_adj_st.ab_flag, gain_adj_st.ud_flag);
			gain_adj_st.step++;
			gain_adj_st.is_wait = 1;
			//printf("step%d\r\n",gain_adj_st.step);
			if(gain_adj_st.step < 125)
				gain_adj_st.adj_st= GAIN_ADJ_ST_SET_AUEU_FRE;
			else
				gain_adj_st.adj_st= GAIN_ADJ_ST_DONE;

			
			//gain_adj_st.is_wait = 0;//进入下一个命令
			break;

		case GAIN_ADJ_ST_DONE://校准完成
			// 步进完成，将数据返回给主控
			//SendMsgPkt( gain_adj_st.dat_len, att_adj_buff );
			gain_adj_st.adj_st  =GAIN_ADJ_ST_DONE; 
			gain_adj_st.is_wait = 0;  
			// 清除校准标志位
			sys_work_info &= (~SYSTEM_FLAG_GAIN_ADJ);
			break;
	}
}

/*************************************************************
Name:         GianAdjustStartAdj        
Description:  增益波动校准子命令开始校准
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
UINT16 GianAdjustStartAdj(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT16 msg_tx_len = 0;
	
	gain_adj_st.adj_st = GAIN_ADJ_ST_SET_AUEU_FRE;
	gain_adj_st.is_wait = 0;

	return msg_tx_len;
	
}
/*************************************************************
Name:         GianAdjustGetAdjStatus        
Description:  增益波动校准子命令查询校准状态
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
UINT16 GianAdjustGetAdjStatus(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT16 msg_tx_len = 0;

	
	p_tx_buff[msg_tx_len++] = gain_adj_st.adj_st;
	return msg_tx_len;
}
/*************************************************************
Name:         GianAdjustGetAdjData        
Description:  增益波动校准子命令获取校准数据
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
UINT16 GianAdjustGetAdjData(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT16 msg_tx_len = 0;

	p_tx_buff[msg_tx_len++] = gain_adj_st.ab_flag;	
	p_tx_buff[msg_tx_len++] = gain_adj_st.ud_flag;	
	memcpy(p_tx_buff+2,att_adj_buff,125*4);
	msg_tx_len += 125*4;
	return msg_tx_len;
}

/*************************************************************
Name:         GianAdjustEnterAdjMode        
Description:  增益波动校准子命令进入校准模式
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
UINT16 GianAdjustEnterAdjMode(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT16 msg_tx_len = 0;

	gain_adj_st.ab_flag = p_msg_dat[0];//ABCD段
	gain_adj_st.ud_flag= p_msg_dat[1];//上下行

	
	gain_adj_st.adj_st = GAIN_ADJ_ST_SET_AUEU_ADJ_MODE;
	gain_adj_st.is_wait = 0;
	gain_adj_st.dat_len = 0;
	sys_work_info |= SYSTEM_FLAG_GAIN_ADJ;

	return msg_tx_len;
	
}
/*************************************************************
Name:         MoveCenterFre        
Description:  增益波动校准获取EU功率
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
UINT32 MoveCenterFre(UCHAR8 ab_flag, UCHAR8 ud_flag)
{
	UINT16 addr_h = 0,addr_l = 0;
	UINT16 val_int16 =0,dat1=0;
	float val_mod = 0;
	float fre = 0,center_fre_d = 0,center_fre_u = 0;
	UINT32 val_int32 = 0;
	UINT16 val_reg5 = 0;
	float constant = 0;
	switch (ab_flag)
	{
		 case SYS_A_FLAG:
			if(ud_flag == SYS_DL_FLAG)
			{
				//addr_h = FPGA_REG_A_D_CH_SPOW_H;
				//addr_l=FPGA_REG_A_D_CH_SPOW_L;
				center_fre_d = sys_param_2b[MADD_MOVE_CENTER_FRE_D].val/100.0+300;
				center_fre_u = sys_param_2b[MADD_MOVE_CENTER_FRE_U].val/100.0+300;
			}
			else if(ud_flag == SYS_UL_FLAG)
			{
				//addr_h = FPGA_REG_A_U_CH_SPOW_H;
				//addr_l =FPGA_REG_A_U_CH_SPOW_L;
				center_fre_d = sys_param_2b[MADD_MOVE_CENTER_FRE_D].val/100.0+300;
				center_fre_u = sys_param_2b[MADD_MOVE_CENTER_FRE_U].val/100.0+300;
			}
			break;
		case SYS_B_FLAG:
			break;
		default :
			break;
	}

	if(center_fre_d < 390.5) 
	{
		constant = 1.92;
		val_reg5 = 0x44;
	}
	else if(center_fre_d < 765.5)
	{
		constant = 3.84;
		val_reg5 = 0x33;
	}
	else if(center_fre_d < 1515.5) 
	{
		constant = 7.68;
		val_reg5 = 0x22;
	}
	else 
	{
		constant = 15.36;
		val_reg5 = 0x11;
	}


	//AU与RU的接收一个是下行一个是上行
	//接收部分 其中整数部分换算成11位16进制整数，D10-D8写入0X232的低3bit，D7-D0写入0X231，小数部分×2^23换算成23位16进制整数，D22-D16写入0X235的低7bit，D15-D8写入0X234，D7-D0写入0X233
	fre = (center_fre_d - 15.5)/constant;
	val_int16 = (UINT16)fre;//取整
	val_mod = fre - (float)val_int16;//取余
	val_int32 = (UINT32) (val_mod*8388608);	

	ReadWriteTF(TF_A,1,0x005, val_reg5);

	
	ReadWriteTF(TF_A,1,0x231,(UCHAR8)((val_int16&0x00ff)>>0));
	ReadWriteTF(TF_A,1,0x232,(UCHAR8)((val_int16&0x0300)>>8));

	ReadWriteTF(TF_A,1,0x233,(UCHAR8)((val_int32&0x0000ff)>>0));
	ReadWriteTF(TF_A,1,0x234,(UCHAR8)((val_int32&0x00ff00)>>8));
	ReadWriteTF(TF_A,1,0x235,(UCHAR8)((val_int32&0x7f0000)>>16));

	//再写一次整数才生效
	ReadWriteTF(TF_A,1,0x231,(UCHAR8)((val_int16&0x00ff)>>0));


	
	//发送部分 其中整数部分换算成11位16进制整数，D10-D8写入0X272的低3bit，D7-D0写入0X271，小数部分×2^23换算成23位16进制整数，D22-D16写入0X275的低7bit，D15-D8写入0X274，D7-D0写入0X273
	fre = (center_fre_u - 15.5)/constant;
	val_int16 = (UINT16)fre;//取整
	val_mod = fre - (float)val_int16;//取余
	val_int32 = (UINT32) (val_mod*8388608);	


	ReadWriteTF(TF_A,1,0x005, val_reg5);

	ReadWriteTF(TF_A,1,0x271,(UCHAR8)((val_int16&0x00ff)>>0));
	ReadWriteTF(TF_A,1,0x272,(UCHAR8)((val_int16&0x0300)>>8));

	ReadWriteTF(TF_A,1,0x273,(UCHAR8)((val_int32&0x0000ff)>>0));
	ReadWriteTF(TF_A,1,0x274,(UCHAR8)((val_int32&0x00ff00)>>8));
	ReadWriteTF(TF_A,1,0x275,(UCHAR8)((val_int32&0x7f0000)>>16));

	//再写一次整数才生效
	ReadWriteTF(TF_A,1,0x271,(UCHAR8)((val_int16&0x00ff)>>0));

}




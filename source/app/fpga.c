/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :fpga.c
* Description :FPGA������غ���
* Version     :v0.1
* Author      :shiyang
* Date        :2008-01-29
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			��ʼ�汾
**************************************************************/
#include "Header.h"

extern _T_PARAM_2B sys_param_2b[];
extern UCHAR8      sys_temp_buff[SYS_TMP_BUFF_SIZE];
extern _T_FP_INFO  fp_inf[FP_MAX];
extern _T_BIG_PKT_BUFF msg_big_buff[MSG_BIG_PKT_COUNT];
extern UCHAR8 msg_buff[FP_MAX][FPGA_MSG_BUFF_SIZE];		// С��Ϣ������
extern UINT32 re_msg_buff_st[FP_MAX];
extern UINT32 module_param_chg_flag;		//ϵͳ���������޸ı�־
extern UINT32 bit_err_cnt; 
extern UINT32 fpga_rx_pkt_cnt;   
extern UCHAR8 benzhen2340;

UCHAR8 str_fpga_check_err[]="Fpga Data Bus Check Error!";
UCHAR8 str_fpga_prog_err[] ="Fpga Program Error!";

UCHAR8 fpga_load_block;		// Fpga��������
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

UINT16 fpga_a_regbk[MAX_CHANNEL_COUNT*2+2];	// ����д��Ĵ���ginp+gcic+{��������,��������}x ch_count 
UINT16 fpga_b_regbk[MAX_CHANNEL_COUNT*2+2];	// ����д��Ĵ���ginp+gcic+{��������,��������}x ch_count

UINT16 fpga_c_regbk[MAX_CHANNEL_COUNT*2+2];	// ����д��Ĵ���ginp+gcic+{��������,��������}x ch_count 
UINT16 fpga_d_regbk[MAX_CHANNEL_COUNT*2+2];	// ����д��Ĵ���ginp+gcic+{��������,��������}x ch_count

//UINT16 fpga_write_bak[FPGA_W_REG_MAX];


/*************************************************************
Name:        FpgaSetErrInfo
Description: ��Fpgaˮӡ��Ϣ����������Ϣ
Input:
	      err_id: ����id 
Output:void          
Return:void
**************************************************************/
void FpgaSetErrInfo( UCHAR8 err_id )
{
	switch(err_id)
	{
		case FPGA_ERR_PROG:			// ���ش���
			sys_param_asc[MADD_PRI_FPGA_DATE].length = sizeof(str_fpga_prog_err);
			sys_param_asc[MADD_PRI_FPGA_DATE].p_asc = str_fpga_prog_err;
		break;
			
		case FPGA_ERR_CHECK:		// У�����
			sys_param_asc[MADD_PRI_FPGA_DATE].length = sizeof(str_fpga_check_err);
			sys_param_asc[MADD_PRI_FPGA_DATE].p_asc = str_fpga_check_err;
		break;
		
	}
}
#ifdef FPGA_MSG_ADD_ADDRESS
/*************************************************************
Name:           FpgaSendMsgPkt
Description:    ͨ��FPGA���ڵ�RE��������
Input:
		  des_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
  		  src_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
  		  length:  ���ݰ��ֽڳ���
  		  p_msg_dat: ֻ�����ݻ����ָ��
  		  
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

	des_fp = (UCHAR8)((des_add>>16)&0xff);	// ��λ��ʾ��ں�
	des_re = (UCHAR8)((des_add>>8)&0xff);		// ��λ��ʾRE��
	des_ree = (UCHAR8)(des_add&0xff);		// ��λ��ʾREe��

	
	src_fp = (UCHAR8)((src_add>>16)&0x00ff);	   // ��λ��ʾ��ں�
	src_re = (UCHAR8)((src_add>>8)&0x00ff);		   // ��λ��ʾRE�� 
	src_ree = (UCHAR8)((src_add>>0)&0x00ff);		   // ��λ��ʾRee��

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

	// д��Ҫ�����Ĺ�ں�
	FPGA_SET_OPT(des_fp);
//	TRACE_INFO_WP("fp%d.", des_fp);

	while ( tx_count<=MSG_BIG_PKT_SIZE )
	{
//		TRACE_INFO_WP("fpga tx2.");
		// �ȴ����ͻ������
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
		
		// �ְ����ж��Ƿ������һ������֡
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
		
		// ����ʣ�����ݳ���
		length -= len;
		tx_count += len;
		
		// д����Ϣ���ĵ�ַ��Ϣ
		FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, (des_add>>8)&0xffff );
		FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, (src_add>>8)&0xffff );
//		TRACE_INFO_WP( "\r\nDesAdd:%06X, SrcAdd:%06X, ", des_add, src_add );
		
		// д�����ݳ���,����1�ֽڵ�֡��� 
		if((frame_no & MSG_FRAME_INDEX_MASK) == 0)
		{
			FpgaWriteRegister( FPGA_REG_W_MSG_LEN, len+1 );
		}
		else
		{
			FpgaWriteRegister( FPGA_REG_W_MSG_LEN, len+1+FPGA_MSG_ADDR_LEN );
		}
		TRACE_INFO_WP( "MsgLen:%d,\r\n ", len+1 );

		// д��֡���
		FpgaWriteRegister( FPGA_REG_W_MSG_DAT, frame_no );
//		TRACE_INFO_WP( "FrmIndex:%02X\r\n ", frame_no );

		//���˷��ʹӵڶ������ݿ�ʼ���Ŀ�ĵ�ַ��Դ��ַ��20141205 
		//��һ������ԭ������ӡ�
		if ( (frame_no & MSG_FRAME_INDEX_MASK) != 0 )
		{//���ǵ�һ����
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, des_fp_tx );
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, des_re_tx );
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, des_ree_tx );
			
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, src_fp_tx );
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, src_re_tx );
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, src_ree_tx );
		}

		// д����Ϣ����
		for ( i=0; i<len; i++ )
		{
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, *p_msg_dat++ );
		}
		
		// ��������
		FpgaWriteRegister( FPGA_REG_MSG_START_SEND, 0x00 );
		TRACE_INFO_WP( "End.\r\n" );
		
		WTD_CLR;
		//����֡����ۼ�
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
Description:    ͨ��FPGA���ڵ�RE��������
Input:
		  des_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
  		  src_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
  		  length:  ���ݰ��ֽڳ���
  		  p_msg_dat: ֻ�����ݻ����ָ��
  		  
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
	des_fp = (UCHAR8)((des_add>>16)&0xff);	// ��λ��ʾ��ں�
	des_re = (UCHAR8)((des_add>>8)&0xff);		// ��λ��ʾRE��
	des_ree = (UCHAR8)(des_add&0xff);		// ��λ��ʾREe��
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

	// д��Ҫ�����Ĺ�ں�
	FPGA_SET_OPT(des_fp);
//	TRACE_INFO_WP("fp%d.", des_fp);

	while ( tx_count<=MSG_BIG_PKT_SIZE )
	{
//		TRACE_INFO_WP("fpga tx2.");
		// �ȴ����ͻ������
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
		
		// �ְ����ж��Ƿ������һ������֡
		if ( length <= FPGA_MSG_FRAME_LEN )
		{
			frame_no |= MSG_FRAME_END_FLAG;
			len = length;
		}
		else
		{
			len = FPGA_MSG_FRAME_LEN;
		}
		
		// ����ʣ�����ݳ���
		length -= len;
		tx_count += len;
		
		// д����Ϣ���ĵ�ַ��Ϣ
		FpgaWriteRegister( FPGA_REG_W_MSG_DES_ADD, (des_add>>8)&0xffff );
		FpgaWriteRegister( FPGA_REG_W_MSG_SRC_ADD, (src_add>>8)&0xffff );
//		TRACE_INFO_WP( "\r\nDesAdd:%06X, SrcAdd:%06X, ", des_add, src_add );
		
		// д�����ݳ���
		FpgaWriteRegister( FPGA_REG_W_MSG_LEN, len+1 );
//		TRACE_INFO_WP( "MsgLen:%d, ", len+1 );

		// д��֡���
		FpgaWriteRegister( FPGA_REG_W_MSG_DAT, frame_no );
//		TRACE_INFO_WP( "FrmIndex:%02X\r\n ", frame_no );

		// д����Ϣ����
		for ( i=0; i<len; i++ )
		{
			FpgaWriteRegister( FPGA_REG_W_MSG_DAT, *p_msg_dat++ );
		}
		
		// ��������
		FpgaWriteRegister( FPGA_REG_MSG_START_SEND, 0x00 );
		TRACE_INFO_WP( "End.\r\n" );
		
		WTD_CLR;
		//����֡����ۼ�
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
Description: �ӹ������FIFO��ȡ���ݣ�����ָ��������
Input:
	len: Ҫ��ȡ�����ݳ���
	p_save_buff: ��������ַ
Output:void         
Return: �ѱ�������ݳ���
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
Description: ͨ��FPGA���ڵ�RE��������
Input:
	des_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
	src_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
	length: ���ݰ��ֽڳ���
	p_msg_dat: ֻ�����ݻ����ָ��
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
		// FPGA���ϣ�����
		return;    
	} 
 
	// ������ݰ�����FIFO״̬,λ��Ӧ,��8λ1��ʾFIFO������,��8λ1��ʾFIFO�� 
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	// �����˳�������ݰ� 
	for ( i=0; i<FP_MAX; i++ )
	{
		// д��Ҫ�����Ĺ�ں�
		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(i);
		FPGA_DISABLE_WRITE; 

		// �ۼ����ݰ�������� ������ն�Ӧ�Ĵ���
		bit_err_cnt += FpgaReadRegister(FPGA_REG_PKT_ERR_COUNT);
		FpgaReadRegister(FPGA_REG_CLEAR_PKT_ERR);
		
		// �жϹ���Ƿ����յ����ݰ�
		if ( 0 != (msg_fifo_st & (0x0001<<i)) ) 
		{
			p_msg_dat = sys_temp_buff;
			
			for ( j=0; j<FPGA_FRAME_FIFO_SIZE; j++ )
			{
				*p_msg_dat++ = (UCHAR8)( 0x00FF & FpgaReadRegister( FPGA_REG_R_MSG_DAT ) );
			} 	   
	   		
	   		// ��ȡ���ݳ���
	   		frame_len = sys_temp_buff[4];	 //TRACE_INFO("frame_len = %d\r\n",frame_len);  
	   		
	   		// ��ȡ����֡���  
	   		frame_no = sys_temp_buff[5];	 // TRACE_INFO("frame_no = %02x\r\n",frame_no);

			if (( src_fp>FP_MAX )||( src_re>RE_MAX )||(0==frame_len)||(frame_len>FPGA_MSG_BUFF_SIZE)||
				((frame_no&MSG_FRAME_INDEX_MASK)>=MSG_MAX_FRAME_INDEX) )
			{
				// �л�FIFOҳ
				FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
				continue;
			}  
			
			frame_len--;	  // ���ȼ�1,��Ϊ��Ч���ݳ���

			if ( 0 ==(frame_no & MSG_FRAME_INDEX_MASK) ) 
			{ 
				des_fp   = sys_temp_buff[6];
				des_re   = sys_temp_buff[7];
				src_fp   = sys_temp_buff[8];
				src_re   = sys_temp_buff[9];
			}       

			if ( 0 != (frame_no & MSG_FRAME_END_FLAG) )	// ��ĩ֡
			{
				msg_end_flag = b_TRUE;
				
				frame_no &= MSG_FRAME_INDEX_MASK;	// ȡ��֡���
				
				// �ж��Ƿ��Ǵ����ݰ�
				if ( frame_no > 0 )
				{	
					// �����ݰ����ж�RE�Ƿ��д󻺳�ʹ��Ȩ
					tmp = GetReBigMsgBuffIndex( src_fp, src_re );
					
					if ( 0 == tmp ) 	// ��REû�д󻺳��ʹ��Ȩ
					{
						// ���ؽ��ն�δ������Ӧ��
						p_msg_dat = 0;
						MsgReceiverBusy( src_fp, src_re );
						continue;
					} 
					else
					{
						// ��������ݻ���
						tmp--;
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
						msg_len = frame_no * FPGA_MSG_FRAME_LEN + frame_len;
 					}
				}
				else
				{
					// ��ͨ���ݰ���ֱ�ӱ��沢����
					p_msg_dat = msg_buff[i];
					msg_len = frame_len;
				}
			}
			else
			{
				// ������������֡
				msg_end_flag = b_FALSE; 
				
				// ������Ҫ���浽�󻺳��У����ж�RE��û�д󻺳��ʹ��Ȩ
				tmp = GetReBigMsgBuffIndex( src_fp, src_re );
				
				if ( 0 == tmp )	 // REû�д����ݻ����ʹ��Ȩ
				{  
					tmp = GetFreeBigBuffIndex();

					if ( 0 != tmp )	// �����ݻ������,����������ǰRE
					{
						tmp--;    
						
						msg_big_buff[tmp].owner = ((src_fp<<8)|src_re); 
						msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;

						 // ����ָ��ָ������ݻ���    
						p_msg_dat = msg_big_buff[tmp].buff; 
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
					}
					else // �����ݻ��屻ռ��
					{
						// ���ؽ��ն�δ������Ӧ��
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
           
			// �л�FIFOҳ
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
						msg_big_buff[tmp].owner = 0;		// �ͷŴ����ݻ�����Դ
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
Description: �ӹ������FIFO��ȡ���ݣ�����ָ��������
Input:
	len: Ҫ��ȡ�����ݳ���
	p_save_buff: ��������ַ
Output:void         
Return: �ѱ�������ݳ���
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
Description: ͨ��FPGA�ӹ�ڵĶ�ȡRE����
Input:
	des_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
	src_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
	length: ���ݰ��ֽڳ���
	p_msg_dat: ֻ�����ݻ����ָ��
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
		// FPGA���ϣ�����
		return;    
	} 
 
	// ������ݰ�����FIFO״̬,λ��Ӧ,��8λ1��ʾFIFO������,��8λ1��ʾFIFO�� 
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	//TRACE_INFO_WP("fpga msg_fifo_st = %02x \r\n",msg_fifo_st); 
	
	// �����˳�������ݰ� 
	for ( i=0; i<FP_MAX; i++ )
	{
		// д��Ҫ�����Ĺ�ں�
		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(i);
		FPGA_DISABLE_WRITE; 

		// �ۼ����ݰ�������� ������ն�Ӧ�Ĵ���
		bit_err_cnt += FpgaReadRegister(FPGA_REG_PKT_ERR_COUNT);
		FpgaReadRegister(FPGA_REG_CLEAR_PKT_ERR);
//		TRACE_INFO_WP("fpga rx1\n"); 
		// �жϹ���Ƿ����յ����ݰ�
		if ( 0 != (msg_fifo_st & (0x0001<<i)) )
		{
			TRACE_INFO_WP("fpga rx2\n"); 
			p_msg_dat = sys_temp_buff;
			
			for ( j=0; j<FPGA_FRAME_FIFO_SIZE; j++ )
			{
				*p_msg_dat++ = (UCHAR8)( 0x00FF & FpgaReadRegister( FPGA_REG_R_MSG_DAT ) );
			} 

	   		// ��ȡ���ݳ���
	   		frame_len = sys_temp_buff[4];	
	   		
	   		// ��ȡ����֡��� 
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
				// �л�FIFOҳ
				FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
				continue;
			} 
			
			//TRACE_INFO_WP( "(%d) fi(0x%02X).", frame_len, frame_no );

			frame_len--;	// ���ȼ�1,��Ϊ��Ч���ݳ���   
			  			 
			if ( 0 != (frame_no & MSG_FRAME_END_FLAG) )	// ��ĩ֡
			{
				msg_end_flag = b_TRUE;
				
				frame_no &= MSG_FRAME_INDEX_MASK;	// ȡ��֡���
				
				// �ж��Ƿ��Ǵ����ݰ�
				if ( frame_no > 0 )
				{	
					// �����ݰ����ж�RE�Ƿ��д󻺳�ʹ��Ȩ
					tmp = GetReBigMsgBuffIndex( src_fp, src_re,src_ree);
					
					if ( 0 == tmp ) 	// ��REû�д󻺳��ʹ��Ȩ
					{
						// ���ؽ��ն�δ������Ӧ��
						p_msg_dat = 0;
						//MsgReceiverBusy( src_fp, src_re,src_ree);
						continue;
					} 
					else
					{
						// ��������ݻ���
						tmp--;
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += (FPGA_MSG_FRAME_LEN+ (frame_no-1) * (FPGA_MSG_FRAME_LEN-FPGA_MSG_ADDR_LEN) );
						msg_len = FPGA_MSG_FRAME_LEN+((frame_no-1) * (FPGA_MSG_FRAME_LEN-FPGA_MSG_ADDR_LEN)) + (frame_len-FPGA_MSG_ADDR_LEN);
 					}
				}
				else
				{
					// ��ͨ���ݰ���ֱ�ӱ��沢����
					p_msg_dat = msg_buff[i];
					msg_len   = frame_len;
				}
			}
			else
			{
				// ������������֡
				msg_end_flag = b_FALSE; 
				
				// ������Ҫ���浽�󻺳��У����ж�RE��û�д󻺳��ʹ��Ȩ
				tmp = GetReBigMsgBuffIndex( src_fp, src_re,src_ree);
				
				if ( 0 == tmp )	 // REû�д����ݻ����ʹ��Ȩ
				{  
					tmp = GetFreeBigBuffIndex();

					if ( 0 != tmp )	// �����ݻ������,����������ǰRE
					{
						tmp--;    
						
						msg_big_buff[tmp].owner = ((src_fp<<16)|(src_re<<8)|src_ree); 
						msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;

						 // ����ָ��ָ������ݻ���    
						p_msg_dat = msg_big_buff[tmp].buff; 
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
					}
					else // �����ݻ��屻ռ��
					{
						// ���ؽ��ն�δ������Ӧ��
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
			
			//���˷���ÿ�����ݶ����Ŀ�ĵ�ַ��Դ��ַ��20141205 
			//�洢ʱֻ�洢��һ������Դ��ַ��Ŀ�ĵ�ַ
			if ( (frame_no1 & MSG_FRAME_END_FLAG) == 0 )
			{
				if ( (frame_no1 & MSG_FRAME_INDEX_MASK) == 0 )//��һ����
				{
					for ( k=0; k<frame_len; k++ )
					{
						//TRACE_INFO_WP("%d ",*p_msg_dat);
						*p_msg_dat++ = sys_temp_buff[k+6];//ȥ����ͷ
					}
				}
				else
				{
					for ( k=0; k<(frame_len-FPGA_MSG_ADDR_LEN); k++ )
					{
						//TRACE_INFO_WP("%d ",*p_msg_dat);
						*p_msg_dat++ = sys_temp_buff[k+6+FPGA_MSG_ADDR_LEN];//ȥ����ͷ
					}
				}
			}
			else
			{//���һ����
					if ( (frame_no1 & MSG_FRAME_INDEX_MASK) == 0 )//��һ����
					{
						for ( k=0; k<frame_len; k++ )
						{
							//TRACE_INFO_WP("%d ",*p_msg_dat);
							*p_msg_dat++ = sys_temp_buff[k+6];//ȥ����ͷ
						}
					}
					else
					{
						for ( k=0; k<(frame_len-FPGA_MSG_ADDR_LEN); k++ )
						{
							//TRACE_INFO_WP("%d ",*p_msg_dat);
							*p_msg_dat++ = sys_temp_buff[k+6+FPGA_MSG_ADDR_LEN];//ȥ����ͷ
						}
				
					}
			}
			
			// �л�FIFOҳ 
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
						msg_big_buff[tmp].owner = 0;		// �ͷŴ����ݻ�����Դ
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
Description: ͨ��FPGA�ӹ�ڵĶ�ȡRE����
Input:
	des_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
	src_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
	length: ���ݰ��ֽڳ���
	p_msg_dat: ֻ�����ݻ����ָ��
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
		// FPGA���ϣ�����
		return;    
	} 
 
	// ������ݰ�����FIFO״̬,λ��Ӧ,��8λ1��ʾFIFO������,��8λ1��ʾFIFO�� 
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	// �����˳�������ݰ� 
	for ( i=0; i<FP_MAX; i++ )
	{
		// д��Ҫ�����Ĺ�ں�
		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(i);
		FPGA_DISABLE_WRITE; 

		// �ۼ����ݰ�������� ������ն�Ӧ�Ĵ���
		bit_err_cnt += FpgaReadRegister(FPGA_REG_PKT_ERR_COUNT);
		FpgaReadRegister(FPGA_REG_CLEAR_PKT_ERR);
//		TRACE_INFO_WP("fpga rx1\n"); 
		// �жϹ���Ƿ����յ����ݰ�
		if ( 0 != (msg_fifo_st & (0x0001<<i)) )
		{
			TRACE_INFO_WP("fpga rx2\n"); 
			p_msg_dat = sys_temp_buff;
			
			for ( j=0; j<FPGA_FRAME_FIFO_SIZE; j++ )
			{
				*p_msg_dat++ = (UCHAR8)( 0x00FF & FpgaReadRegister( FPGA_REG_R_MSG_DAT ) );
			} 

	   		// ��ȡ���ݳ���
	   		frame_len = sys_temp_buff[4];	
	   		
	   		// ��ȡ����֡��� 
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
				// �л�FIFOҳ
				FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
				continue;
			} 
			
			//TRACE_INFO_WP( "(%d) fi(0x%02X).", frame_len, frame_no );

			frame_len--;	// ���ȼ�1,��Ϊ��Ч���ݳ���   
			  			 
			if ( 0 != (frame_no & MSG_FRAME_END_FLAG) )	// ��ĩ֡
			{
				msg_end_flag = b_TRUE;
				
				frame_no &= MSG_FRAME_INDEX_MASK;	// ȡ��֡���
				
				// �ж��Ƿ��Ǵ����ݰ�
				if ( frame_no > 0 )
				{	
					// �����ݰ����ж�RE�Ƿ��д󻺳�ʹ��Ȩ
					tmp = GetReBigMsgBuffIndex( src_fp[i], src_re[i],src_ree[i]);
					
					if ( 0 == tmp ) 	// ��REû�д󻺳��ʹ��Ȩ
					{
						// ���ؽ��ն�δ������Ӧ��
						p_msg_dat = 0;
						MsgReceiverBusy( src_fp[i], src_re[i],src_ree[i]);
						continue;
					} 
					else
					{
						// ��������ݻ���
						tmp--;
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
						msg_len = frame_no * FPGA_MSG_FRAME_LEN + frame_len;
 					}
				}
				else
				{
					// ��ͨ���ݰ���ֱ�ӱ��沢����
					p_msg_dat = msg_buff[i];
					msg_len   = frame_len;
				}
			}
			else
			{
				// ������������֡
				msg_end_flag = b_FALSE; 
				
				// ������Ҫ���浽�󻺳��У����ж�RE��û�д󻺳��ʹ��Ȩ
				tmp = GetReBigMsgBuffIndex( src_fp[i], src_re[i],src_ree[i]);
				
				if ( 0 == tmp )	 // REû�д����ݻ����ʹ��Ȩ
				{  
					tmp = GetFreeBigBuffIndex();

					if ( 0 != tmp )	// �����ݻ������,����������ǰRE
					{
						tmp--;    
						
						msg_big_buff[tmp].owner = ((src_fp[i]<<16)|(src_re[i]<<8)|src_ree[i]); 
						msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;

						 // ����ָ��ָ������ݻ���    
						p_msg_dat = msg_big_buff[tmp].buff; 
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
					}
					else // �����ݻ��屻ռ��
					{
						// ���ؽ��ն�δ������Ӧ��
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
			
			// �л�FIFOҳ 
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
						msg_big_buff[tmp].owner = 0;		// �ͷŴ����ݻ�����Դ
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
Description: ͨ��FPGA���ڵ�RE��������
Input:
	des_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
	src_add: �������ݰ��ĵ�ַ����8λ��ʾ��ںţ���8λ��ʾRE���
	length: ���ݰ��ֽڳ���
	p_msg_dat: ֻ�����ݻ����ָ��
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
		// FPGA���ϣ�����
		return;
	}

	// ��ȡ���ݰ�FIFO״̬
	msg_fifo_st = FpgaReadRegister( FPGA_REG_MSG_FIFO_ST );
	
	// �����˳�������ݰ�
	for ( i=0; i<FP_MAX; i++ )
	{
		// д��Ҫ�����Ĺ�ں�
		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(i);
		FPGA_DISABLE_WRITE;

		// �ۼ����ݰ��������
		bit_err_cnt += FpgaReadRegister(FPGA_REG_PKT_ERR_COUNT);
		FpgaReadRegister(FPGA_REG_CLEAR_PKT_ERR);

		TRACE_INFO_WP( "test1");
		TRACE_INFO_WP( "msg_fifo_st=%d",msg_fifo_st);
		// �жϹ���Ƿ����յ����ݰ�
		if ( 0 != (msg_fifo_st & (0x0001<<i)) )
		{
			TRACE_INFO_WP("fpga rx");
	
			// ��ȡĿ�ĵ�ַ
			des_fp = FpgaReadRegister( FPGA_REG_R_MSG_DAT )+2;
			des_re = FpgaReadRegister( FPGA_REG_R_MSG_DAT )+1;
			des_ree = FpgaReadRegister( FPGA_REG_R_MSG_DAT );
			// ��ȡԴ��ַ
			src_fp = FpgaReadRegister( FPGA_REG_R_MSG_DAT )+2;
			src_re = FpgaReadRegister( FPGA_REG_R_MSG_DAT )+1;
			src_ree = FpgaReadRegister( FPGA_REG_R_MSG_DAT );
			
			// ��ȡ���ݳ���
			frame_len = FpgaReadRegister( FPGA_REG_R_MSG_DAT );
			
			// ��ȡ����֡���
			frame_no = FpgaReadRegister( FPGA_REG_R_MSG_DAT );

			TRACE_INFO_WP(" test(%02X:%02X->%02X:%02X-%d).", src_fp, src_re, des_fp, des_re, frame_len);//add20121127
			
			if (( src_fp>FP_MAX )||( src_re>RE_MAX )||(0==frame_len)||(frame_len>FPGA_MSG_BUFF_SIZE)||
				((frame_no&MSG_FRAME_INDEX_MASK)>=MSG_MAX_FRAME_INDEX) )
			{
				TRACE_INFO_WP(" Err(%02X:%02X->%02X:%02X-%d).", src_fp, src_re, des_fp, des_re, frame_len);
				// �л�FIFOҳ
				FpgaReadRegister( FPGA_REG_R_NEXT_MSG );
				continue;
			}
			
			TRACE_INFO_WP( "(%d) fi(0x%02X).", frame_len, frame_no );

			frame_len--;	// ���ȼ�1,��Ϊ��Ч���ݳ���

			// �ͷŻ�����ָ��
			p_msg_dat = 0;
			
			if ( 0 != (frame_no & MSG_FRAME_END_FLAG) )	// ��ĩ֡
			{
				msg_end_flag = b_TRUE;
				
				frame_no &= MSG_FRAME_INDEX_MASK;	// ȡ��֡���
				
				// �ж��Ƿ��Ǵ����ݰ�
				if ( frame_no > 0 )
				{	
					// �����ݰ����ж�RE�Ƿ��д󻺳�ʹ��Ȩ
					tmp = GetReBigMsgBuffIndex( src_fp, src_re );
					
					if ( 0 == tmp ) 	// ��REû�д󻺳��ʹ��Ȩ
					{
						// ���ؽ��ն�δ������Ӧ��
						MsgReceiverBusy( src_fp, src_re );
					}
					else
					{
						// ��������ݻ���
						tmp--;
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
						msg_len = frame_no * FPGA_MSG_FRAME_LEN + frame_len;
 					}
				}
				else
				{
					// ��ͨ���ݰ���ֱ�ӱ��沢����
					p_msg_dat = msg_buff[i];
					msg_len = frame_len;
				}
			}
			else
			{
				// ������������֡
				msg_end_flag = b_FALSE;
				
				// ������Ҫ���浽�󻺳��У����ж�RE��û�д󻺳��ʹ��Ȩ
				//if ( 0 == (re_msg_buff_st[src_fp] & (0x00000001<<src_re)) )
				tmp = GetReBigMsgBuffIndex( src_fp, src_re );
				if ( 0 == tmp )	 // REû�д����ݻ����ʹ��Ȩ
				{
					tmp = GetFreeBigBuffIndex();

					if ( 0 != tmp )	// �����ݻ������,����������ǰRE
					{
						tmp--;
						
						msg_big_buff[tmp].owner = ((src_fp<<8)|src_re);
						msg_big_buff[tmp].time_out = MSG_BIG_PKT_TIME_OUT;

						// ����ָ��ָ������ݻ���
						p_msg_dat = msg_big_buff[tmp].buff;
						p_msg_dat += ( frame_no * FPGA_MSG_FRAME_LEN );
					}
					else		// �����ݻ��屻ռ��
					{
						// ���ؽ��ն�δ������Ӧ��
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
				// ��ȡ����
				tmp = FpgaSaveMsgDat( frame_len, p_msg_dat );
			}

			// �л�FIFOҳ
			FpgaReadRegister( FPGA_REG_R_NEXT_MSG );

			if (( tmp>0 )&&( tmp<=FPGA_MSG_BUFF_SIZE))
			{
				WTD_CLR;
				if ( 0!=p_msg_dat )
				{
					// ������Ϣ��
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
								msg_big_buff[tmp].owner = 0;		// �ͷŴ����ݻ�����Դ
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
Description:  ��ָ���Ĺ���ж�ȡ͸������
Input:         void
Output:        void          
Return:        void
**************************************************************/
void FpgaReadThrDat()
{
	_T_THR_FIFO * p_fifo;	// FIFOָ��
	UINT16 fp; 
	UCHAR8 dat; 

	WTD_CLR;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA���ϣ�����
		return; 
	}

	// FPGA͸������FIFOָ��
	p_fifo = (0==thr_utx_fifo_use) ? (&uart_thr_tx_fifo[1]) : (&uart_thr_tx_fifo[0]);	
	//TRACE_INFO("FpgaReadThrDat---thr_utx_fifo_use=[%x]\r\n",thr_utx_fifo_use);

	// ѭ����ȡ8����ڵ�͸������
	for ( fp=0; fp<FP_MAX; fp++ )	
	{
		FPGA_ENABLE_WRITE;	// ��FPGAдʹ�� 
		FPGA_SET_OPT(fp);	// �л���ں� 
		FPGA_DISABLE_WRITE;	// �ر�FPGAдʹ�� 

		//thr_func.pf_en_tx_it(0);	// �ر�͸�����ڷ����жϣ���ֹ��ʱ�����жϸı���нṹ

		if ( IS_OPT_ENABLE(fp) )	// �����ʹ��
		{
			while ( p_fifo->count < THR_FIFO_SIZE )
			{
				//TRACE_INFO("mau_rev_thr_dat_from_meu---dat_flag=[%x],fp=[%d]\r\n",FpgaReadRegister(FPGA_REG_THR_FIFO_ST) & (1<<fp),fp);
				
				// FPGA͸������������
				if ( 0 != (FpgaReadRegister(FPGA_REG_THR_FIFO_ST) & (1<<fp)) )	
				{
					// ��FPGA͸�������ȡ����
					dat = (UCHAR8)(0xff&FpgaReadRegister(FPGA_REG_R_THR_DAT));	

					// �������ݵ�FIFO��, ���ݸ���+1
					p_fifo->p_dat[p_fifo->count++] = dat;
					TRACE_INFO("dat=%02x,p_fifo->count=%dr\n",dat,p_fifo->count);
				}
				else
				{
					
				// ��������һ�������
					break;	
				}
				WTD_CLR;
			}
		}
		//if ( 0==thr_tx_end )			// ǰһ�δ���δ���
		//{
			//thr_func.pf_en_tx_it(1);	// �ָ�͸�����ڷ����ж�
		//}
	}

}



/*************************************************************
Name:        FpgaSendThrDat
Description: FPGA����͸�����ݣ�����Ҫָ����ڵĲ���
Input:       void     
Output:      void         
Return:      void
**************************************************************/
void FpgaSendThrDat()
{
	_T_THR_FIFO * p_fifo;	// FIFOָ��
	UCHAR8 wait_time = 0; 
	UCHAR8 dat;
	UINT16 count = 0;
	UINT16 i=0;

	// FPGA͸������FIFOָ��
	p_fifo = (0==thr_urx_fifo_use) ? (&uart_thr_rx_fifo[1]) : (&uart_thr_rx_fifo[0]);

	// ��λ��������ֵ
	p_fifo->index = 0;
#if 0
/*--------------------------����Ϊ����͸������--------------------------*/	
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
/*--------------------------����Ϊ����͸������--------------------------*/	
#endif
	//TRACE_INFO("-------------------1ThrUart_send_dat_to_meu---p_fifo->count=[%d]\r\n",p_fifo->count);	
	
	if(p_fifo->count > 0)
	{
		TRACE_INFO("-------------------1ThrUart_send_dat_to_meu---p_fifo->count=%d:  ",p_fifo->count);	
		TRACE_INFO("data: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\r\n", p_fifo->p_dat[0], p_fifo->p_dat[1],p_fifo->p_dat[2], p_fifo->p_dat[3],p_fifo->p_dat[4], p_fifo->p_dat[5],p_fifo->p_dat[6], p_fifo->p_dat[7],p_fifo->p_dat[8], p_fifo->p_dat[9],p_fifo->p_dat[10], p_fifo->p_dat[11],p_fifo->p_dat[12], p_fifo->p_dat[13],p_fifo->p_dat[14], p_fifo->p_dat[15],p_fifo->p_dat[16], p_fifo->p_dat[17],p_fifo->p_dat[18]);	
	}
	// ѭ����������
	while ( p_fifo->count > 0 ) 
	{
		//printf("aa");
		//TRACE_INFO("2ThrUart_send_dat_to_meu---FpgaReadRegister(FPGA_REG_R_THR_IDLE_ST)=[%x]\r\n",FpgaReadRegister(FPGA_REG_R_THR_IDLE_ST));	
		
		// �ȴ�FPGA͸���������
		if ( 0==(0x01&FpgaReadRegister(FPGA_REG_R_THR_IDLE_ST)) )
		{
			UsNopDelay(1);	// ��ʱ1us
			wait_time++;		// �ȴ�ʱ��+1
			if ( wait_time>150 )	// �����ʱ100us�������Է�æ���˳�
			{
				break;
			}
			else
			{
				continue;
			}
		}
		
		// �ȴ�ʱ������
		wait_time = 0;
		
		// ��FIFOȡ������,FIFO��ָ�����
		dat = p_fifo->p_dat[ p_fifo->index++ ];	
		
		//TRACE_INFO("dat=%02x,count=[%d] ",dat,p_fifo->count);	
		//UsNopDelay(5000);
		// ���˷���͸������
		FPGA_ENABLE_WRITE;		// ��FPGAдʹ��
		FpgaWriteRegister( FPGA_REG_W_THR_DAT, dat );	// д�����ݵ�FPGA͸������
		FPGA_DISABLE_WRITE;		// �ر�FPGAдʹ��

		
		if(sys_param_1b[MADD_PASSTHROUGH_EN].val)
		{
			TRACE_INFO("���ڲ���͸��485......uart_index=%d\r\n",uart_index);
	
			uart_test_tx_buff[uart_index++]=dat; 
	
			if((dat==0x4E)&&(uart_flag==0x7E))
			{
				
				for(i=0;i<uart_index;i++)
				{
					thr_func.pf_send_byte(uart_test_tx_buff[i]);
					TRACE_INFO("���ڷ��Ͳ���͸��485����[%d]:[%x]......\r\n",i,uart_test_tx_buff[i]);
				}
				uart_index=0;
				uart_flag=0;
	
			}
			else if(dat==0x7E)
			{
				uart_flag =dat;
			}
		}

		
		// FIFO���ݸ���-1
		p_fifo->count--;	

		// ι��
		if ( ++count > 1000 )
		{
			WTD_CLR;
			count = 0;
		}
	}

	// ���ݷ�����ɣ���͸�����ڽ���FIFO�����������л�FIFO
	if ( 0 != uart_thr_rx_fifo[thr_urx_fifo_use].count )
	{
		// ��λ��ǰFIFO
		p_fifo->index = 0;
		p_fifo->count = 0;
		// �رս����ж�
		thr_func.pf_ie_rx_dat(0);
		// �л�FIFO
		thr_urx_fifo_use = 1-thr_urx_fifo_use;
		// �ָ������ж�
		thr_func.pf_ie_rx_dat(1);
	}

}
//#endif 

/*************************************************************
Name:        FpgaGetTopoStaus
Description: ��ȡ���˽ṹ�Ļ�����Ϣ
Input:
	      opt: ��ںţ���0��
	      p_fp_info: ָ���Ź����Ϣ�Ľṹ��ָ��
	      
Output:      void         
Return:
		1-��ȡ�ɹ�
		0-��ȡʧ��
**************************************************************/
BOOL FpgaGetTopoStaus( UCHAR8 opt, _T_FP_INFO* p_fp_info )
{
	UINT16 tmp;
	
	WTD_CLR;
	
	if (( FPGA_LDST_OK!=fpga_load_status )||( opt>= FP_MAX ))
	{
		return b_FALSE;
	} 
    
	// д��Ҫ�����Ĺ�ں�   
	FPGA_ENABLE_WRITE;
	FPGA_SET_OPT(opt);
	FPGA_DISABLE_WRITE;   
	//printf("opt = %d ",opt);

	// ��ȡ���״̬   
	tmp = FpgaReadRegister( FPGA_REG_OPT_INFO );
	//printf("tmp = %02x\r\n ",tmp);

	// ��������״̬  COMMA_LOCK:1���� 
	p_fp_info->comma_lock = (BM_OPT_COMMA_LOCK==(tmp&BM_OPT_COMMA_LOCK)) ? COMMA_LOCK : COMMA_UNLOCK;

	// �յ���֡���� 
	p_fp_info->rcv_frm_mode = (tmp&BM_UP_DN)>>UP_DN_BITS;

    /*���֡���ж�������:���˿ڽ���֡���� +���˶������� +�Զ˶������� */
	if (  ( 0!=(tmp&BM_OPT_FRM_LOCK) )		// ֡����
		&&( 0!=(tmp&BM_OPS_COMMA_LOCK) )	// ���˶�������
		&&( 0!=(tmp&BM_OPT_COMMA_LOCK) )	// �Զ˶�������
		)
	{
		p_fp_info->frm_lock = FRAME_LOCK;
	}
	else
	{
		p_fp_info->frm_lock = FRAME_UNLOCK;
	}

	//�ڵ����м���������֡����ʱ��Ч        
	p_fp_info->re_cnt = (UCHAR8)(tmp&0x00ff);

    /*0/1------ĩ��REû���յ�/�յ�����һ��˿�*/
	if ( BM_OPS_END_YES == (tmp&BM_OPS_END_YES) )
	{
		//D7-0��ĩ��RE�յ�����һ��˿ڽڵ����м��� ,D15-8��ĩ��RE�յ�����һ��˿����
		tmp = FpgaReadRegister( FPGA_REG_OPS_INFO );  
		//D7λ�� 1��ʾ �Զ˿ڴ��ڣ�D0~D6��ʾ�Զ˻��Ĺ�ں� Ϊ 1~8
		#ifdef  CLIENT_XINMIN	// ����Ҫ������������
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
Description: ����ģ��״̬
Input:
	fp_no: ��ں�
Output:void         
Return:
	b_TRUE - ����
	b_FALSE - �쳣
**************************************************************/
BOOL FpgaGetSfpStatus( UINT32 fp_no )
{
	if ( fp_no>=FP_MAX )
	{
		return b_TRUE;
	}

	return b_TRUE;		// ��ʱ��֧�ֶ�ȡ��ģ��״̬��ȫ����������
}



/*************************************************************
Name:FpgaTest         
Description:����FPGA���߶�д�Ƿ�����
Input:void
Output:void      
Return:	0:ʧ�ܣ�1: �ɹ�            
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
Description:FPGA����
Input:void          
Output:void         
Return:
	0�����سɹ�
	1������ʧ��
	2��δ���ּ����ļ�  
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
		
		if ( 1==result)			//���سɹ�
		{

			for(i=0;i<200;i++)
			{
				//��д��ַ0д��0xA5A5,�Ӷ���ַ0�����ж�
				FpgaWriteRegister(FPGA_REG_WRITE_PROTECT, 0xA5A5);
				if ( (UINT16)FpgaReadRegister(FPGA_REG_WRITE_CHECK) == 0x5A5A)
				{
					// FPGA��������
					fpga_load_status = FPGA_LDST_OK;
					return 0;
				}
				WTD_CLR;
				//TRACE_INFO("FpgaLoadAll---0�Ĵ�����֤ʧ��return 0\r\n");			
			}
			return 0;
		}
		
	}
	fpga_load_status = FPGA_LDST_FAIL;
	return 1;
}

/*************************************************************
Name: FpgaAttOutput
Description: ATT˥�����������
Input: 1-ȫ˥��0-����
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
Description:  ѡ����ʱ϶
Input: reg_add ��ַ
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
Description:��FPGAд�Ĵ���д����
Input:��ַ������
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
		//��ַ��Χ���
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
Description:��FPGA���Ĵ���������
Input:��ַ
Output:void         
Return:����   
**************************************************************/
UINT16 FpgaReadRegister(UINT16 add)
{
	UCHAR8 reg_type;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return;
	}

	reg_type = (add>>12)&0x0F;

	add &= 0x0FFF;
	
	switch( reg_type )
	{
		case 0x00:
			//ֻ���Ĵ�����ַ
			return *(p_ext_16+(add<<1));	
		break;
			
		case 0x08:
			//ֻд�Ĵ�����ַ���ӻ����ȡ
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
		
		case 0x1://1�ֽ�ͨ�����߼���A�β���
			//if (0X00==add  )
			{
				return sys_param_1b[add].val;
			}
			return 0;
		break;

		case 0x2://2�ֽ�ͨ�����߼���B�β���
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
Description:����FPGA����
Input:void
Output:void         
Return:void
**************************************************************/
void FpgaConfigPara(void)
{
	WTD_CLR;

	FPGA_ENABLE_WRITE;

	// ��ʼ����ڣ�ȫ���ر�
	FpgaWriteRegister(FPGA_REG_OPT_ON, 0);
		
	// ��λ�������IO
	FpgaWriteRegister( FPGA_REG_EX_DEV_CTL, 
		BM_EX_PLL_CLK|BM_EX_PLL_DAT|BM_EX_BA_PLL_LE|BM_EX_BB_PLL_LE|BM_EX_FA_PLL_LE|BM_EX_FB_PLL_LE );

	// ���ù���ģʽ
	FpgaWriteRegister( FPGA_REG_A_ATT_CTL, ATT_MODE_NORMAL );		// A��ATT��������ģʽ
	FpgaWriteRegister( FPGA_REG_B_ATT_CTL, ATT_MODE_NORMAL );		// B��ATT��������ģʽ
	FpgaWriteRegister( FPGA_REG_C_ATT_CTL, ATT_MODE_NORMAL );		// A��ATT��������ģʽ
	FpgaWriteRegister( FPGA_REG_D_ATT_CTL, ATT_MODE_NORMAL );		// B��ATT��������ģʽ
		
	UsNopDelay(200000);
	
	FPGA_DISABLE_WRITE;
	
	

	ReadWriteTF(0,1,0x0FB,0X0A);
	ReadWriteTF(1,1,0x0FB,0X0B);
	ReadWriteTF(2,1,0x0FB,0X0B);
	//ReadWriteTF(3,1,0x0FB,0X0B);	
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( FPGA_REG_ATT_FULL_REDUCE, 0 );		// att1��˥	
	FPGA_DISABLE_WRITE;
	
	
	WTD_CLR;
	
}


/*************************************************************
Name:		CheckClkMode
Description: ���FPGAʱ��
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
Description:FPGA��������ʼ��
Input:void
Output:void      
Return:void        
**************************************************************/
void AfterFpgaLoad(void) 
{
	CHAR8 ret_val;
	UINT16 reg_val;

	//TRACE_INFO("Reset FPGA.\r\n");

	// ��ȡAB��ͨѶ��ʽ
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

	//����汾	
	reg_val = FpgaReadRegister(FPGA_REG_EDITION_INFO); 
	sys_param_2b[MADD_PRI_SOFT_V].val = MCU_SOFT_VER|((reg_val<<8)&0xFF00);
	
	//PCB�汾��    
	reg_val = FpgaReadRegister(FPGA_REG_PCB_VERSION); 
	sys_param_2b[MADD_PRI_HARD_V].val = reg_val;	//hard_ware_v;
	
	//��ȡˮӡ�ļ� 
	FpgaReadRegister(FPGA_REG_IRQ_CLEAN);	//ˮӡ������ʼ��
	
	for (ret_val=0; ret_val<sys_param_asc[MADD_PRI_FPGA_DATE].length; ret_val++)
	{
		str_pri_fpga_date[ret_val] = (CHAR8)FpgaReadRegister(FPGA_REG_WATER_PRINT);
	}      
	for (ret_val=0; ret_val<sys_param_asc[MADD_PRI_FPGA2_DATE].length; ret_val++)
	{
		str_pri_fpga2_date[ret_val] = ' ';
	}	
	//��ʼ����ǰ���˽ṹ���RE��ʱ����ֵ
	//InitTopoInfo();
}		

/*************************************************************
Name:FpgaGetChannelCount         
Description: ��FPGA��ȡͨ����
Input:void
Output:void      
Return:-1:ʧ�ܣ�1: �ɹ�            
**************************************************************/
void FpgaGetChannelCount()
{
	UINT16 tmp;
	UINT16 i;
	
	tmp = FpgaReadRegister(FPGA_REG_CH_COUNT);		// ��FPGA��ȡͨ����
	#if defined CLIENT_JIZHUN
	sys_param_1b[MADD_A_CHANNEL_COUNT].val = tmp&0x1F>>0;		// A��֧�ֵ�ͨ����
	sys_param_1b[MADD_B_CHANNEL_COUNT].val = 0;		// B��֧�ֵ�ͨ����
	sys_param_1b[MADD_C_CHANNEL_COUNT].val = 0;			// C��֧�ֵ�ͨ����
	sys_param_1b[MADD_D_CHANNEL_COUNT].val = 0;		// D��֧�ֵ�ͨ����
	#else 
	sys_param_1b[MADD_A_CHANNEL_COUNT].val = tmp&BM_A_CH_COUNT;			// A��֧�ֵ�ͨ����
	sys_param_1b[MADD_B_CHANNEL_COUNT].val = (tmp&BM_B_CH_COUNT)>>8;		// B��֧�ֵ�ͨ����
	sys_param_1b[MADD_C_CHANNEL_COUNT].val = (tmp&BM_C_CH_COUNT)>>4;			// C��֧�ֵ�ͨ����
	sys_param_1b[MADD_D_CHANNEL_COUNT].val = (tmp&BM_D_CH_COUNT)>>12;		// D��֧�ֵ�ͨ����
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
Description:  ���ƻ���ͳ��
Input:        time   -  �೤ʱ��ͳ��һ��
              enable -  ʹ�ܿ���
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
Description:��ʼ��FPGA
Input:void
Output:void      
Return:-1:ʧ�ܣ�1: �ɹ�            
**************************************************************/
BOOL InitFpga(void)
{
	UCHAR8 tmp;

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA���ϣ�����
		return b_FALSE; 
	}

	
	WTD_CLR;
	//TRACE_INFO("Init FPGA.\r\n");
	CLR_FPGA_RST_PIN;	//PIO_Clear(fpga_reset);
	UsNopDelay(10); 
	SET_FPGA_RST_PIN;	//PIO_Set(fpga_reset);
	
	// ��ȡAB��֧�ֵ�ͨ���� 
	FpgaGetChannelCount();

	//����д�Ĵ���
	FpgaConfigPara();

	
	InitPartA();
	InitPartB();
	InitPartC();
	InitPartD();
	//FPGAƵ���������
	// SetFpgaFreqAdj();

	// FPGA�¶Ȳ���ϵ��
	FpgaSetTempAdjustTable();

	// ʹ�ܻ�����ͳ��,15����
	FpgaEnableTrafficCtl( TRAFFIC_TIME, 1 );


	
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_SHOW_ERROR, 0xF000);//����澯��
	FPGA_DISABLE_WRITE;
	
	return b_TRUE;
	
}


/*************************************************************
Name:    	  FpgaMakeAttAdjMsgHead         
Description:   ������ݵ�att_adj_buff������

Input:         len   - ��������ݳ���
               p_dat - ����ָ��
Output:  
Return:        void            
**************************************************************/
void FpgaMakeAttAdjMsgHead( UINT32 len, UCHAR8 * p_dat )
{
	UINT32 i;
 
	if ( len>512 ) return;

	// ��λ���ݳ���
	fpga_att_adj_st.dat_len = 0;

	// ��������
	for ( i=0; i<len; i++ )
	{
		att_adj_buff[fpga_att_adj_st.dat_len++] = *p_dat++;
	}
}


/*************************************************************
Name:         FpgaGetAdDaPow         
Description:  ���REC��AD��DA����
Input:        ab_flag   -  A��,B��ѡ��
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
Description:  �Ѵ�RE��ȡ������ѡƵ���ʱ��浽������
Input:        p_dat -ָѡƵ�������ݵ� ָ��ͷ
Output:       void      
Return:       void          
**************************************************************/ 
void FpgaHandlePsfAck( UCHAR8 * p_dat )
{
	if ( 1==fpga_att_adj_st.is_wait )
	{

		// ����1�ֽڼĴ������ԣ�2�ֽڵ�ַ
		p_dat += 4; 

		TRACE_INFO_WP("-------------------fpga_att_adj_st.dat_len=%d,H=%04X,L=%04X\r\n",fpga_att_adj_st.dat_len,*(p_dat+3)<<8|*(p_dat+2),*(p_dat+1)<<8|*(p_dat));		
		// ����Psf���ݵ�16λ
		att_adj_buff[ fpga_att_adj_st.dat_len++] = *p_dat++;
		att_adj_buff[ fpga_att_adj_st.dat_len++] = *p_dat++;
		
		// ����1�ֽڼĴ������ԣ�2�ֽڵ�ַ
		p_dat += 4;  
		// ����Psf���ݸ�16λ
		att_adj_buff[ fpga_att_adj_st.dat_len++] = *p_dat++;
		att_adj_buff[ fpga_att_adj_st.dat_len++] = *p_dat++;
		// ����ȴ���־   
		fpga_att_adj_st.is_wait = 0;
		TRACE_INFO_WP("-------------------0=%X,1=%X,2=%X,3=%X\\r\n",att_adj_buff[ fpga_att_adj_st.dat_len-4],att_adj_buff[ fpga_att_adj_st.dat_len-3],att_adj_buff[ fpga_att_adj_st.dat_len-2],att_adj_buff[ fpga_att_adj_st.dat_len-1]);		
		
	}
}


/*************************************************************
Name:         FpgaAttStepAdj        
Description:  ѡ��ҪУ����ATT����д�벽��ֵ
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
		// �������У׼,3att 
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
		// ��������У׼ 1att 
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
Description:  У��ATT�����
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
		// ��ʼУ׼
		if ( 0 == fpga_att_adj_st.is_wait )
		{
			//REC������� У׼ģʽ����3��ATT������Ϊ0 
			FpgaEnterAttAdjMode( fpga_att_adj_st.ab_flag );
			WTD_CLR;
			UsNopDelay(1000*1000);
			WTD_CLR;
			UsNopDelay(1000*1000);
			//WTD_CLR;
			//UsNopDelay(1000*1000);	
			WTD_CLR;
			// ��RE��ȡѡƵ���ʼĴ���   32λ 
			GetPsfFromRe( fpga_att_adj_st.ab_flag, fpga_att_adj_st.ud_flag );
			// ��ȡREC ����� AD��DA����      
			FpgaGetAdDaPow( fpga_att_adj_st.ab_flag );
			
			fpga_att_adj_st.adj_st= ATT_ADJ_ST_WAIT_MAX_PSF;
			// �õȴ���־
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

			// �����ݷ��ظ�����
			SendMsgPkt( fpga_att_adj_st.dat_len, att_adj_buff );
			// ״̬����λ
			fpga_att_adj_st.adj_st  = ATT_ADJ_ST_IDLE; 
			fpga_att_adj_st.is_wait = 0;  
			// ���У׼��־λ
			sys_work_info &= (~SYSTEM_FLAG_ATT_ADJ);
		} 
		
		return;
	}

	if ( ATT_ADJ_ST_STEP_ADJ== fpga_att_adj_st.adj_st )
	{
//		TRACE_INFO("FpgaAttAdjust_ATT_ADJ_ST_STEP_ADJ(%d)\r\n",fpga_att_adj_st.step);			
		// ����У׼ 
		if ( fpga_att_adj_st.step>=64 )
		{
			// ������ɣ������ݷ��ظ�����
			SendMsgPkt( fpga_att_adj_st.dat_len, att_adj_buff );

			// ״̬����λ  
			fpga_att_adj_st.adj_st  = ATT_ADJ_ST_IDLE; 
			fpga_att_adj_st.is_wait = 0; 
			
			// ���У׼��־λ
			sys_work_info &= (~SYSTEM_FLAG_ATT_ADJ);
			
		}
		else
		{
			FpgaAttStepAdj();
			WTD_CLR;
			UsNopDelay(50000);
			//TRACE_INFO("FpgaAttAdjust_ATT_ADJ_ST_STEP_ADJ(%d)\r\n",fpga_att_adj_st.step);
			// ��RE��ȡѡƵ���ʼĴ���
			GetPsfFromRe( fpga_att_adj_st.ab_flag, fpga_att_adj_st.ud_flag );
			fpga_att_adj_st.adj_st= ATT_ADJ_ST_WAIT_STEP_PSF;
			// �õȴ���־
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
Description: FPGA����У׼ģʽ
Input: 
	      ab_flag: AB�α�־
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
		tmp |= (ATT_MODE_ADJUST|ATT_WORK_EN);//|ATT_MANUAL);  // ˥��У׼ģʽ  
		FpgaWriteRegister(FPGA_REG_A_ATT_CTL, tmp);//˥��У׼ģʽ  
		//FpgaWriteRegister(FPGA_REG_ATT_FULL_REDUCE, tmp);//����˥����ȫ˥
		SetAtt1(TF_A,0X1F);
		
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_A_ATT3_CAL, 0X00 ); // ����˥������˥
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
		//FpgaWriteRegister(FPGA_REG_ATT_FULL_REDUCE, tmp);//����˥����ȫ˥

		// ����˥������˥
		SetAtt1(TF_B,0X1F);
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_B_ATT3_CAL, 0X00 ); // ����˥������˥
		FpgaWriteRegister(FPGA_REG_B_ATT3_EN,0x01);
		UsNopDelay(20);

		if ( FPGA_B_NT_TD_WB !=fpga_cfg.b_ultra_info)	// TD�����
		{
			FPGA_SET_CHANNEL(0);		// ����ͨ����
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
		//FpgaWriteRegister(FPGA_REG_ATT_FULL_REDUCE, tmp);//����˥����ȫ˥
		SetAtt1(TF_C,0X1F);
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0); //��0ͨ��
		FpgaWriteRegister(FPGA_REG_C_ATT3_CAL, 0X00 ); // ����˥������˥
		FpgaWriteRegister(FPGA_REG_C_ATT3_EN,0x01);
		UsNopDelay(20);
		TRACE_INFO("\r\n");
		TRACE_INFO("FpgaAttAdjust_ 66666666666666666666666666666-----------\r\n");
		TRACE_INFO("\r\n");
		TRACE_INFO("\r\n");
		FPGA_SET_CHANNEL(0);		// ����ͨ����
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
		// ����˥������˥
	


	}
	else if ( SYS_D_FLAG == abcd_flag )
	{
		float FREQ_CTL_Val=0;
		
		tmp = FpgaReadRegister(FPGA_REG_D_ATT_CTL);
		tmp &= 0xFFFC;
		tmp |= (ATT_MODE_ADJUST|ATT_WORK_EN);//|ATT_MANUAL);
		FpgaWriteRegister(FPGA_REG_D_ATT_CTL, tmp);
		//FpgaWriteRegister(FPGA_REG_ATT_FULL_REDUCE, tmp);//����˥����ȫ˥

		// ����˥������˥
		SetAtt1(TF_D,0X1F);
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0); //��0ͨ��
		FpgaWriteRegister(FPGA_REG_D_ATT3_CAL, 0X00 ); // ����˥������˥
		FpgaWriteRegister(FPGA_REG_D_ATT3_EN,0x01);
		UsNopDelay(20);
		FPGA_SET_CHANNEL(0);		// ����ͨ����
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
			FpgaWriteRegister(FPGA_REG_D_ATT1_CAL, tmp ); // ����˥������˥
			UsNopDelay(20);
			//FpgaWriteRegister(FPGA_REG_C_ATT2_CAL, 0 ); // ����˥������˥
			FpgaWriteRegister(FPGA_REG_D_ATT3_CAL, tmp ); // ����˥������˥
			UsNopDelay(20);
		}*/


	}	
	FPGA_DISABLE_WRITE;
}

/*************************************************************
Name:FpgaExitAttAdjMode
Description: FPGA�˳�У׼ģʽ
Input: 
	ab_flag: AB�α�־
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
		ReadWriteTF(TF_A,1,0X56,0X00);//�����У����ͨ����	

		if(version_number == VERSION_50M_IN_V5)
		{
			FPGA_ENABLE_WRITE;
			FPGA_SET_CHANNEL(0);		// ����ͨ����
			FpgaWriteRegister(FPGA_REG_A_D_FREQ_CTL_L_12, 0x8000);
	 		FpgaWriteRegister(FPGA_REG_A_D_FREQ_CTL_H_14, 0x0000);
			
			//FpgaWriteRegister(FPGA_REC_D_TD_WORK_MODE, TD_WM_NORMAL);
			//sys_param_1b[MADD_D_TD_WORK_MODE].val = TD_WM_NORMAL;
			FPGA_DISABLE_WRITE;
			//�˳�У׼����ʱ����������Ƶ����
			tmp=ReadWriteTF(TF_A,0,0x057,0x01);
			tmp&=(~0x01<<0);
			ReadWriteTF(TF_A,1,0x057,tmp);		
			// ��������			
			//�˳�У׼����������Ƶ����
			tmp=ReadWriteTF(TF_D,0,0x053,0x01);
			tmp&=~((0x01<<2)|(0x01<<4));			
			ReadWriteTF(TF_A,1,0x053,tmp);		

			ReadWriteTF(TF_A,1,0X56,0X00);//�����У����ͨ����
		}
	}
	else if ( SYS_B_FLAG == ab_flag )
	{
		data=0x0b;
		reg= FPGA_REG_B_ATT_CTL;
		FPGA_ENABLE_WRITE;
		if(NET_TYPE_TD!=fpga_cfg.b_net_type)
		{
			FPGA_SET_CHANNEL(0);		// ����ͨ����
			FpgaWriteRegister(FPGA_REG_B_FREQ_CTL_L_12, 0x8000);
	 		FpgaWriteRegister(FPGA_REG_B_FREQ_CTL_H_14, 0x0000);			
		}
		FpgaWriteRegister(FPGA_REG_TD_WORK_MODE, TD_WM_NORMAL);
		sys_param_1b[MADD_TD_WORK_MODE].val = 0;
		FPGA_DISABLE_WRITE;		
		//�˳�У׼����ʱ����������Ƶ����
		tmp=ReadWriteTF(TF_B,0,0x057,0x01);
		tmp&=(~0x01<<0);
		ReadWriteTF(TF_B,1,0x057,tmp);		
	// ��������			
		//�˳�У׼����������Ƶ����
		tmp=ReadWriteTF(TF_B,0,0x053,0x01);
		tmp&=~((0x01<<3)|(0x01<<5));			
		ReadWriteTF(TF_B,1,0x053,tmp);		
		
		ReadWriteTF(TF_B,1,0X56,0X00);//�����У����ͨ����
		
	} 
	else if ( SYS_C_FLAG == ab_flag )
	{
		data=0x0b;
		reg= FPGA_REG_C_ATT_CTL;
		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0);		// ����ͨ����
		FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_L_12, 0x8000);
 		FpgaWriteRegister(FPGA_REG_C_FREQ_CTL_H_14, 0x0000);
		
		FpgaWriteRegister(FPGA_REC_C_TD_WORK_MODE, TD_WM_NORMAL);
		sys_param_1b[MADD_C_TD_WORK_MODE].val = TD_WM_NORMAL;
		FPGA_DISABLE_WRITE;		
		
		//�˳�У׼����ʱ����������Ƶ����
		tmp=ReadWriteTF(TF_C,0,0x057,0x01);
		tmp&=(~0x01<<1);
		ReadWriteTF(TF_C,1,0x057,tmp);		
	// ��������			
		//�˳�У׼����������Ƶ����
		tmp=ReadWriteTF(TF_C,0,0x053,0x01);
		tmp&=~((0x01<<3)|(0x01<<5));			
		ReadWriteTF(TF_C,1,0x053,tmp);	
		ReadWriteTF(TF_C,1,0X56,0X00);//�����У����ͨ����
				
	} 
	else if ( SYS_D_FLAG == ab_flag )
	{
		data=0x0b;
		reg= FPGA_REG_D_ATT_CTL;

		FPGA_ENABLE_WRITE;
		FPGA_SET_CHANNEL(0);		// ����ͨ����
		FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_L_12, 0x8000);
 		FpgaWriteRegister(FPGA_REG_D_FREQ_CTL_H_14, 0x0000);
		
		FpgaWriteRegister(FPGA_REC_D_TD_WORK_MODE, TD_WM_NORMAL);
		sys_param_1b[MADD_D_TD_WORK_MODE].val = TD_WM_NORMAL;
		FPGA_DISABLE_WRITE;
		//�˳�У׼����ʱ����������Ƶ����
		tmp=ReadWriteTF(TF_D,0,0x057,0x01);
		tmp&=(~0x01<<0);
		ReadWriteTF(TF_D,1,0x057,tmp);		
	// ��������			
		//�˳�У׼����������Ƶ����
		tmp=ReadWriteTF(TF_D,0,0x053,0x01);
		tmp&=~((0x01<<2)|(0x01<<4));			
		ReadWriteTF(TF_D,1,0x053,tmp);		

		ReadWriteTF(TF_D,1,0X56,0X00);//�����У����ͨ����

	} 
	// �˳�У׼ģʽ
	tmp = FpgaReadRegister(reg);
	
	tmp &= (~(ATT_MODE_MASK|ATT_MANUAL)); //�Զ�ATT˥��  
	tmp |= ATT_MODE_NORMAL;  //ATT��������ģʽ   
	
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
//	{	// �������
		//У׼����ʱ����������Ƶ����
		tmp=ReadWriteTF(TF_C,0,0x057,0x01);
		tmp&=(~0x01<<1);
		ReadWriteTF(TF_C,1,0x057,tmp);	
//	}    
//	else 
//	{	// ��������
				
		//У׼����ʱ��������Ƶ���أ���������Ƶ����
		tmp=ReadWriteTF(TF_C,0,0x057,0x01);
		tmp|=(0x01<<1);
		ReadWriteTF(TF_C,1,0x057,tmp);
 
		tmp=ReadWriteTF(TF_C,0,0x053,0x01);
		tmp&=~((0x01<<3)|(0x01<<5));
			
		ReadWriteTF(TF_C,1,0x053,tmp);				
//	}
	FPGA_DISABLE_WRITE;
#endif 	
	// ���¸��ݲ�������FPGA�Ĵ���
	module_param_chg_flag = 0xFFFFFFFF;

}

/*************************************************************
Name:         FpgaSetTempAdjustTable
Description:  ��FPGAд���¶Ȳ������
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
Description:����񱣴浽FLASH��
Input:
	p_data:����ָ��
	att_count: ˥��������
	ab_flag: AB��ѡ��
	ud_flag: 1-���У�0-����
Output:void
Return:0:ʧ��1:�ɹ�
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

	// Ginp, 4�ֽ�, ������
	for ( i=0; i<4; i++ )
	{
		buff[w_len++] = *p_data++;
	}

	// Gcic, 4�ֽ�, ������
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
Description: ����GSM�Ĵ���
Input:       BW - �����־
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
Description: ����GSMƵ��ż���Ƶ���֣�REC�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
//NT32 CalcGsmFreqWord( INT32 freq_code, FLOAT32 fd_local )
INT32 SearchFpCalcGsmFreqWord( INT32 freq_code, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   
/*------------����----------------*/	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
    freq_point = ConvGsmFcToFreqDL(freq_code);
	TRACE_INFO("<fp=%f, ful=%f>\r\n", freq_point, down_fre);

	TRACE_INFO("GSM_(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val[d=%d][f/1000=%f],fu_local=%f\r\n",(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val,(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/1000.0,down_fre);	
	
	//down_fre +=(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/10000.0;

	TRACE_INFO("freq_point = %f,fu_local=[%f]\r\n",freq_point,down_fre);
	

	// �������ֱ���Ƶ��    
	digit_freq = CalcGsmdfu( freq_point, 10*down_fre); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	freq_word = CalcFpgaFw_AB( digit_freq )/10.0;  
	*down_fre_word=freq_word;
	if(freq_point<10*down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	
/*------------����----------------*/	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
    freq_point = ConvGsmFcToFreqUL(freq_code);
	TRACE_INFO("<fp=%f, ful=%f>\r\n", freq_point, up_fre);

	TRACE_INFO("GSM_(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val[d=%d][f/1000=%f],fu_local=%f\r\n",(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val,(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/1000.0,up_fre);	
	
	up_fre +=(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/10000.0;

	TRACE_INFO("freq_point = %f,fu_local=[%f]\r\n",freq_point,up_fre);
	
	// �������ֱ���Ƶ��    
	digit_freq = CalcGsmdfu( freq_point, 10*up_fre); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
Description: ����GSMƵ��ż���Ƶ���֣�REC�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
//NT32 CalcGsmFreqWord( INT32 freq_code, FLOAT32 fd_local )
INT32 CalcGsmFreqWord( INT32 freq_code,  FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   

	
	printf("freq_code = %d,up_fre=[%f],down_fre = %f\r\n",freq_code,up_fre,down_fre);
/*------------����----------------*/	
	
	freq_point = ConvGsmFcToFreqDL(freq_code);
	printf("freq_point = %f\r\n",freq_point);	

	// �������ֱ���Ƶ��    
	digit_freq = CalcGsmdfu( freq_point, 10*down_fre); 
	printf("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	//freq_word = CalcFpgaFw_AB( digit_freq )/10.0; 
	freq_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10.0;
	printf("freq_word = %02x\r\n",freq_word);  
	
	*down_fre_word=freq_word;
	if(freq_point<10*down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	
	printf("down_fre_word = %02x\r\n",*down_fre_word);  
	
/*------------����----------------*/	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	freq_point = ConvGsmFcToFreqUL(freq_code);
	printf("freq_point = %f\r\n",freq_point);
	
	// �������ֱ���Ƶ��    
	digit_freq = CalcGsmdfu( freq_point, 10*up_fre); 
	
	printf("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
Description: ����GSMƵ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcDcsFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   
	
	if (!VAL_IN_RANGE( freq_code, 512, 885 ))
	{
		return 0;
	} 

	freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1805;
   TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, fu_local); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, fu_local); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	freq_word = CalcFpgaFw_AB( digit_freq );   
	TRACE_INFO("freq_word = %08x\r\n",freq_word);  
	return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}
#endif 
/*************************************************************
Name: CalcGsmFreqWord
Description: ����GSMƵ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcDcsFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   
	
	if (!VAL_IN_RANGE( freq_code, DCS_MIN_FRE_CODE_CNMOBILE, 885 ))
	{
		return 0;
	} 
/*--------------����------------------------*/
	freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;
   TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, down_fre*10); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	//*down_fre_word = CalcFpgaFw_A( digit_freq )/10; 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10;
    TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<10*down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------����------------------------*/
	freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1710*10;
   TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, up_fre*10); 
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
Description: ����WCDMAplloutputfreq����9363
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 WcdmaFreqWordConfigureTxRxPll( FLOAT32 up_fre,  FLOAT32 down_fre)
{
	FLOAT32 tmp,tmp1;
	UINT32 data;
	

	ReadWriteTF(TF_A,1,0X014,0X03);		 //оƬ����ȴ�ģʽ����ʱоƬ�������
	
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
	ReadWriteTF(TF_A,1,0X014,0X23);		 //������ɺ�оƬ������������״̬��	

	return 0;
}

/*************************************************************
Name: LteFddFreqWordConfigureTxRxPllFreqWordConfigureadTxRxPll
Description: ����LTEFDDplloutputfreq����9363
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
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


	ReadWriteTF(abcd_flag,1,0X014,0X03);		 //оƬ����ȴ�ģʽ����ʱоƬ�������
	
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

	ReadWriteTF(abcd_flag,1,0X014,0X23);		 //������ɺ�оƬ������������״̬��	

	ReadWriteTF(abcd_flag,1,0X53,0Xff);		 //	
	UsNopDelay(1*1000);
	ReadWriteTF(abcd_flag,1,0X53,0X00);		 //	

//	TRACE_INFO("1x233data1=%X\r\n",ReadWriteTF(abcd_flag,0,0X233,data1 ));

	return 0;
}

/*************************************************************
Name: LteFddFreqWordConfigureTxRxPllFreqWordConfigureadTxRxPll
Description: ����LTEFDDplloutputfreq����9363
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
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
	
	ReadWriteTF(abcd_flag,1,0X014,0X03);		 //оƬ����ȴ�ģʽ����ʱоƬ�������
	
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
	
	ReadWriteTF(abcd_flag,1,0X53,0Xff);		 //������ɺ�оƬ������������״̬��	
	UsNopDelay(1*1000);
	ReadWriteTF(abcd_flag,1,0X53,0X00);		 //������ɺ�оƬ������������״̬��	

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

	ReadWriteTF(abcd_flag,1,0X014,0X23);		 //������ɺ�оƬ������������״̬��	

	return 0;
}

/*************************************************************
Name: CalcGsmFreqWord
Description: ����wcdmaƵ��ż���Ƶ����,
Input:
	void 
Output:        
Return:
	Ƶ����
**************************************************************/
void CalcWcdmaPLLoutputFreq(FLOAT32 *up_fre,FLOAT32 *down_fre )
{
	FLOAT32 plloput_freq;	// Ƶ�� 
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
	//����Ƶ��
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

	//����Ƶ��
	//����ģʽ
	*down_fre = (FLOAT32)(freq_code_min+freq_code_max)*0.2*100/2;
	TRACE_INFO("up_fre = %f,down_fre = %f\r\n",*up_fre,*down_fre);
#if 0
	if(FpgaReadRegister(FPGA_REG_B_ATT_CTL)&0X03 == 0)
	{
		*down_fre = (FLOAT32)(freq_code_min+freq_code_max)*0.2*100/2;
	}
	//У׼ģʽ
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
Description: ����wcdmaƵ��ż���Ƶ����,
Input:
	void 
Output:        
Return:
	Ƶ����
**************************************************************/
FLOAT32 CalcLteTdPLLoutputFreq(UCHAR8 flag)
{
	FLOAT32 plloput_freq;	// Ƶ�� 
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


	//�̶�����
	if(version_number == VERSION_50M_IN_V4) //�ɹ̶������Ϊ��̬���� 201601070950
	{
		//plloput_freq=2345*100;
		
	}
		
	//plloput_freq=(FLOAT32)((freq_code_min+freq_code_max)/2-38650)*100*0.1+100*2300;
 	TRACE_INFO("1freq_code_min=[%X],freq_code_max=[%X],plloput_freq=[%f]\r\n",freq_code_min,freq_code_max,plloput_freq);
	return ((INT32)plloput_freq); 
	
}


/*************************************************************
Name: CalcGsmFreqWord
Description: ����wcdmaƵ��ż���Ƶ����,
Input:
	void 
Output:        
Return:
	Ƶ����
**************************************************************/
FLOAT32 CalcLteFddPLLoutputFreq(UCHAR8 flag)
{
	FLOAT32 plloput_freq;	// Ƶ�� 
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
Description: ����GSMƵ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcWcdmaFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ�� 
	FLOAT32 digit_freq;	// ����Ƶ�� 
	INT32   freq_word;     

	//����
	freq_point = freq_code*0.2*100;
	TRACE_INFO("freq_point = %f,fu_local= %f,freq_code=[%X]\r\n",freq_point,down_fre,freq_code);

	// �������ֱ���Ƶ��    
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
	

	// ����Ƶ����    
	TRACE_INFO("freq_word = %08x\r\n",*down_fre_word);  
	//------------------------------------------------------//
	//����
	freq_point = freq_code*0.2*100 -190*100;
	TRACE_INFO("freq_point = %f,fu_local= %f\r\n",freq_point,up_fre);

	// �������ֱ���Ƶ��    
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
Description: ����LteFddƵ��ż���Ƶ����,�µļ��㹫ʽ
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcWCDMAFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   

/*--------------����------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;
	//freq_point = (FLOAT32)(freq_code-0) * 0.01 + 866;
	freq_point = freq_code*0.2;
	down_fre = down_fre/100.0;
	up_fre = up_fre/100.0;


	TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, down_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	//*down_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------����------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1710;
	//freq_point = (FLOAT32)(freq_code-0) * 0.01 + 821;
	freq_point = freq_code*0.2 -190;
	TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, up_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
Description: ����GSMƵ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcTDFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// Ƶ�� 
	FLOAT32 digit_freq;	// ����Ƶ�� 
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

	// �������ֱ���Ƶ��    
	digit_freq = CalcWcdmafu( freq_point*10, fu_local*10); 
	TRACE_INFO("CalcTDdigit_freq = %.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
Description: ����LteFddƵ��ż���Ƶ����,�µļ��㹫ʽ
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcTDSCDMAFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   

/*--------------����------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;
	//freq_point = (FLOAT32)(freq_code-0) * 0.01 + 866;
	freq_point = 2017.5;

	TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, down_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	//*down_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------����------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1710;
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 821;
	TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, up_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
Description: ����GSMƵ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 SearchFpCalcTDFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// Ƶ�� 
	FLOAT32 digit_freq;	// ����Ƶ�� 
	INT32   freq_word;     
	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
    freq_point = freq_code*0.2;
	//freq_point = 2010+(freq_code-36200)*0.1; 
	//TRACE_INFO("freq_point = %0.2f,fu_local=[%0.2f]\r\n",freq_point,fu_local);

	TRACE_INFO("TDS_(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val[d=%d][f/1000=%f],fu_local=%f\r\n",(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val,(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/100.0,fu_local);	
	
	fu_local +=(CHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val/1000/10.0*2000/2300;

	TRACE_INFO("freq_point = %f,fu_local=[%f]\r\n",freq_point,fu_local);
	
	// �������ֱ���Ƶ��    
	digit_freq = CalcWcdmafu( freq_point*10, fu_local*10); 
    TRACE_INFO("digit_freq = %f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	
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
Description: ����GSMƵ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcTetraFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// Ƶ�� 
	FLOAT32 digit_freq;	// ����Ƶ�� 
	INT32   freq_word;     
	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	freq_point = 361+freq_code*0.0125;
	//TRACE_INFO("freq_point = %0.2f\r\n",freq_point);

	// �������ֱ���Ƶ��    
	digit_freq = CalcTdLtefu( freq_point, fu_local); 
	
	if(freq_point>fu_local)
	{
		digit_freq =   freq_point-fu_local; 
	}
	else  
	{
		digit_freq = fu_local-freq_point; 
	}
	 

	// ����Ƶ����    
	//freq_word = CalcFpgaFw_B( digit_freq );   

	freq_word = CalcFpgaFw_AB( digit_freq )/10.0;  	
	//TRACE_INFO("freq_word = %08x\r\n",freq_word);  


	return freq_word//AdjustFpgaFw(freq_word); 
	
}
#endif
INT32 CalcTetraFreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   

	
	//printf("freq_code = %d,up_fre=[%f],down_fre = %f\r\n",freq_code,up_fre,down_fre);
	/*------------����----------------*/	
	
	freq_point = 361+(freq_code-1)*0.0125;

	//printf("freq_point = %f\r\n",freq_point);

	

	// �������ֱ���Ƶ��    
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
	  
	// ����Ƶ����    
	//*down_fre_word = CalcFpgaFw_AB( digit_freq );  
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	//printf("freq_word = %02x\r\n",freq_word);  
	
	//*down_fre_word=freq_word;
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	
	//printf("down_fre_word = %02x\r\n",*down_fre_word);  
	
	/*------------����----------------*/	
	//printf("<fp=%f, ful=%f> ", freq_point, fu_local);
	freq_point = 351+(freq_code-1)*0.0125;
	//printf("freq_point = %f\r\n",freq_point);
	
	// �������ֱ���Ƶ��    
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
	  
	// ����Ƶ����    
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
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcLteTdFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// Ƶ�� 
	FLOAT32 digit_freq;	// ����Ƶ�� 
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
	// �������ֱ���Ƶ��    
	digit_freq = CalcTdLtefu( freq_point, fu_local); 
    //TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
Description: ����LteFddƵ��ż���Ƶ����,�µļ��㹫ʽ
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcLteTddFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   

/*--------------����------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) *10* 0.2 + 1805*10;
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 866;

	TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, down_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	//*down_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------����------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1710;
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 821;
	TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, up_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcLteFddFreqWord( INT32 freq_code, FLOAT32 fu_local )
{
	FLOAT32 freq_point;	// Ƶ�� 
	FLOAT32 digit_freq;	// ����Ƶ�� 
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

	// �������ֱ���Ƶ��    
	digit_freq = CalcWcdmafu( freq_point, fu_local); 
	//digit_freq =0.1;
    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	freq_word = CalcFpgaFw_CD( digit_freq )/100;   
	TRACE_INFO("!!1freq_word = %d\r\n",freq_word);  
   
	if (freq_point<fu_local) freq_word |=0x80000000;	
	return freq_word;//AdjustFpgaFw(freq_word); 
	
}
/*************************************************************
Name: CalcGsmFreqWord
Description: ����LteFddƵ��ż���Ƶ����,�µļ��㹫ʽ
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcLteFddFreqWordNew( INT32 freq_code,FLOAT32 fpga_data_clk,  FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   
	//if (!VAL_IN_RANGE(freq_code, 0, 1400))
	//{
	//	return 0;
	//} 
/*--------------����------------------------*/
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
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, down_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	//*down_fre_word = CalcFpgaFw_CD( digit_freq ); 
	*down_fre_word = CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk);
	TRACE_INFO("*down_fre_word = %x\r\n",*down_fre_word);  	
	if(freq_point<down_fre)
	{
		*down_fre_word |=0x80000000;
	}
	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------����------------------------*/
	//freq_point = (FLOAT32)(freq_code-511) * 0.2 + 1710;
	#if (defined CLIENT_ERRICSON2)
	freq_point = (FLOAT32)(freq_code-0) * 0.01 + 821;
	#elif defined CLIENT_ERRICSON_W

		freq_point = 1950;
	#endif
	TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// �������ֱ���Ƶ��     
	digit_freq = CalcDcsfu( freq_point, up_fre); 
	TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
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
Description: ����GSMƵ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:
	Ƶ����
**************************************************************/
INT32 CalcCdma800FreqWord( INT32 freq_code, FLOAT32 fpga_data_clk, FLOAT32 up_fre, FLOAT32 down_fre, INT32 *up_fre_word,INT32 *down_fre_word )
{
	FLOAT32 freq_point;	// Ƶ��
	FLOAT32 digit_freq;	// ����Ƶ��
	INT32   freq_word;   
	
	if (!VAL_IN_RANGE( freq_code, 1, 333 ))
	{
		return 0;
	} 
/*--------------����------------------------*/
	freq_point = (FLOAT32)(freq_code *10* 0.03 + 870*10);
//   TRACE_INFO("freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, down_fre); 
	
	// �������ֱ���Ƶ��     
	//digit_freq = CalcDcsdfu ( freq_point, down_fre*10); 
	digit_freq = 0*10; 
	*down_fre_word = 0;

	if(digit_freq<0)
	{
		digit_freq=(0-digit_freq);
		*down_fre_word |=( 0x1<<31);
	}
	
//    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	//*down_fre_word |= CalcFpgaFw_AB( digit_freq )/10;   
	*down_fre_word |= CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10;

	TRACE_INFO("down_down_freq_word = %08x\r\n",*down_fre_word);  

/*--------------����------------------------*/
	freq_point = (FLOAT32)(freq_code *10* 0.03 + 825*10);
//   TRACE_INFO("up_freq_point = %0.2f,freq_code=%d, fu_local=%f\r\n",freq_point,freq_code, up_fre); 
	
	// �������ֱ���Ƶ��     
	//digit_freq = CalcDcsfu( freq_point, up_fre*10); 
	digit_freq = 0*10; 

	*up_fre_word = 0;
	if(digit_freq<0)
	{
		digit_freq=(0-digit_freq);
		*up_fre_word |=( 0x1<<31);
	}


//    TRACE_INFO("digit_freq = %0.2f\r\n",digit_freq);  
	  
	// ����Ƶ����    
	//*up_fre_word |= CalcFpgaFw_AB( digit_freq )/10;   
	*up_fre_word |= CALC_FPGA_FRE_WORD(digit_freq,fpga_data_clk)/10;

	TRACE_INFO("up_freq_word = %08x\r\n",*up_fre_word); 	
	//return (freq_word) ;			   
	
	//return AdjustFpgaFw(freq_word); 
	
}

/*************************************************************
Name: FpgaSetTempComp
Params: [seg_sel: 0-A��, 1-B��] [udl_sel: 0-UL����, 1-DL����] [comp: �����Ĵ�����ֵ]
Return: void
Description: ���ò����Ĵ�����ֵ
**************************************************************/
void FpgaSetTempComp( UCHAR8 seg_sel, UCHAR8 udl_sel, UINT16 comp )
{
	UINT16 reg_addr = 0xFFFF;

	// ����ѡ��ȷ���Ĵ�����ַ
	if ( 0==seg_sel )	// A��
	{
		if ( 0==udl_sel )	// ����
		{
			reg_addr = FPGA_REG_A_BT_CMPS;	// ���
		}
		else if ( 1==udl_sel )	// ����
		{
			reg_addr = FPGA_REG_A_FT_CMPS;	// ǰ��
		}
	}
	else if ( 1==seg_sel )	// B��
	{
		if ( 0==udl_sel )	// ����
		{
			reg_addr = FPGA_REG_B_BT_CMPS;	// ���
		}
		else if ( 1==udl_sel )	// ����
		{
			reg_addr = FPGA_REG_B_FT_CMPS;	// ǰ��
		}
	}
	else if ( 2==seg_sel )	// C��
	{
		if ( 0==udl_sel )	// ����
		{
			reg_addr = FPGA_REG_C_BT_CMPS;	// ���
		}
		else if ( 1==udl_sel )	// ����
		{
			reg_addr = FPGA_REG_C_FT_CMPS;	// ǰ��
		}
	}
	else if ( 3==seg_sel )	// D��
	{
		if ( 0==udl_sel )	// ����
		{
			reg_addr = FPGA_REG_D_BT_CMPS;	// ���
		}
		else if ( 1==udl_sel )	// ����
		{
			reg_addr = FPGA_REG_D_FT_CMPS;	// ǰ��
		}
	}
	// ��Ч�ĵ�ַѡ��
	if ( 0xFFFF==reg_addr ) return;

	// д��Ĵ���
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister( reg_addr, comp );
	FPGA_DISABLE_WRITE;
	
}


/*************************************************************
Name:          SentLoadDat      
Description:   ���з��ͼ�������
Input:         Dat - ���͵��ֽ�          
Output:        void           
Return:        void       
**************************************************************/
void SentLoadDatA7(UCHAR8 Dat)
{

#if 1
	UCHAR8 i; 
	//Ϊ�ӿ��߼�����
	//20151120�߼�����ֱ�Ӳ����Ĵ�����ַ
	//volatile unsigned long *DBSRR_SFR=GPIOD_SFR_BASE_SET; 
	//volatile unsigned long *DBRR_SFR=GPIOD_SFR_BASE_RESET; 
	volatile unsigned long *datBSRR_SFR=(unsigned long *)(GPIOD_BASE+0X10); 
	volatile unsigned long *datRR_SFR=(unsigned long *)(GPIOD_BASE+0X14); 
	volatile unsigned long *clkBSRR_SFR=(unsigned long *)(GPIOB_BASE+0X10); 
	volatile unsigned long *clkBRR_SFR=(unsigned long *)(GPIOB_BASE+0X14); 
	for (i = 0;i<8; i++ )
	{ 
		//20151120�����߼�ֱ�Ӳ����Ĵ���
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
		if ( (Dat>>(i-1))&0x01 )//��λ��ǰ
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
Description:FPGA����
Input:�����ļ����ܳ���          
Output:void         
Return:-1:ʧ�ܣ�1: �ɹ�         
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
	
	CLR_FPGA_CS_PIN;      // FPGAƬѡ��   
	TRACE_DEBUG_WP("FpgaLoadAll enter\r\n");
	printf("\r\nCLR_FPGA_CS_PIN\r\n");

  
	//��һ��
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
	
	
	//�ڶ���
	CLR_FPGA_PROGRAM_B_PIN;
	printf("CLR_FPGA_PROGRAM_B_PIN\r\n");
	WTD_CLR;
	UsNopDelay(2000);				//��ʱ 20us   �ȴ� FPGA_INIT_B_ST ����
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
	
	//������
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
	
	
	//���Ĳ�
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
   //�������
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
Description:FPGA����
Input:�����ļ����ܳ���          
Output:void         
Return:-1:ʧ�ܣ�1: �ɹ�         
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

	CLR_FPGA_CS_PIN;      // FPGA��Ƭѡ��Ч

	//UsNopDelay(1000);

	// Fpga�������״̬ 

		

	//��һ��
	CLR_FPGA_NCS1_PIN ;		//����ʱ��
	SET_FPGA_NCONFIG	;	//���� nCONFIG 
	i =0;
	UsNopDelay(100);
	while(0==FPGA_INIT_B)  //�ȴ�GET_FPGA_INIT_B_ST ����
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

	UsNopDelay(350);			        //��ʱ350us  

	//�ڶ���
	CLR_FPGA_NCONFIG ; //����config ��

	UsNopDelay(100);			        //��ʱ350us  
	i=0;
	while(1==FPGA_INIT_B)  //�ȴ�GET_FPGA_INIT_B_ST ����
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

	//������
	SET_FPGA_NCONFIG ; //����config ��
	i= 0 ;
	while(0==FPGA_INIT_B)  //�ȴ�GET_FPGA_INIT_B_ST ����
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
	
	TRACE_DEBUG_WP("FpgaLoad Start\r\n"); // ��λҳ��ַ
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
    //�������
	UsNopDelay(1000); 			//Delay 1ms 
	
	if (GET_FPGA_CONF_DONE)  
	{     
		TRACE_INFO_WP("LOAD SUCCESS-0\r\n");

		SentLoadDatA7(0X00);		//dummy write
		SentLoadDatA7(0X00);		//dummy write

		


		SET_FPGA_NCS1_PIN;


        //���سɹ�,�ӳ�1ms����user mode 
		UsNopDelay(1000);  
		
		
		return 1; 

	} 
	else
	{
		TRACE_INFO_WP("LOAD FAIL-1\r\n");
		
		while (serial_retry--)			  //���Զ෢��CLK
		{	
			if (GET_FPGA_CONF_DONE)
			{
				TRACE_INFO_WP("LOAD SUCCESS-0\r\n");

				SentLoadDatA7(0X00);		//dummy write
				SentLoadDatA7(0X00);		//dummy write


				SET_FPGA_NCS1_PIN;

		        	//���سɹ�,�ӳ�1ms����user mode 
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
Description: ����У׼����AU����У׼ģʽ
Input: 
	      ab_flag: AB�α�־
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
		FpgaWriteRegister(FPGA_REG_A_ATT_CTL, 0x06);//˥��У׼ģʽ 	
		FPGA_SET_CHANNEL(0); //��0ͨ��
		FPGA_DISABLE_WRITE;
		
		SetAtt1(TF_A,0X1F);
		
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_A_ATT3_CAL, 0X00 ); // ����˥������˥
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
Description:  ���沨��У׼����AUƵ��
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
Description:  ���沨��У׼
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
void FpgaGainAdjust()
{
	UINT16 fre_point = 512;

	//printf("adj_st:%d  is_wait:%d\r\n",gain_adj_st.adj_st,gain_adj_st.is_wait);
	if(gain_adj_st.is_wait)//�ȴ�����ִ��
		return;

	switch(gain_adj_st.adj_st)
	{
		case GAIN_ADJ_ST_IDLE:
			gain_adj_st.is_wait = 0;
			break;
		case GAIN_ADJ_ST_SET_AUEU_ADJ_MODE://����У׼ģʽ
			//printf("abcd:%d  ud:%d\r\n",gain_adj_st.ab_flag,gain_adj_st.ud_flag);
			
			
			// �õȴ���־
			gain_adj_st.is_wait = 1;			
			gain_adj_st.adj_st= GAIN_ADJ_ST_IDLE;
			gain_adj_st.fre_point = 512;//��ʼƵ��
			gain_adj_st.step = 0;//�������

			if(gain_adj_st.ud_flag == SYS_DL_FLAG)
			{
				//printf("EU adj\r\n");
				//EU����У׼ģʽ				
				GainAdjSetEUEnterAdjMode( gain_adj_st.ab_flag );
				
			}
			else
			{
				//printf("AU adj\r\n");
				//AU����У׼ģʽ
				GainAdjSetAUEnterAdjMode( gain_adj_st.ab_flag );
				gain_adj_st.is_wait = 0;//������һ������
			}
			WTD_CLR;
			UsNopDelay(1000*1000);
			
			break;
		case GAIN_ADJ_ST_SET_AUEU_FRE://����AU EU��һ��ͨ����Ƶ��
			fre_point = gain_adj_st.fre_point+gain_adj_st.step;//Ƶ�㲽��
			
			//printf("fre_point%d\r\n",fre_point);
			//����AU��Ƶ��
			GainAdjSetAUFrePoint(gain_adj_st.ab_flag,fre_point);
			//����EU��Ƶ��			
			GainAdjSetEUFrePoint(gain_adj_st.ab_flag,fre_point);
			gain_adj_st.is_wait = 1;
			gain_adj_st.adj_st= GAIN_ADJ_ST_GET_EU_SF_POW;
			//gain_adj_st.is_wait = 0;//������һ������
			break;
		case GAIN_ADJ_ST_GET_EU_SF_POW://��ȡEU��һ��ͨ����ѡƵ����
		
			//GetPsfFromRe( gain_adj_st.ab_flag, gain_adj_st.ud_flag );
			GainAdjGetEUPow(gain_adj_st.ab_flag, gain_adj_st.ud_flag);
			gain_adj_st.step++;
			gain_adj_st.is_wait = 1;
			//printf("step%d\r\n",gain_adj_st.step);
			if(gain_adj_st.step < 125)
				gain_adj_st.adj_st= GAIN_ADJ_ST_SET_AUEU_FRE;
			else
				gain_adj_st.adj_st= GAIN_ADJ_ST_DONE;

			
			//gain_adj_st.is_wait = 0;//������һ������
			break;

		case GAIN_ADJ_ST_DONE://У׼���
			// ������ɣ������ݷ��ظ�����
			//SendMsgPkt( gain_adj_st.dat_len, att_adj_buff );
			gain_adj_st.adj_st  =GAIN_ADJ_ST_DONE; 
			gain_adj_st.is_wait = 0;  
			// ���У׼��־λ
			sys_work_info &= (~SYSTEM_FLAG_GAIN_ADJ);
			break;
	}
}

/*************************************************************
Name:         GianAdjustStartAdj        
Description:  ���沨��У׼�����ʼУ׼
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
Description:  ���沨��У׼�������ѯУ׼״̬
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
Description:  ���沨��У׼�������ȡУ׼����
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
Description:  ���沨��У׼���������У׼ģʽ
Input:        void
Output:       void      
Return:       void          
**************************************************************/ 
UINT16 GianAdjustEnterAdjMode(UINT16 len, UCHAR8 * p_msg_dat, UCHAR8 * p_tx_buff )
{
	UINT16 msg_tx_len = 0;

	gain_adj_st.ab_flag = p_msg_dat[0];//ABCD��
	gain_adj_st.ud_flag= p_msg_dat[1];//������

	
	gain_adj_st.adj_st = GAIN_ADJ_ST_SET_AUEU_ADJ_MODE;
	gain_adj_st.is_wait = 0;
	gain_adj_st.dat_len = 0;
	sys_work_info |= SYSTEM_FLAG_GAIN_ADJ;

	return msg_tx_len;
	
}
/*************************************************************
Name:         MoveCenterFre        
Description:  ���沨��У׼��ȡEU����
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


	//AU��RU�Ľ���һ��������һ��������
	//���ղ��� �����������ֻ����11λ16����������D10-D8д��0X232�ĵ�3bit��D7-D0д��0X231��С�����֡�2^23�����23λ16����������D22-D16д��0X235�ĵ�7bit��D15-D8д��0X234��D7-D0д��0X233
	fre = (center_fre_d - 15.5)/constant;
	val_int16 = (UINT16)fre;//ȡ��
	val_mod = fre - (float)val_int16;//ȡ��
	val_int32 = (UINT32) (val_mod*8388608);	

	ReadWriteTF(TF_A,1,0x005, val_reg5);

	
	ReadWriteTF(TF_A,1,0x231,(UCHAR8)((val_int16&0x00ff)>>0));
	ReadWriteTF(TF_A,1,0x232,(UCHAR8)((val_int16&0x0300)>>8));

	ReadWriteTF(TF_A,1,0x233,(UCHAR8)((val_int32&0x0000ff)>>0));
	ReadWriteTF(TF_A,1,0x234,(UCHAR8)((val_int32&0x00ff00)>>8));
	ReadWriteTF(TF_A,1,0x235,(UCHAR8)((val_int32&0x7f0000)>>16));

	//��дһ����������Ч
	ReadWriteTF(TF_A,1,0x231,(UCHAR8)((val_int16&0x00ff)>>0));


	
	//���Ͳ��� �����������ֻ����11λ16����������D10-D8д��0X272�ĵ�3bit��D7-D0д��0X271��С�����֡�2^23�����23λ16����������D22-D16д��0X275�ĵ�7bit��D15-D8д��0X274��D7-D0д��0X273
	fre = (center_fre_u - 15.5)/constant;
	val_int16 = (UINT16)fre;//ȡ��
	val_mod = fre - (float)val_int16;//ȡ��
	val_int32 = (UINT32) (val_mod*8388608);	


	ReadWriteTF(TF_A,1,0x005, val_reg5);

	ReadWriteTF(TF_A,1,0x271,(UCHAR8)((val_int16&0x00ff)>>0));
	ReadWriteTF(TF_A,1,0x272,(UCHAR8)((val_int16&0x0300)>>8));

	ReadWriteTF(TF_A,1,0x273,(UCHAR8)((val_int32&0x0000ff)>>0));
	ReadWriteTF(TF_A,1,0x274,(UCHAR8)((val_int32&0x00ff00)>>8));
	ReadWriteTF(TF_A,1,0x275,(UCHAR8)((val_int32&0x7f0000)>>16));

	//��дһ����������Ч
	ReadWriteTF(TF_A,1,0x271,(UCHAR8)((val_int16&0x00ff)>>0));

}




/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :rec_app.c
* Description :ϵͳ����������غ���
* Version     :v0.1
* Author      :RJ
* Date        :2010-03-10
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*RJ		2010-03-10		v0.1			��ʼ�汾
**************************************************************/
#include "Header.h"

extern _T_PARAM_1B sys_param_1b[];
extern _T_PARAM_2B sys_param_2b[];
extern _T_PARAM_4B sys_param_4b[];
extern _T_MODULE_CFG mod_cfg_a;
extern _T_MODULE_CFG mod_cfg_b;
extern UINT32 fpga_load_status;
extern _T_BIG_PKT_BUFF msg_big_buff[MSG_BIG_PKT_COUNT];
extern UINT32 module_param_chg_flag;		//ϵͳ���������޸ı�־
extern FLOAT32 fpga_dgcic_b;
extern UCHAR8 traffic_start ;//��ʼ������ͳ��

_T_VALID_FP_TOPO valid_fp_topo[FP_MAX];
_T_RE_INFO tmp_re_inf[FP_MAX][RE_MAX];		// RE��Ϣ����ʱ����
_T_FP_INFO fp_inf[FP_MAX];		// ���������Ϣ
_T_TOPO_ALARM_INFO topo_alarm[FP_MAX][RE_MAX] = {0};

UINT16 fp_enable = 0;			// ��ڵ�ʹ��״̬: 1-ʹ��
UINT16 total_re_count = 0;		// �������ܵ�RE����
UCHAR8 pre_re_count[FP_MAX];	// ǰһ�εĹ��RE����
UINT16 total_ree_count = 0;		// �������ܵ�RE����
UCHAR8 pre_ree_count[FP_MAX];	// ǰһ�εĹ��RE����
_T_TOPO_STATUS topo_st;			// ���˹���״̬

UCHAR8 gsm_type_a = G2_TYPE_UNICOM;	// A��gsmģʽ,Ĭ��Ϊ��ͨƵ��
UCHAR8 gsm_type_b = G2_TYPE_UNICOM;	// B��gsmģʽ,Ĭ��Ϊ��ͨƵ��

UINT32 bit_err_cnt=0;
UINT32 topo_chg_cnt = 0;
UINT32 fpga_rx_pkt_cnt = 0;
UINT32 topo_ok_count = 0;
UINT32 topo_err_count = 0;

UCHAR8 ucPllStatus =0;
UCHAR8 benzhen2340 = 0;

_T_NOISE_TEST_STATUS noise_test_st = 0;
//����REƽ�������õ�����,=10log(1~64)
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

// td_scdma����ͨ���ţ���1ͨ��Ϊ�������õ�Ƶ�㣬��ʼֵΪ10087��������ǰ9��Ϊ���ƵĹ̶�Ƶ�㣬��9��Ϊ��Ϊ�Ĺ̶�Ƶ��:10054,10062,10070,10079,10087,10095,10104,10112,10120��10055,10063,10071,10080,10088,10096,10104,10112,10120,
UINT16 tds_dl_channel[19] = {10087,10054,10062,10070,10079,10087,10095,10104,10112,10120,10055,10063,10071,10080,10088,10096};
// �¶����油����
// A�������¶����油����        //                  -20                         -10                     0
const UINT16 temp_cmp_tbl_adl[13] = {(UINT16)((INT16)(2.2*1000)),(UINT16)((INT16)(1.6*1000)),(UINT16)((INT16)(1.2*1000)),
								//					10,						    20,  					30 ,				   					
								(UINT16)((INT16)(0.9*1000)),(UINT16)((INT16)(0.6*1000)),(UINT16)((INT16)(0.2*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.4*1000)),(UINT16)((INT16)(-0.8*1000)),
								//                  70, 				        80, 			
								(UINT16)((INT16)(-0.8*1000)),(UINT16)((INT16)(-1.5*1000)), 0, 0};	
// A�������¶����油����        //                   -20                     1-0                          0
const UINT16 temp_cmp_tbl_aul[13] = {(UINT16)((INT16)(1.6*1000)),(UINT16)((INT16)(1.2*1000)),(UINT16)((INT16)(0.87*1000)),
								//					10,						    20,  						      30 ,				   					
								(UINT16)((INT16)(0.9*1000)),(UINT16)((INT16)(0.2*1000)),(UINT16)((INT16)(0*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(0.2*1000)),(UINT16)((INT16)(0.1*1000)),
								//                  70, 				        80, 			
								(UINT16)((INT16)(-0.2*1000)),(UINT16)((INT16)(-0.9*1000)), 0, 0};		

// B�������¶����油����        //                  -20                          -10                   0
const UINT16 temp_cmp_tbl_bdl[13] = {(UINT16)((INT16)(2.2*1000)),(UINT16)((INT16)(1.9*1000)),(UINT16)((INT16)(1.5*1000)),
								//					10,						      20,  						      30 ,				   					
								(UINT16)((INT16)(1.1*1000)),(UINT16)((INT16)(0.7*1000)),(UINT16)((INT16)(0.4*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.5*1000)),(UINT16)((INT16)(-0.8*1000)),
								//                70, 				            80, 			
								(UINT16)((INT16)(-1.2*1000)),(UINT16)((INT16)(-1.7*1000)), 0, 0};	
// B�������¶����油����       //                   -20                         -10                        0
const UINT16 temp_cmp_tbl_bul[13] = {(UINT16)((INT16)(1.81*1000)),(UINT16)((INT16)(1.31*1000)),(UINT16)((INT16)(1.17*1000)),
								//					10,						     20,  						      30 ,				   					
								(UINT16)((INT16)(0.61*1000)),(UINT16)((INT16)(0.71*1000)),(UINT16)((INT16)(0.11*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.29*1000)),(UINT16)((INT16)(-0.63*1000)),
								//                  70, 				        80, 			
								(UINT16)((INT16)(-0.9*1000)),(UINT16)((INT16)(-1.69*1000)), 0, 0};		

// C�������¶����油����      //                   -20                        -10                        0
const UINT16 temp_cmp_tbl_cdl[13] = {(UINT16)((INT16)(2.3*1000)),(UINT16)((INT16)(2.2*1000)),(UINT16)((INT16)(1.7*1000)),
								//					10,						   20,  						      30 ,				   					
								(UINT16)((INT16)(0.6*1000)),(UINT16)((INT16)(0.8*1000)),(UINT16)((INT16)(0.32*1000)),
								//					40,						50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-0.8*1000)),(UINT16)((INT16)(-1.3*1000)),
								//                  70, 				      80, 			
								(UINT16)((INT16)(-1.4*1000)),(UINT16)((INT16)(-2.2*1000)), 0, 0};	
// C�������¶����油����      //                   -20                         -10                     0
const UINT16 temp_cmp_tbl_cul[13] = {(UINT16)((INT16)(1.9*1000)),(UINT16)((INT16)(1.8*1000)),(UINT16)((INT16)(1.44*1000)),
								//					10,						      20,  						      30 ,				   					
								(UINT16)((INT16)(1.09*1000)),(UINT16)((INT16)(0.3*1000)),(UINT16)((INT16)(0*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(0.1*1000)),(UINT16)((INT16)(-0.4*1000)),
								//                  70, 				        80, 			
								(UINT16)((INT16)(-0.6*1000)),(UINT16)((INT16)(-1.4*1000)), 0, 0};		
// D�������¶����油����         //                  -20                        -10                       0
UINT16 temp_cmp_tbl_ddl[13] = {(UINT16)((INT16)(2.5*1000)),(UINT16)((INT16)(2.3*1000)),(UINT16)((INT16)(1.9*1000)),
								//					10,						      20,  						      30 ,				   					
								(UINT16)((INT16)(1.29*1000)),(UINT16)((INT16)(0.9*1000)),(UINT16)((INT16)(0.2*1000)),
								//					40,							50,							60, 	
								(UINT16)((INT16)(0*1000)),(UINT16)((INT16)(-1.2*1000)),(UINT16)((INT16)(-1.1*1000)),
								//        			70, 				         80, 			
								(UINT16)((INT16)(-1.5*1000)),(UINT16)((INT16)(-2*1000)), 0, 0};	
// D�������¶����油����       //                  -20                          -10                      0
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
	
	fp_enable = 0xFF;		// ʹ�����й�� 1ʹ�ܣ�0ʧ��

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
		
		//��ջ����� 
		ClearTmpReInfo(i);
	}

	sys_param_1b[MADD_DELAY_MODE].val=1;
	sys_param_1b[MADD_DELAY_MODE_A].val=1;
	sys_param_1b[MADD_DELAY_MODE_B].val=1;
	sys_param_1b[MADD_DELAY_MODE_C].val=1;	
	sys_param_1b[MADD_DELAY_MODE_D].val=1;
	
	if ( FPGA_LDST_OK != fpga_load_status )
	{
		// FPGA���ϣ�����
		return;
	}

	sys_work_info = 0;

#ifdef FUNC_TD_AUTO_SEARCH_FP	// TD�Զ�Ƶ������
	// ��ʼ��������ʱʱ�䣬MCU���߼�д�����ַ211�����ÿ�д����
	//FpgaWriteRegister( FPGA_WO_REG(211), 90 );
#endif
}

/*************************************************************
Name:SetValidTopo          
Description: ����������Ϣ
Input:
	msg_length: ��Ϣ���ĳ��ȣ�������CRC
	p_msg_dat: ָ������Ϣ���Ļ���ָ��
	p_tx_buff: ָ��Ӧ���������ָ��
Return: void
**************************************************************/
BOOL SetValidTopo( UCHAR8 * p_dat )
{
	
	UCHAR8 fp_count;
	UCHAR8 fp_set;
	UCHAR8 re_cnt;
	UCHAR8 i,j;

	WTD_CLR;
	fp_count = *p_dat++;

	if ( fp_count>FP_MAX ) 
	{
		return b_FALSE;
	}

	for ( i=0; i<fp_count; i++ )
	{
		fp_set = *p_dat++;
		valid_fp_topo[fp_set].fp_mode = *p_dat++;
		re_cnt = *p_dat++;
		if ( re_cnt > RE_MAX ) 
		{
			return b_FALSE;
		}
		
		valid_fp_topo[fp_set].re_count = re_cnt;
		for ( j=0; j<re_cnt; j++ )
		{
			valid_fp_topo[fp_set].re_inf[j].mode = *p_dat++; 
			valid_fp_topo[fp_set].re_inf[j].id = *p_dat++; 
		}

		msg_big_buff[i].owner = 0;
	}

	SaveValidTopo();
	
	return b_TRUE;

	
}

/*************************************************************
Name:             GetNewTopo          
Description:      ���8����ڵ�״̬:�Ƿ��й�ģ�����
                                    �Ƿ�ù������
                                    ͳ�Ƹù���µ�RE��Ŀ
                                    �Ƿ��жԶ˿ڣ��Լ��Զ˿ڵ�ID
               
                  ��TaskManageTopo�е��� 
Input: void
Return: void
**************************************************************/
void GetNewTopo()
{
	UCHAR8 i,j,k;
	UINT16 tmp;

	// D7-0��1/0----���0~7�Ĺ�ģ��û�в���/����
	tmp = FpgaReadRegister(FPGA_REG_SFP_CONNECT);
	//printf("fp_enable = %d\r\n",fp_enable);
	// ��ȡ���й�ڵ�����״̬
	for ( i=0; i<FP_MAX; i++ )
	{
	#ifdef  CLIENT_XINMIN	// ����Ҫ������������
		fp_inf[FP_MAX-i-1].re_cnt = 0;	// ���RE����
		fp_inf[FP_MAX-i-1].ops_info = 0;	// �������״̬
	#else
		fp_inf[i].re_cnt = 0;	// ���RE����
		fp_inf[i].ops_info = 0;	// �������״̬
		fp_inf[i].ree_cnt=0;
		// �жϹ�ģ���Ƿ����
	#endif
	
		if ( 0== (tmp & (0x01<<i)) )
		{
			#ifdef CLIENT_XINMIN	// ����Ҫ������������
				fp_inf[FP_MAX-i-1].sfp_attach = 1;
			#else
				fp_inf[i].sfp_attach = 1;
         		   #endif 
			
		}
		else
		{
			#ifdef CLIENT_XINMIN	// ����Ҫ������������
				fp_inf[FP_MAX-i-1].sfp_attach = 0;
			#else
				fp_inf[i].sfp_attach = 0;
            #endif
		}
		
		// ������Ƿ�ʹ��
		if ( 0 == fp_enable&(0x01<<i) )
		{
			continue;
		}
		
		// ��ȡ�����Ϣ
		#ifdef  CLIENT_XINMIN	// ����Ҫ������������
			if ( b_FALSE==FpgaGetTopoStaus( i, &fp_inf[FP_MAX-i-1] ) )
			{
				fp_inf[FP_MAX-i-1].re_cnt = 0;
				fp_inf[i].ree_cnt=0;
			}  
		#else
			if ( b_FALSE==FpgaGetTopoStaus( i, &fp_inf[i] ) )
			{
				fp_inf[i].re_cnt = 0;
				fp_inf[i].ree_cnt=0;
			}
		#endif
			
			//printf("i222=%d,eu=%d, ru=%d\\r\n",i,fp_inf[i].re_cnt,fp_inf[i].ree_cnt);
			for(j=0;j<fp_inf[i].re_cnt;j++)
			{
				WTD_CLR;

				for(k=0;k<8;k++)
				{
					if(0!=((1<<k)&tmp_re_inf[i][j].ree_nt_stat))
					{
						fp_inf[i].ree_cnt++;
					}	
				}
				WTD_CLR;
				for(k=0;k<4;k++)
				{
					if(0!=((1<<k)&tmp_re_inf[i][j].ree_fp_stat))
					{
						fp_inf[i].ree_cnt++;
					}	
				}
	
			}
	}
	
}

/*************************************************************
Name:         CheckTopoChange          
Description:  �ж�������û�б仯��ͳ���ܵ�RE��

              ֻҪͳ�Ƶ��κ�һ����ڵ�RE����һ�ε�RE��������ȣ�����Ϊ �����Ѿ��ı�
              ���ͳ�����еĹ�ڵ�RE����

Input:        void
Return:       b_TRUE-���˸ı䣻 
              FALSE-����δ�ı� 
**************************************************************/
BOOL CheckTopoChange()
{
	UCHAR8 i,j;
	
	BOOL IsChange = b_FALSE;
	
	total_re_count = 0;
	total_ree_count = 0;
	
	for ( i=0; i<FP_MAX; i++ )
	{
		WTD_CLR;
		if (  ( fp_inf[i].re_cnt != pre_re_count[i] )||(pre_ree_count[i] != fp_inf[i].ree_cnt)  )		// ��ڵ�RE������ǰһ�εĲ�һ��
		{
			IsChange = b_TRUE; 
			//TRACE_INFO("pre_re_count[%d] =[%x], fp_inf[%d].re_cnt=[%x]\r\n",i,pre_re_count[i],i,fp_inf[i].re_cnt);
			//TRACE_INFO("pre_ree_count[%d] =[%x], fp_inf[%d].ree_cnt=[%x]\r\n",i,pre_ree_count[i],i,fp_inf[i].ree_cnt);

			pre_re_count[i] = fp_inf[i].re_cnt;
			pre_ree_count[i] = fp_inf[i].ree_cnt;
		}else
		{
			for(j=0;j<RE_MAX;j++)
			{
				if((tmp_re_inf[i][j].pre_ree_nt_stat!=tmp_re_inf[i][j].ree_nt_stat)||(tmp_re_inf[i][j].pre_ree_fp_stat!=tmp_re_inf[i][j].ree_fp_stat))
				{
					IsChange = b_TRUE; 
					tmp_re_inf[i][j].pre_ree_nt_stat=tmp_re_inf[i][j].ree_nt_stat;
					tmp_re_inf[i][j].pre_ree_fp_stat=tmp_re_inf[i][j].ree_fp_stat;
				}
			}
		}
		
		total_re_count += fp_inf[i].re_cnt;
		total_ree_count += fp_inf[i].ree_cnt;
	}

	return IsChange;
}

/*************************************************************
Name:CheckRingNetErr          
Description: ����Ƿ����Ͽ� 
Input: void
Return: void
**************************************************************/
void CheckRingNetErr()
{
	static UCHAR8 pre_ring_net_st=0;			// ����״̬����ʼΪ�ǻ���
	UINT32 i;
	UINT32 flag = 0;
	UCHAR8 alarm = 0;
	UINT32 ops_no;

	for ( i=0; i<FP_MAX; i++ )
	{
		// ��ʼ������״̬Ϊ�ǻ��� 
		flag = 1;

		// ���ñ������з���״̬Ϊ����
		fp_inf[i].tx_err = 0;
				
		// ����Ƿ��ǻ�������
		if ( OPS_RCV_FLAG==(fp_inf[i].ops_info & OPS_RCV_FLAG) )
		{	
			// ȡ�û����Զ˹�ں�(0��ʼ)
			ops_no = fp_inf[i].ops_info & OPS_NO_MASK;

			if ( ops_no!=i )	// �Զ˹�ں��뵱ǰ��ںŲ�������ͬ
			{
				// �Զ˹��Ҳ�յ���������֡����ȷ���ǻ���
				if (( ops_no<FP_MAX )&&( OPS_RCV_FLAG==(fp_inf[ops_no].ops_info & OPS_RCV_FLAG) ))
				{		
					// ����
					flag = 0;
				}
				else
				{	 
					// ĩ��REû���յ����˵��������ݣ��жϱ������з��͹���
					fp_inf[i].tx_err = 1;
				}  
			}
		}

		// �����ģ��δ���ӣ������ǰһ�εĻ�����־
		if ( fp_inf[i].sfp_attach==0 )
		{
			pre_ring_net_st &= (~(1<<i));
			continue;
		}

        /*�ϴ�Ϊ�ǻ���*/
		if ( 0==(pre_ring_net_st & (1<<i)) )
		{
			// ��⵽��ǰΪ����
			if ( flag==0 )
			{ 
				
				pre_ring_net_st |= (1<<i);	// �û�����־
			}
		}
		else /*�ϴ�Ϊ����*/
		{
			// ��⵽��ǰ��Ϊ����
			if( flag == 1 )
			{
				alarm = 1;	// ����״̬�澯
				break;
			}
			else
			{
				// ��⵽��ǰΪ����
			}
		}
	}

	sys_param_1b[MADD_TOPO_CHG_ALM].val = alarm;	// ����״̬�澯
	
}

void RefreshParam()
{
	UINT32 tmp = 0;
	INT32 i;
	
	if ( 0 == topo_st.IsTopoUnsteady )
	{
		// ���½ڵ�������������
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
Description:  ����RE��Ϣ
              ����ѭ���е��ã�1���Ӿʹ���һ��  



              
Input:        void
Return:       void
**************************************************************/
void UpdateReInfo()
{  
	UCHAR8 fp_no, re_no; 

	WTD_CLR;
	
    //TRACE_INFO("UpdateReInfo\r\n");
	
	// ���˲��ȶ� 
	if ( 1 == topo_st.IsTopoUnsteady )
	{
		topo_st.IsGetReInfOk = 0;
		topo_st.IsSendReqPkt = 0;
		topo_st.ReAckTimeOut = 0;
		//TRACE_INFO("back 6\r\n");
		return; 
	}          

    //û��RE��Ŀ 
	if ( 0 == total_re_count )
	{
		//TRACE_INFO("back 5\r\n");
		return; 
	}

	// ��ʾ��û����RE��Ϣ����
	if ( 0 == topo_st.IsSendReqPkt )   //ÿ5���ӷ���һ�β�RE״̬�Ĺ㲥��Ϣ
	{
		
		GetReInfo();                    // �㲥��ȡRE��Ϣ���� ,����ÿ��RE��ID +״̬(����  + ֡ģʽ)
		topo_st.IsSendReqPkt = 1;		// ��ʾ�Ѿ�����RE��Ϣ����
		topo_st.IsGetReInfOk = 0;		// ���RE��Ϣ������ɱ�־
		topo_st.ReAckTimeOut = 0;		// ��λӦ��ʱ��ʱ��
		//TRACE_INFO("back 4\r\n");
		return; 
	}  

	// REû�з�������״̬
	if ( 0 == topo_st.IsGetReInfOk )
	{
		topo_st.ReAckTimeOut++;
		
		if ( topo_st.ReAckTimeOut > 5 )		// ��ȡRE��Ϣ��ʱ(5s)
		{
			topo_st.IsSendReqPkt = 0;		//5��֮�ڻ�û�յ�����RE����Ϣ�������¹㲥
			//TRACE_INFO("back 3\r\n");
			return;
		}

		// ��������Ƿ����е�RE������������״̬
		for( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			if ( fp_inf[fp_no].re_cnt > RE_MAX )
			{
				//TRACE_INFO("back 2\r\n");
				return;
			} 
			
			for ( re_no=0; re_no<fp_inf[fp_no].re_cnt; re_no++ )
			{
				if ( 0 == tmp_re_inf[fp_no][re_no].flag )	// ��REû�з�����Ϣ
				{
					//TRACE_INFO("back 1\r\n");  
					//TRACE_INFO("%d,%d\r\n",fp_no,re_no);
					return;
				} 
			}
		}

		topo_st.IsGetReInfOk = 1;		// ���е�RE��Ϣ������ɱ�־
		topo_st.UpdateCycDelay = 0;  	// ����ȴ���ʱ��
		
		// ����RE��Ϣ�����˽ṹ�У�����ջ���
		for( fp_no=0; fp_no<FP_MAX; fp_no++ )
		{
			for ( re_no=0; re_no<fp_inf[fp_no].re_cnt; re_no++ )
			{
				fp_inf[fp_no].re_info[re_no].re_status = tmp_re_inf[fp_no][re_no].status;
				fp_inf[fp_no].re_info[re_no].re_id = tmp_re_inf[fp_no][re_no].id;
			}
			
			ClearTmpReInfo( fp_no );
		}

		//���RE��id
		//CheckReID();
		
	}
	else  //�Ѿ�����������RE����Ϣ
	{
		topo_st.UpdateCycDelay++;
//		TRACE_INFO_WP("Wait..%d\r\n", topo_st.UpdateCycDelay);
		if ( topo_st.UpdateCycDelay>5 )		// ��һ�����ڼ��һ��(5s)
		{
			topo_st.IsSendReqPkt = 0;	// ���㡾�ѷ���RE״̬�������״̬������Ҫ�ط������
			topo_st.IsGetReInfOk = 0;	// ���RE��Ϣ������ɱ�־
		}
	}
	
}
/*************************************************************
Name:RecBoadcastGetTopo         
Description: �㲥��ȡRE��������Ϣ,���±�־��Ϣ
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
Description: �������,���±�־��Ϣ
             �˺�������ѭ����ʵʱ����
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
		// FPGA���ϣ�����
		topo_st.IsTopoUnsteady = 1;
		return; 
	} 


    /*����8����ڵ�����״̬*/
	GetNewTopo();

    /*����Ƿ����Ͽ� */
	//CheckRingNetErr();

    /*����������ޱ仯����ͳ����RE��Ŀ*/
	if ( b_TRUE == CheckTopoChange() )		// ���˱仯
	{
		TRACE_INFO("2013-----------CheckTopoChange\r\n");
		topo_stable_count = 0;
		sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
		sys_work_info |= SYSTEM_FLAG_SET_RE_SYS_CFG;
		sys_work_info |= SYSTEM_FLAG_SET_RE_TDSLOT;
		sys_work_info |= SYSTEM_FLAG_SET_RE_SFC;

		//if(topo_ok_count > 86400)//����ȶ���24Сʱ�򣬷������ȶ� ��ΪTOPO�澯
		//if(topo_ok_count > 300)//5���Ӹ澯���԰汾
		if(topo_ok_count > 7200)  //2Сʱ�汾
			topo_err_count ++;
	} 
	else
	{  
		/*�����ȶ�������1*/
		topo_stable_count++;
		topo_ok_count++;
	}
	
	// ��鵽8�����ϣ���֤�������ȶ����޸ı�
	if ( topo_stable_count < 8 )		
	{ 
		if ( topo_st.IsTopoUnsteady==0 )
		{   
			/*���˱仯������*/
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
Description: ���RE��Ϣ����ʱ����
Input: fp:��ں�
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
Description: �㲥���ͻ�ȡRE״̬�����ݰ�
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

	msg[tx_len++] = 0xA7;		// ��չ��ʶ1
	msg[tx_len++] = 0xE5;		// ��չ��ʶ2
	msg[tx_len++] = 0x0;		// ģʽ�汾0

	tmp = mod_cfg_a.ul_pcf.reg_n;		// A������4153_N
	msg[tx_len++] = (UCHAR8)(tmp&0xFF);	
	msg[tx_len++] = (UCHAR8)(tmp>>8);	
	msg[tx_len++] = (UCHAR8)(tmp>>16);	
	msg[tx_len++] = (UCHAR8)(tmp>>24);	
	
	tmp = mod_cfg_a.ul_pcf.reg_r;		// A������4153_R
	msg[tx_len++] = (UCHAR8)(tmp&0xFF);	
	msg[tx_len++] = (UCHAR8)(tmp>>8);	
	msg[tx_len++] = (UCHAR8)(tmp>>16);	
	msg[tx_len++] = (UCHAR8)(tmp>>24);	

	tmp = mod_cfg_a.dl_pcf.reg_n;		// A������4153_N
	msg[tx_len++] = (UCHAR8)(tmp&0xFF);	
	msg[tx_len++] = (UCHAR8)(tmp>>8);	
	msg[tx_len++] = (UCHAR8)(tmp>>16);	
	msg[tx_len++] = (UCHAR8)(tmp>>24);	
	
	tmp = mod_cfg_a.dl_pcf.reg_r;		// A������4153_R
	msg[tx_len++] = (UCHAR8)(tmp&0xFF);	
	msg[tx_len++] = (UCHAR8)(tmp>>8);	
	msg[tx_len++] = (UCHAR8)(tmp>>16);	
	msg[tx_len++] = (UCHAR8)(tmp>>24);	

	tmp = mod_cfg_b.ul_pcf.reg_n;		// B������4153_N
	msg[tx_len++] = (UCHAR8)(tmp&0xFF);	
	msg[tx_len++] = (UCHAR8)(tmp>>8);	
	msg[tx_len++] = (UCHAR8)(tmp>>16);	
	msg[tx_len++] = (UCHAR8)(tmp>>24);	
	
	tmp = mod_cfg_b.ul_pcf.reg_r;		// B������4153_R
	msg[tx_len++] = (UCHAR8)(tmp&0xFF);	
	msg[tx_len++] = (UCHAR8)(tmp>>8);	
	msg[tx_len++] = (UCHAR8)(tmp>>16);	
	msg[tx_len++] = (UCHAR8)(tmp>>24);	

	tmp = mod_cfg_b.dl_pcf.reg_n;		// B������4153_N
	msg[tx_len++] = (UCHAR8)(tmp&0xFF);	
	msg[tx_len++] = (UCHAR8)(tmp>>8);	
	msg[tx_len++] = (UCHAR8)(tmp>>16);	
	msg[tx_len++] = (UCHAR8)(tmp>>24);	
	
	tmp = mod_cfg_b.dl_pcf.reg_r;		// B������4153_R
	msg[tx_len++] = (UCHAR8)(tmp&0xFF);	
	msg[tx_len++] = (UCHAR8)(tmp>>8);	
	msg[tx_len++] = (UCHAR8)(tmp>>16);	
	msg[tx_len++] = (UCHAR8)(tmp>>24);	

	SendMsgPkt(tx_len, msg);
	
}

/*************************************************************
Name:AssignID          
Description: ����ID
Input:
	fp: ��ں�
	re: REλ�����
	p_id: ����IDֵ�Ļ���ָ��
Return: 
	b_TRUE: �ɹ�����IDֵ
	b_FALSE: ����IDʧ��
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
Description: ���RE��ID�Ƿ����ظ�
Input: void
Return: 
	b_TRUE:  �ɹ�����IDֵ
	b_FALSE: ����IDʧ��
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
		// ������Ƿ�ʹ��
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
					// �������ݰ�����RE��ID
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
							// �������ݰ�����RE��ID
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

	// �����־
	sys_work_info &= (~SYSTEM_FLAG_CHECK_ID);

}

// ��ȡWLAN�ڵ�״̬�����µ��ӿڲ�������
void GetWlanPortStatus()
{
	UINT16 port;
	UINT16 reg;
	
	for ( port=0; port<WLAN_PORT_COUNT; port++)
	{
		sys_param_1b[MADD_WLAN_CONN_ST1+port].val = 0;		// ����״̬Ϊ����
		sys_param_1b[MADD_WLAN_SPEED1+port].val = 0;		// �����ٶ�Ϊ10M

		if ( 0==fpga_cfg.wlan_en )		// 122.88Mʱ��,��WLANģʽ������ȡWLAN����Ϣ
		{
			continue;
		}

		if ( 0==fp_inf[port+WLAN_PORT_OFFSET].sfp_attach)		// ����ģ��δ����
		{
			continue;	// ������״̬��Ϣ
		}
		

		FPGA_ENABLE_WRITE;
		FPGA_SET_OPT(port+WLAN_PORT_OFFSET);		// ���ù��
		FPGA_DISABLE_WRITE;

		reg = FpgaReadRegister(FPGA_WLAN_PORT_INFO);	// ��ȡ����
		if ( 0 == (reg&BM_WLAN_LINK_ST) )	// ���ӶϿ�
		{
			sys_param_1b[MADD_WLAN_CONN_ST1+port].val = 1;
		}
		switch (reg&BM_WLAN_SPEED)		// �ٶ�����
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
Description: ��ȡ���Ĺ����ʱʱ�䣬��д�������ʱ�Ĵ���
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
		sys_param_2b[MADD_MAX_T14].val = (UINT16)(tmp/75.0); //��������ʱ
		//TRACE_INFO("sys_param_2b[MADD_MAX_T14].val=[%x],tmp=[%x]\r\n",sys_param_2b[MADD_MAX_T14].val,tmp);
		tmp = ((UINT32)FpgaReadRegister(FPGA_REG_OPT_MAX_DELAY_H)<<8)| ((FpgaReadRegister(FPGA_REG_OPT_MAX_DELAY_L)>>8)&0xff);
		sys_param_2b[MADD_MAX_T14_A].val = (UINT16)(tmp/75.0/2)+RF_DELAY_TIME_A*100; //��������ʱ
		sys_param_2b[MADD_MAX_T14_B].val = (UINT16)(tmp/75.0/2)+RF_DELAY_TIME_B*100; //��������ʱ
		sys_param_2b[MADD_MAX_T14_C].val = (UINT16)(tmp/75.0/2)+RF_DELAY_TIME_C*100; //��������ʱ
		sys_param_2b[MADD_MAX_T14_D].val = (UINT16)(tmp/75.0/2)+RF_DELAY_TIME_D*100; //��������ʱ

	}
#if 0
	if ( FPGA_LDST_OK == fpga_load_status )
	{
		FPGA_ENABLE_WRITE;
		
		for ( i=0; i<FP_MAX; i++ )
		{
			opt_t14 = 0;

            #ifdef CLIENT_XINMIN
			  FPGA_SET_OPT(7-i); //ѡ�й��  
			#else
			   FPGA_SET_OPT(i); //ѡ�й��     
            #endif 

			 
			// ���ʹ������������ȡ��ʱ,���һ�����й�ڵ������ʱ ʱ�� 
			if ((0!=sys_param_1b[MADD_FP1_EN+i].val )&&( FRAME_LOCK==fp_inf[i].frm_lock))
			{
				tmp = FpgaReadRegister(FPGA_REG_OPT_DELAY_H);
				opt_t14 = (UINT32)tmp<<8;
				tmp = FpgaReadRegister(FPGA_REG_OPT_DELAY_L);
				opt_t14 |= ( (tmp>>8) & 0x00FF );
			}

			if ( max_t14<opt_t14 )
			{
				max_t14 = opt_t14;
			} 
		}

		// ��2,��T12
		max_t14 >>= 1;

		sys_param_2b[MADD_MAX_T14].val = (INT32)(max_t14*8.138)/10; //��������ʱ
//		TRACE_INFO("sys_param_2b[MADD_MAX_T14].val=%04x,max_t14=%d\r\n",sys_param_2b[MADD_MAX_T14].val,max_t14);
		
		tmp = (UINT16)(max_t14>>8);
		FpgaWriteRegister(FPGA_REG_DELAY_SPEC_H, tmp);
		tmp = (UINT16)(max_t14&0xFF)<<8;
		FpgaWriteRegister(FPGA_REG_DELAY_SPEC_L, tmp);
		FPGA_DISABLE_WRITE; 
	}
#endif
}

/*************************************************************
Name:GetPeripheralStatus          
Description: ���µ���״̬
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
 
	/*��ȡ���Ĺ����ʱʱ�䣬��д�������ʱ�Ĵ���*/
	//GetNetworkDelay();

	// PLL״̬ 
	// ���9517ʱ��״̬ 
	sys_param_1b[MADD_CLK_PLL_ST].val = ( 0==GetAD9524LD()? 1 : 0 );
	//sys_param_1b[MADD_CLK_REF_ST].val = ( 0==GetAD9524Refmon() ? 1 : 0 );
//	sys_param_1b[MADD_CLK_].val = ( 0==GetAD9524Status() ? 0 : 1 );

	// DA���໷
	//sys_param_1b[MADD_A_BB_PLL_LOCK].val = (0==GetDA9122LockA()) ? 1 : 0;
	//sys_param_1b[MADD_B_BB_PLL_LOCK].val = (0==GetDA9122LockB()) ? 1 : 0;
	
	// ������ƫ�߱���
	//sys_param_1b[MADD_BER_ALARM].val = 0;

	if ( FPGA_LDST_OK == fpga_load_status )
	{
		// ��ȡʱ��״̬
		tmp = FpgaReadRegister(FPGA_REG_GCLK_ST);
		// FPGA���໷
		sys_param_1b[MADD_FPGA_CLK_ST].val = ( 0==(tmp&BM_FPGA_PLL_LOCK) ? 1 : 0 );

		// SERDES״̬
		for ( i=0; i<FP_MAX; i++ )
		{
			// ����״̬Ϊ����
			sys_param_1b[MADD_FP1_LOS+i].val = 0;//0: ������1: �澯
			sys_param_1b[MADD_FP1_LOF+i].val = 0;
			sys_param_1b[MADD_SERDES1_PLL_ST+i].val = 0;

			// ��ģ����λ״̬
			sys_param_1b[MADD_FP1_ON_POS+i].val = ( fp_inf[i].sfp_attach==1 ) ? 0 : 1;

			if ( 1==fpga_cfg.wlan_en )		// WLANģʽ������ȡWLAN�����ڹ�ڵ�����״̬��Ϣ,ֻ��ȡ��ͨ�����Ϣ
			{
				if ( i>=WLAN_PORT_OFFSET )
				{
					continue;
				}
			}

			if ( fp_inf[i].sfp_attach == 1 )	// ��ģ��������
			{
//				TRACE_INFO("i[%02x]20130509++++++++r\n",i);
				// ��ģ��״̬
				sys_param_1b[MADD_FP1_LOS+i].val = (( FRAME_LOCK==fp_inf[i].frm_lock ) ? 0 : 1);//(( b_TRUE==FpgaGetSfpStatus(i) ) ? 0 : 1);	//(( FRAME_LOCK==fp_inf[i].frm_lock ) ? 0 : 1);
				// ��·ͬ��״̬
				sys_param_1b[MADD_FP1_LOF+i].val = ((FRAME_LOCK==fp_inf[i].frm_lock)&&(0==fp_inf[i].tx_err) ? 0 : 1);
				// ����״̬
				sys_param_1b[MADD_SERDES1_PLL_ST+i].val = ((FRAME_LOCK==fp_inf[i].frm_lock)&&(0==fp_inf[i].tx_err) ? 0 : 1);
			}
#if 0
			else 
	//20130517		
			{//20130510
				// ��ģ��״̬
				sys_param_1b[MADD_FP1_LOS+i].val = 1;	//(( FRAME_LOCK==fp_inf[i].frm_lock ) ? 0 : 1);
				// ��·ͬ��״̬
				sys_param_1b[MADD_FP1_LOF+i].val = 1;
				// ����״̬
				sys_param_1b[MADD_SERDES1_PLL_ST+i].val = 1;
			}
#endif 
		}

		// ��Ƶ��(����)����״̬, 1-ʧ��
/*		sys_param_1b[MADD_A_TX_PLL_ST].val = ((ucPllStatus&A_DN_PLL_LCK)?0:1);
		
		if ( fpga_cfg.a_net_type==NET_TYPE_CMMB )	// CMMB�����У���Ϊ����ǰ�˱�������
		{
			sys_param_1b[MADD_A_RX_PLL_ST].val = 0;
		} 
		else   
		{
			sys_param_1b[MADD_A_RX_PLL_ST].val = ((ucPllStatus&A_UP_PLL_LCK)?0:1);
		}  

	
		if ( fpga_cfg.b_net_type==NET_DIVE )
		{
			// �ּ�û������,��Ϊ����ǰ�˱�������
			sys_param_1b[MADD_B_TX_PLL_ST].val = 0;
		}
		else
		{ 
			sys_param_1b[MADD_B_TX_PLL_ST].val = ((ucPllStatus&B_DN_PLL_LCK)?0:1);
		} 
		
		if ( fpga_cfg.b_net_type==NET_TYPE_CMMB )	// CMMB�����У���Ϊ����ǰ�˱�������
		{
			sys_param_1b[MADD_B_RX_PLL_ST].val = 0;
		}
		else
		{ 
			sys_param_1b[MADD_B_RX_PLL_ST].val = ((ucPllStatus&B_UP_PLL_LCK)?0:1);
		} 
*/


#if	0
		// ֡��ʧ״̬,ֻҪ��һ����ڳ���LOF,����λ֡��ʧ״̬
		sys_param_1b[MADD_OPT_LOF].val = 0;
		 
		for ( i=0; i<FP_MAX; i++ )
		{
			if ( sys_param_1b[MADD_FP1_LOF+i].val == 1 )
			{
				sys_param_1b[MADD_OPT_LOF].val = 1;
				break;
			}
		}
		
		sys_param_4b[MADD_BIT_ERR_COUNT].val  = bit_err_cnt;
		sys_param_4b[MADD_TOPO_CHG_COUNT].val = topo_chg_cnt;
		sys_param_4b[MADD_FPGA_PKT_COUNT].val = fpga_rx_pkt_cnt;

		sys_param_4b[MADD_DEV_ADDR].val = 0x00000000;

		sys_param_1b[MADD_TD_SYNC_ST].val = ((((1<<5) & FpgaReadRegister(FPGA_REG_TD_SYNC_ST) )>>5 ) == 0) ? 1 : 0;	// TDͬ��״̬
		sys_param_1b[MADD_C_TD_SYNC_ST].val = ((((1<<2) & FpgaReadRegister(FPGA_REG_C_TD_SYNC_ST) )>>2 ) == 0) ? 1 : 0;	// TDͬ��״̬
		sys_param_1b[MADD_D_TD_SYNC_ST].val = ((((1<<2) & FpgaReadRegister(FPGA_REG_D_TD_SYNC_ST) )>>2 ) == 0) ? 1 : 0;	// TDͬ��״̬

//		TRACE_INFO("sys_param_1b[MADD_TD_SYNC_ST].val(%02x)(%04x)!!!!!!!!!!!!1\r\n",sys_param_1b[MADD_TD_SYNC_ST].val,FpgaReadRegister(FPGA_REG_TD_SYNC_ST));

//		TRACE_INFO("(INT16)sys_param_2b[MADD_TD_SLOT1_DPOW_OVER_THR].val(%d),sys_param_2b[MADD_TD_SLOT1_DPOW].val(%d)!!!!!!!!!!!!1\r\n",(INT16)sys_param_2b[MADD_TD_SLOT1_DPOW_OVER_THR].val,sys_param_2b[MADD_TD_SLOT1_DPOW].val);		
		sys_param_1b[MADD_TD_D_OVER_SLOT1_THR_ALARM].val =0;
		if((INT16)sys_param_2b[MADD_TD_SLOT1_DPOW_OVER_THR].val<(INT16)sys_param_2b[MADD_TD_SLOT1_DPOW].val)
		{
			sys_param_1b[MADD_TD_D_OVER_SLOT1_THR_ALARM].val =1;
		}
		sys_param_1b[MADD_TD_D_OWE_SLOT1_THR_ALARM].val =0;
		if((INT16)sys_param_2b[MADD_TD_SLOT1_DPOW_OWE_THR].val>(INT16)sys_param_2b[MADD_TD_SLOT1_DPOW].val)
		{
			sys_param_1b[MADD_TD_D_OWE_SLOT1_THR_ALARM].val =1;
		}
		if(1==topo_st.IsTopoUnsteady)
		{
			sys_param_1b[MADD_HOST_DEVICE_LINK_SINGNAL_ALARM].val =1;
		}
		
		sys_param_1b[MADD_LOW_POWER_ALARM].val =0;
		if( 0!=( sys_param_1b[MADD_LOW_POWER].val  ) )
		{
			sys_param_1b[MADD_LOW_POWER_ALARM].val  =1;
		}
		sys_param_1b[MADD_HOST_DEVICE_LINK_SINGNAL_ALARM].val=0;//ȥ��������·�澯����Ϊ���岻һ����
		if ( ( 1==sys_param_1b[MADD_OPT_LOF].val )||( 1==sys_param_1b[MADD_TD_SYNC_ST].val )||( 1==sys_param_1b[MADD_HOST_DEVICE_LINK_SINGNAL_ALARM].val ) )
		{
			sys_param_1b[MADD_DIGITAL_SINGNAL_ALARM].val = 1;			
		}
		
		sys_param_1b[MADD_A_INPUT_OVER_DPOW_THR_ALARM].val = 0;	
		sys_param_1b[MADD_A_INPUT_OWE_DPOW_THR_ALARM].val = 0;
		sys_param_1b[MADD_B_INPUT_OVER_DPOW_THR_ALARM].val = 0;	
		sys_param_1b[MADD_B_INPUT_OWE_DPOW_THR_ALARM].val = 0;	
		
//		TRACE_INFO("sys_param_2b[PARA_A_INPUT_TOTAL_DPOW_OVER_THR].val(%d),sys_param_2b[MADD_A_DL_TOTAL_POW].val(%d)!!!!!!!!!!!!1\r\n",(INT16)sys_param_2b[PARA_A_INPUT_TOTAL_DPOW_OVER_THR].val,(INT16)sys_param_2b[MADD_A_DL_TOTAL_POW].val);				
		if ( ( (INT16)sys_param_2b[MADD_A_INPUT_TOTAL_DPOW_OVER_THR].val< (INT16)sys_param_2b[MADD_A_DL_TOTAL_POW].val ) )
		{
			sys_param_1b[MADD_A_INPUT_OVER_DPOW_THR_ALARM].val = 1;			
		}
		
		if ( ( (INT16)sys_param_2b[MADD_A_INPUT_TOTAL_DPOW_OWE_THR].val> (INT16)sys_param_2b[MADD_A_DL_TOTAL_POW].val ) )
		{
			sys_param_1b[MADD_A_INPUT_OWE_DPOW_THR_ALARM].val = 1;			
		}
		
		if ( ( (INT16)sys_param_2b[MADD_B_INPUT_TOTAL_DPOW_OVER_THR].val< (INT16)sys_param_2b[MADD_B_DL_TOTAL_POW].val ) )
		{
			sys_param_1b[MADD_B_INPUT_OVER_DPOW_THR_ALARM].val = 1;			
		}
		
		if ( ( (INT16)sys_param_2b[MADD_B_INPUT_TOTAL_DPOW_OWE_THR].val> (INT16)sys_param_2b[MADD_B_DL_TOTAL_POW].val ) )
		{
			sys_param_1b[MADD_B_INPUT_OWE_DPOW_THR_ALARM].val = 1;			
		}
		
//		TRACE_INFO("sys_param_1b[MADD_PWR_9V0_VT].val(%d)!!!!!!!!!!!!1\r\n",sys_param_1b[MADD_PWR_9V0_VT].val);		
		sys_param_1b[MADD_BATTERY_BREAKDOWN_ALARM].val = 1;
		if( (sys_param_1b[MADD_PWR_9V0_VT].val<sys_param_1b[MADD_MONITOR_VOL_OVER_THR].val)&&(sys_param_1b[MADD_PWR_9V0_VT].val>sys_param_1b[MADD_MONITOR_VOL_OWE_THR].val))
		{
			sys_param_1b[MADD_BATTERY_BREAKDOWN_ALARM].val = 0;
		}

		//sys_param_1b[MADD_A_1197_LOCK_ST].val = (HMC_1197_LOCK_ST==(UCHAR8)ReadHmc1197(HMC_1197_REG_ADD) ? 0 : 1);

		sys_param_1b[MADD_A_INIT_DA_ST].val = (AD9363_INIT_DA_ST==(UCHAR8)ReadWriteTF(TF_A,0,AD9363_REG_R_INIT_DA_ST,0) ? 0 : 1);
		sys_param_1b[MADD_B_INIT_DA_ST].val = (AD9363_INIT_DA_ST==(UCHAR8)ReadWriteTF(TF_B,0,AD9363_REG_R_INIT_DA_ST,0) ? 0 : 1);
		sys_param_1b[MADD_C_INIT_DA_ST].val = (AD9363_INIT_DA_ST==(UCHAR8)ReadWriteTF(TF_C,0,AD9363_REG_R_INIT_DA_ST,0) ? 0 : 1);
		sys_param_1b[MADD_D_INIT_DA_ST].val = (AD9363_INIT_DA_ST==(UCHAR8)ReadWriteTF(TF_D,0,AD9363_REG_R_INIT_DA_ST,0) ? 0 : 1);

		sys_param_1b[MADD_A_BB_PLL_LOCK].val = (AD9363_BB_PLL_LOCK==(UCHAR8)ReadWriteTF(TF_A,0,AD9363_REG_R_BB_PLL_LOCK,0) ? 0 : 1);
		sys_param_1b[MADD_B_BB_PLL_LOCK].val = (AD9363_BB_PLL_LOCK==(UCHAR8)ReadWriteTF(TF_B,0,AD9363_REG_R_BB_PLL_LOCK,0) ? 0 : 1);
		sys_param_1b[MADD_C_BB_PLL_LOCK].val = (AD9363_BB_PLL_LOCK==(UCHAR8)ReadWriteTF(TF_C,0,AD9363_REG_R_BB_PLL_LOCK,0) ? 0 : 1);
		sys_param_1b[MADD_D_BB_PLL_LOCK].val = (AD9363_BB_PLL_LOCK==(UCHAR8)ReadWriteTF(TF_D,0,AD9363_REG_R_BB_PLL_LOCK,0) ? 0 : 1);

		sys_param_1b[MADD_A_RX_PLL_ST].val = (AD9363_RX_PLL_ST==(UCHAR8)ReadWriteTF(TF_A,0,AD9363_REG_R_RX_PLL_ST,0) ? 0 : 1);
		sys_param_1b[MADD_B_RX_PLL_ST].val = (AD9363_RX_PLL_ST==(UCHAR8)ReadWriteTF(TF_B,0,AD9363_REG_R_RX_PLL_ST,0) ? 0 : 1);
		sys_param_1b[MADD_C_RX_PLL_ST].val = (AD9363_RX_PLL_ST==(UCHAR8)ReadWriteTF(TF_C,0,AD9363_REG_R_RX_PLL_ST,0) ? 0 : 1);
		sys_param_1b[MADD_D_RX_PLL_ST].val = (AD9363_RX_PLL_ST==(UCHAR8)ReadWriteTF(TF_D,0,AD9363_REG_R_RX_PLL_ST,0) ? 0 : 1);
		
		sys_param_1b[MADD_A_TX_PLL_ST].val = (AD9363_TX_PLL_ST==(UCHAR8)ReadWriteTF(TF_A,0,AD9363_REG_R_TX_PLL_ST,0) ? 0 : 1);
		sys_param_1b[MADD_B_TX_PLL_ST].val = (AD9363_TX_PLL_ST==(UCHAR8)ReadWriteTF(TF_B,0,AD9363_REG_R_TX_PLL_ST,0) ? 0 : 1);
		sys_param_1b[MADD_C_TX_PLL_ST].val = (AD9363_TX_PLL_ST==(UCHAR8)ReadWriteTF(TF_C,0,AD9363_REG_R_TX_PLL_ST,0) ? 0 : 1);
		sys_param_1b[MADD_D_TX_PLL_ST].val = (AD9363_TX_PLL_ST==(UCHAR8)ReadWriteTF(TF_D,0,AD9363_REG_R_TX_PLL_ST,0) ? 0 : 1);

		sys_param_1b[MADD_A_Modulator_EN].val = (AD9363_A_Modulator_EN==(UCHAR8)ReadWriteTF(TF_A,0,AD9363_REG_R_Modulator_EN,0) ? 1 : 0);	//����AU   AD9363  0x57	 3C	
		sys_param_1b[MADD_B_Modulator_EN].val = (AD9363_B_Modulator_EN==(UCHAR8)ReadWriteTF(TF_B,0,AD9363_REG_R_Modulator_EN,0) ? 1 : 0);	//����AU   AD9363  0x57	 3C
		sys_param_1b[MADD_C_Modulator_EN].val = (((UCHAR8)ReadWriteTF(TF_C,0,AD9363_REG_R_Modulator_EN,0) & 0X02)? 0 : 1);	//����AU   AD9363  0x57[1]   0
		sys_param_1b[MADD_D_Modulator_EN].val = (((UCHAR8)ReadWriteTF(TF_D,0,AD9363_REG_R_Modulator_EN,0) & 0X01)? 0 : 1);	//����AU   AD9363  0x57[0] 0

		sys_param_1b[MADD_SLOT_TIME_DISTRI_B].val = (UCHAR8)FpgaReadRegister(FPGA_REG_R_SLOT_TIME_B);
		sys_param_1b[MADD_VERSION_FLAG].val = version_number;
#endif		
		
#if 0		
		sys_param_1b[MADD_BATTERY_BREAKDOWN_ALARM].val =0;
		if( 0!=( sys_param_1b[MADD_BATTERY_BREAKDOWN_ALARM].val  ) )
		{
			sys_param_1b[MADD_LOW_POWER_ALARM].val  =1;
		}
#endif

#if	1
		//GetWlanPortStatus();

		CheckErrStatus();
		//AutoProtect();
		//RefreshParam();
		
		// ����FPGA����ָʾ��
		//FPGA_ENABLE_WRITE;
		//FpgaWriteRegister(FPGA_REG_SHOW_ERROR, sys_param_1b[MADD_WORK_ERROR].val);
		//FPGA_DISABLE_WRITE;

		
#endif	
	}

}

/*************************************************************
Name: CheckErrStatus_Erricson          
Description: ���ϵͳ�����Ƿ����쳣
Input: void
Return: void
**************************************************************/
void CheckErrStatus_Erricson()
{
	UCHAR8 i=0,j=0,err=0,tmp = 0;
	UCHAR8 au_err = 0,eu_err = 0,ru_err = 0;
	static UINT16 workerror_last = 0;//��һ�θ澯��ֵ
	static UINT16 workerror_current = 0;//���εĸ澯��ֵ
	static UCHAR8 fp_eu_cnt_old[FP_MAX] = {0};


	

	
	WTD_CLR;


#if 0
	// Ԥ����A\B��״̬
#if ( A_NETWORK_TYPE==NET_NONE )	// A��û�У�״̬ȫ������
	sys_param_1b[MADD_A_TX_PLL_ST].val = 0;
	sys_param_1b[MADD_A_RX_PLL_ST].val = 0;
	sys_param_1b[MADD_A_BB_PLL_LOCK].val = 0;
#endif

#if ( B_NETWORK_TYPE==NET_NONE )	// B��û�У�״̬ȫ������
	sys_param_1b[MADD_B_TX_PLL_ST].val = 0;
	sys_param_1b[MADD_B_RX_PLL_ST].val = 0;
	sys_param_1b[MADD_B_BB_PLL_LOCK].val = 0;
#endif

#if ( C_NETWORK_TYPE==NET_NONE )	// C��û�У�״̬ȫ������
	sys_param_1b[MADD_C_TX_PLL_ST].val = 0;
	sys_param_1b[MADD_C_RX_PLL_ST].val = 0;
	sys_param_1b[MADD_C_BB_PLL_LOCK].val = 0;
#endif

#if ( D_NETWORK_TYPE==NET_NONE )	// D��û�У�״̬ȫ������
	sys_param_1b[MADD_D_TX_PLL_ST].val = 0;
	sys_param_1b[MADD_D_RX_PLL_ST].val = 0;
	sys_param_1b[MADD_D_BB_PLL_LOCK].val = 0;
#endif


	// FPGA�����쳣
	if ( sys_param_1b[MADD_LOAD_FPGA_ST].val !=0 ) goto _set_work_err;

	// ʱ��ʧ��
	if ( sys_param_1b[MADD_CLK_PLL_ST].val==1 ) goto _set_work_err;

	// ����ʧ��
	if ( sys_param_1b[MADD_A_TX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_A_RX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_B_TX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_B_RX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_C_TX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_C_RX_PLL_ST].val==1) goto _set_work_err;

	// FPGA���໷ʧ��
	if ( sys_param_1b[MADD_FPGA_CLK_ST].val == 1) goto _set_work_err;
	
	// DA���໷ʧ��
	if ( sys_param_1b[MADD_A_BB_PLL_LOCK].val ==1 ) goto _set_work_err;
	if ( sys_param_1b[MADD_B_BB_PLL_LOCK].val ==1 ) goto _set_work_err;

	// LNA�쳣
	
	
	// ����쳣
	for( i=0; i<FP_MAX; i++)
	{
		if ( sys_param_1b[MADD_FP1_LOS+i].val==1 ) goto _set_work_err;
		if ( sys_param_1b[MADD_FP1_LOF+i].val==1 ) goto _set_work_err;
		if ( sys_param_1b[MADD_SERDES1_PLL_ST+i].val==1 ) goto _set_work_err;
	}

	if ( sys_param_1b[MADD_OPT_LOF].val == 1) goto _set_work_err;

	sys_param_1b[MADD_WORK_ERROR].val = 0;
	return;

_set_work_err:		// ���ô���״̬
	sys_param_1b[MADD_WORK_ERROR].val = 1;
#endif
	//���ù�ڲ�����EUʱ�����Ӧ��EU RU�澯��
	#if 0
	for(i=0; i<FP_MAX; i++)
	{
		if(sys_param_1b[MADD_FP1_LOS+i].val)
		{
			//sys_param_eu_1b[MADD_EU_ALARM_FLAG1+i].val = tmp? 0:sys_param_eu_1b[MADD_EU_ALARM_FLAG1+i].val;  //��ʧ���� ����澯
			//sys_param_eu_2b[MADD_EU_RUALARM_FLAG1+i].val  = tmp? 0:sys_param_eu_2b[MADD_EU_RUALARM_FLAG1+i].val; //��ʧ��������澯
			sys_param_eu_1b[MADD_EU_ALARM_FLAG1+i].val = 0;
			sys_param_eu_2b[MADD_EU_RUALARM_FLAG1+i].val  = 0;
		 	for(j=0; j<RE_MAX; j++)
		 	{
		 		 topo_alarm[i][j].meu_alarm = 0;
				 topo_alarm[i][j].ru_alarm = 0;
		 	}
		}
	}
	#endif

	//����µļ���EU����ʱ��������ε���EU�ĸ澯״̬

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

	//for(i=FP_MAX; i<8; i++)//���������ڵĸ澯
	//{
	//	sys_param_eu_1b[MADD_EU_ALARM_FLAG1+i].val = 0;
	//	sys_param_eu_2b[MADD_EU_RUALARM_FLAG1+i].val = 0;
	//}

	

	au_err = 0;
	//�¶ȸ澯
	//workerror_current |= sys_param_1b[MADD_BOARD_TEMP].val>80? (0x01):0x00;
	au_err |= sys_param_1b[MADD_BOARD_TEMP].val>80? (0x01):0x00;

	//ʱ��ʧ��
	au_err |=sys_param_1b[MADD_CLK_PLL_ST].val? 0x02:0x00;

	//������·�쳣�澯

	//if(sys_param_1b[MADD_FP1_LOS+0].val |sys_param_1b[MADD_FP1_LOS+1].val |sys_param_1b[MADD_FP1_LOS+2].val |sys_param_1b[MADD_FP1_LOS+3].val )
	//	workerror_current = 0x04;

	for(i=0; i<FP_MAX; i++)
	{
		err += sys_param_1b[MADD_FP1_LOS+i].val;
	}
	if(err >0)
		au_err |= 0x04;

	//���˸澯
	if(topo_err_count >=1)
	{
	
		//au_err |= 0x08;//��ʱ�رոø澯
	}

	sys_param_1b[MADD_WORK_ERROR].val = au_err;//AU��Ӧ�ĸ澯��
	//sys_param_1b[MADD_WORK_ERROR].val = 3;//AU��Ӧ�ĸ澯��

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

	
	//���ܸ澯��	
	workerror_current = 0;
	workerror_current |=  au_err? 0x8000:0x0000;//AU�澯
	workerror_current |=  eu_err?0x4000:0x0000;
	workerror_current |=  ru_err?0x2000:0x0000;
	//workerror_current |= (sys_param_eu_1b[MADD_EU_ALARM_FLAG1].val ||sys_param_eu_1b[MADD_EU_ALARM_FLAG2].val ||sys_param_eu_1b[MADD_EU_ALARM_FLAG3].val ||sys_param_eu_1b[MADD_EU_ALARM_FLAG4].val)? 0x4000:0x0000;//��4λΪEU�澯
	//workerror_current |= (sys_param_eu_2b[MADD_EU_RUALARM_FLAG1].val ||sys_param_eu_2b[MADD_EU_RUALARM_FLAG2].val ||sys_param_eu_2b[MADD_EU_RUALARM_FLAG3].val ||sys_param_eu_2b[MADD_EU_RUALARM_FLAG4].val)? 0x2000:0x0000;//��4λΪRU�澯
	
	//sys_param_1b[MADD_WORK_ERROR].val = 0x3;
	
	//workerror_current = ((UINT16)sys_param_1b[MADD_WORK_ERROR].val<<15)|((UINT16)sys_param_1b[MADD_WORK_ERROR].val<<14)|((UINT16)sys_param_1b[MADD_WORK_ERROR].val<<13);//AU EU RU 
	//workerror_current = 0x6000;
	if(workerror_last != workerror_current)
	{
		printf("Alarm Occurred\r\n");
		workerror_last = workerror_current;
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_SHOW_ERROR,( ~workerror_current)&0xF000);//�͵�ƽ�澯
		FPGA_DISABLE_WRITE;
		sys_param_1b[MADD_HOST_DEVICE_LINK_SINGNAL_ALARM].val  = (UCHAR8) (workerror_last>>8);
	}
	
}

/*************************************************************
Name: CheckErrStatus          
Description: ���ϵͳ�����Ƿ����쳣
Input: void
Return: void
**************************************************************/
void CheckErrStatus()
{

#if 0
	UCHAR8 i;
	
	WTD_CLR;

	// Ԥ����A\B��״̬
#if ( A_NETWORK_TYPE==NET_NONE )	// A��û�У�״̬ȫ������
	sys_param_1b[MADD_A_TX_PLL_ST].val = 0;
	sys_param_1b[MADD_A_RX_PLL_ST].val = 0;
	sys_param_1b[MADD_A_BB_PLL_LOCK].val = 0;
#endif

#if ( B_NETWORK_TYPE==NET_NONE )	// B��û�У�״̬ȫ������
	sys_param_1b[MADD_B_TX_PLL_ST].val = 0;
	sys_param_1b[MADD_B_RX_PLL_ST].val = 0;
	sys_param_1b[MADD_B_BB_PLL_LOCK].val = 0;
#endif

#if ( C_NETWORK_TYPE==NET_NONE )	// C��û�У�״̬ȫ������
	sys_param_1b[MADD_C_TX_PLL_ST].val = 0;
	sys_param_1b[MADD_C_RX_PLL_ST].val = 0;
	sys_param_1b[MADD_C_BB_PLL_LOCK].val = 0;
#endif

#if ( D_NETWORK_TYPE==NET_NONE )	// D��û�У�״̬ȫ������
	sys_param_1b[MADD_D_TX_PLL_ST].val = 0;
	sys_param_1b[MADD_D_RX_PLL_ST].val = 0;
	sys_param_1b[MADD_D_BB_PLL_LOCK].val = 0;
#endif


	// FPGA�����쳣
	if ( sys_param_1b[MADD_LOAD_FPGA_ST].val !=0 ) goto _set_work_err;

	// ʱ��ʧ��
	if ( sys_param_1b[MADD_CLK_PLL_ST].val==1 ) goto _set_work_err;

	// ����ʧ��
	if ( sys_param_1b[MADD_A_TX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_A_RX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_B_TX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_B_RX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_C_TX_PLL_ST].val==1) goto _set_work_err;
	if ( sys_param_1b[MADD_C_RX_PLL_ST].val==1) goto _set_work_err;

	// FPGA���໷ʧ��
	if ( sys_param_1b[MADD_FPGA_CLK_ST].val == 1) goto _set_work_err;
	
	// DA���໷ʧ��
	if ( sys_param_1b[MADD_A_BB_PLL_LOCK].val ==1 ) goto _set_work_err;
	if ( sys_param_1b[MADD_B_BB_PLL_LOCK].val ==1 ) goto _set_work_err;

	// LNA�쳣
	
	
	// ����쳣
	for( i=0; i<FP_MAX; i++)
	{
		if ( sys_param_1b[MADD_FP1_LOS+i].val==1 ) goto _set_work_err;
		if ( sys_param_1b[MADD_FP1_LOF+i].val==1 ) goto _set_work_err;
		if ( sys_param_1b[MADD_SERDES1_PLL_ST+i].val==1 ) goto _set_work_err;
	}

	if ( sys_param_1b[MADD_OPT_LOF].val == 1) goto _set_work_err;

	sys_param_1b[MADD_WORK_ERROR].val = 0;
	return;

_set_work_err:		// ���ô���״̬
	sys_param_1b[MADD_WORK_ERROR].val = 1;

	

	if(workerror_last != sys_param_1b[MADD_WORK_ERROR].val)
	{
		printf("Alarm Occurred\r\n");
		workerror_last = sys_param_1b[MADD_WORK_ERROR].val;
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_SHOW_ERROR, sys_param_1b[MADD_WORK_ERROR].val);
		FPGA_DISABLE_WRITE;
	}
#endif

#if ((defined CLIENT_ERRICSON)||(defined CLIENT_ERRICSON2)||(defined CLIENT_ERRICSON_W))

CheckErrStatus_Erricson();


#endif

	
}

// �Զ�������ʩ
void AutoProtect( void )
{
	UCHAR8 err_off;		// ���Ϲض������־ 1-�ض�

	// A��
	err_off = 0;
	
	if (0==sys_param_1b[MADD_A_DL_WORK_EN].val)	err_off = 1;
	if (0==sys_param_1b[MADD_A_UL_WORK_EN].val)	err_off = 1;
	if (1==sys_param_1b[MADD_A_TX_PLL_ST].val) 	err_off = 1;
	if (1==sys_param_1b[MADD_A_RX_PLL_ST].val) 	err_off = 1;
	if (1==sys_param_1b[MADD_A_BB_PLL_LOCK].val) err_off = 1;
	if (1==sys_param_1b[MADD_CLK_PLL_ST].val)	err_off = 1;

	if ( 0==err_off )	// ����Ҫ�ض�
	{
		if ( b_FALSE==FpgaIsEnableA() )	// ��֮ǰ�ر���FPGA���������
		{ 
			FpgaWorkEnableA( 1 );
		} 
	}
	else	// �ض����
	{
		FpgaWorkEnableA( 0 ); 
	}

	// B��
	err_off = 0;	

	if (0==sys_param_1b[MADD_B_DL_WORK_EN].val)	err_off = 1;
	if (0==sys_param_1b[MADD_B_UL_WORK_EN].val)	err_off = 1;
	if (1==sys_param_1b[MADD_B_TX_PLL_ST].val) 	err_off = 1;
	if (1==sys_param_1b[MADD_B_RX_PLL_ST].val) 	err_off = 1;
	if (1==sys_param_1b[MADD_B_BB_PLL_LOCK].val) err_off = 1;
	if (1==sys_param_1b[MADD_CLK_PLL_ST].val)	err_off = 1;

	if ( 0==err_off )	// ����Ҫ�ض�
	{
		if ( b_FALSE==FpgaIsEnableB() )	// ��֮ǰ�ر���FPGA���������
		{ 
			FpgaWorkEnableB( 1 );
		} 
	}
	else	// �ض����
	{
		FpgaWorkEnableB( 0 ); 
	}

#if 0
	if ((1==sys_param_1b[MADD_A_DL_WORK_EN].val)&&(1==sys_param_1b[MADD_A_UL_WORK_EN].val))
	{
		if (( sys_param_1b[MADD_A_TX_PLL_ST].val==1 )||( sys_param_1b[MADD_A_RX_PLL_ST].val==1 )||( sys_param_1b[MADD_A_BB_PLL_LOCK].val ==1 ))
		{
			// ʱ��ʧ����ض�FPGA���
			//TRACE_ERROR("SecA Err, Close Output\r\n");
			FpgaWorkEnableA( 0 );
		}
		else if ( b_FALSE==FpgaIsEnableA() )
		{
			// ʱ����������֮ǰ�ر���FPGA���������
			FpgaWorkEnableA( 1 );
		}
	}

	if ((1==sys_param_1b[MADD_B_DL_WORK_EN].val)&&(1==sys_param_1b[MADD_B_UL_WORK_EN].val))
	{
		if (( sys_param_1b[MADD_B_TX_PLL_ST].val==1 )||( sys_param_1b[MADD_B_RX_PLL_ST].val==1 )||( sys_param_1b[MADD_B_BB_PLL_LOCK].val ==1 ))
		{
			// ʱ��ʧ����ض�FPGA���
			//TRACE_ERROR("SecB Err, Close Output\r\n");
			FpgaWorkEnableB( 0 );
		}
		else if ( b_FALSE==FpgaIsEnableB() )
		{
			// ʱ����������֮ǰ�ر���FPGA���������
			FpgaWorkEnableB( 1 );
		}
	}
#endif
}

/*************************************************************
Name:UpdateWorkParam          
Description: ���ù�������
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
	FpgaWorkEnableA( 0 );
	FpgaWorkEnableB( 0 );
	FpgaWorkEnableC( 0 );
	FpgaWorkEnableD( 0 );
//	FpgaAttOutput(1);		// ����˥����ȫ˥����ֹ�߼���ʼ����ʱ���ֵ���ɢ

	//���ı����������Ƶ��
	if( 0 != ( mask&PCHG_CENTER_FRE_FLAG) )
	{
		//printf("��������Ƶ��\r\n");
		#if defined CLIENT_JIZHUN
		//TRACE_INFO("�Ͳ�����A = %d\r\n",(CHAR8)sys_param_1b[MADD_A_LTHR_DN].val) ;  
		MoveCenterFre(SYS_A_FLAG, SYS_DL_FLAG);
		#endif
	}
#if 0
	// ��Ҫ���ñ��� 
	if ( 0!= (mask&PCHG_A_FL_CHG) ) 
	{
		mask |= PCHG_A_CHANNEL;	// �����޸�֮���߼���ͨ���Ĵ���Ƶ����Ҫ���¼���
		
		Init_Local_Pll(A_MIXER); 
		Init_Local_Pll(A_MODEN);  
		

	} 

	if ( 0!= (mask&PCHG_B_FL_CHG) ) 
	{
		mask |= PCHG_B_CHANNEL;	// �����޸�֮���߼���ͨ���Ĵ���Ƶ����Ҫ���¼���
		//Init_Local_Pll(B_MIXER); 
		//Init_Local_Pll(B_MODEN); 
		//FpgaSetFreqAdjB();
	
	}

	
#endif

	#if defined CLIENT_ERRICSON
	// �޸�Ƶ��������Χ
	if ( 0!= (mask&PCHG_FPS_RANGE) )
	{

		//FPS_Init();
		//FPS_SetScanFc( &mod_cfg_a );
		//FPS_EnableAutoScan();
		WTD_CLR;
		FPS_SetParam(); 
	}
	#endif
	// ����ͨ����ͨ��ʹ��
	if ( 0 != ( mask&PCHG_A_CHANNEL) )
	{
		WTD_CLR;
		SetChannelByParam(SYS_A_FLAG);
	}

	if ( 0 != ( mask&PCHG_C_CHANNEL) )
	{
		WTD_CLR;
		SetChannelByParam(SYS_C_FLAG);
	}
	
	if ( 0 != ( mask&PCHG_D_CHANNEL) )
	{
		WTD_CLR;
		SetChannelByParam(SYS_D_FLAG);
	}

#if 0

	if ( 0!= (mask&(PCHG_A_CHANNEL|PCHG_B_CHANNEL|PCHG_C_CHANNEL|PCHG_D_CHANNEL)) )
	{
		WTD_CLR;
		// �㲥����Ƶ��
		sys_work_info |= SYSTEM_FLAG_SET_RE_SFC;
		// ʹ�ܻ�����ͳ��,15����
		FpgaEnableTrafficCtl( TRAFFIC_TIME, 1 );
		//traffic_start = 1;
	}
	
	// ���������й���ӳ�
	if ( 0!= ( mask&PCHG_OPT_DELAY ) )
	{
		WTD_CLR;
		SetReSysConfig();
		// ����汾���˲������������õ��������ݰ����ͣ�����ɰ����û��������ᵼ������ʧ��
		//SetReBwConfig();

		sys_work_info |= SYSTEM_FLAG_SET_RE_SYS_CFG;
	}

	// ��������ͨ������� 2012.6.20 ������µ��ж�����  PCHG_A_CHANNEL|PCHG_B_CHANNEL
	if ( 0 != ( mask&(PCHG_A_POW_GAIN|PCHG_B_POW_GAIN|PCHG_A_CHANNEL|PCHG_B_CHANNEL|PCHG_C_POW_GAIN|PCHG_D_POW_GAIN|PCHG_C_CHANNEL|PCHG_D_CHANNEL)) )
	{
		WTD_CLR;
		TRACE_INFO("PCHG_A_POW_GAIN|PCHG_B_POW_GAIN|PCHG_A_CHANNEL|PCHG_B_CHANNEL\r\n");
		FpgaSetOutAttValueA();
		FpgaSetOutAttValueC();
		FpgaSetOutAttValueD();		
//		SetReUlPowerGain();
		sys_work_info |= SYSTEM_FLAG_SET_RE_UPOW;
	}

	if ( 0!=( mask&PCHG_TD_PARAM ) )
	{
		WTD_CLR;
		SetTDParam_C();
		//SetTDParam_D();
		
		sys_work_info |= SYSTEM_FLAG_SET_RE_TDSLOT;
	}

#endif
	 // ����A����Ƶ����ʹ��
 	if ( 0 != ( mask&(PCHG_A_WORK_EN)) )
 	{
 		RFWorkEnableA(); 
 	}

	// ����B����Ƶ����ʹ��
 	if ( 0 != ( mask&(PCHG_A_WORK_EN)) )
 	{
 		WTD_CLR;
 		RFWorkEnableB(); 
 	}

	 // ����C����Ƶ����ʹ��
 	if ( 0 != ( mask&(PCHG_C_WORK_EN)) )
 	{
	 	 WTD_CLR;	
  		RFWorkEnableC();
 	}

	 // ����D����Ƶ����ʹ��
 	if ( 0 != ( mask&(PCHG_D_WORK_EN)) )
 	{
		WTD_CLR;
		RFWorkEnableD();
 	}
#if 0

	// ���ÿ��ƶ˿ڲ�����
	if ( 0 != ( mask&PCHG_CTRL_BAUD) )
	{
		WTD_CLR;
		//CtrlUartConfig();
	}

	// ����͸���˿�
	if ( 0 != ( mask&PCHG_THR_CONFIG) )
	{
		//ThrUartConfig();
	}

#endif

#if 0
	// �͹���ģʽ
	if ( 0 != (mask&PCHG_LOW_POWER) )
	{
		if ( sys_param_1b[MADD_LOW_POWER].val ==0 )
		{
			//SysNormalWorkMode();
			;
		}
		else
		{
			//SysLowPowerMode();
			;
		}
	}
#endif

	// ���ù��ʹ��
	if ( 0 != ( mask&PCHG_SYS_FP_EN) )
	{
		 WTD_CLR;
		 EnableOpt();
	}

	//���ñ������
	#if 0
	if(0!=( mask&PCHG_BENZHEN_ADJ_FLAG ) )
	{
		//SetAdjBenZhenSignalPara();
	}
	#endif
	// ����������ɣ�����ǰģʽ���ǵ͹���ģʽ�������ʹ��λʹ��FPGA����
	#if 0
	if ( 0 == (sys_work_info & SYSTEM_FLAG_LOW_POWER ) )	
	{
	}
	#endif
	
	// ���ù���ʹ��
	FpgaWorkEnableA( sys_param_1b[MADD_A_DL_WORK_EN].val);
	FpgaWorkEnableB( sys_param_1b[MADD_B_DL_WORK_EN].val);
	FpgaWorkEnableC( sys_param_1b[MADD_C_DL_WORK_EN].val);
	FpgaWorkEnableD( sys_param_1b[MADD_D_DL_WORK_EN].val);
	
	#if 0	
	if ((1==sys_param_1b[MADD_A_DL_WORK_EN].val)&&(1==sys_param_1b[MADD_A_UL_WORK_EN].val))
		{
			FpgaWorkEnableA( 1);
		}
		else
		{
			FpgaWorkEnableA( 0 );
		}

		if ((1==sys_param_1b[MADD_B_DL_WORK_EN].val)&&(1==sys_param_1b[MADD_B_UL_WORK_EN].val))
		{
			FpgaWorkEnableB( 1 );
		}
		else
		{
			FpgaWorkEnableB( 0 );
		}

		if ((1==sys_param_1b[MADD_C_DL_WORK_EN].val)&&(1==sys_param_1b[MADD_C_UL_WORK_EN].val))
		{
			FpgaWorkEnableC( 1 );
		}
		else
		{
			FpgaWorkEnableC( 0 );
		}

		if ((1==sys_param_1b[MADD_D_DL_WORK_EN].val)&&(1==sys_param_1b[MADD_D_UL_WORK_EN].val))
		{
			FpgaWorkEnableD( 1 );
		}
		else
		{
			FpgaWorkEnableD( 0 );
		}
#endif		
	// �ָ�˥��������
	UsNopDelay(100*1000);			// ��ʱ5ms
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
Description: ����REC��Ƶ�ʲ�������
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

void SetTDParam_C()
{
	UINT32 i;
	UINT16 tmp=0;
	INT32 val;

	FPGA_ENABLE_WRITE;


	// TD����ģʽ
	FpgaWriteRegister( FPGA_REC_C_TD_WORK_MODE, sys_param_1b[MADD_C_TD_WORK_MODE].val );

	// ��һת�������ʱ��ns
	val = (INT16)sys_param_2b[MADD_C_TD_1ST_CP_TIME].val;	// �з��������ȴ�������չΪ32λ�ٰ��޷���������
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REC_C_TD_1ST_TIME, tmp);

	// �ڶ�ת�������ʱ��ns
	val = (INT16)sys_param_2b[MADD_C_TD_2ND_CP_TIME].val;	// �з��������ȴ�������չΪ32λ�ٰ��޷���������
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REC_C_TD_2ND_TIME, tmp);

	// LNA�����ٺ�DN_PA�رյı���ʱ��ns
	val = (INT16)sys_param_2b[MADD_C_TD_LNA_ON_TIME].val;		// �޷�����
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REC_C_TD_LNA_ON_TIME, tmp);

	// LNA�رճ�ǰDN_PA�����ı���ʱ��ns
	val = (INT16)sys_param_2b[MADD_C_TD_LNA_OFF_TIME].val;		// �޷�����
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REC_C_TD_LNA_OFF_TIME, tmp);
	
	tmp = (sys_param_1b[MADD_C_TD_TYPE_SELECT].val&0X07)| ((sys_param_1b[MADD_C_TD_NORMAL_CP].val<<3)&0X78)|((sys_param_1b[MADD_C_TD_EXTENDED_CP].val<<7)&0X80);

	sys_param_1b[MADD_D_TD_TYPE_SELECT].val=sys_param_1b[MADD_C_TD_TYPE_SELECT].val;
	sys_param_1b[MADD_D_TD_WORK_MODE].val=sys_param_1b[MADD_C_TD_WORK_MODE].val;

	if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
	|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
	|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
	|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
	|| (version_number == VERSION_50M_IN_V5)
	)
	{
		if(sys_param_1b[MADD_SLOT_TIME_EN_C].val==1)//����TDSʱ϶����Զ����
		{
			tmp = (UINT16)sys_param_1b[MADD_SLOT_TIME_EN_C].val;		
			tmp <<= 15;
			TRACE_INFO("FPGA_REG_W_SLOT_TIME_C=[%X]\r\n",tmp);
			FpgaWriteRegister( FPGA_REG_W_SLOT_TIME_C, tmp );
		}
		else
		{
			FpgaWriteRegister( FPGA_REG_W_SLOT_TIME_C, 0 );//�ر�ʱ϶�Զ����

			// ʱ϶���������
			FpgaWriteRegister(FPGA_REC_C_TS_CONFIG, tmp);
			//������֡���
			//FpgaWriteRegister(FPGA_REC_C_TS_CONFIG, sys_param_1b[MADD_C_TD_NORMAL_CP].val);
			//CP���
			//FpgaWriteRegister(FPGA_REC_C_TS_CONFIG, sys_param_1b[MADD_C_TD_EXTENDED_CP].val);
		}
	}	
	else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
	{
		// ʱ϶���������
		FpgaWriteRegister(FPGA_REC_C_TS_CONFIG, tmp);
		//������֡���
		//FpgaWriteRegister(FPGA_REC_C_TS_CONFIG, sys_param_1b[MADD_C_TD_NORMAL_CP].val);
		//CP���
		//FpgaWriteRegister(FPGA_REC_C_TS_CONFIG, sys_param_1b[MADD_C_TD_EXTENDED_CP].val);
	}
	
	FPGA_DISABLE_WRITE;

}


void SetTDParam_D()
{
		UINT32 i;
	UINT16 tmp=0;
	INT32 val;

	FPGA_ENABLE_WRITE;

	// TD����ģʽ
	FpgaWriteRegister( FPGA_REC_D_TD_WORK_MODE, sys_param_1b[MADD_D_TD_WORK_MODE].val );

	// ��һת�������ʱ��ns
	val = (INT16)sys_param_2b[MADD_D_TD_1ST_CP_TIME].val;	// �з��������ȴ�������չΪ32λ�ٰ��޷���������
	tmp = _CalcTdTimeParam( val );
	TRACE_INFO("tm=[%X]\r\n",tmp);
	FpgaWriteRegister(FPGA_REC_D_TD_1ST_TIME, tmp);

	// �ڶ�ת�������ʱ��ns
	val = (INT16)sys_param_2b[MADD_D_TD_2ND_CP_TIME].val;	// �з��������ȴ�������չΪ32λ�ٰ��޷���������
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REC_D_TD_2ND_TIME, tmp);

	// LNA�����ٺ�DN_PA�رյı���ʱ��ns
	val = (INT16)sys_param_2b[MADD_D_TD_LNA_ON_TIME].val;		// �޷�����
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REC_D_TD_LNA_ON_TIME, tmp);

	// LNA�رճ�ǰDN_PA�����ı���ʱ��ns
	val = (INT16)sys_param_2b[MADD_D_TD_LNA_OFF_TIME].val;		// �޷�����
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REC_D_TD_LNA_OFF_TIME, tmp);
	

	tmp = (sys_param_1b[MADD_D_TD_TYPE_SELECT].val&0X07)| ((sys_param_1b[MADD_D_TD_NORMAL_CP].val<<3)&0X78)|((sys_param_1b[MADD_D_TD_EXTENDED_CP].val<<15)&0X80);
	// ʱ϶���������
	FpgaWriteRegister(FPGA_REC_D_TS_CONFIG, tmp);
	//������֡���
	//FpgaWriteRegister(FPGA_REC_D_TS_CONFIG, sys_param_1b[MADD_D_TD_NORMAL_CP].val);
	//CP���
	//FpgaWriteRegister(FPGA_REC_D_TS_CONFIG, sys_param_1b[MADD_D_TD_EXTENDED_CP].val);

	
	FPGA_DISABLE_WRITE;

}
void SetTDParam_B()
{
	UINT32 i;
	UINT16 tmp=0;
	INT32 val;

	
	
	FPGA_ENABLE_WRITE;
	if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
	|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
	|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
	|| (version_number == VERSION_50M_IN_F) || (version_number == VERSION_50M_IN_V4)
	|| (version_number == VERSION_50M_IN_V5)
	)
	{
		// ʱ϶����������
		if(sys_param_1b[MADD_SLOT_TIME_EN_B].val==1)//TDSʱ϶����Զ����
		{
			tmp = (UINT16)sys_param_1b[MADD_SLOT_TIME_EN_B].val;		
			tmp <<= 15;
			TRACE_INFO("FPGA_REG_W_SLOT_TIME_B=[%X]\r\n",tmp);
			FpgaWriteRegister( FPGA_REG_W_SLOT_TIME_B, tmp );
		}
		else
		{
			FpgaWriteRegister( FPGA_REG_W_SLOT_TIME_B, 0 );//�ر�ʱ϶�Զ����
			for ( i=0; i<7; i++)
			{
				if ( sys_param_1b[MADD_TD_T0_UD+i].val == 1 )
				{
					tmp |= (1<<i);
				}
			} 
			TRACE_INFO("FPGA_REG_TDSLOT_CTL=[%X]\r\n",tmp);
			FpgaWriteRegister(FPGA_REG_TDSLOT_CTL, tmp);
		}
	}
	else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
	{
		for ( i=0; i<7; i++)
		{
			if ( sys_param_1b[MADD_TD_T0_UD+i].val == 1 )
			{
				tmp |= (1<<i);
			}
		} 
	
	
		// ʱ϶����������
		FpgaWriteRegister(FPGA_REG_TDSLOT_CTL, tmp);
	}

	// ��һת�������ʱ��ns
	val = sys_param_2b[MADD_TD_1ST_CP_TIME].val;	// �з��������ȴ�������չΪ32λ�ٰ��޷���������
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REG_TD_1ST_TIME, tmp);

	// �ڶ�ת�������ʱ��ns
	val = (INT16)sys_param_2b[MADD_TD_2ND_CP_TIME].val;	// �з��������ȴ�������չΪ32λ�ٰ��޷���������
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REG_TD_2ND_TIME, tmp);

	// LNA�����ٺ�DN_PA�رյı���ʱ��ns  
	val = (INT16)sys_param_2b[MADD_TD_LNA_ON_TIME].val;		// �޷�����
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REG_TD_LNA_ON_TIME, tmp);

	// LNA�رճ�ǰDN_PA�����ı���ʱ��ns  
	val = (INT16)sys_param_2b[MADD_TD_LNA_OFF_TIME].val;		// �޷�����
	tmp = _CalcTdTimeParam( val );
	FpgaWriteRegister(FPGA_REG_TD_LNA_OFF_TIME, tmp);

//	TRACE_INFO("sys_param_1b[MADD_TD_WORK_MODE].val=[%X]\r\n",sys_param_1b[MADD_TD_WORK_MODE].val);

	// TD����ģʽ
	FpgaWriteRegister( FPGA_REG_TD_WORK_MODE, sys_param_1b[MADD_TD_WORK_MODE].val );
	
	FPGA_DISABLE_WRITE;

}

/*************************************************************
Name: SysBroadcastReFcA          
Description: �㲥����RE��Ƶ��
Input: void
Return: void
**************************************************************/
void SysBroadcastReFcA( void )
{
#if ( defined(FUNC_FREQ_POINT_SEARCH_EN) && defined(FUNC_FPS_AUTO_SET) )	// ����Ƶ�����������Զ�����Ƶ��
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;
	UINT32 i;
	UINT16 addr_base;

	if ( 0!=(sys_work_info&SYSTEM_FLAG_ATT_ADJ) )		// ����У׼״̬��������RE����
	{
		return;
	}
		
	if ((total_re_count == 0 )||( total_re_count>(FP_MAX*RE_MAX)))
	{
		return;
	}
	
	TRACE_INFO("Set Re Fc ParamA\r\n");

	p_msg[MSG_DES_FP] = BROADCAST_ADD_FP;
	p_msg[MSG_DES_RE] = BROADCAST_ADD_RE;
	p_msg[MSG_DES_REE] =0;
	p_msg[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_msg[MSG_SRC_RE] = LOCAL_ADD_RE;
	p_msg[MSG_SRC_REE] =0;
	p_msg[MSG_CMD_ID] = MSG_CMD_SET_PARAM;
	p_msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	tx_len = MSG_PKT_HEAD_SIZE;

	for ( i=0; i<MAX_CHANNEL_COUNT; i++)
	{
		tmp = MADD_A_DL_CHANNEL1+i;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[tmp].val&0xFF);	
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[tmp].val>>8);	
	}
	
	for ( i=0; i<MAX_CHANNEL_COUNT; i++)
	{
		tmp = MADD_A_DCH_EN1+i;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[tmp].val;	
	}

#if 1 //( ( B_NETWORK_TYPE==NET_DIVE ) ||( B_NETWORK_TYPE==NET_TYPE_GSM900 ) || ( B_NETWORK_TYPE==NET_TYPE_DCS1800 ) || ( B_NETWORK_TYPE==NET_TYPE_WCDMA2100) ) 

	for ( i=0; i<MAX_CHANNEL_COUNT; i++)
	{
		tmp = MADD_B_DL_CHANNEL1+i;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[tmp].val&0xFF);	
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[tmp].val>>8);	
	}
	
	for ( i=0; i<MAX_CHANNEL_COUNT; i++)
	{
		tmp = MADD_B_DCH_EN1+i;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[tmp].val;	
	}
	
#endif

	for ( i=0; i<MAX_CHANNEL_COUNT-6; i++)
	{
		tmp = MADD_C_DL_CHANNEL1+i;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[tmp].val&0xFF);	
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[tmp].val>>8);	
	}
	
	for ( i=0; i<MAX_CHANNEL_COUNT-6; i++)
	{
		tmp = MADD_C_DCH_EN1+i;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[tmp].val;	
	}


	for ( i=0; i<MAX_CHANNEL_COUNT-6; i++)
	{
		tmp = MADD_D_DL_CHANNEL1+i;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[tmp].val&0xFF);	
		p_msg[tx_len++] = (UCHAR8)(sys_param_2b[tmp].val>>8);	
	}
	
	for ( i=0; i<MAX_CHANNEL_COUNT-6; i++)
	{
		tmp = MADD_D_DCH_EN1+i;
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[tmp].val;	
	}
	

	SendMsgPkt(tx_len, p_msg);
#endif	

}

/*************************************************************
Name: SetReDpxInfo          
Description: ����RE�����������������
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

	// REC��A������˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_A_REC_DPX_IG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_A_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_A_UDPX_IN_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC��A�����˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_A_REC_DPX_OG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_A_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_A_UDPX_OUT_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	// REC��B������˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_B_REC_DPX_IG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_B_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_B_UDPX_IN_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC��B�����˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_B_REC_DPX_OG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_B_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_B_UDPX_OUT_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	
	// REC��C������˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_C_REC_DPX_IG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_C_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_C_UDPX_IN_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC��C�����˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_C_REC_DPX_OG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_C_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_C_UDPX_OUT_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	// REC��D������˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_D_REC_DPX_IG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_D_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_D_UDPX_IN_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC��D�����˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_D_REC_DPX_OG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_D_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_D_UDPX_OUT_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	TRACE_INFO("-------SetReDpxInfo---------MADD_A_REC_DPX_IG:%04X\r\n",sys_param_2b[MADD_A_UDPX_IN_GAIN].val);		
	SendMsgPkt(tx_len, p_msg);
	
}

/*************************************************************
Name: SetReUlPowerGain          
Description: ����RE�����������������
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

	if ( 0!=(sys_work_info&SYSTEM_FLAG_ATT_ADJ) )		// ����У׼״̬��������RE����
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

	// A�����й���---------- �������õ������������
	total_pow = (INT16)sys_param_2b[MADD_A_UCH_MAX_POW1].val;
	//pow_set = total_pow-(INT16)(pow_div_tbl[total_re_count]+0.5);
	pow_set = total_pow;		// ���ʲ�ƽ��
	// ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_A_UCH_MAX_POW1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_A_UCH_MAX_POW1>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 2;
	// ����
	p_msg[tx_len++] = (UCHAR8)(pow_set&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((pow_set>>8)&0x00FF);

	//A��������˥��---------
	// ��ַ��REC��������˥����ӦRE����������˥����ַ2
	p_msg[tx_len++] = (UCHAR8)(MADD_A_DCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_A_DCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_A_DCH_ATT11:%04X\r\n",sys_param_1b[MADD_A_DCH_ATT1].val);	
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_A_DCH_ATT1].val;	

	// A��������˥��---------
	// ��ַ��REC��������˥����ӦRE����������˥����ַ2
	p_msg[tx_len++] = (UCHAR8)(MADD_A_UCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_A_UCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_A_UCH_ATT11:%04X\r\n",sys_param_1b[MADD_A_UCH_ATT1].val);	
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_A_UCH_ATT1].val;	
	
	// B�����й���----------
	total_pow = (INT16)sys_param_2b[MADD_B_UCH_MAX_POW1].val;
	//pow_set = total_pow-pow_div_tbl[total_re_count];
	pow_set = total_pow;		// ���ʲ�ƽ��
	// ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_B_UCH_MAX_POW1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_B_UCH_MAX_POW1>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 2;
	// ����
	p_msg[tx_len++] = (UCHAR8)(pow_set&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((pow_set>>8)&0x00FF);

	//B��������˥��---------
	// ��ַ��REC��������˥����ӦRE����������˥����ַ2
	p_msg[tx_len++] = (UCHAR8)(MADD_B_DCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_B_DCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_B_DCH_ATT11:%04X\r\n",sys_param_1b[MADD_B_DCH_ATT1].val);	
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_B_DCH_ATT1].val;	

	// B��������˥��----------
	// ��ַ��REC��������˥����ӦRE����������˥����ַ2
	p_msg[tx_len++] = (UCHAR8)(MADD_B_UCH_REC_RF_ATT1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_B_UCH_REC_RF_ATT1>>8)&0x00FF);//20130302 modifi 
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_B_UCH_ATT1].val;


	// C�����й���---------- �������õ������������
	total_pow = (INT16)sys_param_2b[MADD_C_UCH_MAX_POW1].val;
	//pow_set = total_pow-(INT16)(pow_div_tbl[total_re_count]+0.5);
	pow_set = total_pow;		// ���ʲ�ƽ��
	// ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_C_UCH_MAX_POW1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_C_UCH_MAX_POW1>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 2;
	// ����
	p_msg[tx_len++] = (UCHAR8)(pow_set&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((pow_set>>8)&0x00FF);

	//C��������˥��---------
	// ��ַ��REC��������˥����ӦRE����������˥����ַ2
	p_msg[tx_len++] = (UCHAR8)(MADD_C_DCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_C_DCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_C_DCH_ATT11:%04X\r\n",sys_param_1b[MADD_C_DCH_ATT1].val);	
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_C_DCH_ATT1].val;	

	//C��������˥��---------
	// ��ַ��REC��������˥����ӦRE����������˥����ַ2
	p_msg[tx_len++] = (UCHAR8)(MADD_C_UCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_C_UCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_C_UCH_ATT11:%04X\r\n",sys_param_1b[MADD_C_UCH_ATT1].val);	
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_C_UCH_ATT1].val;	
	
	// D�����й���----------
	total_pow = (INT16)sys_param_2b[MADD_D_UCH_MAX_POW1].val;
	//pow_set = total_pow-pow_div_tbl[total_re_count];
	pow_set = total_pow;		// ���ʲ�ƽ��
	// ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_D_UCH_MAX_POW1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_D_UCH_MAX_POW1>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 2;
	// ����
	p_msg[tx_len++] = (UCHAR8)(pow_set&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((pow_set>>8)&0x00FF);

	//D��������˥��---------
	// ��ַ��REC��������˥����ӦRE����������˥����ַ2
	p_msg[tx_len++] = (UCHAR8)(MADD_D_DCH_REC_RF_ATT1&0x00FF);//20130302 modifi 
	p_msg[tx_len++] = (UCHAR8)((MADD_D_DCH_REC_RF_ATT1>>8)&0x00FF);
	TRACE_INFO("MADD_D_DCH_ATT11:%04X\r\n",sys_param_1b[MADD_D_DCH_ATT1].val);	
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_D_DCH_ATT1].val;	

	// D��������˥��----------
	// ��ַ��REC��������˥����ӦRE����������˥����ַ2
	p_msg[tx_len++] = (UCHAR8)(MADD_D_UCH_REC_RF_ATT1&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_D_UCH_REC_RF_ATT1>>8)&0x00FF);//20130302 modifi 
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_D_UCH_ATT1].val;
	

#if 0//201411120931
	p_msg[tx_len++] = (UCHAR8)(MADD_METER_OFFSET&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_METER_OFFSET>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_METER_OFFSET].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_METER_OFFSET_B&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_METER_OFFSET_B>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_METER_OFFSET_B].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_METER_OFFSET_C&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_METER_OFFSET_C>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_METER_OFFSET_C].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_METER_OFFSET_D&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_METER_OFFSET_D>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_METER_OFFSET_D].val;
#endif 

	p_msg[tx_len++] = (UCHAR8)(MADD_A_DL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_A_DL_RF_EN>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_A_DL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_A_UL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_A_UL_RF_EN>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_A_UL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_B_DL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_B_DL_RF_EN>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_B_DL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_B_UL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_B_UL_RF_EN>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_B_UL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_C_DL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_C_DL_RF_EN>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_C_DL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_C_UL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_C_UL_RF_EN>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_C_UL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_D_DL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_D_DL_RF_EN>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_D_DL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_D_UL_RF_EN&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_D_UL_RF_EN>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_D_UL_RF_EN].val;

	p_msg[tx_len++] = (UCHAR8)(MADD_FREQ_MODIF_VAL_D&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_FREQ_MODIF_VAL_D>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_FREQ_MODIF_VAL_D].val;	

	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_A&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_A>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_DELAY_MODE_A].val;	

	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_B&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_B>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_DELAY_MODE_B].val;	

	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_C&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_C>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_DELAY_MODE_C].val;	
	
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_D&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_D>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = (UCHAR8)sys_param_1b[MADD_DELAY_MODE_D].val;	

	// REC��A������˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_A_REC_DPX_IG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_A_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_A_UDPX_IN_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC��A�����˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_A_REC_DPX_OG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_A_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_A_UDPX_OUT_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	// REC��B������˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_B_REC_DPX_IG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_B_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_B_UDPX_IN_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC��B�����˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_B_REC_DPX_OG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_B_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_B_UDPX_OUT_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	
	// REC��C������˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_C_REC_DPX_IG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_C_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_C_UDPX_IN_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC��C�����˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_C_REC_DPX_OG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_C_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_C_UDPX_OUT_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);

	// REC��D������˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_D_REC_DPX_IG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_D_REC_DPX_IG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_D_UDPX_IN_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	
	// REC��D�����˫��������
	p_msg[tx_len++] = (UCHAR8)(MADD_D_REC_DPX_OG&0x00FF);			// RE�е�REC˫����������ַ
	p_msg[tx_len++] = (UCHAR8)((MADD_D_REC_DPX_OG>>8)&0x00FF);
	p_msg[tx_len++] = 2;		// ����
	tmp = sys_param_2b[MADD_D_UDPX_OUT_GAIN].val;		// ����
	p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
	TRACE_INFO("-------SetReDpxInfo---------MADD_A_REC_DPX_IG:%04X\r\n",sys_param_2b[MADD_A_UDPX_IN_GAIN].val);		
	
	// ����˲�������
	p_msg[tx_len++] = (UCHAR8)(MADD_GSM_BW_SEL&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_GSM_BW_SEL>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = sys_param_1b[MADD_GSM_BW_SEL].val;	
	
	
	//TRACE_INFO("MADD_B_UCH_ATT11:%04X\r\n",sys_param_1b[MADD_D_UCH_ATT1].val);	

	TRACE_INFO("Set Re PowGain_p_msg[MSG_DES_REE]:%02x\r\n",p_msg[MSG_DES_REE]);
	SendMsgPkt(tx_len, p_msg);


}

/*************************************************************
Name: SetReSysConfig          
Description: ����RE�����������������
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

	// ����˲�������
	p_msg[tx_len++] = (UCHAR8)(MADD_GSM_BW_SEL&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_GSM_BW_SEL>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = sys_param_1b[MADD_GSM_BW_SEL].val;	

	SendMsgPkt(tx_len, p_msg);
	
}

/*************************************************************
Name: SetReSysConfig          
Description: ����RE����ʱģʽ 
Input: void 
Return: void 
**************************************************************/
void SetReSysConfig()
{
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;

	if ( 0!=(sys_work_info&SYSTEM_FLAG_ATT_ADJ) )		// ����У׼״̬��������RE����
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
	// ��ʱģʽ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE].val;	

	sys_param_1b[MADD_DELAY_MODE_A].val=sys_param_1b[MADD_DELAY_MODE].val;
	sys_param_1b[MADD_DELAY_MODE_B].val=sys_param_1b[MADD_DELAY_MODE].val;
	sys_param_1b[MADD_DELAY_MODE_C].val=sys_param_1b[MADD_DELAY_MODE].val;
	sys_param_1b[MADD_DELAY_MODE_D].val=sys_param_1b[MADD_DELAY_MODE].val;
	
	// ��ʱģʽ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_A&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_A>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE_A].val;	

	// ��ʱģʽ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_B&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_B>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE_B].val;	

	// ��ʱģʽ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_C&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_C>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE_C].val;		

	// ��ʱģʽ��ַ
	p_msg[tx_len++] = (UCHAR8)(MADD_DELAY_MODE_D&0x00FF);	
	p_msg[tx_len++] = (UCHAR8)((MADD_DELAY_MODE_D>>8)&0x00FF);
	// ����
	p_msg[tx_len++] = 1;
	// ����
	p_msg[tx_len++] = sys_param_1b[MADD_DELAY_MODE_D].val;		

	//crc
	p_msg[tx_len++] =0;	
	p_msg[tx_len++] = 0;
	
	SendMsgPkt(tx_len, p_msg);
	
}

/*************************************************************
Name: SetReDelayMode          
Description: ����RE��TD����
Input: void 
Return: void
**************************************************************/
void SetReTDParam()
{
	const UINT16 mo_param_add_list1[]={		// һ�ֽڲ�����TDͨ������������
		MADD_TD_T0_UD, 
		MADD_TD_T1_UD, 	
		MADD_TD_T2_UD, 
		MADD_TD_T3_UD, 
		MADD_TD_T4_UD, 
		MADD_TD_T5_UD,	
		MADD_TD_T6_UD,
	};
	const UINT16 mo_param_add_list2[]={		 // ���ֽڲ�����TDת����ʱ��
		MADD_TD_1ST_CP_TIME,
		MADD_TD_2ND_CP_TIME, 
		MADD_TD_LNA_ON_TIME, 
		MADD_TD_LNA_OFF_TIME, 
	};
	
	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;
	UINT32 i;

	if ( 0!=(sys_work_info&SYSTEM_FLAG_ATT_ADJ) )		// ����У׼״̬��������RE����
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
		// TDʱ϶������ģʽ��ַ
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		// ����
		p_msg[tx_len++] = 1;
		// ����
		p_msg[tx_len++] = sys_param_1b[tmp].val;	
	}
	
	for ( i=0; i<ARRY_NUM(mo_param_add_list2, UINT16); i++)
	{
		tmp = mo_param_add_list2[i];	// MADD_TD_T0_UD+i;
		// TDʱ϶������ģʽ��ַ
		p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
		// ����
		p_msg[tx_len++] = 2;
		// ����
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
#if 0
		p_msg[tx_len++] = (UCHAR8)(MADD_D_TD_WORK_MODE&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_D_TD_WORK_MODE>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_D_TD_WORK_MODE].val;	

				p_msg[tx_len++] = (UCHAR8)(MADD_D_TD_1ST_CP_TIME&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_D_TD_1ST_CP_TIME>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_1b[MADD_D_TD_1ST_CP_TIME].val&0Xff);	
		p_msg[tx_len++] = (UCHAR8)((sys_param_1b[MADD_D_TD_1ST_CP_TIME].val>>8)&0Xff);	

		p_msg[tx_len++] = (UCHAR8)(MADD_D_TD_2ND_CP_TIME&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_D_TD_2ND_CP_TIME>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_1b[MADD_D_TD_2ND_CP_TIME].val&0Xff);	
		p_msg[tx_len++] = (UCHAR8)((sys_param_1b[MADD_D_TD_2ND_CP_TIME].val>>8)&0Xff);	


		p_msg[tx_len++] = (UCHAR8)(MADD_D_TD_LNA_ON_TIME&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_D_TD_LNA_ON_TIME>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_1b[MADD_D_TD_LNA_ON_TIME].val&0Xff);	
		p_msg[tx_len++] = (UCHAR8)((sys_param_1b[MADD_D_TD_LNA_ON_TIME].val>>8)&0Xff);	

		p_msg[tx_len++] = (UCHAR8)(MADD_D_TD_LNA_OFF_TIME&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_D_TD_LNA_OFF_TIME>>8)&0x00FF);
		p_msg[tx_len++] = 2;
		p_msg[tx_len++] = (UCHAR8)(sys_param_1b[MADD_D_TD_LNA_OFF_TIME].val&0Xff);	
		p_msg[tx_len++] = (UCHAR8)((sys_param_1b[MADD_D_TD_LNA_OFF_TIME].val>>8)&0Xff);	

		p_msg[tx_len++] = (UCHAR8)(MADD_D_TD_TYPE_SELECT&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_D_TD_TYPE_SELECT>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_D_TD_TYPE_SELECT].val;	

		p_msg[tx_len++] = (UCHAR8)(MADD_D_TD_NORMAL_CP&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_D_TD_NORMAL_CP>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_D_TD_NORMAL_CP].val;	

		p_msg[tx_len++] = (UCHAR8)(MADD_D_TD_EXTENDED_CP&0x00FF);	
		p_msg[tx_len++] = (UCHAR8)((MADD_D_TD_EXTENDED_CP>>8)&0x00FF);
		p_msg[tx_len++] = 1;
		p_msg[tx_len++] = sys_param_1b[MADD_D_TD_EXTENDED_CP].val;
#endif 
	TRACE_INFO("---------------Set Re TD Param_end------------\r\n");


		SendMsgPkt(tx_len, p_msg);

	
}

/*************************************************************
Name:SetAttByParam
Description: ���������е�˥����ֵд��FPGA��
Input: void
Output:void         
Return:void
**************************************************************/
void SetAttByParam( UCHAR8 ab_flag )	
{
#if 0
	if ( SYS_A_FLAG==ab_flag )
	{
		// ǰ������˥����1
		if ( sys_param_1b[MADD_A_IN_ATT1].val < 64 )
		{
			FpgaSetAttValue( SYS_A_FLAG, FPGA_AF_ATT1, sys_param_1b[MADD_A_IN_ATT1].val );
		}

		// ǰ������˥����2
		if ( sys_param_1b[MADD_A_IN_ATT2].val < 64 )
		{
			FpgaSetAttValue( SYS_A_FLAG, FPGA_AF_ATT2, sys_param_1b[MADD_A_IN_ATT2].val );
		}

		// ������˥����1
		if ( sys_param_1b[MADD_A_OUT_ATT1].val < 64 )
		{
			FpgaSetAttValue( SYS_A_FLAG, FPGA_AB_ATT1, sys_param_1b[MADD_A_OUT_ATT1].val );
		}
	}
	else if ( SYS_B_FLAG==ab_flag )
	{
		// ǰ������˥����1
		if ( sys_param_1b[MADD_B_IN_ATT1].val < 64 )
		{
			FpgaSetAttValue( SYS_B_FLAG, FPGA_BF_ATT1, sys_param_1b[MADD_B_IN_ATT1].val );
		}

		// ǰ������˥����2
		if ( sys_param_1b[MADD_B_IN_ATT2].val < 64 )
		{
			FpgaSetAttValue( SYS_B_FLAG, FPGA_BF_ATT2, sys_param_1b[MADD_B_IN_ATT2].val );
		}

		// ������˥����1
		if ( sys_param_1b[MADD_B_OUT_ATT1].val < 64 )
		{
			FpgaSetAttValue( SYS_B_FLAG, FPGA_BB_ATT1, sys_param_1b[MADD_B_OUT_ATT1].val );
		}
	}
#endif
}

/*************************************************************
Name: SetChannelByParam
Description: ���ݲ����е�Ƶ���������Ƶ��
Input: void
Output:void         
Return:void
**************************************************************/
void SetChannelByParam( UCHAR8 abcd_flag )	
{
	UINT32 i;
	
//	TRACE_DEBUG("SetChannelByParam,abcd_flag[%04x]\r\n",abcd_flag);
	
	if ( SYS_A_FLAG == abcd_flag )
	{
		for ( i=0; i<sys_param_1b[MADD_A_CHANNEL_COUNT].val; i++ )
		{
			PA_SetChannel(i, sys_param_1b[MADD_A_DCH_EN1+i].val, sys_param_2b[MADD_A_DL_CHANNEL1+i].val);
		} 
	}
	else if ( SYS_C_FLAG==abcd_flag )
	{
		for ( i=0; i<sys_param_1b[MADD_C_CHANNEL_COUNT].val; i++ )
		{
			PC_SetChannel(i, sys_param_1b[MADD_C_DCH_EN1+i].val, sys_param_2b[MADD_C_DL_CHANNEL1+i].val);
		}
	}
	else if ( SYS_D_FLAG==abcd_flag )
	{

		for ( i=0; i<sys_param_1b[MADD_D_CHANNEL_COUNT].val; i++ )
		{
			PD_SetChannel(i, sys_param_1b[MADD_D_DCH_EN1+i].val, sys_param_2b[MADD_D_DL_CHANNEL1+i].val);
		}
	}
	
}

/*************************************************************
Name: GetPsfFromRe
Description: ��RE��ȡѡƵ����ֵ��У׼ʱ��
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
			reg_psf_l = FPGA_REG_RE_A_UPSF_L;		// ����ѡƵͨ�����ʵ�16λ
			reg_psf_h = FPGA_REG_RE_A_UPSF_H;		// ����ѡƵͨ�����ʸ�16λ
		}
		else
		{
			reg_psf_l = FPGA_REG_RE_A_DPSF_L;		// ����ѡƵͨ�����ʵ�16λ
			reg_psf_h = FPGA_REG_RE_A_DPSF_H;		// ����ѡƵͨ�����ʸ�16λ
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
			reg_psf_l = FPGA_REG_RE_B_UPSF_L;		// ����ѡƵͨ�����ʵ�16λ
			reg_psf_h = FPGA_REG_RE_B_UPSF_H;		// ����ѡƵͨ�����ʸ�16λ
		}
		else
		{
			reg_psf_l = FPGA_REG_RE_B_DPSF_L;		// ����ѡƵͨ�����ʵ�16λ
			reg_psf_h = FPGA_REG_RE_B_DPSF_H;		// ����ѡƵͨ�����ʸ�16λ
		}
		#if ( defined(FUNC_FREQ_POINT_SEARCH_EN) && defined(FUNC_FPS_AUTO_SET) && defined(FUNC_FPS_AVG_FP) )	// ����Ƶ�����������Զ�ƽ������Ƶ��
			ch = 8;		// B�������в���ͨ��8У׼
		#endif

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
			reg_psf_l = FPGA_REG_RE_C_UPSF_L;		// ����ѡƵͨ�����ʵ�16λ
			reg_psf_h = FPGA_REG_RE_C_UPSF_H;		// ����ѡƵͨ�����ʸ�16λ
		}
		else
		{
			reg_psf_l = FPGA_REG_RE_C_DPSF_L;		// ����ѡƵͨ�����ʵ�16λ
			reg_psf_h = FPGA_REG_RE_C_DPSF_H;		// ����ѡƵͨ�����ʸ�16λ
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
			reg_psf_l = FPGA_REG_RE_D_UPSF_L;		// ����ѡƵͨ�����ʵ�16λ
			reg_psf_h = FPGA_REG_RE_D_UPSF_H;		// ����ѡƵͨ�����ʸ�16λ
		}
		else
		{
			reg_psf_l = FPGA_REG_RE_D_DPSF_L;		// ����ѡƵͨ�����ʵ�16λ
			reg_psf_h = FPGA_REG_RE_D_DPSF_H;		// ����ѡƵͨ�����ʸ�16λ
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

	// ��ͷ
	msg[MSG_DES_FP] = ADJ_ADDR_AU;	    // ���й��
	msg[MSG_DES_RE] = ADJ_ADDR_EU;					// ��һ��MEU	
	msg[MSG_DES_REE] = ADJ_ADDR_RU;					// ��һ��MRU
	msg[MSG_SRC_FP] = LOCAL_ADD_FP;         //00
	msg[MSG_SRC_RE] = LOCAL_ADD_RE;         //00
	msg[MSG_SRC_REE] = LOCAL_ADD_REE;         //00
	msg[MSG_CMD_ID] = MSG_CMD_GET_FPGA_REG;
	msg[MSG_ACK_FLAG] = MSG_ACK_MASTER_SEND;
	msg[MSG_RESERVE1] = 0xE7;
	msg[MSG_RESERVE2] = 0x11;

	tx_len = MSG_PKT_HEAD_SIZE;
	// �͵�ַ
	msg[tx_len++] = attr|ch;		// ͨ��0
	msg[tx_len++] = attr2;		
	msg[tx_len++] = (UCHAR8)(reg_psf_l&0x0ff);
	msg[tx_len++] = (UCHAR8)((reg_psf_l>>8)&0x0ff);
	msg[tx_len++] = 0;
	msg[tx_len++] = 0;
	// ��16λ��ַ
	msg[tx_len++] = attr|ch;		// ͨ��0
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
Description: ����RE��ID��
Input: 
	fp: ��ں�(0��ʼ)
	re: �ڵ��(0��ʼ)
	id: ID��
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

	// ID�ŵ�ַ
	msg[tx_len++] = (UCHAR8)(MADD_MODULE_HRI_ID&0x00FF);	
	msg[tx_len++] = (UCHAR8)((MADD_MODULE_HRI_ID>>8)&0x00FF);
	// ����
	msg[tx_len++] = 1;
	// ����
	msg[tx_len++] = id;	
	
	msg[tx_len] = 0;	
	msg[tx_len+1] = 0;	

	SendMsgPkt(tx_len, msg);
	
}

void SysLowPowerMode()
{
#ifndef AD9528
	// 9517���˸�FPGA��ʱ����,ȫ��PowerDown
	Ad9524Write( 0xF0, 0x01|Ad9524Read(0xF0) );		// OUT0
	Ad9524Write( 0xF1, 0x01|Ad9524Read(0xF1) );		// OUT1
	Ad9524Write( 0xF4, 0x01|Ad9524Read(0xF4) );		// OUT2
	Ad9524Write( 0xF5, 0x01|Ad9524Read(0xF5) );		// OUT3
	// OUT4, OUT5��ΪSerdes��ʱ�Ӹ�FPGA�ṩ����ʱ��,���ض�
	Ad9524Write( 0x142, 0x01|Ad9524Read(0x142) );		// OUT6
	Ad9524Write( 0x143, 0x01|Ad9524Read(0x143) );		// OUT7
#endif
	// AD-PowerDown, 08�Ĵ���д01-�ڲ���ȫ����
	//Ad6649Write(AD6655_ADD_CHANNEL, 0x03);			// 0x05
	Ad6649Write(0x08, 0x01);  

	// DA-PowerDown, 0��ַ��bit4��1
	Ad9122Write( 0, (1<<4)|Ad9122Read(0, DA_A_FLAG), DA_A_FLAG );		
	Ad9122Write( 0, (1<<4)|Ad9122Read(0, DA_B_FLAG), DA_B_FLAG );		
	
	// 4153-PowerDown, 2��ַ��bit4��1
	//SetADF4153Reg( (1<<4)|GetADF4153Reg(2, MIXER_FRONT, MIXER_A_FLAG), MIXER_FRONT, MIXER_A_FLAG);
	//SetADF4153Reg( (1<<4)|GetADF4153Reg(2, MIXER_BACK, MIXER_A_FLAG), MIXER_BACK, MIXER_A_FLAG);
	//SetADF4153Reg( (1<<4)|GetADF4153Reg(2, MIXER_FRONT, MIXER_B_FLAG), MIXER_FRONT, MIXER_B_FLAG);
	//SetADF4153Reg( (1<<4)|GetADF4153Reg(2, MIXER_BACK, MIXER_B_FLAG), MIXER_BACK, MIXER_B_FLAG);

	// �ر�5.5Vģ���Դ
	DisablePower5V5;

	// ���õ͹���ģʽ��־
	sys_work_info |= SYSTEM_FLAG_LOW_POWER;

}

void SysNormalWorkMode()
{
	sys_work_info &= (~SYSTEM_FLAG_LOW_POWER);
#ifndef AD9528
	// ��ʼ��9517
	Ad9524Write( 0xF0, (~0x01)&Ad9524Read(0xF0) );		// OUT0
	Ad9524Write( 0xF1, (~0x01)&Ad9524Read(0xF1) );		// OUT1
	Ad9524Write( 0xF4, (~0x01)&Ad9524Read(0xF4) );		// OUT2
	Ad9524Write( 0xF5, (~0x01)&Ad9524Read(0xF5) );		// OUT3
	// OUT4, OUT5��ΪSerdes��ʱ�Ӹ�FPGA�ṩ����ʱ��,���ض�
	Ad9524Write( 0x142, (~0x01)&Ad9524Read(0x142) );		// OUT6
	Ad9524Write( 0x143, (~0x01)&Ad9524Read(0x143) );		// OUT7
#endif
	// ��ʼ��4153
	//InitADF4153AF();
	//InitADF4153AB();
	//InitADF4153BF();
	//InitADF4153BB();
		
	// ��ʼ��AD
	Ad6649Write(0x08, 0x00);

	// ��ʼ��DA
	Ad9122Write( 0, (~0x10)&Ad9122Read(0, DA_A_FLAG), DA_A_FLAG );		
	Ad9122Write( 0, (~0x10)&Ad9122Read(0, DA_B_FLAG), DA_B_FLAG );		

	// ��5.5Vģ���Դ
	EnablePower5V5;

}

/*************************************************************
Name:CheckReID          
Params: [reset_fp: 0-����֮ǰ����������0-����������ʼƵ�㣬�����¿�ʼ����]
Return: void
Description: TD�Զ�Ƶ���������ܣ�������TD�޷�ͬ��֮���Զ��л�Ƶ�㣬֪��TD����ͬ��������Ҫ��ÿ�����1��
**************************************************************/
void TdAutoSearchFp( UCHAR8 reset_fp )
{
#ifdef FUNC_TD_AUTO_SEARCH_FP
	static UCHAR8 search_ch = 0;	// td_scdma����ͨ���ţ���1ͨ��Ϊ�������õ�Ƶ�㣬������ǰ9��Ϊ��Ϊ�Ĺ̶�Ƶ�㣬��9��Ϊ��Ϊ�Ĺ̶�Ƶ��:10055��10063��10071��10080��10088��10096��10104��10112��10120,10054,10062,10070,10079,10087,10095,10104,10112,10120

	UINT16 tmp;
	UINT16 cnt;
	UINT16 search_ch_loop;


	tmp = sys_param_2b[MADD_B_DL_CHANNEL1].val; //��ʼƵ��
	tds_dl_channel[0]=tmp;
	TRACE_INFO("Start FrePoint=[%d]\r\n",tmp);
	TRACE_INFO("\r\n");
	cnt = 16; //��ǰ�̶�дȫ��15��Ƶ��
	//TRACE_INFO("FrePonit Count=[%d]\r\n",cnt);
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_TD_MAIN_CH_CNT, (cnt&0x00FF));
	FPGA_DISABLE_WRITE;
	//����Ƶ�������д��FPGA
	for(search_ch=1;search_ch<16;search_ch++)
	{
		if(tds_dl_channel[search_ch]>=tmp)
		{
			break;
		}   
	}
	search_ch_loop = search_ch; //���Ƶ���ƻ�����С��Ҫд��Ƶ�����
         //����Ƶ���ֲ�д��FPGA
	for(;search_ch<16;search_ch++)
	{  
		PB_SetTdMainChannel( sys_param_1b[MADD_B_DCH_EN1].val, tds_dl_channel[search_ch] );
	}
         for(search_ch=0;search_ch<search_ch_loop;search_ch++)
	{  
		PB_SetTdMainChannel( sys_param_1b[MADD_B_DCH_EN1].val, tds_dl_channel[search_ch] );
	}
	//дƵ������ϣ����������(д��Ҳ��)
	FPGA_ENABLE_WRITE;
	FpgaWriteRegister(FPGA_REG_TD_MAIN_CH_END, (cnt&0x0000));
	FPGA_DISABLE_WRITE; 

	if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A) 
	|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
	|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
	|| (version_number == VERSION_50M_IN_F) ||(version_number == VERSION_50M_IN_V4)
	||(version_number == VERSION_50M_IN_V5)
	)
	{
		//c��
		tmp = sys_param_2b[MADD_C_DL_CHANNEL1].val; //��ʼƵ��
		tds_dl_channel[0]=tmp;
		TRACE_INFO("Start FrePoint=[%d]\r\n",tmp);
		TRACE_INFO("\r\n");
		cnt = 16; //��ǰ�̶�дȫ��15��Ƶ��
		//TRACE_INFO("FrePonit Count=[%d]\r\n",cnt);
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_LTE_MAIN_CH_CNT, (cnt&0x00FF));
		FPGA_DISABLE_WRITE;
		//����Ƶ�������д��FPGA
		for(search_ch=1;search_ch<16;search_ch++)
		{
			if(tds_dl_channel[search_ch]>=tmp)
			{
				break;
			}   
		}
		search_ch_loop = search_ch; //���Ƶ���ƻ�����С��Ҫд��Ƶ�����
		//����Ƶ���ֲ�д��FPGA
		for(;search_ch<16;search_ch++)
		{  
			PC_SetTdMainChannel( sys_param_1b[MADD_C_DCH_EN1].val, tds_dl_channel[search_ch] );
		}
		for(search_ch=0;search_ch<search_ch_loop;search_ch++)
		{  
			PC_SetTdMainChannel( sys_param_1b[MADD_C_DCH_EN1].val, tds_dl_channel[search_ch] );
		}
		//дƵ������ϣ����������(д��Ҳ��)
		FPGA_ENABLE_WRITE;
		FpgaWriteRegister(FPGA_REG_LTE_MAIN_CH_END, (cnt&0x0000));
		FPGA_DISABLE_WRITE; 
	}
#ifdef 0
			tmp = tds_dl_channel[search_ch];
			search_ch++;
			TRACE_INFO("tmp=[%d],search_ch=[%d]\r\n",tmp,search_ch);
			PB_SetTdMainChannel( sys_param_1b[MADD_B_DCH_EN1].val, tmp );	
			sys_param_2b[MADD_B_DL_CHANNEL1].val=tmp;
			tm_search_wait = 0;
			tm_check_wait = 0;	// ����ȴ�ʱ��
		}
		else // ֮ǰ����ͬ��״̬
		{
			tmp = FpgaReadRegister( FPGA_REG_TD_SYNC_ST ) & BM_TD_SYNC_OK;		// ��ȡͬ��״̬
			TRACE_INFO("1tmp{0/1}=[%x],tm_check_wait=[%x]\r\n",tmp,tm_check_wait);
			if ( 0==tmp )	// ��⵽��ͬ��
			{
				if ( 0==tm_check_wait )	// ���μ�⵽��ͬ�����ȴ�15��
				{
					tm_check_wait = 1;
				}
			}

			if ( tm_check_wait>0 )	// ��ʱ�ȴ�
			{
				tm_check_wait++;
				if ( tm_check_wait>=15 )	// 15��ʱ���ж�ͬ��״̬
				{
					if ( 0==tmp )
					{
						pre_sync_st = 0;		// ״̬��Ϊδͬ��
						tm_search_wait = 0;	// ���������ȴ�ʱ��
					}
					tm_check_wait = 0;	// ����ȴ�ʱ��
				}
			}
		}
	}
#endif
#endif
}
/*************************************************************
Name: TempGainCompensate
Params: [force_set: ǿ�Ƹ��ݵ�ǰ�¶ȸ��²���ֵ, 1��Ч]
Return: void
Description: ִ���¶Ȳ�������(�����¶ȱ仯������Ӧ3���ӵ���һ��)
**************************************************************/
void TempGainCompensate( UCHAR8 force_set )
{
	static CHAR8 temp_old = 25;	// ǰһ�ε��¶�ֵ
	static CHAR8 comp_id = -1;	// �������±�
	CHAR8 temp_now;
	CHAR8 seg, index;

	// ��ȡ��ǰ�¶�
	temp_now = (CHAR8)sys_param_1b[MADD_BOARD_TEMP].val;
	//temp_now=-11;
	// ǰ�������¶�һ��
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
			// ����A���¶Ȳ���
			FpgaSetTempComp( 0, 0, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_aul[index]/1000.0) );
			FpgaSetTempComp( 0, 1, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_adl[index]/1000.0) );

			// ����B���¶Ȳ���
			FpgaSetTempComp( 1, 0, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_bul[index]/1000.0) );
			FpgaSetTempComp( 1, 1, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_bdl[index]/1000.0) );

			// ����C���¶Ȳ���
			FpgaSetTempComp( 2, 0, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_cul[index]/1000.0) );
			FpgaSetTempComp( 2, 1, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_cdl[index]/1000.0) );

			// ����D���¶Ȳ���
			FpgaSetTempComp( 3, 0, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_dul[index]/1000.0) );
			FpgaSetTempComp( 3, 1, (UINT16)CALC_FTCOMP(0-(INT16)temp_cmp_tbl_ddl[index]/1000.0) );		}
	}

	// ���汾���¶�
	temp_old = temp_now;

}
/*************************************************************
Name: NoiseTest          
Description: ������Թ�����
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
			//����MCU����ģʽ
			//ReadWriteTF(noise_test_st.type,1,0x077,tmp1|0X40);
			//ReadWriteTF(noise_test_st.type,1,0x07c,tmp2|0X40);
			//0x73 0x75д1
			if(noise_test_st.type == SYS_C_FLAG)
			{
				//printf("C data = %d\r\n",noise_test_st.value);
				ReadWriteTF(TF_D,1,0x0073,0);
				ReadWriteTF(TF_C,1,0x0075,(UCHAR8)(noise_test_st.value*4));
				ReadWriteTF(TF_B,1,0x0073,0);				
				
				//printf("c--����0x75\r\n");
			}
			else if(noise_test_st.type == SYS_D_FLAG)
			{
				ReadWriteTF(TF_C,1,0x0075,0);
				//printf("D data = %d\r\n",noise_test_st.value);
				ReadWriteTF(TF_D,1,0x0073,(UCHAR8)(noise_test_st.value*4));
				ReadWriteTF(TF_B,1,0x0073,0);				
				//printf("d--����0x73\r\n");
			}
			else if(noise_test_st.type == SYS_B_FLAG)
			{
				//printf("B data = %d\r\n",noise_test_st.value);
				ReadWriteTF(TF_C,1,0x0075,0);
				ReadWriteTF(TF_D,1,0x0073,0);
				ReadWriteTF(TF_B,1,0x0073,(UCHAR8)(noise_test_st.value*4));
				//printf("����B--0x73\r\n");
				//printf("����B--0x73--9363_0x17_0 = %02x,\r\n",ReadWriteTF(TF_B,0,0x0017,0) );
				
			}
			//ִ�б���й¶У׼����
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

				//�˳�MCU����ģʽ
				//ReadWriteTF(TF_C,1,0x077,tmp1|0X40);
				//ReadWriteTF(TF_C,1,0x07c,tmp2|0X40);
				//0x73 0x75д0
				//if(noise_test_st.type == SYS_C_FLAG)
				ReadWriteTF(TF_B,1,0x0073,0);
				WTD_CLR;
				UsNopDelay(1000);				
				//else if(noise_test_st.type == SYS_D_FLAG)
				ReadWriteTF(TF_B,1,0x0075,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//ִ�б���й¶У׼����			
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
				//�˳�MCU����ģʽ
				//ReadWriteTF(TF_C,1,0x077,tmp1|0X40);
				//ReadWriteTF(TF_C,1,0x07c,tmp2|0X40);
				//0x73 0x75д0
				//if(noise_test_st.type == SYS_C_FLAG)
				ReadWriteTF(TF_C,1,0x0073,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//else if(noise_test_st.type == SYS_D_FLAG)
				ReadWriteTF(TF_C,1,0x0075,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//ִ�б���й¶У׼����
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
				//�˳�MCU����ģʽ
				//ReadWriteTF(TF_C,1,0x077,tmp1|0X40);
				//ReadWriteTF(TF_C,1,0x07c,tmp2|0X40);
				//0x73 0x75д0
				//if(noise_test_st.type == SYS_C_FLAG)
				ReadWriteTF(TF_B,1,0x0073,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//else if(noise_test_st.type == SYS_D_FLAG)
				ReadWriteTF(TF_B,1,0x0075,0);
				WTD_CLR;
				UsNopDelay(1000);				
				
				//ִ�б���й¶У׼����
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
				//�˳�MCU����ģʽ
				//ReadWriteTF(TF_C,1,0x077,tmp1|0X40);
				//ReadWriteTF(TF_C,1,0x07c,tmp2|0X40);
				//0x73 0x75д0
				//if(noise_test_st.type == SYS_C_FLAG)
				ReadWriteTF(TF_C,1,0x0073,0);
				WTD_CLR;
				UsNopDelay(1000);
				//else if(noise_test_st.type == SYS_D_FLAG)
				ReadWriteTF(TF_C,1,0x0075,0);
				WTD_CLR;
				UsNopDelay(1000);
				//ִ�б���й¶У׼����
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
Description: �·���������չ��
Input: void
Return: void
**************************************************************/
void MAUSetParamToMEU(void)
{
	if ( (0 !=	( sys_work_info & SYSTEM_FLAG_SET_RE_UPOW))
		||( 0 !=	(sys_work_info & SYSTEM_FLAG_SET_RE_SYS_CFG) ) )
	{
		// ����RE����������ܹ���(��ֵ�ɽ�����)
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_UPOW);
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_SYS_CFG);
		WTD_CLR; 
		//SetReUlPowerGain();
		// REC��˫���������õ��������ݰ����ͣ�����ɰ�RE����ʶ�𣬵�����������Ҳ����ʧ��
		//SetReDpxInfo();

	}
	
	if ( 0 !=	(sys_work_info & SYSTEM_FLAG_SET_RE_SYS_CFG) )
	{
		WTD_CLR; 
		// ��Ҫˢ��RE����ʱģʽ
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_SYS_CFG);
		//SetReSysConfig();
		//SetReBwConfig();

	}

	if ( 0!= (sys_work_info & SYSTEM_FLAG_SET_RE_TDSLOT ) )
	{
		WTD_CLR; 
		// ����RE��TDʱ϶
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_TDSLOT);
		//SetReTDParam();
	}

	if ( 0!= (sys_work_info & SYSTEM_FLAG_SET_RE_SFC ) )
	{
		WTD_CLR; 
		// ����RE��Ƶ������
		sys_work_info &= ( ~SYSTEM_FLAG_SET_RE_SFC );
		SysBroadcastReFcA();   
	}

}
/*************************************************************
Name: SetAdjBenZhenSignalPara
Params: 
Return: void
Description: ���ñ���У׼����
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
Description: �Զ�ʱ϶���
**************************************************************/
void ZiDongShiXiPeiBi( void)
{	
	UINT16 tmp=0,tmp2=0,tmp3=0;
//��ȡ�Զ�ʱ϶���

	if( (version_number == VERSION_50M_IN_F)||(version_number == VERSION_50M_IN_V4)||(version_number == VERSION_50M_IN_V5))
	{
		if(sys_param_1b[MADD_SLOT_TIME_EN_C].val==1)//����TDSʱ϶����Զ����
		{
			//ʹ���Զ�ʱ϶��⹦��
			FpgaWriteRegister( FPGA_REG_W_SLOT_TIME_C, 1<<15 );

			//��ȡ�Զ�ʱ϶���
			sys_param_1b[MADD_SLOT_TIME_DISTRI_C].val; 
			tmp = (UCHAR8)FpgaReadRegister(FPGA_REG_R_SLOT_TIME_C);
			tmp2= tmp&0x0f;//������֡���
			tmp3 = (tmp&0xf0)>>4;//������ʱ϶���
			//tmp2 =  (sys_param_1b[MADD_C_TD_NORMAL_CP].val)| ((sys_param_1b[MADD_C_TD_TYPE_SELECT].val<<3)&0X78)|((sys_param_1b[MADD_C_TD_EXTENDED_CP].val<<7)&0X80);
			//��ȡ��ȳɹ�
			//��ԭ�е���ȱȽ�
			if((tmp2 != sys_param_1b[MADD_C_TD_NORMAL_CP].val)||(tmp3 != sys_param_1b[MADD_C_TD_TYPE_SELECT].val))
			{
				sys_param_1b[MADD_C_TD_NORMAL_CP].val = tmp2;
				sys_param_1b[MADD_C_TD_TYPE_SELECT].val = tmp3;
				tmp = (sys_param_1b[MADD_C_TD_TYPE_SELECT].val&0X07)| ((sys_param_1b[MADD_C_TD_NORMAL_CP].val<<3)&0X78)|((sys_param_1b[MADD_C_TD_EXTENDED_CP].val<<7)&0X80);

				//д��ʱ϶��ȼĴ���	
				FPGA_ENABLE_WRITE;
				FpgaWriteRegister(FPGA_REC_C_TS_CONFIG, tmp);
				FPGA_DISABLE_WRITE;

				sys_work_info |= SYSTEM_FLAG_SET_RE_TDSLOT;

			}
		}

	}
	
}
/*************************************************************
Name: MoveBenZhenTo2345
Params: 
Return: void
Description: ���������ƶ�����(���ڲ���)
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
//		printf("��ʱ��%d\r\n",time_tick);
		if(time_tick >= 10)
		{
			time_tick = 0;
			time_start = 0;
		}
		else
			return;
	}
		
	
	//ͬ��
	 if(FpgaReadRegister(FPGA_REG_C_TD_SYNC_ST)&0x04) 
	 {
	 	//Ƶƫ5M
	 	fre = FpgaReadRegister(FPGA_REG_C_LTE_CUR_FREQ_L)|(FpgaReadRegister(FPGA_REG_C_LTE_CUR_FREQ_H)<<12);
//		printf("Ƶƫ%X\r\n",fre);
		fre_f = (FLOAT32)(fre/( 8192*1024*8*1/62.5));
//		printf("ƵƫF%f\r\n",fre_f);

		if((fre_f > 4)&&(fre_f < 6 ))
		{
			//�ƶ�������2340 (Ĭ��Ϊ2345)
			benzhen2340 = 1;
			if(state == 0)
				state= 1;
			//������ʱ 10��
			time_start = 1;
//			printf("ͬ��С��5M\r\n");
			change2340 = 1;
		}
		else if((fre_f > 9)&&(fre_f < 11 ))
		{
			if(change2340 == 1)
			{
//				printf("����r\n");
			}
			else
			{
//				printf("ͬ��>��5M\r\n");
				benzhen2340 = 0;
				if(state == 2)
					state = 3;
				change2340 = 0;
			}
				
		}
		else 
		{
//			printf("ͬ��>��5M\r\n");
			benzhen2340 = 0;
			if(state == 2)
				state = 3;
			change2340 = 0;
		}
	 }
	 else
	 {
//	 		printf("ʧ��\r\n");
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
//	 		printf("��������ִ��\r\n");
	 		module_param_chg_flag |= PCHG_C_CHANNEL;
			module_param_chg_flag |= PCHG_D_CHANNEL;
			MAUSetParamToMRU();
	 }
}

/*************************************************************
Name: MAUSetParamToMEU          
Description: �·���������չ��
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
Description: �·���������չ��
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
Description: �·���������չ��
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
Description: ��ȡEU����
Input: void
Return: void
**************************************************************/
void GainAdjGetEUPow(UCHAR8 ab_flag, UCHAR8 ud_flag)
{

	UCHAR8 * p_msg = sys_temp_buff;
	UINT32 tx_len;
	UINT16 tmp;
	UINT32 i;
		
	p_msg[MSG_DES_FP] = 1;//��һ������µ�EU
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
Description:��չ��Ԫ�㲥������Ƶ����
Input:base_flag:
Output:void         
Return:void
**************************************************************/
//void ReeBroadcastToSetRe(UCHAR8 485_usb_flag, UCHAR8 rf,UCHAR8 *P_tx_buff )
void MAUBroadcastToMEU(UCHAR8 uart_usb_flag,UCHAR8 des_eu,UCHAR8 *p_tx_buff ,UINT msg_tx_length,UCHAR8 msg_cmd_id)
{
	//Ŀ�ĵ�ַ
	p_tx_buff[MSG_DES_FP] = des_eu;  
	p_tx_buff[MSG_DES_RE] = BROADCAST_ADD_RE;   
	p_tx_buff[MSG_DES_REE] = 0; 
	
	// Դ��ַ  
	p_tx_buff[MSG_SRC_FP] = LOCAL_ADD_FP;
	p_tx_buff[MSG_SRC_RE] = LOCAL_ADD_RE; 
	p_tx_buff[MSG_SRC_REE] = LOCAL_ADD_REE;

	// Ӧ����ı����ֶ�
	p_tx_buff[MSG_RESERVE1] = 0;
	p_tx_buff[MSG_RESERVE2] = uart_usb_flag;
	// Ӧ�����������
	p_tx_buff[MSG_CMD_ID] = msg_cmd_id ;
	p_tx_buff[MSG_ACK_FLAG]=MSG_ACK_MASTER_SEND;

	SendMsgPkt( msg_tx_length, p_tx_buff );
	
}


/*************************************************************
Name: MAUSetParamToMEU          
Description: �·���������չ��
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


	#if 0
	if ( (0 !=	( sys_work_info & SYSTEM_FLAG_SET_RE_UPOW))
		||( 0 !=	(sys_work_info & SYSTEM_FLAG_SET_RE_SYS_CFG) ) )
	{
		// ����RE����������ܹ���(��ֵ�ɽ�����)
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_UPOW);
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_SYS_CFG);
		WTD_CLR; 
		//SetReUlPowerGain();
		// REC��˫���������õ��������ݰ����ͣ�����ɰ�RE����ʶ�𣬵�����������Ҳ����ʧ��
		//SetReDpxInfo();

	}
	#endif
	if ( 0 !=	(sys_work_info & SYSTEM_FLAG_SET_RE_SYS_CFG) )
	{
		WTD_CLR; 
		// ��Ҫˢ��RE����ʱģʽ
		sys_work_info &= (~SYSTEM_FLAG_SET_RE_SYS_CFG);
		//SetReSysConfig();
		//SetReBwConfig();

	}

	
	
	au_send_msg |= AU_MSG_FLAG_GET_EU_PARA;

	if ( 0 !=	(au_send_msg & AU_MSG_FLAG_GET_EU_PARA) )
	{
		au_send_msg &= (~AU_MSG_FLAG_GET_EU_PARA);
		printf("au_send_msg TO EU:%x\r\n",au_send_msg);
		MauGetMeuAlarm();
	}

}


/*************************************************************
Name:ReeDetectReST          
Description: ree��ȡre״̬
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


#if 0
	for(i=0;i<REE_MAX;i++)
	{
		sys_param_ree_1b[MADD_REE_DETECT_RF_TEMP1+i].val=0;
		sys_param_ree_1b[MADD_A_REE_DETECT_RF_POW_SWR1+i].val=0;
		sys_param_ree_1b[MADD_B_REE_DETECT_RF_POW_SWR1+i].val=0;				
		sys_param_ree_1b[MADD_C_REE_DETECT_RF_POW_SWR1+i].val=0;
		sys_param_ree_1b[MADD_D_REE_DETECT_RF_POW_SWR1+i].val=0;
		
		sys_param_ree_2b[MADD_A_REE_DETECT_RF_DL_OUT_TOTAL_POW1+i].val=0;
		sys_param_ree_2b[MADD_B_REE_DETECT_RF_DL_OUT_TOTAL_POW1+i].val=0;
		sys_param_ree_2b[MADD_C_REE_DETECT_RF_DL_OUT_TOTAL_POW1+i].val=0;
		sys_param_ree_2b[MADD_D_REE_DETECT_RF_DL_OUT_TOTAL_POW1+i].val=0;
		
		sys_param_ree_2b[MADD_A_REE_DETECT_RF_UL_INPUT_TOTAL_POW1+i].val=0;
		sys_param_ree_2b[MADD_B_REE_DETECT_RF_UL_INPUT_TOTAL_POW1+i].val=0;
		sys_param_ree_2b[MADD_C_REE_DETECT_RF_UL_INPUT_TOTAL_POW1+i].val=0;
		sys_param_ree_2b[MADD_D_REE_DETECT_RF_UL_INPUT_TOTAL_POW1+i].val=0;
		
		sys_param_ree_2b[MADD_A_REE_DETECT_RF_ALARM_ST1+i].val=0;
		sys_param_ree_2b[MADD_B_REE_DETECT_RF_ALARM_ST1+i].val=0;
		sys_param_ree_2b[MADD_C_REE_DETECT_RF_ALARM_ST1+i].val=0;
		sys_param_ree_2b[MADD_D_REE_DETECT_RF_ALARM_ST1+i].val=0;
		
		sys_param_ree_1b[MADD_RE_CIRCUIT_ALARM1+i].val=0;
		sys_param_ree_1b[MADD_RE_WLAN_CONN_ST1+i].val=0;

		sys_param_ree_1b[MADD_A_REE_ERL_JG1+i].val = 0;
		sys_param_ree_1b[MADD_C_REE_ERL_JG1+i].val = 0;
		sys_param_ree_1b[MADD_D_REE_ERL_JG1+i].val = 0;

	}	
#endif


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
	//printf("����");
//	TRACE_INFO(" ReeBroadcastToSetRe---2 \r\n"); 		
	//for(i=0;i<msg_tx_len;i++)
	//{

	//	TRACE_INFO_WP("%x ",sys_temp_buff[i]); 	
	//printf("%x ",sys_temp_buff[i]); 
	//}
	//TRACE_INFO(" \r\n"); 		

#if 0
		for( i=0; i<REE_MAX; i++)
		{		tx_len = MSG_PKT_HEAD_SIZE;
				tmp = MADD_C_DCH_EN1;
				p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
				p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
				p_msg[tx_len++] = 1;
				p_msg[tx_len++] = (UCHAR8)(sys_param_ree_1b[MADD_C_RF_CHANNEL1_EN1+i].val&0xFF);	
					
				
				tmp = MADD_C_DCH_EN2;
				p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
				p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
				p_msg[tx_len++] = 1;
				p_msg[tx_len++] = sys_param_ree_1b[MADD_C_RF_CHANNEL2_EN1+i].val;	

				tmp = MADD_D_DCH_EN1;
				p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
				p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
				p_msg[tx_len++] = 1;
				p_msg[tx_len++] = (UCHAR8)(sys_param_ree_1b[MADD_D_RF_CHANNEL1_EN1+i].val&0xFF);						

				tmp = MADD_D_DCH_EN2;
				p_msg[tx_len++] = (UCHAR8)(tmp&0x00FF);	
				p_msg[tx_len++] = (UCHAR8)((tmp>>8)&0x00FF);
				p_msg[tx_len++] = 1;
				p_msg[tx_len++] = sys_param_ree_1b[MADD_D_RF_CHANNEL2_EN1+i].val;
				
				MAUBroadcastToMEU( 0,i+1,sys_temp_buff ,msg_tx_len,MSG_CMD_SET_PARAM);	
				
		}
#endif
		if(eu_port>FP_MAX)
			eu_port = 1;

		//printf("eu_port:%d\r\n",eu_port);
		MAUBroadcastToMEU( 0,eu_port++,sys_temp_buff ,msg_tx_len,MSG_CMD_GET_PARAM);	

		
		
}


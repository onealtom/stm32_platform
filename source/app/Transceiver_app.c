/***************************************************************
*Shenzhen Grandtelco Technology Co.,Ltd All rights reserved
*
* FileName    :Transceiver_app.c
* Description :收发器芯片处理函数
* Version     :v0.1
* Author      :shiyang
* Date        :2012-06-01
*
* History     :
*
* <author>    <time>    	<version>    <desc>
*shiyang		2008-01-29	v0.1			初始版本
**************************************************************/
#include "Header.h"

//SYSTEM_INIT_DATA_T a_init_data;
//SYSTEM_INIT_DATA_T b_init_data;
SYSTEM_INIT_DATA_T c_init_data;
UCHAR8 sys_rece_buf[RECE_MAX];


//UCHAR8 9363_update_data_mau_a[CMD_UPDATA_DATA_LEN];
//UCHAR8 9363_update_data_mau_b[CMD_UPDATA_DATA_LEN];
//UCHAR8 9363_update_data_mau_c[CMD_UPDATA_DATA_LEN];
//extern UINT16 fpga_write_bak[FPGA_W_REG_MAX];

/*************************************************************
Name:CmdHandleSpiWrite
Description:收发器芯片命令处理
Input:片选，地址，数据
Output:void         
Return:0:失败，1，成功   
**************************************************************/
UCHAR8 CmdHandleSpiWrite(UCHAR8 npcs,UINT16 addr,UCHAR8 data)
{
	UCHAR8 read_back;
	
	ReadWriteTF(npcs,1,addr,data);	

	read_back = ReadWriteTF(npcs,0,addr,0);

	if (data == read_back)
	{
		if((1)&&(TF_C==npcs))				
		{
//			TRACE_DEBUG("ok__________9363_write--read_back[%02x],addr=[%x],data=[%x]\r\n",read_back,addr,data);
						
		}		
		return CMD_RESULT_OK;
	}	
	else
	{
		if((1)&&(TF_C==npcs))				
		{
//			TRACE_DEBUG("error__________9363_write--read_back[%02x],addr=[%x],data=[%x]\r\n",read_back,addr,data);
						
		}		
		return CMD_RESULT_FAIL;
	}
}
/*************************************************************
Name:CmdHandleWait
Description:收发器芯片命令处理
Input:等待时间ms
Output:void         
Return:0:失败，1，成功   
**************************************************************/
UCHAR8 CmdHandleWait(UINT16 time_ms)
{
	UINT16 i;

	for (i=0; i<time_ms; i++)
	{
		UsNopDelay(1000);
		WTD_CLR;
	}	
	return CMD_RESULT_OK;
}
/*************************************************************
Name:CmdHandleWaitCaldone
Description:收发器芯片命令处理
Input:片选，子命令，超时时间ms
Output:void         
Return:0:失败，1，成功   
**************************************************************/
UCHAR8 CmdHandleWaitCaldone(UCHAR8 npcs,UCHAR8 cld_id,UINT16 time_out)
{
	UINT16 i;
	UINT16 addr;
	UCHAR8 bit_mask,bit_result,read;

	switch(cld_id)
	{
		case BBPLL:
			addr = BBPLL_REG;
			bit_mask = BBPLL_BIT;
			bit_result = BBPLL_DONE;		
		break;
		case RXCP:
			addr = RXCP_REG;
			bit_mask = RXCP_BIT;
			bit_result = RXCP_DONE;		
		break;
		case TXCP:
			addr = TXCP_REG;
			bit_mask = TXCP_BIT;
			bit_result = TXCP_DONE;		
		break;		
		case RXFILTER:
			addr = RXFILTER_REG;
			bit_mask = RXFILTER_BIT;
			bit_result = RXFILTER_DONE;		
		break;
		case TXFILTER:
			addr = TXFILTER_REG;
			if((AD9369)&&(TF_C==npcs)	)
			{
				bit_mask = TXFILTER_9369_BIT;
			}
			else
			{
				bit_mask = TXFILTER_BIT;
			}
			bit_result = TXFILTER_DONE;		
		break;
		case BBDC:
			addr = BBDC_REG;
			bit_mask = BBDC_BIT;
			bit_result = BBDC_DONE;		
		break;		
		case RFDC:
			addr = RFDC_REG;
			bit_mask = RFDC_BIT;
			bit_result = RFDC_DONE;		
		break;		
		case TXQUAD:
			addr = TXQUAD_REG;
			bit_mask = TXQUAD_BIT;
			bit_result = TXQUAD_DONE;		
		break;	
		case RXTIA:
			addr = RXTIA_REG;
			bit_mask = RXTIA_BIT;
			bit_result = RXTIA_DONE;		
		break;	
		case MailboxBusy:
			addr = MailboxBusy_REG;
			bit_mask = MailboxBusy_BIT;
			bit_result = MailboxBusy_DONE;		
		break;
		case ADCPROFILE:
			addr = ADCPROFILE_REG;
			bit_mask = ADCPROFILE_BIT;
			bit_result = ADCPROFILE_DONE;		
		break;
		case ADCTuner:
			addr = ADCTuner_REG;
			bit_mask = ADCTuner_BIT;
			bit_result = ADCTuner_DONE;	
		break;
		case RFPLLLOCK:
			addr = RFPLLLOCK_REG;
			bit_mask = RFPLLLOCK_BIT;
			bit_result = RFPLLLOCK_DONE;	
		break;
		case RFPLLCP:
			addr = RFPLLCP_REG;
			bit_mask = RFPLLCP_BIT;
			bit_result = RFPLLCP_DONE;	
		break;
		case RCAL:
			addr = RCAL_REG;
			bit_mask = RCAL_BIT;
			bit_result = RCAL_DONE;	
		break;
		case CLKPLLLOCK:
			addr = CLKPLLLOCK_REG;
			bit_mask = CLKPLLLOCK_BIT;
			bit_result = CLKPLLLOCK_DONE;	
		break;
		default:
			return CMD_RESULT_IGNORE;
		break;
	}

	//wait
	for (i=0; i<time_out; i++)
	{		
		read = ReadWriteTF(npcs,0,addr,0);	
		if(TF_A==npcs)
			//TRACE_DEBUG("__________error9363_CmdHandleWaitCaldone--read=[%x],addr=[%x],i=%d\r\n",read,addr,i);
		;
		if (((read>>bit_mask)&0x01) == bit_result)
			return CMD_RESULT_OK;
		
		WTD_CLR;
		UsNopDelay(2000);
				
	}

	return CMD_RESULT_TIMEOUT;
	
}
/*************************************************************
Name:SaveInitData
Description:保存初始化序列到FLASH
Input:
Output:void         
Return:0:失败，1，成功   
**************************************************************/
UCHAR8 SaveInitData(UCHAR8 npcs,UINT16 current_p, UCHAR8  total_p,UCHAR8 * p_data,UINT16 len)
{
	UINT16 block,page,mcuFpgaSpiStaus;
	UCHAR8 * p_init;
	SYSTEM_INIT_DATA_T * p_init_data;
	UINT32 wr_len,write_byte=0,i;
	UCHAR8 *p_buf=sys_temp_buff;
	TRACE_INFO("SaveInitData.......................\r\n");
	if(TF_A==npcs)
	{
		page = FLASH_A_TS_PAGE_START+1;
		//block = FLASH_A_TS_BLOCK;
		p_init_data =&c_init_data;
	}
	else if(TF_B==npcs)
	{
		page = FLASH_B_TS_PAGE_START+1;
		//block = FLASH_B_TS_BLOCK;
		p_init_data =&c_init_data;
	}
	else if(TF_C==npcs)
	{
		page = FLASH_C_TS_PAGE_START+1;
		//block = FLASH_C_TS_BLOCK;
		p_init_data =&c_init_data;
	}

	
	if (current_p == 0)
	{	
		//第一笔数据
		p_init_data->init_flag = 0xEB90|npcs;
		p_init_data->a_packet = 0;	
	}

	
	if (len>UPDATE_PKT_MAX_LEN)
	{
		TRACE_DEBUG("len[%d],flash_page_size[%d]\r\n",len,UPDATE_PKT_MAX_LEN);
		return 0;		
	}

	
	page += current_p*( (UPDATE_PKT_MAX_LEN+FLASH_PAGE_SIZE-1)/FLASH_PAGE_SIZE );
	p_init_data->packet_len[current_p] = len;//包是从1开始的
	p_init_data->a_packet++;

#if 0
	for(i=0;i<(current_p);i++)
	{
		page +=(p_init_data->packet_len[i]+FLASH_PAGE_SIZE-1)/FLASH_PAGE_SIZE;
	}
	p_init_data->packet_len[current_p] = len;//包是从1开始的
	p_init_data->a_packet++;
#endif
	
	//TRACE_INFO("current_p===[%d],page=0x%x, len=%d...p_init_data->a_packet=%d.\r\n\r\n",current_p,page,len,p_init_data->a_packet);
	while ( len )
	{	
		wr_len = (len>FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : len;
		FlashWrite( page,0, p_data, wr_len,1);	// 写入数据

		page++;
		p_data+= wr_len;		// 指针后移
		len -= wr_len;		// 计算剩余长度						
	}

	//最后一笔数据，写入标志和长度
	if((current_p + 1 ) == total_p)
	//if(cmd_cnt<250)
	{
		//TRACE_INFO("last---cmd_cnt=%d\r\n",cmd_cnt);
		if(TF_A==npcs)
		{
			page = FLASH_A_TS_PAGE_START;
		}
		else if(TF_B==npcs)
		{
			page = FLASH_B_TS_PAGE_START;
		}
		else if(TF_C==npcs)
		{
			page = FLASH_C_TS_PAGE_START;
		}
#if 0
     
		FlashDisableWriteProtect();					//去除写保护
		FlashWriteOnepage(page,(UCHAR8 *)p_init_data,sizeof(SYSTEM_INIT_DATA_T),1);
		FlashEnableWriteProtect();

#else
		//TRACE_INFO("p_init_data.init_flag=%x,p_init_data->a_packet:%d\r\n",p_init_data->init_flag,p_init_data->a_packet);

		
		len= sizeof(SYSTEM_INIT_DATA_T)	 ;
		
		p_init=(UCHAR8 *)p_init_data;
		//TRACE_INFO("len:%d\r\n",len);
		
		FlashEraseSectors(page/16,page/16);
		while ( len )
		{	

			wr_len = (len>FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : len;
			FlashWrite( page,0,p_init, wr_len,1);	// 写入数据

			page++;
			p_init += wr_len;		// 指针后移
			len -= wr_len;		// 计算剩余长度						
		}
		//FlashWriteWithinpage( page,0, (UCHAR8 *)p_init_data, sizeof(SYSTEM_INIT_DATA_T),1);	// 写入数据



#if 1
		page = FLASH_A_TS_PAGE_START+1;
		len= sizeof(SYSTEM_INIT_DATA_T);
	    //TRACE_INFO("sizeof(SYSTEM_INIT_DATA_T)=%d\r\n",len);

		p_init = (UCHAR8 *)p_init_data;
		while ( len )
		{
			//FlashRead(flag_page, 0, data ,FLASH_PAGE_SIZE);
			wr_len = (len>FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : len;
			//FlashRead(page, 0, p_buf ,FLASH_PAGE_SIZE);
			
			FlashRead(page, 0, p_init ,FLASH_PAGE_SIZE);

			page++;
			p_init+=  wr_len;	
			len -= wr_len;		// 计算剩余长度	
		}
	
		p_init = (UCHAR8 *)p_init_data;


		if (p_init_data->init_flag != (0xEB90|npcs))
		{
			TRACE_DEBUG("error_________>>>>[%04x]\r\n",p_init_data->init_flag);	
		}
#endif
		
#endif

	
		
	}

	return 1;
}

/*************************************************************
Name:SaveInitData
Description:获取配置版本更新时间
Input:
Output:void         
Return:0:失败，1，成功   
**************************************************************/
UCHAR8 GetUpdateData(UCHAR8 npcs,UCHAR8 * p_data,UCHAR8 *len)
{
	UINT16 block,page;
	UCHAR8 * p_init_data,length;
	

	*len=0;
	length=0;
	if(TF_A==npcs)
	{
		//page = FLASH_A_TS_PAGE_START;
		//block = FLASH_A_TS_BLOCK;
		p_init_data =str_a_pri_9363_date;
	}
	else if(TF_B==npcs)
	{
		//page = FLASH_B_TS_PAGE_START;
		//block = FLASH_B_TS_BLOCK;
		p_init_data =str_b_pri_9363_date;
	}
	else if(TF_C==npcs)
	{
		//page = FLASH_C_TS_PAGE_START;
		//block = FLASH_C_TS_BLOCK;
		p_init_data =str_c_pri_9363_date;
	}
	
	while( '#'!= (*(p_data+length))  )
	{
		if(length>CMD_UPDATA_DATA_LEN)
		{
			return 1;
		}
		*p_init_data++= *(p_data+length);
		//TRACE_INFO("##################9363_p_init_data=[%c]\r\n",(UCHAR8)*(p_init_data-1));
		length++;		
	}
	if(length++<CMD_UPDATA_DATA_LEN)
	{
		*p_init_data++= '#';
	}
	for(;length<CMD_UPDATA_DATA_LEN;length++)
	{
		*p_init_data++= ' ';
	}
//	*len=length;
	*len=CMD_UPDATA_DATA_LEN;
	
	return 0;
}


/*************************************************************
Name:InitTransceiver
Description:从FLASH中获取初始化序列，并初始化收发器
Input:A,B
Output:void         
Return:<0 错误，0:成功
**************************************************************/
CHAR8 InitTransceiver(UCHAR8 abcd)
{
	UINT16 block,page,flag_page;
	SYSTEM_INIT_DATA_T * p_init_data;
	UCHAR8 * data = sys_temp_buff;
	UINT16 cmd_cnt,packet,i,len,j,k,mcuFpgaSpiStaus;
	UCHAR8 cmd,cmd_result,length;
	UINT16 count=0;
	UINT32 wr_len;
	UCHAR8 * p_init;
	UINT32 ReadByteOneLoop,ReadNums;
	UCHAR8 npcs;
	

	if ( FPGA_LDST_OK != fpga_load_status )
	{
		return NULL;		
	}

	if(SYS_A_FLAG==abcd)
	{
		if ( fpga_cfg.a_net_type==NET_NONE ) return NULL;
		
		npcs = fpga_cfg.a_9363; 
	}
	else if(SYS_B_FLAG==abcd)
	{
		if ( fpga_cfg.b_net_type==NET_NONE ) return NULL;
		
		npcs = fpga_cfg.b_9363;
	}
	else if(SYS_C_FLAG==abcd)
	{
		if ( fpga_cfg.c_net_type==NET_NONE ) return NULL;

		npcs = fpga_cfg.c_9363;
	}
	else if(SYS_D_FLAG==abcd)
	{
		if ( fpga_cfg.d_net_type==NET_NONE ) return NULL;

		npcs = fpga_cfg.d_9363;
	}

	if(TF_A==npcs)
	{

		page = FLASH_A_TS_PAGE_START+1;
		///block = FLASH_A_TS_BLOCK;
		p_init_data =&c_init_data;
		flag_page = FLASH_A_TS_PAGE_START;
	}
	else if(TF_B==npcs)
	{
		page = FLASH_B_TS_PAGE_START+1;
		//block = FLASH_B_TS_BLOCK;
		p_init_data =&c_init_data;
		flag_page = FLASH_B_TS_PAGE_START;
	}
	else if(TF_C==npcs)
	{
		page = FLASH_C_TS_PAGE_START+1;
		//block = FLASH_C_TS_BLOCK;
		p_init_data =&c_init_data;
		flag_page = FLASH_C_TS_PAGE_START;
	}
	else if(TF_D==npcs)
	{
		page = FLASH_C_TS_PAGE_START+1;
		//block = FLASH_C_TS_BLOCK;
		p_init_data =&c_init_data;
		flag_page = FLASH_C_TS_PAGE_START;
	}



	TFInitCs(npcs);

	len= sizeof(SYSTEM_INIT_DATA_T);
	p_init = (UCHAR8 *)p_init_data;
	TRACE_INFO("sizeof(SYSTEM_INIT_DATA_T)=%d\r\n",len);
	while ( len )
	{
		//FlashRead(flag_page, 0, data ,FLASH_PAGE_SIZE);
		wr_len = (len>FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : len;
		FlashRead(flag_page, 0, p_init ,FLASH_PAGE_SIZE);

		flag_page++;
		p_init +=  wr_len;		// 指针后移
		len -= wr_len;		// 计算剩余长度	
	}
	//FlashRead(flag_page, 0, data ,FLASH_PAGE_SIZE);
	
//	p_init = (UCHAR8 *)p_init_data;

//	for (i=0; i<sizeof(SYSTEM_INIT_DATA_T); i++)
//	{
//		*p_init++ = data[i];

//	}
	
	if (p_init_data->init_flag != (0xEB90|npcs))
	{
		TRACE_DEBUG("error__________p_init_data_struction[%04x]\r\n",p_init_data->init_flag);
		return -1;		
	}

	//初始化

	TRACE_INFO("!!!p_init_data->a_packet===%d\r\n",p_init_data->a_packet);
	
	for (packet=0; packet<p_init_data->a_packet; packet++)
	{
		//数据长度,从命令总个数(2byte)开始，---每个命令
		len = p_init_data->packet_len[packet];

		
		TRACE_INFO("current_____packet:%d,..len===%d...........\r\n",packet,len);
		if (len >PKG_MAX_9363)
		{	
			TRACE_DEBUG("error__________len_to_long[%04x],packet=[%04x]\r\n",len,packet);
			
			return -2;
		}
		//读取数据	
		data = sys_rece_buf;

				
		while( len )
		{
			TRACE_INFO("page=%x\r\n",page);
			
			ReadByteOneLoop = len>UPDATE_PKT_MAX_LEN ?UPDATE_PKT_MAX_LEN : len;
			WTD_CLR;
			for(ReadNums=0;ReadNums<ReadByteOneLoop/FLASH_PAGE_SIZE;ReadNums++)
			{
				if(ReadNums>=5)
				{
					TRACE_INFO("error_________error_________ReadNums:%d\r\n",ReadNums);
					return  -1;
				}
				FlashRead( page+ReadNums, 0, data+ReadNums*FLASH_PAGE_SIZE ,FLASH_PAGE_SIZE);
			}
			if(ReadByteOneLoop%FLASH_PAGE_SIZE)
			{			
				if(ReadNums>=5)
				{
					TRACE_INFO("error_________error_________ReadNums:%d\r\n",ReadNums);
					return  -1;
				}
				FlashRead( page+ReadNums, 0,data+ReadNums*FLASH_PAGE_SIZE ,ReadByteOneLoop%FLASH_PAGE_SIZE);
				ReadNums++;
			}
			len -= ReadByteOneLoop;	
						
			page +=ReadNums;


		
			count = 0;
			cmd_cnt = (data[0]<<8)|data[1];	//包中包含的命令个数

			TRACE_INFO("packet=%d,cmd_cnt===%d,ReadNums:%d\r\n",packet,cmd_cnt,ReadNums);
			data += 2;
			count += 2;
	
			//执行命令
			for (i=0; i<cmd_cnt; i++)
			{
				//#if 0
				WTD_CLR;		
				cmd = data[0];
				switch(cmd)
				{		
					case CMD_BLOCK_WRITE:
						data += CMD_BLOCK_WRITE_LEN;	
						count += CMD_BLOCK_WRITE_LEN;
					break;
					
					case CMD_SPI_WRITE:
						cmd_result = CmdHandleSpiWrite(npcs,(data[1]<<8)|data[2],data[3]);
						data += CMD_SPI_WRITE_LEN;
						count += CMD_SPI_WRITE_LEN;

				break;
				
				case CMD_WAIT:
					cmd_result = CmdHandleWait((data[1]<<8)|data[2]);
					data += CMD_WAIT_LEN;		
					count += CMD_WAIT_LEN;
				break;
				
				case CMD_REFCLK_SCALE:
					data += CMD_REFCLK_SCALE_LEN;
					count += CMD_REFCLK_SCALE_LEN;
				break;

				case CMD_WAIT_CALDONE:
					cmd_result = CmdHandleWaitCaldone(npcs,data[1],(data[2]<<8)|data[3]);
					data += CMD_WAIT_CALDONE_LEN;
					count += CMD_WAIT_CALDONE_LEN;
				break;

				case CMD_SPI_READ:
					cmd_result = ReadWriteTF(npcs,0,(data[1]<<8)|data[2],0);
					data += CMD_SPI_READ_LEN;
					count += CMD_SPI_READ_LEN;
				break;
				case CMD_FPGA_WRITE:  break;

				case CMD_UPDATA_DATA:
					TRACE_DEBUG("CMD_UPDATA_DATA9363_order....\r\n");
					length=0;
					cmd_result = GetUpdateData(npcs, data,&length);
					
					data += length;
					count += length;
				break;					

			case CMD_WAIT_FPGA_CFG:
#if 1
				k=0;
				while((TF_C==npcs)&&(AD9369)&&(k<10000))
				{
					k++;
					UsNopDelay(1);
					if(0==k%1000)
						WTD_CLR;
					//等待MCU读写SPI指示信号闲
					if(0x01==(0x01&(FpgaReadRegister(0x7a)>>15))	)
					{
						continue;
					}
					
					TRACE_INFO("( 0x00==(0x01&(FpgaReadRegister(0x7a)>>14))):%x\r\n",(	0x00==(0x01&(FpgaReadRegister(0x7a)>>14))));

					if((k<10000)&&(TF_C==npcs)&&(AD9369)&&(	0x00==(0x01&(FpgaReadRegister(0x7a)>>14)))	)
					{
						//切换成FPGA ROM SPI模式
						mcuFpgaSpiStaus=FpgaReadRegister(0x8000|0x7b);
						mcuFpgaSpiStaus&=0x3fff;
						mcuFpgaSpiStaus|=(0x02<<14);
						TRACE_INFO("1FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus):%x\r\n",mcuFpgaSpiStaus);
						FPGA_ENABLE_WRITE;
						FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus);
						FPGA_DISABLE_WRITE;
						//FPGA SPI 数据使能
						mcuFpgaSpiStaus=FpgaReadRegister(0x8000|0x7b);
						mcuFpgaSpiStaus&=0xdfff;
						mcuFpgaSpiStaus|=(0x1<<13);
						TRACE_INFO("2FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus):%x\r\n",mcuFpgaSpiStaus);
						FPGA_ENABLE_WRITE;
						FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus);
						FPGA_DISABLE_WRITE; 
						//等待FPGA ROM 写SPI 数据完成
						j=0;
						while((j<5000)&&(0x00==(0x01&(FpgaReadRegister(0x7a)>>14))	))
						{
							j++;
							UsNopDelay(1*1000);
							WTD_CLR;
						}
						
						//等待MCU读写SPI指示信号闲
						j=0;
						while((j<5000)&&(0x01==(0x01&(FpgaReadRegister(0x7a)>>15))	))
						{
							j++;
							UsNopDelay(1*1000);
							WTD_CLR;
						}

						//切换成MCU模拟控SPI
						mcuFpgaSpiStaus=FpgaReadRegister(0x8000|0x7b);
						mcuFpgaSpiStaus &= (~((1<<14)|(1<<15)));
						TRACE_INFO("3FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus):%x\r\n",mcuFpgaSpiStaus);
						FPGA_ENABLE_WRITE;
						FpgaWriteRegister(0x8000|0x7b,mcuFpgaSpiStaus);
						FPGA_DISABLE_WRITE;
					}	
					break;
				}
				break;
			#endif	

			default:
					TRACE_DEBUG("error__________9363_order[%04x]\r\n");
					//错误命令
					return -3;			
				break;//	TRACE_DEBUG("p_init_data_struction[%04x]\r\n",p_init_data->init_flag);
			}
			//#endif
#if 0
			WTD_CLR;
			
			cmd = data[0];
			switch(cmd)
			{		
				case CMD_BLOCK_WRITE:
					* tx_p++ = CMD_RESULT_IGNORE;
					pc_trans_info.tx_len++;
					data += CMD_BLOCK_WRITE_LEN;				
				break;
				
				case CMD_SPI_WRITE:
					FPGA_ENABLE_WRITE;
					cmd_result = CmdHandleSpiWrite(ft_ab,(data[1]<<8)|data[2],data[3]);
					FPGA_DISABLE_WRITE;
					* tx_p++ = cmd_result;
					pc_trans_info.tx_len++;
					data += CMD_SPI_WRITE_LEN;
				break;
				
				case CMD_WAIT:
					cmd_result = CmdHandleWait((data[1]<<8)|data[2]);
					* tx_p++ = cmd_result;
					pc_trans_info.tx_len++;
					data += CMD_WAIT_LEN;				
				break;
				
				case CMD_REFCLK_SCALE:
					* tx_p++ = CMD_RESULT_IGNORE;
					pc_trans_info.tx_len++;
					data += CMD_REFCLK_SCALE_LEN;
				break;

				case CMD_WAIT_CALDONE:
					FPGA_ENABLE_WRITE;
					cmd_result = CmdHandleWaitCaldone(ft_ab,data[1],(data[2]<<8)|data[3]);
					FPGA_DISABLE_WRITE;
					* tx_p++ = cmd_result;
					pc_trans_info.tx_len++;
					data += CMD_WAIT_CALDONE_LEN;
				break;

				case CMD_SPI_READ:
					FPGA_ENABLE_WRITE;
					cmd_result = ReadWriteTF(ft_ab,0,(data[1]<<8)|data[2],0);
					FPGA_DISABLE_WRITE;
					* tx_p++ = cmd_result;
					pc_trans_info.tx_len++;
					data += CMD_SPI_READ_LEN;
				break;

				default:
					//错误命令				
			//		PcPacketTransHead(0xdf,0x01,0x01,0x01,0xab,0x01);
					TRACE_INFO("9363_错误命令\r\n");
					* tx_p++ = 0;
					pc_trans_info.tx_len++;
			
					goto out;
				break;
			}
#endif 			
			}

		}
		
	}
exit:
	TRACE_DEBUG("0__________EXIT-9363_,addr=[0X5E]--read=[%x]\r\n",ReadWriteTF(TF_A,0,0X5E,0));

//	TRACE_DEBUG("packet=[%04x],p_init_data->a_packet=[%04x]\r\n",packet,p_init_data->a_packet);
	return 0;
}

//#if 0
/*************************************************************
Name:SetAtt3
Description:设置输出端衰减值
Input:A,B,ATT值*2
Output:void         
Return:void
**************************************************************/
void SetAtt3(UCHAR8 abcd,UCHAR8 att)
{
	UCHAR8 reg_read;
	UCHAR8 npcs;

	switch(abcd)
	{
		case SYS_A_FLAG:
			npcs = fpga_cfg.a_9363;
			break;
		case SYS_B_FLAG:
			npcs = fpga_cfg.b_9363;
			break;
		case SYS_C_FLAG:
			npcs = fpga_cfg.c_9363;
			break;
		case SYS_D_FLAG:
			npcs = fpga_cfg.d_9363;
			break;
		default:
			break;
	}

	//077[D6] 设置为0，使得7C[D6]为自清0.
	reg_read = ReadWriteTF(npcs,0,0x0077,0);
	reg_read &= ~0x40;
	ReadWriteTF(npcs,1,0x0077,reg_read);

	//075[D6~D1]中写入相应的衰减值
	att <<= 1;
	att &= 0x7e;
	ReadWriteTF(npcs,1,0x0075,att);

	//7C[D6]写1来更新衰减值使其生效。
	ReadWriteTF(npcs,1,0x007c,0x40);

}

/*************************************************************
Name:SetAtt1
Description:设置输出端衰减值
Input:A,B,ATT?
Output:void         
Return:void
**************************************************************/
void SetAtt1(UCHAR8 abcd,UCHAR8 att)
{
	UCHAR8 npcs;

	//npcs = abcd;

	switch(abcd)
	{
		case SYS_A_FLAG:
			npcs = fpga_cfg.a_9363;
			break;
		case SYS_B_FLAG:
			npcs = fpga_cfg.b_9363;
			break;
		case SYS_C_FLAG:
			npcs = fpga_cfg.c_9363;
			break;
		case SYS_D_FLAG:
			npcs = fpga_cfg.d_9363;
			break;
		default:
			break;
	}
	

	

	if(TF_D == npcs)
	{
		ReadWriteTF(TF_C,1,0x0FB,0X08);		
		ReadWriteTF(TF_C,1,0x109,att);
	}
	else 
	{
		ReadWriteTF(npcs,1,0x0FB,0X08);
		ReadWriteTF(npcs,1,0x10C,att);
	}

}



/*************************************************************
Name:SetAtt3Tx
Description:TX正交校准过程
Input:A,B,ATT
Output:void         
Return:0:失败，1，成功   
**************************************************************/
UCHAR8 SetAtt3Tx(UCHAR8 npcs,UCHAR8 att)
{
	
	ReadWriteTF(npcs,1,0x169,0xCC);  //关闭RX实时正交校准；
	ReadWriteTF(npcs,1,0x18B,0x8D);   //关闭RX BBDC实时校准；
	ReadWriteTF(npcs,1,0x014,0x03);    //芯片进入等待模式（此时芯片无输出）
	ReadWriteTF(npcs,1,0x0AC,att);   //将刚才的ATT3值写入（这里为0.5dB步进）（比如ATT3设置为10dB）
	ReadWriteTF(npcs,1,0x016,0x10);   // 开始TX正交校准；
	ReadWriteTF(npcs,1,0x169,0xCE);   //启动RX实时正交校准；
	ReadWriteTF(npcs,1,0x18B,0xAD);   //启动RX BBDC实时校准；
	ReadWriteTF(npcs,1,0x014,0x23);    //芯片进入正常工作状态。

	UsNopDelay(100*1000);	
}
/*************************************************************
Name:TransSetPll
Description:配置本振
Input:上下行 ,本振值
Output:void         
Return:  
**************************************************************/
void TransSetPll(UCHAR8 up_down_flag, FLOAT32 pll)
{
	FLOAT32 vco,n;
	UINT16 pll_int;
	UINT32 pll_frac;
	
	vco = pll*4;
	n = vco/50.0;
	pll_int = (UINT16)n;
	pll_frac = (UINT32)(8388593*(n-pll_int));
	
	
	//关输出
	ReadWriteTF(TF_A,1,0x014,0x03);
	ReadWriteTF(TF_B,1,0x014,0x03);

	//设置RX端
	ReadWriteTF(up_down_flag?TF_B:TF_A,1,0x233,(UCHAR8)(pll_frac));		// Write Rx Synth Fractional Freq Word[7:0]
	ReadWriteTF(up_down_flag?TF_B:TF_A,1,0x234,(UCHAR8)(pll_frac>>8));		// Write Rx Synth Fractional Freq Word[15:8]
	ReadWriteTF(up_down_flag?TF_B:TF_A,1,0x235,(UCHAR8)(pll_frac>>16));	// Write Rx Synth Fractional Freq Word[22:16]
	ReadWriteTF(up_down_flag?TF_B:TF_A,1,0x232,(UCHAR8)(pll_int>>8));		// Write Rx Synth Integer Freq Word[10:8]
	ReadWriteTF(up_down_flag?TF_B:TF_A,1,0x231,(UCHAR8)(pll_int));			// Write Rx Synth Integer Freq Word[7:0] 同时启动VCO校准
	ReadWriteTF(up_down_flag?TF_B:TF_A,1,0x005,0x11);					// Set LO divider setting

	//设置TX端
	ReadWriteTF(up_down_flag?TF_A:TF_B,1,0x273,(UCHAR8)(pll_frac));		// Write Tx Synth Fractional Freq Word[7:0]
	ReadWriteTF(up_down_flag?TF_A:TF_B,1,0x274,(UCHAR8)(pll_frac>>8));		// Write Tx Synth Fractional Freq Word[15:8]
	ReadWriteTF(up_down_flag?TF_A:TF_B,1,0x275,(UCHAR8)(pll_frac>>16));	// Write Tx Synth Fractional Freq Word[22:16]
	ReadWriteTF(up_down_flag?TF_A:TF_B,1,0x272,(UCHAR8)(pll_int>>8));		// Write Tx Synth Integer Freq Word[10:8]
	ReadWriteTF(up_down_flag?TF_A:TF_B,1,0x271,(UCHAR8)(pll_int));			// Write Tx Synth Integer Freq Word[7:0] 同时启动VCO校准
	ReadWriteTF(up_down_flag?TF_A:TF_B,1,0x005,0x11);					// Set LO divider setting

	//开输出
	ReadWriteTF(TF_A,1,0x014,0x23);
	ReadWriteTF(TF_B,1,0x014,0x23);	
}
/*************************************************************
Name:TransGetPllRXStatus
Description:查询本振状态
Input:上下行 ,本振值
Output:void         
Return:  
**************************************************************/
UCHAR8 TransGetRxPllStatus(UCHAR8 up_down_flag)
{
	UCHAR8 pll_rx;

	pll_rx = ReadWriteTF(up_down_flag?TF_B:TF_A,0,0x247,0x00);

	//收发有任何一个失锁就告警
	if ((pll_rx&0x02) == 0)
		return 0;
	else 
		return 1;		
}
/*************************************************************
Name:TransGetPllTXStatus
Description:查询本振状态
Input:上下行 ,本振值
Output:void         
Return:  
**************************************************************/
UCHAR8 TransGetTxPllStatus(UCHAR8 up_down_flag)
{
	UCHAR8 pll_tx;

	pll_tx = ReadWriteTF(up_down_flag?TF_A:TF_B,0,0x287,0x00);

	//收发有任何一个失锁就告警
	if ((pll_tx&0x02) == 0)
		return 0;
	else 
		return 1;		
}
/*************************************************************
Name:TransGetPllStatus
Description:查询本振状态
Input:上下行 ,本振值
Output:void         
Return:  
**************************************************************/
UCHAR8 TransGetClkStatus(void)
{
	UCHAR8 clk_a,clk_b;

	clk_a = ReadWriteTF(TF_A,0,0x05e,0x00);
	clk_b = ReadWriteTF(TF_B,0,0x05e,0x00);

	//收发有任何一个失锁就告警
	if ((clk_a&clk_b&0x80) == 0)
		return 0;
	else 
		return 1;		
}
//#endif


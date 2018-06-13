/***************************************************************
*Shenzhen Grandlinking Technology Co.,Ltd All rights reserved
*
* FileName    :spi.c
* Description :SPI处理函数
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


UINT16 flash_page_size = FLASH_PAGE_SIZE_256;
UINT16 flash_type = FLASH_TYPE3;
UCHAR8 flash_parr1=0;
UCHAR8 flash_parr2=0;

/*************************************************************
Name:FlashReadId          
Description:读取FLASH ID
Input:void            
Output:void         
Return:返回32位ID码信息,[31~24]第1字段,[23~16]第二字段,以此类推
**************************************************************/
UINT32 FlashReadId1(void)
{

	UCHAR8 op_data[5]={0};

	WTD_CLR;
	//FlashWaitReady();
	UsNopDelay(100*1000); 			//delay 50ms	

	op_data[0] = 0x9f;

	SpiReadBuf(SPI_CS_AT45,op_data,5,0,0);

	if (op_data[1] != 0x1f)
	{
		TURN_OFF_LED;
	}
	else
	{
		TURN_ON_LED;
	}		

	// [31~24]第1字段,[23~16]第2字段,[15~8]第3字段,[7~0]第4字段
	return (UINT32)( (op_data[1]<<24)|(op_data[2]<<16)|(op_data[3]<<8)|(op_data[4]<<0) );
	
	//return op_data[2];
	
}
/*************************************************************
Name:FlashReadStatus         
Description:读取FLASH状态
Input:void            
Output:void         
Return: status        
**************************************************************/
static UCHAR8 FlashReadStatus1(void)
{
//	UCHAR8 	status,cmd;		
	UCHAR8 cmd[2]={0};
	if(FLASH_TYPE3==FLASH_TYPE)
	{
		cmd[0] = 0x05;

	}else 
	{
		cmd[0] = 0xD7;
	}	
	//cmd[0] = 0xD7;
	
	//cmd[1] = 0x00;

	SpiWriteBuf(SPI_CS_AT45, cmd, 2, NULL, 0);
	
	return cmd[1];	
}

void FlashWaitReady1()
{
	UCHAR8 st;
	UINT32 i = 0;

	if(FLASH_TYPE==FLASH_TYPE3)
	{
		do
		{
			UsNopDelay(1);
			i++;
			st = FlashReadStatus1();
			//TRACE_INFO("3FlashWaitReadyi=[%d]\r\n",i);
			WTD_CLR;
			
		}while( ((st&(1<<0))==1)&&(i<500000) );		
		//TRACE_INFO("0FlashWaitReady\r\n");
	}else
	{
		do
		{
			UsNopDelay(5);
			i++;			
			st = FlashReadStatus1();
			//TRACE_INFO("1FlashWaitReadyi=[%d]\r\n",i);
			WTD_CLR;
			
		}while( ((st&(1<<7))==0)&&(i<500000) );

	}

}

/*************************************************************
Name:FlashEraseSectors          
Description:擦除部分Block
Input:起始block            
Output:void         
Return:         
**************************************************************/
CHAR8 FlashEraseSectors1(UINT32 from,UINT32 to)
{
	UINT32 sector_add;
	UCHAR8 op_data[4]={0};
	UINT16 delay_10ms_count = 400;
	
	for (sector_add=from; sector_add<=to; sector_add++)
	{

		if(FLASH_TYPE==FLASH_TYPE3)
		{
			
			TRACE_INFO("EraseSector %d\r\n",sector_add);				
			WTD_CLR;
			FlashWaitReady1();

			op_data[0]=0x06;
			SpiWriteBuf(SPI_CS_AT45,op_data,1,0,0);
			//UsNopDelay(1*1000);				//delay 50ms	

			//WTD_CLR;
			//op_data[0]=0x05;
			//SpiWriteBuf(SPI_CS_AT45,op_data,2,0,0);
			//WTD_CLR;
			//FlashWaitReady();
			//UsNopDelay(1*1000);				//delay 50ms	
			//TRACE_DEBUG("FlashEraseSectors_op_data[1]=[%x]\r\n",op_data[1]);

			//FlashEraseSectors;
			op_data[0] = 0x20;
			op_data[1] = (UCHAR8)(((sector_add*FLASH_SECTOR_SIZE)>>16)&0x00ff);
			op_data[2] = (UCHAR8)(((sector_add*FLASH_SECTOR_SIZE)>>8)&0x00ff);	
			op_data[3] =(UCHAR8)(((sector_add*FLASH_SECTOR_SIZE)>>0)&0x00ff);
		}else
		{
			op_data[0] = 0x50;
			if (FLASH_TYPE==FLASH_TYPE1)
			{
				op_data[1] = (UCHAR8)((sector_add>>2)&0x00ff);
				op_data[2] = (UCHAR8)(((sector_add<<6)&0x00c0));	
				op_data[3] = 0x01;
			}
			else if (FLASH_TYPE==FLASH_TYPE0)
			{
				op_data[1] = (UCHAR8)((sector_add>>4)&0x00ff);
				op_data[2] = (UCHAR8)(((sector_add<<4)&0x00f0));	
				op_data[3] = 0x01;
			}
			else
				return -1;

		}
		
		SpiWriteBuf(SPI_CS_AT45,op_data,4,0,0);
		//TRACE_DEBUG("1FlashEraseSectors-sector_add=[%d],to*4096=[%d]\r\n",sector_add,to*4096);			
		while (delay_10ms_count--)
		{
			//TRACE_DEBUG("2FlashEraseSectors--delay_10ms_count=[%d]\r\n",delay_10ms_count);	
			//BUSY bit
			if (!(FlashReadStatus1()&(0x01<<0)))    
				break;
			UsNopDelay(1000);				//delay 25ms
			WTD_CLR;
		}
		FLASH_LED;	
		
	}
	return 1;
}

/*************************************************************
Name:FlashRead          
Description:读取一页数据
Input:void            
Output:void         
Return:void         
**************************************************************/
void  FlashRead1(INT32 page,INT16 offset,UCHAR8 *data,INT32 len)
{
	UCHAR8 op_data[5]={0};
	UINT16 i;
	
	
//	TRACE_INFO("FlashReadOnePage\r\n"); 
	FlashWaitReady1();
	//TRACE_INFO("FlashReadOnePage1--page=[%d]\r\n",page); 
	if( FLASH_TYPE==FLASH_TYPE3	)//#endif	//201410081030----
	{
		op_data[0] = 0x03;
		op_data[1] = (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>16)&0x00ff);
		op_data[2] = (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>8)&0x00ff);
		op_data[3] = (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>0)&0x00ff);
		WTD_CLR; 
		data[0]=0;
		SpiReadBuf(SPI_CS_AT45,op_data,4,data,len);
		
	}
	else
	{
		op_data[0] = 0xD2;

		if (FLASH_TYPE==FLASH_TYPE1) //#endif	//201410081030----
		{
			op_data[1] = (UCHAR8)((page>>5)&0x00ff);
			op_data[2] = (UCHAR8)(((page<<3)&0x00f8)|((offset>>8)&0x0007));
			op_data[3] = (UCHAR8)(offset&0x00ff);
		}
		else if (FLASH_TYPE==FLASH_TYPE0)
		{
			op_data[1] = (UCHAR8)((page>>6)&0x00ff);
			op_data[2] = (UCHAR8)(((page<<2)&0x00fc)|((offset>>8)&0x0003));
			op_data[3] = (UCHAR8)(offset&0x00ff);
		} else
		{
			return;
		}
		SpiReadBuf(SPI_CS_AT45,op_data,8,data,len);	
		WTD_CLR; 
		//data[0]=0;
	}
	
//	TRACE_INFO("FlashReadOnePage2\r\n"); 
	//SpiReadBuf(SPI_CS_AT45,op_data,4,data,len);
	//for(i=0;i<len;i++)
	//{
	//	WTD_CLR;
		//TRACE_INFO("1FlashRead-,DAT[%d]=[%x]\r\n",i,data[i]);
	//}
//	WTD_CLR;
//	TRACE_INFO("FlashReadOnePage\r\n"); 
//	FlashWaitReady();	
//	TRACE_INFO("FlashReadOnePage3\r\n"); 
	if ((page&0x10) == 0)
		TURN_OFF_LED
	else
		TURN_ON_LED
	
	WTD_CLR;	
}

/*************************************************************
Name:FlashWriteOnepage          
Description:写一页数据
Input:page address,data pointer,len           
Output:void         
Return:void         
**************************************************************/
CHAR8 FlashWrite1(UINT32 page,INT16 offset,UCHAR8 *data,UINT16 len,UINT16 option)
{
	return 1;
}

/*************************************************************
Name: FlashErasePage         

Description: 消息包命令:擦除外部FLASH一个page的内容
Input: page  :flash 页

Return: void
**************************************************************/
UINT32 FlashPageChang ( UINT32 page )
{
	return page;

}

/*************************************************************
Name: GetFlashPageInfo       
Description: 得到Flash 页信息

Input:
	msg_length: 消息包的长度，不包括CRC
	p_msg_dat: 指向存放消息包的缓冲指针
	p_tx_buff: 指向应答包缓冲区指针
Return: void
**************************************************************/
void GetFlashPageInfo( UINT16 length, UCHAR8 * p_dat, UCHAR8 * p_tx_buff )
{
}


/*************************************************************
Name:Ad9122Write
Description: DAC AD9788SPI写数据
Input:addr:SPI地址，byte_len:数据的长度，val:写入的数据，main_dive_flag主用分集选择          
Output:         
Return:  
*************************************************************/
void Ad9122Write(UCHAR8 addr, UCHAR8 val,UCHAR8 ab_flag)
{ 

	UCHAR8 send_buff[2] = {0x00};	//max 5 bytes
	UCHAR8 dat_len = 2; 

	send_buff[0] = (addr&0x7f);  
	send_buff[1] = (UCHAR8)(val&0x00ff);  

	SpiWriteBuf((ab_flag==0) ? SPI_CS_AD9122_A: SPI_CS_AD9122_B, send_buff, dat_len, 0, 0);
}

/*************************************************************
Name:Ad9122Read
Description: DAC AD9788SPI读数据
Input:addr:SPI地址，byte_len:数据的长度，main_dive_flag主用分集选择     
Output:         
Return:读取的数据  
*************************************************************/
UCHAR8 Ad9122Read(UCHAR8 addr, UCHAR8 ab_flag)
{

	UCHAR8 rece_buf[2];
	UCHAR8 dat_len = 2;
	UCHAR8 ret_val = 0; 
 
    ENABLE_AD9122_READ;  
	   
	rece_buf[0] = 0x80|(addr&0x7f);

	SpiReadBuf((ab_flag==0) ? SPI_CS_AD9122_A: SPI_CS_AD9122_B, rece_buf, dat_len, 0, 0);	

	ret_val = rece_buf[1];  
	
    DISABLE_AD9122_READ;       
	  
	return ret_val;

}



/*************************************************************
Name:Ad9524Write          
Description: 时钟 AD9517寄存器写数据
Input:address,data            
Output:void         
Return:void    
**************************************************************/
void Ad9524Write(UINT16 add, UCHAR8 data)
{
	UCHAR8 op_data[3];
//#ifdef FPGA_ACDU_16M_FLASH
#ifdef AD9528
	op_data[0] = (add>>8)&0x7f;	//Tansfer one byte,write,add high
#else
	op_data[0] = (add>>8)&0x1f;	//Tansfer one byte,write,add high
#endif
	
	op_data[1] = (add&0xff);			//add low
	op_data[2] = data;

	SpiWriteBuf(SPI_CS_AD9524,op_data,3,0,0);
	
}   

/*************************************************************
Name:Ad9524Read           
Description: 时钟 AD9517寄存器读数据 
Input:address            
Output:void         
Return:读到的数据  
**************************************************************/
UCHAR8 Ad9524Read(UINT16 add)
{

	UCHAR8 op_data[3];

#ifdef AD9528
	 ENABLE_AD9528_READ;
	 op_data[0] = (((add>>8)&0x7f)|0x80);	//Tansfer one byte,write,add high
#else
	ENABLE_AD9524_READ;
	op_data[0] = (((add>>8)&0x1f)|0x80);	//Tansfer one byte,write,add high
#endif	
   
	
	op_data[1] = (add&0xff);			//add low

	SpiReadBuf(SPI_CS_AD9524,op_data,3,0,0);
	

#ifndef AD9528
    DISABLE_AD9524_READ; 
#endif
	
	return op_data[2];	
}



/*************************************************************
Name:Ad6649Write          
Description:向Ad6655寄存器写数据
Input:address,data            
Output:void         
Return:void    
**************************************************************/
void Ad6649Write(UINT16 add,UCHAR8  data)
{

	SpiCsEnable(SPI_CS_AD6643);
	UsNopDelay(50);		
	SdioSpiWriteByte(add,data);
	UsNopDelay(10);	 
	SpiCsDisable(SPI_CS_AD6643);						//9627 CS HIGH
	UsNopDelay(50);			
}

/*************************************************************
Name:Ad6655Read          
Description:向Ad6655寄存器读数据
Input:address            
Output:void         
Return:读到的数据  
**************************************************************/
UCHAR8 Ad6643Read(UINT16 add)
{
	UCHAR8 ret;
	
	SpiCsEnable(SPI_CS_AD6643);
	UsNopDelay(50); 
	ret = SdioSpiReadByte(add);
	SpiCsDisable(SPI_CS_AD6643);						//6655 CS HIGH
	UsNopDelay(50);		  
	return ret; 
}  



#if 1


/*************************************************************
Name:FlashReadStatus         
Description:读取FLASH状态
Input:void            
Output:void         
Return: status        
**************************************************************/
UCHAR8 FlashReadStatus2(void)
{
	UCHAR8 cmd[2]={0};

	cmd[0] = 0x05;
	cmd[1] = 0x00;

	SpiWriteBuf(SPI_CS_AT45, cmd, 2, NULL, 0);
	return cmd[1];	
}

void FlashWaitReady2(void)
{
	UCHAR8 st;
	UINT32 i = 0;


		do
		{
			UsNopDelay(5);
			i++;
			st = FlashReadStatus2();
			WTD_CLR;			
		}while( (i<500000)&&((st&(1<<0))==1) );		

}

/*************************************************************
Name:FlashEraseSectors          
Description:擦除部分Block
Input:起始block            
Output:void         
Return:         
**************************************************************/
CHAR8 FlashEraseSectors2(UINT32 from,UINT32 to)
{
	UINT32 sector_add;
	UCHAR8 op_data[5]={0};
	UINT16 delay_10ms_count = 100;
	
	for(sector_add=from; sector_add<=to; sector_add++)
	{
		FlashWaitReady2();

		op_data[0]=0x06;
		SpiWriteBuf(SPI_CS_AT45,op_data,1,NULL,0);

		op_data[0] = 0x20;
		op_data[1] = (UCHAR8)(((sector_add*FLASH_BYTES_PER_SECTOR)>>16)&0x00ff);
		op_data[2] = (UCHAR8)(((sector_add*FLASH_BYTES_PER_SECTOR)>>8)&0x00ff);	
		op_data[3] =(UCHAR8)(((sector_add*FLASH_BYTES_PER_SECTOR)>>0)&0x00ff);
		SpiWriteBuf(SPI_CS_AT45,op_data,4,NULL,0);
			
		delay_10ms_count=400;		
		while (delay_10ms_count--)
		{
		//BUSY bit
		if (!(FlashReadStatus2()&(0x01<<0)))
			break;
			UsNopDelay(1000);	//delay 25ms
			WTD_CLR;
		}
	}
	return 1;
}

/*************************************************************
Name:FlashWritePage          
Description:写一页数据
Input:page address,data pointer,len           
Output:void         
Return:void         
**************************************************************/
void FlashWrite2(UINT32 page,INT16 offset,UCHAR8 *data,UINT16 len,UINT16 option)
{
	UCHAR8 op_data[10]={0};
	
	if((offset+len)>FLASH_PAGE_SIZE)
	{
		return;
	}

	if (0X00==(page%FLASH_PAGE_NUM_PER_SECTOR))
	{
		 FlashEraseSectors2(page/FLASH_PAGE_NUM_PER_SECTOR,page/FLASH_PAGE_NUM_PER_SECTOR);
	}

	FlashWaitReady2();

	op_data[0]=0x06;
	SpiWriteBuf(SPI_CS_AT45,op_data,1,NULL,0);

	op_data[0] = 0x02;
	op_data[1] =  (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>16)&0x00ff);
	op_data[2] = (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>8)&0x00ff);
	op_data[3] = (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>0)&0x00ff);

	SpiWriteBuf(SPI_CS_AT45,op_data,4,data,len);

}


/*************************************************************
Name:FlashRead          
Description:读取一页数据
Input:void            
Output:void         
Return:void         
**************************************************************/
void  FlashRead2(INT32 page,INT16 offset,UCHAR8 *data,INT32 len)
{
	UCHAR8 op_data[10]={0};
	
	FlashWaitReady2();
	
	op_data[0] = 0x03;
	op_data[1] = (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>16)&0x00ff);
	op_data[2] = (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>8)&0x00ff);
	op_data[3] = (UCHAR8)(((page*FLASH_PAGE_SIZE+offset)>>0)&0x00ff);		
	SpiReadBuf(SPI_CS_AT45,op_data,4,data,len);
}

/*************************************************************
Name:FlashReadId          
Description:读取FLASH ID
Input:void            
Output:void         
Return:返回32位ID码信息,[31~24]第1字段,[23~16]第二字段,以此类推
**************************************************************/
UINT32 FlashReadId2(void)
{

	UCHAR8 op_data[5]={0};
	UINT32 id;

	WTD_CLR;
	
	UsNopDelay(100*1000); 			//delay 50ms	

	FlashWaitReady2();
	op_data[0] = 0x9f;

	SpiReadBuf(SPI_CS_AT45,op_data,5,NULL,0);

	// [31~24]第1字段,[23~16]第2字段,[15~8]第3字段,[7~0]第4字段
	 (id=(UINT32)( (op_data[1]<<24)|(op_data[2]<<16)|(op_data[3]<<8)|(op_data[4]<<0) ));
	return id;
}

UINT32 FlashReadId(void)
{
		UINT32 id = 0;
		#ifdef FLASH_OLD
		
			id = FlashReadId1();
		#else
		
			id = FlashReadId2();
		#endif

		return id;
		
}
/*************************************************************
Name:GetFlashPageSize          
Description: 读取Flash页大小
Input:void            
Output:void         
Return:         
**************************************************************/
void GetFlashPageSize()
{
	UINT32 id;

	id = FlashReadId();
	TRACE_INFO("Ex Flash201405071629\r\n ");

	flash_page_size = FLASH_PAGE_SIZE_256;
	flash_type =FLASH_TYPE3;
	flash_parr1 =0;
	//id = FlashReadId(FLASH_TYPE3);
	id = FlashReadId();
	printf("flash_id=<%08X>\r\n ", id);
	 //if(FLASH_ID3==id)
	 {
	 	
		flash_page_size = FLASH_PAGE_SIZE_256;
		flash_type =FLASH_TYPE3;
		flash_parr1=1;
	 }
	TRACE_INFO("flash_page_size=[%04x],FLASH_PAGE_SIZE=[%04x]\r\n",flash_page_size,FLASH_PAGE_SIZE);	


	update_pak_max_len=1024;



}

/*************************************************************
Name:FlashEraseSectors          
Description:擦除部分Block
Input:起始block            
Output:void         
Return:         
**************************************************************/
CHAR8 FlashEraseSectors(UINT32 from,UINT32 to)
{
	#ifdef FLASH_OLD
	//FlashEraseSectors1( from, to);
	#else
	FlashEraseSectors2( from, to);
	#endif
	return 1;
}

void  FlashRead(INT32 page,INT16 offset,UCHAR8 *data,INT32 len)
{
	#ifdef FLASH_OLD
	//FlashRead1(page, offset, data,len);
	#else
	FlashRead2(page, offset, data, FLASH_PAGE_SIZE);
	#endif
}
void FlashWrite(UINT32 page,INT16 offset,UCHAR8 *data,UINT16 len,UINT16 option)
{
	#ifdef FLASH_OLD
	//FlashWrite1(page,offset, data, len,option);
	#else
	FlashWrite2(page, 0, data, len,option );
	#endif
}

#endif









/************************************************************

     Copyright (C), 2011-2111, ����̩�˿Ƽ����޹�˾

*************************************************************
�ļ�����   GLOBAL_DRV_C_
�汾�ţ�   V03
���ߣ�     Τ��� 
�������ڣ� 2010��08��05��
����޸ģ� 
���������� GLOBAL_DRV_C_�ĵײ������ļ� 
�����б� 
�޸����ڣ� 
        1.����:      2010��08��05��  
          ���ߣ�     Τ��� 
          �޸����ݣ� ԭ��
        2.����:      2012��04��17��  
          ���ߣ�     ����ǫ
          �޸����ݣ� ΢�͹�ǥV02 
**************************************************************/
#include "Header.h"

volatile UINT32 sys_work_info = 0;
volatile UINT32 au_send_msg = 0;
UCHAR8 sys_temp_buff[SYS_TMP_BUFF_SIZE];	// ϵͳ��ʱ������

volatile unsigned char * p_ext_8= (volatile unsigned char*)Bank1_SRAM1_ADDR;
volatile unsigned short * p_ext_16 = (volatile unsigned short*)Bank1_SRAM1_ADDR;



/*************************************************************
Name:          InitExtentBus_16      
Description:   ����16λ����
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void InitExtentBus_16(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
  
/*-- FSMC Configuration ------------------------------------------------------*/
  p.FSMC_AddressSetupTime = 8;
  p.FSMC_AddressHoldTime = 8;
  p.FSMC_DataSetupTime = 16;
  p.FSMC_BusTurnAroundDuration = 0;
  p.FSMC_CLKDivision = 1;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

  /* Enable FSMC Bank1_SRAM Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}


/*************************************************************
Name:          InitExtentBus_8      
Description:   ����8λ����
Input:         void          
Output:        void         
Return:        void         
**************************************************************/
void InitExtentBus_8(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
  
/*-- FSMC Configuration ------------------------------------------------------*/
  p.FSMC_AddressSetupTime = 2;
  p.FSMC_AddressHoldTime  = 0;
  p.FSMC_DataSetupTime    = 2;
  p.FSMC_BusTurnAroundDuration = 0; 
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0; 
  p.FSMC_AccessMode = FSMC_AccessMode_A;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

  /* Enable FSMC Bank1_SRAM Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  

  
}

/*************************************************************
Name:FpgaLoadAll
Description:FPGA����
Input:�����ļ����ܳ���          
Output:void         
Return:-1:ʧ�ܣ�1: �ɹ�         
**************************************************************/
CHAR8 FpgaLoadAll(UINT32 len)
{
	#if 1
	UINT32 page_index,ReadByteOneLoop;
	UINT32 i ,ReadNums,flag=0; 
	UCHAR8 *p_flash_page = sys_temp_buff;
	UCHAR8 retry = 100;
	CHAR8 result;
	UCHAR8 serial_retry = 4; 
	UCHAR8 ucTmpDat= 0;
    
	TRACE_DEBUG_WP("FpgaLoadAll enter\r\n");
	WTD_CLR;
#ifdef FPGA_SOLO_LOAD
	CLR_FPGA_NCS1_PIN;
#endif 
	// Fpga�������״̬ 
	CLR_FPGA_NCONFIG;		    // ���� nCONFIG�ܽ�
	
	UsNopDelay(20);				//��ʱ 20us
	TRACE_DEBUG_WP("FpgaLoadAll CLR_FPGA_NCONFIG\r\n");

	if ( 1 == GET_FPGA_STAUTS )	//�ȴ� nstauts ���
		return -1;
	if (GET_FPGA_CONF_DONE)  
	{ 
		return -1;
	}

	SET_FPGA_NCONFIG;			//���� nCONFIG 
	TRACE_DEBUG_WP("FpgaLoadAll SET_FPGA_NCONFIG\r\n");

	for(i=0;i<20;i++)
	{
		WTD_CLR;
		UsNopDelay(500);
		WTD_CLR;	
		//��ʱ2s  
		if ( 1 == GET_FPGA_STAUTS )	 //�ȴ� nstauts ���
		{
			i=21;
			break;
		}
	}
		//��ʱ2s  
	if ( 0 == GET_FPGA_STAUTS )	 //�ȴ� nstauts ���
	{
		return -1;
	}
	TRACE_DEBUG("FpgaLoadAll GET_FPGA_STAUTS--high\r\n");
					
	UsNopDelay(20);			       //��ʱ 20us

#ifndef FPGA_SOLO_LOAD
		CLR_FPGA_NCS1_PIN;
#endif 

	WTD_CLR;
	UsNopDelay(1000);	
	WTD_CLR;
	UsNopDelay(1000);
	WTD_CLR;
	
	TRACE_DEBUG_WP("FpgaLoad Start\r\n"); // ��λҳ��ַ
	if( FPGA_LOAD_BLOCK2==fpga_load_block ) 
	{
		page_index=( FLASH_FPGA_PAGE_START2+1);

	}else
	{
		page_index=( FLASH_FPGA_PAGE_START1+1);

	}	
	TRACE_INFO_WP("Start Page:%04X.\r\n", page_index);

	
	CLR_FPGA_CS_PIN;      // FPGA��Ƭѡ��Ч

	WTD_CLR;
		
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
           #ifdef FPGA_COMPRESS
              SentLoadDat(*(p_flash_page+i)); 
           #else 
            *p_ext_8 = ucTmpDat; 
           #endif 

		   if (!GET_FPGA_STAUTS)//20121119
		   	{
				//TRACE_INFO(" GET_FPGA_STAUTS==0\r\n");
		   		return -2;
		   	}
		   
		}
		len -= ReadByteOneLoop;				
		page_index +=ReadNums;
//		TRACE_INFO(" page_index=[%d],ReadNums=[%d]\r\n",page_index,ReadNums);
		flag=1;
	}
	TRACE_INFO("load all\r\n");
	WTD_CLR;
    //�������
	UsNopDelay(1000); 			//Delay 1ms 
	
	if (GET_FPGA_CONF_DONE)  
	{     
		TRACE_INFO_WP("LOAD SUCCESS-0\r\n");
#if 1
		SentLoadDat(0X00);		//dummy write
		SentLoadDat(0X00);		//dummy write
#else
		*p_ext_8 = 0x00;//dummy write
		*p_ext_8 = 0x00;//dummy write
	 	*p_ext_8 = 0x00;//dummy write
#endif	
#ifndef FPGA_SOLO_LOAD
		SET_FPGA_NCS1_PIN;
#endif

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

				SentLoadDat(0X00);		//dummy write
				SentLoadDat(0X00);		//dummy write

#ifndef FPGA_SOLO_LOAD
		SET_FPGA_NCS1_PIN;
#endif

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
		
#ifdef FPGA_SOLO_LOAD
		//201411171000  SET_FPGA_NCS1_PIN;
		;
#else
		SET_FPGA_NCS1_PIN;
#endif
		
		return -1;
	}	
	#else
	UINT16 page,read_len;
	UINT32 i, j; 
	UCHAR8 *p_flash_page = sys_temp_buff;
	UCHAR8 retry = 100;
	CHAR8 result;
	UCHAR8 serial_retry = 4; 
    UCHAR8 ucTmpDat =0;

	//TRACE_DEBUG_WP("FpgaLoadAll enter\r\n");
	WTD_CLR;
 
	// Fpga�������״̬ 
	CLR_FPGA_NCONFIG;		    // ���� nCONFIG�ܽ�
	
	UsNopDelay(20);				//��ʱ 20us

	if ( 1 == GET_FPGA_STAUTS )	//�ȴ� nstauts ���
		return -1;

	SET_FPGA_NCONFIG;			//���� nCONFIG 

	UsNopDelay(350);			        //��ʱ350us  
	if ( 0 == GET_FPGA_STAUTS )	 //�ȴ� nstauts ���
		return -1;
			
	UsNopDelay(20);			       //��ʱ 20us


	//TRACE_DEBUG_WP("FpgaLoad Start\r\n"); // ��λҳ��ַ
	page = ( FPGA_LOAD_BLOCK1==fpga_load_block ) ? (FLASH_FPGA_PAGE_START1+1) : (FLASH_FPGA_PAGE_START2+1) ;
	//TRACE_INFO_WP("Start Page:%04X.\r\n", page);

	
	CLR_FPGA_CS_PIN;      // FPGA��Ƭѡ��Ч

	WTD_CLR;
		
	CLR_FPGA_NCS1_PIN;   // ��0��ƽWE�ź���� ����FPGA�������ص�WE�ź�
	
	while (len)   
	{
		WTD_CLR;  
		read_len = (len>FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : len;
		FlashReadOnePage(page,0,p_flash_page);		//read one page
		
		for (i=0; i<read_len; i++)
		{
		   ucTmpDat = *(p_flash_page+i);
			
           #ifdef FPGA_COMPRESS 		// ѹ����ʽ�洢
              SentLoadDat(ucTmpDat); 
           #else 
              *p_ext_8 = ucTmpDat; 
           #endif  
		}            
		
		len -= read_len;
		page++;
		
	}
	
	WTD_CLR;
       //�������
	UsNopDelay(1000);			//Delay 1ms 
	
	if (GET_FPGA_CONF_DONE)  
	{     
		//TRACE_INFO_WP("CONF_DONE ==1\r\n");
		//���سɹ�,�ӳ�1ms����user mode 
		for (i=0 ;i<100; i++) 
		{
			UsNopDelay(100);  
			*p_ext_8 = 0x55;		//dummy write
		}   
		
		SET_FPGA_NCS1_PIN;
			
		return 1; 

	} 
	else
	{
		//TRACE_INFO_WP("CONF_DONE ==0\r\n");
		
		while (serial_retry--)			  //���Զ෢��CLK
		{	
			if (GET_FPGA_CONF_DONE)
			{
				//TRACE_INFO_WP("CONF_DONE ==1 @@%d\r\n",serial_retry);
				//���سɹ�,�ӳ�1ms����user mode
				for (i=0 ;i<100; i++)
				{
					UsNopDelay(50);
					*p_ext_8 = 0x55;		//dummy write
				}
				
				SET_FPGA_NCS1_PIN;
				
				return 1;		
			}
			else
			{ 
                        //  TRACE_INFO_WP("CONF_DONE ==0@@%d\r\n",serial_retry);
			}  
			 
		}  
		
		//TRACE_INFO_WP("FPGA CANNT LOAD\r\n");
		
		SET_FPGA_NCS1_PIN;
		
		return -1;
	}	
	#endif
}


/*************************************************************
Name:          GetAD9524LD      
Description:   �ж�9524�Ƿ�����
Input:         void          
Output:        void         
Return:        0:û����
               1:����
**************************************************************/
UCHAR8 GetAD9524LD()
{
//	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15);//20140906����Ϊ����


	//����E2Ϊ����
	if(Ad9524Read(0x22c)==0xe2)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


/*************************************************************
Name:          GetAD9524Refmon      
Description:   �ж�9524�ο��Ƿ�����
Input:         void          
Output:        void         
Return:        0:û����
               1:����
**************************************************************/
UCHAR8 GetAD9524Refmon()
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14);
}


/*************************************************************
Name:          GetAD9524Status      
Description:   �ж�9524�ο��Ƿ�����
Input:         void          
Output:        void         
Return:        0:û����
               1:����
**************************************************************/
UCHAR8 GetAD9524Status()
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15);
}


/*************************************************************
Name:          GetDA9122LockA      
Description:   �ж�A��9122�Ƿ�����
Input:         void          
Output:        void         
Return:        0:û����
               1:����
**************************************************************/
UCHAR8 GetDA9122LockA()
{
    UCHAR8 ret;
	   
	ret = Ad9122Read(0X0E,DA_A_FLAG);
      
	return ((0==ret&0x80)?0:1);
}


/*************************************************************
Name:          GetDA9122LockB      
Description:   �ж�B��9122�Ƿ�����
Input:         void          
Output:        void         
Return:        0:û����
               1:����
**************************************************************/
UCHAR8 GetDA9122LockB()
{
    UCHAR8 ret;
	   
	ret = Ad9122Read(0X0E,DA_B_FLAG);
      
	return ((0==ret&0x80)?0:1);
} 


/*************************************************************
Name:          SysSoftReset      
Description:   �����λ
Input:         void          
Output:        void         
Return:        0:û����
               1:����
**************************************************************/
void SysSoftReset()
{
//	NVIC_SETPRIMASK();
//	NVIC_SETFAULTMASK();
//	__set_FAULTMASK(); 
	NVIC_SystemReset();
}


/*************************************************************
Name:          GetTemperature      
Description:   ���MCU���¶�
Input:         void          
Output:        void         
Return:        �¶ȴ�С
**************************************************************/
CHAR8 GetTemperature()
{
	INT16 Temperature;
	
	Temperature= (1.42 - adc_result[8]*3.3/4096)*1000/4.35 + 25;

	return (CHAR8)Temperature;
}



/*************************************************************
Name:          SentLoadDat      
Description:   ���з��ͼ�������
Input:         Dat - ���͵��ֽ�          
Output:        void           
Return:        void       
**************************************************************/
void SentLoadDat(UCHAR8 Dat)
{
	UCHAR8 i; 
	//Ϊ�ӿ��߼�����
	//20151126�߼�����ֱ�Ӳ����Ĵ�����ַ
	volatile unsigned long *DBSRR_SFR=GPIOD_SFR_BASE_SET; 
	volatile unsigned long *DBRR_SFR=GPIOD_SFR_BASE_RESET; 
	volatile unsigned long *BBSRR_SFR=GPIOB_SFR_BASE_SET; 
	volatile unsigned long *BBRR_SFR=GPIOB_SFR_BASE_RESET; 

	for (i = 0;i<8; i++ )
	{ 

#ifdef FPGA_SOLO_LOAD	
		if ( (Dat>>i)&0x01 )
		{
           	*DBSRR_SFR = GPIO_Pin_13;
		}
		else  
       	{ 
           *DBRR_SFR = GPIO_Pin_13;
       	} 
		*BBRR_SFR = GPIO_Pin_3;	
		*BBSRR_SFR = GPIO_Pin_3;

 	   
#else
       if ( (Dat>>i)&0x01 )
       {
           *p_ext_8 = 0x01;
       }
       else  
       { 
           *p_ext_8 = 0x00;
       } 
#endif	
	}

}


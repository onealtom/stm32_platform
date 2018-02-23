/************************************************************

     Copyright (C), 2011-2111, ����̩�˿Ƽ����޹�˾
     
*************************************************************
�ļ�����   ADC_DRV_H_
�汾�ţ�   V03
���ߣ�     Τ��� 
�������ڣ� 2010��08��05��
����޸ģ� 
���������� ADC_DRV_H_�ĵײ�����ͷ�ļ� 
�����б� 
�޸����ڣ� 
        1.����:      2010��08��05��  
          ���ߣ�     Τ��� 
          �޸����ݣ� ԭ��
        2.����:      2012��04��17��   
          ���ߣ�     ����ǫ
          �޸����ݣ� ΢�͹�ǥV02 
**************************************************************/
#ifndef _GLOBAL_DRV_H_
#define _GLOBAL_DRV_H_

#define Bank1_SRAM1_ADDR    ((uint32_t)0x60000000)
#define Bank1_SRAM2_ADDR    ((uint32_t)0x64000000)
//20151126�߼�����ֱ�Ӳ����Ĵ�����ַ
#define GPIOD_SFR_BASE_SET           ((unsigned long *)0x40011410)
#define GPIOD_SFR_BASE_RESET         ((unsigned long *)0x40011414)

#define GPIOB_SFR_BASE_SET           ((unsigned long *)0x40010C10)
#define GPIOB_SFR_BASE_RESET           ((unsigned long *)0x40010C14)

#define SYS_TMP_BUFF_SIZE		(1056+512)

// variable
extern volatile unsigned char * p_ext_8;
extern volatile unsigned short * p_ext_16;
extern volatile UINT32 sys_work_info;
extern UCHAR8 sys_temp_buff[SYS_TMP_BUFF_SIZE];
extern volatile UINT32 au_send_msg;




// ϵͳ����״̬
#define SYSTEM_FLAG_1S_EVENT			(0x01<<0)	// ��ʱ��1�뵽ʱ�¼�
#define SYSTEM_FLAG_3S_EVENT			(0x01<<1)	// ��ʱ��3�뵽ʱ�¼�
#define SYSTEM_FLAG_5S_EVENT			(0x01<<2)	// ��ʱ��5�뵽ʱ�¼�
#define SYSTEM_FLAG_USB_WAIT_RX		(0x01<<3)	// USB�ȴ���������
#define SYSTEM_FLAG_USB_PKT_UNSEND	(0x01<<4)	// USB���ݵȴ����ͱ�־,����ǰ��λ��������ɺ�����
#define SYSTEM_FLAG_USB_RECE    		(0x01<<5)  	// usb һ�����ݴ���������ȴ�����
#define SYSTEM_FLAG_USB_ONCE_RX 		(0x01<<6)  	// һ�����ݰ��жϺ�������ȡ���ݣ�
#define SYSTEM_FLAG_USB_RX_END		(0x01<<7)	// ��USB���߽��յ�һ������֡
#define SYSTEM_FLAG_SET_RE_SFC		(1<<6)		// �㲥����RE��Ƶ��
#define SYSTEM_FLAG_MCU_UPDATE		(0x01<<9)	// MCU������
#define SYSTEM_FLAG_MCU_RELOAD		(0x01<<10) 	// MCU����������ɣ���������
#define SYSTEM_FLAG_FPGA_UPDATE		(0x01<<11)	// FPGA������
#define SYSTEM_FLAG_FPGA_RELOAD		(0x01<<12)	// FPGA����������ɣ����¼���
#define SYSTEM_FLAG_232_RECE			(0x01<<13)
#define SYSTEM_FLAG_UART_DEBUG		(0x01<<14)
//#define SYSTEM_FLAG_UART_TX_THR		(1<<15)		// ���ڴӴ��ڷ���͸������
#define SYSTEM_FLAG_CHECK_ID			(0x01<<16)	// ��Ҫ���RE��ID
#define SYSTEM_FLAG_LOW_POWER		(1<<17)	// �͹���ģʽ
#define SYSTEM_FLAG_ATT_ADJ			(1<<18)		// У׼״̬
#define SYSTEM_FLAG_SET_RE_UPOW		(1<<19)		// ��Ҫ��������RE�����й���
#define SYSTEM_FLAG_SET_RE_SYS_CFG		(1<<20)		// ��Ҫ��������RE��ϵͳ����:��ʱ���˲��������
#define SYSTEM_FLAG_SET_RE_TDSLOT	(1<<21)		// ��Ҫ��������RE��TDʱ϶ģʽ
#define SYSTEM_INIT_END				(1<<22)		// ϵͳ��ʼ������
#define SYSTEM_FLAG_FPGA_SAVE_THR	(1<<24)		// ���ڴ�Fpga��ȡ͸������
#define SYSTEM_FLAG_SOFT_RESET		(1<<25)		// ִ�������λ

#define SYSTEM_FLAG_REMOTE_UPDATE	(0x01<<26)	// FPGA������
#define SYSTEM_FLAG_GAIN_ADJ			(1<<27)		// ����У׼


//AU���͵���Ϣ����
//���ڹ�����Ϣ
#define AU_MSG_FLAG_GET_EU_PARA			(0x01<<0)	// ��ȡEU����
#define AU_MSG_FLAG_SET_IF_PARA			(0x01<<1)	// ���ò���
#define AU_MSG_FLAG_GET_IF_TOPO			(0x01<<2)	// ��ȡRU��TOPO
#define AU_MSG_FLAG_SET_REF_CLK_POW		(0x01<<3)	// �·�9524�Ĳο�ʱ�ӹ���


void   InitExtentBus_16(void);
void   InitExtentBus_8(void);
CHAR8  FpgaLoadAll(UINT32 len);
UCHAR8 GetAD9524LD();
UCHAR8 GetAD9524Refmon();
UCHAR8 GetAD9524Status();
UCHAR8 GetDA9122LockA();
UCHAR8 GetDA9122LockB();
void   SysSoftReset();
CHAR8  GetTemperature(); 
void SentLoadDat(UCHAR8 Dat);

#endif

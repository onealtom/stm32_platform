#ifndef _FPS_APP_H_
#define _FPS_APP_H_

// Ԥ���峣��
#define FPS_MODE_BCCH				0	// ����ִ��BCCHɨ��
#define FPS_MODE_TCH				1	// ����ִ��TCHɨ��
#define FPS_MODE_CID				2	// ����ִ��С��CID����

#define FPS_ERR_NONE				0	// �޴���
#define FPS_ERR_BCCH_RANGE		    1	// BCCHƵ�㷶Χ����
#define FPS_ERR_BCCH_TIMEOUT		2	// BCCHɨ�賬ʱ
#define FPS_ERR_TCH_FC				3	// TCHƵ�����
#define FPS_ERR_TCH_TIMEOUT		    4	// TCHɨ�賬ʱ
#define FPS_ERR_BUSY_IN_BCCH		5	// ��ǰ����ɨ��BCCH
#define FPS_ERR_BUSY_IN_TCH		    6	// ��ǰ����ɨ��TCH
#define FPS_ERR_BCCH_RESULT		    7	// BCCH�����������
#define FPS_ERR_IN_AUTO_MODE		8	// �����Զ�����ģʽ��
#define FPS_ERR_MANUAL_MODE		    9	// �����ֶ�����ģʽ��

#define FPS_RESULT_OK				0	// ����ִ�гɹ�
#define FPS_RESULT_WORK			    1	// ����ִ�гɹ�
#define FPS_RESULT_ERROR			3	// ����ִ�гɹ�

#define FPS_SCAN_ST_DONE			0	// �������
#define FPS_SCAN_ST_BCCH			1	// ��������BCCH
#define FPS_SCAN_ST_TCH			    1	// ��������TCH
#define FPS_SCAN_ST_PBCCH			2	// TCH�������,��������PBCCH
#define FPS_SCAN_ST_EDGE			3	// PBCCH�������,��������EDGEƵ��
#define FPS_SCAN_ST_CID			    4	// PBCCH�������,��������EDGEƵ��

#define FPS_AUTO_ST_NEW_SCAN		0	// ��ǰû������Ƶ��
#define FPS_AUTO_ST_BCCH			1	// ����BCCH��
#define FPS_AUTO_ST_TCH			    2	// BCCH��������,����TCH
#define FPS_AUTO_ST_CHK_BCCH		3	// ������Ƶ��,�������BCCH
#define FPS_AUTO_ST_CHK_TCH		    4	// ������Ƶ��,�������TCH
#define FPS_AUTO_ST_SCAN_CID		10	// ����CID(С����������)
#define FPS_AUTO_ERR_RANGE		    101	// ������Χ����

#define FPS_BCCH_MAX			    7	// ����BCCH���������

#define TCH_TYPE_MASK			0xCE
#define TCH_TYPE_BITMAP_0		0x00
#define TCH_TYPE_RANGE_1024	    0x80
#define TCH_TYPE_RANGE_512	    0x88
#define TCH_TYPE_RANGE_256	    0x8A
#define TCH_TYPE_RANGE_128	    0x8C
#define TCH_TYPE_BM_VARIABLE	0x8E

// ���Ͷ���
typedef struct
{
	UCHAR8 precision;	// ��ȷ��
	UINT16 fc;			// Ƶ���
	UINT16 cid;			// CIDС��ʶ����
	UINT32 power;		// ����
} _T_FPS_BCCH_INFO;

typedef struct
{
	UINT16 fps_run :1;		                    // 1-��������Ƶ��
	UINT16 cur_mode:1;		                    // �˴�ɨ��ģʽ: 0-����BCCH, 1-����TCH
	UINT16 scan_st :4;		                    // �˴�ɨ��״̬: 	bcch: 1-����ɨ��, 0-ɨ�����, 4-CID
							                    // 			tch:  1-����TCH, 2-����PBCCH, 3-����EDGE, 0-�������
	UINT16 err_st:4;		                    // �˴�ɨ�����Ĵ���״̬  

	UCHAR8 auto_scan_en;	                    // �Զ�����������ʹ��: 1-ʹ�� 
	UCHAR8 auto_state;		                    // �Զ�������״̬: 0-δѡ��BCCH, 1-�״�����BCCH, 2-����TCH, 3-ѭ����⵱ǰBCCH

	UINT16 bcch_lock;		                    // Ҫ������Ŀ��BCCH
	UCHAR8 range_sel;		                    // ��Χѡ��: 0-�ƶ�, 1-��ͨ, 2-�ƶ�, 255-�Զ�(Ĭ���ƶ�)
	
	UCHAR8 switch_count;	                    // BCCH�л�����
	_T_FPS_BCCH_INFO bcch_use;		            // ��ǰʹ�õ�BCCH
	
	UCHAR8 fc_count;		                    // ɨ�跶Χ�ڵ�Ƶ�����
	UINT16 time_out;			                // ��ǰɨ��ĳ�ʱʱ�䵹��ʱ,Ϊ0��ʱ

	UCHAR8 bcch_count;				            // ɨ���������BCCHƵ�����
	_T_FPS_BCCH_INFO bcch_lst[FPS_BCCH_MAX];	// ɨ���������BCCHƵ���б�

	UINT16 bcch_fc_sel;				            // ѡ�е�BCCH
	UCHAR8 tch_count;				            // ɨ���������TCHƵ�����
	UINT16 tch_lst[16];				            // ɨ���������TCHƵ���б�

	UCHAR8 edge_count;				            // ɨ���������EDGEƵ�����
	UINT16 edge_lst[16];				        // ɨ���������EDGEƵ���б�
} _T_FPS_STATUS;

typedef struct 
{
	UCHAR8 valid:1;			     // PBCCH��Ϣ��Ч
	UCHAR8 gprs_support:1;   	 // 1-��GPRSƵ����Ϣ, arfcn_lst_mode���������Ϣ��Ч
							     // 0-��GPRSƵ����Ϣ, arfcn_lst_mode���������Ϣ��Ч
	UCHAR8 rfl_lst_support:1;	 // 1-��RFL�б���Ϣ, rfl_count��rfl_lst������Ч
								 // 0-��RFL�б���Ϣ, ����rfl_count��rfl_lst����
	UCHAR8 arfcn_lst_mode:1;     // 1-GPRSΪƵ���б�ģʽ, arfcn_count��arfcn_lst��Ч 
							     // 0-GPRSΪλӳ��ģʽ, ma_len��ma_bm��Ч
	UCHAR8 pbcch_support:1;		 // 1-֧��PBCCHƵ��, pbcch_arfcnΪ��ЧƵ���,edge_support��Ч;
								 // 0-��֧��PBCCHƵ��, pbcch_arfcn��Ч, edge_support��Ч
	UCHAR8 edge_support:1;	     // 1-֧��EDGEƵ��
	UCHAR8 pbcch_fc_valid:1;	 // 1-��PBCCH��ARFCNƵ��, pbcch_arfcn��Ч
	UINT16 pbcch_arfcn;		     // ��10λΪPBCCHƵ���
	UCHAR8 rfl_count;	         // RFL����
	UCHAR8 rfl_lst[20];		     // RFL�б�
	UCHAR8 ma_len;		         // BITMAP����
	UCHAR8 ma_bm[8];		     // BITMAP����
	UCHAR8 arfcn_count;	         // Ƶ����������
	UCHAR8 arfcn_lst[20];		 // Ƶ�������б�
}_T_PBCCH_INFO;

typedef struct
{
	UCHAR8 cmd_mode;
	UCHAR8 ext_mode;
	UCHAR8 * p_ack_head;
} _T_FPS_REPORT;


// Function
UCHAR8 FPS_ManualStartBcch( UCHAR8 force_run, UINT16 wait_time );
UCHAR8 FPS_ManualStartTch(UINT16 bcch_fc, UCHAR8 force_run, UINT16 wait_time );
UINT16 FPS_GetAutoScanStaus( UCHAR8 * p_ret );
BOOL   FPS_GetAutoScanEn( void );
void   FPS_EnableAutoScan( void );
void   FPS_SetParam( void );
void   FPS_Init( void );
void   FPS_MainFunc( void );


#endif


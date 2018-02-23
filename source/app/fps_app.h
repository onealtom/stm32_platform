#ifndef _FPS_APP_H_
#define _FPS_APP_H_

// 预定义常量
#define FPS_MODE_BCCH				0	// 正在执行BCCH扫描
#define FPS_MODE_TCH				1	// 正在执行TCH扫描
#define FPS_MODE_CID				2	// 正在执行小区CID搜索

#define FPS_ERR_NONE				0	// 无错误
#define FPS_ERR_BCCH_RANGE		    1	// BCCH频点范围出错
#define FPS_ERR_BCCH_TIMEOUT		2	// BCCH扫描超时
#define FPS_ERR_TCH_FC				3	// TCH频点错误
#define FPS_ERR_TCH_TIMEOUT		    4	// TCH扫描超时
#define FPS_ERR_BUSY_IN_BCCH		5	// 当前正在扫描BCCH
#define FPS_ERR_BUSY_IN_TCH		    6	// 当前正在扫描TCH
#define FPS_ERR_BCCH_RESULT		    7	// BCCH搜索结果错误
#define FPS_ERR_IN_AUTO_MODE		8	// 处于自动搜索模式中
#define FPS_ERR_MANUAL_MODE		    9	// 处于手动搜索模式中

#define FPS_RESULT_OK				0	// 命令执行成功
#define FPS_RESULT_WORK			    1	// 命令执行成功
#define FPS_RESULT_ERROR			3	// 命令执行成功

#define FPS_SCAN_ST_DONE			0	// 搜索完成
#define FPS_SCAN_ST_BCCH			1	// 正在搜索BCCH
#define FPS_SCAN_ST_TCH			    1	// 正在搜索TCH
#define FPS_SCAN_ST_PBCCH			2	// TCH解析完成,正在搜索PBCCH
#define FPS_SCAN_ST_EDGE			3	// PBCCH解析完成,正在搜索EDGE频点
#define FPS_SCAN_ST_CID			    4	// PBCCH解析完成,正在搜索EDGE频点

#define FPS_AUTO_ST_NEW_SCAN		0	// 当前没有锁定频点
#define FPS_AUTO_ST_BCCH			1	// 搜索BCCH中
#define FPS_AUTO_ST_TCH			    2	// BCCH搜索结束,解析TCH
#define FPS_AUTO_ST_CHK_BCCH		3	// 已锁定频点,反复检测BCCH
#define FPS_AUTO_ST_CHK_TCH		    4	// 已锁定频点,反复检测TCH
#define FPS_AUTO_ST_SCAN_CID		10	// 搜索CID(小区锁定功能)
#define FPS_AUTO_ERR_RANGE		    101	// 搜索范围错误

#define FPS_BCCH_MAX			    7	// 搜索BCCH的最大数量

#define TCH_TYPE_MASK			0xCE
#define TCH_TYPE_BITMAP_0		0x00
#define TCH_TYPE_RANGE_1024	    0x80
#define TCH_TYPE_RANGE_512	    0x88
#define TCH_TYPE_RANGE_256	    0x8A
#define TCH_TYPE_RANGE_128	    0x8C
#define TCH_TYPE_BM_VARIABLE	0x8E

// 类型定义
typedef struct
{
	UCHAR8 precision;	// 正确率
	UINT16 fc;			// 频点号
	UINT16 cid;			// CID小区识别码
	UINT32 power;		// 功率
} _T_FPS_BCCH_INFO;

typedef struct
{
	UINT16 fps_run :1;		                    // 1-正在搜索频点
	UINT16 cur_mode:1;		                    // 此次扫描模式: 0-搜索BCCH, 1-搜索TCH
	UINT16 scan_st :4;		                    // 此次扫描状态: 	bcch: 1-正在扫描, 0-扫描完成, 4-CID
							                    // 			tch:  1-搜索TCH, 2-搜索PBCCH, 3-搜索EDGE, 0-搜索完成
	UINT16 err_st:4;		                    // 此次扫描结果的错误状态  

	UCHAR8 auto_scan_en;	                    // 自动搜索并设置使能: 1-使能 
	UCHAR8 auto_state;		                    // 自动搜索的状态: 0-未选定BCCH, 1-首次搜索BCCH, 2-解析TCH, 3-循环检测当前BCCH

	UINT16 bcch_lock;		                    // 要锁定的目标BCCH
	UCHAR8 range_sel;		                    // 范围选择: 0-移动, 1-联通, 2-移动, 255-自动(默认移动)
	
	UCHAR8 switch_count;	                    // BCCH切换次数
	_T_FPS_BCCH_INFO bcch_use;		            // 当前使用的BCCH
	
	UCHAR8 fc_count;		                    // 扫描范围内的频点个数
	UINT16 time_out;			                // 当前扫描的超时时间倒计时,为0则超时

	UCHAR8 bcch_count;				            // 扫描结果保存的BCCH频点个数
	_T_FPS_BCCH_INFO bcch_lst[FPS_BCCH_MAX];	// 扫描结果保存的BCCH频点列表

	UINT16 bcch_fc_sel;				            // 选中的BCCH
	UCHAR8 tch_count;				            // 扫描结果保存的TCH频点个数
	UINT16 tch_lst[16];				            // 扫描结果保存的TCH频点列表

	UCHAR8 edge_count;				            // 扫描结果保存的EDGE频点个数
	UINT16 edge_lst[16];				        // 扫描结果保存的EDGE频点列表
} _T_FPS_STATUS;

typedef struct 
{
	UCHAR8 valid:1;			     // PBCCH信息有效
	UCHAR8 gprs_support:1;   	 // 1-有GPRS频点信息, arfcn_lst_mode及其相关信息有效
							     // 0-无GPRS频点信息, arfcn_lst_mode及其相关信息无效
	UCHAR8 rfl_lst_support:1;	 // 1-有RFL列表信息, rfl_count和rfl_lst数据有效
								 // 0-无RFL列表信息, 忽略rfl_count和rfl_lst数据
	UCHAR8 arfcn_lst_mode:1;     // 1-GPRS为频点列表模式, arfcn_count和arfcn_lst有效 
							     // 0-GPRS为位映射模式, ma_len和ma_bm有效
	UCHAR8 pbcch_support:1;		 // 1-支持PBCCH频点, pbcch_arfcn为有效频点号,edge_support无效;
								 // 0-不支持PBCCH频点, pbcch_arfcn无效, edge_support有效
	UCHAR8 edge_support:1;	     // 1-支持EDGE频点
	UCHAR8 pbcch_fc_valid:1;	 // 1-有PBCCH的ARFCN频点, pbcch_arfcn有效
	UINT16 pbcch_arfcn;		     // 低10位为PBCCH频点号
	UCHAR8 rfl_count;	         // RFL个数
	UCHAR8 rfl_lst[20];		     // RFL列表
	UCHAR8 ma_len;		         // BITMAP长度
	UCHAR8 ma_bm[8];		     // BITMAP数据
	UCHAR8 arfcn_count;	         // 频点索引长度
	UCHAR8 arfcn_lst[20];		 // 频点索引列表
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


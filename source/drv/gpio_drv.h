/************************************************************

     Copyright (C), 2011-2111, 格兰泰克科技有限公司

*************************************************************
文件名：   GPIO_DRV_H_ 
版本号：   V03
作者：     韦瑞锦 
生成日期： 2010年08月05日
最近修改： 
功能描述： GPIO的头文件
函数列表： 
修改日期： 
        1.日期:      2010年08月05日  
          作者：     韦瑞锦 
          修改内容： 原版
        2.日期:      2012年04月17日  
          作者：     邓子谦
          修改内容： 微型光钎V02 
**************************************************************/
#ifndef _GPIO_DRV_H_
#define _GPIO_DRV_H_ 

#if 0
/*************************************************A端口的配置************************************************************************/
#define PINS_A_LNA1_VD_M	{GPIO_Pin_0, GPIO_Speed_2MHz,  GPIO_Mode_AIN}
#define PINS_RTS485A		{GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_TXD485A		{GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_RXD485A		{GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}
                                                //GPIO_Pin_4暂时不定义
//#define PINS_SPICLK			{GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
//#define PINS_MISO			{GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IPU}
//#define PINS_MOSI			{GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_WLAN_RESET		{GPIO_Pin_6, GPIO_Speed_2MHz, GPIO_Mode_Out_PP}
#define PINS_WLAN_INT		{GPIO_Pin_7, GPIO_Speed_2MHz,	GPIO_Mode_IPU}
#define PINS_FPGA_CFGDONE  	{GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_TXD232			{GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_RXD232			{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}
#define PINS_DM				{GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_AF_OD}
#define PINS_DP				{GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_USB5V			{GPIO_Pin_13, GPIO_Speed_2MHz,  GPIO_Mode_IPU}
#define PINS_AD9524_SP1		{GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_AD9524_SP0	    {GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_IPU}

#define GPIO_CFG_A  \
			PINS_A_LNA1_VD_M,\
			PINS_RTS485A,\
			PINS_TXD485A,\
			PINS_RXD485A,\
			PINS_WLAN_RESET,\
			PINS_WLAN_INT,\
			PINS_FPGA_CFGDONE,\
			PINS_TXD232,\
			PINS_RXD232,\
			PINS_DM,\
			PINS_DP,\
			PINS_USB5V,\
			PINS_AD9524_SP1,\
			PINS_AD9524_SP0
//			PINS_SPICLK,\
//			PINS_MISO,\
//			PINS_MOSI,\			
			
/**************************** USB connect*************************************/
#define PINS_DP_CONNECT		{GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_AF_OD}


/****************************************************B端口的配置*****************************************************************/
#define PINS_T_BAT			  {GPIO_Pin_0, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_1V2_T_M		  {GPIO_Pin_1, GPIO_Speed_2MHz, GPIO_Mode_AIN}
                                                 //GPIO_Pin_2上连BOOT1
#define PINS_NCS1			  {GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_AD9524_SYNC	  {GPIO_Pin_4, GPIO_Speed_2MHz,  GPIO_Mode_Out_PP}
#define PINS_AD9524_RST	  {GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
//#define PINS_AD6643_SPI_CE	  {GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_AD9524_SIP_CE    {GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_NADV			  {GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_B_AD9122_IRQ     {GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_WDI		         {GPIO_Pin_9, GPIO_Speed_50MHz,   GPIO_Mode_Out_PP}
                                                  //GPIO_Pin_10作为AD6643的SPI双向数据接口，用的时候才初始化
//#define PINS_AD6643_SPI_CLK  {GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}	
#define PINS_WLAN_MDC		{GPIO_Pin_10, GPIO_Speed_2MHz,  GPIO_Mode_Out_PP}
#define PINS_WLAN_MDIO		{GPIO_Pin_11, GPIO_Speed_2MHz,  GPIO_Mode_AF_PP}
#define PINS_AT45DB_SPI_CE	  {GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_SPICLK			{GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_MISO			{GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_MOSI			{GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
//#define PINS_AD9524_SIP_CE    {GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
                                                 //GPIO_Pin_14未连接
                                                 //GPIO_Pin_15未连接
                                                 
#define GPIO_CFG_B  \
			PINS_T_BAT,\
			PINS_1V2_T_M,\
			PINS_NCS1,\
			PINS_AD9524_SYNC,\
			PINS_AD9524_RST,\
			PINS_AD9524_SIP_CE,\
			PINS_NADV,\
			PINS_B_AD9122_IRQ,\
			PINS_WDI,\
			PINS_AT45DB_SPI_CE,\
			PINS_SPICLK,\
			PINS_MISO,\
			PINS_MOSI		
//			PINS_AD9524_SIP_CE,\
//			PINS_AD6643_SPI_CE,\
//			PINS_AD6643_SPI_CLK,\
#define PINS_AD6643_SPI_DO			//{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_Out_PP} 
#define PINS_AD6643_SPI_DI			//{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IPU}

/*******************************************************C端口的配置******************************************************************/
#define PINS_A_D_VCO_VT_M	    {GPIO_Pin_0, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_B_D_VCO_VT_M	    {GPIO_Pin_1, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_CLK_VCO_VT_M	    {GPIO_Pin_2, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_ADT_OUT		    {GPIO_Pin_3, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_A_LNA2_VD_M	    {GPIO_Pin_4, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_B_LNA1_VD_M	    {GPIO_Pin_5, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_IRQ0			    {GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_LED                        {GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_FPGA_CONFIG	    {GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_FPGA_STATUS	    {GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_TXD485_B		    {GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_RXD485_B		    {GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}
#define PINS_RTS485_B		    {GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_EN_A5V  	           {GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_A_AD9122_SPI_CE  {GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_B_AD9122_SPI_CE  {GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}

#define GPIO_CFG_C  \
			PINS_A_D_VCO_VT_M,\
			PINS_B_D_VCO_VT_M,\
			PINS_CLK_VCO_VT_M,\
			PINS_ADT_OUT,\
			PINS_A_LNA2_VD_M,\
			PINS_B_LNA1_VD_M,\
			PINS_IRQ0,\
			PINS_LED,\
			PINS_FPGA_CONFIG,\
			PINS_FPGA_STATUS,\
			PINS_RXD485_B,\
			PINS_TXD485_B,\
			PINS_RTS485_B,\
			PINS_EN_A5V,\
			PINS_A_AD9122_SPI_CE,\
			PINS_B_AD9122_SPI_CE

/*******************************************************D端口的配置************************************************************/
#define PINS_AD2			{GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD3			{GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_AF_PP} 
#define PINS_AD9524_PD		{GPIO_Pin_2, GPIO_Speed_10MHz, GPIO_Mode_Out_PP}
#define PINS_A_AQM_EN   	{GPIO_Pin_3, GPIO_Speed_10MHz, GPIO_Mode_Out_PP}
#define PINS_NWE			{GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_NRD			{GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_B_AQM_EN		{GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_FPGA_CS		{GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD13			{GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD14			{GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD15			{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_FPGA_INIT_B	   {GPIO_Pin_11,  GPIO_Speed_50MHz,  GPIO_Mode_AIN}
                                               //GPIO_Pin_12未连接
#define PINS_FPGA_DATA0			{GPIO_Pin_13,  GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_AD0			{GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD1			{GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}

#define GPIO_CFG_D  	\
			PINS_AD2,\
			PINS_AD3,\
			PINS_AD9524_PD,\
			PINS_A_AQM_EN,\
			PINS_NWE,\
			PINS_NRD,\
			PINS_B_AQM_EN,\
			PINS_FPGA_CS,\
			PINS_AD13,\
			PINS_AD14,\
			PINS_AD15,\
			PINS_FPGA_INIT_B,\
			PINS_FPGA_DATA0,\
			PINS_AD0,\
			PINS_AD1
 

/*******************************************************E端口的配置************************************************************/
#define PINS_B_AD9122_RST	     {GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_A_AD9122_RST	     {GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_A_AD9122_IRQ	     {GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_ADT_SC  	            {GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_ADT_SB	          		{GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_ADT_SA		            {GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_A_AQMPLL_EN			{GPIO_Pin_6, GPIO_Speed_2MHz, GPIO_Mode_Out_PP}
#define PINS_AD4			     {GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD5			     {GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD6			     {GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD7			     {GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD8			     {GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD9			     {GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD10			     {GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD11			     {GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD12			     {GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}

#define GPIO_CFG_E  	\
			PINS_B_AD9122_RST,\
			PINS_A_AD9122_RST,\
			PINS_A_AD9122_IRQ,\
			PINS_ADT_SC,\
			PINS_ADT_SB,\
			PINS_ADT_SA,\
			PINS_A_AQMPLL_EN,\
			PINS_AD4,\
			PINS_AD5,\
			PINS_AD6,\
			PINS_AD7,\
			PINS_AD8,\
			PINS_AD9,\
			PINS_AD10,\
			PINS_AD11,\
			PINS_AD12
#endif
/*************************************************A端口的配置************************************************************************/
//#define PINS_A_LNA1_VD_M	{GPIO_Pin_0, GPIO_Speed_2MHz,  GPIO_Mode_AIN}
//#define PINS_RTS485A		{GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}//201511051616

#define PINS_FB_SW2		{GPIO_Pin_0, GPIO_Speed_50MHz,  GPIO_Mode_Out_PP}
//#define PINS_FB_SW1		{GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_RTS485A		{GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}//201511051616

//#define PINS_TXD485A		{GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_TXD485A		{GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_AF_PP} //2014.08.19
#define PINS_RXD485A		{GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}
#define PINS_LED_RUN		{GPIO_Pin_4, GPIO_Speed_2MHz, GPIO_Mode_Out_PP}                                                //GPIO_Pin_4暂时不定义
//#define PINS_SPICLK			{GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
//#define PINS_MISO			{GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IPU}
//#define PINS_MOSI			{GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_WLAN_RESET		{GPIO_Pin_6, GPIO_Speed_2MHz, GPIO_Mode_Out_PP}
#define PINS_WLAN_INT		{GPIO_Pin_7, GPIO_Speed_2MHz,	GPIO_Mode_IPU}
#define PINS_FPGA_CFGDONE  {GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_TXD232			{GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_RXD232			{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}
#define PINS_DM				{GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_AF_OD}
#define PINS_DP				{GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_USB5V			{GPIO_Pin_13, GPIO_Speed_2MHz,  GPIO_Mode_IPU}
#define PINS_AD9524_SP1		{GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_AD9524_SP0	       {GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_IPU}

#define GPIO_CFG_A  \
			PINS_FB_SW2,\
			PINS_RTS485A,\
			PINS_TXD485A,\
			PINS_RXD485A,\
			PINS_LED_RUN,\
			PINS_WLAN_RESET,\
			PINS_WLAN_INT,\
			PINS_FPGA_CFGDONE,\
			PINS_TXD232,\
			PINS_RXD232,\
			PINS_DM,\
			PINS_DP,\
			PINS_USB5V,\
			PINS_AD9524_SP1,\
			PINS_AD9524_SP0
			
//			PINS_SPICLK,\
//			PINS_MISO,\
//			PINS_MOSI,\			
/**************************** USB connect*************************************/
#define PINS_DP_CONNECT		{GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_AF_OD}


/****************************************************B端口的配置*****************************************************************/
#define PINS_T_BAT			  {GPIO_Pin_0, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_1V2_T_M		  {GPIO_Pin_1, GPIO_Speed_2MHz, GPIO_Mode_AIN}
                                                 //GPIO_Pin_2上连BOOT1
#define PINS_NCS1			  {GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_AD9524_SYNC	  {GPIO_Pin_4, GPIO_Speed_2MHz,  GPIO_Mode_Out_PP}
#define PINS_AD9524_RST	  {GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
//#define PINS_AD6643_SPI_CE	  {GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_AD9524_SIP_CE    {GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_NADV			  {GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_B_AD9122_IRQ     {GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_WDI		         {GPIO_Pin_9, GPIO_Speed_50MHz,   GPIO_Mode_Out_PP}

//#define PINS_WLAN_MDC		{GPIO_Pin_10, GPIO_Speed_2MHz,  GPIO_Mode_Out_PP}
//#define PINS_WLAN_MDIO		{GPIO_Pin_11, GPIO_Speed_2MHz,  GPIO_Mode_AF_PP}
#define PINS_TXD232B			{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_RXD232B			{GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}
                                                  //GPIO_Pin_10作为AD6643的SPI双向数据接口，用的时候才初始化
//#define PINS_AD6643_SPI_CLK  {GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}	
#define PINS_AT45DB_SPI_CE	  {GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
//#define PINS_AD9524_SIP_CE    {GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_SPICLK			{GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_MISO			{GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_MOSI			{GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
                                                 //GPIO_Pin_14未连接
                                                 //GPIO_Pin_15未连接
#define GPIO_CFG_B  \
			PINS_T_BAT,\
			PINS_1V2_T_M,\
			PINS_NCS1,\
			PINS_AD9524_SYNC,\
			PINS_AD9524_RST,\
			PINS_AD9524_SIP_CE,\
			PINS_NADV,\
			PINS_B_AD9122_IRQ,\
			PINS_WDI,\
			PINS_TXD232B,\
			PINS_RXD232B,\
			PINS_AT45DB_SPI_CE,\
			PINS_SPICLK,\
			PINS_MISO,\
			PINS_MOSI



#define PINS_AD6643_SPI_DO			//{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_Out_PP} 
#define PINS_AD6643_SPI_DI			//{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IPU}

/*******************************************************C端口的配置******************************************************************/
#define PINS_A_D_VCO_VT_M	    {GPIO_Pin_0, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_B_D_VCO_VT_M	    {GPIO_Pin_1, GPIO_Speed_2MHz, GPIO_Mode_AIN}
//#define PINS_CLK_VCO_VT_M	    {GPIO_Pin_2, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_ADT_OUT2		    {GPIO_Pin_2, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_ADT_OUT		    {GPIO_Pin_3, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_A_LNA2_VD_M	    {GPIO_Pin_4, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_B_LNA1_VD_M	    {GPIO_Pin_5, GPIO_Speed_2MHz, GPIO_Mode_AIN}
#define PINS_IRQ0			    {GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_LED                {GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_FPGA_CONFIG	    {GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_FPGA_STATUS	    {GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_TXD485_B		    {GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
//#define PINS_OPEN_ALARM	    {GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_RXD485_B		    {GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}
#define PINS_RTS485_B		    {GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_EN_A5V  	           {GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_A_AD9122_SPI_CE  {GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_B_AD9122_SPI_CE  {GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}

#define GPIO_CFG_C  \
			PINS_A_D_VCO_VT_M,\
			PINS_B_D_VCO_VT_M,\
			PINS_ADT_OUT2,\
			PINS_ADT_OUT,\
			PINS_A_LNA2_VD_M,\
			PINS_B_LNA1_VD_M,\
			PINS_IRQ0,\
			PINS_LED,\
			PINS_FPGA_CONFIG,\
			PINS_FPGA_STATUS,\
			PINS_TXD485_B,\
			PINS_RXD485_B,\
			PINS_RTS485_B,\
			PINS_EN_A5V,\
			PINS_A_AD9122_SPI_CE,\
			PINS_B_AD9122_SPI_CE

/*******************************************************D端口的配置************************************************************/
#define PINS_AD2			{GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD3			{GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_AF_PP} 
#define PINS_AD9524_PD		{GPIO_Pin_2, GPIO_Speed_10MHz, GPIO_Mode_Out_PP}
#define PINS_A_AQM_EN   	{GPIO_Pin_3, GPIO_Speed_10MHz, GPIO_Mode_Out_PP}
#define PINS_NWE_IO		{GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_NRD			{GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_B_AQM_EN		{GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_FPGA_CS		{GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD13			{GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD14			{GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD15			{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
//#define PINS_FPGA_INIT_B	   {GPIO_Pin_11,  GPIO_Speed_50MHz,  GPIO_Mode_AIN}

#define PINS_FPGA_INIT_B	   {GPIO_Pin_11,  GPIO_Speed_50MHz,  GPIO_Mode_IPU}
#define PINS_PHY4_MDC		{GPIO_Pin_12,  GPIO_Speed_2MHz,  GPIO_Mode_Out_PP}
#define PINS_FPGA_DATA0	{GPIO_Pin_13,  GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_AD0_PS		    	{GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD1			{GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}

#define GPIO_CFG_D  	\
			PINS_AD2,\
			PINS_AD3,\
			PINS_AD9524_PD,\
			PINS_A_AQM_EN,\
			PINS_NWE_IO,\
			PINS_NRD,\
			PINS_B_AQM_EN,\
			PINS_FPGA_CS,\
			PINS_AD13,\
			PINS_AD14,\
			PINS_AD15,\
			PINS_FPGA_INIT_B,\
			PINS_PHY4_MDC,\
			PINS_FPGA_DATA0,\
			PINS_AD0_PS,\
			PINS_AD1
			
#define PINS_NWE			{GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}  
#define PINS_AD0			{GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
/*******************************************************E端口的配置************************************************************/
#define PINS_B_AD9122_RST		{GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_A_AD9122_RST		{GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_A_AD9122_IRQ	    {GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_IPU}
#define PINS_ADT_SC				{GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_ADT_SB				{GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_ADT_SA		   		{GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_Out_PP}
#define PINS_SRESET_PHY4		{GPIO_Pin_6,  GPIO_Speed_2MHz,  GPIO_Mode_Out_PP}
#define PINS_AD4				{GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD5			 	{GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD6			 	{GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD7			  	{GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD8			 	{GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD9				{GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD10			 	{GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD11				{GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}
#define PINS_AD12			  	{GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_AF_PP}

#define GPIO_CFG_E  	\
			PINS_B_AD9122_RST,\
			PINS_A_AD9122_RST,\
			PINS_A_AD9122_IRQ,\
			PINS_ADT_SC,\
			PINS_ADT_SB,\
			PINS_ADT_SA,\
			PINS_SRESET_PHY4,\
			PINS_AD4,\
			PINS_AD5,\
			PINS_AD6,\
			PINS_AD7,\
			PINS_AD8,\
			PINS_AD9,\
			PINS_AD10,\
			PINS_AD11,\
			PINS_AD12

/*控制LED的管教定义*/
#define IO_LED		GPIO_Pin_7

/*控制AD9524的CLK开关*/ 
#define CLK_PD_HIGH				GPIO_SetBits(GPIOD, GPIO_Pin_2)
#define CLK_PD_LOW				GPIO_ResetBits(GPIOD, GPIO_Pin_2)

/*控制AD9524的手动同步开关*/ 
#define ENABLE_AD9524_SYNC		GPIO_SetBits( GPIOB, GPIO_Pin_4)
#define DISABLE_AD9524_SYNC	GPIO_ResetBits( GPIOB, GPIO_Pin_4)
  
/*控制5V的电源开关*/ 
#define EnablePower5V5			GPIO_SetBits( GPIOC, GPIO_Pin_13)
#define DisablePower5V5			GPIO_ResetBits( GPIOC, GPIO_Pin_13)

/*控制A段的调制器*/   
#define SET_DSOP_A_PIN			GPIO_SetBits(GPIOD, GPIO_Pin_3)
#define CLR_DSOP_A_PIN			GPIO_ResetBits(GPIOD, GPIO_Pin_3)

/*控制B段的调制器*/
#define SET_DSOP_B_PIN			GPIO_SetBits(GPIOD, GPIO_Pin_6)
#define CLR_DSOP_B_PIN			GPIO_ResetBits(GPIOD, GPIO_Pin_6)

/*在加载FPGA时与NWE相或，产生写时钟*/
#define SET_FPGA_NCS1_PIN		GPIO_SetBits(GPIOB, GPIO_Pin_3)
#define CLR_FPGA_NCS1_PIN		GPIO_ResetBits(GPIOB, GPIO_Pin_3)

#define SET_FPGA_DATA0_PIN		GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define CLR_FPGA_DATA0_PIN		GPIO_ResetBits(GPIOD, GPIO_Pin_13)




/*FPGA加载时的信号*/
#define SET_FPGA_NCONFIG		GPIO_SetBits(GPIOC, GPIO_Pin_8)
#define CLR_FPGA_NCONFIG		GPIO_ResetBits(GPIOC, GPIO_Pin_8)

/*FPGA加载时的信号*/
#define GET_FPGA_STAUTS		GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)

/*FPGA加载时的信号*/
#define GET_FPGA_CONF_DONE	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)


/* Fpga 的复位管教 */
#define SET_FPGA_RST_PIN           do{}while(0)		   
#define CLR_FPGA_RST_PIN		   do{}while(0) 


#define SET_FPGA_CCLK_PIN			GPIO_SetBits(GPIOB, GPIO_Pin_3)
#define CLR_FPGA_CCLK_PIN			GPIO_ResetBits(GPIOB, GPIO_Pin_3)

#define SET_FPGA_PROGRAM_B_PIN		GPIO_SetBits(GPIOC, GPIO_Pin_8)
#define CLR_FPGA_PROGRAM_B_PIN		GPIO_ResetBits(GPIOC, GPIO_Pin_8)

#define SET_FPGA_DATA1_PIN			GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define CLR_FPGA_DATA1_PIN			GPIO_ResetBits(GPIOD, GPIO_Pin_13)

#define GET_FPGA_DONE_ST	    	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define GET_FPGA_INIT_B_ST	    	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)
 
#define SET_FPGA_CS_PIN				GPIO_SetBits(GPIOD, GPIO_Pin_7)
#define CLR_FPGA_CS_PIN			GPIO_ResetBits(GPIOD, GPIO_Pin_7)

 
#define FPGA_INIT_B		    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)
// 模拟I2C的IO操作  
#if 0
#define I2C_SCL_H				GPIO_SetBits( GPIOB, GPIO_Pin_10 )
#define I2C_SCL_L				GPIO_ResetBits( GPIOB, GPIO_Pin_10 )
#define I2C_SDA_H				GPIO_SetBits( GPIOB, GPIO_Pin_11 )
#define I2C_SDA_L				GPIO_ResetBits( GPIOB, GPIO_Pin_11 )
#define I2C_SDA_GET				GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_11 )
#endif
// =========================================================================================



// function=========================================
void InitGpio();
void LedFlash();
void LedOn();
void LedOff();
void ClrWtd(void);
void HardResetClkChip(void);
void HardReset9122A();
void HardReset9122B();
void EnableModulatorA(UCHAR8 enable);
void EnableModulatorB(UCHAR8 enable);
void EnableModulatorC(UCHAR8 enable);
void EnableModulatorD(UCHAR8 enable);
void Hmc1197CsEnalbe(UCHAR8 enable);

#endif


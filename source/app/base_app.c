#include "Header.h"


UCHAR8 clk_flag = CLK_FLAG_122_88M;	//ʱ�ӱ�ʾ�� 0-122.88��1-125
UCHAR8 version_number = VERSION_40M_NOIN;	//�汾��ʾ�� 0-20M���壬1-20Mһ�壬 2-40M���壬 3-40Mһ�壻



UCHAR8 aPllRegTbl[]={
	HMC830_REFDIV_02,
	HMC830_SD_CFG_06,
	HMC830_CHARGE_PUMP_09,
    HMC830_VCO_AUTO_0A,
	HMC830_PD_0B,	
	HMC830_VCO_SPI_05, 
	HMC830_VCO_SPI_05,
	HMC830_VCO_SPI_05,
	HMC830_VCO_SPI_05,
	HMC830_FRE_INT_03,
	HMC830_FRE_FRA_04, 
}; 
#if 0
const UCHAR8 ucAd9122RegVal[7][41][2][2]={//9122��DA 6649��AD
//GSM900 
{      //122.88M    //125M
	 //reg  //val  //reg  //val 
  { {0x00, 0x00}, {0x00, 0x00} },
  { {0x01, 0x00}, {0x01, 0x00} },
  { {0x03, 0x00}, {0x03, 0x00} },
  { {0x04, 0x00}, {0x04, 0x00} },
  { {0x05, 0x00}, {0x05, 0x00} },
  { {0x06, 0x48}, {0x06, 0x48} },
  { {0x07, 0x00}, {0x07, 0x00} },
  { {0x08, 0x3f}, {0x08, 0x3f} },
  { {0x0A, 0xc0}, {0x0A, 0xc0} },
  { {0x0A, 0x80}, {0x0A, 0x80} },	
  { {0x0B, 0x20}, {0x0B, 0x20} },
  { {0x0C, 0xd1}, {0x0C, 0xd1} },
  { {0x0D, 0xd9}, {0x0D, 0xd9} },
  { {0x0E, 0x88}, {0x0E, 0x88} },
  { {0x0F, 0x26}, {0x0F, 0x26} },
  { {0x10, 0x48}, {0x10, 0x48} },
  { {0x11, 0x00}, {0x11, 0x00} },
  { {0x12, 0x00}, {0x12, 0x00} },	
  { {0x13, 0x00}, {0x13, 0x00} },
  { {0x14, 0x00}, {0x14, 0x00} },
  { {0x15, 0x10}, {0x15, 0x10} },
  { {0x16, 0x03}, {0x16, 0x03} },
  { {0x17, 0x04}, {0x17, 0x04} },
  { {0x18, 0x01}, {0x18, 0x01} },
  { {0x19, 0x07}, {0x19, 0x07} },
  { {0x1B, 0x80}, {0x1B, 0x80} },
  { {0x1C, 0x00}, {0x1C, 0x00} },
  { {0x1D, 0x5a}, {0x1D, 0x5A} },
  { {0x1E, 0x24}, {0x1E, 0x24} },
  { {0x1F, 0x08}, {0x1F, 0x08} },
  { {0x30, 0x55}, {0x30, 0x04} },
  { {0x31, 0x55}, {0x31, 0x56} },
  { {0x32, 0x55}, {0x32, 0x0E} },
  { {0x33, 0x34}, {0x33, 0x2D} },
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x36, 0x01}, {0x36, 0x01} }, 
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x41, 0x01}, {0x41, 0x01} }, 
  { {0x45, 0x02}, {0x45, 0x00} },  
  { {0x46, 0x0e}, {0x46, 0x00} },
  { {0x47, 0x43}, {0x47, 0x00} },  
    
},
//WCDMA2100 
{      //122.88M               //125M
	 //reg     //val        //reg      //val
  { {0x00, 0x00}, {0x00, 0x00} },
  { {0x01, 0x10}, {0x01, 0x10} },
  { {0x03, 0x00}, {0x03, 0x00} },
  { {0x04, 0x00}, {0x04, 0x00} },
  { {0x05, 0x00}, {0x05, 0x00} },
  { {0x06, 0x48}, {0x06, 0x48} },
  { {0x07, 0x00}, {0x07, 0x00} },
  { {0x08, 0x3f}, {0x08, 0x3f} },
  { {0x0A, 0xc0}, {0x0A, 0xc0} },
  { {0x0A, 0x80}, {0x0A, 0x80} },	
  { {0x0B, 0x20}, {0x0B, 0x20} },
  { {0x0C, 0xd1}, {0x0C, 0xd1} },
  { {0x0D, 0xd9}, {0x0D, 0xd9} },
  { {0x0E, 0x88}, {0x0E, 0x88} },
  { {0x0F, 0x26}, {0x0F, 0x26} },
  { {0x10, 0x48}, {0x10, 0x48} },
  { {0x11, 0x00}, {0x11, 0x00} },
  { {0x12, 0x00}, {0x12, 0x00} },	
  { {0x13, 0x00}, {0x13, 0x00} },
  { {0x14, 0x00}, {0x14, 0x00} },
  { {0x15, 0x10}, {0x15, 0x10} },
  { {0x16, 0x03}, {0x16, 0x03} },
  { {0x17, 0x04}, {0x17, 0x04} },
  { {0x18, 0x01}, {0x18, 0x01} },
  { {0x19, 0x07}, {0x19, 0x07} },
  { {0x1B, 0x80}, {0x1B, 0x80} },
  { {0x1C, 0x00}, {0x1C, 0x00} },
  { {0x1D, 0x5A}, {0x1D, 0x5A} },
  { {0x1E, 0x24}, {0x1E, 0x24} },
  { {0x1F, 0x08}, {0x1F, 0x08} },
  { {0x30, 0x55}, {0x30, 0xBE} },
  { {0x31, 0x55}, {0x31, 0x9F} },
  { {0x32, 0x55}, {0x32, 0x1A} },
  { {0x33, 0x34}, {0x33, 0x2F} },
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x36, 0x01}, {0x36, 0x01} },  
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x41, 0x01}, {0x41, 0x01} }, 
  { {0x45, 0x02}, {0x45, 0x02} },   // ��0x04��Ϊ0x02  20130221
  { {0x46, 0x0E}, {0x46, 0x0e} },  //��0xa1��Ϊ0x0e   20130221
  { {0x47, 0x43}, {0x47, 0x43} },  //��0x43��Ϊ0x43   20130221
    
},
//TD
{      //122.88M               //125M
	 //reg     //val        //reg      //val
  { {0x00, 0x00}, {0x00, 0x00} },
  { {0x01, 0x10}, {0x01, 0x10} },
  { {0x03, 0x00}, {0x03, 0x00} },
  { {0x04, 0x00}, {0x04, 0x00} },
  { {0x05, 0x00}, {0x05, 0x00} },
  { {0x06, 0x48}, {0x06, 0x48} },
  { {0x07, 0x00}, {0x07, 0x00} },
  { {0x08, 0x3f}, {0x08, 0x3f} },
  { {0x0A, 0xc0}, {0x0A, 0xc0} },
  { {0x0A, 0x80}, {0x0A, 0x80} },	
  { {0x0B, 0x20}, {0x0B, 0x20} },
  { {0x0C, 0xd1}, {0x0C, 0xd1} },
  { {0x0D, 0xd9}, {0x0D, 0xd9} },
  { {0x0E, 0x88}, {0x0E, 0x88} },
  { {0x0F, 0x26}, {0x0F, 0x26} },
  { {0x10, 0x48}, {0x10, 0x48} },
  { {0x11, 0x00}, {0x11, 0x00} },
  { {0x12, 0x00}, {0x12, 0x00} },	
  { {0x13, 0x00}, {0x13, 0x00} },
  { {0x14, 0x00}, {0x14, 0x00} },
  { {0x15, 0x10}, {0x15, 0x10} },
  { {0x16, 0x03}, {0x16, 0x03} },
  { {0x17, 0x04}, {0x17, 0x04} },
  { {0x18, 0x01}, {0x18, 0x01} },
  { {0x19, 0x07}, {0x19, 0x07} },
  { {0x1B, 0x80}, {0x1B, 0x80} },
  { {0x1C, 0x00}, {0x1C, 0x00} },
  { {0x1D, 0x5A}, {0x1D, 0x5A} },
  { {0x1E, 0x24}, {0x1E, 0x24} },
  { {0x1F, 0x08}, {0x1F, 0x08} },
  { {0x30, 0x55}, {0x30, 0xBE} },
  { {0x31, 0x55}, {0x31, 0x9F} },
  { {0x32, 0x55}, {0x32, 0x1A} },
  { {0x33, 0x34}, {0x33, 0x2F} },
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x36, 0x01}, {0x36, 0x01} },  
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x41, 0x01}, {0x41, 0x01} }, 
  { {0x45, 0x02}, {0x45, 0x02} },   // ��0x04��Ϊ0x02  20130221
  { {0x46, 0x0E}, {0x46, 0x0e} },  //��0xa1��Ϊ0x0e   20130221
  { {0x47, 0x43}, {0x47, 0x43} },  //��0x43��Ϊ0x43   20130221
},
//CDMA 
{      //122.88M               //125M
	 //reg     //val        //reg      //val
  { {0x00, 0x00}, {0x00, 0x00} },
  { {0x01, 0x10}, {0x01, 0x10} },
  { {0x03, 0x00}, {0x03, 0x00} },
  { {0x04, 0x00}, {0x04, 0x00} },
  { {0x05, 0x00}, {0x05, 0x00} },
  { {0x06, 0x48}, {0x06, 0x48} },
  { {0x07, 0x00}, {0x07, 0x00} },
  { {0x08, 0x3f}, {0x08, 0x3f} },
  { {0x0A, 0xc0}, {0x0A, 0xc0} },
  { {0x0A, 0xe0}, {0x0A, 0xe0} },	
  { {0x0B, 0x20}, {0x0B, 0x20} },
  { {0x0C, 0xd1}, {0x0C, 0xd1} },
  { {0x0D, 0xc5}, {0x0D, 0xc5} },
  { {0x0E, 0x88}, {0x0E, 0x88} },
  { {0x0F, 0x26}, {0x0F, 0x26} },
  { {0x10, 0x48}, {0x10, 0x48} },
  { {0x11, 0x00}, {0x11, 0x00} },
  { {0x12, 0x00}, {0x12, 0x00} },	
  { {0x13, 0x00}, {0x13, 0x00} },
  { {0x14, 0x00}, {0x14, 0x00} },
  { {0x15, 0x10}, {0x15, 0x10} },
  { {0x16, 0x03}, {0x16, 0x03} },
  { {0x17, 0x04}, {0x17, 0x04} },
  { {0x18, 0x01}, {0x18, 0x01} },
  { {0x19, 0x07}, {0x19, 0x07} },
  { {0x1B, 0x80}, {0x1B, 0x80} },
  { {0x1C, 0x00}, {0x1C, 0x00} },
  { {0x1D, 0x7e}, {0x1D, 0x7e} },
  { {0x1E, 0x01}, {0x1E, 0x01} },
  { {0x1F, 0x08}, {0x1F, 0x08} },
  { {0x30, 0x00}, {0x30, 0x00} },
  { {0x31, 0x00}, {0x31, 0x00} },
  { {0x32, 0x00}, {0x32, 0x00} },
  { {0x33, 0xb0}, {0x33, 0xb0} },
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x36, 0x01}, {0x36, 0x01} }, 
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x41, 0x01}, {0x41, 0x01} },
  { {0x45, 0x01}, {0x45, 0x01} },   
  { {0x46, 0xa0}, {0x46, 0xa0} },
  { {0x47, 0x42}, {0x47, 0x42} },  
    
},
//DCS1800
{      //122.88M               //125M
	 //reg     //val        //reg      //val
  { {0x00, 0x00}, {0x00, 0x00} },
  { {0x01, 0x10}, {0x01, 0x10} },
  { {0x03, 0x00}, {0x03, 0x00} },
  { {0x04, 0x00}, {0x04, 0x00} },
  { {0x05, 0x00}, {0x05, 0x00} },
  { {0x06, 0x48}, {0x06, 0x48} },
  { {0x07, 0x00}, {0x07, 0x00} },
  { {0x08, 0x3f}, {0x08, 0x3f} },
  { {0x0A, 0xc0}, {0x0A, 0xc0} },
  { {0x0A, 0x80}, {0x0A, 0x80} },	
  { {0x0B, 0x20}, {0x0B, 0x20} },
  { {0x0C, 0xd1}, {0x0C, 0xd1} },
  { {0x0D, 0xd9}, {0x0D, 0xc5} },
  { {0x0E, 0x88}, {0x0E, 0x88} },
  { {0x0F, 0x26}, {0x0F, 0x26} },
  { {0x10, 0x48}, {0x10, 0x48} },
  { {0x11, 0x00}, {0x11, 0x00} },
  { {0x12, 0x00}, {0x12, 0x00} },	
  { {0x13, 0x00}, {0x13, 0x00} },
  { {0x14, 0x00}, {0x14, 0x00} },
  { {0x15, 0x10}, {0x15, 0x10} },
  { {0x16, 0x03}, {0x16, 0x03} },
  { {0x17, 0x04}, {0x17, 0x04} },
  { {0x18, 0x01}, {0x18, 0x01} },
  { {0x19, 0x07}, {0x19, 0x07} },
  { {0x1B, 0x80}, {0x1B, 0x80} },
  { {0x1C, 0x00}, {0x1C, 0x00} },
  { {0x1D, 0x5A}, {0x1D, 0x5A} },
  { {0x1E, 0x24}, {0x1E, 0x24} },
  { {0x1F, 0x08}, {0x1F, 0x08} },
  { {0x30, 0x55}, {0x30, 0xBE} },
  { {0x31, 0x55}, {0x31, 0x9F} },
  { {0x32, 0x55}, {0x32, 0x1A} },
  { {0x33, 0x34}, {0x33, 0x2F} },
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x36, 0x01}, {0x36, 0x01} },
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x41, 0x01}, {0x41, 0x01} },
  { {0x45, 0x02}, {0x45, 0x04} },    
  { {0x46, 0x0E}, {0x46, 0xa1} },
  { {0x47, 0x43}, {0x47, 0x42} }, 
  
    
},
//CMMB   
{      //122.88M               //125M
	 //reg     //val        //reg      //val
  { {0x00, 0x00}, {0x00, 0x00} },
  { {0x01, 0x10}, {0x01, 0x10} },
  { {0x03, 0x00}, {0x03, 0x00} },
  { {0x04, 0x00}, {0x04, 0x00} },
  { {0x05, 0x00}, {0x05, 0x00} },
  { {0x06, 0x48}, {0x06, 0x48} },
  { {0x07, 0x00}, {0x07, 0x00} },
  { {0x08, 0x3f}, {0x08, 0x3f} },
  { {0x0A, 0xc0}, {0x0A, 0xc0} },
  { {0x0A, 0xe0}, {0x0A, 0xe0} },	
  { {0x0B, 0x20}, {0x0B, 0x20} },
  { {0x0C, 0xd1}, {0x0C, 0xd1} },
  { {0x0D, 0xc5}, {0x0D, 0xc5} },
  { {0x0E, 0x88}, {0x0E, 0x88} },
  { {0x0F, 0x26}, {0x0F, 0x26} },
  { {0x10, 0x48}, {0x10, 0x48} },
  { {0x11, 0x00}, {0x11, 0x00} },
  { {0x12, 0x00}, {0x12, 0x00} },	
  { {0x13, 0x00}, {0x13, 0x00} },
  { {0x14, 0x00}, {0x14, 0x00} },
  { {0x15, 0x10}, {0x15, 0x10} },
  { {0x16, 0x03}, {0x16, 0x03} },
  { {0x17, 0x04}, {0x17, 0x04} },
  { {0x18, 0x01}, {0x18, 0x01} },
  { {0x19, 0x07}, {0x19, 0x07} },
  { {0x1B, 0x80}, {0x1B, 0x80} },
  { {0x1C, 0x00}, {0x1C, 0x00} },
  { {0x1D, 0x7e}, {0x1D, 0x7e} },
  { {0x1E, 0x01}, {0x1E, 0x01} },
  { {0x1F, 0x08}, {0x1F, 0x08} },
  { {0x30, 0x01}, {0x30, 0x00} },
  { {0x31, 0x02}, {0x31, 0x00} },
  { {0x32, 0x03}, {0x32, 0x00} },
  { {0x33, 0xb0}, {0x33, 0xb0} },
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x36, 0x01}, {0x36, 0x01} }, 
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x41, 0x01}, {0x41, 0x01} },  
  { {0x45, 0x01}, {0x45, 0x01} },   
  { {0x46, 0xa0}, {0x46, 0xa0} },
  { {0x47, 0x42}, {0x47, 0x42} },  
  
 },

//tetra ��Ⱥ  
{      //122.88M               //125M
	 //reg     //val        //reg      //val
  { {0x00, 0x00}, {0x00, 0x00} },
  { {0x01, 0x10}, {0x01, 0x10} },
  { {0x03, 0x00}, {0x03, 0x00} },
  { {0x04, 0x00}, {0x04, 0x00} },
  { {0x05, 0x00}, {0x05, 0x00} },
  { {0x06, 0x48}, {0x06, 0x48} },
  { {0x07, 0x00}, {0x07, 0x00} },
  { {0x08, 0x3f}, {0x08, 0x3f} },
  { {0x0A, 0xc0}, {0x0A, 0xc0} },
  { {0x0A, 0x80/*RJ 0xe0*/}, {0x0A, 0xe0} },	
  { {0x0B, 0x20}, {0x0B, 0x20} },
  { {0x0C, 0xd1}, {0x0C, 0xd1} },
  { {0x0D, 0xD9/*RJ 0xc5*/}, {0x0D, 0xc5} },
  { {0x0E, 0x88}, {0x0E, 0x88} },
  { {0x0F, 0x26}, {0x0F, 0x26} },
  { {0x10, 0x48}, {0x10, 0x48} },
  { {0x11, 0x00}, {0x11, 0x00} },
  { {0x12, 0x00}, {0x12, 0x00} },	
  { {0x13, 0x00}, {0x13, 0x00} },
  { {0x14, 0x00}, {0x14, 0x00} },
  { {0x15, 0x10}, {0x15, 0x10} },
  { {0x16, 0x03}, {0x16, 0x03} },
  { {0x17, 0x04}, {0x17, 0x04} },
  { {0x18, 0x01}, {0x18, 0x01} },
  { {0x19, 0x07}, {0x19, 0x07} },
  { {0x1B, 0x80}, {0x1B, 0x80} },
  { {0x1C, 0x00}, {0x1C, 0x00} },
  { {0x1D, 0x5A}, {0x1D, 0x7e} },
  { {0x1E, 0x24}, {0x1E, 0x01} },
  { {0x1F, 0x08}, {0x1F, 0x08} },
  { {0x30, 0x55}, {0x30, 0x05} },
  { {0x31, 0x55}, {0x31, 0x06} },
  { {0x32, 0x55}, {0x32, 0x07} },
  { {0x33, 0x34}, {0x33, 0xb8} },
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x36, 0x01}, {0x36, 0x01} }, 
  { {0x36, 0x00}, {0x36, 0x00} },
  { {0x41, 0x01}, {0x41, 0x01} },  
  { {0x45, 0x01}, {0x45, 0x01} },   
  { {0x46, 0xa0}, {0x46, 0xa0} },
  { {0x47, 0x42}, {0x47, 0x42} },  
  
 },

};
      
// GSM900�ƶ��α�������
const UINT32 GsmCnmobilePll[]=
{
         //MIXER             //MOEND 
     //122.88    //125M    //122.88      //125M  
	0x000002,  0x000002,   0x000002,    0x000002,   //02
	0x002F4A,  0x002F4A,   0x002F4A,	0x002FCA,   //06
	0x479E3D,  0x479E3D,   0x479E3D,    0x479E3D,   //09
    0xFAAAFFFF,0xFAAAFFFF, 0xFAAAFFFF,  0xFAAAFFFF, //0a -��Ĭ��ֵ
	0xFAAAFFFF,0xFAAAFFFF, 0xFAAAFFFF,  0xFAAAFFFF, //0b -��Ĭ��ֵ	
	0x00F80D,  0x00F80D,   0x00F80D,    0x00F80D,   //05
	0x00AB95,  0x00AB95,   0x00AB95,    0x00AB95,   //05
	0x00D11D,  0x00D11D,   0x00D11D,    0x00D11D,   //05
	0x000005,  0x000005,   0x000005,    0x000005,   //05
	0x000023,  0x000023,   0x000018,    0x000018,   //03
	0xAA0000,  0x24DD2F,   0x61AAAA,    0x000000,   //04
 
}; 

// GSM900��ͨ�α�������
const UINT32 GsmUnicomPll[]=
{
         //MIXER               //MOEND 
     //122.88    //125M     //122.88     //125M  
	0x000002,  0x000002,   0x000002,    0x000002,   //02
	0x002F4A,  0x002F4A,   0x002F4A,	0x002F4A,   //06
	0x479E3D,  0x479E3D,   0x479E3D,    0x479E3D,   //09
    0xFAAAFFFF,0xFAAAFFFF, 0xFAAAFFFF,  0xFAAAFFFF, //0a -��Ĭ��ֵ
	0xFAAAFFFF,0xFAAAFFFF, 0xFAAAFFFF,  0xFAAAFFFF, //0b -��Ĭ��ֵ	
	0x00F80D,  0x00F80D,   0x00F80D,    0x00F80D,   //05
	0x00AB95,  0x00AB95,   0x00AB95,    0x00AB95,   //05
	0x00D11D,  0x00D11D,   0x00D11D,    0x00D11D,   //05
	0x000005,  0x000005,   0x000005,    0x000005,   //05
	0x000024,  0x000023,   0x000018,    0x000018,   //03
	0x270000,  0x9FBE76,   0xDEAAAA,    0xDEAAAA,   //04

};

// DCS1800�ƶ��α�������
const UINT32 DcsCnmobilePll[]=
{
         //MIXER                                 //MOEND 
     //122.88           //125M              //122.88           //125M  
	0x000002,  0x000002,   0x000002,    0x000002,   //02
	0x002F4A,  0x002F4A,   0x002F4A,	0x002F4A,   //06
	0x479E3D,  0x479020,   0x479E3D,    0x479020,   //09
    0xFAAAFFFF,0xFAAAFFFF, 0xFAAAFFFF,  0xFAAAFFFF, //0a -��Ĭ��ֵ
	0xFAAAFFFF,0xFAAAFFFF, 0xFAAAFFFF,  0xFAAAFFFF, //0b -��Ĭ��ֵ	
	0x00E80D,  0x00E80D,   0x00E80D,    0x00E80D,   //05
	0x00AB95,  0x00AB95,   0x00AB95,    0x00AB95,   //05
	0x00D11D,  0x00D11D,   0x00D11D,    0x00D11D,   //05
	0x000005,  0x000005,   0x000005,    0x000005,   //05
	0x000020,  0x00001F,   0x000019,    0x000019,   //03
	0x148000,  0x941205,   0xA00000,    0x30BE0D,  //04
};

// DCS1800��ͨ�α�������
const UINT32 DcsUnicomPll[]=
{
         //MIXER                                 //MOEND 
     //122.88           //125M              //122.88           //125M  
	0x000002,  0x000002,   0x000002,    0x000002,   //02
	0x002F4A,  0x002F4A,   0x002F4A,	0x002F4A,   //06
	0x479E3D,  0x479020,   0x479E3D,    0x479020,   //09
    0xFAAAFFFF,0xFAAAFFFF, 0xFAAAFFFF,  0xFAAAFFFF, //0a -��Ĭ��ֵ
	0xFAAAFFFF,0xFAAAFFFF, 0xFAAAFFFF,  0xFAAAFFFF, //0b -��Ĭ��ֵ	
	0x00E80D,  0x00E80D,   0x00E80D,    0x00E80D,   //05
	0x00AB95,  0x00AB95,   0x00AB95,    0x00AB95,   //05
	0x00D11D,  0x00D11D,   0x00D11D,    0x00D11D,   //05
	0x000005,  0x000005,   0x000005,    0x000005,   //05
	0x000020,  0x00001F,   0x000019,    0x000019,   //03
	0x72AAAA,  0xF0A3D7,   0xFE2AAA,    0x8D4FDF,   //04
    
};

//Mixer��Ƶ���ļĴ�������
//�б�ʾ��������ʽ���б�ʾ�Ĵ���ֵ������ʾ122.88��125M����������122.88�����еĵ�һ��
UINT32  auiPllRegVlaue[7][11][2][2]={   
//GSM900 
            //MIXER                                     //MOEND
      //122.88            //125M                //122.88           //125M 
{
	{ {0x02,    0x02},	      {0x02,      0x02},      },        //02
	{ {0x2F4A,  0x2F4A},      {0x2F4A,	  0x02},      },        //06
	{ {0x479E3D,0x479E3D},    {0x479E3D,  0x479E3D},  },        //09
    { {0x2046,  0x2046},      {0x2046,    0x2046},    },        //0a
	{ {0x7c061, 0x7c061},     {0x7c061,   0x7c061},   },        //0b	
	{ {0xE80D,  0xE80D},      {0xE80D,    0xE80D},    },        //05
	{ {0xAB95,  0xAB95},      {0xAB95,    0xAB95},    },        //05
	{ {0xD11D,  0xD11D},      {0xD11D,    0xD11D},    },        //05
	{ {0x05,    0x05},        {0x05,      0x05},      },        //05
	{ {0x1D,   	0x17},        {0x25,   	  0x23},      },        //03
	{ {0x84AAA,0xCCCCCC},     {0x118000,  0xA3D70},   },        //04
},       

//WCDMA2100   
      		 //MIXER                                    //MOEND
		//122.88            //125M                    	//122.88           		//125M
{
	{ {0x02,    	0x02},	      	{0x02,      	0x02},      },   	//02
	{ {0x2F4A,  	0x2F4A},      	{0x2F4A,		0x2F4A},    },     	//06
	{ {0x479E3D,	0x479020},    	{0x479E3D,  	0x479020},  },     	//09
    { {0xFAAAFFFF,	0xFAAAFFFF},	{0xFAAAFFFF,	0xFAAAFFFF},}, 		//0a -��Ĭ��ֵ
	{ {0xFAAAFFFF,	0xFAAAFFFF},	{0xFAAAFFFF, 	0xFAAAFFFF},},  	//0b -��Ĭ��ֵ	
	{ {0xE80D,  	0xE80D},      	{0xE80D,    	0xE80D},    },    	//05
	{ {0xAB95,  	0xAB95},      	{0xAB95,    	0xAB95},    },   	//05
	{ {0xD11D,  	0xD11D},      	{0xD11D,    	0xD11D},    }, 		//05
	{ {0x05,    	0x05},        	{0x05,      	0x05},      },   	//05
	{ {0x25,   		0x24},        	{0x1D,   	  	0x1C},      },   	//03
	{ {0x698000,	0xD1EB85},    	{0x692AAA,  	0xE978D4},  },   	//04
},

//TD
      		//MIXER                  //MOEND
	//122.88      //125M       //122.88    //125M
{
	{ {0x02,    0x02},	      {0x04,      0x02},      		},        //02
	{ {0x2F4A,  0x2F4A},      {0x04,	  0x2F4A},   		},        //06
	{ {0x479E3D,0x479020},    {0x479E3D,  0x479020},  		},        //09
    { {0xFAAAFFFF,0xFAAAFFFF},{0xFAAAFFFF,  0xFAAAFFFF}, 	},//0a -��Ĭ��ֵ
	{ {0xFAAAFFFF,0xFAAAFFFF},{0xFAAAFFFF,  0xFAAAFFFF}, 	}, //0b -��Ĭ��ֵ	
	{ {0xE80D,  0xE80D},      {0xE80D,    0xE80D},    		},        //05
	{ {0xAB95,  0xAB95},      {0xAB95,    0xAB95},    		},        //05
	{ {0xD11D,  0xD11D},      {0xD11D,    0xD11D},    		},        //05
	{ {0x05,    0x05},        {0x05,      0x05},      		},        //05
	{ {0x18,   	0x22},        {0x47,   	  0x1D},      		},        //03
	{ {0x4CAAAA,0xC74538},    {0x200000,  0xE90FF9},  		},         //04
},

//CDMA
       		//MIXER                                    //MOEND
	  //122.88            //125M                    //122.88           //125M
{
	{ {0x02,    0x02},	      {0x04,      0x02},      },        //02
	{ {0x2F4A,  0x2F4A},      {0x04,	  0x02},      },        //06
	{ {0x479E3D,0x479E3D},    {0x479E3D,  0x479E3D},  },        //09
    { {0x2046,  0x2046},      {0x2046,    0x2046},    },        //0a
	{ {0x7c061, 0x7c061},     {0x7c061,   0x7c061},   },        //0b	
	{ {0xF80D,  0xF80D},      {0xF80D,    0xF80D},    },        //05
	{ {0xAB95,  0xAB95},      {0xAB95,    0xAB95},    },        //05
	{ {0xD11D,  0xD11D},      {0xD11D,    0xD11D},    },        //05
	{ {0x05,    0x05},        {0x05,      0x05},      },        //05
	{ {0x18,   	0x17},        {0x47,   	  0x23},      },        //03
	{ {0x4CAAAA,0xCCCCCC},    {0x200000,  0xA3D70},  },         //04
},
 
//DCS1800 
           //MIXER                                                 //MOEND
      //122.88            //125M                           //122.88            //125M
{
	{ {0x02,    0x02},	      {0x02,      0x02},      },        //02
	{ {0x2F4A,  0x2F4A},      {0x2F4A,	  0x02},      },        //06
	{ {0x479E3D,0x479E3D},    {0x479E3D,  0x479E3D},  },        //09
    { {0x2046,  0x2046},      {0x2046,    0x2046},    },        //0a
	{ {0x7c061, 0x7c061},     {0x7c061,   0x7c061},   },        //0b	
	{ {0xE80D,  0xE80D},      {0xE80D,    0xE80D},    },        //05
	{ {0xAB95,  0xAB95},      {0xAB95,    0xAB95},    },        //05
	{ {0xD11D,  0xD11D},      {0xD11D,    0xD11D},    },        //05
	{ {0x05,    0x05},        {0x05,      0x05},      },        //05
	{ {0x1D,   	0x17},        {0x25,   	  0x23},      },        //03
	{ {0x84AAA,0xCCCCCC},     {0x118000,  0xA3D70},   },        //04
}, 
 
//CMMB
             //MIXER                                    //MOEND
      //122.88            //125M                    //122.88           //125M
{
	{ {0x02,    0x02},	      {0x04,      0x02},      },        //02
	{ {0x2F4A,  0x2F4A},      {0x04,	  0x02},      },        //06
	{ {0x479E3D,0x479E3D},    {0x479E3D,  0x479E3D},  },        //09
    { {0x2046,  0x2046},      {0x2046,    0x2046},    },        //0a
	{ {0x7c061, 0x7c061},     {0x7c061,   0x7c061},   },        //0b	
	{ {0xF80D,  0xF80D},      {0xF80D,    0xF80D},   },         //05
	{ {0xAB95,  0xAB95},      {0xAB95,    0xAB95},    },        //05
	{ {0xD11D,  0xD11D},      {0xD11D,    0xD11D} ,   },        //05
	{ {0x05,    0x05},        {0x05,      0x05},      },        //05
	{ {0x18,   	0x17},        {0x47,   	  0x23},      },        //03
	{ {0x4CAAAA,0xCCCCCC},    {0x200000,  0xA3D70},   },        //04
},

//Tetra��Ⱥ
           //MIXER                                    //MOEND
    //122.88            //125M                    //122.88           //125M
{
	{ {0x02,    0x02},	      {0x02,      0x02},      },        //02
	{ {0xB4A,   0x2F4A},      {0xB4A,	  0x02},      },        //06
	{ {0x5E3C78,0x479E3D},    {0x5E3C78,  0x479E3D},  },        //09
    { {0x2046,  0x2046},      {0x2046,    0x2046},    },        //0a
	{ {0x7c061, 0x7c061},     {0x7c061,   0x7c061},   },        //0b	
	{ {0xF88,   0xF80D},      {0xF88,     0xF80D},    },        //05
	{ {0xe210,  0xAB95},      {0xe410,    0xAB95},    },        //05
	{ {0x2818,  0xD11D},      {0x2818,    0xD11D} ,   },        //05
	{ {0x00,    0x05},        {0x00,      0x05},      },        //05
	{ {0x22,   	0x17},        {0x1A,   	  0x23},      },        //03
	{ {0xAA5555,0xCCCCCC},    {0xC20000,  0xA3D70},   },        //04

}, 

}; 
#endif 

/*************************************************************
Name:LoadGsmPllRegTbl           
Description:��ʼ��PLL
Input:
	fb_flag: ǰ��˱�־
	ab_flag: AB�α�־
Output:void       
Return:
	b_FALSE: ʧ��
	b_TRUE:  �ɹ�             
**************************************************************/
 void LoadGsmPllRegTbl(u8 G2Tpye)
 {
    if ( G2_TYPE_CNMOBILE == G2Tpye)
    {
     //  MenCpy(auiPllRegVlaue[0], GsmCnmobilePll, 44*4);
    } 
    else  
    {
      // MenCpy(auiPllRegVlaue[0], GsmUnicomPll, 44*4);
    } 
 } 
 
/*************************************************************
Name:Init_Local_Pll           
Description:��ʼ��PLL
Input:
	fb_flag: ǰ��˱�־
	ab_flag: AB�α�־
Output:void       
Return:
	b_FALSE: ʧ��
	b_TRUE:  �ɹ�             
**************************************************************/
 void LoadDcsPllRegTbl(u8 G2Tpye)
 {
   #if 1
    if ( G2_TYPE_CNMOBILE == G2Tpye)
    {
    //  MenCpy((u8*)auiPllRegVlaue[4], (u8*)DcsCnmobilePll, 44*4);

    }
    else 
    {
     // MenCpy((u8*)auiPllRegVlaue[4], (u8*)DcsUnicomPll, 44*4);
    }
   #endif
 }


/*************************************************************
Name:Init_Local_Pll           
Description:��ʼ��PLL
Input:
	fb_flag: ǰ��˱�־
	ab_flag: AB�α�־
Output:void       
Return:
	b_FALSE: ʧ��
	b_TRUE:  �ɹ�             
**************************************************************/
BOOL Init_Local_Pll(UCHAR8 ucPll)//822 U PLL
{
#if 0
    UCHAR8  ucFmt ;
    UCHAR8  ucPllTye ;
    UCHAR8  i;

    if (A_MIXER==ucPll ||A_MODEN==ucPll)
    {
       ucFmt  = fpga_cfg.a_net_type;
    }
    else
	{
        ucFmt = fpga_cfg.b_net_type;
		if ( NET_DIVE==ucFmt )
		{
			ucFmt = fpga_cfg.a_net_type;
		}
	}

	if ( NET_NONE==ucFmt ) return;
    
    if (A_MIXER==ucPll ||B_MIXER==ucPll)
    {
       ucPllTye = TYPE_MIXER; 
    }
    else
    {
       ucPllTye = TYPE_MODEN; 
    }

	FPGA_ENABLE_WRITE;

#if ((A_NETWORK_TYPE == NET_TYPE_GSM900)||(B_NETWORK_TYPE == NET_TYPE_GSM900))
	LoadGsmPllRegTbl(G2Tpye);         
#elif ((A_NETWORK_TYPE == NET_TYPE_DCS1800)||(B_NETWORK_TYPE == NET_TYPE_DCS1800))
	LoadDcsPllRegTbl(G2Tpye);      
#endif	

	for (i=0;i<11;i++)
	{
    	ReadWriteHmc830(ucPll,0,aPllRegTbl[i],auiPllRegVlaue[ucFmt][i][ucPllTye][clk_flag]);
	} 
	FPGA_DISABLE_WRITE;
#endif	
	return b_TRUE; 
}

/*************************************************************
Name: TdSysCalcFreqWord
Description: ����Ƶ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:Ƶ���ּĴ�����ֵ
**************************************************************/
INT32 SearchFpCalcFreqWord( INT32 freq_code, UCHAR8 Flag,INT32 *up_fre_word,INT32 *down_fre_word )
{



	FLOAT32 PllOutfreq; 
	INT32   freq_word = 0; 
	UCHAR8  ucFormat;
	FLOAT32 fpga_data_clk;

	FLOAT32  up_fre = 0,down_fre = 0;
#if 0

	*up_fre_word = 0;
	*down_fre_word = 0;
	
	if ( SYS_A_FLAG == Flag)
	{
		ucFormat = fpga_cfg.a_net_type;
		fpga_data_clk = fpga_cfg.a_fpga_data_clk;
	} 
	else if ( SYS_B_FLAG == Flag) 
	{
		ucFormat = fpga_cfg.b_net_type;
		fpga_data_clk = fpga_cfg.b_fpga_data_clk;
	}
	else if ( SYS_C_FLAG == Flag) 
	{
		ucFormat = fpga_cfg.c_net_type;
		fpga_data_clk = fpga_cfg.c_fpga_data_clk;
	}
	else if ( SYS_D_FLAG == Flag) 
	{
		ucFormat = fpga_cfg.d_net_type;
		fpga_data_clk = fpga_cfg.d_fpga_data_clk;
	}
	
	WTD_CLR;
	
	TRACE_INFO("SetChannel (Flag=%d)---------------------ucFormat= %04X,freq_code=[%x]\r\n",Flag,ucFormat,freq_code);
	switch ( ucFormat )  
	{
		case NET_TYPE_GSM900:   
			if ( ((freq_code>=0)&& (freq_code<=95)) ||((freq_code>=1000)&& (freq_code<=1023)) )
			{
           		//PllOutfreq =  clk_flag ? GSM_PLL_DL_OUT_150M_CNMOBILE : GSM_PLL_DL_OUT_122M_CNMOBILE; //��������ı������Ƶ��
				down_fre= GSM_PLL_DL_OUT_150M_CNMOBILE;	
				up_fre= GSM_PLL_UL_OUT_150M_CNMOBILE;
			}
			else
            	;//PllOutfreq =  clk_flag ? GSM_PLL_DL_OUT_125M_UNICOM : GSM_PLL_DL_OUT_122M_UNICOM; //��������ı������Ƶ��

			
			//freq_word  =  SearchFpCalcGsmFreqWord( freq_code, up_fre, down_fre , up_fre_word,down_fre_word );	
			freq_word  =  CalcGsmFreqWord( freq_code,fpga_data_clk,up_fre, down_fre , up_fre_word,down_fre_word );	
		break;       
				 
		case NET_TYPE_DCS1800: 

			if ((freq_code>=DCS_MIN_FRE_CODE_CNMOBILE)&& (freq_code<=DCS_MAX_FRE_CODE_CNMOBILE))
			{
				down_fre =   DCS_PLL_DL_OUT_150M_CNMOBILE;  //��������ı������Ƶ��
				up_fre =   DCS_PLL_UL_OUT_150M_CNMOBILE;  //��������ı������Ƶ��
			}else if ((freq_code>=DCS_MIN_FRE_CODE_UNICOM)&& (freq_code<=DCS_MAX_FRE_CODE_UNICOM))
			{
				down_fre =   DCS_PLL_DL_OUT_150M_UNICOM;  //��������ı������Ƶ��
				up_fre =   DCS_PLL_UL_OUT_150M_UNICOM;  //��������ı������Ƶ��
			}
			CalcDcsFreqWord( freq_code,fpga_data_clk, up_fre, down_fre, up_fre_word,down_fre_word );

		break; 
				
		case NET_TYPE_WCDMA2100:
            		CalcWcdmaPLLoutputFreq(&up_fre,&down_fre); //��������ı������Ƶ��           
			CalcWcdmaFreqWord( freq_code, fpga_data_clk,up_fre,down_fre, up_fre_word,down_fre_word);
			TRACE_INFO("WCDMA2100 (PllOutfreq=%f)---------------------freq_word= %04X,freq_code= %04X\r\n",PllOutfreq,freq_word,freq_code);
			WcdmaFreqWordConfigureTxRxPll( up_fre,down_fre );
			
		break; 
		 
		case NET_TYPE_TD: 
			clk_flag=1;
			down_fre=  clk_flag ? TD_SCDMA_PLL_DL_OUT_150M : TD_SCDMA_PLL_DL_OUT_122M; //��������ı������Ƶ��
			up_fre 	=  clk_flag ? TD_SCDMA_PLL_UL_OUT_150M : TD_SCDMA_PLL_DL_OUT_122M; //��������ı������Ƶ��
			*up_fre_word	=   SearchFpCalcTDFreqWord( freq_code, up_fre);
			*down_fre_word  =   SearchFpCalcTDFreqWord( freq_code, down_fre);
			//*up_fre_word =*down_fre_word= freq_word;
		  	
		break; 
		
		case NET_TYPE_CDMA:
		  	
		break; 	 
		
		case NET_TYPE_CMMB: 

		break; 	 
		
	    case NET_TYPE_TETRA:   
			//PllOutfreq =  clk_flag ? TETRA_PLL_DL_OUT_125M : TETRA_PLL_DL_OUT_122M; //��������ı������Ƶ��
			//freq_word  =  CalcTetraFreqWord( freq_code, PllOutfreq );	
			down_fre =  TETRA_PLL_DL_FRQ;
			up_fre = TETRA_PLL_UL_FRQ;
			CalcTetraFreqWord( freq_code, fpga_data_clk,up_fre, down_fre , up_fre_word,down_fre_word );
		break; 

	    case NET_TYPE_LTE_TD:   
            		PllOutfreq =   CalcLteTdPLLoutputFreq(Flag); //��������ı������Ƶ��
			freq_word  =  CalcLteTdFreqWord( freq_code, PllOutfreq );	 
			LteTdFreqWordConfigureTxRxPll( PllOutfreq,Flag);
		break; 
		
	    case NET_TYPE_LTE_FDD:   
            		PllOutfreq =   CalcLteFddPLLoutputFreq(Flag); //��������ı������Ƶ��           
			freq_word  = CalcLteFddFreqWord( freq_code, PllOutfreq );	
			TRACE_INFO("CalcLteFdd (PllOutfreq=%f)---------------------freq_word= %04X,freq_code= %04X\r\n",PllOutfreq,freq_word,freq_code);
			LteFddFreqWordConfigureTxRxPll( PllOutfreq,Flag);
		break;
		
		case NET_TYPE_CDMA800: 
			CalcCdma800FreqWord( freq_code, fpga_data_clk,up_fre, down_fre, up_fre_word,down_fre_word );	   
			break; 

	    default:
			TRACE_ERROR("Err net type.");
	    break; 
		   
	}
#endif
	freq_word = CalcFreqWord( freq_code ,Flag,up_fre_word,down_fre_word);
	return freq_word;
}

/*************************************************************
Name: CalcFreqWord
Description: ����Ƶ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:Ƶ���ּĴ�����ֵ
**************************************************************/
INT32 CalcFreqWord( INT32 freq_code, UCHAR8 Flag,INT32 *up_fre_word,INT32 *down_fre_word )
{

	FLOAT32 PllOutfreq; 
	INT32   freq_word = 0; 
	UCHAR8  ucFormat;
	FLOAT32 fpga_data_clk;

	FLOAT32  up_fre = 0,down_fre = 0;

	*up_fre_word = 0;
	*down_fre_word = 0;
	
	if ( SYS_A_FLAG == Flag)
	{
		ucFormat = fpga_cfg.a_net_type;
		fpga_data_clk = fpga_cfg.a_fpga_data_clk;
	} 
	else if ( SYS_B_FLAG == Flag) 
	{
		ucFormat = fpga_cfg.b_net_type;
		fpga_data_clk = fpga_cfg.b_fpga_data_clk;
	}
	else if ( SYS_C_FLAG == Flag) 
	{
		ucFormat = fpga_cfg.c_net_type;
		fpga_data_clk = fpga_cfg.c_fpga_data_clk;
	}
	else if ( SYS_D_FLAG == Flag) 
	{
		ucFormat = fpga_cfg.d_net_type;
		fpga_data_clk = fpga_cfg.d_fpga_data_clk;
	}
	
	WTD_CLR;
	
//	TRACE_INFO("SetChannel (Flag=%d)---------------------ucFormat= %04X\r\n",Flag,ucFormat);
	switch ( ucFormat )  
	{
		case NET_TYPE_GSM900:   
			if ( G2Tpye== G2_TYPE_CNMOBILE)
			{
			
				down_fre= GSM_PLL_DL_OUT_150M_CNMOBILE;	
				up_fre= GSM_PLL_UL_OUT_150M_CNMOBILE;
			}
			else
			{
			
			}
			freq_word  =  CalcGsmFreqWord( freq_code,fpga_data_clk,up_fre, down_fre , up_fre_word,down_fre_word );	
		break;       
				 
		case NET_TYPE_DCS1800: 

			//PllOutfreq =   DCS_PLL_DL_OUT_150M_UNICOM;  //��������ı������Ƶ��
			//freq_word  =  CalcDcsFreqWord( freq_code, PllOutfreq );
			if(G2_TYPE_CNMOBILE== G2Tpye)
			{				
				down_fre =   DCS_PLL_DL_OUT_150M_CNMOBILE;  //��������ı������Ƶ��
				up_fre =   DCS_PLL_UL_OUT_150M_CNMOBILE;  //��������ı������Ƶ��
				
			}else if (G2_TYPE_UNICOM== G2Tpye)
			{
				down_fre =   DCS_PLL_DL_OUT_150M_UNICOM;  //��������ı������Ƶ��
				up_fre =   DCS_PLL_UL_OUT_150M_UNICOM;  //��������ı������Ƶ��
			}
			
			CalcDcsFreqWord( freq_code, fpga_data_clk,up_fre, down_fre, up_fre_word,down_fre_word );

		break; 
				
		case NET_TYPE_WCDMA2100:
           		CalcWcdmaPLLoutputFreq(&up_fre,&down_fre); //��������ı������Ƶ��           
			//CalcWcdmaFreqWord( freq_code, fpga_data_clk,up_fre,down_fre, up_fre_word,down_fre_word);
			CalcWCDMAFreqWordNew( freq_code, fpga_data_clk,up_fre,down_fre, up_fre_word,down_fre_word);
//			TRACE_INFO("WCDMA2100 (PllOutfreq=%f)---------------------freq_word= %04X,freq_code= %04X\r\n",PllOutfreq,freq_word,freq_code);
			//WcdmaFreqWordConfigureTxRxPll( up_fre,down_fre );
			
		break; 
		 
		case NET_TYPE_TD:  
			down_fre=  TD_SCDMA_PLL_DL_OUT_150M; //��������ı������Ƶ��
			up_fre 	=  TD_SCDMA_PLL_UL_OUT_150M; //��������ı������Ƶ��
			//*up_fre_word	= CalcTDFreqWord( freq_code, up_fre);
			//*down_fre_word  =  CalcTDFreqWord( freq_code, down_fre);

			CalcTDSCDMAFreqWordNew( freq_code, fpga_data_clk,up_fre, down_fre , up_fre_word,down_fre_word );
			//*up_fre_word =*down_fre_word= freq_word;
		  	
		break; 
		
		case NET_TYPE_CDMA:
		  	
		break; 	 
		
		case NET_TYPE_CMMB: 

		break; 	 
		
		case NET_TYPE_TETRA:  
			//clk_flag=1;
            		//PllOutfreq =  clk_flag ? TETRA_PLL_DL_OUT_125M : TETRA_PLL_DL_OUT_122M; //��������ı������Ƶ��
            		down_fre =  TETRA_PLL_DL_FRQ;
			up_fre = TETRA_PLL_UL_FRQ;
			//*down_fre_word  =  CalcTetraFreqWord( freq_code, down_fre );	
			//*up_fre_word  =  CalcTetraFreqWord( freq_code, up_fre );	
			freq_word  =  CalcTetraFreqWord( freq_code, fpga_data_clk,up_fre, down_fre , up_fre_word,down_fre_word );
		break; 

		case NET_TYPE_LTE_TD:   
            		//PllOutfreq =   CalcLteTdPLLoutputFreq(Flag); //��������ı������Ƶ��
			//freq_word  =  CalcLteTdFreqWord( freq_code, PllOutfreq );	
			
			up_fre = LTE_TDD_PLL_UL_OUT;
			down_fre = LTE_TDD_PLL_DL_OUT;
			freq_word  =  CalcLteTddFreqWordNew( freq_code, fpga_data_clk,up_fre, down_fre , up_fre_word,down_fre_word );	
			//LteTdFreqWordConfigureTxRxPll( PllOutfreq,Flag);
		break; 
		
		case NET_TYPE_LTE_FDD:   
            		//PllOutfreq =   CalcLteFddPLLoutputFreq(Flag); //��������ı������Ƶ��           
			//freq_word  = CalcLteFddFreqWord( freq_code, PllOutfreq );	
			#if defined CLIENT_ERRICSON2
				up_fre = LTE_FDD_PLL_UL_OUT;
				down_fre = LTE_FDD_PLL_DL_OUT;
			#elif defined CLIENT_ERRICSON_W
				up_fre = 1950;
				down_fre = 2140;
			#endif
			freq_word  =  CalcLteFddFreqWordNew( freq_code, fpga_data_clk,up_fre, down_fre , up_fre_word,down_fre_word );	
			//LteFddFreqWordConfigureTxRxPll( PllOutfreq,Flag);
		break;
		
		case NET_TYPE_CDMA800: 
			up_fre = CDMA_PLL_UL_OUT;
			down_fre = CDMA_PLL_DL_OUT;
			freq_word  =  CalcCdma800FreqWord( freq_code, fpga_data_clk,up_fre, down_fre, up_fre_word,down_fre_word );	   
			break; 

	    default:
			TRACE_ERROR("Err net type.");
	    break; 
		   
	}

	return freq_word;
}
#if 0
/*************************************************************
Name: CalcFreqWord
Description: ����Ƶ��ż���Ƶ���֣�RE�����еĹ�ʽ����
Input:
	freq_code: Ƶ���
Output:void         
Return:Ƶ���ּĴ�����ֵ
**************************************************************/
UINT16 CalcFreqWord( INT32 freq_code, UCHAR8 Flag)
{

	FLOAT32 PllOutfreq; 
	INT32   freq_word = 0; 
    UCHAR8  ucFormat;
    
    if ( SYS_A_FLAG == Flag)
    {
       ucFormat = fpga_cfg.a_net_type;
    } 
    else if ( SYS_B_FLAG == Flag) 
    {
       ucFormat = fpga_cfg.b_net_type;
    }
    else if ( SYS_C_FLAG == Flag) 
    {
       ucFormat = fpga_cfg.c_net_type;
    }
    else if ( SYS_D_FLAG == Flag) 
    {
       ucFormat = fpga_cfg.d_net_type;
    }

	switch ( ucFormat )  
	{
	    case NET_TYPE_GSM900:   
	     if ( G2Tpye== G2_TYPE_CNMOBILE)
            PllOutfreq =  clk_flag ? GSM_PLL_DL_OUT_125M_CNMOBILE : GSM_PLL_DL_OUT_122M_CNMOBILE; //��������ı������Ƶ��
         else
            PllOutfreq =  clk_flag ? GSM_PLL_DL_OUT_125M_UNICOM : GSM_PLL_DL_OUT_122M_UNICOM; //��������ı������Ƶ��
      
			freq_word  =  CalcGsmFreqWord( freq_code, PllOutfreq );	
		break;       
				 
	    case NET_TYPE_DCS1800: 
	       if ( G2Tpye== G2_TYPE_CNMOBILE) 
             PllOutfreq =  clk_flag ? DCS_PLL_DL_OUT_125M_CNMOBILE : DCS_PLL_DL_OUT_122M_CNMOBILE; //��������ı������Ƶ��
           else
             PllOutfreq =  clk_flag ? DCS_PLL_DL_OUT_125M_UNICOM : DCS_PLL_DL_OUT_122M_UNICOM; //��������ı������Ƶ��
          
			freq_word  =  CalcDcsFreqWord( freq_code, PllOutfreq );
		break; 
				
	    case NET_TYPE_WCDMA2100:
            PllOutfreq =  clk_flag ? WCDMA_PLL_DL_OUT_125M : WCDMA_PLL_DL_OUT_122M; //��������ı������Ƶ��
			freq_word  =  CalcWcdmaFreqWord( freq_code, PllOutfreq );		  	
		break; 
		 
	    case NET_TYPE_TD:  
			PllOutfreq =  clk_flag ? TD_SCDMA_PLL_DL_OUT_125M : TD_SCDMA_PLL_DL_OUT_122M; //��������ı������Ƶ��
			freq_word  =  CalcTDFreqWord( freq_code, PllOutfreq );
		  	
		break; 
		
	    case NET_TYPE_CDMA:
		  	
		break; 	 
		
	    case NET_TYPE_CMMB: 

		break; 	 
		
	    case NET_TYPE_TETRA:   
            PllOutfreq =  clk_flag ? TETRA_PLL_DL_OUT_125M : TETRA_PLL_DL_OUT_122M; //��������ı������Ƶ��
			freq_word  =  CalcTetraFreqWord( freq_code, PllOutfreq );			
		break; 

	    case NET_TYPE_LTE_TD:   
            PllOutfreq =  clk_flag ? LTE_TD_PLL_DL_OUT_125M : LTE_TD_PLL_DL_OUT_122M; //��������ı������Ƶ��
			freq_word  =  CalcLTEFreqWord( freq_code, PllOutfreq );			
		break; 
		
	    case NET_TYPE_LTE_FDD:   
            PllOutfreq =  clk_flag ? LTE_FDD_PLL_DL_OUT_125M : LTE_FDD_PLL_DL_OUT_122M; //��������ı������Ƶ��
			freq_word  =  CalcLTEFreqWord( freq_code, PllOutfreq );			
		break;
		
	    default:
			TRACE_ERROR("Err net type.");
	    break; 
		   
	}

	return freq_word;
}

#endif

void SetClkFlag( UCHAR8 val )
{
	clk_flag = val;
}

// ����ns�ü�����ʱʱ��Ĵ���ֵ��ns������ֵ
UINT32 _CalcDelayReg( UINT32 ns )
{
	if(0==clk_flag)
	{	// 122.88Mʱ��
		return (ns*122.88+500)/1000;
	}
	else
	{	// 125Mʱ��
		return (ns*125+500)/1000;
	}
}



// ���ݼĴ������㻰����ռ��ʱ��us
UINT32 _CalcBusyTime( UINT32 reg_val, UINT32 ch_count )
{
	if(0==clk_flag)
	{	// 122.88Mʱ�� 
		return (UINT32)( (reg_val)*((FLOAT32)((ch_count+1)*4*64/122.88))+0.5 );
	}
	else
	{	// 125Mʱ��
		return (UINT32)( (reg_val)*((FLOAT32)((ch_count+1)*4*64/125))+0.5 );
	}
}

// ����Ƶ���֣�df������Ƶ��(KHz)
INT32 _CalcFpgaFw( INT32 df )
{
	INT32 sign = 1;	// ����
	
	df *= 10;	// �任��10Hz��λ
	if ( df<0 )
	{
		sign = -1;	// ��������
	}

	if(0==clk_flag)
	{	// 122.88Mʱ��
		df = (df + ( sign*100 ))/200;	// 20K
	}
	else
	{	// 125Mʱ��
		df = (df+(sign*62))/125;	// 12.5K
	}

	return df; 

}

// Ƶ������ֵ����
UINT32 _AdjustFpgaFw(INT32 df)
{
	if ( df<0 ) 
	{
		if(0==clk_flag)
		{	// 122.88Mʱ��
			df+= 3072;
		}
		else
		{	// 125Mʱ��
			df+= 5000;
		}
	}
	return (UINT32)df;
}

// ����Ƶ���ּ���FPGAƵ��Ĵ�����ֵ
UINT16 _CalcFpgaFwReg( UINT32 fw )
{
	UINT16 qw,rw; 
	
	if(0==clk_flag)
	{	// 122.88Mʱ��
		qw = fw/384;	// ��
		rw = fw%384;	// ����
		return (UINT16)(((qw&0x07)<<9)|(rw&0x01FF));
	}
	else
	{	// 125Mʱ��
		qw = fw/625;	// ��
		rw = fw%625;	// ����
		return (UINT16)(((qw&0x07)<<10)|(rw&0x03FF));
	}   
}

////////////////////////////// TD���� ////////////////////////////////
// TDʱ�����
UINT16 _CalcTdTimeParam( UINT32 tm )
{
	CHAR8 flag=0;
	if(0!=(tm&0x8000))
	{
		//flag=1;
		TRACE_INFO("tm=[%X]\r\n",tm);
		tm=0xffff-(0x0ffff&tm);
		TRACE_INFO("tm=[%X]\r\n",tm);
		if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A)
		|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
		|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
		
		 )
			return (0xffff-(UINT16)(tm*78.125/1000));// 	
		else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
			return (0xffff-(UINT16)(tm*75.0/1000));// 
		else if(version_number == VERSION_50M_IN_F ||version_number == VERSION_50M_IN_V4)
			return (0xffff-(UINT16)(tm*62.5/1000));// 
		else if(version_number == VERSION_50M_IN_V5)
		{
			return (0xffff-(UINT16)(tm*62.5/1000));// 
		}
			
	}else
	{
		if((version_number == VERSION_40M_NOIN) || (version_number == VERSION_40M_IN_A)
		|| (version_number == VERSION_40M_IN_B) || (version_number == VERSION_40M_IN_C)
		|| (version_number == VERSION_40M_IN_D) || (version_number == VERSION_40M_IN_E)
		)
			return (UINT16)(tm*78.125/1000);// 	
		else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
			return (UINT16)(tm*75.0/1000);// 
		else if(version_number == VERSION_50M_IN_F ||version_number == VERSION_50M_IN_V4)
			return (UINT16)(tm*62.5/1000);// 
	}

	
}

/*************************************************************
Name:         CalcGsmdfu
Description:  ����GSM�����߼���Ƶ��
Input:        freq_point -  �����RFƵ��
              fu_local   -  ��������Ƶ��
Output:       void         
Return:	 GSM�����߼���Ƶ��
**************************************************************/
FLOAT32 CalcGsmdfu( FLOAT32 freq_point, FLOAT32 fd_local )
{
//    FLOAT32 fClkFreq;
    
//    fClkFreq = clk_flag ? AD_FS_125M : AD_FS_122M;
//    return ( freq_point-fu_local+(2.0*fClkFreq)-(5.0*fClkFreq/8.0));
#if 0
	if ( CLK_FLAG_122_88M==clk_flag )	// 122.88M
	{

		return ( freq_point-fd_local+245.76-92.16);

  	}
  	else	// 125M
  	{
 	 	return ( freq_point-fd_local+250-93.75);   
  	}
#endif
	if(freq_point>fd_local)
	{
		return ( freq_point-fd_local); 
	}
	else  
	{
		return ( fd_local-freq_point); 
	}

} 


/*************************************************************
Name:         CalcGsmdfu
Description:  ����GSM�����߼���Ƶ��
Input:        freq_point -  �����RFƵ��
              fu_local   -  ��������Ƶ��
Output:       void         
Return:	 GSM�����߼���Ƶ��
**************************************************************/
FLOAT32 CalcDcsfu( FLOAT32 freq_point, FLOAT32 fd_local )
{
	if(freq_point>fd_local)
	{
		return ( freq_point-fd_local); 
	}
	else  
	{
		return ( fd_local-freq_point); 
	}
 	  

} 

#if 0
/*************************************************************
Name:         CalcGsmdfu
Description:  ����GSM�����߼���Ƶ��
Input:        freq_point -  �����RFƵ��
              fu_local   -  ��������Ƶ��
Output:       void         
Return:	 GSM�����߼���Ƶ��
**************************************************************/
FLOAT32 CalcDcsfu( FLOAT32 freq_point, FLOAT32 fd_local )
{
    FLOAT32 fClkFreq;
    
    fClkFreq = clk_flag ? AD_FS_125M : AD_FS_122M;

//  TRACE_INFO("%f - %f +%f\r\n",freq_point,fu_local,(5.0*fClkFreq/4.0)); 
//  return ( freq_point-fu_local+(2.0*fClkFreq)-(5.0*fClkFreq/8.0));
    if ( CLK_FLAG_122_88M==clk_flag )	// 122.88M
	{

		return ( freq_point-fd_local+245.76-92.16);

  	}
  	else	// 125M
  	{
 	 	return ( freq_point-fd_local+250-93.75);  
  	}

} 
#endif

/*************************************************************
Name:         CalcGsmdfu
Description:  ����GSM�����߼���Ƶ��
Input:        freq_point -  �����RFƵ��
              fu_local   -  ��������Ƶ��
Output:       void         
Return:	 GSM�����߼���Ƶ��
**************************************************************/
FLOAT32 CalcWcdmafu( FLOAT32 freq_point, FLOAT32 fd_local )
{
	if(freq_point>fd_local)
	{
		// TRACE_INFO("CalcWcdmafu--freq_point>fd_local\r\n"); 
		return ( freq_point-fd_local); 
	}
	else
	{
		//TRACE_INFO("CalcWcdmafu--freq_point<fd_local\r\n"); 
		return ( fd_local-freq_point); 
	}
 	  
} 
#if 0

/*************************************************************
Name:         CalcGsmdfu
Description:  ����GSM�����߼���Ƶ��
Input:        freq_point -  �����RFƵ��
              fu_local   -  ��������Ƶ��
Output:       void         
Return:	 GSM�����߼���Ƶ��
**************************************************************/
FLOAT32 CalcWcdmafu( FLOAT32 freq_point, FLOAT32 fd_local )
{
    FLOAT32 fClkFreq;  
    
    fClkFreq = clk_flag ? AD_FS_125M : AD_FS_122M;

  //TRACE_INFO("%f - %f +%f\r\n",freq_point,fu_local,(5.0*fClkFreq/4.0)); 
   //return ( freq_point-fu_local+(2.0*fClkFreq)-(5.0*fClkFreq/8.0));
   if ( CLK_FLAG_122_88M==clk_flag )	// 122.88M
	{

		return ( freq_point-fd_local+245.76-92.16);

  	}
  	else	// 125M
  	{
 	 	return ( freq_point-fd_local+250-93.75);  
  	}
}
/*************************************************************
Name:         CalcGsmdfu
Description:  ����GSM�����߼���Ƶ��
Input:        freq_point -  �����RFƵ��
              fu_local   -  ��������Ƶ��
Output:       void         
Return:	 GSM�����߼���Ƶ��
**************************************************************/
FLOAT32 CalcTetrafu( FLOAT32 freq_point, FLOAT32 fu_local )
{
    FLOAT32 fClkFreq; 
    
    fClkFreq = clk_flag ? AD_FS_125M : AD_FS_122M;

    //TRACE_INFO("%f - %f +%f\r\n",freq_point,fu_local,(5.0*fClkFreq/4.0));
   // RJ return ( freq_point-fu_local+(2.0*fClkFreq)+(5.0*fClkFreq/8.0));
   return ( freq_point-fu_local+(2.0*fClkFreq)-(5.0*fClkFreq/8.0));
}
#endif
/*************************************************************
Name:         CalcTdLtefu
Description:  ����GSM�����߼���Ƶ��
Input:        freq_point -  �����RFƵ��
              fu_local   -  ��������Ƶ��
Output:       void         
Return:	 GSM�����߼���Ƶ��
**************************************************************/
FLOAT32 CalcTdLtefu( FLOAT32 freq_point, FLOAT32 fd_local )
{
    FLOAT32 fClkFreq; 
 	if(freq_point>fd_local)
	{
		 TRACE_INFO("CalcWcdmafu--freq_point>fd_local\r\n"); 
		return ( freq_point-fd_local); 
	}
	else
	{
		TRACE_INFO("CalcWcdmafu--freq_point<fd_local\r\n"); 
		return ( fd_local-freq_point); 
	}
} 


#if  0
/*************************************************************
Name:         CalcFpgaFw
Description:  ����GSM�����߼�������Ƶ����
Input:        fDf -  ������߼�Ƶ��
Output:       void         
Return:	 �߼�������Ƶ����
**************************************************************/
INT32 CalcFpgaFw( FLOAT32 fDf )	
{
    FLOAT32 fdiv;
    
    fdiv = clk_flag ? DIV_125M : DIV_122M;
	return (INT32)((FLOAT32)(fDf)/fdiv + ((fDf<0) ? -0.5 : 0.5 ));
}
#endif
/*************************************************************
Name:         CalcFpgaFw
Description:  ����GSM�����߼�������Ƶ����
Input:        fDf -  ������߼�Ƶ��
Output:       void         
Return:	 �߼�������Ƶ����
**************************************************************/
INT32 CalcFpgaFw_AB( FLOAT32 fDf )	
{  

#if defined CLIENT_JIZHUN
	return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/12.288);

#elif defined CLIENT_DATANG
	return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/61.44);

#else
	 //if(version_number == VERSION_50M_IN_V4)
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/61.44);//
#endif
	
}

/*************************************************************
Name:         CalcFpgaFw_A
Description:  ����GSM�����߼�������Ƶ����
Input:        fDf -  ������߼�Ƶ��
Output:       void         
Return:	 �߼�������Ƶ����
**************************************************************/
INT32 CalcFpgaFw_A( FLOAT32 fDf )	
{  
	return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/61.44);
}

/*************************************************************
Name:         CalcFpgaFw
Description:  ����GSM�����߼�������Ƶ����
Input:        fDf -  ������߼�Ƶ��
Output:       void         
Return:	 �߼�������Ƶ����
**************************************************************/
INT32 CalcFpgaFw_B( FLOAT32 fDf )	
{  
	if((version_number == VERSION_40M_NOIN) 	|| (version_number == VERSION_40M_IN_B)
		|| (version_number == VERSION_40M_IN_D)
	)
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*(7/156.25/4));
	else if((version_number == VERSION_40M_IN_E) || (version_number == VERSION_40M_IN_C))// 2015-2-6 v3c��75��Ϊ62.5
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*62.5);
	else if((version_number == VERSION_20M_NOIN) || (version_number == VERSION_20M_IN))
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/75);
	else if(version_number == VERSION_40M_IN_A)
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/78.125);
	else if(version_number == VERSION_50M_IN_F )
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/62.5);
	else if(version_number == VERSION_50M_IN_V4)
		return (INT32)((FLOAT32)pow(2,13)*1024*8*fDf*1/50.0);

	else if(version_number == VERSION_50M_IN_V5)
		return (INT32)((FLOAT32)pow(2,13)*1024*8*fDf*1/50.0);

}

/*************************************************************
Name:         CalcFpgaFw
Description:  ����GSM�����߼�������Ƶ����
Input:        fDf -  ������߼�Ƶ��
Output:       void         
Return:	 �߼�������Ƶ����
**************************************************************/
INT32 CalcFpgaFw_CD( FLOAT32 fDf )	
{
	if(version_number == VERSION_40M_IN_C)
	{
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/62.5);// 2015-2-6 v3c��50��Ϊ62.5
	}
	else if( version_number==VERSION_40M_IN_D)
	{
		return (INT32)((FLOAT32)pow(2,13)*1024*8*fDf*1/(156.25/7*2)  );
	}
	else if( version_number==VERSION_40M_IN_E)
	{
		return (INT32)((FLOAT32)pow(2,13)*1024*8*fDf*1/62.5 );
	}
	else if( (version_number==VERSION_20M_NOIN) || (version_number==VERSION_20M_IN) )
	{
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/25);
	}
	else if(version_number == VERSION_50M_IN_F ||version_number == VERSION_50M_IN_V4)
	{
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/62.5);// 2015-2-6 v3c��50��Ϊ62.5
	}
	else if(version_number == VERSION_50M_IN_V5)
	{
		return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/37.5);
	}
	else
	{
		if(0x02==sys_param_1b[MADD_C_CHANNEL_COUNT].val)
		{
			//return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/50);
			return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/(156.25/7*3));//201405221849
		}else 
		{
			return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/25);
		}
	}	

	
}
INT32 CalcTypeFddFpgaFw_CD( FLOAT32 fDf )
{

	return (INT32)( (FLOAT32)pow(2,13)*1024*8*fDf*1/37.5);
}


/*************************************************************
Name:         AdjustFpgaFw
Description:  ����GSM�����߼�������Ƶ����
Input:        fDf -  GSM�����߼�������Ƶ����
Output:       void         
Return:	���ƺ��GSM����Ƶ����
**************************************************************/
INT32  AdjustFpgaFw(INT32 iDf)	
{ 
    INT32 iOffSet;

    iOffSet =  clk_flag ? OFFSET_125M : OFFSET_122M;
    
	if( iDf<0 ) 
	{
		iDf += iOffSet;
	}
	
    return iDf;
}

#if 0
/*************************************************************
Name:         CalcFpgaFwReg  
Description:  �����߼�������Ƶ�ʼĴ�����   
Input:        fDf -  GSM�����߼�������Ƶ����   
Output:       void         
Return:	�߼��Ĵ���ֵ
**************************************************************/
UINT16 CalcFpgaFwReg( UINT32 fw )
{
	UINT16 iQw,iRw;

	if(0==clk_flag) 
	{	// 122.88Mʱ��
		iQw = fw/384;	// ��
		iRw = fw%384;	// ����
		return (UINT16)(((iQw&0x07)<<9)|(iRw&0x01FF));
	}
	else
	{	// 125Mʱ��
		iQw = fw/625;	// ��
		iRw = fw%625;	// ����
		return (UINT16)(((iQw&0x07)<<10)|(iRw&0x03FF));
	} 
}
#endif

/*************************************************************
Name:         CalcFpgaFwReg  
Description:  �����߼�������Ƶ�ʼĴ�����   
Input:        fDf -  GSM�����߼�������Ƶ����   
Output:       void         
Return:	�߼��Ĵ���ֵ
**************************************************************/
UINT16 CalcFpgaFwReg( UINT32 fw )
{
	UINT16 iQw,iRw;
	clk_flag=1;
	if(0==clk_flag) 
	{	// 122.88Mʱ��
		iQw = fw/384;	// ��
		iRw = fw%384;	// ����
		return (UINT16)(((iQw&0x07)<<9)|(iRw&0x01FF));
	}
	else
	{	// 125Mʱ��
		iQw = fw/625;	// ��
		iRw = fw%625;	// ����
		return (UINT16)(((iQw&0x07)<<10)|(iRw&0x03FF));
	} 
}

/*************************************************************
Name: ConvGsmFcToFreqDL
Description: ����GSMƵ��ż��������ź�Ƶ��
Input:
	freq_code: Ƶ���
Output:void         
Return:	Ƶ��(KHz)
**************************************************************/
FLOAT32 ConvDcsFcToFreqDL( INT32 freq_code )
{
	FLOAT32 freq_point = 0.0;

	if ( IS_DCS_FC(freq_code) )
	{
		if ( freq_code <= DCS_MAX_FRE_CODE_CNMOBILE )
		{
			freq_point = 1805 + GSM_SF_STEP * (freq_code-511);
		}
		else 
		{ 
			freq_point = 1830 + GSM_SF_STEP * (freq_code-511);
		}
	}

	return freq_point;
}


/*************************************************************
Name: ConvGsmFcToFreqDL
Description: ����GSMƵ��ż��������ź�Ƶ��
Input:
	freq_code: Ƶ���
Output:void         
Return:	Ƶ��(KHz)
**************************************************************/
FLOAT32 ConvGsmFcToFreqDL( INT32 freq_code )
{
	FLOAT32 freq_point = 0.0;

	if ( IS_GSM_FC(freq_code) )
	{
		if ( freq_code <= 124 )
		{
			freq_point = 10*935 + 10*GSM_SF_STEP * freq_code;
		}
		else 
		{ 
			freq_point = 10*935 + 10*GSM_SF_STEP * (freq_code-1024);
		}
	}
	TRACE_INFO("<freq_point=%f, freq_code=%f>\r\n", freq_point, freq_code);
	return freq_point;
}

/*************************************************************
Name: ConvGsmFcToFreqDL
Description: ����GSMƵ��ż��������ź�Ƶ��
Input:
	freq_code: Ƶ���
Output:void         
Return:	Ƶ��(KHz)
**************************************************************/
FLOAT32 ConvGsmFcToFreqUL( INT32 freq_code )
{
	FLOAT32 freq_point = 0.0;

	if ( IS_GSM_FC(freq_code) )
	{
		if ( freq_code <= 124 )
		{
			freq_point = 10*890 + 10*GSM_SF_STEP * freq_code;
		}
		else 
		{ 
			freq_point = 10*890 + 10*GSM_SF_STEP * (freq_code-1024);
		}
	}
	TRACE_INFO("<freq_point=%f, freq_code=%f>\r\n", freq_point, freq_code);
	return freq_point;
}
 
/*************************************************************
Name: ConvGsmFcToFreqDL
Description: ����GSMƵ��ż��������ź�Ƶ��
Input:
	freq_code: Ƶ���
Output:void         
Return:	Ƶ��(KHz)
**************************************************************/
INT32 CalcFreqPointToFreq(UCHAR8 ucNetTye,INT32 freq_code) 
{
   INT32 freq = 0;
   
   switch ( ucNetTye )
   {
	    case NET_TYPE_GSM900: 
        	freq= ConvGsmFcToFreqDL(freq_code); 
		break;      
				 
	    case NET_TYPE_DCS1800: 
			freq= ConvDcsFcToFreqDL(freq_code); 

		break; 
				
	    case NET_TYPE_WCDMA2100:
		  	
		break; 
		
	    case NET_TYPE_TD:
		  	
		break; 
		
	    case NET_TYPE_CDMA:
		  	
		break; 	 
		
	    case NET_TYPE_CMMB: 
		  	
		break; 
		
	    default:
			TRACE_ERROR("Err net type.");
	    break; 

   }

   return freq;
}


/*************************************************************
������:	    MenCpy   
��������:   �ڴ濽��
�������:	void
���������  �� 
����ֵ: 	void   
���ú�����  
����������  
**************************************************************/
void MenCpy(void *pvDst,const void * pvSrc, UINT usLen)
{
    UCHAR8 * pucDst;
	UCHAR8 * pucSrc;
	UINT  usMenLen;
	  
	pucDst   = (UCHAR8 * )pvDst;
	pucSrc   = (UCHAR8 * )pvSrc;
	usMenLen = usLen; 
	  
    if (pucDst == 0 || pucSrc == 0 )
	{
	    return;	
	}  
	  
	while (usMenLen--)
	{
	    *pucDst++ = *pucSrc++;
    }
}






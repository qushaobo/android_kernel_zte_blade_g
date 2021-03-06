/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */



#include "msm_sensor.h"
#include "msm.h"
#include <linux/proc_fs.h>  //wangjianping add sensor  id

#define SENSOR_NAME "hi542"
#define PLATFORM_DRIVER_NAME "msm_camera_hi542"
#define hi542_obj hi542_##obj



#define HI542_REG_MODEL_ID 		 0x0004 /*Chip ID read register*/
#define HI542_MODEL_ID     		 0xB1 /*Hynix HI542 Chip ID*/ 



/* Integration Time */
#define REG_COARSE_INTEGRATION_TIME_LB                     0x0118
#define REG_COARSE_INTEGRATION_TIME_MB1                  0x0117
#define REG_COARSE_INTEGRATION_TIME_MB2                  0x0116
#define REG_COARSE_INTEGRATION_TIME_HB                    0x0115


/* Gain */
#define REG_ANALOGUE_GAIN_CODE_GLOBAL                    0x0129



#ifdef CDBG
#undef CDBG
#endif
#ifdef CDBG_HIGH
#undef CDBG_HIGH
#endif

//#define HI542_DGB

#ifdef HI542_DGB
#define CDBG(fmt, args...) printk(fmt, ##args)
#define CDBG_HIGH(fmt, args...) printk(fmt, ##args)
#else
#define CDBG(fmt, args...) do { } while (0)
#define CDBG_HIGH(fmt, args...) do { } while (0)
#endif


#define HI542_OTP_READ_FUNC

#ifdef HI542_OTP_READ_FUNC 
/* wangjianping 20130327 added for read otp func, begin */
/* OTP Oepration related registers */
#define HI542_OTP_CFG1_REG_SETTING   0x0740
#define HI542_OTP_CFG2_REG_SETTING   0x0747
#define HI542_OTP_CTL2_REG_SETTING   0x0711

#define HI542_OTP_WRITE_ADDR_HIGH    0x0720
#define HI542_OTP_WRITE_ADDR_LOW     0x0721
#define HI542_OTP_READ_ADDR          0x0722

#define HI542_OTP_MODULE_ADDR        0x0381
#define HI542_OTP_FLAG_ADDR          0x038f
#define HI542_OTP_RB_VAL_ADDR1_1     0x0390
#define HI542_OTP_RB_VAL_ADDR1_2     0x0391
#define HI542_OTP_RB_VAL_ADDR2_1     0x0392
#define HI542_OTP_RB_VAL_ADDR2_2     0x0393
#define HI542_OTP_RB_VAL_ADDR3_1     0x0394
#define HI542_OTP_RB_VAL_ADDR3_2     0x0395

#define HI542_OTP_CFG1_REG_SETTING_VAL   0x1A   //0x33
#define HI542_OTP_CFG2_REG_SETTING_VAL   0x06   //0x0b
#define HI542_OTP_CTL2_REG_SETTING_VAL   0x81
#define HI542_OTP_CTL2_REG_CLEARING_VAL   0x00

#define HI542_OTP_GET_HIGH_ADDR(x)     ((x >> 8) & 0xFF)
#define HI542_OTP_GET_LOW_ADDR(x)      ((x) & 0xFF)

uint16_t hi542_module_id = 0;
//uint16_t hi542_wbcalib_data[8] = {0};
/* wangjianping 20130327 added for read otp func, end */
#endif

DEFINE_MUTEX(hi542_mut);
static struct msm_sensor_ctrl_t hi542_s_ctrl;

static struct msm_camera_i2c_reg_conf hi542_start_settings[] = {
	{0x0001, 0x00},
};

static struct msm_camera_i2c_reg_conf hi542_stop_settings[] = {
	//{0x0632, 0x00},
	//{0x0633, 0x00},
	{0x0001, 0x01},
	{0x0617, 0x01},
	{0x0001, 0x00},
	{0x0001, 0x01},
	{0x0617, 0x00},
		
};

static struct msm_camera_i2c_reg_conf hi542_groupon_settings[] = {
	//{0x104, 0x01},
};

static struct msm_camera_i2c_reg_conf hi542_groupoff_settings[] = {
	//{0x104, 0x00},
};

/*[USERSET_0]
DISP_NAME = "capture to preview"
DISP_WIDTH = 1304	
DISP_HEIGHT = 980
DISP_FORMAT = BAYER10_MIPI
DISP_DATABUS = 16
DISP_DATAORDER = BG
MCLK = 24.00
PLL = 2.00*/
static struct msm_camera_i2c_reg_conf hi542_prev_settings[] = {

///////////////////////////////////////////
// Preview Setting
///////////////////////////////////////////

    {0x0010, 0x41},
    #if defined (CONFIG_PROJECT_P825B20) 
	{0x0011, 0x07}, //00}, exposure method change
	#elif defined (CONFIG_PROJECT_P825T20)
	{0x0011, 0x90}, //bsp wangminrong modify x y flip 20130426 
    #else	
	{0x0011, 0x00}, //04 BSP wangminrong 20130425
    #endif

	{0x0034, 0x03},
	{0x0035, 0xD4},

	{0x0500, 0x19}, // 1B, LSC OFF
	{0x0630, 0x05},
	{0x0631, 0x18},//08},
	{0x0632, 0x03},
	{0x0633, 0xD4},//C8},


};


/*	[USERSET_1]
DISP_NAME = "preview to Capture"
DISP_WIDTH = 2608	
DISP_HEIGHT = 1960
DISP_FORMAT = BAYER10_MIPI
DISP_DATABUS = 16
DISP_DATAORDER = BG
MCLK = 24.00
PLL = 2.00*/
static struct msm_camera_i2c_reg_conf hi542_snap_settings[] = {
	
	{0x0010, 0x40},
    #if defined (CONFIG_PROJECT_P825B20) 
	{0x0011, 0x07}, //00}, exposure method change
//	#elif defined (CONFIG_PROJECT_P825T20)
//	{0x0011, 0x04}, //00},//bsp wangminrong modify x y flip 20130426 
    #else	
    {0x0011, 0x00}, //04}, exposure method change BSP wangminrong 20130425
    #endif
	{0x0034, 0x07},
	{0x0035, 0xA8},

	{0x0500, 0x11}, //13}, LSC OFF

	{0x0630, 0x0A},
	{0x0631, 0x30},
	{0x0632, 0x07},
	{0x0633, 0xA8},
	
};



static struct msm_camera_i2c_reg_conf hi542_recommend_settings[] = {
	//{0x0001,0x02},    /* SW reset */            
      // {0x0001,0x01},   /* SW sleep */
       //{0x03d4,0x28},  //20120416 ryu 18);/* LDO level */20120418 ryu 28
       //delay 3 ms
    #if defined (CONFIG_PROJECT_P825B20) 
	{0x0011, 0x97}, //00}, exposure method change
	//#elif defined (CONFIG_PROJECT_P825T20)
	//{0x0011, 0x94}, //00}, exposure method change
    #else	   
    {0x0011,0x90}, //0x94 BSP wangminrong 20130425
    #endif
	{0x0020,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0021,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0022,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0023,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0038,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0039,0x2C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x003C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x003D,0x0C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x003E,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x003F,0x0C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0040,0x00}, //Hblank H
	{0x0041,0x35},////2E} Hblank L
	{0x0042,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0043,0x14}, /*jk 0x20},*/ /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0045,0x07}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0046,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0047,0xD0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0050,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0052,0x10}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0053,0x10}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0054,0x10}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0055,0x08}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0056,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0057,0x08}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0058,0x08}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0059,0x08}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x005A,0x08}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x005B,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0070,0x00}, //03}, EMI OFF
	{0x0081,0x01},//09}, //0B}, BLC scheme
	{0x0082,0x23}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0083,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0085,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0086,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x008C,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00A0,0x0f},//0C},//0B}, RAMP DC OFFSET
	{0x00A1,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00A2,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00A3,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00A4,0xFF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00A5,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00A6,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00A8,0x7F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00A9,0x7F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00AA,0x7F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00B4,0x00}, //08}, BLC offset
	{0x00B5,0x00}, //08},
	{0x00B6,0x02}, //07},
	{0x00B7,0x01}, //07},
	{0x00D4,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00D5,0xaa},//a9}, RAMP T1
	{0x00D6,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00D7,0xc9}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00D8,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00D9,0x59}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00DA,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00DB,0xb0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00DC,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x00DD,0xc9},//c5}, /*rp_rst_flg_on1*/
	{0x011C,0x1F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x011D,0xFF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x011E,0xFF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x011F,0xFF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x012A,0xFF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x012B,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0129,0x40}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0210,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0212,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0213,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0216,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0219,0x33},//    66}, Pixel bias 
	{0x021B,0x55}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x021C,0x85}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x021D,0xFF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x021E,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x021F,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0220,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0221,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0222,0xA0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0227,0x0A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0228,0x5C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0229,0x2d},//41},//00},//2C}, RAMP swing range jwryu120120
	{0x022A,0x04}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x022C,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x022D,0x23}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0237,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0238,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0239,0xA5}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x023A,0x20}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x023B,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x023C,0x22}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x023F,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0240,0x04}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0241,0x07}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0242,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0243,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0244,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0245,0xE0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0246,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0247,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x024A,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x024B,0x14}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x024D,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x024E,0x03}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x024F,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0250,0x53}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0251,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0252,0x07}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0253,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0254,0x4F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0255,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0256,0x07}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0257,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0258,0x4F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0259,0x0C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x025A,0x0C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x025B,0x0C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x026C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x026D,0x09}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x026E,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x026F,0x4B}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0270,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0271,0x09}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0272,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0273,0x4B}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0274,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0275,0x09}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0276,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0277,0x4B}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0278,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0279,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x027A,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x027B,0x55}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x027C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x027D,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x027E,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x027F,0x5E}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0280,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0281,0x03}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0282,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0283,0x45}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0284,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0285,0x03}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0286,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0287,0x45}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0288,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0289,0x5c}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x028A,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x028B,0x60}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A0,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A1,0xe0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A2,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A3,0x22}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A4,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A5,0x5C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A6,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A7,0x60}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A8,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02A9,0x5C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02AA,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02AB,0x60}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02D2,0x0F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02DB,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02DC,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02DD,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02DE,0x0C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02DF,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02E0,0x04}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02E1,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02E2,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02E3,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02E4,0x0F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02F0,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x02F1,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0310,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0311,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0312,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0313,0x5A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0314,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0315,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0316,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0317,0x5A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0318,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0319,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x031A,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x031B,0x2F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x031C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x031D,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x031E,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x031F,0x2F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0320,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0321,0xAB}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0322,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0323,0x55}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0324,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0325,0xAB}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0326,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0327,0x55}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0328,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0329,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x032A,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x032B,0x10}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x032C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x032D,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x032E,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x032F,0x10}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0330,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0331,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0332,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0333,0x2e}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0334,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0335,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0336,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0337,0x2e}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0358,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0359,0x46}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x035A,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x035B,0x59}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x035C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x035D,0x46}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x035E,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x035F,0x59}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0360,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0361,0x46}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0362,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0363,0xa4}, //a2}, Black sun
	{0x0364,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0365,0x46}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0366,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0367,0xa4}, //a2}, Black sun
	{0x0368,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0369,0x46}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x036A,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x036B,0xa6},//a9}, S2 off
	{0x036C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x036D,0x46}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x036E,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x036F,0xa6},//a9}, S2 off
	{0x0370,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0371,0xb0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0372,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0373,0x59}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0374,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0375,0xb0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0376,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0377,0x59}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0378,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0379,0x45}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x037A,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x037B,0xAA}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x037C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x037D,0x99}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x037E,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x037F,0xAE}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0380,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0381,0xB1}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0382,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0383,0x56}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0384,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0385,0x6D}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0386,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0387,0xDC}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A0,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A1,0x5E}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A2,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A3,0x62}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A4,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A5,0xc9}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A6,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A7,0x27}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A8,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03A9,0x59}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03AA,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03AB,0x55}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03AC,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03AD,0xc5}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03AE,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03AF,0x27}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03B0,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03B1,0x55}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03B2,0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03B3,0x55}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03B4,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03B5,0x0A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03D3,0x08}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03D5,0x44}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03D6,0x51}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */// hynix_test : 0x54-->0x51
	{0x03D7,0x56}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03D8,0x44}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03D9,0x06}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0580,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0581,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0582,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0583,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0584,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0585,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0586,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0587,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0588,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0589,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x058A,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x05C2,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x05C3,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0080,0xC7}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0119,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x011A,0x15}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x011B,0xC0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0115,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0116,0x2A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0117,0x4C}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0118,0x20}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0223,0xED}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0224,0xE4}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0225,0x09}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0226,0x36}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x023E,0x80}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x05B0,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03D2,0xAD}, //PLL reset 20120418 ryu add
	{0x0616,0x00}, //D-PHY reset 20120418 ryu add
	{0x0616,0x01}, //D-PHY reset disable 20120418 ryu add
	{0x03D2,0xAC}, //PLL reset disable 20120418 ryu add
	{0x03D0,0xe9}, ///* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x03D1,0x75},   /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0800,0x07}, //0F}, EMI disable
	{0x0801,0x08}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0802,0x02}, //00}, apb clock speed down
	{0x0012,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */

    {0x0013,0x00}, //40}, exposure method change  //BSP wangminrong 20130425 

	{0x0024,0x07}, /* windowing */
	{0x0025,0xa8}, /*jk 0x90},//A8}, *//* windowing */
	{0x0026,0x0A}, /* windowing */
	{0x0027,0x30}, /* jk 0x10},//30}, *//* windowing */
	{0x0030,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0031,0x03},//jk 0xFF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0032,0x07}, //jk 0x06}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0033,0xac}, //jk 0xB0}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0034,0x03}, //jk 0x02}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0035,0xd4}, //jk 0xD8}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x003A,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x003B,0x2E}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x004A,0x03}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x004B,0xd4}, //jk 0xC8}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x004C,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
{0x004D,0x18},//08}, 
	{0x0C98,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0C99,0x5E}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0C9A,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0C9B,0x62}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x05A0,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0084,0x30},//10}, BLC control
	{0x008D,0xFF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0090,0x02},//0b}, BLC defect pixel th
	{0x00A7,0x80},//FF}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x021A,0x15},//05}, /*CDS bias */
	{0x022B,0xb0},//f0}, RAMP filter
	{0x0232,0x37}, //17}, black sun enable
	{0x0010,0x41}, //jk 0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0740,0x1A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0742,0x1A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0743,0x1A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0744,0x1A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0745,0x04}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0746,0x32}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0747,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0748,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0749,0x90}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x074A,0x1A}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x074B,0xB1}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */                          
	{0x0500,0x19},// //1b}, LSC disable
	{0x0510,0x10}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */

	{0x0217,0x44}, //adaptive NCP on
	{0x0218,0x00}, //scn_sel
               
	{0x02ac,0x00}, //outdoor on
	{0x02ad,0x00}, 
	{0x02ae,0x00}, //outdoor off
	{0x02af,0x00},
	{0x02b0,0x00}, //indoor on
	{0x02b1,0x00},
	{0x02b2,0x00}, //indoor off
	{0x02b3,0x00},
	{0x02b4,0x60}, //dark1 on
	{0x02b5,0x21},
	{0x02b6,0x66}, //dark1 off
	{0x02b7,0x8a},
               
	{0x02c0,0x36}, //outdoor NCP en
	{0x02c1,0x36}, //indoor NCP en
	{0x02c2,0x36}, //dark1 NCP en
	{0x02c3,0x36},// //3f}, //dark2 NCP disable jwryu 20120120
	{0x02c4,0xE4}, //outdoor NCP voltage
	{0x02c5,0xE4}, //indoor NCP voltage
	{0x02c6,0xE4}, //dark1 NCP voltage
	{0x02c7,0xdb}, //24}, //dark2 NCP voltage
	
	{0x061A,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x061B,0x03},//03},ryu 20120416 /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x061C,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x061D,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x061E,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x061F,0x03}, /* ryu 20120416 man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0613,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0615,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0616,0x01}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0617,0x00}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0619,0x01}, //continue clk mode 20120418 ryu add
//{0x0661,0x03},
//{0x0650,0x03},
//{0x0651,0x02},
//{0x0652,0x10},
//{0x0654,0x08},	
//{0x0655,0x04},
	
	{0x0008,0x0F}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0630,0x05}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0631,0x18}, //jk 0x08}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0632,0x03}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0633,0xd4}, //jk 0xC8}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0663,0x05},//0a}, trail time /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	{0x0660,0x03}, /* man_spec_edof_ctrl_edof_fw_spare_0 Gain x7 */
	
	
};


static struct v4l2_subdev_info hi542_subdev_info[] = {
	{
	.code   = V4L2_MBUS_FMT_SBGGR10_1X10, //V4L2_MBUS_FMT_SRGGB10_1X10----NOK,////yuxin modify for test2012.06.18
	.colorspace = V4L2_COLORSPACE_JPEG,
	.fmt    = 1,
	.order    = 0,
	},
	/* more can be supported, to be added later */
};

static struct msm_camera_i2c_conf_array hi542_init_conf[] = {
	{&hi542_recommend_settings[0],
	ARRAY_SIZE(hi542_recommend_settings), 0, MSM_CAMERA_I2C_BYTE_DATA}
};

static struct msm_camera_i2c_conf_array hi542_confs[] = {
	{&hi542_snap_settings[0],
	ARRAY_SIZE(hi542_snap_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
	{&hi542_prev_settings[0],
	ARRAY_SIZE(hi542_prev_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
};

static struct msm_sensor_output_info_t hi542_dimensions[] = {
	{
		.x_output = 2608,
		.y_output = 1960,
		.line_length_pclk = 2791,
		.frame_length_lines = 1995,
		.vt_pixel_clk =  84000000,//210000000,//,//182400000
		.op_pixel_clk = 84000000,//182400000
		.binning_factor = 0,
	},
	{
		.x_output = 1304,
		.y_output = 980,
		.line_length_pclk = 2791,
		.frame_length_lines = 1003,
		.vt_pixel_clk = 84000000,//210000000 ,//,//216000000
		.op_pixel_clk =84000000,//108000000
		.binning_factor = 0,
	},
};

static struct msm_camera_csi_params hi542_csic_params = {
	.data_format = CSI_10BIT,
	.lane_cnt    = 2,
	.lane_assign = 0xe4,
	.dpcm_scheme = 0,
	.settle_cnt  = 0x21,//????????yuxin
};

static struct msm_camera_csi_params *hi542_csic_params_array[] = {
	&hi542_csic_params,
	&hi542_csic_params,
};

static struct msm_camera_csid_vc_cfg hi542_cid_cfg[] = {
	{0, CSI_RAW10, CSI_DECODE_10BIT},
	{1, CSI_EMBED_DATA, CSI_DECODE_8BIT},
};

static struct msm_camera_csi2_params hi542_csi_params = {
	.csid_params = {
		.lane_cnt = 2,
		.lut_params = {
			.num_cid = 2,
			.vc_cfg = hi542_cid_cfg,
		},
	},
	.csiphy_params = {
		.lane_cnt = 2,
		.settle_cnt = 0x21,
	},
};

static struct msm_camera_csi2_params *hi542_csi_params_array[] = {
	&hi542_csi_params,
	&hi542_csi_params,
};

static struct msm_sensor_output_reg_addr_t hi542_reg_addr = {
	.x_output = 0x0630 , 
	.y_output = 0x0632,
	.line_length_pclk = 0x0641, ////?????????????? yuxin
	.frame_length_lines = 0x0643,
};

static struct msm_sensor_id_info_t hi542_id_info = {
	.sensor_id_reg_addr = HI542_REG_MODEL_ID ,
	.sensor_id = HI542_MODEL_ID,
};


static struct msm_sensor_exp_gain_info_t hi542_exp_gain_info = {
	.coarse_int_time_addr = 0x0115,//reg_coarse_integration_time_hb
	.global_gain_addr =0x0129, //Again address
	.vert_offset = 0,
};



static int32_t hi542_write_prev_exp_gain(struct msm_sensor_ctrl_t *s_ctrl, 
                                           uint16_t gain, uint32_t line)
{
	uint16_t max_legal_gain = 0x00;//0x0200;
	int32_t rc = 0;
//	static uint32_t fl_lines, offset;
	uint32_t min_line = 4;
	uint32_t pixels_line = 0;

//	uint32_t fixed_value = 0;

	uint8_t i = 0, mask = 0xFF;
	uint8_t values_1[] = { 0, 0, 0, 0, 0 };

//	uint8_t values_2[] = { 0, 0, 0, 0, 0 };


	/* HI542's Max gain x8 = 0x00h, if gain < 0x00h then gain = 0x00h*/
	if (gain < max_legal_gain){
		CDBG("Max legal gain line:%d\n",__LINE__);
		gain = max_legal_gain;
	} 
	/* HI542's min line = 4*/
	if (line < min_line){
		CDBG("Max legal gain line:%d\n",__LINE__);
		line= min_line;
	} 
	
	pixels_line = line*2791;//2791 = above struct hi542_dimensions[] .line_length_pclk

	//	fixed_value = pixels_line + 5582; //5582 = 2791 * 2



	for ( i = 1 ; i < 5; i++ ) {
	   values_1[i]  = ( mask & pixels_line );
	 
	 //  values_2[i] = ( mask & fixed_value);
	 
	  pixels_line >>= 8;
	 
	 //  fixed_value >>= 8;	
	  
	   }

	values_1[0] = gain;

	pr_debug("hi542_write_prev_exp_gain :%d,%d\n",gain,line);
//	offset = s_ctrl->hi542_exp_gain_info->vert_offset;

	/*HI542 fixed time update*/

/*
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0120,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 11,
		values_2[4],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0121,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 12,
		values_2[3],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0122,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 13,
		values_2[2],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0123,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 14,
		values_2[1],
		MSM_CAMERA_I2C_BYTE_DATA);
*/	
#if 0  
	/*HI542 max time update*/
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x011c,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 7,
		values_1[4],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x011d,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 8,
		values_1[3],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x011e,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 9,
		values_1[2],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x011f,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 10,
		values_1[1],
		MSM_CAMERA_I2C_BYTE_DATA);	

#endif
	/*HI542 Analog gain update*/
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0129,//s_ctrl->sensor_exp_gain_info->global_gain_addr,
		values_1[0],
		MSM_CAMERA_I2C_BYTE_DATA);

	/*HI542 Exposure time update*/
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0115,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr,
		values_1[4],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0116,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 1,
		values_1[3],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0117,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 2,
		values_1[2],
		MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		0x0118,//s_ctrl->sensor_exp_gain_info->coarse_int_time_addr + 3,
		values_1[1],
		MSM_CAMERA_I2C_BYTE_DATA);	

	
return rc;
}
					
static int32_t hi542_write_pict_exp_gain(struct msm_sensor_ctrl_t *s_ctrl, 
	                                                     uint16_t gain, uint32_t line)
{
	/*because hi542's preview exp and snapshot exp are same*/
	return hi542_write_prev_exp_gain(s_ctrl, gain, line);

}



static ssize_t camera_id_read_proc(char *page,char **start,off_t off,int count,int *eof,void* data)
{		 	
	int len = 0;

	len += sprintf(page + len, "name: %s\n", "HI542-5.0M");

    #ifdef HI542_OTP_READ_FUNC 
    if(hi542_module_id)	
    {
    	len += sprintf(page + len, "module id: 0x%x\n", hi542_module_id);
    
        switch (hi542_module_id){     
            case 0x01:
            	len += sprintf(page + len, "module : %s\n", "Q-Tech");
            break ;
            case 0x0A:
            	len += sprintf(page + len, "module : %s\n", "Sunny");
            break ;
            case 0x10:
            	len += sprintf(page + len, "module : %s\n", "Truly");
            break ;
            case 0xA0:
            	len += sprintf(page + len, "module : %s\n", "Mcnex");
            break ;
            default:
            	len += sprintf(page + len, "module : %s\n", "I do not know");
        }
    }

	if (off + count >= len)
		*eof = 1;
	if (len < off)
	{
		return 0;

	}
	*start = page + off;
	#endif
	return ((count < len - off) ? count : len - off);
	
}
static void camera_proc_file(void)
{	
    struct proc_dir_entry *proc_file  = create_proc_entry("driver/camera_id_back",0644,NULL);	
    if(proc_file)	
     {		
  	     proc_file->read_proc = camera_id_read_proc;			
     }	
    else	
     {		
        printk(KERN_INFO "camera_proc_file error!\r\n");	
     }
}



#ifdef HI542_OTP_READ_FUNC 
/* wangjianping 20130327 added for read otp func, begin */
static int16_t hi542_sensor_i2c_otp_read_module_id(struct msm_sensor_ctrl_t *s_ctrl)
{
    int rc = -1;
    //struct msm_sensor_ctrl_t *s_ctrl;
	uint16_t module_id = 0;

    //s_ctrl = (struct msm_sensor_ctrl_t *)(id->driver_data);
	/* 1. otp_cfg1 & otp_cfg8 timing setting */
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_CFG1_REG_SETTING,
		HI542_OTP_CFG1_REG_SETTING_VAL,
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    }
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_CFG2_REG_SETTING,
		HI542_OTP_CFG2_REG_SETTING_VAL,
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
	/* 2. otp_ctl2 control register setting */
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_CTL2_REG_SETTING,
		HI542_OTP_CTL2_REG_SETTING_VAL,
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
	/* 3. otp_addr_h & otp_addr_l address setting */
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_WRITE_ADDR_HIGH,
		HI542_OTP_GET_HIGH_ADDR(HI542_OTP_MODULE_ADDR),
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_WRITE_ADDR_LOW,
		HI542_OTP_GET_LOW_ADDR(HI542_OTP_MODULE_ADDR),
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 

    //msleep(3);

	/* 4. data read of 0x0381 */
	rc = msm_camera_i2c_read(s_ctrl->sensor_i2c_client, HI542_OTP_READ_ADDR, &module_id,
            MSM_CAMERA_I2C_BYTE_DATA);
    if (rc < 0) {
        pr_err("%s: i2c read  failed   %d\n", __func__,__LINE__);
    } 

	/* 5. otp_ctl2 clear control register */
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_CTL2_REG_SETTING,
		HI542_OTP_CTL2_REG_CLEARING_VAL,
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    }

    hi542_module_id = module_id;
    //printk("%s: hi542 module_id is 0x%x\n", __func__, module_id);

	return module_id;
}
#if 0
static int16_t hi542_sensor_i2c_otp_read_rg_bg(struct msm_sensor_ctrl_t *s_ctrl)
{
    int rc = 0;
	uint16_t otp_flag = 0;
    uint16_t rg_bg_ratio_addr1 = 0, rg_bg_ratio_addr2 = 0;	
	uint16_t rg_ratio = 0, bg_ratio = 0;

	/* 1. otp_cfg1 & otp_cfg8 timing setting */
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_CFG1_REG_SETTING,
		HI542_OTP_CFG1_REG_SETTING_VAL,
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    }
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_CFG2_REG_SETTING,
		HI542_OTP_CFG2_REG_SETTING_VAL,
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
	/* 2. otp_ctl2 control register setting */
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_CTL2_REG_SETTING,
		HI542_OTP_CTL2_REG_SETTING_VAL,
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
	/* 3. otp_addr_h & otp_addr_l address setting */
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_WRITE_ADDR_HIGH,
		HI542_OTP_GET_HIGH_ADDR(HI542_OTP_FLAG_ADDR),
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_WRITE_ADDR_LOW,
		HI542_OTP_GET_LOW_ADDR(HI542_OTP_FLAG_ADDR),
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 

	/* 4. data read of 0x038f */
	rc = msm_camera_i2c_read(s_ctrl->sensor_i2c_client, HI542_OTP_READ_ADDR, &otp_flag,
            MSM_CAMERA_I2C_BYTE_DATA);
    if (rc < 0) {
        pr_err("%s: i2c read failed   %d\n", __func__,__LINE__);
    } 

	/* 5. otp_ctl2 clear control register */
	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		HI542_OTP_CTL2_REG_SETTING,
		HI542_OTP_CTL2_REG_CLEARING_VAL,
		MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 

    if(otp_flag == 1)
    {
        rg_bg_ratio_addr1 = HI542_OTP_RB_VAL_ADDR1_1;
        rg_bg_ratio_addr2 = HI542_OTP_RB_VAL_ADDR1_2;
    }
    else if(otp_flag == 3)
    {
        rg_bg_ratio_addr1 = HI542_OTP_RB_VAL_ADDR2_1;
        rg_bg_ratio_addr2 = HI542_OTP_RB_VAL_ADDR2_2;
    }
    else if(otp_flag == 7)
    {
        rg_bg_ratio_addr1 = HI542_OTP_RB_VAL_ADDR3_1;
        rg_bg_ratio_addr2 = HI542_OTP_RB_VAL_ADDR3_2;
    }
    else
    {
        /* otp rg/bg ratio register not write correctly, should not reach here */
        return rc;
    }
	
    /* 1. otp_cfg1 & otp_cfg8 timing setting */
    rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
    	HI542_OTP_CFG1_REG_SETTING,
    	HI542_OTP_CFG1_REG_SETTING_VAL,
    	MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    }
    rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
    	HI542_OTP_CFG2_REG_SETTING,
    	HI542_OTP_CFG2_REG_SETTING_VAL,
    	MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
    /* 2. otp_ctl2 control register setting */
    rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
    	HI542_OTP_CTL2_REG_SETTING,
    	HI542_OTP_CTL2_REG_SETTING_VAL,
    	MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
    /* 3. otp_addr_h & otp_addr_l address setting */
    rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
    	HI542_OTP_WRITE_ADDR_HIGH,
    	HI542_OTP_GET_HIGH_ADDR(rg_bg_ratio_addr1),
    	MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
    rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
    	HI542_OTP_WRITE_ADDR_LOW,
    	HI542_OTP_GET_LOW_ADDR(rg_bg_ratio_addr1),
    	MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
    
    /* 4. data read of 0x0390 & 0x0391 */
    rc = msm_camera_i2c_read(s_ctrl->sensor_i2c_client, HI542_OTP_READ_ADDR, &rg_ratio,
            MSM_CAMERA_I2C_BYTE_DATA);
    if (rc < 0) {
        pr_err("%s: i2c read  failed   %d\n", __func__,__LINE__);
    }    
  
    /* 3. otp_addr_h & otp_addr_l address setting */
    rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
    	HI542_OTP_WRITE_ADDR_HIGH,
    	HI542_OTP_GET_HIGH_ADDR(rg_bg_ratio_addr2),
    	MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
    rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
    	HI542_OTP_WRITE_ADDR_LOW,
    	HI542_OTP_GET_LOW_ADDR(rg_bg_ratio_addr2),
    	MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 
    
    rc = msm_camera_i2c_read(s_ctrl->sensor_i2c_client, HI542_OTP_READ_ADDR, &bg_ratio,
            MSM_CAMERA_I2C_BYTE_DATA);
    if (rc < 0) {
        pr_err("%s: i2c read  failed   %d\n", __func__,__LINE__);
    } 
    
    /* 5. otp_ctl2 clear control register */
    rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
    	HI542_OTP_CTL2_REG_SETTING,
    	HI542_OTP_CTL2_REG_CLEARING_VAL,
    	MSM_CAMERA_I2C_BYTE_DATA);	
    if (rc < 0) {
        pr_err("%s: i2c write  failed   %d\n", __func__,__LINE__);
    } 	

    hi542_wbcalib_data[0] = rg_ratio;
    hi542_wbcalib_data[1] = bg_ratio;
	
    //printk("WJP %s otp_flag:0x%x, rg_ratio:0x%x, bg_ratio:0x%x \n",__func__, otp_flag, rg_ratio, bg_ratio);

    return rc;
}
#endif
static int32_t hi542_sensor_i2c_otp_read(struct msm_sensor_ctrl_t *s_ctrl)
{
    int rc = 0;
    //struct msm_sensor_ctrl_t *s_ctrl;
	uint16_t module_id = 0;
	
    /* read otp register */
    //s_ctrl = (struct msm_sensor_ctrl_t *)(id->driver_data);

    module_id =  hi542_sensor_i2c_otp_read_module_id(s_ctrl); 
	if(module_id < 0)
        pr_err("%s: hi542_sensor_i2c_otp_read_module_id read failed %d\n", __func__,__LINE__);

    /* rc =  hi542_sensor_i2c_otp_read_rg_bg(s_ctrl);   
    if (rc < 0) {
        pr_err("%s: hi542_sensor_i2c_otp_read_rg_bg failed  %d\n", __func__,__LINE__);
    } */
	return rc;
}
/* wangjianping 20130327 added for read otp func, end */
#endif

#ifdef CONFIG_PROJECT_P825A20

static int hi542_pwdn_gpio;
static int hi542_reset_gpio;
static int hi542_probe_init_gpio(const struct msm_camera_sensor_info *data)
{
	int rc = 0;
	CDBG("%s: entered\n", __func__);

	hi542_pwdn_gpio = data->sensor_pwd;
	hi542_reset_gpio = data->sensor_reset;

	CDBG("%s: pwdn_gpio:%d, reset_gpio:%d\n", __func__,
			hi542_pwdn_gpio, hi542_reset_gpio);

	rc = gpio_request(hi542_pwdn_gpio, "hi542-pwd");
	if (rc < 0)
		{
		pr_err("%s: gpio_request hi542_pwdn_gpio failed!",
			 __func__);
		goto gpio_request_failed;
		}

	rc = gpio_tlmm_config(GPIO_CFG(hi542_pwdn_gpio, 0,
		GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN,
		GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	if (rc < 0) {
		pr_err("%s:unable to enable Powr Dwn gpio for main camera!\n",
			 __func__);
		gpio_free(hi542_pwdn_gpio);
		goto gpio_request_failed;
	}

	gpio_direction_output(hi542_pwdn_gpio, 0);

	rc = gpio_request(hi542_reset_gpio, "hi542-reset");
	if (rc < 0)
		{
		pr_err("%s: gpio_request hi542_reset_gpio failed!",
			 __func__);
		goto gpio_request_failed2;
		}

	rc = gpio_tlmm_config(GPIO_CFG(hi542_reset_gpio, 0,
		GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN,
		GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	if (rc < 0) {
		pr_err("%s: unable to enable reset gpio for main camera!\n",
			 __func__);
		gpio_free(hi542_reset_gpio);
		goto gpio_request_failed2;
	}

	gpio_direction_output(hi542_reset_gpio, 0);

	if (data->sensor_reset_enable)
		gpio_direction_output(data->sensor_reset, 1);

	gpio_direction_output(data->sensor_pwd, 1);

	return rc;
gpio_request_failed2:
		gpio_free(hi542_pwdn_gpio);
gpio_request_failed:
	return rc;
}


static void hi542_release_gpio(void)
{

	pr_err("%s release gpio %d, %d\n", __func__,hi542_pwdn_gpio,hi542_reset_gpio);

	gpio_free(hi542_pwdn_gpio);
	gpio_free(hi542_reset_gpio);
	
}


int32_t hi542_sensor_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
	struct msm_camera_sensor_info *s_info;
	
	s_info = client->dev.platform_data;
	if (s_info == NULL) {
		pr_err("%s %s NULL sensor data\n", __func__, client->name);
		return -EFAULT;
	}
      rc = hi542_probe_init_gpio(s_info);
      if(rc < 0)
      	{
		pr_err("%s probe faild--gpio requeset faild-----\n", __func__);
		return -EFAULT;
	  }
	
	rc = msm_sensor_i2c_probe(client, id);
      if(rc < 0)
      	 {
		pr_err("%s probe faild-------\n", __func__);
		goto probe_failed;
	  }

    if(rc == 0)
    {
        camera_proc_file();
    }
	  
	pr_err("%s probe OK+++++++++++\n", __func__);
	return rc;

probe_failed:
	hi542_release_gpio();
	return rc;
}


#else
static int32_t hi542_sensor_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
	rc = msm_sensor_i2c_probe(client,id);
	
    if(rc == 0)
    {
        camera_proc_file();
    }
	return rc;
}
#endif


static const struct i2c_device_id hi542_i2c_id[] = {
	{SENSOR_NAME, (kernel_ulong_t)&hi542_s_ctrl},
	{ }
};

static struct i2c_driver hi542_i2c_driver = {
	.id_table = hi542_i2c_id,
	#ifdef CONFIG_PROJECT_P825A20
	.probe  = hi542_sensor_i2c_probe,//msm_sensor_i2c_probe,  yuxin modify 2012.08.28
	#else
	.probe  = hi542_sensor_i2c_probe, //msm_sensor_i2c_probe,
	#endif
	.driver = {
		.name = SENSOR_NAME,
	},
};

static struct msm_camera_i2c_client hi542_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};




static int __init msm_sensor_init_module(void)
{
	return i2c_add_driver(&hi542_i2c_driver);
}

static struct v4l2_subdev_core_ops hi542_subdev_core_ops = {
	.ioctl = msm_sensor_subdev_ioctl,
	.s_power = msm_sensor_power,
};

static struct v4l2_subdev_video_ops hi542_subdev_video_ops = {
	.enum_mbus_fmt = msm_sensor_v4l2_enum_fmt,
};

static struct v4l2_subdev_ops hi542_subdev_ops = {
	.core = &hi542_subdev_core_ops,
	.video  = &hi542_subdev_video_ops,
};

#ifdef CONFIG_PROJECT_P825A20
int32_t hi542_sensor_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
       static int PowerupFlag = 0; //ryu
	struct msm_camera_sensor_info *info = s_ctrl->sensordata;
	printk("%s: sensor name is %s,chip_EN is GPIO %d,RESETB is %d\n", __func__,
		info->sensor_name,info->sensor_pwd,info->sensor_reset);

#if 0  //yuxin modify the power up timing 2012.08.22 ++
       gpio_direction_output(info->sensor_reset, 0);  //active low
	 msleep(5);
        gpio_direction_output(info->sensor_reset, 1);  
		
	gpio_direction_output(info->sensor_pwd, 0);  
       msleep(5);
       gpio_direction_output(info->sensor_pwd, 1);  
	 	
  	rc = msm_sensor_power_up(s_ctrl);
	if (rc < 0) {
		printk("%s: msm_sensor_power_up failed\n", __func__);
		return rc;
	}

#else
      	printk("%s:  PowerupFlag is %d\n", __func__,PowerupFlag);
	if(!PowerupFlag){	//ryu
       gpio_set_value(info->sensor_reset, 0);  //active low
	gpio_set_value(info->sensor_pwd, 0);  
		usleep_range(10000, 11000);
	gpio_set_value(info->sensor_reset, 1);  
		usleep_range(1000, 2000);

	PowerupFlag =1;  //ryu
	}
	   
       rc = msm_sensor_power_up(s_ctrl);
	if (rc < 0) {
		printk("%s: msm_sensor_power_up failed\n", __func__);
		return rc;
	}
	
	 gpio_set_value(info->sensor_pwd, 1);  
	 msleep(20);
	 

#endif//yuxin modify the power up timing 2012.08.22 --
	return rc;
}


int32_t hi542_sensor_power_down(struct msm_sensor_ctrl_t *s_ctrl)
{
	struct msm_camera_sensor_info *info = NULL;

	info = s_ctrl->sensordata;
	printk("%s:start\n",__func__);
	msm_sensor_power_down(s_ctrl);
	gpio_direction_output(info->sensor_pwd, 0);  //active low
	//gpio_direction_output(info->sensor_reset, 0); 

	return 0;
}
#endif //#ifdef CONFIG_PROJECT_P825A20

int32_t hi542_sensor_setting(struct msm_sensor_ctrl_t *s_ctrl,
			int update_type, int res)
{
	int32_t rc = 0;
	static int csi_config;	
	/* wangjianping 20130327 added for read otp func, end */
	#ifdef HI542_OTP_READ_FUNC 
    static int otp_read_flag = 1;
	#endif
	/* wangjianping 20130327 added for read otp func, end */
	CDBG("%s:start\n",__func__);
	//s_ctrl->func_tbl->sensor_stop_stream(s_ctrl); //yuxin del
	//msleep(30);
	if (update_type == MSM_SENSOR_REG_INIT) {
		CDBG("%s:Register INIT\n",__func__);
		s_ctrl->curr_csi_params = NULL;
		msm_sensor_enable_debugfs(s_ctrl);
		msm_camera_i2c_write(
			s_ctrl->sensor_i2c_client,
			0x0001, 0x02,
			MSM_CAMERA_I2C_BYTE_DATA);
		printk("Register write 001 INIT\n");		
		msm_camera_i2c_write(
			s_ctrl->sensor_i2c_client,
			0x0001, 0x01,
			MSM_CAMERA_I2C_BYTE_DATA);

		msm_camera_i2c_write(
			s_ctrl->sensor_i2c_client,
			0x03d4, 0x18, //jk//0x28,
			MSM_CAMERA_I2C_BYTE_DATA);
		msleep(10);
		msm_sensor_write_init_settings(s_ctrl);
			csi_config = 0;

       /* wangjianping 20130327 added for read otp func, begin */
	   #ifdef HI542_OTP_READ_FUNC 
       if(otp_read_flag == 1)
       {
         	hi542_sensor_i2c_otp_read(s_ctrl);
			//hi542_format_wbdata();
			otp_read_flag = 0;

            /* Qtech module use af_main_cam_2.h parameters */
            if(hi542_module_id == 0x01)	
            {  
                s_ctrl->sensordata->actuator_info->cam_name = MSM_ACTUATOR_MAIN_CAM_2;
            }
       }
	   #endif
       /* wangjianping 20130327 added for read otp func, end */
		
	} 
	else if (update_type == MSM_SENSOR_UPDATE_PERIODIC) {
		CDBG("%s:PERIODIC : %d,csi_config now is %d\n",__func__, res,csi_config);
		if (!csi_config) {
			s_ctrl->curr_csic_params = s_ctrl->csic_params[res];
			CDBG("CSI config in progress\n");
			v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
				NOTIFY_CSIC_CFG,
				s_ctrl->curr_csic_params);
			CDBG("CSI config is done\n");
			mb();
			msleep(30);
			csi_config = 1;
		}
		else{
			s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
			msleep(10);
		}
		
		v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
			NOTIFY_PCLK_CHANGE,
			&s_ctrl->sensordata->pdata->ioclk.vfe_clk_rate);
              msm_sensor_write_conf_array(
			s_ctrl->sensor_i2c_client,
			s_ctrl->msm_sensor_reg->mode_settings, res);
		s_ctrl->func_tbl->sensor_start_stream(s_ctrl);
		msleep(50);

	}
	return rc;
}

static struct msm_sensor_fn_t hi542_func_tbl = {
	.sensor_start_stream = msm_sensor_start_stream,
	.sensor_stop_stream = msm_sensor_stop_stream,
	.sensor_group_hold_on = msm_sensor_group_hold_on,
	.sensor_group_hold_off = msm_sensor_group_hold_off,
	.sensor_set_fps = msm_sensor_set_fps,
	.sensor_write_exp_gain = hi542_write_prev_exp_gain,
	.sensor_write_snapshot_exp_gain = hi542_write_pict_exp_gain,
	//.sensor_setting = msm_sensor_setting,  //yuxin del 
	.sensor_csi_setting = hi542_sensor_setting,
	.sensor_set_sensor_mode = msm_sensor_set_sensor_mode,
	.sensor_mode_init = msm_sensor_mode_init,
	.sensor_get_output_info = msm_sensor_get_output_info,
	.sensor_config = msm_sensor_config,
	#ifdef CONFIG_PROJECT_P825A20
	.sensor_power_up = hi542_sensor_power_up,
	.sensor_power_down = hi542_sensor_power_down,
	#else
	.sensor_power_up = msm_sensor_power_up,
	.sensor_power_down = msm_sensor_power_down,
	#endif
};

static struct msm_sensor_reg_t hi542_regs = {
	.default_data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.start_stream_conf = hi542_start_settings,
	.start_stream_conf_size = ARRAY_SIZE(hi542_start_settings),
	.stop_stream_conf = hi542_stop_settings,
	.stop_stream_conf_size = ARRAY_SIZE(hi542_stop_settings),
	.group_hold_on_conf = hi542_groupon_settings,
	.group_hold_on_conf_size = ARRAY_SIZE(hi542_groupon_settings),
	.group_hold_off_conf = hi542_groupoff_settings,
	.group_hold_off_conf_size =
		ARRAY_SIZE(hi542_groupoff_settings),
	.init_settings = &hi542_init_conf[0],
	.init_size = ARRAY_SIZE(hi542_init_conf),
	.mode_settings = &hi542_confs[0],
	.output_settings = &hi542_dimensions[0],
	.num_conf = ARRAY_SIZE(hi542_confs),
};

static struct msm_sensor_ctrl_t hi542_s_ctrl = {
	.msm_sensor_reg = &hi542_regs,
	.sensor_i2c_client = &hi542_sensor_i2c_client,
	.sensor_i2c_addr = 0x40,
	.sensor_output_reg_addr = &hi542_reg_addr,
	.sensor_id_info = &hi542_id_info,
	.sensor_exp_gain_info = &hi542_exp_gain_info,  
	.cam_mode = MSM_SENSOR_MODE_INVALID,
	.csic_params = &hi542_csic_params_array[0],
	.csi_params = &hi542_csi_params_array[0],
	.msm_sensor_mutex = &hi542_mut,
	.sensor_i2c_driver = &hi542_i2c_driver,
	.sensor_v4l2_subdev_info = hi542_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(hi542_subdev_info),
	.sensor_v4l2_subdev_ops = &hi542_subdev_ops,
	.func_tbl = &hi542_func_tbl,
	.clk_rate = MSM_SENSOR_MCLK_24HZ,
};

module_init(msm_sensor_init_module);
MODULE_DESCRIPTION("Hynix 5MP Bayer sensor driver");
MODULE_LICENSE("GPL v2");





#include "msm_sensor.h"

static struct msm_camera_i2c_reg_conf jt8ev5_recommend_settings_init[] ={
{0x0004,0x00},//;-/-/-/-/-/-/-/PISO_MSKN
{0x0100,0x00},//;-/-/-/-/-/-/-/MODSEL
#if (defined CONFIG_PROJECT_P825F01) || (defined CONFIG_PROJECT_P825A31) || (defined CONFIG_PROJECT_P865F01) || (defined CONFIG_PROJECT_P865V30) || (defined CONFIG_PROJECT_P825T20)
{0x0101,0x00},//;-/-/-/-/-/-/VREVON/HREVON
#else
{0x0101,0x03},
#endif
{0x0102,0x02},//;-/-/-/-/-/-/VLAT_ON/GROUP_HOLD
{0x0104,0x00},//;-/-/-/-/-/-/PARALLEL_OUT_SW[1:0]
{0x0105,0x00},//;-/-/-/-/-/H_COUNT[10:8]
{0x0106,0xB4},//;H_COUNT[7:0]
{0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
{0x0108,0xB6},//;V_COUNT[7:0]   0X96----->0XB6    ZZ
{0x0109,0x00},//;-/-/-/-/-/-/-/SCALE_M[8]
{0x010A,0x20},//;SCALE_M[7:0]
{0x010B,0x11},//;-/V_ANABIN[2:0]/-/-/-/H_ANABIN
{0x010C,0x02},//;-/-/HFILY[1:0]/HFILUV[1:0]/SCALING_MODE[1:0]
{0x010D,0x05},//;-/-/-/-/HOUTPIX[11:8]
{0x010E,0x00},//;HOUTPIX[7:0]
{0x010F,0x03},//;-/-/-/-/-/VOUTPIX[10:8]
{0x0110,0xC0},//;VOUTPIX[7:0]
{0x0111,0x00},//;-/-/-/-/-/-/HCROP[1:0]
{0x0112,0x00},//;-/-/-/-/-/-/VCROP[9:8]
{0x0113,0x00},//;VCROP[7:0]
{0x0114,0x01},//;-/-/-/-/OUTPUT_FORMAT[3:0]
{0x0115,0x00},//;-/-/-/-/PICEFF[3:0]
{0x0116,0x00},//;-/-/-/-/-/-/-/TH_RGBST
{0x0120,0x00},//;-/-/-/-/TEST_HC/VSYNC_PH/HSYNC_PH/ESYNC_SW
{0x0121,0x00},//;-/-/H_PRESET[13:8]
{0x0122,0x00},//;H_PRESET[7:0]
{0x0123,0x00},//;V_PRESET[15:8]
{0x0124,0x00},//;V_PRESET[7:0]
{0x0125,0x01},//;-/-/-/-/-/HREG_HRST_POS[10:8]
{0x0126,0xBD},//;HREG_HRST_POS[7:0]
{0x0128,0x00},//;-/-/-/-/-/-/TH_HOUT_MN[9:8]
{0x0129,0x00},//;TH_HOUT_MN[7:0]
{0x012A,0x00},//;-/-/-/-/TH_SIZE_SEL[3:0]
{0x012B,0x00},//;-/-/-/-/-/-/VCI[1:0]
{0x012C,0x00},//;-/-/-/-/-/-/-/TH_VOUT_MN[8]
{0x012D,0x00},//;TH_VOUT_MN[7:0]
{0x012E,0x01},//;-/-/-/-/-/-/-/ISPXSHUTDOWN
{0x0130,0xFC},//;DCLK_DRVUP/DOUT_DRVUP/SDA_DRVUP/MSDA_DRVUP/OCDI_DRVUP/PW
{0x0131,0x00},//;-/-/-/-/-/-/-/DCLK_POL
{0x0132,0x00},//;-/-/-/-/CKSP_SEL[1:0]/CKMR_SEL[1:0]
{0x0133,0x00},//;-/SLEEP_SW/VCO_STP_SW/PHY_PWRON_SW/-/SLEEP_MN/VCO_STP_
{0x0134,0x00},//;-/-/-/-/-/-/-/VCMTESTCK
{0x0135,0x00},//;-/-/-/-/-/-/CKUCDIV[1:0]
{0x0136,0x02},//;-/-/-/-/-/PCMODE/ICP_PCH/ICP_NCH
{0x0137,0x01},//;-/-/-/-/-/PRE_PLL_CNTL[2:0]
{0x0138,0x00},//;-/-/-/-/-/-/-/PLL_MULTI[8]
{0x0139,0x34},//;PLL_MULTI[7:0]
{0x013A,0x03},//;-/-/-/-/VT_SYS_CNTL[3:0]
{0x013B,0x01},//;-/-/-/-/OP_SYS_CNTL[3:0]
{0x013C,0x05},//;-/-/-/-/VT_PIX_CNTL[3:0]
{0x013D,0x00},//;-/-/PLL_SNR_CNTL[1:0]/-/-/PLL_SYS_CNTL[1:0]
{0x013E,0x27},//;-/AD_CNTL[2:0]/-/ST_CNTL[2:0]
{0x013F,0x77},//;-/NREG_CNTL[2:0]/-/BST_CNTL[2:0]
{0x0140,0x03},//;-/-/-/-/-/-/VCO_EN/DIVRSTX
{0x0141,0x00},//;-/-/-/REGVD_SEL/-/-/AMON0_SEL[1:0]
{0x0142,0x00},//;-/AUTO_ICP_R_SEL/ICP_SEL[1:0]/TXEV_SEL[1:0]/LPFR_SEL[1:0]
{0x0144,0x00},//;-/-/-/-/-/VOUT_SEL[2:0]
{0x0145,0x17},//;-/-/CL_SEL[1:0]/-/LSTB/BIAS_SEL/CAMP_EN
{0x0148,0x18},//;EXTCLK_FRQ_MHZ[15:8]
{0x0149,0x00},//;EXTCLK_FRQ_MHZ[7:0]
{0x014B,0x00},//;SY_SPARE1[7:0]
{0x014C,0x00},//;SY_SPARE2[7:0]
{0x0200,0xFF},//;LMCC_SW/LM_BLK_SW/PGC_SW/UV_SW/YBLK_SW/ETI_SW/YNC_SW/
{0x0201,0x3E},//;ALS_SW/BLK_KILLER_SW/BRIGHT_SW/CNTLV_SW/CNT_SW/UVLPF_SW
{0x0202,0x01},//;-/-/-/-/-/-/LM_T0T1_SEL/FCS_SW
{0x0203,0x11},//;-/LCS_LI/LCS_CS/D_HCHARA/-/-/D_HLIMSW[1:0]
{0x0204,0x5B},//;LM_RMG[7:0]
{0x0205,0x09},//;LM_RMB[7:0]
{0x0206,0x1A},//;LM_GMR[7:0]
{0x0207,0x1C},//;LM_GMB[7:0]
{0x0208,0x04},//;LM_BMR[7:0]
{0x0209,0x54},//;LM_BMG[7:0]
{0x020A,0x1A},//;-/GAM01P[6:0]
{0x020B,0x1C},//;-/GAM02P[6:0]
{0x020C,0x1B},//;-/GAM03P[6:0]
{0x020D,0x19},//;-/GAM04P[6:0]
{0x020E,0x2A},//;-/GAM05P[6:0]
{0x020F,0x2D},//;-/GAM06P[6:0]
{0x0210,0x27},//;-/GAM07P[6:0]
{0x0211,0x2C},//;-/GAM08P[6:0]
{0x0212,0x48},//;-/GAM09P[6:0]
{0x0213,0x46},//;-/GAM10P[6:0]
{0x0214,0x30},//;-/GAM11P[6:0]
{0x0215,0x21},//;-/GAM12P[6:0]
{0x0216,0x21},//;-/GAM13P[6:0]
{0x0217,0x1D},//;-/GAM14P[6:0]
{0x0218,0x1A},//;-/GAM15P[6:0]
{0x0219,0x19},//;-/GAM16P[6:0]
{0x021A,0x2F},//;-/GAM17P[6:0]
{0x021B,0x2A},//;-/GAM18P[6:0]
{0x021C,0x28},//;-/GAM19P[6:0]
{0x021D,0x28},//;-/GAM20P[6:0]
{0x021E,0x45},//;-/GAM21P[6:0]
{0x021F,0x3F},//;-/GAM22P[6:0]
{0x0220,0x1F},//;-/GAM23P[6:0]
{0x0221,0x0F},//;-/GAM24P[6:0]
{0x0222,0x00},//;-/-/-/-/BLK_ADJ[3:0]
{0x0223,0x57},//;CbG_MAT[7:0]
{0x0224,0x83},//;CbB_MAT[7:0]
{0x0225,0x80},//;Cb_GAIN[7:0]
{0x0226,0x83},//;CrR_MAT[7:0]
{0x0227,0x6E},//;CrG_MAT[7:0]
{0x0228,0x80},//;Cr_GAIN[7:0]
{0x0229,0x2B},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]   2b----->0b  zhangzhao 2012-8-8
{0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
{0x022B,0x03},//;EXTR_CRNG1[3:0]/EXTR_CRNG0[3:0]
{0x022C,0x00},//;-/-/-/-/EXTR_CRNG2[3:0]
{0x022D,0x08},//;EXTR_PG1[3:0]/EXTR_PG0[3:0]  88------------>08  zhangzhao 2012-8-8
{0x022E,0x00},//;-/-/-/-/EXTR_PG2[3:0]            08---------->0   zhangzhao 2012-8-8
{0x022F,0x08},//;EXTR_MG1[3:0]/EXTR_MG0[3:0]  88------------>08  zhangzhao 2012-8-8
{0x0230,0x00},//;-/-/-/-/EXTR_MG2[3:0]          08---------->0   zhangzhao 2012-8-8
{0x0231,0xB0},//;EXTR_LIM[7:0]
{0x0232,0x00},//;ETI_M[3:0]/ETI_P[3:0]
{0x0233,0xFF},//;YNC_LIM1[3:0]/YNC_LIM0[3:0]
{0x0234,0x0F},//;-/-/-/-/YNC_LIM2[3:0]
{0x0235,0x0F},//;-/-/-/-/YNC_GAIN[3:0]
{0x0236,0x00},//;SHP_CRING1[3:0]/SHP_CRING0[3:0]
{0x0237,0x04},//;-/-/-/-/SHP_CRING2[3:0]
{0x0238,0x00},//;-/-/-/SHP_LIM1[4:0]
{0x0239,0x38},//;SHP_LIM2[7:0]
{0x023A,0x08},//;SHP_PGAIN1[3:0]/SHP_PGAIN0[3:0]
{0x023B,0x00},//;-/-/-/-/SHP_PGAIN2[3:0]
{0x023C,0x08},//;SHP_MGAIN1[3:0]/SHP_MGAIN0[3:0]
{0x023D,0x00},//;-/-/-/-/SHP_MGAIN2[3:0]
{0x023E,0x80},//;ALS_AG[7:0]
{0x023F,0x60},//;-/ALS_BLIM[6:0]
{0x0240,0x60},//;-/ALS_BLK[6:0]
{0x0241,0x70},//;ALS_WHT[7:0]
{0x0242,0xFC},//;BLK_CHLV[7:0]
{0x0243,0xFC},//;WHT_CHLV[7:0]
{0x0244,0xFF},//;BLK_BLV[7:0]
{0x0245,0x00},//;BLK_CNT[7:0]
{0x0246,0x08},//;WHT_CNT[7:0]
{0x0247,0x00},//;WHT_FLV[7:0]
{0x0248,0x08},//;BRIGHT[7:0]
{0x0249,0x87},//;CONT_LEV[7:0]
{0x024A,0x02},//;BLK_CONT1[3:0]/BLK_CONT0[3:0]
{0x024B,0x00},//;-/-/-/-/BLK_CONT2[3:0]
{0x024C,0x00},//;WHT_CONT1[3:0]/WHT_CONT0[3:0]
{0x024D,0x00},//;-/-/-/-/WHT_CONT2[3:0]
{0x024E,0xFF},//;UVK_GAIN1[1:0]/UVK_GAIN0[1:0]/LPF1[1:0]/LPF0[1:0]
{0x024F,0x1F},//;-/-/-/UVK_LIM0[4:0]
{0x0250,0x1F},//;-/-/-/UVK_LIM1[4:0]
{0x0251,0x0F},//;FCS_LV[7:0]
{0x0252,0x0F},//;FCS_GAIN[7:0]
{0x0253,0x07},//;FCS_AG[7:0]
{0x0255,0x82},//;DTLGAIN[3:0]/EMBGAIN[3:0]
{0x0256,0x6A},//;SEPIAOFSU[7:0]
{0x0257,0x93},//;SEPIAOFSV[7:0]
{0x0258,0x55},//;UNICOFSU[7:0]
{0x0259,0x49},//;UNICOFSV[7:0]
{0x025A,0x02},//;-/-/-/-/-/-/ANTQSFT[1:0]
{0x025C,0x00},//;-/-/-/-/-/-/TEST_IN_SW[1:0]
{0x025D,0x00},//;TEST_AG[7:0]
{0x025E,0x00},//;MP_SPARE[7:0]
{0x0300,0x02},//;-/-/-/-/-/-/ALCSW/ALCLOCK
{0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
{0x0303,0x10},//;ALCAIM[7:0]
{0x0304,0x3E},//;AGMIN[7:0]
{0x0305,0x02},//;-/-/-/-/AGMAX[11:8]
{0x0306,0x7F},//;AGMAX[7:0]
{0x0307,0x0F},//;MES[15:8]
{0x0308,0xB0},//;MES[7:0]
{0x0309,0x40},//;ESLIMMODE/ROOMDET/-/-/MAG[11:8]
{0x030A,0xA0},//;MAG[7:0]
{0x030B,0x00},//;MDG[7:0]
{0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
{0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
{0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
{0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
{0x0310,0x1F},//;UDMODE[1:0]/-/UPDNSPD[4:0]
{0x0311,0x1F},//;ALCOFS[2:0]/NEARSPD[4:0]
{0x0312,0x08},//;ALCFRZLV[7:0]
{0x0313,0x01},//;ALCFRZTIM[7:0]
{0x0314,0xF0},//;ALCSIGMAX[7:0]
{0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
{0x0316,0x6C},//;FLLONGON/FRMSPD[1:0]/FL600S[12:8]
{0x0317,0x09},//;FL600S[7:0]
{0x0318,0xD6},//;ACFDET/AC60M/FLMANU/ACDETDLY/MSKLINE[1:0]/ACDPWAIT[1:0]
{0x0319,0x00},//;FL600AT/TTL1V_ON/-/-/-/-/-/FLDETM[8]
{0x031A,0x26},//;FLDETM[7:0]
{0x031B,0x02},//;ACDET1LV[7:0]
{0x031C,0x08},//;ACDET2LV[7:0]
{0x031D,0x0C},//;SATGUP/SATFRZ/SAT1VDET/-/DETSEL[3:0]
{0x031E,0xFF},//;APLSAT[7:0]
{0x031F,0x00},//;PEAKALCON/-/-/-/PEAKDEC[3:0]
{0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
{0x0321,0x00},//;WBMRG[7:0]
{0x0322,0x3D},//;CAREASEL[1:0]/AREAMODE[1:0]/HEXSW/YGATESW/WBMGG[9:8]
{0x0323,0x00},//;WBMGG[7:0]
{0x0324,0x15},//;SQ1SW/SQ1POL/SQ2SW/SQ2POL/SQ3SW/SQ3POL/WBMBG[9:8]
{0x0325,0x00},//;WBMBG[7:0]
{0x0326,0x0D},//;WBGRMAX[7:0]
{0x0327,0x23},//;WBGRMIN[7:0]
{0x0328,0x2B},//;WBGBMAX[7:0]
{0x0329,0x0D},//;WBGBMIN[7:0]
{0x032A,0x0C},//;RBCUT0H[7:0]
{0x032B,0xF3},//;RBCUT0L[7:0]
{0x032C,0x2C},//;-/RYCUT0P[6:0]
{0x032D,0x12},//;-/RYCUT0N[6:0]
{0x032E,0x0F},//;-/BYCUT0P[6:0]
{0x032F,0x28},//;-/BYCUT0N[6:0]
{0x0330,0x00},//;RYCUT1H[7:0]
{0x0331,0x00},//;-/RYCUT1L[6:0]
{0x0332,0x00},//;BYCUT1H[7:0]
{0x0333,0x00},//;-/BYCUT1L[6:0]
{0x0334,0x00},//;RYCUT2H[7:0]
{0x0335,0x00},//;-/RYCUT2L[6:0]
{0x0336,0x00},//;BYCUT2H[7:0]
{0x0337,0x00},//;-/BYCUT2L[6:0]
{0x0338,0x19},//;RYCUT3H[7:0]
{0x0339,0x08},//;-/RYCUT3L[6:0]
{0x033A,0xE7},//;BYCUT3H[7:0]
{0x033B,0x0A},//;-/BYCUT3L[6:0]
{0x033C,0xEB},//;YGATEH[7:0]
{0x033D,0x0},//;YGATEL[7:0]                   12------->0  zhangzhao
{0x033E,0x45},//;CGRANGE[1:0]/CGRANGE_EX/-/AWBSPD[3:0]
{0x033F,0x02},//;AWBHUECOR/-/-/AWBULV[4:0]
{0x0340,0x02},//;AWBFZTIM[2:0]/AWBVLV[4:0]
{0x0341,0x00},//;AWBSFTU[7:0]
{0x0342,0x00},//;AWBSFTV[7:0]
{0x0343,0x00},//;AWBWAIT[7:0]
{0x0344,0x04},//;-/-/-/-/CGCNGSLP[2:0]
{0x0345,0x90},//;CGCNGLV[7:0]
{0x0346,0x12},//;-/RYCUTLITE[6:0]
{0x0347,0x10},//;-/BYCUTLITE[6:0]
{0x0348,0x00},//;SPLMKON/SPLMKBL/FAREAMK/CAREAMK/CGATEMK/-/-/-
{0x0349,0x03},//;-/-/-/-/SPLADRH[11:8]
{0x034A,0x28},//;SPLADRH[7:0]
{0x034B,0x20},//;MKFLKON/MKFLKSPD[1:0]/-/-/SPLADRV[10:8]
{0x034C,0x60},//;SPLADRV[7:0]
{0x034D,0x00},//;MMES[15:8]
{0x034E,0x60},//;MMES[7:0]
{0x034F,0x01},//;-/-/-/-/-/-/ALCAIML[9:8]
{0x0350,0x00},//;ALCAIML[7:0]
{0x0351,0xD0},//;ALCSIGMIN[7:0]
{0x0352,0x73},//;PKDOT_CNTH[3:0]/PKDOT_CNTL[3:0]
{0x0353,0xA0},//;ALC_SUB[1:0]/ALC_ADD[1:0]/-/-/SELFRZLV/PKALCSW
{0x0354,0x00},//;-/-/-/-/-/-/PKALCESL[9:8]
{0x0355,0x03},//;PKALCESL[7:0]
{0x0356,0x00},//;-/-/ALC_SWSEL[1:0]/-/-/AWB_SWSEL[1:0]
{0x0357,0xC0},//;SATSET[7:0]
{0x0358,0x00},//;AU_SPARE_T0[7:0]
{0x0400,0xFF},//;HLNRSW/DANSASW[1:0]/LDNRSW/VNRSW/ABPCSW/WBPSW/BBPSW
{0x0401,0x25},//;-/PWB_T0T1_SEL/ANRSW/PEDAJSW/GDANSASW/LSSCSW/LSAG_SW/
{0x0402,0x00},//;-/-/-/-/-/TPATRGBSW[2:0]
{0x0403,0x40},//;BLKADJ[7:0]
{0x0404,0x00},//;BLKR[3:0]/BLKGR[3:0]
{0x0405,0x00},//;BLKGB[3:0]/BLKB[3:0]
{0x0406,0x30},//;-/-/OBWIDTH[5:0]
{0x0407,0x00},//;-/-/-/-/-/OBCLIP/BLLVSEL/DANSA2L
{0x0408,0x03},//;HNCLIM1[3:0]/HNCLIM0[3:0]
{0x0409,0x0F},//;-/-/-/-/HNCLIM2[3:0]
{0x040A,0x03},//;-/-/-/-/LDNRGA[3:0]
{0x040B,0x73},//;VNRLIM1[3:0]/VNRLIM0[3:0]
{0x040C,0x0F},//;-/-/-/-/VNRLIM2[3:0]
{0x040D,0x08},//;-/-/-/-/VNRG[3:0]
{0x040E,0x0C},//;BBPLV[7:0]
{0x040F,0x20},//;WBPLV0[7:0]
{0x0410,0xC4},//;WBPLV2[3:0]/WBPLV1[3:0]
{0x0411,0x80},//;WHTAG[7:0]
{0x0412,0x68},//;ANCNTLV[7:0]
{0x0413,0x68},//;NSGAIN1[3:0]/NSGAIN0[3:0]
{0x0414,0x03},//;-/-/-/-/NSGAIN2[3:0]
{0x0415,0x43},//;EGCRNG1[3:0]/EGCRNG0[3:0]
{0x0416,0x0F},//;-/-/-/-/EGCRNG2[3:0]
{0x0417,0x08},//;-/-/-/-/EGGAIN[3:0]
{0x0418,0x00},//;-/-/EGLIMSG[1:0]/-/-/EGLIMS[1:0]
{0x0419,0x04},//;-/-/-/-/AJUST0[3:0]
{0x041A,0x00},//;GRPED0[3:0]/GBPED0[3:0]
{0x041B,0x00},//;RPED0[3:0]/BPED0[3:0]
{0x041C,0x00},//;GRPED1[3:0]/GBPED1[3:0]
{0x041D,0x00},//;RPED1[3:0]/BPED1[3:0]
{0x041E,0x80},//;GDANSALV[7:0]
{0x041F,0x08},//;-/-/-/-/GDANSAG[3:0]
{0x0420,0x00},//;PWBGAINGR[7:0]
{0x0421,0x00},//;PWBGAINGB[7:0]
{0x0422,0x5A},//;PWBGAINR[7:0]
{0x0423,0x3B},//;PWBGAINB[7:0]
{0x0426,0x00},//;-/-/-/-/-/-/LIPOL/CSPOL
{0x0427,0x00},//;-/LS4SIG[2:0]/-/LS1SIG[2:0]
{0x0428,0x80},//;LSHOFG[7:0]
{0x0429,0x90},//;LSHOFR[7:0]
{0x042A,0xA8},//;LSHOFB[7:0]
{0x042B,0xC0},//;LSVOFG[7:0]
{0x042C,0xB0},//;LSVOFR[7:0]
{0x042D,0xA8},//;LSVOFB[7:0]
{0x042E,0x60},//;LSALUG[7:0] 1st left up
{0x042F,0x79},//;LSALUR[7:0]
{0x0430,0x67},//;LSALUB[7:0]
{0x0431,0x70},//;LSARUG[7:0] 1st right up
{0x0432,0x50},//;LSARUR[7:0]
{0x0433,0x40},//;LSARUB[7:0]
{0x0434,0x20},//;LSALDG[7:0] 1st left down
{0x0435,0x59},//;LSALDR[7:0]
{0x0436,0x56},//;LSALDB[7:0]
{0x0437,0x38},//;LSARDG[7:0]  1st right down
{0x0438,0x4A},//;LSARDR[7:0]
{0x0439,0x1C},//;LSARDB[7:0]
{0x043A,0xBA},//;LSBLG[7:0] 2nd left
{0x043B,0xD8},//;LSBLR[7:0]
{0x043C,0x7D},//;LSBLB[7:0]
{0x043D,0xB5},//;LSBRG[7:0]  2nd right
{0x043E,0xDE},//;LSBRR[7:0]
{0x043F,0x62},//;LSBRB[7:0]
{0x0440,0xD0},//;LSCUG[7:0] 2nd up
{0x0441,0xF7},//;LSCUR[7:0]
{0x0442,0x95},//;LSCUB[7:0]
{0x0443,0x92},//;LSCDG[7:0] 2nd down
{0x0444,0xA0},//;LSCDR[7:0]
{0x0445,0x89},//;LSCDB[7:0]
{0x0446,0x60},//;LSDLG[7:0] 4th left
{0x0447,0x49},//;LSDLR[7:0]
{0x0448,0x83},//;LSDLB[7:0]
{0x0449,0x3F},//;LSDRG[7:0] 4th right
{0x044A,0x3C},//;LSDRR[7:0]
{0x044B,0x70},//;LSDRB[7:0]
{0x044C,0x70},//;LSEUG[7:0] 4th up
{0x044D,0x90},//;LSEUR[7:0]
{0x044E,0x90},//;LSEUB[7:0]
{0x044F,0xB0},//;LSEDG[7:0] 4th down
{0x0450,0xC0},//;LSEDR[7:0]
{0x0451,0x90},//;LSEDB[7:0]
{0x045B,0xC0},//;LSHCNT_MPY[7:0]
{0x045C,0x01},//;-/-/-/-/LSVCNT_MPY[11:8]
{0x045D,0x7F},//;LSVCNT_MPY[7:0]
{0x045E,0x01},//;-/-/-/-/-/-/LSMGSEL[1:0]
{0x045F,0x00},//;-/-/-/-/TESTPAT[3:0]
{0x0460,0x00},//;TPATSLPH[7:0]
{0x0461,0x00},//;TPATSLPV[7:0]
{0x0462,0x00},//;-/-/-/-/-/-/TDATARE[9:8]
{0x0463,0x00},//;TDATARE[7:0]
{0x0464,0x00},//;-/-/-/-/-/-/TDATAGR[9:8]
{0x0465,0x00},//;TDATAGR[7:0]
{0x0466,0x00},//;-/-/-/-/-/-/TDATABL[9:8]
{0x0467,0x00},//;TDATABL[7:0]
{0x0468,0x00},//;-/-/-/-/-/-/TDATAGB[9:8]
{0x0469,0x00},//;TDATAGB[7:0]
{0x046B,0x00},//;PP_SPARE[7:0]
{0x0600,0x10},//;-/-/-/BOOSTEN/POSLFIX/NEGLFIX/-/NEGLEAKCUT
{0x0601,0x08},//;BSTREADEV/-/-/-/NEGBSTCNT[3:0]
{0x0602,0x06},//;POSBSTSEL/-/-/-/-/POSBSTCNT[2:0]
{0x0603,0x35},//;-/POSBSTHG[2:0]/-/POSBSTGA[2:0]
{0x0604,0x00},//;-/-/-/-/RSTVDSEL/READVDSEL/LNOBMODE/GDMOSBGREN
{0x0605,0x80},//;KBIASSEL/-/-/-/-/-/-/-
{0x0606,0x07},//;-/-/-/BSVBPSEL[4:0]
{0x0607,0x31},//;-/DRADRVLV[2:0]/-/-/DRADRVI[1:0]
{0x0608,0x8E},//;DRADRVPU[1:0]/-/VREFV[4:0]
{0x0609,0xCC},//;ADSW2WEAK/ADSW1WEAK/-/-/VREFAI[3:0]
{0x060A,0x20},//;ADCKSEL/-/ADCKDIV[1:0]/-/SENSEMODE[2:0]
{0x060B,0x00},//;-/-/SPARE[1:0]/ANAMON1_SEL[3:0]
{0x060C,0x07},//;HREG_TEST/-/-/-/-/BINVSIG/BINED/BINCMP
{0x060E,0x00},//;EXT_HCNT_MAX_ON/-/-/HCNT_MAX_MODE/-/-/-/MLT_SPL_MODE
{0x060F,0x0A},//;HCNT_MAX_FIXVAL[15:8]
{0x0610,0xDC},//;HCNT_MAX_FIXVAL[7:0]
{0x0612,0x0C},//;-/-/VREG_TEST[1:0]/ES_MODE/BIN_MODE/DIS_MODE/RODATA_U
{0x0614,0x5C},//;BSC_OFF/LIMITTER_BSC/-/DRESET_CONJ_U[4:0]
{0x0615,0x04},//;-/-/-/-/DRESET_CONJ_D[3:0]
{0x0616,0x04},//;FTLSNS_HIGH/-/FTLSNS_LBSC_U[5:0]
{0x0617,0x00},//;-/-/-/-/-/FTLSNS_LBSC_D[2:0]
{0x0618,0x18},//;-/FTLSNS_CONJ_W[6:0]
{0x0619,0x04},//;-/-/-/-/FTLSNS_CONJ_D[3:0]
{0x061A,0x08},//;SADR_HIGH/-/SADR_LBSC_U[5:0]
{0x061B,0x00},//;-/-/-/-/-/SADR_LBSC_D[2:0]
{0x061C,0x2E},//;SADR_CONJ_U[7:0]
{0x061D,0x00},//;-/-/-/-/SADR_CONJ_D[3:0]
{0x061F,0x03},//;ESREAD_ALT_OFF/-/-/ELEC_INJ_MODE/-/-/AUTO_READ_W/AUT
{0x0620,0x08},//;-/-/-/-/FRAC_EXP_TIME[11:8]
{0x0621,0x90},//;FRAC_EXP_TIME[7:0]
{0x0622,0x70},//;ESREAD_1D[7:0]
{0x0623,0x88},//;ESREAD_1W[7:0]
{0x0624,0x01},//;-/-/-/-/-/-/ESREAD_2D[9:8]
{0x0625,0x3D},//;ESREAD_2D[7:0]
{0x0626,0x88},//;ESREAD_2W[7:0]
{0x0627,0x24},//;ESTGRESET_LOW/ESTGRESET_D[6:0]
{0x0628,0x00},//;ALLZEROSET_ON/EXTD_ROTGRESET/-/-/-/-/ROTGRESET_U[9:8]
{0x0629,0xD8},//;ROTGRESET_U[7:0]
{0x062B,0x00},//;ROREAD_U[7:0]
{0x062C,0x88},//;ROREAD_W[7:0]
{0x062D,0x22},//;ZEROSET_U[7:0]
{0x062E,0x60},//;ZEROSET_W[7:0]
{0x062F,0x00},//;-/-/FIX_RSTDRAIN[1:0]/FIX_RSTDRAIN2[1:0]/FIX_RSTDRAIN3[1:0
{0x0630,0x00},//;-/RSTDRAIN_D[6:0]
{0x0631,0x0F},//;-/-/RSTDRAIN_U[5:0]
{0x0632,0x07},//;-/-/-/-/RSTDRAIN2_D[3:0]
{0x0633,0x07},//;-/-/-/-/RSTDRAIN2_U[3:0]
{0x0634,0x04},//;-/-/-/-/RSTDRAIN3_D[3:0]
{0x0635,0x0D},//;-/-/RSTDRAIN3_U[5:0]
{0x0636,0x01},//;-/-/DRCUT_SIGIN/DRCUT_HIGH/-/-/VSIGDR_MODE[1:0]
{0x0637,0x01},//;-/-/DRCUT_NML_U[5:0]
{0x0638,0x20},//;-/-/DRCUT_CGR_U[5:0]
{0x0639,0x20},//;-/-/DRCUT_CGR_D[5:0]
{0x063A,0x30},//;-/-/DRCUT_VDER_1U[5:0]
{0x063B,0x04},//;-/-/DRCUT_VDER_1D[5:0]
{0x063C,0x30},//;-/-/DRCUT_VDER_2U[5:0]
{0x063D,0x04},//;-/-/DRCUT_VDER_2D[5:0]
{0x063E,0x00},//;-/-/DRCUT_1ITV_MIN[1:0]/-/-/DRCUT_2ITV_MIN[1:0]
{0x063F,0x2F},//;GDMOSCNT_NML[3:0]/GDMOSCNT_VDER[3:0]
{0x0640,0x01},//;-/-/-/-/-/-/GDMOS_VDER_1U[1:0]
{0x0641,0x04},//;-/-/GDMOS_VDER_1D[5:0]
{0x0642,0x01},//;-/-/-/-/-/-/GDMOS_VDER_2U[1:0]
{0x0643,0x04},//;-/-/GDMOS_VDER_2D[5:0]
{0x0644,0x00},//;-/-/-/-/-/-/-/SIGIN_ON
{0x0645,0x01},//;-/-/-/-/-/-/GDMOSLT_VDER_1W[1:0]
{0x0646,0x60},//;-/GDMOSLT_VDER_1D[6:0]
{0x0647,0x01},//;-/-/-/-/-/-/GDMOSLT_VDER_2W[1:0]
{0x0648,0x60},//;-/GDMOSLT_VDER_2D[6:0]
{0x0649,0x01},//;-/-/-/-/-/-/-/VSIGPU_LOW
{0x064A,0x0C},//;VSIGPU_U[7:0]
{0x064B,0x14},//;-/VSIGPU_W[6:0]
{0x064C,0x00},//;-/-/-/-/-/-/-/ROTGRESET_W[8]
{0x064D,0x12},//;ROTGRESET_W[7:0]
{0x0650,0x0E},//;ADSW1_D[7:0]
{0x0651,0x00},//;ADSW1_HIGH/-/ADSW_U[5:0]
{0x0652,0x07},//;ADSW1DMX_LOW/-/-/ADSW1DMX_U[4:0]
{0x0653,0x1C},//;ADSW1LK_HIGH/ADSW1LK_D[6:0]
{0x0654,0x1C},//;ADSW1LKX_LOW/ADSW1LKX_U[6:0]
{0x0655,0x80},//;ADCMP1SRT_LOW/-/-/-/-/ADCMP1SRT_U[2:0]
{0x0656,0x3D},//;-/-/ADCMP1SRT_D[5:0]
{0x0657,0x0E},//;ADSW2_HIGH/-/ADSW2_D[5:0]
{0x0658,0x07},//;ADSW2DMX_LOW/-/-/ADSW2DMX_U[4:0]
{0x0659,0x00},//;FIX_ADENX[1:0]/ADENX_U[5:0]
{0x065A,0x01},//;-/-/ADENX_D[5:0]
{0x065B,0x00},//;-/-/CMPI_CGR_U[5:0]
{0x065C,0x01},//;-/-/CMPI_CGR_D[5:0]
{0x065D,0xA3},//;CMPI1_NML[3:0]/CMPI2_NML[3:0]
{0x065E,0x33},//;CMPI1_CGR[3:0]/CMPI2_CGR[3:0]
{0x065F,0x00},//;-/-/-/-/-/-/CGR_MODE/CDS_STOPBST
{0x0660,0x04},//;BSTCKLFIX_HIGH/-/-/BSTCKLFIX_U[4:0]
{0x0661,0x04},//;-/-/-/BSTCKLFIX_D[4:0]
{0x0662,0x20},//;-/-/ADENX_CGR_U[5:0]
{0x0663,0x20},//;-/-/ADENX_CGR_D[5:0]
{0x0664,0x00},//;-/-/-/-/-/-/-/MS_ADV_INTVL[8]
{0x0665,0xAE},//;MS_ADV_INTVL[7:0]
{0x0666,0x70},//;MS_RSV_INTVL[7:0]
{0x0667,0x03},//;-/-/-/-/SINT_ZS_U[3:0]
{0x0668,0x3B},//;SINT_ZS_W[7:0]
{0x0669,0x3B},//;-/SINT_RS_U[6:0]
{0x066A,0x59},//;SINT_RS_W[7:0]
{0x066B,0x1D},//;SINT_FB_U[7:0]
{0x066C,0x3B},//;-/SINT_FB_W[6:0]
{0x066D,0x01},//;-/-/-/-/-/-/-/SINT_AD_U[8]
{0x066E,0x0B},//;SINT_AD_U[7:0]
{0x066F,0x01},//;-/-/-/-/-/-/-/SINT_AD_W[8]
{0x0670,0x19},//;SINT_AD_W[7:0]
{0x0671,0x11},//;-/-/SINTX_DSHIFT[1:0]/-/-/SINTX_USHIFT[1:0]
{0x0672,0x1E},//;SINT_MS_ZS_W[7:0]
{0x0673,0x2B},//;SINT_MS_RS_W[7:0]
{0x0674,0x2E},//;SINT_MS_RS_U[7:0]
{0x0675,0x01},//;-/-/-/-/-/-/-/SINT_MS_AD1_U[8]
{0x0676,0x23},//;SINT_MS_AD1_U[7:0]
{0x0677,0x0F},//;-/-/-/SINT_MS_FB_W[4:0]
{0x0678,0x5F},//;SINT_MS_AD_W[7:0]
{0x0679,0x20},//;-/SINT_MS_FB_D[6:0]
{0x067A,0x6D},//;SRST_RS_U[7:0]
{0x067B,0x0D},//;-/-/SRST_RS_W[5:0]
{0x067C,0x97},//;SRST_ZS_U[7:0]
{0x067D,0x0D},//;-/-/SRST_ZS_W[5:0]
{0x067E,0x03},//;-/-/-/-/SRST_AD_U[3:0]
{0x067F,0x7D},//;SRST_AD_D[7:0]
{0x0680,0x60},//;SRST_MS_AD4_D[7:0]
{0x0681,0xBA},//;SRST_MS_RS4_U[7:0]
{0x0682,0x03},//;-/-/-/-/SRST_MS_AD_U[3:0]
{0x0683,0x0D},//;-/-/SRST_MS_AD_W[5:0]
{0x0684,0x03},//;VREFSHBGR_LOW/-/-/-/VREFSHBGR_D[3:0]
{0x0685,0x38},//;-/-/VREFSHBGR_U[5:0]
{0x0686,0xBC},//;EN_VREFC_ZERO/-/VREF_H_START_U[5:0]
{0x0687,0x00},//;ADCKEN_MASK[1:0]/-/-/-/-/-/-
{0x0688,0x0B},//;-/ADCKEN_1U[6:0]
{0x0689,0x0C},//;-/-/-/ADCKEN_1D[4:0]
{0x068A,0x0B},//;-/ADCKEN_2U[6:0]
{0x068B,0x0C},//;-/-/-/ADCKEN_2D[4:0]
{0x068C,0x09},//;-/-/-/-/CNTRSTX_U[3:0]
{0x068D,0x0C},//;-/-/-/CNT0RSTX_1D[4:0]
{0x068E,0x09},//;-/-/-/-/CNT0RSTX_2U[3:0]
{0x068F,0x0C},//;-/-/-/CNT0RSTX_2D[4:0]
{0x0690,0x08},//;-/-/-/CNTINVX_START[4:0]
{0x0691,0x14},//;EDCONX_1D[7:0]
{0x0692,0x00},//;EDCONX_RS_HIGH/EDCONX_AD_HIGH/-/-/-/-/-/EDCONX_2D[8]
{0x0693,0x28},//;EDCONX_2D[7:0]
{0x0694,0x00},//;ADTESTCK_INTVL[3:0]/-/-/ADTESTCK_ON/COUNTER_TEST
{0x0695,0x1F},//;-/ADCKEN_MS_1U[6:0]
{0x0696,0x1F},//;-/ADCKEN_MS_2U[6:0]
{0x0697,0x01},//;EXT_VCD_ADJ_ON/MPS_AUTO_VCDADJ/-/AG_SEN_SHIFT/-/-/VCD_
{0x0698,0x00},//;VCD_COEF_FIXVAL[7:0]
{0x0699,0x00},//;-/-/VCD_INTC_FIXVAL[5:0]
{0x069A,0x1B},//;VREFAD_RNG1_SEL[1:0]/VREFAD_RNG2_SEL[1:0]/VREFAD_RNG3_SEL[1:0]
{0x069B,0x00},//;-/-/-/-/-/-/AGADJ1_VREFI_ZS[9:8]
{0x069C,0x3C},//;AGADJ1_VREFI_ZS[7:0]
{0x069D,0x00},//;-/-/-/-/-/-/AGADJ2_VREFI_ZS[9:8]
{0x069E,0x1E},//;AGADJ2_VREFI_ZS[7:0]
{0x069F,0x00},//;-/-/-/-/-/-/-/AGADJ1_VREFI_AD[8]
{0x06A0,0x78},//;AGADJ1_VREFI_AD[7:0]
{0x06A1,0x00},//;-/-/-/-/-/-/-/AGADJ2_VREFI_AD[8]
{0x06A2,0x3C},//;AGADJ2_VREFI_AD[7:0]
{0x06A3,0x06},//;-/-/-/-/-/AGADJ_VREFC[2:0]
{0x06A4,0x00},//;EXT_VREFI_ZS_ON/-/-/-/-/-/VREFI_ZS_FIXVAL[9:8]
{0x06A5,0x00},//;VREFI_ZS_FIXVAL[7:0]
{0x06A6,0x00},//;EXT_VREFI_FB_ON/-/-/-/-/-/VREFI_FB_FIXVAL[9:8]
{0x06A7,0x00},//;VREFI_FB_FIXVAL[7:0]
{0x06A9,0x02},//;GDBSVDDSW_U[4:0]/NREGBSTEN/NREGBSTFNC[1:0]
{0x06AA,0x00},//;EXT_VREFC_ON/-/-/-/-/VREFC_FIXVAL[2:0]
{0x06AB,0x04},//;EXT_PLLFREQ_ON/-/-/-/PLLFREQ_FIXVAL[3:0]
{0x06AC,0xBB},//;PIXNREGBIASCNT[3:0]/CMPNREGBIASCNT[3:0]
{0x06AD,0x40},//;NREGBSTCNT[2:0]/PIXNREGEN/GDPXVDDEN/BSPXVDDEN/RGDBSVDDSRTX
{0x06AE,0xC0},//;BC_LTPTM[1:0]/-/ACT_TESTDAC/-/-/AG_TEST/TESTDACEN
{0x06AF,0xFF},//;TDAC_INT[7:0]
{0x06B0,0x00},//;TDAC_MIN[7:0]
{0x06B1,0x10},//;TDAC_STEP[3:0]/-/-/TDAC_SWD[1:0]
{0x06B2,0x00},//;PIXVREGFUNC[3:0]/CMPNREGEN/VREFNREGEN/RCVVDDSRTX/VSIGRCVDD
{0x06B3,0x00},//;DACS_INT[7:0]
{0x06B4,0xFF},//;DACS_MAX[7:0]
{0x06B5,0x10},//;DACS_STEP[3:0]/-/-/DACS_SWD[1:0]
{0x06B6,0x80},//;TESTDAC_RSVOL[7:0]
{0x06B7,0x60},//;TESTDAC_ADVOL[7:0]
{0x06B8,0x62},//;ZSV_EXEC_MODE[3:0]/-/AGADJ_EXEC_MODE[2:0]
{0x06B9,0x02},//;MPS_AGADJ_MODE/AGADJ_CALC_MODE/-/-/AGADJ_FIX_COEF[11:8]
{0x06BA,0x06},//;AGADJ_FIX_COEF[7:0]
{0x06BB,0xF1},//;ZSV_FORCE_END[3:0]/-/-/ZSV_SUSP_RANGE[1:0]
{0x06BC,0x86},//;ZSV_SUSP_CND/-/-/-/EN_PS_VREFI_ZS[3:0]
{0x06BD,0x10},//;VZS_MPS_STEP[7:0]
{0x06BE,0xA0},//;ZSV_LEVEL[7:0]
{0x06BF,0x10},//;-/-/ZSV_IN_RANGE[5:0]
{0x06C0,0xC7},//;PS_VZS_NML_COEF[7:0]
{0x06C1,0x00},//;-/PS_VZS_NML_INTC[6:0]
{0x06C2,0x10},//;VZS_NML_STEP[7:0]
{0x06C3,0x44},//;ZSV_STOP_CND[1:0]/-/-/ZSV_IN_LINES[3:0]
{0x06C4,0xC7},//;PS_VZS_MPS_COEF[7:0]
{0x06C5,0x01},//;-/PS_VZS_MPS_INTC[6:0]
{0x06C6,0x18},//;-/FBC_IN_RANGE[6:0]
{0x06C7,0x44},//;FBC_SUSP_RANGE[1:0]/-/FBC_IN_LINES[4:0]
{0x06C8,0x44},//;FBC_OUT_RANGE[1:0]/-/FBC_OUT_LINES[4:0]
{0x06C9,0x20},//;FBC_STOP_CND[2:0]/-/-/-/-/-
{0x06CA,0x41},//;FBC_START_CND[2:0]/-/VREFI_FB_STEP[3:0]
{0x06CB,0x82},//;FBC_SUSP_CND/-/-/-/EN_PS_VREFI_FB[3:0]
{0x06CC,0xC0},//;PS_VREFI_FB_AG/LIM_START_FBC/-/-/-/-/-/-
{0x06CD,0x00},//;-/-/-/ST_CKI[4:0]
{0x06CE,0x30},//;-/ST_BLACK_LEVEL[6:0]
{0x06CF,0xF0},//;ST_RSVD_REG[7:0]
{0x06E5,0x22},//;RORDDWSTMD/VDDRD28EN_1U[2:0]/-/VDDRD28EN_1D[2:0]
{0x06E6,0x22},//;-/BSTRDCUT_1U[2:0]/-/BSTRDCUT_1D[2:0]
{0x06E7,0x22},//;ESRDDWSTMD/VDDRD28EN_2U[2:0]/-/VDDRD28EN_2D[2:0]
{0x06E8,0x22},//;-/BSTRDCUT_2U[2:0]/-/BSTRDCUT_2D[2:0]
{0x06E9,0x01},//;-/-/GDMOS_CGR_D[5:0]
{0x06EA,0x01},//;-/-/-/-/GDMOSCNT_CGR[3:0]
{0x06EB,0x02},//;-/-/VOB_DISP/HOB_DISP/VENL_OFF/STP_VCNT_FRM[2:0]
{0x06EC,0x00},//;-/-/-/PS_VFB_NML_COEF[4:0]
{0x06ED,0x00},//;-/-/-/-/PS_VFB_NML_INTC[3:0]
{0x06EE,0x00},//;-/-/-/PS_VFB_MPS_COEF[4:0]
{0x06EF,0x00},//;-/-/-/-/PS_VFB_MPS_INTC[3:0]
{0x06F0,0x00},//;-/-/-/PS_VFB_NML1[4:0]
{0x06F1,0x1E},//;-/-/-/PS_VFB_NML2[4:0]
{0x06F2,0x1C},//;-/-/-/PS_VFB_NML3[4:0]
{0x06F3,0x18},//;-/-/-/PS_VFB_NML4[4:0]
{0x06F4,0x1F},//;-/-/-/PS_VFB_MPS1[4:0]
{0x06F5,0x1D},//;-/-/-/PS_VFB_MPS2[4:0]
{0x06F6,0x1B},//;-/-/-/PS_VFB_MPS3[4:0]
{0x06F7,0x17},//;-/-/-/PS_VFB_MPS4[4:0]
{0x06F8,0x44},//;BSC_ULMT_AGRNG2[7:0]
{0x06F9,0x50},//;BSC_ULMT_AGRNG1[7:0]
{0x06FA,0x60},//;BSC_ULMT_AGRNG0[7:0]
{0x06FB,0x87},//;KBIASCNT_RNG3[3:0]/KBIASCNT_RNG2[3:0]
{0x06FC,0x64},//;KBIASCNT_RNG1[3:0]/KBIASCNT_RNG0[3:0]
{0x06FD,0x0F},//;-/-/-/-/LIMIT_BSC_MODE[3:0]
{0x0700,0x02},//;SOCD[7:0]
{0x0701,0x03},//;SOEI[7:0]
{0x0702,0x04},//;EOEI[7:0]
{0x0703,0xBC},//;SOSI[7:0]
{0x0704,0xBD},//;EOSI[7:0]
{0x0706,0x01},//;-/-/-/SERI_ON_SW/-/-/-/SERI_ON_MN
{0x0707,0x04},//;-/-/-/-/JTIMES[3:0]
{0x0710,0x68},//;TCLK_POST[7:3]/-/-/-
{0x0711,0x28},//;THS_PREPARE[7:3]/-/-/-
{0x0712,0x60},//;THS_ZERO[7:3]/-/-/-
{0x0713,0x38},//;THS_TRAIL[7:3]/-/-/-
{0x0714,0x38},//;TCLK_TRAIL[7:3]/-/-/-
{0x0715,0x28},//;TCLK_PREPARE[7:3]/-/-/-
{0x0716,0xC8},//;TCLK_ZERO[7:3]/-/-/-
{0x0717,0x30},//;TLPX[7:3]/-/-/-
{0x0718,0x03},//;-/-/-/-/-/-/LNKBTWK_ON/LNKBT_ON
{0x0719,0x02},//;MSB_LBRATE[31:24]
{0x071A,0xA8},//;MSB_LBRATE[23:16]
{0x0721,0x00},//;-/-/-/-/-/-/CLKULPS/ESCREQ
{0x0724,0x00},//;-/-/-/-/-/MIPI_JPEG_ID[2:0]
{0x0725,0x78},//;ESCDATA[7:0]
{0x0727,0x00},//;LVDS_D1_DELAY[3:0]/LVDS_CLK_DELAY[3:0]
{0x0728,0x40},//;-/PHASE_ADJUST[2:0]/-/-/HS_SR_CNT/LP_SR_CNT
{0x072A,0x00},//;PN9/-/-/-/MIPI_TEST_MODE[3:0]
{0x072B,0x00},//;T_VALUE1[7:0]
{0x072C,0x00},//;T_VALUE2[7:0]
{0x072D,0x00},//;-/-/-/-/-/-/-/MIPI_CLK_MODE
{0x072E,0x00},//;-/-/-/-/LB_TEST_CLR/LB_TEST_EN/-/LB_MODE
{0x0730,0x00},//;-/-/-/-/-/-/FIFODLY[9:8]
{0x0731,0x00},//;FIFODLY[7:0]
{0x0732,0xA7},//;NUMWAKE[7:0]
{0x0734,0x5F},//;RV_MAT[7:0]
{0x0735,0x55},//;GU_MAT[7:0]
{0x0736,0xB3},//;GV_MAT[7:0]
{0x0737,0xBD},//;BU_MAT[7:0]
{0x0740,0x3E},//;JPG_QTBLNUM[7:0]
{0x0741,0x3C},//;JPG_HTBLNUM[7:0]
{0x0742,0x00},//;JPG_DRIH[7:0]
{0x0743,0x00},//;JPG_DRIL[7:0]
{0x0744,0x00},//;-/-/-/JPG_PROC[1:0]/-/-/-
{0x0745,0x00},//;-/-/-/-/-/JPG_CTRL[2:0]
{0x0746,0x01},//;-/-/-/-/-/JPG_START[2:0]
{0x074E,0x00},//;JP_SPARE[7:0]
{0x074F,0x00},//;JP_SPARE[15:8]
{0x0F00,0x00},//;-/-/-/T_DACTEST/-/T_TMOSEL[2:0]
{0x0F01,0x00},//;-/-/-/T_OUTSEL[4:0]
{0x0100,0x01},//;-/-/-/-/-/-/-/MODSEL

//AF patch 2012-7-13 /* [ECID:0000] zhangzhao 2012-7-15 optimize focus time*/
{0x2400,0x04},//;
{0x2400,0x00},//;
{0x2401,0x3A},//;
{0x2402,0x31},//;
{0x2403,0x30},//;
{0x2404,0x32},//;
{0x2405,0x30},//;
{0x2406,0x30},//;
{0x2407,0x30},//;
{0x2408,0x30},//;
{0x2409,0x30},//;
{0x240A,0x43},//;
{0x240B,0x38},//;
{0x240C,0x33},//;
{0x240D,0x41},//;
{0x240E,0x34},//;
{0x240F,0x41},//;
{0x2410,0x30},//;
{0x2411,0x30},//;
{0x2412,0x38},//;
{0x2413,0x30},//;
{0x2414,0x45},//;
{0x2415,0x41},//;
{0x2416,0x36},//;
{0x2417,0x46},//;
{0x2418,0x30},//;
{0x2419,0x30},//;
{0x241A,0x43},//;
{0x241B,0x30},//;
{0x241C,0x44},//;
{0x241D,0x42},//;
{0x241E,0x31},//;
{0x241F,0x31},//;
{0x2420,0x30},//;
{0x2421,0x41},//;
{0x2422,0x30},//;
{0x2423,0x46},//;
{0x2424,0x30},//;
{0x2425,0x30},//;
{0x2426,0x45},//;
{0x2427,0x32},//;
{0x2428,0x34},//;
{0x2429,0x30},//;
{0x242A,0x43},//;
{0x242B,0x34},//;
{0x242C,0x0D},//;
{0x242D,0x0A},//;
{0x2401,0x3A},//;
{0x2402,0x31},//;
{0x2403,0x30},//;
{0x2404,0x32},//;
{0x2405,0x30},//;
{0x2406,0x31},//;
{0x2407,0x30},//;
{0x2408,0x30},//;
{0x2409,0x30},//;
{0x240A,0x30},//;
{0x240B,0x41},//;
{0x240C,0x30},//;
{0x240D,0x46},//;
{0x240E,0x38},//;
{0x240F,0x30},//;
{0x2410,0x46},//;
{0x2411,0x32},//;
{0x2412,0x37},//;
{0x2413,0x38},//;
{0x2414,0x33},//;
{0x2415,0x32},//;
{0x2416,0x45},//;
{0x2417,0x41},//;
{0x2418,0x36},//;
{0x2419,0x46},//;
{0x241A,0x30},//;
{0x241B,0x30},//;
{0x241C,0x43},//;
{0x241D,0x30},//;
{0x241E,0x44},//;
{0x241F,0x41},//;
{0x2420,0x45},//;
{0x2421,0x46},//;
{0x2422,0x34},//;
{0x2423,0x41},//;
{0x2424,0x30},//;
{0x2425,0x35},//;
{0x2426,0x38},//;
{0x2427,0x41},//;
{0x2428,0x45},//;
{0x2429,0x38},//;
{0x242A,0x45},//;
{0x242B,0x38},//;
{0x242C,0x0D},//;
{0x242D,0x0A},//;
{0x2401,0x3A},//;
{0x2402,0x31},//;
{0x2403,0x30},//;
{0x2404,0x32},//;
{0x2405,0x30},//;
{0x2406,0x32},//;
{0x2407,0x30},//;
{0x2408,0x30},//;
{0x2409,0x30},//;
{0x240A,0x30},//;
{0x240B,0x35},//;
{0x240C,0x46},//;
{0x240D,0x32},//;
{0x240E,0x37},//;
{0x240F,0x38},//;
{0x2410,0x34},//;
{0x2411,0x41},//;
{0x2412,0x30},//;
{0x2413,0x36},//;
{0x2414,0x38},//;
{0x2415,0x41},//;
{0x2416,0x46},//;
{0x2417,0x32},//;
{0x2418,0x37},//;
{0x2419,0x38},//;
{0x241A,0x34},//;
{0x241B,0x41},//;
{0x241C,0x31},//;
{0x241D,0x33},//;
{0x241E,0x38},//;
{0x241F,0x41},//;
{0x2420,0x46},//;
{0x2421,0x32},//;
{0x2422,0x37},//;
{0x2423,0x38},//;
{0x2424,0x34},//;
{0x2425,0x41},//;
{0x2426,0x39},//;
{0x2427,0x43},//;
{0x2428,0x36},//;
{0x2429,0x30},//;
{0x242A,0x36},//;
{0x242B,0x36},//;
{0x242C,0x0D},//;
{0x242D,0x0A},//;
{0x2401,0x3A},//;
{0x2402,0x30},//;
{0x2403,0x39},//;
{0x2404,0x32},//;
{0x2405,0x30},//;
{0x2406,0x33},//;
{0x2407,0x30},//;
{0x2408,0x30},//;
{0x2409,0x30},//;
{0x240A,0x46},//;
{0x240B,0x32},//;
{0x240C,0x46},//;
{0x240D,0x39},//;
{0x240E,0x30},//;
{0x240F,0x31},//;
{0x2410,0x46},//;
{0x2411,0x45},//;
{0x2412,0x30},//;
{0x2413,0x30},//;
{0x2414,0x38},//;
{0x2415,0x30},//;
{0x2416,0x43},//;
{0x2417,0x30},//;
{0x2418,0x33},//;
{0x2419,0x41},//;
{0x241A,0x46},//;
{0x241B,0x41},//;
{0x241C,0x34},//;
{0x241D,0x39},//;
{0x241E,0x0D},//;
{0x241F,0x0A},//;
{0x2401,0x3A},//;
{0x2402,0x30},//;
{0x2403,0x35},//;
{0x2404,0x38},//;
{0x2405,0x30},//;
{0x2406,0x30},//;
{0x2407,0x30},//;
{0x2408,0x30},//;
{0x2409,0x30},//;
{0x240A,0x46},//;
{0x240B,0x45},//;
{0x240C,0x30},//;
{0x240D,0x30},//;
{0x240E,0x32},//;
{0x240F,0x30},//;
{0x2410,0x46},//;
{0x2411,0x43},//;
{0x2412,0x46},//;
{0x2413,0x45},//;
{0x2414,0x36},//;
{0x2415,0x33},//;
{0x2416,0x0D},//;
{0x2417,0x0A},//;
{0x2401,0x3A},//;
{0x2402,0x30},//;
{0x2403,0x30},//;
{0x2404,0x30},//;
{0x2405,0x30},//;
{0x2406,0x30},//;
{0x2407,0x30},//;
{0x2408,0x30},//;
{0x2409,0x31},//;
{0x240A,0x46},//;
{0x240B,0x46},//;
{0x240C,0x0D},//;
{0x240D,0x0A},//;
{0x2400,0x03},//;
{0x2400,0x02},//;
};


static struct msm_camera_i2c_reg_conf jt8ev5_prev_settings[] = {

	//NAME,FIRM_START
	/*{0x2400,		0x03},	//		
	{0x2400,		0x02},	//		
	{0x0100,		0x01},	//	STREAM ON
	{0x27FF,		0xF0},	//	 ENABLE DRIVER
	{0x2401,		0x00},	//	 INF MSB[1:0]
	{0x2402,		0xB0},	//	 INF LSB[7:0]
	{0x27FF,		0xF1},	//	 SET_INF_POSITION
	{0x2401,		0x01},	//	 MAC MSB[1:0]
	{0x2402,		0x70},	//	 MAC LSB[7:0]
	{0x27FF,		0xF2},	//	 SET_MACRO_POSITION
	{0x2401,		0x40},	//	
	{0x2402,		0x40},	//	
	{0x2403,		0x00},	//	
	{0x27FF,		0x62},	//	
	{0x2401,		0x42},	//	
	{0x2402,		0x80},	//	
	{0x2403,		0x00},	//	
	{0x27FF,		0x62},	//	
	{0x2401,		0x44},	//	
	{0x2402,		0x14},	//	
	{0x27FF,		0x61},	//	
	{0x2401,		0x48},	//	
	{0x2402,		0x13},	//	
	{0x27FF,		0x61},	//	
	{0x2401,		0x4C},	//	
	{0x2402,		0x12},	//	
	{0x27FF,		0x61},	//	
	{0x2401,		0x45},	//	
	{0x2402,		0x00},	//	
	{0x27FF,		0x61},	//	
	{0x2401,		0x46},	//	
	{0x2402,		0x00},	//	
	{0x2403,		0x00},	//	,	//	
	{0x27FF,		0x62},	//	,	//	
	{0x2401,		0x49},	//	,	//	
	{0x2402,		0x00},	//	,	//	
	{0x27FF,		0x61},	//	,	//	
	{0x2401,		0x4A},	//	,	//	
	{0x2402,		0x00},	//	
	{0x2403,		0x00},	//	
	{0x27FF,		0x62},	//	
	{0x2401,		0x4D},	//	
	{0x2402,		0x00},	//	
	{0x27FF,		0x61},	//	
	{0x2401,		0x4E},	//	
	{0x2402,		0x2C},	//	
	{0x2403,		0x01},	//	
	{0x27FF,		0x62},	//	
	{0x2401,		0x00},	//	SET DEFAULT POSITION=0
	{0x27FF,		0x3F},	//	INITIALIZE
*/
	{0x2401,		0x15},	//	
	{0x2402,		0x33},	//	
	{0x27ff,		0xe1},	//	


	{0x27FF,		0xF7},	//	finish AF //
	{0x0102,		0x03},	//	-/-/-/-/-/-/VLAT_ON/GROUP_HOLD
	{0x0105,		0x00},	//	- / - / - / - / - / H_COUNT[10:8] 
	{0x0106,		0xB4},	//	H_COUNT[7:0] 
	{0x0107,		0x00},	//	- / - / - / - / - / V_COUNT[10:8] 
	{0x0108,		0xB6},	//	V_COUNT[7:0] 
	{0x0109,		0x00},	//	- / - / - / - / - / - / - / SCALE_M[8] 
	{0x010A,		0x20},	//	SCALE_M[7:0] 
	{0x010B,		0x11},	//	- / V_ANABIN[2:0] / - / - / - / H_ANABIN 
	{0x010D,		0x05},	//	- / - / - / - / HOUTPIX[11:8] 
	{0x010E,		0x00},	//	HOUTPIX[7:0] 
	{0x010F,		0x03},	//	- / - / - / - / - / VOUTPIX[10:8] 
	{0x0110,		0xC0},	//	VOUTPIX[7:0] 
	{0x0111,		0x00},	//	- / - / - / - / - / - / HCROP[1:0] 
	{0x0112,		0x00},	//	- / - / - / - / - / - / VCROP[9:8] 
	{0x0113,		0x00},	//	VCROP[7:0] 
	{0x0229,		0x2B},	//	Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
       {0x0305,        0x02},    //-/-/-/-/AGMAX[11:8]
       {0x0306,        0x7F},    //AGMAX[7:0]

	
	{0x0316,		0x6C},	//	FLLONGON/FRMSPD[1:0]/FL600S[12:8]
	{0x0317,		0x09},	//	FL600S[7:0]
		
	//{0x0300,		0x02},	  //	ALC On   Ų������Ԥ����д�˼Ĵ�������ֹALC��������
	{0x0320,		0x81},	  // AWB On
	{0x0321,		0x00},
	{0x0322,		0x3D},
	{0x0323,		0x00},
	{0x0324,		0x15},
	{0x0325,		0x00},

	{0x0204,0x5B},//;LM_RMG[7:0]
 	{0x0205,0x09},//;LM_RMB[7:0]
	{0x0206,0x1A},//;LM_GMR[7:0]
	{0x0207,0x1C},//;LM_GMB[7:0]
	{0x0208,0x04},//;LM_BMR[7:0]
	{0x0209,0x54},//;LM_BMG[7:0]
	{0x0223,0x57},//;CbG_MAT[7:0]
	{0x0224,0x83},//;CbB_MAT[7:0]
	{0x0225,0x80},//;Cb_GAIN[7:0]
	{0x0226,0x83},//;CrR_MAT[7:0]
	{0x0227,0x6E},//;CrG_MAT[7:0]
	{0x0228,0x80},//;Cr_GAIN[7:0]

	
	{0x0102,		0x02},	//	-/-/-/-/-/-/VLAT_ON/GROUP_HOLD
};




static struct msm_camera_i2c_reg_conf jt8ev5_snap_autofocus_settings[] = {
{0x2400,0x03},//;   
{0x2400,0x02},//;   
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x0100,0x01},//;STREAM ON
{0x27FF,0xF0},//; ENABLE DRIVER
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x00},//; INF MSB[1:0]
{0x2402,0x50},//; INF LSB[7:0]
{0x27FF,0xF1},//; SET_INF_POSITION
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x01},//; MAC MSB[1:0]
{0x2402,0x90},//; MAC LSB[7:0]-------------------------
{0x27FF,0xF2},//; SET_MACRO_POSITION
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x40},//;
{0x2402,0x40},//;
{0x2403,0x00},//;
{0x27FF,0x62},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x42},//;
{0x2402,0x80},//;
{0x2403,0x00},//;
{0x27FF,0x62},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x44},//;
{0x2402,0x14},//;
{0x27FF,0x61},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x48},//;
{0x2402,0x13},//;
{0x27FF,0x61},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x4C},//;
{0x2402,0x12},//;
{0x27FF,0x61},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x45},//;
{0x2402,0x00},//;
{0x27FF,0x61},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x46},//;
{0x2402,0x00},//;
{0x2403,0x00},//;
{0x27FF,0x62},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x49},//;
{0x2402,0x00},//;
{0x27FF,0x61},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x4A},//;
{0x2402,0x00},//;
{0x2403,0x00},//;
{0x27FF,0x62},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x4D},//;
{0x2402,0x00},//;
{0x27FF,0x61},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x4E},//;
{0x2402,0x2C},//;
{0x2403,0x01},//;
{0x27FF,0x62},//;
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x00},//; SET DEFAULT POSITION=0
{0x27FF,0x3F},//; INITIALIZE
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x16},//; Type1 Reg Addr Lower
{0x2402,0x13},//; Write Data (AF Window size 25%)
{0x27FF,0xE1},//; Write Trigger
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x2401,0x17},//; //�Խ���׼�޸�
{0x2402,0x00},//; 
{0x27FF,0xE1},//; 
{0x2800,0x00,0,MSM_CAMERA_I2C_BYTE_DATA,MSM_CAMERA_I2C_CMD_CHECK},
{0x27FF,0x28},//; Trigger cmd
};

static struct msm_camera_i2c_reg_conf jt8ev5_snap_settings[] = {
	
	{0x0102,		0x03},	//	-/-/-/-/-/-/VLAT_ON/GROUP_HOLD
	{0x0105,		0x01},	//	- / - / - / - / - / H_COUNT[10:8] 
	{0x0106,		0x5F},	//	H_COUNT[7:0] 
	{0x0107,		0x00},	//	- / - / - / - / - / V_COUNT[10:8] 
	{0x0108,		0xF7},	//	V_COUNT[7:0] 
	{0x0109,		0x00},	//	- / - / - / - / - / - / - / SCALE_M[8] 
	{0x010A,		0x10},	//	SCALE_M[7:0] 
	{0x010B,		0x00},	//	- / V_ANABIN[2:0] / - / - / - / H_ANABIN 
	{0x010D,		0x0A},	//	- / - / - / - / HOUTPIX[11:8] 
	{0x010E,		0x20},	//	HOUTPIX[7:0] 
	{0x010F,		0x07},	//	- / - / - / - / - / VOUTPIX[10:8] 
	{0x0110,		0x98},	//	VOUTPIX[7:0] 
	{0x0111,		0x00},	//	- / - / - / - / - / - / HCROP[1:0] 
	{0x0112,		0x00},	//	- / - / - / - / - / - / VCROP[9:8] 
	{0x0113,		0x00},	//	VCROP[7:0] 
	//{0x0229,		0x2B},	//	Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]   2b----->0b  zhangzhao 2012-8-8
       {0x0305,        0x00},    //-/-/-/-/AGMAX[11:8]   2b----->0b  zhangzhao 2012-8-8
       {0x0306,        0xFF},   //AGMAX[7:0]   0XA0--------->0XFF   ZZ    2b----->0b  zhangzhao 2012-8-8
	{0x0316,		0x66},	//	FLLONGON/FRMSPD[1:0]/FL600S[12:8]
	{0x0317,		0x2C},	//	FL600S[7:0]
	{0x0102,		0x02},	//	-/-/-/-/-/-/VLAT_ON/GROUP_HOLD
};

#ifdef EFFECT_ADD

static struct msm_camera_i2c_reg_conf jt8ev5_saturation[][1] = 
{	
   	{//level 0
         {0x0229,0x29},
	},
	
	{//level 1
         {0x0229,0x2a},
	},
	
	{//level 2 -default level
         {0x0229,0x2b},
	},
	
	{//level 3
         {0x0229,0x2c},
	},
	
	{//level 4
         {0x0229,0x2d},
	},
};

// contrast
static struct msm_camera_i2c_reg_conf jt8ev5_contrast[][1] = {
      	{//level 0
          {0x0249,0x67},//CONT_LEV[7:0]; 
	},

       {//level 1
          {0x0249,0x77},//CONT_LEV[7:0]; 
       },

       {//default
          {0x0249,0x87},//CONT_LEV[7:0]; 
       },

       {//level 3
          {0x0249,0x97},//CONT_LEV[7:0]; 
       },

       {//level 4
          {0x0249,0xa7},//CONT_LEV[7:0]; 
       },
};


// sharpness
static struct msm_camera_i2c_reg_conf jt8ev5_sharpness[][2] = {
	{//level 2 -auto mode
        	{0x023A,0x08},//;SHP_PGAIN1[3:0]/SHP_PGAIN0[3:0]
       	{0x023C,0x08},//;SHP_MGAIN1[3:0]/SHP_MGAIN0[3:0]
	 },
       {//level 2 -auto mode
        	{0x023A,0x04},//;SHP_PGAIN1[3:0]/SHP_PGAIN0[3:0]
       	{0x023C,0x04},//;SHP_MGAIN1[3:0]/SHP_MGAIN0[3:0]
	 },
	 {//level 2 -auto mode
        	{0x023A,0x08},//;SHP_PGAIN1[3:0]/SHP_PGAIN0[3:0]
       	{0x023C,0x08},//;SHP_MGAIN1[3:0]/SHP_MGAIN0[3:0]
	 },
       {//level 2 -auto mode
        	{0x023A,0x0c},//;SHP_PGAIN1[3:0]/SHP_PGAIN0[3:0]
       	{0x023C,0x0c},//;SHP_MGAIN1[3:0]/SHP_MGAIN0[3:0]
	 },
       {//level 2 -auto mode
        	{0x023A,0x0f},//;SHP_PGAIN1[3:0]/SHP_PGAIN0[3:0]
       	{0x023C,0x0f},//;SHP_MGAIN1[3:0]/SHP_MGAIN0[3:0]
	 },
	
};

static struct msm_camera_i2c_reg_conf jt8ev5_brightness[][1] = {
       {//level 0
          {0x0248,0xc8},//BRIGHT[7:0]; 
	 },
	 
     	{//level 1
          {0x0248,0xe8},//BRIGHT[7:0]; 
	 },
	 {//l default
         {0x0248,0x08},//BRIGHT[7:0]; 
	 },
	 {//level 3
         {0x0248,0x28},//BRIGHT[7:0]; 
	 },
	 {//level 4
          {0x0248,0x48},//BRIGHT[7:0]; 
	 },
};

// exposure
static struct msm_camera_i2c_reg_conf jt8ev5_exposure[][2] = {
	{// -1.7EV    -2
         //Exposure Compensation default
           {0x0302,0x00},//-/-/-/-/-/-/ALCAIM[9:8]; 
           {0x0303,0xe0},//ALCAIM[7:0]; 
       },
       
	{ // -1.0EV   -1
         //Exposure Compensation default
           {0x0302,0x00},//-/-/-/-/-/-/ALCAIM[9:8]; 
           {0x0303,0xf0},//ALCAIM[7:0]; 
       },
       
	{//  0
         //Exposure Compensation default
           {0x0302,0x01},//-/-/-/-/-/-/ALCAIM[9:8]; 
          {0x0303,0x10},//ALCAIM[7:0]; 
       },
       
	{//+1
         //Exposure Compensation default
           {0x0302,0x01},//-/-/-/-/-/-/ALCAIM[9:8]; 
           {0x0303,0x30},//ALCAIM[7:0]; 
	},
	
	{ //+2
         //Exposure Compensation default
           {0x0302,0x01},//-/-/-/-/-/-/ALCAIM[9:8]; 
           {0x0303,0x50},//ALCAIM[7:0]; 
	},

};

// special  effect
static struct msm_camera_i2c_reg_conf jt8ev5_effect[][3] = {
    { //effect_off
       {0x0115,0x00},//-/-/-/-/PICEFF[3:0];
    },

    {  //effect_mono
       {0x0115,0x07},//-/-/-/-/PICEFF[3:0];
    },

    { //effect_negative
       {0x0115,0x03},//-/-/-/-/PICEFF[3:0];
    },
  
    {//SOLARIZE
       {0x0115,0x00},//-/-/-/-/PICEFF[3:0];
    },

    {//SEPIA
       {0x0115,0x05},//-/-/-/-/PICEFF[3:0];
    },

    { 
    //redish
      {0x0115,0x04},//;-/-/-/-/PICEFF[3:0]
	{0x0258,0x68},//;UNICOFSU[7:0]
	{0x0259,0xC0},//;UNICOFSV[7:0]

    },

   { 
    //blueish
      {0x0115,0x04},//;-/-/-/-/PICEFF[3:0]
	{0x0258,0xc0},//;UNICOFSU[7:0]
	{0x0259,0x49},//;UNICOFSV[7:0]
    },
    
    { 
    //greenish
      {0x0115,0x04},//;-/-/-/-/PICEFF[3:0]
	{0x0258,0x55},//;UNICOFSU[7:0]
	{0x0259,0x49},//;UNICOFSV[7:0]
    },      
};


// awb
static struct msm_camera_i2c_reg_conf jt8ev5_awb[][5] = {	
	{ //MSM_V4L2_WB_MIN_MINUS_1,not used
//CAMERA_WB_AUTO                //1
         {0x0320,0x81},//AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8];
         {0x0420,0x00},//PWBGAINGR[7:0];
         {0x0421,0x00},//PWBGAINGB[7:0];
         {0x0422,0x5a},//PWBGAINR[7:0];
         {0x0423,0x3b},//PWBGAINB[7:0];
	}, 
	
	{ // wb_auto
//CAMERA_WB_AUTO                //1
         {0x0320,0x81},//AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8];
         {0x0420,0x00},//PWBGAINGR[7:0];
         {0x0421,0x00},//PWBGAINGB[7:0];
         {0x0422,0x5a},//PWBGAINR[7:0];
         {0x0423,0x3b},//PWBGAINB[7:0];
	}, 
       {//MSM_V4L2_WB_CUSTOM,not used
         {0x0320,0x81},//AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8];
         {0x0420,0x00},//PWBGAINGR[7:0];
         {0x0421,0x00},//PWBGAINGB[7:0];
         {0x0422,0x5a},//PWBGAINR[7:0];
         {0x0423,0x3b},//PWBGAINB[7:0];
	},

	{//INCANDESCENT,  //�׳�
         {0x0320,0x01},//AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8];
         {0x0420,0x00},//PWBGAINGR[7:0];
         {0x0421,0x00},//PWBGAINGB[7:0];
         {0x0422,0x63},//PWBGAINR[7:0];
         {0x0423,0x78},//PWBGAINB[7:0];
	},

       {//FLUORESCENT,    //ӫ��
         {0x0320,0x01},//AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8];
         {0x0420,0x00},//PWBGAINGR[7:0];
         {0x0421,0x00},//PWBGAINGB[7:0];
         {0x0422,0x53},//PWBGAINR[7:0];
         {0x0423,0x88},//PWBGAINB[7:0];
       },

       { //daylight
         {0x0320,0x01},//AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8];
         {0x0420,0x00},//PWBGAINGR[7:0];
         {0x0421,0x00},//PWBGAINGB[7:0];
         {0x0422,0x73},//PWBGAINR[7:0];
         {0x0423,0x48},//PWBGAINB[7:0];
       },

       { //cloudy
         {0x0320,0x01},//AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8];
         {0x0420,0x00},//PWBGAINGR[7:0];
         {0x0421,0x00},//PWBGAINGB[7:0];
         {0x0422,0x8B},//PWBGAINR[7:0];
         {0x0423,0x38},//PWBGAINB[7:0];
       },
};

//anti-banding
static struct msm_camera_i2c_reg_conf jt8ev5_antibanding[][1] = {		
       {//off.not used
//Auto-XCLK24MHz
         {0x0318,0xD6},//ACFDET/AC60M/FLMANU/ACDETDLY/MSKLINE[1:0]/ACDPWAIT[1:0];
       },

       {//60Hz
//Auto-XCLK24MHz
         {0x0318,0x56},//ACFDET/AC60M/FLMANU/ACDETDLY/MSKLINE[1:0]/ACDPWAIT[1:0];
       },
       
	{//50Hz
//Auto-XCLK24MHz
         {0x0318,0x16},//ACFDET/AC60M/FLMANU/ACDETDLY/MSKLINE[1:0]/ACDPWAIT[1:0];
	},

       { //auto
//Auto-XCLK24MHz
         {0x0318,0xD6},//ACFDET/AC60M/FLMANU/ACDETDLY/MSKLINE[1:0]/ACDPWAIT[1:0];
	}, 
};

//ISO
static struct msm_camera_i2c_reg_conf jt8ev5_iso[][2] = {	
	
	{ //auto
	{0x0305,0x02},//;-/-/-/-/AGMAX[11:8]
	{0x0306,0x7F},//;AGMAX[7:0]
	}, 
	
	{//iso_100
	{0x0305,0x00},//;-/-/-/-/AGMAX[11:8]
	{0x0306,0x67},//;AGMAX[7:0]
	},

       {//iso200
	{0x0305,0x00},//;-/-/-/-/AGMAX[11:8]
	{0x0306,0xce},//;AGMAX[7:0]
       },

       { //iso400
	{0x0305,0x01},//;-/-/-/-/AGMAX[11:8]
	{0x0306,0x9c},//;AGMAX[7:0]
       },

       { //iso800
	{0x0305,0x02},//;-/-/-/-/AGMAX[11:8]
	{0x0306,0x7f},//;AGMAX[7:0]
       },
       
       { //iso1600
	{0x0305,0x04},//;-/-/-/-/AGMAX[11:8]
	{0x0306,0xfe},//;AGMAX[7:0]
       },
};


//scene
static struct msm_camera_i2c_reg_conf jt8ev5_scene[][18]={

    //normal
      {
      {0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
      {0x0108,0xB6},//;V_COUNT[7:0]   0X96----->0XB6   ZZ
      {0x0229,0x2B},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
      {0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
      {0x0249,0x87},//;CONT_LEV[7:0]
      {0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
      {0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
      {0x0303,0x10},//;ALCAIM[7:0]
      {0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
      {0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
      {0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
      {0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
      {0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
      {0x0321,0x00},//;WBMRG[7:0]
      {0x0420,0x00},//;PWBGAINGR[7:0]
      {0x0421,0x00},//;PWBGAINGB[7:0]
      {0x0422,0x5A},//;PWBGAINR[7:0]
      {0x0423,0x3B},//;PWBGAINB[7:0]
      },
	
      //MSM_V4L2_SCENE_LANDSCAPE
      	{
       {0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
       {0x0108,0xB6},//;V_COUNT[7:0]
       {0x0229,0x2D},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
       {0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
       {0x0249,0x87},//;CONT_LEV[7:0]
       {0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
       {0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
       {0x0303,0x10},//;ALCAIM[7:0]
       {0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
       {0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
       {0x030E,0xBF},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
       {0x030F,0xF0},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
       {0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
       {0x0321,0x00},//;WBMRG[7:0]
       {0x0420,0x00},//;PWBGAINGR[7:0]
       {0x0421,0x00},//;PWBGAINGB[7:0]
       {0x0422,0x5A},//;PWBGAINR[7:0]
       {0x0423,0x3B},//;PWBGAINB[7:0]
       },
       
      //NAME,Fire_mode
       {
       {0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
       {0x0108,0xB6},//;V_COUNT[7:0]
       {0x0229,0x2B},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
       {0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
       {0x0249,0x87},//;CONT_LEV[7:0]
       {0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
       {0x0302,0x00},//;-/-/-/-/-/-/ALCAIM[9:8]
       {0x0303,0xE0},//;ALCAIM[7:0]
       {0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
       {0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
       {0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
       {0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
       {0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
       {0x0321,0x00},//;WBMRG[7:0]
       {0x0420,0x00},//;PWBGAINGR[7:0]
       {0x0421,0x00},//;PWBGAINGB[7:0]
       {0x0422,0x5A},//;PWBGAINR[7:0]
       {0x0423,0x3B},//;PWBGAINB[7:0]
       },
      
       //beach_mode
       	{
       {0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
       {0x0108,0xB6},//;V_COUNT[7:0]
       {0x0229,0x2D},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
       {0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
       {0x0249,0x87},//;CONT_LEV[7:0]
       {0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
       {0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
       {0x0303,0x30},//;ALCAIM[7:0]
       {0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
       {0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
       {0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
       {0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
       {0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
       {0x0321,0x00},//;WBMRG[7:0]
       {0x0420,0x00},//;PWBGAINGR[7:0]
       {0x0421,0x00},//;PWBGAINGB[7:0]
       {0x0422,0x5A},//;PWBGAINR[7:0]
       {0x0423,0x3B},//;PWBGAINB[7:0]
       },

       //party
       {
       {0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
       {0x0108,0xB6},//;V_COUNT[7:0]
       {0x0229,0x2D},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
       {0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
       {0x0249,0x87},//;CONT_LEV[7:0]
       {0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
       {0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
       {0x0303,0x10},//;ALCAIM[7:0]
       {0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
       {0x030D,0x55},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
       {0x030E,0x55},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
       {0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
       {0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
       {0x0321,0x00},//;WBMRG[7:0]
       {0x0420,0x00},//;PWBGAINGR[7:0]
       {0x0421,0x00},//;PWBGAINGB[7:0]
       {0x0422,0x5A},//;PWBGAINR[7:0]
       {0x0423,0x3B},//;PWBGAINB[7:0]
       },

     //  NAME,person_mode
      {
{0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
{0x0108,0xB6},//;V_COUNT[7:0]
{0x0229,0x2D},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
{0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
{0x0249,0x87},//;CONT_LEV[7:0]
{0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
{0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
{0x0303,0x20},//;ALCAIM[7:0]
{0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
{0x030D,0x5F},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
{0x030E,0xD5},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
{0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
{0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
{0x0321,0x00},//;WBMRG[7:0]
{0x0420,0x00},//;PWBGAINGR[7:0]
{0x0421,0x00},//;PWBGAINGB[7:0]
{0x0422,0x5A},//;PWBGAINR[7:0]
{0x0423,0x3B},//;PWBGAINB[7:0]
},
       
     //  NAME,Evening_mode
     {
{0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
{0x0108,0xB6},//;V_COUNT[7:0]
{0x0229,0x2B},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
{0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
{0x0249,0x87},//;CONT_LEV[7:0]
{0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
{0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
{0x0303,0x10},//;ALCAIM[7:0]
{0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
{0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
{0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
{0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
{0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
{0x0321,0x80},//;WBMRG[7:0]
{0x0420,0x40},//;PWBGAINGR[7:0]
{0x0421,0x40},//;PWBGAINGB[7:0]
{0x0422,0xDE},//;PWBGAINR[7:0]
{0x0423,0x03},//;PWBGAINB[7:0]
},

     // NAME,snow_mode
     {
{0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
{0x0108,0xB6},//;V_COUNT[7:0]
{0x0229,0x2B},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
{0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
{0x0249,0x87},//;CONT_LEV[7:0]
{0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
{0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
{0x0303,0x50},//;ALCAIM[7:0]
{0x030C,0xFF},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
{0x030D,0xDA},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
{0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
{0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
{0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
{0x0321,0x00},//;WBMRG[7:0]
{0x0420,0x00},//;PWBGAINGR[7:0]
{0x0421,0x00},//;PWBGAINGB[7:0]
{0x0422,0x5A},//;PWBGAINR[7:0]
{0x0423,0x3B},//;PWBGAINB[7:0]
},

		 
    //  NAME,night(8-24fps)_mode
    {
{0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
{0x0108,0x96},//;V_COUNT[7:0]
{0x0229,0x2B},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
{0x022A,0x04},//;-/-/-/-/Cbr_MGAIN2[3:0]
{0x0249,0x87},//;CONT_LEV[7:0]
{0x0315,0xA8},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
{0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
{0x0303,0x10},//;ALCAIM[7:0]
{0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
{0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
{0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
{0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
{0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
{0x0321,0x00},//;WBMRG[7:0]
{0x0420,0x00},//;PWBGAINGR[7:0]
{0x0421,0x00},//;PWBGAINGB[7:0]
{0x0422,0x5A},//;PWBGAINR[7:0]
{0x0423,0x3B},//;PWBGAINB[7:0]
},

    //  NAME,Sport(28.9fps)_mode
    {
{0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
{0x0108,0x7D},//;V_COUNT[7:0]
{0x0229,0x2B},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
{0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
{0x0249,0x87},//;CONT_LEV[7:0]
{0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
{0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
{0x0303,0x10},//;ALCAIM[7:0]
{0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
{0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
{0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
{0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
{0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
{0x0321,0x00},//;WBMRG[7:0]
{0x0420,0x00},//;PWBGAINGR[7:0]
{0x0421,0x00},//;PWBGAINGB[7:0]
{0x0422,0x5A},//;PWBGAINR[7:0]
{0x0423,0x3B},//;PWBGAINB[7:0]
},

    //   NAME,Candle light_mode
    {
{0x0107,0x00},//;-/-/-/-/-/V_COUNT[10:8]
{0x0108,0xB6},//;V_COUNT[7:0]
{0x0229,0x2D},//;Cbr_MGAIN1[3:0]/Cbr_MGAIN0[3:0]
{0x022A,0x00},//;-/-/-/-/Cbr_MGAIN2[3:0]
{0x0249,0x87},//;CONT_LEV[7:0]
{0x0315,0x08},//;FAUTO/FCOUNT[2:0]/FCLSBON/EXPLIM[2:0]
{0x0302,0x01},//;-/-/-/-/-/-/ALCAIM[9:8]
{0x0303,0x10},//;ALCAIM[7:0]
{0x030C,0x55},//;A1WEIGHT[1:0]/A2WEIGHT[1:0]/A3WEIGHT[1:0]/A4WEIGHT[1:0]
{0x030D,0x5A},//;A5WEIGHT[1:0]/B1WEIGHT[1:0]/B2WEIGHT[1:0]/B3WEIGHT[1:0]
{0x030E,0x95},//;B4WEIGHT[1:0]/B5WEIGHT[1:0]/C1WEIGHT[1:0]/C2WEIGHT[1:0]
{0x030F,0x50},//;C3WEIGHT[1:0]/C4WEIGHT[1:0]/C5WEIGHT[1:0]/-/-
{0x0320,0x81},//;AWBSW/AWBONDOT[2:0]/-/-/WBMRG[9:8]
{0x0321,0xc0},//;WBMRG[7:0]
{0x0420,0x40},//;PWBGAINGR[7:0]
{0x0421,0x40},//;PWBGAINGB[7:0]
{0x0422,0xDE},//;PWBGAINR[7:0]
{0x0423,0x03},//;PWBGAINB[7:0]
},
};

#endif

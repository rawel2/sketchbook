/* 1.2 LG 2.6� Initial Code*/ 
void ILI9341_LG2.6_Initial(void)
{
/* VCI=2.8V*/ 
/************** Reset LCD Driver ****************//*/ 
LCD_nRESET = 1;
delayms(1); /* Delay 1ms*/ 
LCD_nRESET = 0;
delayms(10); /* Delay 10ms // This delay time is necessary*/ 
LCD_nRESET = 1;
delayms(120); /* Delay 120 ms*/ 
/************** Start Initial Sequence **********//*/ 
    (0xCB),0x39,0x2C,0x00,0x34,0x02,
    (0xCF),0x00,0xC1,0x30,
    (0xE8),0x85,0x00,0x78,
    (0xEA),0x00,0x00,
    (0xED),0x64,0x03,0x12,0x81)
    (0xF7),0x20,
    (0xC0), /*Power control*/ 0x23, /*VRH[5:0]*/ 
    (0xC1), /*Power control*/ 0x10, /*SAP[2:0];BT[3:0]*/ 
    (0xC5), /*VCM control*/ 0x2B,0x2B,
/*    (0xC7), /*VCM control2*/ */ 
/*LCD_ILI9341_INDEX(0xC0,*/ 
    (0x36), /* Memory Access Control*/ 0x48,
    (0xB1),0x00,0x1B,
    (0xB6), /* Display Function Control*/ 0x0A,0x02,
    (0xF2), /* 3Gamma Function Disable*/ 0x00,
    (0x26), /*Gamma curve selected*/ 0x01,
    (0xE0), /*Set Gamma*/ 0x0F,0x31,0x2B,0x0C,0x0E,0x08,0x4E,0xF1,0x37,0x07,0x10,0x03,0x0E,0x09,0x00,
    (0xE1), /*Set Gamma*/ 0x00,0x0E,0x14,0x03,0x11,0x07,0x31,0xC1,0x48,0x08,0x0F,0x0C,0x31,0x36,0x0F,
    (0x11), /*Exit Sleep*/ 
    TFTLCD_DELAY8, 120, 
    (0x29), /*Display on*/ 
}


/* 2.2 BOE 2.0� Initial Code*/ 
void ILI9341_BOE2.0_Initial(void)
{
/* VCI=2.8V*/ 
/************** Reset LCD Driver ****************//*/ 
LCD_nRESET = 1;
delayms(1); /* Delay 1ms*/ 
LCD_nRESET = 0;
delayms(10); /* Delay 10ms // This delay time is necessary*/ 
LCD_nRESET = 1;
delayms(120); /* Delay 120 ms*/ 
/************** Start Initial Sequence **********//*/ 
    (0xCF),0x00,0x99,0x30,
    (0xED),0x64,0x03,0x12,0x81,
    (0xE8),0x85,0x10,0x78,
    (0xCB),0x39,0x2C,0x00,0x34,0x02,
    (0xF7),0x20,
    (0xEA),0x00,0x00,
    (0xC0), /*Power control*/ 0x26, /*VRH[5:0]*/ 
    (0xC1), /*Power control*/ 0x12, /*SAP[2:0];BT[3:0]*/ 
    (0xC5), /*VCM control*/ 0x2B,0x2C,
    (0xC7), /*VCM control2*/ 0xC4,
    (0x36), /* Memory Access Control*/ 0x08,
    (0xB1),0x00,0x1B,
    (0xB6), /* Display Function Control*/ 0x0A,0xA2,
    (0xF2), /* 3Gamma Function Disable*/ 0x00,
    (0x26), /*Gamma curve selected*/ 0x01,
    (0xE0), /*Set Gamma*/ 0x0F,0x24,0x21,0x0A,0x0E,0x09,0x51,0xA9,0x44,0x07,0x10,0x03,0x2C,0x0B,0x00,
    (0xE1), /*Set Gamma*/ 0x00,0x1B,0x1E,0x05,0x11,0x06,0x2E,0x56,0x3B,0x08,0x0F,0x0C,0x13,0x14,0x0F,
    (0x11), /*Exit Sleep*/ 
    TFTLCD_DELAY8, 120, 
    (0x29), /*Display on*/ 
}

/* 2.3 BOE 2.4� Initial Code*/ 
void ILI9341_BOE2.4_Initial(void)
{
/* VCI=2.8V*/ 
/************** Reset LCD Driver ****************//*/ 
LCD_nRESET = 1;
delayms(1); /* Delay 1ms*/ 
LCD_nRESET = 0;
delayms(10); /* Delay 10ms // This delay time is necessary*/ 
LCD_nRESET = 1;
delayms(120); /* Delay 120 ms*/ 
/************** Start Initial Sequence **********//*/ 
    (0xCF),0x00,0x81,0x30,
    (0xED),0x64,0x03,0x12,0x81,
    (0xE8),0x85,0x10,0x78,
    (0xCB),0x39,0x2C,0x00,0x34,0x02,
    (0xF7),0x20,
    (0xEA),0x00,0x00,
    (0xB1),0x00,0x1B,
    (0xB6), /* Display Function Control*/ 0x0A,0xA2,
    (0xC0), /*Power control*/ 0x21, /*VRH[5:0]*/ 
    (0xC1), /*Power control*/ 0x11, /*SAP[2:0];BT[3:0]*/ 
    (0xC5), /*VCM control*/ 0x3F,0x3C,
    (0xC7), /*VCM control2*/ 0xb5,
    (0x36), /* Memory Access Control*/ 0x48,
    (0xF2), /* 3Gamma Function Disable*/ 0x00,
    (0x26), /*Gamma curve selected*/ 0x01,
    (0xE0), /*Set Gamma*/ 0x0F,0x26,0x24,0x0B,0x0E,0x09,0x54,0xA8,0x46,0x0C,0x17,0x09,0x0F,0x07,0x00,
    (0xE1), /*Set Gamma*/ 0x00,0x19,0x1B,0x04,0x10,0x07,0x2A,0x47,0x39,0x03,0x06,0x06,0x30,0x38,0x0F,
    (0x11), /*Exit Sleep*/ 
    TFTLCD_DELAY8, 120, 
    (0x29), /*Display on*/ 
}

/* 3.2 Tianma 2.4� Initial Code*/ 
void ILI9341_Tianma2.4_Initial(void)
{
/* VCI=2.8V*/ 
/************** Reset LCD Driver ****************//*/ 
LCD_nRESET = 1;
delayms(1); /* Delay 1ms*/ 
LCD_nRESET = 0;
delayms(10); /* Delay 10ms // This delay time is necessary*/ 
LCD_nRESET = 1;
delayms(120); /* Delay 120 ms*/ 
/************** Start Initial Sequence **********//*/ 
    (0xCF),0x00,0x81,0x30,
    (0xED),0x64,0x03,0x12,0x81,
    (0xE8),0x85,0x10,0x7A,
    (0xCB),0x39,0x2C,0x00,0x34,0x02,
    (0xF7),0x20,
    (0xEA),0x00,0x00,
    (0xC0), /*Power control*/ 0x21, /*VRH[5:0]*/ 
    (0xC1), /*Power control*/ 0x11, /*SAP[2:0];BT[3:0]*/ 
    (0xC5), /*VCM control*/ 0x3F,0x3C,
    (0xC7), /*VCM control2*/ 0xa7,
    (0x36), /* Memory Access Control*/ 0x48,
    (0xB1),0x00,0x1B,
    (0xB6), /* Display Function Control*/ 0x0A,0xA2,
    (0xF2), /* 3Gamma Function Disable*/ 0x00,
    (0x26), /*Gamma curve selected*/ 0x01,
    (0xE0), /*Set Gamma*/ 0x0F,0x23,0x1F,0x0B,0x0E,0x08,0x4B,0xA8,0x3B,0x0A,0x14,0x06,0x10,0x09,0x00,
    (0xE1), /*Set Gamma*/ 0x00,0x1C,0x20,0x04,0x10,0x08,0x34,0x47,0x44,0x05,0x0B,0x09,0x2F,0x36,0x0F,
    (0x11), /*Exit Sleep*/ 
    TFTLCD_DELAY8, 120, 
    (0x29), /*Display on*/ 
}


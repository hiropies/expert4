/*********************************************************
 Title:		Source file for absoulte encoder
 Copyright:	1999-2017  Myway Plus Co.,Ltd.

 Abstract:

 Model:	Expert4(c6657)
*********************************************************/
#include "enc.h"


/***********************************************
 * Defining register address for communication *
 ***********************************************/
#define ENC_ENCODER_ENABLE_CH0            0X10
#define ENC_ENCODER_ENABLE_CH1            0X20
#define ENC_ENCODER_ENABLE_CH2            0X30

#define ENC_ENCODER_REFRESH_CH0           0X12
#define ENC_ENCODER_REFRESH_CH1           0X22
#define ENC_ENCODER_REFRESH_CH2           0X32

#define ENC_ENCODER_POSITION_CH0          0X40
#define ENC_ENCODER_POSITION_CH1          0X50
#define ENC_ENCODER_POSITION_CH2          0X60

#define ENC_ENCODER_ROTATION_CH0          0X41
#define ENC_ENCODER_ROTATION_CH1          0X51
#define ENC_ENCODER_ROTATION_CH2          0X61

#define ENC_ENCODER_STATUS_CH0            0X4E
#define ENC_ENCODER_STATUS_CH1            0X5E
#define ENC_ENCODER_STATUS_CH2            0X6E

#define ENC_ENCODER_ERROR_CH0             0X4F
#define ENC_ENCODER_ERROR_CH1             0X5F
#define ENC_ENCODER_ERROR_CH2             0X6F

#define ENC_ENCODER_RESET_CH0             0X1F
#define ENC_ENCODER_RESET_CH1             0X2F
#define ENC_ENCODER_RESET_CH2             0X3F

#define ENC_ENCODER_RESET_CRC_CH0         0X1E
#define ENC_ENCODER_RESET_CRC_CH1         0X2E
#define ENC_ENCODER_RESET_CRC_CH2         0X3E

#define ENC_ENCODER_ALARM_SETTING_CH0     0x13
#define ENC_ENCODER_ALARM_SETTING_CH1     0x23
#define ENC_ENCODER_ALARM_SETTING_CH2     0x33

#define ENC_ENCODER_SS_GETSTART_CH0       0X15
#define ENC_ENCODER_SS_GETSTART_CH1       0X25
#define ENC_ENCODER_SS_GETSTART_CH2       0X35

#define ENC_ENCODER_SS_POSITION_CH0       0X45
#define ENC_ENCODER_SS_POSITION_CH1       0X55
#define ENC_ENCODER_SS_POSITION_CH2       0X65

#define ENC_ENCODER_SS_ROTATION_CH0       0X46
#define ENC_ENCODER_SS_ROTATION_CH1       0X56
#define ENC_ENCODER_SS_ROTATION_CH2       0X66

/**********************************
 * end of the register definition *
 **********************************/


#define ENC_START                         0x00U
#define ENC_STOP                          0x01U
#define BATTERY_ALARM_ENABLE              0x01U

INT32 ENC_start_abs(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;

  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH0, ENC_START);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH1, ENC_START);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH2, ENC_START);
    }
  }
  return return_code_s32;
}

INT32 ENC_stop_abs(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;

  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH0, ENC_STOP);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH1, ENC_STOP);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH2, ENC_STOP);
    }
  }
  return return_code_s32;
}

INT32 ENC_set_refresh(INT32 bdn, INT32 ch, UINT32 period){
  INT32 return_code_s32 = 0;
  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_REFRESH_CH0, period);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_REFRESH_CH1, period);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_REFRESH_CH2, period);
    }
  }
  return return_code_s32;
}

INT32 ENC_get_abs(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;
  UINT32 data_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  UINT32 error_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  UINT32 position_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  if(bdn < 0 || bdn > 5){
    return_code_s32 = 0xEFFFFFFF;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = 0xEFFFFFFF;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_POSITION_CH0);
    }
    else if(ch == 1){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_POSITION_CH1);
    }
    else{
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_POSITION_CH2);
    }
    error_u32 = (data_u32 &  0x0F0000000U) >> 28U;
    position_u32 = data_u32 & 0x0001FFFFU;
    if(error_u32 == 0x00U){
      return_code_s32 = (INT32)position_u32;
    }
    else{
      return_code_s32 = -(INT32)position_u32;
    }
  }
  return return_code_s32;
}

INT32 ENC_get_abm(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;
  UINT32 data_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  UINT32 error_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  UINT32 position_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  if(bdn < 0 || bdn > 5){
    return_code_s32 = 0xEFFFFFFF;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = 0xEFFFFFFF;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_ROTATION_CH0);
    }
    else if(ch == 1){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_ROTATION_CH1);
    }
    else{
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_ROTATION_CH2);
    }
    error_u32 = (data_u32 &  0x0F0000000U) >> 28;
    position_u32 = data_u32 & 0x0000FFFFU;
    if(error_u32 == 0x00U){
      return_code_s32 = (INT32)position_u32;
    }
    else{
      return_code_s32 = -(INT32)position_u32;
    }
  }
  return return_code_s32;
}
INT32 ENC_batt_alm_en(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;
  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_ALARM_SETTING_CH0, BATTERY_ALARM_ENABLE);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_ALARM_SETTING_CH1, BATTERY_ALARM_ENABLE);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_ALARM_SETTING_CH2, BATTERY_ALARM_ENABLE);
    }
  }
  return return_code_s32;
}

INT32 ENC_get_status(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;
  UINT32 data_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_STATUS_CH0);
    }
    else if(ch == 1){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_STATUS_CH1);
    }
    else{
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_STATUS_CH2);
    }
    return_code_s32 = (INT32)(data_u32 &  0x0000000FU);

  }
  return return_code_s32;
}

INT32 ENC_get_almc(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;
  UINT32 data_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_ERROR_CH0);
    }
    else if(ch == 1){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_ERROR_CH1);
    }
    else{
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_ERROR_CH2);
    }
    return_code_s32 = (INT32)(data_u32 &  0x000000FFU);
  }
  return return_code_s32;
}

INT32 ENC_reset_abs(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;

  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH0, 0x01U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH0, 0x01U);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH1, 0x01U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH1, 0x01U);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH2, 0x01U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH2, 0x01U);
    }
  }
  return return_code_s32;
}

INT32 ENC_reset_abm(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;

  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH0, 0x02U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH0, 0x01U);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH1, 0x02U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH1, 0x01U);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH2, 0x02U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH2, 0x01U);
    }
  }
  return return_code_s32;
}

INT32 ENC_reset_err(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;

  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH0, 0x04U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH0, 0x01U);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH1, 0x04U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH1, 0x01U);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CH2, 0x04U);
      IPFPGA_write(bdn, ENC_ENCODER_RESET_CRC_CH2, 0x01U);
    }
  }
  return return_code_s32;
}

//Single Shot Initialize
INT32 ENC_ss_init(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;

  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH0, ENC_STOP);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH1, ENC_STOP);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_ENABLE_CH2, ENC_STOP);
    }
  }
  return return_code_s32;
}

//Single Shot Get Start
INT32 ENC_ss_get_start(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;

  if(bdn < 0 || bdn > 5){
    return_code_s32 = -1;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = -1;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      IPFPGA_write(bdn, ENC_ENCODER_SS_GETSTART_CH0, 0x01U);
    }
    else if(ch == 1){
      IPFPGA_write(bdn, ENC_ENCODER_SS_GETSTART_CH1, 0x01U);
    }
    else{
      IPFPGA_write(bdn, ENC_ENCODER_SS_GETSTART_CH2, 0x01U);
    }
  }
  return return_code_s32;
}

//Single Shot Get Abs
INT32 ENC_ss_get_abs(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;
  UINT32 data_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  UINT32 error_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  UINT32 position_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  if(bdn < 0 || bdn > 5){
    return_code_s32 = 0xEFFFFFFF;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = 0xEFFFFFFF;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_SS_POSITION_CH0);
    }
    else if(ch == 1){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_SS_POSITION_CH1);
    }
    else{
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_SS_POSITION_CH2);
    }
    if((data_u32 & 0x08000000U) == 0){
      return_code_s32 = 0xDFFFFFFF;
    }
    else{
        error_u32 = (data_u32 & 0x0F0000000U) >> 28U;
        position_u32 = data_u32 & 0x0001FFFFU;
        if(error_u32 == 0x00U){
          return_code_s32 = (INT32)position_u32;
        }
        else{
          return_code_s32 = -(INT32)position_u32;
        }
      }
    }
  return return_code_s32;
}

//Single Shot Get Abm
INT32 ENC_ss_get_abm(INT32 bdn, INT32 ch){
  INT32 return_code_s32 = 0;
  UINT32 data_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  UINT32 error_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  UINT32 position_u32 = 0U;/* parasoft-suppress OPT-01 "for temporal data " */
  if(bdn < 0 || bdn > 5){
    return_code_s32 = 0xEFFFFFFF;
  }
  if(ch < 0 || ch > 2){
    return_code_s32 = 0xEFFFFFFF;
  }
  if(return_code_s32 == 0){
    if(ch == 0){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_SS_ROTATION_CH0);
    }
    else if(ch == 1){
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_SS_ROTATION_CH1);
    }
    else{
      data_u32 = (UINT32)IPFPGA_read(bdn, ENC_ENCODER_SS_ROTATION_CH2);
    }
    if((data_u32 & 0x08000000U) == 0){
      return_code_s32 = 0xDFFFFFFF;
    }
    else{
        error_u32 = (data_u32 &  0x0F0000000U) >> 28;
        position_u32 = data_u32 & 0x0000FFFFU;
        if(error_u32 == 0x00U){
            return_code_s32 = (INT32)position_u32;
        }
        else{
            return_code_s32 = -(INT32)position_u32;
        }
    }
  }
  return return_code_s32;
}


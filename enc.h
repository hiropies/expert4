/*********************************************************
 Title:		header file for absoulte encoder
 Copyright:	1999-2017  Myway Plus Co.,Ltd.

 Abstract:

 Model:	Expert4(c6657)
*********************************************************/

#include "mwio4.h"
#include "type.h"





/************************************************************************************
 * Start the encoder. If there is a parameter error, return -1. Otherwise, return 0 *
 * @method ENC_start_abs                                                            *
 * @param  bdn           board number                                               *
 * @param  ch            channel number                                             *
 * @return               error value                                                *
 ************************************************************************************/
INT32 ENC_start_abs(INT32 bdn, INT32 ch);

/************************************************************************************
 * Stop the encoder. If there is a parameter error, return -1. Otherwise, return 0. *
 * @method ENC_stop_abs                                                             *
 * @param  bdn          board number                                                *
 * @param  ch           channel number                                              *
 * @return              error value                                                 *
 ************************************************************************************/
INT32 ENC_stop_abs(INT32 bdn, INT32 ch);

/****************************************************************************************************
 * Set reflesh period. Unit is 25ns. If there is a parameter error, return -1. Otherwise, return 0. *
 * @method ENC_set_reflesh                                                                          *
 * @param  bdn             board number                                                             *
 * @param  ch              channel number                                                           *
 * @param  period          period of reflesh timing                                                 *
 * @return                 error value                                                              *
 ****************************************************************************************************/
INT32 ENC_set_refresh(INT32 bdn, INT32 ch, UINT32 period);

/********************************************************************************
 * return the position of the encoder. If there is a error, minus sign is added *
 * @method ENC_get_abs                                                          *
 * @param  bdn         board number                                             *
 * @param  ch          channel number                                           *
 * @return             position of the encoder                                  *
 ********************************************************************************/
INT32 ENC_get_abs(INT32 bdn, INT32 ch);

/********************************************************************************************
 * return the rotation counter of the encoder. If there is a error, minus sign is added *
 * @method ENC_get_abm                                                                      *
 * @param  bdn         board number                                                         *
 * @param  ch          channel number                                                       *
 * @return             rotation information of the encoder                                  *
 ********************************************************************************************/
INT32 ENC_get_abm(INT32 bdn, INT32 ch);

/*********************************************************************************************
 * disable the battery alarm. If there is a parameter error, return -1. Otherwise, return 0. *
 * @method ENC_batt_alm                                                                      *
 * @param  bdn          board number                                                         *
 * @param  ch           channel number                                                       *
 * @return              error value                                                          *
 *********************************************************************************************/
INT32 ENC_batt_alm_en(INT32 bdn, INT32 ch);

/****************************************************************************************
 * return status of the encoder as 4 bit data. If there is a parameter error, return -1 *
 * @method ENC_get_status                                                               *
 * @param  bdn            board number                                                  *
 * @param  ch             channel number                                                *
 * @return                satus of the encoder                                          *
 ****************************************************************************************/
INT32 ENC_get_status(INT32 bdn, INT32 ch);

/***************************************************************************************
 * return status of the encoder as 8bit data. If there is a parameter error, return -1 *
 * @method ENC_get_almc                                                                *
 * @param  bdn          board number                                                   *
 * @param  ch           channel number                                                 *
 * @return              status of the encoder                                          *
 ***************************************************************************************/
INT32 ENC_get_almc(INT32 bdn, INT32 ch);

/*********************************************************************************************
 * Reset the encoder position. If there is a parameter error, return -1. Ohterwise return 0. *
 * @method ENC_reset_abs                                                                     *
 * @param  bdn           board number                                                        *
 * @param  ch            channel number                                                      *
 * @return               error value                                                         *
 *********************************************************************************************/
INT32 ENC_reset_abs(INT32 bdn, INT32 ch);

/*********************************************************************************************************
 * Reset the encoder rotation information. If there is a parameter error, return -1. Ohterwise return 0. *
 * @method ENC_reset_abm                                                                                 *
 * @param  bdn           board number                                                                    *
 * @param  ch            channel number                                                                  *
 * @return               error value                                                                     *
 *********************************************************************************************************/
INT32 ENC_reset_abm(INT32 bdn, INT32 ch);

/**********************************************************************************************************
 * Reset the hardware error of the encoder. If there is a parameter error, return -1. Ohterwise return 0. *
 * @method ENC_reset_err                                                                                  *
 * @param  bdn           board number                                                                     *
 * @param  ch            channel number                                                                   *
 * @return               error value                                                                      *
 **********************************************************************************************************/
INT32 ENC_reset_err(INT32 bdn, INT32 ch);



/******************************************************************************************************
 * Single Shot Mode. Stop the encoder. If there is a parameter error, return -1. Otherwise, return 0. *
 * @method ENC_stop_abs                                                                               *
 * @param  bdn          board number                                                                  *
 * @param  ch           channel number                                                                *
 * @return              error value                                                                   *
 ******************************************************************************************************/
INT32 ENC_ss_init(INT32 bdn, INT32 ch);

/******************************************************************************************************
 * Single Shot Mode. Run the encoder. If there is a parameter error, return -1. Otherwise, return 0.  *
 * @method ENC_stop_abs                                                                               *
 * @param  bdn          board number                                                                  *
 * @param  ch           channel number                                                                *
 * @return              error value                                                                   *
 ******************************************************************************************************/
INT32 ENC_ss_get_start(INT32 bdn, INT32 ch);

/***************************************************************************************************
 *  Single Shot Mode. return the position of the encoder. If there is a error, minus sign is added *
 * @method ENC_get_abs                                                                             *
 * @param  bdn         board number                                                                *
 * @param  ch          channel number                                                              *
 * @return             position of the encoder or state or error                                   *
 ***************************************************************************************************/
INT32 ENC_ss_get_abs(INT32 bdn, INT32 ch);

/***********************************************************************************************************
 *  Single Shot Mode. return the rotation counter of the encoder. If there is a error, minus sign is added *
 * @method ENC_get_abm                                                                                     *
 * @param  bdn         board number                                                                        *
 * @param  ch          channel number                                                                      *
 * @return             rotation information of the encoder or state or error                               *
 ***********************************************************************************************************/
INT32 ENC_ss_get_abm(INT32 bdn, INT32 ch);

extern INT32 IPFPGA_read(INT32 bdn, INT32 port);
extern INT32 IPFPGA_write(INT32 bdn, INT32 port, UINT32 data);


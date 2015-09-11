/**********************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2011 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************************//*!
*
* @file      pwm_hal.c
*
* @author    b35554
* 
* @version   1.0
* 
* @date      March-30-2011
* 
* @brief     PWM HAL File
*
***********************************************************************************************
*
* Detailed Description of the file.
*
* This file includes fuctions made for controling the entire PWM module PWM8B8CV2
* Init() ititializes both channels on left aligned moide,polarity 1, clock  surce A for channel 0 
* and B for chanel 1, both configured with a period of 255* 128/Busclock, and a duty of 10%. both 
* channel's outputs remain disable.
*  
* Important considerations: When using center aligned mode, the "period" parameter is half of the 
* output period. 
*
*
**********************************************************************************************/

#include "pwm.h"

void PWM_init(void){
  PWMCAE = 0x00; /* Set center alignment for channels 0 - 1 */
  
  
  PWMPER2 = 0xFF; /* Set chan 2 period length to the maximum. */
  PWMPER3 = 0xFF; /* Set chan 3 period length to the maximum. */
  PWMPER4 = 0xFF; /* Set chan 4 period length to the maximum. */

  PWMDTY2 = 0x80; /* Set chan 2 duty cycle to half the maximum, 50%. */
  PWMDTY3 = 0x80; /* Set chan 3 duty cycle to half the maximum, 50%. */
  PWMDTY4 = 0x80; /* Set chan 4 duty cycle to half the maximum, 50%. */

  PWME = 0x1C;    /* Enable PWM channels 2, 3 and 4 */
}
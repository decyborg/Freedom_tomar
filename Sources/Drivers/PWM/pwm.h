/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2011 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file      pwm_hil.h
*
* @author    b35554 
*
* @version   1.0
*
* @date      March-30-2011
*
* @brief     PWM HAL Header File
*
************************************************************************************* 
*
*
*
*
*
*************************************************************************************/

#ifndef _PWM_HAL_H
#define _PWM_HAL_H

/*******************************************************************************
* Includes
********************************************************************************/

#include "datatypes.h"
#include <mc9s12vr64.h>

/*******************************************************************************
* Contants
********************************************************************************/
      
#define PWM_NO_ERROR                 0x00
#define PWM_DUTY_ERROR               0x01  
#define PWM_CHANNEL_ERROR            0x02   
#define PWM_PRESCALE_ERROR           0x03  

#define PWM_HIGH_POLARITY            1
#define PWM_LOW_POLARITY             0   

#define PWM_CENTER_ALIGNED           1
#define PWM_LEFT_ALIGNED             0                             


/*******************************************************************************
* Macros
********************************************************************************/


#define setclock(channel,clock)   PWMCLK_PCLK##channel = clock;      \
                                  PWMCLKAB_PCLKAB##channel = (clock>>1) 
                                  
/*******************************************************************************
* Types
********************************************************************************/

typedef enum{
   PWM_CHANNEL0,
   PWM_CHANNEL1,
   PWM_CHANNEL01,
   MAX_PWM_CHANNELS
}pwm_channels_t;

typedef enum{
   PWM_CLOCK_A,
   PWM_CLOCK_SA,
   PWM_CLOCK_B,
   PWM_CLOCK_SB,
   MAX_PWM_CLOCK
}pwm_clk_t;

typedef enum{
   PWM_PRESCALE_BUS_CLK,
   PWM_PRESCALE_BUS_CLK_2,
   PWM_PRESCALE_BUS_CLK_4,
   PWM_PRESCALE_BUS_CLK_8,
   PWM_PRESCALE_BUS_CLK_16,
   PWM_PRESCALE_BUS_CLK_32,
   PWM_PRESCALE_BUS_CLK_64,
   PWM_PRESCALE_BUS_CLK_128,
   MAX_PWM_PRESCALE   
}pwm_prescale_t;

/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Global Functions
********************************************************************************/


/*******************************************************************************
*
* @brief    PWM_Init   Initializes the PWM Module
* @param    none
* @return   none
*
********************************************************************************/   

extern void PWM_Init(void);

/*******************************************************************************
*
* @brief    PWM_ChannelConfig       Config a especific PWM Channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    counter                 It is used by the PWM channel to generate period and duty
* @param    period                  Hexadecimal value required to generate the period
* @param    duty                    Hexadecimal value required to generate the duty cycle 
* @return   pwm_error               Status from the received parameters
*
********************************************************************************/ 

UINT8 PWM_ChannelConfig(pwm_channels_t channel,UINT8 mode,UINT8 polarity, UINT16 period, UINT8 duty);


/*******************************************************************************
*
* @brief    PWM_ChannelEnable       Starts to generate PWM signal on a especific channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @return   pwm_error               Status from the received parameters
********************************************************************************/  

extern UINT8 PWM_ChannelEnable(pwm_channels_t channel);

/*******************************************************************************
*
* @brief    PWM_ChannelDisable      Stops the PWM signal on a especific channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @return   pwm_error               Status from the received parameters
********************************************************************************/ 

extern UINT8 PWM_ChannelDisable(pwm_channels_t channel);

/*******************************************************************************
*
* @brief    PWM_ChannelSetClock     Changes the clock source of channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    clock                   clock source selection for channel
* @return   pwm_error               Status from the received parameters
********************************************************************************/ 

extern UINT8 PWM_ChannelSetClock(pwm_channels_t channel, pwm_clk_t clock);

/*******************************************************************************
*
* @brief    PWM_ChannelSetCounter   Changes the counter value of channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    counter                 It is used by the PWM channel to generate period and duty
* @return   pwm_error               Status from the received parameters
********************************************************************************/  


extern UINT8 PWM_ChannelSetPeriod(pwm_channels_t channel, UINT16 period);


/*******************************************************************************
*
* @brief    PWM_ChannelSetDuty      Changes the duty cycle of channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    duty                    Hexadecimal value required to generate the duty cycle
* @return   pwm_error               Status from the received parameters
********************************************************************************/

extern UINT8 PWM_ChannelSetDuty(pwm_channels_t channel, UINT8 duty);
/*
UINT8 PWM_ChannelSetDutyF(pwm_channels_t channel, double duty);
*/

/*******************************************************************************
*
* @brief    PWM_SetPreScale_CLKA    Changes the  pre-scale for clk A
* @param    prescale                Divider from 1 to 128 on bus clock 
* @return   pwm_error               Status from the received parameters
*
********************************************************************************/

extern UINT8 PWM_SetPreScale_CLKA(pwm_prescale_t prescale);


/*******************************************************************************
*
* @brief    PWM_SetPreScale_CLKB    Changes the  pre-scale for clk B
* @param    prescale                Divider from 1 to 128 on bus clock 
* @return   pwm_error               Status from the received parameters
*
********************************************************************************/

extern UINT8 PWM_SetPreScale_CLKB(pwm_prescale_t prescale);

/*******************************************************************************
*
* @brief    PWM_SetPreScale_CLKSA   Changes the  pre-scale for clk SA
* @param    prescale                Divider from 1 to 512 on CLK A 
*
********************************************************************************/

extern void PWM_SetPreScale_CLKSA(UINT8 prescale);


/*******************************************************************************
*
* @brief    PWM_SetPreScale_CLKSB   Changes the  pre-scale for clk SB
* @param    prescale                Divider from 1 to 512 on CLK B 
*
********************************************************************************/

extern void PWM_SetPreScale_CLKSB(UINT8 prescale);


/*******************************************************************************
*
* @brief    PWM_SetPolarity         Changes polarity of a channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    polarity                high or low  
* @return   pwm_error               Status from the received parameters
*
********************************************************************************/

extern UINT8 PWM_SetPolarity(pwm_channels_t channel, UINT8 polarity);


/******************************************************************************
*
* @brief    PWM_SetMode             Changes mode of a channel 
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    mode                    Center of left aliged  
* @return   pwm_error               Status from the received parameters
*
********************************************************************************/

extern UINT8 PWM_SetMode(pwm_channels_t channel, UINT8 mode);
 

#endif  /*_PWM_HIL_H*/
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

/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/



/**********************************************************************************************
* Constants and macros
**********************************************************************************************/



/**********************************************************************************************
* Local types
**********************************************************************************************/



/**********************************************************************************************
* Local function prototypes
**********************************************************************************************/



/**********************************************************************************************
* Local variables
**********************************************************************************************/



/**********************************************************************************************
* Local functions
**********************************************************************************************/



/**********************************************************************************************
* Global functions
**********************************************************************************************/

/***********************************************************************************************
*
* @brief    PWM_Clock_Init   Initializes the PWM Module
* @param    none
* @return   none
*
************************************************************************************************/  

void PWM_Init(void)
{


   PWMCTL_PSWAI = 1;     /* Wait mode: stop counter   */
   PWMCTL_PFRZ = 1;      /* Freeze mode: stop counter */
                         /* Polarity = 1  ________               ________               */
                         /* Left Aliged           |_____________|        |_____________ */
                         /*               < Duty >                                      */
                         /*               <        Period      >                        */
   
   
   PWM_SetPreScale_CLKSA(1);                              /* Clock SA = CLockA/2 */
   PWM_SetPreScale_CLKSB(1);                              /* Clock SB = CLockB/2 */
   (void)PWM_SetPreScale_CLKA(PWM_PRESCALE_BUS_CLK_128);
   (void)PWM_SetPreScale_CLKB(PWM_PRESCALE_BUS_CLK_128);
   (void) PWM_ChannelSetClock(PWM_CHANNEL0, PWM_CLOCK_A);
   (void) PWM_ChannelSetClock(PWM_CHANNEL1, PWM_CLOCK_B);
   (void) PWM_ChannelConfig(PWM_CHANNEL0,PWM_LEFT_ALIGNED,PWM_HIGH_POLARITY,0xFF,10);
   (void) PWM_ChannelConfig(PWM_CHANNEL1,PWM_LEFT_ALIGNED,PWM_HIGH_POLARITY,0xFF,10);
}


/***********************************************************************************************
*
* @brief    PWM_ChannelConfig       Initialize a especific PWM Channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    mode                    Center of left aliged  
* @param    polarity                high or low  
* @param    period                  Hexadecimal value required to generate the period
* @param    duty                    Hexadecimal value required to generate the duty cycle 
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/ 


UINT8 PWM_ChannelConfig(pwm_channels_t channel,UINT8 mode,UINT8 polarity, UINT16 period, UINT8 duty)
{
   UINT8 pwm_error;
   
   if(MAX_PWM_CHANNELS > channel) 
   { 
      (void)PWM_ChannelDisable(PWM_CHANNEL0);  /* Channels must be disable for concatenation configuration  */
      (void)PWM_ChannelDisable(PWM_CHANNEL1);
   
      if(PWM_CHANNEL01 == channel)
      {
         PWMCTL_CON01 = 1;  
      } 
      else 
      {
         PWMCTL_CON01 = 0;
      }
     
      (void)PWM_SetMode(channel,mode);
      (void)PWM_SetPolarity(channel, polarity);
      (void)PWM_ChannelSetPeriod(channel,period);
      pwm_error = PWM_ChannelSetDuty(channel,duty);
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }
   return pwm_error;
} 

/***********************************************************************************************
*
* @brief    PWM_ChannelEnable       Starts to generate PWM signal on a especific channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/ 

UINT8 PWM_ChannelEnable(pwm_channels_t channel)
{
   UINT8 pwm_error = PWM_NO_ERROR;
   
   if(MAX_PWM_CHANNELS > channel) 
   {
      if(PWM_CHANNEL0 == channel) 
      {
         PWME_PWME0 = 1;
      } 
      else if(PWM_CHANNEL1 == channel) 
      { 
         PWME_PWME1 = 1;    
      } 
      else if(PWM_CHANNEL01 == channel)
      {
         PWME_PWME1 = 1;  
      }
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }
   
   return pwm_error;
}


/***********************************************************************************************
*
* @brief    PWM_ChannelDisable      Stops the PWM signal on a especific channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/ 

UINT8 PWM_ChannelDisable(pwm_channels_t channel)
{
   UINT8 pwm_error = PWM_NO_ERROR;
   
   if(MAX_PWM_CHANNELS > channel) 
   {
      if(PWM_CHANNEL0 == channel) 
      {
         PWME_PWME0 = 0;
      } 
      else if(PWM_CHANNEL1 == channel) 
      { 
         PWME_PWME1 = 0;    
      } 
      else if(PWM_CHANNEL01 == channel)
      {
         PWME_PWME1 = 0;  
      }
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }
   
   return pwm_error;
}



/***********************************************************************************************
*
* @brief    PWM_ChannelSetClock     Changes the clock source of channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    clock                   Clock source selection for channel
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/ 

UINT8 PWM_ChannelSetClock(pwm_channels_t channel, pwm_clk_t clock)
{
   UINT8 pwm_error = PWM_NO_ERROR;
   
   if(MAX_PWM_CHANNELS > channel) 
   {
      if(PWM_CHANNEL0 == channel)
      {
         setclock(0,(UINT8)clock);
      } 
      else if(PWM_CHANNEL1 == channel) 
      {
         setclock(1,(UINT8)clock);  
      }
      else if(PWM_CHANNEL01 == channel) 
      {
         setclock(1,(UINT8)clock);  
      }
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }
   
   return pwm_error;
}


/***********************************************************************************************
*
* @brief    PWM_ChannelSetPeriod    Changes the period parameter of channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    period                  Hexadecimal value required to generate the 
*                                   Period in cock cycles 
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/ 

UINT8 PWM_ChannelSetPeriod(pwm_channels_t channel, UINT16 period)
{
   UINT8 pwm_error = PWM_NO_ERROR;
   
   if(MAX_PWM_CHANNELS > channel) 
   {   
      if(PWM_CHANNEL0 == channel)
      {
         PWMPER0 = (UINT8)period;
      } 
      else if(PWM_CHANNEL1 == channel) 
      {
         PWMPER1 = (UINT8)period;
      }
      else if(PWM_CHANNEL01 == channel) 
      {
         PWMPER01 = period;
      }
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }
   
   return pwm_error;  
}


/***********************************************************************************************
*
* @brief    PWM_ChannelSetDuty      Changes the duty cycle of channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    duty                    Hexadecimal value required to generate the 
*                                   duty cycle in % 
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/ 

UINT8 PWM_ChannelSetDuty(pwm_channels_t channel, UINT8 duty)
{
   UINT8 pwm_error = PWM_NO_ERROR;
   UINT32 temp = 0x00000000;
   
   if(MAX_PWM_CHANNELS > channel) 
   { 
      if(duty <= 100)
      {
         if(PWM_CHANNEL0 == channel)
         {
            if(PWM_HIGH_POLARITY == PWMPOL_PPOL0)
            {
               PWMDTY0 = (UINT8)((PWMPER0*duty)/100);
            } 
            else
            {
               PWMDTY0 = (UINT8)(PWMPER0-((PWMPER0*duty)/100));
            }
         } 
         else if(PWM_CHANNEL1 == channel) 
         {
            if(PWM_HIGH_POLARITY == PWMPOL_PPOL1)
            {
               PWMDTY1 = (UINT8)((PWMPER1*duty)/100);
            } 
            else
            {
               PWMDTY1 = (UINT8)(PWMPER1-((PWMPER1*duty)/100));
            }   
         }               
         else if(PWM_CHANNEL01 == channel)
         {
            if(PWM_HIGH_POLARITY == PWMPOL_PPOL1)
            {
               temp =(UINT32)PWMPER01*(UINT32)duty;
               PWMDTY01 = (UINT16)(temp/100);
            } 
            else
            {
               temp =((UINT32)PWMPER01*(UINT32)duty)/100;
               PWMDTY01 = (UINT16)(PWMPER01-temp);         
            }
         }
      }
      else
      {
         pwm_error = PWM_DUTY_ERROR;
      }
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }   
 
   return pwm_error;   
}


/***********************************************************************************************
*
* @brief    PWM_ChannelSetDutyF     Changes the duty cycle of channel double precision
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    duty                    Hexadecimal value required to generate the 
*                                   duty cycle in % (example: 10.15%) 
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/ 
/*
UINT8 PWM_ChannelSetDutyF(pwm_channels_t channel, double duty)
{
   UINT8 pwm_error = PWM_NO_ERROR;
   double temp = 0x00000000;
   
   if(MAX_PWM_CHANNELS > channel) 
   { 
      if(duty <= 100)
      {
         if(PWM_CHANNEL0 == channel)
         {
            if(PWM_HIGH_POLARITY == PWMPOL_PPOL0)
            {
               PWMDTY0 = (UINT8)((PWMPER0*duty)/100);
            } 
            else
            {
               PWMDTY0 = (UINT8)(PWMPER0-((PWMPER0*duty)/100));
            }
         } 
         else if(PWM_CHANNEL1 == channel) 
         {
            if(PWM_HIGH_POLARITY == PWMPOL_PPOL1)
            {
               PWMDTY1 = (UINT8)((PWMPER1*duty)/100);
            } 
            else
            {
               PWMDTY1 = (UINT8)(PWMPER1-((PWMPER1*duty)/100));
            }   
         }               
         else if(PWM_CHANNEL01 == channel)
         {
            if(PWM_HIGH_POLARITY == PWMPOL_PPOL1)
            {
               temp =(double)PWMPER01*(double)duty;
               PWMDTY01 = (UINT16)(temp/100);
            } 
            else
            {
               temp =((double)PWMPER01*(double)duty)/100;
               PWMDTY01 = (UINT16)(PWMPER01-temp);         
            }
         }
      }
      else
      {
         pwm_error = PWM_DUTY_ERROR;
      }
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }   
 
   return pwm_error; 
}
*/

/***********************************************************************************************
*
* @brief    PWM_SetPreScale_CLKA    Changes the  pre-scale for clk A
* @param    prescale                Divider from 1 to 128 on bus clock 
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/

UINT8 PWM_SetPreScale_CLKA(pwm_prescale_t prescale)
{
   UINT8 pwm_error = PWM_NO_ERROR;
   
   if(MAX_PWM_PRESCALE > prescale) 
   {
      PWMPRCLK_PCKA = (UINT8)prescale;    /* Prescale A  */ 
   }
   else
   {
      pwm_error = PWM_PRESCALE_ERROR;
   }   
 
   return pwm_error;      
}


/***********************************************************************************************
*
* @brief    PWM_SetPreScale_CLKB    Changes the  pre-scale for clk B
* @param    prescale                Divider from 1 to 128 on bus clock 
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/

UINT8 PWM_SetPreScale_CLKB(pwm_prescale_t prescale) 
{
   UINT8 pwm_error = PWM_NO_ERROR;
   
   if(MAX_PWM_PRESCALE > prescale) 
   {
      PWMPRCLK_PCKB = (UINT8)prescale;    /* Prescale B  */ 
   }
   else
   {
      pwm_error = PWM_PRESCALE_ERROR;
   }   
 
   return pwm_error; 
}


/***********************************************************************************************
*
* @brief    PWM_SetPreScale_CLKSA   Changes the  pre-scale for clk SA
* @param    prescale                Divider from 1 to 512 on CLK A 
* @return   none
*
************************************************************************************************/

void PWM_SetPreScale_CLKSA(UINT8 prescale)
{
    PWMSCLA = prescale;    /* Prescale SA  */
}


/***********************************************************************************************
*
* @brief    PWM_SetPreScale_CLKSB   Changes the  pre-scale for clk SB
* @param    prescale                Divider from 1 to 512 on CLK B 
* @return   none
*
************************************************************************************************/

void PWM_SetPreScale_CLKSB(UINT8 prescale) 
{
   PWMSCLB = prescale;    /* Prescale SB  */  
}

 
/**********************************************************************************************
*
* @brief    PWM_SetPolarity         Changes polarity of a channel
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    polarity                high or low  
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/

UINT8 PWM_SetPolarity(pwm_channels_t channel, UINT8 polarity) 
{
   UINT8 pwm_error = PWM_NO_ERROR;
   
   if(MAX_PWM_CHANNELS > channel) 
   {   
      if(PWM_CHANNEL0 == channel)
      {
          PWMPOL_PPOL0 = polarity;
      } 
      else if(PWM_CHANNEL1 == channel) 
      {
         PWMPOL_PPOL1 = polarity;
      }
      else if(PWM_CHANNEL01 == channel) 
      {
         PWMPOL_PPOL1 = polarity;
      }
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }
   
   return pwm_error; 
}


/***********************************************************************************************
*
* @brief    PWM_SetMode             Changes mode of a channel 
* @param    channel                 PWM0, PWM1, PWM01(concatenate)
* @param    mode                    Center of left aliged  
* @return   pwm_error               Status from the received parameters
*
************************************************************************************************/

UINT8 PWM_SetMode(pwm_channels_t channel, UINT8 mode) 
{
   UINT8 pwm_error = PWM_NO_ERROR;
   
   if(MAX_PWM_CHANNELS > channel) 
   {   
      if(PWM_CHANNEL0 == channel)
      {
          PWMCAE_CAE0 = mode;
      } 
      else if(PWM_CHANNEL1 == channel) 
      {
         PWMCAE_CAE1 = mode;
      }
      else if(PWM_CHANNEL01 == channel) 
      {
         PWMCAE_CAE1 = mode;
      }
   }
   else
   {
      pwm_error = PWM_CHANNEL_ERROR;
   }
   
   return pwm_error; 
}

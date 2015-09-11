#include "hs.h"

/******************************************************************************
Function Name  : HS_Module_Init
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : HSx initialization routine:
                 Enables the HSx power supply
                 Enables HSx Open load detection
                 Enables the HSxOC interrupt detection 
******************************************************************************/
void HS_Module_Init(void)
{
   /* Enable HSx power supply */
   HSCR |= HSCR_HSE0_MASK;
   HSCR |= HSCR_HSE1_MASK;

   /* 
      Enable HSx Open Load detection 
   
      Note:
          This OL feature is only working when 
          the corresponding HSDRx is not driven
   */
   HSCR |= HSCR_HSOLE0_MASK;
   HSCR |= HSCR_HSOLE1_MASK;

   /* Enable HSx Over Current interrupt */
   HSIE |= HSIE_HSOCIE_MASK;
     
}

/******************************************************************************
Function Name  : HS0_Disable
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Turns off HS0 source to disable HS0 
******************************************************************************/
void HS0_Disable(void)
{
   /* Disable HS0 power supply */
   HSCR &= ~(uchar)HSCR_HSE0_MASK;    
}

/******************************************************************************
Function Name  : HS1_Disable
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Turns off HS1 source to disable HS1
******************************************************************************/
void HS1_Disable(void)
{
   /* Disable HS1 power supply */
   HSCR &= ~(uchar)HSCR_HSE1_MASK;     
}

/******************************************************************************
Function Name  : HS0_On
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets HS0 on 
******************************************************************************/
void HS0_On(void)
{
    HSDR |= HSDR_HSDR0_MASK;
}

/******************************************************************************
Function Name  : HS1_On
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets HS1 on. 
******************************************************************************/
void HS1_On(void)
{
    HSDR |= HSDR_HSDR1_MASK;
}

/******************************************************************************
Function Name  : HS0_Off
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets HS0 off
******************************************************************************/
void HS0_Off(void)
{
    HSDR &= ~(uchar)HSDR_HSDR0_MASK;
}


/******************************************************************************
Function Name  : HS1_Off
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets HS1 off 
******************************************************************************/
void HS1_Off(void)
{
    HSDR &= ~(uchar)HSDR_HSDR1_MASK;
}
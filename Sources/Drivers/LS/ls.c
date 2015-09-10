/*
 * ls.c
 *
 *  Created on: Jul 7, 2015
 *      Author: B52932
 */

#include "ls.h"
#include "derivative.h"

/******************************************************************************
Function Name  : LS_Module_Init
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : LSx initialization routine:
                 Enables the LSx power supply
                 Enables LSx Open load detection
                 Enables the LSxOC interrupt detection 
******************************************************************************/
void LS_Module_Init(void)
{
   /* Enable LSx power supply */
   LSCR |= LSCR_LSE0_MASK;
   LSCR |= LSCR_LSE1_MASK;   
}

/******************************************************************************
Function Name  : LS0_Disable
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Turns off LS0 source to disable LS0 
******************************************************************************/
void LS0_Disable(void)
{
   /* Disable LS0 power supply */
   LSCR &= ~(unsigned char)LSCR_LSE0_MASK;    
}

/******************************************************************************
Function Name  : LS1_Disable
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Turns off LS1 source to disable LS1
******************************************************************************/
void LS1_Disable(void)
{
   /* Disable LS1 power supply */
   LSCR &= ~(unsigned char)LSCR_LSE1_MASK;     
}

/******************************************************************************
Function Name  : LS0_On
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets LS0 on 
******************************************************************************/
void LS0_On(void)
{
    LSDR |= LSDR_LSDR0_MASK;
}

/******************************************************************************
Function Name  : LS1_On
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets LS1 on. 
******************************************************************************/
void LS1_On(void)
{
    LSDR |= LSDR_LSDR1_MASK;
}

/******************************************************************************
Function Name  : LS0_Off
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets LS0 off
******************************************************************************/
void LS0_Off(void)
{
    LSDR &= ~(unsigned char)LSDR_LSDR0_MASK;
}


/******************************************************************************
Function Name  : LS1_Off
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets LS1 off 
******************************************************************************/
void LS1_Off(void)
{
    LSDR &= ~(unsigned char)LSDR_LSDR1_MASK;
}
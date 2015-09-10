/*
 * ls.h
 *
 *  Created on: Jul 7, 2015
 *      Author: B52932
 */

#ifndef LS_H_
#define LS_H_

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
void LS_Module_Init(void);

/******************************************************************************
Function Name  : LS0_Disable
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Turns off LS0 source to disable LS0 
******************************************************************************/
void LS0_Disable(void);

/******************************************************************************
Function Name  : LS1_Disable
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Turns off LS1 source to disable LS1
******************************************************************************/
void LS1_Disable(void);

/******************************************************************************
Function Name  : LS0_On
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets LS0 on 
******************************************************************************/
void LS0_On(void);

/******************************************************************************
Function Name  : LS1_On
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets LS1 on. 
******************************************************************************/
void LS1_On(void);

/******************************************************************************
Function Name  : LS0_Off
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets LS0 off
******************************************************************************/
void LS0_Off(void);


/******************************************************************************
Function Name  : LS1_Off
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : Sets LS1 off 
******************************************************************************/
void LS1_Off(void);

#endif /* LS_H_ */

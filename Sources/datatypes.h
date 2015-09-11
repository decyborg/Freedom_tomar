/************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2011, Freescale, Inc.
* ALL RIGHTS RESERVED
*
* *******************************************************************************//*!
*
* @file      datatypes.h
*
* @author     
*
* @version   1.0
*
* @date      Feb-15-2011
*
* @brief     Standardized data types and definitions are contained in this file
*
*************************************************************************************/


#ifndef _DATATYPES_H
#define _DATATYPES_H

/*******************************************************************************
* Includes
********************************************************************************/


/*******************************************************************************
* Contants
********************************************************************************/


/*******************************************************************************
* Macros
********************************************************************************/

#define NULL           ((void *) 0)    /* NULL pointer */
                                       
#define TRUE            1              /* TRUE boolean definition */
#define FALSE           0              /* FALSE boolean definition */

#define DISABLED        0
#define ENABLED         1

/*******************************************************************************
* Types
********************************************************************************/



typedef unsigned char     UINT8;    /* unsigned 8 bit definition      */
typedef unsigned short    UINT16;   /* unsigned 16 bit definition     */
typedef unsigned long     UINT32;   /* unsigned 32 bit definition     */
typedef signed char       INT8;     /* signed 8 bit definition        */
typedef short             INT16;    /* signed 16 bit definition       */
typedef long int          INT32;    /* signed 32 bit definition       */
typedef void(*pt2Func)(void);       /* pointer to function definition */


/* Function Pointer Filetype */								
typedef  void ( *CallbackType )( void );


/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Global Functions
********************************************************************************/


#endif /*_DATA_TYPES_H*/
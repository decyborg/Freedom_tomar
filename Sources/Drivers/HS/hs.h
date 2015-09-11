#ifndef _HS_H
#define _HS_H
#include "derivative.h"

typedef unsigned char uchar;

/* Prototypes */
void HS_Module_Init(void);
void HS0_Disable(void);
void HS1_Disable(void);
void HS0_On(void);
void HS1_On(void);
void HS0_Off(void);
void HS1_Off(void);

#endif
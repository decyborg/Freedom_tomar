#ifndef _ADC_H
#define _ADC_H

#include "derivative.h"

/* Parameters */
#define ATD_CLK           6250000L

/* Prototypes */
void ADC_init(unsigned char BUS_CLK);
unsigned char ADC_read(char channel);
#endif
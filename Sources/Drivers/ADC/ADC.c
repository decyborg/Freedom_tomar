#include "ADC.h"


void ADC_init(unsigned long BUS_CLK){

	/* Select 8-bit resolution*/
	ATDCTL1_SRES = 0;
	/* Right justify data */
	ATDCTL3_DJM = 1; 
	/* One conversion per sequence */
	ATDCTL3_S1C = 1;
	ATDCTL3_S2C = 0;
	ATDCTL3_S4C = 0;
	ATDCTL3_S8C = 0;
	/* Select sample time 4 ATD clock cycles */
	ATDCTL4_SMP = 0; 
	/* ATD clock Prescaler */
	ATDCTL4_PRS = (unsigned char) ((BUS_CLK/(2*ATD_CLK)) - 1);
	
}

unsigned char ADC_read(char channel){

	/* Write channel in ATDCTL5 to start conversion */
	ATDCTL5_Cx = channel;
	/* Wait for conversion sequence to finish */
	while(!ATDSTAT0_SCF);
	/* Clear flag */
	ATDSTAT0_SCF = 1;
	/* Return converted value */
	return ATDDR0;
}
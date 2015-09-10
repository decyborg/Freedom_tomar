#include "gpio.h"
#include "derivative.h"

/* Initialize Pusb buttons as inputs */
void gpio_init(void){
	DDR1AD_DDR1AD0 = 0; /* Select AN0 as input */
	DDR1AD_DDR1AD1 = 0; /* Select AN1 as input */
	ATDDIEN_IEN0 = 1; 	/* Enable AN0 as input*/
	ATDDIEN_IEN1 = 1; 	/* Enable AN1 as input*/	
}
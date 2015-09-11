#include "gpio.h"
#include "derivative.h"

/* Initialize Pusb buttons as inputs */
void gpio_init(void){
	DIENL_DIENL0 = 1; 	/* Enable AN0 as input*/
	DIENL_DIENL1 = 1; 	/* Enable AN1 as input*/	
}
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "MagniV_API.h"

#define BUS_CLK	12000000

void main(void) {
	unsigned long delay;
  /* put your own code here */
    clock_init(BUS_CLK);
    sci_init(9600, BUS_CLK, SCI1);
    gpio_init();
    LS_Module_Init();
    /* HSO */
    /* PWM PP2, PP3, PP4*/
    /* Pot PAD0*/
    
    send_string("Test\n\r", SCI1);
    echo(SCI1);
    send_string("\n\rTest successful\n\r",SCI1);

	EnableInterrupts;
	LS0_On();
	LS0_Off();
	LS1_On();
	LS1_Off();


  for(;;) {
    _FEED_COP(); /* feeds the dog */
    for(delay = 0; delay < 30000; ++delay);
  } /* loop forever */
  /* please make sure that you never leave main */
}

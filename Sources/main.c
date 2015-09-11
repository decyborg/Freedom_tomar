#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "MagniV_API.h"
#include "gpio.h"
#include "ls.h"
#include "pwm.h"
#include "hs.h"

#define BUS_CLK	12000000

void main(void) {
	unsigned long delay;
  /* put your own code here */
    clock_init(BUS_CLK);
    sci_init(9600, BUS_CLK, SCI1);
    gpio_init();
    LS_Module_Init();
    HS_Module_Init();
    HS0_On();
    PWM_init();
    
    
    send_string("Test\n\r", SCI1);
    echo(SCI1);
    send_string("\n\rTest successful\n\r",SCI1);

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
    if(read_sw2){
    	LS0_On();	
    } else {
    	LS0_Off();
    }
    if(read_sw3){
    	LS1_On();	
    } else {
    	LS1_Off();
    }
    for(delay = 0; delay < 30000; ++delay);
  } /* loop forever */
  /* please make sure that you never leave main */
}

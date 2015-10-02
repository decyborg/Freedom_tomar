#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "MagniV_API.h"
#include "gpio.h"
#include "ls.h"
#include "pwm.h"
#include "hs.h"
#include "ADC.h"

#define BUS_CLK	12000000
#define POT	 0	/* Potentiometer is attached to channel 1 */
#define LIN_PHY_ENABLE   LPSLRM = 0x00; /* Select normal Slew rate optimized for 20kbits/s */\
				 		 LPIE_LPOCIE = 1; /* Enable over-current interrupt*/ \
				 		 LPCR_LPE = 1; /* Enable LIN Phy*/\
				 		 LPCR_LPPUE = 1; /* switch on 34KOhm pullup*/\
				 		 MODRR2_MODRR = 0; /* Route SCI0 to LINPHY */
				 		 

void DisplayInt(unsigned int number, unsigned int channel);

void main(void) {
	unsigned long delay;
	char exit = 'o';
	
  /* Initialization code */
    clock_init(BUS_CLK);
    sci_init(9600, BUS_CLK, SCI0);
    LIN_PHY_ENABLE;
    sci_init(9600, BUS_CLK, SCI1);
    gpio_init();
    LS_Module_Init();
    HS_Module_Init();
    HS0_On();
    PWM_init();
    ADC_init(BUS_CLK);
    
    /* Test serial communication */
    send_string("\n\rSerial Test, press any key\n\r", SCI1);
    echo(SCI1);
    send_string("\n\rTest successful\n\r",SCI1);

	/* Test Relay */
	send_string("\n\rPress u to activate the relay up and d to activate it down\n\r", SCI1);
	send_string("\n\rPres e to exit relay test\n\r", SCI1);
	
	while(exit != 'e'){
		exit = get_char(SCI1);
		put_char(exit, SCI1);
		if(exit == 'u'){
			send_string("\r\nRelay Low side driver 0 active\r\n", SCI1);
			LS0_On();
			for(delay = 0; delay < 30000; ++delay);
			send_string("\r\nRelay Low side driver 0 inactive\r\n", SCI1);
			LS0_Off();
			exit = 'a';	
		} else if (exit == 'd') {
			send_string("\r\nRelay Low side driver 1 active\r\n", SCI1);
			LS1_On();
			for(delay = 0; delay < 30000; ++delay);
			send_string("\r\nRelay Low side driver 1 inactive\r\n", SCI1);
			LS1_Off();
			exit = 'a';
		}		
	}
	
	put_char('\n', SCI1);
	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
    if(read_sw2){
    	LS0_On();
    	send_string("\r\nSwitch 2 pressed\r\n", SCI1);	
    } else {
    	LS0_Off();
    }
    if(read_sw3){
    	LS1_On();
    	send_string("\r\nSwitch 3 pressed\r\n", SCI1);	
    } else {
    	LS1_Off();
    }
    for(delay = 0; delay < 30000; ++delay);
    send_string("\rADC value:   ", SCI1);
    send_string("\b\b\b", SCI1);
    DisplayInt((unsigned char) ADC_read(POT), SCI1);
    put_char(0x55,SCI0);	/* Send stuff through LIN */
  } /* loop forever */
  /* please make sure that you never leave main */
}


/******************************************************************************
Function Name	:	DisplayInt
Engineer		:	r32151
Date			:	04/09/02

Parameters		:	int count value to display; unsigned char field width
Returns			:	NONE
Notes			:	Transmits Int variable to SCI after conversion to ASCII
            Effectively performs a number to string conversion and then outputs
            the string.
					  If field width = 0 then the int is displayed left justified with
					  leading zeros supressed.
					  If field width = 1-5 then lowest n digits are displayed with leading 
					  zeros.
					  This routine does not check that the field size is valid.					
******************************************************************************/
void DisplayInt(unsigned int number, unsigned int channel)
{
    char    buf[6];
    char    i = 5;
    buf[i] = 0;

    /* for upto 10 digits : max value for long = 4294967296 */

    /* using a do while loop to take care of the number = 0 */
    do
    {
        /* convert least significant character of the int into ascii -> string buffer */
        buf[--i] = (char) (number % 10) + '0';

        /* moves next digit to least significant position */
        number /= 10;
    } while (number != 0);

    send_string(&buf[i], channel );
}


/******************************************************************************
Function Name  : HS_OC_ISR
Engineer       : B30269
Date           : 07/06/11
Parameters     : None
Returns        : None
Notes          : interrupt routine executed by HSxOC detection 
******************************************************************************/
#pragma CODE_SEG NON_BANKED
__interrupt VectorNumber_Vhsdrv void HS_OC_ISR(void)
{
   if(HSIF_HSOCIF0)
   {
      HSIF_HSOCIF0 = 1;
      send_string("\r\nButton is working properly\r\n", SCI1);
      //HS0_Disable(); /* this will disable the HS0 until reset cycle */
   }
   else if(HSIF_HSOCIF1)
   {
      HSIF_HSOCIF1 = 1;
      HS1_Disable(); /* this will disable the HS1 until reset cycle */
   }
   else
   {
      HSIF_HSOCIF1 = 1;
      HSIF_HSOCIF0 = 1;
   }
}
#pragma CODE_SEG DEFAULT

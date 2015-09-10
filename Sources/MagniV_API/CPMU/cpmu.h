/** \addtogroup CPMU Clock, Reset and Power management unit  
 *  @{
 */
/**
 *  @file cpmu.h
 *
 * 	@brief Contains Clock and power management unit API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */

#ifndef CPMU_H_
#define CPMU_H_

/* Include derivative support */
#include "derivative.h"
#include "common.h"


/* Global definitions */
/** Internal Reference Clock */
#define IRC 				1000000	
#define EnableClockOutput	ECLKCTL_NECLK = 0;

/* Typedefs */
/** A structure that holds the divider values for the clock configuration. 
 * 	
 * */
typedef struct {
	unsigned char  syndiv;	/**< Multiplier to the Fvco, Fvco = 2*Fref*(syndiv+1)*/
	unsigned char  postdiv; /**< Divider for Fpll, Fpll = Fvco /(postdiv + 1) */
	unsigned char  refdiv;	/**< Divider for Fref (only used with an external oscillator), Fref = Fosc /(refdiv + 1) */
	unsigned char  reffrq;  /**< Reference clock range selection */
	unsigned char  vcofrq;	/**< VCO clock frequency range selection */
	unsigned long 	error;	/**< Current setup clock error*/
}clock_dividers;

/**
* @var uCPMUSYNR tCPMUSYNR
*/
/**
* @union uCPMUSYNR
* @brief CPMU Synthesizer Register
*/
typedef union uCPMUSYNR
{
  tU08   byte;				/**< access register as byte */
  struct
  {
    tU08 syndiv		:6;      /**< Multiplier to the Fvco, Fvco = 2*Fref*(syndiv+1)*/
    tU08 vcofrq     :2;      /**< VCO clock frequency range selection */
  }bit;						 /**< access register as bits */
}tCPMUSYNR;

/**
* @var uCPMUREFDIV tCPMUREFDIV
*/
/**
* @union uCPMUREFDIV
* @brief CPMU Reference Divider Register
*/
typedef union uCPMUREFDIV
{
  tU08   byte;				/**< access register as byte */
  struct
  {
    tU08 refdiv		:4;      /**< Divider for Fref (only used with an external oscillator), Fref = Fosc /(refdiv + 1) */
    tU08			:2;		 /**< bit reserved area */
    tU08 reffrq     :2;      /**< Reference clock range selection */
  }bit;						 /**< access register as bits */
}tCPMUREFDIV;

/**
* @var uCPMUPOSTDIV tCPMUPOSTDIV 
*/
/**
* @union uCPMUPOSTDIV 
* @brief CPMU Post Divider Register
*/
typedef union uCPMUPOSTDIV 
{
  tU08   byte;				/**< access register as byte */
  struct
  {
    tU08 postdiv	:5;		 /**< Divider for Fpll, Fpll = Fvco /(postdiv + 1) */
    tU08 		    :3;      /**< bit reserved area */
  }bit;						 /**< access register as bits */
}tCPMUPOSTDIV ;

/**
* @var uCPMUIFLG tCPMUIFLG 
*/
/**
* @union uCPMUIFLG 
* @brief CPMU Interrupt Flags Register
*/
typedef union uCPMUIFLG 
{
  tU08   byte;				/**< access register as byte */
  struct
  {
    tU08 uposc		:1;		 /**< Oscillator status bit */
    tU08 oscif		:1;		 /**< Oscillator interrupt flag */
    tU08 		    :1;		 /**< bit reserved area */
    tU08 lock		:1;		 /**< Lock status bit */
    tU08 lockif		:1;		 /**< PLL Lock interrupt flag */
    tU08 		    :2;		 /**< bit reserved area */
    tU08 rtif		:1;		 /**< Real Time Interrupt Flag */
  }bit;						 /**< access register as bits */
}tCPMUIFLG ;

/**
* @var uCPMUOSC tCPMUOSC 
*/
/**
* @union uCPMUOSC 
* @brief CPMU Oscillator register
*/
typedef union uCPMUOSC 
{
  tU08   byte;				/**< access register as byte */
  struct
  {
    tU08 	  		:7;		 /**< bit reserved area */
    tU08 osce		:1;		 /**< Oscillator Enable bit */
  }bit;						 /**< access register as bits */
}tCPMUOSC ;

/**
* @struct tCPMU
* CPMU datastructure
*/
typedef struct          	  /**< CPMU datastructure  */
  {
  volatile tCPMUSYNR  	syndiv;   		/**< CPMU Synthesizer Register */
  volatile tCPMUREFDIV  refdiv;   		/**< CPMU Reference Divider Register */
  volatile tCPMUPOSTDIV postdiv;   		/**< CPMU Post Divider Register */
  volatile tCPMUIFLG  	iflg;   		/**< CPMU Interrupt Flags Register */
  volatile tREG08   	unused_1;   	/**< unused data register */
  volatile tREG08   	unused_2;   	/**< unused data register */
  volatile tREG08   	unused_3;   	/**< unused data register */
  volatile tREG08   	unused_4;   	/**< unused data register */
  volatile tREG08   	unused_5;   	/**< unused data register */
  volatile tREG08   	unused_6;   	/**< unused data register */
  volatile tREG08   	unused_7;   	/**< unused data register */
  volatile tREG08   	unused_8;   	/**< unused data register */
  volatile tREG08   	unused_9;   	/**< unused data register */
  volatile tREG08   	unused_10;   	/**< unused data register */
  volatile tREG08   	unused_11;   	/**< unused data register */
  volatile tREG08   	unused_12;   	/**< unused data register */
  volatile tREG08   	unused_13;   	/**< unused data register */
  volatile tREG08   	unused_14;   	/**< unused data register */
  volatile tREG08   	unused_15;   	/**< unused data register */
  volatile tREG08   	unused_16;   	/**< unused data register */
  volatile tREG08   	unused_17;   	/**< unused data register */
  volatile tREG08   	unused_18;   	/**< unused data register */
  volatile tCPMUOSC 	osc;   			/**< CPMU Oscillator register */
  }tCPMU;

/* Prototypes */
void clock_init(unsigned long BusClock);
void clock_init_ext(unsigned long BusClock, unsigned long ExtFreq);
clock_dividers calc_prs(unsigned long FPLL, unsigned char ExtClock, unsigned long ExtFreq);
clock_dividers search_prs(unsigned long Fref, unsigned long FPLL);
void set_clock(clock_dividers ClockConfig, unsigned char ExtClock);

#endif /* CPMU_H_ */
/** @}*/

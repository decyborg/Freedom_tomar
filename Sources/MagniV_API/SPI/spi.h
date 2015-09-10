/** \addtogroup SPI Serial Peripheral interface
 *  @{
 */
/**
 *  @file spi.h
 *
 * 	@brief Contains Serial peripheral interface API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */

#ifndef SPI_H_
#define SPI_H_

/* Include derivative support */
#include "derivative.h"
#include "common.h"

/* Typedefs */
/** A structure that holds the prescaler values for the baudrate configuration
 * 
 * */
typedef struct {
	unsigned char SPPR;		/**< SPI Baud Rate Preselection Bits */
	unsigned char SPR;		/**< SPI Baud Rate Selection Bits */
	unsigned long error;	/**< Calculated error with the current configuration */
}spi_divider;

/**
* @var uSPICR1 tSPICR1
*/
/**
* @union uSPICR1
* SPI Control Register 1
*/
typedef union uSPICR1
{
  tU08   byte;        /**< access register as byte */
  struct
  {
    tU08 lsbfe      :1;      /**< LSB-First Enable */
    tU08 ssoe      	:1;      /**< Slave select output enable   */
    tU08 cpha    	:1;      /**< SPI Clock Phase Bit */
    tU08 cpol    	:1;      /**< SPI Clock polarity  */
    tU08 mstr       :1;      /**< SPI Master/slave Mode Select Bit */
    tU08 sptie    	:1;      /**< SPI Transmit Interrupt Enable */
    tU08 spe 		:1;      /**< SPI System Enable Bit  */
    tU08 spie   	:1;      /**< SPI Interrupt Enable Bit */
  }bit;           /**< access register as bits */
}tSPICR1;

/**
* @var uSPICR2 tSPICR2
*/
/**
* @union uSPICR2
* SPI Control Register 2
*/
typedef union uSPICR2
{
  tU08   byte;        /**< access register as byte */
  struct
  {
    tU08 spc0	   	:1;      /**< Serial Pin Control Bit 0 */
    tU08 spiswai    :1;      /**< SPI Stop In Wait Mode Bit   */
    tU08 	    	:1;      /**< Reserved Bit */
    tU08 bidiroe    :1;      /**< Output Enable in the Bidirectional Mode of Operation  */
    tU08 modefen    :1;      /**< Mode Fault Enable Bit */
    tU08 	    	:1;      /**< Reserved Bit */
    tU08 xfrw 		:1;      /**< Transfer Width  */
    tU08 		   	:1;      /**< Reserved Bit */
  }bit;           /**< access register as bits */
}tSPICR2;


/**
* @var uSPIBR tSPIBR
*/
/**
* @union uSPIBR
* SPI Baud Rate Register
*/
typedef union uSPIBR
{
  tU08   byte;        /**< access register as byte */
  struct
  {
    tU08 SPR	   	:3;      /**< SPI Baud Rate Selection Bits */
    tU08 		    :1;      /**< Reserved Bit  */
    tU08 SPPR	    :3;      /**< SPI Baud Rate Preselection Bits  */
    tU08 		   	:1;      /**< Reserved Bit */
  }bit;           /**< access register as bits */
}tSPIBR;

/**
* @var uSPISR tSPISR
*/
/**
* @union uSPISR
* SPI Status Register
*/
typedef union uSPISR
{
  tU08   byte;        /**< access register as byte */
  struct
  {
    tU08 		   	:4;      /**< Reserved Bits */
    tU08 modf	    :1;      /**< Mode Fault Flag */
    tU08 sptef	    :1;      /**< SPI Transmit Empty Flag */
    tU08 		    :1;      /**< Reserved Bit  */
    tU08 spif	    :1;      /**< SPIF Interrupt Flag */
  }bit;           /**< access register as bits */
}tSPISR;

/**
* @var uSPIDR tSPIDR
*/
/**
* @union uSPIDR
* SPI Data Register
*/
typedef union uSPIDR
{
  tU16   word;        /**< access register as byte */
  struct
  {
    tREG08 spidrl	   	;      /**< SPI Data Register Low */
    tREG08 spidrh  		;      /**< SPI Data Register High */
  }byte;           /**< access register as bytes */
}tSPIDR;

/**
* @struct tSPI
* spi datastructure
*/
typedef struct          	  /**< spi data structure  */
  {
  volatile tSPICR1  spicr1;   /**< SPI Control Register 1 */
  volatile tSPICR2  spicr2;   /**< SPI Control Register 2 */
  volatile tSPIBR  	spibr;    /**< SPI Baud Rate Register */
  volatile tSPISR  	spisr;    /**< SPI Status Register */
  volatile tSPIDR   spidr;    /**< SPI Data Register */
  }tSPI;

/* Macro definition */
#define BIT_8		0
#define BIT_16		1
#define SPI_MODE0	0
#define SPI_MODE1	1
#define SPI_MODE2	2
#define SPI_MODE3	3
  
  
/* Prototypes */
void spi_init_mst(unsigned long BusClock, unsigned long baudrate, unsigned char transfer_width, unsigned char SPI_MODE);
void spi_init_slv(unsigned char transfer_width, unsigned char SPI_MODE);
spi_divider spi_baud_cal(unsigned long BusClock, unsigned long baudrate);
void send_SPI(word data);
word get_SPI(void);
word tranfer_SPI(word data);

#endif /* SPI_H_ */
/** @}*/

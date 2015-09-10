/** \addtogroup SPI Serial Peripheral interface
 *  @{
 */
/**	
 *  @file spi.c
 *  
 * 	@brief Contains serial peripheral interface API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */

#include "spi.h"

/** \addtogroup CoreSPI Core SPI API functions  
 *  @{
 */
/**	Initializes the SPI interface to the desired baudrate as a Master.
 * 
 * 	This functions initializes the SPI interface to act as a master device, it sets
 * 	the frequency of the SPI clock to the best possible match. It allows to select between
 * 	8-bit transfers or 16-bit transfers by passing the macro BIT_8 or BIT_16 respectively.
 * 	The SPI_MODE parameter selects the Clock Polarity and Clock Phase for the communication protocol.
 * 	In order for an SPI transaction to occur successfully both master and slave must have the same
 * 	Clock Polarity and Clock phase configuration.
 * 	The Clock Polarity and Clock Phase configuration can be achieved as follows
 * <table border="1">
 * <tr>
 *   <td>SPI_MODE</td>
 *   <td>Clock Phase</td>
 *   <td>Clock Polarity</td>		
 * </tr>
 * <tr>
 *   <td>SPI_MODE0</td>
 *   <td>0</td>		
 *   <td>0</td>
 * </tr>
 * <tr>
 *   <td>SPI_MODE1</td>
 *   <td>0</td>		
 *   <td>1</td>
 * </tr>
 * <tr>
 *   <td>SPI_MODE2</td>
 *   <td>1</td>		
 *   <td>0</td>
 * </tr>
 * <tr>
 *   <td>SPI_MODE3</td>
 *   <td>1</td>		
 *   <td>1</td>
 * </tr>
 * </table>
 * By setting the Clock Polarity to zero active-high clocks are selected. In idle state SCK is low.
 * 
 * By setting the Clock Polarity to one active-low clocks selected. In idle state SCK is high.
 * 
 * By setting the Clock Phase to zero sampling of data occurs at odd edges (1,3,5,...) of the SCK clock.
 * 
 * By setting the Clock Phase to one sampling of data occurs at even edges (2,4,6,...) of the SCK clock.
 * 
 * For more information refer to the Reference Manual of your device.
 * The following example sets the SPI clock to a frequency of 12.5MHz with a Bus frequency of 25MHz, selecting
 * an 8-Bit transfer, Clock Polarity with active-high clocks and clock phase with sampling of data at odd edges:
 * @code
 * 	spi_init_mst(25000000, 12500000, BIT_8, SPI_MODE0);
 * @endcode
 * 
* 	@param	BusClock		Bus frequency of the device
* 	@param	baudrate		Desired baudrate
* 	@param  transfer_width  Select between 8bit transfer and 16bit transfer
* 	@param  SPI_MODE        Selects the Clock polarity and Clock phase
 * */
void spi_init_mst(unsigned long BusClock, unsigned long baudrate, unsigned char transfer_width, unsigned char SPI_MODE){
	spi_divider spi_prs;
	tSPI* pSPI = (tSPI*) SPI_ADDR;
	
	spi_prs = spi_baud_cal(BusClock, baudrate);				/* Calculate prescaler values */
	pSPI->spibr.bit.SPR = spi_prs.SPR;						/* Set baud rate */
	pSPI->spibr.bit.SPPR = spi_prs.SPPR;
	pSPI->spicr1.bit.cpol = SPI_MODE && 0b01;				/* Select Clock Polarity */
	pSPI->spicr1.bit.cpha = SPI_MODE && 0b10;				/* Select Clock Phase */
	pSPI->spicr1.bit.mstr = 1;								/* Select Master */
	pSPI->spicr2.bit.modefen = 1;							/* Use SS */
	pSPI->spicr1.bit.ssoe = 1;
	pSPI->spicr2.bit.xfrw = transfer_width;					/* Select between 8bit and 16bit transfer */
	pSPI->spicr1.bit.spe = 1;								/* Enable SPI System */
}



/**	Initializes the SPI interface as slave.
 * 
 * 	This functions initializes the SPI interface to act as a slave device. It allows to select between
 * 	8-bit transfers or 16-bit transfers by passing the macro BIT_8 or BIT_16 respectively.
 * 	The SPI_MODE parameter selects the Clock Polarity and Clock Phase for the communication protocol.
 * 	In order for an SPI transaction to occur successfully both master and slave must have the same
 * 	Clock Polarity and Clock phase configuration.
 * 	The Clock Polarity and Clock Phase configuration can be achieved as follows
 * <table border="1">
 * <tr>
 *   <td>SPI_MODE</td>
 *   <td>Clock Phase</td>
 *   <td>Clock Polarity</td>		
 * </tr>
 * <tr>
 *   <td>SPI_MODE0</td>
 *   <td>0</td>		
 *   <td>0</td>
 * </tr>
 * <tr>
 *   <td>SPI_MODE1</td>
 *   <td>0</td>		
 *   <td>1</td>
 * </tr>
 * <tr>
 *   <td>SPI_MODE2</td>
 *   <td>1</td>		
 *   <td>0</td>
 * </tr>
 * <tr>
 *   <td>SPI_MODE3</td>
 *   <td>1</td>		
 *   <td>1</td>
 * </tr>
 * </table>
 * By setting the Clock Polarity to zero active-high clocks are selected. In idle state SCK is low.
 * 
 * By setting the Clock Polarity to one active-low clocks selected. In idle state SCK is high.
 * 
 * By setting the Clock Phase to zero sampling of data occurs at odd edges (1,3,5,...) of the SCK clock.
 * 
 * By setting the Clock Phase to one sampling of data occurs at even edges (2,4,6,...) of the SCK clock.
 * 
 * For more information refer to the Reference Manual of your device.
 * The following example selects an 8-Bit transfer, Clock Polarity with active-high clocks and clock phase
 * with sampling of data at odd edges:
 * @code
 * 	spi_init_slv(BIT_8, SPI_MODE0);
 * @endcode
 * 
 *  
* 	@param  transfer_width  Select between 8bit transfer and 16bit transfer
* 	@param  SPI_MODE        Selects the Clock polarity and Clock phase
 * */
void spi_init_slv(unsigned char transfer_width, unsigned char SPI_MODE){
	spi_divider spi_prs;
	tSPI* pSPI = (tSPI*) SPI_ADDR;
	
	pSPI->spicr1.bit.mstr = 0;								/* Select Slave */
	pSPI->spicr2.bit.modefen = 1;							/* Use SS */
	pSPI->spicr1.bit.ssoe = 1;
	pSPI->spicr1.bit.cpol = SPI_MODE && 0b01;				/* Select Clock Polarity */
	pSPI->spicr1.bit.cpha = SPI_MODE && 0b10;				/* Select Clock Phase */
	pSPI->spicr2.bit.xfrw = transfer_width;					/* Select between 8bit and 16bit transfer */
	pSPI->spicr1.bit.spe = 1;								/* Enable SPI System */
}

/** Sends data through SPI
 * 
 * @param data Data to be sent
 * */
void send_SPI(word data){
	tSPI* pSPI = (tSPI*) SPI_ADDR;
	while(!pSPI->spisr.bit.sptef){};
	pSPI->spidr.word = data;
}

/** Receives data through SPI
 * 
 * @return Data received through SPI
 * */
word get_SPI(void){
	tSPI* pSPI = (tSPI*) SPI_ADDR;
	
	while(!pSPI->spisr.bit.spif){};									/* Wait for data */
	return pSPI->spidr.word;										/* Return received data */
}

/** Sends and receives data through the SPI interface
 * 
 * @param data Data to be send through the SPI interface
 * 
 * @return Data received through the SPI interface
 * */
word tranfer_SPI(word data){
	send_SPI(data);													/* Send data */
	return get_SPI();												/* Receive data */
}
/** @}*/
/** \addtogroup helperSPI Helper functions  
 *  @{
 */
/** Calculates the best dividers values for the desired frequency
 * 
 * 	@param BusClock Bus frequency of the device
 * 	@param baudrate	Desired baudrate
 * 	
 * 	@return Prescaler values that best match the desired baudrate, and the calculated error with these values
 * */
spi_divider spi_baud_cal(unsigned long BusClock, unsigned long baudrate){
	unsigned long baudrate_temp, min_error;
	long	error;
	unsigned int baud_div;
	unsigned char SPPR_temp, SPR_temp;
	spi_divider spi_pr;
	min_error = 0;													/* Initialize temporary error variable */
	
	for(SPPR_temp = 0; SPPR_temp <= SPPR_MAX; ++SPPR_temp){
		for(SPR_temp = 0; SPR_temp <= SPR_MAX; ++SPR_temp){
			baud_div = (SPPR_temp + 1) * (1 << (SPR_temp + 1));		/* Calculate baudrate divisor (1 << x equals 2^x) */
			baudrate_temp = BusClock / baud_div;					/* Calculate baudrate with current values */
			error = baudrate_temp - baudrate;
			error = error < 0 ? error * (-1) : error;				/* Error absolute value */
			if(error == 0){											/* Perfect match return values */
				spi_pr.SPPR = SPPR_temp;
				spi_pr.SPR = SPR_temp;
				spi_pr.error = error;
				return spi_pr;
			} else{
				if(min_error == 0){									/* First time it enters the loop */
					spi_pr.SPPR = SPPR_temp;						/* Store values */
					spi_pr.SPR = SPR_temp;
					spi_pr.error = error;
					min_error = error;
				} else if(error < min_error){						/* Better values have been found */
					spi_pr.SPPR = SPPR_temp;
					spi_pr.SPR = SPR_temp;
					spi_pr.error = error;
					min_error = error;								/* Update minimum error */
				}
			}
		}
	}
	
	return spi_pr;													/* Return found values that better match the baudrate */
}
/** @}*/
/** @}*/

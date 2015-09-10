/*
 * hw_def.h
 *
 *  Created on: Aug 12, 2015
 *      Author: B52932
 */

#ifndef HW_DEF_H_
#define HW_DEF_H_
#include "derivative.h"

#if (defined(_MC9S12ZVL32_H)) /* S12ZVL32 specific definitions */
/* CPMU definitions */
#define CPMU_ADDR 0x06C4	/* Address in which CPMUSYNR is declared */
#define VCO_MIN 32000000
#define VCO_MID 48000000
#define VCO_MAX 64000000
#define POSTDIV_MAX 31
#define SYNDIV_MAX 63
#define REFDIV_MAX 15
#define REF_MIN_TH1 1000000
#define REF_MIN_TH2 2000000
#define REF_MID_TH  6000000
#define REF_MAX_TH 12000000
#define SELECT_VCO_RANGE(x) (x <= VCO_MID)? 0 : 1 
#define SELECT_REF_RANGE(x) ( (((x >= REF_MIN_TH1) && (x <= REF_MIN_TH2))? 0 : 1) ^ ((x <= REF_MID_TH)? 0 : 3) | ((x <= REF_MAX_TH)? 0 : 1))
/* SCI definitions */
#define SCI0 					0x0700
#define SCI1 					0x0710
#define LIN_PHY_INTEGRATED		1						/* LIN physical layer integrated */
#define SCI_ROUTED 				SCI0					/* Channel routed to LINPHY */
#define MODIFY_ROUTING 			MODRR0_S0L0RR			/* Register that routes SCI0 to external pins */
#define ROUTING_VALUE			0b110					/* Value to write to the register */
/* SPI definitions */
#define SPPR_MAX	7
#define SPR_MAX		7
#define SPI_ADDR	0x0780
#endif /* END of S12ZVL32 specific definitions */

#if (defined(_MC9S12VR64_H)) /* S12VR64 specific definitions */
/* CPMU definitions */
#define CPMU_ADDR 0x0034		/* Address in which CPMUSYNR is declared */
#define VCO_MIN 32000000
#define VCO_MID 48000000
#define VCO_MAX 50000000
#define POSTDIV_MAX 31
#define SYNDIV_MAX 63
#define REFDIV_MAX 15
#define REF_MIN_TH1 1000000
#define REF_MIN_TH2 2000000
#define REF_MID_TH  6000000
#define REF_MAX_TH 12000000
#define SELECT_VCO_RANGE(x) (x <= VCO_MID)? 0 : 1 
#define SELECT_REF_RANGE(x) ( (((x >= REF_MIN_TH1) && (x <= REF_MIN_TH2))? 0 : 1) ^ ((x <= REF_MID_TH)? 0 : 3) | ((x <= REF_MAX_TH)? 0 : 1))
/* SCI definitions */
#define SCI0 			0x00C8
#define SCI1 			0x00D0
#define LIN_PHY_INTEGRATED		1				/* LIN physical layer integrated */
#define SCI_ROUTED 		SCI0					/* Channel routed to LINPHY */
#define MODIFY_ROUTING 	MODRR2_S0L0RR			/* Register that routes SCI0 to external pins */
#define ROUTING_VALUE	0b1100					/* Value to write to the register */
/* SPI definitions */
#define SPPR_MAX	7
#define SPR_MAX		7
#define SPI_ADDR	0x00D8
#endif /* END of S12VR64 specific definitions */

#if (defined(_MC9S12ZVML128_H)) /* S12ZVML128 specific definitions */
/* CPMU definitions */
#define CPMU_ADDR 0x06C4		/* Address in which CPMUSYNR is declared */
#define VCO_MIN 32000000	
#define VCO_MIN_TH 48000000
#define VCO_MID_TH  80000000
#define VCO_MAX	   100000000
#define POSTDIV_MAX 31
#define SYNDIV_MAX 63
#define REFDIV_MAX 15
#define REF_MIN_TH1 1000000
#define REF_MIN_TH2 2000000
#define REF_MID_TH  6000000
#define REF_MAX_TH 12000000
#define SELECT_VCO_RANGE(x) ( ((x <= VCO_MIN_TH)? 0 : 1) | ((x > VCO_MID_TH) ? 0b10:0) ) 
#define SELECT_REF_RANGE(x) ( (((x >= REF_MIN_TH1) && (x <= REF_MIN_TH2))? 0 : 1) ^ ((x <= REF_MID_TH)? 0 : 3) | ((x <= REF_MAX_TH)? 0 : 1))
/* SCI definitions */
#define SCI0 			0x0700
#define SCI1 			0x0710
#define LIN_PHY_INTEGRATED		1				/* LIN physical layer integrated */
#define SCI_ROUTED 		SCI0					/* Channel routed to LINPHY */
#define MODIFY_ROUTING 	MODRR0_S0L0RR			/* Register that routes SCI0 to external pins */
#define ROUTING_VALUE	0b110					/* Value to write to the register */
/* SPI definitions */
#define SPPR_MAX	7
#define SPR_MAX		7
#define SPI_ADDR	0x0780
#endif /* END of S12ZVML128 specific definitions */

#if (defined(_MC9S12ZVC192_H)) /* S12ZVC192 specific definitions */
/* CPMU definitions */
#define CPMU_ADDR 0x06C4		/* Address in which CPMUSYNR is declared */
#define VCO_MIN 32000000
#define VCO_MID 48000000
#define VCO_MAX 64000000
#define POSTDIV_MAX 31
#define SYNDIV_MAX 63
#define REFDIV_MAX 15
#define REF_MIN_TH1 1000000
#define REF_MIN_TH2 2000000
#define REF_MID_TH  6000000
#define REF_MAX_TH 12000000
#define SELECT_VCO_RANGE(x) (x <= VCO_MID)? 0 : 1 
#define SELECT_REF_RANGE(x) ( (((x >= REF_MIN_TH1) && (x <= REF_MIN_TH2))? 0 : 1) ^ ((x <= REF_MID_TH)? 0 : 3) | ((x <= REF_MAX_TH)? 0 : 1))
/* SCI definitions */
#define SCI0 			0x0700
#define SCI1 			0x0710
#define LIN_PHY_INTEGRATED		0				/* This device does not have LINPHY */
/* SPI definitions */
#define SPPR_MAX	7
#define SPR_MAX		7
#define SPI_ADDR	0x0780
#endif /* END of S12ZVC192 specific definitions */

#if (defined(_MC9S12ZVH_H)) /* S12ZVH specific definitions */
/* CPMU definitions */
#define CPMU_ADDR 0x06C4		/* Address in which CPMUSYNR is declared */
#define VCO_MIN 32000000
#define VCO_MID 48000000
#define VCO_MAX 64000000
#define POSTDIV_MAX 31
#define SYNDIV_MAX 63
#define REFDIV_MAX 15
#define REF_MIN_TH1 1000000
#define REF_MIN_TH2 2000000
#define REF_MID_TH  6000000
#define REF_MAX_TH 12000000
#define SELECT_VCO_RANGE(x) (x <= VCO_MID)? 0 : 1 
#define SELECT_REF_RANGE(x) ( (((x >= REF_MIN_TH1) && (x <= REF_MIN_TH2))? 0 : 1) ^ ((x <= REF_MID_TH)? 0 : 3) | ((x <= REF_MAX_TH)? 0 : 1))
/* SCI definitions */
#define SCI0 			0x0700
#define SCI1 			0x0710
#define LIN_PHY_INTEGRATED		0				/* This device does not have LINPHY */
/* SPI definitions */
#define SPPR_MAX	7
#define SPR_MAX		7
#define SPI_ADDR	0x0780
#endif /* END of S12ZVH specific definitions */

#endif /* HW_DEF_H_ */

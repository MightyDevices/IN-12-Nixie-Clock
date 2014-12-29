/*
 * scb.h
 *
 *  Created on: 24-02-2013
 *      Author: Tomek
 */

#ifndef STM32L_SCB_H_
#define STM32L_SCB_H_

#include <stm32l/stm32l.h>

/* base */
#define SCB_BASE            				(0xE000E000 + 0x0D00)
/* scb */
#define SCB									((scb_t *)SCB_BASE)

/* registers */
typedef struct {
	reg32_t CPUID;
	reg32_t ICSR;
	reg32_t VTOR;
	reg32_t AIRCR;
	reg32_t SCR;
	reg32_t CCR;
	reg8_t  SHPR[12];
	reg32_t SHCSR;
	reg32_t CFSR;
	reg32_t HFSR;
	reg32_t DFSR;
	reg32_t MMFAR;
	reg32_t BFAR;
	reg32_t AFSR;
	reg32_t PFR[2];
	reg32_t DFR;
	reg32_t ADR;
	reg32_t MMFR[4];
	reg32_t ISAR[5];
	reg32_t RESERVED0[5];
	reg32_t CPACR;
} __attribute__((packed)) scb_t;

#define SCB_CPUID_IMPLEMENTER          		(0xff000000)
#define SCB_CPUID_VARIANT              		(0x00f00000)
#define SCB_CPUID_ARCHITECTURE         		(0x000f0000)
#define SCB_CPUID_PARTNO                	(0x0000fff0)
#define SCB_CPUID_REVISION              	(0x0000000f)

#define SCB_ICSR_NMIPENDSET            		(1 << 31)
#define SCB_ICSR_PENDSVSET             		(1 << 28)
#define SCB_ICSR_PENDSVCLR             		(1 << 27)
#define SCB_ICSR_PENDSTSET             		(1 << 26)
#define SCB_ICSR_PENDSTCLR             		(1 << 25)
#define SCB_ICSR_ISRPREEMPT            		(1 << 23)
#define SCB_ICSR_ISRPENDING            		(1 << 22)
#define SCB_ICSR_VECTPENDING           		(0x1ff << 12)
#define SCB_ICSR_RETTOBASE             		(1 << 11)
#define SCB_ICSR_VECTACTIVE            		(0x1ff)

#define SCB_VTOR_TBLOFF                    	(0x1FFFFFF << 7)

#define SCB_AIRCR_VECTKEY                  	(0xFFFF << 16)
#define SCB_AIRCR_VECTKEYSTAT              	(0x5FA  << 16)
#define SCB_AIRCR_ENDIANESS                	(1 << 15)
#define SCB_AIRCR_PRIGROUP                 	(7 << 8)
#define SCB_AIRCR_SYSRESETREQ              	(1 << 2)
#define SCB_AIRCR_VECTCLRACTIVE            	(1 << 1)
#define SCB_AIRCR_VECTRESET                	(1 << 0)

#define SCB_SCR_SEVONPEND                  	(1 << 4)
#define SCB_SCR_SLEEPDEEP                  	(1 << 2)
#define SCB_SCR_SLEEPONEXIT                	(1 << 1)

#define SCB_CCR_STKALIGN                   	(1 << 9)
#define SCB_CCR_BFHFNMIGN                  	(1 << 8)
#define SCB_CCR_DIV_0_TRP                  	(1 << 4)
#define SCB_CCR_UNALIGN_TRP                	(1 << 3)
#define SCB_CCR_USERSETMPEND               	(1 << 1)
#define SCB_CCR_NONBASETHRDENA             	(1 << 0)

#define SCB_SHCSR_USGFATENA              	(1 << 18)
#define SCB_SHCSR_BUSFATENA              	(1 << 17)
#define SCB_SHCSR_MEMFATENA              	(1 << 16)
#define SCB_SHCSR_SVCALLPENDED             	(1 << 15)
#define SCB_SHCSR_BUSFATPENDED           	(1 << 14)
#define SCB_SHCSR_MEMFATPENDED           	(1 << 13)
#define SCB_SHCSR_USGFATPENDED           	(1 << 12)
#define SCB_SHCSR_SYSTICKACT               	(1 << 11)
#define SCB_SHCSR_PENDSVACT                	(1 << 10)
#define SCB_SHCSR_MONITORACT               	(1 << 8)
#define SCB_SHCSR_SVCALLACT                	(1 << 7)
#define SCB_SHCSR_USGFATACT              	(1 << 3)
#define SCB_SHCSR_BUSFATACT              	(1 << 1)
#define SCB_SHCSR_MEMFATACT              	(1 << 0)

#define SCB_CFSR_USGFATSR                	(0xFFFF << 16)
#define SCB_CFSR_BUSFATSR                	(0xFF << 8)
#define SCB_CFSR_MEMFATSR                	(0xFF << 0)

#define SCB_HFSR_DEBUGEVT                  	(1 << 31)
#define SCB_HFSR_FORCED                    	(1 << 30)
#define SCB_HFSR_VECTTBL                   	(1 << 1)

#define SCB_DFSR_EXTERNAL                  	(1 << 4)
#define SCB_DFSR_VCATCH                    	(1 << 3)
#define SCB_DFSR_DWTTRAP                   	(1 << 2)
#define SCB_DFSR_BKPT                      	(1 << 1)
#define SCB_DFSR_HALTED                    	(1 << 0)

/* reset system */
void SCB_Reset(void);

#endif /* SCB_H_ */

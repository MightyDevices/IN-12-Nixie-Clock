/*
 * stm32.h
 *
 *  Created on: 13-06-2012
 *      Author: Tomek
 */

#ifndef STM32L_STM32L_H_
#define STM32L_STM32L_H_

#include <stdint.h>

/* enable */
#define ENABLE								1
/* disable */
#define DISABLE								0

/* ram function */
#define RAMFUNC __attribute__ ((long_call, section (".data")))
/* eeprom data */
/* for placing variables in eeprom memory */
#define EEMEM 	__attribute__((section(".eeprom")))

/* register type 8 bit*/
typedef volatile uint8_t reg8_t;
/* register type 16 bit*/
typedef volatile uint16_t reg16_t;
/* register type */
typedef volatile uint32_t reg32_t;
/* bitband type */
typedef volatile uint32_t * bitband_t;

/* base address for bit banding */
#define BITBAND_SRAM_REF               		(0x20000000)
/* base address for bit banding */
#define BITBAND_SRAM_BASE              		(0x22000000)
/* base address for bit banding */
#define BITBAND_PERIPH_REF               	(0x40000000)
/* base address for bit banding */
#define BITBAND_PERIPH_BASE              	(0x42000000)

/* sram bit band */
#define BITBAND_SRAM(address, bit)     (BITBAND_SRAM_BASE +   \
		(((uint32_t)address) - BITBAND_SRAM_REF) * 32 + (bit) * 4)

/* periph bit band */
#define BITBAND_PERIPH(address, bit)   ((void *)(BITBAND_PERIPH_BASE + \
		(((uint32_t)address) - BITBAND_PERIPH_REF) * 32 + (bit) * 4))

/* enable interrupts */
void STM32_EnableInterrupts(void);
/* disable interupts */
void STM32_DisableInterrupts(void);


#endif /* STM32_H_ */

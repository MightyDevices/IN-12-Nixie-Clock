/*
 * comp.h
 *
 *  Created on: 23-01-2014
 *      Author: Tomek
 */

#ifndef STM32L_COMP_H_
#define STM32L_COMP_H_

#include <stm32l/stm32l.h>

/* register base */
#define COMP_BASE             				0x40007C00

/* comparator registers */
typedef struct {
	reg32_t CSR;
} comp_t;

/* comparator */
#define COMP								((comp_t *)COMP_BASE)

/* COMP_CSR register */
#define COMP_CSR_10KPU                      0x00000001
#define COMP_CSR_400KPU                     0x00000002
#define COMP_CSR_10KPD                      0x00000004
#define COMP_CSR_400KPD                     0x00000008
#define COMP_CSR_CMP1EN                     0x00000010
#define COMP_CSR_SW1                        0x00000020
#define COMP_CSR_CMP1OUT                    0x00000080
#define COMP_CSR_SPEED                      0x00001000
#define COMP_CSR_CMP2OUT                    0x00002000
#define COMP_CSR_VREFOUTEN                  0x00010000
#define COMP_CSR_WNDWE                      0x00020000
#define COMP_CSR_INSEL                      0x001C0000
#define COMP_CSR_INSEL_0                    0x00040000
#define COMP_CSR_INSEL_1                    0x00080000
#define COMP_CSR_INSEL_2                    0x00100000
#define COMP_CSR_OUTSEL                     0x00E00000
#define COMP_CSR_OUTSEL_0                   0x00200000
#define COMP_CSR_OUTSEL_1                   0x00400000
#define COMP_CSR_OUTSEL_2                   0x00800000
#define COMP_CSR_FCH3                       0x04000000
#define COMP_CSR_FCH8                       0x08000000
#define COMP_CSR_RCH13                      0x10000000
#define COMP_CSR_CAIE                       0x20000000
#define COMP_CSR_CAIF                       0x40000000
#define COMP_CSR_TSUSP                      0x80000000

/* comparator speed */
#define COMP_SPEED_SLOW                    	0x00000000
#define COMP_SPEED_FAST                     0x00001000

/* comparator inverting input configuration */
#define COMP_INVINPUT_NONE                	0x00000000
#define COMP_INVINPUT_IO                  	0x00040000
#define COMP_INVINPUT_VREFINT             	0x00080000
#define COMP_INVINPUT_3_4VREFINT          	0x000C0000
#define COMP_INVINPUT_1_2VREFINT          	0x00100000
#define COMP_INVINPUT_1_4VREFINT          	0x00140000
#define COMP_INVINPUT_DAC1                	0x00180000
#define COMP_INVINPUT_DAC2                	0x001C0000

/* comparator output selection */
#define COMP_OUTPUTSELECT_TIM2IC4           0x00000000
#define COMP_OUTPUTSELECT_TIM2OCREFCLR      0x00200000
#define COMP_OUTPUTSELECT_TIM3IC4           0x00400000
#define COMP_OUTPUTSELECT_TIM3OCREFCLR      0x00600000
#define COMP_OUTPUTSELECT_TIM4IC4           0x00800000
#define COMP_OUTPUTSELECT_TIM4OCREFCLR      0x00A00000
#define COMP_OUTPUTSELECT_TIM10IC1          0x00C00000
#define COMP_OUTPUTSELECT_NONE              0x00E00000

/* comparator init struct */
typedef struct
{
	/* comparator speed */
	uint32_t speed;
	/* selects input */
	uint32_t inverting_input;
	/* output redirection */
	uint32_t output_select;
} comp_init_t;

#endif /* COMP_H_ */

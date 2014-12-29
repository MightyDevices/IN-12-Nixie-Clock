/*
 * dac.h
 *
 *  Created on: 29-09-2013
 *      Author: Tomek
 */

#ifndef STM32L_DAC_H_
#define STM32L_DAC_H_

#include <stm32l/stm32l.h>

/* dac registers base address */
#define DAC									((dac_t *)0x40007400)

/* dar registers */
typedef struct {
	reg32_t CR;
	reg32_t SWTRIGR;
	reg32_t DHR12R1;
	reg32_t DHR12L1;
	reg32_t DHR8R1;
	reg32_t DHR12R2;
	reg32_t DHR12L2;
	reg32_t DHR8R2;
	reg32_t DHR12RD;
	reg32_t DHR12LD;
	reg32_t DHR8RD;
	reg32_t DOR1;
	reg32_t DOR2;
	reg32_t SR;
} dac_t;

/* DAC_CR register */
#define DAC_CR_EN1                         	0x00000001
#define DAC_CR_BOFF1                       	0x00000002
#define DAC_CR_TEN1                        	0x00000004
#define DAC_CR_TSEL1                       	0x00000038
#define DAC_CR_TSEL1_0                     	0x00000008
#define DAC_CR_TSEL1_1                     	0x00000010
#define DAC_CR_TSEL1_2                     	0x00000020
#define DAC_CR_WAVE1                       	0x000000C0
#define DAC_CR_WAVE1_0                     	0x00000040
#define DAC_CR_WAVE1_1                     	0x00000080
#define DAC_CR_MAMP1                       	0x00000F00
#define DAC_CR_MAMP1_0                     	0x00000100
#define DAC_CR_MAMP1_1                     	0x00000200
#define DAC_CR_MAMP1_2                     	0x00000400
#define DAC_CR_MAMP1_3                     	0x00000800
#define DAC_CR_DMAEN1                      	0x00001000
#define DAC_CR_EN2                         	0x00010000
#define DAC_CR_BOFF2                       	0x00020000
#define DAC_CR_TEN2                        	0x00040000
#define DAC_CR_TSEL2                       	0x00380000
#define DAC_CR_TSEL2_0                     	0x00080000
#define DAC_CR_TSEL2_1                     	0x00100000
#define DAC_CR_TSEL2_2                     	0x00200000
#define DAC_CR_WAVE2                       	0x00C00000
#define DAC_CR_WAVE2_0                     	0x00400000
#define DAC_CR_WAVE2_1                     	0x00800000
#define DAC_CR_MAMP2                       	0x0F000000
#define DAC_CR_MAMP2_0                     	0x01000000
#define DAC_CR_MAMP2_1                     	0x02000000
#define DAC_CR_MAMP2_2                     	0x04000000
#define DAC_CR_MAMP2_3                     	0x08000000
#define DAC_CR_DMAEN2                      	0x10000000

/* DAC_SWTRIGR register */
#define DAC_SWTRIGR_SWTRIG1                	0x01
#define DAC_SWTRIGR_SWTRIG2                	0x02

/* DAC_DHR12R1 register */
#define DAC_DHR12R1_DACC1DHR               	0x0FFF

/* DAC_DHR12L1 register */
#define DAC_DHR12L1_DACC1DHR               	0xFFF0

/* DAC_DHR8R1 register */
#define DAC_DHR8R1_DACC1DHR                	0xFF

/* DAC_DHR12R2 register */
#define DAC_DHR12R2_DACC2DHR               	0x0FFF

/* DAC_DHR12L2 register */
#define DAC_DHR12L2_DACC2DHR               	0xFFF0

/* DAC_DHR8R2 register */
#define DAC_DHR8R2_DACC2DHR                	0xFF

/* DAC_DHR12RD register */
#define DAC_DHR12RD_DACC1DHR               	0x00000FFF
#define DAC_DHR12RD_DACC2DHR               	0x0FFF0000

/* DAC_DHR12LD register */
#define DAC_DHR12LD_DACC1DHR               	0x0000FFF0
#define DAC_DHR12LD_DACC2DHR               	0xFFF00000

/*  DAC_DHR8RD register **/
#define DAC_DHR8RD_DACC1DHR                	0x00FF
#define DAC_DHR8RD_DACC2DHR                	0xFF00

/* DAC_DOR1 register */
#define DAC_DOR1_DACC1DOR                  	0x0FFF

/* DAC_DOR2 register */
#define DAC_DOR2_DACC2DOR                  	0x0FFF

/* DAC_SR register */
#define DAC_SR_DMAUDR1                     	0x00002000
#define DAC_SR_DMAUDR2                     	0x20000000


/* init struct */
typedef struct {
	uint32_t trigger;
	uint32_t wave_gen;
	uint32_t lfsr_unmask_triangle_amp;
	uint32_t output_buf;
} dac_init_t;

/* triggers */
#define DAC_TRIGGER_NONE                   	0x00000000
#define DAC_TRIGGER_T6_TRGO                	0x00000004
#define DAC_TRIGGER_T7_TRGO                	0x00000014
#define DAC_TRIGGER_T9_TRGO                	0x0000001C
#define DAC_TRIGGER_T2_TRGO                	0x00000024
#define DAC_TRIGGER_T4_TRGO                	0x0000002C
#define DAC_TRIGGER_EXT_IT9                	0x00000034
#define DAC_TRIGGER_SOFT               		0x0000003C

/* wave types */
#define DAC_WAVE_NONE            			0x00000000
#define DAC_WAVE_NOISE           			0x00000040
#define DAC_WAVE_TRIANGLE        			0x00000080

/* lfsr masks */
#define DAC_LFSRUNMASK_BIT0                	0x00000000
#define DAC_LFSRUNMASK_BITS1_0             	0x00000100
#define DAC_LFSRUNMASK_BITS2_0             	0x00000200
#define DAC_LFSRUNMASK_BITS3_0             	0x00000300
#define DAC_LFSRUNMASK_BITS4_0             	0x00000400
#define DAC_LFSRUNMASK_BITS5_0             	0x00000500
#define DAC_LFSRUNMASK_BITS6_0             	0x00000600
#define DAC_LFSRUNMASK_BITS7_0             	0x00000700
#define DAC_LFSRUNMASK_BITS8_0             	0x00000800
#define DAC_LFSRUNMASK_BITS9_0             	0x00000900
#define DAC_LFSRUNMASK_BITS10_0            	0x00000A00
#define DAC_LFSRUNMASK_BITS11_0            	0x00000B00

/* triangle amplitude */
#define DAC_TRIANGLE_AMPLITUDE_1            0x00000000
#define DAC_TRIANGLE_AMPLITUDE_3            0x00000100
#define DAC_TRIANGLE_AMPLITUDE_7            0x00000200
#define DAC_TRIANGLE_AMPLITUDE_15           0x00000300
#define DAC_TRIANGLE_AMPLITUDE_31           0x00000400
#define DAC_TRIANGLE_AMPLITUDE_63           0x00000500
#define DAC_TRIANGLE_AMPLITUDE_127          0x00000600
#define DAC_TRIANGLE_AMPLITUDE_255          0x00000700
#define DAC_TRIANGLE_AMPLITUDE_511          0x00000800
#define DAC_TRIANGLE_AMPLITUDE_1023         0x00000900
#define DAC_TRIANGLE_AMPLITUDE_2047         0x00000A00
#define DAC_TRIANGLE_AMPLITUDE_4095         0x00000B00

/* output buffer */
#define DAC_OUTPUT_BUFFER_ENABLE            0x00000000
#define DAC_OUTPUT_BUFFER_DISABLE           0x00000002

/* dac channels */
#define DAC_CHANNEL_1                      	0x00000000
#define DAC_CHANNEL_2                      	0x00000010

/* data align */
#define DAC_ALIGN_12B_R                    	0x00000000
#define DAC_ALIGN_12B_L                    	0x00000004
#define DAC_ALIGN_8B_R                     	0x00000008

/* interrupt flag */
#define DAC_IT_DMAUDR                      	0x00002000

/* status flag */
#define DAC_FLAG_DMAUDR                    	0x00002000

/* dac deinit */
void DAC_Deinit(void);
/* initialize dac */
void DAC_Init(uint32_t channel, dac_init_t *init);
/* initialize structure */
void DAC_StructInit(dac_init_t *init);
/* enable / disable channel */
void DAC_Cmd(uint32_t channel, int enable);
/* software trigger cmd */
void DAC_SoftwareTriggerCmd(uint32_t channel);
/* trigger both channels */
void DAC_DualSoftwareTriggerCmd(int enable);
/* wave generation cmd */
void DAC_WaveGenerationCmd(uint32_t channel, uint32_t wave, int enable);
/* set channel data */
void DAC_SetChannel1Data(uint32_t align, uint16_t data);
/* set channel data */
void DAC_SetChannel2Data(uint32_t align, uint16_t data);
/* set channel data */
void DAC_SetDualChannelData(uint32_t align, uint16_t data_1, uint16_t data_2);
/* get data output */
uint16_t DAC_GetDataOutputValue(uint32_t channel);
/* dac dma functions */
void DAC_DMACmd(uint32_t channel, int enable);
/* configure dac interrupt */
void DAC_ITConfig(uint32_t channel, uint32_t it, int enable);
/* get status */
uint16_t DAC_GetStatus(uint32_t channel);

#endif /* DAC_H_ */

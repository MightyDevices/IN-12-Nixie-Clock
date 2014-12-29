/*
 * stm32_adc.h
 *
 *  Created on: 02-08-2012
 *      Author: Tomek
 */

#ifndef STM32L_ADC_H_
#define STM32L_ADC_H_

#include <stm32l/stm32l.h>

/* base addresses */
#define ADC									((adc_com_t *)0x40012700)
/* registers */
#define ADC1								((adc_t *)0x40012400)

/* adcx registers */
typedef struct {
	reg32_t SR;
	reg32_t CR1;
	reg32_t CR2;
	reg32_t SMPR1;
	reg32_t SMPR2;
	reg32_t SMPR3;
	reg32_t JOFR1;
	reg32_t JOFR2;
	reg32_t JOFR3;
	reg32_t JOFR4;
	reg32_t HTR;
	reg32_t LTR;
	reg32_t SQR1;
	reg32_t SQR2;
	reg32_t SQR3;
	reg32_t SQR4;
	reg32_t SQR5;
	reg32_t JSQR;
	reg32_t JDR1;
	reg32_t JDR2;
	reg32_t JDR3;
	reg32_t JDR4;
	reg32_t DR;
	reg32_t SMPR0;
} adc_t;

/* ADC status register */
#define ADC_SR_AWD                          (0x00000001)
#define ADC_SR_EOC                          (0x00000002)
#define ADC_SR_JEOC                         (0x00000004)
#define ADC_SR_JSTRT                        (0x00000008)
#define ADC_SR_STRT                         (0x00000010)
#define ADC_SR_OVR                          (0x00000020)
#define ADC_SR_ADONS                        (0x00000040)
#define ADC_SR_RCNR                         (0x00000100)
#define ADC_SR_JCNR                         (0x00000200)

/* ADC control register 1 */
#define ADC_CR1_AWDCH                       (0x0000001F)
#define ADC_CR1_AWDCH_0                     (0x00000001)
#define ADC_CR1_AWDCH_1                     (0x00000002)
#define ADC_CR1_AWDCH_2                     (0x00000004)
#define ADC_CR1_AWDCH_3                     (0x00000008)
#define ADC_CR1_AWDCH_4                     (0x00000010)
#define ADC_CR1_EOCIE                       (0x00000020)
#define ADC_CR1_AWDIE                       (0x00000040)
#define ADC_CR1_JEOCIE                      (0x00000080)
#define ADC_CR1_SCAN                        (0x00000100)
#define ADC_CR1_AWDSGL                      (0x00000200)
#define ADC_CR1_JAUTO                       (0x00000400)
#define ADC_CR1_DISCEN                      (0x00000800)
#define ADC_CR1_JDISCEN                     (0x00001000)
#define ADC_CR1_DISCNUM                     (0x0000E000)
#define ADC_CR1_DISCNUM_0                   (0x00002000)
#define ADC_CR1_DISCNUM_1                   (0x00004000)
#define ADC_CR1_DISCNUM_2                   (0x00008000)
#define ADC_CR1_PDD                         (0x00010000)
#define ADC_CR1_PDI                         (0x00020000)
#define ADC_CR1_JAWDEN                      (0x00400000)
#define ADC_CR1_AWDEN                       (0x00800000)
#define ADC_CR1_RES                         (0x03000000)
#define ADC_CR1_RES_0                       (0x01000000)
#define ADC_CR1_RES_1                       (0x02000000)
#define ADC_CR1_OVRIE                       (0x04000000)

/* ADC control register 2 */
#define ADC_CR2_ADON                        (0x00000001)
#define ADC_CR2_CONT                        (0x00000002)
#define ADC_CR2_CFG                         (0x00000004)
#define ADC_CR2_DELS                        (0x00000070)
#define ADC_CR2_DELS_0                      (0x00000010)
#define ADC_CR2_DELS_1                      (0x00000020)
#define ADC_CR2_DELS_2                      (0x00000040)
#define ADC_CR2_DMA                         (0x00000100)
#define ADC_CR2_DDS                         (0x00000200)
#define ADC_CR2_EOCS                        (0x00000400)
#define ADC_CR2_ALIGN                       (0x00000800)
#define ADC_CR2_JEXTSEL                     (0x000F0000)
#define ADC_CR2_JEXTSEL_0                   (0x00010000)
#define ADC_CR2_JEXTSEL_1                   (0x00020000)
#define ADC_CR2_JEXTSEL_2                   (0x00040000)
#define ADC_CR2_JEXTSEL_3                   (0x00080000)
#define ADC_CR2_JEXTEN                      (0x00300000)
#define ADC_CR2_JEXTEN_0                    (0x00100000)
#define ADC_CR2_JEXTEN_1                    (0x00200000)
#define ADC_CR2_JSWSTART                    (0x00400000)
#define ADC_CR2_EXTSEL                      (0x0F000000)
#define ADC_CR2_EXTSEL_0                    (0x01000000)
#define ADC_CR2_EXTSEL_1                    (0x02000000)
#define ADC_CR2_EXTSEL_2                    (0x04000000)
#define ADC_CR2_EXTSEL_3                    (0x08000000)
#define ADC_CR2_EXTEN                       (0x30000000)
#define ADC_CR2_EXTEN_0                     (0x10000000)
#define ADC_CR2_EXTEN_1                     (0x20000000)
#define ADC_CR2_SWSTART                     (0x40000000)

/* ADC sample time register 1 */
#define ADC_SMPR1_SMP20                     (0x00000007)
#define ADC_SMPR1_SMP20_0                   (0x00000001)
#define ADC_SMPR1_SMP20_1                   (0x00000002)
#define ADC_SMPR1_SMP20_2                   (0x00000004)
#define ADC_SMPR1_SMP21                     (0x00000038)
#define ADC_SMPR1_SMP21_0                   (0x00000008)
#define ADC_SMPR1_SMP21_1                   (0x00000010)
#define ADC_SMPR1_SMP21_2                   (0x00000020)
#define ADC_SMPR1_SMP22                     (0x000001C0)
#define ADC_SMPR1_SMP22_0                   (0x00000040)
#define ADC_SMPR1_SMP22_1                   (0x00000080)
#define ADC_SMPR1_SMP22_2                   (0x00000100)
#define ADC_SMPR1_SMP23                     (0x00000E00)
#define ADC_SMPR1_SMP23_0                   (0x00000200)
#define ADC_SMPR1_SMP23_1                   (0x00000400)
#define ADC_SMPR1_SMP23_2                   (0x00000800)
#define ADC_SMPR1_SMP24                     (0x00007000)
#define ADC_SMPR1_SMP24_0                   (0x00001000)
#define ADC_SMPR1_SMP24_1                   (0x00002000)
#define ADC_SMPR1_SMP24_2                   (0x00004000)
#define ADC_SMPR1_SMP25                     (0x00038000)
#define ADC_SMPR1_SMP25_0                   (0x00008000)
#define ADC_SMPR1_SMP25_1                   (0x00010000)
#define ADC_SMPR1_SMP25_2                   (0x00020000)
#define ADC_SMPR1_SMP26                     (0x001C0000)
#define ADC_SMPR1_SMP26_0                   (0x00040000)
#define ADC_SMPR1_SMP26_1                   (0x00080000)
#define ADC_SMPR1_SMP26_2                   (0x00100000)
#define ADC_SMPR1_SMP27                     (0x00E00000)
#define ADC_SMPR1_SMP27_0                   (0x00200000)
#define ADC_SMPR1_SMP27_1                   (0x00400000)
#define ADC_SMPR1_SMP27_2                   (0x00800000)
#define ADC_SMPR1_SMP28                     (0x07000000)
#define ADC_SMPR1_SMP28_0                   (0x01000000)
#define ADC_SMPR1_SMP28_1                   (0x02000000)
#define ADC_SMPR1_SMP28_2                   (0x04000000)
#define ADC_SMPR1_SMP29                     (0x38000000)
#define ADC_SMPR1_SMP29_0                   (0x08000000)
#define ADC_SMPR1_SMP29_1                   (0x10000000)
#define ADC_SMPR1_SMP29_2                   (0x20000000)

/* ADC sample time register 2 */
#define ADC_SMPR2_SMP10                     (0x00000007)
#define ADC_SMPR2_SMP10_0                   (0x00000001)
#define ADC_SMPR2_SMP10_1                   (0x00000002)
#define ADC_SMPR2_SMP10_2                   (0x00000004)
#define ADC_SMPR2_SMP11                     (0x00000038)
#define ADC_SMPR2_SMP11_0                   (0x00000008)
#define ADC_SMPR2_SMP11_1                   (0x00000010)
#define ADC_SMPR2_SMP11_2                   (0x00000020)
#define ADC_SMPR2_SMP12                     (0x000001C0)
#define ADC_SMPR2_SMP12_0                   (0x00000040)
#define ADC_SMPR2_SMP12_1                   (0x00000080)
#define ADC_SMPR2_SMP12_2                   (0x00000100)
#define ADC_SMPR2_SMP13                     (0x00000E00)
#define ADC_SMPR2_SMP13_0                   (0x00000200)
#define ADC_SMPR2_SMP13_1                   (0x00000400)
#define ADC_SMPR2_SMP13_2                   (0x00000800)
#define ADC_SMPR2_SMP14                     (0x00007000)
#define ADC_SMPR2_SMP14_0                   (0x00001000)
#define ADC_SMPR2_SMP14_1                   (0x00002000)
#define ADC_SMPR2_SMP14_2                   (0x00004000)
#define ADC_SMPR2_SMP15                     (0x00038000)
#define ADC_SMPR2_SMP15_0                   (0x00008000)
#define ADC_SMPR2_SMP15_1                   (0x00010000)
#define ADC_SMPR2_SMP15_2                   (0x00020000)
#define ADC_SMPR2_SMP16                     (0x001C0000)
#define ADC_SMPR2_SMP16_0                   (0x00040000)
#define ADC_SMPR2_SMP16_1                   (0x00080000)
#define ADC_SMPR2_SMP16_2                   (0x00100000)
#define ADC_SMPR2_SMP17                     (0x00E00000)
#define ADC_SMPR2_SMP17_0                   (0x00200000)
#define ADC_SMPR2_SMP17_1                   (0x00400000)
#define ADC_SMPR2_SMP17_2                   (0x00800000)
#define ADC_SMPR2_SMP18                     (0x07000000)
#define ADC_SMPR2_SMP18_0                   (0x01000000)
#define ADC_SMPR2_SMP18_1                   (0x02000000)
#define ADC_SMPR2_SMP18_2                   (0x04000000)
#define ADC_SMPR2_SMP19                     (0x38000000)
#define ADC_SMPR2_SMP19_0                   (0x08000000)
#define ADC_SMPR2_SMP19_1                   (0x10000000)
#define ADC_SMPR2_SMP19_2                   (0x20000000)

/* ADC sample time register 3 */
#define ADC_SMPR3_SMP0                      (0x00000007)
#define ADC_SMPR3_SMP0_0                    (0x00000001)
#define ADC_SMPR3_SMP0_1                    (0x00000002)
#define ADC_SMPR3_SMP0_2                    (0x00000004)
#define ADC_SMPR3_SMP1                      (0x00000038)
#define ADC_SMPR3_SMP1_0                    (0x00000008)
#define ADC_SMPR3_SMP1_1                    (0x00000010)
#define ADC_SMPR3_SMP1_2                    (0x00000020)
#define ADC_SMPR3_SMP2                      (0x000001C0)
#define ADC_SMPR3_SMP2_0                    (0x00000040)
#define ADC_SMPR3_SMP2_1                    (0x00000080)
#define ADC_SMPR3_SMP2_2                    (0x00000100)
#define ADC_SMPR3_SMP3                      (0x00000E00)
#define ADC_SMPR3_SMP3_0                    (0x00000200)
#define ADC_SMPR3_SMP3_1                    (0x00000400)
#define ADC_SMPR3_SMP3_2                    (0x00000800)
#define ADC_SMPR3_SMP4                      (0x00007000)
#define ADC_SMPR3_SMP4_0                    (0x00001000)
#define ADC_SMPR3_SMP4_1                    (0x00002000)
#define ADC_SMPR3_SMP4_2                    (0x00004000)
#define ADC_SMPR3_SMP5                      (0x00038000)
#define ADC_SMPR3_SMP5_0                    (0x00008000)
#define ADC_SMPR3_SMP5_1                    (0x00010000)
#define ADC_SMPR3_SMP5_2                    (0x00020000)
#define ADC_SMPR3_SMP6                      (0x001C0000)
#define ADC_SMPR3_SMP6_0                    (0x00040000)
#define ADC_SMPR3_SMP6_1                    (0x00080000)
#define ADC_SMPR3_SMP6_2                    (0x00100000)
#define ADC_SMPR3_SMP7                      (0x00E00000)
#define ADC_SMPR3_SMP7_0                    (0x00200000)
#define ADC_SMPR3_SMP7_1                    (0x00400000)
#define ADC_SMPR3_SMP7_2                    (0x00800000)
#define ADC_SMPR3_SMP8                      (0x07000000)
#define ADC_SMPR3_SMP8_0                    (0x01000000)
#define ADC_SMPR3_SMP8_1                    (0x02000000)
#define ADC_SMPR3_SMP8_2                    (0x04000000)
#define ADC_SMPR3_SMP9                      (0x38000000)
#define ADC_SMPR3_SMP9_0                    (0x08000000)
#define ADC_SMPR3_SMP9_1                    (0x10000000)
#define ADC_SMPR3_SMP9_2                    (0x20000000)

/* ADC injected channeldata offset register  */
#define ADC_JOFR1_JOFFSET1                  (0x00000FFF)
#define ADC_JOFR2_JOFFSET2                  (0x00000FFF)
#define ADC_JOFR3_JOFFSET3                  (0x00000FFF)
#define ADC_JOFR4_JOFFSET4                  (0x00000FFF)
#define ADC_HTR_HT                          (0x00000FFF)
#define ADC_LTR_LT                          (0x00000FFF)

/* ADC regular sequence register */
#define ADC_SQR1_L                          (0x00F00000)
#define ADC_SQR1_L_0                        (0x00100000)
#define ADC_SQR1_L_1                        (0x00200000)
#define ADC_SQR1_L_2                        (0x00400000)
#define ADC_SQR1_L_3                        (0x00800000)
#define ADC_SQR1_SQ28                       (0x000F8000)
#define ADC_SQR1_SQ28_0                     (0x00008000)
#define ADC_SQR1_SQ28_1                     (0x00010000)
#define ADC_SQR1_SQ28_2                     (0x00020000)
#define ADC_SQR1_SQ28_3                     (0x00040000)
#define ADC_SQR1_SQ28_4                     (0x00080000)
#define ADC_SQR1_SQ27                       (0x00007C00)
#define ADC_SQR1_SQ27_0                     (0x00000400)
#define ADC_SQR1_SQ27_1                     (0x00000800)
#define ADC_SQR1_SQ27_2                     (0x00001000)
#define ADC_SQR1_SQ27_3                     (0x00002000)
#define ADC_SQR1_SQ27_4                     (0x00004000)
#define ADC_SQR1_SQ26                       (0x000003E0)
#define ADC_SQR1_SQ26_0                     (0x00000020)
#define ADC_SQR1_SQ26_1                     (0x00000040)
#define ADC_SQR1_SQ26_2                     (0x00000080)
#define ADC_SQR1_SQ26_3                     (0x00000100)
#define ADC_SQR1_SQ26_4                     (0x00000200)
#define ADC_SQR1_SQ25                       (0x0000001F)
#define ADC_SQR1_SQ25_0                     (0x00000001)
#define ADC_SQR1_SQ25_1                     (0x00000002)
#define ADC_SQR1_SQ25_2                     (0x00000004)
#define ADC_SQR1_SQ25_3                     (0x00000008)
#define ADC_SQR1_SQ25_4                     (0x00000010)

/* ADC regular sequence register */
#define ADC_SQR2_SQ19                       (0x0000001F)
#define ADC_SQR2_SQ19_0                     (0x00000001)
#define ADC_SQR2_SQ19_1                     (0x00000002)
#define ADC_SQR2_SQ19_2                     (0x00000004)
#define ADC_SQR2_SQ19_3                     (0x00000008)
#define ADC_SQR2_SQ19_4                     (0x00000010)
#define ADC_SQR2_SQ20                       (0x000003E0)
#define ADC_SQR2_SQ20_0                     (0x00000020)
#define ADC_SQR2_SQ20_1                     (0x00000040)
#define ADC_SQR2_SQ20_2                     (0x00000080)
#define ADC_SQR2_SQ20_3                     (0x00000100)
#define ADC_SQR2_SQ20_4                     (0x00000200)
#define ADC_SQR2_SQ21                       (0x00007C00)
#define ADC_SQR2_SQ21_0                     (0x00000400)
#define ADC_SQR2_SQ21_1                     (0x00000800)
#define ADC_SQR2_SQ21_2                     (0x00001000)
#define ADC_SQR2_SQ21_3                     (0x00002000)
#define ADC_SQR2_SQ21_4                     (0x00004000)
#define ADC_SQR2_SQ22                       (0x000F8000)
#define ADC_SQR2_SQ22_0                     (0x00008000)
#define ADC_SQR2_SQ22_1                     (0x00010000)
#define ADC_SQR2_SQ22_2                     (0x00020000)
#define ADC_SQR2_SQ22_3                     (0x00040000)
#define ADC_SQR2_SQ22_4                     (0x00080000)
#define ADC_SQR2_SQ23                       (0x01F00000)
#define ADC_SQR2_SQ23_0                     (0x00100000)
#define ADC_SQR2_SQ23_1                     (0x00200000)
#define ADC_SQR2_SQ23_2                     (0x00400000)
#define ADC_SQR2_SQ23_3                     (0x00800000)
#define ADC_SQR2_SQ23_4                     (0x01000000)
#define ADC_SQR2_SQ24                       (0x3E000000)
#define ADC_SQR2_SQ24_0                     (0x02000000)
#define ADC_SQR2_SQ24_1                     (0x04000000)
#define ADC_SQR2_SQ24_2                     (0x08000000)
#define ADC_SQR2_SQ24_3                     (0x10000000)
#define ADC_SQR2_SQ24_4                     (0x20000000)

/* ADC regular sequence register */
#define ADC_SQR3_SQ13                       (0x0000001F)
#define ADC_SQR3_SQ13_0                     (0x00000001)
#define ADC_SQR3_SQ13_1                     (0x00000002)
#define ADC_SQR3_SQ13_2                     (0x00000004)
#define ADC_SQR3_SQ13_3                     (0x00000008)
#define ADC_SQR3_SQ13_4                     (0x00000010)
#define ADC_SQR3_SQ14                       (0x000003E0)
#define ADC_SQR3_SQ14_0                     (0x00000020)
#define ADC_SQR3_SQ14_1                     (0x00000040)
#define ADC_SQR3_SQ14_2                     (0x00000080)
#define ADC_SQR3_SQ14_3                     (0x00000100)
#define ADC_SQR3_SQ14_4                     (0x00000200)
#define ADC_SQR3_SQ15                       (0x00007C00)
#define ADC_SQR3_SQ15_0                     (0x00000400)
#define ADC_SQR3_SQ15_1                     (0x00000800)
#define ADC_SQR3_SQ15_2                     (0x00001000)
#define ADC_SQR3_SQ15_3                     (0x00002000)
#define ADC_SQR3_SQ15_4                     (0x00004000)
#define ADC_SQR3_SQ16                       (0x000F8000)
#define ADC_SQR3_SQ16_0                     (0x00008000)
#define ADC_SQR3_SQ16_1                     (0x00010000)
#define ADC_SQR3_SQ16_2                     (0x00020000)
#define ADC_SQR3_SQ16_3                     (0x00040000)
#define ADC_SQR3_SQ16_4                     (0x00080000)
#define ADC_SQR3_SQ17                       (0x01F00000)
#define ADC_SQR3_SQ17_0                     (0x00100000)
#define ADC_SQR3_SQ17_1                     (0x00200000)
#define ADC_SQR3_SQ17_2                     (0x00400000)
#define ADC_SQR3_SQ17_3                     (0x00800000)
#define ADC_SQR3_SQ17_4                     (0x01000000)
#define ADC_SQR3_SQ18                       (0x3E000000)
#define ADC_SQR3_SQ18_0                     (0x02000000)
#define ADC_SQR3_SQ18_1                     (0x04000000)
#define ADC_SQR3_SQ18_2                     (0x08000000)
#define ADC_SQR3_SQ18_3                     (0x10000000)
#define ADC_SQR3_SQ18_4                     (0x20000000)

/* ADC regular sequence register */
#define ADC_SQR4_SQ7                        (0x0000001F)
#define ADC_SQR4_SQ7_0                      (0x00000001)
#define ADC_SQR4_SQ7_1                      (0x00000002)
#define ADC_SQR4_SQ7_2                      (0x00000004)
#define ADC_SQR4_SQ7_3                      (0x00000008)
#define ADC_SQR4_SQ7_4                      (0x00000010)
#define ADC_SQR4_SQ8                        (0x000003E0)
#define ADC_SQR4_SQ8_0                      (0x00000020)
#define ADC_SQR4_SQ8_1                      (0x00000040)
#define ADC_SQR4_SQ8_2                      (0x00000080)
#define ADC_SQR4_SQ8_3                      (0x00000100)
#define ADC_SQR4_SQ8_4                      (0x00000200)
#define ADC_SQR4_SQ9                        (0x00007C00)
#define ADC_SQR4_SQ9_0                      (0x00000400)
#define ADC_SQR4_SQ9_1                      (0x00000800)
#define ADC_SQR4_SQ9_2                      (0x00001000)
#define ADC_SQR4_SQ9_3                      (0x00002000)
#define ADC_SQR4_SQ9_4                      (0x00004000)
#define ADC_SQR4_SQ10                       (0x000F8000)
#define ADC_SQR4_SQ10_0                     (0x00008000)
#define ADC_SQR4_SQ10_1                     (0x00010000)
#define ADC_SQR4_SQ10_2                     (0x00020000)
#define ADC_SQR4_SQ10_3                     (0x00040000)
#define ADC_SQR4_SQ10_4                     (0x00080000)
#define ADC_SQR4_SQ11                       (0x01F00000)
#define ADC_SQR4_SQ11_0                     (0x00100000)
#define ADC_SQR4_SQ11_1                     (0x00200000)
#define ADC_SQR4_SQ11_2                     (0x00400000)
#define ADC_SQR4_SQ11_3                     (0x00800000)
#define ADC_SQR4_SQ11_4                     (0x01000000)
#define ADC_SQR4_SQ12                       (0x3E000000)
#define ADC_SQR4_SQ12_0                     (0x02000000)
#define ADC_SQR4_SQ12_1                     (0x04000000)
#define ADC_SQR4_SQ12_2                     (0x08000000)
#define ADC_SQR4_SQ12_3                     (0x10000000)
#define ADC_SQR4_SQ12_4                     (0x20000000)

/* ADC regular sequence register */
#define ADC_SQR5_SQ1                        (0x0000001F)
#define ADC_SQR5_SQ1_0                      (0x00000001)
#define ADC_SQR5_SQ1_1                      (0x00000002)
#define ADC_SQR5_SQ1_2                      (0x00000004)
#define ADC_SQR5_SQ1_3                      (0x00000008)
#define ADC_SQR5_SQ1_4                      (0x00000010)
#define ADC_SQR5_SQ2                        (0x000003E0)
#define ADC_SQR5_SQ2_0                      (0x00000020)
#define ADC_SQR5_SQ2_1                      (0x00000040)
#define ADC_SQR5_SQ2_2                      (0x00000080)
#define ADC_SQR5_SQ2_3                      (0x00000100)
#define ADC_SQR5_SQ2_4                      (0x00000200)
#define ADC_SQR5_SQ3                        (0x00007C00)
#define ADC_SQR5_SQ3_0                      (0x00000400)
#define ADC_SQR5_SQ3_1                      (0x00000800)
#define ADC_SQR5_SQ3_2                      (0x00001000)
#define ADC_SQR5_SQ3_3                      (0x00002000)
#define ADC_SQR5_SQ3_4                      (0x00004000)
#define ADC_SQR5_SQ4                        (0x000F8000)
#define ADC_SQR5_SQ4_0                      (0x00008000)
#define ADC_SQR5_SQ4_1                      (0x00010000)
#define ADC_SQR5_SQ4_2                      (0x00020000)
#define ADC_SQR5_SQ4_3                      (0x00040000)
#define ADC_SQR5_SQ4_4                      (0x00080000)
#define ADC_SQR5_SQ5                        (0x01F00000)
#define ADC_SQR5_SQ5_0                      (0x00100000)
#define ADC_SQR5_SQ5_1                      (0x00200000)
#define ADC_SQR5_SQ5_2                      (0x00400000)
#define ADC_SQR5_SQ5_3                      (0x00800000)
#define ADC_SQR5_SQ5_4                      (0x01000000)
#define ADC_SQR5_SQ6                        (0x3E000000)
#define ADC_SQR5_SQ6_0                      (0x02000000)
#define ADC_SQR5_SQ6_1                      (0x04000000)
#define ADC_SQR5_SQ6_2                      (0x08000000)
#define ADC_SQR5_SQ6_3                      (0x10000000)
#define ADC_SQR5_SQ6_4                      (0x20000000)

/* ADC injected sequence register */
#define ADC_JSQR_JSQ1                       (0x0000001F)
#define ADC_JSQR_JSQ1_0                     (0x00000001)
#define ADC_JSQR_JSQ1_1                     (0x00000002)
#define ADC_JSQR_JSQ1_2                     (0x00000004)
#define ADC_JSQR_JSQ1_3                     (0x00000008)
#define ADC_JSQR_JSQ1_4                     (0x00000010)
#define ADC_JSQR_JSQ2                       (0x000003E0)
#define ADC_JSQR_JSQ2_0                     (0x00000020)
#define ADC_JSQR_JSQ2_1                     (0x00000040)
#define ADC_JSQR_JSQ2_2                     (0x00000080)
#define ADC_JSQR_JSQ2_3                     (0x00000100)
#define ADC_JSQR_JSQ2_4                     (0x00000200)
#define ADC_JSQR_JSQ3                       (0x00007C00)
#define ADC_JSQR_JSQ3_0                     (0x00000400)
#define ADC_JSQR_JSQ3_1                     (0x00000800)
#define ADC_JSQR_JSQ3_2                     (0x00001000)
#define ADC_JSQR_JSQ3_3                     (0x00002000)
#define ADC_JSQR_JSQ3_4                     (0x00004000)
#define ADC_JSQR_JSQ4                       (0x000F8000)
#define ADC_JSQR_JSQ4_0                     (0x00008000)
#define ADC_JSQR_JSQ4_1                     (0x00010000)
#define ADC_JSQR_JSQ4_2                     (0x00020000)
#define ADC_JSQR_JSQ4_3                     (0x00040000)
#define ADC_JSQR_JSQ4_4                     (0x00080000)
#define ADC_JSQR_JL                         (0x00300000)
#define ADC_JSQR_JL_0                       (0x00100000)
#define ADC_JSQR_JL_1                       (0x00200000)

/* ADC injected data register x */
#define ADC_JDR1_JDATA                      (0x0000FFFF)
#define ADC_JDR2_JDATA                      (0x0000FFFF)
#define ADC_JDR3_JDATA                      (0x0000FFFF)
#define ADC_JDR4_JDATA                      (0x0000FFFF)

/* ADC regular data register */
#define ADC_DR_DATA                         (0x0000FFFF)

/* ADC common status register */
#define ADC_CSR_AWD1                        (0x00000001)
#define ADC_CSR_EOC1                        (0x00000002)
#define ADC_CSR_JEOC1                       (0x00000004)
#define ADC_CSR_JSTRT1                      (0x00000008)
#define ADC_CSR_STRT1                       (0x00000010)
#define ADC_CSR_OVR1                        (0x00000020)
#define ADC_CSR_ADONS1                      (0x00000040)

/* ADC common control register */
#define ADC_CCR_ADCPRE                      (0x00030000)
#define ADC_CCR_ADCPRE_0                    (0x00010000)
#define ADC_CCR_ADCPRE_1                    (0x00020000)
#define ADC_CCR_TSVREFE                     (0x00800000)

/* common registers */
typedef struct {
	reg32_t CSR;
	reg32_t CCR;
} adc_com_t;

/* init struct */
typedef struct {
	uint32_t 	resolution;
	int			scan_conv_mode;
	int 		continuous_conv_mode;
	uint32_t	external_trig_conv_edge;
	uint32_t 	external_trig_conv;
	uint32_t 	data_align;
	uint8_t  	conversion_num;
} adc_init_t;

/* resolution */
#define ADC_RESOLUTION_12b                  (0x00000000)
#define ADC_RESOLUTION_10b                  (0x01000000)
#define ADC_RESOLUTION_8b                   (0x02000000)
#define ADC_RESOLUTION_6b                   (0x03000000)

/* external trigger edge  */
#define ADC_EXTTRIGCONVEDGE_NONE            (0x00000000)
#define ADC_EXTTRIGCONVEDGE_RISING          (0x10000000)
#define ADC_EXTTRIGCONVEDGE_FALLING         (0x20000000)
#define ADC_EXTTRIGCONVEDGE_RISINGFALLING   (0x30000000)

/* external trigger source  */
#define ADC_EXTTRIGCONV_T2_CC3         		(0x02000000)
#define ADC_EXTTRIGCONV_T2_CC2              (0x03000000)
#define ADC_EXTTRIGCONV_T2_TRGO        		(0x06000000)
#define ADC_EXTTRIGCONV_T3_CC1              (0x07000000)
#define ADC_EXTTRIGCONV_T3_CC3              (0x08000000)
#define ADC_EXTTRIGCONV_T3_TRGO             (0x04000000)
#define ADC_EXTTRIGCONV_T4_CC4              (0x05000000)
#define ADC_EXTTRIGCONV_T4_TRGO             (0x09000000)
#define ADC_EXTTRIGCONV_T6_TRGO             (0x0A000000)
#define ADC_EXTTRIGCONV_T9_CC2              (0x00000000)
#define ADC_EXTTRIGCONV_T9_TRGO             (0x01000000)
#define ADC_EXTTRIGCONV_EXT_IT11            (0x0F000000)

/* data align */
#define ADC_DATAALIGN_RIGHT                 (0x00000000)
#define ADC_DATAALIGN_LEFT                  (0x00000800)

/* init struct */
typedef struct {
	uint32_t 	prescaler;
} adc_init_com_t;

/* prescaler */
#define ADC_PRESCALER_DIV1                  (0x00000000)
#define ADC_PRESCALER_DIV2                  (0x00010000)
#define ADC_PRESCALER_DIV4                  (0x00020000)

/* banks */
#define ADC_BANK_A                          (0x00)
#define ADC_BANK_B                          (0x01)

/* adc channels */
#define ADC_C0								(0x00)
#define ADC_C1								(0x01)
#define ADC_C2								(0x02)
#define ADC_C3								(0x03)
#define ADC_C4								(0x04)
#define ADC_C5								(0x05)
#define ADC_C6								(0x06)
#define ADC_C7								(0x07)
#define ADC_C8								(0x08)
#define ADC_C9								(0x09)
#define ADC_C10								(0x0a)
#define ADC_C11								(0x0b)
#define ADC_C12								(0x0c)
#define ADC_C13								(0x0d)
#define ADC_C14								(0x0e)
#define ADC_C15								(0x0f)
#define ADC_C16								(0x10)
#define ADC_C17								(0x11)
#define ADC_C18								(0x12)
#define ADC_C19								(0x13)
#define ADC_C20								(0x14)
#define ADC_C21								(0x15)
#define ADC_C22								(0x16)
#define ADC_C23								(0x17)
#define ADC_C24								(0x18)
#define ADC_C25								(0x19)
#define ADC_C26								(0x1a)
#define ADC_C27								(0x1b)
#define ADC_C28								(0x1c)
#define ADC_C29								(0x1d)
#define ADC_C30								(0x1e)
#define ADC_C31								(0x1f)

/* sample time */
#define ADC_SAMPLETIME_4C                   (0x00)
#define ADC_SAMPLETIME_9C                   (0x01)
#define ADC_SAMPLETIME_16C                  (0x02)
#define ADC_SAMPLETIME_24C                  (0x03)
#define ADC_SAMPLETIME_48C                  (0x04)
#define ADC_SAMPLETIME_96C                  (0x05)
#define ADC_SAMPLETIME_192C                 (0x06)
#define ADC_SAMPLETIME_384C                 (0x07)

/* initilize adc */
void ADC_Init(adc_t *ADCx, adc_init_t *init);
/* initialize structure */
void ADC_StructInit(adc_init_t *init);
/* initialize common registers */
void ADC_CommonInit(adc_init_com_t *init);
/* init struct */
void ADC_CommonStructInit(adc_init_com_t *init);
/* command */
void ADC_Cmd(adc_t *ADCx, int state);
/* get status flags */
uint32_t ADC_GetStatus(adc_t *ADCx);
/* configure regular channel */
void ADC_RegularChannelConfig(adc_t *ADCx, uint8_t channel, uint8_t rank,
		uint8_t sample_time);
/* start software conversion */
void ADC_SoftwareStartConv(adc_t *ADCx);
/* get conversion status */
int ADC_GetSoftwareStartConvStatus(adc_t *ADCx);
/* get conversion value */
uint16_t ADC_GetConversionValue(adc_t *ADCx);
/* enable internal reference and temperature sensor */
void ADC_TempSensorVrefintCmd(int state);


#endif /* STM32_ADC_H_ */

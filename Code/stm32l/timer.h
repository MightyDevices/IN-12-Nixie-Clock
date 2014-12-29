/*
 * stm32_timer.h
 *
 *  Created on: 21-06-2012
 *      Author: Tomek
 */

#ifndef STM32L_TIMER_H_
#define STM32L_TIMER_H_

#include <stm32l/stm32l.h>

/* register base */
#define TIM2_BASE						0x40000000
#define TIM3_BASE						0x40000400
#define TIM4_BASE						0x40000800
#define TIM5_BASE						0x40000C00
#define TIM6_BASE						0x40001000
#define TIM7_BASE						0x40001400
#define TIM9_BASE						0x40010800
#define TIM10_BASE						0x40010C00
#define TIM11_BASE						0x40011000

/* timers */
#define TIM2							((tim_t *)TIM2_BASE)
#define TIM3							((tim_t *)TIM3_BASE)
#define TIM4							((tim_t *)TIM4_BASE)
#define TIM5							((tim_t *)TIM5_BASE)
#define TIM6							((tim_t *)TIM6_BASE)
#define TIM7							((tim_t *)TIM7_BASE)
#define TIM9							((tim_t *)TIM9_BASE)
#define TIM10							((tim_t *)TIM10_BASE)
#define TIM11							((tim_t *)TIM11_BASE)

/* timer */
typedef struct {
	reg16_t CR1;
	reg16_t RESERVED0;
	reg16_t CR2;
	reg16_t RESERVED1;
	reg16_t SMCR;
	reg16_t RESERVED2;
	reg16_t DIER;
	reg16_t RESERVED3;
	reg16_t SR;
	reg16_t RESERVED4;
	reg16_t EGR;
	reg16_t RESERVED5;
	reg16_t CCMR1;
	reg16_t RESERVED6;
	reg16_t CCMR2;
	reg16_t RESERVED7;
	reg16_t CCER;
	reg16_t RESERVED8;
	reg32_t CNT;
	reg16_t PSC;
	reg16_t RESERVED10;
	reg32_t ARR;
	reg32_t RESERVED12;
	reg32_t CCR1;
	reg32_t CCR2;
	reg32_t CCR3;
	reg32_t CCR4;
	reg32_t RESERVED17;
	reg16_t DCR;
	reg16_t RESERVED18;
	reg16_t DMAR;
	reg16_t RESERVED19;
	reg16_t OR;
	reg16_t RESERVED20;
} tim_t;

/* TIMx control register 1 */
#define TIM_CR1_CEN                         (0x0001)
#define TIM_CR1_UDIS                        (0x0002)
#define TIM_CR1_URS                         (0x0004)
#define TIM_CR1_OPM                         (0x0008)
#define TIM_CR1_DIR                         (0x0010)
#define TIM_CR1_CMS                         (0x0060)
#define TIM_CR1_CMS_0                       (0x0020)
#define TIM_CR1_CMS_1                       (0x0040)
#define TIM_CR1_ARPE                        (0x0080)
#define TIM_CR1_CKD                         (0x0300)
#define TIM_CR1_CKD_0                       (0x0100)
#define TIM_CR1_CKD_1                       (0x0200)

/* TIMx control register 2 */
#define TIM_CR2_CCDS                        (0x0008)
#define TIM_CR2_MMS                         (0x0070)
#define TIM_CR2_MMS_0                       (0x0010)
#define TIM_CR2_MMS_1                       (0x0020)
#define TIM_CR2_MMS_2                       (0x0040)
#define TIM_CR2_TI1S                        (0x0080)

/* TIMx slave mode control register */
#define TIM_SMCR_SMS                        (0x0007)
#define TIM_SMCR_SMS_0                      (0x0001)
#define TIM_SMCR_SMS_1                      (0x0002)
#define TIM_SMCR_SMS_2                      (0x0004)
#define TIM_SMCR_OCCS                       (0x0008)
#define TIM_SMCR_TS                         (0x0070)
#define TIM_SMCR_TS_0                       (0x0010)
#define TIM_SMCR_TS_1                       (0x0020)
#define TIM_SMCR_TS_2                       (0x0040)
#define TIM_SMCR_MSM                        (0x0080)
#define TIM_SMCR_ETF                        (0x0F00)
#define TIM_SMCR_ETF_0                      (0x0100)
#define TIM_SMCR_ETF_1                      (0x0200)
#define TIM_SMCR_ETF_2                      (0x0400)
#define TIM_SMCR_ETF_3                      (0x0800)
#define TIM_SMCR_ETPS                       (0x3000)
#define TIM_SMCR_ETPS_0                     (0x1000)
#define TIM_SMCR_ETPS_1                     (0x2000)
#define TIM_SMCR_ECE                        (0x4000)
#define TIM_SMCR_ETP                        (0x8000)

/* TIMx DMA/Interrupt enable register */
#define TIM_DIER_UIE                        (0x0001)
#define TIM_DIER_CC1IE                      (0x0002)
#define TIM_DIER_CC2IE                      (0x0004)
#define TIM_DIER_CC3IE                      (0x0008)
#define TIM_DIER_CC4IE                      (0x0010)
#define TIM_DIER_TIE                        (0x0040)
#define TIM_DIER_UDE                        (0x0100)
#define TIM_DIER_CC1DE                      (0x0200)
#define TIM_DIER_CC2DE                      (0x0400)
#define TIM_DIER_CC3DE                      (0x0800)
#define TIM_DIER_CC4DE                      (0x1000)
#define TIM_DIER_TDE                        (0x4000)

/* TIMx status register */
#define TIM_SR_UIF                          (0x0001)
#define TIM_SR_CC1IF                        (0x0002)
#define TIM_SR_CC2IF                        (0x0004)
#define TIM_SR_CC3IF                        (0x0008)
#define TIM_SR_CC4IF                        (0x0010)
#define TIM_SR_TIF                          (0x0040)
#define TIM_SR_CC1OF                        (0x0200)
#define TIM_SR_CC2OF                        (0x0400)
#define TIM_SR_CC3OF                        (0x0800)
#define TIM_SR_CC4OF                        (0x1000)

/* TIMx event generation register */
#define TIM_EGR_UG                          (0x01)
#define TIM_EGR_CC1G                        (0x02)
#define TIM_EGR_CC2G                        (0x04)
#define TIM_EGR_CC3G                        (0x08)
#define TIM_EGR_CC4G                        (0x10)
#define TIM_EGR_TG                          (0x40)

/* TIMx capture/compare mode register 1 */
#define TIM_CCMR1_CC1S                      (0x0003)
#define TIM_CCMR1_CC1S_0                    (0x0001)
#define TIM_CCMR1_CC1S_1                    (0x0002)
#define TIM_CCMR1_OC1FE                     (0x0004)
#define TIM_CCMR1_OC1PE                     (0x0008)
#define TIM_CCMR1_OC1M                      (0x0070)
#define TIM_CCMR1_OC1M_0                    (0x0010)
#define TIM_CCMR1_OC1M_1                    (0x0020)
#define TIM_CCMR1_OC1M_2                    (0x0040)
#define TIM_CCMR1_OC1CE                     (0x0080)
#define TIM_CCMR1_CC2S                      (0x0300)
#define TIM_CCMR1_CC2S_0                    (0x0100)
#define TIM_CCMR1_CC2S_1                    (0x0200)
#define TIM_CCMR1_OC2FE                     (0x0400)
#define TIM_CCMR1_OC2PE                     (0x0800)
#define TIM_CCMR1_OC2M                      (0x7000)
#define TIM_CCMR1_OC2M_0                    (0x1000)
#define TIM_CCMR1_OC2M_1                    (0x2000)
#define TIM_CCMR1_OC2M_2                    (0x4000)
#define TIM_CCMR1_OC2CE                     (0x8000)
#define TIM_CCMR1_IC1PSC                    (0x000C)
#define TIM_CCMR1_IC1PSC_0                  (0x0004)
#define TIM_CCMR1_IC1PSC_1                  (0x0008)
#define TIM_CCMR1_IC1F                      (0x00F0)
#define TIM_CCMR1_IC1F_0                    (0x0010)
#define TIM_CCMR1_IC1F_1                    (0x0020)
#define TIM_CCMR1_IC1F_2                    (0x0040)
#define TIM_CCMR1_IC1F_3                    (0x0080)
#define TIM_CCMR1_IC2PSC                    (0x0C00)
#define TIM_CCMR1_IC2PSC_0                  (0x0400)
#define TIM_CCMR1_IC2PSC_1                  (0x0800)
#define TIM_CCMR1_IC2F                      (0xF000)
#define TIM_CCMR1_IC2F_0                    (0x1000)
#define TIM_CCMR1_IC2F_1                    (0x2000)
#define TIM_CCMR1_IC2F_2                    (0x4000)
#define TIM_CCMR1_IC2F_3                    (0x8000)

/* TIMx capture/compare mode register 2 */
#define TIM_CCMR2_CC3S                      (0x0003)
#define TIM_CCMR2_CC3S_0                    (0x0001)
#define TIM_CCMR2_CC3S_1                    (0x0002)
#define TIM_CCMR2_OC3FE                     (0x0004)
#define TIM_CCMR2_OC3PE                     (0x0008)
#define TIM_CCMR2_OC3M                      (0x0070)
#define TIM_CCMR2_OC3M_0                    (0x0010)
#define TIM_CCMR2_OC3M_1                    (0x0020)
#define TIM_CCMR2_OC3M_2                    (0x0040)
#define TIM_CCMR2_OC3CE                     (0x0080)
#define TIM_CCMR2_CC4S                      (0x0300)
#define TIM_CCMR2_CC4S_0                    (0x0100)
#define TIM_CCMR2_CC4S_1                    (0x0200)
#define TIM_CCMR2_OC4FE                     (0x0400)
#define TIM_CCMR2_OC4PE                     (0x0800)
#define TIM_CCMR2_OC4M                      (0x7000)
#define TIM_CCMR2_OC4M_0                    (0x1000)
#define TIM_CCMR2_OC4M_1                    (0x2000)
#define TIM_CCMR2_OC4M_2                    (0x4000)
#define TIM_CCMR2_OC4CE                     (0x8000)
#define TIM_CCMR2_IC3PSC                    (0x000C)
#define TIM_CCMR2_IC3PSC_0                  (0x0004)
#define TIM_CCMR2_IC3PSC_1                  (0x0008)
#define TIM_CCMR2_IC3F                      (0x00F0)
#define TIM_CCMR2_IC3F_0                    (0x0010)
#define TIM_CCMR2_IC3F_1                    (0x0020)
#define TIM_CCMR2_IC3F_2                    (0x0040)
#define TIM_CCMR2_IC3F_3                    (0x0080)
#define TIM_CCMR2_IC4PSC                    (0x0C00)
#define TIM_CCMR2_IC4PSC_0                  (0x0400)
#define TIM_CCMR2_IC4PSC_1                  (0x0800)
#define TIM_CCMR2_IC4F                      (0xF000)
#define TIM_CCMR2_IC4F_0                    (0x1000)
#define TIM_CCMR2_IC4F_1                    (0x2000)
#define TIM_CCMR2_IC4F_2                    (0x4000)
#define TIM_CCMR2_IC4F_3                    (0x8000)

/* TIMx capture/compare enable register */
#define TIM_CCER_CC1E                       (0x0001)
#define TIM_CCER_CC1P                       (0x0002)
#define TIM_CCER_CC1NP                      (0x0008)
#define TIM_CCER_CC2E                       (0x0010)
#define TIM_CCER_CC2P                       (0x0020)
#define TIM_CCER_CC2NP                      (0x0080)
#define TIM_CCER_CC3E                       (0x0100)
#define TIM_CCER_CC3P                       (0x0200)
#define TIM_CCER_CC3NP                      (0x0800)
#define TIM_CCER_CC4E                       (0x1000)
#define TIM_CCER_CC4P                       (0x2000)
#define TIM_CCER_CC4NP                      (0x8000)

/* TIMx counter */
#define TIM_CNT_CNT                         (0xFFFF)

/* TIMx prescaler */
#define TIM_PSC_PSC                         (0xFFFF)

/* TIMx auto-rel oad register */
#define TIM_ARR_ARR                         (0xFFFF)

/* TIMx capture/compare register 1 */
#define TIM_CCR1_CCR1                       (0xFFFF)

/* TIMx capture/compare register 2 */
#define TIM_CCR2_CCR2                       (0xFFFF)

/* TIMx capture/compare register 3 */
#define TIM_CCR3_CCR3                       (0xFFFF)

/* TIMx capture/compare register 4 */
#define TIM_CCR4_CCR4                       (0xFFFF)

/* TIMx DMA cont rol register */
#define TIM_DCR_DBA                         (0x001F)
#define TIM_DCR_DBA_0                       (0x0001)
#define TIM_DCR_DBA_1                       (0x0002)
#define TIM_DCR_DBA_2                       (0x0004)
#define TIM_DCR_DBA_3                       (0x0008)
#define TIM_DCR_DBA_4                       (0x0010)
#define TIM_DCR_DBL                         (0x1F00)
#define TIM_DCR_DBL_0                       (0x0100)
#define TIM_DCR_DBL_1                       (0x0200)
#define TIM_DCR_DBL_2                       (0x0400)
#define TIM_DCR_DBL_3                       (0x0800)
#define TIM_DCR_DBL_4                       (0x1000)

/* TIMx DMA address for full transfer */
#define TIM_DMAR_DMAB                       (0xFFFF)

/* TIMx option register */
#define TIM_OR_TI1RMP                       (0x0003)
#define TIM_OR_TI1RMP_0                     (0x0001)
#define TIM_OR_TI1RMP_1                     (0x0002)

/* timer base init */
typedef struct {
	uint16_t prescaler;
	uint16_t counter_mode;
	uint32_t period;
	uint16_t clock_division;
} tim_tbase_init_t;

/* couter modes */
#define TIM_COUNTERMODE_UP                 (0x0000)
#define TIM_COUNTERMODE_DOWN               (0x0010)
#define TIM_COUNTERMODE_CENTERALIGNED1     (0x0020)
#define TIM_COUNTERMODE_CENTERALIGNED2     (0x0040)
#define TIM_COUNTERMODE_CENTERALIGNED3     (0x0060)

/* clock division */
#define TIM_CKD_DIV1                       (0x0000)
#define TIM_CKD_DIV2                       (0x0100)
#define TIM_CKD_DIV4                       (0x0200)

/* output compare mode */
typedef struct {
	uint16_t oc_mode;
	uint16_t output_state;
	uint32_t pulse;
	uint16_t oc_polarity;
} tim_oc_init_t;

/* oc mode */
#define TIM_OCMODE_TIMING                  (0x0000)
#define TIM_OCMODE_ACTIVE                  (0x0010)
#define TIM_OCMODE_INACTIVE                (0x0020)
#define TIM_OCMODE_TOGGLE                  (0x0030)
#define TIM_OCMODE_PWM1                    (0x0060)
#define TIM_OCMODE_PWM2                    (0x0070)

/* output state */
#define TIM_OUTPUTSTATE_DISABLE            (0x0000)
#define TIM_OUTPUTSTATE_ENABLE             (0x0001)

/* oc polarity */
#define TIM_OCPOLARITY_HIGH                (0x0000)
#define TIM_OCPOLARITY_LOW                 (0x0002)

/* tim channel */
#define TIM_CHANNEL_1                      (0x0000)
#define TIM_CHANNEL_2                      (0x0004)
#define TIM_CHANNEL_3                      (0x0008)
#define TIM_CHANNEL_4                      (0x000C)

/* interrupts*/
#define TIM_INT_UIE						   (0x0001)

/* trigger source */
#define TIM_TS_ITR0                        ((uint16_t)0x0000)
#define TIM_TS_ITR1                        ((uint16_t)0x0010)
#define TIM_TS_ITR2                        ((uint16_t)0x0020)
#define TIM_TS_ITR3                        ((uint16_t)0x0030)
#define TIM_TS_TI1F_ED                     ((uint16_t)0x0040)
#define TIM_TS_TI1FP1                      ((uint16_t)0x0050)
#define TIM_TS_TI2FP2                      ((uint16_t)0x0060)
#define TIM_TS_ETRF                        ((uint16_t)0x0070)

/* output source */
#define TIM_TRGOSOURCE_RESET               ((uint16_t)0x0000)
#define TIM_TRGOSOURCE_ENABLE              ((uint16_t)0x0010)
#define TIM_TRGOSOURCE_UPDATE              ((uint16_t)0x0020)
#define TIM_TRGOSOURCE_OC1                 ((uint16_t)0x0030)
#define TIM_TRGOSOURCE_OC1REF              ((uint16_t)0x0040)
#define TIM_TRGOSOURCE_OC2REF              ((uint16_t)0x0050)
#define TIM_TRGOSOURCE_OC3REF              ((uint16_t)0x0060)
#define TIM_TRGOSOURCE_OC4REF              ((uint16_t)0x0070)

/* slave modes */
#define TIM_SLAVEMODE_RESET                ((uint16_t)0x0004)
#define TIM_SLAVEMODE_GATED                ((uint16_t)0x0005)
#define TIM_SLAVEMODE_TRIGGER              ((uint16_t)0x0006)
#define TIM_SLAVEMODE_EXTERNAL1            ((uint16_t)0x0007)

/* slave master modes */
#define TIM_MASTERSLAVEMODE_ENABLE         ((uint16_t)0x0080)
#define TIM_MASTERSLAVEMODE_DISABLE        ((uint16_t)0x0000)

/* prescaler reload mode */
#define TIM_PSCRELOADMODE_UPDATE           ((uint16_t)0x0000)
#define TIM_PSCRELOADMODE_IMMEDIATE        ((uint16_t)0x0001)

/* initialize time base */
void TIM_TimeBaseInit(tim_t *TIMx, tim_tbase_init_t *init);
/* initialize time base struct */
void TIM_TimeBaseStructInit(tim_tbase_init_t *init);
/* set counter value */
void TIM_SetCounter(tim_t *TIMx, uint32_t counter);
/* set autoreload register */
void TIM_SetAutoreload(tim_t *TIMx, uint32_t autoreload);
/* enable disable timer */
void TIM_Cmd(tim_t *TIMx, int state);
/* enable disable one pulse mode */
void TIM_ConfigureOnePulse(tim_t* TIMx, int state);
/* enable disable interrupts */
void TIM_ConfigureInterrupt(tim_t *TIMx, int state, uint16_t interrupt);
/* output compare init (channel 1) */
void TIM_OC1Init(tim_t *TIMx, tim_oc_init_t *init);
/* output compare init (channel 2) */
void TIM_OC2Init(tim_t *TIMx, tim_oc_init_t *init);
/* output compare init (channel 3) */
void TIM_OC3Init(tim_t *TIMx, tim_oc_init_t *init);
/* output compare init (channel 4) */
void TIM_OC4Init(tim_t *TIMx, tim_oc_init_t *init);
/* initialize struct */
void TIM_OCStructInit(tim_oc_init_t *init);
/* select output compare */
void TIM_SelectOCxM(tim_t *TIMx, int TIM_Channel, int TIM_OCMode);
/* set compare1 */
void TIM_SetCompare1(tim_t *TIMx, uint32_t Compare1);
/* set compare2 */
void TIM_SetCompare2(tim_t *TIMx, uint32_t Compare2);
/* set compare3 */
void TIM_SetCompare3(tim_t *TIMx, uint32_t Compare3);
/* set compare4 */
void TIM_SetCompare4(tim_t *TIMx, uint32_t Compare4);
/* select input trigger */
void TIM_SelectInputTrigger(tim_t * TIMx, uint16_t source);
/* select output trigger */
void TIM_SelectOutputTrigger(tim_t *TIMx, uint16_t source);
/* slave mode select */
void TIM_SelectSlaveMode(tim_t *TIMx, uint16_t slave_mode);
/* master slave mode select */
void TIM_SelectMasterSlaveMode(tim_t *TIMx, uint16_t mode);
/* configure external trigger */
void TIM_ETRConfig(tim_t *TIMx, uint16_t prescaler, uint16_t polarity,
                   uint16_t filter);
/* remap */
void TIM_RemapConfig(tim_t *TIMx, uint16_t remap);
/* prescaler update */
void TIM_PrescalerConfig(tim_t* TIMx, uint16_t pres, uint16_t reload_mode);


#endif /* STM32_TIMER_H_ */

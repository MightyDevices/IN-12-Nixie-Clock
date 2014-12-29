/*
 * stm32_timer.c
 *
 *  Created on: 21-06-2012
 *      Author: Tomek
 */


#include <stm32l/timer.h>

/* initialize time base */
void TIM_TimeBaseInit(tim_t *TIMx, tim_tbase_init_t *init)
{
	uint16_t tmpcr1 = 0;

	if ((TIMx == TIM2) || (TIMx == TIM3) ||
		(TIMx == TIM4) || (TIMx == TIM5)) {
		/* Select the Counter Mode */
		tmpcr1 &= (uint16_t)(~((uint16_t)(0x0070)));
		tmpcr1 |= (uint32_t)init->counter_mode;
	}

	if((TIMx != TIM6) && (TIMx != TIM7)) {
		/* Set the clock division */
		tmpcr1 &= (uint16_t)(~((uint16_t)0x0300));
		tmpcr1 |= (uint32_t)init->clock_division;
	}

	TIMx->CR1 = tmpcr1;

	/* Set the Autoreload value */
	TIMx->ARR = init->period ;

	/* Set the Prescaler value */
	TIMx->PSC = init->prescaler;

	/* Generate an update event to reload the Prescaler value immediatly */
	TIMx->EGR = 0x1;
}

/* initialize time base struct */
void TIM_TimeBaseStructInit(tim_tbase_init_t* init)
{
	/* Set the default configuration */
	init->period = 0xFFFFFFFF;
	init->prescaler = 0x0000;
	init->clock_division = TIM_CKD_DIV1;
	init->counter_mode = TIM_COUNTERMODE_UP;
}

/* set counter value */
void TIM_SetCounter(tim_t* TIMx, uint32_t counter)
{
	/* Set the Counter Register value */
	TIMx->CNT = counter;
}

/* set autoreload register */
void TIM_SetAutoreload(tim_t* TIMx, uint32_t autoreload)
{
	/* Set the Autoreload Register value */
	TIMx->ARR = autoreload;
}

/* enable disable timer */
void TIM_Cmd(tim_t* TIMx, int state)
{
	if (state) {
		/* Enable the TIM Counter */
		TIMx->CR1 |= 0x1;
	} else {
		/* Disable the TIM Counter */
		TIMx->CR1 &= ~TIM_CR1_CEN;
	}
}

/* enable disable one pulse mode */
void TIM_ConfigureOnePulse(tim_t* TIMx, int state)
{
	if (state) {
		/* Enable the TIM Counter */
		TIMx->CR1 |= TIM_CR1_OPM;
	} else {
		/* Disable the TIM Counter */
		TIMx->CR1 &= ~TIM_CR1_OPM;
	}
}

/* enable disable interrupts */
void TIM_ConfigureInterrupt(tim_t* TIMx, int state, uint16_t interrupt)
{
	if (state) {
		/* Enable the TIM Counter */
		TIMx->DIER |= interrupt;
	} else {
		/* Disable the TIM Counter */
		TIMx->DIER &= (uint16_t)(~((uint16_t)interrupt));
	}
}

/* output compare init (channel 1) */
void TIM_OC1Init(tim_t* TIMx, tim_oc_init_t *init)
{
	uint16_t tmpccmrx = 0, tmpccer = 0;

	/* Disable the Channel 1: Reset the CC1E Bit */
	TIMx->CCER &= (uint16_t)(~(uint16_t)0x0001);

	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;

	/* Get the TIMx CCMR1 register value */
	tmpccmrx = TIMx->CCMR1;

	/* Reset the Output Compare Mode Bits */
	tmpccmrx &= (uint16_t)(~((uint16_t)0x0070));
	tmpccmrx &= (uint16_t)(~((uint16_t)0x0002));

	/* Select the Output Compare Mode */
	tmpccmrx |= init->oc_mode;

	/* Reset the Output Polarity level */
	tmpccer &= (uint16_t)(~((uint16_t)0x0020));
	/* Set the Output Compare Polarity */
	tmpccer |= init->oc_polarity;

	/* Set the Output State */
	tmpccer |= init->output_state;

	/* Set the Capture Compare Register value */
	TIMx->CCR1 = init->pulse;

	/* Write to TIMx CCMR1 */
	TIMx->CCMR1 = tmpccmrx;

	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/* output compare init (channel 2) */
void TIM_OC2Init(tim_t* TIMx, tim_oc_init_t *init)
{
	uint16_t tmpccmrx = 0, tmpccer = 0;

	/* Disable the Channel 2: Reset the CC1E Bit */
	TIMx->CCER &= (uint16_t)(~(uint16_t)0x0010);

	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;

	/* Get the TIMx CCMR1 register value */
	tmpccmrx = TIMx->CCMR1;

	/* Reset the Output Compare Mode Bits */
	tmpccmrx &= (uint16_t)(~((uint16_t)0x7000));

	/* Select the Output Compare Mode */
	tmpccmrx |= init->oc_mode << 8;

	/* Reset the Output Polarity level */
	tmpccer &= (uint16_t)(~((uint16_t)0x0020));
	/* Set the Output Compare Polarity */
	tmpccer |= init->oc_polarity << 4;

	/* Set the Output State */
	tmpccer |= init->output_state << 4;

	/* Set the Capture Compare Register value */
	TIMx->CCR2 = init->pulse;

	/* Write to TIMx CCMR1 */
	TIMx->CCMR1 = tmpccmrx;

	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/* output compare init (channel 3) */
void TIM_OC3Init(tim_t* TIMx, tim_oc_init_t *init)
{
	uint16_t tmpccmrx = 0, tmpccer = 0;

	/* Disable the Channel 3: Reset the CC1E Bit */
	TIMx->CCER &= (uint16_t)(~(uint16_t)0x0100);

	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;

	/* Get the TIMx CCMR1 register value */
	tmpccmrx = TIMx->CCMR2;

	/* Reset the Output Compare Mode Bits */
	tmpccmrx &= (uint16_t)(~((uint16_t)0x0070));

	/* Select the Output Compare Mode */
	tmpccmrx |= init->oc_mode;

	/* Reset the Output Polarity level */
	tmpccer &= (uint16_t)(~((uint16_t)0x0200));
	/* Set the Output Compare Polarity */
	tmpccer |= init->oc_polarity << 8;

	/* Set the Output State */
	tmpccer |= init->output_state << 8;

	/* Set the Capture Compare Register value */
	TIMx->CCR3 = init->pulse;

	/* Write to TIMx CCMR1 */
	TIMx->CCMR2 = tmpccmrx;

	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/* output compare init (channel 4) */
void TIM_OC4Init(tim_t* TIMx, tim_oc_init_t *init)
{
	uint16_t tmpccmrx = 0, tmpccer = 0;

	/* Disable the Channel 4: Reset the CC1E Bit */
	TIMx->CCER &= (uint16_t)(~(uint16_t)0x1000);

	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;

	/* Get the TIMx CCMR1 register value */
	tmpccmrx = TIMx->CCMR2;

	/* Reset the Output Compare Mode Bits */
	tmpccmrx &= (uint16_t)(~((uint16_t)0x7000));

	/* Select the Output Compare Mode */
	tmpccmrx |= init->oc_mode << 8;

	/* Reset the Output Polarity level */
	tmpccer &= (uint16_t)(~((uint16_t)0x1000));
	/* Set the Output Compare Polarity */
	tmpccer |= init->oc_polarity << 12;

	/* Set the Output State */
	tmpccer |= init->output_state << 12;

	/* Set the Capture Compare Register value */
	TIMx->CCR4 = init->pulse;

	/* Write to TIMx CCMR1 */
	TIMx->CCMR2 = tmpccmrx;

	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/* initialize struct */
void TIM_OCStructInit(tim_oc_init_t *init)
{
	/* Set the default configuration */
	init->oc_mode = TIM_OCMODE_TIMING;
	init->output_state = TIM_OUTPUTSTATE_DISABLE;
	init->pulse = 0x0000;
	init->oc_polarity = TIM_OCPOLARITY_HIGH;
}

/* select output compare */
void TIM_SelectOCxM(tim_t* TIMx, int TIM_Channel, int TIM_OCMode)
{
	uint32_t tmp = 0;
	uint16_t tmp1 = 0;

	tmp = (uint32_t) TIMx;
	tmp += 0x0018;

	tmp1 = 0x0001 << (uint16_t)TIM_Channel;

	/* Disable the Channel: Reset the CCxE Bit */
	TIMx->CCER &= (uint16_t) ~tmp1;

	if ((TIM_Channel == TIM_CHANNEL_1) ||(TIM_Channel == TIM_CHANNEL_3)) {
		tmp += (TIM_Channel >> 1);
		/* Reset the OCxM bits in the CCMRx register */
		*(reg32_t *) tmp &= (uint32_t)~((uint32_t)0x0070);

		/* Configure the OCxM bits in the CCMRx register */
		*(reg32_t *) tmp |= TIM_OCMode;
	} else {
		tmp += (uint16_t)(TIM_Channel - (uint16_t)4)>> (uint16_t)1;
		/* Reset the OCxM bits in the CCMRx register */
		*(reg32_t *) tmp &= (uint32_t)~((uint32_t)0x7000);

		/* Configure the OCxM bits in the CCMRx register */
		*(reg32_t *) tmp |= (uint16_t)(TIM_OCMode << 8);
	}
}

/* set compare1 */
void TIM_SetCompare1(tim_t* TIMx, uint32_t Compare1)
{
	/* Set the Capture Compare1 Register value */
	TIMx->CCR1 = Compare1;
}

/* set compare2 */
void TIM_SetCompare2(tim_t* TIMx, uint32_t Compare2)
{
	/* Set the Capture Compare2 Register value */
	TIMx->CCR2 = Compare2;
}

/* set compare3 */
void TIM_SetCompare3(tim_t* TIMx, uint32_t Compare3)
{
	/* Set the Capture Compare3 Register value */
	TIMx->CCR3 = Compare3;
}

/* set compare4 */
void TIM_SetCompare4(tim_t* TIMx, uint32_t Compare4)
{
	/* Set the Capture Compare4 Register value */
	TIMx->CCR4 = Compare4;
}

/* select input trigger */
void TIM_SelectInputTrigger(tim_t * TIMx, uint16_t source)
{
	uint16_t tmpsmcr = 0;

	/* Get the TIMx SMCR register value */
	tmpsmcr = TIMx->SMCR;
	/* Reset the TS Bits */
	tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_TS));
	/* Set the Input Trigger source */
	tmpsmcr |= source;
	/* Write to TIMx SMCR */
	TIMx->SMCR = tmpsmcr;
}

/* select output trigger */
void TIM_SelectOutputTrigger(tim_t *TIMx, uint16_t source)
{
	/* Reset the MMS Bits */
	TIMx->CR2 &= (uint16_t)~((uint16_t)TIM_CR2_MMS);
	/* Select the TRGO source */
	TIMx->CR2 |=  source;
}

/* slave mode select */
void TIM_SelectSlaveMode(tim_t *TIMx, uint16_t slave_mode)
{
	/* Reset the SMS Bits */
	TIMx->SMCR &= (uint16_t)~((uint16_t)TIM_SMCR_SMS);
	/* Select the Slave Mode */
	TIMx->SMCR |= slave_mode;
}

/* master slave mode select */
void TIM_SelectMasterSlaveMode(tim_t *TIMx, uint16_t mode)
{
	/* Reset the MSM Bit */
	TIMx->SMCR &= (uint16_t)~((uint16_t)TIM_SMCR_MSM);
	/* Set or Reset the MSM Bit */
	TIMx->SMCR |= mode;
}

/* configure external trigger */
void TIM_ETRConfig(tim_t *TIMx, uint16_t prescaler, uint16_t polarity,
                   uint16_t filter)
{
	uint16_t tmpsmcr = 0;

	tmpsmcr = TIMx->SMCR;
	/* Reset the ETR Bits */
	tmpsmcr &= 0x00FF;
	/* Set the Prescaler, the Filter value and the Polarity */
	tmpsmcr |= (uint16_t)(prescaler | (uint16_t)(polarity |
		  (uint16_t)(filter << (uint16_t)8)));
	/* Write to TIMx SMCR */
	TIMx->SMCR = tmpsmcr;
}

/* remap */
void TIM_RemapConfig(tim_t *TIMx, uint16_t remap)
{
	/* Set the Timer remapping configuration */
	TIMx->OR = remap;
}

/* prescaler update */
void TIM_PrescalerConfig(tim_t* TIMx, uint16_t pres, uint16_t reload_mode)
{
	/* Set the Prescaler value */
	TIMx->PSC = pres;
	/* Set or reset the UG Bit */
	TIMx->EGR = reload_mode;
}

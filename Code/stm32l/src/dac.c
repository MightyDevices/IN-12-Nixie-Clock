/*
 * dac.c
 *
 *  Created on: 29-09-2013
 *      Author: Tomek
 */


#include <stm32l/rcc.h>
#include <stm32l/dac.h>

/* dac deinit */
void DAC_Deinit(void)
{
	/* Enable DAC reset state */
	RCC_APB1PeriphResetCmd(APB1_DAC, ENABLE);
	/* Release DAC from reset state */
	RCC_APB1PeriphResetCmd(APB1_DAC, DISABLE);
}

/* initialize dac */
void DAC_Init(uint32_t channel, dac_init_t *init)
{
	uint32_t tmpreg1 = 0, tmpreg2 = 0;

	/* Get the DAC CR value */
	tmpreg1 = DAC->CR;
	/* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
	tmpreg1 &= ~(0x00000FFE << channel);
	/* Configure for the selected DAC channel: buffer output, trigger, wave generation,
	 mask/amplitude for wave generation */
	tmpreg2 = (init->trigger | init->wave_gen |
		  init->lfsr_unmask_triangle_amp | init->output_buf);
	/* Calculate CR register value depending on DAC_Channel */
	tmpreg1 |= tmpreg2 << channel;
	/* Write to DAC CR */
	DAC->CR = tmpreg1;
}

/* initialize structure */
void DAC_StructInit(dac_init_t *init)
{
	/* Initialize the DAC_Trigger member */
	init->trigger = DAC_TRIGGER_NONE;
	/* Initialize the DAC_WaveGeneration member */
	init->wave_gen = DAC_WAVE_NONE;
	/* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
	init->lfsr_unmask_triangle_amp = DAC_LFSRUNMASK_BIT0;
	/* Initialize the DAC_OutputBuffer member */
	init->output_buf = DAC_OUTPUT_BUFFER_ENABLE;
}

/* enable / disable channel */
void DAC_Cmd(uint32_t channel, int enable)
{
	if (enable != DISABLE) {
		/* Enable the selected DAC channel */
		DAC->CR |= (DAC_CR_EN1 << channel);
	} else {
		/* Disable the selected DAC channel */
		DAC->CR &= (~(DAC_CR_EN1 << channel));
	}
}

/* software trigger cmd */
void DAC_SoftwareTriggerCmd(uint32_t channel)
{
	/* Enable software trigger for the selected DAC channel */
	DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1 << (channel >> 4);
}

/* trigger both channels */
void DAC_DualSoftwareTriggerCmd(int enable)
{
	if (enable != DISABLE) {
		/* Enable software trigger for the selected DAC channel */
		DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2;
	} else {
		/* Disable software trigger for the selected DAC channel */
		DAC->SWTRIGR &= ~(DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2);
	}
}

/* wave generation cmd */
void DAC_WaveGenerationCmd(uint32_t channel, uint32_t wave, int enable)
{
	if (enable != DISABLE) {
		/* Enable the selected wave generation for the selected DAC channel */
		DAC->CR |= wave << channel;
	} else {
		/* Disable the selected wave generation for the selected DAC channel */
		DAC->CR &= ~(wave << channel);
	}
}

/* set channel data */
void DAC_SetChannel1Data(uint32_t align, uint16_t data)
{
	/* register depends on data align */
	switch (align) {
	/* 12 bit left */
	case DAC_ALIGN_12B_L : DAC->DHR12L1 = data; break;
	/* 12 bit right */
	case DAC_ALIGN_12B_R : DAC->DHR12R1 = data; break;
	/* 8 bit */
	case DAC_ALIGN_8B_R : DAC->DHR8R1 = data; break;
	}
}

/* set channel data */
void DAC_SetChannel2Data(uint32_t align, uint16_t data)
{
	/* register depends on data align */
	switch (align) {
	/* 12 bit left */
	case DAC_ALIGN_12B_L : DAC->DHR12L2 = data; break;
	/* 12 bit right */
	case DAC_ALIGN_12B_R : DAC->DHR12R2 = data; break;
	/* 8 bit */
	case DAC_ALIGN_8B_R : DAC->DHR8R2 = data; break;
	}
}

/* set channel data */
void DAC_SetDualChannelData(uint32_t align, uint16_t data_1, uint16_t data_2)
{
	/* compose buffer */
	uint32_t data = 0;

	/* 8 bit */
	if (align == DAC_ALIGN_8B_R) {
		data = (data_2 << 8) | data_1;
	/* 12 bit*/
	} else {
		data = (data_2 << 16) | data_1;
	}

	/* register depends on data align */
	switch (align) {
	/* 12 bit left */
	case DAC_ALIGN_12B_L : DAC->DHR12LD = data; break;
	/* 12 bit right */
	case DAC_ALIGN_12B_R : DAC->DHR12RD = data; break;
	/* 8 bit */
	case DAC_ALIGN_8B_R : DAC->DHR8RD = data; break;
	}
}

/* get data output */
uint16_t DAC_GetDataOutputValue(uint32_t channel)
{
	uint16_t val = 0;
	/* get value */
	if (channel == DAC_CHANNEL_1) {
		val = DAC->DOR1;
	} else {
		val = DAC->DOR2;
	}
	/* return value */
	return val;
}

/* dac dma functions */
void DAC_DMACmd(uint32_t channel, int enable)
{
	if (enable != DISABLE) {
		/* Enable the selected DAC channel DMA request */
		DAC->CR |= (DAC_CR_DMAEN1 << channel);
	} else {
		/* Disable the selected DAC channel DMA request */
		DAC->CR &= (~(DAC_CR_DMAEN1 << channel));
	}
}

/* configure dac interrupt */
void DAC_ITConfig(uint32_t channel, uint32_t it, int enable)
{
	if (enable != DISABLE) {
		/* Enable the selected DAC interrupts */
		DAC->CR |=  (it << channel);
	} else {
		/* Disable the selected DAC interrupts */
		DAC->CR &= (~(it << channel));
	}
}

/* get status */
uint16_t DAC_GetStatus(uint32_t channel)
{
	uint16_t status = 0;

	/* get status register */
	if (channel == DAC_CHANNEL_1) {
		status = DAC->SR & 0xffff;
	} else {
		status = DAC->SR >> 16;
	}
	/* return value */
	return status;
}

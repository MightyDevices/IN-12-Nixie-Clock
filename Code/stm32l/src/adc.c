/*
 * atm32_adc.c
 *
 *  Created on: 02-08-2012
 *      Author: Tomek
 */

#include <stm32l/adc.h>

/* initilize adc */
void ADC_Init(adc_t *ADCx, adc_init_t *init)
{
	uint32_t tmpreg1 = 0;
	uint8_t tmpreg2 = 0;

	/* Get the ADCx CR1 value */
	tmpreg1 = ADCx->CR1;
	/* Clear RES and SCAN bits */
	tmpreg1 &= ~((3 << 24) | (1 << 8));
	/* Configure ADCx: scan conversion mode and resolution */
	/* Set SCAN bit according to ADC_ScanConvMode value */
	/* Set RES bit according to ADC_Resolution value */
	tmpreg1 |= (uint32_t)(((uint32_t)init->scan_conv_mode << 8) |
			init->resolution);
	/* Write to ADCx CR1 */
	ADCx->CR1 = tmpreg1;


	/* Get the ADCx CR2 value */
	tmpreg1 = ADCx->CR2;
	/* Clear CONT, ALIGN, EXTEN and EXTSEL bits */
	tmpreg1 &= ~((1 << 1) | (1 << 11) | (3 << 28) | (0xf << 24));
	/* Set ALIGN bit according to ADC_DataAlign value */
	/* Set EXTEN bits according to ADC_ExternalTrigConvEdge value */
	/* Set EXTSEL bits according to ADC_ExternalTrigConv value */
	/* Set CONT bit according to ADC_ContinuousConvMode value */
	tmpreg1 |= (uint32_t)(init->data_align | init->external_trig_conv |
			  init->external_trig_conv_edge |
			  (init->continuous_conv_mode << 1));
	/* Write to ADCx CR2 */
	ADCx->CR2 = tmpreg1;


	/* Get the ADCx SQR1 value */
	tmpreg1 = ADCx->SQR1;
	/* Clear L bits */
	tmpreg1 &= ~(0x1f << 20);
	/* Configure ADCx: regular channel sequence length */
	/* Set L bits according to ADC_NbrOfConversion value */
	tmpreg2 |= (uint8_t)(init->conversion_num - (uint8_t)1);
	tmpreg1 |= ((uint32_t)tmpreg2 << 20);
	/* Write to ADCx SQR1 */
	ADCx->SQR1 = tmpreg1;
}

/* initialize structure */
void ADC_StructInit(adc_init_t *init)
{
	/* Reset ADC init structure parameters values */
	/* Initialize the ADC_Resolution member */
	init->resolution = ADC_RESOLUTION_12b;
	/* Initialize the ADC_ScanConvMode member */
	init->scan_conv_mode = DISABLE;
	/* Initialize the ADC_ContinuousConvMode member */
	init->continuous_conv_mode = DISABLE;
	/* Initialize the ADC_ExternalTrigConvEdge member */
	init->external_trig_conv_edge = ADC_EXTTRIGCONVEDGE_NONE;
	/* Initialize the ADC_ExternalTrigConv member */
	init->external_trig_conv = ADC_EXTTRIGCONV_T2_CC2;
	/* Initialize the ADC_DataAlign member */
	init->data_align = ADC_DATAALIGN_RIGHT;
	/* Initialize the ADC_NbrOfConversion member */
	init->conversion_num = 1;
}

/* initialize common registers */
void ADC_CommonInit(adc_init_com_t *init)
{
	uint32_t tmpreg = 0;
	/* Get the ADC CCR value */
	tmpreg = ADC->CCR;
	/* Clear ADCPRE bit */
	tmpreg &= ~(3 << 16);
	/* Configure ADCx: ADC prescaler according to ADC_Prescaler */
	tmpreg |= (uint32_t)(init->prescaler);
	/* Write to ADC CCR */
	ADC->CCR = tmpreg;
}

/* init struct */
void ADC_CommonStructInit(adc_init_com_t *init)
{
  /* Reset ADC init structure parameters values */
  /* Initialize the ADC_Prescaler member */
	init->prescaler = ADC_PRESCALER_DIV1;
}

/* command */
void ADC_Cmd(adc_t *ADCx, int state)
{
	if (state) {
		/* Set the ADON bit to wake up the ADC from power down mode */
		ADCx->CR2 |= ADC_CR2_ADON;
	} else {
		/* Disable the selected ADC peripheral */
		ADCx->CR2 &= ~ADC_CR2_ADON;
	}
}

/* get status flags */
uint32_t ADC_GetStatus(adc_t *ADCx)
{
	return ADCx->SR;
}

/* configure regular channel */
void ADC_RegularChannelConfig(adc_t *ADCx, uint8_t channel, uint8_t rank,
		uint8_t sample_time)
{
	 uint32_t tmpreg1 = 0, tmpreg2 = 0;

	/* If channel_30 or channel_31 is selected */
	if (channel > ADC_C29) {
		/* Get the old register value */
		tmpreg1 = ADCx->SMPR0;
		/* Calculate the mask to clear */
		tmpreg2 = 0x7 << (3 * (channel - 30));
		/* Clear the old sample time */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)sample_time << (3 * (channel - 30));
		/* Set the new sample time */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SMPR0 = tmpreg1;
	/* If channel_20 ... channel_29 is selected */
	} else if (channel > ADC_C19) {
		/* Get the old register value */
		tmpreg1 = ADCx->SMPR1;
		/* Calculate the mask to clear */
		tmpreg2 = 0x7 << (3 * (channel - 20));
		/* Clear the old sample time */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)sample_time << (3 * (channel - 20));
		/* Set the new sample time */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SMPR1 = tmpreg1;
	/* If channel_10 ... channel_19 is selected */
	} else if (channel > ADC_C9) {
		/* Get the old register value */
		tmpreg1 = ADCx->SMPR2;
		/* Calculate the mask to clear */
		tmpreg2 = 0x7 << (3 * (channel - 10));
		/* Clear the old sample time */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)sample_time << (3 * (channel - 10));
		/* Set the new sample time */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SMPR2 = tmpreg1;
	/* channel include in channel_[0..9] */
	} else {
		/* Get the old register value */
		tmpreg1 = ADCx->SMPR3;
		/* Calculate the mask to clear */
		tmpreg2 = 0x7 << (3 * channel);
		/* Clear the old sample time */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)sample_time << (3 * channel);
		/* Set the new sample time */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SMPR3 = tmpreg1;
	}

	/* For rank 1 to 6 */
	if (rank < 7) {
		/* Get the old register value */
		tmpreg1 = ADCx->SQR5;
		/* Calculate the mask to clear */
		tmpreg2 = 0x0000001F << (5 * (rank - 1));
		/* Clear the old SQx bits for the selected rank */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)channel << (5 * (rank - 1));
		/* Set the SQx bits for the selected rank */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SQR5 = tmpreg1;
	/* For rank 7 to 12 */
	} else if (rank < 13) {
		/* Get the old register value */
		tmpreg1 = ADCx->SQR4;
		/* Calculate the mask to clear */
		tmpreg2 = 0x0000001F << (5 * (rank - 7));
		/* Clear the old SQx bits for the selected rank */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)channel << (5 * (rank - 7));
		/* Set the SQx bits for the selected rank */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SQR4 = tmpreg1;
	/* For rank 13 to 18 */
	} else if (rank < 19) {
		/* Get the old register value */
		tmpreg1 = ADCx->SQR3;
		/* Calculate the mask to clear */
		tmpreg2 = 0x0000001F << (5 * (rank - 13));
		/* Clear the old SQx bits for the selected rank */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)channel << (5 * (rank - 13));
		/* Set the SQx bits for the selected rank */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SQR3 = tmpreg1;
	/* For rank 19 to 24 */
	} else if (rank < 25) {
		/* Get the old register value */
		tmpreg1 = ADCx->SQR2;
		/* Calculate the mask to clear */
		tmpreg2 = 0x0000001F << (5 * (rank - 19));
		/* Clear the old SQx bits for the selected rank */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)channel << (5 * (rank - 19));
		/* Set the SQx bits for the selected rank */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SQR2 = tmpreg1;
	/* For rank 25 to 28 */
	} else {
		/* Get the old register value */
		tmpreg1 = ADCx->SQR1;
		/* Calculate the mask to clear */
		tmpreg2 = 0x0000001F << (5 * (rank - 25));
		/* Clear the old SQx bits for the selected rank */
		tmpreg1 &= ~tmpreg2;
		/* Calculate the mask to set */
		tmpreg2 = (uint32_t)channel << (5 * (rank - 25));
		/* Set the SQx bits for the selected rank */
		tmpreg1 |= tmpreg2;
		/* Store the new register value */
		ADCx->SQR1 = tmpreg1;
	}
}

/* start software conversion */
void ADC_SoftwareStartConv(adc_t *ADCx)
{
	/* Enable the selected ADC conversion for regular group */
	ADCx->CR2 |= ADC_CR2_SWSTART;
}

/* get conversion status */
int ADC_GetSoftwareStartConvStatus(adc_t *ADCx)
{
	int rc = 0;
	/* flag set */
	if (ADCx->CR2 & ADC_CR2_SWSTART) {
		rc = 1;
	}

	/* Return the SWSTART bit status */
	return  rc;
}

/* get conversion value */
uint16_t ADC_GetConversionValue(adc_t* ADCx)
{
	/* Return the selected ADC conversion value */
	return (uint16_t) ADCx->DR;
}

/* enable internal reference and temperature sensor */
void ADC_TempSensorVrefintCmd(int state)
{
	if (state != DISABLE) {
		/* Enable the temperature sensor and Vrefint channel */
		ADC->CCR |= ADC_CCR_TSVREFE;
	} else {
		/* Disable the temperature sensor and Vrefint channel */
		ADC->CCR &= ~ADC_CCR_TSVREFE;
	}
}

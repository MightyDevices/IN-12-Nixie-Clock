/*
 * comp.c
 *
 *  Created on: 23-01-2014
 *      Author: Tomek
 */

#include <stm32l/comp.h>
#include <stm32l/stm32l.h>

/* deinitialize comparator */
void COMP_DeInit(void)
{
	COMP->CSR = 0x00000000;
}

/* initialize comparator */
void COMP_Init(comp_init_t *init)
{
  uint32_t tmpreg = 0;

  /*!< Get the COMP CSR value */
  tmpreg = COMP->CSR;

  /*!< Clear the  INSEL[2:0], OUTSEL[1:0] and SPEED bits */
  tmpreg &= (uint32_t) (~(uint32_t) (COMP_CSR_OUTSEL | COMP_CSR_INSEL |
		  COMP_CSR_SPEED));

  /* Configure COMP: speed, inversion input selection and output redirection */
  tmpreg |= (uint32_t)((init->speed | init->inverting_input
                        | init->output_select));

  /*!< The COMP2 comparator is enabled as soon as the INSEL[2:0] bits value are
     different from "000" */
  /*!< Write to COMP_CSR register */
  COMP->CSR = tmpreg;
}

/* Enable or disable the COMP1 peripheral. */
void COMP_Cmd(int state)
{
	/* comparator enable bit */
	bitband_t cmp_en = BITBAND_PERIPH(&COMP->CSR, 4);
	/* set state */
	*cmp_en = state;
}

/* Return the output level (high or low) of the selected comparator */
uint32_t COMP_GetOutputLevel(void)
{
	/* output bits */
	bitband_t cmp_out1 = BITBAND_PERIPH(&COMP->CSR, 7);
	bitband_t cmp_out2 = BITBAND_PERIPH(&COMP->CSR, 13);

	return (*cmp_out2 << 1) | *cmp_out1;
}

/* Enables or disables the window mode. */
void COMP_WindowCmd(int enable)
{
	/* window mode enable bit */
	bitband_t cmp_wndwe = BITBAND_PERIPH(&COMP->CSR, 17);
	/* set bit */
	*cmp_wndwe = enable;
}

/* Enables or disables the output of internal reference voltage (VREFINT) */
void COMP_VrefintOutputCmd(int enable)
{
	/* vref enable bit */
	bitband_t cmp_vrefouten = BITBAND_PERIPH(&COMP->CSR, 16);
	/* set bit */
	*cmp_vrefouten = enable;
}


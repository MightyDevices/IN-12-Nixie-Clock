/*
 * stm32_usart.c
 *
 *  Created on: 13-06-2012
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/usart.h>

/* initialize usart */
void USART_Init(usart_t *USARTx, usart_init_t *init)
{
	uint32_t tmpreg = 0x00, apbclock = 0x00;
	uint32_t integerdivider = 0x00;
	uint32_t fractionaldivider = 0x00;
	rcc_clocks_t clocks;

	tmpreg = USARTx->CR2;
	/* Clear STOP[13:12] bits */
	tmpreg &= ~(0x00003000);
	/* Set STOP[13:12] bits according to USART_STOPBITS value */
	tmpreg |= (uint32_t)init->stop_bits;
	/* Write to USART CR2 */
	USARTx->CR2 = (uint16_t)tmpreg;

	tmpreg = USARTx->CR1;
	/* Clear M, PCE, PS, TE and RE bits */
	tmpreg &= ~(0x0000160C);

	/* Set the M bits according to USART_WordLength value */
	/* Set PCE and PS bits according to USART_Parity value */
	/* Set TE and RE bits according to USART_Mode value */
	tmpreg |= (uint32_t)init->word_length | init->parity |
			init->mode | (1 << 15);

	/* Write to USART CR1 */
	USARTx->CR1 = (uint16_t)tmpreg;

	tmpreg = USARTx->CR3;
	/* Clear CTSE and RTSE bits */
	tmpreg &= ~(0x00000300);

	/* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
	tmpreg |= init->hardware_flow_control;

	/* Write to USART CR3 */
	USARTx->CR3 = (uint16_t)tmpreg;
	/* get clocks to set baudrate */
	RCC_GetClocksFreq(&clocks);
	/* usart1 sits on apb2 */
	if (USARTx == USART1) {
		apbclock = clocks.pclk2_frequency;
	} else {
		apbclock = clocks.pclk1_frequency;
	}

	/* Determine the integer part */
	if ((USARTx->CR1 & (1 << 15)) != 0) {
		/* Integer part computing in case Oversampling mode is 8 Samples */
		integerdivider = ((25 * apbclock) / (2 * (init->baud_rate)));
	} else {
		/* Integer part computing in case Oversampling mode is 16 Samples */
		integerdivider = ((25 * apbclock) / (4 * (init->baud_rate)));
	}
	tmpreg = (integerdivider / 100) << 4;

	/* Determine the fractional part */
	fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

	/* Implement the fractional part in the register */
	if ((USARTx->CR1 & (1 << 15)) != 0) {
		tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
	} else {
		tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
	}

	/* Write to USART BRR */
	USARTx->BRR = (uint16_t)tmpreg;
}

/* initialize structure with defaults */
void USART_StructInit(usart_init_t *init)
{
	/* defaults */
	init->baud_rate = 9600;
	init->word_length = USART_WORD_8B;
	init->stop_bits = USART_STOPBITS_1;
	init->parity = USART_PARITY_NO;
	init->mode = USART_MODE_RX | USART_MODE_TX;
	init->hardware_flow_control= USART_HARDWAREFLOWCONTROL_NONE;
}

/* usart command */
void USART_Cmd(usart_t *USARTx, int state)
{
	if (state) {
		/* Enable the selected USART by setting the UE bit in the
		 * CR1 register */
		USARTx->CR1 |= (1 << 13);
	} else {
		/* Disable the selected USART by clearing the UE bit in the
		 * CR1 register */
		USARTx->CR1 &= ~(1 << 13);
	}
}

/* usart command */
void USART_DMACmd(usart_t *USARTx, uint32_t dma_req, int state)
{
	if (state) {
		/* Enable the selected USART by setting the UE bit in the
		 * CR1 register */
		USARTx->CR3 |= (uint16_t)dma_req;
	} else {
		/* Disable the selected USART by clearing the UE bit in the
		 * CR1 register */
		USARTx->CR3 &= (uint16_t)~(dma_req);
	}
}

/* Transmits single data through the USARTx peripheral. */
void USART_SendData(usart_t *USARTx, uint16_t data)
{
	/* Transmit Data */
	USARTx->DR = (data & (uint16_t)0x01FF);
}

/* Returns the most recent received data by the USARTx peripheral. */
uint16_t USART_ReceiveData(usart_t *USARTx)
{
	/* Receive Data */
	return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}

/* get usart status */
int USART_GetStatus(usart_t *USARTx)
{
	/* Transmit Data */
	return USARTx->SR;
}

/* configure interrupt */
void USART_ITConfig(usart_t *USARTx, uint8_t interrupt, int state)
{
	if (state) {
		/* Enable the selected SPI interrupt */
		USARTx->CR1 |= interrupt;
	} else {
		/* Disable the selected SPI interrupt */
		USARTx->CR1 &= (uint16_t)~interrupt;
	}
}

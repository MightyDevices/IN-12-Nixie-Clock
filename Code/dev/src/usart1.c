/*
 * usart1.c
 *
 *  Created on: 20-11-2012
 *      Author: Tomek
 */

#include <stdint.h>
#include <stm32l/rcc.h>
#include <stm32l/usart.h>
#include <stm32l/gpio.h>
#include <stm32l/nvic.h>
#include <stm32l/dma.h>
#include <stm32l/stm32l.h>
#include <util/minmax.h>
#include <util/string.h>
#include <util/stdlib.h>
#include <util/circbuf.h>
#include <sys/err.h>

/* buffers */
static cb_t tx_cb, rx_cb;
/* buffer mem */
static uint8_t tx_mem[128], rx_mem[128];
/* current transfer size */
static volatile uint16_t tx_tsize, rx_tsize;

/* start tx transfer */
static void USART1_DmaTxStartTransfer(void *ptr, size_t size)
{
	/* bitband for tx dma enable/disable */
	bitband_t en = BITBAND_PERIPH(&DMAC4->CCR, 0);

	/* clear transfer complete */
	USART1->SR = ~USART_SR_TC;
	/* disable channel */
	*en = 0;
	/* set memory pointer */
	DMAC4->CMAR = (uint32_t)(ptr);
	/* set size */
	DMAC4->CNDTR = size;
	/* store transfer size */
	tx_tsize = size;
	/* enable */
	*en = 1;
}

/* transmit dma interrupt */
static void USART1_DmaTxIsr(void)
{
	/* linear pointer */
	void *lin_ptr;
	/* bytes present in buffer */
	uint16_t bbuf;
	/* get interrupt status register */
	uint32_t isr = DMA1->ISR;

	/* clear interrupt flag */
	DMA1->IFCR = DMA_IFCR_CGIF4;
	/* transfer is completed? */
	if (isr & DMA_ISR_TCIF4) {
		/* update tail pointer */
		tx_cb.tail += tx_tsize;
		/* get number of remaining bytes */
		bbuf = tx_cb.head - tx_cb.tail;
		/* some data is still present in buffer? */
		if (bbuf) {
			/* get data */
			bbuf = CB_GetDataPtrInLinearSpace(&tx_cb, &lin_ptr);
			/* set memory pointer */
			USART1_DmaTxStartTransfer(lin_ptr, bbuf);
		/* nothing left for transfer? */
		} else {
			/* disable channel */
			tx_tsize = 0;
		}
	}
}
/* receive interrupt */
static void USART1_DmaRxIsr(void)
{
	/* bytes buffered */
	uint16_t bbuf;
	/* get interrupt status register */
	uint32_t isr = DMA1->ISR;
	/* clear interrupt flag */
	DMA1->IFCR = DMA_IFCR_CGIF5;

	/* transfer is completed? */
	if (isr & DMA_ISR_TCIF5) {
		/* limit transfer size */
		rx_cb.head += rx_tsize;
		/* new transfer */
		rx_tsize = sizeof(rx_mem);
	/* half transfer completed */
	} else if (isr & DMA_ISR_HTIF5) {
		/* number of bytes already received */
		bbuf = rx_tsize - DMAC5->CNDTR;
		/* update pointers */
		rx_cb.head += bbuf; rx_tsize -= bbuf;
	}
}

/* usart isr */
static void USART1_Isr(void)
{
	/* bytes buffered */
	uint16_t bbuf;
	/* get status register */
	uint16_t sr = USART1->SR;
	/* idle state */
	if (sr & USART_SR_IDLE) {
		/* number of bytes already received */
		bbuf = rx_tsize - DMAC5->CNDTR;
		/* update pointers */
		rx_cb.head += bbuf; rx_tsize -= bbuf;
	}

	/* dummy read, needed to ack interrupt */
	USART1->DR;
}

/* initialize usart3 */
int USART1_Init(void)
{
	/* enable gpioa and dma */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_DMA1EN;
	/* enable usart1 clock */
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	/* reset moder configutration */
	GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
	/* set both as alternate function */
	GPIOA->MODER |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;
	/* reset afrh */
	GPIOA->AFRH &= ~(0xF << 4 | 0xF << 8);
	/* set alternate function to usart */
	GPIOA->AFRH |= GPIO_AF_USART << 4 | GPIO_AF_USART << 8;

	/* reset usart */
	RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
	/* disable reset */
	RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

	/* configure usart */
	USART1->CR1 = USART_CR1_OVER8 | USART_CR1_IDLEIE |
			 USART_CR1_RE | USART_CR1_TE;
	/* configure baud rate, div = 2.25 */
	USART1->BRR = 0x44;
	/* enable usart */
	USART1->CR1 |= USART_CR1_UE;
	/* enable dma request */
	USART1->CR3 = USART_CR3_DMAT | USART_CR3_EIE;

	/* configure rx dma */
	DMAC5->CCR = DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_TCIE | DMA_CCR_HTIE;
	/* peripheral address */
	DMAC5->CPAR = (uint32_t)&USART1->DR;

	/* configure tx dma */
	DMAC4->CCR = DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE;
	/* peripheral address */
	DMAC4->CPAR = (uint32_t)&USART1->DR;

	/* set interrupt vector for dma */
	NVIC_SetInterruptVector(NVIC_DMA5, USART1_DmaRxIsr);
	/* set interrupt priority */
	NVIC_SetInterruptPriority(NVIC_DMA5, 0xff);
	/* enable interrupt */
	NVIC_EnableInterrupt(NVIC_DMA5);

	/* set interrupt vector for dma */
	NVIC_SetInterruptVector(NVIC_DMA4, USART1_DmaTxIsr);
	/* set interrupt priority */
	NVIC_SetInterruptPriority(NVIC_DMA4, 0xff);
	/* enable interrupt */
	NVIC_EnableInterrupt(NVIC_DMA4);

	/* set interrupt vector for usart */
	NVIC_SetInterruptVector(NVIC_USART1, USART1_Isr);
	/* set interrupt priority */
	NVIC_SetInterruptPriority(NVIC_USART1, 0xff);
	/* enable interrupt */
	NVIC_EnableInterrupt(NVIC_USART1);

	/* reset tx buffer */
	CB_Init(&tx_cb, tx_mem, sizeof(tx_mem));
	/* reset rx buffer */
	CB_Init(&rx_cb, rx_mem, sizeof(rx_mem));

	/* configure memory pointer */
	DMAC5->CMAR = (uint32_t)rx_mem;
	/* configure mem size and store current transfer size */
	DMAC5->CNDTR = rx_tsize = sizeof(rx_mem);
	/* enable reception via dma */
	DMAC5->CCR |= DMA_CCR_EN;
	/* enable reception request generation by usart */
	USART1->CR3 |= USART_CR3_DMAR;

	/* all done */
	return EOK;
}

/* deinitialize usart1 */
int USART1_Deinit(void)
{
	/* wait till all bytes are transmitted */
	while ((USART1->SR & USART_SR_TC) == 0);
	/* disable usart */
	USART1->CR1 &= ~USART_CR1_UE;
	/* reset gpio configuration */
	GPIOA->MODER |= GPIO_MODER_MODER9 | GPIO_MODER_MODER10;
	/* disable usart clock */
	RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;

	/* report status */
	return EOK;
}

/* send data */
int USART1_Send(void *ptr, size_t size)
{
	/* linear mem pointer */
	void *lin_ptr; if ((RCC->APB2ENR & RCC_APB2ENR_USART1EN) == 0) return size;
	/* some variables */
	uint16_t bbuf;
	/* write bytes */
	size = CB_Put(&tx_cb, ptr, size);

	/* no transfer is ongoing? */
	if (!tx_tsize) {
		/* get max data chunk that is present in linear memory space */
		bbuf = CB_GetDataPtrInLinearSpace(&tx_cb, &lin_ptr);
		/* start dma transfer */
		USART1_DmaTxStartTransfer(lin_ptr, bbuf);
	}

	/* return number of bytes sent */
	return size;
}

/* receive data */
int USART1_Recv(void *ptr, size_t size)
{
	/* correction for buffer overflow which will occur as the dma keeps
	 * working even when buffer is full */
	if (rx_cb.head - rx_cb.tail > rx_cb.size) {
		/* save as many bytes as you can */
		rx_cb.tail = rx_cb.head - rx_cb.size;
	}
	/* write bytes */
	size = CB_Get(&rx_cb, ptr, size);
	/* return number of bytes received */
	return size;
}

/*
 * m2m.c
 *
 *  Created on: 26-04-2013
 *      Author: Tomek
 */

#include <sys/err.h>
#include <stm32l/rcc.h>
#include <stm32l/dma.h>
#include <stm32l/stm32l.h>
#include <util/stdlib.h>

/* initialize memory to memory transfers */
int M2M_Init(void)
{
	/* enable dma clock */
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	/* configure dma */
	DMAC2->CCR = 0;
	/* reset flags */
	DMA1->IFCR = DMA_IFCR_CGIF1;

	/* ok */
	return EOK;
}

/* perform transfer */
void M2M_Copy(void *dst, void *src, size_t size)
{
	/* destination pointer */
	DMAC2->CMAR = (uint32_t)dst;
	/* source pointer */
	DMAC2->CPAR = (uint32_t)src;
	/* set size */
	DMAC2->CNDTR = size;

	/* enable transfer */
	DMAC2->CCR = DMA_CCR_MEM2MEM | DMA_CCR_MINC | DMA_CCR_PINC | DMA_CCR_EN;
	/* wait till transfer finishes */
	while ((DMA1->ISR & DMA_ISR_TCIF2) == 0);
	/* disable transfer */
	DMAC2->CCR = 0;
	/* clear flag */
	DMA1->IFCR = DMA_IFCR_CTCIF2;
}

/* perform transfer (8-bit wide) */
void M2M_Set(void *dst, uint32_t data, size_t size)
{
	/* destination pointer */
	DMAC2->CMAR = (uint32_t)dst;
	/* source pointer */
	DMAC2->CPAR = (uint32_t)&data;
	/* set size */
	DMAC2->CNDTR = size;

	/* enable transfer */
	DMAC2->CCR = DMA_CCR_MEM2MEM | DMA_CCR_MINC | DMA_CCR_EN;
	/* wait till transfer finishes */
	while ((DMA1->ISR & DMA_ISR_TCIF2) == 0);
	/* disable transfer */
	DMAC2->CCR = 0;
	/* clear flag */
	DMA1->IFCR = DMA_IFCR_CTCIF2;
}

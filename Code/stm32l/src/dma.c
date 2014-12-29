/*
 * stm32_dma.c
 *
 *  Created on: 14-06-2012
 *      Author: Tomek
 */

#include <stm32l/dma.h>

/* initialize dma channel */
void DMA_Init(dma_chan_t *DMAx, dma_init_t *init)
{
	uint32_t tmpreg = 0;
	/* Get the DMAy_Channelx CCR value */
	tmpreg = DMAx->CCR;
	/* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
	tmpreg &= 0xFFFF800F;
	/* Configure DMAy Channelx: data transfer, data size, priority level
	 * and mode */
	tmpreg |= init->dir | init->mode |
		  init->peripheral_inc | init->memory_inc |
		  init->peripheral_data_size | init->memory_data_size |
		  init->priority | init->m2m;

	/* Write to DMAy Channelx CCR */
	DMAx->CCR = tmpreg;

	/* Write to DMAy Channelx CNDTR */
	DMAx->CNDTR = init->buffer_size;

	/* Write to DMAy Channelx CPAR */
	DMAx->CPAR = init->peripheral_base_addr;

	/* Write to DMAy Channelx CMAR */
	DMAx->CMAR = init->memory_base_addr;
}

/* initialize structure */
void DMA_StructInit(dma_init_t *init)
{
	/* Initialize the DMA_PeripheralBaseAddr member */
	init->peripheral_base_addr = 0;
	/* Initialize the DMA_MemoryBaseAddr member */
	init->memory_base_addr = 0;
	/* Initialize the DMA_DIR member */
	init->dir = DMA_DIR_PERIPHERAL_SRC;
	/* Initialize the DMA_BufferSize member */
	init->buffer_size = 0;
	/* Initialize the DMA_PeripheralInc member */
	init->peripheral_inc = DMA_PERIPHERALINC_DISABLE;
	/* Initialize the DMA_MemoryInc member */
	init->memory_inc = DMA_MEMORYINC_DISABLE;
	/* Initialize the DMA_PeripheralDataSize member */
	init->peripheral_data_size = DMA_PERIPHERALDATASIZE_BYTE;
	/* Initialize the DMA_MemoryDataSize member */
	init->memory_data_size = DMA_MEMORYDATASIZE_BYTE;
	/* Initialize the DMA_Mode member */
	init->mode = DMA_MODE_NORMAL;
	/* Initialize the DMA_Priority member */
	init->priority = DMA_PRIORITY_LOW;
	/* Initialize the DMA_M2M member */
	init->m2m = DMA_M2M_DISABLE;
}

/* dma command */
void DMA_Cmd(dma_chan_t* DMAx, int state)
{
	if (state) {
		/* Enable the selected DMAy Channelx */
		DMAx->CCR |= 0x1;
	} else {
		/* Disable the selected DMAy Channelx */
		DMAx->CCR &= (uint16_t)(~0x1);
	}
}

/* set data counter */
void DMA_SetMemoryBuffer(dma_chan_t *DMAx, void *ptr, int size)
{

	/* set memory buffer parameters */
	DMAx->CMAR = (uint32_t)ptr;
	DMAx->CNDTR = (uint16_t)size;
}

/* dma interrupt config */
void DMA_ITConfig(dma_chan_t* DMAx, uint32_t dma_it, int state)
{
	if (state) {
		/* Enable the selected DMA interrupts */
		DMAx->CCR |= dma_it;
	} else {
		/* Disable the selected DMA interrupts */
		DMAx->CCR &= ~dma_it;
	}
}

/* get flag status */
int DMA_GetStatus(void)
{
	return  DMA1->ISR;
}

/* get transfer number */
int DMA_GetTransferNumber(dma_chan_t *DMAx)
{
	return  DMAx->CNDTR;
}

/* clear flag status */
void DMA_ClearFlag(uint32_t dma_flag)
{
	/* Clear the selected DMA flags */
	DMA1->IFCR = dma_flag;
}

/*
 * stm32_dma.h
 *
 *  Created on: 14-06-2012
 *      Author: Tomek
 */

#include <stm32l/stm32l.h>

#ifndef STM32L_DMA_H_
#define STM32L_DMA_H_

/* registers bases */
#define DMA1_BASE							0x40026000

#define DMA1_CHAN1_OFFS						0x00000008
#define DMA1_CHAN2_OFFS						0x0000001c
#define DMA1_CHAN3_OFFS						0x00000030
#define DMA1_CHAN4_OFFS						0x00000044
#define DMA1_CHAN5_OFFS						0x00000058
#define DMA1_CHAN6_OFFS						0x0000006c
#define DMA1_CHAN7_OFFS						0x00000080

#define DMA2_BASE							0x40026400

#define DMA2_CHAN8_OFFS						0x00000008
#define DMA2_CHAN9_OFFS						0x0000001c
#define DMA2_CHAN10_OFFS					0x00000030
#define DMA2_CHAN11_OFFS					0x00000044
#define DMA2_CHAN12_OFFS					0x00000058

/* dma common registers */
#define DMA1								((dma_t *)DMA1_BASE)
#define DMA2								((dma_t *)DMA2_BASE)
/* dma channel */
#define DMAC1								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN1_OFFS))
/* dma channel */
#define DMAC2								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN2_OFFS))
/* dma channel */
#define DMAC3								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN3_OFFS))
/* dma channel */
#define DMAC4								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN4_OFFS))
/* dma channel */
#define DMAC5								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN5_OFFS))
/* dma channel */
#define DMAC6								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN6_OFFS))
/* dma channel */
#define DMAC7								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN7_OFFS))
/* dma channel */
#define DMAC8								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN8_OFFS))
/* dma channel */
#define DMAC9								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN9_OFFS))
/* dma channel */
#define DMAC10								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN10_OFFS))
/* dma channel */
#define DMAC11								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN11_OFFS))
/* dma channel */
#define DMAC12								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN12_OFFS))
/* registers */
typedef struct {
	reg32_t ISR;
	reg32_t IFCR;
} dma_t;

/* DMA interrupt status register */
#define DMA_ISR_GIF1                        (0x00000001)
#define DMA_ISR_TCIF1                       (0x00000002)
#define DMA_ISR_HTIF1                       (0x00000004)
#define DMA_ISR_TEIF1                       (0x00000008)
#define DMA_ISR_GIF2                        (0x00000010)
#define DMA_ISR_TCIF2                       (0x00000020)
#define DMA_ISR_HTIF2                       (0x00000040)
#define DMA_ISR_TEIF2                       (0x00000080)
#define DMA_ISR_GIF3                        (0x00000100)
#define DMA_ISR_TCIF3                       (0x00000200)
#define DMA_ISR_HTIF3                       (0x00000400)
#define DMA_ISR_TEIF3                       (0x00000800)
#define DMA_ISR_GIF4                        (0x00001000)
#define DMA_ISR_TCIF4                       (0x00002000)
#define DMA_ISR_HTIF4                       (0x00004000)
#define DMA_ISR_TEIF4                       (0x00008000)
#define DMA_ISR_GIF5                        (0x00010000)
#define DMA_ISR_TCIF5                       (0x00020000)
#define DMA_ISR_HTIF5                       (0x00040000)
#define DMA_ISR_TEIF5                       (0x00080000)
#define DMA_ISR_GIF6                        (0x00100000)
#define DMA_ISR_TCIF6                       (0x00200000)
#define DMA_ISR_HTIF6                       (0x00400000)
#define DMA_ISR_TEIF6                       (0x00800000)
#define DMA_ISR_GIF7                        (0x01000000)
#define DMA_ISR_TCIF7                       (0x02000000)
#define DMA_ISR_HTIF7                       (0x04000000)
#define DMA_ISR_TEIF7                       (0x08000000)

/* DMA interrupt flag  clear register */
#define DMA_IFCR_CGIF1                      (0x00000001)
#define DMA_IFCR_CTCIF1                     (0x00000002)
#define DMA_IFCR_CHTIF1                     (0x00000004)
#define DMA_IFCR_CTEIF1                     (0x00000008)
#define DMA_IFCR_CGIF2                      (0x00000010)
#define DMA_IFCR_CTCIF2                     (0x00000020)
#define DMA_IFCR_CHTIF2                     (0x00000040)
#define DMA_IFCR_CTEIF2                     (0x00000080)
#define DMA_IFCR_CGIF3                      (0x00000100)
#define DMA_IFCR_CTCIF3                     (0x00000200)
#define DMA_IFCR_CHTIF3                     (0x00000400)
#define DMA_IFCR_CTEIF3                     (0x00000800)
#define DMA_IFCR_CGIF4                      (0x00001000)
#define DMA_IFCR_CTCIF4                     (0x00002000)
#define DMA_IFCR_CHTIF4                     (0x00004000)
#define DMA_IFCR_CTEIF4                     (0x00008000)
#define DMA_IFCR_CGIF5                      (0x00010000)
#define DMA_IFCR_CTCIF5                     (0x00020000)
#define DMA_IFCR_CHTIF5                     (0x00040000)
#define DMA_IFCR_CTEIF5                     (0x00080000)
#define DMA_IFCR_CGIF6                      (0x00100000)
#define DMA_IFCR_CTCIF6                     (0x00200000)
#define DMA_IFCR_CHTIF6                     (0x00400000)
#define DMA_IFCR_CTEIF6                     (0x00800000)
#define DMA_IFCR_CGIF7                      (0x01000000)
#define DMA_IFCR_CTCIF7                     (0x02000000)
#define DMA_IFCR_CHTIF7                     (0x04000000)
#define DMA_IFCR_CTEIF7                     (0x08000000)

typedef struct {
	reg32_t CCR;
	reg32_t CNDTR;
	reg32_t CPAR;
	reg32_t CMAR;
} dma_chan_t;

/* DMA channel x configuration register */
#define DMA_CCR_EN                         	(0x0001)
#define DMA_CCR_TCIE                       	(0x0002)
#define DMA_CCR_HTIE                       	(0x0004)
#define DMA_CCR_TEIE                       	(0x0008)
#define DMA_CCR_DIR                        	(0x0010)
#define DMA_CCR_CIRC                       	(0x0020)
#define DMA_CCR_PINC                       	(0x0040)
#define DMA_CCR_MINC                       	(0x0080)

#define DMA_CCR_PSIZE                      	(0x0300)
#define DMA_CCR_PSIZE_0                    	(0x0100)
#define DMA_CCR_PSIZE_1                    	(0x0200)

#define DMA_CCR_MSIZE                      	(0x0C00)
#define DMA_CCR_MSIZE_0                    	(0x0400)
#define DMA_CCR_MSIZE_1                    	(0x0800)

#define DMA_CCR_PL                         	(0x3000)
#define DMA_CCR_PL_0                       	(0x1000)
#define DMA_CCR_PL_1                       	(0x2000)
#define DMA_CCR_MEM2MEM                    	(0x4000)

#define DMA_CNDTR_NDT                      	(0xFFFF)
#define DMA_CPAR_PA                        	(0xFFFFFFFF)
#define DMA_CMAR_MA                        	(0xFFFFFFFF)

/* dma channel initialization structure */
typedef struct {
	uint32_t peripheral_base_addr;
	uint32_t memory_base_addr;
	uint32_t dir;
	uint32_t buffer_size;
	uint32_t peripheral_inc;
	uint32_t memory_inc;
	uint32_t peripheral_data_size;
	uint32_t memory_data_size;
	uint32_t mode;
	uint32_t priority;
	uint32_t m2m;
} dma_init_t;

#define DMA_DIR_PERIPHERAL_DST             	(0x00000010)
#define DMA_DIR_PERIPHERAL_SRC             	(0x00000000)
#define DMA_PERIPHERALINC_ENABLE           	(0x00000040)
#define DMA_PERIPHERALINC_DISABLE          	(0x00000000)
#define DMA_MEMORYINC_ENABLE				(0x00000080)
#define DMA_MEMORYINC_DISABLE              	(0x00000000)
#define DMA_PERIPHERALDATASIZE_BYTE        	(0x00000000)
#define DMA_PERIPHERALDATASIZE_HWORD    	(0x00000100)
#define DMA_PERIPHERALDATASIZE_WORD        	(0x00000200)
#define DMA_MEMORYDATASIZE_BYTE            	(0x00000000)
#define DMA_MEMORYDATASIZE_HWORD        	(0x00000400)
#define DMA_MEMORYDATASIZE_WORD            	(0x00000800)
#define DMA_MODE_CIRCULAR                  	(0x00000020)
#define DMA_MODE_NORMAL                    	(0x00000000)
#define DMA_PRIORITY_VERYHIGH              	(0x00003000)
#define DMA_PRIORITY_HIGH                  	(0x00002000)
#define DMA_PRIORITY_MEDIUM                	(0x00001000)
#define DMA_PRIORITY_LOW                   	(0x00000000)
#define DMA_M2M_ENABLE                     	(0x00004000)
#define DMA_M2M_DISABLE                    	(0x00000000)

/* interrupts (per channel) */
#define DMA_IT_TC                          	(0x00000002)
#define DMA_IT_HT                          	(0x00000004)
#define DMA_IT_TE                          	(0x00000008)

/* status flags */
#define DMA_FLAG_GL1                      	(0x00000001)
#define DMA_FLAG_TC1                      	(0x00000002)
#define DMA_FLAG_HT1                      	(0x00000004)
#define DMA_FLAG_TE1                      	(0x00000008)
#define DMA_FLAG_GL2                      	(0x00000010)
#define DMA_FLAG_TC2                      	(0x00000020)
#define DMA_FLAG_HT2                      	(0x00000040)
#define DMA_FLAG_TE2                      	(0x00000080)
#define DMA_FLAG_GL3                      	(0x00000100)
#define DMA_FLAG_TC3                      	(0x00000200)
#define DMA_FLAG_HT3                      	(0x00000400)
#define DMA_FLAG_TE3                      	(0x00000800)
#define DMA_FLAG_GL4                      	(0x00001000)
#define DMA_FLAG_TC4                      	(0x00002000)
#define DMA_FLAG_HT4                      	(0x00004000)
#define DMA_FLAG_TE4                      	(0x00008000)
#define DMA_FLAG_GL5                      	(0x00010000)
#define DMA_FLAG_TC5                      	(0x00020000)
#define DMA_FLAG_HT5                      	(0x00040000)
#define DMA_FLAG_TE5                      	(0x00080000)
#define DMA_FLAG_GL6                      	(0x00100000)
#define DMA_FLAG_TC6                      	(0x00200000)
#define DMA_FLAG_HT6                      	(0x00400000)
#define DMA_FLAG_TE6                      	(0x00800000)
#define DMA_FLAG_GL7                      	(0x01000000)
#define DMA_FLAG_TC7                      	(0x02000000)
#define DMA_FLAG_HT7                      	(0x04000000)
#define DMA_FLAG_TE7                      	(0x08000000)

/* initialize dma channel */
void DMA_Init(dma_chan_t *DMAx, dma_init_t *init);
/* initialize structure */
void DMA_StructInit(dma_init_t *init);
/* dma command */
void DMA_Cmd(dma_chan_t *DMAx, int state);
/* set data counter */
void DMA_SetMemoryBuffer(dma_chan_t *DMAx, void *ptr, int size);
/* dma interrupt config */
void DMA_ITConfig(dma_chan_t* DMAx, uint32_t dma_it, int state);
/* get flag status */
int DMA_GetStatus(void);
/* get transfer number */
int DMA_GetTransferNumber(dma_chan_t *DMAx);
/* clear flag status */
void DMA_ClearFlag(uint32_t dma_flag);

#endif


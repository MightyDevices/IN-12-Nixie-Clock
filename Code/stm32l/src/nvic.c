/*
 * stm32_nvic.c
 *
 *  Created on: 14-06-2012
 *      Author: Tomek
 */

#include <stm32l/nvic.h>
#include <stm32l/scb.h>

/* current vector table */
static void *  vectors[128] __attribute__ ((section(".vectors_ram")));

/* default handler */
static void NVIC_Isr(void)
{
	SCB_Reset();
}

/* initialize nvic */
void NVIC_Init(void)
{
	int i;
	/* clear interrupts */
	NVIC->ICER[0] = 0xffffffff;
	NVIC->ICER[1] = 0x000007ff;
	NVIC->ICPR[0] = 0xffffffff;
	NVIC->ICPR[1] = 0x000007ff;

	for (i = 0; i < 0x0b; i++) {
		NVIC->IP[i] = 0xffffffff;
	}

	/* set vector table offset */
	NVIC_SetVectorTableOffset(NVIC_MEM_SRAM, (uint32_t)vectors);

	/* set exception vectors */
	for (i = 0; i < 16; i++) {
		NVIC_SetCoreExceptionVector(i, NVIC_Isr);
	}

	/* set interrupt vectors */
	for (i = 0; i < 44; i++) {
		NVIC_SetInterruptVector(i, NVIC_Isr);
	}

}

/* set vector table offset */
void NVIC_SetInterruptVector(int id, void *addr)
{
	vectors[id + 16] = addr;
}

/* set vector table offset */
void NVIC_SetCoreExceptionVector(int id, void *addr)
{
	vectors[id + 1] = addr;
}

/* set vector table offset */
void NVIC_SetVectorTableOffset(int mem_area, uint32_t offset)
{
	/* build up register */
	uint32_t reg = (mem_area << 29) | (offset << 8);
	/* set vector */
	SCB->VTOR = reg;
}

/* set interrupt group bits */
void NVIC_SetInterruptGrouping(int binary_point)
{
	SCB->AIRCR = (0x5fa << 16) | (binary_point << 8);
}

/* set interrupt priority */
void NVIC_SetInterruptPriority(int num, int priority)
{
	uint32_t temp = 0;
	int reg_offs = num / 4;
	int bit_offs = (num & 3) * 8;

	/* clear out bits */
	temp  = NVIC->IP[reg_offs] & ~(0xff << bit_offs);
	temp |= (priority << bit_offs);
	/* write back */
	NVIC->IP[reg_offs] = temp;
}

/* set exception priority */
void NVIC_SetExceptionPriority(int num, int priority)
{
	/* set priority */
	SCB->SHPR[num - 4] = priority;
}

/* enable interrupt */
void NVIC_EnableInterrupt(int num)
{
	int reg_num = num / 32;
	uint32_t reg = (1 << (num % 32));
	/* enable irq */
	NVIC->ISER[reg_num] = reg;
}

/* disable interrupt */
void NVIC_DisableInterrupt(int num)
{
	int reg_num = num / 32;
	uint32_t reg = (1 << (num % 32));
	/* disable irq */
	NVIC->ICER[reg_num] = reg;
}

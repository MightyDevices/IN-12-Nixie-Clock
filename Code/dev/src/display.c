/*
 * display.c
 *
 *  Created on: 18-12-2014
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/gpio.h>
#include <stm32l/timer.h>
#include <stm32l/nvic.h>
#include <sys/err.h>
#include <stdint.h>

/* pin mask for port a */
#define PORTA_MASK							0xf8fc
/* pin mask for port b */
#define PORTB_MASK							0x0019

/* pin mask for port a */
#define PORTA_ANODES_MASK					0x000c
/* pin mask for port b */
#define PORTB_ANODES_MASK					0x0018

/* pin mask for port a */
#define PORTA_CATHODES_MASK					0xf8f0
/* pin mask for port b */
#define PORTB_CATHODES_MASK					0x0001


/* digits definition */
static const uint32_t cathodes[] = {
	0x00010000, 0x00000800, 0x00001000, 0x00002000,
	0x00004000, 0x00008000, 0x00000010, 0x00000020,
	0x00000040, 0x00000080
};

/* anodes definition */
static const uint32_t anodes[] = {
	0x00080000, 0x00100000, 0x00000004, 0x00000008
};

/* current display */
static uint8_t display[4] = {0, 0, 0, 0};
/* shadowed display */
static uint8_t new_display[4];
/* counters */
static uint8_t anode_cnt, anode_mask;

/* anode timer */
static void Display_Tim6Isr(void)
{
	/* temporary variables */
	uint32_t pins;
	/* next anode counter value */
	uint8_t next = (anode_cnt + 1) & 0x3;

	/* clear interrupt */
	TIM6->SR = 0;

	/* clear current anodes */
	pins = anodes[anode_cnt];
	GPIOA->BSRR = (pins & 0x0000ffff) << 16;
	GPIOB->BSRR = (pins & 0xffff0000);

	/* disable old cathodes */
	pins = cathodes[display[anode_cnt]];
	GPIOA->BSRR = (pins & 0x0000ffff) << 16;
	GPIOB->BSRR = (pins & 0xffff0000);

	/* copy new display */
	display[0] = new_display[0]; display[1] = new_display[1];
	display[2] = new_display[2]; display[3] = new_display[3];

	/* set next cathodes */
	pins = cathodes[display[next]];
	GPIOA->BSRR = pins & 0xffff;
	GPIOB->BSRR = pins >> 16;

	/* anode masking */
	if ((anode_mask & (1 << next)) == 0) {
		/* set next anodes */
		pins = anodes[next];
		GPIOA->BSRR = pins & 0xffff;
		GPIOB->BSRR = pins >> 16;
	}

	/* next anode */
	anode_cnt = next;
}

/* initialize display */
int Display_Init(void)
{
	/* enable gpios */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN |
			RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOHEN;
	/* enable mux timer */
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

	/* configure pins for port a */
	GPIOA->MODER &= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4
			| GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7 |
			GPIO_MODER_MODER11 | GPIO_MODER_MODER12 | GPIO_MODER_MODER13 |
			GPIO_MODER_MODER14 | GPIO_MODER_MODER15);
	/* configure pins port b*/
	GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER3 |
			GPIO_MODER_MODER4);

	/* reset outputs */
	GPIOA->ODR &= ~PORTA_MASK;
	/* reset outputs */
	GPIOB->ODR &= ~PORTB_MASK;

	/* set as outputs */
	GPIOA->MODER |= GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
			GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 |
			GPIO_MODER_MODER7_0 | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 |
			GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
	/* set as outputs */
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER3_0 |
			GPIO_MODER_MODER4_0;


	/* timer configuration */
	TIM6->PSC = 4;
	/* 400Hz mux */
	TIM6->ARR = 10480/4;
	/* enable interrupt */
	TIM6->DIER |= TIM_DIER_UIE;

	/* prepare interrupt */
	NVIC_SetInterruptVector(NVIC_TIM6, Display_Tim6Isr);
	/* set priority */
	NVIC_SetInterruptPriority(NVIC_TIM6, 1);
	/* enable interrupt */
	NVIC_EnableInterrupt(NVIC_TIM6);

	/* enable timer */
	TIM6->CR1 |= TIM_CR1_CEN;

	/* report status */
	return EOK;
}

/* deinit display */
int Display_Deinit(void)
{
	/* disable timer */
	TIM6->CR1 &= ~TIM_CR1_CEN;
	/* disable pins port a */
	GPIOA->MODER |= GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4
			| GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7 |
			GPIO_MODER_MODER11 | GPIO_MODER_MODER12 | GPIO_MODER_MODER13 |
			GPIO_MODER_MODER14 | GPIO_MODER_MODER15;
	/* configure pins port b*/
	GPIOB->MODER |= GPIO_MODER_MODER0 | GPIO_MODER_MODER3 |
			GPIO_MODER_MODER4;
	/* disable mux timer */
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;

	/* report status */
	return EOK;
}

/* set display */
int Display_Set(uint8_t h, uint8_t m)
{
	/* assign display */
	new_display[0] = h / 10;
	new_display[1] = h % 10;
	new_display[2] = m / 10;
	new_display[3] = m % 10;

	/* report status */
	return EOK;
}

/* mask digits */
void Display_SetMask(uint8_t mask)
{
	/* set mask */
	anode_mask = mask;
}

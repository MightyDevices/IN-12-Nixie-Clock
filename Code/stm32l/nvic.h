/*
 * stm32_nvic.h
 *
 *  Created on: 14-06-2012
 *      Author: Tomek
 */

#ifndef STM32L_NVIC_H_
#define STM32L_NVIC_H_

#include <stm32l/stm32l.h>

/* register base */
#define NVIC_BASE							0xE000E100
/* nvic & scb */
#define NVIC								((nvic_t *) NVIC_BASE)

/* nvic registers */
typedef struct {
	reg32_t ISER[8];
	reg32_t RESERVED0[24];
	reg32_t ICER[8];
	reg32_t RSERVED1[24];
	reg32_t ISPR[8];
	reg32_t RESERVED2[24];
	reg32_t ICPR[8];
	reg32_t RESERVED3[24];
	reg32_t IABR[8];
	reg32_t RESERVED4[56];
	reg32_t IP[60];
	reg32_t RESERVED5[644];
	reg32_t STIR;
} __attribute__ ((packed)) nvic_t;

/* core exeptions */
#define NVIC_RESET							0
#define NVIC_NMI							1
#define NVIC_HARDFAULT						2
#define NVIC_MEMMANAGE						3
#define NVIC_BUSFAULT						4
#define NVIC_USAGEFAULT						5
#define NVIC_SVC							10
#define NVIC_DEBUGMON						11
#define NVIC_PENDSV							13
#define NVIC_SYSTICK						14

/* interrupt sources */
#define NVIC_WWDG							0
#define NVIC_PVD							1
#define NVIC_TAMPER							2
#define NVIC_RTC							3
#define NVIC_FLASH							4
#define NVIC_RCC							5
#define NVIC_EXTI0							6
#define NVIC_EXTI1							7
#define NVIC_EXTI2							8
#define NVIC_EXTI3							9
#define NVIC_EXTI4							10
#define NVIC_DMA1							11
#define NVIC_DMA2							12
#define NVIC_DMA3							13
#define NVIC_DMA4							14
#define NVIC_DMA5							15
#define NVIC_DMA6							16
#define NVIC_DMA7							17
#define NVIC_ADC							18
#define NVIC_USBHP							19
#define NVIC_USBLP							20
#define NVIC_DAC							21
#define NVIC_COMP							22
#define NVIC_EXTI5_9						23
#define NVIC_LCD							24
#define NVIC_TIM9							25
#define NVIC_TIM10							26
#define NVIC_TIM11							27
#define NVIC_TIM2							28
#define NVIC_TIM3							29
#define NVIC_TIM4							30
#define NVIC_I2C1EV							31
#define NVIC_I2C1ER							32
#define NVIC_I2C2EV							33
#define NVIC_I2C2ER							34
#define NVIC_SPI1							35
#define NVIC_SPI2							36
#define NVIC_USART1							37
#define NVIC_USART2							38
#define NVIC_USART3							39
#define NVIC_EXTI10_15						40
#define NVIC_RTCALARM						41
#define NVIC_USBWKUP						42
#define NVIC_TIM6							43
#define NVIC_TIM7							44

/* memory areas */
#define NVIC_MEM_FLASH						0
#define NVIC_MEM_SRAM						1

/* initialize nvic */
void NVIC_Init(void);
/* set vector table offset */
void NVIC_SetInterruptVector(int id, void *addr);
/* set vector table offset */
void NVIC_SetCoreExceptionVector(int id, void *addr);
/* set vector table offset */
void NVIC_SetVectorTableOffset(int mem_area, uint32_t offset);
/* enable interrupt */
void NVIC_EnableInterrupt(int num);
/* disable interrupt */
void NVIC_DisableInterrupt(int num);
/* set interrupt priority */
void NVIC_SetInterruptPriority(int num, int priority);
/* set exception priority */
void NVIC_SetExceptionPriority(int num, int priority);
/* set interrupt group bits */
void NVIC_SetInterruptGrouping(int bits);

#endif /* STM32_NVIC_H_ */

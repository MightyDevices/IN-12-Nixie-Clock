/*
 * stm32_gpio.h
 *
 *  Created on: 13-06-2012
 *      Author: Tomek
 */

#ifndef STM32L_GPIO_H_
#define STM32L_GPIO_H_

#include <stm32l/stm32l.h>

/* register base */
#define GPIOA_BASE							0x40020000
#define GPIOB_BASE							0x40020400
#define GPIOC_BASE							0x40020800
#define GPIOD_BASE							0x40020c00
#define GPIOE_BASE							0x40021000
#define GPIOF_BASE							0x40021800
#define GPIOG_BASE							0x40021c00
#define GPIOH_BASE							0x40021400

/* gpios */
#define GPIOA               				((gpio_t *) GPIOA_BASE)
#define GPIOB               				((gpio_t *) GPIOB_BASE)
#define GPIOC               				((gpio_t *) GPIOC_BASE)
#define GPIOD               				((gpio_t *) GPIOD_BASE)
#define GPIOE               				((gpio_t *) GPIOE_BASE)
#define GPIOH               				((gpio_t *) GPIOH_BASE)
#define GPIOF               				((gpio_t *) GPIOF_BASE)
#define GPIOG               				((gpio_t *) GPIOG_BASE)

/* gpio registers */
typedef struct {
	reg32_t MODER;
	reg16_t OTYPER;
	reg16_t RESERVED0;
	reg32_t OSPEEDR;
	reg32_t PUPDR;
	reg16_t IDR;
	reg16_t RESERVED1;
	reg16_t ODR;
	reg16_t RESERVED2;
	reg32_t BSRR;
	reg32_t LCKR;
	reg32_t AFRL;
	reg32_t AFRH;
	reg16_t BRR;
	reg16_t RESERVED3;
}__attribute__ ((packed)) gpio_t;

/* GPIO port mode register */
#define GPIO_MODER_MODER0          			(0x00000003)
#define GPIO_MODER_MODER0_0        			(0x00000001)
#define GPIO_MODER_MODER0_1        			(0x00000002)
#define GPIO_MODER_MODER1          			(0x0000000C)
#define GPIO_MODER_MODER1_0        			(0x00000004)
#define GPIO_MODER_MODER1_1        			(0x00000008)
#define GPIO_MODER_MODER2          			(0x00000030)
#define GPIO_MODER_MODER2_0        			(0x00000010)
#define GPIO_MODER_MODER2_1        			(0x00000020)
#define GPIO_MODER_MODER3          			(0x000000C0)
#define GPIO_MODER_MODER3_0        			(0x00000040)
#define GPIO_MODER_MODER3_1        			(0x00000080)
#define GPIO_MODER_MODER4          			(0x00000300)
#define GPIO_MODER_MODER4_0        			(0x00000100)
#define GPIO_MODER_MODER4_1        			(0x00000200)
#define GPIO_MODER_MODER5          			(0x00000C00)
#define GPIO_MODER_MODER5_0        			(0x00000400)
#define GPIO_MODER_MODER5_1        			(0x00000800)
#define GPIO_MODER_MODER6          			(0x00003000)
#define GPIO_MODER_MODER6_0        			(0x00001000)
#define GPIO_MODER_MODER6_1        			(0x00002000)
#define GPIO_MODER_MODER7          			(0x0000C000)
#define GPIO_MODER_MODER7_0        			(0x00004000)
#define GPIO_MODER_MODER7_1        			(0x00008000)
#define GPIO_MODER_MODER8          			(0x00030000)
#define GPIO_MODER_MODER8_0        			(0x00010000)
#define GPIO_MODER_MODER8_1        			(0x00020000)
#define GPIO_MODER_MODER9          			(0x000C0000)
#define GPIO_MODER_MODER9_0        			(0x00040000)
#define GPIO_MODER_MODER9_1        			(0x00080000)
#define GPIO_MODER_MODER10         			(0x00300000)
#define GPIO_MODER_MODER10_0       			(0x00100000)
#define GPIO_MODER_MODER10_1       			(0x00200000)
#define GPIO_MODER_MODER11         			(0x00C00000)
#define GPIO_MODER_MODER11_0       			(0x00400000)
#define GPIO_MODER_MODER11_1       			(0x00800000)
#define GPIO_MODER_MODER12         			(0x03000000)
#define GPIO_MODER_MODER12_0       			(0x01000000)
#define GPIO_MODER_MODER12_1       			(0x02000000)
#define GPIO_MODER_MODER13         			(0x0C000000)
#define GPIO_MODER_MODER13_0       			(0x04000000)
#define GPIO_MODER_MODER13_1       			(0x08000000)
#define GPIO_MODER_MODER14         			(0x30000000)
#define GPIO_MODER_MODER14_0       			(0x10000000)
#define GPIO_MODER_MODER14_1       			(0x20000000)
#define GPIO_MODER_MODER15         			(0xC0000000)
#define GPIO_MODER_MODER15_0       			(0x40000000)
#define GPIO_MODER_MODER15_1       			(0x80000000)

/* GPIO port output type register */
#define GPIO_OTYPER_OT_0           			(0x00000001)
#define GPIO_OTYPER_OT_1           			(0x00000002)
#define GPIO_OTYPER_OT_2           			(0x00000004)
#define GPIO_OTYPER_OT_3           			(0x00000008)
#define GPIO_OTYPER_OT_4           			(0x00000010)
#define GPIO_OTYPER_OT_5           			(0x00000020)
#define GPIO_OTYPER_OT_6           			(0x00000040)
#define GPIO_OTYPER_OT_7           			(0x00000080)
#define GPIO_OTYPER_OT_8           			(0x00000100)
#define GPIO_OTYPER_OT_9           			(0x00000200)
#define GPIO_OTYPER_OT_10          			(0x00000400)
#define GPIO_OTYPER_OT_11          			(0x00000800)
#define GPIO_OTYPER_OT_12          			(0x00001000)
#define GPIO_OTYPER_OT_13          			(0x00002000)
#define GPIO_OTYPER_OT_14          			(0x00004000)
#define GPIO_OTYPER_OT_15          			(0x00008000)

/* GPIO port output speed register */
#define GPIO_OSPEEDER_OSPEEDR0     			(0x00000003)
#define GPIO_OSPEEDER_OSPEEDR0_0   			(0x00000001)
#define GPIO_OSPEEDER_OSPEEDR0_1   			(0x00000002)
#define GPIO_OSPEEDER_OSPEEDR1     			(0x0000000C)
#define GPIO_OSPEEDER_OSPEEDR1_0   			(0x00000004)
#define GPIO_OSPEEDER_OSPEEDR1_1   			(0x00000008)
#define GPIO_OSPEEDER_OSPEEDR2     			(0x00000030)
#define GPIO_OSPEEDER_OSPEEDR2_0   			(0x00000010)
#define GPIO_OSPEEDER_OSPEEDR2_1   			(0x00000020)
#define GPIO_OSPEEDER_OSPEEDR3     			(0x000000C0)
#define GPIO_OSPEEDER_OSPEEDR3_0   			(0x00000040)
#define GPIO_OSPEEDER_OSPEEDR3_1   			(0x00000080)
#define GPIO_OSPEEDER_OSPEEDR4     			(0x00000300)
#define GPIO_OSPEEDER_OSPEEDR4_0   			(0x00000100)
#define GPIO_OSPEEDER_OSPEEDR4_1   			(0x00000200)
#define GPIO_OSPEEDER_OSPEEDR5    	 		(0x00000C00)
#define GPIO_OSPEEDER_OSPEEDR5_0   			(0x00000400)
#define GPIO_OSPEEDER_OSPEEDR5_1   			(0x00000800)
#define GPIO_OSPEEDER_OSPEEDR6     			(0x00003000)
#define GPIO_OSPEEDER_OSPEEDR6_0   			(0x00001000)
#define GPIO_OSPEEDER_OSPEEDR6_1   			(0x00002000)
#define GPIO_OSPEEDER_OSPEEDR7     			(0x0000C000)
#define GPIO_OSPEEDER_OSPEEDR7_0   			(0x00004000)
#define GPIO_OSPEEDER_OSPEEDR7_1   			(0x00008000)
#define GPIO_OSPEEDER_OSPEEDR8     			(0x00030000)
#define GPIO_OSPEEDER_OSPEEDR8_0   			(0x00010000)
#define GPIO_OSPEEDER_OSPEEDR8_1   			(0x00020000)
#define GPIO_OSPEEDER_OSPEEDR9     			(0x000C0000)
#define GPIO_OSPEEDER_OSPEEDR9_0   			(0x00040000)
#define GPIO_OSPEEDER_OSPEEDR9_1   			(0x00080000)
#define GPIO_OSPEEDER_OSPEEDR10    			(0x00300000)
#define GPIO_OSPEEDER_OSPEEDR10_0  			(0x00100000)
#define GPIO_OSPEEDER_OSPEEDR10_1  			(0x00200000)
#define GPIO_OSPEEDER_OSPEEDR11    			(0x00C00000)
#define GPIO_OSPEEDER_OSPEEDR11_0  			(0x00400000)
#define GPIO_OSPEEDER_OSPEEDR11_1 		 	(0x00800000)
#define GPIO_OSPEEDER_OSPEEDR12    			(0x03000000)
#define GPIO_OSPEEDER_OSPEEDR12_0  			(0x01000000)
#define GPIO_OSPEEDER_OSPEEDR12_1  			(0x02000000)
#define GPIO_OSPEEDER_OSPEEDR13    			(0x0C000000)
#define GPIO_OSPEEDER_OSPEEDR13_0  			(0x04000000)
#define GPIO_OSPEEDER_OSPEEDR13_1  			(0x08000000)
#define GPIO_OSPEEDER_OSPEEDR14    			(0x30000000)
#define GPIO_OSPEEDER_OSPEEDR14_0  			(0x10000000)
#define GPIO_OSPEEDER_OSPEEDR14_1  			(0x20000000)
#define GPIO_OSPEEDER_OSPEEDR15    			(0xC0000000)
#define GPIO_OSPEEDER_OSPEEDR15_0  			(0x40000000)
#define GPIO_OSPEEDER_OSPEEDR15_1  			(0x80000000)

/* GPIO port pu ll-up/pull-down register */
#define GPIO_PUPDR_PUPDR0          			(0x00000003)
#define GPIO_PUPDR_PUPDR0_0        			(0x00000001)
#define GPIO_PUPDR_PUPDR0_1        			(0x00000002)
#define GPIO_PUPDR_PUPDR1          			(0x0000000C)
#define GPIO_PUPDR_PUPDR1_0        			(0x00000004)
#define GPIO_PUPDR_PUPDR1_1        			(0x00000008)
#define GPIO_PUPDR_PUPDR2          			(0x00000030)
#define GPIO_PUPDR_PUPDR2_0        			(0x00000010)
#define GPIO_PUPDR_PUPDR2_1        			(0x00000020)
#define GPIO_PUPDR_PUPDR3          			(0x000000C0)
#define GPIO_PUPDR_PUPDR3_0        			(0x00000040)
#define GPIO_PUPDR_PUPDR3_1        			(0x00000080)
#define GPIO_PUPDR_PUPDR4          			(0x00000300)
#define GPIO_PUPDR_PUPDR4_0        			(0x00000100)
#define GPIO_PUPDR_PUPDR4_1        			(0x00000200)
#define GPIO_PUPDR_PUPDR5          			(0x00000C00)
#define GPIO_PUPDR_PUPDR5_0        			(0x00000400)
#define GPIO_PUPDR_PUPDR5_1        			(0x00000800)
#define GPIO_PUPDR_PUPDR6          			(0x00003000)
#define GPIO_PUPDR_PUPDR6_0        			(0x00001000)
#define GPIO_PUPDR_PUPDR6_1        			(0x00002000)
#define GPIO_PUPDR_PUPDR7          			(0x0000C000)
#define GPIO_PUPDR_PUPDR7_0        			(0x00004000)
#define GPIO_PUPDR_PUPDR7_1        			(0x00008000)
#define GPIO_PUPDR_PUPDR8          			(0x00030000)
#define GPIO_PUPDR_PUPDR8_0        			(0x00010000)
#define GPIO_PUPDR_PUPDR8_1        			(0x00020000)
#define GPIO_PUPDR_PUPDR9          			(0x000C0000)
#define GPIO_PUPDR_PUPDR9_0        			(0x00040000)
#define GPIO_PUPDR_PUPDR9_1        			(0x00080000)
#define GPIO_PUPDR_PUPDR10         			(0x00300000)
#define GPIO_PUPDR_PUPDR10_0       			(0x00100000)
#define GPIO_PUPDR_PUPDR10_1       			(0x00200000)
#define GPIO_PUPDR_PUPDR11         			(0x00C00000)
#define GPIO_PUPDR_PUPDR11_0       			(0x00400000)
#define GPIO_PUPDR_PUPDR11_1       			(0x00800000)
#define GPIO_PUPDR_PUPDR12         			(0x03000000)
#define GPIO_PUPDR_PUPDR12_0       			(0x01000000)
#define GPIO_PUPDR_PUPDR12_1       			(0x02000000)
#define GPIO_PUPDR_PUPDR13         			(0x0C000000)
#define GPIO_PUPDR_PUPDR13_0       			(0x04000000)
#define GPIO_PUPDR_PUPDR13_1       			(0x08000000)
#define GPIO_PUPDR_PUPDR14         			(0x30000000)
#define GPIO_PUPDR_PUPDR14_0       			(0x10000000)
#define GPIO_PUPDR_PUPDR14_1       			(0x20000000)
#define GPIO_PUPDR_PUPDR15         			(0xC0000000)
#define GPIO_PUPDR_PUPDR15_0       			(0x40000000)
#define GPIO_PUPDR_PUPDR15_1       			(0x80000000)

/* GPIO port input data register */
#define GPIO_IDR_IDR_0                      (0x00000001)
#define GPIO_IDR_IDR_1                      (0x00000002)
#define GPIO_IDR_IDR_2                      (0x00000004)
#define GPIO_IDR_IDR_3                      (0x00000008)
#define GPIO_IDR_IDR_4                      (0x00000010)
#define GPIO_IDR_IDR_5                      (0x00000020)
#define GPIO_IDR_IDR_6                      (0x00000040)
#define GPIO_IDR_IDR_7                      (0x00000080)
#define GPIO_IDR_IDR_8                      (0x00000100)
#define GPIO_IDR_IDR_9                      (0x00000200)
#define GPIO_IDR_IDR_10                     (0x00000400)
#define GPIO_IDR_IDR_11                     (0x00000800)
#define GPIO_IDR_IDR_12                     (0x00001000)
#define GPIO_IDR_IDR_13                     (0x00002000)
#define GPIO_IDR_IDR_14                     (0x00004000)
#define GPIO_IDR_IDR_15                     (0x00008000)

/* GPIO port output data register */
#define GPIO_ODR_ODR_0                      (0x00000001)
#define GPIO_ODR_ODR_1                      (0x00000002)
#define GPIO_ODR_ODR_2                      (0x00000004)
#define GPIO_ODR_ODR_3                      (0x00000008)
#define GPIO_ODR_ODR_4                      (0x00000010)
#define GPIO_ODR_ODR_5                      (0x00000020)
#define GPIO_ODR_ODR_6                      (0x00000040)
#define GPIO_ODR_ODR_7                      (0x00000080)
#define GPIO_ODR_ODR_8                      (0x00000100)
#define GPIO_ODR_ODR_9                      (0x00000200)
#define GPIO_ODR_ODR_10                     (0x00000400)
#define GPIO_ODR_ODR_11                     (0x00000800)
#define GPIO_ODR_ODR_12                     (0x00001000)
#define GPIO_ODR_ODR_13                     (0x00002000)
#define GPIO_ODR_ODR_14                     (0x00004000)
#define GPIO_ODR_ODR_15                     (0x00008000)

/* GPIO port bit set/reset register */
#define GPIO_BSRR_BS_0             			(0x00000001)
#define GPIO_BSRR_BS_1             			(0x00000002)
#define GPIO_BSRR_BS_2             			(0x00000004)
#define GPIO_BSRR_BS_3             			(0x00000008)
#define GPIO_BSRR_BS_4             			(0x00000010)
#define GPIO_BSRR_BS_5             			(0x00000020)
#define GPIO_BSRR_BS_6             			(0x00000040)
#define GPIO_BSRR_BS_7             			(0x00000080)
#define GPIO_BSRR_BS_8             			(0x00000100)
#define GPIO_BSRR_BS_9             			(0x00000200)
#define GPIO_BSRR_BS_10            			(0x00000400)
#define GPIO_BSRR_BS_11            			(0x00000800)
#define GPIO_BSRR_BS_12            			(0x00001000)
#define GPIO_BSRR_BS_13            			(0x00002000)
#define GPIO_BSRR_BS_14            			(0x00004000)
#define GPIO_BSRR_BS_15            			(0x00008000)
#define GPIO_BSRR_BR_0             			(0x00010000)
#define GPIO_BSRR_BR_1             			(0x00020000)
#define GPIO_BSRR_BR_2             			(0x00040000)
#define GPIO_BSRR_BR_3             			(0x00080000)
#define GPIO_BSRR_BR_4             			(0x00100000)
#define GPIO_BSRR_BR_5             			(0x00200000)
#define GPIO_BSRR_BR_6             			(0x00400000)
#define GPIO_BSRR_BR_7             			(0x00800000)
#define GPIO_BSRR_BR_8             			(0x01000000)
#define GPIO_BSRR_BR_9             			(0x02000000)
#define GPIO_BSRR_BR_10            			(0x04000000)
#define GPIO_BSRR_BR_11            			(0x08000000)
#define GPIO_BSRR_BR_12            			(0x10000000)
#define GPIO_BSRR_BR_13            			(0x20000000)
#define GPIO_BSRR_BR_14            			(0x40000000)
#define GPIO_BSRR_BR_15            			(0x80000000)

/* GPIO port configuration lock register */
#define GPIO_LCKR_LCK0             			(0x00000001)
#define GPIO_LCKR_LCK1             			(0x00000002)
#define GPIO_LCKR_LCK2             			(0x00000004)
#define GPIO_LCKR_LCK3             			(0x00000008)
#define GPIO_LCKR_LCK4             			(0x00000010)
#define GPIO_LCKR_LCK5             			(0x00000020)
#define GPIO_LCKR_LCK6             			(0x00000040)
#define GPIO_LCKR_LCK7             			(0x00000080)
#define GPIO_LCKR_LCK8             			(0x00000100)
#define GPIO_LCKR_LCK9             			(0x00000200)
#define GPIO_LCKR_LCK10            			(0x00000400)
#define GPIO_LCKR_LCK11            			(0x00000800)
#define GPIO_LCKR_LCK12            			(0x00001000)
#define GPIO_LCKR_LCK13            			(0x00002000)
#define GPIO_LCKR_LCK14            			(0x00004000)
#define GPIO_LCKR_LCK15            			(0x00008000)
#define GPIO_LCKR_LCKK             			(0x00010000)

/* GPIO alternate function low register */
#define GPIO_AFRL_AFRL0            			(0x0000000F)
#define GPIO_AFRL_AFRL1            			(0x000000F0)
#define GPIO_AFRL_AFRL2            			(0x00000F00)
#define GPIO_AFRL_AFRL3            			(0x0000F000)
#define GPIO_AFRL_AFRL4            			(0x000F0000)
#define GPIO_AFRL_AFRL5            			(0x00F00000)
#define GPIO_AFRL_AFRL6            			(0x0F000000)
#define GPIO_AFRL_AFRL7            			(0xF0000000)

/* GPIO alternate function high register */
#define GPIO_AFRH_AFRH8            			(0x0000000F)
#define GPIO_AFRH_AFRH9            			(0x000000F0)
#define GPIO_AFRH_AFRH10           			(0x00000F00)
#define GPIO_AFRH_AFRH11           			(0x0000F000)
#define GPIO_AFRH_AFRH12           			(0x000F0000)
#define GPIO_AFRH_AFRH13           			(0x00F00000)
#define GPIO_AFRH_AFRH14           			(0x0F000000)
#define GPIO_AFRH_AFRH15           			(0xF0000000)

/* pin init structure */
typedef struct {
	uint32_t pins;
	uint32_t mode;
	uint32_t pupd;
	uint32_t speed;
	uint32_t otype;
	uint32_t af;
} gpio_init_t;

/* gpio alternate functions */
#define GPIO_AF_SYSTEM						0
#define GPIO_AF_TIM2						1
#define GPIO_AF_TIM3_4						2
#define GPIO_AF_TIM9_10_11					3
#define GPIO_AF_I2C							4
#define GPIO_AF_SPI							5
#define GPIO_AF_USART						7
#define GPIO_AF_USBFS						10
#define GPIO_AF_LCD							11
#define GPIO_AF_RI							14
#define GPIO_AF_SYSTEM2						15

/* gpio function */
#define GPIO_INPUT							0
#define GPIO_OUTPUT							1
#define GPIO_ALT							2
#define GPIO_ANALOG							3

/* gpio output type */
#define GPIO_OT_PP							0
#define GPIO_OT_OD							1

/* gpio pullup type */
#define GPIO_P_NOPULL						0
#define GPIO_P_PULLUP						1
#define GPIO_P_PULLDN						2

/* gpio speed */
#define GPIO_OS_400K						0
#define GPIO_OS_2M							1
#define GPIO_OS_10M							2
#define GPIO_OS_40M							3

/* gpio pins */
#define GPIO_P0								(1 << 0)
#define GPIO_P1								(1 << 1)
#define GPIO_P2								(1 << 2)
#define GPIO_P3								(1 << 3)
#define GPIO_P4								(1 << 4)
#define GPIO_P5								(1 << 5)
#define GPIO_P6								(1 << 6)
#define GPIO_P7								(1 << 7)
#define GPIO_P8								(1 << 8)
#define GPIO_P9								(1 << 9)
#define GPIO_P10							(1 << 10)
#define GPIO_P11							(1 << 11)
#define GPIO_P12							(1 << 12)
#define GPIO_P13							(1 << 13)
#define GPIO_P14							(1 << 14)
#define GPIO_P15							(1 << 15)
#define GPIO_PALL							(0xffff)


/* gpio deinit */
void GPIO_Deinit(gpio_t *GPIOx);
/* Fills each GPIO_InitStruct member with its default value. */
void GPIO_StructInit(gpio_init_t *init);
/* initialize pins */
void GPIO_Init(gpio_t *GPIOx, gpio_init_t *init);
/* get pin state */
uint16_t GPIO_GetPins(gpio_t *GPIOx);
/* set pin state */
void GPIO_SetPins(gpio_t *GPIOx, uint16_t pins);
/* clear gpio pins */
void GPIO_ClearPins(gpio_t *GPIOx, uint16_t pins);

#endif /* STM32_GPIO_H_ */

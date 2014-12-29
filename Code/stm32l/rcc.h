/*
 * stm32_rcc.h
 *
 *  Created on: 13-06-2012
 *      Author: Tomek
 */

#ifndef STM32L_RCC_H_
#define STM32L_RCC_H_

#include <stm32l/stm32l.h>

/* register base */
#define RCC_BASE							(0x40023800)
/* rcc itself */
#define RCC                 				((rcc_t *) RCC_BASE)

/* rcc registers  */
typedef struct {
	reg32_t CR;
	reg32_t ICSCR;
	reg32_t CFGR;
	reg32_t CIR;
	reg32_t AHBRSTR;
	reg32_t APB2RSTR;
	reg32_t APB1RSTR;
	reg32_t AHBENR;
	reg32_t APB2ENR;
	reg32_t APB1ENR;
	reg32_t AHBLPENR;
	reg32_t APB2LPENR;
	reg32_t APB1LPENR;
	reg32_t CSR;
} __attribute__ ((packed)) rcc_t;

/* clock control register */
#define RCC_CR_HSION                        (0x00000001)
#define RCC_CR_HSIRDY                       (0x00000002)
#define RCC_CR_MSION                        (0x00000100)
#define RCC_CR_MSIRDY                       (0x00000200)
#define RCC_CR_HSEON                        (0x00010000)
#define RCC_CR_HSERDY                       (0x00020000)
#define RCC_CR_HSEBYP                       (0x00040000)
#define RCC_CR_PLLON                        (0x01000000)
#define RCC_CR_PLLRDY                       (0x02000000)
#define RCC_CR_CSSON                        (0x10000000)
#define RCC_CR_RTCPRE                       (0x60000000)
#define RCC_CR_RTCPRE_0                     (0x20000000)
#define RCC_CR_RTCPRE_1                     (0x40000000)

/* internal clock sources calibration register */
#define RCC_ICSCR_HSICAL                    (0x000000FF)
#define RCC_ICSCR_HSITRIM                   (0x00001F00)
#define RCC_ICSCR_MSIRANGE                  (0x0000E000)
#define RCC_ICSCR_MSIRANGE_0                (0x00000000)
#define RCC_ICSCR_MSIRANGE_1                (0x00002000)
#define RCC_ICSCR_MSIRANGE_2                (0x00004000)
#define RCC_ICSCR_MSIRANGE_3                (0x00006000)
#define RCC_ICSCR_MSIRANGE_4                (0x00008000)
#define RCC_ICSCR_MSIRANGE_5                (0x0000A000)
#define RCC_ICSCR_MSIRANGE_6                (0x0000C000)
#define RCC_ICSCR_MSICAL                    (0x00FF0000)
#define RCC_ICSCR_MSITRIM                   (0xFF000000)

/* clock configuration register */
#define RCC_CFGR_SW                         (0x00000003)
#define RCC_CFGR_SW_0                       (0x00000001)
#define RCC_CFGR_SW_1                       (0x00000002)
#define RCC_CFGR_SW_MSI                     (0x00000000)
#define RCC_CFGR_SW_HSI                     (0x00000001)
#define RCC_CFGR_SW_HSE                     (0x00000002)
#define RCC_CFGR_SW_PLL                     (0x00000003)
#define RCC_CFGR_SWS                        (0x0000000C)
#define RCC_CFGR_SWS_0                      (0x00000004)
#define RCC_CFGR_SWS_1                      (0x00000008)
#define RCC_CFGR_SWS_MSI                    (0x00000000)
#define RCC_CFGR_SWS_HSI                    (0x00000004)
#define RCC_CFGR_SWS_HSE                    (0x00000008)
#define RCC_CFGR_SWS_PLL                    (0x0000000C)
#define RCC_CFGR_HPRE                       (0x000000F0)
#define RCC_CFGR_HPRE_0                     (0x00000010)
#define RCC_CFGR_HPRE_1                     (0x00000020)
#define RCC_CFGR_HPRE_2                     (0x00000040)
#define RCC_CFGR_HPRE_3                     (0x00000080)
#define RCC_CFGR_HPRE_DIV1                  (0x00000000)
#define RCC_CFGR_HPRE_DIV2                  (0x00000080)
#define RCC_CFGR_HPRE_DIV4                  (0x00000090)
#define RCC_CFGR_HPRE_DIV8                  (0x000000A0)
#define RCC_CFGR_HPRE_DIV16                 (0x000000B0)
#define RCC_CFGR_HPRE_DIV64                 (0x000000C0)
#define RCC_CFGR_HPRE_DIV128                (0x000000D0)
#define RCC_CFGR_HPRE_DIV256                (0x000000E0)
#define RCC_CFGR_HPRE_DIV512                (0x000000F0)
#define RCC_CFGR_PPRE1                      (0x00000700)
#define RCC_CFGR_PPRE1_0                    (0x00000100)
#define RCC_CFGR_PPRE1_1                    (0x00000200)
#define RCC_CFGR_PPRE1_2                    (0x00000400)
#define RCC_CFGR_PPRE1_DIV1                 (0x00000000)
#define RCC_CFGR_PPRE1_DIV2                 (0x00000400)
#define RCC_CFGR_PPRE1_DIV4                 (0x00000500)
#define RCC_CFGR_PPRE1_DIV8                 (0x00000600)
#define RCC_CFGR_PPRE1_DIV16                (0x00000700)
#define RCC_CFGR_PPRE2                      (0x00003800)
#define RCC_CFGR_PPRE2_0                    (0x00000800)
#define RCC_CFGR_PPRE2_1                    (0x00001000)
#define RCC_CFGR_PPRE2_2                    (0x00002000)
#define RCC_CFGR_PPRE2_DIV1                 (0x00000000)
#define RCC_CFGR_PPRE2_DIV2                 (0x00002000)
#define RCC_CFGR_PPRE2_DIV4                 (0x00002800)
#define RCC_CFGR_PPRE2_DIV8                 (0x00003000)
#define RCC_CFGR_PPRE2_DIV16                (0x00003800)
#define RCC_CFGR_PLLSRC                     (0x00010000)
#define RCC_CFGR_PLLSRC_HSI                 (0x00000000)
#define RCC_CFGR_PLLSRC_HSE                 (0x00010000)
#define RCC_CFGR_PLLMUL                     (0x003C0000)
#define RCC_CFGR_PLLMUL_0                   (0x00040000)
#define RCC_CFGR_PLLMUL_1                   (0x00080000)
#define RCC_CFGR_PLLMUL_2                   (0x00100000)
#define RCC_CFGR_PLLMUL_3                   (0x00200000)
#define RCC_CFGR_PLLMUL3                    (0x00000000)
#define RCC_CFGR_PLLMUL4                    (0x00040000)
#define RCC_CFGR_PLLMUL6                    (0x00080000)
#define RCC_CFGR_PLLMUL8                    (0x000C0000)
#define RCC_CFGR_PLLMUL12                   (0x00100000)
#define RCC_CFGR_PLLMUL16                   (0x00140000)
#define RCC_CFGR_PLLMUL24                   (0x00180000)
#define RCC_CFGR_PLLMUL32                   (0x001C0000)
#define RCC_CFGR_PLLMUL48                   (0x00200000)
#define RCC_CFGR_PLLDIV                     (0x00C00000)
#define RCC_CFGR_PLLDIV_0                   (0x00400000)
#define RCC_CFGR_PLLDIV_1                   (0x00800000)
#define RCC_CFGR_PLLDIV1                    (0x00000000)
#define RCC_CFGR_PLLDIV2                    (0x00400000)
#define RCC_CFGR_PLLDIV3                    (0x00800000)
#define RCC_CFGR_PLLDIV4                    (0x00C00000)
#define RCC_CFGR_MCOSEL                     (0x07000000)
#define RCC_CFGR_MCOSEL_0                   (0x01000000)
#define RCC_CFGR_MCOSEL_1                   (0x02000000)
#define RCC_CFGR_MCOSEL_2                   (0x04000000)
#define RCC_CFGR_MCO_NOCLOCK                (0x00000000)
#define RCC_CFGR_MCO_SYSCLK                 (0x01000000)
#define RCC_CFGR_MCO_HSI                    (0x02000000)
#define RCC_CFGR_MCO_MSI                    (0x03000000)
#define RCC_CFGR_MCO_HSE                    (0x04000000)
#define RCC_CFGR_MCO_PLL                    (0x05000000)
#define RCC_CFGR_MCO_LSI                    (0x06000000)
#define RCC_CFGR_MCO_LSE                    (0x07000000)
#define RCC_CFGR_MCOPRE                     (0x70000000)
#define RCC_CFGR_MCOPRE_0                   (0x10000000)
#define RCC_CFGR_MCOPRE_1                   (0x20000000)
#define RCC_CFGR_MCOPRE_2                   (0x40000000)
#define RCC_CFGR_MCO_DIV1                   (0x00000000)
#define RCC_CFGR_MCO_DIV2                   (0x10000000)
#define RCC_CFGR_MCO_DIV4                   (0x20000000)
#define RCC_CFGR_MCO_DIV8                   (0x30000000)
#define RCC_CFGR_MCO_DIV16                  (0x40000000)

/* clock interrupt register */
#define RCC_CIR_LSIRDYF                     (0x00000001)
#define RCC_CIR_LSERDYF                     (0x00000002)
#define RCC_CIR_HSIRDYF                     (0x00000004)
#define RCC_CIR_HSERDYF                     (0x00000008)
#define RCC_CIR_PLLRDYF                     (0x00000010)
#define RCC_CIR_MSIRDYF                     (0x00000020)
#define RCC_CIR_LSECSS                      (0x00000040)
#define RCC_CIR_CSSF                        (0x00000080)
#define RCC_CIR_LSIRDYIE                    (0x00000100)
#define RCC_CIR_LSERDYIE                    (0x00000200)
#define RCC_CIR_HSIRDYIE                    (0x00000400)
#define RCC_CIR_HSERDYIE                    (0x00000800)
#define RCC_CIR_PLLRDYIE                    (0x00001000)
#define RCC_CIR_MSIRDYIE                    (0x00002000)
#define RCC_CIR_LSECSSIE                    (0x00004000)
#define RCC_CIR_LSIRDYC                     (0x00010000)
#define RCC_CIR_LSERDYC                     (0x00020000)
#define RCC_CIR_HSIRDYC                     (0x00040000)
#define RCC_CIR_HSERDYC                     (0x00080000)
#define RCC_CIR_PLLRDYC                     (0x00100000)
#define RCC_CIR_MSIRDYC                     (0x00200000)
#define RCC_CIR_LSECSSC                     (0x00400000)
#define RCC_CIR_CSSC                        (0x00800000)

/* AHB peripheral reset register */
#define RCC_AHBRSTR_GPIOARST                (0x00000001)
#define RCC_AHBRSTR_GPIOBRST                (0x00000002)
#define RCC_AHBRSTR_GPIOCRST                (0x00000004)
#define RCC_AHBRSTR_GPIODRST                (0x00000008)
#define RCC_AHBRSTR_GPIOERST                (0x00000010)
#define RCC_AHBRSTR_GPIOHRST                (0x00000020)
#define RCC_AHBRSTR_GPIOFRST                (0x00000040)
#define RCC_AHBRSTR_GPIOGRST                (0x00000080)
#define RCC_AHBRSTR_CRCRST                  (0x00001000)
#define RCC_AHBRSTR_FLITFRST                (0x00008000)
#define RCC_AHBRSTR_DMA1RST                 (0x01000000)
#define RCC_AHBRSTR_DMA2RST                 (0x02000000)
#define RCC_AHBRSTR_AESRST                  (0x08000000)
#define RCC_AHBRSTR_FSMCRST                 (0x40000000)

/* APB2 peripheral reset register */
#define RCC_APB2RSTR_SYSCFGRST              (0x00000001)
#define RCC_APB2RSTR_TIM9RST                (0x00000004)
#define RCC_APB2RSTR_TIM10RST               (0x00000008)
#define RCC_APB2RSTR_TIM11RST               (0x00000010)
#define RCC_APB2RSTR_ADC1RST                (0x00000200)
#define RCC_APB2RSTR_SDIORST                (0x00000800)
#define RCC_APB2RSTR_SPI1RST                (0x00001000)
#define RCC_APB2RSTR_USART1RST              (0x00004000)

/* APB1 peripheral reset register */
#define RCC_APB1RSTR_TIM2RST                (0x00000001)
#define RCC_APB1RSTR_TIM3RST                (0x00000002)
#define RCC_APB1RSTR_TIM4RST                (0x00000004)
#define RCC_APB1RSTR_TIM5RST                (0x00000008)
#define RCC_APB1RSTR_TIM6RST                (0x00000010)
#define RCC_APB1RSTR_TIM7RST                (0x00000020)
#define RCC_APB1RSTR_LCDRST                 (0x00000200)
#define RCC_APB1RSTR_WWDGRST                (0x00000800)
#define RCC_APB1RSTR_SPI2RST                (0x00004000)
#define RCC_APB1RSTR_SPI3RST                (0x00008000)
#define RCC_APB1RSTR_USART2RST              (0x00020000)
#define RCC_APB1RSTR_USART3RST              (0x00040000)
#define RCC_APB1RSTR_UART4RST               (0x00080000)
#define RCC_APB1RSTR_UART5RST               (0x00100000)
#define RCC_APB1RSTR_I2C1RST                (0x00200000)
#define RCC_APB1RSTR_I2C2RST                (0x00400000)
#define RCC_APB1RSTR_USBRST                 (0x00800000)
#define RCC_APB1RSTR_PWRRST                 (0x10000000)
#define RCC_APB1RSTR_DACRST                 (0x20000000)
#define RCC_APB1RSTR_COMPRST                (0x80000000)

/* AHB peripheral clock enable register */
#define RCC_AHBENR_GPIOAEN                  (0x00000001)
#define RCC_AHBENR_GPIOBEN                  (0x00000002)
#define RCC_AHBENR_GPIOCEN                  (0x00000004)
#define RCC_AHBENR_GPIODEN                  (0x00000008)
#define RCC_AHBENR_GPIOEEN                  (0x00000010)
#define RCC_AHBENR_GPIOHEN                  (0x00000020)
#define RCC_AHBENR_GPIOFEN                  (0x00000040)
#define RCC_AHBENR_GPIOGEN                  (0x00000080)
#define RCC_AHBENR_CRCEN                    (0x00001000)
#define RCC_AHBENR_FLITFEN                  (0x00008000)
#define RCC_AHBENR_DMA1EN                   (0x01000000)
#define RCC_AHBENR_DMA2EN                   (0x02000000)
#define RCC_AHBENR_AESEN                    (0x08000000)
#define RCC_AHBENR_FSMCEN                   (0x40000000)

/* APB2 peripheral clock enable register */
#define RCC_APB2ENR_SYSCFGEN                (0x00000001)
#define RCC_APB2ENR_TIM9EN                  (0x00000004)
#define RCC_APB2ENR_TIM10EN                 (0x00000008)
#define RCC_APB2ENR_TIM11EN                 (0x00000010)
#define RCC_APB2ENR_ADC1EN                  (0x00000200)
#define RCC_APB2ENR_SDIOEN                  (0x00000800)
#define RCC_APB2ENR_SPI1EN                  (0x00001000)
#define RCC_APB2ENR_USART1EN                (0x00004000)

/* APB1 peripheral clock enable register */
#define RCC_APB1ENR_TIM2EN                  (0x00000001)
#define RCC_APB1ENR_TIM3EN                  (0x00000002)
#define RCC_APB1ENR_TIM4EN                  (0x00000004)
#define RCC_APB1ENR_TIM5EN                  (0x00000008)
#define RCC_APB1ENR_TIM6EN                  (0x00000010)
#define RCC_APB1ENR_TIM7EN                  (0x00000020)
#define RCC_APB1ENR_LCDEN                   (0x00000200)
#define RCC_APB1ENR_WWDGEN                  (0x00000800)
#define RCC_APB1ENR_SPI2EN                  (0x00004000)
#define RCC_APB1ENR_SPI3EN                  (0x00008000)
#define RCC_APB1ENR_USART2EN                (0x00020000)
#define RCC_APB1ENR_USART3EN                (0x00040000)
#define RCC_APB1ENR_UART4EN                 (0x00080000)
#define RCC_APB1ENR_UART5EN                 (0x00100000)
#define RCC_APB1ENR_I2C1EN                  (0x00200000)
#define RCC_APB1ENR_I2C2EN                  (0x00400000)
#define RCC_APB1ENR_USBEN                   (0x00800000)
#define RCC_APB1ENR_PWREN                   (0x10000000)
#define RCC_APB1ENR_DACEN                   (0x20000000)
#define RCC_APB1ENR_COMPEN                  (0x80000000)

/* AHB peripheral clock enable in low power mode register */
#define RCC_AHBLPENR_GPIOALPEN              (0x00000001)
#define RCC_AHBLPENR_GPIOBLPEN              (0x00000002)
#define RCC_AHBLPENR_GPIOCLPEN              (0x00000004)
#define RCC_AHBLPENR_GPIODLPEN              (0x00000008)
#define RCC_AHBLPENR_GPIOELPEN              (0x00000010)
#define RCC_AHBLPENR_GPIOHLPEN              (0x00000020)
#define RCC_AHBLPENR_GPIOFLPEN              (0x00000040)
#define RCC_AHBLPENR_GPIOGLPEN              (0x00000080)
#define RCC_AHBLPENR_CRCLPEN                (0x00001000)
#define RCC_AHBLPENR_FLITFLPEN              (0x00008000)
#define RCC_AHBLPENR_SRAMLPEN               (0x00010000)
#define RCC_AHBLPENR_DMA1LPEN               (0x01000000)
#define RCC_AHBLPENR_DMA2LPEN               (0x02000000)
#define RCC_AHBLPENR_AESLPEN                (0x08000000)
#define RCC_AHBLPENR_FSMCLPEN               (0x40000000)

/* APB2 peripheral clock enable in low power mode register */
#define RCC_APB2LPENR_SYSCFGLPEN            (0x00000001)
#define RCC_APB2LPENR_TIM9LPEN              (0x00000004)
#define RCC_APB2LPENR_TIM10LPEN             (0x00000008)
#define RCC_APB2LPENR_TIM11LPEN             (0x00000010)
#define RCC_APB2LPENR_ADC1LPEN              (0x00000200)
#define RCC_APB2LPENR_SDIOLPEN              (0x00000800)
#define RCC_APB2LPENR_SPI1LPEN              (0x00001000)
#define RCC_APB2LPENR_USART1LPEN            (0x00004000)

/* APB1 peripheral clock enable in low power mode register */
#define RCC_APB1LPENR_TIM2LPEN              (0x00000001)
#define RCC_APB1LPENR_TIM3LPEN              (0x00000002)
#define RCC_APB1LPENR_TIM4LPEN              (0x00000004)
#define RCC_APB1LPENR_TIM5LPEN              (0x00000008)
#define RCC_APB1LPENR_TIM6LPEN              (0x00000010)
#define RCC_APB1LPENR_TIM7LPEN              (0x00000020)
#define RCC_APB1LPENR_LCDLPEN               (0x00000200)
#define RCC_APB1LPENR_WWDGLPEN              (0x00000800)
#define RCC_APB1LPENR_SPI2LPEN              (0x00004000)
#define RCC_APB1LPENR_SPI3LPEN              (0x00008000)
#define RCC_APB1LPENR_USART2LPEN            (0x00020000)
#define RCC_APB1LPENR_USART3LPEN            (0x00040000)
#define RCC_APB1LPENR_UART4LPEN             (0x00080000)
#define RCC_APB1LPENR_UART5LPEN             (0x00100000)
#define RCC_APB1LPENR_I2C1LPEN              (0x00200000)
#define RCC_APB1LPENR_I2C2LPEN              (0x00400000)
#define RCC_APB1LPENR_USBLPEN               (0x00800000)
#define RCC_APB1LPENR_PWRLPEN               (0x10000000)
#define RCC_APB1LPENR_DACLPEN               (0x20000000)
#define RCC_APB1LPENR_COMPLPEN              (0x80000000)

/* control/status register */
#define RCC_CSR_LSION                      	(0x00000001)
#define RCC_CSR_LSIRDY                     	(0x00000002)
#define RCC_CSR_LSEON                      	(0x00000100)
#define RCC_CSR_LSERDY                     	(0x00000200)
#define RCC_CSR_LSEBYP                     	(0x00000400)
#define RCC_CSR_LSECSSON                   	(0x00000800)
#define RCC_CSR_LSECSSD                    	(0x00001000)
#define RCC_CSR_RTCSEL                     	(0x00030000)
#define RCC_CSR_RTCSEL_0                   	(0x00010000)
#define RCC_CSR_RTCSEL_1                   	(0x00020000)
#define RCC_CSR_RTCSEL_NOCLOCK             	(0x00000000)
#define RCC_CSR_RTCSEL_LSE                 	(0x00010000)
#define RCC_CSR_RTCSEL_LSI                 	(0x00020000)
#define RCC_CSR_RTCSEL_HSE                 	(0x00030000)
#define RCC_CSR_RTCEN                      	(0x00400000)
#define RCC_CSR_RTCRST                     	(0x00800000)
#define RCC_CSR_RMVF                       	(0x01000000)
#define RCC_CSR_OBLRSTF                    	(0x02000000)
#define RCC_CSR_PINRSTF                    	(0x04000000)
#define RCC_CSR_PORRSTF                    	(0x08000000)
#define RCC_CSR_SFTRSTF                    	(0x10000000)
#define RCC_CSR_IWDGRSTF                   	(0x20000000)
#define RCC_CSR_WWDGRSTF                   	(0x40000000)
#define RCC_CSR_LPWRRSTF                   	(0x80000000)

/* get clocks frequency */
typedef struct {
	uint32_t sysclk_frequency;
	uint32_t hclk_frequency;
	uint32_t pclk1_frequency;
	uint32_t pclk2_frequency;
	/* prescalers */
	uint8_t ahb_pres, apb1_pres, apb2_pres;
} rcc_clocks_t;

/* MSI frequencies */
#define MSI_FREQ_65K536						(0x00)
#define MSI_FREQ_131K072					(0x01)
#define MSI_FREQ_262K144					(0x02)
#define MSI_FREQ_524K288					(0x03)
#define MSI_FREQ_1M048						(0x04)
#define MSI_FREQ_2M097						(0x05)
#define MSI_FREQ_4M194						(0x06)

/* ahb peripheral */
#define AHB_GPIOA							(1 << 0)
#define AHB_GPIOB							(1 << 1)
#define AHB_GPIOC							(1 << 2)
#define AHB_GPIOD							(1 << 3)
#define AHB_GPIOE							(1 << 4)
#define AHB_GPIOH							(1 << 5)
#define AHB_GPIOF							(1 << 6)
#define AHB_GPIOG							(1 << 7)
#define AHB_CRC								(1 << 12)
#define AHB_FILTF							(1 << 15)
#define AHB_DMA1							(1 << 24)
#define AHB_DMA2							(1 << 25)
#define AHB_AES								(1 << 27)
#define AHB_FSMC							(1 << 30)

/* apb2 peripheral */
#define APB2_SYSCFG							(1 << 0)
#define APB2_TIM9							(1 << 2)
#define APB2_TIM10							(1 << 3)
#define APB2_TIM11							(1 << 4)
#define APB2_ADC1							(1 << 9)
#define APB2_SDIO							(1 << 11)
#define APB2_SPI1							(1 << 12)
#define APB2_USART1							(1 << 14)

/* apb1 peripheral */
#define APB1_TIM2							(1 << 0)
#define APB1_TIM3							(1 << 1)
#define APB1_TIM4							(1 << 2)
#define APB1_TIM5							(1 << 3)
#define APB1_TIM6							(1 << 4)
#define APB1_TIM7							(1 << 5)
#define APB1_LCD							(1 << 9)
#define APB1_WWDG							(1 << 11)
#define APB1_SPI2							(1 << 14)
#define APB1_SPI3							(1 << 15)
#define APB1_USART2							(1 << 17)
#define APB1_USART3							(1 << 18)
#define APB1_USART4							(1 << 19)
#define APB1_USART5							(1 << 20)
#define APB1_I2C1							(1 << 21)
#define APB1_I2C2							(1 << 22)
#define APB1_USB							(1 << 23)
#define APB1_PWR							(1 << 28)
#define APB1_DAC							(1 << 29)
#define APB1_COMP							(1 << 31)

/* ahb dividers */
#define AHB_DIV1							(0x00)
#define AHB_DIV2							(0x08)
#define AHB_DIV4							(0x09)
#define AHB_DIV8							(0x0a)
#define AHB_DIV16							(0x0b)
#define AHB_DIV64							(0x0c)
#define AHB_DIV128							(0x0d)
#define AHB_DIV256							(0x0e)
#define AHB_DIV512							(0x0f)

/* apb dividers */
#define APB_DIV1							(0x00)
#define APB_DIV2							(0x04)
#define APB_DIV4							(0x05)
#define APB_DIV8							(0x06)
#define APB_DIV16							(0x07)

/* clock sources */
#define SYSCLK_MSI							(0x00)
#define SYSCLK_HSI							(0x01)
#define SYSCLK_HSE							(0x02)
#define SYSCLK_PLL							(0x03)

/* rtc clock sources */
#define RCC_RTCCLKSOURCE_LSE             	RCC_CSR_RTCSEL_LSE
#define RCC_RTCCLKSOURCE_LSI             	RCC_CSR_RTCSEL_LSI
#define RCC_RTCCLKSOURCE_HSE_DIV2        	RCC_CSR_RTCSEL_HSE
#define RCC_RTCCLKSOURCE_HSE_DIV4        	(RCC_CSR_RTCSEL_HSE | RCC_CR_RTCPRE_0)
#define RCC_RTCCLKSOURCE_HSE_DIV8        	(RCC_CSR_RTCSEL_HSE | RCC_CR_RTCPRE_1)
#define RCC_RTCCLKSOURCE_HSE_DIV16       	(RCC_CSR_RTCSEL_HSE | RCC_CR_RTCPRE)

/* pll source */
#define RCC_PLLSOURCE_HSI                	0x000000
#define RCC_PLLSOURCE_HSE                	0x010000

/* pll multipliers */
#define RCC_PLLMUL_3                     	0x00000000
#define RCC_PLLMUL_4                     	0x00040000
#define RCC_PLLMUL_6                     	0x00080000
#define RCC_PLLMUL_8                     	0x000C0000
#define RCC_PLLMUL_12                    	0x00100000
#define RCC_PLLMUL_16                    	0x00140000
#define RCC_PLLMUL_24                    	0x00180000
#define RCC_PLLMUL_32                    	0x001C0000
#define RCC_PLLMUL_48                    	0x00200000

/* pll divider */
#define RCC_PLLDIV_2                     	0x00400000
#define RCC_PLLDIV_3                     	0x00800000
#define RCC_PLLDIV_4                     	0x00C00000

/* mco source */
#define RCC_MCOSOURCE_NOCLOCK            	0x00000000
#define RCC_MCOSOURCE_SYSCLK             	0x01000000
#define RCC_MCOSOURCE_HSI                	0x02000000
#define RCC_MCOSOURCE_MSI               	0x03000000
#define RCC_MCOSOURCE_HSE                	0x04000000
#define RCC_MCOSOURCE_PLLCLK             	0x05000000
#define RCC_MCOSOURCE_LSI                	0x06000000
#define RCC_MCOSOURCE_LSE                	0x07000000

/* mco div */
#define RCC_MCODIV_1                     	0x00000000
#define RCC_MCODIV_2                    	0x10000000
#define RCC_MCODIV_4                     	0x20000000
#define RCC_MCODIV_8                     	0x30000000
#define RCC_MCODIV_16                    	0x40000000

/* Resets the RCC clock configuration to the default reset state. */
void RCC_DeInit(void);
/* Configures the Internal Multi Speed oscillator (MSI) clock range. */
void RCC_MSIRangeConfig(int rng);
/* enable disable msi */
void RCC_MSICmd(int state);
/* get status of msi clock */
int RCC_GetMSIStatus(void);
/* enable/disable hsi */
void RCC_HSICmd(int state);
/* get status of hsi clock */
int RCC_GetHSIStatus(void);
/* enable/disable hse */
void RCC_HSECmd(int state);
/* get status of hse clock */
int RCC_GetHSEStatus(void);
/* enable/disable lsi */
void RCC_LSICmd(int state);
/* get status of hsi clock */
int RCC_GetLSIStatus(void);
/* enable/disable pll */
void RCC_PLLCmd(int state);
/* get status of pll clock */
int RCC_GetPLLStatus(void);

/* select clock */
void RCC_SYSCLKConfig(uint32_t source);

/* enables or disables ahb clock */
void RCC_AHBPeriphClockCmd(uint32_t ahb_periph, int state);
/* enables or disables apb2 clock */
void RCC_APB1PeriphClockCmd(uint32_t apb1_periph, int state);
/* enables or disables apb2 clock */
void RCC_APB2PeriphClockCmd(uint32_t apb2_periph, int state);

/* enables or disables ahb clock */
void RCC_AHBPeriphClockLPCmd(uint32_t ahb_periph, int state);
/* enables or disables apb2 clock */
void RCC_APB1PeriphClockLPCmd(uint32_t apb1_periph, int state);
/* enables or disables apb2 clock */
void RCC_APB2PeriphClockLPCmd(uint32_t apb2_periph, int state);

/* enables or disables ahb clock */
void RCC_AHBPeriphResetCmd(uint32_t ahb_periph, int state);
/* enables or disables apb2 clock */
void RCC_APB1PeriphResetCmd(uint32_t apb1_periph, int state);
/* enables or disables apb2 clock */
void RCC_APB2PeriphResetCmd(uint32_t apb2_periph, int state);

/* Configures the AHB clock (HCLK). */
void RCC_HCLKConfig(uint32_t sysclk);
/* Configures the AHB clock (HCLK). */
void RCC_PCLK1Config(uint32_t pclk);
/* Configures the AHB clock (HCLK). */
void RCC_PCLK2Config(uint32_t pclk);

/* get clocks freq */
void RCC_GetClocksFreq(rcc_clocks_t* clocks);

/* select rtc clock source */
void RCC_RTCCLKConfig(uint32_t source);
/* Enables or disables the RTC clock.*/
void RCC_RTCCLKCmd(int state);
/* Forces or releases the RTC peripheral and associated resources reset */
void RCC_RTCResetCmd(int state);

/* configure pll */
void RCC_PLLConfig(uint32_t pll_source, uint32_t mul, uint32_t div);
/* configure mco output */
void RCC_MCOConfig(uint32_t source, uint32_t div);
/* adjust hci trimming */
void RCC_AdjustHSICalibrationValue(uint8_t hsi_trimming);
/* adjust msi trimming */
void RCC_AdjustMSICalibrationValue(uint8_t msi_trimming);

#endif /* STM32_RCC_H_ */

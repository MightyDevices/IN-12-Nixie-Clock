/*
 * stm32_rcc.c
 *
 *  Created on: 13-06-2012
 *      Author: Tomek
 */

#include <stm32l/stm32l.h>
#include <stm32l/rcc.h>

/* default hsi value */
#define HSI_VALUE							16000000
/* default hse value */
#define HSE_VALUE							16000000

/* Resets the RCC clock configuration to the default reset state. */
void RCC_DeInit(void)
{
	/* set reset values */
	RCC->CR = 0x00000100;
	/* Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], MCOSEL[2:0] and
	* MCOPRE[2:0] bits */
	RCC->CFGR &= (uint32_t)0x88FFC00C;
	/* Reset HSION, HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t)0xEEFEFFFE;
	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t)0xFFFBFFFF;
	/* Reset PLLSRC, PLLMUL[3:0] and PLLDIV[1:0] bits */
	RCC->CFGR &= (uint32_t)0xFF02FFFF;
	/* Disable all interrupts */
	RCC->CIR = 0x00000000;
}

/* Configures the Internal Multi Speed oscillator (MSI) clock range. */
void RCC_MSIRangeConfig(int rng)
{
	uint32_t tmpreg;
	/* Check the parameters */
	tmpreg = RCC->ICSCR;
	/* Clear MSIRANGE[2:0] bits */
	tmpreg &= ~0x0000E000;
	/* Set the MSIRANGE[2:0] bits according to RCC_MSIRange value */
	tmpreg |= (uint32_t)(rng << 13);
	/* Store the new value */
	RCC->ICSCR = tmpreg;
}

/* enable disable msi */
void RCC_MSICmd(int state)
{
	if (state) {
		RCC->CR |= RCC_CR_MSION;
	} else  {
		RCC->CR &= ~RCC_CR_MSION;
	}
}

/* get status of msi clock */
int RCC_GetMSIStatus(void)
{
	int rc = 0;
	/* check msion bit */
	if (RCC->CR & RCC_CR_MSIRDY) {
		rc = 1;
	}

	return rc;
}

/* enable/disable hsi */
void RCC_HSICmd(int state)
{
	/* Check the parameters */
	if (state) {
		RCC->CR |= RCC_CR_HSION;
	} else {
		RCC->CR &= ~RCC_CR_HSION;
	}
}

/* get status of hsi clock */
int RCC_GetHSIStatus(void)
{
	int rc = 0;
	/* check hsion bit */
	if (RCC->CR & RCC_CR_HSIRDY) {
		rc = 1;
	}

	return rc;
}

/* enable/disable hsi */
void RCC_HSECmd(int state)
{
	/* Check the parameters */
	if (state) {
		RCC->CR |= RCC_CR_HSEON;
	} else {
		RCC->CR &= ~RCC_CR_HSEON;
	}
}

/* get status of hse clock */
int RCC_GetHSEStatus(void)
{
	int rc = 0;
	/* check hsion bit */
	if (RCC->CR & RCC_CR_HSERDY) {
		rc = 1;
	}

	return rc;
}

/* enable/disable lsi */
void RCC_LSICmd(int state)
{
	/* Check the parameters */
	if (state) {
		RCC->CSR |= RCC_CSR_LSION;
	} else {
		RCC->CSR &= ~RCC_CSR_LSION;
	}
}

/* get status of hsi clock */
int RCC_GetLSIStatus(void)
{
	int rc = 0;
	/* check hsion bit */
	if (RCC->CSR & RCC_CSR_LSIRDY) {
		rc = 1;
	}

	return rc;
}

/* enable/disable pll */
void RCC_PLLCmd(int state)
{
	/* Check the parameters */
	if (state) {
		RCC->CR |= RCC_CR_PLLON;
	} else {
		RCC->CR &= ~RCC_CR_PLLON;
	}
}

/* get status of pll clock */
int RCC_GetPLLStatus(void)
{
	int rc = 0;
	/* check hsion bit */
	if (RCC->CR & RCC_CR_PLLRDY) {
		rc = 1;
	}

	return rc;
}

/* select clock */
void RCC_SYSCLKConfig(uint32_t source)
{
	uint32_t tmpreg = 0;
	/* read */
	tmpreg = RCC->CFGR;
	/* Clear SW[1:0] bits */
	tmpreg &= ~0x3;
	/* Set SW[1:0] bits according to RCC_SYSCLKSource value */
	tmpreg |= source;
	/* Store the new value */
	RCC->CFGR = tmpreg;

	/* wait for status to be set */
	do {
		tmpreg = (RCC->CFGR & RCC_CFGR_SWS) >> 2;
	} while (tmpreg != source);
}

/* enables or disables ahb clock */
void RCC_AHBPeriphClockCmd(uint32_t ahb_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->AHBENR |= ahb_periph;
	} else {
		RCC->AHBENR &= ~ahb_periph;
	}
}

/* enables or disables apb2 clock */
void RCC_APB1PeriphClockCmd(uint32_t apb1_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->APB1ENR |= apb1_periph;
	} else {
		RCC->APB1ENR &= ~apb1_periph;
	}
}

/* enables or disables apb2 clock */
void RCC_APB2PeriphClockCmd(uint32_t apb2_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->APB2ENR |= apb2_periph;
	} else {
		RCC->APB2ENR &= ~apb2_periph;
	}
}

/* enables or disables ahb clock */
void RCC_AHBPeriphClockLPCmd(uint32_t ahb_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->AHBLPENR |= ahb_periph;
	} else {
		RCC->AHBLPENR &= ~ahb_periph;
	}
}

/* enables or disables apb2 clock */
void RCC_APB1PeriphClockLPCmd(uint32_t apb1_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->APB1LPENR |= apb1_periph;
	} else {
		RCC->APB1LPENR &= ~apb1_periph;
	}
}

/* enables or disables apb2 clock */
void RCC_APB2PeriphClockLPCmd(uint32_t apb2_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->APB2LPENR |= apb2_periph;
	} else {
		RCC->APB2LPENR &= ~apb2_periph;
	}
}

/* enables or disables ahb clock */
void RCC_AHBPeriphResetCmd(uint32_t ahb_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->AHBRSTR |= ahb_periph;
	} else {
		RCC->AHBRSTR &= ~ahb_periph;
	}
}

/* enables or disables apb2 clock */
void RCC_APB1PeriphResetCmd(uint32_t apb1_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->APB1RSTR |= apb1_periph;
	} else {
		RCC->APB1RSTR &= ~apb1_periph;
	}
}

/* enables or disables apb2 clock */
void RCC_APB2PeriphResetCmd(uint32_t apb2_periph, int state)
{
	/* Check the parameters */
	if (state) {
		RCC->APB2RSTR |= apb2_periph;
	} else {
		RCC->APB2RSTR &= ~apb2_periph;
	}
}

/* Configures the AHB clock (HCLK). */
void RCC_HCLKConfig(uint32_t sysclk)
{
	uint32_t tmpreg = 0;
	/* Check the parameters */
	tmpreg = RCC->CFGR;
	/* Clear HPRE[3:0] bits */
	tmpreg &= ~0x000000F0;
	/* Set HPRE[3:0] bits according to RCC_SYSCLK value */
	tmpreg |= sysclk << 4;
	/* Store the new value */
	RCC->CFGR = tmpreg;
}

/* Configures the AHB clock (HCLK). */
void RCC_PCLK1Config(uint32_t pclk)
{
	uint32_t tmpreg = 0;
	/* Check the parameters */
	tmpreg = RCC->CFGR;
	/* Clear HPRE[3:0] bits */
	tmpreg &= ~0x00000700;
	/* Set HPRE[3:0] bits according to RCC_SYSCLK value */
	tmpreg |= pclk << 8;
	/* Store the new value */
	RCC->CFGR = tmpreg;
}

/* Configures the AHB clock (HCLK). */
void RCC_PCLK2Config(uint32_t pclk)
{
	uint32_t tmpreg = 0;
	/* Check the parameters */
	tmpreg = RCC->CFGR;
	/* Clear HPRE[3:0] bits */
	tmpreg &= ~0x00003800;
	/* Set HPRE[3:0] bits according to RCC_SYSCLK value */
	tmpreg |= pclk << 11;
	/* Store the new value */
	RCC->CFGR = tmpreg;
}

/* get clocks freq */
void RCC_GetClocksFreq(rcc_clocks_t* clocks)
{
	uint32_t pres, tmp;
	/* get clock source */
	uint32_t source = (RCC->CFGR & RCC_CFGR_SWS) >> 2;
	/* prescalers */
	const uint8_t apbahb_pres[16] = {0, 0, 0, 0, 1, 2, 3, 4,
			1, 2, 3, 4, 6, 7, 8, 9};
	/* pll multipliers */
	const uint8_t pll_mul[9] = {3, 4, 6, 8, 12, 16, 24, 32, 48};

	switch (source) {
	/* msi */
	case SYSCLK_MSI : {
		/* extract range */
		uint32_t msi_range = (RCC->ICSCR >> 13) & 0x7;
		/* set frequency */
		clocks->sysclk_frequency = 32768 * (1 << (msi_range + 1));
	} break;
	/* hsi */
	case SYSCLK_HSI : {
		/* hsi frequency */
		clocks->sysclk_frequency = 16000000;
	} break;
	/* hse */
	case SYSCLK_HSE : {
		/* hse frequency */
		clocks->sysclk_frequency = HSE_VALUE;
	} break;
	/* pll */
	case SYSCLK_PLL : {
		/* get multiplier and divider */
		uint32_t mul = RCC->CFGR & RCC_CFGR_PLLMUL;
		uint32_t div = RCC->CFGR & RCC_CFGR_PLLDIV;
		/* convert */
		mul = pll_mul[(mul >> 18)];
		/* get divides */
		div = (div >> 22) + 1;
		/* get pll source */
		uint8_t pll_source = RCC->CFGR & RCC_CFGR_PLLSRC;
		/* hsi? */
		if (!pll_source) {
			clocks->sysclk_frequency = (16000000 * mul) / div;
		/* hse */
		} else {
			clocks->sysclk_frequency = (HSE_VALUE * mul) / div;
		}
	} break;
	}

	/* Get HCLK prescaler */
	tmp = (RCC->CFGR >> 4) & 0xf;
	pres = apbahb_pres[(RCC->CFGR >> 4) & 0xf];
	/* hclk clock frequency */
	clocks->hclk_frequency = clocks->sysclk_frequency >> pres;
	/* store prescaler information */
	clocks->ahb_pres = tmp;

	/* Get PCLK1 prescaler */
	tmp = (RCC->CFGR >> 8) & 0x7;
	pres = apbahb_pres[tmp];
	/* pclk1 clock frequency */
	clocks->pclk1_frequency = clocks->hclk_frequency >> pres;
	/* store prescaler information */
	clocks->apb1_pres = tmp;

	/* Get PCLK2 prescaler */
	tmp = (RCC->CFGR >> 11) & 0x7;
	pres = apbahb_pres[tmp];
	/* pclk2 clock frequency */
	clocks->pclk2_frequency = clocks->hclk_frequency >> pres;
	/* store prescaler information */
	clocks->apb2_pres = tmp;
}

/* select rtc clock source */
void RCC_RTCCLKConfig(uint32_t source)
{
	uint32_t tmpreg = 0;

	if ((source & RCC_CSR_RTCSEL_HSE) == RCC_CSR_RTCSEL_HSE) {
		/* If HSE is selected as RTC clock source, configure HSE division factor for RTC clock */
		tmpreg = RCC->CR;
		/* Clear RTCPRE[1:0] bits */
		tmpreg &= ~RCC_CR_RTCPRE;
		/* Configure HSE division factor for RTC clock */
		tmpreg |= (source & RCC_CR_RTCPRE);
		/* Store the new value */
		RCC->CR = tmpreg;
	}

	RCC->CSR &= ~RCC_CSR_RTCSEL;
	/* Select the RTC clock source */
	RCC->CSR |= (source & RCC_CSR_RTCSEL);
}

/* Enables or disables the RTC clock.*/
void RCC_RTCCLKCmd(int state)
{
	if (state) {
		RCC->CSR |= RCC_CSR_RTCEN;
	} else {
		RCC->CSR &= ~RCC_CSR_RTCEN;
	}
}

/* Forces or releases the RTC peripheral and associated resources reset */
void RCC_RTCResetCmd(int state)
{
	if (state) {
		RCC->CSR |= RCC_CSR_RTCRST;
	} else {
		RCC->CSR &= ~RCC_CSR_RTCRST;
	}
}

/* configure pll */
void RCC_PLLConfig(uint32_t pll_source, uint32_t mul, uint32_t div)
{
	/* get cfgr value */
	uint32_t cfgr = RCC->CFGR & ~0x00ff0000;
	/* set bits */
	cfgr |= pll_source | mul | div;
	/* rewrite */
	RCC->CFGR |= cfgr;
}

/* configure mco output */
void RCC_MCOConfig(uint32_t source, uint32_t div)
{
	/* get cfgr value */
	uint32_t cfgr = RCC->CFGR & ~0xff000000;
	/* set bits */
	cfgr |= source | div;
	/* rewrite */
	RCC->CFGR |= cfgr;
}

/* adjust hci trimming */
void RCC_AdjustHSICalibrationValue(uint8_t hsi_trimming)
{
	uint32_t tmpreg = 0;

	tmpreg = RCC->ICSCR;
	/* Clear HSITRIM[4:0] bits */
	tmpreg &= ~RCC_ICSCR_HSITRIM;
	/* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
	tmpreg |= (uint32_t)(hsi_trimming & 0x1f) << 8;
	/* Store the new value */
	RCC->ICSCR = tmpreg;
}

/* adjust msi trimming */
void RCC_AdjustMSICalibrationValue(uint8_t msi_trimming)
{
	uint32_t tmpreg = 0;

	tmpreg = RCC->ICSCR;
	/* Clear HSITRIM[4:0] bits */
	tmpreg &= ~RCC_ICSCR_MSITRIM;
	/* Set the HSITRIM[4:0] bits according to MSICalibrationValue value */
	tmpreg |= (uint32_t)(msi_trimming & 0xff) << 24;
	/* Store the new value */
	RCC->ICSCR = tmpreg;
}

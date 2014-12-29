/*
 * lcd.c
 *
 *  Created on: 28-09-2013
 *      Author: Tomek
 */

#include <stm32l/lcd.h>
#include <stm32l/rcc.h>
#include <stm32l/stm32l.h>

/* deinitialize lcd */
void LCD_Deinit(void)
{
  /* Enable LCD reset state */
  RCC_APB1PeriphResetCmd(APB1_LCD, ENABLE);
  /* Release LCD from reset state */
  RCC_APB1PeriphResetCmd(APB1_LCD, DISABLE);
}

/* initialize lcd */
void LCD_Init(lcd_init_t *init)
{
	/* set configuration register */
	LCD->CR &= 0xFFFFFF81;
	LCD->CR |= init->duty | init->bias | init->voltage_source;

	/* frame control register */
	LCD->FCR &= 0xFC03FFFF;
	LCD->FCR |= init->prescaler | init->divider;
	/* this is needed */
	LCD_WaitForSynchro();
}

/* initialize structure */
void LCD_StructInit(lcd_init_t *init)
{
	/* initialize structure members */
	init->prescaler = LCD_PRESCALER_1;
	init->divider = LCD_DIVIDER_31;
	init->duty = LCD_DUTY_1_4;
	init->bias = LCD_BIAS_1_3;
	init->voltage_source = LCD_VOLSOURCE_INTERNAL;
}

/* enable /disable lcd */
void LCD_Cmd(int enable)
{
	/* map to bit */
	bitband_t cr_en = BITBAND_PERIPH(&LCD->CR, 0);
	/* enable / disable */
	*cr_en = enable;
}

/* wait for synchronization */
void LCD_WaitForSynchro(void)
{
	/* map to bit */
	bitband_t sr_fcrsf = BITBAND_PERIPH(&LCD->SR, 5);
	/* Loop until FCRSF flag is set */
	while (!*sr_fcrsf) {
	}
}

/* mux segment command */
void LCD_MuxSegmentCmd(int enable)
{
	/* map to bit */
	bitband_t cr_muxseg = BITBAND_PERIPH(&LCD->CR, 7);
	/* set */
	*cr_muxseg = 1;
}

/* pulse on duration configuration */
void LCD_PulseOnDurationConfig(uint32_t duration)
{
	LCD->FCR &= ~0x00000070;
  	LCD->FCR |= duration;
}

/* configure dead time */
void LCD_DeadTimeConfig(uint32_t dead_time)
{
	LCD->FCR &= ~0x00000780;
	LCD->FCR |= dead_time;
}

/* configure blinking */
void LCD_BlinkConfig(uint32_t mode, uint32_t frequency)
{
	LCD->FCR &= ~0x0003E000;
	LCD->FCR |= mode | frequency;
}

/* configure contrast */
void LCD_ContrastConfig(uint32_t contrast)
{
	LCD->FCR &= ~0x00001C00;
	LCD->FCR |= contrast;
}

/* write */
void LCD_Write(uint32_t reg, uint32_t data)
{
	LCD->RAM[reg] = data;
}

/* update display request */
void LCD_UpdateDisplayRequest(void)
{
	/* map to bit */
	bitband_t sr_udr = BITBAND_PERIPH(&LCD->SR, 2);
	/* set */
	*sr_udr = 1;
}

/* get status register */
uint32_t LCD_GetStatus(void)
{
	return LCD->SR;
}

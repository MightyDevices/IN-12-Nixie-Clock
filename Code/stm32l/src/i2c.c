/*
 * stm32_i2c.c
 *
 *  Created on: 21-11-2012
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/i2c.h>

/* initialize i2c unit */
void I2C_Init(i2c_t *I2Cx, i2c_init_t *init)
{
	uint16_t tmpreg = 0, freqrange = 0;
	uint16_t result = 0x04;
	uint32_t pclk1 = 8000000;
	rcc_clocks_t rcc_clocks;

/*---------------------------- I2Cx CR2 Configuration ------------------------*/
	/* Get the I2Cx CR2 value */
	tmpreg = I2Cx->CR2;
	/* Clear frequency FREQ[5:0] bits */
	tmpreg &= 0xFFC0;
	/* Get pclk1 frequency value */
	RCC_GetClocksFreq(&rcc_clocks);
	pclk1 = rcc_clocks.pclk1_frequency;

	/* Set frequency bits depending on pclk1 value */
	freqrange = (uint16_t)(pclk1 / 1000000);
	tmpreg |= freqrange;
	/* Write to I2Cx CR2 */
	I2Cx->CR2 = tmpreg;

/*---------------------------- I2Cx CCR Configuration ------------------------*/
	/* Disable the selected I2C peripheral to configure TRISE */
	I2Cx->CR1 &= ~(1 << 0);
	/* Reset tmpreg value */
	/* Clear F/S, DUTY and CCR[11:0] bits */
	tmpreg = 0;

	/* Configure speed in standard mode */
	if (init->clock_speed <= 100000) {
		/* Standard mode speed calculate */
		result = (uint16_t)(pclk1 / (init->clock_speed << 1));
		/* Test if CCR value is under 0x4*/
		if (result < 0x04) {
			/* Set minimum allowed value */
			result = 0x04;
		}
		/* Set speed value for standard mode */
		tmpreg |= result;
		/* Set Maximum Rise Time for standard mode */
		I2Cx->TRISE = freqrange + 1;
		/* Configure speed in fast mode */
	} else {
		if (init->duty_cycle == I2C_DUTY_2) {
			/* Fast mode speed calculate: Tlow/Thigh = 2 */
			result = (uint16_t)(pclk1 / (init->clock_speed * 3));
		} else {
			/* Fast mode speed calculate: Tlow/Thigh = 16/9 */
			result = (uint16_t)(pclk1 / (init->clock_speed * 25));
			/* Set DUTY bit */
			result |= I2C_DUTY_16_9;
		}
		/* Test if CCR value is under 0x1*/
		if ((result & 0x0FFF) == 0) {
			/* Set minimum allowed value */
			result |= (uint16_t)0x0001;
		}
		/* Set speed value and set F/S bit for fast mode */
		tmpreg |= (uint16_t)(result | 0x8000);
		/* Set Maximum Rise Time for fast mode */
		I2Cx->TRISE = (uint16_t)(((freqrange * (uint16_t)300) /
				(uint16_t)1000) + (uint16_t)1);
	}

	/* Write to I2Cx CCR */
	I2Cx->CCR = tmpreg;
	/* Enable the selected I2C peripheral */
	I2Cx->CR1 |= 0x0001;

/*---------------------------- I2Cx CR1 Configuration ------------------------*/
	/* Get the I2Cx CR1 value */
	tmpreg = I2Cx->CR1;
	/* Clear ACK, SMBTYPE and  SMBUS bits */
	tmpreg &= 0xFBF5;
	/* Configure I2Cx: mode and acknowledgement */
	/* Set SMBTYPE and SMBUS bits according to I2C_Mode value */
	/* Set ACK bit according to I2C_Ack value */
	tmpreg |= (uint16_t)((uint32_t)init->mode | init->ack);
	/* Write to I2Cx CR1 */
	I2Cx->CR1 = tmpreg;

/*---------------------------- I2Cx OAR1 Configuration -----------------------*/
	/* Set I2Cx Own Address1 and acknowledged address */
	I2Cx->OAR1 = (init->ack_address | init->own_address1);
}

/* initialize structure */
void I2C_StructInit(i2c_init_t *init)
{
	/* initialize the I2C_ClockSpeed member */
	init->clock_speed = 5000;
	/* Initialize the I2C_Mode member */
	init->mode = I2C_MODE_I2C;
	/* Initialize the I2C_DutyCycle member */
	init->duty_cycle = I2C_DUTY_2;
	/* Initialize the I2C_OwnAddress1 member */
	init->own_address1 = 0;
	/* Initialize the I2C_Ack member */
	init->ack = I2C_ACK_DISABLE;
	/* Initialize the I2C_AcknowledgedAddress member */
	init->ack_address= I2C_ACK_ADDR_7B;
}

/* reset i2c */
void I2C_ResetCmd(i2c_t *I2Cx, int state)
{
	if (state) {
		/* Enable the selected I2C peripheral reset*/
		I2Cx->CR1 |= (1 << 15);
	} else {
		/* Disable the selected I2C peripheral reset */
		I2Cx->CR1 &= ~(1 << 15);
	}
}

/* i2c command */
void I2C_Cmd(i2c_t *I2Cx, int state)
{
	if (state) {
		/* Enable the selected I2C peripheral */
		I2Cx->CR1 |= (1 << 0);
	} else {
		/* Disable the selected I2C peripheral */
		I2Cx->CR1 &= ~(1 << 0);
	}
}

/* dma command */
void I2C_DMACmd(i2c_t *I2Cx, int state)
{
	if (state) {
		/* Enable the selected I2C peripheral */
		I2Cx->CR2 |= (1 << 11);
	} else {
		/* Disable the selected I2C peripheral */
		I2Cx->CR2 &= ~(1 << 11);
	}
}

/* last dma transfer? */
void I2C_DMALastTransferCmd(i2c_t *I2Cx, int state)
{
	if (state) {
		/* Enable the selected I2C peripheral */
		I2Cx->CR2 |= (1 << 12);
	} else {
		/* Disable the selected I2C peripheral */
		I2Cx->CR2 &= ~(1 << 12);
	}
}

/* generate start condition */
void I2C_GenerateSTART(i2c_t *I2Cx, int state)
{
	if (state) {
		I2Cx->CR1 |= (1 << 8);
	} else {
		I2Cx->CR1 &= ~(1 << 8);
	}
}

/* generate stop condition */
void I2C_GenerateSTOP(i2c_t *I2Cx, int state)
{
	if (state) {
		I2Cx->CR1 |= (1 << 9);
	} else {
		I2Cx->CR1 &= ~(1 << 9);
	}
}

/* configure interrupt */
void I2C_ITConfig(i2c_t *I2Cx, uint16_t interrupt, int state)
{
	if (state != DISABLE) {
		I2Cx->CR2 |= interrupt;
	} else {
		I2Cx->CR2 &= (uint16_t)~interrupt;
	}
}

/* send data */
void I2C_SendData(i2c_t *I2Cx, uint8_t data)
{
	/* Write in the DR register the data to be sent */
	I2Cx->DR = data;
}

/* get data */
uint8_t I2C_ReceiveData(i2c_t *I2Cx)
{
	/* Return the data in the DR register */
	return (uint8_t)I2Cx->DR;
}


/* get last event */
uint32_t I2C_GetLastEvent(i2c_t *I2Cx)
{
	uint32_t lastevent = 0;
	uint32_t flag1 = 0, flag2 = 0;

	/* Read the I2Cx status register */
	flag1 = I2Cx->SR1;
	flag2 = I2Cx->SR2;
	flag2 = flag2 << 16;

	/* Get the last event value from I2C status register */
	lastevent = (flag1 | flag2) & 0x00FFFFFF;
	/* Return status */
	return lastevent;
}

/* ack enable */
void I2C_AcknowledgeConfig(i2c_t *I2Cx, int state)
{
	/* Check the parameters */
	if (state != DISABLE) {
		/* Enable the acknowledgement */
		I2Cx->CR1 |= (1 << 10);
	} else {
		/* Disable the acknowledgement */
		I2Cx->CR1 &= (uint16_t)~((1 << 10));
	}
}

/* get status */
uint16_t I2C_GetStatus1(i2c_t *I2Cx)
{
	return I2Cx->SR1;
}

/* reset error flag  */
uint16_t I2C_ResetErrorFlags(i2c_t *I2Cx, uint16_t flags)
{
	return I2Cx->SR1 &= ~flags;
}

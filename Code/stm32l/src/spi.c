/*
 * stm32_spi.c
 *
 *  Created on: 31-07-2012
 *      Author: Tomek
 */

#include <stm32l/spi.h>

/* initialize spi */
void SPI_Init(spi_t *SPIx, spi_init_t *init)
{
	uint16_t tmpreg = 0;


	/* Get the SPIx CR1 value */
	tmpreg = SPIx->CR1;

	/* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR,
	 * CPOL and CPHA bits */
	tmpreg &= 0x3040;

	/* Configure SPIx: direction, NSS management, first transmitted bit,
	 * BaudRate prescaler master/salve mode, CPOL and CPHA */
	/* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
	/* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
	/* Set LSBFirst bit according to SPI_FirstBit value */
	/* Set BR bits according to SPI_BaudRatePrescaler value */
	/* Set CPOL bit according to SPI_CPOL value */
	/* Set CPHA bit according to SPI_CPHA value */
	tmpreg |= (uint16_t)((uint32_t)init->direction | init->mode |
				  init->data_size | init->cpol |
				  init->cpha | init->nss |
				  init->prescaler | init->first_bit);

	/* Write to SPIx CR1 */
	SPIx->CR1 = tmpreg;

	/* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
	SPIx->I2SCFGR &= (uint16_t)~((uint16_t)(1 << 11));

	/* Write to SPIx CRCPOLY */
	SPIx->CRCPR = init->crc_poly;
}

/* initialize struct */
void SPI_StructInit(spi_init_t *init)
{
	/* Initialize the SPI_Direction member */
	init->direction = SPI_DIRECTION_2LINES_FULLDUPLEX;
	/* initialize the SPI_Mode member */
	init->mode = SPI_MODE_SLAVE;
	/* initialize the SPI_DataSize member */
	init->data_size = SPI_DATASIZE_8B;
	/* Initialize the SPI_CPOL member */
	init->cpol = SPI_CPOL_LOW;
	/* Initialize the SPI_CPHA member */
	init->cpha = SPI_CPHA_1EDGE;
	/* Initialize the SPI_NSS member */
	init->nss = SPI_NSS_HARD;
	/* Initialize the SPI_BaudRatePrescaler member */
	init->prescaler = SPI_PRESCALER_2;
	/* Initialize the SPI_FirstBit member */
	init->first_bit = SPI_FIRSTBIT_MSB;
	/* Initialize the SPI_CRCPolynomial member */
	init->crc_poly = 7;
}

/* enable or disable spi */
void SPI_Cmd(spi_t *SPIx, int state)
{
  if (state != DISABLE) {
	  /* Enable the selected SPI peripheral */
	  SPIx->CR1 |= (1 << 6);
  } else {
	  /* Disable the selected SPI peripheral */
	  SPIx->CR1 &= (uint16_t)~((uint16_t)(1 << 6));
  }
}

/* receive data */
uint16_t SPI_ReceiveData(spi_t *SPIx)
{
	/* Return the data in the DR register */
	return SPIx->DR;
}

/* send data */
void SPI_SendData(spi_t *SPIx, uint16_t data)
{
	/* Write in the DR register the data to be sent */
	SPIx->DR = data;
}

/* configure interrupt */
void SPI_ITConfig(spi_t *SPIx, uint8_t interrupt, int state)
{
	if (state != DISABLE) {
		/* Enable the selected SPI interrupt */
		SPIx->CR2 |= interrupt;
	} else {
		/* Disable the selected SPI interrupt */
		SPIx->CR2 &= (uint16_t)~interrupt;
	}
}

/* get status */
uint16_t SPI_GetStatus(spi_t *SPIx)
{
	return SPIx->SR;
}

/* get status */
void SPI_ClearStatus(spi_t *SPIx, uint16_t flags)
{
	SPIx->SR &= (uint16_t)~flags;
}

/* configure dma */
void SPI_DMACmd(spi_t* SPIx, uint16_t dma_req, int enable)
{
	/* disable */
	if (enable != DISABLE) {
		/* Enable the selected SPI DMA requests */
		SPIx->CR2 |= dma_req;
	} else {
		/* Disable the selected SPI DMA requests */
		SPIx->CR2 &= (uint16_t)~dma_req;
	}
}

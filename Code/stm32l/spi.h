/*
 * stm32_spi.h
 *
 *  Created on: 31-07-2012
 *      Author: Tomek
 */

#ifndef STM32L_SPI_H_
#define STM32L_SPI_H_

#include <stm32l/stm32l.h>

/* register base */
#define SPI1_BASE							0x40013000
#define SPI2_BASE							0x40003800
#define SPI3_BASE							0x40003C00

/* spis */
#define SPI1              					((spi_t *) SPI1_BASE)
#define SPI2              					((spi_t *) SPI2_BASE)
#define SPI3              					((spi_t *) SPI3_BASE)

/* spi registers */
typedef struct {
	reg16_t CR1;
	reg16_t RESERVED0;
	reg16_t CR2;
	reg16_t RESERVED1;
	reg16_t SR;
	reg16_t RESERVED2;
	reg16_t DR;
	reg16_t RESERVED3;
	reg16_t CRCPR;
	reg16_t RESERVED4;
	reg16_t RXCRCR;
	reg16_t RESERVED5;
	reg16_t TXCRCR;
	reg16_t RESERVED6;
	reg16_t I2SCFGR;
	reg16_t RESERVED7;
	reg16_t I2SPR;
	reg16_t RESERVED8;
} spi_t;

/* SPI control register 1 */
#define SPI_CR1_CPHA                        (0x0001)
#define SPI_CR1_CPOL                        (0x0002)
#define SPI_CR1_MSTR                        (0x0004)
#define SPI_CR1_BR                          (0x0038)
#define SPI_CR1_BR_0                        (0x0008)
#define SPI_CR1_BR_1                        (0x0010)
#define SPI_CR1_BR_2                        (0x0020)
#define SPI_CR1_SPE                         (0x0040)
#define SPI_CR1_LSBFIRST                    (0x0080)
#define SPI_CR1_SSI                         (0x0100)
#define SPI_CR1_SSM                         (0x0200)
#define SPI_CR1_RXONLY                      (0x0400)
#define SPI_CR1_DFF                         (0x0800)
#define SPI_CR1_CRCNEXT                     (0x1000)
#define SPI_CR1_CRCEN                       (0x2000)
#define SPI_CR1_BIDIOE                      (0x4000)
#define SPI_CR1_BIDIMODE                    (0x8000)

/* SPI control register 2 */
#define SPI_CR2_RXDMAEN                     (0x01)
#define SPI_CR2_TXDMAEN                     (0x02)
#define SPI_CR2_SSOE                        (0x04)
#define SPI_CR2_FRF                         (0x08)
#define SPI_CR2_ERRIE                       (0x20)
#define SPI_CR2_RXNEIE                      (0x40)
#define SPI_CR2_TXEIE                       (0x80)

/* SPI status register */
#define SPI_SR_RXNE                         (0x01)
#define SPI_SR_TXE                          (0x02)
#define SPI_SR_CHSIDE                       (0x04)
#define SPI_SR_UDR                          (0x08)
#define SPI_SR_CRCERR                       (0x10)
#define SPI_SR_MODF                         (0x20)
#define SPI_SR_OVR                          (0x40)
#define SPI_SR_BSY                          (0x80)

/* SPI data register */
#define SPI_DR_DR                           (0xFFFF)

/* SPI CRC polynomial register */
#define SPI_CRCPR_CRCPOLY                   (0xFFFF)

/* SPI RX CRC register */
#define SPI_RXCRCR_RXCRC                    (0xFFFF)

/* SPI TX CRC register */
#define SPI_TXCRCR_TXCRC                    (0xFFFF)

/* SPI_I2S configuration register */
#define SPI_I2SCFGR_CHLEN                   (0x0001)
#define SPI_I2SCFGR_DATLEN                  (0x0006)
#define SPI_I2SCFGR_DATLEN_0                (0x0002)
#define SPI_I2SCFGR_DATLEN_1                (0x0004)
#define SPI_I2SCFGR_CKPOL                   (0x0008)
#define SPI_I2SCFGR_I2SSTD                  (0x0030)
#define SPI_I2SCFGR_I2SSTD_0                (0x0010)
#define SPI_I2SCFGR_I2SSTD_1                (0x0020)
#define SPI_I2SCFGR_PCMSYNC                 (0x0080)
#define SPI_I2SCFGR_I2SCFG                  (0x0300)
#define SPI_I2SCFGR_I2SCFG_0                (0x0100)
#define SPI_I2SCFGR_I2SCFG_1                (0x0200)
#define SPI_I2SCFGR_I2SE                    (0x0400)
#define SPI_I2SCFGR_I2SMOD                  (0x0800)

/* SPI_I2S prescaler register */
#define SPI_I2SPR_I2SDIV                    (0x00FF)
#define SPI_I2SPR_ODD                       (0x0100)
#define SPI_I2SPR_MCKOE                     (0x0200)

typedef struct {
	uint16_t direction;
	uint16_t mode;
	uint16_t data_size;
	uint16_t cpol;
	uint16_t cpha;
	uint16_t nss;
	uint16_t prescaler;
	uint16_t first_bit;
	uint16_t crc_poly;
} spi_init_t;

/* direction bits */
#define SPI_DIRECTION_2LINES_FULLDUPLEX 	(0x0000)
#define SPI_DIRECTION_2LINES_RXONLY     	(0x0400)
#define SPI_DIRECTION_1LINE_RX          	(0x8000)
#define SPI_DIRECTION_1LINE_TX          	(0xC000)

/* mode of operation  */
#define SPI_MODE_MASTER                 	(0x0104)
#define SPI_MODE_SLAVE                  	(0x0000)

/* data size */
#define SPI_DATASIZE_16B                	(0x0800)
#define SPI_DATASIZE_8B                 	(0x0000)

/* clock polarity */
#define SPI_CPOL_LOW                    	(0x0000)
#define SPI_CPOL_HIGH                   	(0x0002)

/* clock phase */
#define SPI_CPHA_1EDGE                  	(0x0000)
#define SPI_CPHA_2EDGE                  	(0x0001)

/* slave select */
#define SPI_NSS_SOFT                    	(0x0200)
#define SPI_NSS_HARD                    	(0x0000)

/* clock prescaler */
#define SPI_PRESCALER_2         			(0x0000)
#define SPI_PRESCALER_4         			(0x0008)
#define SPI_PRESCALER_8         			(0x0010)
#define SPI_PRESCALER_16        			(0x0018)
#define SPI_PRESCALER_32        			(0x0020)
#define SPI_PRESCALER_64        			(0x0028)
#define SPI_PRESCALER_128       			(0x0030)
#define SPI_PRESCALER_256       			(0x0038)

/* transfer msb or lsb first */
#define SPI_FIRSTBIT_MSB                	(0x0000)
#define SPI_FIRSTBIT_LSB                	(0x0080)

/* interrupts */
#define SPI_IT_TXE                   		(0x80)
#define SPI_IT_RXNE                  		(0x40)
#define SPI_IT_ERR                   		(0x20)

/* flags */
#define SPI_FLAG_RXNE                		(0x0001)
#define SPI_FLAG_TXE                 		(0x0002)
#define SPI_FLAG_OVR                 		(0x0040)
#define SPI_FLAG_BSY                 		(0x0080)
#define SPI_FLAG_FRE						(0x0100)

/* dma requests */
#define SPI_DMAREQ_TX               		(0x0002)
#define SPI_DMAREQ_RX               		(0x0001)

/* initialize spi */
void SPI_Init(spi_t *SPIx, spi_init_t *init);
/* initialize struct */
void SPI_StructInit(spi_init_t *init);
/* enable or disable spi */
void SPI_Cmd(spi_t *SPIx, int state);
/* receive data */
uint16_t SPI_ReceiveData(spi_t *SPIx);
/* send data */
void SPI_SendData(spi_t *SPIx, uint16_t data);
/* configure interrupt */
void SPI_ITConfig(spi_t *SPIx, uint8_t interrupt, int state);
/* get status */
uint16_t SPI_GetStatus(spi_t *SPIx);
/* get status */
void SPI_ClearStatus(spi_t *SPIx, uint16_t flags);
/* configure dma */
void SPI_DMACmd(spi_t* SPIx, uint16_t dma_req, int enable);

#endif /* STM32_SPI_H_ */

/*
 * stm32_usart.h
 *
 *  Created on: 13-06-2012
 *      Author: Tomek
 */

#ifndef STM32L_USART_H_
#define STM32L_USART_H_

#include <stm32l/stm32l.h>

/* register base */
#define USART1_BASE							0x40013800
#define USART2_BASE							0x40004400
#define USART3_BASE							0x40004800
#define USART4_BASE							0x40004c00
#define USART5_BASE							0x40005000

/* usart */
#define USART1              				((usart_t *) USART1_BASE)
#define USART2              				((usart_t *) USART2_BASE)
#define USART3              				((usart_t *) USART3_BASE)
#define USART4              				((usart_t *) USART4_BASE)
#define USART5             	 				((usart_t *) USART5_BASE)


/* usart registers */
typedef struct {
	reg16_t SR;
	reg16_t RESERVED0;
	reg16_t DR;
	reg16_t RESERVED1;
	reg16_t BRR;
	reg16_t RESERVED2;
	reg16_t CR1;
	reg16_t RESERVED3;
	reg16_t CR2;
	reg16_t RESERVED4;
	reg16_t CR3;
	reg16_t RESERVED5;
	reg16_t GTPR;
	reg16_t RESERVED6;
} __attribute__((packed)) usart_t;

/* Status register */
#define USART_SR_PE                         (0x0001)
#define USART_SR_FE                         (0x0002)
#define USART_SR_NE                         (0x0004)
#define USART_SR_ORE                        (0x0008)
#define USART_SR_IDLE                       (0x0010)
#define USART_SR_RXNE                       (0x0020)
#define USART_SR_TC                         (0x0040)
#define USART_SR_TXE                        (0x0080)
#define USART_SR_LBD                        (0x0100)
#define USART_SR_CTS                        (0x0200)

/* Data register */
#define USART_DR_DR                         (0x01FF)

/* Baud rate register */
#define USART_BRR_DIV_FRACTION              (0x000F)
#define USART_BRR_DIV_MANTISSA              (0xFFF0)

/* Control register 1 */
#define USART_CR1_SBK                       (0x0001)
#define USART_CR1_RWU                       (0x0002)
#define USART_CR1_RE                        (0x0004)
#define USART_CR1_TE                        (0x0008)
#define USART_CR1_IDLEIE                    (0x0010)
#define USART_CR1_RXNEIE                    (0x0020)
#define USART_CR1_TCIE                      (0x0040)
#define USART_CR1_TXEIE                     (0x0080)
#define USART_CR1_PEIE                      (0x0100)
#define USART_CR1_PS                        (0x0200)
#define USART_CR1_PCE                       (0x0400)
#define USART_CR1_WAKE                      (0x0800)
#define USART_CR1_M                         (0x1000)
#define USART_CR1_UE                        (0x2000)
#define USART_CR1_OVER8                     (0x8000)

/* Control register 2 */
#define USART_CR2_ADD                       (0x000F)
#define USART_CR2_LBDL                      (0x0020)
#define USART_CR2_LBDIE                     (0x0040)
#define USART_CR2_LBCL                      (0x0100)
#define USART_CR2_CPHA                      (0x0200)
#define USART_CR2_CPOL                      (0x0400)
#define USART_CR2_CLKEN                     (0x0800)
#define USART_CR2_STOP                      (0x3000)
#define USART_CR2_STOP_0                    (0x1000)
#define USART_CR2_STOP_1                    (0x2000)
#define USART_CR2_LINEN                     (0x4000)

/* Control register 3 */
#define USART_CR3_EIE                       (0x0001)
#define USART_CR3_IREN                      (0x0002)
#define USART_CR3_IRLP                      (0x0004)
#define USART_CR3_HDSEL                     (0x0008)
#define USART_CR3_NACK                      (0x0010)
#define USART_CR3_SCEN                      (0x0020)
#define USART_CR3_DMAR                      (0x0040)
#define USART_CR3_DMAT                      (0x0080)
#define USART_CR3_RTSE                      (0x0100)
#define USART_CR3_CTSE                      (0x0200)
#define USART_CR3_CTSIE                     (0x0400)
#define USART_CR3_ONEBIT                    (0x0800)

/* Guard time and prescaler register */
#define USART_GTPR_PSC                      (0x00FF)
#define USART_GTPR_PSC_0                    (0x0001)
#define USART_GTPR_PSC_1                    (0x0002)
#define USART_GTPR_PSC_2                    (0x0004)
#define USART_GTPR_PSC_3                    (0x0008)
#define USART_GTPR_PSC_4                    (0x0010)
#define USART_GTPR_PSC_5                    (0x0020)
#define USART_GTPR_PSC_6                    (0x0040)
#define USART_GTPR_PSC_7                    (0x0080)
#define USART_GTPR_GT                       (0xFF00)

/* init struct */
typedef struct {
	uint32_t baud_rate;
	uint16_t word_length;
	uint16_t stop_bits;
	uint16_t parity;
	uint16_t mode;
	uint16_t hardware_flow_control;
} usart_init_t;

/* word length */
#define USART_WORD_8B                  		(0x0000)
#define USART_WORD_9B                  		(0x1000)

/* usart stopbits */
#define USART_STOPBITS_1                    (0x0000)
#define USART_STOPBITS_0_5                  (0x1000)
#define USART_STOPBITS_2                    (0x2000)
#define USART_STOPBITS_1_5                  (0x3000)

/* usart parity */
#define USART_PARITY_NO                     (0x0000)
#define USART_PARITY_EVEN                   (0x0400)
#define USART_PARITY_ODD                    (0x0600)

/* mode */
#define USART_MODE_RX                       (0x0004)
#define USART_MODE_TX                       (0x0008)

/* flow control */
#define USART_HARDWAREFLOWCONTROL_NONE		(0x0000)
#define USART_HARDWAREFLOWCONTROL_RTS       (0x0100)
#define USART_HARDWAREFLOWCONTROL_CTS       (0x0200)
#define USART_HARDWAREFLOWCONTROL_RTS_CTS   (0x0300)

/* dma requests */
#define USART_DMAREQ_TX                     (0x0080)
#define USART_DMAREQ_RX                     (0x0040)

/* usart flags */
#define USART_FLAG_CTS                      (0x0200)
#define USART_FLAG_LBD                      (0x0100)
#define USART_FLAG_TXE                      (0x0080)
#define USART_FLAG_TC                       (0x0040)
#define USART_FLAG_RXNE                     (0x0020)
#define USART_FLAG_IDLE                     (0x0010)
#define USART_FLAG_ORE                      (0x0008)
#define USART_FLAG_NE                       (0x0004)
#define USART_FLAG_FE                       (0x0002)
#define USART_FLAG_PE                       (0x0001)

/* usart interrupts */
#define USART_IT_IDLE                       (1 << 4)
#define USART_IT_RXNEIE                     (1 << 5)
#define USART_IT_TCIE                       (1 << 6)
#define USART_IT_TXEIE                      (1 << 7)
#define USART_IT_PEIE                      	(1 << 8)

/* usart deinit */
void USART_DeInit(usart_t *USARTx);
/* initialize usart */
void USART_Init(usart_t *USARTx, usart_init_t *init);
/* initialize structure with defaults */
void USART_StructInit(usart_init_t *init);
/* Transmits single data through the USARTx peripheral. */
void USART_SendData(usart_t *USARTx, uint16_t data);
/* Returns the most recent received data by the USARTx peripheral. */
uint16_t USART_ReceiveData(usart_t *USARTx);
/* usart command */
void USART_Cmd(usart_t *USARTx, int state);
/* usart command */
void USART_DMACmd(usart_t *USARTx, uint32_t dma_req, int state);
/* set baudrate */
void USART_SetBaudrate(usart_t *USARTx, int baudrade);
/* get usart status */
int USART_GetStatus(usart_t *USARTx);
/* configure interrupt */
void USART_ITConfig(usart_t *USARTx, uint8_t interrupt, int state);

#endif /* STM32_USART_H_ */

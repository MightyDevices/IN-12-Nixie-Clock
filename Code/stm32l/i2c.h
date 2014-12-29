/*
 * stm32_i2c.h
 *
 *  Created on: 21-11-2012
 *      Author: Tomek
 */

#ifndef STM32L_I2C_H_
#define STM32L_I2C_H_

#include <stm32l/stm32l.h>

/* register base */
#define I2C1_BASE							0x40005400
#define I2C2_BASE							0x40005800

/* usart */
#define I2C1              					((i2c_t *) I2C1_BASE)
#define I2C2              					((i2c_t *) I2C2_BASE)

/* registers */
typedef struct {
	reg16_t 	CR1;
	reg16_t  	RESERVED0;
	reg16_t 	CR2;
	reg16_t  	RESERVED1;
	reg16_t 	OAR1;
	reg16_t  	RESERVED2;
	reg16_t 	OAR2;
	reg16_t  	RESERVED3;
	reg16_t 	DR;
	reg16_t  	RESERVED4;
	reg16_t 	SR1;
	reg16_t  	RESERVED5;
	reg16_t 	SR2;
	reg16_t  	RESERVED6;
	reg16_t 	CCR;
	reg16_t  	RESERVED7;
	reg16_t 	TRISE;
	reg16_t  	RESERVED8;
} __attribute__((packed)) i2c_t;

/* I2C Control register 1 */
#define I2C_CR1_PE                          (0x0001)
#define I2C_CR1_SMBUS                       (0x0002)
#define I2C_CR1_SMBTYPE                     (0x0008)
#define I2C_CR1_ENARP                       (0x0010)
#define I2C_CR1_ENPEC                       (0x0020)
#define I2C_CR1_ENGC                        (0x0040)
#define I2C_CR1_NOSTRETCH                   (0x0080)
#define I2C_CR1_START                       (0x0100)
#define I2C_CR1_STOP                        (0x0200)
#define I2C_CR1_ACK                         (0x0400)
#define I2C_CR1_POS                         (0x0800)
#define I2C_CR1_PEC                         (0x1000)
#define I2C_CR1_ALERT                       (0x2000)
#define I2C_CR1_SWRST                       (0x8000)

/* I2C Control register 2 */
#define I2C_CR2_FREQ                        (0x003F)
#define I2C_CR2_FREQ_0                      (0x0001)
#define I2C_CR2_FREQ_1                      (0x0002)
#define I2C_CR2_FREQ_2                      (0x0004)
#define I2C_CR2_FREQ_3                      (0x0008)
#define I2C_CR2_FREQ_4                      (0x0010)
#define I2C_CR2_FREQ_5                      (0x0020)

#define I2C_CR2_ITERREN                     (0x0100)
#define I2C_CR2_ITEVTEN                     (0x0200)
#define I2C_CR2_ITBUFEN                     (0x0400)
#define I2C_CR2_DMAEN                       (0x0800)
#define I2C_CR2_LAST                        (0x1000)

/* Own address register 1 */
#define I2C_OAR1_ADD1_7                     (0x00FE)
#define I2C_OAR1_ADD8_9                     (0x0300)

#define I2C_OAR1_ADD0                       (0x0001)
#define I2C_OAR1_ADD1                       (0x0002)
#define I2C_OAR1_ADD2                       (0x0004)
#define I2C_OAR1_ADD3                       (0x0008)
#define I2C_OAR1_ADD4                       (0x0010)
#define I2C_OAR1_ADD5                       (0x0020)
#define I2C_OAR1_ADD6                       (0x0040)
#define I2C_OAR1_ADD7                       (0x0080)
#define I2C_OAR1_ADD8                       (0x0100)
#define I2C_OAR1_ADD9                       (0x0200)

#define I2C_OAR1_ADDMODE                    (0x8000)

/* own address register 2 */
#define I2C_OAR2_ENDUAL                     (0x01)
#define I2C_OAR2_ADD2                       (0xFE)

/* data register */
#define I2C_DR_DR                           (0xFF)

/* status register 1 */
#define I2C_SR1_SB                          (0x0001)
#define I2C_SR1_ADDR                        (0x0002)
#define I2C_SR1_BTF                         (0x0004)
#define I2C_SR1_ADD10                       (0x0008)
#define I2C_SR1_STOPF                       (0x0010)
#define I2C_SR1_RXNE                        (0x0040)
#define I2C_SR1_TXE                         (0x0080)
#define I2C_SR1_BERR                        (0x0100)
#define I2C_SR1_ARLO                        (0x0200)
#define I2C_SR1_AF                          (0x0400)
#define I2C_SR1_OVR                         (0x0800)
#define I2C_SR1_PECERR                      (0x1000)
#define I2C_SR1_TIMEOUT                     (0x4000)
#define I2C_SR1_SMBALERT                    (0x8000)

/* status register 2 */
#define I2C_SR2_MSL                         (0x0001)
#define I2C_SR2_BUSY                        (0x0002)
#define I2C_SR2_TRA                         (0x0004)
#define I2C_SR2_GENCALL                     (0x0010)
#define I2C_SR2_SMBDEFAULT                  (0x0020)
#define I2C_SR2_SMBHOST                     (0x0040)
#define I2C_SR2_DUALF                       (0x0080)
#define I2C_SR2_PEC                         (0xFF00)

/* clock control register */
#define I2C_CCR_CCR                         (0x0FFF)
#define I2C_CCR_DUTY                        (0x4000)
#define I2C_CCR_FS                          (0x8000)

/* TRISE register */
#define I2C_TRISE_TRISE                     (0x3F)

/* init struct */
typedef struct {
	uint32_t 	clock_speed;
	uint16_t 	mode;
	uint16_t 	duty_cycle;
	uint16_t 	own_address1;
	uint16_t 	ack;
	uint16_t 	ack_address;
} i2c_init_t;

/* mode */
#define I2C_MODE_I2C                    	(0x0000)
#define I2C_MODE_SMBUS_DEV            		(0x0002)
#define I2C_MODE_SMBUS_HOST              	(0x000A)

/* duty cycle */
#define I2C_DUTY_16_9              			(0x4000)
#define I2C_DUTY_2                 			(0xBFFF)

/* ack */
#define I2C_ACK_ENABLE                  	(0x0400)
#define I2C_ACK_DISABLE                 	(0x0000)

/* transfer direction */
#define I2C_DIR_TX      					(0x00)
#define I2C_DIR_RX         					(0x01)

/* ack addr */
#define I2C_ACK_ADDR_7B    					(0x4000)
#define I2C_ACK_ADDR_10B   					(0xC000)

/* interrupts */
#define I2C_IT_BUF                      	(0x0400)
#define I2C_IT_EVT                      	(0x0200)
#define I2C_IT_ERR                      	(0x0100)

#define I2C_IT_SMBALERT                 	(0x01008000)
#define I2C_IT_TIMEOUT                  	(0x01004000)
#define I2C_IT_PECERR                   	(0x01001000)
#define I2C_IT_OVR                      	(0x01000800)
#define I2C_IT_AF                       	(0x01000400)
#define I2C_IT_ARLO                     	(0x01000200)
#define I2C_IT_BERR                     	(0x01000100)
#define I2C_IT_TXE                      	(0x06000080)
#define I2C_IT_RXNE                     	(0x06000040)
#define I2C_IT_STOPF                    	(0x02000010)
#define I2C_IT_ADD10                    	(0x02000008)
#define I2C_IT_BTF                      	(0x02000004)
#define I2C_IT_ADDR                     	(0x02000002)
#define I2C_IT_SB                       	(0x02000001)

/* sr2 flags */
#define I2C_FLAG_DUALF                  	(0x00800000)
#define I2C_FLAG_SMBHOST                	(0x00400000)
#define I2C_FLAG_SMBDEFAULT             	(0x00200000)
#define I2C_FLAG_GENCALL                	(0x00100000)
#define I2C_FLAG_TRA                    	(0x00040000)
#define I2C_FLAG_BUSY                   	(0x00020000)
#define I2C_FLAG_MSL                    	(0x00010000)

/* sr1 flags */
#define I2C_FLAG_SMBALERT               	(0x10008000)
#define I2C_FLAG_TIMEOUT                	(0x10004000)
#define I2C_FLAG_PECERR                 	(0x10001000)
#define I2C_FLAG_OVR                    	(0x10000800)
#define I2C_FLAG_AF                     	(0x10000400)
#define I2C_FLAG_ARLO                   	(0x10000200)
#define I2C_FLAG_BERR                   	(0x10000100)
#define I2C_FLAG_TXE                    	(0x10000080)
#define I2C_FLAG_RXNE                   	(0x10000040)
#define I2C_FLAG_STOPF                  	(0x10000010)
#define I2C_FLAG_ADD10                  	(0x10000008)
#define I2C_FLAG_BTF                    	(0x10000004)
#define I2C_FLAG_ADDR                   	(0x10000002)
#define I2C_FLAG_SB                     	(0x10000001)

/* BUSY, MSL and SB flag */
#define I2C_EVENT_MASTER_MODE_SELECT        				(0x00030001)
/* BUSY, MSL, ADDR, TXE and TRA flags */
#define I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED        	(0x00070082)
/* BUSY, MSL and ADDR flags */
#define I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED           	(0x00030002)
/* BUSY, MSL and ADD10 flags */
#define I2C_EVENT_MASTER_MODE_ADDRESS10                   	(0x00030008)

/* BUSY, MSL and RXNE flags */
#define I2C_EVENT_MASTER_BYTE_RECEIVED                    	(0x00030040)

/* TRA, BUSY, MSL, TXE flags */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING                 	(0x00070080)
/* TRA, BUSY, MSL, TXE and BTF flags */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTED                 	(0x00070084)

/* BUSY and RXNE flags */
#define I2C_EVENT_SLAVE_BYTE_RECEIVED                      	(0x00020040)
/* STOPF flag */
#define I2C_EVENT_SLAVE_STOP_DETECTED                      	(0x00000010)

/* TRA, BUSY, TXE and BTF flags */
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTED                   	(0x00060084)
/* TRA, BUSY and TXE flags */
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTING                  	(0x00060080)
/* AF flag */
#define I2C_EVENT_SLAVE_ACK_FAILURE                        	(0x00000400)

/* initialize i2c unit */
void I2C_Init(i2c_t *I2Cx, i2c_init_t *init);
/* initialize structure */
void I2C_StructInit(i2c_init_t *init);
/* reset i2c */
void I2C_ResetCmd(i2c_t* I2Cx, int state);
/* i2c command */
void I2C_Cmd(i2c_t *I2Cx, int state);
/* dma command */
void I2C_DMACmd(i2c_t *I2Cx, int state);
/* last dma transfer? */
void I2C_DMALastTransferCmd(i2c_t *I2Cx, int state);
/* generate start condition */
void I2C_GenerateSTART(i2c_t *I2Cx, int state);
/* generate stop condition */
void I2C_GenerateSTOP(i2c_t *I2Cx, int state);
/* configure interrupt */
void I2C_ITConfig(i2c_t *I2Cx, uint16_t interrupt, int state);
/* send data */
void I2C_SendData(i2c_t *I2Cx, uint8_t data);
/* get data */
uint8_t I2C_ReceiveData(i2c_t *I2Cx);
/* get last event */
uint32_t I2C_GetLastEvent(i2c_t *I2Cx);
/* ack enable */
void I2C_AcknowledgeConfig(i2c_t *I2Cx, int state);
/* get status */
uint16_t I2C_GetStatus1(i2c_t *I2Cx);
/* reset error flag  */
uint16_t I2C_ResetErrorFlags(i2c_t *I2Cx, uint16_t flags);

#endif /* STM32_I2C_H_ */

/*
 * lcd.h
 *
 *  Created on: 28-09-2013
 *      Author: Tomek
 */

#ifndef STM32L_LCD_H_
#define STM32L_LCD_H_

#include <stm32l/stm32l.h>

/* base addresses */
#define LCD									((lcd_t *)0x40002400)

/* lcd registers */
typedef struct {
  reg32_t CR;
  reg32_t FCR;
  reg32_t SR;
  reg32_t CLR;
  reg32_t RESERVED;
  reg32_t RAM[16];
} lcd_t;

/* Bit definition for LCD_CR register */
#define LCD_CR_LCDEN               			0x00000001
#define LCD_CR_VSEL               		 	0x00000002
#define LCD_CR_DUTY                			0x0000001C
#define LCD_CR_DUTY_0              			0x00000004
#define LCD_CR_DUTY_1              			0x00000008
#define LCD_CR_DUTY_2              			0x00000010
#define LCD_CR_BIAS                			0x00000060
#define LCD_CR_BIAS_0              			0x00000020
#define LCD_CR_BIAS_1              			0x00000040
#define LCD_CR_MUX_SEG             			0x00000080

/* Bit definition for LCD_FCR register */
#define LCD_FCR_HD                 			0x00000001
#define LCD_FCR_SOFIE              			0x00000002
#define LCD_FCR_UDDIE              			0x00000008
#define LCD_FCR_PON                			0x00000070
#define LCD_FCR_PON_0              			0x00000010
#define LCD_FCR_PON_1              			0x00000020
#define LCD_FCR_PON_2              			0x00000040
#define LCD_FCR_DEAD               			0x00000380
#define LCD_FCR_DEAD_0            		 	0x00000080
#define LCD_FCR_DEAD_1             			0x00000100
#define LCD_FCR_DEAD_2             			0x00000200
#define LCD_FCR_CC                 			0x00001C00
#define LCD_FCR_CC_0               			0x00000400
#define LCD_FCR_CC_1               			0x00000800
#define LCD_FCR_CC_2               			0x00001000
#define LCD_FCR_BLINKF             			0x0000E000
#define LCD_FCR_BLINKF_0           			0x00002000
#define LCD_FCR_BLINKF_1           			0x00004000
#define LCD_FCR_BLINKF_2           			0x00008000
#define LCD_FCR_BLINK              			0x00030000
#define LCD_FCR_BLINK_0            			0x00010000
#define LCD_FCR_BLINK_1            			0x00020000
#define LCD_FCR_DIV                			0x003C0000
#define LCD_FCR_PS                 			0x03C00000

/* LCD_SR register */
#define LCD_SR_ENS                 			0x00000001
#define LCD_SR_SOF                 			0x00000002
#define LCD_SR_UDR                 			0x00000004
#define LCD_SR_UDD                 			0x00000008
#define LCD_SR_RDY                 			0x00000010
#define LCD_SR_FCRSR               			0x00000020

/* LCD_CLR register */
#define LCD_CLR_SOFC               			0x00000002
#define LCD_CLR_UDDC               			0x00000008

/* LCD_RAM register */
#define LCD_RAM_SEGMENT_DATA       			0xFFFFFFFF

/* initialization structure */
typedef struct {
	/* prescaler */
	uint32_t prescaler;
	/* divider */
	uint32_t divider;
	/* duty cycle */
	uint32_t duty;
	/* bias */
	uint32_t bias;
	/* voltage source */
	uint32_t voltage_source;
} lcd_init_t;

/* prescaler values */
#define LCD_PRESCALER_1        				0x00000000
#define LCD_PRESCALER_2        				0x00400000
#define LCD_PRESCALER_4        				0x00800000
#define LCD_PRESCALER_8        				0x00C00000
#define LCD_PRESCALER_16       				0x01000000
#define LCD_PRESCALER_32       				0x01400000
#define LCD_PRESCALER_64       				0x01800000
#define LCD_PRESCALER_128      				0x01C00000
#define LCD_PRESCALER_256      				0x02000000
#define LCD_PRESCALER_512      				0x02400000
#define LCD_PRESCALER_1024     				0x02800000
#define LCD_PRESCALER_2048     				0x02C00000
#define LCD_PRESCALER_4096     				0x03000000
#define LCD_PRESCALER_8192     				0x03400000
#define LCD_PRESCALER_16384    				0x03800000
#define LCD_PRESCALER_32768   				0x03C00000

/* divider values */
#define LCD_DIVIDER_16    		 			0x00000000
#define LCD_DIVIDER_17    					0x00040000
#define LCD_DIVIDER_18    					0x00080000
#define LCD_DIVIDER_19    					0x000C0000
#define LCD_DIVIDER_20    					0x00100000
#define LCD_DIVIDER_21    					0x00140000
#define LCD_DIVIDER_22    					0x00180000
#define LCD_DIVIDER_23    					0x001C0000
#define LCD_DIVIDER_24    					0x00200000
#define LCD_DIVIDER_25    					0x00240000
#define LCD_DIVIDER_26    					0x00280000
#define LCD_DIVIDER_27    					0x002C0000
#define LCD_DIVIDER_28    					0x00300000
#define LCD_DIVIDER_29    					0x00340000
#define LCD_DIVIDER_30   					0x00380000
#define LCD_DIVIDER_31    					0x003C0000

/* duty values */
#define LCD_DUTY_STATIC                 	0x00000000
#define LCD_DUTY_1_2                   		0x00000004
#define LCD_DUTY_1_3                    	0x00000008
#define LCD_DUTY_1_4                   	 	0x0000000C
#define LCD_DUTY_1_8                    	0x00000010

/* bias */
#define LCD_BIAS_1_4                    	0x00000000
#define LCD_BIAS_1_2                    	LCD_CR_BIAS_0
#define LCD_BIAS_1_3                    	LCD_CR_BIAS_1

/* voltage source */
#define LCD_VOLSOURCE_INTERNAL      		0x00000000
#define LCD_VOLSOURCE_EXTERNAL      		LCD_CR_VSEL


/* interrupt sources */
#define LCD_IT_SOF                      	LCD_FCR_SOFIE
#define LCD_IT_UDD                      	LCD_FCR_UDDIE



/* pulse on duration */
#define LCD_PULSEON_DURATION_0           	0x00000000
#define LCD_PULSEON_DURATION_1           	0x00000010
#define LCD_PULSEON_DURATION_2           	0x00000020
#define LCD_PULSEON_DURATION_3           	0x00000030
#define LCD_PULSEON_DURATION_4           	0x00000040
#define LCD_PULSEON_DURATION_5           	0x00000050
#define LCD_PULSEON_DURATION_6           	0x00000060
#define LCD_PULSEON_DURATION_7           	0x00000070


/* dead time */
#define LCD_DEADTIME_0                  	0x00000000
#define LCD_DEADTIME_1                  	0x00000080
#define LCD_DEADTIME_2                  	0x00000100
#define LCD_DEADTIME_3                  	0x00000180
#define LCD_DEADTIME_4                  	0x00000200
#define LCD_DEADTIME_5                  	0x00000280
#define LCD_DEADTIME_6                  	0x00000300
#define LCD_DEADTIME_7                  	0x00000380

/* blink modes */
#define LCD_BLINK_MODE_OFF               	0x00000000
#define LCD_BLINK_MODE_SEG0_COM0         	0x00010000
#define LCD_BLINK_MODE_SEG0_ALLCOM       	0x00020000
#define LCD_BLINK_MODE_ALLSEG_ALLCOM     	0x00030000

/* blink frequency */
#define LCD_BLINK_FREQ_DIV8         		0x00000000
#define LCD_BLINK_FREQ_DIV16        		0x00002000
#define LCD_BLINK_FREQ_DIV32        		0x00004000
#define LCD_BLINK_FREQ_DIV64        		0x00006000
#define LCD_BLINK_FREQ_DIV128       		0x00008000
#define LCD_BLINK_FREQ_DIV256       		0x0000A000
#define LCD_BLINK_FREQ_DIV512       		0x0000C000
#define LCD_BLINK_FREQ_DIV1024     	 		0x0000E000

/* contrast levels */
#define LCD_CONTRAST_0               		0x00000000
#define LCD_CONTRAST_1               		0x00000400
#define LCD_CONTRAST_2               		0x00000800
#define LCD_CONTRAST_3               		0x00000C00
#define LCD_CONTRAST_4               		0x00001000
#define LCD_CONTRAST_5               		0x00001400
#define LCD_CONTRAST_6               		0x00001800
#define LCD_CONTRAST_7               		0x00001C00

/* status flags */
#define LCD_FLAG_ENS                    	LCD_SR_ENS
#define LCD_FLAG_SOF                    	LCD_SR_SOF
#define LCD_FLAG_UDR                    	LCD_SR_UDR
#define LCD_FLAG_UDD                    	LCD_SR_UDD
#define LCD_FLAG_RDY                    	LCD_SR_RDY
#define LCD_FLAG_FCRSF                  	LCD_SR_FCRSR

/* ram registers */
#define LCD_RAM_0               			0x00000000
#define LCD_RAM_1               			0x00000001
#define LCD_RAM_2               			0x00000002
#define LCD_RAM_3               			0x00000003
#define LCD_RAM_4               			0x00000004
#define LCD_RAM_5               			0x00000005
#define LCD_RAM_6               			0x00000006
#define LCD_RAM_7               			0x00000007
#define LCD_RAM_8              		 		0x00000008
#define LCD_RAM_9               			0x00000009
#define LCD_RAM_10              			0x0000000A
#define LCD_RAM_11              			0x0000000B
#define LCD_RAM_12              			0x0000000C
#define LCD_RAM_13              			0x0000000D
#define LCD_RAM_14              			0x0000000E
#define LCD_RAM_15              			0x0000000F

/* deinitialize lcd */
void LCD_Deinit(void);
/* initialize lcd */
void LCD_Init(lcd_init_t *init);
/* initialize structure */
void LCD_StructInit(lcd_init_t *init);
/* enable /disable lcd */
void LCD_Cmd(int enable);
/* wait for synchronization */
void LCD_WaitForSynchro(void);
/* mux segment command */
void LCD_MuxSegmentCmd(int enable);
/* pulse on duration configuration */
void LCD_PulseOnDurationConfig(uint32_t duration);
/* configure dead time */
void LCD_DeadTimeConfig(uint32_t dead_time);
/* configure blinking */
void LCD_BlinkConfig(uint32_t mode, uint32_t frequency);
/* configure contrast */
void LCD_ContrastConfig(uint32_t contrast);
/* write */
void LCD_Write(uint32_t reg, uint32_t data);
/* update display request */
void LCD_UpdateDisplayRequest(void);
/* get status register */
uint32_t LCD_GetStatus(void);

#endif /* LCD_H_ */

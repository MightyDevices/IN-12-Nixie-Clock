/*
 * stm32_flash.h
 *
 *  Created on: 18-06-2012
 *      Author: Tomek
 */

#ifndef STM32_FLASH_H_
#define STM32_FLASH_H_

#include <stm32l/stm32l.h>

/* register base */
#define FLASH_BASE							(0x40023c00)
/* flash controller itself */
#define FLASH								((flash_t *) FLASH_BASE)

typedef struct {
	reg32_t ACR;
	reg32_t PECR;
	reg32_t PDKEYR;
	reg32_t PEKEYR;
	reg32_t PRGKEYR;
	reg32_t OPTKEYR;
	reg32_t SR;
	reg32_t OBR;
	reg32_t WRPR1;
} flash_t;

#define FLASH_ACR_LATENCY                   (0x00000001)
#define FLASH_ACR_PRFTEN                    (0x00000002)
#define FLASH_ACR_ACC64                     (0x00000004)
#define FLASH_ACR_SLEEP_PD                  (0x00000008)
#define FLASH_ACR_RUN_PD                    (0x00000010)

#define FLASH_PECR_PELOCK                   (0x00000001)
#define FLASH_PECR_PRGLOCK                  (0x00000002)
#define FLASH_PECR_OPTLOCK                  (0x00000004)
#define FLASH_PECR_PROG                     (0x00000008)
#define FLASH_PECR_DATA                     (0x00000010)
#define FLASH_PECR_FTDW                     (0x00000100)
#define FLASH_PECR_ERASE                    (0x00000200)
#define FLASH_PECR_FPRG                     (0x00000400)
#define FLASH_PECR_PARALLBANK               (0x00008000)
#define FLASH_PECR_EOPIE                    (0x00010000)
#define FLASH_PECR_ERRIE                    (0x00020000)
#define FLASH_PECR_OBL_LAUNCH               (0x00040000)

#define FLASH_PDKEYR_PDKEYR                 (0xFFFFFFFF)
#define FLASH_PEKEYR_PEKEYR                 (0xFFFFFFFF)
#define FLASH_PRGKEYR_PRGKEYR               (0xFFFFFFFF)
#define FLASH_OPTKEYR_OPTKEYR               (0xFFFFFFFF)

#define FLASH_SR_BSY                        (0x00000001)
#define FLASH_SR_EOP                        (0x00000002)
#define FLASH_SR_ENHV                       (0x00000004)
#define FLASH_SR_READY                      (0x00000008)
#define FLASH_SR_WRPERR                     (0x00000100)
#define FLASH_SR_PGAERR                     (0x00000200)
#define FLASH_SR_SIZERR                     (0x00000400)
#define FLASH_SR_OPTVERR                    (0x00000800)
#define FLASH_SR_OPTVERRUSR                 (0x00001000)

#define FLASH_OBR_RDPRT                     (0x000000AA)
#define FLASH_OBR_BOR_LEV                   (0x0000000F)
#define FLASH_OBR_USER                      (0x00000070)
#define FLASH_OBR_IWDG_SW                   (0x00000010)
#define FLASH_OBR_NRST_STOP                 (0x00000020)
#define FLASH_OBR_NRST_STDBY                (0x00000040)
#define FLASH_OBR_NRST_BFB2                 (0x00000080)

#define FLASH_WRPR_WRP                      (0xFFFFFFFF)
#define FLASH_WRPR1_WRP                     (0xFFFFFFFF)
#define FLASH_WRPR2_WRP                     (0xFFFFFFFF)


/* register base */
#define OB_BASE             				0x1FF80000
/* option bytes */
#define OB                  				((ob_t *) OB_BASE)

/* option bytes */
typedef struct {
  reg32_t RDP;
  reg32_t USER;
  reg32_t WRP01;
  reg32_t WRP23;
  reg32_t WRP45;
  reg32_t WRP67;
  reg32_t WRP89;
  reg32_t WRP1011;
} ob_t;

/* protecting keys */
#define FLASH_PDKEY1               			(0x04152637)
#define FLASH_PDKEY2               			(0xFAFBFCFD)
#define FLASH_PEKEY1               			(0x89ABCDEF)
#define FLASH_PEKEY2               			(0x02030405)
#define FLASH_PRGKEY1              			(0x8C9DAEBF)
#define FLASH_PRGKEY2              			(0x13141516)
#define FLASH_OPTKEY1              			(0xFBEAD9C8)
#define FLASH_OPTKEY2              			(0x24252627)

/* latency */
#define FLASH_LATENCY_0                		(0x00)
#define FLASH_LATENCY_1                		(0x01)

/* bor levels */
#define OB_BOR_OFF							0x00
/* software wdg */
#define OB_IWDG_SW                   		0x10
/* hardware wdg */
#define OB_IWDG_HW                  		0x00
/* no reset generated when entering STOP */
#define OB_STOP_NORST              	 		0x20
/* reset generated when entering STOP */
#define OB_STOP_RST                  		0x00
/* no reset generated when entering STANDBY */
#define OB_STDBY_NORST               		0x40
/* reset generated when entering STANDBY */
#define OB_STDBY_RST                	 	0x00

/* set latency */
void FLASH_SetLatency(uint32_t latency);
/* Enables or disables the Prefetch Buffer */
void FLASH_PrefetchBufferCmd(int state);
/* Enables or disables read access to flash by 64 bits. */
void FLASH_ReadAccess64Cmd(int state);
/* Enable or disable the power down mode during Sleep mode. */
void FLASH_SLEEPPowerDownCmd(int state);
/* flash unlock */
void FLASH_Unlock(void);
/* flash lock */
void FLASH_Lock(void);
/* flash erase page */
void FLASH_ErasePage(uint32_t page_addr);
/* fast program word */
void FLASH_FastProgramWord(uint32_t addr, uint32_t data);
/* data eeprom unlock */
void DATA_EEPROM_Unlock(void);
/* data eeprom lock */
void DATA_EEPROM_Lock(void);
/* Enables or disables DATA EEPROM fixed Time programming (2*Tprog) */
void DATA_EEPROM_FixedTimeProgramCmd(int state);
/* Erase a byte in data memory. */
void DATA_EEPROM_EraseByte(uint32_t addr);
/* Erase a halfword in data memory. */
void DATA_EEPROM_EraseHalfWord(uint32_t addr);
/* Erase a word in data memory.*/
void DATA_EEPROM_EraseWord(uint32_t addr);
/* program byte */
void DATA_EEPROM_FastProgramByte(uint32_t addr, uint8_t data);
/* program half-word */
void DATA_EEPROM_FastProgramHalfWord(uint32_t addr, uint16_t data);
/* Programs a word at a specified address in data memory. */
void DATA_EEPROM_FastProgramWord(uint32_t addr, uint32_t data);
/* Programs a word at a specified address in data memory without erase. */
void DATA_EEPROM_ProgramWord(uint32_t addr, uint32_t data);
/* unlock option bytes */
void FLASH_OB_Unlock(void);
/* lock option bytes */
void FLASH_OB_Lock(void);
/* option byte launch */
void FLASH_OB_Launch(void);
/* configure option bytes */
void FLASH_OB_UserConfig(uint8_t flags);


#endif /* STM32_FLASH_H_ */

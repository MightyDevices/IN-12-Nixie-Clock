/*
 * stm32_flash.c
 *
 *  Created on: 18-06-2012
 *      Author: Tomek
 */


#include <stm32l/flash.h>

/* set latency */
void FLASH_SetLatency(uint32_t latency)
{
   uint32_t tmpreg = 0;
   /* Read the ACR register */
   tmpreg = FLASH->ACR;

   /* Sets the Latency value */
   tmpreg &= ~(FLASH_ACR_LATENCY);
   tmpreg |= latency;

   /* Write the ACR register */
   FLASH->ACR = tmpreg;
}

/* Enables or disables the Prefetch Buffer */
void FLASH_PrefetchBufferCmd(int state)
{
	if (state) {
		FLASH->ACR |= FLASH_ACR_PRFTEN;
	} else {
		FLASH->ACR &= ~(FLASH_ACR_PRFTEN);
	}
}

/* Enables or disables read access to flash by 64 bits. */
void FLASH_ReadAccess64Cmd(int state)
{
	if (state) {
		FLASH->ACR |= FLASH_ACR_ACC64;
	} else {
		FLASH->ACR &= ~(FLASH_ACR_ACC64);
	}
}

/* Enable or disable the power down mode during Sleep mode. */
void FLASH_SLEEPPowerDownCmd(int state)
{
	if (state) {
		FLASH->ACR |= FLASH_ACR_SLEEP_PD;
	} else {
		FLASH->ACR &= ~(FLASH_ACR_SLEEP_PD);
	}
}

/* flash unlock */
void FLASH_Unlock(void)
{
	if (FLASH->PECR & FLASH_PECR_PRGLOCK) {
		/* Unlocking the data memory and FLASH_PECR register access */
		DATA_EEPROM_Unlock();

		/* Unlocking the program memory access */
		FLASH->PRGKEYR = FLASH_PRGKEY1;
		FLASH->PRGKEYR = FLASH_PRGKEY2;
	}
}

/* flash lock */
void FLASH_Lock(void)
{
	/* Set the PRGLOCK Bit to lock the program memory access */
	FLASH->PECR |= FLASH_PECR_PRGLOCK;
}

/* flash erase page */
void FLASH_ErasePage(uint32_t page_addr)
{
	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);

	/* Set the ERASE bit */
	FLASH->PECR |= FLASH_PECR_ERASE;
	/* Set PROG bit */
	FLASH->PECR |= FLASH_PECR_PROG;

	/* Write 00000000h to the first word of the program page to erase */
	*(volatile uint32_t *)page_addr = 0x00000000;

	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);

	/* If the erase operation is completed, disable the ERASE and PROG bits */
	FLASH->PECR &= ~FLASH_PECR_PROG;
	FLASH->PECR &= ~FLASH_PECR_ERASE;
}

/* fast program word */
void FLASH_FastProgramWord(uint32_t addr, uint32_t data)
{
	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);
    /* If the previous operation is completed, proceed to program the new
     * word */
    *(volatile uint32_t *)addr = data;
    /* Wait for last operation to be completed */
    while (FLASH->SR & FLASH_SR_BSY);
}

/* data eeprom unlock */
void DATA_EEPROM_Unlock(void)
{
	if (FLASH->PECR & FLASH_PECR_PELOCK) {
		/* Unlocking the Data memory and FLASH_PECR register access*/
		FLASH->PEKEYR = FLASH_PEKEY1;
		FLASH->PEKEYR = FLASH_PEKEY2;
	}
}

/* data eeprom lock */
void DATA_EEPROM_Lock(void)
{
  /* Set the PELOCK Bit to lock the data memory and FLASH_PECR register access */
  FLASH->PECR |= FLASH_PECR_PELOCK;
}

/* Enables or disables DATA EEPROM fixed Time programming (2*Tprog) */
void DATA_EEPROM_FixedTimeProgramCmd(int state)
{
	if (state) {
		FLASH->ACR |= FLASH_PECR_FTDW;
	} else {
		FLASH->ACR &= ~(FLASH_PECR_FTDW);
	}
}

/* Erase a word in data memory.*/
void DATA_EEPROM_EraseWord(uint32_t addr)
{
	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);

	/* Write "00000000h" to valid address in the data memory" */
	*(volatile uint32_t *) addr = 0x00000000;
}

/* program byte */
void DATA_EEPROM_FastProgramByte(uint32_t addr, uint8_t data)
{
	uint32_t tmp = 0, tmpaddr = 0;

	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);
    /* Clear the FTDW bit */
    FLASH->PECR &= (uint32_t)(~((uint32_t)FLASH_PECR_FTDW));

    if (data != 0x00) {
      /* If the previous operation is completed, proceed to write the new
       * data */
      *(volatile uint8_t *)addr = data;
      /* Wait for last operation to be completed */
      while (FLASH->SR & FLASH_SR_BSY);
    } else {
    	/* get word */
    	tmpaddr = addr & 0xFFFFFFFC;
    	tmp = * (volatile uint32_t *) tmpaddr;
    	tmpaddr = 0xFF << (8 * (addr & 0x3));
    	tmp &= ~tmpaddr;
    	/* clear */
    	DATA_EEPROM_EraseWord(addr & 0xFFFFFFFC);
    	/* re-program */
    	DATA_EEPROM_FastProgramWord((addr & 0xFFFFFFFC), tmp);
    }
}

/* program half-word */
void DATA_EEPROM_FastProgramHalfWord(uint32_t addr, uint16_t data)
{
	uint32_t tmp = 0, tmpaddr = 0;

	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);

	/* Clear the FTDW bit */
	FLASH->PECR &= (uint32_t)(~((uint32_t)FLASH_PECR_FTDW));

	if (data != 0x0000) {
		/* If the previous operation is completed, proceed to write the new data */
		*(volatile uint16_t *)addr = data;
		/* Wait for last operation to be completed */
		while (FLASH->SR & FLASH_SR_BSY);
	} else {
		/* fits into word */
		if ((addr & 0x3) != 0x3) {
			tmpaddr = addr & 0xFFFFFFFC;
			tmp = * (volatile uint32_t *) tmpaddr;
			tmpaddr = 0xFFFF << (0x8 * (addr & 0x3));
			tmp &= ~tmpaddr;
			/* erase */
			DATA_EEPROM_EraseWord(addr & 0xFFFFFFFC);
			/* reprogram */
			DATA_EEPROM_FastProgramWord((addr & 0xFFFFFFFC), tmp);
		/* does not fit into one word */
		} else {
			DATA_EEPROM_FastProgramByte(addr, data & 0xff);
			DATA_EEPROM_FastProgramByte(addr + 1, data >> 8);
		}
	}
}

/* Programs a word at a specified address in data memory. */
void DATA_EEPROM_FastProgramWord(uint32_t addr, uint32_t data)
{
	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);
    /* Clear the FTDW bit */
    FLASH->PECR &= ~FLASH_PECR_FTDW;
    /* If the previous operation is completed, proceed to program the new data */
    *(volatile uint32_t *)addr = data;
    /* Wait for last operation to be completed */
    while (FLASH->SR & FLASH_SR_BSY);
}

/* Programs a word at a specified address in data memory without erase. */
void DATA_EEPROM_ProgramWord(uint32_t addr, uint32_t data)
{
	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);

	*(volatile uint32_t *)addr = data;

	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);
}

/* unlock option bytes */
void FLASH_OB_Unlock(void)
{
	if (FLASH->PECR & FLASH_PECR_OPTLOCK) {
		/* Unlocking the data memory and FLASH_PECR register access */
		DATA_EEPROM_Unlock();

		/* Unlocking the option bytes block access */
		FLASH->OPTKEYR = FLASH_OPTKEY1;
		FLASH->OPTKEYR = FLASH_OPTKEY2;
	}
}

/* lock option bytes */
void FLASH_OB_Lock(void)
{
	/* Set the OPTLOCK Bit to lock the option bytes block access */
	FLASH->PECR |= FLASH_PECR_OPTLOCK;
}

/* option byte launch */
void FLASH_OB_Launch(void)
{
	/* Set the OBL_Launch bit to launch the option byte loading */
	FLASH->PECR |= FLASH_PECR_OBL_LAUNCH;
}

/* configure option bytes */
void FLASH_OB_UserConfig(uint8_t flags)
{
	uint32_t tmp;
	/* set new flags */
	tmp = flags | (OB->USER & 0x80);
	/* build up */
	tmp = (0xFF << 24) | ((~tmp & 0xff) << 16) | (0x00 << 8) | tmp;
	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);
	/* Write the User Option Byte */
	OB->USER = tmp;
	/* Wait for last operation to be completed */
	while (FLASH->SR & FLASH_SR_BSY);
}

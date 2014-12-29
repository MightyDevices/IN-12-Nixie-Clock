/*
 * pwr.h
 *
 *  Created on: 01-08-2012
 *      Author: Tomek
 */

#ifndef STM32L_PWR_H_
#define STM32L_PWR_H_

#include <stm32l/stm32l.h>

/* base */
#define PWR_BASE							(0x40007000)
/* register base */
#define PWR									((pwr_t *) PWR_BASE)

/* registers */
typedef struct {
	reg32_t CR;
	reg32_t CSR;
} pwr_t;

/* PWR power control register */
#define PWR_CR_LPSDSR                       (0x0001)
#define PWR_CR_PDDS                         (0x0002)
#define PWR_CR_CWUF                         (0x0004)
#define PWR_CR_CSBF                         (0x0008)
#define PWR_CR_PVDE                         (0x0010)
#define PWR_CR_PLS                          (0x00E0)
#define PWR_CR_PLS_0                        (0x0020)
#define PWR_CR_PLS_1                        (0x0040)
#define PWR_CR_PLS_2                        (0x0080)
#define PWR_CR_PLS_LEV0                     (0x0000)
#define PWR_CR_PLS_LEV1                     (0x0020)
#define PWR_CR_PLS_LEV2                     (0x0040)
#define PWR_CR_PLS_LEV3                     (0x0060)
#define PWR_CR_PLS_LEV4                     (0x0080)
#define PWR_CR_PLS_LEV5                     (0x00A0)
#define PWR_CR_PLS_LEV6                     (0x00C0)
#define PWR_CR_PLS_LEV7                     (0x00E0)
#define PWR_CR_DBP                          (0x0100)
#define PWR_CR_ULP                          (0x0200)
#define PWR_CR_FWU                          (0x0400)
#define PWR_CR_VOS                          (0x1800)
#define PWR_CR_VOS_0                        (0x0800)
#define PWR_CR_VOS_1                        (0x1000)
#define PWR_CR_LPRUN                        (0x4000)

/* PWR power control/status register */
#define PWR_CSR_WUF                         (0x0001)
#define PWR_CSR_SBF                         (0x0002)
#define PWR_CSR_PVDO                        (0x0004)
#define PWR_CSR_VREFINTRDYF                 (0x0008)
#define PWR_CSR_VOSF                        (0x0010)
#define PWR_CSR_REGLPF                      (0x0020)
#define PWR_CSR_EWUP1                       (0x0100)
#define PWR_CSR_EWUP2                       (0x0200)
#define PWR_CSR_EWUP3                       (0x0400)


/* voltage scaling */
#define PWR_VOS_1V8							(1 << 11)
#define PWR_VOS_1V5							(2 << 11)
#define PWR_VOS_1V2							(3 << 11)

/* wakeup pins */
#define PWR_WKUP_P1							(0x0100)
#define PWR_WKUP_P2							(0x0200)
#define PWR_WKUP_P3							(0x0400)

/* regulators */
#define PWR_REGULATOR_ON                	(0x00000000)
#define PWR_REGULATOR_LP          			(0x00000001)

/* entry */
#define PWR_ENTRY_WFI              			(1)
#define PWR_ENTRY_WFE              			(2)

/* pvd levels */
#define PWR_PVDLEVEL_0                  	PWR_CR_PLS_LEV0
#define PWR_PVDLEVEL_1                  	PWR_CR_PLS_LEV1
#define PWR_PVDLEVEL_2                  	PWR_CR_PLS_LEV2
#define PWR_PVDLEVEL_3                  	PWR_CR_PLS_LEV3
#define PWR_PVDLEVEL_4                  	PWR_CR_PLS_LEV4
#define PWR_PVDLEVEL_5                  	PWR_CR_PLS_LEV5
#define PWR_PVDLEVEL_6                  	PWR_CR_PLS_LEV6

/* deinitialize power */
void PWR_DeInit(void);
/* enables or disables access to the RTC and backup registers */
void PWR_RTCAccessCmd(int state);
/* configures the voltage threshold detected by the Power Voltage
 * Detector(PVD) */
void PWR_PVDLevelConfig(uint32_t level);
/* power level detector enable/disable*/
void PWR_PVDCmd(int state);
/* Enables or disables the WakeUp Pin functionality. */
void PWR_WakeUpPinCmd(uint32_t pins, int state);
/* fast wakeup command enable/disable */
void PWR_FastWakeUpCmd(int state);
/* ultra low power command */
void PWR_UltraLowPowerCmd(int state);
/* Configures the voltage scaling range */
void PWR_VoltageScalingConfig(uint32_t scaling);
/* enter low power run mode */
void PWR_EnterLowPowerRunMode(int state);
/* enter sleep mode */
void PWR_EnterSleepMode(uint32_t regulator, int entry);
/* enter stop mode */
void PWR_EnterSTOPMode(uint32_t regulator, int entry);
/* enter standby mode */
void PWR_EnterSTANDBYMode(void);
/* enter or exit */
void PWR_LowPowerRunMode(int state);
/* clear flag */
void PWR_ClearFlag(uint32_t flag);

#endif /* STM32_PWR_H_ */

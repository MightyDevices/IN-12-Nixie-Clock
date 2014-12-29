/*
 * exti.h
 *
 *  Created on: 24-02-2013
 *      Author: Tomek
 */

#ifndef STM32L_EXTI_H_
#define STM32L_EXTI_H_

#include <stm32l/stm32l.h>

/* register base */
#define EXTI_BASE							(0x40010400)
/* rcc itself */
#define EXTI                 				((exti_t *) EXTI_BASE)

/* registers */
typedef struct {
	reg32_t IMR;
	reg32_t EMR;
	reg32_t RTSR;
	reg32_t FTSR;
	reg32_t SWIER;
	reg32_t PR;
} exti_t;

/* EXTI interrupt mask register */
#define EXTI_IMR_MR0                        (0x00000001)
#define EXTI_IMR_MR1                        (0x00000002)
#define EXTI_IMR_MR2                        (0x00000004)
#define EXTI_IMR_MR3                        (0x00000008)
#define EXTI_IMR_MR4                        (0x00000010)
#define EXTI_IMR_MR5                        (0x00000020)
#define EXTI_IMR_MR6                        (0x00000040)
#define EXTI_IMR_MR7                        (0x00000080)
#define EXTI_IMR_MR8                        (0x00000100)
#define EXTI_IMR_MR9                        (0x00000200)
#define EXTI_IMR_MR10                       (0x00000400)
#define EXTI_IMR_MR11                       (0x00000800)
#define EXTI_IMR_MR12                       (0x00001000)
#define EXTI_IMR_MR13                       (0x00002000)
#define EXTI_IMR_MR14                       (0x00004000)
#define EXTI_IMR_MR15                       (0x00008000)
#define EXTI_IMR_MR16                       (0x00010000)
#define EXTI_IMR_MR17                       (0x00020000)
#define EXTI_IMR_MR18                       (0x00040000)
#define EXTI_IMR_MR19                       (0x00080000)
#define EXTI_IMR_MR20                       (0x00100000)
#define EXTI_IMR_MR21                       (0x00200000)
#define EXTI_IMR_MR22                       (0x00400000)
#define EXTI_IMR_MR23                       (0x00800000)

/* EXTI event mask  register */
#define EXTI_EMR_MR0                        (0x00000001)
#define EXTI_EMR_MR1                        (0x00000002)
#define EXTI_EMR_MR2                        (0x00000004)
#define EXTI_EMR_MR3                        (0x00000008)
#define EXTI_EMR_MR4                        (0x00000010)
#define EXTI_EMR_MR5                        (0x00000020)
#define EXTI_EMR_MR6                        (0x00000040)
#define EXTI_EMR_MR7                        (0x00000080)
#define EXTI_EMR_MR8                        (0x00000100)
#define EXTI_EMR_MR9                        (0x00000200)
#define EXTI_EMR_MR10                       (0x00000400)
#define EXTI_EMR_MR11                       (0x00000800)
#define EXTI_EMR_MR12                       (0x00001000)
#define EXTI_EMR_MR13                       (0x00002000)
#define EXTI_EMR_MR14                       (0x00004000)
#define EXTI_EMR_MR15                       (0x00008000)
#define EXTI_EMR_MR16                       (0x00010000)
#define EXTI_EMR_MR17                       (0x00020000)
#define EXTI_EMR_MR18                       (0x00040000)
#define EXTI_EMR_MR19                       (0x00080000)
#define EXTI_EMR_MR20                       (0x00100000)
#define EXTI_EMR_MR21                       (0x00200000)
#define EXTI_EMR_MR22                       (0x00400000)
#define EXTI_EMR_MR23                       (0x00800000)

/* EXTI rising edge trigger selection register */
#define EXTI_RTSR_TR0                       (0x00000001)
#define EXTI_RTSR_TR1                       (0x00000002)
#define EXTI_RTSR_TR2                       (0x00000004)
#define EXTI_RTSR_TR3                       (0x00000008)
#define EXTI_RTSR_TR4                       (0x00000010)
#define EXTI_RTSR_TR5                       (0x00000020)
#define EXTI_RTSR_TR6                       (0x00000040)
#define EXTI_RTSR_TR7                       (0x00000080)
#define EXTI_RTSR_TR8                       (0x00000100)
#define EXTI_RTSR_TR9                       (0x00000200)
#define EXTI_RTSR_TR10                      (0x00000400)
#define EXTI_RTSR_TR11                      (0x00000800)
#define EXTI_RTSR_TR12                      (0x00001000)
#define EXTI_RTSR_TR13                      (0x00002000)
#define EXTI_RTSR_TR14                      (0x00004000)
#define EXTI_RTSR_TR15                      (0x00008000)
#define EXTI_RTSR_TR16                      (0x00010000)
#define EXTI_RTSR_TR17                      (0x00020000)
#define EXTI_RTSR_TR18                      (0x00040000)
#define EXTI_RTSR_TR19                      (0x00080000)
#define EXTI_RTSR_TR20                      (0x00100000)
#define EXTI_RTSR_TR21                      (0x00200000)
#define EXTI_RTSR_TR22                      (0x00400000)
#define EXTI_RTSR_TR23                      (0x00800000)

/* Falling edge trigger selection register */
#define EXTI_FTSR_TR0                       (0x00000001)
#define EXTI_FTSR_TR1                       (0x00000002)
#define EXTI_FTSR_TR2                       (0x00000004)
#define EXTI_FTSR_TR3                       (0x00000008)
#define EXTI_FTSR_TR4                       (0x00000010)
#define EXTI_FTSR_TR5                       (0x00000020)
#define EXTI_FTSR_TR6                       (0x00000040)
#define EXTI_FTSR_TR7                       (0x00000080)
#define EXTI_FTSR_TR8                       (0x00000100)
#define EXTI_FTSR_TR9                       (0x00000200)
#define EXTI_FTSR_TR10                      (0x00000400)
#define EXTI_FTSR_TR11                      (0x00000800)
#define EXTI_FTSR_TR12                      (0x00001000)
#define EXTI_FTSR_TR13                      (0x00002000)
#define EXTI_FTSR_TR14                      (0x00004000)
#define EXTI_FTSR_TR15                      (0x00008000)
#define EXTI_FTSR_TR16                      (0x00010000)
#define EXTI_FTSR_TR17                      (0x00020000)
#define EXTI_FTSR_TR18                      (0x00040000)
#define EXTI_FTSR_TR19                      (0x00080000)
#define EXTI_FTSR_TR20                      (0x00100000)
#define EXTI_FTSR_TR21                      (0x00200000)
#define EXTI_FTSR_TR22                      (0x00400000)
#define EXTI_FTSR_TR23                      (0x00800000)

/* EXTI software interrupt  event register */
#define EXTI_SWIER_SWIER0                   (0x00000001)
#define EXTI_SWIER_SWIER1                   (0x00000002)
#define EXTI_SWIER_SWIER2                   (0x00000004)
#define EXTI_SWIER_SWIER3                   (0x00000008)
#define EXTI_SWIER_SWIER4                   (0x00000010)
#define EXTI_SWIER_SWIER5                   (0x00000020)
#define EXTI_SWIER_SWIER6                   (0x00000040)
#define EXTI_SWIER_SWIER7                   (0x00000080)
#define EXTI_SWIER_SWIER8                   (0x00000100)
#define EXTI_SWIER_SWIER9                   (0x00000200)
#define EXTI_SWIER_SWIER10                  (0x00000400)
#define EXTI_SWIER_SWIER11                  (0x00000800)
#define EXTI_SWIER_SWIER12                  (0x00001000)
#define EXTI_SWIER_SWIER13                  (0x00002000)
#define EXTI_SWIER_SWIER14                  (0x00004000)
#define EXTI_SWIER_SWIER15                  (0x00008000)
#define EXTI_SWIER_SWIER16                  (0x00010000)
#define EXTI_SWIER_SWIER17                  (0x00020000)
#define EXTI_SWIER_SWIER18                  (0x00040000)
#define EXTI_SWIER_SWIER19                  (0x00080000)
#define EXTI_SWIER_SWIER20                  (0x00100000)
#define EXTI_SWIER_SWIER21                  (0x00200000)
#define EXTI_SWIER_SWIER22                  (0x00400000)
#define EXTI_SWIER_SWIER23                  (0x00800000)

/* EXTI pending register */
#define EXTI_PR_PR0                         (0x00000001)
#define EXTI_PR_PR1                         (0x00000002)
#define EXTI_PR_PR2                         (0x00000004)
#define EXTI_PR_PR3                         (0x00000008)
#define EXTI_PR_PR4                         (0x00000010)
#define EXTI_PR_PR5                         (0x00000020)
#define EXTI_PR_PR6                         (0x00000040)
#define EXTI_PR_PR7                         (0x00000080)
#define EXTI_PR_PR8                         (0x00000100)
#define EXTI_PR_PR9                         (0x00000200)
#define EXTI_PR_PR10                        (0x00000400)
#define EXTI_PR_PR11                        (0x00000800)
#define EXTI_PR_PR12                        (0x00001000)
#define EXTI_PR_PR13                        (0x00002000)
#define EXTI_PR_PR14                        (0x00004000)
#define EXTI_PR_PR15                        (0x00008000)
#define EXTI_PR_PR16                        (0x00010000)
#define EXTI_PR_PR17                        (0x00020000)
#define EXTI_PR_PR18                        (0x00040000)
#define EXTI_PR_PR19                        (0x00080000)
#define EXTI_PR_PR20                        (0x00100000)
#define EXTI_PR_PR21                        (0x00200000)
#define EXTI_PR_PR22                        (0x00400000)
#define EXTI_PR_PR23                        (0x00800000)

/* init struct */
typedef struct {
  uint32_t line;
  uint32_t mode;
  uint32_t trigger;
  uint32_t line_cmd;
} exti_init_t;

/* exti lines */
#define EXTI_LINE0       					(0x00000001)
#define EXTI_LINE1       					(0x00000002)
#define EXTI_LINE2       					(0x00000004)
#define EXTI_LINE3      	 				(0x00000008)
#define EXTI_LINE4       					(0x00000010)
#define EXTI_LINE5       					(0x00000020)
#define EXTI_LINE6       					(0x00000040)
#define EXTI_LINE7       					(0x00000080)
#define EXTI_LINE8       					(0x00000100)
#define EXTI_LINE9       					(0x00000200)
#define EXTI_LINE10      					(0x00000400)
#define EXTI_LINE11      					(0x00000800)
#define EXTI_LINE12      					(0x00001000)
#define EXTI_LINE13      					(0x00002000)
#define EXTI_LINE14      					(0x00004000)
#define EXTI_LINE15      					(0x00008000)
#define EXTI_LINE16      					(0x00010000)
#define EXTI_LINE17      					(0x00020000)
#define EXTI_LINE18      					(0x00040000)
#define EXTI_LINE19      					(0x00080000)
#define EXTI_LINE20      					(0x00100000)
#define EXTI_LINE21      					(0x00200000)
#define EXTI_LINE22      					(0x00400000)
#define EXTI_LINE23      					(0x00800000)

/* mode */
#define EXTI_MODE_INTERRUPT					(0x01)
#define EXTI_MODE_EVENT						(0x02)

/* trigger */
#define EXTI_TRIGGER_RISING					(0x01)
#define EXTI_TRIGGER_FALLING				(0x02)

/* reset registers */
void EXTI_DeInit(void);
/* initialize exti */
void EXTI_Init(exti_init_t *init);
/* initialize struct */
void EXTI_StructInit(exti_init_t *init);
/* generate sw interrupt */
void EXTI_GenerateSWInterrupt(uint32_t line);
/* clear pending flag */
void EXTI_ClearFlag(uint32_t line);
/* Checks whether the specified EXTI line is asserted or not. */
uint32_t EXTI_GetITStatus(void);


#endif /* EXTI_H_ */

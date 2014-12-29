/*
 * stepup.h
 *
 *  Created on: 17-12-2014
 *      Author: Tomek
 */

#ifndef DEV_STEPUP_H_
#define DEV_STEPUP_H_

#include <stdint.h>

/* initialize step up converter */
int StepUp_Init(void);
/* deinitialize step up converter */
int StepUp_Deinit(void);
/* enable/disable step up converter */
void StepUp_Cmd(uint8_t state);
/* return voltage */
uint32_t StepUp_GetVoltage(void);


#endif /* STEPUP_H_ */

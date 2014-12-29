/*
 * dev.c
 *
 *  Created on: 29-11-2014
 *      Author: Tomek
 */

#include <dev/usart1.h>
#include <dev/stepup.h>
#include <dev/display.h>
#include <dev/dots.h>
#include <dev/hsi.h>
#include <dev/buttons.h>
#include <dev/failsafe.h>
#include <sys/err.h>

/* initialize devices */
int Dev_Init(void)
{
	/* status */
	int rc = EOK;

	/* initialize debug interface */
	rc |= USART1_Init();
	/* initialize buttons */
	rc |= Buttons_Init();
	/* enable hsi */
	rc |= HSI_Init();
	/* initialize step up */
	rc |= StepUp_Init();
	/* initialize display */
	rc |= Display_Init();
	/* initialize separator dots */
	rc |= Dots_Init();
	/* failsafe monitor */
	rc |= Failsafe_Init();


	/* report status */
	return EOK;
}

/* deinitialize */
int Dev_Deinit(void)
{
	/* status */
	int rc = EOK;

	/* deinit bluenrg */
	rc |= Failsafe_Deinit();
	/* deinit gyroscope */
	rc |= Dots_Deinit();
	/* deinit magnetometer */
	rc |= Display_Deinit();
	/* deinit lsm9ds0 accelerometer */
	rc |= StepUp_Deinit();
	/* deinit hsi */
	rc |= HSI_Deinit();
	/* deinit buttons */
	rc |= Buttons_Deinit();
	/* deinit uart1 */
	rc |= USART1_Deinit();

	/* report status */
	return EOK;
}

/* device polling */
void Dev_Poll(void)
{

}

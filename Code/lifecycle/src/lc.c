/*
 * lc.c
 *
 *  Created on: 11-04-2014
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/nvic.h>
#include <stm32l/adc.h>
#include <stm32l/dma.h>
#include <stm32l/timer.h>
#include <stm32l/gpio.h>
#include <dev/dev.h>
#include <dev/usart1.h>
#include <dev/m2m.h>
#include <dev/systime.h>
#include <dev/stepup.h>
#include <dev/ob.h>
#include <dev/display.h>
#include <dev/dots.h>
#include <dev/hsi.h>
#include <dev/power.h>
#include <dev/buttons.h>
#include <dev/lse.h>
#include <dev/realtime.h>
#include <dev/extimux.h>
#include <dev/failsafe.h>
#include <dev/watchdog.h>
#include <nixie/nixie.h>
#include <nixie/shutdown.h>
#include <lifecycle/lc.h>
#include <test/test.h>
#include <sys/time.h>
#include <sys/err.h>

#define DEBUG
#include <dev/debug.h>

/* power save state machine */
/* reset state */
#define LC_RESET							0
/* initialize all modules */
#define LC_INIT								1
/* normal power state */
#define LC_NORMAL							2
/* deinitialize all modules */
#define LC_DEINIT							3
/* shutdown */
#define LC_SHUTDOWN							4
/* current state and mode of operation */
static uint8_t state, mode;

/* processing in reset state */
static void LC_ResetState(void)
{
	/* go to init state */
	state = LC_INIT; mode = LC_MODE_RUN;
}

/* initialize */
 void LC_InitState(void)
{
	/* init status */
	int rc = EOK;

	/* initialize all devices */
	rc |= Dev_Init();
	/* funbrush init */
	rc |= Nixie_Init();
	/* initialize tests */
	rc |= Test_Init();

	/* didn't manage to wake every module up */
	if (rc != EOK) {
		state = LC_DEINIT;
	/* all modules are up! */
	} else {
		state = LC_NORMAL;
	}
}

/* normal state */
static void LC_NormalState(void)
{
	/* poll all devices */
	Dev_Poll();
	/* funbrush poll */
	Nixie_Poll();
	/* poll tests */
	Test_Poll();

	/* kick watchdog */
	Watchdog_Kick();

	/* shutdown flag was set */
	if (mode != LC_MODE_RUN) {
		state = LC_DEINIT;
	}
}

/* de-initialize */
 void LC_DeinitState(void)
{
	/* init status */
	int rc = EOK;

	/* test deinit */
	rc |= Test_Deinit();
	/* funbrush deinit */
	rc |= Nixie_Deinit();
	/* de-initialize all devices */
	rc |= Dev_Deinit();

	/* go to shutdown state */
	if (rc == EOK) {
		state = LC_SHUTDOWN;
	}
}

/* shutdown state */
static void LC_ShutdownState(void)
{
	/* polling in shutdown mode */
	NixieShutdown_Poll();
	USART1_Init();
	dprintf("EXITED SHDN\n");SysTime_Delay(10);
	USART1_Deinit();

	/* end of shutdown mode? */
	if (mode != LC_MODE_SHDN) {
		state = LC_INIT;
	}
}

/* initialize chip */
void LC_Init(void)
{
	/* option bytes reset */
	OB_Init();
	/* reset rcc */
	RCC_DeInit();

	/* set clock */
	RCC_MSIRangeConfig(MSI_FREQ_4M194);

	/* reset interrupt unit */
	NVIC_Init();
	/* enable interrupts */
	STM32_EnableInterrupts();

	/* power controller */
	Power_Init();
	/* initialize m2m transfers */
	M2M_Init();
	/* initialize time base */
	SysTime_Init();
	/* initialize exti mux */
	ExtiMux_Init();
	/* start lse */
	LSE_Init();
	/* initialize real time clock */
	RealTime_Init();

	/* initialize watchdog */
	Watchdog_Init();
}

/* polling */
void LC_Poll(void)
{
	/* main state machine */
	switch (state) {
	/* reset */
	case LC_RESET : {
		LC_ResetState();
	} break;
	/* initialize normal operation */
	case LC_INIT : {
		LC_InitState();
	} break;
	/* normal operation */
	case LC_NORMAL : {
		LC_NormalState();
	} break;
	/* de-initialize */
	case LC_DEINIT : {
		LC_DeinitState();
	} break;
	/* shutdown mode */
	case LC_SHUTDOWN : {
		LC_ShutdownState();
	} break;
	}
}

/* puts device to sleep */
void LC_SetMode(uint8_t new_mode)
{
	mode = new_mode;
}

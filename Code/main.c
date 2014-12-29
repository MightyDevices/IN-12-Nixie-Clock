/*
 * main.c
 *
 *      Author: Tomek
 */


#include <lifecycle/lc.h>
#include <sys/time.h>

/* system entry point */
int main(void)
{
	/* initialize device */
	LC_Init();

	/* main program loop */
	for (;;) {
		/* process device routines */
		LC_Poll();
	}

	/* never reached */
	return 0;
}



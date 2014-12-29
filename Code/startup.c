/*
 * startup.c
 *
 *  Created on: 23-04-2012
 *      Author: Tomek
 */

#include <stdint.h>

/* data pointers */
/* bss section */
extern  uint32_t __bss_start, __bss_end;
/* initialized data section */
extern  uint32_t __data_start, __data_end, __datai_start;
/* initial stack pointer */
extern  uint32_t __stack;

/* main program routine */
extern int main(void);
/* default reset handler */
void ResetHandler(void);

/* default handler */
static void DefaultHandler(void)
{
	while (1);
}

/* init vector table */
volatile void *  _init_vectors[] __attribute__ ((section(".vectors_flash"))) = {
	/* initial stack pointer */
	&__stack,
	/* initial reset handler */
	ResetHandler,
	/* nmi */
	DefaultHandler,
	/* hard fault */
	DefaultHandler,
	/* memmanage */
	DefaultHandler,
	/* bus fault */
	DefaultHandler,
	/* usage fault */
	DefaultHandler,
	/* reserved */
	0, 0, 0, 0,
	/* svc */
	DefaultHandler,
	/* debug mon */
	DefaultHandler,
	/* reserved */
	0,
	/* pend sv */
	DefaultHandler,
	/* systick */
	DefaultHandler
};

/* default reset handler */
void ResetHandler(void)
{
	volatile uint32_t *start, *end, *starti;

	/* copy data section */
	start = &__data_start;
	end = &__data_end;
	starti = &__datai_start;
	/* copy */
	while (start < end) {
		*(start++) = *(starti++);
	}

	/* zero bss section */
	start = &__bss_start;
	end = &__bss_end;
	/* zero */
	while (start < end) {
		*(start++) = 0;
	}

	/* jump to main */
	main();

	/* prevent unwanted code execution */
	for (;;);
}





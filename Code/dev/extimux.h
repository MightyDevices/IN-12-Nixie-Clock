/*
 * extimux.h
 *
 *  Created on: 20-12-2014
 *      Author: Tomek
 */

#ifndef DEV_EXTIMUX_H_
#define DEV_EXTIMUX_H_

/* exti callback type */
typedef  void (*exticb_t) (void);

/* exti vector ids */
#define EXTIMUX_EXTI5						0
#define EXTIMUX_EXTI6						1
#define EXTIMUX_EXTI7						2
#define EXTIMUX_EXTI8						3
#define EXTIMUX_EXTI9						4

/* initialize exti */
int ExtiMux_Init(void);
/* deinit exti muxer */
int ExtiMux_Deinit(void);
/* register interrupt callback */
void ExtiMux_Register(uint8_t num, exticb_t cb);
/* unregister routine */
void ExtiMux_Unregister(uint8_t num);

#endif /* EXTIMUX_H_ */

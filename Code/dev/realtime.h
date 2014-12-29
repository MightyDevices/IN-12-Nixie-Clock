/*
 * realtime.h
 *
 *  Created on: 14-12-2014
 *      Author: Tomek
 */

#ifndef DEV_REALTIME_H_
#define DEV_REALTIME_H_

/* initialize real time clock */
int RealTime_Init(void);
/* deinitialize realtime clock */
int RealTime_Deinit(void);
/* returns day of week */
uint8_t RealTime_GetDayofWeek(uint16_t y, uint8_t m, uint8_t d);
/* set up clock */
void RealTime_SetTime(uint8_t h, uint8_t m, uint8_t s);
/* set date */
void RealTime_SetDate(uint8_t y, uint8_t m, uint8_t d);
/* get current time */
void RealTime_GetTime(uint8_t *h, uint8_t *m, uint8_t *s);
/* get current date */
void RealTime_GetDate(uint8_t *y, uint8_t *m, uint8_t *d, uint8_t *w);


#endif /* REALTIME_H_ */

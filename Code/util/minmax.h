/*
 * minmax.h
 *
 *  Created on: 22-12-2012
 *      Author: Tomek
 */

#ifndef UTIL_MINMAX_H_
#define UTIL_MINMAX_H_

/* max macro definition */
#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/* min macro definition */
#define min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


#endif /* PARAM_H_ */

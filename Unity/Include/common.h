#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus	/* for C++ */

#ifndef BOOL
#define BOOL bool
#endif

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

#else	/* for C */

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#endif

#endif  /* COMMON_H_ */

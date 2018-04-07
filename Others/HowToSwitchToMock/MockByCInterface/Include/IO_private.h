#ifndef IO_PRIVATE_H_
#define IO_PRIVATE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct IOInterface_t * IOInterface;
typedef struct IO_t * IO;

typedef struct IO_t {
	IOInterface vtable;
	const char * type;
	int id;
} IO_t;

typedef struct IOInterface_t {
	void (*destroy)(IO self);
	void (*write)(IO self, intptr_t address, uint32_t data);
	uint32_t (*read)(IO self, intptr_t address);
} IOInterface_t;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_PRIVATE_H_ */

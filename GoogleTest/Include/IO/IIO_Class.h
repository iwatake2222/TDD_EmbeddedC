#ifndef IIO_CLASS_H_
#define IIO_CLASS_H_

#include <stdint.h>

typedef uint32_t ioAddress;
typedef uint32_t ioData;

class IIO_Class {
public:
	virtual ~IIO_Class() {}
	virtual void write(ioAddress address, ioData data) = 0;
	virtual ioData read(ioAddress address) = 0;
};

#endif /* IIO_CLASS_H_ */

#ifndef IIO_H_
#define IIO_H_

#include <stdint.h>

class IIO
{
public:
	virtual ~IIO() {}
	
	virtual void write(intptr_t address, uint32_t data) = 0;
	virtual uint32_t read(intptr_t address) = 0;

};

#endif /* IIO_H_ */

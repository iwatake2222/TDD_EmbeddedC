#ifndef IO_CLASS_H_
#define IO_CLASS_H_

#include "IO/IIO_Class.h"

class IO_Class : public IIO_Class {
public:
	IO_Class();
	virtual ~IO_Class();
	virtual void write(ioAddress address, ioData data);
	virtual ioData read(ioAddress address);
};

#endif /* IO_CLASS_H_ */

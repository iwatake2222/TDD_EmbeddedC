#ifndef DEVICE_DRIVER_X_H_
#define DEVICE_DRIVER_X_H_

#include <stdint.h>
#include "IIO.h"

class DeviceDriverX
{
public:
	static const intptr_t BASE_ADDRESS = 0xF8000000;

public:
	DeviceDriverX(intptr_t baseAddress, IIO *io);
	DeviceDriverX(IIO *io);
	~DeviceDriverX();
	
	void powerOn();

private:
	intptr_t m_baseAddress;
	IIO * m_io;
};

#endif /* DEVICE_DRIVER_X_H_ */

#include "DeviceDriverX.h"


#define REG_OFFSET_POWER  0x00
#define REG_OFFSET_STATUS 0x04


DeviceDriverX::DeviceDriverX(intptr_t baseAddress, IIO *io)
	: m_baseAddress(baseAddress), m_io(io)
{
}

DeviceDriverX::DeviceDriverX(IIO *io)
	: m_baseAddress(BASE_ADDRESS), m_io(io)
{
}

DeviceDriverX::~DeviceDriverX()
{
}

void DeviceDriverX::powerOn()
{
	m_io->write(m_baseAddress + 0x00, 0xAB);

	int status;
	do {
		status = m_io->read(m_baseAddress + 0x04);
	} while(status == 0);
}

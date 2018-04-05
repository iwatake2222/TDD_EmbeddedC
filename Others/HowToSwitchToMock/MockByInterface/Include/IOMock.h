#ifndef IO_MOCK_H_
#define IO_MOCK_H_

#include "IIO.h"

class IOMock : public IIO
{
public:
	IOMock();
	virtual ~IOMock() override;
	
	virtual void write(intptr_t address, uint32_t data) override final;
	virtual uint32_t read(intptr_t address) override final;
};

#endif /* IO_MOCK_H_ */

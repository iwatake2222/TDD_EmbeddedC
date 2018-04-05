#ifndef IO_H_
#define IO_H_

#include "IIO.h"

class IO : public IIO
{
public:
	IO();
	virtual ~IO() override;
	
	virtual void write(intptr_t address, uint32_t data) override final;
	virtual uint32_t read(intptr_t address) override final;
};

#endif /* IO_H_ */

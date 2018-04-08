#include <IO/Flash.h>
#include <IO/m28w160ect.h>
#include <MockIO.h>
#include "FakeMicroTime.h"
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

extern "C" {
	void MockIO2_write(ioAddress address, ioData data)
	{
		mock().actualCall("IO_write")
			.withIntParameter("address", (int)address)
			.withIntParameter("data", (int)data);
	}


	ioData MockIO2_read(ioAddress address)
	{
		mock().actualCall("IO_read")
			.withIntParameter("address", (int)address);
		return (ioData)mock().returnValue().getIntValue();
	}
}


TEST_GROUP(FlashTest_CppUMock)
{
	ioAddress m_address;
	ioData m_data;
	int m_result;

	void setup()
	{
		UT_PTR_SET(IO_write, MockIO2_write);
		UT_PTR_SET(IO_read, MockIO2_read);
		m_address = 0x1000;
		m_data = 0xBEEF;
		m_result = -1;
		Flash_create();
	}

	void teardown()
	{
		Flash_destroy();
		mock().checkExpectations();
		mock().clear();
	}
};

TEST(FlashTest_CppUMock, WriteSucceeds_ImmediatelyReady)
{
	/* Set expected IO access sequence */
	mock().expectOneCall("IO_write")
		.withParameter("address", COMMAND_REGISTER)
		.withParameter("data", PROGRAM_COMMAND);
	mock().expectOneCall("IO_write")
		.withParameter("address", m_address)
		.withParameter("data", m_data);
	mock().expectOneCall("IO_read")
		.withParameter("address", STATUS_REGISTER)
		.andReturnValue((int)READY_BIT);
	mock().expectOneCall("IO_read")
		.withParameter("address", m_address)
		.andReturnValue((int)m_data);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	LONGS_EQUAL(FLASH_SUCCESS, m_result);
}




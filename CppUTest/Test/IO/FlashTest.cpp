#include <IO/Flash.h>
#include <IO/m28w160ect.h>
#include <MockIO.h>
#include "FakeMicroTime.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(Flash)
{
	ioAddress m_address;
	ioData m_data;
	int m_result;

	void setup()
	{
		UT_PTR_SET(IO_write, MockIO_write);
		UT_PTR_SET(IO_read, MockIO_read);
		m_address = 0x1000;
		m_data = 0xBEEF;
		m_result = -1;
		MockIO_create(20);
		Flash_create();
	}

	void teardown()
	{
		Flash_destroy();
		/* Check IO access sequence */
		MockIO_verify_complete();
		MockIO_destroy();
	}
};

TEST(Flash, WriteSucceeds_ImmediatelyReady)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(m_address, m_data);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	LONGS_EQUAL(FLASH_SUCCESS, m_result);
}

TEST(Flash, WriteSucceeds_NotImmediatelyReady)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, 0);
	MockIO_expect_readThenReturn(STATUS_REGISTER, 0);
	MockIO_expect_readThenReturn(STATUS_REGISTER, 0);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(m_address, m_data);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	LONGS_EQUAL(FLASH_SUCCESS, m_result);
}


TEST(Flash, WriteFails_VppError)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT | VPP_ERROR_BIT);
	MockIO_expect_write(COMMAND_REGISTER, RESET_COMMAND);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	LONGS_EQUAL(FLASH_VPP_ERROR, m_result);
}

TEST(Flash, WriteFails_FlashReadBackError)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(m_address, m_data - 1);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	LONGS_EQUAL(FLASH_READ_BACK_ERROR, m_result);
}

TEST(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, ~READY_BIT);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(m_address, m_data);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	LONGS_EQUAL(FLASH_SUCCESS, m_result);
}

TEST(Flash, WriteFails_Timeout)
{
	FakeMicroTime_init(0, 500);
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	for (int i = 0; i < 10; i++) {
		MockIO_expect_readThenReturn(STATUS_REGISTER, ~READY_BIT);
	}

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	LONGS_EQUAL(FLASH_TIMEOUT_ERROR, m_result);
}



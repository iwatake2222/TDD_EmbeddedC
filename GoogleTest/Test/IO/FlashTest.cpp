#include <IO/Flash.h>
#include <IO/m28w160ect.h>
#include <MockIO.h>
#include "FakeMicroTime.h"
#include "gtest/gtest.h"

class FlashTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		m_saved_IO_write = IO_write;
		m_saved_IO_read = IO_read;
		IO_write = MockIO_write;
		IO_read = MockIO_read;
		m_address = 0x1000;
		m_data = 0xBEEF;
		m_result = -1;
		MockIO_create(20);
		Flash_create();
	}
	
	virtual void TearDown()
	{
		Flash_destroy();
		/* Check IO access sequence */
		MockIO_verify_complete();
		MockIO_destroy();
		IO_write = m_saved_IO_write;
		IO_read = m_saved_IO_read;
	}

	void (*m_saved_IO_write)(ioAddress address, ioData data);
	ioData (*m_saved_IO_read)(ioAddress address);
	ioAddress m_address;
	ioData m_data;
	int m_result;
};


TEST_F(FlashTest, WriteSucceeds_ImmediatelyReady)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(m_address, m_data);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	EXPECT_EQ(FLASH_SUCCESS, m_result);
}

TEST_F(FlashTest, WriteSucceeds_NotImmediatelyReady)
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
	EXPECT_EQ(FLASH_SUCCESS, m_result);
}


TEST_F(FlashTest, WriteFails_VppError)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT | VPP_ERROR_BIT);
	MockIO_expect_write(COMMAND_REGISTER, RESET_COMMAND);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	EXPECT_EQ(FLASH_VPP_ERROR, m_result);
}

TEST_F(FlashTest, WriteFails_FlashReadBackError)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(m_address, m_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(m_address, m_data - 1);

	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	EXPECT_EQ(FLASH_READ_BACK_ERROR, m_result);
}

TEST_F(FlashTest, WriteSucceeds_IgnoresOtherBitsUntilReady)
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
	EXPECT_EQ(FLASH_SUCCESS, m_result);
}

TEST_F(FlashTest, WriteFails_Timeout)
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
	EXPECT_EQ(FLASH_TIMEOUT_ERROR, m_result);
}



#include <IO/Flash.h>
#include <IO/m28w160ect.h>
#include "FakeMicroTime.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;

class MockIO
{
public:
	MOCK_METHOD2(IO_write, void(ioAddress address, ioData data));
	MOCK_METHOD1(IO_read, ioData(ioAddress address));
};
MockIO *mockIO;

extern "C" {

static void MockIO_write_wrapper(ioAddress address, ioData data)
{
	mockIO->IO_write(address, data);
}

static ioData MockIO_read_wrapper(ioAddress address)
{
	return mockIO->IO_read(address);
}

}

class FlashTest2 : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		m_saved_IO_write = IO_write;
		m_saved_IO_read = IO_read;
		IO_write = MockIO_write_wrapper;
		IO_read = MockIO_read_wrapper;
		m_address = 0x1000;
		m_data = 0xBEEF;
		m_result = -1;
		Flash_create();
		mockIO = new MockIO();
	}
	
	virtual void TearDown()
	{
		Flash_destroy();
		IO_write = m_saved_IO_write;
		IO_read = m_saved_IO_read;
		delete mockIO;
	}

	void (*m_saved_IO_write)(ioAddress address, ioData data);
	ioData (*m_saved_IO_read)(ioAddress address);
	ioAddress m_address;
	ioData m_data;
	int m_result;
};


TEST_F(FlashTest2, WriteSucceeds_ImmediatelyReady)
{
	/* Set expected IO access sequence */
	InSequence dummy;
	EXPECT_CALL(*mockIO, IO_write(COMMAND_REGISTER, PROGRAM_COMMAND)).Times(AtLeast(1));
	EXPECT_CALL(*mockIO, IO_write(m_address, m_data)).Times(AtLeast(1));
	EXPECT_CALL(*mockIO, IO_read(STATUS_REGISTER)).WillOnce(Return((ioData)READY_BIT));
	EXPECT_CALL(*mockIO, IO_read(m_address)).WillOnce(Return((ioData)m_data));


	/* Call the target function */
	m_result = Flash_write(m_address, m_data);

	/* Check the result */
	EXPECT_EQ(FLASH_SUCCESS, m_result);
}


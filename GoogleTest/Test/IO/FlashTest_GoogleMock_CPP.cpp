#include <IO/Flash_Class.h>
#include <IO/m28w160ect.h>
#include "FakeMicroTime.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;


class FlashTest_GoogleMock_CPP : public ::testing::Test
{
private:
	class MockIO_Class : public IIO_Class {
	public:
		MOCK_METHOD2(write, void(ioAddress address, ioData data));
		MOCK_METHOD1(read, ioData(ioAddress address));
	};

protected:
	virtual void SetUp()
	{
		m_address = 0x1000;
		m_data = 0xBEEF;
		m_result = -1;
		m_mockIO = new MockIO_Class();
		m_flashClass = new Flash_Class(m_mockIO);
	}
	
	virtual void TearDown()
	{
		delete m_flashClass;
		delete m_mockIO;
	}

	MockIO_Class *m_mockIO;
	Flash_Class * m_flashClass;
	ioAddress m_address;
	ioData m_data;
	int m_result;
};


TEST_F(FlashTest_GoogleMock_CPP, WriteSucceeds_ImmediatelyReady)
{
	/* Set expected IO access sequence */
	InSequence dummy;
	EXPECT_CALL(*m_mockIO, write(COMMAND_REGISTER, PROGRAM_COMMAND)).Times(AtLeast(1));
	EXPECT_CALL(*m_mockIO, write(m_address, m_data)).Times(AtLeast(1));
	EXPECT_CALL(*m_mockIO, read(STATUS_REGISTER)).WillOnce(Return((ioData)READY_BIT));
	EXPECT_CALL(*m_mockIO, read(m_address)).WillOnce(Return((ioData)m_data));


	/* Call the target function */
	m_result = m_flashClass->write(m_address, m_data);

	/* Check the result */
	EXPECT_EQ(Flash_Class::FLASH_SUCCESS, m_result);
}


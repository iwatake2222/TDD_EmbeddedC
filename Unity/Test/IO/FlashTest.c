#include <IO/Flash.h>
#include <IO/m28w160ect.h>
#include <MockIO.h>
#include "FakeMicroTime.h"
#include <unity_fixture.h>


TEST_GROUP(Flash);

ioAddress s_address;
ioData s_data;
int s_result;

TEST_SETUP(Flash)
{
	UT_PTR_SET(IO_write, MockIO_write);
	UT_PTR_SET(IO_read, MockIO_read);
	s_address = 0x1000;
	s_data = 0xBEEF;
	s_result = -1;
	MockIO_create(20);
	Flash_create();
}

TEST_TEAR_DOWN(Flash)
{
	Flash_destroy();
	/* Check IO access sequence */
	MockIO_verify_complete();
	MockIO_destroy();
}

TEST(Flash, WriteSucceeds_ImmediatelyReady)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(s_address, s_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(s_address, s_data);

	/* Call the target function */
	s_result = Flash_write(s_address, s_data);

	/* Check the result */
	TEST_ASSERT_EQUAL(FLASH_SUCCESS, s_result);
}

TEST(Flash, WriteSucceeds_NotImmediatelyReady)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(s_address, s_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, 0);
	MockIO_expect_readThenReturn(STATUS_REGISTER, 0);
	MockIO_expect_readThenReturn(STATUS_REGISTER, 0);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(s_address, s_data);

	/* Call the target function */
	s_result = Flash_write(s_address, s_data);

	/* Check the result */
	TEST_ASSERT_EQUAL(FLASH_SUCCESS, s_result);
}


TEST(Flash, WriteFails_VppError)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(s_address, s_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT | VPP_ERROR_BIT);
	MockIO_expect_write(COMMAND_REGISTER, RESET_COMMAND);

	/* Call the target function */
	s_result = Flash_write(s_address, s_data);

	/* Check the result */
	TEST_ASSERT_EQUAL(FLASH_VPP_ERROR, s_result);
}

TEST(Flash, WriteFails_FlashReadBackError)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(s_address, s_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(s_address, s_data - 1);

	/* Call the target function */
	s_result = Flash_write(s_address, s_data);

	/* Check the result */
	TEST_ASSERT_EQUAL(FLASH_READ_BACK_ERROR, s_result);
}

TEST(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady)
{
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(s_address, s_data);
	MockIO_expect_readThenReturn(STATUS_REGISTER, ~READY_BIT);
	MockIO_expect_readThenReturn(STATUS_REGISTER, READY_BIT);
	MockIO_expect_readThenReturn(s_address, s_data);

	/* Call the target function */
	s_result = Flash_write(s_address, s_data);

	/* Check the result */
	TEST_ASSERT_EQUAL(FLASH_SUCCESS, s_result);
}

TEST(Flash, WriteFails_Timeout)
{
	FakeMicroTime_init(0, 500);
	/* Set expected IO access sequence */
	MockIO_expect_write(COMMAND_REGISTER, PROGRAM_COMMAND);
	MockIO_expect_write(s_address, s_data);
	for (int i = 0; i < 10; i++) {
		MockIO_expect_readThenReturn(STATUS_REGISTER, ~READY_BIT);
	}

	/* Call the target function */
	s_result = Flash_write(s_address, s_data);

	/* Check the result */
	TEST_ASSERT_EQUAL(FLASH_TIMEOUT_ERROR, s_result);
}

/*** TEST_RUNNER (Don't forget to call RUN_TEST_GROUP) ***/
TEST_GROUP_RUNNER(Flash)
{
	RUN_TEST_CASE(Flash, WriteSucceeds_ImmediatelyReady);
	RUN_TEST_CASE(Flash, WriteSucceeds_NotImmediatelyReady);
	RUN_TEST_CASE(Flash, WriteFails_VppError);
	RUN_TEST_CASE(Flash, WriteFails_FlashReadBackError);
	RUN_TEST_CASE(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady);
	RUN_TEST_CASE(Flash, WriteFails_Timeout);
}


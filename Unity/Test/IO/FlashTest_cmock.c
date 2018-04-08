#include <IO/Flash.h>
#include <IO/m28w160ect.h>
#include "FakeMicroTime.h"
#include "unity.h"
#include "cmock.h"
#include "unity_fixture.h"
#include "MockIO_cmock.h"

TEST_GROUP(Flash_cmock);

ioAddress s_address;
ioData s_data;
int s_result;

TEST_SETUP(Flash_cmock)
{
	extern void IO_cmock_write(ioAddress address, ioData data);
	extern ioData IO_cmock_read(ioAddress address);
	UT_PTR_SET(IO_write, IO_cmock_write);
	UT_PTR_SET(IO_read, IO_cmock_read);
	MockIO_Init();
	s_address = 0x1000;
	s_data = 0xBEEF;
	s_result = -1;
	Flash_create();
}

TEST_TEAR_DOWN(Flash_cmock)
{
	Flash_destroy();
	MockIO_Verify();
	MockIO_Destroy();
}



TEST(Flash_cmock, WriteSucceeds_ImmediatelyReady)
{
	/* Set expected IO access sequence */
	IO_write_Expect(COMMAND_REGISTER, PROGRAM_COMMAND);
	IO_write_Expect(s_address, s_data);
	IO_read_ExpectAndReturn(STATUS_REGISTER, (int)READY_BIT);
	IO_read_ExpectAndReturn(s_address, (int)s_data);

	/* Call the target function */
	s_result = Flash_write(s_address, s_data);

	/* Check the result */
	TEST_ASSERT_EQUAL(FLASH_SUCCESS, s_result);
}

/*** TEST_RUNNER (Don't forget to call RUN_TEST_GROUP) ***/
TEST_GROUP_RUNNER(Flash_cmock)
{
	RUN_TEST_CASE(Flash_cmock, WriteSucceeds_ImmediatelyReady);
}


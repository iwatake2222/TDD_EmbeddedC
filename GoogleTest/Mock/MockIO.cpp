#include <stdio.h>
#include <stdlib.h>
#include "MockIO.h"
#include "gtest/gtest.h"

static const char * report_expect_write_was_read =
    "Expected IO_Write(0x%x, 0x%x)\n"
    "\t        But was IO_Read(0x%x)";
static const char * report_read_wrong_address =
    "Expected IO_Read(0x%x) returns 0x%x;\n"
    "\t        But was IO_Read(0x%x)";
static const char * report_expect_read_was_write =
    "Expected IO_Read(0x%x) would return 0x%x)\n"
    "\t        But was IO_Write(0x%x, 0x%x)";
static const char * report_write_does_not_match =
    "Expected IO_Write(0x%x, 0x%x)\n"
    "\t        But was IO_Write(0x%x, 0x%x)";
static const char * report_too_many_write_expectations = "MockIO_Expect_IO_Write: Too many expectations";
static const char * report_too_many_read_expectations = "MockIO_Expect_IO_Read: Too many expectations";
static const char * report_MockIO_not_initialized = "MockIO not initialized, call MockIO_Create()";
static const char * report_write_but_out_of_expectations = "IO_Write(0x%x, 0x%x)";
static const char * report_read_but_out_of_expectations = "IO_Read(0x%x)";
static const char * report_no_more_expectations = "R/W %d: No more expectations but was ";
static const char * report_expectation_number = "R/W %d: ";

/*****************************************
 * Data containers and accessors
 *****************************************/
enum {
	FLASH_READ, FLASH_WRITE, NoExpectedValue = -1
};

typedef struct {
	int kind;
	ioAddress address;
	ioData data;
} Expectation;

static Expectation *s_expectations = NULL;
static int s_setExpectationCount;
static int s_getExpectationCount;
static int s_maxExpectationCount;
static int s_failureAlreadyReported = 0;
static Expectation s_expected;
static Expectation s_actual;

/*****************************************
 * Mock functions
 *****************************************/
static void fail(const char * message)
{
	s_failureAlreadyReported = 1;
	FAIL() << message;
}

static void failWhenNotInitialized(void)
{
	if (s_expectations == NULL) fail(report_MockIO_not_initialized);
}

static void failWhenNoRoomForExpectations(const char * message)
{
	failWhenNotInitialized();
	if (s_setExpectationCount >= s_maxExpectationCount) fail(message);
}

static void recordExpectation(int kind, ioAddress address, ioData data)
{
	s_expectations[s_setExpectationCount].kind = kind;
	s_expectations[s_setExpectationCount].address = address;
	s_expectations[s_setExpectationCount].data = data;
	s_setExpectationCount++;
}

void MockIO_create(int maxExpectations)
{
	s_expectations = (Expectation*)calloc(maxExpectations, sizeof(Expectation));
	s_setExpectationCount = 0;
	s_getExpectationCount = 0;
	s_maxExpectationCount = maxExpectations;
	s_failureAlreadyReported = 0;
}

void MockIO_destroy()
{
	if(s_expectations) free(s_expectations);
	s_expectations = NULL;
}

void MockIO_expect_write(ioAddress address, ioData data)
{
	failWhenNoRoomForExpectations(report_too_many_write_expectations);
	recordExpectation(FLASH_WRITE, address, data);
}

void MockIO_expect_readThenReturn(ioAddress address, ioData data)
{
	failWhenNoRoomForExpectations(report_too_many_write_expectations);
	recordExpectation(FLASH_READ, address, data);
}


static void setExpectedAndActual(ioAddress address, ioData data)
{
	s_expected.address = s_expectations[s_getExpectationCount].address;
	s_expected.data = s_expectations[s_getExpectationCount].data;
	s_actual.address = address;
	s_actual.data = data;
}

static void failExpectation(const char * expectationFailMessage)
{
	char message[100];
	int size = sizeof message - 1;
	int offset = snprintf(message, size,
			report_expectation_number, s_getExpectationCount + 1);
	snprintf(message + offset, size - offset,
			expectationFailMessage, s_expected.address, s_expected.data,
			s_actual.address, s_actual.data);
	fail(message);
}

static void failWhen(int condition, const char * expectationFailMessage)
{
	if (condition) failExpectation(expectationFailMessage);
}

static void failWhenNoUnusedExpectations(const char * format)
{
	char message[100];
	int size = sizeof message - 1;

	if (s_getExpectationCount >= s_setExpectationCount)
	{
		int offset = snprintf(message, size,
				report_no_more_expectations, s_getExpectationCount + 1);
		snprintf(message + offset, size - offset,
				format, s_actual.address, s_actual.data);
		fail(message);
	}
}

static int expectationIsNot(int kind)
{
	return kind != s_expectations[s_getExpectationCount].kind;
}

static int expectedAddressIsNot(ioAddress address)
{
	return address != s_expected.address;
}

static int expectedDataIsNot(ioData data)
{
	return s_expected.data != data;
}

void MockIO_write(ioAddress address, ioData data)
{
	setExpectedAndActual(address, data);
	failWhenNotInitialized();
	failWhenNoUnusedExpectations(report_write_but_out_of_expectations);
	failWhen(expectationIsNot(FLASH_WRITE), report_expect_read_was_write);
	failWhen(expectedAddressIsNot(address), report_write_does_not_match);
	failWhen(expectedDataIsNot(data), report_write_does_not_match);
	s_getExpectationCount++;
}

ioData MockIO_read(ioAddress address)
{
	setExpectedAndActual(address, NoExpectedValue);
	failWhenNotInitialized();
	failWhenNoUnusedExpectations(report_read_but_out_of_expectations);
	failWhen(expectationIsNot(FLASH_READ), report_expect_write_was_read);
	failWhen(expectedAddressIsNot(address), report_read_wrong_address);
	return s_expectations[s_getExpectationCount++].data;
}

static void failWhenNotAllExpectationsUsed(void)
{
	char format[] = "Expected %d reads/writes but got %d";
	char message[sizeof format + 5 + 5];

	if (s_getExpectationCount == s_setExpectationCount) return;

	snprintf(message, sizeof message, format, s_setExpectationCount, s_getExpectationCount);
	fail(message);
}


void MockIO_verify_complete()
{
	if (s_failureAlreadyReported) return;
	failWhenNotAllExpectationsUsed();
}

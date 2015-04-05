#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Mock_IO.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#if WIN32
#define snprintf _snprintf
#endif

enum
{
	FLASH_READ, FLASH_WRITE, NoExpectedValue = -1
};

typedef struct Expectation
{
	int kind;
	ioAddress addr;
	ioData value;
} Expectation;

static Expectation * expectations = 0;
static int setExpectationCount;
static int getExpectationCount;
static int maxExpectationCount;
static int failureAlreadyReported = 0;

static Expectation expected;
static Expectation actual;

static char * report_expect_write_was_read ="Expected IO_Write(0x%x, 0x%x)\n\tBut was IO_Read(0x%x)";
static char * report_read_wrong_address ="Expected IO_Read(0x%x) returns 0x%x;\n\tBut was IO_Read(0x%x)";
static char * report_expect_read_was_write ="Expected IO_Read(0x%x) would return 0x%x)\n\tBut was IO_Write(0x%x, 0x%x)";
static char * report_write_does_not_match ="Expected IO_Write(0x%x, 0x%x)\n\tBut was IO_Write(0x%x, 0x%x)";
static char * report_too_many_write_expectations ="MockIO_Expect_IO_Write: Too many expectations";
static char * report_too_many_read_expectations ="MockIO_Expect_IO_Read: Too many expectations";
static char * report_MockIO_not_initialized ="MockIO not initialized, call MockIO_Create()";
static char * report_write_but_out_of_expectations ="IO_Write(0x%x, 0x%x)";
static char * report_read_but_out_of_expectations ="IO_Read(0x%x)";
static const char * report_no_more_expectations ="R/W %d: No more expectations but was ";
static const char * report_expectation_number ="R/W %d: ";

void MockIO_Create(int maxExpectations)
{
	expectations = (Expectation*)calloc(maxExpectations, sizeof(Expectation));
	setExpectationCount = 0;
	getExpectationCount = 0;
	maxExpectationCount = maxExpectations;
	failureAlreadyReported = 0;
}

void MockIO_Destroy(void)
{
	if (expectations)
		free(expectations);
	expectations = 0;
}

static void fail(char * message)
{
	failureAlreadyReported = 1;
	Logger::WriteMessage(message);
}

static void failWhenNotInitialized(void)
{
	if (expectations == 0)
		fail(report_MockIO_not_initialized);
}

static void failWhenNoRoomForExpectations(char * message)
{
	failWhenNotInitialized();
	if (setExpectationCount >= maxExpectationCount)
		fail(message);
}

void recordExpectation(int kind, ioAddress addr, ioData data)
{
	expectations[setExpectationCount].kind = kind;
	expectations[setExpectationCount].addr = addr;
	expectations[setExpectationCount].value = data;
	setExpectationCount++;
}

void MockIO_Expect_Write(ioAddress addr, ioData value)
{
	failWhenNoRoomForExpectations(report_too_many_write_expectations);
	recordExpectation(FLASH_WRITE, addr, value);
}

void MockIO_Expect_ReadThenReturn(ioAddress addr, ioData value)
{
	failWhenNoRoomForExpectations(report_too_many_read_expectations);
	recordExpectation(FLASH_READ, addr, value);
}

static void failWhenNotAllExpectationsUsed(void)
{
	char format[] = "Expected %d reads/writes but got %d";
	char message[sizeof format + 5 + 5];

	if (getExpectationCount == setExpectationCount)
		return;

	snprintf(message, sizeof message, format, setExpectationCount,
		getExpectationCount);
	fail(message);
}

void MockIO_Verify_Complete(void)
{
	if (failureAlreadyReported)
		return;
	failWhenNotAllExpectationsUsed();
}

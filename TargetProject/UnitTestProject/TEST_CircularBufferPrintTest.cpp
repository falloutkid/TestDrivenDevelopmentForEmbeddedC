#include "stdafx.h"
#include "CppUnitTest.h"

#include <TargetApplication\CircularBuffer.h>
#include "FormatOutputSpy.h"
#include <TargetApplication\Utils.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_CircularBufferPrintTest)
	{
	public:
		CircularBuffer buffer;
		const char * expectedOutput;
		const char * actualOutput;

		int(*saveFormatOutput)(const char * format, ...);

		TEST_METHOD_INITIALIZE(setup)
		{
			saveFormatOutput = FormatOutput;
			FormatOutput = FormatOutputSpy;

			FormatOutputSpy_Create(100);
			actualOutput = FormatOutputSpy_GetOutput();
			buffer = CircularBuffer_Create(10);
		}

		TEST_METHOD_CLEANUP(teardown)
		{
			FormatOutput = saveFormatOutput;

			CircularBuffer_Destroy(buffer);
			FormatOutputSpy_Destroy();
		}

		TEST_METHOD(PrintEmpty)
		{
			expectedOutput = "Circular buffer content:\n<>\n";
			CircularBuffer_Print(buffer);
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		TEST_METHOD(PrintAfterOneIsPut)
		{
			expectedOutput = "Circular buffer content:\n<17>\n";
			CircularBuffer_Put(buffer, 17);
			CircularBuffer_Print(buffer);
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		TEST_METHOD(PrintNotYetWrappedOrFull)
		{
			expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";
			CircularBuffer_Put(buffer, 10);
			CircularBuffer_Put(buffer, 20);
			CircularBuffer_Put(buffer, 30);
			CircularBuffer_Print(buffer);
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		TEST_METHOD(PrintNotYetWrappedAndIsFull)
		{
			expectedOutput = "Circular buffer content:\n<31, 41, 59, 26, 53>\n";

			CircularBuffer b = CircularBuffer_Create(5);
			CircularBuffer_Put(b, 31);
			CircularBuffer_Put(b, 41);
			CircularBuffer_Put(b, 59);
			CircularBuffer_Put(b, 26);
			CircularBuffer_Put(b, 53);

			CircularBuffer_Print(b);

			Assert::AreEqual(expectedOutput, actualOutput);
			CircularBuffer_Destroy(b);
		}

		TEST_METHOD(PrintOldToNewWhenWrappedAndFull)
		{
			expectedOutput = "Circular buffer content:\n<201, 202, 203, 204, 999>\n";

			CircularBuffer b = CircularBuffer_Create(5);
			CircularBuffer_Put(b, 200);
			CircularBuffer_Put(b, 201);
			CircularBuffer_Put(b, 202);
			CircularBuffer_Put(b, 203);
			CircularBuffer_Put(b, 204);
			CircularBuffer_Get(b);
			CircularBuffer_Put(b, 999);

			CircularBuffer_Print(b);

			Assert::AreEqual(expectedOutput, actualOutput);
			CircularBuffer_Destroy(b);
		}
	};
}
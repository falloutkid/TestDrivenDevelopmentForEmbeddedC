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

		TEST_METHOD_INITIALIZE( setup)
		{
			saveFormatOutput = FormatOutput;
			FormatOutput = FormatOutputSpy;

			FormatOutputSpy_Create(100);
			actualOutput = FormatOutputSpy_GetOutput();
			buffer = CircularBuffer_Create(10);
		}

		TEST_METHOD_CLEANUP( teardown)
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
	};
}
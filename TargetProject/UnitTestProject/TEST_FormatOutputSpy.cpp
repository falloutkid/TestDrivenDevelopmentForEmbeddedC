#include "stdafx.h"
#include "CppUnitTest.h"
#include "FormatOutputSpy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_FormatOutputSpy)
	{
	public:
		int(*saveFormatOutput)(const char * format, ...);
		TEST_METHOD_INITIALIZE(setup)
		{
			saveFormatOutput = FormatOutput;
			FormatOutput = FormatOutputSpy;
		}

		TEST_METHOD_CLEANUP(teardown)
		{
			FormatOutput = saveFormatOutput;
			FormatOutputSpy_Destroy();
		}

		TEST_METHOD(HelloWorld)
		{
			FormatOutputSpy_Create(20);
			FormatOutput("Hello, World\n");
			Assert::AreEqual("Hello, World\n", FormatOutputSpy_GetOutput());
		}

		TEST_METHOD(LimitOutputBufferSize)
		{
			FormatOutputSpy_Create(4);
			FormatOutput("Hello, World\n");
			Assert::AreEqual("Hell", FormatOutputSpy_GetOutput());
		}

		TEST_METHOD(PrintMultipleTimes)
		{
			FormatOutputSpy_Create(25);
			FormatOutput("Hello");
			FormatOutput(", World\n");
			Assert::AreEqual("Hello, World\n", FormatOutputSpy_GetOutput());
		}
	};
}
#include "stdafx.h"
#include "CppUnitTest.h"

#include <TargetApplication\LedDriver.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_LedDeiver)
	{
	public:
		TEST_CLASS_INITIALIZE(LedDriverInitialize){}

		TEST_CLASS_CLEANUP(LedDriverCleanup){}

		TEST_METHOD(LedOffAfterCreate)
		{
			uint16_t virtual_led = 0xFFFF;
			LedDriver_Create(virtual_led);
			Assert::AreEqual(0, (int)virtual_led);
		}
	};
}
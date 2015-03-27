#include "stdafx.h"
#include "CppUnitTest.h"

#include <TargetApplication\LedDriver.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	static uint16_t virtual_led;
	TEST_CLASS(TEST_LedDeiver)
	{	
	public:

		TEST_CLASS_INITIALIZE(LedDriverInitialize)
		{
			LedDriver_Create(&virtual_led);
		}

		TEST_CLASS_CLEANUP(LedDriverCleanup){}

		TEST_METHOD(LedOffAfterCreate)
		{		
			Assert::AreEqual(0, (int)virtual_led);
		}

		TEST_METHOD(TurnOnLedOne)
		{
			LedDriver_TurnOn(1);
			Assert::AreEqual(1, (int)virtual_led);
		}

		TEST_METHOD(TurnOffLedOne)
		{
			LedDriver_TurnOn(1);
			LedDriver_TurnOn(0);
			Assert::AreEqual(1, (int)virtual_led);
		}
	};
}
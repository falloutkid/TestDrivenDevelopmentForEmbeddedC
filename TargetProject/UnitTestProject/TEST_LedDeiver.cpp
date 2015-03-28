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

		TEST_METHOD_INITIALIZE(LedDriverInitialize)
		{
			LedDriver_Create(&virtual_led);
		}

		TEST_METHOD_CLEANUP(LedDriverCleanup){}

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

		TEST_METHOD(TurnOnMultipleLeds)
		{
			LedDriver_TurnOn(9);
			LedDriver_TurnOn(8);

			Assert::AreEqual(0x180, (int)virtual_led);
		}

		TEST_METHOD(TurnOffAnyLed)
		{
			LedDriver_TurnAllOn();
			LedDriver_TurnOff(8);

			Assert::AreEqual(0xFF7F, (int)virtual_led);
		}

		TEST_METHOD(AllOn)
		{
			LedDriver_TurnAllOn();

			Assert::AreEqual(0xffff, (int)virtual_led);
		}

		TEST_METHOD(AllOff)
		{
			LedDriver_TurnAllOn();
			LedDriver_TurnAllOff();

			Assert::AreEqual(0, (int)virtual_led);
		}
	};
}
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

		TEST_METHOD(LedMemoryReadCheck)
		{
			virtual_led = 0xFFFF;
			LedDriver_TurnOn(8);

			Assert::AreEqual(0x80, (int)virtual_led);
		}

		TEST_METHOD(OutOfBoundsChangesNothoingTurnOn)
		{
			LedDriver_TurnOn(8);
			LedDriver_TurnOn(-1);
			LedDriver_TurnOn(0);
			LedDriver_TurnOn(17);
			LedDriver_TurnOn(3141);

			Assert::AreEqual(0x80, (int)virtual_led);
		}

		TEST_METHOD(OutOfBoundsChangesNothoingTurnOff)
		{
			LedDriver_TurnAllOn();
			LedDriver_TurnOff(-1);
			LedDriver_TurnOff(0);
			LedDriver_TurnOff(17);
			LedDriver_TurnOff(3141);

			Assert::AreEqual(0xffff, (int)virtual_led);
		}

		TEST_METHOD(IsOn)
		{
			Assert::IsFalse(LedDriver_IsOn(8), L"LEDがON状態");
			LedDriver_TurnOn(8);
			Assert::IsTrue(LedDriver_IsOn(8), L"LEDがOFF状態");
		}

		TEST_METHOD(OutOfBoundsIsOn)
		{
			Assert::IsFalse(LedDriver_IsOn(0), L"範囲外のアクセス");
			Assert::IsFalse(LedDriver_IsOn(-1), L"範囲外のアクセス");
			Assert::IsFalse(LedDriver_IsOn(-5), L"範囲外のアクセス");
			Assert::IsFalse(LedDriver_IsOn(17), L"範囲外のアクセス");
			Assert::IsFalse(LedDriver_IsOn(3141), L"範囲外のアクセス");
		}

		TEST_METHOD(IsOff)
		{
			Assert::IsTrue(LedDriver_IsOff(8), L"LEDがON状態");
			LedDriver_TurnOn(8);
			Assert::IsFalse(LedDriver_IsOff(8), L"LEDがOFF状態");
		}

		TEST_METHOD(OutOfBoundsIsOff)
		{
			LedDriver_TurnAllOn();
			Assert::IsTrue(LedDriver_IsOff(0), L"範囲外のアクセス");
			Assert::IsTrue(LedDriver_IsOff(-1), L"範囲外のアクセス");
			Assert::IsTrue(LedDriver_IsOff(-5), L"範囲外のアクセス");
			Assert::IsTrue(LedDriver_IsOff(17), L"範囲外のアクセス");
			Assert::IsTrue(LedDriver_IsOff(3141), L"範囲外のアクセス");
		}
	};
}
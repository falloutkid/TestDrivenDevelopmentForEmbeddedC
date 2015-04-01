#include "stdafx.h"
#include "CppUnitTest.h"

#include "FakeTimeService.h"
#include <TargetApplication\LightScheduler.h>
#include "memory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_FakeTimeService)
	{
	public:
		TEST_CLASS_INITIALIZE(Setup)
		{
			TimeService_Create();
		}

		TEST_CLASS_CLEANUP(Teardown)
		{
			TimeService_Destroy();
		}

		TEST_METHOD(Create)
		{
			Time time;
			TimeService_GetTime(&time);
			Assert::AreEqual((int)TIME_UNKNOWN, time.minuteOfDay);
			Assert::AreEqual((int)TIME_UNKNOWN, time.dayOfWeek);
		}

		TEST_METHOD(Set)
		{
			Time time;
			FakeTimeService_SetMinute(42);
			FakeTimeService_SetDay(SATURDAY);
			TimeService_GetTime(&time);
			Assert::AreEqual(42, time.minuteOfDay);
			Assert::AreEqual((int)SATURDAY, time.dayOfWeek);
		}
	};
}
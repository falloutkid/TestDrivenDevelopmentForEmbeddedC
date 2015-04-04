#include "stdafx.h"
#include "CppUnitTest.h"

#include <TargetApplication\LightScheduler.h>
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_LightSchedulerRandomize)
	{
	public:
		int(*saveRandomMinute_Get)();
		TEST_METHOD_INITIALIZE(setup)
		{
			LightController_Create();
			LightScheduler_Create();
			saveRandomMinute_Get = RandomMinute_Get;
			RandomMinute_Get = FakeRandomMinute_Get;
		}

		TEST_METHOD_CLEANUP(teardown)
		{
			LightScheduler_Destroy();
			LightController_Destroy();
			RandomMinute_Get = saveRandomMinute_Get;
		}

		void checkLightState(int id, int level)
		{
			if (id == LIGHT_ID_UNKNOWN)
			{
				Assert::AreEqual(id, LightControllerSpy_GetLastId());
				Assert::AreEqual(level, LightControllerSpy_GetLastState());
			}
			else
				Assert::AreEqual(level, LightControllerSpy_GetLightState(id));
		}

		void setTimeTo(int day, int minute)
		{
			FakeTimeService_SetDay(day);
			FakeTimeService_SetMinute(minute);
		}

		TEST_METHOD(TurnsOnEarly)
		{
			FakeRandomMinute_SetFirstAndIncrement(-10, 5);
			LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
			LightScheduler_Randomize(4, EVERYDAY, 600);
			setTimeTo(MONDAY, 600 - 10);
			LightScheduler_WakeUp();
			checkLightState(4, LIGHT_ON);
		}
	};
}
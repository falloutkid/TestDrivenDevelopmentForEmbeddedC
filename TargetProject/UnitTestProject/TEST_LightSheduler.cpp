#include "stdafx.h"
#include "CppUnitTest.h"

#include "LightControllerSpy.h"
#include <TargetApplication\LightScheduler.h>
#include "FakeTimeService.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_LightSheduler)
	{
	public:
		TEST_METHOD_INITIALIZE(setup)
		{
			LightController_Create();
			LightScheduler_Create();
		}

		TEST_METHOD_CLEANUP(teardown)
		{
			LightScheduler_Destroy();
			LightController_Destroy();
		}

		void checkLightState(int id, int state)
		{
			Assert::AreEqual(id, LightControllerSpy_GetLastId());
			Assert::AreEqual(state, LightControllerSpy_GetLastState());
		}

		void setTimeTo(int day, int minute)
		{
			FakeTimeService_SetDay(day);
			FakeTimeService_SetMinute(minute);
		}

		TEST_METHOD(NoChangeToLightsDuringInitialization)
		{
			checkLightState((int)LIGHT_ID_UNKNOWN, (int)LIGHT_STATE_UNKNOWN);
		}

		TEST_METHOD(NoScheduleNothingHappens)
		{
			setTimeTo(MONDAY, 100);
			LightScheduler_WakeUp();

			checkLightState((int)LIGHT_ID_UNKNOWN, (int)LIGHT_STATE_UNKNOWN);
		}

		TEST_METHOD(ScheduleOnEverydayNotTimeYet)
		{
			LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
			setTimeTo(MONDAY, 1199);
			LightScheduler_WakeUp();

			checkLightState((int)LIGHT_ID_UNKNOWN, (int)LIGHT_STATE_UNKNOWN);
		}

		TEST_METHOD(ScheduleOnEverydayItsTimeTurnOn)
		{
			LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
			setTimeTo(MONDAY, 1200);

			LightScheduler_WakeUp();

			checkLightState(3, (int)LIGHT_ON);
		}

		TEST_METHOD(ScheduleOnEverydayItsTimeTurnOff)
		{
			LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
			setTimeTo(MONDAY, 1200);

			LightScheduler_WakeUp();

			checkLightState(3, (int)LIGHT_OFF);
		}

		TEST_METHOD(ScheduleTuesdayButItsMonday)
		{
			LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
			setTimeTo(MONDAY, 1200);
			LightScheduler_WakeUp();
			checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
		}

		TEST_METHOD(ScheduleTuesdayAndItsTuesday)
		{
			LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
			setTimeTo(TUESDAY, 1200);
			LightScheduler_WakeUp();
			checkLightState(3, LIGHT_ON);
		}

		TEST_METHOD(ScheduleWeekEndItsSaturday)
		{
			LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
			setTimeTo(SATURDAY, 1200);
			LightScheduler_WakeUp();
			checkLightState(3, LIGHT_ON);
		}

		TEST_METHOD(ScheduleWeekEndItsSunday)
		{
			LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
			setTimeTo(SATURDAY, 1200);
			LightScheduler_WakeUp();
			checkLightState(3, LIGHT_ON);
		}
	};

	TEST_CLASS(TEST_LightSchedulerInitAndCleanup)
	{
	public:
		TEST_METHOD_INITIALIZE(setup)
		{
			LightController_Create();
			LightScheduler_Create();
		}

		TEST_METHOD_CLEANUP(teardown)
		{
			LightScheduler_Destroy();
			LightController_Destroy();
		}

		TEST_METHOD(CreateStartsOneMinuteAlarm)
		{
			LightScheduler_Create();
			Assert::AreEqual((void *)LightScheduler_WakeUp,	(void *)FakeTimeService_GetAlarmCallback());

			Assert::AreEqual(60, FakeTimeService_GetAlarmPeriod());
			LightScheduler_Destroy();
		}

		TEST_METHOD(DestroyCancelsOneMinuteAlarm)
		{
			LightScheduler_Create();
			LightScheduler_Destroy();
			
			Assert::AreEqual((void*)nullptr, (void *)FakeTimeService_GetAlarmCallback());
		}
	};
}
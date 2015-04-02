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
			if (id == LIGHT_ID_UNKNOWN)
			{
				Assert::AreEqual(id, LightControllerSpy_GetLastId());
				Assert::AreEqual(state, LightControllerSpy_GetLastState());
			}
			else {
				Assert::AreEqual(state, LightControllerSpy_GetLightState(id));
			}
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

		TEST_METHOD(ScheduleTwoEventsAtTheSameTime)
		{
			LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
			LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

			setTimeTo(SUNDAY, 1200);

			LightScheduler_WakeUp();

			checkLightState(3, LIGHT_ON);
			checkLightState(12, LIGHT_ON);
		}

		TEST_METHOD(RejectsTooManyEvents)
		{
			int i;
			for (i = 0; i < 128; i++)
				Assert::AreEqual((int)LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));

			Assert::AreEqual((int)LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));
		}

		TEST_METHOD(RemoveRecyclesScheduleSlot)
		{
			int i;
			for (i = 0; i < 128; i++)
				Assert::AreEqual((int)LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));

			LightScheduler_ScheduleRemove(6, MONDAY, 600);

			Assert::AreEqual((int)LS_OK, LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
		}

		TEST_METHOD(RemoveMultipleScheduledEvent)
		{
			LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
			LightScheduler_ScheduleTurnOn(7, MONDAY, 600);
			LightScheduler_ScheduleRemove(6, MONDAY, 600);

			setTimeTo(MONDAY, 600);

			LightScheduler_WakeUp();

			checkLightState(6, LIGHT_STATE_UNKNOWN);
			checkLightState(7, LIGHT_ON);
		}

		TEST_METHOD(AcceptsValidLightIds)
		{
			Assert::AreEqual((int)LS_OK, LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
			Assert::AreEqual((int)LS_OK, LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
			Assert::AreEqual((int)LS_OK, LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
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
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
		}

		TEST_METHOD_CLEANUP(teardown)
		{
			LightController_Create();
		}

		TEST_METHOD(NoChangeToLightsDuringInitialization)
		{
			Assert::AreEqual((int)LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
			Assert::AreEqual((int)LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
		}

		TEST_METHOD(NoScheduleNothingHappens)
		{
			FakeTimeService_SetDay(MONDAY);
			FakeTimeService_SetMinute(100);
			LightScheduler_WakeUp();
			Assert::AreEqual((int)LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
			Assert::AreEqual((int)LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
		}
#if 0
		

		TEST_METHOD(ScheduleOnEverydayNotTimeYet)
		{
			LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
			FakeTimeService_SetDay(MONDAY);
			FakeTimeService_SetMinute(1199);
			LightScheduler_WakeUp();

			Assert::AreEqual(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
			Assert::AreEqual(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
		}
#endif
	};
}
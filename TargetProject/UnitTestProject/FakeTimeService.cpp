#include "stdafx.h"
#include "FakeTimeService.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	static Time fake_time_;

	void TimeService_Create(void)
	{
		fake_time_.dayOfWeek = (int)TIME_UNKNOWN;
		fake_time_.minuteOfDay = (int)TIME_UNKNOWN;
	}

	void TimeService_Destroy(void)
	{
	}

	void TimeService_GetTime(Time * time)
	{
		time->minuteOfDay = fake_time_.minuteOfDay;
		time->dayOfWeek = fake_time_.dayOfWeek;
	}

	void FakeTimeService_SetMinute(int minute)
	{
		fake_time_.minuteOfDay = minute;
	}

	void FakeTimeService_SetDay(int day)
	{
		fake_time_.dayOfWeek = day;
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */
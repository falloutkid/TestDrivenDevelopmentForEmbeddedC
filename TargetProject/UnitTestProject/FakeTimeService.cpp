#include "stdafx.h"
#include "FakeTimeService.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	static Time fake_time_;
	static WakeUpCallback callback_;
	static int period_;

	void TimeService_Create(void)
	{
		fake_time_.dayOfWeek = (int)TIME_UNKNOWN;
		fake_time_.minuteOfDay = (int)TIME_UNKNOWN;
		callback_ = NULL;
		period_ = -1;
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

	void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
	{
		callback_ = cb;
		period_ = seconds;
	}

	void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
	{
		if (cb == callback_ && period_ == seconds)
		{
			callback_ = NULL;
			period_ = 0;
		}
	}

	WakeUpCallback FakeTimeService_GetAlarmCallback(void)
	{
		return callback_;
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */
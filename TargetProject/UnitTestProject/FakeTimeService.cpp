#include "stdafx.h"
#include "FakeTimeService.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	void TimeService_Create(void)
	{
	}

	void TimeService_Destroy(void)
	{
	}

	void TimeService_GetTime(Time * time)
	{
		time->minuteOfDay = (int)TIME_UNKNOWN;
		time->dayOfWeek = (int)TIME_UNKNOWN;
	}

	void FakeTimeService_SetMinute(int)
	{

	}

	void FakeTimeService_SetDay(int)
	{

	}
#ifdef __cplusplus
}
#endif /* __cplusplus */
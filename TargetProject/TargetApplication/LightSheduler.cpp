#include "stdafx.h"
#include "LightScheduler.h"
#include "LightController.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	enum
	{
		TURN_OFF,
		TURN_ON,	
	};

	const int UNUSED = -1;
	const int MAX_EVENTS = 128;

	typedef struct
	{
		int id;
		Day day;
		int minuteOfDay;
		int event;
	} ScheduledLightEvent;

	static ScheduledLightEvent scheduled_event_;

	void LightScheduler_Create(void)
	{
		scheduled_event_.id = UNUSED;
	}

	void LightScheduler_Destroy(void)
	{

	}

	void LightScheduler_WakeUp(void)
	{
		Time time;
		TimeService_GetTime(&time);

		if (scheduled_event_.id == UNUSED)
			return;
		if (time.minuteOfDay != scheduled_event_.minuteOfDay)
			return;

		if (scheduled_event_.event == (int)TURN_ON)
			LightController_On(scheduled_event_.id);
		else
			LightController_Off(scheduled_event_.id);
	}

	int LightScheduler_ScheduleTurnOn(int id, Day day, int minute)
	{
		scheduled_event_.id = id;
		scheduled_event_.day = day;
		scheduled_event_.minuteOfDay = minute;
		scheduled_event_.event = (int)TURN_ON;
		return 0;
	}

	int LightScheduler_ScheduleTurnOff(int id, Day day, int minute)
	{
		scheduled_event_.id = id;
		scheduled_event_.day = day;
		scheduled_event_.minuteOfDay = minute;
		scheduled_event_.event = (int)TURN_OFF;
		return 0;
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */
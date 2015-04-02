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

	void operateLightController(ScheduledLightEvent* light_event)
	{
		if (light_event->event == (int)TURN_ON)
			LightController_On(scheduled_event_.id);
		else
			LightController_Off(scheduled_event_.id);
	}

	bool isLightRespondToday(Time* time, ScheduledLightEvent* light_event)
	{
		if (light_event->day == EVERYDAY)
			return true;

		if (time->dayOfWeek == light_event->day)
			return true;

		bool is_weekend = (time->dayOfWeek == SATURDAY) || (time->dayOfWeek == SUNDAY);
		if ((light_event->day == WEEKEND) && is_weekend)
			return true;

		if ((light_event->day == WEEKDAY) && !is_weekend)
			return true;

		return false;
	}

	void processLightController(Time* time, ScheduledLightEvent* light_event)
	{
		if (light_event->id == UNUSED)
			return;
		if (time->minuteOfDay != light_event->minuteOfDay)
			return;
		if (!isLightRespondToday(time, light_event))
			return;

		operateLightController(light_event);
	}

	void LightScheduler_WakeUp(void)
	{
		Time time;
		TimeService_GetTime(&time);

		processLightController(&time, &scheduled_event_);
	}

	int scheduleEvent(int id, Day day, int minute, int event)
	{
		scheduled_event_.id = id;
		scheduled_event_.day = day;
		scheduled_event_.minuteOfDay = minute;
		scheduled_event_.event = event;
		return 0;
	}

	int LightScheduler_ScheduleTurnOn(int id, Day day, int minute)
	{
		return scheduleEvent(id, day, minute, (int)TURN_ON);
	}

	int LightScheduler_ScheduleTurnOff(int id, Day day, int minute)
	{
		return scheduleEvent(id, day, minute, (int)TURN_OFF);
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */
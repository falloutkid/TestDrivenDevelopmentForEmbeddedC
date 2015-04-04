#include "stdafx.h"
#include "LightScheduler.h"
#include "LightController.h"
#include "RandomMinute.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	enum
	{
		TURN_OFF,
		TURN_ON,
		RANDOM_ON,
		RANDOM_OFF
	};

	const int UNUSED = -1;
	const int MAX_EVENTS = 128;

	typedef struct
	{
		int id;
		Day day;
		int minuteOfDay;
		int event;
		int randomize;
		int randomMinutes;
	} ScheduledLightEvent;

	static ScheduledLightEvent scheduled_events_[MAX_EVENTS];

	void LightScheduler_Create(void)
	{
		for (int i = 0; i < MAX_EVENTS;i++)
			scheduled_events_[i].id = UNUSED;

		TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
	}

	void LightScheduler_Destroy(void)
	{
		TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
	}

	void operateLightController(ScheduledLightEvent* light_event)
	{
		if (light_event->event == (int)TURN_ON)
			LightController_On(light_event->id);
		else
			LightController_Off(light_event->id);
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
		int i;
		Time time;
		int td;
		int min;

		TimeService_GetTime(&time);
		td = time.dayOfWeek;
		min = time.minuteOfDay;

		for (i = 0; i < MAX_EVENTS; i++)
		{
			ScheduledLightEvent * se = &scheduled_events_[i];
			if (se->id != UNUSED)
			{
				Day d = se->day;
				if ((d == EVERYDAY) || (d == td) || (d == WEEKEND &&
					(SATURDAY == td || SUNDAY == td)) ||
					(d == WEEKDAY && (td >= MONDAY
					&& td <= FRIDAY)))
				{
					/* it's the right day */
					if (min == se->minuteOfDay + se->randomMinutes)
					{
						if (TURN_ON == se->event)
							LightController_On(se->id);
						else if (TURN_OFF == se->event)
							LightController_Off(se->id);

						if (se->randomize == RANDOM_ON)
							se->randomMinutes = RandomMinute_Get();
						else
							se->randomMinutes = 0;

					}
				}
			}
		}
	}

	int scheduleEvent(int id, Day day, int minute, int event)
	{

		for (int i = 0; i < MAX_EVENTS; i++)
		{
			if (scheduled_events_[i].id == UNUSED)
			{
				scheduled_events_[i].id = id;
				scheduled_events_[i].day = day;
				scheduled_events_[i].minuteOfDay = minute;
				scheduled_events_[i].event = event;
				return LS_OK;
			}
		}
		return LS_TOO_MANY_EVENTS;
	}

	int LightScheduler_ScheduleTurnOn(int id, Day day, int minute)
	{
		return scheduleEvent(id, day, minute, (int)TURN_ON);
	}

	int LightScheduler_ScheduleTurnOff(int id, Day day, int minute)
	{
		return scheduleEvent(id, day, minute, (int)TURN_OFF);
	}

	void LightScheduler_Randomize(int id, Day day, int minuteOfDay)
	{
		int i;
		for (i = 0; i < MAX_EVENTS; i++)
		{
			ScheduledLightEvent * scheduled_event = &scheduled_events_[i];
			if (scheduled_event->id == id && scheduled_event->day == day && scheduled_event->minuteOfDay == minuteOfDay)
			{
				scheduled_event->randomize = RANDOM_ON;
				scheduled_event->randomMinutes = RandomMinute_Get();
			}
		}
	}


	void LightScheduler_ScheduleRemove(int id, Day day, int minute)
	{
		int i;

		for (i = 0; i < MAX_EVENTS; i++)
		{
			if (scheduled_events_[i].id == id
				&& scheduled_events_[i].day == day
				&& scheduled_events_[i].minuteOfDay == minute)
			{
				scheduled_events_[i].id = UNUSED;
			}
		}
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */
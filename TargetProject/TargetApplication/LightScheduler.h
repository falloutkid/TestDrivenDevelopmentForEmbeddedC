#ifndef D_LightScheduler_H
#define D_LightScheduler_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "TimeService.h"

	typedef enum  {
		NONE = -1, EVERYDAY = 10, WEEKDAY, WEEKEND,
		SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
	} Day;

	enum { LS_OK, LS_TOO_MANY_EVENTS, LS_ID_OUT_OF_BOUNDS };

	void LightScheduler_Create(void);
	void LightScheduler_Destroy(void);
	int LightScheduler_ScheduleTurnOn(int id, Day day, int minute);
	int LightScheduler_ScheduleTurnOff(int id, Day day, int minute);
	void LightScheduler_Randomize(int id, Day day, int minuteOfDay);
	void LightScheduler_ScheduleRemove(int id, Day day, int minute);
	void LightScheduler_WakeUp(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_LightScheduler_H */
#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\TimeService.h>
	enum { TIME_UNKNOWN = -1 };

	void FakeTimeService_SetMinute(int);
	void FakeTimeService_SetDay(int);
	WakeUpCallback FakeTimeService_GetAlarmCallback(void);
	int FakeTimeService_GetAlarmPeriod(void);
	void FakeTimeService_MinuteIsUp(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_FakeTimeService_H */
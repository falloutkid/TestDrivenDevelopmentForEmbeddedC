#ifndef D_LightControllerSpy_H
#define D_LightControllerSpy_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\LightController.h>

	enum
	{
		LIGHT_ID_UNKNOWN = -1, LIGHT_STATE_UNKNOWN = -1,
		LIGHT_OFF = 0, LIGHT_ON = 1
	};

	int LightControllerSpy_GetLightState(int id);
	int LightControllerSpy_GetLastId(void);
	int LightControllerSpy_GetLastState(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_LightControllerSpy_H */

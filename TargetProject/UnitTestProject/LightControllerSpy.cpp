#include "stdafx.h"
#include "LightControllerSpy.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\LightController.h>
	int LightControllerSpy_GetLightState(int id)
	{
		return 0;
	}

	int LightControllerSpy_GetLastId()
	{
		return 0;
	}

	int LightControllerSpy_GetLastState()
	{
		return 0;
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */

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
		return LIGHT_ID_UNKNOWN;
	}

	int LightControllerSpy_GetLastState()
	{
		return LIGHT_STATE_UNKNOWN;
	}

	/// LightController‚ÌƒXƒ^ƒu
	void LightController_Create(void)
	{

	}
	void LightController_Destroy(void)
	{

	}
#ifdef __cplusplus
}
#endif /* __cplusplus */

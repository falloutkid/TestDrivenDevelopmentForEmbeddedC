#include "stdafx.h"
#include "LightControllerSpy.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\LightController.h>

	static int last_id_;
	static int last_state_;
	int LightControllerSpy_GetLightState(int id)
	{
		return 0;
	}

	int LightControllerSpy_GetLastId()
	{
		return last_id_;
	}

	int LightControllerSpy_GetLastState()
	{
		return last_state_;
	}

	/// LightController‚ÌƒXƒ^ƒu
	void LightController_Create(void)
	{
		last_id_ = (int)LIGHT_ID_UNKNOWN;
		last_state_ = (int)LIGHT_STATE_UNKNOWN;
	}
	void LightController_Destroy(void)
	{

	}

	void LightController_On(int id)
	{
		last_id_ = id;
		last_state_ = LIGHT_ON;
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */

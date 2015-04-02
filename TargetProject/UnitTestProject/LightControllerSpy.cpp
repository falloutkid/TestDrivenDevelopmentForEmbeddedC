#include "stdafx.h"
#include "LightControllerSpy.h"
#include "memory.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\LightController.h>

	static int last_id_;
	static int last_state_;
	static int lights[MAX_LIGHTS];
	int LightControllerSpy_GetLightState(int id)
	{
		return lights[id];
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

		memset(lights, (int)LIGHT_OFF, sizeof(lights));
	}
	void LightController_Destroy(void)
	{

	}

	void LightController_On(int id)
	{
		last_id_ = id;
		last_state_ = LIGHT_ON;

		lights[id] = LIGHT_ON;
	}

	void LightController_Off(int id)
	{
		last_id_ = id;
		last_state_ = LIGHT_OFF;

		lights[id] = LIGHT_OFF;
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */

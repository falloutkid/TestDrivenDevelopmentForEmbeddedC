#ifndef D_LightController_H
#define D_LightController_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	enum { MAX_LIGHTS = 32 };

	void LightController_Create(void);
	void LightController_Destroy(void);
	void LightController_On(int id);
	void LightController_Off(int id);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_LightController_H */

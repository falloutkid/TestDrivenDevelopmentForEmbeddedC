#ifndef D_LedDriver_H
#define D_LedDriver_H
#include <stdint.h>

#define TRUE 1
#define FALSE 0
typedef int BOOL;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	void LedDriver_Create(uint16_t *ledsAddress);
	void LedDriver_Destroy(void);

	void LedDriver_TurnOn(int ledNumber);
	void LedDriver_TurnOff(int ledNumber);
	void LedDriver_TurnAllOn(void);
	void LedDriver_TurnAllOff(void);
	BOOL LedDriver_IsOn(int ledNumber);
	BOOL LedDriver_IsOff(int ledNumber);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_LedDriver_H */

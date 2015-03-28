#ifndef D_LedDriver_H
#define D_LedDriver_H
#include <stdint.h>

#define TRUE 1
#define FALSE 0
typedef int BOOL;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	void LedDriver_Create(uint16_t *leds_address);
	void LedDriver_Destroy(void);

	void LedDriver_TurnOn(int led_number);
	void LedDriver_TurnOff(int led_number);
	void LedDriver_TurnAllOn(void);
	void LedDriver_TurnAllOff(void);
	BOOL LedDriver_IsOn(int led_number);
	BOOL LedDriver_IsOff(int led_number);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_LedDriver_H */

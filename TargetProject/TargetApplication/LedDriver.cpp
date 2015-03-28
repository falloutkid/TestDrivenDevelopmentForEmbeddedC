#include "stdafx.h"
#include "LedDriver.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	enum { ALL_LEDS_OFF = 0, ALL_LEDS_ON = ~0 };

	static uint16_t *ledsAddress;
	static uint16_t ledsImage;

	void LedDriver_Create(uint16_t *leds_address)
	{		
		ledsAddress = leds_address;
		*ledsAddress = 0;
	}

	void LedDriver_Destroy(void)
	{
	}

	enum { FIRST_LED = 1, LAST_LED = 16 };

	static BOOL IsLedOutOfBounds(int led_number)
	{
		return FALSE;
	}

	static uint16_t convertLedNumberToBit(int led_number)
	{
		return 0;
	}

	static void updateHardware(void)
	{
		*ledsAddress = 0;
	}

	static void setLedImageBit(int led_number)
	{
		ledsImage = 0;
	}
	void LedDriver_TurnOn(int led_number)
	{
		*ledsAddress |= (1 << (led_number -1 ));
	}

	static void clearLedImageBit(int led_number)
	{
	}

	void LedDriver_TurnOff(int led_number)
	{
		*ledsAddress ^= (1 << (led_number - 1));
	}

	void LedDriver_TurnAllOn(void)
	{
		*ledsAddress = ALL_LEDS_ON;
	}

	void LedDriver_TurnAllOff(void)
	{
	}

	BOOL LedDriver_IsOn(int led_number)
	{
		return FALSE;
	}

	BOOL LedDriver_IsOff(int led_number)
	{
		return FALSE;
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */

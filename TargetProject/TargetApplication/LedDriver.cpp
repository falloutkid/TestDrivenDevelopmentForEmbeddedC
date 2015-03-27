#include "stdafx.h"
#include "LedDriver.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	enum { ALL_LEDS_OFF = 0, ALL_LEDS_ON = ~0 };

	static uint16_t *ledsAddress;
	static uint16_t ledsImage;

	void LedDriver_Create(uint16_t *address)
	{		
		ledsAddress = address;
		*ledsAddress = 0;
	}

	void LedDriver_Destroy(void)
	{
	}

	enum { FIRST_LED = 1, LAST_LED = 16 };

	static BOOL IsLedOutOfBounds(int ledNumber)
	{
		return FALSE;
	}

	static uint16_t convertLedNumberToBit(int ledNumber)
	{
		return 0;
	}

	static void updateHardware(void)
	{
		*ledsAddress = 0;
	}

	static void setLedImageBit(int ledNumber)
	{
		ledsImage = 0;
	}
	void LedDriver_TurnOn(int ledNumber)
	{
		*ledsAddress = 1;
	}

	static void clearLedImageBit(int ledNumber)
	{
	}
	void LedDriver_TurnOff(int ledNumber)
	{
	}

	void LedDriver_TurnAllOn(void)
	{
	}

	void LedDriver_TurnAllOff(void)
	{
	}

	BOOL LedDriver_IsOn(int ledNumber)
	{
		return FALSE;
	}

	BOOL LedDriver_IsOff(int ledNumber)
	{
		return FALSE;
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */

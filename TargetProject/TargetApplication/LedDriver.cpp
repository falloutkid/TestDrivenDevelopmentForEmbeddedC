#include "stdafx.h"
#include "LedDriver.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	enum { ALL_LEDS_OFF = 0, ALL_LEDS_ON = ~0 };
	enum { FIRST_LED = 1, LAST_LED = 16};

	static uint16_t *ledsAddress;
	static uint16_t ledsImage;

	void LedDriver_Create(uint16_t *leds_address)
	{		
		ledsAddress = leds_address;
		LedDriver_TurnAllOff();
	}

	void LedDriver_Destroy(void)
	{
	}

	static BOOL IsLedOutOfBounds(int led_number)
	{
		return (led_number < FIRST_LED) || (led_number > LAST_LED);
	}

	static uint16_t convertLedNumberToBit(int led_number)
	{
		return (1 << (led_number - 1));
	}

	static void updateHardware(void)
	{
		*ledsAddress = ledsImage;
	}

	static void setLedImageBit(int led_number)
	{
		ledsImage |= convertLedNumberToBit(led_number);
	}
	void LedDriver_TurnOn(int led_number)
	{
		if (IsLedOutOfBounds(led_number))
		{
			return;
		}
		setLedImageBit(led_number);
		updateHardware();
	}

	static void clearLedImageBit(int led_number)
	{
		ledsImage ^= convertLedNumberToBit(led_number);
	}

	void LedDriver_TurnOff(int led_number)
	{
		if (IsLedOutOfBounds(led_number))
		{
			return;
		}
		clearLedImageBit(led_number);
		updateHardware();
	}

	void LedDriver_TurnAllOn(void)
	{
		ledsImage = ALL_LEDS_ON;
		updateHardware();
	}

	void LedDriver_TurnAllOff(void)
	{
		ledsImage = ALL_LEDS_OFF;
		updateHardware();
	}

	BOOL LedDriver_IsOn(int led_number)
	{
		if ((ledsImage && convertLedNumberToBit(led_number) != 0))
			return TRUE;
		return FALSE;
	}

	BOOL LedDriver_IsOff(int led_number)
	{
		if ((ledsImage && convertLedNumberToBit(led_number) != 0))
			return FALSE;
		return TRUE;
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */

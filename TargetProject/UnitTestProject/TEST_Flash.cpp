#include "stdafx.h"
#include "CppUnitTest.h"
#include <TargetApplication\Flash.h>
#include <TargetApplication\m28w160ect.h>
#include "MOCK_IO.h"
#include "FakeMicroTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	ioAddress address;
	ioData data;
	int result;
	TEST_CLASS(TEST_Flash)
	{
	public:
		
		TEST_METHOD_INITIALIZE(setup)
		{
			address = 0x1000;
			data = 0xBEEF;
			result = -1;

			MockIO_Create(20);
			Flash_Create();
		}

		TEST_METHOD_CLEANUP(teardown)
		{
			Flash_Destroy();
			MockIO_Verify_Complete();
			MockIO_Destroy();
		}

		TEST_METHOD(WriteSucceeds_ReadyImmediately)
		{
			MockIO_Expect_Write(CommandRegister, ProgramCommand);
			MockIO_Expect_Write(address, data);
			MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
			MockIO_Expect_ReadThenReturn(address, data);
			result = Flash_Write(address, data);
			Assert::AreEqual((int)FLASH_SUCCESS, result);
		}

		TEST_METHOD(WriteSucceeds_NotImmediatelyReady)
		{
			MockIO_Expect_Write(CommandRegister, ProgramCommand);
			MockIO_Expect_Write(address, data);
			MockIO_Expect_ReadThenReturn(StatusRegister, 0);
			MockIO_Expect_ReadThenReturn(StatusRegister, 0);
			MockIO_Expect_ReadThenReturn(StatusRegister, 0);
			MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
			MockIO_Expect_ReadThenReturn(address, data);

			result = Flash_Write(address, data);
			Assert::AreEqual((int)FLASH_SUCCESS, result);
		}

		TEST_METHOD(WriteFails_VppError)
		{
			MockIO_Expect_Write(CommandRegister, ProgramCommand);
			MockIO_Expect_Write(address, data);
			MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | VppErrorBit);
			MockIO_Expect_Write(CommandRegister, Reset);

			result = Flash_Write(address, data);

			Assert::AreEqual((int)FLASH_VPP_ERROR, result);
		}

		TEST_METHOD(WriteFails_FlashReadBackError)
		{
			MockIO_Expect_Write(CommandRegister, ProgramCommand);
			MockIO_Expect_Write(address, data);
			MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
			MockIO_Expect_ReadThenReturn(address, data - 1);

			result = Flash_Write(address, data);

			Assert::AreEqual((int)FLASH_READ_BACK_ERROR, result);
		}

		TEST_METHOD(WriteSucceeds_IgnoresOtherBitsUntilReady)
		{
			MockIO_Expect_Write(CommandRegister, ProgramCommand);
			MockIO_Expect_Write(address, data);
			MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
			MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
			MockIO_Expect_ReadThenReturn(address, data);

			result = Flash_Write(address, data);

			Assert::AreEqual((int)FLASH_SUCCESS, result);
		}

		TEST_METHOD(WriteFails_Timeout)
		{
			FakeMicroTime_Init(0, 500);
			Flash_Create();
			MockIO_Expect_Write(CommandRegister, ProgramCommand);
			MockIO_Expect_Write(address, data);
			for (int i = 0; i < 10; i++)
				MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
			result = Flash_Write(address, data);
			Assert::AreEqual((int)FLASH_TIMEOUT_ERROR, result);
		}

		TEST_METHOD(WriteFails_TimeoutAtEndOfTime)
		{
			FakeMicroTime_Init(0xffffffff, 500);
			Flash_Create();
			MockIO_Expect_Write(CommandRegister, ProgramCommand);
			MockIO_Expect_Write(address, data);
			for (int i = 0; i < 10; i++)
				MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
			result = Flash_Write(address, data);
			Assert::AreEqual((int)FLASH_TIMEOUT_ERROR, result);
		}
	};
}
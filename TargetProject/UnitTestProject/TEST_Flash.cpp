#include "stdafx.h"
#include "CppUnitTest.h"
#include <TargetApplication\Flash.h>
#include <TargetApplication\IO.h>
#include "MOCK_IO.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{

	TEST_CLASS(TEST_Flash)
	{
	public:
		
		TEST_METHOD_INITIALIZE(setup)
		{
			MockIO_Create(20);
			Flash_Create();
		}

		TEST_METHOD_CLEANUP(teardown)
		{
			MockIO_Destroy();
		}

		TEST_METHOD(WriteSucceeds_ReadyImmediately)
		{
			MockIO_Expect_Write(0, 0x40);
			MockIO_Expect_Write(0x1000, 0x8EEF);
			MockIO_Expect_ReadThenReturn(0, 1<<7);
			MockIO_Expect_ReadThenReturn(0x1000, 0x8EEF);
			int result = Flash_Write(0x1000, 0x8EEF);
			Assert::AreEqual((int)FLASH_SUCCESS, result);
			MockIO_Verify_Complete();
		}
	};
}
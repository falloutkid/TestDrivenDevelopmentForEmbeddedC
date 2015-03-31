#include "stdafx.h"
#include "CppUnitTest.h"

#include "LightControllerSpy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_LightControllerSpy)
	{
	public:
		TEST_CLASS_INITIALIZE(Setup)
		{
			LightController_Create();
		}

		TEST_CLASS_CLEANUP(Teardown)
		{
			LightController_Destroy();
		}


		TEST_METHOD(Create)
		{
			Assert::AreEqual((int)LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
			Assert::AreEqual((int)LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
		}

		TEST_METHOD(RememberTheLastLightIdControlled)
		{
			LightController_On(10);
			Assert::AreEqual(10, LightControllerSpy_GetLastId());
			Assert::AreEqual((int)LIGHT_ON, LightControllerSpy_GetLastState());
		}
	};
}
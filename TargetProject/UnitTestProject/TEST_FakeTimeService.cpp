#include "stdafx.h"
#include "CppUnitTest.h"

#include "FakeTimeService.h"
#include <TargetApplication\LightScheduler.h>
#include "memory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_FakeTimeService)
	{
	public:
		TEST_CLASS_INITIALIZE(Setup)
		{
			TimeService_Create();
		}

		TEST_CLASS_CLEANUP(Teardown)
		{
			TimeService_Destroy();
		}

		TEST_METHOD(TestMethod1)
		{
			// TODO: テスト コードをここに挿入します
		}

	};
}
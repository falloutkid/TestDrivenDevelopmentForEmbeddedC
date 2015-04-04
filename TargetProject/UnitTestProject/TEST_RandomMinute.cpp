#include "stdafx.h"
#include "CppUnitTest.h"


#include "string.h"
#include <TargetApplication\RandomMinute.h>
#include <stdio.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static int minute;

namespace UnitTestProject
{
	TEST_CLASS(TEST_RandomMinute)
	{
	private:
		static const int BOUND = 30;
		
	public:
		
		TEST_CLASS_INITIALIZE(setup)
		{
			RandomMinute_Create(BOUND);
			minute = 0;
			srand(1);
		}
		void AssertMinuteIsInRange()
		{
			if (minute < -BOUND || minute > BOUND)
			{
				printf("bad minute value: %d\n", minute);
				Assert::Fail(L"Minute out of range");
			}
		}

		TEST_METHOD(GetIsInRange)
		{
			for (int i = 0; i < 100; i++)
			{
				minute = RandomMinute_Get();
#if 0
				char write_data[256];
				sprintf(write_data, "Nomber[%d]::minute[%d]\n", i, minute);
				Logger::WriteMessage(write_data);
#endif
				AssertMinuteIsInRange();
			}
		}

		TEST_METHOD(AllValuesPossible)
		{
			int hit[2 * BOUND + 1];
			memset(hit, 0, sizeof(hit));
			int i;
			for (i = 0; i < 300; i++)
			{
				minute = RandomMinute_Get();
				AssertMinuteIsInRange();
				hit[minute + BOUND]++;
			}
			for (i = 0; i < 2 * BOUND + 1; i++) {
				Assert::IsTrue(hit[i] > 0);
			}
		}
	};
}

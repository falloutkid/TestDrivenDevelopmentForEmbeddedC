#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TEST_LedDeiver)
	{
	public:
		TEST_CLASS_INITIALIZE(LedDriverInitialize){}

		TEST_CLASS_CLEANUP(LedDriverCleanup){}

		TEST_METHOD(LedOffAfterCreate)
		{
			Assert::Fail(L"Start here");
		}
	};
}
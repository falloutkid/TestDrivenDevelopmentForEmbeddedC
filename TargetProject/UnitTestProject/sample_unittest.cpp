#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <TargetApplication\SampleSource.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{	
	/*
	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize\n");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup\n");
	}
	*/

	TEST_CLASS(SampleUnitTest)
	{
	public:
		double(*sample_function)(double, double);

		SampleUnitTest()
		{
			Logger::WriteMessage("In Class1\n");
		}

		~SampleUnitTest()
		{
			Logger::WriteMessage("In ~Class1\n");
		}

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize\n");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup\n");
		}

		TEST_METHOD_INITIALIZE(MethodInitialize)
		{
			Logger::WriteMessage("In Method Initialize\n");
		}

		TEST_METHOD_CLEANUP(MethodCleanup)
		{
			Logger::WriteMessage("In Method Cleanup\n");
		}

		TEST_METHOD(TestMethodSample1)
		{
			Logger::WriteMessage("In TestMethodSample1 Execute\n");
			SampleClass* sample = new SampleClass();
			std::string expect = "Hello, World!";
			Assert::AreEqual(sample->echo(), expect);
		}
		
		TEST_METHOD(TestMethodSample2)
		{
			Logger::WriteMessage("In TestMethodSample2 Execute\n");
			Assert::IsTrue(true);
		}

		TEST_METHOD(FunctionPointerAdd)
		{		
			sample_function = Add;
			Assert::AreEqual(5.0, sample_function(1, 4));
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(TestMethodSample2)
			TEST_IGNORE()
			END_TEST_METHOD_ATTRIBUTE()
	};
}
#include "stdafx.h"
#include "RuntimeError.h"
#include "CppUnitTest.h"
#include "stdio.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	void RuntimeError(const char * message, int parameter, const char * file, int line)
	{
		char write_message[256];
		sprintf_s(write_message, 256, "%s:%d:FAIL\nMessage[%s]:Parameter[%d]\n", file, line, message, parameter);
		Logger::WriteMessage(write_message);
	}
#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifndef D_MockIO_H
#define D_MockIO_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\IO.h>
	void MockIO_Create(int maxExpectations);
	void MockIO_Destroy(void);
	void MockIO_Expect_Write(ioAddress offset, ioData data);
	void MockIO_Expect_ReadThenReturn(ioAddress  offset, ioData returnData);
	void MockIO_Verify_Complete(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

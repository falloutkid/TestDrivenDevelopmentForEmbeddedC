#ifndef D_FormatOutputSpy_H
#define D_FormatOutputSpy_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\Utils.h>

	int FormatOutputSpy(const char * format, ...);
	void FormatOutputSpy_Create(int size);
	void FormatOutputSpy_Destroy(void);
	const char * FormatOutputSpy_GetOutput(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_FormatOutput_H */

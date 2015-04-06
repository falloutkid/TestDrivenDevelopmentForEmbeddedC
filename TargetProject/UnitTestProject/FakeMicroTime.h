#ifndef D_FakeMicroTime_H
#define D_FakeMicroTime_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\MicroTime.h>

	void FakeMicroTime_Init(uint32_t start, uint32_t increment);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_FakeMicroTime_H */

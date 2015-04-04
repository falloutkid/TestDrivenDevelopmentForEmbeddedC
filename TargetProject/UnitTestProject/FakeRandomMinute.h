#ifndef D_FakeRandomMinute_H
#define D_FakeRandomMinute_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <TargetApplication\RandomMinute.h>

	void FakeRandomMinute_SetFirstAndIncrement(int seed, int increment);
	int FakeRandomMinute_Get(void);
	void FakeRandomMinute_Reset(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_RandomMinute_H */

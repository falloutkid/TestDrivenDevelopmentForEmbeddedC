#ifndef D_MicroTime_H
#define D_MicroTime_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <stdint.h>

	uint32_t MicroTime_Get(void);
	void MicroTime_Delay(uint32_t);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_MicroTime_H */

#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	typedef struct CircularBufferStruct * CircularBuffer;

	CircularBuffer CircularBuffer_Create(int capacity);
	void CircularBuffer_Destroy(CircularBuffer);
	int CircularBuffer_IsEmpty(CircularBuffer);
	int CircularBuffer_IsFull(CircularBuffer);
	int CircularBuffer_Put(CircularBuffer, int);
	int CircularBuffer_Get(CircularBuffer);
	int CircularBuffer_Capacity(CircularBuffer);
	void CircularBuffer_Print(CircularBuffer);
	int CircularBuffer_VerifyIntegrity(CircularBuffer);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* D_CircularBuffer_H */

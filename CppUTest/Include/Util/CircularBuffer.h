#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct CircularBuffer_t;
typedef struct CircularBuffer_t *CircularBuffer;

CircularBuffer CircularBuffer_create(int size);
void CircularBuffer_destroy(CircularBuffer buffer);
void CircularBuffer_print(CircularBuffer buffer);
void CircularBuffer_put(CircularBuffer buffer, int value);
int CircularBuffer_get(CircularBuffer buffer);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CIRCULAR_BUFFER_H_ */

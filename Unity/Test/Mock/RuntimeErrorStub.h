#ifndef RUNTIME_ERROR_STUB_H_
#define RUNTIME_ERROR_STUB_H_

#ifdef __cplusplus
extern "C" {
#endif

void RuntimeErrorStub_reset(void);
const char * RuntimeErrorStub_getLastError(void);
int RuntimeErrorStub_GetLastParameter(void);

#ifdef __cplusplus
}
#endif

#endif  /* RUNTIME_ERROR_STUB_H_ */

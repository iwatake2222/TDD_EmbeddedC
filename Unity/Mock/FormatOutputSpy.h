#ifndef FORMAT_OUTPUT_SPY_H_
#define FORMAT_OUTPUT_SPY_H_

#include <Util/Utils.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void formatOutputSpy_create(int size);
void formatOutputSpy_destroy();
int formatOutputSpy(const char* format, ...);
char* formatOutputSpy_getOutput();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FORMAT_OUTPUT_SPY_H_ */

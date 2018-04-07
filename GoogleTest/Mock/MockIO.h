#ifndef MOCK_IO_H_
#define MOCK_IO_H_

#include <IO/IO.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void MockIO_create(int maxExpectations);
void MockIO_destroy();
void MockIO_expect_write(ioAddress address, ioData data);
void MockIO_expect_readThenReturn(ioAddress address, ioData data);
void MockIO_verify_complete();
void MockIO_write(ioAddress address, ioData data);
ioData MockIO_read(ioAddress address);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MOCK_IO_H_ */

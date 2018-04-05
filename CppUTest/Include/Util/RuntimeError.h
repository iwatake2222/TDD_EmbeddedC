#ifndef RUNTIME_ERROR_H_
#define RUNTIME_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

void RuntimeError(const char * message, int parameter, const char * file, int line);

#ifdef __cplusplus
}
#endif

#define RUNTIME_ERROR(description, parameter)\
	RuntimeError(description, parameter, __FILE__, __LINE__)

#endif  /* RUNTIME_ERROR_H_ */

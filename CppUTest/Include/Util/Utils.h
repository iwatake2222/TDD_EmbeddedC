#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// int formatOutput(const char* format, ...);
extern int (*formatOutput)(const char* format, ...);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UTILS_H_ */

#ifndef RANDOM_MINUTE_H_
#define RANDOM_MINUTE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void RandomMinute_create(int bound);
void RandomMinute_destroy();
extern int (*RandomMinute_get)();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RANDOM_MINUTE_H_ */

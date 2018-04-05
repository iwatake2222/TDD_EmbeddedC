#ifndef LIGHT_CONTROLLER_H_
#define LIGHT_CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int LightController_create();
int LightController_destroy();
void LightController_on(int id);
void LightController_off(int id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIGHT_CONTROLLER_H_ */

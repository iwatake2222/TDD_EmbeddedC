#ifndef LIGHT_CONTROLLER_SPY_H_
#define LIGHT_CONTROLLER_SPY_H_

#include <HomeAutomation/LightController.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum {
	LIGHT_ID_UNKNOWN = -1,
};

enum {
	LIGHT_STATE_UNKNOWN = -1,
	LIGHT_STATE_OFF = 0,
	LIGHT_STATE_ON = 1,
};

int LightControllerSpy_getLastId();
int LightControllerSpy_getLastState();
int LightControllerSpy_getLightState(int id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIGHT_CONTROLLER_SPY_H_ */

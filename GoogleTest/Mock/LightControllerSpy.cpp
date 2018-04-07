#include "LightControllerSpy.h"

/*****************************************
 * Data containers and accessors
 *****************************************/
static int s_lastId;
static int s_lastState;

#define MAX_ID_NUM 32
static int s_state[MAX_ID_NUM];


int LightControllerSpy_getLastId()
{
	return s_lastId;
}

int LightControllerSpy_getLastState()
{
	return s_lastState;
}

int LightControllerSpy_getLightState(int id)
{
	if (id == LIGHT_ID_UNKNOWN) return LIGHT_STATE_UNKNOWN;
	return s_state[id];
}

/*****************************************
 * Mock functions
 *****************************************/
int LightController_create()
{
	s_lastId = LIGHT_ID_UNKNOWN;
	s_lastState = LIGHT_STATE_UNKNOWN;
	for (int i = 0; i < MAX_ID_NUM; i++) s_state[i] = LIGHT_STATE_UNKNOWN;
}

int LightController_destroy()
{
}	

void LightController_on(int id)
{
	s_lastId = id;
	s_lastState = LIGHT_STATE_ON;
	s_state[id] = LIGHT_STATE_ON;
}

void LightController_off(int id)
{
	s_lastId = id;
	s_lastState = LIGHT_STATE_OFF;
	s_state[id] = LIGHT_STATE_OFF;
}

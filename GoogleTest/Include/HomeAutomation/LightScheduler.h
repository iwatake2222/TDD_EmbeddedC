#ifndef LIGHT_SCHEDULER_H_
#define LIGHT_SCHEDULER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




enum {
	LS_OK,
	LS_ITEM_NOT_FOUND,
	LS_ID_OUT_OF_BOUNDS,
	LS_TOO_MANY_EVENTS,
};

void LightScheduler_create();
void LightScheduler_destroy();
int LightScheduler_scheduleTurnOn(int id, DAY day, int minuteOfDay);
int LightScheduler_scheduleTurnOff(int id, DAY day, int minuteOfDay);
int LightScheduler_scheduleRemove(int id, DAY day, int minuteOfDay);
void LightScheduler_wakeup();
int LightScheduler_randomize(int id, DAY day, int minuteOfDay);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIGHT_SCHEDULER_H_ */

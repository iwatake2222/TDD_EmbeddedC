#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

void LedDriver_create(uint16_t* address);
void LedDriver_destroy();
void LedDriver_turnOn(int ledNumber);
void LedDriver_turnOff(int ledNumber);
void LedDriver_turnAllOn();
void LedDriver_turnAllOff();
int  LedDriver_isOn(int ledNumber);
int  LedDriver_isOff(int ledNumber);

#ifdef __cplusplus
}
#endif

#endif  /* LED_DRIVER_H_ */

#ifndef CONFIG_H
#define CONFIG_H

#include "semphr.h"

extern int btn_state;
extern int led_state;
extern SemaphoreHandle_t xMutex;
extern TaskHandle_t xTaskControlarLed;

#define GREEN_LED_PIN 2
#define BTN_A_PIN 3

#endif

#include "FreeRTOS.h"
#include "config.h"

int btn_state = 0;
int led_state = 0;
SemaphoreHandle_t xMutex;
TaskHandle_t xTaskControlarLed;

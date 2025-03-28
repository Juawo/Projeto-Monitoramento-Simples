#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "config.h"
#include "tarefas.h"
#include "semphr.h"

void vLerButao(void *pvParameters) {
    while (1) {
        int estadoAtual = gpio_get(BTN_A_PIN); // Lê o botão

        if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
            btn_state = estadoAtual;
            xSemaphoreGive(xMutex);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vProcessar(void *pvParameters) {
    while (1) {
        int estado;
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
            estado = btn_state;
            xSemaphoreGive(xMutex);
        }

        if (estado == 1) {
            vTaskResume(xTaskControlarLed);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void vControlarLed(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
            led_state = !led_state;
            xSemaphoreGive(xMutex);
        }

        gpio_put(GREEN_LED_PIN, led_state);
        vTaskDelay(pdMS_TO_TICKS(100));

        vTaskSuspend(xTaskControlarLed);
    }
}

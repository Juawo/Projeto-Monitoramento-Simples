#include <stdlib.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "config.h"
#include "tarefas.h"

void setup() {
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(BTN_A_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
}

int main() {
    setup();

    xMutex = xSemaphoreCreateMutex(); // Criar antes das tarefas

    xTaskCreate(vLerButao, "Ler Estado do Butão", 256, NULL, 1, NULL);
    xTaskCreate(vProcessar, "Processar Decisão", 256, NULL, 2, NULL);
    xTaskCreate(vControlarLed, "Controlar LED", 256, NULL, 3, &xTaskControlarLed);

    vTaskStartScheduler();

    for (;;);
}

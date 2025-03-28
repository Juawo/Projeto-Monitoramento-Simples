#include "FreeRTOS.h"
#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "pico/stdlib.h"
#include "config.h"
#include "tarefas.h"
#include "semphr.h"

void vLerButao(void *pvParameters)
{
    while (1)
    {
        int estadoAtual = !gpio_get(BTN_A_PIN); // Ler o botão
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) { 
            btn_state = estadoAtual; // Atualiza estado do botão
            xSemaphoreGive(xMutex); 
        }
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}

void vProcessar(void *pvParameters) {
    int estadoAnterior = 0;
    while (1) {
        int estadoAtual;
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
            estadoAtual = btn_state;
            xSemaphoreGive(xMutex);
        }

        if (estadoAtual == 1 && estadoAnterior == 0) { // Detecta transição do botão
            vTaskResume(xTaskControlarLed); // Ativa LED
        }

        estadoAnterior = estadoAtual; // Atualiza estado anterior

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}


void vControlarLed(void *pvParameters) {
    while (1) {
        vTaskSuspend(NULL); // Aguarda ser ativada

        if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
            led_state = !led_state; // Alterna estado do LED
            btn_state = 0; // Resetar para evitar reativação contínua
            xSemaphoreGive(xMutex);
        }

        gpio_put(GREEN_LED_PIN, led_state); // Atualiza LED

        vTaskDelay(pdMS_TO_TICKS(100)); // Pequeno delay para estabilidade
    }
}


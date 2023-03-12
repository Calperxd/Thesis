#include "setup.h"
#include "FreeRTOS.h"
#include "task.h"

// toggle the led 1 every second
void taskLed1(void *pvParameters)
{
    while (1)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        vTaskDelay(pdMS_TO_TICKS(500));
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// toggle the led 2 every 200 second
void taskLed2(void *pvParameters)
{
    while (1)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        vTaskDelay(pdMS_TO_TICKS(200));
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main(void)
{
    setupClock();
    setupLed();
    xTaskCreate((TaskFunction_t)taskLed1, "Led1", configMINIMAL_STACK_SIZE, NULL, 5, NULL );
    xTaskCreate((TaskFunction_t)taskLed2, "Led2", configMINIMAL_STACK_SIZE, NULL, 5, NULL );
    vTaskStartScheduler();
    while (1){}
}
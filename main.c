/*************************************************************************************************/
/*Standard Includes*/
#include <stdlib.h>

/*************************************************************************************************/
/*FreeRTOS Includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"

/*************************************************************************************************/
/*Project Includes*/
#include "setup.h"
#include "Decoder.h"
#include "Potentiometer.h"
/*************************************************************************************************/
/*Global Variables*/
volatile uint8_t RUNNING_SAMPLING = (1 << 0 );
uint32_t SamplingTime = 15;
// Buffer adc
uint32_t pui32ADC0Value[1];
uint32_t SamplerCounter = 0;
/*************************************************************************************************/
/*FreeRTOS variables*/
static xQueueHandle mQueue = NULL;
static EventGroupHandle_t mEventGroup = NULL;
static TimerHandle_t mTimer = NULL;

/*************************************************************************************************/

void vTimerCallback(TimerHandle_t xTimer) 
{
    xEventGroupClearBits(mEventGroup, RUNNING_SAMPLING);
    SamplerCounter = 0;
}



void UARTIntHandler(void)
{
    uint8_t buffer[21] = {0};
    uint32_t status;
    uint_fast8_t i = 0;
    uint_fast8_t HashTagCounter = 0;
    status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, status);
    while(HashTagCounter < 6)
    {
        buffer[i] = UARTCharGet(UART0_BASE);
        if (buffer[i] == '#')
        {
            HashTagCounter++;
        }
        i++;
    }
    xQueueSendFromISR(mQueue, buffer, pdFALSE);
}

void DecoderTask(void *param)
{
    uint8_t buffer[21] = {0};
    FullCommand command;
    while (1)
    {
        if(uxQueueMessagesWaiting(mQueue) > 0)
        {
            if(xQueueReceive(mQueue, buffer, 0) == pdTRUE)
            {
                DecodeCommand(buffer, &command);
                switch (command.commands)
                {
                    case CMD_START:
                        SamplingTime = command.param1;
                        xEventGroupSetBits(mEventGroup, RUNNING_SAMPLING);
                        xTimerChangePeriod(mTimer, pdMS_TO_TICKS(SamplingTime * 1000), 0);
                        xTimerStart(mTimer, 0);
                        SamplerCounter = 0;
                        break;
                    case CMD_STOP:
                        xEventGroupClearBits(mEventGroup, RUNNING_SAMPLING);
                        if (xTimerIsTimerActive(mTimer))
                        {
                            xTimerStop(mTimer,0);
                        }
                        SamplerCounter = 0;
                        break;
                    case CMD_PLUS:
                        up();
                        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
                        vTaskDelay(pdMS_TO_TICKS(25));
                        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
                        vTaskDelay(pdMS_TO_TICKS(25));
                        break;
                    case CMD_MINUS:
                        down();
                        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
                        vTaskDelay(pdMS_TO_TICKS(25));
                        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
                        vTaskDelay(pdMS_TO_TICKS(25));
                        break;
                    case CMD_STRRG:
                        break;
                    case CMD_STRG:
                        break;
                    case CMD_CLRRG:
                        break;
                    default:
                        break;
                }
            }
        }
        memset(&command,0,sizeof(FullCommand));
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void SamplerTask(void *param)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(200);
    xLastWakeTime = xTaskGetTickCount();
    EventBits_t uxBits;
    uint32_t value;
    char buffer[6];
    int i, len;
    while (1)
    {
        uxBits = xEventGroupWaitBits(mEventGroup, RUNNING_SAMPLING, pdFALSE, pdFALSE, 0);
        if ((uxBits & RUNNING_SAMPLING) ==  RUNNING_SAMPLING)
        {
            
            ADCProcessorTrigger(ADC0_BASE, 3);
            while(!ADCIntStatus(ADC0_BASE, 3, false)){}
            ADCIntClear(ADC0_BASE, 3);
            ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);
            value = pui32ADC0Value[0];
            // Determina a quantidade de dígitos no número
            if (value == 0) 
            {
                len = 1;
            } 
            else 
            {
                for (len = 0; value > 0; len++) 
                {
                    value /= 10;
                }
            }
            // Converte o valor numérico para caracteres
            value = pui32ADC0Value[0];
            for (i = len - 1; i >= 0; i--) 
            {
                buffer[i] = (value % 10) + '0';
                value /=10;
            }
            // Envia caracteres pelo UART
            for (i = 0; i < len; i++) 
            {
                UARTCharPut(UART0_BASE, buffer[i]);
            }
            UARTCharPut(UART0_BASE, 10);  // Newline
            SamplerCounter++;
            continue;
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void WorkingTask(void *param)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(500);
    xLastWakeTime = xTaskGetTickCount();
    uint8_t WorkingLed = 0;
    EventBits_t uxBits;
    while (1)
    {
        uxBits = xEventGroupWaitBits(mEventGroup, RUNNING_SAMPLING, pdFALSE, pdFALSE, 0);
        if((uxBits & RUNNING_SAMPLING) ==  RUNNING_SAMPLING)
        {
            WorkingLed ^= (1 << 0);
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, WorkingLed);
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }
        WorkingLed ^= (1 << 0);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, WorkingLed);
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}


int main(void)
{
    setupClock();
    setupLed();
    setupUart();
    setupADC();
    mQueue = xQueueCreate(10, 21);
    mEventGroup = xEventGroupCreate();
    mTimer = xTimerCreate("Timer", pdMS_TO_TICKS(SamplingTime * 1000), pdFALSE, (void *)0, vTimerCallback);
    xTaskCreate(DecoderTask, "Decoder", configMINIMAL_STACK_SIZE, NULL, 4, NULL );
    xTaskCreate(SamplerTask, "Sampler", configMINIMAL_STACK_SIZE, NULL, 4, NULL );
    xTaskCreate(WorkingTask, "WorkingLed", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
    vTaskStartScheduler();
    while(1){}
}

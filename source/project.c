#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/*Setup Lib*/
#include "setup.h"
#include "floatpointUtils.h"
#include "microFFT.h"
#include "Potentiometer.h"


/* Scheduler includes. */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

/*Linear Regression Lib*/
#include "LinearRegression.h"

// TCB
static TaskHandle_t taskLED = NULL;
static TaskHandle_t taskADC = NULL;
static TaskHandle_t taskPOT = NULL;
static TaskHandle_t taskListener = NULL;

// Table
LinearRegressionTable table;

// Buffer adc
uint32_t pui32ADC0Value[1];

char angular[5];
char linear[5];

uint8_t time[2] = {0};
uint8_t digitCounter = 0;
uint8_t sampleTime = 15;
bool StartSampling =  false;

// turn on
void TaskLED(void *pvParameters)
{
    while (1)
    {
        if (!StartSampling)
        {
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
            vTaskDelay(pdMS_TO_TICKS(500));
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        if (StartSampling)
        {
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
            vTaskDelay(pdMS_TO_TICKS(100));
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}


void TaskADC(void *pvParameters)
{
    uint8_t snum[4];
    while (1)
    {
        ADCProcessorTrigger(ADC0_BASE, 3);
        while(!ADCIntStatus(ADC0_BASE, 3, false)){}
        ADCIntClear(ADC0_BASE, 3);
        ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);
        itoa(pui32ADC0Value[0], snum, 4);
        UARTCharPut(UART0_BASE, snum[0]);
        UARTCharPut(UART0_BASE, snum[1]);
        UARTCharPut(UART0_BASE, snum[2]);
        UARTCharPut(UART0_BASE, snum[3]);
        UARTCharPut(UART0_BASE, 10);
    }
}

void TaskPOT(void *pvParameters)
{
    uint32_t btnUp;
    uint32_t btnDown;
    while (1)
    {
        btnUp = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0);
        btnDown = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1);
        if(btnUp == 0)
        {
            up();
        }
        if(btnDown == 0)
        {
            down();
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

static void Commands(uint32_t command)
{
    switch (command)
    {
        case 35:
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
            vTaskDelay(pdMS_TO_TICKS(25));
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
            vTaskDelay(pdMS_TO_TICKS(25));
            break;
        case 36:
            up();
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
            vTaskDelay(pdMS_TO_TICKS(25));
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
            vTaskDelay(pdMS_TO_TICKS(25));
            break;
        case 37:
            down();
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
            vTaskDelay(pdMS_TO_TICKS(25));
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
            vTaskDelay(pdMS_TO_TICKS(25));
            break;

        default:
            time[digitCounter] = command;
            UARTCharPut(UART0_BASE, time[digitCounter]);
            digitCounter++;
            break;
    }
    if (digitCounter == 2)
    {
        sampleTime = atoi(time);
        digitCounter = 0;
        StartSampling =  true;
    }
}


void TaskListener(void *pvParameters)
{
    vTaskSuspend(taskADC);
    uint32_t Chars = 0;
    while (1)
    {
        while(UARTCharsAvail(UART0_BASE))
        {
            Chars = UARTCharGetNonBlocking(UART0_BASE);
            Commands(Chars);
        }
        if (StartSampling)
        {
            vTaskResume(taskADC);
            vTaskDelay(pdMS_TO_TICKS(1000*sampleTime));
            vTaskSuspend(taskADC);
            sampleTime = 0;
            StartSampling =  false;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

int main(void)
{
    setupClock();
    setupLed();
    setupSW();
    setupUart();
    setupADC();
    setupDigitalPotentiometer();
    static int x[4] = {1,2,3,4};
    static float y[4] = {701.4, 1201, 1713, 2197};
    table.maxIndex = 4;
    table.x = x;
    table.y = y;
    tableRegister(table);

    //char ampBuff[5];
    //char freqBuff[5];
    //ftoa(getAngularCoef(),angular,5);
    //ftoa(getLinearCoef(),linear,5);

    xTaskCreate((TaskFunction_t)TaskLED, "LED", configMINIMAL_STACK_SIZE, NULL, 4, &taskLED );
    xTaskCreate((TaskFunction_t)TaskADC, "ADC", configMINIMAL_STACK_SIZE, NULL, 4, &taskADC );
    xTaskCreate((TaskFunction_t)TaskPOT, "Potentiometer", configMINIMAL_STACK_SIZE, NULL, 7, &taskPOT );
    xTaskCreate((TaskFunction_t)TaskListener, "Listener", configMINIMAL_STACK_SIZE, NULL, 4, &taskListener );
    vTaskStartScheduler();
    while (1){}
}
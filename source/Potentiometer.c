#include "Potentiometer.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "setup.h"

void setupDigitalPotentiometer(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)){}
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);
    // Pin CS must be high
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, (1<<GPIO_PIN_2));
}

//PN2 - CS
//PN3 - INC
//PN4 - U/D
void up(void)
{
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, 0);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_4, GPIO_PIN_4);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, 0);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, GPIO_PIN_2);
}

void down(void)
{
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, 0);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_4, 0);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, 0);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);
    SysCtlDelay(getClock() / (100 * 3));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, GPIO_PIN_2);
}
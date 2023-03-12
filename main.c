#include "setup.h"

int main()
{
    setupClock();
    setupLed();
    while (1)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
        for (size_t i = 0; i < 1000000; i++)
        {
            /* code */
        }
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
        for (size_t i = 0; i < 1000000; i++)
        {
            /* code */
        }
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 2);
        for (size_t i = 0; i < 1000000; i++)
        {
            /* code */
        }
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
        for (size_t i = 0; i < 1000000; i++)
        {
            /* code */
        }
    }
    
    return 0;
}

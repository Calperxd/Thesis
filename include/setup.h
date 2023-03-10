/**
 * @file setup.h
 * @author Gabriel Alexandre Linhares Calper Seabra (gcalperseabra@gmail.com)
 * @brief Setup header
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SETUP_H
#define SETUP_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


/* TivaWare includes */
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"



/**
 * @brief Setup the system clock
 * 
 */
void setupClock(void);

/**
 * @brief Setup the GPIO PORT N for use of leds
 * 
 */
void setupLed(void);

/**
 * @brief Setup the switch buttom just for test cases
 * 
 */
void setupSW(void);

/**
 * @brief Setup the UART 115200 8-1 No parity
 * 
 */
void setupUart(void);
/**
 * @brief Setup the adc
 * 
 */
void setupADC(void);
/**
 * @brief Get the system clock
 * 
 * @return int 
 */
int getClock(void);




#endif
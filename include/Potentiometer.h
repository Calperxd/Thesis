/**
 * @file Potentiometer.h
 * @author Gabriel Alexandre Linhares Calper Seabra
 * @brief This is a library for controlling a digital potentiometer using the following pins:
 * PN2 - CS
 * PN3 - INC
 * PN4 - U/D
 * @version 0.1
 * @date 2022-11-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

/**
 * @brief Initializes the pins used for the digital potentiometer.
 * 
 */
void setupDigitalPotentiometer(void);

/**
 * @brief Increases the value of the potentiometer.
 * 
 */
void up(void);

/**
 * @brief Decreases the value of the potentiometer.
 * 
 */
void down(void);

#endif

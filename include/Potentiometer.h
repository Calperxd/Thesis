/**
 * @file Potentiometer.h
 * @author Gabriel Alexandre Linhares Calper Seabra (gcalperseabra@gmail.com)
 * @brief This is a lib for digital potentiometer the pins used were
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
 * @brief This function initilize the pins used in digital potentiometer
 * 
 */
void setupDigitalPotentiometer(void);
void up(void);
void down(void);





#endif
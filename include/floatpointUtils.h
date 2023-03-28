/**
 * @file floatpointUtils.h
 * @brief Declarations of functions for operations with floating-point numbers
 * @version 0.1
 * @date 2022-11-02
 */

#ifndef FLOATPOINTUTILS_H
#define FLOATPOINTUTILS_H
#include <math.h>
#include <stdint.h>


/**
 * @brief Rounds a floating-point number to two decimal places.
 * @param num The number to be rounded.
 * @return The rounded number with two decimal places.
 */
float roundToTwoDecimalPlaces(float num);

void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char* res, int afterpoint);

#endif

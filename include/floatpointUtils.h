/**
 * @file floatpointUtils.h
 * @brief Float point lib utils
 * @version 0.1
 * @date 2022-11-02
 * 
 * 
 */


#ifndef FLOATPOIJNTUTILS_H
#define FLOATPOIJNTUTILS_H
#include <math.h>

float roundToTwoDecimalPlaces(float num);
void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void floatToString(float n, char* res, int afterpoint);



#endif

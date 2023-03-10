/**
 * @file LinearRegression.h
 * @author Gabriel Alexandre Linhares Calper Seabra(gcalperseabra@gmail.com)
 * @brief This is an implementation of linear regression
 * @version 0.1
 * @date 2022-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include <math.h>

typedef struct LinearRegressionTable
{
    int maxIndex;
    int *x;
    float *y;
}LinearRegressionTable;

/**
 * @brief This function executes a LinearRegression on the  array x and y, note that you must pass the leanght of array for both x and y
 * 
 * @param table the array to perform the linear regression
 */
void tableRegister(LinearRegressionTable table);
/**
 * @brief Get the Angular Coeffiecient
 * 
 * @return float 
 */
float getAngularCoef(void);
/**
 * @brief Get the Linear Coefficient
 * 
 * @return float 
 */
float getLinearCoef(void);

#endif
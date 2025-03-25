/**
 * @file r_square.h
 * @brief
 * 在C语言中，你可以通过以下步骤来计算这些拟合优度参数：
 * 计算预测值：使用拟合得到的多项式系数，计算每个数据点的预测值。
 * 计算SSE：对于每个数据点，计算预测值与实际值之间的差异，平方后求和。
 * 计算R?：
 * 计算实际值的平均值。
 * 计算总平方和（SST），即每个实际值与平均值的差异的平方和。
 * R? = 1 - (SSE / SST)
 * 计算Adjusted R?：
 * Adjusted R? = 1 - [(1 - R?) * (n - 1) / (n - p - 1)]
 * 其中，n是数据点的数量，p是模型中参数的个数。
 * 计算RMSE：
 * RMSE = sqrt(SSE / n)
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-25
 * @copyright Copyright (c) 2025  Zhengzhou GL. TECH Co.,Ltd
 *
 */

#ifndef R_SQUARE_H
#define R_SQUARE_H

#include <stddef.h>

// 计算R?的函数声明
float r_square_float(const float *d_X, const float *d_Y, int d_N, const float *coeff, int n);
double r_square_double(const double *d_X, const double *d_Y, int d_N, const double *coeff, int n);

#endif // R_SQUARE_H

/**
 * @file cubic_fit.h
 * @brief 多项式拟合
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-13
 * @copyright Copyright (c) 2025  Zhengzhou GL. TECH Co.,Ltd
 *
 */
#ifndef __CUBIC_FIT_H_
#define __CUBIC_FIT_H_

/**
 * @brief 三次拟合函数
 *
 * @param d_X 输入的数据的x值
 * @param d_Y 输入的数据的y值
 * @param d_N 输入的数据的个数
 * @param rank 多项式的次数 only 3
 * @param coeff 输出的系数
 */
void polyfit(double *d_X, double *d_Y, int d_N, int rank, double *coeff);

/**
 * @brief 计算三次拟合曲线的极值点
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-13
 *
 */
void find_max_y_x(double coef[4], double x_min, double x_max, double *x_max_y, double *max_y);

/**
 * @brief 线性曲线拟合
 *
 * @param x
 * @param y
 * @param size
 * @param slope
 * @param intercept
 */
void linear_curve_fit(float *x, float *y, int size, float *slope, float *intercept);

// 二次拟合函数
void quadratic_fit(double *x, double *y, int n, double *a, double *b, double *c);
#endif

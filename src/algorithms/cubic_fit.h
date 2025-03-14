/**
 * @file cubic_fit.h
 * @brief ����ʽ���
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-13
 * @copyright Copyright (c) 2025  Zhengzhou GL. TECH Co.,Ltd
 *
 */
#ifndef __CUBIC_FIT_H_
#define __CUBIC_FIT_H_

/**
 * @brief
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-13
 *
 */
void polyfit(double *d_X, double *d_Y, int d_N, int rank, double *coeff);

/**
 * @brief ��������������ߵļ�ֵ��
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-13
 *
 */
void find_max_y_x(double coef[4], double x_min, double x_max, double *x_max_y, double *max_y);
#endif

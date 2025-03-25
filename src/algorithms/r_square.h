/**
 * @file r_square.h
 * @brief
 * ��C�����У������ͨ�����²�����������Щ����ŶȲ�����
 * ����Ԥ��ֵ��ʹ����ϵõ��Ķ���ʽϵ��������ÿ�����ݵ��Ԥ��ֵ��
 * ����SSE������ÿ�����ݵ㣬����Ԥ��ֵ��ʵ��ֵ֮��Ĳ��죬ƽ������͡�
 * ����R?��
 * ����ʵ��ֵ��ƽ��ֵ��
 * ������ƽ���ͣ�SST������ÿ��ʵ��ֵ��ƽ��ֵ�Ĳ����ƽ���͡�
 * R? = 1 - (SSE / SST)
 * ����Adjusted R?��
 * Adjusted R? = 1 - [(1 - R?) * (n - 1) / (n - p - 1)]
 * ���У�n�����ݵ��������p��ģ���в����ĸ�����
 * ����RMSE��
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

// ����R?�ĺ�������
float r_square_float(const float *d_X, const float *d_Y, int d_N, const float *coeff, int n);
double r_square_double(const double *d_X, const double *d_Y, int d_N, const double *coeff, int n);

#endif // R_SQUARE_H

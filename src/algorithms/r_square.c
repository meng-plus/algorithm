#include "r_square.h"
#include <math.h>

// 计算多项式预测值
static float predict_float(float x, const float *coeff, int n)
{
    float result = 0.0f;
    for (int i = 0; i <= n; i++) { result += coeff[i] * powf(x, i); }
    return result;
}

static double predict_double(double x, const double *coeff, int n)
{
    double result = 0.0;
    for (int i = 0; i <= n; i++) { result += coeff[i] * pow(x, i); }
    return result;
}

// 计算R?的函数实现（float版本）
float r_square_float(const float *d_X, const float *d_Y, int d_N, const float *coeff, int n)
{
    float sse = 0.0f, sst = 0.0f, y_mean = 0.0f;

    // 计算实际值的平均值
    for (int i = 0; i < d_N; i++) { y_mean += d_Y[i]; }
    y_mean /= d_N;

    // 计算SSE和SST
    for (int i = 0; i < d_N; i++)
    {
        float y_pred  = predict_float(d_X[i], coeff, n);
        sse          += (y_pred - d_Y[i]) * (y_pred - d_Y[i]);
        sst          += (d_Y[i] - y_mean) * (d_Y[i] - y_mean);
    }

    // 计算R?
    return 1.0f - (sse / sst);
}

// 计算R?的函数实现（double版本）
double r_square_double(const double *d_X, const double *d_Y, int d_N, const double *coeff, int n)
{
    double sse = 0.0, sst = 0.0, y_mean = 0.0;

    // 计算实际值的平均值
    for (int i = 0; i < d_N; i++) { y_mean += d_Y[i]; }
    y_mean /= d_N;

    // 计算SSE和SST
    for (int i = 0; i < d_N; i++)
    {
        double y_pred  = predict_double(d_X[i], coeff, n);
        sse           += (y_pred - d_Y[i]) * (y_pred - d_Y[i]);
        sst           += (d_Y[i] - y_mean) * (d_Y[i] - y_mean);
    }

    // 计算R?
    return 1.0 - (sse / sst);
}

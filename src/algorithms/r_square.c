#include "r_square.h"
#include <math.h>

// �������ʽԤ��ֵ
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

// ����R?�ĺ���ʵ�֣�float�汾��
float r_square_float(const float *d_X, const float *d_Y, int d_N, const float *coeff, int n)
{
    float sse = 0.0f, sst = 0.0f, y_mean = 0.0f;

    // ����ʵ��ֵ��ƽ��ֵ
    for (int i = 0; i < d_N; i++) { y_mean += d_Y[i]; }
    y_mean /= d_N;

    // ����SSE��SST
    for (int i = 0; i < d_N; i++)
    {
        float y_pred  = predict_float(d_X[i], coeff, n);
        sse          += (y_pred - d_Y[i]) * (y_pred - d_Y[i]);
        sst          += (d_Y[i] - y_mean) * (d_Y[i] - y_mean);
    }

    // ����R?
    return 1.0f - (sse / sst);
}

// ����R?�ĺ���ʵ�֣�double�汾��
double r_square_double(const double *d_X, const double *d_Y, int d_N, const double *coeff, int n)
{
    double sse = 0.0, sst = 0.0, y_mean = 0.0;

    // ����ʵ��ֵ��ƽ��ֵ
    for (int i = 0; i < d_N; i++) { y_mean += d_Y[i]; }
    y_mean /= d_N;

    // ����SSE��SST
    for (int i = 0; i < d_N; i++)
    {
        double y_pred  = predict_double(d_X[i], coeff, n);
        sse           += (y_pred - d_Y[i]) * (y_pred - d_Y[i]);
        sst           += (d_Y[i] - y_mean) * (d_Y[i] - y_mean);
    }

    // ����R?
    return 1.0 - (sse / sst);
}

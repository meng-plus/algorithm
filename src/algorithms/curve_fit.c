#include "curve_fit.h"

void linear_curve_fit(float *x, float *y, int size, float *slope, float *intercept)
{
        float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < size; i++)
    {
        sum_x  += x[i];
        sum_y  += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    *slope     = (size * sum_xy - sum_x * sum_y) / (size * sum_x2 - sum_x * sum_x);
    *intercept = (sum_y - *slope * sum_x) / size;
}

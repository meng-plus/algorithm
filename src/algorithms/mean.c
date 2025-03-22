#include "mean.h"

float mean_i(int *data, int size)
{
    float sum = 0;
    for (int i = 0; i < size; i++) { sum += data[i] / 1.0 / size; }
    return sum;
}

float mean_f(float *data, int size)
{
    float sum = 0.0f;
    for (int i = 0; i < size; i++) { sum += (data[i] / size); }
    return sum;
}

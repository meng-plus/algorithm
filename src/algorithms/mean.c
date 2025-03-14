#include "mean.h"

int mean(int *data, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += data[i];
    }
    return sum / size;
}

#include "filter.h"

void sliding_window_filter(int *input, int *output, int size, int window_size)
{
    for (int i = 0; i <= size - window_size; i++)
    {
        output[i] = 0;
        for (int j = 0; j < window_size; j++)
        {
            output[i] += input[i + j];
        }
        output[i] /= window_size;
    }
}

#include "filter.h"
#include <string.h>
void sliding_window_filter(int *input, int *output, int size, int window_size)
{
    for (int i = 0; i <= size - window_size; i++)
    {
        output[i] = 0;
        for (int j = 0; j < window_size; j++) { output[i] += input[i + j]; }
        output[i] /= window_size;
    }
}

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
void medianFilter(void *arr, int size, int elementSize, void *medianValue, CompareFunc compare)
{
    bubbleSort(arr, size, elementSize, compare);
    if (size % 2 == 0)
    {
        int mid1            = size / 2 - 1;
        int mid2            = size / 2;
        int value1          = *(int *)((char *)arr + mid1 * sizeof(int));
        int value2          = *(int *)((char *)arr + mid2 * sizeof(int));
        *(int *)medianValue = (value1 + value2) / 2;
    }
    else
    {
        int mid = size / 2;
        memcpy(medianValue, (char *)arr + mid * sizeof(int), elementSize);
    }
}
// 通用最大值及位置
void findMaxGeneric(void *arr, int size, int elementSize, void *maxValue, int *maxIndex, CompareFunc compare)
{
    memcpy(maxValue, arr, elementSize);
    *maxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        void *currentElement = (char *)arr + i * elementSize;
        if (compare(currentElement, maxValue) > 0)
        {
            memcpy(maxValue, currentElement, elementSize);
            *maxIndex = i;
        }
    }
}

// 通用最小值及位置
void findMinGeneric(void *arr, int size, int elementSize, void *minValue, int *minIndex, CompareFunc compare)
{
    memcpy(minValue, arr, elementSize);
    *minIndex = 0;
    for (int i = 1; i < size; i++)
    {
        void *currentElement = (char *)arr + i * elementSize;
        if (compare(currentElement, minValue) < 0)
        {
            memcpy(minValue, currentElement, elementSize);
            *minIndex = i;
        }
    }
}

int countOccurrences(int arr[], int size, int target)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target) { count++; }
    }
    return count;
}

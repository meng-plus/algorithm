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

// 均值滤波
int32_t meanFilterint32(int32_t arr[], int size)
{
    int32_t sum = 0;
    for (int i = 0; i < size; i++) { sum += arr[i]; }
    return sum / size;
}
// 均值滤波
float meanFilterFloat(float arr[], int size)
{
    float sum = 0;
    for (int i = 0; i < size; i++) { sum += arr[i]; }
    return sum / size;
}
uint16_t meanFilterUint16(uint16_t arr[], int size)
{
    uint32_t sum = 0;
    for (int i = 0; i < size; i++) { sum += arr[i]; }
    return sum / size;
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
    int mid = size / 2;
    memcpy(medianValue, (char *)arr + mid * sizeof(int), elementSize);
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

int countOccurrences(void *arr, int size, int elementSize, void *target)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        void *currentElement = (char *)arr + i * elementSize;
        if (memcmp(currentElement, target, elementSize) == 0) { count++; }
    }
    return count;
}

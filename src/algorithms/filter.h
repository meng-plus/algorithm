#ifndef FILTER_H
#define FILTER_H

#include "sort.h"
/**
 * @brief 移动平均滤波
 *
 * @param arr
 * @param size
 * @param windowSize
 * @return float
 */
void sliding_window_filter(int *input, int *output, int size, int window_size);
/**
 * @brief 均值滤波
 *
 * @param data
 * @param size
 * @return float
 */
float mean_i(int* data, int size);
float mean_f(float * data, int size);
/**
 * @brief 中值滤波
 *
 * @param arr 数组
 * @param size 数组长度
 * @param elementSize 元素大小
 * @param medianValue 中值
 * @param compare 比较函数
 * @return int
 */
void medianFilter(void *arr, int size,  int elementSize,void *medianValue,CompareFunc compare);

// 通用最大值及位置
void findMaxGeneric(void *arr, int size, int elementSize, void *maxValue, int *maxIndex, CompareFunc compare);
// 通用最小值及位置
void findMinGeneric(void *arr, int size, int elementSize, void *minValue, int *minIndex, CompareFunc compare);
int countOccurrences(int arr[], int size, int target);

#endif // FILTER_H

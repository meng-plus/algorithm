#ifndef FILTER_H
#define FILTER_H

#include "sort.h"
#include <stdint.h>
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
 * @param arr  数组
 * @param size 数组长度
 * @return  均值结果
 */
int32_t meanFilterint32(int32_t arr[], int size);
float meanFilterFloat(float arr[], int size);
uint16_t meanFilterUint16(uint16_t arr[], int size);
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

/**
 * @brief 寻找最大值
 *
 * @param arr 数据数组
 * @param size 数组长度
 * @param elementSize 元素大小
 * @param targetValue 目标数据
 * @param index 目标数据的位置
 * @param compare  compare(currentElement, mValue)
 */
void findMaxGeneric(void *arr, int size, int elementSize, void *targetValue, int *index, CompareFunc compare);
// 通用最小值及位置
void findMinGeneric(void *arr, int size, int elementSize, void *targetValue, int *index, CompareFunc compare);

/**
 * @brief  计算数组中某个元素出现的次数
 *
 * @param arr
 * @param size
 * @param elementSize
 * @param target
 * @param index
 * @return int 返回出现的次数
 */
int countOccurrences(void *arr, int size, int elementSize, void *target);

#endif // FILTER_H

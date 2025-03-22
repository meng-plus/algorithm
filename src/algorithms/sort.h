/**
 * @file sort.h
 * @brief 排序算法
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-22
 * @copyright Copyright (c) 2025  Zhengzhou GL. TECH Co.,Ltd
 *
 */
#ifndef __SORT_H_
#define __SORT_H_

#include <stdint.h>

// 比较函数类型
typedef int (*CompareFunc)(const void*, const void*);
// 示例比较函数（用于 float 类型）
int compareFloat(const void *a, const void *b);
// 示例比较函数（用于 int 类型）
int compareInt(const void *a, const void *b);

// 冒泡排序
void bubbleSort(void *arr, int size, int elementSize, CompareFunc compare);
// 选择排序
void selectionSort(void *arr, int size, int elementSize, CompareFunc compare);
// 插入排序
void insertionSort(void *arr, int size, int elementSize, CompareFunc compare);
// 希尔排序
void shellSort(void *arr, int size, int elementSize, CompareFunc compare);
// 归并排序
void mergeSort(void *arr, int size, int elementSize, CompareFunc compare);
// 快速排序
void quickSort(void *arr, int size, int elementSize, CompareFunc compare);
// 堆排序
void heapSort(void *arr, int size, int elementSize, CompareFunc compare);
// 计数排序
void countingSort(void *arr, int size, int elementSize, CompareFunc compare);
// 桶排序 未实现
//void bucketSort(void *arr, int size, int elementSize, CompareFunc compare);
// 基数排序
void radixSort(void *arr, int size, int elementSize, CompareFunc compare);

#endif

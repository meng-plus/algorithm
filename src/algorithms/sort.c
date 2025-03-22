/**
 * @file sort.c
 * @brief 排序函数
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-22
 * @copyright Copyright (c) 2025  Zhengzhou GL. TECH Co.,Ltd
 *
 */

#include "sort.h"
#include <stdlib.h>
#include <string.h>
// 示例比较函数（用于 int 类型）
int compareInt(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// 示例比较函数（用于 float 类型）
int compareFloat(const void *a, const void *b)
{
    float diff = (*(float *)a - *(float *)b);
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

// 冒泡排序
void bubbleSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            void *currentElement = (char *)arr + j * elementSize;
            void *nextElement    = (char *)arr + (j + 1) * elementSize;
            if (compare(currentElement, nextElement) > 0)
            {
                for (int k = 0; k < elementSize; k++)
                {
                    char temp                     = *((char *)currentElement + k);
                    *((char *)currentElement + k) = *((char *)nextElement + k);
                    *((char *)nextElement + k)    = temp;
                }
            }
        }
    }
}
// 选择排序
void selectionSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            void *currentElement = (char *)arr + j * elementSize;
            void *minElement     = (char *)arr + minIndex * elementSize;
            if (compare(currentElement, minElement) < 0) { minIndex = j; }
        }
        if (minIndex != i)
        {
            void *temp = malloc(elementSize);
            memcpy(temp, (char *)arr + i * elementSize, elementSize);
            memcpy((char *)arr + i * elementSize, (char *)arr + minIndex * elementSize, elementSize);
            memcpy((char *)arr + minIndex * elementSize, temp, elementSize);
            free(temp);
        }
    }
}
// 插入排序
void insertionSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    for (int i = 1; i < size; i++)
    {
        void *currentElement = malloc(elementSize);
        memcpy(currentElement, (char *)arr + i * elementSize, elementSize);
        int j = i - 1;
        while (j >= 0 && compare((char *)arr + j * elementSize, currentElement) > 0)
        {
            memcpy((char *)arr + (j + 1) * elementSize, (char *)arr + j * elementSize, elementSize);
            j--;
        }
        memcpy((char *)arr + (j + 1) * elementSize, currentElement, elementSize);
        free(currentElement);
    }
}
// 希尔排序
void shellSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            void *currentElement = malloc(elementSize);
            memcpy(currentElement, (char *)arr + i * elementSize, elementSize);
            int j = i - gap;
            while (j >= 0 && compare((char *)arr + j * elementSize, currentElement) > 0)
            {
                memcpy((char *)arr + (j + gap) * elementSize, (char *)arr + j * elementSize, elementSize);
                j -= gap;
            }
            memcpy((char *)arr + (j + gap) * elementSize, currentElement, elementSize);
            free(currentElement);
        }
    }
}
// 归并排序
void mergeSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    if (size <= 1) return;
    int mid = size / 2;
    mergeSort(arr, mid, elementSize, compare);
    mergeSort((char *)arr + mid * elementSize, size - mid, elementSize, compare);
    void *temp = malloc(size * elementSize);
    int i = 0, j = mid, k = 0;
    while (i < mid && j < size)
    {
        void *front = (char *)arr + i * elementSize;
        void *back  = (char *)arr + j * elementSize;
        if (compare(front, back) <= 0)
        {
            memcpy((char *)temp + k * elementSize, front, elementSize);
            i++;
        }
        else
        {
            memcpy((char *)temp + k * elementSize, back, elementSize);
            j++;
        }
        k++;
    }
    while (i < mid)
    {
        void *front = (char *)arr + i * elementSize;
        memcpy((char *)temp + k * elementSize, front, elementSize);
        i++;
        k++;
    }
    while (j < size)
    {
        void *back = (char *)arr + j * elementSize;
        memcpy((char *)temp + k * elementSize, back, elementSize);
        j++;
        k++;
    }
    memcpy(arr, temp, size * elementSize);
    free(temp);
}
// 快速排序
void quickSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    if (size <= 1) return;
    void *pivot = malloc(elementSize);
    memcpy(pivot, arr, elementSize);
    int i = 0, j = size - 1;
    while (i < j)
    {
        while (i < j && compare((char *)arr + j * elementSize, pivot) >= 0) j--;
        memcpy((char *)arr + i * elementSize, (char *)arr + j * elementSize, elementSize);
        while (i < j && compare((char *)arr + i * elementSize, pivot) <= 0) i++;
        memcpy((char *)arr + j * elementSize, (char *)arr + i * elementSize, elementSize);
    }
    memcpy((char *)arr + i * elementSize, pivot, elementSize);
    quickSort(arr, i, elementSize, compare);
    quickSort((char *)arr + (i + 1) * elementSize, size - i - 1, elementSize, compare);
    free(pivot);
}

void heapify(void *arr, int size, int index, int elementSize, CompareFunc compare)
{
    int largest = index;         // 假设当前节点是最大的
    int left    = 2 * index + 1; // 左子节点
    int right   = 2 * index + 2; // 右子节点

    // 找出当前节点、左子节点和右子节点中的最大值的索引
    if (left < size && compare((char *)arr + left * elementSize, (char *)arr + largest * elementSize) > 0)
    {
        largest = left;
    }
    if (right < size && compare((char *)arr + right * elementSize, (char *)arr + largest * elementSize) > 0)
    {
        largest = right;
    }

    // 如果最大值不是当前节点，交换并递归调整
    if (largest != index)
    {
        void *temp = malloc(elementSize);
        memcpy(temp, (char *)arr + index * elementSize, elementSize);
        memcpy((char *)arr + index * elementSize, (char *)arr + largest * elementSize, elementSize);
        memcpy((char *)arr + largest * elementSize, temp, elementSize);
        free(temp);

        heapify(arr, size, largest, elementSize, compare);
    }
}

// 堆排序
void heapSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    // 构建大顶堆
    for (int i = size / 2 - 1; i >= 0; i--) { heapify(arr, size, i, elementSize, compare); }

    // 依次交换堆顶元素和最后一个元素，并重新调整堆
    for (int i = size - 1; i > 0; i--)
    {
        // 交换堆顶元素和最后一个元素
        void *temp = malloc(elementSize);
        memcpy(temp, arr, elementSize);
        memcpy(arr, (char *)arr + i * elementSize, elementSize);
        memcpy((char *)arr + i * elementSize, temp, elementSize);
        free(temp);

        // 调整堆
        heapify(arr, i, 0, elementSize, compare);
    }
}

// 计数排序
void countingSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    int max = *(int *)arr;
    for (int i = 1; i < size; i++)
    {
        if (compare((char *)arr + i * elementSize, &max) > 0) { max = *(int *)((char *)arr + i * elementSize); }
    }
    int *count = (int *)malloc((max + 1) * sizeof(int));
    for (int i = 0; i <= max; i++) { count[i] = 0; }
    for (int i = 0; i < size; i++) { count[*(int *)((char *)arr + i * elementSize)]++; }
    for (int i = 1; i <= max; i++) { count[i] += count[i - 1]; }
    void *output = malloc(size * elementSize);
    for (int i = size - 1; i >= 0; i--)
    {
        int index = count[*(int *)((char *)arr + i * elementSize)] - 1;
        memcpy((char *)output + index * elementSize, (char *)arr + i * elementSize, elementSize);
        count[*(int *)((char *)arr + i * elementSize)]--;
    }
    memcpy(arr, output, size * elementSize);
    free(count);
    free(output);
}
// 基数排序
void radixSort(void *arr, int size, int elementSize, CompareFunc compare)
{
    int max = *(int *)arr;
    for (int i = 1; i < size; i++)
    {
        if (compare((char *)arr + i * elementSize, &max) > 0) { max = *(int *)((char *)arr + i * elementSize); }
    }
    for (int exp = 1; max / exp > 0; exp *= 10) { countingSort(arr, size, elementSize, compare); }
}

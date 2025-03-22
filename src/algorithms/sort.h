/**
 * @file sort.h
 * @brief �����㷨
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-22
 * @copyright Copyright (c) 2025  Zhengzhou GL. TECH Co.,Ltd
 *
 */
#ifndef __SORT_H_
#define __SORT_H_

#include <stdint.h>

// �ȽϺ�������
typedef int (*CompareFunc)(const void*, const void*);
// ʾ���ȽϺ��������� float ���ͣ�
int compareFloat(const void *a, const void *b);
// ʾ���ȽϺ��������� int ���ͣ�
int compareInt(const void *a, const void *b);

// ð������
void bubbleSort(void *arr, int size, int elementSize, CompareFunc compare);
// ѡ������
void selectionSort(void *arr, int size, int elementSize, CompareFunc compare);
// ��������
void insertionSort(void *arr, int size, int elementSize, CompareFunc compare);
// ϣ������
void shellSort(void *arr, int size, int elementSize, CompareFunc compare);
// �鲢����
void mergeSort(void *arr, int size, int elementSize, CompareFunc compare);
// ��������
void quickSort(void *arr, int size, int elementSize, CompareFunc compare);
// ������
void heapSort(void *arr, int size, int elementSize, CompareFunc compare);
// ��������
void countingSort(void *arr, int size, int elementSize, CompareFunc compare);
// Ͱ���� δʵ��
//void bucketSort(void *arr, int size, int elementSize, CompareFunc compare);
// ��������
void radixSort(void *arr, int size, int elementSize, CompareFunc compare);

#endif

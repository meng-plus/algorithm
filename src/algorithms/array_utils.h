#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stddef.h>
#include "sort.h"
// 比较函数指针类型
typedef int (*CompareFunc)(const void *, const void *);

// 数组操作功能
size_t remove_duplicates(void *base, size_t num, size_t size, CompareFunc compare);   // 去重
void reverse_array(void *base, size_t num, size_t size);                              // 反转数组
void *find_median(void *base, size_t num, size_t size, CompareFunc compare);          // 查找中位数
void *find_mode(void *base, size_t num, size_t size, CompareFunc compare);            // 查找众数
void array_slice(void *dest, const void *src, size_t start, size_t end, size_t size); // 数组切片
void array_fill(void *base, size_t num, size_t size, const void *value);              // 数组填充
void array_copy(void *dest, const void *src, size_t num, size_t size);                // 数组拷贝
double array_sum(const void *base, size_t num, size_t size);                          // 数组求和（适用于数值类型）
double array_average(const void *base, size_t num, size_t size);                      // 数组平均值（适用于数值类型）

#endif                                                                                // ARRAY_UTILS_H

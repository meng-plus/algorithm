/**
 * @file search.h
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 查找算法1
 * @version 0.1
 * @date 2025-03-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef SEARCH_LIB_H
#define SEARCH_LIB_H

#include <stddef.h>

// 比较函数指针类型
typedef int (*CompareFunc)(const void*, const void*);

// 线性查找
void* linear_search(const void* base, size_t num, size_t size, const void* target, CompareFunc compare);

// 二分查找（要求数据已排序）
void* binary_search(const void* base, size_t num, size_t size, const void* target, CompareFunc compare);
// 查找最大值
void* find_max(const void* base, size_t num, size_t size, CompareFunc compare);

// 查找最小值
void* find_min(const void* base, size_t num, size_t size, CompareFunc compare);

// 查找某个数据出现的次数
size_t count_occurrences(const void* base, size_t num, size_t size, const void* target, CompareFunc compare);

// 数组操作功能
size_t remove_duplicates(void* base, size_t num, size_t size, CompareFunc compare); // 去重
void reverse_array(void* base, size_t num, size_t size); // 反转数组
void* find_median(void* base, size_t num, size_t size, CompareFunc compare); // 查找中位数
void* find_mode(void* base, size_t num, size_t size, CompareFunc compare); // 查找众数
void array_slice(void* dest, const void* src, size_t start, size_t end, size_t size); // 数组切片
void array_fill(void* base, size_t num, size_t size, const void* value); // 数组填充
void array_copy(void* dest, const void* src, size_t num, size_t size); // 数组拷贝
double array_sum(const void* base, size_t num, size_t size); // 数组求和（适用于数值类型）
double array_average(const void* base, size_t num, size_t size); // 数组平均值（适用于数值类型）


#endif // SEARCH_LIB_H

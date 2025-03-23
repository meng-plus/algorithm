#include "search.h"
#include <string.h> // 用于 memcpy 和 memcmp
#include <stdlib.h> // 用于 malloc 和 free
// 线性查找实现
void *linear_search(const void *base, size_t num, size_t size, const void *target, CompareFunc compare)
{
    const char *array = (const char *)base;
    for (size_t i = 0; i < num; i++)
    {
        if (compare(array + i * size, target) == 0) { return (void *)(array + i * size); }
    }
    return NULL;
}

// 二分查找实现
void *binary_search(const void *base, size_t num, size_t size, const void *target, CompareFunc compare)
{
    const char *array = (const char *)base;
    size_t low        = 0;
    size_t high       = num - 1;

    while (low <= high)
    {
        size_t mid              = low + (high - low) / 2;
        const void *mid_element = array + mid * size;
        int cmp_result          = compare(mid_element, target);

        if (cmp_result == 0) { return (void *)mid_element; }
        else if (cmp_result < 0) { low = mid + 1; }
        else { high = mid - 1; }
    }
    return NULL;
}

// 查找最大值
void *find_max(const void *base, size_t num, size_t size, CompareFunc compare)
{
    if (num == 0) return NULL; // 空数组

    const char *array = (const char *)base;
    void *max         = (void *)(array); // 初始化为第一个元素

    for (size_t i = 1; i < num; i++)
    {
        if (compare(array + i * size, max) > 0) { max = (void *)(array + i * size); }
    }
    return max;
}

// 查找最小值
void *find_min(const void *base, size_t num, size_t size, CompareFunc compare)
{
    if (num == 0) return NULL; // 空数组

    const char *array = (const char *)base;
    void *min         = (void *)(array); // 初始化为第一个元素

    for (size_t i = 1; i < num; i++)
    {
        if (compare(array + i * size, min) < 0) { min = (void *)(array + i * size); }
    }
    return min;
}

// 查找某个数据出现的次数
size_t count_occurrences(const void *base, size_t num, size_t size, const void *target, CompareFunc compare)
{
    const char *array = (const char *)base;
    size_t count      = 0;

    for (size_t i = 0; i < num; i++)
    {
        if (compare(array + i * size, target) == 0) { count++; }
    }
    return count;
}

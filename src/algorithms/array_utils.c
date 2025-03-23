#include "array_utils.h"
#include <string.h> // 用于 memcpy 和 memcmp
#include <stdlib.h> // 用于 malloc 和 free

// 去重实现
size_t remove_duplicates(void *base, size_t num, size_t size, CompareFunc compare)
{
    if (num == 0) return 0;

    char *array         = (char *)base;
    size_t unique_index = 0;

    for (size_t i = 1; i < num; i++)
    {
        if (compare(array + i * size, array + unique_index * size) != 0)
        {
            unique_index++;
            memcpy(array + unique_index * size, array + i * size, size);
        }
    }

    return unique_index + 1; // 返回去重后的元素个数
}

// 反转数组实现
void reverse_array(void *base, size_t num, size_t size)
{
    char *array = (char *)base;
    for (size_t i = 0; i < num / 2; i++)
    {
        void *temp = malloc(size);
        memcpy(temp, array + i * size, size);
        memcpy(array + i * size, array + (num - i - 1) * size, size);
        memcpy(array + (num - i - 1) * size, temp, size);
        free(temp);
    }
}

// 查找中位数实现
void *find_median(void *base, size_t num, size_t size, CompareFunc compare)
{
    if (num == 0) return NULL;

    quickSort(base, num, size, compare); // 先排序
    return (char *)base + (num / 2) * size;
}

// 查找众数实现
void *find_mode(void *base, size_t num, size_t size, CompareFunc compare)
{
    if (num == 0) return NULL;

    quickSort(base, num, size, compare); // 先排序

    char *array          = (char *)base;
    void *mode           = array;
    size_t max_count     = 1;
    size_t current_count = 1;

    for (size_t i = 1; i < num; i++)
    {
        if (compare(array + i * size, array + (i - 1) * size) == 0)
        {
            current_count++;
            if (current_count > max_count)
            {
                max_count = current_count;
                mode      = array + i * size;
            }
        }
        else { current_count = 1; }
    }

    return mode;
}

// 数组切片实现
void array_slice(void *dest, const void *src, size_t start, size_t end, size_t size)
{
    const char *source = (const char *)src;
    char *destination  = (char *)dest;

    for (size_t i = start; i < end; i++) { memcpy(destination + (i - start) * size, source + i * size, size); }
}

// 数组填充实现
void array_fill(void *base, size_t num, size_t size, const void *value)
{
    char *array = (char *)base;
    for (size_t i = 0; i < num; i++) { memcpy(array + i * size, value, size); }
}

// 数组拷贝实现
void array_copy(void *dest, const void *src, size_t num, size_t size)
{
    memcpy(dest, src, num * size);
}

// 数组求和实现（适用于数值类型）
double array_sum(const void *base, size_t num, size_t size)
{
    const char *array = (const char *)base;
    double sum        = 0.0;

    for (size_t i = 0; i < num; i++)
    {
        if (size == sizeof(int)) { sum += *(int *)(array + i * size); }
        else if (size == sizeof(double)) { sum += *(double *)(array + i * size); }
        // 可以扩展支持更多类型
    }

    return sum;
}

// 数组平均值实现（适用于数值类型）
double array_average(const void *base, size_t num, size_t size)
{
    if (num == 0) return 0.0;
    return array_sum(base, num, size) / num;
}

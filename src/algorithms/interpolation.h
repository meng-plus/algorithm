#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <stdint.h>

// 支持的数据类型
typedef enum
{
    DATA_TYPE_INT,
    DATA_TYPE_FLOAT,
    DATA_TYPE_DOUBLE
} DataType;

// 插值算法类型
typedef enum
{
    INTERP_LINEAR,           /*!< 线性插值 */
    INTERP_NEAREST_NEIGHBOR, /*!< 临近插值 */
    INTERP_CUBIC,            /*!< 三次插值 */
    INTERP_LAGRANGE,         /*!< 拉格朗日插值 */
    INTERP_HERMITE,          /*!< 埃尔米特插值 */
    INTERP_BSPLINE           /*!< B样条插值 */
} InterpolationType;

/**
 * @brief  插值函数接口
 *
 * @param x 待插值的自变量
 * @param y 插值结果
 * @param x_table x表
 * @param y_table y表
 * @param table_size 表大小
 * @param data_type 数据类型
 * @param interp_type 插值算法类型
 */
void interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type,
                 InterpolationType interp_type);

#endif // INTERPOLATION_H

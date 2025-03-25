#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <stdint.h>
#include <stdbool.h>
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
    INTERP_SPLINE            /*!< B样条插值 计算结果与matlab 略有出入  ont  suppose DATA_TYPE_INT*/
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
// 样条插值系数结构体
typedef struct
{
    double *a;
    double *b;
    double *c;
    double *d;
} SplineCoefficients;

/**
 * @brief 创造系数结构体
 *
 * @param table_size 待插值数据长度
 * @return
 */
SplineCoefficients *splinecoeff_create(int table_size);
void splinecoeff_destory(SplineCoefficients *coeff);
/**
 * @brief 样条插值函数 计算插值系数
 *
 *
 * @param coeff  样条插值系数
 * @param x_table  x表
 * @param y_table  y表
 * @param table_size 表大小
 */
void calculate_spline_coefficients(SplineCoefficients *coeff, const void *x_table, const void *y_table, int table_size,
                                   DataType data_type);
/**
 * @brief 计算插值结果
 *
 * @param coeff  样条插值系数
 * @param x_val  待插值的自变量
 * @param x_table x表
 * @param table_size 表大小
 * @return
 */
double calculate_spline_result(SplineCoefficients *coeff, const void *x_val, const void *x_table, int table_size,
                               DataType data_type);

/**
 * @brief 计算样条插值结果
 * 是上面操作的整合步骤
 * @param x 待插值的自变量
 * @param y 插值结果
 * @param x_table x表
 * @param y_table y表
 * @param table_size 表大小
 * @return true 插值成功 false 插值失败
 */
bool spline_interpolate(const void *x, void *y, const void *x_table, const void *y_table, int table_size,
                        DataType data_type);
#endif // INTERPOLATION_H

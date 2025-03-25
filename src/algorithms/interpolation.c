#include "interpolation.h"

#include "interpolation.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// 线性插值
void linear_interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type)
{
    double x_val = 0.0;
    double y_val = 0.0;
    double x0 = 0.0, x1 = 0.0, y0 = 0.0, y1 = 0.0;
    if (data_type == DATA_TYPE_INT) { x_val = *(int *)x; }
    else if (data_type == DATA_TYPE_FLOAT) { x_val = *(float *)x; }
    else if (data_type == DATA_TYPE_DOUBLE) { x_val = *(double *)x; }
    for (int i = 0; i < table_size - 1; i++)
    {
        if (data_type == DATA_TYPE_INT)
        {
            x0 = ((int *)x_table)[i];
            x1 = ((int *)x_table)[i + 1];
            y0 = ((int *)y_table)[i];
            y1 = ((int *)y_table)[i + 1];
        }
        else if (data_type == DATA_TYPE_FLOAT)
        {
            x0 = ((float *)x_table)[i];
            x1 = ((float *)x_table)[i + 1];
            y0 = ((float *)y_table)[i];
            y1 = ((float *)y_table)[i + 1];
        }
        else if (data_type == DATA_TYPE_DOUBLE)
        {
            x0 = ((double *)x_table)[i];
            x1 = ((double *)x_table)[i + 1];
            y0 = ((double *)y_table)[i];
            y1 = ((double *)y_table)[i + 1];
        }
        if (x_val >= x0 && x_val <= x1)
        {
            y_val = y0 + (y1 - y0) * (x_val - x0) / (x1 - x0);
            break;
        }
    }
    if (data_type == DATA_TYPE_INT) { *(int *)y = (int)y_val; }
    else if (data_type == DATA_TYPE_FLOAT) { *(float *)y = (float)y_val; }
    else if (data_type == DATA_TYPE_DOUBLE) { *(double *)y = y_val; }
}
// 临近插值
void nearest_neighbor_interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type)
{
    double x_val    = 0.0;
    double y_val    = 0.0;
    double min_diff = 1e9;
    double diff     = 0.0;
    if (data_type == DATA_TYPE_INT) { x_val = *(int *)x; }
    else if (data_type == DATA_TYPE_FLOAT) { x_val = *(float *)x; }
    else if (data_type == DATA_TYPE_DOUBLE) { x_val = *(double *)x; }
    for (int i = 0; i < table_size; i++)
    {
        if (data_type == DATA_TYPE_INT) { diff = fabs(x_val - ((int *)x_table)[i]); }
        else if (data_type == DATA_TYPE_FLOAT) { diff = fabs(x_val - ((float *)x_table)[i]); }
        else if (data_type == DATA_TYPE_DOUBLE) { diff = fabs(x_val - ((double *)x_table)[i]); }
        if (diff < min_diff)
        {
            min_diff = diff;
            if (data_type == DATA_TYPE_INT) { y_val = ((int *)y_table)[i]; }
            else if (data_type == DATA_TYPE_FLOAT) { y_val = ((float *)y_table)[i]; }
            else if (data_type == DATA_TYPE_DOUBLE) { y_val = ((double *)y_table)[i]; }
        }
    }
    if (data_type == DATA_TYPE_INT) { *(int *)y = (int)y_val; }
    else if (data_type == DATA_TYPE_FLOAT) { *(float *)y = (float)y_val; }
    else if (data_type == DATA_TYPE_DOUBLE) { *(double *)y = y_val; }
}
// 三次插值

void cubic_interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type)
{
    if (!x || !y || !x_table || !y_table || table_size < 2)
    {
        return; // 非法输入
    }

    // 处理 float 类型
    if (data_type == DATA_TYPE_FLOAT)
    {
        float *xf = (float *)x;
        float *yf = (float *)y;
        float *xt = (float *)x_table;
        float *yt = (float *)y_table;

        // 边界处理（外推）：直接返回边界值
        if (*xf <= xt[0])
        {
            *yf = yt[0];
            return;
        }
        if (*xf >= xt[table_size - 1])
        {
            *yf = yt[table_size - 1];
            return;
        }

        for (int i = 0; i < table_size - 1; i++)
        {
            if (*xf >= xt[i] && *xf <= xt[i + 1])
            {
                // 选取4个点（避免越界）
                //float x0 = (i > 0) ? xt[i - 1] : xt[i];
                float x1 = xt[i];
                float x2 = xt[i + 1];
                //float x3 = (i < table_size - 2) ? xt[i + 2] : xt[i + 1];

                float y0 = (i > 0) ? yt[i - 1] : yt[i];
                float y1 = yt[i];
                float y2 = yt[i + 1];
                float y3 = (i < table_size - 2) ? yt[i + 2] : yt[i + 1];

                float t = (*xf - x1) / (x2 - x1);
                float a = (-0.5f * y0) + (1.5f * y1) - (1.5f * y2) + (0.5f * y3);
                float b = y0 - (2.5f * y1) + (2.0f * y2) - (0.5f * y3);
                float c = (-0.5f * y0) + (0.5f * y2);
                float d = y1;

                *yf = a * t * t * t + b * t * t + c * t + d;
                return;
            }
        }
    }

    // 处理 double 类型
    else if (data_type == DATA_TYPE_DOUBLE)
    {
        double *xd = (double *)x;
        double *yd = (double *)y;
        double *xt = (double *)x_table;
        double *yt = (double *)y_table;

        if (*xd <= xt[0])
        {
            *yd = yt[0];
            return;
        }
        if (*xd >= xt[table_size - 1])
        {
            *yd = yt[table_size - 1];
            return;
        }

        for (int i = 0; i < table_size - 1; i++)
        {
            if (*xd >= xt[i] && *xd <= xt[i + 1])
            {
                //double x0 = (i > 0) ? xt[i - 1] : xt[i];
                double x1 = xt[i];
                double x2 = xt[i + 1];
                //double x3 = (i < table_size - 2) ? xt[i + 2] : xt[i + 1];

                double y0 = (i > 0) ? yt[i - 1] : yt[i];
                double y1 = yt[i];
                double y2 = yt[i + 1];
                double y3 = (i < table_size - 2) ? yt[i + 2] : yt[i + 1];

                double t = (*xd - x1) / (x2 - x1);
                double a = (-0.5 * y0) + (1.5 * y1) - (1.5 * y2) + (0.5 * y3);
                double b = y0 - (2.5 * y1) + (2.0 * y2) - (0.5 * y3);
                double c = (-0.5 * y0) + (0.5 * y2);
                double d = y1;

                *yd = a * t * t * t + b * t * t + c * t + d;
                return;
            }
        }
    }

    // 处理 int 类型
    else if (data_type == DATA_TYPE_INT)
    {
        int *xi = (int *)x;
        int *yi = (int *)y;
        int *xt = (int *)x_table;
        int *yt = (int *)y_table;

        if (*xi <= xt[0])
        {
            *yi = yt[0];
            return;
        }
        if (*xi >= xt[table_size - 1])
        {
            *yi = yt[table_size - 1];
            return;
        }

        for (int i = 0; i < table_size - 1; i++)
        {
            if (*xi >= xt[i] && *xi <= xt[i + 1])
            {
                //int x0 = (i > 0) ? xt[i - 1] : xt[i];
                int x1 = xt[i];
                int x2 = xt[i + 1];
                //int x3 = (i < table_size - 2) ? xt[i + 2] : xt[i + 1];

                int y0 = (i > 0) ? yt[i - 1] : yt[i];
                int y1 = yt[i];
                int y2 = yt[i + 1];
                int y3 = (i < table_size - 2) ? yt[i + 2] : yt[i + 1];

                float t = (float)(*xi - x1) / (x2 - x1);
                float a = (-0.5f * y0) + (1.5f * y1) - (1.5f * y2) + (0.5f * y3);
                float b = y0 - (2.5f * y1) + (2.0f * y2) - (0.5f * y3);
                float c = (-0.5f * y0) + (0.5f * y2);
                float d = y1;

                *yi = (int)(a * t * t * t + b * t * t + c * t + d + 0.5f); // 四舍五入
                return;
            }
        }
    }
}

// 拉格朗日插值
void lagrange_interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type)
{
    double x_val = 0.0;
    double y_val = 0.0;

    if (data_type == DATA_TYPE_INT) { x_val = *(int *)x; }
    else if (data_type == DATA_TYPE_FLOAT) { x_val = *(float *)x; }
    else if (data_type == DATA_TYPE_DOUBLE) { x_val = *(double *)x; }

    for (int i = 0; i < table_size; i++)
    {
        double L = 1.0;

        for (int j = 0; j < table_size; j++)
        {
            if (i != j)
            {
                double xi = 0.0, xj = 0.0;

                if (data_type == DATA_TYPE_INT)
                {
                    xi = ((int *)x_table)[i];
                    xj = ((int *)x_table)[j];
                }
                else if (data_type == DATA_TYPE_FLOAT)
                {
                    xi = ((float *)x_table)[i];
                    xj = ((float *)x_table)[j];
                }
                else if (data_type == DATA_TYPE_DOUBLE)
                {
                    xi = ((double *)x_table)[i];
                    xj = ((double *)x_table)[j];
                }

                L *= (x_val - xj) / (xi - xj);
            }
        }

        if (data_type == DATA_TYPE_INT) { y_val += ((int *)y_table)[i] * L; }
        else if (data_type == DATA_TYPE_FLOAT) { y_val += ((float *)y_table)[i] * L; }
        else if (data_type == DATA_TYPE_DOUBLE) { y_val += ((double *)y_table)[i] * L; }
    }

    if (data_type == DATA_TYPE_INT) { *(int *)y = (int)y_val; }
    else if (data_type == DATA_TYPE_FLOAT) { *(float *)y = (float)y_val; }
    else if (data_type == DATA_TYPE_DOUBLE) { *(double *)y = y_val; }
}
// 埃尔米特插值
void hermite_interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type)
{
    double x_val = 0.0;
    double y_val = 0.0;

    if (data_type == DATA_TYPE_INT) { x_val = *(int *)x; }
    else if (data_type == DATA_TYPE_FLOAT) { x_val = *(float *)x; }
    else if (data_type == DATA_TYPE_DOUBLE) { x_val = *(double *)x; }

    // 找到包含 x_val 的区间
    int index = -1;
    for (int i = 0; i < table_size - 1; i++)
    {
        if (data_type == DATA_TYPE_INT)
        {
            if (x_val >= ((int *)x_table)[i] && x_val <= ((int *)x_table)[i + 1])
            {
                index = i;
                break;
            }
        }
        else if (data_type == DATA_TYPE_FLOAT)
        {
            if (x_val >= ((float *)x_table)[i] && x_val <= ((float *)x_table)[i + 1])
            {
                index = i;
                break;
            }
        }
        else if (data_type == DATA_TYPE_DOUBLE)
        {
            if (x_val >= ((double *)x_table)[i] && x_val <= ((double *)x_table)[i + 1])
            {
                index = i;
                break;
            }
        }
    }

    if (index < 0 || index >= table_size - 1)
    {
        // 如果 x_val 不在有效的插值区间，使用线性插值
        linear_interpolate(x, y, x_table, y_table, table_size, data_type);
        return;
    }

    // 获取两个点的坐标和导数
    double x0 = 0.0, x1 = 0.0;
    double y0 = 0.0, y1 = 0.0;
    double d0 = 0.0, d1 = 0.0;

    if (data_type == DATA_TYPE_INT)
    {
        x0 = ((int *)x_table)[index];
        x1 = ((int *)x_table)[index + 1];
        y0 = ((int *)y_table)[index];
        y1 = ((int *)y_table)[index + 1];
        // 假设导数已经提供
        d0 = ((double *)y_table)[index + table_size];
        d1 = ((double *)y_table)[index + 1 + table_size];
    }
    else if (data_type == DATA_TYPE_FLOAT)
    {
        x0 = ((float *)x_table)[index];
        x1 = ((float *)x_table)[index + 1];
        y0 = ((float *)y_table)[index];
        y1 = ((float *)y_table)[index + 1];
        // 假设导数已经提供
        d0 = ((double *)y_table)[index + table_size];
        d1 = ((double *)y_table)[index + 1 + table_size];
    }
    else if (data_type == DATA_TYPE_DOUBLE)
    {
        x0 = ((double *)x_table)[index];
        x1 = ((double *)x_table)[index + 1];
        y0 = ((double *)y_table)[index];
        y1 = ((double *)y_table)[index + 1];
        // 假设导数已经提供
        d0 = ((double *)y_table)[index + table_size];
        d1 = ((double *)y_table)[index + 1 + table_size];
    }

    // 计算埃尔米特插值
    double t  = (x_val - x0) / (x1 - x0);
    double t2 = t * t;
    double t3 = t2 * t;

    y_val = y0 * (2 * t3 - 3 * t2 + 1) + y1 * (-2 * t3 + 3 * t2) + d0 * (t3 - 2 * t2 + t) * (x1 - x0)
            + d1 * (t3 - t2) * (x1 - x0);

    if (data_type == DATA_TYPE_INT) { *(int *)y = (int)y_val; }
    else if (data_type == DATA_TYPE_FLOAT) { *(float *)y = (float)y_val; }
    else if (data_type == DATA_TYPE_DOUBLE) { *(double *)y = y_val; }
}

// 样条插值系数结构体
typedef struct
{
    double *a;
    double *b;
    double *c;
    double *d;
} SplineCoefficients;
// 计算样条插值系数
SplineCoefficients *calculate_spline_coefficients(const double *x_table, const double *y_table, int table_size)
{
    SplineCoefficients *coeff = (SplineCoefficients *)malloc(sizeof(SplineCoefficients));
    coeff->a                  = (double *)malloc(table_size * sizeof(double));
    coeff->b                  = (double *)malloc(table_size * sizeof(double));
    coeff->c                  = (double *)malloc(table_size * sizeof(double));
    coeff->d                  = (double *)malloc(table_size * sizeof(double));
    double *h                 = (double *)malloc((table_size - 1) * sizeof(double));
    double *alpha             = (double *)malloc(table_size * sizeof(double));
    double *l                 = (double *)malloc(table_size * sizeof(double));
    double *mu                = (double *)malloc(table_size * sizeof(double));
    double *z                 = (double *)malloc(table_size * sizeof(double));
    // 计算h[i] = x[i+1] - x[i]
    for (int i = 0; i < table_size - 1; i++) { h[i] = x_table[i + 1] - x_table[i]; }
    // 计算alpha[i]
    for (int i = 1; i < table_size - 1; i++)
    {
        alpha[i] = (3.0 / h[i]) * (y_table[i + 1] - y_table[i]) - (3.0 / h[i - 1]) * (y_table[i] - y_table[i - 1]);
    }
    // 自然边界条件：二阶导数为0
    l[0]  = 1.0;
    mu[0] = 0.0;
    z[0]  = 0.0;
    // 前向消元
    for (int i = 1; i < table_size - 1; i++)
    {
        l[i]  = 2.0 * (x_table[i + 1] - x_table[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i]  = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }
    // 自然边界条件：二阶导数为0
    l[table_size - 1]        = 1.0;
    z[table_size - 1]        = 0.0;
    coeff->c[table_size - 1] = 0.0;
    // 后向代入
    for (int j = table_size - 2; j >= 0; j--)
    {
        coeff->c[j] = z[j] - mu[j] * coeff->c[j + 1];
        coeff->b[j] = (y_table[j + 1] - y_table[j]) / h[j] - h[j] * (coeff->c[j + 1] + 2.0 * coeff->c[j]) / 3.0;
        coeff->d[j] = (coeff->c[j + 1] - coeff->c[j]) / (3.0 * h[j]);
        coeff->a[j] = y_table[j];
    }
    free(h);
    free(alpha);
    free(l);
    free(mu);
    free(z);
    return coeff;
}
// 样条插值函数
void spline_interpolate(const void *x, void *y, const void *x_table, const void *y_table, int table_size,
                        DataType data_type)
{
    if (data_type != DATA_TYPE_FLOAT && data_type != DATA_TYPE_DOUBLE)
    {
        printf("Unsupported data type for spline interpolation.\n");
        return;
    }
    SplineCoefficients *coeff = calculate_spline_coefficients((const double *)x_table, (const double *)y_table,
                                                              table_size);
    double x_val              = (data_type == DATA_TYPE_FLOAT) ? *(float *)x : *(double *)x;
    int i                     = 0;
    // 找到x所在的区间
    while (i < table_size - 1 && x_val > ((double *)x_table)[i + 1]) { i++; }
    // 计算插值结果
    double dx     = x_val - ((double *)x_table)[i];
    double result = coeff->a[i] + coeff->b[i] * dx + coeff->c[i] * dx * dx + coeff->d[i] * dx * dx * dx;
    if (data_type == DATA_TYPE_FLOAT) { *(float *)y = (float)result; }
    else { *(double *)y = result; }
    free(coeff->a);
    free(coeff->b);
    free(coeff->c);
    free(coeff->d);
    free(coeff);
}


// 插值函数接口
void interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type,
                 InterpolationType interp_type)
{
    switch (interp_type)
    {
    case INTERP_LINEAR: /*!< 线性插值 */
        linear_interpolate(x, y, x_table, y_table, table_size, data_type);
        break;
    case INTERP_NEAREST_NEIGHBOR: /*!< 临近插值 */
        nearest_neighbor_interpolate(x, y, x_table, y_table, table_size, data_type);
        break;
    case INTERP_CUBIC: /*!< 三次插值 */
        cubic_interpolate(x, y, x_table, y_table, table_size, data_type);
        break;
    case INTERP_LAGRANGE: /*!< 拉格朗日插值 */
        lagrange_interpolate(x, y, x_table, y_table, table_size, data_type);

        break;
    case INTERP_HERMITE: /*!< 埃尔米特插值 */
        hermite_interpolate(x, y, x_table, y_table, table_size, data_type);

        break;
    case INTERP_SPLINE: /*!< B样条插值 */
        spline_interpolate(x, y, x_table, y_table, table_size, data_type);
        break;
    }
}

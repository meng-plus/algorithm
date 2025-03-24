#include "interpolation.h"

#include "interpolation.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// ���Բ�ֵ
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
// �ٽ���ֵ
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
} // ���β�ֵ
void cubic_interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type)
{
    double x_val = 0.0;
    double y_val = 0.0;

    if (data_type == DATA_TYPE_INT) { x_val = *(int *)x; }
    else if (data_type == DATA_TYPE_FLOAT) { x_val = *(float *)x; }
    else if (data_type == DATA_TYPE_DOUBLE) { x_val = *(double *)x; }

    // �ҵ����� x_val ������
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

    if (index < 1 || index >= table_size - 2)
    {
        // ��� x_val ������Ч�Ĳ�ֵ���䣬ʹ�����Բ�ֵ
        linear_interpolate(x, y, x_table, y_table, table_size, data_type);
        return;
    }

    // ��ȡ�ĸ��������
    double x0 = 0.0, x1 = 0.0, x2 = 0.0, x3 = 0.0;
    double y0 = 0.0, y1 = 0.0, y2 = 0.0, y3 = 0.0;

    if (data_type == DATA_TYPE_INT)
    {
        x0 = ((int *)x_table)[index - 1];
        x1 = ((int *)x_table)[index];
        x2 = ((int *)x_table)[index + 1];
        x3 = ((int *)x_table)[index + 2];

        y0 = ((int *)y_table)[index - 1];
        y1 = ((int *)y_table)[index];
        y2 = ((int *)y_table)[index + 1];
        y3 = ((int *)y_table)[index + 2];
    }
    else if (data_type == DATA_TYPE_FLOAT)
    {
        x0 = ((float *)x_table)[index - 1];
        x1 = ((float *)x_table)[index];
        x2 = ((float *)x_table)[index + 1];
        x3 = ((float *)x_table)[index + 2];

        y0 = ((float *)y_table)[index - 1];
        y1 = ((float *)y_table)[index];
        y2 = ((float *)y_table)[index + 1];
        y3 = ((float *)y_table)[index + 2];
    }
    else if (data_type == DATA_TYPE_DOUBLE)
    {
        x0 = ((double *)x_table)[index - 1];
        x1 = ((double *)x_table)[index];
        x2 = ((double *)x_table)[index + 1];
        x3 = ((double *)x_table)[index + 2];

        y0 = ((double *)y_table)[index - 1];
        y1 = ((double *)y_table)[index];
        y2 = ((double *)y_table)[index + 1];
        y3 = ((double *)y_table)[index + 2];
    }

    // ���β�ֵ��ʽ
    double t  = (x_val - x1) / (x2 - x1);
    double t2 = t * t;
    double t3 = t2 * t;

    y_val = y1 * (2 * t3 - 3 * t2 + 1) + y2 * (-2 * t3 + 3 * t2) + y0 * (t3 - 2 * t2 + t) + y3 * (t3 - t2);

    if (data_type == DATA_TYPE_INT) { *(int *)y = (int)y_val; }
    else if (data_type == DATA_TYPE_FLOAT) { *(float *)y = (float)y_val; }
    else if (data_type == DATA_TYPE_DOUBLE) { *(double *)y = y_val; }
}
// �������ղ�ֵ
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
// �������ز�ֵ
void hermite_interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type)
{
    double x_val = 0.0;
    double y_val = 0.0;

    if (data_type == DATA_TYPE_INT) { x_val = *(int *)x; }
    else if (data_type == DATA_TYPE_FLOAT) { x_val = *(float *)x; }
    else if (data_type == DATA_TYPE_DOUBLE) { x_val = *(double *)x; }

    // �ҵ����� x_val ������
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
        // ��� x_val ������Ч�Ĳ�ֵ���䣬ʹ�����Բ�ֵ
        linear_interpolate(x, y, x_table, y_table, table_size, data_type);
        return;
    }

    // ��ȡ�����������͵���
    double x0 = 0.0, x1 = 0.0;
    double y0 = 0.0, y1 = 0.0;
    double d0 = 0.0, d1 = 0.0;

    if (data_type == DATA_TYPE_INT)
    {
        x0 = ((int *)x_table)[index];
        x1 = ((int *)x_table)[index + 1];
        y0 = ((int *)y_table)[index];
        y1 = ((int *)y_table)[index + 1];
        // ���赼���Ѿ��ṩ
        d0 = ((double *)y_table)[index + table_size];
        d1 = ((double *)y_table)[index + 1 + table_size];
    }
    else if (data_type == DATA_TYPE_FLOAT)
    {
        x0 = ((float *)x_table)[index];
        x1 = ((float *)x_table)[index + 1];
        y0 = ((float *)y_table)[index];
        y1 = ((float *)y_table)[index + 1];
        // ���赼���Ѿ��ṩ
        d0 = ((double *)y_table)[index + table_size];
        d1 = ((double *)y_table)[index + 1 + table_size];
    }
    else if (data_type == DATA_TYPE_DOUBLE)
    {
        x0 = ((double *)x_table)[index];
        x1 = ((double *)x_table)[index + 1];
        y0 = ((double *)y_table)[index];
        y1 = ((double *)y_table)[index + 1];
        // ���赼���Ѿ��ṩ
        d0 = ((double *)y_table)[index + table_size];
        d1 = ((double *)y_table)[index + 1 + table_size];
    }

    // ���㰣�����ز�ֵ
    double t  = (x_val - x0) / (x1 - x0);
    double t2 = t * t;
    double t3 = t2 * t;

    y_val = y0 * (2 * t3 - 3 * t2 + 1) + y1 * (-2 * t3 + 3 * t2) + d0 * (t3 - 2 * t2 + t) * (x1 - x0)
            + d1 * (t3 - t2) * (x1 - x0);

    if (data_type == DATA_TYPE_INT) { *(int *)y = (int)y_val; }
    else if (data_type == DATA_TYPE_FLOAT) { *(float *)y = (float)y_val; }
    else if (data_type == DATA_TYPE_DOUBLE) { *(double *)y = y_val; }
}
// B������ֵ
void bspline_interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type)
{
    double x_val = 0.0;
    double y_val = 0.0;

    if (data_type == DATA_TYPE_INT) { x_val = *(int *)x; }
    else if (data_type == DATA_TYPE_FLOAT) { x_val = *(float *)x; }
    else if (data_type == DATA_TYPE_DOUBLE) { x_val = *(double *)x; }

    // �ҵ����� x_val ������
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

    if (index < 1 || index >= table_size - 2)
    {
        // ��� x_val ������Ч�Ĳ�ֵ���䣬ʹ�����Բ�ֵ
        linear_interpolate(x, y, x_table, y_table, table_size, data_type);
        return;
    }

    // ��ȡ�ĸ��������
    double x0 = 0.0, x1 = 0.0, x2 = 0.0, x3 = 0.0;
    double y0 = 0.0, y1 = 0.0, y2 = 0.0, y3 = 0.0;

    if (data_type == DATA_TYPE_INT)
    {
        x0 = ((int *)x_table)[index - 1];
        x1 = ((int *)x_table)[index];
        x2 = ((int *)x_table)[index + 1];
        x3 = ((int *)x_table)[index + 2];

        y0 = ((int *)y_table)[index - 1];
        y1 = ((int *)y_table)[index];
        y2 = ((int *)y_table)[index + 1];
        y3 = ((int *)y_table)[index + 2];
    }
    else if (data_type == DATA_TYPE_FLOAT)
    {
        x0 = ((float *)x_table)[index - 1];
        x1 = ((float *)x_table)[index];
        x2 = ((float *)x_table)[index + 1];
        x3 = ((float *)x_table)[index + 2];

        y0 = ((float *)y_table)[index - 1];
        y1 = ((float *)y_table)[index];
        y2 = ((float *)y_table)[index + 1];
        y3 = ((float *)y_table)[index + 2];
    }
    else if (data_type == DATA_TYPE_DOUBLE)
    {
        x0 = ((double *)x_table)[index - 1];
        x1 = ((double *)x_table)[index];
        x2 = ((double *)x_table)[index + 1];
        x3 = ((double *)x_table)[index + 2];

        y0 = ((double *)y_table)[index - 1];
        y1 = ((double *)y_table)[index];
        y2 = ((double *)y_table)[index + 1];
        y3 = ((double *)y_table)[index + 2];
    }

    // ���� B ������ֵ
    double t  = (x_val - x1) / (x2 - x1);
    double t2 = t * t;
    double t3 = t2 * t;

    y_val = (1 - t) * (y1 + t * (y2 - y1)) + t * (y2 + (1 - t) * (y3 - y2));

    if (data_type == DATA_TYPE_INT) { *(int *)y = (int)y_val; }
    else if (data_type == DATA_TYPE_FLOAT) { *(float *)y = (float)y_val; }
    else if (data_type == DATA_TYPE_DOUBLE) { *(double *)y = y_val; }
}

// ��ֵ�����ӿ�
void interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type,
                 InterpolationType interp_type)
{
    switch (interp_type)
    {
    case INTERP_LINEAR: /*!< ���Բ�ֵ */
        linear_interpolate(x, y, x_table, y_table, table_size, data_type);
        break;
    case INTERP_NEAREST_NEIGHBOR: /*!< �ٽ���ֵ */
        nearest_neighbor_interpolate(x, y, x_table, y_table, table_size, data_type);
        break;
    case INTERP_CUBIC: /*!< ���β�ֵ */
        cubic_interpolate(x, y, x_table, y_table, table_size, data_type);
        break;
    case INTERP_LAGRANGE: /*!< �������ղ�ֵ */
        lagrange_interpolate(x, y, x_table, y_table, table_size, data_type);

        break;
    case INTERP_HERMITE: /*!< �������ز�ֵ */
        hermite_interpolate(x, y, x_table, y_table, table_size, data_type);

        break;
    case INTERP_BSPLINE: /*!< B������ֵ */
        bspline_interpolate(x, y, x_table, y_table, table_size, data_type);
        break;
    }
}

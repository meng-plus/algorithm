#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <stdint.h>

// ֧�ֵ���������
typedef enum
{
    DATA_TYPE_INT,
    DATA_TYPE_FLOAT,
    DATA_TYPE_DOUBLE
} DataType;

// ��ֵ�㷨����
typedef enum
{
    INTERP_LINEAR,           /*!< ���Բ�ֵ */
    INTERP_NEAREST_NEIGHBOR, /*!< �ٽ���ֵ */
    INTERP_CUBIC,            /*!< ���β�ֵ */
    INTERP_LAGRANGE,         /*!< �������ղ�ֵ */
    INTERP_HERMITE,          /*!< �������ز�ֵ */
    INTERP_BSPLINE           /*!< B������ֵ */
} InterpolationType;

/**
 * @brief  ��ֵ�����ӿ�
 *
 * @param x ����ֵ���Ա���
 * @param y ��ֵ���
 * @param x_table x��
 * @param y_table y��
 * @param table_size ���С
 * @param data_type ��������
 * @param interp_type ��ֵ�㷨����
 */
void interpolate(void *x, void *y, void *x_table, void *y_table, int table_size, DataType data_type,
                 InterpolationType interp_type);

#endif // INTERPOLATION_H

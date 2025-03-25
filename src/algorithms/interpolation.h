#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <stdint.h>
#include <stdbool.h>
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
    INTERP_SPLINE            /*!< B������ֵ ��������matlab ���г���  ont  suppose DATA_TYPE_INT*/
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
// ������ֵϵ���ṹ��
typedef struct
{
    double *a;
    double *b;
    double *c;
    double *d;
} SplineCoefficients;

/**
 * @brief ����ϵ���ṹ��
 *
 * @param table_size ����ֵ���ݳ���
 * @return
 */
SplineCoefficients *splinecoeff_create(int table_size);
void splinecoeff_destory(SplineCoefficients *coeff);
/**
 * @brief ������ֵ���� �����ֵϵ��
 *
 *
 * @param coeff  ������ֵϵ��
 * @param x_table  x��
 * @param y_table  y��
 * @param table_size ���С
 */
void calculate_spline_coefficients(SplineCoefficients *coeff, const void *x_table, const void *y_table, int table_size,
                                   DataType data_type);
/**
 * @brief �����ֵ���
 *
 * @param coeff  ������ֵϵ��
 * @param x_val  ����ֵ���Ա���
 * @param x_table x��
 * @param table_size ���С
 * @return
 */
double calculate_spline_result(SplineCoefficients *coeff, const void *x_val, const void *x_table, int table_size,
                               DataType data_type);

/**
 * @brief ����������ֵ���
 * ��������������ϲ���
 * @param x ����ֵ���Ա���
 * @param y ��ֵ���
 * @param x_table x��
 * @param y_table y��
 * @param table_size ���С
 * @return true ��ֵ�ɹ� false ��ֵʧ��
 */
bool spline_interpolate(const void *x, void *y, const void *x_table, const void *y_table, int table_size,
                        DataType data_type);
#endif // INTERPOLATION_H

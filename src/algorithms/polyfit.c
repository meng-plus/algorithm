#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RANK_ 3
/*
*********************************************************************************************************
*   函 数 名: polyfit
*   功能说明: 多项式曲线拟合（与matlab效果一致）
*   形    参: d_X	输入的数据的x值
			  d_Y	输入的数据的y值
			  d_N	输入的数据的个数
			  rank  多项式的次数
			  coeff 输出的系数
*   返 回 值: 无
*********************************************************************************************************
*/
//原理：At * A * C = At * Y	，其中 At 为 A 转置矩阵，C 为系数矩阵
void polyfit(double *d_X, double *d_Y, int d_N, int rank, double *coeff)
{
    if (RANK_ != rank) //判断次数是否合法
        return;

    int i, j, k;
    double aT_A[RANK_ + 1][RANK_ + 1] = {0};
    double aT_Y[RANK_ + 1]            = {0};


    for (i = 0; i < rank + 1; i++)     //行
    {
        for (j = 0; j < rank + 1; j++) //列
        {
            for (k = 0; k < d_N; k++)
            {
                aT_A[i][j] += pow(d_X[k], i + j); //At * A 线性矩阵
            }
        }
    }

    for (i = 0; i < rank + 1; i++)
    {
        for (k = 0; k < d_N; k++)
        {
            aT_Y[i] += pow(d_X[k], i) * d_Y[k]; //At * Y 线性矩阵
        }
    }

    //以下为高斯列主元素消去法解线性方程组
    for (k = 0; k < rank + 1 - 1; k++)
    {
        int row            = k;
        double mainElement = fabs(aT_A[k][k]);
        double temp        = 0.0;

        //找主元素
        for (i = k + 1; i < rank + 1 - 1; i++)
        {
            if (fabs(aT_A[i][i]) > mainElement)
            {
                mainElement = fabs(aT_A[i][i]);
                row         = i;
            }
        }

        //交换两行
        if (row != k)
        {
            for (i = 0; i < rank + 1; i++)
            {
                temp         = aT_A[k][i];
                aT_A[k][i]   = aT_A[row][i];
                aT_A[row][i] = temp;
            }
            temp      = aT_Y[k];
            aT_Y[k]   = aT_Y[row];
            aT_Y[row] = temp;
        }


        //消元过程
        for (i = k + 1; i < rank + 1; i++)
        {
            for (j = k + 1; j < rank + 1; j++) { aT_A[i][j] -= aT_A[k][j] * aT_A[i][k] / aT_A[k][k]; }
            aT_Y[i] -= aT_Y[k] * aT_A[i][k] / aT_A[k][k];
        }
    }

    //回代过程
    for (i = rank + 1 - 1; i >= 0; coeff[i] /= aT_A[i][i], i--)
    {
        for (j = i + 1, coeff[i] = aT_Y[i]; j < rank + 1; j++) { coeff[i] -= aT_A[i][j] * coeff[j]; }
    }

    return;
}

// 计算三次拟合曲线的极值点
void find_max_y_x(double coef[4], double x_min, double x_max, double *x_max_y, double *max_y)
{
    double a = 3 * coef[3];
    double b = 2 * coef[2];
    double c = coef[1];

    double x1, x2;
    double discriminant = b * b - 4 * a * c;

    *x_max_y = x_min;
    *max_y   = coef[3] * pow(x_min, 3) + coef[2] * pow(x_min, 2) + coef[1] * x_min + coef[0];

    if (discriminant >= 0)
    {
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);

        double candidates[] = {x_min, x_max, x1, x2};
        for (int i = 0; i < 4; i++)
        {
            if (candidates[i] >= x_min && candidates[i] <= x_max)
            {
                double y_val = coef[3] * pow(candidates[i], 3) + coef[2] * pow(candidates[i], 2)
                               + coef[1] * candidates[i] + coef[0];
                if (y_val > *max_y)
                {
                    *max_y   = y_val;
                    *x_max_y = candidates[i];
                }
            }
        }
    }
}
void linear_curve_fit(float *x, float *y, int size, float *slope, float *intercept)
{
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < size; i++)
    {
        sum_x  += x[i];
        sum_y  += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    *slope     = (size * sum_xy - sum_x * sum_y) / (size * sum_x2 - sum_x * sum_x);
    *intercept = (sum_y - *slope * sum_x) / size;
}
// 二次拟合函数
void quadratic_fit(float *x, float *y, int n, float *coeff)
{
    float sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
    float sum_y = 0, sum_xy = 0, sum_x2y = 0;

    for (int i = 0; i < n; i++)
    {
        float xi  = x[i];
        float yi  = y[i];
        sum_x    += xi;
        sum_x2   += xi * xi;
        sum_x3   += xi * xi * xi;
        sum_x4   += xi * xi * xi * xi;
        sum_y    += yi;
        sum_xy   += xi * yi;
        sum_x2y  += xi * xi * yi;
    }

    float A[3][3] = {
        {     n,  sum_x, sum_x2},
        { sum_x, sum_x2, sum_x3},
        {sum_x2, sum_x3, sum_x4}
    };

    float B[3] = {sum_y, sum_xy, sum_x2y};

    // 解线性方程组
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            float ratio = A[j][i] / A[i][i];
            for (int k = 0; k < 3; k++) { A[j][k] -= ratio * A[i][k]; }
            B[j] -= ratio * B[i];
        }
    }

    coeff[2] = B[2] / A[2][2];
    coeff[1] = (B[1] - A[1][2] * (coeff[2])) / A[1][1];
    coeff[0] = (B[0] - A[0][1] * (coeff[1]) - A[0][2] * coeff[2]) / A[0][0];
}

#include <stdio.h>
#include <stdlib.h>

// 二次拟合函数
void quadratic_fit(double *x, double *y, int n, double *a, double *b, double *c)
{
    double sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
    double sum_y = 0, sum_xy = 0, sum_x2y = 0;

    for (int i = 0; i < n; i++)
    {
        double xi = x[i];
        double yi = y[i];
        sum_x += xi;
        sum_x2 += xi * xi;
        sum_x3 += xi * xi * xi;
        sum_x4 += xi * xi * xi * xi;
        sum_y += yi;
        sum_xy += xi * yi;
        sum_x2y += xi * xi * yi;
    }

    double A[3][3] = {
        {n, sum_x, sum_x2},
        {sum_x, sum_x2, sum_x3},
        {sum_x2, sum_x3, sum_x4}};

    double B[3] = {sum_y, sum_xy, sum_x2y};

    // 解线性方程组
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            double ratio = A[j][i] / A[i][i];
            for (int k = 0; k < 3; k++)
            {
                A[j][k] -= ratio * A[i][k];
            }
            B[j] -= ratio * B[i];
        }
    }

    *c = B[2] / A[2][2];
    *b = (B[1] - A[1][2] * (*c)) / A[1][1];
    *a = (B[0] - A[0][1] * (*b) - A[0][2] * (*c)) / A[0][0];
}

#include <stdio.h>
#include <assert.h>
#include "algorithm.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_meanFilterFloat)
{
    float data[] = {1, 2, 3, 4, 5};
    ck_assert_int_eq(meanFilterFloat(data, 5), 3.0);
}
END_TEST

START_TEST(test_medianFilter)
{
    {
        int data[] = {1, 2, 3, 4, 5};
        ck_assert_int_eq(meanFilterint32(data, 5), 3.0);
    }
    float data[] = {21, 30, 15, 25, 35};
    float median = 0;
    medianFilter(data, 5, sizeof(float), &median, compareFloat);

    ck_assert_float_eq(median, 25);
}
END_TEST

// 测试初始化函数
START_TEST(test_kalman_filter_init)
{
    KalmanFilter kf;
    KalmanFilter_Init(&kf, 0.01, 0.1, 1, 0);

    ck_assert_float_eq(kf.Q, 0.01);
    ck_assert_float_eq(kf.R, 0.1);
    ck_assert_float_eq(kf.P, 1);
    ck_assert_float_eq(kf.x, 0);
    ck_assert_float_eq(kf.K, 0);
}
END_TEST

// 测试更新函数
START_TEST(test_kalman_filter_update)
{
    KalmanFilter kf;
    KalmanFilter_Init(&kf, 0.01, 0.1, 1, 0);

    float measurement    = 1.2;
    float filtered_value = KalmanFilter_Update(&kf, measurement);

    // 检查卡尔曼增益和状态估计值是否合理
    ck_assert(kf.K > 0 && kf.K < 1);
    ck_assert(filtered_value > 0 && filtered_value < measurement);
}
END_TEST

// 测试多次更新
START_TEST(test_kalman_filter_multiple_updates)
{
    KalmanFilter kf;
    KalmanFilter_Init(&kf, 0.01, 0.1, 1, 0);

    // 模拟含噪声的测量数据（真实值为 1.0）
    float measurements[] = {1.2, 0.9, 1.1, 0.8, 1.3, 1.1, 0.7, 1.4, 0.6, 1.5};
    int num_measurements = sizeof(measurements) / sizeof(measurements[0]);

    // 记录滤波后的值
    float filtered_values[num_measurements];

    // 更新卡尔曼滤波器
    for (int i = 0; i < num_measurements; i++)
    {
        filtered_values[i] = KalmanFilter_Update(&kf, measurements[i]);
        // printf("measurement: %f, filtered: %f\n", measurements[i], filtered_values[i]);
    }

    // 检查滤波后的值是否逐渐收敛到真实值（1.0）
    for (int i = 1; i < num_measurements; i++)
    {
        // 检查滤波后的值是否比原始测量值更接近真实值
        float measurement_error = fabs(measurements[i] - 1.0);
        float filtered_error    = fabs(filtered_values[i] - 1.0);
        // printf("measurement_error: %f, filtered_error: %f\n", measurement_error, filtered_error);
        ck_assert(filtered_error <= measurement_error);

        // 检查滤波后的值是否逐渐稳定
        if (i > 1)
        {
            float delta = fabs(filtered_values[i] - filtered_values[i - 1]);
            // printf("delta: %f\n", delta);
            ck_assert(delta < 0.2); // 确保滤波后的值变化不大
        }
    }

    // 检查最终滤波后的值是否接近真实值
    float final_error = fabs(filtered_values[num_measurements - 1] - 1.0);
    ck_assert(final_error < 0.2);
}
END_TEST
// 测试用例 1：简单的线性数据
START_TEST(test_linear_curve_fit_simple)
{
    float x[] = {1, 2, 3, 4, 5};
    float y[] = {2, 4, 6, 8, 10};
    int size  = sizeof(x) / sizeof(x[0]);
    float slope, intercept;
    linear_curve_fit(x, y, size, &slope, &intercept);
    // 预期结果：斜率为 2，截距为 0
    ck_assert_float_eq_tol(slope, 2.0f, 1e-6);
    ck_assert_float_eq_tol(intercept, 0.0f, 1e-6);
}
END_TEST
// 测试用例 2：带截距的线性数据
START_TEST(test_linear_curve_fit_intercept)
{
    float x[] = {1, 2, 3, 4, 5};
    float y[] = {3, 5, 7, 9, 11};
    int size  = sizeof(x) / sizeof(x[0]);
    float slope, intercept;
    linear_curve_fit(x, y, size, &slope, &intercept);
    // 预期结果：斜率为 2，截距为 1
    ck_assert_float_eq_tol(slope, 2.0f, 1e-6);
    ck_assert_float_eq_tol(intercept, 1.0f, 1e-6);
}
END_TEST
// 测试用例 3：随机数据
START_TEST(test_linear_curve_fit_random)
{
    float x[] = {0, 1, 2, 3, 4};
    float y[] = {1.1, 2.9, 4.2, 6.0, 7.8};
    int size  = sizeof(x) / sizeof(x[0]);
    float slope, intercept;
    linear_curve_fit(x, y, size, &slope, &intercept);
    // 预期结果：斜率接近 2，截距接近 1
    ck_assert_float_eq_tol(slope, 1.65f, 1e-2);
    ck_assert_float_eq_tol(intercept, 1.1f, 1e-2);
}
END_TEST
// 测试用例 1：简单的二次拟合
START_TEST(test_quadratic_fit_simple)
{
    float x[] = {0, 1, 2, 3, 4};
    float y[] = {1, 4, 9, 16, 25};
    int size  = sizeof(x) / sizeof(x[0]);
    float coeff[3];
    quadratic_fit(x, y, size, coeff);
    // 预期结果：y = p1+p2*x+p3*x^2
    ck_assert_float_eq_tol(coeff[2], 1.0f, 1e-6);
    ck_assert_float_eq_tol(coeff[1], 2.0f, 1e-6);
    ck_assert_float_eq_tol(coeff[0], 1.0f, 1e-6);
    // 计算R²
    float r2_float = r_square_float(x, y, 5, coeff, 2);
    ck_assert_float_eq_tol(r2_float, 1.0f, 1e-6);
}
END_TEST
// 测试用例 2：带线性项和常数的二次拟合
START_TEST(test_quadratic_fit_with_terms)
{
    float x[] = {0, 1, 2, 3, 4};
    float y[] = {2, 5, 12, 23, 38};
    int size  = sizeof(x) / sizeof(x[0]);
    float coeff[3];
    quadratic_fit(x, y, size, coeff);
    // 预期结果：y = p1+p2*x+p3*x^2
    ck_assert_float_eq_tol(coeff[2], 2.0f, 1e-6);
    ck_assert_float_eq_tol(coeff[1], 1.0f, 1e-6);
    ck_assert_float_eq_tol(coeff[0], 2.0f, 1e-6);
}
END_TEST
// 测试用例 3：随机数据的二次拟合
START_TEST(test_quadratic_fit_random)
{
    float x[] = {-2, -1, 0, 1, 2};
    float y[] = {8, -1, -6, -1, 8};
    int size  = sizeof(x) / sizeof(x[0]);
    float coeff[3];
    quadratic_fit(x, y, size, coeff);
    // 预期结果：y = p1+p2*x+p3*x^2
    ck_assert_double_eq_tol(coeff[2], 3.285714f, 1e-6);
    ck_assert_double_eq_tol(coeff[1], 0.0f, 1e-6);
    ck_assert_double_eq_tol(coeff[0], -4.971429f, 1e-6);
}
END_TEST

START_TEST(test_cubic_fit)
{
    double x[] = {108,     108.099,    108.198, 108.297, 108.396, 108.495, 108.595, 108.694, 108.793, 108.892, 108.991,
                  109.091, 109.19,     109.289, 109.388, 109.487, 109.586, 109.686, 109.785, 109.884, 109.983, 110.082,
                  110.182, 110.281,    110.38,  110.479, 110.578, 110.678, 110.777, 110.876, 110.975, 111.074, 111.173,
                  111.273, 111 - .372, 111.471, 111.57,  111.669, 111.769, 111.868, 111.967};
    double y[] = {315.689e-6, 264.934e-6, 279.018e-6, 345.008e-6, 358.117e-6, 377.427e-6, 442.797e-6,
                  406.923e-6, 414.009e-6, 473.356e-6, 498.069e-6, 521.719e-6, 496.297e-6, 523.136e-6,
                  513.747e-6, 583.9e-6,   616.497e-6, 600.73e-6,  579.737e-6, 606.133e-6, 614.105e-6,
                  633.149e-6, 630.58e-6,  631.82e-6,  645.816e-6, 672.92e-6,  658.748e-6, 637.932e-6,
                  622.874e-6, 648.65e-6,  665.037e-6, 621.545e-6, 591.429e-6, 616.939e-6, 635.718e-6,
                  560.339e-6, 577.346e-6, 581.597e-6, 576.283e-6, 570.082e-6, 542.623e-6};
    int n      = sizeof(x) / sizeof(x[0]);
    double coef[4];

    polyfit(x, y, n, 3, coef);
    // 计算R²
    float r2_float = r_square_double(x, y, n, coef, 3);
    ck_assert_double_eq_tol(r2_float, 0.961957f, 1e-6);
    // printf("拟合的三次多项式为: y = %.12fx^3 + %.12fx^2 + %.12fx + %.12f\n", coef[3], coef[2], coef[1], coef[0]);

    double x_max_y, max_y;
    find_max_y_x(coef, 105, 113, &x_max_y, &max_y);
    // printf("在范围 [105,113] 内, 最大 y 值为 %.5f 对应 x = %.5f\n", max_y, x_max_y);
    ck_assert_int_le(max_y, 0.00063);
    ck_assert_int_ge(max_y, 0.00057);
    ck_assert_int_le(x_max_y, 113);
    ck_assert_int_ge(x_max_y, 105);
}
END_TEST

START_TEST(test_bubbleSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST

START_TEST(test_bubbleSort_float)
{
    float arr[]      = {3.5, 1.2, 4.8, 1.1, 5.6, 9.0, 2.3, 6.7, 5.4, 3.9};
    float expected[] = {1.1, 1.2, 2.3, 3.5, 3.9, 4.8, 5.4, 5.6, 6.7, 9.0};
    int size         = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, size, sizeof(float), compareFloat);

    for (int i = 0; i < size; i++) { ck_assert_float_eq(arr[i], expected[i]); }
}
END_TEST
START_TEST(test_heapSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST


START_TEST(test_heapSort_float)
{
    float arr[]      = {3.5, 1.2, 4.8, 1.1, 5.6, 9.0, 2.3, 6.7, 5.4, 3.9};
    float expected[] = {1.1, 1.2, 2.3, 3.5, 3.9, 4.8, 5.4, 5.6, 6.7, 9.0};
    int size         = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, size, sizeof(float), compareFloat);

    for (int i = 0; i < size; i++) { ck_assert_float_eq(arr[i], expected[i]); }
}
END_TEST

START_TEST(test_selectionSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST
START_TEST(test_insertionSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST

START_TEST(test_insertionSort_float)
{
    float arr[]      = {3.5, 1.2, 4.8, 1.1, 5.6, 9.0, 2.3, 6.7, 5.4, 3.9};
    float expected[] = {1.1, 1.2, 2.3, 3.5, 3.9, 4.8, 5.4, 5.6, 6.7, 9.0};
    int size         = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, size, sizeof(float), compareFloat);

    for (int i = 0; i < size; i++) { ck_assert_float_eq(arr[i], expected[i]); }
}
END_TEST
START_TEST(test_shellSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    shellSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST

START_TEST(test_shellSort_float)
{
    float arr[]      = {3.5, 1.2, 4.8, 1.1, 5.6, 9.0, 2.3, 6.7, 5.4, 3.9};
    float expected[] = {1.1, 1.2, 2.3, 3.5, 3.9, 4.8, 5.4, 5.6, 6.7, 9.0};
    int size         = sizeof(arr) / sizeof(arr[0]);

    shellSort(arr, size, sizeof(float), compareFloat);

    for (int i = 0; i < size; i++) { ck_assert_float_eq(arr[i], expected[i]); }
}
END_TEST
START_TEST(test_mergeSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST

START_TEST(test_mergeSort_float)
{
    float arr[]      = {3.5, 1.2, 4.8, 1.1, 5.6, 9.0, 2.3, 6.7, 5.4, 3.9};
    float expected[] = {1.1, 1.2, 2.3, 3.5, 3.9, 4.8, 5.4, 5.6, 6.7, 9.0};
    int size         = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, size, sizeof(float), compareFloat);

    for (int i = 0; i < size; i++) { ck_assert_float_eq(arr[i], expected[i]); }
}
END_TEST
START_TEST(test_quickSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST

START_TEST(test_quickSort_float)
{
    float arr[]      = {3.5, 1.2, 4.8, 1.1, 5.6, 9.0, 2.3, 6.7, 5.4, 3.9};
    float expected[] = {1.1, 1.2, 2.3, 3.5, 3.9, 4.8, 5.4, 5.6, 6.7, 9.0};
    int size         = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, size, sizeof(float), compareFloat);

    for (int i = 0; i < size; i++) { ck_assert_float_eq(arr[i], expected[i]); }
}
END_TEST
START_TEST(test_countingSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    countingSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST

START_TEST(test_radixSort_int)
{
    int arr[]      = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int size       = sizeof(arr) / sizeof(arr[0]);

    radixSort(arr, size, sizeof(int), compareInt);

    for (int i = 0; i < size; i++) { ck_assert_int_eq(arr[i], expected[i]); }
}
END_TEST

// 测试线性插值
START_TEST(test_linear_interpolation)
{
    double x         = 1.5;
    double y         = 0.0;
    double x_table[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double y_table[] = {0.8415, 0.9093, 0.1411, -0.7568, -0.9589}; //sin(x)
    int table_size   = 5;

    interpolate(&x, &y, x_table, y_table, table_size, DATA_TYPE_DOUBLE, INTERP_LINEAR);
    ck_assert_double_eq_tol(y, 0.8754, 1e-6);
}
END_TEST

// 测试临近插值
START_TEST(test_nearest_neighbor_interpolation)
{
    double x         = 1.6;
    double y         = 0.0;
    double x_table[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double y_table[] = {0.8415, 0.9093, 0.1411, -0.7568, -0.9589}; //sin(x)
    int table_size   = 5;

    interpolate(&x, &y, x_table, y_table, table_size, DATA_TYPE_DOUBLE, INTERP_NEAREST_NEIGHBOR);
    ck_assert_double_eq_tol(y, 0.9093, 1e-6);
}
END_TEST

// 测试三次插值
START_TEST(test_cubic_interpolation)
{
    double x         = 2.6;
    double y         = 0.0;
    double x_table[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double y_table[] = {0.8415, 0.9093, 0.1411, -0.7568, -0.9589}; //sin(x)
    int table_size   = 5;

    interpolate(&x, &y, x_table, y_table, table_size, DATA_TYPE_DOUBLE, INTERP_CUBIC);
    ck_assert_double_eq_tol(y, 0.497846, 1e-6);
}
END_TEST

// 测试样条插值
START_TEST(test_spline_interpolation)
{
    double x         = 1.2;
    double y         = 0.0;
    double x_table[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double y_table[] = {0.8415, 0.9093, 0.1411, -0.7568, -0.9589}; //sin(x)
    int table_size   = 5;

    interpolate(&x, &y, x_table, y_table, table_size, DATA_TYPE_DOUBLE, INTERP_SPLINE);
    // 需要根据具体实现调整期望值
    ck_assert_double_eq_tol(y, 0.89389, 1e-6);
}
END_TEST
Suite *algorithms_suite(void)
{
    Suite *s;
    TCase *tc_mean;

    s = suite_create("algorithms");

    /* Core test case */
    tc_mean = tcase_create("mean");
    tcase_add_test(tc_mean, test_meanFilterFloat);
    tcase_add_test(tc_mean, test_medianFilter);
    tcase_add_test(tc_mean, test_kalman_filter_init);
    tcase_add_test(tc_mean, test_kalman_filter_update);
    tcase_add_test(tc_mean, test_kalman_filter_multiple_updates);
    suite_add_tcase(s, tc_mean);
    /* Core test case */
    TCase *tc_cubic_fit = tcase_create("cubic_fit");
    tcase_add_test(tc_cubic_fit, test_cubic_fit);
    tcase_add_test(tc_cubic_fit, test_linear_curve_fit_simple);
    tcase_add_test(tc_cubic_fit, test_linear_curve_fit_intercept);
    tcase_add_test(tc_cubic_fit, test_linear_curve_fit_random);
    tcase_add_test(tc_cubic_fit, test_quadratic_fit_simple);
    tcase_add_test(tc_cubic_fit, test_quadratic_fit_with_terms);
    tcase_add_test(tc_cubic_fit, test_quadratic_fit_random);

    suite_add_tcase(s, tc_cubic_fit);

    TCase *tc_sort = tcase_create("sort");
    tcase_add_test(tc_sort, test_bubbleSort_int);
    tcase_add_test(tc_sort, test_bubbleSort_float);
    tcase_add_test(tc_sort, test_heapSort_int);
    tcase_add_test(tc_sort, test_heapSort_float);
    tcase_add_test(tc_sort, test_insertionSort_int);
    tcase_add_test(tc_sort, test_insertionSort_float);
    tcase_add_test(tc_sort, test_shellSort_int);
    tcase_add_test(tc_sort, test_shellSort_float);
    tcase_add_test(tc_sort, test_mergeSort_int);
    tcase_add_test(tc_sort, test_mergeSort_float);
    tcase_add_test(tc_sort, test_quickSort_int);
    tcase_add_test(tc_sort, test_quickSort_float);
    tcase_add_test(tc_sort, test_selectionSort_int);
    tcase_add_test(tc_sort, test_countingSort_int);
    tcase_add_test(tc_sort, test_radixSort_int);
    suite_add_tcase(s, tc_sort);

    TCase *tc_interpolation = tcase_create("interpolation");
    tcase_add_test(tc_interpolation, test_linear_interpolation);
    tcase_add_test(tc_interpolation, test_nearest_neighbor_interpolation);
    tcase_add_test(tc_interpolation, test_cubic_interpolation);
    tcase_add_test(tc_interpolation, test_spline_interpolation);
    suite_add_tcase(s, tc_interpolation);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s  = algorithms_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

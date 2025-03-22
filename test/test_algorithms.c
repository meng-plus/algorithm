#include <stdio.h>
#include <assert.h>
#include "algorithm.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_mean_f)
{
    float data[] = {1, 2, 3, 4, 5};
    ck_assert_int_eq(mean_f(data, 5), 3.0);
}
END_TEST

START_TEST(test_mean_i)
{
    int data[] = {1, 2, 3, 4, 5};
    ck_assert_int_eq(mean_i(data, 5), 3.0);
}
END_TEST
START_TEST(test_cubic_fit)
{
    double x[] = {108,     108.099, 108.198, 108.297, 108.396, 108.495, 108.595, 108.694, 108.793, 108.892, 108.991,
                  109.091, 109.19,  109.289, 109.388, 109.487, 109.586, 109.686, 109.785, 109.884, 109.983, 110.082,
                  110.182, 110.281, 110.38,  110.479, 110.578, 110.678, 110.777, 110.876, 110.975, 111.074, 111.173,
                  111.273, 111.372, 111.471, 111.57,  111.669, 111.769, 111.868, 111.967};
    double y[] = {315.689e-6, 264.934e-6, 279.018e-6, 345.008e-6, 358.117e-6, 377.427e-6, 442.797e-6,
                  406.923e-6, 414.009e-6, 473.356e-6, 498.069e-6, 521.719e-6, 496.297e-6, 523.136e-6,
                  513.747e-6, 583.9e-6,   616.497e-6, 600.73e-6,  579.737e-6, 606.133e-6, 614.105e-6,
                  633.149e-6, 630.58e-6,  631.82e-6,  645.816e-6, 672.92e-6,  658.748e-6, 637.932e-6,
                  622.874e-6, 648.65e-6,  665.037e-6, 621.545e-6, 591.429e-6, 616.939e-6, 635.718e-6,
                  560.339e-6, 577.346e-6, 581.597e-6, 576.283e-6, 570.082e-6, 542.623e-6};
    int n      = sizeof(x) / sizeof(x[0]);
    double coef[4];

    polyfit(x, y, n, 3, coef);

    printf("拟合的三次多项式为: y = %.12fx^3 + %.12fx^2 + %.12fx + %.12f\n", coef[3], coef[2], coef[1], coef[0]);

    double x_max_y, max_y;
    find_max_y_x(coef, 105, 113, &x_max_y, &max_y);
    printf("在范围 [105,113] 内, 最大 y 值为 %.5f 对应 x = %.5f\n", max_y, x_max_y);
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

Suite *algorithms_suite(void)
{
    Suite *s;
    TCase *tc_mean;

    s = suite_create("algorithms");

    /* Core test case */
    tc_mean = tcase_create("mean");

    tcase_add_test(tc_mean, test_mean_i);
    tcase_add_test(tc_mean, test_mean_f);
    suite_add_tcase(s, tc_mean);
    /* Core test case */
    TCase *tc_cubic_fit = tcase_create("cubic_fit");
    tcase_add_test(tc_cubic_fit, test_cubic_fit);
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

#include <stdio.h>
#include <assert.h>
#include "algorithm_module.h"

void test_mean()
{
    int data[]   = {1, 2, 3, 4, 5};
    float result = mean_i(data, 5);
    printf("test_mean passed %f\n", result);
}

int main()
{
    test_mean();
    return 0;
}

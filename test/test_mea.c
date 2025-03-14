#include <stdio.h>
#include <assert.h>
#include "../src/algorithms/mean.h"

void test_mean()
{
    int data[] = {1, 2, 3, 4, 5};
    int result = mean(data, 5);
    assert(result == 3);
    printf("test_mean passed\n");
}

int main2()
{
    test_mean();
    return 0;
}

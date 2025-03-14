#include <stdio.h>
#include <assert.h>
#include "../src/algorithms/filter.h"

void test_sliding_window_filter()
{
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int output[9];
    sliding_window_filter(input, output, 9, 3);

    assert(output[0] == 2);
    assert(output[1] == 3);
    assert(output[2] == 4);
    assert(output[3] == 5);
    assert(output[4] == 6);
    assert(output[5] == 7);
    assert(output[6] == 8);
    printf("test_sliding_window_filter passed\n");
}

int main1()
{
    test_sliding_window_filter();
    return 0;
}

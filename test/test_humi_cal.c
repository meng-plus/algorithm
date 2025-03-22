#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "algorithm_module.h"
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s temp rh\n", argv[0]);
        return -1;
    }
    printf("argc:%d\n", argc);
    printf("argv[0]:%s\n", argv[0]);
    printf("argv[1]:%s\n", argv[1]);
    printf("argv[2]:%s\n", argv[2]);

    float temp = atof(argv[1]);
    float rh   = atof(argv[2]);
    printf("temp:%f, rh:%f\n", temp, rh);
    float wp   = GetWaterP(temp);
    float ww   = WaterW(rh, temp) * 1000;
    float ppmv = GetHumi_ppmv(temp, rh, 101.325);
    printf("temp:%f, rh:%f, wp:%f, ww:%f ppmv:%fppm\n", temp, rh, wp, ww, ppmv);
    return 0;
}

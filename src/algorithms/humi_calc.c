#include "humi_calc.h"
#include <math.h>
/**
 * @brief 换算水汽饱和蒸汽压
 *
 * @param temp 温度℃
 * @return float
 */
float GetWaterP(float temp)
{
    return exp(7.23 * 0.0000001 * pow(temp, 3) - 2.71 * 0.0001 * pow(temp, 2) + 7.2 * 0.01 * temp + 6.42);
}

/**
 * @brief 计算含湿量
 *
 * @param  rh 相对湿度
 * @param  wp 饱和蒸汽压
 * @return 单位 kg/m3
 */
float WaterW(float rh, float temp)
{
    float tmp;
    tmp = GetWaterP(temp); //得到该温度下的饱和水蒸气压
    return 622.0 * rh * 0.01 * tmp / (1000.0 * (101325 - rh * 0.01 * tmp));
}
/**
 * @brief 绝对湿度计算  ppmv = e * 1e6 / (press * 1000 - e)
 *
 * @param temp 环境温度
 * @param rh 相对湿度
 * @param press 大气压
 * @return float ppmv
 */
float GetHumi_ppmv(float temp, float rh, float press)
{
    float ew, e;
    ew = GetWaterP(temp); //得到当前温度下的饱和水蒸气压
    e  = ew * rh / 100.0;
    return (e * 1e6 / (press * 1000 - e));
}


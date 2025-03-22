/**
 * @file humi_cal.h
 * @brief 湿度计算库
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-22
 * @copyright Copyright (c) 2025  Zhengzhou GL. TECH Co.,Ltd
 *
 */

#ifndef __HUM_CALC_H_
#define __HUM_CALC_H_


/**
 * @brief 换算水汽饱和蒸汽压
 *
 * @param temp 温度℃
 * @return float
 */
float GetWaterP(float temp);
/**
 * @brief 计算含湿量
 *
 * @param rh
 * @param temp
 * @return float kg/m3
 */
float WaterW(float rh, float temp);
/**
 * @brief 绝对湿度计算  ppmv = e * 1e6 / (press * 1000 - e)
 *
 * @param temp 环境温度
 * @param rh 相对湿度
 * @param press 大气压
 * @return float ppmv
 */
float GetHumi_ppmv(float temp, float rh, float press);
#endif

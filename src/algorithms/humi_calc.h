/**
 * @file humi_cal.h
 * @brief ʪ�ȼ����
 * @author mengplus (chengmeng_2@outlook.com)
 * @version  0.1
 * @date 2025-03-22
 * @copyright Copyright (c) 2025  Zhengzhou GL. TECH Co.,Ltd
 *
 */

#ifndef __HUM_CALC_H_
#define __HUM_CALC_H_


/**
 * @brief ����ˮ����������ѹ
 *
 * @param temp �¶ȡ�
 * @return float
 */
float GetWaterP(float temp);
/**
 * @brief ���㺬ʪ��
 *
 * @param rh
 * @param temp
 * @return float kg/m3
 */
float WaterW(float rh, float temp);
/**
 * @brief ����ʪ�ȼ���  ppmv = e * 1e6 / (press * 1000 - e)
 *
 * @param temp �����¶�
 * @param rh ���ʪ��
 * @param press ����ѹ
 * @return float ppmv
 */
float GetHumi_ppmv(float temp, float rh, float press);
#endif

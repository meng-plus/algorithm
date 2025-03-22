#include "humi_calc.h"
#include <math.h>
/**
 * @brief ����ˮ����������ѹ
 *
 * @param temp �¶ȡ�
 * @return float
 */
float GetWaterP(float temp)
{
    return exp(7.23 * 0.0000001 * pow(temp, 3) - 2.71 * 0.0001 * pow(temp, 2) + 7.2 * 0.01 * temp + 6.42);
}

/**
 * @brief ���㺬ʪ��
 *
 * @param  rh ���ʪ��
 * @param  wp ��������ѹ
 * @return ��λ kg/m3
 */
float WaterW(float rh, float temp)
{
    float tmp;
    tmp = GetWaterP(temp); //�õ����¶��µı���ˮ����ѹ
    return 622.0 * rh * 0.01 * tmp / (1000.0 * (101325 - rh * 0.01 * tmp));
}
/**
 * @brief ����ʪ�ȼ���  ppmv = e * 1e6 / (press * 1000 - e)
 *
 * @param temp �����¶�
 * @param rh ���ʪ��
 * @param press ����ѹ
 * @return float ppmv
 */
float GetHumi_ppmv(float temp, float rh, float press)
{
    float ew, e;
    ew = GetWaterP(temp); //�õ���ǰ�¶��µı���ˮ����ѹ
    e  = ew * rh / 100.0;
    return (e * 1e6 / (press * 1000 - e));
}


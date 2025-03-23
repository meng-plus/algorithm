#include "kalman_filter.h"

// 初始化卡尔曼滤波器
void KalmanFilter_Init(KalmanFilter *kf, float Q, float R, float P, float initial_value)
{
    kf->Q = Q;
    kf->R = R;
    kf->P = P;
    kf->x = initial_value;
    kf->K = 0;
}

// 更新卡尔曼滤波器状态
float KalmanFilter_Update(KalmanFilter *kf, float measurement)
{
    // 预测步骤
    kf->P = kf->P + kf->Q; // 更新估计误差协方差

    // 更新步骤
    kf->K = kf->P / (kf->P + kf->R);               // 计算卡尔曼增益
    kf->x = kf->x + kf->K * (measurement - kf->x); // 更新状态估计值
    kf->P = (1 - kf->K) * kf->P;                   // 更新估计误差协方差

    return kf->x;                                  // 返回滤波后的状态估计值
}

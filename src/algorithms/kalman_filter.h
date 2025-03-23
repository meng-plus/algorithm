#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

typedef struct {
    float Q;  // 过程噪声协方差
    float R;  // 观测噪声协方差
    float P;  // 估计误差协方差
    float K;  // 卡尔曼增益
    float x;  // 状态估计值
} KalmanFilter;

// 初始化卡尔曼滤波器
void KalmanFilter_Init(KalmanFilter *kf, float Q, float R, float P, float initial_value);

// 更新卡尔曼滤波器状态
float KalmanFilter_Update(KalmanFilter *kf, float measurement);

#endif // KALMAN_FILTER_H

#ifndef  __F_MY_FUNCTION_H__
#define  __F_MY_FUNCTION_H__


void F_HAL_Delay_us(uint32_t us)
{
    uint32_t Delay = us * 168/4;
    do
    {
        __NOP();
    }
    while (Delay --);
}


//void F_HAL_Delay_us(uint16_t us)
//{
//	/*为防止因中断打断延时,造成计数错误
//	    如从0xfffE开始延时1us,但由于中断打断（此时计数器仍在计数）,本因计数至0xffff便停止计数
//	    但由于错过计数值.并重载arr值.导致实际延时(0xffff+1)us
//	 */
//	uint16_t differ=0xffff-us-5;
//	HAL_TIM_Base_Start(&htim7);
//	__HAL_TIM_SetCounter(&htim7,differ);
//	while(differ < 0xffff-5)
//	{
//		differ = __HAL_TIM_GetCounter(&htim7);
//	}
//	HAL_TIM_Base_Stop(&htim7);
//}


/*卡尔曼滤波*/
#define dt 0.0055
float KalmanFilter_Elect(float curr_elect_val,float last_elect_val)
{
    static float Q_curr = 1.0;//0.1           //Q增大，动态响应增大，过程噪声的协方差
    static float Q_last = 0.0001;         //过程噪声的协方差，过程噪声的协方差为一个一行两列矩阵
    static float R_elect = 10.0;                  //测量噪声的协方差 即测量偏差

    static float Pk[2][2] = { {1, 0}, {0, 1 }};

    static float Pdot[4] = {0,0,0,0};

    static float q_bias = 0.0;
    static float elect_err = 0.0;
    static float PCt_0 = 0.0;
    static float PCt_1 = 0.0;
    static float E = 0.0;
    static float K_0 = 0.0, K_1 = 0.0, t_0 = 0.0, t_1 = 0.0;

    Pdot[0] = Q_curr - Pk[0][1] - Pk[1][0];       //Pk-先验估计误差协方差的微分
    Pdot[1] = -Pk[1][1];
    Pdot[2] = -Pk[1][1];
    Pdot[3] = Q_last;

    Pk[0][0] += Pdot[0] * dt;             //Pk-先验估计误差的协方差微分的积分
    Pk[0][1] += Pdot[1] * dt;             //先验估计误差协方差
    Pk[1][0] += Pdot[2] * dt;
    Pk[1][1] += Pdot[3] * dt;

    elect_err = curr_elect_val - last_elect_val;          //偏差 = 测量值 - 预测值，先验估计

    PCt_0 = Pk[0][0];
    PCt_1 = Pk[1][0];

    E = R_elect + PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = Pk[0][1];

    Pk[0][0] -= K_0 * t_0;                    //后验估计误差协方差
    Pk[0][1] -= K_0 * t_1;
    Pk[1][0] -= K_1 * t_0;
    Pk[1][1] -= K_1 * t_1;

    curr_elect_val += K_0 * elect_err;                //后验估计 更新最优电磁值 最优电磁值 = 预测值 + 卡尔曼增益*(测量值-预测值)
    q_bias += K_1 * elect_err;                //后验估计 更新误差

    return curr_elect_val;
}


#endif












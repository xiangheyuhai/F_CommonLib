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

/*得到两个数的绝对值
 * */
u16 F_Abs(u16 x1,u16 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
}




/*卡尔曼滤波
 * */
#define dt 0.0055
float KalmanFilter_Elect(float curr_elect_val,float last_elect_val)
{
    static float Q_curr = 1.0;//0.1           //Q澧炲ぇ锛屽姩鎬佸搷搴斿澶э紝杩囩▼鍣０鐨勫崗鏂瑰樊
    static float Q_last = 0.0001;         //杩囩▼鍣０鐨勫崗鏂瑰樊锛岃繃绋嬪櫔澹扮殑鍗忔柟宸负涓�涓竴琛屼袱鍒楃煩闃�
    static float R_elect = 10.0;                  //娴嬮噺鍣０鐨勫崗鏂瑰樊 鍗虫祴閲忓亸宸�

    static float Pk[2][2] = { {1, 0}, {0, 1 }};

    static float Pdot[4] = {0,0,0,0};

    static float q_bias = 0.0;
    static float elect_err = 0.0;
    static float PCt_0 = 0.0;
    static float PCt_1 = 0.0;
    static float E = 0.0;
    static float K_0 = 0.0, K_1 = 0.0, t_0 = 0.0, t_1 = 0.0;

    Pdot[0] = Q_curr - Pk[0][1] - Pk[1][0];       //Pk-鍏堥獙浼拌璇樊鍗忔柟宸殑寰垎
    Pdot[1] = -Pk[1][1];
    Pdot[2] = -Pk[1][1];
    Pdot[3] = Q_last;

    Pk[0][0] += Pdot[0] * dt;             //Pk-鍏堥獙浼拌璇樊鐨勫崗鏂瑰樊寰垎鐨勭Н鍒�
    Pk[0][1] += Pdot[1] * dt;             //鍏堥獙浼拌璇樊鍗忔柟宸�
    Pk[1][0] += Pdot[2] * dt;
    Pk[1][1] += Pdot[3] * dt;

    elect_err = curr_elect_val - last_elect_val;          //鍋忓樊 = 娴嬮噺鍊� - 棰勬祴鍊硷紝鍏堥獙浼拌

    PCt_0 = Pk[0][0];
    PCt_1 = Pk[1][0];

    E = R_elect + PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = Pk[0][1];

    Pk[0][0] -= K_0 * t_0;                    //鍚庨獙浼拌璇樊鍗忔柟宸�
    Pk[0][1] -= K_0 * t_1;
    Pk[1][0] -= K_1 * t_0;
    Pk[1][1] -= K_1 * t_1;

    curr_elect_val += K_0 * elect_err;                //鍚庨獙浼拌 鏇存柊鏈�浼樼數纾佸�� 鏈�浼樼數纾佸�� = 棰勬祴鍊� + 鍗″皵鏇煎鐩�*(娴嬮噺鍊�-棰勬祴鍊�)
    q_bias += K_1 * elect_err;                //鍚庨獙浼拌 鏇存柊璇樊

    return curr_elect_val;
}


#endif












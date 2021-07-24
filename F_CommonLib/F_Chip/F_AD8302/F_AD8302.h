#ifndef __F_AD8302_H
#define __F_AD8302_H
#include "all_config.h"

#ifdef F_AD8302


int AD8302_Get_Phase(u16 adc_value, float phase_k, int phase_last);
float KalmanFilter_Elect(float curr_elect_val,float last_elect_val);
#endif
#endif

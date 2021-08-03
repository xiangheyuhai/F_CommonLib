#include "./F_AD8302.h"

#ifdef F_AD8302

/*
  * 相位校准  调试时先把相位设置为0°，再采集电压看是否为1.800v，若不是，在得到的数字量上加减AD8302_Ampli_Eror，使得到的数字量为2234或模拟量为1.800v
 * */
#define AD8302_Ampli_Eror -40


/*计算相位*/
/*
 *	u16 adc_value  此时的电压数字量
 *	float phase_k  斜率，正常时为-100.0
 *	int phase_last  上次的相位
 *
 * eg：FixedPhase_Differ = AD8302_Get_Phase(ADC_Value_Real[0],-100.0,FixedPhase_Differ_Last);
 *
 * */
int AD8302_Get_Phase(u16 adc_value, float phase_k, int phase_last)
{
	u16 tamp_adc = 0;
	float tamp_adc_ampli = 0;
	int phase_deiier = 0;
	tamp_adc = adc_value + AD8302_Ampli_Eror;
	tamp_adc_ampli = (float)tamp_adc*3.3/4096;
	phase_deiier = (int)(tamp_adc_ampli * phase_k + 180);/*计算得到相位*/
	phase_deiier = (int)KalmanFilter_Elect((float)phase_deiier, (float)phase_last);
	return phase_deiier;
}





#endif










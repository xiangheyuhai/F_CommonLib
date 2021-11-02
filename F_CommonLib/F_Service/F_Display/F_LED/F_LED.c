#include "F_LED.h"
#include "all_config.h"
#ifdef F_LED_Blink
#ifdef F_STM32_F4


void LED_Init(void)
{
	LED_Drv_Init();
}
#endif
#endif

#ifndef __F_SEG595_H
#define __F_SEG595_H
#include "all_config.h"
#ifdef Service_Display_SEG595



uint8_t SEG_DATA[4];




void SEG595_Display(uint8_t *data);
void SEG595_SendData(uint8_t data);
void SEG595_Init(void);

#endif
#endif


#ifndef __F_MB1504_H
#define __F_MB1504_H
#include "all_config.h"
#ifdef F_MB1504

unsigned long MB1504_Fre;


#define		F_Osc	12000000
#define		F_Step	10000


void MB1504_Init(void);
void MB1504_SetR(unsigned char P, unsigned long R);
void MB1504_SetNA(unsigned long N, unsigned char A);
void MB1504_SetF(unsigned char P, unsigned long f);



#endif
#endif

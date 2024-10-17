#ifndef __ADC_H__
#define __ADC_H__
#include "stm32f10x.h"                  // Device header

void adcInit();
uint16_t ADC1_Read(void);

#endif
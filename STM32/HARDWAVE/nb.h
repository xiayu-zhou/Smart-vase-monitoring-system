#ifndef __NB_H__
#define __NB_H__

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "spi.h"
#include "GPIO.h"
#include "usart.h"
#include "timer.h"
#include "str.h"
#include <string.h>

void Init_Nbiot(void);//³õÊ¼»¯NbiotÄ£¿é
bool Wait_Str1_Str2_x_100ms(char uartx,char and_or,char str_NO,char* str1,char* str2,unsigned char time_x_100ms);
void DealUpData(char *from,uint8_t *to,uint16_t len);

#endif
#ifndef __C485_H__
#define __C485_H__
#include "usart.h"
#include "delay.h"
#include "timer.h"
#include "lcd.h"
//��ʪ��
extern char Temp_value_str[6];
extern char Hum_value_str[5];
extern unsigned int Tem_value,Hum_value;
void readTemHum();

//������̼
extern unsigned int CO2_value;
extern char CO2_value_str[5];
void readCO2();

//һ����̼
extern unsigned int CO_value;
extern char CO_value_str[5];
void readCO();

//����
extern unsigned int O2_value;
extern char O2_value_str[5];
void readO2();

#endif
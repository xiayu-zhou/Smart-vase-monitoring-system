#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "spi.h"
#include "GPIO.h"
#include "usart.h"
#include "timer.h"
#include "nb.h"
#include "c485.h"
#include "str.h"
#include "pwm.h"
#include "adc.h"
#include "stdlib.h"    
#include <string.h>
#include "key.h"
char NBSendBuf[100];

void readTH()
{
	char T[3],H[3];
	char Tem[6];
	clearSting(T,3,'0');
	clearSting(H,3,'0');
	readTemHum();
	int_to_hex(Tem_value/10,T,2);
	int_to_hex(Hum_value/10,H,2);
	copy_str(Tem,T,2);
	copy_str(&Tem[2],H,2);
	Tem[4] = 0;
	USART1TxStr(Temp_value_str);
	USART1TxStr(Hum_value_str);
	nbSendData(NBSendBuf,10,Tem);
	USART1TxStr("\r\n");
	USART1TxStr(NBSendBuf);
	USART2TxStr(NBSendBuf);
	delay_ms(6000);
}

void readCO2_m()
{
	char temp[5];
	clearSting(temp,4,'0');
	readCO2();
	int_to_hex(CO2_value,temp,4);
	temp[4] = 0;
	nbSendData(NBSendBuf,11,temp);
	USART1TxStr(CO2_value_str);
	USART1TxStr("\r\n");
	USART1TxStr(NBSendBuf);
	USART2TxStr(NBSendBuf);
	delay_ms(6000);
}

void readCO_m()
{
	char temp[5];
	clearSting(temp,4,'0');
	readCO();
	int_to_hex(CO_value,temp,4);
	temp[4] = 0;
	nbSendData(NBSendBuf,12,temp);
	USART1TxStr(CO_value_str);
	USART1TxStr("\r\n");
	USART1TxStr(NBSendBuf);
	USART2TxStr(NBSendBuf);
	delay_ms(6000);
}

void readO2_m()
{
	char temp[3];
	clearSting(temp,2,'0');
	readO2();
	int_to_hex(O2_value/10,temp,2);
	temp[2] = 0;
	nbSendData(NBSendBuf,13,temp);
	USART1TxStr(O2_value_str);
	USART1TxStr("\r\n");
	USART1TxStr(NBSendBuf);
	USART2TxStr(NBSendBuf);	
	delay_ms(6000);
}

//虚拟数据随机生成
void readO()
{
	char shuiwei[3];
	char turangshidu[3];
	char turanghanO2[3];
	char jiawan[9];
	char Tem[15];
	int a;
	char str[9];
	uint16_t adc_value;
	clearSting(shuiwei,2,'0');
	clearSting(turangshidu,2,'0');
	clearSting(turanghanO2,2,'0');
	clearSting(jiawan,8,'0');
	//adc_value = ADC1_Read();
	//adc_value = ADC1_Read();
	//srand(adc_value);
	srand(timer3);
	a = rand()%60000;
	
	int_to_hex(a%10,shuiwei,2);
	int_to_hex(a%100,turangshidu,2);
	int_to_hex(a*3/10%100,turanghanO2,2);
	int_to_hex(a,jiawan,8);
	
	sprintf(str,"%d",a%10);
	LCD_Show_Chinese16x16(10,116,"水位：");
	LCD_ShowString(60,116,str);
	
	sprintf(str,"%d",a%100);
	LCD_Show_Chinese16x16(10,137,"土壤湿度：");
	LCD_ShowString(92,137,str);
	
	sprintf(str,"%d",a*3/10%100);
	LCD_Show_Chinese16x16(10,158,"土壤含氧量：");
	LCD_ShowString(110,158,str);

	sprintf(str,"%d",a);
	LCD_Show_Chinese16x16(10,179,"甲烷：");
	LCD_ShowString(60,179,str);
	
	shuiwei[2] = 0;
	turangshidu[2] = 0;
	turanghanO2[2] = 0;
	jiawan[8] = 0;
//	USART1TxStr(shuiwei);
//	USART1TxStr("\r\n");
//	USART1TxStr(turangshidu);
//	USART1TxStr("\r\n");
//	USART1TxStr(turanghanO2);
//	USART1TxStr("\r\n");
//	USART1TxStr(jiawan);
//	USART1TxStr("\r\n");
	copy_str(Tem,turanghanO2,2);	
	copy_str(&Tem[2],turangshidu,2);
	copy_str(&Tem[4],shuiwei,2);
	copy_str(&Tem[6],jiawan,8);
	Tem[14] = 0;
	nbSendData(NBSendBuf,18,Tem);
	USART1TxStr(Tem);
	USART1TxStr("\r\n");
	USART2TxStr(NBSendBuf);
	delay_ms(6000);
}

void Init()
{
	GPIO_Configuration();//GPIO初始化
	//delay_init();	    	 		//延时函数初始化	
	Usart1_Init(115200);					//传感器透传
	Usart2_Init(115200);			  //连接NBIOT	
	Usart3_Init(9600);				//连接485传感器
	Uart5_Init(115200);
	TIM3_Int_Init(999,7199);	//开启定时器3，计数100ms	
	Lcd_Init();					//初始化LCD	
	PWM_Init();
	KEY_EXTIX_Init();
	LCD_Clear(BLACK); //清屏 ,这是真正的屏幕背景色	
	POINT_COLOR=GREEN;
	POINT_COLOR=WHITE;	//画笔为白色
	LCD_Show_Chinese16x16(100,0,"课设"); //显示中文字符串
	NB_PWR_ON();			//NB模块上电
	Sensor_PWR_ON(); //传感器供电
	Init_Nbiot();
	//adcInit();
	LCD_Show_Chinese16x16(80,0,"物联网课设智能花盆"); //显示中文字符串
	
	LCD_Show_Chinese16x16(40,200,"当前传感器：");
	
	LCD_Show_Chinese16x16(140,200,"无");
}



int main()
{
	Init();
	while(1)
	{
		if(KEY_value == 1)
		{
			readTH();
		}
		else if(KEY_value == 2)
		{
			readCO_m();
		}
		else if(KEY_value == 3)
		{
			readO2_m();
		}
		else if(KEY_value == 4)
		{
			readCO2_m();
		}
		else if(KEY_value == 5)
		{
			readTH();
			readCO_m();    
			readO2_m();
			readCO2_m();
		}
		USART1TxChar(KEY_value+48);
		//readTH();
		//readCO_m();                                                              
		//readO2_m();
		//readCO2_m();
		USART1TxStr("123");
		readO();
		//delay_ms(6000);
	}
}
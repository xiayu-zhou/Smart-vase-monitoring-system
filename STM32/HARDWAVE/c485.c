
#include "c485.h"

//温湿度
unsigned char Read_Humiture_CMD[8]								={0x01,0x03,0x00,0x00,0x00,0x02,0xC4,0x0B};//读取温湿度数据的命令
unsigned int Tem_value = 0,Hum_value = 0;
char Temp_value_str[6];
char Hum_value_str[5];
int Tem_value_int = 0;

//二氧化碳
unsigned char Read_CO2_CMD[8]											={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};//读取二氧化碳数据的命令
unsigned int CO2_value = 0;
char CO2_value_str[5];

//一氧化碳
unsigned char Read_CO_CMD[8]											={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};//读取一氧化碳数据的命令
unsigned int CO_value = 0;
char CO_value_str[5];

//氧气
unsigned char Read_O2_CMD[8]         		 					={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};//读取氧气数据的命令
unsigned int O2_value = 0;
char O2_value_str[5];

void readTemHum()
{
	USART3TxData_hex(Read_Humiture_CMD,8);//发送采集温湿度传感器数据的命令  	
	delay_ms(1500);
	if((Flag_Usart3_Receive) && (!Count_Timer3_value_USART3_receive_timeout))//串口3（485）接收到数据且未超时
	{
		Flag_Usart3_Receive = 0;
		//01 03 04 01 1B 02 7C 8B 49 
		//提取已经获取到的温湿度数据
		Tem_value = USART3_RX_BUF[3];
		Tem_value <<= 8;
		Tem_value |= USART3_RX_BUF[4];
		Hum_value = USART3_RX_BUF[5];
		Hum_value <<= 8;
		Hum_value |= USART3_RX_BUF[6];
		CLR_Buf3();
		Tem_value_int = Tem_value;//将数据赋给有符号变量，方便判断正负值
		if(Tem_value_int > 0)
		{		
			Temp_value_str[0]	= '+';
			Temp_value_str[1]	=	(char)(Tem_value / 100 + '0');
			Temp_value_str[2]	=	(char)(Tem_value % 100 / 10 + '0');
			Temp_value_str[3]	=	'.';
			Temp_value_str[4]	=	(char)(Tem_value % 10 + '0');
		}
		if(Tem_value_int < 0)//如果是零下温度
		{
			Tem_value = (~Tem_value)+1;//取反加1转成正数方便运算
			Temp_value_str[0]	= '-';
			Temp_value_str[1]	=	(char)(Tem_value / 100 + '0');
			Temp_value_str[2]	=	(char)(Tem_value % 100 / 10 + '0');
			Temp_value_str[3]	=	'.';
			Temp_value_str[4]	=	(char)(Tem_value % 10 + '0');
		}
		Temp_value_str[5]	=	0;

		Hum_value_str[0]	=	(char)(Hum_value / 100 + '0');
		Hum_value_str[1]	=	(char)(Hum_value % 100 / 10 + '0');
		Hum_value_str[2]	=	'.';
		Hum_value_str[3]	=	(char)(Hum_value % 10 + '0');
		Hum_value_str[4]  =	0;
	}
	else
	{
		Temp_value_str[0] = 0;
		Hum_value_str[0]  =	0;
	}
	LCD_Show_Chinese16x16(10,32,"温度：");
	LCD_ShowString(60,32,Temp_value_str);
	LCD_Show_Chinese16x16(170,32,"湿度：");
	LCD_ShowString(220,32,Hum_value_str);
	CLR_Buf2();	
}

void readCO2()
{
	USART3TxData_hex(Read_CO2_CMD,8);//发送采CO2传感器数据的命令  	
	delay_ms(1500);
	if((Flag_Usart3_Receive) && (!Count_Timer3_value_USART3_receive_timeout))//串口3（485）接收到数据且未超时
	{
		Flag_Usart3_Receive = 0;
		//01 03 02 00 29 79 9A
		//提取已经获取到的CO2数据
		CO2_value = USART3_RX_BUF[3];
		CO2_value <<= 8;
		CO2_value |= USART3_RX_BUF[4];
		CLR_Buf3();
		CO2_value_str[0]	=	(char)(CO2_value / 1000 + '0');
		CO2_value_str[1]	=	(char)(CO2_value % 1000/ 100 + '0');
		CO2_value_str[2]	=(char)(CO2_value % 100/ 10 + '0');
		CO2_value_str[3]	=	(char)(CO2_value % 10 + '0');
		CO2_value_str[4]  =	0;
	}
	else
	{
		CO2_value_str[0]  = 0;
	}
		//LCD显示CO2浓度数据
	LCD_Show_Chinese16x16(10,53,"二氧化碳：");
	LCD_ShowString(90,53,CO2_value_str);
	CLR_Buf2();	
}

void readCO()
{
	USART3TxData_hex(Read_CO_CMD,8);//发送采CO传感器数据的命令  	
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	if((Flag_Usart3_Receive) && (!Count_Timer3_value_USART3_receive_timeout))//串口3（485）接收到数据且未超时
	{
		Flag_Usart3_Receive = 0;
		//01 03 02 00 29 79 9A
		//提取已经获取到的CO数据
		CO_value = USART3_RX_BUF[3];
		CO_value <<= 8;
		CO_value |= USART3_RX_BUF[4];
		CLR_Buf3();
		CO_value_str[0]	=	(char)(CO_value / 1000 + '0');
		CO_value_str[1]	=	(char)(CO_value % 1000/ 100 + '0');
		CO_value_str[2]	=(char)(CO_value % 100/ 10 + '0');
		CO_value_str[3]	=	(char)(CO_value % 10 + '0');
		CO_value_str[4] = 0;
	}
	else
	{
		CO_value_str[1] = 0;
	}
	//LCD显示CO浓度数据
	LCD_Show_Chinese16x16(10,74,"一氧化碳：");
	LCD_ShowString(90,74,CO_value_str);
	CLR_Buf2();	
}

void readO2()
{
	USART3TxData_hex(Read_O2_CMD,8); //发送采集氧气传感器数据的命令
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);		
	if((Flag_Usart3_Receive)&&(!Count_Timer3_value_USART3_receive_timeout)) //串口3（485）接收到数据且未超时
	{
		Flag_Usart3_Receive = 0;
		//01 03 02 00 AE 39 F8 
		//提取已经获取到的氧气浓度数据
		O2_value = USART3_RX_BUF[3];
		O2_value <<= 8;
		O2_value |= USART3_RX_BUF[4];
		CLR_Buf3();
		O2_value_str[0] = (char )(O2_value / 100 + '0');
		O2_value_str[1] = (char )(O2_value % 100/10 + '0');
		O2_value_str[2] = '.';
		O2_value_str[3] = (char )(O2_value % 10 + '0');
		O2_value_str[4] = 0;
	}
	else
	{
		O2_value_str[1] = 0;
	}
	//LCD显示氧气浓度数据
	LCD_Show_Chinese16x16(10,95,"氧气：");	
	LCD_ShowString(60,95,O2_value_str);
}
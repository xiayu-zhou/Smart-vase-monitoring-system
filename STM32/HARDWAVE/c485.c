
#include "c485.h"

//��ʪ��
unsigned char Read_Humiture_CMD[8]								={0x01,0x03,0x00,0x00,0x00,0x02,0xC4,0x0B};//��ȡ��ʪ�����ݵ�����
unsigned int Tem_value = 0,Hum_value = 0;
char Temp_value_str[6];
char Hum_value_str[5];
int Tem_value_int = 0;

//������̼
unsigned char Read_CO2_CMD[8]											={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};//��ȡ������̼���ݵ�����
unsigned int CO2_value = 0;
char CO2_value_str[5];

//һ����̼
unsigned char Read_CO_CMD[8]											={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};//��ȡһ����̼���ݵ�����
unsigned int CO_value = 0;
char CO_value_str[5];

//����
unsigned char Read_O2_CMD[8]         		 					={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};//��ȡ�������ݵ�����
unsigned int O2_value = 0;
char O2_value_str[5];

void readTemHum()
{
	USART3TxData_hex(Read_Humiture_CMD,8);//���Ͳɼ���ʪ�ȴ��������ݵ�����  	
	delay_ms(1500);
	if((Flag_Usart3_Receive) && (!Count_Timer3_value_USART3_receive_timeout))//����3��485�����յ�������δ��ʱ
	{
		Flag_Usart3_Receive = 0;
		//01 03 04 01 1B 02 7C 8B 49 
		//��ȡ�Ѿ���ȡ������ʪ������
		Tem_value = USART3_RX_BUF[3];
		Tem_value <<= 8;
		Tem_value |= USART3_RX_BUF[4];
		Hum_value = USART3_RX_BUF[5];
		Hum_value <<= 8;
		Hum_value |= USART3_RX_BUF[6];
		CLR_Buf3();
		Tem_value_int = Tem_value;//�����ݸ����з��ű����������ж�����ֵ
		if(Tem_value_int > 0)
		{		
			Temp_value_str[0]	= '+';
			Temp_value_str[1]	=	(char)(Tem_value / 100 + '0');
			Temp_value_str[2]	=	(char)(Tem_value % 100 / 10 + '0');
			Temp_value_str[3]	=	'.';
			Temp_value_str[4]	=	(char)(Tem_value % 10 + '0');
		}
		if(Tem_value_int < 0)//����������¶�
		{
			Tem_value = (~Tem_value)+1;//ȡ����1ת��������������
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
	LCD_Show_Chinese16x16(10,32,"�¶ȣ�");
	LCD_ShowString(60,32,Temp_value_str);
	LCD_Show_Chinese16x16(170,32,"ʪ�ȣ�");
	LCD_ShowString(220,32,Hum_value_str);
	CLR_Buf2();	
}

void readCO2()
{
	USART3TxData_hex(Read_CO2_CMD,8);//���Ͳ�CO2���������ݵ�����  	
	delay_ms(1500);
	if((Flag_Usart3_Receive) && (!Count_Timer3_value_USART3_receive_timeout))//����3��485�����յ�������δ��ʱ
	{
		Flag_Usart3_Receive = 0;
		//01 03 02 00 29 79 9A
		//��ȡ�Ѿ���ȡ����CO2����
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
		//LCD��ʾCO2Ũ������
	LCD_Show_Chinese16x16(10,53,"������̼��");
	LCD_ShowString(90,53,CO2_value_str);
	CLR_Buf2();	
}

void readCO()
{
	USART3TxData_hex(Read_CO_CMD,8);//���Ͳ�CO���������ݵ�����  	
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	if((Flag_Usart3_Receive) && (!Count_Timer3_value_USART3_receive_timeout))//����3��485�����յ�������δ��ʱ
	{
		Flag_Usart3_Receive = 0;
		//01 03 02 00 29 79 9A
		//��ȡ�Ѿ���ȡ����CO����
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
	//LCD��ʾCOŨ������
	LCD_Show_Chinese16x16(10,74,"һ����̼��");
	LCD_ShowString(90,74,CO_value_str);
	CLR_Buf2();	
}

void readO2()
{
	USART3TxData_hex(Read_O2_CMD,8); //���Ͳɼ��������������ݵ�����
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);		
	if((Flag_Usart3_Receive)&&(!Count_Timer3_value_USART3_receive_timeout)) //����3��485�����յ�������δ��ʱ
	{
		Flag_Usart3_Receive = 0;
		//01 03 02 00 AE 39 F8 
		//��ȡ�Ѿ���ȡ��������Ũ������
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
	//LCD��ʾ����Ũ������
	LCD_Show_Chinese16x16(10,95,"������");	
	LCD_ShowString(60,95,O2_value_str);
}
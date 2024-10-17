
#include "key.h"
#include "lcd.h"
#include "usart.h"
#include "delay.h"

#define KEY1 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)

unsigned char KEY_value = 0;

void KEY_Init(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void KEY_EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	KEY_Init();	 //	�����˿ڳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	//�ж����Լ��жϳ�ʼ������ �½��ش���
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


	//GPIOA.6	  �ж����Լ��жϳ�ʼ������  �½��ش���	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		//ʹ�ܰ���KEY���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//��ռ���ȼ�Ϊ���� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;					//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI9_5_IRQHandler(void)//�ⲿ�ж�5��6��7������� 
{	
	if(KEY1 == 0)
	{
		if(KEY_value < 5)
			KEY_value++;
		else 
			KEY_value = 0;
		if(KEY_value == 0)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"��");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 1)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"��ʪ��");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 2)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"һ����̼");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 3)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"����");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 4)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"������̼");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 5)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"ȫ�� ");
			POINT_COLOR=WHITE;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line6); //���LINE6�ϵ��жϱ�־λ
}


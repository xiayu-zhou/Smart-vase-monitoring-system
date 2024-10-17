
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
	KEY_Init();	 //	按键端口初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	//中断线以及中断初始化配置 下降沿触发
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


	//GPIOA.6	  中断线以及中断初始化配置  下降沿触发	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		//使能按键KEY所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//抢占优先级为第四 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;					//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI9_5_IRQHandler(void)//外部中断5，6，7服务程序 
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
			LCD_Show_Chinese16x16(140,200,"无");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 1)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"温湿度");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 2)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"一氧化碳");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 3)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"氧气");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 4)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"二氧化碳");
			POINT_COLOR=WHITE;
		}
		else if(KEY_value == 5)
		{
			POINT_COLOR=RED;
			LCD_ShowString(140,200,"        ");
			LCD_Show_Chinese16x16(140,200,"全部 ");
			POINT_COLOR=WHITE;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE6上的中断标志位
}


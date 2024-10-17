#include "gpio.h"
 
void GPIO_Configuration(void)//GPIO初始化
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	/*初始化结构体*/   
	GPIO_StructInit(&GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PA端口时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PC端口时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//使能PC端口时钟 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通推挽输出 
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA.1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通推挽输出 
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA.4，控制NB模块开关
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通推挽输出 
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB.5，控制传感器开关
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通推挽输出 
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //初始化PC.13，控制红色R_LED
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通推挽输出 
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //初始化PC.14，控制绿色G_LED
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通推挽输出 
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //初始化PC.15，控制黄色Y_LED
	
	R_LED_OFF;	
	G_LED_OFF;
	Y_LED_OFF;
}

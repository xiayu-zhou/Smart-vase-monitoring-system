#include "sys.h"
#include "usart.h"
#include "GPIO.h"
#include "stdbool.h"
#include "pwm.h"
#include "gpio.h"
#if SYSTEM_SUPPORT_OS
#include "includes.h"					 
#endif
char USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
unsigned char USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
unsigned char USART3_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
char USART3GetCmd[150];

u16 USART1_RX_STA=0;       //����״̬���	  
u16 USART2_RX_STA=0;       //����״̬���
u16 USART3_RX_STA=0;       //����״̬��� 

unsigned char Count_Timer3_value_USART1_receive_timeout = 0;
unsigned char Count_Timer3_value_USART2_receive_timeout = 0;
unsigned char Count_Timer3_value_USART3_receive_timeout = 0;

bool  Flag_Usart1_Receive;
bool  Flag_Usart1_Remap_Receive;
bool  Flag_Usart2_Receive;
bool  Flag_Usart3_Receive;
bool  Flag_Usart1_Remap;
bool  Flag_Usart3_Remap;
bool  Flag_Usart3_Receive_Complete;
bool  Flag_usart1_receive_OK = 0;
bool 	Flag_usart1_receive_T = 0;
bool 	Flag_usart2_receive_T = 0;

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void Usart1_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ��
    GPIO_PinRemapConfig(GPIO_Remap_USART1,DISABLE);//��ӳ��ر�	
	//USART1_TX   PA.9��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
	
  //Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;	//һ������Ϊ9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1,&USART_InitStructure);	//��ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//�����ж�
	USART_Cmd(USART1, ENABLE);	//ʹ�ܴ���

}

void Usart1_Remap_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ��
  GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

	//USART1_TX   PB.6��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PB.6
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.6
   
  //USART1_RX	  GPIOB.7��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PB7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOAB.7  

  //Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;	//һ������Ϊ9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1,&USART_InitStructure);	//��ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//�����ж�
	USART_Cmd(USART1, ENABLE);	//ʹ�ܴ���

}

/* USART1����һ���ַ� */ 
void USART1TxChar(char ch)
{
	USART_SendData(USART1,(u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	{}

}

/* USART1����һ���������ݣ�ʮ�����ƣ� */
void USART1TxData(unsigned char *pt)
{
	while(*pt != '\0')
	{
		USART1TxChar(*pt);
		pt++;
	}
}

void USART1TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    USART1TxChar(*pt);
    pt++;
    len --; 
  }
}

/* USART1����һ���ַ��� */ 
void USART1TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		USART1TxChar(*pt);
		pt++;
	}
}

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)	//�����ж�
	{
		Res = USART_ReceiveData(USART1);	//��ȡ���յ�������
		USART1_RX_BUF[USART1_RX_STA] = Res;
		if(USART1_RX_BUF[USART1_RX_STA] == 'K')
		{
			if(USART1_RX_BUF[USART1_RX_STA - 1] == 'O')
			{
				Flag_usart1_receive_OK = 1;
			}
		}
		if(USART1_RX_BUF[USART1_RX_STA] == 'T')
		{
			Flag_usart1_receive_T = 1;
		}
		USART1_RX_STA ++;
		if(USART1_RX_STA > (USART1_REC_LEN - 1))
			USART1_RX_STA = 0;
		Flag_usart1_receive_T = 1;
		Count_Timer3_value_USART1_receive_timeout = 2;
	}
} 

void CLR_Buf1(void)     //�������1���ջ���
{
	unsigned int y=0;
	for( y= 0;y < USART1_REC_LEN;y ++)
	{
		USART1_RX_BUF[y] = '\0';
	}
	USART1_RX_STA = 0;
} 

/**************************����2��ʼ��********************************/

/*����2��ʼ��*/
void Usart2_Init(u32 bound) 
{
	USART2_RCC_Configuration();   
	GPIO_PinRemapConfig(GPIO_Remap_USART2,DISABLE);//��ӳ��ر�	
	USART2_GPIO_Configuration();  
	USART2_Configuration(bound);   
	USART2_NVIC_Configuration();
}

void Usart2_Remap_Init(u32 bound) 
{
	USART2_RCC_Configuration();  
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);//��ӳ���	
	USART2_GPIO_Configuration();  
	USART2_Configuration(bound);   
	USART2_NVIC_Configuration();
}

/*��ʼ������2��ʱ��*/
static void USART2_RCC_Configuration(void)
{  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_TIM3, ENABLE); 
}

/*���ô���2��GPIO*/
static void USART2_GPIO_Configuration(void)	
{
	/*����GPIO��ʼ���ṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;       //PA.2 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);      //��ʼ��PA.2 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//PA.3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//��ʼ��PA.3
	
	/*����USART2�ķ��Ͷ˿�*/   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       //PD.5 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_Init(GPIOD, &GPIO_InitStructure);      //��ʼ��PD.5 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;     //PD.6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);     //��ʼ��PD.6 
}

/*���ô���2�Ĺ�������*/
static void USART2_Configuration(u32 bound) 
{
	USART_InitTypeDef USART_InitStructure; 
	/*USART���ʱ�ӳ�ʼ������*/  
	USART2_RCC_Configuration();
	/*USART���GPIO��ʼ������*/   
	USART2_GPIO_Configuration();
	USART_InitStructure.USART_BaudRate = bound;	//������һ������Ϊ9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 	//�շ�ģʽ
	/*����USART2���첽˫�����й���ģʽ*/  
	USART_Init(USART2, &USART_InitStructure); 
	/*ʹ��USART2�Ľ����ж� */   
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	/*ʹ��USART2*/   
	USART_Cmd(USART2, ENABLE);
}

//�����ж����ȼ�����  
static void USART2_NVIC_Configuration(void) 
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* USART2�ж����ȼ�*/   
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ����ȼ���Ϊ����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}


/* USART2����һ���ַ� */ 
void USART2TxChar(int ch) 
{ 
	USART_SendData(USART2,(u8) ch);         
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
	{}
}

/* USART2����һ���������ݣ�ʮ�����ƣ� */
void USART2TxData(unsigned char *pt)
{
	while(*pt != '\0')   
	{
		USART2TxChar(*pt);
		pt++;
	}
}

void USART2TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    USART2TxChar(*pt);
    pt++;
    len --; 
  }
}

/* USART2����һ���ַ��� */ 
void USART2TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		USART2TxChar(*pt);
		pt++;
	}
}

uint8_t nbcmd = 0;
uint8_t nbflag = 0;
uint8_t select = 0;
uint8_t num = 0;

/*����2�жϷ������*/
void USART2_IRQHandler(void) 
{
	u8 Res;	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�
	{
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		USART1TxChar(Res);
		USART2_RX_BUF[USART2_RX_STA] = Res;
		if(USART2_RX_BUF[USART2_RX_STA] == 'T')
		{	
			Flag_usart2_receive_T = 1;	
		}	
		if(Res == 'V' && USART2_RX_BUF[USART2_RX_STA - 1] == 'C')
		{
			nbflag = 1;
		}
		if(nbflag == 1)
		{
			nbcmd++;
		}
		if(nbcmd == 18)
		{
			if(USART2_RX_BUF[USART2_RX_STA] == 'A')
			{
				if(USART2_RX_BUF[(USART2_RX_STA + 499)%USART_REC_LEN] == '4' 
					&& USART2_RX_BUF[(USART2_RX_STA + 498)%USART_REC_LEN] == 'F' && USART2_RX_BUF[(USART2_RX_STA + 497)%USART_REC_LEN] == '1')
				{
					select = 1;
				}			
			}else if(USART2_RX_BUF[USART2_RX_STA] == 'B')
			{
				if(USART2_RX_BUF[(USART2_RX_STA + 499)%USART_REC_LEN] == '4' 
					&& USART2_RX_BUF[(USART2_RX_STA + 498)%USART_REC_LEN] == 'F' && USART2_RX_BUF[(USART2_RX_STA + 497)%USART_REC_LEN] == '1')
				{
					select = 2;
				}			
			}else if(USART2_RX_BUF[USART2_RX_STA] == 'C')
			{
				if(USART2_RX_BUF[(USART2_RX_STA + 499)%USART_REC_LEN] == '4' 
					&& USART2_RX_BUF[(USART2_RX_STA + 498)%USART_REC_LEN] == 'F' && USART2_RX_BUF[(USART2_RX_STA + 497)%USART_REC_LEN] == '1')
				{
					select = 3;
				}			
			}

		}else if(nbcmd == 28)
		{
			num = hex_to_num(USART2_RX_BUF[USART2_RX_STA]) + hex_to_num(USART2_RX_BUF[(USART2_RX_STA + 499)%USART_REC_LEN]) * 16;
			nbcmd = 0;
			nbflag = 0;
			if(select == 1)
				PWM_Car1(num);
			else if(select == 2)
			{
				if(num != 0)
					G_LED_ON
				else 
					G_LED_OFF
			}
			else if(select == 3)
				PWM_Car2(num);
			select = 0;
		}

		USART2_RX_STA++;
		if(USART2_RX_STA > (USART_REC_LEN - 1))
			USART2_RX_STA = 0;
		Flag_Usart2_Receive = 1;
		Count_Timer3_value_USART2_receive_timeout = 2;	

	}
}

void CLR_Buf2(void)     //�������2���ջ���
{
	unsigned int y=0;
	for( y= 0;y < USART_REC_LEN;y ++)
	{
		USART2_RX_BUF[y] = '\0';
	}
	USART2_RX_STA =0;
}

/**************************����3��ʼ��********************************/
/*��ʼ������3��ʱ��*/
static void USART3_RCC_Configuration(void)
{  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
}

/*���ô���3��GPIO*/
static void USART3_GPIO_Configuration(void)	
{
	/*����GPIO��ʼ���ṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//����3GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;       //PB.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);      //��ʼ��PB.10
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	//PB.11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//��ʼ��PB.11
	
	//����3��ӳ��GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	//PC.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	//��ʼ��PC.10
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	//PC.11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	//��ʼ��PC.11
	
}

/*���ô���3�Ĺ�������*/
static void USART3_Configuration(u32 bound) 
{
	USART_InitTypeDef USART_InitStructure; 
	/*USART���ʱ�ӳ�ʼ������*/  
	USART3_RCC_Configuration();
	/*USART���GPIO��ʼ������*/   
	USART3_GPIO_Configuration();
	USART_InitStructure.USART_BaudRate = bound;	//������һ������Ϊ9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 	//�շ�ģʽ
	/*����USART3���첽˫�����й���ģʽ*/  
	USART_Init(USART3, &USART_InitStructure); 
	/*ʹ��USART3�Ľ����ж� */   
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	/*ʹ��USART3*/   
	USART_Cmd(USART3, ENABLE);
}

//�����ж����ȼ�����  
static void USART3_NVIC_Configuration(void) 
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* USART3�ж����ȼ�*/   
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ����ȼ���Ϊ�ڶ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}

/*����3��ʼ��*/
void Usart3_Init(u32 bound) 
{
	USART3_RCC_Configuration();  
	USART3_GPIO_Configuration();  
	USART3_Configuration(bound);   
	USART3_NVIC_Configuration();
}

/*����3��ӳ���ʼ��*/
void Usart3_Remap_Init(u32 bound) 
{
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);//������ӳ��
	USART3_RCC_Configuration();  
	USART3_GPIO_Configuration();  
	USART3_Configuration(bound);   
	USART3_NVIC_Configuration();
}

/* USART3����һ���ַ� */ 
void USART3TxChar(int ch) 
{ 
	USART_SendData(USART3,(u8) ch);         
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
	{}
}

/* USART3����һ���������ݣ�ʮ�����ƣ� */
void USART3TxData(unsigned char *pt)
{
	while(*pt != '\0')   
	{
		USART3TxChar(*pt);
		pt++;
	}
}

void USART3TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    USART3TxChar(*pt);
    pt++;
    len --; 
  }
}

/* USART3����һ���ַ��� */ 
void USART3TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		USART3TxChar(*pt);
		pt++;
	}
}

/*����3�жϷ������*/
void USART3_IRQHandler(void) 
{
	u8 Res;	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
	{
		Res =USART_ReceiveData(USART3);	//��ȡ���յ�������
//		USART1TxChar(Res);//����		
		USART3_RX_BUF[USART3_RX_STA]=Res;
		USART3_RX_STA++;
		if(USART3_RX_STA > (USART_REC_LEN - 1))
			USART3_RX_STA = 0;
		Flag_Usart3_Receive = 1;
		Count_Timer3_value_USART3_receive_timeout = 2;//��ʱ200ms
	}
}

void CLR_Buf3(void)     //�����3���ջ���
{
	unsigned int y=0;
	for( y= 0;y < USART_REC_LEN;y ++)
	{
		USART3_RX_BUF[y] = '\0';
	}
	USART3_RX_STA =0;
}

///////////////////////////5/////////////////////////////////////////////   
static void UART5_GPIO_Configuration(void) 
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOC, &GPIO_InitStructure);   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);   

}

static void UART5_Configuration(u32 bound) 
{
	USART_InitTypeDef USART_InitStructure; 
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART5, &USART_InitStructure); 
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	USART_Cmd(UART5, ENABLE);
}

static void UART5_NVIC_Configuration(void) 
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}

void Uart5_Init(u32 bound)
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);  
	UART5_GPIO_Configuration();  
	UART5_Configuration(bound);   
	UART5_NVIC_Configuration();
}

void UART5TxChar(int ch) 
{ 
	USART_SendData(UART5,(u8) ch);         
	while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET)
	{}
}

void UART5TxData(unsigned char *pt)
{
	while(*pt != '\0')   
	{
		UART5TxChar(*pt);
		pt++;
	}
}
void UART5TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    UART5TxChar(*pt);
    pt++;
    len --; 
  }
}

void UART5TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		UART5TxChar(*pt);
		pt++;
	}
}

void UART5_IRQHandler(void)  	
{
	u8 Res;	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) 
	{
		Res =USART_ReceiveData(UART5);
		if(Res == 'L')
			PWM_Car1(100);
		else if(Res == '1')
			PWM_Car1(25);
		else if(Res == '2')
			PWM_Car1(50);
		else if(Res == '3')
			PWM_Car1(75);
		else if(Res == '4')
			PWM_Car1(100);
		else if(Res == 'l')
			PWM_Car1(0);
		else if(Res == 'J')
			G_LED_ON
		else if(Res == 'j')
			G_LED_OFF
		else if(Res == 'F')
			PWM_Car2(100);
		else if(Res == 'f')
			PWM_Car2(0);
		else if(Res == '5')
			PWM_Car2(25);
		else if(Res == '6')
			PWM_Car2(50);
		else if(Res == '7')
			PWM_Car2(75);
		else if(Res == '8')
			PWM_Car2(100);
		USART1TxChar(Res);
	}
}


#endif

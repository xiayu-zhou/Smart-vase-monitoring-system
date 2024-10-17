
#include "nb.h"


bool Flag_device_error = 0;

void Init_Nbiot(void)//��ʼ��Nbiotģ��
{
	unsigned int i,j,n = 3;
	char n_str;
	char temp_str[30];
	for(i = 0;i < 30;i ++)
		temp_str[i] = 0;
	Y_LED_ON;
	USART1TxStr("���NBģ���ϵ�ʱ���ص�����...\r\n");
	LCD_ShowString(8*2,16*2,"restarting...");	
	delay_ms(1500);
	Wait_Str1_Str2_x_100ms(2,1,1,"Leaving the BROM","",60);
	CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;	
	while(n--)
	{
		USART1TxStr("����AT...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*3,&n_str);
		LCD_ShowString(8*2,16*3,"AT...");
		USART2TxStr("AT\r\n");//����NBģ��
		if(!Wait_Str1_Str2_x_100ms(2,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;	
	n = 3;
	while(n--)
	{
		USART1TxStr("��ѯ�豸PDP��ַ...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*4,&n_str);
		LCD_ShowString(8*2,16*4,"AT+CGPADDR=1");
		USART2TxStr("AT+CGPADDR=1\r\n");//��ѯ�豸��PDP��ַ�����ظ�ʽ��+CGPADDR: 1,21.176.194.17,0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.1    ���OK
		if(!Wait_Str1_Str2_x_100ms(2,2,2,"+CGPADDR:","OK",50))
			n = 0;
		
	}CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;
	n = 3;
	while(n--)
	{
		USART1TxStr("���õ���IOTƽ̨��ַ�Ͷ˿ں�...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*5,&n_str);
		LCD_ShowString(8*2,16*5,"AT+QLWSERV=\"221.229.214.202\",5683");
		USART2TxStr("AT+QLWSERV=\"221.229.214.202\",5683\r\n");//���õ���IOTƽ̨��ַ�Ͷ˿ڣ����ظ�ʽ��OK
		if(!Wait_Str1_Str2_x_100ms(2,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;
	n = 3;
	while(n--)
	{
		USART1TxStr("��ѯIMEI��...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*6,&n_str);
		LCD_ShowString(8*2,16*6,"AT+CGSN=1");
		USART2TxStr("AT+CGSN=1\r\n");//��ѯIMEI�� ���ظ�ʽӦ��Ϊ��+CGSN: 123456789ABCDEF   ���OK
		if(!Wait_Str1_Str2_x_100ms(2,2,2,"+CGSN:","OK",50))//�ɹ��յ�IMEI���
		{//�ж�IMEI��λ�ã���ȡIMEI�룬ƴ����һ��ATָ�AT+QLWCONF="123456789ABCDEF"
			for(i = 0;i < USART_REC_LEN;i ++)//�ж�IMEI��λ��
			{
				if((USART2_RX_BUF[i] == '+') 
					&& (USART2_RX_BUF[i+1] == 'C')
					&& (USART2_RX_BUF[i+2] == 'G')
					&& (USART2_RX_BUF[i+3] == 'S')
					&& (USART2_RX_BUF[i+4] == 'N')
					&& (USART2_RX_BUF[i+5] == ':'))
				{
					strcpy(temp_str,"AT+QLWCONF=\"");//�༭��һ��ATָ��
					for(j = 0;j < 15;j ++,i ++)
						temp_str[j+12] = USART2_RX_BUF[i+7];//��ȡIMEI�룬����ƴ��
					strcpy(&temp_str[27],"\"\r\n");
					i = USART_REC_LEN;
				}
			}
			n = 0;
		}
	}CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;
	n = 3;
	while(n--)
	{
		USART1TxStr("���õ���IOTƽ̨����...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*7,&n_str);
		LCD_ShowString(8*2,16*7,temp_str);
		USART2TxStr(temp_str);//����ATָ�AT+QLWCONF="123456789ABCDEF" ���õ���IOTƽ̨������ ���ظ�ʽ��OK
		if(!Wait_Str1_Str2_x_100ms(2,1,1,"OK","",50))
			n = 0;
		for(i = 0;i < 30;i ++)
			temp_str[i] = 0;
		
	}CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;
	n = 3;
	while(n--)
	{
		USART1TxStr("���LwM2M����...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*8,&n_str);
		LCD_ShowString(8*2,16*8,"AT+QLWADDOBJ=19,0,1,\"0\"");
		USART2TxStr("AT+QLWADDOBJ=19,0,1,\"0\"\r\n");//���LwM2M���󣬷��ظ�ʽ��OK
		//Wait_Str1_Str2_x_100ms(5,1,1,"UPDATE OK","",25);
		if(!Wait_Str1_Str2_x_100ms(2,1,1,"OK","",50))
			n = 0;
		delay_ms(1000);delay_ms(1000);delay_ms(1000);
	}CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;
	n = 3;
	while(n--)
	{
		USART1TxStr("����Ƶ������ע������...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*9,&n_str);
		LCD_ShowString(8*2,16*9,"AT+QLWOPEN=0");
		USART2TxStr("AT+QLWOPEN=0\r\n");//����Ƶ������ע���������̷��� OK��֮��ȴ�Լ7�룬�ɹ����� CONNECT OK ,�ٵȴ�Լ4�룬����+QLWOBSERVE: 0,19,0,0
		if(!Wait_Str1_Str2_x_100ms(2,1,1,"CONNECT OK","",100))//���ȴ�10��
		{
			USART1TxStr("�ɹ����ӷ�������\r\n");
		}
		if(!Wait_Str1_Str2_x_100ms(2,1,1,"+QLWOBSERVE:","",70))
			n = 0;
		
	}CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;
	n = 3;
	while(n--)
	{
		USART1TxStr("�������ݸ�ʽ...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*10,&n_str);
		LCD_ShowString(8*2,16*10,"AT+QLWCFG=\"dataformat\",1,1");
		USART2TxStr("AT+QLWCFG=\"dataformat\",1,1\r\n");//�������ݸ�ʽΪʮ�������ַ�����ʽ�����ظ�ʽ��OK
		if(!Wait_Str1_Str2_x_100ms(2,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();
	
	Y_LED_OFF;	
	delay_ms(1000);
	Y_LED_ON;
	n = 3;
	while(n--)
	{
		USART1TxStr("��������֡...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*11,&n_str);
		LCD_ShowString(8*2,16*11,"AT+QLWDATASEND=19,0,1,14,02......");
		//USART2TxStr("AT+QLWDATASEND=19,0,1,6,020011000103,0x0100\r\n");
		
		USART2TxStr("AT+QLWDATASEND=19,0,1,13,02000100080000000000000000,0x0100\r\n");
	//	Wait_Str1_Str2_x_100ms(5,1,1,"OK","",20);
		if(!Wait_Str1_Str2_x_100ms(2,1,1,"SEND OK","",100))
		{
			n = 0;
			G_LED_ON;
			Y_LED_OFF;
			R_LED_OFF;
			LCD_ShowString(8*2,16*12,"send ok!");
		}
		else
		{
			Y_LED_OFF;
			G_LED_OFF;
			Y_LED_ON;
			LCD_ShowString(8*2,16*12,"fail   !");
		}
		
	}CLR_Buf2();
	LCD_Clear(BLACK);
}

bool Wait_Str1_Str2_x_100ms(char uartx,char and_or,char str_NO,char* str1,char* str2,unsigned char time_x_100ms)
{
	bool Flag_receive_right = 0;
	bool* add_Flag_Usart_x_Receive;
	unsigned char* Count_Timer3_value_USART_x_receive_timeout;
	char* USARTx_RX_BUF;
	unsigned int LEN = 0;
	switch(uartx)
	{
		case 1: add_Flag_Usart_x_Receive = &Flag_Usart1_Receive; 
						Count_Timer3_value_USART_x_receive_timeout = &Count_Timer3_value_USART1_receive_timeout;
						USARTx_RX_BUF = &USART1_RX_BUF[0];
						LEN = USART_REC_LEN;
						break;
		case 2: add_Flag_Usart_x_Receive = &Flag_Usart2_Receive; 
						Count_Timer3_value_USART_x_receive_timeout = &Count_Timer3_value_USART2_receive_timeout;
						USARTx_RX_BUF = (char*)&USART2_RX_BUF[0];
						LEN = USART_REC_LEN;
						break;
		case 3: add_Flag_Usart_x_Receive = &Flag_Usart3_Receive; 
						Count_Timer3_value_USART_x_receive_timeout = &Count_Timer3_value_USART3_receive_timeout;
						USARTx_RX_BUF = (char*)&USART3_RX_BUF[0];
						LEN = USART_REC_LEN;
						break;

	}
	Count_time_wait_ok = time_x_100ms;
	while(!Flag_receive_right && Count_time_wait_ok)
	{
		if(*add_Flag_Usart_x_Receive//�������x�����ݽ���
		&&(!*Count_Timer3_value_USART_x_receive_timeout))//����������ճ�ʱ
		{
			*add_Flag_Usart_x_Receive = 0;
			if(and_or == 2)//���Ҫ�����������ַ���
			{
				if(Query(USARTx_RX_BUF,str1,LEN) && Query(USARTx_RX_BUF,str2,LEN))
				{
					Flag_receive_right = 1;
					//USART1TxStr(USARTx_RX_BUF);
					//USART1TxStr("������ȷ��\r\n");
				}
			}
			else if(and_or == 1)//���ֻҪ������һ���ַ���
			{
				if(Query(USARTx_RX_BUF,str1,LEN))
				{
					Flag_receive_right = 1;
					//USART1TxStr(USARTx_RX_BUF);
					//USART1TxStr("������ȷ��\r\n");
				}
				else
				{
					if(str_NO == 2)
					{
						if(Query(USARTx_RX_BUF,str2,LEN))
						{
							Flag_receive_right = 1;
							//USART1TxStr(USARTx_RX_BUF);
							//USART1TxStr("������ȷ��\r\n");
						}
					}
				}
			}
		}
	}
	if(!Count_time_wait_ok)
	{
		//USART1TxStr("Flag_device_error = 1 \r\n");
		//USART1TxStr(USARTx_RX_BUF);
		Flag_device_error = 1;
		R_LED_ON;
	}
	else
	{
		R_LED_OFF;
		Flag_device_error = 0;
	}
//	USART1TxStr("Count_time_wait_ok = ");
//	USART1TxChar(Count_time_wait_ok / 100 + '0'); 
//	USART1TxChar(Count_time_wait_ok % 100 / 10 + '0'); 
//	USART1TxChar(Count_time_wait_ok % 10 + '0');
//  USART1TxStr("\r\n");	
	delay_ms(100);	
	if(Flag_device_error)
		return 1;//��ʱ����1
	else
		return 0;//��������0
}

void DealUpData(char *from,uint8_t *to,uint16_t len)
{
	int i=0;
	uint16_t tlen=len+7;
	char tmp[3]={0};
	strcat((char *)to,"19,0,1,");
	to+=7;
	if(tlen>=100)
	{
		*to=tlen/100+'0';
		to++;
		*to=(tlen%100)/10+'0';
		to++;
		*to=tlen%10+'0';
		to++;
	}else if(tlen>=10){
		*to=tlen/10+'0';
		to++;
		*to=tlen%10+'0';
		to++;
	}else{
		*to=tlen+'0';
		to++;
	}
	strcat((char *)to,",020001000700");
	to+=13;
	sprintf((char *)to,"%02x",len);
	
	to++;
	for(i=0;i<strlen(from);i++)
	{
		sprintf(tmp,"%02x",from[i]);
		strcat((char *)to,tmp);
	}
	strcat((char *)to,",0x0100\r\n");
}

void Array_CLR(char *src,char len) //�������
{	
	unsigned int y=0;	
	for( y= 0;y < len;y ++)
	{
		src[y] = '\0';
	}
}

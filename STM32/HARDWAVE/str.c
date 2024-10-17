
#include "str.h"


void copy_str(char* des,char* src,unsigned char len)
{
	unsigned char i;
	for(i = 0;i < len;i ++)
	{
		*(des + i) = *(src + i);
	}
}

void int_to_hex(unsigned int num, char* hex_str, uint8_t len) {
    int temp;
    while (num != 0)
    {
        temp = num % 16;
        if (temp < 10) {
            temp += 48; // ASCII??0??  
        }
        else {
            temp += 55; // ASCII??A??  
        }
        len--;
        hex_str[len] = temp;
        num /= 16;
    }
}

void nbSendData(char* buf, int serverID, char* Data)
{
    int len, Len;
    len = strlen(Data) / 2;
    Len = len + 5;
    sprintf(buf,"AT+QLWDATASEND=19,0,1,%d,02%04X%04X%s,0x0100\r\n",Len,serverID,len,Data);
}

void clearSting(char* str, int Len,char ch)
{
    unsigned char i;
    for (i = 0; i < Len; i++)
    {
        str[i] = ch;
    }
}

unsigned char Query(char * src,char * des,unsigned int LEN)
	//查询数组有无包含该字符串，有则返回1，无则返回0
{
	unsigned int y= 0,len= 0,n= 0;
	unsigned char Result = 0;
	char * i;
	i = des;
	for(; *i != '\0';i ++,len ++){}// 判断需要检测的字符的长度
	for(y = 0; y < LEN - len;y ++)
		//开始检测，次数为总长度减去字符长度的字节数
	{
		for(n = 0;n < len;n ++)
		{
			if(*(src + y + n) == *(des + n))
				//开始检测双方的第一个字节，如果相等则结果等于1，并且继续检测双方的第二个字节
			{
				Result = 1;				
			}
			else
			{
				Result = 0;	//不相等则结果等于0，并且退出此次循环，
										//开始检测数组的第二个字节和字符的第一个字节
				break;
			}
		}
		if(n == len)
		{
			return Result;
		}
	}
	return Result;
}

uint8_t bijiao(char *str,char *str1,uint8_t len)
{
	uint8_t i;
	for(i = 0;i < len;i++)
	{
		if(str[i] != str1[i])
			return 0;
	}
	return 1;
}

uint8_t hex_to_num(char ch)
{
	if(ch < 58)
		return ch - 48;
	else return ch - 65;
}


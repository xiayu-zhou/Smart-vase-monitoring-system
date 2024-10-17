#ifndef __STR_H__
#define __STR_H__
#include "stm32f10x.h"                  // Device header
#include <string.h>

void copy_str(char* des,char* src,unsigned char len);
void int_to_hex(unsigned int num, char* hex_str, uint8_t len);
void nbSendData(char* buf, int serverID, char* Data);
void clearSting(char* str, int Len,char ch);
unsigned char Query(char * src,char * des,unsigned int LEN);
uint8_t bijiao(char *str,char *str1,uint8_t len);
uint8_t hex_to_num(char ch);

#endif
//定长顺序存储
#include <stdio.h>
#define MAXSIZE 100
typedef struct
{
	char str[MAXSIZE + 1];					//最后一位存'\0'
	int length;
}Str;

//变长顺序分配存储
#include<stdio.h>
#include<stdlib.h>
typedef struct
{
	char *ch;					//指向动态分配的存储区的首地址的字符指针
	int length;
}Str;

//将一个串赋值给另一个串
int strassign(Str &str, char*ch) {
	if (str.ch)									//若str非空，则释放其空间
	{
		free(str.ch);
		str.ch = NULL;
	}												//创建length存储ch长度，用c指向ch，用c处理操作而不应直接用ch
	int length=0;
	char*c = ch;
	while (c)
	{
		++length;
		++c;
	}
	if (length == 0)
	{
		str.length = 0;
		return 1;
	}
	else
	{
		str.ch = (char*)malloc(sizeof(char)*(length + 1));
		if (str.ch == NULL) return 0;
		else
		{
			c = ch;
			for (int i = 0;i <= length;++i, ++c)
			{
				str.ch[i] = *c;
			}
			str.length = length;
			return 1;
		}
	}
}

//取串长度
int strlength(Str str)
{
	return str.length;
}

//串的比较
int strcompare(Str s1, Str s2)
{
	int i = 0;
	while (i < s1.length&&i < s2.length)
	{
		if (s1.ch[i]==s2.ch[i])
		{
			++i;
			continue;
		}
		else
		{
			return s1.ch[i]-s2.ch[i];
		}
	}
	return s1.length - s2.length;
}


//串连接
int concat(Str &str, Str str1, Str str2)
{
	if (str.ch)
	{
		free(str.ch);
		str.ch = NULL;
	}
	str.ch = (char*)malloc(sizeof(char)*(str1.length+str2.length+1));
	if (str.ch == NULL) return 0;
	for (int i = 0;i < str1.length;++i)
	{
		str.ch[i] = str1.ch[i];
	}
	for (int i = 0;i <= str2.length;++I)
	{
		str.ch[str1.length + i] = str2.ch[i];
	}
	str.length = str1.length + str2.length;
	return 1;
}

//求子串，从pos开始，长度为len，存入substr
int substring(Str &substr, Str str, int pos, int len)
{
	if (pos<0 || len>str.length) return 0;
	if (substr.ch)
	{
		free(substr.ch);
		substr.ch = NULL;
	}
	if (len == 0)										//若len为0，则无需malloc操作
	{
		substr.ch = NULL;
		substr.length = 0;
		return 1;
	}
	substr.ch = (char*)malloc(sizeof(char)*(len+1));
	if (substr.ch) return 0;
	substr.length = 0;
	while (substr.length<len)
	{
		substr.ch[substr.length] = str.ch[pos + substr.length];
		++substr.length;
	}
	substr.ch[substr.length] = '\0';
	--substr.length;
	return 1;
}

//串清空
int clearstring(Str &str)
{
	if (str.ch)
	{
		free(str.ch);
		str.ch = NULL;
	}
	str.length = 0;
}

/*
	串的模式匹配算法
	（本节字符存储在1~length，之前是0~length-1）
*/
//简单模式匹配算法，返回主串中的位置
int index(Str str, Str substr)
{
	int i = 1, j = 1, k = 1;
	while (i<=str.length&&j<=substr.length)
	{
		if (str.ch[i] == str.ch[j])
		{
			++i;
			++j;
		}
		else
		{
			++k;
			j = 1;
			i = k;
		}
	}
	if (j > substr.length)
	{
		return k;
	}
	else
	{
		return 0;
	}
}

//KMP算法，包含getnext，KMP
void getnext(Str substr, int next[])
{
	int i = 1, j = 0;
	next[i] = 0;
	while (i<=substr.length)
	{
		if (j == 0 || substr.ch[i] == substr.ch[j])
		{
			++i, ++j;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}
int KMP(Str str, Str substr, int next[])
{
	int i = 1, j = 1;
	while (i<=str.length&&j<=substr.length)
	{
		if (j==0||str.ch[i] == substr.ch[j])
		{
			++i, ++j;
		}
		else
		{
			j = next[j];
		}
	}
	if (j>substr.length)
	{
		return i - substr.length;
	}
	else return 0;
}

//KMP算法改进，nextval替换next，省去不必要的过程(在getnext基础上添加代码)
void getnextval(Str substr, int nextval[])
{
	int i = 1, j = 0;
	nextval[i] = 0;
	while (i <= substr.length)
	{
		if (j == 0 || substr.ch[i] == substr.ch[j])
		{
			++i, ++j;
			if (substr.ch[i] != substr.ch[j])
			{
				nextval[i] = j;
			}
			else
			{
				nextval[i] = nextval[j];
			}
		}
		else
		{
			j = nextval[j];
		}
	}
}







#include<stdio.h>

int main(void)
{
	FILE* fp = fopen("test.txt", "r");
	if(fp == NULL)
	{
		printf("�ļ���ʧ��!");
		return -1;
	}
	int lower = 0, upper = 0, other = 0;
	char ch = 0;
	while(!feof(fp))
	{
		ch = getc(fp);
		if(ch >= 'a' && ch <= 'z')
		{
			lower++;
		}
		else if(ch >= 'A' && ch <= 'Z')
		{
			upper++;
		}
		else if(ch != ' ')
		{
			other++;
		}
	}
	printf("Сд�ַ�:%d\n��д�ַ�:%d\n�����ַ�:%d\n", lower, upper, other);
	printf("�ַ�����:%d", lower+upper+other);
	fclose(fp);
	return 0;
}

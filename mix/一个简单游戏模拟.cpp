#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int turn(int n)
{
	int a = 0, b = 0;
	a = rand()%5+1;
	b = rand()%5+1;
	if(n == 1)
	{
		if(a+b==7||a+b==11)
		{
			printf("��%d����Ӯ�ˣ�", n); 
			return 0;
		}
		else if(a+b==2||a+b==3||a+b==12)
		{
			printf("��%d�������ˣ�", n);  
			return 0;
		}
		else
		{
			return a+b;
		}
	}
	else
	{
		if(a+b==7)
		{
			printf("��%d�������ˣ�", n); 
			return 0;
		}
	}
	return a+b;
}

int main(void)
{
	int n = 1, sum = 0, temp = 0;
	srand(time(0));
	while(temp = turn(n))
	{
		if(n == 1)
		{
			sum = temp;
		}
		else
		{
			if(sum == temp)
			{
				printf("��%d����Ӯ�ˣ�", n); 
				break;
			}
		}
		printf("��%d�ֵ���:%d\n", n, temp);
		n++;
	}
	return 0;
}

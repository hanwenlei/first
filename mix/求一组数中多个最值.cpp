#include<stdio.h>

int main(void)
{
	int i = 0, cntMin = 0, cntMax = 0, minNum = 50000, maxNum = -50000;
	int a[10] = {0}, min[10] = {0}, max[10] = {0};
	for(i = 0; i < 10; i++)			//���������ݣ������� 
	{
		scanf("%d", &a[i]);
		if(a[i] < minNum)
		{
			minNum = a[i];
			cntMin = 0;
			min[cntMin++] = i;
		}
		else if(a[i] == minNum)
		{
			min[cntMin++] = i;
		}
		if(a[i] > maxNum)
		{
			maxNum = a[i];
			cntMax = 0;
			max[cntMax++] = i;
		}
		else if(a[i] == maxNum)
		{
			max[cntMax++] = i;
		}
	}
	printf("max:");
	for(i = 0; i < cntMax; i++)					//������ֵ���м������ֵ��ѭ������ 
	{
		printf("a[%d]=%d ", max[i], maxNum);
	}
	printf("\nmin:");
	for(i = 0; i < cntMin; i++)					//�����Сֵ���м�����Сֵ��ѭ������ 
	{
		printf("a[%d]=%d ", min[i], minNum);
	}
	return 0;
}
